/*******************************************************************************
**                            HYUNDAI MOTORS GROUP                            **
**                                                                            **
**                            All rights reserved                             **
**                                                                            **
**            You can NOT use this sample code for Product Release            **
*******************************************************************************/
/*******************************************************************************
**                              Revision History                              **
********************************************************************************
** Revision   Date          By            Description                         **
********************************************************************************
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

#include "LowPower_Callout.h"
#include "Rte_IoHwAb.h"
#include "IoHwAb_IOManager.h"
#include "WdgStack_Callout.h"
#include "WdgM.h"
#include "Gpt.h"
#include "Os_Debug.h"

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#define ECUM_SYST_CSR_ENABLE_MASK 0x00000001u
#define ECUM_SCR_SLEEPDEEP_MASK   0x00000004u

/* polyspace-begin MISRA-C3:11.4 [Justified:Low] "It is for accessing register address" */
/* polyspace-begin MISRA-C3:20.7 [Jusitifed:Low] "To access Register address" */
//CONSTP2VAR(volatile Mcu_Cm4ScsRegType, AUTOMATIC, REGSPACE) EcuM_Cm4ScsRegBaseAddr =
//                                    (volatile Mcu_Cm4ScsRegType *)MCU_SYSTEM_CM4_SCS_REG_BASE_ADDR;
/* polyspace-end MISRA-C3:11.4 [Justified:Low] "It is for accessing register address" */
/* polyspace-end MISRA-C3:20.7 [Jusitifed:Low] "To access Register address" */

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define ECUM_START_SEC_CALLOUT_CODE
#include "MemMap.h"

/*******************************************************************************
 * Function Name        : EcuM_H2LTransition_Callout_Swp
 *
 * Service ID           : NA
 *
 * Description          : Callout for SWP in Sleep Sequence
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Non Re-entrant
 *
 * Parameters           : None
 *
 * @return              : void
 *
 * @pre                 : None
 *
 * @remarks             : Global Variable(s)     :
 *                        None
 *
 *                        Function(s) invoked    :
 *                        SchM_Enter_EcuM_WAKEUP_STATUS_PROTECTION(),
 *                        SchM_Exit_EcuM_WAKEUP_STATUS_PROTECTION(),
 *                        WdgStack_TransitHighToLow(),
 *                        IoHwAb_IOMH2L(), Os_DebugH2L(), Gpt_SetMode()
 ******************************************************************************/
FUNC(void, ECUM_CALLOUT_CODE) EcuM_H2LTransition_Callout_Swp(void)
{
  SchM_Enter_EcuM_WAKEUP_STATUS_PROTECTION();

  /* Stop OS Counter for Main Core */
//  EcuM_Cm4ScsRegBaseAddr->SYST_CSR &= ~ECUM_SYST_CSR_ENABLE_MASK;

  SchM_Exit_EcuM_WAKEUP_STATUS_PROTECTION();

  #if (IOHWAB_USE_IO_MAN == STD_ON)
  (void)IoHwAb_IOMH2L();
  #endif
  (void)Os_DebugH2L();

  (void)WdgStack_TransitHighToLow();

  /* All Gpt channels that are not enabled for wakeup and
   * all enabled GPT Predef Timers are stopped. */
  Gpt_SetMode(GPT_MODE_SLEEP);
}

/*******************************************************************************
 * Function Name        : EcuM_H2LTransition_Callout_App
 *
 * Service ID           : NA
 *
 * Description          : User Callout for Sleep Sequence
 *                        The application should take the necessary action here
 *                        before switching to Low Power Mode
 *                        - Disable unnecessary peripherals in Low Power Mode
 *                        - Enable Wakeup sources(ex: Icu channel, Gpt channel)
 *                        - Check early wakeup
 *                        - Apply workaround for MCU Errata
 *                        - etc
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Non Re-entrant
 *
 * Parameters           : None
 *
 * @return              : void
 *
 * @pre                 : None
 *
 * @remarks             : Global Variable(s)     :
 *                        None
 *
 *                        Function(s) invoked    :
 *                        Icu_EnableEdgeDetection(), Icu_EnableNotification(),
 *                        Icu_DisableEdgeDetection(), Icu_DisableNotification(),
 *                        IoHwAb_DigDirReadDirect(), EcuM_SetWakeupEvent(),
 *                        SchM_Enter_EcuM_WAKEUP_STATUS_PROTECTION(),
 *                        SchM_Exit_EcuM_WAKEUP_STATUS_PROTECTION()
 ******************************************************************************/
FUNC(void, ECUM_CALLOUT_CODE) EcuM_H2LTransition_Callout_App(void)
{
  IoHwAb_LevelType LddLevel;
  EcuM_WakeupSourceType LddWakeupMask;

  SchM_Enter_EcuM_WAKEUP_STATUS_PROTECTION();

  LddWakeupMask = ECUM_WKSOURCE_NONE;

  /* Enable Wakeup Signals */
  (void)Icu_EnableEdgeDetection(IcuConf_IcuChannel_IcuChannel_FD_CAN1_RX);
  (void)Icu_EnableNotification(IcuConf_IcuChannel_IcuChannel_FD_CAN1_RX);

  /*****************************************************************************
   * Check that the pin level has already changed before ICU Edge Detection is
   * enabled
   ****************************************************************************/
  (void)IoHwAb_DigDirReadDirect((uint16)IoHwAbDigitalDirectLogical_FD_CAN1_RX, &LddLevel);

  if (LddLevel == (IoHwAb_LevelType)IOHWAB_LOW)
  {
    LddWakeupMask |= ECUM_WKSOURCE_FD_CAN1_RX_POLL;
  }

  if (LddWakeupMask != ECUM_WKSOURCE_NONE)
  {
    /* Disable all Wakeup Signals */
    (void)Icu_DisableEdgeDetection(IcuConf_IcuChannel_IcuChannel_FD_CAN1_RX);
    (void)Icu_DisableNotification(IcuConf_IcuChannel_IcuChannel_FD_CAN1_RX);
  }

  SchM_Exit_EcuM_WAKEUP_STATUS_PROTECTION();

  if ((LddWakeupMask & ECUM_WKSOURCE_FD_CAN1_RX_POLL) == ECUM_WKSOURCE_FD_CAN1_RX_POLL)
  {
    /* Do not execute in interrupt disabled region */
    (void)EcuM_SetWakeupEvent(ECUM_WKSOURCE_FD_CAN1_RX_POLL);
  }
}

/*******************************************************************************
 * Function Name        : EcuM_L2HTransition_Callout_Swp
 *
 * Service ID           : NA
 *
 * Description          : Callout for SWP in Wakeup Sequence
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Non Re-entrant
 *
 * Parameters           : None
 *
 * @return              : void
 *
 * @pre                 : None
 *
 * @remarks             : Global Variable(s)     :
 *                        None
 *
 *                        Function(s) invoked    :
 *                        WdgStack_TransitLowToHigh(), WdgM_PmModeChange(),
 *                        SchM_Enter_EcuM_WAKEUP_STATUS_PROTECTION(),
 *                        SchM_Exit_EcuM_WAKEUP_STATUS_PROTECTION(),
 *                        IoHwAb_IOML2H(), Gpt_SetMode()
 ******************************************************************************/
FUNC(void, ECUM_CALLOUT_CODE) EcuM_L2HTransition_Callout_Swp(void)
{
  /* All channels and all enabled GPT Predef Timers are permitted to run.
   * Restart all enabled GPT Predef Timers
   * but does not restart any timer channels that were stopped */
  (void)Gpt_SetMode(GPT_MODE_NORMAL);

  #if (IOHWAB_USE_IO_MAN == STD_ON)
  (void)IoHwAb_IOML2H();
  #endif

  (void)WdgStack_TransitLowToHigh();

  SchM_Enter_EcuM_WAKEUP_STATUS_PROTECTION();

  /* Resume OS Counter for Main Core */
//  EcuM_Cm4ScsRegBaseAddr->SYST_CSR |= ECUM_SYST_CSR_ENABLE_MASK;
  /* Clear SLEEPDEEP bit from System Control Register in Core */
//  EcuM_Cm4ScsRegBaseAddr->SCR &= ~ECUM_SCR_SLEEPDEEP_MASK;

  SchM_Exit_EcuM_WAKEUP_STATUS_PROTECTION();
}

/*******************************************************************************
 * Function Name        : EcuM_L2HTransition_Callout_App
 *
 * Service ID           : NA
 *
 * Description          : User Callout for Wakeup Sequence
 *                        The application should take the necessary action here
 *                        before switching to RUN Mode
 *                        - Enable necessary peripherals in High Power Mode
 *                        - Disable Wakeup sources(ex: Icu channel, Gpt channel)
 *                        - Apply workaround for MCU Errata
 *                        - etc
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Non Re-entrant
 *
 * Parameters           : None
 *
 * @return              : void
 *
 * @pre                 : None
 *
 * @remarks             : Global Variable(s)     :
 *                        Lp_GaaAdcStatus, Lp_GulPitStatus, Lp_GaaStm0Status,
 *                        Lp_GaaStm2Status
 *
 *                        Function(s) invoked    :
 *                        Icu_DisableEdgeDetection(), Icu_DisableNotification(),
 *                        SchM_Enter_EcuM_WAKEUP_STATUS_PROTECTION(),
 *                        SchM_Exit_EcuM_WAKEUP_STATUS_PROTECTION()
 ******************************************************************************/
FUNC(void, ECUM_CALLOUT_CODE) EcuM_L2HTransition_Callout_App(void)
{
  SchM_Enter_EcuM_WAKEUP_STATUS_PROTECTION();

  /* Disable all Wakeup Signals */
  (void)Icu_DisableEdgeDetection(IcuConf_IcuChannel_IcuChannel_FD_CAN1_RX);
  (void)Icu_DisableNotification(IcuConf_IcuChannel_IcuChannel_FD_CAN1_RX);

  SchM_Exit_EcuM_WAKEUP_STATUS_PROTECTION();
}

/*******************************************************************************
 * Function Name        : EcuM_Boot_Callout
 *
 * Service ID           : NA
 *
 * Description          : User Callout for Before SWP Start
 *                        If MCU wakes up in Low Power Mode and operates as a
 *                        reset sequence. This callout can be used to identify
 *                        the wakeup and implement the required behavior.
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Non Re-entrant
 *
 * Parameters           : None
 *
 * @return              : void
 *
 * @pre                 : Interrupt cannot be used because it is before StartOS
 *                        Can not use SWP and MCAL API
 *
 * @remarks             : Global Variable(s)     :
 *                        None
 *
 *                        Function(s) invoked    :
 *                        None
 ******************************************************************************/
FUNC(void, ECUM_CALLOUT_CODE) EcuM_Boot_Callout(void)
{
  /* Example: Check Wakeup Factor and action
   * If <Wakeup Factor == External Wakeup>
   * {
   *   <Necessary Functionality Initialize>
   *   <User Action>
   *   <Enter LP Again or Proceed to SWP Init>
   * }
   */
}

/*******************************************************************************
 * Function Name        : EcuM_PostInitUser
 *
 * Service ID           : NA
 *
 * Description          : User Callout called after DriverInitOne
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Non Re-entrant
 *
 * Parameters           : None
 *
 * @return              : void
 *
 * @pre                 : None
 *
 * @remarks             : Global Variable(s)     :
 *                        None
 *
 *                        Function(s) invoked    :
 *                        Icu_DisableEdgeDetection()
 ******************************************************************************/
FUNC(void, ECUM_CALLOUT_CODE) EcuM_PostInitUser(void)
{

}

/***************************************************************************//**
 * Function Name        : CheckWakeup_FD_CAN1_RX
 *
 * Service ID           : NA
 *
 * Description          : Notification for IcuChannel_FD_CAN1_RX
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Non Re-entrant
 *
 * Parameters           : None
 *
 * @return              : void
 *
 * @pre                 : The function name shall be set in the Signal
 *                        Notification field of the corresponding ICU Channel
 *
 * @remarks             : Global Variable(s)     :
 *                        None
 *
 *                        Function(s) invoked    :
 *                        Icu_DisableEdgeDetection(), Icu_DisableNotification(),
 *                        SchM_Enter_EcuM_WAKEUP_STATUS_PROTECTION(),
 *                        SchM_Exit_EcuM_WAKEUP_STATUS_PROTECTION(),
 *                        EcuM_SetWakeupEvent()
 ******************************************************************************/
FUNC(void, ECUM_CALLOUT_CODE) CheckWakeup_FD_CAN1_RX(void)
{
  SchM_Enter_EcuM_WAKEUP_STATUS_PROTECTION();

  (void)Icu_DisableEdgeDetection(IcuConf_IcuChannel_IcuChannel_FD_CAN1_RX);
  (void)Icu_DisableNotification(IcuConf_IcuChannel_IcuChannel_FD_CAN1_RX);

  /* Wakeup Sequence */
  (void)EcuM_SetWakeupEvent(ECUM_WKSOURCE_FD_CAN1_RX);

  SchM_Exit_EcuM_WAKEUP_STATUS_PROTECTION();
}

/*******************************************************************************
 * Function Name        : IcuSignalNotification_FD_CAN1_RX
 *
 * Service ID           : NA
 *
 * Description          : Notification for IcuChannel_CAN0RX
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Non Re-entrant
 *
 * Parameters           : None
 *
 * @return              : void
 *
 * @pre                 : The function name shall be set in the Signal
 *                        Notification field of the corresponding ICU Channel
 *
 * @remarks             : Global Variable(s)     :
 *                        None
 *
 *                        Function(s) invoked    :
 *                        Icu_DisableEdgeDetection(), Icu_DisableNotification()
 ******************************************************************************/
FUNC(void, ICU_CALLOUT_CODE) IcuSignalNotification_FD_CAN1_RX(void)
{
  Icu_DisableEdgeDetection(IcuConf_IcuChannel_IcuChannel_FD_CAN1_RX);
  Icu_DisableNotification(IcuConf_IcuChannel_IcuChannel_FD_CAN1_RX);
}

#define ECUM_STOP_SEC_CALLOUT_CODE
#include "MemMap.h"
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
