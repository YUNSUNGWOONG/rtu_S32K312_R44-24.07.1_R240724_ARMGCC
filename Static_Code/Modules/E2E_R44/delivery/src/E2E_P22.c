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
**  SRC-MODULE: E2E_P22.c                                                     **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR E2E Module                                            **
**                                                                            **
**  PURPOSE   : To implement specification of E2E Profile 22 driver           **
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
** 0.0.1    10-Sep-2019    TruongBX        Initial Version                    **
** 0.0.2    20-Feb-2020    CuongLX         Remove marcro                      **
** 0.0.3    01-Oct-2020    MinhNQ26        Fix code review comments (#15965)  **
** 1.0.1    28-Dec-2021    HiepVT1         Add code to check the validity of  **
**                                         E2E inputs (Length and offset)     **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "E2E.h"

/*******************************************************************************
**                      Internal Function Declarations                        **
*******************************************************************************/
static FUNC(uint8, E2E_CODE) E2E_P22CalculateCRC(
  P2CONST(E2E_P22ConfigType, AUTOMATIC, E2E_APPL_CONST) ConfigPtr,
  P2CONST(uint8, AUTOMATIC, E2E_APPL_CONST) DataPtr,
  VAR(uint16, AUTOMATIC) Length,
  VAR(uint8, AUTOMATIC) Counter);

static FUNC(void, E2E_CODE) E2E_P22CheckStatus(
  VAR(uint8, AUTOMATIC) ReceivedCRC,
  VAR(uint8, AUTOMATIC) ComputedCRC,
  VAR(uint8, AUTOMATIC) ReceivedCounter,
  P2CONST(E2E_P22ConfigType, AUTOMATIC, E2E_APPL_CONST) ConfigPtr,
  P2VAR(E2E_P22CheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr );

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define E2E_START_SEC_CODE_ASIL_D /*polyspace MISRA2012:2.5 [Justified:Low] "This macro is necessary for Memory mapping"*/
#include "MemMap.h"  /*polyspace MISRA2012:20.1 [Justified:Low] "This include directive is necessary for Memory mapping"*/

/*******************************************************************************
** Function Name        : E2E_P22CalculateCRC                                 **
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
**                        Function(s) invoked    : Crc_CalculateCRC32P4       **
*******************************************************************************/
/* @Trace: SRS_E2E_08534  SRS_E2E_08529 SRS_BSW_00323 SRS_E2E_08539 RS_E2E_08543 */

static FUNC(uint8, E2E_CODE) E2E_P22CalculateCRC(
  P2CONST(E2E_P22ConfigType, AUTOMATIC, E2E_APPL_CONST) ConfigPtr,
  P2CONST(uint8, AUTOMATIC, E2E_APPL_CONST) DataPtr,
  VAR(uint16, AUTOMATIC) Length,
  VAR(uint8, AUTOMATIC) Counter)
{
  /* @Trace: SafeE2E_SUD_MF_709 */    
  /* Note: Source code that implement item SafeE2E_SUD_MF_709 */   
   
  /* Local variable to store computed crc value */
  VAR(uint8, AUTOMATIC)	computedCRCValue = 0x00U;
  /* Local variable to store offset value */
  VAR(uint16, AUTOMATIC) offset;
  /*Length for calculate CRC */
  VAR(uint16, AUTOMATIC) LengthForCRC = 0x0000U;

  offset = ConfigPtr->Offset / 0x08U;
  /* calculate CRC when CRC offset larger than 0 */
  if (0x00U < ConfigPtr->Offset)
  {
    computedCRCValue = \
    Crc_CalculateCRC8H2F(&DataPtr[0x00U], (uint32)offset, E2E_P22_CRC_INIT_VALUE, TRUE);
    LengthForCRC= Length - offset - 0x0001U;
      /* The validity of LengthForCRC has been checked before. Checking again just only for polyspace */
	computedCRCValue = \
	  Crc_CalculateCRC8H2F(&DataPtr[offset + 0x0001U], \
	  (uint32)LengthForCRC, computedCRCValue, FALSE);
    
  }
  /* calculate CRC when CRC offset less than or equal 0 */
  else
  {
    /* The validity of LengthForCRC has been checked before. Checking again just only for polyspace */
    LengthForCRC = Length - 0x0001U;
    
    computedCRCValue = \
      Crc_CalculateCRC8H2F(&DataPtr[0x01U], (uint32)LengthForCRC, \
      E2E_P22_CRC_INIT_VALUE, TRUE);      
  }
  computedCRCValue = \
    Crc_CalculateCRC8H2F(&ConfigPtr->DataIDList[Counter], (uint32)0x0001U, \
    computedCRCValue, FALSE);

  return computedCRCValue;
}

/*******************************************************************************
** Function Name        : E2E_P22CheckStatus                                  **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : This function check status of received data.        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : ConfigPtr,ReceivedCounter,                          **
**                        RecievedCRC, ComputedCRC, ReceivedDataID,           **
**                        Length ,ReceivedLength                              **
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

static FUNC(void, E2E_CODE) E2E_P22CheckStatus(
  VAR(uint8, AUTOMATIC) ReceivedCRC,
  VAR(uint8, AUTOMATIC) ComputedCRC,
  VAR(uint8, AUTOMATIC) ReceivedCounter,
  P2CONST(E2E_P22ConfigType, AUTOMATIC, E2E_APPL_CONST) ConfigPtr,
  P2VAR(E2E_P22CheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr )
{
  /* @Trace: SafeE2E_SUD_MF_708 */    
  /* Note: Source code that implement item SafeE2E_SUD_MF_708 */   
   
  /* Local variable to store delta counter value */
  VAR(uint8, AUTOMATIC) deltaCounter;
  /* polyspace-begin MISRA2012:D4.14 MISRA2012:D4.1 MISRA2012:18.1 RTE:IDP [Justified:Low] "the pointer is validated in previous branch"*/
  if (ReceivedCRC == ComputedCRC)
  {
    
    if (ReceivedCounter >= StatePtr->Counter)
    {
      deltaCounter = ReceivedCounter - StatePtr->Counter;
    }
    else
    {
      deltaCounter = \
        (uint8)(E2E_P22_CNT_MAX + ReceivedCounter - StatePtr->Counter + 0x01U);
    }
    if (deltaCounter <= ConfigPtr->MaxDeltaCounter)
    {
      StatePtr->Status = E2E_P22STATUS_OKSOMELOST;

      if (deltaCounter == (uint8)0x00U)
      {
        StatePtr->Status = E2E_P22STATUS_REPEATED;
      }
        
      if (deltaCounter == (uint8)0x01U)
      {
        StatePtr->Status = E2E_P22STATUS_OK;
      }
    }
    else
    {
      StatePtr->Status = E2E_P22STATUS_WRONGSEQUENCE;
    }
    StatePtr->Counter = ReceivedCounter;
  }
  else
  {
    StatePtr->Status = E2E_P22STATUS_ERROR;
  }/* polyspace-end MISRA2012:D4.14 MISRA2012:D4.1 MISRA2012:18.1 RTE:IDP [Justified:Low] "the pointer is validated in previous branch"*/
}

/*******************************************************************************
**                      Interface Function Declarations                       **
*******************************************************************************/

/*******************************************************************************
** Function Name        : E2E_P22ProtectInit                                  **
**                                                                            **
** Service ID           : 0x41                                                **
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

FUNC(Std_ReturnType, E2E_CODE) E2E_P22ProtectInit (
  P2VAR(E2E_P22ProtectStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr)
{
  /* @Trace: SafeE2E_SUD_MF_705 */    
  /* Note: Source code that implement item SafeE2E_SUD_MF_705 */   
   
  /* Local variable to store return value */
  VAR(Std_ReturnType, AUTOMATIC)	retValue;

  retValue = E2E_E_INPUTERR_NULL;
  /*Initial State structure when StatePtr not null*/
  if (NULL_PTR != StatePtr)
  {
    /* polyspace-begin MISRA2012:D4.14 MISRA2012:D4.1 MISRA2012:18.1 RTE:IDP [Justified:Low] "the pointer is validated in previous branch"*/
    StatePtr->Counter = E2E_P22_CNT_ZERO;
    /* polyspace-end MISRA2012:D4.14 MISRA2012:D4.1 MISRA2012:18.1 RTE:IDP [Justified:Low] "the pointer is validated in previous branch"*/
    retValue = E2E_E_OK;
  }

  return retValue;
}

/*******************************************************************************
** Function Name        : E2E_P22Protect                                      **
**                                                                            **
** Service ID           : 0x40                                                **
**                                                                            **
** Description          : This function shall write counter in Data,and       **
**                        finally compute CRC over DataID and Data and write  **
**                        CRC in data. And then it shall increment the        **
**                        counter.                                            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : ConfigPtr,Length                                    **
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
**                        Function(s) invoked    : E2E_P22CalculateCRC        **
*******************************************************************************/
/* @Trace: SRS_E2E_08527 SRS_E2E_08528 RS_E2E_08540 SRS_BSW_00337
SRS_E2E_08534  SRS_E2E_08529 SRS_BSW_00323 SRS_E2E_08539 RS_E2E_08543*/

FUNC(Std_ReturnType, E2E_CODE) E2E_P22Protect (
  P2CONST(E2E_P22ConfigType, AUTOMATIC, E2E_APPL_CONST) ConfigPtr,
  P2VAR(E2E_P22ProtectStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
  P2VAR(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr,
  VAR(uint16, AUTOMATIC) Length)
{
  /* Local variable to store return value */
  VAR(Std_ReturnType, AUTOMATIC) retValue;
  /* Local variable to store calculated crc value */
  VAR(uint8, AUTOMATIC)	calculateCRC;
  /* Local variable to store nibble byte of counter value */
  VAR(uint8, AUTOMATIC)	counterByteNibble;

  retValue = E2E_E_INPUTERR_NULL;
  /* Check inputs exit*/
  /* polyspace-begin MISRA2012:D4.14 MISRA2012:D4.1 MISRA2012:18.1 RTE:IDP [Justified:Low] "the pointer is validated in previous branch"*/
  if ((NULL_PTR != ConfigPtr) && (NULL_PTR != StatePtr) && (NULL_PTR != DataPtr))
  {
    /* check correct for value of Length data 
      1. The offset shall be a multiple of 8 and 0 <= Offset <= DataLength-(2*8).
    */
    if ((Length == (ConfigPtr->DataLength / 0x08U)) && \
        (0x00U == (ConfigPtr->Offset % 0x08U)) && \
        (ConfigPtr->DataLength >= E2E_P22_MIN_DATA_LENGTH_LIMIT) && \
        (ConfigPtr->Offset <= (ConfigPtr->DataLength - E2E_P22_MIN_DATA_LENGTH_LIMIT)))
    {
      /* @Trace: SafeE2E_SUD_MF_701 */    
      /* Note: Source code that implement item SafeE2E_SUD_MF_701 */
      /*Get Byte of Data is used to write 4 bit of Counter*/
      counterByteNibble = \
        (uint8)(DataPtr[(ConfigPtr->Offset / 0x08U) + E2E_P22_LEN_OFS_BYTE_ONE] & E2E_HIGH_NIBBLE_MASK);

      /* write lower 4 bit of Counter to Data at location Data[Config->Offset +8] in bit */
      DataPtr[(ConfigPtr->Offset / 0x08U) + E2E_P22_LEN_OFS_BYTE_ONE] = \
        (uint8)((StatePtr->Counter & E2E_LOW_NIBBLE_MASK) | counterByteNibble);

      /*Calculate CRC by call to function E2E_P22CalculateCRC*/
      calculateCRC = \
        E2E_P22CalculateCRC(ConfigPtr, (P2CONST(uint8, AUTOMATIC, E2E_APPL_CONST))DataPtr, Length, StatePtr->Counter);

      /*Write calculate CRC to Data in first byte of Data (at localtion Data[Config->Offset/8])*/
      DataPtr[ConfigPtr->Offset / 0x08U] = (uint8)calculateCRC;
      /*Increase Counter after finish protect Data process*/
      StatePtr->Counter = (StatePtr->Counter + 0x01U) % E2E_P22_CNT_MAX_VL_CYCLE;
      retValue = E2E_E_OK;
    }
    else
    {
      /* @Trace: SafeE2E_SUD_MF_702 */    
      /* Note: Source code that implement item SafeE2E_SUD_MF_702 */
      retValue = E2E_E_INPUTERR_WRONG;
    }
  }/* polyspace-end MISRA2012:D4.14 MISRA2012:D4.1 MISRA2012:18.1 RTE:IDP [Justified:Low] "the pointer is validated in previous branch"*/
  /* @Trace: SafeE2E_SUD_MF_700 */    
  /* Note: Source code that implement item SafeE2E_SUD_MF_700 */

  return retValue;
}

/*******************************************************************************
** Function Name        : E2E_P22CheckInit                                    **
**                                                                            **
** Service ID           : 0x3e                                                **
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

FUNC(Std_ReturnType, E2E_CODE) E2E_P22CheckInit (
  P2VAR(E2E_P22CheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr)
{
  /* @Trace: SafeE2E_SUD_MF_706 */    
  /* Note: Source code that implement item SafeE2E_SUD_MF_706 */   
   
  /* Local variable to store return value */
  VAR(Std_ReturnType, AUTOMATIC) retValue;

  retValue = E2E_E_INPUTERR_NULL;
  /*Initial State structure when StatePtr not NULL_PTR*/
  if (NULL_PTR != StatePtr)
  {
    /* polyspace-begin MISRA2012:D4.14 MISRA2012:D4.1 MISRA2012:18.1 RTE:IDP [Justified:Low] "the pointer is validated in previous branch"*/
    StatePtr->Counter = E2E_P22_CNT_MAX;
    StatePtr->Status = E2E_P22STATUS_ERROR;
    /* polyspace-end MISRA2012:D4.14 MISRA2012:D4.1 MISRA2012:18.1 RTE:IDP [Justified:Low] "the pointer is validated in previous branch"*/
    retValue = E2E_E_OK;
  }

  return retValue;
}

/*******************************************************************************
** Function Name        : E2E_P22Check                                        **
**                                                                            **
** Service ID           : 0x3d                                                **
**                                                                            **
** Description          : This function shall check counter, CRC over         **
**                        received data and determine the check status.       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : ConfigPtr, DataPtr                                  **
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
**                        Function(s) invoked    : E2E_P22CalculateCRC        **
**                                                 E2E_P22CheckStatus         **
*******************************************************************************/
/* @Trace: SRS_E2E_08527 SRS_E2E_08528 RS_E2E_08540 SRS_BSW_00337
SRS_E2E_08534  SRS_E2E_08529 SRS_BSW_00323 SRS_E2E_08539 RS_E2E_08543 */

FUNC(Std_ReturnType, E2E_CODE) E2E_P22Check (
  P2CONST(E2E_P22ConfigType, AUTOMATIC, E2E_APPL_CONST) ConfigPtr,
  P2VAR(E2E_P22CheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
  P2CONST(uint8, AUTOMATIC, E2E_APPL_CONST) DataPtr,
  VAR(uint16, AUTOMATIC) Length)
{
  /* Local variable to store return value */
  VAR(Std_ReturnType, AUTOMATIC) retValue;
  /* Local variable to store received counter value */
  VAR(uint8, AUTOMATIC) receivedCounterValue;
  /* Local variable to store received crc value */
  VAR(uint8, AUTOMATIC) receivedCRCValue;
  /* Local variable to store calculated crc value */
  VAR(uint8, AUTOMATIC) calculateCRC;

  retValue = E2E_E_INPUTERR_NULL;
  /* polyspace-begin MISRA2012:D4.14 MISRA2012:D4.1 MISRA2012:18.1 RTE:IDP [Justified:Low] "the pointer is validated in previous branch"*/
  if ((NULL_PTR != ConfigPtr) && (NULL_PTR != StatePtr))
  {
    /* @Trace: SafeE2E_SUD_MF_704 */    
    /* Note: Source code that implement item SafeE2E_SUD_MF_704 */   
    retValue = E2E_E_INPUTERR_WRONG;
    /*Check correct Data input */
    if ((NULL_PTR == DataPtr) && (0x00U != Length))
    {
      retValue = E2E_E_INPUTERR_WRONG;
    }
    else if ((NULL_PTR != DataPtr) && (0x00U == Length))
    {
      retValue = E2E_E_INPUTERR_WRONG;
    }
    else if ((Length < ((uint16)(ConfigPtr->Offset / 0x0008U) + 0x0001U)) && \
	  (Length != 0))
    {
      retValue = E2E_E_INPUTERR_WRONG;
    }	
    else
    {
      if (NULL_PTR != DataPtr)
      {
        /* check correct for value of Length data 
          1. The offset shall be a multiple of 8 and 0 <= Offset <= DataLength-(2*8).
        */
        if ((Length == (ConfigPtr->DataLength / 0x08U)) && \
            (0x00U == (ConfigPtr->Offset % 0x08U)) && \
            (ConfigPtr->DataLength >= E2E_P22_MIN_DATA_LENGTH_LIMIT) && \
            (ConfigPtr->Offset <= (ConfigPtr->DataLength - E2E_P22_MIN_DATA_LENGTH_LIMIT)))
        {
          /*Read Counter from receivedData*/
          receivedCounterValue = (uint8)((DataPtr[(ConfigPtr->Offset / 0x08U) \
          + E2E_P22_CNT_BYTE_ONE]) & E2E_LOW_NIBBLE_MASK);          
          /*Read CRC from receivedData*/
          receivedCRCValue = DataPtr[(ConfigPtr->Offset) / 0x08U];
          /*Calculate CRC from received Data by call to local function E2E_P22CalculateCRC */
          calculateCRC = E2E_P22CalculateCRC(ConfigPtr, DataPtr, Length, receivedCounterValue);
          /*Check and set status for State-> status by call CheckStatus() function*/
          E2E_P22CheckStatus(receivedCRCValue, calculateCRC, receivedCounterValue, ConfigPtr, StatePtr);
          retValue = E2E_E_OK;
        }        
      }
      else
      {
        /*Do check step with NewDataAvailable is False*/
        StatePtr->Status = E2E_P22STATUS_NONEWDATA;
        retValue = E2E_E_OK;
      }
    }
  }/* polyspace-end MISRA2012:D4.14 MISRA2012:D4.1 MISRA2012:18.1 RTE:IDP [Justified:Low] "the pointer is validated in previous branch"*/
  /* @Trace: SafeE2E_SUD_MF_703 */    
  /* Note: Source code that implement item SafeE2E_SUD_MF_703 */   

  return retValue;
}

/*******************************************************************************
** Function Name        : E2E_P22MapStatusToSM                                **
**                                                                            **
** Service ID           : 0x3f                                                **
**                                                                            **
** Description          : This function shall maps the check status of        **
**                        Profile 22 to a generic check status, which can be  **
**                        used by E2E state machine check function. The E2E   **
**                        Profile 22 delivers a more fine-granular status, but**
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

FUNC(E2E_PCheckStatusType, E2E_CODE) E2E_P22MapStatusToSM (
        VAR(Std_ReturnType, AUTOMATIC) CheckReturn,
        VAR(E2E_P22CheckStatusType, AUTOMATIC) Status)
{
  /* @Trace: SafeE2E_SUD_MF_707 */    
  /* Note: Source code that implement item SafeE2E_SUD_MF_707 */   
   
  /* Local variable to store return value */
  VAR(E2E_PCheckStatusType, AUTOMATIC) checkStatus;

  checkStatus = E2E_P_ERROR;
  /*Choose return status follow Status*/
  if (E2E_E_OK == CheckReturn)
  {
    switch (Status)
    {
      case E2E_P22STATUS_OK: /*Walk through*/
      case E2E_P22STATUS_OKSOMELOST:
        checkStatus = E2E_P_OK;
        break;

      case E2E_P22STATUS_NONEWDATA:
        checkStatus = E2E_P_NONEWDATA;
        break;

      case E2E_P22STATUS_REPEATED:
        checkStatus = E2E_P_REPEATED;
        break;

      case E2E_P22STATUS_WRONGSEQUENCE:
        checkStatus = E2E_P_WRONGSEQUENCE;
        break;

      case E2E_P22STATUS_ERROR:
        checkStatus = E2E_P_ERROR;
        break;

      default:
        /*Walk through*/
        break;
    }
  }

  return checkStatus;
}
#define E2E_STOP_SEC_CODE_ASIL_D
#include "MemMap.h"  /*polyspace MISRA2012:20.1 [Justified:Low] "This include directive is necessary for Memory mapping"*/

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
