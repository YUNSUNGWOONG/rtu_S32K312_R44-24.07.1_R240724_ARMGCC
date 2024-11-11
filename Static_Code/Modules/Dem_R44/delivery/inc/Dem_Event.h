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
**  SRC-MODULE: Dem_Event.h                                                   **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostic Event Manager                              **
**                                                                            **
**  PURPOSE   : C header for Dem_Event.c                                      **
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
** 1.0.1.0   07-May-2021   HaoLT6        R44-Redmine #18724                   **
** 1.0.0     26-Feb-2021   EK Kim        Initial version                      **
*******************************************************************************/

#ifndef DEM_EVENT_H
#define DEM_EVENT_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Dem_PCTypes.h"
#include "SchM_Dem.h"

#define DEM_START_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
**                  Extern Function Definition                                **
*******************************************************************************/

extern FUNC(Std_ReturnType, DEM_CODE) 
Dem_GetEventConditionsAndControlDTCSetting(Dem_EventIdType EventId);


extern FUNC(Std_ReturnType, DEM_CODE) Dem_ProcessEventStatus(
  Dem_EventIdType EventId, Dem_EventStatusType EvStatus);

#if (DEM_BSW_ERROR_BUFFER_SIZE > DEM_ZERO)
extern FUNC(void, DEM_CODE) Dem_MainfunctionBswEvents(void);
#endif

extern FUNC(void, DEM_CODE) Dem_MainfunctionEvents(void);

extern FUNC(Std_ReturnType, DEM_CODE) Dem_GetEventDTCOrigin(
  Dem_EventParameterCPCType event,
  P2VAR(Dem_DTCOriginType, AUTOMATIC, DEM_VAR) DTCOrigin
  /*,P2VAR(boolean, AUTOMATIC, DEM_VAR) MirrorExist */);    


extern FUNC(boolean, DEM_CODE) Dem_DTCOriginBelongToEvent(
  Dem_EventIdType EventId,
  Dem_DTCOriginType DTCOrigin);

extern FUNC(Std_ReturnType, DEM_CODE) Dem_GetOpCycleStateByEvent(
  Dem_EventIdType EventId,
  P2VAR(Dem_OperationCycleStateType, AUTOMATIC, DEM_VAR) CycleState);  

extern FUNC(Dem_TestResultType, DEM_CODE) Dem_GetTestResultThisOperation(
  Dem_UdsStatusByteType EventStatusByte,
  boolean RequireTestedCycle);

extern FUNC(void, DEM_CODE) Dem_ProcessUDSStatus(void);

extern FUNC(void, DEM_CODE) Dem_ProcessWIRStatus(void);

#if (DEM_SIZE_OF_EVENT_DATA > DEM_ZERO)
extern FUNC(void, DEM_CODE) Dem_ProcessCaptureDataRelated(
  Dem_EventIdType EventId,
  Dem_EventStatusType EventStatus,
  uint8 EnvDataCapture);
#endif

#if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
#if (DEM_MAX_NUMBER_EVENT_ENTRY_EVENT_BUFFER > DEM_ZERO)
extern FUNC(void, DEM_CODE) Dem_SortedEventsByWWHOBDTCClass(void);
#endif
#endif

extern FUNC(Std_ReturnType, DEM_CODE) Dem_GetEventDTC(
  Dem_EventParameterCPCType event,
  P2VAR(Dem_DTCType, AUTOMATIC, DEM_APPL_DATA) DTC,
  Dem_DTCFormatType DTCFormat);

extern FUNC(Dem_EventIdType, DEM_CODE) Dem_GetEventIdByDTC(
    uint8 ApiId,
    const Dem_DTCType DTC,
    const Dem_DTCFormatType DTCFormat);

extern FUNC(void, DEM_CODE) Dem_InitBswEventQueue(void);

extern FUNC(void, DEM_CODE) Dem_InitEventQueue(void);

#if (DEM_MAX_DEM_MULTI_EVENT_TRIGGERING > DEM_ZERO)
extern FUNC(uint8, DEM_CODE) Dem_GetIndexOfMasterEventByEventId
  (Dem_EventIdType EventId);
#endif

#if (DEM_ENABLE_CONDITION_SUPPORT == STD_ON)
extern FUNC(Std_ReturnType, DEM_CODE) Dem_GetEventEnableConditionState(
    Dem_EventIdType EventId);
#endif

#if (DEM_STORAGE_CONDITION_SUPPORT == STD_ON)
extern FUNC(Std_ReturnType, DEM_CODE) Dem_GetEventStorageConditionState(
    Dem_EventIdType EventId);
#endif
/*******************************************************************************
**                  Inline Function Definition                                **
*******************************************************************************/
/* polyspace:begin<MISRA-C:1.1:Not a defect:No action planned>
 * inline-MISRA C:2012 permits the use of inline functions in header files */
/* polyspace:begin<MISRA-C:8.1:Not a defect:No action planned>
 * inline-MISRA C:2012 permits the use of inline functions in header files */
/* polyspace:begin<MISRA-C:8.5:Not a defect:No action planned>
 * inline-MISRA C:2012 permits the use of inline functions in header files */

static DEM_INLINE FUNC(boolean, DEM_CODE) Dem_EventIdIsValid(
    Dem_EventIdType EventId)
{
  boolean LblValid;
  if ((EventId <= DEM_NUMBER_OF_EVENTS) && (DEM_NO_EVENT != EventId))
  {
    /* @Trace: Dem_SUD_API_20610 */
    LblValid = DEM_TRUE;
  }
  else
  /* polyspace<RTE:UNR:Not a defect:No action planned> If-condition evaluates
   * to true or false according to configuration */
  {
    /* @Trace: Dem_SUD_API_20007 */
    LblValid = DEM_FALSE;
  }
  return LblValid;
}

static DEM_INLINE FUNC(DemEventKindType, DEM_CODE) Dem_GetEventKind(
    Dem_EventIdType EventId)
{
  /* @Trace: Dem_SUD_API_20611 */
  return DEM_GET_EVENTPARAM_EVENT_KIND(
      Dem_Event[EventId - DEM_ONE].ParamFieldsA);
}
/* @Trace: Dem_SUD_MACRO_032 */
static DEM_INLINE FUNC(boolean, DEM_CODE) Dem_EventStatusIsValid(
    Dem_EventStatusType EventStatus)
{ 
  boolean LblValid;
  if (
      ((EventStatus == (Dem_EventStatusType)DEM_EVENT_STATUS_PASSED) ||
       (EventStatus == (Dem_EventStatusType)DEM_EVENT_STATUS_FAILED))||
      ((EventStatus == (Dem_EventStatusType)DEM_EVENT_STATUS_PREPASSED) ||
       (EventStatus == (Dem_EventStatusType)DEM_EVENT_STATUS_PREFAILED) ||
       (EventStatus == (Dem_EventStatusType)
           DEM_EVENT_STATUS_FDC_THRESHOLD_REACHED))
  )
  {
    /* @Trace: Dem_SUD_API_20612 */
    LblValid = DEM_TRUE;
  }
  else
  {
    /* @Trace: Dem_SUD_API_20008 */
    LblValid = DEM_FALSE;
  }

  return LblValid;
}

static DEM_INLINE FUNC(uint16, DEM_CODE)  Dem_SetBit16(uint16 Val,
    uint8 Position)
{
  /* @Trace: Dem_SUD_API_20613 */
  uint16 LusMask = (uint16)DEM_ONE << Position;
  return Val | LusMask;
}
static DEM_INLINE FUNC(uint16, DEM_CODE)  Dem_ClearBit16(uint16 Val,
    uint8 Position)
{
  /* @Trace: Dem_SUD_API_20614 */
  uint16 LusMask = (uint16)DEM_ONE << Position;
  return Val & ((uint16)~LusMask);
}
static DEM_INLINE FUNC(boolean, DEM_CODE)  Dem_IsBit16Set(uint16 Val,
    uint8 Position)
{
  boolean LblIsSet;
  uint16 LusValSet = Val;
  /* polyspace<MISRA-C:21.1:Not a defect:Justify with annotations  a defect>
   * Rule violation by runtime error(orange) of PolySpace */
  LusValSet = (uint16)(LusValSet >> Position);
  if ((uint16)(LusValSet & (uint16)DEM_ONE) != (uint16)DEM_ZERO)
  {
    /* @Trace: Dem_SUD_API_20615 */
    LblIsSet = DEM_TRUE;
  }
  else
  {
    /* @Trace: Dem_SUD_API_20616 */
    LblIsSet = DEM_FALSE;
  }
  return LblIsSet;
}
static DEM_INLINE FUNC(uint8, DEM_CODE)  Dem_SetBit8(uint8 Val,
    uint8 Position)
{
  /* @Trace: Dem_SUD_API_20617 */
  uint8 LusMask = (uint8)(DEM_ONE << Position);
  return Val | LusMask;
}

static DEM_INLINE FUNC(uint8, DEM_CODE)  Dem_ClearBit8(uint8 Val,
    uint8 Position)
{
  /* @Trace: Dem_SUD_API_20618 */
  uint8 LusMask = (uint8)(DEM_ONE << Position);
  return Val & ((uint8)~LusMask);
}

static DEM_INLINE FUNC(boolean, DEM_CODE)  Dem_IsBit8Set(uint8 Val,
    uint8 Position)
{
  boolean LblIsSet;
  uint8 LucValSet = Val;
  /* polyspace<MISRA-C:21.1:Not a defect:Justify with annotations  a defect>
   * Rule violation by runtime error(orange) of PolySpace */
  LucValSet = (uint8)(LucValSet >> Position);
  if ((uint8)(LucValSet & (uint8)DEM_ONE) != (uint8)DEM_ZERO)
  {
    /* @Trace: Dem_SUD_API_20620 */
    LblIsSet = DEM_TRUE;
  }
  else
  {
    /* @Trace: Dem_SUD_API_20619 */
    LblIsSet = DEM_FALSE;
  }
  return LblIsSet;
}
/*
* +---------+---------+---------+---------+---------+---------+---------+---------+
* |    15   |    14   |    13   |    12   |    11   |    10   |    9    |    8    |
* +---------+---------+---------+---------+---------+---------+---------+---------+
* | Reserve | Reserve | Reserve | Reserve | Reserve | Reserve | Reserve | Reserve |
* |         |         |         |         |         |         |         |         |
* +---------+---------+---------+---------+---------+---------+---------+---------+
* |    7    |    6    |    5    |    4    |    3    |    2    |    1    |    0    |
* +---------+---------+---------+---------+---------+---------+---------+---------+
* |J1939ExFF|J1939 Dtc|  Delete |   Lock  |  Stored |  Filter | Suppress|         |
* |  Filter |  Filter |         |         |         |         |         |         |
* +---------+---------+---------+---------+---------+---------+---------+---------+
*/

static DEM_INLINE FUNC(void, DEM_CODE) Dem_EvSetProcState(
    Dem_EventIdType EventId, uint8 ProcessState)
{
  /* @Trace: Dem_SUD_API_20621 */
  uint8 LucProcessState = ProcessState;
  Dem_EventState[EventId] = (uint16)Dem_SetBit16(
      (uint16)Dem_EventState[EventId],
      (uint8)LucProcessState);
}

static DEM_INLINE FUNC(void, DEM_CODE) Dem_EvSetUdsProcState(
    Dem_EventIdType EventId, uint8 ProcessState)
{
  /* @Trace: Dem_SUD_API_20638 */
  uint8 LucProcessState = ProcessState;
  LucProcessState = LucProcessState - DEM_SIXTEEN;
  Dem_UDSProcsessState[EventId] = (uint8)Dem_SetBit8(
      (uint8)Dem_UDSProcsessState[EventId],
      (uint8)LucProcessState);
}

static DEM_INLINE FUNC(boolean, DEM_CODE) Dem_EvIsProcStateTriggered(
    Dem_EventIdType EventId, uint8 ProcessState)
{
  boolean LblReVal = DEM_FALSE;
  uint8 LucProcessState = ProcessState;
  /* @Trace: Dem_SUD_API_20623 */
  if ((EventId <= DEM_NUMBER_OF_EVENTS) && (DEM_NO_EVENT != EventId))
  {
    /* @Trace: Dem_SUD_API_20622 */
    LblReVal = Dem_IsBit16Set((uint16)Dem_EventState[EventId],
        (uint8)LucProcessState);
  }
  return LblReVal;
}

static DEM_INLINE FUNC(boolean, DEM_CODE) Dem_EvIsUdsProcStateTriggered(
    Dem_EventIdType EventId, uint8 ProcessState)
{
  boolean LblReVal = DEM_FALSE;
  uint8 LucProcessState = ProcessState;
  /* @Trace: Dem_SUD_API_20640 */
  if ((EventId <= DEM_NUMBER_OF_EVENTS) && (DEM_NO_EVENT != EventId))
  {
    /* @Trace: Dem_SUD_API_20639 */
    LucProcessState = LucProcessState - DEM_SIXTEEN;
    LblReVal = Dem_IsBit8Set((uint8)Dem_UDSProcsessState[EventId],
        (uint8)LucProcessState);
  }
  return LblReVal;
}

static DEM_INLINE FUNC(void, DEM_CODE) Dem_EvClearProcState(
    Dem_EventIdType EventId, uint8 ProcessState)
{
  uint8 LucProcessState = ProcessState;
  /* @Trace: Dem_SUD_API_20009 */
  if ((EventId <= DEM_NUMBER_OF_EVENTS) && (DEM_NO_EVENT != EventId))
  {
    /* @Trace: Dem_SUD_API_20624 */
    Dem_EventState[EventId] = (uint16)Dem_ClearBit16(
        (uint16)Dem_EventState[EventId],
        (uint8)LucProcessState);
  }
}

static DEM_INLINE FUNC(void, DEM_CODE) Dem_EvClearUdsProcState(
    Dem_EventIdType EventId, uint8 ProcessState)
{
  uint8 LucProcessState = ProcessState;
  /* @Trace: Dem_SUD_API_20642 */
  if ((EventId <= DEM_NUMBER_OF_EVENTS) && (DEM_NO_EVENT != EventId))
  {
    /* @Trace: Dem_SUD_API_20641 */
    LucProcessState = LucProcessState - DEM_SIXTEEN;
    Dem_UDSProcsessState[EventId] = (uint8)Dem_ClearBit8(
        (uint8)Dem_UDSProcsessState[EventId],
        (uint8)LucProcessState);
  }
}

static DEM_INLINE FUNC(void, DEM_CODE) Dem_EvInitProcState(
    Dem_EventIdType EventId)
{
  /*Initialize for state as:
   * Bit No.8 (DemAvailable) to TRUE ==> 1
   * */
  /* @Trace: Dem_SUD_API_20625 */
  Dem_EventState[EventId] = 0x0100U;
  Dem_UDSProcsessState[EventId] = 0x00U;
}

static DEM_INLINE FUNC(Dem_EventIdType, DEM_CODE) Dem_GetFirstEventOfDTC(
    Dem_CombinedDtcPCType DTCClass)
{
  Dem_EventIdType LddFirstEventId = DEM_NO_EVENT;
  /* polyspace<RTE:UNR:Not a defect:No action planned>
   * If-condition always evaluates to true */
  /* @Trace: Dem_SUD_API_20627 */
  if (DTCClass->dtc_PointToEventList < DEM_MAX_LISTOFCOMBINEDEVENTS)
  {
    Dem_EventIdType LddEventId =
        Dem_ListOfCombinedEvents[DTCClass->dtc_PointToEventList];
    /* polyspace<RTE:UNR:Not a defect:No action planned>
     * If-condition always evaluates to true */
    /* @Trace: Dem_SUD_API_20628 */
    if ((boolean)DEM_TRUE == Dem_EventIdIsValid(LddEventId))
    {
      /* @Trace: Dem_SUD_API_20626 */
      LddFirstEventId = LddEventId;
    }
  }

  return LddFirstEventId;
}

static DEM_INLINE FUNC(boolean, DEM_CODE) Dem_EventHasDtc(
    Dem_EventIdType EventId)
{
  boolean LblValid;
  if (Dem_Event[EventId - DEM_ONE].e_PointToDTC < DEM_MAX_NUMBER_OF_DTC)
  {
    /* @Trace: Dem_SUD_API_20629 */
    LblValid = DEM_TRUE;
  }
  else
  {
    /* @Trace: Dem_SUD_API_20010 */
    LblValid = DEM_FALSE;
  }
  return LblValid;
}

static DEM_INLINE FUNC(boolean, DEM_CODE) Dem_GetLockByEventId(
  const Dem_EventIdType EventId)
{
  boolean LblLock;

  SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();
  if ((boolean)DEM_TRUE == Dem_EvIsProcStateTriggered(
      EventId, DEM_EVPROCSTATE_EVENT_LOCK))
  { 
    /* @Trace: Dem_SUD_API_20011 */
    LblLock = DEM_FALSE;
  }
  else
  {
    /* @Trace: Dem_SUD_API_20630 */
    LblLock = DEM_TRUE;
    Dem_EvSetProcState(EventId, DEM_EVPROCSTATE_EVENT_LOCK);   
  }
  
  SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();  

  return LblLock;
}

static DEM_INLINE FUNC(boolean, DEM_CODE) Dem_GetLocksByEventIdAndEvMem(
    const Dem_EventIdType EventId)
{
  boolean LblLock = DEM_FALSE;

  SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();
  /* @Trace: Dem_SUD_API_20631 */
  #if (DEM_NUMBER_OF_DEM_CLIENT > DEM_ZERO)
  if (DEM_NO_EVMEM_IDX == Dem_Event[EventId - DEM_ONE].ucEventMemDstIdx)
  {
    /* @Trace: Dem_SUD_API_20632 */
    LblLock = DEM_TRUE;
    Dem_EvSetProcState(EventId, DEM_EVPROCSTATE_EVENT_LOCK);
  }
  else
  {
    /* @Trace: Dem_SUD_API_20633 */
    /* @Trace: Dem_SUD_API_20634 */
    for (uint8 ClientId = DEM_ZERO;
         ClientId < DEM_NUMBER_OF_DEM_CLIENT;
         ClientId++)
    {
      /* @Trace: Dem_SUD_API_20635 */
      if ((Dem_Client[ClientId].usDemEventMemorySetId ==
           Dem_Event[EventId - DEM_ONE].ucEventMemDstIdx))
      {
        /* @Trace: Dem_SUD_API_20013 */
        if (DEM_CLEARDTC_STATE_READY == Dem_ClearDtcState[ClientId].cds_State)
        {
          if ((boolean)DEM_TRUE ==
              Dem_EvIsProcStateTriggered(EventId, DEM_EVPROCSTATE_EVENT_LOCK))
          {
            /* @Trace: Dem_SUD_API_20012 */
            LblLock = DEM_FALSE;
            break;
          }
          else
          {
            /* @Trace: Dem_SUD_API_20636 */
            LblLock = DEM_TRUE;
            Dem_EvSetProcState(EventId, DEM_EVPROCSTATE_EVENT_LOCK);
          }
        }
        else
        {
          LblLock = DEM_FALSE;
        }
      }
    }
  }

  #endif
  
  SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();  

  return LblLock;
}


static DEM_INLINE FUNC(void, DEM_CODE) Dem_FreeLockByEventId(
  const Dem_EventIdType EventId)
{
  /* @Trace: Dem_SUD_API_20637 */
  SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();
  Dem_EvClearProcState(EventId, DEM_EVPROCSTATE_EVENT_LOCK);      
  SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();  
}
/* polyspace:end<MISRA-C:8.5:Not a defect:No action planned>
 * inline-MISRA C:2012 permits the use of inline functions in header files */
/* polyspace:end<MISRA-C:8.1:Not a defect:No action planned>
 * inline-MISRA C:2012 permits the use of inline functions in header files */
/* polyspace:end<MISRA-C:1.1:Not a defect:No action planned>
 * inline-MISRA C:2012 permits the use of inline functions in header files */


/**************************************************/
#define DEM_STOP_SEC_CODE
#include "MemMap.h"
/*************************************************/

#endif

     

