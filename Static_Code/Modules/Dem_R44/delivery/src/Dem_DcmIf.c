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
**  SRC-MODULE: Dem_DcmIf.c                                                   **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostic Event Manager                              **
**                                                                            **
**  PURPOSE   : Provision of Dcm interface functionality                      **
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
** 2.1.0.0   29-Mar-2024   EK Kim        Jira #CP44-3819                      **
** 2.0.0.0   31-Dec-2023   EK Kim        Jira #CP44-1515 #CP44-3198 #CP44-3298**
** 1.0.16    28-Nov-2023   DanhTQ1       #CP44-3052                           **
** 1.0.7.0   10-Nov-2022   SY Kim        #CP44-1115                           **
** 1.0.6.0   21-Oct-2022   LanhLT        #CP44-863                            **
** 1.0.1.0   07-May-2021   HaoLT6        R44-Redmine #18724                   **
** 1.0.0     26-Feb-2021   EK Kim        Initial version                      **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Dem.h"                /* DEM module Header File */
#include "Dem_Ram.h"            /* DEM Ram Header File */
#if (DEM_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"                /* Det Header File */
#endif

#include "NvM.h"              /* NVRAM manager symbols Header File */

#include "SchM_Dem.h"       /* Basic s/w module Scheduler symbols Header File */

#include "Dem_Types.h"
#include "Dem_Event.h"
#include "Dem_Dtc.h"
#include "Dem_EventMemory.h"
#include "Dem_EventRelatedData.h"
#include "Dem_EventCallback.h"
#if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
#include "Dem_Obd.h"
#endif

#if (DEM_J1979_2_OBD_ON_UDS == STD_ON)
#include "Dcm.h"
#endif
/* polyspace:begin<MISRA-C:1.1:Not a defect:Justify with annotations> Not a
 * defect */

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

#define DEM_START_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
    

/*******************************************************************************
** Function Name        : Dem_SetDTCFilter                                    **
**                                                                            **
** Service ID           : 0x13                                                **
**                                                                            **
** Description          : The server shall perform a bit-wise logical AND-    **
**                        ing operation between the mask specified in the     **
**                        client's request and the actual status associated   **
**                        with each DTC supported by the server. In addition  **
**                        to the DTCStatusAvailabilityMask, the server shall  **
**                        return all DTCs for which the result of the AND-    **
**                        ing operation is non-zero [i.e. (statusOfDTC &      **
**                        DTCStatusMask) != 0]. If the client specifies a     **
**                        status mask that contains bits that the server      **
**                        does not support, then the server shall process     **
**                        the DTC information using only the bits that it     **
**                        does support. If no DTCs within the server match    **
**                        the masking criteria specified in the client's      **
**                        request, no DTC or status information shall be      **
**                        provided following the DTCStatusAvailabilityMask    **
**                        byte in the positive response message (statusOf     **
**                        DTC & DTCStatusMask) & (severity & DTCSeverity      **
**                        Mask) != 0                                          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : DTCStatusMask, DTCOrigin, DTCFormat                 **
**                        FilterWithSeverity, DTCSeverityMask                 **
**                        FilterForFaultDetectionCounter                      **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Dem_ReturnSetFilterType                             **
**                                                                            **
** Preconditions        : The API Dem_Init()                                  **
**                        should have been called in sequence                 **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
/* @Trace: SRS_BSW_00369 SRS_Diag_04057 SRS_Diag_04162 SRS_Diag_04220
           SRS_Diag_04000 SRS_Diag_04164
 */
/* @Trace: Dem_SUD_MACRO_036 */
/* polyspace +1 CODE-METRICS:LEVEL [Not a defect:LOW] "Not a defect" */ 
FUNC(Std_ReturnType, DEM_CODE) Dem_SetDTCFilter(
        uint8 ClientId,
        uint8 DTCStatusMask,
        Dem_DTCFormatType DTCFormat,
        Dem_DTCOriginType DTCOrigin,
        boolean FilterWithSeverity,
        Dem_DTCSeverityType DTCSeverityMask,
        boolean FilterForFaultDetectionCounter)
{

  /* @Trace: SWS_Dem_00301
   * The Dem shall provide the ability to access the non-volatile
   * stored Permanent DTC by filtering for permanent DTCs to the Dcm
   * (refer to Dem_SetDTCFilter and Dem_GetNextFilteredDTC).*/

  /* @Trace: SWS_Dem_00057
   * The function Dem_SetDTCFilter shall set the filter criteria for the client
   *  with the same client ID for subsequent calls
   * */

  /* @Trace: SWS_Dem_01300
   * API behavior without set DTC filter
   * If any of the APIs requiring a Dem_SetDTCFilter according to
   * [SWS_Dem_00057] is called without
   * a prior call of Dem_SetDTCFilter for this client, the Dem shall report the
   * Det DEM_E_WRONG_CONDITION.
   * */

  /* @Trace: SWS_Dem_01265
   * IF Dem_SetDTCFilter is called with an invalid DTCStatusMask, the Dem shall
   * return E_NOT_OK.
   * 0x00: Autosar-specific value to deactivate the status-byte filtering
   * (different meaning than in ISO 14229-1) to report all supported DTCs
   * (used for service 0x19 subfunctions 0x0A/0x15)
   *
   * 0x01..0xFF: Status-byte mask according to ISO 14229-1 DTCStatusMask
   * (handed over by Dcm from service request directly) to filter for DTCs with
   * at least one status bit set matching this status-byte mask
   * */
  Std_ReturnType LddRetVal = E_OK;

  boolean LblSetDTCFilterSIDLockIdx = Dem_SetDTCFilterServiceIsLock(ClientId,
      DEM_SETDTCFILTER_SID_LOCK_IDX);
  /* @Trace: Dem_SUD_API_20275 */
  #if (DEM_NUMBER_OF_DEM_CLIENT > DEM_ZERO)
  if (ClientId >= DEM_NUMBER_OF_DEM_CLIENT)
  {
    /* @Trace: Dem_SUD_API_20288 */
    DEM_REPORT_ERROR(DEM_SETDTCFILTER_SID, DEM_E_PARAM_DATA);
    LddRetVal = E_NOT_OK;
  }
  else
  #endif
  /* @Trace: Dem_SUD_API_20283 */
  if (DEM_TRUE == LblSetDTCFilterSIDLockIdx)
  {
    /* @Trace: Dem_SUD_API_20064 */
    LddRetVal = E_NOT_OK;
  }
  else
  {
    Dem_SetDTCFilterServiceLock(ClientId, DEM_SETDTCFILTER_SID_LOCK_IDX);
    /* Module initialization check */
    if (Dem_GucInit != DEM_INIT)
    {
      /* @Trace: Dem_SUD_API_20289 */
      DEM_REPORT_ERROR(DEM_SETDTCFILTER_SID, DEM_E_UNINIT);
      LddRetVal = E_NOT_OK;
    }
    /* DTCOrigin check */
    else if ((boolean) DEM_FALSE == Dem_EvMem_DTCOriginIsValid(DTCOrigin))
    {
      /* @Trace: SWS_Dem_01264
       * IF Dem_SetDTCFilter is called with an invalid DTCOrigin, the Dem shall
       * return E_NOT_OK.
       * */
      /* @Trace: SWS_Dem_01067
       * The Det error DEM_E_WRONG_CONFIGURATION shall be reported if the
       * function Dem_SetDTCFilter is called with a value of the parameter
       * DTCOrigin that is not supported per configuration (e.g.
       * if DTCOrigin "DEM_DTC_ORIGIN_MIRROR_MEMORY" is passed, but no mirror
       * memory is configured).
       * */
      /* @Trace: Dem_SUD_API_20290 */
      DEM_REPORT_ERROR( DEM_SETDTCFILTER_SID, DEM_E_WRONG_CONFIGURATION);
      LddRetVal = E_NOT_OK;
    }
    /* DTCFormat check */
    else if ((DTCFormat != DEM_DTC_FORMAT_UDS)
            #if (DEM_J1979_2_OBD_ON_UDS == STD_ON)
            /* Trace: DEM_19792_42_04 */
            && (DTCFormat != DEM_DTC_FORMAT_OBD_3BYTE)
            #endif /*(DEM_J1979_2_OBD_ON_UDS == STD_ON)*/
            #if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
            && (DTCFormat != DEM_DTC_FORMAT_OBD)
            #endif
        )
    {
      /* @Trace: SWS_Dem_01066
       * The Det error DEM_E_WRONG_CONFIGURATION shall be reported if the
       * function Dem_SetDTCFilter is called with a value of the parameter
       * DTCFormat that is not supported per configuration (e.g. if DTCFormat
       * = DEM_DTC_FORMAT_OBD is passed, but OBD is not supported per
       * configuration).
       * */
      /* @Trace: Dem_SUD_API_20276 */
      DEM_REPORT_ERROR(DEM_SETDTCFILTER_SID, DEM_E_WRONG_CONFIGURATION);
      LddRetVal = E_NOT_OK;
    }
    /* FilterwithSeverity input is not defined */
    else if ((FilterWithSeverity != DEM_TRUE ) &&
             (FilterWithSeverity != DEM_FALSE ))
    {
      /* @Trace: Dem_SUD_API_20277 */
      DEM_REPORT_ERROR(DEM_SETDTCFILTER_SID, DEM_E_PARAM_DATA);
      LddRetVal = E_NOT_OK;
    }
    /* FilterForFaultDetectionCounter input is not defined */
    else if ((FilterForFaultDetectionCounter != DEM_TRUE ) &&
             (FilterForFaultDetectionCounter != DEM_FALSE ))
    {
      /* @Trace: Dem_SUD_API_20278 */
      DEM_REPORT_ERROR(DEM_SETDTCFILTER_SID, DEM_E_PARAM_DATA);
      LddRetVal = E_NOT_OK;
    }
    /* @ISO 14229 11.3.1.9
     * (((statusOfDTC & DTCStatusMask) !=0) &&
     * ((severity & DTCSeverityMask) != 0)) == TRUE
     */
     /* polyspace-begin DEFECT:DEAD_CODE [Justified:Low] Dead Code by User Defined. */
     /* polyspace-begin MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] "Same as Dead Code" */
    else if ((DTCSeverityMask !=
                (Dem_DTCSeverityType) DEM_DTC_SEV_NO_SEVERITY) &&
            ((DTCSeverityMask & (Dem_DTCSeverityType) DEM_DTC_SEV_MASK) ==
                DEM_ZERO))
    {
      /* @Trace: Dem_SUD_API_20279 */
      DEM_REPORT_ERROR(DEM_SETDTCFILTER_SID, DEM_E_PARAM_DATA);
      LddRetVal = E_NOT_OK;
    }
    /* polyspace-end MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] Same as Dead Code. */
    /* polyspace-end DEFECT:DEAD_CODE [Justified:Low] Dead Code by User Defined. */
    else
    {
      /* @Trace: SWS_Dem_01263
       * A call of Dem_SetDTCFilter sets the requested filter on the event
       * memory assigned to ClientID of the call.
       * */

      /* @Trace: SWS_Dem_00649
       * Each call of Dem_SetDTCFilter shall lead to a reset of the sequence
       * for that client.
       * */

      Dem_EventIdType LddEventId;
      for ( LddEventId = DEM_ONE; LddEventId <= DEM_NUMBER_OF_EVENTS;
            LddEventId++)
      {
        /* @Trace: SWS_Dem_01101
         * A suppressed DTC shall not be visible for the following Dcm
         * query-functions; therefore the following functions shall treat the
         * DTC as if filter is not matching.
         * */
        /* @Trace: Dem_SUD_API_20280 */
        if (DEM_TRUE != Dem_EvIsProcStateTriggered(LddEventId,
            DEM_EVPROCSTATE_DTC_SUPP))
        {
          /* @Trace: Dem_SUD_API_20282 */
          if ((DEM_NO_EVMEM_IDX != Dem_Event[LddEventId - DEM_ONE]
              .ucEventMemDstIdx)
              #if (DEM_NUMBER_OF_DEM_CLIENT > DEM_ZERO)
              && (Dem_Client[ClientId].usDemEventMemorySetId ==
                  Dem_Event[LddEventId - DEM_ONE].ucEventMemDstIdx)
              #endif
              )
          {
            /* @Trace: Dem_SUD_API_20281 */
            Dem_EvClearProcState(LddEventId, DEM_EVPROCSTATE_DTC_FILTER);
          }
        }
      }
      /* @Trace: Dem_SUD_API_20065 , Dem_SUD_API_20285*/
      Dem_DTCFilterState[ClientId].dfs_DTCOrigin = DTCOrigin;
      Dem_DTCFilterState[ClientId].dfs_FilterForFDC =
          FilterForFaultDetectionCounter;
      Dem_DTCFilterState[ClientId].dfs_DTCSeverityMask = DTCSeverityMask;
      Dem_DTCFilterState[ClientId].dfs_FilterWithSeverity = FilterWithSeverity;

      /* @Trace: SWS_Dem_01058
       * The function Dem_SetDTCFilter shall ignore unsupported bits (refer
       * to configuration parameter DemDtcStatusAvailabilityMask) retrieved
       * in DTCStatusMask.
       * */

      uint8 LucMask = DEM_ZERO;
      #if (DEM_NUMBER_OF_DEM_CLIENT > DEM_ZERO)
      /* @Trace: Dem_SUD_API_20284 */
      LucMask = Dem_EvMem_GetAvailableMaskFromMemSetIdx(
          Dem_Client[ClientId].usDemEventMemorySetId);
      #endif

      if (LucMask != DEM_ZERO)
      {
        /* @Trace: Dem_SUD_API_20287 */
        Dem_DTCFilterState[ClientId].dfs_DTCStatusMask = DTCStatusMask &
            LucMask;
      }
      else
      {
        /* @Trace: Dem_SUD_API_20286 */
        Dem_DTCFilterState[ClientId].dfs_DTCStatusMask = DTCStatusMask;
      }

      Dem_DTCFilterState[ClientId].dfs_DTCFormat = DTCFormat;
      Dem_DTCFilterState[ClientId].dfs_JobAction = DEM_JOB_TRIGGER;
      Dem_DTCFilterState[ClientId].dfs_NumOfFilteredDTC = DEM_ZERO;

      #if (DEM_J1979_2_OBD_ON_UDS == STD_ON)
      /* EDR, RGID is Only activate 0x56, 0x1A */
      /* Trace: DEM_19792_1A_01 */
      Dem_DTCFilterState[ClientId].dfs_ExtendedDataRecord = DEM_ZERO;
      /* Trace: DEM_19792_56_02 */
      Dem_DTCFilterState[ClientId].dfs_ReadinessGroupNumber = 0xFF;
      #endif /*(DEM_J1979_2_OBD_ON_UDS == STD_ON)*/

      /* Initialize the count for no.of filtered DTC's returned to DCM */
      Dem_DTCFilterState[ClientId].dfs_NextEvent = DEM_ONE;

      /* @LddRetVal = E_OK; */
    }
    Dem_DTCFilterState[ClientId].dfs_resultGetDtcFilter = LddRetVal;
    Dem_SetDTCFilterServiceUnLock(ClientId, DEM_SETDTCFILTER_SID_LOCK_IDX);
  }

  return LddRetVal;
}

/*******************************************************************************
** Function Name        : Dem_SetDTCFilterByExtendedDataRecordNumber[R21-11 DEM]**
**                                                                            **
** Service ID           : 0xc1                                                **
**                                                                            **
** Description          : Sets the DTC Filter based on a given Extended Data  **
**                        Record group on the primary fault memory. the       **
**                        server selects all DTCs that have a matching        **
**                        extended data record.                               **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : DTCFormat, ExtendedDataRecordnumber                 **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Dem_ReturnSetFilterType                             **
**                                                                            **
** Preconditions        : The API Dem_Init()                                  **
**                        should have been called in sequence                 **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
/* Trace: DEM_19792_1A_02 */
#if (DEM_J1979_2_OBD_ON_UDS == STD_ON)
FUNC(Std_ReturnType, DEM_CODE) Dem_SetDTCFilterByExtendedDataRecordNumber(
        uint8 ClientId,
        Dem_DTCFormatType DTCFormat, 
        uint8 ExtendedDataRecordnumber)
{
  /* @Trace: SWS_Dem_01300
   * API behavior without set DTC filter
   * If any of the APIs requiring a Dem_SetDTCFilter according to
   * [SWS_Dem_00057] is called without
   * a prior call of Dem_SetDTCFilter for this client, the Dem shall report the
   * Det DEM_E_WRONG_CONDITION.
   * */

  /* @Trace: SWS_Dem_01265
   * IF Dem_SetDTCFilter is called with an invalid DTCStatusMask, the Dem shall
   * return E_NOT_OK.
   * 0x00: Autosar-specific value to deactivate the status-byte filtering
   * (different meaning than in ISO 14229-1) to report all supported DTCs
   * (used for service 0x19 subfunctions 0x0A/0x15)
   *
   * 0x01..0xFF: Status-byte mask according to ISO 14229-1 DTCStatusMask
   * (handed over by Dcm from service request directly) to filter for DTCs with
   * at least one status bit set matching this status-byte mask
   * */

  Std_ReturnType LddRetVal = E_OK;

  boolean LblSetDTCFilterByExtendedDataRecordSIDLockIdx = Dem_SetDTCFilterServiceIsLock(ClientId,
      DEM_SETDTCFILTERBYEXTENDEDDATARECORD_SID_LOCK_IDX);
  /* @Trace: Dem_SUD_API_20275 */
  #if (DEM_NUMBER_OF_DEM_CLIENT > DEM_ZERO)
  if (ClientId >= DEM_NUMBER_OF_DEM_CLIENT)
  {
    /* @Trace: Dem_SUD_API_20288 */
    DEM_REPORT_ERROR(DEM_SETDTCFILTERBYEXTENDEDDATARECORD_SID, DEM_E_PARAM_DATA);
    LddRetVal = E_NOT_OK;
  }
  else
  #endif
  /* @Trace: Dem_SUD_API_20283 */
  if (DEM_TRUE == LblSetDTCFilterByExtendedDataRecordSIDLockIdx)
  {
    /* @Trace: Dem_SUD_API_20064 */
    LddRetVal = E_NOT_OK;
  }
  else
  {
    Dem_SetDTCFilterServiceLock(ClientId, DEM_SETDTCFILTERBYEXTENDEDDATARECORD_SID_LOCK_IDX);
    /* Module initialization check */
    if (Dem_GucInit != DEM_INIT)
    {
      /* @Trace: Dem_SUD_API_20289 */
      DEM_REPORT_ERROR(DEM_SETDTCFILTERBYEXTENDEDDATARECORD_SID, DEM_E_UNINIT);
      LddRetVal = E_NOT_OK;
    }
    /* DTCFormat check */
    else if ((DTCFormat != DEM_DTC_FORMAT_UDS)
            #if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
            && (DTCFormat != DEM_DTC_FORMAT_OBD_3BYTE)
            #endif            
        )
    { 
    /* Trace: DEM_19792_1A_07 */  
      /* @Trace: SWS_Dem_91193 in R21-11
       * Defines the DTC format of the requested data. Valid selections are
       * DEM_DTC_FORMAT-UDS and DEM_DTC_FORMAT_OBD_3BYTE
       * */
      /* @Trace: SWS_Dem_01377 in R21-11
       *  If Dem_SetDTCFilterByExtendedDataRecord is called with DTCFormat equal to 
       *  DEM_DTC_FORMAT_OBD_3BYTE and DemSupportedobdUdsDtcSeparation is set to TRUE,
       *  the Dem shall use the DTCs configured via DemDtcValue3Byte as filter target.
        */
      /* @Trace: SWS_Dem_01378 in R21-11
       *  If Dem_SetDTCFilterByExtendedDataRecord is called with DTCFormat equal to 
       *  DEM_DTC_FORMAT_UDS,
       *  the Dem shall use the 3-byte DTCs configured via DemDtcValue as filter target.
        */      
      /* @Trace: SWS_Dem_01066
       * The Det error DEM_E_WRONG_CONFIGURATION shall be reported if the
       * function Dem_SetDTCFilter is called with a value of the parameter
       * DTCFormat that is not supported per configuration (e.g. if DTCFormat
       * = DEM_DTC_FORMAT_OBD is passed, but OBD is not supported per
       * configuration).
       * */  
      /* @Trace: Dem_SUD_API_20276 */
      DEM_REPORT_ERROR(DEM_SETDTCFILTERBYEXTENDEDDATARECORD_SID, DEM_E_WRONG_CONFIGURATION);
      LddRetVal = E_NOT_OK;
    }
    else if (
      ((Dem_ObdUdsDtc_Separation_Support == STD_ON) && (DTCFormat != DEM_DTC_FORMAT_OBD_3BYTE)) ||
      ((Dem_ObdUdsDtc_Separation_Support == STD_OFF) && (DTCFormat != DEM_DTC_FORMAT_UDS)) )
    {
      DEM_REPORT_ERROR(DEM_SETDTCFILTERBYEXTENDEDDATARECORD_SID, DEM_E_PARAM_DATA);
      LddRetVal = E_NOT_OK;
    }
    else
    {      
      /* @Trace: SWS_Dem_01263
       * A call of Dem_SetDTCFilter sets the requested filter on the event
       * memory assigned to ClientID of the call.
       * */

      /* @Trace: SWS_Dem_00649
       * Each call of Dem_SetDTCFilter shall lead to a reset of the sequence
       * for that client.
       * */

      Dem_EventIdType LddEventId;
      for ( LddEventId = DEM_ONE; LddEventId <= DEM_NUMBER_OF_EVENTS;
            LddEventId++)
      {
        /* @Trace: SWS_Dem_01101
         * A suppressed DTC shall not be visible for the following Dcm
         * query-functions; therefore the following functions shall treat the
         * DTC as if filter is not matching.
         * */
        /* @Trace: Dem_SUD_API_20280 */
        if (DEM_TRUE != Dem_EvIsProcStateTriggered(LddEventId,
            DEM_EVPROCSTATE_DTC_SUPP))
        {
          /* @Trace: Dem_SUD_API_20282 */
          if ((DEM_NO_EVMEM_IDX != Dem_Event[LddEventId - DEM_ONE]
              .ucEventMemDstIdx)
              #if (DEM_NUMBER_OF_DEM_CLIENT > DEM_ZERO)
              && (Dem_Client[ClientId].usDemEventMemorySetId ==
                  Dem_Event[LddEventId - DEM_ONE].ucEventMemDstIdx)
              #endif
              )
          {
            /* @Trace: Dem_SUD_API_20281 */
            Dem_EvClearProcState(LddEventId, DEM_EVPROCSTATE_DTC_FILTER);
          }
        }
      }     
        /* @Trace: SWS_Dem_01362 in R21-11
         * The function Dem_SetDTCFilterByExtendedDataRecordNumber shall set a DTC filter criteria for supported 
         * ExtendedDataRecords on DTCs based on the parameter ExtendedDataRecordnumber for the client with 
         * the same client ID for subsequent calls of:
         * - Dem_GetNumberOfFilteredDTC
         * - Dem_GetNextFilteredDTC.
         * An extended data record for a DTC is considered as supported if the DTC refers to an extended data record
         * that has DemExtendedDataRecordnumber set to the number of the extended data record.
         * */

      Dem_DTCFilterState[ClientId].dfs_ExtendedDataRecord = ExtendedDataRecordnumber;      
      Dem_DTCFilterState[ClientId].dfs_DTCFormat = DTCFormat;
      Dem_DTCFilterState[ClientId].dfs_JobAction = DEM_JOB_TRIGGER;
      Dem_DTCFilterState[ClientId].dfs_NumOfFilteredDTC = DEM_ZERO;

      Dem_DTCFilterState[ClientId].dfs_ReadinessGroupNumber = 0xFF;
      Dem_DTCFilterState[ClientId].dfs_DTCStatusMask = DEM_ZERO;
      Dem_DTCFilterState[ClientId].dfs_DTCOrigin = DEM_DTC_ORIGIN_PRIMARY_MEMORY;
      Dem_DTCFilterState[ClientId].dfs_FilterForFDC = DEM_ZERO;
      Dem_DTCFilterState[ClientId].dfs_DTCSeverityMask = DEM_ZERO;
      Dem_DTCFilterState[ClientId].dfs_FilterWithSeverity = DEM_ZERO;

      /* Initialize the count for no.of filtered DTC's returned to DCM */
      Dem_DTCFilterState[ClientId].dfs_NextEvent = DEM_ONE;

      /* @LddRetVal = E_OK; */
    }
    Dem_DTCFilterState[ClientId].dfs_resultGetDtcFilter = LddRetVal;
    Dem_SetDTCFilterServiceUnLock(ClientId, DEM_SETDTCFILTERBYEXTENDEDDATARECORD_SID_LOCK_IDX);
  }

  return LddRetVal;
}
#endif /* J9792 */

/*******************************************************************************
** Function Name        : Dem_SetDTCFilterByReadinessGroup[R21-11 DEM]        **
**                                                                            **
** Service ID           : 0xc2                                                **
**                                                                            **
** Description          : Sets the DTC Filter based on a given DTC readiness  **
**                        group on the primary fault memory. the server       **
**                        selects all DTCs that have this DTC readiness       **
**                        group configured.                                   **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : DTCFormat, ReadinessGroupNumber                     **                 
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Dem_ReturnSetFilterType                             **
**                                                                            **
** Preconditions        : The API Dem_Init()                                  **
**                        should have been called in sequence                 **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
/* Trace: DEM_19792_56_03 */
#if (DEM_J1979_2_OBD_ON_UDS == STD_ON)
FUNC(Std_ReturnType, DEM_CODE) Dem_SetDTCFilterByReadinessGroup(
        uint8 ClientId,
        Dem_DTCFormatType DTCFormat, 
        Dem_EventOBDReadinessGroupType ReadinessGroupNumber)
{
  /* @Trace: SWS_Dem_01300
   * API behavior without set DTC filter
   * If any of the APIs requiring a Dem_SetDTCFilter according to
   * [SWS_Dem_00057] is called without
   * a prior call of Dem_SetDTCFilter for this client, the Dem shall report the
   * Det DEM_E_WRONG_CONDITION.
   * */

  /* @Trace: SWS_Dem_01265
   * IF Dem_SetDTCFilter is called with an invalid DTCStatusMask, the Dem shall
   * return E_NOT_OK.
   * 0x00: Autosar-specific value to deactivate the status-byte filtering
   * (different meaning than in ISO 14229-1) to report all supported DTCs
   * (used for service 0x19 subfunctions 0x0A/0x15)
   *
   * 0x01..0xFF: Status-byte mask according to ISO 14229-1 DTCStatusMask
   * (handed over by Dcm from service request directly) to filter for DTCs with
   * at least one status bit set matching this status-byte mask
   * */

  Std_ReturnType LddRetVal = E_OK;

  boolean LblSetDTCFilterByReadinessGroupSIDLockIdx = Dem_SetDTCFilterServiceIsLock(ClientId,
      DEM_SETDTCFILTERBYREADINESSGROUP_SID_LOCK_IDX);
  /* @Trace: Dem_SUD_API_20275 */
  #if (DEM_NUMBER_OF_DEM_CLIENT > DEM_ZERO)
  if (ClientId >= DEM_NUMBER_OF_DEM_CLIENT)
  {
    /* @Trace: Dem_SUD_API_20288 */
    DEM_REPORT_ERROR(DEM_SETDTCFILTERBYREADINESSGROUP_SID, DEM_E_PARAM_DATA);
    LddRetVal = E_NOT_OK;
  }
  else
  #endif
  /* @Trace: Dem_SUD_API_20283 */
  if (DEM_TRUE == LblSetDTCFilterByReadinessGroupSIDLockIdx)
  {
    /* @Trace: Dem_SUD_API_20064 */
    LddRetVal = E_NOT_OK;
  }
  else
  {
    Dem_SetDTCFilterServiceLock(ClientId, DEM_SETDTCFILTERBYREADINESSGROUP_SID_LOCK_IDX);
    /* Module initialization check */
    if (Dem_GucInit != DEM_INIT)
    {
      /* @Trace: Dem_SUD_API_20289 */
      DEM_REPORT_ERROR(DEM_SETDTCFILTERBYREADINESSGROUP_SID, DEM_E_UNINIT);
      LddRetVal = E_NOT_OK;
    }
   
    /* Trace: DEM_19792_56_08 */  
    /* DTCFormat check */
      /* @Trace: SWS_Dem_01374 in R21-11
       * If Dem_SetDTCFilterByReadinessGroup is called with DTCFormat equal to 
       * DEM_DTC_FORMAT_OBD_3BYTE and DemSupportedobdUdsDtcSeparation is set to TRUE,
       * the Dem shall use the DTCs configured via DemDtcValue3Byte as filter target.    
       * */
      /* @Trace: SWS_Dem_01376 in R21-11
       * If Dem_SetDTCFilterByReadinessGroup is called with DTCFormat equal to 
       * DEM_DTC_FORMAT_UDS and DemSupportedobdUdsDtcSeparation is set to TRUE,
       * the Dem shall report the Det DEM_E_PARAM_DATA.    
       * */
    else if (
      ((Dem_ObdUdsDtc_Separation_Support == STD_ON) && (DTCFormat != DEM_DTC_FORMAT_OBD_3BYTE)) ||
      ((Dem_ObdUdsDtc_Separation_Support == STD_OFF) && (DTCFormat != DEM_DTC_FORMAT_UDS)) )
    {
      DEM_REPORT_ERROR(DEM_SETDTCFILTERBYEXTENDEDDATARECORD_SID, DEM_E_PARAM_DATA);
      LddRetVal = E_NOT_OK;
    }
    else
    {
        /* Trace: DEM_19792_56_08 */
        /* @Trace: SWS_Dem_91193 in R21-11
        * Defines the DTC format of the requested data. Valid selections are
        * DEM_DTC_FORMAT-UDS and DEM_DTC_FORMAT_OBD_3BYTE
        * */
       /* polyspace-begin MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] "Same as Dead Code" */
       /* polyspace-begin DEFECT:DEAD_CODE [Justified:Low] Dead Code by User Defined. */
      if ((DTCFormat != DEM_DTC_FORMAT_OBD_3BYTE) &&
            (DTCFormat != DEM_DTC_FORMAT_UDS) 
          )
      {
        DEM_REPORT_ERROR(DEM_SETDTCFILTERBYREADINESSGROUP_SID, DEM_E_WRONG_CONFIGURATION);
        LddRetVal = E_NOT_OK;
      }             
      /* polyspace-end MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] "Same as Dead Code" */
      /* polyspace-end DEFECT:DEAD_CODE [Justified:Low] Dead Code by User Defined. */
      
      /* @Trace: SWS_Dem_01263
       * A call of Dem_SetDTCFilter sets the requested filter on the event
       * memory assigned to ClientID of the call.
       * */

      /* @Trace: SWS_Dem_00649
       * Each call of Dem_SetDTCFilter shall lead to a reset of the sequence
       * for that client.
       * */

      Dem_EventIdType LddEventId;
      for ( LddEventId = DEM_ONE; LddEventId <= DEM_NUMBER_OF_EVENTS;
            LddEventId++)
      {
        /* @Trace: SWS_Dem_01101
         * A suppressed DTC shall not be visible for the following Dcm
         * query-functions; therefore the following functions shall treat the
         * DTC as if filter is not matching.
         * */
        /* @Trace: Dem_SUD_API_20280 */
        if (DEM_TRUE != Dem_EvIsProcStateTriggered(LddEventId,
            DEM_EVPROCSTATE_DTC_SUPP))
        {
          /* @Trace: Dem_SUD_API_20282 */
          if ((DEM_NO_EVMEM_IDX != Dem_Event[LddEventId - DEM_ONE]
              .ucEventMemDstIdx)
              #if (DEM_NUMBER_OF_DEM_CLIENT > DEM_ZERO)
              && (Dem_Client[ClientId].usDemEventMemorySetId ==
                  Dem_Event[LddEventId - DEM_ONE].ucEventMemDstIdx)
              #endif
              )
          {
            /* @Trace: Dem_SUD_API_20281 */
            Dem_EvClearProcState(LddEventId, DEM_EVPROCSTATE_DTC_FILTER);
          }
        }
      }
      
        /* @Trace: SWS_Dem_01364 in R21-11
         * The function Dem_SetDTCFilterByReadinessGroup shall set a DTC filter criteria for DTCs 
         * that are assigned to a given DTC readiness group for the client with the same client ID 
         * for subsequent calls of:
         * - Dem_GetNumberOfFilteredDTC
         * - Dem_GetNextFilteredDTC.
         * */
      Dem_DTCFilterState[ClientId].dfs_ReadinessGroupNumber = ReadinessGroupNumber;      
      Dem_DTCFilterState[ClientId].dfs_DTCFormat = DTCFormat;
      Dem_DTCFilterState[ClientId].dfs_JobAction = DEM_JOB_TRIGGER;
      Dem_DTCFilterState[ClientId].dfs_NumOfFilteredDTC = DEM_ZERO;

      Dem_DTCFilterState[ClientId].dfs_ExtendedDataRecord = DEM_ZERO;
      Dem_DTCFilterState[ClientId].dfs_DTCStatusMask = DEM_ZERO;
      Dem_DTCFilterState[ClientId].dfs_DTCOrigin = DEM_DTC_ORIGIN_PRIMARY_MEMORY;
      Dem_DTCFilterState[ClientId].dfs_FilterForFDC = DEM_ZERO;
      Dem_DTCFilterState[ClientId].dfs_DTCSeverityMask = DEM_ZERO;
      Dem_DTCFilterState[ClientId].dfs_FilterWithSeverity = DEM_ZERO;

      /* Initialize the count for no.of filtered DTC's returned to DCM */
      Dem_DTCFilterState[ClientId].dfs_NextEvent = DEM_ONE;

      /* @LddRetVal = E_OK; */
    }
    Dem_DTCFilterState[ClientId].dfs_resultGetDtcFilter = LddRetVal;
    Dem_SetDTCFilterServiceUnLock(ClientId, DEM_SETDTCFILTERBYREADINESSGROUP_SID_LOCK_IDX);
  }

  return LddRetVal;
}
#endif /* J19792 */

/*******************************************************************************
** Function Name        : Dem_SetFreezeFrameRecordFilter                      **
**                                                                            **
** Service ID           : 0x3f                                                **
**                                                                            **
** Description          : This API shall set a freeze frame Record filter     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : DTCFormat                                           **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : uint16* NumberOfFilteredRecords                     **
**                                                                            **
** Return parameter     : Dem_ReturnSetFilterType                             **
**                                                                            **
** Preconditions        : The API Dem_PreInit(), Dem_Init()                   **
**                        should have been called in sequence                 **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Dem_GucInit                                         **
**                        Dem_FilteredFFRecord                                **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        (void)Det_ReportError                               **
*******************************************************************************/
/* @Trace: SRS_Diag_04074 SRS_Diag_04204 SRS_Diag_04164
 */
/* @Trace: Dem_SUD_MACRO_037 */
/* polyspace +1 CODE-METRICS:LEVEL [Not a defect:LOW] "Not a defect" */ 
FUNC(Std_ReturnType, DEM_CODE)Dem_SetFreezeFrameRecordFilter(
  uint8 ClientId,
  Dem_DTCFormatType DTCFormat)
{
  /* @Trace: SWS_Dem_00595
   * The function Dem_SetFreezeFrameRecordFilter shall set the static filter
   * criteria attribute "all freeze frame records currently stored in the event
   * memory" to be used for the subsequent calls of Dem_GetNextFilteredRecord
   * and Dem_GetNumberOfFreezeFrameRecords. This filter always belongs to
   * primary memory.
   * */
  /* @Trace: SWS_Dem_00650
   * The filter criteria attributes of Dem_SetFreezeFrameRecordFilter shall be
   * used until the next call of Dem_SetFreezeFrameRecordFilter or Dem
   * initialization. Each call of
   * Dem_SetFreezeFrameRecordFilter shall lead to a reset of the sequence
   * iterating over freezeframes.
   * */

  Std_ReturnType LddRetVal = E_OK;

  boolean LblSetFreezeFrameRecordFilterSIDLockIdx =
      Dem_SetFFRecordFilterServiceIsLock(ClientId,
          DEM_SETFREEZEFRAMERECORDFILTER_SID_LOCK_IDX);
  /* @Trace: Dem_SUD_API_20394 */
  #if (DEM_NUMBER_OF_DEM_CLIENT > DEM_ZERO)
  if (ClientId >= DEM_NUMBER_OF_DEM_CLIENT)
  {
    /* @Trace: Dem_SUD_API_20405 */
    DEM_REPORT_ERROR(DEM_SETFREEZEFRAMERECORDFILTER_SID, DEM_E_PARAM_DATA);
    LddRetVal = E_NOT_OK;
  }
  else
  #endif
  /* @Trace: Dem_SUD_API_20394 */
  if (DEM_TRUE == LblSetFreezeFrameRecordFilterSIDLockIdx)
  {
    /* @Trace: Dem_SUD_API_20406 */
    LddRetVal = E_NOT_OK;
  }
  else
  {
    /* @Trace: Dem_SUD_API_20404 */
    Dem_SetFFRecordFilterServiceLock(ClientId,
        DEM_SETFREEZEFRAMERECORDFILTER_SID_LOCK_IDX);

    if (DEM_INIT != Dem_GucInit)
    {
      /* @Trace: Dem_SUD_API_20408 */
      DEM_REPORT_ERROR(DEM_SETFREEZEFRAMERECORDFILTER_SID, DEM_E_UNINIT);
      LddRetVal = E_NOT_OK;
    }
    /* @Trace: Dem_SUD_API_20407 */
    else if ((DTCFormat != DEM_DTC_FORMAT_OBD) 
            #if(DEM_J1979_2_OBD_ON_UDS == STD_ON)
            /* Trace: DEM_19792_42_04 */
            && (DTCFormat != DEM_DTC_FORMAT_OBD_3BYTE) 
            #endif /*(DEM_J1979_2_OBD_ON_UDS == STD_ON)*/
            && (DTCFormat !=DEM_DTC_FORMAT_UDS))
    {
      /* @Trace: Dem_SUD_API_20409 */
      DEM_REPORT_ERROR(DEM_SETFREEZEFRAMERECORDFILTER_SID, DEM_E_PARAM_CONFIG);
      LddRetVal = E_NOT_OK;
    }
    else
    {
      uint16 LusRecordFiltered = DEM_ZERO;
      #if ((DEM_MAX_EVENT_DESTINATION_SELECTED > DEM_ZERO) && \
           (DEM_SIZE_OF_FREEZEFRAME > DEM_ZERO))
      Dem_EventIdType LddEvId;
      Dem_NumOfEventMemoryEntryType LddMemLoc = DEM_ZERO;
      /* @Trace: SWS_Dem_00595
       * The function Dem_DcmSetFreezeFrameRecordFilter
       * shall set the static filter criteria attribute "all freeze frame
       * records currently stored in the event memory" to be used for the
       * subsequent calls of Dem_DcmGetNextFilteredRecord. The filter criteria
       * attributes shall be used until the next call of
       * Dem_DcmSetFreezeFrameRecordFilter or Dem initialization. */
      /* @Trace: Dem_SUD_API_20396 */
      Dem_FilteredFFRecord[ClientId].nextEvent = DEM_NO_EVENT;
      for (LddEvId = DEM_ONE; LddEvId <= DEM_NUMBER_OF_EVENTS; LddEvId++)
      {
        /* @Trace: Dem_SUD_API_20395 */
        Dem_EvClearProcState(LddEvId, DEM_EVPROCSTATE_DTC_FILTER);
      }

      /* It can be processed regardless of combined event
       * because of searching the event from event memory,
       * It always stores a first event out of combined events.
       */
      Dem_NumOfEventMemoryEntryType LddSizeOfMem =
          Dem_EvMem_GetSizeOfEventMemory(
          ClientId, DEM_DTC_ORIGIN_PRIMARY_MEMORY);
      Dem_NumOfEventMemoryEntryType LddStartIndex =
          Dem_EvMem_GetStartIndexEvMemory(ClientId,
              DEM_DTC_ORIGIN_PRIMARY_MEMORY);

      LddSizeOfMem = LddSizeOfMem + LddStartIndex;
      /* @Trace: Dem_SUD_API_20397 */
      for (LddMemLoc = DEM_ZERO;
           LddMemLoc < LddSizeOfMem;
           LddMemLoc++)
      {
        LddEvId = Dem_EvMem_GetEventIdByEvMemEntry(
            DEM_DTC_ORIGIN_PRIMARY_MEMORY,
            LddMemLoc);
        /* if (DEM_TRUE == Dem_EventIdIsValid(LddEvId)) */
        /* @Trace: Dem_SUD_API_20398 */
        if ((LddEvId <= DEM_NUMBER_OF_EVENTS) && (DEM_NO_EVENT != LddEvId)
            && (Dem_Event[LddEvId - DEM_ONE].ucEventMemDstIdx
                == Dem_Client[ClientId].usDemEventMemorySetId))
        {
          /* Filtering according to  expected DTCformat */
          /* @Trace: Dem_SUD_API_20399 */
          if ((boolean) DEM_TRUE == Dem_DTCFormatIsValid(LddEvId, DTCFormat))
          {
            Dem_EventParameterPCType LddEvent = &Dem_Event[LddEvId - DEM_ONE];
            /* @Trace: Dem_SUD_API_20400 */
            if (LddEvent->e_PointToData < DEM_NUM_OF_EVENTRELATEDDATA)
            {
              /* @Trace: Dem_SUD_API_20401 */
              if (Dem_EventRelatedData[LddEvent->e_PointToData].FFClassPos
                  < DEM_NUM_OF_FREEZEFRAMECLASS)
              {
                Dem_RecordNumberType LddRecNumber = Dem_EvMem_GetRecNumOfFF(
                    Dem_EvMem_GetEmEntryByMemPosition(
                    DEM_DTC_ORIGIN_PRIMARY_MEMORY, LddMemLoc));
                /* RecordNumber 0 means that Freeze Frame Record is not stored
                 * in the event memory */
                /* @Trace: Dem_SUD_API_20402 */
                if (DEM_ZERO != LddRecNumber)
                {
                  /* Compute the number of filtered records */
                  LusRecordFiltered += LddRecNumber;
                  Dem_EvSetProcState(LddEvId, DEM_EVPROCSTATE_DTC_FILTER);
                  /* @Trace: Dem_SUD_API_20403 */
                  if (DEM_NO_EVENT == Dem_FilteredFFRecord[ClientId].nextEvent)
                  {
                    /* @Trace: Dem_SUD_API_20411 */
                    Dem_FilteredFFRecord[ClientId].nextEvent = LddEvId;
                  }
                }
              }
            }
          }
        }
      }
      #endif
      /* @Trace: Dem_SUD_API_20410 */
      /* Initialize the Index of record number for next event */
      Dem_FilteredFFRecord[ClientId].nextRecord = DEM_ZERO;

      /* Set the number of filtered record to zero */
      Dem_FilteredFFRecord[ClientId].numberOfFilteredRecords =
          LusRecordFiltered;

      /* @LddRetVal = E_OK; */
    }
    Dem_FilteredFFRecord[ClientId].resultSetFFRecFilter = LddRetVal;
    Dem_SetFFRecordFilterServiceUnLock(ClientId,
        DEM_SETFREEZEFRAMERECORDFILTER_SID_LOCK_IDX);
  }
  return LddRetVal;
}/* End of API */
/*******************************************************************************
** Function Name        : Dem_GetStatusOfDTC                                  **
**                                                                            **
** Service ID           : 0x15                                                **
**                                                                            **
** Description          : This API shall be used to gets the status of a DTC. **
**                        For large configurations and DTC-calibration, the   **
**                        interface behavior can be asynchronous              **
**                        (splitting the DTC-search into segments).           **
**                        The DTCs of OBD Events Suppression shall be         **
**                        reported as Dem_WRONG_DTC.)                         **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Reentrant for different ClientIds, non reentrant    **
**                        for the same ClientId.                              **
**                                                                            **
** Input Parameters     : ClientId                                            **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : DTCStatus                                           **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : The API Dem_PreInit(), Dem_Init()                   **
**                        should have been called in sequence                 **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Dem_GucInit                                         **
**                        Dem_Event                                           **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        (void)Det_ReportError                               **
*******************************************************************************/
/* @Trace: SRS_Diag_04010 SRS_Diag_04067 SRS_Diag_04220
 */
/* polyspace +1 CODE-METRICS:LEVEL [Not a defect:LOW] "Not a defect" */ 
FUNC(Std_ReturnType, DEM_CODE) Dem_GetStatusOfDTC(uint8 ClientId,
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA) DTCStatus)
{
  Std_ReturnType LddRetVal = E_NOT_OK;

  boolean LblGetStatusOfDTCSIDLockIdx = Dem_SelectedDTCServiceIsLock(ClientId,
      DEM_GETSTATUSOFDTC_SID_LOCK_IDX);
  boolean LblClearDTCSIDLockIdx = Dem_SelectedDTCServiceIsLock(ClientId,
      DEM_CLEARDTC_SID_LOCK_IDX);
  /* @Trace: Dem_SUD_API_20213 */
  #if (DEM_NUMBER_OF_DEM_CLIENT > DEM_ZERO)
  if (ClientId >= DEM_NUMBER_OF_DEM_CLIENT)
  {
    /* @Trace: Dem_SUD_API_20220 */
    DEM_REPORT_ERROR(DEM_GETSTATUSOFDTC_SID, DEM_E_PARAM_DATA);
    LddRetVal = E_NOT_OK;
  }
  else
  #endif
  /* @Trace: Dem_SUD_API_20224 */
  if (DEM_TRUE == LblGetStatusOfDTCSIDLockIdx)
  {
    /* @Trace: Dem_SUD_API_20053 */
    LddRetVal = DEM_PENDING;
  }
  else if (DEM_TRUE == LblClearDTCSIDLockIdx)
  {
    /* @Trace: Dem_SUD_API_20054 */
    LddRetVal = DEM_BUSY;
  }
  else
  {
    /* lock this client id */
    Dem_SelectedDTCServiceLock(ClientId,
        DEM_GETSTATUSOFDTC_SID_LOCK_IDX);

    /* Check module Initialization status */
    if (Dem_GucInit != DEM_INIT)
    {
      /* @Trace: Dem_SUD_API_20226 */
      DEM_REPORT_ERROR(DEM_GETSTATUSOFDTC_SID, DEM_E_UNINIT);
      LddRetVal = E_NOT_OK;
    }
    /* Check DTC Status is a Null pointer */
    else if (DTCStatus == NULL_PTR)
    {
      /* @Trace: Dem_SUD_API_20227 */
      DEM_REPORT_ERROR(DEM_GETSTATUSOFDTC_SID, DEM_E_PARAM_POINTER);
      LddRetVal = E_NOT_OK;
    }
    else if (E_OK != Dem_ClientSelectDtcState[ClientId].resultSelectDTC)
    {
      /* @Trace: Dem_SUD_API_20214 */
      DEM_REPORT_ERROR(DEM_GETSTATUSOFDTC_SID, DEM_E_WRONG_CONDITION);
      LddRetVal = Dem_ClientSelectDtcState[ClientId].resultSelectDTC;
    }
    else
    {
      Dem_EventIdType LddEventId = Dem_GetEventIdByDTC(
           DEM_GETSTATUSOFDTC_SID,
           Dem_ClientSelectDtcState[ClientId].selectedDTC,
           Dem_ClientSelectDtcState[ClientId].selectedDTCFormat);
      Std_ReturnType LddDtcGroupIsValid = Dem_DTCGroupIsValid(
          Dem_ClientSelectDtcState[ClientId].selectedDTC,
          Dem_ClientSelectDtcState[ClientId].selectedDTCFormat);

      if (((Dem_ClientSelectDtcState[ClientId].selectedDTCFormat != DEM_DTC_FORMAT_UDS)
      #if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
          && (Dem_ClientSelectDtcState[ClientId].selectedDTCFormat != DEM_DTC_FORMAT_OBD)
     #if (DEM_J1979_2_OBD_ON_UDS == STD_ON)
      /* Trace: DEM_19792_42_04 */
          && (Dem_ClientSelectDtcState[ClientId].selectedDTCFormat != DEM_DTC_FORMAT_OBD_3BYTE)
      #endif /*(DEM_J1979_2_OBD_ON_UDS == STD_ON)*/
      #endif /*(DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)*/
      #if (DEM_J1939_SUPPORT == STD_ON)
          && (Dem_ClientSelectDtcState[ClientId].selectedDTCFormat != DEM_DTC_FORMAT_J1939)

      #endif
      ) || (E_OK == LddDtcGroupIsValid))
      {
        /* @Trace: SWS_Dem_01259
         * If the API Dem_GetStatusOfDTC is called on a selected DTC that does
         * not exist in the selected format or if the selected DTC is a group
         * of DTC or no DTC was selected, the Dem shall return DEM_WRONG_DTC.
         * */
        /* @Trace: Dem_SUD_API_20215 */
        LddRetVal = DEM_WRONG_DTC;
      }

      /* @if (DEM_FALSE == Dem_EventIdIsValid(LddEventId)) */
      else if ((LddEventId > DEM_NUMBER_OF_EVENTS) ||
               (DEM_NO_EVENT == LddEventId))
      {
        /* @Trace: SWS_Dem_01275
         * If the API Dem_GetStatusOfDTC is called on a selected DTC that does
         * not have an assigned DTC status, the Dem shall return
         *  DEM_NO_SUCH_ELEMENT.
         * */
        /* @Trace: Dem_SUD_API_20216 */
        LddRetVal = DEM_NO_SUCH_ELEMENT;
      }
      else if ( DEM_TRUE != Dem_DTCFormatIsValid(LddEventId,
                    Dem_ClientSelectDtcState[ClientId].selectedDTCFormat))
      {
        /* @Trace: SWS_Dem_01259
         * If the API Dem_GetStatusOfDTC is called on a selected DTC that does
         * not exist in the selected format or if the selected DTC is a group
         * of DTC or no DTC was selected, the Dem shall return DEM_WRONG_DTC.
         * */
        /* @Trace: Dem_SUD_API_20056 */
        LddRetVal = DEM_WRONG_DTC;
      }

      #if (DEM_MAX_EVENT_DESTINATION_SELECTED > DEM_ZERO)
      else if ((boolean)DEM_FALSE == Dem_DTCOriginBelongToEvent(LddEventId,
          Dem_ClientSelectDtcState[ClientId].selectedDTCOrigin))
      {
        /* @Trace: SWS_Dem_01260
         * If the API Dem_GetStatusOfDTC is called on a not existing selected
         * DTCOrigin, the Dem shall return DEM_WRONG_DTCORIGIN.
         * */
        /* @Trace: Dem_SUD_API_20055 */
        LddRetVal = DEM_WRONG_DTCORIGIN;
      }
      else
      {
        if ((boolean)DEM_TRUE == Dem_EvIsProcStateTriggered(LddEventId,
            DEM_EVPROCSTATE_DTC_SUPP))
        /* polyspace<RTE:UNR:Not a defect:No action planned> If-condition always
         *  can evaluates to true/false according to DTCSuppression
         *  configuration */
        {
          /* @Trace: SWS_Dem_01100
           * Behavior of DTC query functions for suppressed DTCs. In
           * case any of the following APIs is called on a single
           * selected DTC which is suppressed, the Dem shall return
           * DEM_WRONG_DTC
           * */
          /* @Trace: Dem_SUD_API_20218 */
          LddRetVal = DEM_WRONG_DTC;
        }
        else
        {
          /* @Trace: SWS_Dem_00059
           * The function Dem_GetStatusOfDTC shall copy the status of the
           * selected DTC to the parameter DTCStatus. The DTCStatus format is
           * according to ISO-14229-1[2].
           * */
          /* @Trace: Dem_SUD_API_20219 */
          P2CONST(Dem_CombinedDtcType, AUTOMATIC, DEM_VAR) LddCbDTC =
              Dem_GetCbDTCByEventId(LddEventId);
          /* @Trace: Dem_SUD_API_20221 */
          if (NULL_PTR != LddCbDTC)
          {
            /* If specific StatusAvailablilityMask of a DTC is existed */
            /* @Trace: SWS_Dem_01049
             * If the Dem module is requested to report the status of a
             * combined DTC (refer e.g. Dem_GetStatusOfDTC or
             * Dem_GetNextFilteredDTC), the calculation
             * of the status byte shall be performed according [SWS_Dem_00441].
             * */
            /* polyspace-begin MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] Same as Dead Code. */
            /* polyspace-begin DEFECT:DEAD_CODE [Justified:Low] Dead Code by Configuration. */
            /* polyspace +1 DEFECT:DATA_RACE [Not a defect:Low] "Not a defect" */ 
            if (DEM_ZERO != LddCbDTC->UdsStatusAvailabilityMask)
            {
              /* UdsStatusAvailabilityMask and Dem_DTCFilterState[ClientId].
               * dfs_DTCStatusMask are subset of Dem_Status_Availability_Mask */
                /* @Trace: SWS_Dem_00657
                 * The Dem module shall mask all DTC status bytes (API
                 * parameters DTCStatus)
                 * provided to the Dcm with the DTC status availability mask (
                 * by performing a bit-wise AND operation).
                 */
              /* @Trace: Dem_SUD_API_20223 */
              *DTCStatus = Dem_GetDTCStatus(LddEventId) &
                  LddCbDTC->UdsStatusAvailabilityMask;
            }
            /* polyspace-end MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] Same as Dead Code. */
            /* polyspace-end DEFECT:DEAD_CODE [Justified:Low] */
            else
            {
              /* @Trace: Dem_SUD_API_20222 */
              *DTCStatus = Dem_GetDTCStatus(LddEventId);
            }
            LddRetVal = E_OK;
          }
        }
      }
      #else
      /* @Trace: Dem_SUD_API_20217 */
      else
      {
        DEM_UNUSED(DTCOrigin);
        DEM_UNUSED(DTCStatus);
        LddRetVal = DEM_WRONG_DTCORIGIN;
      }
      #endif
    }
    /* unlock this client id */
    Dem_SelectedDTCServiceUnLock(ClientId, DEM_GETSTATUSOFDTC_SID_LOCK_IDX);
  }
  return LddRetVal;
}
/*******************************************************************************
** Function Name        : Dem_GetDTCStatusAvailabilityMask                    **
**                                                                            **
** Service ID           : 0x16                                                **
**                                                                            **
** Description          : This API shall be used to get the DTC Status        **
**                        availability mask                                   **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant for different ClientIDs, Non re-entrant  **
**                        for same ClientId.                                  **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : Dem_UdsStatusByteType* DTCStatusMask                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : The API Dem_PreInit(), Dem_Init()                   **
**                        should have been called in sequence                 **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Dem_GucInit                                         **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        (void)Det_ReportError()                             **
*******************************************************************************/
/* @Trace: SRS_Diag_04010 SRS_Diag_04067 SRS_Diag_04164
 */
FUNC(Std_ReturnType, DEM_CODE) 
Dem_GetDTCStatusAvailabilityMask(
  uint8 ClientId,
  P2VAR(Dem_UdsStatusByteType, AUTOMATIC, DEM_APPL_DATA) DTCStatusMask)
{
  Std_ReturnType LddRetVal = E_NOT_OK;
  /* @Trace: SWS_Dem_00060
   * The function Dem_GetDTCStatusAvailabilityMask shall provide the UDS status
   * availability mask (refer to DemDtcStatusAvailabilityMask in DemGeneral),
   * that means the UDS status information (according to ISO-14229-1[2])
   * supported by the Dem module with respect to the tester client
   * with UDS service 0x19. ClientID shall not be evaluated for determining the
   * availability mask.
   * */

  /* Module initialization check */
  if (Dem_GucInit != DEM_INIT)
  {
    /* @Trace: Dem_SUD_API_20204 */
    DEM_REPORT_ERROR(DEM_GETDTCSTATUSAVAILABILITYMASK_SID, DEM_E_UNINIT);
    LddRetVal = E_NOT_OK;
  }
  /* @Trace: Dem_SUD_API_20206 */
  #if (DEM_NUMBER_OF_DEM_CLIENT > DEM_ZERO)
  else if (ClientId >= DEM_NUMBER_OF_DEM_CLIENT)
  {
    /* @Trace: Dem_SUD_API_20205 */
    DEM_REPORT_ERROR(
        DEM_GETDTCSTATUSAVAILABILITYMASK_SID, DEM_E_WRONG_CONFIGURATION);
    LddRetVal = E_NOT_OK;
  }
  #endif
  /* @Trace: Dem_SUD_API_20207 */
  else if (DTCStatusMask == NULL_PTR)
  {
    /* @Trace: Dem_SUD_API_20208 */
    DEM_REPORT_ERROR(DEM_GETDTCSTATUSAVAILABILITYMASK_SID, DEM_E_PARAM_POINTER);
    LddRetVal = E_NOT_OK;
  }
  else
  {
    /* @Trace: Dem_SUD_API_20210 */
    /* Set DTCStatusAvailabilityMask to DTCStatusMask */
    #if (DEM_NUMBER_OF_DEM_CLIENT > DEM_ZERO)
    /* @Trace: Dem_SUD_API_20209 */
    *DTCStatusMask = Dem_EvMem_GetAvailableMaskFromMemSetIdx(
    Dem_Client[ClientId].usDemEventMemorySetId);
    LddRetVal = E_OK;
    #endif
  }

  return LddRetVal;
}

/*******************************************************************************
** Function Name        : Dem_GetDTCSeverityAvailabilityMask                  **
**                                                                            **
** Service ID           : 0xb2                                                **
**                                                                            **
** Description          : This API shall be used to get the DTC Severity      **
**                        availability mask.                                  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant for different ClientIDs, Non re-entrant  **
**                        for same ClientId.                                  **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : Dem_DTCSeverityType* DTCSeverityMask                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : The API Dem_PreInit(), Dem_Init()                   **
**                        should have been called in sequence                 **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Dem_GucInit                                         **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        (void)Det_ReportError()                             **
*******************************************************************************/
/* @Trace: SRS_Diag_04141 SRS_Diag_04164 SRS_Diag_04164
 */
FUNC(Std_ReturnType, DEM_CODE) Dem_GetDTCSeverityAvailabilityMask(
        uint8 ClientId,
        P2VAR(Dem_DTCSeverityType, AUTOMATIC, DEM_APPL_DATA) DTCSeverityMask)
{
  Std_ReturnType LddRetVal = E_NOT_OK;
  /* @Trace: SWS_Dem_01181
   * The Dem module shall be able to return the DTC severity availability mask
   * (refer to Dem_GetDTCSeverityAvailabilityMask) in accordance to
   * ISO 14229-1 [1].
   * */

  /* @Trace: SWS_Dem_01182
   * The function Dem_GetDTCSeverityAvailabilityMask shall calculate the DTC
   * severity availability mask in accordance to ISO 14229-1 [1] from the
   * severity configuration of each supported DTC.
   * */
  /* @Trace: SWS_Dem_01177
   * The interface Dem_GetDTCSeverityAvailabilityMask shall provide
   * the DtcSeverityAvailabilityMask to the DCM.
   * */
  /* Module initialization check */
  if (Dem_GucInit != DEM_INIT)
  {
    /* @Trace: Dem_SUD_API_00168 */
    DEM_REPORT_ERROR( DEM_GETDTCSEVERITYAVAILABILITYMASK_SID, DEM_E_UNINIT);
    LddRetVal = E_NOT_OK;
  }
  /* @Trace: Dem_SUD_API_12942 */
  #if (DEM_NUMBER_OF_DEM_CLIENT > DEM_ZERO)
  else if (ClientId >= DEM_NUMBER_OF_DEM_CLIENT)
  {
    /* @Trace: Dem_SUD_API_12946 */
    DEM_REPORT_ERROR( DEM_GETDTCSEVERITYAVAILABILITYMASK_SID,
        DEM_E_WRONG_CONFIGURATION);
    LddRetVal = E_NOT_OK;
  }
  #endif
  /* @Trace: Dem_SUD_API_12947 */
  else if (DTCSeverityMask == NULL_PTR)
  {
    /* @Trace: Dem_SUD_API_12948 */
    DEM_REPORT_ERROR( DEM_GETDTCSEVERITYAVAILABILITYMASK_SID,
        DEM_E_PARAM_POINTER);
    LddRetVal = E_NOT_OK;
  }
  else
  {
    /* get DTCSeverityMask*/
    /* @Trace: Dem_SUD_API_12949 */
    #if (DEM_NUMBER_OF_DEM_CLIENT > DEM_ZERO)
    uint8 LucDtcSeverityInformation = DEM_ZERO;
    uint8 LucDtcClassInformation = DEM_ZERO;
    /* @Trace: Dem_SUD_API_12950 */
    for (uint16 dtcId = DEM_ZERO; dtcId < DEM_MAX_NUMBER_OF_DTC; dtcId++)
    {
      P2CONST(Dem_CombinedDtcType, AUTOMATIC, DEM_VAR) LddCbDTC =
          &Dem_GaaCombinedDtc[dtcId];
      Dem_EventIdType LddEventId = Dem_GetFirstEventOfDTC(LddCbDTC);
      /* @Trace: Dem_SUD_API_12951 */
      if (DEM_TRUE == Dem_EventIdIsValid(LddEventId))
      {
        Dem_EventParameterCPCType LddEvent = &Dem_Event[LddEventId - DEM_ONE];
        /* @Trace: Dem_SUD_API_12952 */
        if (Dem_Client[ClientId].usDemEventMemorySetId ==
              LddEvent->ucEventMemDstIdx)
        {
          /* @Trace: SWS_Dem_01182
           * The function Dem_GetDTCSeverityAvailabilityMask shall calculate the
           * DTC severity availability mask in accordance to ISO 14229-1 [1]
           * from the severity configuration of each supported DTC.
           */
          /* @Trace: Dem_SUD_API_12943 */
          if (DEM_SEVERITY_NO_SEVERITY != LddCbDTC->ddDtcSeverity)
          {
            /* @Trace: Dem_SUD_API_12953 */
            LucDtcSeverityInformation |= LddCbDTC->ddDtcSeverity;
          }
          /* @Trace: Dem_SUD_API_12945 */
          /* polyspace-begin MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] Same as Dead Code. */
          /* polyspace-begin DEFECT:DEAD_CODE [Justified:Low] Dead Code by Configuration. */
          /* polyspace +1 DEFECT:DATA_RACE [Not a defect:Low] "Not a defect" */ 
          if (DEM_DTC_WWHOBD_CLASS_NOCLASS != LddCbDTC->eDemWWHOBDDTCClass)
          {
            /* @Trace: Dem_SUD_API_12944 */
            LucDtcClassInformation |= LddCbDTC->eDemWWHOBDDTCClass;
          }
          /* polyspace-end MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] Same as Dead Code. */
          /* polyspace-end DEFECT:DEAD_CODE [Justified:Low] */
        }
      }
    }
    /* DTCSeverityMask / DTCSeverity byte definition */
    /********************************************************************
     *  Bit 7 | Bit 6 | Bit 5 | Bit 4 | Bit 3 | Bit 2 | Bit 1 | Bit 0   *
     *    DTC severity info   |              DTC class info             *
     ********************************************************************/

    /* @Trace: SWS_Dem_01181
     * The Dem module shall be able to return the DTC severity availability mask
     * (refer to Dem_GetDTCSeverityAvailabilityMask) in accordance to
     *  ISO 14229-1 [1].
     */
    *DTCSeverityMask = LucDtcSeverityInformation | LucDtcClassInformation;
    LddRetVal = E_OK;
    #endif
  }

  return LddRetVal;
}
/*******************************************************************************
** Function Name        : Dem_GetNumberOfFilteredDTC                          **
**                                                                            **
** Service ID           : 0x17                                                **
**                                                                            **
** Description          : This API shall be used to get the number of         **
**                        Filtered DTC                                        **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Re-entrant for different ClientIDs, Non re-entrant  **
**                        for same ClientId.                                  **
**                                                                            **
** Input Parameters     : ClientId                                            **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : uint16* NumberOfFilteredDTC                         **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : The API Dem_PreInit(), Dem_Init()                   **
**                        should have been called in sequence                 **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        Dem_GucInit                                         **
**                                                                            **
**                        Function(s) invoked :                               **
**                        (void)Det_ReportError()                             **
*******************************************************************************/
FUNC(Std_ReturnType, DEM_CODE) Dem_GetNumberOfFilteredDTC(uint8 ClientId,
P2VAR (uint16, AUTOMATIC, DEM_APPL_DATA) NumberOfFilteredDTC)
{
  /* @Trace: SWS_Dem_00061
   * The function Dem_GetNumberOfFilteredDTC shall get the number of DTCs
   * matching the filter criteria defined by the function call of
   * Dem_SetDTCFilter
   * */

  Std_ReturnType LddRetVal = DEM_PENDING;

  boolean LblGetNumberOfFilteredDTCSIDLockIdx =
      Dem_SetDTCFilterServiceIsLock(
          ClientId, DEM_GETNUMBEROFFILTEREDDTC_SID_LOCK_IDX);
  /* @Trace: Dem_SUD_API_20302 */
  #if (DEM_NUMBER_OF_DEM_CLIENT > DEM_ZERO)
  if (ClientId >= DEM_NUMBER_OF_DEM_CLIENT)
  {
    /* @Trace: Dem_SUD_API_20298 */
    DEM_REPORT_ERROR(DEM_GETNUMBEROFFILTEREDDTC_SID, DEM_E_PARAM_DATA);
    LddRetVal = E_NOT_OK;
  }
  else
  #endif
  /* @Trace: Dem_SUD_API_20303 */
  if (DEM_TRUE == LblGetNumberOfFilteredDTCSIDLockIdx)
  {
    /* @Trace: Dem_SUD_API_20066 */
    LddRetVal = E_NOT_OK;
  }
  else
  {
    Dem_SetDTCFilterServiceLock(ClientId,
         DEM_GETNUMBEROFFILTEREDDTC_SID_LOCK_IDX);
    /*  Check   module  Initialization  status  */
    if (Dem_GucInit != DEM_INIT)
    {
      /* @Trace: Dem_SUD_API_20304 */
      DEM_REPORT_ERROR(DEM_GETNUMBEROFFILTEREDDTC_SID, DEM_E_UNINIT);
      LddRetVal = E_NOT_OK;
    }
    else if (NumberOfFilteredDTC == NULL_PTR)
    {
      /* @Trace: Dem_SUD_API_20305 */
      DEM_REPORT_ERROR(DEM_GETNUMBEROFFILTEREDDTC_SID, DEM_E_PARAM_POINTER);
      LddRetVal = E_NOT_OK;
    }
    /* @Trace: Dem_SUD_API_20306 */
    #if (DEM_NUMBER_OF_DEM_CLIENT > DEM_ZERO)
    else if (E_OK != Dem_DTCFilterState[ClientId].dfs_resultGetDtcFilter)
    {
      /* @Trace: SWS_Dem_01267
       * If any of the APIs requesting a Dem_SetDTCFilter (see [SWS_Dem_00057])
       * is called prior of calling Dem_SetDTCFilter a Det error
       * DEM_E_WRONG_CONDITION shall be reported for this API call.
       * */
      /* @Trace: Dem_SUD_API_20068 */
      DEM_REPORT_ERROR(DEM_GETNUMBEROFFILTEREDDTC_SID, DEM_E_WRONG_CONDITION);
      LddRetVal = E_NOT_OK;
    }
    #endif
    /* @Trace: Dem_SUD_API_20299 */
    else
    {
      *NumberOfFilteredDTC = DEM_ZERO;
      /* DEM_JOB_TRIGGER: by Dem_SetFreezeFrameRecordFilter
       * DEM_JOB_RUNNING: by Dem_MainFunction
       * DEM_JOB_DONE:    after job is finished by Dem_MainFunction
       */
      if ((DEM_JOB_TRIGGER == Dem_DTCFilterState[ClientId].dfs_JobAction) ||
      (DEM_JOB_RUNNING == Dem_DTCFilterState[ClientId].dfs_JobAction))
      {
        /* Return appropriate value */
        /* @Trace: Dem_SUD_API_20300 */
        LddRetVal = DEM_PENDING;
      }
      else if (DEM_JOB_DONE == Dem_DTCFilterState[ClientId].dfs_JobAction)
      {
        /* @Trace: Dem_SUD_API_20301 */
        /* Return the number of filtered DTC's */
        *NumberOfFilteredDTC =
        		Dem_DTCFilterState[ClientId].dfs_NumOfFilteredDTC;
        LddRetVal = E_OK;
      }
      else
      {
        /* @Trace: SWS_Dem_01266
         * In case of calling any subsequent function of Dem_SetDTCFilter
         * (see [SWS_Dem_00057])
         * after the initial Dem_SetDTCFilter did not return E_OK, the Dem shall
         * shall return E_NOT_OK on this subsequent functioncall.
         */
        /* @Trace: Dem_SUD_API_20067 */
        LddRetVal = E_NOT_OK;
      }
    }
    Dem_SetDTCFilterServiceUnLock(ClientId,
        DEM_GETNUMBEROFFILTEREDDTC_SID_LOCK_IDX);
  }
  return LddRetVal;
}/* End of API */
/*******************************************************************************
** Function Name        : Dem_GetNumberOfFreezeFrameRecords                   **
**                                                                            **
** Service ID           : 0x5a                                                **
**                                                                            **
** Description          : This function returns the number of all freeze      **
**                        frame records currently stored in the primary event **
**                        memory                                              **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Reentrant Reentrant for different ClientIds, non    **
**                        reentrant for the same ClientId.                    **
**                                                                            **
** Input Parameters     : uint8 ClientId                                      **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : uint16* NumberOfFilteredRecords                     **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : The API Dem_PreInit(), Dem_Init()                   **
**                        should have been called in sequence                 **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        Dem_GucInit                                         **
**                                                                            **
**                        Function(s) invoked :                               **
**                        (void)Det_ReportError()                             **
*******************************************************************************/
/* @Trace: SRS_BSW_00369 SRS_Diag_04205
 */
FUNC(Std_ReturnType, DEM_CODE)
Dem_GetNumberOfFreezeFrameRecords(
  uint8 ClientId,
  P2VAR (uint16, AUTOMATIC, DEM_APPL_DATA) NumberOfFilteredRecords)
{
  /* @Trace: SWS_Dem_01312
   * Dem_GetNumberOfFreezeFrameRecords shall retrieve the number of freeze
   * frame records in primary memory that match the current filter
   * */
  Std_ReturnType LddRetVal = DEM_PENDING;

  boolean LblGetNumberOfFreezeFrameRecordsSIDLockIdx =
      Dem_SetFFRecordFilterServiceIsLock(ClientId,
          DEM_GETNUMBEROFFREEZEFRAMERECORDS_SID_LOCK_IDX);

  #if (DEM_NUMBER_OF_DEM_CLIENT > DEM_ZERO)
  if (ClientId >= DEM_NUMBER_OF_DEM_CLIENT)
  {
    /* @Trace: Dem_SUD_API_20570 */
    DEM_REPORT_ERROR(DEM_GETNUMBEROFFREEZEFRAMERECORDS_SID, DEM_E_PARAM_DATA);
    LddRetVal = DEM_PENDING;
  }
  else
  #endif
  if (DEM_TRUE == LblGetNumberOfFreezeFrameRecordsSIDLockIdx)
  {
    /* @Trace: Dem_SUD_API_20119 */
    LddRetVal = DEM_PENDING;
  }
  else
  {
    Dem_SetFFRecordFilterServiceLock(ClientId,
        DEM_GETNUMBEROFFREEZEFRAMERECORDS_SID_LOCK_IDX);
    /*  Check   module  Initialization  status  */
    if (Dem_GucInit != DEM_INIT)
    {
      /* @Trace: Dem_SUD_API_20571 */
      DEM_REPORT_ERROR(DEM_GETNUMBEROFFREEZEFRAMERECORDS_SID, DEM_E_UNINIT);
      LddRetVal = DEM_PENDING;
    }
    /* @Trace: Dem_SUD_API_20572 */
    #if (DEM_NUMBER_OF_DEM_CLIENT > DEM_ZERO)
    else if ( E_OK != Dem_FilteredFFRecord[ClientId].resultSetFFRecFilter)
    {
      /* @Trace: SWS_Dem_01313
       * API behavior without set DTC filter d If any of the APIs requiring a
       * Dem_SetFreezeFrameRecordFilter is called without a prior call of
       * Dem_SetFreezeFrameRecordFilter for this client, the Dem shall report
       * the Det DEM_E_WRONG_CONDITION.
       * */
      /* @Trace: Dem_SUD_API_20120 */
      DEM_REPORT_ERROR(DEM_GETNUMBEROFFREEZEFRAMERECORDS_SID,
          DEM_E_WRONG_CONDITION);
      LddRetVal = DEM_PENDING;
    }
    #endif
    /* @Trace: Dem_SUD_API_20573 */
    else if (NumberOfFilteredRecords == NULL_PTR)
    {
      /* @Trace: Dem_SUD_API_20569 */
      DEM_REPORT_ERROR(DEM_GETNUMBEROFFREEZEFRAMERECORDS_SID,
          DEM_E_PARAM_POINTER);
      LddRetVal = DEM_PENDING;
    }
    else
    {
      /* @Trace: Dem_SUD_API_20568 */
      *NumberOfFilteredRecords = Dem_FilteredFFRecord[ClientId].
          numberOfFilteredRecords;
      LddRetVal = E_OK;
    }
    Dem_SetFFRecordFilterServiceUnLock(ClientId,
        DEM_GETNUMBEROFFREEZEFRAMERECORDS_SID_LOCK_IDX);
  }
  return LddRetVal;
}/* End of API */
/*******************************************************************************
** Function Name        : Dem_GetNextFilteredDTC                              **
**                                                                            **
** Service ID           : 0x18                                                **
**                                                                            **
** Description          : This API shall be used to get the next Filtered     **
**                        DTC                                                 **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : uint32* DTC,                                        **
**                        uint8* DTCStatus                                    **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : The API Dem_PreInit(), Dem_Init()                   **
**                        should have been called in sequence                 **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        Dem_GucInit                                         **
**                        Dem_Event                                           **
**                                                                            **
**                        Function(s) invoked :                               **
**                        (void)Det_ReportError                               **
*******************************************************************************/
/* @Trace: SRS_Diag_04010 SRS_Diag_04195 SRS_Diag_04220
 */
/* polyspace +1 CODE-METRICS:LEVEL [Not a defect:LOW] "Not a defect" */ 
FUNC(Std_ReturnType, DEM_CODE) Dem_GetNextFilteredDTC(
    uint8 ClientId,
  P2VAR (uint32, AUTOMATIC, DEM_APPL_DATA) DTC,
  P2VAR (uint8, AUTOMATIC, DEM_APPL_DATA) DTCStatus)
{

  /* @Trace: SWS_Dem_00216
   * With each call to the function Dem_GetNextFilteredDTC the Dem module shall
   * return the next DTC and its associated status matching the filter criteria
   * defined by the function call of Dem_SetDTCFilter
   * */
  Std_ReturnType LddRetVal = DEM_NO_SUCH_ELEMENT;

  boolean LblGetNextFilteredDTCSIDLockIdx =
      Dem_SetDTCFilterServiceIsLock(ClientId,
          DEM_GETNEXTFILTEREDDTC_SID_LOCK_IDX);
  /* @Trace: Dem_SUD_API_20317 */
  #if (DEM_NUMBER_OF_DEM_CLIENT > DEM_ZERO)
  if (ClientId >= DEM_NUMBER_OF_DEM_CLIENT)
  {
    /* @Trace: Dem_SUD_API_20324 */
    DEM_REPORT_ERROR(DEM_GETNEXTFILTEREDDTC_SID, DEM_E_PARAM_DATA);
    LddRetVal = E_NOT_OK;
  }
  else
  #endif
  /* @Trace: Dem_SUD_API_20325 */
  if (DEM_TRUE == LblGetNextFilteredDTCSIDLockIdx)
  {
    /* @Trace: Dem_SUD_API_20069 */
    LddRetVal = E_NOT_OK;
  }
  else
  {
    Dem_SetDTCFilterServiceLock(ClientId,
        DEM_GETNEXTFILTEREDDTC_SID_LOCK_IDX);
    /* Check module Initialization status */
    if (DEM_INIT != Dem_GucInit)
    {
      /* @Trace: Dem_SUD_API_20326 */
      DEM_REPORT_ERROR(DEM_GETNEXTFILTEREDDTC_SID, DEM_E_UNINIT);
      LddRetVal = DEM_NO_SUCH_ELEMENT;
    }
    else if ( (NULL_PTR == DTC) || (NULL_PTR == DTCStatus))
    {
      /* @Trace: Dem_SUD_API_20075 */
      DEM_REPORT_ERROR(DEM_GETNEXTFILTEREDDTC_SID, DEM_E_PARAM_POINTER);
      LddRetVal = DEM_NO_SUCH_ELEMENT;
    }
    /* @Trace: Dem_SUD_API_20327 */
    #if (DEM_NUMBER_OF_DEM_CLIENT > DEM_ZERO)
    else if (E_OK != Dem_DTCFilterState[ClientId].dfs_resultGetDtcFilter)
    {
      /* @Trace: SWS_Dem_01267
       * If any of the APIs requesting a Dem_SetDTCFilter (see [SWS_Dem_00057])
       * is called prior of calling Dem_SetDTCFilter a Det error
       * DEM_E_WRONG_CONDITION shall be reported for this API call.
       * */
      /* @Trace: SWS_Dem_01266
         * In case of calling any subsequent function of Dem_SetDTCFilter (see
         * [SWS_Dem_00057]) after the initial Dem_SetDTCFilter did not return
         * E_OK, the Dem shall shall return E_NOT_OK on this subsequent
         * functioncall.
         */
      /* @Trace: Dem_SUD_API_20328 */
      DEM_REPORT_ERROR(DEM_GETNEXTFILTEREDDTC_SID, DEM_E_WRONG_CONDITION);
      LddRetVal = E_NOT_OK;
    }
    #endif
    /* @Trace: Dem_SUD_API_20312 */
    else if ((DEM_JOB_TRIGGER == Dem_DTCFilterState[ClientId].dfs_JobAction) ||
             (DEM_JOB_RUNNING == Dem_DTCFilterState[ClientId].dfs_JobAction))
    {
      DEM_REPORT_ERROR(DEM_GETNEXTFILTEREDDTC_SID, DEM_E_WRONG_CONDITION);
      /* @Trace: SWS_Dem_00653
       * The API Dem_GetNextFilteredDTC shall not return the value DEM_PENDING
       * when DTCFormat = DEM_DTC_FORMAT_OBD (indicating emission-related
       * services).
       * */
      /* @Trace: Dem_SUD_API_20070 */
      if (DEM_DTC_FORMAT_OBD != Dem_DTCFilterState[ClientId].dfs_DTCOrigin)
      {
        /* Return appropriate value */
        /* @Trace: Dem_SUD_API_20313 */
        LddRetVal = DEM_PENDING;
      }
    }
    else if (DEM_JOB_DONE != Dem_DTCFilterState[ClientId].dfs_JobAction)
    {
      /* @Trace: Dem_SUD_API_20072 */
      Dem_DTCFilterState[ClientId].dfs_NextEvent = DEM_NO_EVENT;
      LddRetVal = DEM_NO_SUCH_ELEMENT;
    }
    else if (DEM_NO_EVENT == Dem_DTCFilterState[ClientId].dfs_NextEvent)
    {
      /* @Trace: Dem_SUD_API_20073 */
      LddRetVal = DEM_NO_SUCH_ELEMENT;
    }
    /* @Trace: SWS_Dem_01101
     * A suppressed DTC shall not be visible for the following Dcm
     * query-functions; therefore the following functions shall treat the DTC
     * as if filter is not matching.
     * */
    else if (DEM_TRUE == Dem_EvIsProcStateTriggered(
        Dem_DTCFilterState[ClientId].dfs_NextEvent, DEM_EVPROCSTATE_DTC_SUPP))
    {
      /* @Trace: Dem_SUD_API_20074 */
      LddRetVal = DEM_NO_SUCH_ELEMENT;
    }
    else
    {
      /* dfs_NextEvent is EventId.*/
      /* polyspace-begin MISRA2012:14.2 [Justified:Low] Justify with annotations */
      for (; Dem_DTCFilterState[ClientId].dfs_NextEvent <= DEM_NUMBER_OF_EVENTS;
             Dem_DTCFilterState[ClientId].dfs_NextEvent++)
      /* polyspace-end MISRA2012:14.2 [Justified:Low] Justify with annotations */
      {
        /* It can set a only first event(out of combined dtc) to true */
        /* @Trace: Dem_SUD_API_20314 */
        if ((boolean)DEM_TRUE == Dem_EvIsProcStateTriggered(
            Dem_DTCFilterState[ClientId].dfs_NextEvent,
            DEM_EVPROCSTATE_DTC_FILTER))
        {
          P2CONST(Dem_CombinedDtcType, AUTOMATIC, DEM_VAR) LddCbDTC =
              Dem_GetCbDTCByEventId(Dem_DTCFilterState[ClientId].dfs_NextEvent);

          Dem_EvClearProcState(Dem_DTCFilterState[ClientId].dfs_NextEvent,
              DEM_EVPROCSTATE_DTC_FILTER);

          if (NULL_PTR != LddCbDTC)
          {
            /* @Trace: SWS_Dem_00410
             * The Dem module shall report DTCs in the chronological order of
             * the event storage (refer to API Dem_GetNextFilteredDTC), if:
             * the DTCStatus parameter has the pending DTC or confirmed DTC
             * bit or both bits set
             * - all other bits of the DTCStatus parameter are set to false
             * - DemResetConfirmedBitOnOverflow is set to true
             */
            *DTC = Dem_GetDtcByCombineDTC(LddCbDTC);

            /* If specific StatusAvailablilityMask of a DTC is existed */
            /* @Trace: SWS_Dem_01049
             * If the Dem module is requested to report the status of a
             * combined DTC (refer e.g. Dem_GetStatusOfDTC or
             * Dem_GetNextFilteredDTC), the calculation
             * of the status byte shall be performed according [SWS_Dem_00441].
             * */
            /* polyspace-begin MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] Same as Dead Code. */
            /* polyspace-begin DEFECT:DEAD_CODE [Justified:Low] Dead Code by Configuration. */
            /* polyspace +1 DEFECT:DATA_RACE [Not a defect:Low] "Not a defect" */ 
            if (DEM_ZERO != LddCbDTC->UdsStatusAvailabilityMask)
            {
              /* @Trace: Dem_SUD_API_20318 */
              *DTCStatus = Dem_GetDTCStatus(Dem_DTCFilterState[ClientId].
                  dfs_NextEvent) & LddCbDTC->UdsStatusAvailabilityMask;
            }
            else
            {
              /* @Trace: Dem_SUD_API_20316 */
              *DTCStatus = Dem_GetDTCStatus(Dem_DTCFilterState[ClientId].
                  dfs_NextEvent);
            }
            /* polyspace-end MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] Same as Dead Code. */
            /* polyspace-end DEFECT:DEAD_CODE [Justified:Low] */

            if (DEM_ZERO != Dem_DTCFilterState[ClientId].dfs_DTCStatusMask)
            {
              /* @Trace: Dem_SUD_API_20320 */
              if ((Dem_DTCFilterState[ClientId].dfs_DTCStatusMask &
                  (*DTCStatus)) != 0)
              {
                /* @Trace: Dem_SUD_API_20321 */
                LddRetVal = E_OK;
              }
            }
            else
            {
              /* @Trace: Dem_SUD_API_20319 */
              LddRetVal = E_OK;
            }

            if (E_OK == LddRetVal)
            {
              break;
            }
          }
          else
          {
            /* @Trace: Dem_SUD_API_20315 */
            DEM_REPORT_ERROR(DEM_GETNEXTFILTEREDDTC_SID, DEM_E_PARAM_DATA);
          }
        }
      }
      /* @Trace: Dem_SUD_API_20323 */
      if (E_OK != LddRetVal)
      {
        /* @Trace: Dem_SUD_API_20322 */
        Dem_DTCFilterState[ClientId].dfs_NextEvent = DEM_NO_EVENT;
      }
    }
    Dem_SetDTCFilterServiceUnLock(ClientId,
        DEM_GETNEXTFILTEREDDTC_SID_LOCK_IDX);
  }

  return LddRetVal;
}/* End of API */
/*******************************************************************************
** Function Name        : Dem_GetDTCByOccurrenceTime                          **
**                                                                            **
** Service ID           : 0x19                                                **
**                                                                            **
** Description          : Gets the DTC by occurrence time. There is no        **
**                        explicit parameter for the DTC-origin as the        **
**                        origin always is DEM_DTC_ORIGIN_PRIMARY_MEMORY.     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant for different ClientIDs, Non re-entrant  **
**                        for same ClientId.                                  **
**                                                                            **
** Input Parameters     : DTCRequest                                          **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : uint32* DTC                                         **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : The API Dem_PreInit(), Dem_Init()                   **
**                        should have been called in sequence                 **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Dem_GucInit                                         **
**                                                                            **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        (void)Det_ReportError                               **
*******************************************************************************/
/* @Trace: SRS_Diag_04102 SRS_Diag_04195 SRS_Diag_04220 SRS_Diag_04072
 */
#if (DEM_DCM_RPT_FAILEDCONFIRMEDDTCINFO_USED == STD_ON)
FUNC(Std_ReturnType, DEM_CODE)
Dem_GetDTCByOccurrenceTime(
  uint8 ClientId,
  Dem_DTCRequestType DTCRequest,
  P2VAR (uint32, AUTOMATIC, DEM_APPL_DATA) DTC)
{
  /* @Trace: SWS_Dem_00219
   * The function Dem_GetDTCByOccurrenceTime shall provide the capability
   * to get one DTC stored in the primary event memory of the addressed
   * DemEventMemorySet according to the API parameter DTCRequest.
   * */
  Std_ReturnType LddRetVal = DEM_NO_SUCH_ELEMENT;

  if (Dem_GucInit != DEM_INIT)
  {
    /* @Trace: Dem_SUD_API_20435 */
    DEM_REPORT_ERROR(DEM_GETDTCBYOCCURRENCETIME_SID, DEM_E_UNINIT);
    LddRetVal = E_NOT_OK;
  }
  else if (DTC == NULL_PTR)
  {
    /* @Trace: Dem_SUD_API_20439 */
    DEM_REPORT_ERROR(DEM_GETDTCBYOCCURRENCETIME_SID, DEM_E_PARAM_POINTER);
    LddRetVal = E_NOT_OK;
  }
  else if ((DTCRequest != DEM_FIRST_FAILED_DTC) &&
           (DTCRequest != DEM_MOST_RECENT_FAILED_DTC) &&
           (DTCRequest != DEM_MOST_REC_DET_CONFIRMED_DTC) &&
           (DTCRequest != DEM_FIRST_DET_CONFIRMED_DTC))
  {
    /* @Trace: Dem_SUD_API_20440 */
    DEM_REPORT_ERROR(DEM_GETDTCBYOCCURRENCETIME_SID, DEM_E_PARAM_DATA);
    LddRetVal = E_NOT_OK;
  }
  /* @Trace: Dem_SUD_API_20441 */
  #if (DEM_NUMBER_OF_DEM_CLIENT > DEM_ZERO)
  else if (ClientId >= DEM_NUMBER_OF_DEM_CLIENT)
  {
    /* @Trace: Dem_SUD_API_20442 */
    DEM_REPORT_ERROR(DEM_GETDTCBYOCCURRENCETIME_SID, DEM_E_PARAM_DATA);
    LddRetVal = E_NOT_OK;
  }
  #endif
  else
  {
    /* @Trace: SWS_Dem_00935
     *      1.first failed DTC requested
     *      2.most recent failed DTC requested
     *      3. most recently detected confirmed DTC requested
     *      4. first detected confirmed DTC requested */
    /* @Trace: Dem_SUD_API_20443 */
    if (E_OK == Dem_EvMem_GetDTCByOccurrenceTime(ClientId, DTCRequest, DTC))
    {
      Dem_EventIdType LddEventId = Dem_GetEventIdByDTC(
           DEM_GETDTCBYOCCURRENCETIME_SID,
           *DTC,
           Dem_ClientSelectDtcState[ClientId].selectedDTCFormat);
      /* @Trace: Dem_SUD_API_20436 */
      if ((LddEventId <= DEM_NUMBER_OF_EVENTS) && (DEM_NO_EVENT != LddEventId))
      {
        /* @Trace: SWS_Dem_01101
         * A suppressed DTC shall not be visible for the following Dcm
         * query-functions; therefore the following functions shall treat
         * the DTC as if filter is not matching:
         * Dem_GetDTCByOccurrenceTime
         * */
        if ((boolean)DEM_TRUE != Dem_EvIsProcStateTriggered(LddEventId,
            DEM_EVPROCSTATE_DTC_SUPP))
        {
          /* @Trace: Dem_SUD_API_20438 */
          /* Set the return value */
          LddRetVal = E_OK;
        }
        else
        {
          /* @Trace: Dem_SUD_API_20437 */
          LddRetVal = E_NOT_OK;
        }
      }
      else
      {
        /* @Trace: SWS_Dem_00221
         * The API Dem_GetDTCByOccurrenceTime shall return DEM_NO_SUCH_ELEMENT,
         * if no DTC is matching the requested occurrence time in the
         * parameter DTCRequest.
         * */
        /* LddRetVal = DEM_NO_SUCH_ELEMENT; */
      }
    }
    else
    {
      /* @LddRetVal = DEM_NO_SUCH_ELEMENT; */
    }
  }
  /* @Trace: Dem_SUD_API_20095 */
  return LddRetVal;
}
#endif
/*******************************************************************************
** Function Name        : Dem_GetNextFilteredRecord                           **
**                                                                            **
** Service ID           : 0x3a                                                **
**                                                                            **
** Description          : This API provides Gets the next freeze frame record **
**                        number and its associated DTC stored in the event   **
**                        memory. The interface has an asynchronous behaviour **
**                        because NvRAM access might be required.             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant for different ClientIds, non reentrant    **
**                        for the same ClientId.                              **
**                                                                            **
** Input Parameters     : uint8 ClientId                                      **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : uint32* DTC,                                        **
**                        uint8* RecordNumber                                 **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : The API Dem_PreInit(), Dem_Init()                   **
**                        should have been called in sequence                 **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Dem_GucInit                                         **
**                        Dem_FilteredFFRecord                                **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        (void)Det_ReportError                               **
*******************************************************************************/
/* @Trace: SRS_BSW_00369 SRS_Diag_04074 SRS_Diag_04220
 */
/* polyspace +1 CODE-METRICS:LEVEL [Not a defect:Low] "Not a defect" */
FUNC(Std_ReturnType, DEM_CODE) Dem_GetNextFilteredRecord(
  uint8 ClientId,
  P2VAR (uint32, AUTOMATIC, DEM_APPL_DATA) DTC,
  P2VAR (uint8, AUTOMATIC, DEM_APPL_DATA) RecordNumber)
{
  Std_ReturnType LddRetVal = DEM_NO_SUCH_ELEMENT;

  boolean LblGetNextFilteredRecordSIDLockIdx =
      Dem_SetFFRecordFilterServiceIsLock(ClientId,
          DEM_GETNEXTFILTEREDRECORD_SID_LOCK_IDX);
  /* @Trace: Dem_SUD_API_20414 */
  #if (DEM_NUMBER_OF_DEM_CLIENT > DEM_ZERO)
  if (ClientId >= DEM_NUMBER_OF_DEM_CLIENT)
  {
    /* @Trace: Dem_SUD_API_20425 */
    DEM_REPORT_ERROR(DEM_GETNEXTFILTEREDRECORD_SID, DEM_E_PARAM_DATA);
    LddRetVal = DEM_NO_SUCH_ELEMENT;
  }
  else
  #endif
  /* @Trace: Dem_SUD_API_20428 */
  if (DEM_TRUE == LblGetNextFilteredRecordSIDLockIdx)
  {
    /* @Trace: Dem_SUD_API_20091 */
    LddRetVal = DEM_PENDING;
  }
  else
  {
    Dem_SetFFRecordFilterServiceLock(ClientId,
        DEM_GETNEXTFILTEREDRECORD_SID_LOCK_IDX);
    /* Check module Initialization status */
    if (DEM_INIT != Dem_GucInit)
    {
      /* @Trace: Dem_SUD_API_20430 */
      DEM_REPORT_ERROR(DEM_GETNEXTFILTEREDRECORD_SID, DEM_E_UNINIT);
      LddRetVal = DEM_NO_SUCH_ELEMENT;
    }
    /* @Trace: Dem_SUD_API_20432 */
    #if (DEM_NUMBER_OF_DEM_CLIENT > DEM_ZERO)
    else if ( E_OK != Dem_FilteredFFRecord[ClientId].resultSetFFRecFilter)
    {
      /* @Trace: SWS_Dem_01313
       * API behavior without set DTC filter d If any of the APIs requiring a
       * Dem_SetFreezeFrameRecordFilter is called without a prior call of
       * Dem_SetFreezeFrameRecordFilter for this client, the Dem shall report
       * the Det DEM_E_WRONG_CONDITION.
       * */
      /* @Trace: Dem_SUD_API_20092 */
      DEM_REPORT_ERROR( DEM_GETNEXTFILTEREDRECORD_SID, DEM_E_WRONG_CONDITION);
      LddRetVal = DEM_NO_SUCH_ELEMENT;
    }
    #endif
    /* @Trace: Dem_SUD_API_20433 */
    else if ( (NULL_PTR == DTC) || (NULL_PTR == RecordNumber))
    {
      /* @Trace: Dem_SUD_API_20434 */
      DEM_REPORT_ERROR(DEM_GETNEXTFILTEREDRECORD_SID, DEM_E_PARAM_POINTER);
      LddRetVal = DEM_NO_SUCH_ELEMENT;
    }
    /* @Trace: SWS_Dem_01101
     * A suppressed DTC shall not be visible for the following Dcm
     * query-functions; therefore the following functions shall treat the DTC as
     * if filter is not matching.
     * */
    else if (DEM_TRUE == Dem_EvIsProcStateTriggered(
        Dem_FilteredFFRecord[ClientId].nextEvent, DEM_EVPROCSTATE_DTC_SUPP))
    {
      /* @Trace: Dem_SUD_API_20093 */
      LddRetVal = DEM_NO_SUCH_ELEMENT;
    }
    else
    {
      /* @Trace: Dem_SUD_API_20417 */
      #if ((DEM_MAX_EVENT_DESTINATION_SELECTED > DEM_ZERO) && \
           (DEM_SIZE_OF_FREEZEFRAME > DEM_ZERO))
      Dem_EventIdType LddEventId;
      Dem_EventMemoryEntryPtrType LddEntry;

      /*  if event is deleled or aged, Dem returns the next event.*/
      /* @Trace: Dem_SUD_API_20418 */
      /* polyspace-begin MISRA2012:14.2 [Justified:Low] Justify with annotations */
      for (; Dem_FilteredFFRecord[ClientId].nextEvent <= DEM_NUMBER_OF_EVENTS;
             Dem_FilteredFFRecord[ClientId].nextEvent++)
      /* polyspace-end MISRA2012:14.2 [Justified:Low] Justify with annotations */
      {
        /* @Trace: Dem_SUD_API_20419 */
        if ((boolean)DEM_TRUE == Dem_EvIsProcStateTriggered(
              Dem_FilteredFFRecord[ClientId].nextEvent,
              DEM_EVPROCSTATE_DTC_FILTER ))
        {
          /* Session checking is not necessary.
           * Dcm calls the this function after calling
           * Dem_SetFreezeFrameRecordFilter
           */
          LddEventId = Dem_FilteredFFRecord[ClientId].nextEvent;

          LddEntry = Dem_EvMem_FindEntry(LddEventId,
              DEM_DTC_ORIGIN_PRIMARY_MEMORY);
          /* @Trace: Dem_SUD_API_20420 */
          if (NULL_PTR != LddEntry)
          {
            Dem_EventParameterPCType LddEvent =
                &Dem_Event[LddEventId - DEM_ONE];
            /* @Trace: Dem_SUD_API_20421 */
            if (LddEvent->e_PointToData < DEM_NUM_OF_EVENTRELATEDDATA)
            {
              Dem_EventRelatedDataCPCType EvData =
                  &Dem_EventRelatedData[LddEvent->e_PointToData];
              const Dem_RecordNumberType maxRecordCount =
                  Dem_EvMem_GetRecNumOfFF(LddEntry);
              /* @Trace: Dem_SUD_API_20422 */
              if ( (Dem_FilteredFFRecord[ClientId].nextRecord <
                       maxRecordCount) &&
                   (Dem_FilteredFFRecord[ClientId].nextRecord <
                       EvData->MaxNumOfFreezeFrameRecords)
              )
              {
                /* if Event has no ff , FFRecordClassIndex is 0xFFFF */
                const uint16 offset = EvData->FFRecordClassIndex +
                    Dem_FilteredFFRecord[ClientId].nextRecord;
                /* @Trace: Dem_SUD_API_20423 */
                if (offset < DEM_NUM_OF_FRREZEFRAMERECORDCLASS)
                {
                  /* @Trace: SWS_Dem_00225
                   * With each call to the function Dem_GetNextFilteredRecord
                   * the Dem module shall return the next DTC and its
                   * associated relative addressed freeze frame record
                   * numbers matching the filter criteria defined by the
                   * function call Dem_SetFreezeFrameRecordFilter.
                   * */
                  /* @Trace: Dem_SUD_API_20424 */
                  (void)Dem_GetEventDTC(&Dem_Event[LddEventId - DEM_ONE],
                      DTC, DEM_DTC_FORMAT_UDS);
                  *RecordNumber = Dem_FreezeFrameRecordClass[offset].
                      FreezeFrameRecordNumber;

                  /* Increment index count of record number for one dtc */
                  Dem_FilteredFFRecord[ClientId].nextRecord++;
                  LddRetVal = E_OK;
                  break;
                }
              }
            }
          }
          /* [1] No exist in event memory
           * [2] end loop about all records of a freeze frame of a event
           * [3] etc */
          /* @Trace: Dem_SUD_API_20094 */
          Dem_EvClearProcState(Dem_FilteredFFRecord[ClientId].nextEvent,
              DEM_EVPROCSTATE_DTC_FILTER);
        }

        /* Initialize the Index for next event */
        Dem_FilteredFFRecord[ClientId].nextRecord = DEM_ZERO;
      }
      #endif
    }
    /* @Trace: Dem_SUD_API_20426 */
    if (E_OK != LddRetVal)
    {
      /* @Trace: Dem_SUD_API_20427 */
      Dem_FilteredFFRecord[ClientId].nextRecord = DEM_ZERO;
      Dem_FilteredFFRecord[ClientId].nextEvent = DEM_NO_EVENT;
    }
    Dem_SetFFRecordFilterServiceUnLock(ClientId,
        DEM_GETNEXTFILTEREDRECORD_SID_LOCK_IDX);
  }
  return LddRetVal;
}/* End of API */
/*******************************************************************************
** Function Name        : Dem_GetNextFilteredDTCAndFDC                        **
**                                                                            **
** Service ID           : 0x3b                                                **
**                                                                            **
** Description          : This API provides the capability to gets the next   **
**                        filtered DTC and its associated Fault Detection     **
**                        Counter (FDC) matching the filter criteria. The     **
**                        interface has an asynchronous behavior, because a   **
**                        large number of DTCs has to be processed and the    **
**                        FDC might be received asynchronously from a SW-C,   **
**                        too                                                 **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Re-entrant for different ClientIDs, Non re-entrant  **
**                        for same ClientId.                                  **
**                                                                            **
** Input Parameters     : ClientId                                            **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : DTC,                                                **
**                        DTCFaultDetectionCounter                            **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : The API Dem_PreInit(), Dem_Init()                   **
**                        should have been called in sequence                 **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Dem_GucInit                                         **
**                        Dem_Event                                           **
**                        Dem_GaaPreDebounceMonitorInternal                   **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        (void)Det_ReportError                               **
*******************************************************************************/
/* @Trace: SRS_Diag_04010 SRS_Diag_04220
 */
/* polyspace +2 CODE-METRICS:LEVEL [Not a defect:Low] "Not a defect" */
FUNC(Std_ReturnType, DEM_CODE)
Dem_GetNextFilteredDTCAndFDC(
  uint8 ClientId,
  P2VAR (uint32, AUTOMATIC, DEM_APPL_DATA) DTC,
  P2VAR (sint8, AUTOMATIC, DEM_APPL_DATA) DTCFaultDetectionCounter)
{
  /* @Trace: SWS_Dem_00228
   * With each call to the function Dem_GetNextFilteredDTCAndFDC the Dem
   * module shall return the next DTC and its associated fault detection counter
   * (FDC, refer to [SWS_Dem_00264]) matching the filter criteria defined
   * by the function call Dem_SetDTCFilter
   * */
  Std_ReturnType LddRetVal = DEM_NO_SUCH_ELEMENT;

  boolean LblGetNextFilteredDTCAndFDCSIDLockIdx =
      Dem_SetDTCFilterServiceIsLock(ClientId,
          DEM_GETNEXTFILTEREDDTCANDFDC_SID_LOCK_IDX);
  /* @Trace: Dem_SUD_API_20336 */
  #if (DEM_NUMBER_OF_DEM_CLIENT > DEM_ZERO)
  if (ClientId >= DEM_NUMBER_OF_DEM_CLIENT)
  {
    /* @Trace: Dem_SUD_API_20342 */
    DEM_REPORT_ERROR(DEM_GETNEXTFILTEREDDTCANDFDC_SID, DEM_E_PARAM_DATA);
    LddRetVal = E_NOT_OK;
  }
  else
  #endif
  /* @Trace: Dem_SUD_API_20347 */
  if (DEM_TRUE == LblGetNextFilteredDTCAndFDCSIDLockIdx)
  {
    /* @Trace: Dem_SUD_API_20076 */
    LddRetVal = E_NOT_OK;
  }
  else
  {
    Dem_SetDTCFilterServiceLock(ClientId,
        DEM_GETNEXTFILTEREDDTCANDFDC_SID_LOCK_IDX);

    if (DEM_INIT != Dem_GucInit)
    {
      /* @Trace: Dem_SUD_API_20348 */
      DEM_REPORT_ERROR(DEM_GETNEXTFILTEREDDTCANDFDC_SID, DEM_E_UNINIT);
      LddRetVal = DEM_NO_SUCH_ELEMENT;
    }
    else if ((NULL_PTR == DTC) || (NULL_PTR == DTCFaultDetectionCounter))
    {
      /* @Trace: Dem_SUD_API_20349 */
      DEM_REPORT_ERROR(DEM_GETNEXTFILTEREDDTCANDFDC_SID, DEM_E_PARAM_POINTER);
      LddRetVal = DEM_NO_SUCH_ELEMENT;
    }
    /* @Trace: Dem_SUD_API_20350 */
    #if (DEM_NUMBER_OF_DEM_CLIENT > DEM_ZERO)
    else if (E_OK != Dem_DTCFilterState[ClientId].dfs_resultGetDtcFilter)
    {
      /* @Trace: SWS_Dem_01267
       * If any of the APIs requesting a Dem_SetDTCFilter (see [SWS_Dem_00057])
       * is called prior of calling Dem_SetDTCFilter a Det error
       * DEM_E_WRONG_CONDITION shall be reported for this API call.
       * */
      /* @Trace: SWS_Dem_01266
       * In case of calling any subsequent function of Dem_SetDTCFilter
       * (see [SWS_Dem_00057]) after the initial Dem_SetDTCFilter did not
       * return E_OK, the Dem shall shall return E_NOT_OK on this
       * subsequent function call.
       */
      /* @Trace: Dem_SUD_API_20077 */
      DEM_REPORT_ERROR(DEM_GETNEXTFILTEREDDTCANDFDC_SID, DEM_E_WRONG_CONDITION);
      LddRetVal = E_NOT_OK;
    }
    #endif
    /* Check whether filtering of FDC was TRUE */
    else if (Dem_DTCFilterState[ClientId].dfs_FilterForFDC == DEM_FALSE)
    {
      /* @Trace: Dem_SUD_API_20338 */
      DEM_REPORT_ERROR(DEM_GETNEXTFILTEREDDTCANDFDC_SID, DEM_E_WRONG_CONDITION);
      LddRetVal = DEM_NO_SUCH_ELEMENT;
    }
    else if ( (DEM_JOB_TRIGGER == Dem_DTCFilterState[ClientId].dfs_JobAction) ||
    (DEM_JOB_RUNNING == Dem_DTCFilterState[ClientId].dfs_JobAction))
    {
      /* @Trace: Dem_SUD_API_20078 */
      DEM_REPORT_ERROR(DEM_GETNEXTFILTEREDDTCANDFDC_SID, DEM_E_WRONG_CONDITION);
      /* Return appropriate value */
      LddRetVal = DEM_PENDING;
    }
    else if (DEM_JOB_DONE != Dem_DTCFilterState[ClientId].dfs_JobAction)
    {
      /* @Trace: Dem_SUD_API_20079 */
      Dem_DTCFilterState[ClientId].dfs_NextEvent = DEM_NO_EVENT;
      LddRetVal = DEM_NO_SUCH_ELEMENT;
    }
    else if (DEM_NO_EVENT == Dem_DTCFilterState[ClientId].dfs_NextEvent)
    {
      /* @Trace: Dem_SUD_API_20080 */
      LddRetVal = DEM_NO_SUCH_ELEMENT;
    }
    /* @Trace: SWS_Dem_01101
     * A suppressed DTC shall not be visible for the following Dcm
     * query-functions; therefore the following functions shall treat the DTC
     * as if filter is not matching.
     * */
    else if (DEM_TRUE == Dem_EvIsProcStateTriggered(
        Dem_DTCFilterState[ClientId].dfs_NextEvent, DEM_EVPROCSTATE_DTC_SUPP))
    {
      /* @Trace: Dem_SUD_API_20150 */
      LddRetVal = DEM_NO_SUCH_ELEMENT;
    }
    else
    {
      /* nextEvent is EventId.*/
      /* @Trace: Dem_SUD_API_20339 */
      /* polyspace-begin MISRA2012:14.2 [Justified:Low] Justify with annotations */
      for (; Dem_DTCFilterState[ClientId].dfs_NextEvent <= DEM_NUMBER_OF_EVENTS;
             Dem_DTCFilterState[ClientId].dfs_NextEvent++)
      /* polyspace-end MISRA2012:14.2 [Justified:Low] Justify with annotations */
      {
        /* @Trace: Dem_SUD_API_20340 */
        if ((boolean)DEM_TRUE == Dem_EvIsProcStateTriggered(
            Dem_DTCFilterState[ClientId].dfs_NextEvent,
            DEM_EVPROCSTATE_DTC_FILTER))
        {
          Dem_EventParameterPCType LddEvent;
          Dem_EvClearProcState(Dem_DTCFilterState[ClientId].dfs_NextEvent,
              DEM_EVPROCSTATE_DTC_FILTER);

          LddEvent = &Dem_Event[ Dem_DTCFilterState[ClientId].
                                 dfs_NextEvent - DEM_ONE];
          /* @Trace: Dem_SUD_API_20341 */
          if (E_OK == Dem_GetEventDTC(LddEvent, DTC, DEM_DTC_FORMAT_UDS))
          {

            /* Load the FDC value of the requested DTC */
            if (E_OK == Dem_GetFaultDetectionCounter(
                Dem_DTCFilterState[ClientId].dfs_NextEvent,
                DTCFaultDetectionCounter))
            {
              /* @Trace: Dem_SUD_API_20344 */
              Dem_DTCFilterState[ClientId].dfs_NextEvent++;
              LddRetVal = E_OK;

              break;
            }
            else
            {
              /* @Trace: Dem_SUD_API_20343 */
              /* @Trace: SWS_Dem_00513
               * If the callback-function Dem_GetFaultDetectionCounter returns
               * other than E_OK or is not configured for a DTC filtered by
               * Dem_GetNextFilteredDTCAndFDC, this FDC value shall be returned
               * as 0.*/
              *DTCFaultDetectionCounter = (sint8)0x00;
            }
          }
        }
      }
      /* No matched DTC */
      /* @Trace: Dem_SUD_API_20345 */
      if (E_OK != LddRetVal)
      {
        /* @Trace: Dem_SUD_API_20346 */
        Dem_DTCFilterState[ClientId].dfs_NextEvent = DEM_NO_EVENT;
      }
    }
    /* @Trace: Dem_SUD_API_20337 */
    Dem_SetDTCFilterServiceUnLock(ClientId,
        DEM_GETNEXTFILTEREDDTCANDFDC_SID_LOCK_IDX);
  }
  return LddRetVal;
}/* End of API */
/*******************************************************************************
** Function Name        : Dem_GetNextFilteredDTCAndSeverity                   **
**                                                                            **
** Service ID           : 0x3d                                                **
**                                                                            **
** Description          : This API provides the capability to get the next    **
**                        filtered DTC and its associated Severity matching   **
**                        the filter criteria. The interface has an           **
**                        asynchronous behavior, because a large number of    **
**                        DTCs has to be processed.                           **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Re-entrant for different ClientIDs, Non re-entrant  **
**                        for same ClientId.                                  **
**                                                                            **
** Input Parameters     : ClientId                                            **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : DTC, DTCStatus,                                     **
**                        DTCSeverity, DTCFunctionalUnit                      **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : The API Dem_PreInit(), Dem_Init()                   **
**                        should have been called in sequence                 **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Dem_GucInit                                         **
**                        Dem_Event                                           **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        (void)Det_ReportError                               **
*******************************************************************************/
/* @Trace: SRS_Diag_04010 SRS_Diag_04071 SRS_Diag_04220
 */
/* polyspace +2 CODE-METRICS:LEVEL [Not a defect:Low] "Not a defect" */
FUNC(Std_ReturnType, DEM_CODE)
  Dem_GetNextFilteredDTCAndSeverity(
  uint8 ClientId,
  P2VAR (uint32, AUTOMATIC, DEM_APPL_DATA) DTC,
  P2VAR (uint8, AUTOMATIC, DEM_APPL_DATA) DTCStatus,
  P2VAR (Dem_DTCSeverityType, AUTOMATIC, DEM_APPL_DATA) DTCSeverity,
  P2VAR (uint8, AUTOMATIC, DEM_APPL_DATA) DTCFunctionalUnit)
{
  /* @Trace: SWS_Dem_01291
   * If the API Dem_GetSeverityOfDTC or Dem_GetNextFilteredDTCAndSeverity is
   * called and for the selected DTC a severity value in DemDTCSeverity is
   * configured, the Dem shall set the value configured in DemDTCSeverity as
   * DTCSeverity.
   */

  /* @Trace: SWS_Dem_01292
   * If the API Dem_GetSeverityOfDTC or Dem_GetNextFilteredDTCAndSeverity is
   * called and for the selected DTC no severity value in DemDTCSeverity is
   * configured, the Dem shall set DEM_SEVERITY_NO_SEVERITY as DTCSeverity.
   * */

  /* @Trace: SWS_Dem_00287
   * With each call to the function Dem_GetNextFilteredDTCAndSeverity the Dem
   * module shall return the next DTC and its associated fault severity matching
   * the filter criteria defined by the function call Dem_SetDTCFilter.
   * */

  Std_ReturnType LddRetVal = DEM_NO_SUCH_ELEMENT;
  Dem_EventParameterPCType LddEvent;
  P2CONST(Dem_CombinedDtcType, AUTOMATIC, DEM_VAR) LddCbDTC;

  boolean LblGetNextFilteredDTCAndSeveritySIDLockIdx =
      Dem_SetDTCFilterServiceIsLock(ClientId,
          DEM_GETNEXTFILTEREDDTCANDSEVERITY_SID_LOCK_IDX);
  /* @Trace: Dem_SUD_API_20359 */
  #if (DEM_NUMBER_OF_DEM_CLIENT > DEM_ZERO)
  if (ClientId >= DEM_NUMBER_OF_DEM_CLIENT)
  {
    /* @Trace: Dem_SUD_API_20376 */
    DEM_REPORT_ERROR(DEM_GETNEXTFILTEREDDTCANDSEVERITY_SID, DEM_E_PARAM_DATA);
    LddRetVal = E_NOT_OK;
  }
  else
  #endif
  /* @Trace: Dem_SUD_API_20367 */
  if (DEM_TRUE == LblGetNextFilteredDTCAndSeveritySIDLockIdx)
  {
    /* @Trace: Dem_SUD_API_20383 */
    LddRetVal = E_NOT_OK;
  }
  else
  {
    Dem_SetDTCFilterServiceLock(ClientId,
          DEM_GETNEXTFILTEREDDTCANDSEVERITY_SID_LOCK_IDX);
    /* Check module Initialization status */
    if (DEM_INIT != Dem_GucInit)
    {
      /* @Trace: Dem_SUD_API_20384 */
      DEM_REPORT_ERROR(DEM_GETNEXTFILTEREDDTCANDSEVERITY_SID, DEM_E_UNINIT);
      LddRetVal = DEM_NO_SUCH_ELEMENT;
    }
    else if ((NULL_PTR == DTC) || (NULL_PTR == DTCStatus) ||
             (NULL_PTR == DTCSeverity) || (NULL_PTR == DTCFunctionalUnit))
    {
      /* @Trace: Dem_SUD_API_20385 */
      DEM_REPORT_ERROR(DEM_GETNEXTFILTEREDDTCANDSEVERITY_SID,
           DEM_E_PARAM_POINTER);
      LddRetVal = DEM_NO_SUCH_ELEMENT;
    }
    /* @Trace: Dem_SUD_API_20360 */
    #if (DEM_NUMBER_OF_DEM_CLIENT > DEM_ZERO)
    /* @Trace: Dem_SUD_API_20362 */
    else if (E_OK != Dem_DTCFilterState[ClientId].dfs_resultGetDtcFilter)
    {
      /* @Trace: SWS_Dem_01267
       * If any of the APIs requesting a Dem_SetDTCFilter (see [SWS_Dem_00057])
       * is called prior of calling Dem_SetDTCFilter a Det error
       * DEM_E_WRONG_CONDITION shall be reported for this API call.
       * */
      /* @Trace: SWS_Dem_01266
         * In case of calling any subsequent function of Dem_SetDTCFilter
         * (see [SWS_Dem_00057]) after the initial Dem_SetDTCFilter did not
         * return E_OK, the Dem shall shall return E_NOT_OK on this
         * subsequent functioncall.
         */
      /* @Trace: Dem_SUD_API_20361 */
      DEM_REPORT_ERROR(DEM_GETNEXTFILTEREDDTCANDSEVERITY_SID,
          DEM_E_WRONG_CONDITION);
      LddRetVal = E_NOT_OK;
    }
    #endif
    else if (Dem_DTCFilterState[ClientId].dfs_FilterWithSeverity != DEM_TRUE)
    {
      /* @Trace: Dem_SUD_API_20363 */
      DEM_REPORT_ERROR(DEM_GETNEXTFILTEREDDTCANDSEVERITY_SID,
          DEM_E_WRONG_CONDITION);
      LddRetVal = DEM_NO_SUCH_ELEMENT;
    }
    else if ((DEM_JOB_TRIGGER == Dem_DTCFilterState[ClientId].dfs_JobAction) ||
    (DEM_JOB_RUNNING == Dem_DTCFilterState[ClientId].dfs_JobAction))
    {
      /* @Trace: Dem_SUD_API_20364 */
      DEM_REPORT_ERROR(DEM_GETNEXTFILTEREDDTCANDSEVERITY_SID,
          DEM_E_WRONG_CONDITION);
      /* Return appropriate value */
      LddRetVal = DEM_PENDING;
    }
    else if (DEM_JOB_DONE != Dem_DTCFilterState[ClientId].dfs_JobAction)
    {
      /* @Trace: Dem_SUD_API_20365 */
      Dem_DTCFilterState[ClientId].dfs_NextEvent = DEM_NO_EVENT;
      LddRetVal = DEM_NO_SUCH_ELEMENT;
    }
    else if (DEM_NO_EVENT == Dem_DTCFilterState[ClientId].dfs_NextEvent)
    {
      /* @Trace: Dem_SUD_API_20366 */
      LddRetVal = DEM_NO_SUCH_ELEMENT;
    }
    /* @Trace: SWS_Dem_01101
     * A suppressed DTC shall not be visible for the following Dcm
     * query-functions;
     * therefore the following functions shall treat the DTC as if filter is not
     * matching.
     * */
    else if (DEM_TRUE == Dem_EvIsProcStateTriggered(
        Dem_DTCFilterState[ClientId].dfs_NextEvent, DEM_EVPROCSTATE_DTC_SUPP))
    {
      /* @Trace: Dem_SUD_API_20368 */
      LddRetVal = DEM_NO_SUCH_ELEMENT;
    }
    else
    {
      /* nextEvent is EventId.*/
      /* @Trace: Dem_SUD_API_20369 */
      /* polyspace-begin MISRA2012:14.2 [Justified:Low] Justify with annotations */
      for (; Dem_DTCFilterState[ClientId].dfs_NextEvent <= DEM_NUMBER_OF_EVENTS;
             Dem_DTCFilterState[ClientId].dfs_NextEvent++)
      /* polyspace-end MISRA2012:14.2 [Justified:Low] Justify with annotations */
      {
        /* @Trace: Dem_SUD_API_20370 */
        if ((boolean)DEM_TRUE == Dem_EvIsProcStateTriggered(
             Dem_DTCFilterState[ClientId].dfs_NextEvent,
                DEM_EVPROCSTATE_DTC_FILTER))
        {
          Dem_EvClearProcState(Dem_DTCFilterState[ClientId].
              dfs_NextEvent, DEM_EVPROCSTATE_DTC_FILTER);

          LddEvent =
              &Dem_Event[Dem_DTCFilterState[ClientId].dfs_NextEvent - DEM_ONE];
          /* @Trace: Dem_SUD_API_20371 */
          if (LddEvent->e_PointToDTC < DEM_MAX_NUMBER_OF_DTC)
          {
            LddCbDTC = &Dem_GaaCombinedDtc[LddEvent->e_PointToDTC];

            *DTC = Dem_GetDtcByCombineDTC(LddCbDTC);
            

            *DTCSeverity = LddCbDTC->ddDtcSeverity;
            #if (DEM_J1979_2_OBD_ON_UDS == STD_ON)
            /* Trace: DEM_19792_ */
            *DTCSeverity = *DTCSeverity | LddCbDTC->eDemWWHOBDDTCClass;
            #endif /* J19792 */
            *DTCFunctionalUnit = LddCbDTC->ucDtcFunctionalUnit;

            /* If specific StatusAvailablilityMask of a DTC is existed */
            /* polyspace-begin MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] Same as Dead Code. */
            /* polyspace-begin DEFECT:DEAD_CODE [Justified:Low] Dead Code by Configuration. */
            /* polyspace +1 DEFECT:DATA_RACE [Not a defect:Low] "Not a defect" */ 
            if (DEM_ZERO != LddCbDTC->UdsStatusAvailabilityMask)
            {
              /* @Trace: Dem_SUD_API_20375 */
              /* UdsStatusAvailabilityMask and Dem_DTCFilterState[ClientId].
               *  dfs_DTCStatusMask are subset of Dem_Status_Availability_Mask*/
              *DTCStatus = Dem_GetDTCStatus(Dem_DTCFilterState[
                        ClientId].dfs_NextEvent) &
                        LddCbDTC->UdsStatusAvailabilityMask;
            }
            else
            {
              /* @Trace: Dem_SUD_API_20377 */
              *DTCStatus = Dem_GetDTCStatus(
                  Dem_DTCFilterState[ClientId].dfs_NextEvent);
            }
            /* polyspace-end MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] Same as Dead Code. */
            /* polyspace-end DEFECT:DEAD_CODE [Justified:Low] */
            /* @Trace: Dem_SUD_API_20378 */
            if (DEM_ZERO != Dem_DTCFilterState[ClientId].dfs_DTCStatusMask)
            {
              /* @Trace: Dem_SUD_API_20379 */
              if ((Dem_DTCFilterState[ClientId].dfs_DTCStatusMask &
                  (*DTCStatus)) != DEM_ZERO)
              {
                /* @Trace: Dem_SUD_API_20380 */
                /* Increment the index to fetch the next DTC */
                Dem_DTCFilterState[ClientId].dfs_NextEvent++;

                LddRetVal = E_OK;
                break;
              }
            }
          }
        }
      }
      /* @Trace: Dem_SUD_API_20381 */
      if (E_OK != LddRetVal)
      {
        /* @Trace: Dem_SUD_API_20382 */
        Dem_DTCFilterState[ClientId].dfs_NextEvent = DEM_NO_EVENT;
      }
    }
    Dem_SetDTCFilterServiceUnLock(ClientId,
        DEM_GETNEXTFILTEREDDTCANDSEVERITY_SID_LOCK_IDX);
  }
  return LddRetVal;
}/* End of API */
/*******************************************************************************
** Function Name        : Dem_GetTranslationType                              **
**                                                                            **
** Service ID           : 0x3c                                                **
**                                                                            **
** Description          : Gets the supported DTC formats of the ECU.          **
**                        The supported formats are configured via            **
**                        DemTypeOfDTCSupported.                              **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant for different ClientIDs, Non re-entrant  **
**                        for same ClientId.                                  **
**                                                                            **
** Input Parameters     : ClientId - Unique client id, assigned to the        **
**                        instance of the calling module.                     **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Dem_DTCTranslationFormatType                        **
**                                                                            **
** Preconditions        : The API Dem_PreInit(), Dem_Init()                   **
**                        should have been called in sequence                 **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Dem_GucInit                                         **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        (void)Det_ReportError                               **
*******************************************************************************/
/* @Trace: SRS_Diag_04201
 */
FUNC(Dem_DTCTranslationFormatType, DEM_CODE) 
Dem_GetTranslationType(uint8 ClientId)
{
  Dem_DTCTranslationFormatType LddDtcFormatType = DEM_DTC_TRANSLATION_INVALID;
  /* @Trace: SWS_Dem_00231
   * The API Dem_GetTranslationType shall return the translation
   * format of the DemEventMemorySet configured in DemTypeOfDTCSupported.
   * */
  /* Module Initialization check */
  if (Dem_GucInit != DEM_INIT)
  {
    /* @Trace: Dem_SUD_API_20050 */
    DEM_REPORT_ERROR(DEM_GETTRANSLATIONTYPE_SID, DEM_E_UNINIT);
  }
  /* @Trace: Dem_SUD_API_20200 */
  #if (DEM_NUMBER_OF_DEM_CLIENT > DEM_ZERO)
  /* @Trace: Dem_SUD_API_20202 */
  else if (ClientId >= DEM_NUMBER_OF_DEM_CLIENT)
  {
    /* @Trace: Dem_SUD_API_20051 */
    DEM_REPORT_ERROR( DEM_GETTRANSLATIONTYPE_SID, DEM_E_WRONG_CONFIGURATION);
  }
  #endif
  else
  {
    boolean LddRetVal = Dem_EvMem_GetDemTypeOfDTCSupported(
        ClientId, &LddDtcFormatType);
    /* ClientId not found */
    /* @Trace: Dem_SUD_API_20201 */
    /* polyspace-begin MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] Same as Dead Code. */
    /* polyspace-begin DEFECT:DEAD_CODE [Justified:Low] */
    /* polyspace +1 DEFECT:DATA_RACE [Not a defect:Low] "Not a defect" */ 
    if (DEM_FALSE == LddRetVal)
    {
      /* @Trace: Dem_SUD_API_20052 */
      DEM_REPORT_ERROR(DEM_GETTRANSLATIONTYPE_SID, DEM_E_WRONG_CONFIGURATION);
    }
    /* polyspace-end MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] Same as Dead Code. */
    /* polyspace-end DEFECT:DEAD_CODE [Justified:Low] */
  }

  /* Return Type of DTC supported */
  return LddDtcFormatType;
}
/*******************************************************************************
** Function Name        : Dem_GetSeverityOfDTC                                **
**                                                                            **
** Service ID           : 0x0e                                                **
**                                                                            **
** Description          : Gets Severity of the requested DTC                  **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Reentrant for different ClientIds, non reentrant    **
**                        for the same ClientId.                              **
**                                                                            **
** Input Parameters     : ClientId    - Unique client id, assigned to the     **
**                                      instance of the calling module.       **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : DTCSeverity - This parameter contains the           **
**                                      DTCSeverity according to ISO 14229-1  **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : The API Dem_PreInit(), Dem_Init()                   **
**                        should have been called in sequence                 **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        Dem_GucInit                                         **
**                        Dem_Event                                           **
**                                                                            **
**                        Function(s) invoked :                               **
**                        (void)Det_ReportError                               **
*******************************************************************************/
/* @Trace: SRS_Diag_04010 SRS_Diag_04071 SRS_Diag_04220
 */
FUNC(Std_ReturnType, DEM_CODE)
Dem_GetSeverityOfDTC(
    uint8 ClientId,
  P2VAR (Dem_DTCSeverityType, AUTOMATIC, DEM_APPL_DATA) DTCSeverity)
{
  /* @Trace: SWS_Dem_01291
   * If the API Dem_GetSeverityOfDTC or Dem_GetNextFilteredDTCAndSeverity is
   * called and for the selected DTC a severity value in DemDTCSeverity is
   * configured, the Dem shall set the value configured in DemDTCSeverity as
   * DTCSeverity.
   */

  /* @Trace: SWS_Dem_01292
   * If the API Dem_GetSeverityOfDTC or Dem_GetNextFilteredDTCAndSeverity
   * is called and for the selected DTC no severity value in DemDTCSeverity is
   * configured, the Dem shall set DEM_SEVERITY_NO_SEVERITY as DTCSeverity.
   * */
  Std_ReturnType LddRetVal = E_OK;
  uint16 LusByteShift =
      ((uint16)DEM_ONE << DEM_SELECTDTC_SID_LOCK_IDX) |
      ((uint16)DEM_ONE << DEM_CLEARDTC_SID_LOCK_IDX) |
      ((uint16)DEM_ONE << DEM_DISABLEDTCRECORDUPDATE_SID_LOCK_IDX) |
      ((uint16)DEM_ONE << DEM_ENABLEDTCRECORDUPDATE_SID_LOCK_IDX) |
      ((uint16)DEM_ONE << DEM_GETDTCSELECTIONRESULT_SID_LOCK_IDX) |
      ((uint16)DEM_ONE << DEM_GETFUNCTIONALUNITOFDTC_SID_LOCK_IDX) |
      ((uint16)DEM_ONE << DEM_GETSEVERITYOFDTC_SID_LOCK_IDX) |
      ((uint16)DEM_ONE << DEM_GETSTATUSOFDTC_SID_LOCK_IDX) |
      ((uint16)DEM_ONE << DEM_SELECTFREEZEFRAMEDATA_SID_LOCK_IDX) |
      ((uint16)DEM_ONE << DEM_SELECTEXTENDEDDATARECORD_SID_LOCK_IDX) |
      ((uint16)DEM_ONE << DEM_SETDTCSUPPRESSION_SID_LOCK_IDX) |
      ((uint16)DEM_ONE << DEM_GETDTCSUPPRESSION_SID_LOCK_IDX);
  Std_ReturnType LucResult = Dem_CheckStatusOfSelectedDTCServices(
      ClientId,
      DEM_GETSEVERITYOFDTC_SID,
      LusByteShift);
  /* @Trace: Dem_SUD_API_20235 */
  #if (DEM_NUMBER_OF_DEM_CLIENT > DEM_ZERO)
  /* @Trace: Dem_SUD_API_20243 */
  if (ClientId >= DEM_NUMBER_OF_DEM_CLIENT)
  {
    /* @Trace: Dem_SUD_API_20242 */
    DEM_REPORT_ERROR(DEM_GETSEVERITYOFDTC_SID, DEM_E_WRONG_CONDITION);
    LddRetVal = DEM_WRONG_DTC;
  }
  else
  #endif
  /* Check module Initialization status */
  if (E_OK != LucResult)
  {
    /* @Trace: SWS_Dem_01305
     * Behavior if one client starting a new operation while the previous one
     * is still running
     * In case any of the Dem_SelectDTC related APIs according to
     * [SWS_Dem_01253] is called by one client and the same client has already
     * started another Dem_SelectDTC related operation according to
     * [SWS_Dem_01253] and this different operation is not completed,
     * the Dem shall return DEM_BUSY.
     * */
    /* @Trace: Dem_SUD_API_20057 */
    LddRetVal = LucResult;
  }
  else
  {
    /* lock this client id */
    Dem_SelectedDTCServiceLock(ClientId, DEM_GETSEVERITYOFDTC_SID_LOCK_IDX);

    if (Dem_GucInit != DEM_INIT)
    {
      /* @Trace: Dem_SUD_API_20244 */
      DEM_REPORT_ERROR(DEM_GETSEVERITYOFDTC_SID, DEM_E_UNINIT);
      LddRetVal = E_NOT_OK;
    }
    /* @Trace: Dem_SUD_API_20245 */
    #if (DEM_NUMBER_OF_DEM_CLIENT > DEM_ZERO)
    /* @Trace: Dem_SUD_API_20246 */
    /* @Trace: Dem_SUD_MACRO_077 */
    #if (DEM_MAX_NUM_GRP_DTC > DEM_ZERO)
    /* @Trace: Dem_SUD_API_20247 */
    else if ( DEM_DTC_GROUP_IS_VALID( Dem_ClientSelectDtcState[ClientId].
        selectedDTC))
    {
      /* @Trace: Dem_SUD_API_20058 */
      DEM_REPORT_ERROR(DEM_GETSEVERITYOFDTC_SID, DEM_E_PARAM_DATA);
      LddRetVal = DEM_WRONG_DTC;
    }
    #endif
    #endif
    else if (DTCSeverity == NULL_PTR)
    {
      /* @Trace: Dem_SUD_API_20236 */
      DEM_REPORT_ERROR(DEM_GETSEVERITYOFDTC_SID, DEM_E_PARAM_POINTER);
      LddRetVal = E_NOT_OK;
    }

    else if (E_OK != Dem_ClientSelectDtcState[ClientId].resultSelectDTC)
    {
      /* @Trace: Dem_SUD_API_20237 */
      DEM_REPORT_ERROR(DEM_GETSEVERITYOFDTC_SID, DEM_E_WRONG_CONDITION);
      LddRetVal = Dem_ClientSelectDtcState[ClientId].resultSelectDTC;
    }
    else
    {
      /* @Trace: Dem_SUD_API_20238 */
      #if (DEM_NUMBER_OF_DEM_CLIENT > DEM_ZERO)
      Dem_EventIdType LddEventId = Dem_GetEventIdByDTC(
        DEM_GETSEVERITYOFDTC_SID,
        Dem_ClientSelectDtcState[ClientId].selectedDTC,
        Dem_ClientSelectDtcState[ClientId].selectedDTCFormat);
      if ((LddEventId > DEM_NUMBER_OF_EVENTS) || (DEM_NO_EVENT == LddEventId))
      {
        /* @Trace: Dem_SUD_API_20059 */
        DEM_REPORT_ERROR(DEM_GETSEVERITYOFDTC_SID, DEM_E_PARAM_CONFIG);
        LddRetVal = DEM_WRONG_DTC;
      }
      else if (DEM_TRUE == Dem_EvIsProcStateTriggered(LddEventId,
          DEM_EVPROCSTATE_DTC_SUPP))
      {
        /* @Trace: SWS_Dem_01100
         * Behavior of DTC query functions for suppressed DTCs. In
         * case any of the following APIs is called on a single
         * selected DTC which is suppressed, the Dem shall return DEM_WRONG_DTC
         * */
        /* @Trace: Dem_SUD_API_20239 */
        LddRetVal = DEM_WRONG_DTC;
      }
      else
      {
        Dem_CombinedDtcPCType LddCbDTC = Dem_GetDtcByDtcId(
            Dem_ClientSelectDtcState[ClientId].selectedDTC,
            Dem_ClientSelectDtcState[ClientId].selectedDTCFormat);
        if (NULL_PTR == LddCbDTC)
        {
          /* @Trace: Dem_SUD_API_20240 */
          DEM_REPORT_ERROR(DEM_GETSEVERITYOFDTC_SID, DEM_E_PARAM_CONFIG);
          LddRetVal = DEM_WRONG_DTC;
        }
        else
        {
          /* @Trace: Dem_SUD_API_20241 */
          *DTCSeverity = LddCbDTC->ddDtcSeverity;
          /* @LddRetVal = DEM_GET_SEVERITYOFDTC_OK; */
        }
      }
      #endif
    }
    /* unlock this client id */
    Dem_SelectedDTCServiceUnLock(ClientId, DEM_GETSEVERITYOFDTC_SID_LOCK_IDX);
  }

  return LddRetVal;
}

/*******************************************************************************
** Function Name        : Dem_ClearDTC                                        **
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
** Input Parameters     : Uint32 DTC                                          **
**                        DTCOrigin, DTCFormat                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Dem_ReturnClearDTCType                              **
**                                                                            **
** Preconditions        : The API Dem_PreInit(), Dem_Init()                   **
**                        should have been called in sequence                 **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        Dem_GucInit                                         **
**                        Dem_Event                                           **
**                        Dem_GulDemClearTimeCount                            **
**                        Dem_GblClearTimeStartObd                            **
**                        Dem_GusWarmUpCycleCount                             **
**                        Dem_GulTimeSinceMilOn                               **
**                                                                            **
**                        Function(s) invoked :                               **
**                        (void)Det_ReportError                               **
**                        Dem_BinarySearch                                    **
*******************************************************************************/
/* @Trace: SRS_BSW_00369 SRS_Diag_04065 SRS_Diag_04117 SRS_Diag_04126
           SRS_Diag_04194 SRS_Diag_04220
 */
FUNC(Std_ReturnType, DEM_CODE) Dem_ClearDTC(uint8 ClientId)
{
  Std_ReturnType LddRetVal = DEM_CLEAR_FAILED;
  uint16 LusByteShift =
      ((uint16)DEM_ONE << DEM_SELECTDTC_SID_LOCK_IDX) |
      ((uint16)DEM_ONE << DEM_CLEARDTC_SID_LOCK_IDX) |
      ((uint16)DEM_ONE << DEM_DISABLEDTCRECORDUPDATE_SID_LOCK_IDX) |
      ((uint16)DEM_ONE << DEM_ENABLEDTCRECORDUPDATE_SID_LOCK_IDX) |
      ((uint16)DEM_ONE << DEM_GETDTCSELECTIONRESULT_SID_LOCK_IDX) |
      ((uint16)DEM_ONE << DEM_GETFUNCTIONALUNITOFDTC_SID_LOCK_IDX) |
      ((uint16)DEM_ONE << DEM_GETSEVERITYOFDTC_SID_LOCK_IDX) |
      ((uint16)DEM_ONE << DEM_GETSTATUSOFDTC_SID_LOCK_IDX) |
      ((uint16)DEM_ONE << DEM_SELECTFREEZEFRAMEDATA_SID_LOCK_IDX) |
      ((uint16)DEM_ONE << DEM_SELECTEXTENDEDDATARECORD_SID_LOCK_IDX) |
      ((uint16)DEM_ONE << DEM_SETDTCSUPPRESSION_SID_LOCK_IDX) |
      ((uint16)DEM_ONE << DEM_GETDTCSUPPRESSION_SID_LOCK_IDX);
  Std_ReturnType LucResult = Dem_CheckStatusOfSelectedDTCServices(
      ClientId,
      DEM_CLEARDTC_SID,
      LusByteShift);
  /* @Trace: Dem_SUD_API_11951 */
  #if (DEM_NUMBER_OF_DEM_CLIENT > DEM_ZERO)
  if (ClientId >= DEM_NUMBER_OF_DEM_CLIENT)
  {
    /* @Trace: Dem_SUD_API_11961 */
    DEM_REPORT_ERROR(DEM_CLEARDTC_SID, DEM_E_WRONG_CONFIGURATION);
    /* @LddRetVal = DEM_CLEAR_FAILED; */
  }
  else
  #endif
  if (E_OK != LucResult)
  {
    /* @Trace: Dem_SUD_API_11962 */
    LddRetVal = LucResult;
  }
  else
  {
    /* lock this client id */
    Dem_SelectedDTCServiceLock(ClientId, DEM_CLEARDTC_SID_LOCK_IDX);

    if (Dem_GucInit != DEM_INIT)
    {
      /* @Trace: Dem_SUD_API_11963 */
      DEM_REPORT_ERROR(DEM_CLEARDTC_SID, DEM_E_UNINIT);
      /* @LddRetVal = DEM_CLEAR_FAILED; */
    }
    /* @Trace: Dem_SUD_API_11964 */
    #if (DEM_NUMBER_OF_DEM_CLIENT > DEM_ZERO)
    else if (E_OK != Dem_ClientSelectDtcState[ClientId].resultSelectDTC)
    {
      /* @Trace: Dem_SUD_API_11966 */
      /* @Trace: SWS_Dem_01255
       * If any of the APIs requiring a Dem_SelectDTC (see [SWS_Dem_01253]) is
       * called without a prior call to Dem_SelectDTC, the Dem shall report the
       * Det error DEM_E_WRONG_CONDITION.
       * */
      DEM_REPORT_ERROR(DEM_CLEARDTC_SID, DEM_E_WRONG_CONDITION);
      LddRetVal = Dem_ClientSelectDtcState[ClientId].resultSelectDTC;
    }
    #endif
    else
    {
      /* @Trace: Dem_SUD_API_11965 */
      LddRetVal = E_OK;
      /* @Trace: Dem_SUD_API_11967 */
      #if (DEM_CLEAR_DTC_LIMITATION == DEM_ONLY_CLEAR_ALL_DTCS)
      if (DEM_DTC_GROUP_ALL_DTCS !=
    		  Dem_ClientSelectDtcState[ClientId].selectedDTC)
      {
        /* @Trace: Dem_SUD_API_11968 */
        /* @Trace: SWS_Dem_00670
         * If the configuration parameter DemClearDTCLimitation is set to
         * DEM_ONLY_CLEAR_ALL_DTCS, the APIs Dem_ClearDTC are called with a
         * selected DTC group different to DEM_DTC_GROUP_ALL_DTCS the Dem shall
         * return DEM_WRONG_DTC.*/

        LddRetVal = DEM_WRONG_DTC;
      }
      else
      #endif
      /* @Trace: SWS_Dem_01100
       * Behavior of DTC query functions for suppressed DTCs. In
       * case any of the following APIs is called on a single
       * selected DTC which is suppressed, the Dem shall return DEM_WRONG_DTC
       * */
      /* Single Dtc */
      if (E_OK != Dem_DTCGroupIsValid(
          Dem_ClientSelectDtcState[ClientId].selectedDTC,
          Dem_ClientSelectDtcState[ClientId].selectedDTCFormat))
      {
        Dem_EventIdType LddEventId = Dem_GetEventIdByDTC(
          DEM_CLEARDTC_SID,
          Dem_ClientSelectDtcState[ClientId].selectedDTC,
          Dem_ClientSelectDtcState[ClientId].selectedDTCFormat);

        if ((LddEventId > DEM_NUMBER_OF_EVENTS) || (DEM_NO_EVENT == LddEventId))
        {
          /* @Trace: Dem_SUD_API_10694 */
          DEM_REPORT_ERROR(DEM_CLEARDTC_SID, DEM_E_PARAM_CONFIG);
          LddRetVal = DEM_WRONG_DTC;
        }
        else if (DEM_TRUE == Dem_EvIsProcStateTriggered(
                            LddEventId, DEM_EVPROCSTATE_DTC_SUPP))
        {
          /* @Trace: Dem_SUD_API_11953 */
          LddRetVal = DEM_WRONG_DTC;
        }
        /* @Trace: Dem_SUD_API_11954 */
        #if (DEM_AVAILABILITY_SUPPORT == DEM_EVENT_AVAILABILITY)
        else if ( DEM_TRUE != Dem_EvIsProcStateTriggered(LddEventId,
            DEM_EVPROCSTATE_EVENT_AVAILABLE))
        {
          /* @Trace: Dem_SUD_API_10695 */
          /* @Trace: SWS_Dem_01108
           * If an event is set to unavailable, the corresponding event shall
           * be treated as if it is not configured in the system (e.g.
           * Dem_SetEventStatus and Dem_GetEventUdsStatus shall
           * return E_NOT_OK). */

          LddRetVal = E_NOT_OK;
        }
        #endif
        else
        {
          /* @Trace: Dem_SUD_API_11955 */
          /* Nothing to do */
        }
      }
      else
      {
        /* @Trace: Dem_SUD_API_11952 */
        /* Nothing to do */
      }
      
      /* @Trace: Dem_SUD_API_11956 */
      if (E_OK == LddRetVal)
      {
        SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();
        if ((DEM_CLEARDTC_STATE_USER_CDD ==
        		Dem_ClearDtcState[ClientId].cds_User) ||
            (DEM_CLEARDTC_STATE_USER_J1939DCM ==
            	Dem_ClearDtcState[ClientId].cds_User))
        {
          /* @Trace: Dem_SUD_API_10696 */
          SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();
          LddRetVal = DEM_PENDING; /* It means 'busy' state */
        }
        else /* DEM_CLEARDTC_STATE_USER_DCM or IDLE */
        {
          Dem_ClearDtcState[ClientId].cds_User = DEM_CLEARDTC_STATE_USER_DCM;
          /* @Trace: Dem_SUD_API_11957 */
          /* @Trace: Dem_SUD_MACRO_057 */
          #if (DEM_J1939_CLEAR_DTC_SUPPORT == STD_ON)
          /* Not used */
          /* @Trace: Dem_SUD_API_11958 */
          Dem_ClearDtcState[ClientId].cds_DTCTypeFilter = DEM_ZERO;
          #endif
          SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();

          /* @Trace: SWS_Dem_00661
           * In case of multiple clients are requesting Dem_ClearDTC in
           * parallel, the Dem shall internally process the different requests.
           * */
          LddRetVal = Dem_InternalClearDTC(ClientId,
              Dem_ClientSelectDtcState[ClientId].selectedDTC,
              Dem_ClientSelectDtcState[ClientId].selectedDTCFormat,
              Dem_ClientSelectDtcState[ClientId].selectedDTCOrigin);
          /* @Trace: Dem_SUD_API_11960 */
          if (DEM_PENDING != LddRetVal)
          {
            /* @Trace: Dem_SUD_API_11959 */
            SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();
            Dem_ClearDtcState[ClientId].cds_User = DEM_CLEARDTC_STATE_USER_IDLE;
            SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();
          }
        }
      }
    }
    Dem_SelectedDTCServiceUnLock(ClientId, DEM_CLEARDTC_SID_LOCK_IDX);
  }

  return LddRetVal;
}
/*******************************************************************************
** Function Name        : Dem_SelectDTC                                       **
**                                                                            **
** Service ID           : 0xb7                                                **
**                                                                            **
** Description          : Selects a DTC or DTC group as target for            **
**                        further operations.                                 **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant for different ClientIds, non reentrant    **
**                        for the same ClientId.                              **
**                                                                            **
** Input Parameters     : ClientId  - Unique client id, assigned to the       **
**                                    instance of the calling module.         **
**                        DTC       - Defines the DTC in respective format    **
**                                    that is selected. If the DTC fits       **
**                                    to a DTC group number, the DTC          **
**                                    group is selected.                      **
**                        DTCOrigin - Defines the input-format                **
**                                    of the provided DTC value.              **
**                        DTCFormat - The event memory of the requested       **
**                                    DTC or group of DTC.                    **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : E_OK      - DTC successfully selected.              **
**                        DEM_BUSY  - Another Dem_SelectDTC or                **
**                                    Dem_SelectDTC dependent operation of    **
**                                    this client is currently in progress.   **
**                                                                            **
** Preconditions        : The API Dem_PreInit(), Dem_Init()                   **
**                        should have been called in sequence                 **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        Dem_GucInit                                         **
**                        Dem_Event                                           **
**                        Dem_Client                                          **
**                        Dem_ClientSelectDtcState                            **
**                                                                            **
**                        Function(s) invoked :                               **
**                        (void)Det_ReportError                               **
**                                                                            **
*******************************************************************************/
/* @Trace: SRS_BSW_00369 SRS_Diag_04010 SRS_Diag_04058 SRS_Diag_04000
           SRS_Diag_04154
 */
/* polyspace +1 MISRA-C3:8.4 MISRA-C3:8.5 [Justified:Low] Justify with annotations */
FUNC(Std_ReturnType, DEM_CODE) Dem_SelectDTC(uint8 ClientId, uint32 DTC,
    Dem_DTCFormatType DTCFormat, Dem_DTCOriginType DTCOrigin)
{
  Std_ReturnType LddRetVal = E_OK;
  uint16 LusByteShift =
      ((uint16)DEM_ONE << DEM_SELECTDTC_SID_LOCK_IDX) |
      ((uint16)DEM_ONE << DEM_CLEARDTC_SID_LOCK_IDX) |
      ((uint16)DEM_ONE << DEM_DISABLEDTCRECORDUPDATE_SID_LOCK_IDX) |
      ((uint16)DEM_ONE << DEM_ENABLEDTCRECORDUPDATE_SID_LOCK_IDX) |
      ((uint16)DEM_ONE << DEM_GETDTCSELECTIONRESULT_SID_LOCK_IDX) |
      ((uint16)DEM_ONE << DEM_GETFUNCTIONALUNITOFDTC_SID_LOCK_IDX) |
      ((uint16)DEM_ONE << DEM_GETSEVERITYOFDTC_SID_LOCK_IDX) |
      ((uint16)DEM_ONE << DEM_GETSTATUSOFDTC_SID_LOCK_IDX) |
      ((uint16)DEM_ONE << DEM_SELECTFREEZEFRAMEDATA_SID_LOCK_IDX) |
      ((uint16)DEM_ONE << DEM_SELECTEXTENDEDDATARECORD_SID_LOCK_IDX) |
      ((uint16)DEM_ONE << DEM_SETDTCSUPPRESSION_SID_LOCK_IDX) |
      ((uint16)DEM_ONE << DEM_GETDTCSUPPRESSION_SID_LOCK_IDX);
  Std_ReturnType LucResult = Dem_CheckStatusOfSelectedDTCServices(
      ClientId,
      DEM_SELECTDTC_SID,
      LusByteShift);

  Dem_CombinedDtcPCType LddCbDTC = Dem_GetDtcByDtcId(DTC, DTCFormat);
  /* @Trace: SWS_Dem_00171
   * If the Dcm has requested an unavailable event memory / DTC origin, the Dem
   * module functions with the respective return value shall return
   * DEM_<...>_WRONG_DTCORIGIN.
   */
  /* @Trace: SWS_Dem_00172
   * If the Dcm has requested a DTC that is not available at all or that is
   * available but has a different event memory / DTC origin than the requested
   * one, the Dem module functions with the respective return
   * value shall return DEM_<...>_WRONG_DTC.
   */
  #if (DEM_NUMBER_OF_DEM_CLIENT > DEM_ZERO)
  if (ClientId >= DEM_NUMBER_OF_DEM_CLIENT)
  {
    /* @Trace: Dem_SUD_API_12299 */
    DEM_REPORT_ERROR(DEM_SELECTDTC_SID, DEM_E_PARAM_DATA);
    /*@Dem_ClientSelectDtcState[ClientId].resultSelectDTC = E_NOT_OK;*/
  }
  else
  #endif
  if (E_OK != LucResult)
  {
    /* @Trace: Dem_SUD_API_12302 */
    LddRetVal = LucResult;
  }
  else
  {
    /* lock this client id */
    Dem_SelectedDTCServiceLock(ClientId, DEM_SELECTDTC_SID_LOCK_IDX);
    /* @Trace: Dem_SUD_API_12304 */
    #if (DEM_NUMBER_OF_DEM_CLIENT > DEM_ZERO)
    if (DEM_INIT != Dem_GucInit)
    {
      /* @Trace: Dem_SUD_API_12303 */
      DEM_REPORT_ERROR(DEM_SELECTDTC_SID, DEM_E_UNINIT);
      Dem_ClientSelectDtcState[ClientId].resultSelectDTC = E_NOT_OK;
    }
    /* @Trace: SWS_Dem_01262
     * API Behaviour on undefined DTCOrigin
     * If any of the APIs requiring a Dem_SelectDTC (see [SWS_Dem_01253]) is
     * called on a not existing selected DTCOrigin, the Dem shall return
     * DEM_WRONG_DTCORIGIN on this API.
     * */
    else if (DEM_FALSE == Dem_EvMem_DTCOriginIsValid(DTCOrigin))
    {
      /* @Trace: Dem_SUD_API_12305 */
      DEM_REPORT_ERROR(DEM_SELECTDTC_SID, DEM_E_PARAM_DATA);
      Dem_ClientSelectDtcState[ClientId].resultSelectDTC = DEM_WRONG_DTCORIGIN;
    }
    /* @Trace: SWS_Dem_01261
     * API Behaviour on undefined DTC or format
     * If any of the APIs requiring a Dem_SelectDTC according to [SWS_Dem_01253]
     *  is called while the selection with Dem_SelectDTC is invalid,
     *  then the Dem shall return DEM_WRONG_DTC. A selection is invalid in case
     * the provided DTC does not specify a valid DTC or GroupOfDTCs in the
     * corresponding DTCFormat.
     * The selection also is invalid, if Dem_SelectDTC was not called before.
     * */
    else if (
             #if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
             (DEM_DTC_FORMAT_OBD != DTCFormat) &&
             #if(DEM_J1979_2_OBD_ON_UDS == STD_ON)
             /* Trace: DEM_19792_42_04 */
             (DEM_DTC_FORMAT_OBD_3BYTE != DTCFormat) &&
             #endif /* (DEM_J1979_2_OBD_ON_UDS == STD_ON)*/
             #endif /* (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT) */
             (DEM_DTC_FORMAT_UDS != DTCFormat)
             #if (DEM_J1939_SUPPORT == STD_ON)
             && (DEM_DTC_FORMAT_J1939 != DTCFormat)
             #endif
             )
    {
      /* @Trace: Dem_SUD_API_12306 */
      DEM_REPORT_ERROR( DEM_SELECTDTC_SID, DEM_E_PARAM_DATA);
      Dem_ClientSelectDtcState[ClientId].resultSelectDTC = DEM_WRONG_DTC;
    }
    /* Group Dtc */
    else if ((E_OK != Dem_DTCGroupIsValid(DTC, DTCFormat))
        && (NULL_PTR == LddCbDTC))
    {
      /* @Trace: Dem_SUD_API_12307 */
      DEM_REPORT_ERROR(DEM_SELECTDTC_SID, DEM_E_PARAM_DATA);
      Dem_ClientSelectDtcState[ClientId].resultSelectDTC = DEM_WRONG_DTC;
    }
    else
    {
      /* @Trace: SWS_Dem_01254
       * The API Dem_SelectDTC triggers the Dem internal DTC selection
       * process on the event memory assigned to the ClientId. The result of
       * the selection shall be reflected in the return value of the API calls
       * following the Dem_SelectDTC call, see [SWS_Dem_01253].
       * */

      /* @Trace: SWS_Dem_01253
       * If the API Dem_SelectDTC is called, the Dem shall use the selected DTC
       * or group of DTC in the requested DTCOrigin and DTCFormat as target for
       * the following API calls:
       * - Dem_ClearDTC
       * - Dem_DisableDTCRecordUpdate
       * - Dem_EnableDTCRecordUpdate
       * - Dem_GetDTCSelectionResult
       * - Dem_GetFunctionalUnitOfDTC
       * - Dem_GetSeverityOfDTC
       * - Dem_GetStatusOfDTC
       * - Dem_SelectFreezeFrameData
       * - Dem_SelectExtendedDataRecord
       * - Dem_SetDTCSuppression
       * - Dem_GetDTCSuppression.
       */
      SchM_Enter_Dem_REQUEST_DATA_PROTECTION();
      /* @Trace: Dem_SUD_API_12308 */
      #if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
      /* @Trace: Dem_SUD_API_12309 */
      Std_ReturnType LddDtcGroupIsValid = Dem_DTCGroupIsValid(DTC, DTCFormat);
      if ((DTCFormat == DEM_DTC_FORMAT_OBD) &&
          (E_OK != LddDtcGroupIsValid))
      {
        /* @Trace: Dem_SUD_API_12300 */
        /*Convert to internal value*/
        /*Dem_ClientSelectDtcState[ClientId].selectedDTC = (DTC >> DEM_EIGHT);*/
        Dem_ClientSelectDtcState[ClientId].selectedDTC = DTC ;
      }
      else
      #endif
      {
        /* @Trace: Dem_SUD_API_12301 */
        Dem_ClientSelectDtcState[ClientId].selectedDTC = DTC;
      }

      Dem_ClientSelectDtcState[ClientId].selectedDTCFormat = DTCFormat;
      Dem_ClientSelectDtcState[ClientId].selectedDTCOrigin = DTCOrigin;

      Dem_ClientSelectDtcState[ClientId].resultSelectDTC = E_OK;
      SchM_Exit_Dem_REQUEST_DATA_PROTECTION();

    }
    LddRetVal = E_OK;
    #endif
    Dem_SelectedDTCServiceUnLock(ClientId, DEM_SELECTDTC_SID_LOCK_IDX);
  }
  return LddRetVal;
}
/*******************************************************************************
** Function Name        : Dem_GetDTCSelectionResult                           **
**                                                                            **
** Service ID           : 0xb8                                                **
**                                                                            **
** Description          : Provides information if the last call to            **
**                        Dem_SelectDTC has selected a                        **
**                        valid DTC or group of DTCs.                         **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Reentrant for different ClientIds, non reentrant    **
**                        for the same ClientId.                              **
**                                                                            **
** Input Parameters     : ClientId             - Unique client id, assigned   **
**                                               to the instance of the       **
**                                               calling module.              **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : E_OK                 - The DTC select parameter     **
**                                               check is successful and the  **
**                                               requested DTC or group of    **
**                                               DTC in the selected origin   **
**                                               is selected for further      **
**                                               operations.                  **
**                        E_NOT_OK             - No DTC selected.             **
**                        DEM_WRONG_DTC        - Selected DTC value in        **
**                                               selected format does not     **
**                                               exist.                       **
**                        DEM_WRONG_DTCORIGIN  - Selected DTCOrigin does not  **
**                                               exist.                       **
**                        DEM_PENDING          - Checking the SelectDTC       **
**                                               parameters is currently in   **
**                                               progress. The caller shall   **
**                                               call this function again     **
**                                               later.                       **
**                        DEM_BUSY             - A different Dem_SelectDTC    **
**                                               dependent operation of this  **
**                                               client is currently in       **
**                                               progress.                    **
** Preconditions        : The API Dem_PreInit(), Dem_Init()                   **
**                        should have been called in sequence                 **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        Dem_GucInit                                         **
**                        Dem_Client                                          **
**                        Dem_ClientSelectDtcState                            **
**                                                                            **
**                        Function(s) invoked :                               **
**                        (void)Det_ReportError                               **
**                                                                            **
*******************************************************************************/
/* @Trace: SRS_BSW_00369 SRS_Diag_04010
 */
/* polyspace +1 MISRA-C3:8.4 [Justified:Low] Justify with annotations */
FUNC(Std_ReturnType, DEM_CODE) Dem_GetDTCSelectionResult(uint8 ClientId)
{
  Std_ReturnType LddRetVal = E_NOT_OK;
  uint16 LusByteShift =
      ((uint16)DEM_ONE << DEM_SELECTDTC_SID_LOCK_IDX) |
      ((uint16)DEM_ONE << DEM_CLEARDTC_SID_LOCK_IDX) |
      ((uint16)DEM_ONE << DEM_DISABLEDTCRECORDUPDATE_SID_LOCK_IDX) |
      ((uint16)DEM_ONE << DEM_ENABLEDTCRECORDUPDATE_SID_LOCK_IDX) |
      ((uint16)DEM_ONE << DEM_GETDTCSELECTIONRESULT_SID_LOCK_IDX) |
      ((uint16)DEM_ONE << DEM_GETFUNCTIONALUNITOFDTC_SID_LOCK_IDX) |
      ((uint16)DEM_ONE << DEM_GETSEVERITYOFDTC_SID_LOCK_IDX) |
      ((uint16)DEM_ONE << DEM_GETSTATUSOFDTC_SID_LOCK_IDX) |
      ((uint16)DEM_ONE << DEM_SELECTFREEZEFRAMEDATA_SID_LOCK_IDX) |
      ((uint16)DEM_ONE << DEM_SELECTEXTENDEDDATARECORD_SID_LOCK_IDX) |
      ((uint16)DEM_ONE << DEM_SETDTCSUPPRESSION_SID_LOCK_IDX) |
      ((uint16)DEM_ONE << DEM_GETDTCSUPPRESSION_SID_LOCK_IDX);
  Std_ReturnType LucResult = Dem_CheckStatusOfSelectedDTCServices(
      ClientId,
      DEM_GETDTCSELECTIONRESULT_SID,
      LusByteShift);
  /* @Trace: Dem_SUD_API_11983 */
  #if (DEM_NUMBER_OF_DEM_CLIENT > DEM_ZERO)
  if (ClientId >= DEM_NUMBER_OF_DEM_CLIENT)
  {
    /* @Trace: Dem_SUD_API_11984 */
    DEM_REPORT_ERROR(DEM_GETDTCSELECTIONRESULT_SID, DEM_E_WRONG_CONFIGURATION);
  }
  else
  #endif
  if (E_OK != LucResult)
  {
    /* @Trace: Dem_SUD_API_10697 */
    LddRetVal = LucResult;
  }
  else
  {
    /* lock this client id */
    Dem_SelectedDTCServiceLock(ClientId,
         DEM_GETDTCSELECTIONRESULT_SID_LOCK_IDX);

    if (DEM_INIT != Dem_GucInit)
    {
      /* @Trace: Dem_SUD_API_10699 */
      DEM_REPORT_ERROR(DEM_GETDTCSELECTIONRESULT_SID, DEM_E_UNINIT);
    }
    /* @Trace: Dem_SUD_API_11985 */
    #if (DEM_NUMBER_OF_DEM_CLIENT > DEM_ZERO)
    else if (E_OK != Dem_ClientSelectDtcState[ClientId].resultSelectDTC)
    {
      /* @Trace: SWS_Dem_01255
       * If any of the APIs requiring a Dem_SelectDTC (see [SWS_Dem_01253])
       * is called without a prior call to Dem_SelectDTC, the Dem shall report
       * the Det error DEM_E_WRONG_CONDITION.
       * */
      /* @Trace: SWS_Dem_01299
       * API behavior without selected DTC
       * If any of the APIs requiring a Dem_SelectDTC according to
       * [SWS_Dem_01253] is called without a prior call of Dem_SelectDTC for
       * this client, the Dem shall report the Det DEM_E_WRONG_CONDITION.
       * */
      /* @Trace: SWS_Dem_01258
       * If the API Dem_GetDTCSelectionResult is called and the Origin
       * provided to Dem_SelectDTC is invalid, the Dem shall return
       * DEM_WRONG_DTCORIGIN.
       * */
      /* @Trace: SWS_Dem_01257
       * If the API Dem_GetDTCSelectionResult is called and the DTC or
       * group of DTC from Dem_SelectDTC is invalid, the Dem shall
       * return DEM_WRONG_DTC.
       * */
      /* @Trace: Dem_SUD_API_10700 */
      DEM_REPORT_ERROR(DEM_GETDTCSELECTIONRESULT_SID, DEM_E_WRONG_CONDITION);
      LddRetVal = Dem_ClientSelectDtcState[ClientId].resultSelectDTC;
    }
    else
    {
      /* @Trace: SWS_Dem_01304
       * Life cycle of Dem_Select dependent operations
       * The Dem shall consider an operation based on Dem_SelectDTC according
       *  to [SWS_Dem_01253] to be finished independently if the client has
       *  requested the E_OK result from the Dem or not.
       * */
      /* @Trace: SWS_Dem_01256
       * The API Dem_GetDTCSelectionResult shall return E_OK, if the selection
       * of Dem_SelectDTC was successful and the DTC or group of DTC are ready
       * for further processing.
       * */
      /* @Trace: Dem_SUD_API_10698 */
      SchM_Enter_Dem_REQUEST_DATA_PROTECTION();
      LddRetVal = Dem_ClientSelectDtcState[ClientId].resultSelectDTC;
      SchM_Exit_Dem_REQUEST_DATA_PROTECTION();
    }
    #endif
    Dem_SelectedDTCServiceUnLock(ClientId,
                         DEM_GETDTCSELECTIONRESULT_SID_LOCK_IDX);
  }

  return LddRetVal;
}

/*******************************************************************************
** Function Name        : Dem_GetDTCSelectionResultForClearDTC                **
**                                                                            **
** Service ID           : 0xbb                                                **
**                                                                            **
** Description          : Provides information if the last call to            **
**                        Dem_SelectDTC has selected a valid DTC or group of  **
**                        DTCs, respecting the settings if the Dem shall      **
**                        clear only all DTCs.                                **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Reentrant for different ClientIds, non reentrant    **
**                        for the same ClientId.                              **
**                                                                            **
** Input Parameters     : ClientId             - Unique client id, assigned   **
**                                               to the instance of the       **
**                                               calling module.              **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : E_OK                 - The DTC select parameter     **
**                                               check is successful and the  **
**                                               requested DTC or group of    **
**                                               DTC in the selected origin   **
**                                               is selected for further      **
**                                               operations.                  **
**                        E_NOT_OK             - No DTC selected.             **
**                        DEM_WRONG_DTC        - Selected DTC value in        **
**                                               selected format              **
**                                               does not exist.              **
**                        DEM_WRONG_DTCORIGIN  - Selected DTCOrigin does not  **
**                                               exist.                       **
**                        DEM_PENDING          - Checking the SelectDTC       **
**                                               parameters is currently in   **
**                                               progress. The caller         **
**                                               shall call this function     **
**                                               again later.                 **
**                        DEM_BUSY             - A different Dem_SelectDTC    **
**                                               dependent operation of this  **
**                                               client is currently in       **
**                                               progress.                    **
** Preconditions        : The API Dem_PreInit(), Dem_Init()                   **
**                        should have been called in sequence                 **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        Dem_GucInit                                         **
**                        Dem_Client                                          **
**                        Dem_ClientSelectDtcState                            **
**                                                                            **
**                        Function(s) invoked :                               **
**                        (void)Det_ReportError                               **
**                                                                            **
*******************************************************************************/
/* @Trace: SRS_BSW_00369 SRS_Diag_04010
 */
FUNC(Std_ReturnType, DEM_CODE) Dem_GetDTCSelectionResultForClearDTC
    ( uint8 ClientId )
{
  Std_ReturnType LddRetVal = E_NOT_OK;
  uint16 LusByteShift =
      ((uint16)DEM_ONE << DEM_SELECTDTC_SID_LOCK_IDX) |
      ((uint16)DEM_ONE << DEM_CLEARDTC_SID_LOCK_IDX) |
      ((uint16)DEM_ONE << DEM_DISABLEDTCRECORDUPDATE_SID_LOCK_IDX) |
      ((uint16)DEM_ONE << DEM_ENABLEDTCRECORDUPDATE_SID_LOCK_IDX) |
      ((uint16)DEM_ONE << DEM_GETDTCSELECTIONRESULT_SID_LOCK_IDX) |
      ((uint16)DEM_ONE << DEM_GETFUNCTIONALUNITOFDTC_SID_LOCK_IDX) |
      ((uint16)DEM_ONE << DEM_GETSEVERITYOFDTC_SID_LOCK_IDX) |
      ((uint16)DEM_ONE << DEM_GETSTATUSOFDTC_SID_LOCK_IDX) |
      ((uint16)DEM_ONE << DEM_SELECTFREEZEFRAMEDATA_SID_LOCK_IDX) |
      ((uint16)DEM_ONE << DEM_SELECTEXTENDEDDATARECORD_SID_LOCK_IDX) |
      ((uint16)DEM_ONE << DEM_SETDTCSUPPRESSION_SID_LOCK_IDX) |
      ((uint16)DEM_ONE << DEM_GETDTCSUPPRESSION_SID_LOCK_IDX);
  Std_ReturnType LucResult = Dem_CheckStatusOfSelectedDTCServices(
      ClientId,
      DEM_GETDTCSELECTIONRESULTFORCLEARDTC_SID,
      LusByteShift);

  /* @Trace: Dem_SUD_API_11986 */
  #if (DEM_NUMBER_OF_DEM_CLIENT > DEM_ZERO)
  if (ClientId >= DEM_NUMBER_OF_DEM_CLIENT)
  {
    /* @Trace: Dem_SUD_API_11987 */
    DEM_REPORT_ERROR(DEM_GETDTCSELECTIONRESULTFORCLEARDTC_SID,
        DEM_E_WRONG_CONFIGURATION);
    /* @LddRetVal = DEM_CLEAR_FAILED; */
  }
  else
  #endif
  if (E_OK != LucResult)
  {
    /* @Trace: Dem_SUD_API_10701 */
    LddRetVal = LucResult;
  }
  else
  {
    /* lock this client id */
    Dem_SelectedDTCServiceLock(ClientId,
        DEM_GETDTCSELECTIONRESULTFORCLEARDTC_SID_LOCK_IDX);

    if (DEM_INIT != Dem_GucInit)
    {
      /* @Trace: Dem_SUD_API_10702 */
      DEM_REPORT_ERROR(DEM_GETDTCSELECTIONRESULTFORCLEARDTC_SID, DEM_E_UNINIT);
    }
    /* @Trace: Dem_SUD_API_11988 */ 
    #if (DEM_NUMBER_OF_DEM_CLIENT > DEM_ZERO)
    else if (E_OK != Dem_ClientSelectDtcState[ClientId].resultSelectDTC)
    {
      /* @Trace: SWS_Dem_01255
       * If any of the APIs requiring a Dem_SelectDTC (see [SWS_Dem_01253]) is
       * called without a prior call to Dem_SelectDTC, the Dem shall report the
       * Det error DEM_E_WRONG_CONDITION.
       * */

      /* @Trace: SWS_Dem_01299
       * API behavior without selected DTC
       * If any of the APIs requiring a Dem_SelectDTC according to
       * [SWS_Dem_01253] is called without a prior call of Dem_SelectDTC for
       * this client, the Dem shall report the Det DEM_E_WRONG_CONDITION.
       * */
      /* @Trace: Dem_SUD_API_10703 */
      DEM_REPORT_ERROR(DEM_GETDTCSELECTIONRESULTFORCLEARDTC_SID,
          DEM_E_WRONG_CONDITION);
      LddRetVal = Dem_ClientSelectDtcState[ClientId].resultSelectDTC;
    }
    #endif
    else
    {
      /* @Trace: Dem_SUD_API_11989 */
      #if (DEM_NUMBER_OF_DEM_CLIENT > DEM_ZERO)
      SchM_Enter_Dem_REQUEST_DATA_PROTECTION();
      LddRetVal = Dem_ClientSelectDtcState[ClientId].resultSelectDTC;
      /* @Trace: Dem_SUD_API_11990 */
      #if (DEM_CLEAR_DTC_LIMITATION == DEM_ONLY_CLEAR_ALL_DTCS)
      /* @Trace: Dem_SUD_API_11991 */
      if (E_NOT_OK == Dem_DTCGroupIsValid(
          Dem_ClientSelectDtcState[ClientId].selectedDTC,
          Dem_ClientSelectDtcState[ClientId].selectedDTCFormat))
      {
        /* @Trace: SWS_Dem_01296
         * Definition of Dem_GetDTCSelectionResultForClearDTC functionality
         * The API Dem_GetDTCSelectionResultForClearDTC shall behave exactly as
         *  Dem_GetDTCSelectionResult with the only difference that,
         *  DEM_WRONG_DTC is returned in case of a single DTC was selected
         * and DemClearDTCLimitation is set to DEM_ONLY_CLEAR_ALL_DTCS for
         * that client.
         * */
        /* @Trace: Dem_SUD_API_10704 */
        DEM_REPORT_ERROR(DEM_GETDTCSELECTIONRESULTFORCLEARDTC_SID,
            DEM_E_PARAM_DATA);
        LddRetVal = DEM_WRONG_DTC;
      }
      #endif
      SchM_Exit_Dem_REQUEST_DATA_PROTECTION();
      #endif
    }
    Dem_SelectedDTCServiceUnLock(ClientId,
        DEM_GETDTCSELECTIONRESULTFORCLEARDTC_SID_LOCK_IDX);
  }
  return LddRetVal;
}

/*******************************************************************************
** Function Name        : Dem_DisableDTCSetting                               **
**                                                                            **
** Service ID           : 0x24                                                **
**                                                                            **
** Description          : This function shall be called to disable the DTC    **
**                        setting for a DTC group                             **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Reentrant for different ClientIds, non reentrant    **
**                        for the same ClientId.                              **
**                                                                            **
** Input Parameters     : ClientId                                            **
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
** Remarks              : Global Variable(s)     :                            **
**                        Dem_GucInit                                         **
**                        Dem_GaaDisableDtcSettingMemSet                      **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        (void)Det_ReportError                               **
**                                                                            **
*******************************************************************************/
/* @Trace: SRS_Diag_04010 SRS_Diag_04164
 */
FUNC(Std_ReturnType, DEM_CODE) Dem_DisableDTCSetting(uint8 ClientId)
{
  /* @Trace: SWS_Dem_01290
   * DTCs affected by Dem_DisableDTCSetting and Dem_EnableDTCSetting
   * Calls of the APIs Dem_DisableDTCSetting and Dem_EnableDTCSetting have
   *  effect on all events and UDS status bytes assigned the DemEventMemorySet
   *  referenced by the clientId of the call. DTCs not referenced from
   *  this DemEventMemorySet are not affected.
   * */
  Std_ReturnType LddRetVal = E_OK;

  boolean LblDisableDTCSettingSIDLockIdx = Dem_SelectedDTCServiceIsLock(ClientId,
      DEM_DISABLEDTCSETTING_SID_LOCK_IDX);

  #if (DEM_NUMBER_OF_DEM_CLIENT > DEM_ZERO)
  if (DEM_NUMBER_OF_DEM_CLIENT <= ClientId)
  {
    /* @Trace: Dem_SUD_API_20580 */
    DEM_REPORT_ERROR(DEM_DISABLEDTCSETTING_SID, DEM_E_PARAM_DATA);
    LddRetVal = E_NOT_OK;
  }
  else
  #endif
  if (DEM_TRUE == LblDisableDTCSettingSIDLockIdx)
  {
    /* @Trace: Dem_SUD_API_20096 */
    LddRetVal = DEM_PENDING;
  }
  else
  {
    /* lock this client id */
    Dem_SelectedDTCServiceLock(ClientId, DEM_DISABLEDTCSETTING_SID_LOCK_IDX);

    /* Module initialization check */
    if (Dem_GucInit != DEM_INIT)
    {
      /* @Trace: Dem_SUD_API_20581 */
      DEM_REPORT_ERROR(DEM_DISABLEDTCSETTING_SID, DEM_E_UNINIT);
      LddRetVal = E_NOT_OK;
    }
    else
    {
      /* @Trace: Dem_SUD_API_20583 */
      /* polyspace-begin MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] Same as Dead Code. */
      /* polyspace-begin DEFECT:DEAD_CODE [Justified:Low] Dead Code by Call function.*/
      /* polyspace +1 DEFECT:DATA_RACE [Not a defect:Low] "Not a defect" */ 
      #if (DEM_NUMBER_OF_DEM_CLIENT > DEM_ZERO)
      if (DEM_NO_EVMEM_IDX != Dem_Client[ClientId].usDemEventMemorySetId)
      {
        /* @Trace: Dem_SUD_API_20582 */
        /* @Trace: SWS_Dem_00079
         * If the function Dem_DisableDTCSetting is called, the Dem shall
         * disable the storage of all events and UDS status byte updates.
         * */

        /* Enable DTC setting of the requested Memory set of client Id */
        Dem_GaaDisableDtcSettingMemSet[
               Dem_Client[ClientId].usDemEventMemorySetId] = DEM_TRUE;
      }
      else
      #endif
      {
        /* @Trace: Dem_SUD_API_20097 */
        DEM_REPORT_ERROR(DEM_DISABLEDTCSETTING_SID, DEM_E_PARAM_DATA);
        LddRetVal = E_NOT_OK;
      }
      /* polyspace-end MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] Same as Dead Code. */
      /* polyspace-end DEFECT:DEAD_CODE [Justified:Low] */
    }
    Dem_SelectedDTCServiceUnLock(ClientId,
                     DEM_DISABLEDTCSETTING_SID_LOCK_IDX);
  }

  /* Return the value */
  return LddRetVal;
}
/*******************************************************************************
** Function Name        : Dem_EnableDTCSetting                                **
**                                                                            **
** Service ID           : 0x25                                                **
**                                                                            **
** Description          : This function shall be called to enable the DTC     **
**                        setting for a DTC group                             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : DTCGroup, DTCKind                                   **
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
** Remarks              : Global Variable(s)     :                            **
**                        Dem_GucInit                                         **
**                        Dem_GaaDisableDtcSettingMemSet                      **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        (void)Det_ReportError                               **
**                        Dem_GetIndexOfDTCGroup                              **
*******************************************************************************/
/* @Trace: SRS_BSW_00101 SRS_BSW_00310 SRS_Diag_04010 SRS_Diag_04115
           SRS_Diag_04125 SRS_Diag_04158 SRS_Diag_04164
 */
FUNC(Std_ReturnType, DEM_CODE) Dem_EnableDTCSetting(uint8 ClientId)
{
  /* @Trace: SWS_Dem_01290
   * DTCs affected by Dem_DisableDTCSetting and Dem_EnableDTCSetting
   * Calls of the APIs Dem_DisableDTCSetting and Dem_EnableDTCSetting have
   *  effect on all events and UDS status bytes assigned the DemEventMemorySet
   *  referenced by the clientId of the call. DTCs not referenced from
   *  this DemEventMemorySet are not affected.
   * */
  Std_ReturnType LddRetVal = E_OK;

  boolean LblEnableDTCSettingSIDLockIdx = Dem_SelectedDTCServiceIsLock(ClientId,
      DEM_ENABLEDTCSETTING_SID_LOCK_IDX);
  /* @Trace: Dem_SUD_API_20587 */
  #if (DEM_NUMBER_OF_DEM_CLIENT > DEM_ZERO)
  /* @Trace: Dem_SUD_API_20592 */
  if (DEM_NUMBER_OF_DEM_CLIENT <= ClientId)
  {
    /* @Trace: Dem_SUD_API_20593 */
    DEM_REPORT_ERROR(DEM_ENABLEDTCSETTING_SID, DEM_E_PARAM_DATA);
    LddRetVal = E_NOT_OK;
  }
  else
  #endif
  if (DEM_TRUE == LblEnableDTCSettingSIDLockIdx)
  {
    /* @Trace: Dem_SUD_API_20098 */
    LddRetVal = DEM_PENDING;
  }
  else
  {
    /* lock this client id */
    /* @Trace: Dem_SUD_API_20594 */
    Dem_SelectedDTCServiceLock(ClientId,
                   DEM_ENABLEDTCSETTING_SID_LOCK_IDX);
    /* @Trace: Dem_SUD_API_20596 */
    if (Dem_GucInit != DEM_INIT)
    {
      /* @Trace: Dem_SUD_API_20595 */
      DEM_REPORT_ERROR(DEM_ENABLEDTCSETTING_SID, DEM_E_UNINIT);
      LddRetVal = E_NOT_OK;
    }
    else
    {
      /* @Trace: Dem_SUD_API_20597 */
      #if (DEM_NUMBER_OF_DEM_CLIENT > DEM_ZERO)
      /* @Trace: Dem_SUD_API_20598 */
      /* polyspace-begin MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] Same as Dead Code. */
      /* polyspace-begin DEFECT:DEAD_CODE [Justified:Low] Dead Code by Call function.*/
      /* polyspace +1 DEFECT:DATA_RACE [Not a defect:Low] "Not a defect" */ 
      if (DEM_NO_EVMEM_IDX != Dem_Client[ClientId].usDemEventMemorySetId)
      {
        /* @Trace: SWS_Dem_00682
         * The API Dem_EnableDTCSetting shall trigger the callback function
         * InitMonitorForEvent of the related event(s) in case ControlDTCSetting
         * of the event(s) is re-enabled. The InitMonitorReason parameter shall
         * be set to DEM_INIT_MONITOR_REENABLED.
         * */
        /* @Trace: Dem_SUD_API_20599 */
        if (Dem_GaaDisableDtcSettingMemSet[
              Dem_Client[ClientId].usDemEventMemorySetId] != DEM_FALSE)
        {
          /* @Trace: Dem_SUD_API_20588 */
          /* @Trace: SWS_Dem_00080
           * If the function Dem_EnableDTCSetting is called, the Dem shall
           * enable the storage of all events and UDS status byte.
           * */

          /* Enable DTC setting of the requested Memory set of client Id */
          Dem_GaaDisableDtcSettingMemSet[
               Dem_Client[ClientId].usDemEventMemorySetId] = DEM_FALSE;
          /* @Trace: Dem_SUD_API_20589 */
          for ( Dem_EventIdType LddEventId = DEM_ONE;
                LddEventId <= DEM_NUMBER_OF_EVENTS;
                LddEventId++ )
          {
            /* @Trace: SWS_Dem_00256
             */
            Dem_EventParameterPCType LddEvent = &Dem_Event[
                                  LddEventId - DEM_ONE];
            /* @Trace: Dem_SUD_API_20591 */
            if (( LddEvent->ucEventMemDstIdx ==
                Dem_Client[ClientId].usDemEventMemorySetId) &&
                (LddEvent->pDemInitMonitorForEvent != NULL_PTR))
            {
              /* polyspace<RTE: COR : Not a defect : No Action Planned >
               * function ptr points to a valid function */
              /* @Trace: Dem_SUD_API_20590 */
              LddEvent->pDemInitMonitorForEvent(
                  (Dem_InitMonitorReasonType) DEM_INIT_MONITOR_REENABLED);
            }
          }
        }
      }
      else
      #endif
      {
        /* @Trace: Dem_SUD_API_20099 */
        DEM_REPORT_ERROR(DEM_ENABLEDTCSETTING_SID, DEM_E_PARAM_DATA);
        LddRetVal = E_NOT_OK;
      }
      /* polyspace-end MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] Same as Dead Code. */
      /* polyspace-end DEFECT:DEAD_CODE [Justified:Low] */
    }
    Dem_SelectedDTCServiceUnLock(ClientId,
                       DEM_ENABLEDTCSETTING_SID_LOCK_IDX);
  }
  /* Return the value */
  return LddRetVal;
}
/*******************************************************************************
** Function Name        : Dem_DisableDTCRecordUpdate                          **
**                                                                            **
** Service ID           : 0x1a                                                **
**                                                                            **
** Description          : Disables the event memory update of a specific DTC  **
**                        (only one at one time).                             **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Reentrant for different ClientIds, non reentrant    **
**                        for the same ClientId.                              **
**                                                                            **
** Input Parameters     : ClientId             - Unique client id, assigned to**
**                                               the instance of the calling  **
**                                               module.                      **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
** Return parameter     : E_OK                 - The DTC select parameter     **
**                                               check is successful and the **
**                                               requested DTC or group of   **
**                                               DTC in the selected origin  **
**                                               is selected for further      **
**                                               operations.                  **
**                        E_NOT_OK             - No DTC selected.             **
**                        DEM_WRONG_DTC        - Selected DTC value in        **
**                                               selected format does not     **
**                                               exist.                       **
**                        DEM_WRONG_DTCORIGIN  - Selected DTCOrigin does not  **
**                                               exist.                       **
**                        DEM_PENDING          - Checking the SelectDTC       **
**                                               parameters is currently in   **
**                                               progress. The caller         **
**                                               shall call this function     **
**                                               again later.                 **
**                        DEM_BUSY             - A different Dem_SelectDTC    **
**                                               dependent operation of this  **
**                                               client is currently in       **
**                                               progress.                    **
** Preconditions        : The API Dem_PreInit(), Dem_Init()                   **
**                        should have been called in sequence                 **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Dem_GucInit                                         **
**                        Dem_Event                                           **
**                        Dem_ClientSelectDtcState                            **
**                        Function(s) invoked    :                            **
**                        (void)Det_ReportError                               **
**                        SchM_Exit_Dem_REQUEST_RECORD_PROTECTION             **
*******************************************************************************/
/* @Trace: SRS_BSW_00369 SRS_Diag_04010 SRS_Diag_04066
 */
FUNC(Std_ReturnType, DEM_CODE)Dem_DisableDTCRecordUpdate(uint8 ClientId)
{
  Std_ReturnType LddRetVal = E_NOT_OK;
  uint16 LusByteShift =
      ((uint16)DEM_ONE << DEM_SELECTDTC_SID_LOCK_IDX) |
      ((uint16)DEM_ONE << DEM_CLEARDTC_SID_LOCK_IDX) |
      ((uint16)DEM_ONE << DEM_DISABLEDTCRECORDUPDATE_SID_LOCK_IDX) |
      ((uint16)DEM_ONE << DEM_ENABLEDTCRECORDUPDATE_SID_LOCK_IDX) |
      ((uint16)DEM_ONE << DEM_GETDTCSELECTIONRESULT_SID_LOCK_IDX) |
      ((uint16)DEM_ONE << DEM_GETFUNCTIONALUNITOFDTC_SID_LOCK_IDX) |
      ((uint16)DEM_ONE << DEM_GETSEVERITYOFDTC_SID_LOCK_IDX) |
      ((uint16)DEM_ONE << DEM_GETSTATUSOFDTC_SID_LOCK_IDX) |
      ((uint16)DEM_ONE << DEM_SELECTFREEZEFRAMEDATA_SID_LOCK_IDX) |
      ((uint16)DEM_ONE << DEM_SELECTEXTENDEDDATARECORD_SID_LOCK_IDX) |
      ((uint16)DEM_ONE << DEM_SETDTCSUPPRESSION_SID_LOCK_IDX) |
      ((uint16)DEM_ONE << DEM_GETDTCSUPPRESSION_SID_LOCK_IDX);
  Std_ReturnType LucResult = Dem_CheckStatusOfSelectedDTCServices(
      ClientId,
      DEM_DISABLEDTCRECORDUPDATE_SID,
      LusByteShift);

  #if (DEM_NUMBER_OF_DEM_CLIENT > DEM_ZERO)
  if (ClientId >= DEM_NUMBER_OF_DEM_CLIENT)
  {
    /* @Trace: Dem_SUD_API_20450 */
      DEM_REPORT_ERROR(DEM_DISABLEDTCRECORDUPDATE_SID,
           DEM_E_WRONG_CONFIGURATION);
  }
  else
  #endif
  if (E_OK != LucResult)
  {
    /* @Trace: Dem_SUD_API_20100 */
    LddRetVal = LucResult;
  }
  else
  {
    /* lock this client id */
    Dem_SelectedDTCServiceLock(ClientId,
        DEM_DISABLEDTCRECORDUPDATE_SID_LOCK_IDX);
    if (Dem_GucInit != DEM_INIT)
    {
      /* @Trace: Dem_SUD_API_20453 */
      DEM_REPORT_ERROR(DEM_DISABLEDTCRECORDUPDATE_SID, DEM_E_UNINIT);
    }
    /* @Trace: Dem_SUD_API_20451 */
    #if (DEM_NUMBER_OF_DEM_CLIENT > DEM_ZERO)
    /* @Trace: Dem_SUD_API_20454 */
    else if (E_OK != Dem_ClientSelectDtcState[ClientId].resultSelectDTC)
    {
      /* @Trace: SWS_Dem_01255
       * If any of the APIs requiring a Dem_SelectDTC (see [SWS_Dem_01253]) is
       * called without a prior call to Dem_SelectDTC, the Dem shall report the
       *  Det error DEM_E_WRONG_CONDITION.
       * */
      /* @Trace: SWS_Dem_01299
       * API behavior without selected DTC
       * If any of the APIs requiring a Dem_SelectDTC according to
       * [SWS_Dem_01253] is called without a prior call of Dem_SelectDTC for
       * this client, the Dem shall report the Det DEM_E_WRONG_CONDITION.
       * */
      /* @Trace: SWS_Dem_01258
       * If the API Dem_GetDTCSelectionResult is called and the Origin provided
       * to Dem_SelectDTC is invalid, the Dem shall return DEM_WRONG_DTCORIGIN.
       * */
      /* @Trace: SWS_Dem_01257
       * If the API Dem_GetDTCSelectionResult is called and the DTC or group of
       * DTC from Dem_SelectDTC is invalid, the Dem shall return DEM_WRONG_DTC.
       * */
      /* @Trace: Dem_SUD_API_20452 */
      DEM_REPORT_ERROR(DEM_DISABLEDTCRECORDUPDATE_SID, DEM_E_WRONG_CONDITION);
      LddRetVal = Dem_ClientSelectDtcState[ClientId].resultSelectDTC;
    }
    else
    {
      Dem_EventIdType LddEventId;
      switch( Dem_GetConditionOfDTCRecordUpdate(ClientId,
          Dem_ClientSelectDtcState[ClientId].selectedDTC))
      {
        case DEM_CONDITIONDTCRECUP_NO_DTC:
          LddEventId = Dem_GetEventIdByDTC(DEM_DISABLEDTCRECORDUPDATE_SID,
              Dem_ClientSelectDtcState[ClientId].selectedDTC,
              Dem_ClientSelectDtcState[ClientId].selectedDTCFormat);
          /* @if (DEM_FALSE == Dem_EventIdIsValid(LddEventId)) */
          if (( LddEventId > DEM_NUMBER_OF_EVENTS) ||
              ( DEM_NO_EVENT == LddEventId))
          {
            /* @Trace: Dem_SUD_API_20101 */
            DEM_REPORT_ERROR(DEM_DISABLEDTCRECORDUPDATE_SID,
                 DEM_E_PARAM_CONFIG);
            LddRetVal = DEM_WRONG_DTC;
          }
          else
          {
            SchM_Enter_Dem_REQUEST_RECORD_PROTECTION();
            /* @Trace: Dem_SUD_API_20447 */
            #if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
            if (DEM_TRUE ==
                Dem_DTCFormatIsValid(LddEventId, DEM_DTC_FORMAT_OBD))
            {
              /* @Trace: Dem_SUD_API_20448 */
              /* Load the DTC for which record update to be disabled */
              Dem_GstRecordDisableDTC[ClientId].usObdDtc =
                  (uint16)Dem_ClientSelectDtcState[ClientId].selectedDTC;
            }
            else
            /* @Trace: Dem_SUD_API_20449 */
            #endif
            {
              /* Load the DTC for which record update to be disabled */
              Dem_GstRecordDisableDTC[ClientId].ulUdsDtc =
                  Dem_ClientSelectDtcState[ClientId].selectedDTC;
            }
            SchM_Exit_Dem_REQUEST_RECORD_PROTECTION();
            LddRetVal = E_OK;
          }
          break;
          
        case DEM_CONDITIONDTCRECUP_DISABLED_DTC:
        /* @Trace: Dem_SUD_API_20102 */
          LddRetVal = E_OK;
          break;

        /* @Trace: SWS_Dem_00648
         * If development error detection is enabled and the function
         * Dem_DisableDTCRecordUpdate is called while another DTC is locked by
         * the same client, the Dem module shall report the Det
         * DEM_E_WRONG_CONDITION (refer also to [SWS_Dem_00370]).
         */
        default:
        /* @Trace: Dem_SUD_API_20103 */
          DEM_REPORT_ERROR(DEM_DISABLEDTCRECORDUPDATE_SID,
                DEM_E_WRONG_CONDITION);
          LddRetVal = E_NOT_OK;
          break;
      }
    }
    #endif
    Dem_SelectedDTCServiceUnLock(ClientId,
                        DEM_DISABLEDTCRECORDUPDATE_SID_LOCK_IDX);
  }
  return LddRetVal;
}
/******************************************************************************
** Function Name        : Dem_EnableDTCRecordUpdate                          **
**                                                                           **
** Service ID           : 0x1b                                               **
**                                                                           **
** Description          : Enables the event memory update of the DTC disabled**
**                        by Dem_DcmDisableDTCRecordUpdate() before.         **
**                                                                           **
** Sync/Async           : Asynchronous                                       **
**                                                                           **
** Re-entrancy          : Reentrant for different ClientIds, non reentrant   **
**                        for the same ClientId.                             **
**                                                                           **
** Input Parameters     : ClientId      : Unique client id, assigned to the  **
**                                        instance of the calling module.    **
**                                                                           **
** InOut parameter      : None                                               **
**                                                                           **
** Output Parameters    : None                                               **
**                                                                           **
** Return parameter     : Std_ReturnType                                     **
**                        E_OK          : DTC record successfully updated.   **
**                        E_NOT_OK      : No DTC selected.                   **
**                        DEM_BUSY      : A different Dem_SelectDTC dependent**
**                                        operation according to             **
**                                        SWS_Dem_01253 of this              **
**                                        client is currently in progress.   **
**                                                                           **
** Preconditions        : The API Dem_PreInit(), Dem_Init()                  **
**                        should have been called in sequence                **
**                                                                           **
** Remarks              : Global Variable(s)    :                            **
**                        Dem_GucInit                                        **
**                        Dem_ClientSelectDtcState                           **
**                                                                           **
**                        Function(s) invoked   :                            **
**                        (void)Det_ReportError                              **
**                        SchM_Exit_Dem_REQUEST_RECORD_PROTECTION()          **
*******************************************************************************/
/* @Trace: SRS_Diag_04074
 */
FUNC(Std_ReturnType, DEM_CODE) Dem_EnableDTCRecordUpdate(uint8 ClientId)
{
  Std_ReturnType LddRetVal = E_OK;
  uint16 LusByteShift =
      ((uint16)DEM_ONE << DEM_SELECTDTC_SID_LOCK_IDX) |
      ((uint16)DEM_ONE << DEM_CLEARDTC_SID_LOCK_IDX) |
      ((uint16)DEM_ONE << DEM_DISABLEDTCRECORDUPDATE_SID_LOCK_IDX) |
      ((uint16)DEM_ONE << DEM_ENABLEDTCRECORDUPDATE_SID_LOCK_IDX) |
      ((uint16)DEM_ONE << DEM_GETDTCSELECTIONRESULT_SID_LOCK_IDX) |
      ((uint16)DEM_ONE << DEM_GETFUNCTIONALUNITOFDTC_SID_LOCK_IDX) |
      ((uint16)DEM_ONE << DEM_GETSEVERITYOFDTC_SID_LOCK_IDX) |
      ((uint16)DEM_ONE << DEM_GETSTATUSOFDTC_SID_LOCK_IDX) |
      ((uint16)DEM_ONE << DEM_SELECTFREEZEFRAMEDATA_SID_LOCK_IDX) |
      ((uint16)DEM_ONE << DEM_SELECTEXTENDEDDATARECORD_SID_LOCK_IDX) |
      ((uint16)DEM_ONE << DEM_SETDTCSUPPRESSION_SID_LOCK_IDX) |
      ((uint16)DEM_ONE << DEM_GETDTCSUPPRESSION_SID_LOCK_IDX);
  Std_ReturnType LucResult = Dem_CheckStatusOfSelectedDTCServices(
      ClientId,
      DEM_ENABLEDTCRECORDUPDATE_SID,
      LusByteShift);
  
  /* @Trace: Dem_SUD_API_20460 */
  #if (DEM_NUMBER_OF_DEM_CLIENT > DEM_ZERO)
  if (ClientId >= DEM_NUMBER_OF_DEM_CLIENT)
  {
    /* @Trace: Dem_SUD_API_20463 */
    DEM_REPORT_ERROR(DEM_ENABLEDTCRECORDUPDATE_SID, DEM_E_WRONG_CONFIGURATION);
    LddRetVal = E_NOT_OK;
  }
  else
  /* @Trace: Dem_SUD_API_20462 */
  #endif
  if (E_OK != LucResult)
  {
    /* @Trace: Dem_SUD_API_20104 */
    LddRetVal = LucResult;
  }
  else
  {
    /* lock this client id */
    Dem_SelectedDTCServiceLock(ClientId,
        DEM_ENABLEDTCRECORDUPDATE_SID_LOCK_IDX);
    if (Dem_GucInit != DEM_INIT)
    {
      /* @Trace: Dem_SUD_API_20464 */
      DEM_REPORT_ERROR(DEM_ENABLEDTCRECORDUPDATE_SID, DEM_E_UNINIT);
      LddRetVal = E_NOT_OK;
    }
    /* @Trace: Dem_SUD_API_20465 */
    #if (DEM_NUMBER_OF_DEM_CLIENT > DEM_ZERO)
    else if (E_OK != Dem_ClientSelectDtcState[ClientId].resultSelectDTC)
    {
      /* @Trace: Dem_SUD_API_20105 */
      DEM_REPORT_ERROR(DEM_ENABLEDTCRECORDUPDATE_SID, DEM_E_WRONG_CONDITION);
      LddRetVal = E_NOT_OK;
    }
    else
    {
      /* @Trace: SWS_Dem_00271
       * The function Dem_EnableDTCRecordUpdate shall release the currently
       * disabled DTC which has been protected by the function
       * Dem_DisableDTCRecordUpdate, so that the data can be updated again.
       */
      SchM_Enter_Dem_REQUEST_RECORD_PROTECTION();
      #if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
      /* Enable the record update */
      /* @Trace: Dem_SUD_API_20461 */
      Dem_GstRecordDisableDTC[ClientId].usObdDtc = DEM_ZERO;

      Dem_GstRecordDisableDTC[ClientId].ulUdsDtc = DEM_ZERO;
      #else
      /* Enable the record update */
      /* @Trace: Dem_SUD_API_20466 */
      Dem_GstRecordDisableDTC[ClientId].ulUdsDtc = DEM_ZERO;
      #endif
      SchM_Exit_Dem_REQUEST_RECORD_PROTECTION();
    }
    #endif
    Dem_SelectedDTCServiceUnLock(ClientId,
                DEM_ENABLEDTCRECORDUPDATE_SID_LOCK_IDX);
  }
  return LddRetVal;
}
/*******************************************************************************
** Function Name        : Dem_GetFunctionalUnitOfDTC                          **
**                                                                            **
** Service ID           : 0x34                                                **
**                                                                            **
** Description          : Gets the functional unit of the requested DTC.      **
**                                                                            **
** Sync/Async           : Reentrant for different ClientIds, non reentrant    **
**                        for the same ClientId.                              **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : ClientId          - Unique client id, assigned to   **
**                                            the instance of the calling     **
**                                            module.                         **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : DTCFunctionalUnit                                   **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : The API Dem_PreInit(), Dem_Init()                   **
**                        should have been called in sequence                 **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Dem_GucInit                                         **
**                        Dem_Event                                           **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        (void)Det_ReportError                               **
*******************************************************************************/
/* @Trace: SRS_Diag_04071 SRS_Diag_04220 SRS_Diag_04156
 */
FUNC(Std_ReturnType, DEM_CODE) Dem_GetFunctionalUnitOfDTC(uint8 ClientId,
P2VAR (uint8, AUTOMATIC, DEM_APPL_DATA) DTCFunctionalUnit)
{
  Std_ReturnType LddRetVal = E_NOT_OK;
  uint16 LusByteShift =
      ((uint16)DEM_ONE << DEM_SELECTDTC_SID_LOCK_IDX) |
      ((uint16)DEM_ONE << DEM_CLEARDTC_SID_LOCK_IDX) |
      ((uint16)DEM_ONE << DEM_DISABLEDTCRECORDUPDATE_SID_LOCK_IDX) |
      ((uint16)DEM_ONE << DEM_ENABLEDTCRECORDUPDATE_SID_LOCK_IDX) |
      ((uint16)DEM_ONE << DEM_GETDTCSELECTIONRESULT_SID_LOCK_IDX) |
      ((uint16)DEM_ONE << DEM_GETFUNCTIONALUNITOFDTC_SID_LOCK_IDX) |
      ((uint16)DEM_ONE << DEM_GETSEVERITYOFDTC_SID_LOCK_IDX) |
      ((uint16)DEM_ONE << DEM_GETSTATUSOFDTC_SID_LOCK_IDX) |
      ((uint16)DEM_ONE << DEM_SELECTFREEZEFRAMEDATA_SID_LOCK_IDX) |
      ((uint16)DEM_ONE << DEM_SELECTEXTENDEDDATARECORD_SID_LOCK_IDX) |
      ((uint16)DEM_ONE << DEM_SETDTCSUPPRESSION_SID_LOCK_IDX) |
      ((uint16)DEM_ONE << DEM_GETDTCSUPPRESSION_SID_LOCK_IDX);
  Std_ReturnType LucResult = Dem_CheckStatusOfSelectedDTCServices(
      ClientId,
      DEM_GETFUNCTIONALUNITOFDTC_SID,
      LusByteShift);

  /* @Trace: SWS_Dem_01293
   * If the API Dem_GetFunctionalUnitOfDTC is called and for the selected DTC
   * a functional unit value in DemDTCFunctionalUnit is configured, the Dem
   * shall set the value configured in DemDTCFunctionalUnit in the out parameter
   * DTCFunctionalUnit.
   */

  /* @Trace: SWS_Dem_01294
   * If the API Dem_GetFunctionalUnitOfDTC is called and for the selected
   * DTC no functional unit in DemDTCFunctionalUnit is configured, the
   * Dem shall set a value of 0x00 in the out parameter DTCFunctionalUnit.
   * */
  /* @Trace: Dem_SUD_API_20254 */
  #if (DEM_NUMBER_OF_DEM_CLIENT > DEM_ZERO)
  if (ClientId >= DEM_NUMBER_OF_DEM_CLIENT)
  {
    /* @Trace: Dem_SUD_API_20265 */
    DEM_REPORT_ERROR(DEM_GETFUNCTIONALUNITOFDTC_SID, DEM_E_WRONG_CONFIGURATION);
    /* @LddRetVal = E_NOT_OK; */
  }
  else
  /* @Trace: Dem_SUD_API_20262 */
  #endif
  if (E_OK != LucResult)
  {
    /* @Trace: Dem_SUD_API_20061 */
    LddRetVal = LucResult;
  }
  else
  {
    /* lock this client id */
    Dem_SelectedDTCServiceLock(ClientId,
        DEM_GETFUNCTIONALUNITOFDTC_SID_LOCK_IDX);

    if ( Dem_GucInit != DEM_INIT)
    {
      /* @Trace: Dem_SUD_API_20269 */
      DEM_REPORT_ERROR(DEM_GETFUNCTIONALUNITOFDTC_SID, DEM_E_UNINIT);
      /* @LddRetVal = E_NOT_OK; */
    }
    /* @Trace: Dem_SUD_API_20266 */
    #if (DEM_NUMBER_OF_DEM_CLIENT > DEM_ZERO)
    /* @Trace: Dem_SUD_API_20267 */
    #if (DEM_MAX_NUM_GRP_DTC > DEM_ZERO)
    /* @Trace: Dem_SUD_API_20268 */
    else if ( DEM_DTC_GROUP_IS_VALID(
        Dem_ClientSelectDtcState[ClientId].selectedDTC))
    {
      /* @Trace: Dem_SUD_API_20255 */
      DEM_REPORT_ERROR(DEM_GETFUNCTIONALUNITOFDTC_SID, DEM_E_PARAM_DATA);
      LddRetVal = DEM_WRONG_DTC;
    }
    #endif
    #endif
    else if (DTCFunctionalUnit == NULL_PTR)
    {
      /* @Trace: Dem_SUD_API_20256 */
      DEM_REPORT_ERROR(DEM_GETFUNCTIONALUNITOFDTC_SID, DEM_E_PARAM_POINTER);
      /* @LddRetVal = E_NOT_OK; */
    }
    /* @Trace: Dem_SUD_API_20257 */
    #if (DEM_NUMBER_OF_DEM_CLIENT > DEM_ZERO)
    /* @Trace: Dem_SUD_API_20258 */
    else if (E_OK != Dem_ClientSelectDtcState[ClientId].resultSelectDTC)
    {
      /* @Trace: Dem_SUD_API_20259 */
      DEM_REPORT_ERROR(DEM_GETFUNCTIONALUNITOFDTC_SID, DEM_E_WRONG_CONDITION);
      LddRetVal = Dem_ClientSelectDtcState[ClientId].resultSelectDTC;
    }
    #endif
    else
    {
      /* @Trace: Dem_SUD_API_20260 */
      #if (DEM_NUMBER_OF_DEM_CLIENT > DEM_ZERO)
      Dem_EventIdType LddEventId = Dem_GetEventIdByDTC(
          DEM_GETFUNCTIONALUNITOFDTC_SID,
          Dem_ClientSelectDtcState[ClientId].selectedDTC,
          Dem_ClientSelectDtcState[ClientId].selectedDTCFormat);
      
      if ((LddEventId > DEM_NUMBER_OF_EVENTS) || (DEM_NO_EVENT == LddEventId))
      {
        /* @Trace: Dem_SUD_API_20063 */
        DEM_REPORT_ERROR(DEM_GETFUNCTIONALUNITOFDTC_SID, DEM_E_PARAM_CONFIG);
        LddRetVal = DEM_WRONG_DTC;
      }
      else if (DEM_TRUE == Dem_EvIsProcStateTriggered(LddEventId,
                 DEM_EVPROCSTATE_DTC_SUPP))
      {
        /* @Trace: SWS_Dem_01100
         * Behavior of DTC query functions for suppressed DTCs. In
         * case any of the following APIs is called on a single
         * selected DTC which is suppressed, the Dem shall return DEM_WRONG_DTC
         * */
        /* @Trace: Dem_SUD_API_20261 */
        LddRetVal = DEM_WRONG_DTC;
      }
      else
      {
        Dem_CombinedDtcPCType LddCbDTC =
            Dem_GetDtcByDtcId( Dem_ClientSelectDtcState[ClientId].selectedDTC,
            Dem_ClientSelectDtcState[ClientId].selectedDTCFormat);

        if ( NULL_PTR == LddCbDTC)
        {
          /* @Trace: Dem_SUD_API_20263 */
          DEM_REPORT_ERROR(DEM_GETFUNCTIONALUNITOFDTC_SID, DEM_E_PARAM_CONFIG);
          LddRetVal = DEM_WRONG_DTC;
        }
        else
        {
          /* @Trace: Dem_SUD_API_20264 */
          *DTCFunctionalUnit = LddCbDTC->ucDtcFunctionalUnit;
          LddRetVal = E_OK;
        }
      }
      #endif
    }
    /* unlock this client id */
    Dem_SelectedDTCServiceUnLock(ClientId,
            DEM_GETFUNCTIONALUNITOFDTC_SID_LOCK_IDX);
  }

  return LddRetVal;
}


/******************************************************************************
** Function Name        : Dem_SelectFreezeFrameData                          **
**                                                                           **
** Service ID           : 0xb9                                               **
**                                                                           **
** Description          : Sets the filter to be used by                      **
**                        Dem_GetNextFreezeFrameData and                     **
**                        Dem_GetSizeOfFreezeFrameSelection.                 **
**                                                                           **
** Sync/Async           : Synchronous                                        **
**                                                                           **
** Re-entrancy          : Reentrant for different ClientIds, non reentrant   **
**                        for the same ClientId.                             **
**                                                                           **
** Input Parameters     : ClientId             - Unique client id, assigned  **
**                                               to the instance             **
**                                               of the calling module.      **
**                        RecordNumber         - Unique identifier for a     **
**                                               snapshot record as          **
**                                               defined in ISO 14229-1.     **
**                                               The value 0xFF is a         **
**                                               placeholder referencing all **
**                                               snapshot records            **
**                                               of the addressed DTC. The   **
**                                               value 0x00 indicates        **
**                                               the DTC-specific WWHOBD     **
**                                               snapshot record.            **
**                                                                           **
** InOut parameter      : None                                               **
**                                                                           **
** Output Parameters    : None                                               **
**                                                                           **
** Return parameter     : E_OK                 - Freeze frame data           **
**                                               successfully selected.      **
**                        DEM_WRONG_DTC        - Selected DTC value in       **
**                                               selected format             **
**                                               does not exist.             **
**                        DEM_WRONG_DTCORIGIN  - Selected DTCOrigin does     **
**                                               not exist.                  **
**                        DEM_PENDING          - Selecting the freeze frame  **
**                                               is currently in progress.   **
**                                               The caller shall call this  **
**                                               function again at a later   **
**                                               moment.                     **
**                        DEM_BUSY             - A different Dem_SelectDTC   **
**                                               dependent operation         **
**                                               according to SWS_Dem_01253  **
**                                               of this client is currently **
**                                               in progress.                **
**                                                                           **
** Preconditions        : The API Dem_PreInit(), Dem_Init()                  **
**                        should have been called in sequence                **
**                                                                           **
** Remarks              : Global Variable(s)     :                           **
**                        Dem_GucInit                                        **
**                        Dem_ClientSelectExtendedDataRecord                 **
**                        Dem_ClientSelectDtcState                           **
**                                                                           **
**                        Function(s) invoked    :                           **
**                        (void)Det_ReportError                              **
*******************************************************************************/
/* @Trace: SRS_Diag_04074
 */
#if (DEM_NUMBER_OF_DEM_CLIENT >= DEM_ZERO)
FUNC(Std_ReturnType, DEM_CODE) Dem_SelectFreezeFrameData(
    uint8 ClientId,
    uint8 RecordNumber)
{
  Std_ReturnType LddRetVal = E_OK;
  uint16 LusByteShift =
      ((uint16)DEM_ONE << DEM_SELECTDTC_SID_LOCK_IDX) |
      ((uint16)DEM_ONE << DEM_CLEARDTC_SID_LOCK_IDX) |
      ((uint16)DEM_ONE << DEM_DISABLEDTCRECORDUPDATE_SID_LOCK_IDX) |
      ((uint16)DEM_ONE << DEM_ENABLEDTCRECORDUPDATE_SID_LOCK_IDX) |
      ((uint16)DEM_ONE << DEM_GETDTCSELECTIONRESULT_SID_LOCK_IDX) |
      ((uint16)DEM_ONE << DEM_GETFUNCTIONALUNITOFDTC_SID_LOCK_IDX) |
      ((uint16)DEM_ONE << DEM_GETSEVERITYOFDTC_SID_LOCK_IDX) |
      ((uint16)DEM_ONE << DEM_GETSTATUSOFDTC_SID_LOCK_IDX) |
      ((uint16)DEM_ONE << DEM_SELECTFREEZEFRAMEDATA_SID_LOCK_IDX) |
      ((uint16)DEM_ONE << DEM_SELECTEXTENDEDDATARECORD_SID_LOCK_IDX) |
      ((uint16)DEM_ONE << DEM_SETDTCSUPPRESSION_SID_LOCK_IDX) |
      ((uint16)DEM_ONE << DEM_GETDTCSUPPRESSION_SID_LOCK_IDX);
  Std_ReturnType LucResult = Dem_CheckStatusOfSelectedDTCServices(
      ClientId,
      DEM_SELECTFREEZEFRAMEDATA_SID,
      LusByteShift);

  #if (DEM_NUMBER_OF_DEM_CLIENT > DEM_ZERO)
  if (ClientId >= DEM_NUMBER_OF_DEM_CLIENT)
  {
    /* @Trace: Dem_SUD_API_20561 */
    DEM_REPORT_ERROR(DEM_SELECTFREEZEFRAMEDATA_SID, DEM_E_WRONG_CONDITION);
    LddRetVal = E_NOT_OK;
  }
  else
  #endif
  if (E_OK != LucResult)
  {
    /* @Trace: Dem_SUD_API_20118 */
    LddRetVal = LucResult;
  }
  else
  {
    /* lock this client id */
    Dem_SelectedDTCServiceLock(ClientId,
        DEM_SELECTFREEZEFRAMEDATA_SID_LOCK_IDX);

    if (Dem_GucInit != DEM_INIT)
    {
      /* @Trace: Dem_SUD_API_20562 */
      DEM_REPORT_ERROR(DEM_SELECTFREEZEFRAMEDATA_SID, DEM_E_UNINIT);
      LddRetVal = E_NOT_OK;
    }
    else
    {
      /* @Trace: SWS_Dem_01268
       * If the API Dem_SelectFreezeFrameData is called, the Dem shall use the
       * DTC selected by Dem_SelectDTC and the RecordNumber as a target for the
       * following API calls:
       * - Dem_GetNextFreezeFrameData
       * - Dem_GetSizeOfFreezeFrameSelection
       */
      if (E_OK != Dem_ClientSelectDtcState[ClientId].resultSelectDTC)
      {
        /* @Trace: Dem_SUD_API_20564 */
        DEM_REPORT_ERROR(DEM_SELECTFREEZEFRAMEDATA_SID, DEM_E_WRONG_CONDITION);
        Dem_ClientSelectFreezeFrameData[ClientId].resultSelectFreezeFrameData =
             Dem_ClientSelectDtcState[ClientId].resultSelectDTC;
        LddRetVal = Dem_ClientSelectFreezeFrameData[
                       ClientId].resultSelectFreezeFrameData;
      }
      else
      {
        /* @Trace: Dem_SUD_API_20563 */
        Dem_ClientSelectFreezeFrameData[ClientId].selectRecordNumber =
            RecordNumber;
        Dem_ClientSelectFreezeFrameData[ClientId].resultSelectFreezeFrameData =
            E_OK;
      }
    }
    /* unlock this client id */
    Dem_SelectedDTCServiceUnLock(ClientId,
             DEM_SELECTFREEZEFRAMEDATA_SID_LOCK_IDX);
  }

  return LddRetVal;
}/* End the function*/
/******************************************************************************
** Function Name        : Dem_GetNextFreezeFrameData                         **
**                                                                           **
** Service ID           : 0x1d                                               **
**                                                                           **
** Description          : Gets freeze frame data by the DTC selected by      **
**                        Dem_SelectFreezeFrameData. The function stores     **
**                        the data in the provided DestBuffer.               **
**                                                                           **
** Sync/Async           : Asynchronous                                       **
**                                                                           **
** Re-entrancy          : Reentrant for different ClientIds, non reentrant   **
**                        for the same ClientId.                             **
**                                                                           **
** Input Parameters     : ClientId             - Unique client id, assigned  **
**                                               to the instance             **
**                                               of the calling module.      **
**                        BufSize              - When the function is called **
**                                               this parameter              **
**                                               contains the maximum number **
**                                               of data bytes               **
**                                               that can be written to the  **
**                                               buffer. The function returns**
**                                               the actual number of written**
**                                               data bytes in this parameter**
**                        DestBuffer           - This parameter contains a   **
**                                               byte pointer that           **
**                                               points to the buffer, to    **
**                                               which the freeze            **
**                                               frame data record shall be  **
**                                               written to. The format is:  **
**                                               {RecordNumber, NumOfDIDs,   **
**                                               DID[1],data[1],...,         **
**                                               DID[N], data[N]}            **
**                                                                           **
** InOut parameter      : None                                               **
**                                                                           **
** Output Parameters    : None                                               **
**                                                                           **
** Return parameter     : E_OK                 - Size and buffer successfully**
**                                               returned.                   **
**                        DEM_BUFFER_TOO_SMALL - provided buffer size        **
**                                               too small                   **
**                        DEM_PENDING          - The requested value is      **
**                                               calculated asynchronously   **
**                                               and currently not available.**
**                                               The caller can retry later. **
**                        DEM_WRONG_DTC        - DTC value not existing      **
**                        E_NOT_OK             - selection function is not   **
**                                               called.                     **
**                        DEM_WRONG_DTCORIGIN  - Wrong DTC origin            **
**                        DEM_NO_SUCH_ELEMENT  - Found no (further) element  **
**                                               matching the filter         **
**                                               criteria                    **
**                                                                           **
** Preconditions        : The API Dem_PreInit(), Dem_Init()                  **
**                        should have been called in sequence                **
**                                                                           **
** Remarks              : Global Variable(s)     :                           **
**                        Dem_GucInit                                        **
**                        Dem_ClientSelectExtendedDataRecord                 **
**                                                                           **
**                        Function(s) invoked    :                           **
**                        (void)Det_ReportError                              **
*******************************************************************************/
/* @Trace: SRS_BSW_00369 SRS_Diag_04010 SRS_Diag_04074
 */
FUNC(Std_ReturnType, DEM_CODE) Dem_GetNextFreezeFrameData(
  uint8 ClientId,
  P2VAR (uint8, AUTOMATIC, DEM_VAR) DestBuffer,
  P2VAR (uint16, AUTOMATIC, DEM_VAR) BufSize)
{
  /* @Trace: SWS_Dem_00071
   * The function Dem_GetNextFreezeFrameData shall copy the specific data
   * identifiers (DIDs) of the freezeframe record selected by the API
   * Dem_SelectFreezeFrameData for the specified ClientId to the destination
   * buffer provided by the DestBuffer parameter. The Dem shall transmit these
   * data as a complete record with the format shown in Figure 7.51.
   */
  Std_ReturnType LddRetVal = E_OK;

  if (DEM_INIT != Dem_GucInit)
  {
    /* @Trace: Dem_SUD_API_20526 */
    DEM_REPORT_ERROR(DEM_GETNEXTFREEZEFRAMEDATA_SID, DEM_E_UNINIT);
    LddRetVal = DEM_WRONG_DTC;
  }
  /* @Trace: Dem_SUD_API_20539 */
  #if (DEM_NUMBER_OF_DEM_CLIENT > DEM_ZERO)
  else if (ClientId >= DEM_NUMBER_OF_DEM_CLIENT)
  {
    /* @Trace: Dem_SUD_API_20540 */
    DEM_REPORT_ERROR(DEM_GETNEXTFREEZEFRAMEDATA_SID, DEM_E_WRONG_CONFIGURATION);
    LddRetVal = DEM_WRONG_DTC;
  }
  /* @Trace: Dem_SUD_API_20541 */
  #endif
  else if (E_OK !=
        Dem_ClientSelectFreezeFrameData[ClientId].resultSelectFreezeFrameData)
  {
    /* @Trace: Dem_SUD_API_20542 */
    /* @Trace: SWS_Dem_01270, SWS_Dem_01271
     * If any of the APIs requiring a Dem_SelectFreezeFrameData (see
     * [SWS_Dem_01268]) are called without a prior call to
     * Dem_SelectFreezeFrameData, the Dem shall report the Det error
     * DET_E_WRONG_CONDITION.
     * */
    DEM_REPORT_ERROR(DEM_GETNEXTFREEZEFRAMEDATA_SID, DEM_E_WRONG_CONDITION);
    /* @Trace: SWS_Dem_01269
     * The API Dem_SelectFreezeFrameData triggers the Dem internal Freeze Frame
     * selection process on the event memory assigned to the ClientId.
     * The Dem shall provide the result of the selection process
     * in the return value of the API calls following the
     * Dem_SelectFreezeFrameData call, see [SWS_Dem_01268].
     */
    LddRetVal = Dem_ClientSelectFreezeFrameData[
                  ClientId].resultSelectFreezeFrameData;
  }
  else if ((NULL_PTR == DestBuffer) || (NULL_PTR == BufSize))
  /* polyspace<RTE:UNR:Not a defect:No action planned> No error. Avoid to
   * 'Unreachable code' of the polyspace */
  {
    /* @Trace: Dem_SUD_API_20543 */
    DEM_REPORT_ERROR(DEM_GETNEXTFREEZEFRAMEDATA_SID, DEM_E_PARAM_POINTER);
    LddRetVal = DEM_WRONG_DTC;
  }
  else
  {
    /* The default value of result shall be
     * DEM_GET_READEVDATA_WRONG_RECORDNUMBER */
    Std_ReturnType LddResult = E_NOT_OK;
    Dem_EventIdType LddEventId = Dem_GetEventIdByDTC(
        DEM_GETNEXTFREEZEFRAMEDATA_SID,
        Dem_ClientSelectDtcState[ClientId].selectedDTC,
        Dem_ClientSelectDtcState[ClientId].selectedDTCFormat);
    /* @if (DEM_FALSE == Dem_EventIdIsValid(LddEventId)) */
    if ((LddEventId > DEM_NUMBER_OF_EVENTS) || (DEM_NO_EVENT == LddEventId))
    {
      /* @Trace: Dem_SUD_API_20527 */
      DEM_REPORT_ERROR(DEM_GETNEXTFREEZEFRAMEDATA_SID, DEM_E_PARAM_CONFIG);
      LddRetVal = DEM_WRONG_DTC;
    }
    else if ((boolean)DEM_FALSE == Dem_DTCOriginBelongToEvent(LddEventId,
        Dem_ClientSelectDtcState[ClientId].selectedDTCOrigin))
    {
      /* @Trace: Dem_SUD_API_20528 */
      DEM_REPORT_ERROR(DEM_GETNEXTFREEZEFRAMEDATA_SID, DEM_E_PARAM_CONFIG);
      /* No destination of the event configured */
      LddRetVal = DEM_WRONG_DTCORIGIN;
    }
    else
    #if (( DEM_MAX_EVENT_DESTINATION_SELECTED > DEM_ZERO) && \
         ( DEM_SIZE_OF_FREEZEFRAME > DEM_ZERO))
    {
      Dem_EventParameterPCType LddEvent = &Dem_Event[LddEventId - DEM_ONE];
      /* @Trace: Dem_SUD_API_20530 */
      if ( LddEvent->e_PointToData < DEM_NUM_OF_EVENTRELATEDDATA)
      {
	  	#if (DEM_J1979_2_OBD_ON_UDS == STD_ON)
        uint8 protocolId = 0x00u;
		#endif
        /* [Dem236] range : 1 ~ 254 (0xFE) */
        switch( Dem_ClientSelectFreezeFrameData[ClientId].selectRecordNumber )
        {
        /***************************************************************
         * The value 0x00 indicates the DTC-specific OBD freeze frame. *
         ***************************************************************/
        /* @Trace: SWS_Dem_00576
         * If the RecordNumber selected by the API Dem_SelectFreezeFrameData
         * is set to 0x00, Dem_GetNextFreezeFrameData shall provide the event
         * /DTC specific WWH-OBD equivalent freeze frame record.
         */
        case DEM_OBD_RECORD_NUMBER:
         #if (DEM_J1979_2_OBD_ON_UDS == STD_ON)
         (void) Dcm_GetObdProtocolId(&protocolId);
         if(protocolId == DEM_PROTOCOLID_J1979_2_OBD_ON_UDS)
         {
            LddResult = Dem_ReadDataOfFreezeFrame(
            &Dem_EventRelatedData[LddEvent->e_PointToData],
            Dem_ClientSelectDtcState[ClientId].selectedDTCOrigin,
            Dem_ClientSelectFreezeFrameData[ClientId].selectRecordNumber,
            DEM_DATAID_IGNORED,
            DEM_FFFORMAT_TYPE_HDR_REC,
            DestBuffer,
            BufSize);
          break;
         }
         else
		 #endif
         {
            #if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
            /* @IF_REQ : permanent memory ?*/
            /* @Trace: Dem_SUD_API_20114 */
            LddResult = Dem_GetOBDFreezeFrameData(LddEvent,
                Dem_ClientSelectDtcState[ClientId].selectedDTCOrigin,
                DestBuffer,BufSize);
            #else
            /* @Trace: Dem_SUD_API_20534 */
            /* LddResult = DEM_GET_READEVDATA_WRONG_RECORDNUMBER; */
            #endif
         }         
          break;

        /***************************************************************
         * The value 0xFF is not allowed.                              *
         ***************************************************************/
        case DEM_MAX_RECORD:
        /* @Trace: Dem_SUD_API_20115 */
          /* LddResult = DEM_GET_READEVDATA_WRONG_RECORDNUMBER; */
          break;

        /***************************************************************
         * This record number is unique per DTC (relative addressing). *
         ***************************************************************/
        default:
        /* @Trace: Dem_SUD_API_20531 */
          LddResult = Dem_ReadDataOfFreezeFrame(
            &Dem_EventRelatedData[LddEvent->e_PointToData],
            Dem_ClientSelectDtcState[ClientId].selectedDTCOrigin,
            Dem_ClientSelectFreezeFrameData[ClientId].selectRecordNumber,
            DEM_DATAID_IGNORED,
            DEM_FFFORMAT_TYPE_HDR_REC,
            DestBuffer,
            BufSize);
          break;
        }
      }
    }
    #else
    {
      /* @Trace: Dem_SUD_API_20529 */
      DEM_UNUSED_PTR(BufSize);
      DEM_UNUSED_PTR(DestBuffer);
    }
    #endif
    
    /* @Trace: Dem_SUD_API_20532 */
    if (E_OK == LddRetVal)
    {
      switch(LddResult)
      {
        case DEM_GET_READEVDATA_OK:
          /* *BufSize is updated in the Dem_ReadDataOfFreezeFrame */
          /* @Trace: Dem_SUD_API_20533 */
          LddRetVal = E_OK;
          break;
          /* @Trace: SWS_Dem_00630
           * If a single DTC is selected and the API Dem_SelectFreezeFrameData
           * is called with a valid RecordNumber which is not stored,
           * Dem_GetNextFreezeFrameDatashall return E_OK and BufSize 0
           * (empty buffer).
           */
        case DEM_GET_READEVDATA_NOT_STORED:
          if (E_OK != Dem_DTCGroupIsValid(
              Dem_ClientSelectDtcState[ClientId].selectedDTC,
              Dem_ClientSelectDtcState[ClientId].selectedDTCFormat))
          {
            /* @Trace: Dem_SUD_API_20535 */
            *BufSize = DEM_ZERO;
            LddRetVal = E_OK;
          }
          else
          {
            /* @Trace: Dem_SUD_API_20536 */
            LddRetVal = DEM_WRONG_DTC;
          }
          break;
        case DEM_GET_READEVDATA_WRONG_RECORDNUMBER:
          /* DEM_REPORT_ERROR(DEM_GETNEXTFREEZEFRAMEDATA_SID,
           * DEM_E_PARAM_CONFIG); */
          /* @Trace: Dem_SUD_API_20537 */
          LddRetVal = DEM_NO_SUCH_ELEMENT;
          break;
        case DEM_GET_READEVDATA_WRONG_BUFFERSIZE:
        /* @Trace: Dem_SUD_API_20538 */
          DEM_REPORT_ERROR(DEM_GETNEXTFREEZEFRAMEDATA_SID, DEM_E_PARAM_LENGTH);
          LddRetVal = DEM_BUFFER_TOO_SMALL;
          break;
        /* polyspace<RTE:UNR:Not a defect:No action planned> No problem.
         * Unreachable code */
        default:
        /* @Trace: Dem_SUD_API_20116 */
          LddRetVal = DEM_WRONG_DTC;
          break;
      }
    }
  }
  return LddRetVal;
}/* End Of API */
/*******************************************************************************
** Function Name        : Dem_GetSizeOfFreezeFrameSelection                  **
**                                                                           **
** Service ID           : 0x1f                                               **
**                                                                           **
** Description          : Gets the size of freeze frame data by DTC selected **
**                        by the call of Dem_SelectFreezeFrameData.          **
**                                                                           **
** Sync/Async           : Asynchronous                                       **
**                                                                           **
** Re-entrancy          : Reentrant for different ClientIds, non reentrant   **
**                        for the same ClientId.                             **
**                                                                           **
** Input Parameters     : ClientId             - Unique client id, assigned  **
**                                               to the instance of the      **
**                                               calling module.             **
**                                                                           **
** InOut parameter      : None                                               **
**                                                                           **
** Output Parameters    : SizeOfFreezeFrame    - Number of bytes in the      **
**                                               requested freeze frame      **
**                                               record.                     **
**                                                                           **
** Return parameter     : E_OK                 - Size returned successfully  **
**                        E_NOT_OK             - selection function is not   **
**                                               called.                     **
**                        DEM_PENDING          - The requested value is      **
**                                               calculated asynchronously   **
**                                               and currently not available.**
**                                               The caller can retry later. **
**                        DEM_WRONG_DTC        - DTC value not existing      **
**                        DEM_WRONG_DTCORIGIN  - Wrong DTC origin            **
**                        DEM_NO_SUCH_ELEMENT  - Record number is not        **
**                                               supported by configuration  **
**                                               and therefore invalid       **
**                                                                           **
** Preconditions        : The API Dem_PreInit(), Dem_Init()                  **
**                        should have been called in sequence                **
**                                                                           **
** Remarks              : Global Variable(s)     :                           **
**                        Dem_GucInit                                        **
**                        Dem_ClientSelectExtendedDataRecord                 **
**                                                                           **
**                        Function(s) invoked    :                           **
**                        (void)Det_ReportError                              **
*******************************************************************************/
/* @Trace: SRS_BSW_00369 SRS_Diag_04010 SRS_Diag_04204
 */
FUNC(Std_ReturnType, DEM_CODE) Dem_GetSizeOfFreezeFrameSelection(
  uint8 ClientId,
  P2VAR (uint16, AUTOMATIC, DEM_VAR) SizeOfFreezeFrame)
{
  /* @Trace: SWS_Dem_00074
   * The function Dem_GetSizeOfFreezeFrameSelection shall return the size of
   * the requested freeze frame record(s) by Dem_SelectFreezeFrameData for the
   * specified ClientId, which represents the number of user data bytes,
   * including any freeze frame headerinformation (according to the format
   * defined in [SWS_Dem_00071]).
   */
  Std_ReturnType LddRetVal = DEM_WRONG_DTC;

  if (DEM_INIT != Dem_GucInit)
  {
    /* @Trace: Dem_SUD_API_20489 */
    DEM_REPORT_ERROR(DEM_GETSIZEOFFREEZEFRAMESELECTION_SID, DEM_E_UNINIT);
    /* @LddRetVal = DEM_WRONG_DTC; */
  }
  else if (NULL_PTR == SizeOfFreezeFrame)
  {
    /* @Trace: Dem_SUD_API_20494 */
    DEM_REPORT_ERROR(DEM_GETSIZEOFFREEZEFRAMESELECTION_SID,
        DEM_E_PARAM_POINTER);
    /* @LddRetVal = DEM_WRONG_DTC; */
  }
  /* @Trace: Dem_SUD_API_20496 */
  #if (DEM_NUMBER_OF_DEM_CLIENT > DEM_ZERO)
  else if (ClientId >= DEM_NUMBER_OF_DEM_CLIENT)
  {
      /* @Trace: Dem_SUD_API_20495 */
      DEM_REPORT_ERROR(DEM_GETSIZEOFFREEZEFRAMESELECTION_SID,
          DEM_E_WRONG_CONFIGURATION);
      /* @LddRetVal = DEM_WRONG_DTC; */
  }
  /* @Trace: Dem_SUD_API_20497 */
  else if (DEM_DTC_ORIGIN_PRIMARY_MEMORY !=
      Dem_ClientSelectDtcState[ClientId].selectedDTCOrigin)
  {
    /* @Trace: Dem_SUD_API_20498 */
    DEM_REPORT_ERROR(DEM_GETSIZEOFFREEZEFRAMESELECTION_SID,
        DEM_E_PARAM_CONFIG);
    LddRetVal = DEM_WRONG_DTCORIGIN;
  }
  #endif
  else if (E_OK != Dem_ClientSelectFreezeFrameData[
                         ClientId].resultSelectFreezeFrameData)
  {
      /* @Trace: Dem_SUD_API_20499 */
      /* @Trace: SWS_Dem_01270, SWS_Dem_01271
       * If any of the APIs requiring a Dem_SelectFreezeFrameData (see
       * [SWS_Dem_01268]) are called without a prior call to
       * Dem_SelectFreezeFrameData, the Dem shall report the Det error
       * DET_E_WRONG_CONDITION.
       * */
      DEM_REPORT_ERROR(DEM_GETSIZEOFFREEZEFRAMESELECTION_SID,
          DEM_E_WRONG_CONDITION);
      /* @Trace: SWS_Dem_01269
       * The API Dem_SelectFreezeFrameData triggers the Dem internal Freeze
       * Frame selection process on the event memory assigned to the ClientId.
       * The Dem shall provide the result of the selection process in the
       * return value of the API calls following the Dem_SelectFreezeFrameData
       * call, see [SWS_Dem_01268].
       */
      LddRetVal = Dem_ClientSelectFreezeFrameData[
                       ClientId].resultSelectFreezeFrameData;
  }
  else
  {
    Dem_EventIdType LddEventId = Dem_GetEventIdByDTC(
        DEM_GETSIZEOFFREEZEFRAMESELECTION_SID,
        Dem_ClientSelectDtcState[ClientId].selectedDTC,
        Dem_ClientSelectDtcState[ClientId].selectedDTCFormat);
    /* @if (DEM_FALSE == Dem_EventIdIsValid(LddEventId)) */
    if ((LddEventId > DEM_NUMBER_OF_EVENTS) || (DEM_NO_EVENT == LddEventId))
    {
      /* @Trace: Dem_SUD_API_20490 */
      DEM_REPORT_ERROR(DEM_GETSIZEOFFREEZEFRAMESELECTION_SID,
          DEM_E_PARAM_CONFIG);
      LddRetVal = DEM_WRONG_DTC;
    }
    else if ((boolean)DEM_FALSE == Dem_DTCOriginBelongToEvent(LddEventId,
        Dem_ClientSelectDtcState[ClientId].selectedDTCOrigin))
    {
      /* @Trace: Dem_SUD_API_20110 */
      DEM_REPORT_ERROR(DEM_GETSIZEOFFREEZEFRAMESELECTION_SID,
          DEM_E_PARAM_CONFIG);
      /* No destination of the event configured */
      LddRetVal = DEM_WRONG_DTCORIGIN;
    }
    else
    {
      /* @Trace: Dem_SUD_API_20491 */
      #if ((DEM_MAX_EVENT_DESTINATION_SELECTED > DEM_ZERO) && \
           (DEM_SIZE_OF_FREEZEFRAME > DEM_ZERO))
      uint16 LusFreezeFrameSize = DEM_ZERO;
      /* NOTE : Why DEM_DTC_ORIGIN_PERMANENT_MEMORY  is not
       * checked in the AUTOEVER source? */
      if (E_OK == Dem_GetSizeOfFreezeFrameByRecord(
          LddEventId,
          Dem_ClientSelectFreezeFrameData[ClientId].selectRecordNumber,
          Dem_ClientSelectDtcState[ClientId].selectedDTCOrigin,
          &LusFreezeFrameSize))
      {
        /* @Trace: Dem_SUD_API_20493 */
        *SizeOfFreezeFrame = LusFreezeFrameSize;
        /* DEM_ZERO(not stored) or valid size*/
        LddRetVal = E_OK;
      }
      else
      #endif
      {
        /* @Trace: Dem_SUD_API_20492 */
        DEM_REPORT_ERROR(DEM_GETSIZEOFFREEZEFRAMESELECTION_SID,
            DEM_E_PARAM_CONFIG);
        LddRetVal = DEM_NO_SUCH_ELEMENT;
      }
    }
  }
  return LddRetVal;
}

/*******************************************************************************
** Function Name        : Dem_SelectExtendedDataRecord                        **
**                                                                            **
** Service ID           : 0xba                                                **
**                                                                            **
** Description          : Sets the filter to be used by                       **
**                        Dem_GetNextExtendedDataRecord and                   **
**                        Dem_GetSizeOfExtendedDataRecordSelection.           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant for different ClientIds, non reentrant    **
**                        for the same ClientId.                              **
**                                                                            **
** Input Parameters     : ClientId             - Unique client id, assigned   **
**                                               to the instance              **
**                                               of the calling module.       **
**                        ExtendedDataNumber   - Identification/Number of     **
**                                               requested extended data      **
**                                               record. Additionally the     **
**                                               values 0xFE and 0xFF are     **
**                                               explicitly allowed to request**
**                                               the overall size of all OBD  **
**                                               records / all records.       **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : E_OK                 - Extended data record         **
**                                               successfully selected.       **
**                        DEM_WRONG_DTC        - Selected DTC value in        **
**                                               selected format              **
**                                               does not exist.              **
**                        DEM_WRONG_DTCORIGIN  - Selected DTCOrigin does not  **
**                                               exist.                       **
**                        DEM_PENDING          - Selecting the freeze frame   **
**                                               is currently                 **
**                                               in progress. The caller      **
**                                               shall call this              **
**                                               function again at a later    **
**                                               moment.                      **
**                        DEM_BUSY             - A different Dem_SelectDTC    **
**                                               dependent operation according**
**                                               to SWS_Dem_01253 of this     **
**                                               client is currently in       **
**                                               progress.                    **
**                                                                            **
** Preconditions        : The API Dem_PreInit(), Dem_Init()                   **
**                        should have been called in sequence                 **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Dem_GucInit                                         **
**                        Dem_ClientSelectExtendedDataRecord                  **
**                        Dem_ClientSelectDtcState                            **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        (void)Det_ReportError                               **
*******************************************************************************/
/* @Trace: SRS_Diag_04074
 */
FUNC(Std_ReturnType, DEM_CODE) Dem_SelectExtendedDataRecord(
  uint8 ClientId,
  uint8 ExtendedDataNumber)
{
  Std_ReturnType LddRetVal = E_OK;
  uint16 LusByteShift =
      ((uint16)DEM_ONE << DEM_SELECTDTC_SID_LOCK_IDX) |
      ((uint16)DEM_ONE << DEM_CLEARDTC_SID_LOCK_IDX) |
      ((uint16)DEM_ONE << DEM_DISABLEDTCRECORDUPDATE_SID_LOCK_IDX) |
      ((uint16)DEM_ONE << DEM_ENABLEDTCRECORDUPDATE_SID_LOCK_IDX) |
      ((uint16)DEM_ONE << DEM_GETDTCSELECTIONRESULT_SID_LOCK_IDX) |
      ((uint16)DEM_ONE << DEM_GETFUNCTIONALUNITOFDTC_SID_LOCK_IDX) |
      ((uint16)DEM_ONE << DEM_GETSEVERITYOFDTC_SID_LOCK_IDX) |
      ((uint16)DEM_ONE << DEM_GETSTATUSOFDTC_SID_LOCK_IDX) |
      ((uint16)DEM_ONE << DEM_SELECTFREEZEFRAMEDATA_SID_LOCK_IDX) |
      ((uint16)DEM_ONE << DEM_SELECTEXTENDEDDATARECORD_SID_LOCK_IDX) |
      ((uint16)DEM_ONE << DEM_SETDTCSUPPRESSION_SID_LOCK_IDX) |
      ((uint16)DEM_ONE << DEM_GETDTCSUPPRESSION_SID_LOCK_IDX);
  Std_ReturnType LucResult = Dem_CheckStatusOfSelectedDTCServices(
      ClientId,
      DEM_SELECTEXTENDEDDATARECORD_SID,
      LusByteShift);

  #if (DEM_NUMBER_OF_DEM_CLIENT > DEM_ZERO)
  if (ClientId >= DEM_NUMBER_OF_DEM_CLIENT)
  {
    /* @Trace: Dem_SUD_API_20553 */
    DEM_REPORT_ERROR(DEM_SELECTEXTENDEDDATARECORD_SID, DEM_E_WRONG_CONDITION);
    LddRetVal = E_NOT_OK;
  }
  else
  #endif
  if (E_OK != LucResult)
  {
    /* @Trace: Dem_SUD_API_20117 */
    LddRetVal = LucResult;
  }
  else
  {
    /* lock this client id */
    Dem_SelectedDTCServiceLock(ClientId,
                DEM_SELECTEXTENDEDDATARECORD_SID_LOCK_IDX);

    if (Dem_GucInit != DEM_INIT)
    {
      /* @Trace: Dem_SUD_API_20554 */
      DEM_REPORT_ERROR(DEM_SELECTEXTENDEDDATARECORD_SID, DEM_E_UNINIT);
      LddRetVal = E_NOT_OK;
    }
    else
    {
      /* @Trace: SWS_Dem_01272
       * If the API Dem_SelectExtendedDataRecord is called, the Dem shall use
       * the DTC selected by Dem_SelectDTC and the ExtendedDataNumber as a
       * target for the following API calls:
       * - Dem_GetNextExtendedDataRecord
       * - Dem_GetSizeOfExtendedDataRecordSelection
       */
      if (E_OK != Dem_ClientSelectDtcState[ClientId].resultSelectDTC)
      {
        /* @Trace: Dem_SUD_API_20555 */
        DEM_REPORT_ERROR(DEM_SELECTEXTENDEDDATARECORD_SID,
            DEM_E_WRONG_CONDITION);

        Dem_ClientSelectExtendedDataRecord[
             ClientId].resultSelectExtendedDataRecord =
             Dem_ClientSelectDtcState[ClientId].resultSelectDTC;
        LddRetVal = Dem_ClientSelectExtendedDataRecord[
                ClientId].resultSelectExtendedDataRecord;
      }
      else
      {
        Dem_EventIdType LddEventId = Dem_GetEventIdByDTC(
            DEM_SELECTEXTENDEDDATARECORD_SID,
            Dem_ClientSelectDtcState[ClientId].selectedDTC,
            Dem_ClientSelectDtcState[ClientId].selectedDTCFormat);

        if ((LddEventId > DEM_NUMBER_OF_EVENTS) || (DEM_NO_EVENT == LddEventId))
        {
          /* @Trace: Dem_SUD_API_20500 */
          DEM_REPORT_ERROR(DEM_SELECTEXTENDEDDATARECORD_SID, DEM_E_PARAM_CONFIG);
          /* @Trace: SWS_Dem_91017
          Selected DTC value in selected format does not exist. 
          */
          LddRetVal = DEM_WRONG_DTC;
        }
        else if ((boolean)DEM_FALSE == Dem_DTCOriginBelongToEvent(LddEventId,
                  Dem_ClientSelectDtcState[ClientId].selectedDTCOrigin))
        {
          /* @Trace: Dem_SUD_API_20501 */
          DEM_REPORT_ERROR(DEM_SELECTEXTENDEDDATARECORD_SID, DEM_E_PARAM_CONFIG);
          /* @Trace: SWS_Dem_91017
          No destination of the event configured.
          */
          LddRetVal = DEM_WRONG_DTCORIGIN;
        }
        else
        {
          #if ((DEM_MAX_EVENT_DESTINATION_SELECTED > DEM_ZERO) && \
               (DEM_SIZE_OF_EXTENDED_DATA > DEM_ZERO))
          Dem_EventParameterPCType LddEvent = &Dem_Event[LddEventId - DEM_ONE];
          
          if (LddEvent->e_PointToData < DEM_NUM_OF_EVENTRELATEDDATA)
          {
            /* @Trace: Dem_SUD_API_20556 */

            Dem_EventRelatedDataPCType LddEvData;
            Dem_ExtendedDataClassPCType LddExtendedData;
            
            LddEvData = &Dem_EventRelatedData[LddEvent->e_PointToData];
            LddExtendedData = &Dem_ExtendedDataClass[LddEvData->EDClassPos];

            Dem_ClientSelectExtendedDataRecord[ClientId].
              nextPointToEDRecordMap = LddExtendedData->PointToEDRecordMap;
            Dem_ClientSelectExtendedDataRecord[ClientId].
              maxNumOfEDRecordClass = 
                LddExtendedData->PointToEDRecordMap +
                LddExtendedData->NumOfEDRecordClass;

            Dem_ClientSelectExtendedDataRecord[ClientId].
                     selectExtendedDataNumber = ExtendedDataNumber;
            Dem_ClientSelectExtendedDataRecord[ClientId].
                     resultSelectExtendedDataRecord = E_OK;
          }
          else
          {
            /* @Trace: Dem_SUD_API_20502 */
            /* FIXME
             * The requested Record number is not configured
             * No return value is defined in the specification.*/
            LddRetVal = E_NOT_OK;
          }
          #endif
        }
      }
    }
    /* unlock this client id */
    Dem_SelectedDTCServiceUnLock(ClientId,
        DEM_SELECTEXTENDEDDATARECORD_SID_LOCK_IDX);
  }

  return LddRetVal;
}/* End the function*/

/*******************************************************************************
** Function Name        : Dem_GetNextExtendedDataRecord                       **
**                                                                            **
** Service ID           : 0x20                                                **
**                                                                            **
** Description          : Gets extended data record for the DTC selected by   **
**                        Dem_SelectExtendedDataRecord. The function stores   **
**                        the data in the provided DestBuffer.                **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Reentrant for different ClientIds, non reentrant    **
**                        for the same ClientId.                              **
**                                                                            **
** Input Parameters     : Client               - Unique client id, assigned   **
**                                               to the instance of the       **
**                                               calling module.              **
**                        BufSize              - When the function is called  **
**                                               this parameter contains the  **
**                                               maximum number of data bytes **
**                                               that can be written to the   **
**                                               buffer. The function returns **
**                                               the actual number of written **
**                                               data bytes in this parameter.**
**                        DestBuffer           - This parameter contains a    **
**                                               byte pointer that points to  **
**                                               the buffer, to which the     **
**                                               extended data record shall be**
**                                               written to. The format is:   **
**                                               {ExtendedDataRecord-Number,  **
**                                               data[0], data[1], ...,       **
**                                               data[n]}                     **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : E_OK                 - Size and buffer successfully **
**                                               returned.                    **
**                        DEM_BUFFER_TOO_SMALL - provided buffer size too     **
**                                               small                        **
**                        DEM_PENDING          - The requested value is       **
**                                               calculated asynchronously and**
**                                               currently not available.     **
**                                               The caller can retry later.  **
**                        DEM_WRONG_DTC        - DTC value not existing       **
**                        E_NOT_OK             - selection function is not    **
**                                               called.                      **
**                        DEM_WRONG_DTCORIGIN  - Wrong DTC origin             **
**                        DEM_NO_SUCH_ELEMENT  - Found no (further) element   **
**                                               matching the filter criteria **
**                                                                            **
** Preconditions        : The API Dem_PreInit(), Dem_Init()                   **
**                        should have been called in sequence                 **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Dem_GucInit                                         **
**                        Dem_ClientSelectExtendedDataRecord                  **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        (void)Det_ReportError                               **
*******************************************************************************/
/* @Trace: SRS_BSW_00369 SRS_Diag_04010 SRS_Diag_04074
 */
FUNC(Std_ReturnType, DEM_CODE)
Dem_GetNextExtendedDataRecord(
  uint8 ClientId,
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA) DestBuffer,
  P2VAR(uint16, AUTOMATIC, DEM_APPL_DATA) BufSize)
{
  /* @Trace: SWS_Dem_00075
   * The API Dem_GetNextExtendedDataRecord shall copy the complete data of the
   * requested extended data record by Dem_SelectExtendedDataRecord API for the
   * specified ClientId to the destination buffer (DestBuffer). The function
   * shall transmit these data as a complete record with the format shown in
   * figure 7.52. The extended data record number is placed as the first byte
   * in the copied data.
   */
  Std_ReturnType LddRetVal = DEM_WRONG_DTC;

  if (DEM_INIT != Dem_GucInit)
  {
    /* @Trace: Dem_SUD_API_20505 */
    DEM_REPORT_ERROR(DEM_GETNEXTEXTENDEDDATARECORD_SID, DEM_E_UNINIT);
    /*@LddRetVal = DEM_WRONG_DTC;*/
  }
  /* @Trace: Dem_SUD_API_20512 */
  #if (DEM_NUMBER_OF_DEM_CLIENT > DEM_ZERO)
  /* @Trace: Dem_SUD_API_20515 */
  else if (ClientId >= DEM_NUMBER_OF_DEM_CLIENT)
  {
    /* @Trace: Dem_SUD_API_20514 */
    DEM_REPORT_ERROR(DEM_GETNEXTEXTENDEDDATARECORD_SID,
        DEM_E_WRONG_CONFIGURATION);
    /* @LddRetVal = DEM_WRONG_DTC; */
  }
  #endif
  else if (E_OK != Dem_ClientSelectExtendedDataRecord[ClientId].
                      resultSelectExtendedDataRecord)
  {
   /* @Trace: Dem_SUD_API_20516 */
   /* @Trace: SWS_Dem_01274
    * If any of the APIs requiring a Dem_SelectExtendedDataRecord (see
    * [SWS_Dem_01272]) are called without a prior call to
    * Dem_SelectExtendedDataRecord, the Dem shall report the Det error
    * DEM_E_WRONG_CONDITION.
    * */
   DEM_REPORT_ERROR(DEM_GETNEXTEXTENDEDDATARECORD_SID, DEM_E_WRONG_CONDITION);
   /* @Trace: SWS_Dem_01273
    * The API Dem_SelectExtendedDataRecord triggers the Dem internal extended
    * data record selection process on the event memory assigned to the
    * ClientId. The Dem shall provide the result of the selection process
    * in the return value of the API calls following the
    * Dem_SelectExtendedDataRecord, see [SWS_Dem_01272].
    */
   LddRetVal = Dem_ClientSelectExtendedDataRecord[ClientId].
         resultSelectExtendedDataRecord;
  }
  else if ((NULL_PTR == DestBuffer) || (NULL_PTR == BufSize))
  {
    /* @Trace: Dem_SUD_API_20517 */
    DEM_REPORT_ERROR(DEM_GETNEXTEXTENDEDDATARECORD_SID, DEM_E_PARAM_POINTER);
    /*@LddRetVal = DEM_WRONG_DTC;*/
  }
  else
  {
    Dem_EventIdType LddEventId = Dem_GetEventIdByDTC(
        DEM_GETNEXTEXTENDEDDATARECORD_SID,
        Dem_ClientSelectDtcState[ClientId].selectedDTC,
        Dem_ClientSelectDtcState[ClientId].selectedDTCFormat);
    /* @if (DEM_FALSE == Dem_EventIdIsValid(LddEventId)) */
    if ((LddEventId > DEM_NUMBER_OF_EVENTS) || (DEM_NO_EVENT == LddEventId))
    {
      /* @Trace: Dem_SUD_API_20112 */
      DEM_REPORT_ERROR(DEM_GETNEXTEXTENDEDDATARECORD_SID, DEM_E_PARAM_CONFIG);
      LddRetVal = DEM_WRONG_DTC;
    }
    else if ((boolean)DEM_FALSE == Dem_DTCOriginBelongToEvent(LddEventId,
              Dem_ClientSelectDtcState[ClientId].selectedDTCOrigin))
    {
      /* @Trace: Dem_SUD_API_20506 */
      DEM_REPORT_ERROR(DEM_GETNEXTEXTENDEDDATARECORD_SID, DEM_E_PARAM_CONFIG);
      /* No destination of the event configured */
      LddRetVal = DEM_WRONG_DTCORIGIN;
    }
    else
    {
      #if (( DEM_MAX_EVENT_DESTINATION_SELECTED > DEM_ZERO) && \
           ( DEM_SIZE_OF_EXTENDED_DATA > DEM_ZERO))
      Dem_EventParameterPCType LddEvent = &Dem_Event[LddEventId - DEM_ONE];
      
      /* @Trace: Dem_SUD_API_20508 */
      if (LddEvent->e_PointToData < DEM_NUM_OF_EVENTRELATEDDATA)
      {
        Dem_ReturnReadEventDataType LddResult = DEM_GET_READEVDATA_WRONG_RECORDNUMBER;
        Dem_NumOfExtendedDataRecordClassType *pointToMap;
        Dem_ExtendedDataNumberType RecordNumber = 0U;
        
        pointToMap = &Dem_ClientSelectExtendedDataRecord[ClientId].nextPointToEDRecordMap;

        /* If this condition is not justified, LddResult will be DEM_GET_READEVDATA_WRONG_RECORDNUMBER 
           and LddRetVal will be DEM_NO_SUCH_ELEMENT.
        */
        if (*pointToMap < Dem_ClientSelectExtendedDataRecord[ClientId].maxNumOfEDRecordClass)
        {
          if(Dem_ClientSelectExtendedDataRecord[ClientId].selectExtendedDataNumber == DEM_MAX_EXTENDED_RECORD_NUMBER)
          {
            RecordNumber = 
              Dem_ExtendedDataRecordClass[Dem_ListOfEDRecordClassIndex[*pointToMap]].ExtendedDataRecordNumber;
          }
          else
          {
            RecordNumber = Dem_ClientSelectExtendedDataRecord[ClientId].selectExtendedDataNumber;
          }

          LddResult = Dem_ReadDataOfExtendedData(
            &Dem_EventRelatedData[LddEvent->e_PointToData],
            Dem_ClientSelectDtcState[ClientId].selectedDTCOrigin,
            RecordNumber,
            &DestBuffer[DEM_ONE],
            BufSize);
        }
        switch(LddResult)
        {
          case DEM_GET_READEVDATA_OK:
            /* @Trace: Dem_SUD_API_20509 */
            /* Prepare the next extended data record by increasing the value by 1 */
            (*pointToMap)++;

            /* *BufSize is updated in the Dem_ReadDataOfFreezeFrame */
            DestBuffer[DEM_ZERO] = RecordNumber;
        	  *BufSize += DEM_ONE;
            LddRetVal = E_OK;
            break;
          case DEM_GET_READEVDATA_NOT_STORED:
            /* @Trace: Dem_SUD_API_20510 */
            /* @Trace: SWS_Dem_00631
             * If the API Dem_SelectExtendedDataRecord is called with a valid
             * DTC and a valid extended data record number which is not stored,
             * the API shall return E_OK and Dem_GetNextExtendedDataRecord
             * shall return BufSize 0 (empty buffer). */
            *BufSize = DEM_ZERO;
            LddRetVal = E_OK;
            break;
          case DEM_GET_READEVDATA_WRONG_RECORDNUMBER:
            /* @Trace: Dem_SUD_API_20511 */
            /* DEM_REPORT_ERROR(DEM_GETNEXTEXTENDEDDATARECORD_SID,
             * DEM_E_PARAM_CONFIG); */
            /*No record number configured */
            LddRetVal = DEM_NO_SUCH_ELEMENT;
            break;
          /* polyspace<RTE:UNR:Not a defect:No action planned> No problem.
           * Unreachable code */
          case DEM_GET_READEVDATA_WRONG_BUFFERSIZE:
            /* @Trace: Dem_SUD_API_20513 */
            DEM_REPORT_ERROR(DEM_GETNEXTEXTENDEDDATARECORD_SID,
                DEM_E_PARAM_LENGTH);
            LddRetVal = DEM_BUFFER_TOO_SMALL;
            break;
          /* polyspace<RTE:UNR:Not a defect:No action planned> No problem.
           * Unreachable code */
          default:
            /* @Trace: Dem_SUD_API_20113 */
            LddRetVal = DEM_NO_SUCH_ELEMENT;
            break;
        }
      }
      #else
      /* @Trace: Dem_SUD_API_20507 */
      LddRetVal = DEM_NO_SUCH_ELEMENT; /* No extended data configured */
      #endif
    }
  }
  return LddRetVal;
}
/*******************************************************************************
** Function Name        : Dem_GetSizeOfExtendedDataRecordSelection            **
**                                                                            **
** Service ID           : 0x21                                                **
**                                                                            **
** Description          : Gets the size of Extended Data Record by DTC        **
**                        selected by the call of                             **
**                        Dem_SelectExtendedDataRecord.                       **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Reentrant for different ClientIds, non reentrant    **
**                        for the same ClientId.                              **
**                                                                            **
** Input Parameters     : ClientId                  - Unique client id,       **
**                                                    assigned to the instance**
**                                                    of the calling module.  **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : SizeOfExtendedDataRecord  - Size of the requested   **
**                                                    extended data           **
**                                                    record(s) including     **
**                                                    record number.          **
**                                                    The format for a single **
**                                                    ExtendedDataRecord      **
**                                                    is: {RecordNumber,      **
**                                                    data[1], ...,data[N]}   **
**                                                                            **
** Return parameter     : E_OK                      - Size returned           **
**                                                    successfully            **
**                        E_NOT_OK                  - selection function is   **
**                                                    not called.             **
**                        DEM_PENDING               - The requested value is  **
**                                                    calculated              **
**                                                    asynchronously and      **
**                                                    currently not           **
**                                                    available.The caller    **
**                                                    can retry later.        **
**                        DEM_WRONG_DTC             - DTC value not existing  **
**                        DEM_WRONG_DTCORIGIN       - Wrong DTC origin        **
**                        DEM_NO_SUCH_ELEMENT       - Found no (further)      **
**                                                    element matching the    **
**                                                    filter criteria         **
**                                                                            **
** Preconditions        : The API Dem_PreInit(), Dem_Init()                   **
**                        should have been called in sequence                 **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Dem_GucInit                                         **
**                        Dem_ClientSelectExtendedDataRecord                  **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        (void)Det_ReportError                               **
********************************************************************************/
/* polyspace:begin<MISRA-C:5.1:Not a defect:Justify with annotations> This
 * Identifier is Specification. */

/* @Trace: SRS_BSW_00369 SRS_Diag_04010
 */
/* polyspace +2 CODE-METRICS:LEVEL [Not a defect:Low] "Not a defect" */
FUNC(Std_ReturnType, DEM_CODE)
Dem_GetSizeOfExtendedDataRecordSelection(
  uint8 ClientId,
  P2VAR(uint16, AUTOMATIC, DEM_APPL_DATA) SizeOfExtendedDataRecord)
{
  Std_ReturnType LddRetVal = DEM_WRONG_DTC;

  /* Check module Initialization */
  if (DEM_INIT != Dem_GucInit)
  {
    /* @Trace: Dem_SUD_API_20470 */
    DEM_REPORT_ERROR(DEM_GETSIZEOFEXTENDEDDATARECORDSELECTION_SID,
        DEM_E_UNINIT);
    /*@LddRetVal = DEM_WRONG_DTC;*/
  }
  /* @Trace: Dem_SUD_API_20478 */
  #if (DEM_NUMBER_OF_DEM_CLIENT > DEM_ZERO)
  /* @Trace: Dem_SUD_API_20480 */
  else if (ClientId >= DEM_NUMBER_OF_DEM_CLIENT)
  {
    /* @Trace: Dem_SUD_API_20479 */
    DEM_REPORT_ERROR(DEM_GETSIZEOFEXTENDEDDATARECORDSELECTION_SID,
        DEM_E_WRONG_CONFIGURATION);
    /* @LddRetVal = DEM_WRONG_DTC; */
  }
  #endif
  else if (E_OK != Dem_ClientSelectExtendedDataRecord[ClientId].
                 resultSelectExtendedDataRecord)
  {
    /* @Trace: Dem_SUD_API_20481 */
    /* @Trace: SWS_Dem_01274
     * If any of the APIs requiring a Dem_SelectExtendedDataRecord (see
     * [SWS_Dem_01272]) are called without a prior call to
     * Dem_SelectExtendedDataRecord, the Dem shall report the Det error
     * DEM_E_WRONG_CONDITION.
     * */
    DEM_REPORT_ERROR(DEM_GETSIZEOFEXTENDEDDATARECORDSELECTION_SID,
       DEM_E_WRONG_CONDITION);
    /* @Trace: SWS_Dem_01269
     * The API Dem_SelectExtendedDataRecord triggers the Dem internal extended
     * data record selection process on the event memory assigned to the
     * ClientId. The Dem shall provide the result of the selection process
     * in the return value of the API calls following the
     * Dem_SelectExtendedDataRecord, see [SWS_Dem_01272].
     */
    LddRetVal = Dem_ClientSelectExtendedDataRecord[ClientId].
       resultSelectExtendedDataRecord;
  }
  else if (NULL_PTR == SizeOfExtendedDataRecord)
  {
    /* @Trace: Dem_SUD_API_20482 */
    DEM_REPORT_ERROR(DEM_GETSIZEOFEXTENDEDDATARECORDSELECTION_SID,
        DEM_E_PARAM_POINTER);
    /*@LddRetVal = DEM_WRONG_DTC;*/
  }
  /* Dem240 : Identification/Number of requested extended data record.
   * Valid values are from 0x01 to0xEF.
   * Additionally the values 0xFE and 0xFF are explicitly allowed to request
   * the overall size of all OBD records / all records.
   *  i.   1 <= n <= EF
   *  ii.  FE, FF */
  else if ((DEM_MIN_VALID_EXTENDED_RECORD_NUMBER  >
       Dem_ClientSelectExtendedDataRecord[ClientId].selectExtendedDataNumber) ||
          (((uint8)DEM_MAX_EXTENDED_RECORD_NUMBER !=
       Dem_ClientSelectExtendedDataRecord[ClientId].selectExtendedDataNumber) &&
          ((uint8)DEM_EXTENDED_DATA_NUMBER_OBD  !=
       Dem_ClientSelectExtendedDataRecord[ClientId].selectExtendedDataNumber) &&
          (DEM_MAX_VALID_EXTENDED_RECORD_NUMBER  <
       Dem_ClientSelectExtendedDataRecord[ClientId].selectExtendedDataNumber)))
  {
    /* @Trace: Dem_SUD_API_20106 */
    DEM_REPORT_ERROR(DEM_GETSIZEOFEXTENDEDDATARECORDSELECTION_SID,
        DEM_E_PARAM_DATA);
    LddRetVal = DEM_NO_SUCH_ELEMENT;
  }
  else
  {
    /* @Trace: Dem_SUD_API_20107 */
    Dem_EventIdType LddEventId = Dem_GetEventIdByDTC(
        DEM_GETSIZEOFEXTENDEDDATARECORDSELECTION_SID,
        Dem_ClientSelectDtcState[ClientId].selectedDTC,
        Dem_ClientSelectDtcState[ClientId].selectedDTCFormat);
    /* @if (DEM_FALSE == Dem_EventIdIsValid(LddEventId)) */
    if (( LddEventId > DEM_NUMBER_OF_EVENTS) ||
        ( DEM_NO_EVENT == LddEventId))
    {
      /* @Trace: Dem_SUD_API_20471 */
      DEM_REPORT_ERROR(DEM_GETSIZEOFEXTENDEDDATARECORDSELECTION_SID,
          DEM_E_PARAM_CONFIG);
      /*@LddRetVal = DEM_WRONG_DTC;*/
    }
    else if ( (boolean)DEM_FALSE == Dem_DTCOriginBelongToEvent(LddEventId,
                Dem_ClientSelectDtcState[ClientId].selectedDTCOrigin ))
    {
      /* @Trace: Dem_SUD_API_20472 */
      DEM_REPORT_ERROR(DEM_GETSIZEOFEXTENDEDDATARECORDSELECTION_SID,
                          DEM_E_PARAM_CONFIG);
      /* No destination of the event configured */
      LddRetVal = DEM_WRONG_DTCORIGIN;
    }
    else
    #if ((DEM_MAX_EVENT_DESTINATION_SELECTED > DEM_ZERO) && \
         (DEM_SIZE_OF_EXTENDED_DATA > DEM_ZERO))
    {
      Dem_EventRelatedDataPCType LddEvData = NULL_PTR;
      Dem_EventParameterPCType LddEvent = &Dem_Event[LddEventId - DEM_ONE];
     
      /* @Trace: Dem_SUD_API_20474 */
      if (LddEvent->e_PointToData < DEM_NUM_OF_EVENTRELATEDDATA)
      {
        LddEvData = &Dem_EventRelatedData[LddEvent->e_PointToData];

        /* @#if (DEM_OBD_SUPPORT !=  DEM_OBD_NO_OBD_SUPPORT) */
        if (DEM_EXTENDED_DATA_NUMBER_OBD == Dem_ClientSelectExtendedDataRecord[
                       ClientId].selectExtendedDataNumber)
        {
          /*  OBD is not supported yet */
          /* @Trace: Dem_SUD_API_20109 */
          DEM_REPORT_ERROR(DEM_GETSIZEOFEXTENDEDDATARECORDSELECTION_SID,
              DEM_E_PARAM_DATA);
          LddRetVal = DEM_WRONG_DTCORIGIN;
        }
        else if (LddEvData->EDClassPos < DEM_NUM_OF_EXTENDEDDATACLASS)
        {
          /* Dem076
           * record number 0xFE: the size of all OBD stored extended data
           * records(0x90 to 0xEF) record number 0xFF: the size of all stored
           * extended data records (0x01 to 0xEF)*/
          Dem_SizeOfExtendedDataClassType LddExtendedDataSize = DEM_ZERO;
          Dem_NumOfExtendedDataRecordClassType LddNumOfMatchedEDR = DEM_ZERO;
          LddExtendedDataSize = Dem_GetSizeOfExtendedData(
              &Dem_ExtendedDataClass[LddEvData->EDClassPos],
              Dem_ClientSelectExtendedDataRecord[ClientId].
              selectExtendedDataNumber,
              &LddNumOfMatchedEDR
              #if (DEM_J1979_2_OBD_ON_UDS == STD_ON)
              , LddEventId
              #endif
              );
          if (DEM_ZERO != LddExtendedDataSize)
          {
            if (DEM_NO_EVMEM_ENTRY == Dem_EvMemToEventMap[LddEventId])
            {
              /* @Trace: Dem_SUD_API_20476 */
              *SizeOfExtendedDataRecord = DEM_ZERO; /* Event is not stored.*/
            }
            else
            {
              /* @Trace: Dem_SUD_API_20477 */
              /*SWS_Dem_00240:  Size of the requested extended data record(s)
                including number of 'extended data record' */
              *SizeOfExtendedDataRecord = LddExtendedDataSize +
                  LddNumOfMatchedEDR;
            }
            LddRetVal = E_OK;
          }
          else
          {
            /* @Trace: Dem_SUD_API_20475 */
            DEM_REPORT_ERROR(DEM_GETSIZEOFEXTENDEDDATARECORDSELECTION_SID,
                DEM_E_PARAM_CONFIG);
            LddRetVal = DEM_NO_SUCH_ELEMENT;
          }
        }
        else
        {
          /* @Trace: Dem_SUD_API_20108 */
          LddRetVal = DEM_WRONG_DTC;
        }
      }
    }
    #else
    {
      /* @Trace: Dem_SUD_API_20473 */
      DEM_REPORT_ERROR(DEM_GETSIZEOFEXTENDEDDATARECORDSELECTION_SID,
          DEM_E_PARAM_CONFIG);
      LddRetVal = DEM_WRONG_DTC;
    }
    #endif
  }
  /* polyspace<RTE:UNR:Not a defect:No action planned> If-condition always
   * evaluates to true. Avoid to 'Unreachable code' of the polyspace */
  return LddRetVal;
}
/* polyspace:end<MISRA-C:5.1:Not a defect:Justify with annotations> This
 * Identifier is Specification. */
#endif
#define DEM_STOP_SEC_CODE
#include "MemMap.h"

/* polyspace:end<MISRA-C:1.1:Not a defect:Justify with annotations> Not
 * a defect */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/

