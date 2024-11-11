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
**  SRC-MODULE: Dem_J1939.h                                                   **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostic Event Manager                              **
**                                                                            **
**  PURPOSE   : Provision of extern declarations of APIs and Service ID       **
**              macros                                                        **
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
** 1.0.6.0   21-Oct-2022   LanhLT        #CP44-853                            **
** 1.0.1.0   07-May-2021   HaoLT6        R44-Redmine #18724                   **
** 1.0.0     26-Feb-2021   EK Kim        Initial version                      **
*******************************************************************************/

#ifndef DEM_J1939_H
#define DEM_J1939_H

/* 
   polyspace:begin<MISRA-C:5.1:Not a defect:Justify with annotations>
   Number of character is AUTOSAR standard
   polyspace:begin<MISRA-C:1.1:Not a defect:Justify with annotations>
   Not a defect
   polyspace:begin<MISRA-C:19.7:Not a defect:Justify with annotations>
   Not a defect
   polyspace:begin<MISRA-C:8.8:Not a defect:Justify with annotations>
   Not a defect
*/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Dem_Cfg.h"     /* Dem_PBcfg.h [SWS_Dem_00151 */
#include "Dem_Types.h"
#include "Dem_PCTypes.h" 
#include "Dem_Config.h"
#include "Dem_J1939Types.h"



/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
#if (DEM_J1939_SUPPORT == STD_ON)


/* Service ID for Dem_J1939DcmSetDTCFilter */
#define DEM_J1939DCMSETDTCFILTER_SID                               ((uint8)0x90)
/* Service ID for Dem_J1939DcmGetNumberOfFilteredDTC */
#define DEM_J1939DCMGETNUMBEROFFILTEREDDTC_SID                     ((uint8)0x91)
/* Service ID for Dem_J1939DcmGetNextFilteredDTC */
#define DEM_J1939DCMGETNEXTFILTEREDDTC_SID                         ((uint8)0x92)
/* Service ID for Dem_J1939DcmFirstDTCwithLampStatus */
#define DEM_J1939DCMFIRSTDTCWITHLAMPSTATUS_SID                     ((uint8)0x93)
/* Service ID for J1939DcmGetNextDTCwithLampStatus */
#define DEM_J1939DCMGETNEXTDTCWITHLAMPSTATUS_SID                   ((uint8)0x94)
/* Service ID for J1939DcmGetNextDTCwithLampStatus */
#define DEM_J1939DCMCLEARDTC_SID                                   ((uint8)0x95)
/* Service ID for Dem_J1939DcmSetFreezeFrameFilter */
#define DEM_J1939DCMSETFREEZEFRAMEFILTER_SID                       ((uint8)0x96)
/* Service ID for Dem_J1939DcmGetNextFreezeFrame */
#define DEM_J1939DCMGETNEXTFREEZEFRAME_SID                         ((uint8)0x97)
/* Service ID for Dem_J1939DcmGetNextFreezeFrame */
#define DEM_J1939DCMGETNEXTSPNINFREEZEFRAME_SID                    ((uint8)0x98)
/* Service ID for Dem_J1939DcmSetRatioFilter */
#define DEM_J1939DCMSETRATIOFILTER_SID                             ((uint8)0x99)
/* Service ID for Dem_J1939DcmGetNextRatio */
#define DEM_J1939DCMGETNEXTRATIO_SID                               ((uint8)0x9a)
/* Service ID for Dem_J1939DcmReadDiagnosticReadiness1 */
#define DEM_J1939DCMREADDIAGNOSTICREADINESS1_SID                   ((uint8)0x9b)
/* Service ID for Dem_J1939DcmReadDiagnosticReadiness2 */
#define DEM_J1939DCMREADDIAGNOSTICREADINESS2_SID                   ((uint8)0x9c)
/* Service ID for Dem_J1939DcmReadDiagnosticReadiness3 */
#define DEM_J1939DCMREADDIAGNOSTICREADINESS3_SID                   ((uint8)0x9d)

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"

/* 
  polyspace:begin<MISRA-C:16.4:Not a defect:Justify with annotations>
  Not a defect
*/
  /* For J1939 */
extern FUNC(Std_ReturnType, DEM_CODE)
Dem_J1939DcmSetDTCFilter(
  Dem_J1939DcmDTCStatusFilterType DTCStatusFilter,
  Dem_DTCKindType DTCKind,
  Dem_DTCOriginType DTCOrigin,
  uint8 ClientId,
  Dem_J1939DcmLampStatusType* LampStatus);
  
extern FUNC(Std_ReturnType, DEM_CODE)
Dem_J1939DcmGetNumberOfFilteredDTC(
  uint16* NumberOfFilteredDTC,
  uint8 ClientId);

extern FUNC(Std_ReturnType, DEM_CODE)
Dem_J1939DcmGetNextFilteredDTC(
  uint32* J1939DTC,
  uint8* OccurenceCounter,
  uint8 ClientId);

extern Std_ReturnType Dem_J1939DcmClearDTC(
  Dem_J1939DcmSetClearFilterType DTCTypeFilter,
  Dem_DTCOriginType DTCOrigin,
  uint8 ClientId);

extern Std_ReturnType
Dem_J1939DcmSetFreezeFrameFilter(
  Dem_J1939DcmSetFreezeFrameFilterType FreezeFrameKind,
  uint8 ClientId);

extern Std_ReturnType
Dem_J1939DcmGetNextFreezeFrame(
  uint32* J1939DTC,
  uint8* OccurenceCounter,
  uint8* DestBuffer,
  uint16* BufSize,
  uint8 ClientId);


extern FUNC(Std_ReturnType, DEM_CODE)
Dem_J1939DcmGetNextDTCwithLampStatus( 
  Dem_J1939DcmLampStatusType* LampStatus, 
  uint32* J1939DTC, 
  uint8* OccurenceCounter,
  uint8 ClientId);

extern FUNC(void, DEM_CODE) Dem_J1939MainFunction(uint8 ClientId);


extern FUNC(void, DEM_CODE) Dem_EvMem_InitChronologicalOrder(
  Dem_DTCOriginType DTCOrigin);

extern FUNC(void, DEM_CODE) Dem_EvMem_DelChronologicalOrder(
  const Dem_DTCOriginType DTCOrigin,  
  const Dem_NumOfEventMemoryEntryType MemLocation);

extern FUNC(void, DEM_CODE) Dem_EvMem_AddNewChronologicalOrder(
  const Dem_DTCOriginType DTCOrigin,  
  const Dem_NumOfEventMemoryEntryType MemLocation);

extern  FUNC(Std_ReturnType, DEM_CODE)
Dem_J1939DcmSetRatioFilter(
  uint16* IgnitionCycleCounter,
  uint16* OBDMonitoringConditionsEncountered,
  uint8 ClientId);

extern  FUNC(Std_ReturnType, DEM_CODE)
Dem_J1939DcmGetNextFilteredRatio(
  uint32* SPN,
  uint16* Numerator,
  uint16* Denominator,
  uint8 ClientId);

#if(DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
#if (DEM_J1939_READINESS1_SUPPORT == STD_ON)
extern FUNC(Std_ReturnType, DEM_CODE) Dem_J1939DcmReadDiagnosticReadiness1(
  Dem_J1939DcmDiagnosticReadiness1Type* DataValue,
  uint8 ClientId );
#endif
#endif

#if(DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
#if (DEM_J1939_READINESS2_SUPPORT == STD_ON)
extern FUNC(Std_ReturnType, DEM_CODE) Dem_J1939DcmReadDiagnosticReadiness2(
  Dem_J1939DcmDiagnosticReadiness2Type* DataValue,
  uint8 ClientId );
#endif
#endif

#if(DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
#if (DEM_J1939_READINESS3_SUPPORT == STD_ON)
extern FUNC(Std_ReturnType, DEM_CODE) Dem_J1939DcmReadDiagnosticReadiness3(
  Dem_J1939DcmDiagnosticReadiness3Type* DataValue,
  uint8 ClientId );
#endif
#endif

extern  FUNC(Std_ReturnType, DEM_CODE)
Dem_J1939DcmGetNextSPNInFreezeFrame(
  uint32* SPNSupported,
  uint8* SPNDataLength,
  uint8 ClientId);

extern FUNC(void, DEM_CODE) Dem_J1939DcmFirstDTCwithLampStatus(uint8 ClientId);
/* polyspace:end<MISRA-C:16.4:Not a defect:Justify with annotations>
 * Not a defect */


#define DEM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
**                  NVRAM Block Id Permanent RAM addresses                     *
*******************************************************************************/
/* 
   polyspace:end<MISRA-C:5.1:Not a defect:Justify with annotations>
   Number of character is AUTOSAR standard
   polyspace:end<MISRA-C:1.1:Not a defect:Justify with annotations>
   Not a defect
   polyspace:end<MISRA-C:19.7:Not a defect:Justify with annotations>
   Not a defect
   polyspace:end<MISRA-C:8.8:Not a defect:Justify with annotations>
   Not a defect
*/
#endif
#endif /* DEM_J1939_H */


/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
