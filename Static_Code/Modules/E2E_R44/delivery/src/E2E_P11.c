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
**  SRC-MODULE: E2E_P11.c                                                     **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR E2E Module                                            **
**                                                                            **
**  PURPOSE   : To implement specification of E2E Profile 11 driver           **
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
** 0.0.1    02-Sep-2019    VuHB            Initial Version                    **
** 0.0.2    20-Feb-2020    CuongLX         Remove marcro less meaning         **
** 0.0.3    19-Mar-2020    CuongLX         Change logic check DataIDMode of   **
**                                         function check                     **
** 1.0.1    28-Dec-2021    HiepVT1         Add code to check the validity of  **
**                                         E2E inputs (Length and offset)     **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "E2E.h"
/*******************************************************************************
**                      Global DataPtr Types                                  **
*******************************************************************************/

/*******************************************************************************
**          Function Prototypes for E2E Profile 11                            **
*******************************************************************************/
static FUNC(uint8, E2E_CODE) E2E_P11CalculateCRC(
    P2CONST(E2E_P11ConfigType, AUTOMATIC, E2E_APPL_CONST) ConfigPtr,
    P2CONST(uint8, AUTOMATIC, E2E_APPL_CONST) DataPtr,
    VAR(uint16, AUTOMATIC) Length);

static FUNC(void, AUTOMATIC) E2E_P11CheckStatus(
    P2CONST(E2E_P11ConfigType, AUTOMATIC, E2E_APPL_CONST) ConfigPtr,
    P2VAR(E2E_P11CheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
    VAR(boolean, AUTOMATIC) NewDataAvailable,
    VAR(boolean, AUTOMATIC) IsCorrectData,
    VAR(uint8, AUTOMATIC) RcvdCntrVal);

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define E2E_START_SEC_CODE_ASIL_D /*polyspace MISRA2012:2.5 [Justified:Low] "This macro is necessary for Memory mapping"*/
#include "MemMap.h" /*polyspace MISRA2012:20.1 [Justified:Low] "This include directive is necessary for Memory mapping"*/

/*******************************************************************************
** Function Name        : E2E_P11Protect                                      **
**                                                                            **
** Service ID           : 0x3b                                                **
**                                                                            **
** Description          : Protects the array/buffer to be transmitted using   **
**                        the E2E profile 11. This includes checksum          **
**                        calculation, handling of counter.                   **
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

FUNC(Std_ReturnType, E2E_CODE) E2E_P11Protect(
    P2CONST(E2E_P11ConfigType, AUTOMATIC, E2E_APPL_CONST) ConfigPtr,
    P2VAR(E2E_P11ProtectStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
    P2VAR(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr,
    VAR(uint16, AUTOMATIC) Length)
{
  /* Local variable to store nibble value */
  VAR(uint8, AUTOMATIC) dataNibble;
  /* Local variable to store counter value */
  VAR(uint8, AUTOMATIC) counterValue;
  /* Local variable to store crc offset value */
  VAR(uint16, AUTOMATIC) crcOffset;
  /* Local variable to store nibble offset value */
  VAR(uint16, AUTOMATIC) nibbleOffset;
  /* Local variable to store counter offset value */
  VAR(uint16, AUTOMATIC) counterOffset;
  /* Local variable to store calculated crc value */
  VAR(uint8, AUTOMATIC) crcCalculate;
  /* Local variable to store offset value */
  VAR(Std_ReturnType, AUTOMATIC) returnValue;

  returnValue = E2E_E_OK;
  
  /* @Trace: SafeE2E_SUD_MF_601 */
  /* polyspace-begin MISRA2012:D4.14 [Justified:Low] "the pointer is check for not null previous branch"*/
  if ((NULL_PTR == ConfigPtr) || (NULL_PTR == StatePtr) || 
      (NULL_PTR == DataPtr))
  {
    returnValue = E2E_E_INPUTERR_NULL;
  }
  else if ((E2E_P11_MAX_DATA_LENGTH_LIMIT < ConfigPtr->DataLength) ||
           (E2E_P11_CNT_MAX < ConfigPtr->MaxDeltaCounter))
  
  {
    returnValue = E2E_E_INPUTERR_WRONG;
  }
  /* @Trace: SafeE2E_SUD_MF_602 */
  else if ((0x0000U != ((ConfigPtr->CounterOffset) % 0x0004U)) ||
           (0x0000U != ((ConfigPtr->CRCOffset) % 0x0008U)) ||
           (0x0000U != ((ConfigPtr->DataLength) % 0x0008U)) ||
           (Length != ((ConfigPtr->DataLength) / 0x0008U)))
  {
    returnValue = E2E_E_INPUTERR_WRONG;
  }
  else if(Length < ((uint16)(ConfigPtr->CRCOffset / 0x0008U) + 0x0001U))
  {
    returnValue = E2E_E_INPUTERR_WRONG;
  }  
  else
  {
    nibbleOffset = (ConfigPtr->DataIDNibbleOffset) / 0x0008U;
    counterOffset = (ConfigPtr->CounterOffset) / 0x0008U;

    /* @Trace: SafeE2E_SUD_MF_603 */
    if (E2E_P11_DATAID_NIBBLE == (ConfigPtr->DataIDMode))
    {
      /* 
      * Calculate the pointer to Nibble Byte based on 
      * the DataIDNibble offset */
      
      dataNibble = DataPtr[nibbleOffset]; 
      
      if (0x0000U == ((ConfigPtr->DataIDNibbleOffset) % 
        0x0008U))
      {
        /* Update the nibble value in the lower nibble of the nibble byte */
        dataNibble = (uint8)((dataNibble & E2E_HIGH_NIBBLE_MASK) | 
          ((uint8)((ConfigPtr->DataID) >> 0x0008U) & 
          E2E_LOW_NIBBLE_MASK));
      }
      else
      {
        /* Update the nibble value in the higher nibble of the nibble byte */
        dataNibble = (uint8)((dataNibble & E2E_LOW_NIBBLE_MASK) | 
          ((uint8)((ConfigPtr->DataID) >> 0x04U) & 
          E2E_HIGH_NIBBLE_MASK));
      }
      /* store the nibble value in data stream */
      DataPtr[nibbleOffset] = dataNibble;
    }
    
    /*Calculate the pointer to Counter Byte based on the counter offset */
    
    
    counterValue = DataPtr[counterOffset]; 
    

    /* @Trace: SafeE2E_SUD_MF_600 */    
    if (0x0000U == 
      ((ConfigPtr->CounterOffset) % 0x0008U))
    {
      /* Update the counter value in the lower nibble of the counter byte */
      counterValue = (uint8)((counterValue & E2E_HIGH_NIBBLE_MASK) | 
        ((StatePtr->Counter) & E2E_LOW_NIBBLE_MASK));     
    }
    else
    {
      /* Update the counter value in the higher nibble of the counter byte */
      counterValue = (uint8)((counterValue & E2E_LOW_NIBBLE_MASK) | 
        ((uint8)((StatePtr->Counter) << 0x04U) & 
        E2E_HIGH_NIBBLE_MASK)); 
    }
    /* store the counter value in data stream */
    DataPtr[counterOffset] = counterValue;

    /* Compute offset */
    crcOffset = ConfigPtr->CRCOffset / 0x0008U;

    /* Compute CRC */
    crcCalculate = E2E_P11CalculateCRC(ConfigPtr, 
      (P2CONST(uint8, AUTOMATIC, E2E_APPL_CONST))DataPtr, Length);

    /* Write CRC */
    DataPtr[crcOffset] = crcCalculate;

    /* Increment Counter */
    StatePtr->Counter = ((StatePtr->Counter + 0x01U) % E2E_P11_CNT_LIMIT);
  }/* polyspace-end MISRA2012:D4.14 [Justified:Low] "the pointer is check for not null previous branch"*/

  return returnValue;
}

/*******************************************************************************
** Function Name        : E2E_P11Check                                        **
**                                                                            **
** Service ID           : 0x38                                                **
**                                                                            **
** Description          : Checks the Data received using the E2E profile 11   **
**                        This includes checksum calculation, handling of     **
**                        counter.                                            **
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
SRS_E2E_08534  SRS_E2E_08529 SRS_BSW_00323 SRS_E2E_08539 RS_E2E_08543*/

FUNC(Std_ReturnType, E2E_CODE) E2E_P11Check(
    P2CONST(E2E_P11ConfigType, AUTOMATIC, E2E_APPL_CONST) ConfigPtr,
    P2VAR(E2E_P11CheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
    P2CONST(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr,
    VAR(uint16, AUTOMATIC) Length)
{
  /* Local variable to store return value */
  VAR(Std_ReturnType, AUTOMATIC) returnValue;
  /* Local variable to store received counter value */
  VAR(uint8, AUTOMATIC) receivedCounterVal;
  /* Local variable to store nibble value */
  VAR(uint8, AUTOMATIC) nibbleValue;
  /* Local variable to store received crc value */
  VAR(uint8, AUTOMATIC) receivedCrcVal;
  /* Local variable to store calculated crc value */
  VAR(uint8, AUTOMATIC) crcCalculate;
  /* Local variable to store crc offset value */
  VAR(uint16, AUTOMATIC) crcOffset;
  /* Local variable to store counter offset value */
  VAR(uint16, AUTOMATIC) counterOffset;
  /* Local variable to store nibble offset value */
  VAR(uint16, AUTOMATIC) dataIDNibbleOffset;
  /* Local variable to store flag check whether data is available */
  VAR(boolean, AUTOMATIC) newDataAvailable;
  /* Local variable to store flag check whether data is correct */
  VAR(boolean, AUTOMATIC) isCorrectData;

  returnValue = E2E_E_OK;
  nibbleValue = 0x00U;
  newDataAvailable = FALSE;
  isCorrectData = FALSE;
  receivedCounterVal = 0x00U;
 
  /* Verify inputs of the check function */
  if ((NULL_PTR != ConfigPtr) && (NULL_PTR != StatePtr))
  {
    /* @Trace: SafeE2E_SUD_MF_606 */    
    if ((NULL_PTR == DataPtr) && (0x00U != Length))
    {
      returnValue = E2E_E_INPUTERR_WRONG;
    }
    else if ((NULL_PTR != DataPtr) && (0x00U == Length))
    {
      returnValue = E2E_E_INPUTERR_WRONG;
    }
      /* polyspace-begin MISRA2012:D4.14 [Justified:Low] "the pointer is check for not null previous branch"*/
    else if ((Length < ((uint16)(ConfigPtr->CRCOffset / 0x0008U) + 0x0001U)) && \
      (Length != 0))
    {
      returnValue = E2E_E_INPUTERR_WRONG;
    }
    else
    {
      if (NULL_PTR != DataPtr)
      {      
        if ((E2E_P11_MAX_DATA_LENGTH_LIMIT >= ConfigPtr->DataLength) && \
            (E2E_P11_CNT_MAX >= ConfigPtr->MaxDeltaCounter) && \
            (0x0000U == (ConfigPtr->CounterOffset % 0x0004U)) && \
            (0x0000U == (ConfigPtr->CRCOffset % 0x0008U)) && \
            (0x0000U == (ConfigPtr->DataLength % 0x0008U)))

        {
          newDataAvailable = TRUE;
          /* Read Nibble */
          if (E2E_P11_DATAID_NIBBLE == ConfigPtr->DataIDMode)
          {
            dataIDNibbleOffset = (ConfigPtr->DataIDNibbleOffset / 0x0008U);

            if (0x0000U == (ConfigPtr->DataIDNibbleOffset % 0x0008U))
            {
              /* Get the nibble value from the lower 
              *  nibble of the nibble byte */
              
              nibbleValue = \
              (DataPtr[dataIDNibbleOffset] & E2E_LOW_NIBBLE_MASK); 
              
            }
            else
            {
              /* Get the nibble value from the higher 
              * nibble of the nibble byte */
              
              nibbleValue = \
                ((DataPtr[dataIDNibbleOffset] >> 0x04U) & E2E_LOW_NIBBLE_MASK);
              
            }
          }
          /* Read Counter */
          counterOffset = (ConfigPtr->CounterOffset / 0x0008U);

          if (0x0000U == (ConfigPtr->CounterOffset % 0x0008U))
          {
            /* Get the counter value from the lower 
            * nibble of the counter byte */
           
            receivedCounterVal = \
              (DataPtr[counterOffset] & E2E_LOW_NIBBLE_MASK);  
            
          }
          else
          {
            /* Get the counter value from the higher 
            * nibble of the counter byte */
            
            receivedCounterVal = \
            ((DataPtr[counterOffset] >> 0x04U) & E2E_LOW_NIBBLE_MASK);  
           
          } /* End of else */

          /* Read CRC */
          crcOffset = (ConfigPtr->CRCOffset / 0x0008U);
          receivedCrcVal = DataPtr[crcOffset];

          /* Compute CRC */
          crcCalculate = E2E_P11CalculateCRC(ConfigPtr, DataPtr, Length);

          /* Check received crc, data id, length is correct */
          if (receivedCrcVal == crcCalculate)
          {
            isCorrectData = TRUE;
          }
          else
          {
            isCorrectData = FALSE;
          }
          /* Check data id, length is correct */
          if ((E2E_P11_DATAID_NIBBLE == ConfigPtr->DataIDMode) && \
              (nibbleValue != (uint8)((ConfigPtr->DataID >> 0x0008U) & \
              E2E_LOW_NIBBLE_MASK)))
          {
            isCorrectData = FALSE;
          }
          
          /* Do Checks */
          E2E_P11CheckStatus(ConfigPtr, StatePtr, newDataAvailable, 
            isCorrectData, receivedCounterVal);
        }
        else
        {
          returnValue = E2E_E_INPUTERR_WRONG;
        }/* polyspace-end MISRA2012:D4.14 [Justified:Low] "the pointer is check for not null previous branch"*/
      }
      else
      {
        /* Do Checks */
        E2E_P11CheckStatus(ConfigPtr, StatePtr, newDataAvailable, isCorrectData, 
          receivedCounterVal);
      }
    }
  }
  
  /* @Trace: SafeE2E_SUD_MF_605 */    
  else
  {
    returnValue = E2E_E_INPUTERR_NULL;
  }
  /* return the error flag value */
  return returnValue;
}

/*******************************************************************************
** Function Name        : E2E_P11CheckStatus                                  **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : This function Check Status  over received data.     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : ConfigPtr, DataPtr, Length                          **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return Value         : none                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                                                                            **
**                        Function(s) invoked    : None                       **
*******************************************************************************/
/* @Trace: SRS_E2E_08534  SRS_E2E_08529 SRS_BSW_00323 SRS_E2E_08539 RS_E2E_08543*/

static FUNC(void, AUTOMATIC) E2E_P11CheckStatus(
    P2CONST(E2E_P11ConfigType, AUTOMATIC, E2E_APPL_CONST) ConfigPtr,
    P2VAR(E2E_P11CheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
    VAR(boolean, AUTOMATIC) NewDataAvailable,
    VAR(boolean, AUTOMATIC) IsCorrectData,
    VAR(uint8, AUTOMATIC) RcvdCntrVal)
{
  /* Local variable to store delta counter value */
  VAR(uint8, AUTOMATIC) deltaCounter;

  /* @Trace: SafeE2E_SUD_MF_610 */
  /* Check new data is available */
  if (TRUE == NewDataAvailable)
  {
    /* polyspace-begin MISRA2012:D4.14 [Justified:Low] "the pointer is check for not null previous branch"*/
    if (TRUE == IsCorrectData)
    {
      /* Compute Delta Counter */
      
      if (RcvdCntrVal >= (StatePtr->Counter))
      
      {
        deltaCounter = RcvdCntrVal - StatePtr->Counter;
      }
      /* when the received counter is less than the previous counter */
      else
      {
        deltaCounter = ((E2E_P11_CNT_MAX - StatePtr->Counter) + RcvdCntrVal) + 0x01U;
      }
      /* Counter Check */

      /* When the delta counter value is greater than max delta counter value */
      if (deltaCounter > ConfigPtr->MaxDeltaCounter)
      {
        StatePtr->Status = E2E_P11STATUS_WRONGSEQUENCE;
      }
      /* When the delta counter value is zero */
      else if ((uint8)0x00U == deltaCounter)
      {
        StatePtr->Status = E2E_P11STATUS_REPEATED;
      }
      /* When the delta counter value is one */
      else if ((uint8)0x01U == deltaCounter)
      {
        StatePtr->Status = E2E_P11STATUS_OK;
      }
      /*
      * When the delta counter value is greater than one and
      * equal to or less than the max delta counter
      */
      else
      {
        StatePtr->Status = E2E_P11STATUS_OKSOMELOST;
      }
      /* Update the counter value */
      StatePtr->Counter = RcvdCntrVal;
    }
    else
    {
      StatePtr->Status = E2E_P11STATUS_ERROR;
    }
  }
  else
  {    
    StatePtr->Status = E2E_P11STATUS_NONEWDATA;  
  }/* polyspace-end MISRA2012:D4.14 [Justified:Low] "the pointer is check for not null previous branch"*/
}

/*******************************************************************************
** Function Name        : E2E_P11CalculateCRC                                 **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : This function calculate CRC over received data.     **
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
**                        Function(s) invoked    : Crc_CalculateCRC8          **
*******************************************************************************/
/* @Trace: SRS_E2E_08534  SRS_E2E_08529 SRS_BSW_00323 SRS_E2E_08539 RS_E2E_08543*/

static FUNC(uint8, E2E_CODE) E2E_P11CalculateCRC(
    P2CONST(E2E_P11ConfigType, AUTOMATIC, E2E_APPL_CONST) ConfigPtr,
    P2CONST(uint8, AUTOMATIC, E2E_APPL_CONST) DataPtr,
    VAR(uint16, AUTOMATIC) Length)
{
  /* Local variable to store crc value */
  VAR(uint8, AUTOMATIC) crcCalculate;
  /* Local variable to store crc data value */
  VAR(uint8, AUTOMATIC)  crcData;
  /* Local variable to store crc offset value */
  VAR(uint16, AUTOMATIC) crcOffset;
  /* Local variable to store length data after Crc byte */
  VAR(uint16, AUTOMATIC) lengthAftCrc = 0x0000U;

  crcCalculate = 0x00U;

  /* @Trace: SafeE2E_SUD_MF_609 */
  /* Compute offset */
  crcOffset = ConfigPtr->CRCOffset / 0x0008U;

  switch (ConfigPtr->DataIDMode)
  {
    case E2E_P11_DATAID_BOTH:

      /* Take LSB Byte for CRC calculation */
      crcData = (uint8)(ConfigPtr->DataID & E2E_LOW_BYTE_MASK);

      /* Calculate CRC for the LSB Byte */
      crcCalculate = Crc_CalculateCRC8(&crcData, 0x00000001UL, 
        E2E_P11_CRC_INIT_VALUE, FALSE);

      /* Take MSB Byte for CRC calculation */
      crcData = (uint8)((ConfigPtr->DataID >> 0x0008U) & 
        E2E_LOW_BYTE_MASK);

      /* Calculate CRC for the MSB Byte */
      crcCalculate = Crc_CalculateCRC8(&crcData, 0x00000001UL, 
        crcCalculate, FALSE);

      break;

    case E2E_P11_DATAID_NIBBLE:

      /* Take LSB Byte for CRC calculation */
      crcData = (uint8)(ConfigPtr->DataID & E2E_LOW_BYTE_MASK);

      /* Calculate CRC for the LSB Byte */
      crcCalculate = Crc_CalculateCRC8(&crcData, 0x00000001UL, 
        E2E_P11_CRC_INIT_VALUE, FALSE);

      /* Make 0x00 for CRC calculation */
      crcData = 0x00U;

      /* Calculate CRC for the LSB Byte */
      crcCalculate = Crc_CalculateCRC8(&crcData, 0x00000001UL, 
        crcCalculate, FALSE);

      break;

    default:
      /* Nothing */
      break;
  }

  /* The validity of LengthForCRC has been checked before. Checking again just only for polyspace */
  if(Length > (crcOffset + 0x0001U))
  {
    lengthAftCrc = (Length - crcOffset) - 0x0001U;
  } 

  if (0x00U < crcOffset)
  {
    crcCalculate = Crc_CalculateCRC8(&DataPtr[0x00U], (uint32)crcOffset, 
      crcCalculate, FALSE);
	  
    crcCalculate = Crc_CalculateCRC8(&DataPtr[crcOffset + 0x0001U],  
      (uint32)lengthAftCrc, crcCalculate, FALSE);
  }
  else
  {
    crcCalculate = Crc_CalculateCRC8(&DataPtr[0x01U], 
      (uint32)lengthAftCrc, crcCalculate, FALSE);
  }
  
  return crcCalculate;
}

/*******************************************************************************
** Function Name        : E2E_P11ProtectInit                                  **
**                                                                            **
** Service ID           : 0x3c                                                **
**                                                                            **
** Description          : This function shall initializes the protection      **
**                        state.                                              **
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

FUNC(Std_ReturnType, E2E_CODE) E2E_P11ProtectInit(
    P2VAR(E2E_P11ProtectStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr)
{
  /* Local variable to store return value */
  VAR(Std_ReturnType, AUTOMATIC) returnValue;

  returnValue = E2E_E_OK;
  
  /* @Trace: SafeE2E_SUD_MF_604 */    
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
** Function Name        : E2E_P11CheckInit                                    **
**                                                                            **
** Service ID           : 0x39                                                **
**                                                                            **
** Description          : This function shall initializes the check state.    **
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

FUNC(Std_ReturnType, E2E_CODE) E2E_P11CheckInit(
    P2VAR(E2E_P11CheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr)
{
  /* Local variable to store return value */
  VAR(Std_ReturnType, AUTOMATIC) returnValue;

  returnValue = E2E_E_OK;

  /* @Trace: SafeE2E_SUD_MF_607 */
  /* Check for the invalid input parameters */
  /* polyspace-begin MISRA2012:D4.14 [Justified:Low] "the pointer is check for not null previous branch"*/
  if (NULL_PTR == StatePtr)
  {
    returnValue = E2E_E_INPUTERR_NULL;
  }
  else
  { 
    /* Set Counter to 0x0E */
    StatePtr->Counter = E2E_P11_CNT_MAX;

    /* Set Status to E2E_P11STATUS_ERROR */
    StatePtr->Status = E2E_P11STATUS_ERROR;
  }/* polyspace-end MISRA2012:D4.14 [Justified:Low] "the pointer is check for not null previous branch"*/

  return returnValue;
}
/*******************************************************************************
** Function Name        : E2E_P11MapStatusToSM                                **
**                                                                            **
** Service ID           : 0x3a                                                **
**                                                                            **
** Description          : This function shall maps the check status of        **
**                        Profile 11 to a generic check status, which can be  **
**                        used by E2E state machine check function. The E2E   **
**                        Profile 11 delivers a more fine-granular status, but**
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

FUNC(E2E_PCheckStatusType, E2E_CODE) E2E_P11MapStatusToSM(
    VAR(Std_ReturnType, AUTOMATIC) CheckReturn,
    VAR(E2E_P11CheckStatusType, AUTOMATIC) Status)
{
  /* Local variable to store return value */
  VAR(E2E_PCheckStatusType, AUTOMATIC) returnValue;
  
  returnValue = E2E_P_ERROR;

  /* @Trace: SafeE2E_SUD_MF_608 */
  /* Verify inputs of the protect function */
  if (E2E_E_OK == CheckReturn)
  {
    switch (Status)
    {
      case E2E_P11STATUS_OK: /* walk through */
      case E2E_P11STATUS_OKSOMELOST:
        returnValue = E2E_P_OK;
        break;

      case E2E_P11STATUS_ERROR:
        returnValue = E2E_P_ERROR;
        break;

      case E2E_P11STATUS_REPEATED:
        returnValue = E2E_P_REPEATED;
        break;

      case E2E_P11STATUS_NONEWDATA:
        returnValue = E2E_P_NONEWDATA;
        break;

      case E2E_P11STATUS_WRONGSEQUENCE:
        returnValue = E2E_P_WRONGSEQUENCE;
        break;

      default:
        returnValue = E2E_P_ERROR;
        break;
    }
  }

  return returnValue;
}

#define E2E_STOP_SEC_CODE_ASIL_D
#include "MemMap.h" /*polyspace MISRA2012:20.1 [Justified:Low] "This include directive is necessary for Memory mapping"*/

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
