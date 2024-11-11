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
**  SRC-MODULE: Dem_J1939Types.h                                              **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostic Event Manager                              **
**                                                                            **
**  PURPOSE   : This file contains the type definitions and macro             **
**              definitions of DEM module                                     **
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

#ifndef DEM_J1939TYPES_H
#define DEM_J1939TYPES_H

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
#include "Rte_Dem_Type.h"   /* Rte Header File for Dem Types */
#include "Std_Types.h"
#include "Dem_Cfg.h"
#include "Dem_Types.h"


#if (DEM_J1939_SUPPORT == STD_ON)

/*******************************************************************************
**                         Global Data Types                                  **
*******************************************************************************/
  /*For J1939 */
typedef uint8 Dem_ReturnGetNextFilteredElementType;
#define DEM_FILTERED_NO_MATCHING_ELEMENT                          ((uint8)0x01) 
#define DEM_FILTERED_BUFFER_TOO_SMALL                             ((uint8)0x03)

#ifndef DEM_SWCGEN
typedef uint8 Dem_J1939DcmDTCStatusFilterType;
#endif
#define DEM_J1939DTC_ACTIVE                                       0
#define DEM_J1939DTC_PREVIOUSLY_ACTIVE                            1
#define DEM_J1939DTC_PENDING                                      2
#define DEM_J1939DTC_PERMANENT                                    3
#define DEM_J1939DTC_CURRENTLY_ACTIVE                             4

/*typedef uint16  Dem_J1939DcmLampStatusType;*/

#define DEM_J1939LAMP_SLOW_FLASH                                  0x00
#define DEM_J1939LAMP_FAST_FLASH                                  0x01
#define DEM_J1939LAMP_DO_NOT_FLASH                                0x03
#define DEM_J1939LAMP_ON                                          0x01
#define DEM_J1939LAMP_OFF                                         0x00
#define DEM_J1939LAMP_NOT_AVAILABLE                               0xFFU

#ifndef DEM_SWCGEN
typedef uint8  Dem_J1939DcmSetClearFilterType; 
#endif
/* active DTCs */
#define DEM_J1939DTC_CLEAR_ACTIVE                                 0
/* previously active DTCs */
#define DEM_J1939DTC_CLEAR_PREVIOUSLY_ACTIVE                      1
/* active and previously active DTCs */
#define DEM_J1939DTC_CLEAR_ACTIVE_AND_PREVIOUSLY_ACTIVE           2

#ifndef DEM_SWCGEN
typedef uint8  Dem_J1939DcmSetFreezeFrameFilterType; 
#endif
/* FreezeFrame (DM04) */
#define DEM_J1939DCM_FREEZEFRAME                                  0
/* ExpandedFreezeFrame(DM25) */
#define DEM_J1939DCM_EXPANDED_FREEZEFRAME                         1
/* SPNs in Expanded-FreezeFrame (DM24) */
#define DEM_J1939DCM_SPNS_IN_EXPANDED_FREEZEFRAME                 2


#define DEM_J1939DCM_FILTEREDDTC_BY_CHRONOLOGICAL_ORDER           (0)
#define DEM_J1939DCM_FILTEREDDTC_BY_EVENTIDD                      (1)

#define DEM_J1939RDY_MAX_DTC_NUMBER                         0xFAU
#define DEM_J1939RDY_MAX_WARMUP_NUMBER                      0xFAU
#define DEM_J1939RDY_MAX_DISTANCE                           0xFAFFU
#define DEM_J1939RDY_MAX_TIME                               0xFAFFU

#ifndef DEM_SWCGEN
#if (DEM_J1939_SUPPORT == STD_ON)
typedef struct STag_Dem_J1939DcmLampStatusType
{
  /* lamp status */
  uint8 LampStatus;
  /* flash lamp status */
  uint8 FlashLampStatus;
} Dem_J1939DcmLampStatusType;
#endif
#endif
/* types of the J1939FreezeFrame
 * @IF_REQ : to Dem_SizeOfJ1939FreezeFrameClassType,
 * Dem_NumOfJ1939FreezeFrameClassType */
typedef uint16          Dem_SizeOfJ1939FreezeFrameClassType;
typedef uint16          Dem_NumOfJ1939FreezeFrameClassType;
/* @IF_REQ : to Dem_NumOfSpnDataElementClassType,
 * Dem_SizeOfSpnDataElementClassType*/
typedef uint16          Dem_SpnIdentifierType;
typedef uint8           Dem_NumOfSpnDataElementType;
typedef uint8           Dem_SizeOfSpnDataElementType;
/* types of the SPN Class */
typedef uint8           Dem_NumOfSpnClassType;
typedef uint16          Dem_SizeOfSpnClassType;
typedef uint32          Dem_SizeOfJ1939FreezeFrameDataType;

/*******************************************************************************
 **                 Structure for combined DTC                                **
 *******************************************************************************/
typedef struct STag_Dem_J1939LampType
{
  uint16 MilId;
  uint16 RedStopLampId;
  uint16 WarningLampId;
  uint16 ProtectLampId;
} Dem_J1939LampType;


typedef struct STag_Dem_J1939DTCFilterStateType {
  Dem_DTCKindType j1939_DTCKind;
  Dem_DTCOriginType j1939_DTCOrigin;
  Dem_J1939DcmDTCStatusFilterType j1939_DTCStatusFilter;
  uint8 j1939_JobAction;
  uint16  j1939_NumOfFilteredDTC;
  uint8 FilteringType;
} Dem_J1939DTCFilterStateType;

typedef struct STag_Dem_J1939DcmDiagnosticReadiness1Type {
  uint8 ActiveTroubleCodes;
  uint8 PreviouslyActiveDiagnosticTroubleCodes;
  uint8 OBDCompliance;
  uint8 ContinuouslyMonitoredSystemsSupport_Status;
  uint8 NonContinuouslyMonitoredSystemsSupport5;
  uint8 NonContinuouslyMonitoredSystemsSupport6;
  uint8 NonContinuouslyMonitoredSystemsStatus7;
  uint8 NonContinuouslyMonitoredSystemsStatus8;
} Dem_J1939DcmDiagnosticReadiness1Type;

typedef struct STag_Dem_J1939DcmDiagnosticReadiness2Type {
  uint16 DistanceTraveledWhileMILisActivated;
  uint16 DistanceSinceDTCsCleared;
  uint16 MinutesRunbyEngineWhileMILisActivated;
  uint16 TimeSinceDiagnosticTroubleCodesCleared;
} Dem_J1939DcmDiagnosticReadiness2Type;

typedef struct STag_Dem_J1939DcmDiagnosticReadiness3Type {
  uint16 TimeSinceEngineStart;
  uint8 NumberofWarmupsSinceDTCsCleared;
  uint8 ContinuouslyMonitoredSystemsEnableCompletedStatus;
  uint8 NonContinuouslyMonitoredSystemsEnableStatus5;
  uint8 NonContinuouslyMonitoredSystemsEnableStatus6;
  uint8 NonContinuouslyMonitoredSystems7;
  uint8 NonContinuouslyMonitoredSystems8;
} Dem_J1939DcmDiagnosticReadiness3Type;

#endif

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
/* _DEM_TYPES_H */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
