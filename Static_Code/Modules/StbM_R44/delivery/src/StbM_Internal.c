/* polyspace +1 MISRA2012:1.1 [Not a defect:Low] "This rule is manually checked and has no impact." */
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
**  SRC-MODULE: StbM_Internal.c                                               **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Synchronized Time-Base Manager Module                 **
**                                                                            **
**  PURPOSE   : Provision of internal functions and their functionality.      **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision        Date                By              Description            **
********************************************************************************
** 1.0.7           14-Feb-2024         JWMoon          CP44-3634              **
** 1.0.5           30-Nov-2022         NamNT1          ASPICE-76              **
** 1.0.3           21-Jul-2022         ThuanVT         JIRA BUGCLASSIC-152,   **
**												  	   R44-Redmine #633	      **
** 1.0.1           15-Sep-2021         SHKim           #20096                 **
** 1.0.0     	   16-Dec-2020         SHKim           Initial Version        **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

/* StbM module header */
#include "StbM_Internal.h"

#include "StbM_Ram.h"

#include "StbM_Math.h"

#include "StbM_MacroFunction.h"

/* @Trace: SWS_StbM_00059 */
/* @Trace: SWS_StbM_00246 */
#if (STD_ON == STBM_ETHIF_GLOBAL_TIME_SUPPORT)
/* Ethernet Interface */
#include "EthIf.h"
#endif /* STD_ON == STBM_ETHIF_GLOBAL_TIME_SUPPORT */

/* @Trace: SWS_StbM_00426 */
/* Timer Driver file inclusion */
#include "Gpt.h"

/* OS module header */
#include "Os.h"

/* @Trace: SWS_StbM_00058 */
/* DET module header */
#include "Det.h"

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

/*******************************************************************************
** Function Name        : StbM_Internal_GetVirtualLocalTime                   **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Returns the Virtual Local Time of the referenced    **
**                           Time Base.                                       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : lusConfigPtr: ptr of  StbM_GaaTimeBaseConfig        **
**                        localTimePtr: StbM_VirtualLocalTimeType             **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : localTimePtr: StbM_VirtualLocalTimeType             **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : StbM_GaaOSTimeClockValue,     **
**                                StbM_GaaEthernetTimeClockValue              **
**                        Function(s) invoked : GetCounterValue,              **
**                                EthIf_GetCurrentTime,                       **
**                                StbM_Math_DiffOfTwoTimeStamp,               **
**                                StbM_Math_ConvertTimeStampToRaw             **
*******************************************************************************/
/* @Trace: RS_TS_00002, RS_TS_00008, RS_TS_00018, RS_TS_00021 */
#define STBM_START_SEC_CODE
#include "MemMap.h"

FUNC(Std_ReturnType, STBM_CODE) StbM_Internal_GetVirtualLocalTime(
  VAR(uint16, AUTOMATIC)lusConfigPtr,
  P2VAR(StbM_VirtualLocalTimeType, AUTOMATIC, STBM_APPL_DATA)localTimePtr)
{
  VAR(Std_ReturnType,AUTOMATIC)lddReturnVal;

  P2CONST(StbM_TimeBaseConfigType, AUTOMATIC, STBM_APPL_DATA)lpTimeBaseConfig;  
  /* Pointer declaration */ 
  P2CONST(StbM_OSTimeClockConfigType, AUTOMATIC, STBM_APPL_DATA)lpOsTimeConfig;
  P2VAR(StbM_OSTimeClockValueType, AUTOMATIC, STBM_APPL_DATA)lpOsTimeValue;
  #if (STD_ON == STBM_ETHIF_GLOBAL_TIME_SUPPORT)
  P2CONST(StbM_EthernetTimeClockConfigType, AUTOMATIC, STBM_APPL_DATA)lpEthernetTimeConfig;
  P2VAR(StbM_EthernetTimeClockValueType, AUTOMATIC, STBM_APPL_DATA)lpEthernetTimeValue;
  #endif /* STD_ON == STBM_ETHIF_GLOBAL_TIME_SUPPORT */ 
  
  VAR(StbM_LocalTimeHardwareType, AUTOMATIC)lddLocalTimeHardware;
  VAR(TickType,AUTOMATIC)lddNumTicks;
  VAR(uint32,AUTOMATIC)lddCurrentNumTicks;
  VAR(uint32,AUTOMATIC)lddPreviousNumTicks;
  VAR(uint32, AUTOMATIC)lulTickValue;
  #if (STD_ON == STBM_ETHIF_GLOBAL_TIME_SUPPORT)
  VAR(Eth_TimeStampQualType,AUTOMATIC)lddVilidityStatus;
  VAR(Eth_TimeStampType, AUTOMATIC)lucEthIfGetTime;
  VAR(StbM_TimeStampType, AUTOMATIC)lulEthTimeStamp;
  VAR(StbM_TimeStampType, AUTOMATIC)lulEthElapsedTime;
  #endif /* STD_ON == STBM_ETHIF_GLOBAL_TIME_SUPPORT */ 
  VAR(uint64, AUTOMATIC)lulTimeValue;
 
  /* Initialize initial value */ 
  lddNumTicks = (TickType)STBM_ZERO;

  lddReturnVal = E_OK;
  localTimePtr->nanosecondsLo = (uint32)STBM_ZERO;
  localTimePtr->nanosecondsHi = (uint32)STBM_ZERO;
  
  #if (STD_ON == STBM_ETHIF_GLOBAL_TIME_SUPPORT)
  lddVilidityStatus = ETH_INVALID;
  lucEthIfGetTime.secondsHi = STBM_ZERO;
  lucEthIfGetTime.seconds = STBM_ZERO;
  lucEthIfGetTime.nanoseconds = STBM_ZERO;
  STBM_INIT_TIMESTAMP(&lulEthTimeStamp);
  STBM_INIT_TIMESTAMP(&lulEthElapsedTime);
  #endif /* STD_ON == STBM_ETHIF_GLOBAL_TIME_SUPPORT */ 

  /* Get hardware clock config */  
  lpTimeBaseConfig = &StbM_GaaTimeBaseConfig[lusConfigPtr];
  /* polyspace +1 RTE:IDP [Not a defect:Low] "StbM_GaaTimeBaseConfig is verified and generated by Generator Tool" */
  lddLocalTimeHardware = lpTimeBaseConfig->ucLocalTimeHardware; /*polyspace MISRA-C:18.1 [Not a defect:Low] "StbM_GaaTimeBaseConfig is verified and generated by Generator Tool"*/

  /* Check local hardware type */        
  /* @Trace: StbM_SUD_API_411 */
  if((OS_FREERUNNING_SOURCE == lddLocalTimeHardware)
     ||(GPT_FREERUNNING_SOURCE == lddLocalTimeHardware))
  {
    /* Update counter id with configurations */
    lpOsTimeConfig = &StbM_GaaOsTimeClockConfig[lpTimeBaseConfig->usLocalTimeClockID];
    lpOsTimeValue = &StbM_GaaOsTimeClockValue[lpTimeBaseConfig->usLocalTimeClockID];
    lddReturnVal = GetCounterValue(lpOsTimeConfig->ddCounterID, &lddNumTicks);
    /* If no error dectected */
    /* polyspace +1 DEFECT:USELESS_IF MISRA-C3:14.3 [Not a defect:Low] "The value of lddReturnVal depends on the configurations" */
    if(E_OK == lddReturnVal)
    {   
      /* Calculate Count value */
      lddCurrentNumTicks = (uint32)lddNumTicks;
      lddPreviousNumTicks = lpOsTimeValue->ddPreviousTickCount;
      /* Check tickcount over */
      if(lddCurrentNumTicks >= lddPreviousNumTicks)
      {
        lulTickValue = lddCurrentNumTicks - lddPreviousNumTicks;
      }        
      /* @Trace: StbM_SUD_API_412 */
      else
      {
        lulTickValue = STBM_MAX_OF_UINT32 -
                (lddPreviousNumTicks - lddCurrentNumTicks);
      }    
      /* @Trace: SWS_StbM_00352 */
      /* Convert lulTickValue into nanoSeconds */
      lulTimeValue = (uint64)lulTickValue;
      /* polyspace +5 DEFECT:UINT_OVFL [Not a defect:Low] "ulNanoSecondsPerTick is verified by Generator Tool" */
      /* polyspace +4 CERT-C:INT30-C [Not a defect:Low] "ulNanoSecondsPerTick is verified by Generator Tool" */
      lulTimeValue = lulTimeValue * ((uint64)(lpOsTimeConfig->ulNanoSecondsPerTick));
      /* Back up Previous Value */       
      lpOsTimeValue->ddPreviousTimeValue = 
                    lpOsTimeValue->ddPreviousTimeValue + lulTimeValue;
      lpOsTimeValue->ddPreviousTickCount = lddCurrentNumTicks;
      /* Set output parameter */   
      localTimePtr->nanosecondsLo = (uint32)
                ((lpOsTimeValue->ddPreviousTimeValue) & STBM_64BIT_LSB_MASK);
      localTimePtr->nanosecondsHi = (uint32)
                (((lpOsTimeValue->ddPreviousTimeValue) & STBM_64BIT_MSB_MASK)
                                    >>STBM_THIRTY_TWO);
    }        
    /* @Trace: StbM_SUD_API_413 */
    else
    {
        /* Do nothing */
    }
  }
  /* @Trace: SWS_StbM_00178 */
  #if (STD_ON == STBM_ETHIF_GLOBAL_TIME_SUPPORT)      
  /* @Trace: StbM_SUD_API_414 */
  else if(ETH_FREERUNNING_SOURCE == lddLocalTimeHardware)
  {
    /* Get current time form Ethernet */
    lpEthernetTimeConfig = &StbM_GaaEthernetTimeClockConfig[lpTimeBaseConfig->usLocalTimeClockID];
    lddReturnVal = EthIf_GetCurrentTime(lpEthernetTimeConfig->ucCtrlIdx, 
                            &lddVilidityStatus, &lucEthIfGetTime);   
    /* If no error dectected */
    if(E_OK == lddReturnVal)
    {
      /* Check quality of HW time stamp */
      if(ETH_VALID == lddVilidityStatus)
      {    
        /* Do nothing */
      }
      else
      {
        lddReturnVal = E_NOT_OK;
      }
    }
    else
    {
      /* Do nothing */
    }
    if(E_OK == lddReturnVal)
    {
      lpEthernetTimeValue = &StbM_GaaEthernetTimeClockValue
                            [lpTimeBaseConfig->usLocalTimeClockID];
      if(STBM_FALSE == (lpEthernetTimeValue->blFirst))
      {
        /* For Eth local time, reset timelocal */ 
        lulTimeValue = STBM_ZERO;
        /* Mark first value */
        lpEthernetTimeValue->ddFirstValue.secondsHi = 
                            lucEthIfGetTime.secondsHi;
        lpEthernetTimeValue->ddFirstValue.seconds = 
                            lucEthIfGetTime.seconds;
        lpEthernetTimeValue->ddFirstValue.nanoseconds = 
                            lucEthIfGetTime.nanoseconds;
        lpEthernetTimeValue->blFirst = STBM_TRUE;
      }
      else
      {
        lulEthTimeStamp.secondsHi = lucEthIfGetTime.secondsHi;
        lulEthTimeStamp.seconds = lucEthIfGetTime.seconds;
        lulEthTimeStamp.nanoseconds = lucEthIfGetTime.nanoseconds; 
  
        lddReturnVal = StbM_Math_DiffOfTwoTimeStamp
                            (lpEthernetTimeValue->ddFirstValue, 
                            lulEthTimeStamp, &lulEthElapsedTime);
        /* Check if  lulEthTimeStamp >= lpEthernetTimeValue->ddFirstValue */
        if(E_OK == lddReturnVal)
        {
          StbM_Math_ConvertTimeStampToRaw(lulEthElapsedTime, &lulTimeValue);
        }
        else
        {
          /* Do nothing */
        }
      }
      /* Set output parameter */ 
      if(E_OK == lddReturnVal)
      {            
        localTimePtr->nanosecondsLo = (uint32)(lulTimeValue & 
                        STBM_64BIT_LSB_MASK);
        localTimePtr->nanosecondsHi = (uint32)((lulTimeValue & 
                        STBM_64BIT_MSB_MASK)>>STBM_THIRTY_TWO); 
      }
      else
      {
        /* Do nothing */
      }
    }      
    /* @Trace: StbM_SUD_API_415 */
    else
    {
      /* Do nothing */
    }
  }
  #endif /* STD_ON == STBM_ETHIF_GLOBAL_TIME_SUPPORT */     
  /* @Trace: StbM_SUD_API_416 */
  else
  {   
    localTimePtr->nanosecondsLo = (uint32)(STBM_ZERO);
    localTimePtr->nanosecondsHi = (uint32)(STBM_ZERO);
  }

  return (lddReturnVal);
} /* End of StbM_Internal_GetVirtualLocalTime(void) */

#define STBM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : StbM_Internal_GetCurrentTime                        **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Returns a time value (Local Time Base derived from  **
**                           Global Time Base) in standard format.            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : lusConfigPtr: ptr of  StbM_GaaTimeBaseConfig        **
**                        timeVltRx: StbM_VirtualLocalTimeType                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : timeStamp: StbM_TimeStampType                       **
**                        timeVlt: StbM_TimeStampType                         **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                                StbM_GaaTimeBaseValue                       **
**                                StbM_GaaEthernetTimeClockValue              **
**                        Function(s) invoked :                               **
**                                StbM_Internal_GetVirtualLocalTime           **
**                                StbM_Math_TimeStampInterpolate              **
**                                StbM_Math_SumOfTwoTimeStamp                 **
*******************************************************************************/
/* @Trace: RS_TS_00005, RS_TS_00006, RS_TS_00013, RS_TS_00014 */
#define STBM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, STBM_CODE) StbM_Internal_GetCurrentTime(
  VAR(uint16, AUTOMATIC)lusConfigPtr,
  P2VAR(StbM_TimeStampType, AUTOMATIC, STBM_APPL_DATA)timeStamp,
  P2VAR(StbM_VirtualLocalTimeType, AUTOMATIC, STBM_APPL_DATA)timeVlt,
  P2CONST(StbM_VirtualLocalTimeType, AUTOMATIC, STBM_APPL_DATA)timeVltRx)
{
  Std_ReturnType lddReturnVal;
  
  P2CONST(StbM_TimeBaseConfigType, AUTOMATIC, STBM_APPL_DATA)lpTimeBaseConfig;
  P2VAR(StbM_TimeBaseValueType, AUTOMATIC, STBM_APPL_DATA)lpTimeBaseValue;
  P2VAR(StbM_TimeBaseValueType, AUTOMATIC, STBM_APPL_DATA)lpSyncTimeBaseValue;
  VAR(StbM_SynchronizedTimeBaseType, AUTOMATIC)timeBaseId;
  VAR(StbM_SynchronizedTimeBaseType, AUTOMATIC)syncTimeBaseId;
  VAR(uint16, AUTOMATIC)lusSyncConfigPtr;
  VAR(StbM_TimeStampType, AUTOMATIC)lddTimeStamp;
  VAR(StbM_TimeStampType, AUTOMATIC)lddSyncTimeStamp;
  VAR(StbM_TimeStampType, AUTOMATIC)lddOffsetTimeStamp;
  VAR(StbM_VirtualLocalTimeType, AUTOMATIC)lddVlt;
  VAR(StbM_VirtualLocalTimeType, AUTOMATIC)lddVltInput;
  VAR(StbM_VirtualLocalTimeType, AUTOMATIC)lddSyncVlt;
  
  STBM_INIT_TIMESTAMP(&lddOffsetTimeStamp);
  STBM_INIT_TIMESTAMP(&lddSyncTimeStamp);
  /* Get Virtual local time */ 
  lddReturnVal = StbM_Internal_GetVirtualLocalTime(lusConfigPtr, &lddVlt); 
  /* Check option for calculte Time Sync */
  if(NULL_PTR == timeVltRx)
  {
    STBM_COPY_VLTIME(&lddVltInput, &lddVlt);
  }   
  /* @Trace: StbM_SUD_API_425 */
  else
  {
    STBM_COPY_VLTIME(&lddVltInput, timeVltRx);
  }
  /* Check if don't have error when get VLT*/
  /* @Trace: SWS_StbM_00434*/     
  /* @Trace: StbM_SUD_API_421 */
  if((E_OK == lddReturnVal) && (lusConfigPtr < STBM_NUMBER_TIME_BASES_CONFIGURED))
  { 
    lpTimeBaseValue = &StbM_GaaTimeBaseValue[lusConfigPtr];
    lddReturnVal =StbM_Math_TimeStampInterpolate(lpTimeBaseValue->ddRate,
              StbM_GaaTimeTuple[lusConfigPtr], lddVltInput,&lddTimeStamp);
    /* Check Time Base is offset time */
    lpTimeBaseConfig = &StbM_GaaTimeBaseConfig[lusConfigPtr];
    timeBaseId = lpTimeBaseConfig->ddTimeBaseId; 
    /* @Trace: StbM_SUD_API_422 */
    if((timeBaseId >= STBM_SIXTEEN) &&         
             (timeBaseId <= STBM_MAX_OFFSET_TIME_BASES_CONFIGURED))
    {  
      /* @Trace: SWS_StbM_00177 */
      STBM_COPY_TIMESTAMP(&lddOffsetTimeStamp, &lddTimeStamp);
      /* Get Sync Time Base address*/      
      syncTimeBaseId = lpTimeBaseConfig->ddSyncTimeBaseId; 
      STBM_GET_ADDRESS_SYNC_TIME_BASES_CONFIGURED(syncTimeBaseId,lusSyncConfigPtr);  
      /* Get Hardware Local time of Sync Time Base */
      lddReturnVal = StbM_Internal_GetVirtualLocalTime(lusSyncConfigPtr, &lddSyncVlt); 
      /* Check if time base don't have VLT*/
      /* polyspace +1 MISRA-C3:14.3 [Not a defect:Low] "The value of lddReturnVal depends on the configurations" */
      if(E_OK == lddReturnVal)
      { 
        /* Cal Time current of Sync time base */
        lpSyncTimeBaseValue = &StbM_GaaTimeBaseValue[lusSyncConfigPtr];
        lddReturnVal =StbM_Math_TimeStampInterpolate(lpSyncTimeBaseValue->ddRate,
              StbM_GaaTimeTuple[lusSyncConfigPtr], lddSyncVlt,&lddSyncTimeStamp);
        if(E_OK == lddReturnVal)
        {    
          StbM_Math_SumOfTwoTimeStamp(lddOffsetTimeStamp, lddSyncTimeStamp, &lddTimeStamp);
        }
        /* @Trace: StbM_SUD_API_423 */
        else
        {
          /* Do nothing */ 
        }
      }
      /* @Trace: StbM_SUD_API_424 */
      else
      {
        /* Do nothing */ 
      }
    }
    else
    {
      /* Do nothing */
    }   
  }
  else
  {
    lddReturnVal = E_NOT_OK;
  }
    
  /* @Trace: StbM_SUD_API_426 */
  if(E_OK == lddReturnVal)
  {
    STBM_COPY_TIMESTAMP(timeStamp, &lddTimeStamp);
    if(NULL_PTR != timeVlt)
    {
      STBM_COPY_VLTIME(timeVlt, &lddVlt);
    }   
    /* @Trace: StbM_SUD_API_427 */
    else
    {
      /* Do nothing */
    }   
  }
  /* @Trace: StbM_SUD_API_428 */
  else
  {
    /* return zero in fail case */
    timeStamp->nanoseconds = STBM_ZERO;
    timeStamp->seconds = STBM_ZERO;
    timeStamp->secondsHi = STBM_ZERO;
  } 
  
  return (lddReturnVal);
} /* End of StbM_Internal_GetCurrentTime(void) */

#define STBM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : StbM_Internal_WriteTimeRecordTable                  **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Store a package data into Recording Table Block     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : lusConfigPtr: ptr of  StbM_GaaTimeBaseConfig        **
**                        globalTime: StbM_TimeStampType                      **
**                        timeBaseStatus: StbM_TimeBaseStatusType             **
**                        localTime: Only for Sync TimeBase                   **
**                        virtualTime: Only for Sync TimeBase                 **
**                        measureDataPtr: Only for Sync TimeBase              **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : STD_ON == STBM_TIME_RECORDING_SUPPORT               **
**                                                                            **
** Remarks              : Global Variable(s)  : None                          **
**                        Function(s) invoked :                               **
**                                StbM_Internal_CalRateDeviation              **
**                                StbM_Internal_RecordSyncTimeBase            **
**                                StbM_Internal_RecordOffsetTimeBase          **
*******************************************************************************/
/* @Trace: RS_TS_00024, RS_TS_00026, RS_TS_00034,  RS_TS_00035, RS_TS_00036  */
#if(STD_ON == STBM_TIME_RECORDING_SUPPORT)

#define STBM_START_SEC_CODE
#include "MemMap.h"

FUNC(void, STBM_CODE) StbM_Internal_WriteTimeRecordTable(
  VAR(uint16, AUTOMATIC)lusConfigPtr,
  VAR(StbM_TimeStampType, AUTOMATIC)globalTime,
  VAR(StbM_TimeBaseStatusType, AUTOMATIC)timeBaseStatus,
  #if(STBM_ZERO < STBM_NUMBER_SYNC_TIME_RECORD_TABLE_CONFIGURED)
  VAR(StbM_TimeStampType, AUTOMATIC)localTime, 
  VAR(StbM_VirtualLocalTimeType, AUTOMATIC)virtualTime, 
  VAR(StbM_MeasurementType, AUTOMATIC)measureDataPtr
  #endif /* STBM_ZERO < STBM_NUMBER_SYNC_TIME_RECORD_TABLE_CONFIGURED */
  )
{
  P2CONST(StbM_TimeBaseConfigType, AUTOMATIC, STBM_APPL_DATA)lpTimeBaseConfig;

  #if(STBM_ZERO < STBM_NUMBER_SYNC_TIME_RECORD_TABLE_CONFIGURED)
  VAR(StbM_RateDeviationType, AUTOMATIC)lusRate;
  #endif /* STBM_ZERO < STBM_NUMBER_SYNC_TIME_RECORD_TABLE_CONFIGURED */
 
  /* Get address of TimeBaseConfig */  
  lpTimeBaseConfig = &StbM_GaaTimeBaseConfig[lusConfigPtr];
  /* @Trace: SWS_StbM_00428 */
  /* Condition STBM_FALSE == (lpTimeBaseConfig->enSystemWideTimeMasterSlave) */
  /* is checked by Generation tool*/
  /* @Trace: StbM_SUD_API_431 */
  if(STBM_BASE_INVAILD != lpTimeBaseConfig->ucBaseOfRecording)
  {
    /* @Trace: SWS_StbM_00312 */
    if(lusConfigPtr < STBM_NUMBER_SYNC_TIME_BASES_CONFIGURED)
    {
      #if(STBM_ZERO < STBM_NUMBER_SYNC_TIME_RECORD_TABLE_CONFIGURED)
      (void) StbM_Internal_CalRateDeviation(lusConfigPtr, &(lusRate));
      /* @Trace: SWS_StbM_00314 */
      /* @Trace: SWS_StbM_00313 */  
      StbM_Internal_RecordSyncTimeBase(lpTimeBaseConfig->ucBaseOfRecording,
            globalTime.seconds, globalTime.nanoseconds, timeBaseStatus, 
            virtualTime.nanosecondsLo, lusRate,
            localTime.seconds, localTime.nanoseconds, measureDataPtr.pathDelay
            );
     #endif /* STBM_ZERO < STBM_NUMBER_SYNC_TIME_RECORD_TABLE_CONFIGURED */
    }
    /* @Trace: StbM_SUD_API_432 */
    else 
    /* Don't need to check */
    /* (lusConfigPtr < (STBM_NUMBER_SYNC_TIME_BASES_CONFIGURED + */
    /*                  STBM_NUMBER_OFFSET_TIME_BASES_CONFIGURED)*/
    /* This condition is check at StbM_BusSetGlobalTime */
    {
      #if(STBM_ZERO < STBM_NUMBER_OFFSET_TIME_RECORD_TABLE_CONFIGURED)
      /* @Trace: SWS_StbM_ */
      StbM_Internal_RecordOffsetTimeBase(lpTimeBaseConfig->ucBaseOfRecording,
            globalTime.seconds, globalTime.nanoseconds, timeBaseStatus); 
      #endif /* STBM_ZERO < STBM_NUMBER_OFFSET_TIME_RECORD_TABLE_CONFIGURED */
    }
  }
  /* @Trace: StbM_SUD_API_433 */
  else
  {
    /* Do nothing */
  }
} /* End of StbM_Internal_WriteTimeRecordTable(void) */

#define STBM_STOP_SEC_CODE
#include "MemMap.h"

#endif  /* STD_ON == STBM_TIME_RECORDING_SUPPORT */ 
/*******************************************************************************
** Function Name        : StbM_Internal_RecordSyncTimeBase                    **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Store a package data into Sync Recording Table Block**
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : ucBaseOfRecording: ptr of                           **
**                                     StbM_GaaSyncTimeRecordingConfig        **
**                        GlbSeconds: a part of  Sync Recording data          **
**                        GlbNanoSeconds: a part of  Sync Recording data      **
**                        TimeBaseStatus: a part of  Sync Recording data      **
**                        VirtualLocalTimeLow: a part of  Sync Recording data **
**                        RateDeviation: a part of  Sync Recording data       **
**                        LocSeconds: a part of  Sync Recording data          **
**                        LocNanoSeconds: a part of  Sync Recording data      **
**                        PathDelay: a part of  Sync Recording data           **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : STD_ON == STBM_TIME_RECORDING_SUPPORT               **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                                StbM_GaaSyncRecordValue                     **
**                        Function(s) invoked : None                          **
*******************************************************************************/
/* @Trace: RS_TS_00024,  RS_TS_00034  */
#if(STD_ON == STBM_TIME_RECORDING_SUPPORT) 

#define STBM_START_SEC_CODE
#include "MemMap.h"

FUNC(void, STBM_CODE) StbM_Internal_RecordSyncTimeBase(
  VAR(uint8, AUTOMATIC)ucBaseOfRecording,
  VAR(uint32, AUTOMATIC)GlbSeconds,
  VAR(uint32, AUTOMATIC)GlbNanoSeconds,
  VAR(uint8, AUTOMATIC)TimeBaseStatus, 
  VAR(uint32, AUTOMATIC)VirtualLocalTimeLow, 
  VAR(sint16, AUTOMATIC)RateDeviation, 
  VAR(uint32, AUTOMATIC)LocSeconds, 
  VAR(uint32, AUTOMATIC)LocNanoSeconds, 
  VAR(uint32, AUTOMATIC)PathDelay)
{
  P2CONST(StbM_SyncTimeRecordingConfigType, AUTOMATIC, STBM_APPL_DATA)
                                lpTimeRecordConfig;
  
  P2VAR(StbM_SyncRecordTableBlockType, AUTOMATIC, STBM_APPL_DATA)lpSyncRecord;
  P2VAR(StbM_TimeRecordingValueType, AUTOMATIC, STBM_APPL_DATA)lpTimeRecordValue;
  
  
  /* Get address of TimeBaseConfig */  
  lpTimeRecordConfig = &(StbM_GaaSyncTimeRecordingConfig[ucBaseOfRecording]);
  lpTimeRecordValue = &(StbM_GaaSyncRecordValue[ucBaseOfRecording]);
  lpSyncRecord = &(lpTimeRecordConfig->pAddress[lpTimeRecordValue->ulPtr]);

  /* @Trace: SWS_StbM_00314 */
  /* polyspace +1 RTE:IDP [Not a defect:Low] "StbM_GaaTimeBaseConfig is verified and generated by Generator Tool" */
  lpSyncRecord->GlbSeconds = GlbSeconds; /*polyspace MISRA-C:18.1 [Not a defect:Low] "StbM_GaaSyncTimeRecordingConfig is verified and generated by Generator Tool"*/
  lpSyncRecord->GlbNanoSeconds = GlbNanoSeconds;
  lpSyncRecord->TimeBaseStatus = TimeBaseStatus;
  lpSyncRecord->VirtualLocalTimeLow = VirtualLocalTimeLow;
  lpSyncRecord->RateDeviation = RateDeviation;
  /* @Trace: SWS_StbM_00313 */
  lpSyncRecord->LocSeconds = LocSeconds;
  lpSyncRecord->LocNanoSeconds = LocNanoSeconds;
  lpSyncRecord->PathDelay = PathDelay;
  /* Calculate write ptr */
  lpTimeRecordValue->ulPtr = lpTimeRecordValue->ulPtr + STBM_ONE;
  /* @Trace: StbM_SUD_API_441 */
  if((lpTimeRecordValue->ulPtr) == (lpTimeRecordConfig->usCount))
  {
    lpTimeRecordValue->ulPtr = STBM_ZERO;
    lpTimeRecordValue->blOver = STBM_TRUE;
  }
  /* @Trace: StbM_SUD_API_442 */
  else
  {
    /* Do nothing */  
  }
} /* End of StbM_Internal_RecordSyncTimeBase(void) */

#define STBM_STOP_SEC_CODE
#include "MemMap.h"

#endif  /* STD_ON == STBM_TIME_RECORDING_SUPPORT */ 

/*******************************************************************************
** Function Name        : StbM_Internal_RecordOffsetTimeBase                  **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Store package data into Offset Recording Table Block**
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : ucBaseOfRecording: ptr of                           **
**                                     StbM_GaaOffsetTimeRecordingConfig      **
**                        GlbSeconds: a part of  Offset Recording data        **
**                        GlbNanoSeconds: a part of  Offset Recording data    **
**                        TimeBaseStatus: a part of  Offset Recording data    **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : STD_ON == STBM_TIME_RECORDING_SUPPORT               **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                                StbM_GaaOffsetRecordValue                   **
**                        Function(s) invoked : None                          **
*******************************************************************************/
/* @Trace: RS_TS_00024,  RS_TS_00034  */
#if((STD_ON == STBM_TIME_RECORDING_SUPPORT) && (STBM_ZERO < STBM_NUMBER_OFFSET_TIME_RECORD_TABLE_CONFIGURED))

#define STBM_START_SEC_CODE
#include "MemMap.h"

FUNC(void, STBM_CODE) StbM_Internal_RecordOffsetTimeBase(
  VAR(uint8, AUTOMATIC)ucBaseOfRecording,
  VAR(uint32, AUTOMATIC)GlbSeconds,
  VAR(uint32, AUTOMATIC)GlbNanoSeconds,
  VAR(uint8, AUTOMATIC)TimeBaseStatus)
{
  P2CONST(StbM_OffsetTimeRecordingConfigType, AUTOMATIC, STBM_APPL_DATA)
                                lpTimeRecordConfig;
  
  P2VAR(StbM_OffsetRecordTableBlockType, AUTOMATIC, STBM_APPL_DATA)lpOffsetRecord;
  P2VAR(StbM_TimeRecordingValueType, AUTOMATIC, STBM_APPL_DATA)lpTimeRecordValue;
  
  /* Get address of TimeBaseConfig */  
  lpTimeRecordConfig = &(StbM_GaaOffsetTimeRecordingConfig[ucBaseOfRecording]);
  lpTimeRecordValue = &(StbM_GaaOffsetRecordValue[ucBaseOfRecording]);
  lpOffsetRecord = &(lpTimeRecordConfig->pAddress[lpTimeRecordValue->ulPtr]);

  /* @Trace: SWS_StbM_00388 */
  /* polyspace +1 RTE:IDP [Not a defect:Low] "StbM_GaaTimeBaseConfig is verified and generated by Generator Tool" */
  lpOffsetRecord->GlbSeconds = GlbSeconds; /*polyspace MISRA-C:18.1 [Not a defect:Low] "StbM_GaaOffsetTimeRecordingConfig is verified and generated by Generator Tool"*/
  lpOffsetRecord->GlbNanoSeconds = GlbNanoSeconds;
  lpOffsetRecord->TimeBaseStatus = TimeBaseStatus;
  /* Calculate write ptr */
  lpTimeRecordValue->ulPtr = lpTimeRecordValue->ulPtr + STBM_ONE;
  /* @Trace: StbM_SUD_API_451 */
  if((lpTimeRecordValue->ulPtr) == (lpTimeRecordConfig->usCount))
  {
    lpTimeRecordValue->ulPtr = STBM_ZERO;
    lpTimeRecordValue->blOver = STBM_TRUE;
  }
  /* @Trace: StbM_SUD_API_452 */
  else
  {
    /* Do nothing */  
  }
} /* End of StbM_Internal_RecordOffsetTimeBase(void) */

#define STBM_STOP_SEC_CODE
#include "MemMap.h"

#endif  /* (STD_ON == STBM_TIME_RECORDING_SUPPORT) && (STBM_ZERO < STBM_NUMBER_OFFSET_TIME_RECORD_TABLE_CONFIGURED) */


/*******************************************************************************
** Function Name        : StbM_Internal_ReadTimeRecordTable                   **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Read all Recording data and pass them into call     **
**                           back function                                    **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : lusConfigPtr: ptr of StbM_GaaTimeBaseConfig         **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : STD_ON == STBM_TIME_RECORDING_SUPPORT               **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                                StbM_GaaSyncRecordValue                     **
**                                StbM_GaaOffsetRecordValue                   **
**                        Function(s) invoked : None                          **
*******************************************************************************/
/* @Trace: RS_TS_00034 */
#if(STD_ON == STBM_TIME_RECORDING_SUPPORT) 

#define STBM_START_SEC_CODE
#include "MemMap.h"

FUNC(void, STBM_CODE) StbM_Internal_ReadTimeRecordTable(
  VAR(uint16, AUTOMATIC)lusConfigPtr)
{
  P2CONST(StbM_TimeBaseConfigType, AUTOMATIC, STBM_APPL_DATA)lpTimeBaseConfig;
  P2CONST(StbM_SyncTimeRecordingConfigType, AUTOMATIC, STBM_APPL_DATA)
                                lpSyncTimeRecordingConfig;
  P2VAR(StbM_SyncRecordTableBlockType, AUTOMATIC, STBM_APPL_DATA)lpSyncRecord;
  #if(STBM_NUMBER_OFFSET_TIME_RECORD_TABLE_CONFIGURED > STBM_ZERO)
  P2VAR(StbM_OffsetRecordTableBlockType, AUTOMATIC, STBM_APPL_DATA)lpOffsetRecord;
  P2CONST(StbM_OffsetTimeRecordingConfigType, AUTOMATIC, STBM_APPL_DATA)
                                lpOffsetTimeRecordingConfig;
  #endif
  P2VAR(StbM_TimeRecordingValueType, AUTOMATIC, STBM_APPL_DATA)lpTimeRecordValue;
  
  VAR(uint16, STBM_VAR) lucCount;
  
  /* Get address of TimeBaseConfig */  
  lpTimeBaseConfig = &StbM_GaaTimeBaseConfig[lusConfigPtr];
  /* @Trace: SWS_StbM_00428 */
  /* Condition STBM_FALSE == (lpTimeBaseConfig->enSystemWideTimeMasterSlave) */
  /* is checked by Generation tool*/
  /* @Trace: StbM_SUD_API_461 */
  if(STBM_BASE_INVAILD != lpTimeBaseConfig->ucBaseOfRecording)
  {
    /* @Trace: SWS_StbM_00312 */
    if(lusConfigPtr < STBM_NUMBER_SYNC_TIME_BASES_CONFIGURED)
    {
      lpSyncTimeRecordingConfig = &(StbM_GaaSyncTimeRecordingConfig
                                [lpTimeBaseConfig->ucBaseOfRecording]);
      lpTimeRecordValue = &StbM_GaaSyncRecordValue
                                [lpTimeBaseConfig->ucBaseOfRecording];
      /* @Trace: StbM_SUD_API_462 */
      if(STBM_TRUE == lpTimeRecordValue->blOver)
      {
        for(lucCount = lpTimeRecordValue->ulPtr; lucCount <
                   (lpSyncTimeRecordingConfig->usCount); lucCount++)
        {
          lpSyncRecord = &(lpSyncTimeRecordingConfig->pAddress[lucCount]);
          (void)(*(lpSyncTimeRecordingConfig->pCallback))(lpSyncRecord);   
        } 
      }
      else
      {
        /* Do nothing */
      }
      for(lucCount = STBM_ZERO; lucCount <
                  (lpTimeRecordValue->ulPtr); lucCount++)
      {
        lpSyncRecord = &(lpSyncTimeRecordingConfig->pAddress[lucCount]);
        (void)(*(lpSyncTimeRecordingConfig->pCallback))(lpSyncRecord);   
      }
      lpTimeRecordValue->ulPtr = STBM_ZERO;
      lpTimeRecordValue->blOver = STBM_FALSE; 
    }
    /* Pure time base is checked by Generation tool */
    /* @Trace: StbM_SUD_API_463 */
    else
    {
      #if(STBM_NUMBER_OFFSET_TIME_RECORD_TABLE_CONFIGURED > STBM_ZERO)
      lpOffsetTimeRecordingConfig = &(StbM_GaaOffsetTimeRecordingConfig
                                [lpTimeBaseConfig->ucBaseOfRecording]);
      #endif
      lpTimeRecordValue = &StbM_GaaOffsetRecordValue
                                [lpTimeBaseConfig->ucBaseOfRecording];
      /* @Trace: StbM_SUD_API_464 */
      #if(STBM_NUMBER_OFFSET_TIME_RECORD_TABLE_CONFIGURED > STBM_ZERO)
      if(STBM_TRUE == lpTimeRecordValue->blOver)
      {
          for(lucCount = lpTimeRecordValue->ulPtr; lucCount <
                     (lpOffsetTimeRecordingConfig->usCount); lucCount++)
        {
          lpOffsetRecord = &(lpOffsetTimeRecordingConfig->pAddress[lucCount]);
          (void)(*(lpOffsetTimeRecordingConfig->pCallback))(lpOffsetRecord);   
        } 
      }
      else
      {
        /* Do nothing */
      }
      for(lucCount = STBM_ZERO; lucCount <
                  (lpTimeRecordValue->ulPtr); lucCount++)
      {
        lpOffsetRecord = &(lpOffsetTimeRecordingConfig->pAddress[lucCount]);
        (void)(*(lpOffsetTimeRecordingConfig->pCallback))(lpOffsetRecord);    
      }
      #endif
      lpTimeRecordValue->ulPtr = STBM_ZERO;
      lpTimeRecordValue->blOver = STBM_FALSE; 
    }
  }
  /* @Trace: StbM_SUD_API_465 */
  else
  {
    /* Do nothing */
  }
} /* End of StbM_Internal_ReadTimeRecordTable(void) */

#define STBM_STOP_SEC_CODE
#include "MemMap.h"

#endif  /* STD_ON == STBM_TIME_RECORDING_SUPPORT */ 

/*******************************************************************************
** Function Name        : StbM_Internal_CheckTimeLeap                         **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Check STBM_STATE_TIMELEAP_FUTURE /                  **
**                          STBM_STATE_TIMELEAP_PAST flag of Time Base.       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : lusConfigPtr: ptr of StbM_GaaTimeBaseConfig         **
**                        localTime : Sync Local time                         **
**                        globalTime : receive Global time                    **
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
**                                StbM_GaaTimeBaseValue                       **
**                        Function(s) invoked :                               **
**                                StbM_Math_ConvertTimeStampToRaw             **
**                                StbM_Internal_UpdateStatusOfTimeBase        **
*******************************************************************************/
/* @Trace: RS_TS_00009 */
#define STBM_START_SEC_CODE
#include "MemMap.h"

FUNC(Std_ReturnType, STBM_CODE) StbM_Internal_CheckTimeLeap(
  VAR(uint16,AUTOMATIC)lusConfigPtr,
  VAR(StbM_TimeStampType, AUTOMATIC)localTime,
  VAR(StbM_TimeStampType, AUTOMATIC)globalTime)
{
  VAR(Std_ReturnType,AUTOMATIC)lddReturnVal;

  P2VAR(StbM_TimeBaseValueType, AUTOMATIC, STBM_APPL_DATA)lpTimeBaseValue;
  P2CONST(StbM_TimeBaseConfigType, AUTOMATIC, STBM_APPL_DATA)lpTimeBaseConfig;
  VAR(StbM_TimeStampType, AUTOMATIC)lddElapsedTimeStamp;
  
  STBM_INIT_TIMESTAMP(&lddElapsedTimeStamp);
  
  /* Get address of TimeBaseConfig */
  lpTimeBaseValue = &StbM_GaaTimeBaseValue[lusConfigPtr];
  lpTimeBaseConfig = &StbM_GaaTimeBaseConfig[lusConfigPtr];
  /* @Trace: SWS_StbM_00182 */
  /* @Trace: SWS_StbM_00305 */    
  /* calculate delta of TimeStamp  globalTime - localTime */
  lddReturnVal =StbM_Math_DiffOfTwoTimeStamp(localTime, 
                            globalTime, &lddElapsedTimeStamp);
  
  StbM_Math_ConvertTimeStampToRaw(lddElapsedTimeStamp,
                           &(lpTimeBaseValue->ulTimeLeap));
  /* when GlobalTime >= LocalTime  */
  /* @Trace: StbM_SUD_API_492 */
  if(E_OK == lddReturnVal)
  {
    /* Set sign of time leap TGRx - TLSync */
    lpTimeBaseValue->blSignOfTimeLeap = STBM_TRUE;  
    #if (STD_ON == STBM_TIME_LEAP_SUPPORT)
    if( ((lpTimeBaseValue->ulTimeLeap) > (lpTimeBaseConfig->ulStbMTimeLeapFutureThreshold)) &&
        ((lpTimeBaseConfig->ulStbMTimeLeapFutureThreshold) != STBM_ZERO))
    {
      (void) StbM_Internal_UpdateStatusOfTimeBase(lusConfigPtr,
                      STBM_STATE_TIMELEAP_FUTURE, STBM_TRUE);
      lddReturnVal = E_NOT_OK;
    }
    else
    {
      /* Do nothing */                    
    }
    #endif /* STD_ON == STBM_TIME_LEAP_SUPPORT */
  }
  /* when GlobalTime < LocalTime  */
  /* @Trace: StbM_SUD_API_493 */
  else
  {
    /* Set sign of time leap TGRx - TLSync */
    lpTimeBaseValue->blSignOfTimeLeap = STBM_FALSE;  
    #if (STD_ON == STBM_TIME_LEAP_SUPPORT)        
    if( ((lpTimeBaseValue->ulTimeLeap) > (lpTimeBaseConfig->ulStbMTimeLeapPastThreshold)) &&
         ((lpTimeBaseConfig->ulStbMTimeLeapPastThreshold) != STBM_ZERO))
    {
      lpTimeBaseValue->ulTimeLeapClear = STBM_ZERO;
      (void) StbM_Internal_UpdateStatusOfTimeBase(lusConfigPtr,
                      STBM_STATE_TIMELEAP_PAST, STBM_TRUE);
    }
    /* @Trace: StbM_SUD_API_474 */
    else
    {
    #endif /* STD_ON == STBM_TIME_LEAP_SUPPORT */
      lddReturnVal = E_OK;   
    #if (STD_ON == STBM_TIME_LEAP_SUPPORT)               
    }
    #endif /* STD_ON == STBM_TIME_LEAP_SUPPORT */
  }
    
  #if (STD_ON == STBM_TIME_LEAP_SUPPORT) 
  if(E_NOT_OK == lddReturnVal)
  {
    lpTimeBaseValue->ulTimeLeapClear = STBM_ZERO;
  }
  /* @Trace: StbM_SUD_API_491 */
  else
  {
    if((lpTimeBaseValue->ulTimeLeapClear) >=
                      (lpTimeBaseConfig->usClearTimeleapCount))
    {
      (void) StbM_Internal_UpdateStatusOfTimeBase(lusConfigPtr,
                      STBM_STATE_TIMELEAP_FUTURE, STBM_FALSE);
      (void)StbM_Internal_UpdateStatusOfTimeBase(lusConfigPtr,
                      STBM_STATE_TIMELEAP_PAST, STBM_FALSE);
    }
    else
    {
      if(((uint8)STBM_ZERO) != ((lpTimeBaseValue->ddLocalTime.timeBaseStatus)&    
                      (STBM_STATE_TIMELEAP_FUTURE | STBM_STATE_TIMELEAP_PAST))) 
      {
        lpTimeBaseValue->ulTimeLeapClear =     
                      lpTimeBaseValue->ulTimeLeapClear + STBM_ONE;                
      }
      else
      {
        /* Do nothing */                    
      }                          
    }
  }
  #endif /* STD_ON == STBM_TIME_LEAP_SUPPORT */
  return (lddReturnVal);
} /* End of StbM_Internal_CheckTimeLeap(void) */

#define STBM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : StbM_Internal_CheckTimeOut                          **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Check STBM_STATE_TIMEOUT flag of Time Base.         **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : lusConfigPtr: ptr of StbM_GaaTimeBaseConfig         **
**                        globalTime : Global time                            **
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
**                                StbM_GaaTimeBaseValue                       **
**                        Function(s) invoked :                               **
**                                StbM_Math_DiffOfTwoTimeStamp                **
**                                StbM_Math_ConvertTimeStampToRaw             **
**                                StbM_Internal_UpdateStatusOfTimeBase        **
*******************************************************************************/
/* @Trace: RS_TS_00009, RS_TS_00025 */
#define STBM_START_SEC_CODE
#include "MemMap.h"

FUNC(Std_ReturnType, STBM_CODE) StbM_Internal_CheckTimeOut(
  VAR(uint16,AUTOMATIC)lusConfigPtr,
  VAR(StbM_TimeStampType, AUTOMATIC)globalTime)
{
  VAR(Std_ReturnType,AUTOMATIC)lddReturnVal;

  P2VAR(StbM_TimeBaseValueType, AUTOMATIC, STBM_APPL_DATA)lpTimeBaseValue;
  P2CONST(StbM_TimeBaseConfigType, AUTOMATIC, STBM_APPL_DATA)lpTimeBaseConfig;
  VAR(StbM_TimeStampType, AUTOMATIC)localTime;
  VAR(StbM_TimeStampType, AUTOMATIC)lddElapsedTimeStamp;
  VAR(uint64, STBM_VAR) ulRawTimeOut;
  
  STBM_INIT_TIMESTAMP(&localTime);
  STBM_INIT_TIMESTAMP(&lddElapsedTimeStamp);
  
  /* Get address of TimeBaseConfig */
  lpTimeBaseValue = &StbM_GaaTimeBaseValue[lusConfigPtr];    
  /* calculate delta of TimeStamp  globalTime - localTime */
  STBM_COPY_TIMESTAMP(&localTime, &(lpTimeBaseValue->ddLocalTime));
  lddReturnVal =StbM_Math_DiffOfTwoTimeStamp(localTime, 
                            globalTime, &lddElapsedTimeStamp);
  /* GlobalTime >= LocalTime  */
  /* @Trace: SWS_StbM_00183 */
  /* @Trace: SWS_StbM_00187 */
  /* @Trace: StbM_SUD_API_501 */
  if(E_OK == lddReturnVal)
  {
    StbM_Math_ConvertTimeStampToRaw(lddElapsedTimeStamp, &ulRawTimeOut); 
    lpTimeBaseConfig = &StbM_GaaTimeBaseConfig[lusConfigPtr];
    if(ulRawTimeOut > (lpTimeBaseConfig->ulSyncLossTimeout))
    {
      (void) StbM_Internal_UpdateStatusOfTimeBase(lusConfigPtr,
                      STBM_STATE_TIMEOUT, STBM_TRUE);
      lddReturnVal = E_NOT_OK;
    }
    /* @Trace: StbM_SUD_API_502 */
    else
    {
      /* Do nothing */                    
    }
  }
  /* when GlobalTime < LocalTime  */
  else
  {
    /* Do nothing */
  }

  return (lddReturnVal);
} /* End of StbM_Internal_CheckTimeOut(void) */

#define STBM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : StbM_Internal_UpdateStatusWithoutNotification       **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Update status of TimeBase                           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : lusConfigPtr: ptr of StbM_GaaTimeBaseConfig         **
**                        localStatusMask : Bit mask                          **
**                        localStatusValue : Bit value                        **
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
**                                StbM_GaaTimeBaseValue                       **
**                        Function(s) invoked : None                          **
*******************************************************************************/
/* @Trace: RS_TS_00016, RS_TS_20001 */
#define STBM_START_SEC_CODE
#include "MemMap.h"

FUNC(Std_ReturnType, STBM_CODE) StbM_Internal_UpdateStatusWithoutNotification(
  VAR(uint16, AUTOMATIC)localConfigPtr,
  VAR(uint8, AUTOMATIC) localStatusMask,
  VAR(boolean, AUTOMATIC) localStatusValue)
{
  VAR(Std_ReturnType,AUTOMATIC)lddReturnVal;
  
  P2VAR(StbM_TimeBaseValueType, AUTOMATIC, STBM_APPL_DATA)lpTimeBaseValue;
  VAR(uint16, AUTOMATIC)lucStatusEvent;
  VAR(uint8, AUTOMATIC)lucStatusBackup;
  
  lddReturnVal = E_NOT_OK;
  /* Backup Status of Time Base */
  lpTimeBaseValue = &StbM_GaaTimeBaseValue[localConfigPtr]; 
  lucStatusBackup = lpTimeBaseValue->ddLocalTime.timeBaseStatus;
  /* Set/clear status bit */
  /* Return E_OK when it has change status */
  /* @Trace: StbM_SUD_API_471 */
  if(STBM_TRUE == localStatusValue)
  {
    if(STBM_ZERO == (lucStatusBackup & localStatusMask))
    {
      lucStatusBackup |= localStatusMask;
      lddReturnVal = E_OK;
    }
    else
    {
      /* Do nothing */                          
    }
  }
  /* @Trace: StbM_SUD_API_472 */
  else
  {
    if(STBM_ZERO != (lucStatusBackup & localStatusMask))
    {
      lucStatusBackup &= ~localStatusMask;
      lddReturnVal = E_OK;
    }
    else
    {
      /* Do nothing */                          
    }
  }
  /* Set return value */
  lpTimeBaseValue->ddLocalTime.timeBaseStatus = (StbM_TimeBaseStatusType)
                                                    lucStatusBackup;
  /* check if it has changed any event */
  if(E_OK == lddReturnVal)
  {
    /* @Trace: SWS_StbM_00284 */
    switch(localStatusMask)
    {
      /* Check STBM_STATE_TIMEOUT */
      /* @Trace: StbM_SUD_API_473 */
      case STBM_STATE_TIMEOUT: 
        if(STBM_TRUE == localStatusValue)
        {
          lucStatusEvent = STBM_EV_TIMEOUT_OCCURRED;
        }
        else    
        {
          lucStatusEvent = STBM_EV_TIMEOUT_REMOVED;
        }  
        break;
      /* Check STBM_STATE_SYNC_TO_GATEWAY */
      /* @Trace: StbM_SUD_API_474 */
      case STBM_STATE_SYNC_TO_GATEWAY: 
        if(STBM_TRUE == localStatusValue)
        {
          lucStatusEvent = STBM_EV_SYNC_TO_SUBDOMAIN;
        }
         else    
        {
          lucStatusEvent = STBM_EV_SYNC_TO_GLOBAL_MASTER;
        }  
        break;
      /* Check STBM_STATE_GLOBAL_TIME_BASE */
      /* @Trace: StbM_SUD_API_475 */
      case STBM_STATE_GLOBAL_TIME_BASE: 
        lucStatusEvent = STBM_EV_GLOBAL_TIME; 
        break;
      /* Check STBM_STATE_TIMELEAP_FUTURE */
      /* @Trace: StbM_SUD_API_476 */
      case STBM_STATE_TIMELEAP_FUTURE: 
        if(STBM_TRUE == localStatusValue)
        {
          lucStatusEvent = STBM_EV_TIMELEAP_FUTURE;
        }
        else    
        {
          lucStatusEvent = STBM_EV_TIMELEAP_FUTURE_REMOVED;
        }
        break;
      /* Check STBM_STATE_TIMELEAP_PAST */
      /* case STBM_STATE_TIMELEAP_PAST: */
      /* @Trace: StbM_SUD_API_477 */
      default:
        if(STBM_TRUE == localStatusValue)
        {
          lucStatusEvent = STBM_EV_TIMELEAP_PAST;
        }
        else    
        {
          lucStatusEvent = STBM_EV_TIMELEAP_PAST_REMOVED;
        }
     break;
    }  
    /* Set return value */
    /* @Trace: SWS_StbM_00278 */
    lpTimeBaseValue->ulNotificationEvents |= lucStatusEvent;
  }
  else
  {
    /* Do nothing */                          
  }
  return (lddReturnVal);
} /* End of StbM_Internal_UpdateStatusWithoutNotification(void) */

#define STBM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : StbM_Internal_UpdateStatusOfTimeBase                **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Update status of TimeBase                           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : lusConfigPtr: ptr of StbM_GaaTimeBaseConfig         **
**                        localStatusMask : Bit mask                          **
**                        localStatusValue : Bit value                        **
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
**                                StbM_GaaTimeBaseValue                       **
**                        Function(s) invoked  :                              **
**                            StbM_Internal_UpdateStatusWithoutNotification   **
*******************************************************************************/
/* @Trace: RS_TS_00016, RS_TS_00027, RS_TS_000356, RS_TS_20001 */
#define STBM_START_SEC_CODE
#include "MemMap.h"

FUNC(Std_ReturnType, STBM_CODE) StbM_Internal_UpdateStatusOfTimeBase(
  VAR(uint16, AUTOMATIC)localConfigPtr,
  VAR(uint8, AUTOMATIC) localStatusMask,
  VAR(boolean, AUTOMATIC) localStatusValue)
{
  VAR(Std_ReturnType,AUTOMATIC)lddReturnVal;
  
  #if (STD_ON == STBM_STATUS_NOTIFICATION_SUPPORT)
  P2CONST(StbM_TimeBaseConfigType, AUTOMATIC, STBM_APPL_DATA)lpTimeBaseConfig;
  P2VAR(StbM_TimeBaseValueType, AUTOMATIC, STBM_APPL_DATA)lpTimeBaseValue;
  VAR(uint16, AUTOMATIC)lucStatusMaskCofig;
  VAR(uint16, AUTOMATIC)lucStatusEventBackup;
  VAR(uint16, AUTOMATIC)lucStatusEvent;
  VAR(uint16, AUTOMATIC)lulCheckResult;
  #endif /* STD_ON == STBM_STATUS_NOTIFICATION_SUPPORT */
  
  /* Backup StatusEvent before status is updated */
  #if (STD_ON == STBM_STATUS_NOTIFICATION_SUPPORT)
  lpTimeBaseValue = &StbM_GaaTimeBaseValue[localConfigPtr];
  lucStatusEventBackup = lpTimeBaseValue->ulNotificationEvents;
  #endif /* STD_ON == STBM_STATUS_NOTIFICATION_SUPPORT */
  
  /* Update Status of Time Base */
  lddReturnVal = StbM_Internal_UpdateStatusWithoutNotification(
                        localConfigPtr,localStatusMask,localStatusValue);

  #if (STD_ON == STBM_STATUS_NOTIFICATION_SUPPORT)
  /* check any status event is changed */
  /* @Trace: SWS_StbM_00277 */
  /* @Trace: StbM_SUD_API_481 */
  if(E_OK == lddReturnVal)
  {
    /* Get status notify after update */
    lucStatusEvent = lpTimeBaseValue->ulNotificationEvents;
    /* Get Config status of Time Base */
    lpTimeBaseConfig = &StbM_GaaTimeBaseConfig[localConfigPtr];
    /* @Trace: SWS_StbM_00279 */
    lucStatusMaskCofig = lpTimeBaseConfig->usStatusMask;
    lulCheckResult = (lucStatusEventBackup^lucStatusEvent) & lucStatusMaskCofig;
    if(STBM_ZERO != lulCheckResult)    
    { 
      /* Notify via callback function */
      if(NULL_PTR != lpTimeBaseConfig->pStatusCallback)    
      {
        /* @Trace: SWS_StbM_00282 */
        (void)(*(lpTimeBaseConfig->pStatusCallback))(
                  (StbM_TimeBaseNotificationType)lulCheckResult);
        /* @Trace: SWS_StbM_00280 */
        lpTimeBaseValue->ulNotificationEvents &= lulCheckResult;
      }
      else
      {
        /* Do nothing */                          
      } 
      /* Notify via RTE interface */
      if(NULL_PTR != lpTimeBaseConfig->pStatusInterface)    
      {
        /* @Trace: SWS_StbM_00282 */
        (void)(*(lpTimeBaseConfig->pStatusInterface))(
                  (const StbM_TimeBaseNotificationType)lulCheckResult);
        /* @Trace: SWS_StbM_00280 */
        lpTimeBaseValue->ulNotificationEvents &= lulCheckResult;
      }
      else
      {
        /* Do nothing */                          
      } 
    }
    /* @Trace: StbM_SUD_API_482 */
    else
    {
      /* Do nothing */                          
    }          
  }
  /* @Trace: StbM_SUD_API_483 */
  else
  {
    /* Do nothing */                          
  }
  #endif /* STD_ON == STBM_STATUS_NOTIFICATION_SUPPORT */

  return (lddReturnVal);
} /* End of StbM_Internal_UpdateStatusOfTimeBase(void) */

#define STBM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : StbM_Internal_IncreaseCounterOfTimeBase             **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Update timeBaseUpdateCounter                        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : lusConfigPtr: ptr of StbM_GaaTimeBaseConfig         **
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
**                                StbM_GaaTimeBaseValue                       **
**                        Function(s) invoked : None                          **
*******************************************************************************/
/* @Trace: RS_TS_00011 */
#define STBM_START_SEC_CODE
#include "MemMap.h"

FUNC(void, STBM_CODE) StbM_Internal_IncreaseCounterOfTimeBase(
  VAR(uint16, AUTOMATIC)localConfigPtr)
{
  P2VAR(StbM_TimeBaseValueType, AUTOMATIC, STBM_APPL_DATA)lpTimeBaseValue;
  
  /* Backup StatusEvent before status is updated */
  lpTimeBaseValue = &StbM_GaaTimeBaseValue[localConfigPtr];
  /* @Trace: SWS_StbM_00350 */ 
  /* @Trace: StbM_SUD_API_511 */
  if(((uint8)STBM_TWO_HUNDRED_AND_FIVE) == 
              (lpTimeBaseValue->timeBaseUpdateCounter))
  {
    lpTimeBaseValue->timeBaseUpdateCounter = (uint8)STBM_ZERO;
  }
  /* @Trace: StbM_SUD_API_512 */
  else
  {
    lpTimeBaseValue->timeBaseUpdateCounter = 
            lpTimeBaseValue->timeBaseUpdateCounter + (uint8)STBM_ONE;
  }
} /* End of StbM_Internal_UpdateCounterOfTimeBase(void) */

#define STBM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : StbM_Internal_SlaveTimeCorrection                   **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Apply Offset Correction By Rate Adaption            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : lusConfigPtr: ptr of StbM_GaaTimeBaseConfig         **
**                        timeVlt: StbM_VirtualLocalTimeType                  **
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
**                                StbM_GaaTimeBaseValue                       **
**                                StbM_GaaTimeTuple                           **
**                        Function(s) invoked :                               **
**                                StbM_Math_SumOfNumberWithVlt                **
**                                StbM_Math_CompareVlt                        **
**                                StbM_Math_TimeStampInterpolate              **
*******************************************************************************/
/* @Trace: RS_TS_00018, RS_TS_00019 */
#define STBM_START_SEC_CODE
#include "MemMap.h"

FUNC(Std_ReturnType, STBM_CODE) StbM_Internal_SlaveTimeCorrection(
  VAR(uint16, AUTOMATIC)lusConfigPtr,
  VAR(StbM_VirtualLocalTimeType, AUTOMATIC)timeVlt)
{
  VAR(Std_ReturnType,AUTOMATIC)lddReturnVal;
  
  P2CONST(StbM_TimeBaseConfigType, AUTOMATIC, STBM_APPL_DATA)lpTimeBaseConfig;
  P2CONST(StbM_TimeCorrectionConfigType, AUTOMATIC, STBM_APPL_DATA)
                                                       lpTimeCorrectionConfig;
  
  P2VAR(StbM_TimeBaseValueType, AUTOMATIC, STBM_APPL_DATA)lpTimeBaseValue;
  P2VAR(StbM_TimeTupleType, AUTOMATIC, STBM_APPL_DATA)lpTimeTuple;
  VAR(StbM_RateCorrectionType, AUTOMATIC)lddRateInterval;
  VAR(StbM_TimeStampType, AUTOMATIC)lddTimeStamp;
  VAR(StbM_VirtualLocalTimeType, AUTOMATIC)lddVlt;
  
  lddReturnVal = E_NOT_OK;
  
  lpTimeBaseConfig = &StbM_GaaTimeBaseConfig[lusConfigPtr];
  /* @Trace: Interval */
  if(STBM_BASE_INVAILD != (lpTimeBaseConfig->ucBaseOfCorrection))
  {    
    lpTimeCorrectionConfig = &StbM_GaaTimeCorrectionConfig
                                  [lpTimeBaseConfig->ucBaseOfCorrection];
    /* @Trace: SWS_StbM_00356 */
    /* @Trace: SWS_StbM_00400 */
    if(STBM_ZERO != (lpTimeCorrectionConfig->ulDuration))
    {
      lpTimeBaseValue = &StbM_GaaTimeBaseValue[lusConfigPtr];
      if((lpTimeBaseValue->ulTimeLeap) < 
               ((uint64)(lpTimeCorrectionConfig->ulJumpThreshold)))
      {
        lpTimeTuple = &StbM_GaaTimeTuple[lusConfigPtr];
        StbM_Math_SumOfNumberWithVlt(lpTimeTuple->ddVirtualLocalTime, 
                   (lpTimeCorrectionConfig->ulInterval), &lddVlt);
        lddReturnVal = StbM_Math_CompareVlt(lddVlt, timeVlt);
        /* @Trace: SWS_StbM_00353 */
        /* Check (TV - TVSync) >= StbMOffsetCorrectionAdaptionInterval*/
        if((E_OK == lddReturnVal) && (lpTimeCorrectionConfig->ulInterval != STBM_ZERO))
        {
          /* @Trace: StbM_SUD_API_521 */
          /* @Trace: SWS_StbM_00356 */
          lddRateInterval = (StbM_RateCorrectionType)((lpTimeBaseValue->ulTimeLeap)/
                   (lpTimeCorrectionConfig->ulInterval));
          lpTimeBaseValue->ddRate = lpTimeBaseValue->ddRate + lddRateInterval;
          (void) StbM_Math_TimeStampInterpolate(lpTimeBaseValue->ddRate,
              StbM_GaaTimeTuple[lusConfigPtr], lddVlt,&lddTimeStamp);
          STBM_COPY_TIMESTAMP(&(lpTimeTuple->ddLocalTime), &lddTimeStamp);
          STBM_COPY_VLTIME(&(lpTimeTuple->ddVirtualLocalTime),&lddVlt);
        }
        /* @Trace: StbM_SUD_API_524 */
        else
        {
          /* Do nothing */
        }
        /* In case of actually performing Offset Correction By Rate Adaption */
        /* the Main Time Tuple is not overwritten by the Received Time Tuple */
        lddReturnVal = E_OK;
      }
      /* @Trace: StbM_SUD_API_522 */
      else
      {
        /* Not change rate correction */
        /* @Trace: SWS_StbM_0440 */
        /* @Trace: SWS_StbM_0441 */
        /* Do nothing */
      }
    }
    else
    {
      /* Do nothing */
    }
  }
  /* @Trace: StbM_SUD_API_523 */
  else
  {
    /* Do nothing */
  }    
  return (lddReturnVal);
} /* End of StbM_Internal_SlaveTimeCorrection(void) */

#define STBM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : StbM_Internal_SlaveRateCorrection                   **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Apply Rate Correction                               **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : lusConfigPtr: ptr of StbM_GaaTimeBaseConfig         **
**                        timeStamp: StbM_TimeStampType                       **
**                        timeVlt: StbM_VirtualLocalTimeType                  **
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
**                                StbM_GaaTimeBaseValue                       **
**                                StbM_GaaTimeTuple                           **
**                        Function(s) invoked :                               **
**                                StbM_Math_SumOfNumberWithVlt                **
**                                StbM_Math_CompareVlt                        **
**                                StbM_Math_CalRateCorrection                 **
*******************************************************************************/
/* @Trace: RS_TS_00018 */
#define STBM_START_SEC_CODE
#include "MemMap.h"

FUNC(Std_ReturnType, STBM_CODE) StbM_Internal_SlaveRateCorrection(
  VAR(uint16, AUTOMATIC)lusConfigPtr,
  VAR(StbM_TimeStampType, AUTOMATIC)timeStamp,
  VAR(StbM_VirtualLocalTimeType, AUTOMATIC)timeVlt)
{
  VAR(Std_ReturnType,AUTOMATIC)lddReturnVal;
  
  P2CONST(StbM_TimeBaseConfigType, AUTOMATIC, STBM_APPL_DATA)lpTimeBaseConfig;
  P2CONST(StbM_TimeCorrectionConfigType, AUTOMATIC, STBM_APPL_DATA)
                                                       lpTimeCorrectionConfig;
  
  P2VAR(StbM_TimeBaseValueType, AUTOMATIC, STBM_APPL_DATA)lpTimeBaseValue;
  P2VAR(StbM_TimeCorrectionValueType, AUTOMATIC, STBM_APPL_DATA)lpTimeCorrectionValue;
  P2VAR(StbM_TimeTupleType, AUTOMATIC, STBM_APPL_DATA)lpTimeCorrectionTuple;
  
  VAR(StbM_VirtualLocalTimeType, AUTOMATIC)lddVlt;
  VAR(StbM_RateCorrectionType, AUTOMATIC)lddRate;
  
  lddReturnVal = E_NOT_OK;
  lpTimeCorrectionConfig = NULL_PTR;

  /* @Trace: SWS_StbM_00372 */
  /* Check if Time correction is configured */
  lpTimeBaseConfig = &StbM_GaaTimeBaseConfig[lusConfigPtr];
  lpTimeBaseValue = &StbM_GaaTimeBaseValue[lusConfigPtr]; 
  if(STBM_BASE_INVAILD != (lpTimeBaseConfig->ucBaseOfCorrection))
  { 
    lpTimeCorrectionConfig = &StbM_GaaTimeCorrectionConfig
                                [lpTimeBaseConfig->ucBaseOfCorrection];  
    /* @Trace: SWS_StbM_00377 */
    if(STBM_ZERO != (lpTimeCorrectionConfig->ulDuration))
    {
      /* @Trace: SWS_StbM_00376 */
      /* @Trace: SWS_StbM_00374 */
      /* @Trace: SWS_StbM_00373 */  
      /* Check if don't have any error status is set */     
      if(STBM_ZERO == ((lpTimeBaseValue->ddLocalTime.timeBaseStatus) & ( 
               /* TIMELEAP is checked by StbM_BusSetGlobalTime API */
               /*STBM_STATE_TIMELEAP_FUTURE | STBM_STATE_TIMELEAP_PAST | */
               STBM_STATE_TIMEOUT)))
      {
        lddReturnVal = E_OK; 
      }
      else
      {
        /* Do nothing */
      }
    }
    else
    {
      /* Do nothing */
    }
  }
  else
  {/* polyspace RTE:UNR [Not a defect:Low] "This branch is available for other configuration" */
    /* Do nothing */
  }
  
  /* Check if don't have any error */
  if(E_OK == lddReturnVal)
  {
    lpTimeCorrectionValue = &StbM_GaaTimeCorrectionValue
                                  [lpTimeBaseConfig->ucBaseOfCorrection];
    /* @Trace: StbM_SUD_API_531 */
    if(lpTimeBaseValue->ucFirstSynch == STBM_ONE)
    {
      lpTimeCorrectionTuple = &(lpTimeCorrectionConfig->pTimeTuple[STBM_ZERO]);
      /* @Trace: SWS_StbM_00370 */
      /* polyspace +1 RTE:IDP [Not a defect:Low] "StbM_GaaTimeBaseConfig is verified and generated by Generator Tool" */
      STBM_COPY_VLTIME(&(lpTimeCorrectionValue->ddMark), &timeVlt);
      /* @Trace: SWS_StbM_00366 */
      /* polyspace +1 RTE:IDP [Not a defect:Low] "StbM_GaaTimeBaseConfig is verified and generated by Generator Tool" */
      STBM_COPY_TIMESTAMP(&(lpTimeCorrectionTuple->ddLocalTime), &timeStamp); /*polyspace MISRA-C:18.1 [Not a defect:Low] "StbM_GaaTimeBaseConfig is verified and generated by Generator Tool"*/
      STBM_COPY_VLTIME(&(lpTimeCorrectionTuple->ddVirtualLocalTime), &timeVlt);
      /* Set first flag for time correction */      
      lpTimeCorrectionValue->ucCount = STBM_ONE;
      lpTimeCorrectionValue->ucFirst = STBM_TRUE;
    }
    /* @Trace: StbM_SUD_API_532 */
    else
    {    
      /* @Trace: SWS_StbM_00370 */
      StbM_Math_SumOfNumberWithVlt(lpTimeCorrectionValue->ddMark, lpTimeCorrectionConfig->ulDuration, &lddVlt);
      lddReturnVal = StbM_Math_CompareVlt(timeVlt, lddVlt);
      if(E_NOT_OK == lddReturnVal)
      {
        /* @Trace: SWS_StbM_00370 */
        /* Start new Rate Correction measurement */
        STBM_COPY_VLTIME(&(lpTimeCorrectionValue->ddMark), &timeVlt);  
        lpTimeCorrectionValue->ucCount = STBM_ZERO;
        /* Next Rate Correction measurement */
        if(STBM_TRUE == (lpTimeCorrectionValue->ucFirst))
        {
          lpTimeCorrectionValue->ucFirst = STBM_FALSE;
        }
        else
        {
          /* Do nothing */
        }
      }
      else
      {
        /* Do nothing */  
      }
      /* @Trace: SWS_StbM_00368 */ 
      /* @Trace: SWS_StbM_00367 */ 
      if((lpTimeCorrectionValue->ucCount) <
                (lpTimeCorrectionConfig->ucPerMeasurement))
      {
        lpTimeCorrectionTuple = &(lpTimeCorrectionConfig->pTimeTuple
                                    [lpTimeCorrectionValue->ucCount]);
        /* @Trace: SWS_StbM_00361 */ 
        if(STBM_FALSE == (lpTimeCorrectionValue->ucFirst))
        {
          /* @Trace: SWS_StbM_00361 */
          /* @Trace: SWS_StbM_00360 */
	  /* polyspace +3 RTE:IDP [Not a defect:Low] "StbM_GaaTimeBaseConfig is verified and generated by Generator Tool" */
          lddReturnVal = StbM_Math_CalRateCorrection(
                  lpTimeCorrectionTuple->ddLocalTime, timeStamp,
                  lpTimeCorrectionTuple->ddVirtualLocalTime,timeVlt,&lddRate); /*polyspace MISRA-C:18.1 [Not a defect:Low] "StbM_GaaTimeBaseConfig is verified and generated by Generator Tool"*/
          if(E_OK == lddReturnVal)
          {
            lpTimeBaseValue->ddRate = lddRate;
            lpTimeBaseValue->ucRateValid = STBM_TRUE;
          }
          else
          {
            /* Do nothing */
          }
        }
        else
        {
          /* Do nothing */
          lddReturnVal = E_OK; 
          /* @Trace: SWS_StbM_00362 */
          /* @Trace: SWS_StbM_00412 */
        }
        /* @Trace: SWS_StbM_00371 */
        /* @Trace: SWS_StbM_00366 */
        /* @Trace: SWS_StbM_00364 */
	/* polyspace +1 RTE:IDP [Not a defect:Low] "StbM_GaaTimeBaseConfig is verified and generated by Generator Tool" */
        STBM_COPY_TIMESTAMP(&(lpTimeCorrectionTuple->ddLocalTime), &timeStamp); /*polyspace MISRA-C:18.1 [Not a defect:Low] "StbM_GaaTimeBaseConfig is verified and generated by Generator Tool"*/
        STBM_COPY_VLTIME(&(lpTimeCorrectionTuple->ddVirtualLocalTime), &timeVlt);
        
        lpTimeCorrectionValue->ucCount = lpTimeCorrectionValue->ucCount + STBM_ONE;     
      }
      else
      {
        /* Do nothing */
        lddReturnVal = E_NOT_OK;
      }
    }                                  
  }
  else
  {
    /* Do nothing */
  }

  return (lddReturnVal);
} /* End of StbM_Internal_SlaveRateCorrection(void) */

#define STBM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : StbM_Internal_CalRateDeviation                      **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Convert StbM_RateCorrectionType to                  **
**                                StbM_RateDeviationType                      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : lusConfigPtr: ptr of StbM_GaaTimeBaseConfig         **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : rateDeviation: StbM_RateDeviationType               **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                                StbM_GaaTimeBaseValue                       **
**                        Function(s) invoked : None                          **
*******************************************************************************/
#define STBM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, STBM_CODE) StbM_Internal_CalRateDeviation(
  VAR(uint16, AUTOMATIC)lusConfigPtr,
  P2VAR(StbM_RateDeviationType, AUTOMATIC, STBM_APPL_DATA)rateDeviation)
{
  Std_ReturnType lddReturnVal;
  P2VAR(StbM_TimeBaseValueType, AUTOMATIC, STBM_APPL_DATA)lpTimeBaseValue;
  VAR(StbM_RateCorrectionType, AUTOMATIC)rateCorrection;
  VAR(uint32, AUTOMATIC)lulRateDeviation;
  VAR(uint16, AUTOMATIC)lusRateDeviation;
  VAR(StbM_RateDeviationType, AUTOMATIC)lddRateDeviation;  
  
  lpTimeBaseValue = &StbM_GaaTimeBaseValue[lusConfigPtr];
  /* Check vaild rate */
  /* @Trace: StbM_SUD_API_541 */
  if(STBM_TRUE != (lpTimeBaseValue->ucRateValid))
  {
    lddReturnVal = E_NOT_OK;
  }
  else
  {
    lddReturnVal = E_OK;
  }

  rateCorrection = (uint32)lpTimeBaseValue->ddRate; 
  if((lusConfigPtr >=  STBM_NUMBER_SYNC_TIME_BASES_CONFIGURED) &&
     (lusConfigPtr <  (STBM_NUMBER_SYNC_TIME_BASES_CONFIGURED +
                      STBM_NUMBER_OFFSET_TIME_BASES_CONFIGURED)))

  {
    /* If out of range of Deviation */
    if(STBM_RATE_DEVIATION_MAX <= rateCorrection)
    {
      lddRateDeviation = (StbM_RateDeviationType)STBM_RATE_DEVIATION_MAX;
    }
    else
    {
      lddRateDeviation = (StbM_RateDeviationType)((uint16)rateCorrection);   
    }
  }
  else
  {
    /* If out of range of Deviation */
    if(STBM_RATE_CORRECTION_ALLOW_MAX <= rateCorrection)
    {
      lddRateDeviation = (StbM_RateDeviationType)STBM_RATE_DEVIATION_MAX;
    }
    /* If out of range of Deviation */
    else if(STBM_RATE_CORRECTION_ALLOW_MIN >= rateCorrection)
    {
      lddRateDeviation = (StbM_RateDeviationType)(STBM_ZERO - STBM_RATE_DEVIATION_MAX);
    }
    else if(STBM_RATE_CORRECTION_ONE <= rateCorrection)
    {
      lulRateDeviation = (uint32)(rateCorrection - STBM_RATE_CORRECTION_ONE);
      lddRateDeviation = (StbM_RateDeviationType)lulRateDeviation;
    }
    else
    {
      lusRateDeviation = (uint16)(STBM_RATE_CORRECTION_ONE - rateCorrection);  
      lddRateDeviation = (StbM_RateDeviationType)(lusRateDeviation);
      lddRateDeviation = STBM_ZERO - lddRateDeviation;
    }
  }
  /* Set output */
  *rateDeviation = lddRateDeviation;
  
  return (lddReturnVal);
} /* End of StbM_Internal_CalRateDeviation(void) */

#define STBM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : StbM_Internal_SetRateDeviation                      **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Convert StbM_RateDeviationType to                   **
**                                StbM_RateCorrectionType                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : lusConfigPtr: ptr of StbM_GaaTimeBaseConfig         **
**                        rateDeviation: StbM_RateDeviationType               **
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
**                                StbM_GaaTimeBaseValue                       **
**                                StbM_GaaTimeTuple                           **
**                        Function(s) invoked :                               **
**                                StbM_Internal_GetCurrentTime                **
*******************************************************************************/
/* @Trace: RS_TS_00018 */
#define STBM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, STBM_CODE) StbM_Internal_SetRateDeviation(
  VAR(uint16, AUTOMATIC)lusConfigPtr,
  VAR(StbM_RateDeviationType, AUTOMATIC)rateDeviation)
{
  Std_ReturnType lddReturnVal;

  P2CONST(StbM_TimeBaseConfigType, AUTOMATIC, STBM_APPL_DATA)lpTimeBaseConfig;
  P2CONST(StbM_TimeCorrectionConfigType, AUTOMATIC, STBM_APPL_DATA)
                                lpTimeCorrectionConfig;
  P2VAR(StbM_TimeBaseValueType, AUTOMATIC, STBM_APPL_DATA)lpTimeBaseValue;
  P2VAR(StbM_TimeTupleType, AUTOMATIC, STBM_APPL_DATA)lpTimeTuple;
  VAR(StbM_TimeStampType, AUTOMATIC)lddTimeStamp;
  VAR(StbM_VirtualLocalTimeType, AUTOMATIC)lddVlt;
  VAR(sint32, AUTOMATIC)lusRate;
  VAR(sint32, AUTOMATIC)lusRateMax;
  
  /* Check StbMAllowMasterRateCorrection  */
  /* @Trace: StbM_SUD_API_551 */
  lddReturnVal = E_OK;
  
  STBM_INIT_VLTIME(&lddVlt);
  
  lpTimeBaseConfig = &StbM_GaaTimeBaseConfig[lusConfigPtr];
  if(STBM_BASE_INVAILD != (lpTimeBaseConfig->ucBaseOfCorrection))
  {    
    lpTimeCorrectionConfig = &StbM_GaaTimeCorrectionConfig
                              [lpTimeBaseConfig->ucBaseOfCorrection];
    /* @Trace: SWS_StbM_00395 */ 
    if(STBM_FALSE == (lpTimeCorrectionConfig->blMaster))
    {
      lddReturnVal = E_NOT_OK;
    }
    else
    { 
      lpTimeBaseValue = &StbM_GaaTimeBaseValue[lusConfigPtr];
      lusRateMax = (sint32)(lpTimeCorrectionConfig->ulRateDeviationMax);
      /* @Trace: SWS_StbM_00396 */
      if((sint32)rateDeviation >= (sint32)lusRateMax)
      {
        lusRate = (sint32)lusRateMax;
      }
      else if((sint32)STBM_ZERO >= ((sint32)rateDeviation + (sint32)lusRateMax))
      {
        lusRate = (sint32)STBM_ZERO - (sint32)(lusRateMax); 
      } 
      else
      {
        lusRate = (sint32)rateDeviation;    
      } 

      /* @Trace: SWS_StbM_00411 */ 
      if((lusConfigPtr >=  STBM_NUMBER_SYNC_TIME_BASES_CONFIGURED) &&
         (lusConfigPtr <  (STBM_NUMBER_SYNC_TIME_BASES_CONFIGURED +
                      STBM_NUMBER_OFFSET_TIME_BASES_CONFIGURED)))

      {
        if((sint32)lusRate > (sint32)STBM_ZERO)
        {
          lpTimeBaseValue->ddRate = (StbM_RateCorrectionType)lusRate;
        }
        else
        {
          /* Ignore with negative values */
          /* Do nothing */
        }
      }
      else
      {
        lpTimeBaseValue->ddRate =(StbM_RateCorrectionType)
            (sint32)(lusRate) + (sint32)(STBM_RATE_CORRECTION_ONE);  
      }       
      lpTimeBaseValue->ucRateValid = STBM_TRUE;         
      /* Update Main Timetuple */                   
      /* @Trace: SWS_StbM_00424 */                   
      /* @Trace: SWS_StbM_00442 */                   
      /* @Trace: SWS_StbM_00443 */                   
      (void) StbM_Internal_GetCurrentTime(lusConfigPtr,
                      &lddTimeStamp, &lddVlt, NULL_PTR);
      lpTimeTuple = &StbM_GaaTimeTuple[lusConfigPtr];
      STBM_COPY_VLTIME(&(lpTimeTuple->ddVirtualLocalTime),&lddVlt);
      STBM_COPY_TIMESTAMP(&(lpTimeTuple->ddLocalTime), &lddTimeStamp);          
    }
  }
  else
  {
    /* Do nothing */
  }
 
  return (lddReturnVal);
} /* End of StbM_Internal_SetRateDeviation(void) */

#define STBM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : StbM_Internal_TimerNotification                     **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Internal Operation for Time Nofiticaiton            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : lusConfigPtr: ptr of StbM_GaaTimeBaseConfig         **
**                        lddTimeStamp: StbM_TimeStampType                    **
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
**                                StbM_GaaTimeBaseValue                       **
**                                StbM_GaaNotificationValue                   **
**                                StbM_GaaCallBackParameterValue              **
**                        Function(s) invoked :                               **
**                                StbM_Math_DiffOfTwoTimeStamp                **
**                                StbM_Math_ConvertTimeStampToRaw             **
**                                Gpt_StartTimer                              **
**                                StbM_TimeNotificationCallback               **
*******************************************************************************/
#if (STD_ON == STBM_TIME_NOTIFICATION_SUPPORT)
/* @Trace: RS_TS_00002, RS_TS_00017 */
#define STBM_START_SEC_CODE
#include "MemMap.h"

FUNC(void, STBM_CODE) StbM_Internal_TimerNotification(
  VAR(uint16, AUTOMATIC)lusConfigPtr,
  VAR(StbM_TimeStampType, AUTOMATIC)lddTimeStamp)
{
  Std_ReturnType lddReturnVal;
  Std_ReturnType lddLoopBreak;
  
  P2CONST(StbM_TimeBaseConfigType, AUTOMATIC, STBM_APPL_DATA)lpTimeBaseConfig;
  P2VAR(StbM_TimeBaseValueType, AUTOMATIC, STBM_APPL_DATA)lpTimeBaseValue;
  P2VAR(StbM_NotificationValueType, AUTOMATIC, STBM_APPL_DATA)lpNotificationValue;
  VAR(uint16, AUTOMATIC)lusNotificationPtr;
  VAR(uint16, AUTOMATIC)lusBaseOfNotification;
  VAR(uint16, AUTOMATIC)lusEndOfNotification;
  VAR(uint64, AUTOMATIC)lulGptTimeValue;
  VAR(uint32, AUTOMATIC)lulGptTickValue;
  VAR(StbM_TimeStampType, AUTOMATIC)lddElapsedStamp;
 
  lpTimeBaseValue = &StbM_GaaTimeBaseValue[lusConfigPtr];
  lpTimeBaseConfig = &StbM_GaaTimeBaseConfig[lusConfigPtr];
  
  STBM_INIT_TIMESTAMP(&lddElapsedStamp);
  
  /* check start gpt flag */
  if(STBM_ZERO != (lpTimeBaseValue->blStartTimerCount))
  {        
    lusBaseOfNotification = (lpTimeBaseConfig)->usBaseOfNotification;
    lusEndOfNotification = lusBaseOfNotification +   
                            (lpTimeBaseConfig)->usSizeOfNotification; 
    lddLoopBreak = E_NOT_OK;
    for(lusNotificationPtr = lusBaseOfNotification; lusNotificationPtr < 
                 lusEndOfNotification; lusNotificationPtr++)
    {
      if(E_NOT_OK==lddLoopBreak)
      {
        lpNotificationValue = &StbM_GaaNotificationValue[lusNotificationPtr];
        /* @Trace: StbM_SUD_API_561 */
        if(STBM_TRUE == (lpNotificationValue->blStartTimer))
        {
          /* difference between the current value of the corresponding  */ 
          /* Time Base and the expiration time CustomerTimerExpireTime */
          /* @Trace: SWS_StbM_00335 */
          lddReturnVal = StbM_Math_DiffOfTwoTimeStamp(lddTimeStamp, 
                  lpNotificationValue->CustomerTimerExpireTime,  
                  &lddElapsedStamp);
          if(E_OK == lddReturnVal)
          {
            StbM_Math_ConvertTimeStampToRaw(lddElapsedStamp, (&lulGptTimeValue));
            if((STBM_TIME_START_THRESHOLD > STBM_ZERO) && (lulGptTimeValue < STBM_TIME_START_THRESHOLD))
            {      
              /* Set ptr of call back function*/ 
              StbM_GaaCallBackParameterValue.usId = lusNotificationPtr;
              /* @Trace: SWS_StbM_00336 */ 
              /* @Trace: SWS_StbM_00337 */ 
              lulGptTickValue = (uint32) 
                  (lulGptTimeValue / STBM_GPT_CHANNEL_NANO_SECOND_EACH_TICK);
              if(STBM_ZERO != lulGptTickValue)
              {       
                /* Set diff time of call back function*/ 
                StbM_GaaCallBackParameterValue.ddTimeDiff = 
                                      (StbM_TimeDiffType)STBM_ZERO;     
                /* In case use GPT interrupt, set enCbk */ 
                StbM_GaaCallBackParameterValue.enCbk = STBM_TRUE;
                /* Set trigger time for GPT */
                Gpt_StartTimer((Gpt_ChannelType) 
                    STBM_GPT_CHANNEL_CONFIGURATION_ID,  
                    (Gpt_ValueType) lulGptTickValue);
                /* End loop */ 
                lddLoopBreak = E_OK;
              }
              /* @Trace: StbM_SUD_API_562 */
              else
              {        
                /* Set diff time of call back function*/ 
                StbM_GaaCallBackParameterValue.ddTimeDiff = (StbM_TimeDiffType)lulGptTimeValue;
                /* @Trace: SWS_StbM_00432 */
                StbM_TimeNotificationCallback();
              }
            }
            else
            {
              /* Do nothing */
            }              
          }
          else
          {   
            /* Set ptr of call back function*/ 
            StbM_GaaCallBackParameterValue.usId = lusNotificationPtr;       
            /* In overtime case, Diff time set ZERO */ 
            StbM_GaaCallBackParameterValue.ddTimeDiff = STBM_ZERO;
            /* @Trace: SWS_StbM_00432 */
            StbM_TimeNotificationCallback();
          }
        }
        else
        {
          /* Do nothing */
        }
      }
      else
      {/* polyspace RTE:UNR [Not a defect:Low] "This branch is available for other configuration" */
        /* Do nothing */
      }
    }    
  } 
  else
  {
    /* Do nothing */
  }
} /* End of StbM_Internal_TimerNotification(void) */

#define STBM_STOP_SEC_CODE
#include "MemMap.h"
#endif /*(STD_ON == STBM_TIME_NOTIFICATION_SUPPORT)*/
/*******************************************************************************
** Function Name        : StbM_Internal_Trigger                               **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Internal Operation for Trigged Customer             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : lusConfigPtr: ptr of StbM_GaaTimeBaseConfig         **
**                        lddTimeStamp: StbM_TimeStampType                    **
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
**                                StbM_GaaTimeBaseValue                       **
**                                StbM_GaaTriggeredValue                      **
**                        Function(s) invoked :                               **
**                                StbM_Math_DiffOfTwoTimeStamp                **
**                                StbM_Math_ConvertTimeStampToRaw             **
**                                GetScheduleTableStatus                      **
**                                SyncScheduleTable                           **
*******************************************************************************/
#if (STD_ON == STBM_TRIGGERED_CUSTOMER_SUPPORT)
/* @Trace: RS_TS_00032 */
#define STBM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, STBM_CODE) StbM_Internal_Trigger(
  VAR(uint16, AUTOMATIC)lusConfigPtr,
  VAR(StbM_TimeStampType, AUTOMATIC)lddTimeStamp)
{
  P2CONST(StbM_TimeBaseConfigType, AUTOMATIC, STBM_APPL_DATA)lpTimeBaseConfig;
  P2CONST(StbM_TriggeredConfigType, AUTOMATIC, STBM_APPL_DATA)lpTriggeredConfig;
  P2VAR(StbM_TriggeredValueType, AUTOMATIC, STBM_APPL_DATA)lpTriggeredValue;
  
  VAR(uint16, AUTOMATIC)lusCount;
  VAR(uint8, AUTOMATIC)lusStartPtr;
  VAR(uint8, AUTOMATIC)lusEndPtr;
  VAR(uint32, AUTOMATIC)lulvalue;
  VAR(uint64, AUTOMATIC)lulElapsedTimeRaw;
  VAR(uint64, AUTOMATIC)lulTimeStamp;
  VAR(uint64, AUTOMATIC)lulOsMicroSecondsPerTick;
  VAR(StbM_TimeStampType, AUTOMATIC)lulElapsedTimeStamp;
  VAR(StatusType, AUTOMATIC)lddStatus;
  VAR(ScheduleTableStatusType, AUTOMATIC)lucScheduleStatus;
   
  STBM_INIT_TIMESTAMP(&lulElapsedTimeStamp);
  lucScheduleStatus = SCHEDULETABLE_STOPPED;
  
  lpTimeBaseConfig = &StbM_GaaTimeBaseConfig[lusConfigPtr];
  if(STBM_ZERO < (lpTimeBaseConfig->ucSizeOfTriggered))
  {
    lusStartPtr = lpTimeBaseConfig->ucBaseOfTriggered;
    lusEndPtr = lusStartPtr + lpTimeBaseConfig->ucSizeOfTriggered;
    for(lusCount = lusStartPtr; lusCount < lusEndPtr; lusCount++)
    {
      lpTriggeredConfig = &StbM_GaaTriggeredConfig[lusCount];
      lpTriggeredValue = &StbM_GaaTriggeredValue[lusCount];     
      (void) StbM_Math_DiffOfTwoTimeStamp(lpTriggeredValue->time,lddTimeStamp, &lulElapsedTimeStamp);
      StbM_Math_ConvertTimeStampToRaw(lulElapsedTimeStamp,&lulElapsedTimeRaw);
      /* @Trace: StbM_SUD_API_571 */
      if(lulElapsedTimeRaw > (lpTriggeredConfig->ulPeriod))
      {
        lddStatus = GetScheduleTableStatus(
                   (ScheduleTableType)(lpTriggeredConfig->ulScheduleTableId),
                   (ScheduleTableStatusRefType)(&lucScheduleStatus));
        if((E_OK == lddStatus) &&
        /* @Trace: SWS_StbM_00092 */
           ((SCHEDULETABLE_WAITING ==lucScheduleStatus) ||
            (SCHEDULETABLE_RUNNING ==lucScheduleStatus) ||
            (SCHEDULETABLE_RUNNING_AND_SYNCHRONOUS ==lucScheduleStatus)))
        {
          /* Convert localTimeStamp to micro second */
          lulTimeStamp = (uint64)(lddTimeStamp.seconds) | (((uint64)
                        (lddTimeStamp.secondsHi))<<STBM_THIRTY_TWO);
          lulTimeStamp = lulTimeStamp *  STBM_SEC_IN_MICROSEC;
          lulTimeStamp = lulTimeStamp + (uint64)((uint32)
                         (lddTimeStamp.nanoseconds / STBM_MICROSEC_IN_NANOSEC));
          /* @Trace: SWS_StbM_00303 */
          /* Convert localTimeStamp to Os tick */
          lulOsMicroSecondsPerTick = (lpTriggeredConfig->ulOsSecondsPerTick);
          lulvalue = (uint32)(lulTimeStamp % (lulOsMicroSecondsPerTick * lpTriggeredConfig->ulScheduleTableDuration));
          lulvalue = (TickType)(lulvalue / lulOsMicroSecondsPerTick);
          /* @Trace: SWS_StbM_00302 */
          (void) SyncScheduleTable((ScheduleTableType)
                  (lpTriggeredConfig->ulScheduleTableId), lulvalue);
          STBM_COPY_TIMESTAMP(&(lpTriggeredValue->time), &lddTimeStamp);
        }
        /* @Trace: StbM_SUD_API_572 */
        else
        {
          /* Do nothing */
        }
      }
      /* @Trace: StbM_SUD_API_573 */
      else
      {
        /* Do nothing */
      } 
    }
  }
  /* @Trace: StbM_SUD_API_574 */
  else
  {
    /* Do nothing */
  }
} /* End of StbM_Internal_Trigger(void) */

#define STBM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* STD_ON == STBM_TRIGGERED_CUSTOMER_SUPPORT */

/*******************************************************************************
** Function Name        : StbM_TimeNotificationCallback                       **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Internal function that call by Main function        **
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
** Remarks              : Global Variable(s)  :                               **
**                                StbM_GaaTimeBaseValue                       **
**                                StbM_GaaNotificationValue                   **
**                        Function(s) invoked : None                          **
*******************************************************************************/
/* @Trace: RS_TS_00017 */
#define STBM_START_SEC_CODE
#include "MemMap.h"

FUNC(void, STBM_CODE) StbM_TimeNotificationCallback(void)
{
  P2VAR(StbM_TimeBaseValueType, AUTOMATIC, STBM_APPL_DATA)lpTimeBaseValue;
  P2CONST(StbM_NotificationConfigType, AUTOMATIC, STBM_APPL_DATA)lpConfig;
  P2VAR(StbM_NotificationValueType, AUTOMATIC, STBM_APPL_DATA)lpValue;
   
  lpConfig = & StbM_GaaNotificationConfig[StbM_GaaCallBackParameterValue.usId]; 
  lpTimeBaseValue = & StbM_GaaTimeBaseValue[lpConfig->ddTimeBaseId]; 
  lpValue = & StbM_GaaNotificationValue[StbM_GaaCallBackParameterValue.usId]; 
  /* @Trace: SWS_StbM_00271 */
  /* @Trace: StbM_SUD_API_591 */
  #if(STBM_NUMBER_NOTIFICATION_CUSTOMER_CONFIGURED > 0)
  (void)(*(lpConfig->pCallback))(StbM_GaaCallBackParameterValue.ddTimeDiff);
  #endif
  /* Clear request callback function */
  
  lpValue->blStartTimer = STBM_FALSE;
  lpTimeBaseValue->blStartTimerCount =  
                            lpTimeBaseValue->blStartTimerCount - STBM_ONE;
} /* End of StbM_TimeNotificationCallback(void) */

#define STBM_STOP_SEC_CODE
#include "MemMap.h"

#if (STD_ON == STBM_DEV_ERROR_DETECT)
/*******************************************************************************
** Function Name        : StbM_CheckSyncOffsetTimeBaseID                      **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Internal function that checks the valid of          **
**                        synchronous time base ID.                           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : Std_ReturnType: InputErr                            **
**                        StbM_SynchronizedTimeBaseType: timeBaseId           **
**                        uint8: ServiceID                                    **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : STD_ON == STBM_DEV_ERROR_DETECT                     **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
**                        Function(s) invoked : Det_ReportError               **
*******************************************************************************/

#define STBM_START_SEC_CODE
#include "MemMap.h"

FUNC(Std_ReturnType, STBM_CODE) StbM_CheckSyncOffsetTimeBaseID(
	Std_ReturnType	InputErr,
  StbM_SynchronizedTimeBaseType timeBaseId,
  uint8 ServiceID)
{
	/* @Trace: StbM_SUD_API_592 */
	Std_ReturnType StbM_LddReturnVal = InputErr;
	if(StbM_LddReturnVal == E_OK)
	{
		if(!((timeBaseId <= STBM_MAX_SYNC_TIME_BASES_CONFIGURED) ||
		((timeBaseId >= STBM_SIXTEEN) &&
		(timeBaseId <= STBM_MAX_OFFSET_TIME_BASES_CONFIGURED))))
		{
			/* @Trace: StbM_SUD_API_593 */
			(void)Det_ReportError(STBM_MODULE_ID, STBM_INSTANCE_ID,
											ServiceID, STBM_E_PARAM);
			StbM_LddReturnVal = E_NOT_OK;
		}
		else
		{
			/* Do nothing */
		}
	}
  else
  {
  	/* Do nothing */
  }
	return StbM_LddReturnVal;
}

#define STBM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : StbM_CheckInvalid3Pointer                           **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Internal function that checks the valid of          **
**                        input pointer                                       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : Std_ReturnType: InputErr                            **
**                        const void*: CheckPtr1                              **
**                        const void*: CheckPtr2                              **
**                        const void*: CheckPtr3                              **
**                        uint8: ApiID                                        **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : STD_ON == STBM_DEV_ERROR_DETECT                     **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
**                        Function(s) invoked : Det_ReportError               **
*******************************************************************************/

#define STBM_START_SEC_CODE
#include "MemMap.h"

FUNC(Std_ReturnType, STBM_CODE) StbM_CheckInvalid3Pointer(
	Std_ReturnType InputErr,
	P2CONST(void, AUTOMATIC, STBM_APPL_DATA) CheckPtr1,
	P2CONST(void, AUTOMATIC, STBM_APPL_DATA) CheckPtr2,
	P2CONST(void, AUTOMATIC, STBM_APPL_DATA) CheckPtr3,
	uint8 ApiID)
{
	/* @Trace: StbM_SUD_API_594 */
	Std_ReturnType StbM_LddReturnVal = InputErr;
	if(StbM_LddReturnVal == E_OK)
	{
		if((CheckPtr1 == NULL_PTR) || (CheckPtr2 == NULL_PTR) || (CheckPtr3 == NULL_PTR))
		{
			/* @Trace: StbM_SUD_API_595 */
			(void)Det_ReportError(STBM_MODULE_ID, STBM_INSTANCE_ID,
					ApiID, STBM_E_PARAM_POINTER);
			StbM_LddReturnVal = E_NOT_OK;
		}
		else
		{
			/* Do nothing */
		}
	}
	else
	{
		/* Do nothing */
	}
	return StbM_LddReturnVal;
}

#define STBM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : StbM_CheckInvalid2Pointer                           **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Internal function that checks the valid of          **
**                        input pointer                                       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : Std_ReturnType: InputErr                            **
**                        const void*: CheckPtr1                              **
**                        const void*: CheckPtr2                              **
**                        uint8: ServiceID                                    **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : STD_ON == STBM_DEV_ERROR_DETECT                     **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
**                        Function(s) invoked : Det_ReportError               **
*******************************************************************************/

#define STBM_START_SEC_CODE
#include "MemMap.h"

FUNC(Std_ReturnType, STBM_CODE) StbM_CheckInvalid2Pointer(
	Std_ReturnType InputErr,
	P2CONST(void, AUTOMATIC, STBM_APPL_DATA) CheckPtr1,
	P2CONST(void, AUTOMATIC, STBM_APPL_DATA) CheckPtr2,
	uint8 ApiID)
{
	/* @Trace: StbM_SUD_API_596 */
	Std_ReturnType StbM_LddReturnVal = InputErr;
	if(StbM_LddReturnVal == E_OK)
	{
		if((CheckPtr1 == NULL_PTR) || (CheckPtr2 == NULL_PTR))
		{
			/* @Trace: StbM_SUD_API_597 */
			(void)Det_ReportError(STBM_MODULE_ID, STBM_INSTANCE_ID,
					ApiID, STBM_E_PARAM_POINTER);
			StbM_LddReturnVal = E_NOT_OK;
		}
		else
		{
			/* Do nothing */
		}
	}
	else
	{
		/* Do nothing */
	}
	return StbM_LddReturnVal;
}

#define STBM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : StbM_CheckInvalid1Pointer                           **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Internal function that checks the valid of          **
**                        input pointer                                       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : Std_ReturnType: InputErr                            **
**                        const void*: CheckPtr                               **
**                        uint8: ApiID                                        **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : STD_ON == STBM_DEV_ERROR_DETECT                     **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
**                        Function(s) invoked : Det_ReportError               **
*******************************************************************************/

#define STBM_START_SEC_CODE
#include "MemMap.h"

FUNC(Std_ReturnType, STBM_CODE) StbM_CheckInvalid1Pointer(
	Std_ReturnType InputErr,
	P2CONST(void, AUTOMATIC, STBM_APPL_DATA) CheckPtr,
	uint8 ApiID)
{
	/* @Trace: StbM_SUD_API_598 */
	Std_ReturnType StbM_LddReturnVal = InputErr;
	if(StbM_LddReturnVal == E_OK)
	{
		if(CheckPtr == NULL_PTR)
		{
			/* @Trace: StbM_SUD_API_599 */
			(void)Det_ReportError(STBM_MODULE_ID, STBM_INSTANCE_ID,
					ApiID, STBM_E_PARAM_POINTER);
			StbM_LddReturnVal = E_NOT_OK;
		}
		else
		{
			/* Do nothing */
		}
	}
	else
	{
		/* Do nothing */
	}
	return StbM_LddReturnVal;
}

#define STBM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : StbM_CheckInitStatus                                **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Internal function that checks the valid of          **
**                        input pointer                                       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : Std_ReturnType: InputErr                            **
**                        uint8: ApiID                                        **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : STD_ON == STBM_DEV_ERROR_DETECT                     **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
**                        Function(s) invoked : Det_ReportError               **
*******************************************************************************/

#define STBM_START_SEC_CODE
#include "MemMap.h"

FUNC(Std_ReturnType, STBM_CODE) StbM_CheckInitStatus(
	Std_ReturnType InputErr,
	uint8 ApiID)
{
	/* @Trace: StbM_SUD_API_600 */
	Std_ReturnType StbM_LddReturnVal = InputErr;
		if(STBM_UNINITIALIZED == StbM_GblInitStatus)
		{
			/* @Trace: StbM_SUD_API_601 */
			(void)Det_ReportError(STBM_MODULE_ID, STBM_INSTANCE_ID,
					ApiID, STBM_E_UNINIT);
			StbM_LddReturnVal = E_NOT_OK;
		}
		else
		{
			/* Do nothing */
		}
	return StbM_LddReturnVal;
}

#define STBM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : StbM_CheckTimeBaseID                                **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Internal function that checks the valid of          **
**                        time base ID                                        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : Std_ReturnType: InputErr                            **
**                        StbM_TimeStampType: timeBaseId                      **
**                        uint8: ApiID                                        **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : STD_ON == STBM_DEV_ERROR_DETECT                     **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
**                        Function(s) invoked : Det_ReportError               **
*******************************************************************************/

#define STBM_START_SEC_CODE
#include "MemMap.h"

FUNC(Std_ReturnType, STBM_CODE) StbM_CheckTimeBaseID(
	Std_ReturnType InputErr,
  StbM_SynchronizedTimeBaseType timeBaseId,
	uint8 ApiID)
{
	/* @Trace: StbM_SUD_API_602 */
	Std_ReturnType StbM_LddReturnVal = InputErr;
  if(E_OK == StbM_LddReturnVal)
  {
    if(((timeBaseId > STBM_MAX_SYNC_TIME_BASES_CONFIGURED) &&
         (timeBaseId < STBM_SIXTEEN)) ||
               ((timeBaseId > STBM_MAX_OFFSET_TIME_BASES_CONFIGURED)&&
         (timeBaseId < STBM_THIRTY_TWO)) ||
               (timeBaseId > STBM_MAX_PURE_TIME_BASES_CONFIGURED))
    {
    	/* @Trace: StbM_SUD_API_603 */
      (void)Det_ReportError(STBM_MODULE_ID, STBM_INSTANCE_ID,
      		ApiID, STBM_E_PARAM);
      StbM_LddReturnVal = E_NOT_OK;
    }
    else
    {
    	/* Do nothing */
    }
  }
  else
  {
  	/* Do nothing */
  }
  return StbM_LddReturnVal;
}

#define STBM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* (STD_ON == STBM_DEV_ERROR_DETECT) */

/*******************************************************************************
** Function Name        : StbM_IntprocessOfBusSetGlobalTime                   **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Internal function that handles internal process of  **
**                        StbM_BusSetGlobalTime function.                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : StbM_TimeStampType: globalTimePtr                   **
**                        uint16: lusConfigPtr                                **
**                        const StbM_UserDataType*: userData                  **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
**                        Function(s) invoked :                               **
**                        StbM_Internal_IncreaseCounterOfTimeBase             **
**                        StbM_Internal_UpdateStatusOfTimeBase                **
**                                                                            **
*******************************************************************************/
#define STBM_START_SEC_CODE
#include "MemMap.h"

FUNC(void, STBM_CODE) StbM_IntprocessOfBusSetGlobalTime(
		P2CONST(StbM_TimeStampType, AUTOMATIC, STBM_APPL_DATA)globalTimePtr,
		VAR(uint16, AUTOMATIC)lusConfigPtr,
		P2CONST(StbM_UserDataType, AUTOMATIC, STBM_APPL_DATA)userData)
{
	/* @Trace: StbM_SUD_API_608 */
	P2VAR(StbM_TimeBaseValueType, AUTOMATIC, STBM_APPL_DATA)lpTimeBaseValue;
	lpTimeBaseValue = &StbM_GaaTimeBaseValue[lusConfigPtr];
  /* @Trace: SWS_StbM_00187 */
  STBM_COPY_TIMESTAMP(&(lpTimeBaseValue->ddLocalTime), globalTimePtr);
  /* Update main userData */
  /* polyspace +1 MISRA-C3:D4.14 [Not a defect:Low] "This pointer is manual checked and has no impact" */
  STBM_SET_USERDATA(&(lpTimeBaseValue->ddUserData), userData);
  /* @Trace: SWS_StbM_00350 */
  /* Update timeBaseUpdateCounter */
  (void) StbM_Internal_IncreaseCounterOfTimeBase(lusConfigPtr);
  /* An invocation of StbM_BusSetGlobalTime API shall clear the TIMEOUT bit. */
  /* @Trace: SWS_StbM_00185 */
  (void) StbM_Internal_UpdateStatusOfTimeBase(lusConfigPtr,
                    STBM_STATE_GLOBAL_TIME_BASE, STBM_TRUE);
  /* @Trace: SWS_StbM_00184 */
  if(STBM_ZERO != ((globalTimePtr->timeBaseStatus) &
                            STBM_STATE_SYNC_TO_GATEWAY))
  {
  	/* @Trace: StbM_SUD_API_609 */
    (void)StbM_Internal_UpdateStatusOfTimeBase(lusConfigPtr,
                    STBM_STATE_SYNC_TO_GATEWAY, STBM_TRUE);
  }
  else
  {
  	/* @Trace: StbM_SUD_API_610 */
    (void) StbM_Internal_UpdateStatusOfTimeBase(lusConfigPtr,
                    STBM_STATE_SYNC_TO_GATEWAY, STBM_FALSE);
  }
  /* @Trace: SWS_StbM_00183 */
  /* @Trace: SWS_StbM_00187 */
  /* @Trace: StbM_SUD_API_611 */
  (void)StbM_Internal_UpdateStatusOfTimeBase(lusConfigPtr,
                    STBM_STATE_TIMEOUT, STBM_FALSE);
}

#define STBM_STOP_SEC_CODE
#include "MemMap.h"

#if(STD_ON == STBM_TIME_RECORDING_SUPPORT)
/*******************************************************************************
** Function Name        : StbM_InitTimeRecording                              **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Internal function that Initializes all Block        **
**                        Elements of the measurement recording table with    **
**                        zero when STBM_TIME_RECORDING_SUPPORT is enabled.   **
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
** Preconditions        : STD_ON == STBM_TIME_RECORDING_SUPPORT               **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
**                        Function(s) invoked : None                          **
*******************************************************************************/
#define STBM_START_SEC_CODE
#include "MemMap.h"

FUNC(void, STBM_CODE) StbM_InitTimeRecording(void)
{
	#if((STBM_ZERO < STBM_NUMBER_SYNC_TIME_RECORD_TABLE_CONFIGURED)||\
			(STBM_ZERO < STBM_NUMBER_OFFSET_TIME_RECORD_TABLE_CONFIGURED))
	uint16 lusIndex;
	uint16 lusSize;
  uint16 lusCount;
	#endif
	#if(STBM_ZERO < STBM_NUMBER_SYNC_TIME_RECORD_TABLE_CONFIGURED)
	P2VAR(StbM_SyncRecordTableBlockType, AUTOMATIC, STBM_APPL_DATA)lpSyncRecord;
  for(lusCount = (uint16)STBM_ZERO; lusCount <(uint16)
          (STBM_NUMBER_SYNC_TIME_RECORD_TABLE_CONFIGURED); lusCount++)
  {
  	/* @Trace: StbM_SUD_API_604 */
    lusSize = StbM_GaaSyncTimeRecordingConfig[lusCount].usCount;
    for(lusIndex = (uint16)STBM_ZERO; lusIndex <lusSize; lusIndex++)
    {
    	/* @Trace: StbM_SUD_API_605 */
      lpSyncRecord = &(StbM_GaaSyncTimeRecordingConfig[lusCount].pAddress[lusIndex]);
      lpSyncRecord->GlbSeconds = (uint32)STBM_ZERO;
      lpSyncRecord->GlbNanoSeconds = (uint32)STBM_ZERO;
      lpSyncRecord->TimeBaseStatus = (StbM_TimeBaseStatusType)STBM_ZERO;
      lpSyncRecord->VirtualLocalTimeLow = (uint32)STBM_ZERO;
      lpSyncRecord->RateDeviation = (StbM_RateDeviationType)STBM_ZERO;
      lpSyncRecord->LocSeconds = (uint32)STBM_ZERO;
      lpSyncRecord->LocNanoSeconds = (uint32)STBM_ZERO;
      lpSyncRecord->PathDelay = (uint32)STBM_ZERO;
    }
  }
	#endif /* STBM_ZERO < STBM_NUMBER_SYNC_TIME_RECORD_TABLE_CONFIGURED */
	#if(STBM_ZERO < STBM_NUMBER_OFFSET_TIME_RECORD_TABLE_CONFIGURED)
  P2VAR(StbM_OffsetRecordTableBlockType, AUTOMATIC, STBM_APPL_DATA)lpOffsetRecord;
  for(lusCount = (uint16)STBM_ZERO; lusCount <(uint16)
          (STBM_NUMBER_OFFSET_TIME_RECORD_TABLE_CONFIGURED); lusCount++)
  {
  	/* @Trace: StbM_SUD_API_606 */
    lusSize = StbM_GaaOffsetTimeRecordingConfig[lusCount].usCount;
    for(lusIndex = (uint16)STBM_ZERO; lusIndex <lusSize; lusIndex++)
    {
    	/* @Trace: StbM_SUD_API_607 */
      lpOffsetRecord = &(StbM_GaaOffsetTimeRecordingConfig[lusCount].pAddress[lusIndex]);
      lpOffsetRecord->GlbSeconds = (uint32)STBM_ZERO;
      lpOffsetRecord->GlbNanoSeconds = (uint32)STBM_ZERO;
      lpOffsetRecord->TimeBaseStatus = (StbM_TimeBaseStatusType)STBM_ZERO;
    }
  }
  #endif /* STBM_ZERO < STBM_NUMBER_OFFSET_TIME_RECORD_TABLE_CONFIGURED */
}
#define STBM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* STD_ON == STBM_TIME_RECORDING_SUPPORT */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
