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
**  SRC-MODULE: Dem_Dtc.h                                                     **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostic Event Manager                              **
**                                                                            **
**  PURPOSE   : C header for Dem_Dtc.c                                        **
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
** 2.0.0.0   31-Dec-2023   EK Kim        Jira #CP44-1515 #CP44-3198 #CP44-3298**
** 1.0.8.0   13-Dec-2021   SY Kim        Jira #CP44-1169                      **
** 1.0.1.0   07-May-2021   HaoLT6        R44-Redmine #18724                   **
** 1.0.0     26-Feb-2021   EK Kim        Initial version                      **
*******************************************************************************/

#ifndef DEM_DTC_H
#define DEM_DTC_H
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/

#define DEM_START_SEC_CODE
#include "MemMap.h"

extern FUNC(Std_ReturnType, DEM_CODE)
Dem_DTCGroupIsValid(
  const Dem_DTCGroupType DTCGroup,
  const Dem_DTCFormatType DTCFormat);

#if (DEM_NUMBER_OF_DEM_CLIENT > DEM_ZERO)
  extern FUNC(void, DEM_CODE)  Dem_InitProtectedRecord(void);
#endif

#if (DEM_NUMBER_OF_DEM_CLIENT > DEM_ZERO)
extern FUNC(Dem_ReturnConditionOfDTCRecordUpdateType, DEM_CODE)
Dem_GetConditionOfDTCRecordUpdate(
  uint8 ClientId,
  const Dem_DTCType DTC);
#endif

#if (DEM_NUMBER_OF_DEM_CLIENT > DEM_ZERO)
extern FUNC(Dem_ReturnConditionOfDTCRecordUpdateType, DEM_CODE)
Dem_GetStatusOfDTCRecordUpdate(
  Dem_EventIdType EventId);
#endif

extern FUNC(void, DEM_CODE) Dem_CountAndStoreFilterDtc(uint8 ClientId);

extern FUNC(Std_ReturnType, DEM_CODE) Dem_ClearSingleDTCStatusByte(
  Dem_CombinedDtcPCType cbDTC,
  Dem_DTCOriginType DTCOrigin);

extern FUNC(Dem_UdsStatusByteType, DEM_CODE) Dem_GetDTCStatus(
  const Dem_EventIdType EventId);

extern FUNC(Std_ReturnType, DEM_CODE) Dem_InternalClearDTC(
  Dem_ClientIdType ClientId, uint32 DTC,
  Dem_DTCFormatType DTCFormat, Dem_DTCOriginType DTCOrigin);

extern FUNC(boolean, DEM_CODE) Dem_SelectedDTCServiceIsLock(
  uint8 ClientId,
  uint8 ServiceId);

extern FUNC(void, DEM_CODE) Dem_SelectedDTCServiceLock(
  uint8 ClientId,
  uint8 ServiceId);

extern FUNC(void, DEM_CODE) Dem_SelectedDTCServiceUnLock(
  uint8 ClientId,
  uint8 ServiceId);

extern FUNC(boolean, DEM_CODE) Dem_SetDTCFilterServiceIsLock(
  uint8 ClientId,
  uint8 ServiceId);

extern FUNC(void, DEM_CODE) Dem_SetDTCFilterServiceLock(
  uint8 ClientId,
  uint8 ServiceId);

extern FUNC(void, DEM_CODE) Dem_SetDTCFilterServiceUnLock(
  uint8 ClientId,
  uint8 ServiceId);

extern FUNC(boolean, DEM_CODE) Dem_SetFFRecordFilterServiceIsLock(
  uint8 ClientId,
  uint8 ServiceId);

extern FUNC(void, DEM_CODE) Dem_SetFFRecordFilterServiceLock(
  uint8 ClientId,
  uint8 ServiceId);

extern FUNC(void, DEM_CODE) Dem_SetFFRecordFilterServiceUnLock(
  uint8 ClientId,
  uint8 ServiceId);

extern FUNC(Std_ReturnType, DEM_CODE) Dem_CheckStatusOfSelectedDTCServices(
  uint8 ClientId,
  uint8 ServiceId,
  uint16 ServiceIdIndex);

/* polyspace:begin<MISRA-C:1.1:Not a defect:No action planned>
 * inline-MISRA C:2012 permits the use of inline functions in header files */
/* polyspace:begin<MISRA-C:8.1:Not a defect:No action planned>
 * inline-MISRA C:2012 permits the use of inline functions in header files */
/* polyspace:begin<MISRA-C:8.5:Not a defect:No action planned>
 * inline-MISRA C:2012 permits the use of inline functions in header files */

static DEM_INLINE FUNC(Dem_CombinedDtcPCType, DEM_CODE) Dem_GetCbDTCByEventId(
    Dem_EventIdType EventId)
{
  Dem_CombinedDtcPCType LddCbDTC;

  /* polyspace<RTE:UNR:Not a defect:No action planned>
   * If-condition always evaluates to false. */
  if ((EventId > DEM_NUMBER_OF_EVENTS) || (DEM_NO_EVENT == EventId))
  /* polyspace<RTE:UNR:Not a defect:No action planned>
   * If-condition always evaluates to false. */
  {
    /* @Trace: Dem_SUD_API_20034 */
    LddCbDTC = NULL_PTR;
  }  
  else
  {    
    /* @Trace: Dem_SUD_API_20930 */
    uint16 LusPos = Dem_Event[EventId - DEM_ONE].e_PointToDTC;
    if (LusPos < DEM_MAX_NUMBER_OF_DTC)
    {
      /* @Trace: Dem_SUD_API_20931 */
      LddCbDTC = &Dem_GaaCombinedDtc[LusPos];
    }
    else
    {
      /* @Trace: Dem_SUD_API_20932 */
      LddCbDTC = NULL_PTR;
    }
  }
  
  return LddCbDTC;
}

static DEM_INLINE FUNC(boolean, DEM_CODE) Dem_DTCFormatIsValid(
  Dem_EventIdType EventId, 
  Dem_DTCFormatType DTCFormat)
{
  boolean LblValid = DEM_FALSE;
  Dem_CombinedDtcPCType LddCbDTC = Dem_GetCbDTCByEventId(EventId);
  /* @Trace: Dem_SUD_API_20035 */
  if (NULL_PTR != LddCbDTC)
  {
    /* @Trace: Dem_SUD_API_20934 */
    switch(DTCFormat)
    {
      /* @Trace: Dem_SUD_API_20933 */
      case DEM_DTC_FORMAT_UDS:
      /* polyspace +1 MISRA-C3:D4.1 [Justified:Low] "Not a defect" */
      if(LddCbDTC->ulUdsDtc != DEM_NO_DTC)
      {
        /* polyspace +1 MISRA-C3:10.3 [Justified:Low] "Not a defect" */
        LblValid = DEM_TRUE;
      }
      break;

	  #if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
      case DEM_DTC_FORMAT_OBD:
      if(LddCbDTC->usObdDtc != DEM_NO_DTC)
      {
        LblValid = DEM_TRUE;
      }
      break;

	  #if(DEM_J1979_2_OBD_ON_UDS == STD_ON)
      case DEM_DTC_FORMAT_OBD_3BYTE:
	  #if (DEM_OBD_UDS_DTC_SEPARATION_SUPPORT == STD_ON)
      if(LddCbDTC->ulObdDtc3Byte != DEM_NO_DTC)
	  #else 
      if(LddCbDTC->ulUdsDtc != DEM_NO_DTC)
	  #endif /* (DEM_OBD_UDS_DTC_SEPARATION_SUPPORT == STD_ON) */
      {
        LblValid = DEM_TRUE;
      }
      break;
	  #endif /*(DEM_J1979_2_OBD_ON_UDS == STD_ON)*/
	  #endif /* (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT) */

      #if (DEM_DTC_FORMAT_J1939 == STD_ON)
      if(LddCbDTC->J1939DTCValue != DEM_NO_DTC)
      {
        LblValid = DEM_TRUE;
      }
      break;
      #endif /* (DEM_DTC_FORMAT_J1939 == STD_ON) */

      default:
      break;

    }
  }     
  return LblValid;
}

static DEM_INLINE  FUNC(Dem_CombinedDtcPCType , DEM_CODE) Dem_GetDtcByDtcId(
  const uint32 DTC, const Dem_DTCFormatType DTCFormat)
{
  P2CONST(Dem_CombinedDtcType, AUTOMATIC,  DEM_VAR) LddCbDTC = NULL_PTR;
  uint16 LucDtcLoc;
  uint32 LulDtcVal;
  uint32 LulTmpDTC = DTC;
    /* @Trace: Dem_SUD_API_20943 */
  if ((DEM_DTC_FORMAT_OBD == DTCFormat) &&
      ((DEM_DTC_GROUP_ALL_DTCS != DTC) &&
       (DEM_DTC_GROUP_EMISSION_REL_DTCS_WWH_OBD != DTC)))
  {
    /* @Trace: Dem_SUD_API_20942 */
    LulTmpDTC = DTC >> DEM_EIGHT;
  }
  /* @Trace: Dem_SUD_API_20036 */
  /* @Trace: Dem_SUD_API_20938 */
  for (LucDtcLoc = 0U; LucDtcLoc < DEM_MAX_NUMBER_OF_DTC; LucDtcLoc++)
  {     
    /* @Trace: Dem_SUD_API_20939 */
    #if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
    /* Trace: DEM_19792_42_01*/
    /* @Trace: Dem_SUD_API_20940 */
    if (Dem_GaaCombinedDtc[LucDtcLoc].ddDtcFormat != DEM_DTC_FORMAT_UDS)        
    {
      if (DEM_DTC_FORMAT_OBD == DTCFormat)
      {
        /* Making DTC lowByte to zero for OBD DTC */
        /*LulDtcVal = Dem_GaaCombinedDtc[LucDtcLoc].usObdDtc << 8U ;*/
        /* @Trace: Dem_SUD_API_20941 */
        LulDtcVal = Dem_GaaCombinedDtc[LucDtcLoc].usObdDtc;
      }
	  #if (DEM_J1979_2_OBD_ON_UDS == STD_ON)
      else if(DEM_DTC_FORMAT_OBD_3BYTE == DTCFormat)
      {
        /* DemSupportedobdUdsDtcSeparation is need to supported */
        
        if (Dem_ObdUdsDtc_Separation_Support ==  STD_ON)
        {
          LulDtcVal = Dem_GaaCombinedDtc[LucDtcLoc].ulObdDtc3Byte; 
        }
        else
        
        {
          LulDtcVal = Dem_GaaCombinedDtc[LucDtcLoc].ulUdsDtc;          
        }
      }
	  #endif /* J19792 */
      else
      {
         LulDtcVal = Dem_GaaCombinedDtc[LucDtcLoc].ulUdsDtc;
      }
    }
    else
    #endif    
    {
      LulDtcVal = Dem_GaaCombinedDtc[LucDtcLoc].ulUdsDtc;
    }
    /* @Trace: Dem_SUD_API_20937 */
    if (LulDtcVal == LulTmpDTC)
    {
      /* @Trace: Dem_SUD_API_20936 */
      LddCbDTC = &Dem_GaaCombinedDtc[LucDtcLoc];
    }
  }
  
  return LddCbDTC;
}

static DEM_INLINE FUNC(Dem_NumOfEventIdType, DEM_CODE)
  Dem_GetStartEventIdMapOfCbDTC(Dem_CombinedDtcPCType CombinedDTC)
{
  /* @Trace: Dem_SUD_API_20944 */
  return CombinedDTC->dtc_PointToEventList;
}

static DEM_INLINE FUNC(Dem_EventIdType, DEM_CODE)
  Dem_GetEventIdByEventIdMapOfCbDTC(Dem_NumOfEventIdType EventIdMapIdx)
{
  /* @Trace: Dem_SUD_API_20945 */
  return Dem_ListOfCombinedEvents[EventIdMapIdx];
}

static DEM_INLINE FUNC(Dem_NumOfEventIdType, DEM_CODE)
  Dem_GetEndEventIdMapOfCbDTC(Dem_CombinedDtcPCType CombinedDTC)
{
  Dem_NumOfEventIdType LddEndPos =
      CombinedDTC->dtc_PointToEventList + CombinedDTC->ddNumberOfEvents;
  /* @Trace: Dem_SUD_API_20946 */
  if (LddEndPos > DEM_MAX_LISTOFCOMBINEDEVENTS)
  /* polyspace<RTE:UNR:Not a defect:No action planned>
   * The block is only partially unreachable. */
  {
    /* @Trace: Dem_SUD_API_20037 */
    LddEndPos = DEM_ZERO;
  }
  return LddEndPos;
}

static DEM_INLINE FUNC(Dem_DTCType, DEM_CODE) Dem_GetDtcByCombineDTC(
  P2CONST(Dem_CombinedDtcType, AUTOMATIC, DEM_CONST) CbDTC)
{
  Dem_DTCType LddDTC;
  /* @Trace: Dem_SUD_API_20947 */
  #if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
  if (CbDTC->ddDtcFormat != DEM_DTC_FORMAT_UDS)
  {
    #if (DEM_J1979_2_OBD_ON_UDS == STD_ON)
    /* Trace: DEM_19792_42_01 */
    if (CbDTC->ddDtcFormat == DEM_DTC_FORMAT_OBD_3BYTE)
    {
      /* DemSupportedobdUdsDtcSeparation is need to supported */         
      if (Dem_ObdUdsDtc_Separation_Support == STD_ON)
      {
        LddDTC = CbDTC->ulObdDtc3Byte;
      }
      else
      {
        LddDTC = CbDTC->ulUdsDtc;
      }
    }
    else if ( CbDTC->ulUdsDtc != DEM_ZERO )
    {
      LddDTC = CbDTC->ulUdsDtc;
    }
    else
    #endif /* J19792 */
    {
      /* @Trace: Dem_SUD_API_20949 */
      /* Making DTC lowByte to zero for OBD DTC */
      LddDTC = (uint32)CbDTC->usObdDtc << DEM_EIGHT ;
    }
  }
  else
  /* @Trace: Dem_SUD_API_20948 */
  #endif
  {
    LddDTC = CbDTC->ulUdsDtc;
  }

  return LddDTC;
}

/* polyspace:end<MISRA-C:8.5:Not a defect:No action planned>
 * inline-MISRA C:2012 permits the use of inline functions in header files */
/* polyspace:end<MISRA-C:8.1:Not a defect:No action planned>
 * inline-MISRA C:2012 permits the use of inline functions in header files */
/* polyspace:end<MISRA-C:1.1:Not a defect:No action planned>
 * inline-MISRA C:2012 permits the use of inline functions in header files */

#define DEM_STOP_SEC_CODE
#include "MemMap.h"

#endif /* DEM_DTC_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/


