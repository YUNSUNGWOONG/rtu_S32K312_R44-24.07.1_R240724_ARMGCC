/*******************************************************************************
**                                                                            **
**  (C) 2021 HYUNDAI AUTOEVER Co., Ltd.                                       **
**                                                                            **
**  Confidential Proprietary Information. Distribution Limited.               **
**  This source code is permitted to be used only in projects contracted      **
**  with Hyundai Autoever, and any other use is prohibited.                   **
**  If you use it for other purposes or change the source code,               **
**  you may take legal responsibility.                                        **
**  In this case, There is no warranty and technical support.                 **
**                                                                            **
**  SRC-MODULE:           CanTp_Cfg.c                                         **
**                                                                            **
**  PRODUCT   :           AUTOSAR CAN Transport Layer Module                  **
**                                                                            **
**  PURPOSE   :           This file contain function body for generic public  **
**                        API's.                                              **
**                                                                            **
**  HARDWARE DEPENDANT [Yes/No]: No                                           **
**                                                                            **
**  AUTOSAR RELEASE:  4.4.0                                                   **
********************************************************************************

********************************************************************************
**                      Generation Tool Information                           **
********************************************************************************
**  Framework version : 1.1.5                                                 **
**                                                                            **
**  Module version : 1.1.0.0                                                  **
**                                                                            **
**  Change History: Refer log file (use -l option to generate log file)       **
**                                                                            **
********************************************************************************

********************************************************************************
**                      File Generation Information                           **
*******************************************************************************/
/*
* INPUT FILE:      Configuration\Definition\ECUConfigurationParameters.arxml
*                  Configuration\Ecu\Ecud_CanIf.arxml           
*                  Configuration\Ecu\Ecud_CanTp.arxml           
*                  Configuration\Ecu\Ecud_Com.arxml             
*                  Configuration\Ecu\Ecud_EcuC.arxml            
*                  Configuration\Ecu\Ecud_PduR.arxml            
*                  Generated\Bsw_Output\bswmd\Bswmd_CanTp.arxml 
*                  Static_Code\Modules\CanIf_R44\generator\CanIf_ECU_Configuration_PDF.arxml
*                  Static_Code\Modules\CanTp_R44\generator\CanTp_ECU_Configuration_PDF.arxml
*                  Static_Code\Modules\Com_R44\generator\Com_ECU_Configuration_PDF.arxml
*                  Static_Code\Modules\PduR_R44\generator\PduR_ECU_Configuration_PDF.arxml
* GENERATED ON: The time-stamp is removed
*/


/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "CanTp.h"
#include "CanTp_PCTypes.h"



/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
#define    CANTP_CFG_C_AR_RELEASE_MAJOR_VERSION          0x04u
#define    CANTP_CFG_C_AR_RELEASE_MINOR_VERSION          0x04u
#define    CANTP_CFG_C_AR_RELEASE_REVISION_VERSION       0x00u
#define    CANTP_CFG_C_SW_MAJOR_VERSION                  0x01u
#define    CANTP_CFG_C_SW_MINOR_VERSION                  0x01u
#define    CANTP_CFG_C_SW_PATCH_VERSION                  0x00u


/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/
#if (CANTP_PCTYPES_AR_RELEASE_MAJOR_VERSION != \
  CANTP_CFG_C_AR_RELEASE_MAJOR_VERSION)
  #error "CanTp_Cfg.c : Mismatch in Specification Major Version"
#endif
#if (CANTP_PCTYPES_AR_RELEASE_MINOR_VERSION != \
  CANTP_CFG_C_AR_RELEASE_MINOR_VERSION)
  #error "CanTp_Cfg.c : Mismatch in Specification Minor Version"
#endif
#if (CANTP_PCTYPES_AR_RELEASE_REVISION_VERSION != \
  CANTP_CFG_C_AR_RELEASE_REVISION_VERSION)
  #error "CanTp_Cfg.c : Mismatch in Specification Revision Version"
#endif
#if (CANTP_PCTYPES_SW_MAJOR_VERSION != CANTP_CFG_C_SW_MAJOR_VERSION)
  #error "CanTp_Cfg.c : Mismatch in Software Major Version"
#endif
#if (CANTP_PCTYPES_SW_MINOR_VERSION != CANTP_CFG_C_SW_MINOR_VERSION)
  #error "CanTp_Cfg.c : Mismatch in Software Minor Version"
#endif




/*******************************************************************************
**                      Initialization Structure                              **
*******************************************************************************/
#define CANTP_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/* Array to store Channel specific data variables */
VAR(CanTp_ChannelRamType, CANTP_VAR) CanTp_ChannelTxRam[CANTP_TOTAL_RX_TX_CHANNELS];
VAR(CanTp_ChannelRamType, CANTP_VAR) CanTp_ChannelRxRam[CANTP_TOTAL_RX_TX_CHANNELS];

/* Array for N_As/N_Ar, N_Bs/N_Br, N_Cs/N_Cr Timers for all the channels */ 
VAR(uint16, CANTP_VAR) CanTp_Timers[CANTP_TOTAL_RX_TX_CHANNELS][CANTP_SIX];

/* Array for STMin timers of all channels */
VAR(uint8, CANTP_VAR) CanTp_StMinTimers[CANTP_TOTAL_RX_TX_CHANNELS];

#define CANTP_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

#define CANTP_START_SEC_CONST_8
#include "MemMap.h"

CONST(uint8, CANTP_CONST) CanTp_ChannelMapping[] = 
{
    0x00,
    
    0x01,
    
    0x02
};
#define CANTP_STOP_SEC_CONST_8
#include "MemMap.h"


#define CANTP_START_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
#include "MemMap.h"

CONST(CanTp_RxExtPdusType, CANTP_CONST) CanTp_RxExtFcPdus[] =
{
   /* RxPDU 0 - RxPduID_0 */
   {
       /* NoOfPdusOrSduId */
       0,
       
       /* RxNSaOrNAeSduMapIndex */
       CANTP_INVALID,
       
       /* AddressingMode */
       CANTP_STANDARD_ADDRESS,
       
       /* InPduwithMetaDataSts */
       CANTP_FALSE
   },
   
   /* RxPDU 1 - RxPduID_1 */
   {
       /* NoOfPdusOrSduId */
       1,
       
       /* RxNSaOrNAeSduMapIndex */
       CANTP_INVALID,
       
       /* AddressingMode */
       CANTP_STANDARD_ADDRESS,
       
       /* InPduwithMetaDataSts */
       CANTP_FALSE
   },
   
   /* RxPDU 2 - RxPduID_2 */
   {
       /* NoOfPdusOrSduId */
       CANTP_INVALID,
       
       /* RxNSaOrNAeSduMapIndex */
       CANTP_INVALID,
       
       /* AddressingMode */
       CANTP_INVALID,
       
       /* InPduwithMetaDataSts */
       CANTP_INVALID
   }
   
};

#define CANTP_STOP_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
#include "MemMap.h"  

#define CANTP_START_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
#include "MemMap.h"

CONST(CanTp_RxExtPdusType, CANTP_CONST) CanTp_RxExtPdus[] =
{
    /* RxPDU 0 - RxPduID_0 */
    {
        /* NoOfPdusOrSduId */
        0,
        
        /* RxNSaOrNAeSduMapIndex */
        CANTP_INVALID,
        
        /* AddressingMode */
        CANTP_STANDARD_ADDRESS,
        
        /* InPduwithMetaDataSts */
        CANTP_FALSE
    },
    
    /* RxPDU 1 - RxPduID_1 */
    {
        /* NoOfPdusOrSduId */
        1,
        
        /* RxNSaOrNAeSduMapIndex */
        CANTP_INVALID,
        
        /* AddressingMode */
        CANTP_STANDARD_ADDRESS,
        
        /* InPduwithMetaDataSts */
        CANTP_FALSE
    },
    
    /* RxPDU 2 - RxPduID_2 */
    {
         /* NoOfPdusOrSduId */
         2,
         
         /* RxNSaOrNAeSduMapIndex */
         CANTP_INVALID,
         
         /* AddressingMode */
         CANTP_STANDARD_ADDRESS,
         
         /* InPduwithMetaDataSts */
         CANTP_FALSE
    }
    
};

#define CANTP_STOP_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
#include "MemMap.h"  

#define CANTP_START_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
#include "MemMap.h"


CONST(CanTp_RxNSduDynamicType, CANTP_CONST) CanTp_RxSduDynamic[] =
{
    /* RxNSDU 0 - CanTpConfig_CanTpChannel_0_Pdu_DcmIPdu_FD_CAN1_Diag_Msg_TP_Phys_Req_FD_CAN1_CanTpRxNSdu_0_Pdu_DcmIPdu_FD_CAN1_Diag_Msg_TP_Phys_Req_FD_CAN1 */
    {
      /* UpTargetPduId */
        0x02,
    
      /* LoTxFcTargetPduId */
        0x07,
    
      /* NarTimeoutValue */
        0xC8,
    
      /* NbrTimeoutValue */
        0x01,
    
      /* NcrTimeoutValue */
        0xC8,
    
      /* RxWftMax */
        0x00
    },
    /* RxNSDU 1 - CanTpConfig_CanTpChannel_1_Pdu_ISignalIPdu_FD_CAN1_Normal_Msg_FD_TP_01_B_CanTpRxNSdu_1_Pdu_ISignalIPdu_FD_CAN1_Normal_Msg_FD_TP_01_B */
    {
      /* UpTargetPduId */
        0x00,
    
      /* LoTxFcTargetPduId */
        0x06,
    
      /* NarTimeoutValue */
        0xC8,
    
      /* NbrTimeoutValue */
        0x01,
    
      /* NcrTimeoutValue */
        0xC8,
    
      /* RxWftMax */
        0x00
    },
    /* RxNSDU 2 - CanTpConfig_CanTpChannel_2_RxOnly_Pdu_DcmIPdu_FD_CAN1_Diag_Msg_TP_Func_FD_CAN1_CanTpRxNSdu_2_Pdu_DcmIPdu_FD_CAN1_Diag_Msg_TP_Func_FD_CAN1 */
    {
      /* UpTargetPduId */
        0x03,
    
      /* LoTxFcTargetPduId */
        CANTP_INVALID,
    
      /* NarTimeoutValue */
        0xC8,
    
      /* NbrTimeoutValue */
        0x01,
    
      /* NcrTimeoutValue */
        0xC8,
    
      /* RxWftMax */
        0x00
    }
};

#define CANTP_STOP_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
#include "MemMap.h"  


#define CANTP_START_SEC_CONST_8
#include "MemMap.h"

CONST(CanTp_ChannelType, CANTP_CONST) CanTp_RxSduMap[] =
{
    /* FcNPduConfirmationPdu_0 */
    0x00,
    
    /* FcNPduConfirmationPdu_1 */
    0x01
    
};
#define CANTP_STOP_SEC_CONST_8
#include "MemMap.h"


#define CANTP_START_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
#include "MemMap.h"

CONST(CanTp_RxNsduStaticType, CANTP_CONST) CanTp_RxSduStatic[] =
{
    /* RxNSDU 0 - CanTpConfig_CanTpChannel_0_Pdu_DcmIPdu_FD_CAN1_Diag_Msg_TP_Phys_Req_FD_CAN1_CanTpRxNSdu_0_Pdu_DcmIPdu_FD_CAN1_Diag_Msg_TP_Phys_Req_FD_CAN1 */
    {
        /* ChannelId */
        0x00,
        
        /* TaType */
        CANTP_PHYSICAL_ADDRESS,
        
        /* AddressingMode */
        CANTP_STANDARD_ADDRESS,
        
        /* RxPaddingActivation */
        CANTP_TRUE,
        
        /* InPduwithMetaDataSts */
        CANTP_FALSE,
        	
        /* OutPduWithMetaData */
        CANTP_FALSE
    },
    
    /* RxNSDU 1 - CanTpConfig_CanTpChannel_1_Pdu_ISignalIPdu_FD_CAN1_Normal_Msg_FD_TP_01_B_CanTpRxNSdu_1_Pdu_ISignalIPdu_FD_CAN1_Normal_Msg_FD_TP_01_B */
    {
        /* ChannelId */
        0x01,
        
        /* TaType */
        CANTP_PHYSICAL_ADDRESS,
        
        /* AddressingMode */
        CANTP_STANDARD_ADDRESS,
        
        /* RxPaddingActivation */
        CANTP_TRUE,
        
        /* InPduwithMetaDataSts */
        CANTP_FALSE,
        	
        /* OutPduWithMetaData */
        CANTP_FALSE
    },
    
    /* RxNSDU 2 - CanTpConfig_CanTpChannel_2_RxOnly_Pdu_DcmIPdu_FD_CAN1_Diag_Msg_TP_Func_FD_CAN1_CanTpRxNSdu_2_Pdu_DcmIPdu_FD_CAN1_Diag_Msg_TP_Func_FD_CAN1 */
    { 
        /* ChannelId */
        0x02,
        
        /* TaType */
        CANTP_FUNCTIONAL_ADDRESS,
        
        /* AddressingMode */
        CANTP_STANDARD_ADDRESS,
        
        /* RxPaddingActivation */
        CANTP_TRUE,
        
        /* InPduwithMetaDataSts */
        CANTP_FALSE,
        	
        /* OutPduWithMetaData */
        CANTP_FALSE
    }
    
}; 

#define CANTP_STOP_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
#include "MemMap.h"  

#define CANTP_START_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h"

VAR(CanTp_STminBsType, CANTP_VAR) CanTp_STminBs[] =
{
    /* RxNSduRam 0 - CanTpConfig_CanTpChannel_0_Pdu_DcmIPdu_FD_CAN1_Diag_Msg_TP_Phys_Req_FD_CAN1_CanTpRxNSdu_0_Pdu_DcmIPdu_FD_CAN1_Diag_Msg_TP_Phys_Req_FD_CAN1 */
    {
        /* BlockSize */
        0x00,
        /* STMin */
        0x05
    },
    
    /* RxNSduRam 1 - CanTpConfig_CanTpChannel_1_Pdu_ISignalIPdu_FD_CAN1_Normal_Msg_FD_TP_01_B_CanTpRxNSdu_1_Pdu_ISignalIPdu_FD_CAN1_Normal_Msg_FD_TP_01_B */
    {
        /* BlockSize */
        0x00,
        /* STMin */
        0x05
    },
    
    /* RxNSduRam 2 - CanTpConfig_CanTpChannel_2_RxOnly_Pdu_DcmIPdu_FD_CAN1_Diag_Msg_TP_Func_FD_CAN1_CanTpRxNSdu_2_Pdu_DcmIPdu_FD_CAN1_Diag_Msg_TP_Func_FD_CAN1 */
    {
        /* BlockSize */
        0x00,
        /* STMin */
        0x05
    }
    
}; 
#define CANTP_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h"


#define CANTP_START_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
#include "MemMap.h"

CONST(uint8, CANTP_CONST) CanTp_STminMapping[CANTP_TEN] =
{
    0x00,
    
    0x01,
    
    0x01,
    
    0x01,
    
    0x01,
    
    0x01,
    
    0x01,
    
    0x01,
    
    0x01,
    
    0x01
};

#define CANTP_STOP_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
#include "MemMap.h"  

#define CANTP_START_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
#include "MemMap.h"


CONST(CanTp_TxNSduDynamicType, CANTP_CONST) CanTp_TxSduDynamic[] =
{
    /* TxNSDU 0 - CanTpConfig_CanTpChannel_0_Pdu_DcmIPdu_FD_CAN1_Diag_Msg_TP_Phys_Req_FD_CAN1_CanTpTxNSdu_0_Pdu_DcmIPdu_FD_CAN1_Diag_Msg_TP_Phys_Res_FD_CAN1 */
    {
      /* UpConfirmationSduId */
        0x02,
    
      /* LoTargetPduId */
        0x07,
    
      /* NasTimeoutValue */
        0xC8,
    
      /* NbsTimeoutValue */
        0xC8,
    
      /* NcsTimeoutValue */
        0x01
    },
    /* TxNSDU 1 - CanTpConfig_CanTpChannel_1_Pdu_ISignalIPdu_FD_CAN1_Normal_Msg_FD_TP_01_B_CanTpTxNSdu_1_Pdu_ISignalIPdu_FD_CAN1_Normal_Msg_FD_TP_01_A */
    {
      /* UpConfirmationSduId */
        0x00,
    
      /* LoTargetPduId */
        0x06,
    
      /* NasTimeoutValue */
        0xC8,
    
      /* NbsTimeoutValue */
        0xC8,
    
      /* NcsTimeoutValue */
        0x01
    }
};

#define CANTP_STOP_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
#include "MemMap.h"  


#define CANTP_START_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
#include "MemMap.h"

CONST(CanTp_TxNsduStaticType, CANTP_CONST) CanTp_TxSduStatic[] =
{
    /* TxNSDU 0 - CanTpConfig_CanTpChannel_0_Pdu_DcmIPdu_FD_CAN1_Diag_Msg_TP_Phys_Req_FD_CAN1_CanTpTxNSdu_0_Pdu_DcmIPdu_FD_CAN1_Diag_Msg_TP_Phys_Res_FD_CAN1*/
    {
        /* ChannelId */
        0x00,
        
        /* TaType */
        CANTP_PHYSICAL_ADDRESS,
        
        /* AddressingMode */
        CANTP_STANDARD_ADDRESS,
        
        /* OutTxPduwithMetaDataSts */
        CANTP_FALSE,
        	
        /* InTxPduwithMetaDataSts */
        CANTP_FALSE,
        
        /* TxPaddingActivation */
        CANTP_TRUE,
        
        /* TxCancelTransmitAct */
        CANTP_TRUE,
        
        /* TxSduMaxLength */
        0x08    
    },   
    
    /* TxNSDU 1 - CanTpConfig_CanTpChannel_1_Pdu_ISignalIPdu_FD_CAN1_Normal_Msg_FD_TP_01_B_CanTpTxNSdu_1_Pdu_ISignalIPdu_FD_CAN1_Normal_Msg_FD_TP_01_A*/
    {
        /* ChannelId */
        0x01,
        
        /* TaType */
        CANTP_PHYSICAL_ADDRESS,
        
        /* AddressingMode */
        CANTP_STANDARD_ADDRESS,
        
        /* OutTxPduwithMetaDataSts */
        CANTP_FALSE,
        	
        /* InTxPduwithMetaDataSts */
        CANTP_FALSE,
        
        /* TxPaddingActivation */
        CANTP_TRUE,
        
        /* TxCancelTransmitAct */
        CANTP_TRUE,
        
        /* TxSduMaxLength */
        0x40    
    }   
    
}; 

#define CANTP_STOP_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
#include "MemMap.h"  



/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
