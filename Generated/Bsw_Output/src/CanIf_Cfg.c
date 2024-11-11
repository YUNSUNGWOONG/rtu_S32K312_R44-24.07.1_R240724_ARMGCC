
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
**  Generate On : The time-stamp is removed                                   **
**                                                                            **
**  SRC-MODULE:           CanIf_Cfg.c                                         **
**                                                                            **
**  PRODUCT   :           AUTOSAR CAN Interface Module                        **
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
**                      File Generation Information                           **
*******************************************************************************/
/*
* INPUT FILE:      Configuration\Definition\Can_43_FLEXCAN_s32k312_mqfp172.epd
*                  Configuration\Definition\ECUConfigurationParameters.arxml
*                  Configuration\Ecu\Ecud_CanIf.arxml           
*                  Configuration\Ecu\Ecud_CanNm.arxml           
*                  Configuration\Ecu\Ecud_CanSM.arxml           
*                  Configuration\Ecu\Ecud_CanTp.arxml           
*                  Configuration\Ecu\Ecud_CanTrcv.arxml         
*                  Configuration\Ecu\Ecud_EcuC.arxml            
*                  Configuration\Ecu\Ecud_EcuM.arxml            
*                  Configuration\Ecu\Ecud_Nm.arxml              
*                  Configuration\Ecu\Ecud_PduR.arxml            
*                  Configuration\Ecu\Mcal\Ecud_Can.arxml        
*                  Configuration\System\Bswmd\Bswmd_Can.arxml   
*                  Generated\Bsw_Output\bswmd\Bswmd_CanIf.arxml 
*                  Generated\Bsw_Output\bswmd\Bswmd_CanTp.arxml 
*                  Generated\Bsw_Output\bswmd\Bswmd_CanTrcv.arxml
*                  Static_Code\Modules\CanIf_R44\generator\CanIf_ECU_Configuration_PDF.arxml
*                  Static_Code\Modules\CanNm_R44\generator\CanNm_ECU_Configuration_PDF.arxml
*                  Static_Code\Modules\CanSM_R44\generator\CanSM_ECU_Configuration_PDF.arxml
*                  Static_Code\Modules\CanTp_R44\generator\CanTp_ECU_Configuration_PDF.arxml
*                  Static_Code\Modules\CanTrcv_R44\generator\CanTrcv_ECU_Configuration_PDF.arxml
*                  Static_Code\Modules\EcuM_R44\generator\EcuM_ECU_Configuration_PDF.arxml
*                  Static_Code\Modules\PduR_R44\generator\PduR_ECU_Configuration_PDF.arxml
* GENERATED ON:    11-Nov-2024 - 12:54:55                       
*/


/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "CanIf_PCTypes.h"

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/* AUTOSAR SPECIFICATION VERSION INFORMATION */
#define    CANIF_CFG_C_AR_RELEASE_MAJOR_VERSION          0x04u
#define    CANIF_CFG_C_AR_RELEASE_MINOR_VERSION          0x04u
#define    CANIF_CFG_C_AR_RELEASE_REVISION_VERSION       0x00u
#define    CANIF_CFG_C_SW_MAJOR_VERSION                  0x01u
#define    CANIF_CFG_C_SW_MINOR_VERSION                  0x01u
#define    CANIF_CFG_C_SW_PATCH_VERSION                  0x00u

/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/
#if (CANIF_PCTYPES_AR_RELEASE_MAJOR_VERSION != CANIF_CFG_C_AR_RELEASE_MAJOR_VERSION)
   #error "CanIf_Cfg.c : Mismatch in Specification Major Version"
#endif
#if (CANIF_PCTYPES_AR_RELEASE_MINOR_VERSION != CANIF_CFG_C_AR_RELEASE_MINOR_VERSION)
   #error "CanIf_Cfg.c : Mismatch in Specification Minor Version"
#endif
#if (CANIF_PCTYPES_AR_RELEASE_REVISION_VERSION != CANIF_CFG_C_AR_RELEASE_REVISION_VERSION)
   #error "CanIf_Cfg.c : Mismatch in Specification Revision Version"
#endif
#if (CANIF_PCTYPES_SW_MAJOR_VERSION != CANIF_CFG_C_SW_MAJOR_VERSION)
   #error "CanIf_Cfg.c : Mismatch in Software Major Version"
#endif
#if (CANIF_PCTYPES_SW_MINOR_VERSION != CANIF_CFG_C_SW_MINOR_VERSION)
   #error "CanIf_Cfg.c : Mismatch in Software Minor Version"
#endif


/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

/*******************************************************************************
**                      Initialization Structure                              **
*******************************************************************************/
/* Structure for CAN Driver */
/* CONST(CanIf_CanDriverType, CANIF_CONST)CanIf_CanDriver[]; */

/* Structure for Transciever */
/* CONST(CanIf_TransceiverConfigType, CANIF_CONST)CanIf_CanTrcv[]; */

/* Function pointer to CanTrcv Driver */
/* CONST(CanIf_CanTrcvDriverType, CANIF_CONST)CanIf_CanTrcvDriver[]; */

#define CANIF_START_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
#include "MemMap.h"
/* Structure for HRH Init */
CONST(CanIf_HrhInitType, CANIF_CONST)CanIf_HrhInit[] =
{
    /* HRH_INIT 0 - CanGeneral_CanIfCtrlDrvCfg0 */
    {
        /* usMaxHrhId */
        0x0005
    }
};

#define CANIF_STOP_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
#include "MemMap.h"

/*  Structure for Rx callback user  */
/* CONST(CanIf_RxCbkUserType, CANIF_CONST)CanIf_RxCbkUser[]; */

#define CANIF_START_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
#include "MemMap.h"
/* Structure for Rx L-PDU(Range Or List) */
CONST(CanIf_RxLpduType, CANIF_VAR) CanIf_RxLpdu[] =
{
    /* RX-LIST-RANGE 0 - CanIfRxPduCfg_IN_ECU1_FD_CAN1_0x18c_FD_CAN1_BSD_01_50ms_P11 */
    {
        /* rxPduCanId */
        0x0000018CuL,

        /* rxLowerCanId */
        0x00000000uL,

        /* rxUpperCanId */
        0xFFFFFFFFuL,

        /* ddRxPduId */
        0x0000,

        /* ddTargetId */
        0x0008,

        /* ulCanIfRxPduCanIdMask */
        0x000007DFuL,

        /* ucMetaDataLength */
        0x00,

        /* ucMetaDataItemType */
        CANIF_INVALID_METADATA_TYPE,

        /* DataLengthCheck */
        0x01,

        /* Dlc */
        0x08,

        /* ucCallbackIndex */
        0xFF,

        /* ucRxUserOrNotifSts */
        0x00,

        /* ucControllerId */
        0x00,

        /* ucRxPduCanIdType */
        0x04
    },
    /* RX-LIST-RANGE 1 - CanIfRxPduCfg_IN_ECU1_FD_CAN1_0x205_FD_CAN1_V_CGW_02_A */
    {
        /* rxPduCanId */
        0x00000205uL,

        /* rxLowerCanId */
        0x00000000uL,

        /* rxUpperCanId */
        0xFFFFFFFFuL,

        /* ddRxPduId */
        0x0001,

        /* ddTargetId */
        0x0013,

        /* ulCanIfRxPduCanIdMask */
        0x000007DFuL,

        /* ucMetaDataLength */
        0x00,

        /* ucMetaDataItemType */
        CANIF_INVALID_METADATA_TYPE,

        /* DataLengthCheck */
        0x01,

        /* Dlc */
        0x08,

        /* ucCallbackIndex */
        0xFF,

        /* ucRxUserOrNotifSts */
        0x00,

        /* ucControllerId */
        0x00,

        /* ucRxPduCanIdType */
        0x04
    },
    /* RX-LIST-RANGE 2 - CanIfRxPduCfg_IN_ECU1_FD_CAN1_CANNM_MESSAGE */
    {
        /* rxPduCanId */
        0x00000508uL,

        /* rxLowerCanId */
        0x00000500uL,

        /* rxUpperCanId */
        0x0000057FuL,

        /* ddRxPduId */
        0x0002,

        /* ddTargetId */
        0x0000,

        /* ulCanIfRxPduCanIdMask */
        0x000007DFuL,

        /* ucMetaDataLength */
        0x00,

        /* ucMetaDataItemType */
        CANIF_INVALID_METADATA_TYPE,

        /* DataLengthCheck */
        0x01,

        /* Dlc */
        0x08,

        /* ucCallbackIndex */
        0xFF,

        /* ucRxUserOrNotifSts */
        0x02,

        /* ucControllerId */
        0x00,

        /* ucRxPduCanIdType */
        0x04
    },
    /* RX-LIST-RANGE 3 - CanIfRxPduCfg_IN_ECU1_FD_CAN1_0x650_FD_CAN1_AtmReq */
    {
        /* rxPduCanId */
        0x00000650uL,

        /* rxLowerCanId */
        0x00000000uL,

        /* rxUpperCanId */
        0xFFFFFFFFuL,

        /* ddRxPduId */
        0x0003,

        /* ddTargetId */
        0x000A,

        /* ulCanIfRxPduCanIdMask */
        0x000007DFuL,

        /* ucMetaDataLength */
        0x00,

        /* ucMetaDataItemType */
        CANIF_INVALID_METADATA_TYPE,

        /* DataLengthCheck */
        0x01,

        /* Dlc */
        0x08,

        /* ucCallbackIndex */
        0xFF,

        /* ucRxUserOrNotifSts */
        0x00,

        /* ucControllerId */
        0x00,

        /* ucRxPduCanIdType */
        0x04
    },
    /* RX-LIST-RANGE 4 - CanIfRxPduCfg_IN_ECU1_FD_CAN1_0x75e_FD_CAN1_Normal_Msg_FD_TP_01_B */
    {
        /* rxPduCanId */
        0x0000075EuL,

        /* rxLowerCanId */
        0x00000000uL,

        /* rxUpperCanId */
        0xFFFFFFFFuL,

        /* ddRxPduId */
        0x0004,

        /* ddTargetId */
        0x0001,

        /* ulCanIfRxPduCanIdMask */
        0x000007DFuL,

        /* ucMetaDataLength */
        0x00,

        /* ucMetaDataItemType */
        CANIF_INVALID_METADATA_TYPE,

        /* DataLengthCheck */
        0x00,

        /* Dlc */
        0x00,

        /* ucCallbackIndex */
        0xFF,

        /* ucRxUserOrNotifSts */
        0x01,

        /* ucControllerId */
        0x00,

        /* ucRxPduCanIdType */
        0x04
    },
    /* RX-LIST-RANGE 5 - CanIfRxPduCfg_IN_ECU1_FD_CAN1_0x768_FD_CAN1_Diag_Msg_TP_Phys_Req_FD_CAN1 */
    {
        /* rxPduCanId */
        0x00000768uL,

        /* rxLowerCanId */
        0x00000000uL,

        /* rxUpperCanId */
        0xFFFFFFFFuL,

        /* ddRxPduId */
        0x0005,

        /* ddTargetId */
        0x0000,

        /* ulCanIfRxPduCanIdMask */
        0x000007DFuL,

        /* ucMetaDataLength */
        0x00,

        /* ucMetaDataItemType */
        CANIF_INVALID_METADATA_TYPE,

        /* DataLengthCheck */
        0x00,

        /* Dlc */
        0x00,

        /* ucCallbackIndex */
        0xFF,

        /* ucRxUserOrNotifSts */
        0x01,

        /* ucControllerId */
        0x00,

        /* ucRxPduCanIdType */
        0x04
    },
    /* RX-LIST-RANGE 6 - CanIfRxPduCfg_IN_ECU1_FD_CAN1_0x7df_FD_CAN1_Diag_Msg_TP_Func_FD_CAN1 */
    {
        /* rxPduCanId */
        0x000007DFuL,

        /* rxLowerCanId */
        0x00000000uL,

        /* rxUpperCanId */
        0xFFFFFFFFuL,

        /* ddRxPduId */
        0x0006,

        /* ddTargetId */
        0x0002,

        /* ulCanIfRxPduCanIdMask */
        0x000007DFuL,

        /* ucMetaDataLength */
        0x00,

        /* ucMetaDataItemType */
        CANIF_INVALID_METADATA_TYPE,

        /* DataLengthCheck */
        0x00,

        /* Dlc */
        0x00,

        /* ucCallbackIndex */
        0xFF,

        /* ucRxUserOrNotifSts */
        0x01,

        /* ucControllerId */
        0x00,

        /* ucRxPduCanIdType */
        0x04
    }
};

#define CANIF_STOP_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
#include "MemMap.h"

#define CANIF_START_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
#include "MemMap.h"
/* Structure for HRH */
CONST(CanIf_HrhType, CANIF_CONST) CanIf_Hrh[] =
{
    /* HRH 0 - CanIfHrhCfg_IN_0x500_0x57f_ECU1_FD_CAN1_NM_Message */
    {
        /* ddRxLpduIndex */
        0x0002,

        /* hrhsoftwarefilter */
        CANIF_TRUE,

        /* NoOfHrhRange */
        0x01,

        /* hrhcanidlower */
        0x00000500uL,

        /* hrhcanidupper */
        0x0000057FuL,

        /* hrhRangeMask */
        0x00000000uL,

        /* hrhRangeBaseId */
        0x00000000uL,

        /* ddNoOfRxLpdusList */
        0x01,

        /* ucFilterMethod */
        0x00
    },
    /* HRH 1 - CanIfHrhCfg_IN_ECU1_FD_CAN1_0x7df_FD_CAN1_Diag_Msg_TP_Func_FD_CAN1 */
    {
        /* ddRxLpduIndex */
        0x0006,

        /* hrhsoftwarefilter */
        CANIF_TRUE,

        /* NoOfHrhRange */
        0x00,

        /* hrhcanidlower */
        0x00000000uL,

        /* hrhcanidupper */
        0x00000000uL,

        /* hrhRangeMask */
        0x00000000uL,

        /* hrhRangeBaseId */
        0x00000000uL,

        /* ddNoOfRxLpdusList */
        0x01,

        /* ucFilterMethod */
        0x03
    },
    /* HRH 2 - CanIfHrhCfg_IN_ECU1_FD_CAN1_0x650_FD_CAN1_AtmReq */
    {
        /* ddRxLpduIndex */
        0x0003,

        /* hrhsoftwarefilter */
        CANIF_TRUE,

        /* NoOfHrhRange */
        0x00,

        /* hrhcanidlower */
        0x00000000uL,

        /* hrhcanidupper */
        0x00000000uL,

        /* hrhRangeMask */
        0x00000000uL,

        /* hrhRangeBaseId */
        0x00000000uL,

        /* ddNoOfRxLpdusList */
        0x01,

        /* ucFilterMethod */
        0x03
    },
    /* HRH 3 - CanIfHrhCfg_IN_ECU1_FD_CAN1_0x18c_FD_CAN1_BSD_01_50ms_P11 */
    {
        /* ddRxLpduIndex */
        0x0000,

        /* hrhsoftwarefilter */
        CANIF_TRUE,

        /* NoOfHrhRange */
        0x00,

        /* hrhcanidlower */
        0x00000000uL,

        /* hrhcanidupper */
        0x00000000uL,

        /* hrhRangeMask */
        0x00000000uL,

        /* hrhRangeBaseId */
        0x00000000uL,

        /* ddNoOfRxLpdusList */
        0x01,

        /* ucFilterMethod */
        0x03
    },
    /* HRH 4 - CanIfHrhCfg_IN_ECU1_FD_CAN1_0x205_FD_CAN1_V_CGW_02_A */
    {
        /* ddRxLpduIndex */
        0x0001,

        /* hrhsoftwarefilter */
        CANIF_TRUE,

        /* NoOfHrhRange */
        0x00,

        /* hrhcanidlower */
        0x00000000uL,

        /* hrhcanidupper */
        0x00000000uL,

        /* hrhRangeMask */
        0x00000000uL,

        /* hrhRangeBaseId */
        0x00000000uL,

        /* ddNoOfRxLpdusList */
        0x01,

        /* ucFilterMethod */
        0x03
    },
    /* HRH 5 - CanIfHrhCfg_IN_0x748_0x77e_ECU1_FD_CAN1 */
    {
        /* ddRxLpduIndex */
        0x0004,

        /* hrhsoftwarefilter */
        CANIF_TRUE,

        /* NoOfHrhRange */
        0x00,

        /* hrhcanidlower */
        0x00000000uL,

        /* hrhcanidupper */
        0x00000000uL,

        /* hrhRangeMask */
        0x00000000uL,

        /* hrhRangeBaseId */
        0x00000000uL,

        /* ddNoOfRxLpdusList */
        0x02,

        /* ucFilterMethod */
        0x00
    }
};

#define CANIF_STOP_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
#include "MemMap.h"

#define CANIF_START_SEC_CONFIG_DATA_PREBUILD_16
#include "MemMap.h"
/* Structure for HRH Map array */
CONST(uint16, CANIF_CONST) CanIf_HrhMapArray[] =
{
    0x0004,

    0x0003,

    0x0001,

    0x0002,

    0x0000,

    0x0005
};
                    
#define CANIF_STOP_SEC_CONFIG_DATA_PREBUILD_16
#include "MemMap.h"

#define CANIF_START_SEC_CONFIG_DATA_PREBUILD_16
#include "MemMap.h"
/* Structure for Basic TxPdu Index Map array */
CONST(uint16, CANIF_CONST) CanIf_TxBasicPduIndexMapping[] =
{
    CANIF_INVALID,

    CANIF_INVALID,

    CANIF_INVALID,

    CANIF_INVALID,

    CANIF_INVALID,

    CANIF_INVALID,

    CANIF_INVALID,

    CANIF_INVALID
};
                    
#define CANIF_STOP_SEC_CONFIG_DATA_PREBUILD_16
#include "MemMap.h"

/* Structure for Tx Buffer */
/* CONST(CanIf_TxBufferType, CANIF_CONST) CanIf_TxBuffer[]; */

/* Structure for Tx callback user */
/* CONST(CanIf_TxCbkUserType, CANIF_CONST)CanIf_TxCbkUser[]; */

#define CANIF_START_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
#include "MemMap.h"
/* Structure for Transmit L-PDU */
CONST(CanIf_TxLpduType, CANIF_CONST)CanIf_TxLpdu[] =
{
    /* TX LPDU 0 - CanIfTxPduCfg_OUT_ECU1_FD_CAN1_0x42_FD_CAN1_TCU_01_10ms_P11 */
    {
        /* ddCanId */
        0x40000042UL,

        /* ddHthIdorBufferId */
        0x0D,

        /* ddTxConfirmPduId */
        0x0001,

        /* ddTxPduId */
        0x0000,

        /* ucCallbackIndex */
        0xFF,

        /* ucTxCbkUser */
        0x00,

        /* ucHTHTypeOrTXPN */
        0x01,

        /* ucCanIdType */
        0x01,

        /* TriggerTransmit */
        0x00,

        /* Truncation */
        0x01,

        /* ddCanIdMask */
        0x000007DFuL,

        /* ucMetaDataLength */
        0x00
    },
    /* TX LPDU 1 - CanIfTxPduCfg_OUT_ECU1_FD_CAN1_0x202_FD_CAN1_V_CGW_01_B */
    {
        /* ddCanId */
        0x40000202UL,

        /* ddHthIdorBufferId */
        0x0C,

        /* ddTxConfirmPduId */
        0x0007,

        /* ddTxPduId */
        0x0001,

        /* ucCallbackIndex */
        0xFF,

        /* ucTxCbkUser */
        0x00,

        /* ucHTHTypeOrTXPN */
        0x01,

        /* ucCanIdType */
        0x01,

        /* TriggerTransmit */
        0x00,

        /* Truncation */
        0x01,

        /* ddCanIdMask */
        0x000007DFuL,

        /* ucMetaDataLength */
        0x00
    },
    /* TX LPDU 2 - CanIfTxPduCfg_OUT_ECU1_FD_CAN1_0x2b0_FD_CAN1_AFLS_01_100ms */
    {
        /* ddCanId */
        0x400002B0UL,

        /* ddHthIdorBufferId */
        0x0B,

        /* ddTxConfirmPduId */
        0x0002,

        /* ddTxPduId */
        0x0002,

        /* ucCallbackIndex */
        0xFF,

        /* ucTxCbkUser */
        0x00,

        /* ucHTHTypeOrTXPN */
        0x01,

        /* ucCanIdType */
        0x01,

        /* TriggerTransmit */
        0x00,

        /* Truncation */
        0x01,

        /* ddCanIdMask */
        0x000007DFuL,

        /* ucMetaDataLength */
        0x00
    },
    /* TX LPDU 3 - CanIfTxPduCfg_OUT_ECU1_FD_CAN1_0x400_FD_CAN1_AHLS_01_300ms */
    {
        /* ddCanId */
        0x40000400UL,

        /* ddHthIdorBufferId */
        0x0A,

        /* ddTxConfirmPduId */
        0x0003,

        /* ddTxPduId */
        0x0003,

        /* ucCallbackIndex */
        0xFF,

        /* ucTxCbkUser */
        0x00,

        /* ucHTHTypeOrTXPN */
        0x01,

        /* ucCanIdType */
        0x01,

        /* TriggerTransmit */
        0x00,

        /* Truncation */
        0x01,

        /* ddCanIdMask */
        0x000007DFuL,

        /* ucMetaDataLength */
        0x00
    },
    /* TX LPDU 4 - CanIfTxPduCfg_OUT_ECU1_FD_CAN1_0x502_FD_CAN1_NM_CGW */
    {
        /* ddCanId */
        0x40000502UL,

        /* ddHthIdorBufferId */
        0x09,

        /* ddTxConfirmPduId */
        0x0000,

        /* ddTxPduId */
        0x0004,

        /* ucCallbackIndex */
        0xFF,

        /* ucTxCbkUser */
        0x02,

        /* ucHTHTypeOrTXPN */
        0x01,

        /* ucCanIdType */
        0x01,

        /* TriggerTransmit */
        0x00,

        /* Truncation */
        0x01,

        /* ddCanIdMask */
        0x000007DFuL,

        /* ucMetaDataLength */
        0x00
    },
    /* TX LPDU 5 - CanIfTxPduCfg_OUT_ECU1_FD_CAN1_0x651_FD_CAN1_AtmResp */
    {
        /* ddCanId */
        0x40000651UL,

        /* ddHthIdorBufferId */
        0x08,

        /* ddTxConfirmPduId */
        0x0005,

        /* ddTxPduId */
        0x0005,

        /* ucCallbackIndex */
        0xFF,

        /* ucTxCbkUser */
        0x00,

        /* ucHTHTypeOrTXPN */
        0x01,

        /* ucCanIdType */
        0x01,

        /* TriggerTransmit */
        0x00,

        /* Truncation */
        0x01,

        /* ddCanIdMask */
        0x000007DFuL,

        /* ucMetaDataLength */
        0x00
    },
    /* TX LPDU 6 - CanIfTxPduCfg_OUT_ECU1_FD_CAN1_0x75a_FD_CAN1_Normal_Msg_FD_TP_01_A */
    {
        /* ddCanId */
        0x4000075AUL,

        /* ddHthIdorBufferId */
        0x07,

        /* ddTxConfirmPduId */
        0x0001,

        /* ddTxPduId */
        0x0006,

        /* ucCallbackIndex */
        0xFF,

        /* ucTxCbkUser */
        0x01,

        /* ucHTHTypeOrTXPN */
        0x01,

        /* ucCanIdType */
        0x01,

        /* TriggerTransmit */
        0x00,

        /* Truncation */
        0x01,

        /* ddCanIdMask */
        0x000007DFuL,

        /* ucMetaDataLength */
        0x00
    },
    /* TX LPDU 7 - CanIfTxPduCfg_OUT_ECU1_FD_CAN1_0x760_FD_CAN1_Diag_Msg_TP_Phys_Res_FD_CAN1 */
    {
        /* ddCanId */
        0x40000760UL,

        /* ddHthIdorBufferId */
        0x06,

        /* ddTxConfirmPduId */
        0x0000,

        /* ddTxPduId */
        0x0007,

        /* ucCallbackIndex */
        0xFF,

        /* ucTxCbkUser */
        0x01,

        /* ucHTHTypeOrTXPN */
        0x01,

        /* ucCanIdType */
        0x01,

        /* TriggerTransmit */
        0x00,

        /* Truncation */
        0x01,

        /* ddCanIdMask */
        0x000007DFuL,

        /* ucMetaDataLength */
        0x00
    }
};

#define CANIF_STOP_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
#include "MemMap.h"

#define CANIF_START_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
#include "MemMap.h"
/* Structure for Controller */
CONST(CanIf_ControllerConfigType, CANIF_CONST)CanIf_ControllerConfig[] =
{
    /* CONTROLLER 0 - CanIf_0 */
    {
        /* *pTxLpdu */
        &CanIf_TxLpdu[0],

        /* ddNoOfTxPdu */
        0x08,

        /* blPartialNWEnabled */
        CANIF_FALSE
    }
};

#define CANIF_STOP_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
#include "MemMap.h"

/* Structure for TxPduInfoPtr */
/* VAR(PduInfoType, CANIF_VAR)CanIf_TxPduInfoPtr[]; */

/* Structure for Tx Pdu To Queue Mapping */
/* VAR(CanIf_TxPduIdType, CANIF_VAR) CanIf_TxPduToQueueMapping[]; */

/* Structure for wakeup source information */
/* CONST(CanIf_WakeupSourceInfoType, CANIF_CONST)CanIf_WakeupSource[CANIF_NO_OF_WAKEUP_SOURCES]; */


/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
