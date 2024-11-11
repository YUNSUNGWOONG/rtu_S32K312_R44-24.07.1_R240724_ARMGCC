/*******************************************************************************
**                                                                            **
** (C) 2021 HYUNDAI AUTOEVER Corp.                                            **
** Confidential Proprietary Information. Distribution Limited.                **
** This source code is permitted to be used only in projects contracted       **
** with Hyundai Autoever, and any other use is prohibited.                    **
** If you use it for other purposes or change the source code,                **
** you may take legal responsibility.                                         **
** In this case, There is no warranty and technical support.                  **
**                                                                            **
**  SRC-MODULE: Dem_Obd.c                                                     **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostic Event Manager                              **
**                                                                            **
**  PURPOSE   : Provision of OnBoard Diagnostic functionality                 **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/
/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By            Description                          **
********************************************************************************
** 2.1.0.0   31-Mar-2024   EK Kim        Jira #CP44-4039 #CP44-4038 #CP44-3777**
** 2.0.0.0   31-Dec-2023   EK Kim        Jira #CP44-1515 #CP44-3198 #CP44-3298**
** 1.0.3     14-Oct-2021   LanhLT        R44-Redmine #21058                   **
** 1.0.1.0   07-May-2021   HaoLT6        R44-Redmine #18724                   **
** 1.0.0     26-Feb-2021   EK Kim        Initial version                      **
*******************************************************************************/
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

#include "Dem.h"                /* DEM module Header File */
#include "Dem_Dcm.h"            /* DEM Dcm Header File */
#include "Dem_Ram.h"            /* DEM Ram Header File */
#include "SchM_Dem.h"       /* Basic s/w module Scheduler symbols Header File */
#include "NvM.h"              /* NVRAM manager symbols Header File */
#include "Dem_EventRelatedData.h"
#include "Dem_Event.h"
#include "Dem_EventMemory.h"
#include "Dem_ObdRam.h"
#include "Dem_Dtc.h"
#if (DEM_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"                /* Det Header File */
#endif

#if (DEM_FIM_INTEGRATED == STD_ON)
#include "FiM.h"
#endif

/*******************************************************************************
**                           Global Data                                      **
*******************************************************************************/
/* polyspace-begin MISRA-C3:8.4 [Justified:Low] Justify with annotations */

/* Used to calculate time in sec */
VAR(uint16, DEM_VAR) Dem_GulDemMilOnTimeObdSecCount;

/* Used to calculate time in sec */
VAR(uint16, DEM_VAR) Dem_GulDemClearTimeObdSecCount;

/* polyspace-end MISRA-C3:8.4 [Justified:Low] Justify with annotations */
/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

#if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
static FUNC(uint8, DEM_CODE) Dem_ObdGetSizeOfPID(
  VAR(uint8, DEM_VAR) PID,
  VAR(uint8, DEM_VAR) DataElementIndexOfPID);


#if (DEM_NUMBER_OF_RATIO_INFO > DEM_ZERO)
static FUNC(void, DEM_CODE) Dem_GetFimPermission(
  Dem_RatioIdType RatioIndex,
  boolean* permission);

static FUNC(void, DEM_CODE )Dem_GetRatioIndex(
  Dem_EventParameterCPCType event,
  uint32 ArrayIndex,
  P2VAR(uint8, AUTOMATIC,DEM_VAR) RatioId);
  
/* Trace: DEM_OBD_09_03 */
static FUNC(void, DEM_CODE) Dem_DivideIumprRatioValue(
  VAR(Dem_RatioIdType, DEM_VAR) RatioID);
/* Trace: DEM_OBD_09_04 */
static FUNC(void, DEM_CODE) Dem_CalCulateMinimumRatioPerGroup(
  VAR(uint8, DEM_VAR) IumprGroupID);
/* Trace: DEM_OBD_09_05 */
static FUNC(void, DEM_CODE) Dem_ProcessDen100ms(void);  

#if (DEM_J1979_2_OBD_ON_UDS == STD_ON)
/* Trace: DEM_19792_06_03 */
static FUNC(void, DEM_CODE) Dem_ProcessMonitorActivityInhibitConditionCheck(void);
#endif /* J19792 */
#endif /* (DEM_NUMBER_OF_RATIO_INFO > DEM_ZERO))*/

#if ((DEM_PID01_BYTEB_LOWER_NIBBLE & 0x07U) != DEM_ZERO)
/* Trace: DEM_OBD_01_02 */
static FUNC(void, DEM_CODE) Dem_CalcPID41PerGroup(
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA) PIDValue,
  VAR(uint8, DEM_VAR) DisableGroupIndexinPID41,
  VAR(uint8, DEM_VAR) ReadinessGroup,
  VAR(uint8, DEM_VAR) CompletenessIndexinPID41
  );
#endif

#if ((DEM_PID01_BYTEC_SPARK != DEM_ZERO) || (DEM_PID01_BYTEC_COMPRESSION != DEM_ZERO))
/* Trace: DEM_OBD_01_03 */
static FUNC(void, DEM_CODE) Dem_CalcPID41PerGroupCheck(
  VAR(uint16, DEM_VAR) DisableGroupID,
  VAR(uint8, DEM_VAR) OBDReadyGroupID,
  VAR(uint8, DEM_VAR) SupportedEnableGroup,
  VAR(uint8, DEM_VAR) ReadinessCompletenessGroup,
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA) PID41ByteCAddr,
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA) PID41ByteDAddr
  );
#endif
#endif


#define DEM_START_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name        : Dem_InitOBD                                         **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Service to init value variable handling for OBD     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : Dem_EventIdType EventId                             **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_Returntype                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        Dem_GulEventIdDisabled                              **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Det_ReportError                                     **
**                        SchM_Exit_Dem_CAPTURE_OBD_DATA()                    **
*******************************************************************************/
/* @Trace: Dem_SUD_MACRO_023 */
#if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
FUNC(void, DEM_CODE) Dem_InitOBD(void)
{
  /* @Trace: Dem_SUD_API_11687 */
  #if (DEM_NUMBER_OF_RATIO_INFO > DEM_ZERO)
  /* @Trace: Dem_SUD_API_11695 */
  VAR(uint8, DEM_VAR) LucGroupRatioCount;
  VAR(uint8, DEM_VAR) LucRatioCount;
  #endif

  VAR(uint16, DEM_VAR) LusMemLoc;
  VAR(uint16, DEM_VAR) LusEventId;
  VAR(Dem_CombinedDtcPCType, DEM_VAR) LddCbDTC;

  /* Initialise the distance of start engine*/
  Dem_OBDOldDistanceInfo = DEM_ZERO;
  /* Initialise the time of start engine*/
  Dem_OBDOldEngStartInfo = DEM_ZERO;
  /* Initialise the obd event stored in permanent memory to zero */
  Dem_GusEventstoredinPermanent = DEM_ZERO;
  /* Initialise the obd dtc stored to zero */
  Dem_GusObdDtcFirstStored =  DEM_ZERO;
  /* Initialise the obd event store to false */
  Dem_ObdEventStored = DEM_FALSE;
  /* Initialise the  Milli Second Count to zero */
  Dem_GulDemTimeObdmsCount = DEM_ZERO;
  /* Initialise the Second Count to zero */
  Dem_GulDemMilOnTimeObdSecCount = DEM_ZERO;
  /* Initialise the Second Count to zero */
  Dem_GulDemClearTimeObdSecCount = DEM_ZERO;
  /* Initialise the Time since mil is on to zero */
  Dem_GulTimeSinceMilOn = DEM_ZERO;

  #if (DEM_NUMBER_OF_INDICATORS > DEM_ZERO)
  /* Trace: DEM_GEN_08 */
  /* Initialise the Mil on flag to false */
  Dem_GucMilonFlag = Dem_EventStatusNvRamData.MilonFlag;
  /* Initialise the Pre Mil on flag to false */
  Dem_GucPreMilonFlag = Dem_EventStatusNvRamData.PreMilonFlag;
  #endif

  /* Initialise the Mil on status to false */
  Dem_MilonStatus = DEM_ZERO;

  /* Initialise the Mil re-active flag to false */
  Dem_GucMilActivatedCnt = DEM_ZERO;
  Dem_GucPreMilActivatedCnt = DEM_ZERO;
  /* Initialise the time since clear function is called to false */
  Dem_GulDemClearTimeCount = DEM_ZERO;

  Dem_GblDtcCleared = Dem_EventStatusNvRamData.DtcClear;
  /* Initialise the warmup cycle count to zero */
  Dem_GusWarmUpCycleCount = DEM_ZERO;

  /* @Trace: Dem_SUD_API_11696 */
  #if (DEM_NUMBER_OF_DEM_CLIENT > DEM_ZERO)
  /* @Trace: Dem_SUD_API_11697 */
  for (uint8 LucClientIdx = DEM_ZERO;
             LucClientIdx < DEM_NUMBER_OF_DEM_CLIENT;
             LucClientIdx++)
  {
    /* @Trace: Dem_SUD_API_11698 */
    Dem_GstRecordDisableDTC[LucClientIdx].usObdDtc = DEM_ZERO;
  }
  #endif

  /* polyspace +1 MISRA2012:2.2 [Justified:Low] Justify with annotations */
  Dem_ObdMemoryId = DEM_NO_EVMEM_ENTRY;
  /* @Trace: Dem_SUD_API_11699 */
  #if ((DEM_OBD_CENTRALIZED_PID_21_HANDLING == STD_ON) && \
       (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT))
  /* Dem_DataOfPID21 = 0xFFFFU;*/
  /* @Trace: Dem_SUD_API_11700 */
  /* Trace: DEM_OBD_01_08 */
  Dem_DataOfPID21 = Dem_EventStatusNvRamData.DataOfPID21;
  #endif
  
  Dem_DataOfPID4D = Dem_EventStatusNvRamData.DataOfPID4D;
  Dem_DataOfPID4E = Dem_EventStatusNvRamData.DataOfPID4E;
  Dem_DataOfPID31 = Dem_EventStatusNvRamData.DataOfPID31;

  Dem_WWHOBDNumCycleCmd = DEM_ZERO;
  Dem_WWHOBDActMode     = DEM_WWHOBD_ACTIVATION_MODE_1;
  Dem_WWHOBDConMICont   = DEM_ZERO;
  Dem_WWHOBDPreActMode  = DEM_WWHOBD_ACTIVATION_MODE_1;
  Dem_WWHOBDB1Counter     = DEM_ZERO;
  Dem_WWHOBDNumCycleNoB1Class = DEM_ZERO;
  /* @Trace: Dem_SUD_API_11701 */
  #if (DEM_NUMBER_OF_RATIO_INFO > DEM_ZERO)
  Dem_GblRatioInit = DEM_FALSE;
  /* Initialise the ignition cycle count to zero */
  Dem_GusIgnitionCylCnt = Dem_EventStatusNvRamData.IgnitionCylCnt;
  /* Initialise the general denominator for infotype08 and infotype0b as zero
   */
  Dem_GusGeneralDenominator = Dem_EventStatusNvRamData.GeneralDenCnt;
  
  /* Trace: DEM_OBD_09_07 */  
  /* @Trace: Dem_SUD_API_11690 */
  /* Initialise the numerator and denominator of IUMPR group to zero */
  for (LucGroupRatioCount = DEM_ZERO;
       LucGroupRatioCount < DEM_IUMPR_MAX;
       LucGroupRatioCount++)
  {
    /* @Trace: Dem_SUD_API_11689 */
    Dem_GaaIumprUpdateFlagPerGroup[LucGroupRatioCount] = Dem_EventStatusNvRamData.IumprUpdateFlagPerGroup[LucGroupRatioCount];
    /* If assigned ratio is exist */
    if (Dem_GaaIumprUpdateFlagPerGroup[LucGroupRatioCount] == DEM_TRUE)
    {    
      Dem_GaaIumprMinimumRatioIDPerGroup[LucGroupRatioCount] = 
          Dem_EventStatusNvRamData.IumprMinimumRatioIDPerGroup[LucGroupRatioCount];  
    }
    /* If ratio is not assigned yet this group, init to Last index which always 0 */
    else
    {      
      Dem_GaaIumprUpdateFlagPerGroup[LucGroupRatioCount] = DEM_FALSE;
      Dem_GaaIumprMinimumRatioIDPerGroup[LucGroupRatioCount] = DEM_NUMBER_OF_RATIO_INFO;
    }

  }
  
  for (LucRatioCount = DEM_ZERO;
       LucRatioCount < DEM_NUMBER_OF_RATIO_INFO;
       LucRatioCount++)
  {
    Dem_GaaIumprDenominator[LucRatioCount] =
        Dem_EventStatusNvRamData.IumprDenominator[LucRatioCount];
    Dem_GaaIumprDenominatorIsCounted[LucRatioCount] = DEM_FALSE;
    Dem_GaaIumprNumerator[LucRatioCount] =
        Dem_EventStatusNvRamData.IumprNumerator[LucRatioCount];
    Dem_GaaIumprNumeratorIsCounted[LucRatioCount] = DEM_FALSE;

    #if (DEM_J1979_2_OBD_ON_UDS == STD_ON)
    Dem_GaaMonitorActivityNumerator[LucRatioCount] = Dem_EventStatusNvRamData.MonitorActivityNumerator[LucRatioCount];
    Dem_GaaMonitorActivityNumeratorNeedCountedCycleEnd[LucRatioCount] = Dem_EventStatusNvRamData.MonitorActivityNumeratorNeedCountedCycleEnd[LucRatioCount];
    Dem_GaaMonitorActivityRatio[LucRatioCount] = Dem_EventStatusNvRamData.MonitorActivityRatio[LucRatioCount];
    Dem_GaaMonitorActivityDenominator[LucRatioCount] = Dem_EventStatusNvRamData.MonitorActivityDenominator[LucRatioCount];  
    Dem_GaaMonitorActivityDenominatorNeedCountedCycleEnd[LucRatioCount] = Dem_EventStatusNvRamData.MonitorActivityDenominatorNeedCountedCycleEnd[LucRatioCount];
    #endif /* (DEM_J1979_2_OBD_ON_UDS == STD_ON) */
  }
  /* Last Array of Denominator, Numerator is always use to ZERO */
  Dem_GaaIumprDenominator[DEM_NUMBER_OF_RATIO_INFO] = DEM_ZERO;
  Dem_GaaIumprNumerator[DEM_NUMBER_OF_RATIO_INFO] = DEM_ZERO;

  
  /* @Trace: Dem_SUD_API_11691 */
  /*Initialise the Dem_GusRatioDenCondState */
  for (uint8 LucIdx = DEM_ZERO;
             LucIdx < DEM_IUMPR_MAX_CONDITION_NUMBER ;
             LucIdx++)
  {
    /* @Trace: Dem_SUD_API_11692 */
    Dem_GusRatioDenCondState[LucIdx] = DEM_IUMPR_DEN_STATUS_NOT_REACHED;
  }
  #endif

  /* All Primary Memory needed to be Checked that OBD DTC Exist. */
  /* @Trace: Dem_SUD_API_11693 */
  for (LusMemLoc = Dem_GaaDemPrimaryMemory[0].usStartIdx; 
       LusMemLoc < Dem_GaaDemPrimaryMemory[DEM_MAX_NUMBER_PRIMARY_MEMORY-1].usStopIdx; 
       LusMemLoc++)
  {
    LusEventId = Dem_PrimaryEventMemory[LusMemLoc].EventIdRef;
    if (DEM_NO_EVENT != LusEventId)
    {
      LddCbDTC = Dem_GetCbDTCByEventId(LusEventId);
      if (LddCbDTC->usObdDtc != DEM_FALSE ) 
      {
        /* @Trace: Dem_SUD_API_11694 */
        Dem_ObdMemoryId = Dem_EventStatusNvRamData.ObdMemoryId;
        break;
      }    
    }  
  }  

  #if (DEM_NUMBER_OF_INDICATORS > DEM_ZERO)
  Dem_SetMalfuntionOnOff();
  #endif
}
#endif

/*******************************************************************************
** Function Name        : Dem_MainFunctionOBD                                 **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Main function handling for OBD                      **
**                                                                            **
** Timing:              : FIXED_CYCLIC                                        **
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
** Remarks              : Global Variable(s)  :                               **
**                        Dem_GucInit                                         **
**                        Dem_GblMilStarted                                   **
**                        Dem_GulTimeSinceMilOn                               **
**                        Dem_GulDemTimeObdmsCount                            **
**                        Dem_GucMilonFlag                                    **
**                        Dem_GblClearTimeStartObd                            **
**                        Dem_GulDemClearTimeCount                            **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Det_ReportError                                     **
*******************************************************************************/
/* @Trace: SRS_Diag_04141
 */
/* Check if DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT */
#if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
FUNC(void, DEM_CODE) Dem_MainFunctionOBD(void)
{
  VAR(uint32, DEM_VAR)  LulnewDistanceInfo = DEM_ZERO;
  VAR(uint32, DEM_VAR)  LulTravelDistance = DEM_ZERO;
  VAR(uint32, DEM_VAR)  LulNewEngStartInfo = DEM_ZERO;
  VAR(uint32, DEM_VAR)  LulGapEngStartInfo = DEM_ZERO;
  VAR(boolean, DEM_VAR) LblIsIncreaseB1Counter = DEM_FALSE;
  VAR(boolean, DEM_VAR) LblConditionMode4Active = DEM_FALSE;
  VAR(boolean, DEM_VAR) LblConditionMode3Active = DEM_FALSE;
  VAR(boolean, DEM_VAR) LblConditionMode2Active = DEM_FALSE;
  VAR(uint8, DEM_VAR)   LucNewActiveMode = Dem_WWHOBDActMode;
  VAR(boolean, DEM_VAR) LblIsCommandOn = DEM_FALSE;
  VAR(Std_ReturnType, DEM_VAR) LddTimeEngStartStatus = E_NOT_OK;
  VAR(Std_ReturnType, DEM_VAR) LddTravelDisStatus = E_NOT_OK;
  VAR(boolean, DEM_VAR) LblCheckMilOnEdge = DEM_FALSE;

  LddTimeEngStartStatus =
      Dem_OBDReadDataOfTimeEngineStart((uint8*)&LulNewEngStartInfo);
  LddTravelDisStatus =
      Dem_OBDReadDataOfTravelDistance((uint8*)&LulnewDistanceInfo);

  #if ((DEM_NUMBER_OF_RATIO_INFO > DEM_ZERO) && \
    (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT))
  /* It's Enough to 100ms period */
  static VAR(uint8, DEM_VAR) LucCount100ms = DEM_ZERO;
  if (LucCount100ms >= DEM_TEN)
  {
    Dem_ProcessDen100ms();

    #if (DEM_J1979_2_OBD_ON_UDS == STD_ON)
    /* Trace: DEM_19792_06_03 */
    Dem_ProcessMonitorActivityInhibitConditionCheck();

    #endif /* J19792 */
    LucCount100ms = DEM_ZERO;
  }
  else
  {
    LucCount100ms++;
  }
  #endif

  if ( (Dem_GucPreMilonFlag == DEM_ZERO) && (Dem_GucMilonFlag == DEM_BIT7_MASK1) )
  {
    LblCheckMilOnEdge = DEM_TRUE;
    Dem_GusWarmUpCycleCount = DEM_ZERO;
  }
  Dem_GucPreMilonFlag = Dem_GucMilonFlag;
  
  if (Dem_GucMilonFlag != Dem_EventStatusNvRamData.MilonFlag)
  {
    SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();
    Dem_EventStatusNvRamData.MilonFlag = Dem_GucMilonFlag;
    Dem_EventStatusNvRamData.PreMilonFlag = Dem_GucPreMilonFlag;
    SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();
    /* @Trace: Dem_SUD_API_12858 */
    Dem_EvMem_SetNonVolatieDataStatus(
        DEM_NVDATA_ALL_EVENT_STATUS_ID, DEM_EVMEM_STATUS_DIRTY_NVM);
    Dem_EvMem_TriggerWriteAllBlocks(); 
  }


  /* @Trace: Dem_SUD_API_11714 */
  if ((Dem_GusWarmUpCycleCount >= DEM_FORTY ) ||
     (LblCheckMilOnEdge == DEM_TRUE))
  {
    /* @Trace: Dem_SUD_API_11703 */
    SchM_Enter_Dem_CAPTURE_OBD_DATA();
    #if ((DEM_OBD_CENTRALIZED_PID_21_HANDLING == STD_ON) && \
         (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT))
    Dem_DataOfPID21 = DEM_ZERO;
    #endif
    Dem_DataOfPID4D = DEM_ZERO;
    Dem_GucPreMilActivatedCnt = Dem_GucMilActivatedCnt;
    Dem_EventStatusNvRamData.DataOfPID21 = Dem_DataOfPID21;
    Dem_EventStatusNvRamData.DataOfPID4D = Dem_DataOfPID4D;
    SchM_Exit_Dem_CAPTURE_OBD_DATA();
  }

  /* polyspace-begin MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] Same as Dead Code. */
  /* polyspace-begin DEFECT:DEAD_CODE [Justified:Low] */
  /* DEM_GEN_07 */
  if (LddTravelDisStatus == E_OK) 
  {
    SchM_Enter_Dem_CAPTURE_OBD_DATA();
    /* @Trace: Dem_SUD_API_11747 */
    if (Dem_OBDOldDistanceInfo < LulnewDistanceInfo)
    {
      LulTravelDistance = LulnewDistanceInfo - Dem_OBDOldDistanceInfo;
      Dem_OBDOldDistanceInfo = LulnewDistanceInfo;
      /* Check first time after miloff is Mil flag is set*/

      /*********************************************************
       * PID21: Distance travelled while MIL is activated
       *********************************************************/
      /* @Trace: Dem_SUD_API_11754 */
      if (Dem_GucMilonFlag == DEM_BIT7_MASK1)
      {
        /* @Trace: Dem_SUD_API_11755 */
        Dem_DataOfPID21 = Dem_DataOfPID21 + (uint16)LulTravelDistance;
        /* Trace: DEM_OBD_01_08 */
        Dem_EventStatusNvRamData.DataOfPID21 = Dem_DataOfPID21;
      }

      /*********************************************************
       * PID31: Distance since DTCs cleared
       *********************************************************/
      /* @Trace: Dem_SUD_API_11756 */
      /* Check first time after miloff is Mil flag is set*/
      if (DEM_TRUE == Dem_GblDtcCleared)
      {
        if ((Dem_DataOfPID31 + LulTravelDistance) >
               DEM_MAX_DISTANCE_SINCE_DTCS_CLEARED)
        {
          /* @Trace: Dem_SUD_API_10731 */
          Dem_DataOfPID31 = DEM_MAX_DISTANCE_SINCE_DTCS_CLEARED;
        }
        else
        {
          /* @Trace: Dem_SUD_API_11757 */
          Dem_DataOfPID31 = Dem_DataOfPID31 + (uint16)LulTravelDistance;
        }
        /* Trace: DEM_OBD_01_08 */
        Dem_EventStatusNvRamData.DataOfPID31 = Dem_DataOfPID31;

      }
    }
    SchM_Exit_Dem_CAPTURE_OBD_DATA();
  }
  else
  {
    /* @Trace: Dem_SUD_API_11725 */
    /* Nothing to do */
  }
  /* polyspace-end MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] Same as Dead Code. */
  /* polyspace-end DEFECT:DEAD_CODE [Justified:Low] */


  /* The value of PID $4D is reset if the MIL is illuminated again,
   * no DTC requests the MIL indicator for 40 warm-up cycles or
   * if the memory is erased by Mode $04.*/
  /* polyspace-begin MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] Same as Dead Code. */
  /* polyspace-begin DEFECT:DEAD_CODE [Justified:Low] */
  /* @Trace: Dem_SUD_API_11704 */
  if (LddTimeEngStartStatus == E_OK)
  {
    SchM_Enter_Dem_CAPTURE_OBD_DATA();
    /* @Trace: Dem_SUD_API_11706 */
    if (Dem_OBDOldEngStartInfo < LulNewEngStartInfo)
    {
      LulGapEngStartInfo = LulNewEngStartInfo - Dem_OBDOldEngStartInfo;
      Dem_OBDOldEngStartInfo = LulNewEngStartInfo;

      /*********************************************************
       * PID4D: Engine run time while MIL is activated
       *********************************************************/
      /* Check first time after miloff is Mil flag is set*/
      /* @Trace: Dem_SUD_API_11708 */
      if (Dem_GucMilonFlag == DEM_BIT7_MASK1)
      {
        /* @Trace: Dem_SUD_API_11707 */
        Dem_DataOfPID4D = Dem_DataOfPID4D + (uint16)LulGapEngStartInfo;
        /* Trace: DEM_OBD_01_08 */
        Dem_EventStatusNvRamData.DataOfPID4D = Dem_DataOfPID4D;
      }

      /*********************************************************
       * PID4E: Engine run time since DTCs cleared
       *********************************************************/
      /* Check first time after miloff is Mil flag is set*/
      /* @Trace: Dem_SUD_API_11710 */
      if (DEM_TRUE == Dem_GblDtcCleared)
      {
        /* @Trace: Dem_SUD_API_11709 */
        Dem_DataOfPID4E = Dem_DataOfPID4E + (uint16)LulGapEngStartInfo;
        /* Trace: DEM_OBD_01_08 */
        Dem_EventStatusNvRamData.DataOfPID4E = Dem_DataOfPID4E;
      }
    }
    SchM_Exit_Dem_CAPTURE_OBD_DATA();
  }
  else
  {
    /* @Trace: Dem_SUD_API_11705 */
    /* Nothing to do */
  }
  /* polyspace-end MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] Same as Dead Code. */
  /* polyspace-end DEFECT:DEAD_CODE [Justified:Low] */

  /* Check whether command ON based on MIL status */
  if (Dem_GucMilonFlag == DEM_BIT7_MASK1)
  {
    /* @Trace: Dem_SUD_API_11711 */
    LblIsCommandOn = DEM_TRUE;
  }
  else
  {
    /* @Trace: Dem_SUD_API_11712 */
    LblIsCommandOn = DEM_FALSE;
  }

  #if (DEM_OBD_SUPPORT != DEM_OBD_MASTER_ECU)
  /*Handling for WWH OBD*/
  if (DEM_WWHOBD_ACTIVATION_MODE_4 == Dem_WWHOBDActMode)
  {
    /* @Trace: Dem_SUD_API_11717 */
    /* @Trace: SWS_Dem_01141
     * If Activation Mode 4 becomes active the counter shall be reset to 0.*/
    Dem_WWHOBDConMICont = DEM_ZERO;
  }
  else
  {
    if (DEM_TRUE == LblIsCommandOn)
    {
      /* @Trace: SWS_Dem_01142
       * The counter shall increment for each engine operating hour during
       * which the event is detected and the Continuous-MI is commanded to be on.
       * */
      /* @Trace: SWS_Dem_01147
       * The counter shall be reported as a two byte value. If any count
       * operation occurs which would cause a counter to roll over past
       * 0x00FF then the count value shall instead be maintained at 0x00FF.*/
      Dem_WWHOBDConMICont = Dem_WWHOBDConMICont + (uint16)LulGapEngStartInfo;
      /* @Trace: Dem_SUD_API_11718 */
      if (Dem_WWHOBDConMICont > DEM_MAX_WWHOBD_CON_MI_CONT)
      {
        /* @Trace: Dem_SUD_API_11719 */
        Dem_WWHOBDConMICont = DEM_MAX_WWHOBD_CON_MI_CONT;
      }
    }
    else
    {
      /* @Trace: SWS_Dem_01143
       * The counter shall halt its value when the Continuous-MI is no
       * longer commanded to be on.*/
      /* @Trace: SWS_Dem_01146
       * The counter shall reset to zero if the Continuous-MI is not commanded
       * on after more than 40 warm-up cycles or after more than 200 engine
       * operating hours or upon a ClearDTC request.*/
      /* @Trace: Dem_SUD_API_11721 */
      if ((Dem_GusWarmUpCycleCount >= DEM_FORTY) ||
          (Dem_WWHOBDConMICont > DEM_WWHOBD_ENGINE_HOURS_LIMIT))
      {
        /* @Trace: Dem_SUD_API_11720 */
        Dem_WWHOBDConMICont = DEM_ZERO;
      }
    }
  }

  /* @Trace: SWS_Dem_01144
   * The counter shall continue its incrementation if the
   * Continuous-MI is again commanded on within three operation sequences.*/

  /* @Trace: SWS_Dem_01145
   * The counter shall reset to zero and start incrementing its value if
   * the Continuous-MI is again commanded on after more than three
   * operation sequences.*/
  /* @Trace: Dem_SUD_API_11723 */
  if (Dem_WWHOBDNumCycleCmd > DEM_THREE)
  {
    /* @Trace: Dem_SUD_API_11722 */
    Dem_WWHOBDConMICont = DEM_ZERO;
  }

  /* @Trace: SWS_Dem_01148
   * The counter shall be stored non-volatile.*/
  Dem_EventStatusNvRamData.WWHOBDConMICont = Dem_WWHOBDConMICont;
  #else
  /* @Trace: SWS_Dem_01149
   * The counter shall increment for each engine operating hour during
   * which the event is detected and the Continuous-MI is commanded to be on,*/

  /* @Trace: SWS_Dem_01151
   * The counter shall never be reset.*/

  /* @Trace: SWS_Dem_01150
   * The counter shall halt its value when the Continuous-MI
   * is no longer commanded to be on */
  /* @Trace: Dem_SUD_API_11713 */
  if (DEM_TRUE == LblIsCommandOn)
  {
    /* @Trace: SWS_Dem_01152
     * The counter shall be reported as a two byte value. If any
     * count operation occurs which would cause a counter to roll over past
     * 0x00FF then the count value shall instead be maintained at 0x00FF.
     * */
    Dem_WWHOBDConMICont = Dem_WWHOBDConMICont + (uint16)LulGapEngStartInfo;
    /* @Trace: Dem_SUD_API_11715 */
    if (Dem_WWHOBDConMICont > DEM_MAX_WWHOBD_CON_MI_CONT)
    {
      /* @Trace: Dem_SUD_API_11716 */
      Dem_WWHOBDConMICont = DEM_MAX_WWHOBD_CON_MI_CONT;
    }
  }
  /* @Trace: SWS_Dem_01153
   * The counter shall be stored non-volatile.*/
  Dem_EventStatusNvRamData.WWHOBDConMICont = Dem_WWHOBDConMICont;
  #endif


  /* Handling B1 counter*/
  for (Dem_EventIdType LddEventId = DEM_ONE;
                       LddEventId <= DEM_NUMBER_OF_EVENTS;
                       LddEventId++)
  {
    Dem_EventParameterCPCType LddEvent = &Dem_Event[LddEventId - DEM_ONE];
    uint32 LulDTC;
    /* @Trace: Dem_SUD_API_11724 */
    if (E_OK == Dem_GetEventDTC(LddEvent, &LulDTC, DEM_DTC_FORMAT_OBD))
    {
      Dem_CombinedDtcPCType LddCbDTC =
          Dem_GetDtcByDtcId(LulDTC, DEM_DTC_FORMAT_OBD);
      /* @Trace: Dem_SUD_API_11726 */
      if (NULL_PTR != LddCbDTC)
      {
        /* @Trace: SWS_Dem_01161
         * If at least one Class A event is Confirmed and TestFailed the
         * Activation Mode 4 shall be active.*/
        /* @Trace: Dem_SUD_API_11728 */
        /* polyspace-begin DEFECT:DEAD_CODE [Justified:Low] "Dead Code by Configuration" */
        /* polyspace-begin MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] Same as Dead Code. */
        if ((((Dem_AllEventStatusByte[LddEventId] &
              (Dem_UdsStatusByteType)DEM_UDS_STATUS_CDTC) ==
                  DEM_UDS_STATUS_CDTC) &&
             ((Dem_AllEventStatusByte[LddEventId] &
              (Dem_UdsStatusByteType)DEM_UDS_STATUS_TF) ==
                  DEM_UDS_STATUS_TF)) &&
             (LddCbDTC->eDemWWHOBDDTCClass == DEM_DTC_WWHOBD_CLASS_A))
        {
          /* @Trace: Dem_SUD_API_11727 */
          LucNewActiveMode = DEM_WWHOBD_ACTIVATION_MODE_4;
          LblConditionMode4Active = DEM_TRUE;
        }
        /* polyspace-end MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] Same as Dead Code. */
        /* polyspace-end DEFECT:DEAD_CODE [Justified:Low] "Dead Code by Configuration" */

        /* @Trace: SWS_Dem_01163
         * If Activation Mode 4 has been degraded to Activation Mode 3 and
         * an Activation Mode 4 relevant event is confirmed the Activation
         * Mode 4 shall be reactivated if the configured value of
         * EventFailureCycleCounterThreshold is reached.*/
        Dem_EventMemoryEntryPtrType LddMemEntry =
            Dem_EvMem_FindEntry(LddEventId, LddEvent->aaEventDestination);
        /* @Trace: Dem_SUD_API_11729 */
        if (NULL_PTR != LddMemEntry)
        {
          /* @Trace: Dem_SUD_API_10733 */
          if ((DEM_WWHOBD_ACTIVATION_MODE_4 == Dem_WWHOBDPreActMode)
              && (DEM_WWHOBD_ACTIVATION_MODE_3 == Dem_WWHOBDActMode)
              && ((Dem_AllEventStatusByte[LddEventId] &
                  (Dem_UdsStatusByteType)DEM_UDS_STATUS_CDTC) ==
                      DEM_UDS_STATUS_CDTC)
              /* If confirm bit is set, it mean that Failure Cycle Counter is
               * reached and reset immediately */
          )
          {
            /* @Trace: Dem_SUD_API_11730 */
            LucNewActiveMode = DEM_WWHOBD_ACTIVATION_MODE_4;
            LblConditionMode4Active = DEM_TRUE;
          }
        }
        /* @Trace: SWS_Dem_01154
         * The B1 counter shall increment for each 1 hour engine operating
         * hour during which at least one Class B1 event is detected as Confirmed
         * and TestFailed.*/
        /* @Trace: Dem_SUD_API_11732 */
        /* polyspace-begin DEFECT:DEAD_CODE [Justified:Low] "Dead Code by Configuration" */
        /* polyspace-begin MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] Same as Dead Code. */
        if ((((Dem_AllEventStatusByte[LddEventId] &
              (Dem_UdsStatusByteType)DEM_UDS_STATUS_CDTC) ==
                  DEM_UDS_STATUS_CDTC) &&
            ((Dem_AllEventStatusByte[LddEventId] &
              (Dem_UdsStatusByteType)DEM_UDS_STATUS_TF) ==
                  DEM_UDS_STATUS_TF)) &&
            (LddCbDTC->eDemWWHOBDDTCClass == DEM_DTC_WWHOBD_CLASS_B1))
        {
          /* @Trace: Dem_SUD_API_11731 */
          LblIsIncreaseB1Counter = DEM_TRUE;
        }
        /* polyspace-end DEFECT:DEAD_CODE [Justified:Low] "Dead Code by Configuration" */
        /* polyspace-end MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] Same as Dead Code. */

        /* @Trace: SWS_Dem_01165 */
        /* @Trace: Dem_SUD_API_11734 */
        /* polyspace-begin DEFECT:DEAD_CODE [Justified:Low] "Dead Code by Configuration" */
        /* polyspace-begin MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] Same as Dead Code. */
        if ((((Dem_AllEventStatusByte[LddEventId] &
              (Dem_UdsStatusByteType)DEM_UDS_STATUS_CDTC) ==
                  DEM_UDS_STATUS_CDTC) ||
            ((Dem_AllEventStatusByte[LddEventId] &
              (Dem_UdsStatusByteType)DEM_UDS_STATUS_TF) ==
                  DEM_UDS_STATUS_TF)) &&
            (LddCbDTC->eDemWWHOBDDTCClass == DEM_DTC_WWHOBD_CLASS_C))
        {
          /* @Trace: Dem_SUD_API_11733 */
          LblConditionMode2Active = DEM_TRUE;
        }
      }
      /* polyspace-end MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] Same as Dead Code. */
      /* polyspace-end DEFECT:DEAD_CODE [Justified:Low] "Dead Code by Configuration" */
    }
  }
  /* @Trace: SWS_Dem_01155
   * The B1 counter shall latch its value when no Class B1 event
   * is no longer detected as Confirmed and TestFailed
   * or after a ClearDTC request.*/
  /* @Trace: Dem_SUD_API_10734 */
  /* polyspace-begin DEFECT:DEAD_CODE [Justified:Low] "Dead Code by Configuration" */
  /* polyspace-begin MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] Same as Dead Code. */
  if (( DEM_TRUE == LblIsIncreaseB1Counter ) &&
      (DEM_TRUE != Dem_GblDtcCleared))
  {
    /* @Trace: SWS_Dem_01158
     * The B1 counter shall be reported as a two byte value. If any
     * count operation occurs which would cause a counter to roll over
     * past 0x00FF then the count value shall instead be latched at 0x00FF.*/
    Dem_WWHOBDB1Counter = Dem_WWHOBDB1Counter + (uint16)LulGapEngStartInfo;
    /* @Trace: Dem_SUD_API_11737 */
    if (Dem_WWHOBDB1Counter > DEM_MAX_WWHOBD1_COUNTER)
    {
      /* @Trace: Dem_SUD_API_11735 */
      Dem_WWHOBDB1Counter = DEM_MAX_WWHOBD1_COUNTER;
    }
  }
  /* polyspace-end DEFECT:DEAD_CODE [Justified:Low] "Dead Code by Configuration" */
  /* polyspace-end MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] Same as Dead Code. */

  /* @Trace: SWS_Dem_01157
   * If B1 Counter exceeds 200 engine operating hours and no Class
   * B1 event have been detected the counter shall be set to 190.*/
  /* @Trace: Dem_SUD_API_11739 */
  if (( DEM_TRUE != LblIsIncreaseB1Counter ) &&
      (Dem_WWHOBDB1Counter > DEM_TWO_HUNDRED))
  {
    /* @Trace: Dem_SUD_API_11738 */
    Dem_WWHOBDB1Counter = DEM_ONE_HUNDRED_NINETY;
  }

  /* @Trace: SWS_Dem_01156
   * The B1 counter shall reset to zero after three consecutive operating
   * sequences where no Class B1 event have been detected.*/
  /* @Trace: Dem_SUD_API_11741 */
  if (Dem_WWHOBDNumCycleNoB1Class >= DEM_THREE)
  {
    /* @Trace: Dem_SUD_API_11740 */
    Dem_WWHOBDB1Counter = DEM_ZERO;
  }

  /* @Trace: SWS_Dem_01159
   * The B1 counter shall be stored non-volatile.*/
  Dem_EventStatusNvRamData.WWHOBDB1Counter = Dem_WWHOBDB1Counter;
  /* @Trace: Dem_SUD_API_11743 */
  if (Dem_WWHOBDB1Counter > Dem_WWHOBDHighestB1Cont)
  {
    /* @Trace: Dem_SUD_API_11742 */
    Dem_WWHOBDHighestB1Cont = Dem_WWHOBDB1Counter;
  }

  /* @Trace: Dem_SUD_API_11745 */
  /* polyspace-begin DEFECT:DEAD_CODE [Justified:Low] "Dead Code by Configuration" */
  /* polyspace-begin MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] Same as Dead Code. */
  if (Dem_WWHOBDB1Counter > DEM_TWO_HUNDRED)
  {
    /* @Trace: Dem_SUD_API_11744 */
    /* @Trace: SWS_Dem_01160
     * If the B1 counter exceeds 200 engine operating hours the Activation
     * Mode 4 shall be active.*/
    LucNewActiveMode = DEM_WWHOBD_ACTIVATION_MODE_4;
    LblConditionMode4Active = DEM_TRUE;
  }
  /* polyspace-end DEFECT:DEAD_CODE [Justified:Low] "Dead Code by Configuration" */
  /* polyspace-end MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] Same as Dead Code. */

  /* @Trace: SWS_Dem_01162
   * If Activation Mode 4 is active and no Activation Mode 4 relevant
   * condition is present anymore, then the Activation Mode 3 shall be
   * activated.*/
  /* @Trace: Dem_SUD_API_10732 */
  if ((DEM_WWHOBD_ACTIVATION_MODE_4 == Dem_WWHOBDActMode) &&
      (DEM_TRUE != LblConditionMode4Active))
  {
    /* @Trace: Dem_SUD_API_11746 */
    LucNewActiveMode = DEM_WWHOBD_ACTIVATION_MODE_3;
    LblConditionMode3Active = DEM_TRUE;
  }
  /* @Trace: SWS_Dem_01164
   * If Activation Mode 3 is active and no Activation Mode
   * 3 and Activation Mode 4 relevant condition is present,
   * then the Activation Mode 1 shall be set.*/
  /* @Trace: Dem_SUD_API_11749 */
  if ((DEM_WWHOBD_ACTIVATION_MODE_3 == Dem_WWHOBDActMode) &&
      (DEM_TRUE != LblConditionMode4Active) &&
      (DEM_TRUE != LblConditionMode3Active))
  {
    /* @Trace: Dem_SUD_API_11748 */
    LucNewActiveMode = DEM_WWHOBD_ACTIVATION_MODE_1;
  }

  /* @Trace: SWS_Dem_01165
   * If an Class C event is Confirmed and TestFailed and no Activation
   * Mode 3 or Activation Mode 4 is active, the Activation Mode 2 shall
   * be set to active.*/
  /* @Trace: Dem_SUD_API_11751 */
  /* polyspace-begin DEFECT:DEAD_CODE [Justified:Low] "Dead Code by Configuration" */
  /* polyspace-begin MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] "Same as Dead Code" */
  if ((DEM_TRUE == LblConditionMode2Active) &&
      (DEM_TRUE != LblConditionMode4Active) &&
      (DEM_TRUE != LblConditionMode3Active))
  {
    /* @Trace: Dem_SUD_API_11750 */
    LucNewActiveMode = DEM_WWHOBD_ACTIVATION_MODE_2;
  }
  /* polyspace-begin MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] "Same as Dead Code" */
  /* polyspace-end DEFECT:DEAD_CODE [Justified:Low] "Dead Code by Configuration" */
  
  /* @Trace: Dem_SUD_API_11753 */
  if (Dem_WWHOBDActMode != LucNewActiveMode)
  {
    /* @Trace: Dem_SUD_API_11752 */
    /*Saved previous active mode*/
    Dem_WWHOBDPreActMode = Dem_WWHOBDActMode;
    Dem_WWHOBDActMode = LucNewActiveMode;
  }
}
#endif



/*******************************************************************************
** Function Name        : Dem_SetEventDisabled                                **
**                                                                            **
** Service ID           : 0x51                                                **
**                                                                            **
** Description          : Service for reporting the event as disabled to the  **
**                        Dem for the PID $41 computation.                   **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant for different EventIds. Non reentrant for **
**                        the same EventId.                                   **
**                                                                            **
** Input Parameters     : EventId                                             **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                        -  E_OK set of event to disabled was successfull    **
**                        -  E_NOT_OK set of event disabled failed            **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/

/* Check if DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT */
#if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
FUNC(Std_ReturnType, DEM_CODE) Dem_SetEventDisabled(
  VAR(Dem_EventIdType, DEM_VAR) EventId
)
{
  /* @Trace: SWS_Dem_00348
   * The Dem module shall provide the disabling of events (refer to
   * Dem_SetEventDisabled). OBD Events Suppression (refer to chapter
   * 7.4.8) shall be ignored for this computation.*/

  /* @Trace: SWS_Dem_00294
   * In order to allow a monitor to report that the event cannot be
   * computed in the driving cycle (aborted e.g. due to physical
   * reasons), the Dem shall provide the API Dem_SetEventDisabled.*/
  /* EventId Index */
  /* @Trace: Dem_SUD_API_12849 */
  VAR(Dem_EventIdType, DEM_VAR) LddEventParameterIndex;
  VAR(Std_ReturnType, DEM_VAR) LddReturnValue;
  VAR(uint32, DEM_VAR) LulReadinessGroup;


  /* Get the Event Parameter Index */
  LddEventParameterIndex = EventId - DEM_ONE;
  /* Module Initialization check */
  if (DEM_INIT != Dem_GucInit)
  {
    /* @Trace: Dem_SUD_API_12839 */
    /* Report to DET */
    DEM_REPORT_ERROR(DEM_SETEVENTDISABLED_SID, DEM_E_UNINIT);

    /* Return appropriate value */
    LddReturnValue = E_NOT_OK;
  }
  else if ((EventId > DEM_NUMBER_OF_EVENTS) || (DEM_ZERO == EventId))
  {
    /* @Trace: Dem_SUD_API_12850 */
    /* Report to DET */
    DEM_REPORT_ERROR(DEM_SETEVENTDISABLED_SID, DEM_E_PARAM_CONFIG);

    /* Return appropriate value */
    LddReturnValue = E_NOT_OK;
  }
  else
  {
    LulReadinessGroup =
      Dem_Event[LddEventParameterIndex].ulEventOBDReadinessGroup;

    SchM_Enter_Dem_CAPTURE_OBD_DATA();

    switch(LulReadinessGroup)
    {
      case DEM_OBD_RDY_MISF:
      {
        /* @Trace: Dem_SUD_API_12851 */
        /* Disable the event with masking 0x01 */
        Dem_GulEventIdDisabled =
            Dem_GulEventIdDisabled | DEM_OBD_RDY_DISABLE_MISF;
      }
      break;

      case DEM_OBD_RDY_FLSYS:
      {
        /* @Trace: Dem_SUD_API_12852 */
        /* Disable the event with masking 0x02 */
        Dem_GulEventIdDisabled = Dem_GulEventIdDisabled
            | DEM_OBD_RDY_DISABLE_FLSYS;
      }
      break;

      case DEM_OBD_RDY_CMPRCMPT:
      {
        /* @Trace: Dem_SUD_API_12853 */
        /* Disable the event with masking 0x04 */
        Dem_GulEventIdDisabled = Dem_GulEventIdDisabled |
            DEM_OBD_RDY_DISABLE_CMPRCMPT;
      }
      break;

      case DEM_OBD_RDY_CAT:
      {
        /* @Trace: Dem_SUD_API_12854 */
        /* Disable the event with masking 0x08 */
        Dem_GulEventIdDisabled =
            Dem_GulEventIdDisabled | DEM_OBD_RDY_DISABLE_CAT;
      }
      break;

      case DEM_OBD_RDY_HTCAT:
      {
        /* @Trace: Dem_SUD_API_12855 */
        /* Disable the event with masking 0x10 */
        Dem_GulEventIdDisabled =
            Dem_GulEventIdDisabled | DEM_OBD_RDY_DISABLE_HTCAT;
      }
      break;

      case DEM_OBD_RDY_EVAP:
      {
        /* @Trace: Dem_SUD_API_12856 */
        /* Disable the event with masking 0x20 */
        Dem_GulEventIdDisabled =
            Dem_GulEventIdDisabled | DEM_OBD_RDY_DISABLE_EVAP;
      }
      break;

      case DEM_OBD_RDY_SECAIR:
      {
        /* @Trace: Dem_SUD_API_12840 */
        /* Disable the event with masking 0x40 */
        Dem_GulEventIdDisabled =
            Dem_GulEventIdDisabled | DEM_OBD_RDY_DISABLE_SECAIR;
      }
      break;

      case DEM_OBD_RDY_O2SENS:
      {
        /* @Trace: Dem_SUD_API_12841 */
        /* Disable the event with masking 0x80 */
        Dem_GulEventIdDisabled =
            Dem_GulEventIdDisabled | DEM_OBD_RDY_DISABLE_O2SENS;
      }
      break;

      case DEM_OBD_RDY_O2SENSHT:
      {
        /* @Trace: Dem_SUD_API_12842 */
        /* Disable the event with masking 0x100 */
        Dem_GulEventIdDisabled =
            Dem_GulEventIdDisabled | DEM_OBD_RDY_DISABLE_O2SENSHT;
      }
      break;

      case DEM_OBD_RDY_EGR:
      {
        /* @Trace: Dem_SUD_API_12843 */
        /* Disable the event with masking 0x200 */
        Dem_GulEventIdDisabled =
            Dem_GulEventIdDisabled | DEM_OBD_RDY_DISABLE_EGR;
      }
      break;

      case DEM_OBD_RDY_HCCAT:
      {
        /* @Trace: Dem_SUD_API_12844 */
        /* Disable the event with masking 0x400 */
        Dem_GulEventIdDisabled =
            Dem_GulEventIdDisabled | DEM_OBD_RDY_DISABLE_HCCAT;
      }
      break;

      case DEM_OBD_RDY_NOXCAT:
      {
        /* @Trace: Dem_SUD_API_12845 */
        /* Disable the event with masking 0x800 */
        Dem_GulEventIdDisabled =
            Dem_GulEventIdDisabled | DEM_OBD_RDY_DISABLE_NOXCAT;
      }
      break;

      case DEM_OBD_RDY_BOOSTPR:
      {
        /* @Trace: Dem_SUD_API_12846 */
        /* Disable the event with masking 0x1000 */
        Dem_GulEventIdDisabled =
            Dem_GulEventIdDisabled | DEM_OBD_RDY_DISABLE_BOOSTPR;
      }
      break;

      case DEM_OBD_RDY_EGSENS:
      {
        /* @Trace: Dem_SUD_API_12847 */
        /* Disable the event with masking 0x2000 */
        Dem_GulEventIdDisabled =
            Dem_GulEventIdDisabled | DEM_OBD_RDY_DISABLE_EGSENS;
      }
      break;

      case DEM_OBD_RDY_PMFLT:
      {
        /* @Trace: Dem_SUD_API_12848 */
        /* Disable the event with masking 0x4000 */
        Dem_GulEventIdDisabled =
            Dem_GulEventIdDisabled | DEM_OBD_RDY_DISABLE_PMFLT;
      }
      break;

      case DEM_OBD_RDY_AC:
      {
        /* @Trace: Dem_SUD_API_00139 */
        /* Disable the event with masking 0x8000 */
        Dem_GulEventIdDisabled =
            Dem_GulEventIdDisabled | DEM_OBD_RDY_DISABLE_AC;
      }
      break;
      default:
      /* Do Nothing */
      break;
    }

    SchM_Exit_Dem_CAPTURE_OBD_DATA();

    LddReturnValue = E_OK;
  }
  /* Return E_OK or E_NOT_OK */
  return(LddReturnValue);
}
#endif

/*******************************************************************************
** Function Name        : Dem_DcmReadDataOfPID01                              **
**                                                                            **
** Service ID           : 0x61                                                **
**                                                                            **
** Description          : Service to report the value of PID 01 for Dem       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : PID01value                                          **
**                                                                            **
** Return parameter     : Std_Returntype                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        Dem_GulPid01Value                                   **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Det_ReportError, Dem_CalcPIDValue                   **
*******************************************************************************/
/* @Trace: SRS_Diag_04126 SRS_Diag_04141 SRS_Diag_04220
 */
#if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
FUNC(Std_ReturnType, DEM_CODE) Dem_DcmReadDataOfPID01(
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA) PID01Value)
{
  /* @Trace: SWS_Dem_00293
   * For the following PIDs the data layout shall be compliant to SAE J1979DA
   * [18].
   * - PID $41 monitor status this driving cycle (4 byte)
   * - PID $01 monitor status since DTCs cleared (4 byte)
   * - PID $02 DTC that caused required freeze frame storage (2 byte)
   * - PID $1C OBD requirements to which vehicle or engine is certified (1 byte)
   * - PID $21 distance traveled while MIL is activated (2 byte)
   * - PID $30 number of warm-ups (WUC) since DTCs cleared (1 byte)
   * - PID $31 distance traveled since DTCs cleared (2 byte)
   * - PID $41 monitor status this driving cycle (4 byte)
   * - PID $4D engine run time while MIL is activated (2 byte)
   * - PID $4E engine run time since DTCs cleared (2 byte)
   * - PID $91 ECU OBD System Information (5 byte)
   */
  VAR(Std_ReturnType, DEM_VAR) LddReturnValue;

  /* @Trace: Dem_SUD_API_12558 */
  #if (DEM_MAX_NUMBER_EVENT_ENTRY_PER > DEM_ZERO)
  /* @Trace: Dem_SUD_API_12569 */
  VAR(uint8, DEM_VAR) LaaPid01data[DEM_FOUR] =
  {DEM_ZERO, DEM_ZERO, DEM_ZERO, DEM_ZERO};
  VAR(Dem_EventIdType, DEM_VAR) LddEventCount;
  VAR(Dem_EventIdType, DEM_VAR) LddConfirmedDtcCount;
  VAR(uint8, DEM_VAR) LucByteCount;
  #endif

  LddReturnValue = E_OK;
  /* Module Initialization check */
  if (DEM_INIT != Dem_GucInit)
  {
    /* @Trace: Dem_SUD_API_12580 */
    /* Error report to DET */
    DEM_REPORT_ERROR(DEM_DCMREADDATAOFPID01_SID, DEM_E_UNINIT);
  }
  else if (NULL_PTR == PID01Value)
  {
    /* @Trace: Dem_SUD_API_12591 */
    /* Report to DET */
    DEM_REPORT_ERROR(DEM_DCMREADDATAOFPID01_SID, DEM_E_PARAM_POINTER);
  }
  else
  {
    P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA) LpPID01Value = PID01Value;
    #if (DEM_MAX_NUMBER_EVENT_ENTRY_PER > DEM_ZERO)

    /* Initialise the event count to zero */
    LddEventCount = DEM_ZERO;
    LddConfirmedDtcCount = DEM_ZERO;
    /* Loop to find that number of events whose confirmed bit is set */
    while (LddEventCount < DEM_NUMBER_OF_EVENTS)
    {

      Dem_EventIdType LddEventId = LddEventCount + DEM_ONE;
      Dem_UdsStatusByteType LddEventStatusMask = DEM_ZERO;
      LddEventStatusMask = Dem_AllEventStatusByte[LddEventId];
      /* @Trace: Dem_SUD_API_12602 */
      #if (DEM_AVAILABILITY_SUPPORT == DEM_EVENT_AVAILABILITY)
      /* @Trace: Dem_SUD_API_12603 */
      boolean LblEventAvailable =
          Dem_EvIsProcStateTriggered(
              LddEventId, DEM_EVPROCSTATE_EVENT_AVAILABLE);
      #endif

      boolean LblDTCSuppression =
          Dem_EvIsProcStateTriggered(LddEventId, DEM_EVPROCSTATE_DTC_SUPP);
      /* @Trace: SWS_Dem_01103
       * Unavailable events shall not be considered for computation of service
       * $01 PID $41.*/

      /* @Trace: SWS_Dem_01101
       * A suppressed DTC shall not be visible for the following Dcm query-
       * functions; therefore the following functions shall treat the DTC as if
       * filter is not matching.
       * */
      /* Check if confirmedDtc bit is set or not */
      /* @Trace: Dem_SUD_API_12578 */
      if (Dem_Event[LddEventCount].e_PointToDTC < DEM_MAX_NUMBER_OF_DTC)
      {
        /* @Trace: Dem_SUD_API_12579 */
        if ((DEM_BIT3_MASK1 == (LddEventStatusMask & DEM_BIT3_MASK1)) &&
           (DEM_DTC_FORMAT_UDS !=
               Dem_GaaCombinedDtc
                 [Dem_Event[LddEventCount].e_PointToDTC].ddDtcFormat)
           #if (DEM_AVAILABILITY_SUPPORT == DEM_EVENT_AVAILABILITY)
           && (DEM_TRUE == LblEventAvailable)
           #endif
           && (DEM_TRUE != LblDTCSuppression)
          )
        {
          /* @Trace: Dem_SUD_API_12581 */
          /* confirmedDtcCount is incremented by 1 */
          LddConfirmedDtcCount = LddConfirmedDtcCount + DEM_ONE;
        }
      }
      /* Increment the count by 1 */
      LddEventCount++;
    }
    /* Check LusConfirmedDtcCountcount is greater than zero or not */
    if (LddConfirmedDtcCount > DEM_ZERO)
    {
      /* @Trace: SWS_Dem_00351
       * The Dem module shall compute and provide the number of confirmed
       * faults (PID $01, Byte A).
       * */
      /* Store the bit0 to bit6 of byteA with 0x7f*/
      /* @Trace: Dem_SUD_API_12601 */
      LaaPid01data[DEM_OBD_RDY_BYTE_A] = (uint8)(LddConfirmedDtcCount & DEM_BIT7_MASK2);


      /* @Trace: SWS_Dem_01138
       * The Dem module shall compute and provide the ECU MIL status (PID $01,
       * Byte A).
       * */
      /* update the bit7 to byteA */
        LaaPid01data[DEM_OBD_RDY_BYTE_A] = LaaPid01data[DEM_OBD_RDY_BYTE_A] | Dem_GucMilonFlag;
      
    }
    else
    {
      /* @Trace: Dem_SUD_API_12600 */
      /* @Trace: SWS_Dem_01137
       * For WWH-OBD PID$01 shall not provide the number of confirmed faults.
       * */

      /* @Trace: SWS_Dem_01139
       * For WWH-OBD PID$01 shall not provide the ECU MIL status.
       * */
      /* Update the byteA of pid01 with 0 as there is no confirmed dtc */
      LaaPid01data[DEM_OBD_RDY_BYTE_A] = DEM_ZERO;
    }

    /* PID01 ByteB lowernibble */
    LaaPid01data[DEM_OBD_RDY_BYTE_B] = (uint8)DEM_PID01_BYTEB_LOWER_NIBBLE &
      (uint8)DEM_MASK_LOWER_NIBBLE;

    /* Check Misfire is supported or not */
    /* @Trace: Dem_SUD_MACRO_038 */
    #if ((DEM_PID01_BYTEB_LOWER_NIBBLE & DEM_OBD_RDY_BYTEB_0_SUPPORTED_ENABLE_MISF) == DEM_OBD_RDY_BYTEB_0_SUPPORTED_ENABLE_MISF)
    {
      /* @Trace: Dem_SUD_API_12560 */
      /* Calculate Byte-2 Bit4 value*/
      /* Trace: DEM_OBD_01_03 */
      Dem_CalcReadinessPIDValue(DEM_PID01_CALC, &LaaPid01data[DEM_OBD_RDY_BYTE_B], 
        DEM_OBD_RDY_BYTEB_4_COMPLETENESS_READINESS_MISF, DEM_OBD_RDY_MISF);
    }
    #else
    {
      /* @Trace: Dem_SUD_API_12559 */
      /* Misfire not supported then bit4 of byteB is set to 0 */
      LaaPid01data[DEM_OBD_RDY_BYTE_B] = (LaaPid01data[DEM_OBD_RDY_BYTE_B] & ~DEM_OBD_RDY_BYTEB_4_COMPLETENESS_READINESS_MISF);
    }
    #endif
    /* Check Fuel system is supported or not */
    #if ((DEM_PID01_BYTEB_LOWER_NIBBLE & DEM_OBD_RDY_BYTEB_1_SUPPORTED_ENABLE_FLSYS) == DEM_OBD_RDY_BYTEB_1_SUPPORTED_ENABLE_FLSYS)
    {
      /* @Trace: Dem_SUD_API_12561 */
      /* Calculate Byte-2 Bit5 value*/
      /* Trace: DEM_OBD_01_03 */
      Dem_CalcReadinessPIDValue(DEM_PID01_CALC, &LaaPid01data[DEM_OBD_RDY_BYTE_B], 
        DEM_OBD_RDY_BYTEB_5_COMPLETENESS_READINESS_FLSYS, DEM_OBD_RDY_FLSYS);      
    }
    #else
    {
      /* @Trace: Dem_SUD_API_12562 */
      /* Fuel system not supported then bit5 is set of byteB to 0 */
      LaaPid01data[DEM_OBD_RDY_BYTE_B] = (LaaPid01data[DEM_OBD_RDY_BYTE_B] & ~DEM_OBD_RDY_BYTEB_5_COMPLETENESS_READINESS_FLSYS);
    }
    #endif

    /* Check Comprehensive component is supported or not */
     #if ((DEM_PID01_BYTEB_LOWER_NIBBLE & DEM_OBD_RDY_BYTEB_2_SUPPORTED_ENABLE_CMPRCMPT) == DEM_OBD_RDY_BYTEB_2_SUPPORTED_ENABLE_CMPRCMPT)
    {
      /* @Trace: Dem_SUD_API_12564 */
      /* Calculate Byte-2 Bit6 value*/
      /* Trace: DEM_OBD_01_03 */
      Dem_CalcReadinessPIDValue(DEM_PID01_CALC, &LaaPid01data[DEM_OBD_RDY_BYTE_B], 
        DEM_OBD_RDY_BYTEB_6_COMPLETENESS_READINESS_CMPRCMPT, DEM_OBD_RDY_CMPRCMPT);      
    }
    #else
    {
      /* @Trace: Dem_SUD_API_12563 */
      /* Comprehensive component not supported then bit6 of byteB is set to 0*/
      LaaPid01data[DEM_OBD_RDY_BYTE_B] = LaaPid01data[DEM_OBD_RDY_BYTE_B] & DEM_BIT6_MASK2;
    }
    #endif

    /* bit7 of byteB is set to 0 as it is ISO/SAE reserved */
    LaaPid01data[DEM_OBD_RDY_BYTE_B] = (LaaPid01data[DEM_OBD_RDY_BYTE_B] & ~DEM_OBD_RDY_BYTEB_7_COMPLETENESS_READINESS_RESERVED);

    /* Check for the engine is spark */
    #if ((DEM_PID01_BYTEB_LOWER_NIBBLE & DEM_OBD_RDY_BYTEB_3_COMPRESSION_SPARK_IGNITION) == DEM_ZERO)
    {
      /* PID01 ByteC */
      LaaPid01data[DEM_OBD_RDY_BYTE_C] = DEM_PID01_BYTEC_SPARK;

      /* Check Catalyst monitoring is supported or not */
      /* @Trace: Dem_SUD_MACRO_039 */
      #if ((DEM_PID01_BYTEC_SPARK & DEM_OBD_RDY_BYTEC_0_SPARK_SUPPORTED_ENABLED_CAT) == DEM_OBD_RDY_BYTEC_0_SPARK_SUPPORTED_ENABLED_CAT)
      {
        /* @Trace: Dem_SUD_API_12582 */
        /* Calculate Byte-3 Bit-1 value*/
        /* Trace: DEM_OBD_01_03 */
        Dem_CalcReadinessPIDValue(DEM_PID01_CALC, &LaaPid01data[DEM_OBD_RDY_BYTE_D], 
          DEM_OBD_RDY_BYTED_0_SPARK_COMPLETENESS_READINESS_CAT, DEM_OBD_RDY_CAT);
      }
      #else
      {
        /* @Trace: Dem_SUD_API_12583 */
        /*  Catalyst monitoring not supported then bit0 of byteD is set to 0 */
        LaaPid01data[DEM_OBD_RDY_BYTE_D] = (LaaPid01data[DEM_OBD_RDY_BYTE_D] & ~DEM_OBD_RDY_BYTED_0_SPARK_COMPLETENESS_READINESS_CAT);
      }
      #endif

      /* Check Heated Catalyst monitoring is supported or not */
      #if ((DEM_PID01_BYTEC_SPARK & DEM_OBD_RDY_BYTEC_1_SPARK_SUPPORTED_ENABLED_HTCAT) == DEM_OBD_RDY_BYTEC_1_SPARK_SUPPORTED_ENABLED_HTCAT)
      {
        /* @Trace: Dem_SUD_API_12584 */
        /* Calculate Byte-3 Bit-2 value*/
        /* Trace: DEM_OBD_01_03 */
        Dem_CalcReadinessPIDValue(DEM_PID01_CALC, &LaaPid01data[DEM_OBD_RDY_BYTE_D], 
          DEM_OBD_RDY_BYTED_1_SPARK_COMPLETENESS_READINESS_HTCAT, DEM_OBD_RDY_HTCAT); 
      }
      #else
      {
        /* @Trace: Dem_SUD_API_12585 */
        /* Heated Catalyst monitoring not supported then bit1 of byteD is set to
         0 */
        LaaPid01data[DEM_OBD_RDY_BYTE_D] = (LaaPid01data[DEM_OBD_RDY_BYTE_D] & ~DEM_OBD_RDY_BYTED_1_SPARK_COMPLETENESS_READINESS_HTCAT);
      }
      #endif

      /* Check Evaporative system monitoring is supported or not */
      #if ((DEM_PID01_BYTEC_SPARK & DEM_OBD_RDY_BYTEC_2_SPARK_SUPPORTED_ENABLED_EVAP) == DEM_OBD_RDY_BYTEC_2_SPARK_SUPPORTED_ENABLED_EVAP)
      {
        /* @Trace: Dem_SUD_API_12587 */
        /* Calculate Byte-3 Bit-2 value*/
        /* Trace: DEM_OBD_01_03 */
        Dem_CalcReadinessPIDValue(DEM_PID01_CALC, &LaaPid01data[DEM_OBD_RDY_BYTE_D], 
          DEM_OBD_RDY_BYTED_2_SPARK_COMPLETENESS_READINESS_EVAP, DEM_OBD_RDY_EVAP);
      }
      #else
      {
        /* @Trace: Dem_SUD_API_12586 */
        /*  Evaporative system monitoring not supported then bit2 of byteD is
          set to 0 */
        LaaPid01data[DEM_OBD_RDY_BYTE_D] = (LaaPid01data[DEM_OBD_RDY_BYTE_D] & ~DEM_OBD_RDY_BYTED_2_SPARK_COMPLETENESS_READINESS_EVAP);
      }
      #endif

      /* Check Secondary air system monitoring is supported or not */
      #if ((DEM_PID01_BYTEC_SPARK & DEM_OBD_RDY_BYTEC_3_SPARK_SUPPORTED_ENABLED_SECAIR) == DEM_OBD_RDY_BYTEC_3_SPARK_SUPPORTED_ENABLED_SECAIR)
      {
        /* @Trace: Dem_SUD_API_12589 */
        /* Calculate Byte-3 Bit-3 value*/
        /* Trace: DEM_OBD_01_03 */
        Dem_CalcReadinessPIDValue(DEM_PID01_CALC, &LaaPid01data[DEM_OBD_RDY_BYTE_D], 
          DEM_OBD_RDY_BYTED_3_SPARK_COMPLETENESS_READINESS_SECAIR, DEM_OBD_RDY_SECAIR);
      }
      #else
      {
        /* @Trace: Dem_SUD_API_12588 */
        /*  Secondary air system monitoring not supported then bit3 of byteD
          is set to 0 */
        LaaPid01data[DEM_OBD_RDY_BYTE_D] = (LaaPid01data[DEM_OBD_RDY_BYTE_D] & ~DEM_OBD_RDY_BYTED_3_SPARK_COMPLETENESS_READINESS_SECAIR);
      }
      #endif
      /*  As per ISO 0 is set to 0 */
      LaaPid01data[DEM_OBD_RDY_BYTE_C] = (LaaPid01data[DEM_OBD_RDY_BYTE_C] & ~DEM_OBD_RDY_BYTEC_4_SUPPORTED_ENABLED_RESERVED);
      /* As per ISO 0 is set to 0 */
      LaaPid01data[DEM_OBD_RDY_BYTE_D] = (LaaPid01data[DEM_OBD_RDY_BYTE_D] & ~DEM_OBD_RDY_BYTED_4_COMPLETENESS_READINESS_RESERVED);

      /* Check Oxygen sensor monitoring is supported or not */
      #if ((DEM_PID01_BYTEC_SPARK & DEM_OBD_RDY_BYTEC_5_SPARK_SUPPORTED_ENABLED_O2SENS) == DEM_OBD_RDY_BYTEC_5_SPARK_SUPPORTED_ENABLED_O2SENS)
      {
        /* @Trace: Dem_SUD_API_12590 */
        /* Calculate Byte-3 Bit-5 value*/
        /* Trace: DEM_OBD_01_03 */
        Dem_CalcReadinessPIDValue(DEM_PID01_CALC, &LaaPid01data[DEM_OBD_RDY_BYTE_D], 
          DEM_OBD_RDY_BYTED_5_SPARK_COMPLETENESS_READINESS_O2SENS, DEM_OBD_RDY_O2SENS);  
      }
      #else
      {
        /* @Trace: Dem_SUD_API_12592 */
        /* Oxygen sensor monitoring not supported then bit5 of byteD
          is set to 0 */
        LaaPid01data[DEM_OBD_RDY_BYTE_D] = (LaaPid01data[DEM_OBD_RDY_BYTE_D] & ~DEM_OBD_RDY_BYTED_5_SPARK_COMPLETENESS_READINESS_O2SENS);
      }
      #endif

      /* Check Oxygen sensor heater monitoring is supported or not */
      #if ((DEM_PID01_BYTEC_SPARK & DEM_OBD_RDY_BYTEC_6_SPARK_SUPPORTED_ENABLED_O2SENSHT) == DEM_OBD_RDY_BYTEC_6_SPARK_SUPPORTED_ENABLED_O2SENSHT)
      {
        /* @Trace: Dem_SUD_API_12593 */
        /* Calculate Byte-3 Bit-6 value*/
      /* Trace: DEM_OBD_01_03 */
      Dem_CalcReadinessPIDValue(DEM_PID01_CALC, &LaaPid01data[DEM_OBD_RDY_BYTE_D], 
      DEM_OBD_RDY_BYTED_6_SPARK_COMPLETENESS_READINESS_O2SENSHT, DEM_OBD_RDY_O2SENSHT);   
      }
      #else
      {
        /* @Trace: Dem_SUD_API_12594 */
        /* Oxygen sensor heater monitoring not supported then bit6 of byteD
          is set to 0 */
        LaaPid01data[DEM_OBD_RDY_BYTE_D] = (LaaPid01data[DEM_OBD_RDY_BYTE_D] & ~DEM_OBD_RDY_BYTED_6_SPARK_COMPLETENESS_READINESS_O2SENSHT);
      }
      #endif

      /* Check EGR system monitoring is supported or not */
      #if ((DEM_PID01_BYTEC_SPARK & DEM_OBD_RDY_BYTEC_7_SPARK_SUPPORTED_ENABLED_EGR) == DEM_OBD_RDY_BYTEC_7_SPARK_SUPPORTED_ENABLED_EGR)
      {
        /* @Trace: Dem_SUD_API_12595 */
        /* Calculate Byte-3 Bit-7 value*/
      /* Trace: DEM_OBD_01_03 */
      Dem_CalcReadinessPIDValue(DEM_PID01_CALC, &LaaPid01data[DEM_OBD_RDY_BYTE_D], 
      DEM_OBD_RDY_BYTED_7_SPARK_COMPLETENESS_READINESS_EGR, DEM_OBD_RDY_EGR);  
      }
      #else
      {
        /* @Trace: Dem_SUD_API_12596 */
        /* EGR system monitoring not supported then bit6 of byteD
          is set to 0 */
        LaaPid01data[DEM_OBD_RDY_BYTE_D] = (LaaPid01data[DEM_OBD_RDY_BYTE_D] & ~DEM_OBD_RDY_BYTED_7_SPARK_COMPLETENESS_READINESS_EGR);
      }
      #endif
    } /* Check for the engine is spark */
    #else
    {
      /* PID01 ByteC If compression engine */
      LaaPid01data[DEM_OBD_RDY_BYTE_C] = DEM_PID01_BYTEC_COMPRESSION;

      /* Check NMHC catalyst monitoring is supported or not */
      /* @Trace: Dem_SUD_MACRO_040 */
      #if ((DEM_PID01_BYTEC_COMPRESSION & DEM_OBD_RDY_BYTEC_0_COMPRESSION_SUPPORTED_ENABLED_HCCAT) == DEM_OBD_RDY_BYTEC_0_COMPRESSION_SUPPORTED_ENABLED_HCCAT)
      {
        /* @Trace: Dem_SUD_API_12565 */
        /* Calculate Byte-3 Bit-0 value*/
      /* Trace: DEM_OBD_01_03 */
      Dem_CalcReadinessPIDValue(DEM_PID01_CALC, &LaaPid01data[DEM_OBD_RDY_BYTE_D], 
      DEM_OBD_RDY_BYTED_0_COMPRESSION_COMPLETENESS_READINESS_HCCAT, DEM_OBD_RDY_HCCAT);
      }
      #else
      {
        /* @Trace: Dem_SUD_API_12566 */
        /* NMHC Catalyst monitoring not supported then bit0 of byteD is set to 0
         */
        LaaPid01data[DEM_OBD_RDY_BYTE_D] = (LaaPid01data[DEM_OBD_RDY_BYTE_D] & ~DEM_OBD_RDY_BYTED_0_COMPRESSION_COMPLETENESS_READINESS_HCCAT);
      }
      #endif

      /* Check NOx aftertreatment system monitoring is supported or not */
      #if ((DEM_PID01_BYTEC_COMPRESSION & DEM_OBD_RDY_BYTEC_1_COMPRESSION_SUPPORTED_ENABLED_NOXCAT) == DEM_OBD_RDY_BYTEC_1_COMPRESSION_SUPPORTED_ENABLED_NOXCAT)
      {
        /* @Trace: Dem_SUD_API_12567 */
        /* Calculate Byte-3 Bit-1 value*/
      /* Trace: DEM_OBD_01_03 */
      Dem_CalcReadinessPIDValue(DEM_PID01_CALC, &LaaPid01data[DEM_OBD_RDY_BYTE_D], 
      DEM_OBD_RDY_BYTED_1_COMPRESSION_COMPLETENESS_READINESS_NOXCAT, DEM_OBD_RDY_NOXCAT);
      }
      #else
      {
        /* @Trace: Dem_SUD_API_12568 */
        /*  NOx aftertreatment system monitoring not supported then bit1 of
            byteD is set to 0
         */
        LaaPid01data[DEM_OBD_RDY_BYTE_D] = (LaaPid01data[DEM_OBD_RDY_BYTE_D] & ~DEM_OBD_RDY_BYTED_1_COMPRESSION_COMPLETENESS_READINESS_NOXCAT);
      }
      #endif

      /* Set Bit2 of byteD to zero */
      LaaPid01data[DEM_OBD_RDY_BYTE_D] = LaaPid01data[DEM_OBD_RDY_BYTE_D] & DEM_BIT2_MASK2;

      /* Check Boost pressure system monitoring is supported or not */
      #if ((DEM_PID01_BYTEC_COMPRESSION & DEM_OBD_RDY_BYTEC_3_COMPRESSION_SUPPORTED_ENABLED_BOOSTPR) == DEM_OBD_RDY_BYTEC_3_COMPRESSION_SUPPORTED_ENABLED_BOOSTPR)
      {
        /* @Trace: Dem_SUD_API_12570 */
        /* Calculate Byte-3 Bit-3 value*/
      /* Trace: DEM_OBD_01_03 */
      Dem_CalcReadinessPIDValue(DEM_PID01_CALC, &LaaPid01data[DEM_OBD_RDY_BYTE_D], 
      DEM_OBD_RDY_BYTED_3_COMPRESSION_COMPLETENESS_READINESS_BOOSTPR, DEM_OBD_RDY_BOOSTPR);
      }
      #else
      {
        /* @Trace: Dem_SUD_API_12571 */
        /* Boost pressure system monitoring not supported then bit3 of byteD
           is set to 0
         */
        LaaPid01data[DEM_OBD_RDY_BYTE_D] = (LaaPid01data[DEM_OBD_RDY_BYTE_D] & ~DEM_OBD_RDY_BYTED_3_COMPRESSION_COMPLETENESS_READINESS_BOOSTPR);
      }
      #endif

      /* Set Bit4 of byteD to zero */
      LaaPid01data[DEM_OBD_RDY_BYTE_D] = LaaPid01data[DEM_OBD_RDY_BYTE_D] & DEM_BIT4_MASK2;

      /* Check Exhaust gas sensor monitoring is supported or not */
      #if ((DEM_PID01_BYTEC_COMPRESSION & DEM_OBD_RDY_BYTEC_5_COMPRESSION_SUPPORTED_ENABLED_EGSENS) == DEM_OBD_RDY_BYTEC_5_COMPRESSION_SUPPORTED_ENABLED_EGSENS)
      {
        /* @Trace: Dem_SUD_API_12572 */
        /* Calculate Byte-3 Bit- value*/
      /* Trace: DEM_OBD_01_03 */
      Dem_CalcReadinessPIDValue(DEM_PID01_CALC, &LaaPid01data[DEM_OBD_RDY_BYTE_D], 
      DEM_OBD_RDY_BYTED_5_COMPRESSION_COMPLETENESS_READINESS_EGSENS, DEM_OBD_RDY_EGSENS);  
      }
      #else
      {
        /* @Trace: Dem_SUD_API_12573 */
        /* Exhaust gas sensor not supported then bit5 of byteD
          is set to 0 */
        LaaPid01data[DEM_OBD_RDY_BYTE_D] = (LaaPid01data[DEM_OBD_RDY_BYTE_D] & ~DEM_OBD_RDY_BYTED_5_COMPRESSION_COMPLETENESS_READINESS_EGSENS);
      }
      #endif

      /* Check PM filter monitoring is supported or not */
      #if ((DEM_PID01_BYTEC_COMPRESSION & DEM_OBD_RDY_BYTEC_6_COMPRESSION_SUPPORTED_ENABLED_PMFLT) == DEM_OBD_RDY_BYTEC_6_COMPRESSION_SUPPORTED_ENABLED_PMFLT)
      {
        /* @Trace: Dem_SUD_API_12574 */
        /* Calculate Byte-3 Bit-6 value*/
      /* Trace: DEM_OBD_01_03 */
      Dem_CalcReadinessPIDValue(DEM_PID01_CALC, &LaaPid01data[DEM_OBD_RDY_BYTE_D], 
      DEM_OBD_RDY_BYTED_6_COMPRESSION_COMPLETENESS_READINESS_PMFLT, DEM_OBD_RDY_PMFLT);
      }
      #else
      {
        /* @Trace: Dem_SUD_API_12575 */
        /* PM filter monitoring not supported then bit6 of byteD
          is set to 0 */
        LaaPid01data[DEM_OBD_RDY_BYTE_D] = (LaaPid01data[DEM_OBD_RDY_BYTE_D] & ~DEM_OBD_RDY_BYTED_6_COMPRESSION_COMPLETENESS_READINESS_PMFLT);
      }
      #endif

      /* Check EGR system monitoring is supported or not */
      #if ((DEM_PID01_BYTEC_COMPRESSION & DEM_OBD_RDY_BYTEC_7_SPARK_SUPPORTED_ENABLED_EGR) == DEM_OBD_RDY_BYTEC_7_SPARK_SUPPORTED_ENABLED_EGR)
      {
        /* @Trace: Dem_SUD_API_12576 */
        /* Calculate Byte-3 Bit-7 value*/
      /* Trace: DEM_OBD_01_03 */
      Dem_CalcReadinessPIDValue(DEM_PID01_CALC, &LaaPid01data[DEM_OBD_RDY_BYTE_D], 
      DEM_OBD_RDY_BYTED_7_SPARK_COMPLETENESS_READINESS_EGR, DEM_OBD_RDY_EGR);  

      }
      #else
      {
        /* @Trace: Dem_SUD_API_12577 */
        /* EGR system monitoring not supported then bit6 of byteD
          is set to 0 */
        LaaPid01data[DEM_OBD_RDY_BYTE_D] = (LaaPid01data[DEM_OBD_RDY_BYTE_D] & ~DEM_OBD_RDY_BYTED_7_SPARK_COMPLETENESS_READINESS_EGR);
      }
      #endif
    }
    #endif

    /* Initialise  the count value to zero */
    /* @Trace: Dem_SUD_API_12598 */
    LucByteCount = DEM_ZERO;

    /* Loop for giving the data */
    while (LucByteCount < DEM_FOUR)
    {
      /* @Trace: Dem_SUD_API_12597 */
      /* Output data into destination buffer */
      *LpPID01Value = LaaPid01data[LucByteCount];

      /*
       * MISRA Rule        : 17.4
       * Message           : Increment or decrement operation performed
       *                     on pointer.
       * Reason            : Increment operator is used to achieve better
       *                     throughput.
       * Verification      : However, part of the code is verified manually
                            and it is not having any impact
       */
       LpPID01Value++;

      LucByteCount++;
    }
    #else
    /*No event is present in primary memory */
    /* @Trace: Dem_SUD_API_12599 */
    *LpPID01Value = DEM_ZERO;
    #endif
  } /*Det check */
  return (LddReturnValue);
}
#endif



/*******************************************************************************
** Function Name        : Dem_ReadDataOfPID01                                 **
**                                                                            **
** Service ID           : 0x61                                                **
**                                                                            **
** Description          : Service to report the value of PID $01 computed by  **
**                        the Dem API is needed in OBD relevant ECUs only     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : PID01value                                          **
**                                                                            **
** Return parameter     : Std_Returntype                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        Dem_GulPid01Value                                   **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Det_ReportError, Dem_CalcPIDValue                   **
*******************************************************************************/
#if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
FUNC(Std_ReturnType, DEM_CODE) Dem_ReadDataOfPID01(
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA) PID01Value)
{
  /* @Trace: Dem_SUD_API_12888 */
  VAR(Std_ReturnType, DEM_VAR) LddReturnValue = E_OK;
  /* Module Initialization check */
  if (DEM_INIT != Dem_GucInit)
  {
    /* @Trace: Dem_SUD_API_00160 */
    /* Error report to DET */
    DEM_REPORT_ERROR(DEM_READDATAOFPID01_SID, DEM_E_UNINIT);
    LddReturnValue = E_NOT_OK;
  }
  else if (NULL_PTR == PID01Value)
  {
    /* @Trace: Dem_SUD_API_00163 */
    /* Report to DET */
    DEM_REPORT_ERROR(DEM_READDATAOFPID01_SID, DEM_E_PARAM_POINTER);
    LddReturnValue = E_NOT_OK;
  }
  else
  {
    /* @Trace: Dem_SUD_API_00164 */
    LddReturnValue = Dem_DcmReadDataOfPID01(PID01Value);
    /* @LddReturnValue = E_OK;*/
  }

  return LddReturnValue;
}
#endif

/*******************************************************************************
** Function Name        : Dem_GetB1Counter                                    **
**                                                                            **
** Service ID           : 0x61                                                **
**                                                                            **
** Description          : Service to report the value of the B1 counter       **
**                        computed by the Dem. API is needed in WWH-OBD       **
**                        relevant ECUs only                                  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : B1Counter                                           **
**                                                                            **
** Return parameter     : Std_Returntype                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        Dem_GulPid01Value                                   **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Det_ReportError, Dem_CalcPIDValue                   **
*******************************************************************************/
#if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
FUNC(Std_ReturnType, DEM_CODE) Dem_GetB1Counter(
  P2VAR(uint16, AUTOMATIC, DEM_APPL_DATA) B1Counter)
{
  VAR(Std_ReturnType, DEM_VAR) LddReturnValue = E_OK;
  /* Module Initialization check */
  if (DEM_INIT != Dem_GucInit)
  {
    /* @Trace: Dem_SUD_API_00161 */
    /* Error report to DET */
    DEM_REPORT_ERROR(DEM_GETB1COUNTER_SID, DEM_E_UNINIT);
    LddReturnValue = E_NOT_OK;
  }
  else if (NULL_PTR == B1Counter)
  {
    /* @Trace: Dem_SUD_API_00165 */
    /* Report to DET */
    DEM_REPORT_ERROR(DEM_GETB1COUNTER_SID, DEM_E_PARAM_POINTER);
    LddReturnValue = E_NOT_OK;
  }
  else
  {
    /* @Trace: Dem_SUD_API_00166 */
    *B1Counter = Dem_WWHOBDB1Counter;
    /* @LddReturnValue = E_OK;*/
  }
  return LddReturnValue;
}
#endif

/*******************************************************************************
** Function Name        : Dem_DcmReadDataOfPID21                              **
**                                                                            **
** Service ID           : 0x64                                                **
**                                                                            **
** Description          : Service to report the value of PID 21 for Dem       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : PID21value                                          **
**                                                                            **
** Return parameter     : Std_Returntype                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        Dem_GaaPid, Dem_GulTimeSinceMilOn                   **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Det_ReportError, Dem_GetReadDataOfPID               **
*******************************************************************************/
/* Check if DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT */
/* @Trace: Dem_SUD_MACRO_136 */
#if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
FUNC(Std_ReturnType, DEM_CODE) Dem_DcmReadDataOfPID21(
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA) PID21Value)
{
  /* @Trace: SWS_Dem_01098
   * On invocation of Dem_DcmReadDataOfPID21 the Dem shall return the
   * current value of PID $21.
   * */
  /* @Trace: SWS_Dem_01099
   * If Dem_DcmReadDataOfPID21 is called before Dem_SetDataOfPID21,
   * the Dem shall return 0xFFFF as PID $21 value.*/
  /* @Trace: SWS_Dem_00346
   * The Dem module shall use PID $0D (refer to chapter 7.11.7) to
   * calculate PID $21 and PID $31.*/
  /* @Trace: SWS_Dem_00293
   * For the following PIDs the data layout shall be compliant to SAE J1979DA
   * [18].
   * - PID $41 monitor status this driving cycle (4 byte)
   * - PID $01 monitor status since DTCs cleared (4 byte)
   * - PID $02 DTC that caused required freeze frame storage (2 byte)
   * - PID $1C OBD requirements to which vehicle or engine is certified (1 byte)
   * - PID $21 distance traveled while MIL is activated (2 byte)
   * - PID $30 number of warm-ups (WUC) since DTCs cleared (1 byte)
   * - PID $31 distance traveled since DTCs cleared (2 byte)
   * - PID $41 monitor status this driving cycle (4 byte)
   * - PID $4D engine run time while MIL is activated (2 byte)
   * - PID $4E engine run time since DTCs cleared (2 byte)
   * - PID $91 ECU OBD System Information (5 byte)
   */
  VAR(Std_ReturnType, DEM_VAR) LddReturnValue = E_OK;

  /* Module Initialization check */
  if (DEM_INIT != Dem_GucInit)
  {
    /* @Trace: Dem_SUD_API_12607 */
    /* Error report to DET */
    DEM_REPORT_ERROR(DEM_DCMREADDATAOFPID21_SID, DEM_E_UNINIT);
    LddReturnValue = E_NOT_OK;
  }
  else if (NULL_PTR == PID21Value)
  {
    /* @Trace: Dem_SUD_API_12608 */
    /* Report to DET */
    DEM_REPORT_ERROR(DEM_DCMREADDATAOFPID21_SID, DEM_E_PARAM_POINTER);
    LddReturnValue = E_NOT_OK;
  }
  else
  {
    /*size is 16bit*/
    P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA) LpPID21Value = PID21Value;
    /* @Trace: Dem_SUD_API_12609 */
    /* @Trace: Dem_SUD_MACRO_148 */
    #if ((DEM_OBD_CENTRALIZED_PID_21_HANDLING == STD_ON) && \
         (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT))
         /* @Trace: Dem_SUD_API_12610 */
    *LpPID21Value = (uint8)(Dem_DataOfPID21 & 0x00FFU);
    LpPID21Value++;
    *LpPID21Value = (uint8)((Dem_DataOfPID21 & 0xFF00U) >> DEM_EIGHT);
    #endif
  }
  return(LddReturnValue);
}
#endif
/*******************************************************************************
** Function Name        : Dem_DcmReadDataOfPID30                              **
**                                                                            **
** Service ID           : 0x65                                                **
**                                                                            **
** Description          : Service to report the value of PID 30 for Dem       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : PID30value                                          **
**                                                                            **
** Return parameter     : Std_Returntype                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        Function(s) invoked :                               **
**                        Det_ReportError                                     **
**                        SchM_Exit_Dem_CAPTURE_OBD_DATA                      **
*******************************************************************************/
/* Check if DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT */
/* @Trace: Dem_SUD_MACRO_137 */
#if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
FUNC(Std_ReturnType, DEM_CODE) Dem_DcmReadDataOfPID30(
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA) PID30Value)
{
  /* @Trace: SWS_Dem_00293
   * For the following PIDs the data layout shall be compliant to SAE J1979DA
   * [18].
   * - PID $41 monitor status this driving cycle (4 byte)
   * - PID $01 monitor status since DTCs cleared (4 byte)
   * - PID $02 DTC that caused required freeze frame storage (2 byte)
   * - PID $1C OBD requirements to which vehicle or engine is certified (1 byte)
   * - PID $21 distance traveled while MIL is activated (2 byte)
   * - PID $30 number of warm-ups (WUC) since DTCs cleared (1 byte)
   * - PID $31 distance traveled since DTCs cleared (2 byte)
   * - PID $41 monitor status this driving cycle (4 byte)
   * - PID $4D engine run time while MIL is activated (2 byte)
   * - PID $4E engine run time since DTCs cleared (2 byte)
   * - PID $91 ECU OBD System Information (5 byte)
   */
  VAR(Std_ReturnType, DEM_VAR) LddReturnValue = E_OK;

  /* Module Initialization check */
  if (DEM_INIT != Dem_GucInit)
  {
    /* @Trace: Dem_SUD_API_12611 */
     /* Error report to DET */
    DEM_REPORT_ERROR(DEM_DCMREADDATAOFPID30_SID, DEM_E_UNINIT);
  }
  else if (NULL_PTR == PID30Value)
  {
    /* @Trace: Dem_SUD_API_12612 */
    /* Report to DET */
    DEM_REPORT_ERROR(DEM_DCMREADDATAOFPID30_SID, DEM_E_PARAM_POINTER);
  }
  else
  {
    /* Check count is not maximum */
    if (Dem_EventStatusNvRamData.NumOfWUCSinceLC < DEM_MAX_WARM_UP_COUNT)
    {
      /* @Trace: Dem_SUD_API_12613 */
      /* Store the LSB byte */
      *PID30Value = Dem_EventStatusNvRamData.NumOfWUCSinceLC;
    }
    else
    {
      /* @Trace: Dem_SUD_API_12614 */
      *PID30Value = DEM_MAX_WARM_UP_COUNT;
    }
  }
  return(LddReturnValue);
}
#endif
/*******************************************************************************
** Function Name        : Dem_DcmReadDataOfPID31                              **
**                                                                            **
** Service ID           : 0x66                                                **
**                                                                            **
** Description          : Service to report the value of PID 31 for Dem       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : PID31value                                          **
**                                                                            **
** Return parameter     : Std_Returntype                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s):Dem_GulDemClearTimeCount,        **
**                        Dem_GaaPid                                          **
**                        Function(s) invoked :                               **
**                        Det_ReportError, Dem_GetReadDataOfPID               **
*******************************************************************************/
/* Check if DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT */
/* @Trace: Dem_SUD_MACRO_138 */
#if (DEM_OBD_SUPPORT == DEM_OBD_MASTER_ECU)
FUNC(Std_ReturnType, DEM_CODE) Dem_DcmReadDataOfPID31(
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA) PID31Value)
{
  /* @Trace: SWS_Dem_00704
   * Only the Master ECU is allowed to report information for PID
   * $31 / $4D / $4E to the scan tool.
   * */
  /* @Trace: SWS_Dem_00293
   * For the following PIDs the data layout shall be compliant to SAE J1979DA
   * [18].
   * - PID $41 monitor status this driving cycle (4 byte)
   * - PID $01 monitor status since DTCs cleared (4 byte)
   * - PID $02 DTC that caused required freeze frame storage (2 byte)
   * - PID $1C OBD requirements to which vehicle or engine is certified (1 byte)
   * - PID $21 distance traveled while MIL is activated (2 byte)
   * - PID $30 number of warm-ups (WUC) since DTCs cleared (1 byte)
   * - PID $31 distance traveled since DTCs cleared (2 byte)
   * - PID $41 monitor status this driving cycle (4 byte)
   * - PID $4D engine run time while MIL is activated (2 byte)
   * - PID $4E engine run time since DTCs cleared (2 byte)
   * - PID $91 ECU OBD System Information (5 byte)
   */
  VAR(Std_ReturnType, DEM_VAR) LddReturnValue = E_OK;

  /* Module Initialization check */
  if (DEM_INIT != Dem_GucInit)
  {
    /* @Trace: Dem_SUD_API_12615 */
   /* Error report to DET */
    DEM_REPORT_ERROR(DEM_DCMREADDATAOFPID31_SID, DEM_E_UNINIT);
    LddReturnValue = E_NOT_OK;
  }
  else if (NULL_PTR == PID31Value)
  {
    /* @Trace: Dem_SUD_API_12616 */
    /* Report to DET */
    DEM_REPORT_ERROR(DEM_DCMREADDATAOFPID31_SID, DEM_E_PARAM_POINTER);
    LddReturnValue = E_NOT_OK;
  }
  else
  {
    /* @Trace: Dem_SUD_API_12617 */
    /* MISRA Rule : 10.1
     * Message : Implicit conversion from unsigned long to double.
     * Reason : The result will never be greater than unsigned long
     * Verification : However, part of the code is verified
     * manually and it is not having any impact.
     */
    /* @Trace: SWS_Dem_00703
     * The Dem of the Master ECU shall calculate information for
     * PID $31 / $4D / $4E vehicle wide.
     * */
    /*size is 16bit)*/
    P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA) LpPID31Value = PID31Value;
    *LpPID31Value = (uint8)(Dem_DataOfPID31 & 0x00FFU);
    LpPID31Value++;
    *LpPID31Value = (uint8)((Dem_DataOfPID31 & 0xFF00U) >> DEM_EIGHT);
  }
  return(LddReturnValue);
}
#endif
/*******************************************************************************
** Function Name        : Dem_DcmReadDataOfPID41                              **
**                                                                            **
** Service ID           : 0x67                                                **
**                                                                            **
** Description          : Service to report the value of PID 41 for Dem       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : PID41value                                          **
**                                                                            **
** Return parameter     : Std_Returntype                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : None                          **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Det_ReportError, Dem_GetReadDataOfPID               **
**                        SchM_Exit_Dem_CAPTURE_OBD_DATA                      **
*******************************************************************************/
/* Check if DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT */
/* @Trace: Dem_SUD_MACRO_140 */
#if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
FUNC(Std_ReturnType, DEM_CODE) Dem_DcmReadDataOfPID41(
 P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA) PID41Value)
{
  /* @Trace: SWS_Dem_00293
   * For the following PIDs the data layout shall be compliant to SAE J1979DA
   * [18].
   * - PID $41 monitor status this driving cycle (4 byte)
   * - PID $01 monitor status since DTCs cleared (4 byte)
   * - PID $02 DTC that caused required freeze frame storage (2 byte)
   * - PID $1C OBD requirements to which vehicle or engine is certified (1 byte)
   * - PID $21 distance traveled while MIL is activated (2 byte)
   * - PID $30 number of warm-ups (WUC) since DTCs cleared (1 byte)
   * - PID $31 distance traveled since DTCs cleared (2 byte)
   * - PID $41 monitor status this driving cycle (4 byte)
   * - PID $4D engine run time while MIL is activated (2 byte)
   * - PID $4E engine run time since DTCs cleared (2 byte)
   * - PID $91 ECU OBD System Information (5 byte)
   */
  VAR(Std_ReturnType, DEM_VAR) LddReturnValue = E_OK;
  VAR(uint8, DEM_VAR) LaaPid41data[DEM_FOUR] = {DEM_ZERO, DEM_ZERO, DEM_ZERO,
      DEM_ZERO};
  VAR(uint8, DEM_VAR) LucByteCount;

  /* Module Initialization check */
  if (DEM_INIT != Dem_GucInit)
  {
    /* @Trace: Dem_SUD_API_12618 */
    /* Error report to DET */
    DEM_REPORT_ERROR(DEM_DCMREADDATAOFPID41_SID, DEM_E_UNINIT);
  }
  else if (NULL_PTR == PID41Value)
  {
    /* @Trace: Dem_SUD_API_12622 */
    /* Report to DET */
    DEM_REPORT_ERROR(DEM_DCMREADDATAOFPID41_SID, DEM_E_PARAM_POINTER);
  }
  else
  {
    P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA) LpPID41Value = PID41Value;
    /* Set byte1 of Pid41 to Zero as per SAEJ1979 */
    LaaPid41data[DEM_ZERO] = DEM_ZERO;

    /* Initialize local variables to zero */
    LaaPid41data[DEM_ONE] = DEM_ZERO;
    LaaPid41data[DEM_TWO] = DEM_ZERO;
    LaaPid41data[DEM_THREE] = DEM_ZERO;
    /* Check that event is disabled for Misfire monitoring or it is not
     * supported.
     */
    #if ((DEM_PID01_BYTEB_LOWER_NIBBLE & DEM_OBD_RDY_BYTEB_0_SUPPORTED_ENABLE_MISF) != DEM_OBD_RDY_BYTEB_0_SUPPORTED_ENABLE_MISF)
    /* @Trace: Dem_SUD_API_12623 */
    /* Bit0, Bit4 of byte-2 are set to 0 WITH MASK 0XEE*/
    LaaPid41data[DEM_OBD_RDY_BYTE_B] = (LaaPid41data[DEM_OBD_RDY_BYTE_B] & ~DEM_OBD_RDY_BYTEB_0_SUPPORTED_ENABLE_MISF);
    LaaPid41data[DEM_OBD_RDY_BYTE_B] = (LaaPid41data[DEM_OBD_RDY_BYTE_B] & ~DEM_OBD_RDY_BYTEB_4_COMPLETENESS_READINESS_MISF);
    #else
    /* @Trace: SWS_Dem_00356
      * The Dem module shall compute the readiness group disabled
      * (if the disabled status is reported by the monitor for any
      * event of a group). OBD Events Suppression (refer to chapter 7.4.8)
      * shall be ignored for this computation.*/

    /* Trace: DEM_OBD_01_02 */
    Dem_CalcPID41PerGroup(&LaaPid41data[DEM_OBD_RDY_BYTE_B], 
                          DEM_OBD_RDY_DISABLE_MISF, 
                          DEM_OBD_RDY_MISF, 
                          DEM_OBD_RDY_BYTEB_4_COMPLETENESS_READINESS_MISF);    
    #endif

    /* Check that event is disabled for Fuel system monitoring */
    #if ((DEM_PID01_BYTEB_LOWER_NIBBLE & DEM_OBD_RDY_BYTEB_1_SUPPORTED_ENABLE_FLSYS) != DEM_OBD_RDY_BYTEB_1_SUPPORTED_ENABLE_FLSYS)
    /* @Trace: Dem_SUD_API_12625 */
    /* Bit1, Bit5 of byte-2 are set to 0 */
    LaaPid41data[DEM_OBD_RDY_BYTE_B] = (LaaPid41data[DEM_OBD_RDY_BYTE_B] & ~DEM_OBD_RDY_BYTEB_1_SUPPORTED_ENABLE_FLSYS);
    LaaPid41data[DEM_OBD_RDY_BYTE_B] = (LaaPid41data[DEM_OBD_RDY_BYTE_B] & ~DEM_OBD_RDY_BYTEB_5_COMPLETENESS_READINESS_FLSYS);
    #else
    /* Trace: DEM_OBD_01_02 */
    Dem_CalcPID41PerGroup(&LaaPid41data[DEM_OBD_RDY_BYTE_B], 
                          DEM_OBD_RDY_DISABLE_FLSYS, 
                          DEM_OBD_RDY_FLSYS, 
                          DEM_OBD_RDY_BYTEB_5_COMPLETENESS_READINESS_FLSYS);
    #endif

    /* Check that event is disabled for Comprehensive component monitoring */
    #if ((DEM_PID01_BYTEB_LOWER_NIBBLE & DEM_OBD_RDY_BYTEB_2_SUPPORTED_ENABLE_CMPRCMPT) != DEM_OBD_RDY_BYTEB_2_SUPPORTED_ENABLE_CMPRCMPT)
    /* @Trace: Dem_SUD_API_12627 */
    /* Bit-2, Bit-6 of byte-2 are set to 0 */
    LaaPid41data[DEM_OBD_RDY_BYTE_B] = (LaaPid41data[DEM_OBD_RDY_BYTE_B] & ~DEM_OBD_RDY_BYTEB_2_SUPPORTED_ENABLE_CMPRCMPT);
    LaaPid41data[DEM_OBD_RDY_BYTE_B] = (LaaPid41data[DEM_OBD_RDY_BYTE_B] & ~DEM_OBD_RDY_BYTEB_6_COMPLETENESS_READINESS_CMPRCMPT);
    #else
    /* Trace: DEM_OBD_01_02 */
    Dem_CalcPID41PerGroup(&LaaPid41data[DEM_OBD_RDY_BYTE_B], 
                          DEM_OBD_RDY_DISABLE_CMPRCMPT, 
                          DEM_OBD_RDY_CMPRCMPT, 
                          DEM_OBD_RDY_BYTEB_6_COMPLETENESS_READINESS_CMPRCMPT);
    #endif

    /* Check Compression ignition monitoring supported*/
    #if ((DEM_PID01_BYTEB_LOWER_NIBBLE & DEM_OBD_RDY_BYTEB_3_COMPRESSION_SPARK_IGNITION) == DEM_OBD_RDY_BYTEB_3_COMPRESSION_SPARK_IGNITION)
    /* Trace: DEM_OBD_09_09 */
    /* Bit3 of byte2 is set to 0 if Spark ignition monitors supported */
    /* @Trace: Dem_SUD_API_12629 */
    LaaPid41data[DEM_OBD_RDY_BYTE_B] = (LaaPid41data[DEM_OBD_RDY_BYTE_B] | ~DEM_OBD_RDY_BYTEB_3_COMPRESSION_SPARK_IGNITION);
    #else
    /* Trace: DEM_OBD_09_09 */
    /* Bit3 of byte2 is set to 0 if Spark ignition monitors supported */
    /* @Trace: Dem_SUD_API_12619 */
    LaaPid41data[DEM_OBD_RDY_BYTE_B] = LaaPid41data[DEM_OBD_RDY_BYTE_B] & (~DEM_OBD_RDY_BYTEB_3_COMPRESSION_SPARK_IGNITION);
    #endif

    /* Set bit7 is set of byte2 to 0 as it is ISO reserved */
    LaaPid41data[DEM_OBD_RDY_BYTE_B] = (LaaPid41data[DEM_OBD_RDY_BYTE_B] & ~DEM_OBD_RDY_BYTEB_7_COMPLETENESS_READINESS_RESERVED);

    /* For spark engines*/
    /* @Trace: Dem_SUD_MACRO_039 */
    #if ((DEM_PID01_BYTEB_LOWER_NIBBLE & DEM_OBD_RDY_BYTEB_3_COMPRESSION_SPARK_IGNITION) == DEM_ZERO)
    /* Check Catalyst monitoring is supported or not */
    #if ((DEM_PID01_BYTEC_SPARK & DEM_OBD_RDY_BYTEC_0_SPARK_SUPPORTED_ENABLED_CAT) == \
                                  DEM_OBD_RDY_BYTEC_0_SPARK_SUPPORTED_ENABLED_CAT)  
    Dem_CalcPID41PerGroupCheck(
        DEM_OBD_RDY_DISABLE_CAT,
        DEM_OBD_RDY_CAT,
        DEM_OBD_RDY_BYTEC_0_SPARK_SUPPORTED_ENABLED_CAT,
        DEM_OBD_RDY_BYTED_0_SPARK_COMPLETENESS_READINESS_CAT,
        &LaaPid41data[DEM_OBD_RDY_BYTE_C],
        &LaaPid41data[DEM_OBD_RDY_BYTE_D]
      );
    #else
    /*  monitoring disabled */
    LaaPid41data[DEM_OBD_RDY_BYTE_C] = (LaaPid41data[DEM_OBD_RDY_BYTE_C] & ~DEM_OBD_RDY_BYTEC_0_SPARK_SUPPORTED_ENABLED_CAT);
    #endif

    /* Check Heated Catalyst monitoring is supported or not */
    #if ((DEM_PID01_BYTEC_SPARK & DEM_OBD_RDY_BYTEC_1_SPARK_SUPPORTED_ENABLED_HTCAT) == \
                                  DEM_OBD_RDY_BYTEC_1_SPARK_SUPPORTED_ENABLED_HTCAT)  
    Dem_CalcPID41PerGroupCheck(
        DEM_OBD_RDY_DISABLE_HTCAT,
        DEM_OBD_RDY_HTCAT,
        DEM_OBD_RDY_BYTEC_1_SPARK_SUPPORTED_ENABLED_HTCAT,
        DEM_OBD_RDY_BYTED_1_SPARK_COMPLETENESS_READINESS_HTCAT,
        &LaaPid41data[DEM_OBD_RDY_BYTE_C],
        &LaaPid41data[DEM_OBD_RDY_BYTE_D]
      );
    #else
    LaaPid41data[DEM_OBD_RDY_BYTE_C] = (LaaPid41data[DEM_OBD_RDY_BYTE_C] & ~DEM_OBD_RDY_BYTEC_1_SPARK_SUPPORTED_ENABLED_HTCAT);      
    #endif

    /* Check Evaporative system monitoring is supported or not */
    #if ((DEM_PID01_BYTEC_SPARK & DEM_OBD_RDY_BYTEC_2_SPARK_SUPPORTED_ENABLED_EVAP) == \
                                  DEM_OBD_RDY_BYTEC_2_SPARK_SUPPORTED_ENABLED_EVAP)  
    Dem_CalcPID41PerGroupCheck(
        DEM_OBD_RDY_DISABLE_EVAP,
        DEM_OBD_RDY_EVAP,
        DEM_OBD_RDY_BYTEC_2_SPARK_SUPPORTED_ENABLED_EVAP,
        DEM_OBD_RDY_BYTED_2_SPARK_COMPLETENESS_READINESS_EVAP,
        &LaaPid41data[DEM_OBD_RDY_BYTE_C],
        &LaaPid41data[DEM_OBD_RDY_BYTE_D]
      );
    #else
    /*  Evaporative system monitoring not supported then bit2 of byteD is set to 0 */
    LaaPid41data[DEM_OBD_RDY_BYTE_C] = (LaaPid41data[DEM_OBD_RDY_BYTE_C] & ~DEM_OBD_RDY_BYTEC_2_SPARK_SUPPORTED_ENABLED_EVAP); 
    #endif

    /* Check Secondary air system monitoring is supported or not */
    #if ((DEM_PID01_BYTEC_SPARK & DEM_OBD_RDY_BYTEC_3_SPARK_SUPPORTED_ENABLED_SECAIR) == \
                                  DEM_OBD_RDY_BYTEC_3_SPARK_SUPPORTED_ENABLED_SECAIR)  
    Dem_CalcPID41PerGroupCheck(
        DEM_OBD_RDY_DISABLE_SECAIR,
        DEM_OBD_RDY_SECAIR,
        DEM_OBD_RDY_BYTEC_3_SPARK_SUPPORTED_ENABLED_SECAIR,
        DEM_OBD_RDY_BYTED_3_SPARK_COMPLETENESS_READINESS_SECAIR,
        &LaaPid41data[DEM_OBD_RDY_BYTE_C],
        &LaaPid41data[DEM_OBD_RDY_BYTE_D]
      );
    #else
    LaaPid41data[DEM_OBD_RDY_BYTE_C] = (LaaPid41data[DEM_OBD_RDY_BYTE_C] & ~DEM_OBD_RDY_BYTEC_3_SPARK_SUPPORTED_ENABLED_SECAIR);
    #endif

    /*  As per ISO 0 is set to 0 */
    LaaPid41data[DEM_OBD_RDY_BYTE_C] = (LaaPid41data[DEM_OBD_RDY_BYTE_C] & ~DEM_OBD_RDY_BYTEC_4_SUPPORTED_ENABLED_RESERVED);
    /* As per ISO 0 is set to 0 */
    LaaPid41data[DEM_OBD_RDY_BYTE_D] = (LaaPid41data[DEM_OBD_RDY_BYTE_D] & ~DEM_OBD_RDY_BYTED_4_COMPLETENESS_READINESS_RESERVED);

    /* Check Oxygen sensor monitoring is supported or not */
    #if ((DEM_PID01_BYTEC_SPARK & DEM_OBD_RDY_BYTEC_5_SPARK_SUPPORTED_ENABLED_O2SENS) == \
                                  DEM_OBD_RDY_BYTEC_5_SPARK_SUPPORTED_ENABLED_O2SENS)  
    Dem_CalcPID41PerGroupCheck(
        DEM_OBD_RDY_DISABLE_O2SENS,
        DEM_OBD_RDY_O2SENS,
        DEM_OBD_RDY_BYTEC_5_SPARK_SUPPORTED_ENABLED_O2SENS,
        DEM_OBD_RDY_BYTED_5_SPARK_COMPLETENESS_READINESS_O2SENS,
        &LaaPid41data[DEM_OBD_RDY_BYTE_C],
        &LaaPid41data[DEM_OBD_RDY_BYTE_D]
      );
    #else
    LaaPid41data[DEM_OBD_RDY_BYTE_C] = (LaaPid41data[DEM_OBD_RDY_BYTE_C] & ~DEM_OBD_RDY_BYTEC_5_SPARK_SUPPORTED_ENABLED_O2SENS);
    #endif

    /* Check Oxygen sensor heater monitoring is supported or not */
    #if ((DEM_PID01_BYTEC_SPARK & DEM_OBD_RDY_BYTEC_6_SPARK_SUPPORTED_ENABLED_O2SENSHT) == \
                                  DEM_OBD_RDY_BYTEC_6_SPARK_SUPPORTED_ENABLED_O2SENSHT)  
    Dem_CalcPID41PerGroupCheck(
        DEM_OBD_RDY_DISABLE_O2SENSHT,
        DEM_OBD_RDY_O2SENSHT,
        DEM_OBD_RDY_BYTEC_6_SPARK_SUPPORTED_ENABLED_O2SENSHT,
        DEM_OBD_RDY_BYTED_6_SPARK_COMPLETENESS_READINESS_O2SENSHT,
        &LaaPid41data[DEM_OBD_RDY_BYTE_C],
        &LaaPid41data[DEM_OBD_RDY_BYTE_D]
      );
    #else
    LaaPid41data[DEM_OBD_RDY_BYTE_C] = (LaaPid41data[DEM_OBD_RDY_BYTE_C] & ~DEM_OBD_RDY_BYTEC_6_SPARK_SUPPORTED_ENABLED_O2SENSHT);
    #endif

    /* Check EGR system monitoring is supported or not */
    #if ((DEM_PID01_BYTEC_SPARK & DEM_OBD_RDY_BYTEC_7_SPARK_SUPPORTED_ENABLED_EGR) == \
                                  DEM_OBD_RDY_BYTEC_7_SPARK_SUPPORTED_ENABLED_EGR)  
    Dem_CalcPID41PerGroupCheck(
        DEM_OBD_RDY_DISABLE_EGR,
        DEM_OBD_RDY_EGR,
        DEM_OBD_RDY_BYTEC_7_SPARK_SUPPORTED_ENABLED_EGR,
        DEM_OBD_RDY_BYTED_7_SPARK_COMPLETENESS_READINESS_EGR,
        &LaaPid41data[DEM_OBD_RDY_BYTE_C],
        &LaaPid41data[DEM_OBD_RDY_BYTE_D]
      );
    #else
    LaaPid41data[DEM_OBD_RDY_BYTE_C] = (LaaPid41data[DEM_OBD_RDY_BYTE_C] & ~DEM_OBD_RDY_BYTEC_7_SPARK_SUPPORTED_ENABLED_EGR); 
    #endif

    #else /* Spark Ignition End */
    /* For Compression engines*/

    /* Check NMHC Catalyst monitoring is supported or not */
    #if ((DEM_PID01_BYTEC_COMPRESSION & DEM_OBD_RDY_BYTEC_0_COMPRESSION_SUPPORTED_ENABLED_HCCAT) == \
                                  DEM_OBD_RDY_BYTEC_0_COMPRESSION_SUPPORTED_ENABLED_HCCAT)
    Dem_CalcPID41PerGroupCheck(
        DEM_OBD_RDY_DISABLE_HCCAT,
        DEM_OBD_RDY_HCCAT,
        DEM_OBD_RDY_BYTEC_0_COMPRESSION_SUPPORTED_ENABLED_HCCAT,
        DEM_OBD_RDY_BYTED_0_SPARK_COMPLETENESS_READINESS_CAT,
        &LaaPid41data[DEM_OBD_RDY_BYTE_C],
        &LaaPid41data[DEM_OBD_RDY_BYTE_D]
      );
    #else
    LaaPid41data[DEM_OBD_RDY_BYTE_C] = (LaaPid41data[DEM_OBD_RDY_BYTE_C] & ~DEM_OBD_RDY_BYTEC_0_COMPRESSION_SUPPORTED_ENABLED_HCCAT);    
    #endif

    /* Check NOx aftertreatment monitoring is supported or not */
    #if ((DEM_PID01_BYTEC_COMPRESSION & DEM_OBD_RDY_BYTEC_1_COMPRESSION_SUPPORTED_ENABLED_NOXCAT) == \
                                  DEM_OBD_RDY_BYTEC_1_COMPRESSION_SUPPORTED_ENABLED_NOXCAT)
    Dem_CalcPID41PerGroupCheck(
        DEM_OBD_RDY_DISABLE_NOXCAT,
        DEM_OBD_RDY_NOXCAT,
        DEM_OBD_RDY_BYTEC_1_COMPRESSION_SUPPORTED_ENABLED_NOXCAT,
        DEM_OBD_RDY_BYTED_1_COMPRESSION_COMPLETENESS_READINESS_NOXCAT,
        &LaaPid41data[DEM_OBD_RDY_BYTE_C],
        &LaaPid41data[DEM_OBD_RDY_BYTE_D]
      );
    #else
    LaaPid41data[DEM_OBD_RDY_BYTE_C] = (LaaPid41data[DEM_OBD_RDY_BYTE_C] & ~DEM_OBD_RDY_BYTEC_1_COMPRESSION_SUPPORTED_ENABLED_NOXCAT);
    #endif

    /* Check Boost pressure system monitoring is supported or not */
    #if ((DEM_PID01_BYTEC_COMPRESSION & DEM_OBD_RDY_BYTEC_3_COMPRESSION_SUPPORTED_ENABLED_BOOSTPR) == \
                                  DEM_OBD_RDY_BYTEC_3_COMPRESSION_SUPPORTED_ENABLED_BOOSTPR)
    Dem_CalcPID41PerGroupCheck(
        DEM_OBD_RDY_DISABLE_BOOSTPR,
        DEM_OBD_RDY_BOOSTPR,
        DEM_OBD_RDY_BYTEC_3_COMPRESSION_SUPPORTED_ENABLED_BOOSTPR,
        DEM_OBD_RDY_BYTED_3_COMPRESSION_COMPLETENESS_READINESS_BOOSTPR,
        &LaaPid41data[DEM_OBD_RDY_BYTE_C],
        &LaaPid41data[DEM_OBD_RDY_BYTE_D]
      );
    #else
    LaaPid41data[DEM_OBD_RDY_BYTE_C] = (LaaPid41data[DEM_OBD_RDY_BYTE_C] & ~DEM_OBD_RDY_BYTEC_3_COMPRESSION_SUPPORTED_ENABLED_BOOSTPR);
    #endif

    /*  As per ISO 0 is set to 0 */
    LaaPid41data[DEM_OBD_RDY_BYTE_C] = (LaaPid41data[DEM_OBD_RDY_BYTE_C] & ~DEM_OBD_RDY_BYTEC_4_SUPPORTED_ENABLED_RESERVED);
    /* As per ISO 0 is set to 0 */
    LaaPid41data[DEM_OBD_RDY_BYTE_D] = (LaaPid41data[DEM_OBD_RDY_BYTE_D] & ~DEM_OBD_RDY_BYTED_4_COMPLETENESS_READINESS_RESERVED);

    /* Check Exhaust gas sensor monitoring is supported or not */
    #if ((DEM_PID01_BYTEC_COMPRESSION & DEM_OBD_RDY_BYTEC_5_COMPRESSION_SUPPORTED_ENABLED_EGSENS) == \
                                  DEM_OBD_RDY_BYTEC_5_COMPRESSION_SUPPORTED_ENABLED_EGSENS)
    Dem_CalcPID41PerGroupCheck(
        DEM_OBD_RDY_DISABLE_EGSENS,
        DEM_OBD_RDY_EGSENS,
        DEM_OBD_RDY_BYTEC_5_COMPRESSION_SUPPORTED_ENABLED_EGSENS,
        DEM_OBD_RDY_BYTED_5_COMPRESSION_COMPLETENESS_READINESS_EGSENS,
        &LaaPid41data[DEM_OBD_RDY_BYTE_C],
        &LaaPid41data[DEM_OBD_RDY_BYTE_D]
      );
    #else
    LaaPid41data[DEM_OBD_RDY_BYTE_C] = (LaaPid41data[DEM_OBD_RDY_BYTE_C] & ~DEM_OBD_RDY_BYTEC_5_COMPRESSION_SUPPORTED_ENABLED_EGSENS);
    #endif

    /* Check PM filter monitoring is supported or not */
    #if ((DEM_PID01_BYTEC_COMPRESSION & DEM_OBD_RDY_BYTEC_6_COMPRESSION_SUPPORTED_ENABLED_PMFLT) == \
                                  DEM_OBD_RDY_BYTEC_6_COMPRESSION_SUPPORTED_ENABLED_PMFLT)
    Dem_CalcPID41PerGroupCheck(
        DEM_OBD_RDY_DISABLE_PMFLT,
        DEM_OBD_RDY_PMFLT,
        DEM_OBD_RDY_BYTEC_6_COMPRESSION_SUPPORTED_ENABLED_PMFLT,
        DEM_OBD_RDY_BYTED_6_COMPRESSION_COMPLETENESS_READINESS_PMFLT,
        &LaaPid41data[DEM_OBD_RDY_BYTE_C],
        &LaaPid41data[DEM_OBD_RDY_BYTE_D]
      );
    #else
    LaaPid41data[DEM_OBD_RDY_BYTE_C] = (LaaPid41data[DEM_OBD_RDY_BYTE_C] & ~DEM_OBD_RDY_BYTEC_6_COMPRESSION_SUPPORTED_ENABLED_PMFLT);
    #endif

    #if ((DEM_PID01_BYTEC_COMPRESSION & DEM_OBD_RDY_BYTEC_7_SPARK_SUPPORTED_ENABLED_EGR) == \
                                  DEM_OBD_RDY_BYTEC_7_SPARK_SUPPORTED_ENABLED_EGR)
    Dem_CalcPID41PerGroupCheck(
        DEM_OBD_RDY_DISABLE_EGR,
        DEM_OBD_RDY_EGR,
        DEM_OBD_RDY_BYTEC_7_SPARK_SUPPORTED_ENABLED_EGR,
        DEM_OBD_RDY_BYTED_7_SPARK_COMPLETENESS_READINESS_EGR,
        &LaaPid41data[DEM_OBD_RDY_BYTE_C],
        &LaaPid41data[DEM_OBD_RDY_BYTE_D]
      );
    #else
    LaaPid41data[DEM_OBD_RDY_BYTE_C] = (LaaPid41data[DEM_OBD_RDY_BYTE_C] & ~DEM_OBD_RDY_BYTEC_7_SPARK_SUPPORTED_ENABLED_EGR);
    #endif 
    /* Compression Ignition End */
    #endif /* ((DEM_PID01_BYTEB_LOWER_NIBBLE & DEM_OBD_RDY_BYTEB_3_COMPRESSION_SPARK_IGNITION) == DEM_ZERO) */

    /* Initialise  the count value to zero */
    LucByteCount = DEM_ZERO;

    /* Loop for giving the data */
      /* @Trace: Dem_SUD_API_12621 */
    while (LucByteCount < DEM_FOUR)
    {
      /* @Trace: Dem_SUD_API_12620 */
      /* Output data into destination buffer */
      *LpPID41Value = LaaPid41data[LucByteCount];
        /*
        *  MISRA Rule        : 17.4
        * Message           : Increment or decrement operation
        *                     performed on pointer.
        * Reason            : Increment operator is used to achieve
        *                     better throughput.
        * Verification      : However, part of the code is verified
        *                     manually and it is not having any impact.
        */
        LpPID41Value++;

      LucByteCount++;
    }
  }/* Det check */
  return(LddReturnValue);
}
#endif
/*******************************************************************************
** Function Name        : Dem_DcmReadDataOfPID4D                              **
**                                                                            **
** Service ID           : 0x68                                                **
**                                                                            **
** Description          : Service to report the value of PID  4D for Dem      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : PID4Dvalue                                          **
**                                                                            **
** Return parameter     : Std_Returntype                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        Dem_GulTimeSinceMilOn                               **
**                        Function(s) invoked :                               **
**                        Det_ReportError                                     **
*******************************************************************************/
/* Check if DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT */
/* @Trace: Dem_SUD_MACRO_141 */
#if (DEM_OBD_SUPPORT == DEM_OBD_MASTER_ECU)
FUNC(Std_ReturnType, DEM_CODE) Dem_DcmReadDataOfPID4D(
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA) PID4DValue)
{
  /* @Trace: SWS_Dem_00704
   * Only the Master ECU is allowed to report information for PID
   * $31 / $4D / $4E to the scan tool.
   * */
  /* @Trace: SWS_Dem_00293
   * For the following PIDs the data layout shall be compliant to SAE J1979DA
   * [18].
   * - PID $41 monitor status this driving cycle (4 byte)
   * - PID $01 monitor status since DTCs cleared (4 byte)
   * - PID $02 DTC that caused required freeze frame storage (2 byte)
   * - PID $1C OBD requirements to which vehicle or engine is certified (1 byte)
   * - PID $21 distance traveled while MIL is activated (2 byte)
   * - PID $30 number of warm-ups (WUC) since DTCs cleared (1 byte)
   * - PID $31 distance traveled since DTCs cleared (2 byte)
   * - PID $41 monitor status this driving cycle (4 byte)
   * - PID $4D engine run time while MIL is activated (2 byte)
   * - PID $4E engine run time since DTCs cleared (2 byte)
   * - PID $91 ECU OBD System Information (5 byte)
   */
  VAR(Std_ReturnType, DEM_VAR) LddReturnValue = E_OK;

  /* Module Initialization check */
  if (DEM_INIT != Dem_GucInit)
  {
    /* @Trace: Dem_SUD_API_12630 */
   /* Error report to DET */
    DEM_REPORT_ERROR(DEM_DCMREADDATAOFPID4D_SID, DEM_E_UNINIT);
  }
  else if (NULL_PTR == PID4DValue)
  {
    /* @Trace: Dem_SUD_API_12631 */
    /* Report to DET */
    DEM_REPORT_ERROR(DEM_DCMREADDATAOFPID4D_SID, DEM_E_PARAM_POINTER);
  }
  else
  {
    /* @Trace: Dem_SUD_API_12632 */
    /* @Trace: SWS_Dem_00703
     * The Dem of the Master ECU shall calculate information for
     * PID $31 / $4D / $4E vehicle wide.
     * */
    /*size is 16bit)*/
    P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA) LpPID4DValue = PID4DValue;
    *LpPID4DValue = (uint8)(Dem_DataOfPID4D & 0x00FFU);
    LpPID4DValue++;
    *LpPID4DValue = (uint8)((Dem_DataOfPID4D & 0xFF00U) >> DEM_EIGHT);
  }
  return(LddReturnValue);
}
#endif
/*******************************************************************************
** Function Name        : Dem_DcmReadDataOfPID4E                              **
**                                                                            **
** Service ID           : 0x69                                                **
**                                                                            **
** Description          : Service to report the value of PID  4E for Dem      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : PID4Dvalue                                          **
**                                                                            **
** Return parameter     : Std_Returntype                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        Dem_GulDemClearTimeCount                            **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Det_ReportError                                     **
**                        SchM_Exit_Dem_CAPTURE_OBD_DATA                      **
*******************************************************************************/
/* Check if DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT */
/* @Trace: Dem_SUD_MACRO_143 */
#if (DEM_OBD_SUPPORT == DEM_OBD_MASTER_ECU)
FUNC(Std_ReturnType, DEM_CODE) Dem_DcmReadDataOfPID4E(
 P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA) PID4EValue)
{
  /* @Trace: SWS_Dem_00704
   * Only the Master ECU is allowed to report information for PID
   * $31 / $4D / $4E to the scan tool.
   * */
  /* @Trace: SWS_Dem_00293
   * For the following PIDs the data layout shall be compliant to SAE J1979DA
   * [18].
   * - PID $41 monitor status this driving cycle (4 byte)
   * - PID $01 monitor status since DTCs cleared (4 byte)
   * - PID $02 DTC that caused required freeze frame storage (2 byte)
   * - PID $1C OBD requirements to which vehicle or engine is certified (1 byte)
   * - PID $21 distance traveled while MIL is activated (2 byte)
   * - PID $30 number of warm-ups (WUC) since DTCs cleared (1 byte)
   * - PID $31 distance traveled since DTCs cleared (2 byte)
   * - PID $41 monitor status this driving cycle (4 byte)
   * - PID $4D engine run time while MIL is activated (2 byte)
   * - PID $4E engine run time since DTCs cleared (2 byte)
   * - PID $91 ECU OBD System Information (5 byte)
   */
  VAR(Std_ReturnType, DEM_VAR) LddReturnValue = E_OK;

  /* Module Initialization check */
  if (DEM_INIT != Dem_GucInit)
  {
    /* @Trace: Dem_SUD_API_12633 */
    /* Error report to DET */
    DEM_REPORT_ERROR(DEM_DCMREADDATAOFPID4E_SID, DEM_E_UNINIT);
  }
  else if (NULL_PTR == PID4EValue)
  {
    /* @Trace: Dem_SUD_API_12634 */
    /* Report to DET */
    DEM_REPORT_ERROR(DEM_DCMREADDATAOFPID4E_SID, DEM_E_PARAM_POINTER);
  }
  else
  {
    /* @Trace: Dem_SUD_API_12635 */
    /* @Trace: SWS_Dem_00703
     * The Dem of the Master ECU shall calculate information for
     * PID $31 / $4D / $4E vehicle wide.
     * */
    /*size is 16bit)*/
    P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA) LpPID4EValue = PID4EValue;
    *LpPID4EValue = (uint8)(Dem_DataOfPID4E & 0x00FFU);
    LpPID4EValue++;
    *LpPID4EValue = (uint8)((Dem_DataOfPID4E & 0xFF00U) >> DEM_EIGHT);
  }
  return(LddReturnValue);
}
#endif

/*******************************************************************************
** Function Name        : Dem_DcmReadDataOfPID1C                              **
**                                                                            **
** Service ID           : 0x63                                                **
**                                                                            **
** Description          : Service to report the value of PID  1C for Dem      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : PID1Cvalue                                          **
**                                                                            **
** Return parameter     : Std_Returntype                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        Dem_GulPid1CValue                                   **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Det_ReportError                                     **
**                        SchM_Exit_Dem_CAPTURE_OBD_DATA                      **
*******************************************************************************/
/* @Trace: SRS_Diag_04141 SRS_Diag_04082
 */
/* Check if DEM_OBD2_SUPPORT != DEM_OBD_NO_OBD_SUPPORT */
/* @Trace: Dem_SUD_MACRO_147 */
#if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
FUNC(Std_ReturnType, DEM_CODE) Dem_DcmReadDataOfPID1C(
 P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA) PID1CValue)
{
  /* @Trace: SWS_Dem_00293
   * For the following PIDs the data layout shall be compliant to SAE J1979DA
   * [18].
   * - PID $41 monitor status this driving cycle (4 byte)
   * - PID $01 monitor status since DTCs cleared (4 byte)
   * - PID $02 DTC that caused required freeze frame storage (2 byte)
   * - PID $1C OBD requirements to which vehicle or engine is certified (1 byte)
   * - PID $21 distance traveled while MIL is activated (2 byte)
   * - PID $30 number of warm-ups (WUC) since DTCs cleared (1 byte)
   * - PID $31 distance traveled since DTCs cleared (2 byte)
   * - PID $41 monitor status this driving cycle (4 byte)
   * - PID $4D engine run time while MIL is activated (2 byte)
   * - PID $4E engine run time since DTCs cleared (2 byte)
   * - PID $91 ECU OBD System Information (5 byte)
   */
  VAR(Std_ReturnType, DEM_VAR) LddReturnValue = E_OK;

  /* Module Initialization check */
  if (DEM_INIT != Dem_GucInit)
  {
    /* @Trace: Dem_SUD_API_12604 */
     /* Error report to DET */
    DEM_REPORT_ERROR(DEM_DCMREADDATAOFPID1C_SID, DEM_E_UNINIT);
  }
  else if (NULL_PTR == PID1CValue)
  {
    /* @Trace: Dem_SUD_API_12605 */
    /* Report to DET */
    DEM_REPORT_ERROR(DEM_DCMREADDATAOFPID1C_SID, DEM_E_PARAM_POINTER);
  }
  else
  {
    /* @Trace: Dem_SUD_API_12606 */
    /* @Trace: SWS_Dem_00748
     * The function Dem_DcmReadDataOfPID1C shall return the appropriate
     * value OBD requirements to which vehicle or engine is certified.
     * according to the respective standards [12], e.g. OBD, OBDII, JOBD etc.
     * The value PID1Cvalue to return is in configuration parameter
     * DemOBDCompliancy defined.*/

    /* update the pid1cvalue with OBD compliance */
    /* @Trace: Dem_SUD_MACRO_042 */
    *PID1CValue = DEM_OBD_COMPLIANCE;
  }
  return(LddReturnValue);
}
#endif

/*******************************************************************************
** Function Name        : Dem_DcmReadDataOfPID91                              **
**                                                                            **
** Service ID           : 0x6a                                                **
**                                                                            **
** Description          : Service to report the value of PID  1C for Dem      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : PID91value                                          **
**                                                                            **
** Return parameter     : Std_Returntype                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        Dem_GulPid1CValue                                   **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Det_ReportError                                     **
**                        SchM_Exit_Dem_CAPTURE_OBD_DATA                      **
*******************************************************************************/
/* @Trace: Dem_SUD_MACRO_149 */
#if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
FUNC(Std_ReturnType, DEM_CODE)Dem_DcmReadDataOfPID91(
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA) PID91value)
{
  /* @Trace: SWS_Dem_00293
   * For the following PIDs the data layout shall be compliant to SAE J1979DA
   * [18].
   * - PID $41 monitor status this driving cycle (4 byte)
   * - PID $01 monitor status since DTCs cleared (4 byte)
   * - PID $02 DTC that caused required freeze frame storage (2 byte)
   * - PID $1C OBD requirements to which vehicle or engine is certified (1 byte)
   * - PID $21 distance traveled while MIL is activated (2 byte)
   * - PID $30 number of warm-ups (WUC) since DTCs cleared (1 byte)
   * - PID $31 distance traveled since DTCs cleared (2 byte)
   * - PID $41 monitor status this driving cycle (4 byte)
   * - PID $4D engine run time while MIL is activated (2 byte)
   * - PID $4E engine run time since DTCs cleared (2 byte)
   * - PID $91 ECU OBD System Information (5 byte)
   */
  VAR(Std_ReturnType, DEM_VAR) LddReturnValue = E_OK;

  /* Module Initialization check */
  if (DEM_INIT != Dem_GucInit)
  {
    /* @Trace: Dem_SUD_API_12636 */
     /* Error report to DET */
    DEM_REPORT_ERROR(DEM_DCMREADDATAOFPID91_SID, DEM_E_UNINIT);
  }
  else if (NULL_PTR == PID91value)
  {
    /* @Trace: Dem_SUD_API_12637 */
    /* Report to DET */
    DEM_REPORT_ERROR(DEM_DCMREADDATAOFPID91_SID, DEM_E_PARAM_POINTER);
  }
  else
  {
    /* Format 91:
     * Byte 0
     * 0-3 ==> Calculated
     *     0000: Activation Mode 1
     *     0001: Activation Mode 2
     *     0010: Activation Mode 3
     *     0011: Activation Mode 4
     * 4-7 ==> Reserved
     * Byte 1
     * 0-7 ==> Calculated
     *         High byte of Continuous MI Counter (1h/bit)
     * Byte 2
     * 0-7 ==> Calculated
     *         Low byte of Continuous MI Counter (1h/bit)
     * Byte 3
     * 0-7 ==> Calculated
     *         High byte of highest ECU B1 counter (1h/bit)
     * Byte 4
     * 0-7 ==> Calculated
     *         Low byte of highest ECU B1 counter (1h/bit)
     * */
    P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA) LpPID91Value = PID91value;
    /* @Trace: Dem_SUD_API_12638 */
    for (uint8 LucIdx = DEM_ZERO; LucIdx <= DEM_FOUR; LucIdx++)
    {
      if (DEM_ZERO == LucIdx)
      {
        /* @Trace: Dem_SUD_API_12639 */
       /* Reset all bit to 0 */
       *LpPID91Value = DEM_ZERO;
       /* Set Activation Mode */
       *LpPID91Value = Dem_WWHOBDActMode;
      }
      else if (DEM_ONE == LucIdx)
      {
        /* @Trace: Dem_SUD_API_12640 */
       /* Reset all bit to 0 */
       *LpPID91Value = DEM_ZERO;
       /* High byte of Continuous MI Counter (1h/bit) */
       *LpPID91Value = (uint8)((Dem_WWHOBDConMICont & 0xFF00U) >> DEM_EIGHT);
      }
      else if (DEM_TWO == LucIdx)
      {
        /* @Trace: Dem_SUD_API_12641 */
       /* Reset all bit to 0 */
       *LpPID91Value = DEM_ZERO;
       /* Low byte of Continuous MI Counter (1h/bit) */
       *LpPID91Value = (uint8)(Dem_WWHOBDConMICont & 0x00FFU);
      }
      else if (DEM_THREE == LucIdx)
      {
        /* @Trace: Dem_SUD_API_12642 */
       /* Reset all bit to 0 */
       *LpPID91Value = DEM_ZERO;
       /* High byte of highest ECU B1 counter (1h/bit) */
       *LpPID91Value = (uint8)((Dem_WWHOBDB1Counter & 0xFF00U) >> DEM_EIGHT);
      }
      else
      {
        /* @Trace: Dem_SUD_API_12643 */
       /* Reset all bit to 0 */
       *LpPID91Value = DEM_ZERO;
       /* High byte of highest ECU B1 counter (1h/bit) */
       *LpPID91Value = (uint8)(Dem_WWHOBDB1Counter & 0x00FFU);
      }
      LpPID91Value++;
    }
  }
  return(LddReturnValue);
}
#endif


/*******************************************************************************
** Function Name        : Dem_ReadDataOfTimeEngineStart                       **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Service to report the value of time since engine    **
**                        starts for Dem                                      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : PIDValue                                            **
**                                                                            **
** Return parameter     : Std_Returntype                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        Dem_GulPid1CValue                                   **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Det_ReportError                                     **
*******************************************************************************/
/* @Trace: Dem_SUD_MACRO_152 */
#if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
FUNC(Std_ReturnType, DEM_CODE) Dem_ReadDataOfTimeEngineStart(
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA) PIDValue)
{
  VAR(Std_ReturnType, DEM_VAR) LddReturnValue = E_OK;

  /* Module Initialization check */
  if (DEM_INIT != Dem_GucInit)
  {
    /* @Trace: Dem_SUD_API_10728 */
   /* Error report to DET */
    DEM_REPORT_ERROR(DEM_DCMREADDATAOFPID31_SID, DEM_E_UNINIT);
  }
  else if (NULL_PTR == PIDValue)
  {
    /* @Trace: Dem_SUD_API_10729 */
    /* Report to DET */
    DEM_REPORT_ERROR(DEM_DCMREADDATAOFPID31_SID, DEM_E_PARAM_POINTER);
  }
  else
  {
    /* MISRA Rule : 10.1
     * Message : Implicit conversion from unsigned long to double.
     * Reason : The result will never be greater than unsigned long
     * Verification : However, part of the code is verified
     * manually and it is not having any impact.
     */
    P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA) LpPIDValue = PIDValue;
    P2CONST(Dem_DataElementClassType, AUTOMATIC, DEM_CONST)
     LddElementClass = Dem_GstGeneralOBDInfo->pOBDTimeSinceEngineStart;
    /* @Trace: Dem_SUD_API_11758 */
    /* polyspace-begin MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] Same as Dead Code. */
    /* polyspace-begin DEFECT:DEAD_CODE [Justified:Low] */
    if (NULL_PTR != LddElementClass)
    {
      if (NULL_PTR != LddElementClass->ReadFunc)
      {
        /* @Trace: Dem_SUD_API_11759 */
        LddElementClass->ReadFunc(LpPIDValue, DEM_ZERO);

      }
      else if (NULL_PTR != LddElementClass->SRReadFunc)
      {
        LddElementClass->SRReadFunc(LpPIDValue);
      }
      else
      {
        /* @Trace: Dem_SUD_API_10730 */
        /* Km with DTC clear is set to zero if speed is not found  */
        *LpPIDValue = (uint8)DEM_ZERO;

        /*
         * MISRA Rule        : 17.4
         * Message           : Increment or decrement operation performed
         *                     on pointer.
         * Reason            : Increment operator is used to achieve better
         *                     throughput.
         * Verification      : However, part of the code is verified manually
                              and it is not having any impact
         */
        LpPIDValue++;

        /* Km with DTC clear is set to zero if speed is not found  */
        *LpPIDValue = (uint8)DEM_ZERO;
      }
    }
    /* polyspace-end MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] Same as Dead Code. */
    /* polyspace-end DEFECT:DEAD_CODE [Justified:Low] */
  }
  return(LddReturnValue);
}
#endif

/*******************************************************************************
** Function Name        : Dem_ObdGetSizeOfPID                                 **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : This function shall be used to get size of Pid      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : PID                                                 **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : Size Of PID                                         **
**                                                                            **
** Return parameter     : Size of PID                                         **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        Dem_GulEventIdDisabled                              **
**                                                                            **
**                        Function(s) invoked :                               **
*******************************************************************************/
/* @Trace: Dem_SUD_MACRO_153 */
#if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
static FUNC(uint8, DEM_CODE) Dem_ObdGetSizeOfPID(
  VAR(uint8, DEM_VAR) PID,
  VAR(uint8, DEM_VAR) DataElementIndexOfPID)
{
  VAR(uint8, DEM_VAR) LucSize = DEM_ZERO;
  /* @Trace: Dem_SUD_API_11761 */
  #if (DEM_MAX_NUMBER_OF_PID_RECDS > DEM_ZERO)
  for (uint8 LucIdx = DEM_ZERO; LucIdx < DEM_MAX_NUMBER_OF_PID_RECDS; LucIdx++)
  {
    /* @Trace: Dem_SUD_API_10727 */
    if ((PID == Dem_GaaPid[LucIdx].PidIdentifier) &&
        (DataElementIndexOfPID < Dem_GaaPid[LucIdx].NumOfPidDataElements))
    {
      /* @Trace: Dem_SUD_API_11760 */
      CONSTP2CONST(Dem_DataElementClassType, AUTOMATIC, DEM_CONST)
      ListOfDataElementPtr =
          &Dem_DataElementClass
            [Dem_ListOfDataElementClassIndex
               [Dem_GaaPid[LucIdx].PointToDataElementMap]];
      LucSize = ListOfDataElementPtr[DataElementIndexOfPID].size;
    }
  }
  #endif

  return LucSize;
}
#endif

/*******************************************************************************
** Function Name        : Dem_DcmReadDataOfOBDFreezeFrame                     **
**                                                                            **
** Service ID           : 0x52                                                **
**                                                                            **
** Description          : This function shall be used to copy a specific      **
**                        FreezeFrame selected via the associated PID number  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : PID                   - This parameter is an        **
**                                                identifier for a PID as     **
**                                                defined in ISO15031-5.      **
**                        DataElementIndexOfPID - Data element index of this  **
**                                                PID according to the Dcm    **
**                                                configuration of service    **
**                                                $02. It is zero-based and   **
**                                                consecutive, and ordered by **
**                                                the data element positions  **
**                                                (configured in Dcm, refer   **
**                                                to SWS_Dem_00597).          **
**                                                                            **
** InOut parameter      : DestBuffer            - This parameter contains a   **
**                                                byte pointer that points to **
**                                                the buffer, to which the    **
**                                                data element of the PID     **
**                                                shall be written to. The    **
**                                                format is raw hexadecimal   **
**                                                values and contains no      **
**                                                header-information.         **
**                        BufSize               - When the function is called **
**                                                this parameter contains the **
**                                                maximum number of data      **
**                                                bytes that can be written   **
**                                                to the buffer.              **
**                                                                            **
** Output Parameters    : uint8 *DestBuffer,                                  **
**                                                                            **
** Return parameter     : Std_Returntype                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        Dem_GulEventIdDisabled                              **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Det_ReportError                                     **
*******************************************************************************/
/* @Trace: SRS_Diag_04220
 */
#if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
FUNC(Std_ReturnType, DEM_CODE)
    Dem_DcmReadDataOfOBDFreezeFrame(
    VAR(uint8, DEM_VAR) PID,
    VAR(uint8, DEM_VAR) DataElementIndexOfPID,
    P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA)DestBuffer,
    P2VAR(uint16, AUTOMATIC, DEM_APPL_DATA)BufSize)
{
  /* @Trace: SWS_Dem_00596
   * The Dem module shall provide access on PID data elements of the most
   * important freeze frame being selected for the output of service $02
   * (OBD freeze frame of the event which caused MIL on) to the Dcm module
   * (refer to Dem_DcmReadDataOfOBDFreezeFrame).*/

  /* @Trace: SWS_Dem_00597
   * The index values (refer to API parameter DataElementIndexOfPID)
   * of Dem_DcmReadDataOfOBDFreezeFrame shall be assigned zerobased and
   * consecutive. Their order shall be derived from the position of the data
   * elements (refer to DcmDspPidDataPos, of the referencing DcmDspPidData
   * containers) in the Dcm�s PID layout.
   */
  /* @Trace: Dem_SUD_API_12655 */
  VAR(Std_ReturnType, DEM_VAR) LddRetVal = E_NOT_OK;
  Std_ReturnType LddResult  = E_NOT_OK;
  P2VAR(Dem_EventMemoryEntryType, AUTOMATIC, DEM_APPL_DATA) LddEntry = NULL_PTR;
  /* Module Initialization check */
  if (DEM_INIT != Dem_GucInit)
  {
    /* @Trace: Dem_SUD_API_12644 */
    DEM_REPORT_ERROR(DEM_DCMREADDATAOFOBDFREEZEFRAME_SID, DEM_E_UNINIT);
    /* @retVal = E_NOT_OK;*/
  }
  else if ((NULL_PTR == DestBuffer) ||
          (NULL_PTR == BufSize))
  {
    /* @Trace: Dem_SUD_API_12648 */
    DEM_REPORT_ERROR(DEM_DCMREADDATAOFOBDFREEZEFRAME_SID, DEM_E_PARAM_POINTER);
    /* @retVal = E_NOT_OK;*/
  }
  /* @Trace: Dem_SUD_API_12649 */
  #if (DEM_MAX_NUMBER_OF_PID_DATAELEMENT > DEM_ZERO)
  else if (DataElementIndexOfPID > DEM_MAX_NUMBER_OF_PID_DATAELEMENT)
  {
    /* @Trace: Dem_SUD_API_12650 */
    DEM_REPORT_ERROR(DEM_DCMREADDATAOFOBDFREEZEFRAME_SID, DEM_E_PARAM_CONFIG);
    /* @retVal = E_NOT_OK;*/
  }
  #endif
  else
  {
    /* @Trace: Dem_SUD_MACRO_076 */
    #if (DEM_MAX_NUMBER_OF_PID_RECDS == DEM_ZERO)
    /* @Trace: Dem_SUD_API_12651 */
    DEM_REPORT_ERROR(DEM_DCMREADDATAOFOBDFREEZEFRAME_SID, DEM_E_PARAM_CONFIG);
    /* @retVal = E_NOT_OK;*/
    #else
    /* @Trace: Dem_SUD_API_10727 */
    /* @Trace: SWS_Dem_00291
     * The Dem module shall support only the legislative freeze frame
     * (record number 0). This will be a single list of PIDs assigned
     * to this freeze frame (refer to DemPidClass).*/
    uint16 LusSize = DEM_ZERO;
    /* @Trace: Dem_SUD_API_12652 */
    /* Get the Primary memory address */
    /* @IF_REQ:  DO NOT ACCESS VARIABLE, USE FUNCTION */
    if ((DEM_NO_EVMEM_ENTRY != Dem_ObdMemoryId) &&
        (DEM_MAX_NUMBER_EVENT_ENTRY_PRI > Dem_ObdMemoryId))
    {
      /* @Trace: Dem_SUD_API_12653 */
      LddEntry = &Dem_PrimaryEventMemory[Dem_ObdMemoryId];
    }


    /* Get size of Data Element in PID*/
    /* @size = Dem_GetSizeOfOBDFreezeFrameData(event);*/
    LusSize = Dem_ObdGetSizeOfPID(PID, DataElementIndexOfPID);

    if (*BufSize < LusSize)
    {  
      /* @Trace: Dem_SUD_API_00135 */
      DEM_REPORT_ERROR(DEM_DCMREADDATAOFOBDFREEZEFRAME_SID, DEM_E_PARAM_LENGTH);
      LddRetVal = E_NOT_OK;
    }
    else if ( NULL_PTR == LddEntry)
    {
      /* @Trace: Dem_SUD_API_12654 */
      *BufSize = LusSize;
      LddRetVal = E_NOT_OK;
    }
    /* @Trace: SWS_Dem_01101
     * A suppressed DTC shall not be visible for the following Dcm query-
     * functions; therefore the following functions shall treat the DTC as if
     * filter is not matching: Dem_DcmReadDataOfOBDFreezeFrame
     * */
    else if ((boolean)DEM_TRUE ==
               Dem_EvIsProcStateTriggered(
                   LddEntry->EventIdRef, DEM_EVPROCSTATE_DTC_SUPP))
    {
      /* @Trace: Dem_SUD_API_12645 */
      *BufSize = LusSize;
      LddRetVal = E_NOT_OK;
    }
    else
    {
      /* @IF_REQ : FIND OBD EVENT ENTRY !!! */

      /* @IF_REQ: DTC Format should be verified by 
      Dem_VerifyRecordNumberOfFreezeFrame in future */
      LddResult = Dem_GetReadDataOfPID(LddEntry, DestBuffer,
                          DEM_FALSE, PID, 
                          DEM_FALSE, DataElementIndexOfPID);
      /* @Trace: Dem_SUD_API_12646 */
      if (E_OK == LddResult)
      {
        /* @Trace: Dem_SUD_API_12647 */
        *BufSize = LusSize;
        LddRetVal = E_OK;
      }
    } 
    #endif
  }
  return LddRetVal;
}
#endif
/*******************************************************************************
** Function Name        : Dem_RepIUMPRFaultDetect                             **
**                                                                            **
** Service ID           : 0x73                                                **
**                                                                            **
** Description          : Service for reporting that faults are possibly found**
**                        because all conditions are fulfilled.               **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : RatioID                                             **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_Returntype                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        Dem_GucInit                                         **
**                        Dem_GaaRatioIdInfo                                  **
**                        Dem_Event                                           **
**                        Dem_GaaIumprNumerator                               **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Det_ReportError                                     **
*******************************************************************************/
/* @Trace: SRS_Diag_04126
 */
#if ((DEM_NUMBER_OF_RATIO_INFO > DEM_ZERO) && \
     (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT))
FUNC(Std_ReturnType, DEM_CODE) Dem_RepIUMPRFaultDetect(
    VAR(Dem_RatioIdType, DEM_VAR) RatioID )
{
  /* @Trace: SWS_Dem_00360
   * For OBD relevant systems the Dem module shall provide the API
   * Dem_RepIUMPRFaultDetect.
   * */
  VAR(Std_ReturnType, DEM_VAR) LddReturnValue = E_NOT_OK;
  VAR(uint8, DEM_VAR) LucIumprGroupId;
  VAR(boolean, DEM_VAR) LblDirty = DEM_FALSE;
  VAR(boolean, DEM_VAR) LblPermission;

  /* Module Initialization check */
  if (DEM_INIT != Dem_GucInit)
  {
    /* @Trace: Dem_SUD_API_12857 */
    /* Report to DET */
    DEM_REPORT_ERROR(DEM_REPIUMPRFAULTDETECT_SID, DEM_E_UNINIT);
  }
  else if (RatioID >= DEM_NUMBER_OF_RATIO_INFO)
  {
    /* @Trace: Dem_SUD_API_12859 */
    /* Report to DET */
    DEM_REPORT_ERROR(DEM_REPIUMPRFAULTDETECT_SID, DEM_E_PARAM_CONFIG);
  }
  #if (DEM_AVAILABILITY_SUPPORT == DEM_EVENT_AVAILABILITY)
  else if ( DEM_TRUE != Dem_EvIsProcStateTriggered(
      Dem_GaaRatioIdInfo[RatioID].rid_EventId, DEM_EVPROCSTATE_EVENT_AVAILABLE))
  {
    /* @Trace: Dem_SUD_API_12860 */
    /* @Trace: SWS_Dem_01108
     * If an event is set to unavailable, the corresponding event shall
     * be treated as if it is not configured in the system (e.g.
     * Dem_SetEventStatus and Dem_GetEventUdsStatus shall return E_NOT_OK). */

    /* @LddReturnValue = E_NOT_OK; */
  }
  #endif
  else
  {
    /* @Trace: SWS_Dem_00296
     * The Dem module shall provide the API Dem_RepIUMPRFaultDetect for the
     * asymmetric monitor to report that a malfunction could have been found.
     * */
    /* @Trace: Dem_SUD_API_12861 */
    /* polyspace +1 MISRA-C3:14.3 [Justified:Low] Justify with annotations */
    if (DEM_RATIO_API == Dem_GaaRatioIdInfo[RatioID].ucRatioIdType)
    {
      LblPermission = DEM_FALSE;
      Dem_GetFimPermission(RatioID, &LblPermission);
      /* @Trace: Dem_SUD_MACRO_056 */
      #if (DEM_FIM_INTEGRATED == STD_ON)
      /* @Trace: Dem_SUD_API_12862 */
      if (LblPermission == DEM_TRUE)
      #endif
      {     
        Dem_UdsStatusByteType LddEventStatusMask = DEM_ZERO;
        Dem_OperationCycleStateType LddCycleState =
            (Dem_OperationCycleStateType)DEM_CYCLE_STATE_NOTSTART;
        
        LddEventStatusMask =
            Dem_AllEventStatusByte[Dem_GaaRatioIdInfo[RatioID].rid_EventId];
        (void)Dem_GetOpCycleStateByEvent(
            Dem_GaaRatioIdInfo[RatioID].rid_EventId, &LddCycleState);

        /* @Trace: Dem_SUD_API_12863 */
        if ((LddCycleState == DEM_CYCLE_STATE_START) &&
           ((LddEventStatusMask & (Dem_UdsStatusByteType)DEM_UDS_STATUS_PDTC) !=
               (Dem_UdsStatusByteType)DEM_UDS_STATUS_PDTC))
        {
          /* Get the group id for a particular ratioid */
          LucIumprGroupId = Dem_GaaRatioIdInfo[RatioID].ucIUMPRGroup;
          /* @Trace: Dem_SUD_API_12865 */
          if (Dem_GaaIumprNumeratorIsCounted[RatioID] == DEM_FALSE)    
          {
            /*In IUMPR, if either the numerator or denominator for a specific
            *component reaches the maximum value of 65535, both numbers shall
            *be divided by two before either is incremented again to avoid
            *overflow problems
            */
            /* @Trace: Dem_SUD_API_12864 */          
            if (Dem_GaaIumprNumerator[RatioID] ==
                DEM_MAX_DENOMINATOR_NUMERATOR_VALUE)
            {
              Dem_DivideIumprRatioValue(RatioID);
            }         

            /* Increment the numerator for the requested group */
            /* @Trace: SWS_Dem_01188
            * The Dem shall increment the ratio-individual IUMPR-
            * numerator at maximum of one time per OBD driving cycle.*/
            /* @Trace: Dem_SUD_API_10725 */
            /* @Trace: Dem_SUD_API_11769 */
            Dem_GaaIumprNumerator[RatioID]++;
            Dem_GaaIumprNumeratorIsCounted[RatioID] = DEM_TRUE;   
            Dem_CalCulateMinimumRatioPerGroup(LucIumprGroupId);        

            #if (DEM_J1979_2_OBD_ON_UDS == STD_ON)
            /* Trace: DEM_19792_06_06 */
            /* Increment Flag Logic */
            if (( DEM_IS_BIT_UNSET_MONITOR_ACTIVITY(Dem_GaaMonitorActivityNumeratorNeedCountedCycleEnd[RatioID], 
                                                    DEM_MONITOR_ACTIVITY_NUM_INHIBIT)  )   &&  
                ( DEM_IS_BIT_UNSET_MONITOR_ACTIVITY(Dem_GaaMonitorActivityNumeratorNeedCountedCycleEnd[RatioID], 
                                                    DEM_MONITOR_ACTIVITY_NUM_INCREMENT)  ))  
            {
              DEM_SET_MONITOR_ACTIVITYBYTE(Dem_GaaMonitorActivityNumeratorNeedCountedCycleEnd[RatioID],
                                              DEM_MONITOR_ACTIVITY_NUM_INCREMENT);     
            }
            #endif /* (DEM_J1979_2_OBD_ON_UDS == STD_ON) */

            SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();
            Dem_EventStatusNvRamData.IumprNumerator[RatioID] =
                Dem_GaaIumprNumerator[RatioID];
            Dem_EventStatusNvRamData.IumprDenominator[RatioID] =
                Dem_GaaIumprDenominator[RatioID];
            SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();

            if (LucIumprGroupId < DEM_IUMPR_NONE)
            {
              SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();
              Dem_EventStatusNvRamData.IumprMinimumRatioIDPerGroup[LucIumprGroupId] =
                  Dem_GaaIumprMinimumRatioIDPerGroup[LucIumprGroupId];        
              Dem_EventStatusNvRamData.IumprUpdateFlagPerGroup[LucIumprGroupId] =
                  Dem_GaaIumprUpdateFlagPerGroup[LucIumprGroupId];
               SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();
            }

            LblDirty = DEM_TRUE;
            /* Set return value as true */
            LddReturnValue = E_OK;
          }
        }
      }
    }

  }/* Det check */
  /* @Trace: Dem_SUD_API_12866 */
  if (LblDirty == DEM_TRUE)
  {
    /* @Trace: Dem_SUD_API_12858 */
    Dem_EvMem_SetNonVolatieDataStatus(
        DEM_NVDATA_ALL_EVENT_STATUS_ID, DEM_EVMEM_STATUS_DIRTY_NVM);
    Dem_EvMem_TriggerWriteAllBlocks(); 
  }
  
  return(LddReturnValue);
}
#endif

/*******************************************************************************
** Function Name        : Dem_RepIUMPRDenRelease                              **
**                                                                            **
** Service ID           : 0x72                                                **
**                                                                            **
** Description          : This Service is used to release a denominator of a  **
**                        specific monitor                                    **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : RatioID                                             **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_Returntype                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        Dem_GucInit                                         **
**                       Dem_GulEventIdDisabled                               **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Det_ReportError                                     **
*******************************************************************************/
/* @Trace: SRS_Diag_04126
 */
#if ((DEM_NUMBER_OF_RATIO_INFO > DEM_ZERO) && \
     (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT))
FUNC(Std_ReturnType, DEM_CODE) Dem_RepIUMPRDenRelease(
  VAR(Dem_RatioIdType, DEM_VAR) RatioID)
{

  /* @Trace: SWS_Dem_00308
   * The Dem shall provide the API Dem_RepIUMPRDenRelease to IUMPRrelevant
   * SW-C, to control the denominator specific to the respective RatioId.
   * */
  VAR(Std_ReturnType, DEM_VAR) LddReturnValue = E_NOT_OK;

  /* Module Initialization check */
  if (DEM_INIT != Dem_GucInit)
  {
    /* @Trace: Dem_SUD_API_12876 */
    /* Report to DET */
    DEM_REPORT_ERROR(DEM_REPIUMPRDENRELEASE_SID, DEM_E_UNINIT);
  }
  else if (RatioID >= DEM_NUMBER_OF_RATIO_INFO)
  {
    /* @Trace: Dem_SUD_API_12877 */
    /* Report to DET */
    DEM_REPORT_ERROR(DEM_REPIUMPRDENRELEASE_SID, DEM_E_PARAM_CONFIG);
  }
  #if (DEM_AVAILABILITY_SUPPORT == DEM_EVENT_AVAILABILITY)
  else if (DEM_TRUE !=
             Dem_EvIsProcStateTriggered(
                 Dem_GaaRatioIdInfo[RatioID].rid_EventId,
                 DEM_EVPROCSTATE_EVENT_AVAILABLE))
  {
    /* @Trace: Dem_SUD_API_12881 */
    /* @Trace: SWS_Dem_01108
     * If an event is set to unavailable, the corresponding event shall
     * be treated as if it is not configured in the system (e.g.
     * Dem_SetEventStatus and Dem_GetEventUdsStatus shall return E_NOT_OK). */

    /* @LddReturnValue = E_NOT_OK; */
  }
  #endif
  else
  {
    /* @Trace: Dem_SUD_API_12879
     * The Dem module shall provide the APIs for releasing (refer to
     * Dem_RepIUMPRDenRelease) the denominator under special conditions
     * if the DemIUMPRDenGroup is configured as DEM_IUMPR_DEN_PHYS_API.*/
    /* @Trace: Dem_SUD_API_12858 */
    /* polyspace-begin MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] Same as Dead Code. */
    /* polyspace-begin DEFECT:DEAD_CODE [Justified:Low] Dead Code by Configuration. */
    if (Dem_GaaRatioIdInfo[RatioID].ucIUMPRDenGroup == DEM_IUMPR_DEN_PHYS_API)
    {
      /* @Trace: Dem_SUD_API_12880 */
      /* Release the ratioid */
      /* Trace: DEM_OBD_09_11 */
      Dem_GusRatioDenCondState[DEM_IUMPR_DEN_PHYS_API] = DEM_IUMPR_DEN_STATUS_REACHED;

      LddReturnValue = E_OK;
    }
    /* polyspace-end MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] Same as Dead Code. */
    /* polyspace-end DEFECT:DEAD_CODE [Justified:Low] */
  }/* Det check */
  return(LddReturnValue);
}
#endif

/*******************************************************************************
** Function Name        : Dem_SetIUMPRDenCondition                            **
**                                                                            **
** Service ID           : 0xae                                                **
**                                                                            **
** Description          : This Service is used to set condition of denominator**
**                                                                            **
** Sync/Async           : Synchronous /Asynchronous                           **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : ConditionID                                         **
**                        ConditionStatus                                     **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_Returntype                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        Dem_GucInit                                         **
**                       Dem_GulEventIdDisabled                               **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Det_ReportError                                     **
*******************************************************************************/
#if ((DEM_NUMBER_OF_RATIO_INFO > DEM_ZERO) && \
     (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT))
FUNC(Std_ReturnType, DEM_CODE) Dem_SetIUMPRDenCondition(
    VAR(Dem_IumprDenomCondIdType, DEM_VAR) ConditionId,
    VAR(Dem_IumprDenomCondStatusType, DEM_VAR) CondidtionStatus
   )
{
  /* @Trace: SWS_Dem_00714
   * The Dem shall provide an API Dem_SetIUMPRDenCondition to get informed about
   * the IUMPR-Cycle Flag status by a software component.
   * */
  /* @Trace: SWS_Dem_00717
   * The Dem shall provide the API Dem_SetIUMPRDenCondition to set the status of
   * a particular condition (mainly in depending ECUs).
   * */
  VAR(Std_ReturnType, DEM_VAR) LddReturnValue = E_NOT_OK;

  /* Module Initialization check */
  if (DEM_INIT != Dem_GucInit)
  {
    /* @Trace: Dem_SUD_API_12867 */
    /* Report to DET */
    DEM_REPORT_ERROR(DEM_SETIUMPRDENCONDITION_SID, DEM_E_UNINIT);
  }
  else if (ConditionId > DEM_IUMPR_MAX_CONDITION_NUMBER)
  {
    /* @Trace: Dem_SUD_API_12868 */
    /* Report to DET */
    DEM_REPORT_ERROR(DEM_SETIUMPRDENCONDITION_SID, DEM_E_PARAM_CONFIG);
  }
  else if ((DEM_IUMPR_DEN_STATUS_NOT_REACHED != CondidtionStatus) &&
           (DEM_IUMPR_DEN_STATUS_REACHED     != CondidtionStatus) &&
           (DEM_IUMPR_DEN_STATUS_INHIBITED   != CondidtionStatus))
  {
    /* @Trace: Dem_SUD_API_12869 */
    DEM_REPORT_ERROR(DEM_SETIUMPRDENCONDITION_SID, DEM_E_PARAM_CONFIG);
  }
  else
  {
    /* @Trace: Dem_SUD_API_12871 */
    if (ConditionId < DEM_IUMPR_MAX_CONDITION_NUMBER)
    {
      /* @Trace: Dem_SUD_API_12870 */
      /* Lock the ratioid */
      Dem_GusRatioDenCondState[ConditionId] = CondidtionStatus;
      LddReturnValue = E_OK;
    }

  }/* Det check */
  return(LddReturnValue);

}
#endif

/*******************************************************************************
** Function Name        : Dem_GetIUMPRDenCondition                            **
**                                                                            **
** Service ID           : 0xaf                                                **
**                                                                            **
** Description          : This Service is used to get condition of denominator**
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : ConditionID                                         **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : ConditionStatus                                     **
**                                                                            **
** Return parameter     : Std_Returntype                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        Dem_GucInit                                         **
**                       Dem_GulEventIdDisabled                               **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Det_ReportError                                     **
*******************************************************************************/
/* @Trace: SRS_Diag_04001
 */
#if ((DEM_NUMBER_OF_RATIO_INFO > DEM_ZERO) && \
     (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT))
FUNC(Std_ReturnType, DEM_CODE) Dem_GetIUMPRDenCondition(
  VAR(Dem_IumprDenomCondIdType, DEM_VAR) ConditionId,
  P2VAR(Dem_IumprDenomCondStatusType, AUTOMATIC, DEM_VAR) CondidtionStatus)
{
  /* @Trace: SWS_Dem_00966
   * The Dem shall provide an API Dem_GetIUMPRDenCondition to give a software
   * component the possibility to get the General Denominator status information.
   * */
  /* @Trace: SWS_Dem_00716
   * The Dem shall provide the API Dem_GetIUMPRDenCondition
   * to read out the status of a particular condition.
   * */
  VAR(Std_ReturnType, DEM_VAR) LddReturnValue = E_NOT_OK;

  if (DEM_INIT != Dem_GucInit)
  {
    /* @Trace: Dem_SUD_API_12872 */
    DEM_REPORT_ERROR(DEM_GETIUMPRDENCONDITION_SID, DEM_E_UNINIT);
  }
  else if (ConditionId >= DEM_IUMPR_MAX_CONDITION_NUMBER)
  {
    /* @Trace: Dem_SUD_API_12873 */
    DEM_REPORT_ERROR(DEM_GETIUMPRDENCONDITION_SID, DEM_E_PARAM_CONFIG);
  }
  else if (NULL_PTR == CondidtionStatus)
  {
    /* @Trace: Dem_SUD_API_12874 */
    DEM_REPORT_ERROR(DEM_GETIUMPRDENCONDITION_SID, DEM_E_PARAM_CONFIG);
  }
  else
  {
    /* @Trace: Dem_SUD_API_12875 */
    *CondidtionStatus = Dem_GusRatioDenCondState[ConditionId];
    LddReturnValue = E_OK;
  }
  return LddReturnValue;
}
#endif

/*******************************************************************************
** Function Name        : Dem_DcmGetInfoTypeValue08                           **
**                                                                            **
** Service ID           : 0x6b                                                **
**                                                                            **
** Description          : Service is used for requesting IUMPR data according **
**                        to InfoType $08. This interface is derived from     **
**                        the prototype <Module>_GetInfotypeValueData()       **
**                        defined by the Dcm. Therefore Dcm_OpStatusType      **
**                        and Std_ReturnType are contained. API is needed     **
**                        in OBD-relevant ECUs only.                          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : OpStatus          - Only DCM_INITIAL will appear,   **
**                                            because this API behaves        **
**                                            synchronous.                    **
**                        Iumprdata08Buffer - The maximum number of data      **
**                                            bytes that can be written to    **
**                                            the Iumprdata08 Buffer.         **
**                        Iumprdata08       - Buffer containing the number    **
**                                            of data elements (as defined in **
**                                            ISO-15031-5) and contents of    **
**                                            InfoType $08. The buffer is     **
**                                            provided by the Dcm             **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        Dem_GucInit                                         **
**                        Dem_GaaIumprDenominator                             **
**                        Dem_GusGeneralDenominator                           **
**                        Dem_GusIgnitionCylCnt                               **
**                        Dem_GaaIumprNumerator                               **
**                                                                            **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Det_ReportError                                     **
*******************************************************************************/
/* @Trace: SRS_BSW_00301
 */
/* polyspace +5 MISRA2012:8.13 [Justified:Low] Justify with annotations */
#if ((DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT) && (DEM_NUMBER_OF_RATIO_INFO > 0U))
FUNC(Std_ReturnType, DEM_CODE) Dem_DcmGetInfoTypeValue08(
  VAR(Dcm_OpStatusType, AUTOMATIC) OpStatus,
  P2VAR (uint8, AUTOMATIC, DEM_APPL_DATA) Iumprdata08,
  P2VAR (uint8, AUTOMATIC, DEM_APPL_DATA) Iumprdata08BufferSize
  )
{
  /* @Trace: SWS_Dem_00298
   * In order to support the data requests in service $09 as described above,
   * the Dem shall provide the API Dem_DcmGetInfoTypeValue08 or
   * Dem_DcmGetInfoTypeValue0B to the Dcm.
   * */
  /* @Trace: SWS_Dem_00357
   * If the DemOBDEngineType is set to DEM_IGNITION_SPARK the Dem module shall
   * provide the API Dem_DcmGetInfoTypeValue08 for InfoType $08 IUMPR data.
   * */
  VAR(Std_ReturnType, DEM_VAR) LddReturnValue  = E_OK;
  VAR(uint8, DEM_VAR) LucIndex;

  /* Module Initialization check */
  if (DEM_INIT != Dem_GucInit)
  {
    /* @Trace: Dem_SUD_API_12548 */
    /* Report to DET */
    DEM_REPORT_ERROR( DEM_DCMGETINFOTYPEVALUE08_SID, DEM_E_UNINIT);
  }
  else if (DCM_INITIAL != OpStatus)
  {
    /* @Trace: Dem_SUD_API_12549 */
    /* Report to DET */
    DEM_REPORT_ERROR( DEM_DCMGETINFOTYPEVALUE08_SID, DEM_E_PARAM_CONFIG);
  }
  else if (NULL_PTR == Iumprdata08)
  {
    /* @Trace: Dem_SUD_API_12550 */
    /* Report to DET */
    DEM_REPORT_ERROR( DEM_DCMGETINFOTYPEVALUE08_SID, DEM_E_PARAM_POINTER);
  }
  else if (NULL_PTR == Iumprdata08BufferSize)
  {
    /* @Trace: Dem_SUD_API_12551 */
    /* Report to DET */
    DEM_REPORT_ERROR( DEM_DCMGETINFOTYPEVALUE08_SID, DEM_E_PARAM_POINTER);
  }
  else
  {
    /* @Trace: Dem_SUD_API_12552 */
    LucIndex = DEM_ZERO;

    /* Number of data elements */
    Iumprdata08[LucIndex] = DEM_SIXTEEN;
    LucIndex = LucIndex + DEM_ONE;
    
    /* OBD Monitoring Conditions Encountered Counts */
    Iumprdata08[LucIndex] = (uint8)(Dem_GusGeneralDenominator >> DEM_EIGHT);
    LucIndex = LucIndex + DEM_ONE;
    
    Iumprdata08[LucIndex] = (uint8)Dem_GusGeneralDenominator;
    LucIndex = LucIndex + DEM_ONE;
    
    /* Ignition Cycle Counter */
    Iumprdata08[LucIndex] = (uint8)(Dem_GusIgnitionCylCnt >> DEM_EIGHT);
    LucIndex = LucIndex + DEM_ONE;
    
    Iumprdata08[LucIndex] = (uint8)Dem_GusIgnitionCylCnt;
    LucIndex = LucIndex + DEM_ONE;


    /* Catalyst Monitor Completion Counts Bank 1 (Numerator) */
    Iumprdata08[LucIndex] = (uint8)(Dem_GaaIumprNumerator[Dem_GaaIumprMinimumRatioIDPerGroup[DEM_ONE]] >> DEM_EIGHT);
    LucIndex = LucIndex + DEM_ONE;
    
    Iumprdata08[LucIndex] = (uint8)(Dem_GaaIumprNumerator[Dem_GaaIumprMinimumRatioIDPerGroup[DEM_ONE]]);
    LucIndex = LucIndex + DEM_ONE;
    
    /* Catalyst Monitor Conditions Encountered Counts Bank 1 (Denominator) */
    Iumprdata08[LucIndex] = (uint8)(Dem_GaaIumprDenominator[Dem_GaaIumprMinimumRatioIDPerGroup[DEM_ONE]] >> DEM_EIGHT);
    LucIndex = LucIndex + DEM_ONE;
    
    Iumprdata08[LucIndex] = (uint8)(Dem_GaaIumprDenominator[Dem_GaaIumprMinimumRatioIDPerGroup[DEM_ONE]]);
    LucIndex = LucIndex + DEM_ONE;
    
    /* Catalyst Monitor Completion Counts Bank 2 (Numerator) */
    Iumprdata08[LucIndex] = (uint8)(Dem_GaaIumprNumerator[Dem_GaaIumprMinimumRatioIDPerGroup[DEM_TWO]] >> DEM_EIGHT);
    LucIndex = LucIndex + DEM_ONE;
    
    Iumprdata08[LucIndex] = (uint8)(Dem_GaaIumprNumerator[Dem_GaaIumprMinimumRatioIDPerGroup[DEM_TWO]]);
    LucIndex = LucIndex + DEM_ONE;
    
    /* Catalyst Monitor Conditions Encountered Counts Bank 2 (Denominator) */
    Iumprdata08[LucIndex] = (uint8)(Dem_GaaIumprDenominator[Dem_GaaIumprMinimumRatioIDPerGroup[DEM_TWO]] >> DEM_EIGHT);
    LucIndex = LucIndex + DEM_ONE;
    Iumprdata08[LucIndex] = (uint8)(Dem_GaaIumprDenominator[Dem_GaaIumprMinimumRatioIDPerGroup[DEM_TWO]]);
    LucIndex = LucIndex + DEM_ONE;
    
    
    /* O2 Sensor Monitor Completion Counts Bank 1 (Numerator) */
    Iumprdata08[LucIndex] = (uint8)(Dem_GaaIumprNumerator[Dem_GaaIumprMinimumRatioIDPerGroup[DEM_NINE]] >> DEM_EIGHT);
    LucIndex = LucIndex + DEM_ONE;
    Iumprdata08[LucIndex] = (uint8)(Dem_GaaIumprNumerator[Dem_GaaIumprMinimumRatioIDPerGroup[DEM_NINE]]);
    LucIndex = LucIndex + DEM_ONE;
    
    /* O2 Sensor Monitor Conditions Encountered Counts Bank 1 (Denominator) */
    Iumprdata08[LucIndex] = (uint8)(Dem_GaaIumprDenominator[Dem_GaaIumprMinimumRatioIDPerGroup[DEM_NINE]] >> DEM_EIGHT);
    LucIndex = LucIndex + DEM_ONE;
    Iumprdata08[LucIndex] = (uint8)(Dem_GaaIumprDenominator[Dem_GaaIumprMinimumRatioIDPerGroup[DEM_NINE]]);
    LucIndex = LucIndex + DEM_ONE;
    
    /* O2 Sensor Monitor Completion Counts Bank 2 (Numerator) */
    Iumprdata08[LucIndex] = (uint8)(Dem_GaaIumprNumerator[Dem_GaaIumprMinimumRatioIDPerGroup[DEM_TEN]] >> DEM_EIGHT);
    LucIndex = LucIndex + DEM_ONE;
    Iumprdata08[LucIndex] = (uint8)(Dem_GaaIumprNumerator[Dem_GaaIumprMinimumRatioIDPerGroup[DEM_TEN]]);
    LucIndex = LucIndex + DEM_ONE;
    
    /* O2 Sensor Monitor Conditions Encountered Counts Bank 2 (Denominator) */
    Iumprdata08[LucIndex] = (uint8)(Dem_GaaIumprDenominator[Dem_GaaIumprMinimumRatioIDPerGroup[DEM_TEN]] >> DEM_EIGHT);
    LucIndex = LucIndex + DEM_ONE;
    Iumprdata08[LucIndex] = (uint8)(Dem_GaaIumprDenominator[Dem_GaaIumprMinimumRatioIDPerGroup[DEM_TEN]]);
    LucIndex = LucIndex + DEM_ONE;
    
    
    /* EGR and/or VVT Monitor Completion Counts Bank (Numerator) */
    Iumprdata08[LucIndex] = (uint8)(Dem_GaaIumprNumerator[Dem_GaaIumprMinimumRatioIDPerGroup[DEM_THREE]] >> DEM_EIGHT);
    LucIndex = LucIndex + DEM_ONE;
    Iumprdata08[LucIndex] = (uint8)(Dem_GaaIumprNumerator[Dem_GaaIumprMinimumRatioIDPerGroup[DEM_THREE]]);
    LucIndex = LucIndex + DEM_ONE;
    
    /* EGR and/or VVT Monitor Conditions Encountered Counts Bank (Denominator) */
    Iumprdata08[LucIndex] = (uint8)(Dem_GaaIumprDenominator[Dem_GaaIumprMinimumRatioIDPerGroup[DEM_THREE]] >> DEM_EIGHT);
    LucIndex = LucIndex + DEM_ONE;
    Iumprdata08[LucIndex] = (uint8)(Dem_GaaIumprDenominator[Dem_GaaIumprMinimumRatioIDPerGroup[DEM_THREE]]);
    LucIndex = LucIndex + DEM_ONE;
    
    /* AIR Monitor Completion Counts Bank (Numerator) */
    Iumprdata08[LucIndex] = (uint8)(Dem_GaaIumprNumerator[Dem_GaaIumprMinimumRatioIDPerGroup[DEM_THIRTEEN]] >> DEM_EIGHT);
    LucIndex = LucIndex + DEM_ONE;
    Iumprdata08[LucIndex] = (uint8)(Dem_GaaIumprNumerator[Dem_GaaIumprMinimumRatioIDPerGroup[DEM_THIRTEEN]]);
    LucIndex = LucIndex + DEM_ONE;
    
    /* AIR Monitor Conditions Encountered Counts Bank (Denominator) */
    Iumprdata08[LucIndex] = (uint8)(Dem_GaaIumprDenominator[Dem_GaaIumprMinimumRatioIDPerGroup[DEM_THIRTEEN]] >> DEM_EIGHT);
    LucIndex = LucIndex + DEM_ONE;
    Iumprdata08[LucIndex] = (uint8)(Dem_GaaIumprDenominator[Dem_GaaIumprMinimumRatioIDPerGroup[DEM_THIRTEEN]]);
    LucIndex = LucIndex + DEM_ONE;
    
    
    /* EVAP Monitor Completion Counts Bank (Numerator) */
    Iumprdata08[LucIndex] = (uint8)(Dem_GaaIumprNumerator[Dem_GaaIumprMinimumRatioIDPerGroup[DEM_FIVE]] >> DEM_EIGHT);
    LucIndex = LucIndex + DEM_ONE;
    Iumprdata08[LucIndex] = (uint8)(Dem_GaaIumprNumerator[Dem_GaaIumprMinimumRatioIDPerGroup[DEM_FIVE]]);
    LucIndex = LucIndex + DEM_ONE;
    
    /* EVAP Monitor Conditions Encountered Counts Bank (Denominator) */
    Iumprdata08[LucIndex] = (uint8)(Dem_GaaIumprDenominator[Dem_GaaIumprMinimumRatioIDPerGroup[DEM_FIVE]] >> DEM_EIGHT);
    LucIndex = LucIndex + DEM_ONE;
    Iumprdata08[LucIndex] = (uint8)(Dem_GaaIumprDenominator[Dem_GaaIumprMinimumRatioIDPerGroup[DEM_FIVE]]);
    LucIndex = LucIndex + DEM_ONE;
    
    /* Secondary O2 Sensor Monitor Completion Counts Bank 1 (Numerator) */
    Iumprdata08[LucIndex] = (uint8)(Dem_GaaIumprNumerator[Dem_GaaIumprMinimumRatioIDPerGroup[DEM_FOURTEEN]] >> DEM_EIGHT);
    LucIndex = LucIndex + DEM_ONE;
    Iumprdata08[LucIndex] = (uint8)(Dem_GaaIumprNumerator[Dem_GaaIumprMinimumRatioIDPerGroup[DEM_FOURTEEN]]);
    LucIndex = LucIndex + DEM_ONE;
    
    /* Secondary O2 Sensor Monitor Conditions Encountered Counts Bank 1 (Denominator) */
    Iumprdata08[LucIndex] = (uint8)(Dem_GaaIumprDenominator[Dem_GaaIumprMinimumRatioIDPerGroup[DEM_FOURTEEN]] >> DEM_EIGHT);
    LucIndex = LucIndex + DEM_ONE;
    Iumprdata08[LucIndex] = (uint8)(Dem_GaaIumprDenominator[Dem_GaaIumprMinimumRatioIDPerGroup[DEM_FOURTEEN]]);
    LucIndex = LucIndex + DEM_ONE;
    
    /* Secondary O2 Sensor Monitor Completion Counts Bank 2 (Numerator) */
    Iumprdata08[LucIndex] = (uint8)(Dem_GaaIumprNumerator[Dem_GaaIumprMinimumRatioIDPerGroup[DEM_FIFTEEN]] >> DEM_EIGHT);
    LucIndex = LucIndex + DEM_ONE;
    Iumprdata08[LucIndex] = (uint8)(Dem_GaaIumprNumerator[Dem_GaaIumprMinimumRatioIDPerGroup[DEM_FIFTEEN]]);
    LucIndex = LucIndex + DEM_ONE;
    
    /* Secondary O2 Sensor Monitor Conditions Encountered Counts Bank 2 (Denominator) */
    Iumprdata08[LucIndex] = (uint8)(Dem_GaaIumprDenominator[Dem_GaaIumprMinimumRatioIDPerGroup[DEM_FIFTEEN]] >> DEM_EIGHT);
    LucIndex = LucIndex + DEM_ONE;
    Iumprdata08[LucIndex] = (uint8)(Dem_GaaIumprDenominator[Dem_GaaIumprMinimumRatioIDPerGroup[DEM_FIFTEEN]]);

  }/* Det check */
  return(LddReturnValue);
}
#endif


/*******************************************************************************
** Function Name        : Dem_DcmGetInfoTypeValue0B                           **
**                                                                            **
** Service ID           : 0x6c                                                **
**                                                                            **
** Description          : Service is used for requesting IUMPR data according **
**                        to InfoType $0B. This interface is derived from the **
**                        prototype <Module>_GetInfotypeValueData() defined   **
**                        by the Dcm. Therefore Dcm_OpStatusType and          **
**                        Std_ReturnType are contained. API is needed in      **
**                        OBD-relevant ECUs only.                             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : OpStatus              - Only DCM_INITIAL will       **
**                                                appear, because this API    **
**                                                behaves synchronous.        **
**                        Iumprdata0BBufferSize - The maximum number of data  **
**                                                bytes that can be written   **
**                                                to the Iumprdata0B Buffer.  **
**                        Iumprdata0B           - Buffer containing the       **
**                                                number of data elements (as **
**                                                defined in ISO-15031-5) and **
**                                                contents of InfoType$0B.    **
**                                                The buffer is provided by   **
**                                                the Dcm                     **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
/* @Trace: SRS_BSW_00301
 */
/* polyspace +5 MISRA2012:8.13 [Justified:Low] Justify with annotations */
#if ((DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT) && (DEM_NUMBER_OF_RATIO_INFO > 0U))
FUNC(Std_ReturnType, DEM_CODE) Dem_DcmGetInfoTypeValue0B(
  VAR(Dcm_OpStatusType, AUTOMATIC) OpStatus,
  P2VAR (uint8, AUTOMATIC, DEM_APPL_DATA) Iumprdata0B,
  P2VAR (uint8, AUTOMATIC, DEM_APPL_DATA) Iumprdata0BBufferSize
  )
{
  /* @Trace: SWS_Dem_00298
   * In order to support the data requests in service $09 as described above,
   * the Dem shall provide the API Dem_DcmGetInfoTypeValue08 or
   * Dem_DcmGetInfoTypeValue0B to the Dcm.
   * */
  /* @Trace: SWS_Dem_00358
   * If the DemOBDEngineType is set to DEM_IGNITION_COMPRESSION the Dem module
   * shall provide the API Dem_DcmGetInfoTypeValue0B for Info Type $0B IUMPR
   * data.
   * */
  VAR(Std_ReturnType, DEM_VAR) LddReturnValue = E_OK;
  VAR(uint8, DEM_VAR) LucIndex;

  /* Module Initialization check */
  if (DEM_INIT != Dem_GucInit)
  {
    /* @Trace: Dem_SUD_API_12553 */
    /* Report to DET */
    DEM_REPORT_ERROR( DEM_DCMGETINFOTYPEVALUE0B_SID, DEM_E_UNINIT);
  }
  else if (DCM_INITIAL != OpStatus)
  {
    /* @Trace: Dem_SUD_API_12554 */
    /* Report to DET */
    DEM_REPORT_ERROR( DEM_DCMGETINFOTYPEVALUE0B_SID, DEM_E_PARAM_CONFIG);
  }
  else if (NULL_PTR == Iumprdata0B)
  {
    /* @Trace: Dem_SUD_API_12555 */
    /* Report to DET */
    DEM_REPORT_ERROR( DEM_DCMGETINFOTYPEVALUE0B_SID, DEM_E_PARAM_POINTER);
  }
  else if (NULL_PTR == Iumprdata0BBufferSize)
  {
    /* @Trace: Dem_SUD_API_12556 */
    /* Report to DET */
    DEM_REPORT_ERROR( DEM_DCMGETINFOTYPEVALUE0B_SID, DEM_E_PARAM_POINTER);
  }
  else
  {
    /* @Trace: Dem_SUD_API_12557 */
    LucIndex = DEM_ZERO;

    /* Number of data elements */
    Iumprdata0B[LucIndex] = DEM_SIXTEEN;
    LucIndex = LucIndex + DEM_ONE;
    /* OBD Monitoring Conditions Encountered Counts */
    Iumprdata0B[LucIndex] = (uint8)(Dem_GusGeneralDenominator >> DEM_EIGHT);
    LucIndex = LucIndex + DEM_ONE;
    Iumprdata0B[LucIndex] = (uint8)Dem_GusGeneralDenominator;
    LucIndex = LucIndex + DEM_ONE;
    /* Ignition Cycle Counter */
    Iumprdata0B[LucIndex] = (uint8)(Dem_GusIgnitionCylCnt >> DEM_EIGHT);
    LucIndex = LucIndex + DEM_ONE;
    Iumprdata0B[LucIndex] = (uint8)Dem_GusIgnitionCylCnt;
    LucIndex = LucIndex + DEM_ONE;


    /* NMHC Catalyst Monitor Completion Condition Counts (Numerator) */
    Iumprdata0B[LucIndex] = (uint8)(Dem_GaaIumprNumerator[Dem_GaaIumprMinimumRatioIDPerGroup[DEM_SIX]] >> DEM_EIGHT);
    LucIndex = LucIndex + DEM_ONE;
    Iumprdata0B[LucIndex] = (uint8)(Dem_GaaIumprNumerator[Dem_GaaIumprMinimumRatioIDPerGroup[DEM_SIX]]);
    LucIndex = LucIndex + DEM_ONE;
    /* NMHC Catalyst Monitor Conditions Encountered Counts (Denominator) */
    Iumprdata0B[LucIndex] = (uint8)(Dem_GaaIumprDenominator[Dem_GaaIumprMinimumRatioIDPerGroup[DEM_SIX]] >> DEM_EIGHT);
    LucIndex = LucIndex + DEM_ONE;
    Iumprdata0B[LucIndex] = (uint8)(Dem_GaaIumprDenominator[Dem_GaaIumprMinimumRatioIDPerGroup[DEM_SIX]]);
    LucIndex = LucIndex + DEM_ONE;

    
    /* NOx Catalyst Monitor Completion Condition Counts (Numerator) */
    Iumprdata0B[LucIndex] = (uint8)(Dem_GaaIumprNumerator[Dem_GaaIumprMinimumRatioIDPerGroup[DEM_EIGHT]] >> DEM_EIGHT);
    LucIndex = LucIndex + DEM_ONE;
    Iumprdata0B[LucIndex] = (uint8)(Dem_GaaIumprNumerator[Dem_GaaIumprMinimumRatioIDPerGroup[DEM_EIGHT]]);
    LucIndex = LucIndex + DEM_ONE;
    /* NOx Catalyst Monitor Conditions Encountered Counts (Denominator) */
    Iumprdata0B[LucIndex] = (uint8)(Dem_GaaIumprDenominator[Dem_GaaIumprMinimumRatioIDPerGroup[DEM_EIGHT]] >> DEM_EIGHT);
    LucIndex = LucIndex + DEM_ONE;
    Iumprdata0B[LucIndex] = (uint8)(Dem_GaaIumprDenominator[Dem_GaaIumprMinimumRatioIDPerGroup[DEM_EIGHT]]);
    LucIndex = LucIndex + DEM_ONE;

    
    /* NOx Adsorber Monitor Completion Condition Counts (Numerator) */
    Iumprdata0B[LucIndex] = (uint8)(Dem_GaaIumprNumerator[Dem_GaaIumprMinimumRatioIDPerGroup[DEM_SEVEN]] >> DEM_EIGHT);
    LucIndex = LucIndex + DEM_ONE;
    Iumprdata0B[LucIndex] = (uint8)(Dem_GaaIumprNumerator[Dem_GaaIumprMinimumRatioIDPerGroup[DEM_SEVEN]]);
    LucIndex = LucIndex + DEM_ONE;
    /* NOx Adsorber Monitor Conditions Encountered Counts (Denominator) */
    Iumprdata0B[LucIndex] = (uint8)(Dem_GaaIumprDenominator[Dem_GaaIumprMinimumRatioIDPerGroup[DEM_SEVEN]] >> DEM_EIGHT);
    LucIndex = LucIndex + DEM_ONE;
    Iumprdata0B[LucIndex] = (uint8)(Dem_GaaIumprDenominator[Dem_GaaIumprMinimumRatioIDPerGroup[DEM_SEVEN]]);
    LucIndex = LucIndex + DEM_ONE;

    
    /* PM Filter Monitor Completion Condition Counts (Numerator) */
    Iumprdata0B[LucIndex] = (uint8)(Dem_GaaIumprNumerator[Dem_GaaIumprMinimumRatioIDPerGroup[DEM_ELEVEN]] >> DEM_EIGHT);
    LucIndex = LucIndex + DEM_ONE;
    Iumprdata0B[LucIndex] = (uint8)(Dem_GaaIumprNumerator[Dem_GaaIumprMinimumRatioIDPerGroup[DEM_ELEVEN]]);
    LucIndex = LucIndex + DEM_ONE;
    /* PM Filter Monitor Conditions Encountered Counts (Denominator) */
    Iumprdata0B[LucIndex] = (uint8)(Dem_GaaIumprDenominator[Dem_GaaIumprMinimumRatioIDPerGroup[DEM_ELEVEN]] >> DEM_EIGHT);
    LucIndex = LucIndex + DEM_ONE;
    Iumprdata0B[LucIndex] = (uint8)(Dem_GaaIumprDenominator[Dem_GaaIumprMinimumRatioIDPerGroup[DEM_ELEVEN]]);
    LucIndex = LucIndex + DEM_ONE;
    
    /* Exhaust Gas Sensor Monitor Completion Condition Counts (Numerator) */
    Iumprdata0B[LucIndex] = (uint8)(Dem_GaaIumprNumerator[Dem_GaaIumprMinimumRatioIDPerGroup[DEM_FOUR]] >> DEM_EIGHT);
    LucIndex = LucIndex + DEM_ONE;
    Iumprdata0B[LucIndex] = (uint8)(Dem_GaaIumprNumerator[Dem_GaaIumprMinimumRatioIDPerGroup[DEM_FOUR]]);
    LucIndex = LucIndex + DEM_ONE;
    
    /* Exhaust Gas Sensor Monitor Conditions Encountered Counts (Denominator) */
    Iumprdata0B[LucIndex] = (uint8)(Dem_GaaIumprDenominator[Dem_GaaIumprMinimumRatioIDPerGroup[DEM_FOUR]] >> DEM_EIGHT);
    LucIndex = LucIndex + DEM_ONE;
    Iumprdata0B[LucIndex] = (uint8)(Dem_GaaIumprDenominator[Dem_GaaIumprMinimumRatioIDPerGroup[DEM_FOUR]]);
    LucIndex = LucIndex + DEM_ONE;

    
    /* EGR and/or VVT Monitor Completion Condition Counts (Numerator) */
    Iumprdata0B[LucIndex] = (uint8)(Dem_GaaIumprNumerator[Dem_GaaIumprMinimumRatioIDPerGroup[DEM_THREE]] >> DEM_EIGHT);
    LucIndex = LucIndex + DEM_ONE;
    Iumprdata0B[LucIndex] = (uint8)(Dem_GaaIumprNumerator[Dem_GaaIumprMinimumRatioIDPerGroup[DEM_THREE]]);
    LucIndex = LucIndex + DEM_ONE;
    /* EGR and/or VVT Monitor Conditions Encountered Counts (Denominator) */
    Iumprdata0B[LucIndex] = (uint8)(Dem_GaaIumprDenominator[Dem_GaaIumprMinimumRatioIDPerGroup[DEM_THREE]] >> DEM_EIGHT);
    LucIndex = LucIndex + DEM_ONE;
    Iumprdata0B[LucIndex] = (uint8)(Dem_GaaIumprDenominator[Dem_GaaIumprMinimumRatioIDPerGroup[DEM_THREE]]);
    LucIndex = LucIndex + DEM_ONE;

    
    /* Boost Pressure Monitor Monitor Completion Condition Counts (Numerator) */
    Iumprdata0B[LucIndex] = (uint8)(Dem_GaaIumprNumerator[Dem_GaaIumprMinimumRatioIDPerGroup[DEM_ZERO]] >> DEM_EIGHT);
    LucIndex = LucIndex + DEM_ONE;
    Iumprdata0B[LucIndex] = (uint8)(Dem_GaaIumprNumerator[Dem_GaaIumprMinimumRatioIDPerGroup[DEM_ZERO]]);
    LucIndex = LucIndex + DEM_ONE;
    /* Boost Pressure Monitor Monitor Conditions Encountered Counts (Denominator) */
    Iumprdata0B[LucIndex] = (uint8)(Dem_GaaIumprDenominator[Dem_GaaIumprMinimumRatioIDPerGroup[DEM_ZERO]] >> DEM_EIGHT);
    LucIndex = LucIndex + DEM_ONE;
    Iumprdata0B[LucIndex] = (uint8)(Dem_GaaIumprDenominator[Dem_GaaIumprMinimumRatioIDPerGroup[DEM_ZERO]]);


  }/* Det check */
  return(LddReturnValue);
}
#endif

/*******************************************************************************
** Function Name        : Dem_DcmGetDTCOfOBDFreezeFrame                       **
**                                                                            **
** Service ID           : 0x53                                                **
**                                                                            **
** Description          : Gets DTC by freeze frame record number              **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : FrameNumber                                         **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : uint8 *DTC,                                         **
**                                                                            **
** Return parameter     : Std_Returntype                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : None                          **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Det_ReportError                                     **
*******************************************************************************/
/* @Trace: SRS_Diag_04220 SRS_Diag_04000
 */
#if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
  FUNC(Std_ReturnType, DEM_CODE) Dem_DcmGetDTCOfOBDFreezeFrame(
  uint8 FrameNumber,
  P2VAR(uint32, AUTOMATIC, DEM_APPL_DATA)DTC,
  Dem_DTCFormatType DTCFormat)
{
  /* @Trace: SWS_Dem_00623
   * The function Dem_DcmGetDTCOfOBDFreezeFrame shall return the DTC
   * associated with the most important freeze frame being selected
   * for the output of service $02 (PID $02).*/
  VAR(Std_ReturnType, DEM_VAR) LddReturnValue = E_NOT_OK;
  VAR(uint32, DEM_VAR) LulDTC;

  /* Module Initialization check */
  if (DEM_INIT != Dem_GucInit)
  {
    /* @Trace: Dem_SUD_API_12656 */
    /* Error report to DET */
    DEM_REPORT_ERROR(DEM_DCMGETDTCOFOBDFREEZEFRAME_SID, DEM_E_UNINIT);

    /* Return Value is set to not ok */
    LddReturnValue = E_NOT_OK;
  }
  else if (DTC == NULL_PTR)
  {
    /* @Trace: Dem_SUD_API_12663 */
    /* Report to DET */
   DEM_REPORT_ERROR(DEM_DCMGETDTCOFOBDFREEZEFRAME_SID, DEM_E_PARAM_POINTER);

    /* Return Value is set to not ok */
    LddReturnValue = E_NOT_OK;
  }
  else if ((DTCFormat != DEM_DTC_FORMAT_UDS) &&
           (DTCFormat != DEM_DTC_FORMAT_OBD))
  {
    /* @Trace: Dem_SUD_API_12665 */
    DEM_REPORT_ERROR(DEM_DCMGETDTCOFOBDFREEZEFRAME_SID, DEM_E_PARAM_DATA);
    LddReturnValue = E_NOT_OK;
  }
  else
  {
    /* Check if Freeze Frame number is zero or not*/
    if (DEM_ZERO == FrameNumber)
    {
      LulDTC = DEM_ZERO;
      if (Dem_ObdMemoryId == DEM_NO_EVMEM_ENTRY)
      {
        /* @Trace: Dem_SUD_API_12667 */
        LulDTC = DEM_ZERO;
        LddReturnValue = E_OK;
      }
      else
      {
        P2VAR(Dem_EventMemoryEntryType, AUTOMATIC, DEM_APPL_DATA) LddEntry =
            NULL_PTR;
            /* @Trace: Dem_SUD_API_12657 */
        if (DEM_MAX_NUMBER_EVENT_ENTRY_PRI > Dem_ObdMemoryId)
        {
          /* @Trace: Dem_SUD_API_12669 */
          LddEntry = &Dem_PrimaryEventMemory[Dem_ObdMemoryId];
        }
        /* @Trace: Dem_SUD_API_12658 */
        if (NULL_PTR != LddEntry)
        {
          /* @Trace: Dem_SUD_API_12659 */
          if ((LddEntry->EventIdRef != DEM_NO_EVENT) &&
              (LddEntry->EventIdRef < DEM_NUMBER_OF_EVENTS))
          {
            /* @Trace: SWS_Dem_01101
             * A suppressed DTC shall not be visible for the following Dcm query
             * -functions; therefore the following functions shall treat the DTC
             * as if filter is not matching: Dem_DcmGetDTCOfOBDFreezeFrame
             * */
            if ((boolean)DEM_TRUE ==
                  Dem_EvIsProcStateTriggered(
                      LddEntry->EventIdRef, DEM_EVPROCSTATE_DTC_SUPP))
            {
              /* @Trace: Dem_SUD_API_12661 */
              /* Set the return value */
              LddReturnValue = E_NOT_OK;
            }
            else
            {
              /* @Trace: Dem_SUD_API_12660 */
              (void)Dem_GetEventDTC(
                  &Dem_Event[LddEntry->EventIdRef - DEM_ONE],
                  &LulDTC,
                  DTCFormat); /*DEM_DTC_FORMAT_OBD*/
              LddReturnValue = E_OK;
            }
          }
        }
      }
      /* Most important freeze frame dtc */
      /* *DTC = (LulDTC << DEM_EIGHT) & DEM_THREE_HIGH_BYTE_ENABLE; */
      *DTC = LulDTC;
    }/* Check Freeze frame record number */
    else
    {
      /* @Trace: Dem_SUD_API_00136 */
      /* Error report to DET */
      DEM_REPORT_ERROR(DEM_DCMGETDTCOFOBDFREEZEFRAME_SID, DEM_E_PARAM_CONFIG);
      /* Return Value is set to not ok */
      LddReturnValue = E_NOT_OK;
    }
  }/* Det check */
  return(LddReturnValue);
}
#endif

/*******************************************************************************
** Function Name        : Dem_SetPtoStatus                                    **
**                                                                            **
** Service ID           : 0x79                                                **
**                                                                            **
** Description          : This API is available for support of pid 1E         **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : PtoStatus                                           **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_Returntype                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        Dem_GblPtoStatus                                    **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Det_ReportError                                     **
*******************************************************************************/
#if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
FUNC(Std_ReturnType, DEM_CODE) Dem_SetPtoStatus(boolean PtoStatus)
{
  /* @Trace: SWS_Dem_00377
   * The Dem module shall provide the interface Dem_SetPtoStatus
   * allowing a SWC implementing the PTO functionality to notify
   * the Dem module if PTO is active or inactive.
   * */
  /* @Trace: Dem_SUD_API_12885 */
  VAR(Std_ReturnType, DEM_VAR) LddReturnValue;

  /* Module Initialization check */
  if (DEM_INIT != Dem_GucInit)
  {
    /* @Trace: Dem_SUD_API_12883 */
    /* Error report to DET */
    DEM_REPORT_ERROR(DEM_SETPTOSTATUS_SID, DEM_E_UNINIT);

    /* Return Value is set to not ok */
    LddReturnValue = E_NOT_OK;
  }

  else if ((PtoStatus != DEM_TRUE) && (PtoStatus != DEM_FALSE))
  {
    /* @Trace: Dem_SUD_API_12884 */
   /* Report to DET */
   DEM_REPORT_ERROR(DEM_SETPTOSTATUS_SID, DEM_E_PARAM_CONFIG);

    /* Return Value is set to not ok */
    LddReturnValue = E_NOT_OK;
  }
  else
  {    /* Check new status is same as old status */
    if (PtoStatus !=  Dem_GblPtoStatus)
    {
      /* @Trace: Dem_SUD_API_12886 */
      Dem_GblPtoStatus = PtoStatus;

      LddReturnValue = E_OK;
    }
    else
    {
      /* @Trace: Dem_SUD_API_12887 */
      LddReturnValue = E_NOT_OK;
    }
  }
  return(LddReturnValue);
}
#endif

/*******************************************************************************
 ** Function Name       : Dem_GetFimPermission                                **
 **                                                                           **
 ** Service ID          : None                                                **
 **                                                                           **
 ** Description         : Function is used to get Fim permission              **
 **                                                                           **
 ** Re-entrancy         : Reentrant                                           **
 **                                                                           **
 ** Input Parameters    : RatioIndex                                          **
 **                                                                           **
 ** InOut parameter     : None                                                **
 **                                                                           **
 ** Output Parameters   : permission                                          **
 **                                                                           **
 ** Return parameter    : None                                                **
 **                                                                           **
 ** Preconditions       : None                                                **
 **                                                                           **
 ** Remarks             :                                                     **
 *******************************************************************************/
#if ((DEM_NUMBER_OF_RATIO_INFO > DEM_ZERO) && \
     (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT))
static FUNC(void, DEM_CODE)Dem_GetFimPermission(
    Dem_RatioIdType RatioIndex,
    boolean* permission )
{

  #if ((DEM_FIM_INTEGRATED == STD_ON) && (DEM_MAX_NUMBER_OF_FID_REF > DEM_ZERO))
  Std_ReturnType LddRetCheck;
  FiM_FunctionIdType LucInddexOfFID;
  boolean LblAllGreen = DEM_TRUE;
  
  for (LucInddexOfFID = DEM_ZERO; 
       LucInddexOfFID < Dem_GaaRatioIdInfo[RatioIndex].NumOfPrimaryFid; 
       LucInddexOfFID++)
  {
    /* @Trace: Dem_SUD_API_11762 */
   LddRetCheck = FiM_GetFunctionPermission(
        (FiM_FunctionIdType)Dem_GaaRatioIdInfo[RatioIndex].aaPrimaryFid[LucInddexOfFID],
        permission);

    if ((*permission == DEM_FALSE) || (LddRetCheck == E_NOT_OK))
    {
      /* SWS_Dem_01392
      * The IUMPR ratio shall be blocked whenever any of t Events
      * linked (via FunctionInhibitionConfiguration or through SummaryEvents) to one of the
      * FIDs referenced by DemFunctionIdRef is in state PENDING, or any other event
      * causal to this event (according to component dependency structure) is in state PENDING
      */
      LblAllGreen = DEM_FALSE;
      break;
    }
  }

  if (DEM_FALSE == LblAllGreen)
  {
    *permission = DEM_FALSE;
  }
  else
  {
    *permission = DEM_TRUE;
  }
  #else
  /* @Trace: Dem_SUD_API_11763 */
  DEM_UNUSED(RatioIndex);
  *permission = DEM_TRUE;
  #endif
}
#endif


/*******************************************************************************
 ** Function Name       : Dem_ProcessNum                                      **
 **                                                                           **
 ** Service ID          : None                                                **
 **                                                                           **
 ** Description         : Function is used to get ratio index                 **
 **                                                                           **
 ** Re-entrancy         : Reentrant                                           **
 **                                                                           **
 ** Input Parameters    : EventId, EventStatus                                **
 **                                                                           **
 ** InOut parameter     : None                                                **
 **                                                                           **
 ** Output Parameters   : None                                                **
 **                                                                           **
 ** Return parameter    : None                                                **
 **                                                                           **
 ** Preconditions       : None                                                **
 **                                                                           **
 ** Remarks             :                                                     **
 *******************************************************************************/
/* @Trace: SRS_Diag_04001
 */
#if ((DEM_NUMBER_OF_RATIO_INFO > DEM_ZERO) && \
    (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT))
FUNC(Std_ReturnType, DEM_CODE)Dem_ProcessNum(
    Dem_EventIdType EventId,
    Dem_UdsStatusByteType EventStatus)
{
  VAR(Std_ReturnType, DEM_VAR) LddReturnValue = E_OK;
  VAR(uint16, DEM_VAR) LusNum = DEM_ZERO;
  VAR(uint16, DEM_VAR) LusIndex = DEM_ZERO;
  VAR(boolean, DEM_VAR) LblPermission;
  VAR(boolean, DEM_VAR) LblDirty = DEM_FALSE;
  VAR(uint8, DEM_VAR) LucIumprGroupId;
  VAR(boolean, DEM_VAR) LblIsBit2GetTransit;

  Dem_EventParameterCPCType LddEvent = &Dem_Event[EventId - DEM_ONE];
  LusNum = LddEvent->usRatioIdCount;

  for (LusIndex = DEM_ZERO; LusIndex < LusNum; LusIndex++)
  {
    uint8 LucRatioIndex = DEM_ZERO;

    Dem_GetRatioIndex(LddEvent,LusIndex, &LucRatioIndex);
    /* @Trace: SWS_Dem_00359
     * Only for monitors being configured with the option observer,
     * the Dem module shall increment the numerator of the corresponding
     * monitor, if the assigned event gets tested/qualified
     * (as passed or failed).*/
    /* @Trace: Dem_SUD_API_11766 */
    /* polyspace-begin MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] Same as Dead Code. */
    /* polyspace-begin DEFECT:DEAD_CODE [Justified:Low] */
    if ((Dem_GaaRatioIdInfo[LucRatioIndex].ucRatioIdType == DEM_RATIO_OBSERVER)
        /* @&& (Dem_GusRatioFaultFound[LucRatioIndex] == DEM_FALSE)*/)
    {
      Dem_GetFimPermission(LucRatioIndex, &LblPermission);

      #if (DEM_FIM_INTEGRATED == STD_ON)
      /* @Trace: Dem_SUD_API_11767 */
      if (LblPermission == DEM_TRUE)
      #endif
      { 
        LucIumprGroupId = Dem_GaaRatioIdInfo[LucRatioIndex].ucIUMPRGroup;
        LblIsBit2GetTransit = 
            Dem_EvIsUdsProcStateTriggered(
                EventId, DEM_UDSPROCSTATE_TRANSITION_BIT_2);

        /* @Trace: SWS_Dem_00299
         * As long as an event has Pending status, the Dem module shall
         * stop increasing the numerator and denominator.*/
        /* @Trace: Dem_SUD_API_10726 */
        if ((Dem_GaaIumprNumeratorIsCounted[LucRatioIndex] == DEM_FALSE) &&
           (((EventStatus & (Dem_UdsStatusByteType)DEM_UDS_STATUS_PDTC) !=
             (Dem_UdsStatusByteType)DEM_UDS_STATUS_PDTC) &&
            (DEM_FALSE == LblIsBit2GetTransit)))
        {
          /*In IUMPR, if either the numerator or denominator
            for a specific component reaches the maximum value
              of 65535, both numbers shall be divided by two
            before either is incremented again to avoid overflow
            problems */
            /* @Trace: Dem_SUD_API_11768 */
          if (Dem_GaaIumprNumerator[LucRatioIndex] ==
              DEM_MAX_DENOMINATOR_NUMERATOR_VALUE)
          {
              Dem_DivideIumprRatioValue(LucRatioIndex);
          }

          /* Increment the numerator for the requested group */
          /* @Trace: SWS_Dem_01188
          * The Dem shall increment the ratio-individual IUMPR-
          * numerator at maximum of one time per OBD driving cycle.*/
          /* @Trace: Dem_SUD_API_10725 */
          if (Dem_GaaIumprNumeratorIsCounted[LucRatioIndex] == DEM_FALSE)
          {
            /* @Trace: Dem_SUD_API_11769 */
            Dem_GaaIumprNumerator[LucRatioIndex]++;
            Dem_GaaIumprNumeratorIsCounted[LucRatioIndex] = DEM_TRUE;
            Dem_CalCulateMinimumRatioPerGroup(LucIumprGroupId);         
          }

            #if (DEM_J1979_2_OBD_ON_UDS == STD_ON)
          /* Trace: DEM_19792_06_06 */
          /* Increment Flag Logic */
          if (( DEM_IS_BIT_UNSET_MONITOR_ACTIVITY(Dem_GaaMonitorActivityNumeratorNeedCountedCycleEnd[LucRatioIndex], 
                                                  DEM_MONITOR_ACTIVITY_NUM_INHIBIT)  )   &&  
              ( DEM_IS_BIT_UNSET_MONITOR_ACTIVITY(Dem_GaaMonitorActivityNumeratorNeedCountedCycleEnd[LucRatioIndex], 
                                                  DEM_MONITOR_ACTIVITY_NUM_INCREMENT)  ))  
          {
                DEM_SET_MONITOR_ACTIVITYBYTE(Dem_GaaMonitorActivityNumeratorNeedCountedCycleEnd[LucRatioIndex],
                                            DEM_MONITOR_ACTIVITY_NUM_INCREMENT);     
          }
          #endif /* J19792 */
          
          SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();
          Dem_EventStatusNvRamData.IumprNumerator[LucRatioIndex] =
              Dem_GaaIumprNumerator[LucRatioIndex];
          Dem_EventStatusNvRamData.IumprDenominator[LucRatioIndex] =
              Dem_GaaIumprDenominator[LucRatioIndex];

          #if (DEM_J1979_2_OBD_ON_UDS == STD_ON)
          Dem_EventStatusNvRamData.MonitorActivityNumeratorNeedCountedCycleEnd[LucRatioIndex] = 
              Dem_GaaMonitorActivityNumeratorNeedCountedCycleEnd[LucRatioIndex]; 
          #endif
          SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();

          if (LucIumprGroupId < DEM_IUMPR_NONE)
          {
            SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();
            Dem_EventStatusNvRamData.IumprMinimumRatioIDPerGroup[LucIumprGroupId] =
              Dem_GaaIumprMinimumRatioIDPerGroup[LucIumprGroupId];      
            Dem_EventStatusNvRamData.IumprUpdateFlagPerGroup[LucIumprGroupId] =
              Dem_GaaIumprUpdateFlagPerGroup[LucIumprGroupId];
            SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();
          }

          LblDirty = DEM_TRUE;
        }
      }
    }
    /* polyspace-end MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] Same as Dead Code. */
    /* polyspace-end DEFECT:DEAD_CODE [Justified:Low] */
  }
  /* @Trace: Dem_SUD_API_11764 */
  /* polyspace-begin MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] Same as Dead Code. */
  /* polyspace-begin DEFECT:DEAD_CODE [Justified:Low] */
  if (LblDirty == DEM_TRUE)
  {
    /* @Trace: Dem_SUD_API_11765 */
    Dem_EvMem_SetNonVolatieDataStatus(DEM_NVDATA_ALL_EVENT_STATUS_ID,
        DEM_EVMEM_STATUS_DIRTY_NVM);
    Dem_EvMem_TriggerWriteAllBlocks(); 
  }
  /* polyspace-end MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] Same as Dead Code. */
  /* polyspace-end DEFECT:DEAD_CODE [Justified:Low] */
  
  return LddReturnValue;
}
#endif


/*******************************************************************************
 ** Function Name       : Dem_ProcessDen                                      **
 **                                                                           **
 ** Service ID          : None                                                **
 **                                                                           **
 ** Description         : The function is used for incrementing of denominator**
 **                                                                           **
 ** Sync/Async          : Synchronous                                         **
 **                                                                           **
 ** Re-entrancy         : Reentrant                                           **
 **                                                                           **
 ** Input Parameters    : EventId                                             **
 **                                                                           **
 ** InOut parameter     : None                                                **
 **                                                                           **
 ** Output Parameters   : None                                                **
 **                                                                           **
 ** Return parameter    : void                                                **
 **                                                                           **
 ** Preconditions       : None                                                **
 **                                                                           **
 ** Remarks             : Global Variable(s)  :                               **
 **                       Dem_GaaOperationCycleIdsList, Dem_GaaRatioIdInfo    **
 **                       Dem_Event,Dem_GulEventIdDisabled                    **
 **                       Dem_GaaIumprDenominator, Dem_GaaIumprNumerator      **
 **                       Function(s) invoked :  None                         **
 ******************************************************************************/
/* @Trace: SRS_Diag_04001 SRS_Diag_04126
 */
#if ((DEM_NUMBER_OF_RATIO_INFO > DEM_ZERO) && \
     (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT))
FUNC(void, DEM_CODE) Dem_ProcessDen(
  VAR(Dem_EventIdType, DEM_VAR) EventId)
{
  VAR(uint16, DEM_VAR) LusTotalRatioCount;
  VAR(uint16, DEM_VAR) LusRatioCount;
  VAR(uint8, DEM_VAR) LucIumprGroupId;
  VAR(uint8, DEM_VAR) LucRatioIdIndex;
  VAR(boolean, DEM_VAR) LblPermission;
  VAR(boolean, DEM_VAR) LblDirty = DEM_FALSE;
  VAR(uint8, DEM_VAR) LaaIumprGrp[DEM_SIXTEEN];
  VAR(uint8, DEM_VAR) LucTempGroupCount;
  /* @Trace: Dem_SUD_API_11778 */
  for (LucTempGroupCount = DEM_ZERO; LucTempGroupCount < DEM_SIXTEEN;
      LucTempGroupCount++)
  {
    /* @Trace: Dem_SUD_API_11770 */
    /* Initialise the local variable to false */
    LaaIumprGrp[LucTempGroupCount] = DEM_FALSE;
  }
  /* @Trace: Dem_SUD_API_11779 */
  if (Dem_GblRatioInit == DEM_FALSE)
  {
    /* @Trace: SWS_Dem_00712
     * In master and optionally primary OBD ECUs, the Dem shall increment ECU
     * global internal general denominator depending on the denominator
     * DEM_IUMPR_GENERAL_OBDCOND, if available. Depending on the system
     * definition the global general denominator (and therefore the
     * DEM_IUMPR_GENERAL_OBDCOND) may not be needed in some or even all primary
     * ECUs. In such cases the DEM_IUMPR_GENERAL_OBDCOND is never set, and the
     * general denominator is stuck at 0 (and reporting of the InfoType $08 /
     * $0B is disabled in the Dcm).*/
    /* @Trace: SWS_Dem_00711
     * The Dem of the Master ECU shall calulate the IUMPR-Cycle Flag.*/
    #if ((DEM_OBD_SUPPORT == DEM_OBD_MASTER_ECU) || \
         (DEM_OBD_SUPPORT == DEM_OBD_PRIMARY_ECU))
         /* @Trace: Dem_SUD_API_11782 */
    if ((Dem_GusRatioDenCondState[DEM_IUMPR_GENERAL_OBDCOND] ==
           DEM_IUMPR_DEN_STATUS_REACHED))
    #endif
    {
      /* @Trace: Dem_SUD_API_11783 */
      if (Dem_GusGeneralDenominator < DEM_MAX_DENOMINATOR_NUMERATOR_VALUE)
      {
        /* @Trace: SWS_Dem_01104
         * IUMPR ratios referring to an unavailable event shall neither be
         * computed nor reported.*/
        #if (DEM_AVAILABILITY_SUPPORT == DEM_EVENT_AVAILABILITY)
        /* @Trace: Dem_SUD_API_11784 */
        if (DEM_TRUE ==
              Dem_EvIsProcStateTriggered(
                  EventId, DEM_EVPROCSTATE_EVENT_AVAILABLE))
        #endif
        {
          /* @Trace: Dem_SUD_API_11785 */
          Dem_GusGeneralDenominator++;
          SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();
          Dem_EventStatusNvRamData.GeneralDenCnt = Dem_GusGeneralDenominator;
          SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();
          LblDirty = DEM_TRUE;
        }
      }
      
    }
    Dem_GblRatioInit = DEM_TRUE;
 
  }

  /* Loop for incrementing the denominator */
  /* Store the total ratioid configured for that event */
  LusTotalRatioCount = Dem_Event[EventId-DEM_ONE].usRatioIdCount;

  LusRatioCount = DEM_ZERO;
  while (LusRatioCount < LusTotalRatioCount)
  {
    Dem_UdsStatusByteType LddEventStatusMask = DEM_ZERO;

    LddEventStatusMask = Dem_AllEventStatusByte[EventId];
    Dem_GetRatioIndex(
        &Dem_Event[EventId - DEM_ONE],LusRatioCount,&LucRatioIdIndex);

    LucIumprGroupId = Dem_GaaRatioIdInfo[LucRatioIdIndex].ucIUMPRGroup;

    Dem_GetFimPermission(LucRatioIdIndex, &LblPermission);


    /* @Trace: SWS_Dem_00299
     * As long as an event has Pending status, the Dem module shall
     * stop increasing the numerator and denominator.*/

    /* @Trace: SWS_Dem_01236
     * The Dem shall increment monitor internal denominators depending on
     * the DEM_IUMPR_GENERAL_INDIVIDUAL_DENOMINATOR, and additional conditions
     * if configured in DemIUMPRDenGroup a maximum of once per driving cycle,
     * and shall consider monitor specific conditions only for the cycle the
     * Release operation was called in.*/

    /* @Trace: SWS_Dem_01392
     * The IUMPR ratio shall be blocked whenever any of the Events linked
     * (via FunctionInhibitionConfiguration or through SummaryEvents) to one
     * of the FIDs referenced by DemFunctionIdRef is in state PENDING,
     * or any other event causal to this event (according to component
     * dependency structure) is in state PENDING (see DemComponentClassRef
     * referenced by DemDiagnosticEventRef).*/

    #if (DEM_AVAILABILITY_SUPPORT == DEM_EVENT_AVAILABILITY)
    boolean LblEventAvailable =
        Dem_EvIsProcStateTriggered(EventId, DEM_EVPROCSTATE_EVENT_AVAILABLE);
    #endif
    /* @Trace: Dem_SUD_API_11773 */
    if (((LblPermission == DEM_TRUE)
        #if ((DEM_NUMBER_OF_DEM_COMPONENT > DEM_ZERO) && \
             (DEM_NUMBER_OF_EVENTS > DEM_ZERO ))
        || (DEM_CAUSAL_FAULT != Dem_EvtDepdntStt[EventId - DEM_ONE])
        #endif
        )
        && ((LucIumprGroupId < DEM_IUMPR_NONE) && (LaaIumprGrp[LucIumprGroupId] == DEM_FALSE))
        && (Dem_GusRatioDenCondState[DEM_IUMPR_GENERAL_INDIVIDUAL_DENOMINATOR] ==
              DEM_IUMPR_DEN_STATUS_REACHED)
        /* @&& (Dem_GusRatioIdDisable[LucRatioIdIndex] == DEM_FALSE)*/
        && ((LddEventStatusMask & (Dem_UdsStatusByteType)DEM_UDS_STATUS_PDTC) !=
              (Dem_UdsStatusByteType)DEM_UDS_STATUS_PDTC)

        /* @Trace: SWS_Dem_01104
         * IUMPR ratios referring to an unavailable event shall neither be
         * computed nor reported.*/
        #if (DEM_AVAILABILITY_SUPPORT == DEM_EVENT_AVAILABILITY)
        && (DEM_TRUE == LblEventAvailable)
        #endif
    )
    {
      /* Set the variable */
      LaaIumprGrp[LucIumprGroupId] = DEM_TRUE;
      
      /*In IUMPR, if either the numerator or denominator for a specific
       *component reaches the maximum value of 65535, both numbers shall
       *be divided by two before either is incremented again to avoid
       *overflow problems
       */
      /* @Trace: Dem_SUD_API_11774 */
      if (Dem_GaaIumprDenominator[LucIumprGroupId] ==
          DEM_MAX_DENOMINATOR_NUMERATOR_VALUE)
      {          
        Dem_DivideIumprRatioValue(LucRatioIdIndex);     
      } 

      /* Increment the denominator for the requested group */
      /* @Trace: Dem_SUD_API_11776 */
      if (Dem_GaaIumprDenominatorIsCounted[LucIumprGroupId] == DEM_FALSE)
      {
        /* @Trace: Dem_SUD_API_11777 */
        Dem_GaaIumprDenominator[LucIumprGroupId]++;
        Dem_GaaIumprDenominatorIsCounted[LucIumprGroupId] = DEM_TRUE;
      }
      SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();
      Dem_EventStatusNvRamData.IumprDenominator[LucIumprGroupId] =
          Dem_GaaIumprDenominator[LucIumprGroupId];
      Dem_EventStatusNvRamData.IumprNumerator[LucIumprGroupId] =
          Dem_GaaIumprNumerator[LucIumprGroupId];
      SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();

      LblDirty = DEM_TRUE;

    }
    /* @Trace: Dem_SUD_API_10723 */
    LusRatioCount++;
  }
    /* Loop for incrementing the denominator */
  /* @Trace: Dem_SUD_API_11772 */
  if (LblDirty == DEM_TRUE)
  {
    /* @Trace: Dem_SUD_API_11771 */
    Dem_EvMem_SetNonVolatieDataStatus(
        DEM_NVDATA_ALL_EVENT_STATUS_ID, DEM_EVMEM_STATUS_DIRTY_NVM);
    Dem_EvMem_TriggerWriteAllBlocks(); 
  }

}
#endif


/*******************************************************************************
 ** Function Name       : Dem_CalcPIDValue                                    **
 **                                                                           **
 ** Service ID          : None                                                **
 **                                                                           **
 ** Description         : API to calculate the value of PID Byte              **
 **                                                                           **
 ** Sync/Async          : Synchronous                                         **
 **                                                                           **
 ** Re-entrancy         : Reentrant                                           **
 **                                                                           **
 ** Input Parameters    : LucOBDReadinessGrp                                  **
 **                                                                           **
 ** InOut parameter     : None                                                **
 **                                                                           **
 ** Output Parameters   : PIDValue                                            **
 **                                                                           **
 ** Return parameter    : void                                                **
 **                                                                           **
 ** Preconditions       : None                                                **
 **                                                                           **
 ** Remarks             : Global Variable(s)  :                               **
 **                       Dem_Event                                           **
 **                                                                           **
 **                       Function(s) invoked : None                          **
 *******************************************************************************/
/* @Trace: SRS_Diag_04126
 */
/* Check if DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT */
#if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
/* Trace: DEM_OBD_01_03 */
FUNC(void, DEM_CODE) Dem_CalcReadinessPIDValue(
  VAR(uint8, DEM_VAR) LucPIDType,
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA) PIDValue,
  VAR(uint8, DEM_VAR) LusByteValue,
  VAR(uint8, DEM_VAR) LucOBDReadinessGrp )
{
  /* Initialize the count to zero */
  VAR(Dem_EventIdType, DEM_VAR) LddEventCount = DEM_ZERO;
  /* Trace: DEM_OBD_01_04 */
  VAR(boolean, DEM_VAR) LblNotReadyGrpFlag = DEM_FALSE;
  VAR(boolean, DEM_VAR) LblConfirmedDTCinGrpFlag = DEM_FALSE;

  *PIDValue = (uint8)(*PIDValue & (uint8)(~LusByteValue));

  /* @Trace: SWS_Dem_00354
   * The Dem module shall compute for PID $01 the readiness status
   * (if all events of a DemEventOBDReadinessGroup are reported as
   * OK tested since last clear, or the event has caused MIL on).
   * Suppressed Events (refer to chapter 7.4.8) shall be ignored
   * for this computation.*/
  /* @Trace: SWS_Dem_00355
   * The Dem module shall compute for PID $41 the readiness group
   * complete for current driving cycle (if all events of a group
   * are tested in the current driving cycle). OBD Events Suppression
   * (refer to chapter 7.4.8) shall be ignored for this computation.*/

  /* @Trace: SWS_Dem_01103
   * Unavailable events shall not be considered for computation of service $01
   * PID $41.*/
  /* @Trace: Dem_SUD_API_11786 */
  while (LddEventCount < DEM_NUMBER_OF_EVENTS)
  {
    /* @Trace: Dem_SUD_API_11787 */
    if (Dem_Event[LddEventCount].ulEventOBDReadinessGroup == LucOBDReadinessGrp)
    {
      Dem_EventIdType EventId = LddEventCount + DEM_ONE;
      Dem_UdsStatusByteType LddEventStatusMask = DEM_ZERO;

      LddEventStatusMask = Dem_AllEventStatusByte[EventId];
       /* @Trace: Dem_SUD_API_11788 */
      #if (DEM_AVAILABILITY_SUPPORT == DEM_EVENT_AVAILABILITY)
       /* @Trace: Dem_SUD_API_11790 */
      boolean LblEventAvailable =
          Dem_EvIsProcStateTriggered(EventId, DEM_EVPROCSTATE_EVENT_AVAILABLE);
      #endif
      /* Trace: DEM_OBD_01_04 */ 
      #if (DEM_AVAILABILITY_SUPPORT == DEM_EVENT_AVAILABILITY)
      if (DEM_TRUE == LblEventAvailable)
      #endif 
      {    
        /* @Trace: Dem_SUD_API_11791 */
        if (LucPIDType == DEM_PID01_CALC)
        {
          /* Check if test is failed/Passed Last Clear */
          if ((LddEventStatusMask & DEM_UDS_STATUS_TNCSLC) == DEM_UDS_STATUS_TNCSLC)
          {      
            LblNotReadyGrpFlag = DEM_TRUE; 
          }

          /* Check if Confirmed State */
          if ((LddEventStatusMask & DEM_UDS_STATUS_CDTC) == DEM_UDS_STATUS_CDTC)
          {      
            LblConfirmedDTCinGrpFlag = DEM_TRUE; 
            /* Readiness is Fixed to OK */
            LddEventCount = DEM_NUMBER_OF_EVENTS;
          }          
        }
        /* @Trace: Dem_SUD_API_11789 */
        else 
        {
          if (LucPIDType == DEM_PID41_CALC)
          {
            /* Check Enable State */
            /* not yet developed */
            
            /* Check if test is failed/Passed this operation cycle */
            if ((LddEventStatusMask & DEM_UDS_STATUS_TNCTOC) == DEM_UDS_STATUS_TNCTOC)
            {      
              LblNotReadyGrpFlag = DEM_TRUE; 
              /* Completeness is Fixed to NOT OK */
              LddEventCount = DEM_NUMBER_OF_EVENTS;
            }
          }
        } 
      }
    }/* End the loop */
    /* Increment the count by one */
    LddEventCount++;
  }
  /* Trace: DEM_OBD_01_05 */
  if (LucPIDType == DEM_PID01_CALC)
  {
    /* 1. If Confirmed DTC Exist in Requested Group */
    if (LblConfirmedDTCinGrpFlag == DEM_TRUE)
    {
      /* This group is Ready -> Value is zero in SAE1979) */
      *PIDValue = *PIDValue & (~LusByteValue);      
    }
    else 
    {
      /* If Not Tested Since Last Clear DTC or Confirmed DTC not Exist in Requested Group */
      if (LblNotReadyGrpFlag == DEM_TRUE) 
      {
        /* This group is not Ready -> Value is one in SAE1979 */
        /* @Trace: Dem_SUD_API_11791 */
        *PIDValue = *PIDValue | LusByteValue;      
      }
    }
    
  }
  else if (LucPIDType == DEM_PID41_CALC)
  {    
    /* If Not Tested since This Operation Cycle dtc Exist in Requested Group */
    if (LblNotReadyGrpFlag == DEM_TRUE)
    {
      /* This group is Complete -> Value is zero in SAE1979) */
      /* @Trace: Dem_SUD_API_11791 */
      *PIDValue = *PIDValue | LusByteValue;      
    }
  }
  else
  {
    /* Do Nothing */
  }
}
#endif


/*******************************************************************************
 ** Function Name       : Dem_CalcPID41_34                                    **
 **                                                                           **
 ** Service ID          : None                                                **
 **                                                                           **
 ** Description         : API to calculate the value of PID 41 for Dem        **
 **                                                                           **
 ** Sync/Async          : Synchronous                                         **
 **                                                                           **
 ** Re-entrancy         : Reentrant                                           **
 **                                                                           **
 ** Input Parameters    : None                                                **
 **                                                                           **
 ** InOut parameter     : None                                                **
 **                                                                           **
 ** Output Parameters   : PID41value                                          **
 **                                                                           **
 ** Return parameter    : void                                                **
 **                                                                           **
 ** Preconditions       : None                                                **
 **                                                                           **
 ** Remarks             : Global Variable(s)  :                               **
 **                       Dem_GulEventIdDisabled                              **
 **                                                                           **
 **                       Function(s) invoked :                               **
 **                       Dem_CalcPIDValue                                    **
 *******************************************************************************/
/* Check if DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT */
#if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
FUNC(void, DEM_CODE) Dem_CalcPID41_34(
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA) PID41Value)
{
  VAR(uint32, DEM_VAR) LulEventIdDisabledMask;
  VAR(uint8, DEM_VAR) LaaPid41data[DEM_TWO];
  VAR(uint8, DEM_VAR) LucByteCSpark;
  VAR(uint8, DEM_VAR) LucBitPos;
  VAR(uint8, DEM_VAR) LucReadynessGruoupIndex;

  /*For spark engines*/
  #if ((DEM_PID01_BYTEB_LOWER_NIBBLE & DEM_EIGHT) == DEM_ZERO)
  /* @Trace: Dem_SUD_API_11835 */
  uint8 LaaReadynessGruoup[DEM_SEVEN] = { DEM_OBD_RDY_CAT, DEM_OBD_RDY_HTCAT,
      DEM_OBD_RDY_EVAP, DEM_OBD_RDY_SECAIR, DEM_OBD_RDY_O2SENS,
      DEM_OBD_RDY_O2SENSHT, DEM_OBD_RDY_EGR};

  #else /*For Ignition engines*/
  /* @Trace: Dem_SUD_API_11827 */
  uint8 LaaReadynessGruoup[DEM_SIX] = { DEM_OBD_RDY_HCCAT, DEM_OBD_RDY_NOXCAT,
      DEM_OBD_RDY_BOOSTPR, DEM_OBD_RDY_EGSENS,
      DEM_OBD_RDY_PMFLT, DEM_OBD_RDY_EGR};
  LucByteCSpark = DEM_PID01_BYTEC_COMPRESSION;
  #endif

  #if ((DEM_PID01_BYTEB_LOWER_NIBBLE & DEM_EIGHT) == DEM_ZERO)
  LucByteCSpark = DEM_PID01_BYTEC_SPARK;
  #endif

  LaaPid41data[DEM_ZERO] = *PID41Value;

  /*
   * MISRA Rule       : 17.4
   * Message          : Increment or decrement operation
   *                    performed on pointer.
   * Reason           : Increment operator is used to achieve
   *                    better throughput.
   * Verification     : However, part of the code is verified
   *                    manually and it is not having any impact.
   */

  LaaPid41data[DEM_ONE] = *PID41Value + DEM_ONE;

  LucBitPos = DEM_ONE;

  LucReadynessGruoupIndex = DEM_ZERO;

  /* For spark engines*/
  #if ((DEM_PID01_BYTEB_LOWER_NIBBLE & DEM_EIGHT) == DEM_ZERO)

  LulEventIdDisabledMask = DEM_EIGHT;

  /*
   * MISRA Rule       : 13.2
   * Message          : Testing a value should be made explicit.
   * Reason           : Increment operator is used to achieve
   *                    better throughput.
   * Verification     : However, part of the code is verified
   *                    manually and it is not having any impact.
   */
  /* @Trace: Dem_SUD_API_11836 */
  while (LucByteCSpark != DEM_ZERO)
  {
    if (((LucByteCSpark & DEM_ONE) == DEM_ONE))
    {
      /* Check that event is disabled or readiness state Catalyst monitoring
           is supported.
       */
      if ((Dem_GulEventIdDisabled & LulEventIdDisabledMask) ==
          LulEventIdDisabledMask)
      {
        /* @Trace: Dem_SUD_API_11838 */
        /*
         * MISRA Rule        : 21.1
         * Message           : An integer expression with a value that is
         *                     apparently negative is being converted to an
         *                     unsigned type.
         * Reason            : Negation operator is used to achieve
         *                     better throughput.
         * Verification      : However, part of the code is verified
         *                     manually and it is not having any impact.
         */

        /* Bit0 of Byte-3 is set to 0 to indicate monitor is disabled */
        LaaPid41data[DEM_ZERO] = (LaaPid41data[DEM_ZERO] &
            ((uint8)(~LucBitPos)));

        /* Bit0 of Byte-4 is set to 1 to indicate monitor is not completed  */
        LaaPid41data[DEM_ONE] = LaaPid41data[DEM_ONE] | LucBitPos;
      }
      else
      {
        /* @Trace: Dem_SUD_API_11840 */
        if (LucReadynessGruoupIndex < DEM_SEVEN)
        {
          /* @Trace: Dem_SUD_API_11839 */
          /* Bit0 of Byte-3 is set to 1 if Catalyst monitoring
           is enabled*/
          LaaPid41data[DEM_ZERO] = LaaPid41data[DEM_ZERO] | LucBitPos;

        /* Trace: DEM_OBD_01_03 */
        Dem_CalcReadinessPIDValue(DEM_PID41_CALC, &LaaPid41data[DEM_ONE], 
        LucBitPos, LaaReadynessGruoup[LucReadynessGruoupIndex]);  
        }
      }

    }
    else /* Catalyst monitoring is not supported*/
    {
      /* @Trace: Dem_SUD_API_11837 */
      /*
       * MISRA Rule        : 21.1
       * Message           : An integer expression with a value that is
       *                     apparently negative is being converted to an
       *                     unsigned type.
       * Reason            : Negation operator is used to achieve
       *                     better throughput.
       * Verification      : However, part of the code is verified
       *                     manually and it is not having any impact.
       */
      /* Bit-0 of Byte-3 is set to 0   */
      LaaPid41data[DEM_ZERO] = (LaaPid41data[DEM_ZERO] &
          ((uint8)(~LucBitPos)));

      /*
       * MISRA Rule        : 21.1
       * Message           : An integer expression with a value that is
       *                     apparently negative is being converted to an
       *                   : unsigned type.
       * Reason            : Negation operator is used to achieve
       *                     better throughput.
       * Verification      : However, part of the code is verified
       *                     manually and it is not having any impact.
       */
      /* Bit0 of Byte-4 is set to 1 to indicate monitor is not completed  */
      LaaPid41data[DEM_ONE] = (LaaPid41data[DEM_ONE] & ((uint8)(~LucBitPos)));
    }

    LucByteCSpark = LucByteCSpark >> DEM_ONE;

    LucBitPos = LucBitPos << DEM_ONE;

    if (LucBitPos != DEM_BIT4_MASK1)
    {
      /* @Trace: Dem_SUD_API_11841 */
      LulEventIdDisabledMask = LulEventIdDisabledMask << DEM_ONE;

      LucReadynessGruoupIndex++;
    }
    else
    {
      /* @Trace: Dem_SUD_API_11842 */
      /* Do nothing. To avoid warnings */
    }
  }
  #else /* For compression engines*/
  {
    /* EventId Disabled Mask is 0x400 */
    LulEventIdDisabledMask = DEM_BIT10_MASK1;
    /* @Trace: Dem_SUD_API_11828 */
    while (LucByteCSpark != DEM_ZERO)
    {
      if (((LucByteCSpark & DEM_ONE) == DEM_ONE))
      {
        /* Check that event is disabled or readiness state Catalyst monitoring
         is supported.
         */
        if ((Dem_GulEventIdDisabled & LulEventIdDisabledMask) ==
            LulEventIdDisabledMask)
        {
          /* @Trace: Dem_SUD_API_11830 */
          /*
           * MISRA Rule        : 21.1
           * Message           : An integer expression with a value that is
           *                     apparently negative is being converted to an
           *                   : unsigned type.
           * Reason            : Negation operator is used to achieve
           *                     better throughput.
           * Verification      : However, part of the code is verified
           *                     manually and it is not having any impact.
           */

          /* Bit0 of Byte-3 is set to 0 to indicate monitor is disabled */
          LaaPid41data[DEM_ZERO] = (LaaPid41data[DEM_ZERO] &
              ((uint8)(~LucBitPos)));

          /* Bit0 of Byte-4 is set to 1 to indicate monitor is not completed  */
          LaaPid41data[DEM_ONE] = LaaPid41data[DEM_ONE] | LucBitPos;
        }
        else
        {
          /* @Trace: Dem_SUD_API_11831 */
          /* Bit0 of Byte-3 is set to 1 if Catalyst monitoring
           is enabled*/
          LaaPid41data[DEM_ZERO] = LaaPid41data[DEM_ZERO] | LucBitPos;

        /* Trace: DEM_OBD_01_03 */
        Dem_CalcReadinessPIDValue(DEM_PID41_CALC, &LaaPid41data[DEM_ONE], 
            LucBitPos, LaaReadynessGruoup[LucReadynessGruoupIndex]);  
        }

      }
      else /* Catalyst monitoring is not supported*/
      {
        /* @Trace: Dem_SUD_API_11829 */
        /* Bit-0 of Byte-3 is set to 0   */
        LaaPid41data[DEM_ZERO] = LaaPid41data[DEM_ZERO] & (~LucBitPos);

        /* Bit0 of Byte-4 is set to 1 to indicate monitor is not completed  */
        LaaPid41data[DEM_ONE] = LaaPid41data[DEM_ONE] & (~LucBitPos);
      }

      LucByteCSpark = LucByteCSpark >> DEM_ONE;
      LucBitPos = LucBitPos << DEM_ONE;

      if ((LucBitPos != DEM_BIT2_MASK1) && (LucBitPos != DEM_BIT4_MASK1))
      {
        if (LucBitPos != DEM_BIT7_MASK1)
        {
          /* @Trace: Dem_SUD_API_11832 */
          LulEventIdDisabledMask = LulEventIdDisabledMask << DEM_ONE;
        }
        else
        {
          /* @Trace: Dem_SUD_API_11833 */
          /* EventId Disabled Mask is 0x200 */
          LulEventIdDisabledMask = Dem_GulEventIdDisabled | DEM_BIT9_MASK1;
        }

        LucReadynessGruoupIndex++;
      }
      else
      {
        /* @Trace: Dem_SUD_API_11834 */
        /* Do nothing. To avoid warnings*/
      }
    }
  }
  #endif
  PID41Value[DEM_ZERO] = LaaPid41data[DEM_ZERO];

  PID41Value[DEM_ONE]  = LaaPid41data[DEM_ONE];
}
#endif


/*******************************************************************************
 ** Function Name       : Dem_SetMalfuntionOnOff                              **
 **                                                                           **
 ** Service ID          : None                                                **
 **                                                                           **
 ** Description         : Function is used to process the indicator bit for   **
 **                       Obd                                                 **
 **                                                                           **
 ** Re-entrancy         : Reentrant                                           **
 **                                                                           **
 ** Input Parameters    : LucIndicatorIndex, LusCount, EventStatusMask        **
 **                                                                           **
 ** InOut parameter     : None                                                **
 **                                                                           **
 ** Output Parameters   : None                                                **
 **                                                                           **
 ** Return parameter    : None                                                **
 **                                                                           **
 ** Preconditions       : None                                                **
 **                                                                           **
 ** Remarks             :                                                     **
 *******************************************************************************/
#if ((DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT) && (DEM_NUMBER_OF_INDICATORS > DEM_ZERO))
FUNC(void, DEM_CODE)
Dem_SetMalfuntionOnOff(void)
{
  VAR(boolean, DEM_VAR) LblIndicatorAttributeStatus;
  VAR(Dem_NumOfIndicatorAttributeType, DEM_VAR) LddIdx;
  P2CONST(Dem_IndicatorAttributeType , AUTOMATIC, DEM_VAR) LddIndicator;
  /* @Trace: Dem_SUD_API_11792 */
  for (LddIdx = DEM_ZERO; LddIdx < DEM_NUMBER_OF_INDICATORS; LddIdx++)
  {
    LddIndicator = Dem_GetCfgIndicatorAtt(LddIdx);
    /* @Trace: Dem_SUD_API_11793 */
    if (DEM_MIL_INDICATORID == LddIndicator->IndicatorIdRef)
    {
      LblIndicatorAttributeStatus = Dem_EvMem_GetIndicatorAttStatus(
          LddIndicator->EventIdRef, LddIndicator->IndicatorAttStatusPos);
      Dem_GucMilonFlag = LblIndicatorAttributeStatus << 7U;
      /* @Trace: Dem_SUD_API_11795 */
      if (Dem_GucMilonFlag == DEM_BIT7_MASK1)
      {
        /* @Trace: Dem_SUD_API_11794 */
        break;
      }
    }
  }

}
#endif

/*******************************************************************************
 ** Function Name       : Dem_GetRatioIndex                                   **
 **                                                                           **
 ** Service ID          : None                                                **
 **                                                                           **
 ** Description         : Function is used to get ratio index                 **
 **                                                                           **
 ** Re-entrancy         : Reentrant                                           **
 **                                                                           **
 ** Input Parameters    : event, ArrayIndex, EventStatusMask                  **
 **                                                                           **
 ** InOut parameter     : None                                                **
 **                                                                           **
 ** Output Parameters   : RatioId                                             **
 **                                                                           **
 ** Return parameter    : None                                                **
 **                                                                           **
 ** Preconditions       : None                                                **
 **                                                                           **
 ** Remarks             :                                                     **
 *******************************************************************************/
#if ((DEM_NUMBER_OF_RATIO_INFO > DEM_ZERO) && \
     (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT))
static FUNC(void, DEM_CODE) Dem_GetRatioIndex(
    VAR(Dem_EventParameterCPCType, DEM_VAR) event,
    VAR(uint32, DEM_VAR) ArrayIndex,
    P2VAR(uint8, AUTOMATIC,DEM_VAR) RatioId)
{
  /* @Trace: Dem_SUD_API_11796 */
  *RatioId = event->aaRatioIndex[ArrayIndex];
}
#endif

/*******************************************************************************
 ** Function Name       : Dem_GetMalfuntionOnOff                              **
 **                                                                           **
 ** Service ID          : None                                                **
 **                                                                           **
 ** Description         : Function is used to get the indicator bit for obd   **
 **                                                                           **
 ** Re-entrancy         : Reentrant                                           **
 **                                                                           **
 ** Input Parameters    : None                                                **
 **                                                                           **
 ** InOut parameter     : None                                                **
 **                                                                           **
 ** Output Parameters   : None                                                **
 **                                                                           **
 ** Return parameter    : Dem_GucMilonFlag                                    **
 **                                                                           **
 ** Preconditions       : None                                                **
 **                                                                           **
 ** Remarks             :                                                     **
 *******************************************************************************/
#if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
FUNC(boolean, DEM_CODE) Dem_GetMalfuntionOnOff(void)
{
  /* @Trace: Dem_SUD_API_11805 */
  return Dem_GucMilonFlag;
}
#endif

/*******************************************************************************
 ** Function Name       : Dem_SetObdCycle                                     **
 **                                                                           **
 ** Service ID          : None                                                **
 **                                                                           **
 ** Description         : Function is used to set OBD Cyle                     **
 **                                                                           **
 ** Re-entrancy         : Reentrant                                           **
 **                                                                           **
 ** Input Parameters    : None                                                **
 **                                                                           **
 ** InOut parameter     : None                                                **
 **                                                                           **
 ** Output Parameters   : None                                                **
 **                                                                           **
 ** Return parameter    : None                                                **
 **                                                                           **
 ** Preconditions       : None                                                **
 **                                                                           **
 ** Remarks             :                                                     **
 *******************************************************************************/
#if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
FUNC(Std_ReturnType, DEM_CODE) Dem_SetObdCycle (
  VAR(uint8, DEM_VAR) LucOperationCycleId
)
{
  VAR(boolean, DEM_VAR) LblDirty = DEM_FALSE;

  SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();
  /* polyspace-begin MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] Same as Dead Code. */
  /* polyspace-begin DEFECT:DEAD_CODE [Justified:Low] */
  if ((DEM_OPCYC_WARMUP ==
         Dem_GstOperationCycleName[LucOperationCycleId].ucOperationCycle)
      &&(DEM_TRUE == Dem_EventStatusNvRamData.DtcClear))
  {
    /* @Trace: Dem_SUD_API_11806 */
    if (Dem_EventStatusNvRamData.NumOfWUCSinceLC < DEM_MAX_WARM_UP_COUNT)
    {
      /* @Trace: Dem_SUD_API_11807 */
      Dem_EventStatusNvRamData.NumOfWUCSinceLC++;
      LblDirty = DEM_TRUE;
    }
    /* Trace: DEM_GEN_03*/
    /* @Trace: Dem_SUD_API_11809 */
    Dem_GusWarmUpCycleCount++;
  }
  else if (DEM_OPCYC_WARMUP ==
             Dem_GstOperationCycleName[LucOperationCycleId].ucOperationCycle)
  {
    /* @Trace: Dem_SUD_API_11809 */
    Dem_GusWarmUpCycleCount++;
  }
  /* polyspace-end MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] Same as Dead Code. */
  /* polyspace-end DEFECT:DEAD_CODE [Justified:Low] */
  #if (DEM_NUMBER_OF_RATIO_INFO > DEM_ZERO)
  /* polyspace-begin DEFECT:DEAD_CODE [Justified:Low] "Dead Code by Configuration" */
  /* polyspace-begin MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] Same as Dead Code. */
  else if (DEM_OPCYC_IGNITION ==
             Dem_GstOperationCycleName[LucOperationCycleId].ucOperationCycle)
  {
    /* @Trace: Dem_SUD_API_10722 */
    if (Dem_GusIgnitionCylCnt < DEM_MAX_DENOMINATOR_NUMERATOR_VALUE)
    {
      /* @Trace: Dem_SUD_API_11808 */
      Dem_GusIgnitionCylCnt++;
      /* Trace: DEM_OBD_09_21*/
      if (Dem_GusIgnitionCylCnt == DEM_MAX_DENOMINATOR_NUMERATOR_VALUE)
      {
        Dem_GusIgnitionCylCnt = DEM_ZERO;
      }

      Dem_EventStatusNvRamData.IgnitionCylCnt = Dem_GusIgnitionCylCnt;
      LblDirty = DEM_TRUE;
    }
  }
  /* polyspace-end MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] Same as Dead Code. */
  /* polyspace-end DEFECT:DEAD_CODE [Justified:Low] "Dead Code by Configuration" */
  #endif
  else if (DEM_OPCYC_OBD_DCY ==
             Dem_GstOperationCycleName[LucOperationCycleId].ucOperationCycle)
  {
    /* @Trace: SWS_Dem_01156
     * The B1 counter shall reset to zero after three consecutive operating
     * sequences where no Class B1 event have been detected.*/
    if (Dem_PreWWHOBDB1Counter == Dem_WWHOBDB1Counter)
    {
      /* @Trace: Dem_SUD_API_11811 */
      Dem_WWHOBDNumCycleNoB1Class++;
    }
    else
    {
      /* @Trace: Dem_SUD_API_11812 */
      Dem_WWHOBDNumCycleNoB1Class = DEM_ZERO;
    }
    Dem_PreWWHOBDB1Counter = Dem_WWHOBDB1Counter;
    Dem_WWHOBDNumCycleCmd++;
    /* Trace: DEM_OBD_09_22 */
    #if (DEM_NUMBER_OF_RATIO_INFO > DEM_ZERO )
    /* @Trace: Dem_SUD_API_12227 */
    (void)Dem_OCStartInit();
    /* After OCStartInit, Update NvRAM */
    LblDirty = DEM_TRUE;
    #endif
  }
  else
  {
    /* @Trace: Dem_SUD_API_11810 */
    /* Nothing to do */
  }
  SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();
  /* @Trace: Dem_SUD_API_11814 */
  if (LblDirty == DEM_TRUE)
  {
    /* @Trace: Dem_SUD_API_11813 */
    Dem_EvMem_SetNonVolatieDataStatus(
        DEM_NVDATA_ALL_EVENT_STATUS_ID, DEM_EVMEM_STATUS_DIRTY_NVM);
    Dem_EvMem_TriggerWriteAllBlocks();
  }

  return E_OK;
}
#endif

/*******************************************************************************
 ** Function Name       : Dem_ClearObdInfomation                              **
 **                                                                           **
 ** Service ID          : None                                                **
 **                                                                           **
 ** Description         : Function is used to clear OBD information           **
 **                                                                           **
 ** Re-entrancy         : Reentrant                                           **
 **                                                                           **
 ** Input Parameters    : None                                                **
 **                                                                           **
 ** InOut parameter     : None                                                **
 **                                                                           **
 ** Output Parameters   : None                                                **
 **                                                                           **
 ** Return parameter    : None                                                **
 **                                                                           **
 ** Preconditions       : None                                                **
 **                                                                           **
 ** Remarks             :                                                     **
 ******************************************************************************/
/* @Trace: SRS_Diag_04141
 */
#if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
FUNC(void, DEM_CODE)
Dem_ClearObdInfomation(void)
{
  /* @Trace: SWS_Dem_01178
   * In addition to chapter 7.7.2.2 the Dem shall clear/reset the
   * following values:
   *      Activation Mode
   *      Readiness (PID $01, PID $41 and PID $90)
   *      Continuous-MI Counter
   *      Highest ECU B1 Counter
   *      B1 Counter
   *      Legislative Freeze Frame */
  /* Legislative Freeze Frame */
  /* @Trace: Dem_SUD_API_10721 */
  if ((DEM_NO_EVMEM_ENTRY != Dem_ObdMemoryId) &&
      (DEM_MAX_NUMBER_EVENT_ENTRY_PRI > Dem_ObdMemoryId))
  {
    /* @Trace: Dem_SUD_API_10679 */
    if (DEM_NO_EVENT != Dem_PrimaryEventMemory[Dem_ObdMemoryId].EventIdRef)
    {
      Dem_EventMemoryEntryPtrType LddMemEntry =
          &Dem_PrimaryEventMemory[Dem_ObdMemoryId];

      SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();
      /* @Trace: Dem_SUD_API_11816 */
      for (uint8 LucIdx = DEM_ZERO; LucIdx < DEM_SIZE_OF_EVENT_DATA; LucIdx++)
      {
        /* @Trace: Dem_SUD_API_11815 */
        LddMemEntry->data[LucIdx] = DEM_ZERO;
      }
      SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();

      #if (DEM_EVMEM_TIMESTAMP_USED == STD_ON)
      /* @Trace: Dem_SUD_API_11817 */
      Dem_EvMem_ClearMemLocInEvMemMap(
          LddMemEntry->EventIdRef, DEM_DTC_ORIGIN_PRIMARY_MEMORY, LddMemEntry);
      #else
      /* @Trace: Dem_SUD_API_11818 */
      Dem_EvMem_ClearMemLocInEvMemMap(
          LddMemEntry->EventIdRef, DEM_DTC_ORIGIN_PRIMARY_MEMORY);
      #endif
      Dem_EvClearProcState(LddMemEntry->EventIdRef, DEM_EVPROCSTATE_EVENT_DEL);
      /* Clear the event memory entry in RAM */
      Dem_EvMem_ClearEventMemoryEntry(LddMemEntry);

      /* NvBlock flag for EventStatus will be set after this job has been
       * finished */
      Dem_EvMem_SetEvMemNvBlockStatus(
          DEM_DTC_ORIGIN_PRIMARY_MEMORY,
          Dem_ObdMemoryId,
          DEM_EVMEM_STATUS_CLEARDTC);

      SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();
      Dem_ObdMemoryId = DEM_NO_EVMEM_ENTRY;
      LddMemEntry->EventIdRef = DEM_NO_EVENT;
      Dem_EventStatusNvRamData.ObdMemoryId = Dem_ObdMemoryId;
      SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();

      Dem_EvMem_SetNonVolatieDataStatus(DEM_NVDATA_ALL_EVENT_STATUS_ID,
          DEM_EVMEM_STATUS_DIRTY_NVM);
      Dem_EvMem_TriggerWriteAllBlocks();
    }
  }
  /* Clear activation mode*/
  SchM_Enter_Dem_CAPTURE_OBD_DATA();
  Dem_WWHOBDActMode = DEM_WWHOBD_ACTIVATION_MODE_1;
  Dem_WWHOBDPreActMode = DEM_WWHOBD_ACTIVATION_MODE_1;
  /* Continuous-MI Counter*/
  Dem_WWHOBDConMICont = DEM_ZERO;

  /* Highest ECU B1 Counter*/
  Dem_WWHOBDHighestB1Cont = DEM_ZERO;

  /* B1 Counter*/
  Dem_WWHOBDB1Counter = DEM_ZERO;

  /* Readiness (PID $01, PID $41 and PID $90)*/
  Dem_DataOfPID4D = DEM_ZERO;
  #if ((DEM_OBD_CENTRALIZED_PID_21_HANDLING == STD_ON) && \
       (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT))
  Dem_DataOfPID21 = DEM_ZERO;
  #endif

  /* Trace: DEM_OBD_01_07 */
  Dem_DataOfPID31 = DEM_ZERO;
  Dem_DataOfPID4E = DEM_ZERO;
  Dem_EventStatusNvRamData.DataOfPID21 = Dem_DataOfPID21;
  Dem_EventStatusNvRamData.DataOfPID31 = Dem_DataOfPID31;
  Dem_EventStatusNvRamData.DataOfPID4D = Dem_DataOfPID4D;
  Dem_EventStatusNvRamData.DataOfPID4E = Dem_DataOfPID4E;

  Dem_GblClearTimeStartObd = DEM_TRUE;
  Dem_GblDtcCleared = DEM_TRUE;
  Dem_GulTimeSinceMilOn = DEM_ZERO;
  Dem_GulDemClearTimeCount = DEM_ZERO;
  SchM_Exit_Dem_CAPTURE_OBD_DATA();

  SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();
  Dem_EventStatusNvRamData.DtcClear        = Dem_GblDtcCleared;
  Dem_EventStatusNvRamData.NumOfWUCSinceLC = DEM_ZERO;
  Dem_EventStatusNvRamData.WWHOBDConMICont = DEM_ZERO;
  Dem_EventStatusNvRamData.WWHOBDB1Counter = DEM_ZERO;
  Dem_EventStatusNvRamData.ObdMemoryId     = DEM_NO_EVMEM_ENTRY;


  /* @Trace: Dem_SUD_API_11819 */
  #if (DEM_NUMBER_OF_RATIO_INFO > DEM_ZERO)
  /* Initialise the ignition cycle count to zero */
  Dem_EventStatusNvRamData.IgnitionCylCnt = DEM_ZERO;
  Dem_GusIgnitionCylCnt = Dem_EventStatusNvRamData.IgnitionCylCnt;
  /* Initialise the general denominator for infotype08 and infotype0b as zero */
  Dem_EventStatusNvRamData.GeneralDenCnt = DEM_ZERO;
  Dem_GusGeneralDenominator = Dem_EventStatusNvRamData.GeneralDenCnt;

  /* Trace: DEM_OBD_09_08 */
  /* Initialise the numerator and denominator of IUMPR group to zero */
  /* @Trace: Dem_SUD_API_11820 */
  for (uint8 LusIndex = DEM_ZERO; LusIndex < DEM_NUMBER_OF_RATIO_INFO;
      LusIndex++)
  {
    /* @Trace: Dem_SUD_API_10680 */
    Dem_EventStatusNvRamData.IumprDenominator[LusIndex] = DEM_ZERO;
    Dem_GaaIumprDenominator[LusIndex] =
        Dem_EventStatusNvRamData.IumprDenominator[LusIndex];

    Dem_EventStatusNvRamData.IumprNumerator[LusIndex] = DEM_ZERO;
    Dem_GaaIumprNumerator[LusIndex] =
      Dem_EventStatusNvRamData.IumprNumerator[LusIndex];
  }

  for (uint8 LucGroupRatioCount = DEM_ZERO; LucGroupRatioCount < DEM_IUMPR_MAX;
      LucGroupRatioCount++)
  {
    /* Init to Last Array, which always 0 */
    Dem_EventStatusNvRamData.IumprMinimumRatioIDPerGroup[LucGroupRatioCount] = DEM_NUMBER_OF_RATIO_INFO;
    Dem_GaaIumprMinimumRatioIDPerGroup[LucGroupRatioCount] =
        Dem_EventStatusNvRamData.IumprMinimumRatioIDPerGroup[LucGroupRatioCount];
        
    Dem_EventStatusNvRamData.IumprUpdateFlagPerGroup[LucGroupRatioCount] = DEM_ZERO;
    Dem_GaaIumprUpdateFlagPerGroup[LucGroupRatioCount] =
        Dem_EventStatusNvRamData.IumprUpdateFlagPerGroup[LucGroupRatioCount];
  }


  #if (DEM_J1979_2_OBD_ON_UDS == STD_ON)
  /* Trace: DEM_19792_06_05 */
  for (uint16 LusIndex = DEM_ZERO; LusIndex < DEM_NUMBER_OF_RATIO_INFO; LusIndex++)    
  {               
    Dem_EventStatusNvRamData.MonitorActivityDenominator[LusIndex] = DEM_MONITOR_ACTIVITY_INIT;     
    Dem_GaaMonitorActivityDenominator[LusIndex] =  Dem_EventStatusNvRamData.MonitorActivityDenominator[LusIndex];
    Dem_EventStatusNvRamData.MonitorActivityNumerator[LusIndex] = DEM_MONITOR_ACTIVITY_INIT;
    Dem_EventStatusNvRamData.MonitorActivityRatio[LusIndex] = DEM_MONITOR_ACTIVITY_INIT;
    Dem_GaaMonitorActivityNumerator[LusIndex] = Dem_EventStatusNvRamData.MonitorActivityNumerator[LusIndex];
    Dem_GaaMonitorActivityRatio[LusIndex] = Dem_EventStatusNvRamData.MonitorActivityRatio[LusIndex];
  }
  #endif /* (DEM_J1979_2_OBD_ON_UDS == STD_ON) */

  Dem_EvMem_SetNonVolatieDataStatus(DEM_NVDATA_ALL_EVENT_STATUS_ID,
      DEM_EVMEM_STATUS_DIRTY_NVM);
  Dem_EvMem_TriggerWriteAllBlocks();
  #endif

  SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();
}
#endif


/*******************************************************************************
 ** Function Name       : Dem_OCStartInit                                     **
 **                                                                           **
 ** Service ID          : None                                                **
 **                                                                           **
 ** Description         : Function is used to start OBD Cyle                  **
 **                                                                           **
 ** Re-entrancy         : Reentrant                                           **
 **                                                                           **
 ** Input Parameters    : None                                                **
 **                                                                           **
 ** InOut parameter     : None                                                **
 **                                                                           **
 ** Output Parameters   : None                                                **
 **                                                                           **
 ** Return parameter    : None                                                **
 **                                                                           **
 ** Preconditions       : None                                                **
 **                                                                           **
 ** Remarks             :                                                     **
 *******************************************************************************/
#if ((DEM_NUMBER_OF_RATIO_INFO > DEM_ZERO) && \
     (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT))
FUNC(Std_ReturnType, DEM_CODE)
Dem_OCStartInit(void)
{
  /* @Trace: Dem_SUD_API_11821 */
  #if (DEM_NUMBER_OF_RATIO_INFO > DEM_ZERO)
  /* @Trace: Dem_SUD_API_11822 */
  Dem_GblRatioInit = DEM_FALSE;
  #endif

  #if (DEM_J1979_2_OBD_ON_UDS == STD_ON)
  /* Trace: DEM_19792_06_08 */

  /* @Trace: Dem_SUD_API_11821 */
  /* Update Monitor Activity Ratio When Driving Cycle End */
  Dem_UpdateMonitorActivityRatio();

  /* Driving Cycle Start Funciton */
  Dem_InitMonitorActivityRatio();
  #endif /* (DEM_J1979_2_OBD_ON_UDS == STD_ON) */

  /* Trace: DEM_OBD_09_22 */
  /* @Trace: Dem_SUD_API_12228 */
  #if ((DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT) && \
                 (DEM_NUMBER_OF_RATIO_INFO > DEM_ZERO))
  /* @Trace: Dem_SUD_API_12229 */
  for (uint8 LucIdxRatio = DEM_ZERO;
              LucIdxRatio < DEM_NUMBER_OF_RATIO_INFO;
              LucIdxRatio++ )
  {
    /* @Trace: Dem_SUD_API_12230 */
    Dem_GaaIumprDenominatorIsCounted[LucIdxRatio] = DEM_FALSE;
    Dem_GaaIumprNumeratorIsCounted[LucIdxRatio] = DEM_FALSE;
  }

  /* @Trace: Dem_SUD_API_11691 */
  /*Initialise the Dem_GusRatioDenCondState */
  for (uint8 LucIdx = DEM_ZERO;
             LucIdx < DEM_IUMPR_MAX_CONDITION_NUMBER ;
             LucIdx++)
  {
	  /* @Trace: Dem_SUD_API_11692 */    
	  Dem_GusRatioDenCondState[LucIdx] = DEM_IUMPR_DEN_STATUS_NOT_REACHED;  
  }
  #endif 

  return E_OK;
}
#endif

/*******************************************************************************
 ** Function Name       : Dem_SetDataOfPID21                                  **
 **                                                                           **
 ** Service ID          : 0xa6                                                **
 **                                                                           **
 ** Description         : Function is used to set the value of PID $21 in the **
 **                       Dem by a software component.                        **
 **                                                                           **
 ** Re-entrancy         : Non Reentrant                                       **
 **                                                                           **
 ** Input Parameters    : PID21value Buffer containing the contents of PID $21**
 **                                                                           **
 ** InOut parameter     : None                                                **
 **                                                                           **
 ** Output Parameters   : None                                                **
 **                                                                           **
 ** Return parameter    : Always E_OK is returned                             **
 **                                                                           **
 ** Preconditions       : None                                                **
 **                                                                           **
 ** Remarks             :                                                     **
 *******************************************************************************/
#if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
FUNC(Std_ReturnType, DEM_CODE)
Dem_SetDataOfPID21(
    P2CONST(uint8, AUTOMATIC, DEM_APPL_DATA) PID21value)
{
  VAR(Std_ReturnType, DEM_VAR) LddReturnValue = E_OK;
  /* Module Initialization check */
  if (DEM_INIT != Dem_GucInit)
  {
    /* @Trace: Dem_SUD_API_12897 */
    /* Report to DET */
    DEM_REPORT_ERROR( DEM_SETDATAOFPID21_SID, DEM_E_UNINIT);
  }
  else if (NULL_PTR == PID21value)
  {
    /* @Trace: Dem_SUD_API_12898 */
    /* Report to DET */
    DEM_REPORT_ERROR( DEM_SETDATAOFPID21_SID, DEM_E_PARAM_POINTER);
  }
  else
  {
    /* @Trace: SWS_Dem_01095
     * On invocation of Dem_SetDataOfPID21 the internal PID $21 value shall be
     * updated. */
    P2CONST(uint8, AUTOMATIC, DEM_APPL_DATA) LpPID21Value = PID21value;
    SchM_Enter_Dem_CAPTURE_OBD_DATA();
    /* @Trace: Dem_SUD_API_12899 */
    for (uint8 LucIdx = DEM_ZERO; LucIdx < DEM_TWO; LucIdx++)
    {
      /* @Trace: Dem_SUD_API_12900 */
      #if ((DEM_OBD_CENTRALIZED_PID_21_HANDLING == STD_ON) && \
           (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT))
      if (DEM_ZERO == LucIdx)
      {
        /* @Trace: Dem_SUD_API_12901 */
        Dem_DataOfPID21 = DEM_ZERO;
        Dem_DataOfPID21 |= *LpPID21Value;
      }
      else
      {
        /* @Trace: Dem_SUD_API_12902 */
        Dem_DataOfPID21 |= (uint16)((uint16)*LpPID21Value << DEM_EIGHT);
      }
      LpPID21Value++;
      #endif
    }
    SchM_Exit_Dem_CAPTURE_OBD_DATA();
  }
  return LddReturnValue;
}
#endif
/*******************************************************************************
 ** Function Name       : Dem_GetDataOfPID21                                  **
 **                                                                           **
 ** Service ID          : 0xb1                                                **
 **                                                                           **
 ** Description         : Function is used to set the value of PID $21 in the **
 **                       Dem by a software component.                        **
 **                                                                           **
 ** Re-entrancy         : Non Reentrant                                       **
 **                                                                           **
 ** Input Parameters    : PID21value Content of PID $21 as raw hex value.     **
 **                                                                           **
 ** InOut parameter     : None                                                **
 **                                                                           **
 ** Output Parameters   : None                                                **
 **                                                                           **
 ** Return parameter    : Always E_OK is returned                             **
 **                                                                           **
 ** Preconditions       : None                                                **
 **                                                                           **
 ** Remarks             :                                                     **
 *******************************************************************************/
#if ((DEM_OBD_CENTRALIZED_PID_21_HANDLING == STD_ON) && \
     (DEM_OBD_SUPPORT == DEM_OBD_MASTER_ECU))
FUNC(Std_ReturnType, DEM_CODE)
Dem_GetDataOfPID21(
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA) PID21value )
{
  VAR(Std_ReturnType, DEM_VAR) LddReturnValue = E_OK;
  /* Module Initialization check */
  if (DEM_INIT != Dem_GucInit)
  {
    /* @Trace: Dem_SUD_API_12889 */
    /* Report to DET */
    DEM_REPORT_ERROR( DEM_GETDATAOFPID21_SID, DEM_E_UNINIT);
  }
  else if (NULL_PTR == PID21value)
  {
    /* @Trace: Dem_SUD_API_12890 */
    /* Report to DET */
    DEM_REPORT_ERROR ( DEM_GETDATAOFPID21_SID, DEM_E_PARAM_POINTER);
  }
  else
  {
    /* @Trace: SWS_Dem_01096
     * An OBD Master ECU shall calculate the PID $21 value by its own */
    /* @Trace: SWS_Dem_01097
     * On invocation of Dem_GetDataOfPID21 the internal calculated PID $21 value
     * shall be returned */
    #if (DEM_MAX_NUMBER_OF_PID_RECDS > DEM_ZERO)
    uint8 LucPidNum;
    uint8 LucCount;
    /* @Trace: Dem_SUD_API_12892 */
    for (LucCount = DEM_ZERO;
         LucCount < DEM_MAX_NUMBER_OF_PID_RECDS;
         LucCount++)
    {
      /* @LucPidNum = Dem_GaaPid[LucCount].ucPid;*/
      LucPidNum = Dem_GaaPid[LucCount].PidIdentifier;
      /* @Trace: Dem_SUD_API_12895 */
      /* polyspace-begin MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] Same as Dead Code. */
      /* polyspace-begin DEFECT:DEAD_CODE [Justified:Low] */
      if (DEM_PID_21 == LucPidNum)
      {
        CONSTP2CONST(Dem_DataElementClassType, AUTOMATIC, DEM_CONST)
        LddElementClass =
            &Dem_DataElementClass
              [Dem_GaaDataElementRefAry[LucCount].ucDataElementIndex];
        /* @Trace: Dem_SUD_API_12894 */
        if (NULL_PTR != LddElementClass->ReadFunc)
        {
          /* @Trace: Dem_SUD_API_12893 */
          LddElementClass->ReadFunc(PID21value, DEM_ZERO);

          /* MISRA Rule   : 13.6
           * Message      : LucCount being modified in the  body of the loop.
           * Reason       : Once the search element found, control exiting
           *                from the for loop to terminate next iteration.
           * Verification : However, part of the code is verified
           *                manually and it is not having any impact.
           */

          /* Exit the loop */
          break;
        }
        else 
        {
          if (NULL_PTR != LddElementClass->SRReadFunc)
          {
            LddElementClass->SRReadFunc(PID21value);

            /* Exit the loop */
            break;
          }
        }
      }
      /* polyspace-end MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] Same as Dead Code. */
      /* polyspace-end DEFECT:DEAD_CODE [Justified:Low] */
    }
    /* Speed is not found */
    /* @Trace: Dem_SUD_API_12896 */
    /* polyspace +1 MISRA-C3:14.3 [Justified:Low] Justify with annotations */
    if (DEM_PID_21 != LucPidNum)
    {
      /* @Trace: Dem_SUD_API_00167 */
      /* Km with MIL On is set to zero if speed is not found  */
      *PID21value = (uint8)DEM_ZERO;
    }
    #else
    /* @Trace: Dem_SUD_API_12891 */
    /* Km with MIL On is set to zero if speed is not found  */
    *PID21value = (uint8)DEM_ZERO;
    #endif

    Dem_DataOfPID21 = *PID21value;
  }

  return LddReturnValue;
}
#endif

/*******************************************************************************
 ** Function Name       : Dem_SetDataOfPID31                                  **
 **                                                                           **
 ** Service ID          : 0xa7                                                **
 **                                                                           **
 ** Description         : Function is used to set the value of PID $31 in the **
 **                       Dem by a software component.                        **
 **                                                                           **
 ** Re-entrancy         : Reentrant                                           **
 **                                                                           **
 ** Input Parameters    : PID31value  - Buffer containing the contents of     **
 **                                     PID $31. The buffer is provided by    **
 **                                     the Dcm with the appropriate size,    **
 **                                     i.e. during configuration, the Dcm    **
 **                                     identifies the required size from the **
 **                                     largest PID in order to configure a   **
 **                                     PIDBuffer.                            **
 **                                                                           **
 ** InOut parameter     : None                                                **
 **                                                                           **
 ** Output Parameters   : None                                                **
 **                                                                           **
 ** Return parameter    : None                                                **
 **                                                                           **
 ** Preconditions       : None                                                **
 **                                                                           **
 ** Remarks             :                                                     **
 *******************************************************************************/
#if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
FUNC(Std_ReturnType, DEM_CODE)
Dem_SetDataOfPID31(
    P2CONST(uint8, AUTOMATIC, DEM_APPL_DATA) PID31value )
{
  VAR(Std_ReturnType, DEM_VAR) LddReturnValue = E_OK;
  /* Module Initialization check */
  if (DEM_INIT != Dem_GucInit)
  {
    /* @Trace: Dem_SUD_API_12903 */
    /* Report to DET */
    DEM_REPORT_ERROR( DEM_SETDATAOFPID31_SID, DEM_E_UNINIT);
  }
  else if (NULL_PTR == PID31value)
  {
    /* @Trace: Dem_SUD_API_12904 */
    /* Report to DET */
    DEM_REPORT_ERROR ( DEM_SETDATAOFPID31_SID, DEM_E_PARAM_POINTER);
  }
  else
  {
    P2CONST(uint8, AUTOMATIC, DEM_APPL_DATA) LpPID31Value = PID31value;
    SchM_Enter_Dem_CAPTURE_OBD_DATA();
    /* @Trace: Dem_SUD_API_12905 */
    for ( uint8 LucIdx = DEM_ZERO; LucIdx < DEM_TWO; LucIdx++)
    {
      if (DEM_ZERO == LucIdx)
      {
        /* @Trace: Dem_SUD_API_12906 */
        Dem_DataOfPID31 = DEM_ZERO;
        Dem_DataOfPID31 |= *LpPID31Value;
      }
      else
      {
        /* @Trace: Dem_SUD_API_12907 */
        Dem_DataOfPID31
        |= (uint16)((uint16)*LpPID31Value << DEM_EIGHT);
      }

      LpPID31Value++;
    }
    SchM_Exit_Dem_CAPTURE_OBD_DATA();
  }
  
  return LddReturnValue;
}
#endif

/*******************************************************************************
 ** Function Name       : Dem_SetDataOfPID4D                                  **
 **                                                                           **
 ** Service ID          : 0xa8                                                **
 **                                                                           **
 ** Description         : Function is used to set the value of PID $4D in the **
 **                       Dem by a software component.                        **
 **                                                                           **
 ** Re-entrancy         : Reentrant                                           **
 **                                                                           **
 ** Input Parameters    : PID4Dvalue                                          **
 **                                                                           **
 ** InOut parameter     : None                                                **
 **                                                                           **
 ** Output Parameters   : None                                                **
 **                                                                           **
 ** Return parameter    : None                                                **
 **                                                                           **
 ** Preconditions       : None                                                **
 **                                                                           **
 ** Remarks             :                                                     **
 *******************************************************************************/
#if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
FUNC(Std_ReturnType, DEM_CODE)
Dem_SetDataOfPID4D(
    P2CONST(uint8, AUTOMATIC, DEM_APPL_DATA) PID4Dvalue )
{
  VAR(Std_ReturnType, DEM_VAR) LddReturnValue = E_OK;
  /* Module Initialization check */
  if (DEM_INIT != Dem_GucInit)
  {
    /* @Trace: Dem_SUD_API_12908 */
    /* Report to DET */
    DEM_REPORT_ERROR( DEM_SETDATAOFPID4D_SID, DEM_E_UNINIT);
  }
  else if (NULL_PTR == PID4Dvalue)
  {
    /* @Trace: Dem_SUD_API_12909 */
    /* Report to DET */
    DEM_REPORT_ERROR ( DEM_SETDATAOFPID4D_SID, DEM_E_PARAM_POINTER);
  }
  else
  {
    P2CONST(uint8, AUTOMATIC, DEM_APPL_DATA) LpPID4DValue = PID4Dvalue;
    SchM_Enter_Dem_CAPTURE_OBD_DATA();
    /* @Trace: Dem_SUD_API_12910 */
    for (uint8 LucIdx = DEM_ZERO; LucIdx < DEM_TWO; LucIdx++)
    {
      if (DEM_ZERO == LucIdx)
      {
        /* @Trace: Dem_SUD_API_12911 */
        Dem_DataOfPID4D = DEM_ZERO;
        Dem_DataOfPID4D |= *LpPID4DValue;
      }
      else
      {
        /* @Trace: Dem_SUD_API_12912 */
        Dem_DataOfPID4D
        |= (uint16)((uint16)*LpPID4DValue << DEM_EIGHT);
      }

      LpPID4DValue++;
    }
    SchM_Exit_Dem_CAPTURE_OBD_DATA();
  }
  
  return LddReturnValue;
}
#endif


/*******************************************************************************
** Function Name        : Dem_SetDataOfPID4E                                  **
**                                                                            **
** Service ID           : 0xa9                                                **
**                                                                            **
** Description          : Function is used to set the value of PID $4E in the **
**                        Dem by a software component.                        **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : PID4Evalue - Buffer containing the contents of      **
**                                     PID $4E. The buffer is provided by     **
**                                     size, i.e. during configuration, the   **
**                                     Dcm identifies the required size from  **
**                                     the largest PID in order to configure  **
**                                     a PIDBuffer.                           **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
#if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
FUNC(Std_ReturnType, DEM_CODE)
Dem_SetDataOfPID4E(
    P2CONST(uint8, AUTOMATIC, DEM_APPL_DATA) PID4Evalue )
{
  VAR(Std_ReturnType, DEM_VAR) LddReturnValue = E_OK;
  /* Module Initialization check */
  if (DEM_INIT != Dem_GucInit)
  {
    /* @Trace: Dem_SUD_API_12913 */
    /* Report to DET */
    DEM_REPORT_ERROR( DEM_SETDATAOFPID4E_SID, DEM_E_UNINIT);
  }
  else if (NULL_PTR == PID4Evalue)
  {
    /* @Trace: Dem_SUD_API_12914 */
    /* Report to DET */
    DEM_REPORT_ERROR ( DEM_SETDATAOFPID4E_SID, DEM_E_PARAM_POINTER);
  }
  else
  {
    P2CONST(uint8, AUTOMATIC, DEM_APPL_DATA) LpPID4EValue = PID4Evalue;
    SchM_Enter_Dem_CAPTURE_OBD_DATA();
    /* @Trace: Dem_SUD_API_12915 */
    for (uint8 LucIdx = DEM_ZERO; LucIdx < DEM_TWO; LucIdx++)
    {
      if (DEM_ZERO == LucIdx)
      {
        /* @Trace: Dem_SUD_API_12916 */
        Dem_DataOfPID4E = DEM_ZERO;
        Dem_DataOfPID4E |= *LpPID4EValue;
      }
      else
      {
        /* @Trace: Dem_SUD_API_12917 */
        Dem_DataOfPID4E |= (uint16)((uint16)*LpPID4EValue << DEM_EIGHT);
      }

      LpPID4EValue++;
    }
    SchM_Exit_Dem_CAPTURE_OBD_DATA();
  }
  
  return LddReturnValue;
}
#endif



/*******************************************************************************
** Function Name        : Dem_SetDTR                                          **
**                                                                            **
** Service ID           : 0xa2                                                **
**                                                                            **
** Description          : Reports a DTR result with lower and upper limit.    **
**                        The internal event status serves as master whether  **
**                        the DTR values are forwarded or ignored, also       **
**                        taking the DTRUpdateKind into account.              **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant for different DTRIds. Non reentrant for   **
**                        the same DTRId.                                     **
**                                                                            **
** Input Parameters     : DTRId      - Identification of a DTR element by     **
**                                     assigned DTRId.                        **
**                        TestResult - Test result of DTR                     **
**                        LowerLimit - Lower limit of DTR                     **
**                        UpperLimit - Upper limit of DTR                     **
**                        Ctrlval    - Control value of the DTR to support    **
**                                     its interpretation Dem-internally.     **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
/* @Trace: SRS_Diag_04126 SRS_Diag_04179 SRS_Diag_04181
 */
#if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
FUNC(Std_ReturnType, DEM_CODE)
Dem_SetDTR(
    VAR(uint16, DEM_VAR) DTRId,
    VAR(sint32, DEM_VAR) TestResult,
    VAR(sint32, DEM_VAR) LowerLimit,
    VAR(sint32, DEM_VAR) UpperLimit,
    VAR(Dem_DTRControlType, DEM_VAR)Ctrlval
    )
{
  sint32 LslTestResult = TestResult;
  sint32 LslLowerLimit = LowerLimit;
  sint32 LslUpperLimit = UpperLimit;

  /* @Trace: SWS_Dem_00756
   * The Dem shall provide an API Dem_SetDTR within an interface
   * DTRCentralReport to provide a report mechanism to the SWC for their test
   * results. Arguments shall be the DemDtrId, the test value, the minimum and
   * maximum limit, and a state indicating whether the monitor provides a valid
   * minimum limit, maximum limit, or both, or whether the reported values shall
   * be reset to zero.*/

  Std_ReturnType LddRetVal = E_NOT_OK;
  /* Module Initialization check */
  if (DEM_INIT != Dem_GucInit)
  {
    /* @Trace: Dem_SUD_API_12954 */
    /* Report to DET */
    DEM_REPORT_ERROR( DEM_SETDTR_SID, DEM_E_UNINIT);
    /* @LddRetVal = E_NOT_OK;*/
  }
  #if (DEM_NUMBER_OF_DTRS > DEM_ZERO)
  else if (DTRId >= DEM_NUMBER_OF_DTRS)
  {
    /* @Trace: Dem_SUD_API_00169 */
    DEM_REPORT_ERROR( DEM_SETDTR_SID, DEM_E_PARAM_DATA);
    /* @LddRetVal = E_NOT_OK;*/
  }
  #endif
  else
  {
    /* @Trace: SWS_Dem_00757
     * If DemDtrEventRef references a DemEventParameter, the Dem shall
     * process the reported DTR values only if all the enable/storage
     * conditions of the referenced event are fulfilled, independent
     * of DemDtrUpdateKind. If any of the enable/storage conditions
     * of the referenced event are not fulfilled, then the Dem shall
     * ignore the reported DTR values.*/
    #if (DEM_NUMBER_OF_DTRS > DEM_ZERO)
    boolean LblIsProceed = DEM_FALSE;
    if (Dem_GaaDtrInfo[DTRId].usEventId != DEM_NO_IDX_U16)
    {
      /* @Trace: SWS_Dem_01105
       * DTRs referring to the event shall neither be computed nor reported
       * (Dem_SetDTR).*/

      #if (DEM_AVAILABILITY_SUPPORT == DEM_EVENT_AVAILABILITY)
      /* @Trace: Dem_SUD_API_12971 */
      if (DEM_TRUE ==
            Dem_EvIsProcStateTriggered(
                Dem_GaaDtrInfo[DTRId].usEventId,
                DEM_EVPROCSTATE_EVENT_AVAILABLE))
      #endif
      {
        /* @Trace: Dem_SUD_MACRO_006*/
        #if (DEM_ENABLE_CONDITION_SUPPORT == STD_ON)
        /* @Trace: Dem_SUD_API_12972 */
        if (E_OK ==
              Dem_GetEventEnableConditionState(Dem_GaaDtrInfo[DTRId].usEventId))
        #endif
        {
          #if (DEM_STORAGE_CONDITION_SUPPORT == STD_ON)
          /* @Trace: Dem_SUD_API_12973 */
          if (E_OK ==
                Dem_GetEventStorageConditionState(
                    Dem_GaaDtrInfo[DTRId].usEventId))
          #endif
          {
            /* @Trace: SWS_Dem_00754
             * The Dem shall use the DemDtrUpdateKind for the evaluation and
             * processing of reported DTR-values:
             * DEM_DTR_UPDATE_ALWAYS: State of the event is not considered
             * (default, and used if DemDtrEventRef is not configured).
             * DEM_DTR_UPDATE_STEADY: Only when the events pre-debouncing
             * within Dem is stuck at the FAIL or PASS limit, and the latest
             * result matches the debouncing direction.*/
            /* @Trace: Dem_SUD_API_12974 */
            if (DEM_DTR_UPDATE_STEADY == Dem_GaaDtrInfo[DTRId].usUpdateKind)
            {
              /* @Trace: Dem_SUD_API_12975 */
              LblIsProceed = DEM_TRUE;
            }
          }
        }
      }
    }
    else if (DEM_DTR_UPDATE_ALWAYS == Dem_GaaDtrInfo[DTRId].usUpdateKind)
    {
      /* @Trace: Dem_SUD_API_12970 */
      LblIsProceed = DEM_TRUE;
    }
    else
    {
      /* @Trace: Dem_SUD_API_12965 */
      /* Nothing to do */
    }

    if (DEM_TRUE == LblIsProceed)
    {
      LddRetVal = E_OK;
      if (Ctrlval == DEM_DTR_CTL_RESET)
      {
        /* @Trace: Dem_SUD_API_12976 */
        Dem_DtrData[DTRId].Testvalue = DEM_ZERO;
        Dem_DtrData[DTRId].Lowlimvalue = DEM_ZERO;
        Dem_DtrData[DTRId].Upplimvalue = DEM_ZERO;
      }
      else if ((DEM_DTR_CTL_NO_MAX == Ctrlval) ||
               (DEM_DTR_CTL_NO_MIN == Ctrlval) ||
               (DEM_DTR_CTL_NORMAL == Ctrlval))
      {
        uint8 LucOldOutInSide = DEM_DTR_INSIDE;
        uint8 LucNewOutInSide = DEM_DTR_INSIDE;

        if (Ctrlval == DEM_DTR_CTL_NO_MAX)
        {
          /* @Trace: Dem_SUD_API_12960 */
          LslUpperLimit = (sint32)0xFFFF;
        }
        else if (Ctrlval == DEM_DTR_CTL_NO_MIN)
        {
          /* @Trace: Dem_SUD_API_12956 */
          LslLowerLimit = (sint32)0x00;
        }
        else
        {
          /* @Trace: Dem_SUD_API_12955 */
          /* Nothing to do */
        }

        if (LslTestResult < LslLowerLimit)
        {
          /* @Trace: Dem_SUD_API_12959 */
          LucOldOutInSide = DEM_DTR_OUTSIDE_MIN;
        }
        else if (LslTestResult > LslUpperLimit)
        {
          /* @Trace: Dem_SUD_API_12958 */
          LucOldOutInSide = DEM_DTR_OUTSIDE_MAX;
        }
        else
        {
          /* @Trace: Dem_SUD_API_12957 */
          /* Nothing to do */
        }
        /* @Trace: SWS_Dem_00759
         * The Dem shall ensure the validity of the test results vs.
         * threshold(s). If the parameter TestResult passed in Dem_SetDTR is
         * inside/outside the thresholds given by UpperLimit and LowerLimit,
         * Testvalue of Dem_DcmGetDTRData shall also be inside/outside
         * Upplimvalue and Lowlimvalue. If rounding effects lead to an
         * unintended change of the meaning, the thresholds shall be shifted by
         * one increment accordingly to restore the result*/
        uint16 LslValDTRConvert;
        if (E_OK == Dem_DTR_Conversion_Linear(LslTestResult,
                      Dem_GaaDtrInfo[DTRId].usDemDtrCompuNumerator0,
                      Dem_GaaDtrInfo[DTRId].usDemDtrCompuNumerator1,
                      Dem_GaaDtrInfo[DTRId].usDemDtrCompuDenominator0,
                      &LslValDTRConvert))
        {
          /* @Trace: Dem_SUD_API_12961 */
          Dem_DtrData[DTRId].Testvalue = LslValDTRConvert;
        }
        if (E_OK == Dem_DTR_Conversion_Linear(LslLowerLimit,
                      Dem_GaaDtrInfo[DTRId].usDemDtrCompuNumerator0,
                      Dem_GaaDtrInfo[DTRId].usDemDtrCompuNumerator1,
                      Dem_GaaDtrInfo[DTRId].usDemDtrCompuDenominator0,
                      &LslValDTRConvert))
        {
          /* @Trace: Dem_SUD_API_12963 */
          Dem_DtrData[DTRId].Lowlimvalue = LslValDTRConvert;
        }
        if (E_OK == Dem_DTR_Conversion_Linear(LslUpperLimit,
                      Dem_GaaDtrInfo[DTRId].usDemDtrCompuNumerator0,
                      Dem_GaaDtrInfo[DTRId].usDemDtrCompuNumerator1,
                      Dem_GaaDtrInfo[DTRId].usDemDtrCompuDenominator0,
                      &LslValDTRConvert))
        {
          /* @Trace: Dem_SUD_API_12966 */
          Dem_DtrData[DTRId].Upplimvalue = LslValDTRConvert;
        }

        if (Dem_DtrData[DTRId].Testvalue < Dem_DtrData[DTRId].Lowlimvalue)
        {
          /* @Trace: Dem_SUD_API_00170 */
          LucNewOutInSide = DEM_DTR_OUTSIDE_MIN;
        }
        else if (Dem_DtrData[DTRId].Testvalue
            > Dem_DtrData[DTRId].Upplimvalue)
        {
          /* @Trace: Dem_SUD_API_12967 */
          LucNewOutInSide = DEM_DTR_OUTSIDE_MAX;
        }
        else
        {
          /* @Trace: Dem_SUD_API_12968 */
          /* Nothing to do */
        }

        if (((LucOldOutInSide == DEM_DTR_INSIDE)
            && (LucNewOutInSide == DEM_DTR_OUTSIDE_MAX))
            || ((LucOldOutInSide == DEM_DTR_OUTSIDE_MAX)
                && ((LucNewOutInSide == DEM_DTR_INSIDE)
                    || (LucNewOutInSide == DEM_DTR_OUTSIDE_MIN))))
        {
          /* @Trace: Dem_SUD_API_12969 */
          Dem_DtrData[DTRId].Upplimvalue = Dem_DtrData[DTRId].Upplimvalue
              - DEM_ONE;
        }
        else if (((LucOldOutInSide == DEM_DTR_INSIDE)
            && (LucNewOutInSide == DEM_DTR_OUTSIDE_MIN))
            || ((LucOldOutInSide == DEM_DTR_OUTSIDE_MIN)
                && ((LucNewOutInSide == DEM_DTR_INSIDE)
                    || (LucNewOutInSide == DEM_DTR_OUTSIDE_MAX))))
        {
          /* @Trace: Dem_SUD_API_00171 */
          Dem_DtrData[DTRId].Lowlimvalue = Dem_DtrData[DTRId].Lowlimvalue
              + DEM_ONE;
        }
        else
        {
          /* @Trace: Dem_SUD_API_12964 */
          /* Nothing to do */
        }
      }
      else if (Ctrlval != DEM_DTR_CTL_INVISIBLE)
      {
        /* @Trace: Dem_SUD_API_00172 */
        /* DEM_DTR_CTL_INVISIBLE Values are all ignored. This DTR is treated
         * for the external view (tester) as if not integrated.*/
        LddRetVal = E_NOT_OK;
      }
      else
      {
        /* @Trace: Dem_SUD_API_12977 */
        /* Nothing to do */
      }
    }
    #else
    /* @Trace: Dem_SUD_API_12962 */
    DEM_UNUSED(DTRId);
    DEM_UNUSED(LslTestResult);
    DEM_UNUSED(LslLowerLimit);
    DEM_UNUSED(LslUpperLimit);
    DEM_UNUSED(Ctrlval);
    #endif
  }

  return LddRetVal;
}

#endif

/*******************************************************************************
** Function Name        : Dem_DcmGetDTRData                                   **
**                                                                            **
** Service ID           : 0xa5                                                **
**                                                                            **
** Description          : Reports a DTR data along with TID-value, UaSID,     **
**                        test result with lower and upper limit.             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : Obdmid      - Identification of a DTR element by    **
**                                      assigned DTRId.                       **
**                        TIDindex    - Index of the TID within the DEM. Runs **
**                                      from 0 to "numberOfTIDs" obtained in  **
**                                      the call to                           **
**                                      Dem_DcmGetNumTIDsOfOBDMID()           **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : TIDvalue    - TID to be put on the tester reponse   **
**                        UaSID       - UaSID to be put on the tester reponse **
**                        Testvalue   - Latest test result                    **
**                        Lowlimvalue - Lower limit value associated to the   **
**                                      latest test result                   **
**                        Upplimvalue - Upper limit value associated to the   **
**                                      latest test result                   **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
#if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
FUNC(Std_ReturnType, DEM_CODE)
Dem_DcmGetDTRData(
    VAR(uint8, DEM_VAR) Obdmid,
    VAR(uint8, DEM_VAR) TIDindex,
    P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA) TIDvalue,
    P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA) UaSID,
    P2VAR(uint16, AUTOMATIC, DEM_APPL_DATA) Testvalue,
    P2VAR(uint16, AUTOMATIC, DEM_APPL_DATA) Lowlimvalue,
    P2VAR(uint16, AUTOMATIC, DEM_APPL_DATA) Upplimvalue
    )
{
  /* @Trace: SWS_Dem_00762
   * Upon request by the Dcm, the Dem shall respond with the data
   * available for a particular OBDMID / TIDindex per requested OBDMID using the
   * API Dem_DcmGetDTRData. This value can be used by the Dcm to iteratively
   * request for the DTR data per OBDMID / TIDindex starting from 0 to
   * numberofTIDs minus one.
   * */

  Std_ReturnType LddRetVal = E_NOT_OK;
  /* Module Initialization check */
  if (DEM_INIT != Dem_GucInit)
  {
    /* @Trace: Dem_SUD_API_12684 */
    /* Report to DET */
    DEM_REPORT_ERROR( DEM_DCMGETDTRDATA_SID, DEM_E_UNINIT);
  }
  else if ((NULL_PTR == TIDvalue) ||
           (NULL_PTR == UaSID) ||
           (NULL_PTR == Testvalue) ||
           (NULL_PTR == Lowlimvalue) ||
           (NULL_PTR == Upplimvalue) )
  {
    /* @Trace: Dem_SUD_API_12686 */
    DEM_REPORT_ERROR( DEM_DCMGETDTRDATA_SID, DEM_E_PARAM_POINTER);
  }
  else
  {
    #if (DEM_NUMBER_OF_DTRS > DEM_ZERO)
    /* @Trace: Dem_SUD_API_12688 */
    for (uint8 LucIdx = DEM_ZERO; LucIdx < DEM_NUMBER_OF_DTRS; LucIdx++)
    {
      /* @Trace: Dem_SUD_API_12689 */
      #if (DEM_AVAILABILITY_SUPPORT == DEM_EVENT_AVAILABILITY)
      /* @Trace: Dem_SUD_API_12690 */
      boolean LblEvIsAvailableTriggered = DEM_TRUE;
      #endif
      boolean LblEvIsSuppressionTriggered = DEM_FALSE;
      /* @Trace: Dem_SUD_API_12691 */
      if (DEM_NO_IDX_U16 != Dem_GaaDtrInfo[LucIdx].usEventId)
      {
        /* @Trace: Dem_SUD_API_12692 */
        #if (DEM_AVAILABILITY_SUPPORT == DEM_EVENT_AVAILABILITY)
        LblEvIsAvailableTriggered =
            Dem_EvIsProcStateTriggered(
                Dem_GaaDtrInfo[LucIdx].usEventId,
                DEM_EVPROCSTATE_EVENT_AVAILABLE);
        #endif
        LblEvIsSuppressionTriggered =
            Dem_EvIsProcStateTriggered(
                Dem_GaaDtrInfo[LucIdx].usEventId, DEM_EVPROCSTATE_DTC_SUPP);
      }
      /* @Trace: Dem_SUD_API_12685 */
      if ((Obdmid == Dem_GaaDtrInfo[LucIdx].usOBDMID) &&
         (TIDindex == Dem_GaaDtrInfo[LucIdx].usTIDIndex)
         #if (DEM_AVAILABILITY_SUPPORT == DEM_EVENT_AVAILABILITY)
         && (DEM_TRUE == LblEvIsAvailableTriggered)
         #endif
         && (DEM_TRUE != LblEvIsSuppressionTriggered)
        )
      {
        /* @Trace: Dem_SUD_API_12693 */
        *TIDvalue = Dem_GaaDtrInfo[LucIdx].usTID;
        *UaSID = Dem_GaaDtrInfo[LucIdx].usUaSID;
        *Testvalue = Dem_DtrData[LucIdx].Testvalue;
        *Lowlimvalue = Dem_DtrData[LucIdx].Lowlimvalue;
        *Upplimvalue = Dem_DtrData[LucIdx].Upplimvalue;
        LddRetVal = E_OK;
      }

    }
    #else
    /* @Trace: Dem_SUD_API_12687 */
    DEM_UNUSED(Obdmid);
    DEM_UNUSED(TIDindex);
    #endif
  }
  return LddRetVal;
}
#endif
/*******************************************************************************
** Function Name        : Dem_DcmGetNumTIDsOfOBDMID                           **
**                                                                            **
** Service ID           : 0xa4                                                **
**                                                                            **
** Description          : Gets the number of TIDs per (functional) OBDMID.    **
**                        This can be used by the DCM to iteratively request  **
**                        for OBD/TID result data within a loop from          **
**                        0....numberOfTIDs-1 API is needed in OBD-relevant   **
**                        ECUs only.                                          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : Obdmid         - OBDMID subject of the request to   **
**                                         identify the number of assigned    **
**                                         TIDs                               **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : numberOfTIDs   - Number of assigned TIDs for the    **
**                                         requested OBDMID. Used as loop     **
**                                         value for the DCM to retrieve all  **
**                                         OBD/TID result data.               **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
/* @Trace: SRS_Diag_04001
 */
#if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
FUNC(Std_ReturnType, DEM_CODE)
Dem_DcmGetNumTIDsOfOBDMID(
    VAR(uint8, DEM_VAR) Obdmid,
    P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA) numberOfTIDs
    )
{
  /* @Trace: SWS_Dem_00761
   * Upon request by the Dcm, the Dem shall repond with the number
   * of TIDs per requested OBDMID using the API Dem_DcmGetNumTIDsOfOBDMID.
   * This value can be used by the Dcm to iteratively request for the DTR
   * data per OBDMID / TID-index whereas the TID-index loops from 0
   * to number-of-TIDs minus one.*/
  Std_ReturnType LddRetVal = E_NOT_OK;
  /* Module Initialization check */
  if (DEM_INIT != Dem_GucInit)
  {
    /* @Trace: Dem_SUD_API_12678 */
    /* Report to DET */
    DEM_REPORT_ERROR( DEM_DCMGETNUMTIDSOFOBDMID_SID, DEM_E_UNINIT);
  }
  else if (NULL_PTR == numberOfTIDs)
  {
    /* @Trace: Dem_SUD_API_12679 */
    DEM_REPORT_ERROR( DEM_DCMGETNUMTIDSOFOBDMID_SID, DEM_E_PARAM_POINTER);
  }
  else
  {
    #if (DEM_NUMBER_OF_DTRS > DEM_ZERO)
    uint8 LucTmpNumberOfTids = DEM_ZERO;
    /* @Trace: Dem_SUD_API_12683 */
    for (uint8 LucIdx = DEM_ZERO; LucIdx < DEM_NUMBER_OF_DTRS; LucIdx++)
    {
      /* @Trace: Dem_SUD_API_12682 */
      if (Dem_GaaDtrInfo[LucIdx].usOBDMID == Obdmid)
      {
        /* @Trace: Dem_SUD_API_12681 */
        LucTmpNumberOfTids = LucTmpNumberOfTids + DEM_ONE;
      }
    }
    *numberOfTIDs = LucTmpNumberOfTids;
    LddRetVal = E_OK;
    #else
    /* @Trace: Dem_SUD_API_12680 */
    DEM_UNUSED(Obdmid);
    #endif
  }
  return LddRetVal;
}
#endif

/*******************************************************************************
** Function Name        : Dem_DcmGetAvailableOBDMIDs                          **
**                                                                            **
** Service ID           : 0xa3                                                **
**                                                                            **
** Description          : Reports the value of a requested "availability-     **
**                        OBDMID" to the DCM upon a Service $06 request.      **
**                        Derived from that the tester displays the supported **
**                        tests a mechanic can select from. API is needed in  **
**                        OBD-relevant ECUs only.                             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : Obdmid         - Availablity OBDMID ($00,$20,       **
**                                         $40...)                            **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : Obdmidvalue    - Bit coded information on the       **
**                                         support of OBDMIDs.                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
#if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
FUNC(Std_ReturnType, DEM_CODE)
Dem_DcmGetAvailableOBDMIDs(
    VAR(uint8, DEM_VAR) Obdmid,
    P2VAR(uint32, AUTOMATIC, DEM_APPL_DATA) Obdmidvalue
    )
{
  /* @Trace: SWS_Dem_01301
   * Behavior on invalid Obdmid value
   * If Dem_DcmGetAvailableOBDMIDs is called with an invalid Obdmid value which
   * is different to 0x00, 0x20, 0x40, 0x60, 0x80, 0xA0, 0xC0 or 0xE0, the Dem
   * shall report the Det development error DEM_E_INVALID_OBDMID.*/
  if (DEM_INIT != Dem_GucInit)
  {
    /* @Trace: Dem_SUD_API_12670 */
    /* Report to DET */
    DEM_REPORT_ERROR( DEM_DCMGETAVAILABLEOBDMIDS_SID, DEM_E_UNINIT);
  }
  else if (DEM_TRUE == Dem_IsValidOBDMid(Obdmid))
  {
    /* @Trace: Dem_SUD_API_12671 */
    DEM_REPORT_ERROR( DEM_DCMGETAVAILABLEOBDMIDS_SID, DEM_E_INVALID_OBDMID);
  }
  else if (NULL_PTR == Obdmidvalue)
  {
    /* @Trace: Dem_SUD_API_00137 */
    DEM_REPORT_ERROR( DEM_DCMGETAVAILABLEOBDMIDS_SID, DEM_E_PARAM_POINTER);
  }
  else
  {
    /* @Trace: SWS_Dem_00760
     * Computing available OBD MID values
     * If Dem_DcmGetAvailableOBDMIDs is called with an "availablity Obdmid"
     * value of 0x00, 0x20, 0x40, 0x60, 0x80, 0xA0, 0xC0 or 0xE0 and the Dem has
     * configured DemDtrMid, the Dem shall compute and provide the Supported-
     * OBDMID information in the OUT parameter Obdmidvalue and return E_OK.
     * The computed Obdmids parameter is according to ISO 15031-5[12] and sets
     * a bit for each supported Obdmid in the request range (starting with
     * Obdmid+1) and having the last bit of the Obdmidvalue set, if any
     * subsequent range has configured Obdmids.*/

    /* 00 ==> 01 - 20
     * 20 ==> 21 - 40
     * 40 ==> 41 - 60
     * 60 ==> 61 - 80
     * 80 ==> 81 - A0
     * A0 ==> A1 - C0
     * C0 ==> C1 - E0
     * E0 ==> E1 - FF*/
    /* @Trace: Dem_SUD_API_12672 */
    #if (DEM_NUMBER_OF_DTRS > DEM_ZERO)
    uint8 LaaValue[DEM_FOUR] = { DEM_ZERO, DEM_ZERO, DEM_ZERO, DEM_ZERO };
    for (uint8 LucByteIdx = DEM_ZERO; LucByteIdx < DEM_FOUR; LucByteIdx++)
    {
      /* @Trace: Dem_SUD_API_12674 */
      for (uint8 LucMidIdx = DEM_EIGHT; LucMidIdx > DEM_ZERO; LucMidIdx--)
      {
        /* @Trace: Dem_SUD_API_12675 */
        for (uint8 LucIdx = DEM_ZERO; LucIdx < DEM_NUMBER_OF_DTRS; LucIdx++)
        {
          uint8 LucOffset =
              Obdmid +
              (((LucByteIdx + DEM_ONE)* DEM_EIGHT) - (LucMidIdx - DEM_ONE));
              /* @Trace: Dem_SUD_API_12677 */
          if (Dem_GaaDtrInfo[LucIdx].usOBDMID == LucOffset )
          {
            /* @Trace: Dem_SUD_API_12676 */
            LaaValue[LucByteIdx] |= (DEM_ONE << (LucMidIdx - DEM_ONE));
          }
        }
      }
    }
    /* @Trace: Dem_SUD_API_12673 */
    uint8 * LpObdMidValue = NULL_PTR;
    LpObdMidValue = (uint8*)Obdmidvalue;
    *LpObdMidValue = LaaValue[DEM_ZERO];
    LpObdMidValue++;
    *LpObdMidValue = LaaValue[DEM_ONE];
    LpObdMidValue++;
    *LpObdMidValue = LaaValue[DEM_TWO];
    LpObdMidValue++;
    *LpObdMidValue = LaaValue[DEM_THREE];
    #endif
  }
  return E_OK;
}
#endif



/*******************************************************************************
** Function Name        : Dem_OBDReadDataOfTimeEngineStart                    **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : It used read data of time engine start              **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : uint8* Data                                         **
**                                                                            **
** Return parameter     : Std_Returntype                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Det_ReportError                                     **
*******************************************************************************/
/* polyspace +3 MISRA-C3:5.8 [Justified:Low] Justify with annotations */
#if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
FUNC(Std_ReturnType, DEM_CODE) Dem_OBDReadDataOfTimeEngineStart(
   P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA) Data)
{
  Std_ReturnType LddReturnValue;

  LddReturnValue = E_NOT_OK;
  if (NULL_PTR == Data)
  {
    /* @Trace: Dem_SUD_API_10677 */
    /* Report to DET */
    LddReturnValue = E_NOT_OK;
  }
  else
  {
    P2CONST(Dem_DataElementClassType, AUTOMATIC, DEM_CONST) LddDataElementEngineStart
      = Dem_GstGeneralOBDInfo[DEM_ZERO].pOBDTimeSinceEngineStart;
    /* @Trace: Dem_SUD_API_11823 */
    /* polyspace-begin MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] Same as Dead Code. */
    /* polyspace-begin DEFECT:DEAD_CODE [Justified:Low] */
    if (NULL_PTR != LddDataElementEngineStart)
    {
      /* @Trace: Dem_SUD_API_10678 */
      if (NULL_PTR != LddDataElementEngineStart->ReadFunc)
      {
        /* @Trace: Dem_SUD_API_11824 */
        LddDataElementEngineStart->ReadFunc(Data, DEM_ZERO);
        LddReturnValue = E_OK;
      }
      else
      {
        if (NULL_PTR != LddDataElementEngineStart->SRReadFunc)
        {
          LddDataElementEngineStart->SRReadFunc(Data);
          LddReturnValue = E_OK;
        }
      }
    }
    /* polyspace-end MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] Same as Dead Code. */
    /* polyspace-end DEFECT:DEAD_CODE [Justified:Low] */
  }
  return(LddReturnValue);
}
#endif

/*******************************************************************************
** Function Name        : Dem_OBDReadDataOfTravelDistance                     **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : It used read data of travel distance                **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : uint8* Data                                         **
**                                                                            **
** Return parameter     : Std_Returntype                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                                                                            **
**                        Function(s) invoked :                               **
**                                                                            **
*******************************************************************************/
/* polyspace +3 MISRA-C3:5.8 [Justified:Low] Justify with annotations */
#if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
FUNC(Std_ReturnType, DEM_CODE) Dem_OBDReadDataOfTravelDistance(
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA) Data)
{
  Std_ReturnType LddReturnValue;

  LddReturnValue = E_NOT_OK;
  if (NULL_PTR == Data)
  {
    /* @Trace: Dem_SUD_API_10675 */
    /* Report to DET */
    LddReturnValue = E_NOT_OK;
  }
  else
  {
    P2CONST(Dem_DataElementClassType, AUTOMATIC, DEM_CONST)
    LddDataElementDistance =
        Dem_GstGeneralOBDInfo[DEM_ZERO].pOBDInputDistanceInformation;
    /* @Trace: Dem_SUD_API_11825 */
    /* polyspace-begin MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] Same as Dead Code. */
    /* polyspace-begin DEFECT:DEAD_CODE [Justified:Low] */
    if (NULL_PTR != LddDataElementDistance)
    {
      /* @Trace: Dem_SUD_API_10676 */
      if (NULL_PTR != LddDataElementDistance->ReadFunc)
      {
        /* @Trace: Dem_SUD_API_11826 */
        LddDataElementDistance->ReadFunc(Data, DEM_ZERO);
        LddReturnValue = E_OK;
      }
      else
      {
        if (NULL_PTR != LddDataElementDistance->SRReadFunc)
        {
          LddDataElementDistance->SRReadFunc(Data);
          LddReturnValue = E_OK;
        }
      }
    }
    /* polyspace-end MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] Same as Dead Code. */
    /* polyspace-end DEFECT:DEAD_CODE [Justified:Low] */
  }
  return(LddReturnValue);
}
#endif
/*******************************************************************************
** Function Name        : Dem_DTR_Conversion_Linear                           **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : It used conversion liner for DTR                    **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : sint32 Value                                        **
**                        sint32 Value                                        **
**                        uint16 Num0                                         **
**                        uint16 Num1                                         **
**                        uint16 Denominator0                                 **
**                                                                            **
** InOut parameter      : uint16* CalcResult                                  **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_Returntype                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                                                                            **
**                        Function(s) invoked :                               **
**                                                                            **
*******************************************************************************/
#if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
FUNC(Std_ReturnType, DEM_CODE) Dem_DTR_Conversion_Linear(
  sint32 Value,
  uint16 Num0,
  uint16 Num1,
  uint16 Denominator0,
  uint16 * CalcResult)
{
  uint32 LulVal = (uint32) Value;
  Std_ReturnType LddReturnValue = E_OK;
  if ((DEM_ZERO != Num1) && (DEM_ZERO != Denominator0))
  {
    /* @Trace: Dem_SUD_API_11798 */
    if (LulVal > ((DEM_MAX_DENOMINATOR_NUMERATOR_VALUE) / ((uint32)Num1)))
    {
      /* @Trace: Dem_SUD_API_11799 */
      LddReturnValue = E_NOT_OK;
    }
    /* @Trace: Dem_SUD_API_11800 */
    if (E_OK == LddReturnValue)
    {
      *CalcResult = (((uint16)LulVal) * (Num1));
      if ((*CalcResult > ((DEM_MAX_DENOMINATOR_NUMERATOR_VALUE) - (Num0))))
      {
        /* @Trace: Dem_SUD_API_11801 */
        LddReturnValue = E_NOT_OK;
      }
      else
      {
        /* @Trace: Dem_SUD_API_11802 */
        *CalcResult = (*CalcResult + Num0)/(Denominator0);
      }
    }
  }
  else
  {
    /* @Trace: Dem_SUD_API_11797 */
    LddReturnValue = E_NOT_OK;
  }

  return LddReturnValue;
}
#endif

/*******************************************************************************
** Function Name        : Dem_IsValidOBDMid                                   **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : It used to check whether Obd mid is valid           **
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
** Return parameter     : boolean                                             **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                                                                            **
**                        Function(s) invoked :                               **
**                                                                            **
*******************************************************************************/
#if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
FUNC(boolean, DEM_CODE) Dem_IsValidOBDMid(uint8 Obdmid)
{
  boolean LblRetVal = DEM_FALSE;
  /* @Trace: Dem_SUD_API_11804 */
  if ((0x00U != Obdmid) &&\
      (0x20U != Obdmid) &&\
      (0x40U != Obdmid) &&\
      (0x60U != Obdmid) &&\
      (0x80U != Obdmid) &&\
      (0xA0U != Obdmid) &&\
      (0xC0U != Obdmid) &&\
      (0xE0U != Obdmid))
  {
    /* @Trace: Dem_SUD_API_11803 */
    LblRetVal = DEM_TRUE;
  }

  return LblRetVal;
}
#endif


/*******************************************************************************
** Function Name        : Dem_CalcPID41PerGroup                               **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : This function shall be used to calculate PID41      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : PID                                                 **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : PID41 Value of requested Group                      **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        Dem_GulEventIdDisabled                              **
**                                                                            **
**                        Function(s) invoked :                               **
*******************************************************************************/
/* @Trace: Dem_SUD_MACRO_153 */
#if ((DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT) && \
     ((DEM_PID01_BYTEB_LOWER_NIBBLE & 0x07U) != DEM_ZERO))
static FUNC(void, DEM_CODE) Dem_CalcPID41PerGroup(
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA) PIDValue,
  VAR(uint8, DEM_VAR) DisableGroupIndexinPID41,
  VAR(uint8, DEM_VAR) ReadinessGroup,
  VAR(uint8, DEM_VAR) CompletenessIndexinPID41
  )
{
    if (DEM_ZERO == (Dem_GulEventIdDisabled & DisableGroupIndexinPID41))
    {
      /* @Trace: Dem_SUD_API_11068 */
      *PIDValue = *PIDValue | DisableGroupIndexinPID41;

      Dem_CalcReadinessPIDValue(DEM_PID41_CALC, PIDValue, 
      CompletenessIndexinPID41, ReadinessGroup); 
    }
    else
    {
      /* @Trace: Dem_SUD_API_12624 */
      *PIDValue = *PIDValue & (~DisableGroupIndexinPID41);

      /* Bit-4 of byte2 is set to 1 if monitor is disabled */
      *PIDValue = *PIDValue | CompletenessIndexinPID41;
    }  
}
#endif

/*******************************************************************************
 ** Function Name       : Dem_CalcPID41PerGroupCheck                          **
 **                                                                           **
 ** Service ID          : None                                                **
 **                                                                           **
 ** Description         : API to calculate the value of PID 41                **
 **                                                                           **
 ** Sync/Async          : Synchronous                                         **
 **                                                                           **
 ** Re-entrancy         : Reentrant                                           **
 **                                                                           **
 ** Input Parameters    : DisableGroupID, OBDReadyGroupID,                    **
 **                       ReadinessCompletenessGroup, SupportedEnableGroup    **
 ** InOut parameter     : None                                                **
 **                                                                           **
 ** Output Parameters   : PID41ByteCAddr , PID41ByteDAddr                     **
 **                                                                           **
 ** Return parameter    : void                                                **
 **                                                                           **
 ** Preconditions       : None                                                **
 **                                                                           **
 ** Remarks             : Global Variable(s)  :                               **
 **                       Dem_GulEventIdDisabled                              **
 **                                                                           **
 **                       Function(s) invoked : None                          **
 *******************************************************************************/
#if ((DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT) && \
    ((DEM_PID01_BYTEC_SPARK != DEM_ZERO) || (DEM_PID01_BYTEC_COMPRESSION != DEM_ZERO)))
static FUNC(void, DEM_CODE) Dem_CalcPID41PerGroupCheck(
  VAR(uint16, DEM_VAR) DisableGroupID,
  VAR(uint8, DEM_VAR) OBDReadyGroupID,
  VAR(uint8, DEM_VAR) SupportedEnableGroup,
  VAR(uint8, DEM_VAR) ReadinessCompletenessGroup,
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA) PID41ByteCAddr,
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA) PID41ByteDAddr
  )
{
    if ((Dem_GulEventIdDisabled & DisableGroupID) !=
          DisableGroupID)
    {
      /* Trace: DEM_OBD_01_03 */
      Dem_CalcReadinessPIDValue(DEM_PID41_CALC, PID41ByteDAddr, 
      ReadinessCompletenessGroup, 
      OBDReadyGroupID);
      /*  monitoring Enabled */
      *PID41ByteCAddr = (*PID41ByteCAddr | SupportedEnableGroup);
    }
    else
    {
      /*  monitoring disabled */
      *PID41ByteCAddr = (*PID41ByteCAddr & ~SupportedEnableGroup);
      /*  monitoring uncomplete */
      *PID41ByteDAddr = (*PID41ByteDAddr | ReadinessCompletenessGroup);
    }
}
#endif


/*******************************************************************************
** Function Name        : Dem_DcmGetInfoTypeValue79                           **
**                                                                            **
** Service ID           : 0xc3                                                **
**                                                                            **
** Description          : Service to report the value of monitor activity     **
                          denominator PID computed by the Dem.                **
                          API is needed in OBD-relevant ECUs only.            ** 
                          API Availability:                                   **
                          This API will be available only if:                 **
                          ({ecucDem/DemGeneral.DemOBDSupport)}                **
                          != DEM_OBD_NO_OBD_SUPPORT)                          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : OpStatus: OpStatus "Only DCM_INITIAL will appear,   **
**                                    because this API behaves synchronous."  **
**                        DataValueBufferSize: The maximum number of data     **
**                                    bytes that can be written to the        ** 
**                                    DataValueBuffer When the function       **
**                                    returns, the value is updated with      **
**                                    the actual number of data bytes that    **
**                                    are written to the Data ValueBuffer     **
**                        DataValueBuffer: Buffer containing the contents     **
**                                    of the monitor activity denominator.    ** 
**                                    The buffer is provided by the caller    **
**                                    with the appropriate size.              **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        Dem_GucInit                                         **
**                        Dem_GaaIumprDenominator                             **
**                        Dem_GusGeneralDenominator                           **
**                        Dem_GusIgnitionCylCnt                               **
**                        Dem_GaaIumprNumerator                               **
**                                                                            **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Det_ReportError                                     **
*******************************************************************************/
#if (DEM_J1979_2_OBD_ON_UDS == STD_ON)
/* Trace: DEM_19792_06_16 */
#if ((DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT) && (DEM_NUMBER_OF_RATIO_INFO > DEM_ZERO))
/* polyspace +4 MISRA2012:8.13 [Justified:Low] Justify with annotations */
FUNC(Std_ReturnType, DEM_CODE) Dem_DcmGetInfoTypeValue79(
  VAR(Dcm_OpStatusType, AUTOMATIC) OpStatus,
  P2VAR (uint8, AUTOMATIC, DEM_APPL_DATA) DataValueBuffer,
  P2VAR (uint8, AUTOMATIC, DEM_APPL_DATA) DataValueBufferSize
  )
{
  VAR(Std_ReturnType, DEM_VAR) LddReturnValue = E_OK;
  VAR(uint8, DEM_VAR) LucIndex;

  /* Module Initialization check */
  if (DEM_INIT != Dem_GucInit)
  {
    /* @Trace: Dem_SUD_API_12553 */
    /* Report to DET */
    DEM_REPORT_ERROR( DEM_DCMGETINFOTYPEVALUE79_SID, DEM_E_UNINIT);
  }
  else if (DCM_INITIAL != OpStatus)
  {
    /* @Trace: Dem_SUD_API_12554 */
    /* Report to DET */
    DEM_REPORT_ERROR( DEM_DCMGETINFOTYPEVALUE79_SID, DEM_E_PARAM_CONFIG);
  }
  else if (NULL_PTR == DataValueBuffer)
  {
    /* @Trace: Dem_SUD_API_12555 */
    /* Report to DET */
    DEM_REPORT_ERROR( DEM_DCMGETINFOTYPEVALUE79_SID, DEM_E_PARAM_POINTER);
  }
  else if (NULL_PTR == DataValueBufferSize)
  {
    /* @Trace: Dem_SUD_API_12556 */
    /* Report to DET */
    DEM_REPORT_ERROR( DEM_DCMGETINFOTYPEVALUE79_SID, DEM_E_PARAM_POINTER);
  }
  else
  {
      /* @Trace: SWS_Dem_01369 in R21-11
      * Support of Monitor Activity Denominator dThe Dem shall calculate the data
      * for ITID "Monitor Activity Denominator" and provide it in the parameter 
      * of DataValueBuffer of the API Dem_DcmGetInfoTypeValue79.c
      * */
      LucIndex = DEM_ZERO;      
      /* Get the Monitor Activity Denominator, Index 0 */
      /* In General, MAD is Same in All Ratio */
      DataValueBuffer[LucIndex] = Dem_GaaMonitorActivityDenominator[LucIndex];
  }/* Det check */

  return(LddReturnValue);
}
#endif
#endif /* J19792 */
/*******************************************************************************
 ** Function Name       : Dem_ProcessMonitorActivityInhibitConditionCheck     **
 **                                                                           **
 ** Service ID          : None                                                **
 **                                                                           **
 ** Description         : Function is used to Calculate                       **
 **                       Inhibit Condition Monitor Activity N/D              **
 **                                                                           **
 ** Re-entrancy         : Reentrant                                           **
 **                                                                           **
 ** Input Parameters    : None                                                **
 **                                                                           **
 ** InOut parameter     : None                                                **
 **                                                                           **
 ** Output Parameters   : None                                                **
 **                                                                           **
 ** Return parameter    : None                                                **
 **                                                                           **
 ** Preconditions       : None                                                **
 **                                                                           **
 ** Remarks             :                                                     **
 *******************************************************************************/
/* @Trace: RS_Diag_04252 in R21-11
  Support of SAE J1979-2
 */
#if (DEM_J1979_2_OBD_ON_UDS == STD_ON)
/* Trace: DEM_19792_06_17 */
#if ((DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT) && (DEM_NUMBER_OF_RATIO_INFO > DEM_ZERO))
static FUNC(void, DEM_CODE)Dem_ProcessMonitorActivityInhibitConditionCheck(void)
{  
  VAR(uint16, DEM_VAR) LusIndex = DEM_ZERO;
  VAR(uint8, DEM_VAR) LucRatioIndex = DEM_ZERO;
  VAR(uint16, DEM_VAR) LusEventId = DEM_ZERO;
  VAR(boolean, DEM_VAR) LblPermission = DEM_FALSE;
  VAR(boolean, DEM_VAR) LblPendingOBDDTCisExist = DEM_FALSE;
  VAR(uint8, DEM_VAR) LucPendingOBDDRatioIndex = DEM_ZERO;
  P2CONST(Dem_CombinedDtcType, AUTOMATIC,  DEM_VAR) LddCbDTC;
  
  /* Check For ALL DTC, not Depend on DemEventMemorySet */
  for (LusIndex = DEM_ZERO; LusIndex < DEM_MAX_NUMBER_EVENT_ENTRY_PRI; LusIndex++)
  {
    LusEventId = Dem_PrimaryEventMemory[LusIndex].EventIdRef;
    if ((LusEventId != DEM_NO_EVENT) && (LusEventId != Dem_ObdMemoryId))
    {
      LddCbDTC = Dem_GetCbDTCByEventId(LusEventId);

      if ((DEM_IS_BIT_SET_UDSSTATUSBYTE(LusEventId, DEM_UDS_STATUS_PDTC)) &&
            ((LddCbDTC->ddDtcFormat == DEM_DTC_FORMAT_OBD) || 
            (LddCbDTC->ddDtcFormat == DEM_DTC_FORMAT_OBD_3BYTE))
        )
      {  
        /* Pending OBD DTC is Exist */
        LblPendingOBDDTCisExist = DEM_TRUE;          
        break;
      }
    }
  }
  
  /* Check Ratio Permission of All FID related with MonitorActivity */    
  for (LucRatioIndex = DEM_ZERO; LucRatioIndex < DEM_NUMBER_OF_RATIO_INFO; LucRatioIndex++)
  {
    /* Check Inhibit Condition - OBD(Event Can Mil-On) DTC Exist in Primary Memory */
    /* Check Only When Permit to Increase */
    /* Checking 1st index is enough to Check Num inhibit condition related with Pending OBD DTC(Event Can Mil-On) */
    if (DEM_IS_BIT_UNSET_MONITOR_ACTIVITY(Dem_GaaMonitorActivityDenominatorNeedCountedCycleEnd[LucRatioIndex], 
                                          DEM_MONITOR_ACTIVITY_DEN_INHIBIT) ||
        DEM_IS_BIT_UNSET_MONITOR_ACTIVITY(Dem_GaaMonitorActivityNumeratorNeedCountedCycleEnd[LucRatioIndex], 
                                          DEM_MONITOR_ACTIVITY_NUM_INHIBIT) )
    {
      if (LblPendingOBDDTCisExist == DEM_TRUE)
      {
        for(LucPendingOBDDRatioIndex = DEM_ZERO; LucPendingOBDDRatioIndex < DEM_NUMBER_OF_RATIO_INFO; LucPendingOBDDRatioIndex++)    
        {     
          /* Trace: DEM_19792_06_09 */
          /* If Pending OBD DTC Exist in Primary Memory, Monitor Activity Denominator cannot increase */
          DEM_SET_MONITOR_ACTIVITYBYTE(Dem_GaaMonitorActivityDenominatorNeedCountedCycleEnd[LucPendingOBDDRatioIndex],
                                        DEM_MONITOR_ACTIVITY_DEN_INHIBIT);
                      
          /* If Monitor Activity Denominator Increment flag is already set, reset the flag */
          if ( DEM_IS_BIT_SET_MONITOR_ACTIVITY(Dem_GaaMonitorActivityDenominatorNeedCountedCycleEnd[LucPendingOBDDRatioIndex],
                                      DEM_MONITOR_ACTIVITY_DEN_INCREMENT) )
          {
            /* Reset the Increment Bit */
            DEM_CLR_MONITOR_ACTIVITYBYTE(Dem_GaaMonitorActivityDenominatorNeedCountedCycleEnd[LucPendingOBDDRatioIndex],
                                      DEM_MONITOR_ACTIVITY_DEN_INCREMENT);
          }      
        
          /* If Pending OBD DTC Exist in Primary Memory, Monitor Activity Numerator cannot increase */
          DEM_SET_MONITOR_ACTIVITYBYTE(Dem_GaaMonitorActivityNumeratorNeedCountedCycleEnd[LucPendingOBDDRatioIndex],
                                        DEM_MONITOR_ACTIVITY_NUM_INHIBIT);
                        
          /* If Monitor Activity Numerator Increment flag is already set, reset the flag */
          if ( DEM_IS_BIT_SET_MONITOR_ACTIVITY(Dem_GaaMonitorActivityNumeratorNeedCountedCycleEnd[LucPendingOBDDRatioIndex],
                                        DEM_MONITOR_ACTIVITY_NUM_INCREMENT))
          {
              /* Reset the Increment Bit */
              DEM_CLR_MONITOR_ACTIVITYBYTE(Dem_GaaMonitorActivityNumeratorNeedCountedCycleEnd[LucPendingOBDDRatioIndex],
                                            DEM_MONITOR_ACTIVITY_NUM_INCREMENT);
          }  
        }
      } 

      SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();
      Dem_EventStatusNvRamData.MonitorActivityDenominatorNeedCountedCycleEnd[LucRatioIndex] = 
      Dem_GaaMonitorActivityDenominatorNeedCountedCycleEnd[LucRatioIndex];
      Dem_EventStatusNvRamData.MonitorActivityNumeratorNeedCountedCycleEnd[LucRatioIndex] = 
      Dem_GaaMonitorActivityNumeratorNeedCountedCycleEnd[LucRatioIndex];
      SchM_Exit_Dem_REQUEST_STATUS_PROTECTION(); 
    }
    
    /* Check Inhibit Condition - FIMFID per Ratio */
    /* Check Only When Permit to Increase */
    if (DEM_IS_BIT_UNSET_MONITOR_ACTIVITY(Dem_GaaMonitorActivityDenominatorNeedCountedCycleEnd[LucRatioIndex], 
                                              DEM_MONITOR_ACTIVITY_DEN_INHIBIT))
    {
      if (Dem_GaaRatioIdInfo[LucRatioIndex].ucRatioIdType == DEM_RATIO_OBSERVER)
          /* @&& (Dem_GusRatioFaultFound[LucRatioIndex] == DEM_FALSE)*/
      {
        Dem_GetFimPermission(LucRatioIndex, &LblPermission);
      }

      #if (DEM_FIM_INTEGRATED == STD_ON)
      /* @Trace: Dem_SUD_API_11767 */
      if (LblPermission == DEM_FALSE)
      #endif
      {
        /* If LblPermission is FALSE, Monitor Activity Denominator cannot increase */
        DEM_SET_MONITOR_ACTIVITYBYTE(Dem_GaaMonitorActivityDenominatorNeedCountedCycleEnd[LucRatioIndex]
                                        ,DEM_MONITOR_ACTIVITY_DEN_INHIBIT);
        /* If Increment flag is already set, reset the flag */
        if ( DEM_IS_BIT_SET_MONITOR_ACTIVITY(Dem_GaaMonitorActivityDenominatorNeedCountedCycleEnd[LucRatioIndex]
                                              ,DEM_MONITOR_ACTIVITY_DEN_INCREMENT) )
        {
          /* Reset the Increment Bit */
          DEM_CLR_MONITOR_ACTIVITYBYTE(Dem_GaaMonitorActivityDenominatorNeedCountedCycleEnd[LucRatioIndex],
                                    (DEM_MONITOR_ACTIVITY_DEN_INCREMENT));
          SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();
          Dem_EventStatusNvRamData.MonitorActivityDenominatorNeedCountedCycleEnd[LucRatioIndex] = 
          Dem_GaaMonitorActivityDenominatorNeedCountedCycleEnd[LucRatioIndex];
          SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();
        }
      }
    } 
  }
}
#endif
#endif /* J19792 */
/*******************************************************************************
 ** Function Name       : Dem_UpdateMonitorActivityRatio                           **
 **                                                                           **
 ** Service ID          : None                                                **
 **                                                                           **
 ** Description         : Function is used to update MAR                      **
 **                                                                           **
 ** Re-entrancy         : Reentrant                                           **
 **                                                                           **
 ** Input Parameters    : EventId, EventStatus                                **
 **                                                                           **
 ** InOut parameter     : None                                                **
 **                                                                           **
 ** Output Parameters   : None                                                **
 **                                                                           **
 ** Return parameter    : None                                                **
 **                                                                           **
 ** Preconditions       : None                                                **
 **                                                                           **
 ** Remarks             :                                                     **
 *******************************************************************************/
/* @Trace: RS_Diag_04252 in R21-11
  Support of SAE J1979-2
 */
#if (DEM_J1979_2_OBD_ON_UDS == STD_ON)
/* Trace: DEM_19792_06_08 */
#if ((DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT) && (DEM_NUMBER_OF_RATIO_INFO > DEM_ZERO))
FUNC(void, DEM_CODE)Dem_UpdateMonitorActivityRatio(void)
{
    /* Monitor-Activity */         
  VAR(uint8, DEM_VAR) LucRatioIndex = DEM_ZERO;                        

    for(LucRatioIndex = DEM_ZERO; LucRatioIndex < DEM_NUMBER_OF_RATIO_INFO; LucRatioIndex++)    
    {           
      /* If Set Monitor Activity Denominator Incremented Flag in this OC */
      if ( DEM_IS_BIT_SET_MONITOR_ACTIVITY(Dem_GaaMonitorActivityDenominatorNeedCountedCycleEnd[LucRatioIndex], 
                                              DEM_MONITOR_ACTIVITY_DEN_INCREMENT)  )     
      {
          /* Only can Incremented once for MINI-D */
          if (Dem_GaaMonitorActivityDenominator[LucRatioIndex] < 0xFFu)
          {
            Dem_GaaMonitorActivityDenominator[LucRatioIndex]++;
            SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();
            Dem_EventStatusNvRamData.MonitorActivityDenominator[LucRatioIndex] = Dem_GaaMonitorActivityDenominator[LucRatioIndex];   
            SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();
          }   
      }    
      
      /* If Set Monitor Activity Numerator Incremented Flag in this OC */
      if ( DEM_IS_BIT_SET_MONITOR_ACTIVITY(Dem_GaaMonitorActivityNumeratorNeedCountedCycleEnd[LucRatioIndex], 
                                            DEM_MONITOR_ACTIVITY_NUM_INCREMENT)  )   
      {
          if (Dem_GaaMonitorActivityNumerator[LucRatioIndex] < 0xFFu)
          {
              Dem_GaaMonitorActivityNumerator[LucRatioIndex]++;
              SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();
              Dem_EventStatusNvRamData.MonitorActivityNumerator[LucRatioIndex] = Dem_GaaMonitorActivityNumerator[LucRatioIndex];
              SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();
          }
      }

      /* Monitor Activity Ratio is Only Updated When MAD reached 0xFFu */
      if (Dem_GaaMonitorActivityDenominator[LucRatioIndex] == 0xFFu)
      {
          /* Calculate Monitor Activity Ratio */
          Dem_GaaMonitorActivityRatio[LucRatioIndex] = Dem_GaaMonitorActivityNumerator[LucRatioIndex];     
          /* Mini-N Reset, Mini-D will reset after Loop */
          Dem_GaaMonitorActivityNumerator[LucRatioIndex] = 0u;
          Dem_GaaMonitorActivityDenominator[LucRatioIndex] = 0u;

          SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();
          Dem_EventStatusNvRamData.MonitorActivityRatio[LucRatioIndex] = Dem_GaaMonitorActivityRatio[LucRatioIndex];
              Dem_EventStatusNvRamData.MonitorActivityNumerator[LucRatioIndex] = Dem_GaaMonitorActivityNumerator[LucRatioIndex];
          Dem_EventStatusNvRamData.MonitorActivityDenominator[LucRatioIndex] = Dem_GaaMonitorActivityDenominator[LucRatioIndex];   
          SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();
      }
    }
}
#endif
#endif /* J19792 */



/*******************************************************************************
 ** Function Name       : Dem_InitMonitorActivityRatio                           **
 **                                                                           **
 ** Service ID          : None                                                **
 **                                                                           **
 ** Description         : Function is used to Init Monitor Activity 
                              when Operation Cycle Start                      **
 **                                                                           **
 ** Re-entrancy         : Reentrant                                           **
 **                                                                           **
 ** Input Parameters    : EventId, EventStatus                                **
 **                                                                           **
 ** InOut parameter     : None                                                **
 **                                                                           **
 ** Output Parameters   : None                                                **
 **                                                                           **
 ** Return parameter    : None                                                **
 **                                                                           **
 ** Preconditions       : None                                                **
 **                                                                           **
 ** Remarks             :                                                     **
 *******************************************************************************/
/* @Trace: RS_Diag_04252 in R21-11
  Support of SAE J1979-2
 */
#if (DEM_J1979_2_OBD_ON_UDS == STD_ON)
/* Trace: DEM_19792_06_05 */
#if ((DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT) && (DEM_NUMBER_OF_RATIO_INFO > DEM_ZERO))
FUNC(void, DEM_CODE)Dem_InitMonitorActivityRatio(void)
{
  /* Monitor-Activity */
  VAR(uint16, DEM_VAR) LucRatioIndex = DEM_ZERO;

  /* Init MAR Status */
  for(LucRatioIndex = DEM_ZERO; LucRatioIndex < DEM_NUMBER_OF_RATIO_INFO; LucRatioIndex++)    
  {         
    DEM_CLR_MONITOR_ACTIVITYBYTE(Dem_GaaMonitorActivityNumeratorNeedCountedCycleEnd[LucRatioIndex], 
                                  (DEM_MONITOR_ACTIVITY_ALLBYTE));
    DEM_CLR_MONITOR_ACTIVITYBYTE(Dem_GaaMonitorActivityDenominatorNeedCountedCycleEnd[LucRatioIndex], 
                                  (DEM_MONITOR_ACTIVITY_ALLBYTE));  
    SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();
    Dem_EventStatusNvRamData.MonitorActivityDenominatorNeedCountedCycleEnd[LucRatioIndex] = 
          Dem_GaaMonitorActivityDenominatorNeedCountedCycleEnd[LucRatioIndex];
    Dem_EventStatusNvRamData.MonitorActivityNumeratorNeedCountedCycleEnd[LucRatioIndex] =
          Dem_GaaMonitorActivityNumeratorNeedCountedCycleEnd[LucRatioIndex];
    SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();
  }
}

#endif
#endif /* J19792 */


/*******************************************************************************
 ** Function Name       : Dem_DivideIumprRatioValue                           **
 **                                                                           **
 ** Service ID          : None                                                **
 **                                                                           **
 ** Description         : Num or Den have to Divided when Num or Den reached 
                          to 0xFFFF. Min Ratio or Min Index have to re-assigned**
 **                                                                           **
 ** Re-entrancy         : Reentrant                                           **
 **                                                                           **
 ** Input Parameters    : RatioID                                **
 **                                                                           **
 ** InOut parameter     : None                                                **
 **                                                                           **
 ** Output Parameters   : None                                                **
 **                                                                           **
 ** Return parameter    : None                                                **
 **                                                                           **
 ** Preconditions       : None                                                **
 **                                                                           **
 ** Remarks             :                                                     **
 *******************************************************************************/
/* Trace: DEM_OBD_09_03 */
#if ((DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT) && (DEM_NUMBER_OF_RATIO_INFO > DEM_ZERO))
static FUNC(void, DEM_CODE) Dem_DivideIumprRatioValue(
  VAR(Dem_RatioIdType, DEM_VAR) RatioID)
{
  if (Dem_GaaIumprDenominator[RatioID] != DEM_ZERO)
  {
    Dem_GaaIumprDenominator[RatioID] =
        (Dem_GaaIumprDenominator[RatioID] - DEM_ONE) / DEM_TWO;
  }
  if (Dem_GaaIumprNumerator[RatioID] != DEM_ZERO)
  {
    Dem_GaaIumprNumerator[RatioID] =
        (Dem_GaaIumprNumerator[RatioID] - DEM_ONE) / DEM_TWO;
  }
}
#endif /*((DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT) && (DEM_NUMBER_OF_RATIO_INFO > DEM_ZERO))*/

/*******************************************************************************
 ** Function Name       : Dem_CalCulateMinimumRatioPerGroup                   **
 **                                                                           **
 ** Service ID          : None                                                **
 **                                                                           **
 ** Description         : when denominator or numerator change, 
                          Check the Minimum Ratio Per Group
 **                                                                           **
 ** Re-entrancy         : Reentrant                                           **
 **                                                                           **
 ** Input Parameters    : RatioID                                **
 **                                                                           **
 ** InOut parameter     : None                                                **
 **                                                                           **
 ** Output Parameters   : None                                                **
 **                                                                           **
 ** Return parameter    : None                                                **
 **                                                                           **
 ** Preconditions       : None                                                **
 **                                                                           **
 ** Remarks             :                                                     **
 *******************************************************************************/
/* Trace: DEM_OBD_09_04 */
#if ((DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT) && (DEM_NUMBER_OF_RATIO_INFO > DEM_ZERO))
static FUNC(void, DEM_CODE) Dem_CalCulateMinimumRatioPerGroup(
  VAR(uint8, DEM_VAR) IumprGroupID)
{
  VAR(uint16, DEM_VAR) LusPerRatioIndex;
  VAR(uint16, DEM_VAR) LusPrevMinRatioId;
  VAR(float32, DEM_VAR) LusPrevMinRatioValue;
  VAR(float32, DEM_VAR) LusRatioValue;
  
  if (IumprGroupID < DEM_IUMPR_NONE)
  {
    LusPrevMinRatioId = Dem_GaaIumprMinimumRatioIDPerGroup[IumprGroupID];

    /* All Numerators in Same Group have to compared with Minimum Ratio */
    for ( LusPerRatioIndex = DEM_ZERO; 
          LusPerRatioIndex < DEM_NUMBER_OF_RATIO_INFO; 
          LusPerRatioIndex++)
    {
      /* Check this Ratio is Same Group */
      if (IumprGroupID == Dem_GaaRatioIdInfo[LusPerRatioIndex].ucIUMPRGroup)
      {
        if ((Dem_GaaIumprDenominator[LusPerRatioIndex] == DEM_ZERO) || (Dem_GaaIumprDenominator[LusPrevMinRatioId] == DEM_ZERO))
        {
          LusPrevMinRatioValue = (float32)Dem_GaaIumprNumerator[LusPrevMinRatioId];
          LusRatioValue = (float32)Dem_GaaIumprNumerator[LusPerRatioIndex];
        }
        else
        {
          LusPrevMinRatioValue = ((float32)Dem_GaaIumprNumerator[LusPrevMinRatioId] / (float32)Dem_GaaIumprDenominator[LusPrevMinRatioId]);
          LusRatioValue = ((float32)Dem_GaaIumprNumerator[LusPerRatioIndex] / (float32)Dem_GaaIumprDenominator[LusPerRatioIndex]);
        }
        
        /* Check Minimum Value */
        if (LusRatioValue < LusPrevMinRatioValue)
        {
          Dem_GaaIumprMinimumRatioIDPerGroup[IumprGroupID] = LusPerRatioIndex;
          Dem_GaaIumprUpdateFlagPerGroup[IumprGroupID] = DEM_TRUE;
        }
        else if (LusRatioValue > LusPrevMinRatioValue)
        {
          /* Do Nothing */
        }
        else 
      {

          if ( (Dem_GaaIumprNumerator[LusPerRatioIndex] > Dem_GaaIumprNumerator[LusPrevMinRatioId] ) || 
                  (Dem_GaaIumprDenominator[LusPerRatioIndex] > Dem_GaaIumprDenominator[LusPrevMinRatioId] )  )
          {
            Dem_GaaIumprMinimumRatioIDPerGroup[IumprGroupID] = LusPerRatioIndex;
            Dem_GaaIumprUpdateFlagPerGroup[IumprGroupID] = DEM_TRUE;
          }

        }
      }
    }
  }
}
#endif /*((DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT) && (DEM_NUMBER_OF_RATIO_INFO > DEM_ZERO))*/
/*******************************************************************************
 ** Function Name       : Dem_ProcessDen100ms                                 **
 **                                                                           **
 ** Service ID          : None                                                **
 **                                                                           **
 ** Description         : The function is used for incrementing of            ** 
 **                        denominator every 100ms                            **
 **                                                                           **
 ** Sync/Async          : Synchronous                                         **
 **                                                                           **
 ** Re-entrancy         : Reentrant                                           **
 **                                                                           **
 ** Input Parameters    : EventId                                             **
 **                                                                           **
 ** InOut parameter     : None                                                **
 **                                                                           **
 ** Output Parameters   : None                                                **
 **                                                                           **
 ** Return parameter    : void                                                **
 **                                                                           **
 ** Preconditions       : None                                                **
 **                                                                           **
 ** Remarks             : Global Variable(s)  :                               **
 **                       Dem_GaaOperationCycleIdsList, Dem_GaaRatioIdInfo    **
 **                       Dem_Event,Dem_GulEventIdDisabled                    **
 **                       Dem_GaaIumprDenominator, Dem_GaaIumprNumerator      **
 **                       Function(s) invoked :  None                         **
 ******************************************************************************/
/* @Trace: SRS_Diag_04001 SRS_Diag_04126 */
/* Trace: DEM_OBD_09_05 */
#if ((DEM_NUMBER_OF_RATIO_INFO > DEM_ZERO) && \
     (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT))
static FUNC(void, DEM_CODE) Dem_ProcessDen100ms(void)
{
  VAR(uint16, DEM_VAR) LusRatioCount = DEM_ZERO;
  VAR(uint8, DEM_VAR) LucIumprGroupId;
  VAR(boolean, DEM_VAR) LblPermission = DEM_FALSE;
  VAR(boolean, DEM_VAR) LblDirty = DEM_FALSE;
  VAR(Dem_EventIdType, DEM_VAR) EventId;
  VAR(Dem_UdsStatusByteType, DEM_VAR) LddEventStatusMask = DEM_ZERO;
  VAR(uint8, DEM_VAR) LucRatioIdIndex = DEM_ZERO;
  VAR(uint8, DEM_VAR) LucDenCond = DEM_IUMPR_DEN_STATUS_NOT_REACHED;
  #if (DEM_AVAILABILITY_SUPPORT == DEM_EVENT_AVAILABILITY)
   VAR(boolean, DEM_VAR) LblEventAvailable;
  #endif

  if (Dem_GblRatioInit == DEM_FALSE)
  {
    /* @Trace: SWS_Dem_00712
     * In master and optionally primary OBD ECUs, the Dem shall increment ECU
     * global internal general denominator depending on the denominator
     * DEM_IUMPR_GENERAL_OBDCOND, if available. Depending on the system
     * definition the global general denominator (and therefore the
     * DEM_IUMPR_GENERAL_OBDCOND) may not be needed in some or even all primary
     * ECUs. In such cases the DEM_IUMPR_GENERAL_OBDCOND is never set, and the
     * general denominator is stuck at 0 (and reporting of the InfoType $08 /
     * $0B is disabled in the Dcm).*/
    /* @Trace: SWS_Dem_00711
     * The Dem of the Master ECU shall calulate the IUMPR-Cycle Flag.*/
    #if ((DEM_OBD_SUPPORT == DEM_OBD_MASTER_ECU) || \
         (DEM_OBD_SUPPORT == DEM_OBD_PRIMARY_ECU))
         /* @Trace: Dem_SUD_API_11782 */
    if ((Dem_GusRatioDenCondState[DEM_IUMPR_GENERAL_OBDCOND] ==
           DEM_IUMPR_DEN_STATUS_REACHED))
    #endif
    {
      /* Trace: DEM_OBD_09_14*/
      Dem_GblRatioInit = DEM_TRUE;

      /* @Trace: Dem_SUD_API_11783 */
      if (Dem_GusGeneralDenominator < DEM_MAX_DENOMINATOR_NUMERATOR_VALUE)
      {
          /* @Trace: Dem_SUD_API_11785 */
          Dem_GusGeneralDenominator++;

          /* Trace: DEM_OBD_09_21*/
          if (Dem_GusGeneralDenominator == DEM_MAX_DENOMINATOR_NUMERATOR_VALUE)
          {
            Dem_GusGeneralDenominator = DEM_ZERO;
          }

          SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();
          Dem_EventStatusNvRamData.GeneralDenCnt = Dem_GusGeneralDenominator;
          SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();
          LblDirty = DEM_TRUE;  
      }
    }
  }


  for ( LucRatioIdIndex = DEM_ZERO; 
        LucRatioIdIndex < DEM_NUMBER_OF_RATIO_INFO; 
        LucRatioIdIndex++)
  {
    EventId = Dem_GaaRatioIdInfo[LucRatioIdIndex].rid_EventId;
    LddEventStatusMask = Dem_AllEventStatusByte[EventId];

    LucIumprGroupId = Dem_GaaRatioIdInfo[LucRatioIdIndex].ucIUMPRGroup;

    Dem_GetFimPermission(LucRatioIdIndex, &LblPermission);

    #if (DEM_AVAILABILITY_SUPPORT == DEM_EVENT_AVAILABILITY)
    LblEventAvailable = Dem_EvIsProcStateTriggered(EventId, DEM_EVPROCSTATE_EVENT_AVAILABLE);
    #endif

    #if (DEM_J1979_2_OBD_ON_UDS == STD_ON)
    /* Trace: DEM_19792_06_18 */
    /* @Trace: Dem_SUD_API_11773 */
    if ((LblPermission == DEM_TRUE)    
        #if ((DEM_NUMBER_OF_DEM_COMPONENT > DEM_ZERO) && \
             (DEM_NUMBER_OF_EVENTS > DEM_ZERO ))
        && (DEM_CAUSAL_FAULT != Dem_EvtDepdntStt[EventId - DEM_ONE])
        #endif        
        /* Check Inhibit Condition */  
        && (DEM_IS_BIT_UNSET_MONITOR_ACTIVITY(Dem_GaaMonitorActivityDenominatorNeedCountedCycleEnd[LucRatioIdIndex], 
                                            DEM_MONITOR_ACTIVITY_DEN_INHIBIT) &&
            DEM_IS_BIT_UNSET_MONITOR_ACTIVITY(Dem_GaaMonitorActivityDenominatorNeedCountedCycleEnd[LucRatioIdIndex], 
                                          DEM_MONITOR_ACTIVITY_DEN_INCREMENT) )                                              
        && (Dem_GusRatioDenCondState[DEM_IUMPR_GENERAL_OBDCOND] == DEM_IUMPR_DEN_STATUS_REACHED)
        && ((LddEventStatusMask & (Dem_UdsStatusByteType)DEM_UDS_STATUS_PDTC) !=
              (Dem_UdsStatusByteType)DEM_UDS_STATUS_PDTC)
        /* @Trace: SWS_Dem_01104
         * IUMPR ratios referring to an unavailable event shall neither be
         * computed nor reported.*/
        #if (DEM_AVAILABILITY_SUPPORT == DEM_EVENT_AVAILABILITY)
        && (DEM_TRUE == LblEventAvailable)
        #endif
      )
      {
          DEM_SET_MONITOR_ACTIVITYBYTE(Dem_GaaMonitorActivityDenominatorNeedCountedCycleEnd[LucRatioIdIndex],
                                      DEM_MONITOR_ACTIVITY_DEN_INCREMENT);    
          SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();
          Dem_EventStatusNvRamData.MonitorActivityDenominatorNeedCountedCycleEnd[LucRatioIdIndex] = 
          Dem_GaaMonitorActivityDenominatorNeedCountedCycleEnd[LucRatioIdIndex];
          SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();
          LblDirty = DEM_TRUE;
      }
      #endif /* J9792 */      

    /* @Trace: SWS_Dem_00299
     * As long as an event has Pending status, the Dem module shall
     * stop increasing the numerator and denominator.*/

    /* @Trace: SWS_Dem_01236
     * The Dem shall increment monitor internal denominators depending on
     * the DEM_IUMPR_GENERAL_INDIVIDUAL_DENOMINATOR, and additional conditions
     * if configured in DemIUMPRDenGroup a maximum of once per driving cycle,
     * and shall consider monitor specific conditions only for the cycle the
     * Release operation was called in.*/

    /* @Trace: SWS_Dem_01392
     * The IUMPR ratio shall be blocked whenever any of the Events linked
     * (via FunctionInhibitionConfiguration or through SummaryEvents) to one
     * of the FIDs referenced by DemFunctionIdRef is in state PENDING,
     * or any other event causal to this event (according to component
     * dependency structure) is in state PENDING (see DemComponentClassRef
     * referenced by DemDiagnosticEventRef).*/

    /* @Trace: SWS_Dem_00299
     * As long as an event has Pending status, the Dem module shall
     * stop increasing the numerator and denominator.*/

    /* @Trace: SWS_Dem_01236
     * The Dem shall increment monitor internal denominators depending on
     * the DEM_IUMPR_GENERAL_INDIVIDUAL_DENOMINATOR, and additional conditions
     * if configured in DemIUMPRDenGroup a maximum of once per driving cycle,
     * and shall consider monitor specific conditions only for the cycle the
     * Release operation was called in.*/

    /* @Trace: SWS_Dem_01392
     * The IUMPR ratio shall be blocked whenever any of the Events linked
     * (via FunctionInhibitionConfiguration or through SummaryEvents) to one
     * of the FIDs referenced by DemFunctionIdRef is in state PENDING,
     * or any other event causal to this event (according to component
     * dependency structure) is in state PENDING (see DemComponentClassRef
     * referenced by DemDiagnosticEventRef).*/

    /* Trace: DEM_OBD_09_15 */

//  @uint8 LucDenCond = DEM_IUMPR_DEN_STATUS_NOT_REACHED;
    switch (Dem_GaaRatioIdInfo[LucRatioIdIndex].ucIUMPRDenGroup)
    {
      /* @Trace: SWS_Dem_01236
      * The Dem shall increment monitor internal denominators depending on
      * the DEM_IUMPR_GENERAL_INDIVIDUAL_DENOMINATOR, and additional conditions
      * if configured in DemIUMPRDenGroup a maximum of once per driving cycle,
      * and shall consider monitor specific conditions only for the cycle the
      * Release operation was called in.*/

      /* @Trace: SWS_Dem_00943
      * DEM_IUMPR_GENERAL_INDIVIDUAL_DENOMINATOR - individual denominators to
      * support different conditions than the general denominator.
      * It acts on individual denominators and allows a different condition to b e set than
      * for the general denominator. If the standard individual denominator conditions 
      * differ from the general denominator conditions, 
      * they typically differ by a "fueled engine" criterion. */      
      /* polyspace-begin DEFECT:DEAD_CODE [Justified:Low] "Dead Code by Configuration" */
      case DEM_IUMPR_DEN_NONE:
          /* -> If Denominator Configuration is DEM_IUMPR_DEN_NONE,
          use DEM_IUMPR_GENERAL_INDIVIDUAL_DENOMINATOR (General Denominator + fueled engine operatoin 10 seconds?)          
          General Denominator is only used for Infotype $08, $0B*/
        if (Dem_GusRatioDenCondState[DEM_IUMPR_GENERAL_INDIVIDUAL_DENOMINATOR] == DEM_IUMPR_DEN_STATUS_REACHED)
        {
          LucDenCond = DEM_IUMPR_DEN_STATUS_REACHED;
        }
        break;
      /* polyspace-end DEFECT:DEAD_CODE [Justified:Low] "Dead Code by Configuration" */
      default:
        if (Dem_GusRatioDenCondState[DEM_IUMPR_GENERAL_INDIVIDUAL_DENOMINATOR] == DEM_IUMPR_DEN_STATUS_REACHED)
        {
          /* -> If Denominator Configuration is not DEM_IUMPR_DEN_NONE (Cold Start, Physical Condition, etc..),
          use Additional Condition */
          if (Dem_GusRatioDenCondState[Dem_GaaRatioIdInfo[LucRatioIdIndex].ucIUMPRDenGroup]
              == DEM_IUMPR_DEN_STATUS_REACHED)
          {
            LucDenCond = DEM_IUMPR_DEN_STATUS_REACHED;
          }
        }
        break;
    }
  
    /* Trace: DEM_OBD_09_24 */
    /* @Trace: Dem_SUD_API_11773 */
    if ((LblPermission == DEM_TRUE)    
        #if ((DEM_NUMBER_OF_DEM_COMPONENT > DEM_ZERO) && \
             (DEM_NUMBER_OF_EVENTS > DEM_ZERO ))
        && (DEM_CAUSAL_FAULT != Dem_EvtDepdntStt[EventId - DEM_ONE])
        #endif
        /* Trace: DEM_OBD_09_16 */
        && (LucDenCond == DEM_IUMPR_DEN_STATUS_REACHED)
        && (Dem_GaaIumprDenominatorIsCounted[LucRatioIdIndex] == DEM_FALSE)
        && ((LddEventStatusMask & (Dem_UdsStatusByteType)DEM_UDS_STATUS_PDTC) !=
              (Dem_UdsStatusByteType)DEM_UDS_STATUS_PDTC)

        /* @Trace: SWS_Dem_01104
         * IUMPR ratios referring to an unavailable event shall neither be
         * computed nor reported.*/
        #if (DEM_AVAILABILITY_SUPPORT == DEM_EVENT_AVAILABILITY)
        && (DEM_TRUE == LblEventAvailable)
        #endif
        )
    {
      /*In IUMPR, if either the numerator or denominator for a specific
       *component reaches the maximum value of 65535, both numbers shall
       *be divided by two before either is incremented again to avoid
       *overflow problems
       */
      /* @Trace: Dem_SUD_API_11774 */
      /* Trace: DEM_OBD_09_17 */
      if (Dem_GaaIumprDenominator[LucRatioIdIndex] ==
          DEM_MAX_DENOMINATOR_NUMERATOR_VALUE)
      {          
        Dem_DivideIumprRatioValue(LucRatioIdIndex);      
      }

      /* Increment the denominator for the requested group */
      /* @Trace: Dem_SUD_API_11776 */
      if (Dem_GaaIumprDenominatorIsCounted[LucRatioIdIndex] == DEM_FALSE) 
      {
        /* @Trace: Dem_SUD_API_11777 */
        Dem_GaaIumprDenominator[LucRatioIdIndex]++;
        Dem_GaaIumprDenominatorIsCounted[LucRatioIdIndex] = DEM_TRUE;
        Dem_CalCulateMinimumRatioPerGroup(LucIumprGroupId);
      }
      
      SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();
      Dem_EventStatusNvRamData.IumprDenominator[LucRatioIdIndex] =
          Dem_GaaIumprDenominator[LucRatioIdIndex];
      Dem_EventStatusNvRamData.IumprNumerator[LucRatioIdIndex] =
          Dem_GaaIumprNumerator[LucRatioIdIndex];         
      SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();  

      if (LucIumprGroupId < DEM_IUMPR_NONE)
      {
        SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();
        Dem_EventStatusNvRamData.IumprMinimumRatioIDPerGroup[LucIumprGroupId] =
          Dem_GaaIumprMinimumRatioIDPerGroup[LucIumprGroupId];    
        Dem_EventStatusNvRamData.IumprUpdateFlagPerGroup[LucIumprGroupId] =
          Dem_GaaIumprUpdateFlagPerGroup[LucIumprGroupId];
        SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();
      }


      LblDirty = DEM_TRUE;
    }
    /* @Trace: Dem_SUD_API_10723 */
    LusRatioCount++;
  }

  /* Loop for incrementing the denominator */
  /* @Trace: Dem_SUD_API_11772 */
  if (LblDirty == DEM_TRUE)
  {
    /* @Trace: Dem_SUD_API_11771 */
    Dem_EvMem_SetNonVolatieDataStatus(
        DEM_NVDATA_ALL_EVENT_STATUS_ID, DEM_EVMEM_STATUS_DIRTY_NVM);
    Dem_EvMem_TriggerWriteAllBlocks(); 
  }
}
#endif

#define DEM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
