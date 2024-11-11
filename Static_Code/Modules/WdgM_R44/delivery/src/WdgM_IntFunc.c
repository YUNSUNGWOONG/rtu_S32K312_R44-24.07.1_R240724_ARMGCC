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
**  SRC-MODULE: WdgM_IntFunc.c                                                **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR WDGM                                                  **
**                                                                            **
**  PURPOSE   : Watchdog Manager internal API Functionality                   **
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
** 0.0.2     23-Sep-2019   ThanhNT      Optimized validation function         **
** 0.0.3     15-Oct-2019   ThanhNT      Update module version information     **
** 0.0.4     24-Oct-2019   ThanhNT      Update coding convention              **
** 0.0.5     24-Oct-2019   ThanhNT      Update version checking mechanism     **
** 0.0.7     21-Nov-2019   ThanhNT      Update SUD and SRS Ids                **
** 0.0.8     27-Nov-2019   ThanhNT      Fix misra warning                     **
** 0.0.9     05-Dec-2019   ThanhNT      Update Implementation of              **
**                                      WdgM_FirstExpiredSEID and             **
**                                      WdgM_InvFirstExpiredSEID (#refs: 9572)**
** 0.0.12   02-Jan-2019    ThanhNT      Fix WdgM changes Global Supervision   **
**                                      Status at wrong cycle (#refs: 10397)  **
** 0.0.13   03-Feb-2020    ThanhNT      Fix parameters validation shall be    **
**                                      checked regardless of                 **
**                                      WDGM_DEV_ERROR_DETECT (#refs: 10695)  **
** 0.0.14    11-Mar-2020   TienVD       Update traceability                   **
** 0.0.16    26-Mar-2020   ThanhNT      Fix misra defect                      **
** 0.0.17    09-Jul-2020   ThanhNH5     #14409: Added check for totalSEInMode **
** 0.0.18    12-Aug-2020   ThanhNH5     #15179: Removed dead code             **
** 0.0.19    10-Sep-2020   ThanhNH5     Added WdgM_GetCoreIndex (#15739)      **
** 0.0.20    11-Sep-2020   ThanhNH5     Fixed DEM configuration issue(#15741) **
** 0.0.21    11-Sep-2020   ThanhNH5     Added multi core protection (#15596)  **
** 0.0.22    12-Sep-2020   LanBT        Update to use common function         **
**                                      signature with coreId in prama(#15485)**
** 0.0.23    12-Sep-2020   LanBT        To remove WdgM_PtrConfig global       **
**                                      variable and use locally only (#15485)**
** 0.0.24    12-Sep-2020   ThanhNH5     Added Os APIs checking (#15690)       **
** 0.0.25    16-Sep-2020   ThanhNH5     Added DeInit time out for each core   **
**                                      (#15843)                              **
** 0.0.26    17-Sep-2020   ThanhNH5     Removed RunTime error report(#15690)  **
** 0.0.27    25-Sep-2020   ThanhNH5     Corrected Processing platform global  **
**                                      status(#15969)                        **
** 0.0.28    05-Oct-2020   ThanhNH5     Merge variables in single and         **
**                                      multi core (#15485)                   **
** 0.0.30    16-Oct-2020   ThanhNT      Update MemMap ASIL_D (#16306)         **
** 0.0.31    16-Oct-2020   ThanhNT      Update global variables multicore     **
**                                      (#16286)                              **
** 0.0.32    30-Oct-2020   ThanhNH5     Updated Exclusive areas (#16306)      **
** 0.0.33    30-Oct-2020   ThanhNH5     Fix issue WdgM_FailedRefCycleCounter  **
**                                      access (#16813)                       **
** 1.0.2     22-Mar-2021   HiepVT1      Changed code to use Det_ReportError() **
**                                      replace for Det_ReportRuntimeError()  **
**                                      dependent on the DET version(#18339)  **
**                                      and update trace                      **
** 1.2.0     01-Dec-2021   HiepVT1      Updated WdgM_EvaluateLocalStatus      **
**                                      function to support                   **
**                                      SWS_WdgM_CONSTR_6501                  **
** 1.3.0.1   30-Jun-2022   TriBD        #CP44-322                             **
** 1.3.1.0   08-Aug-2022   TriBD        #CP44-385                             **
** 1.3.1.1   19-Aug-2022   TriBD        #CP44-754                             **
** 1.3.2.0   12-Dec-2022   NhanNV8      #CP44-1023                            **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-begin MISRA-C3:20.1 [Not a defect:Low] "see SWS_MemMap_00003 of AUTOSAR"    */

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "WdgM_IntFunc.h"     /* WdgM internal function prototype */
#include "WdgM_Ram.h"         /* WdgM Ram variables header file */
#include "SchM_WdgM.h"        /* SchM Header file */
#include "WdgM_Cores.h"       /* WdgM cores header file */
#if(WDGM_ENABLE_OS_APPLICATION == STD_ON)
#include "BswM_WdgM.h"        /* BswM Module header file */
#endif
#if(WDGM_IMMEDIATE_RESET == STD_ON)
#include "Mcu.h"              /* Mcu Header file */
#endif
#include "Det.h"              /* Det Header file */

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/*******************************************************************************
**                      File version check                                    **
*******************************************************************************/

/*******************************************************************************
**                       Function Definitions                                 **
*******************************************************************************/
#define WDGM_START_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"
static FUNC(void, WDGM_CODE) WdgM_EvaluatePlatformGlobalStatus(
  P2CONST(WdgM_ConfigType, AUTOMATIC, CONST) ptrConfig,
  P2CONST(WdgM_ModePropertyType, AUTOMATIC, WDGM_CONST)ptrModes,
  VAR(CoreIdType, AUTOMATIC) coreId
);
#define WDGM_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"

#if(WDGM_ENABLE_EXTERNAL_TRANSITION == STD_ON)
#define WDGM_START_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"
static FUNC(boolean, WDGM_CODE) WdgM_GetExtLSIndex(
  P2CONST(WdgM_ModePropertyType, AUTOMATIC, WDGM_CONST) ptrModes,
  P2VAR(uint16, AUTOMATIC, WDGM_DATA) ptrExLSIndex,
  P2VAR(WdgM_ExLSGraphArrayType, AUTOMATIC, WDGM_DATA) ptrExLSGraphArrayIndex,
  VAR(WdgM_SupervisedEntityIdType, AUTOMATIC) supervisedEntityId,
  VAR(WdgM_CheckpointIdType, AUTOMATIC) cpId
);
#define WDGM_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"
#endif

#define WDGM_START_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"
static FUNC(void, WDGM_CODE) WdgM_CalcNewLocalStatus(
  P2CONST(WdgM_ActiveSEType, AUTOMATIC, WDGM_CONST) ptrActiveSE,
  VAR(uint8, AUTOMATIC) seStatus,
  P2VAR(uint8, AUTOMATIC, WDGM_DATA) ptrNewLocalStatus
);
#define WDGM_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"
/*******************************************************************************
** Function Name      : WdgM_SEIDBinarySearch                                 **
**                                                                            **
** Service ID         : NA                                                    **
**                                                                            **
** Description        : This service gives the supervised entity position     **
**                      in the configured mode                                **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : supervisedEntityId : An active SE Id                  **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : Pointer to corresponding Active SE                    **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                      WdgM_PtrConfig,                                       **
**                      WdgM_CurrentMode                                      **
**                                                                            **
**                      Function(s) invoked : None                            **
*******************************************************************************/
/* @Trace: SRS_BSW_00327 SRS_BSW_00337 SRS_BSW_00385 SRS_BSW_00323 */
#define WDGM_START_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"

FUNC_P2CONST(WdgM_ActiveSEType, AUTOMATIC, WDGM_CODE)  WdgM_SEIDBinarySearch(    VAR(CoreIdType, AUTOMATIC) coreId,     VAR(WdgM_SupervisedEntityIdType, AUTOMATIC) supervisedEntityId  )
{
  P2CONST(WdgM_ModePropertyType, AUTOMATIC, WDGM_CONST) ptrMode;
  P2CONST(WdgM_ActiveSEType, AUTOMATIC, WDGM_CONST) ptrActiveSE;
  P2CONST(WdgM_ActiveSEType, AUTOMATIC, WDGM_CONST) ptrFirstSEInMode;
  VAR(WdgM_SupervisedEntityIdType, AUTOMATIC) currentSEId;
  VAR(uint16, AUTOMATIC) totalSEInMode;
  VAR(uint16, AUTOMATIC) lowIdx;
  VAR(uint16, AUTOMATIC) highIdx;
  VAR(uint16, AUTOMATIC) midIdx;
  P2CONST(WdgM_ConfigType, AUTOMATIC, CONST) WdgM_PtrConfig;

  /* @Trace: SafeWdgM_SUD_API_409 */
  /* Local pointer to WdgM_ConfigType */
  WdgM_PtrConfig = GET_CONFIG_PTR(coreId);
  
  /* Get the pointer to previous mode array */
  ptrMode = &(WdgM_PtrConfig->PtrModes[WDGM_READ_CURRENT_MODE(coreId)]);
  /* Initialize return value with null pointer */
  ptrActiveSE = NULL_PTR;
  /* Get the total SE's in the previous mode */
  totalSEInMode = ptrMode->TotalSEInMode;

  if (totalSEInMode > WDGM_ZERO)
  {
    /* Get the pointer to WdgM_GaaModexLocalStatus */
    ptrFirstSEInMode = ptrMode->PtrActiveSEList;

    highIdx = totalSEInMode - WDGM_ONE;
    /* Initialize lowIdx variable with one */
    lowIdx  = WDGM_ONE;

    /* Get the lower limit of SEID */
    currentSEId = ptrFirstSEInMode->SEId;
    /* Check whether search SEID is in range */
    if ((supervisedEntityId >= currentSEId) && 
        (supervisedEntityId <= ptrFirstSEInMode[highIdx].SEId))
    {
      /* @Trace: SafeWdgM_SUD_API_410 */
      /* Check whether requested SEID is same as first SEID of the list */
      if (supervisedEntityId != currentSEId)
      {
        do
        {
          /* Get the middle index number */
          midIdx = (highIdx + lowIdx) >> WDGM_ONE;
          /* Get the SEID of the mid value in SE array */
          currentSEId = ptrFirstSEInMode[midIdx].SEId;
          /* Compare SEID with the requested one */
          if (currentSEId == supervisedEntityId)
          {
            /* Update the return pointer with the WdgM_GaaModexLocalStatus
              array */
            ptrActiveSE = &(ptrFirstSEInMode[midIdx]);
            /* Set highIdx to zero to break the loop */
            highIdx = WDGM_ZERO;
          }
          else
          {
            /* Compare the SEID with the requested one */
            if (supervisedEntityId < currentSEId)
            {
              /* If the received SEID is lower, update highIdx */
              highIdx = midIdx - WDGM_ONE;
            }
            else
            {
              /* If the received SEID is higher, update lowIdx  */
              lowIdx  = midIdx + WDGM_ONE;
            }
          } /* End of the condition "If currentSEId equal to SEID" */
        } while (lowIdx  <= highIdx);
      } /* if(supervisedEntityId != currentSEId) */
      else
      {
        /* @Trace: SafeWdgM_SUD_API_412 */
        /* Update the return pointer with the actual SEID mapping structure */
        ptrActiveSE = ptrFirstSEInMode;
      }
    } /* if((supervisedEntityId >= currentSEId) &&... */
  } /* if((supervisedEntityId >= currentSEId) &&... */
  /* @Trace: SafeWdgM_SUD_API_411 */
  /* Return pointer of SEID*/
  return (ptrActiveSE);
}
#define WDGM_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"

/*******************************************************************************
** Function Name      : WdgM_SEIndexBinarySearch                              **
**                                                                            **
** Service ID         : NA                                                    **
**                                                                            **
** Description        : This service gives the supervised entity position     **
**                      in the configured mode                                **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : supervisedEntityId : A configured SE Id               **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : ptrSEIndex : Pointer to store SE Index                **
**                                                                            **
** Return parameter   : WDGM_TRUE: Found the configured SE Id                 **
**                      WDGM_FALSE: Not found the configured SE Id            **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                      WdgM_SupervisedEntity,                                **
**                      WdgM_TotalSEs                                         **
**                                                                            **
**                      Function(s) invoked : None                            **
*******************************************************************************/
/* @Trace: SRS_BSW_00327 SRS_BSW_00337 SRS_BSW_00385 SRS_BSW_00323 */
#define WDGM_START_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"
FUNC(boolean, WDGM_CODE) WdgM_SEIndexBinarySearch(
  VAR(WdgM_SupervisedEntityIdType, AUTOMATIC) supervisedEntityId,
  P2VAR(WdgM_SupervisedEntityIndexType, AUTOMATIC, WDGM_DATA) ptrSEIndex
)
{
  P2CONST(WdgM_SupervisedEntityType, AUTOMATIC, WDGM_CONST) ptrFirstSE;
  VAR(WdgM_SupervisedEntityIdType, AUTOMATIC) currentSEId;
  VAR(WdgM_SupervisedEntityIndexType, AUTOMATIC) totalSE;
  VAR(WdgM_SupervisedEntityIndexType, AUTOMATIC) lowIdx;
  VAR(WdgM_SupervisedEntityIndexType, AUTOMATIC) highIdx;
  VAR(WdgM_SupervisedEntityIndexType, AUTOMATIC) midIdx;
  VAR(boolean, AUTOMATIC) returnValue;

  /* @Trace: SafeWdgM_SUD_API_421 */
  /* If SE is configured then return the value true */
  returnValue = WDGM_FALSE;
  /* Get the pointer to previous mode array */
  ptrFirstSE = &WdgM_SupervisedEntity[WDGM_ZERO];
  /* Get the total SE's in the previous mode */
  totalSE = WdgM_TotalSEs;
  /* Initialize highIdx variable */
  highIdx = totalSE - WDGM_ONE;
  /* Initialize lowIdx variable with one */
  lowIdx = WDGM_ONE;
  /* Get the lower limit of SEID */
  currentSEId = ptrFirstSE->SEId;
  /* Check whether search SEID is in range */
  if ((supervisedEntityId >= currentSEId) && (supervisedEntityId <= ptrFirstSE[highIdx].SEId))
  {
    /* @Trace: SafeWdgM_SUD_API_422 */
    /* Check whether requested SEID is same as first SEID of the list */
    if (supervisedEntityId != currentSEId)
    {
      do
      {
        /* Get the middle index number */
        midIdx = (highIdx + lowIdx) >> WDGM_ONE;

        /* Get the SEID of the middle number */
        currentSEId = ptrFirstSE[midIdx].SEId;
        /* Compare SEID with the requested one */
        if (currentSEId == supervisedEntityId)
        {
          /* Update the return pointer with the middle index number */
          *ptrSEIndex = midIdx;
          /* Set highIdx to zero to break the loop */
          highIdx = WDGM_ZERO;
          /* If SE is configured then return the value true */
          returnValue = WDGM_TRUE;
        }
        else
        {
          /* Compare the SEID with the requested one */
          if (supervisedEntityId < currentSEId)
          { /* polyspace +2 DEFECT:UINT_OVFL CERT-C:INT30-C [Justified:high] "The generator had checked the value of the totalSE and the size of the SE array to guarantee index is in allowed range" */
            /* If the received SEID is lower, update highIdx */
            highIdx = midIdx - WDGM_ONE;
          }
          else
          {
            /* If the received SEID is higher, update lowIdx  */
            lowIdx  = midIdx + WDGM_ONE;
          }
        } /* End of the condition "If currentSEId equal to supervisedEntityId */
      } while (lowIdx  <= highIdx);
    } /* if(supervisedEntityId != currentSEId) */
    else
    {
      /* @Trace: SafeWdgM_SUD_API_423 */
      /* Update the return pointer with the actual SEID mapping structure */
      *ptrSEIndex = WDGM_ZERO;
      /* If SE is configured then return the value true */
      returnValue = WDGM_TRUE;
    }
  } /* if((supervisedEntityId >= currentSEId) &&... */
  /* @Trace: SafeWdgM_SUD_API_424 */
  /* Return pointer of SEID */
  return (returnValue);
}
#define WDGM_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"

/*******************************************************************************
** Function Name      : WdgM_InternalSetMode                                  **
**                                                                            **
** Service ID         : NA                                                    **
**                                                                            **
** Description        : This service performs the mode switch configured mode **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : modeIdx : Internal WdgM Mode                          **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : WDGM_TRUE: WdgIf_SetMode returns E_OK                 **
**                      WDGM_FALSE: WdgIf_SetMode returns E_NOT_OK            **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                      WdgM_PtrConfig                                        **
**                                                                            **
**                      Function(s) invoked :                                 **
**                      WdgIf_SetMode                                         **
*******************************************************************************/
/* @Trace: SRS_ModeMgm_09028 SRS_BSW_00171 SRS_ModeMgm_09110 SRS_BSW_00339 SRS_WdgM_CUS_00003 */
#define WDGM_START_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"
FUNC(boolean, WDGM_CODE) WdgM_InternalSetMode(
  VAR(CoreIdType, AUTOMATIC) coreId, 
  VAR(WdgM_ModeType, AUTOMATIC) modeIdx
)
{
  VAR(boolean, AUTOMATIC) setModeFailed;
  #if(WDGM_ENABLE_TRIGGER == STD_ON)
  P2CONST(WdgM_ModePropertyType, AUTOMATIC, WDGM_CONST) ptrMode;
  P2CONST(WdgM_TriggerType, AUTOMATIC, WDGM_CONST) ptrTriggers;
  /* Local variable for return value */
  VAR(Std_ReturnType, AUTOMATIC) returnValue;
  VAR(uint8, AUTOMATIC) counterTrigger;
  P2CONST(WdgM_ConfigType, AUTOMATIC, CONST) WdgM_PtrConfig;
  #else
  WDGM_UNUSED(coreId);
  WDGM_UNUSED(modeIdx);
  #endif

  /* @Trace: SafeWdgM_SUD_API_056 */
  setModeFailed = WDGM_FALSE;

  #if(WDGM_ENABLE_TRIGGER == STD_ON)
  /* @Trace: SafeWdgM_SUD_API_057 */
  WdgM_PtrConfig = GET_CONFIG_PTR(coreId);
  
  /* Get the pointer to Init mode array */
  ptrMode = &(WdgM_PtrConfig->PtrModes[modeIdx]);
  /* Get the pointer to watchdog trigger array */
  ptrTriggers = ptrMode->PtrTriggers;
  counterTrigger = WDGM_ZERO;
  /* Loop running through all configured watchdog drivers */
  while (counterTrigger < ptrMode->TotalTriggers)
  {
    /* Set the Watchdog mode for all the configured drivers */
    returnValue = WdgIf_SetMode(ptrTriggers[counterTrigger].WdgIfDeviceId,
      ptrTriggers[counterTrigger].WdgIfMode);
    if (returnValue == E_NOT_OK)
    {
      setModeFailed = WDGM_TRUE;
      counterTrigger = ptrMode->TotalTriggers;
    }
    else
    {
      counterTrigger++;
    }
  }
  #endif

  return (setModeFailed);
}
#define WDGM_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"

/*******************************************************************************
** Function Name      : WdgM_TriggerWdgIf                                     **
**                                                                            **
** Service ID         : NA                                                    **
**                                                                            **
** Description        : This service triggers all the internal watchdogs      **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : ptrMode : Pointer to a configuration set of a mode    **
**                      triggerMode : Type to trigger Wdg devices             **
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
**                      WdgM_DeInitTimeout                                    **
**                                                                            **
**                      Function(s) invoked:                                  **
**                      WdgIf_SetTriggerCondition                             **
*******************************************************************************/
/* @Trace: SRS_ModeMgm_09028 SRS_WdgM_CUS_00003 */
#if(WDGM_ENABLE_TRIGGER == STD_ON)
#define WDGM_START_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"
FUNC(void, WDGM_CODE) WdgM_TriggerWdgIf(
  VAR(CoreIdType, AUTOMATIC) coreId,
  P2CONST(WdgM_ModePropertyType, AUTOMATIC, WDGM_CONST) ptrMode,
  VAR(WdgM_TriggerModeType, AUTOMATIC) triggerMode
)
{
  P2CONST(WdgM_TriggerType, AUTOMATIC, WDGM_CONST) ptrTriggers;
  /* While loop index variable */
  VAR(uint8, AUTOMATIC) counterTrigger;
  
  /* @Trace: SafeWdgM_SUD_API_442 */
  ptrTriggers = ptrMode->PtrTriggers;
  counterTrigger = WDGM_ZERO;
  /* Loop running through all configured watchdog drivers to trigger
    with configured timeout value */
  while (counterTrigger < ptrMode->TotalTriggers)
  {
    if (ptrTriggers[counterTrigger].WdgIfMode != WDGIF_OFF_MODE)
    {
      switch (triggerMode)
      {
      case WDGM_TM_NORMAL:
        WdgIf_SetTriggerCondition(ptrTriggers[counterTrigger].WdgIfDeviceId,
          ptrTriggers[counterTrigger].WdgIfTimeout);
        break;
      case WDGM_TM_TIMEOUT:
        WdgIf_SetTriggerCondition(ptrTriggers[counterTrigger].WdgIfDeviceId,
          WDGM_ZERO);
        break;
      case WDGM_TM_DEINIT:
        WdgIf_SetTriggerCondition(ptrTriggers[counterTrigger].WdgIfDeviceId,
          WdgM_DeInitTimeout[coreId]);
        break;
      default:
        /* do nothing */
        break;
      }
    }
    /* Increment to next watchdog */
    counterTrigger++;
  }
}
#define WDGM_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"
#endif

/*******************************************************************************
** Function Name      : WdgM_ClearActivityFlag                                **
**                                                                            **
** Service ID         : NA                                                    **
**                                                                            **
** Description        : This service clears global variables                  **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : ptrCurrentMode : Pointer to a configuration set of a  **
**                                       mode                                 **
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
**                      WdgM_FirstExpSEIDStatus,                              **
**                      WdgM_FirstExpiredSEID,                                **
**                      WdgM_InvFirstExpiredSEID,                             **
**                      WdgM_FreeRunningCounter,                              **
**                      WdgM_FailedRefCycleCounter,                           **
**                      WdgM_AliveIndicationStatus,                           **
**                      WdgM_DeadlineSupervisionStatus,                       **
**                      WdgM_SupervisedEntity,                                **
**                      WdgM_IntLogicalSupervisionStatus,                     **
**                      WdgM_ExtLogicalSupervisionStatus                      **
**                                                                            **
**                      Function(s) invoked:                                  **
**                      SchM_Enter_WdgM_GLOBALSUPVSNSTATUS_PROTECTION,        **
**                      SchM_Exit_WdgM_GLOBALSUPVSNSTATUS_PROTECTION          **
*******************************************************************************/
/* @Trace: SRS_BSW_00171 SRS_ModeMgm_09107 SRS_BSW_00323 */
#define WDGM_START_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"
FUNC(void, WDGM_CODE) WdgM_ClearActivityFlag(
  VAR(CoreIdType, AUTOMATIC) coreId, 
  P2CONST(WdgM_ModePropertyType, AUTOMATIC, WDGM_CONST) ptrCurrentMode
)
{
  #if ((WDGM_ENABLE_ALIVE_SUPERVISION == STD_ON) || \
    (WDGM_ENABLE_DEADLINE_SUPERVISION == STD_ON) || \
    (WDGM_ENABLE_INTERNAL_TRANSITION == STD_ON) || \
    (WDGM_ENABLE_EXTERNAL_TRANSITION == STD_ON))
  VAR(uint16, AUTOMATIC) count;
  #endif
  #if(WDGM_ENABLE_ALIVE_SUPERVISION == STD_ON)
  P2VAR(WdgM_ExAliveIndicationsCountType, AUTOMATIC, WDGM_APPL_DATA) ptrAliveIndicationStatus;
  #endif
  #if(WDGM_ENABLE_INTERNAL_TRANSITION == STD_ON)
  VAR(WdgM_IntLogicSupStatArrIndexType, AUTOMATIC) iLSIndex;
  VAR(WdgM_IntLogicSupStatArrIndexType, AUTOMATIC) iLSCounter;
  P2CONST(WdgM_IntLSGraphArrayType, AUTOMATIC, WDGM_CONST) ptrIntLSGraphArray;
  VAR(uint16, AUTOMATIC) numberOfInternalGraph;
  P2VAR(WdgM_IntLogicalSupervisionStatusType, AUTOMATIC, WDGM_DATA) ptrIntLogicalSupervisionStatus;
  #endif
  
  #if(WDGM_ENABLE_EXTERNAL_TRANSITION == STD_ON)
  P2VAR(WdgM_ExtLogicalSupervisionStatusType, AUTOMATIC, WDGM_DATA) ptrExtLogicalSupervisionStatus;
  #endif
  
  #if(WDGM_ENABLE_DEADLINE_SUPERVISION == STD_ON)
  P2VAR(WdgM_DeadlineSupervisionStatusType, AUTOMATIC, WDGM_DATA) ptrDeadlineSupervisionStatus;
  #endif
  
  #if((WDGM_ENABLE_ALIVE_SUPERVISION == STD_ON) || \
    (WDGM_ENABLE_INTERNAL_TRANSITION == STD_ON))
  P2CONST(WdgM_ActiveSEType, AUTOMATIC, WDGM_CONST) ptrActiveSE;
  VAR(WdgM_SupervisedEntityIndexType, AUTOMATIC) supervisedEntityIdx;
  #endif

  /* @Trace: SafeWdgM_SUD_API_042 */
  #if ((WDGM_ENABLE_ALIVE_SUPERVISION == STD_OFF) && \
    (WDGM_ENABLE_DEADLINE_SUPERVISION == STD_OFF) && \
    (WDGM_ENABLE_INTERNAL_TRANSITION == STD_OFF) && \
    (WDGM_ENABLE_EXTERNAL_TRANSITION == STD_OFF))
    WDGM_UNUSED_PTR(ptrCurrentMode);
    WDGM_UNUSED(coreId);
  #endif

  #if((WDGM_ENABLE_ALIVE_SUPERVISION == STD_ON) || \
    (WDGM_ENABLE_INTERNAL_TRANSITION == STD_ON))
  ptrActiveSE = ptrCurrentMode->PtrActiveSEList;
  #endif
  #if(WDGM_ENABLE_ALIVE_SUPERVISION == STD_ON)
  /* Set the count to total number of active SE's configured in the
    current mode */
  count = ptrCurrentMode->TotalSEInMode;
  while(count != WDGM_ZERO)
  {
    count--;
    supervisedEntityIdx = ptrActiveSE[count].SEArrayIndex;
    /* Set the failure cycle count for the corresponding alive supervision
      to WDGM_ZERO */
    *(WdgM_FailedRefCycleCounter[supervisedEntityIdx]) = WDGM_ZERO;
  }
  #endif

  SchM_Enter_WdgM_GLOBALSUPVSNSTATUS_PROTECTION();
  #if(WDGM_ENABLE_ALIVE_SUPERVISION == STD_ON)
  ptrAliveIndicationStatus = WDGM_GET_ALIVE_INDICATION_STATUS_PTR(coreId);
  /* Clear the Free running counter */
  WDGM_WRITE_FREE_RUNNING_COUNTER(coreId, (uint32)WDGM_ZERO);
  /* Set the count to total number of alive supervisions configured in
    the current mode */
  count = ptrCurrentMode->TotalAliveSupervisions;
  while(count != WDGM_ZERO)
  {
    count--;
    /* Set the alive indication count for the corresponding alive supervision
      to WDGM_ZERO */
    ptrAliveIndicationStatus[count] = WDGM_ZERO;
  }
  #endif

  #if(WDGM_ENABLE_DEADLINE_SUPERVISION == STD_ON)
  /* Set the count to total number of deadline supervisions configured
    in the current mode */
  count = ptrCurrentMode->TotalDeadlineSupervisions;
  while(count != WDGM_ZERO)
  {
    count--;
    ptrDeadlineSupervisionStatus = WDGM_GET_DEADLINE_SUPERVISON_STATUS_PTR(coreId, count);
    /* Set the Deadline supervision status count for the corresponding Deadline
    supervision to WDGM_ZERO */
    ptrDeadlineSupervisionStatus->TickValue = WDGM_ZERO;
    /* Set the Deadline supervision status for the corresponding Deadline
    supervision to WDGM_DS_NOT_STARTED */
    ptrDeadlineSupervisionStatus->DSStatus = WDGM_DS_NOT_STARTED;
  }
  #endif
  
  /* @Trace: SafeWdgM_SUD_API_043 */
  #if(WDGM_ENABLE_INTERNAL_TRANSITION == STD_ON)
  /* Set the count to total number of active SE's configured in the
    current mode */
  count = ptrCurrentMode->TotalSEInMode;
  while(count != WDGM_ZERO)
  {
    count--;
    supervisedEntityIdx = ptrActiveSE[count].SEArrayIndex;
    numberOfInternalGraph = WdgM_SupervisedEntity[supervisedEntityIdx].NumberOfInternalGraph;
    for (iLSCounter = WDGM_ZERO; iLSCounter < numberOfInternalGraph; iLSCounter++)
    {
        ptrIntLSGraphArray = WdgM_SupervisedEntity[supervisedEntityIdx].PtrIntLSGraphArray;
        iLSIndex = ptrIntLSGraphArray[iLSCounter].ILSIndex;
        ptrIntLogicalSupervisionStatus = WDGM_GET_INTLOGICAL_SUPERVISON_STATUS_PTR(coreId, iLSIndex);
        /* Set the last reported CP of the corresponding internal logical
          supervision in the SE to WDGM_ZERO */
        ptrIntLogicalSupervisionStatus->LastReportedCP
          = WDGM_ZERO;
        /* Set the activity flag of the corresponding internal logical supervision
          in the SE to WDGM_FALSE */
        ptrIntLogicalSupervisionStatus->ActivityFlag
          = WDGM_FALSE;
    }
  }
  #endif
  
  /* @Trace: SafeWdgM_SUD_API_067 */
  #if(WDGM_ENABLE_EXTERNAL_TRANSITION == STD_ON)
  /* Set the count to total number of external logical supervisions configured
    in the current mode */
  count = ptrCurrentMode->TotalExLogicalSupervisions;
  while(count != WDGM_ZERO)
  {
    count--;
    ptrExtLogicalSupervisionStatus = WDGM_GET_EXTLOGICAL_SUPERVISON_STATUS_PTR(coreId,count);
    /* Set the last reported reported SE/CP of the corresponding external
      logical supervision in the SE to WDGM_ZERO */
    ptrExtLogicalSupervisionStatus->LastRepExLSGraphArrIdx = WDGM_ZERO;
    /* Set the activity flag of the corresponding external logical supervision
      to WDGM_FALSE */
    ptrExtLogicalSupervisionStatus->ActivityFlag = WDGM_FALSE;
  }
  #endif

  SchM_Exit_WdgM_GLOBALSUPVSNSTATUS_PROTECTION();
}
#define WDGM_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"

/*******************************************************************************
** Function Name      : WdgM_PerformAliveIndication                           **
**                                                                            **
** Service ID         : NA                                                    **
**                                                                            **
** Description        : This service increases the alive indication of alive  **
**                      supervisions configured                               **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : supervisedEntityId : Supervised Entity Id to perform  **
**                                           Alive Indication                 **
**                      cpId : Checkpoint Id of a Supervised Entity           **
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
**                      WdgM_PtrConfig,                                       **
**                      WdgM_CurrentMode,                                     **
**                      WdgM_AliveIndicationStatus                            **
**                                                                            **
**                      Function(s) invoked:                                  **
**                      SchM_Enter_WdgM_GLOBALSUPVSNSTATUS_PROTECTION,        **
**                      SchM_Exit_WdgM_GLOBALSUPVSNSTATUS_PROTECTION          **
*******************************************************************************/
/* @Trace: WdgM_SRS_SWS_00321 */
#if(WDGM_ENABLE_ALIVE_SUPERVISION == STD_ON)
#define WDGM_START_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"
FUNC(void, WDGM_CODE) WdgM_PerformAliveIndication(
  VAR(CoreIdType, AUTOMATIC) coreId, 
  VAR(WdgM_SupervisedEntityIdType, AUTOMATIC) supervisedEntityId, 
  VAR(WdgM_CheckpointIdType, AUTOMATIC) cpId,
  VAR(WdgM_ModeType, AUTOMATIC) currentMode
)
{
  /* Local pointer for the pointing to the current mode */
  P2CONST(WdgM_ModePropertyType, AUTOMATIC, WDGM_CONST)ptrModes;
  /* Local pointer for the pointing to alive supervision array */
  P2CONST(WdgM_AliveSupervisionType, AUTOMATIC, WDGM_CONST) ptrAliveSupervisions;
  /* Local variable for total alive supervisions in the current mode */
  VAR(uint16, AUTOMATIC) totalAliveSupervisions;
  VAR(uint16, AUTOMATIC) idx;
  P2CONST(WdgM_ConfigType, AUTOMATIC, CONST) WdgM_PtrConfig;
  P2VAR(WdgM_ExAliveIndicationsCountType, AUTOMATIC, WDGM_APPL_DATA) ptrAliveIndicationStatus;

  /* @Trace: SafeWdgM_SUD_API_450 */
  WdgM_PtrConfig = GET_CONFIG_PTR(coreId);
  
  ptrModes = &(WdgM_PtrConfig->PtrModes[currentMode]);
  ptrAliveSupervisions = ptrModes->PtrAliveSupervisions;
  totalAliveSupervisions = ptrModes->TotalAliveSupervisions;
  ptrAliveIndicationStatus = WDGM_GET_ALIVE_INDICATION_STATUS_PTR(coreId);

  idx = WDGM_ZERO;
  /* Match SE and CP in AliveSupervisions list */
  while (idx < totalAliveSupervisions)
  {
    if ((supervisedEntityId == ptrAliveSupervisions[idx].SEId)
      && (cpId == ptrAliveSupervisions[idx].Checkpoint))
    {
      SchM_Enter_WdgM_GLOBALSUPVSNSTATUS_PROTECTION();
      /* Update alive counters */
      ptrAliveIndicationStatus[idx]++;
      SchM_Exit_WdgM_GLOBALSUPVSNSTATUS_PROTECTION();
      idx = totalAliveSupervisions;
    }
    idx++;
  }
}
#define WDGM_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"

/*******************************************************************************
** Function Name      : WdgM_PerformAliveSupervision                          **
**                                                                            **
** Service ID         : NA                                                    **
**                                                                            **
** Description        : This service evaluates the result of all the alive    **
**                      supervisions configured                               **
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
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                      WdgM_PtrConfig,                                       **
**                      WdgM_CurrentMode,                                     **
**                      WdgM_FreeRunningCounter,                              **
**                      WdgM_AlreadyUpdated,                                  **
**                      WdgM_AliveIndicationStatus,                           **
**                      WdgM_SEStatus,                                        **
**                      WdgM_TotalSEs                                         **
**                                                                            **
**                      Function(s) invoked:                                  **
**                      SchM_Enter_WdgM_GLOBALSUPVSNSTATUS_PROTECTION,        **
**                      SchM_Exit_WdgM_GLOBALSUPVSNSTATUS_PROTECTION          **
*******************************************************************************/
/* @Trace: SRS_ModeMgm_09112 SRS_ModeMgm_09143 */
#define WDGM_START_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"
FUNC(void, WDGM_CODE) WdgM_PerformAliveSupervision(
  VAR(CoreIdType, AUTOMATIC) coreId
)
{
  P2CONST(WdgM_ModePropertyType, AUTOMATIC, WDGM_CONST) ptrCurrentMode;
  P2CONST(WdgM_AliveSupervisionType, AUTOMATIC, WDGM_CONST) ptrAliveSupervisions;
  WdgM_SupervisedEntityIndexType supervisedEntityIdx;
  VAR(uint16, AUTOMATIC) totalAliveSupervisions;
  VAR(uint16, AUTOMATIC) idx;
  WdgM_ExAliveIndicationsCountType exAliveIndicationCount;
  P2CONST(WdgM_ConfigType, AUTOMATIC, CONST) WdgM_PtrConfig;
  VAR(uint8, AUTOMATIC) seStatus;
  P2VAR(uint32, AUTOMATIC, WDGM_APPL_DATA) ptrFreeRunningCounter;
  P2VAR(WdgM_ExAliveIndicationsCountType, AUTOMATIC, WDGM_APPL_DATA) ptrAliveIndicationStatus;

  /* @Trace: SafeWdgM_SUD_API_058 */
  WdgM_PtrConfig = GET_CONFIG_PTR(coreId);
  
  /* Get the pointer to current mode array */
  ptrCurrentMode = &(WdgM_PtrConfig->PtrModes[WDGM_READ_CURRENT_MODE(coreId)]);
  ptrFreeRunningCounter = WDGM_GET_FREE_RUNNING_COUNTER_PTR(coreId);
  ptrAliveIndicationStatus = WDGM_GET_ALIVE_INDICATION_STATUS_PTR(coreId);

  if (*ptrFreeRunningCounter == WdgM_PtrConfig->MaxAliveSupervisionRefCycle)
  {
    
    *ptrFreeRunningCounter = WDGM_ZERO;
  }
  /* @Trace: SafeWdgM_SUD_API_059 */
  /* Increment free running timer */
  (*ptrFreeRunningCounter)++;
  
  /* Get the number of alive supervision's in the current mode */
  totalAliveSupervisions = ptrCurrentMode->TotalAliveSupervisions;
  /* Get the pointer to the Alive supervision's in the current mode */
  ptrAliveSupervisions = ptrCurrentMode->PtrAliveSupervisions;
  idx = WDGM_ZERO;
  
  /* Set the flags of updating status to WDGM_FALSE */
  while (idx < totalAliveSupervisions)
  {
    /* To clear updated flag for all activated SE in current mode 
       of a corresponding coreId */
    supervisedEntityIdx = ptrAliveSupervisions[idx].SEArrayIndex;
    (*(WdgM_AlreadyUpdated[supervisedEntityIdx])) = WDGM_FALSE;
    idx++;
  }
  /* Set the index to WDGM_ZERO */
  idx = WDGM_ZERO;
  /* Match SE and CP in AliveSupervisions list */
  while (idx < totalAliveSupervisions)
  {
    /* @Trace: SafeWdgM_SUD_API_060 */
    supervisedEntityIdx = ptrAliveSupervisions[idx].SEArrayIndex;
    seStatus = WDGM_READ_SE_STATUS(supervisedEntityIdx);
    if ((seStatus & WDGM_STATUS_MASK) != WDGM_LOCAL_STATUS_DEACTIVATED)
    {
      if ((ptrAliveSupervisions[idx].SupervisionRefCycle >= WDGM_ONE)
        && (((*ptrFreeRunningCounter)
        % (ptrAliveSupervisions[idx].SupervisionRefCycle)) == WDGM_ZERO))
      {
        /* @Trace: SafeWdgM_SUD_API_061 */
        SchM_Enter_WdgM_GLOBALSUPVSNSTATUS_PROTECTION();
        
        /* Check whether the required number of alive indications has
          occurred */
        exAliveIndicationCount = ptrAliveIndicationStatus[idx];
        if ((exAliveIndicationCount
          <= ((ptrAliveSupervisions[idx].ExAliveIndications)
          + (ptrAliveSupervisions[idx].ExAliveIndMaxMargin)))
          && (exAliveIndicationCount
          >= ((ptrAliveSupervisions[idx].ExAliveIndications)
          - (ptrAliveSupervisions[idx].ExAliveIndMinMargin))))
        {
          /* Set the result if only SE status's not updated ever */
          if ((*(WdgM_AlreadyUpdated[supervisedEntityIdx])) == WDGM_FALSE)
          {
            /* Update AI result as CORRECT */
            WDGM_WRITE_SE_STATUS(supervisedEntityIdx,
              (seStatus | WDGM_ALIVESUPERVISION_CORRECT));
          }
        }
        else
        {
          /* Set the flag to WDGM_TRUE */
          (*(WdgM_AlreadyUpdated[supervisedEntityIdx])) = WDGM_TRUE;
          /* Update AI result as INCORRECT*/
          WDGM_WRITE_SE_STATUS(supervisedEntityIdx, seStatus
            & WDGM_ALIVESUPERVISION_INCORRECT);
        }
        /* Expected alive indication value is reset to WDGM_ZERO */
        ptrAliveIndicationStatus[idx] = WDGM_ZERO;
        
        SchM_Exit_WdgM_GLOBALSUPVSNSTATUS_PROTECTION();
      }
    }
    /* @Trace: SafeWdgM_SUD_API_062 */
    idx++;
  } /* index < totalAliveSupervisions */
}
#define WDGM_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"
#endif

/*******************************************************************************
** Function Name      : WdgM_PerformDeadlineSupervision                       **
**                                                                            **
** Service ID         : NA                                                    **
**                                                                            **
** Description        : This service performs deadline supervision for the    **
**                      requested checkpoint                                  **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : supervisedEntityId : Supervised Entity Id to perform  **
**                                           Deadline Supervision             **
**                      cpId : Checkpoint Id of a Supervised Entity           **
**                      supervisedEntityIdx: Index of Supervised Entity in    **
**                                           Global Supervised Entity array   **
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
**                      WdgM_PtrConfig,                                       **
**                      WdgM_CurrentMode,                                     **
**                      WdgM_SEStatus,                                        **
**                      WdgM_DeadlineSupervisionStatus,                       **
**                                                                            **
**                      Function(s) invoked:                                  **
**                      GetCounterValue,                                      **
**                      GetElapsedValue,                                      **
**                      SchM_Enter_WdgM_GLOBALSUPVSNSTATUS_PROTECTION,        **
**                      SchM_Exit_WdgM_GLOBALSUPVSNSTATUS_PROTECTION          **
*******************************************************************************/
/* @Trace: SRS_WdgM_CUS_00007 */
#if(WDGM_ENABLE_DEADLINE_SUPERVISION == STD_ON)
#define WDGM_START_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"
FUNC(void, WDGM_CODE) WdgM_PerformDeadlineSupervision(
  VAR(CoreIdType, AUTOMATIC) coreId, 
  VAR(WdgM_SupervisedEntityIdType, AUTOMATIC) supervisedEntityId, 
  VAR(WdgM_CheckpointIdType, AUTOMATIC) cpId,
  VAR(WdgM_SupervisedEntityIndexType, AUTOMATIC) supervisedEntityIdx,
  VAR(WdgM_ModeType, AUTOMATIC) currentMode
)
{
  P2CONST(WdgM_ModePropertyType, AUTOMATIC, WDGM_CONST) ptrModes;
  P2CONST(WdgM_DeadlineSupervisionType, AUTOMATIC, WDGM_CONST)
    ptrDeadlineSupervisions;
  P2VAR(WdgM_DeadlineSupervisionStatusType, AUTOMATIC, WDGM_DATA)
    ptrDeadlineSupervisionStatus;
  P2CONST(WdgM_SupervisedEntityType, AUTOMATIC, WDGM_CONST)
    ptrSupervisedEntity;
  VAR(uint16, AUTOMATIC) totalDeadlineSupervisions;
  VAR(uint16, AUTOMATIC) idx;
  VAR(TickType, AUTOMATIC) tickValue;
  VAR(TickType, AUTOMATIC) elapsedTickValue;
  VAR(StatusType, AUTOMATIC) statusReturn;
  P2CONST(WdgM_ConfigType, AUTOMATIC, CONST) WdgM_PtrConfig;
  VAR(uint8, AUTOMATIC) seStatus;

  /* @Trace: SafeWdgM_SUD_API_063 */
  WdgM_PtrConfig = GET_CONFIG_PTR(coreId);
  seStatus = WDGM_READ_SE_STATUS(supervisedEntityIdx);

  if ((seStatus & WDGM_DEADLINESUPERVISION_CORRECT)
    == WDGM_DEADLINESUPERVISION_CORRECT)
  {
    ptrModes = &(WdgM_PtrConfig->PtrModes[currentMode]);
    totalDeadlineSupervisions = ptrModes->TotalDeadlineSupervisions;
    ptrDeadlineSupervisions = ptrModes->PtrDeadlineSupervisions;
    ptrSupervisedEntity = &WdgM_SupervisedEntity[supervisedEntityIdx];
    idx = WDGM_ZERO;
    tickValue = WDGM_ZERO;
    elapsedTickValue = WDGM_ZERO;
    while (idx < totalDeadlineSupervisions)
    {
      /* @Trace: SafeWdgM_SUD_API_352 */
      if (supervisedEntityId == ptrDeadlineSupervisions[idx].SEId)
      {
        ptrDeadlineSupervisionStatus
          = WDGM_GET_DEADLINE_SUPERVISON_STATUS_PTR(coreId, idx);
        if (cpId
          == ptrDeadlineSupervisions[idx].InitialCheckpoint)
        {
          /* @Trace: SafeWdgM_SUD_API_353 */
          statusReturn = GetCounterValue(ptrSupervisedEntity->CounterID,
            &tickValue);
          /* polyspace-begin DEFECT:DEAD_CODE MISRA2012:2.1,14.3 [Not a defect:Low] "It's not a dead-code, it's required to update SE Status when there is something wrong returned from OS during runtime" */
          if (E_OK != statusReturn)
          {
            seStatus &= WDGM_DEADLINESUPERVISION_INCORRECT;
          }
          /* polyspace-end DEFECT:DEAD_CODE MISRA2012:2.1,14.3 [Not a defect:Low] */
          else
          {
            SchM_Enter_WdgM_GLOBALSUPVSNSTATUS_PROTECTION();
            ptrDeadlineSupervisionStatus->TickValue = tickValue;
            /* Set Monitoring status as started */
            ptrDeadlineSupervisionStatus->DSStatus = WDGM_DS_STARTED;
            SchM_Exit_WdgM_GLOBALSUPVSNSTATUS_PROTECTION();
          }
        }
        else if (cpId
          == ptrDeadlineSupervisions[idx].FinalCheckpoint)
        {
          /* @Trace: SafeWdgM_SUD_API_358 */
          if (ptrDeadlineSupervisionStatus->DSStatus == WDGM_DS_STARTED)
          {
            tickValue = ptrDeadlineSupervisionStatus->TickValue;
            statusReturn = GetElapsedValue(ptrSupervisedEntity->CounterID,
              &tickValue, &elapsedTickValue);
              
            SchM_Enter_WdgM_GLOBALSUPVSNSTATUS_PROTECTION();
            
            /* Set Monitoring status as not started */
            ptrDeadlineSupervisionStatus->DSStatus = WDGM_DS_NOT_STARTED;
            
            /* @Trace: SafeWdgM_SUD_API_360 */
            /* polyspace-begin DEFECT:DEAD_CODE MISRA2012:2.1,14.3 [Not a defect:Low] "It's not a dead-code, it's required to update SE Status when there is something wrong returned from OS during runtime" */
            if (E_OK != statusReturn)
            {
                seStatus &= WDGM_DEADLINESUPERVISION_INCORRECT;
            }
            /* polyspace-end DEFECT:DEAD_CODE MISRA2012:2.1,14.3 [Not a defect:Low] */
            else
            {
              if ((elapsedTickValue <= ptrDeadlineSupervisions[idx].DeadlineMax)
                && (elapsedTickValue >= ptrDeadlineSupervisions[idx].DeadlineMin))
              {
                /* Clear Time-Stamp */
                ptrDeadlineSupervisionStatus->TickValue = WDGM_ZERO;
                /* Set DS result as WDGM_DEADLINESUPERVISION_CORRECT */
                  seStatus |= WDGM_DEADLINESUPERVISION_CORRECT;
              }
              else
              {
                  seStatus &= WDGM_DEADLINESUPERVISION_INCORRECT;
              }
            }
            SchM_Exit_WdgM_GLOBALSUPVSNSTATUS_PROTECTION();
          }
        }
        else
        {
        }
      }
      /* @Trace: SafeWdgM_SUD_API_362 */
      idx++;
    } /* index < totalDeadlineSupervisions */
    /* @Trace: SafeWdgM_SUD_API_363 */
    SchM_Enter_WdgM_GLOBALSUPVSNSTATUS_PROTECTION();
    
    WDGM_WRITE_SE_STATUS(supervisedEntityIdx, seStatus);
    
    SchM_Exit_WdgM_GLOBALSUPVSNSTATUS_PROTECTION();
  }

}
#define WDGM_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"
#endif

/*******************************************************************************
** Function Name      : WdgM_PerformIntLogicalSupervision                     **
**                                                                            **
** Service ID         : NA                                                    **
**                                                                            **
** Description        : This service performs internal logical supervision    **
**                      for the requested checkpoint                          **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : cpId : Checkpoint Id of a Supervised Entity           **
**                      supervisedEntityIdx: Index of Supervised Entity in    **
**                                           Global Supervised Entity array   **
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
**                      WdgM_SEStatus,                                        **
**                      WdgM_SupervisedEntity,                                **
**                      WdgM_IntLogicalSupervisionStatus                      **
**                                                                            **
**                      Function(s) invoked:                                  **
**                      SchM_Enter_WdgM_GLOBALSUPVSNSTATUS_PROTECTION,        **
**                      SchM_Exit_WdgM_GLOBALSUPVSNSTATUS_PROTECTION          **
*******************************************************************************/
/* @Trace: SRS_ModeMgm_09225 SRS_ModeMgm_09221 SRS_ModeMgm_09222 */
#if(WDGM_ENABLE_INTERNAL_TRANSITION == STD_ON)
#define WDGM_START_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"
FUNC(void, WDGM_CODE) WdgM_PerformIntLogicalSupervision(
  VAR(CoreIdType, AUTOMATIC) coreId, 
  VAR(WdgM_CheckpointIdType, AUTOMATIC) cpId,
  VAR(WdgM_SupervisedEntityIndexType, AUTOMATIC) supervisedEntityIdx
)
{
  P2CONST(WdgM_SupervisedEntityType, AUTOMATIC, WDGM_CONST) ptrSupervisedEntity;
  P2CONST(WdgM_CheckpointIdType, AUTOMATIC, WDGM_CONST) ptrIntLSGraphMapArray;
  P2CONST(WdgM_IntLSGraphArrayType, AUTOMATIC, WDGM_CONST) ptrIntLSGraphArray;
  P2CONST(WdgM_CheckpointGraphType, AUTOMATIC, WDGM_CONST) ptrCheckpoint;
  P2CONST(WdgM_CheckpointGraphType, AUTOMATIC, WDGM_CONST) ptrLastReportedCP;
  P2VAR(WdgM_IntLogicalSupervisionStatusType, AUTOMATIC, WDGM_DATA)
    ptrIntLogicalSupervisionStatus;
  WdgM_CpMapArrayIndexType cpMapArrayIndex;
  VAR(uint8, AUTOMATIC) maxBranches;
  VAR(boolean, AUTOMATIC) found;
  VAR(uint8, AUTOMATIC) seStatus;
  
  /* @Trace: SafeWdgM_SUD_API_390 */
  seStatus = WDGM_READ_SE_STATUS(supervisedEntityIdx);
  if ((seStatus & WDGM_LGSUPERVISION_CORRECT) == WDGM_LGSUPERVISION_CORRECT)
  {
    ptrSupervisedEntity = &WdgM_SupervisedEntity[supervisedEntityIdx];
    /* Connect to CP properties */
    ptrCheckpoint = &((ptrSupervisedEntity->PtrCheckpoint)[cpId]);
    ptrIntLSGraphArray = ptrSupervisedEntity->PtrIntLSGraphArray;

    /* Check whether the checkpoint is configured for internal LS */
    if ((ptrIntLSGraphArray != NULL_PTR)
      && ((ptrCheckpoint->MaxBranches != WDGM_ZERO)
      || (ptrCheckpoint->CpType != WDGM_CP_BI)))
    {
        ptrIntLSGraphMapArray = ptrIntLSGraphArray[ptrCheckpoint->GraphIdx].PtrIntLSGraphMapArray;
      /* Access ILS Status Array */
      ptrIntLogicalSupervisionStatus = 
        WDGM_GET_INTLOGICAL_SUPERVISON_STATUS_PTR(coreId, ptrIntLSGraphArray[ptrCheckpoint->GraphIdx].ILSIndex);

      SchM_Enter_WdgM_GLOBALSUPVSNSTATUS_PROTECTION();
      
      /* @Trace: SafeWdgM_SUD_API_396 */
      /* Expecting an initial checkpoint */
      if (ptrIntLogicalSupervisionStatus->ActivityFlag == WDGM_FALSE)
      {
        if (ptrCheckpoint->CpType == WDGM_CP_INITIAL)
        {
          ptrIntLogicalSupervisionStatus->ActivityFlag = WDGM_TRUE;
          /* Update last reported CP */
          ptrIntLogicalSupervisionStatus->LastReportedCP = cpId;
          /* Set ILS result as WDGM_LGSUPERVISION_CORRECT */
          WDGM_WRITE_SE_STATUS(supervisedEntityIdx, seStatus
            | WDGM_LGSUPERVISION_CORRECT);
        }
        else
        {
          /* Set ILS result as WDGM_LGSUPERVISION_INCORRECT */
          WDGM_WRITE_SE_STATUS(supervisedEntityIdx, seStatus
            & WDGM_LGSUPERVISION_INCORRECT);
        }
      }
      /* Expecting a successor */
      else
      {
        /* Access property of last reported CP */
        ptrLastReportedCP = &((ptrSupervisedEntity->PtrCheckpoint)
          [ptrIntLogicalSupervisionStatus->LastReportedCP]);
        /* Get the map array index of Last Reported CP */
        cpMapArrayIndex = ptrLastReportedCP->CpMapArrayIndex;
        /* Get the maximum branches available for Last Reported CP */
        maxBranches = ptrLastReportedCP->MaxBranches;
        found = WDGM_FALSE;
        while (maxBranches != WDGM_ZERO)
        {
          /* @Trace: SafeWdgM_SUD_API_400 */
          /* Check whether the new CP is a successor of the stored CP */
          if (cpId == ptrIntLSGraphMapArray[cpMapArrayIndex])
          {
            /* Update ILS result */
            WDGM_WRITE_SE_STATUS(supervisedEntityIdx,
              seStatus | WDGM_LGSUPERVISION_CORRECT);
            /* Break the loop */
            maxBranches = WDGM_ZERO;
            found = WDGM_TRUE;
          }
          else
          {
            cpMapArrayIndex++;
            maxBranches--;
          }
        }
        
        /* @Trace: SafeWdgM_SUD_API_408 */
        if (found == WDGM_TRUE)
        {
          if (ptrCheckpoint->CpType == WDGM_CP_FINAL)
          {
            ptrIntLogicalSupervisionStatus->ActivityFlag = WDGM_FALSE;
          }
          else
          {
            /* Update last reported CP */
            ptrIntLogicalSupervisionStatus->LastReportedCP = cpId;
          }
        }
        else
        {
          /* Set ILS result as WDGM_LGSUPERVISION_INCORRECT */
          WDGM_WRITE_SE_STATUS(supervisedEntityIdx, seStatus
            & WDGM_LGSUPERVISION_INCORRECT);
        }
      } /* ptrIntLogicalSupervisionStatus->ActivityFlag != WDGM_FALSE */
      
      SchM_Exit_WdgM_GLOBALSUPVSNSTATUS_PROTECTION();
    } /* (ptrIntLSGraphArray != NULL_PTR) &&.... */
  }
}
#define WDGM_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"
#endif

/*******************************************************************************
** Function Name      : WdgM_PerformExtLogicalSupervision                     **
**                                                                            **
** Service ID         : NA                                                    **
**                                                                            **
** Description        : This service performs external logical supervision    **
**                      for the requested checkpoint                          **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : supervisedEntityId : Supervised Entity Id to perform  **
**                                           External Logical Supervision     **
**                      cpId : Checkpoint Id of a Supervised Entity           **
**                      supervisedEntityIdx: Index of Supervised Entity in    **
**                                           Global Supervised Entity array   **
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
**                      WdgM_SEStatus,                                        **
**                      WdgM_PtrConfig,                                       **
**                      WdgM_CurrentMode,                                     **
**                      WdgM_ExtLogicalSupervisionStatus                      **
**                                                                            **
**                      Function(s) invoked:                                  **
**                      SchM_Enter_WdgM_GLOBALSUPVSNSTATUS_PROTECTION,        **
**                      SchM_Exit_WdgM_GLOBALSUPVSNSTATUS_PROTECTION          **
*******************************************************************************/
/* @Trace: SRS_ModeMgm_09225 SRS_ModeMgm_09221 SRS_ModeMgm_09222 */
#if(WDGM_ENABLE_EXTERNAL_TRANSITION == STD_ON)
#define WDGM_START_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"
FUNC(void, WDGM_CODE) WdgM_PerformExtLogicalSupervision(
  VAR(CoreIdType, AUTOMATIC) coreId, 
  VAR(WdgM_SupervisedEntityIdType, AUTOMATIC) supervisedEntityId,
  VAR(WdgM_CheckpointIdType, AUTOMATIC) cpId,
  VAR(WdgM_SupervisedEntityIndexType, AUTOMATIC) supervisedEntityIdx,
  VAR(WdgM_ModeType, AUTOMATIC) currentMode
)
{
  P2CONST(WdgM_ModePropertyType, AUTOMATIC, WDGM_CONST) ptrModes;
  P2CONST(WdgM_ExLSGraphType, AUTOMATIC, WDGM_CONST) ptrExLSGraph;
  P2CONST(WdgM_ExLSGraphType, AUTOMATIC, WDGM_CONST) ptrLastRepExLSGraph;
  P2CONST(WdgM_ExLogicalSupervisionType, AUTOMATIC, WDGM_CONST)
    ptrExLogicalSupervision;
  P2VAR(WdgM_ExtLogicalSupervisionStatusType, AUTOMATIC, WDGM_DATA)
    ptrExtLogicalSupervisionStatus;
  P2CONST(WdgM_ExLSGraphMapArrayType, AUTOMATIC, WDGM_CONST)
    ptrExLSGraphMapArray;
  VAR(WdgM_CpMapArrayIndexType, AUTOMATIC) cpMapArrayIndex;
  VAR(WdgM_ExLSGraphArrayType, AUTOMATIC) exLSGraphArrayIndex;
  VAR(uint16, AUTOMATIC) exLSIndex;
  VAR(uint8, AUTOMATIC) maxBranches;
  VAR(boolean, AUTOMATIC) validExLSCp;
  VAR(boolean, AUTOMATIC) found;
  P2CONST(WdgM_ConfigType, AUTOMATIC, CONST) WdgM_PtrConfig;
  VAR(uint8, AUTOMATIC) seStatus;

  /* @Trace: SafeWdgM_SUD_API_364 */
  WdgM_PtrConfig = GET_CONFIG_PTR(coreId);

  /*Initialize Variables*/
  seStatus = WDGM_READ_SE_STATUS(supervisedEntityIdx);

  if ((seStatus & WDGM_LGSUPERVISION_CORRECT) == WDGM_LGSUPERVISION_CORRECT)
  {
    /* Initialize ExLS Status Array Index */
    ptrModes = &(WdgM_PtrConfig->PtrModes[currentMode]);
    /* Available logical supervisions in a mode */
    ptrExLogicalSupervision = ptrModes->PtrExLogicalSupervisions;
    validExLSCp = WdgM_GetExtLSIndex(ptrModes, &exLSIndex, 
                    &exLSGraphArrayIndex, supervisedEntityId, cpId);

    /* Ignore the CheckpointReached function call in case of an
      invalid ExLS CP (CP is not configured for ExLS) */
    /* @Trace: SafeWdgM_SUD_API_376 */
    if (validExLSCp == WDGM_TRUE)
    {
      /* Pointer to ExLS Graph Array */
      ptrExLSGraph = ptrExLogicalSupervision[exLSIndex].PtrExLSGraph;
      /* Access ExLS Status Array */
      ptrExtLogicalSupervisionStatus = 
        WDGM_GET_EXTLOGICAL_SUPERVISON_STATUS_PTR(coreId, exLSIndex);

      /* Expecting an initial checkpoint */
      if (ptrExtLogicalSupervisionStatus->ActivityFlag == WDGM_FALSE)
      {
        if (ptrExLSGraph[exLSGraphArrayIndex].CpType == WDGM_CP_INITIAL)
        {
          ptrExtLogicalSupervisionStatus->ActivityFlag = WDGM_TRUE;
          /* Store index of last reported ExLSGraphArrayIndex from this
            we will get previous reported SE and CP */
          ptrExtLogicalSupervisionStatus->LastRepExLSGraphArrIdx
            = exLSGraphArrayIndex;
          /* Set ExLS result as WDGM_LGSUPERVISION_CORRECT */
          SchM_Enter_WdgM_GLOBALSUPVSNSTATUS_PROTECTION();
          WDGM_WRITE_SE_STATUS(supervisedEntityIdx, seStatus
            | WDGM_LGSUPERVISION_CORRECT);
          SchM_Exit_WdgM_GLOBALSUPVSNSTATUS_PROTECTION();
        }
        else
        {
          SchM_Enter_WdgM_GLOBALSUPVSNSTATUS_PROTECTION();
          /* Set ELS result as WDGM_LGSUPERVISION_INCORRECT */
          WDGM_WRITE_SE_STATUS(supervisedEntityIdx, seStatus
            & WDGM_LGSUPERVISION_INCORRECT);
          SchM_Exit_WdgM_GLOBALSUPVSNSTATUS_PROTECTION();
        }
      }
      /* Expecting a successor */
      else
      {
        /* @Trace: SafeWdgM_SUD_API_381 */
        /* Access the last reported SE and CP */
        ptrLastRepExLSGraph = &((ptrExLogicalSupervision[exLSIndex].PtrExLSGraph)
          [ptrExtLogicalSupervisionStatus->LastRepExLSGraphArrIdx]);
        /* Get the map array index of Last Reported CP i.e. Index of
          Checkpoint Mapping Array
          WdgM_GaaExLSGraph<MODE_ID><GRAPH_ID>MapArray*/
        cpMapArrayIndex = ptrLastRepExLSGraph->CpMapArrayIndex;

        ptrExLSGraphMapArray
          = &((ptrExLogicalSupervision[exLSIndex].PtrExLSGraphMapArray)
          [cpMapArrayIndex]);
        /* Get the maximum branches available for Last Reported CP */
        maxBranches = WDGM_ZERO;
        found = WDGM_FALSE;
        while (maxBranches < ptrLastRepExLSGraph->MaxBranches)
        {
          /* @Trace: SafeWdgM_SUD_API_384 */
          /* Check whether the new CP is a successor of the stored CP */
          if ((cpId == ptrExLSGraphMapArray[maxBranches].Checkpoint)
            && (supervisedEntityId == ptrExLSGraphMapArray[maxBranches].SEId))
          {
            /* Update ILS result */
            SchM_Enter_WdgM_GLOBALSUPVSNSTATUS_PROTECTION();
            WDGM_WRITE_SE_STATUS(supervisedEntityIdx,
              seStatus | WDGM_LGSUPERVISION_CORRECT);
            SchM_Exit_WdgM_GLOBALSUPVSNSTATUS_PROTECTION();
            /* Break the loop */
            maxBranches = ptrLastRepExLSGraph->MaxBranches;
            found = WDGM_TRUE;
          }
          else
          {
            maxBranches++;
          }
        }
        
        /* @Trace: SafeWdgM_SUD_API_388 */
        if (found == WDGM_TRUE)
        {
          /* Check the property of current reported ExLS */
          if (ptrExLSGraph[exLSGraphArrayIndex].CpType == WDGM_CP_FINAL)
          {
            /* Reset the activity flag */
            ptrExtLogicalSupervisionStatus->ActivityFlag = WDGM_FALSE;
          }
          else
          {
            /* Store index of newly reported ExLSGraphArrayIndex */
            ptrExtLogicalSupervisionStatus->LastRepExLSGraphArrIdx
              = exLSGraphArrayIndex;
          }
        }
        else
        {
          SchM_Enter_WdgM_GLOBALSUPVSNSTATUS_PROTECTION();
          WDGM_WRITE_SE_STATUS(supervisedEntityIdx, seStatus
            & WDGM_LGSUPERVISION_INCORRECT);
          SchM_Exit_WdgM_GLOBALSUPVSNSTATUS_PROTECTION();
        }
      } /* End of the condition "If ptrExtLogicalSupervisionStatus->ActivityFlag equal to WDGM_FALSE */
    } /* End of the condition "If validExLSCp equal to WDGM_TRUE*/
  }
}
#define WDGM_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"
#endif

/*******************************************************************************
** Function Name      : WdgM_EvaluateLocalStatus                              **
**                                                                            **
** Service ID         : NA                                                    **
**                                                                            **
** Description        : This service evaluates the local supervision status   **
**                      of supervised entities                                **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : None                                                  **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : ptrSEFailedFlag : Pointer used for marking after      **
**                                        there is a failed SE when           **
**                                        evaluating local status             **
**                      ptrSEExpiredFlag : Pointer used for marking after     **
**                                         there is an expired SE when        **
**                                         evaluating local status            **
**                                                                            **
** Return parameter   : None                                                  **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                      WdgM_PtrConfig,                                       **
**                      WdgM_CurrentMode,                                     **
**                      WdgM_SupervisedEntity,                                **
**                      WdgM_SEStatus,                                        **
**                      WdgM_FailedRefCycleCounter,                           **
**                      WdgM_FirstExpSEIDStatus,                              **
**                      WdgM_FirstExpiredSEID,                                **
**                      WdgM_InvFirstExpiredSEID                              **
**                                                                            **
**                      Function(s) invoked:                                  **
**                      PtrRteSwitchMode,                                     **
**                      SchM_Enter_WdgM_GLOBALSUPVSNSTATUS_PROTECTION,        **
**                      SchM_Exit_WdgM_GLOBALSUPVSNSTATUS_PROTECTION          **
*******************************************************************************/
/* @Trace:  SRS_ModeMgm_09225 SRS_BSW_00171 SRS_ModeMgm_09112 SRS_ModeMgm_09160 SRS_ModeMgm_09221 */
#define WDGM_START_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"
FUNC(void, WDGM_CODE) WdgM_EvaluateLocalStatus(
  VAR(CoreIdType, AUTOMATIC) coreId, 
  P2VAR(boolean, AUTOMATIC, WDGM_DATA) ptrSEFailedFlag,
  P2VAR(boolean, AUTOMATIC, WDGM_DATA) ptrSEExpiredFlag
)
{
  P2CONST(WdgM_ModePropertyType, AUTOMATIC, WDGM_CONST)ptrCurrentMode;
  P2CONST(WdgM_ActiveSEType, AUTOMATIC, WDGM_CONST)ptrActiveSE;
  #if((WDGM_ENABLE_ALIVE_SUPERVISION == STD_ON) || \
    (WDGM_ENABLE_DEADLINE_SUPERVISION == STD_ON) || \
    (WDGM_ENABLE_LOGICAL_SUPERVISION == STD_ON) || \
    (WDGM_ENABLE_OS_APPLICATION == STD_ON))
  P2CONST(WdgM_SupervisedEntityType, AUTOMATIC, WDGM_CONST) ptrSupervisedEntity;
  #endif
  VAR(WdgM_SupervisedEntityIndexType, AUTOMATIC) supervisedEntityIdx;
  VAR(uint16, AUTOMATIC) activeSECnt;
  VAR(uint8, AUTOMATIC) preLocalStatus;
  VAR(uint8, AUTOMATIC) newLocalStatus;
  VAR(boolean, AUTOMATIC) failedFlag;
  VAR(boolean, AUTOMATIC) expiredFlag;

  P2CONST(WdgM_ConfigType, AUTOMATIC, CONST) WdgM_PtrConfig;
  VAR(uint8, AUTOMATIC) seStatus;

  /* @Trace: SafeWdgM_SUD_API_052 */
  WdgM_PtrConfig = GET_CONFIG_PTR(coreId);

  /* Get the pointer to current mode array */
  ptrCurrentMode = &(WdgM_PtrConfig->PtrModes[WDGM_READ_CURRENT_MODE(coreId)]);
  /* Get the number of active SE's in the current mode */
  activeSECnt = WDGM_ZERO;

  failedFlag = WDGM_FALSE;
  expiredFlag = WDGM_FALSE;

  /* Loop through all the SE's */
  while (activeSECnt < ptrCurrentMode->TotalSEInMode)
  {
    /* Get index to the Active SE */
    ptrActiveSE = &((ptrCurrentMode->PtrActiveSEList)[activeSECnt]);
    supervisedEntityIdx = ptrActiveSE->SEArrayIndex;
    seStatus = WDGM_READ_SE_STATUS(supervisedEntityIdx);
    /* Get the pointer to current WdgM_SupervisedEntity array */
    #if((WDGM_ENABLE_ALIVE_SUPERVISION == STD_ON) || \
      (WDGM_ENABLE_DEADLINE_SUPERVISION == STD_ON) || \
      (WDGM_ENABLE_LOGICAL_SUPERVISION == STD_ON) || \
      (WDGM_ENABLE_OS_APPLICATION == STD_ON))
    ptrSupervisedEntity = &WdgM_SupervisedEntity[supervisedEntityIdx];
    #endif

    preLocalStatus = seStatus & WDGM_STATUS_MASK;
    newLocalStatus = preLocalStatus;
    WdgM_CalcNewLocalStatus(ptrActiveSE, seStatus, &newLocalStatus);
    #if((WDGM_ENABLE_ALIVE_SUPERVISION == STD_ON) || \
       (WDGM_ENABLE_DEADLINE_SUPERVISION == STD_ON) || \
     (WDGM_ENABLE_LOGICAL_SUPERVISION == STD_ON))

    if (preLocalStatus != newLocalStatus)
    {
      SchM_Enter_WdgM_GLOBALSUPVSNSTATUS_PROTECTION();
      WDGM_WRITE_SE_STATUS(supervisedEntityIdx,
        (seStatus & WDGM_CLEAR_SE) | newLocalStatus);
      SchM_Exit_WdgM_GLOBALSUPVSNSTATUS_PROTECTION();
      (void)(*(ptrSupervisedEntity->PtrRteSwitchMode))(newLocalStatus);
    }
    #endif

    /* @Trace: SafeWdgM_SUD_API_053 */
    switch (newLocalStatus)
    {
    case WDGM_LOCAL_STATUS_EXPIRED:
      expiredFlag = WDGM_TRUE;
      break;

    case WDGM_LOCAL_STATUS_FAILED:
      failedFlag = WDGM_TRUE;
      #if(WDGM_ENABLE_OS_APPLICATION == STD_ON)
      if(ptrSupervisedEntity->TrustedType == WDGM_OS_APPLICATION_NON_TRUSTED){
        BswM_WdgM_RequestPartitionReset(ptrSupervisedEntity->ApplicationId);
      }
      #endif
      break;

    case WDGM_LOCAL_STATUS_OK:
    default:
      /* do nothing */
      break;
    }

    /* @Trace: SafeWdgM_SUD_API_054 */
    SchM_Enter_WdgM_FIRSTEXPIREDSEID_MULTICORE_PROTECTION();
    /* Check whether the current SE is the first one to go to
      WDGM_LOCAL_STATUS_EXPIRED status */
    if ((expiredFlag == WDGM_TRUE)
      && (WDGM_FALSE  == WdgM_FirstExpSEIDStatus))
    {
      /* Write the value of SEID into NON-Initialized RAM area */
      WdgM_FirstExpiredSEID = ptrActiveSE->SEId;
      /* Write the inverse value of SEID into NON-Initialized RAM area */
      WdgM_InvFirstExpiredSEID =
        (WdgM_SupervisedEntityIdType)(~(ptrActiveSE->SEId));
      WdgM_FirstExpSEIDStatus = WDGM_TRUE;
    }
    SchM_Exit_WdgM_FIRSTEXPIREDSEID_MULTICORE_PROTECTION();
    activeSECnt++;
  } /* activeSECnt < ptrCurrentMode->TotalSEInMode */

  /* @Trace: SafeWdgM_SUD_API_055 */
  *ptrSEFailedFlag = failedFlag;
  *ptrSEExpiredFlag = expiredFlag;
}
#define WDGM_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"

/*******************************************************************************
** Function Name      : WdgM_EvaluateGlobalStatus                             **
**                                                                            **
** Service ID         : NA                                                    **
**                                                                            **
** Description        : This service evaluates the global supervision status  **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : failedFlag : Marking whether there is a failed SE     **
**                      expiredFlag : Marking whether there is an expired SE  **
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
**                      WdgM_PtrConfig,                                       **
**                      WdgM_CurrentMode,                                     **
**                      WdgM_GlobalSupervisionStatus,                         **
**                      WdgM_InvGlobalSupervisionStatus,                      **
**                      WdgM_ExpSupervisionCycleCounter,                      **
**                                                                            **
**                      Function(s) invoked:                                  **
**                      WdgM_TriggerWdgIf,                                    **
**                      Dem_SetEventStatus,                                   **
**                      Mcu_PerformReset,                                     **
**                      Rte_Switch_globalMode_currentMode,                    **
**                      SchM_Enter_WdgM_GLOBALSUPVSNSTATUS_PROTECTION,        **
**                      SchM_Exit_WdgM_GLOBALSUPVSNSTATUS_PROTECTION          **
*******************************************************************************/
/* @Trace: SRS_ModeMgm_09169 SRS_WdgM_CUS_00006 SRS_BSW_00339 SRS_ModeMgm_09159 SRS_ModeMgm_09161 SRS_ModeMgm_09226 SRS_ModeMgm_09112 SRS_ModeMgm_09160 SRS_ModeMgm_09221 SRS_WdgM_CUS_00012 */
#define WDGM_START_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"
FUNC(void, WDGM_CODE) WdgM_EvaluateGlobalStatus(
  VAR(CoreIdType, AUTOMATIC) coreId, 
  VAR(boolean, AUTOMATIC) failedFlag, 
  VAR(boolean, AUTOMATIC) expiredFlag
)
{
  P2CONST(WdgM_ModePropertyType, AUTOMATIC, WDGM_CONST)ptrModes;
  VAR(WdgM_GlobalStatusType, AUTOMATIC) preGlobalStatus;
  VAR(WdgM_GlobalStatusType, AUTOMATIC) newGlobalStatus;
  VAR(uint16, AUTOMATIC) expireTolerance;
  VAR(WdgM_GlobalStatusType, AUTOMATIC) invSupervisionStatus;

  /* Point to a WdgM_ConfigType const */
  P2CONST(WdgM_ConfigType, AUTOMATIC, CONST) WdgM_PtrConfig;
  P2VAR(WdgM_GlobalStatusType, AUTOMATIC, WDGM_APPL_DATA) ptrGlobalSupervisionStatus;
  P2VAR(WdgM_GlobalStatusType, AUTOMATIC, WDGM_APPL_DATA) ptrInvGlobalSupervisionStatus;
  P2VAR(WdgM_ExpSupCycleTolType, AUTOMATIC, WDGM_APPL_DATA) ptrExpSupervisionCycleCounter;

  WdgM_PtrConfig = GET_CONFIG_PTR(coreId);
  ptrGlobalSupervisionStatus = WDGM_GET_GLOBAL_SUPERVISION_STATUS_PTR(coreId);
  ptrInvGlobalSupervisionStatus = WDGM_GET_INV_GLOBAL_SUPERVISION_STATUS_PTR(coreId);
  ptrExpSupervisionCycleCounter = WDGM_GET_EXP_SUPERVISION_CYCLE_COUNTER_PTR(coreId);
  
  /* @Trace: SafeWdgM_SUD_API_044 */
  ptrModes = &(WdgM_PtrConfig->PtrModes[WDGM_READ_CURRENT_MODE(coreId)]);
  expireTolerance = ptrModes->WdgTrigBlockCount;
  preGlobalStatus = *ptrGlobalSupervisionStatus;
  newGlobalStatus = *ptrGlobalSupervisionStatus;
  invSupervisionStatus = ~(*ptrInvGlobalSupervisionStatus);

  /* check whether double inverse value match */
  if (invSupervisionStatus == *ptrGlobalSupervisionStatus)
  {
    
    switch (preGlobalStatus)
    {
    /* @Trace: SafeWdgM_SUD_API_045 */
    case WDGM_GLOBAL_STATUS_OK:
      if (expiredFlag == WDGM_TRUE)
      {
        if (expireTolerance == WDGM_ZERO)
        {
          /* (4) WDGM_GLOBAL_STATUS_OK -> WDGM_GLOBAL_STATUS_STOPPED */
          newGlobalStatus = WDGM_GLOBAL_STATUS_STOPPED;
        }
        else
        {
          /* (3) WDGM_GLOBAL_STATUS_OK -> WDGM_GLOBAL_STATUS_EXPIRED */
          newGlobalStatus = WDGM_GLOBAL_STATUS_EXPIRED;

          (*ptrExpSupervisionCycleCounter)++;
        }
      }
      else
      {
        if (failedFlag == WDGM_TRUE)
        {
          /* (2) WDGM_GLOBAL_STATUS_OK -> WDGM_GLOBAL_STATUS_FAILED */
          newGlobalStatus = WDGM_GLOBAL_STATUS_FAILED;
        }
        else
        {
          /* (1) WDGM_GLOBAL_STATUS_OK -> WDGM_GLOBAL_STATUS_OK */
          newGlobalStatus = WDGM_GLOBAL_STATUS_OK;
        }
      }
      break;

    /* @Trace: SafeWdgM_SUD_API_046 */
    case WDGM_GLOBAL_STATUS_FAILED:
      if (expiredFlag == WDGM_TRUE)
      {
        if (expireTolerance == WDGM_ZERO)
        {
          /* (8) WDGM_GLOBAL_STATUS_FAILED -> WDGM_GLOBAL_STATUS_STOPPED */
          newGlobalStatus = WDGM_GLOBAL_STATUS_STOPPED;
        }
        else
        {
          /* (7) WDGM_GLOBAL_STATUS_FAILED -> WDGM_GLOBAL_STATUS_EXPIRED */
          newGlobalStatus = WDGM_GLOBAL_STATUS_EXPIRED;

          (*ptrExpSupervisionCycleCounter)++;
        }
      }
      else
      {
        if (failedFlag == WDGM_TRUE)
        {
          /* (5) WDGM_GLOBAL_STATUS_FAILED -> WDGM_GLOBAL_STATUS_FAILED */
          newGlobalStatus = WDGM_GLOBAL_STATUS_FAILED;
        }
        else
        {
          /* (6) WDGM_GLOBAL_STATUS_FAILED -> WDGM_GLOBAL_STATUS_OK */
          newGlobalStatus = WDGM_GLOBAL_STATUS_OK;
        }
      }
      break;

    /* @Trace: SafeWdgM_SUD_API_047 */
    case WDGM_GLOBAL_STATUS_EXPIRED:
      if (expiredFlag == WDGM_TRUE)
      {
        (*ptrExpSupervisionCycleCounter)++;
        if (*ptrExpSupervisionCycleCounter <= expireTolerance)
        {
          /* (9) WDGM_GLOBAL_STATUS_EXPIRED -> WDGM_GLOBAL_STATUS_EXPIRED */
          newGlobalStatus = WDGM_GLOBAL_STATUS_EXPIRED;
        }
        else
        {
          /* (10) WDGM_GLOBAL_STATUS_EXPIRED -> WDGM_GLOBAL_STATUS_STOPPED */
          newGlobalStatus = WDGM_GLOBAL_STATUS_STOPPED;
        }
      }
      else
      {
        /* Impossible */
      }
      break;

    /* @Trace: SafeWdgM_SUD_API_048 */
    case WDGM_GLOBAL_STATUS_STOPPED:
      newGlobalStatus = WDGM_GLOBAL_STATUS_STOPPED;
      break;
    case WDGM_GLOBAL_STATUS_DEACTIVATED:
      newGlobalStatus = WDGM_GLOBAL_STATUS_DEACTIVATED;
      break;
    default:
      /* Do nothing */
      break;
    }
  }
  else
  {
    /* @Trace: SafeWdgM_SUD_API_044 */
    /* if not matched, stop it */
    newGlobalStatus = WDGM_GLOBAL_STATUS_STOPPED;
  }
  /* @Trace: SafeWdgM_SUD_API_051 */
  SchM_Enter_WdgM_GLOBALSUPVSNSTATUS_PROTECTION();
  *ptrGlobalSupervisionStatus = newGlobalStatus;
  *ptrInvGlobalSupervisionStatus = ~(*ptrGlobalSupervisionStatus);
  SchM_Exit_WdgM_GLOBALSUPVSNSTATUS_PROTECTION();
  WdgM_EvaluatePlatformGlobalStatus(WdgM_PtrConfig, ptrModes, coreId);
}
#define WDGM_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"

/*******************************************************************************
** Function Name      : WdgM_EvaluatePlatformGlobalStatus                     **
**                                                                            **
** Service ID         : NA                                                    **
**                                                                            **
** Description        : This service get the core index                       **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : ptrConfig: pointer to WdgM Config                     **
**                      ptrModes: pointer to WdgM Mode                        **
**                      coreId: core id                                       **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : None                                                  **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                      WdgM_PlatformGlobalSupervisionStatus                  **
**                      WdgM_InvPlatformGlobalSupervisionStatus               **
**                                                                            **
**                      Function(s) invoked:                                  **
**                      Rte_Switch_globalMode_currentMode                     **
**                      Dem_SetEventStatus                                    **
**                      SchM_Enter_WdgM_GLOBALSUPVSNSTATUS_PROTECTION         **
**                      SchM_Exit_WdgM_GLOBALSUPVSNSTATUS_PROTECTION          **
**                      Mcu_PerformReset                                      **
**                      WdgM_TriggerWdgIf                                     **
*******************************************************************************/
/* @Trace: SRS_ModeMgm_09162 SRS_BSW_00171 SRS_WdgM_CUS_00012 */
#define WDGM_START_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"
static FUNC(void, WDGM_CODE) WdgM_EvaluatePlatformGlobalStatus(
  P2CONST(WdgM_ConfigType, AUTOMATIC, CONST) ptrConfig,
  P2CONST(WdgM_ModePropertyType, AUTOMATIC, WDGM_CONST)ptrModes,
  VAR(CoreIdType, AUTOMATIC) coreId
)
{
  VAR(WdgM_GlobalStatusType, AUTOMATIC) prePlatformGlobalStatus;
  VAR(WdgM_GlobalStatusType, AUTOMATIC) newPlatformGlobalStatus;
  VAR(WdgM_GlobalStatusType, AUTOMATIC) invPlatformSupervisionStatus;
  P2VAR(WdgM_GlobalStatusType, AUTOMATIC, WDGM_APPL_DATA) ptrGlobalSupervisionStatus;
  VAR(uint8, AUTOMATIC) u8Count;

  #if((WDGM_DEM_ERROR_REPORT == STD_OFF) || \
    (WDGM_DEM_STOPPED_SUPERVISION_REPORT == STD_OFF))
  WDGM_UNUSED_PTR(ptrConfig);
  #endif
  #if ((WDGM_TOTAL_CORES == WDGM_ONE) && (WDGM_ENABLE_TRIGGER == STD_OFF))
  WDGM_UNUSED(coreId);
  #endif

  /* @Trace: SafeWdgM_SUD_API_245 */
  SchM_Enter_WdgM_GLOBALSUPVSNSTATUS_PROTECTION();
  
  prePlatformGlobalStatus = WdgM_PlatformGlobalSupervisionStatus;
  invPlatformSupervisionStatus = ~WdgM_InvPlatformGlobalSupervisionStatus;
  
  #if (WDGM_TOTAL_CORES > WDGM_ONE)
  if (WDGM_MASTER_CORE_ID == coreId)
  #endif
  {
    if (prePlatformGlobalStatus == invPlatformSupervisionStatus)
    {
      newPlatformGlobalStatus = WDGM_GLOBAL_STATUS_DEACTIVATED;
      for (u8Count = 0U; u8Count < WDGM_TOTAL_CORES; u8Count++)
      {
        ptrGlobalSupervisionStatus = WDGM_GET_GLOBAL_SUPERVISION_STATUS_PTR(u8Count);
        #if (WDGM_TOTAL_CORES > WDGM_ONE)
        if ((ptrGlobalSupervisionStatus != NULL_PTR) && 
          (StatusSeverity[*ptrGlobalSupervisionStatus] > StatusSeverity[newPlatformGlobalStatus]))
        #endif
        {
          newPlatformGlobalStatus = *ptrGlobalSupervisionStatus;
        }
      }
    }
    else
    {
      newPlatformGlobalStatus = WDGM_GLOBAL_STATUS_STOPPED;
    }
    WdgM_PlatformGlobalSupervisionStatus = newPlatformGlobalStatus;
    WdgM_InvPlatformGlobalSupervisionStatus = ~WdgM_PlatformGlobalSupervisionStatus;
  }

  newPlatformGlobalStatus = WdgM_PlatformGlobalSupervisionStatus;

  SchM_Exit_WdgM_GLOBALSUPVSNSTATUS_PROTECTION();

  switch (newPlatformGlobalStatus)
  {
  /* @Trace: SafeWdgM_SUD_API_247 */
  case WDGM_GLOBAL_STATUS_OK:
  case WDGM_GLOBAL_STATUS_FAILED:
  case WDGM_GLOBAL_STATUS_EXPIRED:
    #if(WDGM_ENABLE_TRIGGER == STD_ON)
    WdgM_TriggerWdgIf(coreId, ptrModes, WDGM_TM_NORMAL);
    #endif
    /* Report global state to Rte after every supervision cycle */
    if (prePlatformGlobalStatus != newPlatformGlobalStatus)
    {
      (void)Rte_Switch_globalMode_currentMode(newPlatformGlobalStatus);
    }
    break;

  /* case WDGM_GLOBAL_STATUS_STOPPED is removed for code coverage test */
  /* and case WDGM_GLOBAL_STATUS_STOPPED will be handled at default */
  /* case WDGM_GLOBAL_STATUS_STOPPED: */
  /* @Trace: SafeWdgM_SUD_API_252 */
  default:
    #if(WDGM_DEM_ERROR_REPORT == STD_ON)
    #if(WDGM_DEM_STOPPED_SUPERVISION_REPORT == STD_ON)
    if ((prePlatformGlobalStatus != newPlatformGlobalStatus) && 
      (ptrConfig->DemEventParam.ESupervisionEnable == WDGM_TRUE))
    {
      (void)Dem_SetEventStatus(ptrConfig->DemEventParam.ESupervision, DEM_EVENT_STATUS_FAILED);
    }
    #endif
    #endif
    #if(WDGM_IMMEDIATE_RESET == STD_ON)
    Mcu_PerformReset();
    #else
    /* Report global state to Rte after every supervision cycle */
    if (prePlatformGlobalStatus != newPlatformGlobalStatus)
    {
      (void)Rte_Switch_globalMode_currentMode(newPlatformGlobalStatus);
    }
    #endif
    #if(WDGM_ENABLE_TRIGGER == STD_ON)
    WdgM_TriggerWdgIf(coreId, ptrModes, WDGM_TM_TIMEOUT);
    #else
    WDGM_UNUSED_PTR(ptrModes);
    #endif
    break;
  }
}
#define WDGM_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"

/*******************************************************************************
** Function Name      : WdgM_GetCoreIndex                                     **
**                                                                            **
** Service ID         : NA                                                    **
**                                                                            **
** Description        : This service get the core index                       **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   :                                                       **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : ptrCoreId: buffer to store core Id                    **
**                                                                            **
** Return parameter   : E_OK: success                                         **
**                      E_NOT_OK: failure                                     **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                      WdgM_Config                                           **
**                                                                            **
**                      Function(s) invoked:                                  **
**                      GetCoreID                                             **
*******************************************************************************/
/* @Trace: SRS_WdgM_CUS_00012 */
#define WDGM_START_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"
FUNC(Std_ReturnType, WDGM_CODE) WdgM_GetCoreIndex(
  P2VAR(WdgM_CoreIdType, AUTOMATIC, WDGM_DATA) ptrCoreId
)
{
  VAR(Std_ReturnType, AUTOMATIC) retVal;

  /* @Trace: SafeWdgM_SUD_API_452 */
  retVal = E_OK;
  #if(WDGM_TOTAL_CORES > WDGM_ONE)
  /* Get core ID, coreID is also an index to access to array */
  *ptrCoreId = (WdgM_CoreIdType)GetCoreID();
  if ((*ptrCoreId >= WDGM_TOTAL_CORES) || (WdgM_Config[(*ptrCoreId)] == NULL_PTR))
  {
    retVal = E_NOT_OK;
  }
  #else
  *ptrCoreId = (WdgM_CoreIdType)0x00U;
  #endif

  return retVal;
}
#define WDGM_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"

/*******************************************************************************
** Function Name      : WdgM_ValidateOffMode                                  **
**                                                                            **
** Service ID         : NA                                                    **
**                                                                            **
** Description        : Validate Wdg Off Mode configuration                   **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : ptrNewMode: pointer to WdgM Mode                      **
**                      coreId : core id                                      **
**                      serviceId : service id of calling function            **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : E_OK: success                                         **
**                      E_NOT_OK: failure                                     **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                                                                            **
**                      Function(s) invoked:                                  **
**                      Det_ReportRuntimeError                                **
*******************************************************************************/
/* @Trace: SRS_BSW_00171 SRS_WdgM_CUS_00013 */
#if((WDGM_OFF_MODE_ENABLED == STD_OFF) && (WDGM_ENABLE_TRIGGER == STD_ON))
#define WDGM_START_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"
FUNC(Std_ReturnType, WDGM_CODE) WdgM_ValidateOffMode(
  P2CONST(WdgM_ModePropertyType, AUTOMATIC, WDGM_CONST) ptrNewMode,
  VAR(WdgM_CoreIdType, AUTOMATIC) coreId, VAR(uint8, AUTOMATIC) serviceId
)
{
  P2CONST(WdgM_TriggerType, AUTOMATIC, WDGM_CONST) ptrTriggers;
  VAR(uint8, AUTOMATIC) counterTrigger;
  VAR(Std_ReturnType, AUTOMATIC) returnValue;
  
  /* @Trace: SafeWdgM_SUD_API_078 */
  returnValue = E_OK;
  
  ptrTriggers = ptrNewMode->PtrTriggers;
  counterTrigger = WDGM_ZERO;
  /* Loop running through all configured watchdog drivers */
  while (counterTrigger < ptrNewMode->TotalTriggers)
  {
    if ((ptrTriggers[counterTrigger].WdgIfMode) == WDGIF_OFF_MODE)
    {
      #if (((DET_AR_RELEASE_MAJOR_VERSION == 0x04)&&(DET_AR_RELEASE_MINOR_VERSION >= 0x02))|| \
        (DET_AR_RELEASE_MAJOR_VERSION > 0x04))
      /* Report runtime error to Det*/
      (void)Det_ReportRuntimeError(WDGM_MODULE_ID, coreId,
         serviceId, WDGM_E_DISABLE_NOT_ALLOWED);
      #else
      #if(WDGM_DEV_ERROR_DETECT == STD_ON)
      /* Report error to Det*/
      (void)Det_ReportError(WDGM_MODULE_ID, coreId,
         serviceId, WDGM_E_DISABLE_NOT_ALLOWED);
      #endif
      #endif
      counterTrigger = ptrNewMode->TotalTriggers;
      returnValue = E_NOT_OK;
    }
    else
    {
      counterTrigger++;
    }
  }
  return returnValue;
}
#define WDGM_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"
#endif

/*******************************************************************************
** Function Name      : WdgM_GetExtLSIndex                                    **
**                                                                            **
** Service ID         : NA                                                    **
**                                                                            **
** Description        : This service is used to validate whether a checkpoint **
**                      belongs to an External Logical Supervision graph      **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : ptrModes : pointer to current WdgM Mode               **
**                      supervisedEntityId: Supervised Entity ID              **
**                      cpId: checkpoint ID                                   **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : ptrExLSIndex: index of External LS Graph in current   **
**                        Mode                                                **
**                      ptrExLSGraphArrayIndex: index of checkpoint in        **
**                        External LS Graph                                   **
**                                                                            **
** Return parameter   : WDGM_TRUE: Checkpoint belongs to External LS Graph    **
**                      WDGM_FALSE: Checkpoint doesn't belongs to External LS **
**                                  Graph                                     **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                                                                            **
**                      Function(s) invoked:                                  **
**                      GetCoreID                                             **
*******************************************************************************/
/* @Trace: SRS_ModeMgm_09221 SRS_ModeMgm_09222 */
#if(WDGM_ENABLE_EXTERNAL_TRANSITION == STD_ON)
#define WDGM_START_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"
static FUNC(boolean, WDGM_CODE) WdgM_GetExtLSIndex(
  P2CONST(WdgM_ModePropertyType, AUTOMATIC, WDGM_CONST) ptrModes,
  P2VAR(uint16, AUTOMATIC, WDGM_DATA) ptrExLSIndex,
  P2VAR(WdgM_ExLSGraphArrayType, AUTOMATIC, WDGM_DATA) ptrExLSGraphArrayIndex,
  VAR(WdgM_SupervisedEntityIdType, AUTOMATIC) supervisedEntityId,
  VAR(WdgM_CheckpointIdType, AUTOMATIC) cpId
)
{
  P2CONST(WdgM_ExLogicalSupervisionType, AUTOMATIC, WDGM_CONST)
    ptrExLogicalSupervision;
  P2CONST(WdgM_ExLSGraphType, AUTOMATIC, WDGM_CONST) ptrExLSGraph;
  VAR(boolean, AUTOMATIC) validExLSCp;
  VAR(uint16, AUTOMATIC) totalExLogicalSupervisions;
  VAR(WdgM_ExLSGraphArrayType, AUTOMATIC) exLSGraphArrayIndex;
  VAR(uint16, AUTOMATIC) exLSIndex;
  VAR(WdgM_CheckpointIdType, AUTOMATIC) totalCheckpoints;

  /* @Trace: SafeWdgM_SUD_API_453 */
  ptrExLogicalSupervision = ptrModes->PtrExLogicalSupervisions;
  validExLSCp = WDGM_FALSE;
  exLSIndex = WDGM_ZERO;
    /* Load total ExLS */
  totalExLogicalSupervisions =
    ptrModes->TotalExLogicalSupervisions;
  /* Check whether reported CP of SE is present in any transition */
  while ((totalExLogicalSupervisions != WDGM_ZERO)
    && (validExLSCp == WDGM_FALSE))
  {
    /* Store ExLS Graph Array Index of the reported SE/CP */
    exLSGraphArrayIndex = WDGM_ZERO;
    /* Pointer to ExLS Graph Array */
    ptrExLSGraph = ptrExLogicalSupervision[exLSIndex].PtrExLSGraph;
    totalCheckpoints
      = ptrExLogicalSupervision[exLSIndex].TotalCheckpoints;
    /* Loop all CP in WdgM_GaaExLSGraph array */
    while ((totalCheckpoints != WDGM_ZERO)
      && (validExLSCp == WDGM_FALSE))
    {
      /* Match the SE and CP in WdgM_GaaExLSGraph<><> array*/
      if ((ptrExLSGraph[exLSGraphArrayIndex].SEId == supervisedEntityId)
        && (ptrExLSGraph[exLSGraphArrayIndex].Checkpoint == cpId))
      {
        /* Valid Ex Logical Supervision CP detected */
        validExLSCp = WDGM_TRUE;
        *ptrExLSIndex = exLSIndex;
        *ptrExLSGraphArrayIndex = exLSGraphArrayIndex;
      }
      else
      {
        totalCheckpoints--;
        /* Next index of the ExLS Graph Array ) */
        exLSGraphArrayIndex++;
      }
    }
    /* Total CP in ExLS Graph Array (Size of ExLS Graph Array) */
    if (validExLSCp == WDGM_FALSE)
    {
      totalExLogicalSupervisions--;
      /* Update ExLS Status Array Index */
      exLSIndex++;
    }
  } /* totalExLogicalSupervisions != WDGM_ZERO) &&... */
  return validExLSCp;
}
#define WDGM_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"
#endif

/*******************************************************************************
** Function Name      : WdgM_CalcNewLocalStatus                               **
**                                                                            **
** Service ID         : NA                                                    **
**                                                                            **
** Description        : Calculating new local supervision status              **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : ptrActiveSE: pointer to an active SE                  **
**                      seStatus : current status of the active SE            **
**                      preLocalStatus : local supervision status of active SE**
**                      ptrNewLocalStatus: new local supervision status of    **
**                        active SE                                           **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   :                                                       **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                      WdgM_FailedRefCycleCounter                            **
**                                                                            **
**                      Function(s) invoked:                                  **
**                                                                            **
*******************************************************************************/
/* @Trace: SRS_BSW_00171 SRS_ModeMgm_09112 SRS_ModeMgm_09221 SRS_ModeMgm_09160  */
#define WDGM_START_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"
static FUNC(void, WDGM_CODE) WdgM_CalcNewLocalStatus(
  P2CONST(WdgM_ActiveSEType, AUTOMATIC, WDGM_CONST) ptrActiveSE,
  VAR(uint8, AUTOMATIC) seStatus,
  P2VAR(uint8, AUTOMATIC, WDGM_DATA) ptrNewLocalStatus
)
{
  #if(WDGM_ENABLE_ALIVE_SUPERVISION == STD_ON)
  VAR(WdgM_SupervisedEntityIndexType, AUTOMATIC) supervisedEntityIdx;
  #endif
  #if((WDGM_ENABLE_DEADLINE_SUPERVISION == STD_ON) || \
      (WDGM_ENABLE_LOGICAL_SUPERVISION == STD_ON))
  VAR(boolean, AUTOMATIC) deadlineAndLogicalSupervisionPass;
  #endif
  
  /* @Trace: SafeWdgM_SUD_API_457 */
  #if(WDGM_ENABLE_ALIVE_SUPERVISION == STD_ON)
  supervisedEntityIdx = ptrActiveSE->SEArrayIndex;
  #endif
  #if((WDGM_ENABLE_DEADLINE_SUPERVISION == STD_ON) || \
      (WDGM_ENABLE_LOGICAL_SUPERVISION == STD_ON))
  deadlineAndLogicalSupervisionPass = WDGM_TRUE;
  #endif
  
  #if(WDGM_ENABLE_ALIVE_SUPERVISION == STD_OFF)
  WDGM_UNUSED_PTR(ptrActiveSE);
  #endif

  #if((WDGM_ENABLE_ALIVE_SUPERVISION == STD_OFF) && \
      (WDGM_ENABLE_DEADLINE_SUPERVISION == STD_OFF) && \
      (WDGM_ENABLE_LOGICAL_SUPERVISION == STD_OFF))
  WDGM_UNUSED_PTR(ptrNewLocalStatus);
  #endif

  #if(WDGM_ENABLE_DEADLINE_SUPERVISION == STD_ON)
  /* Check whether the result of deadline supervisions for the SE is false */
  if ((seStatus & WDGM_DEADLINESUPERVISION_CORRECT)
    != WDGM_DEADLINESUPERVISION_CORRECT)
  {
    /* Set the flag if the result of either logical or deadline supervision
      is false */
    deadlineAndLogicalSupervisionPass = WDGM_FALSE;
  }
  #endif

  #if(WDGM_ENABLE_LOGICAL_SUPERVISION == STD_ON)
  /* Check whether the result of logical supervisions for the SE is false */
  if ((seStatus & WDGM_LGSUPERVISION_CORRECT)
    != WDGM_LGSUPERVISION_CORRECT)
  {
    /* Set the flag if the result of either logical or deadline supervision
      is false */
    deadlineAndLogicalSupervisionPass = WDGM_FALSE;
  }
  #endif
  /* @Trace: SafeWdgM_SUD_API_458 */
  switch (seStatus & WDGM_STATUS_MASK)
  {
  case WDGM_LOCAL_STATUS_OK:
    /* @Trace: SafeWdgM_SUD_API_279 */
    #if((WDGM_ENABLE_DEADLINE_SUPERVISION == STD_ON)\
      ||(WDGM_ENABLE_LOGICAL_SUPERVISION == STD_ON))
    if(deadlineAndLogicalSupervisionPass == WDGM_FALSE)
    {
      /* (2) WDGM_LOCAL_STATUS_OK -> WDGM_LOCAL_STATUS_EXPIRED */
      *ptrNewLocalStatus = WDGM_LOCAL_STATUS_EXPIRED;
    }
    else
    #endif
    {
      #if(WDGM_ENABLE_ALIVE_SUPERVISION == STD_ON)
      if ((seStatus & WDGM_ALIVESUPERVISION_CORRECT) != WDGM_ALIVESUPERVISION_CORRECT)
      {
        if (ptrActiveSE->FailedTolerance == WDGM_ZERO)
        {
          /* (2) WDGM_LOCAL_STATUS_OK -> WDGM_LOCAL_STATUS_EXPIRED */
          *ptrNewLocalStatus = WDGM_LOCAL_STATUS_EXPIRED;
        }
        else
        {
          /* (3) WDGM_LOCAL_STATUS_OK -> WDGM_LOCAL_STATUS_FAILED */
          *ptrNewLocalStatus = WDGM_LOCAL_STATUS_FAILED;
          (*(WdgM_FailedRefCycleCounter[supervisedEntityIdx]))++;
        }
      }
      else
      #endif
      {
        /* (1) WDGM_LOCAL_STATUS_OK -> WDGM_LOCAL_STATUS_OK */
      }
    }
    break;

  /* @Trace: SafeWdgM_SUD_API_290 */
  case WDGM_LOCAL_STATUS_FAILED:
    #if((WDGM_ENABLE_DEADLINE_SUPERVISION == STD_ON)\
      ||(WDGM_ENABLE_LOGICAL_SUPERVISION == STD_ON))
    if(deadlineAndLogicalSupervisionPass == WDGM_FALSE)
    {
      /* (6) WDGM_LOCAL_STATUS_FAILED -> WDGM_LOCAL_STATUS_EXPIRED */
      *ptrNewLocalStatus = WDGM_LOCAL_STATUS_EXPIRED;
    }
    else
    #endif
    {
      #if(WDGM_ENABLE_ALIVE_SUPERVISION == STD_ON)
      if ((seStatus & WDGM_ALIVESUPERVISION_CORRECT) != WDGM_ALIVESUPERVISION_CORRECT)
      {
        if ((*(WdgM_FailedRefCycleCounter[supervisedEntityIdx])) >= ptrActiveSE->FailedTolerance)
        {
          /* (6) WDGM_LOCAL_STATUS_FAILED -> WDGM_LOCAL_STATUS_EXPIRED */
          *ptrNewLocalStatus = WDGM_LOCAL_STATUS_EXPIRED;
        }
        else
        {
          /* (4) WDGM_LOCAL_STATUS_FAILED -> WDGM_LOCAL_STATUS_FAILED */
        }
        (*(WdgM_FailedRefCycleCounter[supervisedEntityIdx]))++;
      }
      else
      {
        if ((*(WdgM_FailedRefCycleCounter[supervisedEntityIdx])) == WDGM_ONE)
        {
          /* (5) WDGM_LOCAL_STATUS_FAILED -> WDGM_LOCAL_STATUS_OK */
          *ptrNewLocalStatus = WDGM_LOCAL_STATUS_OK;
        }
        else
        {
          /* (4) WDGM_LOCAL_STATUS_FAILED -> WDGM_LOCAL_STATUS_FAILED */
        }
        (*(WdgM_FailedRefCycleCounter[supervisedEntityIdx]))--;
      }
      #endif
    }
    break;

  case WDGM_LOCAL_STATUS_EXPIRED:
  case WDGM_LOCAL_STATUS_DEACTIVATED:
  default:
    /* do nothing */
    break;
  }
}
#define WDGM_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"
/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/
/* polyspace-end MISRA-C3:20.1 */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
