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
**  SRC-MODULE: StbM.c                                                        **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Synchronized Time-Base Manager Module                 **
**                                                                            **
**  PURPOSE   : Provision of Autosar API functions and their functionality.   **
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
#include "StbM.h"
/* @Trace: StbM_SUD_FILE_001 */

#include "StbM_Ram.h"

#include "StbM_Internal.h"

#include "StbM_Math.h"

#include "StbM_MacroFunction.h"

/* @Trace: SWS_StbM_00059 */
/* @Trace: SWS_StbM_00246 */
/* @Trace: SWS_StbM_00246 */
/* @Trace: StbM_SDD_DATATYPE_001 */
/* @Trace: StbM_SDD_DATATYPE_002 */
#if (STD_ON == STBM_ETHIF_GLOBAL_TIME_SUPPORT)
/* Ethernet Interface */
#include "EthIf.h"
#endif /* STD_ON == STBM_ETHIF_GLOBAL_TIME_SUPPORT */

/* @Trace: SWS_StbM_00426 */
/* @Trace: StbM_SDD_DATATYPE_003 */
/* @Trace: StbM_SDD_DATATYPE_004 */
#if ((STD_ON == STBM_GPT_GLOBAL_TIME_SUPPORT) || \
       (STD_ON == STBM_TIME_NOTIFICATION_SUPPORT))
/* Timer Driver file inclusion */
#include "Gpt.h"
#endif /* STD_ON == STBM_GPT_GLOBAL_TIME_SUPPORT */

/* OS module header */
#include "Os.h"
/* @Trace: StbM_SDD_DATATYPE_005 */
/* @Trace: StbM_SDD_DATATYPE_006 */
/* @Trace: StbM_SDD_DATATYPE_007 */
/* @Trace: StbM_SDD_DATATYPE_008 */
/* @Trace: StbM_SDD_DATATYPE_009 */
/* @Trace: StbM_SDD_DATATYPE_010 */

/* @Trace: SWS_StbM_00058 */
/* DET module header */
#include "Det.h"

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

/*******************************************************************************
** Function Name        : StbM_GetVersionInfo                                 **
**                                                                            **
** Service ID           : 0x05                                                **
**                                                                            **
** Description          : Returns the version information of StbM module.     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : versionInfo                                         **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : None                          **
**                        Function(s) invoked : Det_ReportError               **
*******************************************************************************/
#if (STD_ON == STBM_VERSION_INFO_API)
#define STBM_START_SEC_CODE
#include "MemMap.h"

FUNC(void, STBM_CODE) StbM_GetVersionInfo(P2VAR(Std_VersionInfoType, 
  AUTOMATIC, STBM_APPL_DATA) versionInfo)
{
  /* @Trace: SWS_StbM_00066 */
  /* Check for DET errors */
  /* @Trace: SWS_StbM_00094 */
  /* @Trace: StbM_SUD_API_221 */
  if (NULL_PTR == versionInfo)
  {
    #if (STD_ON == STBM_DEV_ERROR_DETECT)
    /* Report a null pointer DET error */
    (void) Det_ReportError (STBM_MODULE_ID, STBM_INSTANCE_ID,
                        STBM_GETVERSIONINFO_SID, STBM_E_PARAM_POINTER); /*polyspace MISRA-C:17.7 [Not a defect:Low] "This function isn't required to use return value of sub-function."*/
    #endif /* STD_ON == STBM_DEV_ERROR_DETECT */
  }
  /* @Trace: StbM_SUD_API_222 */
  else
  {
    /* Copy the vendor Id */
    /* polyspace +1 MISRA-C3:D4.14 [Not a defect:Low] "This pointer is manual checked and has no impact" */
    versionInfo->vendorID = STBM_VENDOR_ID; /*polyspace MISRA-C:4.14 [Not a defect:Low] "This parameter is passed by Upper layer. Module only check that it isn't NULL"*/

    /* Copy the module Id */
    versionInfo->moduleID = STBM_MODULE_ID;

    /* Copy Software Major Version */
    versionInfo->sw_major_version = (uint8)STBM_SW_MAJOR_VERSION;

    /* Copy Software Minor Version */
    versionInfo->sw_minor_version = (uint8)STBM_SW_MINOR_VERSION;

    /* Copy Software Patch Version */
    versionInfo->sw_patch_version = (uint8)STBM_SW_PATCH_VERSION;
  }
  
} /* End of StbM_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC,
   * STBM_APPL_DATA) versionInfo) */

#define STBM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* STD_ON == STBM_VERSION_INFO_API */

/*******************************************************************************
** Function Name        : StbM_Init                                           **
**                                                                            **
** Service ID           : 0x00                                                **
**                                                                            **
** Description          : Initializes the StbM module.                        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : ConfigPtr : Pointer Configuration                   **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : StbM_GblInitStatus            **
**                             StbM_GaaTimeBaseValue                          **
**                             StbM_GaaTimeTuple                              **
**                             StbM_GaaOsTimeClockValue                       **
**                             StbM_GaaEthernetTimeClockValue                 **
**                        Function(s) invoked : Det_ReportError               **
*******************************************************************************/
/* @Trace: RS_TS_00002, RS_TS_00003, RS_TS_00007, RS_TS_00011, RS_TS_00015, 
  RS_TS_00017, RS_TS_00018, RS_TS_00022, RS_TS_00034 */
#define STBM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, STBM_CODE) StbM_Init(P2CONST(StbM_ConfigType,
  AUTOMATIC, STBM_APPL_DATA)ConfigPtr)
{
  /* @Trace: SWS_StbM_00052 */
  StbM_GblInitStatus = STBM_UNINITIALIZED;
  P2VAR(StbM_TimeBaseValueType, AUTOMATIC, STBM_APPL_DATA)lpTimeBaseValue; 
  uint16 lusCount;

  #if (STD_ON == STBM_DEV_ERROR_DETECT)
  /* @Trace: StbM_SUD_API_211 */
  if(NULL_PTR != ConfigPtr)
  {
    /* Report a null pointer DET error */
    (void) Det_ReportError (STBM_MODULE_ID, STBM_INSTANCE_ID,
                        STBM_INIT_SID, STBM_E_INIT_FAILED); /*polyspace MISRA-C:17.7 [Not a defect:Low] "This function isn't required to use return value of sub-function."*/
  }
  /* @Trace: StbM_SUD_API_212 */
  else
  #endif /* STD_ON == STBM_DEV_ERROR_DETECT */
  {
    /* Set init status to ON */
    /* @Trace: SWS_StbM_00421 - Gentool */
    /* @Trace: SWS_StbM_00180 - Gentool */
    /* @Trace: SWS_StbM_00413 - Gentool */
    /* @Trace: SWS_StbM_00399 */
    /* @Trace: SWS_StbM_00121 */
    for(lusCount = (uint16)STBM_ZERO; lusCount <(uint16) 
                        (STBM_NUMBER_TIME_BASES_CONFIGURED); lusCount++)
    {
      /* @Trace: SWS_StbM_00170 */
      lpTimeBaseValue = &StbM_GaaTimeBaseValue[lusCount];
      lpTimeBaseValue->ddLocalTime.timeBaseStatus =  
                        (StbM_TimeBaseStatusType)STBM_ZERO;
      /* @Trace: SWS_StbM_00345 */
      lpTimeBaseValue->ulNotificationEvents = (uint16)STBM_ZERO;
      /* @Trace: SWS_StbM_00344 */
      lpTimeBaseValue->timeBaseUpdateCounter = (uint8)STBM_ZERO; 
      /* @Trace: SWS_StbM_00427 */
      lpTimeBaseValue->ddUserData.userDataLength = (uint8)STBM_ZERO;
      lpTimeBaseValue->ddUserData.userByte0 = (uint8)STBM_ZERO;
      lpTimeBaseValue->ddUserData.userByte1 = (uint8)STBM_ZERO;
      lpTimeBaseValue->ddUserData.userByte2 = (uint8)STBM_ZERO;
      
      lpTimeBaseValue->ucFirstSynch = STBM_ZERO;
      /* @Trace: SWS_StbM_00431 */
      if((StbM_GaaTimeBaseConfig[lusCount].ddTimeBaseId >= STBM_SIXTEEN) &&         
           (StbM_GaaTimeBaseConfig[lusCount].ddTimeBaseId <=        
                                 STBM_MAX_OFFSET_TIME_BASES_CONFIGURED))
      {
        lpTimeBaseValue->ddRate = STBM_RATE_CORRECTION_ZERO;
      }
      else
      {
        lpTimeBaseValue->ddRate = STBM_RATE_CORRECTION_ONE;
      } 
      lpTimeBaseValue->ucRateValid = STBM_FALSE; 
      /* Clear all main time tupe */
      StbM_GaaTimeTuple[lusCount].ddLocalTime.nanoseconds = (uint32)STBM_ZERO;
      StbM_GaaTimeTuple[lusCount].ddLocalTime.seconds = (uint32)STBM_ZERO;
      StbM_GaaTimeTuple[lusCount].ddLocalTime.secondsHi = (uint16)STBM_ZERO;
      StbM_GaaTimeTuple[lusCount].ddVirtualLocalTime.nanosecondsLo = (uint32)STBM_ZERO; 
      StbM_GaaTimeTuple[lusCount].ddVirtualLocalTime.nanosecondsHi = (uint32)STBM_ZERO;
    }
    
    /* @Trace: SWS_StbM_00306 */
		#if(STD_ON==STBM_TIME_RECORDING_SUPPORT)
    StbM_InitTimeRecording();
		#endif
    
    #if(STBM_ZERO < STBM_NUMBER_LOCAL_TIME_CLOCK_CONFIGURED)
    for(lusCount = (uint16)STBM_ZERO; lusCount <(uint16) 
            (STBM_NUMBER_LOCAL_TIME_CLOCK_CONFIGURED); lusCount++)
    {
      StbM_GaaOsTimeClockValue[lusCount].ddPreviousTickCount = 
                            (uint32)STBM_ZERO;
      StbM_GaaOsTimeClockValue[lusCount].ddPreviousTimeValue = 
                            (uint64)STBM_ZERO;
    }
    #endif /* STBM_ZERO < STBM_NUMBER_LOCAL_TIME_CLOCK_CONFIGURED */ 
    
    #if(STBM_ZERO < STBM_NUMBER_ETH_TIME_CLOCK_CONFIGURED)
    for(lusCount = (uint16)STBM_ZERO; lusCount <(uint16) 
            (STBM_NUMBER_ETH_TIME_CLOCK_CONFIGURED); lusCount++)
    {
      StbM_GaaEthernetTimeClockValue[lusCount].blFirst = STBM_FALSE;
    }
    #endif /* STBM_ZERO < STBM_NUMBER_ETH_TIME_CLOCK_CONFIGURED */ 

    /* @Trace: SWS_StbM_00100 */
    StbM_GblInitStatus = STBM_INITIALIZED;
  }
} /* End of StbM_Init(void) */

#define STBM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : StbM_GetCurrentTime                                 **
**                                                                            **
** Service ID           : 0x07                                                **
**                                                                            **
** Description          : Returns a time value (Local Time Base derived from  **
**                           Global Time Base) in standard format.            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : timeBaseId : StbM_SynchronizedTimeBaseType          **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : timeStamp : StbM_TimeStampType                      **
**                        userData : StbM_UserDataType                        **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : StbM_GblInitStatus            **
**                        Function(s) invoked : Det_ReportError               **
**                             StbM_Internal_SlaveTimeCorrection              **
*******************************************************************************/
/* @Trace: RS_TS_00005, RS_TS_00006, RS_TS_00013, RS_TS_00014, RS_TS_00015, RS_TS_00029, 
RS_TS_00030, RS_TS_00031 */

#define STBM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, STBM_CODE) StbM_GetCurrentTime(
  VAR(StbM_SynchronizedTimeBaseType, AUTOMATIC)timeBaseId,
  P2VAR(StbM_TimeStampType, AUTOMATIC, STBM_APPL_DATA)timeStamp,
  P2VAR(StbM_UserDataType, AUTOMATIC, STBM_APPL_DATA)userData)
{
  /* @Trace: SWS_StbM_00195 */
  Std_ReturnType lddReturnVal;

  P2VAR(StbM_TimeBaseValueType, AUTOMATIC, STBM_APPL_DATA)lpTimeBaseValue;
  VAR(uint16, AUTOMATIC)lusConfigPtr;
  VAR(StbM_TimeStampType, AUTOMATIC)lddTimeStamp;
  VAR(StbM_VirtualLocalTimeType, AUTOMATIC)lddTimeVlt;
  
  lddReturnVal = E_OK;
  STBM_INIT_VLTIME(&lddTimeVlt);
  /* @Trace: StbM_SUD_API_081 */
  #if (STD_ON == STBM_DEV_ERROR_DETECT)
  STBM_CHECK_INIT(lddReturnVal,STBM_GETCURRENTTIME_SID);
  /* @Trace: SWS_StbM_00196 */  
  lddReturnVal = StbM_CheckTimeBaseID(lddReturnVal,timeBaseId,STBM_GETCURRENTTIME_SID);
  /* @Trace: SWS_StbM_00197 */  
  lddReturnVal = StbM_CheckInvalid2Pointer(lddReturnVal,timeStamp,userData,STBM_GETCURRENTTIME_SID);
  
  if(E_NOT_OK == lddReturnVal)
  {
    /* Do nothing */                          
  }                           
  else                        
  #endif /* STD_ON == STBM_DEV_ERROR_DETECT */
  /* @Trace: StbM_SUD_API_082 */
  { 
    /* Get address of TimeBaseConfig */  
    STBM_GET_ADDRESS_TIME_BASES_CONFIGURED(timeBaseId,lusConfigPtr);
    lpTimeBaseValue = &StbM_GaaTimeBaseValue[lusConfigPtr];
    /* @Trace: SWS_StbM_00177 */
    /* @Trace: SWS_StbM_00434*/
    lddReturnVal = StbM_Internal_GetCurrentTime(
                            lusConfigPtr, &lddTimeStamp, &lddTimeVlt, NULL_PTR);
    if(E_OK == lddReturnVal)
    {
      /* @Trace: SWS_StbM_00398 */
      /* polyspace +3 MISRA-C3:D4.14 [Not a defect:Low] "This pointer is manual checked and has no impact" */
      STBM_GET_USERDATA(userData, &(lpTimeBaseValue->ddUserData));
      /* @Trace: SWS_StbM_00173 */
      STBM_COPY_STATUS(timeStamp, &(lpTimeBaseValue->ddLocalTime));
      /* Convert StbM_TimeStampType to StbM_TimeStampExtendedType */
      STBM_COPY_TIMESTAMP(timeStamp, &lddTimeStamp);         
      /* @Trace: SWS_StbM_00436 */ 
      #if (STD_ON == STBM_TIME_CORRECTION_SUPPORT)
      (void)StbM_Internal_SlaveTimeCorrection(lusConfigPtr, lddTimeVlt);
      #endif /* STD_ON == STBM_TIME_CORRECTION_SUPPORT */ 
    }
    else
    {
      /* Do nothing */ 
    }
  }
  
  return (lddReturnVal);
} /* End of StbM_GetCurrentTime(void) */

#define STBM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : StbM_GetCurrentTimeExtended                         **
**                                                                            **
** Service ID           : 0x08                                                **
**                                                                            **
** Description          : Returns a time value (Local Time Base derived from  **
**                           Global Time Base) in extended format.            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : timeBaseId : StbM_SynchronizedTimeBaseType          **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : timeStamp : StbM_TimeStampExtendedType              **
**                        userData : StbM_UserDataType                        **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : STD_ON == STBM_GET_CURRENT_TIME_EXTENDED            **
**                                                                            **
** Remarks              : Global Variable(s)  : StbM_GblInitStatus            **
**                        Function(s) invoked : Det_ReportError               **
**                             StbM_Internal_SlaveTimeCorrection              **
*******************************************************************************/
/* @Trace: RS_TS_00005, RS_TS_00006, RS_TS_00013, RS_TS_00014, RS_TS_00015 */
#if (STD_ON == STBM_GET_CURRENT_TIME_EXTENDED)

#define STBM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, STBM_CODE) StbM_GetCurrentTimeExtended(
  VAR(StbM_SynchronizedTimeBaseType, AUTOMATIC)timeBaseId,
  P2VAR(StbM_TimeStampExtendedType, AUTOMATIC, STBM_APPL_DATA)timeStamp,
  P2VAR(StbM_UserDataType, AUTOMATIC, STBM_APPL_DATA)userData)
{
  /* @Trace: SWS_StbM_00197 */  
  Std_ReturnType lddReturnVal;

  P2VAR(StbM_TimeBaseValueType, AUTOMATIC, STBM_APPL_DATA)lpTimeBaseValue;
  VAR(uint16, AUTOMATIC)lusConfigPtr;
  VAR(StbM_TimeStampType, AUTOMATIC)lddTimeStamp;
  VAR(StbM_VirtualLocalTimeType, AUTOMATIC)lddTimeVlt;
  
  STBM_INIT_VLTIME(&lddTimeVlt);
  
  lddReturnVal = E_OK;
  /* @Trace: StbM_SUD_API_091 */  
  #if (STD_ON == STBM_DEV_ERROR_DETECT)
  lddReturnVal = StbM_CheckInitStatus(lddReturnVal, STBM_GETCURRENTTIMEEXTENDED_SID);
  /* @Trace: SWS_StbM_00201 */
  lddReturnVal = StbM_CheckTimeBaseID(lddReturnVal, timeBaseId, STBM_GETCURRENTTIMEEXTENDED_SID);
  /* @Trace: SWS_StbM_00202 */ 
  lddReturnVal = StbM_CheckInvalid2Pointer(lddReturnVal, timeStamp, userData, STBM_GETCURRENTTIMEEXTENDED_SID);

  if(E_NOT_OK == lddReturnVal)
  {
    /* Do nothing */                          
  }                           
  else  
  #endif /* STD_ON == STBM_DEV_ERROR_DETECT */
  /* @Trace: StbM_SUD_API_092 */
  {
    /* Get address of TimeBaseConfig */  
    STBM_GET_ADDRESS_TIME_BASES_CONFIGURED(timeBaseId,lusConfigPtr);
    lpTimeBaseValue = &StbM_GaaTimeBaseValue[lusConfigPtr];
    /* @Trace: SWS_StbM_00434*/
    /* @Trace: SWS_StbM_00177 */
    lddReturnVal = StbM_Internal_GetCurrentTime(
                            lusConfigPtr, &lddTimeStamp, &lddTimeVlt, NULL_PTR);
    if(E_OK == lddReturnVal)
    {
      /* @Trace: SWS_StbM_00398 */
      /* polyspace +1 MISRA-C3:D4.14 [Not a defect:Low] "This pointer is manual checked and has no impact" */
      STBM_GET_USERDATA(userData, &(lpTimeBaseValue->ddUserData));
      /* @Trace: SWS_StbM_00173 */
      /* polyspace +1 MISRA-C3:D4.14 [Not a defect:Low] "This pointer is manual checked and has no impact" */
      STBM_COPY_STATUS(timeStamp, &(lpTimeBaseValue->ddLocalTime));
      /* Convert StbM_TimeStampType to StbM_TimeStampExtendedType */
      timeStamp->nanoseconds = lddTimeStamp.nanoseconds;
      timeStamp->seconds = (uint64)(lddTimeStamp.seconds) | (((uint64)
                       (lddTimeStamp.secondsHi))<<STBM_THIRTY_TWO);     
      /* @Trace: SWS_StbM_00436 */ 
      #if (STD_ON == STBM_TIME_CORRECTION_SUPPORT)
      (void) StbM_Internal_SlaveTimeCorrection(lusConfigPtr, lddTimeVlt); /*polyspace MISRA-C:17.7 [Not a defect:Low] "This function isn't required to use return value of sub-function."*/
      #endif /* STD_ON == STBM_TIME_CORRECTION_SUPPORT */ 
    }
    else
    {
      /* Do nothing */ 
    } 
  }
  
  return (lddReturnVal);
} /* End of StbM_GetCurrentTimeExtended(void) */

#define STBM_STOP_SEC_CODE
#include "MemMap.h"
 
#endif /* STD_ON == STBM_GET_CURRENT_TIME_EXTENDED */

/*******************************************************************************
** Function Name        : StbM_GetCurrentVirtualLocalTime                     **
**                                                                            **
** Service ID           : 0x1e                                                **
**                                                                            **
** Description          : Returns the Virtual Local Time of the referenced    **
**                           Time Base.                                       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : timeBaseId : StbM_SynchronizedTimeBaseType          **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : localTimePtr : StbM_VirtualLocalTimeType            **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : StbM_GblInitStatus            **
**                        Function(s) invoked : Det_ReportError               **
**                             StbM_Internal_GetVirtualLocalTime              **
*******************************************************************************/
/*@Trace: RS_TS_00006, RS_TS_00007, RS_TS_00033 */
#define STBM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, STBM_CODE) StbM_GetCurrentVirtualLocalTime(
  VAR(StbM_SynchronizedTimeBaseType, AUTOMATIC)timeBaseId,
  P2VAR(StbM_VirtualLocalTimeType, AUTOMATIC, STBM_APPL_DATA)localTimePtr)
{
  /* @Trace: SWS_StbM_91006 */ 
  Std_ReturnType lddReturnVal;
  VAR(uint16, AUTOMATIC)lusConfigPtr;
  
  lddReturnVal = E_OK;
  /* @Trace: StbM_SUD_API_161 */  
  #if (STD_ON == STBM_DEV_ERROR_DETECT)
  STBM_CHECK_INIT(lddReturnVal,STBM_GETCURRENTVIRTUALLOCALTIME_SID);
  /* @Trace: SWS_StbM_00444 */   
  STBM_CHECK_TIME_BASE_ID(lddReturnVal,timeBaseId,STBM_GETCURRENTVIRTUALLOCALTIME_SID);
  /* @Trace: SWS_StbM_00445 */   
  STBM_CHECK_INVALID_POINTER(lddReturnVal,localTimePtr,STBM_GETCURRENTVIRTUALLOCALTIME_SID);
  
  if(E_NOT_OK == lddReturnVal)
  {
    /* Do nothing */                          
  }                           
  else  
  #endif /* STD_ON == STBM_DEV_ERROR_DETECT */
  /* @Trace: StbM_SUD_API_162 */ 
  {
    /* Get address of TimeBaseConfig */  
    STBM_GET_ADDRESS_TIME_BASES_CONFIGURED(timeBaseId,lusConfigPtr);
    /* @Trace: SWS_StbM_00437 */
    lddReturnVal =StbM_Internal_GetVirtualLocalTime(lusConfigPtr, localTimePtr);
  }
  
  return (lddReturnVal);
} /* End of StbM_GetCurrentVirtualLocalTime(void) */

#define STBM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : StbM_SetGlobalTime                                  **
**                                                                            **
** Service ID           : 0x0b                                                **
**                                                                            **
** Description          : Allows the Customers to set the new global time that**
**                          has to be valid for the system, which will be sent**
**                          to the busses.                                    **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : timeBaseId : StbM_SynchronizedTimeBaseType          **
**                        timeStamp : StbM_TimeStampType                      **
**                        userData : StbM_UserDataType                        **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : StbM_GblInitStatus            **
**                                  StbM_GaaTimeBaseValue                     **
**                                  StbM_GaaTimeTuple                         **
**                        Function(s) invoked : Det_ReportError               **
**                             StbM_Internal_GetVirtualLocalTime              **
**                             StbM_Internal_GetCurrentTime                   **
**                             StbM_Internal_IncreaseCounterOfTimeBase        **
**                             StbM_Internal_UpdateStatusOfTimeBase           **
*******************************************************************************/
/* @Trace: RS_TS_00009, RS_TS_00010, RS_TS_00013, RS_TS_00029 */
#define STBM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, STBM_CODE) StbM_SetGlobalTime(
  VAR(StbM_SynchronizedTimeBaseType, AUTOMATIC)timeBaseId,
  P2CONST(StbM_TimeStampType, AUTOMATIC, STBM_APPL_DATA)timeStamp,
  P2CONST(StbM_UserDataType, AUTOMATIC, STBM_APPL_DATA)userData)
{
  /* @Trace: SWS_StbM_00213 */
  Std_ReturnType lddReturnVal;

  P2CONST(StbM_TimeBaseConfigType, AUTOMATIC, STBM_APPL_DATA)lpTimeBaseConfig;
  P2VAR(StbM_TimeBaseValueType, AUTOMATIC, STBM_APPL_DATA)lpTimeBaseValue;
  P2VAR(StbM_TimeBaseValueType, AUTOMATIC, STBM_APPL_DATA)lpSyncTimeBaseValue;
  P2VAR(StbM_TimeTupleType, AUTOMATIC, STBM_APPL_DATA)lpTimeTuple;
  VAR(StbM_SynchronizedTimeBaseType, AUTOMATIC)syncTimeBaseId;
  VAR(uint16, AUTOMATIC)lusConfigPtr;
  VAR(uint16, AUTOMATIC)lusSyncConfigPtr;
  VAR(StbM_TimeStampType, AUTOMATIC)lddTimeStamp;
  VAR(StbM_TimeStampType, AUTOMATIC)lddSyncTimeStamp;
  VAR(StbM_TimeStampType, AUTOMATIC)lddRevTimeStamp;
  VAR(StbM_VirtualLocalTimeType, AUTOMATIC)lddVlt;
  
  lddReturnVal = E_OK;
  /* Init value */ 
  STBM_INIT_TIMESTAMP(&lddTimeStamp);
  
  STBM_INIT_TIMESTAMP(&lddSyncTimeStamp);
  
  STBM_INIT_TIMESTAMP(&lddRevTimeStamp);  
  
  /* @Trace: StbM_SUD_API_021 */ 
  #if (STD_ON == STBM_DEV_ERROR_DETECT)
  lddReturnVal = StbM_CheckInitStatus(lddReturnVal,STBM_SETGLOBALTIME_SID);
  /* @Trace: SWS_StbM_00214 */ 
  lddReturnVal = StbM_CheckTimeBaseID(lddReturnVal,timeBaseId,STBM_SETGLOBALTIME_SID);
  /* @Trace: SWS_StbM_00215 */ 
  lddReturnVal = StbM_CheckInvalid1Pointer(lddReturnVal,timeStamp,STBM_SETGLOBALTIME_SID);
  
  if(E_NOT_OK == lddReturnVal)
  {
    /* Do nothing */                          
  }                           
  else  
  #endif /* STD_ON == STBM_DEV_ERROR_DETECT */
  /* @Trace: StbM_SUD_API_022 */ 
  {
    /* Get address of TimeBaseConfig */  
    STBM_GET_ADDRESS_TIME_BASES_CONFIGURED(timeBaseId,lusConfigPtr);
    /* @Trace: StbM_SUD_API_023 */ 
    if((timeBaseId >= STBM_SIXTEEN) &&         
           (timeBaseId <= STBM_MAX_OFFSET_TIME_BASES_CONFIGURED))
    {
      /* @Trace: SWS_StbM_00304 */
      /* Get Config of Sync Time Base */
      /* polyspace +1 RTE:IDP [Not a defect:Low] "StbM_GaaTimeBaseConfig is verified and generated by Generator Tool" */
      lpTimeBaseConfig = &StbM_GaaTimeBaseConfig[lusConfigPtr];
      /* polyspace +1 RTE:IDP [Not a defect:Low] "StbM_GaaTimeBaseConfig is verified and generated by Generator Tool" */
      syncTimeBaseId = lpTimeBaseConfig->ddSyncTimeBaseId; /*polyspace MISRA-C:18.1 [Not a defect:Low] "StbM_GaaTimeBaseConfig is verified and generated by Generator Tool"*/ 
      STBM_GET_ADDRESS_SYNC_TIME_BASES_CONFIGURED(syncTimeBaseId,lusSyncConfigPtr);
      lpSyncTimeBaseValue = &StbM_GaaTimeBaseValue[lusSyncConfigPtr];
      /* @Trace: StbM_SUD_API_024 */ 
      if(((lpSyncTimeBaseValue->ddLocalTime.timeBaseStatus) & 
                        STBM_STATE_GLOBAL_TIME_BASE)!=STBM_ZERO)
      {
	/* polyspace +1 MISRA-C3:D4.14 [Not a defect:Low] "This pointer is manual checked and has no impact" */
        STBM_COPY_TIMESTAMP(&lddRevTimeStamp, timeStamp); /*polyspace MISRA-C:4.14 [Not a defect:Low] "This parameter is passed by Upper layer. Module only check that it isn't NULL"*/
        (void)StbM_Internal_GetCurrentTime(lusSyncConfigPtr, &lddSyncTimeStamp, NULL_PTR, NULL_PTR);
        lddReturnVal = StbM_Math_DiffOfTwoTimeStamp(
                        lddSyncTimeStamp,lddRevTimeStamp,&lddTimeStamp);
      }
      else
      {
        /* otherwise return E_NOT_OK */
        lddReturnVal = E_NOT_OK;
      }
    } 
    else
    {
      /* coppy Global timestamp into local  */
      /* polyspace +1 MISRA-C3:D4.14 [Not a defect:Low] "This pointer is manual checked and has no impact" */
      STBM_COPY_TIMESTAMP(&lddTimeStamp, timeStamp); /*polyspace MISRA-C:4.14 [Not a defect:Low] "This parameter is passed by Upper layer. Module only check that it isn't NULL"*/
    }
    /* check if don't have any error */
    if(E_OK == lddReturnVal)
    {
      /* Get VLT of Syn time Base */
      lddReturnVal = StbM_Internal_GetVirtualLocalTime(lusConfigPtr, &lddVlt);
      /* check if don't have any error */
      /* polyspace +1 MISRA-C3:14.3 [Not a defect:Low] "The value of lddReturnVal depends on the configurations" */
      if(E_OK == lddReturnVal)
      {
        /* Update main TimeTuple */
        /* @Trace: SWS_StbM_00342 */
        lpTimeTuple = &StbM_GaaTimeTuple[lusConfigPtr];
        STBM_COPY_VLTIME(&(lpTimeTuple->ddVirtualLocalTime),&lddVlt);
        STBM_COPY_TIMESTAMP(&(lpTimeTuple->ddLocalTime), &lddTimeStamp);
        /* Update main userData */
        lpTimeBaseValue = &StbM_GaaTimeBaseValue[lusConfigPtr];
	/* polyspace +1 MISRA-C3:D4.14 [Not a defect:Low] "This pointer is manual checked and has no impact" */
        STBM_SET_USERDATA(&(lpTimeBaseValue->ddUserData), userData); /*polyspace MISRA-C:4.14 [Not a defect:Low] "This parameter is passed by Upper layer. Module only check that it isn't NULL"*/
        /* @Trace: SWS_StbM_00350 */ 
        /* Update timeBaseUpdateCounter */
        StbM_Internal_IncreaseCounterOfTimeBase(lusConfigPtr);
        /* @Trace: SWS_StbM_00181 */ 
       (void) StbM_Internal_UpdateStatusOfTimeBase(lusConfigPtr,
                        STBM_STATE_GLOBAL_TIME_BASE, STBM_TRUE); /*polyspace MISRA-C:17.7 [Not a defect:Low] "This function isn't required to use return value of sub-function."*/
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
  
  return (lddReturnVal);
} /* End of StbM_SetGlobalTime(void) */

#define STBM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : StbM_UpdateGlobalTime                               **
**                                                                            **
** Service ID           : 0x10                                                **
**                                                                            **
** Description          : Allows the Customers to set the Global Time that    **
**                          will be sent to the buses.                        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : timeBaseId : StbM_SynchronizedTimeBaseType          **
**                        timeStamp : StbM_TimeStampType                      **
**                        userData : StbM_UserDataType                        **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : StbM_GblInitStatus            **
**                                  StbM_GaaTimeBaseValue                     **
**                                  StbM_GaaTimeTuple                         **
**                        Function(s) invoked : Det_ReportError               **
**                             StbM_Internal_GetVirtualLocalTime              **
**                             StbM_Internal_GetCurrentTime                   **
**                             StbM_Internal_UpdateStatusOfTimeBase           **
*******************************************************************************/
/* @Trace: RS_TS_00009, RS_TS_00010, RS_TS_00013 */
#define STBM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, STBM_CODE) StbM_UpdateGlobalTime(
  VAR(StbM_SynchronizedTimeBaseType, AUTOMATIC)timeBaseId,
  P2CONST(StbM_TimeStampType, AUTOMATIC, STBM_APPL_DATA)timeStamp,
  P2CONST(StbM_UserDataType, AUTOMATIC, STBM_APPL_DATA)userData)
{
  /* @Trace: SWS_StbM_00385 */ 
  Std_ReturnType lddReturnVal;

  P2CONST(StbM_TimeBaseConfigType, AUTOMATIC, STBM_APPL_DATA)lpTimeBaseConfig;
  P2VAR(StbM_TimeBaseValueType, AUTOMATIC, STBM_APPL_DATA)lpTimeBaseValue;
  P2VAR(StbM_TimeBaseValueType, AUTOMATIC, STBM_APPL_DATA)lpSyncTimeBaseValue;
  P2VAR(StbM_TimeTupleType, AUTOMATIC, STBM_APPL_DATA)lpTimeTuple;
  VAR(StbM_SynchronizedTimeBaseType, AUTOMATIC)syncTimeBaseId;
  VAR(uint16, AUTOMATIC)lusConfigPtr;
  VAR(uint16, AUTOMATIC)lusSyncConfigPtr;
  VAR(StbM_TimeStampType, AUTOMATIC)lddTimeStamp;
  VAR(StbM_TimeStampType, AUTOMATIC)lddSyncTimeStamp;
  VAR(StbM_TimeStampType, AUTOMATIC)lddRevTimeStamp;
  VAR(StbM_VirtualLocalTimeType, AUTOMATIC)lddVlt;
  
  lddReturnVal = E_OK;
 
  STBM_INIT_TIMESTAMP(&lddTimeStamp);
  STBM_INIT_TIMESTAMP(&lddRevTimeStamp);
  STBM_INIT_TIMESTAMP(&lddSyncTimeStamp);
  
  /* @Trace: StbM_SUD_API_071 */ 
  #if (STD_ON == STBM_DEV_ERROR_DETECT)
  lddReturnVal = StbM_CheckInitStatus(lddReturnVal,STBM_UPDATEGLOBALTIME_SID);
  /* @Trace: SWS_StbM_00340 */   
  lddReturnVal = StbM_CheckTimeBaseID(lddReturnVal,timeBaseId,STBM_UPDATEGLOBALTIME_SID);
  /* @Trace: SWS_StbM_00341 */ 
  lddReturnVal = StbM_CheckInvalid1Pointer(lddReturnVal, timeStamp, STBM_UPDATEGLOBALTIME_SID);
  if(E_NOT_OK == lddReturnVal)
  {
    /* Do nothing */                          
  }                           
  else  
  #endif /* STD_ON == STBM_DEV_ERROR_DETECT */
  /* @Trace: StbM_SUD_API_072 */ 
  {
    /* Get address of TimeBaseConfig */  
    STBM_GET_ADDRESS_TIME_BASES_CONFIGURED(timeBaseId,lusConfigPtr);
    /* @Trace: StbM_SUD_API_073 */ 
    if((timeBaseId >= STBM_SIXTEEN) &&         
           (timeBaseId <= STBM_MAX_OFFSET_TIME_BASES_CONFIGURED))
    {
      /* @Trace: SWS_StbM_00304 */
      /* Get Config of Sync Time Base */
      lpTimeBaseConfig = &StbM_GaaTimeBaseConfig[lusConfigPtr];
      /* polyspace +1 RTE:IDP [Not a defect:Low] "StbM_GaaTimeBaseConfig is verified and generated by Generator Tool" */
      syncTimeBaseId = lpTimeBaseConfig->ddSyncTimeBaseId;
      STBM_GET_ADDRESS_SYNC_TIME_BASES_CONFIGURED(syncTimeBaseId,lusSyncConfigPtr);
      
      lpSyncTimeBaseValue = &StbM_GaaTimeBaseValue[lusSyncConfigPtr];
      if(((lpSyncTimeBaseValue->ddLocalTime.timeBaseStatus) & 
                        STBM_STATE_GLOBAL_TIME_BASE)!=STBM_ZERO)
      {
	/* polyspace +1 MISRA-C3:D4.14 [Not a defect:Low] "This pointer is manual checked and has no impact" */
        STBM_COPY_TIMESTAMP(&lddRevTimeStamp, timeStamp); /*polyspace MISRA-C:4.14 [Not a defect:Low] "This parameter is passed by Upper layer. Module only check that it isn't NULL"*/
        (void) StbM_Internal_GetCurrentTime(lusSyncConfigPtr, &lddSyncTimeStamp, NULL_PTR, NULL_PTR); /*polyspace MISRA-C:17.7 [Not a defect:Low] "This function isn't required to use return value of sub-function."*/
        lddReturnVal = StbM_Math_DiffOfTwoTimeStamp(
                        lddRevTimeStamp,lddSyncTimeStamp,&lddTimeStamp);
      }
      /* @Trace: StbM_SUD_API_074 */ 
      else
      {
        /* otherwise return E_NOT_OK */
	/* polyspace +1 MISRA-C3:D4.14 [Not a defect:Low] "This pointer is manual checked and has no impact" */
        lddReturnVal = E_NOT_OK;
      }
    }
    else
    {
      /* coppy Global timestamp into local  */
      /* polyspace +1 MISRA-C3:D4.14 [Not a defect:Low] "This pointer is manual checked and has no impact" */
      STBM_COPY_TIMESTAMP(&lddTimeStamp, timeStamp); /*polyspace MISRA-C:4.14 [Not a defect:Low] "This parameter is passed by Upper layer. Module only check that it isn't NULL"*/
    }        
    /* check if don't have any error */
    if(E_OK == lddReturnVal)
    {
      /* Get VLT of Syn time Base */
      lddReturnVal = StbM_Internal_GetVirtualLocalTime(lusConfigPtr, &lddVlt);
      /* check if don't have any error */
      /* polyspace +1 MISRA-C3:14.3 [Not a defect:Low] "The value of lddReturnVal depends on the configurations" */
      if(E_OK == lddReturnVal)
      {
        /* Update main TimeTuple */
        /* @Trace: SWS_StbM_00342 */
        lpTimeTuple = &StbM_GaaTimeTuple[lusConfigPtr];
        STBM_COPY_VLTIME(&(lpTimeTuple->ddVirtualLocalTime),&lddVlt);
        STBM_COPY_TIMESTAMP(&(lpTimeTuple->ddLocalTime), &lddTimeStamp);
        /* Update main userData */
        lpTimeBaseValue = &StbM_GaaTimeBaseValue[lusConfigPtr];
	/* polyspace +1 MISRA-C3:D4.14 [Not a defect:Low] "This pointer is manual checked and has no impact" */
        STBM_SET_USERDATA(&(lpTimeBaseValue->ddUserData), userData); /*polyspace MISRA-C:4.14 [Not a defect:Low] "This parameter is passed by Upper layer. Module only check that it isn't NULL"*/
        /* Don't increase timeBaseUpdateCounter */
        /* @Trace: SWS_StbM_00181 */
        (void) StbM_Internal_UpdateStatusOfTimeBase(lusConfigPtr,
                        STBM_STATE_GLOBAL_TIME_BASE, STBM_TRUE); /*polyspace MISRA-C:17.7 [Not a defect:Low] "This function isn't required to use return value of sub-function."*/
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
  
  return (lddReturnVal);
} /* End of StbM_UpdateGlobalTime(void) */

#define STBM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : StbM_SetUserData                                    **
**                                                                            **
** Service ID           : 0x0c                                                **
**                                                                            **
** Description          : Allows the Customers to set the new User Data that  **
**                          has to be valid for the system, which will be sent**
**                          to the busses.                                    **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : timeBaseId : StbM_SynchronizedTimeBaseType          **
**                        userData : StbM_UserDataType                        **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : StbM_GblInitStatus            **
**                                  StbM_GaaTimeBaseValue                     **
**                        Function(s) invoked : Det_ReportError               **
*******************************************************************************/
/* @Trace: RS_TS_00015 */
#define STBM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, STBM_CODE) StbM_SetUserData(
  VAR(StbM_SynchronizedTimeBaseType, AUTOMATIC)timeBaseId,
  P2CONST(StbM_UserDataType, AUTOMATIC, STBM_APPL_DATA)userData)
{
  Std_ReturnType lddReturnVal;
  /* @Trace: SWS_StbM_00218 */
  P2VAR(StbM_TimeBaseValueType, AUTOMATIC, STBM_APPL_DATA)lpTimeBaseValue;
  VAR(uint16, AUTOMATIC)lusConfigPtr;
  
  lddReturnVal = E_OK;
  /* @Trace: StbM_SUD_API_051 */
  #if (STD_ON == STBM_DEV_ERROR_DETECT)
  lddReturnVal = StbM_CheckInitStatus(lddReturnVal,STBM_SETUSERDATA_SID);
  /* @Trace: SWS_StbM_00219 */ 
  lddReturnVal = StbM_CheckTimeBaseID(lddReturnVal,timeBaseId,STBM_SETUSERDATA_SID);
  /* @Trace: SWS_StbM_00220 */ 
  lddReturnVal = StbM_CheckInvalid1Pointer(lddReturnVal,userData,STBM_SETUSERDATA_SID);
  
  if(E_NOT_OK == lddReturnVal)
  {
    /* Do nothing */                          
  }                           
  else  
  #endif /* STD_ON == STBM_DEV_ERROR_DETECT */
  /* @Trace: StbM_SUD_API_052 */
  {
    /* Get address of TimeBaseConfig */  
    STBM_GET_ADDRESS_TIME_BASES_CONFIGURED(timeBaseId,lusConfigPtr);
    lpTimeBaseValue = &StbM_GaaTimeBaseValue[lusConfigPtr];
    /* polyspace +2 RTE:IDP [Not a defect:Low] "This pointer is manual checked and has no impact" */
    /* polyspace +1 MISRA-C3:D4.14 [Not a defect:Low] "This pointer is manual checked and has no impact" */
    STBM_COPY_USERDATA(&(lpTimeBaseValue->ddUserData), userData);
  }
  
  return (lddReturnVal);
} /* End of StbM_SetUserData(void) */

#define STBM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : StbM_SetOffset                                      **
**                                                                            **
** Service ID           : 0x0d                                                **
**                                                                            **
** Description          : Allows the Customers and the Timesync Modules to set**
**                          the Offset Time and the User Data.                **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : timeBaseId : StbM_SynchronizedTimeBaseType          **
**                        timeStamp : StbM_TimeStampType                      **
**                        userData : StbM_UserDataType                        **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : StbM_GblInitStatus            **
**                                  StbM_GaaTimeBaseValue                     **
**                                  StbM_GaaTimeTuple                         **
**                        Function(s) invoked : Det_ReportError               **
**                             StbM_Internal_GetVirtualLocalTime              **
**                             StbM_Internal_IncreaseCounterOfTimeBase        **
**                             StbM_Internal_UpdateStatusOfTimeBase           **
*******************************************************************************/
/* @Trace: RS_TS_00007, RS_TS_00009, RS_TS_00012, RS_TS_00013, RS_TS_00015,
 RS_TS_00029 */
#define STBM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, STBM_CODE) StbM_SetOffset(
  VAR(StbM_SynchronizedTimeBaseType, AUTOMATIC)timeBaseId,
  P2CONST(StbM_TimeStampType, AUTOMATIC, STBM_APPL_DATA)timeStamp,
  P2CONST(StbM_UserDataType, AUTOMATIC, STBM_APPL_DATA)userData)
{
  /* @Trace: SWS_StbM_00223 */ 
  Std_ReturnType lddReturnVal;

  P2VAR(StbM_TimeBaseValueType, AUTOMATIC, STBM_APPL_DATA)lpTimeBaseValue;
  P2VAR(StbM_TimeTupleType, AUTOMATIC, STBM_APPL_DATA)lpTimeTuple;
  VAR(uint16, AUTOMATIC)lusConfigPtr;
  VAR(StbM_VirtualLocalTimeType, AUTOMATIC)lddVlt;
  
  lddReturnVal = E_OK;
  /* @Trace: StbM_SUD_API_031 */ 
  #if (STD_ON == STBM_DEV_ERROR_DETECT)
  lddReturnVal = StbM_CheckInitStatus(lddReturnVal,STBM_SETOFFSET_SID);
  /* @Trace: SWS_StbM_00191 */
  /* @Trace: SWS_StbM_00224 */ 
  lddReturnVal = StbM_CheckTimeBaseID(lddReturnVal,timeBaseId,STBM_SETOFFSET_SID);
  /* @Trace: SWS_StbM_00225 */  
  lddReturnVal = StbM_CheckInvalid2Pointer(lddReturnVal, timeStamp, userData, STBM_SETOFFSET_SID);
  
  if(E_NOT_OK == lddReturnVal)
  {
    /* Do nothing */                          
  }                           
  else  
  #endif /* STD_ON == STBM_DEV_ERROR_DETECT */
  /* @Trace: StbM_SUD_API_032 */
  {
    /* Get address of TimeBaseConfig */  
    STBM_GET_ADDRESS_OFFSET_TIME_BASES_CONFIGURED(timeBaseId,lusConfigPtr);
    lpTimeBaseValue = &StbM_GaaTimeBaseValue[lusConfigPtr];
    lpTimeTuple = &StbM_GaaTimeTuple[lusConfigPtr];   
    /* Get VLT of Syn time Base */
    lddReturnVal = StbM_Internal_GetVirtualLocalTime(lusConfigPtr, &lddVlt);
    /* Update timebase */
    /* polyspace +2 MISRA-C3:D4.14 [Not a defect:Low] "This pointer is manual checked and has no impact" */
    STBM_COPY_TIMESTAMP(&(lpTimeBaseValue->ddLocalTime), timeStamp);
    STBM_COPY_USERDATA(&(lpTimeBaseValue->ddUserData), userData);
    /* Update main TimeTuple */
    /* @Trace: SWS_StbM_00190 */
    STBM_COPY_TIMESTAMP(&(lpTimeTuple->ddLocalTime), timeStamp);
    STBM_COPY_VLTIME(&(lpTimeTuple->ddVirtualLocalTime),&lddVlt);
    /* @Trace: SWS_StbM_00350 */ 
    /* Update timeBaseUpdateCounter */
    StbM_Internal_IncreaseCounterOfTimeBase(lusConfigPtr);
    /* @Trace: SWS_StbM_00181 */ 
    (void) StbM_Internal_UpdateStatusOfTimeBase(lusConfigPtr,
                        STBM_STATE_GLOBAL_TIME_BASE, STBM_TRUE); /*polyspace MISRA-C:17.7 [Not a defect:Low] "This function isn't required to use return value of sub-function."*/
  }
  
  return (lddReturnVal);
} /* End of StbM_SetOffset(void) */

#define STBM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : StbM_GetOffset                                      **
**                                                                            **
** Service ID           : 0x0e                                                **
**                                                                            **
** Description          : Allows the Customers and the Timesync Modules to get**
**                          the Offset Time and the User Data.                **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : timeBaseId : StbM_SynchronizedTimeBaseType          **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : timeStamp : StbM_TimeStampType                      **
**                        userData : StbM_UserDataType                        **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : StbM_GblInitStatus            **
**                                  StbM_GaaTimeBaseValue                     **
**                        Function(s) invoked : Det_ReportError               **
**                             StbM_Internal_GetVirtualLocalTime              **
**                             StbM_Math_TimeStampInterpolate                 **
*******************************************************************************/
/* @Trace: RS_TS_00012, RS_TS_00013, RS_TS_00014, RS_TS_00029, RS_TS_00031 */
#define STBM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, STBM_CODE) StbM_GetOffset(
  VAR(StbM_SynchronizedTimeBaseType, AUTOMATIC)timeBaseId,
  P2VAR(StbM_TimeStampType, AUTOMATIC, STBM_APPL_DATA)timeStamp,
  P2VAR(StbM_UserDataType, AUTOMATIC, STBM_APPL_DATA)userData)
{
  /* @Trace: SWS_StbM_00228 */ 
  Std_ReturnType lddReturnVal;

  P2VAR(StbM_TimeBaseValueType, AUTOMATIC, STBM_APPL_DATA)lpTimeBaseValue;
  VAR(uint16, AUTOMATIC)lusConfigPtr;
  VAR(StbM_VirtualLocalTimeType, AUTOMATIC)lddVlt;
  VAR(StbM_TimeStampType, AUTOMATIC)lddTimeStamp;
  
  lddReturnVal = E_OK; 
  /* @Trace: StbM_SUD_API_191 */
  #if (STD_ON == STBM_DEV_ERROR_DETECT)
  lddReturnVal = StbM_CheckInitStatus(lddReturnVal, STBM_GETOFFSET_SID);
  /* @Trace: SWS_StbM_00191 */
  /* @Trace: SWS_StbM_00229 */ 
  lddReturnVal = StbM_CheckSyncOffsetTimeBaseID(lddReturnVal, timeBaseId, STBM_GETOFFSET_SID);
  /* @Trace: SWS_StbM_00230 */   
  lddReturnVal = StbM_CheckInvalid2Pointer(lddReturnVal, timeStamp, userData, STBM_GETOFFSET_SID);
  
  if(E_NOT_OK == lddReturnVal)
  {
    /* Do nothing */                          
  }                           
  else  
  #endif /* STD_ON == STBM_DEV_ERROR_DETECT */
  /* @Trace: StbM_SUD_API_192 */
  { 
    /* Get address of TimeBaseConfig */  
    STBM_GET_ADDRESS_OFFSET_TIME_BASES_CONFIGURED(timeBaseId,lusConfigPtr);
    lpTimeBaseValue = &StbM_GaaTimeBaseValue[lusConfigPtr];
    /* @Trace: SWS_StbM_00192 */  
    /* Get VLT of Syn time Base */
    lddReturnVal = StbM_Internal_GetVirtualLocalTime(lusConfigPtr, &lddVlt);
    (void) StbM_Math_TimeStampInterpolate(lpTimeBaseValue->ddRate,
              StbM_GaaTimeTuple[lusConfigPtr], lddVlt,&lddTimeStamp); /*polyspace MISRA-C:17.7 [Not a defect:Low] "This function isn't required to use return value of sub-function."*/  
    /* polyspace +2 MISRA-C3:D4.14 [Not a defect:Low] "This pointer is manual checked and has no impact" */
    STBM_COPY_TIMESTAMP(timeStamp, &(lddTimeStamp));
    STBM_GET_USERDATA(userData, &(lpTimeBaseValue->ddUserData));
  }
  
  return (lddReturnVal);
} /* End of StbM_GetOffset(void) */

#define STBM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : StbM_BusGetCurrentTime                              **
**                                                                            **
** Service ID           : 0x07                                                **
**                                                                            **
** Description          : Returns the current Time Tuple, status and User Data**
**                          of the Time Base.                                 **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : timeBaseId : StbM_SynchronizedTimeBaseType          **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : globalTimePtr : StbM_TimeStampType                  **
**                        localTimePtr : StbM_VirtualLocalTimeType            **
**                        userData : StbM_UserDataType                        **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : StbM_GblInitStatus            **
**                                  StbM_GaaTimeBaseValue                     **
**                        Function(s) invoked : Det_ReportError               **
**                             StbM_Internal_GetCurrentTime                   **
**                             StbM_Internal_SlaveTimeCorrection              **
*******************************************************************************/
/* @Trace: RS_TS_00004, RS_TS_00005, RS_TS_00006,  RS_TS_00014, RS_TS_00018,
RS_TS_00029, RS_TS_00031 */
#define STBM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, STBM_CODE) StbM_BusGetCurrentTime(
  VAR(StbM_SynchronizedTimeBaseType, AUTOMATIC)timeBaseId,
  P2VAR(StbM_TimeStampType, AUTOMATIC, STBM_APPL_DATA)globalTimePtr,
  P2VAR(StbM_VirtualLocalTimeType, AUTOMATIC, STBM_APPL_DATA)localTimePtr,
  P2VAR(StbM_UserDataType, AUTOMATIC, STBM_APPL_DATA)userData)
{
  /* @Trace: SWS_StbM_91005 */
  Std_ReturnType lddReturnVal;

  P2VAR(StbM_TimeBaseValueType, AUTOMATIC, STBM_APPL_DATA)lpTimeBaseValue;
  VAR(uint16, AUTOMATIC)lusConfigPtr;
  VAR(StbM_TimeStampType, AUTOMATIC)lddtimeStamp;
  VAR(StbM_VirtualLocalTimeType, AUTOMATIC)lddtimeVlt;
  
  lddReturnVal = E_OK;
  
  STBM_INIT_VLTIME(&lddtimeVlt);
  /* @Trace: StbM_SUD_API_171 */
  #if (STD_ON == STBM_DEV_ERROR_DETECT)
  lddReturnVal = StbM_CheckInitStatus(lddReturnVal, STBM_BUSGETCURRENTTIME_SID);
  /* @Trace: SWS_StbM_00446 */
  lddReturnVal = StbM_CheckSyncOffsetTimeBaseID(lddReturnVal,timeBaseId,STBM_BUSGETCURRENTTIME_SID);
  /* @Trace: SWS_StbM_00447 */ 
  lddReturnVal = StbM_CheckInvalid3Pointer(lddReturnVal, globalTimePtr, userData,
  		localTimePtr, STBM_BUSGETCURRENTTIME_SID);
  if(E_NOT_OK == lddReturnVal)
  {
    /* Do nothing */
  }
  else  
  #endif /* STD_ON == STBM_DEV_ERROR_DETECT */
  /* @Trace: StbM_SUD_API_172 */
  {
    /* Get address of TimeBaseConfig */  
    STBM_GET_ADDRESS_SYNC_OFFSET_TIME_BASES_CONFIGURED(timeBaseId,lusConfigPtr);
    
    lddReturnVal = StbM_Internal_GetCurrentTime(lusConfigPtr, &lddtimeStamp, &lddtimeVlt, NULL_PTR);
    /* @Trace: SWS_StbM_00434*/
    if(E_OK == lddReturnVal)
    { 
      /* Set output */
      /* polyspace +2 MISRA-C3:D4.14 [Not a defect:Low] "This pointer is manual checked and has no impact" */
      STBM_COPY_TIMESTAMP(globalTimePtr, &lddtimeStamp);
      STBM_COPY_VLTIME(localTimePtr,&lddtimeVlt);
      /* @Trace: SWS_StbM_00355 */
      /* @Trace: SWS_StbM_00436 */  
      #if (STD_ON == STBM_TIME_CORRECTION_SUPPORT) 
      (void)StbM_Internal_SlaveTimeCorrection(lusConfigPtr, lddtimeVlt);
      #endif /* STD_ON == STBM_TIME_CORRECTION_SUPPORT */ 
      lpTimeBaseValue = &StbM_GaaTimeBaseValue[lusConfigPtr];
      /* @Trace: SWS_StbM_00173 */
      STBM_COPY_STATUS(globalTimePtr, &(lpTimeBaseValue->ddLocalTime));
      /* @Trace: SWS_StbM_00435 */
      /* polyspace +1 MISRA-C3:D4.14 [Not a defect:Low] "This pointer is manual checked and has no impact" */
      STBM_GET_USERDATA(userData, &(lpTimeBaseValue->ddUserData));
    }
    else
    {
      /* Do nothing */                          
    } 
  }
  
  return (lddReturnVal);
} /* End of StbM_BusGetCurrentTime(void) */

#define STBM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : StbM_BusSetGlobalTime                               **
**                                                                            **
** Service ID           : 0x0f                                                **
**                                                                            **
** Description          : Allows the Time Base Provider Modules to forward a  **
**                          new Global Time tuple (i.e., the Received Time    ** 
**                          Tuple) to the StbM.                               **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : timeBaseId : StbM_SynchronizedTimeBaseType          **
**                        globalTimePtr : StbM_TimeStampType                  **
**                        userData : StbM_UserDataType                        **
**                        measureDataPtr : StbM_MeasurementType               **
**                        localTimePtr : StbM_VirtualLocalTimeType            **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : StbM_GblInitStatus            **
**                                  StbM_GaaTimeBaseValue                     **
**                                  StbM_GaaTimeTuple                         **
**                        Function(s) invoked : Det_ReportError               **
**                             StbM_Internal_GetVirtualLocalTime              **
**                             StbM_Internal_GetCurrentTime                   **
**                             StbM_Internal_CheckTimeLeap                    **
**                             StbM_Internal_SlaveRateCorrection              **
**                             StbM_Internal_IncreaseCounterOfTimeBase        **
**                             StbM_Internal_UpdateStatusOfTimeBase           **
**                             StbM_Internal_WriteTimeRecordTable             **
*******************************************************************************/
/* @Trace: RS_TS_00007, RS_TS_00008, RS_TS_00009, RS_TS_00018, RS_TS_00025,
RS_TS_00030, RS_TS_00034 */
#define STBM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, STBM_CODE) StbM_BusSetGlobalTime(
  VAR(StbM_SynchronizedTimeBaseType, AUTOMATIC)timeBaseId,
  P2CONST(StbM_TimeStampType, AUTOMATIC, STBM_APPL_DATA)globalTimePtr,
  P2CONST(StbM_UserDataType, AUTOMATIC, STBM_APPL_DATA)userData,
  P2CONST(StbM_MeasurementType, AUTOMATIC, STBM_APPL_DATA)measureDataPtr,
  P2CONST(StbM_VirtualLocalTimeType, AUTOMATIC, STBM_APPL_DATA)localTimePtr)
{
  /* @Trace: SWS_StbM_00233 */
  Std_ReturnType lddReturnVal;
  #if (STD_ON == STBM_TIME_CORRECTION_SUPPORT) 
  Std_ReturnType lddCheckCorrection;
  #endif /* STD_ON == STBM_TIME_CORRECTION_SUPPORT */
  
  P2VAR(StbM_TimeBaseValueType, AUTOMATIC, STBM_APPL_DATA)lpTimeBaseValue;
  P2VAR(StbM_TimeTupleType, AUTOMATIC, STBM_APPL_DATA)lpTimeTuple;
  VAR(uint16, AUTOMATIC)lusConfigPtr;
  VAR(StbM_TimeStampType, AUTOMATIC)lddTimeStamp;
  VAR(StbM_TimeStampType, AUTOMATIC)lddGlobalTimeStamp;
  VAR(StbM_VirtualLocalTimeType, AUTOMATIC)lddVlt;
  VAR(StbM_VirtualLocalTimeType, AUTOMATIC)lddVltSync;
  
  lddReturnVal = E_OK;
  
  STBM_INIT_TIMESTAMP(&lddTimeStamp);
  STBM_INIT_TIMESTAMP(&lddGlobalTimeStamp);
  STBM_INIT_VLTIME(&lddVlt);
  
  #if (STD_ON == STBM_TIME_CORRECTION_SUPPORT) 
  lddCheckCorrection = E_NOT_OK;
  #endif /* STD_ON == STBM_TIME_CORRECTION_SUPPORT */
 
  /* @Trace: StbM_SUD_API_181 */
  #if (STD_ON == STBM_DEV_ERROR_DETECT)
  STBM_CHECK_INIT(lddReturnVal, STBM_BUSSETGLOBALTIME_SID);
  /* @Trace: SWS_StbM_00234 */ 
  lddReturnVal = StbM_CheckSyncOffsetTimeBaseID(lddReturnVal, timeBaseId, STBM_BUSSETGLOBALTIME_SID);
  /* @Trace: SWS_StbM_00235 */
  lddReturnVal = StbM_CheckInvalid3Pointer(lddReturnVal, globalTimePtr, measureDataPtr, localTimePtr, STBM_BUSSETGLOBALTIME_SID);

  if(E_NOT_OK == lddReturnVal)
  {
    /* Do nothing */                          
  }                           
  else
  #endif /* STD_ON == STBM_DEV_ERROR_DETECT */
  /* @Trace: StbM_SUD_API_182 */
  { 
    /* Get address of TimeBaseConfig */  
    STBM_GET_ADDRESS_SYNC_OFFSET_TIME_BASES_CONFIGURED(timeBaseId,lusConfigPtr);
    lpTimeBaseValue = &StbM_GaaTimeBaseValue[lusConfigPtr];
	/* polyspace +3 CERT-C:EXP33-C [To fix:Low] "<Bus>TSyn module should control data Initialization before setting global time to StbM" */
	/* polyspace +2 MISRA-C3:9.1 [To fix:Low] "<Bus>TSyn module should control data Initialization before setting global time to StbM" */
    /* polyspace +2 DEFECT:NON_INIT_VAR MISRA-C3:D4.14 [Not a defect:Low] "This pointer is manual checked and has no impact" */
    STBM_COPY_TIMESTAMP(&lddGlobalTimeStamp, globalTimePtr);    
    STBM_COPY_VLTIME(&lddVltSync, localTimePtr);      
    /* @Trace: SWS_StbM_00182 */
    /* @Trace: SWS_StbM_00305 */  
    /* @Trace: StbM_SUD_API_183 */
    /* polyspace +1 RTE:IDP [Not a defect:Low] "StbM_GaaTimeBaseConfig is verified and generated by Generator Tool" */
    if(STBM_ZERO == (lpTimeBaseValue->ucFirstSynch))
    {
      lpTimeBaseValue->ucFirstSynch = STBM_ONE;  
      /* for first call, only get vlt  */
      /* @Trace: SWS_StbM_00359 */
      lddReturnVal = StbM_Internal_GetVirtualLocalTime(lusConfigPtr, &lddVlt);  
      /* for first call, set local time as global time  */
      STBM_COPY_TIMESTAMP(&lddTimeStamp, globalTimePtr);      
    }
    else
    {
      if(STBM_ONE == (lpTimeBaseValue->ucFirstSynch))
      {
        lpTimeBaseValue->ucFirstSynch = STBM_TWO;
      }
      else
      {
        /* Do nothing */ 
      }
      /* Get Current time of Syn time Base */
      /* @Trace: SWS_StbM_00438 */
      /* @Trace: SWS_StbM_00439 */     
      (void)StbM_Internal_GetCurrentTime(lusConfigPtr,
                                &lddTimeStamp, &lddVlt, &lddVltSync);
      /* check TIMELEAP_FUTURE/TIMELEAP_PAST bit */   
      lddReturnVal = StbM_Internal_CheckTimeLeap(lusConfigPtr,  
                                lddTimeStamp, lddGlobalTimeStamp);
      #if (STD_ON == STBM_TIME_CORRECTION_SUPPORT)
      /* Time correction only run at two time */
      if(E_OK == lddReturnVal)        
      {          
        /* @Trace: SWS_StbM_00355 */
        lddCheckCorrection = StbM_Internal_SlaveTimeCorrection(  
                    lusConfigPtr, lddVlt);
      }
      else
      {
        /* Do nothing */
      }
      #endif /* STD_ON == STBM_TIME_CORRECTION_SUPPORT */
    }
    /* Check don't have any error */
    /* @Trace: SWS_StbM_00374 */
    /* @Trace: SWS_StbM_00375 */
    /* @Trace: SWS_StbM_00376 */
    if(E_OK == lddReturnVal)
    {
      /* Time Correction feature */
      #if (STD_ON == STBM_TIME_CORRECTION_SUPPORT) 
      (void) StbM_Internal_SlaveRateCorrection(lusConfigPtr,
                                lddGlobalTimeStamp, lddVltSync); /*polyspace MISRA-C:17.7 [Not a defect:Low] "This function isn't required to use return value of sub-function."*/
      if(E_OK == lddCheckCorrection)
      {
        /* Do nothing */
      }
      else
      #endif /* STD_ON == STBM_TIME_CORRECTION_SUPPORT */
      /* Otherwise the Main Time Tuple is overwritten by the Received Time Tuple. */ 
      {
        /* Update main TimeTuple */
        /* @Trace: SWS_StbM_00179 */
        /* @Trace: SWS_StbM_00393 */
      lpTimeTuple = &StbM_GaaTimeTuple[lusConfigPtr];
        STBM_COPY_VLTIME(&(lpTimeTuple->ddVirtualLocalTime),localTimePtr);
        STBM_COPY_TIMESTAMP(&(lpTimeTuple->ddLocalTime), globalTimePtr);
      }
      StbM_IntprocessOfBusSetGlobalTime(globalTimePtr, lusConfigPtr, userData);
      /* Time Base Record feature */
      /* @Trace: SWS_StbM_00307 */
      #if(STD_ON == STBM_TIME_RECORDING_SUPPORT)
      /* @Trace: SWS_StbM_00428 */
      /* @Trace: SWS_StbM_00312 */
      StbM_Internal_WriteTimeRecordTable(lusConfigPtr,
          lddGlobalTimeStamp, lpTimeBaseValue->ddLocalTime.timeBaseStatus, 
          #if(STBM_ZERO < STBM_NUMBER_SYNC_TIME_RECORD_TABLE_CONFIGURED)
	  /* polyspace +1 MISRA-C3:D4.14 [Not a defect:Low] "This pointer is manual checked and has no impact" */
          lddTimeStamp, lddVltSync, (*measureDataPtr)
          #endif /* STBM_ZERO < STBM_NUMBER_SYNC_TIME_RECORD_TABLE_CONFIGURED */
          );
      #endif  /* STD_ON == STBM_TIME_RECORDING_SUPPORT */  
    }
    /* @Trace: StbM_SUD_API_184 */
    else
    {
      /* Do nothing */                          
    }
  }
  
  return (lddReturnVal);
} /* End of StbM_BusSetGlobalTime(void) */

#define STBM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : StbM_GetRateDeviation                               **
**                                                                            **
** Service ID           : 0x11                                                **
**                                                                            **
** Description          : Returns value of the current rate deviation of a    **
**                          Time Base.                                        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : timeBaseId : StbM_SynchronizedTimeBaseType          **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : rateDeviation : StbM_RateDeviationType              **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : StbM_GblInitStatus            **
**                        Function(s) invoked : Det_ReportError               **
**                             StbM_Internal_CalRateDeviation                 **
*******************************************************************************/
/*@Trace: RS_TS_00018 */
#define STBM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, STBM_CODE) StbM_GetRateDeviation(
  VAR(StbM_SynchronizedTimeBaseType, AUTOMATIC)timeBaseId,
  P2VAR(StbM_RateDeviationType, AUTOMATIC, STBM_APPL_DATA)rateDeviation)
{
  /* @Trace: SWS_StbM_00378 */
  Std_ReturnType lddReturnVal;
  VAR(uint16, AUTOMATIC)lusConfigPtr;
  
  lddReturnVal = E_OK;
  /* @Trace: StbM_SUD_API_111 */
  #if (STD_ON == STBM_DEV_ERROR_DETECT)
  STBM_CHECK_INIT(lddReturnVal,STBM_GETRATEDEVIATION_SID);
  /* @Trace: SWS_StbM_00379 */ 
  STBM_CHECK_TIME_BASE_ID(lddReturnVal,timeBaseId,STBM_GETRATEDEVIATION_SID);
  /* @Trace: SWS_StbM_00380 */ 
  STBM_CHECK_INVALID_POINTER(lddReturnVal,rateDeviation,STBM_GETRATEDEVIATION_SID);
  
  if(E_NOT_OK == lddReturnVal)
  {
    /* Do nothing */                          
  }                           
  else  
  #endif /* STD_ON == STBM_DEV_ERROR_DETECT */
  /* @Trace: StbM_SUD_API_112 */
  {
    /* @Trace: SWS_StbM_00422 */
    /* @Trace: SWS_StbM_00397 */
    /* @Trace: SWS_StbM_00412 */
    STBM_GET_ADDRESS_TIME_BASES_CONFIGURED(timeBaseId,lusConfigPtr);
    lddReturnVal = StbM_Internal_CalRateDeviation(lusConfigPtr, rateDeviation);
  } 
  
  return (lddReturnVal);
} /* End of StbM_GetRateDeviation(void) */

#define STBM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : StbM_SetRateCorrection                              **
**                                                                            **
** Service ID           : 0x12                                                **
**                                                                            **
** Description          : Allows to set the rate of a Synchronized Time Base  **
**                         (being either a Pure Local Time Base or not).      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : timeBaseId : StbM_SynchronizedTimeBaseType          **
**                        rateDeviation : StbM_RateDeviationType              **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : StbM_GblInitStatus            **
**                        Function(s) invoked : Det_ReportError               **
**                             StbM_Internal_SetRateDeviation                 **
*******************************************************************************/
/*@Trace: RS_TS_00018 */
#define STBM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, STBM_CODE) StbM_SetRateCorrection(
  VAR(StbM_SynchronizedTimeBaseType, AUTOMATIC)timeBaseId,
  VAR(StbM_RateDeviationType, AUTOMATIC)rateDeviation)
{
  /* @Trace: SWS_StbM_00390 */ 
  Std_ReturnType lddReturnVal;
  VAR(uint16, AUTOMATIC)lusConfigPtr;
  
  lddReturnVal = E_OK;
  /* @Trace: StbM_SUD_API_041 */ 
  #if (STD_ON == STBM_DEV_ERROR_DETECT)
  STBM_CHECK_INIT(lddReturnVal,STBM_SETRATECORRECTION_SID);
  /* @Trace: SWS_StbM_00391 */  
  STBM_CHECK_TIME_BASE_ID(lddReturnVal,timeBaseId,STBM_SETRATECORRECTION_SID);
  
  if(E_NOT_OK == lddReturnVal)
  {
    /* Do nothing */                          
  }                           
  else  
  #endif /* STD_ON == STBM_DEV_ERROR_DETECT */
  /* @Trace: StbM_SUD_API_042 */ 
  {
    STBM_GET_ADDRESS_TIME_BASES_CONFIGURED(timeBaseId,lusConfigPtr);
    lddReturnVal = StbM_Internal_SetRateDeviation(lusConfigPtr,rateDeviation);
    /* @Trace: SWS_StbM_00395 */ 
  /* @Trace: StbM_SUD_API_043 */ 
    if(E_NOT_OK == lddReturnVal)
    {
      /* @Trace: SWS_StbM_00392 */ 
      #if (STD_ON == STBM_DEV_ERROR_DETECT)
      (void)Det_ReportError(STBM_MODULE_ID, STBM_INSTANCE_ID,
              STBM_SETRATECORRECTION_SID, STBM_E_SERVICE_DISABLED);
      #endif /* STD_ON == STBM_DEV_ERROR_DETECT */
    }
    else
    {
      /* Do nothing */
    }
  }

  return (lddReturnVal);
} /* End of StbM_SetRateCorrection(void) */

#define STBM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : StbM_GetTimeLeap                                    **
**                                                                            **
** Service ID           : 0x13                                                **
**                                                                            **
** Description          : Returns value of Time Leap.                         **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : timeBaseId : StbM_SynchronizedTimeBaseType          **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : timeJump : StbM_TimeDiffType                        **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : StbM_GblInitStatus            **
**                                  StbM_GaaTimeBaseValue                     **
**                        Function(s) invoked : Det_ReportError               **
*******************************************************************************/
/*@Trace: RS_TS_00003 RS_TS_00009 */
#define STBM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, STBM_CODE) StbM_GetTimeLeap(
  VAR(StbM_SynchronizedTimeBaseType, AUTOMATIC)timeBaseId,
  P2VAR(StbM_TimeDiffType, AUTOMATIC, STBM_APPL_DATA)timeJump)
{
  /* @Trace: SWS_StbM_00267 */
  Std_ReturnType lddReturnVal;

  P2VAR(StbM_TimeBaseValueType, AUTOMATIC, STBM_APPL_DATA)lpTimeBaseValue;
  VAR(uint16, AUTOMATIC)lusConfigPtr;
  VAR(uint32, AUTOMATIC)lulTimeLeap;
  VAR(StbM_TimeDiffType, AUTOMATIC)lddTimeJump;
  
  lddReturnVal = E_OK; 
  lddTimeJump = (StbM_TimeDiffType)STBM_ZERO;
  /* @Trace: StbM_SUD_API_141 */
  #if (STD_ON == STBM_DEV_ERROR_DETECT)
  lddReturnVal = StbM_CheckInitStatus(lddReturnVal,STBM_GETTIMELEAP_SID);
  /* @Trace: SWS_StbM_00268 */ 
  lddReturnVal = StbM_CheckSyncOffsetTimeBaseID(lddReturnVal,timeBaseId,STBM_GETTIMELEAP_SID);
  /* @Trace: SWS_StbM_00269 */  
  lddReturnVal = StbM_CheckInvalid1Pointer(lddReturnVal,timeJump,STBM_GETTIMELEAP_SID);
  
  if(E_NOT_OK == lddReturnVal)
  {
    /* Do nothing */                          
  }                           
  else  
  #endif /* STD_ON == STBM_DEV_ERROR_DETECT */
  /* @Trace: StbM_SUD_API_142 */
  {
    STBM_GET_ADDRESS_SYNC_OFFSET_TIME_BASES_CONFIGURED(timeBaseId,lusConfigPtr);
    lpTimeBaseValue = &StbM_GaaTimeBaseValue[lusConfigPtr];
    /* @Trace: SWS_StbM_00425 */
    if(STBM_TWO == (lpTimeBaseValue->ucFirstSynch))
    {
      if(STBM_TRUE == (lpTimeBaseValue->blSignOfTimeLeap))
      {
        /* @Trace: StbM_SUD_API_143 */
        if(STBM_TIMELEAP_MAX < (lpTimeBaseValue->ulTimeLeap))
        {
          lddTimeJump = (StbM_TimeDiffType)STBM_TIMELEAP_MAX; 
        }
        else
        {
          lulTimeLeap = (uint32)(lpTimeBaseValue->ulTimeLeap);
          lddTimeJump = (StbM_TimeDiffType)lulTimeLeap; 
        }
      }
      else
      {
        if(STBM_TIMELEAP_MAX < (lpTimeBaseValue->ulTimeLeap))
        {
	        lddTimeJump = (StbM_TimeDiffType)STBM_TIMELEAP_MIN;
        }
        else
        {
          lulTimeLeap = (uint32)(lpTimeBaseValue->ulTimeLeap);
          lulTimeLeap = (uint32)(~lulTimeLeap + (uint32)STBM_ONE);
          lddTimeJump = (StbM_TimeDiffType)lulTimeLeap;
        }
      }
    }
    /* @Trace: StbM_SUD_API_144 */
    else    
    {
      /* return E_NOT_OK until the second valid invocation of */
      /* StbM_BusSetGlobalTime API */
      lddReturnVal = E_NOT_OK;                        
    } 
    /* Return value */
    /* polyspace +1 MISRA-C3:D4.14 [Not a defect:Low] "This pointer is manual checked and has no impact" */
    *timeJump = lddTimeJump;
  }
  
  return (lddReturnVal);
} /* End of StbM_GetTimeLeap(void) */

#define STBM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : StbM_GetTimeBaseStatus                              **
**                                                                            **
** Service ID           : 0x14                                                **
**                                                                            **
** Description          : Returns detailed status information for a           **
**                          Synchronized (or Pure Local) Time Base and, if    **
**                          called for an Offset Time Base, for the Offset    **
**                          Time Base and the underlying Synchronized Time    **
**                          Base.                                             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : timeBaseId : StbM_SynchronizedTimeBaseType          **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : syncTimeBaseStatus : StbM_TimeBaseStatusType        **
**                        offsetTimeBaseStatus : StbM_TimeBaseStatusType      **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : StbM_GblInitStatus            **
**                                  StbM_GaaTimeBaseValue                     **
**                        Function(s) invoked : Det_ReportError               **
*******************************************************************************/
/* @Trace: RS_TS_00005 */

#define STBM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, STBM_CODE) StbM_GetTimeBaseStatus(
  VAR(StbM_SynchronizedTimeBaseType, AUTOMATIC)timeBaseId,
  P2VAR(StbM_TimeBaseStatusType, AUTOMATIC, STBM_APPL_DATA)syncTimeBaseStatus,
  P2VAR(StbM_TimeBaseStatusType, AUTOMATIC, STBM_APPL_DATA)offsetTimeBaseStatus)
{
  /* @Trace: SWS_StbM_00263 */  
  Std_ReturnType lddReturnVal;

  P2CONST(StbM_TimeBaseConfigType, AUTOMATIC, STBM_APPL_DATA)lpTimeBaseConfig;
  P2VAR(StbM_TimeBaseValueType, AUTOMATIC, STBM_APPL_DATA)lpTimeBaseValue;
  P2VAR(StbM_TimeBaseValueType, AUTOMATIC, STBM_APPL_DATA)lpSyncTimeBaseValue;
  VAR(StbM_SynchronizedTimeBaseType, AUTOMATIC)syncTimeBaseId;
  VAR(uint16, AUTOMATIC)lusConfigPtr;
  VAR(uint16, AUTOMATIC)lusSyncConfigPtr;
  VAR(StbM_TimeStampType, AUTOMATIC)lddTimeStamp;
  VAR(StbM_TimeStampType, AUTOMATIC)lddSyncTimeStamp;
  
  lddReturnVal = E_OK;
  /* @Trace: StbM_SUD_API_131 */  
  #if (STD_ON == STBM_DEV_ERROR_DETECT)
  lddReturnVal = StbM_CheckInitStatus(lddReturnVal, STBM_GETTIMEBASESTATUS_SID);
  /* @Trace: SWS_StbM_00264 */   
  lddReturnVal = StbM_CheckTimeBaseID(lddReturnVal,timeBaseId, STBM_GETTIMEBASESTATUS_SID);
  /* @Trace: SWS_StbM_00265 */   
  lddReturnVal = StbM_CheckInvalid2Pointer(lddReturnVal, syncTimeBaseStatus, offsetTimeBaseStatus, STBM_GETTIMEBASESTATUS_SID);
  
  if(E_NOT_OK == lddReturnVal)
  {
    /* Do nothing */                          
  }                           
  else  
  #endif /* STD_ON == STBM_DEV_ERROR_DETECT */
  /* @Trace: StbM_SUD_API_132 */  
  {     
    /* @Trace: SWS_StbM_00262 */      
    /* Get address of TimeBaseConfig */
    STBM_GET_ADDRESS_TIME_BASES_CONFIGURED(timeBaseId,lusConfigPtr);
    lpTimeBaseValue = &StbM_GaaTimeBaseValue[lusConfigPtr];
    /* polyspace +1 RTE:IDP [Not a defect:Low] "This pointer is manual checked and has no impact" */
    STBM_COPY_STATUS(&lddTimeStamp, &(lpTimeBaseValue->ddLocalTime));
    if(!((timeBaseId >= STBM_SIXTEEN) &&         
             (timeBaseId <= STBM_MAX_OFFSET_TIME_BASES_CONFIGURED)))
    {
      /* return the status of the corresponding Time Base */
      /* polyspace +2 MISRA-C3:D4.14 [Not a defect:Low] "This pointer is manual checked and has no impact" */
      *syncTimeBaseStatus = lddTimeStamp.timeBaseStatus;
      *offsetTimeBaseStatus = (StbM_TimeBaseStatusType)STBM_ZERO;
    }
    /* @Trace: StbM_SUD_API_133 */ 
    else
    {
      /* Get Config of Sync Time Base */
      lpTimeBaseConfig = &StbM_GaaTimeBaseConfig[lusConfigPtr];
      syncTimeBaseId = lpTimeBaseConfig->ddSyncTimeBaseId;  
      STBM_GET_ADDRESS_SYNC_TIME_BASES_CONFIGURED(syncTimeBaseId,lusSyncConfigPtr);
      lpSyncTimeBaseValue = &StbM_GaaTimeBaseValue[lusSyncConfigPtr]; 
      /* @Trace: SWS_StbM_00261 */ 
      STBM_COPY_STATUS(&lddSyncTimeStamp, &(lpSyncTimeBaseValue->ddLocalTime));
      /* return the status of the corresponding Time Base */
      /* polyspace +2 MISRA-C3:D4.14 [Not a defect:Low] "This pointer is manual checked and has no impact" */
      *syncTimeBaseStatus = lddSyncTimeStamp.timeBaseStatus;
      *offsetTimeBaseStatus = lddTimeStamp.timeBaseStatus;
    }
  }
  
  return (lddReturnVal);
} /* End of StbM_GetTimeBaseStatus(void) */

#define STBM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : StbM_StartTimer                                     **
**                                                                            **
** Service ID           : 0x15                                                **
**                                                                            **
** Description          : Sets a time value, which the Time Base value is     ** 
**                          compared against.                                 **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : timeBaseId : StbM_SynchronizedTimeBaseType          **
**                        customerId : StbM_CustomerIdType                    **
**                        expireTime : StbM_TimeStampType                     **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : StbM_GblInitStatus            **
**                                  StbM_GaaTimeBaseValue                     **
**                                  StbM_GaaNotificationValue                 **
**                        Function(s) invoked : Det_ReportError               **
**                                  StbM_Internal_GetCurrentTime              **
**                                  StbM_Math_SumOfTwoTimeStamp               **
*******************************************************************************/
/* @Trace: RS_TS_00017, RS_TS_00023 */
#define STBM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, STBM_CODE) StbM_StartTimer(
  VAR(StbM_SynchronizedTimeBaseType, AUTOMATIC)timeBaseId,
  VAR(StbM_CustomerIdType, AUTOMATIC)customerId,
  P2CONST(StbM_TimeStampType, AUTOMATIC, STBM_APPL_DATA)expireTime)
{
  /* @Trace: SWS_StbM_00272 */  
  Std_ReturnType lddReturnVal;
  #if(STBM_TIME_NOTIFICATION_SUPPORT == STD_ON)
  VAR(uint16, AUTOMATIC)lusEndOfNotification;
  VAR(uint16, AUTOMATIC)lusCount;
  VAR(uint16, AUTOMATIC)lusBaseOfNotification;
  P2CONST(StbM_TimeBaseConfigType, AUTOMATIC, STBM_APPL_DATA)lpTimeBaseConfig;
  P2VAR(StbM_TimeBaseValueType, AUTOMATIC, STBM_APPL_DATA)lpTimeBaseValue;
  P2VAR(StbM_NotificationValueType, AUTOMATIC, STBM_APPL_DATA)lpNotificationValue;
  VAR(uint16, AUTOMATIC)lusConfigPtr;
  VAR(uint16, AUTOMATIC)lusNotificationPtr;
  #endif
  VAR(StbM_TimeStampType, AUTOMATIC)lddTimeStamp;
  VAR(StbM_TimeStampType, AUTOMATIC)lulExpireTime;

  lddReturnVal = E_OK; 
  STBM_INIT_TIMESTAMP(&lddTimeStamp);
  STBM_INIT_TIMESTAMP(&lulExpireTime);
  /* @Trace: StbM_SUD_API_151 */ 
  #if (STD_ON == STBM_DEV_ERROR_DETECT)
  lddReturnVal = StbM_CheckInitStatus(lddReturnVal, STBM_STARTTIMER_SID);
  /* @Trace: SWS_StbM_00296 */  
  lddReturnVal = StbM_CheckTimeBaseID(lddReturnVal, timeBaseId, STBM_STARTTIMER_SID);
  /* @Trace: SWS_StbM_00298 */ 
  lddReturnVal = StbM_CheckInvalid1Pointer(lddReturnVal,expireTime,STBM_STARTTIMER_SID);
  
  if(E_NOT_OK == lddReturnVal)
  {
    /* Do nothing */                          
  }                           
  else  
  #endif /* STD_ON == STBM_DEV_ERROR_DETECT */
  /* @Trace: StbM_SUD_API_152 */ 
  {
    #if(STBM_TIME_NOTIFICATION_SUPPORT == STD_ON)
    /* check customerId */  
    STBM_GET_ADDRESS_TIME_BASES_CONFIGURED(timeBaseId,lusConfigPtr);
    /* polyspace +2 RTE:IDP [Not a defect:Low] "StbM_GaaTimeBaseConfig is verified and generated by Generator Tool" */

    lpTimeBaseConfig = &StbM_GaaTimeBaseConfig[lusConfigPtr];
    /* polyspace +1 RTE:IDP [Not a defect:Low] "StbM_GaaTimeBaseConfig is verified and generated by Generator Tool" */
    lusBaseOfNotification = (lpTimeBaseConfig)->usBaseOfNotification; /*polyspace MISRA-C:18.1 [Not a defect:Low] "StbM_GaaTimeBaseConfig is verified and generated by Generator Tool"*/
    lusEndOfNotification = lusBaseOfNotification +   
                            (lpTimeBaseConfig)->usSizeOfNotification;
	#endif
    lddReturnVal = E_NOT_OK; 
    #if(STBM_TIME_NOTIFICATION_SUPPORT == STD_ON)
    lusNotificationPtr = STBM_ZERO;
    for(lusCount = lusBaseOfNotification; lusCount < lusEndOfNotification;    
                            lusCount++)
    {
      /* polyspace +1 RTE:OBAI [Not a defect:Low] "StbM_GaaNotificationConfig is verified and generated by Generator Tool" */
      if(customerId == StbM_GaaNotificationConfig[lusCount].usId) /*polyspace MISRA-C:18.1 [Not a defect:Low] "StbM_GaaNotificationConfig is verified and generated by Generator Tool"*/
      {
        lusNotificationPtr = lusCount;
        lddReturnVal = E_OK;
      }    
      else
      {
        /* Do nothing */ 
      }    
    }
    #else
    (void)STBM_UNUSED(customerId);
    #endif
    /* If customerId is invalid */
    /* @Trace: StbM_SUD_API_153 */
    #if(STBM_TIME_NOTIFICATION_SUPPORT == STD_ON)
    if(E_NOT_OK == lddReturnVal)
    #endif
    {    
      /* @Trace: SWS_StbM_00406 */ 
      #if (STD_ON == STBM_DEV_ERROR_DETECT) 
      (void)Det_ReportError(STBM_MODULE_ID, STBM_INSTANCE_ID,  
                            STBM_STARTTIMER_SID, STBM_E_PARAM);
      #endif /* STD_ON == STBM_DEV_ERROR_DETECT */          
    }
    #if(STBM_TIME_NOTIFICATION_SUPPORT == STD_ON)
    else
    {
      lddReturnVal = StbM_Internal_GetCurrentTime(lusConfigPtr, &lddTimeStamp, NULL_PTR, NULL_PTR);
      if(E_OK == lddReturnVal)
      { 
        lpTimeBaseValue = &StbM_GaaTimeBaseValue[lusConfigPtr];
        lpNotificationValue = &StbM_GaaNotificationValue[lusNotificationPtr];
	/* polyspace +1 MISRA-C3:D4.14 [Not a defect:Low] "This pointer is manual checked and has no impact" */
        STBM_COPY_TIMESTAMP(&lulExpireTime,expireTime); /*polyspace MISRA-C:4.14 [Not a defect:Low] "This parameter is passed by Upper layer. Module only check that it isn't NULL"*/
        /* calculate the time CustomerTimerExpireTime */
        /* @Trace: SWS_StbM_00270 */
        StbM_Math_SumOfTwoTimeStamp(lddTimeStamp, lulExpireTime, 
                  &(lpNotificationValue->CustomerTimerExpireTime));
        /* polyspace +3 DEFECT:UINT_CONV_OVFL [Not a defect:Low] "blStartTimerCount is not able to reach the max value of uint32" */
        /* polyspace +2 CERT-C:INT31-C [Not a defect:Low] "blStartTimerCount is not able to reach the max value of uint32" */
        lpTimeBaseValue->blStartTimerCount = STBM_ONE +
                  lpTimeBaseValue->blStartTimerCount;
        lpNotificationValue->blStartTimer = STBM_TRUE;
      }
      else
      {
        /* Do nothing */                          
      } 
    }
    #endif
  }
  
  return (lddReturnVal);
} /* End of StbM_StartTimer(void) */

#define STBM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : StbM_GetSyncTimeRecordHead                          **
**                                                                            **
** Service ID           : 0x16                                                **
**                                                                            **
** Description          : Accesses to the recorded snapshot data Header of the**
**                          table belonging to the Synchronized Time Base.    **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : timeBaseId : StbM_SynchronizedTimeBaseType          **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : syncRecordTableHead : StbM_SyncRecordTableHeadType  **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : StbM_GblInitStatus            **
**                        Function(s) invoked : Det_ReportError               **
*******************************************************************************/
/* @Trace: SWS_StbM_00320 */
/* @Trace: RS_TS_00002, RS_TS_00034  */
#if (STD_ON == STBM_TIME_RECORDING_SUPPORT) 

#define STBM_START_SEC_CODE
#include "MemMap.h"

FUNC(Std_ReturnType, STBM_CODE) StbM_GetSyncTimeRecordHead(
  VAR(StbM_SynchronizedTimeBaseType, AUTOMATIC)timeBaseId,
  P2VAR(StbM_SyncRecordTableHeadType, AUTOMATIC, STBM_APPL_DATA)syncRecordTableHead)
{
  /* @Trace: SWS_StbM_00319 */ 
  Std_ReturnType lddReturnVal;
  P2CONST(StbM_TimeBaseConfigType, AUTOMATIC, STBM_APPL_DATA)lpConfig;
  P2CONST(StbM_SyncRecordTableHeadType, AUTOMATIC, STBM_APPL_DATA)lpRecord;
  VAR(uint16, AUTOMATIC)lusConfigPtr;
  
  lddReturnVal = E_OK; 
  /* @Trace: StbM_SUD_API_121 */ 
  #if (STD_ON == STBM_DEV_ERROR_DETECT)
  STBM_CHECK_INIT(lddReturnVal,STBM_GETSYNCTIMERECORDHEAD_SID);
  /* @Trace: SWS_StbM_00394 */   
  STBM_CHECK_SYNC_TIME_BASE_ID(lddReturnVal,timeBaseId,STBM_GETSYNCTIMERECORDHEAD_SID);
  /* @Trace: SWS_StbM_00405 */ 
  STBM_CHECK_INVALID_POINTER(lddReturnVal,syncRecordTableHead,STBM_GETSYNCTIMERECORDHEAD_SID);
  
  if(E_NOT_OK == lddReturnVal)
  {
    /* Do nothing */                          
  }                           
  else  
  #endif /* STD_ON == STBM_DEV_ERROR_DETECT */
  /* @Trace: StbM_SUD_API_122 */ 
  {
    lusConfigPtr = (uint16)timeBaseId;
    lpConfig = &StbM_GaaTimeBaseConfig[lusConfigPtr];
    /* @Trace: SWS_StbM_00428 */
    /* Condition STBM_FALSE == (lpTimeBaseConfig->enSystemWideTimeMasterSlave) */
    /* is checked by Generation tool*/
    if(STBM_BASE_INVAILD != lpConfig->ucBaseOfRecording)
    {
      lpRecord = &StbM_GaaSyncRecordTableHead[lpConfig->ucBaseOfRecording];
      /* @Trace: SWS_StbM_ */
      /* polyspace +1 MISRA-C3:D4.14 [Not a defect:Low] "This pointer is manual checked and has no impact" */
      syncRecordTableHead->SynchronizedTimeDomain = lpRecord->SynchronizedTimeDomain; /*polyspace MISRA-C:4.14 [Not a defect:Low] "This parameter is passed by Upper layer. Module only check that it isn't NULL"*/
      syncRecordTableHead->HWfrequency = lpRecord->HWfrequency;
      syncRecordTableHead->HWprescaler = lpRecord->HWprescaler;
    }
    else
    {
      lddReturnVal = E_NOT_OK; 
    }
  }
  
  return (lddReturnVal);
} /* End of StbM_GetSyncTimeRecordHead(void) */

#define STBM_STOP_SEC_CODE
#include "MemMap.h"

#endif /* STD_ON == STBM_TIME_RECORDING_SUPPORT */
/*******************************************************************************
** Function Name        : StbM_GetOffsetTimeRecordHead                        **
**                                                                            **
** Service ID           : 0x17                                                **
**                                                                            **
** Description          : Accesses to the recorded snapshot data Header of the**
**                          table belonging to the Offset Time Base.          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : timeBaseId : StbM_SynchronizedTimeBaseType          **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : offsetRecordTableHead:StbM_OffsetRecordTableHeadType**
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : StbM_GblInitStatus            **
**                        Function(s) invoked : Det_ReportError               **
*******************************************************************************/
/* @Trace: RS_TS_00034 */
/* @Trace: SWS_StbM_00326 */
#if (STD_ON == STBM_TIME_RECORDING_SUPPORT) 

#define STBM_START_SEC_CODE
#include "MemMap.h"

FUNC(Std_ReturnType, STBM_CODE) StbM_GetOffsetTimeRecordHead(
  VAR(StbM_SynchronizedTimeBaseType, AUTOMATIC)timeBaseId,
  P2VAR(StbM_OffsetRecordTableHeadType, AUTOMATIC, STBM_APPL_DATA)offsetRecordTableHead)
{
  /* @Trace: SWS_StbM_00325 */
  Std_ReturnType lddReturnVal;
  P2CONST(StbM_TimeBaseConfigType, AUTOMATIC, STBM_APPL_DATA)lpConfig;
  P2CONST(StbM_OffsetRecordTableHeadType, AUTOMATIC, STBM_APPL_DATA)lpRecord;
  VAR(uint16, AUTOMATIC)lusConfigPtr;
  
  lddReturnVal = E_OK;  
  /* @Trace: StbM_SUD_API_101 */
  #if (STD_ON == STBM_DEV_ERROR_DETECT)
  STBM_CHECK_INIT(lddReturnVal,STBM_GETOFFSETTIMERECORDHEAD_SID);
  /* @Trace: SWS_StbM_00327 */  
  STBM_CHECK_OFFSET_TIME_BASE_ID(lddReturnVal,timeBaseId,STBM_GETOFFSETTIMERECORDHEAD_SID);
  /* @Trace: SWS_StbM_00404 */
  STBM_CHECK_INVALID_POINTER(lddReturnVal,offsetRecordTableHead,STBM_GETOFFSETTIMERECORDHEAD_SID);
  
  if(E_NOT_OK == lddReturnVal)
  {
    /* Do nothing */
  }                           
  else  
  #endif /* STD_ON == STBM_DEV_ERROR_DETECT */
  /* @Trace: StbM_SUD_API_102 */
  {
    lusConfigPtr = (uint16)timeBaseId - STBM_SIXTEEN +
                      STBM_BASE_OFFSET_TIME_BASES_CONFIGURED;
    lpConfig = &StbM_GaaTimeBaseConfig[lusConfigPtr];
    /* @Trace: SWS_StbM_00428 */
    /* Condition STBM_FALSE == (lpTimeBaseConfig->enSystemWideTimeMasterSlave) */
    /* is checked by Generation tool*/
    if(STBM_BASE_INVAILD != lpConfig->ucBaseOfRecording)
    {
      lpRecord = &StbM_GaaOffsetRecordTableHead[lpConfig->ucBaseOfRecording];
      /* @Trace: SWS_StbM_00316 */
      /* polyspace +1 MISRA-C3:D4.14 [Not a defect:Low] "This pointer is manual checked and has no impact" */
      offsetRecordTableHead->OffsetTimeDomain = lpRecord->OffsetTimeDomain; /*polyspace MISRA-C:4.14 [Not a defect:Low] "This parameter is passed by Upper layer. Module only check that it isn't NULL"*/
    }
    else
    {/* polyspace RTE:UNR [Not a defect:Low] "This branch is available for other configuration" */
      lddReturnVal = E_NOT_OK; 
    }
  }
  
  return (lddReturnVal);
} /* End of StbM_GetOffsetTimeRecordHead(void) */

#define STBM_STOP_SEC_CODE
#include "MemMap.h"

#endif /* STD_ON == STBM_TIME_RECORDING_SUPPORT */

/*******************************************************************************
** Function Name        : StbM_TriggerTimeTransmission                        **
**                                                                            **
** Service ID           : 0x1c                                                **
**                                                                            **
** Description          : Called by the <Upper Layer> to force the Timesync   **
**                          Modules to transmit the current Time Base again   **
**                          due to an incremented                             **
**                          timeBaseUpdateCounter[timeBaseId].                **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : timeBaseId : StbM_SynchronizedTimeBaseType          **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : StbM_GblInitStatus            **
**                        Function(s) invoked : Det_ReportError               **
**                              StbM_Internal_IncreaseCounterOfTimeBase       **
*******************************************************************************/
/* @Trace: RS_TS_00011 */
#define STBM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, STBM_CODE) StbM_TriggerTimeTransmission(
  VAR(StbM_SynchronizedTimeBaseType, AUTOMATIC)timeBaseId)
{
  /* @Trace: SWS_StbM_00346 */
  Std_ReturnType lddReturnVal;
  
  VAR(uint16, AUTOMATIC)lusConfigPtr;
  
  lddReturnVal = E_OK;  
  /* @Trace: StbM_SUD_API_061 */
  #if (STD_ON == STBM_DEV_ERROR_DETECT)
  STBM_CHECK_INIT(lddReturnVal,STBM_TRIGGERTIMETRANSMISSION_SID);
  /* @Trace: SWS_StbM_00349 */
  STBM_CHECK_SYNC_OFFSET_TIME_BASE_ID(lddReturnVal,timeBaseId,STBM_TRIGGERTIMETRANSMISSION_SID);
  
  if(E_NOT_OK == lddReturnVal)
  {
    /* Do nothing */                          
  }                           
  else  
  #endif /* STD_ON == STBM_DEV_ERROR_DETECT */ 
  /* @Trace: StbM_SUD_API_062 */
  {
    STBM_GET_ADDRESS_SYNC_OFFSET_TIME_BASES_CONFIGURED(timeBaseId,lusConfigPtr);        
    /* @Trace: SWS_StbM_00350 */ 
    /* Update timeBaseUpdateCounter */
    StbM_Internal_IncreaseCounterOfTimeBase(lusConfigPtr);
  }
  
  return (lddReturnVal);
} /* End of StbM_TriggerTimeTransmission(void) */

#define STBM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : StbM_GetTimeBaseUpdateCounter                       **
**                                                                            **
** Service ID           : 0x1b                                                **
**                                                                            **
** Description          : Allows the Timesync Modules to detect, whether a    **
**                          Time Base should be transmitted immediately in    **
**                          the subsequent <Bus>TSyn_MainFunction() cycle.    **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : timeBaseId : StbM_SynchronizedTimeBaseType          **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : uint8                                               **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : StbM_GblInitStatus            **
**                        Function(s) invoked : Det_ReportError               **
*******************************************************************************/
/* @Trace: RS_TS_00011 */
#define STBM_START_SEC_CODE
#include "MemMap.h"
FUNC(uint8, STBM_CODE) StbM_GetTimeBaseUpdateCounter(
  VAR(StbM_SynchronizedTimeBaseType, AUTOMATIC)timeBaseId)
{
  /* @Trace: SWS_StbM_00347 */
  Std_ReturnType lddReturnVal;
  uint8 lusReturnVal;

  P2VAR(StbM_TimeBaseValueType, AUTOMATIC, STBM_APPL_DATA)lpTimeBaseValue;
  VAR(uint16, AUTOMATIC)lusConfigPtr;
  
  lusReturnVal = STBM_ZERO;
  lddReturnVal = E_OK;
  /* @Trace: StbM_SUD_API_201 */
  #if (STD_ON == STBM_DEV_ERROR_DETECT)
  STBM_CHECK_INIT(lddReturnVal,STBM_GETTIMEBASEUPDATECOUNTER_SID);
  /* @Trace: SWS_StbM_00348 */ 
  STBM_CHECK_SYNC_OFFSET_TIME_BASE_ID(lddReturnVal,timeBaseId,STBM_GETTIMEBASEUPDATECOUNTER_SID);
  
  if(E_NOT_OK == lddReturnVal)
  {
    /* Do nothing */                          
  }                           
  else  
  #endif /* STD_ON == STBM_DEV_ERROR_DETECT */
  /* @Trace: StbM_SUD_API_202 */
  {
    STBM_GET_ADDRESS_SYNC_OFFSET_TIME_BASES_CONFIGURED(timeBaseId,lusConfigPtr);
    lpTimeBaseValue = &StbM_GaaTimeBaseValue[lusConfigPtr];
    /* @Trace: SWS_StbM_00414 */
    /* @Trace: SWS_StbM_00351 */
    lusReturnVal = lpTimeBaseValue->timeBaseUpdateCounter;
    /* action */
  }
  
  return (lusReturnVal);
} /* End of StbM_GetTimeBaseUpdateCounter(void) */

#define STBM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : StbM_GetMasterConfig                                **
**                                                                            **
** Service ID           : 0x1d                                                **
**                                                                            **
** Description          : Indicates if the functionality for a system wide    ** 
**                          master (e.g. StbM_SetGlobalTime) for a given Time **
**                          Base is available or not.                         **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : timeBaseId : StbM_SynchronizedTimeBaseType          **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : masterConfig : StbM_MasterConfigType                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : StbM_GblInitStatus            **
**                        Function(s) invoked : Det_ReportError               **
*******************************************************************************/
/* @Trace: RS_TS_00029 */
#define STBM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, STBM_CODE) StbM_GetMasterConfig(
  VAR(StbM_SynchronizedTimeBaseType, AUTOMATIC)timeBaseId,
  P2VAR(StbM_MasterConfigType, AUTOMATIC, STBM_APPL_DATA)masterConfig)
{
  /* @Trace: SWS_StbM_91002 */ 
  Std_ReturnType lddReturnVal;

  P2CONST(StbM_TimeBaseConfigType, AUTOMATIC, STBM_APPL_DATA)lpTimeBaseConfig;
  VAR(uint16, AUTOMATIC)lusConfigPtr;
  
  lddReturnVal = E_OK;
  /* @Trace: StbM_SUD_API_011 */
  #if (STD_ON == STBM_DEV_ERROR_DETECT)
  STBM_CHECK_INIT(lddReturnVal,STBM_GETMASTERCONFIG_SID);
  /* @Trace: SWS_StbM_00415 */  
  STBM_CHECK_TIME_BASE_ID(lddReturnVal,timeBaseId,STBM_GETMASTERCONFIG_SID);
  /* @Trace: SWS_StbM_00416 */ 
  STBM_CHECK_INVALID_POINTER(lddReturnVal,masterConfig,STBM_GETMASTERCONFIG_SID);
  
  if(E_NOT_OK == lddReturnVal)
  {
    /* Do nothing */                          
  }                           
  else
  #endif /* STD_ON == STBM_DEV_ERROR_DETECT */
  /* @Trace: StbM_SUD_API_012 */
  {
    STBM_GET_ADDRESS_TIME_BASES_CONFIGURED(timeBaseId,lusConfigPtr);
    lpTimeBaseConfig = &StbM_GaaTimeBaseConfig[lusConfigPtr];
    /* @Trace: SWS_StbM_00408*/
    *masterConfig = (StbM_MasterConfigType)
          (lpTimeBaseConfig->enSystemWideTimeMasterSlave);
  }
  
  return (lddReturnVal);
} /* End of StbM_GetMasterConfig(void) */

#define STBM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : StbM_MainFunction                                   **
**                                                                            **
** Service ID           : 0x04                                                **
**                                                                            **
** Description          : This function will be called cyclically by a task   ** 
**                          body provided by the BSW Schedule. It will invoke ** 
**                          the triggered customers and synchronize the       ** 
**                          referenced OS ScheduleTables.                     **
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
** Remarks              : Global Variable(s)  : StbM_GaaTimeBaseValue         **
**                        Function(s) invoked : StbM_Internal_GetCurrentTime  **
**                                      StbM_Internal_CheckTimeOut            **
**                                      StbM_Internal_SlaveTimeCorrection     **
**                                      StbM_Internal_TimerNotification       **
**                                      StbM_Internal_ReadTimeRecordTable     **
**                                      StbM_Internal_Trigger                 **
*******************************************************************************/
/* @Trace: RS_TS_00009, RS_TS_00017, RS_TS_00025, RS_TS_00034  */
#define STBM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, STBM_CODE) StbM_MainFunction(void)
{
  /* @Trace: SWS_StbM_00057*/

  Std_ReturnType lddReturnVal;
  P2VAR(StbM_TimeBaseValueType, AUTOMATIC, STBM_APPL_DATA)lpTimeBaseValue;
  
  VAR(uint16, AUTOMATIC)lusConfigPtr;
  VAR(StbM_TimeStampType, AUTOMATIC)lddTimeStamp; 
  #if (STD_ON == STBM_TIME_CORRECTION_SUPPORT) 
  VAR(StbM_VirtualLocalTimeType, AUTOMATIC)lddVlt;
  #endif /* STD_ON == STBM_TIME_CORRECTION_SUPPORT */ 
  
  STBM_INIT_TIMESTAMP(&lddTimeStamp); 
  #if (STD_ON == STBM_TIME_CORRECTION_SUPPORT) 
  STBM_INIT_VLTIME(&lddVlt); 
  #endif /* STD_ON == STBM_TIME_CORRECTION_SUPPORT */ 
  
  for(lusConfigPtr = (uint16)STBM_ZERO; lusConfigPtr <(uint16) 
                      (STBM_NUMBER_TIME_BASES_CONFIGURED); lusConfigPtr++)
  {
    lpTimeBaseValue = &(StbM_GaaTimeBaseValue[lusConfigPtr]);
    /* @Trace: StbM_SUD_API_231 */
    if(((lpTimeBaseValue->ddLocalTime.timeBaseStatus) & 
                        STBM_STATE_GLOBAL_TIME_BASE)!=STBM_ZERO)
    {
      lddReturnVal = StbM_Internal_GetCurrentTime(lusConfigPtr,&lddTimeStamp,   
                 #if (STD_ON == STBM_TIME_CORRECTION_SUPPORT) 
                   &lddVlt, 
                 #else
                   NULL_PTR,
                 #endif /* STD_ON == STBM_TIME_CORRECTION_SUPPORT */ 
                    NULL_PTR);
      if(E_OK == lddReturnVal)
      {
        /* Check TIMEOUT bit */
        /* @Trace: SWS_StbM_00183 */
        /* @Trace: SWS_StbM_00187 */
        (void) StbM_Internal_CheckTimeOut(lusConfigPtr, lddTimeStamp); /*polyspace MISRA-C:17.7 [Not a defect:Low] "This function isn't required to use return value of sub-function."*/
        
        /* Time correction */      
        #if (STD_ON == STBM_TIME_CORRECTION_SUPPORT)  
        (void) StbM_Internal_SlaveTimeCorrection(lusConfigPtr, lddVlt); /*polyspace MISRA-C:17.7 [Not a defect:Low] "This function isn't required to use return value of sub-function."*/
        #endif /* STD_ON == STBM_TIME_CORRECTION_SUPPORT */ 
        
        #if (STD_ON == STBM_TIME_NOTIFICATION_SUPPORT)  
        /* @Trace: SWS_StbM_00335 */
        /* @Trace: SWS_StbM_00336 */
        /* @Trace: SWS_StbM_00337 */
        /* @Trace: SWS_StbM_00432 */
        StbM_Internal_TimerNotification(lusConfigPtr, lddTimeStamp);
        #endif /* STD_ON == STBM_TIME_NOTIFICATION_SUPPORT */       
      
        #if(STD_ON == STBM_TIME_RECORDING_SUPPORT) 
        /* @Trace: SWS_StbM_00322 */
        /* @Trace: SWS_StbM_00323 */
        /* @Trace: SWS_StbM_00328 */
        /* @Trace: SWS_StbM_00329 */
        StbM_Internal_ReadTimeRecordTable(lusConfigPtr);
        #endif /* STD_ON == STBM_TIME_RECORDING_SUPPORT */       
      
        #if(STD_ON == STBM_TRIGGERED_CUSTOMER_SUPPORT)   
        StbM_Internal_Trigger(lusConfigPtr, lddTimeStamp);
        #endif /* STD_ON == STBM_TRIGGERED_CUSTOMER_SUPPORT */ 
      }
      else
      {
        /* Do nothing */
      }
    }
    /* @Trace: StbM_SUD_API_232 */
    else
    {
      /* Do nothing */
    }    
  }
} /* End of StbM_MainFunction(void) */

#define STBM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
