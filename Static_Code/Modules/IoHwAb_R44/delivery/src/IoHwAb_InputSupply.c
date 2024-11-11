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
**  SRC-MODULE: IoHwAb_InputSupply.c                                          **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR IOHWAB                                                **
**                                                                            **
**  PURPOSE   : APIs implementation for Input Supply module                   **
**              IoHwAb_InputSupplyInit                                        **
**              IoHwAb_InputSupplyDigitalControl                              **
**              IoHwAb_InputSupplySwControl                                   **
**              IoHwAb_InputSupplyAnalogControl                               **
**                                                                            **
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
** 1.7.1     10-May-2024  YongEun.Lee       #CP44-7556                        **
** 1.3.2     10-Aug-2022  KhaLN1            #CP44-731                         **
** 1.3.0.1   30-Jun-2022  KhaLN1            #CP44-365                         **
** 1.3.0     16-Mar-2022  PhucNHM           R44-Redmine #24320                **
** 1.1.0     15-Jul-2021  YangJin.Kim       R44-Redmine #18100                **
** 1.0.0     04-Dec-2020  YangJin.Kim       R40-Redmine #26992                **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "IoHwAb_InputSupply.h"
#include "IoHwAb_Config.h"
#include "Rte_IoHwAb.h"

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
#if (IOHWAB_USE_IN_SUP_SWT == STD_ON)
#define IOHWAB_START_SEC_VAR_CLEARED_8
#include "MemMap.h"
static VAR(boolean, IOHWAB_VAR) IoHwAb_GblInputSupplySwBusy; /* polyspace VARIABLE:* [Not a defect:Low] "System intended for multitasking" */
#define IOHWAB_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h"
#endif /* (IOHWAB_USE_IN_SUP_SWT == STD_ON) */
/* polyspace-begin RTE:UNR [Not a defect:Unset] "Reachable code" */
/* polyspace-begin MISRA-C3:8.3 [Justified:Unset] "Prototypes are generated wrongly. It will be fixed soon" */
/* polyspace-begin DEFECT:DEAD_CODE [Justified:Unset] "It depends on the configuration." */
/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

#if (IOHWAB_USE_IN_SUP_SWT == STD_ON)
/*******************************************************************************
** Function Name        : IoHwAb_InputSupplyInit                              **
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
**                        Function(s) invoked    : none                       **
*******************************************************************************/
/* @Trace: SRS_IoHwAb_CUS_00005 */
/* @Trace: SWR_IOHWAB_712_001 SWR_IOHWAB_712_002 */
/* @Trace: IoHwAb_SUD_API_099 */
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(void, IOHWAB_CODE)IoHwAb_InputSupplyInit(void)
{
  IoHwAb_IndexType LucIdx;

  for (LucIdx = 0; LucIdx < IOHWAB_NUM_ISUPPLY; LucIdx++)
  {
    /* Set the initial value for Input supply switch (raub_ISSwitchControl) */
    IoHwAb_GblInputSupplySwControl[LucIdx]
      = IoHwAb_GaaInputSupplyInfos[LucIdx].ucInitMode;
  }
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"

#if (IOHWAB_USE_DIG_IN == STD_ON) 
#if (IOHWAB_USE_DIG_SUP_SWT == STD_ON)
/*******************************************************************************
** Function Name        : IoHwAb_InputSupplyDigitalControl                    **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          :                                                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : blHp, blOn                                          **
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
**                        Function(s) invoked    : none                       **
*******************************************************************************/
/* @Trace: SRS_IoHwAb_CUS_00005 */
/* @Trace: SWR_IOHWAB_713_001_API */
/* @Trace: IoHwAb_SUD_API_0100 */
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(void, IOHWAB_CODE)IoHwAb_InputSupplyDigitalControl(
  boolean blHp, boolean blOn)
{
  if ( (blOn == 0) || (blHp == 0))
  {
    /* Do nothing, work around for error compiler -Werror=unused-parameter */
  }

  IoHwAb_IndexType LucIdx;
  IoHwAb_IndexType LucEndIdx;
  IoHwAb_IndexType LucChRefIdx;
  boolean LblDoCtrl = TRUE;
  Dio_LevelType LddLevel;

  #if (IOHWAB_USE_DIG_SUP_SWT_LP == STD_ON)
  if (blHp == 0U)
  {
    LucEndIdx = IOHWAB_NUM_ISUPPLY_DIG_IN_LP;
  }
  else
  #endif /* (IOHWAB_USE_DIG_SUP_SWT_LP == STD_ON) */
  {
    LucEndIdx = IOHWAB_NUM_ISUPPLY_DIG;
  }

  if (blOn != 0U)
  {
    IoHwAb_GblInputSupplySwBusy = TRUE;
  }
  else
  {
    IoHwAb_GblInputSupplySwBusy = FALSE;
  }

  for (LucIdx = 0U; LucIdx < LucEndIdx; LucIdx++)
  {
    LucChRefIdx = IoHwAb_GaaInputSupplyInfos[LucIdx].ddRefChIdx;
    /* polyspace +2 MISRA-C3:14.3 [Not a defect:Low] "It depends on the configuration" */
    /* polyspace +1 MISRA-C3:2.1 [Not a defect:Low] "It depends on the configuration" */
    if ((IoHwAb_GaaInputSupplyInfos[LucIdx].blUseInApp == TRUE)
      && (IoHwAb_GblInputSupplySwControl[LucIdx] == IOHWAB_IS_SW_OFF))
    {
      LblDoCtrl = FALSE;
    }
    /* polyspace +2 MISRA-C3:14.3 [Not a defect:Low] "It depends on the configuration" */
    /* polyspace +1 DEFECT:USELESS_IF [Not a defect:Medium] "It depends on the configuration" */
    if (LblDoCtrl != 0U)
    {
      if (blOn != 0U)
      {
        LddLevel = ( (IoHwAb_GaaGenInfos[LucChRefIdx].ucPolar == IOHWAB_POL_LOW)
          ? (Dio_LevelType)STD_LOW : (Dio_LevelType)STD_HIGH );
      }
      else
      {
        LddLevel = ( (IoHwAb_GaaGenInfos[LucChRefIdx].ucPolar == IOHWAB_POL_LOW)
          ? (Dio_LevelType)STD_HIGH : (Dio_LevelType)STD_LOW );
      }

      Dio_WriteChannel(IoHwAb_GaaGenInfos[LucChRefIdx].ddDioChType, LddLevel);
    }
  }
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : IoHwAb_InputSupplySwControl                         **
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
** Return parameter     : LddError                                            **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Function(s) invoked    : none                       **
*******************************************************************************/
/* @Trace: SRS_IoHwAb_CUS_00005 */
/* @Trace: IoHwAb_SUD_API_0101 */
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, IOHWAB_CODE)IoHwAb_InputSupplySwControl(
  IoHwAb_IndexType ChIdx, IoHwAb_LevelType Level)
{
  Std_ReturnType LddError = E_OK;

  if ((IoHwAb_GblInputSupplySwBusy != 0U) || (ChIdx >= IOHWAB_NUM_ISUPPLY))
  {
    LddError = RTE_E_IoHwAb_If_InputSupply_E_BUSY;
  }
  else 
  {
    /* polyspace +2 MISRA-C3:14.3 [Not a defect:Low] "It depends on the configuration" */
    /* polyspace +1 MISRA-C3:2.1 [Not a defect:Low] "It depends on the configuration" */
    if (IoHwAb_GaaInputSupplyInfos[ChIdx].blUseInApp == TRUE)
    {
      if (Level != 0U)
      {
        IoHwAb_GblInputSupplySwControl[ChIdx] = IOHWAB_IS_SW_ON;
      }
      else
      {
        IoHwAb_GblInputSupplySwControl[ChIdx] = IOHWAB_IS_SW_OFF;
      }
    }
  }

  return LddError;
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"
#endif /* (IOHWAB_USE_DIG_SUP_SWT == STD_ON) */
#endif /* (IOHWAB_USE_DIG_IN == STD_ON) */

#if (IOHWAB_USE_ANA_IN == STD_ON)
#if (IOHWAB_USE_ANA_SUP_SWT == STD_ON)
/*******************************************************************************
** Function Name        : IoHwAb_InputSupplyAnalogControl                     **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          :                                                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : blHp, blOn                                          **
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
**                        Function(s) invoked    : none                       **
*******************************************************************************/
/* @Trace: SRS_IoHwAb_CUS_00005 */
/* @Trace: IoHwAb_SUD_API_0102 */
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(void, IOHWAB_CODE)IoHwAb_InputSupplyAnalogControl(boolean blOn)
{
  IoHwAb_IndexType LucIdx;
  IoHwAb_IndexType LucChRefIdx;
  Dio_LevelType LddLevel;

  for (LucIdx = IOHWAB_NUM_ISUPPLY_DIG; LucIdx < IOHWAB_NUM_ISUPPLY; LucIdx++)
  {
    LucChRefIdx = IoHwAb_GaaInputSupplyInfos[LucIdx].ddRefChIdx;

    /* For analog blUseInApp is always 'FALSE' by default, condition checking is redundant and removed */
    if (blOn != 0U)
    {
	  LddLevel = ( (IoHwAb_GaaGenInfos[LucChRefIdx].ucPolar == IOHWAB_POL_LOW)
	    ? (Dio_LevelType)STD_LOW : (Dio_LevelType)STD_HIGH );
    }
    else
    {
	  LddLevel = ( (IoHwAb_GaaGenInfos[LucChRefIdx].ucPolar == IOHWAB_POL_LOW)
	    ? (Dio_LevelType)STD_HIGH : (Dio_LevelType)STD_LOW );
    }

    Dio_WriteChannel(IoHwAb_GaaGenInfos[LucChRefIdx].ddDioChType, LddLevel);

  }
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"

#endif /* (IOHWAB_USE_ANA_SUP_SWT == STD_ON) */
#endif /* (IOHWAB_USE_ANA_IN == STD_ON) */

#endif /* (IOHWAB_USE_IN_SUP_SWT == STD_ON) */
/* polyspace-end RTE:UNR [Not a defect:Unset] "Reachable code" */
/* polyspace-end MISRA-C3:8.3 [Justified:Unset] "Prototypes are generated wrongly. It will be fixed soon" */
/* polyspace-end DEFECT:DEAD_CODE [Justified:Unset] "It depends on the configuration." */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
