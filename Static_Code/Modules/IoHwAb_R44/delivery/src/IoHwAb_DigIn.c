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
**  SRC-MODULE: IoHwAb_DigIn.c                                                **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR IOHWAB                                                **
**                                                                            **
**  PURPOSE   : APIs implementation for IoHwAb module                         **
**              IoHwAb_DigInRead                                              **
**              IoHwAb_DigInReadRaw                                           **
**              IoHwAb_DigInReadDirect                                        **
**              IoHwAb_DigInWrite                                             **
**              IoHwAb_DigInFreeze                                            **
**              IoHwAb_DigInUnfreeze                                          **
**              IoHwAb_DigInIsFrozen                                          **
**              IoHwAb_DigInInit1                                             **
**              IoHwAb_DigInInit2                                             **
**              IoHwAb_DigInH2L                                               **
**              IoHwAb_DigInSampleLP                                          **
**              IoHwAb_DigInReadHwInputs                                      **
**              IoHwAb_DigInDebounce                                          **
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
** 1.3.0     16-Mar-2022  PhucNHM           R44-Redmine #24320                **
** 1.1.0     15-Jul-2021  YangJin.Kim       R44-Redmine #18100                **
** 1.0.0     04-Dec-2020  YangJin.Kim       R40-Redmine #26992                **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "IoHwAb_DigIn.h"
#include "IoHwAb_Config.h"
#include "HwResource.h"
#include "Rte_IoHwAb.h"
#if (IOHWAB_USE_MC33972 == STD_ON)
#include "IoHwAb_DigInMC33972.h"
#endif /* (IOHWAB_USE_MC33972 == STD_ON) */
#if (IOHWAB_USE_DIG_SUP_SWT == STD_ON)
#include "IoHwAb_InputSupply.h"
#endif /* (IOHWAB_USE_DIG_SUP_SWT == STD_ON) */
#include "SchM_IoHwAb.h"

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
#if (IOHWAB_USE_DIG_IN == STD_ON)
#define IOHWAB_START_SEC_VAR_CLEARED_8
#include "MemMap.h"
VAR(uint8, IOHWAB_VAR) IoHwAb_DigInFilteringStart; /* polyspace VARIABLE:* [Not a defect:Low] "System intended for multitasking" */
#define IOHWAB_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h"
#endif /* (IOHWAB_USE_DIG_IN == STD_ON) */

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
/* polyspace-begin RTE:UNR [Not a defect:Unset] "Reachable code" */
/* polyspace-begin MISRA-C3:D4.14 [Justified:Unset] "The pointer is checked always." */
/* polyspace-begin MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Unset] "It depends on the configuration" */
/* polyspace-begin MISRA-C3:8.3 [Justified:Unset] "Prototypes are generated wrongly. It will be fixed soon" */
/* polyspace-begin DEFECT:DEAD_CODE [Justified:Unset] "It depends on the configuration." */
/* polyspace-begin DEFECT:USELESS_IF [Justified:Unset] "It depends on the configuration" */
#if (IOHWAB_USE_DIG_IN == STD_ON)

static FUNC(uint8, IOHWAB_CODE)IoHwAb_DigInDebounceIncrement(
  uint8 LucTempFiltValue, uint8 LucDecInc, uint8 LucDecInc_4);

static FUNC(uint8, IOHWAB_CODE)IoHwAb_DigInDebounceDecrement(
  uint8 LucTempFiltValue, uint8 LucDecInc, uint8 LucDecInc_4);

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

/*******************************************************************************
** Function Name        : IoHwAb_DigInRead                                    **
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
**                          IoHwAb_GaaDigInFiltBuffer                         **
**                        Function(s) invoked    :                            **
**                          IOHWAB_DIGIN_GET_FILT_VAL,                        **
**                          SchM_Enter_IoHwAb_IoHwAbProtection,               **
**                          SchM_Exit_IoHwAb_IoHwAbProtection                 **
*******************************************************************************/

/* @Trace: SWR_IOHWAB_705_001_API */
/* @Trace: IoHwAb_SUD_API_086 */
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(void,IOHWAB_CODE)IoHwAb_DigInRead(IoHwAb_IndexType ChIdx,
  P2VAR(IoHwAb_LevelType, AUTOMATIC, IOHWAB_APPL_DATA) Level)
{
  SchM_Enter_IoHwAb_IoHwAbProtection();
  if ((Level != NULL_PTR) && (ChIdx < IOHWAB_NUM_DIGIN_LGC))
  {
    *Level = IOHWAB_DIGIN_GET_FILT_VAL(IoHwAb_GaaDigInFiltBuffer[ChIdx]);
  }
  SchM_Exit_IoHwAb_IoHwAbProtection();
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"


/*******************************************************************************
** Function Name        : IoHwAb_DigInReadRaw                                 **
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
**                          IoHwAb_GaaDigInFiltBuffer                         **
**                        Function(s) invoked    :                            **
**                          IOHWAB_DIGIN_GET_RAW_VAL,                         **
**                          SchM_Enter_IoHwAb_IoHwAbProtection,               **
**                          SchM_Exit_IoHwAb_IoHwAbProtection                 **
*******************************************************************************/

/* @Trace: SWS_IoHwAb_00019 SWR_IOHWAB_705_002_API */
/* @Trace: IoHwAb_SUD_API_087 */
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"

FUNC(void,IOHWAB_CODE)IoHwAb_DigInReadRaw(IoHwAb_IndexType ChIdx,
  P2VAR(IoHwAb_LevelType, AUTOMATIC, IOHWAB_APPL_DATA) Level)
{
  SchM_Enter_IoHwAb_IoHwAbProtection();
  if ((Level != NULL_PTR) && ( ChIdx < IOHWAB_NUM_DIGIN_LGC ))
  {
    *Level = IOHWAB_DIGIN_GET_RAW_VAL(IoHwAb_GaaDigInFiltBuffer[ChIdx]);
  }
  SchM_Exit_IoHwAb_IoHwAbProtection();
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"


/*******************************************************************************
** Function Name        : IoHwAb_DigInReadDirect                              **
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
**                          IoHwAb_GaaDigInInfos,                             **
**                          IoHwAb_GaaGenInfos                                **
**                        Function(s) invoked    :                            **
**                          Dio_ReadChannel                                   **
*******************************************************************************/

/* @Trace: SRS_IoHwAb_12338 SRS_IoHwAb_12319 */
/* @Trace: SWS_IoHwAb_00078 SWR_IOHWAB_703_005 SWR_IOHWAB_703_002 */
/* @Trace: IoHwAb_SUD_API_088 */
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(void,IOHWAB_CODE)IoHwAb_DigInReadDirect(IoHwAb_IndexType ChIdx,
  P2VAR(IoHwAb_LevelType, AUTOMATIC, IOHWAB_APPL_DATA) Level)
{
  if ( ChIdx < IOHWAB_NUM_DIGIN_LGC )
  {
    IoHwAb_IndexType LucChRefIdx = IoHwAb_GaaDigInInfos[ChIdx].ddRefChIdx;

    if (Level != NULL_PTR)
    {
      if (Dio_ReadChannel(IoHwAb_GaaGenInfos[LucChRefIdx].ddDioChType) == STD_LOW)
      {
        if (IoHwAb_GaaGenInfos[LucChRefIdx].ucPolar == IOHWAB_POL_LOW)
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
        if (IoHwAb_GaaGenInfos[LucChRefIdx].ucPolar == IOHWAB_POL_LOW)
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
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"


/*******************************************************************************
** Function Name        : IoHwAb_DigInWrite                                   **
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
**                          IoHwAb_GaaDigInFiltBuffer,                        **
**                          IoHwAb_GaaDigInInfos                              **
**                        Function(s) invoked    :                            **
**                          SchM_Enter_IoHwAb_IoHwAbProtection,               **
**                          SchM_Exit_IoHwAb_IoHwAbProtection                 **
*******************************************************************************/

/* @Trace: SWR_IOHWAB_705_003_API */
/* @Trace: IoHwAb_SUD_API_089 */
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(void,IOHWAB_CODE)IoHwAb_DigInWrite(IoHwAb_IndexType ChIdx,
  IoHwAb_LevelType Level)
{
  SchM_Enter_IoHwAb_IoHwAbProtection();
  if ( ChIdx < IOHWAB_NUM_DIGIN_LGC )
  {
    IoHwAb_GaaDigInFiltBuffer[ChIdx] &= IOHWAB_DIGIN_RESULT_COUNT_CLEAR_BIT_MASK;
    if (Level != 0)
    {
      IoHwAb_GaaDigInFiltBuffer[ChIdx]
        |= (IOHWAB_DIGIN_RESULT_SET_BIT_MASK
        | (IoHwAb_GaaDigInInfos[ChIdx].ucFiltConst & IOHWAB_DIGIN_COUNT_BIT_MASK));
    }
    else
    {
      IoHwAb_GaaDigInFiltBuffer[ChIdx]
        |= IoHwAb_GaaDigInInfos[ChIdx].ucFiltConst >> 4;
    }
  }
  SchM_Exit_IoHwAb_IoHwAbProtection();
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"


/*******************************************************************************
** Function Name        : IoHwAb_DigInFreeze                                  **
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
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                          IoHwAb_GaaDigInFiltBuffer                         **
**                        Function(s) invoked    :                            **
**                          SchM_Enter_IoHwAb_IoHwAbProtection,               **
**                          SchM_Exit_IoHwAb_IoHwAbProtection                 **
*******************************************************************************/

/* @Trace: SWR_IOHWAB_705_004_API */
/* @Trace: IoHwAb_SUD_API_090 */
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(void,IOHWAB_CODE)IoHwAb_DigInFreeze(IoHwAb_IndexType ChIdx)
{
  SchM_Enter_IoHwAb_IoHwAbProtection();
  if ( ChIdx < IOHWAB_NUM_DIGIN_LGC )
  {
    IoHwAb_GaaDigInFiltBuffer[ChIdx] |= IOHWAB_DIGIN_FREEZE_BIT_MASK;
  }
  SchM_Exit_IoHwAb_IoHwAbProtection();
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"


/*******************************************************************************
** Function Name        : IoHwAb_DigInUnfreeze                                **
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
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                          IoHwAb_GaaDigInFiltBuffer                         **
**                        Function(s) invoked    :                            **
**                          SchM_Enter_IoHwAb_IoHwAbProtection,               **
**                          SchM_Exit_IoHwAb_IoHwAbProtection                 **
*******************************************************************************/

/* @Trace: SWR_IOHWAB_705_005_API */
/* @Trace: IoHwAb_SUD_API_091 */
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(void,IOHWAB_CODE)IoHwAb_DigInUnfreeze(IoHwAb_IndexType ChIdx)
{
  SchM_Enter_IoHwAb_IoHwAbProtection();
  if (ChIdx < IOHWAB_NUM_DIGIN_LGC)
  {
    IoHwAb_GaaDigInFiltBuffer[ChIdx] &= IOHWAB_DIGIN_UNFREEZE_BIT_MASK;
  }
  SchM_Exit_IoHwAb_IoHwAbProtection();
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"


/*******************************************************************************
** Function Name        : IoHwAb_DigInIsFrozen                                **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          :                                                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : BufIdx, PortIdx, ChIdx                              **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : Result                                              **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                          IoHwAb_GaaDigInFiltBuffer                         **
**                        Function(s) invoked    :                            **
**                          IOHWAB_DIGIN_GET_FREEZE_VAL,                      **
**                          SchM_Enter_IoHwAb_IoHwAbProtection,               **
**                          SchM_Exit_IoHwAb_IoHwAbProtection                 **
*******************************************************************************/

/* @Trace: SWR_IOHWAB_705_006_API */
/* @Trace: IoHwAb_SUD_API_092 */
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(void,IOHWAB_CODE)IoHwAb_DigInIsFrozen(IoHwAb_IndexType ChIdx,
  P2VAR(IoHwAb_BoolType, AUTOMATIC, IOHWAB_APPL_DATA) DigInResult)
{
  SchM_Enter_IoHwAb_IoHwAbProtection();
  if ((DigInResult != NULL_PTR) && (ChIdx < IOHWAB_NUM_DIGIN_LGC))
  {
    *DigInResult = (IOHWAB_DIGIN_GET_FREEZE_VAL(IoHwAb_GaaDigInFiltBuffer[ChIdx]) == 0)
      ? IOHWAB_FALSE : IOHWAB_TRUE;
  }
  SchM_Exit_IoHwAb_IoHwAbProtection();
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"


/*******************************************************************************
** Function Name        : IoHwAb_DigInInit1                                   **
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
**                          IoHwAb_GaaDigInRawBuffer,                         **
**                          IoHwAb_GaaDigInFiltBuffer                         **
**                        Function(s) invoked    :                            **
**                          bidigdir_ReadHWInputs                             **
*******************************************************************************/
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
/* @Trace: IoHwAb_SUD_API_093 */
FUNC(void,IOHWAB_CODE)IoHwAb_DigInInit1(void)
{
  IoHwAb_IndexType LucIdx;
  IoHwAb_IndexType LucBufIdx;
  IoHwAb_IndexType LucShiftBit;

  /* acquisition of non multiplexed digital inputs   */
  IoHwAb_DigInReadHwInputs(FALSE);

  /* loop for updating all the inputs */
  for (LucIdx = 0U; LucIdx < IOHWAB_NUM_DIGIN_LGC; LucIdx++)
  {
    LucBufIdx = LucIdx / 8U;
    LucShiftBit = LucIdx % 8U;

    /* check the raw value */
    if( (IoHwAb_GaaDigInRawBuffer[LucBufIdx].ucRawBuffer 
      & ((uint8)(1U << LucShiftBit))) != 0U )
    {
      /* the raw value is 1 */
      /* update the counter 4 bits,bit R and bit F */
      IoHwAb_GaaDigInFiltBuffer[LucIdx] = 0x31U;
    }
    else
    {
      /* the raw value is 0 */
      /* update the counter 4 bits,bit R and bit F */
      IoHwAb_GaaDigInFiltBuffer[LucIdx] = 0x0EU;
    }
  }
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : IoHwAb_DigInInit2                                   **
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
**                          IoHwAb_GaaDigInFiltBuffer,                        **
**                          IoHwAb_GaaDigInInfos,                             **
**                          IoHwAb_DigInFilteringStart                        **
**                        Function(s) invoked    :                            **
**                          IoHwAb_InputSupplyDigitalControl,                 **
**                          IOHWAB_DIGIN_GET_FILT_VAL                         **
*******************************************************************************/
/* @Trace: IoHwAb_SUD_API_094 */
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(void,IOHWAB_CODE)IoHwAb_DigInInit2(void)
{
  IoHwAb_IndexType LucIdx;

  /* switch off switched battery for digital inputs */
  #if (IOHWAB_USE_DIG_SUP_SWT == STD_ON)
  IoHwAb_InputSupplyDigitalControl(TRUE, FALSE);
  #endif /* (IOHWAB_USE_DIG_SUP_SWT == STD_ON) */

  /* loop for updating all the inputs */
  for (LucIdx = 0; LucIdx < IOHWAB_NUM_DIGIN_LGC; LucIdx++)
  {
    IoHwAb_GaaDigInFiltBuffer[LucIdx] &= 0xF0U;

    /* check the filtered value */
    if ( (IOHWAB_DIGIN_GET_FILT_VAL(IoHwAb_GaaDigInFiltBuffer[LucIdx])) != 0U )
    {
      /* the filtered value is 1 */
      /* update the counter 4 bits keep unchanged R and F bits*/
      IoHwAb_GaaDigInFiltBuffer[LucIdx]
        |= IoHwAb_GaaDigInInfos[LucIdx].ucFiltConst & IOHWAB_DIGIN_COUNT_BIT_MASK;
    }
    else
    {
      /* the filtered value is 0 */
      /* update only the 4 bits of the counter (bits R and F are already 0) */
      IoHwAb_GaaDigInFiltBuffer[LucIdx]
        |= IoHwAb_GaaDigInInfos[LucIdx].ucFiltConst >> 4;
    }
  }

  IoHwAb_DigInFilteringStart = FALSE;
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : IoHwAb_DigInH2L                                     **
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
**                          IoHwAb_GaaDigInFiltBuffer,                        **
**                          IoHwAb_GaaDigInInfos                              **
**                        Function(s) invoked    :                            **
**                          IOHWAB_DIGIN_GET_FILT_VAL,                        **
**                          SchM_Enter_IoHwAb_IoHwAbProtection,               **
**                          SchM_Exit_IoHwAb_IoHwAbProtection                 **
*******************************************************************************/
/* @Trace: IoHwAb_SUD_API_095 */
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(void,IOHWAB_CODE)IoHwAb_DigInH2L(void)
{
  IoHwAb_IndexType LucIdx;

  for (LucIdx = 0; LucIdx < IOHWAB_NUM_DIGIN_LGC; LucIdx++)
  {
    /* service to protect from preemption and interrupts */
    SchM_Enter_IoHwAb_IoHwAbProtection();

    /* reset the counter value */
    IoHwAb_GaaDigInFiltBuffer[LucIdx] &= 0xF0U;

    if (IOHWAB_DIGIN_GET_FILT_VAL(IoHwAb_GaaDigInFiltBuffer[LucIdx]) != 0U )
    {
      /* set the counter to the maximum increment */
      IoHwAb_GaaDigInFiltBuffer[LucIdx]
        |= IoHwAb_GaaDigInInfos[LucIdx].ucFiltConst & IOHWAB_DIGIN_COUNT_BIT_MASK;
    }
    else
    {
      /* set the counter to the minimum decrement */
      IoHwAb_GaaDigInFiltBuffer[LucIdx]
        |= IoHwAb_GaaDigInInfos[LucIdx].ucFiltConst >> 4;
    }

    SchM_Exit_IoHwAb_IoHwAbProtection();
  }
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : IoHwAb_DigInSampleLP                                **
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
**                          IoHwAb_GaaDigInFiltBuffer,                        **
**                          IoHwAb_GaaDigInRawBuffer                          **
**                        Function(s) invoked    :                            **
**                          IOHWAB_DIGIN_GET_FREEZE_VAL,                      **
**                          SchM_Enter_IoHwAb_IoHwAbProtection,               **
**                          SchM_Exit_IoHwAb_IoHwAbProtection                 **
*******************************************************************************/
/* @Trace: SRS_IoHwAb_CUS_00003 */
/* @Trace: SWR_IOHWAB_703_003 */
/* @Trace: IoHwAb_SUD_API_097 */
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(void,IOHWAB_CODE)IoHwAb_DigInSampleLP(void)
{
  IoHwAb_IndexType LucIdx;
  IoHwAb_IndexType LucBufIdx;
  uint8 LucShiftBit;
  IoHwAb_IndexType LucStartIdx = IOHWAB_NUM_DIGIN_FAST_HIGH;
  IoHwAb_IndexType LucEndIdx = LucStartIdx + IOHWAB_NUM_DIGIN_SLOW;

  for (LucIdx = LucStartIdx; LucIdx < LucEndIdx; LucIdx++)
  {
    LucBufIdx   = (IoHwAb_IndexType)(LucIdx / 8U);
    LucShiftBit = (uint8)(LucIdx % 8U);

    /* disable interrupts */
    SchM_Enter_IoHwAb_IoHwAbProtection();

    /* update only if bit 6 E/D is 0 */
    if (IOHWAB_DIGIN_GET_FREEZE_VAL(IoHwAb_GaaDigInFiltBuffer[LucIdx]) == 0)
    {
      /* copy the raw data into the local mirror */
      if ( (IoHwAb_GaaDigInRawBuffer[LucBufIdx].ucRawBuffer 
         & ((uint8)(1U << LucShiftBit)) ) != 0U )
      {
        IoHwAb_GaaDigInFiltBuffer[LucIdx] |= IOHWAB_DIGIN_RAW_BIT_MASK;
      }
      else
      {
        IoHwAb_GaaDigInFiltBuffer[LucIdx] &= (uint8)(~(IOHWAB_DIGIN_RAW_BIT_MASK));
      }
    }
    /*  enable interrupts */
    SchM_Exit_IoHwAb_IoHwAbProtection();
  }
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : IoHwAb_DigInReadHwInputs                            **
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
**                          IoHwAb_GaaDigInInfos,                             **
**                          IoHwAb_GaaGenInfos,                               **
**                          IoHwAb_GaaDigInRawBuffer                          **
**                        Function(s) invoked    :                            **
**                          Dio_ReadChannel,                                  **
**                          SchM_Enter_IoHwAb_IoHwAbProtection,               **
**                          SchM_Exit_IoHwAb_IoHwAbProtection                 **
*******************************************************************************/
/* @Trace: IoHwAb_SUD_API_098 */
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(void,IOHWAB_CODE)IoHwAb_DigInReadHwInputs(boolean blFast)
{
  IoHwAb_IndexType LucIdx;
  IoHwAb_IndexType LucEndIdx;
  IoHwAb_IndexType LucBufIdx;
  IoHwAb_IndexType LucChRefIdx;
  uint8 LucShiftBit;
  uint8 LucShiftValue;
  Dio_LevelType LddDioChValue;

  if (blFast != 0U)
  {
     LucEndIdx = IOHWAB_NUM_DIGIN_FAST;
  }
  else
  {
  #if (IOHWAB_USE_MC33972 == STD_ON)
    LucEndIdx = IOHWAB_NUM_DIGIN_LGC - IOHWAB_NUM_DIGIN_MC33972_LGC;
  #else /* (IOHWAB_USE_MC33972 == STD_ON) */
    LucEndIdx = IOHWAB_NUM_DIGIN_LGC;
  #endif /* (IOHWAB_USE_MC33972 == STD_ON) */
  }

  /* loop to read all ports with digital inputs */
  for (LucIdx = 0; LucIdx < LucEndIdx; LucIdx++)
  {
    LucBufIdx     = (IoHwAb_IndexType)(LucIdx / 8U);
    LucShiftBit   = (uint8)(LucIdx % 8U);
    LucShiftValue = (uint8)(1U << LucShiftBit);
    LucChRefIdx   = IoHwAb_GaaDigInInfos[LucIdx].ddRefChIdx;

    /* service to protect from preemption and interrupts */
    SchM_Enter_IoHwAb_IoHwAbProtection();

    LddDioChValue = Dio_ReadChannel(IoHwAb_GaaGenInfos[LucChRefIdx].ddDioChType);

    IoHwAb_GaaDigInRawBuffer[LucBufIdx].ucTempBuffer
      &= (uint8)(~(LucShiftValue));
    IoHwAb_GaaDigInRawBuffer[LucBufIdx].ucRawBuffer
      &= (uint8)(~(LucShiftValue));

    if (LddDioChValue == 0)
    {
      if (IoHwAb_GaaGenInfos[LucChRefIdx].ucPolar == IOHWAB_POL_LOW)
      {
        IoHwAb_GaaDigInRawBuffer[LucBufIdx].ucRawBuffer
          |= LucShiftValue;
      }
    }
    else
    {
      IoHwAb_GaaDigInRawBuffer[LucBufIdx].ucTempBuffer
        |= LucShiftValue;
      if (IoHwAb_GaaGenInfos[LucChRefIdx].ucPolar == IOHWAB_POL_HIGH)
      {
        IoHwAb_GaaDigInRawBuffer[LucBufIdx].ucRawBuffer
          |= LucShiftValue;
      }
    }

    /* service to exit the protected area */
    SchM_Exit_IoHwAb_IoHwAbProtection();
  }
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : IoHwAb_DigInDebounce                                **
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
**                          IoHwAb_GaaDigInInfos,                             **
**                          IoHwAb_GaaGenInfos,                               **
**                          IoHwAb_GaaDigInRawBuffer                          **
**                        Function(s) invoked    :                            **
**                          Dio_ReadChannel,                                  **
**                          SchM_Enter_IoHwAb_IoHwAbProtection,               **
**                          SchM_Exit_IoHwAb_IoHwAbProtection,                **
**                          IoHwAb_DigInDebounceIncrement,                    **
**                          IoHwAb_DigInDebounceDecrement                     **
*******************************************************************************/
/* @Trace: SWR_IOHWAB_704_004 SWS_IoHwAb_00021 */
/* @Trace: IoHwAb_SUD_API_096 */
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(void,IOHWAB_CODE)IoHwAb_DigInDebounce(IoHwAb_IndexType Idx,
  IoHwAb_IndexType NumFilt)
{
  uint8 LucDecInc;
  uint8 LucDecInc_4;
  IoHwAb_IndexType LucBufIdx;
  uint8 LucShiftBit;
  uint8 LucRawValue;
  uint8 LucTempFiltValue;

  IoHwAb_IndexType LucIdx = Idx;
  IoHwAb_IndexType LucNumFilt = NumFilt;

  /* calculate the absolute index of the last input to process */
  LucNumFilt += LucIdx;

  /* loop to process all required inputs */
  for (; LucIdx < LucNumFilt; LucIdx++)
  {
    LucBufIdx = (IoHwAb_IndexType)(LucIdx / 8U);
    LucShiftBit = (uint8)(LucIdx % 8U);

    /* proceed only if LucBufIdx is in valid range */
    if(LucBufIdx < IOHWAB_NUM_DIGIN_RAW_BUFFER)
    {
      if ((IoHwAb_GaaDigInRawBuffer[LucBufIdx].ucRawBuffer & ((uint8)(1U << LucShiftBit))) != 0U)
      {
        LucRawValue = 1U;
      }
      else
      {
        LucRawValue = 0U;
      }

      /*update and process only if bit with the current raw value are different to bit with filtered value */
      if( (LucIdx < IOHWAB_NUM_DIGIN_LGC) &&
          ((!(LucRawValue == IOHWAB_DIGIN_GET_FILT_VAL(IoHwAb_GaaDigInFiltBuffer[LucIdx])))
            || (!(LucRawValue == IOHWAB_DIGIN_GET_RAW_VAL(IoHwAb_GaaDigInFiltBuffer[LucIdx])))) )
      {
        /* update and process only if bit 6 E/D is 0*/
        if (IOHWAB_DIGIN_GET_FREEZE_VAL(IoHwAb_GaaDigInFiltBuffer[LucIdx]) == 0U)
        {
          /* initialization filtering or task filtering */
          if (IoHwAb_DigInFilteringStart != 0U)
          {
            /* initialization filtering */
            LucDecInc = 0x01U;
            LucDecInc_4 = 0x0EU;
          }
          else
          {
            /* task filtering */
            LucDecInc = IoHwAb_GaaDigInInfos[LucIdx].ucFiltConst & IOHWAB_DIGIN_COUNT_BIT_MASK;
            LucDecInc_4 = IoHwAb_GaaDigInInfos[LucIdx].ucFiltConst >> 4;
          }

          /* service to protect from preemption and interrupts */
          SchM_Enter_IoHwAb_IoHwAbProtection();

          /* copy the current counter into static mirror */
          LucTempFiltValue = IoHwAb_GaaDigInFiltBuffer[LucIdx];

          /* copy the raw data into the local mirror */
          if (LucRawValue != 0U)
          {
            LucTempFiltValue = IoHwAb_DigInDebounceIncrement(LucTempFiltValue, LucDecInc, LucDecInc_4);
          }
          else
          {
            LucTempFiltValue = IoHwAb_DigInDebounceDecrement(LucTempFiltValue, LucDecInc, LucDecInc_4);
          }/* increment or decrement */

          /* update the filtered input value */
          IoHwAb_GaaDigInFiltBuffer[LucIdx] = LucTempFiltValue;

          /* service to exit the protected area */
          SchM_Exit_IoHwAb_IoHwAbProtection();
        }
      }
    }
  }
}

/*******************************************************************************
** Function Name        : IoHwAb_DigInDebounceIncrement                       **
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
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : None                       **
*******************************************************************************/
static FUNC(uint8, IOHWAB_CODE)IoHwAb_DigInDebounceIncrement(
  uint8 LucTempFiltValue, uint8 LucDecInc, uint8 LucDecInc_4)
{
  uint8 LucReturnValue;

  /* this is an increment */
  /* set the raw bit to 1 */
  LucReturnValue = LucTempFiltValue | IOHWAB_DIGIN_RAW_BIT_MASK;

  /* filter the data only if this is a filtered input for 0->1 transition */
  if ( LucDecInc_4 != 0U )
  {
    /* this is a filtered input */
    if (IOHWAB_DIGIN_GET_FILT_VAL(LucReturnValue) != 0U)
    {
      /* input already 1 */
      /* set the counter to the maximum increment */
      LucReturnValue &= 0xF0U;
      LucReturnValue |= LucDecInc;
    }
    else
    {
      /* input not 1 yet, increment the filter */
      LucReturnValue++;

      /* if bit 4 = 1, transition */
      if (IOHWAB_DIGIN_GET_FILT_VAL(LucReturnValue) != 0U)
      {
        /* set the counter to the maximum increment */
        LucReturnValue &= 0xF0U;
        LucReturnValue |= LucDecInc;
      }
    }
  }
  else
  {
    /* not filtered for 0->1 transition */
    /* set the F bit and the counter to the maximum increment */
    LucReturnValue &= 0xF0U;
    LucReturnValue |= (0x10U | LucDecInc);
  }/* filtered or not */

  return LucReturnValue;
}

/*******************************************************************************
** Function Name        : IoHwAb_DigInDebounceDecrement                       **
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
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : None                       **
*******************************************************************************/
static FUNC(uint8, IOHWAB_CODE)IoHwAb_DigInDebounceDecrement(
  uint8 LucTempFiltValue, uint8 LucDecInc, uint8 LucDecInc_4)
{
  uint8 LucReturnValue;

  /* this is a decrement */
  LucReturnValue = LucTempFiltValue & (uint8)(~(IOHWAB_DIGIN_RAW_BIT_MASK));
  /* filter the data only if this is a filtered input */
  if(LucDecInc != 0U)
  {
    /* this is filtered for 1->0 transition */
    if (IOHWAB_DIGIN_GET_FILT_VAL(LucReturnValue) == 0U)
    {
      /* input already 0 */
      /* set the counter to the minimum decrement */
      LucReturnValue &= 0xF0U;
      LucReturnValue |= LucDecInc_4;
    }
    else
    {
      /* input not 0 yet, decrement the filter */
      LucReturnValue--;

      /* if bit 4 = 0, transition */
      if ( IOHWAB_DIGIN_GET_FILT_VAL(LucReturnValue) == 0U)
      {
        /* set the counter to the minimum decrement */
        LucReturnValue &= 0xF0U;
        LucReturnValue |= LucDecInc_4;
      }
    }
  }
  else
  {
    /* this is not filtered for 1->0 transition */
    /* reset the F bit and set the counter to the minimum decrement */
    LucReturnValue &= 0xE0U;
    LucReturnValue |= LucDecInc_4;
  }/* filtered or not */

  return LucReturnValue;
}

#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"

#endif /* (IOHWAB_USE_DIG_IN == STD_ON) */

/* polyspace-end RTE:UNR [Not a defect:Unset] "Reachable code" */
/* polyspace-end MISRA-C3:D4.14 [Justified:Unset] "The pointer is checked always." */
/* polyspace-end MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Unset] "It depends on the configuration" */
/* polyspace-end MISRA-C3:8.3 [Justified:Unset] "Prototypes are generated wrongly. It will be fixed soon" */
/* polyspace-end DEFECT:DEAD_CODE [Justified:Unset] "It depends on the configuration." */
/* polyspace-end DEFECT:USELESS_IF [Justified:Unset] "It depends on the configuration" */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
