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
**  SRC-MODULE: PduR_Types.h                                                  **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR PDU Router                                            **
**                                                                            **
**  PURPOSE   : Type definition of AUTOSAR PDU Router                         **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision    Date          By          Description                          **
********************************************************************************
** 1.0.9.0_HF1 24-May-2024   Mj Kim      CP44-8274                            **
** 1.0.3       07-Dec-2021   PhucNHM     R44-Redmine #22235                   **
** 1.0.0       04-Dec-2020   AUTOEVER    Initial Version                      **
*******************************************************************************/

#ifndef PDUR_TYPES_H
#define PDUR_TYPES_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* @Trace: PduR_SUD_FILE_001 */
/* @Trace: SRS_BSW_00301 */
/* @Trace: PduR_SUD_DATATYPE_001 PduR_SUD_DATATYPE_002 PduR_SUD_DATATYPE_003 */
/* @Trace: PduR_SUD_DATATYPE_004 PduR_SUD_DATATYPE_005 PduR_SUD_DATATYPE_006 */
/* @Trace: PduR_SUD_DATATYPE_007 */
/* Import types:
 * BufReq_ReturnType, PduIdType, PduInfoType, PduLengthType, RetryInfoType
 * Std_ReturnType, Std_VersionInfoType
 */
#include "ComStack_Types.h" /* COM Stack header module */
/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
/* @Trace: SWS_BSW_00480 */
/* @Trace: PduR_SUD_MACRO_005 */
/* Invalid configuration pointer */
#define PDUR_E_INIT_FAILED                   ((uint8) 0)

/* API service used without module initialization */
#define PDUR_E_UNINIT                        ((uint8) 1)

/* Invalid PduId is reported using following error code */
#define PDUR_E_PDU_ID_INVALID                ((uint8) 2)

/* Invalid Routing Path Group Id is reported using following error code */
#define PDUR_E_ROUTING_PATH_GROUP_ID_INVALID ((uint8) 8)

/* NULL Data pointer is reported using the following error code */
#define PDUR_E_PARAM_POINTER                 ((uint8) 9)

/* @Trace: PduR_SUD_MACRO_007 */
/* Rejection of Transmit request for a valid and idle PDU identifier by
 *     TP module is reported using following error code */
#define PDUR_E_TP_TX_REQ_REJECTED            ((uint8) 3)

/* Buffer Overflow is reported using following error code */
#define PDUR_E_PDU_INSTANCES_LOST            ((uint8) 10)
/* Maximum number of gateway multicast supported destination modules */
#define PDUR_MAX_MULTICAST_COUNT              ((uint8) 15)

/* @Trace: SRS_BSW_00305 */
/* @Trace: PduR_SUD_DATATYPE_057 */
/* PduR ConfigId returntype */
typedef uint16 PduR_PBConfigIdType;

/* @Trace: PduR_SUD_DATATYPE_055 */
typedef uint16 PduR_RoutingPathGroupIdType;

/* @Trace: PduR_SUD_DATATYPE_056 */
/* @Trace: SRS_BSW_00335 */
/* @Traceability BEGIN -- SRS: SWS_PduR_00742 */
/* PDU Router States */
typedef enum
{
  /*PDU Router is not initialised*/
  PDUR_UNINIT  = 0,
  /* PDU Router initialized successfully */
  PDUR_ONLINE
}PduR_StateType;
/* @Traceability END -- SRS: SWS_PduR_00742 */
typedef uint8 PduR_ReturnType;

/* @Trace: PduR_SUD_DATATYPE_058 */
/* PDU Router gateway buffer status */
typedef struct
{
  uint8 ucNoOfRoutePdu;
  uint8 aaPathStatus[PDUR_MAX_MULTICAST_COUNT];
  uint8 aaBufStatus[PDUR_MAX_MULTICAST_COUNT];
} PduR_GwBufferStatus;

/* Buffer Free Status */
typedef enum 
{
  PDUR_EMPTY  = 0,
  PDUR_OCCUPIED = 1
} PduR_Buffer_StateType;
/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/

#endif /* PDUR_TYPES_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
