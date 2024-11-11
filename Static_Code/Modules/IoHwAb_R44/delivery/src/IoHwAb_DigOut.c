/*******************************************************************************
**                                                                            **
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  This source code is permitted to be used only in projects contracted      **
**  with Hyundai Autoever, and any other use is prohibited.                   **
**  If you use it for other purposes or change the source code,               **
**  you may take legal responsibility.                                        **
**  In this case, There is no warranty and technical support.                 **
**                                                                            **
**  SRC-MODULE: IoHwAb_DigOut.c                                               **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR IOHWAB                                                **
**                                                                            **
**  PURPOSE   : APIs implementation for IoHwAb module                         **
**              IoHwAb_DigOutInit                                             **
**              IoHwAb_DigOutDeInit                                           **
**              IoHwAb_DigOutWrite                                            **
**              IoHwAb_DigOutWriteDirect                                      **
**              IoHwAb_DigOutRead                                             **
**              IoHwAb_DigOutReadDirect                                       **
**              IoHwAb_DigOutWriteOutputsToHW                                 **
**              IoHwAb_DigOutGetFailure                                       **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By               Description                       **
********************************************************************************
** 1.4.5     18-May-2023  KhaLN1            #CP44-2223                        **
** 1.3.0.1   30-Jun-2022  KhaLN1            #CP44-365                         **
** 1.1.0     15-Jul-2021  YangJin.Kim       R44-Redmine #18100                **
** 1.0.0     04-Dec-2020  YangJin.Kim       R40-Redmine #26992                **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "IoHwAb_DigOut.h"
#include "IoHwAb_Config.h"
#if (IOHWAB_USE_L9826 == STD_ON)
#include "IoHwAb_DigOutL9826.h"
#endif /* (IOHWAB_USE_L9826 == STD_ON) */
#if (IOHWAB_USE_L99MC6 == STD_ON)
#include "IoHwAb_DigOutL99MC6.h"
#endif /* (IOHWAB_USE_L99MC6 == STD_ON) */
#if (IOHWAB_USE_TLE7240SL == STD_ON)
#include "IoHwAb_DigOutTLE7240SL.h"
#endif /* (IOHWAB_USE_TLE7240SL == STD_ON) */


#include "Rte_IoHwAb.h"
#include "SchM_IoHwAb.h"
#include "IoHwAb_Util.h"

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
#if ((IOHWAB_USE_L9826_DIAG == STD_ON) && (IOHWAB_USE_DIG_OUT == STD_ON))
static FUNC(Std_ReturnType, IOHWAB_CODE)IoHwAb_DigOutGetFailureBitThree(
  uint8 LucBufIdx, uint8 LucShiftBit);

static FUNC(Std_ReturnType, IOHWAB_CODE)IoHwAb_DigOutGetFailureBitSeven(
  uint8 LucBufIdx, uint8 LucShiftBit);

static FUNC(Std_ReturnType, IOHWAB_CODE)IoHwAb_DigOutGetFailureBitOther(
  uint8 LucBufIdx, uint8 LucShiftBit);
#endif /* ((IOHWAB_USE_L9826_DIAG == STD_ON) && (IOHWAB_USE_DIG_OUT == STD_ON)) */

/* polyspace-begin RTE:UNR [Not a defect:Unset] "Reachable code" */
/* polyspace-begin MISRA-C3:D4.14 [Justified:Unset] "The pointer is checked always." */
/* polyspace-begin MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Unset] "It depends on the configuration" */
/* polyspace-begin MISRA-C3:8.3 [Justified:Unset] "Prototypes are generated wrongly. It will be fixed soon" */
/* polyspace-begin DEFECT:DEAD_CODE [Justified:Unset] "It depends on the configuration." */
/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#if (IOHWAB_USE_DIG_OUT == STD_ON)
/*******************************************************************************
** Function Name        : IoHwAb_DigOutInit                                   **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          :                                                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                          IoHwAb_GaaDigOutResultBuffer,                     **
**                          IoHwAb_GaaDigOutDefVal,                           **
**                          IoHwAb_GaaDigOutL9826Infos                        **
**                        Function(s) invoked    :                            **
**                          IoHwAb_DigOutL9826SwitchOn                        **
*******************************************************************************/
/* @Trace: SRS_IoHwAb_12323 */
/* @Trace: SWS_IoHwAb_00078 SWR_IOHWAB_706_001 */
/* @Trace: IoHwAb_SUD_API_067 */
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(void, IOHWAB_CODE)IoHwAb_DigOutInit(void)
{
  uint8 LucIdx;

  for (LucIdx = 0U; LucIdx < IOHWAB_NUM_DIGOUT_MCU_BUFFER; LucIdx++)
  {
    IoHwAb_GaaDigOutResultBuffer[LucIdx].ucResult
      = IoHwAb_GaaDigOutDefVal[LucIdx];
  }

  /* update buffered outputs except demultiplexed outputs  */
  IoHwAb_DigOutWriteOutputsToHW();

  #if (IOHWAB_USE_L9826 == STD_ON)
  for (LucIdx = 0U; LucIdx < IOHWAB_NUM_DIGOUT_L9826; LucIdx++)
  {
    IoHwAb_GaaDigOutResultBuffer[LucIdx + IOHWAB_NUM_DIGOUT_L9826_START_IDX].ucResult
      = IoHwAb_GaaDigOutL9826Infos[LucIdx].ucDefVal;
  }

  IoHwAb_DigOutL9826SwitchOn();

  /* update the L9826 demultiplexed outputs */
  (void)IoHwAb_DigOutL9826();
  #endif /* (IOHWAB_USE_L9826 == STD_ON) */

  #if (IOHWAB_USE_L99MC6 == STD_ON)
  for (LucIdx = 0U; LucIdx < IOHWAB_NUM_DIGOUT_L99MC6; LucIdx++)
  {
    IoHwAb_GaaDigOutResultBuffer[LucIdx + IOHWAB_NUM_DIGOUT_L99MC6_START_IDX].ucResult
      = IoHwAb_GaaDigOutL99MC6Infos[LucIdx].ucDefVal;
  }

  (void)IoHwAb_DigOutL99MC6SwitchOn();

  /* update the L99MC6 demultiplexed outputs */
  (void)IoHwAb_DigOutL99MC6();
  #endif /* (IOHWAB_USE_L99MC6 == STD_ON) */

  #if (IOHWAB_USE_TLE7240SL == STD_ON)
  for (LucIdx = 0U; LucIdx < IOHWAB_NUM_DIGOUT_TLE7240SL; LucIdx++)
  {
    IoHwAb_GaaDigOutResultBuffer[LucIdx + IOHWAB_NUM_DIGOUT_TLE7240SL_START_IDX].ucResult
      = IoHwAb_GaaDigOutTLE7240SLInfos[LucIdx].ucDefVal;
  }

  (void)IoHwAb_DigOutTLE7240SLSwitchOn();

  /* update the TLE7240SL demultiplexed outputs */
  (void) IoHwAb_DigOutTLE7240SL();
  #endif /* (IOHWAB_USE_TLE7240SL == STD_ON) */

}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : IoHwAb_DigOutDeInit                                 **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          :                                                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : none                       **
**                        Function(s) invoked    :                            **
**                          IoHwAb_DigOutL9826SwitchOff,                      **
**                          IoHwAb_DigOutL99MC6SwitchOff                      **
*******************************************************************************/
/* @Trace: IoHwAb_SUD_API_068 */
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(void, IOHWAB_CODE)IoHwAb_DigOutDeInit(void)
{
  #if (IOHWAB_USE_L9826 == STD_ON)
  (void)IoHwAb_DigOutL9826SwitchOff();
  #endif /* (IOHWAB_USE_L9826 == STD_ON) */

  #if (IOHWAB_USE_L99MC6 == STD_ON)
  (void)IoHwAb_DigOutL99MC6SwitchOff();
  #endif /* (IOHWAB_USE_L99MC6 == STD_ON) */

  #if (IOHWAB_USE_TLE7240SL == STD_ON)
  (void)IoHwAb_DigOutTLE7240SLSwitchOff();
  #endif /* (IOHWAB_USE_TLE7240SL == STD_ON) */
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : IoHwAb_DigOutWrite                                  **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          :                                                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : ChIdx, Level                                        **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                          IoHwAb_GaaDigOutResultBuffer                      **
**                        Function(s) invoked    :                            **
**                          SchM_Enter_IoHwAb_IoHwAbProtection,               **
**                          SchM_Exit_IoHwAb_IoHwAbProtection                 **
*******************************************************************************/
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
/* @Trace: IoHwAb_SUD_API_069 */
FUNC(void, IOHWAB_CODE)IoHwAb_DigOutWrite(IoHwAb_IndexType ChIdx,
  IoHwAb_LevelType Level)
{
  uint8 LucShiftBit =  (uint8)(ChIdx % 8U);
  uint8 LucResBufIdx = (uint8)(ChIdx / 8U);
  IoHwAb_LevelType LucLevel = Level;

  uint8 LucLockStatus = IOHWAB_UNLOCKED;
  
  if (LucLevel != IOHWAB_LOW)
  {
    LucLevel = IOHWAB_HIGH;
  }

  if (LucResBufIdx < IOHWAB_NUM_DIGOUT_RESULT_BUFFER)
  {
    LucLockStatus = ((IoHwAb_GaaDigitalSignal_Locked[LucResBufIdx])
      & ((uint8)(1U << LucShiftBit))) >> LucShiftBit;
      
    if (IOHWAB_UNLOCKED == LucLockStatus)
    {  
       SchM_Enter_IoHwAb_IoHwAbProtection();
       IoHwAb_GaaDigOutResultBuffer[LucResBufIdx].ucResult
         &= (uint8)(~((uint8)(1U << LucShiftBit)));
       IoHwAb_GaaDigOutResultBuffer[LucResBufIdx].ucResult
         |= (uint8)(LucLevel << LucShiftBit);
       SchM_Exit_IoHwAb_IoHwAbProtection();
    }
  }
  
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : IoHwAb_DigOutWriteDirect                            **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          :                                                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : ChIdx, Level                                        **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                          IoHwAb_GaaDigOutResultBuffer,                     **
**                          IoHwAb_GaaGenInfos,                               **
**                          IoHwAb_GaaDigOutChIdx,                            **
**                          bodigdir_DirectWrite                              **
**                        Function(s) invoked    :                            **
**                          Dio_ReadChannel,                                  **
**                          Dio_WriteChannel,                                 **
**                          SchM_Enter_IoHwAb_IoHwAbProtection,               **
**                          SchM_Exit_IoHwAb_IoHwAbProtection                 **
*******************************************************************************/

/* @Trace: SWS_IoHwAb_00078 */
/* @Trace: IoHwAb_SUD_API_070 */
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(void, IOHWAB_CODE)IoHwAb_DigOutWriteDirect(IoHwAb_IndexType ChIdx,
  IoHwAb_LevelType Level)
{
  Dio_LevelType LddDioChValue;
  uint8 LucShiftBit   = (uint8)(ChIdx % 8U);
  uint8 LucResBufIdx  = (uint8)(ChIdx / 8U);

  IoHwAb_LevelType LucLevel = Level;

  uint8 LucLockStatus = IOHWAB_UNLOCKED;

  if (LucLevel != IOHWAB_LOW)
  {
    LucLevel = IOHWAB_HIGH;
  }
  if ((LucResBufIdx < IOHWAB_NUM_DIGOUT_RESULT_BUFFER) &&
    (ChIdx < IOHWAB_NUM_DIGOUT_MCU_LGC))
  {
   LucLockStatus = ((IoHwAb_GaaDigitalSignal_Locked[LucResBufIdx])
      & ((uint8)(1U << LucShiftBit))) >> LucShiftBit;
      
   if(LucLockStatus == IOHWAB_UNLOCKED)
   {
     SchM_Enter_IoHwAb_IoHwAbProtection();
     IoHwAb_GaaDigOutResultBuffer[LucResBufIdx].ucResult
       &= (uint8)(~((uint8)(1U << LucShiftBit)));
     IoHwAb_GaaDigOutResultBuffer[LucResBufIdx].ucResult
       |= (uint8)(LucLevel << LucShiftBit);
     if (IoHwAb_GaaGenInfos[IoHwAb_GaaDigOutChIdx[ChIdx]].ucPolar == IOHWAB_POL_LOW)
     {
      if (LucLevel == IOHWAB_LOW)
      {
         LucLevel = IOHWAB_HIGH;
      }
      else
      {
         LucLevel = IOHWAB_LOW;
      }
     }

     LddDioChValue = Dio_ReadChannel(
       IoHwAb_GaaGenInfos[IoHwAb_GaaDigOutChIdx[ChIdx]].ddDioChType);

     if (LddDioChValue != LucLevel)
     {
       IoHwAb_GaaDigOutResultBuffer[LucResBufIdx].ucTempResult
       &= (uint8)(~((uint8)(1U << LucShiftBit)));
       IoHwAb_GaaDigOutResultBuffer[LucResBufIdx].ucTempResult
       |= (uint8)(LucLevel << LucShiftBit);

       Dio_WriteChannel(
       IoHwAb_GaaGenInfos[IoHwAb_GaaDigOutChIdx[ChIdx]].ddDioChType,
        LucLevel);
     }
     SchM_Exit_IoHwAb_IoHwAbProtection();     
   }   
  }
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"


/*******************************************************************************
** Function Name        : IoHwAb_DigOutRead                                   **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          :                                                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : ChIdx                                               **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : Level                                               **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                          IoHwAb_GaaDigOutResultBuffer                      **
**                        Function(s) invoked    :                            **
**                          SchM_Enter_IoHwAb_IoHwAbProtection,               **
**                          SchM_Exit_IoHwAb_IoHwAbProtection                 **
*******************************************************************************/
/* @Trace: SRS_IoHwAb_12412 */
/* @Trace: IoHwAb_SUD_API_071 */

#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(void, IOHWAB_CODE)IoHwAb_DigOutRead(IoHwAb_IndexType ChIdx,
  P2VAR(IoHwAb_LevelType, AUTOMATIC, IOHWAB_APPL_DATA) Level)
{
  uint8 LucShiftBit = (uint8)(ChIdx % 8U);
  uint8 LucResBufIdx = (uint8)(ChIdx / 8U);
  
  if ((Level != NULL_PTR )&&(LucResBufIdx < IOHWAB_NUM_DIGOUT_RESULT_BUFFER)) 
  {
    SchM_Enter_IoHwAb_IoHwAbProtection();
    *Level = ((IoHwAb_GaaDigOutResultBuffer[LucResBufIdx].ucResult)
    & ((uint8)(1U << LucShiftBit))) >> LucShiftBit;
    SchM_Exit_IoHwAb_IoHwAbProtection();
  }
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"


/*******************************************************************************
** Function Name        : IoHwAb_DigOutReadDirect                             **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          :                                                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : ChIdx                                               **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : Level                                               **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                          IoHwAb_GaaGenInfos,                               **
**                          IoHwAb_GaaDigOutChIdx                             **
**                        Function(s) invoked    :                            **
**                          Dio_ReadChannel                                   **
*******************************************************************************/
/* @Trace: SRS_IoHwAb_12412 */
/* @Trace: SWS_IoHwAb_00078 */
/* @Trace: IoHwAb_SUD_API_072 */
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(void, IOHWAB_CODE)IoHwAb_DigOutReadDirect(IoHwAb_IndexType ChIdx,
  P2VAR(IoHwAb_LevelType, AUTOMATIC, IOHWAB_APPL_DATA) Level)
{
  Dio_LevelType LddDioChValue;
  if ( (ChIdx < IOHWAB_NUM_DIGOUT_MCU_LGC) && (Level != NULL_PTR) )
  {
    LddDioChValue = Dio_ReadChannel(
    IoHwAb_GaaGenInfos[IoHwAb_GaaDigOutChIdx[ChIdx]].ddDioChType);

    if (IoHwAb_GaaGenInfos[IoHwAb_GaaDigOutChIdx[ChIdx]].ucPolar == IOHWAB_POL_LOW)
    {
      if (LddDioChValue == STD_LOW)
      {
        *Level = IOHWAB_HIGH;
      }
      else
      {
        *Level = IOHWAB_LOW;
      }
    }
    else
    {
      if (LddDioChValue == STD_LOW)
      {
        *Level = IOHWAB_LOW;
      }
      else
      {
        *Level = IOHWAB_HIGH;
      }
    }
  }
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : IoHwAb_DigOutWriteOutputsToHW                       **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          :                                                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                          IoHwAb_GaaDigOutResultBuffer,                     **
**                          IoHwAb_GaaGenInfos,                               **
**                          IoHwAb_GaaDigOutChIdx                             **
**                        Function(s) invoked    :                            **
**                          Dio_ReadChannel,                                  **
**                          Dio_WriteChannel                                  **
**                          SchM_Enter_IoHwAb_IoHwAbProtection,               **
**                          SchM_Exit_IoHwAb_IoHwAbProtection                 **
*******************************************************************************/
/* @Trace: SWS_IoHwAb_00078 */
/* @Trace: IoHwAb_SUD_API_073 */
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(void, IOHWAB_CODE)IoHwAb_DigOutWriteOutputsToHW(void)
{
  IoHwAb_IndexType LucIdx;
  uint8 LucShiftBit;
  uint8 LucResBufIdx;
  uint8 LucPolarByte;
  uint8 LucPolarValue;
  Dio_LevelType LddDioChValue;

  for (LucIdx = 0; LucIdx < IOHWAB_NUM_DIGOUT_MCU_LGC; LucIdx++)
  {
    LucShiftBit  = (uint8)(LucIdx % 8U);
    LucResBufIdx = (uint8)(LucIdx / 8U);

    SchM_Enter_IoHwAb_IoHwAbProtection();

    if (IoHwAb_GaaGenInfos[IoHwAb_GaaDigOutChIdx[LucIdx]].ucPolar == IOHWAB_POL_LOW)
    {
      LucPolarByte = IoHwAb_GaaDigOutResultBuffer[LucResBufIdx].ucResult
        ^ ((uint8)(0x01U << LucShiftBit));
    }
    else
    {
      LucPolarByte = IoHwAb_GaaDigOutResultBuffer[LucResBufIdx].ucResult;
    }
    LucPolarValue = (LucPolarByte & ((uint8)(0x01U << LucShiftBit))) >> LucShiftBit;

    LddDioChValue = Dio_ReadChannel(
      IoHwAb_GaaGenInfos[IoHwAb_GaaDigOutChIdx[LucIdx]].ddDioChType);

    if (LddDioChValue != LucPolarValue)
    {
      IoHwAb_GaaDigOutResultBuffer[LucResBufIdx].ucTempResult = LucPolarByte;
      Dio_WriteChannel(
        IoHwAb_GaaGenInfos[IoHwAb_GaaDigOutChIdx[LucIdx]].ddDioChType,
        LucPolarValue);
    }

    SchM_Exit_IoHwAb_IoHwAbProtection();
  }
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : IoHwAb_DigOutGetFailure                             **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          :                                                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : ChIdx                                               **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LddError                                            **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                          IoHwAb_GaaDigOutL9826Infos,                       **
**                          IoHwAb_GaaParallelConfigInL9826                   **
**                          IoHwAb_GaaDiagInL9826                             **
**                        Function(s) invoked    : none                       **
*******************************************************************************/
/* @Trace: IoHwAb_SUD_API_074 */
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, IOHWAB_CODE)IoHwAb_DigOutGetFailure(
  IoHwAb_IndexType ChIdx)
{
  Std_ReturnType LddError = E_OK;

  #if (IOHWAB_USE_L9826_DIAG == STD_ON)
  uint8 LucShiftBit = (uint8)ChIdx % 8U;
  uint8 LucBufIdx = ( (uint8)ChIdx / 8U ) - IOHWAB_NUM_DIGOUT_MCU_BUFFER;

  if(LucBufIdx < IOHWAB_NUM_DIGOUT_L9826)
  {
    if (IoHwAb_GaaDigOutL9826ResultBuffer[LucBufIdx].blStartDiag == IOHWAB_FALSE)
    {
			LddError = E_OK;
    }
    else
    {
			if ((LucShiftBit == IOHWAB_THREE)
				&& ((IoHwAb_GaaDigOutL9826Infos[LucBufIdx].ucDefVal & 0x08U) == 0U))
			{
        LddError = IoHwAb_DigOutGetFailureBitThree(LucBufIdx, LucShiftBit);
			}
			else if ((LucShiftBit == IOHWAB_SEVEN)
				&& ((IoHwAb_GaaDigOutL9826Infos[LucBufIdx].ucDefVal & 0x80U) == 0U))
			{
        LddError = IoHwAb_DigOutGetFailureBitSeven(LucBufIdx, LucShiftBit);
			}
			else
			{
        LddError = IoHwAb_DigOutGetFailureBitOther(LucBufIdx, LucShiftBit);
			}
    }
  }
  #else
  IOHWAB_UNUSED(ChIdx);
  #endif /* (IOHWAB_USE_L9826_DIAG  == STD_ON) */

  return LddError;
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"

#if (IOHWAB_USE_L9826_DIAG == STD_ON)
/*******************************************************************************
** Function Name        : IoHwAb_DigOutGetFailureBitThree                     **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          :                                                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : ChIdx                                               **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LddError                                            **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                          IoHwAb_GaaDigOutL9826ResultBuffer                 **
**                        Function(s) invoked    : None                       **
*******************************************************************************/
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
static FUNC(Std_ReturnType, IOHWAB_CODE)IoHwAb_DigOutGetFailureBitThree(
  uint8 LucBufIdx, uint8 LucShiftBit)
{
  Std_ReturnType LddReturnValue;

  /* Pin 0 in parallel mode */
  if((IoHwAb_GaaDigOutL9826ResultBuffer[LucBufIdx].ucDiagSCGResult
    & ((uint8)(0x01U << LucShiftBit))) != 0)
  {
    LddReturnValue = RTE_E_IoHwAb_If_DigOut_E_PARALLEL;
  }
  else
  {
    LddReturnValue = E_OK;
  }

  return LddReturnValue;
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : IoHwAb_DigOutGetFailureBitSeven                     **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          :                                                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : ChIdx                                               **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LddError                                            **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                          IoHwAb_GaaDigOutL9826ResultBuffer                 **
**                        Function(s) invoked    : None                       **
*******************************************************************************/
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
static FUNC(Std_ReturnType, IOHWAB_CODE)IoHwAb_DigOutGetFailureBitSeven(
  uint8 LucBufIdx, uint8 LucShiftBit)
{
  Std_ReturnType LddReturnValue;

  /* Pin 1 in parallel mode */
  if((IoHwAb_GaaDigOutL9826ResultBuffer[LucBufIdx].ucDiagSCGResult
    & ((uint8)(0x01U << LucShiftBit))) != 0)		  
  {
    LddReturnValue = RTE_E_IoHwAb_If_DigOut_E_PARALLEL;	  
  }
  else
  {
      LddReturnValue = E_OK;		  
  }

  return LddReturnValue;
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : IoHwAb_DigOutGetFailureBitOther                     **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          :                                                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : ChIdx                                               **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LddError                                            **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                          IoHwAb_GaaDigOutL9826ResultBuffer                 **
**                        Function(s) invoked    : None                       **
*******************************************************************************/
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
static FUNC(Std_ReturnType, IOHWAB_CODE)IoHwAb_DigOutGetFailureBitOther(
  uint8 LucBufIdx, uint8 LucShiftBit)
{
  Std_ReturnType LddReturnValue;

  if((IoHwAb_GaaDigOutL9826ResultBuffer[LucBufIdx].ucDiagSCGResult
    & ((uint8)(0x01U << LucShiftBit))) != 0)
  {
    LddReturnValue = RTE_E_IoHwAb_If_DigOut_E_OL_SCG;	   
  }
  else
  {
    if((IoHwAb_GaaDigOutL9826ResultBuffer[LucBufIdx].ucDiagSCBResult
      & ((uint8)(0x01U << LucShiftBit))) != 0)
    {
      LddReturnValue = RTE_E_IoHwAb_If_DigOut_E_SCB;
    }
    else
    {
      LddReturnValue = E_OK;
    }
  }

  return LddReturnValue;
}

#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"
#endif /* (IOHWAB_USE_L9826_DIAG == STD_ON) */
#endif /* (IOHWAB_USE_DIG_OUT == STD_ON) */

/* polyspace-end RTE:UNR [Not a defect:Unset] "Reachable code" */
/* polyspace-end MISRA-C3:D4.14 [Justified:Unset] "The pointer is checked always." */
/* polyspace-end MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Unset] "It depends on the configuration" */
/* polyspace-end MISRA-C3:8.3 [Justified:Unset] "Prototypes are generated wrongly. It will be fixed soon" */
/* polyspace-end DEFECT:DEAD_CODE [Justified:Unset] "It depends on the configuration." */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/

