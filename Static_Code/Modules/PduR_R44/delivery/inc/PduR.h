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
**  SRC-MODULE: PduR.h                                                        **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR PDU Router                                            **
**                                                                            **
**  PURPOSE   : Module Header File                                            **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By          Description                            **
********************************************************************************
** 1.0.5     11-Nov-2022   HaoTA4      CP44-383                               **
** 1.0.3     07-Dec-2021   PhucNHM     R44-Redmine #22235                     **
** 1.0.2     05-Oct-2021   PhucNHM     R44-Redmine #20586                     **
** 1.0.1     22-Jun-2021   PhucNHM     R44-Redmine #18951                     **
** 1.0.0     04-Dec-2020   AUTOEVER    Initial Version                        **
*******************************************************************************/
#ifndef PDUR_H
#define PDUR_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* @Trace: PduR_SUD_FILE_001 */
#include "ComStack_Types.h"       /* Com Stack Types header file */
#include "PduR_Types.h"           /* Type definition header file */
/* @Trace: SRS_BSW_00345 */
/* @Trace: SRS_BSW_00346 */
/* @Trace: SRS_BSW_00392 */
/* @Trace: SRS_BSW_00394 */
/* @Trace: SRS_BSW_00403 */
/* @Trace: PduR_SUD_MACRO_001 */
/* @Trace: PduR_SUD_MACRO_002 */
#include "PduR_Cfg.h"
#if (PDUR_VARIANT_POSTBUID_SUPPORT == STD_ON)
#include "PduR_Pbcfg.h"
#endif
#include "PduR_IntTypes.h"        /* PDU Router module post-build time header */
#include "PduR_Globals.h"             /* Type definition header file */


/*Instance ID*/
#define PDUR_INSTANCE_ID                  ((uint8) 0)

/* AUTRON BUGFIX Definition - Enable Featuring */
#define AUTRON_LOCAL_BUG_FIX

/*******************************************************************************
**                      Global Data Type                                      **
*******************************************************************************/
/**
 * typedef PduR_PBConfigType
 *
 * This structure is required to be generated in case of Post Build or Multiple
 *  configuration
 */
/* @Trace: SRS_BSW_00404 */
/* @Trace: SRS_BSW_00405 */
/* @Trace: SRS_BSW_00438 */
/* @Trace: PduR_SUD_DATATYPE_054 */
/* Structure for PduR_PBConfigType */
#if (PDUR_VARIANT_POSTBUID_SUPPORT == STD_ON)
typedef struct
{
  /* Transmission structure of routing path */
  #if ((PDUR_IF_TRANSMIT == STD_ON)||(PDUR_TP_TRANSMIT == STD_ON))
  P2CONST(PduR_UpTx, AUTOMATIC, PDUR_CONST) UpTransmit;
  #endif
  /* Source structure of routing path */
  #if ((PDUR_LO_RXINDICATION == STD_ON)||(PDUR_TP_RXINDICATION == STD_ON))
  P2CONST(PduR_LoRxSource, AUTOMATIC, PDUR_CONST) LoRxSource;
  #endif
  /* Destination structure of routing path */
  #if ((PDUR_LO_TXCONFIRMATION == STD_ON)||(PDUR_TP_TXCONFIRMATION == STD_ON))
  P2CONST(PduR_LoTxDestination, AUTOMATIC, PDUR_CONST) LoTxDestination;
  #endif
  /* If Buffer structure for gateway communication interface */
  #if (PDUR_TX_BUFFER_ROUTING_COUNT > PDUR_ZERO)
  P2VAR(PduR_TxBuffer, AUTOMATIC, PDUR_CONST) IfTxBuffer;
  #endif
  /* Tp Buffer structure for gateway transport protocol */
  #if (PDUR_TP_BUFFER_ROUTING_COUNT > PDUR_ZERO)
  P2VAR(PduR_TpBuffer, AUTOMATIC, PDUR_VAR) TpTxBuffer;
  #endif
  #if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON)
  /* Array group Id for all routing path */
  P2VAR(uint8, AUTOMATIC, PDUR_VAR) GroupPathId;
  /* Array group Id for store group Id at initialize */
  P2CONST(uint8, AUTOMATIC, PDUR_CONST) PathIdAtInit;
  #endif
  /* Configuration Id */
  PduR_PBConfigIdType ConfigurationId;
  /* Max PduId of transmission */
  #if ((PDUR_IF_TRANSMIT == STD_ON)||(PDUR_TP_TRANSMIT == STD_ON))
  PduIdType UpTransmitMaxPduId;
  #endif
  /* Max PduId of interface and transport reception */
  #if ((PDUR_TP_RXINDICATION == STD_ON) || (PDUR_LO_RXINDICATION == STD_ON))
  PduIdType IfTpRxIndicationMaxPduId;
  #endif
  /* Max PduId of interface and transport confirmation */
  #if ((PDUR_TP_TXCONFIRMATION == STD_ON) ||\
    (PDUR_LO_TXCONFIRMATION == STD_ON))
  PduIdType IfTpConfirmationMaxPduId;
  #endif
  /* Total interface routing paths that use buffer */
  #if (PDUR_TX_BUFFER_ROUTING_COUNT > PDUR_ZERO)
  uint16 TxBufRoutingCount;
  #endif
  /* Total transport routing paths that use buffer */
  #if (PDUR_TP_BUFFER_ROUTING_COUNT > PDUR_ZERO)
  uint16 TpBufRoutingCount;
  #endif
  /* Total transport routing paths that use buffer */
  #if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON)
  uint16 RoutingPathGroupMaxId;
  /* Routing path group multi of 32 count */
  uint16 PathGroupMulti32Count;
  #endif
  /* Total transport routing paths that use buffer */
  #if ((PDUR_TP_TXCONFIRMATION == STD_ON) &&\
    (PDUR_TP_GATEWAY_OPERATION == STD_ON))
  uint16 TpGWLowDestCount;
  #endif
} PduR_PBConfigType;
#else
typedef struct
{
  uint8 dummy;
} PduR_PBConfigType;
#endif
/*******************************************************************************
**                     Service Id's                                           **
*******************************************************************************/
/* @Trace: PduR_SUD_MACRO_003 */
/* Service ID for PduR_Init */
#define PDUR_INIT_SID                     ((uint8)0xF0)

/* Service ID for PduR_GetVersionInfo */
#define PDUR_GET_VERSION_SID              ((uint8)0xF1)

/* Service ID for PduR_GetConfigurationId */
#define PDUR_GET_CONFIG_ID_SID            ((uint8)0xF2)

/* Service ID for  PduR_EnableRouting*/
#define PDUR_ENABLE_ROUTING_SID           ((uint8)0xF3)

/* Service ID for  PduR_DisableRouting*/
#define PDUR_DISABLE_ROUTING_SID          ((uint8)0xF4)

/* Service ID for  PduR_GetGwBufferStatus*/
#define PDUR_GET_GW_BUFFER_STATUS_SID     ((uint8)0xF5)

/* Service ID for  PduR_ComTransmit */
#define PDUR_TRANSMIT_SID                 ((uint8)0x49)

/* Service ID for  PduR_<User:Up>CancelTransmit  */
#define PDUR_CANCEL_TRANSMIT_SID          ((uint8)0x4A)

/* Service ID for  PduR_<User:Up>CancelReceive  */
#define PDUR_CANCEL_RECEIVE_SID           ((uint8)0x4C)

/* Service ID for  PduR_<Lo>RxIndication     */
#define PDUR_RX_INDICATION_SID            ((uint8)0x42)

/* Service ID for  PduR_<Lo>TxConfirmation   */
#define PDUR_TX_CONFIRMATION_SID          ((uint8)0x40)

/* Service ID for  PduR_<Lo>TriggerTransmit */
#define PDUR_TRIGGER_TRANSMIT_SID         ((uint8)0x41)

/* Service ID for  PduR_<LoTp>CopyRxData    */
#define PDUR_COPYRX_DATA_SID              ((uint8)0x44)

/* Service ID for  PduR_<LoTp>RxIndication  */
#define PDUR_TP_RX_INDICATION_SID         ((uint8)0x45)

/* Service ID for  PduR_<LoTp>StartOfReception */
#define PDUR_STARTOF_RECEPTION_SID        ((uint8)0x46)

/* Service ID for  PduR_<LoTp>CopyTxData     */
#define PDUR_COPYTX_DATA_SID              ((uint8)0x43)

/* Service ID for  PduR_<LoTp>TxConfirmation     */
#define PDUR_TP_TX_CONFIRMATION_SID    ((uint8)0x48)


/*******************************************************************************
**                                  Macros                                    **
*******************************************************************************/
/* polyspace<MISRA-C:19.7:Not a defect:Justified> use function like-macro for removing unused argument compiler warning */
#define PDUR_UNUSED(x)                            do { \
                                                    if((uint32)(x) != \
                                                    (uint32)PDUR_ZERO) {} \
                                                  } while(0)

/* polyspace<MISRA-C:19.7:Not a defect:Justified> use function like-macro for removing unused argument compiler warning */
#define PDUR_UNUSED_PTR(x)                        do { \
                                                    if((x) != NULL_PTR) {} \
                                                  } while(0)


/*******************************************************************************
**                     Global Data                                            **
*******************************************************************************/
/* @Trace: SRS_BSW_00400 */
/* @Trace: PduR_SUD_CONSTVAR_001 */
#if (PDUR_VARIANT_POSTBUID_SUPPORT == STD_ON)
#define PDUR_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "MemMap.h"
extern CONST(PduR_PBConfigType, PDUR_CONST) PduR_Config_Variant_FL;
#define PDUR_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "MemMap.h"

#define PDUR_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "MemMap.h"
extern CONST(PduR_PBConfigType, PDUR_CONST) PduR_Config_Variant_FR;
#define PDUR_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "MemMap.h"

#define PDUR_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "MemMap.h"
extern CONST(PduR_PBConfigType, PDUR_CONST) PduR_Config_Variant_RL;
#define PDUR_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "MemMap.h"

#define PDUR_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "MemMap.h"
extern CONST(PduR_PBConfigType, PDUR_CONST) PduR_Config_Variant_RR;
#define PDUR_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
#include "MemMap.h"
#endif
/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
#define PDUR_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void,PDUR_CODE) PduR_Init(
  P2CONST(PduR_PBConfigType, AUTOMATIC, PDUR_APPL_CONST) ConfigPtr);
#define PDUR_STOP_SEC_CODE
#include "MemMap.h"

#if (PDUR_VARIANT_POSTBUID_SUPPORT == STD_ON)
#define PDUR_START_SEC_CODE
#include "MemMap.h"
extern FUNC(PduR_PBConfigIdType,PDUR_CODE) PduR_GetConfigurationId(void);
#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif

#if (PDUR_VERSION_INFO_API == STD_ON)
#define PDUR_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void,PDUR_CODE) PduR_GetVersionInfo
    (P2VAR(Std_VersionInfoType, AUTOMATIC,PDUR_APPL_DATA) versioninfo);

#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif /* End of if (PDUR_VERSION_INFO_API == STD_ON) */

#if (PDUR_ZERO_COST_OPERATION == STD_OFF)
#if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON)
#define PDUR_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, PDUR_CODE) PduR_EnableRouting(PduR_RoutingPathGroupIdType id);

#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif /* End of if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON) */
#endif /* End of if (PDUR_ZERO_COST_OPERATION == STD_OFF) */

#if (PDUR_ZERO_COST_OPERATION == STD_OFF)
#if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON)
#define PDUR_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void,
  PDUR_CODE) PduR_DisableRouting(PduR_RoutingPathGroupIdType id,
  boolean initialize);

#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif /* End of if (PDUR_ROUTINGPATH_GROUP_SUPPORT == STD_ON) */
#endif /* End of if (PDUR_ZERO_COST_OPERATION == STD_OFF) */

#if (PDUR_IF_GATEWAY_OPERATION == STD_ON)
#if (PDUR_FIFO_TX_BUFFER_SUPPORT == STD_ON)
#define PDUR_START_SEC_CODE
#include "MemMap.h"
/* Rx Buffer is always smaller than when this API called. */
extern FUNC(void, PDUR_CODE) PduR_GetGwBufferStatus(PduIdType LddPduRSrcPduId, 
  P2VAR(PduR_GwBufferStatus, AUTOMATIC, PDUR_VAR) LpGwStatus);
#define PDUR_STOP_SEC_CODE
#include "MemMap.h"
#endif
#endif

#endif /* PDUR_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
