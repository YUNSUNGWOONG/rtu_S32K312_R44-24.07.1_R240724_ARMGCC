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
**  SRC-MODULE: Dem_Obd.h                                                     **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostic Event Manager                              **
**                                                                            **
**  PURPOSE   : C header for Dem_Obd.c                                        **
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
** 1.0.1.0   07-May-2021   HaoLT6        R44-Redmine #18724                   **
** 1.0.0     26-Feb-2021   EK Kim        Initial version                      **
*******************************************************************************/

#ifndef DEM_OBD_H
#define DEM_OBD_H
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Dem_ObdRam.h"

/*******************************************************************************
**                      Macro Section                                         **
*******************************************************************************/
/* @Trace: SWS_Dem_00755
 * The Dem shall only support a linear mapping, i.e. only support
 * values for the coefficients b, c, and f.
 * */
/* @Trace: SWS_Dem_00758
 * The Dem shall support a conversion of the ECUinternal resolution into
 * the standardized external uint16 size and resolution according to the
 * configured and standardized UaSID. For that reason, the conversion
 * formula is configured per DTR. It is assumed that the conveyed parameter
 * of the API call contain the values in the internal size and resolution.
 * The Dem does offer sint32 as parameter for that reason to cover uint16
 * as well as sint16 (or even sint32) internal data types. */
#define DEM_DTR_INSIDE         (0x00U)
#define DEM_DTR_OUTSIDE_MIN    (0x01U)
#define DEM_DTR_OUTSIDE_MAX    (0x02U)

/* Trace: DEM_OBD_09_10 */
#define DEM_PID01_CALC          (0x01U)
#define DEM_PID41_CALC          (0x41U)

/* Trace: DEM_19792_06_10 */
#define DEM_MONITOR_ACTIVITY_INIT           (0x00U)
#define DEM_MONITOR_ACTIVITY_ALLBYTE           (DEM_MONITOR_ACTIVITY_NUM_INCREMENT | \
                                                DEM_MONITOR_ACTIVITY_NUM_INHIBIT)
#define DEM_MONITOR_ACTIVITY_NUM_INCREMENT  DEM_BIT0_MASK1
#define DEM_MONITOR_ACTIVITY_NUM_INHIBIT    DEM_BIT1_MASK1
#define DEM_MONITOR_ACTIVITY_DEN_INCREMENT  DEM_BIT0_MASK1
#define DEM_MONITOR_ACTIVITY_DEN_INHIBIT    DEM_BIT1_MASK1

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
#define DEM_START_SEC_CODE
#include "MemMap.h"


#if(DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)

extern FUNC(void, DEM_CODE) Dem_InitOBD(void);
extern FUNC(void, DEM_CODE) Dem_MainFunctionOBD(void);



#if (DEM_NUMBER_OF_INDICATORS > DEM_ZERO)
extern FUNC(void, DEM_CODE)
Dem_SetMalfuntionOnOff(void);
#endif

#if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
extern FUNC(Std_ReturnType, DEM_CODE) Dem_GetReadDataOfPID(
  Dem_EventMemoryEntryCPType entry,
  P2VAR(uint8, AUTOMATIC, DEM_VAR) DestBuffer,
  const boolean ReportTotalPid,
  const Dem_PidIdentifierType PidIdentifier,
  const boolean ReportTotalDataElement,
  const Dem_NumOfDataElementClassType DataElementIndexOfPID);
#endif

/* Trace: DEM_OBD_09_10 */
extern FUNC(void, DEM_CODE) Dem_CalcReadinessPIDValue(
  VAR(uint8, DEM_VAR) LucPIDType,
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA) PIDValue,
  VAR(uint8, DEM_VAR) LusByteValue,
  VAR(uint8, DEM_VAR) LucOBDReadinessGrp);

extern FUNC(void, DEM_CODE) Dem_CalcPID41_34(
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA) PID41Value);

/* Trace: DEM_OBD_01_03 */
extern FUNC(void, DEM_CODE) Dem_CalcPID41_ByteC_ByteD(
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA) PID41Value);

extern FUNC(Std_ReturnType, DEM_CODE) Dem_ReadDataOfTimeEngineStart(
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA) PIDValue);

extern FUNC(Std_ReturnType, DEM_CODE) Dem_GetPIDDataOnRequest(
  P2CONST(Dem_EventMemoryEntryType, AUTOMATIC, DEM_APPL_CONST)LpEventMemory,
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA)DestBuffer,
  VAR(uint8, DEM_VAR) LucEventMemoryIndex,
  VAR(boolean, DEM_VAR) ReportTotalRecord,
  VAR(uint16, DEM_VAR) DataIdentifier,
  P2VAR(uint16, AUTOMATIC, DEM_APPL_DATA)LucTotalSizePid);

#if (DEM_MAX_NUMBER_OF_PID_DATAELEMENT > DEM_ZERO)

extern FUNC(Std_ReturnType, DEM_CODE)
Dem_GetSizeOfOBDFreezeFrameData(
    Dem_EventParameterCPCType event,
    CONST(boolean, DEM_VAR) ReportTotalRecord,
    CONST(Dem_PidIdentifierType, DEM_VAR) PidIdentifier,
    P2VAR(Dem_SizeOfOBDFreezeFrameDataType, AUTOMATIC, DEM_APPL_DATA) BufSize);
#endif

#if(DEM_NUMBER_OF_RATIO_INFO > DEM_ZERO)
extern FUNC(void, DEM_CODE) Dem_ProcessDen(
  VAR(Dem_EventIdType, DEM_VAR) EventId);

extern FUNC(Std_ReturnType, DEM_CODE)Dem_ProcessNum(
    Dem_EventIdType EventId,
    VAR(Dem_UdsStatusByteType, DEM_VAR) EventStatus
);

extern FUNC(Std_ReturnType, DEM_CODE)
Dem_OCStartInit(void);


#if (DEM_J1979_2_OBD_ON_UDS == STD_ON)
/* Trace: DEM_19792_06_06 */
extern FUNC(Std_ReturnType, DEM_CODE)Dem_ProcessMonitorActivityNum(
    Dem_EventIdType EventId, 
    P2VAR(boolean, AUTOMATIC, DEM_APPL_DATA) NvMDirtyFlag
);
/* Trace: DEM_19792_06_08 */
extern FUNC(void, DEM_CODE)Dem_UpdateMonitorActivityRatio(void);
/* Trace: DEM_19792_06_08 */
extern FUNC(void, DEM_CODE)Dem_InitMonitorActivityRatio(void);
#endif /* J19792 */
#endif

extern FUNC(boolean, DEM_CODE) Dem_GetMalfuntionOnOff(void);

extern FUNC(Std_ReturnType, DEM_CODE)
Dem_SetObdCycle(
VAR(uint8, DEM_VAR) LucOperationCycleId);

extern FUNC(void, DEM_CODE) Dem_ClearObdInfomation(void);

extern FUNC(Std_ReturnType, DEM_CODE) Dem_SetDataOfPID21(
    P2CONST(uint8, AUTOMATIC, DEM_APPL_DATA) PID21value );
extern FUNC(Std_ReturnType, DEM_CODE) Dem_SetDataOfPID31(
    P2CONST(uint8, AUTOMATIC, DEM_APPL_DATA) PID31value );
extern FUNC(Std_ReturnType, DEM_CODE) Dem_SetDataOfPID4D(
    P2CONST(uint8, AUTOMATIC, DEM_APPL_DATA) PID4Dvalue );
extern FUNC(Std_ReturnType, DEM_CODE) Dem_SetDataOfPID4E(
    P2CONST(uint8, AUTOMATIC, DEM_APPL_DATA) PID4Evalue );

#endif

#if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
extern FUNC(Std_ReturnType, DEM_CODE) Dem_OBDReadDataOfTimeEngineStart(
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA) Data);

extern FUNC(Std_ReturnType, DEM_CODE) Dem_OBDReadDataOfTravelDistance(
  P2VAR(uint8, AUTOMATIC, DEM_APPL_DATA) Data);
#endif

#if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
extern FUNC(Std_ReturnType, DEM_CODE) Dem_DTR_Conversion_Linear(
  sint32 Value,
  uint16 Num0,
  uint16 Num1,
  uint16 Denominator0,
  uint16 * CalcResult);
#endif

#if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
FUNC(boolean, DEM_CODE) Dem_IsValidOBDMid(uint8 Obdmid);
#endif
#define DEM_STOP_SEC_CODE
#include "MemMap.h"

#endif /* DEM_INDICATOR_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/


