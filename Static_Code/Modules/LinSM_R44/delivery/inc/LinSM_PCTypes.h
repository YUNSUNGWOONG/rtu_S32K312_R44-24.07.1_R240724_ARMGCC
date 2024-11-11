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
**  SRC-MODULE: LinSM_PCTypes.h                                               **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR LinSM Module                                          **
**                                                                            **
**  PURPOSE   : This file contains the structure definitions                  **
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

#ifndef LINSM_PCTYPES_H
#define LINSM_PCTYPES_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "LinSM.h"                /* LinSM Config header */
#include "SchM_LinSM.h"           /* SchM LinSM header */

/*******************************************************************************
**                      MACRO Definitions                                     **
*******************************************************************************/
/* LinSM numerical macros */
#define LINSM_ZERO                             0x00U
#define LINSM_ONE                              0x01U
#define LINSM_TWO                              0x02U
#define LINSM_THREE                            0x03U

/* LinSM Initialization status */
#define LINSM_UNINIT                           ((boolean)0x00U)
#define LINSM_INIT                             ((boolean)0x01U)

/* LinSM boolean macros */
#define LINSM_TRUE                             ((boolean)0x01U)
#define LINSM_FALSE                            ((boolean)0x00U)

/* LinSMTransceiverPassiveMode configuration status */
#define LINSM_TRCV_NOTCONFIGURED               0xFFU
#define LINSM_TRCV_CONFIGURED_TRUE             0x00U
#define LINSM_TRCV_CONFIGURED_FALSE            0x01U

/* LinSM macros for timer type */
#define LINSM_MODE_REQ_TIMER                   0x00U
#define LINSM_SCHEDULE_REQ_TIMER               0x01U

/* LinSM Api request mask */
#define LINSM_MODE_REQ                         0x01U
#define LINSM_SCHEDULE_REQ                     0x02U
#define LINSM_MODE_REQ_FAILED                  0x04U
#define LINSM_SCHEDULE_REQ_FAILED              0x08U

/* LinSM Api reset request mask */
#define LINSM_RESET_MODE_REQ                   0x0EU
#define LINSM_RESET_SCHEDULE_REQ               0x0DU
#define LINSM_RESET_MODE_REQ_FAILED            0x0BU
#define LINSM_RESET_SCHEDULE_REQ_FAILED        0x07U

/*LinSM Invalid value */
#define LINSM_INVALID						   0xFFU

//#if (LINSM_SINGLE_CHANNEL == STD_OFF)
/* polyspace-begin MISRA-C3:D4.9 [Justified:Low] "use function like-macro for reduce execution time and stack" */
/* polyspace-end MISRA-C3:D4.9 [Justified:Low] "use function like-macro for reduce execution time and stack" */
/*******************************************************************************
**                            Global Data                                     **
*******************************************************************************/
/* Structure for Schedule of LinSM channel information */
typedef struct
{

  /* #7499: this member is used only when DET is STD_ON */
  #if (LINSM_DEV_ERROR_DETECT == STD_ON)
  /* Schedule Indexes, Config parameter: LinSMScheduleIndex */
  P2CONST(uint8, AUTOMATIC, LINSM_CONST)pScheduleIds;
  #else
  uint8 ucLinSMDummy;
  #endif

} LinSM_HandleChannel;

/* Structure for LinSM channel information */
typedef struct
{
  #if (LINSM_TIMEOUT_FUNC == STD_ON)
  /* Timeout value for single channel
   *   Config parameter:LinSMConfirmationTimeout*/
  uint16 usLinSMConfirmationTimeout;
  #endif

  #if (LINSM_SLAVE_SUPPORT == STD_ON)
  /* Timeout in seconds after a failed wakeup sequence until a new wakeup process is started
   *   Config parameter: LinSMSilenceAfterWakeupTimeout*/
  uint16 usSilenceAfterWakeupTimeout;
  #endif

  /* Index for the LinSM Channel, Config parameter: LinSMComMNetworkHandleRef */
  NetworkHandleType ddLinSMChannelId;
} LinSM_StaticChannel;

/* Type definition for SchM Function pointer */
typedef P2FUNC(void, LINSM_CODE, LinSM_SchMFuncPtr) (void);

/* Type definition for LinIf Function pointer */
typedef P2FUNC(Std_ReturnType, LINSM_CODE, LinSM_ModeReqPtr)
  (NetworkHandleType Channel);

/*******************************************************************************
**                     Global Data                                            **
*******************************************************************************/
#define LINSM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
/* Structure Array to hold the ConfigType parameters */
/* polyspace-begin MISRA-C3:8.11 [Justified:Low] "size of array is determined by configuration" */
extern CONST(LinSM_ConfigType, LINSM_CONST) LinSM_GaaConfigType[LINSM_NO_OF_CHANNELS];
#define LINSM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

#define LINSM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
/* Structure Array to hold the HandleChannel parameters */
extern CONST(LinSM_HandleChannel, LINSM_CONST) LinSM_GaaHandleChannel[LINSM_NO_OF_CHANNELS];
#define LINSM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

#define LINSM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
/* Structure Array to hold the all channel parameters */
extern CONST(LinSM_StaticChannel, LINSM_CONST) LinSM_GaaStaticChannel[LINSM_NO_OF_CHANNELS];
#define LINSM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

#define LINSM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
/* Structure Array to hold the all channel Node Type */
extern CONST(LinSM_NodeType, LINSM_CONST) LinSM_CurrentNodeType[LINSM_NO_OF_CHANNELS];
#define LINSM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

#if (LINSM_SINGLE_CHANNEL == STD_OFF)
#define LINSM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
/* Extern definition for Channel Map array for mapping active and inactive
 *   channels */
extern CONST(NetworkHandleType, LINSM_CONST) LinSM_GaaInternalChannelMap[];
#define LINSM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif /* End of if (LINSM_SINGLE_CHANNEL == STD_OFF) */

#define LINSM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
extern CONST(uint8, LINSM_CONST) LinSM_GaaScheduleIds[];
#define LINSM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

#if (LINSM_GLOBAL_TRCV_SUPPORT == STD_ON)
#define LINSM_START_SEC_CONST_8
#include "MemMap.h"
/* Array that holds the value of LinSMTransceiverPassiveMode parameter */
extern CONST(uint8, LINSM_CONST) LinSM_GaaTrcvPassiveMode[LINSM_NO_OF_CHANNELS];
#define LINSM_STOP_SEC_CONST_8
#include "MemMap.h"
#endif /* End of if (LINSM_GLOBAL_TRCV_SUPPORT == STD_ON) */

#define LINSM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
/* Global array for SchM_Enter functions */
extern CONST(LinSM_SchMFuncPtr, LINSM_CONST) LinSM_GaaSchMEnterFuncPtr[];
#define LINSM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

#define LINSM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
/* Global array for SchM_Exit functions */
extern CONST(LinSM_SchMFuncPtr, LINSM_CONST) LinSM_GaaSchMExitFuncPtr[];
#define LINSM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
/* polyspace-end MISRA-C3:8.11 [Justified:Low] "size of array is determined by configuration" */
#endif /* LINSM_PCTYPES_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
