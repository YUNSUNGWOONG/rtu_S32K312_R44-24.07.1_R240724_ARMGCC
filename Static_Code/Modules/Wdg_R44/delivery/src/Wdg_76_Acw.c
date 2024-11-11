/* polyspace +1 MISRA2012:1.1 [Justified: Low] "Macro definitions are needed for performance and file size" */
/*******************************************************************************
**                                                                            **
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  This source code is permitted to be used only in projects contracted with **
**  Hyundai Autoever, and any other use is prohibited.                        **
**  If you use it for other  purposes or change the source code, you may take **
**  legal responsibility.                                                     **
**  In this case, There is no warranty and technical support.                 **
**                                                                            **
**  SRC-MODULE: Wdg_76_Acw.c                                                  **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR AUTOEVER CUSTOM WDG                                   **
**                                                                            **
**  PURPOSE   : Autoever Custom Watchdog API Functionality                    **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By           Description                           **
********************************************************************************
** 0.0.1     11-Oct-2019   DongNx       Initial version                       **
** 0.0.2     18-Feb-2020   ThuanNM2     Add conversion factor                 **
** 0.0.3     13-Oct-2020   MinhNQ26     Fix warnings <#16419>                 **
** 1.3.1     19-May-2022   TriBD        R44_2021 #25412                       **
** 1.3.1.1   30-Jun-2022   TriBD        #CP44-324                             **
** 1.3.2.0   01-Aug-2022   TriBD        #CP44-384 (update UNECE standard)     **
** 1.3.3.0   12-Dec-2022   NhanNV8      #CP44-1021                            **
** 1.3.4.0   21-Aug-2023   JH KIM       #CP44-2795                            **
** 1.3.4.0   22-Aug-2023   HS Park      #CP44-2490                            **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/

/* @Trace: SRS_BSW_00346 SRS_Wdg_12165 SRS_Wdg_CUS_00003*/
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Wdg_76_Acw.h"
#include "HwResource.h"
#if (WDG_76_ACW_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"
#endif /* (WDG_76_ACW_DEV_ERROR_DETECT == STD_ON) */

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
/* polyspace +10 MISRA-C3:2.5 [Justified:Low] "This macro is necessary for Memory mapping" */
/* polyspace-begin MISRA-C3:20.1 [Justified: Low] "see SWS_MemMap_00004 of AUTOSAR" */
#if (WDG_76_ACW_DEV_ERROR_DETECT == STD_ON)
#define WDG_76_ACW_START_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h"
/* polyspace +1 VARIABLE:ALL [Not a defect:Low] "This is designed behavior." */
static VAR(Wdg_76_Acw_StatusType, WDG_76_ACW_VAR_INIT) Wdg_76_Acw_Status = \
  WDG_76_ACW_UNINIT;
#define WDG_76_ACW_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h"
#endif /* (WDG_76_ACW_DEV_ERROR_DETECT == STD_ON) */

/* polyspace +6 MISRA-C3:2.5 [Justified:Low] "This macro is necessary for Memory mapping" */
#define WDG_76_ACW_START_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h"
/* polyspace +1 VARIABLE:ALL [Not a defect:Low] "This is designed behavior." */
static VAR(WdgIf_ModeType, WDG_76_ACW_VAR_INIT) Wdg_76_Acw_CurrentMode = \
  WDGIF_SLOW_MODE;
#define WDG_76_ACW_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h"

#define WDG_76_ACW_START_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h"
/* polyspace +1 VARIABLE:ALL [Not a defect:Low] "This is designed behavior." */
static VAR(Dio_LevelType, WDG_76_ACW_VAR_INIT) Wdg_76_Acw_TriggerLevel = \
 (Dio_LevelType)STD_LOW;
#define WDG_76_ACW_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h"

#define WDG_76_ACW_START_SEC_VAR_CLEARED_32
#include "MemMap.h"
/* polyspace +1 VARIABLE:ALL [Not a defect:Low] "This is designed behavior." */
static VAR(uint32, WDG_76_ACW_VAR_INIT) Wdg_76_Acw_SlowPeriodUs = WDG_76_ACW_ZERO;
#define WDG_76_ACW_STOP_SEC_VAR_CLEARED_32
#include "MemMap.h"

/* polyspace-begin  MISRA-C3:2.5 [Justified:Low] "This macro is necessary for Memory mapping" */
#define WDG_76_ACW_START_SEC_VAR_CLEARED_32
#include "MemMap.h"
/* polyspace +1 VARIABLE:ALL [Not a defect:Low] "This is designed behavior." */
static VAR(uint32, WDG_76_ACW_VAR_INIT) Wdg_76_Acw_SlowDutyUs = WDG_76_ACW_ZERO;
#define WDG_76_ACW_STOP_SEC_VAR_CLEARED_32
#include "MemMap.h"

#define WDG_76_ACW_START_SEC_VAR_CLEARED_32
#include "MemMap.h"
/* polyspace +1 VARIABLE:ALL [Not a defect:Low] "This is designed behavior." */
static VAR(uint32, WDG_76_ACW_VAR_INIT) Wdg_76_Acw_FastPeriodUs = WDG_76_ACW_ZERO;
#define WDG_76_ACW_STOP_SEC_VAR_CLEARED_32
#include "MemMap.h"

/* polyspace-begin  MISRA-C3:2.5 [Justified:Low] "This macro is necessary for Memory mapping" */
#define WDG_76_ACW_START_SEC_VAR_CLEARED_32
#include "MemMap.h"
/* polyspace +1 VARIABLE:ALL [Not a defect:Low] "This is designed behavior." */
static VAR(uint32, WDG_76_ACW_VAR_INIT) Wdg_76_Acw_FastDutyUs = WDG_76_ACW_ZERO;
#define WDG_76_ACW_STOP_SEC_VAR_CLEARED_32
#include "MemMap.h"

#define WDG_76_ACW_START_SEC_VAR_CLEARED_32
#include "MemMap.h"
/* polyspace +1 VARIABLE:ALL [Not a defect:Low] "This is designed behavior." */
static VAR(uint32, WDG_76_ACW_VAR_INIT) Wdg_76_Acw_TriggerCount = WDG_76_ACW_ZERO;
#define WDG_76_ACW_STOP_SEC_VAR_CLEARED_32
#include "MemMap.h"

#define WDG_76_ACW_START_SEC_VAR_CLEARED_32
#include "MemMap.h"
/* polyspace +1 VARIABLE:ALL [Not a defect:Low] "This is designed behavior." */
static VAR(uint32, WDG_76_ACW_VAR_INIT) Wdg_76_Acw_SlowDutyTick = WDG_76_ACW_ZERO;
#define WDG_76_ACW_STOP_SEC_VAR_CLEARED_32
#include "MemMap.h"

#define WDG_76_ACW_START_SEC_VAR_CLEARED_32
#include "MemMap.h"
/* polyspace +1 VARIABLE:ALL [Not a defect:Low] "This is designed behavior." */
static VAR(uint32, WDG_76_ACW_VAR_INIT) Wdg_76_Acw_FastDutyTick = WDG_76_ACW_ZERO;
#define WDG_76_ACW_STOP_SEC_VAR_CLEARED_32
#include "MemMap.h"

#define WDG_76_ACW_START_SEC_VAR_CLEARED_32
#include "MemMap.h"
/* polyspace +1 VARIABLE:ALL [Not a defect:Low] "This is designed behavior." */
static VAR(uint32, WDG_76_ACW_VAR_INIT) Wdg_76_Acw_SlowPeriodTick = WDG_76_ACW_ZERO;
#define WDG_76_ACW_STOP_SEC_VAR_CLEARED_32
#include "MemMap.h"

#define WDG_76_ACW_START_SEC_VAR_CLEARED_32
#include "MemMap.h"
/* polyspace +1 VARIABLE:ALL [Not a defect:Low] "This is designed behavior." */
static VAR(uint32, WDG_76_ACW_VAR_INIT) Wdg_76_Acw_FastPeriodTick = WDG_76_ACW_ZERO;
#define WDG_76_ACW_STOP_SEC_VAR_CLEARED_32
#include "MemMap.h"


/*******************************************************************************
**                       Function Prototypes                                  **
*******************************************************************************/


#define WDG_76_ACW_START_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
/*******************************************************************************
** Function Name        : Wdg_76_Acw_Init                                     **
**                                                                            **
** Service ID           : 0x00                                                **
**                                                                            **
** Description          : Initializes the module                              **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : ConfigPtr : container all parameter to initialize   **
**                                       module                               **
**                                                                            **
** InOut parameter      : none                                                **
**                                                                            **
** Output Parameters    : none                                                **
**                                                                            **
** Return parameter     : none                                                **
**                                                                            **
** Preconditions        : none                                                **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                            Wdg_76_Acw_CurrentMode                          **
**                            Wdg_76_Acw_FastDutyUs                           **
**                            Wdg_76_Acw_SlowDutyUs                           **
**                            Wdg_76_Acw_FastPeriodUs                         **
**                            Wdg_76_Acw_DutyPeriodUs                         **
**                            Wdg_76_Acw_Status                               **
**                            Wdg_76_Acw_TriggerLevel                         **
**                            Wdg_76_Acw_TriggerCount                         **
**                                                                            **
**                        Function(s) invoked :                               **
**                            Det_ReportError                                 **
**                            Dem_ReportErrorStatus                           **
**                            Gpt_StopTimer                                   **
**                            Dio_WriteChannel                                **
**                            Gpt_EnableNotification                          **
**                            Gpt_StartTimer                                  **
*******************************************************************************/

/* @Trace: SRS_BSW_00101 SRS_BSW_00323 SRS_BSW_00335 SRS_BSW_00337 
 SRS_BSW_00400 SRS_BSW_00406 SRS_SPAL_12057 SRS_SPAL_12125 SRS_BSW_00414 
 SRS_SPAL_12448 SRS_SPAL_12461 SRS_Wdg_12105 SRS_Wdg_12106 SRS_BSW_00466
 SRS_BSW_00358
*/
FUNC(void, WDG_76_ACW_CODE) Wdg_76_Acw_Init \
  (P2CONST(Wdg_76_Acw_ConfigType, AUTOMATIC, WDG_76_ACW_APPL_CONST) ConfigPtr)
{
  P2CONST(Wdg_76_Acw_ConfigType, AUTOMATIC, WDG_76_ACW_APPL_CONST) LpConfig \
    = NULL_PTR;
  #ifndef WDG_76_ACW_INITMODE_IS_OFF_MODE
  VAR(Gpt_ValueType, AUTOMATIC) NextGptTick;
  #endif
  
  /* @Trace: Wdg_SUD_API_020 */
  /* polyspace +2 MISRA2012:2.2 DEFECT:USELESS_WRITE [Not a defect:Low] "It's not a dead-code, the assignment based on AUTOSAR specification" */
  #if (WDG_76_ACW_DEV_ERROR_DETECT == STD_ON)
  Wdg_76_Acw_Status = WDG_76_ACW_UNINIT;
  #endif /* (WDG_76_ACW_DEV_ERROR_DETECT == STD_ON) */

  #if (WDG_76_ACW_PRECOMPILE_SUPPORT == STD_ON)
  WDG_76_ACW_UNUSED_PTR(ConfigPtr);
  /* If precompile support enable, initialize the configuration pointer
    with the default pointer */
  LpConfig = &Wdg_76_Acw_Config;
  #else /* (WDG_76_ACW_PRECOMPILE_SUPPORT == STD_ON) */
  LpConfig = ConfigPtr;
  #endif /* (WDG_76_ACW_PRECOMPILE_SUPPORT == STD_ON) */

  #if (WDG_76_ACW_PRECOMPILE_SUPPORT == STD_OFF)
  if (NULL_PTR == LpConfig)
  {
    /* @Trace: Wdg_SUD_PB_API_021 */
    #if (WDG_76_ACW_DEV_ERROR_DETECT == STD_ON)
    (void)Det_ReportError(WDG_76_ACW_MODULE_ID, WDG_76_ACW_INSTANCE_ID, \
      WDG_76_ACW_INIT_SID, WDG_76_ACW_E_PARAM_POINTER);
    #endif /* (WDG_76_ACW_DEV_ERROR_DETECT == STD_ON) */
  }/* polyspace +3 MISRA-C3:D4.14 [Not a defect:Low] "Pointer is checked null before using" */
  else
  #endif /* (WDG_76_ACW_PRECOMPILE_SUPPORT == STD_OFF) */
  {
    #if (WDG_76_ACW_DISABLE_ALLOWED == STD_OFF) && defined(WDG_76_ACW_INITMODE_IS_OFF_MODE)
      /* @Trace: Wdg_SUD_API_024 */
      WDG_76_ACW_UNUSED_PTR(LpConfig);
      #if (WDG_76_ACW_DEM_ERROR_REPORT == STD_ON)
      Dem_ReportErrorStatus(WDG_76_ACW_E_DISABLE_REJECTED, \
        DEM_EVENT_STATUS_FAILED);
      #endif /* (WDG_76_ACW_DEM_ERROR_REPORT == STD_ON) */
    #else /* (WDG_76_ACW_DISABLE_ALLOWED == STD_OFF) */
    {
      /* @Trace: Wdg_SUD_API_025 */
      #if (WDG_76_ACW_DEV_ERROR_DETECT == STD_ON)
      Wdg_76_Acw_Status = WDG_76_ACW_BUSY;
      #endif /* (WDG_76_ACW_DEV_ERROR_DETECT == STD_ON) */
          
      Gpt_StopTimer(WDG_76_ACW_GPT_CHANNEL);
      
      Wdg_76_Acw_CurrentMode = LpConfig->InitialMode;
      Wdg_76_Acw_FastDutyUs = LpConfig->FastDutyUs;
      Wdg_76_Acw_SlowDutyUs = LpConfig->SlowDutyUs;
      Wdg_76_Acw_FastPeriodUs = LpConfig->FastPeriodUs;
      Wdg_76_Acw_SlowPeriodUs = LpConfig->SlowPeriodUs;
      Wdg_76_Acw_FastDutyTick = LpConfig->FastDutyTick;
      Wdg_76_Acw_SlowDutyTick = LpConfig->SlowDutyTick;
      Wdg_76_Acw_FastPeriodTick = LpConfig->FastPeriodTick;
      Wdg_76_Acw_SlowPeriodTick = LpConfig->SlowPeriodTick;
      
      #if defined(WDG_76_ACW_INITMODE_IS_FAST_MODE)
        /* @Trace: Wdg_SUD_API_029 */
        Wdg_76_Acw_TriggerLevel = (Dio_LevelType)STD_LOW;
        #ifdef WDG_76_ACW_DIO_MODE_CHANNEL
        Dio_WriteChannel(WDG_76_ACW_DIO_MODE_CHANNEL, WDG_76_ACW_FAST_MODE_LEVEL);
        #endif

        Dio_WriteChannel(WDG_76_ACW_DIO_TRIGGER_CHANNEL, Wdg_76_Acw_TriggerLevel); 

        Wdg_76_Acw_TriggerCount = LpConfig->InitialTimeoutUs / Wdg_76_Acw_FastPeriodUs;
        
        #if HWRESOURCE_VENDOR(HWRESOURCE_INFINEON)
        NextGptTick = (Gpt_ValueType)(Wdg_76_Acw_FastPeriodUs - Wdg_76_Acw_FastDutyUs);
        #else
        NextGptTick = (Gpt_ValueType)(Wdg_76_Acw_FastPeriodTick - Wdg_76_Acw_FastDutyTick);
        #endif

        Gpt_EnableNotification(WDG_76_ACW_GPT_CHANNEL);
        Gpt_StartTimer(WDG_76_ACW_GPT_CHANNEL, NextGptTick);
        
        #if (WDG_76_ACW_DISABLE_ALLOWED == STD_ON)
        #ifdef WDG_76_ACW_DIO_ENABLE_CHANNEL
        Dio_WriteChannel(WDG_76_ACW_DIO_ENABLE_CHANNEL, \
                        (Dio_LevelType)WDG_76_ACW_ENABLE_LEVEL);
        #endif
        #endif /* (WDG_76_ACW_DISABLE_ALLOWED == STD_ON) */  

      #elif defined(WDG_76_ACW_INITMODE_IS_SLOW_MODE)
        /* @Trace: Wdg_SUD_API_028 */
        Wdg_76_Acw_TriggerLevel = (Dio_LevelType)STD_LOW;

        #ifdef WDG_76_ACW_DIO_MODE_CHANNEL
        Dio_WriteChannel(WDG_76_ACW_DIO_MODE_CHANNEL, WDG_76_ACW_SLOW_MODE_LEVEL);
        #endif

        Dio_WriteChannel(WDG_76_ACW_DIO_TRIGGER_CHANNEL, Wdg_76_Acw_TriggerLevel); 

        Wdg_76_Acw_TriggerCount = LpConfig->InitialTimeoutUs / Wdg_76_Acw_SlowPeriodUs;
        
        #if HWRESOURCE_VENDOR(HWRESOURCE_INFINEON)
        NextGptTick = (Gpt_ValueType)(Wdg_76_Acw_SlowPeriodUs - Wdg_76_Acw_SlowDutyUs);
        #else
        NextGptTick = (Gpt_ValueType)(Wdg_76_Acw_SlowPeriodTick - Wdg_76_Acw_SlowDutyTick);
        #endif

        Gpt_EnableNotification(WDG_76_ACW_GPT_CHANNEL);
        Gpt_StartTimer(WDG_76_ACW_GPT_CHANNEL, NextGptTick);
        
        #if (WDG_76_ACW_DISABLE_ALLOWED == STD_ON)
        #ifdef WDG_76_ACW_DIO_ENABLE_CHANNEL
        Dio_WriteChannel(WDG_76_ACW_DIO_ENABLE_CHANNEL, \
                        (Dio_LevelType)WDG_76_ACW_ENABLE_LEVEL);
        #endif
        #endif /* (WDG_76_ACW_DISABLE_ALLOWED == STD_ON) */  
        
      #elif (WDG_76_ACW_DISABLE_ALLOWED == STD_ON) && defined(WDG_76_ACW_INITMODE_IS_OFF_MODE)
        /* @Trace: Wdg_SUD_API_027 */
        Wdg_76_Acw_TriggerCount = WDG_76_ACW_ZERO;
        Gpt_DisableNotification(WDG_76_ACW_GPT_CHANNEL);
        Gpt_StopTimer(WDG_76_ACW_GPT_CHANNEL);
        
        #ifdef WDG_76_ACW_DIO_ENABLE_CHANNEL
        Dio_WriteChannel(WDG_76_ACW_DIO_ENABLE_CHANNEL, \
                        (Dio_LevelType)WDG_76_ACW_DISABLE_LEVEL);
        #endif
        
        #if (WDG_76_ACW_DEM_ERROR_REPORT == STD_ON)
        Dem_ReportErrorStatus(WDG_76_ACW_E_DISABLE_REJECTED, \
          DEM_EVENT_STATUS_PASSED);
        #endif /* (WDG_76_ACW_DEM_ERROR_REPORT == STD_ON) */
      #endif /* (WDG_76_ACW_DISABLE_ALLOWED == STD_ON) && defined(WDG_76_ACW_INITMODE_IS_OFF_MODE) */
      #if (WDG_76_ACW_DEV_ERROR_DETECT == STD_ON)
      /* @Trace: Wdg_SUD_API_031 */
      Wdg_76_Acw_Status = WDG_76_ACW_IDLE;
      #endif /* (WDG_76_ACW_DEV_ERROR_DETECT == STD_ON) */
    }
    #endif
  }
}
#define WDG_76_ACW_STOP_SEC_CODE
#include "MemMap.h"

#define WDG_76_ACW_START_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
/*******************************************************************************
** Function Name        : Wdg_76_Acw_SetMode                                  **
**                                                                            **
** Service ID           : 0x01                                                **
**                                                                            **
** Description          : Switches the watchdog into the mode Mode.           **
**                                                                            **
** Sync/Async           :  Synchronous                                        **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : Mode : container new mode to switch                 **
**                                                                            **
** InOut parameter      : none                                                **
**                                                                            **
** Output Parameters    : none                                                **
**                                                                            **
** Return parameter     : ReturnValue: return status switch mode ok           **
**                                          or not ok                         **
**                                                                            **
** Preconditions        : none                                                **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                            Wdg_76_Acw_CurrentMode                          **
**                            Wdg_76_Acw_FastDutyUs                           **
**                            Wdg_76_Acw_SlowDutyUs                           **
**                            Wdg_76_Acw_FastPeriodUs                         **
**                            Wdg_76_Acw_DutyPeriodUs                         **
**                            Wdg_76_Acw_Status                               **
**                            Wdg_76_Acw_TriggerLevel                         **
**                            Wdg_76_Acw_TriggerCount                         **
**                                                                            **
**                        Function(s) invoked :                               **
**                            Det_ReportError                                 **
**                            Dem_ReportErrorStatus                           **
**                            Dio_WriteChannel                                **
**                            Gpt_StopTimer                                   **
**                            Gpt_DisableNotification                         **
**                            Gpt_EnableNotification                          **
**                            Gpt_StartTimer                                  **
*******************************************************************************/
/* @Trace: SRS_BSW_00323 SRS_BSW_00335 SRS_BSW_00337 SRS_BSW_00466
 SRS_SPAL_12448 SRS_Wdg_12015 SRS_Wdg_12018 SRS_Wdg_12106
 SRS_SPAL_12092 SRS_Wdg_CUS_00004
*/
FUNC(Std_ReturnType, WDG_76_ACW_CODE) Wdg_76_Acw_SetMode \
  (VAR(WdgIf_ModeType, AUTOMATIC) Mode)
{
  VAR(Gpt_ValueType, AUTOMATIC) NextGptTick;
  VAR(Std_ReturnType, AUTOMATIC) returnValue;

  returnValue = (Std_ReturnType)E_OK;
  
  #if (WDG_76_ACW_DEV_ERROR_DETECT == STD_ON)
  if (WDG_76_ACW_IDLE != Wdg_76_Acw_Status)
  {
    /* @Trace: Wdg_SUD_API_001 */
    (void)Det_ReportError(WDG_76_ACW_MODULE_ID, WDG_76_ACW_INSTANCE_ID, \
        WDG_76_ACW_SETMODE_SID, WDG_76_ACW_E_DRIVER_STATE);
    returnValue = E_NOT_OK;
  }
  else
  #endif /* (WDG_76_ACW_DEV_ERROR_DETECT == STD_ON) */
  {
    #if (WDG_76_ACW_DISABLE_ALLOWED == STD_OFF)
    if (WDGIF_OFF_MODE == Mode)
    {
      /* @Trace: Wdg_SUD_API_002 */
      #if (WDG_76_ACW_DEM_ERROR_REPORT == STD_ON)
      Dem_ReportErrorStatus(WDG_76_ACW_E_DISABLE_REJECTED, \
        DEM_EVENT_STATUS_FAILED);
      #endif /* (WDG_76_ACW_DEM_ERROR_REPORT == STD_ON) */
      
      #if (WDG_76_ACW_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(WDG_76_ACW_MODULE_ID, WDG_76_ACW_INSTANCE_ID, \
        WDG_76_ACW_SETMODE_SID, WDG_76_ACW_E_PARAM_MODE);
      #endif /* (WDG_76_ACW_DEV_ERROR_DETECT == STD_ON) */
      
      returnValue = E_NOT_OK;
    }
    else
    #endif /* (WDG_76_ACW_DISABLE_ALLOWED == STD_OFF) */
    {
      /* @Trace: Wdg_SUD_API_003 */
      #if (WDG_76_ACW_DEV_ERROR_DETECT == STD_ON)
      Wdg_76_Acw_Status = WDG_76_ACW_BUSY;
      #endif /* (WDG_76_ACW_DEV_ERROR_DETECT == STD_ON) */   
             
      if (WDGIF_FAST_MODE == Mode)
      {
        /* @Trace: Wdg_SUD_API_006 */
        if (WDGIF_FAST_MODE != Wdg_76_Acw_CurrentMode)
        {
          if ((Dio_LevelType)STD_LOW == Wdg_76_Acw_TriggerLevel)
          {
            Wdg_76_Acw_TriggerLevel = (Dio_LevelType)STD_HIGH;
            #if HWRESOURCE_VENDOR(HWRESOURCE_INFINEON)
            NextGptTick = (Gpt_ValueType)(Wdg_76_Acw_FastDutyUs);
            #else
            NextGptTick = (Gpt_ValueType)(Wdg_76_Acw_FastDutyTick);
            #endif
          }
          else 
          {
            Wdg_76_Acw_TriggerLevel = (Dio_LevelType)STD_LOW;
            #if HWRESOURCE_VENDOR(HWRESOURCE_INFINEON)
            NextGptTick = (Gpt_ValueType)(Wdg_76_Acw_FastPeriodUs - Wdg_76_Acw_FastDutyUs);
            #else
            NextGptTick = (Gpt_ValueType)(Wdg_76_Acw_FastPeriodTick - Wdg_76_Acw_FastDutyTick);
            #endif
          }
          
          Dio_WriteChannel(WDG_76_ACW_DIO_TRIGGER_CHANNEL, (Dio_LevelType)Wdg_76_Acw_TriggerLevel);

          #ifdef WDG_76_ACW_DIO_MODE_CHANNEL
          Dio_WriteChannel(WDG_76_ACW_DIO_MODE_CHANNEL, WDG_76_ACW_FAST_MODE_LEVEL);          
          #endif
        }
        else 
        {
          NextGptTick = Gpt_GetTimeRemaining(WDG_76_ACW_GPT_CHANNEL);
        }
        
        if (WDG_76_ACW_ZERO != NextGptTick)
        {
          Gpt_DisableNotification(WDG_76_ACW_GPT_CHANNEL);
          Gpt_StopTimer(WDG_76_ACW_GPT_CHANNEL);
		  
          Gpt_EnableNotification(WDG_76_ACW_GPT_CHANNEL);
          Gpt_StartTimer(WDG_76_ACW_GPT_CHANNEL, NextGptTick);
        }
        else
        {
          /* Branch for MISRA compliance*/
        }
      }
      else if (WDGIF_SLOW_MODE == Mode)
      {
        /* @Trace: Wdg_SUD_API_007 */
        if (WDGIF_SLOW_MODE != Wdg_76_Acw_CurrentMode)
        {
          if ((Dio_LevelType)STD_LOW == Wdg_76_Acw_TriggerLevel)
          {
            Wdg_76_Acw_TriggerLevel = (Dio_LevelType)STD_HIGH;
            #if HWRESOURCE_VENDOR(HWRESOURCE_INFINEON)
            NextGptTick = (Gpt_ValueType)(Wdg_76_Acw_SlowDutyUs);
            #else
            NextGptTick = (Gpt_ValueType)(Wdg_76_Acw_SlowDutyTick);
            #endif
          }
          else 
          {
            Wdg_76_Acw_TriggerLevel = (Dio_LevelType)STD_LOW;
            #if HWRESOURCE_VENDOR(HWRESOURCE_INFINEON)
            NextGptTick = (Gpt_ValueType)(Wdg_76_Acw_SlowPeriodUs - Wdg_76_Acw_SlowDutyUs);
            #else
            NextGptTick = (Gpt_ValueType)(Wdg_76_Acw_SlowPeriodTick - Wdg_76_Acw_SlowDutyTick);
            #endif
          }
          
          Dio_WriteChannel(WDG_76_ACW_DIO_TRIGGER_CHANNEL, (Dio_LevelType)Wdg_76_Acw_TriggerLevel);

          #ifdef WDG_76_ACW_DIO_MODE_CHANNEL
          Dio_WriteChannel(WDG_76_ACW_DIO_MODE_CHANNEL, WDG_76_ACW_SLOW_MODE_LEVEL);          
          #endif
        }
        else 
        {
          NextGptTick = Gpt_GetTimeRemaining(WDG_76_ACW_GPT_CHANNEL);
        }
        
        if (WDG_76_ACW_ZERO != NextGptTick)
        {
          Gpt_DisableNotification(WDG_76_ACW_GPT_CHANNEL);
          Gpt_StopTimer(WDG_76_ACW_GPT_CHANNEL);
		  
          Gpt_EnableNotification(WDG_76_ACW_GPT_CHANNEL);
          Gpt_StartTimer(WDG_76_ACW_GPT_CHANNEL, NextGptTick);
        }
        else
        {
          /* Branch for MISRA compliance*/
        }
      }
      #if (WDG_76_ACW_DISABLE_ALLOWED == STD_ON)
      else  /* WDGIF_OFF_MODE */
      {
        /* @Trace: Wdg_SUD_API_004 */
        Wdg_76_Acw_TriggerCount = WDG_76_ACW_ZERO;
        
        #ifdef WDG_76_ACW_DIO_ENABLE_CHANNEL
        Dio_WriteChannel(WDG_76_ACW_DIO_ENABLE_CHANNEL, \
                        (Dio_LevelType)WDG_76_ACW_DISABLE_LEVEL);
        #endif
						
        #if (WDG_76_ACW_DEM_ERROR_REPORT == STD_ON)
        Dem_ReportErrorStatus(WDG_76_ACW_E_DISABLE_REJECTED, \
          DEM_EVENT_STATUS_PASSED);
        #endif /* (WDG_76_ACW_DEM_ERROR_REPORT == STD_ON) */
      }
      #else
      else
      {
        /* This branch makes polyspace happy*/
      }
      #endif /* (WDG_76_ACW_DISABLE_ALLOWED == STD_ON) */
      
      /* @Trace: Wdg_SUD_API_005 */
      Wdg_76_Acw_CurrentMode = Mode;
      
      #if (WDG_76_ACW_DEV_ERROR_DETECT == STD_ON)
      Wdg_76_Acw_Status = WDG_76_ACW_IDLE;
      #endif /* (WDG_76_ACW_DEV_ERROR_DETECT == STD_ON) */
    } /* End of the condition "if Mode equal to WDGIF_OFF_MODE" */
  } /* if (Wdg_76_Acw_Status != WDG_76_ACW_IDLE) */

  return returnValue;
}
#define WDG_76_ACW_STOP_SEC_CODE
#include "MemMap.h"


#define WDG_76_ACW_START_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
/*******************************************************************************
** Function Name        : Wdg_76_Acw_SetTriggerCondition                      **
**                                                                            **
** Service ID           : 0x03                                                **
**                                                                            **
** Description          : Sets the timeout value for the trigger counter.     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : timeout : time trigger module external wdg          **
**                                                                            **
** InOut parameter      : none                                                **
**                                                                            **
** Output Parameters    : none                                                **
**                                                                            **
** Return parameter     : none                                                **
**                                                                            **
** Preconditions        : none                                                **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                            Wdg_76_Acw_CurrentMode                          **
**                            Wdg_76_Acw_FastDutyUs                           **
**                            Wdg_76_Acw_SlowDutyUs                           **
**                            Wdg_76_Acw_FastPeriodUs                         **
**                            Wdg_76_Acw_DutyPeriodUs                         **
**                            Wdg_76_Acw_Status                               **
**                            Wdg_76_Acw_TriggerLevel                         **
**                            Wdg_76_Acw_TriggerCount                         **
**                                                                            **
**                        Function(s) invoked :                               **
**                            Det_ReportError                                 **
**                            Dio_WriteChannel                                **
**                            Gpt_StopTimer                                   **
**                            Gpt_DisableNotification                         **
**                            Gpt_StartTimer                                  **
*******************************************************************************/
/* @Trace: SRS_BSW_00337 SRS_BSW_00337 SRS_BSW_00323 SRS_BSW_00343 SRS_SPAL_12448
 SRS_Wdg_12019 SRS_SPAL_12092
*/
FUNC(void, WDG_76_ACW_CODE) Wdg_76_Acw_SetTriggerCondition \
  (VAR(uint16, AUTOMATIC) timeout)
{
  VAR(boolean, AUTOMATIC) Success;
  VAR(uint32, AUTOMATIC) TimeoutUs;
  
  Success = (boolean)TRUE;
  TimeoutUs = WDG_76_ACW_CONVERT_TO_US * (uint32)timeout;
  
  /* @Trace: Wdg_SUD_API_010 */
  #if (WDG_76_ACW_DEV_ERROR_DETECT == STD_ON)
  if (WDG_76_ACW_IDLE != Wdg_76_Acw_Status)
  {
    (void)Det_ReportError(WDG_76_ACW_MODULE_ID, WDG_76_ACW_INSTANCE_ID, \
      WDG_76_ACW_SETTRIGGERCONDITION_SID, WDG_76_ACW_E_DRIVER_STATE);
      
    Success = FALSE;
  }
  #endif /* (WDG_76_ACW_DEV_ERROR_DETECT == STD_ON) */

  if (WDG_76_ACW_MAX_TIMEOUT < TimeoutUs)
  {
    #if (WDG_76_ACW_DEV_ERROR_DETECT == STD_ON)
    (void)Det_ReportError(WDG_76_ACW_MODULE_ID, WDG_76_ACW_INSTANCE_ID, \
      WDG_76_ACW_SETTRIGGERCONDITION_SID, WDG_76_ACW_E_PARAM_TIMEOUT);
    #endif /* (WDG_76_ACW_DEV_ERROR_DETECT == STD_ON) */
    
    Success = FALSE;
  }

  if (TRUE == Success)
  {
    if (WDG_76_ACW_ZERO == TimeoutUs)
    {
      /* @Trace: Wdg_SUD_API_013 */
      Gpt_DisableNotification(WDG_76_ACW_GPT_CHANNEL);
      Gpt_StopTimer(WDG_76_ACW_GPT_CHANNEL);
    
      Wdg_76_Acw_TriggerCount = WDG_76_ACW_ZERO;
      #if (WDG_76_ACW_DEV_ERROR_DETECT == STD_ON)
      Wdg_76_Acw_Status = WDG_76_ACW_EXPIRED;
      #endif /* (WDG_76_ACW_DEV_ERROR_DETECT == STD_ON) */
    }
    else
    {        
      /* @Trace: Wdg_SUD_API_012 */
      if (WDGIF_FAST_MODE == Wdg_76_Acw_CurrentMode)
      {
	/* polyspace +1 RTE:ZDV [Justified:Low] "Generator has been validated for non-zero value." */
        Wdg_76_Acw_TriggerCount = TimeoutUs / Wdg_76_Acw_FastPeriodUs;
      }
      else if (WDGIF_SLOW_MODE == Wdg_76_Acw_CurrentMode)
      {
	/* polyspace +1 RTE:ZDV [Justified:Low] "Generator has been validated for non-zero value." */
        Wdg_76_Acw_TriggerCount = TimeoutUs / Wdg_76_Acw_SlowPeriodUs;
      } else
      {
	  /* Branch for MISRA compliance*/
      }
    }
  }
}
#define WDG_76_ACW_STOP_SEC_CODE
#include "MemMap.h"

#if (WDG_76_ACW_VERSION_INFO_API == STD_ON)
#define WDG_76_ACW_START_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
/*******************************************************************************
** Function Name        : Wdg_76_Acw_GetVersionInfo                           **
**                                                                            **
** Service ID           : 0x04                                                **
**                                                                            **
** Description          : Returns the version information of the module.      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : versioninfo : container version information         **
**                                                                            **
** InOut parameter      : none                                                **
**                                                                            **
** Output Parameters    : none                                                **
**                                                                            **
** Return parameter     : none                                                **
**                                                                            **
** Preconditions        : none                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : none                          **
**                                                                            **
**                        Function(s) invoked :                               **
**                            Det_ReportError                                 **
*******************************************************************************/
/* @Trace: SRS_Wdg_CUS_00001
*/
FUNC(void, WDG_76_ACW_CODE) Wdg_76_Acw_GetVersionInfo \
  (P2VAR(Std_VersionInfoType, AUTOMATIC, WDG_76_ACW_APPL_CONST) versioninfo)
{
  /* check NULL pointer */
  if (NULL_PTR == versioninfo)
  {
    /* @Trace: Wdg_SUD_API_015 */
    #if(WDG_76_ACW_DEV_ERROR_DETECT == STD_ON)
    /* Report to DET */
    (void)Det_ReportError(WDG_76_ACW_MODULE_ID, WDG_76_ACW_INSTANCE_ID, \
      WDG_76_ACW_GETVERSIONINFO_SID, WDG_76_ACW_E_PARAM_POINTER);
    /* @Traceability END -- SUD: Wdg_SUD_API_015 */
    #endif /* (WDG_76_ACW_DEV_ERROR_DETECT == STD_ON) */
  }
  else
  {
    /* @Trace: Wdg_SUD_API_016 */
    /* Load the vendor Id */
    /* polyspace +10 MISRA-C3:D4.14 [Not a defect:Low] "Pointer is checked null before using" */
    versioninfo->vendorID = WDG_76_ACW_VENDOR_ID;
    /* Load the module Id */
    versioninfo->moduleID = WDG_76_ACW_MODULE_ID;
    /* Load Software Major Version */
    versioninfo->sw_major_version = WDG_76_ACW_SW_MAJOR_VERSION;
    /* Load Software Minor Version */
    versioninfo->sw_minor_version = WDG_76_ACW_SW_MINOR_VERSION;
    /* Load Software Patch Version */
    versioninfo->sw_patch_version = WDG_76_ACW_SW_PATCH_VERSION;
  }
}
#define WDG_76_ACW_STOP_SEC_CODE
#include "MemMap.h"
#endif /* (WDG_76_ACW_VERSION_INFO_API == STD_ON) */

#define WDG_76_ACW_START_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
/*******************************************************************************
** Function Name        : Wdg_76_Acw_Gpt_Cbk                                  **
**                                                                            **
** Service ID           : 0x05                                                **
**                                                                            **
** Description          : implement trigger external wdg                      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : none                                                **
**                                                                            **
** InOut parameter      : none                                                **
**                                                                            **
** Output Parameters    : none                                                **
**                                                                            **
** Return parameter     : none                                                **
**                                                                            **
** Preconditions        : none                                                **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                            Wdg_76_Acw_CurrentMode                          **
**                            Wdg_76_Acw_FastDutyUs                           **
**                            Wdg_76_Acw_SlowDutyUs                           **
**                            Wdg_76_Acw_FastPeriodUs                         **
**                            Wdg_76_Acw_DutyPeriodUs                         **
**                            Wdg_76_Acw_TriggerLevel                         **
**                            Wdg_76_Acw_TriggerCount                         **
**                                                                            **
**                        Function(s) invoked : none                          **
*******************************************************************************/
FUNC(void, WDG_76_ACW_GPT_CODE) Wdg_76_Acw_Gpt_Cbk(void)
{
  VAR(Gpt_ValueType, WDG_76_ACW_VAR) NextGptTick;
  
  if(WDG_76_ACW_ZERO < Wdg_76_Acw_TriggerCount)
  {
      
    if ((Dio_LevelType)STD_LOW == Wdg_76_Acw_TriggerLevel)
    {
      /* @Trace: Wdg_SUD_API_035 */
      Wdg_76_Acw_TriggerLevel = (Dio_LevelType)STD_HIGH;
      
      if (WDGIF_FAST_MODE == Wdg_76_Acw_CurrentMode)
      {
        #if HWRESOURCE_VENDOR(HWRESOURCE_INFINEON)
        NextGptTick = (Gpt_ValueType)(Wdg_76_Acw_FastDutyUs);
        #else
        NextGptTick = (Gpt_ValueType)(Wdg_76_Acw_FastDutyTick);
        #endif
      }
      else
      {
        #if HWRESOURCE_VENDOR(HWRESOURCE_INFINEON)
        NextGptTick = (Gpt_ValueType)(Wdg_76_Acw_SlowDutyUs);
        #else
        NextGptTick = (Gpt_ValueType)(Wdg_76_Acw_SlowDutyTick);
        #endif
      }
      
      Wdg_76_Acw_TriggerCount--;
    }
    else
    {
      /* @Trace: Wdg_SUD_API_036 */
      Wdg_76_Acw_TriggerLevel = (Dio_LevelType)STD_LOW; 
      
      if (WDGIF_FAST_MODE == Wdg_76_Acw_CurrentMode)
      {
        #if HWRESOURCE_VENDOR(HWRESOURCE_INFINEON)
        NextGptTick = (Gpt_ValueType)(Wdg_76_Acw_FastPeriodUs - Wdg_76_Acw_FastDutyUs);
        #else
        NextGptTick = (Gpt_ValueType)(Wdg_76_Acw_FastPeriodTick - Wdg_76_Acw_FastDutyTick);
        #endif
      }
      else
      {
        #if HWRESOURCE_VENDOR(HWRESOURCE_INFINEON)
        NextGptTick = (Gpt_ValueType)((Wdg_76_Acw_SlowPeriodUs - Wdg_76_Acw_SlowDutyUs));
        #else
        NextGptTick = (Gpt_ValueType)(Wdg_76_Acw_SlowPeriodTick - Wdg_76_Acw_SlowDutyTick);
        #endif                
      }
    }  
    /* @Trace: Wdg_SUD_API_037 */
    Gpt_StartTimer(WDG_76_ACW_GPT_CHANNEL, NextGptTick);
    Dio_WriteChannel(WDG_76_ACW_DIO_TRIGGER_CHANNEL, Wdg_76_Acw_TriggerLevel);
  }
  else 
  {
    /* @Trace: Wdg_SUD_API_038 */
    Gpt_DisableNotification(WDG_76_ACW_GPT_CHANNEL);
    Gpt_StopTimer(WDG_76_ACW_GPT_CHANNEL);
    
    Wdg_76_Acw_TriggerCount = WDG_76_ACW_ZERO;
    
    Dio_WriteChannel(WDG_76_ACW_DIO_TRIGGER_CHANNEL, STD_LOW);
    #if (WDG_76_ACW_DEV_ERROR_DETECT == STD_ON)
    Wdg_76_Acw_Status = WDG_76_ACW_EXPIRED;
    #endif /* (WDG_76_ACW_DEV_ERROR_DETECT == STD_ON) */
  }
}
#define WDG_76_ACW_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/
/* polyspace-end MISRA-C3:20.1 [Justified: Low] "see SWS_MemMap_00004 of AUTOSAR" */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
