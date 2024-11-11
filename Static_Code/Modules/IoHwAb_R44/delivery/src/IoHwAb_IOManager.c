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
**  SRC-MODULE: IoHwAb_IOManager.c                                            **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR IOHWAB                                                **
**                                                                            **
**  PURPOSE   : APIs implementation for IoHwAb module                         **
**              IoHwAb_IOMDelayTicks                                          **
**              IoHwAb_IOMInit                                                **
**              IoHwAb_IOMDeInit                                              **
**              IoHwAb_IOMDigInInit                                           **
**              IoHwAB_IOMDigInSample                                         **
**              IoHwAb_IOMAnaInAcqEnd                                         **
**              IoHwAb_IOML2H                                                 **
**              IoHwAb_IOMH2L                                                 **
**              IoHwAb_IOMInputsLP                                            **
**              IoHwAb_IOMOutputsLP                                           **
**              IoHwAb_IOMOnTimer                                             **
**              IoHwAb_IOM_5ms                                                **
**              IoHwAb_IOM_10ms                                               **
**              IOHWAB_IOM_TASK_FG2_FUNC                                      **
**              IOHWAB_IOM_TASK_FG1_FUNC                                      **
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
** 1.4.5     25-May-2023  KhaLN1            #CP44-2239                        **
** 1.4.3     12-Dec-2022  KhaLN1            #CP44-1247                        **
** 1.3.2     10-Aug-2022  KhaLN1            #CP44-731                         **
** 1.3.0.1   30-Jun-2022  KhaLN1            #CP44-365                         **
** 1.3.0     16-Mar-2022  PhucNHM           R44-Redmine #24320                **
** 1.1.0     15-Jul-2021  YangJin.Kim       R44-Redmine #18100                **
** 1.0.1     26-Feb-2020  YangJin.Kim       R40-Redmine #28531                **
** 1.0.0     04-Dec-2020  YangJin.Kim       R40-Redmine #26992                **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "IoHwAb_IOManager.h"
#include "IoHwAb_Config.h"
#include "SchM_IoHwAb.h"
#include "Rte_IoHwAb.h"
#include "IoHwAb_Util.h"

#if (IOHWAB_USE_IO_MAN == STD_ON)
#include "Os.h"
#endif /* (IOHWAB_USE_IO_MAN == STD_ON) */
#if ((IOHWAB_USE_ANA_IN == STD_ON) || (IOHWAB_USE_ANA_IN_DIR == STD_ON))
#include "IoHwAb_Adc.h"
#endif /* ((IOHWAB_USE_ANA_IN == STD_ON) || (IOHWAB_USE_ANA_IN_DIR == STD_ON)) */
#if (IOHWAB_USE_DIG_IN == STD_ON)
#include "IoHwAb_DigIn.h"
#if (IOHWAB_USE_MC33972 == STD_ON)
#include "IoHwAb_DigInMC33972.h"
#endif /* (IOHWAB_USE_MC33972 == STD_ON) */
#endif /* (IOHWAB_USE_DIG_IN == STD_ON) */
#if (IOHWAB_USE_DIG_OUT == STD_ON)
#include "IoHwAb_DigOut.h"
#if (IOHWAB_USE_L9826 == STD_ON)
#include "IoHwAb_DigOutL9826.h"
#endif /* (IOHWAB_USE_L9826 == STD_ON) */
#if (IOHWAB_USE_L99MC6 == STD_ON)
#include "IoHwAb_DigOutL99MC6.h"
#endif /* (IOHWAB_USE_L99MC6 == STD_ON) */
#if (IOHWAB_USE_TLE7240SL == STD_ON)
#include "IoHwAb_DigOutTLE7240SL.h"
#endif /* (IOHWAB_USE_TLE7240SL == STD_ON) */
#endif /* (IOHWAB_USE_DIG_OUT == STD_ON) */
#if (IOHWAB_USE_IN_SUP_SWT == STD_ON)
#include "IoHwAb_InputSupply.h"
#endif /* (IOHWAB_USE_IN_SUP_SWT == STD_ON) */
#if (IOHWAB_USE_VOL_MON == STD_ON)
#include "IoHwAb_VolMon.h"
#endif /* (IOHWAB_USE_VOL_MON == STD_ON) */
#if (IOHWAB_USE_LP_FLAG == STD_ON)
#include "BswM.h"
#endif /* (IOHWAB_USE_LP_FLAG == STD_ON) */
#if (IOHWAB_USE_PM_MODULE == STD_ON)
#include "Pm_Types.h"
#endif /* (IOHWAB_USE_PM_MODULE == STD_ON) */
/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#define IOHWAB_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
#ifndef TEST_APPLICATION
/* polyspace +1 DEFECT:DATA_RACE [Not a defect:High] "Not a defect" */
static VAR(IoHwAb_AcqState, IOHWAB_VAR)IoHwAb_GucInAcqState; /* polyspace VARIABLE:* [Not a defect:Low] "System intended for multitasking" */
#else
VAR(IoHwAb_AcqState, IOHWAB_VAR)IoHwAb_GucInAcqState;
#endif
#define IOHWAB_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
#if (IOHWAB_USE_IO_MAN == STD_ON)

#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
static FUNC(StatusType, IOHWAB_CODE)IoHwAb_IOMActivateTask(TaskType TaskId);
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"

#if (IOHWAB_USE_DIG_IN == STD_ON)

#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
static FUNC(void, IOHWAB_CODE)IoHwAb_IOMDigInInit(void);
static FUNC(void, IOHWAB_CODE)IoHwAb_Demultiplexed(void);
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"


#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
static FUNC(void, IOHWAB_CODE)IoHwAB_IOMDigInSample(void);
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"

#endif /* (IOHWAB_USE_DIG_IN == STD_ON) */

#endif /* (IOHWAB_USE_IO_MAN == STD_ON) */

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"

#if (IOHWAB_USE_IO_MAN == STD_ON)

#if (IOHWAB_USE_DIG_SUP_SWT == STD_ON)
#if (IOHWAB_USE_DIG_SUP_SWT_LP == STD_ON)
/* MCU dependent Code */
/*polyspace:begin<MISRA-C:8.1:Not a defect:Justify with annotations> No Impact of this rule violation*/
/*polyspace:begin<MISRA-C:10.1:Not a defect:Justify with annotations> No Impact of this rule violation*/
/*polyspace:begin<MISRA-C:11.3:Not a defect:Justify with annotations> No Impact of this rule violation*/
/*polyspace:begin<RTE: ABS_ADDR : Not a defect : No Action Planned >  */
/* polyspace-begin RTE:UNR [Not a defect:Unset] "Reachable code" */
/*******************************************************************************
** Function Name        : IoHwAb_IOMDelayTicks                                **
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
**                        Function(s) invoked    :                            **
*******************************************************************************/
FUNC(void, IOHWAB_CODE)IoHwAb_IOMDelayTicks(uint32 ticks)
{
  volatile uint32 requestedTime;
  
#if (defined(IOHWAB_MCAL_INFINEON_TC21X) || defined(IOHWAB_MCAL_INFINEON_TC22X) \
  || defined(IOHWAB_MCAL_INFINEON_TC23X) || defined(IOHWAB_MCAL_INFINEON_TC26X) \
  || defined(IOHWAB_MCAL_INFINEON_TC27X) || defined(IOHWAB_MCAL_INFINEON_TC29X) \
  || defined(IOHWAB_MCAL_RENESAS_RH850U2A))


  uint32 previousTime;
  uint32 currentTime;
  uint32 elapsedTime;

  requestedTime = ticks;
  previousTime = IOHWAB_CURRENT_CLOCK_TICK();
  do
  {
/*polyspace:begin<MISRA-C:2.1:Not a defect:Justify with annotations> No Impact of this rule violation*/
    IOHWAB_NOP();
    IOHWAB_NOP();
    IOHWAB_NOP();
    IOHWAB_NOP();
    IOHWAB_NOP();
/*polyspace:end<MISRA-C:2.1:Not a defect:Justify with annotations> No Impact of this rule violation*/


    currentTime = IOHWAB_CURRENT_CLOCK_TICK();

    if (currentTime > previousTime)
    {
      elapsedTime = currentTime - previousTime;
    }
    else
    {
      elapsedTime = 0xFFFFFFFFu - previousTime;
      elapsedTime += currentTime + IOHWAB_ONE;
    }

    previousTime = currentTime;

    if (requestedTime > elapsedTime)
    {
      requestedTime -= elapsedTime;
    }
    else
    {
      requestedTime = IOHWAB_ZERO;
    }
  } while (requestedTime != IOHWAB_ZERO);

#else /* All Mcus but Aurix platform */
  requestedTime = ((uint32)IOHWAB_ISUPPLY_MCU_CLK_LP*ticks)/IOHWAB_MCU_CLK_DIV;
  if (requestedTime > 0u)
  {
    for (;requestedTime!=0u; requestedTime--){/* Do Nothing */};
  }  
#endif /* #if Aurix */
}

#endif /* (IOHWAB_USE_DIG_SUP_SWT_LP == STD_ON) */
#endif /* (IOHWAB_USE_DIG_SUP_SWT == STD_ON)      */
/*polyspace:end<MISRA-C:11.3:Not a defect:Justify with annotations> No Impact of this rule violation*/
/*******************************************************************************
** Function Name        : IoHwAb_IOMInit                                      **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          : This Service initilize IO Manager module.           **
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
**                          IoHwAb_AnaInInit,                                 **
**                          IoHwAb_AnaInConvertStart,                         **
**                          IoHwAb_IOMDigInInit,                              **
**                          IoHwAb_DigOutInit,                                **
**                          IoHwAb_DigOutWriteOutputsToHW,                    **
**                          IoHwAb_DigOutL9826,                               **
**                          IoHwAb_DigOutL99MC6,                              **
**                          IoHwAb_VolMonInit,                                **
**                          Gpt_EnableNotification                            **
*******************************************************************************/
FUNC(void, IOHWAB_CODE)IoHwAb_IOMInit(void)
{
  #if (defined(IOHWAB_MCAL_RENESAS_RH850F1L) || defined(IOHWAB_MCAL_RENESAS_RH850F1L_413) \
    || defined(IOHWAB_MCAL_RENESAS_RH850F1K) || defined(IOHWAB_MCAL_RENESAS_RH850F1KM))
  IoHwAb_IOManager_AssignTaskID();  
  #endif /* RH850 */
  
  #if (IOHWAB_USE_IN_SUP_SWT == STD_ON)
  IoHwAb_InputSupplyInit();
  #endif /* (IOHWAB_USE_IN_SUP_SWT == STD_ON) */

  #if (IOHWAB_USE_ANA_IN == STD_ON)
  IoHwAb_AnaInInit();

  /* initialise analog inputs */
  /* only the converter is initialised, it would be to long to update the     */
  /* values of all ananlog inputs                                             */
  IoHwAb_AnaInConvertStart();
  #endif /* (IOHWAB_USE_ANA_IN == STD_ON) */

  #if (IOHWAB_USE_DIG_IN == STD_ON)
  /* call of digital input init functions (must be after biostartup_Startup) */
  IoHwAb_IOMDigInInit();
  #endif /* (IOHWAB_USE_DIG_IN == STD_ON) */

  #if (IOHWAB_USE_DIG_OUT == STD_ON)
  /* initialisation of all digital outputs with default values */
  IoHwAb_DigOutInit();
  #endif /* (IOHWAB_USE_DIG_OUT == STD_ON) */

  #if (IOHWAB_USE_VOL_MON == STD_ON)
  /* battery monitoring initialisation */
  IoHwAb_VolMonInit();
  #endif /* (IOHWAB_USE_VOL_MON == STD_ON) */

  #if (IOHWAB_USE_IO_MAN_GPTTIMER == STD_ON)
  Gpt_EnableNotification(IOHWAB_IOM_GPT_TIMER_ID);
  #endif /* (IOHWAB_USE_IO_MAN_GPTTIMER == STD_ON) */
}


/*******************************************************************************
** Function Name        : IoHwAb_IOMDeInit                                    **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          : This Service deinitilize IO Manager module.         **
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
**                          Gpt_DisableNotification                           **
*******************************************************************************/
FUNC(void, IOHWAB_CODE)IoHwAb_IOMDeInit(void)
{
  #if (IOHWAB_USE_IO_MAN_GPTTIMER == STD_ON)
  Gpt_DisableNotification(IOHWAB_IOM_GPT_TIMER_ID);
  #endif /* (IOHWAB_USE_IO_MAN_GPTTIMER == STD_ON) */

  #if (IOHWAB_USE_DIG_OUT == STD_ON)
  /* deinitialisation of all digital outputs with default values */
  #if (IOHWAB_USE_L9826 == STD_ON) || (IOHWAB_USE_L99MC6 == STD_ON) \
   || (IOHWAB_USE_TLE7240SL == STD_ON)
  IoHwAb_DigOutDeInit();
  #endif
  #endif /* (IOHWAB_USE_DIG_OUT == STD_ON) */
}

#if (IOHWAB_USE_DIG_IN == STD_ON)
/*******************************************************************************
** Function Name        : IoHwAb_IOMDigInInit                                 **
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
**                          IoHwAb_DigInFilteringStart                        **
**                        Function(s) invoked    :                            **
**                          IoHwAb_InputSupplyDigitalControl,                 **
**                          IoHwAb_DigInMC33972Init                           **
**                          IoHwAb_DigInInit1                                 **
**                          IoHwAB_IOMDigInSample                             **
**                          IoHwAb_DigInInit2                                 **
*******************************************************************************/
static FUNC(void, IOHWAB_CODE)IoHwAb_IOMDigInInit(void)
{
  #if (IOHWAB_USE_DIG_SUP_SWT == STD_ON)
  IoHwAb_InputSupplyDigitalControl(TRUE, TRUE);
  #endif /* (IOHWAB_USE_DIG_SUP_SWT == STD_ON) */


  #if (IOHWAB_USE_MC33972 == STD_ON)
  /* initialise multiplexed digital inputs */
  (void)IoHwAb_DigInMC33972Init();
  #endif /* (IOHWAB_USE_MC33972 == STD_ON) */

  IoHwAb_DigInFilteringStart = TRUE;

  /* first sample of digital inputs acquisition and filtering */
  IoHwAb_DigInInit1();

  /* the second sample of digital inputs acquisition and filtering  */
  IoHwAB_IOMDigInSample();

  /* the third sample of digital inputs acquisition and filtering  */
  IoHwAB_IOMDigInSample();

  /* Initialize debounce function for all digital inputs*/
  /* (fast, slow, mux) */
  IoHwAb_DigInInit2();
}
#endif /* (IOHWAB_USE_DIG_IN == STD_ON) */

#if (IOHWAB_USE_DIG_IN == STD_ON)
/*******************************************************************************
** Function Name        : IoHwAB_IOMDigInSample                               **
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
**                        Function(s) invoked    :                            **
**                          IoHwAb_DigInReadHwInputs,                         **
**                          IoHwAb_DigInMC33972Acq,                           **
**                          IoHwAb_DigInDebounce                              **
*******************************************************************************/
/* @Trace: SRS_IoHwAb_12324 */
/* @Trace: SWR_IOHWAB_703_001 SWR_IOHWAB_703_002 SWR_IOHWAB_703_005 SWR_IOHWAB_704_001 SWR_IOHWAB_704_002 */
/* @Trace: SWR_IOHWAB_704_003 SWR_IOHWAB_704_004 */
static FUNC(void, IOHWAB_CODE)IoHwAB_IOMDigInSample(void)
{
  /* acquisition of non multiplexed digital inputs */
  IoHwAb_DigInReadHwInputs(FALSE);

  #if (IOHWAB_USE_MC33972 == STD_ON)
  /* acquire values of multiplexed inputs in mc33972 */
  (void)IoHwAb_DigInMC33972Acq();
  #endif /* (IOHWAB_USE_MC33972 == STD_ON) */

  /* filtering of all digital inputs  */
  /* polyspace +1 MISRA-C3:2.2 [Not a defect:Low] "It depends on the configuration" */
  IoHwAb_DigInDebounce(0, IOHWAB_NUM_DIGIN_FAST + IOHWAB_NUM_DIGIN_SLOW);
}
#endif /* (IOHWAB_USE_DIG_IN == STD_ON) */

/*******************************************************************************
** Function Name        : IoHwAb_IOMAnaInAcqEnd                               **
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
**                          IoHwAb_GucInAcqState                              **
**                        Function(s) invoked    :                            **
**                          IoHwAb_InputSupplyAnalogControl,                  **
**                          GetTaskState,                                     **
**                          ActivateTask,                                     **
**                          CoSvAb_FastTimerStart,                            **
**                          Gpt_StartTimer                                    **
*******************************************************************************/
FUNC(void, IOHWAB_CODE)IoHwAb_IOMAnaInAcqEnd (void)
{
  /* callback called when all analog acquisition is finished */

  #if ((IOHWAB_USE_ANA_IN == STD_ON) && (IOHWAB_USE_IN_SUP_SWT == STD_ON) &&   \
       (IOHWAB_USE_ANA_SUP_SWT == STD_ON))
  /* switch off switched battery for analog inputs */
  IoHwAb_InputSupplyAnalogControl(FALSE);
  #endif /* ((IOHWAB_USE_ANA_IN == STD_ON) && (IOHWAB_USE_IN_SUP_SWT == STD_ON) &&
             (IOHWAB_USE_ANA_SUP_SWT == STD_ON)) */

  /* start task for analog filtering */

#if defined(IOHWAB_IOM_TASK_FG1)
  (void)IoHwAb_IOMActivateTask(IoHwAb_GddIOMTaskFG1);
#endif
}

/*******************************************************************************
** Function Name        : IoHwAb_IOML2H                                       **
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
**                          IoHwAb_DigOutL99MC6SwitchOn,                      **
**                          IoHwAb_DigInMC33972L2H                            **
*******************************************************************************/
FUNC(void, IOHWAB_CODE)IoHwAb_IOML2H(void)
{
  #if (IOHWAB_USE_DIG_OUT == STD_ON)
  #if (IOHWAB_USE_L9826 == STD_ON)
  (void)IoHwAb_DigOutL9826SwitchOn();
  #endif /* (IOHWAB_USE_L9826 == STD_ON) */
  #endif /* (IOHWAB_USE_DIG_OUT == STD_ON) */

  #if (IOHWAB_USE_DIG_OUT == STD_ON)
  #if (IOHWAB_USE_L99MC6 == STD_ON)
  (void)IoHwAb_DigOutL99MC6SwitchOn();
  #endif /* (IOHWAB_USE_L99MC6 == STD_ON) */
  #endif /* (IOHWAB_USE_DIG_OUT == STD_ON) */

  #if (IOHWAB_USE_DIG_OUT == STD_ON)
  #if (IOHWAB_USE_TLE7240SL == STD_ON)
  /* switch on the TLE7240SL devices after they were deselected */
  (void)IoHwAb_DigOutTLE7240SLSwitchOn();
  #endif /* (IOHWAB_USE_TLE7240SL == STD_ON) */
  #endif /* (IOHWAB_USE_DIG_OUT == STD_ON) */

  #if (IOHWAB_USE_DIG_IN == STD_ON)
  /* call the low to high function of each module present in th eproject */
  #if (IOHWAB_USE_MC33972 == STD_ON)
  (void)IoHwAb_DigInMC33972L2H();
  #endif /* (IOHWAB_USE_MC33972 == STD_ON) */
  #endif /* (IOHWAB_USE_DIG_IN == STD_ON) */
}


/*******************************************************************************
** Function Name        : IoHwAb_IOMH2L                                       **
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
**                          IoHwAb_DigOutL99MC6SwitchOff,                     **
**                          IoHwAb_DigInMC33972H2L,                           **
**                          IoHwAb_DigInH2L                                   **
*******************************************************************************/
FUNC(void, IOHWAB_CODE)IoHwAb_IOMH2L(void)
{
  #if (IOHWAB_USE_DIG_OUT == STD_ON)
  #if (IOHWAB_USE_L9826 == STD_ON)
  IoHwAb_DigOutL9826SwitchOff();
  #endif /* (IOHWAB_USE_L9826 == STD_ON) */
  #endif /* (IOHWAB_USE_DIG_OUT == STD_ON) */

  #if (IOHWAB_USE_DIG_OUT == STD_ON)
  #if (IOHWAB_USE_L99MC6 == STD_ON)
  /* switch on the L99MC6 devices after they were deselected */
  (void)IoHwAb_DigOutL99MC6SwitchOff();
  #endif /* (IOHWAB_USE_L99MC6 == STD_ON) */
  #endif /* (IOHWAB_USE_DIG_OUT == STD_ON) */

  #if (IOHWAB_USE_DIG_OUT == STD_ON)
  #if (IOHWAB_USE_TLE7240SL == STD_ON)
  /* switch on the TLE7240SL devices after they were deselected */
  (void)IoHwAb_DigOutTLE7240SLSwitchOff();
  #endif /* (IOHWAB_USE_TLE7240SL == STD_ON) */
  #endif /* (IOHWAB_USE_DIG_OUT == STD_ON) */
  

  #if (IOHWAB_USE_DIG_IN == STD_ON)
  /* call the high to low function of each module present in th eproject */
  #if (IOHWAB_USE_MC33972 == STD_ON)
  (void)IoHwAb_DigInMC33972H2L();
  #endif /* (IOHWAB_USE_MC33972 == STD_ON) */

  IoHwAb_DigInH2L();
  #endif /* (IOHWAB_USE_DIG_IN == STD_ON) */
}


/*******************************************************************************
** Function Name        : IoHwAb_IOMInputsLP                                  **
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
**                          IoHwAb_InputSupplyDigitalControl,                 **
**                          IoHwAb_DigInReadHwInputs,                         **
**                          IoHwAb_DigInSampleLP                              **
*******************************************************************************/
/* @Trace:  */
FUNC(void, IOHWAB_CODE)IoHwAb_IOMInputsLP(void)
{
  #if (IOHWAB_USE_DIG_IN == STD_ON)
  #if (IOHWAB_USE_DIG_SUP_SWT == STD_ON)
  #if (IOHWAB_USE_DIG_SUP_SWT_LP == STD_ON)
  /* switch on switched battery for digital inputs */
  IoHwAb_InputSupplyDigitalControl(FALSE, TRUE);
  /* wait DIGITAL_SUPPLY_SWITCH_DELAY ms */
  IoHwAb_IOMDelayTicks((uint32)IoHwAb_GddISupplyDigSwitchDelay);
  #endif /* (IOHWAB_USE_DIG_SUP_SWT_LP == STD_ON) */
  #endif /* (IOHWAB_USE_DIG_SUP_SWT == STD_ON) */
  #endif /* (IOHWAB_USE_DIG_IN == STD_ON) */

  #if (IOHWAB_USE_DIG_IN == STD_ON)
  /* update value of fast and slow buffered digital inputs */
  IoHwAb_DigInReadHwInputs(FALSE);
  #endif /* (IOHWAB_USE_DIG_IN == STD_ON) */

  #if (IOHWAB_USE_DIG_IN == STD_ON)
  #if (IOHWAB_USE_DIG_SUP_SWT == STD_ON)
  #if (IOHWAB_USE_DIG_SUP_SWT_LP == STD_ON)
  /* switch off switched battery for digital inputs */
  IoHwAb_InputSupplyDigitalControl(FALSE, FALSE);
  #endif /* (IOHWAB_USE_DIG_SUP_SWT_LP == STD_ON) */
  #endif /* (IOHWAB_USE_DIG_SUP_SWT == STD_ON) */
  #endif /* (IOHWAB_USE_DIG_IN == STD_ON) */

  #if (IOHWAB_USE_DIG_IN == STD_ON)
  /* update raw values of all digital inputs available in low power */
  IoHwAb_DigInSampleLP();
  #endif /* (IOHWAB_USE_DIG_IN == STD_ON) */
}


/*******************************************************************************
** Function Name        : IoHwAb_IOMOutputsLP                                 **
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
**                          IoHwAb_DigOutWriteOutputsToHW                     **
*******************************************************************************/
FUNC(void, IOHWAB_CODE)IoHwAb_IOMOutputsLP(void)
{
  #if (IOHWAB_USE_DIG_OUT == STD_ON)
  /* update buffered outputs except demultiplexed outputs */
  IoHwAb_DigOutWriteOutputsToHW();
  #endif /* (IOHWAB_USE_DIG_OUT == STD_ON) */
}


/*******************************************************************************
** Function Name        : IoHwAb_IOMOnTimer                                   **
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
**                          IoHwAb_GucInAcqState                              **
**                        Function(s) invoked    :                            **
**                          GetTaskState,                                     **
**                          ActivateTask,                                     **
**                          CoSvAb_FastTimerStart,                            **
**                          Gpt_StartTimer                                    **
*******************************************************************************/
FUNC(void, IOHWAB_CODE)IoHwAb_IOMOnTimer(void)
{
  switch (IoHwAb_GucInAcqState)
  {
  case IOHWAB_ACQ_ANALOG_END :
#if defined(IOHWAB_IOM_TASK_FG1)
    (void)IoHwAb_IOMActivateTask(IoHwAb_GddIOMTaskFG1);
#endif /* (IOHWAB_IOM_TASK_FG1) */
    break;

  case IOHWAB_ACQ_DIGITAL :
    /* Do nothing */
  case IOHWAB_ACQ_ANALOG :
#if defined(IOHWAB_IOM_TASK_FG2)
    (void)IoHwAb_IOMActivateTask(IoHwAb_GddIOMTaskFG2);
#endif /* (IOHWAB_IOM_TASK_FG2) */
    break;

  default :
    /* Do nothing */
    break;
  }
}


/*******************************************************************************
** Function Name        : IoHwAb_IOM_5ms                                      **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          :                                                     **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Reentrancy           : Non Reentrant                                       **
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
**                          IoHwAb_VolMon,                                    **
**                          IoHwAb_DigInReadHwInputs,                         **
**                          IoHwAb_DigInDebounce                              **
*******************************************************************************/

/* @Trace: SRS_IoHwAb_12419 */
/* @Trace: SWR_IOHWAB_702_001 SWR_IOHWAB_704_004 SWR_IOHWAB_710_003 */
/* @Trace: IoHwAb_SUD_API_110*/
FUNC(void, IOHWAB_CODE)IoHwAb_IOM_5ms(void)
{
  #if (IOHWAB_USE_VOL_MON == STD_ON)
  /* battery monitoring management*/
  IoHwAb_VolMon();
  #endif /* (IOHWAB_USE_VOL_MON == STD_ON) */

  #if (IOHWAB_USE_DIG_IN == STD_ON)
  /* fast digital input acquisition and debounce */
  IoHwAb_DigInReadHwInputs(TRUE);
  IoHwAb_DigInDebounce((IoHwAb_IndexType)0, IOHWAB_NUM_DIGIN_FAST);
  #endif /* (IOHWAB_USE_DIG_IN == STD_ON) */ 
}


/*******************************************************************************
** Function Name        : IoHwAb_IOM_10ms                                     **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          :                                                     **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Reentrancy           : Non Reentrant                                       **
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
**                          IoHwAb_GucInAcqState                              **
**                        Function(s) invoked    :                            **
**                          Pm_GetPowerMode,                                  **
**                          Det_ReportError,                                  **
**                          Dem_ReportErrorStatus,                            **
**                          IoHwAb_DigOutWriteOutputsToHW,                    **
**                          IoHwAb_DigOutL9826,                               **
**                          IoHwAb_DigOutL99MC6,                              **
**                          IoHwAb_InputSupplyDigitalControl,                 **
**                          CoSvAb_FastTimerStart,                            **
**                          Gpt_StartTimer,                                   **
**                          GetTaskState,                                     **
**                          ActivateTask,                                     **
**                          IoHwAb_InputSupplyAnalogControl                   **
*******************************************************************************/

/* @Trace: SRS_IoHwAb_12324 SRS_IoHwAb_12450 SRS_IoHwAb_12419 SRS_IoHwAb_12323 SRS_IoHwAb_CUS_00003 */
/* @Trace: SWR_IOHWAB_702_001 SWR_IOHWAB_703_001 SWR_IOHWAB_703_004 */
/* @Trace: SWR_IOHWAB_706_001 SWR_IOHWAB_707_002 SWR_IOHWAB_707_003 SWR_IOHWAB_707_004 */
/* @Trace: IoHwAb_SUD_API_111 */
FUNC(void, IOHWAB_CODE)IoHwAb_IOM_10ms(void)
{
  #if (((IOHWAB_USE_DIG_IN == STD_ON) && (IOHWAB_USE_DIG_SUP_SWT != STD_ON)) \
    || ((IOHWAB_USE_DIG_IN != STD_ON) \
      && (IOHWAB_USE_ANA_IN == STD_ON) && (IOHWAB_USE_ANA_SUP_SWT != STD_ON)))
  StatusType LddError = E_NOT_OK;
  #endif /* (((IOHWAB_USE_DIG_IN == STD_ON) && (IOHWAB_USE_DIG_SUP_SWT == STD_OFF)) \
    || ((IOHWAB_USE_ANA_IN == STD_ON) && (IOHWAB_USE_ANA_SUP_SWT == STD_OFF))) */

  #if (IOHWAB_USE_LP_FLAG == STD_ON)
  #if (IOHWAB_USE_PM_MODULE == STD_ON)
  Pm_PowerModeType LddPmMode = 0U;

  (void)Pm_GetPowerMode(&LddPmMode);
  if ((Pm_PowerModeType)LddPmMode != (Pm_PowerModeType)PM_POWERMODE_LOW)
  {
    #endif /* (IOHWAB_USE_PM_MODULE == STD_ON) */
    /* Set the Lowpower Flag */
    BswM_RequestMode((BswM_UserType)IOHWAB_MODULE_ID, (BswM_ModeType)IOHWAB_LOWPOWER_PREVENT);
    #endif /* (IOHWAB_USE_LP_FLAG == STD_ON) */


    /* if the previous IO processing is not yet finished send error to system   */
    /* and skip IO processing                                                   */
    if(IoHwAb_GucInAcqState != IOHWAB_ACQ_NO_ACTION)
    {
      #if (IOHWAB_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError((uint16)IOHWAB_MODULE_ID, (uint8)IOHWAB_INSTANCE_ID,
        (uint8)IOHWAB_IOM_10MS_SID, (uint8)IOHWAB_E_DET_WRONG_STATE);
      #endif /* (IOHWAB_DEV_ERROR_DETECT == STD_ON) */
      #if (IOHWAB_USE_DEM_EVENT == STD_ON)
      Dem_ReportErrorStatus(IOHWAB_E_WRONG_STATE, DEM_EVENT_STATUS_FAILED);
      #endif /* (IOHWAB_USE_DEM_EVENT == STD_ON) */
    }
    else
    {
      #if (IOHWAB_USE_DIG_OUT == STD_ON)
      /* currently updating digital outputs */
      IoHwAb_GucInAcqState = IOHWAB_ACQ_DIGITAL_OUT;
      IoHwAb_Demultiplexed();
      #endif /* (IOHWAB_USE_DIG_OUT == STD_ON) */

  /* @Trace: SRS_IoHwAb_12455 */
  #if (IOHWAB_USE_POWER_STATE_ASYNCH_MODE == STD_ON)
    #if ( ((IOHWAB_USE_ADC_POWER_STATE_API == STD_ON) &&  (IOHWAB_USE_PWM_POWER_STATE_API == STD_OFF)) \
      ||  ((IOHWAB_USE_ADC_POWER_STATE_API == STD_OFF) &&  (IOHWAB_USE_PWM_POWER_STATE_API == STD_ON))  )
      if(IoHwAb_GucPwrStNotifCnt == IOHWAB_ONE){
        IoHwAb_EnterPowerState();
        IoHwAb_GucPwrStNotifCnt = 0;
      }
    #endif

    #if ( (IOHWAB_USE_ADC_POWER_STATE_API == STD_ON) && (IOHWAB_USE_PWM_POWER_STATE_API == STD_ON) )
      if(IoHwAb_GucPwrStNotifCnt == IOHWAB_TWO){
        IoHwAb_EnterPowerState();
        IoHwAb_GucPwrStNotifCnt = 0;
      }
    #endif
  #endif
      /* If any kind of digital inputs is present */
      #if (IOHWAB_USE_DIG_IN == STD_ON)
      /* Next step will be acquisition and filtering of digital inputs */
      IoHwAb_GucInAcqState = IOHWAB_ACQ_DIGITAL;

      #if ((IOHWAB_USE_IN_SUP_SWT == STD_ON) && (IOHWAB_USE_DIG_SUP_SWT == STD_ON))
      /* switch on switched battery for digital inputs */
      IoHwAb_InputSupplyDigitalControl(TRUE, TRUE);
      /* start timer for switched battery delay */
      #if (IOHWAB_USE_IO_MAN_FASTTIMER == STD_ON)
      (void) CoSvAb_FastTimerStart(IOHWAB_IOM_FAST_TIMER_ID, IoHwAb_GddISupplyDigSwitchDelay);
      #endif /* (IOHWAB_USE_IO_MAN_FASTTIMER == STD_ON) */

      #if (IOHWAB_USE_IO_MAN_GPTTIMER == STD_ON)
      #if (IOHWAB_IOM_GPT_TICKS_FOR_1US == IOHWAB_ONE)
      Gpt_StartTimer(IOHWAB_IOM_GPT_TIMER_ID, (uint32)IoHwAb_GddISupplyDigSwitchDelay);
      #else
      Gpt_StartTimer(IOHWAB_IOM_GPT_TIMER_ID,
       ((uint32)IoHwAb_GddISupplyDigSwitchDelay * (uint32)IOHWAB_IOM_GPT_TICKS_FOR_1US));
      #endif /* (IOHWAB_IOM_GPT_TICKS_FOR_1US == IOHWAB_ONE) */
      #endif /* (IOHWAB_USE_IO_MAN_GPTTIMER == STD_ON) */
      #else /* ((IOHWAB_USE_IN_SUP_SWT == STD_ON) && (IOHWAB_USE_DIG_SUP_SWT == STD_ON)) */
#if defined(IOHWAB_IOM_TASK_FG2)
    /* activate acquisition task */
      LddError = IoHwAb_IOMActivateTask(IoHwAb_GddIOMTaskFG2);

      if (LddError == E_OK)
      {
      }
#endif /* (IOHWAB_IOM_TASK_FG2)      */
      #endif /* ((IOHWAB_USE_IN_SUP_SWT == STD_ON) && (IOHWAB_USE_DIG_SUP_SWT == STD_ON)) */

      #else /* (IOHWAB_USE_DIG_IN == STD_ON) */
      /* If any kind of analog inputs is present and no digital input is present */
      #if (IOHWAB_USE_ANA_IN == STD_ON)
      /* Next step will be acquisition and filtering of analog inputs */
      IoHwAb_GucInAcqState = IOHWAB_ACQ_ANALOG;
      #if ((IOHWAB_USE_IN_SUP_SWT == STD_ON) && (IOHWAB_USE_ANA_SUP_SWT == STD_ON))
      /* switch on switched battery for analog inputs */
      IoHwAb_InputSupplyAnalogControl(TRUE);
      #if (IOHWAB_USE_IO_MAN_FASTTIMER == STD_ON)
      /* Start Timer for switched battery delay */
      (void) CoSvAb_FastTimerStart(IOHWAB_IOM_FAST_TIMER_ID, IoHwAb_GddISupplyAnaSwitchDelay);
      #endif /* (IOHWAB_USE_IO_MAN_FASTTIMER == STD_ON) */
      #if (IOHWAB_USE_IO_MAN_GPTTIMER == STD_ON)
      #if (IOHWAB_IOM_GPT_TICKS_FOR_1US == IOHWAB_ONE)
      /* Start Timer for switched battery delay */
      Gpt_StartTimer(IOHWAB_IOM_GPT_TIMER_ID, IoHwAb_GddISupplyAnaSwitchDelay);
      #else
      /* Start Timer for switched battery delay */
      Gpt_StartTimer(IOHWAB_IOM_GPT_TIMER_ID,
        (IoHwAb_GddISupplyAnaSwitchDelay * IOHWAB_IOM_GPT_TICKS_FOR_1US));
      #endif /* (IOHWAB_IOM_GPT_TICKS_FOR_1US == IOHWAB_ONE) */
      #endif /* (IOHWAB_USE_IO_MAN_GPTTIMER == STD_ON) */
      #else /* (IOHWAB_USE_IN_SUP_SWT == STD_ON)&&(IOHWAB_USE_ANA_SUP_SWT == STD_ON) */
#if defined(IOHWAB_IOM_TASK_FG2)
      /* start acquisition of analog inputs directly, activate acquisition task */
      LddError = IoHwAb_IOMActivateTask(IoHwAb_GddIOMTaskFG2);
      
      if (LddError == E_OK)
      {
      }
#endif /* (IOHWAB_IOM_TASK_FG2)      */

      #endif /* ((IOHWAB_USE_ANA_SUP_SWT == STD_ON)&&(IOHWAB_USE_IN_SUP_SWT == STD_ON))  */
      /* If there is no digital inputs or analog inputs */
      #else /* (IOHWAB_USE_ANA_IN == STD_ON) */
      /* Acquisition is finished */
      IoHwAb_GucInAcqState = IOHWAB_ACQ_NO_ACTION;
      #if (IOHWAB_USE_LP_FLAG == STD_ON)
      /* Clear the Lowpower Flag */
      BswM_RequestMode((BswM_UserType)IOHWAB_MODULE_ID, (BswM_ModeType)IOHWAB_LOWPOWER_ALLOW);
      #endif /* (IOHWAB_USE_LP_FLAG == STD_ON) */
      #endif /* (IOHWAB_USE_ANA_IN == STD_ON) */
      #endif /* (IOHWAB_USE_DIG_IN == STD_ON) */
    }
  #if ((IOHWAB_USE_LP_FLAG == STD_ON) && (IOHWAB_USE_PM_MODULE == STD_ON))
  }
  #endif
}


#if  defined(IOHWAB_IOM_TASK_FG2)

/*******************************************************************************
** Function Name        : TASK(IOHWAB_IOM_TASK_FG2)                           **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          :                                                     **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Reentrancy           : Non Reentrant                                       **
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
**                          IoHwAb_GucInAcqState                              **
**                        Function(s) invoked    :                            **
**                          IoHwAb_DigInReadHwInputs,                         **
**                          IoHwAb_DigInMC33972Acq,                           **
**                          IoHwAb_InputSupplyDigitalControl,                 **
**                          IoHwAb_AnaInConvertAllChannels,                   **
**                          CoSvAb_FastTimerStart,                            **
**                          Gpt_StartTimer,                                   **
**                          ChainTask,                                        **
**                          TerminateTask                                     **
*******************************************************************************/
IOHWAB_IOM_TASK_FG2_FUNC
{
  /* Default: activate task not needed, only terminate current task */
  boolean LblActivateFiltering = FALSE;

  /* This task is used to acquire all inputs */
  switch (IoHwAb_GucInAcqState)
  {
  case IOHWAB_ACQ_DIGITAL :
    #if (IOHWAB_USE_DIG_IN == STD_ON)
    /* update value of fast and slow buffered digital inputs */
    IoHwAb_DigInReadHwInputs(FALSE);

    #if (IOHWAB_USE_MC33972 == STD_ON)
    /* read multiplexed inputs */
    (void)IoHwAb_DigInMC33972Acq();
    #endif /* (IOHWAB_USE_MC33972 == STD_ON) */
    #endif /* (IOHWAB_USE_DIG_IN == STD_ON) */

    #if (IOHWAB_USE_DIG_IN == STD_ON)
    #if (IOHWAB_USE_DIG_SUP_SWT == STD_ON)
    /* switch off switched battery for digital inputs */
    IoHwAb_InputSupplyDigitalControl(TRUE, FALSE);
    #endif /* (IOHWAB_USE_DIG_SUP_SWT == STD_ON) */
    #endif /* (IOHWAB_USE_DIG_IN == STD_ON) */
    LblActivateFiltering = TRUE;
    break;

  case IOHWAB_ACQ_ANALOG :
    /* start analog acquisition, CB when finished to start analog mux acquisition */
    #if (IOHWAB_USE_ANA_IN == STD_ON)
    if (IoHwAb_AnaInConvertAllChannels() != E_OK)
    {
      #if (IOHWAB_USE_IO_MAN_FASTTIMER == STD_ON)
      /* if task is already in use, wait IOHWAB_IOM_MULTI_ACT_DELAY us */
      (void) CoSvAb_FastTimerStart(IOHWAB_IOM_FAST_TIMER_ID, IOHWAB_IOM_MULTI_ACT_DELAY);
      #endif /* (IOHWAB_USE_IO_MAN_FASTTIMER == STD_ON) */
      #if (IOHWAB_USE_IO_MAN_GPTTIMER == STD_ON)
      /* if task is already in use, wait IOHWAB_IOM_MULTI_ACT_DELAY us */
      #if (IOHWAB_IOM_GPT_TICKS_FOR_1US == IOHWAB_ONE)
      /* if task is already in use, wait IOHWAB_IOM_MULTI_ACT_DELAY us */
      Gpt_StartTimer(IOHWAB_IOM_GPT_TIMER_ID, (uint32)IOHWAB_IOM_MULTI_ACT_DELAY);
      #else
      /* if task is already in use, wait IOHWAB_IOM_MULTI_ACT_DELAY us */
      Gpt_StartTimer(IOHWAB_IOM_GPT_TIMER_ID,
        ((uint32)IOHWAB_IOM_MULTI_ACT_DELAY * (uint32)IOHWAB_IOM_GPT_TICKS_FOR_1US));
      #endif /* (IOHWAB_IOM_GPT_TICKS_FOR_1US == IOHWAB_ONE) */
      #endif /* (IOHWAB_USE_IO_MAN_GPTTIMER == STD_ON) */
    }
    else
    {
      /* Avoid MISRA warning, remove the unused code */
    }
    #endif /* (IOHWAB_USE_ANA_IN == STD_ON) */
    break;

  default :
    /* Do nothing */
    break;
  }

  /****end user code******/
  if (LblActivateFiltering != 0U)
  {
#if defined(IOHWAB_IOM_TASK_FG1)
    (void)ChainTask(IoHwAb_GddIOMTaskFG1);
#endif /* (IOHWAB_IOM_TASK_FG1)      */
  }
  else
  {
    (void)TerminateTask();
  }
}

#endif /* (IOHWAB_IOM_TASK_FG2)      */

#if defined(IOHWAB_IOM_TASK_FG1)
/*******************************************************************************
** Function Name        : TASK(IOHWAB_IOM_TASK_FG1)                           **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          :                                                     **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Reentrancy           : Non Reentrant                                       **
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
**                          IoHwAb_GucInAcqState                              **
**                        Function(s) invoked    :                            **
**                          IoHwAb_DigInDebounce,                             **
**                          IoHwAb_InputSupplyAnalogControl,                  **
**                          CoSvAb_FastTimerStart,                            **
**                          Gpt_StartTimer,                                   **
**                          GetTaskState,                                     **
**                          ActivateTask,                                     **
**                          IoHwAb_AnaInFilter,                               **
**                          TerminateTask                                     **
*******************************************************************************/
IOHWAB_IOM_TASK_FG1_FUNC
{
  #if (IOHWAB_USE_ANA_SUP_SWT == STD_OFF)
  StatusType LddError = E_NOT_OK;
  #endif /* (IOHWAB_USE_ANA_SUP_SWT == STD_OFF) */

  /* This task is used to filter all inputs */
  switch (IoHwAb_GucInAcqState)
  {
  case IOHWAB_ACQ_DIGITAL :
    /* slow digital inputs debouncing (direct, mux) */
    #if (IOHWAB_USE_DIG_IN == STD_ON)
    IoHwAb_DigInDebounce(IOHWAB_NUM_DIGIN_FAST, IOHWAB_NUM_DIGIN_SLOW);
    #endif /* (IOHWAB_USE_DIG_IN == STD_ON) */

    #if (IOHWAB_USE_ANA_IN == STD_ON)
    /* Next step will be acquisition of analog inputs */
    IoHwAb_GucInAcqState = IOHWAB_ACQ_ANALOG;
    #if (IOHWAB_USE_ANA_SUP_SWT == STD_ON)
    /* switch on switched battery for analog inputs */
    IoHwAb_InputSupplyAnalogControl(TRUE);
    #if (IOHWAB_USE_IO_MAN_FASTTIMER == STD_ON)
    /* Start Timer for switched battery delay */
    (void) CoSvAb_FastTimerStart(IOHWAB_IOM_FAST_TIMER_ID, IoHwAb_GddISupplyAnaSwitchDelay);
    #endif /* (IOHWAB_USE_IO_MAN_FASTTIMER == STD_ON) */
    #if (IOHWAB_USE_IO_MAN_GPTTIMER == STD_ON)
    #if (IOHWAB_IOM_GPT_TICKS_FOR_1US == IOHWAB_ONE)
    /* Start Timer for switched battery delay */
    Gpt_StartTimer(IOHWAB_IOM_GPT_TIMER_ID, (uint32)IoHwAb_GddISupplyAnaSwitchDelay);
    #else
    /* Start Timer for switched battery delay */
    Gpt_StartTimer(IOHWAB_IOM_GPT_TIMER_ID,
      ((uint32)IoHwAb_GddISupplyAnaSwitchDelay * (uint32)IOHWAB_IOM_GPT_TICKS_FOR_1US));
    #endif /* (IOHWAB_IOM_GPT_TICKS_FOR_1US == IOHWAB_ONE) */
    #endif /* (IOHWAB_USE_IO_MAN_GPTTIMER == STD_ON) */
    #else /* (IOHWAB_USE_ANA_SUP_SWT == STD_ON) */
    /* start acquisition of analog inputs directly, activate acquisition task */
#if defined(IOHWAB_IOM_TASK_FG2)
    LddError = IoHwAb_IOMActivateTask(IoHwAb_GddIOMTaskFG2);
    if(LddError == E_OK)
    {
    }
#endif /* (IOHWAB_IOM_TASK_FG2)      */
    #endif /* (IOHWAB_USE_ANA_SUP_SWT == STD_ON) */
    #else /* (IOHWAB_USE_ANA_IN == STD_ON) */
    /* IO acquisition and filtering is finished */
    IoHwAb_GucInAcqState = IOHWAB_ACQ_NO_ACTION;

    #if (IOHWAB_USE_LP_FLAG == STD_ON)
    /* Clear the Lowpower Flag */
    BswM_RequestMode((BswM_UserType)IOHWAB_MODULE_ID, (BswM_ModeType)IOHWAB_LOWPOWER_ALLOW);
    #endif /* (IOHWAB_USE_LP_FLAG == STD_ON) */
    #endif /* (IOHWAB_USE_ANA_IN == STD_ON) */
    break;

  case IOHWAB_ACQ_ANALOG :
    /* Do nothing */
  case IOHWAB_ACQ_ANALOG_MUX :
    /* Do nothing */
  case IOHWAB_ACQ_ANALOG_END :
    /* do analog filtering for analog inputs (direct and mux) */
    #if (IOHWAB_USE_ANA_IN == STD_ON)
    IoHwAb_AnaInFilter();
    #endif /* (IOHWAB_USE_ANA_IN == STD_ON) */
    /* IO acquisition and filtering is finished */
    IoHwAb_GucInAcqState = IOHWAB_ACQ_NO_ACTION;

    #if (IOHWAB_USE_LP_FLAG == STD_ON)
    /* Clear the Lowpower Flag */
    BswM_RequestMode((BswM_UserType)IOHWAB_MODULE_ID, (BswM_ModeType)IOHWAB_LOWPOWER_ALLOW);
    #endif /* (IOHWAB_USE_LP_FLAG == STD_ON) */
    break;

  default:
    /* Do nothing */
    break;
  }

  /****end user code******/
  (void) TerminateTask();
}
#endif /* (IOHWAB_IOM_TASK_FG1)      */
/*******************************************************************************
** Function Name        : IoHwAb_IOMActivateTask                              **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          :                                                     **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Reentrancy           : Non Reentrant                                       **
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
**                                                                            **
**                        Function(s) invoked    :                            **
**                          GetTaskState,                                     **
**                          ActivateTask,                                     **
**                          CoSvAb_FastTimerStart,                            **
**                          Gpt_StartTimer,                                   **
*******************************************************************************/
static FUNC(StatusType, IOHWAB_CODE)IoHwAb_IOMActivateTask(TaskType TaskId)
{
  StatusType LddError = E_NOT_OK;
  TaskStateType LddTaskState = RUNNING;

  LddError = GetTaskState(TaskId, &LddTaskState);

  if ((LddError == E_OK)
    && (LddTaskState == SUSPENDED))
  {
    LddError = ActivateTask(TaskId);
  }

  if ((LddError != E_OK)
    || (LddTaskState != SUSPENDED))
  {
    #if (IOHWAB_USE_IO_MAN_FASTTIMER == STD_ON)
    /* if task is already in use, wait IoHwAb_GddIOMMultiActDelay us */
    (void) CoSvAb_FastTimerStart((CoSvAb_TimerType)IOHWAB_IOM_FAST_TIMER_ID, (CoSvAb_FastTimerDelay)IOHWAB_IOM_MULTI_ACT_DELAY);
    #endif /* (IOHWAB_USE_IO_MAN_FASTTIMER == STD_ON) */
    #if (IOHWAB_USE_IO_MAN_GPTTIMER == STD_ON)
    #if (IOHWAB_IOM_GPT_TICKS_FOR_1US == IOHWAB_ONE)
    /* if task is already in use, wait IoHwAb_GddIOMMultiActDelay us */
    Gpt_StartTimer(IOHWAB_IOM_GPT_TIMER_ID, (uint32)IOHWAB_IOM_MULTI_ACT_DELAY);
    #else
    /* if task is already in use, wait IoHwAb_GddIOMMultiActDelay us */
    Gpt_StartTimer(IOHWAB_IOM_GPT_TIMER_ID,
      ((uint32)IOHWAB_IOM_MULTI_ACT_DELAY * (uint32)IOHWAB_IOM_GPT_TICKS_FOR_1US));
    #endif /* (IOHWAB_IOM_GPT_TICKS_FOR_1US == IOHWAB_ONE) */
    #endif /* (IOHWAB_USE_IO_MAN_GPTTIMER == STD_ON) */
    LddError = E_NOT_OK;
  }

  return LddError;
}

/*polyspace:end<MISRA-C:8.1:Not a defect:Justify with annotations> No Impact of this rule violation*/
/*polyspace:end<MISRA-C:10.1:Not a defect:Justify with annotations> No Impact of this rule violation*/
/*polyspace:end<RTE: ABS_ADDR : Not a defect : No Action Planned >  */
/* polyspace-end RTE:UNR [Not a defect:Unset] "Reachable code" */



#endif /* (IOHWAB_USE_IO_MAN == STD_ON) */

#if (IOHWAB_USE_DIG_OUT == STD_ON)
/*******************************************************************************
** Function Name        : IoHwAb_Demultiplexed                              **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          :                                                     **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Reentrancy           : Non Reentrant                                       **
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
**                                                                            **
**                        Function(s) invoked    :                            **
**                          IoHwAb_DigOutL9826,                               **
**                          IoHwAb_DigOutL99MC6,                              **
**                          IoHwAb_DigOutTLE7240SL,                           **
*******************************************************************************/
static FUNC(void, IOHWAB_CODE)IoHwAb_Demultiplexed(void)
{
  /* update buffered outputs except demultiplexed digital outputs  */
  IoHwAb_DigOutWriteOutputsToHW();
  
  #if (IOHWAB_USE_L9826 == STD_ON)
  /* update the L9826 demultiplexed outputs */
  (void)IoHwAb_DigOutL9826();
  #endif /* (IOHWAB_USE_L9826 == STD_ON) */

  #if (IOHWAB_USE_L99MC6 == STD_ON)
  /* update the L99MC6 demultiplexed outputs */
  (void)IoHwAb_DigOutL99MC6();
  #endif /* (IOHWAB_USE_L99MC6 == STD_ON) */

  #if (IOHWAB_USE_TLE7240SL == STD_ON)
  /* update the TLE7240SL demultiplexed outputs */
  (void)IoHwAb_DigOutTLE7240SL();
  #endif /* (IOHWAB_USE_TLE7240SL == STD_ON) */
}
#endif /* (IOHWAB_USE_DIG_OUT == STD_ON) */

#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/

