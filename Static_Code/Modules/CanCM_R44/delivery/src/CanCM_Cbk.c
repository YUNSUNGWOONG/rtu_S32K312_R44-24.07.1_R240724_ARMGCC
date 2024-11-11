/* polyspace +1 MISRA2012:1.1 [Not a defect:Low] "The number of macros doesn't master." */
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
**  SRC-MODULE: CanCM_Cbk.c                                                   **
**                                                                            **
**  TARGET    : General CAN Communication Manager                             **
**                                                                            **
**  PRODUCT   : AUTOEVER CAN Communication Manager Module                     **
**                                                                            **
**  PURPOSE   : Provision API for ComM indicating mode                        **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: yes                                          **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By               Description                       **
********************************************************************************
** 1.0.9     20-Dec-2023   HieuTM8          CP44-3561                         **
** 1.0.3.1   29-Jun-2022   NhatTD2          CP44-135                          **
** 1.0.2     23-Feb-2022   HieuTM8          Redmine #20448                    **
** 1.0.1     22-Sep-2021   LinhTT36         Redmine #20380                    **
** 1.0.0     22-Dec-2020   SJ Kim           Initial Version                   **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/


#include "CanCM_Cbk.h"
#include "SchM_CanCM.h"


/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

/*******************************************************************************
** Function Name        : CanCM_ComModeIndication                             **
**                                                                            **
** Service ID           : 0x03U                                               **
**                                                                            **
** Description          : This function is called by ComM for indicating mode **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : channelIdComm : channel ID in ComM side             **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                            CanCM_LastChannelID                             **
**                            CanCM_GaaCanCMComMChannelMap[]                  **
**                            CanCM_DevErrorDetect                            **
**                            CanCM_WakeupSupport                             **
**                            CanCM_GunFlagStatus[]                           **
**                            CanCM_GddCommStat[]                             **
**                            CanCM_GddRTimerCounter[]                        **
**                            CanCM_GddNTimerCounter[]                        **
**                            CanCM_GddETimerCounter[]                        **
**                            CanCM_GddVolMod[]                               **
**                            CanCM_GaaChannelConfig[]                        **
**                        Function(s) invoked :                               **
**                            Det_ReportError                                 **
**                            BswM_RequestMode                                **
*******************************************************************************/
#define CANCM_START_SEC_CODE
#include "MemMap.h"
/* @Trace: CanCM_SUD_DATATYPE_011 */
/* @Trace: 
 * SRS_CanCM_ES95400_30E_00007 SRS_CanCM_ES95400_30E_00035 SRS_BSW_00337 SRS_CanCM_ES95400_30E_00002 SRS_CanCM_ES95400_30E_00003
 * SRS_CanCM_ES95400_30E_00006
 */
 /* @Trace: CanCM_SUD_API_010 */
FUNC(void, CANCM_CODE) CanCM_ComModeIndication (NetworkHandleType channelIdComm,ComM_ModeType commState)
{

  VAR(NetworkHandleType,CANCM_VAR) channelIndex;

  /* if ComM channel id is greater than total channels */
  /* polyspace-begin MISRA-C3:18.1 [Not a defect:Low] "The size of array is pre-defined, The value of channelIdComm is already checked before used" */
  /* polyspace-begin RTE:UNR [Not a defect:Low] "The section is reachable in another configuration, CanCM is a lib module"*/
  /* polyspace +2 RTE:IDP [Not a defect:Low] "The size of array is pre-defined, The value of channelIdComm is already checked before used" */
  /* polyspace +1 MISRA-C3:D4.1 [Not a defect:Low] "The size of array is pre-defined, the value of channelIdComm is checked before used" */
  if ((channelIdComm > CanCM_LastChannelID) ||(CanCM_ComMChannelMap[channelIdComm] == CANCM_INVALID_CHANNEL))
  {
    /* 
     * polyspace-begin MISRA2012:14.3 [Not a defect:Low] "It's changed in GEN code" 
     * polyspace-begin MISRA2012:2.1 [Not a defect:Low] "It's changed in GEN code" 
     * polyspace-begin DEFECT:DEAD_CODE [Not a defect:Low] "The value of the variable CanCM_DevErrorDetect can be changed depending on configuration as CanCm is lib module"
     * polyspace-begin DEFECT:USELESS_IF [Not a defect:Low] "If-condition is not always true, the value of the variable can be changed depending on generated code"
     * polyspace-begin RTE:UNR [Not a defect:Low] "If-condition is not always false, CanCM is a lib module and the value of CanCM_DevErrorDetect can be changed by configuration"
     */
    #if(STD_ON == CANCM_DEV_ERROR_DETECT)
      /* Report error to DET */
      (void)Det_ReportError(
              CANCM_MODULE_ID,
              CANCM_INSTANCE_ID,
              CANCM_COMMODEINDICATION_SID,
              CANCM_E_INVALID_REQUEST);
    #endif
    /* 
     * polyspace-end MISRA2012:14.3 [Not a defect:Low] "It's changed in GEN code" 
     * polyspace-end MISRA2012:2.1 [Not a defect:Low] "It's changed in GEN code" 
     * polyspace-end DEFECT:DEAD_CODE [Not a defect:Low] "The value of the variable CanCM_DevErrorDetect can be changed depending on configuration as CanCm is lib module"
     * polyspace-end DEFECT:USELESS_IF [Not a defect:Low] "If-condition is not always true, the value of the variable can be changed depending on generated code"
     * polyspace-end RTE:UNR [Not a defect:Low] "If-condition is not always false, CanCM is a lib module and the value of CanCM_DevErrorDetect can be changed by configuration"
     */

  }
  else
  {
    /* polyspace-begin MISRA-C3:D4.1 [Not a defect:Low] "The size of array is pre-defined, the validity channelIndex is verified by generated code */
    /* polyspace-begin RTE:OBAI [Not a defect:Low] "The size of array is pre-defined, The value of channelIdIndex is already checked before used" */
    /* map to channel-id of CanCM */
    /* @Trace: CanCM_SUD_API_011 */
    channelIndex = CanCM_ComMChannelMap[channelIdComm];
    
    /* ComM state is NOCOM */
    if (COMM_NO_COMMUNICATION == commState)
    {
      /* polyspace-begin MISRA-C3:2.1 [Not a defect:Low] "if-condition is not always true, the value of the variable can be changed depending on generated code" */
      /* polyspace-begin DEFECT:DEAD_CODE [Not a defect:Low] "The value of the variable CanCM_WakeupSupport can be changed depending on configuration, CanCm is lib module" */
      /* polyspace +3 RTE:UNR [Not a defect:Low] "If-condition is not always false, CanCM is a lib module and the value of CanCM_WakeupSupport can be changed by configuratio" */
      /* polyspace +1 MISRA2012:14.3 [Not a defect:Low] "It's changed in GEN code"*/
      #if(STD_ON == CANCM_WAKEUP_SUPPORT)
        /* @Trace: CanCM_SUD_API_038 */
        /* enable wake-up event */
        /* polyspace +3 MISRA-C3:18.1 [Not a defect:Low] "The size of array is pre-defined, the value of channelIndex  is checked before used" */
        /* polyspace +2 RTE:OBAI [Not a defect:Low] "The size of array is pre-defined, The value of channelIdIndex is already checked by generator" */
        SchM_Enter_CanCM_MAIN_PROTECTION();
        CanCM_FlagStatus[channelIndex]
              .BitByteRecord.WakChkEnabled = CANCM_ONE;
        SchM_Exit_CanCM_MAIN_PROTECTION();
      #endif
      /* polyspace-end MISRA-C3:2.1 [Not a defect:Low] "if-condition is not always true, the value of the variable can be changed depending on generated code" */
      /* polyspace-end DEFECT:DEAD_CODE [Not a defect:Low] "The value of the variable CanCM_WakeupSupport can be changed depending on configuration, CanCm is lib module" */
      /* Current state is SHUTDOWN */
      /* @Trace: CanCM_SUD_API_012 */
      /* polyspace-begin MISRA-C3:18.1 [Not a defect:Low] "The size of array is pre-defined, the value of channelIndex is checked before used" */
      if (CANCM_COMM_STAT_SHUTDOWN  == CanCM_CommStat[channelIndex])
      {
        /* CAN Network is in Bus Sleep Mode */
        CanCM_CommStat[channelIndex] = CANCM_COMM_STAT_INACTIVE;
        /* reset Reception DM Start timer */
        CanCM_RTimerCounter[channelIndex] = CANCM_ZERO;
        /* Disable reception for Com module */
        /* polyspace +4 RTE:IDP [Not a defect:Low] "The size of array is pre-defined, The value of channelIdIndex is already checked before used" */
        BswM_RequestMode(
          (BswM_UserType)CanCMBswmMRxInd(
                CanCM_ChannelConfig[channelIndex].ChannelId),
          (BswM_ModeType)CANCM_COMM_STAT_RX_DISABLED);
        
      }
      /* Current state is not INACTIVE */
      else if (CANCM_COMM_STAT_INACTIVE != CanCM_CommStat[channelIndex])
      {
        /* CAN Network is in Bus Sleep Mode */
        CanCM_CommStat[channelIndex] = CANCM_COMM_STAT_INACTIVE;
        /* Network is switched into Network Inactive without touching *
        *  Network Shutdown                                           *
        *  Reset Reception DM Start timer                             */
        CanCM_RTimerCounter[channelIndex] = CANCM_ZERO;
        /* reset Network Activation timer */
        CanCM_NTimerCounter[channelIndex] = CANCM_ZERO;
        /* reset Voltage Error Delay timer */
        CanCM_ETimerCounter[channelIndex] = CANCM_ZERO;
        /* Disable reception for Com module */
        /* polyspace +4 RTE:IDP [Not a defect:Low] "The size of array is pre-defined, The value of channelIdIndex is already checked before used" */
        BswM_RequestMode(
          (BswM_UserType)CanCMBswmMRxInd(
                CanCM_ChannelConfig[channelIndex].ChannelId),
          (BswM_ModeType)CANCM_COMM_STAT_RX_DISABLED);
        /* Disable Com transmission */
        /* polyspace +1 RTE:IDP [Not a defect:Low] "The size of array is pre-defined, The value of channelIdIndex is already checked before used" */
        BswM_RequestMode((BswM_UserType)CanCMBswmMTxInd(CanCM_ChannelConfig[channelIndex].ChannelId),(BswM_ModeType)CANCM_COMM_STAT_TX_DISABLED);
        /* Mark transmission flag is disabled */
        SchM_Enter_CanCM_MAIN_PROTECTION();
        CanCM_FlagStatus[channelIndex]
                .BitByteRecord.TxDisabled = CANCM_ONE;
        SchM_Exit_CanCM_MAIN_PROTECTION();
      }
      else
      {
        /* Do nothing */
      }


    }
    /* ComM state is SILENT */
    else if (COMM_SILENT_COMMUNICATION == commState)
    {
      /* Current state is ACTIVE */
      /* polyspace-begin RTE:IDP [Not a defect:Low] "The size of array is pre-defined, The value of channelIdIndex is already checked before used" */
      if (CANCM_COMM_STAT_ACTIVE == CanCM_CommStat[channelIndex])
      {
        /* @Trace: CanCM_SUD_API_036 */
        CanCM_CommStat[channelIndex] = CANCM_COMM_STAT_SHUTDOWN;
        /* reset Network Activation timer */
        CanCM_NTimerCounter[channelIndex] = CANCM_ZERO;
        /* reset Voltage Error Delay timer */
        CanCM_ETimerCounter[channelIndex] = CANCM_ZERO;
        /* Disable Com transmission */
        BswM_RequestMode(
          (BswM_UserType)CanCMBswmMTxInd(
                CanCM_ChannelConfig[channelIndex].ChannelId),
          (BswM_ModeType)CANCM_COMM_STAT_TX_DISABLED);
        /* Mark transmission flag is disabled */
        SchM_Enter_CanCM_MAIN_PROTECTION();
        CanCM_FlagStatus[channelIndex]
                .BitByteRecord.TxDisabled = CANCM_ONE;
        SchM_Exit_CanCM_MAIN_PROTECTION();
        /* Notify to BswM to disable DM */
        BswM_RequestMode(
          (BswM_UserType)CanCMBswmMRxInd(
                CanCM_ChannelConfig[channelIndex].ChannelId),
          (BswM_ModeType)CANCM_COMM_STAT_RX_ENABLED_DM_DISABLED);
      }
      /* polyspace-end RTE:IDP [Not a defect:Low] "The size of array is pre-defined, The value of channelIdIndex is already checked before used" */
    }
    /* ComM state is FULLCOM */
    else if (COMM_FULL_COMMUNICATION == commState)
    {
      /* polyspace-begin MISRA-C3:2.1 [Not a defect:Low] "if-condition is not always true, the value of the variable can be changed depending on generated code" */
      /* polyspace-begin DEFECT:DEAD_CODE [Not a defect:Low] "The value of the variable CanCM_WakeupSupport can be changed depending on configuration, CanCm is lib module" */
      /* polyspace +4 RTE:UNR [Not a defect:Low] "If-condition is not always false, CanCM is a lib module and the value of CanCM_WakeupSupport can be changed by configuratio" */
      /* polyspace +2 MISRA2012:14.3 [Not a defect:Low] "It's changed in GEN code"*/
      /* @Trace: CanCM_SUD_API_035 */
      #if(STD_ON == CANCM_WAKEUP_SUPPORT)
      /* In FULLCOMM channel is ACTIVE*/
      SchM_Enter_CanCM_MAIN_PROTECTION();
      CanCM_FlagStatus[channelIndex]
            .BitByteRecord.WakChkEnabled = CANCM_ZERO;
      SchM_Exit_CanCM_MAIN_PROTECTION();
      #endif
      /* polyspace-end DEFECT:DEAD_CODE [Not a defect:Low] "The value of the variable CanCM_WakeupSupport can be changed depending on configuration, CanCm is lib module" */
      SchM_Enter_CanCM_MAIN_PROTECTION();
      /* Nm flag is disable & Voltage is not fail */
      if ((CANCM_ONE == CanCM_FlagStatus[channelIndex]
              .BitByteRecord.NmDisabled) &&
          (CANCM_ZERO == CanCM_FlagStatus[channelIndex]
              .BitByteRecord.VolFailed))
      {
        SchM_Exit_CanCM_MAIN_PROTECTION();
        /* Nm could not be enabled because voltage was recovered during
           Network Shutdown or Inactive */
        /* Notify BswM to invoke Nm_EnableCommunication() */
        /* polyspace +3 RTE:IDP [Not a defect:Low] "The size of array is pre-defined, The value of channelIdIndex is already checked before used" */
        BswM_RequestMode(
          (BswM_UserType)CanCMBswmMVolInd(
                CanCM_ChannelConfig[channelIndex].ChannelId),
          (BswM_ModeType)CANCM_VOL_MODE_NORMAL);
        /* mark Nm flag is enable */
        SchM_Enter_CanCM_MAIN_PROTECTION();
        CanCM_FlagStatus[channelIndex]
                .BitByteRecord.NmDisabled = CANCM_ZERO;
        SchM_Exit_CanCM_MAIN_PROTECTION();
      }
      else
      {
        SchM_Exit_CanCM_MAIN_PROTECTION();
      }
      
      /* If current state is SHUTDOWN */
      if (CANCM_COMM_STAT_SHUTDOWN == CanCM_CommStat[channelIndex])
      {
        /* Change current COMM state to ACTIVE */
        CanCM_CommStat[channelIndex] = CANCM_COMM_STAT_ACTIVE;
        /* Transition to Network Inactive has been canceled.
           Notify BswM for Network Activation                 */
        /* polyspace +3 RTE:IDP [Not a defect:Low] "The size of array is pre-defined, The value of channelIdIndex is already checked before used" */
        BswM_RequestMode(
          (BswM_UserType)CanCMBswmMTxInd(
                CanCM_ChannelConfig[channelIndex].ChannelId),
          (BswM_ModeType)CANCM_COMM_STAT_TX_ENABLED);
        /* mark transmission flag is enable */
        SchM_Enter_CanCM_MAIN_PROTECTION();
        CanCM_FlagStatus[channelIndex]
                .BitByteRecord.TxDisabled = CANCM_ZERO;
        /* If DM timer is expired */
        if (CanCM_FlagStatus[channelIndex]
                .BitByteRecord.DtcDisabled == CANCM_ZERO)
        {
          SchM_Exit_CanCM_MAIN_PROTECTION();
          /* Notify BswM to enable Reception Deadline Monitoring */
          /* polyspace +2 RTE:IDP [Not a defect:Low] "The size of array is pre-defined, The value of channelIdIndex is already checked before used" */
          BswM_RequestMode(
            (BswM_UserType)CanCMBswmMRxInd(
                  CanCM_ChannelConfig[channelIndex].ChannelId),
            (BswM_ModeType)CANCM_COMM_STAT_RX_ENABLED_DM_ENABLED);
        }
        else
        {
          SchM_Exit_CanCM_MAIN_PROTECTION();
        }
      }
      /* If current state is INACTIVE */
      /* polyspace-begin RTE:IDP [Not a defect:Low] "The size of array CanCM_ChannelConfig is pre-defined, The value of channelIdIndex is already checked before used" */
      else if (CANCM_COMM_STAT_INACTIVE == CanCM_CommStat[channelIndex])
      {

        /* Change Current Network State */
        CanCM_CommStat[channelIndex] = CANCM_COMM_STAT_START;
        /* Network Activation Timer shall be started */
        CanCM_NTimerCounter[channelIndex] = 
                CanCM_ChannelConfig[channelIndex].ActivationTime;

        /* Notify BswM for Com Reception to be enabled */
        BswM_RequestMode(
          (BswM_UserType)CanCMBswmMRxInd(
                CanCM_ChannelConfig[channelIndex].ChannelId),
          (BswM_ModeType)CANCM_COMM_STAT_RX_ENABLED_DM_DISABLED);

        /* Start Reception DM Start timer */
        CanCM_RTimerCounter[channelIndex] = 
                CanCM_ChannelConfig[channelIndex].TimeoutStartTime;
        /* In order to start CAN Transmission ASAP if voltage is normal and
        previously error */
        CanCM_ETimerCounter[channelIndex] = CANCM_TWO;
        /* marked current voltage mode normal for channel */
        CanCM_VolMod[channelIndex] = CANCM_VOL_MODE_NORMAL;
      }
      /* polyspace-end RTE:IDP [Not a defect:Low] "The size of array CanCM_ChannelConfig is pre-defined, The value of channelIdIndex is already checked before used" */
      else
      {
        /* Do nothing */
      }
	  /* polyspace-end MISRA-C3:2.1 [Not a defect:Low] "if-condition is not always true, the value of the variable can be changed depending on generated code" */
	  /* polyspace-end MISRA-C3:D4.1 [Not a defect:Low] "The size of array is pre-defined, the validity channelIndex is verified by generated code */
    }
    /* polyspace-begin RTE:UNR [Not a defect:Low] "The section is reachable in another configuration, CanCM is a lib module"*/
    else
    {
      /* invalid comm state */
    }
    /* polyspace-end RTE:UNR [Not a defect:Low] "The section is reachable in another configuration, CanCM is a lib module"*/
  }
  /* polyspace-end RTE:UNR [Not a defect:Low] "The section is reachable in another configuration, CanCM is a lib module"*/
  /* polyspace-end MISRA-C3:18.1 [Not a defect:Low] "The size of array is pre-defined, The value of channelIdIndex is already checked before used" */
  /* polyspace-end RTE:OBAI [Not a defect:Low] "The size of array is pre-defined, The value of channelIdIndex is already checked before used" */
}
#define CANCM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
**                          End of File                                       **
*******************************************************************************/
