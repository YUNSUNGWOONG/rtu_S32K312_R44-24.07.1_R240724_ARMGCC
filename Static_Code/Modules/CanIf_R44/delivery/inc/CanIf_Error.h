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
**  SRC-MODULE: CanIf_Error.h                                                 **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR CanIf                                                 **
**                                                                            **
**  PURPOSE   : The file contains the Development Error Tracer code helping   **
**              to findout the error occurred within the CanIf module during  **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
*******************************************************************************/
/*******************************************************************************
** Revision  Date          By             Description                         **
********************************************************************************
** 1.1.0     29-Feb-2024    Jh Yang        #CP44-2947                         **
** 1.0.15    22-Jan-2024    JH Jang        #CP44-2840, CP44-2848              **
** 1.0.6     25-Jul-2022    HieuTM8        #CP44-444                          **
** 1.0.5     30-Jun-2022    HieuTM8        #CP44-130                          **
** 1.0.1     22-Sep-2021    HieuTM8        #20891                             **
** 1.0.0     21-Dec-2020    SJ Kim         Initialization                     **
*******************************************************************************/

#ifndef CANIF_ERROR_H
#define CANIF_ERROR_H
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "CanIf.h"       /* Header file for Fr Module */

#include "CanIf_Types.h" /* Header file for config Ptr type */
/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/* AUTOSAR Specification Version Information */
#define CANIF_ERROR_AR_RELEASE_MAJOR_VERSION ((uint8)4)
#define CANIF_ERROR_AR_RELEASE_MINOR_VERSION ((uint8)4)
#define CANIF_ERROR_AR_RELEASE_REVISION_VERSION ((uint8)0)

/* Software Version Information */
#define CANIF_ERROR_SW_MAJOR_VERSION ((uint8)1)
#define CANIF_ERROR_SW_MINOR_VERSION ((uint8)1)
#define CANIF_ERROR_SW_PATCH_VERSION ((uint8)0)
/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
/* polyspace-begin MISRA2012:D4.9 [No action planned:Low] "use macro function to reduce length of code"*/
#if (STD_ON == CANIF_DEV_ERROR_DETECT)
/* This Error code is used when CanIf module is not initialized */
#define CANIF_GLOBAL_INIT_STATUS_ERROR(CANIF_API_ID, retVal)                   \
  do {                                                                         \
    switch (CanIf_CanIfStatus) {                                               \
    case CANIF_UNINITIALISED:                                                  \
      (void)Det_ReportError(CANIF_MODULE_ID, (uint8)CANIF_ZERO, CANIF_API_ID,  \
                            CANIF_E_UNINIT);                                   \
      (retVal) = (uint8)E_NOT_OK;                                              \
      break;                                                                   \
    default:                                                                   \
      break;                                                                   \
    };                                                                         \
  } while (0)

/* This Error code is used when controller id has invalid Id */
#define CANIF_CONTROLLER_RANGE_ERROR(CANIF_API_ID, retVal)                     \
  do {                                                                         \
    if (CANIF_NO_OF_CONTROLLER <= ControllerId) {                               \
      (void)Det_ReportError(CANIF_MODULE_ID, (uint8)CANIF_ZERO, CANIF_API_ID,  \
                            CANIF_E_PARAM_CONTROLLERID);                       \
      (retVal) = (uint8)E_NOT_OK;                                              \
    }                                                                          \
  } while (0)

/* This Error code is used when controller Mode is invalid or out of defined
   values or CAN_CS_UNINIT */
#define CANIF_INVALID_CONTROLLER_MODE_ERROR(CANIF_API_ID, ControllerMode, retVal) \
  do {                                                                         \
    switch (ControllerMode) {                                                  \
    case CANIF_SLEEP:                                                          \
      break;                                                                   \
    case CANIF_STARTED:                                                        \
      break;                                                                   \
    case CANIF_STOPPED:                                                        \
      break;                                                                   \
    case CANIF_UNINIT:                                                         \
    default:                                                                   \
      (void)Det_ReportError(CANIF_MODULE_ID, (uint8)CANIF_ZERO, CANIF_API_ID,  \
                            CANIF_E_PARAM_CTRLMODE);                           \
      (retVal) = (Std_ReturnType)E_NOT_OK;                                     \
      break;                                                                   \
    };                                                                         \
  } while (0)

/* This Error code is used when Transceiver ID is Invalid */
#define CANIF_TRANSCEIVERID_RANGE_ERROR(CANIF_API_ID, retVal)                  \
  do {                                                                         \
    if ((uint8)CANIF_NO_OF_TRANSCEIVER <= TransceiverId) {                     \
      (void)Det_ReportError(CANIF_MODULE_ID, (uint8)CANIF_ZERO, CANIF_API_ID,  \
                            CANIF_E_PARAM_TRCV);                               \
      (retVal) = (uint8)E_NOT_OK;                                              \
    }                                                                          \
  } while (0)

/* This Error code is used when transition of Transceiver mode is prohibited */
#define CANIF_TRCV_MODE_SLEEP_STANDBY_ERROR(CANIF_API_ID, currentOpMode,       \
                                            TransceiverMode, retVal)           \
  do {                                                                         \
    if (((uint8)E_OK == (retVal)) &&                                           \
        (((uint8)CANTRCV_TRCVMODE_SLEEP == (currentOpMode)) &&                 \
         ((CanTrcv_TrcvModeType)CANTRCV_TRCVMODE_STANDBY ==                    \
          (TransceiverMode)))) {                                               \
      (void)Det_ReportError(CANIF_MODULE_ID, (uint8)CANIF_ZERO, CANIF_API_ID,  \
                            CANIF_E_PARAM_TRCVMODE);                           \
      (retVal) = (uint8)E_NOT_OK;                                              \
    }                                                                          \
  } while (0)

/* This Error code is used when transition of Transceiver mode is prohibited */
#define CANIF_TRCV_MODE_SLEEP_NORMAL_ERROR(CANIF_API_ID, currentOpMode,        \
                                           TransceiverMode, retVal)            \
  do {                                                                         \
    if (((uint8)E_OK == (retVal)) &&                                           \
        (((uint8)CANTRCV_TRCVMODE_NORMAL == (currentOpMode)) &&                \
         ((CanTrcv_TrcvModeType)CANTRCV_TRCVMODE_SLEEP ==                      \
          (TransceiverMode)))) {                                               \
      (void)Det_ReportError(CANIF_MODULE_ID, (uint8)CANIF_ZERO, CANIF_API_ID,  \
                            CANIF_E_PARAM_TRCVMODE);                           \
      (retVal) = (uint8)E_NOT_OK;                                              \
    }                                                                          \
  } while (0)

/* This Error code is used when Transceiver mode is invalid */
#define CANIF_TRCV_MODE_INVALID_ERROR(CANIF_API_ID, TransceiverMode, retVal)   \
  do {                                                                         \
    switch (TransceiverMode) {                                                 \
    case CANTRCV_TRCVMODE_STANDBY:                                             \
      break;                                                                   \
    case CANTRCV_TRCVMODE_NORMAL:                                              \
      break;                                                                   \
    case CANTRCV_TRCVMODE_SLEEP:                                               \
      break;                                                                   \
    default:                                                                   \
      (void)Det_ReportError(CANIF_MODULE_ID, (uint8)CANIF_ZERO, CANIF_API_ID,  \
                            CANIF_E_PARAM_TRCVMODE);                           \
      (retVal) = (uint8)E_NOT_OK;                                              \
      break;                                                                   \
    };                                                                         \
  } while (0)

/* This Error code is used when Pdu Mode is invalid */
#define CANIF_INVALID_PDU_MODE_REQ_ERROR(CANIF_API_ID, retVal)                 \
  do {                                                                         \
    switch (PduModeRequest) {                                                  \
    case CANIF_OFFLINE:                                                        \
      break;                                                                   \
    case CANIF_ONLINE:                                                         \
      break;                                                                   \
    case CANIF_TX_OFFLINE:                                                     \
      break;                                                                   \
    case CANIF_TX_OFFLINE_ACTIVE:                                              \
      break;                                                                   \
    default:                                                                   \
      (void)Det_ReportError(CANIF_MODULE_ID, (uint8)CANIF_ZERO, CANIF_API_ID,  \
                            CANIF_E_PARAM_PDU_MODE);                           \
      (retVal) = (uint8)E_NOT_OK;                                              \
      break;                                                                   \
    };                                                                         \
  } while (0)
  
#define CANIF_INVALID_STANDARD_CANID_ERROR(CANIF_API_ID, CanId, retVal)        \
  do {                                                                         \
    if ((((uint8)CANIF_RX_BASIC_CAN_STD == sftwrFltrng) ||                     \
         ((uint8)CANIF_RX_FULL_CAN_STD == sftwrFltrng)) &&                     \
        (CANIF_STANDARD_CANID_VALUE < (CanId)) &&                              \
        (CANIF_ZERO == ((CanId) & CANIF_STANDARD_FD_VALUE) )) {                \
      (void)Det_ReportError(CANIF_MODULE_ID, (uint8)CANIF_ZERO, CANIF_API_ID,  \
                            CANIF_E_PARAM_CANID);                              \
      (retVal) = (uint8)E_NOT_OK;                                              \
    }                                                                          \
  } while (0)

#define CANIF_INVALID_EXTENDED_CANID_ERROR(CANIF_API_ID, CanId, retVal)        \
  do {                                                                         \
    if ((((uint8)CANIF_RX_BASIC_CAN_EXT == sftwrFltrng) ||                     \
         ((uint8)CANIF_RX_FULL_CAN_EXT == sftwrFltrng)) &&                     \
        (CANIF_EXTENDED_CANID_VALUE < (CanId)) &&                              \
        (CANIF_ZERO == ((CanId) & CANIF_EXTENDED_FD_VALUE))) {                 \
      (void)Det_ReportError(CANIF_MODULE_ID, (uint8)CANIF_ZERO, CANIF_API_ID,  \
                            CANIF_E_PARAM_CANID);                              \
      (retVal) = (uint8)E_NOT_OK;                                              \
    }                                                                          \
  } while (0)

/* This Error code is used when CanId is out of range for Standard type */
#define CANIF_STD_CANID_ERROR(CANIF_API_ID, retVal)                            \
  do {                                                                         \
    if ((Can_IdType)CANIF_STANDARD_CANID_VALUE < CanId) {                      \
      (void)Det_ReportError(CANIF_MODULE_ID, (uint8)CANIF_ZERO, CANIF_API_ID,  \
                            CANIF_E_PARAM_CANID);                              \
      (retVal) = (uint8)E_NOT_OK;                                              \
    }                                                                          \
  } while (0)

/* This Error code is used when CanId is out of range for extended type */
#define CANIF_EXTD_CANID_ERROR(CANIF_API_ID, retVal)                           \
  do {                                                                         \
    if ((Can_IdType)CANIF_EXTENDED_CANID_VALUE < CanId) {                      \
      (void)Det_ReportError(CANIF_MODULE_ID, (uint8)CANIF_ZERO, CANIF_API_ID,  \
                            CANIF_E_PARAM_CANID);                              \
      (retVal) = (uint8)E_NOT_OK;                                              \
    }                                                                          \
  } while (0)

/* This Error code is used notification value is out of range */
#define CANIF_NOTIFICATION_STATUS_ERROR(CANIF_API_ID, retVal)                  \
  do {                                                                         \
    if ((uint8)CANIF_ZERO == notifStsMask) {                                   \
      (void)Det_ReportError(CANIF_MODULE_ID, (uint8)CANIF_ZERO, CANIF_API_ID,  \
                            CANIF_E_INVALID_TXPDUID);                          \
      (retVal) = (uint8)E_NOT_OK;                                              \
    }                                                                          \
  } while (0)
  
/* This Error code is used when TrcvWakeupMode is out of raange */ 
#define CANIF_INVALID_TRCV_WAKEUPMODE_ERROR(CANIF_API_ID, retVal)              \
  do {                                                                         \
    if ((uint8)CANIF_TRCV_WU_CLEAR < (uint8)TrcvWakeupMode) {                  \
      (void)Det_ReportError(CANIF_MODULE_ID, (uint8)CANIF_ZERO, CANIF_API_ID,  \
                            CANIF_E_PARAM_TRCVWAKEUPMODE);                     \
      (retVal) = (uint8)E_NOT_OK;                                              \
    }                                                                          \
  } while (0)

/* This Error code is used when input parameter is NULL_PTR */
#define CANIF_NULL_PTR_ERROR(CANIF_API_ID, retVal, CANIF_INPUT_PTR)            \
  do {                                                                         \
    if ((CANIF_INPUT_PTR) == NULL_PTR) {                                       \
      (void)Det_ReportError(CANIF_MODULE_ID, (uint8)CANIF_ZERO, CANIF_API_ID,  \
                            CANIF_E_PARAM_POINTER);                            \
      (retVal) = (uint8)E_NOT_OK;                                              \
    }                                                                          \
  } while (0)

#endif /* (STD_ON == CANIF_DEV_ERROR_DETECT) */


/* This Error code is used when SDU length is incorrect */
#define CANIF_VALID_SDU_LENGTH(CANIF_API_ID, retVal)                           \
  do {                                                                         \
    if ((uint8)CANIF_SDU_MAX_LENGTH < (PduInfoPtr->SduLength)) {               \
      (void)Det_ReportRuntimeError(CANIF_MODULE_ID, (uint8)CANIF_ZERO,         \
                            CANIF_API_ID, CANIF_E_DATA_LENGTH_MISMATCH);       \
      if (CANIF_FALSE == ptrTxLpdu->Truncate) {                                \
        (void)Det_ReportRuntimeError(CANIF_MODULE_ID, (uint8)CANIF_ZERO,       \
                              CANIF_API_ID, CANIF_E_TXPDU_LENGTH_EXCEEDED);    \
        (retVal) = (uint8)E_NOT_OK;                                            \
      }                                                                        \
    }                                                                          \
  } while (0)

/* This Error code is used when Pdu Mode is Offline or  controller mode is in stopped */
#define CANIF_OFFLINE_PDU_STOPPED_CTRL_MODE(CANIF_API_ID, retVal)              \
  do {                                                                         \
    if (((CANIF_TX_DISABLED == txStatus) &&                                    \
         (CANIF_RX_DISABLED == rxStatus)) ||                                   \
        (CANIF_TX_DISABLED == txStatus) || ((uint8)CAN_CS_STOPPED == currentMode)) {  \
      (void)Det_ReportRuntimeError(CANIF_MODULE_ID, (uint8)CANIF_ZERO, CANIF_API_ID,  \
                            CANIF_E_STOPPED);                                  \
          CanIf_TxNotification(ptrTxLpdu , E_NOT_OK);                          \
      (retVal) = (Std_ReturnType)E_NOT_OK;                                     \
    }                                                                          \
  } while (0)

#endif /* CANIF_ERROR_H */
/* polyspace-end MISRA2012:D4.9 [No action planned:Low] "use macro function to reduce length of code"*/
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
