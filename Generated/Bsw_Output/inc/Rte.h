/*******************************************************************************
**                           HYUNDAI AUTOEVER Corp.                           **
********************************************************************************
** (C) 2021 HYUNDAI AUTOEVER Corp.                                            **
** Confidential Proprietary Information. Distribution Limited.                **
** This source code is permitted to be used only in projects contracted       **
** with Hyundai Autoever, and any other use is prohibited.                    **
** If you use it for other purposes or change the source code,                **
** you may take legal responsibility.                                         **
** In this case, There is no warranty and technical support.                  **
********************************************************************************
**  Module Name : RTE                                                         **
**                                                                            **
**  File Name : Rte.h                                                         **
**                                                                            **
**  Generated On : Mon Nov 11 2024 13:32:30 KST                               **
**                                                                            **
**  Generated from :                                                          **
**  Configuration\Definition\Os_ECU_Configuration_PDF_S32K312.arxml           **
**  Configuration\Ecu\ECUCD_EcucValueCollection.arxml                         **
**  Configuration\Ecu\Ecud_BswM.arxml                                         **
**  Configuration\Ecu\Ecud_CanCM.arxml                                        **
**  Configuration\Ecu\Ecud_CanIf.arxml                                        **
**  Configuration\Ecu\Ecud_CanNm.arxml                                        **
**  Configuration\Ecu\Ecud_CanSM.arxml                                        **
**  Configuration\Ecu\Ecud_CanTp.arxml                                        **
**  Configuration\Ecu\Ecud_CanTrcv.arxml                                      **
**  Configuration\Ecu\Ecud_Com.arxml                                          **
**  Configuration\Ecu\Ecud_ComM.arxml                                         **
**  Configuration\Ecu\Ecud_ComXf.arxml                                        **
**  Configuration\Ecu\Ecud_Crc.arxml                                          **
**  Configuration\Ecu\Ecud_CryIf.arxml                                        **
**  Configuration\Ecu\Ecud_Crypto_76_HaeModule.arxml                          **
**  Configuration\Ecu\Ecud_Csm.arxml                                          **
**  Configuration\Ecu\Ecud_Dcm.arxml                                          **
**  Configuration\Ecu\Ecud_Dem.arxml                                          **
**  Configuration\Ecu\Ecud_Det.arxml                                          **
**  Configuration\Ecu\Ecud_E2EXf.arxml                                        **
**  Configuration\Ecu\Ecud_EcuC.arxml                                         **
**  Configuration\Ecu\Ecud_EcuM.arxml                                         **
**  Configuration\Ecu\Ecud_FiM.arxml                                          **
**  Configuration\Ecu\Ecud_Fota.arxml                                         **
**  Configuration\Ecu\Ecud_IoHwAb.arxml                                       **
**  Configuration\Ecu\Ecud_LinIf.arxml                                        **
**  Configuration\Ecu\Ecud_LinSM.arxml                                        **
**  Configuration\Ecu\Ecud_LinTrcv.arxml                                      **
**  Configuration\Ecu\Ecud_MemIf.arxml                                        **
**  Configuration\Ecu\Ecud_Nm.arxml                                           **
**  Configuration\Ecu\Ecud_NvM.arxml                                          **
**  Configuration\Ecu\Ecud_Os.arxml                                           **
**  Configuration\Ecu\Ecud_PduR.arxml                                         **
**  Configuration\Ecu\Ecud_Rte.arxml                                          **
**  Configuration\Ecu\Ecud_StbM.arxml                                         **
**  Configuration\Ecu\Ecud_Tm.arxml                                           **
**  Configuration\Ecu\Ecud_WdgIf.arxml                                        **
**  Configuration\Ecu\Ecud_WdgM.arxml                                         **
**  Configuration\Ecu\Ecud_Wdg_76_Acw.arxml                                   **
**  Configuration\Ecu\Mcal\Ecud_Adc.arxml                                     **
**  Configuration\Ecu\Mcal\Ecud_Wdg.arxml                                     **
**  Configuration\System\Bswmd\Bswmd_Adc.arxml                                **
**  Configuration\System\Bswmd\Bswmd_BswM.arxml                               **
**  Configuration\System\Bswmd\Bswmd_Can.arxml                                **
**  Configuration\System\Bswmd\Bswmd_ComXf.arxml                              **
**  Configuration\System\Bswmd\Bswmd_Crypto.arxml                             **
**  Configuration\System\Bswmd\Bswmd_Dio.arxml                                **
**  Configuration\System\Bswmd\Bswmd_E2EXf.arxml                              **
**  Configuration\System\Bswmd\Bswmd_Fee.arxml                                **
**  Configuration\System\Bswmd\Bswmd_Fls.arxml                                **
**  Configuration\System\Bswmd\Bswmd_Gpt.arxml                                **
**  Configuration\System\Bswmd\Bswmd_Icu.arxml                                **
**  Configuration\System\Bswmd\Bswmd_Lin.arxml                                **
**  Configuration\System\Bswmd\Bswmd_Mcl.arxml                                **
**  Configuration\System\Bswmd\Bswmd_Mcu.arxml                                **
**  Configuration\System\Bswmd\Bswmd_Port.arxml                               **
**  Configuration\System\Bswmd\Bswmd_Pwm.arxml                                **
**  Configuration\System\Bswmd\Bswmd_Spi.arxml                                **
**  Configuration\System\Bswmd\Bswmd_Wdg.arxml                                **
**  Configuration\System\Composition\EcuExtract.arxml                         **
**  Configuration\System\DBImport\DataTypes\AUTOSAR_DataTypes.arxml           **
**  Configuration\System\DBImport\DataTypes\CanStack_DataTypes.arxml          **
**  Configuration\System\DBImport\DataTypes\ComStack_DataTypes.arxml          **
**  Configuration\System\DBImport\FD_CAN1.arxml                               **
**  Configuration\System\DBImport\LIN1.arxml                                  **
**  Configuration\System\DBImport\LIN2.arxml                                  **
**  Configuration\System\Swcd_App\App_Dcm.arxml                               **
**  Configuration\System\Swcd_App\App_Dem.arxml                               **
**  Configuration\System\Swcd_App\App_E2EXf.arxml                             **
**  Configuration\System\Swcd_App\App_Lin.arxml                               **
**  Configuration\System\Swcd_App\App_Mode.arxml                              **
**  Configuration\System\Swcd_App\App_WdgM.arxml                              **
**  Configuration\System\Swcd_Bsw\MODE_PortInterfaces.arxml                   **
**  Configuration\System\Swcd_Bsw\Swcd_Bsw_BswM.arxml                         **
**  Configuration\System\Swcd_Bsw\Swcd_Lin.arxml                              **
**  Configuration\System\Transformer\Transformer.arxml                        **
**  Generated\Bsw_Output\bswmd\Bswmd_CanCM.arxml                              **
**  Generated\Bsw_Output\bswmd\Bswmd_CanIf.arxml                              **
**  Generated\Bsw_Output\bswmd\Bswmd_CanNm.arxml                              **
**  Generated\Bsw_Output\bswmd\Bswmd_CanSM.arxml                              **
**  Generated\Bsw_Output\bswmd\Bswmd_CanTp.arxml                              **
**  Generated\Bsw_Output\bswmd\Bswmd_CanTrcv.arxml                            **
**  Generated\Bsw_Output\bswmd\Bswmd_Com.arxml                                **
**  Generated\Bsw_Output\bswmd\Bswmd_ComM.arxml                               **
**  Generated\Bsw_Output\bswmd\Bswmd_Crc.arxml                                **
**  Generated\Bsw_Output\bswmd\Bswmd_CryIf.arxml                              **
**  Generated\Bsw_Output\bswmd\Bswmd_Crypto_76_HaeModule.arxml                **
**  Generated\Bsw_Output\bswmd\Bswmd_Csm.arxml                                **
**  Generated\Bsw_Output\bswmd\Bswmd_Dcm.arxml                                **
**  Generated\Bsw_Output\bswmd\Bswmd_Dem.arxml                                **
**  Generated\Bsw_Output\bswmd\Bswmd_Det.arxml                                **
**  Generated\Bsw_Output\bswmd\Bswmd_EcuM.arxml                               **
**  Generated\Bsw_Output\bswmd\Bswmd_FiM.arxml                                **
**  Generated\Bsw_Output\bswmd\Bswmd_Fota.arxml                               **
**  Generated\Bsw_Output\bswmd\Bswmd_IoHwAb.arxml                             **
**  Generated\Bsw_Output\bswmd\Bswmd_IpduM.arxml                              **
**  Generated\Bsw_Output\bswmd\Bswmd_KeyM.arxml                               **
**  Generated\Bsw_Output\bswmd\Bswmd_LinIf.arxml                              **
**  Generated\Bsw_Output\bswmd\Bswmd_LinSM.arxml                              **
**  Generated\Bsw_Output\bswmd\Bswmd_LinTrcv.arxml                            **
**  Generated\Bsw_Output\bswmd\Bswmd_MemIf.arxml                              **
**  Generated\Bsw_Output\bswmd\Bswmd_Mem_76_Pfls.arxml                        **
**  Generated\Bsw_Output\bswmd\Bswmd_Nm.arxml                                 **
**  Generated\Bsw_Output\bswmd\Bswmd_NvM.arxml                                **
**  Generated\Bsw_Output\bswmd\Bswmd_Os.arxml                                 **
**  Generated\Bsw_Output\bswmd\Bswmd_PduR.arxml                               **
**  Generated\Bsw_Output\bswmd\Bswmd_StbM.arxml                               **
**  Generated\Bsw_Output\bswmd\Bswmd_Tm.arxml                                 **
**  Generated\Bsw_Output\bswmd\Bswmd_WdgIf.arxml                              **
**  Generated\Bsw_Output\bswmd\Bswmd_WdgM.arxml                               **
**  Generated\Bsw_Output\bswmd\Bswmd_Wdg_76_Acw.arxml                         **
**  Generated\Bsw_Output\swcd\Swcd_Bsw_ComM.arxml                             **
**  Generated\Bsw_Output\swcd\Swcd_Bsw_Csm.arxml                              **
**  Generated\Bsw_Output\swcd\Swcd_Bsw_Dcm.arxml                              **
**  Generated\Bsw_Output\swcd\Swcd_Bsw_Dem.arxml                              **
**  Generated\Bsw_Output\swcd\Swcd_Bsw_Det.arxml                              **
**  Generated\Bsw_Output\swcd\Swcd_Bsw_EcuM.arxml                             **
**  Generated\Bsw_Output\swcd\Swcd_Bsw_FiM.arxml                              **
**  Generated\Bsw_Output\swcd\Swcd_Bsw_IoHwAb.arxml                           **
**  Generated\Bsw_Output\swcd\Swcd_Bsw_KeyM.arxml                             **
**  Generated\Bsw_Output\swcd\Swcd_Bsw_NvM.arxml                              **
**  Generated\Bsw_Output\swcd\Swcd_Bsw_Os.arxml                               **
**  Generated\Bsw_Output\swcd\Swcd_Bsw_StbM.arxml                             **
**  Generated\Bsw_Output\swcd\Swcd_Bsw_WdgM.arxml                             **
**  Generated\Bsw_Output\swcd\Swcd_Fota.arxml                                 **
**  Static_Code\Modules\EcuM_R44\generator\EcuM_PortInterface.arxml           **
**  Static_Code\Modules\Rte_R44\generator\SafeRTE_PDF.arxml                   **
**                                                                            **
**  Generator version : 1.8.0.0                                               **
**                                                                            **
**  NOTE: This is a generated file, Please DO NOT EDIT manually!              **
**                                                                           **/
/******************************************************************************/
/*                 Multiple Header Inclusion Protection Start                 */
/******************************************************************************/
#ifndef RTE_H
#define RTE_H

/******************************************************************************/
/*                              Header Inclusion                              */
/******************************************************************************/
#include "Compiler.h"
#include "Platform_Types.h"
#include "Std_Types.h"
#include "Rte_Cfg.h"

/******************************************************************************/
/*                                ERROR CODES                                 */
/******************************************************************************/
#define Rte_IsInfrastructureError(status)                                     (((status) & 128U) != 0U)
#define Rte_HasOverlayedError(status)                                         (((status) & 64U) != 0U)
#define Rte_ApplicationError(status)                                          ((status) & 63U)

/******************************************************************************/
/*                                Error values                                */
/******************************************************************************/
#define RTE_INSTANCE_ID                                                       0U
#define RTE_TRUE                                                              1U
#define RTE_FALSE                                                             0U
#define RTE_PARTITION_RUNNING                                                 2U
#define RTE_PARTITION_STOPPED                                                 0U
#define RTE_MODULE_PARTITION_RUNNING                                          3U
#define INVALID_RUNNABLE                                                      205U
#define INVALID_ENTITY                                                        205U
/******************************************************************************/
/*                     Standard Application Error Values                      */
/******************************************************************************/
#define RTE_E_INVALID                                                         1U
#define RTE_E_COM_STOPPED                                                     128U
#define RTE_E_COM_BUSY                                                        141U
#define RTE_E_TIMEOUT                                                         129U
#define RTE_E_LIMIT                                                           130U
#define RTE_E_NO_DATA                                                         131U
#define RTE_E_TRANSMIT_ACK                                                    132U
#define RTE_E_NEVER_RECEIVED                                                  133U
#define RTE_E_UNCONNECTED                                                     134U
#define RTE_E_IN_EXCLUSIVE_AREA                                               135U
#define RTE_E_SEG_FAULT                                                       136U
#define RTE_E_OUT_OF_RANGE                                                    137U
#define RTE_E_SERIALIZATION_ERROR                                             138U
#define RTE_E_HARD_TRANSFORMER_ERROR                                          138U
#define RTE_E_XFRM_FAILURE                                                    138U
#define RTE_E_SERIALIZATION_LIMIT                                             139U
#define RTE_E_TRANSFORMER_LIMIT                                               139U
#define RTE_E_SOFT_TRANSFORMER_ERROR                                          140U
#define RTE_E_FILTER_ERROR                                                    0x4000
#define RTE_E_LOST_DATA                                                       64U
#define RTE_E_MAX_AGE_EXCEEDED                                                64U
#define RTE_E_INVALID_ARGS                                                    201U
#define RTE_E_OK                                                              0U
#define RTE_E_ILLEGAL_INVOCATION                                              203U
#define RTE_E_UNINIT                                                          204U
#define SCHM_E_OK                                                             0U
#define SCHM_E_NOT_OK                                                         202U
#define SCHM_E_TIMEOUT                                                        129U
#define SCHM_E_LIMIT                                                          130U
#define SCHM_E_NO_DATA                                                        131U
#define SCHM_E_TRANSMIT_ACK                                                   132U
#define SCHM_E_IN_EXCLUSIVE_AREA                                              135U
#define SCHM_E_INVALID                                                        1U
#define SCHM_E_UNINIT                                                         204U
#define SCHM_E_SEG_FAULT                                                      136U
#define SCHM_E_ILLEGAL_INVOCATION                                             203U
#define SCHM_E_INVALID_ARGS                                                   201U
#define SCHM_E_UNCONNECTED                                                    134U
#define SCHM_E_LOST_DATA                                                      64U

/******************************************************************************/
/*                            OS API return Macro                             */
/******************************************************************************/
#define RTE_E_OS_ERROR                                                        (200U)
#define SCHM_E_OS_ERROR                                                       (200U)

/******************************************************************************/
/*                          Transformer Return Codes                          */
/******************************************************************************/
#define RTE_TRANSFORMER_UNSPECIFIED                                           (0x00U)
#define RTE_TRANSFORMER_SERIALIZER                                            (0x01U)
#define RTE_TRANSFORMER_SAFETY                                                (0x02U)
#define RTE_TRANSFORMER_SECURITY                                              (0x03U)
#define RTE_TRANSFORMER_CUSTOM                                                (0xffU)

/******************************************************************************/
/*                           SchM APIs Service IDs                            */
/******************************************************************************/
#define SCHM_START_SERVICEID                                                  0x70U
#define SCHM_STARTTIMING_SERVICEID                                            0x76U
#define SCHM_INIT_SERVICEID                                                   0x00U
#define SCHM_DEINIT_SERVICEID                                                 0x01U
#define SCHM_GETVERSIONINFO_SERVICEID                                         0x02U
#define SCHM_ENTER_SERVICEID                                                  0x03U
#define SCHM_EXIT_SERVICEID                                                   0x04U
#define SCHM_ACTMAINFUNCTION_SERVICEID                                        0x05U
#define SCHM_SWITCH_SERVICEID                                                 0x06U
#define SCHM_MODE_SERVICEID                                                   0x07U
#define SCHM_SWITCHACK_SERVICEID                                              0x08U
#define SCHM_TRIGGER_SERVICEID                                                0x09U
#define SCHM_SEND_SERVICEID                                                   0x0AU
#define SCHM_RECEIVE_SERVICEID                                                0x0BU
#define SCHM_CALL_SERVICEID                                                   0x0CU
#define SCHM_RESULT_SERVICEID                                                 0x0DU

/******************************************************************************/
/*                            RTE APIs Service IDs                            */
/******************************************************************************/
#define RTE_CDATA_SERVICEID                                                   0x1FU
#define RTE_PRM_SERVICEID                                                     0x20U
#define RTE_START_SERVICEID                                                   0x70U
#define RTE_STOP_SERVICEID                                                    0x71U
#define RTE_FEEDBACK_SERVICEID                                                0x17U
#define RTE_INVALIDATE_SERVICEID                                              0x16U
#define RTE_WRITE_SERVICEID                                                   0x14U
#define RTE_READ_SERVICEID                                                    0x19U
#define RTE_PARTITIONTERMINATED_SERVICEID                                     0x72U
#define RTE_PARTITIONRESTARTING_SERVICEID                                     0x73U
#define RTE_RESTARTPARTITION_SERVICEID                                        0x74U

#define RTE_SEND_SERVICEID                                                    0x13U
#define RTE_PORT_SERVICEID                                                    0x12U
#define RTE_RECEIVE_SERVICEID                                                 0x1BU
#define RTE_DREAD_SERVICEID                                                   0x1AU
#define RTE_ENTER_SERVICEID                                                   0x2AU
#define RTE_EXIT_SERVICEID                                                    0x2BU
#define RTE_TRIGGER_SERVICEID                                                 0x2DU
#define RTE_IRTRIGGER_SERVICEID                                               0x2EU
#define RTE_SWITCH_SERVICEID                                                  0x15U
#define RTE_SWITCHACK_SERVICEID                                               0x18U
#define RTE_MODE_SERVICEID                                                    0x2CU
#define RTE_PIM_SERVICEID                                                     0x1EU

#define RTE_CALL_SERVICEID                                                    0x1CU
#define RTE_RESULT_SERVICEID                                                  0x1DU

#define RTE_IINVALIDATE_SERVICEID                                             0x24U
#define RTE_IFEEDBACK_SERVICEID                                               0x2FU
#define RTE_IWRITE_SERVICEID                                                  0x22U
#define RTE_IWRITEREF_SERVICEID                                               0x23U
#define RTE_IREAD_SERVICEID                                                   0x21U
#define RTE_ISTATUS_SERVICEID                                                 0x25U
#define RTE_ISUPDATED_SERVICEID                                               0x30U

#define RTE_IRVIREAD_SERVICEID                                                0x26U
#define RTE_IRVIWRITE_SERVICEID                                               0x27U
#define RTE_IRVIWRITEREF_SERVICEID                                            0x31U
#define RTE_IRVREAD_SERVICEID                                                 0x28U
#define RTE_IRVWRITE_SERVICEID                                                0x29U

/******************************************************************************/
/*                        LDCOM call-back Service IDs                         */
/******************************************************************************/
#define RTE_LDCOMCBKRXINDICATION_SERVICEID                                    0xA0U
#define RTE_LDCOMCBKSTARTOFRECEPTION_SERVICEID                                0xA1U
#define RTE_LDCOMCBKCOPYRXDATA_SERVICEID                                      0xA2U
#define RTE_LDCOMCBKTPRXINDICATION_SERVICEID                                  0xA3U
#define RTE_LDCOMCBKCOPYTXDATA_SERVICEID                                      0xA4U
#define RTE_LDCOMCBKTPTXCONFIRMATION_SERVICEID                                0xA5U
#define RTE_LDCOMCBKTRIGGERTRANSMIT_SERVICEID                                 0xA6U
#define RTE_LDCOMCBKTXCONFIRMATION_SERVICEID                                  0xA7U
/******************************************************************************/
/*                         COM call-back Service IDs                          */
/******************************************************************************/
#define RTE_COMCBKTACK_CS_SERVICEID                                           0x90U
#define RTE_COMCBKTERR_CS_SERVICEID                                           0x91U
#define RTE_COMCBKINV_CS_SERVICEID                                            0x92U
#define RTE_COMCBKRXTOUT_CS_SERVICEID                                         0x93U
#define RTE_COMCBKTXTOUT_CS_SERVICEID                                         0x94U
#define RTE_COMCBK_CS_SERVICEID                                               0x9FU

#define RTE_COMCBKTACK_CSG_SERVICEID                                          0x96U
#define RTE_COMCBKTERR_CSG_SERVICEID                                          0x97U
#define RTE_COMCBKINV_CSG_SERVICEID                                           0x98U
#define RTE_COMCBKRXTOUT_CSG_SERVICEID                                        0x99U
#define RTE_COMCBKTXTOUT_CSG_SERVICEID                                        0x9AU
#define RTE_COMCBK_CSG_SERVICEID                                              0x95U
#define RTE_SETMIRROR_SERVICEID                                               0x9BU
#define RTE_GETMIRROR_SERVICEID                                               0x9CU
#define RTE_NVMNOTIFYINITBLOCK_SERVICEID                                      0x9EU
#define RTE_NVMNOTIFYJOBFINISHED_SERVICEID                                    0x9DU

/******************************************************************************/
/*                  Multiple Header Inclusion Protection End                  */
/******************************************************************************/
#endif

/******************************************************************************/
/*                             End of Rte.h File                              */
/******************************************************************************/
