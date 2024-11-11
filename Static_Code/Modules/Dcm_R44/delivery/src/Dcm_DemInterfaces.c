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
**  SRC-MODULE: Dcm_DemInterfaces.c                                           **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostic Communication Manager Module               **
**                                                                            **
**  PURPOSE   : This file contains wrapper DEM interfaces                     **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By             Description                         **
********************************************************************************
** 0.0.1     31-Dec-2019   LamNV10        AR440 Implementation                **
** 0.0.2     05-May-2020   LamNV10        Add pre-compile for API of UDS 0x19 **
** 0.0.3     16-Aug-2020   HueKM          Fix defect and coding rules         **
** 0.0.4     13-Oct-2020   HueKM          Changes made as per #15766          **
** 0.0.5     16-Dec-2020   HueKM          Mapping SUD API ID as per #17448    **
** 1.0.12    30-Jun-2023   SY Kim         Refer #CP44-2255                    **
** 1.1.0     12-Oct-2023   SY Kim         Refer #CP44-3106                    **
** 1.3.0     31-Dec-2023   EK Kim         Refer #CP44-1515                    **
** 1.4.0     29-Mar-2024   EK Kim         Refer #CP44-3850                    **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Dcm.h"
#if (DCM_DEM_CONFIGURED == STD_ON)
#include "Dem.h"
#include "Dem_Dcm.h"
#include "Dcm_Utils.h"
#include "Rte_Dcm_Type.h"

#include "Rte_Dem.h"
#include "Dcm_DemInterfaces.h"

#define DCM_START_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
**                      FUNCTION DEFINITIONS                                  **
*******************************************************************************/
/*******************************************************************************
** Function Name        : IDem_EnableDTCSetting                               **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : The function is wrapper of                          **
**                        Dem_EnableDTCSetting() interface                    **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) IDem_EnableDTCSetting(void)
{
  /* @Trace: Dcm_SUD_API_00464 */
  uint8 LucClientId = Dcm_Internal_GetDemClientId();
  return Dem_EnableDTCSetting(LucClientId);
}

/*******************************************************************************
** Function Name        : IDem_DisableDTCSetting                              **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : The function is wrapper of                          **
**                        Dem_DisableDTCSetting() interface                   **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) IDem_DisableDTCSetting(void)
{
  /* @Trace: Dcm_SUD_API_00462 */
  uint8 LucClientId = Dcm_Internal_GetDemClientId();
  return Dem_DisableDTCSetting(LucClientId);
}

/*******************************************************************************
** Function Name        : IDem_GetDTCStatusAvailabilityMask                   **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : The function is wrapper of                          **
**                        Dem_GetDTCStatusAvailabilityMask() interface        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : DTCStatusMask                                       **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) IDem_GetDTCStatusAvailabilityMask(
  P2VAR(Dem_UdsStatusByteType, AUTOMATIC, DCM_APPL_DATA) DTCStatusMask)
{
  /* @Trace: Dcm_SUD_API_00474 */
  Std_ReturnType LddRetVal = E_NOT_OK;
  uint8 LucClientId = Dcm_Internal_GetDemClientId();

  if (NULL_PTR != DTCStatusMask)
  {
    /* @Trace: SWS_Dcm_00007 */
    /* @Trace: Dcm_SUD_API_00473 */
    LddRetVal = Dem_GetDTCStatusAvailabilityMask(LucClientId, DTCStatusMask);
  }

  return LddRetVal;
}

/*******************************************************************************
** Function Name        : IDem_SetDTCFilter                                   **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : The function is wrapper of                          **
**                        Dem_SetDTCFilter() interface                        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : DTCStatusMask, DTCFormat, DTCOrigin                 **
**                        FilterWithSeverity, DTCSeverityMask,                **
**                        FilterForFaultDetectionCounter                      **
**                                                                            **
** InOut Parameters     : pErrorCode                                          **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) IDem_SetDTCFilter(
  uint8 DTCStatusMask,
  Dem_DTCFormatType DTCFormat, 
  Dem_DTCOriginType DTCOrigin,
  boolean FilterWithSeverity, 
  Dem_DTCSeverityType DTCSeverityMask,
  boolean FilterForFaultDetectionCounter,
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) pErrorCode)
{
  Std_ReturnType LddRetVal;
  uint8 LucClientId = Dcm_Internal_GetDemClientId();

  LddRetVal = Dem_SetDTCFilter(
    LucClientId, DTCStatusMask, DTCFormat, DTCOrigin, 
    FilterWithSeverity, DTCSeverityMask,FilterForFaultDetectionCounter);

  /* @Trace: SWS_Dcm_01043 SWS_Dcm_01255 */
  /* @Trace: Dcm_SUD_API_00519 Dcm_SUD_API_00520 */
  /* If E_NOT_OK value is returned, the Dcm module shall send NRC 0x31 */
  *pErrorCode = (E_OK == LddRetVal) ? *pErrorCode : DCM_E_REQUESTOUTOFRANGE;

  return LddRetVal;
}

/*******************************************************************************
** Function Name        : IDem_SetDTCFilterByExtendedDataRecordNumber                                   **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : The function is wrapper of                          **
**                        Dem_SetDTCFilterByExtendedDataRecordNumber() interface                        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : DTCFormat, ExtendedDataRecordnumber                **
**                                                                            **
** InOut Parameters     : pErrorCode                                          **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
 #if (DCM_J1979_2_SUPPORT == STD_ON)
/* Trace: DCM_19792_1A_08 */
FUNC(Std_ReturnType, DCM_CODE) IDem_SetDTCFilterByExtendedDataRecordNumber(
  Dem_DTCFormatType DTCFormat, 
  uint8 ExtendedDataRecordnumber,
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) pErrorCode)
{
  Std_ReturnType LddRetVal;
  uint8 LucClientId = Dcm_Internal_GetDemClientId();

  LddRetVal = Dem_SetDTCFilterByExtendedDataRecordNumber(
    LucClientId, DTCFormat, ExtendedDataRecordnumber);

  /* @Trace: SWS_Dcm_01043 SWS_Dcm_01255 */
  /* @Trace: Dcm_SUD_API_00519 Dcm_SUD_API_00520 */
  /* If E_NOT_OK value is returned, the Dcm module shall send NRC 0x31 */
  *pErrorCode = (E_OK == LddRetVal) ? *pErrorCode : DCM_E_REQUESTOUTOFRANGE;

  return LddRetVal;
}
#endif /* J19792 */

/*******************************************************************************
** Function Name        : IDem_SetDTCFilterByExtendedDataRecordNumber                                   **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : The function is wrapper of                          **
**                        Dem_SetDTCFilterByExtendedDataRecordNumber() interface                        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : DTCFormat, ExtendedDataRecordnumber                **
**                                                                            **
** InOut Parameters     : pErrorCode                                          **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
 #if (DCM_J1979_2_SUPPORT == STD_ON)
/* Trace: DCM_19792_56_13 */
FUNC(Std_ReturnType, DCM_CODE) IDem_SetDTCFilterByReadinessGroup(
  Dem_DTCFormatType DTCFormat,
  Dem_EventOBDReadinessGroupType ReadinessGroupNumber,
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) pErrorCode)
{
  Std_ReturnType LddRetVal;
  uint8 LucClientId = Dcm_Internal_GetDemClientId();

  LddRetVal = Dem_SetDTCFilterByReadinessGroup(
    LucClientId, DTCFormat, ReadinessGroupNumber);

  /* @Trace: SWS_Dcm_01043 SWS_Dcm_01255 */
  /* @Trace: Dcm_SUD_API_00519 Dcm_SUD_API_00520 */
  /* If E_NOT_OK value is returned, the Dcm module shall send NRC 0x31 */
  *pErrorCode = (E_OK == LddRetVal) ? *pErrorCode : DCM_E_REQUESTOUTOFRANGE;

  return LddRetVal;
}
#endif /* J19792 */

/*******************************************************************************
** Function Name        : IDem_GetTranslationType                             **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : The function is wrapper of                          **
**                        Dem_GetTranslationType() interface                  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Dem_DTCTranslationFormatType                        **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
FUNC(Dem_DTCTranslationFormatType, DCM_CODE) IDem_GetTranslationType(void)
{
  /* @Trace: Dcm_SUD_API_00514 */
  uint8 LucClientId = Dcm_Internal_GetDemClientId();
  return Dem_GetTranslationType(LucClientId);
}

/*******************************************************************************
** Function Name        : IDem_GetNumberOfFilteredDTC                         **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : The function is wrapper of                          **
**                        Dem_GetNumberOfFilteredDTC() interface              **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : NumberOfFilteredDTC                                 **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) IDem_GetNumberOfFilteredDTC(
  P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) NumberOfFilteredDTC)
{
  /* @Trace: Dcm_SUD_API_00498 */
  Std_ReturnType LddRetVal = E_NOT_OK;
  uint8 LucClientId = Dcm_Internal_GetDemClientId();

  if (NULL_PTR != NumberOfFilteredDTC)
  {
    /* @Trace: Dcm_SUD_API_00497 */
    LddRetVal = Dem_GetNumberOfFilteredDTC(LucClientId, NumberOfFilteredDTC);
  }

  return LddRetVal;
}

/*******************************************************************************
** Function Name        : IDem_SelectDTC                                      **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : The function is wrapper of                          **
**                        Dem_SelectDTC() interface                           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : DTC, DTCFormat, DTCOrigin                           **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) IDem_SelectDTC(
  uint32 DTC, 
  Dem_DTCFormatType DTCFormat, 
  Dem_DTCOriginType DTCOrigin)
{
  /* @Trace: Dcm_SUD_API_00515 */
  uint8 LucClientId = Dcm_Internal_GetDemClientId();

  /* @Trace: SWS_Dcm_01263 */
  return Dem_SelectDTC(LucClientId, DTC, DTCFormat, DTCOrigin);
}

/*******************************************************************************
** Function Name        : IDem_GetDTCSelectionResultForClearDTC               **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : The function is wrapper of                          **
**                        Dem_GetDTCSelectionResultForClearDTC() interface    **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) IDem_GetDTCSelectionResultForClearDTC(void)
{
  /* @Trace: Dcm_SUD_API_00468 */
  uint8 LucClientId = Dcm_Internal_GetDemClientId();

  /* @Trace: SWS_Dcm_01400 SWS_Dcm_01268 */
  return Dem_GetDTCSelectionResultForClearDTC(LucClientId);
}

/*******************************************************************************
** Function Name        : IDem_ClearDTC                                       **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : The function is wrapper of                          **
**                        Dem_ClearDTC() interface                            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) IDem_ClearDTC(void)
{
  /* @Trace: Dcm_SUD_API_00451 */
  uint8 LucClientId = Dcm_Internal_GetDemClientId();

  /* @Trace: SWS_Dcm_00005 */
  return Dem_ClearDTC(LucClientId);
}

/*******************************************************************************
** Function Name        : IDem_GetNextFilteredDTC                             **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : The function is wrapper of                          **
**                        Dem_GetNextFilteredDTC() interface                  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : DTC, DTCStatus                                      **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) IDem_GetNextFilteredDTC(
  P2VAR(uint32, AUTOMATIC, DCM_APPL_DATA) DTC,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) DTCStatus)
{
  /* @Trace: Dcm_SUD_API_00483 */
  Std_ReturnType LddRetVal = E_NOT_OK;
  uint8 LucClientId = Dcm_Internal_GetDemClientId();

  if ((NULL_PTR != DTC) && (NULL_PTR != DTCStatus))
  {
    /* @Trace: Dcm_SUD_API_00482 */
    LddRetVal = Dem_GetNextFilteredDTC(LucClientId, DTC, DTCStatus);
  }

  return LddRetVal;
}

/*******************************************************************************
** Function Name        : IDem_GetNextFilteredDTCAndSeverity                  **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : The function is wrapper of                          **
**                        Dem_GetNextFilteredDTCAndSeverity() interface       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : DTC, DTCStatus, DTCSeverity, DTCFunctionalUnit      **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) IDem_GetNextFilteredDTCAndSeverity(
  P2VAR(uint32, AUTOMATIC, DCM_APPL_DATA) DTC, 
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) DTCStatus,
  P2VAR(Dem_DTCSeverityType, AUTOMATIC, DCM_APPL_DATA) DTCSeverity, 
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) DTCFunctionalUnit)
{
  /* @Trace: Dcm_SUD_API_00489 */
  Std_ReturnType LddRetVal = E_NOT_OK;
  uint8 LucClientId = Dcm_Internal_GetDemClientId();

  if ((NULL_PTR != DTC) && (NULL_PTR != DTCStatus) && 
      (NULL_PTR != DTCSeverity) && (NULL_PTR != DTCFunctionalUnit))
  {
    /* @Trace: Dcm_SUD_API_00488 */
    LddRetVal = Dem_GetNextFilteredDTCAndSeverity(
      LucClientId, DTC, DTCStatus, DTCSeverity, DTCFunctionalUnit);
  }

  return LddRetVal;
}

/*******************************************************************************
** Function Name        : IDem_GetStatusOfDTC                                 **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : The function is wrapper of                          **
**                        Dem_GetStatusOfDTC() interface                      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : DTCStatus                                           **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) IDem_GetStatusOfDTC(
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) DTCStatus)
{
  /* @Trace: Dcm_SUD_API_00513 */
  Std_ReturnType LddRetVal = E_NOT_OK;
  uint8 LucClientId = Dcm_Internal_GetDemClientId();

  if (NULL_PTR != DTCStatus)
  {
    /* @Trace: Dcm_SUD_API_00512 */
    LddRetVal = Dem_GetStatusOfDTC(LucClientId, DTCStatus);
  }

  return LddRetVal;
}

/*******************************************************************************
** Function Name        : IDem_GetSeverityOfDTC                               **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : The function is wrapper of                          **
**                        Dem_GetSeverityOfDTC() interface                    **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : DTCSeverity                                         **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) IDem_GetSeverityOfDTC(
  P2VAR(Dem_DTCSeverityType, AUTOMATIC, DCM_APPL_DATA) DTCSeverity)
{
  /* @Trace: Dcm_SUD_API_00504 */
  Std_ReturnType LddRetVal = E_NOT_OK;
  uint8 LucClientId = Dcm_Internal_GetDemClientId();

  if (NULL_PTR != DTCSeverity)
  {
    /* @Trace: Dcm_SUD_API_00503 */
    LddRetVal = Dem_GetSeverityOfDTC(LucClientId, DTCSeverity);
  }

  return LddRetVal;
}

/*******************************************************************************
** Function Name        : IDem_GetFunctionalUnitOfDTC                         **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : The function is wrapper of                          **
**                        Dem_GetFunctionalUnitOfDTC() interface              **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : DTCFunctionalUnit                                   **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) IDem_GetFunctionalUnitOfDTC(
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) DTCFunctionalUnit)
{
  /* @Trace: Dcm_SUD_API_00477 */
  Std_ReturnType LddRetVal = E_NOT_OK;
  uint8 LucClientId = Dcm_Internal_GetDemClientId();

  if (NULL_PTR != DTCFunctionalUnit)
  {
    /* @Trace: Dcm_SUD_API_00476 */
    LddRetVal = Dem_GetFunctionalUnitOfDTC(LucClientId, DTCFunctionalUnit);
  }

  return LddRetVal;
}

/*******************************************************************************
** Function Name        : IDem_GetSizeOfExtendedDataRecordSelection           **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : The function is wrapper of                          **
**                        Dem_GetSizeOfExtendedDataRecordSelection interface  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : SizeOfExtendedDataRecord                            **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
#if (DCM_RPT_DTCEXTENDEDDATARECORD == STD_ON)
FUNC(Std_ReturnType, DCM_CODE) IDem_GetSizeOfExtendedDataRecordSelection(
  P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) SizeOfExtendedDataRecord)
{
  /* @Trace: Dcm_SUD_API_00505 */
  Std_ReturnType LddRetVal = E_NOT_OK;
  uint8 LucClientId = Dcm_Internal_GetDemClientId();

  if (NULL_PTR != SizeOfExtendedDataRecord)
  {
    /* @Trace: Dcm_SUD_API_00506 */
    LddRetVal = Dem_GetSizeOfExtendedDataRecordSelection(
      LucClientId, SizeOfExtendedDataRecord);
  }

  return LddRetVal;
}
#endif

/*******************************************************************************
** Function Name        : IDem_DisableDTCRecordUpdate                         **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : The function is wrapper of                          **
**                        Dem_DisableDTCRecordUpdate() interface              **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : pErrorCode                                          **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) IDem_DisableDTCRecordUpdate(
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) pErrorCode)
{
  uint8 LucClientId = Dcm_Internal_GetDemClientId();
  Std_ReturnType LddRetVal = Dem_DisableDTCRecordUpdate(LucClientId);

  /* @Trace: SWS_Dcm_01212 SWS_Dcm_01213 */
  /* @Trace: Dcm_SUD_API_00460 Dcm_SUD_API_00459 */
  *pErrorCode = ((DEM_WRONG_DTC == LddRetVal) || \
    (DEM_WRONG_DTCORIGIN == LddRetVal)) ? DCM_E_REQUESTOUTOFRANGE : *pErrorCode;

  return LddRetVal;
}

/*******************************************************************************
** Function Name        : IDem_EnableDTCRecordUpdate                          **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : The function is wrapper of                          **
**                        Dem_EnableDTCRecordUpdate() interface               **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) IDem_EnableDTCRecordUpdate(void)
{
  /* @Trace: Dcm_SUD_API_00463 */
  uint8 LucClientId = Dcm_Internal_GetDemClientId();
  return Dem_EnableDTCRecordUpdate(LucClientId);
}

/*******************************************************************************
** Function Name        : IDem_SelectExtendedDataRecord                       **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : The function is wrapper of                          **
**                        Dem_SelectExtendedDataRecord() interface            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : ExtendedDataNumber                                  **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
#if (DCM_RPT_DTCEXTENDEDDATARECORD == STD_ON)
FUNC(Std_ReturnType, DCM_CODE) IDem_SelectExtendedDataRecord(
  uint8 ExtendedDataNumber)
{
  /* @Trace: Dcm_SUD_API_00516 */
  uint8 LucClientId = Dcm_Internal_GetDemClientId();
  return Dem_SelectExtendedDataRecord(LucClientId, ExtendedDataNumber);
}
#endif

/*******************************************************************************
** Function Name        : IDem_GetNextExtendedDataRecord                      **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : The function is wrapper of                          **
**                        Dem_GetNextExtendedDataRecord() interface           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : BufferSize                                          **
**                                                                            **
** Output Parameters    : DestBuffer                                          **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
#if (DCM_RPT_DTCEXTENDEDDATARECORD == STD_ON)
FUNC(Std_ReturnType, DCM_CODE) IDem_GetNextExtendedDataRecord(
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) DestBuffer, 
  P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) BufferSize)
{
  /* @Trace: Dcm_SUD_API_00478 */
  Std_ReturnType LddRetVal = E_NOT_OK;
  uint8 LucClientId = Dcm_Internal_GetDemClientId();

  if ((NULL_PTR != DestBuffer) && (NULL_PTR != BufferSize))
  {
    /* @Trace: Dcm_SUD_API_00479 */
    LddRetVal = Dem_GetNextExtendedDataRecord(
      LucClientId, DestBuffer, BufferSize);
  }

  return LddRetVal;
}
#endif

/*******************************************************************************
** Function Name        : IDem_GetSizeOfFreezeFrameSelection                  **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : The function is wrapper of                          **
**                        Dem_GetSizeOfFreezeFrameSelection() interface       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : SizeOfFreezeFrame                                   **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
#if (DCM_RPT_DTCSNAPSHOTREC_BYDTCNUM == STD_ON)
FUNC(Std_ReturnType, DCM_CODE) IDem_GetSizeOfFreezeFrameSelection(
  P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) SizeOfFreezeFrame)
{
  /* @Trace: Dcm_SUD_API_00508 */
  Std_ReturnType LddRetVal = E_NOT_OK;
  uint8 LucClientId = Dcm_Internal_GetDemClientId();

  if (NULL_PTR != SizeOfFreezeFrame)
  {
    /* @Trace: Dcm_SUD_API_00509 */
    LddRetVal = Dem_GetSizeOfFreezeFrameSelection(
      LucClientId, SizeOfFreezeFrame);
  }

  return LddRetVal;
}
#endif

/*******************************************************************************
** Function Name        : IDem_GetNextFreezeFrameData                         **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : The function is wrapper of                          **
**                        Dem_GetNextFreezeFrameData() interface              **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : BufferSize                                          **
**                                                                            **
** Output Parameters    : DestBuffer                                          **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
#if (DCM_RPT_DTCSNAPSHOTREC_BYDTCNUM == STD_ON)
FUNC(Std_ReturnType, DCM_CODE) IDem_GetNextFreezeFrameData(
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) DestBuffer,
  P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) BufferSize)
{
  /* @Trace: Dcm_SUD_API_00493 */
  Std_ReturnType LddRetVal = E_NOT_OK;
  uint8 LucClientId = Dcm_Internal_GetDemClientId();

  if ((NULL_PTR != DestBuffer) && (NULL_PTR != BufferSize))
  {
    /* @Trace: Dcm_SUD_API_00494 */
    LddRetVal = Dem_GetNextFreezeFrameData(LucClientId, DestBuffer, BufferSize);
  }

  return LddRetVal;
}

/*******************************************************************************
** Function Name        : IDem_SelectFreezeFrameData                          **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : The function is wrapper of                          **
**                        Dem_SelectFreezeFrameData() interface               **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : RecordNumber                                        **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) IDem_SelectFreezeFrameData(
  uint8 RecordNumber)
{
  /* @Trace: Dcm_SUD_API_00517 */
  uint8 LucClientId = Dcm_Internal_GetDemClientId();
  return Dem_SelectFreezeFrameData(LucClientId, RecordNumber);
}
#endif

/*******************************************************************************
** Function Name        : IDem_SetFreezeFrameRecordFilter                     **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : The function is wrapper of                          **
**                        Dem_SetFreezeFrameRecordFilter() interface          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : DTCFormat                                           **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) IDem_SetFreezeFrameRecordFilter(
  Dem_DTCFormatType DTCFormat)
{
  /* @Trace: Dcm_SUD_API_00522 */
  uint8 LucClientId = Dcm_Internal_GetDemClientId();
  return Dem_SetFreezeFrameRecordFilter(LucClientId, DTCFormat);
}

/*******************************************************************************
** Function Name        : IDem_GetNumberOfFreezeFrameRecords                  **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : The function is wrapper of                          **
**                        Dem_GetNumberOfFreezeFrameRecords() interface       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : NumberOfFilteredRecords                             **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) IDem_GetNumberOfFreezeFrameRecords(
  P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) NumberOfFilteredRecords)
{
  /* @Trace: Dcm_SUD_API_00501 */
  Std_ReturnType LddRetVal = E_NOT_OK;
  uint8 LucClientId = Dcm_Internal_GetDemClientId();

  if (NULL_PTR != NumberOfFilteredRecords)
  {
    /* @Trace: Dcm_SUD_API_00500 */
    LddRetVal = Dem_GetNumberOfFreezeFrameRecords(
      LucClientId, NumberOfFilteredRecords);
  }

  return LddRetVal;
}

/*******************************************************************************
** Function Name        : IDem_GetNextFilteredRecord                          **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : The function is wrapper of                          **
**                        Dem_GetNextFilteredRecord() interface               **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : DTC, RecordNumber                                   **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) IDem_GetNextFilteredRecord(
  P2VAR(uint32, AUTOMATIC, DCM_APPL_DATA) DTC,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) RecordNumber)
{
  /* @Trace: Dcm_SUD_API_00492 */
  Std_ReturnType LddRetVal = E_NOT_OK;
  uint8 LucClientId = Dcm_Internal_GetDemClientId();

  if ((NULL_PTR != DTC) && ((NULL_PTR != RecordNumber)))
  {
    /* @Trace: Dcm_SUD_API_00491 */
    LddRetVal = Dem_GetNextFilteredRecord(LucClientId, DTC, RecordNumber);
  }

  return LddRetVal;
}

/*******************************************************************************
** Function Name        : IDem_DcmGetDTCOfOBDFreezeFrame                      **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : The function is wrapper of                          **
**                        Dem_DcmGetDTCOfOBDFreezeFrame() interface           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : FrameNumber, DTCFormat                              **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : DTC                                                 **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
#if ((DCM_RPT_DTCSNAPSHOTREC_BYSNAPSHOTNUM == STD_ON) || \
     (DCM_OBD_REQPOWERTRAIN_FREEZEFRAMEDATA_SERVICE == STD_ON))
FUNC(Std_ReturnType, DCM_CODE) IDem_DcmGetDTCOfOBDFreezeFrame(
  uint8 FrameNumber, 
  P2VAR(uint32, AUTOMATIC, DCM_APPL_DATA) DTC,
  Dem_DTCFormatType DTCFormat)
{
  /* @Trace: Dcm_SUD_API_00452 */
  Std_ReturnType LddRetVal = E_NOT_OK;

  if (NULL_PTR != DTC)
  {
    /* @Trace: Dcm_SUD_API_00453 */
    LddRetVal = Dem_DcmGetDTCOfOBDFreezeFrame(FrameNumber, DTC, DTCFormat);
  }

  return LddRetVal;
}

/*******************************************************************************
** Function Name        : IDem_DcmReadDataOfOBDFreezeFrame                    **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : The function is wrapper of                          **
**                        Dem_DcmReadDataOfOBDFreezeFrame() interface         **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : PID, DataElementIndexOfPID                          **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : DestBuffer, BufferSize                              **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) IDem_DcmReadDataOfOBDFreezeFrame(
  uint8 PID, 
  uint8 DataElementIndexOfPID, 
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) DestBuffer, 
  P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) BufferSize)
{
  /* @Trace: Dcm_SUD_API_00455 */
  Std_ReturnType LddRetVal = E_NOT_OK;

  if ((NULL_PTR != DestBuffer) && (NULL_PTR != BufferSize))
  {
    /* @Trace: Dcm_SUD_API_00456 */
    LddRetVal = Dem_DcmReadDataOfOBDFreezeFrame(
      PID, DataElementIndexOfPID, DestBuffer, BufferSize);
  }

  return LddRetVal;
}
#endif

/*******************************************************************************
** Function Name        : IDem_GetDTCByOccurrenceTime                         **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : The function is wrapper of                          **
**                        Dem_GetDTCByOccurrenceTime() interface              **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : DTCRequest                                          **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : DTC                                                 **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
#if (DCM_RPT_FAILEDCONFIRMEDDTCINFO == STD_ON)
FUNC(Std_ReturnType, DCM_CODE) IDem_GetDTCByOccurrenceTime(
  Dem_DTCRequestType DTCRequest, 
  P2VAR(uint32, AUTOMATIC, DCM_APPL_DATA) DTC)
{
  /* @Trace: Dcm_SUD_API_00465 */
  Std_ReturnType LddRetVal = E_NOT_OK;
  uint8 LucClientId = Dcm_Internal_GetDemClientId();

  if (NULL_PTR != DTC)
  {
    /* @Trace: Dcm_SUD_API_00466 */
    LddRetVal = Dem_GetDTCByOccurrenceTime(LucClientId, DTCRequest, DTC);
  }

  return LddRetVal;
}
#endif

/*******************************************************************************
** Function Name        : IDem_GetNextFilteredDTCAndFDC                       **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : The function is wrapper of                          **
**                        Dem_GetNextFilteredDTCAndFDC() interface            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : DTC, DTCFaultDetectionCounter                       **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) IDem_GetNextFilteredDTCAndFDC(
  P2VAR(uint32, AUTOMATIC, DCM_APPL_DATA) DTC, 
  P2VAR(sint8, AUTOMATIC, DCM_APPL_DATA) DTCFaultDetectionCounter)
{
  /* @Trace: Dcm_SUD_API_00486 */
  Std_ReturnType LddRetVal = E_NOT_OK;
  uint8 LucClientId = Dcm_Internal_GetDemClientId();

  if ((NULL_PTR != DTC) && (NULL_PTR != DTCFaultDetectionCounter))
  {
    /* @Trace: Dcm_SUD_API_00485 */
    LddRetVal = Dem_GetNextFilteredDTCAndFDC(
      LucClientId, DTC, DTCFaultDetectionCounter);
  }

  return LddRetVal;
}

/*******************************************************************************
** Function Name        : IDem_GetDTCSeverityAvailabilityMask                 **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : The function is wrapper of                          **
**                        Dem_GetDTCSeverityAvailabilityMask() interface      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : DTCSeverityMask                                     **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) IDem_GetDTCSeverityAvailabilityMask(
  P2VAR(Dem_DTCSeverityType, AUTOMATIC, DCM_APPL_DATA) DTCSeverityMask)
{
  /* @Trace: Dcm_SUD_API_00471 */
  Std_ReturnType LddRetVal = E_NOT_OK;
  uint8 LucClientId = Dcm_Internal_GetDemClientId();

  if (NULL_PTR != DTCSeverityMask)
  {
    /* @Trace: Dcm_SUD_API_00470 */
    LddRetVal = Dem_GetDTCSeverityAvailabilityMask(
      LucClientId, DTCSeverityMask);
  }

  return LddRetVal;
}

#define DCM_STOP_SEC_CODE
#include "MemMap.h"

#endif /*#if (DCM_DEM_CONFIGURED == STD_ON) */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
