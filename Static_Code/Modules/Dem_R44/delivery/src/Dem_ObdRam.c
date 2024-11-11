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
**  SRC-MODULE: Dem_ObdRam.c                                                  **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostics Event Manager Module                      **
**                                                                            **
**  PURPOSE   : Defining Global Variables                                     **
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


/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Dem_ObdRam.h" /* Dem global Ram variables header file for OBD */

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
VAR(Dem_EventMemoryEntryType, DEM_VAR_NOINIT) Dem_PermanentEventMemory
  [DEM_MAX_NUMBER_EVENT_ENTRY_PER];
#endif

#define DEM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "MemMap.h"


/*************************************************************************
 * VAR CLEARED_32
 ************************************************************************/

#define DEM_START_SEC_VAR_CLEARED_32
#include "MemMap.h"

/* Used to Store the Mil on time [min] */
VAR(uint32, DEM_VAR) Dem_GulTimeSinceMilOn;  

/* Used to calculate time in milli sec */
VAR(uint32, DEM_VAR) Dem_GulDemTimeObdmsCount;
/* Used to Store whether event is disabled or not for pid41e */
VAR(uint32, DEM_VAR) Dem_GulEventIdDisabled;
/* Used to Store time since clear dtc is called count in min */
VAR(uint32, DEM_VAR) Dem_GulDemClearTimeCount;

VAR(uint32, DEM_VAR) Dem_OBDOldDistanceInfo;
VAR(uint32, DEM_VAR) Dem_OBDOldEngStartInfo;

#define DEM_STOP_SEC_VAR_CLEARED_32
#include "MemMap.h"

/*************************************************************************
 * CLEARED_16
 ************************************************************************/

#define DEM_START_SEC_VAR_CLEARED_16
#include "MemMap.h"


#if (DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT)
/* Store the value of ignition counter */
VAR(uint16, DEM_VAR) Dem_GusIgnitionCylCnt;

/* Pointer point the memory location in which Obd event is stored */
VAR(uint16, DEM_VAR) Dem_GusObdDtcFirstStored;

/* Pointer point the memory location in which Obd event is stored */
VAR(uint16, DEM_VAR) Dem_GusEventstoredinPermanent;

/* Store the value of General Denominator*/
VAR(uint16, DEM_VAR) Dem_GusGeneralDenominator;

#if (DEM_NUMBER_OF_RATIO_INFO > DEM_ZERO)
/* Trace: DEM_OBD_09_18 */
/* Store the value of Denominator, Last Array is Always 0 */
VAR(uint16, DEM_VAR) Dem_GaaIumprDenominator[DEM_NUMBER_OF_RATIO_INFO + DEM_ONE];
/* Store the value of Numerator, Last Array is Always 0 */
VAR(uint16, DEM_VAR) Dem_GaaIumprNumerator[DEM_NUMBER_OF_RATIO_INFO + DEM_ONE];
/* Minimum Ratio per IUMPR Group */
VAR(uint16, DEM_VAR) Dem_GaaIumprMinimumRatioIDPerGroup[DEM_IUMPR_MAX];
#endif


/* Used to Store the warm up cycle count */
VAR(uint16, DEM_VAR) Dem_GusWarmUpCycleCount;

#if (DEM_OBD_CENTRALIZED_PID_21_HANDLING == STD_ON)
VAR(uint16, DEM_VAR) Dem_DataOfPID21;
#endif

/*Data PID 31*/
VAR(uint16, DEM_VAR) Dem_DataOfPID31;
/*Data PID 4D*/
VAR(uint16, DEM_VAR) Dem_DataOfPID4D;
/*Data PID 4E*/
VAR(uint16, DEM_VAR) Dem_DataOfPID4E;

/*Class B1 counter*/
VAR(uint16, DEM_VAR) Dem_WWHOBDB1Counter;

/*Class B1 counter in previous operation cycle*/
VAR(uint16, DEM_VAR) Dem_PreWWHOBDB1Counter;

/*Continuous-MI counter*/
VAR(uint16, DEM_VAR) Dem_WWHOBDConMICont;

/* Highest B1 counter*/
VAR(uint16, DEM_VAR) Dem_WWHOBDHighestB1Cont;
#endif



#define DEM_STOP_SEC_VAR_CLEARED_16
#include "MemMap.h"

/*************************************************************************
 * CLEARED_8
 ************************************************************************/

#define DEM_START_SEC_VAR_CLEARED_8
#include "MemMap.h"

/* Activation Mode */
VAR(uint8, DEM_VAR) Dem_WWHOBDActMode;

/* Previous Activation Mode */
VAR(uint8, DEM_VAR) Dem_WWHOBDPreActMode;

/* Number of Cycle to Continuous-MI is again commanded on */
VAR(uint8, DEM_VAR) Dem_WWHOBDNumCycleCmd;

/* Number of Cycle which no Class B1 event have been detected.  */
VAR(uint8, DEM_VAR) Dem_WWHOBDNumCycleNoB1Class;

/* Current Obd Memory ID  */
VAR(uint8, DEM_VAR) Dem_ObdMemoryId;

/* DEM_GEN_06 */
/* Used to calculate Mil Off->On Check  */
VAR(uint8, DEM_VAR) Dem_GucPreMilonFlag;

/* Used to calculate Mil status of pid01 */
VAR(uint8, DEM_VAR) Dem_GucMilonFlag;

/* Used to calculate Mil status */
VAR(uint8, DEM_VAR) Dem_MilonStatus;

/* Used to indicate whether MIL is re-active or not */
VAR(uint8, DEM_VAR) Dem_GucMilActivatedCnt;
/* Used to indicate whether MIL is re-active or not */
VAR(uint8, DEM_VAR) Dem_GucPreMilActivatedCnt;

/* Used to calculate Warm up cycle count when Mil status is off */
VAR(uint8, DEM_VAR) Dem_GucWarmUpCycleCountMil;

/* Used to calculate Warm up cycle count when DTC is cleared */
VAR(uint8, DEM_VAR) Dem_GucWarmUpCycleCountDtcClear;

#if (DEM_MAX_NUMBER_EVENT_ENTRY_PER > DEM_ZERO)
/* Permanent Event Memory variable */
VAR(uint8, DEM_VAR) Dem_PermanentEventMemoryState
  [DEM_MAX_NUMBER_EVENT_ENTRY_PER];
#endif

#if (DEM_NUMBER_OF_RATIO_INFO > DEM_ZERO)
VAR(uint8, DEM_VAR) Dem_GusRatioDenCondState[DEM_IUMPR_MAX_CONDITION_NUMBER];
#if (DEM_J1979_2_OBD_ON_UDS == STD_ON)
/* Trace: DEM_19792_06_11 */
/* Store the value of Monitor Activity Denominator (MAD) */
VAR(uint8, DEM_VAR) Dem_GaaMonitorActivityDenominator[DEM_NUMBER_OF_RATIO_INFO];
/* Store the value of Monitor Activity Numerator (MAN) */
VAR(uint8, DEM_VAR) Dem_GaaMonitorActivityNumerator[DEM_NUMBER_OF_RATIO_INFO];
/* Store the value of Monitor Activity RATIO (MAR) */
VAR(uint8, DEM_VAR) Dem_GaaMonitorActivityRatio[DEM_NUMBER_OF_RATIO_INFO];

/* Trace: DEM_19792_06_12 */
/* Store the indicator of Monitor Activity Denominator whether it is updated in one Operation
 * Cycle*/
VAR(uint8, DEM_VAR) Dem_GaaMonitorActivityDenominatorNeedCountedCycleEnd[DEM_NUMBER_OF_RATIO_INFO];
/* Store the indicator of Monitor Activity Numerator whether it is updated in one Operation
 * Cycle*/
VAR(uint8, DEM_VAR) Dem_GaaMonitorActivityNumeratorNeedCountedCycleEnd[DEM_NUMBER_OF_RATIO_INFO];

#endif /* J19792 */
#endif

#define DEM_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h"

/*****************************************************************************/
/* VAR CLEARED BOOLEAN                                                       */
/*****************************************************************************/

#define DEM_START_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"

/* Current operation cycle Id Value */
VAR(boolean, DEM_VAR) Dem_ObdEventStored;
/* Used to calculate Mil status of pid01 */
VAR(boolean, DEM_VAR) Dem_GblMilStarted;
/* Used to calculate Clear Dtc time */
VAR(boolean, DEM_VAR) Dem_GblDtcCleared;


/* Used to Store the pto status */
VAR(boolean, DEM_VAR) Dem_GblPtoStatus;
/* Used to calculate time since clear dtc is called */
VAR(boolean, DEM_VAR) Dem_GblClearTimeStartObd;

#if (DEM_NUMBER_OF_RATIO_INFO > DEM_ZERO)
VAR(boolean, DEM_VAR) Dem_GblRatioInit;
/* Trace: DEM_OBD_09_19 */
/* Store the indicator of Denominator whether it is updated in one Operation
 * Cycle*/
VAR(boolean, DEM_VAR) Dem_GaaIumprDenominatorIsCounted[DEM_NUMBER_OF_RATIO_INFO];
VAR(boolean, DEM_VAR) Dem_GaaIumprNumeratorIsCounted[DEM_NUMBER_OF_RATIO_INFO];
/* Minimum Ratio Update Flag Per IUMPR Group */
VAR(boolean, DEM_VAR) Dem_GaaIumprUpdateFlagPerGroup[DEM_IUMPR_MAX];

#endif

#define DEM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"


#define DEM_START_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h"

#if (DEM_NUMBER_OF_DTRS > DEM_ZERO)
Dem_DTRDataType Dem_DtrData[DEM_NUMBER_OF_DTRS];
#endif

#define DEM_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h"



/*************************************************************************
 * CONST
 ************************************************************************/


/*****************************************************************************/

#endif /* DEM_OBD_SUPPORT != DEM_OBD_NO_OBD_SUPPORT */
/*******************************************************************************
**                       End of File                                          **
*******************************************************************************/
