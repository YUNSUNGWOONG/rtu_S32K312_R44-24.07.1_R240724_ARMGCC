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
**  SRC-MODULE: IoHwAb_Gpt.c                                                  **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR IOHWAB                                                **
**                                                                            **
**  PURPOSE   : APIs implementation for IoHwAb module                         **
**              IoHwAb_GptStartTimer                                          **
**              IoHwAb_GptStopTimer                                           **
**              IoHwAb_GptGetTimeElapsed                                      **
**              IoHwAb_GptGetTimeRemaining                                    **
**              IoHwAb_GptDisableNotification                                 **
**              IoHwAb_GptEnableNotification                                 **
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
** 1.3.0.1   30-Jun-2022  KhaLN1            #CP44-365                         **
** 1.1.0     15-Jul-2021  YangJin.Kim       R44-Redmine #18100                **
** 1.0.0     04-Dec-2020  YangJin.Kim       R40-Redmine #26992                **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "IoHwAb_Gpt.h"
#include "Rte_IoHwAb.h"
#include "IoHwAb_Config.h"
#if (IOHWAB_USE_GPT == STD_ON)
#include "Gpt.h"
#endif /* (IOHWAB_USE_GPT == STD_ON) */

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
/*polyspace:begin<RTE: IDP : Not a defect : No Action Planned >  */
/*polyspace:begin<RTE: NIV : Not a defect : No Action Planned >  */ 
/* polyspace-begin MISRA-C3:D4.14 [Justified:Unset] "The pointer is checked always." */
/* polyspace-begin MISRA-C3:8.3 [Justified:Unset] "Prototypes are generated wrongly. It will be fixed soon" */
/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#if (IOHWAB_USE_GPT == STD_ON)
/*******************************************************************************
** Function Name        : IoHwAb_GptStartTimer                                **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          : This Service starts the timer of the corresponding  **
**                        GPT channel.                                        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : ChIdx, Value                                        **
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
**                          IoHwAb_GaaGptChIdx                                **
**                        Function(s) invoked    :                            **
**                          IoHwAb_GpGptStartTimer                            **
*******************************************************************************/
/* @Trace: SWS_IoHwAb_00078 SWR_IOHWAB_501_001 */
/* @Trace: IoHwAb_SUD_API_035 */
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, IOHWAB_CODE)IoHwAb_GptStartTimer(IoHwAb_IndexType ChIdx,
  IoHwAb_GptValueType Value)
{
  Std_ReturnType LddError = E_OK;

  if ((IoHwAb_GpGptStartTimer != IOHWAB_NULL_PTR) &&
      (ChIdx < IOHWAB_GPT_NUM_LGC))
  {
    IoHwAb_GpGptStartTimer(IoHwAb_GaaGptChIdx[ChIdx], (Gpt_ValueType)Value);
  }
  else
  {
    LddError = RTE_E_IoHwAb_If_Gpt_E_NOT_SUPPORTED;
  }

  return LddError;
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : IoHwAb_GptStopTimer                                 **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          : This Service stops the timer of the corresponding   **
**                        GPT channel.                                        **
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
**                          IoHwAb_GaaGptChIdx                                **
**                        Function(s) invoked    :                            **
**                          IoHwAb_GpGptStopTimer                             **
*******************************************************************************/
/* @Trace: SWS_IoHwAb_00078 SWR_IOHWAB_501_002 */
/* @Trace: IoHwAb_SUD_API_036 */
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, IOHWAB_CODE)IoHwAb_GptStopTimer(IoHwAb_IndexType ChIdx)
{
  Std_ReturnType LddError = E_OK;

  if ((IoHwAb_GpGptStopTimer != IOHWAB_NULL_PTR)&&
      (ChIdx < IOHWAB_GPT_NUM_LGC))
  {
    IoHwAb_GpGptStopTimer(IoHwAb_GaaGptChIdx[ChIdx]);
  }
  else
  {
    LddError = RTE_E_IoHwAb_If_Gpt_E_NOT_SUPPORTED;
  }

  return LddError;
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : IoHwAb_GptGetTimeElapsed                            **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          : This Service reads the elapsed time value of the    **
**                        corresponding GPT channel.                          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : ChIdx                                               **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : Value                                               **
**                                                                            **
** Return parameter     : LddError                                            **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                          IoHwAb_GaaGptChIdx                                **
**                        Function(s) invoked    :                            **
**                          IoHwAb_GpGptGetTimeElapsed                        **
*******************************************************************************/
/* @Trace: SWS_IoHwAb_00078 SWR_IOHWAB_502_001 */
/* @Trace: IoHwAb_SUD_API_037 */
#if (IOHWAB_GPT_TIME_ELAPSED_API == STD_ON)
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, IOHWAB_CODE)IoHwAb_GptGetTimeElapsed(IoHwAb_IndexType ChIdx,
  P2VAR(IoHwAb_GptValueType, AUTOMATIC, IOHWAB_APPL_DATA) Value)
{
  Std_ReturnType LddError = E_OK;

  if ((IoHwAb_GpGptGetTimeElapsed != IOHWAB_NULL_PTR) && (Value != NULL_PTR) &&
      (ChIdx < IOHWAB_GPT_NUM_LGC))
  {
    *Value = (IoHwAb_GptValueType)IoHwAb_GpGptGetTimeElapsed(IoHwAb_GaaGptChIdx[ChIdx]);
  }
  else
  {
    LddError = RTE_E_IoHwAb_If_Gpt_E_NOT_SUPPORTED;
  }

  return LddError;
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"
#endif /*(IOHWAB_GPT_TIME_ELAPSED_API == STD_ON)*/

/*******************************************************************************
** Function Name        : IoHwAb_GptGetTimeRemaining                          **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          : This Service reads the remaining time value of the  **
**                        corresponding GPT channel.                          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : ChIdx                                               **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : Value                                               **
**                                                                            **
** Return parameter     : LddError                                            **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                          IoHwAb_GaaGptChIdx                                **
**                        Function(s) invoked    :                            **
**                          IoHwAb_GpGptGetTimeRemaining                      **
*******************************************************************************/
/* @Trace: SRS_IoHwAb_CUS_00001 */
/* @Trace: SWS_IoHwAb_00078 SWR_IOHWAB_502_002 */
/* @Trace: IoHwAb_SUD_API_038 */
#if (IOHWAB_GPT_TIME_REMAINING_API == STD_ON)
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, IOHWAB_CODE)IoHwAb_GptGetTimeRemaining(IoHwAb_IndexType ChIdx,
  P2VAR(IoHwAb_GptValueType, AUTOMATIC, IOHWAB_APPL_DATA) Value)
{
  Std_ReturnType LddError = E_OK;

  if ((IoHwAb_GpGptGetTimeRemaining != IOHWAB_NULL_PTR) && (Value != NULL_PTR) &&
      (ChIdx < IOHWAB_GPT_NUM_LGC))
  {
    *Value = (IoHwAb_GptValueType)IoHwAb_GpGptGetTimeRemaining(IoHwAb_GaaGptChIdx[ChIdx]);
  }
  else
  { 
    LddError = RTE_E_IoHwAb_If_Gpt_E_NOT_SUPPORTED;
  }

  return LddError;
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"
#endif /*(IOHWAB_GPT_TIME_REMAINING_API == STD_ON)*/

/*******************************************************************************
** Function Name        : IoHwAb_GptDisableNotification                       **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          : This Service disables notification feature of the   **
**                        corresponding GPT channel.                          **
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
**                          IoHwAb_GaaGptChIdx                                **
**                        Function(s) invoked    :                            **
**                          IoHwAb_GpGptDisableNotification                   **
*******************************************************************************/
/* @Trace: SRS_IoHwAb_CUS_00001 */
/* @Trace: SWS_IoHwAb_00078 SWR_IOHWAB_503_002 */
/* @Trace: IoHwAb_SUD_API_039 */
#if (IOHWAB_GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON)
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, IOHWAB_CODE)IoHwAb_GptDisableNotification(IoHwAb_IndexType ChIdx)
{
  Std_ReturnType LddError = E_OK;

  if ((IoHwAb_GpGptDisableNotification != IOHWAB_NULL_PTR) &&
      (ChIdx < IOHWAB_GPT_NUM_LGC))
  {
    IoHwAb_GpGptDisableNotification(IoHwAb_GaaGptChIdx[ChIdx]);
  }
  else
  {
    LddError = RTE_E_IoHwAb_If_Gpt_E_NOT_SUPPORTED;
  }

  return LddError;
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"
#endif /*(IOHWAB_GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON)*/

/*******************************************************************************
** Function Name        : IoHwAb_GptEnableNotification                        **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          : This Service enables notification feature of the    **
**                        corresponding GPT channel.                          **
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
**                          IoHwAb_GaaGptChIdx                                **
**                        Function(s) invoked    :                            **
**                          IoHwAb_GpGptEnableNotification                    **
*******************************************************************************/
/* @Trace: SRS_IoHwAb_CUS_00001 */
/* @Trace: SWS_IoHwAb_00078 SWS_IoHwAb_00107 SWR_IOHWAB_503_001 */
/* @Trace: SWS_IoHwAb_00124 */
/* @Trace: IoHwAb_SUD_API_040 */
#if (IOHWAB_GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON)
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, IOHWAB_CODE)IoHwAb_GptEnableNotification(IoHwAb_IndexType ChIdx)
{
  Std_ReturnType LddError = E_OK;

  if ((IoHwAb_GpGptEnableNotification != IOHWAB_NULL_PTR) &&
      (ChIdx < IOHWAB_GPT_NUM_LGC))
  {
    IoHwAb_GpGptEnableNotification(IoHwAb_GaaGptChIdx[ChIdx]);
  }
  else
  {
    LddError = RTE_E_IoHwAb_If_Gpt_E_NOT_SUPPORTED;
  }

  return LddError;
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"
#endif /*(IOHWAB_GPT_ENABLE_DISABLE_NOTIFICATION_API == STD_ON)*/
#endif /* (IOHWAB_USE_GPT == STD_ON) */


/*polyspace:begin<MISRA-C:11.3:Not a defect:Justify with annotations> No Impact of this rule violation*/
/*******************************************************************************
** Function Name        : IoHwAb_PreModeChange (Bolero Only)                  **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          : This Service covers Bolero errat #e7953             **
**                        This Api should be called before the Mcu_InitClock. **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : PIT_TIE_STATUS                                      **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Function(s) invoked    :                            **
*******************************************************************************/
#if defined(IOHWAB_MCAL_FREESCALE_MPC560XB)
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(void, IOHWAB_CODE)IoHwAb_GptPreModeChange(
  P2VAR(IoHwAb_IndexType, AUTOMATIC, IOHWAB_APPL_DATA) PIT_TIE_STATUS)
{
  uint16  LusPitChIdx;
  uint16  LusPitTieStatus = 0U;
  
  for( LusPitChIdx = 0U; LusPitChIdx < GPT_PIT_CHAN_NUM; LusPitChIdx++)
  {
    if((( REG_READ32(PIT_TCTRL(LusPitChIdx)))&((uint32)PIT_TCTRL_TIE)) == (uint32)PIT_TCTRL_TIE )
    {
      PIT_INTERRUPT_DISABLE(LusPitChIdx);
      LusPitTieStatus |= (uint16)((uint16)1 << (uint16)LusPitChIdx);      
    }
  }
  if (PIT_TIE_STATUS != NULL_PTR)
  {
     *PIT_TIE_STATUS = LusPitTieStatus;
  }
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"
#endif


/*******************************************************************************
** Function Name        : IoHwAb_PostModeChange (Bolero Only)                 **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          : This Service covers Bolero errat #e7953             **
**                        This Api should be called after the Mcu_InitClock.  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : PIT_TIE_STATUS                                      **
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
**                        Function(s) invoked    :                            **
*******************************************************************************/
#if defined(IOHWAB_MCAL_FREESCALE_MPC560XB)
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(void, IOHWAB_CODE)IoHwAb_GptPostModeChange(
  P2VAR(IoHwAb_IndexType, AUTOMATIC, IOHWAB_APPL_DATA) PIT_TIE_STATUS)
{
  uint16 LusPitChIdx = 0U;
  uint16 LusPitTieStatus = 0U;
  if (PIT_TIE_STATUS != NULL_PTR)
  { 
    LusPitTieStatus = *PIT_TIE_STATUS;
    for( LusPitChIdx = 0U; LusPitChIdx < GPT_PIT_CHAN_NUM; LusPitChIdx++)
    {
      if( (LusPitTieStatus & (uint16)((uint16)1 << (uint16)LusPitChIdx)) != 0U )
      {
        PIT_INTERRUPT_ENABLE(LusPitChIdx);
      }
    }
  }
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*polyspace:end<MISRA-C:11.3:Not a defect:Justify with annotations> No Impact of this rule violation*/
/*polyspace:end<RTE: IDP : Not a defect : No Action Planned >  */
/*polyspace:end<RTE: NIV : Not a defect : No Action Planned >  */
/* polyspace-end MISRA-C3:D4.14 [Justified:Unset] "The pointer is checked always." */
/* polyspace-end MISRA-C3:8.3 [Justified:Unset] "Prototypes are generated wrongly. It will be fixed soon" */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
