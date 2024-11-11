/*******************************************************************************
**                                                                            **
**  (C) 2021 HYUNDAI AUTOEVER Co., Ltd.                                       **
**  Confidential Proprietary Information. Distribution Limited.               **
**  This source code is permitted to be used only in projects contracted      **
**  with Hyundai Autoever, and any other use is prohibited.                   **
**  If you use it for other purposes or change the source code,               **
**  you may take legal responsibility.                                        **
**  In this case, There is no warranty and technical support.                 **
**                                                                            **
**  SRC-MODULE:           CanNm_Cfg.c                                         **
**                                                                            **
**  PRODUCT   :           AUTOSAR CAN Network Manager module                  **
**                                                                            **
**  PURPOSE   :           This file contain function body for generic public  **
**                        API's.                                              **
**                                                                            **
**  HARDWARE DEPENDANT [Yes/No]: No                                           **
**                                                                            **
**  AUTOSAR RELEASE:  4.4.0                                                   **
*******************************************************************************/

/*******************************************************************************
**                      Generation Tool Information                           **
********************************************************************************
**  Framework Version: 1.1.5                                                  **
**  Module Version   : 1.2.0.0                                                **
**                                                                            **
**  Change History: Refer log file (use -l option to generate log file)       **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      File Generation Information                           **
*******************************************************************************/
/*
* INPUT FILE:      Configuration\Definition\ECUConfigurationParameters.arxml
*                  Configuration\Ecu\Ecud_CanIf.arxml           
*                  Configuration\Ecu\Ecud_CanNm.arxml           
*                  Configuration\Ecu\Ecud_CanSM.arxml           
*                  Configuration\Ecu\Ecud_ComM.arxml            
*                  Configuration\Ecu\Ecud_EcuC.arxml            
*                  Configuration\Ecu\Ecud_Nm.arxml              
*                  Configuration\Ecu\Ecud_PduR.arxml            
*                  Configuration\System\DBImport\DataTypes\AUTOSAR_DataTypes.arxml
*                  Configuration\System\DBImport\DataTypes\CanStack_DataTypes.arxml
*                  Generated\Bsw_Output\bswmd\Bswmd_CanNm.arxml 
*                  Static_Code\Modules\CanIf_R44\generator\CanIf_ECU_Configuration_PDF.arxml
*                  Static_Code\Modules\CanNm_R44\generator\CanNm_ECU_Configuration_PDF.arxml
*                  Static_Code\Modules\CanSM_R44\generator\CanSM_ECU_Configuration_PDF.arxml
*                  Static_Code\Modules\ComM_R44\generator\ComM_ECU_Configuration_PDF.arxml
*                  Static_Code\Modules\Nm_R44\generator\Nm_ECU_Configuration_PDF.arxml
*                  Static_Code\Modules\PduR_R44\generator\PduR_ECU_Configuration_PDF.arxml
* GENERATED ON: The time-stamp is removed
*/
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* Inclusion for CanNm Configuration header file */
#include "CanNm_Cfg.h"
/* Inclusion for CanNm Internal Type definition */
#include "CanNm_IntTypes.h"
/* Inclusion for CanNm Global Type definition */
#include "CanNm_Globals.h"

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#define CANNM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

/* Array for Pn Filter Mask Byte */
CONST(uint8, CANNM_CONST) CanNm_ArrayPnMaskByte[CANNM_NUMBER_OF_PN_FILTER_MASK_BYTE] =
{
  0x1,
  
  0x0,
  
  0x0,
  
  0x0
};

#define CANNM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

#define CANNM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

/* Structure of PN information */
CONST(CanNm_PnInfoType, CANNM_CONST) CanNm_structPnInfo =
{
  /* pnInfoLength */
  4,
  
  /* pnInfoOffset */
  4
};

#define CANNM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

#define CANNM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

/* Array of Tx Pdu */
CONST(CanNm_TxPdu, CANNM_CONST) CanNm_ArrayTxPdu[CANNM_NUMBER_OF_TXPDU] =
{
  {
    /* canNmTxPduId */
    0,
    
    /* canNmChannelIndex */
    0
  }
};

#define CANNM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

#define CANNM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

/* Array of Rx Pdu */
CONST(CanNm_RxPdu, CANNM_CONST) CanNm_ArrayRxPdu[CANNM_NUMBER_OF_RXPDU] =
{
  {
    /* canNmRxPduId */
    0,
    
    /* canNmChannelIndex */
    0
  }
};

#define CANNM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

#define CANNM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

/* Array of structure for each CANNM Channel Config Set */
CONST(CanNm_StaticChannel, CANNM_CONST)CanNm_ArrayStaticChannel[CANNM_NUMBER_OF_CHANNEL] =
{
  {
    /* waitBusSleepTime */
    300,
    
    /* ntwkTimeOutTime */
    200,
    
    /* repeatMsgTime */
    240,
    
    /* remoteSleepIndTime */
    1000,
    
    /* msgCycleTime */
    20,
    
    /* msgCycleOffset */
    1,
    
    /* msgTimeOutTime */
    1,
    
    /* immMsgCycleTime */
    2,
    
    /* txPduId */
    4,
    
    /* canNmTransmitHandleId */
    0,
    
    /* txTriggerUserPduId */
    4,
    
    /* carWakeupByte */
    4,
    
    /* carWkpNodeId */
    0,
    
    /* carWakeupMask */
    0,
    
    /* noOfImmediateNmTx */
    3,
    
    /* userDataLength */
    4,
    
    /* pduLength */
    8,
    
    /* pduNidPosition */
    CANNM_PDU_BYTE_0,
    
    /* userDataPosition */
    4,
    
    /* pduCbvPosition */
    CANNM_PDU_BYTE_1,
    
    /* nodeId */
    2,
    
    /* comMChannelId */
    0,
    
    /* busLoadRedActive */
    CANNM_FALSE,
    
    /* activeWakeupBitEnabled */
    CANNM_TRUE,
    
    /* allNmMessagesKeepAwake */
    CANNM_FALSE,
    
    /* pnEnabled */
    CANNM_TRUE,
    
    /* pnEraCalcEnabled */
    CANNM_FALSE,
    
    /* carWakeUpRxEnabled */
    CANNM_FALSE,
    
    /* carWakeUpFilterEnabled */
    CANNM_FALSE,
    
    /* pnHandleMultipleNetworkRequests */
    CANNM_FALSE,
    
    /* canIfTriggerTransmit */
    0,
    
    /* nodeDetectionEnabled */
    CANNM_TRUE,
    
    /* forcePnAvailabilityConfEnabled */
    CANNM_TRUE,
    
    /* nmStatePosition */
    CANNM_PDU_BYTE_3,
    
    /* nwRequestReasonPosition */
    CANNM_PDU_BYTE_2,
    
    /* userDataInitValue */
    255
  }
};

#define CANNM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"


/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
