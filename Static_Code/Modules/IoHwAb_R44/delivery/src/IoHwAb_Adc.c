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
**  SRC-MODULE: IoHwAb_Adc.c                                                  **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR IOHWAB                                                **
**                                                                            **
**  PURPOSE   : APIs implementation for IoHwAb module                         **
**              IoHwAb_AnaInInit                                              **
**              IoHwAb_AnaInConvertStart                                      **
**              IoHwAb_AnaInConvertStop                                       **
**              IoHwAb_AnaInRead                                              **
**              IoHwAb_AnaInReadDirect                                        **
**              IoHwAb_AnaInFreeze                                            **
**              IoHwAb_AnaInUnfreeze                                          **
**              IoHwAb_AnaInFirstOrderFiltering                               **
**              IoHwAb_AnaInFilter                                            **
**              IoHwAb_AnaInConvertAllChannels                                **
**              IoHwAb_AnaInAdcAllGrNf                                        **
**              IoHwAb_AnaInDirReadDirect                                     **
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
** 1.6.4     08-Dec-2023  YongEun.Lee       #CP44-3041                        **
** 1.6.3     07-Sep-2023  KhaLN1            #CP44-2913, #CP44-2914            **
** 1.6.2     15-Aug-2023  KhaLN1            #CP44-2683, #CP44-2684            **
** 1.6.0     07-Jul-2023  KhaLN1            #CP44-2241                        **
** 1.4.2     10-Nov-2022  KhaLN1            #CP44-797                         **
** 1.4.0     22-Aug-2022  KhaLN1            #CP44-485                         **
** 1.3.0.1   30-Jun-2022  KhaLN1            #CP44-365                         **
** 1.1.0     15-Jul-2021  YangJin.Kim       R44-Redmine #18100                **
** 1.0.1     26-Feb-2020  YangJin.Kim       R40-Redmine #28531                **
** 1.0.0     04-Dec-2020  YangJin.Kim       R40-Redmine #26992                **
*******************************************************************************/


/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Rte_IoHwAb.h"
#include "IoHwAb_Adc.h"
#include "IoHwAb_Config.h"
#if (IOHWAB_USE_IO_MAN== STD_ON)
#include "IoHwAb_IOManager.h"
#endif /* (IOHWAB_USE_IO_MAN == STD_ON) */

#if ((IOHWAB_USE_ANA_IN == STD_ON) || (IOHWAB_USE_ANA_IN_DIR == STD_ON))
#include "Adc.h"
#include "IoHwAb_Util.h"
#include "Adc_Cfg.h"
#endif

#include "SchM_IoHwAb.h"


/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
/*polyspace:begin<RTE: IDP :Not a defect : No Action Planned >                */
/*polyspace:begin<RTE: NIV :Not a defect : No Action Planned >                */
/*polyspace:begin<RTE: OBAI:Not a defect : No Action Planned > Array Checked  */
/* polyspace-begin RTE:UNR [Not a defect:Unset] "Reachable code" */
/* polyspace-begin MISRA-C3:D4.14 [Justified:Unset] "The pointer is checked always." */
/* polyspace-begin MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Unset] "It depends on the configuration" */
/* polyspace-begin MISRA-C3:8.3 [Justified:Unset] "Prototypes are generated wrongly. It will be fixed soon" */
/* polyspace-begin DEFECT:DEAD_CODE [Justified:Unset] "It depends on the configuration." */
/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
#if ((IOHWAB_USE_ANA_IN == STD_ON) || (IOHWAB_USE_ANA_IN_DIR == STD_ON))

#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
/* polyspace-begin MISRA-C3:5.9 [Justified:Unset] "Not a defect" */
#if (defined(IOHWAB_MCAL_NXP_S32K14X))
static FUNC(Std_ReturnType, IOHWAB_CODE)IoHwAb_AnaInConvCompleted(uint8 IoHwAb_AdcHwUnitNum, uint8 IoHwAb_AdcDirLength);
#elif (defined(IOHWAB_MCAL_CYPRESS_CYTXXX))
static FUNC(Std_ReturnType, IOHWAB_CODE)IoHwAb_AnaInConvCompleted(const Adc_GroupConfigType * IoHwAb_AdcGroupCfg);
#else
static FUNC(Std_ReturnType, IOHWAB_CODE)IoHwAb_AnaInConvCompleted(uint8 IoHwAb_AdcHwUnitNum);
#endif

#if (IOHWAB_USE_ANA_IN_DIR == STD_ON)
static FUNC(Std_ReturnType, IOHWAB_CODE) IoHwAb_DetCheckAnaInDirReadDirect(
  IoHwAb_IndexType ChIdx,
  CONSTP2CONST(IoHwAb_ValueType, AUTOMATIC, IOHWAB_APPL_DATA) Value,
  IoHwAb_LengthType AnaInDirLength);
#endif /* (IOHWAB_USE_ANA_IN_DIR == STD_ON) */

/* polyspace-end MISRA-C3:5.9 [Justified:Unset] "Not a defect" */
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"

#endif /* ((IOHWAB_USE_ANA_IN == STD_ON) || (IOHWAB_USE_ANA_IN_DIR == STD_ON)) */
/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"

#if (IOHWAB_USE_ANA_IN == STD_ON)
/*******************************************************************************
** Function Name        : IoHwAb_AnaInInit                                    **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          :                                                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : BufIdx                                              **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : Level                                               **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                          IoHwAb_GaaAnaInFiltResults,                       **
**                          IoHwAb_GaaAnaInInfos,                             **
**                          IoHwAb_GaaAnaInAdcResults,                        **
**                          IoHwAb_GblAnaInAdcIsBusy,                         **
**                          IoHwAb_GaaAnaInAllGroupInfos                      **
**                        Function(s) invoked    :                            **
**                          Adc_SetupResultBuffer,                            **
**                          Det_ReportError,                                  **
**                          Dem_ReportErrorStatus                             **
*******************************************************************************/
/* @Trace: IoHwAb_SUD_API_011 */
FUNC(void, IOHWAB_CODE)IoHwAb_AnaInInit(void)
{
  uint8 LucIdx;
  uint8 LucAdcHwUnitId;

  for (LucIdx = 0; LucIdx < IOHWAB_ANAIN_NUM_LGC; LucIdx++)
  {
    IoHwAb_GaaAnaInFiltResults[LucIdx].blEnable = TRUE;
    IoHwAb_GaaAnaInFiltResults[LucIdx].usFiltResult
      = IoHwAb_GaaAnaInInfos[LucIdx].usDefVal;
    LucAdcHwUnitId = IoHwAb_GaaAnaInInfos[LucIdx].ucAdcHwUnitId;

    if (Adc_SetupResultBuffer(IoHwAb_GaaAnaInInfos[LucIdx].ddAdcGroupType,
      &(IoHwAb_GaaAnaInAdcResults.usOneChBuffer[LucAdcHwUnitId])) != E_OK)
    {
#if (IOHWAB_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError((uint16)IOHWAB_MODULE_ID, (uint8)IOHWAB_INSTANCE_ID,
        (uint8)IOHWAB_ANAIN_INIT_SID, (uint8)IOHWAB_E_DET_SETUP_FAIL);
#endif /* (IOHWAB_DEV_ERROR_DETECT == STD_ON) */
#if (IOHWAB_USE_DEM_EVENT == STD_ON)
      Dem_ReportErrorStatus(IOHWAB_E_SETUP_FAIL, DEM_EVENT_STATUS_FAILED);
#endif /* (IOHWAB_USE_DEM_EVENT == STD_ON) */
    }
  }

  for (LucIdx = 0; LucIdx < IOHWAB_ADCHWUNIT_MAX_NUM; LucIdx++)
  {
    IoHwAb_GblAnaInAdcIsBusy[LucIdx] = FALSE;
  }

  for (LucIdx = 0; LucIdx < IOHWAB_ANAIN_NUM_ADC_ALLGROUP; LucIdx++)
  {
    if (Adc_SetupResultBuffer(IoHwAb_GaaAnaInAllGroupInfos[LucIdx].ddAdcAllGroupType,
      IoHwAb_GaaAnaInAdcResults.usAllChBuffer[LucIdx]) != E_OK)
    {
#if (IOHWAB_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError((uint16)IOHWAB_MODULE_ID, (uint8)IOHWAB_INSTANCE_ID,
        (uint8)IOHWAB_ANAIN_INIT_SID, (uint8)IOHWAB_E_DET_SETUP_FAIL);
#endif /* (IOHWAB_DEV_ERROR_DETECT == STD_ON) */
#if (IOHWAB_USE_DEM_EVENT == STD_ON)
      Dem_ReportErrorStatus(IOHWAB_E_SETUP_FAIL, DEM_EVENT_STATUS_FAILED);
#endif /* (IOHWAB_USE_DEM_EVENT == STD_ON) */
    }
  }
}


/*******************************************************************************
** Function Name        : IoHwAb_AnaInConvertStart                            **
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
**                          IoHwAb_GaaAnaInAllGroupInfos                      **
**                        Function(s) invoked    :                            **
**                          Adc_EnableGroupNotification                       **
*******************************************************************************/
/* @Trace: SWS_IoHwAb_00078 SWS_IoHwAb_00121 SWS_IoHwAb_00104 */
/* @Trace: IoHwAb_SUD_API_012 */
FUNC(void, IOHWAB_CODE)IoHwAb_AnaInConvertStart(void)
{
  uint8 LucIdx;

  /* enable each adc's notification function */
  for (LucIdx = 0; LucIdx < IOHWAB_ANAIN_NUM_ADC_ALLGROUP; LucIdx++)
  {
    Adc_EnableGroupNotification(IoHwAb_GaaAnaInAllGroupInfos[LucIdx].ddAdcAllGroupType);
  }
}


/*******************************************************************************
** Function Name        : IoHwAb_AnaInConvertStop                             **
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
**                          IoHwAb_GaaAnaInAllGroupInfos                      **
**                        Function(s) invoked    :                            **
**                          Adc_DisableGroupNotification                      **
*******************************************************************************/
/* @Trace: SWS_IoHwAb_00078 */
/* @Trace: IoHwAb_SUD_API_013 */
FUNC(void, IOHWAB_CODE)IoHwAb_AnaInConvertStop(void)
{
  uint8 LucIdx;

  /* disable each adc's notification function */
  for (LucIdx = 0; LucIdx < IOHWAB_ANAIN_NUM_ADC_ALLGROUP; LucIdx++)
  {
    Adc_DisableGroupNotification(IoHwAb_GaaAnaInAllGroupInfos[LucIdx].ddAdcAllGroupType);
  }
}

/*******************************************************************************
** Function Name        : IoHwAb_AnaInRead                                    **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          :                                                     **
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
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                          IoHwAb_GaaAnaInFiltResults                        **
**                        Function(s) invoked    :                            **
**                          SchM_Enter_IoHwAb_IoHwAbProtection,               **
**                          SchM_Exit_IoHwAb_IoHwAbProtection                 **
*******************************************************************************/

/* @Trace: SRS_IoHwAb_12409 SRS_IoHwAb_12410 */
/* @Trace: SWR_IOHWAB_709_001_API SWR_IOHWAB_Safety_002 SWR_IOHWAB_Safety_001 */
/* @Trace: IoHwAb_SUD_API_014 */
FUNC(void, IOHWAB_CODE)IoHwAb_AnaInRead(IoHwAb_IndexType ChIdx,
  P2VAR(IoHwAb_ValueType, AUTOMATIC, IOHWAB_APPL_DATA) Value)
{
  if (IOHWAB_ANAIN_NUM_LGC <= ChIdx)
  {
#if (IOHWAB_DEV_ERROR_DETECT == STD_ON)
    (void)Det_ReportError((uint16)IOHWAB_MODULE_ID, (uint8)IOHWAB_INSTANCE_ID,
      (uint8)IOHWAB_ANAIN_READ_DIRECT_SID, (uint8)IOHWAB_E_DET_WRONG_PARAM);
#endif /* (IOHWAB_DEV_ERROR_DETECT == STD_ON) */
#if (IOHWAB_USE_DEM_EVENT == STD_ON)
    Dem_ReportErrorStatus(IOHWAB_E_WRONG_PARAM, DEM_EVENT_STATUS_FAILED);
#endif /* (IOHWAB_USE_DEM_EVENT == STD_ON) */    
  }
  else
  {
    SchM_Enter_IoHwAb_IoHwAbProtection();
    if (Value != NULL_PTR)
    {
      *Value = IoHwAb_GaaAnaInFiltResults[ChIdx].usFiltResult;
    }
    SchM_Exit_IoHwAb_IoHwAbProtection();
  }
}


/*******************************************************************************
** Function Name        : IoHwAb_AnaInReadDirect                              **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          :                                                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non-Reentrant                                       **
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
**                          IoHwAb_GaaAnaInInfos,                             **
**                          IoHwAb_GblAnaInAdcIsBusy,                         **
**                          IoHwAb_GaaAnaInAdcResults                         **
**                        Function(s) invoked    :                            **
**                          SchM_Enter_IoHwAb_IoHwAbProtection,               **
**                          SchM_Exit_IoHwAb_IoHwAbProtection,                **
**                          Adc_GetGroupStatus,                               **
**                          Adc_StartGroupConversion,                         **
**                          Det_ReportError,                                  **
**                          Dem_ReportErrorStatus                             **
*******************************************************************************/

/* @Trace: SRS_IoHwAb_12410 */
/* @Trace: SWS_IoHwAb_00078 SWR_IOHWAB_301_001 */
/* @Trace: SWR_IOHWAB_707_001 */
/* @Trace: IoHwAb_SUD_API_015 */
/* polyspace +1 CODE-METRICS:CALLS [Justified:Low] "Function is called to get A/D conversion result" */
FUNC(Std_ReturnType, IOHWAB_CODE)IoHwAb_AnaInReadDirect(IoHwAb_IndexType ChIdx,
  P2VAR(IoHwAb_ValueType, AUTOMATIC, IOHWAB_APPL_DATA) Value)
{
  Std_ReturnType LddError = E_OK;
  uint8 LucAdcHwUnitId;
#if !(defined(IOHWAB_MCAL_CYPRESS_CYTXXX))
  uint8 LucAdcHwUnitNum;
#endif
  /*  Check if Value is NULL_PTR.  */
  if (Value == NULL_PTR)
  {
    #if (IOHWAB_DEV_ERROR_DETECT == STD_ON)
    (void)Det_ReportError((uint16)IOHWAB_MODULE_ID, (uint8)IOHWAB_INSTANCE_ID,
    (uint8)IOHWAB_ANAIN_READ_DIRECT_SID, (uint8)IOHWAB_E_DET_WRONG_PARAM);
    #endif /* (IOHWAB_DEV_ERROR_DETECT == STD_ON) */
    #if (IOHWAB_USE_DEM_EVENT == STD_ON)
    Dem_ReportErrorStatus(IOHWAB_E_WRONG_PARAM, DEM_EVENT_STATUS_FAILED);
    #endif /* (IOHWAB_USE_DEM_EVENT == STD_ON) */
    LddError = E_NOT_OK;
  }

  /*  Check if IOHWAB_ANAIN_NUM_LGC is less than or equal to ChIdx.  */
  if (LddError == E_OK)
  {
    if (IOHWAB_ANAIN_NUM_LGC <= ChIdx)
    {
      #if (IOHWAB_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError((uint16)IOHWAB_MODULE_ID, (uint8)IOHWAB_INSTANCE_ID,
      (uint8)IOHWAB_ANAIN_READ_DIRECT_SID, (uint8)IOHWAB_E_DET_WRONG_PARAM);
      #endif /* (IOHWAB_DEV_ERROR_DETECT == STD_ON) */
      #if (IOHWAB_USE_DEM_EVENT == STD_ON)
      Dem_ReportErrorStatus(IOHWAB_E_WRONG_PARAM, DEM_EVENT_STATUS_FAILED);
      #endif /* (IOHWAB_USE_DEM_EVENT == STD_ON) */
      LddError = E_NOT_OK;
    }
    else
    {
      LucAdcHwUnitId = IoHwAb_GaaAnaInInfos[ChIdx].ucAdcHwUnitId;
#if !(defined(IOHWAB_MCAL_CYPRESS_CYTXXX))
    /* polyspace-begin DEFECT:USELESS_WRITE MISRA-C3:2.2 [Justified:Low] "It is used for other MCUs." */
      LucAdcHwUnitNum = IoHwAb_GaaAnaInInfos[ChIdx].ucAdcHwUnitNum;
    /* polyspace-end DEFECT:USELESS_WRITE MISRA-C3:2.2 [Justified:Low] "It is used for other MCUs." */
#endif
    }
  }

  SchM_Enter_IoHwAb_IoHwAbProtection();

  /*  Check if Adc busy flag is set.  */
  if (LddError == E_OK)
  {
    if (IoHwAb_GblAnaInAdcIsBusy[LucAdcHwUnitId] == TRUE)
    {
      #if (IOHWAB_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError((uint16)IOHWAB_MODULE_ID, (uint8)IOHWAB_INSTANCE_ID,
        (uint8)IOHWAB_ANAIN_READ_DIRECT_SID, (uint8)IOHWAB_E_DET_BUSY);
      #endif /* (IOHWAB_DEV_ERROR_DETECT == STD_ON) */
      #if (IOHWAB_USE_DEM_EVENT == STD_ON)
      Dem_ReportErrorStatus(IOHWAB_E_BUSY, DEM_EVENT_STATUS_FAILED);
      #endif /* (IOHWAB_USE_DEM_EVENT == STD_ON) */
      LddError = IOHWAB_ANAIN_BUSY_ERR;
    }
    else
    {
      IoHwAb_GblAnaInAdcIsBusy[LucAdcHwUnitId] = TRUE;
    }
  }

  SchM_Exit_IoHwAb_IoHwAbProtection();

  if (LddError == E_OK)
  {
    SchM_Enter_IoHwAb_IoHwAbProtection();

    Adc_StartGroupConversion(IoHwAb_GaaAnaInInfos[ChIdx].ddAdcGroupType);

    #if (defined(IOHWAB_MCAL_NXP_S32K14X))
    LddError = IoHwAb_AnaInConvCompleted(LucAdcHwUnitNum, 0U);
    #elif (defined(IOHWAB_MCAL_CYPRESS_CYTXXX))
    LddError = IoHwAb_AnaInConvCompleted(
    (const Adc_GroupConfigType *) Adc_GetGroupConfig(IoHwAb_GaaAnaInInfos[ChIdx].ddAdcGroupType));
    #else
    LddError = IoHwAb_AnaInConvCompleted(LucAdcHwUnitNum);
    #endif
	
    #if (defined(IOHWAB_MCAL_FREESCALE_MPC560XB) || defined(IOHWAB_MCAL_FREESCALE_MPC574XR) || \
         defined(IOHWAB_MCAL_ST_SPC58XCX)        || defined(IOHWAB_MCAL_ST_SPC58XHX) || \
         defined(IOHWAB_MCAL_NXP_S32K14X)        || defined(IOHWAB_MCAL_NXP_S32G2X) || \
         defined(IOHWAB_MCAL_NXP_S32K31X)        || defined(IOHWAB_MCAL_NXP_S32K31X_3_0_0_P01_HF01))
    SchM_Exit_IoHwAb_IoHwAbProtection();
    (void)Adc_ReadGroup( IoHwAb_GaaAnaInInfos[ChIdx].ddAdcGroupType, Value);

    #else /* Aurix, RH850, Cypress */
      #if (defined(IOHWAB_MCAL_CYPRESS_CYTXXX))
      IOHWAB_ADC_CONV_PROC((const Adc_GroupConfigType *)Adc_GetGroupConfig(
        IoHwAb_GaaAnaInInfos[ChIdx].ddAdcGroupType));
      #else
      IOHWAB_ADC_CONV_PROC(LucAdcHwUnitNum);
      #endif
    SchM_Exit_IoHwAb_IoHwAbProtection();        
      #if (defined(IOHWAB_MCAL_CYPRESS_S6J32XX) || defined(IOHWAB_MCAL_CYPRESS_S6J33XX ) || \
           defined(IOHWAB_MCAL_CYPRESS_CYTXXX))
      (void)Adc_ReadGroup( IoHwAb_GaaAnaInInfos[ChIdx].ddAdcGroupType, Value);
      #else /* When Arix, RH850 */
      *Value = IoHwAb_GaaAnaInAdcResults.usOneChBuffer[LucAdcHwUnitId];
      Adc_StopGroupConversion(IoHwAb_GaaAnaInInfos[ChIdx].ddAdcGroupType);
      #endif
    #endif

    /*  Clear the Adc busy flag.  */
    SchM_Enter_IoHwAb_IoHwAbProtection();
    IoHwAb_GblAnaInAdcIsBusy[LucAdcHwUnitId] = FALSE;
    SchM_Exit_IoHwAb_IoHwAbProtection();
  }

  return LddError;
}


/*******************************************************************************
** Function Name        : IoHwAb_AnaInFreeze                                  **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          :                                                     **
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
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                          IoHwAb_GaaAnaInFiltResults                        **
**                        Function(s) invoked    :                            **
**                          SchM_Enter_IoHwAb_IoHwAbProtection,               **
**                          SchM_Exit_IoHwAb_IoHwAbProtection                 **
*******************************************************************************/

/* @Trace: SWR_IOHWAB_709_002_API */
/* @Trace: IoHwAb_SUD_API_016 */ 
FUNC(void, IOHWAB_CODE)IoHwAb_AnaInFreeze(IoHwAb_IndexType ChIdx)
{
  SchM_Enter_IoHwAb_IoHwAbProtection();
  if (ChIdx < IOHWAB_ANAIN_NUM_LGC)
  {
    IoHwAb_GaaAnaInFiltResults[ChIdx].blEnable = FALSE;
  }
  SchM_Exit_IoHwAb_IoHwAbProtection();
}


/*******************************************************************************
** Function Name        : IoHwAb_AnaInUnfreeze                                **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          :                                                     **
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
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                          IoHwAb_GaaAnaInFiltResults                        **
**                        Function(s) invoked    :                            **
**                          SchM_Enter_IoHwAb_IoHwAbProtection,               **
**                          SchM_Exit_IoHwAb_IoHwAbProtection                 **
*******************************************************************************/

/* @Trace: SWR_IOHWAB_709_003_API */
/* @Trace: IoHwAb_SUD_API_017 */
FUNC(void, IOHWAB_CODE)IoHwAb_AnaInUnfreeze(IoHwAb_IndexType ChIdx)
{
  SchM_Enter_IoHwAb_IoHwAbProtection();
  if (ChIdx < IOHWAB_ANAIN_NUM_LGC)
  {
    IoHwAb_GaaAnaInFiltResults[ChIdx].blEnable = TRUE;
  }
  SchM_Exit_IoHwAb_IoHwAbProtection();
}

/*******************************************************************************
** Function Name        : IoHwAb_AnaInFilter                                  **
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
**                          IoHwAb_GaaAnaInFiltResults,                       **
**                          IoHwAb_GaaAnaInInfos                              **
**                        Function(s) invoked    : none                       **
*******************************************************************************/
/* @Trace: SWR_IOHWAB_708_001 SWR_IOHWAB_708_002 SWR_IOHWAB_708_003 */
/* @Trace: SWS_IoHwAb_00021 */
/* @Trace: IoHwAb_SUD_API_018 */
FUNC(void, IOHWAB_CODE)IoHwAb_AnaInFilter(void)
{
  uint8 LucIdx;
  uint8 LucFiltCst = 0U;          /*store localy the filtering constant*/

  for (LucIdx = 0U; LucIdx < IOHWAB_ANAIN_NUM_LGC; LucIdx++)
  {
    /*take every configured analog input*/
    if (IoHwAb_GaaAnaInFiltResults[LucIdx].blEnable != 0U)
    {
      /*for code zise optimization*/
      LucFiltCst = IoHwAb_GaaAnaInInfos[LucIdx].ucFiltCst;

      if (LucFiltCst != 0U)
      {
        /*we do the filtering for this one*/
        IoHwAb_GaaAnaInFiltResults[LucIdx].usFiltResult
          = IoHwAb_AnaInFirstOrderFiltering(               /*new filtered value*/
            IoHwAb_GaaAnaInFiltResults[LucIdx].usFiltResult, /*previous filtered value*/
            IoHwAb_GaaAnaInFiltResults[LucIdx].usRawResult,  /*current sample*/
            LucFiltCst);                                     /*filtering constant*/

        IoHwAb_GaaAnaInFiltResults[LucIdx].usFiltResult
          = IoHwAb_GaaAnaInFiltResults[LucIdx].usFiltResult;
      }
      else
      {
        /*input defined with no filtering*/
        /*just copy the raw value*/
        IoHwAb_GaaAnaInFiltResults[LucIdx].usFiltResult
          = IoHwAb_GaaAnaInFiltResults[LucIdx].usRawResult;
      }
    }
  }
}

/*******************************************************************************
** Function Name        : IoHwAb_AnaInConvertAllChannels                      **
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
**                          IoHwAb_GblAnaInAdcIsBusy,                         **
**                          IoHwAb_GaaAnaInAllGroupInfos                      **
**                        Function(s) invoked    :                            **
**                          Adc_StartGroupConversion,                         **
**                          Det_ReportError,                                  **
**                          Dem_ReportErrorStatus                             **
*******************************************************************************/
/* @Trace: IoHwAb_SUD_API_019 */
FUNC(Std_ReturnType, IOHWAB_CODE)IoHwAb_AnaInConvertAllChannels(void)
{
  uint8 LucIdx;
  uint8 LucHwUnitId = 0U;
  Std_ReturnType LddError = E_OK;

  for (LucIdx = 0; LucIdx < IOHWAB_ANAIN_NUM_ADC_ALLGROUP; LucIdx++)
  {
    SchM_Enter_IoHwAb_IoHwAbProtection();
    LucHwUnitId = IoHwAb_GaaAnaInAllGroupInfos[LucIdx].ucAdcHwUnitId;
    if (IoHwAb_GblAnaInAdcIsBusy[LucHwUnitId] == FALSE)
    {
      IoHwAb_GblAnaInAdcIsBusy[LucHwUnitId] = TRUE;
      SchM_Exit_IoHwAb_IoHwAbProtection();
    }
    else
    {
      SchM_Exit_IoHwAb_IoHwAbProtection();
#if (IOHWAB_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError((uint16)IOHWAB_MODULE_ID, (uint8)IOHWAB_INSTANCE_ID,
        (uint8)IOHWAB_ANAIN_CONVERT_ALL_SID, (uint8)IOHWAB_E_DET_BUSY);
#endif /* (IOHWAB_DEV_ERROR_DETECT == STD_ON) */
#if (IOHWAB_USE_DEM_EVENT == STD_ON)
      Dem_ReportErrorStatus(IOHWAB_E_BUSY, DEM_EVENT_STATUS_FAILED);
#endif /* (IOHWAB_USE_DEM_EVENT == STD_ON) */
      LddError = IOHWAB_ANAIN_BUSY_ERR;
    }
  }

  for (LucIdx = 0; LucIdx < IOHWAB_ANAIN_NUM_ADC_ALLGROUP; LucIdx++)
  {
    if (Adc_GetGroupStatus(IoHwAb_GaaAnaInAllGroupInfos[LucIdx].ddAdcAllGroupType)
      != ADC_BUSY)
    {
      /* start group(for all channels in ADC module) conversion */
      Adc_StartGroupConversion(IoHwAb_GaaAnaInAllGroupInfos[LucIdx].ddAdcAllGroupType);
    }
    else
    {
#if (IOHWAB_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError((uint16)IOHWAB_MODULE_ID, (uint8)IOHWAB_INSTANCE_ID,
        (uint8)IOHWAB_ANAIN_CONVERT_ALL_SID, (uint8)IOHWAB_E_DET_MCAL_BUSY);
#endif /* (IOHWAB_DEV_ERROR_DETECT == STD_ON) */
      LddError = IOHWAB_ANAIN_BUSY_ERR;
    }
  }

  return LddError;
}

/*******************************************************************************
** Function Name        : IoHwAb_AnaInAdcAllGrNf                              **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          :                                                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : GroupId                                             **
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
**                          IoHwAb_GaaAnaInInfos,                             **
**                          IoHwAb_GaaAnaInFiltResults,                       **
**                          IoHwAb_GblAnaInAdcIsBusy                          **
**                        Function(s) invoked    :                            **
**                          IoHwAb_AnaInConvProcAllChannels,                  **
**                          IoHwAb_IOMAnaInAcqEnd                             **
*******************************************************************************/
/* @Trace: IoHwAb_SUD_API_020 */
FUNC(void, IOHWAB_CODE)IoHwAb_AnaInAdcAllGrNf(uint8 GroupId)
{
  uint8 LucIdx;
  uint8 LucBufIdx;
  uint8 LucHwUnitId = 0U;
  boolean LblDoCbk = TRUE;

  for (LucIdx = 0; LucIdx < IOHWAB_ANAIN_NUM_LGC; LucIdx++)
  {
    if (IoHwAb_GaaAnaInInfos[LucIdx].ucAdcGroupId == GroupId)
    {
      /* polyspace-begin DEFECT:USELESS_IF [Not a defect:Low] "It is not a defect. The condition to entry the branch will depend on user configuration" */
      if (LucHwUnitId != IoHwAb_GaaAnaInInfos[LucIdx].ucAdcHwUnitId)
      {
        /* In Normal case, it is assigned only once. */
        LucHwUnitId = IoHwAb_GaaAnaInInfos[LucIdx].ucAdcHwUnitId;
      }
      /* polyspace-end DEFECT:USELESS_IF [Not a defect:Low] "It is not a defect. The condition to entry the branch will depend on user configuration" */
      LucBufIdx = IoHwAb_GaaAnaInInfos[LucIdx].ucIndexInResultBuffer;
      IoHwAb_GaaAnaInFiltResults[LucIdx].usRawResult
        = IoHwAb_GaaAnaInAdcResults.usAllChBuffer[GroupId][LucBufIdx];
    }
  }

  SchM_Enter_IoHwAb_IoHwAbProtection();
  /* ADC Busy flag is cleared */
  IoHwAb_GblAnaInAdcIsBusy[LucHwUnitId] = FALSE;
  
  /* Callback function */
  for (LucIdx = 0; LucIdx < IOHWAB_ANAIN_NUM_ADC_ALLGROUP; LucIdx++)
  {
    LucHwUnitId = IoHwAb_GaaAnaInAllGroupInfos[LucIdx].ucAdcHwUnitId;
    if (IoHwAb_GblAnaInAdcIsBusy[LucHwUnitId] == TRUE)
    {
      LblDoCbk = FALSE;
    }
  }
  SchM_Exit_IoHwAb_IoHwAbProtection();

  /* All resource is free check */
  /* polyspace-begin DEFECT:USELESS_IF [Not a defect:Low] "It is not a defect. The condition to entry the branch will depend on user configuration" */
  if (LblDoCbk == TRUE)
  {
    IoHwAb_IOMAnaInAcqEnd();
  }
  /* polyspace-end DEFECT:USELESS_IF [Not a defect:Low] "It is not a defect. The condition to entry the branch will depend on user configuration" */
}
#endif /* (IOHWAB_USE_ANA_IN == STD_ON) */

/*polyspace:begin<MISRA-C:17.4:Not a defect:Justify with annotations> No Impact of this rule violation*/
/*polyspace-begin RTE:UNR [Not a Defect] "No Impact of this rule violation"*/
#if (IOHWAB_USE_ANA_IN_DIR == STD_ON)
/*******************************************************************************
** Function Name        : IoHwAb_AnaInDirReadDirect                           **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          :                                                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : ChIdx                                               **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : Value                                               **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                          IoHwAb_GaaAnaInDirInfos,                          **
**                          IoHwAb_GblAnaInAdcIsBusy,                         **
**                          IOHWAB_ANAIN_NUM_ADC_ALLGROUP                     **
**                        Function(s) invoked    :                            **
**                          Adc_GetGroupStatus,                               **
**                          Adc_SetupResultBuffer,                            **
**                          Adc_StartGroupConversion,                         **
**                          SchM_Enter_IoHwAb_IoHwAbProtection,               **
**                          SchM_Exit_IoHwAb_IoHwAbProtection,                **
**                          IoHwAb_AnaInDirConvProc,                          **
**                          IoHwAb_DetCheckAnaInDirReadDirect                 **
*******************************************************************************/
/* @Trace: SRS_IoHwAb_12410 */
/* @Trace: SWS_IoHwAb_00078 SWR_IOHWAB_301_001 */
/* @Trace: IoHwAb_SUD_API_021 */
FUNC(Std_ReturnType, IOHWAB_CODE)IoHwAb_AnaInDirReadDirect(IoHwAb_IndexType ChIdx,
  P2VAR(IoHwAb_ValueType, AUTOMATIC, IOHWAB_APPL_DATA) Value,
  IoHwAb_LengthType AnaInDirLength)
{
  uint8 LucIdx;
  uint8 LucAdcHwUnitId;
#if !(defined(IOHWAB_MCAL_CYPRESS_CYTXXX))
  uint8 LucAdcHwUnitNum = IoHwAb_GaaAnaInDirInfos[ChIdx].ucAdcHwUnitNum;
#endif

  Std_ReturnType LddError = E_OK;
  LucAdcHwUnitId = IoHwAb_GaaAnaInDirInfos[ChIdx].ucAdcHwUnitId;

  /* DET,DEM check */
  LddError = IoHwAb_DetCheckAnaInDirReadDirect(ChIdx, Value, AnaInDirLength);

  if (LddError == E_OK)
  {
    SchM_Enter_IoHwAb_IoHwAbProtection();

    Adc_StartGroupConversion(IoHwAb_GaaAnaInDirInfos[ChIdx].ddAdcGroupType);
    #if (defined(IOHWAB_MCAL_NXP_S32K14X))
    if (LucAdcGroupLength > 0U)
    {
      LddError = IoHwAb_AnaInConvCompleted(LucAdcHwUnitNum, (LucAdcGroupLength - 1U));
    }
    else 
    {
      LddError = IoHwAb_AnaInConvCompleted(LucAdcHwUnitNum, 0U);
    }
    #elif (defined(IOHWAB_MCAL_CYPRESS_CYTXXX))
    LddError = IoHwAb_AnaInConvCompleted(
    (const Adc_GroupConfigType *) Adc_GetGroupConfig(IoHwAb_GaaAnaInDirInfos[ChIdx].ddAdcGroupType));
    #else
    LddError = IoHwAb_AnaInConvCompleted(LucAdcHwUnitNum);
    #endif

    #if (defined(IOHWAB_MCAL_FREESCALE_MPC560XB)|| defined(IOHWAB_MCAL_FREESCALE_MPC574XR) ||\
         defined(IOHWAB_MCAL_ST_SPC58XCX)       || defined(IOHWAB_MCAL_ST_SPC58XHX) ||\
         defined(IOHWAB_MCAL_NXP_S32K14X)       || defined(IOHWAB_MCAL_NXP_S32G2X) || \
         defined(IOHWAB_MCAL_NXP_S32K31X)       || defined(IOHWAB_MCAL_NXP_S32K31X_3_0_0_P01_HF01))
    SchM_Exit_IoHwAb_IoHwAbProtection();
    (void)Adc_ReadGroup( IoHwAb_GaaAnaInDirInfos[ChIdx].ddAdcGroupType, IoHwAb_GaaAnaInDirAdcResults[LucAdcHwUnitId]);
    #else /* Aurix, RH850, Cypress */
      #if (defined(IOHWAB_MCAL_CYPRESS_CYTXXX))
      IOHWAB_ADC_CONV_PROC((const Adc_GroupConfigType *)Adc_GetGroupConfig(
        IoHwAb_GaaAnaInDirInfos[ChIdx].ddAdcGroupType));
      #else
      IOHWAB_ADC_CONV_PROC(LucAdcHwUnitNum);
      #endif
      SchM_Exit_IoHwAb_IoHwAbProtection();
      #if (defined(IOHWAB_MCAL_CYPRESS_S6J32XX) || defined(IOHWAB_MCAL_CYPRESS_S6J33XX) ||\
           defined(IOHWAB_MCAL_CYPRESS_CYTXXX))
      (void)Adc_ReadGroup(IoHwAb_GaaAnaInDirInfos[ChIdx].ddAdcGroupType,
                         IoHwAb_GaaAnaInDirAdcResults[LucAdcHwUnitId]);
      #else /* When Aurix, RH850 */
      Adc_StopGroupConversion(IoHwAb_GaaAnaInDirInfos[ChIdx].ddAdcGroupType);
      #endif
    #endif

    for (LucIdx = 0; LucIdx < AnaInDirLength; LucIdx++)
    {
      *Value = IoHwAb_GaaAnaInDirAdcResults[LucAdcHwUnitId][LucIdx];
/* polyspace-begin MISRA-C3:17.8 [Justified:Unset] "This function parameter has to be changed for an adc group which has multiple adc channels." */
      Value++;
/* polyspace-end MISRA-C3:17.8 [Justified:Unset] "This function parameter has to be changed for an adc group which has multiple adc channels." */
    }

    /*  Clear the Adc busy flag.  */
    SchM_Enter_IoHwAb_IoHwAbProtection();
    IoHwAb_GblAnaInAdcIsBusy[LucAdcHwUnitId] = FALSE;
    SchM_Exit_IoHwAb_IoHwAbProtection();
  }

  return LddError;
}
#endif /* (IOHWAB_USE_ANA_IN_DIR == STD_ON) */
/*polyspace:end<MISRA-C:17.4:Not a defect:Justify with annotations> No Impact of this rule violation*/
/*polyspace-end RTE:UNR*/
#if ((IOHWAB_USE_ANA_IN == STD_ON) || (IOHWAB_USE_ANA_IN_DIR == STD_ON))
/*******************************************************************************
** Function Name        : IoHwAb_AnaInFirstOrderFiltering                     **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          :                                                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : FiltValue, RawValue, Gain                           **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : result                                              **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : none                       **
**                        Function(s) invoked    : none                       **
*******************************************************************************/
/* @Trace: SWS_IoHwAb_00019 SWR_IOHWAB_708_001 SWR_IOHWAB_708_002 SWR_IOHWAB_708_003*/
FUNC(uint16, IOHWAB_CODE)IoHwAb_AnaInFirstOrderFiltering(
  uint16 FiltValue, uint16 RawValue, uint8 Gain)
{
  uint16 LusFilteredResult;
  if (FiltValue >= RawValue)
  {
    LusFilteredResult = RawValue + (uint16)((((uint32)FiltValue - (uint32)RawValue) * (uint32)Gain) >> 8);
  }
  else
  {
    LusFilteredResult = RawValue - (uint16)((((uint32)RawValue - (uint32)FiltValue) * (uint32)Gain) >> 8);
  }
  return LusFilteredResult;
}
/*polyspace:begin<MISRA-C:11.3:Not a defect:Justify with annotations> No Impact of this rule violation*/
/*polyspace-begin RTE:UNR [Not a Defect] "No Impact of this rule violation"*/
/* polyspace-begin MISRA-C3:18.1 [Justified:Unset] "Not a defect and validated by test cases" */
/*******************************************************************************
** Function Name        : IoHwAb_AnaInConvCompleted                           **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          :                                                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : IoHwAb_AdcHwUnitId                                  **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : IoHwAb_AdcHwUnitNum                                 **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : none                       **
**                        Function(s) invoked    : none                       **
*******************************************************************************/
/* @Trace: SRS_IoHwAb_12339 */
/* @Trace: SWR_IOHWAB_Safety_002 */
/* @Trace: IoHwAb_SUD_API_022 */
#if (defined(IOHWAB_MCAL_NXP_S32K14X))
static FUNC(Std_ReturnType, IOHWAB_CODE)IoHwAb_AnaInConvCompleted(uint8 IoHwAb_AdcHwUnitNum, uint8 IoHwAb_AdcDirLength)
{
  volatile uint16 LulAdcDelayCounter = IOHWAB_ADC_READDIRECT_MAX_DELAY ;
  Std_ReturnType LddError = (Std_ReturnType)E_OK;

  if (IoHwAb_AdcHwUnitNum < 0xFFU)
  {
    while( IOHWAB_ADC_CONV_COMPLETED(IoHwAb_AdcHwUnitNum, IoHwAb_AdcDirLength) == 0U )
    {
      if(LulAdcDelayCounter > 0)
      {
        LulAdcDelayCounter--;
      }
      else
      {
        break;
      }
    }

    if (LulAdcDelayCounter == 0U)
    {
      LddError = (Std_ReturnType)E_NOT_OK;
    }
  }
  else
  {
    LddError = (Std_ReturnType)E_NOT_OK;
  }
  return LddError;
}
#elif (defined(IOHWAB_MCAL_CYPRESS_CYTXXX))
static FUNC(Std_ReturnType, IOHWAB_CODE)IoHwAb_AnaInConvCompleted(
  const Adc_GroupConfigType * IoHwAb_AdcGroupCfg)
{
  volatile uint16 LulAdcDelayCounter;
  Std_ReturnType LddError;
  volatile uint32 LulAdcChBaseAddress;
  const Adc_ChannelConfigType * LpAdcChConfig;

  LulAdcDelayCounter = IOHWAB_ADC_READDIRECT_MAX_DELAY;
  LddError = (Std_ReturnType)E_OK;
  LpAdcChConfig =
    Adc_GetChannelConfig(IoHwAb_AdcGroupCfg->LastLogicalChannelConfigIndex);
  LulAdcChBaseAddress = LpAdcChConfig->RegisterBase;

  if (LulAdcChBaseAddress != 0U)
  {
    while( IOHWAB_ADC_CONV_COMPLETED(LulAdcChBaseAddress) == 0U )
    {
      if(LulAdcDelayCounter > 0)
      {
        LulAdcDelayCounter--;
      }
      else
      {
        break;
      }
    }

    if (LulAdcDelayCounter == 0U)
    {
      LddError = (Std_ReturnType)E_NOT_OK;
    }
  }
  else
  {
    LddError = (Std_ReturnType)E_NOT_OK;
  }
  return LddError;
}
#else
static FUNC(Std_ReturnType, IOHWAB_CODE)IoHwAb_AnaInConvCompleted(uint8 IoHwAb_AdcHwUnitNum)
{
  volatile uint16 LulAdcDelayCounter = IOHWAB_ADC_READDIRECT_MAX_DELAY ;
  Std_ReturnType LddError = (Std_ReturnType)E_OK;

  if (IoHwAb_AdcHwUnitNum < 0xFFU)
  {
    while( IOHWAB_ADC_CONV_COMPLETED(IoHwAb_AdcHwUnitNum) == 0U )
    {
      if(LulAdcDelayCounter > 0)
      {
        LulAdcDelayCounter--;
      }
      else
      {
        break;
      }
    }

    if (LulAdcDelayCounter == 0U)
    {
      LddError = (Std_ReturnType)E_NOT_OK;
    }
    IOHWAB_ADC_ACKNOWLEDGED(IoHwAb_AdcHwUnitNum);
  }
  else
  {
    LddError = (Std_ReturnType)E_NOT_OK;
  }
  return LddError;
}
#endif

#endif /* ((IOHWAB_USE_ANA_IN == STD_ON) || (IOHWAB_USE_ANA_IN_DIR == STD_ON)) */

#if (IOHWAB_USE_ANA_IN_DIR == STD_ON)
/*******************************************************************************
** Function Name        : IoHwAb_DetCheckAnaInDirReadDirect                   **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          : This function will check the validity of the        **
**                        parameters passed in the AnaInDirReadDirect         **
**                        function.                                           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : ChIdx                                               **
**                        Value                                               **
                          AnaInDirLength                                      **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                        IoHwAb_GaaAnaInDirInfos                             **
**                        IoHwAb_GaaAnaInDirAdcResults                        **
**                        IoHwAb_GblAnaInAdcIsBusy                            **
                                                                              **
**                        Function(s) invoked :                               **
**                        Det_ReportError                                     **
**                        Dem_ReportErrorStatus                               **
**                        Adc_SetupResultBuffer                               **
**                        SchM_Enter_IoHwAb_IoHwAbProtection                  **
**                        SchM_Exit_IoHwAb_IoHwAbProtection                   **
*******************************************************************************/
static FUNC(Std_ReturnType, IOHWAB_CODE) IoHwAb_DetCheckAnaInDirReadDirect(
  IoHwAb_IndexType ChIdx,
  CONSTP2CONST(IoHwAb_ValueType, AUTOMATIC, IOHWAB_APPL_DATA) Value,
  IoHwAb_LengthType AnaInDirLength)
{
  uint8 LucAdcHwUnitId;
  uint8 LucAdcGroupLength;
  Std_ReturnType LddError;

  LucAdcGroupLength = IoHwAb_GaaAnaInDirInfos[ChIdx].ucAdcGroupLength;
  LucAdcHwUnitId = IoHwAb_GaaAnaInDirInfos[ChIdx].ucAdcHwUnitId;
  LddError = E_OK;

  /* Check if Value is NULL_PTR */
  if (Value == NULL_PTR)
  {
    #if (IOHWAB_DEV_ERROR_DETECT == STD_ON)
    (void)Det_ReportError((uint16)IOHWAB_MODULE_ID, (uint8)IOHWAB_INSTANCE_ID,
      (uint8)IOHWAB_ANAINDIR_READ_DIRECT_SID, (uint8)IOHWAB_E_DET_WRONG_PARAM);
    #endif /* (IOHWAB_DEV_ERROR_DETECT == STD_ON) */
    #if (IOHWAB_USE_DEM_EVENT == STD_ON)
    Dem_ReportErrorStatus(IOHWAB_E_WRONG_PARAM, DEM_EVENT_STATUS_FAILED);
    #endif /* (IOHWAB_USE_DEM_EVENT == STD_ON) */
    LddError = E_NOT_OK;
  }

  /* Check if AnaInDirLength is less than LucAdcGroupLength */
  if (LddError == E_OK)
  {
    if (AnaInDirLength > LucAdcGroupLength)
    {
      #if (IOHWAB_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError((uint16)IOHWAB_MODULE_ID, (uint8)IOHWAB_INSTANCE_ID,
        (uint8)IOHWAB_ANAINDIR_READ_DIRECT_SID, (uint8)IOHWAB_E_DET_WRONG_PARAM);
      #endif /* (IOHWAB_DEV_ERROR_DETECT == STD_ON) */
      #if (IOHWAB_USE_DEM_EVENT == STD_ON)
      Dem_ReportErrorStatus(IOHWAB_E_WRONG_PARAM, DEM_EVENT_STATUS_FAILED);
      #endif /* (IOHWAB_USE_DEM_EVENT == STD_ON) */
      LddError = RTE_E_IoHwAb_If_AnaInDir_E_WRONG_LENGTH;
    }
  }

  /* Check result setup buffer */
  if (LddError == E_OK)
  {
    if (Adc_SetupResultBuffer(IoHwAb_GaaAnaInDirInfos[ChIdx].ddAdcGroupType,
      IoHwAb_GaaAnaInDirAdcResults[LucAdcHwUnitId]) != E_OK)
    {
      #if (IOHWAB_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError((uint16)IOHWAB_MODULE_ID, (uint8)IOHWAB_INSTANCE_ID,
        (uint8)IOHWAB_ANAINDIR_READ_DIRECT_SID, (uint8)IOHWAB_E_DET_SETUP_FAIL);
      #endif /* (IOHWAB_DEV_ERROR_DETECT == STD_ON) */
      #if (IOHWAB_USE_DEM_EVENT == STD_ON)
      Dem_ReportErrorStatus(IOHWAB_E_SETUP_FAIL, DEM_EVENT_STATUS_FAILED);
      #endif /* (IOHWAB_USE_DEM_EVENT == STD_ON) */
      LddError = RTE_E_IoHwAb_If_AnaInDir_E_SETUP_BUFFER_FAIL;
    }
  }

  /* Check if Adc busy flag is set */
  if (LddError == E_OK)
  {
    SchM_Enter_IoHwAb_IoHwAbProtection();
    if (IoHwAb_GblAnaInAdcIsBusy[LucAdcHwUnitId] == TRUE)
    {
      #if (IOHWAB_DEV_ERROR_DETECT == STD_ON)
      (void)Det_ReportError((uint16)IOHWAB_MODULE_ID, (uint8)IOHWAB_INSTANCE_ID,
        (uint8)IOHWAB_ANAINDIR_READ_DIRECT_SID, (uint8)IOHWAB_E_DET_BUSY);
      #endif /* (IOHWAB_DEV_ERROR_DETECT == STD_ON) */
      #if (IOHWAB_USE_DEM_EVENT == STD_ON)
      Dem_ReportErrorStatus(IOHWAB_E_BUSY, DEM_EVENT_STATUS_FAILED);
      #endif /* (IOHWAB_USE_DEM_EVENT == STD_ON) */
      LddError = RTE_E_IoHwAb_If_AnaInDir_E_BUSY;
    }
    else
    {
      IoHwAb_GblAnaInAdcIsBusy[LucAdcHwUnitId] = TRUE;
    }
    SchM_Exit_IoHwAb_IoHwAbProtection();
  }

  return LddError;
}
#endif /* (IOHWAB_USE_ANA_IN_DIR == STD_ON) */

#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"

/*polyspace:end<MISRA-C:11.3:Not a defect:Justify with annotations> No Impact of this rule violation*/
/*polyspace-end RTE:UNR*/
/*polyspace:end<RTE: IDP : Not a defect : No Action Planned >                 */
/*polyspace:end<RTE: NIV : Not a defect : No Action Planned >                 */
/*polyspace:end<RTE: OBAI: Not a defect : No Action Planned > Array Checked   */
/* polyspace-end RTE:UNR [Not a defect:Unset] "Reachable code" */
/* polyspace-end MISRA-C3:18.1 [Justified:Unset] "Not a defect and validated by test cases" */
/* polyspace-end MISRA-C3:D4.14 [Justified:Unset] "The pointer is checked always." */
/* polyspace-end MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Unset] "It depends on the configuration" */
/* polyspace-end MISRA-C3:8.3 [Justified:Unset] "Prototypes are generated wrongly. It will be fixed soon" */
/* polyspace-end DEFECT:DEAD_CODE [Justified:Unset] "It depends on the configuration." */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
