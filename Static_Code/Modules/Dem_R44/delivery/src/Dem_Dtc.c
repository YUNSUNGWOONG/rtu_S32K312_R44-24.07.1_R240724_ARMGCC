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
**  SRC-MODULE: Dem_Dtc.c                                                     **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostics Event Manager Module                      **
**                                                                            **
**  PURPOSE   : Provides the interface of varialble data that ara configurable**
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: No                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: No                                        **
**                                                                            **
*******************************************************************************/
/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By            Description                          **
********************************************************************************
** 2.0.0.0   31-Dec-2023   EK Kim        Jira #CP44-1515 #CP44-3198 #CP44-3298**
** 1.0.8.0   13-Dec-2021   SY Kim        Jira #CP44-1169 #CP44-1295           **
** 1.0.1.0   07-May-2021   HaoLT6        R44-Redmine #18724                   **
** 1.0.0     26-Feb-2021   EK Kim        Initial version                      **
*******************************************************************************/

 
/* polyspace:begin<MISRA-C:1.1:Not a defect:No action planned> Not a defect  */
 

/*******************************************************************************
**                     Include Section                                       **
*******************************************************************************/
#include "Dem.h"        /* DEM module Header File */
#include "Dem_Ram.h"    /* DEM Ram Header File */

/* DEM_DEV_ERROR_DETECT is defined in Dem_Cfg.h
 * Dem_Cfg.h is included by Dem.h */
#if (DEM_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"        /* Det Module Header File */
#endif

#include "SchM_Dem.h"   /* Basic s/w module Scheduler symbols Header File */ 
#include "Rte_Dem.h"
#include "Dem_Event.h"
#include "Dem_EventCallback.h"
#include "Dem_EventMemory.h"
#include "Dem_EventDebounce.h"
#include "Dem_Indicator.h"
#include "Dem_Dtc.h"

/* Trace: DEM_19792_1A_04 */
#include "Dem_EventRelatedData.h"

#define DEM_START_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
 ** Function Name       : Dem_DTCGroupIsValid                                 **
 **                                                                           **
 ** Service ID          : None                                                **
 **                                                                           **
 ** Description         : This internal function whether Group DTC input is   **
 **                       valid or not                                        **
 **                                                                           **
 ** Sync/Async          : Asynchronous                                        **
 **                                                                           **
 ** Re-entrancy         : Non-Reentrant                                       **
 **                                                                           **
 ** Input Parameters    : DTCGroup, DTCFormat                                 **
 **                                                                           **
 ** InOut parameter     : None                                                **
 **                                                                           **
 ** Output Parameters   : None                                                **
 **                                                                           **
 ** Return parameter    : Std_ReturnType                                      **
 **                                                                           **
 ** Preconditions       : None                                                **
 **                                                                           **
 ** Remarks             :                                                     **
 *******************************************************************************/
/* @Trace: SRS_Diag_04000
 */
/* @Trace: Dem_SUD_MACRO_041 */
FUNC(Std_ReturnType, DEM_CODE)
Dem_DTCGroupIsValid(const Dem_DTCGroupType DTCGroup,
    const Dem_DTCFormatType DTCFormat)
{
  Std_ReturnType LddRetVal = E_NOT_OK;
  Dem_DTCGroupType LddTmpDtcGroup = DTCGroup;

  if (( DEM_DTC_FORMAT_OBD == DTCFormat ) &&
     (( DEM_DTC_GROUP_ALL_DTCS != DTCGroup) &&
      ( DEM_DTC_GROUP_EMISSION_REL_DTCS_WWH_OBD != DTCGroup)))
  {
    /* @Trace: Dem_SUD_API_11493 */
    LddTmpDtcGroup = LddTmpDtcGroup >> DEM_EIGHT;
  }
  else
  {
    /* @Trace: Dem_SUD_API_11492 */
    /* Do nothing*/
  }

  if (( DEM_DTC_GROUP_ALL_DTCS == LddTmpDtcGroup) ||
      ( DEM_DTC_GROUP_EMISSION_REL_DTCS_WWH_OBD == LddTmpDtcGroup) )
  {
    /* @Trace: Dem_SUD_API_10735 */
    LddRetVal = E_OK;
  }
  else
  {
    /* @Trace: Dem_SUD_API_11494 */
    #if (DEM_MAX_NUM_GRP_DTC > DEM_ZERO)
    uint8 LucDtcGroupId;
    /* @Trace: Dem_SUD_API_11497 */
    for (LucDtcGroupId = DEM_ZERO;
         LucDtcGroupId < Dem_Max_Num_Grp_DTC;
         LucDtcGroupId++)
    {
      /* @Trace: Dem_SUD_API_11495 */
      if (Dem_GaaGroupDTC[LucDtcGroupId] == LddTmpDtcGroup)
      {
        /* @Trace: Dem_SUD_API_11496 */
        LddRetVal = E_OK;
        break;
      }
    }
    #endif
  }

  return LddRetVal;
}

/*******************************************************************************
** Function Name        : Dem_InitProtectedRecord                             **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Init Record Disable DTC for all client id.          **
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
** Remarks              : None                                                **
*******************************************************************************/
#if (DEM_NUMBER_OF_DEM_CLIENT > DEM_ZERO)
FUNC(void, DEM_CODE)  Dem_InitProtectedRecord(void)
{
  uint8 LucClientId;
  /* @Trace: Dem_SUD_API_11500 */
  for (LucClientId = 0; LucClientId < DEM_NUMBER_OF_DEM_CLIENT; LucClientId++)
  {
    #if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
    /* @Trace: Dem_SUD_API_11498 */
    Dem_GstRecordDisableDTC[LucClientId].usObdDtc = DEM_ZERO;
    Dem_GstRecordDisableDTC[LucClientId].ulUdsDtc = DEM_ZERO;
    #else
    /* @Trace: Dem_SUD_API_11499 */
    Dem_GstRecordDisableDTC[LucClientId].ulUdsDtc = DEM_ZERO;
    #endif
  }
}
#endif

/******************************************************************************
 * Function Name        : Dem_GetConditionOfDTCRecordUpdate 
 *
 * Service ID           : None
 *
 ** Description         : It is used to get the condition of a DTC 
 **                       record update
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Reentrant
 *
 * Input Parameters     : ClientId, DTC
 *
 * InOut parameter      : None
 *
 * Output Parameters    : None
 *
 * Return parameter     : Dem_ReturnConditionOfDTCRecordUpdateType
 *
 * Preconditions        : None
 *
 * Remarks              : Global Variable(s)   :
 *
 *                        Function(s) invoked  :
 *
 ******************************************************************************/
/* @Trace: Dem_SUD_MACRO_043 */
#if (DEM_NUMBER_OF_DEM_CLIENT > DEM_ZERO)
FUNC(Dem_ReturnConditionOfDTCRecordUpdateType, DEM_CODE)
Dem_GetConditionOfDTCRecordUpdate(
  uint8 ClientId,
  const Dem_DTCType DTC)
{
  Dem_ReturnConditionOfDTCRecordUpdateType LddRetVal =
      DEM_CONDITIONDTCRECUP_NO_DTC;

  /* Check already a record is disabled */
  #if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
  /* @Trace: Dem_SUD_API_10736 */
  if ((Dem_GstRecordDisableDTC[ClientId].usObdDtc != DEM_ZERO) ||
      (Dem_GstRecordDisableDTC[ClientId].ulUdsDtc != DEM_ZERO))
  #else
  /* @Trace: Dem_SUD_API_11503 */
  /* @Trace: Dem_SUD_API_11502 */
  if  (Dem_GstRecordDisableDTC[ClientId].ulUdsDtc != DEM_ZERO)
  #endif
  {
    /* @Trace: Dem_SUD_API_11504 */
    #if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
    if (((Dem_GstRecordDisableDTC[ClientId].usObdDtc == DTC) ||
        (Dem_GstRecordDisableDTC[ClientId].ulUdsDtc == DTC))
    #else
    /* @Trace: Dem_SUD_API_11501 */
    if ((Dem_GstRecordDisableDTC[ClientId].ulUdsDtc == DTC)
    #endif
      )
    {
      /* @Trace: Dem_SUD_API_10737 */
      LddRetVal = DEM_CONDITIONDTCRECUP_DISABLED_DTC;
    }
    else
    {
      /* @Trace: Dem_SUD_API_10738 */
      LddRetVal = DEM_CONDITIONDTCRECUP_NO_MATCHING_DTC;
    }
  }
  return LddRetVal;
}
#endif

/******************************************************************************
 * Function Name        : Dem_GetStatusOfDTCRecordUpdate
 *
 * Service ID           : None
 *
 ** Description         : It is used to get status of DTC record update
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Reentrant
 *
 * Input Parameters     : EventId
 *
 * InOut parameter      : None
 *
 * Output Parameters    : None
 *
 * Return parameter     : Std_ReturnType(E_OK or E_NOT_OK)
 *
 * Preconditions        : None
 *
 * Remarks              : Global Variable(s)  :
 *
 *                        Function(s) invoked :
 *
 ******************************************************************************/
#if (DEM_NUMBER_OF_DEM_CLIENT > DEM_ZERO)
FUNC(Std_ReturnType, DEM_CODE)
Dem_GetStatusOfDTCRecordUpdate(
  Dem_EventIdType EventId)
{
  Std_ReturnType LddRetVal = E_OK;
  Dem_CombinedDtcPCType LddCbDTC = Dem_GetCbDTCByEventId(EventId);
  /* @Trace: Dem_SUD_API_11505 */
  for (uint8 LucClientId = DEM_ZERO;
       LucClientId < DEM_NUMBER_OF_DEM_CLIENT;
       LucClientId++)
  {
    /* @Trace: Dem_SUD_API_10740 */
    if (NULL_PTR != LddCbDTC)
    {
      /* @Trace: Dem_SUD_API_11506 */
      if ((( DEM_NO_DTC != LddCbDTC->ulUdsDtc) &&
           (LddCbDTC->ulUdsDtc ==
             Dem_GstRecordDisableDTC[LucClientId].ulUdsDtc))
          #if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
          || (( DEM_NO_DTC != LddCbDTC->usObdDtc ) &&
          (LddCbDTC->usObdDtc == Dem_GstRecordDisableDTC[LucClientId].usObdDtc))
          #endif
          )
      {
        /* @Trace: Dem_SUD_API_10739 */
        LddRetVal = E_NOT_OK;
        break;
      }
    }
  }
  return LddRetVal;
}
#endif

/*******************************************************************************
 ** Function Name       : Dem_CountAndStoreFilterDtc                          **
 **                                                                           **
 ** Service ID          : None                                                **
 **                                                                           **
 ** Description         : Counts and store the filtered dtc as per request by **
 **                       Dcm                                                 **
 **                                                                           **
 ** Sync/Async          : Synchronous                                         **
 **                                                                           **
 ** Re-entrancy         : Reentrant                                           **
 **                                                                           **
 ** Input Parameters    : ClientId                                            **
 **                                                                           **
 ** InOut parameter     : None                                                **
 **                                                                           **
 ** Output Parameters   : None                                                **
 **                                                                           **
 ** Return parameter    : Void                                                **
 **                                                                           **
 ** Preconditions       : None                                                **
 **                                                                           **
 ** Remarks             :                                                     **
 ******************************************************************************/
/* @Trace: SRS_Diag_04205 SRS_Diag_04164
 */
/* polyspace +1 CODE-METRICS:PATH [Not a defect:Low] "Not a defect" */
FUNC(void, DEM_CODE) Dem_CountAndStoreFilterDtc(uint8 ClientId)
{
  /* @Trace: Dem_SUD_API_11507 */
  #if (DEM_MAX_EVENT_DESTINATION_SELECTED > DEM_ZERO)

  Dem_NumOfDTCValueType LddDtcLoc = DEM_ZERO;
  Std_ReturnType LddResult = E_NOT_OK;

  /* Loop can be cancelled by Dem_DcmCancelOperation
   * (done DEM_JOB_RUNNING->DEM_JOB_CANCEL)*/
  /* @Trace: Dem_SUD_API_11525 */
  for ( LddDtcLoc = DEM_ZERO;
      ( LddDtcLoc < DEM_MAX_NUMBER_OF_DTC) &&
      ( Dem_DTCFilterState[ClientId].dfs_JobAction == DEM_JOB_RUNNING);
        LddDtcLoc++)
  {
    P2CONST(Dem_CombinedDtcType, AUTOMATIC, DEM_APPL_CONST) LddCbDTC =
            &Dem_GaaCombinedDtc[LddDtcLoc];
    Dem_EventIdType LddEventId = Dem_GetFirstEventOfDTC(LddCbDTC);
    /* polyspace<RTE:UNR:Not a defect:No action planned> If-condition always
     * evaluates to true. Avoid to 'Unreachable code' of the polyspace */
    /* @Trace: Dem_SUD_API_11518 */
    if ((DEM_NO_EVENT != LddEventId)
    #if (DEM_NUMBER_OF_DEM_CLIENT > DEM_ZERO)
    && ( Dem_Event[LddEventId - DEM_ONE].ucEventMemDstIdx ==
         Dem_Client[ClientId].usDemEventMemorySetId)
    #endif
       )
    {
      /* DTCSuppressionStatus: Don't worry aboue combination type 1, type2
       * Refer to Dem_SetDTCSuppression 
       * E_OK means 'DTCSuppression == false' */

      /* polyspace<RTE:UNR:Not a defect:No action planned> Unreachable code'
       * according to DTCSuppression configuration */
      /* @Trace: Dem_SUD_API_10744 */
      if (DEM_FALSE == Dem_EvIsProcStateTriggered(LddEventId,
            DEM_EVPROCSTATE_DTC_SUPP))
      {
        Dem_UdsStatusByteType LddDtcStatusByte = Dem_GetDTCStatus(LddEventId);
        /* @Trace: Dem_SUD_API_11526 */
        #if (( DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT) && \
             ( DEM_MAX_NUMBER_EVENT_ENTRY_PER > DEM_ZERO))
        if ( ( DEM_DTC_ORIGIN_PERMANENT_MEMORY ==
               Dem_DTCFilterState[ClientId].dfs_DTCOrigin) )
        {
          Dem_NumOfEventMemoryEntryType LddMemLoc = DEM_NO_EVMEM_ENTRY;
          LddMemLoc = Dem_EvMem_FindPerMemLoc(LddEventId);
          if (LddMemLoc != DEM_NO_EVMEM_ENTRY)
          {
            /* @Trace: Dem_SUD_API_11529 */
            LddResult = E_OK;
          }
          else
          {
            /* @Trace: Dem_SUD_API_11528 */
            LddResult = E_NOT_OK;
          }
        }
        else
        #endif
        {
          /* @Trace: Dem_SUD_API_11527 */
          LddResult = E_OK;
          /* @Trace: Dem_SUD_API_11508 */
          #if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
          if (DEM_DTC_ORIGIN_OBD_RELEVANT_MEMORY ==
              Dem_DTCFilterState[ClientId].dfs_DTCOrigin)
          {
            /* @Trace: Dem_SUD_API_11524 */
            if ((DEM_OBD_EVENT_MEMORY_SET_IDX !=
                 Dem_Event[LddEventId - DEM_ONE].ucEventMemDstIdx) ||
                #if (DEM_J1979_2_OBD_ON_UDS == STD_ON)
                /* Trace: DEM_19792_42_04 */
                ((LddCbDTC->ddDtcFormat != DEM_DTC_FORMAT_OBD_3BYTE) && 
                 (LddCbDTC->ddDtcFormat != DEM_DTC_FORMAT_OBD) &&
                 (LddCbDTC->ddDtcFormat != DEM_DTC_FORMAT_UDS))
                #else
                ((LddCbDTC->ddDtcFormat != DEM_DTC_FORMAT_OBD) &&
                (LddCbDTC->ddDtcFormat != DEM_DTC_FORMAT_OBD_3BYTE))
                #endif /*(DEM_J1979_2_OBD_ON_UDS == STD_ON)*/
                )
            {
              /* @Trace: Dem_SUD_API_10741 */
              LddResult = E_NOT_OK;
            }
          }
          else
          #endif
          /* polyspace-begin DEFECT:DEAD_CODE [Justified:Low] "Dead Code by Configuration" */
          /* polyspace-begin MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] "Same as Dead Code" */
          /* @Trace: Dem_SUD_API_11509 */
          /* polyspace +1 DEFECT:DATA_RACE [Not a defect:Low] "Not a defect" */ 
          if (( Dem_Event[LddEventId - DEM_ONE].aaEventDestination !=
                Dem_DTCFilterState[ClientId].dfs_DTCOrigin) 
                && ( LddCbDTC->ddDtcFormat != DEM_DTC_FORMAT_UDS)
                #if (DEM_J1979_2_OBD_ON_UDS == STD_ON)
                && ( LddCbDTC->ddDtcFormat != DEM_DTC_FORMAT_OBD_3BYTE)
                #endif
              )
          {
            /* @Trace: Dem_SUD_API_10742 */
            LddResult = E_NOT_OK;
          }
          /* Check for DTCFormat filter matching */
          else if (Dem_EvMem_DTCFormatIsValid(
                    Dem_DTCFilterState[ClientId].dfs_DTCFormat, LddCbDTC)
                    != DEM_TRUE)
          {
            /* @Trace: Dem_SUD_API_10743 */
            LddResult = E_NOT_OK;
          }
          /* Check for DTCStatusMask filter matching */
          else if (DEM_ZERO != Dem_DTCFilterState[ClientId].dfs_DTCStatusMask)
          {
            Dem_UdsStatusByteType LddStatusMask =
                Dem_DTCFilterState[ClientId].dfs_DTCStatusMask;
            /* If specific StatusAvailablilityMask of a DTC is existed */
            /* @Trace: Dem_SUD_API_11511 */
            /* polyspace +1 MISRA-C3:14.3 [Justified:Low] Justify with annotations */
            if (DEM_ZERO != LddCbDTC->UdsStatusAvailabilityMask)
            {
              /* @Trace: Dem_SUD_API_11512 */
              /* UdsStatusAvailabilityMask and
               * Dem_DTCFilterState[ClientId].dfs_DTCStatusMask are
               * subset of Dem_Status_Availability_Mask */
              LddStatusMask = Dem_DTCFilterState[ClientId].dfs_DTCStatusMask &
                      LddCbDTC->UdsStatusAvailabilityMask;
            }
            /* @Trace: Dem_SUD_API_11513 */
            if ((LddDtcStatusByte & LddStatusMask) == DEM_ZERO)
            {
              /* @Trace: Dem_SUD_API_11514 */
              LddResult = E_NOT_OK;
            }
          }          
          else
          {
            /* @Trace: Dem_SUD_API_11510 */
            /* Do nothing */
          }          
          /* polyspace-end DEFECT:DEAD_CODE [Justified:Low] "Dead Code by Configuration" */
          /* polyspace-end MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] "Same as Dead Code" */
          
          /* Check for DTCSeverity filter matching */
          /* @Trace: Dem_SUD_API_11516 */
          if ((Dem_DTCFilterState[ClientId].dfs_FilterWithSeverity == DEM_TRUE)
              && ((LddCbDTC->ddDtcSeverity &
                 Dem_DTCFilterState[ClientId].dfs_DTCSeverityMask) == DEM_ZERO)
              #if (DEM_J1979_2_OBD_ON_UDS == STD_ON)
              /* Trace: DEM_19792_42_06 */
              && ((LddCbDTC->eDemWWHOBDDTCClass &
                 Dem_DTCFilterState[ClientId].dfs_DTCSeverityMask) == DEM_ZERO)
              #endif /*(DEM_J1979_2_OBD_ON_UDS == STD_ON)*/
             )
          {
            /* @Trace: Dem_SUD_API_11515 */
            LddResult = E_NOT_OK;
          }
          
          /* Check if Filter with FDC supported */
          /* @Trace: Dem_SUD_API_11517 */
          if (Dem_DTCFilterState[ClientId].dfs_FilterForFDC == DEM_TRUE)
          {
            sint8 LscFDC = (sint8)0x00;
            
            /* If event don't support FDC , FDC is zero, so 'result' is no-ok */
            /* @Trace: Dem_SUD_API_11519 */
            if (E_OK == Dem_GetFaultDetectionCounter(LddEventId, &LscFDC))
            {
              /* @Trace: SWS_Dem_00208
               * The FDC values should be in the range 0x01-0x7E */
              /* @Trace: Dem_SUD_API_11520 */
              if ((LscFDC < (sint8)0x01) || (LscFDC > (sint8)0x7E))
              {
                /* @Trace: Dem_SUD_API_11521 */
                LddResult = E_NOT_OK;
              }
            }
          }
          
          #if (DEM_J1979_2_OBD_ON_UDS == STD_ON)
          if(LddResult == E_OK)
          {
            /* Trace: DEM_19792_56_06 */
            /* Check separately with other SubFunc because 0x56, 0x1A uses independent filter values */
            /* exclude DEM_OBD_RDY_NONE Group Request (DEM_OBD_RDY_NONE is zero) */
            /* polyspace-begin MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] "Same as Dead Code" */
            if (Dem_DTCFilterState[ClientId].dfs_ReadinessGroupNumber != 0xFFu)
            {
              /* Ignore Previous Filtering Check */
              LddResult = E_NOT_OK;
              if (Dem_Event[LddEventId - DEM_ONE].ulEventOBDReadinessGroup == 
                    Dem_DTCFilterState[ClientId].dfs_ReadinessGroupNumber)
              {
                LddResult = E_OK;
              }
            }
            /* polyspace-end MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] "Same as Dead Code" */

            /* Trace: DEM_19792_1A_05 */
            if (Dem_DTCFilterState[ClientId].dfs_ExtendedDataRecord != 0x00)          
            {
              /* Ignore Previous Filtering Check */
              LddResult = E_NOT_OK;          
              
              /* @Trace: Dem_SUD_API_20126 */
              if (Dem_Event[LddEventId - DEM_ONE].e_PointToData < DEM_NUM_OF_EVENTRELATEDDATA)
              {
                Dem_EventRelatedDataPCType LddEvData = 
                    &Dem_EventRelatedData[Dem_Event[LddEventId - DEM_ONE].e_PointToData];
                
                if (LddEvData->EDClassPos < DEM_NUM_OF_EXTENDEDDATACLASS)
                {
                  Dem_ExtendedDataClassPCType LddExtendedData = 
                      &Dem_ExtendedDataClass[LddEvData->EDClassPos];
                    /* In case of BufSize is DEM_ZERO, Read FF regardless of a size of
                    * DestBuffer */
                  uint16 LusExtendedDataSize = Dem_GetSizeOfExtendedData(
                      LddExtendedData, Dem_DTCFilterState[ClientId].dfs_ExtendedDataRecord, NULL_PTR
                      #if (DEM_J1979_2_OBD_ON_UDS == STD_ON)
                      , LddEventId
                      #endif
                      );
              
                  /* If Size is not zero = Requested EDR Supported in this DTC */ 
                  if (LusExtendedDataSize > DEM_ZERO)
                  {
                    LddResult = E_OK;          
                  }
                }
              }            
            }
          }
          #endif /* J19792 */
        }
		
	    if (E_OK == LddResult)
        {
          if ((DEM_DTC_ORIGIN_PRIMARY_MEMORY == Dem_DTCFilterState[ClientId].dfs_DTCOrigin)
             && (DEM_TRUE != Dem_GaaDTCAttributes[LddCbDTC->usDemDTCAttributesRef].ucPrimaryMemory))
          {
            LddResult = E_NOT_OK;
          } 
          else if ((DEM_DTC_ORIGIN_MIRROR_MEMORY == Dem_DTCFilterState[ClientId].dfs_DTCOrigin)
                && (DEM_TRUE != Dem_GaaDTCAttributes[LddCbDTC->usDemDTCAttributesRef].ucMirrorMemory))
          {
            LddResult = E_NOT_OK;
          }
          else
          {
             /* do nothing */
          }
        }
		
        /* @Trace: Dem_SUD_API_11522 */
        if (E_OK == LddResult)
        {
          /* @Trace: Dem_SUD_API_11523 */
          Dem_EvSetProcState(LddEventId, DEM_EVPROCSTATE_DTC_FILTER);
          /* Increment the number of filtered DTC */
          Dem_DTCFilterState[ClientId].dfs_NumOfFilteredDTC++;
        }
      }
    }
  }
  #endif

  SchM_Enter_Dem_REQUEST_DATA_PROTECTION();
  /* polyspace<RTE:UNR:Not a defect:No action planned> if-condition will
   * evaluate to false if Dem_DcmCancelOperation is called by Dcm */
  /* @Trace: Dem_SUD_API_11530 */
  if (DEM_JOB_RUNNING == Dem_DTCFilterState[ClientId].dfs_JobAction)
  {
    /* @Trace: Dem_SUD_API_11531 */
    Dem_DTCFilterState[ClientId].dfs_JobAction = DEM_JOB_DONE;
  }
  SchM_Exit_Dem_REQUEST_DATA_PROTECTION();
}

/*******************************************************************************
 ** Function Name       : Dem_ClearEventsWithOutAssignedDTCs                  **
 **                                                                           **
 ** Service ID          : None                                                **
 **                                                                           **
 ** Description         : Clear events which do not assigned to any DTCs      **
 **                                                                           **
 ** Sync/Async          : Synchronous                                         **
 **                                                                           **
 ** Re-entrancy         : Reentrant                                           **
 **                                                                           **
 ** Input Parameters    : None                                                **
 **                                                                           **
 ** InOut parameter     : None                                                **
 **                                                                           **
 ** Output Parameters   : None                                                **
 **                                                                           **
 ** Return parameter    : Std_ReturnType                                      **
 **                                                                           **
 ** Preconditions       : None                                                **
 **                                                                           **
 ** Remarks             :                                                     **
 ******************************************************************************/
/* @Trace: SRS_BSW_00101 SRS_BSW_00310 SRS_Diag_04073 SRS_Diag_04117
           SRS_Diag_04150 SRS_Diag_04191 SRS_Diag_04194 SRS_Diag_04214
           SRS_BSW_00387
 */
/* polyspace +1 CODE-METRICS:PATH [Not a defect:Low] "Not a defect" */
FUNC(Std_ReturnType, DEM_CODE) Dem_ClearEventsWithOutAssignedDTCs(void)
{
  Std_ReturnType LddRetVal = E_NOT_OK;
  Dem_EventIdType LddEventId = DEM_ONE;
  Dem_EventParameterPCType LddEvent;
  boolean LblClearAllowed;
  /* @Trace: Dem_SUD_API_11532 */
  #if ((DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT) && \
       (DEM_MAX_NUMBER_EVENT_ENTRY_PER > DEM_ZERO))
  /* @Trace: Dem_SUD_API_11543 */
  Dem_NumOfEventMemoryEntryType LddMemLoc = DEM_NO_EVMEM_ENTRY;
  #endif
  /* @Trace: Dem_SUD_API_11550 */
  for (; LddEventId <= DEM_NUMBER_OF_EVENTS; LddEventId++)
  {
    LddEvent = &Dem_Event[LddEventId - DEM_ONE];
    /* @Trace: Dem_SUD_API_11551 */
    if (DEM_NO_IDX_U8 == LddEvent->e_PointToDTC)
    {

      Dem_EvClearProcState(LddEventId, DEM_EVPROCSTATE_EVENT_DEL);

      LblClearAllowed = DEM_TRUE;
      /* @Trace: Dem_SUD_API_11552 */
      if (NULL_PTR != LddEvent->pDemClearEventAllowed)
      {
        boolean LblEvAllowed = DEM_TRUE;

        /* @Trace: SWS_Dem_00515
         * The Dem module shall call the callback DemClearEventAllowed for
         * each event it is configured for, before clearing this event.
         * */
        if (E_OK == LddEvent->pDemClearEventAllowed(&LblEvAllowed))
        {
          /* @Trace: SWS_Dem_00667
           * If the DTC is not configured to use event combination,
           * the out-parameter Allowed of the callback DemClearEventAllowed
           * returns "false" and the return value is equal to E_OK,
           * the Dem shall not clear the respective event memory
           * entry and Dem-internal data values.*/

          /* @Trace: SWS_Dem_01295
           * If the DTC is configured to use event combination, if only
           * one DemClearEventAllowed callback has the out-parameter Allowed
           * set to FALSE and returns E_OK, the Dem shall not clear the event
           * status, respective event memory entry and Dem-internal
           * data values.*/

          /* @Trace: SWS_Dem_01202
           * Defintion of a failed clear DTC operation. If the Dem module is
           * requested to clear diagnostic information, the Dem shall return
           * DEM_CLEAR_FAILED in case of clearing a single DTC at least one
           * DemClearEventAllowed callback assigned to the event of the
           * DTC returns FALSE.
           * */
          /* @Trace: Dem_SUD_API_11554 */
          if (DEM_FALSE == LblEvAllowed)
          {
            /* @Trace: Dem_SUD_API_10745 */
            LblClearAllowed = DEM_FALSE;

            if (DEM_NO_STATUS_BYTE_CHANGE
                == LddEvent->usDemClearEventAllowedBehavior)
            {
              /* @Trace: Dem_SUD_API_10746 */
              /* @Trace: SWS_Dem_00668
               * If the out-parameter "Allowed" of the callback
               * DemClearEventAllowed returns "false" and the configuration
               * parameter DemClearEventAllowedBehavior is set to
               * DEM_NO_STATUS_BYTE_CHANGE, the related UDS status byte shall
               * not be modified.
               * */
            }
            else if (DEM_ONLY_THIS_CYCLE_AND_READINESS
                != LddEvent->usDemClearEventAllowedBehavior)
            {
              /* @Trace: Dem_SUD_API_10747 */
              /* @Trace: SWS_Dem_00669
               * If the out-parameter Allowed of the callback
               * DemClearEventAllowed returns "false" and the configuration
               * parameter DemClearEventAllowedBehavior is set to
               * DEM_ONLY_THIS_CYCLE_AND_READINESS, the related
               * UDS status bits 1 (TestFailedThisOperationCycle),
               * 4 (TestNotCompletedSinceLastClear),
               * 5 (TestFailedSinceLastClear), and
               * 6 (TestNotCompletedThisOperationCycle) shall be reset.
               * */
              DEM_RST_UDSSTATUSBYTE(LddEventId,
                  (uint8) DEM_UDS_STATUS_TFTOC | (uint8) DEM_UDS_STATUS_TNCSLC |
                  (uint8) DEM_UDS_STATUS_TFSLC | (uint8) DEM_UDS_STATUS_TNCTOC);
              /* @Trace: SWS_Dem_01332
               * In case an event is partially cleared according to
               * [SWS_Dem_00669], the dependent functionality shall be handled
               * as if the event is not cleared at all. This means the callback
               * function InitMonitorForEvent will not be called and the FDC
               * will remain unchanged in this situation.
               * */
            }
            else
            {
              /* @Trace: Dem_SUD_API_11556 */
              /* Nothing to do */
            }
          }
        }
        else
        {
          /* @Trace: Dem_SUD_API_11553 */
          /* @Trace: SWS_Dem_00516
           * If the return value of the callback DemClearEventAllowed is equal
           * to E_NOT_OK, the return value shall not be changed and
           * event-deletion is allowed.
           * */
        }
      }
      /* @Trace: Dem_SUD_API_11555 */
      if (DEM_TRUE == LblClearAllowed)
      {
        uint8 LucDebType = DEM_GET_EVENTPARAM_DEBOUNCE_TYPE(
            LddEvent->ParamFieldsA);
        Dem_UdsStatusByteType LddDTCStatusOld = Dem_GetDTCStatus(LddEventId);
        Dem_UdsStatusByteType LddEventStatusByteOld =
            Dem_AllEventStatusByte[LddEventId];

        /* @IF_REQ: SWS_Dem_00301 :
         * Permanent DTCs must only be cleared once they have been self-healed
         * if the last diagnosis result is detected as a PASS and the MIL is no
         * longer being triggered for this event.*/

        /* @Trace: SWS_Dem_00680
         * The Dem_ClearDTC API shall trigger the callback function
         * InitMonitorForEvent of the related event(s) in case of clearing
         * the event(s). The InitMonitorReason parameter shall be set to
         * DEM_INIT_MONITOR_CLEAR.
         * */

        /* Re-initialization triggered before the Dem module returns  E_OK */
        /* @Trace: Dem_SUD_API_11533*/
        /* @Trace: Dem_SUD_MACRO_016 */
        #if (DEM_TRIGGER_INIT_BEFORE_CLEAR_OK == STD_ON)
        /* @Trace: SWS_Dem_00256
         */
        /* @Trace: Dem_SUD_API_11534 */
        if (LddEvent->pDemInitMonitorForEvent != NULL_PTR)
        {
          /* @Trace: Dem_SUD_API_10751 */
          /* polyspace<RTE: COR : Not a defect : No Action Planned > function
           * ptr points to a valid function */
          LddEvent->pDemInitMonitorForEvent((Dem_InitMonitorReasonType)
              DEM_INIT_MONITOR_CLEAR);
        }
        #endif

        /* [Dem077]
         * The function Dem_ClearDTC shall clear the status of all event(s)
         * related to the specified DTC(s), as well as all associated event
         * memory entries for these event(s). */
        DEM_RST_UDSSTATUSBYTE(LddEventId,
            (uint8) DEM_UDS_STATUS_TNCSLC | (uint8) DEM_UDS_STATUS_TNCTOC);

        /* Dem343:
         * After receiving a command for clearing the event memory
         * (refer to Dem_ClearDTC), the respective fault detection counters
         * shall be initialized with 0, presuming event debouncing is handled
         * Dem-internally. */
        /* @Trace: Dem_SUD_API_11535 */
        if ((DEM_DEBOUNCE_TIME_BASED == LucDebType)
            || (DEM_DEBOUNCE_COUNTER_BASED == LucDebType))
        {
          /* @Trace: Dem_SUD_API_11536 */
          Dem_ResetFaultDectectionCounter(LddEventId);
        }

        /* Reset the indicator failure cycle counter to zero */
        /* @Trace: Dem_SUD_API_11537 */
        if (DEM_TRUE == Dem_InitIndicator(LddEventId))
        {
          /* @Trace: Dem_SUD_API_10748 */
          Dem_EvMem_SetNonVolatieDataStatus(DEM_NVDATA_ALL_EVENT_STATUS_ID,
          DEM_EVMEM_STATUS_CLEARDTC);
        }
        /* @Trace: Dem_SUD_API_11538 */
        #if ((DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT) && \
             (DEM_MAX_NUMBER_EVENT_ENTRY_PER > DEM_ZERO))
        LddMemLoc = Dem_EvMem_FindPerMemLoc(LddEventId);
        /* @Trace: Dem_SUD_API_11539 */
        if (DEM_NO_EVMEM_ENTRY != LddMemLoc)
        {
          /* @Trace: Dem_SUD_API_11540 */
          if (DEM_NO_INDATT_IDX != LddEvent->e_PointToIndicator)
          {
            /* @Trace: Dem_SUD_API_11541 */
            if (Dem_GaaIndicatorList[LddEvent->e_PointToIndicator].
                NumHealingCycles > DEM_ONE)
            {
              /* @Trace: Dem_SUD_API_10749 */
              (void)Dem_EvMem_SetIndicatorHealingCounter(
                  Dem_GaaIndicatorList[LddEvent->e_PointToIndicator].
                         HealingCycleCounterPos,
                  Dem_GaaIndicatorList[LddEvent->e_PointToIndicator].
                         NumHealingCycles - DEM_TWO);
              Dem_PermanentEventMemory[LddMemLoc].PfcQualified = DEM_FALSE;
            }
          }
        }
        #endif
        /* @Trace: Dem_SUD_API_11542 */
        if (LddEventStatusByteOld != Dem_AllEventStatusByte[LddEventId])
        {
          Dem_TriggerCallbackOnUdsStatus(LddEventId, LddEventStatusByteOld,
            LddDTCStatusOld);
          /* @Trace: Dem_SUD_API_11545 */
          #if (DEM_UDS_STATUS_IN_EVENT_NVBLOCK == STD_ON)
          /* @Trace: Dem_SUD_API_11544 */
          if (((LddEventStatusByteOld ^ Dem_AllEventStatusByte[LddEventId])
              & DEM_UDS_STATUS_MASK_ALLEVENTSTATUS) != DEM_ZERO)
          {
            /* @Trace: Dem_SUD_API_11546 */
            Dem_EvMem_SetUdsStatusByteToNvData(LddEventId);
            Dem_EvMem_SetNonVolatieDataStatus(DEM_NVDATA_ALL_EVENT_STATUS_ID,
            DEM_EVMEM_STATUS_CLEARDTC);
          }
          #endif
        }
        /* @Trace: Dem_SUD_API_11547 */
        #if (DEM_TRIGGER_INIT_BEFORE_CLEAR_OK == STD_OFF)
        /* Re-initialization triggered after the Dem module returns E_OK */
        /* if (E_OK == LddRetVal) : condition is always true */
        /* @Trace: Dem_SUD_API_11548 */
        Dem_EvSetProcState(LddEventId, DEM_EVPROCSTATE_INITMON_ONCLEARDTC);
        #endif
        /* @Trace: Dem_SUD_API_11549 */
        if (DEM_TRUE == Dem_EvIsProcStateTriggered(LddEventId,
              DEM_EVPROCSTATE_EVENT_STORED))
        {
          /* @Trace: Dem_SUD_API_10750 */
          Dem_EvSetProcState(LddEventId, DEM_EVPROCSTATE_EVENT_DEL);
        }

        LddRetVal = E_OK;
      }
    }
  }

  return LddRetVal;
}

/*******************************************************************************
 ** Function Name       : Dem_ClearSingleDTCStatusByte                        **
 **                                                                           **
 ** Service ID          : None                                                **
 **                                                                           **
 ** Description         : Clear single DTC status byte                        **
 **                                                                           **
 ** Sync/Async          : Synchronous                                         **
 **                                                                           **
 ** Re-entrancy         : Reentrant                                           **
 **                                                                           **
 ** Input Parameters    : cbDTC, DTCOrigin                                    **
 **                                                                           **
 ** InOut parameter     : None                                                **
 **                                                                           **
 ** Output Parameters   : None                                                **
 **                                                                           **
 ** Return parameter    : Std_ReturnType                                      **
 **                                                                           **
 ** Preconditions       : None                                                **
 **                                                                           **
 ** Remarks             :                                                     **
 ******************************************************************************/
/* @Trace: SRS_BSW_00101 SRS_BSW_00310 SRS_Diag_04001 SRS_Diag_04067
           SRS_Diag_04068 SRS_Diag_04073 SRS_Diag_04117 SRS_Diag_04150
           SRS_Diag_04191 SRS_Diag_04194 SRS_Diag_04214 SRS_Diag_04164
 */
/* polyspace +1 CODE-METRICS:PATH [Not a defect:Low] "Not a defect" */
FUNC(Std_ReturnType, DEM_CODE) Dem_ClearSingleDTCStatusByte(
  Dem_CombinedDtcPCType cbDTC,
  Dem_DTCOriginType DTCOrigin
  )
{
  Std_ReturnType LddRetVal = E_NOT_OK;

  Dem_EventIdType LddEventId;
  Dem_EventParameterPCType LddEvent;

  boolean LblClearAllowed;
  /* @Trace: Dem_SUD_API_11568 */
  #if (DEM_CLEAR_EVENTS_WITHOUT_DTC_EVENT_MEMORY != DEM_NO_EVMEM_IDX)
  /*trigger to clear events without assigned DTCs*/
  /* @Trace: Dem_SUD_API_11557 */
  boolean LblClearEventsWoDTCs = DEM_FALSE;
  #endif
  Dem_NumOfEventIdType LddStartPos = Dem_GetStartEventIdMapOfCbDTC(cbDTC);
  const Dem_NumOfEventIdType LddEndPos = Dem_GetEndEventIdMapOfCbDTC(cbDTC);
  /* @Trace: Dem_SUD_API_11590 */
  #if ((DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT) && \
       (DEM_MAX_NUMBER_EVENT_ENTRY_PER > DEM_ZERO))
  /* @Trace: Dem_SUD_API_11579 */
  Dem_NumOfEventMemoryEntryType LddMemLoc = DEM_NO_EVMEM_ENTRY;
  #endif

  /* @Trace: SWS_Dem_00718
   * In Master, Primary and Dependent / Secondary ECUs executing
   * service $04 shall clear all emission-related diagnostic information
   * in primary and user defined (event) memory (if configured) as defined
   * in SAE J1979 [17].*/

  /* @Trace: SWS_Dem_00719
   * Executing service $04 shall include non emissionrelated diagnostic
   * information (e.g. Debouncing counter, Event/DTC related status
   * information as TestFailedSinceLastClear) of primary and
   * all user defined event memories (if configured) in Master,
   * Primary and Dependent / Secondary ECUs.*/

  uint8 LucEventAllowedFalseCnt = DEM_ZERO;
  boolean LblCombinedEventExist = DEM_FALSE;
  uint16 LucNumOfEvent = LddEndPos - LddStartPos;
  /* @Trace: Dem_SUD_API_11601 */
  if (LucNumOfEvent > DEM_ONE)
  {
    /* @Trace: Dem_SUD_API_11603 */
    LblCombinedEventExist = DEM_TRUE;
  }
  /* @Trace: Dem_SUD_API_11604 */
  for (; LddStartPos < LddEndPos; LddStartPos++)
  {              
    LddEventId = Dem_ListOfCombinedEvents[LddStartPos];
    LddEvent = &Dem_Event[LddEventId - DEM_ONE];
    /* @Trace: Dem_SUD_API_11605 */
    if (NULL_PTR != LddEvent->pDemClearEventAllowed)
    {
      boolean LblEvAllowed = DEM_TRUE;
      /* @Trace: Dem_SUD_API_11606 */
      if (E_OK == LddEvent->pDemClearEventAllowed(&LblEvAllowed))
      {
        /* @Trace: Dem_SUD_API_11558 */
        if (DEM_FALSE == LblEvAllowed)
        {
          /* @Trace: Dem_SUD_API_11560 */
          /* Increase flag */
          LucEventAllowedFalseCnt++;
        }
      }
    }
  }

  /* @Case: Single DTC   -> LucEventAllowedFalseCnt = 0     -> Clear event
   *                       LucEventAllowedFalseCnt = 1     -> Not clear event
   *
   * @Case: Combined DTC -> LucEventAllowedFalseCnt = 0     -> Clear
   *                       LucEventAllowedFalseCnt = 1     -> Not clear event
   *                       LucEventAllowedFalseCnt = 2(>1) -> Clear event
   */
  LddStartPos = Dem_GetStartEventIdMapOfCbDTC(cbDTC);
  /* @Trace: Dem_SUD_API_11559 */
  for (; LddStartPos < LddEndPos; LddStartPos++)
  {              
    LddEventId = Dem_ListOfCombinedEvents[LddStartPos];
    LddEvent= &Dem_Event[LddEventId - DEM_ONE];
    /* @Trace: Dem_SUD_API_11561 */
    #if (DEM_CLEAR_EVENTS_WITHOUT_DTC_EVENT_MEMORY != DEM_NO_EVMEM_IDX)
    /* @Trace: Dem_SUD_API_11562 */
    if ((DEM_NO_EVMEM_IDX != LddEvent->ucEventMemDstIdx) &&
        (DEM_CLEAR_EVENTS_WITHOUT_DTC_EVENT_MEMORY ==
            LddEvent->ucEventMemDstIdx))
    {
      /* @Trace: Dem_SUD_API_11563 */
      /* @Trace: SWS_Dem_01249
       * If the event memory referenced by
       * DemClearEventsWithoutDTCEventMemoryRef is cleared via any of the
       * Dem_ClearDTC APIs, the Dem shall clear also all the events that are
       * not assigned to any event memory.
       * */
      LblClearEventsWoDTCs = DEM_TRUE;
    }
    #endif
    /* @Trace: Dem_SUD_API_10752 */

    Dem_EvClearProcState(LddEventId,DEM_EVPROCSTATE_EVENT_DEL);

    LblClearAllowed = DEM_TRUE;

    /* @Trace: Dem_SUD_API_11567 */
    if (NULL_PTR != LddEvent->pDemClearEventAllowed)
    {
      boolean LblEvAllowed = DEM_TRUE;
      /* polyspace<RTE: COR : Not a defect : No Action Planned > function ptr
       * points to a valid function */

      /* @Trace: SWS_Dem_00515
       * The Dem module shall call the callback DemClearEventAllowed for
       * each event it is configured for, before clearing this event.
       * */
      if (E_OK == LddEvent->pDemClearEventAllowed(&LblEvAllowed))
      {
        /* @Trace: SWS_Dem_00667
         * If the DTC is not configured to use event combination,
         * the out-parameter Allowed of the callback DemClearEventAllowed
         * returns "false" and the return value is equal to E_OK,
         * the Dem shall not clear the respective event memory
         * entry and Dem-internal data values.*/

        /* @Trace: SWS_Dem_01295
         * If the DTC is configured to use event combination, if only
         * one DemClearEventAllowed callback has the out-parameter Allowed
         * set to FALSE and returns E_OK, the Dem shall not clear the
         * event status, respective event memory entry and
         * Dem-internal data values.*/

        /* @Trace: SWS_Dem_01202
         * Defintion of a failed clear DTC operation. If the Dem module is
         * requested to clear diagnostic information, the Dem shall return
         * DEM_CLEAR_FAILED in case of clearing a single DTC at least one
         * DemClearEventAllowed callback assigned to the event of the
         * DTC returns FALSE.
         * */
        /* @Trace: Dem_SUD_API_11570 */
        if (DEM_FALSE == LblEvAllowed)
        {
          LblClearAllowed = DEM_FALSE;
          if (DEM_NO_STATUS_BYTE_CHANGE ==
              LddEvent->usDemClearEventAllowedBehavior)
          {
            /* @Trace: Dem_SUD_API_11572 */
            /* @Trace: SWS_Dem_00668
             * If the out-parameter "Allowed" of the callback
             * DemClearEventAllowed returns "false" and the configuration
             * parameter DemClearEventAllowedBehavior is set to
             * DEM_NO_STATUS_BYTE_CHANGE, the related UDS status byte shall not
             * be modified.
             * */
          }
          else if (( DEM_ONLY_THIS_CYCLE_AND_READINESS ==
                     LddEvent->usDemClearEventAllowedBehavior) &&  \
                  (( DEM_ONE != LucEventAllowedFalseCnt) || \
                   ( DEM_TRUE != LblCombinedEventExist)))
          {
            /* @Trace: Dem_SUD_API_11571 */
            /* @Trace: SWS_Dem_00669
             * If the out-parameter Allowed of the callback DemClearEventAllowed
             * returns "false" and the configuration parameter
             * DemClearEventAllowedBehavior is set to
             * DEM_ONLY_THIS_CYCLE_AND_READINESS, the related
             * UDS status bits 1 (TestFailedThisOperationCycle),
             * 4 (TestNotCompletedSinceLastClear),
             * 5 (TestFailedSinceLastClear), and
             * 6 (TestNotCompletedThisOperationCycle) shall be reset.
             * */
            DEM_RST_UDSSTATUSBYTE(LddEventId,
                    (uint8)DEM_UDS_STATUS_TFTOC |
                    (uint8)DEM_UDS_STATUS_TNCSLC|
                    (uint8)DEM_UDS_STATUS_TFSLC |
                    (uint8)DEM_UDS_STATUS_TNCTOC);
            /* @Trace: SWS_Dem_01332
             * In case an event is partially cleared according to
             * [SWS_Dem_00669], the dependent functionality shall be handled as
             * if the event is not cleared at all. This means the callback
             * function InitMonitorForEvent will not be called and the FDC will
             * remain unchanged in this situation.
             * */
          }
          else
          {
            /* @Trace: Dem_SUD_API_10753 */
            /* Nothing to do */
          }
        }
      }
      else
      {
        /* @Trace: Dem_SUD_API_11569 */
        /* @Trace: SWS_Dem_00516
         * If the return value of the callback DemClearEventAllowed is
         * equal to E_NOT_OK, the return value shall not be changed and
         * event-deletion is allowed.
         * */
      }
    }
    /* @Trace: Dem_SUD_API_11573 */
    if ((DEM_TRUE == LblClearAllowed)&& (DEM_ONE != LucEventAllowedFalseCnt))
    {
      /* @Trace: Dem_SUD_API_11574 */
      if (DEM_DTC_ORIGIN_MIRROR_MEMORY != DTCOrigin)
      {
        uint8 LucDebType = DEM_GET_EVENTPARAM_DEBOUNCE_TYPE(
            LddEvent->ParamFieldsA);
        Dem_UdsStatusByteType LddDTCStatusOld = Dem_GetDTCStatus(LddEventId);
        Dem_UdsStatusByteType LddEventStatusByteOld =
            Dem_AllEventStatusByte[LddEventId];

        /* @IF_REQ: SWS_Dem_00301
         * Permanent DTCs must only be cleared once they have been self-healed
         * if the last diagnosis result is detected as a PASS and the MIL is no
         * longer being triggered for this event. */

        /* @Trace: SWS_Dem_00680
         * The Dem_ClearDTC API shall trigger the callback function
         * InitMonitorForEvent of the related event(s) in case of clearing the
         * event(s).The InitMonitorReason parameter shall be set to
         * DEM_INIT_MONITOR_CLEAR.
         * */

        /* Re-initialization triggered before the Dem module returns  E_OK */
        /* @Trace: Dem_SUD_API_11575 */
        #if (DEM_TRIGGER_INIT_BEFORE_CLEAR_OK == STD_ON)
        /* @Trace: SWS_Dem_00256
         */
        /* @Trace: Dem_SUD_API_11576 */
        if (LddEvent->pDemInitMonitorForEvent != NULL_PTR)
        {
          /* @Trace: Dem_SUD_API_11577 */
          /* polyspace<RTE: COR : Not a defect : No Action Planned > function
           * ptr points to a valid function */
          LddEvent->pDemInitMonitorForEvent(
              (Dem_InitMonitorReasonType) DEM_INIT_MONITOR_CLEAR);
        }
        #endif
    
        /* [Dem077]
         * The function Dem_ClearDTC shall clear the status of all event(s)
         * related to the specified DTC(s), as well as all associated event
         * memory entries for these event(s). */

        /* @Trace: SWS_Dem_00385
         * After a clear command has been applied to a specific DTC the Dem
         * module shall set the UDS status byte to 0x50 (readiness bits 4 and 6
         * set to 1, and all others are set to zero). */
        DEM_RST_UDSSTATUSBYTE(LddEventId,
            (uint8)DEM_UDS_STATUS_TNCSLC |(uint8)DEM_UDS_STATUS_TNCTOC);

        Dem_MonitorStatusType LddMonitorStatusByteOld =
            Dem_AllMonitorStatus[LddEventId];
        /* @Trace: SWS_Dem_01284
         * When processing a clear DTC command (e.g. via Dem_ClearDTC), the Dem
         * shall set the monitor status assigned to the cleared DTCs to 0x04. */
        Dem_AllMonitorStatus[LddEventId] = DEM_MONITOR_STATUS_ASSIGNED_CLEARDTC;
        /* @Trace: Dem_SUD_API_11578 */
        if (LddMonitorStatusByteOld != Dem_AllMonitorStatus[LddEventId])
        {
          /* @Trace: Dem_SUD_API_11580 */
          DemTriggerCallbackOnMonitorStatus(LddEventId);
        }

        /* @Trace: SWS_Dem_00343
         * After receiving a command for clearing the event memory (refer to
         * chapter 7.7.2.2), the Dem-internal debounce algorithm shall be reset,
         * presuming event debouncing is handled Dem-internally.
         */
        /* @Trace: Dem_SUD_API_11581 */
        if (( DEM_DEBOUNCE_TIME_BASED == LucDebType) ||
            ( DEM_DEBOUNCE_COUNTER_BASED == LucDebType))
        {
          /* @Trace: Dem_SUD_API_11582 */
          Dem_ResetFaultDectectionCounter(LddEventId);
        }
    
        /* Reset the indicator failure cycle counter to zero */
        /* @Trace: Dem_SUD_API_11583 */
        if (DEM_TRUE == Dem_InitIndicator(LddEventId))
        {
          /* @Trace: Dem_SUD_API_11584 */
          Dem_EvMem_SetNonVolatieDataStatus(DEM_NVDATA_ALL_EVENT_STATUS_ID,
              DEM_EVMEM_STATUS_CLEARDTC);
        }

        /* @Trace: Dem_SUD_API_11585 */
        #if ((DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT) && \
             (DEM_MAX_NUMBER_EVENT_ENTRY_PER > DEM_ZERO))
        LddMemLoc = Dem_EvMem_FindPerMemLoc(LddEventId);
        /* @Trace: Dem_SUD_API_11586 */
        if (DEM_NO_EVMEM_ENTRY != LddMemLoc)
        {
          /* @Trace: Dem_SUD_API_10801 */
          if (DEM_NO_INDATT_IDX != LddEvent->e_PointToIndicator)
          {
            /* @Trace: Dem_SUD_API_11587 */
            if (Dem_GaaIndicatorList[LddEvent->e_PointToIndicator]
                        .NumHealingCycles > DEM_ONE)
            {
              /* @Trace: Dem_SUD_API_11588 */
              (void)Dem_EvMem_SetIndicatorHealingCounter(
                  Dem_GaaIndicatorList[LddEvent->e_PointToIndicator].
                           HealingCycleCounterPos,
                  Dem_GaaIndicatorList[LddEvent->e_PointToIndicator].
                           NumHealingCycles - DEM_ONE);
              Dem_PermanentEventMemory[LddMemLoc].PfcQualified  = DEM_FALSE;
            }
          }
        }
        #endif
      

        /* @Trace: SWS_Dem_00763
         * The Dem shall reset the DTR data using the reference to the
         * Event per DTR, whenever the Event is affected by a fault clear
         * command.*/
        /* @Trace: Dem_SUD_API_11591 */
        #if ((DEM_NUMBER_OF_DTRS > DEM_ZERO) && \
             (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT))
        /* @Trace: Dem_SUD_API_11589 */
        for (uint8 LucIdx = DEM_ZERO; LucIdx < DEM_NUMBER_OF_DTRS; LucIdx++)
        {
          /* @Trace: Dem_SUD_API_11592 */
          if (Dem_GaaDtrInfo[LucIdx].usEventId == LddEventId)
          {
            /* @Trace: Dem_SUD_API_11593 */
            Dem_DtrData[LucIdx].Testvalue = DEM_ZERO;
            Dem_DtrData[LucIdx].Lowlimvalue = DEM_ZERO;
            Dem_DtrData[LucIdx].Upplimvalue = DEM_ZERO;
          }
        }
        #endif
        /* @Trace: Dem_SUD_API_11594 */
        if (LddEventStatusByteOld != Dem_AllEventStatusByte[LddEventId])
        {
          Dem_TriggerCallbackOnUdsStatus(LddEventId, LddEventStatusByteOld,
                      LddDTCStatusOld);
          /* @Trace: Dem_SUD_API_11595 */
          #if (DEM_UDS_STATUS_IN_EVENT_NVBLOCK == STD_ON)
          /* @Trace: Dem_SUD_API_11596 */
          if ((( LddEventStatusByteOld ^ Dem_AllEventStatusByte[LddEventId]) &
                 DEM_UDS_STATUS_MASK_ALLEVENTSTATUS) != DEM_ZERO)
          {
            /* @Trace: Dem_SUD_API_11597 */
            Dem_EvMem_SetUdsStatusByteToNvData(LddEventId);
            Dem_EvMem_SetNonVolatieDataStatus(DEM_NVDATA_ALL_EVENT_STATUS_ID,
                 DEM_EVMEM_STATUS_CLEARDTC);
          }
          #endif
        }
        /* @Trace: Dem_SUD_API_11598 */
        #if (DEM_TRIGGER_INIT_BEFORE_CLEAR_OK == STD_OFF)
        /* Re-initialization triggered after the Dem module returns E_OK */
        /* if (E_OK == LddRetVal) : condition is always true */
        /* @Trace: Dem_SUD_API_11599 */
        Dem_EvSetProcState(LddEventId, DEM_EVPROCSTATE_INITMON_ONCLEARDTC);
        #endif
      }
      /* @Trace: Dem_SUD_API_11600 */
      if (DEM_TRUE == Dem_EvIsProcStateTriggered(LddEventId,
                 DEM_EVPROCSTATE_EVENT_STORED))
      {
        /* @Trace: Dem_SUD_API_11602 */
        Dem_EvSetProcState(LddEventId,DEM_EVPROCSTATE_EVENT_DEL);
      }

      LddRetVal = E_OK;
    }
  }
  /* @Trace: Dem_SUD_API_11564 */
  #if (DEM_CLEAR_EVENTS_WITHOUT_DTC_EVENT_MEMORY != DEM_NO_EVMEM_IDX)
  /* @Trace: Dem_SUD_API_11565 */
  if (DEM_TRUE == LblClearEventsWoDTCs)
  {
    /* @Trace: Dem_SUD_API_11566 */
    (void)Dem_ClearEventsWithOutAssignedDTCs();
  }
  #endif

  return LddRetVal;
}

/******************************************************************************
 * Function Name        : Dem_GetDTCStatus
 *
 * Service ID           : None
 *
 * Description          : This function is used to get status of DTC
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Reentrant
 *
 * Input Parameters     : EventId
 *                        
 * InOut parameter      : None
 *
 * Output Parameters    : None
 *
 * Return parameter     : Dem_UdsStatusByteType
 *
 * Preconditions        : None
 *
 * Remarks              : 
 *****************************************************************************/
/* @Trace: SRS_Diag_04073
 */
/* polyspace +1 CODE-METRICS:CALLING [Not a defect:Low] "Not a defect" */
FUNC(Dem_UdsStatusByteType, DEM_CODE) Dem_GetDTCStatus(
  const Dem_EventIdType EventId)
{
  Dem_UdsStatusByteType LddDTCStatus = DEM_ZERO;
  
  #if (DEM_EVENT_COMBINATION_SUPPORT != DEM_EVCOMB_DISABLED)
  P2CONST(Dem_CombinedDtcType, AUTOMATIC,  DEM_VAR) LddCbDTC =
                     Dem_GetCbDTCByEventId(EventId);
  /* @Trace: Dem_SUD_API_11609 */
  if (NULL_PTR != LddCbDTC)
  {    
    Dem_NumOfEventIdType LddStartPos = Dem_GetStartEventIdMapOfCbDTC(LddCbDTC);
    const Dem_NumOfEventIdType LddEndPos =
            Dem_GetEndEventIdMapOfCbDTC(LddCbDTC);
    /* @Trace: SWS_Dem_00441
     * The Dem module shall implement the status bit calculations for the
     * UDS status byte according to Table 7.2.
     */
    /* @Trace: Dem_SUD_API_11611 */
    for (; LddStartPos < LddEndPos; LddStartPos++)
    {
      /* Compute the DTC status */
      /* @Trace: Dem_SUD_API_11610 */
      LddDTCStatus |= Dem_AllEventStatusByte[
                   Dem_ListOfCombinedEvents[LddStartPos]];
    }
    /* As per SWS SWS_Dem_00441 : CbEvtBit 4 = (Event[1]Bit 4 | Event[2]Bit 4
     *       | ... | Event[n]Bit 4) & ! CbEvtBit 5 */
    /* @Trace: Dem_SUD_API_11615 */
    if (DEM_ZERO != (LddDTCStatus & (Dem_UdsStatusByteType)
          DEM_UDS_STATUS_TFSLC))
    {
      /* @Trace: Dem_SUD_API_11614 */
      LddDTCStatus &= (Dem_UdsStatusByteType)(~(Dem_UdsStatusByteType)
          DEM_UDS_STATUS_TNCSLC);
    }
    /* As per SWS SWS_Dem_00441 : CbEvtBit 6 = (Event[1]Bit 6 | Event[2]Bit 6 |
     * ... | Event[n]Bit 6) & ! CbEvtBit 1  */
    /* @Trace: Dem_SUD_API_11613 */
    if (DEM_ZERO != (LddDTCStatus & (Dem_UdsStatusByteType)
          DEM_UDS_STATUS_TFTOC))
    {
      /* @Trace: Dem_SUD_API_11612 */
      LddDTCStatus &= (Dem_UdsStatusByteType)(~(Dem_UdsStatusByteType)
          DEM_UDS_STATUS_TNCTOC);
    }
  }
  #else  
  /* polyspace<RTE:UNR:Not a defect:No action planned> If-condition always
   * evaluates to true. */
  /* @Trace: Dem_SUD_API_11607 */
  if (DEM_TRUE == Dem_EventIdIsValid(EventId))
  {
    /* Update the DTC Status */
    /* @Trace: Dem_SUD_API_11608 */
    LddDTCStatus = Dem_AllEventStatusByte[EventId];
  }
  #endif  

  return LddDTCStatus;
}

/* polyspace:end<MISRA-C:5.1:Not a defect:Justify with annotations> This
 * Identifier is Specification. */

/*******************************************************************************
** Function Name        : Dem_InternalClearDTC                                **
**                                                                            **
** Service ID           : 0x22                                                **
**                                                                            **
** Description          : This API shall be used to clear single DTC's as     **
**                        well as group of DTC's                              **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : ClientId, DTC, DTCFormat, DTCOrigin                 **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : The API Dem_PreInit(), Dem_Init()                   **
**                        should have been called in sequence                 **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
/* polyspace +1 CODE-METRICS:FXLN CODE-METRICS:LEVEL [Not a defect:Low] "Not a defect" */
FUNC(Std_ReturnType, DEM_CODE) Dem_InternalClearDTC(
    Dem_ClientIdType ClientId,
    uint32 DTC,
    Dem_DTCFormatType DTCFormat,
    Dem_DTCOriginType DTCOrigin)
{
  Std_ReturnType LddRetVal = DEM_CLEAR_FAILED;

  if (DEM_INIT != Dem_GucInit)
  {
    /* @Trace: Dem_SUD_API_10803 */
    DEM_REPORT_ERROR(DEM_CLEARDTC_SID, DEM_E_UNINIT);
  }
  /* @Trace: Dem_SUD_API_11625 */
  #if (DEM_NUMBER_OF_DEM_CLIENT > DEM_ZERO)
  else if (ClientId >= DEM_NUMBER_OF_DEM_CLIENT)
  {
    /* @Trace: Dem_SUD_API_11617 */
    /* @Trace: Dem_SUD_API_11627 */
    DEM_REPORT_ERROR(DEM_CLEARDTC_SID, DEM_E_PARAM_DATA);
  }
  #endif
  else if ((DEM_DTC_FORMAT_OBD != DTCFormat) &&
          #if (DEM_J1979_2_OBD_ON_UDS == STD_ON)
          /* Trace: DEM_19792_42_04 */
           (DEM_DTC_FORMAT_OBD_3BYTE != DTCFormat) &&
          #endif /*(DEM_J1979_2_OBD_ON_UDS == STD_ON)*/
           (DEM_DTC_FORMAT_UDS != DTCFormat) &&
           (DEM_DTC_FORMAT_J1939 != DTCFormat))
  {
    /* @Trace: Dem_SUD_API_11626 */
    /* @Trace: Dem_SUD_API_10804 */
    DEM_REPORT_ERROR(DEM_CLEARDTC_SID, DEM_E_PARAM_CONFIG); 
  }
  /* checks supported DTCOrigin in ECU */  
  else if (DEM_FALSE == Dem_EvMem_DTCOriginIsValid(DTCOrigin))
  {
    /* @Trace: Dem_SUD_API_10802 */
    DEM_REPORT_ERROR(DEM_CLEARDTC_SID, DEM_E_PARAM_CONFIG);
    LddRetVal = DEM_WRONG_DTCORIGIN;
  }
  else 
  {
    SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();
    if ((DEM_FALSE == Dem_ClearDtcState[ClientId].cds_RequestCancel) ||
       ((DEM_TRUE == Dem_ClearDtcState[ClientId].cds_RequestCancel) &&
       ((DEM_CLEARDTC_STATE_AFTER_CLEAROK ==
           Dem_ClearDtcState[ClientId].cds_State) || /* return pending */
        (DEM_CLEARDTC_STATE_READY == Dem_ClearDtcState[ClientId].cds_State))
        /* new request can be accepted */
       /* other states shall be processed in Dem_EvMem_MainFunctionClearDtc */
       ))
    {
      switch (Dem_ClearDtcState[ClientId].cds_State)
      {  
        case DEM_CLEARDTC_STATE_READY:   
          /* @Trace: Dem_SUD_API_10806 */

          Dem_ClearDtcState[ClientId].cds_State =
                  DEM_CLEARDTC_STATE_PREPARE_CLEARDTC;
          SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();
          
          Dem_ClearDtcState[ClientId].cds_RequestCancel = DEM_FALSE;
          Dem_ClearDtcState[ClientId].cds_DTC = DTC;
          Dem_ClearDtcState[ClientId].cds_DTCFormat = DTCFormat;
          Dem_ClearDtcState[ClientId].cds_DTCOrigin = DTCOrigin;
          Dem_ClearDtcState[ClientId].cds_ClientIdRef = ClientId;
          Dem_ClearDtcState[ClientId].cds_Result = DEM_CLEAR_FAILED;
          Dem_ClearDtcState[ClientId].cds_MemLocation = DEM_ZERO;
          LddRetVal = DEM_WRONG_DTC;
          
          /* Single DTC - Note: E_NOT_OK means Single DTC  */
          if (E_NOT_OK == Dem_DTCGroupIsValid(DTC, DTCFormat))
          { 
            /* @Trace: SWS_Dem_00718
             * In Master, Primary and Dependent / Secondary ECUs executing
             * service $04 shall clear all emission-related diagnostic
             * information in primary and user defined (event) memory
             * (if configured) as defined in SAE J1979 [18].
             */             
            if (DEM_DTC_FORMAT_UDS == DTCFormat)
            {      
              Dem_EventIdType LddEventId = Dem_GetEventIdByDTC(
                  DEM_CLEARDTC_SID, DTC, DTCFormat);
              /* if (DEM_TRUE == Dem_EventIdIsValid(LddEventId)) */
              /* @Trace: Dem_SUD_API_11632 */
              if (( LddEventId <= DEM_NUMBER_OF_EVENTS) &&
                  ( DEM_NO_EVENT != LddEventId))
              {
                Dem_CombinedDtcPCType LddCbDTC =
                         Dem_GetCbDTCByEventId(LddEventId);
                /* Only clear the event(s) assigned to a single DTC */
                /* @Trace: Dem_SUD_API_11631 */
                if (DEM_TRUE == Dem_EvMem_DTCFormatIsValid(DTCFormat,
                        LddCbDTC)) /* DEM_DTC_FORMAT_UDS */
                {
                  if (DEM_TRUE == Dem_DTCOriginBelongToEvent(LddEventId,
                         DTCOrigin))
                  {
                    /* @Trace: Dem_SUD_API_11629 */
                    Dem_ClearDtcState[ClientId].cds_EventIdRef = LddEventId;
                    LddRetVal = DEM_PENDING;
                  }
                  else
                  {
                    /* @Trace: Dem_SUD_API_11630 */
                    LddRetVal = DEM_WRONG_DTCORIGIN;
                  }
                }
              }
            }
            #if (DEM_J1979_2_OBD_ON_UDS == STD_ON)
             /* Trace: DEM_19792_42_04 */
            else if ((DEM_DTC_FORMAT_OBD == DTCFormat) || (DEM_DTC_FORMAT_OBD_3BYTE == DTCFormat)) /*OBD*/
            #else
            else if (DEM_DTC_FORMAT_OBD == DTCFormat) /*OBD*/
            #endif /*(DEM_J1979_2_OBD_ON_UDS == STD_ON)*/
            {
              Dem_EventIdType LddEventId = Dem_GetEventIdByDTC(
                  DEM_CLEARDTC_SID, DTC, DTCFormat);

              /* if (DEM_TRUE == Dem_EventIdIsValid(LddEventId)) */
              /* @Trace: Dem_SUD_API_11621 */
              if (( LddEventId <= DEM_NUMBER_OF_EVENTS) &&
                  ( DEM_NO_EVENT != LddEventId))
              {
                Dem_CombinedDtcPCType LddCbDTC = Dem_GetCbDTCByEventId(
                    LddEventId);
                /* Only clear the event(s) assigned to a single DTC */
                /* @Trace: Dem_SUD_API_10809 */
                if (DEM_TRUE == Dem_EvMem_DTCFormatIsValid(DTCFormat, LddCbDTC))
                  /* DEM_DTC_FORMAT_UDS */
                {
                  if (DEM_TRUE == Dem_DTCOriginBelongToEvent(LddEventId,
                       DTCOrigin))
                  {
                    /* @Trace: Dem_SUD_API_11622 */
                    Dem_ClearDtcState[ClientId].cds_EventIdRef = LddEventId;
                    LddRetVal = DEM_PENDING;
                  }
                  else
                  {
                    /* @Trace: Dem_SUD_API_11623 */
                    LddRetVal = DEM_WRONG_DTCORIGIN;
                  }
                }
              }
            }
            else
            {
              /* @Trace: Dem_SUD_API_11620 */
              /* Nothing to do */
            }
          }
          /* Group DTC */
          else
          {
            /* @Trace: Dem_SUD_API_11619 */
            Dem_ClearDtcState[ClientId].cds_EventIdRef = DEM_NO_EVENT;
            /* If event is null-ptr, DTC is DTC Group */
            LddRetVal = DEM_PENDING;
          }      
          /* @Trace: Dem_SUD_API_11618 */
          if (DEM_PENDING != LddRetVal)
          {
            /* @Trace: Dem_SUD_API_11624 */
            SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();
            Dem_ClearDtcState[ClientId].cds_State = DEM_CLEARDTC_STATE_READY;
            SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();            
            DEM_REPORT_ERROR(DEM_CLEARDTC_SID, DEM_E_PARAM_DATA);   
          }
          break;

        case DEM_CLEARDTC_STATE_PREPARE_CLEARDTC: /* @No break; */
        case DEM_CLEARDTC_STATE_RUNNING: /* @No break; */
        case DEM_CLEARDTC_STATE_CLEAR_EVMEM: /* @No break; */        
        case DEM_CLEARDTC_STATE_WAIT:    /* @No break; */
        case DEM_CLEARDTC_STATE_AFTER_CLEAROK: 
          /* @Trace: Dem_SUD_API_10807 */
          SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();

          /* Note: DEM_CLEARDTC_STATE_AFTER_CLEAROK
           * If new request is accepted and Dem don't completed previous
           * request's job yet, The dem returns DEM_PENDING , and after
           * finishing job , Dem will process new request */
          LddRetVal = DEM_PENDING;
          break;            
        case DEM_CLEARDTC_STATE_RESULT:
          /* @Trace: Dem_SUD_API_11628 */
          Dem_ClearDtcState[ClientId].cds_State =
                        DEM_CLEARDTC_STATE_AFTER_CLEAROK;
          SchM_Exit_Dem_REQUEST_STATUS_PROTECTION(); 

          LddRetVal = Dem_ClearDtcState[ClientId].cds_Result;
          break;      
        /* polyspace<RTE:UNR:Not a defect:No action planned> No error.
         * Avoid to 'Unreachable code' of the polyspace */
        default:
          /* @Trace: Dem_SUD_API_10808 */
          SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();
          LddRetVal = DEM_CLEAR_FAILED;
          DEM_REPORT_ERROR(DEM_CLEARDTC_SID, DEM_E_UNEXPECTED_RESULT);    
          break;  
      }
    }
    else
    {
      /* @Trace: Dem_SUD_API_10805 */
      SchM_Exit_Dem_REQUEST_STATUS_PROTECTION(); 
    }
  }
  return LddRetVal;
}

/******************************************************************************
 * Function Name        : Dem_SelectedDTCServiceIsLock
 *
 * Service ID           : None
 *
 * Description          : This function is used to check whether selected DTC
 *                        service is lock
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Reentrant
 *
 * Input Parameters     : ClientId
 *                        ServiceId
 *
 * InOut parameter      : None
 *
 * Output Parameters    : None
 *
 * Return parameter     : boolean
 *
 * Preconditions        : None
 *
 * Remarks              :
 *****************************************************************************/
FUNC(boolean, DEM_CODE) Dem_SelectedDTCServiceIsLock(
  uint8 ClientId,
  uint8 ServiceId)
{
  boolean LddRetVal = DEM_FALSE;
  /* @Trace: Dem_SUD_API_11634 */
  #if (DEM_NUMBER_OF_DEM_CLIENT > DEM_ZERO)
  /* @Trace: Dem_SUD_API_11635 */
  if ((ClientId < DEM_NUMBER_OF_DEM_CLIENT) &&
      (ServiceId < DEM_MAXIMUM_CLEARDTC_SID_LOCKID))
  {
    /* @Trace: Dem_SUD_API_11636 */
    if (DEM_TRUE == Dem_ClientSelectDtcState[ClientId].isLockService[ServiceId])
    {
      /* @Trace: Dem_SUD_API_11633 */
      LddRetVal = DEM_TRUE;
    }
  }
  #endif
  return LddRetVal;
}

/******************************************************************************
 * Function Name        : Dem_SelectedDTCServiceLock
 *
 * Service ID           : None
 *
 * Description          : This function is used to lock the selected DTC
 *                        service
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Reentrant
 *
 * Input Parameters     : ClientId
 *                        ServiceId
 *
 * InOut parameter      : None
 *
 * Output Parameters    : None
 *
 * Return parameter     : void
 *
 * Preconditions        : None
 *
 * Remarks              :
 *****************************************************************************/
/* polyspace +1 CODE-METRICS:CALLING [Not a defect:Low] "Not a defect" */
FUNC(void, DEM_CODE) Dem_SelectedDTCServiceLock(
  uint8 ClientId,
  uint8 ServiceId)
{
  /* @Trace: Dem_SUD_API_11638 */
  #if (DEM_NUMBER_OF_DEM_CLIENT > DEM_ZERO)
  /* @Trace: Dem_SUD_API_11639 */
  if ((ClientId < DEM_NUMBER_OF_DEM_CLIENT) &&
      (ServiceId < DEM_MAXIMUM_CLEARDTC_SID_LOCKID))
  {
    /* @Trace: Dem_SUD_API_11637 */
    Dem_ClientSelectDtcState[ClientId].isLockService[ServiceId] = DEM_TRUE;
  }
  #endif
}

/******************************************************************************
 * Function Name        : Dem_SelectedDTCServiceUnLock
 *
 * Service ID           : None
 *
 * Description          : This function is used to select unlock the  DTC
 *                        service
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Reentrant
 *
 * Input Parameters     : ClientId
 *                        ServiceId
 *
 * InOut parameter      : None
 *
 * Output Parameters    : None
 *
 * Return parameter     : void
 *
 * Preconditions        : None
 *
 * Remarks              :
 *****************************************************************************/
/* polyspace +1 CODE-METRICS:CALLING [Not a defect:Low] "Not a defect" */
FUNC(void, DEM_CODE) Dem_SelectedDTCServiceUnLock(
  uint8 ClientId,
  uint8 ServiceId)
{
  /* @Trace: Dem_SUD_API_11641 */
  #if (DEM_NUMBER_OF_DEM_CLIENT > DEM_ZERO)
  /* @Trace: Dem_SUD_API_11642 */
  if ((ClientId < DEM_NUMBER_OF_DEM_CLIENT) &&
      (ServiceId < DEM_MAXIMUM_CLEARDTC_SID_LOCKID))
  {
    /* @Trace: Dem_SUD_API_11640 */
    Dem_ClientSelectDtcState[ClientId].isLockService[ServiceId] = DEM_FALSE;
  }
  #endif
}

/******************************************************************************
 * Function Name        : Dem_SetDTCFilterServiceIsLock
 *
 * Service ID           : None
 *
 * Description          : This function is used to check whether set DTC
 *                        filter service is lock
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Reentrant
 *
 * Input Parameters     : ClientId
 *                        ServiceId
 *
 * InOut parameter      : None
 *
 * Output Parameters    : None
 *
 * Return parameter     : boolean
 *
 * Preconditions        : None
 *
 * Remarks              :
 *****************************************************************************/
FUNC(boolean, DEM_CODE) Dem_SetDTCFilterServiceIsLock(
  uint8 ClientId,
  uint8 ServiceId)
{
  boolean LddRetVal = DEM_FALSE;
  /* @Trace: Dem_SUD_API_11643 */
  #if (DEM_NUMBER_OF_DEM_CLIENT > DEM_ZERO)
  /* @Trace: Dem_SUD_API_11644 */
  if ((ClientId < DEM_NUMBER_OF_DEM_CLIENT) &&
      (ServiceId < DEM_MAXIMUM_SETDTCFILTER_SID_LOCKID))
  {
    /* @Trace: Dem_SUD_API_11645 */
    if (DEM_TRUE == Dem_DTCFilterState[ClientId].dfs_isLockService[ServiceId])
    {
      /* @Trace: Dem_SUD_API_11646 */
      LddRetVal = DEM_TRUE;
    }
  }
  #endif
  return LddRetVal;
}

/******************************************************************************
 * Function Name        : Dem_SetDTCFilterServiceLock
 *
 * Service ID           : None
 *
 * Description          : This function is used to lock the set DTC filter
 *                        service
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Reentrant
 *
 * Input Parameters     : ClientId
 *                        ServiceId
 *
 * InOut parameter      : None
 *
 * Output Parameters    : None
 *
 * Return parameter     : void
 *
 * Preconditions        : None
 *
 * Remarks              :
 *****************************************************************************/
FUNC(void, DEM_CODE) Dem_SetDTCFilterServiceLock(
  uint8 ClientId,
  uint8 ServiceId)
{
  /* @Trace: Dem_SUD_API_11647 */
  #if (DEM_NUMBER_OF_DEM_CLIENT > DEM_ZERO)
  /* @Trace: Dem_SUD_API_11648 */
  if ((ClientId < DEM_NUMBER_OF_DEM_CLIENT) &&
      (ServiceId < DEM_MAXIMUM_SETDTCFILTER_SID_LOCKID))
  {
    /* @Trace: Dem_SUD_API_11649 */
    Dem_DTCFilterState[ClientId].dfs_isLockService[ServiceId] = DEM_TRUE;
  }
  #endif
}

/******************************************************************************
 * Function Name        : Dem_SetDTCFilterServiceUnLock
 *
 * Service ID           : None
 *
 * Description          : This function is used to unlock the set DTC filter
 *                        service
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Reentrant
 *
 * Input Parameters     : ClientId
 *                        ServiceId
 *
 * InOut parameter      : None
 *
 * Output Parameters    : None
 *
 * Return parameter     : void
 *
 * Preconditions        : None
 *
 * Remarks              :
 *****************************************************************************/
FUNC(void, DEM_CODE) Dem_SetDTCFilterServiceUnLock(
  uint8 ClientId,
  uint8 ServiceId)
{
  /* @Trace: Dem_SUD_API_11651 */
  #if (DEM_NUMBER_OF_DEM_CLIENT > DEM_ZERO)
  /* @Trace: Dem_SUD_API_11652 */
  if ((ClientId < DEM_NUMBER_OF_DEM_CLIENT) &&
      (ServiceId < DEM_MAXIMUM_SETDTCFILTER_SID_LOCKID))
  {
    /* @Trace: Dem_SUD_API_11650 */
    Dem_DTCFilterState[ClientId].dfs_isLockService[ServiceId] = DEM_FALSE;
  }
  #endif
}

/******************************************************************************
 * Function Name        : Dem_SetFFRecordFilterServiceIsLock
 *
 * Service ID           : None
 *
 * Description          : This function is used to check whether set FF record
 *                        filter service is lock
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Reentrant
 *
 * Input Parameters     : ClientId
 *                        ServiceId
 *
 * InOut parameter      : None
 *
 * Output Parameters    : None
 *
 * Return parameter     : boolean
 *
 * Preconditions        : None
 *
 * Remarks              :
 *****************************************************************************/
FUNC(boolean, DEM_CODE) Dem_SetFFRecordFilterServiceIsLock(
  uint8 ClientId,
  uint8 ServiceId)
{
  boolean LddRetVal = DEM_FALSE;
  /* @Trace: Dem_SUD_API_11654 */
  #if (DEM_NUMBER_OF_DEM_CLIENT > DEM_ZERO)
  /* @Trace: Dem_SUD_API_11655 */
  if ((ClientId < DEM_NUMBER_OF_DEM_CLIENT) &&
      (ServiceId < DEM_MAXIMUM_SETFREEZEFRAMERECORDFILTER_SID_LOCKID))
  {
    /* @Trace: Dem_SUD_API_11656 */
    if (DEM_TRUE == Dem_FilteredFFRecord[ClientId].isLockService[ServiceId])
    {
      /* @Trace: Dem_SUD_API_11653 */
      LddRetVal = DEM_TRUE;
    }
  }
  #endif
  return LddRetVal;
}

/******************************************************************************
 * Function Name        : Dem_SetFFRecordFilterServiceLock
 *
 * Service ID           : None
 *
 * Description          : This function is used to lock the set FF record
 *                        filter service
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Reentrant
 *
 * Input Parameters     : ClientId
 *                        ServiceId
 *
 * InOut parameter      : None
 *
 * Output Parameters    : None
 *
 * Return parameter     : void
 *
 * Preconditions        : None
 *
 * Remarks              :
 *****************************************************************************/
FUNC(void, DEM_CODE) Dem_SetFFRecordFilterServiceLock(
  uint8 ClientId,
  uint8 ServiceId)
{
  /* @Trace: Dem_SUD_API_11658 */
  #if (DEM_NUMBER_OF_DEM_CLIENT > DEM_ZERO)
  /* @Trace: Dem_SUD_API_11659 */
  if ((ClientId < DEM_NUMBER_OF_DEM_CLIENT) &&
      (ServiceId < DEM_MAXIMUM_SETFREEZEFRAMERECORDFILTER_SID_LOCKID))
  {
    /* @Trace: Dem_SUD_API_11657 */
    Dem_FilteredFFRecord[ClientId].isLockService[ServiceId] = DEM_TRUE;
  }
  #endif
}

/******************************************************************************
 * Function Name        : Dem_SetFFRecordFilterServiceUnLock
 *
 * Service ID           : None
 *
 * Description          : This function is used to unlock the set FF record
 *                        filter service
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Reentrant
 *
 * Input Parameters     : ClientId
 *                        ServiceId
 *
 * InOut parameter      : None
 *
 * Output Parameters    : None
 *
 * Return parameter     : void
 *
 * Preconditions        : None
 *
 * Remarks              :
 *****************************************************************************/
FUNC(void, DEM_CODE) Dem_SetFFRecordFilterServiceUnLock(
  uint8 ClientId,
  uint8 ServiceId)
{
  /* @Trace: Dem_SUD_API_11662 */
  #if (DEM_NUMBER_OF_DEM_CLIENT > DEM_ZERO)
  /* @Trace: Dem_SUD_API_11661 */
  if ((ClientId < DEM_NUMBER_OF_DEM_CLIENT) &&
      (ServiceId < DEM_MAXIMUM_SETFREEZEFRAMERECORDFILTER_SID_LOCKID))
  {
    /* @Trace: Dem_SUD_API_11660 */
    Dem_FilteredFFRecord[ClientId].isLockService[ServiceId] = DEM_FALSE;
  }
  #endif
}

/******************************************************************************
 * Function Name        : Dem_CheckStatusOfSelectedDTCServices
 *
 * Service ID           : None
 *
 * Description          : This function is used to check status of selected DTC
 *                        services
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Reentrant
 *
 * Input Parameters     : ClientId
 *                        ServiceId
 *                        ServiceIdIndex
 *
 * InOut parameter      : None
 *
 * Output Parameters    : None
 *
 * Return parameter     : void
 *
 * Preconditions        : None
 *
 * Remarks              :
 *****************************************************************************/
/* @Trace: SRS_Diag_04010 SRS_Diag_04065 SRS_Diag_04122
 */
/* polyspace +1 CODE-METRICS:CALLING CODE-METRICS:PATH [Not a defect:Low] "Not a defect" */
FUNC(Std_ReturnType, DEM_CODE) Dem_CheckStatusOfSelectedDTCServices(
  uint8 ClientId,
  uint8 ServiceId,
  uint16 ServiceIdIndex)
{
  Std_ReturnType LddRetVal = E_OK;
  /* @Trace: Dem_SUD_API_11663 */
  #if (DEM_NUMBER_OF_DEM_CLIENT > DEM_ZERO)
  /* @Trace: Dem_SUD_API_11674 */
  if (ClientId < DEM_NUMBER_OF_DEM_CLIENT)
  {
    uint16 LusServiceIdIndex = ServiceIdIndex;
    boolean LblGetSeverityOfDTCSIDLockIdx =
        Dem_SelectedDTCServiceIsLock(ClientId,
            DEM_GETSEVERITYOFDTC_SID_LOCK_IDX);

    boolean LblSelectDTCSIDLockIdx =
        Dem_SelectedDTCServiceIsLock(ClientId,
            DEM_SELECTDTC_SID_LOCK_IDX);

    boolean LblClearDTCSIDLockIdx =
        Dem_SelectedDTCServiceIsLock(ClientId,
            DEM_CLEARDTC_SID_LOCK_IDX);

    boolean LblGetFunctionalUnitOfDTCSIDLockIdx =
        Dem_SelectedDTCServiceIsLock(ClientId,
            DEM_GETFUNCTIONALUNITOFDTC_SID_LOCK_IDX);

    boolean LblSelectFreezeFrameDataSIDLockIdx =
        Dem_SelectedDTCServiceIsLock(ClientId,
            DEM_SELECTFREEZEFRAMEDATA_SID_LOCK_IDX);

    boolean LblSelectExtendedDataRecordSIDLockIdx =
        Dem_SelectedDTCServiceIsLock(ClientId,
            DEM_SELECTEXTENDEDDATARECORD_SID_LOCK_IDX);

    boolean LblSetDTCSuppressionSIDLockIdx =
        Dem_SelectedDTCServiceIsLock(ClientId,
            DEM_SETDTCSUPPRESSION_SID_LOCK_IDX);

    boolean LblGetDTCSuppressionSIDLockIdx =
        Dem_SelectedDTCServiceIsLock(ClientId,
            DEM_GETDTCSUPPRESSION_SID_LOCK_IDX);

    switch (ServiceId)
    {
      case DEM_GETSEVERITYOFDTC_SID :
      {
        /* @Trace: Dem_SUD_API_11682 */
        if (DEM_TRUE == LblGetSeverityOfDTCSIDLockIdx)
        {
          /* @Trace: Dem_SUD_API_11680 */
          LusServiceIdIndex &= ~(uint16)DEM_BIT6_MASK1;
          LddRetVal = DEM_PENDING;
        }
        break;
      }
      case DEM_CLEARDTC_SID :
      {
        if (DEM_TRUE == LblClearDTCSIDLockIdx)
        {
          /* @Trace: Dem_SUD_API_11681 */
          LusServiceIdIndex &= ~(uint16)DEM_BIT1_MASK1;
          /* @Trace: SWS_Dem_00664
           * If the clear DTC process is started by one client and still
           * ongoing, then in case another client calls Dem_ClearDTC, the Dem
           * shall return DEM_PENDING */
          LddRetVal = DEM_PENDING;
        }
        else if (DEM_TRUE == LblSelectDTCSIDLockIdx)
        {
          /* @Trace: Dem_SUD_API_11683 */
          LddRetVal = DEM_CLEAR_BUSY;
        }
        else
        {
          /* @Trace: Dem_SUD_API_11684 */
          /* Nothing to do */
        }
        break;
      }
      case DEM_SELECTDTC_SID :
      {
        /* @Trace: Dem_SUD_API_11686 */
        if (DEM_TRUE == LblSelectDTCSIDLockIdx)
        {
          /* @Trace: Dem_SUD_API_11685 */
          LusServiceIdIndex &= ~(uint16)DEM_BIT0_MASK1;
          LddRetVal = DEM_BUSY;
        }
        break;
      }
      case DEM_GETFUNCTIONALUNITOFDTC_SID :
      {
        /* @Trace: Dem_SUD_API_11664 */
        if (DEM_TRUE == LblGetFunctionalUnitOfDTCSIDLockIdx)
        {
          /* @Trace: Dem_SUD_API_11665 */
          LusServiceIdIndex &= ~(uint16)DEM_BIT5_MASK1;
          LddRetVal = DEM_PENDING;
        }
        break;
      }
      case DEM_SELECTFREEZEFRAMEDATA_SID :
      {
        /* @Trace: Dem_SUD_API_11667 */
        if (DEM_TRUE == LblSelectFreezeFrameDataSIDLockIdx)
        {
          /* @Trace: Dem_SUD_API_11666 */
          LusServiceIdIndex &= ~(uint16)DEM_BIT8_MASK1;
          LddRetVal = DEM_PENDING;
        }
        break;
      }
      case DEM_SELECTEXTENDEDDATARECORD_SID :
      {
        /* @Trace: Dem_SUD_API_11669 */
        if (DEM_TRUE == LblSelectExtendedDataRecordSIDLockIdx)
        {
          /* @Trace: Dem_SUD_API_11668 */
          LusServiceIdIndex &= ~(uint16)DEM_BIT9_MASK1;
          LddRetVal = DEM_PENDING;
        }
        break;
      }
      case DEM_SETDTCSUPPRESSION_SID :
      {
        /* @Trace: Dem_SUD_API_11671 */
        if (DEM_TRUE == LblSetDTCSuppressionSIDLockIdx)
        {
          /* @Trace: Dem_SUD_API_11670 */
          LusServiceIdIndex &= ~(uint16)DEM_BIT10_MASK1;
          LddRetVal = DEM_PENDING;
        }
        break;
      }
      case DEM_GETDTCSUPPRESSION_SID :
      {
        if (DEM_TRUE == LblGetDTCSuppressionSIDLockIdx)
        {
          /* @Trace: Dem_SUD_API_11672 */
          LusServiceIdIndex &= ~(uint16)DEM_BIT11_MASK1;
          LddRetVal = DEM_PENDING;
        }
        break;
      }
      default :
      {
        /* @Trace: Dem_SUD_API_11673 */
        /* Nothing to do */
        break;
      }
    }
    /* @Trace: Dem_SUD_API_11675 */
    if (E_OK == LddRetVal)
    {
      boolean LblSelectedDTCServiceIsLock = DEM_FALSE;
      /* @Trace: Dem_SUD_API_11676 */
      for (uint8 LucIdx = DEM_ZERO; LucIdx < DEM_TWELVE; LucIdx++)
      {
        uint16 LusBitMask = (uint16)DEM_ONE << (uint16)LucIdx;
        /* @Trace: Dem_SUD_API_11677 */
        if (LusBitMask == (LusServiceIdIndex & LusBitMask))
        {
          LblSelectedDTCServiceIsLock = Dem_SelectedDTCServiceIsLock(ClientId,
              LucIdx);
          /* @Trace: Dem_SUD_API_11678 */
          if (DEM_TRUE == LblSelectedDTCServiceIsLock)
          {
            /* @Trace: Dem_SUD_API_11679 */
            /* @Trace: SWS_Dem_01305
             * Behavior if one client starting a new operation while the
             * previous one is  still running In case any of the Dem_SelectDTC
             * related APIs according to [SWS_Dem_01253] is called by one client
             * and the same client has already started another Dem_SelectDTC
             * related operation according to [SWS_Dem_01253] and this different
             * operation is not completed, the Dem shall return DEM_BUSY.
             * */

            /* @Trace: SWS_Dem_01306
             * Behavior if one client calling Dem_SelectDTC before the previous
             * operation finished If Dem_SelectDTC is called by one client and
             * the same client is calling Dem_SelectDTC again and the Dem is
             * currently still processing the previous operation based on
             * Dem_SelectDTC according to [SWS_Dem_01253], the Dem shall return
             * DEM_BUSY.
             * */
            LddRetVal = DEM_BUSY;
            break;
          }
        }
      }
    }
  }
  #endif

  return LddRetVal;
}
#define DEM_STOP_SEC_CODE
#include "MemMap.h"

/* polyspace:end<MISRA-C:1.1:Not a defect:No action planned> Not a defect  */



