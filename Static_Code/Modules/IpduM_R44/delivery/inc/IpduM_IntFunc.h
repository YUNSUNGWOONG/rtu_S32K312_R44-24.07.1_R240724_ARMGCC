/*******************************************************************************
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  This source code is permitted to be used only in projects contracted      **
**  with Hyundai Autoever, and any other use is prohibited.                   **
**  If you use it for other purposes or change the source code,               **
**  you may take legal responsibility.                                        **
**  In this case, There is no warranty and technical support.                 **
**                                                                            **
**  SRC-MODULE: IpduM_IntFunc.h                                               **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR IpduM Module                                          **
**                                                                            **
**  PURPOSE   : Provision of header file for IpudM_IntFunc.c                  **
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
** 1.0.7          27-Jul-2023         HaoTA4           CP44-2462              **
** 1.0.6          27-Jan-2023         JW Oh            CP44-1590              **
** 1.0.5          16-Dec-2022         NhatTD2          CP44-973               **
** 1.0.2          27-Jun-2022         DuyNHP2          CP44-141               **
** 1.0.1          10-Mar-2022         DuyNHP2          R44-Redmine #24418     **
** 1.0.0          15-Dec-2020         JsLim            Initial Version        **
*******************************************************************************/

#ifndef IPDUM_INTFUNC_H
#define IPDUM_INTFUNC_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "IpduM_Cfg.h"
#include "IpduM_IntTypes.h"

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
#define IPDUM_INTFUNC_AR_RELEASE_MAJOR_VERSION       (0x04u)
#define IPDUM_INTFUNC_AR_RELEASE_MINOR_VERSION       (0x04u)

#if(IPDUM_ENABLE_MODULE == STD_ON)

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
/* Remap invoked API if enabling COM invocation optimization */
#if (IPDUM_COM_SUPPORT_DIRECT == STD_ON)
#define IpduM_UpRxIndFunc                   Com_RxIndication
#define IpduM_UpTriggerTxFunc               Com_TriggerTransmit
#define IpduM_UpTxConfFunc                  Com_TxConfirmation
#else /* (IPDUM_COM_SUPPORT_DIRECT == STD_OFF) */
#define IpduM_UpRxIndFunc                   PduR_IpduMRxIndication
#define IpduM_UpTriggerTxFunc               PduR_IpduMTriggerTransmit
#define IpduM_UpTxConfFunc                  PduR_IpduMTxConfirmation
#endif /* End of #if (IPDUM_COM_SUPPORT_DIRECT == STD_ON) */

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
#define IPDUM_START_SEC_CODE
#include "MemMap.h"

#if (IPDUM_DEV_ERROR_DETECT == STD_ON)
extern FUNC(uint8, IPDUM_CODE) IpduM_DetCheckFuncs(
  uint8 ApiId, PduIdType CheckedId, PduIdType MaxId,
  P2CONST(PduInfoType, AUTOMATIC, IPDUM_APPL_DATA) PduInfoPtr);
#endif

/*******************************************************************************
**            Internal function for Tx Pathway                                **
*******************************************************************************/
#if (IPDUM_TX_IPDU == STD_ON)
extern FUNC(void, IPDUM_CODE) IpduM_InitMux(void);

extern FUNC(Std_ReturnType, IPDUM_CODE) IpduM_FetchTxMuxIpduPart(
    IpduM_TxPartIntType TxInIpduId);

extern FUNC(Std_ReturnType, IPDUM_CODE) IpduM_TxIpduMux(
  IpduM_TxPartIntType TxInIpduId,
  P2CONST(PduInfoType, AUTOMATIC, IPDUM_CONST) PduInfoPtr);

FUNC(Std_ReturnType, IPDUM_CODE) IpduM_StoreDynIndAndUpdrJIT(
  boolean triggerFlag,
  IpduM_TxPartIntType secPartIdx, 
  IpduM_TxPartIntType dynPartIdx, IpduM_TxPartIntType TxOutIpduId);
#endif

#if (IPDUM_TX_TRIGGERTRANS_IPDU == STD_ON)
extern FUNC(Std_ReturnType, IPDUM_CODE) IpduM_TriggerTxIpduMux(
  IpduM_TxConfIntType TxOutIpduId,
  P2VAR(PduInfoType, AUTOMATIC, IPDUM_APPL_DATA) PduInfoPtr);
#endif

#if (IPDUM_TX_CONF_IPDU == STD_ON)
extern FUNC(void, IPDUM_CODE) IpduM_TxConfirmIpduMux(
  IpduM_TxConfIntType TxOutIpduId, Std_ReturnType result);
#endif
/*******************************************************************************
**            Internal function for Rx Pathway                                **
*******************************************************************************/
#if (IPDUM_RX_IPDU == STD_ON)
#if (IPDUM_RX_DYNAMIC_IPDU == STD_ON)
extern FUNC(uint16, IPDUM_CODE) IpduM_GetSelBitField(
  IpduM_RxMuxIntType SelFieldId, boolean ByteOrder,
  P2CONST(uint8, AUTOMATIC, IPDUM_APPL_DATA) DestPtr);

#if (IPDUM_BINARY_SEARCH == STD_ON)
extern FUNC(IpduM_RxPartIntType, IPDUM_CODE) IpduM_BinarySearch(
  IpduM_RxPartIntType RxDynPartId, IpduM_RxPartIntType Size, uint16 Key);
#endif

#if (IPDUM_LINEAR_SEARCH == STD_ON)
FUNC(IpduM_RxPartIntType, IPDUM_CODE) IpduM_LinearSearch(
  IpduM_RxPartIntType RxDynPartId, IpduM_RxPartIntType Size, uint16 Key);
#endif
#endif /* (IPDUM_RX_DYNAMIC_IPDU == STD_ON) */

extern FUNC(void, IPDUM_CODE) IpduM_RxIpduMux(
  IpduM_RxMuxIntType RxIpduId,
  P2CONST(PduInfoType, AUTOMATIC, IPDUM_APPL_DATA) PduInfoPtr);
#endif /* (IPDUM_RX_IPDU == STD_ON) */


/*******************************************************************************
**            Internal function for Tx ContainerPdu                           **
*******************************************************************************/
#if (IPDUM_TX_CONTAINER == STD_ON)
extern FUNC(void, IPDUM_CODE) IpduM_InitContainer(void);

extern FUNC(void, IPDUM_CODE) IpduM_TxQueuedContainerPdu(
    IpduM_TxContainedIntType ContainerId);
extern FUNC(void, IPDUM_CODE) IpduM_TriggerContainerPdu(
  IpduM_TxContainerIntType ContainerId, boolean AddedTxContainedFlag);

extern FUNC(Std_ReturnType, IPDUM_CODE) IpduM_ContainerTransmit(
  IpduM_TxContainedIntType ContainedId,
  P2CONST(PduInfoType, AUTOMATIC, IPDUM_APPL_DATA) PduInfoPtr);

#if (IPDUM_TX_CONF_CONTAINER == STD_ON)
extern FUNC(void, IPDUM_CODE) IpduM_ContainerTxConfirmation(
  IpduM_TxContainerIntType ContainerId, Std_ReturnType result);
#endif

extern FUNC(Std_ReturnType, IPDUM_CODE) IpduM_ContainerTriggerTransmit(
  IpduM_TxContainerIntType ContainerId,
  P2VAR(PduInfoType, AUTOMATIC, IPDUM_APPL_DATA) PduInfoPtr);
#endif /* (IPDUM_TX_CONTAINER == STD_ON) */
/*******************************************************************************
**            Internal function for Rx ContainerPdu                           **
*******************************************************************************/
#if (IPDUM_RX_CONTAINER == STD_ON)
extern FUNC(void, IPDUM_CODE) IpduM_ContainerRxIndication(
  IpduM_RxContainerIntType ContainerId,
  P2CONST(PduInfoType, AUTOMATIC, IPDUM_APPL_DATA) PduInfoPtr);

#if (IPDUM_RX_DEFFERRED_CONTAINER == STD_ON)
extern FUNC(void, IPDUM_CODE) IpduM_ExtractQueuedRxContainer(
  IpduM_RxContainerIntType ContainerId);
#endif

#endif /* (IPDUM_RX_CONTAINER == STD_ON) */

/*******************************************************************************
**            Internal function for Checking Header Type                      **
*******************************************************************************/
#if ((IPDUM_TX_CONTAINER == STD_ON) || ((IPDUM_RX_CONTAINER == STD_ON) && (IPDUM_RX_DYNAMIC_CONTAINER == STD_ON)))
extern FUNC(void, IPDUM_CODE) IpduM_ReadContainerHeader(
  P2CONST(uint8, AUTOMATIC, IPDUM_APPL_DATA) BufPtr,
  P2VAR(IpduM_HeaderFieldType, AUTOMATIC, IPDUM_APPL_DATA) Header,
  uint8 HeaderSize);
#endif

#if (IPDUM_TX_CONTAINER == STD_ON)
#if (IPDUM_TX_DYNAMIC_CONTAINER == STD_ON)
extern FUNC(void, IPDUM_CODE) IpduM_WriteContainerHeader(
  P2VAR(uint8, AUTOMATIC, IPDUM_APPL_DATA) BufPtr,
  P2CONST(IpduM_HeaderFieldType, AUTOMATIC, IPDUM_APPL_DATA) Header,
  uint8 HeaderSize);
#endif
#endif

#define IPDUM_STOP_SEC_CODE
#include "MemMap.h"

#endif /* IPDUM_ENABLE_MODULE == STD_ON */

#endif /* IPDUM_INTFUNC_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
