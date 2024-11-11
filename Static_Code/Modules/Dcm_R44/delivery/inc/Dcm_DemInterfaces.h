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
**  SRC-MODULE: Dcm_DemInterfaces.h                                           **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostic Communication Manager Module               **
**                                                                            **
**  PURPOSE   : C header for Dcm_DemInterfaces                                **
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
** 0.0.3     13-Oct-2020   HueKM          Changes made as per #15766          **
** 1.1.0     12-Oct-2023   SY Kim         Refer #CP44-3106                    **
** 1.3.0     31-Dec-2023   EK Kim         Refer #CP44-1515                    **
** 1.4.0     29-Mar-2024   EK Kim         Refer #CP44-3850                    **
*******************************************************************************/
#ifndef DCM_DEMINTERFACES_H
#define DCM_DEMINTERFACES_H

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
#define DCM_START_SEC_CODE
#include "MemMap.h"

extern FUNC(Std_ReturnType, DCM_CODE) IDem_EnableDTCSetting(void);

extern FUNC(Std_ReturnType, DCM_CODE) IDem_DisableDTCSetting(void);

extern FUNC(Std_ReturnType, DCM_CODE) IDem_GetDTCStatusAvailabilityMask(
  P2VAR(Dem_UdsStatusByteType, AUTOMATIC, DCM_APPL_DATA) DTCStatusMask);

extern FUNC(Std_ReturnType, DCM_CODE) IDem_SetDTCFilter(
  uint8 DTCStatusMask,
  Dem_DTCFormatType DTCFormat, 
  Dem_DTCOriginType DTCOrigin,
  boolean FilterWithSeverity, 
  Dem_DTCSeverityType DTCSeverityMask,
  boolean FilterForFaultDetectionCounter,
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) pErrorCode);

extern FUNC(Dem_DTCTranslationFormatType, DCM_CODE) IDem_GetTranslationType(void);

extern FUNC(Std_ReturnType, DCM_CODE) IDem_GetNumberOfFilteredDTC(
  P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) NumberOfFilteredDTC);

extern FUNC(Std_ReturnType, DCM_CODE) IDem_SelectDTC(
  uint32 DTC, 
  Dem_DTCFormatType DTCFormat, 
  Dem_DTCOriginType DTCOrigin);

extern FUNC(Std_ReturnType, DCM_CODE) IDem_GetDTCSelectionResultForClearDTC(void);

extern FUNC(Std_ReturnType, DCM_CODE) IDem_ClearDTC(void);

extern FUNC(Std_ReturnType, DCM_CODE) IDem_GetNextFilteredDTC(
  P2VAR(uint32, AUTOMATIC, DCM_APPL_DATA) DTC,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) DTCStatus);

extern FUNC(Std_ReturnType, DCM_CODE) IDem_GetNextFilteredDTCAndSeverity(
  P2VAR(uint32, AUTOMATIC, DCM_APPL_DATA) DTC, 
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) DTCStatus,
  P2VAR(Dem_DTCSeverityType, AUTOMATIC, DCM_APPL_DATA) DTCSeverity, 
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) DTCFunctionalUnit);

extern FUNC(Std_ReturnType, DCM_CODE) IDem_GetStatusOfDTC(
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) DTCStatus);

extern FUNC(Std_ReturnType, DCM_CODE) IDem_GetSeverityOfDTC(
  P2VAR(Dem_DTCSeverityType, AUTOMATIC, DCM_APPL_DATA) DTCSeverity);

extern FUNC(Std_ReturnType, DCM_CODE) IDem_GetFunctionalUnitOfDTC(
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) DTCFunctionalUnit);

#if (DCM_RPT_DTCEXTENDEDDATARECORD == STD_ON)
extern FUNC(Std_ReturnType, DCM_CODE) IDem_GetSizeOfExtendedDataRecordSelection(
  P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) SizeOfExtendedDataRecord);
#endif

extern FUNC(Std_ReturnType, DCM_CODE) IDem_DisableDTCRecordUpdate(
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) pErrorCode);

extern FUNC(Std_ReturnType, DCM_CODE) IDem_EnableDTCRecordUpdate(void);

#if (DCM_RPT_DTCEXTENDEDDATARECORD == STD_ON)
extern FUNC(Std_ReturnType, DCM_CODE) IDem_SelectExtendedDataRecord(
  uint8 ExtendedDataNumber);
#endif

#if (DCM_RPT_DTCEXTENDEDDATARECORD == STD_ON)
extern FUNC(Std_ReturnType, DCM_CODE) IDem_GetNextExtendedDataRecord(
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) DestBuffer, 
  P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) BufferSize);
#endif

#if (DCM_RPT_DTCSNAPSHOTREC_BYDTCNUM == STD_ON)
extern FUNC(Std_ReturnType, DCM_CODE) IDem_GetSizeOfFreezeFrameSelection(
  P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) SizeOfFreezeFrame);
#endif

#if (DCM_RPT_DTCSNAPSHOTREC_BYDTCNUM == STD_ON)
extern FUNC(Std_ReturnType, DCM_CODE) IDem_GetNextFreezeFrameData(
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) DestBuffer,
  P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) BufferSize);

extern FUNC(Std_ReturnType, DCM_CODE) IDem_SelectFreezeFrameData(
  uint8 RecordNumber);
#endif

extern FUNC(Std_ReturnType, DCM_CODE) IDem_SetFreezeFrameRecordFilter(
  Dem_DTCFormatType DTCFormat);

extern FUNC(Std_ReturnType, DCM_CODE) IDem_GetNumberOfFreezeFrameRecords(
  P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) NumberOfFilteredRecords);

extern FUNC(Std_ReturnType, DCM_CODE) IDem_GetNextFilteredRecord(
  P2VAR(uint32, AUTOMATIC, DCM_APPL_DATA) DTC,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) RecordNumber);

#if ((DCM_RPT_DTCSNAPSHOTREC_BYSNAPSHOTNUM == STD_ON) || \
     (DCM_OBD_REQPOWERTRAIN_FREEZEFRAMEDATA_SERVICE == STD_ON))
extern FUNC(Std_ReturnType, DCM_CODE) IDem_DcmGetDTCOfOBDFreezeFrame(
  uint8 FrameNumber, 
  P2VAR(uint32, AUTOMATIC, DCM_APPL_DATA) DTC,
  Dem_DTCFormatType DTCFormat);

extern FUNC(Std_ReturnType, DCM_CODE) IDem_DcmReadDataOfOBDFreezeFrame(
  uint8 PID, 
  uint8 DataElementIndexOfPID, 
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) DestBuffer, 
  P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) BufferSize);
#endif

#if(DCM_RPT_FAILEDCONFIRMEDDTCINFO == STD_ON)
extern FUNC(Std_ReturnType, DCM_CODE) IDem_GetDTCByOccurrenceTime(
  Dem_DTCRequestType DTCRequest, 
  P2VAR(uint32, AUTOMATIC, DCM_APPL_DATA) DTC);
#endif

extern FUNC(Std_ReturnType, DCM_CODE) IDem_GetNextFilteredDTCAndFDC(
  P2VAR(uint32, AUTOMATIC, DCM_APPL_DATA) DTC, 
  P2VAR(sint8, AUTOMATIC, DCM_APPL_DATA) DTCFaultDetectionCounter);

extern FUNC(Std_ReturnType, DCM_CODE) IDem_GetDTCSeverityAvailabilityMask(
  P2VAR(Dem_DTCSeverityType, AUTOMATIC, DCM_APPL_DATA) DTCSeverityMask);

#if (DCM_J1979_2_SUPPORT == STD_ON)
/* Trace: DCM_19792_1A_08 */
extern FUNC(Std_ReturnType, DCM_CODE) IDem_SetDTCFilterByExtendedDataRecordNumber(
  Dem_DTCFormatType DTCFormat, 
  uint8 ExtendedDataRecordnumber,
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) pErrorCode);

/* Trace: DCM_19792_56_13 */
extern FUNC(Std_ReturnType, DCM_CODE) IDem_SetDTCFilterByReadinessGroup(
  Dem_DTCFormatType DTCFormat, 
  Dem_EventOBDReadinessGroupType ReadinessGroupNumber,
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) pErrorCode);
#endif /* DCM_J1979_2_SUPPORT == STD_ON */

#define DCM_STOP_SEC_CODE
#include "MemMap.h"

#endif /* DCM_DEMINTERFACES_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
