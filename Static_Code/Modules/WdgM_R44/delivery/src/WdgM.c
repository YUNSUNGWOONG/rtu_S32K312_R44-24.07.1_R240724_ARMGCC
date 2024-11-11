/* polyspace +1 MISRA2012:1.1 [Not a Defect:Low] "Macro definitions are needed for performance and file size" */
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
**  SRC-MODULE: WdgM.c                                                        **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR WDGM                                                  **
**                                                                            **
**  PURPOSE   : Watchdog Manager API Functionality                            **
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
** 0.0.1     16-Sep-2019   ThanhNT      Initial version                       **
** 0.0.2     23-Sep-2019   ThanhNT      Fixbug on SetMode function            **
** 0.0.3     15-Oct-2019   ThanhNT      Update module version information     **
** 0.0.4     24-Oct-2019   ThanhNT      Update coding convention              **
** 0.0.5     24-Oct-2019   ThanhNT      Update version checking mechanism     **
** 0.0.6     12-Nov-2019   ThanhNT      Add Deactivated state checking in APIs**
** 0.0.7     21-Nov-2019   ThanhNT      Update SUD and SRS Ids                **
** 0.0.8     27-Nov-2019   ThanhNT      Fix misra warning                     **
** 0.0.9     05-Dec-2019   ThanhNT      Update Implementation of              **
**                                      WdgM_FirstExpiredSEID and             **
**                                      WdgM_InvFirstExpiredSEID (#refs: 9572)**
** 0.0.10     26-Dec-2019   ThanhNT     Fix function shall return if          **
**                                      WDGM_OFF_MODE_ENABLE is STD_OFF and   **
**                                      there is WDGIF_OFF_MODE configured    **
**                                      (#refs: 9736)                         **
** 0.0.11    30-Dec-2019   ThanhNT      Fix WdgM_Init doesn't change Local    **
**                                      Status of SEs to Deactivated          **
**                                      (#refs: 10393)                        **
** 0.0.13   03-Feb-2020    ThanhNT      Fix parameters validation shall be    **
**                                      checked regardless of                 **
**                                      WDGM_DEV_ERROR_DETECT (#refs: 10695)  **
** 0.0.14   15-Feb-2020    ThanhNT      WdgM_SetMode should return E_NOT_OK   **
**                                      incase global supervision status is   **
**                                      not WDGM_GLOBAL_STATUS_OK and         **
**                                      WDGM_GLOBAL_STATUS_FAILED(refs: 11135)**
** 0.0.15    11-Mar-2020   TienVD       Update traceability                   **
** 0.0.16    26-Mar-2020   ThanhNT      Fix misra defect                      **
** 0.0.17    06-Aug-2020   ThanhNH5     Fix Runtime error report (#15137)     **
** 0.0.18    10-Sep-2020   ThanhNH5     Added multi core check   (#15674)     **
** 0.0.19    10-Sep-2020   ThanhNH5     Fixed wrong assignment                **
**                                     "setModeFailed == WDGM_FALSE;" (#15689)**
** 0.0.20    10-Sep-2020   ThanhNH5     Replace macro WDGM_CORE_INFO (#15739) **
** 0.0.21    11-Sep-2020   ThanhNH5     Fixed DEM configuration issue(#15741) **
** 0.0.22    12-Sep-2020   LanBT        Update to use common internal function**
**                                      and macro signature with coreId in    **
**                                      prama (#15485)                        **
** 0.0.23    12-Sep-2020   LanBT        To remove WdgM_PtrConfig global       **
**                                      variable and use locally only (#15485)**
** 0.0.24    14-Sep-2020   ThanhNH5     Removed Workaround comments (#15690)  **
** 0.0.25    16-Sep-2020   ThanhNH5     Added DeInit time out for each core   **
**                                      (#15843)                              **
** 0.0.26    22-Sep-2020   ThanhNH5     Removed compiled warnings (#15944)    **
** 0.0.27    23-Sep-2020   ThanhNH5     Support InitMode for all cores        **
**                                      (#15709)                              **
** 0.0.28    25-Sep-2020   ThanhNH5     Fixed compile warning (#15969)        **
** 0.0.29    05-Oct-2020   ThanhNH5     Merge variables in single and         **
**                                      multi core (#15485)                   **
** 0.0.30    16-Oct-2020   ThanhNT      Update MemMap ASIL_D (#16306)         **
** 0.0.31    16-Oct-2020   ThanhNT      Update global variables multicore     **
**                                      (#16286)                              **
** 0.0.32    30-Oct-2020   ThanhNH5     Updated Exclusive areas (#16306)      **
** 1.0.2     22-Mar-2021   HiepVT1      Changed code to use Det_ReportError() **
**                                      replace for Det_ReportRuntimeError()  **
**                                      dependent on the DET version(#18339)  **
**                                      and update trace                      **
** 1.3.0.1   30-Jun-2022   TriBD        #CP44-322                             **
** 1.3.1.0   08-Aug-2022   TriBD        #CP44-385                             **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-begin MISRA-C3:20.1 [Not a defect:Low] "see SWS_MemMap_00003 of AUTOSAR" */
/* polyspace-begin DEFECT:DEAD_CODE MISRA2012:2.1,14.3 [Not a defect:Low] "The coreID got from OS side and could be updated in the runtime environment" */
/* polyspace-begin MISRA-C3:8.3 [Not a defect:Low] "Parameter names is generated by Rte incorrect" */
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "WdgM.h"               /* WdgM module header file */
#include "WdgM_IntFunc.h"       /* WdgM internal function prototype */
#include "WdgM_Ram.h"           /* WdgM module header file */
#include "SchM_WdgM.h"          /* SchM Header file */
#include "WdgM_Cores.h"         /* WdgM cores header file */
#if(WDGM_IMMEDIATE_RESET == STD_ON)
#include "Mcu.h"                /* Mcu Header file */
#endif
#include "Det.h"                /* Det Header file */

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/*******************************************************************************
**                      File version check                                    **
*******************************************************************************/

/*******************************************************************************
**                       Function Definitions                                 **
*******************************************************************************/
/*******************************************************************************
** Function Name      : WdgM_Init                                             **
**                                                                            **
** Service ID         : 0x00                                                  **
**                                                                            **
** Description        : This service performs initialization of WdgM          **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : ConfigPtr : Pointer to post-build configuration data  **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : None                                                  **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                      WdgM_CurrentMode,                                     **
**                      WdgM_PtrConfig,                                       **
**                      WdgM_GlobalSupervisionStatus,                         **
**                      WdgM_InvGlobalSupervisionStatus                       **
**                      WdgM_SEStatus,                                        **
**                      WdgM_TotalSEs                                         **
**                                                                            **
**                      Function(s) invoked :                                 **
**                      Det_ReportError,                                      **
**                      WdgM_InternalSetMode,                                 **
**                      WdgM_ClearActivityFlag,                               **
**                      WdgM_TriggerWdgIf,                                    **
**                      Dem_SetEventStatus,                                   **
**                      Mcu_PerformReset,                                     **
**                      WdgM_ValidateConfig                                   **
*******************************************************************************/
/* @Trace: SRS_BSW_00171 SRS_WdgM_CUS_00013 SRS_ModeMgm_09110 SRS_ModeMgm_09169 SRS_BSW_00339 SRS_ModeMgm_09159 SRS_ModeMgm_09107  SRS_ModeMgm_09221 SRS_ModeMgm_09222 SRS_WdgM_CUS_00007 SRS_BSW_00323 SRS_BSW_00310 SRS_BSW_00358  SRS_ModeMgm_09109 SRS_WdgM_CUS_00012 */
#define WDGM_START_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"
FUNC(void, WDGM_CODE) WdgM_Init(
  P2CONST(WdgM_ConfigType, WDGM_CONST, WDGM_CONST)ConfigPtr
)
{
  P2CONST(WdgM_ModePropertyType, AUTOMATIC, WDGM_CONST) ptrInitMode;
  P2CONST(WdgM_ActiveSEType, AUTOMATIC, WDGM_CONST) ptrInitModeLocalStatus;
  P2CONST(WdgM_ModePropertyType, AUTOMATIC, WDGM_CONST) ptrOtherMode;
  P2CONST(WdgM_ActiveSEType, AUTOMATIC, WDGM_CONST) ptrOtherModeLocalStatus;
  P2CONST(WdgM_ActiveSEType, AUTOMATIC, WDGM_CONST) ptrActiveSE;
  VAR(WdgM_SupervisedEntityIndexType, AUTOMATIC) counterActiveSE;
  VAR(uint8, AUTOMATIC) seStatus;
  #if (WDGM_TOTAL_CORES > WDGM_ONE)
  VAR(Std_ReturnType, AUTOMATIC) resultStatus;
  #endif
  #if((WDGM_OFF_MODE_ENABLED == STD_OFF) && (WDGM_ENABLE_TRIGGER == STD_ON))
  VAR(Std_ReturnType, AUTOMATIC) offModeValidationStatus;
  #endif
  #if(WDGM_ENABLE_TRIGGER == STD_ON)
  VAR(boolean, AUTOMATIC) setModeFailed;
  #endif

  VAR(WdgM_CoreIdType, AUTOMATIC) coreId;
  P2CONST(WdgM_ConfigType, AUTOMATIC, CONST) WdgM_PtrConfig;
  VAR(WdgM_ModeType, AUTOMATIC) initialMode;
  P2VAR(WdgM_GlobalStatusType, AUTOMATIC, WDGM_APPL_DATA) ptrGlobalSupervisionStatus;
  P2VAR(WdgM_GlobalStatusType, AUTOMATIC, WDGM_APPL_DATA) ptrInvGlobalSupervisionStatus;
  VAR(WdgM_ModeType, AUTOMATIC) modeCounter;
  VAR(WdgM_ModeType, AUTOMATIC) totalMode;

  /* Get core index*/
  /* @Trace: SafeWdgM_SUD_API_023 */
  #if (WDGM_TOTAL_CORES == WDGM_ONE)
  (void)WdgM_GetCoreIndex(&coreId);
  #else
  resultStatus = WdgM_GetCoreIndex(&coreId);
  if (resultStatus == E_OK)
  #endif
  {
    /* @Trace: SafeWdgM_SUD_API_024 */
    ptrGlobalSupervisionStatus = WDGM_GET_GLOBAL_SUPERVISION_STATUS_PTR(coreId);
    ptrInvGlobalSupervisionStatus = WDGM_GET_INV_GLOBAL_SUPERVISION_STATUS_PTR(coreId);
    /* Check for module status */
    /* Check Global Platform when coreId is MasterCore and check Global Status in case other Cores*/
    if (
      #if (WDGM_TOTAL_CORES > WDGM_ONE)
        (WDGM_MASTER_CORE_ID == coreId) && 
      #endif
        ((WDGM_GLOBAL_STATUS_DEACTIVATED != WdgM_PlatformGlobalSupervisionStatus) ||
        (WDGM_GLOBAL_STATUS_DEACTIVATED != *ptrGlobalSupervisionStatus))
        )
    {
      #if (WDGM_DEV_ERROR_DETECT == STD_ON)
      /* Report error to Det in case WdgM has already initialized */
      (void)Det_ReportError(WDGM_MODULE_ID, coreId,
          WDGM_INIT_SID, WDGM_E_NO_DEINIT);
      #endif
    }
    #if (WDGM_TOTAL_CORES > WDGM_ONE)
    else if ((WDGM_MASTER_CORE_ID != coreId) && 
              (WDGM_GLOBAL_STATUS_DEACTIVATED != *ptrGlobalSupervisionStatus))
    {
      #if (WDGM_DEV_ERROR_DETECT == STD_ON)
      /* Report error to Det in case WdgM has already initialized */
      (void)Det_ReportError(WDGM_MODULE_ID, coreId,
          WDGM_INIT_SID, WDGM_E_NO_DEINIT);
      #endif
    }
    else if ((WDGM_MASTER_CORE_ID != coreId) && 
              (WDGM_GLOBAL_STATUS_DEACTIVATED == WdgM_PlatformGlobalSupervisionStatus))
    {
      /* Master core must be initialised first before 
         other cores can be initialised */
      #if (WDGM_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError(WDGM_MODULE_ID, coreId,
        WDGM_INIT_SID, WDGM_E_UNINIT);
      #endif
    }
    #endif /* end (WDGM_TOTAL_CORES > WDGM_ONE) */
    else
    {
      /* @Trace: SafeWdgM_SUD_API_025 */
      WDGM_UNUSED_PTR(ConfigPtr);
      /* Local pointer to WdgM_ConfigType */
      WdgM_PtrConfig = GET_CONFIG_PTR(coreId);
      totalMode = WdgM_PtrConfig->TotalMode;
      /* Get the initial mode of WdgM */
      initialMode = WdgM_PtrConfig->InitialMode;
      WDGM_WRITE_CURRENT_MODE(coreId,initialMode);
      /* Get the pointer to Init mode array */
      ptrInitMode = &(WdgM_PtrConfig->PtrModes[initialMode]);

      #if((WDGM_OFF_MODE_ENABLED == STD_OFF) && (WDGM_ENABLE_TRIGGER == STD_ON))
      offModeValidationStatus = WdgM_ValidateOffMode(ptrInitMode, \
                  coreId, WDGM_INIT_SID);
      if (offModeValidationStatus == E_OK)
      #endif /* if((WDGM_OFF_MODE_ENABLED == STD_OFF) && (WDGM_ENABLE_TRIGGER == STD_ON)) */
      {
        /* @Trace: SafeWdgM_SUD_API_026 */
        /* Clear the Global supervision status */
        *ptrGlobalSupervisionStatus = WDGM_GLOBAL_STATUS_DEACTIVATED;
        *ptrInvGlobalSupervisionStatus = ~(*ptrGlobalSupervisionStatus);
        
        ptrInitModeLocalStatus = ptrInitMode->PtrActiveSEList;
        /* Get the total SE's in the Init mode */
        counterActiveSE = WDGM_ZERO;
        while (counterActiveSE
          < (WdgM_SupervisedEntityIndexType)ptrInitMode->TotalSEInMode)
        {
          seStatus = WDGM_READ_SE_STATUS(ptrInitModeLocalStatus[counterActiveSE].SEArrayIndex);
          /* If SE is active in Init mode, then check for current status of SE */
          if (((seStatus & WDGM_LOCAL_STATUS_DEACTIVATED) == WDGM_LOCAL_STATUS_DEACTIVATED) ||
            ((seStatus & WDGM_LOCAL_STATUS_FAILED) == WDGM_LOCAL_STATUS_OK))
          {
            /* Activate the SE present in the Init mode */
            WDGM_WRITE_SE_STATUS(ptrInitModeLocalStatus[counterActiveSE].SEArrayIndex, 
              (WDGM_CLEAR_STATUS | WDGM_SET_ALLSUPVSN_CORRECT | WDGM_LOCAL_STATUS_OK));
          }
          else
          {
            WDGM_WRITE_SE_STATUS(ptrInitModeLocalStatus[counterActiveSE].SEArrayIndex, 
              (WDGM_CLEAR_STATUS | WDGM_SET_ALLSUPVSN_CORRECT | WDGM_LOCAL_STATUS_DEACTIVATED));
          }
          /* Increment the SEs loop count */
          counterActiveSE++;
        }
        
        /* @Trace: SafeWdgM_SUD_API_064 */
        /* Set Local Status of SEs to WDGM_LOCAL_STATUS_DEACTIVATED */
        modeCounter = WDGM_ZERO;
        while (modeCounter < totalMode)
        {
          counterActiveSE = WDGM_ZERO;
          ptrOtherMode = &(WdgM_PtrConfig->PtrModes[modeCounter]);
          ptrOtherModeLocalStatus = ptrOtherMode->PtrActiveSEList;
          if (ptrOtherMode != ptrInitMode)
          {
            while(counterActiveSE 
              < (WdgM_SupervisedEntityIndexType)ptrOtherMode->TotalSEInMode)
            {
              ptrActiveSE = WdgM_SEIDBinarySearch(coreId, 
                              ptrOtherModeLocalStatus[counterActiveSE].SEId);
              if (ptrActiveSE == NULL_PTR)
              {
                WDGM_WRITE_SE_STATUS(ptrOtherModeLocalStatus[counterActiveSE].SEArrayIndex,
                  (WDGM_CLEAR_STATUS | WDGM_SET_ALLSUPVSN_CORRECT | WDGM_LOCAL_STATUS_DEACTIVATED));
              }
              counterActiveSE++;
            }
          }
          modeCounter++;
        }
        
        /* Establish the hardware watchdog modes */
        #if(WDGM_ENABLE_TRIGGER == STD_ON)
        setModeFailed = WdgM_InternalSetMode(coreId, initialMode);
        if (setModeFailed == WDGM_TRUE)
        {
          /* @Trace: SafeWdgM_SUD_API_028 */
          /* Update Global Supervision Status */
          *ptrGlobalSupervisionStatus = WDGM_GLOBAL_STATUS_STOPPED;
          *ptrInvGlobalSupervisionStatus = ~(*ptrGlobalSupervisionStatus);
          
          #if (WDGM_TOTAL_CORES > WDGM_ONE)
          if (WDGM_MASTER_CORE_ID == coreId)
          #endif
          {
            WdgM_PlatformGlobalSupervisionStatus = WDGM_GLOBAL_STATUS_STOPPED;
            WdgM_InvPlatformGlobalSupervisionStatus = ~WdgM_PlatformGlobalSupervisionStatus;
          }
          
          #if(WDGM_DEM_ERROR_REPORT == STD_ON)
          if (WdgM_PtrConfig->DemEventParam.ESetModeEnable == WDGM_TRUE)
          {
            (void)Dem_SetEventStatus(WdgM_PtrConfig->DemEventParam.ESetMode, DEM_EVENT_STATUS_FAILED);
          }
          #if(WDGM_DEM_STOPPED_SUPERVISION_REPORT == STD_ON)
          if (WdgM_PtrConfig->DemEventParam.ESupervisionEnable == WDGM_TRUE)
          {
            (void)Dem_SetEventStatus(WdgM_PtrConfig->DemEventParam.ESupervision, DEM_EVENT_STATUS_FAILED);
          }
          #endif
          #endif
          #if(WDGM_IMMEDIATE_RESET == STD_ON)
          Mcu_PerformReset();
          #endif
          WdgM_TriggerWdgIf(coreId, ptrInitMode, WDGM_TM_TIMEOUT);
        }
        else
        #endif /* if(WDGM_ENABLE_TRIGGER == STD_ON) */
        {
          /* @Trace: SafeWdgM_SUD_API_027 */
          WdgM_ClearActivityFlag(coreId, ptrInitMode);
          
          /* Clear the expired supervision cycle counter */
          WDGM_WRITE_EXP_SUPERVISION_CYCLE_COUNTER(coreId, WDGM_ZERO);

          /* Set Global Supervision Status */
          *ptrGlobalSupervisionStatus = WDGM_GLOBAL_STATUS_OK;
          *ptrInvGlobalSupervisionStatus = ~(*ptrGlobalSupervisionStatus);
          
          #if (WDGM_TOTAL_CORES > WDGM_ONE)
          if (WDGM_MASTER_CORE_ID == coreId)
          #endif
          {
            WdgM_PlatformGlobalSupervisionStatus = WDGM_GLOBAL_STATUS_OK;
            WdgM_InvPlatformGlobalSupervisionStatus = ~WdgM_PlatformGlobalSupervisionStatus;
            /* Reset the expired bit to indicate that no SE is in
              WDGM_LOCAL_STATUS_EXPIRED status */
            WdgM_FirstExpSEIDStatus = WDGM_FALSE;
            /* Set the NON-Initialized RAM area for storing expired SEID values to
              WDGM_ZERO */
            WdgM_FirstExpiredSEID = WDGM_ZERO;
            WdgM_InvFirstExpiredSEID = ~WdgM_FirstExpiredSEID;
          }
          
          #if(WDGM_ENABLE_TRIGGER == STD_ON)
          WdgM_TriggerWdgIf(coreId, ptrInitMode, WDGM_TM_NORMAL);
          #endif
        }
      }
    }
  }
  #if (WDGM_TOTAL_CORES > WDGM_ONE)
  else
  {
	#if (((DET_AR_RELEASE_MAJOR_VERSION == 0x04)&&(DET_AR_RELEASE_MINOR_VERSION >= 0x02))|| \
	  (DET_AR_RELEASE_MAJOR_VERSION > 0x04))
    /* Report runtime error to Det in case invalid core id*/
    (void)Det_ReportRuntimeError(WDGM_MODULE_ID, coreId,
        WDGM_INIT_SID, WDGM_E_COREINACTIVATED);
	#else
	#if(WDGM_DEV_ERROR_DETECT == STD_ON)
	/* Report error to Det in case invalid core id*/
    (void)Det_ReportError(WDGM_MODULE_ID, coreId,
        WDGM_INIT_SID, WDGM_E_COREINACTIVATED);	
	#endif
	#endif
  }
  #endif
}
#define WDGM_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"

/*******************************************************************************
** Function Name      : WdgM_DeInit                                           **
**                                                                            **
** Service ID         : 0x01                                                  **
**                                                                            **
** Description        : This service performs Deinitialization of WdgM        **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : None                                                  **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : None                                                  **
**                                                                            **
** Preconditions      : Watchdog Manager should be initialized                **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                      WdgM_GlobalSupervisionStatus,                         **
**                      WdgM_InvGlobalSupervisionStatus                       **
**                      WdgM_PtrConfig,                                       **
**                      WdgM_CurrentMode                                      **
**                                                                            **
**                      Function(s) invoked :                                 **
**                      Det_ReportError,                                      **
**                      WdgM_TriggerWdgIf                                     **
*******************************************************************************/
/* @Trace: SRS_BSW_00171 SRS_WdgM_CUS_00013 SRS_BSW_00310 SRS_BSW_00336 SRS_BSW_00323  */
#define WDGM_START_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"
FUNC(void, WDGM_CODE) WdgM_DeInit(void)
{

#if(WDGM_ENABLE_TRIGGER == STD_ON)
  /* Get the pointer to current mode */
  P2CONST(WdgM_ModePropertyType, AUTOMATIC, WDGM_CONST)ptrCurrentMode;
  P2CONST(WdgM_ConfigType, AUTOMATIC, CONST) WdgM_PtrConfig;
#endif
  VAR(WdgM_CoreIdType, AUTOMATIC) coreId;
  VAR(Std_ReturnType, AUTOMATIC) resultStatus;
  P2VAR(WdgM_GlobalStatusType, AUTOMATIC, WDGM_APPL_DATA) ptrGlobalSupervisionStatus;
  P2VAR(WdgM_GlobalStatusType, AUTOMATIC, WDGM_APPL_DATA) ptrInvGlobalSupervisionStatus;

  /* @Trace: SafeWdgM_SUD_API_001 */
  /* Get core index*/
  resultStatus = WdgM_GetCoreIndex(&coreId);
  #if (WDGM_TOTAL_CORES > WDGM_ONE)
  if (resultStatus == E_OK)
  #endif
  {
    /* @Trace: SafeWdgM_SUD_API_002 */
    ptrGlobalSupervisionStatus = WDGM_GET_GLOBAL_SUPERVISION_STATUS_PTR(coreId);
    ptrInvGlobalSupervisionStatus = WDGM_GET_INV_GLOBAL_SUPERVISION_STATUS_PTR(coreId);
    /* Det Check for module initialization*/
    if ((WDGM_MASTER_CORE_ID == coreId) &&
        (WDGM_GLOBAL_STATUS_DEACTIVATED == WdgM_PlatformGlobalSupervisionStatus) &&
        (WDGM_GLOBAL_STATUS_DEACTIVATED == *ptrGlobalSupervisionStatus))
    {
      #if(WDGM_DEV_ERROR_DETECT == STD_ON)
      /* Report to DET  */
      (void)Det_ReportError(WDGM_MODULE_ID, coreId,
        WDGM_DEINIT_SID, WDGM_E_UNINIT);
      #endif
      resultStatus = E_NOT_OK;
    }
    /* @Trace: SafeWdgM_SUD_API_003 */
    #if (WDGM_TOTAL_CORES > WDGM_ONE)
    
    else if ((WDGM_MASTER_CORE_ID != coreId) &&
            (WDGM_GLOBAL_STATUS_DEACTIVATED == *ptrGlobalSupervisionStatus))
    {
      #if(WDGM_DEV_ERROR_DETECT == STD_ON)
      /* Report to DET  */
      (void)Det_ReportError(WDGM_MODULE_ID, coreId,
        WDGM_DEINIT_SID, WDGM_E_UNINIT);
      #endif
      resultStatus = E_NOT_OK;
    }
    #endif /* end (WDGM_TOTAL_CORES > WDGM_ONE) */
    else
    {
      /* To make polyspace happy */
    }
    if (resultStatus == E_OK)
    {
      /* Change global supervision status to DEACTIVATED */
      *ptrGlobalSupervisionStatus = WDGM_GLOBAL_STATUS_DEACTIVATED;
      *ptrInvGlobalSupervisionStatus = ~(*ptrGlobalSupervisionStatus);
      #if (WDGM_TOTAL_CORES > WDGM_ONE)
      if (WDGM_MASTER_CORE_ID == coreId)
      #endif
      {
        WdgM_PlatformGlobalSupervisionStatus = WDGM_GLOBAL_STATUS_DEACTIVATED;
        WdgM_InvPlatformGlobalSupervisionStatus = ~WdgM_PlatformGlobalSupervisionStatus;
      }
      
      #if(WDGM_ENABLE_TRIGGER == STD_ON)
      /* Local pointer to WdgM_ConfigType */
      WdgM_PtrConfig = GET_CONFIG_PTR(coreId);
      /* Get the address of currentMode from the Mode structure array into the
        global pointer */
      ptrCurrentMode = &(WdgM_PtrConfig->PtrModes[WDGM_READ_CURRENT_MODE(coreId)]);
      /* Trigger all the watchdogs which are not in OFFMODE to the timeout value
        configured  */
      WdgM_TriggerWdgIf(coreId, ptrCurrentMode, WDGM_TM_DEINIT);
      #endif
    }
  }
  #if (WDGM_TOTAL_CORES > WDGM_ONE)
  else
  {
	#if (((DET_AR_RELEASE_MAJOR_VERSION == 0x04)&&(DET_AR_RELEASE_MINOR_VERSION >= 0x02))|| \
	  (DET_AR_RELEASE_MAJOR_VERSION > 0x04))
    /* Report runtime error to Det in case invalid core id*/
    (void)Det_ReportRuntimeError(WDGM_MODULE_ID, coreId,
        WDGM_DEINIT_SID, WDGM_E_COREINACTIVATED);
	#else
	#if(WDGM_DEV_ERROR_DETECT == STD_ON)
	/* Report error to Det in case invalid core id*/
    (void)Det_ReportError(WDGM_MODULE_ID, coreId,
        WDGM_DEINIT_SID, WDGM_E_COREINACTIVATED);
	#endif
	#endif
  }
  #endif
}
#define WDGM_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"

#if(WDGM_VERSION_INFO_API == STD_ON)
/*******************************************************************************
** Function Name        : WdgM_GetVersionInfo                                 **
**                                                                            **
** Service ID           : 0x02                                                **
**                                                                            **
** Description          : This API reads the version information of WdgM      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : VersionInfo : Pointer to where to store the         **
**                                      information of the module WdgM        **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) : None                           **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Det_ReportError                                     **
*******************************************************************************/
/* @Trace: SRS_BSW_00171 SRS_WdgM_CUS_00013 SRS_WdgM_CUS_00013 SRS_BSW_00310 SRS_BSW_00323 */
#define WDGM_START_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"
FUNC(void, WDGM_CODE) WdgM_GetVersionInfo
  (P2VAR(Std_VersionInfoType, AUTOMATIC, WDGM_APPL_DATA) VersionInfo)
{
  VAR(WdgM_CoreIdType, AUTOMATIC) coreId;
  #if (WDGM_TOTAL_CORES > WDGM_ONE)
  VAR(Std_ReturnType, AUTOMATIC) coreIdxStatus;
  #endif
  /* Get core index*/
  /* @Trace: SafeWdgM_SUD_API_004 */
  #if (WDGM_TOTAL_CORES > WDGM_ONE)
  coreIdxStatus = WdgM_GetCoreIndex(&coreId);
  if (coreIdxStatus == E_OK)
  #else
  (void)WdgM_GetCoreIndex(&coreId);
  #endif
  {
    /* check NULL pointer */
    if (VersionInfo == NULL_PTR)
    {
      /* @Trace: SafeWdgM_SUD_API_006 */
      #if(WDGM_DEV_ERROR_DETECT == STD_ON)
      /* Report to DET */
      (void)Det_ReportError(WDGM_MODULE_ID, coreId,
        WDGM_GETVERSIONINFO_SID, WDGM_E_INV_POINTER);
      #endif
    }
    else
    {
      /* @Trace: SafeWdgM_SUD_API_005 */
      /* Load the vendor Id */
      /* polyspace-begin MISRA-C3:D4.14 [Not a defect:Low] "VersionInfo will be checked before using" */
      VersionInfo->vendorID = WDGM_VENDOR_ID;
      /* Load the module Id */
      VersionInfo->moduleID = WDGM_MODULE_ID;
      /* Load Software Major Version */
      VersionInfo->sw_major_version = WDGM_SW_MAJOR_VERSION;
      /* Load Software Minor Version */
      VersionInfo->sw_minor_version = WDGM_SW_MINOR_VERSION;
      /* Load Software Patch Version */
      VersionInfo->sw_patch_version = WDGM_SW_PATCH_VERSION;
      /* polyspace-end MISRA-C3:D4.14 */
    }
  }
  #if (WDGM_TOTAL_CORES > WDGM_ONE)
  else
  {
	#if (((DET_AR_RELEASE_MAJOR_VERSION == 0x04)&&(DET_AR_RELEASE_MINOR_VERSION >= 0x02))|| \
	  (DET_AR_RELEASE_MAJOR_VERSION > 0x04))
    /* Report runtime error to Det in case invalid core id*/
    (void)Det_ReportRuntimeError(WDGM_MODULE_ID, coreId,
        WDGM_GETVERSIONINFO_SID, WDGM_E_COREINACTIVATED);
	#else
	#if(WDGM_DEV_ERROR_DETECT == STD_ON)
	/* Report error to Det in case invalid core id*/
    (void)Det_ReportError(WDGM_MODULE_ID, coreId,
        WDGM_GETVERSIONINFO_SID, WDGM_E_COREINACTIVATED);
	#endif
	#endif
  }
  #endif
}
#define WDGM_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"
#endif /* (WDGM_VERSION_INFO_API == STD_ON) */

/*******************************************************************************
** Function Name        : WdgM_SetMode                                        **
**                                                                            **
** Service ID           : 0x03                                                **
**                                                                            **
** Description          : This service performs switching between different   **
**                        modes of WdgM                                       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : Mode : One of the configured WdgM modes             **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : E_OK: Successfull changed to the new mode           **
**                        E_NOT_OK: Changing to the new mode failed           **
**                                                                            **
** Preconditions        : Watchdog Manager should be initialized              **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                        WdgM_PtrConfig,                                     **
**                        WdgM_GlobalSupervisionStatus,                       **
**                        WdgM_InvGlobalSupervisionStatus                     **
**                        WdgM_SEStatus,                                      **
**                        WdgM_SupervisedEntity,                              **
**                        WdgM_CurrentMode,                                   **
**                        WdgM_FailedRefCycleCounter                          **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Det_ReportError,                                    **
**                        Dem_SetEventStatus,                                 **
**                        WdgM_InternalSetMode,                               **
**                        Mcu_PerformReset,                                   **
**                        Rte_Switch_globalMode_currentMode,                  **
**                        WdgM_TriggerWdgIf,                                  **
**                        WdgM_ClearActivityFlag,                             **
**                        PtrRteSwitchMode,                                   **
**                        SchM_Enter_WdgM_GLOBALSUPVSNSTATUS_PROTECTION,      **
**                        SchM_Exit_WdgM_GLOBALSUPVSNSTATUS_PROTECTION        **
*******************************************************************************/
/* @Trace: SRS_BSW_00357 SRS_BSW_00171 SRS_WdgM_CUS_00013 SRS_WdgM_CUS_00013 SRS_BSW_00310 SRS_ModeMgm_09110 SRS_BSW_00323 SRS_BSW_00406 SRS_ModeMgm_09109  SRS_ModeMgm_09158 SRS_ModeMgm_09169 SRS_BSW_00339 SRS_ModeMgm_09159   SRS_WdgM_CUS_00012 */
#define WDGM_START_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"
FUNC(Std_ReturnType, WDGM_CODE) WdgM_SetMode(
  VAR(WdgM_ModeType, AUTOMATIC) Mode
)
{
  P2CONST(WdgM_ModePropertyType, AUTOMATIC, WDGM_CONST) ptrNewMode;
  P2CONST(WdgM_ModePropertyType, AUTOMATIC, WDGM_CONST) ptrPrevMode;
  P2CONST(WdgM_ActiveSEType, AUTOMATIC, WDGM_CONST) ptrNewModeLocalStatus;
  P2CONST(WdgM_ActiveSEType, AUTOMATIC, WDGM_CONST) ptrPrevModeLocalStatus;
  /* Local variable for return value */
  VAR(Std_ReturnType, AUTOMATIC) returnValue;
  VAR(WdgM_SupervisedEntityIndexType, AUTOMATIC) supervisedEntityIdx;
  VAR(uint16, AUTOMATIC) newModeSECount;
  VAR(uint16, AUTOMATIC) prevModeSECount;
  VAR(boolean, AUTOMATIC) deactivateFlag;
  VAR(uint8, AUTOMATIC) seStatus;
  #if(WDGM_ENABLE_TRIGGER == STD_ON)
  VAR(boolean, AUTOMATIC) setModeFailed;
  P2VAR(WdgM_GlobalStatusType, AUTOMATIC, WDGM_APPL_DATA) ptrInvGlobalSupervisionStatus;
  #endif

  VAR(WdgM_CoreIdType, AUTOMATIC) coreId;
  P2CONST(WdgM_ConfigType, AUTOMATIC, CONST) WdgM_PtrConfig;
  P2VAR(WdgM_GlobalStatusType, AUTOMATIC, WDGM_APPL_DATA) ptrGlobalSupervisionStatus;
  VAR(WdgM_GlobalStatusType, AUTOMATIC) globalSupervisionStatus;

  /* @Trace: SafeWdgM_SUD_API_029 */
  /* Get core index*/
  returnValue = WdgM_GetCoreIndex(&coreId);
  
  #if (WDGM_TOTAL_CORES > WDGM_ONE)
  if (returnValue == E_OK)
  #endif
  {
    /* @Trace: SafeWdgM_SUD_API_030 */
    /* Local pointer to WdgM_ConfigType */
    WdgM_PtrConfig = GET_CONFIG_PTR(coreId);
    ptrGlobalSupervisionStatus = WDGM_GET_GLOBAL_SUPERVISION_STATUS_PTR(coreId);
    
    /* Store the current global status and uses for whole function */
    globalSupervisionStatus = *ptrGlobalSupervisionStatus;
    
    /* Det Check for module initialization*/
    if (WDGM_GLOBAL_STATUS_DEACTIVATED == globalSupervisionStatus)
    {
      #if (WDGM_DEV_ERROR_DETECT == STD_ON)
      /* Report to DET  */
      (void)Det_ReportError(WDGM_MODULE_ID, coreId,
        WDGM_SETMODE_SID, WDGM_E_UNINIT);
      #endif
      returnValue = E_NOT_OK;
    }
    else if (Mode >= WdgM_PtrConfig->TotalMode)
    {
      /* Check for Mode is correct */
      #if (WDGM_DEV_ERROR_DETECT == STD_ON)
      /* Report to DET  */
      (void)Det_ReportError(WDGM_MODULE_ID, coreId,
        WDGM_SETMODE_SID, WDGM_E_PARAM_MODE);
      #endif
      returnValue = E_NOT_OK;
    }
    else
    {
      /* @Trace: SafeWdgM_SUD_API_031 */
      /* Is OFFMODE Disabled */
      #if((WDGM_OFF_MODE_ENABLED == STD_OFF) && (WDGM_ENABLE_TRIGGER == STD_ON))
      /* To prevent accessing from invalid array index */
      returnValue = WdgM_ValidateOffMode(&(WdgM_PtrConfig->PtrModes[Mode]), \
                      coreId, WDGM_SETMODE_SID);
        /* Check the return value */
      if (returnValue == E_OK)
      #endif /* #if((WDGM_OFF_MODE_ENABLED == STD_OFF)
        && (WDGM_ENABLE_TRIGGER == STD_ON)) */
      {
        ptrNewMode = &(WdgM_PtrConfig->PtrModes[Mode]);

        /* Check if Global Status is WDGM_GLOBAL_STATUS_OK or
          WDGM_GLOBAL_STATUS_FAILED */
        if ((WDGM_GLOBAL_STATUS_OK == globalSupervisionStatus) ||
          (WDGM_GLOBAL_STATUS_FAILED == globalSupervisionStatus))
        {
          /* @Trace: SafeWdgM_SUD_API_032 */
          #if(WDGM_ENABLE_TRIGGER == STD_ON)
          /* Establish the hardware watchdog modes */
          setModeFailed = WdgM_InternalSetMode(coreId, Mode);
          if (setModeFailed == WDGM_TRUE)
          {
            SchM_Enter_WdgM_GLOBALSUPVSNSTATUS_PROTECTION();
            
            /* Update Global supervision */
            ptrInvGlobalSupervisionStatus = WDGM_GET_INV_GLOBAL_SUPERVISION_STATUS_PTR(coreId);
            *ptrGlobalSupervisionStatus = WDGM_GLOBAL_STATUS_STOPPED;
            *ptrInvGlobalSupervisionStatus = ~(*ptrGlobalSupervisionStatus);
            #if (WDGM_TOTAL_CORES > WDGM_ONE)
            if (coreId == WDGM_MASTER_CORE_ID)
            #endif
            {
              /* WDGM_GLOBAL_STATUS_STOPPED is the most serverity of WdgM Module.
              In case of master core, when global supervision status switches to 
              WDGM_GLOBAL_STATUS_STOPPED then we can know for sure that WdgM will 
              have the most severity. Platform Global Supervision Status shall swich
              to WDGM_GLOBAL_STATUS_STOPPED immediately. */
              WdgM_PlatformGlobalSupervisionStatus = WDGM_GLOBAL_STATUS_STOPPED;
              WdgM_InvPlatformGlobalSupervisionStatus = ~WdgM_PlatformGlobalSupervisionStatus;
            }
            SchM_Exit_WdgM_GLOBALSUPVSNSTATUS_PROTECTION();
            #if(WDGM_DEM_ERROR_REPORT == STD_ON)
            if (WdgM_PtrConfig->DemEventParam.ESetModeEnable == WDGM_TRUE)
            {
              (void)Dem_SetEventStatus(WdgM_PtrConfig->DemEventParam.ESetMode, DEM_EVENT_STATUS_FAILED);
            }
            #if(WDGM_DEM_STOPPED_SUPERVISION_REPORT == STD_ON)
            if (WdgM_PtrConfig->DemEventParam.ESupervisionEnable == WDGM_TRUE)
            {
              (void)Dem_SetEventStatus(WdgM_PtrConfig->DemEventParam.ESupervision, DEM_EVENT_STATUS_FAILED);
            }
            #endif
            #endif
            #if(WDGM_IMMEDIATE_RESET == STD_ON)
            Mcu_PerformReset();
            #else
            (void)Rte_Switch_globalMode_currentMode(WDGM_GLOBAL_STATUS_STOPPED);
            #endif
            WdgM_TriggerWdgIf(coreId, ptrNewMode, WDGM_TM_TIMEOUT);
            returnValue = E_NOT_OK;
          }
          else
          #endif
          {
            /* @Trace: SafeWdgM_SUD_API_033 */
            /* Clear activity flags for all logical supervisions */
            WdgM_ClearActivityFlag(coreId, ptrNewMode);

            /* Get the total SE's in the new mode */
            newModeSECount = WDGM_ZERO;
            /* Get the pointer to WdgM_GaaModexLocalStatus */
            ptrNewModeLocalStatus = ptrNewMode->PtrActiveSEList;
            while (newModeSECount < ptrNewMode->TotalSEInMode)
            {
              supervisedEntityIdx
                = ptrNewModeLocalStatus[newModeSECount].SEArrayIndex;
              
              SchM_Enter_WdgM_GLOBALSUPVSNSTATUS_PROTECTION();
              seStatus = WDGM_READ_SE_STATUS(supervisedEntityIdx);
              /* Check if the SE in new mode was not activated in old mode */
              if ((seStatus & WDGM_STATUS_MASK) == WDGM_LOCAL_STATUS_DEACTIVATED)
              {
                /* Activate the SE present in the new mode */
                WDGM_WRITE_SE_STATUS(supervisedEntityIdx,
                  (seStatus & WDGM_CLEAR_SE) | WDGM_LOCAL_STATUS_OK);

                SchM_Exit_WdgM_GLOBALSUPVSNSTATUS_PROTECTION();
                (void)(WdgM_SupervisedEntity[supervisedEntityIdx].PtrRteSwitchMode)
                  (WDGM_LOCAL_STATUS_OK);
              }
              else
              {
                SchM_Exit_WdgM_GLOBALSUPVSNSTATUS_PROTECTION();
              }
              /* Increment the SEs loop count */
              newModeSECount++;
            }
            
            /* @Trace: SafeWdgM_SUD_API_034 */
            /* Get the pointer to previous mode array */
            ptrPrevMode = &(WdgM_PtrConfig->PtrModes[WDGM_READ_CURRENT_MODE(coreId)]);
            /* Get the total SE's in the previous mode */
            prevModeSECount = WDGM_ZERO;
            /* Get the pointer to WdgM_GaaModexLocalStatus */
            ptrPrevModeLocalStatus = ptrPrevMode->PtrActiveSEList;
            while (prevModeSECount < ptrPrevMode->TotalSEInMode)
            {
              deactivateFlag = WDGM_TRUE;
              /* Get the pointer to WdgM_GaaModexLocalStatus */
              ptrNewModeLocalStatus = ptrNewMode->PtrActiveSEList;
              /* Get the total SE's in the new mode */
              newModeSECount = WDGM_ZERO;
              while (newModeSECount < ptrNewMode->TotalSEInMode)
              {
                /* Check if the SE in previous mode is not activated in new mode */
                if ((ptrPrevModeLocalStatus[prevModeSECount].SEArrayIndex)
                  == (ptrNewModeLocalStatus[newModeSECount].SEArrayIndex))
                {
                  deactivateFlag = WDGM_FALSE;
                  newModeSECount = ptrNewMode->TotalSEInMode;
                }
                else
                {
                  /* Increment the SEs loop count */
                  newModeSECount++;
                }
              }

              /* Deactivate if SE not activated in new mode */
              if (deactivateFlag == WDGM_TRUE)
              {
                supervisedEntityIdx
                  = ptrPrevModeLocalStatus[prevModeSECount].SEArrayIndex;
                
                SchM_Enter_WdgM_GLOBALSUPVSNSTATUS_PROTECTION();
                seStatus = WDGM_READ_SE_STATUS(supervisedEntityIdx);
                /* De-Activate the SE not present in the new mode */
                WDGM_WRITE_SE_STATUS(supervisedEntityIdx,
                  ((seStatus & WDGM_CLEAR_SE)
                  | WDGM_SET_ALLSUPVSN_CORRECT) | WDGM_LOCAL_STATUS_DEACTIVATED);
                #if(WDGM_ENABLE_ALIVE_SUPERVISION == STD_ON)
                /* Reset failure cycle counter */
                *(WdgM_FailedRefCycleCounter[supervisedEntityIdx]) = WDGM_ZERO;
                #endif
                SchM_Exit_WdgM_GLOBALSUPVSNSTATUS_PROTECTION();
                (void)(WdgM_SupervisedEntity[supervisedEntityIdx].PtrRteSwitchMode)
                  (WDGM_LOCAL_STATUS_DEACTIVATED);
              }
              prevModeSECount++;
            }
            /* @Trace: SafeWdgM_SUD_API_035 */
            SchM_Enter_WdgM_GLOBALSUPVSNSTATUS_PROTECTION();
            
            WDGM_WRITE_CURRENT_MODE(coreId, Mode);
            
            SchM_Exit_WdgM_GLOBALSUPVSNSTATUS_PROTECTION();
            
            #if(WDGM_ENABLE_TRIGGER == STD_ON)
            WdgM_TriggerWdgIf(coreId, ptrNewMode, WDGM_TM_NORMAL);
            #endif
          }
        }
        else
        {
          returnValue = E_NOT_OK;
        }
      }
    }
  }
  #if (WDGM_TOTAL_CORES > WDGM_ONE)
  else
  {
	#if (((DET_AR_RELEASE_MAJOR_VERSION == 0x04)&&(DET_AR_RELEASE_MINOR_VERSION >= 0x02))|| \
	  (DET_AR_RELEASE_MAJOR_VERSION > 0x04))
    /* Report runtime error to Det in case invalid core id*/
    (void)Det_ReportRuntimeError(WDGM_MODULE_ID, coreId,
        WDGM_SETMODE_SID, WDGM_E_COREINACTIVATED);
	#else
	#if(WDGM_DEV_ERROR_DETECT == STD_ON)
	/* Report error to Det in case invalid core id*/
    (void)Det_ReportError(WDGM_MODULE_ID, coreId,
        WDGM_SETMODE_SID, WDGM_E_COREINACTIVATED);
	#endif
	#endif
  }
  #endif
  return (returnValue);
}
#define WDGM_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"

/*******************************************************************************
** Function Name        : WdgM_GetMode                                        **
**                                                                            **
** Service ID           : 0x0b                                                **
**                                                                            **
** Description          : This service Returns the current mode of WdgM       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : Mode : Current mode of the WdgM                     **
**                                                                            **
** Return parameter     : E_OK: Current mode successfully returned            **
**                        E_NOT_OK: Returning current mode failed             **
**                                                                            **
** Preconditions        : Watchdog Manager should be initialized              **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                        WdgM_CurrentMode,                                   **
**                        WdgM_GlobalSupervisionStatus                        **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Det_ReportError,                                    **
**                        SchM_Enter_WdgM_GLOBALSUPVSNSTATUS_PROTECTION,      **
**                        SchM_Exit_WdgM_GLOBALSUPVSNSTATUS_PROTECTION        **
*******************************************************************************/
/* @Trace: SRS_BSW_00357 SRS_BSW_00171 SRS_WdgM_CUS_00013 SRS_BSW_00310 SRS_BSW_00323 */
#define WDGM_START_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"
FUNC(Std_ReturnType, WDGM_CODE) WdgM_GetMode(
  P2VAR(WdgM_ModeType, WDGM_DATA, WDGM_APPL_DATA) Mode
)
{
  /* Local variable for return value */
  VAR(Std_ReturnType, AUTOMATIC) returnValue;
  VAR(WdgM_CoreIdType, AUTOMATIC) coreId;
  P2VAR(WdgM_GlobalStatusType, AUTOMATIC, WDGM_APPL_DATA) ptrGlobalSupervisionStatus;
  
  /* @Trace: SafeWdgM_SUD_API_007 */
  /* Get core index*/
  returnValue = WdgM_GetCoreIndex(&coreId);

  #if (WDGM_TOTAL_CORES > WDGM_ONE)
  if (returnValue == E_OK)
  #endif
  {
    /* @Trace: SafeWdgM_SUD_API_008 */
    ptrGlobalSupervisionStatus = WDGM_GET_GLOBAL_SUPERVISION_STATUS_PTR(coreId);
    /* Det Check for module initialization*/
    if (WDGM_GLOBAL_STATUS_DEACTIVATED == *ptrGlobalSupervisionStatus)
    {
      #if (WDGM_DEV_ERROR_DETECT == STD_ON)
      /* Report to DET  */
      (void)Det_ReportError(WDGM_MODULE_ID, coreId,
        WDGM_GETMODE_SID, WDGM_E_UNINIT);
      /* Set return value to E_NOT_OK */
      #endif
      returnValue = E_NOT_OK;
    }
    /* Det Check for NULL pointer */
    if (Mode == NULL_PTR)
    {
      #if (WDGM_DEV_ERROR_DETECT == STD_ON)
      /* Report to DET  */
      (void)Det_ReportError(WDGM_MODULE_ID, coreId,
        WDGM_GETMODE_SID, WDGM_E_INV_POINTER);
      #endif /* #if (WDGM_DEV_ERROR_DETECT == STD_ON) */
      /* Set return value to E_NOT_OK */
      returnValue = E_NOT_OK;
    }
    /* @Trace: SafeWdgM_SUD_API_009 */
    /* Check the return value */
    if (returnValue == E_OK)
    {
      SchM_Enter_WdgM_GLOBALSUPVSNSTATUS_PROTECTION();
      /* polyspace-begin MISRA-C3:D4.14 [Not a defect:Low] "Mode will be checked before using" */
      /* Store the current mode into provided pointer */
      *Mode = WDGM_READ_CURRENT_MODE(coreId);
      /* polyspace-end MISRA-C3:D4.14 */
      SchM_Exit_WdgM_GLOBALSUPVSNSTATUS_PROTECTION();
    }
  }
  #if (WDGM_TOTAL_CORES > WDGM_ONE)
  else
  {
	#if (((DET_AR_RELEASE_MAJOR_VERSION == 0x04)&&(DET_AR_RELEASE_MINOR_VERSION >= 0x02))|| \
	  (DET_AR_RELEASE_MAJOR_VERSION > 0x04))
    /* Report runtime error to Det in case invalid core id*/
    (void)Det_ReportRuntimeError(WDGM_MODULE_ID, coreId,
        WDGM_GETMODE_SID, WDGM_E_COREINACTIVATED);
	#else
	#if(WDGM_DEV_ERROR_DETECT == STD_ON)
	/* Report error to Det in case invalid core id*/
    (void)Det_ReportError(WDGM_MODULE_ID, coreId,
        WDGM_GETMODE_SID, WDGM_E_COREINACTIVATED);
	#endif
	#endif
  }
  #endif
  return (returnValue);
}
#define WDGM_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"

/*******************************************************************************
** Function Name        : WdgM_CheckpointReached                              **
**                                                                            **
** Service ID           : 0x0e                                                **
**                                                                            **
** Description          : Indicates to the WdgM that a checkpoint within      **
**                        a supervised entity has been reached                **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : SEID : Identifier of the Supervised Entity that     **
**                               reports a CheckpointID                       **
**                        CheckpointID : Identifier of the Checkpoint within  **
**                                       a Supervised Entity that has been    **
**                                       reached                              **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : E_OK: Successfully updated alive counter            **
**                        E_NOT_OK: Update failed                             **
**                                                                            **
** Preconditions        : Watchdog Manager should be initialized              **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        WdgM_SupervisedEntity,                              **
**                        WdgM_GlobalSupervisionStatus,                       **
**                        WdgM_CurrentMode                                    **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Det_ReportError,                                    **
**                        WdgM_SEIndexBinarySearch,                           **
**                        WdgM_SEIDBinarySearch,                              **
**                        WdgM_PerformAliveIndication,                        **
**                        WdgM_PerformDeadlineSupervision,                    **
**                        WdgM_PerformIntLogicalSupervision,                  **
**                        WdgM_PerformExtLogicalSupervision                   **
*******************************************************************************/
/* @Trace: SRS_BSW_00357 SRS_BSW_00171 SRS_WdgM_CUS_00013 SRS_BSW_00323 SRS_BSW_00310 SRS_ModeMgm_09221 SRS_ModeMgm_09222 SRS_ModeMgm_09112 SRS_ModeMgm_09160 SRS_WdgM_CUS_00012 */
#define WDGM_START_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"
FUNC(Std_ReturnType, WDGM_CODE) WdgM_CheckpointReached(
  VAR(WdgM_SupervisedEntityIdType, AUTOMATIC) SEID, 
  VAR(WdgM_CheckpointIdType, AUTOMATIC) CheckpointID
)
{
  /* Local pointer for the pointing to SE in the current mode */
  P2CONST(WdgM_ActiveSEType, AUTOMATIC, WDGM_CONST) ptrSE;
  /* Index for looping through Localstatusparam structure array */
  VAR(WdgM_SupervisedEntityIndexType, AUTOMATIC) supervisedEntityIdx;
  /* Local variable for return value */
  VAR(Std_ReturnType, AUTOMATIC) returnValue;
  VAR(boolean, AUTOMATIC) isSEValid;
  /* Local variable for storing total checkpoints in the corresponding SE */
  VAR(WdgM_CheckpointIdType, AUTOMATIC) totalCheckpoints;
  VAR(WdgM_CoreIdType, AUTOMATIC) coreId;
  P2VAR(WdgM_GlobalStatusType, AUTOMATIC, WDGM_APPL_DATA) ptrGlobalSupervisionStatus;
  #if((WDGM_ENABLE_ALIVE_SUPERVISION == STD_ON) || \
    (WDGM_ENABLE_DEADLINE_SUPERVISION == STD_ON) || \
    (WDGM_ENABLE_INTERNAL_TRANSITION == STD_ON) || \
    (WDGM_ENABLE_EXTERNAL_TRANSITION == STD_ON))
    /* Local pointer for the pointing to the SE array */
  P2CONST(WdgM_SupervisedEntityType, AUTOMATIC, WDGM_CONST) ptrSupervisedEntity;
  #endif
  #if((WDGM_ENABLE_ALIVE_SUPERVISION == STD_ON) || \
    (WDGM_ENABLE_DEADLINE_SUPERVISION == STD_ON) || \
    (WDGM_ENABLE_EXTERNAL_TRANSITION == STD_ON))
  VAR(WdgM_ModeType, AUTOMATIC) currMode;
  #endif
  
  /* @Trace: SafeWdgM_SUD_API_036 */
  /* Get core index*/
  returnValue = WdgM_GetCoreIndex(&coreId);
  supervisedEntityIdx = WDGM_ZERO;

  #if (WDGM_TOTAL_CORES > WDGM_ONE)
  if (returnValue == E_OK)
  #endif
  {
    /* @Trace: SafeWdgM_SUD_API_037 */
    ptrGlobalSupervisionStatus = WDGM_GET_GLOBAL_SUPERVISION_STATUS_PTR(coreId);
    /* Det Check for module initialization*/
    if (WDGM_GLOBAL_STATUS_DEACTIVATED == *ptrGlobalSupervisionStatus)
    {
      #if (WDGM_DEV_ERROR_DETECT == STD_ON)
      /* Report to DET  */
      (void)Det_ReportError(WDGM_MODULE_ID, coreId,
        WDGM_CHECKPOINTREACHED_SID, WDGM_E_UNINIT);
      #endif
      /* Set return value to E_NOT_OK since module is not initialized */
      returnValue = E_NOT_OK;
    }
    else
    {
      /* @Trace: SafeWdgM_SUD_API_038 */
      /* Get the pointer to the actual SEIndex array */
      isSEValid = WdgM_SEIndexBinarySearch(SEID, &supervisedEntityIdx);
      if (isSEValid != WDGM_TRUE)
      {
        #if (WDGM_DEV_ERROR_DETECT == STD_ON)
        /* Report to DET  */
        (void)Det_ReportError(WDGM_MODULE_ID, coreId,
          WDGM_CHECKPOINTREACHED_SID, WDGM_E_PARAM_SEID);
        #endif
        /* Return the E_NOT_OK since SE is invalid */
        returnValue = E_NOT_OK;
      }
      else
      {
        /* @Trace: SafeWdgM_SUD_API_039 */
        totalCheckpoints = WdgM_SupervisedEntity[supervisedEntityIdx].TotalCheckpoints;
        if (CheckpointID >= totalCheckpoints)
        {
          #if (WDGM_DEV_ERROR_DETECT == STD_ON)
          /* Report to DET  */
          (void)Det_ReportError(WDGM_MODULE_ID, coreId,
            WDGM_CHECKPOINTREACHED_SID, WDGM_E_CPID);
          #endif
          /* Return the E_NOT_OK since CP is invalid */
          returnValue = E_NOT_OK;
        }
        else
        {
          /* @Trace: SafeWdgM_SUD_API_040 */
          #if((WDGM_ENABLE_ALIVE_SUPERVISION == STD_ON) || \
            (WDGM_ENABLE_DEADLINE_SUPERVISION == STD_ON) || \
            (WDGM_ENABLE_INTERNAL_TRANSITION == STD_ON) || \
            (WDGM_ENABLE_EXTERNAL_TRANSITION == STD_ON))
          ptrSupervisedEntity = &WdgM_SupervisedEntity[supervisedEntityIdx];
          #endif
          #if((WDGM_ENABLE_ALIVE_SUPERVISION == STD_ON) || \
            (WDGM_ENABLE_DEADLINE_SUPERVISION == STD_ON) || \
            (WDGM_ENABLE_EXTERNAL_TRANSITION == STD_ON))
          currMode = WDGM_READ_CURRENT_MODE(coreId);
          #endif
          /* Check whether SE is active in current mode or not */
          ptrSE = WdgM_SEIDBinarySearch(coreId, SEID);
          if (ptrSE != NULL_PTR)
          {
            /* @Trace: SafeWdgM_SUD_API_065 */
            #if(WDGM_ENABLE_ALIVE_SUPERVISION == STD_ON)
            if ((ptrSupervisedEntity->SupervisionMechanism & WDGM_B0_AS) == WDGM_B0_AS)
            {
              WdgM_PerformAliveIndication(coreId, SEID, CheckpointID, currMode);
            }
            #endif /* #if(WDGM_ENABLE_ALIVE_SUPERVISION == STD_ON) */

            #if(WDGM_ENABLE_DEADLINE_SUPERVISION == STD_ON)
            if ((ptrSupervisedEntity->SupervisionMechanism & WDGM_B1_DS) == WDGM_B1_DS)
            {
              /* Perform deadline monitoring for the requested checkpoint */
              WdgM_PerformDeadlineSupervision(coreId, SEID, CheckpointID,
                ptrSE->SEArrayIndex, currMode);
            }
            #endif

            #if(WDGM_ENABLE_INTERNAL_TRANSITION == STD_ON)
            /* ILS Algorithm */
            if ((ptrSupervisedEntity->SupervisionMechanism & WDGM_B2_ILS) == WDGM_B2_ILS)
            {
              /* Perform internal logical supervision for the requested checkpoint */
              WdgM_PerformIntLogicalSupervision(coreId, CheckpointID,
                ptrSE->SEArrayIndex);
            }
            #endif

            #if(WDGM_ENABLE_EXTERNAL_TRANSITION == STD_ON)
            if ((ptrSupervisedEntity->SupervisionMechanism & WDGM_B3_ELS) == WDGM_B3_ELS)
            {
              /* Perform external logical supervision for the requested checkpoint */
              WdgM_PerformExtLogicalSupervision(coreId, SEID, CheckpointID,
                ptrSE->SEArrayIndex, currMode);
            }
            #endif
          }
          /* Is Det reporting enabled */
          else
          {
            /* @Trace: SafeWdgM_SUD_API_041 */
	        #if (((DET_AR_RELEASE_MAJOR_VERSION == 0x04)&&(DET_AR_RELEASE_MINOR_VERSION >= 0x02))|| \
	          (DET_AR_RELEASE_MAJOR_VERSION > 0x04))
            /* Report runtime error to Det*/
            (void)Det_ReportRuntimeError(WDGM_MODULE_ID, coreId,
              WDGM_CHECKPOINTREACHED_SID, WDGM_E_SEDEACTIVATED);
	        #else
			#if(WDGM_DEV_ERROR_DETECT == STD_ON)
	        /* Report error to Det*/
            (void)Det_ReportError(WDGM_MODULE_ID, coreId,
              WDGM_CHECKPOINTREACHED_SID, WDGM_E_SEDEACTIVATED);
			#endif
	        #endif
            /* Return the E_NOT_OK since SE not configured */
            returnValue = E_NOT_OK;
          }
        }
      }
    }
  }
  #if (WDGM_TOTAL_CORES > WDGM_ONE)
  else
  {
	#if (((DET_AR_RELEASE_MAJOR_VERSION == 0x04)&&(DET_AR_RELEASE_MINOR_VERSION >= 0x02))|| \
	  (DET_AR_RELEASE_MAJOR_VERSION > 0x04))
    /* Report runtime error to Det in case invalid core id*/
    (void)Det_ReportRuntimeError(WDGM_MODULE_ID, coreId,
        WDGM_CHECKPOINTREACHED_SID, WDGM_E_COREINACTIVATED);
	#else
	#if(WDGM_DEV_ERROR_DETECT == STD_ON)
	/* Report error to Det in case invalid core id*/
    (void)Det_ReportError(WDGM_MODULE_ID, coreId,
        WDGM_CHECKPOINTREACHED_SID, WDGM_E_COREINACTIVATED);
	#endif
	#endif
  }
  #endif
  return (returnValue);
}

#define WDGM_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"


/*******************************************************************************
** Function Name        : WdgM_GetLocalStatus                                 **
**                                                                            **
** Service ID           : 0x0c                                                **
**                                                                            **
** Description          : This service provides the supervision status of an  **
**                        individual supervised entity                        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : SEID : Identifier of the supervised entity whose    **
**                               supervision status shall be returned         **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : Status : Supervision status of the given supervised **
**                                 entity                                     **
**                                                                            **
** Return parameter     : E_OK: Supervision status successfully returned      **
**                        E_NOT_OK: Returning supervision status failed       **
**                                                                            **
** Preconditions        : Watchdog Manager should be initialized              **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                        WdgM_SEStatus,                                      **
**                        WdgM_GlobalSupervisionStatus                        **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Det_ReportError,                                    **
**                        WdgM_SEIndexBinarySearch,                           **
**                        SchM_Enter_WdgM_GLOBALSUPVSNSTATUS_PROTECTION,      **
**                        SchM_Exit_WdgM_GLOBALSUPVSNSTATUS_PROTECTION        **
*******************************************************************************/
/* @Trace: SRS_BSW_00357 SRS_BSW_00171 SRS_WdgM_CUS_00013 SRS_BSW_00323 SRS_BSW_00310 */
#define WDGM_START_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"
FUNC(Std_ReturnType, WDGM_CODE) WdgM_GetLocalStatus(
  VAR(WdgM_SupervisedEntityIdType, AUTOMATIC) SEID,
  P2VAR(WdgM_LocalStatusType, WDGM_DATA, WDGM_APPL_DATA) Status
)
{
  VAR(WdgM_SupervisedEntityIndexType, AUTOMATIC) supervisedEntityIdx;
  /* Local variable for return value */
  VAR(Std_ReturnType, AUTOMATIC) returnValue;
  VAR(boolean, AUTOMATIC) isSEValid;
  VAR(WdgM_CoreIdType, AUTOMATIC) coreId;
  P2VAR(WdgM_GlobalStatusType, AUTOMATIC, WDGM_APPL_DATA) ptrGlobalSupervisionStatus;
 
  /* @Trace: SafeWdgM_SUD_API_019 */
  /* Get core index*/
  returnValue = WdgM_GetCoreIndex(&coreId);

  supervisedEntityIdx = WDGM_ZERO;
  #if (WDGM_TOTAL_CORES > WDGM_ONE)
  if (returnValue == E_OK)
  #endif
  {
    /* @Trace: SafeWdgM_SUD_API_020 */
    ptrGlobalSupervisionStatus = WDGM_GET_GLOBAL_SUPERVISION_STATUS_PTR(coreId);
    /* Det Check for module initialization*/
    if (WDGM_GLOBAL_STATUS_DEACTIVATED == *ptrGlobalSupervisionStatus)
    {
      #if (WDGM_DEV_ERROR_DETECT == STD_ON)
      /* Report to DET  */
      (void)Det_ReportError(WDGM_MODULE_ID, coreId,
        WDGM_GETLOCALSTATUS_SID, WDGM_E_UNINIT);
      #endif
      /* Set return value to E_NOT_OK */
      returnValue = E_NOT_OK;
    }
    /* Det Check for NULL pointer */
    if (Status == NULL_PTR)
    {
      #if (WDGM_DEV_ERROR_DETECT == STD_ON)
      /* Report to DET  */
      (void)Det_ReportError(WDGM_MODULE_ID, coreId,
        WDGM_GETLOCALSTATUS_SID, WDGM_E_INV_POINTER);
      #endif
      /* Set return value to E_NOT_OK */
      returnValue = E_NOT_OK;
    }
    if (returnValue == E_OK)
    {
      /* @Trace: SafeWdgM_SUD_API_021 */
      /* Get the pointer to the actual SEIndex array */
      isSEValid = WdgM_SEIndexBinarySearch(SEID, &supervisedEntityIdx);
      if (isSEValid != WDGM_TRUE)
      {
        #if (WDGM_DEV_ERROR_DETECT == STD_ON)
        /* Report to DET  */
        (void)Det_ReportError(WDGM_MODULE_ID, coreId,
          WDGM_GETLOCALSTATUS_SID, WDGM_E_PARAM_SEID);
        #endif
        /* Return the E_NOT_OK since SE not configured */
        returnValue = E_NOT_OK;
      }
      else
      {
        /* @Trace: SafeWdgM_SUD_API_022 */
        if (WDGM_READ_SE_STATUS_PTR(supervisedEntityIdx) != NULL_PTR)
        {
          SchM_Enter_WdgM_GLOBALSUPVSNSTATUS_PROTECTION();
          /* polyspace-begin MISRA-C3:D4.14 [Not a defect:Low] "Status will be checked before using" */
          /* Update the Local status */
          *Status = (WdgM_LocalStatusType)(WDGM_READ_SE_STATUS(supervisedEntityIdx)
            & WDGM_STATUS_MASK);
          /* polyspace-end MISRA-C3:D4.14 */
          SchM_Exit_WdgM_GLOBALSUPVSNSTATUS_PROTECTION();
        }
        else
        {
          /* polyspace-begin MISRA-C3:D4.14 [Not a defect:Low] "Status will be checked before using" */
          *Status = (WDGM_LOCAL_STATUS_DEACTIVATED & WDGM_STATUS_MASK);
          /* polyspace-end MISRA-C3:D4.14 */
        }
      }
    }
  }
  #if (WDGM_TOTAL_CORES > WDGM_ONE)
  else
  {
	#if (((DET_AR_RELEASE_MAJOR_VERSION == 0x04)&&(DET_AR_RELEASE_MINOR_VERSION >= 0x02))|| \
	  (DET_AR_RELEASE_MAJOR_VERSION > 0x04))
    /* Report runtime error to Det in case invalid core id*/
    (void)Det_ReportRuntimeError(WDGM_MODULE_ID, coreId,
        WDGM_GETLOCALSTATUS_SID, WDGM_E_COREINACTIVATED);
	#else
	#if(WDGM_DEV_ERROR_DETECT == STD_ON)
	/* Report error to Det in case invalid core id*/
    (void)Det_ReportError(WDGM_MODULE_ID, coreId,
        WDGM_GETLOCALSTATUS_SID, WDGM_E_COREINACTIVATED);
	#endif
	#endif
  }
  #endif
  return (returnValue);
}
#define WDGM_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"

/*******************************************************************************
** Function Name        : WdgM_GetGlobalStatus                                **
**                                                                            **
** Service ID           : 0x0d                                                **
**                                                                            **
** Description          : This service provides global supervision status of  **
**                        WdgM                                                **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : Status : Global supervision status of the WdgM      **
**                                                                            **
** Return parameter     : E_OK: Supervision status successfully returned      **
**                        E_NOT_OK: Returning supervision status failed       **
**                                                                            **
** Preconditions        : Watchdog Manager should be initialized              **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                        WdgM_GlobalSupervisionStatus                        **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Det_ReportError,                                    **
**                        SchM_Enter_WdgM_GLOBALSUPVSNSTATUS_PROTECTION,      **
**                        SchM_Exit_WdgM_GLOBALSUPVSNSTATUS_PROTECTION        **
*******************************************************************************/
/* @Trace: SRS_BSW_00357 SRS_BSW_00171 SRS_WdgM_CUS_00013 SRS_BSW_00310 SRS_BSW_00323 */
#define WDGM_START_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"
FUNC(Std_ReturnType, WDGM_CODE) WdgM_GetGlobalStatus(
  P2VAR(WdgM_GlobalStatusType, WDGM_DATA, WDGM_APPL_DATA) Status
)
{
  /* Local variable for return value */
  VAR(Std_ReturnType, AUTOMATIC) returnValue;
  VAR(WdgM_CoreIdType, AUTOMATIC) coreId;
  P2VAR(WdgM_GlobalStatusType, AUTOMATIC, WDGM_APPL_DATA) ptrGlobalSupervisionStatus;
  
  /* @Trace: SafeWdgM_SUD_API_016 */
  /* Get core index*/
  returnValue = WdgM_GetCoreIndex(&coreId);
  
  #if (WDGM_TOTAL_CORES > WDGM_ONE)
  if (returnValue == E_OK)
  #endif
  {
    /* @Trace: SafeWdgM_SUD_API_017 */
    ptrGlobalSupervisionStatus = WDGM_GET_GLOBAL_SUPERVISION_STATUS_PTR(coreId);
    /* Det Check for module initialization*/
    if (WDGM_GLOBAL_STATUS_DEACTIVATED == *ptrGlobalSupervisionStatus)
    {
      #if (WDGM_DEV_ERROR_DETECT == STD_ON)
      /* Report to DET  */
      (void)Det_ReportError(WDGM_MODULE_ID, coreId,
        WDGM_GETGLOBALSTATUS_SID, WDGM_E_UNINIT);
      #endif
      /* Set return value to E_NOT_OK */
      returnValue = E_NOT_OK;
    }
    /* Det Check for NULL pointer */
    if (Status == NULL_PTR)
    {
      #if (WDGM_DEV_ERROR_DETECT == STD_ON)
      /* Report to DET  */
      (void)Det_ReportError(WDGM_MODULE_ID, coreId,
        WDGM_GETGLOBALSTATUS_SID, WDGM_E_INV_POINTER);
      #endif
      /* Set return value to E_NOT_OK */
      returnValue = E_NOT_OK;
    }
    /* @Trace: SafeWdgM_SUD_API_018 */
    /* Check the return value */
    if (returnValue == E_OK)
    {
      SchM_Enter_WdgM_GLOBALSUPVSNSTATUS_PROTECTION();
      /* polyspace-begin MISRA-C3:D4.14 [Not a defect:Low] "Status is initialised before using" */
      /* Store the global supervision status into the input pointer */
      *Status = WdgM_PlatformGlobalSupervisionStatus;
      /* polyspace-end MISRA-C3:D4.14 */
      SchM_Exit_WdgM_GLOBALSUPVSNSTATUS_PROTECTION();
    }
  }
  #if (WDGM_TOTAL_CORES > WDGM_ONE)
  else
  {
	#if (((DET_AR_RELEASE_MAJOR_VERSION == 0x04)&&(DET_AR_RELEASE_MINOR_VERSION >= 0x02))|| \
	  (DET_AR_RELEASE_MAJOR_VERSION > 0x04))
    /* Report runtime error to Det in case invalid core id*/
    (void)Det_ReportRuntimeError(WDGM_MODULE_ID, coreId,
        WDGM_GETGLOBALSTATUS_SID, WDGM_E_COREINACTIVATED);
	#else
	#if(WDGM_DEV_ERROR_DETECT == STD_ON)
	/* Report error to Det in case invalid core id*/
    (void)Det_ReportError(WDGM_MODULE_ID, coreId,
        WDGM_GETGLOBALSTATUS_SID, WDGM_E_COREINACTIVATED);
    #endif		
	#endif
  }
  #endif
  return (returnValue);
}
#define WDGM_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"

/*******************************************************************************
** Function Name        : WdgM_PerformReset                                   **
**                                                                            **
** Service ID           : 0x0f                                                **
**                                                                            **
** Description          : This service instructs the WdgM to initiate         **
**                        a watchdog reset                                    **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : Watchdog Manager should be initialized              **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                        WdgM_PtrConfig,                                     **
**                        WdgM_CurrentMode,                                   **
**                        WdgM_GlobalSupervisionStatus                        **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Det_ReportError,                                    **
**                        WdgM_TriggerWdgIf,                                  **
*******************************************************************************/
/* @Trace: SRS_BSW_00171 SRS_WdgM_CUS_00013 SRS_BSW_00323 SRS_BSW_00310 SRS_ModeMgm_09232 */
#define WDGM_START_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"
FUNC(void, WDGM_CODE) WdgM_PerformReset(void)
{
  #if(WDGM_ENABLE_TRIGGER == STD_ON)
  /* Local pointer for the pointing to the current mode */
  P2CONST(WdgM_ModePropertyType, AUTOMATIC, WDGM_CONST)ptrMode;
  P2CONST(WdgM_ConfigType, AUTOMATIC, CONST) WdgM_PtrConfig;
  #endif
  VAR(WdgM_CoreIdType, AUTOMATIC) coreId;
  #if (WDGM_TOTAL_CORES > WDGM_ONE)
  VAR(Std_ReturnType, AUTOMATIC) coreIdxStatus;
  #endif
  P2VAR(WdgM_GlobalStatusType, AUTOMATIC, WDGM_APPL_DATA) ptrGlobalSupervisionStatus;

  /* @Trace: SafeWdgM_SUD_API_190 */
  #if (WDGM_TOTAL_CORES == WDGM_ONE)
  (void)WdgM_GetCoreIndex(&coreId);
  #else
  /* Get core index*/
  coreIdxStatus = WdgM_GetCoreIndex(&coreId);
  if (coreIdxStatus == E_OK)
  #endif
  {
    ptrGlobalSupervisionStatus = WDGM_GET_GLOBAL_SUPERVISION_STATUS_PTR(coreId);
    /* Det Check for module initialization*/
    if (WDGM_GLOBAL_STATUS_DEACTIVATED == *ptrGlobalSupervisionStatus)
    {
      /* @Trace: SafeWdgM_SUD_API_193 */
      #if (WDGM_DEV_ERROR_DETECT == STD_ON)
      /* Report to DET  */
      (void)Det_ReportError(WDGM_MODULE_ID, coreId,
        WDGM_PERFORMRESET_SID, WDGM_E_UNINIT);
      #endif
    }
    else
    {
      /* @Trace: SafeWdgM_SUD_API_194 */
      #if(WDGM_ENABLE_TRIGGER == STD_ON)
      /* Local pointer to WdgM_ConfigType */
      WdgM_PtrConfig = GET_CONFIG_PTR(coreId);
      /* Get the address of currentMode from the Mode structure array into the
        global pointer */
      ptrMode = &(WdgM_PtrConfig->PtrModes[WDGM_READ_CURRENT_MODE(coreId)]);
      /* polyspace-end RTE:IDP MISRA-C3:D4.1 MISRA-C3:18.1 */
      WdgM_TriggerWdgIf(coreId, ptrMode, WDGM_TM_TIMEOUT);
      #endif
    }
  }
  #if (WDGM_TOTAL_CORES > WDGM_ONE)
  else
  {
	#if (((DET_AR_RELEASE_MAJOR_VERSION == 0x04)&&(DET_AR_RELEASE_MINOR_VERSION >= 0x02))|| \
	  (DET_AR_RELEASE_MAJOR_VERSION > 0x04))
    /* Report runtime error to Det in case invalid core id*/
    (void)Det_ReportRuntimeError(WDGM_MODULE_ID, coreId,
        WDGM_PERFORMRESET_SID, WDGM_E_COREINACTIVATED);
	#else
	#if(WDGM_DEV_ERROR_DETECT == STD_ON)
	/* Report error to Det in case invalid core id*/
    (void)Det_ReportError(WDGM_MODULE_ID, coreId,
        WDGM_PERFORMRESET_SID, WDGM_E_COREINACTIVATED);
	#endif
	#endif
  }
  #endif
}
#define WDGM_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"

/*******************************************************************************
** Function Name        : WdgM_GetFirstExpiredSEID                            **
**                                                                            **
** Service ID           : 0x10                                                **
**                                                                            **
** Description          : This service returns SEID that first reached the    **
**                        state WDGM_LOCAL_STATUS_EXPIRED                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : SEID : Identifier of the supervised entity that     **
**                               first reached the state                      **
**                               WDGM_LOCAL_STATUS_EXPIRED                    **
**                                                                            **
** Return parameter     : E_OK: Successfully returned                         **
**                        E_NOT_OK: Error when returning the SEID             **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                        WdgM_FirstExpiredSEID,                              **
**                        WdgM_InvFirstExpiredSEID                            **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Det_ReportError,                                    **
**                        SchM_Enter_WdgM_GLOBALSUPVSNSTATUS_PROTECTION,      **
**                        SchM_Exit_WdgM_GLOBALSUPVSNSTATUS_PROTECTION        **
*******************************************************************************/
/* @Trace: SRS_BSW_00357 SRS_BSW_00171 SRS_WdgM_CUS_00013 SRS_WdgM_CUS_00008 */
#define WDGM_START_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"
FUNC(Std_ReturnType, WDGM_CODE) WdgM_GetFirstExpiredSEID(
  P2VAR(WdgM_SupervisedEntityIdType, WDGM_DATA, WDGM_APPL_DATA) SEID
)
{
  VAR(WdgM_SupervisedEntityIdType, AUTOMATIC) invFirstExpiredSEID;
  VAR(WdgM_CoreIdType, AUTOMATIC) coreId;

  /* Local variable for return value */
  VAR(Std_ReturnType, AUTOMATIC) returnValue;

  /* @Trace: SafeWdgM_SUD_API_013 */
  /* Get core index*/
  returnValue = WdgM_GetCoreIndex(&coreId);
  #if (WDGM_TOTAL_CORES > WDGM_ONE)
  if (returnValue == E_OK)
  #endif
  {
    /* Is Det reporting enabled */
    /* Det Check for NULL pointer */
    if (SEID == NULL_PTR)
    {
      /* @Trace: SafeWdgM_SUD_API_015 */
      #if (WDGM_DEV_ERROR_DETECT == STD_ON)
      /* Report to DET  */
      (void)Det_ReportError(WDGM_MODULE_ID, coreId,
        WDGM_GETFIRSTEXPIRED_SEID_SID, WDGM_E_INV_POINTER);
      #endif
      /* Set return value to E_NOT_OK */
      returnValue = E_NOT_OK;
    }
    else
    {
      /* @Trace: SafeWdgM_SUD_API_014 */
      SchM_Enter_WdgM_GLOBALSUPVSNSTATUS_PROTECTION();

      /* Check whether double inverse value match */
      invFirstExpiredSEID = ~WdgM_InvFirstExpiredSEID;
      if ((WdgM_FirstExpiredSEID == invFirstExpiredSEID) &&
        (WDGM_TRUE == WdgM_FirstExpSEIDStatus))
      {
        /* polyspace-begin MISRA-C3:D4.14 [Not a defect:Low] "SEID will be checked before using" */
        /* Write the first expired SEID value in the out pointer */
        *SEID = WdgM_FirstExpiredSEID;
        /* polyspace-end MISRA-C3:D4.14 */
      }
      else
      {
        /* polyspace-begin MISRA-C3:D4.14 [Not a defect:Low] "SEID will be checked before using" */
        /* Incase double inverse value does not match or there is no expired SEID */
        *SEID = WDGM_ZERO;
        /* polyspace-end MISRA-C3:D4.14 */
        /* Set return value to E_NOT_OK */
        returnValue = E_NOT_OK;
      }

      SchM_Exit_WdgM_GLOBALSUPVSNSTATUS_PROTECTION();
    }
  }
  #if (WDGM_TOTAL_CORES > WDGM_ONE)
  else
  {
	#if (((DET_AR_RELEASE_MAJOR_VERSION == 0x04)&&(DET_AR_RELEASE_MINOR_VERSION >= 0x02))|| \
	  (DET_AR_RELEASE_MAJOR_VERSION > 0x04))
    /* Report runtime error to Det in case invalid core id*/
    (void)Det_ReportRuntimeError(WDGM_MODULE_ID, coreId,
        WDGM_GETFIRSTEXPIRED_SEID_SID, WDGM_E_COREINACTIVATED);
	#else
	#if(WDGM_DEV_ERROR_DETECT == STD_ON)
	/* Report error to Det in case invalid core id*/
    (void)Det_ReportError(WDGM_MODULE_ID, coreId,
        WDGM_GETFIRSTEXPIRED_SEID_SID, WDGM_E_COREINACTIVATED);
	#endif
	#endif
  }
  #endif
  return (returnValue);
}
#define WDGM_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"

/*******************************************************************************
** Function Name        : WdgM_MainFunction                                   **
**                                                                            **
** Service ID           : 0x08                                                **
**                                                                            **
** Description          : This service performs the processing of the cyclic  **
**                        Watchdog Manager jobs.                              **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : Watchdog Manager should be initialized              **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                        WdgM_GlobalSupervisionStatus                        **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Det_ReportError,                                    **
**                        WdgM_PerformAliveSupervision,                       **
**                        WdgM_EvaluateLocalStatus,                           **
**                        WdgM_EvaluateGlobalStatus                           **
*******************************************************************************/
/* @Trace: SRS_BSW_00171 SRS_WdgM_CUS_00013 SRS_BSW_00323 SRS_BSW_00406 SRS_ModeMgm_09112 SRS_BSW_00310 SRS_BSW_00373 SRS_ModeMgm_09161 SRS_ModeMgm_09226 SRS_ModeMgm_09160 SRS_ModeMgm_09221    SRS_ModeMgm_09169 SRS_WdgM_CUS_00006 SRS_BSW_00339 SRS_ModeMgm_09159 SRS_ModeMgm_09163 */
#define WDGM_START_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"
FUNC(void, WDGM_CODE) WdgM_MainFunction(void)
{
  VAR(boolean, AUTOMATIC) expiredFlag;
  VAR(boolean, AUTOMATIC) failedFlag;
  VAR(WdgM_CoreIdType, AUTOMATIC) coreId;
  #if (WDGM_TOTAL_CORES > WDGM_ONE)
  VAR(Std_ReturnType, AUTOMATIC) coreIdxStatus;
  #endif
  P2VAR(WdgM_GlobalStatusType, AUTOMATIC, WDGM_APPL_DATA) ptrGlobalSupervisionStatus;

  /* @Trace: SafeWdgM_SUD_API_010 */
  expiredFlag = WDGM_FALSE;
  failedFlag = WDGM_FALSE;

  #if (WDGM_TOTAL_CORES == WDGM_ONE)
  (void)WdgM_GetCoreIndex(&coreId);
  #else
  /* Get core index*/
  coreIdxStatus = WdgM_GetCoreIndex(&coreId);
  if (coreIdxStatus == E_OK)
  #endif
  {
    /* @Trace: SafeWdgM_SUD_API_011 */
    ptrGlobalSupervisionStatus = WDGM_GET_GLOBAL_SUPERVISION_STATUS_PTR(coreId);
    /* Det Check for module initialization*/
    if (WDGM_GLOBAL_STATUS_DEACTIVATED == *ptrGlobalSupervisionStatus)
    {
      #if (WDGM_DEV_ERROR_DETECT == STD_ON)
      /* Report to DET  */
      (void)Det_ReportError(WDGM_MODULE_ID, coreId,
        WDGM_MAINFUNCTION_SID, WDGM_E_UNINIT);
      #endif
    }
    else
    {
      /* @Trace: SafeWdgM_SUD_API_012 */
      #if(WDGM_ENABLE_ALIVE_SUPERVISION == STD_ON)
      WdgM_PerformAliveSupervision(coreId);
      #endif
      /* Evaluate the local supervision status */
      WdgM_EvaluateLocalStatus(coreId, &failedFlag, &expiredFlag);
      
      /* Evaluate the global supervision status */
      WdgM_EvaluateGlobalStatus(coreId, failedFlag, expiredFlag);
    }
  }
  #if (WDGM_TOTAL_CORES > WDGM_ONE)
  else
  {
	#if (((DET_AR_RELEASE_MAJOR_VERSION == 0x04)&&(DET_AR_RELEASE_MINOR_VERSION >= 0x02))|| \
	  (DET_AR_RELEASE_MAJOR_VERSION > 0x04))
    /* Report runtime error to Det in case invalid core id*/
    (void)Det_ReportRuntimeError(WDGM_MODULE_ID, coreId,
        WDGM_MAINFUNCTION_SID, WDGM_E_COREINACTIVATED);
	#else
	#if(WDGM_DEV_ERROR_DETECT == STD_ON)
	/* Report error to Det in case invalid core id*/
    (void)Det_ReportError(WDGM_MODULE_ID, coreId,
        WDGM_MAINFUNCTION_SID, WDGM_E_COREINACTIVATED);
	#endif
	#endif
  }
  #endif
}
#define WDGM_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"

/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/
/* polyspace-end MISRA-C3:20.1 */
/* polyspace-end DEFECT:DEAD_CODE MISRA2012:2.1,14.3 */
/* polyspace-end MISRA-C3:8.3 */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
