/*******************************************************************************
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  This source code is permitted to be used only in projects contracted      **
**  with Hyundai Autoever, and any other use is prohibited.                   **
**  If you use it for other purposes or change the source code,               **
**  you may take legal responsibility.                                        **
**  In this case, There is no warranty and technical support.                 **
**                                                                            **
**  SRC-MODULE: IpduM_Globals.c                                               **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR IpduM module                                          **
**                                                                            **
**  PURPOSE   : This file provides definitions of Global Variables used in    **
**              the module                                                    **
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

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "IpduM_Globals.h"

#if(IPDUM_ENABLE_MODULE == STD_ON)

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#define IPDUM_START_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"
/* Global variable to store Initialization status of IPDUM */
VAR(boolean, IPDUM_VAR) IpduM_InitStatus;
#define IPDUM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"

#if (IPDUM_VARIANT_POSTBUILD_SUPPORT == STD_ON)
#if ((IPDUM_TX_IPDU == STD_ON)||(IPDUM_SEGMENT_BITFIELD == STD_ON))
#define IPDUM_START_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"
P2CONST(IpduM_SegmentType, AUTOMATIC, IPDUM_CONST) IpduM_SegmentField;
#define IPDUM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"
#endif

#if ((IPDUM_TX_IPDU == STD_ON)||(IPDUM_TX_STATIC_IPDU ==STD_ON)|| \
     (IPDUM_JIT_UPDATE == STD_ON)||(IPDUM_TX_CONF_IPDU == STD_ON))
#define IPDUM_START_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"
P2CONST(IpduM_TxOutIpduType, AUTOMATIC, IPDUM_CONST) IpduM_TxOutIpdu;
#define IPDUM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"
#endif

#if ((IPDUM_TX_IPDU == STD_ON)||(IPDUM_JIT_UPDATE == STD_ON)|| \
     (IPDUM_TX_CONF_IPDU == STD_ON))
#define IPDUM_START_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"
P2CONST(IpduM_TxInIpduType, AUTOMATIC, IPDUM_CONST) IpduM_TxInIpdu;
#define IPDUM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"
#endif

#if ((IPDUM_RX_IPDU == STD_ON)&&(IPDUM_RX_DYNAMIC_IPDU == STD_ON))
#define IPDUM_START_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"
P2CONST(IpduM_RxMuxDynPartType, AUTOMATIC, IPDUM_CONST) IpduM_RxMuxDynPartArr;
P2CONST(IpduM_SelBitFieldType, AUTOMATIC, IPDUM_CONST) IpduM_SelBitField;
#define IPDUM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"
#endif

#if ((IPDUM_RX_IPDU == STD_ON) && \
       ((IPDUM_RX_STATIC_IPDU == STD_ON)||(IPDUM_RX_DYNAMIC_IPDU == STD_ON)))
#define IPDUM_START_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"
P2CONST(IpduM_RxIpduType, AUTOMATIC, IPDUM_CONST) IpduM_RxInIpdu;
#define IPDUM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"
#endif

#if ((IPDUM_TX_IPDU == STD_ON) || (IPDUM_TX_CONTAINER == STD_ON))
#define IPDUM_START_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"
P2CONST(IpduM_TxReqIntType, AUTOMATIC, IPDUM_CONST) IpduM_TxReqPduArr;
#define IPDUM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"
#endif

#if ((IPDUM_RX_IPDU == STD_ON) || (IPDUM_RX_CONTAINER == STD_ON))
#define IPDUM_START_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"
P2CONST(IpduM_RxIndIntType, AUTOMATIC, IPDUM_CONST) IpduM_RxIndPduArr;
#define IPDUM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"  
#endif

#if ((IPDUM_TX_CONF_IPDU == STD_ON) || (IPDUM_TX_CONF_CONTAINER == STD_ON))
#define IPDUM_START_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"
P2CONST(IpduM_TxConfIntType, AUTOMATIC, IPDUM_CONST)  IpduM_TxConfPduArr;
#define IPDUM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"  
#endif

#endif
/*******************************************************************************
**                      Variable for Library                                  **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

#endif /* IPDUM_ENABLE_MODULE == STD_ON */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
