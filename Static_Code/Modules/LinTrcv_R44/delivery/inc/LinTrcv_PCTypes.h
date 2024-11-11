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
**  SRC-MODULE: LinTrcv_PCTypes.h                                             **
**                                                                            **
**  TARGET    : MC33661                                                       **
**                                                                            **
**  PRODUCT   : AUTOSAR LIN Transceiver Driver                                **
**                                                                            **
**  PURPOSE   : Provision of Pre-compile time parameters                      **
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
** 1.0.7          08-Apr-2024           YB Song          #CP44-7310           **
** 1.0.5          17-May-2023           KhaLN1           #CP44-2131           **
** 1.0.3          03-Aug-2022           KhaLN1           #CP44-705            **
** 1.0.2          17-May-2022           DuyNHP2          R44-Redmine #20124   **
** 1.0.0          22-Dec-2020           SJ Kim           Initial Version      **
*******************************************************************************/

#ifndef LINTRCV_PCTYPES_H
#define LINTRCV_PCTYPES_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "LinTrcv_Driver.h"   /* LinTrcv header file */

#if(STD_ON == LINTRCV_WAKEUP_SUPPORT)
#include "LinIf.h"                     /* LinIf header file */
#endif

/*******************************************************************************
**                      MACRO Definitions                                     **
*******************************************************************************/
/* @Trace: LinTrcv_SUD_MACRO_005 */
#define LINTRCV_UNINIT                     ((boolean)0x00)
#define LINTRCV_INIT                       ((boolean)0x01)
#define LINTRCV_ZERO                       (0x00U)
#define LINTRCV_ONE                        (0x01U)
#define LINTRCV_TRUE                       ((boolean)0x01)
#define LINTRCV_FALSE                      ((boolean)0x00)
#define LINTRCV_INVALID                    ((uint16)0xFFFF)
#define LINTRCV_INVALID_WKSOURCE           ((EcuM_WakeupSourceType)0xFFFFFFFFU)
#ifndef UNUSED                        /* Check for unused parameter warnings*/
  /*  polyspace +1 MISRA-C3:D4.9 [Justified:Low] "Use function like-macro for reduce execution time and stack" */
  #define UNUSED(variable) (void) variable
#endif

/*******************************************************************************
**                      Enumerate Types Definitions                           **
*******************************************************************************/
/* @Trace: LinTrcv_SUD_DATATYPE_005 */
/* define wake up notification flag */
typedef enum
{
  LINTRCV_WAKEUP_NOTIFICATION_DISABLED = FALSE,
  LINTRCV_WAKEUP_NOTIFICATION_ENABLED = TRUE
}LinTrcv_WakeupNotification;

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
/* @Trace: LinTrcv_SUD_DATATYPE_006 */
/*data structure of LinTrcv Ram Data*/
typedef struct
{
  /* Operational Mode */
  LinTrcv_TrcvModeType ddOpMode;

  #if(STD_ON == LINTRCV_WAKEUP_SUPPORT)
  /*  BusWakeUp Notification */
  LinTrcv_WakeupNotification ddWakeupEventNotification;

  /* WakeUp Pending state*/
  boolean blWakeupPending;
  #endif
}LinTrcv_NetworkRamData;

#define LINTRCV_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
/* @Trace: LinTrcv_SUD_CONSTVAR_001 */
/* Extern definition for LIN network structure array */
extern CONST(LinTrcv_ConfigType, LINTRCV_CONST) LinTrcv_GaaNetworkInfo[LINTRCV_NUM_OF_NETWORKS];
#define LINTRCV_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/

#endif /* LINTRCV_PCTYPES_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
