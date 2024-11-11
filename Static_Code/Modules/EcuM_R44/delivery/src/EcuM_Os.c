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
**  FILE-NAME : EcuM_Os.c                                                     **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR EcuM Module                                           **
**                                                                            **
**  PURPOSE   : Os Related Functionality implementation of EcuM               **
**              EcuM_IncrementTimer                                           **
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
** 1.2.0     04-Oct-2022   TriBD             R44-Redmine #27878               **
**           25-Nov-2022   Manje Woo         R44-Redmine #31620               **
** 0.0.2     07-Apr-2020   LocLT5            R44-Redmine #655, #8670          **
** 0.0.1     14-Feb-2020   ThangMA            R44-Redmine #655, #8668         **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "EcuM.h"
#include "EcuM_Os.h"
#include "EcuM_Ram.h"
#include "SchM_EcuM.h"

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

/*******************************************************************************
** Function Name        : EcuM_IncrementTimer                                 **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : For incrementing the timer every 1 second           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non-Reentrant, Non-Interruptible                    **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : The ECU state Manager must be initialized           **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        EcuM_RunningTimer                                   **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        None                                                **
*******************************************************************************/
#if (STD_ON == ECUM_ALARM_CLOCK_PRESENT)
#define ECUM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, ECUM_CODE) EcuM_IncrementTimer(void)
{
  /* Initialize prescale with value zero */
  uint32 prescale = (uint32)ECUM_ZERO;

  /* update EcuM clock in the Up phase and sleep phase */
  if(EcuM_State == ECUM_STATE_APP_RUN)
  {
    /* polyspace-begin DEFECT:DEAD_CODE [Justified:Medium] "Reachable code by configuration change" */
    /* polyspace-begin MISRA-C3:2.1 [Justified:Medium] "Reachable code by configuration change" */
    /* polyspace-begin MISRA-C3:14.3 [Justified:Medium] "Reachable code by configuration change" */
    /* polyspace-begin RTE:UNR [Not a defect:Low] "Reachable code by configuration change" */
	SchM_Enter_EcuM_ALARM_TIME_PROTECTION();
	/* @Trace: EcuM_SUD_API_954 */
    /* if the main function period is greater than EcuM clock time */
    if (ECUM_MAIN_FUNCTION_PERIOD > ECUM_CLOCK_PERIOD)
    {
      prescale = (uint32)(ECUM_MAIN_FUNCTION_PERIOD/ECUM_CLOCK_PERIOD);
      /* Update the EcuM clock time when every main function period was passed */
      EcuM_RunningTimer += prescale;
    }
    else
    {
      /* @Trace: EcuM_SUD_API_953 */
      /* increase the counter */
      EcuM_RunCounterTime++;
      prescale = (uint32)(ECUM_CLOCK_PERIOD/ECUM_MAIN_FUNCTION_PERIOD);
      /* Update the EcuM clock time when one sec of time has been accumulated */
      if (prescale == EcuM_RunCounterTime)
      {
        /*
         *   MISRA Rule        : 17.4
         *   Message           : Performing pointer arithmetic.
         *   Reason            : Array Indexing is not used to achieve better
         *                       throughput.
         *   Verification      : However, part of the code is verified manually
         *                       and it is not having any impact.
         */
        EcuM_RunningTimer++;
        /* clear the counter */
        EcuM_RunCounterTime = (uint32)ECUM_ZERO;
      }
    }
    SchM_Exit_EcuM_ALARM_TIME_PROTECTION();
    /* polyspace-end DEFECT:DEAD_CODE */
    /* polyspace-end MISRA-C3:2.1 */
    /* polyspace-end MISRA-C3:14.3 */
    /* polyspace-end RTE:UNR */
  }
}
#define ECUM_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/

