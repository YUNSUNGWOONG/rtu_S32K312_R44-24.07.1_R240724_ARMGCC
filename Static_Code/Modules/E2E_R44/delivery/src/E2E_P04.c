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
**  SRC-MODULE: E2E_P04.c                                                     **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR E2E Module                                            **
**                                                                            **
**  PURPOSE   : To implement specification of E2E Profile 4 driver            **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision Date           By               Description                       **
********************************************************************************
** 1.0.1.1  27-Jun-2022    Gongbin Lim      #CP44-320                         **
** 0.0.1    10-Sep-2019    TruongBX         Initial Version                   **
** 0.0.2    20-Feb-2020    CuongLX          Remove marcro less meaning        **
** 0.0.3    01-Oct-2020    MinhNQ26         Fix code review comments (#15965) **
** 1.0.1    28-Dec-2021    HiepVT1          Add code to check the validity of **
**                                          E2E inputs (Length and offset)    **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "E2E.h"
/*******************************************************************************
**                      Internal Function Declarations                        **
*******************************************************************************/

static FUNC(uint32, E2E_CODE) E2E_P04CalculateCRC( \
    P2CONST(uint8, AUTOMATIC, E2E_APPL_CONST) DataPtr, \
    P2CONST(E2E_P04ConfigType, AUTOMATIC, E2E_APPL_CONST) ConfigPtr, \
    VAR(uint16, AUTOMATIC) Length);

static FUNC(void, E2E_CODE) E2E_P04CheckStatus( \
    P2CONST(E2E_P04ConfigType, AUTOMATIC, E2E_APPL_CONST) ConfigPtr, \
    P2VAR(E2E_P04CheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr, \
    VAR(uint16, AUTOMATIC) receivedCounter, \
    VAR(boolean, AUTOMATIC) newDataAvailable, \
    VAR(boolean, AUTOMATIC) IsCorrectData);

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define E2E_START_SEC_CODE_ASIL_D /*polyspace MISRA2012:2.5 [Justified:Low] "This macro is necessary for Memory mapping"*/
#include "MemMap.h"  /*polyspace MISRA2012:20.1 [Justified:Low] "This include directive is necessary for Memory mapping"*/

/*******************************************************************************
** Function Name        : E2E_P04CalculateCRC                                 **
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
** Return Value         : uint32                                              **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                                                                            **
**                        Function(s) invoked    : Crc_CalculateCRC32P4       **
*******************************************************************************/
/* @Trace: SRS_E2E_08534  SRS_E2E_08529 SRS_BSW_00323 SRS_E2E_08539 RS_E2E_08543 */
static FUNC(uint32, E2E_CODE) E2E_P04CalculateCRC(
    P2CONST(uint8, AUTOMATIC, E2E_APPL_CONST) DataPtr,
    P2CONST(E2E_P04ConfigType, AUTOMATIC, E2E_APPL_CONST) ConfigPtr,
    VAR(uint16, AUTOMATIC) Length)
{
  /* @Trace: SafeE2E_SUD_MF_209 */    
  /* Note: Source code that implement item SafeE2E_SUD_MF_209 */   
   
  /* Local variable to store calculate CRC */
  VAR(uint32, AUTOMATIC) computedCRC;
  /*Length for calculate CRC*/
  VAR(uint16, AUTOMATIC) lengthForCRC;
  /* calculate CRC in first time call */
  
  lengthForCRC = (ConfigPtr->Offset / 0x08U) + 8U;

  computedCRC = \
    Crc_CalculateCRC32P4(& DataPtr[0x00U], \
      (uint32)lengthForCRC, E2E_P04_CRC_START_VAL, TRUE);
  /* polyspace-begin MISRA2012:D4.14 [Justified:Low] "the pointer is check for not null previous branch"*/
  if (((ConfigPtr->Offset / 0x08U) + 12U) < Length)
  {
    /* calculate CRC in second time call */
    lengthForCRC = (Length - (ConfigPtr->Offset / (0x08U)) - 12U);
    
    computedCRC = \
      Crc_CalculateCRC32P4(&DataPtr[(ConfigPtr->Offset / 0x08U) + 12U],
      (uint32)lengthForCRC, computedCRC, FALSE);
  }
  /* polyspace-end MISRA2012:D4.14 [Justified:Low] "the pointer is check for not null previous branch"*/


  return computedCRC;
}

/*******************************************************************************
** Function Name        : E2E_P04CheckStatus                                  **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : This function check status of received data.        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : ConfigPtr,receivedCounter, NewDataAvaiable,         **
**                        RecievedCRC, ComputedCRC, receivedDataID,           **
**                        Length ,receivedLength                              **
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
static FUNC(void, E2E_CODE) E2E_P04CheckStatus(
    P2CONST(E2E_P04ConfigType, AUTOMATIC, E2E_APPL_CONST) ConfigPtr,
    P2VAR(E2E_P04CheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
    VAR(uint16, AUTOMATIC)  receivedCounter,
    VAR(boolean, AUTOMATIC) newDataAvailable,
    VAR(boolean, AUTOMATIC) IsCorrectData)
{
  /* @Trace: SafeE2E_SUD_MF_208 */    
  /* Note: Source code that implement item SafeE2E_SUD_MF_208 */    

  /* Local variable to store delta counter */
  VAR(uint16, AUTOMATIC) deltaCounter;

  /* polyspace-begin MISRA2012:D4.14 [Justified:Low] "the pointer is check for not null previous branch"*/
  if (TRUE != newDataAvailable)
  {
    StatePtr->Status = E2E_P04STATUS_NONEWDATA;
  }
  else
  {
    if (TRUE == IsCorrectData)
    {
      if (receivedCounter >= StatePtr->Counter)
      {
        deltaCounter = receivedCounter - StatePtr->Counter;
      }
      else
      {
        deltaCounter = \
          (uint16)(E2E_P04_CNT_MAX + receivedCounter - StatePtr->Counter + 0x01U);
      }

      if (deltaCounter <= (uint16)ConfigPtr->MaxDeltaCounter)
      {
        StatePtr->Status = E2E_P04STATUS_OKSOMELOST;

        if (0x00U == deltaCounter)
        {
          StatePtr->Status = E2E_P04STATUS_REPEATED;
        }

        if ((uint16)0x01U == deltaCounter)
        {
          StatePtr->Status = E2E_P04STATUS_OK;
        }
      }
      else
      {
        StatePtr->Status = E2E_P04STATUS_WRONGSEQUENCE;
      }

      StatePtr->Counter = receivedCounter;
    }
    else
    {
      StatePtr->Status = E2E_P04STATUS_ERROR;
    }
  }
  /* polyspace-end MISRA2012:D4.14 [Justified:Low] "the pointer is check for not null previous branch"*/
}

/*******************************************************************************
**                      Interface Function Declarations                       **
*******************************************************************************/

/*******************************************************************************
** Function Name        : E2E_P04ProtectInit                                  **
**                                                                            **
** Service ID           : 0x22                                                **
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
FUNC(Std_ReturnType, E2E_CODE) E2E_P04ProtectInit(
    P2VAR(E2E_P04ProtectStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr)
{
  /* @Trace: SafeE2E_SUD_MF_205 */    
  /* Note: Source code that implement item SafeE2E_SUD_MF_205 */   

  /* Local variable to store return value */
  VAR(Std_ReturnType, AUTOMATIC)	returnValue;

  returnValue = E2E_E_INPUTERR_NULL;
  /* Verify inputs of the protect function */
  /* polyspace-begin MISRA2012:D4.14 [Justified:Low] "the pointer is check for not null previous branch"*/
  if (NULL_PTR != StatePtr)
  {
    /* Set Counter to 0 */
    StatePtr->Counter = 0x0000U;
    
    returnValue = E2E_E_OK;
  }/* polyspace-end MISRA2012:D4.14 [Justified:Low] "the pointer is check for not null previous branch"*/

  return returnValue;
}
/*******************************************************************************
** Function Name        : E2E_P04Protect                                      **
**                                                                            **
** Service ID           : 0x21                                                **
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
**                        Function(s) invoked    : E2E_P04CalculateCRC        **
*******************************************************************************/
/* @Trace: SRS_E2E_08527 SRS_E2E_08528 RS_E2E_08540 SRS_BSW_00337 
SRS_E2E_08534  SRS_E2E_08529 SRS_BSW_00323 SRS_E2E_08539 RS_E2E_08543*/
FUNC(Std_ReturnType, E2E_CODE) E2E_P04Protect(
    P2CONST(E2E_P04ConfigType, AUTOMATIC, E2E_APPL_CONST) ConfigPtr,
    P2VAR(E2E_P04ProtectStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
    P2VAR(uint8, AUTOMATIC, E2E_APPL_DATA) DataPtr,
    VAR(uint16, AUTOMATIC) Length)
{
  /* Local variable to store return value */
  VAR(Std_ReturnType, AUTOMATIC) returnValue;
  /* Local variable to store offset value */
  VAR(uint16, AUTOMATIC) offsetInByte;
  /* Local variable to store calculated CRC value */
  VAR(uint32, AUTOMATIC) computedCRC;

  returnValue = E2E_E_INPUTERR_NULL;

  /* polyspace-begin MISRA2012:D4.14 [Justified:Low] "the pointer is check for not null previous branch"*/
  if ((NULL_PTR != ConfigPtr) && (NULL_PTR != StatePtr) && (NULL_PTR != DataPtr))
  {
    
    offsetInByte = ConfigPtr->Offset / 0x08U;

      /* check correct for value of Length data 
        1. The offset shall be a multiple of 8 and 0 <= Offset <= MaxDataLength-(12*8)
        2. Length is>= MinDataLength. The value shall be <= 4096*8 (4kB) and shall be>= 12*8.
        3. DataLength is <= MaxDataLength. The value shall be <= 4096*8 (4kB) and it shall be>= MinDataLength.
      */
    if ((ConfigPtr->MinDataLength >= E2E_P04_MIN_DATA_LENGTH_LIMIT) && \
        ((uint16)E2E_P04_MAX_DATA_LENGTH_LIMIT >= ConfigPtr->MaxDataLength) && \
        (Length >= (ConfigPtr->MinDataLength / 0x08U)) && \
        (Length <= (ConfigPtr->MaxDataLength / 0x08U)) && \
        (ConfigPtr->Offset <= (ConfigPtr->MaxDataLength - E2E_P04_MIN_DATA_LENGTH_LIMIT)) && \
        (0x00U == (ConfigPtr->Offset % 0x08U))  && \
        (Length > ((ConfigPtr->Offset / (0x0008U)) + 12U)))
    {
      /* @Trace: SafeE2E_SUD_MF_204 */    
      /* Note: Source code that implement item SafeE2E_SUD_MF_204 */

      /* Write length input to Data in location DataPtr[Offset.. Offset+1] 
      in Big Endian order and LSB fist ...*/
      DataPtr[offsetInByte] = \
        (uint8)((Length >> 0x08U) & E2E_LOW_BYTE_MASK);

      DataPtr[offsetInByte + 1U] = \
        (uint8)(Length & E2E_LOW_BYTE_MASK);
      /*..............................*/
      /* Write counter to Data in location DataPtr[Offset+2...Offset+3] 
      in Big Endian order */
      DataPtr[offsetInByte + 2U] = \
        (uint8)((StatePtr->Counter >> 0x08U) & E2E_LOW_BYTE_MASK);

      DataPtr[offsetInByte + 3U] = \
        (uint8)((StatePtr->Counter) & E2E_LOW_BYTE_MASK);
      /*..............................*/
      /* Write DataID to Data in location DataPtr[Offset+4...Offset+7] in Big Endian order */
      DataPtr[offsetInByte + 4U] = \
        (uint8)((ConfigPtr->DataID >> 0x18U) & E2E_FOUR_BYTE_BYTE_MASK);

      DataPtr[offsetInByte + 5U] = \
        (uint8)((ConfigPtr->DataID >> 0x10U) & E2E_FOUR_BYTE_BYTE_MASK);
      
      DataPtr[offsetInByte + 6U] = \
        (uint8)((ConfigPtr->DataID >> 8U) & E2E_FOUR_BYTE_BYTE_MASK);

      DataPtr[offsetInByte + 7U] = \
        (uint8)(ConfigPtr->DataID & E2E_FOUR_BYTE_BYTE_MASK);

      /*..............................*/
      /* Calculate CRC */
      computedCRC = E2E_P04CalculateCRC((P2CONST(uint8, AUTOMATIC, E2E_APPL_CONST))DataPtr, ConfigPtr, Length);
      /* Write DataID to Data in location DataPtr[Offset+8...Offset +11] using big Endian order */
      DataPtr[offsetInByte + 8U] = \
        (uint8)((computedCRC >> 0x18U) & E2E_FOUR_BYTE_BYTE_MASK);

      DataPtr[offsetInByte + 9U] = \
        (uint8)((computedCRC >> 0x10U) & E2E_FOUR_BYTE_BYTE_MASK);

      DataPtr[offsetInByte + 10U] = \
        (uint8)((computedCRC >> 8U) & E2E_FOUR_BYTE_BYTE_MASK);

      DataPtr[offsetInByte + 11U] = \
        (uint8)(computedCRC & E2E_FOUR_BYTE_BYTE_MASK);
      /*..............................*/
      /*Increment the counter after finish write data (i.e. next value after ) 0xFFFF is 0).*/
      StatePtr->Counter = \
        (uint16)(((uint32)StatePtr->Counter + (uint32)0x01U) % E2E_P04_CNT_MAX_VL_CYCLE);
      /* Protect process finished successful */
      returnValue = E2E_E_OK;
    }
    /*Data or Length of Data is wrong */
    else
    {
      /* @Trace: SafeE2E_SUD_MF_203 */    
      /* Note: Source code that implement item SafeE2E_SUD_MF_203 */
      returnValue = E2E_E_INPUTERR_WRONG;
    }
  } /* polyspace-end MISRA2012:D4.14 [Justified:Low] "the pointer is check for not null previous branch"*/
  /* @Trace: SafeE2E_SUD_MF_202 */    
  /* Note: Source code that implement item SafeE2E_SUD_MF_202 */
  return returnValue;
}

/*******************************************************************************
** Function Name        : E2E_P04CheckInit                                    **
**                                                                            **
** Service ID           : 0x24                                                **
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
FUNC(Std_ReturnType, E2E_CODE) E2E_P04CheckInit (
    P2VAR(E2E_P04CheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr)
{
  /* @Trace: SafeE2E_SUD_MF_200 */    
  /* Note: Source code that implement item SafeE2E_SUD_MF_200 */   
   
  /* Local variable to store return value */
  VAR(Std_ReturnType, AUTOMATIC)	returnValue;

  returnValue = E2E_E_INPUTERR_NULL;
  /* Verify inputs of the protect function */
  /* polyspace-begin MISRA2012:D4.14 [Justified:Low] "the pointer is check for not null previous branch"*/
  if (NULL_PTR != StatePtr)
  {
    /* Set Counter to 0xFF */
    StatePtr->Counter = E2E_P04_CNT_MAX;
   
    /* Set Status to E2E_P04STATUS_ERROR */
    StatePtr->Status = E2E_P04STATUS_ERROR;

    returnValue = E2E_E_OK;
  } /* polyspace-end MISRA2012:D4.14 [Justified:Low] "the pointer is check for not null previous branch"*/

  return returnValue;
}
/*******************************************************************************
** Function Name        : E2E_P04Check                                        **
**                                                                            **
** Service ID           : 0x23                                                **
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
**                        Function(s) invoked    : E2E_P04CalculateCRC        **
**                                                 E2E_P04CheckStatus         **
*******************************************************************************/
/* @Trace: SRS_E2E_08527 SRS_E2E_08528 RS_E2E_08540 SRS_BSW_00337 ,
SRS_E2E_08534  SRS_E2E_08529 SRS_BSW_00323 SRS_E2E_08539 RS_E2E_08543*/
FUNC(Std_ReturnType, E2E_CODE) E2E_P04Check(
    P2CONST(E2E_P04ConfigType, AUTOMATIC, E2E_APPL_CONST) ConfigPtr,
    P2VAR(E2E_P04CheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
    P2CONST(uint8, AUTOMATIC, E2E_APPL_CONST) DataPtr,
    VAR(uint16, AUTOMATIC) Length)
{
  /* Local variable to store return value */
  VAR(Std_ReturnType, AUTOMATIC)	returnValue;
  /* Local variable to store the high bytes of length value on received DataPtr */
  VAR(uint16, AUTOMATIC)	receivedLengthHighByte;
  /* Local variable to store the low bytes of length value on received DataPtr */
  VAR(uint16, AUTOMATIC)	receivedLengthLowByte;
  /* Local variable to store the high bytes of counter value on received DataPtr */
  VAR(uint16, AUTOMATIC)	receivedCounterHighByte;
  /* Local variable to store the low bytes of counter value on received DataPtr */
  VAR(uint16, AUTOMATIC)	receivedCounterLowByte;
  /* Local variable to store offset value */
  VAR(uint16, AUTOMATIC)	offsetInByte;
  /* Local variable to store received Crc value */
  VAR(uint32, AUTOMATIC)	receivedCRC;
  /* Local variable to store calculated Crc value */
  VAR(uint32, AUTOMATIC)	computeCRC;
  /* Local variable to store received counter value */
  VAR(uint16, AUTOMATIC)	receivedCounter;
  /* Local variable to store flag check whether data is available */
  VAR(boolean, AUTOMATIC)	newDataAvailable;
  /* Local variable to store flag check whether data is correct */
  VAR(boolean, AUTOMATIC)	isCorrectData;
  /* Local variable to store received data id value */
  VAR(uint32, AUTOMATIC)	receivedDataID;
  /* Local variable to store received length value */
  VAR(uint16, AUTOMATIC)	receivedLength;

  returnValue = E2E_E_INPUTERR_NULL;
  receivedCounter = 0x00U;
  newDataAvailable = FALSE;
  isCorrectData = FALSE;

  /* polyspace-begin MISRA2012:D4.14 [Justified:Low] "the pointer is check for not null previous branch"*/
  /*Check null input */
  if ((NULL_PTR != ConfigPtr) && (NULL_PTR != StatePtr))
  {
    /* @Trace: SafeE2E_SUD_MF_207 */    
    /* Note: Source code that implement item SafeE2E_SUD_MF_207 */
    offsetInByte = ConfigPtr->Offset / 0x08U;
    
    /*Check correct of parameter input */
    if ((NULL_PTR == DataPtr) && (0x00U != Length))
    {
      returnValue = E2E_E_INPUTERR_WRONG;
    }
    else if ((NULL_PTR != DataPtr) && (0x00U == Length))
    {
      returnValue = E2E_E_INPUTERR_WRONG;
    }
    else if ((Length < ((ConfigPtr->Offset / (0x0008U)) + 12U)) && \
	  (Length != 0))
    {
      returnValue = E2E_E_INPUTERR_WRONG;
    }	
    else
    {
      if (NULL_PTR != DataPtr)
      {
        if ((ConfigPtr->MinDataLength >= E2E_P04_MIN_DATA_LENGTH_LIMIT) && \
            ((uint16)E2E_P04_MAX_DATA_LENGTH_LIMIT >= ConfigPtr->MaxDataLength) && \
            (Length >= (ConfigPtr->MinDataLength / 0x08U)) && \
            (Length <= (ConfigPtr->MaxDataLength / 0x08U)) && \
            (ConfigPtr->Offset <= (ConfigPtr->MaxDataLength - E2E_P04_MIN_DATA_LENGTH_LIMIT)) && \
            (0x00U == (ConfigPtr->Offset % 8U)))
        {
          newDataAvailable = TRUE;
          /* read Length from received Data in location DataPtr[Offset...Offset+1] 
          in Big Endian order to uint16 local variable receivedLength */
          receivedLengthHighByte = \
            ((uint16)(DataPtr[offsetInByte])) << 0x08U;
          receivedLengthLowByte = (uint16)(DataPtr[offsetInByte + 1U]);
          receivedLength = \
            (uint16)((receivedLengthHighByte & E2E_HIGH_BYTE_MASK) | \
            (receivedLengthLowByte & E2E_LOW_BYTE_MASK));
          /* read Counter from received Data in location DataPtr[Offset+2...Offset+3] 
          in Big Endian order on uint16 local variable receivedCounter */
          receivedCounterHighByte = \
            ((uint16)(DataPtr[offsetInByte + 2U])) << 0x08U;
          receivedCounterLowByte = (uint16)(DataPtr[offsetInByte + 3U]);
          receivedCounter = \
            (uint16)((receivedCounterHighByte & E2E_HIGH_BYTE_MASK) | \
            (receivedCounterLowByte & E2E_LOW_BYTE_MASK));
                    
          /* read receivedDataID from received Data in location DataPtr[Offset+4...Offset+7] 
          in Big Endian order on uint32 local variable receivedDataID */
          receivedDataID = \
            ((uint32)(DataPtr[offsetInByte + 4U] & \
              E2E_FOUR_BYTE_BYTE_MASK) << 0x18U) | \
            ((uint32)(DataPtr[offsetInByte + 5U] & \
              E2E_FOUR_BYTE_BYTE_MASK) << 0x10U) | \
            ((uint32)(DataPtr[offsetInByte + 6U] & \
              E2E_FOUR_BYTE_BYTE_MASK) << 0x08U) | \
            (uint32)(DataPtr[offsetInByte + 7U] & \
              E2E_FOUR_BYTE_BYTE_MASK);
          /* read receivedCRC from received Data in location DataPtr[Offset+8...Offset+11] 
          using big Endian order on 4-byte local variable receivedCRC */
          receivedCRC = \
            ((uint32)(DataPtr[offsetInByte + 8U] & \
              E2E_FOUR_BYTE_BYTE_MASK) << 0x18U) | \
            ((uint32)(DataPtr[offsetInByte + 9U] & \
              E2E_FOUR_BYTE_BYTE_MASK) << 0x10U) | \
            (uint32)((DataPtr[offsetInByte + 10U] & \
              E2E_FOUR_BYTE_BYTE_MASK) << 0x08U) | \
            (uint32)(DataPtr[offsetInByte + 11U] & \
              E2E_FOUR_BYTE_BYTE_MASK);
          /*Calculate CRC by call to E2E_P04computedCRC() function */
          computeCRC = E2E_P04CalculateCRC(DataPtr, ConfigPtr, Length);

          if (((receivedCRC == computeCRC) && (ConfigPtr->DataID == receivedDataID) &&
               (receivedLength == Length)))
          {
            isCorrectData = TRUE;
          }
          else
          {
            isCorrectData = FALSE;
          }

          /*Check status to detect status by call to CheckStatus() function*/
          E2E_P04CheckStatus(ConfigPtr, StatePtr, receivedCounter, newDataAvailable, isCorrectData);
          /* Set return value to E2E_E_OK after check process finish*/
          returnValue = E2E_E_OK;
        }
        else
        {
          returnValue = E2E_E_INPUTERR_WRONG;
        }
      }
      else
      {
        /*Check status to detect status by call to CheckStatus() function*/
        E2E_P04CheckStatus(ConfigPtr, StatePtr, receivedCounter, newDataAvailable, isCorrectData);
        /* Set return value to E2E_E_OK after check process finish*/
        returnValue = E2E_E_OK;
      }
    }/* polyspace-end MISRA2012:D4.14 [Justified:Low] "the pointer is check for not null previous branch"*/
  }

  /* @Trace: SafeE2E_SUD_MF_206 */    
  /* Note: Source code that implement item SafeE2E_SUD_MF_206 */

  return returnValue;
}

/*******************************************************************************
** Function Name        : E2E_P04MapStatusToSM                                **
**                                                                            **
** Service ID           : 0x25                                                **
**                                                                            **
** Description          : This function shall maps the check status of        **
**                        Profile 4 to a generic check status, which can be   **
**                        used by E2E state machine check function. The E2E   **
**                        Profile 4 delivers a more fine-granular status, but **
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
FUNC(E2E_PCheckStatusType, E2E_CODE) E2E_P04MapStatusToSM (
    VAR(Std_ReturnType, AUTOMATIC) CheckReturn,
    VAR(E2E_P04CheckStatusType, AUTOMATIC) Status)
{
  /* @Trace: SafeE2E_SUD_MF_201 */    
  /* Note: Source code that implement item SafeE2E_SUD_MF_201 */   
   
  /* Local variable to store return value */
  VAR(E2E_PCheckStatusType, AUTOMATIC) checkStatus;

  checkStatus = E2E_P_ERROR;
  /*Choose return status follow Status*/
  if (E2E_E_OK == CheckReturn)
  {
    switch (Status)
    {
      case E2E_P04STATUS_OK:
            /*Walk through*/
      case E2E_P04STATUS_OKSOMELOST:
        checkStatus = E2E_P_OK;
        break;

      case E2E_P04STATUS_NONEWDATA:
        checkStatus = E2E_P_NONEWDATA;
        break;

      case E2E_P04STATUS_REPEATED:
        checkStatus = E2E_P_REPEATED;
        break;

      case E2E_P04STATUS_WRONGSEQUENCE:
        checkStatus = E2E_P_WRONGSEQUENCE;
        break;

      case E2E_P04STATUS_ERROR:
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
