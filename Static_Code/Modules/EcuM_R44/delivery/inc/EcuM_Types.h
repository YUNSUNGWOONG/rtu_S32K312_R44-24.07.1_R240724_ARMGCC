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
**  FILE-NAME : EcuM_Types.h                                                  **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR EcuM Module                                           **
**                                                                            **
**  PURPOSE   : Type definitions of ECU State Manager                         **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By               Description                       **
********************************************************************************
** 1.2.0     04-Oct-2022   TriBD             R44_2021 #27878                  **
** 1.1.0     22-Mar-2021   TinhPV3           R44_2021 #17960                  **
** 0.0.2     07-Apr-2020   LocLT5            R44-Redmine #655, #8670          **
** 0.0.1     14-Feb-2020   ThangMA            R44-Redmine #655, #8668         **
*******************************************************************************/

/* polyspace:begin<MISRA-C:1.1:Not a defect:Justify with annotations> Not a defect */

#ifndef ECUM_TYPES_H
#define ECUM_TYPES_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Std_Types.h"
#include "Rte_EcuM_Type.h"
#include "SchM_EcuM_Type.h"

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

#define ECUM_WKSOURCE_ALL_SOURCES  ((EcuM_WakeupSourceType) 0xFFFFFFFFU)

/* Possible states of a wakeup source */
typedef enum 
{ 
  ECUM_WKSTATUS_NONE = 0,
  ECUM_WKSTATUS_PENDING,
  ECUM_WKSTATUS_VALIDATED,
  ECUM_WKSTATUS_EXPIRED
} EcuM_WakeupStatusType;

typedef enum 
{ 
  ECUM_WK_NONE = 0,
  ECUM_WK_UNKNOWN,
  ECUM_WK_KNOWN,
  ECUM_WK_KNOWN_ALARM
} EcuM_WakeupTypeConfigType;

typedef enum
{
  ECUM_RUNSTATUS_UNKNOWN = 0,
  ECUM_RUNSTATUS_REQUESTED,
  ECUM_RUNSTATUS_RELEASED
} EcuM_RunStatusType;

#ifndef ECUM_STATE_STARTUP
#define ECUM_STATE_STARTUP 16U
#endif /* ECUM_STATE_STARTUP */

#ifndef ECUM_STATE_STARTUP_ONE
#define ECUM_STATE_STARTUP_ONE 17U
#endif /* ECUM_STATE_STARTUP_ONE */

#ifndef ECUM_STATE_STARTUP_TWO
#define ECUM_STATE_STARTUP_TWO 18U
#endif /* ECUM_STATE_STARTUP_TWO */

#ifndef ECUM_STATE_STARTUP_THREE
#define ECUM_STATE_STARTUP_THREE 19U
#endif /* ECUM_STATE_STARTUP_THREE */

#ifndef ECUM_STATE_STARTUP_FOUR
#define ECUM_STATE_STARTUP_FOUR 20U
#endif /* ECUM_STATE_STARTUP_FOUR */

#ifndef ECUM_STATE_WAKEUP
#define ECUM_STATE_WAKEUP 32U
#endif /* ECUM_STATE_WAKEUP */

#ifndef ECUM_STATE_WAKEUP_ONE
#define ECUM_STATE_WAKEUP_ONE 33U
#endif /* ECUM_STATE_WAKEUP_ONE */

#ifndef ECUM_STATE_WAKEUP_VALIDATION
#define ECUM_STATE_WAKEUP_VALIDATION 34U
#endif /* ECUM_STATE_WAKEUP_VALIDATION */

#ifndef ECUM_STATE_WAKEUP_REACTION
#define ECUM_STATE_WAKEUP_REACTION 35U
#endif /* ECUM_STATE_WAKEUP_REACTION */

#ifndef ECUM_STATE_WAKEUP_TWO
#define ECUM_STATE_WAKEUP_TWO 36U
#endif /* ECUM_STATE_WAKEUP_TWO */

#ifndef ECUM_STATE_WAKEUP_WAKESLEEP
#define ECUM_STATE_WAKEUP_WAKESLEEP 37U
#endif /* ECUM_STATE_WAKEUP_WAKESLEEP */

#ifndef ECUM_STATE_WAKEUP_TTII
#define ECUM_STATE_WAKEUP_TTII 38U
#endif /* ECUM_STATE_WAKEUP_TTII */

#ifndef ECUM_STATE_RUN
#define ECUM_STATE_RUN 48U
#endif /* ECUM_STATE_RUN */

#ifndef ECUM_STATE_APP_RUN
#define ECUM_STATE_APP_RUN 50U
#endif /* ECUM_STATE_APP_RUN */

#ifndef ECUM_STATE_APP_POST_RUN
#define ECUM_STATE_APP_POST_RUN 51U
#endif /* ECUM_STATE_APP_POST_RUN */

#ifndef ECUM_STATE_SHUTDOWN
#define ECUM_STATE_SHUTDOWN 64U
#endif /* ECUM_STATE_SHUTDOWN */

#ifndef ECUM_STATE_PREP_SHUTDOWN
#define ECUM_STATE_PREP_SHUTDOWN 68U
#endif /* ECUM_STATE_PREP_SHUTDOWN */

#ifndef ECUM_STATE_GO_SLEEP
#define ECUM_STATE_GO_SLEEP 73U
#endif /* ECUM_STATE_GO_SLEEP */

#ifndef ECUM_STATE_GO_OFF_ONE
#define ECUM_STATE_GO_OFF_ONE 77U
#endif /* ECUM_STATE_GO_OFF_ONE */

#ifndef ECUM_STATE_GO_OFF_TWO
#define ECUM_STATE_GO_OFF_TWO 78U
#endif /* ECUM_STATE_GO_OFF_TWO */

#ifndef ECUM_STATE_SLEEP
#define ECUM_STATE_SLEEP 80U
#endif /* ECUM_STATE_SLEEP */

#ifndef ECUM_STATE_OFF
#define ECUM_STATE_OFF 128U
#endif /* ECUM_STATE_OFF */

#ifndef ECUM_STATE_RESET
#define ECUM_STATE_RESET 144U
#endif /* ECUM_STATE_RESET */

/* For DET Error */
#define ECUM_E_EARLIER_ACTIVE                  0x03
#define ECUM_E_PAST                            0x04
#define ECUM_E_NOT_ACTIVE                      0x05

#define ECUM_E_UNINIT                          0x10
#define ECUM_E_SERVICE_DISABLED                0x11
#define ECUM_E_NULL_POINTER                    0x12
#define ECUM_E_INVALID_PAR                     0x13
#define ECUM_E_STATE_PAR_OUT_OF_RANGE          0x16
#define ECUM_E_UNKNOWN_WAKEUP_SOURCE           0x17
#define ECUM_E_START_CORE_FAILED               0x18
#define ECUM_E_SHUTDOWN_FAILED                 0x19
#define ECUM_E_UNKNOWN_SLEEP_MODE              0x20
#define ECUM_E_INVALID_API_CALL                0x21
#define ECUM_E_INVALID_SHUTDOWNTARGET          0x22
#define ECUM_E_MULTIPLE_RUN_REQUESTS           0x23

//temporary add. need to update definition of error
#define ECUM_E_PARAM_POINTER           		   0x24
#define ECUM_E_RAM_CHECK_FAILED                0x25
#define ECUM_E_CONFIGURATION_DATA_INCONSISTENT 0x26
#define ECUM_E_MISMATCHED_RUN_RELEASE          0x27
#define ECUM_E_INIT_FAILED                     0x28
/* polyspace:end<MISRA-C:1.1:Not a defect:Justify with annotations> Not a defect */
#endif /* ECUM_TYPES_H */

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/

