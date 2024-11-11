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
**  SRC-MODULE: E2E_P01.c                                                     **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR E2E Module                                            **
**                                                                            **
**  PURPOSE   : To implement specification of E2E Profile 1 driver            **
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
** 0.0.2    20-Feb-2020    CuongLX         Remove marcro                      **
** 1.0.1    28-Dec-2021    HiepVT1         Add code to check the validity of  **
**                                         E2E inputs (Length and offset)     **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* Include file for Profile 1 implementation */
#include "E2E.h"

/*******************************************************************************
**                      Internal Function Declarations                        **
*******************************************************************************/

static FUNC(uint8, E2E_CODE) E2E_P01CalculateCRC( \
  P2CONST(E2E_P01ConfigType, AUTOMATIC, E2E_APPL_CONST) ConfigPtr, \
  P2CONST(uint8, AUTOMATIC, E2E_APPL_CONST) DataPtr, \
  VAR(uint8, AUTOMATIC) Counter);

static FUNC(void, E2E_CODE) E2E_P01CheckDeltaCounter( \
  P2CONST(E2E_P01ConfigType, AUTOMATIC, E2E_APPL_CONST) ConfigPtr, \
  P2VAR(E2E_P01CheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr, \
  VAR(uint8, AUTOMATIC) Counter, \
  VAR(uint8, AUTOMATIC) DeltaCounter);

static FUNC(void, E2E_CODE) E2E_P01CheckStatus( \
  P2CONST(E2E_P01ConfigType, AUTOMATIC, E2E_APPL_CONST) ConfigPtr, \
  P2VAR(E2E_P01CheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr, \
  VAR(uint8, AUTOMATIC) Counter, \
  VAR(uint8, AUTOMATIC) DataIDNibble);

static FUNC(Std_ReturnType, AUTOMATIC) E2E_P01CheckParams( \
  P2CONST(E2E_P01ConfigType, AUTOMATIC, E2E_APPL_CONST) ConfigPtr);

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

#define E2E_START_SEC_CODE_ASIL_D /*polyspace MISRA2012:2.5 [Justified:Low] "This macro is necessary for Memory mapping"*/
#include "MemMap.h" /*polyspace MISRA2012:20.1 [Justified:Low] "This include directive is necessary for Memory mapping"*/

/*******************************************************************************
** Function Name        : E2E_P01ProtectInit                                  **
**                                                                            **
** Service ID           : 0x1b                                                **
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
FUNC(Std_ReturnType, E2E_CODE) E2E_P01ProtectInit(
  P2VAR(E2E_P01ProtectStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr)
{
  /* @Trace: SafeE2E_SUD_MF_004 */    
  /* Note: Source code that implement item SafeE2E_SUD_MF_004 */ 

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
** Function Name        : E2E_P01CheckInit                                    **
**                                                                            **
** Service ID           : 0x1c                                                **
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
FUNC(Std_ReturnType, E2E_CODE) E2E_P01CheckInit(
  P2VAR(E2E_P01CheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr)
{
  /* @Trace: SafeE2E_SUD_MF_007 */    
  /* Note: Source code that implement item SafeE2E_SUD_MF_007 */ 

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
    StatePtr->LastValidCounter = 0x00U;
    StatePtr->MaxDeltaCounter = 0x00U;
    StatePtr->WaitForFirstData = TRUE;
    StatePtr->NewDataAvailable = TRUE;
    StatePtr->LostData = 0x00U;
    StatePtr->NoNewOrRepeatedDataCounter = 0x00U;
    StatePtr->SyncCounter = 0x00U;
    StatePtr->Status = E2E_P01STATUS_NONEWDATA;
    
  }/* polyspace-end MISRA2012:D4.14 [Justified:Low] "the pointer is check for not null previous branch"*/

  return returnValue;
}

/*******************************************************************************
** Function Name        : E2E_P01MapStatusToSM                                **
**                                                                            **
** Service ID           : 0x1d                                                **
**                                                                            **
** Description          : This function shall maps the check status of        **
**                        Profile 1 to a generic check status, which can be   **
**                        used by E2E state machine check function. The E2E   **
**                        Profile 1 delivers a more fine-granular status, but **
**                        this is not relevant for the E2E state machine.     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : CheckReturn: Return value of E2E_P01Check function  **
**                        Status: Status determined by E2E_P01Check function  **
**                        ProfileBehavior:                                    **
**                          FALSE: check has the legacy                       **
**                          behavior, before R4.2                             **
**                          TRUE: check behaves like new P4/P5/P6             **
**                          P4/P5/P6 profiles introduced in R4.2              **
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
/* @Trace: SRS_E2E_08527 SRS_E2E_08528 RS_E2E_08540 SRS_BSW_00337*/
FUNC(E2E_PCheckStatusType, AUTOMATIC) E2E_P01MapStatusToSM(
  VAR(Std_ReturnType, AUTOMATIC) CheckReturn,
  VAR(E2E_P01CheckStatusType, AUTOMATIC) Status,
  VAR(boolean, AUTOMATIC) ProfileBehavior)
{
  /* @Trace: SafeE2E_SUD_MF_008 */    
  /* Note: Source code that implement item SafeE2E_SUD_MF_008 */ 

  /* Local variable to store return value */
  VAR(E2E_PCheckStatusType, AUTOMATIC) returnValue;
  
  returnValue = E2E_P_ERROR;

  if (E2E_E_OK == CheckReturn)
  {
    switch (Status)
    {
      case E2E_P01STATUS_OK: /* walk through */
      case E2E_P01STATUS_OKSOMELOST:
        returnValue = E2E_P_OK;
        break;

      case E2E_P01STATUS_WRONGCRC:
        returnValue = E2E_P_ERROR;
        break;

      case E2E_P01STATUS_REPEATED:
        returnValue = E2E_P_REPEATED;
        break;

      case E2E_P01STATUS_NONEWDATA:
        returnValue = E2E_P_NONEWDATA;
        break;

      case E2E_P01STATUS_WRONGSEQUENCE:
        returnValue = E2E_P_WRONGSEQUENCE;
        break;

      case E2E_P01STATUS_INITIAL:
      {
        if (TRUE == ProfileBehavior)
        {
          returnValue = E2E_P_WRONGSEQUENCE;
        }
        else
        {
          returnValue = E2E_P_OK;
        }
      }
      break;

      case E2E_P01STATUS_SYNC:
      {
        if (TRUE == ProfileBehavior)
        {
          returnValue = E2E_P_OK;
        }
        else
        {
          returnValue = E2E_P_WRONGSEQUENCE;
        }
      }
      break;

      default:
        /* Do Nothing */
        break;
    }
  }

  return returnValue;
}

/*******************************************************************************
** Function Name        : E2E_P01Protect                                      **
**                                                                            **
** Service ID           : 0x01                                                **
**                                                                            **
** Description          : Protects the array/buffer to be transmitted using   **
**                        the E2E profile 1. This includes checksum           **
**                        calculation, handling of counter and Data ID.       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : ConfigPtr: Pointer to static configuration          **
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
**                        Function(s) invoked    : E2E_P01CalculateCRC        **
**                                                 E2E_P01CheckParams         **
**                                                                            **
*******************************************************************************/
/* @Trace: SRS_E2E_08527 SRS_E2E_08528 RS_E2E_08540 SRS_BSW_00337
SRS_E2E_08534  SRS_E2E_08529 SRS_BSW_00323 SRS_E2E_08539 RS_E2E_08543 */
FUNC(Std_ReturnType, AUTOMATIC) E2E_P01Protect(
  P2CONST(E2E_P01ConfigType, AUTOMATIC, E2E_APPL_CONST) ConfigPtr,
  P2VAR(E2E_P01ProtectStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
  P2VAR(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr)
{
  /* Local variable to store return value */
  VAR(Std_ReturnType, AUTOMATIC) returnValue;
  /* Local variable to storecounter value */ 
  VAR(uint8, AUTOMATIC) counterProtect;
  /* Local variable to store DataIDNibble value */
  VAR(uint8, AUTOMATIC) configDataIDNibble;
  /* Local variable to store CRC value */
  VAR(uint8, AUTOMATIC) crcValue;

  /* @Trace: SafeE2E_SUD_MF_001 */    
  /* Note: Source code that implement item SafeE2E_SUD_MF_001 */ 

  /* Check for the invalid input parameters */
  /* polyspace-begin MISRA2012:D4.14 [Justified:Low] "the pointer is check for not null previous branch"*/
  if((NULL_PTR == StatePtr) || (NULL_PTR == DataPtr) || (NULL_PTR == ConfigPtr))
  {
    returnValue = E2E_E_INPUTERR_NULL;
  }
  else if((uint16)(ConfigPtr->DataLength / 0x0008U) < ((uint16)(ConfigPtr->CRCOffset / 0x0008U) + 0x0001U))
  {
    returnValue = E2E_E_INPUTERR_WRONG;
  }  
  else
  {
  /* Call function to check input parameters */
    returnValue = E2E_P01CheckParams(ConfigPtr);
  }

  /* @Trace: SafeE2E_SUD_MF_002 */    
  /* Note: Source code that implement item SafeE2E_SUD_MF_002 */ 
  /* Check data input */
  if (E2E_E_OK == returnValue)
  {
    /* Calculate the pointer to Counter Byte based on the counter offset */
    
    counterProtect = DataPtr[ConfigPtr->CounterOffset / 0x0008U];
    

    /* Calculate the pointer to DataIDNibble based on the DataIDNibble offset */
    configDataIDNibble = DataPtr[ConfigPtr->DataIDNibbleOffset / 0x0008U];

    /* Check to find the Offset position of the counter */    
    if (0x0000U == (ConfigPtr->CounterOffset % 0x0008U))
    {
      /* Update the counter value in the lower nibble of the counter byte */  
      counterProtect = (uint8)(counterProtect & E2E_HIGH_NIBBLE_MASK) | \
                (uint8)(StatePtr->Counter & E2E_LOW_NIBBLE_MASK);
      
    }
    else
    {
      /* Update the counter value in the higher nibble of the counter byte */
      counterProtect = (uint8)(counterProtect & E2E_LOW_NIBBLE_MASK) | \
      (uint8)((StatePtr->Counter << 0x04U) & E2E_HIGH_NIBBLE_MASK);
    }
    

    // Write counter value in data
    DataPtr[(ConfigPtr->CounterOffset) / 0x0008U] = counterProtect;

    /* 
    *  Write the low nibble of high byte of Data ID - only for 
    *  E2E_P01_DATAID_NIBBLE 
    */
    if (E2E_P01_DATAID_NIBBLE == ConfigPtr->DataIDMode)
    {
      if (0x00U == (ConfigPtr->DataIDNibbleOffset % 0x0008U))
      {
        configDataIDNibble = 
          (uint8)(configDataIDNibble & E2E_HIGH_NIBBLE_MASK) | \
          (uint8)((ConfigPtr->DataID >> 0x0008U) & E2E_LOW_NIBBLE_MASK);
      }
      else
      {
        configDataIDNibble = 
          (uint8)(configDataIDNibble & E2E_LOW_NIBBLE_MASK) | \
          (uint8)((ConfigPtr->DataID >> 0x04U) & E2E_HIGH_NIBBLE_MASK);
      }

      /* Write DataIDNibble value in data */
      DataPtr[(ConfigPtr->DataIDNibbleOffset) / 0x0008U] = configDataIDNibble;
    }

    /* Calculate CRC over Data ID and Data */
    crcValue = E2E_P01CalculateCRC(ConfigPtr, \
                (P2CONST(uint8, AUTOMATIC, E2E_APPL_CONST)) DataPtr, \
                StatePtr->Counter);

    /* Write the Crc to data at configured location */
    DataPtr[(ConfigPtr->CRCOffset) / 0x0008U] = crcValue;

    /* Increment the counter modulo 15 */
    StatePtr->Counter = ((StatePtr->Counter + 0x01U) % E2E_P01_CNT_LIMIT);
  }/* polyspace-end MISRA2012:D4.14 [Justified:Low] "the pointer is check for not null previous branch"*/

  return returnValue;
}

/*******************************************************************************
** Function Name        : E2E_P01Check                                        **
**                                                                            **
** Service ID           : 0x02                                                **
**                                                                            **
** Description          : Checks the Data received using the E2E profile 1    **
**                        This includes checksum calculation, handling of     **
**                        counter and Data ID.                                **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : ConfigPtr: Pointer to static configuration          **
**                        DataPtr: Pointer to received data                   **
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
**                        Function(s) invoked    : E2E_P01CheckParams         **
**                                                 E2E_P01CalculateCRC        **                   
**                                                 E2E_P01CheckStatus         **
**                                                                            **
*******************************************************************************/
/* @Trace: SRS_E2E_08527 SRS_E2E_08528 RS_E2E_08540 SRS_BSW_00337
SRS_E2E_08534  SRS_E2E_08529 SRS_BSW_00323 SRS_E2E_08539 RS_E2E_08543 */
FUNC(Std_ReturnType, AUTOMATIC) E2E_P01Check(
  P2CONST(E2E_P01ConfigType, AUTOMATIC, E2E_APPL_CONST) ConfigPtr,
  P2VAR(E2E_P01CheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
  P2CONST(uint8, AUTOMATIC, E2E_APPL_CONST) DataPtr)
{


  /* Local variable to store return value */
  VAR(Std_ReturnType, AUTOMATIC) returnValue;
  /* Local variable to store counter offset value */
  VAR(uint16, AUTOMATIC) counterOffset;
  /* Local variable to store DataIDNibble offset value */
  VAR(uint16, AUTOMATIC) dataIDNibbleOffset;
  /* Local variable to store received counter value */
  VAR(uint8, AUTOMATIC) receivedCnt;
  /* Local variable to store received crc value */
  VAR(uint8, AUTOMATIC) receivedCrc;
  /* Local variable to store received DataIDNibble value */
  VAR(uint8, AUTOMATIC) receivedDtIdNbl;
  /* Local variable to store calculated CRC value */
  VAR(uint8, AUTOMATIC) calculatedCRC;

  receivedDtIdNbl = 0U;

  /* @Trace: SafeE2E_SUD_MF_005 */    
  /* Note: Source code that implement item SafeE2E_SUD_MF_005 */ 
  /* polyspace-begin MISRA2012:D4.14 [Justified:Low] "the pointer is check for not null previous branch"*/
  if((NULL_PTR == StatePtr) || (NULL_PTR == DataPtr) || (NULL_PTR == ConfigPtr))
  {
    returnValue = E2E_E_INPUTERR_NULL;
  }
  else if((uint16)(ConfigPtr->DataLength / 0x0008U) < ((uint16)(ConfigPtr->CRCOffset / 0x0008U) + 0x0001U))
  {
    returnValue = E2E_E_INPUTERR_WRONG;
  }  
  else
  {
    /* Call function to check input parameters */
    returnValue = E2E_P01CheckParams(ConfigPtr);
  }
  /* @Trace: SafeE2E_SUD_MF_006 */    
  /* Note: Source code that implement item SafeE2E_SUD_MF_006 */ 
  if (E2E_E_OK == returnValue)
  {
    /* 
    * Maximum allowed delta counter between previous and current counter 
    * is incremented 
    */
    StatePtr->MaxDeltaCounter++;
    
    if (E2E_P01_CNT_MAX < StatePtr->MaxDeltaCounter)
    {
      /* If MaxDeltaCounter counter value exceeds 0x0E */
      StatePtr->MaxDeltaCounter = E2E_P01_CNT_MAX;
    }
    /* Check for the availability of New Data */ 
    if (TRUE == StatePtr->NewDataAvailable)
    {      
      counterOffset = (ConfigPtr->CounterOffset) / 0x0008U;
      
      if (0x0000U == ((ConfigPtr->CounterOffset) % 0x0008U))
      {
        /* Get the counter value from the lower nibble of the counter byte */
        receivedCnt = DataPtr[counterOffset] & E2E_LOW_NIBBLE_MASK;
      } 
      else
      {
        /* Get the counter value from the higher nibble of the counter byte */
        receivedCnt = (DataPtr[counterOffset] >> 0x04U) & E2E_LOW_NIBBLE_MASK;    
      }

      dataIDNibbleOffset = ConfigPtr->DataIDNibbleOffset / 0x0008U;

      /* Check the counter */
      if (E2E_P01_CNT_LIMIT > receivedCnt)
      {
        /* Get Crc value from the crc byte */
        receivedCrc = DataPtr[ConfigPtr->CRCOffset / 0x0008U];

        /* Read the low nibble of high byte of Data ID */
        if (E2E_P01_DATAID_NIBBLE == ConfigPtr->DataIDMode)
        {
          if (0x00U == (ConfigPtr->DataIDNibbleOffset % 0x0008U))
          {
            receivedDtIdNbl = DataPtr[dataIDNibbleOffset] & E2E_LOW_NIBBLE_MASK;
          }
          else
          {
            receivedDtIdNbl = \
              (DataPtr[dataIDNibbleOffset] >> 0x04U) & E2E_LOW_NIBBLE_MASK;
          }
        }

        /* Calculate CRC over Data ID and Data */
        calculatedCRC = 
          E2E_P01CalculateCRC(ConfigPtr, DataPtr, receivedCnt);

        if (calculatedCRC == receivedCrc)
        {
          /* Call function to check status  */
          E2E_P01CheckStatus(ConfigPtr, StatePtr, receivedCnt, receivedDtIdNbl);
        }
        else
        {
          StatePtr->Status = E2E_P01STATUS_WRONGCRC;
        }
      }
      else
      {
        returnValue = E2E_E_INPUTERR_WRONG;
      }
    }
    else
    {
      if (E2E_P01_CNT_MAX > StatePtr->NoNewOrRepeatedDataCounter)
      {
        StatePtr->NoNewOrRepeatedDataCounter++;
      }

      StatePtr->Status = E2E_P01STATUS_NONEWDATA;
    }
  }/* polyspace-end MISRA2012:D4.14 [Justified:Low] "the pointer is check for not null previous branch"*/
  return returnValue;
}

/*******************************************************************************
** Function Name        : E2E_P01CheckParams                                  **
**                                                                            **
** Service ID           : None                                                    **
**                                                                            **
** Description          : Verify data of ConfigPtr parameters of profile 01   **
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
static FUNC(Std_ReturnType, AUTOMATIC) E2E_P01CheckParams(
  P2CONST(E2E_P01ConfigType, AUTOMATIC, E2E_APPL_CONST) ConfigPtr)
{
  /* @Trace: SafeE2E_SUD_MF_011 */    
  /* Note: Source code that implement item SafeE2E_SUD_MF_011 */ 

  /* Local variable to store result value */
  VAR(Std_ReturnType, AUTOMATIC) returnValue;

  /* Check for the ranges of input parameters */
  /* polyspace-begin MISRA2012:D4.14 [Justified:Low] "the pointer is check for not null previous branch"*/
  if ((E2E_P01_MAX_DATA_LENGTH_LIMIT < ConfigPtr->DataLength) || \
      (E2E_P01_CNT_MAX < ConfigPtr->MaxDeltaCounterInit) || \
      (ConfigPtr->CounterOffset > (ConfigPtr->DataLength - 0x04U)) || \
      (ConfigPtr->CRCOffset > (ConfigPtr->DataLength - 0x08U)))
  {
    returnValue = E2E_E_INPUTERR_WRONG;
  }
  /* Check for alignment of input parameters */
  else if ((0x0000U != ((ConfigPtr->CRCOffset) % 0x0008U)) || \
       (0x0000U != ((ConfigPtr->CounterOffset) % 0x0004U)) || \
       (0x0000U != ((ConfigPtr->DataLength) % 0x0008U)))
  {
    returnValue = E2E_E_INPUTERR_WRONG;
  }
  /* Check whether high byte is used when DataIDMode is E2E_P01_DATAID_LOW */
  else if ((E2E_P01_DATAID_LOW == (ConfigPtr->DataIDMode)) && \
       (E2E_P01_DATAID_LOW_LIMIT < (ConfigPtr->DataID)))
  {
    returnValue = E2E_E_INPUTERR_WRONG;
  }
  else
  {
    returnValue = E2E_E_OK;
  }
  /* polyspace-end MISRA2012:D4.14 [Justified:Low] "the pointer is check for not null previous branch"*/
  
  return returnValue;
}

/*******************************************************************************
** Function Name        : E2E_P01CheckStatus                                  **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : This function check status of received Data.        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : Counter: Counter receiver received                  **
**                        ConfigPtr: Pointer to static configuration          **
**                                                                            **
** InOut Parameters     : StatePtr: Pointer to port/data communication state  **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return value         : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                                                                            **
**                        Function(s) invoked    : E2E_P01CheckDeltaCounter   **
*******************************************************************************/
/* @Trace: SRS_E2E_08527 SRS_E2E_08528 RS_E2E_08540 SRS_BSW_00337
SRS_E2E_08534  SRS_E2E_08529 SRS_BSW_00323 */
static FUNC(void, E2E_CODE) E2E_P01CheckStatus(
  P2CONST(E2E_P01ConfigType, AUTOMATIC, E2E_APPL_CONST) ConfigPtr,
  P2VAR(E2E_P01CheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
  VAR(uint8, AUTOMATIC) Counter,
  VAR(uint8, AUTOMATIC) DataIDNibble)
{
  /* @Trace: SafeE2E_SUD_MF_012 */    
  /* Note: Source code that implement item SafeE2E_SUD_MF_012 */ 

  /* Local variable to store delta counter */
  VAR(uint8, AUTOMATIC) deltaCnt;
  
  /* Check received nibble is identical to the one in DataID */
  if ((E2E_P01_DATAID_NIBBLE == ConfigPtr->DataIDMode)
      && (DataIDNibble != (ConfigPtr->DataID >> 0x0008U)))
  {
    StatePtr->Status = E2E_P01STATUS_WRONGCRC;
  }
  else
  {
    /* Check any correct data has already be received */
    if (TRUE == StatePtr->WaitForFirstData)
    {
      StatePtr->WaitForFirstData = FALSE;
      StatePtr->MaxDeltaCounter = ConfigPtr->MaxDeltaCounterInit;
      StatePtr->LastValidCounter = Counter;
      StatePtr->Status = E2E_P01STATUS_INITIAL;
    }
    else
    {
      /* Compute the delta, taking into account the overflow */
      if (Counter >= StatePtr->LastValidCounter)
      {
        deltaCnt = Counter - StatePtr->LastValidCounter;
      }
      else
      {
        deltaCnt = E2E_P01_CNT_LIMIT + Counter - StatePtr->LastValidCounter;
      }

      /* 
      * Call function: the previous and the current data have correct Crc, 
      * verify the counter */
      E2E_P01CheckDeltaCounter(ConfigPtr, StatePtr, Counter, deltaCnt);
    }
  }
}

/*******************************************************************************
** Function Name        : E2E_P01CheckDeltaCounter                            **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : This function check status of received Data         **
**                        by counter                                          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : ConfigPtr: Pointer to static configuration          **
**                      : ReceivedCounter: received counter                   **
**                                                                            **
** InOut Parameters     : StatePtr: Pointer to port/data communication state  **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return value         : None                                                **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                                                                            **
**                        Function(s) invoked    : None                       **
*******************************************************************************/
/* @Trace: SRS_E2E_08534  SRS_E2E_08529 SRS_BSW_00323*/
static FUNC(void, E2E_CODE) E2E_P01CheckDeltaCounter(
  P2CONST(E2E_P01ConfigType, AUTOMATIC, E2E_APPL_CONST) ConfigPtr,
  P2VAR(E2E_P01CheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
  VAR(uint8, AUTOMATIC) Counter, 
  VAR(uint8, AUTOMATIC) DeltaCounter)
{
  /* @Trace: SafeE2E_SUD_MF_010 */    
  /* Note: Source code that implement item SafeE2E_SUD_MF_010 */ 

  /* If there are no difference in counter value then the data is repeated */
  if (0x00U == DeltaCounter)
  {
    /* Increment NoNewOrRepeatedDataCounter */
    if (E2E_P01_CNT_MAX > StatePtr->NoNewOrRepeatedDataCounter)
    {
      StatePtr->NoNewOrRepeatedDataCounter++;
    }

    StatePtr->Status = E2E_P01STATUS_REPEATED;
  }
  /* If the difference is one then a new data is avaialble */
  else if (0x01U == DeltaCounter)
  {
    /* Reset the Delta counter */
    StatePtr->MaxDeltaCounter = ConfigPtr->MaxDeltaCounterInit;
    StatePtr->LastValidCounter = Counter;
    /* Reset the Lost data */
    StatePtr->LostData = 0x00U;

    if (StatePtr->NoNewOrRepeatedDataCounter <= ConfigPtr->MaxNoNewOrRepeatedData)
    {
      StatePtr->NoNewOrRepeatedDataCounter = 0x00U;

      if (0x00U < StatePtr->SyncCounter)
      {
        StatePtr->SyncCounter--;
        StatePtr->Status = E2E_P01STATUS_SYNC;
      }
      else
      {
        StatePtr->Status = E2E_P01STATUS_OK;
      }
    }
    else
    {
      StatePtr->NoNewOrRepeatedDataCounter = 0x00U;
      StatePtr->SyncCounter = ConfigPtr->SyncCounterInit;
      StatePtr->Status = E2E_P01STATUS_SYNC;
    }
  }
  /* If the difference is more than ONE then some data is lost */
  else if (DeltaCounter <= StatePtr->MaxDeltaCounter)
  {
    /* Reset the Delta counter */
    StatePtr->MaxDeltaCounter = ConfigPtr->MaxDeltaCounterInit;
    /* Update the last valid counter with the current counter value */
    StatePtr->LastValidCounter = Counter;
    /* Update the lost data count */
    StatePtr->LostData = DeltaCounter - 0x01U;

    if (StatePtr->NoNewOrRepeatedDataCounter <= ConfigPtr->MaxNoNewOrRepeatedData)
    {
      StatePtr->NoNewOrRepeatedDataCounter = 0x00U;

      if (0x00U < StatePtr->SyncCounter)
      {
        StatePtr->SyncCounter--;
        StatePtr->Status = E2E_P01STATUS_SYNC;
      }
      else
      {
        StatePtr->Status = E2E_P01STATUS_OKSOMELOST;
      }
    }
    else
    {
      StatePtr->NoNewOrRepeatedDataCounter = 0x00U;
      StatePtr->SyncCounter = ConfigPtr->SyncCounterInit;
      StatePtr->Status = E2E_P01STATUS_SYNC;
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
      StatePtr->LastValidCounter = Counter;
    }

    StatePtr->Status = E2E_P01STATUS_WRONGSEQUENCE;
  }
}
/*******************************************************************************
** Function Name        : E2E_P01CalculateCRC                                 **
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
**                        Function(s) invoked    : Crc_CalculateCRC8          **
*******************************************************************************/
/* @Trace: SRS_E2E_08534  SRS_E2E_08529 SRS_BSW_00323 SRS_E2E_08539 RS_E2E_08543*/
static FUNC(uint8, E2E_CODE) E2E_P01CalculateCRC(
  P2CONST(E2E_P01ConfigType, AUTOMATIC, E2E_APPL_CONST) ConfigPtr,
  P2CONST(uint8, AUTOMATIC, E2E_APPL_CONST) DataPtr,
  VAR(uint8, AUTOMATIC) Counter)
{
  /* @Trace: SafeE2E_SUD_MF_009 */    
  /* Note: Source code that implement item SafeE2E_SUD_MF_009 */ 

  /* Local variable to  CRC value */
  VAR(uint8, AUTOMATIC) crcValue;
  /* Local variable to store CRC Data */
  VAR(uint8, AUTOMATIC) crcData;
  /* Local variable to store CRC byte postion */
  VAR(uint8, AUTOMATIC) crcBytePos;
  /* Local variable to store length data after Crc byte */
  VAR(uint16, AUTOMATIC) dataLengthAfterCrc;
  /* Local variable to store length data  */
  VAR(uint16, AUTOMATIC) dataLength;
  
  crcValue = E2E_P01_CRC_START_VAL;
  
  switch (ConfigPtr->DataIDMode)
  {
    case E2E_P01_DATAID_BOTH:

      /* Take LSB Byte for CRC calculation */
      crcData = (uint8)((ConfigPtr->DataID) & E2E_LOW_BYTE_MASK);
      crcValue = Crc_CalculateCRC8( \
                    (P2CONST(uint8, AUTOMATIC, E2E_APPL_CONST)) &crcData, \
                    0x00000001UL, E2E_P01_CRC_START_VAL, FALSE);

      /* Take MSB Byte for CRC calculation */
      crcData = (uint8)(((ConfigPtr->DataID) >> 0x0008U) & E2E_LOW_BYTE_MASK);
      crcValue = Crc_CalculateCRC8( \
                  (P2CONST(uint8, AUTOMATIC, E2E_APPL_CONST)) &crcData, \
                  0x00000001UL, crcValue, FALSE);

      break;

    case E2E_P01_DATAID_LOW:

      /* Take LSB Byte for CRC calculation */
      crcData = (uint8)((ConfigPtr->DataID) & E2E_LOW_BYTE_MASK);

      /* Calculate CRC for the LSB Byte */
      crcValue = Crc_CalculateCRC8( \
                    (P2CONST(uint8, AUTOMATIC, E2E_APPL_CONST)) &crcData, \
                    0x00000001UL, E2E_P01_CRC_START_VAL, FALSE);

      break;

    case E2E_P01_DATAID_ALT:

      if (0x00U == (Counter % 0x02U))
      {
        /* Take LSB Byte for CRC calculation */
        crcData = (uint8)((ConfigPtr->DataID) & E2E_LOW_BYTE_MASK);

        /* Calculate CRC for the LSB Byte */
        crcValue = Crc_CalculateCRC8( \
                    (P2CONST(uint8, AUTOMATIC, E2E_APPL_CONST)) &crcData, \
                    0x00000001UL, E2E_P01_CRC_START_VAL, FALSE);
      } 
      else
      {
        /* Take MSB Byte for CRC calculation */
        crcData = (uint8)(((ConfigPtr->DataID) >> 0x0008U) & E2E_LOW_BYTE_MASK);

        /* Calculate CRC for the MSB Byte */
        crcValue = Crc_CalculateCRC8( \
                    (P2CONST(uint8, AUTOMATIC, E2E_APPL_CONST)) &crcData, \
                    0x00000001UL, E2E_P01_CRC_START_VAL, FALSE);
      } /* End of else */

      break;

    case E2E_P01_DATAID_NIBBLE:

      /* Take LSB Byte for CRC calculation */
      crcData = (uint8)((ConfigPtr->DataID) & E2E_LOW_BYTE_MASK);
      crcValue = Crc_CalculateCRC8( \
                  (P2CONST(uint8, AUTOMATIC, E2E_APPL_CONST)) &crcData, \
                  0x00000001UL, E2E_P01_CRC_START_VAL, FALSE);

      /* Make 0x00 for CRC calculation */
      crcData = 0x00U;

      /* Take MSB Byte for CRC calculation */
      crcValue = Crc_CalculateCRC8( \
                    (P2CONST(uint8, AUTOMATIC, E2E_APPL_CONST)) &crcData, \
                    0x00000001UL, crcValue, FALSE);

      break;

    default:
      /*Do Nothing*/
      break;
  }

  crcBytePos = (uint8)(ConfigPtr->CRCOffset / 0x0008U);
  /* Check if CRC Byte Position is not ZERO */
  if (0x01U <= crcBytePos)
  {
    /* Calculate the CRC for the Data Byte before the CRC Byte */
    crcValue = Crc_CalculateCRC8(DataPtr, (uint32)crcBytePos, crcValue, FALSE);
  }

  dataLength = ConfigPtr->DataLength / 0x0008U;

  /* Check if the CRC byte postion is the last byte in the Data Stream */
  if ((uint8)(dataLength) > (crcBytePos + 0x01U))
  {
    dataLengthAfterCrc = (uint16)(dataLength) - (uint16)crcBytePos - 
                            0x0001U;
    /* Calculate the CRC for the Data Byte after the CRC Byte */
    crcValue = Crc_CalculateCRC8( \
      (P2CONST(uint8, AUTOMATIC, E2E_APPL_CONST)) & DataPtr[crcBytePos + 0x01U],  
      (uint32)dataLengthAfterCrc, crcValue, FALSE);
  }

  crcValue = crcValue ^ E2E_P01_CRC_XOR_VAL;

  return (crcValue);
}

#define E2E_STOP_SEC_CODE_ASIL_D
#include "MemMap.h" /*polyspace MISRA2012:20.1 [Justified:Low] "This include directive is necessary for Memory mapping"*/

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
