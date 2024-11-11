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
**  SRC-MODULE: CanCM.c                                                       **
**                                                                            **
**  TARGET    : General CAN Communication Manager                             **
**                                                                            **
**  PRODUCT   : AUTOEVER CAN Communication Manager Module                     **
**                                                                            **
**  PURPOSE   : Provision APIs of CanCM module                                **
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
** 1.0.7     20-Jun-2023   HieuTM8          CP44-2219                         **
** 1.0.6.0   04-Nov-2022   JW Oh            CP44-752                          **
** 1.0.5.0   14-Oct-2022   NhatTD2          CP44-833, CP44-812                **
** 1.0.3.1   29-Jun-2022   NhatTD2          CP44-135                          **
** 1.0.3     14-Apr-2022   HieuTM8          Redmine #26375                    **
** 1.0.2     23-Feb-2022   HieuTM8          Redmine #20448                    **
** 1.0.1     22-Sep-2021   LinhTT36         Redmine #20380                    **
** 1.0.0     22-Dec-2020   SJ Kim           Initial Version                   **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "CanCM.h"               /* CanCM header file */
/* @Trace: SRS_BSW_00301 */
#include "Rte_IoHwAb.h"
#include "CanCM_Error.h"         /* CanCM DET header file */
#include "SchM_CanCM.h"

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

#if(STD_ON == CANCM_WAKEUP_SUPPORT)
static FUNC(void, CANCM_CODE) CanCM_CheckRemoteWakeup(
  CanCM_ChannelType channelIdCanCm);
#endif

static FUNC(void, CANCM_CODE) CanCM_ReadBattery(
  P2VAR(uint16, AUTOMATIC, CANCM_VAR) pusAdcValue);

static FUNC(void, CANCM_CODE) CanCM_CheckTimeOut(
  CanCM_ChannelType channelIdCanCm);

static FUNC(void, CANCM_CODE) CanCM_Check_ETimerCounter(
  CanCM_ChannelType channelIdCanCm);

#if(CANCM_BATMON_CONFIG_EXIST == STD_ON)
static FUNC(void, CANCM_CODE) CanCM_Check_Critical_Voltage(
  CanCM_ChannelType channelIdCanCm);
#endif

static FUNC(void, CANCM_CODE) CanCM_CheckVoltage(
  CanCM_ChannelType channelIdCanCm);

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

/*******************************************************************************
** Function Name        : CanCM_Init                                          **
**                                                                            **
** Service ID           : 0x01U                                               **
**                                                                            **
** Description          : This function initialize CanCM to originally state  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
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
** Remarks              : Global Variable(s)  :                               **
**                            CanCM_NTimerCounter[]                           **
**                            CanCM_ETimerCounter[]                           **
**                            CanCM_RTimerCounter[]                           **
**                            CanCM_FlagStatus[]                              **
**                            CanCM_VolMod[]                                  **
**                            CanCM_CommStat[]                                **
**                            CanCM_BatVolFailCnt                             **
**                            CanCM_AdcSampleCnt                              **
**                            CanCM_BatVol                                    **
**                            CanCM_CanCMStatus                               **
**                        Function(s) invoked :                               **
**                            None                                            **
*******************************************************************************/
#define CANCM_START_SEC_CODE
#include "MemMap.h"
/* @Trace: 
 * SRS_CanCM_ES95400_30E_00018 SRS_CanCM_ES95400_30E_00020 SRS_BSW_00400 SRS_BSW_00438 SRS_BSW_00406 SRS_BSW_00337 SRS_BSW_00339 */
#if(STD_ON==CANCM_VARIANT_POSTBUILD_SUPPORT)
FUNC(void, CANCM_CODE) CanCM_Init(P2CONST(CanCM_ConfigType, AUTOMATIC,CANCM_APPL_CONST) ConfigPtr)
#else
FUNC(void, CANCM_CODE) CanCM_Init(void)
#endif
{
  /* @Trace: CanCM_SUD_API_029 */
  /* polyspace-begin RTE:UNR [Not a defect:Low] "if-condition is not always false as CanCM is a lib module" */
  if((boolean)CANCM_UNINITIALISED == CanCM_CanCMStatus)
  {
    /* Declare looping variable */
    VAR(uint8, CANCM_VAR) count;
    /* declaration of variable which store the selectedConfig */
    #if(STD_ON == CANCM_VARIANT_POSTBUILD_SUPPORT)
    VAR(CanCM_ConfigType,CANCM_VAR) selectedConfig;

    /* declaration of result local variable */
    VAR(Std_ReturnType, CANCM_VAR) result;

    /* polyspace-begin RTE:UNR [Not a defect:Low] "If condition is not always true or false, the secion is reachable in another configuration. CanCM is a lib module" */
    if(NULL_PTR == ConfigPtr)
    {
      /* @Trace: CanCM_SUD_API_031 */
      /* set result to E_NOT_OK */
      result = (Std_ReturnType)E_NOT_OK;

      /* 
       * polyspace-begin MISRA-C3:2.1 [Not a defect:Low] "CanSM is a lib module, the value of variable can be changed according to the configured value of CanCMDevErrorDetect parameter" 
       * polyspace-begin MISRA-C3:14.3 [Not a defect:Low] "The value of the variable can be changed depending on configuration as CanCm is lib module"
       * polyspace-begin DEFECT:DEAD_CODE [Not a defect:Low] "If-condition is not always false, it can be changed depending on configuration"
       */
      /* polyspace +2 DEFECT:USELESS_IF [Not a defect:Low] "If-condition is not always true,the condition can be changed depending on configuration" */
      /* polyspace-begin RTE:UNR [Not a defect:Low] "if-condition is not always false as CanCM is a lib module, the value of CanCM_DevErrorDetect is decided by generated code" */
      if(STD_ON == CanCM_DevErrorDetect)
      {
        /* @Trace: CanCM_SUD_API_032 */
        /* report to Det */
        (void)Det_ReportError(CANCM_MODULE_ID,
        CANCM_INSTANCE_ID, CANCM_INIT_SID, CANCM_E_NULL_POINTER);
      }
      /* polyspace-end RTE:UNR [Not a defect:Low] "if-condition is not always true as CanCM is a lib module, the value of CanCM_DevErrorDetect is decided by generated code" */
      /* 
       * polyspace-end MISRA-C3:2.1 [Not a defect:Low] "CanSM is a lib module, the value of variable can be changed according to the configured value of CanCMDevErrorDetect parameter" 
       * polyspace-end MISRA-C3:14.3 [Not a defect:Low] "The value of the variable can be changed depending on configuration as CanCm is lib module"
       * polyspace-end DEFECT:DEAD_CODE [Not a defect:Low] "If-condition is not always false, it can be changed depending on configuration"
       */
    }
    else
    {
      /* @Trace: CanCM_SUD_API_030 */
      /* set result to E_OK */
      result = (Std_ReturnType)E_OK;

      /* store configuration data to local variable */
      /* polyspace-begin MISRA-C3:D4.14 [Not a defect:Low] "ConfigPtr is already checked whether it is NULL_PTR before being used" */
      selectedConfig = *ConfigPtr;
      /* polyspace-end MISRA-C3:D4.14 [Not a defect:Low] "ConfigPtr is already checked whether it is NULL_PTR before being used" */
    }
    /* @Trace: CanCM_SUD_API_033 */
    /* polyspace-begin RTE:UNR [Not a defect:Low] "If condition is not always true or false, the secion is reachable in another configuration. CanCM is a lib module" */
    if(E_OK == (Std_ReturnType)result)
    #endif
    {
      /* @Trace: CanCM_SUD_API_034 */
      #if(STD_ON == CANCM_VARIANT_POSTBUILD_SUPPORT)
      /* the status of CanCMDemStatusSupport parameter */
      CanCM_DemStatus = selectedConfig.DemSupport;

      /* the status of DisableDMOnAbnormalVoltage parameter */
      CanCM_DisableDMOnAbnormalVoltage = selectedConfig.DMAbnormal;
      /* the status of CanCMWakeUpSupport parameter */
      CanCM_WakeupSupport = selectedConfig.WKSupport;
      /* the status of CanCMHysteresisSupport parameter */
      CanCM_HysteresisSupport = selectedConfig.HysSupport;
      /* the value of CanCMFilteringConstant parameter */
      CanCM_FiltConst = selectedConfig.FilteringConst;
      /* the number of CanCM channels */
      CanCM_NumOfChannels = selectedConfig.NumOfChannels;

      /* the number of ADC groups */
      CanCM_NumOfAdcGrp = selectedConfig.NumOfAdcGroups;
      /*The largest channelId mapping CanCMChannelConfig */
      CanCM_LastChannelID = selectedConfig.LastChannelID;
      /* ADC groups */
	  
	  #if(CANCM_BATMON_CONFIG_EXIST == STD_ON)
      CanCM_AdcGroup = selectedConfig.PtrAdcGroup;
	  #endif

      /* channel mapping */
      CanCM_ComMChannelMap = selectedConfig.PtrComMChannelMap;
      /* CanCMChannelConfig */
      CanCM_ChannelConfig = selectedConfig.PtrChannelConfig;
      #endif
      /* Loop all channels, are managed by CanCM */
      /* polyspace-begin MISRA-C3:D4.1 [Not a defect:Low] "The size of all arrays is pre-defined, equal CanCM_NumOfChannels, count is always less than CanCM_NumOfChannels */
      /* polyspace-begin RTE:OBAI [Not a defect:Low] "The size of array is pre-defined, The value of count is already checked before used" */
      /* polyspace-begin MISRA-C3:18.1 [Not a defect:Low] "The size of array is pre-defined, which equal CanCM_NumOfChannels. The value of count can not be greater or equal that number" */
      /* @Trace: CanCM_SUD_API_001 */  
      for (count = CANCM_ZERO; count < CanCM_NumOfChannels; count++)
      {
        /* @Trace: CanCM_SUD_API_002 */
        /* Initialize Network Activation Timer */
        CanCM_NTimerCounter[count] = CANCM_ZERO;
        /* Initialize Delay Voltage Error Timer */
        CanCM_ETimerCounter[count] = CANCM_ZERO;
        /* Initialize Reception DM Timer */
        CanCM_RTimerCounter[count] = CANCM_ZERO;
        /* Initialize Internal Status Variable */
        CanCM_FlagStatus[count].MaskByte = CANCM_ZERO;
        /* Initialize Current Voltage Mode */
        CanCM_VolMod[count] = CANCM_VOL_MODE_NORMAL;
        /* Initialize Current Network State */
        CanCM_CommStat[count] = CANCM_COMM_STAT_INACTIVE;
        /* Report the error to DEM with event id and DEM_EVENT_STATUS_PASSED */
        /* polyspace-begin MISRA-C3:2.1 [Not a defect:Low] "if-condition is not always true, the value of the variable can be changed depending on generated code" */
        /* polyspace-begin DEFECT:DEAD_CODE [Not a defect:Low] "The value of the variable CanCM_DemStatus can be changed depending on configuration, CanCm is lib module" */
        /* polyspace-begin RTE:UNR [Not a defect:Low] "If-condition is not always false, CanCM is a lib module and the value of CanCM_DemStatus can be changed by configuration" */
        /* polyspace-begin MISRA-C3:14.3 [Not a defect:Low] "The value of CanCM_DemStatus can be according to configuration. CanCM is a lib module" */

        /* @Trace: CanCM_SUD_API_003 */
        #if(STD_ON == CANCM_DEM_STATUS)
          /* Report error to Dem */
          /* polyspace +3 RTE:IDP [Not a defect:Low] "The size of array is pre-defined, The value of count is already checked before used" */
          (void)Dem_SetEventStatus(
                    CanCM_ChannelConfig[count].EventId, 
                          (Dem_EventStatusType)DEM_EVENT_STATUS_PASSED);
        #endif
        /* polyspace-end MISRA-C3:2.1 [Not a defect:Low] "if-condition is not always true, the value of the variable can be changed depending on generated code" */
        /* polyspace-end DEFECT:DEAD_CODE [Not a defect:Low] "The value of the variable CanCM_DemStatus can be changed depending on configuration, CanCm is lib module" */
        /* polyspace-end RTE:UNR [Not a defect:Low] "If-condition is not always false, CanCM is a lib module and the value of CanCM_DemStatus can be changed by configuration" */
        /* polyspace-end MISRA-C3:14.3 [Not a defect:Low] "The value of CanCM_DemStatus can be according to configuration. CanCM is a lib module" */
      }
      /* polyspace-end MISRA-C3:D4.1 [Not a defect:Low] "The size of all arrays is pre-defined, equal CanCM_NumOfChannels, count is always less than CanCM_NumOfChannels */  
      /* polyspace-end RTE:OBAI [Not a defect:Low] "The size of array is pre-defined, The value of count is already checked before used" */

      /* polyspace -end MISRA-C3:18.1 [Not a defect:Low] "The size of array is pre-defined, which equal CanCM_NumOfChannels. The value of count can not be greater or equal that number" */
      /* Loop all ADC channels and set values to default one */
      /* polyspace-begin MISRA-C3:D4.1 [Not a defect:Low] "The size of array is pre-defined, equal CanCM_NumOfAdcGrp, count is always less than CanCM_NumOfAdcGrp */
      /* polyspace-begin RTE:IDP [Not a defect:Low] "The size of array is pre-defined, which equal CanCM_NumOfAdcGrp. The value of count can not be greater or equal that number" */
      /* polyspace-begin RTE:OBAI [Not a defect:Low] "The size of array is pre-defined, The value of count is already checked before used" */
	  #if(CANCM_BATMON_CONFIG_EXIST == STD_ON)
	  for (count = CANCM_ZERO; count < CanCM_NumOfAdcGrp; count++)
      {
          #if(STD_OFF == CANCM_VARIANT_POSTBUILD_SUPPORT)
    	  CanCM_AdcGroupVal[count] = CanCM_AdcDefaultVal[count];
          #else
    	  CanCM_AdcGroupVal[count] = selectedConfig.PtrAdcDefaultVal[count];
          #endif

      }
	  #endif
      /* polyspace-end RTE:IDP [Not a defect:Low] "The size of array is pre-defined, which equal CanCM_NumOfAdcGrp. The value of count can not be greater or equal that number" */
      /* polyspace-end MISRA-C3:D4.1 [Not a defect:Low] "The size of array is pre-defined, equal CanCM_NumOfAdcGrp, count is always less than CanCM_NumOfAdcGrp */
      /* polyspace-end RTE:OBAI [Not a defect:Low] "The size of array is pre-defined, The value of count is already checked before used" */
      /* Initialize Fail count value */
      CanCM_BatVolFailCnt = (uint16)CANCM_ZERO;
      /* Initialize Sample mode count value */
      CanCM_AdcSampleCnt = (uint16)CANCM_ZERO;
      /* Initialize Battery Voltage value */
      CanCM_BatVol = (uint16)CANCM_ZERO;
      /* Mark CanCM status INITIALISED */
      CanCM_CanCMStatus = (boolean)CANCM_INITIALISED;
    }
  }
  /* polyspace-end RTE:UNR [Not a defect:Low] "if-condition is not always false as CanCM is a lib module" */
}
#define CANCM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : CanCM_MainFunction                                  **
**                                                                            **
** Service ID           : 0x02U                                               **
**                                                                            **
** Description          : This function include main tasks of CanCM:          **
**                          + Check Wake-Up                                   **
**                          + Manage Channels state                           **
**                          + Monitor Battery Voltage                         ** 
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : CanCM_Init() should be invoked before               **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                            CanCM_CanCMStatus                               **
**                            CanCM_DevErrorDetect                            **
**                            CanCM_AdcSampleCnt                              **
**                            CanCM_BatVol                                    **
**                            CanCM_NumOfChannels                             **
**                            CanCM_WakeupSupport                             **
**                            CanCM_ChannelConfig[]                           **
**                            CanCM_FlagStatus[]                              **
**                        Function(s) invoked :                               **
**                            Det_ReportError                                 **
**                            CanCM_ReadBattery                               **
**                            CanCM_CheckRemoteWakeup                         **
**                            CanCM_CheckTimeOut                              **
**                            CanCM_CheckVoltage                              **
*******************************************************************************/
#define CANCM_START_SEC_CODE
#include "MemMap.h"
/* @Trace: 
 * SRS_CanCM_ES95400_30E_00009 SRS_CanCM_ES95400_30E_00011 
 * SRS_CanCM_ES95400_30E_00012 SRS_CanCM_ES95400_30E_00013 
 * SRS_CanCM_ES95400_30E_00018 SRS_CanCM_ES95400_30E_00019 
 * SRS_CanCM_ES95400_30E_00025 SRS_CanCM_ES95400_30E_00026 
 * SRS_CanCM_ES95400_30E_00027 SRS_CanCM_ES95400_30E_00028 
 * SRS_CanCM_ES95400_30E_00029 SRS_CanCM_ES95400_30E_00030
 * SRS_CanCM_ES95400_30E_00010 SRS_CanCM_ES95400_30E_00039
 */
/* @Trace: CanCM_SUD_API_006 */
FUNC(void, CANCM_CODE) CanCM_MainFunction(void)
{


  /* Declare loop variable */
  VAR(uint8, CANCM_VAR) count;
  /* Declare flag check Det error */ 	
  VAR(boolean, CANCM_VAR) hasError;


  

  /* If CanCM is not initialized */
  /* polyspace-begin RTE:UNR [Not a defect:Low] "The section is reachable in another configuration, CanCM is a lib module"*/
  if (CANCM_UNINITIALISED == CanCM_CanCMStatus)
  {
	   /* Mark Det error flag is TRUE */
	   hasError = (boolean)CANCM_TRUE;
			  
  }
  /* polyspace-end RTE:UNR [Not a defect:Low] "The section is reachable in another configuration, CanCM is a lib module"*/
  /* CanCM is initialzed */
  else
  {
	    /* Mark Det error flag is FALSE */
	    hasError = (boolean)CANCM_FALSE;
  }

  
  /* There is no DET error */
  /* polyspace-begin MISRA2012:14.3 [Not a defect:Low] "The value of the variable hasError depended on CanCM_DevErrorDetect which can be changed based on configuration" */
  /* polyspace-begin DEFECT:USELESS_IF [Not a defect:Low] "The value of the variable hasError depended on CanCM_DevErrorDetect which can be changed based on configuration" */
  if(hasError == FALSE)
  {
    /* If sample mode is multiple of CANCM_ADC_SAMPLE_MOD */
    if (CANCM_ZERO == (CanCM_AdcSampleCnt % CANCM_ADC_SAMPLE_MOD))
    {

      /* Read battery voltage */
      CanCM_ReadBattery(&CanCM_BatVol);

    }
     /* Else, sample mode is NOT multiple of CANCM_ADC_SAMPLE_MOD */
    else
    {
   	  /* Nothing to do */
    }
    /* Increase sample mode 1 unit */
    CanCM_AdcSampleCnt++;
    
    /* Loop all channels, are managed by CanCM */
    /* polyspace-begin RTE:OBAI [Not a defect:Low] "The size of array is pre-defined, which equal CanCM_NumOfChannels. The value of count can not be greater than this number" */
    for (count = CANCM_ZERO; count < CanCM_NumOfChannels; count++)
    { 
      /* wakeup source is supported */
      /* polyspace-begin MISRA-C3:2.1 [Not a defect:Low] "if-condition is not always true, the value of the variable can be changed depending on generated code" */
      /* polyspace-begin DEFECT:DEAD_CODE [Not a defect:Low] "The value of the variable CanCM_WakeupSupport can be changed depending on configuration, CanCm is lib module" */
      /* polyspace-begin RTE:UNR [Not a defect:Low] "If-condition is not always true or false, CanCM is a lib module and the value of CanCM_WakeupSupport can be changed by configuratio" */
      /* polyspace +1 MISRA2012:14.3 [Not a defect:Low] "It's changed in GEN code" */
      #if(STD_ON == CANCM_WAKEUP_SUPPORT)
      SchM_Enter_CanCM_MAIN_PROTECTION();
      /* If wake-up source is valid & event is enabled */
      /* polyspace +4 MISRA-C3:18.1 [Not a defect:Low] "The size of array is pre-defined, The value of count is already checked before used" */
      /* polyspace +3 RTE:IDP [Not a defect:Low] "The size of array is pre-defined, which equal CanCM_NumOfChannels. The value of count is checked before used" */
      /* polyspace +2 MISRA-C3:D4.1 [Not a defect:Low] "The size of array is pre-defined, the value of count  is checked before used" */
      if ((CANCM_INVALID != CanCM_ChannelConfig[count].WakSrc) &&
            (CANCM_ONE == CanCM_FlagStatus[count].BitByteRecord.WakChkEnabled))
      {
        SchM_Exit_CanCM_MAIN_PROTECTION();
        /* @Trace: CanCM_SUD_API_004 */
        /* Check Wakeup for each channel */
        CanCM_CheckRemoteWakeup(count);
      }
      /* wake-up source is invalid or event is disabled */
      else
      {
        SchM_Exit_CanCM_MAIN_PROTECTION();
      }
      #endif
      /* polyspace-end MISRA-C3:2.1 [Not a defect:Low] "if-condition is not always true, the value of the variable can be changed depending on generated code" */
      /* polyspace-end DEFECT:DEAD_CODE [Not a defect:Low] "The value of the variable CanCM_WakeupSupport can be changed depending on configuration, CanCm is lib module" */
      /* polyspace-end RTE:UNR [Not a defect:Low] "If-condition is not always true or false, CanCM is a lib module and the value of CanCM_WakeupSupport can be changed by configuratio" */
      /* Check timeout each channel */
      CanCM_CheckTimeOut(count);
      /* Check voltage each channel */
      CanCM_CheckVoltage(count);
    }
    /* polyspace-end RTE:OBAI [Not a defect:Low] "The size of array is pre-defined, which equal CanCM_NumOfChannels. The value of count can not be greater than this number" */
  }
  /* There is Det error */
  /* polyspace-begin RTE:UNR [Not a defect:Low] "The section is reachable in another configuration, CanCM is a lib module"*/
  else
  {
    /* Nothing to do */
  }	 
  /* polyspace-end RTE:UNR [Not a defect:Low] "The section is reachable in another configuration, CanCM is a lib module"*/
  /* polyspace-end MISRA2012:14.3 [Not a defect:Low] "The value of the variable hasError depended on CanCM_DevErrorDetect which can be changed based on configuration" */  
  /* polyspace-end DEFECT:USELESS_IF [Not a defect:Low] "The value of the variable hasError depended on CanCM_DevErrorDetect which is decided by configuration" */
}
#define CANCM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : CanCM_GetCurrentVoltageMode                         **
**                                                                            **
** Service ID           : 0x04U                                               **
**                                                                            **
** Description          : This function is used to                            **
**                             get current voltage mode of Channel            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : channelIdCanCm : Channel ID                         **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : ptrVolMode : voltage mode of channel                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : CanCM_Init() should be invoked before               **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                            CanCM_CanCMStatus                               **
**                            CanCM_DevErrorDetect                            **
**                            CanCM_NumOfChannels                             **
**                            CanCM_ChannelConfig[]                           **
**                            CanCM_CanCMStatus                               **
**                            CanCM_ETimerCounter                             **
**                            CanCM_VolMod                                    **
**                        Function(s) invoked :                               **
**                            Det_ReportError                                 **
*******************************************************************************/
#define CANCM_START_SEC_CODE
#include "MemMap.h"
/* @Trace: 
 * SRS_CanCM_ES95400_30E_00019 SRS_CanCM_ES95400_30E_00032 SRS_BSW_00337 SRS_CanCM_ES95400_30E_00002 
 */
/* @Trace: CanCM_SUD_API_015 */
FUNC(Std_ReturnType, CANCM_CODE) CanCM_GetCurrentVoltageMode(CanCM_ChannelType channelIdCanCm,P2VAR(CanCM_VolModType, AUTOMATIC, CANCM_APPL_DATA) ptrVolMode)
{


  VAR(uint8, CANCM_VAR) count;
  VAR(boolean, CANCM_VAR) hasDetError;
  VAR(Std_ReturnType, CANCM_VAR) returnVal;
  
  /* Initialize loop variable */
  count = CANCM_ZERO;

  /* Initialize return flag */
  returnVal = E_NOT_OK;

  /* If DET reporting is enabled */
  /* 
   * polyspace-begin MISRA2012:14.3 [Not a defect:Low] "It's changed in GEN code"
   * polyspace-begin MISRA2012:2.1 [Not a defect:Low] "It's changed in GEN code" 
   * polyspace-begin DEFECT:DEAD_CODE [Not a defect:Low] "The value of the variable CanCM_DevErrorDetect can be changed depending on configuration as CanCm is lib module"
   * polyspace-begin RTE:UNR [Not a defect:Low] "The section is reachable in another configuration, CanCM is a lib module"
   */
  #if(STD_ON == CANCM_DEV_ERROR_DETECT)
    /* If CanCM  is not initialized */
    if (CANCM_UNINITIALISED == CanCM_CanCMStatus) 
    {
      /* Marked Det error flag to TRUE */
      hasDetError = (boolean)CANCM_TRUE;
      /* Report error to DET */
      (void)Det_ReportError(CANCM_MODULE_ID,
            CANCM_INSTANCE_ID, CANCM_GETCURRENTVOLTAGEMODE_SID, CANCM_E_UNINIT);
    }

    /* Check NULL_PTR with return parameter */
    else if (NULL_PTR == ptrVolMode) 
    {
      /* Marked Det error flag to TRUE */
      hasDetError = (boolean)CANCM_TRUE;
      /* Report error to DET */
      (void)Det_ReportError(CANCM_MODULE_ID, CANCM_INSTANCE_ID, 
              CANCM_GETCURRENTVOLTAGEMODE_SID, CANCM_E_NULL_POINTER);
    }
    /* There is no errors */
    else
    {
       /* There is no DET Error in this case */
       hasDetError = (boolean)CANCM_FALSE;
    }
  /* Else, dectect error is disabled */
  #else
    /* There is no DET Error in this case */
    hasDetError = (boolean)CANCM_FALSE;
  #endif
  /* 
   * polyspace-end RTE:UNR [Not a defect:Low] "The section is reachable in another configuration, CanCM is a lib module"
   * polyspace-end MISRA2012:2.1 [Not a defect:Low] "It's changed in GEN code" 
   * polyspace-end MISRA2012:14.3 [Not a defect:Low] "It's changed in GEN code"
   * polyspace-end DEFECT:DEAD_CODE [Not a defect:Low] "The value of the variable CanCM_DevErrorDetect can be changed depending on configuration as CanCm is lib module"
   */
  
  /* There is no Det error */
  /* polyspace-begin RTE:UNR [Not a defect:Low] "If condition is not always true or false, the unreachable secion here is reachable in another configuration. CanCM is a lib module" */
  /* polyspace-begin MISRA2012:14.3 [Not a defect:Low] "The value of the variable hasError depended on CanCM_DevErrorDetect which can be changed based on configuration" */
  /* polyspace-begin DEFECT:USELESS_IF [Not a defect:Low] "The value of the variable hasError depended on CanCM_DevErrorDetect which can be changed based on configuration" */
  if(CANCM_FALSE == hasDetError)
  {
    /* Initialize voltage mode is undefined */
    /* polyspace +3 MISRA-C3:18.1 [Not a defect:Low] "Pointer can not be ouside its bound, the type of the these two are the same" */
    /* polyspace +2 MISRA-C3:D4.1 [Not a defect:Low] "the data type of pointer and enum are the same, pointer can not be out of its bound" */
    /* polyspace-begin MISRA2012:D4.14 [Not a defect:Low] "The pointer is checked NULL before" */
    *ptrVolMode = CANCM_VOL_MODE_UNDEFINED;
    /* Loop all channels, are handled by CanCM */
    /* polyspace-begin MISRA2012:14.2 [Not a defect:Low] "It's used to break loop" */
    /* polyspace-begin MISRA-C3:18.1 [Not a defect:Low] "The size of all  arrays is pre-defined, The value of count is already checked before used" */
    do
    {
      /* Find channel has Id, as channelIdCanCm */
      /* polyspace +2 RTE:IDP [Not a defect:Low] "The size of array is pre-defined, the value of count  is checked before used" */
      /* polyspace-begin MISRA-C3:D4.1 [Not a defect:Low] "the size of array is pre-defined, the value of count is checked before being used " */
      if (CanCM_ChannelConfig[count].ChannelId == channelIdCanCm)
      {
        /* If delay time is not expired -> voltage is still in critical */
        /* polyspace  +1 RTE:OBAI [Not a defect:Low] "The size of array CanCM_ETimerCounter is pre-defined, The value of count is already checked before used" */
        if (CanCM_ETimerCounter[count] != CANCM_ZERO)
        {
          /* Current is CRITICAL because waiting to change to NON-CRITICAL */
          /* polyspace +1 MISRA-C3:D4.1 [Not a defect:Low] "the data type of pointer and enum are the same, pointer can not be out of its bound" */
          *ptrVolMode = CANCM_VOL_MODE_CRITICAL;
        }
        /* delay time is expired */
        else
        {
          /* get voltage mode, has cached before*/
          *ptrVolMode = CanCM_VolMod[count];
        }
        /* Mark return value is OK */
        returnVal = E_OK;
        /* To stop loop */
        count = CanCM_NumOfChannels;
      }
      /* Not found */
      else
      {
        /* increase loop variable */
        count++;
      }
	  /* polyspace-end MISRA-C3:D4.1 [Not a defect:Low] "the size of array is pre-defined, the value of count is checked before being used " */
    /* Conditon to break loop */
    }while (count < CanCM_NumOfChannels);
    /* polyspace-end MISRA2012:14.2 [Not a defect:Low] "It's used to break loop" */
    /* polyspace-end MISRA2012:D4.14 [Not a defect:Low] "The pointer is checked NULL before" */
    /* polyspace-end MISRA-C3:18.1 [Not a defect:Low] "The size of all  arrays is pre-defined, The value of count is already checked before used" */
  }
  /* polyspace-end RTE:UNR [Not a defect:Low] "If condition is not always true or false, the unreachable secion here is reachable in another configuration. CanCM is a lib module" */
  /* polyspace-end MISRA2012:14.3 [Not a defect:Low] "The value of the variable hasError depended on CanCM_DevErrorDetect which can be changed based on configuration" */
  /* polyspace-end DEFECT:USELESS_IF [Not a defect:Low] "The value of the variable hasError depended on CanCM_DevErrorDetect which is decided by configuration" */
  /* return out value OK or not */
  return returnVal;
}
#define CANCM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : CanCM_GetCurrentNetworkState                        **
**                                                                            **
** Service ID           : 0x05U                                               **
**                                                                            **
** Description          : This function is used to                            **
**                              get current network state of Channel          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : channelIdCanCm : Channel ID                         **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : ptrCommStat : network state of Channel              **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : CanCM_Init() should be invoked before               **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                            CanCM_CanCMStatus                               **
**                            CanCM_DevErrorDetect                            **
**                            CanCM_NumOfChannels                             **
**                            CanCM_ChannelConfig[]                           **
**                            CanCM_CommStat[]                                **
**                        Function(s) invoked :                               **
**                            Det_ReportError                                 **
*******************************************************************************/
#define CANCM_START_SEC_CODE
#include "MemMap.h"
/* @Trace: 
 * SRS_CanCM_ES95400_30E_00019 SRS_CanCM_ES95400_30E_00021 
 * SRS_CanCM_ES95400_30E_00022 SRS_CanCM_ES95400_30E_00023 
 * SRS_CanCM_ES95400_30E_00024 SRS_CanCM_ES95400_30E_00031
 * SRS_CanCM_ES95400_30E_00002
 * SRS_BSW_00337
 */
FUNC(Std_ReturnType, CANCM_CODE) CanCM_GetCurrentNetworkState(
  NetworkHandleType channelIdCanCm,
  P2VAR(CanCM_CommStatType, AUTOMATIC, CANCM_APPL_DATA) ptrCommStat)
{
  /* @Trace: CanCM_SUD_API_013 */

  VAR(Std_ReturnType, CANCM_VAR) returnVal;
  VAR(boolean, CANCM_VAR) hasDetError;
  VAR(uint8, CANCM_VAR) channelIndex;
  
  /* Initialize return value */
  returnVal = E_NOT_OK;

  /* Initialize loop variable */
  channelIndex = CANCM_ZERO;

  /* If DET reporting is enabled */
  /* 
   * polyspace-begin MISRA2012:14.3 [Not a defect:Low] "It's changed in GEN code" 
   * polyspace-begin MISRA2012:2.1 [Not a defect:Low] "It's changed in GEN code"
   * polyspace-begin DEFECT:DEAD_CODE [Not a defect:Low] "The value of the variable CanCM_DevErrorDetect can be changed depending on configuration as CanCm is lib module"
   */
  /* polyspace-begin DEFECT:USELESS_IF [Not a defect:Low] "The value of the variable hasError depended on CanCM_DevErrorDetect which is decided by configuration" */
  /* polyspace-begin RTE:UNR [Not a defect:Low] "If condition is not always true or false, the secion is reachable in another configuration. CanCM is a lib module" */
  #if(STD_ON == CANCM_DEV_ERROR_DETECT)
    /* If CanCM is not initialized */
    if (CANCM_UNINITIALISED == CanCM_CanCMStatus) 
    {
      /* Marked Det error flag to TRUE */
      hasDetError = (boolean)CANCM_TRUE;
      /* Report error to DET */
      (void)Det_ReportError(CANCM_MODULE_ID, CANCM_INSTANCE_ID, 
        CANCM_GETCURRENTNETWORKSTATE_SID, CANCM_E_UNINIT);
    }
    /* Check NULL with return parameter */
    else if (NULL_PTR == ptrCommStat) 
    {
      /* Marked Det error flag to TRUE */
      hasDetError = (boolean)CANCM_TRUE;
      /* Report error to DET */
      (void)Det_ReportError(CANCM_MODULE_ID, CANCM_INSTANCE_ID, 
        CANCM_GETCURRENTNETWORKSTATE_SID, CANCM_E_NULL_POINTER);
    }
    /* There is no error */
    else
    {
    	/* There is no DET Error in this case */
    	hasDetError = (boolean)CANCM_FALSE;
    }
  /* Else DET reporting is disabled */
  #else
	/* There is no DET Error in this case */
    hasDetError = (boolean)CANCM_FALSE;
  #endif
  /* 
   * polyspace-end MISRA2012:2.1 [Not a defect:Low] "It's changed in GEN code"
   * polyspace-end MISRA2012:14.3 [Not a defect:Low] "It's changed in GEN code" 
   * polyspace-end DEFECT:DEAD_CODE [Not a defect:Low] "The value of the variable CanCM_DevErrorDetect can be changed depending on configuration as CanCm is lib module"
   */
  /* polyspace-end RTE:UNR [Not a defect:Low] "If condition is not always true, the secion is reachable in another configuration. CanCM is a lib module" */
  /* There is no Det error */
  /* polyspace +1 MISRA2012:14.3 [Not a defect:Low] "It's changed in GEN code" */
  /* polyspace-begin RTE:UNR [Not a defect:Low] "The secion is reachable in another configuration. CanCM is a lib module" */
  if(CANCM_FALSE == hasDetError)
  {
    /* Initialize network state is undefined */
    /* polyspace +3 MISRA-C3:18.1 [Not a defect:Low] "pointer can not be ouside its bound, the type of ptrCommStat and CANCM_COMM_STAT_UNDEFINED are the same" */
    /* polyspace +2 MISRA-C3:D4.1 [Not a defect:Low] "the data type of pointer and enum are the same, pointer can not be out of its bound" */
    /* polyspace-begin MISRA2012:D4.14 [Not a defect:Low] "The pointer is checked NULL before" */
    *ptrCommStat = (CanCM_CommStatType)CANCM_COMM_STAT_UNDEFINED;
    /* Loop all channels, are handled by CanCM */
    /* polyspace-begin MISRA2012:14.2 [Not a defect:Low] "It's used to break loop" */
    /* polyspace-begin RTE:OBAI [Not a defect:Low] "The size of array is pre-defined, which equal CanCM_NumOfChannels. The value of count can not be greater or equal that number" */
    /* polyspace-begin MISRA-C3:18.1 [Not a defect:Low] "The size of all  arrays is pre-defined, The value of ChannelIndex is already checked before used" */
    do
    {
      /* Find channel has Id, is same to input */
      /* polyspace +2 RTE:IDP [Not a defect:Low] "The size of array is pre-defined, the value of channelIndex  is checked before used" */
      /* polyspace-begin MISRA-C3:D4.1 [Not a defect:Low] "The size of array is pre-defined, the value of channelIndex is checked before used" */
      if (CanCM_ChannelConfig[channelIndex].ChannelId == channelIdCanCm)
      {
        /* get channel state, has cached before */
        *ptrCommStat = CanCM_CommStat[channelIndex];
        /* marked return value E_OK */
        returnVal = E_OK;
        /* Stop loop */
        channelIndex = (uint8)CanCM_NumOfChannels;
      }
      /* polyspace-end MISRA-C3:D4.1 [Not a defect:Low] "The size of array is pre-defined, the value of channelIndex is checked before used" */
      /* Not found */
      else
      {
        /* increase loop variable */
    	  channelIndex++;
      }
    }
    /* Conditon to break loop */
    while(channelIndex < CanCM_NumOfChannels);
    /* polyspace-end MISRA-C3:18.1 [Not a defect:Low] "The size of all  arrays is pre-defined, The value of ChannelIndex is already checked before used" */
    /* polyspace-end RTE:OBAI [Not a defect:Low] "The size of array is pre-defined, which equal CanCM_NumOfChannels. The value of count can not be greater or equal that number" */
    /* polyspace-end MISRA2012:14.2 [Not a defect:Low] "It's used to break loop" */
    /* polyspace-end MISRA2012:D4.14 [Not a defect:Low] "The pointer is checked NULL before" */
  }
  /* polyspace-end RTE:UNR [Not a defect:Low] "The secion is reachable in another configuration. CanCM is a lib module" */
  /* polyspace-end DEFECT:USELESS_IF [Not a defect:Low] "The value of the variable hasError depended on CanCM_DevErrorDetect which is decided by configuration" */
  return returnVal;
}
#define CANCM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : CanCM_GetVoltageFailCount                           **
**                                                                            **
** Service ID           : 0x06U                                               **
**                                                                            **
** Description          : This function is used to get CRITICAL voltage times **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : ptrCount : Number of CRITICAL voltage times         **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                            CanCM_DevErrorDetect                            **
**                            CanCM_BatVolFailCnt                             **
**                        Function(s) invoked :                               **
**                            Det_ReportError                                 **
*******************************************************************************/
#define CANCM_START_SEC_CODE
#include "MemMap.h"
/* @Trace: 
 * SRS_CanCM_ES95400_30E_00019 SRS_CanCM_ES95400_30E_00033 SRS_BSW_00337 SRS_CanCM_ES95400_30E_00002
 */
/* @Trace: CanCM_SUD_API_014 */
FUNC(void, CANCM_CODE) CanCM_GetVoltageFailCount(
  P2VAR(uint16, AUTOMATIC, CANCM_APPL_DATA) ptrCount)
{

  /* Declare Det error flag */
  VAR(boolean, CANCM_VAR) hasDetError;



  /* If DET reporting is enabled */
  /* 
   * polyspace-begin MISRA2012:14.3 [Not a defect:Low] "It's changed in GEN code"
   * polyspace-begin MISRA2012:2.1 [Not a defect:Low] "It's changed in GEN code" 
   * polyspace-begin DEFECT:DEAD_CODE [Not a defect:Low] "The value of the variable CanCM_DevErrorDetect can be changed depending on configuration as CanCm is lib module"
   */
  /* polyspace-begin DEFECT:USELESS_IF [Not a defect:Low] "The value of the variable hasError depended on CanCM_DevErrorDetect which is decided by configuration" */
  /* polyspace-begin RTE:UNR [Not a defect:Low] "If-condition is not always false, CanCM is a lib module and the value of CanCM_DevErrorDetect can be changed by configuration" */
  #if(STD_ON == CANCM_DEV_ERROR_DETECT)
    /* Check whether Version Information is equal to NULL Pointer */
    if (NULL_PTR == ptrCount)
    {
      /* mark Det error flag as TRUE */
      hasDetError = (boolean)CANCM_TRUE;
      /* Report error to DET */
      (void)Det_ReportError(CANCM_MODULE_ID, CANCM_INSTANCE_ID, 
                 CANCM_GETVOLTAGEFAILCOUNT_SID, CANCM_E_NULL_POINTER);
    }
    /* Else, not NULL */
    else
    {
    	/* There is no DET Error in this case */
    	hasDetError = (boolean)CANCM_FALSE;
    }
  /* Else, DET reporting is disabled */
  #else
  	/* There is no DET Error in this case */
  	hasDetError = (boolean)CANCM_FALSE;
  #endif
  /* 
   * polyspace-end MISRA2012:2.1 [Not a defect:Low] "It's changed in GEN code" 
   * polyspace-end MISRA2012:14.3 [Not a defect:Low] "It's changed in GEN code"
   * polyspace-end DEFECT:DEAD_CODE [Not a defect:Low] "The value of the variable CanCM_DevErrorDetect can be changed depending on configuration as CanCm is lib module"
   */
  /* polyspace-end RTE:UNR [Not a defect:Low] "If-condition is not always false, CanCM is a lib module and the value of CanCM_DevErrorDetect can be changed by configuration" */
  /* There is DET error */
  /* polyspace-begin RTE:UNR [Not a defect:Low] "The if-condition is not always true or false as CanCM is a lib module, the unreachable section here is reachable in another configuration" */
  /* polyspace +1 MISRA2012:14.3 [Not a defect:Low] "It's changed in GEN code" */
  if(CANCM_FALSE == hasDetError) 
  {
    /* get value is cached to return */
    /* polyspace +3 MISRA-C3:18.1 [Not a defect:Low] "pointer can not be ouside its bound, the type of ptrCout and CanCM_BatVolFailCnt are uint16" */
    /* polyspace +2 MISRA-C3:D4.1 [Not a defect:Low] "The two pointters have the same data type" */
    /* polyspace +1 MISRA2012:D4.14 [Not a defect:Low] "The pointer is checked NULL before" */
    *ptrCount = (uint16)CanCM_BatVolFailCnt;
  }
  /* Else, there is no Det error */
  else
  {
    /* Nothing to do */
  }
  /* polyspace-end RTE:UNR [Not a defect:Low] "The if-condition is not always true or false as CanCM is a lib module, the unreachable section here is reachable in another configuration" */
  /* polyspace-end DEFECT:USELESS_IF [Not a defect:Low] "The value of the variable hasError depended on CanCM_DevErrorDetect which is decided by configuration" */
}
#define CANCM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : CanCM_ReadBattery                                   **
**                                                                            **
** Service ID           : Service id of function                              **
**                                                                            **
** Description          : This function count & return current BAT voltage    **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : pusAdcValue : current battery volatage              **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                            CanCM_NumOfAdcGrp                               **
**                            CanCM_CanCMAdcGroup[]                           **
**                            CanCM_DevErrorDetect                            **
**                        Function(s) invoked :                               **
**                            IoHwAb_AnaInDirReadDirect                       **
**                            CanCM_GetFilteredAdcValue                       **
**                            Det_ReportError                                 **
*******************************************************************************/
#define CANCM_START_SEC_CODE
#include "MemMap.h"
/* @Trace: 
 * SRS_CanCM_ES95400_30E_00014
 * SRS_CanCM_ES95400_30E_00019
 * SRS_CanCM_ES95400_30E_00039
 * SRS_CanCM_ES95400_30E_00001
 * SRS_CanCM_ES95400_30E_00004
 * SRS_BSW_00337
 * SRS_CanCM_ES95400_30E_00015
 */
static FUNC(void, CANCM_CODE) CanCM_ReadBattery(
  P2VAR(uint16, AUTOMATIC, CANCM_VAR) pusAdcValue)
{
	
  #if(CANCM_BATMON_CONFIG_EXIST == STD_ON)
  VAR(IoHwAb_ValueType, CANCM_VAR) ioHwAbAdcValue;
  VAR(IoHwAb_ValueType, CANCM_VAR) tempValue;
  VAR(boolean, CANCM_VAR) isNeedUpdate;
  VAR(uint8, CANCM_VAR) count;
  P2VAR(uint16, AUTOMATIC, CANCM_VAR) result;
  VAR(uint32, CANCM_VAR) tmpValue;

  
  /* Initialize ADC value is zero */
  ioHwAbAdcValue = CANCM_ZERO;
  /* Initialize flag need update is false */
  isNeedUpdate = CANCM_FALSE;

  /* Loop for all ADC groups to count voltage */
  for(count = CANCM_ZERO; count < CanCM_NumOfAdcGrp ;count++)
  {
    /* Initialize temp value each loop */
    tempValue = CANCM_ZERO;
    
    /* Reading value for ADC group is OK */
    /* polyspace-begin MISRA-C3:18.1 [Not a defect:Low] "The size of all  arrays is pre-defined, The value of count is already checked before used" */
    /* polyspace-begin RTE:IDP [Not a defect:Low] "the size of CanCM_AdcGroup is already defined, which equal CanCM_NumOfAdcGroup. the value of count can not be greater than this" */
    /* polyspace-begin MISRA-C3:D4.1 [Not a defect:Low] "The size of array is pre-defined, the value of count  is checked before used" */
    /* polyspace-begin RTE:OBAI [Not a defect:Low] "The size of array is pre-defined, which equal CanCM_NumOfAdcGrp. The value of count is already checked before used" */
    if (E_OK == (uint8)IoHwAb_AnaInDirReadDirect(
           (IoHwAb_IndexType)CanCM_AdcGroup[count],&tempValue,CANCM_ONE))
    {
      /* @Trace: CanCM_SUD_API_022 */
      /* Filter above value with value, is cached before */
      result = &CanCM_AdcGroupVal[count];
      /* If previous value greater than or equal current*/
      if (CanCM_AdcGroupVal[count] >= tempValue)
      {
        /* @Trace: CanCM_SUD_API_023 */
        /* Previous value subtract current value */
        tmpValue = ((uint32)CanCM_AdcGroupVal[count] - (uint32)tempValue);
        /* Filter value to configured number */
        *result = tempValue + 
                (uint16)((tmpValue * (uint32)CanCM_FiltConst) >> CANCM_EIGHT);
      }
      else
      {
        /* Current value subtract previous value */
        tmpValue = ((uint32)tempValue - (uint32)CanCM_AdcGroupVal[count]);
        /* Filter value to configured number */
        *result = tempValue - 
                (uint16)((tmpValue * (uint32)CanCM_FiltConst) >> CANCM_EIGHT);
      }
      /* when voltage is increased */
      if (ioHwAbAdcValue < CanCM_AdcGroupVal[count])
      {
        /* update ADC value */
        ioHwAbAdcValue = CanCM_AdcGroupVal[count];
      }
      /* voltage is not increased */
      else
      {
        /* Nothing to do */
      }
      /* Mark flag is updated */
      isNeedUpdate = CANCM_TRUE;
    }
    /* polyspace-end RTE:IDP [Not a defect:Low] "the size of CanCM_AdcGroup is already defined, which equal CanCM_NumOfAdcGroup. the value of count can not be greater than this" */
    /* polyspace-end MISRA-C3:D4.1 [Not a defect:Low] "The size of array is pre-defined, the value of count  is checked before used" */
    /* polyspace-end RTE:OBAI [Not a defect:Low] "The size of array is pre-defined, which equal CanCM_NumOfAdcGrp. The value of count is already checked before used" */
    /* polyspace-end MISRA-C3:18.1 [Not a defect:Low] "The size of all  arrays is pre-defined, The value of count is already checked before used" */
    
    /* Reading value for ADC group is not OK */
    /* polyspace-begin RTE:UNR [Not a defect:Low] "The section is reachable in another configuration, CanCM is a lib module"*/
    else 
    {
      /* Detecting errors is enable */
      /*
       * polyspace-begin MISRA2012:14.3 [Not a defect:Low] "It's changed in GEN code"
       * polyspace-begin MISRA2012:2.1 [Not a defect:Low] "It's changed in GEN code"
       * polyspace-begin DEFECT:DEAD_CODE [Not a defect:Low] "The value of the variable CanCM_DevErrorDetect can be changed depending on configuration as CanCm is lib module"
       * polyspace-begin DEFECT:USELESS_IF [Not a defect:Low] "If-condition is not always true, the value of the variable can be changed depending on generated code"
       * polyspace-begin RTE:UNR [Not a defect:Low] "if-condition is not always false as CanCM is a lib module, the value of CanCM_DevErrorDetect is decided by generated code"
       */
      #if(STD_ON == CANCM_DEV_ERROR_DETECT)
        /* Report error to DET */
        (void)Det_ReportError(CANCM_MODULE_ID,
            CANCM_INSTANCE_ID, CANCM_MAINFUNCTION_SID, CANCM_E_READBATTERYFAIL);
      #endif
      /*
       * polyspace-end MISRA2012:2.1 [Not a defect:Low] "It's changed in GEN code"
       * polyspace-end MISRA2012:14.3 [Not a defect:Low] "It's changed in GEN code"
       * polyspace-end DEFECT:DEAD_CODE [Not a defect:Low] "The value of the variable CanCM_DevErrorDetect can be changed depending on configuration as CanCm is lib module"
       * polyspace-end DEFECT:USELESS_IF [Not a defect:Low] "If-condition is not always true, the value of the variable can be changed depending on generated code"
       * polyspace-end RTE:UNR [Not a defect:Low] "if-condition is not always false as CanCM is a lib module, the value of CanCM_DevErrorDetect is decided by generated code"
      */
    }
    /* polyspace-end RTE:UNR [Not a defect:Low] "The section is reachable in another configuration, CanCM is a lib module"*/
  }
  /* out loop, if flag updating is TRUE */
  if (CANCM_TRUE == isNeedUpdate)
  {
    /* update ADC value */
    *pusAdcValue = ioHwAbAdcValue;

  }
  /* no need to update */
  /* polyspace-begin RTE:UNR [Not a defect:Low] "The section is reachable in another configuration, CanCM is a lib module"*/
  else
  {
    /* Nothing to do */
  }
  /* polyspace-end RTE:UNR [Not a defect:Low] "The section is reachable in another configuration, CanCM is a lib module"*/
  #endif
}
#define CANCM_STOP_SEC_CODE
#include "MemMap.h"


/*******************************************************************************
** Function Name        : CanCM_CheckRemoteWakeup                             **
**                                                                            **
** Service ID           : Service id of function                              **
**                                                                            **
** Description          : This function get status wake-up event for channels **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : channelIdCanCm : chanel ID                          **
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
**                            CanCM_ChannelConfig[]                           **
**                            CanCM_FlagStatus[]                              **
**                        Function(s) invoked :                               **
**                            IoHwAb_DigDirReadDirect                         **
**                            EcuM_CheckWakeup                                **
*******************************************************************************/
#if(STD_ON == CANCM_WAKEUP_SUPPORT)
#define CANCM_START_SEC_CODE
#include "MemMap.h"
/* @Trace: 
 * SRS_CanCM_ES95400_30E_00016
 */
static FUNC(void, CANCM_CODE) CanCM_CheckRemoteWakeup(
  CanCM_ChannelType channelIdCanCm)
{
  /* Declare variable to check wake-up pin */
  VAR(IoHwAb_LevelType, CANCM_VAR) value;
  
  /* Initialize for this variable */
  value = CANCM_ZERO;
  
  /* @Trace: CanCM_SUD_API_027 */
  /* Check in IoHwAb, Is wake-up pin of input channel supported? */
  (void)IoHwAb_DigDirReadDirect(
    (IoHwAb_IndexType)CanCM_ChannelConfig[channelIdCanCm].WakPin, &value);

  /* Wake-up pin is supported */
  if (CANCM_ZERO == (uint8)value)
  {
    SchM_Enter_CanCM_MAIN_PROTECTION();
    /* Enable wake-up event for channel id */
    CanCM_FlagStatus[channelIdCanCm].BitByteRecord.WakEvt = CANCM_ONE;
    SchM_Exit_CanCM_MAIN_PROTECTION();

    /* @Trace: CanCM_SUD_API_028 */
    /* Notify to EcuM which source needs to be enabled wake-up */
    (void)EcuM_CheckWakeup(CanCM_ChannelConfig[channelIdCanCm].WakSrc);
  }
  /* Else, not supported */
  else
  {
    /* Nothing to do */
  }
}
#define CANCM_STOP_SEC_CODE
#include "MemMap.h"
#endif
/*******************************************************************************
** Function Name        : CanCM_CheckWakeup                                   **
**                                                                            **
** Service ID           : 0x08U                                               **
**                                                                            **
** Description          : This function check wake-up, is public outside      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : source : wake-up source                             **
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
**                            CanCM_WakeupSupport                             **
**                            CanCM_NumOfChannels                             **
**                            CanCM_ChannelConfig[]                           **
**                            CanCM_FlagStatus[]                              **
**                        Function(s) invoked :                               **
**                            IoHwAb_DigDirReadDirect                         **
**                            EcuM_SetWakeupEvent                             **
**                            EcuM_ClearWakeupEvent                           **
*******************************************************************************/
#define CANCM_START_SEC_CODE
#include "MemMap.h"
/* @Trace: CanCM_SUD_DATATYPE_001 */
/* @Trace: 
 * SRS_CanCM_ES95400_30E_00034 SRS_CanCM_ES95400_30E_00016 SRS_CanCM_ES95400_30E_00002
 */
/* @Trace: CanCM_SUD_API_024 */
FUNC(void, CANCM_CODE) CanCM_CheckWakeup(EcuM_WakeupSourceType source)
{

  #if(STD_ON == CANCM_WAKEUP_SUPPORT)
  /* Declare variable to loop all channels */
  VAR(uint8, CANCM_VAR) count;
  /* Declare variable to check wake-up pin */
  VAR(IoHwAb_LevelType, CANCM_VAR) value;
  #endif
  /* Initialize value for this */
 // value = CANCM_ZERO;
 // count = 0;
  
  /* If Wake-up feature is supported */
  /* polyspace-begin DEFECT:DEAD_CODE [Not a defect:Low] "The value of the variable CanCM_WakeupSupport can be changed depending on configuration, CanCm is lib module" */
  /* polyspace-begin MISRA-C3:2.1 [Not a defect:Low] "if-condition is not always true, the value of the variable can be changed depending on generated code" */
  /* polyspace-begin RTE:UNR [Not a defect:Low] "the section is reachable in another configuration, value of CanCM_WakeupSupport is decided by generated code. CanCM is a lib module" */
  /* polyspace +1 MISRA2012:14.3 [Not a defect:Low] "It's changed in GEN code" */
  #if(STD_ON == CANCM_WAKEUP_SUPPORT)
    /* Loop all channels, are managed by CanCM */
	/* polyspace-begin RTE:IDP [Not a defect:Low] "The size of array CanCM_ChannelConfig is pre-defined, which equal CanCM_NumOfChannels. The value of count is checked before used" */
    for (count = CANCM_ZERO; count < CanCM_NumOfChannels; count++)
    {
      /* @Trace: CanCM_SUD_API_025 */
      /* Which channel is same wake-up source with input & event is enable*/
      /* polyspace-begin MISRA-C3:18.1 [Not a defect:Low] "The size of all  arrays is pre-defined, The value of count is already checked before used" */
      /* polyspace-begin MISRA-C3:D4.1 [Not a defect:Low] "The size of array is pre-defined, the value of count  is checked before used" */
      /* polyspace-begin RTE:OBAI [Not a defect:Low] "The size of array is pre-defined, The value of count is already checked before used" */
      SchM_Enter_CanCM_MAIN_PROTECTION();
      if((CanCM_ChannelConfig[count].WakSrc == source) && 
        (CanCM_FlagStatus[count].BitByteRecord.WakEvt == CANCM_ONE))
      {
        /* Disable wake-up event for this channel */
        CanCM_FlagStatus[count].BitByteRecord.WakEvt = CANCM_ZERO;
        SchM_Exit_CanCM_MAIN_PROTECTION();
        /* Check in IoHwAb, Is wake-up pin of input channel supported? */
        /* @Trace: CanCM_SUD_API_026 */
        (void)IoHwAb_DigDirReadDirect(
          (IoHwAb_IndexType)CanCM_ChannelConfig[count].WakPin, &value);
        /* wake-up pin is supported */
        if (CANCM_ZERO == (uint8)value)
        {
          /* Notify EcuM set wake-up to source*/
          (void)EcuM_SetWakeupEvent(source);
          /* Notify EcuM clear wake-up to source*/
          (void)EcuM_ClearWakeupEvent(source);
        }
        /*else, not supported */
        else
        {
          /* Nothing to do */
        }
      }
      /* else, not found or event is disable */
      else
      {
        SchM_Exit_CanCM_MAIN_PROTECTION();
      }
      /* polyspace-end MISRA-C3:18.1 [Not a defect:Low] "The size of all  arrays is pre-defined, The value of count is already checked before used" */
      /* polyspace-end RTE:OBAI [Not a defect:Low] "The size of array is pre-defined, The value of count is already checked before used" */
      /* polyspace-end MISRA-C3:D4.1 [Not a defect:Low] "The size of array is pre-defined, the value of count  is checked before used" */
	  /* polyspace-end MISRA-C3:2.1 [Not a defect:Low] "if-condition is not always true, the value of the variable can be changed depending on generated code" */
    }
    /* polyspace-end RTE:IDP [Not a defect:Low] "The size of array is pre-defined, which equal CanCM_NumOfChannels. The value of count is checked before used" */
  #endif
  /* polyspace-end RTE:UNR [Not a defect:Low] "the section is reachable in another configuration, value of CanCM_WakeupSupport is decided by generated code. CanCM is a lib module" */
  /* polyspace-end DEFECT:DEAD_CODE [Not a defect:Low] "The value of the variable CanCM_WakeupSupport can be changed depending on configuration, CanCm is lib module" */
  //CANCM_UNUSED(count);
  //CANCM_UNUSED(value);
  CANCM_UNUSED(source);
}
#define CANCM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : CanCM_CheckTimeOut                                  **
**                                                                            **
** Service ID           : Service id of function                              **
**                                                                            **
** Description          : This function check timers, is called in main task  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : channelIdCanCm : chanel ID                          **
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
**                            CanCM_RTimerCounter[]                           **
**                            CanCM_CommStat[]                                **
**                            CanCM_FlagStatus[]                              **
**                            CanCM_ChannelConfig[]                           **
**                            CanCM_NTimerCounter[]                           **
**                            CanCM_ETimerCounter[]                           **
**                            CanCM_RTimerCounter[]                           **
**                            Function(s) invoked :                           **
**                            BswM_RequestMode                                **
**                            Dem_SetEventStatus                              **
**                            CanIf_SetBatteryVoltageMode                     **
*******************************************************************************/
#define CANCM_START_SEC_CODE
#include "MemMap.h"
/* @Trace: 
 * SRS_CanCM_ES95400_30E_00030 SRS_CanCM_ES95400_30E_00011 SRS_CanCM_ES95400_30E_00012 SRS_CanCM_ES95400_30E_00013 SRS_BSW_00339
 * SRS_CanCM_ES95400_30E_00003
 */
static FUNC(void, CANCM_CODE) CanCM_CheckTimeOut(CanCM_ChannelType channelIdCanCm)
{
  /* Check if Reception DM Start timer is running */
  /* polyspace-begin RTE:IDP [Not a defect:Low] "The size of array is pre-defined, the value of channelIdCanCm is checked before used" */
  /* polyspace-begin MISRA-C3:D4.1 [Not a defect:Low] "The size of array is pre-defined, the value of channelIdCanCm  is checked before used" */
  /* polyspace-begin RTE:OBAI [Not a defect:Low] "The size of array is pre-defined, The value of channelIdCanCm is already checked before used" */
  /* polyspace-begin MISRA-C3:18.1 [Not a defect:Low] "The size of all  arrays is pre-defined, The value of ChannelIdCanCm is already checked before used" */
  /* @Trace: CanCM_SUD_API_007 */
  if (CANCM_ZERO != CanCM_RTimerCounter[channelIdCanCm])
  {
    /* Decrement the timer */
    CanCM_RTimerCounter[channelIdCanCm]--;
    /* Timer is expired, state is active, is not disabled DM (1) */
    SchM_Enter_CanCM_MAIN_PROTECTION();
    if ((CANCM_ZERO == CanCM_RTimerCounter[channelIdCanCm]) &&
        (CANCM_COMM_STAT_ACTIVE == CanCM_CommStat[channelIdCanCm]) &&
        (CANCM_ONE != CanCM_FlagStatus[channelIdCanCm]
            .BitByteRecord.DtcDisabled))
    {
      SchM_Exit_CanCM_MAIN_PROTECTION();
      /*Notify BswM to enable Reception Deadline Monitoring */
      /* polyspace +4 MISRA-C3:D4.1 [Not a defect:Low] "The size of array is pre-defined, the value of channelIdCanCm is checked before used" */
      BswM_RequestMode(
        (BswM_UserType)CanCMBswmMRxInd(
              CanCM_ChannelConfig[channelIdCanCm].ChannelId),
        (BswM_ModeType)CANCM_COMM_STAT_RX_ENABLED_DM_ENABLED);
    }
    /* Esle, oposite (1) */
    else
    {
      SchM_Exit_CanCM_MAIN_PROTECTION();
    }
  }
  /* polyspace-end RTE:IDP [Not a defect:Low] "The size of array is pre-defined, the value of channelIdCanCm is checked before used" */
  /* polyspace-end MISRA-C3:D4.1 [Not a defect:Low] "The size of array is pre-defined, the value of channelIdCanCm  is checked before used" */
  /* polyspace-end RTE:OBAI [Not a defect:Low] "The size of array is pre-defined, The value of channelIdCanCm is already checked before used" */
  /* Else, Reception DM Start timer is stoped */
  else
  {
    /* Nothing to do */
  }

  /* Check if Network Activation Timer is running */
  /* @Trace: CanCM_SUD_API_008 */
  if (CANCM_ZERO != CanCM_NTimerCounter[channelIdCanCm])
  {
    /* Decrement Network Activation Timer */
    CanCM_NTimerCounter[channelIdCanCm]--;
    /* Check if Network Activation Timer is expired */
    if (CANCM_ZERO == CanCM_NTimerCounter[channelIdCanCm])
    {
      /* This channel has failed voltage */
      SchM_Enter_CanCM_MAIN_PROTECTION();
      if (CANCM_ZERO == CanCM_FlagStatus[channelIdCanCm].BitByteRecord.VolFailed)
      {
        SchM_Exit_CanCM_MAIN_PROTECTION();
        /* Notify BswM for Network Activation */
        /* polyspace +3 RTE:IDP [Not a defect:Low] "The size of array is pre-defined, The value of channelIdCanCm is already checked before used" */
        /* polyspace +3 MISRA-C3:D4.1 [Not a defect:Low] "The size of array is pre-defined, the value of channelIdCanCm is checked before used" */
        BswM_RequestMode((BswM_UserType)CanCMBswmMTxInd(CanCM_ChannelConfig[channelIdCanCm].ChannelId),(BswM_ModeType)CANCM_COMM_STAT_TX_ENABLED);
        /* Mark transmission flag is enabled */
        SchM_Enter_CanCM_MAIN_PROTECTION();
        CanCM_FlagStatus[channelIdCanCm].BitByteRecord.TxDisabled = CANCM_ZERO;
        SchM_Exit_CanCM_MAIN_PROTECTION();
      }
      /* voltage is not failed */
      else
      {
        SchM_Exit_CanCM_MAIN_PROTECTION();
      }

      /* Change current COMM state to ACTIVE */
      /* polyspace +1 MISRA-C3:D4.1 [Not a defect:Low] "The size of array is pre-defined, the value of channelIdCanCm is checked before used" */
      CanCM_CommStat[channelIdCanCm] = CANCM_COMM_STAT_ACTIVE;

    }
    /* Network Activation Timer is not expired */
    else
    {
      /* Nothing to do */
    }
  }
  /* Else, Network Activation Timer is stoped */
  else
  {
    /* Nothing to do */
  }

  /* Check if Voltage Error Delay timer is running */
  /* @Trace: CanCM_SUD_API_009 */
  if (CANCM_ZERO != CanCM_ETimerCounter[channelIdCanCm])
  {
    CanCM_Check_ETimerCounter(channelIdCanCm);
  }
  /* Voltage Error Delay timer is stoped */
  /* polyspace-end MISRA-C3:18.1 [Not a defect:Low] "The size of all  arrays is pre-defined, The value of ChannelIdCanCm is already checked before used" */
 
  else
  {
    /* Nothing to do */
  }
}
#define CANCM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : CanCM_Check_ETimerCounter                           **
**                                                                            **
** Service ID           : Service id of function                              **
**                                                                            **
** Description          : This function check Voltage Error Delay timer       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : channelIdCanCm : chanel ID                          **
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
**                            CanCM_ETimerCounter                             **
**                            CanCM_ChannelConfig                             **
**                            CanCM_FlagStatus                                **
**                        Function(s) invoked :                               **
**                            BswM_RequestMode                                **
**                            Dem_SetEventStatus                              **
**                            CanIf_SetBatteryVoltageMode                     **
*******************************************************************************/
#define CANCM_START_SEC_CODE
#include "MemMap.h"
static FUNC(void, CANCM_CODE) CanCM_Check_ETimerCounter(CanCM_ChannelType channelIdCanCm)
{
  /* polyspace-begin MISRA-C3:D4.1 [Not a defect:Low] "The size of array is pre-defined, the value of channelIdCanCm is checked before used" */
  /* Decrement the timer */
  CanCM_ETimerCounter[channelIdCanCm]--;
  /* Timer is expired */
  if ((CANCM_ZERO == CanCM_ETimerCounter[channelIdCanCm]))
  {
    /* Enable transmit ability of CanIf */
    /* polyspace +2 RTE:IDP [Not a defect:Low] "The size of array is pre-defined, The value of channelIdCanCm is already checked before used" */
    if ((uint8) E_OK == CanIf_SetBatteryVoltageMode(
            CanCM_ChannelConfig[channelIdCanCm].CanIfCtrlId,
            CANIF_SET_BATVOL_NORMAL))
    {
      /* Clear Voltage Failed Flag */
      SchM_Enter_CanCM_MAIN_PROTECTION();
      CanCM_FlagStatus[channelIdCanCm]
              .BitByteRecord.VolFailed = CANCM_ZERO;
      SchM_Exit_CanCM_MAIN_PROTECTION();
      /* Dem reporting is enabled */
      /* polyspace-begin MISRA-C3:2.1 [Not a defect:Low] "if-condition is not always true, the value of the variable can be changed depending on generated code" */
      /* polyspace-begin DEFECT:DEAD_CODE [Not a defect:Low] "The value of the variable CanCM_DemStatus can be changed depending on configuration, CanCm is lib module" */
      /* polyspace-begin RTE:UNR [Not a defect:Low] "the section is reachable in another configuration, value of CanCM_DemStatus is decided by generated code. CanCM is a lib module" */
      /* polyspace +1 MISRA2012:14.3 [Not a defect:Low] "It's changed in GEN code"*/
      #if(STD_ON == CANCM_DEM_STATUS)
        /* Report to DEM with event id and DEM_EVENT_STATUS_PASSED */
        (void)Dem_SetEventStatus(CanCM_ChannelConfig[channelIdCanCm].EventId,
                    (Dem_EventStatusType)DEM_EVENT_STATUS_PASSED);
      #endif
      /* polyspace-end MISRA-C3:2.1 [Not a defect:Low] "if-condition is not always true, the value of the variable can be changed depending on generated code" */
      /* polyspace-end DEFECT:DEAD_CODE [Not a defect:Low] "The value of the variable CanCM_DemStatus can be changed depending on configuration, CanCm is lib module" */    
      /* polyspace-end RTE:UNR [Not a defect:Low] "the section is reachable in another configuration, value of CanCM_DemStatus is decided by generated code. CanCM is a lib module" */
      /* NM & App message transmission should be enabled in 
        Network Active and Network Start only */
      if ((CANCM_COMM_STAT_ACTIVE == CanCM_CommStat[channelIdCanCm]) ||
          (CANCM_COMM_STAT_START == CanCM_CommStat[channelIdCanCm]))
      {
        SchM_Enter_CanCM_MAIN_PROTECTION();
        /*Nm flag is TRUE*/
        if (CANCM_ONE == 
            CanCM_FlagStatus[channelIdCanCm].BitByteRecord.NmDisabled)
        {
          SchM_Exit_CanCM_MAIN_PROTECTION();
          /* Notify BswM to invoke Nm_EnableCommunication() */
          BswM_RequestMode(
            (BswM_UserType)CanCMBswmMVolInd(
              CanCM_ChannelConfig[channelIdCanCm].ChannelId),
            (BswM_ModeType)CANCM_VOL_MODE_NORMAL);
          /* Mark Nm flag is ZERO */
          SchM_Enter_CanCM_MAIN_PROTECTION();
          CanCM_FlagStatus[channelIdCanCm]
                      .BitByteRecord.NmDisabled = CANCM_ZERO;
          SchM_Exit_CanCM_MAIN_PROTECTION();
        }
        /* Nm flag is FALSE */
        else
        {
          SchM_Exit_CanCM_MAIN_PROTECTION();
        }
        /* Check if Network Activation Timer is running */
        if ((CANCM_ZERO == CanCM_NTimerCounter[channelIdCanCm]))
        {
          /* Notify BswM to enable CAN transmission */
          BswM_RequestMode(
            (BswM_UserType)CanCMBswmMTxInd(
                  CanCM_ChannelConfig[channelIdCanCm].ChannelId),
            (BswM_ModeType)CANCM_COMM_STAT_TX_ENABLED);
          /* Mark transmission flag is ZERO */
          SchM_Enter_CanCM_MAIN_PROTECTION();
          CanCM_FlagStatus[channelIdCanCm]
                      .BitByteRecord.TxDisabled = CANCM_ZERO;
          SchM_Exit_CanCM_MAIN_PROTECTION();
        }
        /* Else, Network Activation Timer is stoped */
        else
        {
          /* Nothing to do */
        }
      }
    }
    /* Enable transmit ability of CanIf, but it's not OK */
    /* polyspace-begin RTE:UNR [Not a defect:Low] "Tthe secion is reachable in another configuration. CanCM is a lib module" */
    else
    {
      /* Nothing to do */
    }
    /* polyspace-end RTE:UNR [Not a defect:Low] "The secion is reachable in another configuration. CanCM is a lib module" */
  }
  /* Timer is not expired or voltage mode is not CRITICAL */
  else
  {
    /* Nothing to do */
  }
  /* polyspace-end MISRA-C3:D4.1 [Not a defect:Low] "The size of array is pre-defined, the value of channelIdCanCm is checked before used" */
}
#define CANCM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : CanCM_CheckVoltage                                  **
**                                                                            **
** Service ID           : Service id of function                              **
**                                                                            **
** Description          : This function check voltage, is called in main task **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : channelIdCanCm : channel ID                         **
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
**                            CanCM_ChannelConfig[]                           **
**                            CanCM_VolMod[]                                  **
**                            CanCM_FlagStatus[]                              **
**                            CanCM_RTimerCounter[]                           **
**                            CanCM_CommStat[]                                **
**                            CanCM_ETimerCounter[]                           **
**                            CanCM_DisableDMOnAbnormalVoltage                **
**                            CanCM_HysteresisSupport                         **
**                            CanCM_DemStatus                                 **
**                        Function(s) invoked :                               **
**                            BswM_RequestMode                                **
**                            Dem_SetEventStatus                              **
**                            CanIf_SetBatteryVoltageMode                     **
*******************************************************************************/
#define CANCM_START_SEC_CODE
#include "MemMap.h"
/* @Trace: 
 * SRS_CanCM_ES95400_30E_00030 SRS_CanCM_ES95400_30E_00008 SRS_CanCM_ES95400_30E_00028 SRS_CanCM_ES95400_30E_00025 SRS_CanCM_ES95400_30E_00039 SRS_BSW_00339
 * SRS_CanCM_ES95400_30E_00003 SRS_CanCM_ES95400_30E_00005 */
static FUNC(void, CANCM_CODE) CanCM_CheckVoltage(
  CanCM_ChannelType channelIdCanCm)
{
  VAR(uint16, CANCM_VAR) hysteresis;
  /* If Hysteresis is supported get value from configure else it's 0 */
  /* polyspace-begin MISRA-C3:18.1 [Not a defect:Low] "The size of all  arrays is pre-defined, The value of ChannelIdCanCm is already checked before used" */
  /* polyspace-begin MISRA-C3:2.1 [Not a defect:Low] "if-condition is not always true, the value of the variable can be changed depending on generated code" */
  /* polyspace-begin MISRA-C3:14.3 [Not a defect:Low] "The value of the variable CanCM_HysteresisSupport can be changed depending on configuration, CanCm is lib module" */
  /* polyspace-begin DEFECT:DEAD_CODE [Not a defect:Low] "The value of the variable CanCM_HysteresisSupport can be changed depending on configuration, CanCm is lib module" */
  /* polyspace-begin RTE:UNR [Not a defect:Low] "the section is reachable in another configuration, value of CanCM_HysteresisSupport is decided by generated code. CanCM is a lib module" */
  /* @Trace: CanCM_SUD_API_037 */
  #if(STD_ON == CANCM_HYSTERESIS_SUPPORT)
	/* polyspace +2 RTE:IDP [Not a defect:Low] "channelIdCanCm is already checked before used" */
	/* polyspace +1 MISRA-C3:D4.1 [Not a defect:Low] "channelIdCanCm is already valid before being passed through CanCM_CheckVoltage" */
    hysteresis = CanCM_ChannelConfig[channelIdCanCm].Hysteresis;
  #else
    hysteresis = CANCM_ZERO;
  #endif
  /* polyspace-end MISRA-C3:2.1 [Not a defect:Low] "if-condition is not always true, the value of the variable can be changed depending on generated code" */
  /* polyspace-end MISRA-C3:14.3 [Not a defect:Low] "The value of the variable CanCM_HysteresisSupport can be changed depending on configuration, CanCm is lib module" */
  /* polyspace-end DEFECT:DEAD_CODE [Not a defect:Low] "The value of the variable CanCM_HysteresisSupport can be changed depending on configuration, CanCm is lib module" */
  /* polyspace-end RTE:UNR [Not a defect:Low] "the section is reachable in another configuration, value of CanCM_HysteresisSupport is decided by generated code. CanCM is a lib module" */
  
  /* If Abnormal Voltage mode is disable */
  /* polyspace +5 RTE:UNR [Not a defect:Low] "the section is reachable in another configuration, value of CanCM_DisableDMOnAbnormalVoltage is decided by generated code. CanCM is a lib module" */
  /* polyspace +3 MISRA-C3:2.1 [Not a defect:Low] "CanCM is a lib module, the value of CanCM_DisableDMOnAbnormalVoltage can be changed in generated code determined by different configurations" */
  /* polyspace +2 DEFECT:DEAD_CODE [Not a defect:Low] "The value of the variable CanCM_DisableDMOnAbnormalVoltage can be changed depending on configuration, CanCm is lib module" */
  /* polyspace +1 MISRA2012:14.3 [Not a defect:Low] "It's changed in GEN code" */
  #if(STD_ON == CANCM_DISABLE_DM_ON_ABNOMAL_VOLTAGE)
    /* Voltage check for turning off or on */
    /* polyspace-begin DEFECT:DEAD_CODE [Not a defect:Low] "The value of the variable CanCM_ChannelConfig.AbnormalUpper/AbnormalUpper can be changed depending on configuration, no impact" */
    /* polyspace +3 RTE:IDP [Not a defect:Low] "The value of channelIdCanCm is already checked before used" */
    /* polyspace +2 MISRA-C3:D4.1 [Not a defect:Low] "The size of array is pre-defined, the value of channelIdCanCm is checked before used" */
    /* @Trace: CanCM_SUD_API_121 */
    #if((CANCM_COMPARE_ABNOMAL_UPPER_AND_ABNORMAL_LOWER == STD_ON) && (CANCM_BATMON_CONFIG_EXIST == STD_ON))
    if (CanCM_ChannelConfig[channelIdCanCm].AbnormalUpper
    == CanCM_ChannelConfig[channelIdCanCm].AbnormalLower)
    {
      /* @Trace: CanCM_SUD_API_016 */
      /* #8515 */
      /* Do nothing */
    /* polyspace-end DEFECT:DEAD_CODE [Not a defect:Low] "The value of the variable CanCM_ChannelConfig.AbnormalUpper/AbnormalUpper can be changed depending on configuration, no impact" */
    /* Voltage is in Normal range*/
    /* polyspace +3 MISRA-C3:D4.1 [Not a defect:Low] "The size of array is pre-defined, the value of channelIdCanCm is checked before used" */
    }
    else 
    #endif

	#if(CANCM_BATMON_CONFIG_EXIST == STD_ON)
    if ((CanCM_BatVol < (CanCM_ChannelConfig[channelIdCanCm].AbnormalUpper - hysteresis))
             &&(CanCM_BatVol > (CanCM_ChannelConfig[channelIdCanCm].AbnormalLower+ hysteresis)))
    #endif
    {
      /* @Trace: CanCM_SUD_API_017 */
      /* Current battery voltage is in normal range */
      CanCM_VolMod[channelIdCanCm] = CANCM_VOL_MODE_NORMAL;
      SchM_Enter_CanCM_MAIN_PROTECTION();
      /* Check if recording DTC on signal timeout is disabled */
      if ((CANCM_ONE == CanCM_FlagStatus[channelIdCanCm]
                         .BitByteRecord.DtcDisabled) &&
          (CANCM_ZERO == CanCM_RTimerCounter[channelIdCanCm]) &&
          (CANCM_COMM_STAT_INACTIVE != CanCM_CommStat[channelIdCanCm]) &&
          (CANCM_COMM_STAT_SHUTDOWN != CanCM_CommStat[channelIdCanCm]))
      {
        SchM_Exit_CanCM_MAIN_PROTECTION();
        /* Notify BswM to enable Reception Deadline Monitoring */
        BswM_RequestMode(
          (BswM_UserType)CanCMBswmMRxInd(
              CanCM_ChannelConfig[channelIdCanCm].ChannelId),
          (BswM_ModeType)CANCM_COMM_STAT_RX_ENABLED_DM_ENABLED);
        /* Mark flag DM is enabled */
        SchM_Enter_CanCM_MAIN_PROTECTION();
        CanCM_FlagStatus[channelIdCanCm].BitByteRecord.DtcDisabled = CANCM_ZERO;
        SchM_Exit_CanCM_MAIN_PROTECTION();
      }
      /* Else, recording DTC on signal timeout is NOT disabled */
      else
      {
        SchM_Exit_CanCM_MAIN_PROTECTION();
      }
    }
    /* Voltage is not in Normal range */
	#if(CANCM_BATMON_CONFIG_EXIST == STD_ON)
    else
    {
      /* Voltage mode is not critical*/
      if (CANCM_VOL_MODE_CRITICAL != CanCM_VolMod[channelIdCanCm])
      {
        /* @Trace: CanCM_SUD_API_018 */
        /* Current battery voltage is not in normal range */
        CanCM_VolMod[channelIdCanCm] = CANCM_VOL_MODE_ABNORMAL;

      }
      /* Voltage mode is critical*/
      else
      {
        /* Nothing to do */
      }
      SchM_Enter_CanCM_MAIN_PROTECTION();
      /* Check if recording DTC on signal timeout is disabled */
      if (CANCM_ZERO == CanCM_FlagStatus[channelIdCanCm].BitByteRecord.DtcDisabled)
      {
        SchM_Exit_CanCM_MAIN_PROTECTION();
        /* If network is not START state */
        if (CANCM_COMM_STAT_START != CanCM_CommStat[channelIdCanCm])
        {
          /* Notify BswM to disable Reception Deadline Monitoring */
          BswM_RequestMode((BswM_UserType)CanCMBswmMRxInd(CanCM_ChannelConfig[channelIdCanCm].ChannelId),
            (BswM_ModeType)CANCM_COMM_STAT_RX_ENABLED_DM_DISABLED);
        }
        /* Else, network is START state */
        else
        {
          /* Nothing to do */
        }
        SchM_Enter_CanCM_MAIN_PROTECTION();
        /* Mark flag DM is disabled */
        CanCM_FlagStatus[channelIdCanCm].BitByteRecord.DtcDisabled = CANCM_ONE;
        SchM_Exit_CanCM_MAIN_PROTECTION();
      }
      /* Else, recording DTC on signal timeout is disabled */
      else
      {
        SchM_Exit_CanCM_MAIN_PROTECTION();
      }
    }
	#endif
  #endif
  /* Voltage check for turning off or on Com Tx on critical voltage */
  /* polyspace-begin RTE:UNR [Not a defect:Low] "The section is reachable in another configuration" */
  /* polyspace-begin MISRA-C3:2.1 [Not a defect:Low] "The value of CriticalUpper and CriticalLower can be changed in generated code" */
  /* polyspace-begin MISRA-C3:14.3 [Not a defect:Low] "The value of CriticalUpper and CriticalLower can be changed in generated code" */
  /* polyspace +4 RTE:IDP [Not a defect:Low] "The size of array is pre-defined, The value of channelIdCanCm is already checked before used" */
  /* polyspace +3 MISRA-C3:D4.1 [Not a defect:Low] "The size of array is pre-defined, the value of channelIdCanCm is checked before used" */
  /* polyspace-begin DEFECT:DEAD_CODE [Not a defect:Low] "The value of CriticalUpper and CriticalLower can be changed in generated code which is different from configurations" */
  /* polyspace +3 MISRA2012:14.3 [Not a defect:Low] "The value of the variable CanCM_HysteresisSupport can be changed depending on configuration, CanCm is lib module" */
  /* polyspace +2 MISRA-C3:2.1 [Not a defect:Low] "if-condition is not always true, the value of the variable can be changed depending on generated code" */
  /* @Trace: CanCM_SUD_API_120 */
  #if ((CANCM_COMPARE_CRITICAL_UPPER_AND_CRITICAL_LOWER == STD_ON) && (CANCM_BATMON_CONFIG_EXIST == STD_ON))
  if (CanCM_ChannelConfig[channelIdCanCm].CriticalUpper
    == CanCM_ChannelConfig[channelIdCanCm].CriticalLower)
  {
    /* #8515 */
    /* Nothing to do */
  /* Voltage is in critical range */
  /* @Trace: CanCM_SUD_API_019 */
  }
  else
  #endif

  #if(CANCM_BATMON_CONFIG_EXIST == STD_ON)
  if (
    (CanCM_BatVol > CanCM_ChannelConfig[channelIdCanCm].CriticalUpper) ||
    (CanCM_BatVol < CanCM_ChannelConfig[channelIdCanCm].CriticalLower))
  {
    CanCM_Check_Critical_Voltage(channelIdCanCm);
  }
  /* polyspace-end RTE:UNR [Not a defect:Low] "The section is reachable in another configuration" */
  /* polyspace-end MISRA-C3:2.1 [Not a defect:Low] "The value of CriticalUpper and CriticalLower can be changed in generated code" */
  /* polyspace-end MISRA-C3:14.3 [Not a defect:Low] "The value of CriticalUpper and CriticalLower can be changed in generated code" */
  /* polyspace-end DEFECT:DEAD_CODE [Not a defect:Low] "The value of CriticalUpper and CriticalLower can be changed in generated code which is different from configurations" */
  else
  {
    SchM_Enter_CanCM_MAIN_PROTECTION();
    /* current battery voltage is not in critical range */
    if ((CANCM_ONE == CanCM_FlagStatus[channelIdCanCm].BitByteRecord.VolFailed)
        &&(CANCM_ZERO == CanCM_ETimerCounter[channelIdCanCm]))
    {
      /* Check voltage is in critical range with hysteresis */
      if ((CanCM_BatVol < (CanCM_ChannelConfig[channelIdCanCm].CriticalUpper - hysteresis))
		   &&(CanCM_BatVol > (CanCM_ChannelConfig[channelIdCanCm].CriticalLower + hysteresis)))
      {
        /* @Trace: CanCM_SUD_API_021 */
        /* If Abnormal Volatge mode is disabled */
        /* 
         * polyspace-begin MISRA2012:14.3 [Not a defect:Low] "It's changed in GEN code" 
         * polyspace-begin MISRA2012:2.1 [Not a defect:Low] "It's changed in GEN code"
         */
        /* polyspace-begin DEFECT:DEAD_CODE [Not a defect:Low] "The value of the variable CanCM_DisableDMOnAbnormalVoltage can be changed depending on configuration, CanCm is lib module" */
        /* polyspace-begin RTE:UNR [Not a defect:Low] "the section is reachable in another configuration, value of CanCM_DisableDMOnAbnormalVoltage is decided by generated code. CanCM is a lib module" */
        #if(STD_OFF == CANCM_DISABLE_DM_ON_ABNOMAL_VOLTAGE)
          /* Current battery voltage is in normal range */
          CanCM_VolMod[channelIdCanCm] = CANCM_VOL_MODE_NORMAL;
        /* polyspace-end DEFECT:DEAD_CODE [Not a defect:Low] "The value of the variable CanCM_DisableDMOnAbnormalVoltage can be changed depending on configuration, CanCm is lib module" */
        /* 
        * polyspace-end MISRA2012:2.1 [Not a defect:Low] "It's changed in GEN code"
        * polyspace-end MISRA2012:14.3 [Not a defect:Low] "It's changed in GEN code" 
        */
        /* Else, Abnormal Volatge mode is enabled */
        #else
          /* #6168 */
          /* Current battery voltage is in abnormal range */
          CanCM_VolMod[channelIdCanCm] = CANCM_VOL_MODE_ABNORMAL;
        #endif
        
        /* polyspace-end RTE:UNR [Not a defect:Low] "the section is reachable in another configuration, value of CanCM_DisableDMOnAbnormalVoltage is decided by generated code. CanCM is a lib module" */
        /* Start Voltage Error Timer */
        CanCM_ETimerCounter[channelIdCanCm] = CanCM_ChannelConfig[channelIdCanCm].DelayTimeCritical;
      }
      /* Else, Voltage is not in critical range with hysteresis */
      else
      {
        /* Nothing to do*/
      }
    }
    /* current battery voltage is in critical range */
    else
    {
      /* Nothing to do */
    }
    SchM_Exit_CanCM_MAIN_PROTECTION();
  }
  #endif
  /* polyspace-end MISRA-C3:18.1 [Not a defect:Low] "The size of all  arrays is pre-defined, The value of ChannelIdCanCm is already checked before used" */
}
#define CANCM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : CanCM_Check_Critical_Voltage                        **
**                                                                            **
** Service ID           : Service id of function                              **
**                                                                            **
** Description          : This function check BatVoltage                      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : channelIdCanCm : chanel ID                          **
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
**                            CanCM_ETimerCounter                             **
**                            CanCM_ChannelConfig                             **
**                            CanCM_FlagStatus                                **
**                        Function(s) invoked :                               **
**                            BswM_RequestMode                                **
**                            Dem_SetEventStatus                              **
**                            CanIf_SetBatteryVoltageMode                     **
*******************************************************************************/
#define CANCM_START_SEC_CODE
#include "MemMap.h"
#if(CANCM_BATMON_CONFIG_EXIST == STD_ON)
static FUNC(void, CANCM_CODE) CanCM_Check_Critical_Voltage(CanCM_ChannelType channelIdCanCm)
{
  /* polyspace-begin RTE:UNR [Not a defect:Low] "The section is reachable in another configuration" */
  /* polyspace-begin MISRA-C3:2.1 [Not a defect:Low] "The value of CriticalUpper and CriticalLower can be changed in generated code" */
  /* polyspace-begin MISRA-C3:14.3 [Not a defect:Low] "The value of CriticalUpper and CriticalLower can be changed in generated code" */
  /* polyspace-begin DEFECT:DEAD_CODE [Not a defect:Low] "The value of CriticalUpper and CriticalLower can be changed in generated code which is different from configurations" */
  /* current battery voltage is in critical range */
  CanCM_VolMod[channelIdCanCm] = CANCM_VOL_MODE_CRITICAL;
  SchM_Enter_CanCM_MAIN_PROTECTION();
  /* Check if CAN transmission is disabled */
  if (CANCM_ZERO == CanCM_FlagStatus[channelIdCanCm].BitByteRecord.VolFailed)
  {
    SchM_Exit_CanCM_MAIN_PROTECTION();
    /* Increment battery voltage failure count */
    CanCM_BatVolFailCnt++;
    /*Notify BswM to disable CAN transmission */
    BswM_RequestMode(
      (BswM_UserType)CanCMBswmMTxInd(
            CanCM_ChannelConfig[channelIdCanCm].ChannelId),
      (BswM_ModeType)CANCM_COMM_STAT_TX_DISABLED);
    SchM_Enter_CanCM_MAIN_PROTECTION();
    /* Mark flag transmission is disabled */
    CanCM_FlagStatus[channelIdCanCm]
            .BitByteRecord.TxDisabled = CANCM_ONE;
      /* Set flag for battery voltage failure */
    CanCM_FlagStatus[channelIdCanCm]
              .BitByteRecord.VolFailed = CANCM_ONE;
    SchM_Exit_CanCM_MAIN_PROTECTION();
    /* Disable transmit ability of CanIf */
    if ((uint8)E_OK == CanIf_SetBatteryVoltageMode(CanCM_ChannelConfig[channelIdCanCm].CanIfCtrlId,CANIF_SET_BATVOL_CRITICAL))
    {
      /* DEM reporting is enable */
      /* polyspace-begin MISRA-C3:2.1 [Not a defect:Low] "If-condition is not always true, the value of the variable can be changed depending on generated code" */
      /* polyspace-begin DEFECT:DEAD_CODE [Not a defect:Low] "The value of the variable CanCM_DemStatus can be changed depending on configuration, CanCm is lib module" */
      /* polyspace-begin RTE:UNR [Not a defect:Low] "the section is reachable in another configuration, value of CanCM_DemStatus is decided by generated code. CanCM is a lib module" */
      /* polyspace +1 MISRA2012:14.3 [Not a defect:Low] "It's changed in GEN code" */
      #if(STD_ON == CANCM_DEM_STATUS)
        /* Report to DEM with event id and DEM_EVENT_STATUS_FAILED */
        /* @Trace: CanCM_SUD_API_020 */
        (void)Dem_SetEventStatus(CanCM_ChannelConfig[channelIdCanCm].EventId,
                    (Dem_EventStatusType)DEM_EVENT_STATUS_FAILED);
      #endif
      /* polyspace-end RTE:UNR [Not a defect:Low] "the section is reachable in another configuration, value of CanCM_DemStatus is decided by generated code. CanCM is a lib module" */
      /* polyspace-end MISRA-C3:2.1 [Not a defect:Low] "If-condition is not always true, the value of the variable can be changed depending on generated code" */
      /* polyspace-end DEFECT:DEAD_CODE [Not a defect:Low] "The value of the variable CanCM_DemStatus can be changed depending on configuration, CanCm is lib module" */

      /* Notify to BswM about voltage mode is critical */
      BswM_RequestMode((BswM_UserType)CanCMBswmMVolInd(CanCM_ChannelConfig[channelIdCanCm].ChannelId),(BswM_ModeType)CANCM_VOL_MODE_CRITICAL);
      /* Mark flag Nm is disabled */
      SchM_Enter_CanCM_MAIN_PROTECTION();
      CanCM_FlagStatus[channelIdCanCm].BitByteRecord.NmDisabled = CANCM_ONE;
      SchM_Exit_CanCM_MAIN_PROTECTION();
    }
    /* Disable transmit ability of CanIf but it's not OK */
    /* polyspace-begin RTE:UNR [Not a defect:Low] "The section is reachable in another configuration. CanCM is a lib module" */
    else
    {
      /* Nothing to do */
    }
    /* polyspace-end RTE:UNR [Not a defect:Low] "The section is reachable in another configuration. CanCM is a lib module" */
  }
  else
  {
    SchM_Exit_CanCM_MAIN_PROTECTION();
  }
  /* Check if Voltage Error Timer is running */
  if (CANCM_ZERO != CanCM_ETimerCounter[channelIdCanCm])
  {
    /* Stop Voltage Error Timer because
    voltage entered critical range again */
    CanCM_ETimerCounter[channelIdCanCm] = CANCM_ZERO;
  }
  /* Else, Voltage Error Timer is running */
  else
  {
    /* Nothing to do */
  }
  /* polyspace-end RTE:UNR [Not a defect:Low] "The section is reachable in another configuration" */
  /* polyspace-end MISRA-C3:2.1 [Not a defect:Low] "The value of CriticalUpper and CriticalLower can be changed in generated code" */
  /* polyspace-end MISRA-C3:14.3 [Not a defect:Low] "The value of CriticalUpper and CriticalLower can be changed in generated code" */
  /* polyspace-end DEFECT:DEAD_CODE [Not a defect:Low] "The value of CriticalUpper and CriticalLower can be changed in generated code which is different from configurations" */
}
#endif
#define CANCM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name        : CanCM_GetVersionInfo                                **
**                                                                            **
** Service ID           : 0x07U                                               **
**                                                                            **
** Description          : This function get version of module                 **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : ptrVersionInfo : pointer of version info            **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                            None                                            **
**                        Function(s) invoked :                               **
**                            None                                            **
*******************************************************************************/
#if(STD_ON == CANCM_VERSION_INFO_API)
#define CANCM_START_SEC_CODE
#include "MemMap.h"
/* @Trace: CanCM_SUD_DATATYPE_003 */
/* @Trace: 
 * SRS_CanCM_ES95400_30E_00017 SRS_CanCM_ES95400_30E_00019  SRS_CanCM_ES95400_30E_00002
 * SRS_CanCM_ES95400_30E_00036 
 */
FUNC(void, CANCM_CODE)CanCM_GetVersionInfo(
  P2VAR(Std_VersionInfoType, AUTOMATIC, CANCM_APPL_DATA) ptrVersionInfo)
{
  /* @Trace: CanCM_SUD_API_005 */
  /* Declare Det error flag */
  VAR(boolean, CANCM_VAR) hasDetError;

  /* If this function is disable */
  /* 
   * polyspace-begin DEFECT:DEAD_CODE [Not a defect:Low] "CanCM is a lib module, the value of CanCM_VersionInfoApi can be changed in generated code determined by different configurations" 
   * polyspace-begin MISRA-C3:2.1 [Not a defect:Low] "CanCM is a lib module, the value of CanCM_VersionInfoApi can be changed in generated code determined by different configurations"
   * polyspace-begin MISRA-C3:14.3 [Not a defect:Low] "CanCM is a lib module, the value of CanCM_VersionInfoApi can be changed in generated code determined by different configurations"
   */
  /* polyspace-begin RTE:UNR [Not a defect:Low] "The if-condition is not always true or false as CanCM is a lib module, the value of CanCM_VersionInfoApi is decided by generated code" */
    /* Detect error is enabled */
    /* 
     * polyspace-begin MISRA2012:14.3 [Not a defect:Low] "It's changed in GEN code"
     * polyspace-begin MISRA2012:2.1 [Not a defect:Low] "It's changed in GEN code"
     * polyspace-begin DEFECT:DEAD_CODE [Not a defect:Low] "The value of the variable CanCM_DevErrorDetect can be changed depending on configuration as CanCm is lib module"
     */
 
     /* polyspace-begin DEFECT:USELESS_IF [Not a defect:Low] "The value of the variable hasError depended on CanCM_DevErrorDetect which is decided by configuration" */
     /* polyspace-begin RTE:UNR [Not a defect:Low] "The if-condition is not always true or false as CanCM is a lib module, the value of CanCM_DevErrorDetect is decided by generated code" */
    #if(STD_ON == CANCM_DEV_ERROR_DETECT)
      /* Check whether Version Information is equal to NULL Pointer */
      if (NULL_PTR == ptrVersionInfo)
      {
        /* mark flag Det error as TRUE */
        hasDetError = (boolean)CANCM_TRUE;
        /* report to Det */
        (void)Det_ReportError(CANCM_MODULE_ID, 
          CANCM_INSTANCE_ID, CANCM_GETVERSION_SID, CANCM_E_NULL_POINTER); 
      }
      /* Else, pointer is not NULL */
      else
      {
        /* There is no DET Error in this case */
        hasDetError = (boolean)CANCM_FALSE;
      }
    /* 
     * polyspace-end MISRA2012:14.3 [Not a defect:Low] "It's changed in GEN code"
     * polyspace-end MISRA2012:2.1 [Not a defect:Low] "It's changed in GEN code"
     * polyspace-end DEFECT:DEAD_CODE [Not a defect:Low] "The value of the variable CanCM_DevErrorDetect can be changed depending on configuration as CanCm is lib module"
     */
    /* Detect error is disabled */
    #else
      /* There is no DET Error in this case */
      hasDetError = (boolean)CANCM_FALSE;
    #endif
    /* polyspace-end RTE:UNR [Not a defect:Low] "The if-condition is not always true or false as CanCM is a lib module, the value of CanCM_DevErrorDetect is decided by generated code" */
    /* There is Det error */
    /* polyspace-begin RTE:UNR [Not a defect:Low] "hasDetError is decided by variable named CanCM_DevErrorDetect which can be changed in generated code" */
    /* polyspace +1 MISRA2012:14.3 [Not a defect:Low] "It's changed in GEN code" */
    if(CANCM_FALSE == hasDetError)
    {
      /* Copy the vendor Id */
      /* polyspace +2 MISRA-C3:D4.1 [Not a defect:Low] "venderID is an uint16 variable, 0x4Cu is not out if bound" */
      /* polyspace-begin MISRA2012:D4.14 [Not a defect:Low] "The pointer is checked NULL before"*/
      ptrVersionInfo->vendorID = CANCM_VENDOR_ID;
      /* Copy the module Id */
      ptrVersionInfo->moduleID = CANCM_MODULE_ID;
      /* Copy Software Major Version */
      ptrVersionInfo->sw_major_version = (uint8)CANCM_CFG_SW_MAJOR_VERSION;
      /* Copy Software Minor Version */
      ptrVersionInfo->sw_minor_version = (uint8)CANCM_CFG_SW_MINOR_VERSION;
      /* polyspace-end MISRA2012:D4.14 [Not a defect:Low] "The pointer is checked NULL before" */
    }
    /* Else, no Det error */

    else
    {
      /* Nothing to do */
    }
    /* polyspace-end DEFECT:USELESS_IF [Not a defect:Low] "The value of the variable hasError depended on CanCM_DevErrorDetect which is decided by configuration" */
    /* polyspace-end RTE:UNR [Not a defect:Low] "hasDetError is decided by variable named CanCM_DevErrorDetect which can be changed in generated code" */

  /* 
   * polyspace-end DEFECT:DEAD_CODE [Not a defect:Low] "CanCM is a lib module, the value of CanCM_VersionInfoApi can be changed in generated code determined by different configurations" 
   * polyspace-end MISRA-C3:2.1 [Not a defect:Low] "CanCM is a lib module, the value of CanCM_VersionInfoApi can be changed in generated code determined by different configurations"
   * polyspace-end MISRA-C3:14.3 [Not a defect:Low] "CanCM is a lib module, the value of CanCM_VersionInfoApi can be changed in generated code determined by different configurations"
   */
  /* polyspace-end RTE:UNR [Not a defect:Low] "The if-condition is not always true or false as CanCM is a lib module, the value of CanCM_VersionInfoApi is decided by generated code" */
  //CANCM_UNUSED(hasDetError);
  CANCM_UNUSED(ptrVersionInfo);
}

#define CANCM_STOP_SEC_CODE
#include "MemMap.h"
#endif 
/*******************************************************************************
**                          End of File                                       **
*******************************************************************************/
