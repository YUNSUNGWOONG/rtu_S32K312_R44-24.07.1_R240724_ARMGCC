/*******************************************************************************
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  This source code is permitted to be used only in projects contracted      **
**  with Hyundai Autoever, and any other use is prohibited.                   **
**  If you use it for other purposes or change the source code,               **
**  you may take legal responsibility.                                        **
**  In this case, There is no warranty and technical support.                 **
**                                                                            **
** SRC-MODULE: IpduM.h                                                        **
**                                                                            **
** TARGET    : All                                                            **
**                                                                            **
** PRODUCT   : AUTOSAR IpduM Module                                           **
**                                                                            **
** PURPOSE   : Provision of IpduM Module header                               **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision       Date                By               Description            **
********************************************************************************
** 1.0.6          27-Jan-2023         JW Oh            CP44-1590              **
** 1.0.4          06-Nov-2022         NhatTD2          CP44-612               **
** 1.0.2          27-Jun-2022         DuyNHP2          CP44-141               **
** 1.0.1          10-Mar-2022         DuyNHP2          R44-Redmine #24418     **
** 1.0.0          15-Dec-2020         JsLim            Initial Version        **
*******************************************************************************/

#ifndef IPDUM_H
#define IPDUM_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* Inclusion for NetworkHandleType */
#include "ComStack_Types.h"
#include "IpduM_IntTypes.h"

/* Inclusion for pre-processor switches */
#include "IpduM_Cfg.h"

#if(IPDUM_ENABLE_MODULE == STD_ON)

#if ((IPDUM_DEV_ERROR_DETECT == STD_ON) || \
     (IPDUM_TX_CONTAINER == STD_ON) || (IPDUM_RX_CONTAINER == STD_ON))
#include "Det.h"
#endif

#endif /* IPDUM_ENABLE_MODULE == STD_ON */

#if (IPDUM_VARIANT_POSTBUILD_SUPPORT == STD_ON)
#include "IpduM_PBcfg.h"
#endif


/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
/* Service ID for IpduM_GetVersionInfo */
#define IPDUM_GETVERSIONINFO_SID    (uint8)0x01
/* Service ID for IpduM_Transmit */
#define IPDUM_TRANSMIT_SID          (uint8)0x49
/* Service ID for IpduM_RxIndication */
#define IPDUM_RXINDICATION_SID      (uint8)0x42
/* Service ID for IpduM_TxConfirmation */
#define IPDUM_TXCONFIRMATION_SID    (uint8)0x40
/* Service ID for IpduM_TriggerTransmit */
#define IPDUM_TRIGGERTRANSMIT_SID   (uint8)0x41

/* Service ID for IpduM_MainFunctionRx */
#define IPDUM_MAINFUNCTIONRX_SID    (uint8)0x11

/*******************************************************************************
**                      DET Error Codes                                       **
*******************************************************************************/
#define IPDUM_E_NO_ERROR            (uint8)0xFF
/* ErrorId if API service called with wrong parameter */
#define IPDUM_E_PARAM               (uint8)0x10
/* ErrorId if  API service called with wrong Pointer */
#define IPDUM_E_PARAM_POINTER       (uint8)0x11
/* ErrorId if API service used without module initialization */
#define IPDUM_E_UNINIT              (uint8)0x20
/* ErrorId if Invalid configuration set selection */
#define IPDUM_E_INIT_FAILED         (uint8)0x21

/* ErrorId for Erroneous header detected */
#define IPDUM_E_HEADER              (uint8)0x30
/* ErrorId for Container Queue overflow */
#define IPDUM_E_QUEUEOVFL           (uint8)0x31
/* ErrorId for Partly or erroneous container received */
#define IPDUM_E_CONTAINER           (uint8)0x32
/*******************************************************************************
**                      MACROs                                                **
*******************************************************************************/
/* Instance ID */
#define IPDUM_INSTANCE_ID           (uint8)0x00

/* To prevent the unused argument compiler warning */
#define IPDUM_UNUSED(x)             (void)x


/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
#define IPDUM_START_SEC_CODE
#include "MemMap.h"

extern FUNC(void, IPDUM_CODE) IpduM_Init(
  P2CONST(IpduM_ConfigType, AUTOMATIC, IPDUM_APPL_CONST) config);

#if(IPDUM_ENABLE_MODULE == STD_ON)

#if (IPDUM_VERSION_INFO_API == STD_ON)
extern FUNC(void, IPDUM_CODE) IpduM_GetVersionInfo(
  P2VAR(Std_VersionInfoType, AUTOMATIC, IPDUM_VAR) versioninfo);
#endif

#if ((IPDUM_TX_IPDU == STD_ON) || (IPDUM_TX_CONTAINER == STD_ON))
extern FUNC(Std_ReturnType, IPDUM_CODE) IpduM_Transmit(
  PduIdType TxPduId,
  P2CONST(PduInfoType, AUTOMATIC, IPDUM_APPL_DATA) PduInfoPtr);
#endif


#if ((IPDUM_RX_IPDU == STD_ON) || (IPDUM_RX_CONTAINER == STD_ON))
extern FUNC(void, IPDUM_CODE) IpduM_RxIndication(
  PduIdType RxPduId,
  P2CONST(PduInfoType, AUTOMATIC, IPDUM_APPL_DATA) PduInfoPtr);
#endif /* ((IPDUM_RX_IPDU == STD_ON) || (IPDUM_RX_CONTAINER == STD_ON)) */


#if ((IPDUM_TX_CONF_IPDU == STD_ON) || (IPDUM_TX_CONF_CONTAINER == STD_ON))
extern FUNC(void, IPDUM_CODE) IpduM_TxConfirmation(
  PduIdType TxPduId, Std_ReturnType result);
#endif

#if ((IPDUM_TX_TRIGGERTRANS_IPDU == STD_ON) || \
     (IPDUM_TX_TRIGGERTRANSMIT_CONTAINER == STD_ON))
extern FUNC(Std_ReturnType, IPDUM_CODE) IpduM_TriggerTransmit(
  PduIdType TxPduId,
  P2VAR(PduInfoType, AUTOMATIC, IPDUM_APPL_DATA) PduInfoPtr);
#endif

#endif /* IPDUM_ENABLE_MODULE == STD_ON */

#define IPDUM_STOP_SEC_CODE
#include "MemMap.h"


#endif /* IPDUM_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
