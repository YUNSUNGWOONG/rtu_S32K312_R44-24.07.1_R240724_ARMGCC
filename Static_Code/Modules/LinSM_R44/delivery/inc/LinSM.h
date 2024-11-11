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
**  SRC-MODULE: LinSM.h                                                       **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR LinSM Module                                          **
**                                                                            **
**  PURPOSE   : Provision of LinSM APIs                                       **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: yes                                          **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/
 
/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision       Date                  By               Description          **
********************************************************************************
** 1.0.2          17-Sep-2021           DuyNGB           R44-Redmine #20123   **
** 1.0.0          22-Dec-2020           SJ Kim           Initial Version      **
*******************************************************************************/

#ifndef LINSM_H
#define LINSM_H
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* polyspace:begin<MISRA-C:1.1:Justified:Justify with annotations> Too many nesting levels of #includes */
#include "LinSM_Cfg.h"            /* LinSM  Configuration header file */
#include "LinIf.h"                /* LinIf header */
#include "ComM.h"                 /* ComM header file */
/* polyspace:end<MISRA-C:1.1:Justified:Justify with annotations> */
/*******************************************************************************
**                     Version Information                                    **
*******************************************************************************/

/*******************************************************************************
**                            Global Data                                     **
*******************************************************************************/
typedef uint8 LinSM_ModeType;
/* Service ID for LinSM_MainFunction */
#define LINSM_MAINFUNCTION_SID                ((uint8)0x30U)
/* Service ID for LinSM_Init */
#define LINSM_INIT_SID                        ((uint8)0x01U)
/* Service ID for LinSM_RequestComMode */
#define LINSM_REQUESTCOMMODE_SID              ((uint8)0x12U)
/* Service ID for LinSM_GetCurrentComMode */
#define LINSM_GETCURRENTCOMMODE_SID           ((uint8)0x11U)
/* Service ID for LinSM_ScheduleRequest */
#define LINSM_SCHEDULEREQUEST_SID             ((uint8)0x10U)
/* Service ID for LinSM_GetVersionInfo */
#define LINSM_GETVERSIONINFO_SID              ((uint8)0x02U)
/* Service ID for LinSM_GotoSleepConfirmation */
#define LINSM_GOTOSLEEPCONFIRMATION_SID       ((uint8)0x22U)
/* Service ID for LinSM_WakeupConfirmation */
#define LINSM_WAKEUPCONFIRMATION_SID          ((uint8)0x21U)
/* Service ID for LinSM_ScheduleRequestConfirmation */
#define LINSM_SCHEDULEREQUESTCONFIRMATION_SID ((uint8)0x20U)
/* Service ID for LinSM_GotoSleepIndication */
#define LINSM_GOTOSLEEPINDICATION_SID 		  ((uint8)0x03U)
/* InstanceID for LinSM Module*/
#define LINSM_INSTANCE_ID                     ((uint8)0x00U)

/* DET error codes */
#define LINSM_E_UNINIT                        ((uint8)0x00U)
#define LINSM_E_NONEXISTENT_NETWORK           ((uint8)0x20U)
#define LINSM_E_PARAMETER                     ((uint8)0x30U)
#define LINSM_E_PARAM_POINTER             	  ((uint8)0x40U)
#define LINSM_E_CONFIRMATION_TIMEOUT          ((uint8)0x00U)
#define LINSM_E_INIT_FAILED					  ((uint8)0x50U)

/* LinSM network states */
#define LINSM_NO_COM                          ((LinSM_ModeType)0x02U)
#define LINSM_FULL_COM                        ((LinSM_ModeType)0x01U)

/* Macro for Unused parameter */
/* polyspace-begin MISRA-C3:D4.9 [Justified:Low] "use function like-macro for reduce execution time and stack" */
#define LINSM_UNUSED(x)                    do { \
                                            if((uint32)(x) != (uint32)LINSM_ZERO) {} \
                                          } while(0)

#define LINSM_UNUSED_PTR(x)                do { \
                                            (void) x; \
                                          } while(0)
/* polyspace-end MISRA-C3:D4.9 [Justified:Low] "use function like-macro for reduce execution time and stack" */

typedef struct
{
  #if (LINSM_DEV_ERROR_DETECT == STD_ON)
    #if (LINSM_MASTER_SUPPORT == STD_ON)
	/* No of Schedules Configured for this channel */
    LinIf_SchHandleType ddNoOfSchedules;
	#endif /* End of  LINSM_MASTER_SUPPORT */
  #endif /* End of  LINSM_DEV_ERROR_DETECT */

  /* Index for the LinSM Channel, Config parameter: LinSMModeRequestRepetitionMax */
  uint8 ucModeRequestRepetitionMax;
} LinSM_ConfigType;

typedef signed int LinSM_UnderlyingType;

typedef enum
{
  /* Master node */
  LINSM_MASTER_NODE,
  /* Slave node */
  LINSM_SLAVE_NODE
} LinSM_NodeType;

typedef enum
{
  /* Substate run communication */
  LINSM_RUN_COMMUNICATION,
  /* Substate go to sleep */
  LINSM_GOTO_SLEEP
}LinSM_SubStateOfFullCom;

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
#define LINSM_START_SEC_CODE
/* polyspace<MISRA-C:1.1:Justified:Justify with annotations> */
#include "MemMap.h"

extern FUNC(void,
  LINSM_CODE) LinSM_Init(P2CONST(LinSM_ConfigType, AUTOMATIC,
    LINSM_APPL_CONST) ConfigPtr);

/* polyspace<MISRA-C:8.8:Justified:Justify with annotations> No Impact of this rule violation (AUTOSAR Standard : Rte SWS #7283) */
extern FUNC(void, LINSM_CODE) LinSM_MainFunction(void);

extern FUNC(Std_ReturnType, LINSM_CODE) LinSM_ScheduleRequest(
  NetworkHandleType network, LinIf_SchHandleType schedule);

extern FUNC(Std_ReturnType, LINSM_CODE) LinSM_RequestComMode(
  NetworkHandleType network, ComM_ModeType mode);

#if (LINSM_VERSION_INFO_API == STD_ON)
extern FUNC(void,
  LINSM_CODE) LinSM_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC,
    LINSM_APPL_DATA) versioninfo);

#endif

extern FUNC(Std_ReturnType, LINSM_CODE) LinSM_GetCurrentComMode(
  NetworkHandleType network, P2VAR(ComM_ModeType, AUTOMATIC,
    LINSM_APPL_DATA) mode);

#define LINSM_STOP_SEC_CODE
/* polyspace<MISRA-C:1.1:Justified:Justify with annotations> Too many nesting levels of #includes */
#include "MemMap.h"

/* Callback*/
#define LINSM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, LINSM_APPL_CODE) LinSM_ScheduleRequestConfirmation(
  NetworkHandleType network, LinIf_SchHandleType schedule);

extern FUNC(void, LINSM_APPL_CODE) LinSM_GotoSleepIndication(
  NetworkHandleType network);

extern FUNC(void, LINSM_APPL_CODE) LinSM_GotoSleepConfirmation(
  NetworkHandleType network, boolean success);

extern FUNC(void, LINSM_APPL_CODE) LinSM_WakeupConfirmation(
  NetworkHandleType network, boolean success);

#define LINSM_STOP_SEC_CODE
#include "MemMap.h"

#endif /* LINSM_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
