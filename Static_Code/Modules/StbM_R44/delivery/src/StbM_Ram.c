/*******************************************************************************
**                                                                            **
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  This source code is permitted to be used only in projects contracted      **
**  with Hyundai Autoever, and any other use is prohibited.                   **
**  If you use it for other purposes or change the source code,               **
**  you may take legal responsibility.                                        **
**  In this case, There is no warranty and technical support.                 **
**                                                                            **
**  SRC-MODULE: StbM_Math.c                                                   **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Synchronized Time-Base Manager Module                 **
**                                                                            **
**  PURPOSE   : Provision of AUTOSAR StbM implementation specific global data **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision        Date                By              Description            **
********************************************************************************
** 1.0.3           21-Jul-2022         ThuanVT         JIRA BUGCLASSIC-152,   **
**												  	   R44-Redmine #633	      **
** 1.0.1           15-Sep-2021         SHKim           #20096                 **
** 1.0.0     	   16-Dec-2020         SHKim           Initial Version        **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

/* StbM ram data header */
#include "StbM_Ram.h"

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

#define STBM_START_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"
/* StbM initialization status */
/* @Trace: StbM_SDD_GLOBALVAR_001 */
VAR(boolean, STBM_VAR) StbM_GblInitStatus;
#define STBM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"

#define STBM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* Holds triggered customer count elapsed based on main function invocation */
#if ( 0 < STBM_NUMBER_TIME_BASES_CONFIGURED)
VAR(StbM_TimeBaseValueType, STBM_VAR) 
    StbM_GaaTimeBaseValue[STBM_NUMBER_TIME_BASES_CONFIGURED];
#else
VAR(StbM_TimeBaseValueType, STBM_VAR) 
    StbM_GaaTimeBaseValue[STBM_ONE];
#endif

#define STBM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

#define STBM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

#if ( 0 < STBM_NUMBER_LOCAL_TIME_CLOCK_CONFIGURED)
VAR(StbM_OSTimeClockValueType, STBM_VAR) 
    StbM_GaaOsTimeClockValue[STBM_NUMBER_LOCAL_TIME_CLOCK_CONFIGURED];
#else
VAR(StbM_OSTimeClockValueType, STBM_VAR) 
    StbM_GaaOsTimeClockValue[STBM_ONE];
#endif

#if ( 0 < STBM_NUMBER_ETH_TIME_CLOCK_CONFIGURED)
VAR(StbM_EthernetTimeClockValueType, STBM_VAR) 
    StbM_GaaEthernetTimeClockValue[STBM_NUMBER_ETH_TIME_CLOCK_CONFIGURED];
#else
VAR(StbM_EthernetTimeClockValueType, STBM_VAR) 
    StbM_GaaEthernetTimeClockValue[STBM_ONE];
#endif

#define STBM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

#define STBM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

#if ( 0 < STBM_NUMBER_TIME_BASES_CONFIGURED)
VAR(StbM_TimeTupleType, STBM_VAR) 
    StbM_GaaTimeTuple[STBM_NUMBER_TIME_BASES_CONFIGURED];
#else
VAR(StbM_TimeTupleType, STBM_VAR) 
    StbM_GaaTimeTuple[STBM_ONE];
#endif

#define STBM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

#define STBM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

#if ( 0 < STBM_NUMBER_NOTIFICATION_CUSTOMER_CONFIGURED)
VAR(StbM_NotificationValueType, STBM_VAR) 
    StbM_GaaNotificationValue[STBM_NUMBER_NOTIFICATION_CUSTOMER_CONFIGURED];
#else
VAR(StbM_NotificationValueType, STBM_VAR) 
    StbM_GaaNotificationValue[STBM_ONE];
#endif

#define STBM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

#define STBM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

VAR(StbM_CallBackParameterValueType, STBM_VAR) StbM_GaaCallBackParameterValue;

#define STBM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

#define STBM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

#if ( 0 < STBM_NUMBER_SYNC_TIME_RECORD_TABLE_CONFIGURED)
VAR(StbM_TimeRecordingValueType, STBM_VAR)  
    StbM_GaaSyncRecordValue[STBM_NUMBER_SYNC_TIME_RECORD_TABLE_CONFIGURED];
#else
VAR(StbM_TimeRecordingValueType, STBM_VAR)  
    StbM_GaaSyncRecordValue[STBM_ONE];
#endif

#if ( 0 < STBM_NUMBER_OFFSET_TIME_RECORD_TABLE_CONFIGURED)
VAR(StbM_TimeRecordingValueType, STBM_VAR)  
    StbM_GaaOffsetRecordValue[STBM_NUMBER_OFFSET_TIME_RECORD_TABLE_CONFIGURED];
#else
VAR(StbM_TimeRecordingValueType, STBM_VAR)  
    StbM_GaaOffsetRecordValue[STBM_ONE];
#endif

#define STBM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

#define STBM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

#if ( 0 < STBM_NUMBER_TIME_CORRECTION_CONFIGURED)
VAR(StbM_TimeCorrectionValueType, STBM_VAR)
    StbM_GaaTimeCorrectionValue[STBM_NUMBER_TIME_CORRECTION_CONFIGURED];
#else
VAR(StbM_TimeCorrectionValueType, STBM_VAR)
    StbM_GaaTimeCorrectionValue[STBM_ONE];
#endif

#define STBM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

#define STBM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

#if ( 0 < STBM_NUMBER_TIME_TRIGGERED_CONFIGURED)
VAR(StbM_TriggeredValueType, STBM_VAR)   
    StbM_GaaTriggeredValue[STBM_NUMBER_TIME_TRIGGERED_CONFIGURED];
#else
VAR(StbM_TriggeredValueType, STBM_VAR)   
    StbM_GaaTriggeredValue[STBM_ONE];
#endif

#define STBM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
