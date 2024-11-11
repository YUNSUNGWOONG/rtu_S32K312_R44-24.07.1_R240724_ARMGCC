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
**  SRC-MODULE: Dem_ObdRam.h                                                  **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostics Event Manager Module                      **
**                                                                            **
**  PURPOSE   : Header file for Dem_ObdRam.c                                  **
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
** 2.1.0.0   31-Mar-2024   EK Kim        Jira #CP44-4039                      **
** 2.0.0.0   31-Dec-2023   EK Kim        Jira #CP44-1515 #CP44-3198 #CP44-3298**
** 1.0.1.0   07-May-2021   HaoLT6        R44-Redmine #18724                   **
** 1.0.0     26-Feb-2021   EK Kim        Initial version                      **
*******************************************************************************/


#ifndef DEM_OBDRAM_H
#define DEM_OBDRAM_H
 
/* polyspace:begin<MISRA-C:8.12:Not a defect:Justify with annotations>
 * size of array is determined by configuration */

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Dem.h"        /* Dem module header file */
#include "NvM.h"        /* NVRAM manager symbols Header File */

#if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/


/*************************************************************************
 * VAR INIT_UNSPECIFIED
 ************************************************************************/
#define DEM_START_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h"

#define DEM_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h"

/*************************************************************************
 * NO_INIT_UNSPECIFIED == SAVED_ZONE
 ************************************************************************/
#define DEM_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "MemMap.h"

#if (DEM_MAX_NUMBER_EVENT_ENTRY_PER > DEM_ZERO)
/* Permanent Event Memory variable */
extern VAR(Dem_EventMemoryEntryType, DEM_VAR_NOINIT)
Dem_PermanentEventMemory[DEM_MAX_NUMBER_EVENT_ENTRY_PER];
#endif

#define DEM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "MemMap.h"


/*************************************************************************
 * VAR CLEARED_32
 ************************************************************************/

#define DEM_START_SEC_VAR_CLEARED_32
#include "MemMap.h"

/* Used to Store the Mil on time */
extern VAR(uint32, DEM_VAR) Dem_GulTimeSinceMilOn;
/* Used to calculate time in milli sec */
extern VAR(uint32, DEM_VAR) Dem_GulDemTimeObdmsCount;
/* Used to Store whether event is disabled or not for pid41e */
extern VAR(uint32, DEM_VAR) Dem_GulEventIdDisabled;
/* Used to Store time since clear dtc is called count in min */
extern VAR(uint32, DEM_VAR) Dem_GulDemClearTimeCount;
extern VAR(uint32, DEM_VAR) Dem_OBDOldDistanceInfo;
extern VAR(uint32, DEM_VAR) Dem_OBDOldEngStartInfo;
#define DEM_STOP_SEC_VAR_CLEARED_32
#include "MemMap.h"

/*************************************************************************
 * CLEARED_16
 ************************************************************************/

#define DEM_START_SEC_VAR_CLEARED_16
#include "MemMap.h"

/* Store the value of General Denominator*/
extern VAR(uint16, DEM_VAR) Dem_GusGeneralDenominator;
/* Store the value of ignition counter */
extern VAR(uint16, DEM_VAR) Dem_GusIgnitionCylCnt;
/* Global variable is used for store the first obd dtc  */
extern VAR(uint16, DEM_VAR) Dem_GusObdDtcFirstStored;
/* Pointer point the memory location in which Obd event is stored */
extern VAR(uint16, DEM_VAR) Dem_GusEventstoredinPermanent;

#if (DEM_NUMBER_OF_RATIO_INFO > 0U)
/* Trace: DEM_OBD_09_18 */
/* Store the value of Denominator, Last Array is Always 0 */
extern VAR(uint16, DEM_VAR) Dem_GaaIumprDenominator[DEM_NUMBER_OF_RATIO_INFO + DEM_ONE];
/* Store the value of Numerator, Last Array is Always 0 */
extern VAR(uint16, DEM_VAR) Dem_GaaIumprNumerator[DEM_NUMBER_OF_RATIO_INFO + DEM_ONE];
/* Minimum Ratio per IUMPR Group */
extern VAR(uint16, DEM_VAR) Dem_GaaIumprMinimumRatioIDPerGroup[DEM_IUMPR_MAX];
/* Minimum Ratio Update Flag Per IUMPR Group */
extern VAR(boolean, DEM_VAR) Dem_GaaIumprUpdateFlagPerGroup[DEM_IUMPR_MAX];
#endif /*(DEM_NUMBER_OF_RATIO_INFO > 0U)*/

/* Used to Store the warm up cycle count */
extern VAR(uint16, DEM_VAR) Dem_GusWarmUpCycleCount;

/*Class B1 counter in previous operation cycle*/
extern VAR(uint16, DEM_VAR) Dem_PreWWHOBDB1Counter;

#if ((DEM_OBD_CENTRALIZED_PID_21_HANDLING == STD_ON) && \
     (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT))
/* Data of PID21*/
extern VAR(uint16, DEM_VAR) Dem_DataOfPID21;
#endif

#if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
/* Data of PID31*/
extern VAR(uint16, DEM_VAR) Dem_DataOfPID31;
/* Data of PID4D*/
extern VAR(uint16, DEM_VAR) Dem_DataOfPID4D;
/* Data of PID4E*/
extern VAR(uint16, DEM_VAR) Dem_DataOfPID4E;

/*Class B1 counter*/
extern VAR(uint16, DEM_VAR) Dem_WWHOBDB1Counter;

/*Continuous-MI counter*/
extern VAR(uint16, DEM_VAR) Dem_WWHOBDConMICont;

/* Highest B1 counter*/
extern VAR(uint16, DEM_VAR) Dem_WWHOBDHighestB1Cont;
#endif

#define DEM_STOP_SEC_VAR_CLEARED_16
#include "MemMap.h"

/*************************************************************************
 * CLEARED_8
 ************************************************************************/

#define DEM_START_SEC_VAR_CLEARED_8
#include "MemMap.h"

/* Activation Mode */
extern VAR(uint8, DEM_VAR) Dem_WWHOBDActMode;

/* Previous Activation Mode */
extern VAR(uint8, DEM_VAR) Dem_WWHOBDPreActMode;

/* Number of Cycle to Continuous-MI is again commanded on */
extern VAR(uint8, DEM_VAR) Dem_WWHOBDNumCycleCmd;

/* Number of Cycle which no Class B1 event have been detected.  */
extern VAR(uint8, DEM_VAR) Dem_WWHOBDNumCycleNoB1Class;

/* Current Obd Memory ID  */
extern VAR(uint8, DEM_VAR) Dem_ObdMemoryId;

/* Used to indicate whether MIL is re-active or not */
extern VAR(uint8, DEM_VAR) Dem_GucMilActivatedCnt;
/* Used to indicate whether MIL is re-active or not */
extern VAR(uint8, DEM_VAR) Dem_GucPreMilActivatedCnt;

/* DEM_GEN_06 */
/* Used to calculate Mil Off->On Check  */
extern VAR(uint8, DEM_VAR) Dem_GucPreMilonFlag;

/* Used to calculate Mil status of pid01 */
extern VAR(uint8, DEM_VAR) Dem_GucMilonFlag;
/* Used to calculate Mil status */
extern VAR(uint8, DEM_VAR) Dem_MilonStatus;
/* Used to calculate Warm up cycle count when Mil status is off */
extern VAR(uint8, DEM_VAR) Dem_GucWarmUpCycleCountMil;
/* Used to calculate Warm up cycle count when DTC is cleared */
extern VAR(uint8, DEM_VAR) Dem_GucWarmUpCycleCountDtcClear;

#if (DEM_MAX_NUMBER_EVENT_ENTRY_PER > DEM_ZERO)
/* Permanent Event Memory variable */
extern VAR(uint8, DEM_VAR)
  Dem_PermanentEventMemoryState[DEM_MAX_NUMBER_EVENT_ENTRY_PER];
#endif

#if (DEM_NUMBER_OF_RATIO_INFO > 0U)
#if (DEM_J1979_2_OBD_ON_UDS == STD_ON)
/* Trace: DEM_19792_06_11 */
/* Store the value of Monitor Activity Denominator (MAD - General Denominator) */
extern VAR(uint8, DEM_VAR) Dem_GaaMonitorActivityDenominator[DEM_NUMBER_OF_RATIO_INFO];
/* Store the value of Monitor Activity Numerator (MAN) */
extern VAR(uint8, DEM_VAR) Dem_GaaMonitorActivityNumerator[DEM_NUMBER_OF_RATIO_INFO];
/* Store the value of Monitor Activity RATIO (MAR) */
extern VAR(uint8, DEM_VAR) Dem_GaaMonitorActivityRatio[DEM_NUMBER_OF_RATIO_INFO];

/* Trace: DEM_19792_06_12 */
/* Store the indicator of Monitor Activity Denominator whether it is updated in one Operation Cycle */
extern VAR(uint8, DEM_VAR) Dem_GaaMonitorActivityDenominatorNeedCountedCycleEnd[DEM_NUMBER_OF_RATIO_INFO];
/* Store the indicator of Monitor Activity Numerator whether it is updated in one Operation Cycle */
extern VAR(uint8, DEM_VAR) Dem_GaaMonitorActivityNumeratorNeedCountedCycleEnd[DEM_NUMBER_OF_RATIO_INFO];

#endif /* J19792 */
#endif /*(DEM_NUMBER_OF_RATIO_INFO > 0U)*/

#define DEM_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h"

/*****************************************************************************/
/* VAR CLEARED BOOLEAN                                                       */
/*****************************************************************************/

#define DEM_START_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"

#if (DEM_NUMBER_OF_RATIO_INFO > DEM_ZERO)
/* Store the indicator of Denominator whether it is updated in one Operation
 * Cycle*/
extern VAR(boolean, DEM_VAR) Dem_GaaIumprDenominatorIsCounted[DEM_NUMBER_OF_RATIO_INFO];
/* Store the indicator of Numerator whether it is updated in one Operation
 * Cycle*/
extern VAR(boolean, DEM_VAR) Dem_GaaIumprNumeratorIsCounted[DEM_NUMBER_OF_RATIO_INFO];

#endif


/* Current operation cycle Id Value */
extern VAR(boolean, DEM_VAR) Dem_ObdEventStored;
/* Used to calculate Mil status of pid01 */
extern VAR(boolean, DEM_VAR) Dem_GblMilStarted;
/* Used to calculate Clear Dtc time */
extern VAR(boolean, DEM_VAR) Dem_GblDtcCleared;
/* Used to Store the pto status */
extern VAR(boolean, DEM_VAR) Dem_GblPtoStatus;
/* Used to calculate time since clear dtc is called */
extern VAR(boolean, DEM_VAR) Dem_GblClearTimeStartObd;
#if (DEM_NUMBER_OF_RATIO_INFO > DEM_ZERO)
/* Store the value of General Denominator*/
extern VAR(boolean, DEM_VAR) Dem_GblRatioInit;
#endif

#if (DEM_IUMPR_MAX_CONDITION_NUMBER > DEM_ZERO)
extern VAR(uint8, DEM_VAR)
  Dem_GusRatioDenCondState[DEM_IUMPR_MAX_CONDITION_NUMBER];
#endif

#define DEM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"


#define DEM_START_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h"

#if (DEM_NUMBER_OF_DTRS > DEM_ZERO)
extern Dem_DTRDataType Dem_DtrData[DEM_NUMBER_OF_DTRS];
#endif

#define DEM_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h"

/*************************************************************************
 * CONST
 ************************************************************************/
 
#define DEM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern CONST(Dem_OBDClassType, DEM_CONST) Dem_GaaObd[DEM_ONE];
#define DEM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"  

/*****************************************************************************/

/* polyspace:end<MISRA-C:8.12:Not a defect:Justify with annotations>
 * size of array is determined by configuration */
#endif /* DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT */
#endif /* DEM_OBDRAM_H */

/*******************************************************************************
**                       End of File                                          **
*******************************************************************************/

