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
**  SRC-MODULE: CanIf_Rx.h                                                    **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR CanIf                                                 **
**                                                                            **
**  PURPOSE   : Header file of CanIf_Rx.c                                     **
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
** 1.1.0     29-Feb-2024   Jh Yang        #CP44-2946, #CP44-2947              **
** 1.0.10    27-Oct-2022   HieuTM8        #CP44-1008                          **
** 1.0.5     30-Jun-2022   HieuTM8        #CP44-130                           **
** 1.0.1     22-Sep-2021   HieuTM8        #20891                              **
** 1.0.0     21-Dec-2020   SJ Kim         Initialization                      **
*******************************************************************************/

#ifndef CANIF_RX_H
#define CANIF_RX_H
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "CanIf_Ram.h"           /* Ram header file */
#include "CanIf_PCTypes.h"       /* Pre-compile time header file */
#include "CanSM_CanIf.h"           /* CAN State Manager call back header file */
#if (STD_ON == CANIF_PDUR_CALLBACK)
#include "PduR_CanIf.h"          /* Call-back PduR header file */
#endif
#if (STD_ON == CANIF_CANTP_CALLBACK)
#include "CanTp.h"           /* Call-back CanTp header file */
#endif
#if (STD_ON == CANIF_CANNM_CALLBACK)
#include "CanNm.h"           /* Call-back CanNm header file */
#endif
#include "SchM_CanIf.h"          /* SchM CanIf Header file */
#include "CanIf_Error.h"         /* DET header file */

#if (STD_ON == CANIF_AUTRON_CANTRCV_SUPPORT)
#include "CanTrcv.h"            /* CanTrcv header file */
#endif
#if (STD_ON == CANIF_EXTENAL_CANTRCV_SUPPORT)
#include "CanIf_CanTrcv.h"            /* CanTrcv header file */
#endif

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/* AUTOSAR Specification Version Information */
#define CANIF_RX_AR_RELEASE_MAJOR_VERSION       4
#define CANIF_RX_AR_RELEASE_MINOR_VERSION       4
#define CANIF_RX_AR_RELEASE_REVISION_VERSION    0

/* Software Version Information */
#define CANIF_RX_SW_MAJOR_VERSION       1
#define CANIF_RX_SW_MINOR_VERSION       1
#define CANIF_RX_SW_REVISION_VERSION    0
/*******************************************************************************
**                      Global Symbols                                        **
*******************************************************************************/

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
#if (STD_ON == CANIF_RX_LPDU)
#define CANIF_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, CANIF_CODE) CanIf_RxNotification (
    P2CONST(CanIf_RxLpduType, AUTOMATIC, CANIF_CONST) ptrRxLpdu,
    P2CONST(PduInfoType, AUTOMATIC, CANIF_CONST) PduInfoPtr);
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"
#endif

#if ((STD_ON == CANIF_RX_LPDU) && (STD_ON == CANIF_META_DATA_SUPPORT))
#define CANIF_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, CANIF_CODE) CanIf_RxData (Can_IdType CanId,
    P2CONST(CanIf_RxLpduType, AUTOMATIC, CANIF_CONST) ptrRxLpdu,
    P2VAR(Can_IdType, AUTOMATIC, CANIF_VAR) metadata);
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"
#endif

#if ((STD_ON == CANIF_BINARY_SEARCH)||(STD_ON == CANIF_IDTABLE_SEARCH))
#define CANIF_START_SEC_CODE
#include "MemMap.h"
extern FUNC(CanIf_RxLpduTypePtr, CANIF_CODE)
  CanIf_BinarySearch (
    P2CONST(CanIf_RxLpduType, AUTOMATIC, CANIF_CONST) ptrRxLpdu,
    VAR(PduIdType, CANIF_VAR) size,
    VAR(Can_IdType, CANIF_VAR) canId,
    VAR(uint8, CANIF_VAR) canFrameType);
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"
#endif

#define CANIF_START_SEC_CODE
#include "MemMap.h"
extern FUNC(CanIf_RxLpduTypePtr, CANIF_CODE)
  CanIf_TriggerSWFilter (
    P2CONST(CanIf_HrhType, AUTOMATIC, CANIF_CONST) ptrHrh,
    VAR(Can_IdType, CANIF_VAR) CanId,
    VAR(uint8, CANIF_VAR) canFrameType);
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"

#if ((STD_ON == CANIF_READRXPDU_NOTIFY_STATUS_API) || \
     (STD_ON == CANIF_READRXPDU_DATA_API))
#define CANIF_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, CANIF_CODE) CanIf_RxStatusUpdate (
    P2CONST(CanIf_RxLpduType, AUTOMATIC, CANIF_CONST) ptrRxLpdu,
    P2CONST(PduInfoType, AUTOMATIC, CANIF_CONST) PduInfoPtr);
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"
#endif

#if (STD_ON == CANIF_LINEAR_SEARCH)
#define CANIF_START_SEC_CODE
#include "MemMap.h"
extern FUNC(P2CONST(CanIf_RxLpduType, AUTOMATIC, CANIF_CONST), CANIF_CODE)
  CanIf_LinearSearch (
    P2CONST(CanIf_RxLpduType, AUTOMATIC, CANIF_CONST) ptrRxLpdu,
    VAR(PduIdType, CANIF_VAR) size,
    VAR(Can_IdType, CANIF_VAR) canId,
    VAR(uint8, CANIF_VAR) canFrameType);
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"
#endif

#define CANIF_START_SEC_CODE
#include "MemMap.h"
extern FUNC(CanIf_RxLpduTypePtr, CANIF_CODE) CanIf_Filtering (
            VAR(uint8, CANIF_VAR) sftwrFltrng,
            P2CONST(CanIf_HrhType, AUTOMATIC, CANIF_CONST) ptrHrh,
            VAR(Can_IdType, CANIF_VAR) canId,
            VAR(uint8, CANIF_VAR) canFrameType,
            P2VAR(Can_IdType, AUTOMATIC, CANIF_VAR) metadata);
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"

#if (STD_ON == CANIF_DEV_ERROR_DETECT)
#define CANIF_START_SEC_CODE
#include "MemMap.h"
extern FUNC(uint8, CANIF_CODE) CanIf_DETRxindication (
                    P2CONST(Can_HwType, AUTOMATIC, CANIF_APPL_CONST) Mailbox,
                    P2CONST(PduInfoType, AUTOMATIC, CANIF_APPL_CONST) PduInfoPtr);
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"

#define CANIF_START_SEC_CODE
#include "MemMap.h"
extern FUNC(uint8, CANIF_CODE) CanIf_CheckParameter (
                    P2CONST(Can_HwType, AUTOMATIC, CANIF_APPL_CONST) Mailbox,
                    P2CONST(PduInfoType, AUTOMATIC, CANIF_APPL_CONST) PduInfoPtr,
                    VAR(uint8, CANIF_VAR) offsetid);
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"
#endif

#if (STD_ON == CANIF_RX_LPDU)
#define CANIF_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, CANIF_CODE) CanIf_CheckRxPduCanIdType (
                      P2CONST(CanIf_RxLpduType, AUTOMATIC, CANIF_CONST) ptrRxLpdu,
                      VAR(uint8, CANIF_VAR) canFrameType);
#define CANIF_STOP_SEC_CODE
#include "MemMap.h"
#endif

#endif  /*CANIF_RX_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
