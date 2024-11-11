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
**  SRC-MODULE: CanIf_Config.c                                                **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR CanIf                                                 **
**                                                                            **
**  PURPOSE   : Provision of variables of which value is set at link time     **
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
** 1.0.9    03-Oct-2022    HieuTM8        #CP44-832                           **
** 1.0.5    30-Jun-2022    HieuTM8        #CP44-130                           **
** 1.0.1    22-Sep-2021    HieuTM8        #20891                              **
** 1.0.0    21-Dec-2020    SJ Kim         Initialization                      **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "CanIf_PCTypes.h"
#include "CanIf_Ram.h"

#if (STD_ON == CANIF_PDUR_CALLBACK)
#include "PduR_CanIf.h"          /* PduR Header file */
#endif
#if (STD_ON == CANIF_CANTP_CALLBACK)
#include "CanTp.h"           /* Callback CanTp Header file */
#endif
#if (STD_ON == CANIF_CANNM_CALLBACK)
#include "CanNm.h"           /* Callback CanNm  Header file */
#endif
#if (STD_ON == CANIF_OSEKNM_CALLBACK)
#include "OsekNm.h"           /* Callback OsekNm  Header file */
#endif
#if (STD_ON == CANIF_RX_J1939TP_CALLBACK)
#include "J1939Tp.h"         /* Callback J1939Tp Header file */
#endif
#if (STD_ON == CANIF_RX_J1939NM_CALLBACK)
#include "J1939Nm.h"         /* Callback J1939Tp Header file */
#endif
#if (STD_ON == CANIF_RX_XCP_CALLBACK)
#include "Xcp.h"             /* Callback XCP Header file */
#endif

#define CANIF_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

#if (STD_ON == CANIF_RX_MULTIPLE_CALLBACK)
  CONSTP2CONST(CanIf_RxCbkUserType, AUTOMATIC, CANIF_CONST) CanIf_RxMulCbkUser = &CanIf_RxCbkUser[0];
#else
  CONST(CanIf_RxCbkUserType, CANIF_CONST) CanIf_RxSingleCbkUser[] =
  {
    {
  #if (STD_ON == CANIF_RX_PDUR_CALLBACK)
    #ifdef CANIF_PDUR_RXIND_MACRO
      &CANIF_PDUR_RXIND_MACRO
    #else
      NULL_PTR
    #endif
  #else
      NULL_PTR
  #endif
    },
    {
  #if (STD_ON == CANIF_RX_CANTP_CALLBACK)
    #ifdef CANIF_CANTP_RXIND_MACRO
      &CANIF_CANTP_RXIND_MACRO
    #else
      NULL_PTR
    #endif
  #else
      NULL_PTR
  #endif
    },
    {
  #if (STD_ON == CANIF_RX_CANNM_CALLBACK)
    #ifdef CANIF_CANNM_RXIND_MACRO
      &CANIF_CANNM_RXIND_MACRO
    #else
      NULL_PTR
    #endif
  #else
      NULL_PTR
  #endif
    },
    {
  #if (STD_ON == CANIF_RX_CDD_CALLBACK)
    #ifdef CANIF_CDD_RXIND_MACRO
      &CANIF_CDD_RXIND_MACRO
    #else
      NULL_PTR
    #endif
  #else
      NULL_PTR
  #endif
    },
    {
  #if (STD_ON == CANIF_RX_J1939TP_CALLBACK)
    #ifdef CANIF_J1939TP_RXIND_MACRO
      &CANIF_J1939TP_RXIND_MACRO
    #else
      NULL_PTR
    #endif
  #else
      NULL_PTR
  #endif
    },
    {
  #if (STD_ON == CANIF_RX_XCP_CALLBACK)
    #ifdef CANIF_XCP_RXIND_MACRO
      &CANIF_XCP_RXIND_MACRO
    #else
      NULL_PTR
    #endif
  #else
      NULL_PTR
  #endif
    },
    {
  #if (STD_ON == CANIF_RX_OSEKNM_CALLBACK)
    #ifdef CANIF_OSEKNM_RXIND_MACRO
      &CANIF_OSEKNM_RXIND_MACRO
    #else
      NULL_PTR
    #endif
  #else
      NULL_PTR
  #endif
    },
    {
  #if (STD_ON == CANIF_RX_J1939NM_CALLBACK)
    #ifdef CANIF_J1939NM_RXIND_MACRO
      &CANIF_J1939NM_RXIND_MACRO
    #else
      NULL_PTR
    #endif
  #else
      NULL_PTR
  #endif
    },
    {
  #if (STD_ON == CANIF_RX_CANTSYN_CALLBACK)
    #ifdef CANIF_CANTSYN_RXIND_MACRO
      &CANIF_CANTSYN_RXIND_MACRO
    #else
      NULL_PTR
    #endif
  #else
      NULL_PTR
  #endif
    }
  };
#endif

#if (STD_ON == CANIF_TX_MULTIPLE_CALLBACK)
  CONSTP2CONST(CanIf_TxCbkUserType, AUTOMATIC, CANIF_CONST) CanIf_TxMulCbkUser = &CanIf_TxCbkUser[0];
#else
  CONST(CanIf_TxCbkUserType, CANIF_CONST) CanIf_TxSingleCbkUser[] =
  {
    {
  #if (STD_ON == CANIF_TX_PDUR_CALLBACK)
    #ifdef CANIF_PDUR_TXCNFRM_MACRO
      &CANIF_PDUR_TXCNFRM_MACRO
    #else
      NULL_PTR
    #endif
  #else
      NULL_PTR
  #endif
    },
    {
  #if (STD_ON == CANIF_TX_CANTP_CALLBACK)
    #ifdef CANIF_CANTP_TXCNFRM_MACRO
      &CANIF_CANTP_TXCNFRM_MACRO
    #else
      NULL_PTR
    #endif
  #else
      NULL_PTR
  #endif
    },
    {
  #if (STD_ON == CANIF_TX_CANNM_CALLBACK)
    #ifdef CANIF_CANNM_TXCNFRM_MACRO
      &CANIF_CANNM_TXCNFRM_MACRO
    #else
      NULL_PTR
    #endif
  #else
      NULL_PTR
  #endif
    },
    {
  #if (STD_ON == CANIF_TX_CDD_CALLBACK)
    #ifdef CANIF_CDD_TXCNFRM_MACRO
      &CANIF_CDD_TXCNFRM_MACRO
    #else
      NULL_PTR
    #endif
  #else
      NULL_PTR
  #endif
    },
    {
  #if (STD_ON == CANIF_TX_J1939TP_CALLBACK)
    #ifdef CANIF_J1939TP_TXCNFRM_MACRO
      &CANIF_J1939TP_TXCNFRM_MACRO
    #else
      NULL_PTR
    #endif
  #else
      NULL_PTR
  #endif
    },
    {
  #if (STD_ON == CANIF_TX_XCP_CALLBACK)
    #ifdef CANIF_XCP_TXCNFRM_MACRO
      &CANIF_XCP_TXCNFRM_MACRO
    #else
      NULL_PTR
    #endif
  #else
      NULL_PTR
  #endif
    },
    {
  #if (STD_ON == CANIF_TX_OSEKNM_CALLBACK)
    #ifdef CANIF_OSEKNM_TXCNFRM_MACRO
      &CANIF_OSEKNM_TXCNFRM_MACRO
    #else
      NULL_PTR
    #endif
  #else
      NULL_PTR
  #endif
    },
    {
  #if (STD_ON == CANIF_TX_J1939NM_CALLBACK)
    #ifdef CANIF_J1939NM_TXCNFRM_MACRO
      &CANIF_J1939NM_TXCNFRM_MACRO
    #else
      NULL_PTR
    #endif
  #else
      NULL_PTR
  #endif
    },
    {
  #if (STD_ON == CANIF_TX_CANTSYN_CALLBACK)
    #ifdef CANIF_CANTSYN_TXCNFRM_MACRO
      &CANIF_CANTSYN_TXCNFRM_MACRO
    #else
      NULL_PTR
    #endif
  #else
      NULL_PTR
  #endif
    }
  };
#endif

/* @Trace: SWS_CANIF_00883 */
#if (STD_ON == CANIF_TRIGGER_TRANSMIT_SUPPORT)
CONST(CanIf_TxCbkTriggerUserType, CANIF_CONST) CanIf_TxSingleCbkTriggerUser[] =
{
  {
	  &CANIF_PDUR_TRIGGER_TRANSMIT_MACRO
  },
  {
    &CANIF_CDD_TRIGGER_TRANSMIT_MACRO
  }
};
#endif /*#if (STD_ON == CANIF_TRIGGER_TRANSMIT_SUPPORT)*/

#define CANIF_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"


/* define for Post-Build */
#if (STD_ON == CANIF_VARIANT_POSTBUILD_SUPPORT)

#define CANIF_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "MemMap.h"
/* Structure for Controller */
P2CONST(CanIf_ControllerConfigType, AUTOMATIC, CANIF_CONST) CanIfControllerConfig;
#define CANIF_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "MemMap.h"

#if ((CANIF_DEV_ERROR_DETECT == STD_ON) || CANIF_MULTIPLE_CANDRV_SUPPORT )
#define CANIF_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "MemMap.h"
P2CONST(CanIf_HrhInitType, AUTOMATIC, CANIF_CONST) CanIfHrhInit;
#define CANIF_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "MemMap.h"
#endif

#define CANIF_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "MemMap.h"
P2CONST(CanIf_HrhType,AUTOMATIC, CANIF_CONST) CanIfHrh;
#define CANIF_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "MemMap.h"

#define CANIF_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "MemMap.h"
P2CONST(CanIf_RxLpduType, AUTOMATIC,CANIF_VAR) CanIfRxLpdu;
#define CANIF_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "MemMap.h"

#define CANIF_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "MemMap.h"
P2CONST(CanIf_TxLpduType,AUTOMATIC, CANIF_CONST) CanIfTxLpdu;
#define CANIF_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "MemMap.h"

#if (CANIF_TX_QUEUE == STD_ON)
#define CANIF_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "MemMap.h"
P2CONST(CanIf_TxBufferType,AUTOMATIC, CANIF_CONST) CanIfTxBuffer;
#define CANIF_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "MemMap.h"
#endif

#define CANIF_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "MemMap.h"
P2CONST(uint16, AUTOMATIC, CANIF_CONST) CanIfHrhMapArray;
#define CANIF_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "MemMap.h"

#define CANIF_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "MemMap.h"
P2CONST(uint16, AUTOMATIC, CANIF_CONST) CanIfTxBasicPduIndexMapping;
#define CANIF_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "MemMap.h"

#endif

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
