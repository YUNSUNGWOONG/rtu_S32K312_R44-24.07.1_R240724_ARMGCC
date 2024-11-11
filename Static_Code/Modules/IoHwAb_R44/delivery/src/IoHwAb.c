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
**  SRC-MODULE: IoHwAb.c                                                      **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR IOHWAB                                                **
**                                                                            **
**  PURPOSE   : APIs implementation for IoHwAb module                         **
**              IoHwAb_Init                                                   **
**              IoHwAb_DeInit                                                 **
**              IoHwAb_GetVersionInfo                                         **
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
** 1.3.2     10-Aug-2022  KhaLN1            #CP44-731                         **
** 1.3.0.1   30-Jun-2022  KhaLN1            #CP44-365                         **
** 1.3.0     16-Mar-2022  PhucNHM           R44-Redmine #24709                **
** 1.1.0     15-Jul-2021  YangJin.Kim       R44-Redmine #18100                **
** 1.0.0     04-Dec-2020  YangJin.Kim       R40-Redmine #26992                **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "IoHwAb.h"
#include "IoHwAb_Config.h"

#if (IOHWAB_USE_DIG_DIR == STD_ON)
#include "IoHwAb_DigDir.h"
#endif /* (IOHWAB_USE_DIG_DIR == STD_ON) */
#if (IOHWAB_USE_IO_MAN == STD_ON)
#include "IoHwAb_IOManager.h"
#endif /* (IOHWAB_USE_IO_MAN == STD_ON) */

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
/*******************************************************************************
** Function Name        : IoHwAb_Init                                         **
**                                                                            **
** Service ID           : 0x01                                                **
**                                                                            **
** Description          : This function initializes all the IO Hardware       **
**                        Abstraction software.                               **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
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
**                        Function(s) invoked    : biostartup_Startup         **
*******************************************************************************/

/* @Trace: SRS_BSW_00101 */
/* @Trace: SWS_IoHwAb_00037 SWS_IoHwAb_00119 */
/* @Trace: SWS_IoHwAb_00044 */
/* @Trace: SWS_IoHwAb_00158 SWS_IoHwAb_00060 SWS_IoHwAb_00102 SWR_IOHWAB_201_001 SWR_IOHWAB_201_002 */
/* @Trace: SWS_IoHwAb_00157 */
/* @Trace: IoHwAb_SUD_API_001 */
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(void, IOHWAB_CODE) IoHwAb_Init(P2CONST(IoHwAb_ConfigType, 
  AUTOMATIC, 
  IOHWAB_APPL_CONST) ConfigPtr)
{
  /* @Trace: SWS_IoHwAb_00158 */
  do
  {
    if(ConfigPtr != NULL_PTR)
    {
      /* Do nothing */
    }
  } while(0);

  #if (IOHWAB_USE_DIG_DIR == STD_ON)
  /* Initilization Port module */
  IoHwAb_DigDirInit();
  #endif /* (IOHWAB_USE_DIG_DIR == STD_ON) */

  #if (IOHWAB_USE_IO_MAN == STD_ON)
  /* Initialization of IO functions first part, start switched battery */
  IoHwAb_IOMInit();
  #endif /* (IOHWAB_USE_IO_MAN == STD_ON) */

  IoHwAb_GddJobResult = IOHWAB_JOB_OK;

}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : IoHwAb_DeInit                                       **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          : This function deinitializes all the IO Hardware     **
**                        Abstraction software.                               **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
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
**                        Function(s) invoked    : biostartup_Startup         **
*******************************************************************************/
/* @Trace: SRS_BSW_00336 */
/* @Trace: SWS_IoHwAb_00044 */
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
/* @Trace: IoHwAb_SUD_API_002 */
FUNC(void, IOHWAB_CODE) IoHwAb_DeInit(void)
{
  #if (IOHWAB_USE_IO_MAN == STD_ON)
  /* Initialization of IO functions first part, start switched battery */
  IoHwAb_IOMDeInit();
  #endif /* (IOHWAB_USE_IO_MAN == STD_ON) */

  IoHwAb_GddJobResult = IOHWAB_JOB_UNINIT;
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : IoHwAb_GetVersionInfo                               **
**                                                                            **
** Service ID           : 0x10                                                **
**                                                                            **
** Description          : This function returns the version information of    **
**                        the this module.                                    **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : versioninfo                                         **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    :                            **
**                          Det_ReportError,                                  **
**                          Dem_ReportErrorStatus                             **
*******************************************************************************/

/* @Trace: IoHwAb_SUD_API_003 IoHwAb_SUD_API_004 */
/* @Trace: SRS_BSW_00407 */
/* @Trace: SWS_IoHwAb_00120 */
/* polyspace-begin MISRA-C3:D4.14 [Justified:Unset] "The pointer is checked always." */
#if (IOHWAB_VERSION_INFO_API == STD_ON)
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(void, IOHWAB_CODE) IoHwAb_GetVersionInfo(P2VAR(Std_VersionInfoType,
    AUTOMATIC,
    IOHWAB_APPL_DATA) versioninfo)
{
  /* Check whether version information is equal to NULL */
  if (IOHWAB_NULL_PTR == versioninfo)
  {
    #if (IOHWAB_DEV_ERROR_DETECT == STD_ON)
    /* Report to DET */
    (void) Det_ReportError((uint16)IOHWAB_MODULE_ID, (uint8)IOHWAB_INSTANCE_ID,
      (uint8)IOHWAB_GETVERSIONINFO_SID, (uint8)IOHWAB_E_DET_WRONG_PARAM);
    #endif /* (IOHWAB_DEV_ERROR_DETECT == STD_ON) */
    #if (IOHWAB_USE_DEM_EVENT == STD_ON)
    Dem_ReportErrorStatus(IOHWAB_E_WRONG_PARAM, DEM_EVENT_STATUS_FAILED);
    #endif /* (IOHWAB_USE_DEM_EVENT == STD_ON) */
  }
  else
  {
    /* Copy the vendor ID */
    versioninfo->vendorID = (uint16)IOHWAB_VENDOR_ID;

    /* Copy the module ID */
    versioninfo->moduleID = (uint16)IOHWAB_MODULE_ID;

    /* Copy software major version */
    versioninfo->sw_major_version = (uint8)IOHWAB_SW_MAJOR_VERSION;

    /* Copy software minor version */
    versioninfo->sw_minor_version = (uint8)IOHWAB_SW_MINOR_VERSION;

    /* Copy software patch version */
    versioninfo->sw_patch_version = (uint8)IOHWAB_SW_PATCH_VERSION;
  }
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"
#endif /* End of if (IOHWAB_VERSION_INFO_API == STD_ON) */
/* polyspace-end MISRA-C3:D4.14 [Justified:Unset] "The pointer is checked always." */

/*******************************************************************************
** Function Name        : IoHwAb_PreparePowerState                            **
**                                                                            **
** Service ID           : 0x80                                                **
** Description          : The API shall be invoked by the IoHwAbs in order to **
** prepare the transition to a given power state. The aim of this API is to   **
** incapsulate all actions to prepare the HW for a predefined power mode,     **
** decoupling application power definition from HW power states               **
**                                                                            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
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
**                        Function(s) invoked    :                            **
**                             Adc_GetCurrentPowerState                       **
**                             Adc_PreparePowerState                          **
**                             Pwm_GetCurrentPowerState                       **
**                             Pwm_PreparePowerState                          **
**                             Det_ReportError                                **
*******************************************************************************/
/* @Trace: SRS_IoHwAb_12453 */
/* @Trace: SWS_IoHwAb_00198 */
/* @Trace: SWS_IoHwAb_00154 */
/* @Trace: SWS_IoHwAb_00146 SWS_IoHwAb_00149 SWS_IoHwAb_00150 */
/* @Trace: IoHwAb_SUD_API_005 IoHwAb_SUD_API_006 IoHwAb_SUD_API_007 IoHwAb_SUD_API_008 */
#if (IOHWAB_USE_POWER_STATE == STD_ON)
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(void, IOHWAB_CODE) IoHwAb_PreparePowerState(uint8 state)
{

#if (IOHWAB_USE_ADC_POWER_STATE_API == STD_ON)
  Adc_PowerStateType Adc_CurrentPowerState = (uint8)IOHWAB_ZERO;
  Adc_PowerStateRequestResultType Adc_ret = ADC_SERVICE_ACCEPTED;

  (void) Adc_GetCurrentPowerState(&Adc_CurrentPowerState, &Adc_ret);
  if (Adc_ret != ADC_SERVICE_ACCEPTED)
  {
    /* Report to DET */
    #if (IOHWAB_DEV_ERROR_DETECT == STD_ON)
    (void) Det_ReportError((uint16)IOHWAB_MODULE_ID, (uint8)IOHWAB_INSTANCE_ID,
    (uint8)IOHWAB_PREPAREPOWERSTATE_SID, (uint8)IOHWAB_E_DET_GETPS_FAILED);
    #endif
  }
  else
  {
    if (Adc_CurrentPowerState != state) //check
    {
      (void) Adc_PreparePowerState((Adc_PowerStateType)state, &Adc_ret); // Prepare for low power
      if (Adc_ret != ADC_SERVICE_ACCEPTED)
      {
        /* Report to DET */
        #if (IOHWAB_DEV_ERROR_DETECT == STD_ON)
        (void) Det_ReportError((uint16)IOHWAB_MODULE_ID, (uint8)IOHWAB_INSTANCE_ID,
        (uint8)IOHWAB_PREPAREPOWERSTATE_SID, (uint8)IOHWAB_E_DET_PREPAREPS_FAILED);
        #endif
      }
    }
    else
    {
      // do nothing
    }
  }
#endif /* (IOHWAB_USE_POWER_STATE_API == STD_ON) */

#if (IOHWAB_USE_PWM_POWER_STATE_API == STD_ON)
  Pwm_PowerStateType Pwm_CurrentPowerState = 0;
  Pwm_PowerStateRequestResultType Pwm_ret = PWM_SERVICE_ACCEPTED;

  (void) Pwm_GetCurrentPowerState(&Pwm_CurrentPowerState, &Pwm_ret);
  if (Pwm_ret != PWM_SERVICE_ACCEPTED)
  {
    /* Report to DET */
    #if (IOHWAB_DEV_ERROR_DETECT == STD_ON)
    (void) Det_ReportError((uint16)IOHWAB_MODULE_ID, (uint8)IOHWAB_INSTANCE_ID,
      (uint8)IOHWAB_PREPAREPOWERSTATE_SID, (uint8)IOHWAB_E_DET_GETPS_FAILED);
    #endif
  }
  else
  {
    if (Pwm_CurrentPowerState != state) //check
    {
      (void) Pwm_PreparePowerState(state, &Pwm_ret); // Prepare for low power
      if (Pwm_ret != PWM_SERVICE_ACCEPTED)
      {
        /* Report to DET */
        #if (IOHWAB_DEV_ERROR_DETECT == STD_ON)
        (void) Det_ReportError((uint16)IOHWAB_MODULE_ID, (uint8)IOHWAB_INSTANCE_ID,
        (uint8)IOHWAB_PREPAREPOWERSTATE_SID, (uint8)IOHWAB_E_DET_PREPAREPS_FAILED);
        #endif
      }
    }
    else
    {
      // nothing
    }
  }
#endif /* (IOHWAB_USE_PWM_POWER_STATE_API == STD_ON) */

}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : IoHwAb_EnterPowerState_LowPower                     **
**                                                                            **
** Service ID           : 0x90                                                **
**                                                                            **
** Description          : The API shall be invoked by the IoHwAbs in order to **
** effectively enter a power state which was prepared by the API              **
**IoHwAb_PreparePowerState<#Mode>() . The aim of this API is to incapsulate   **
**all actions to set the HW in a power state corresponding to a predefined    **
**power mode, decoupling application power definition from HW power states    **
**                                                                            **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
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
**                        Function(s) invoked    :                            **
**                          Adc_SetPowerState                                 **
**                          Pwm_SetPowerState                                 **
**                          Det_ReportError                                   **
*******************************************************************************/
/* @Trace: SRS_IoHwAb_12454 */
/* @Trace: SWS_IoHwAb_00147 SWS_IoHwAb_00151 SWS_IoHwAb_00152 SWS_IoHwAb_00153 */
/* @Trace: IoHwAb_SUD_API_009 IoHwAb_SUD_API_010 */
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(void, IOHWAB_CODE) IoHwAb_EnterPowerState(void)
{

#if (IOHWAB_USE_ADC_POWER_STATE_API == STD_ON)
  Adc_PowerStateRequestResultType Adc_ret = ADC_SERVICE_ACCEPTED;

  (void) Adc_SetPowerState(&Adc_ret);
  if (Adc_ret != ADC_SERVICE_ACCEPTED)
  {
    /* Report to DET */
    #if (IOHWAB_DEV_ERROR_DETECT == STD_ON)
    (void) Det_ReportError((uint16)IOHWAB_MODULE_ID, (uint8)IOHWAB_INSTANCE_ID,
      (uint8)IOHWAB_ENTERPOWERSTATE_SID, (uint8)IOHWAB_E_DET_ENTERPS_FAILED);
    #endif
  }
  else
  {
    // do nothing
  }
#endif /* (IOHWAB_USE_ADC_POWER_STATE_API == STD_ON) */

#if (IOHWAB_USE_PWM_POWER_STATE_API == STD_ON)
  Pwm_PowerStateRequestResultType Pwm_ret = PWM_SERVICE_ACCEPTED;

  (void) Pwm_SetPowerState(&Pwm_ret);
  if (Pwm_ret != PWM_SERVICE_ACCEPTED)
  {
    /* Report to DET */
    #if (IOHWAB_DEV_ERROR_DETECT == STD_ON)
    (void) Det_ReportError((uint16)IOHWAB_MODULE_ID, (uint8)IOHWAB_INSTANCE_ID,
      (uint8)IOHWAB_ENTERPOWERSTATE_SID, (uint8)IOHWAB_E_DET_ENTERPS_FAILED);
    #endif
  }
  else
  {
    // do nothing
  }
#endif /* (IOHWAB_USE_PWM_POWER_STATE_API == STD_ON) */

}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"
#endif /* End of #if (IOHWAB_VERSION_INFO_API == STD_ON) */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
