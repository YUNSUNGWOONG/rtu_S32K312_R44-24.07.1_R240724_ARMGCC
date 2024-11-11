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
**  File Name : Rte_Dcm_Type.h                                                **
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
#ifndef RTE_DCM_TYPE_H
#define RTE_DCM_TYPE_H

/******************************************************************************/
/*                              Header Inclusion                              */
/******************************************************************************/
#include "Rte_Type.h"

/******************************************************************************/
/*                Compatibility between C/C++ Languages Start                 */
/******************************************************************************/
#ifdef __cplusplus
extern "C" 
{

#endif

/******************************************************************************/
/*                           Enumeration DataTypes                            */
/******************************************************************************/
#ifndef DCM_E_CONDITIONSNOTCORRECT
#define DCM_E_CONDITIONSNOTCORRECT                                            0x22U
#endif /* DCM_E_CONDITIONSNOTCORRECT */

#ifndef DCM_E_REQUESTOUTOFRANGE
#define DCM_E_REQUESTOUTOFRANGE                                               0x31U
#endif /* DCM_E_REQUESTOUTOFRANGE */

#ifndef DCM_E_GENERALREJECT
#define DCM_E_GENERALREJECT                                                   0x10U
#endif /* DCM_E_GENERALREJECT */

#ifndef DCM_E_VEHICLESPEEDTOOLOW
#define DCM_E_VEHICLESPEEDTOOLOW                                              0x89U
#endif /* DCM_E_VEHICLESPEEDTOOLOW */

#ifndef DCM_E_VMSCNC_7
#define DCM_E_VMSCNC_7                                                        0xF7U
#endif /* DCM_E_VMSCNC_7 */

#ifndef DCM_E_VMSCNC_B
#define DCM_E_VMSCNC_B                                                        0xFBU
#endif /* DCM_E_VMSCNC_B */

#ifndef DCM_E_CERTIFICATEVERIFICATIONFAILEDINVALIDTYPE
#define DCM_E_CERTIFICATEVERIFICATIONFAILEDINVALIDTYPE                        0x53U
#endif /* DCM_E_CERTIFICATEVERIFICATIONFAILEDINVALIDTYPE */

#ifndef DCM_E_THROTTLE_PEDALTOOHIGH
#define DCM_E_THROTTLE_PEDALTOOHIGH                                           0x8AU
#endif /* DCM_E_THROTTLE_PEDALTOOHIGH */

#ifndef DCM_E_TRANSFERDATASUSPENDED
#define DCM_E_TRANSFERDATASUSPENDED                                           0x71U
#endif /* DCM_E_TRANSFERDATASUSPENDED */

#ifndef DCM_UDS_ON_FLEXRAY
#define DCM_UDS_ON_FLEXRAY                                                    4U
#endif /* DCM_UDS_ON_FLEXRAY */

#ifndef DCM_DID_SUPPORTED
#define DCM_DID_SUPPORTED                                                     0x00U
#endif /* DCM_DID_SUPPORTED */

#ifndef DCM_E_RPMTOOLOW
#define DCM_E_RPMTOOLOW                                                       0x82U
#endif /* DCM_E_RPMTOOLOW */

#ifndef DCM_E_FAILUREPREVENTSEXECUTIONOFREQUESTEDACTION
#define DCM_E_FAILUREPREVENTSEXECUTIONOFREQUESTEDACTION                       0x26U
#endif /* DCM_E_FAILUREPREVENTSEXECUTIONOFREQUESTEDACTION */

#ifndef DCM_NO_ACTIVE_PROTOCOL
#define DCM_NO_ACTIVE_PROTOCOL                                                12U
#endif /* DCM_NO_ACTIVE_PROTOCOL */

#ifndef DCM_E_CERTIFICATEVERIFICATIONFAILEDINVALIDSIGNATURE
#define DCM_E_CERTIFICATEVERIFICATIONFAILEDINVALIDSIGNATURE                   0x51U
#endif /* DCM_E_CERTIFICATEVERIFICATIONFAILEDINVALIDSIGNATURE */

#ifndef DCM_RESPONSE_PENDING
#define DCM_RESPONSE_PENDING                                                  0x78U
#endif /* DCM_RESPONSE_PENDING */

#ifndef DCM_E_UPLOADDOWNLOADNOTACCEPTED
#define DCM_E_UPLOADDOWNLOADNOTACCEPTED                                       0x70U
#endif /* DCM_E_UPLOADDOWNLOADNOTACCEPTED */

#ifndef DCM_E_CRLINTEGRITYCHECKFAILED
#define DCM_E_CRLINTEGRITYCHECKFAILED                                         0xF0U
#endif /* DCM_E_CRLINTEGRITYCHECKFAILED */

#ifndef DCM_PERIODICTRANS_ON_IP
#define DCM_PERIODICTRANS_ON_IP                                               11U
#endif /* DCM_PERIODICTRANS_ON_IP */

#ifndef DCM_E_VMSCNC_8
#define DCM_E_VMSCNC_8                                                        0xF8U
#endif /* DCM_E_VMSCNC_8 */

#ifndef DCM_E_SUBFUNCTIONNOTSUPPORTEDINACTIVESESSION
#define DCM_E_SUBFUNCTIONNOTSUPPORTEDINACTIVESESSION                          0x7EU
#endif /* DCM_E_SUBFUNCTIONNOTSUPPORTEDINACTIVESESSION */

#ifndef DCM_SAFETY_SYSTEM_DIAGNOSTIC_SESSION
#define DCM_SAFETY_SYSTEM_DIAGNOSTIC_SESSION                                  4U
#endif /* DCM_SAFETY_SYSTEM_DIAGNOSTIC_SESSION */

#ifndef DCM_E_VMSCNC_C
#define DCM_E_VMSCNC_C                                                        0xFCU
#endif /* DCM_E_VMSCNC_C */

#ifndef DCM_E_TEMPERATURETOOHIGH
#define DCM_E_TEMPERATURETOOHIGH                                              0x86U
#endif /* DCM_E_TEMPERATURETOOHIGH */

#ifndef DCM_E_EXCEEDNUMBEROFATTEMPTS
#define DCM_E_EXCEEDNUMBEROFATTEMPTS                                          0x36U
#endif /* DCM_E_EXCEEDNUMBEROFATTEMPTS */

#ifndef DCM_E_NORESPONSEFROMSUBNETCOMPONENT
#define DCM_E_NORESPONSEFROMSUBNETCOMPONENT                                   0x25U
#endif /* DCM_E_NORESPONSEFROMSUBNETCOMPONENT */

#ifndef DCM_POS_RESP
#define DCM_POS_RESP                                                          0x00U
#endif /* DCM_POS_RESP */

#ifndef DCM_E_DEAUTHENTICATIONFAILED
#define DCM_E_DEAUTHENTICATIONFAILED                                          0x5DU
#endif /* DCM_E_DEAUTHENTICATIONFAILED */

#ifndef DCM_E_ROLEANDRIGHTCERTIFICATEDENIED
#define DCM_E_ROLEANDRIGHTCERTIFICATEDENIED                                   0xF2U
#endif /* DCM_E_ROLEANDRIGHTCERTIFICATEDENIED */

#ifndef DCM_PROGRAMMING_SESSION
#define DCM_PROGRAMMING_SESSION                                               2U
#endif /* DCM_PROGRAMMING_SESSION */

#ifndef DCM_CANCEL
#define DCM_CANCEL                                                            2U
#endif /* DCM_CANCEL */

#ifndef DCM_PERIODICTRANS_ON_FLEXRAY
#define DCM_PERIODICTRANS_ON_FLEXRAY                                          10U
#endif /* DCM_PERIODICTRANS_ON_FLEXRAY */

#ifndef DCM_E_BRAKESWITCH_NOTCLOSED
#define DCM_E_BRAKESWITCH_NOTCLOSED                                           0x8FU
#endif /* DCM_E_BRAKESWITCH_NOTCLOSED */

#ifndef DCM_RES_NEG_OK
#define DCM_RES_NEG_OK                                                        2U
#endif /* DCM_RES_NEG_OK */

#ifndef DCM_E_ENGINEISRUNNING
#define DCM_E_ENGINEISRUNNING                                                 0x83U
#endif /* DCM_E_ENGINEISRUNNING */

#ifndef DCM_ROE_ON_IP
#define DCM_ROE_ON_IP                                                         8U
#endif /* DCM_ROE_ON_IP */

#ifndef DCM_OBD_ON_FLEXRAY
#define DCM_OBD_ON_FLEXRAY                                                    1U
#endif /* DCM_OBD_ON_FLEXRAY */

#ifndef DCM_IDLE
#define DCM_IDLE                                                              255U
#endif /* DCM_IDLE */

#ifndef DCM_E_WRONGBLOCKSEQUENCECOUNTER
#define DCM_E_WRONGBLOCKSEQUENCECOUNTER                                       0x73U
#endif /* DCM_E_WRONGBLOCKSEQUENCECOUNTER */

#ifndef DCM_E_VEHICLESPEEDTOOHIGH
#define DCM_E_VEHICLESPEEDTOOHIGH                                             0x88U
#endif /* DCM_E_VEHICLESPEEDTOOHIGH */

#ifndef DCM_E_ENGINERUNTIMETOOLOW
#define DCM_E_ENGINERUNTIMETOOLOW                                             0x85U
#endif /* DCM_E_ENGINERUNTIMETOOLOW */

#ifndef DCM_POSITIVE_RESPONSE
#define DCM_POSITIVE_RESPONSE                                                 0x00U
#endif /* DCM_POSITIVE_RESPONSE */

#ifndef DCM_E_CERTIFICATEVERIFICATIONFAILEDINVALIDFORMAT
#define DCM_E_CERTIFICATEVERIFICATIONFAILEDINVALIDFORMAT                      0x54U
#endif /* DCM_E_CERTIFICATEVERIFICATIONFAILEDINVALIDFORMAT */

#ifndef DCM_E_VMSCNC_9
#define DCM_E_VMSCNC_9                                                        0xF9U
#endif /* DCM_E_VMSCNC_9 */

#ifndef DCM_E_INVALIDKEY
#define DCM_E_INVALIDKEY                                                      0x35U
#endif /* DCM_E_INVALIDKEY */

#ifndef DCM_OBD_ON_CAN
#define DCM_OBD_ON_CAN                                                        0U
#endif /* DCM_OBD_ON_CAN */

#ifndef DCM_CONDITIONS_NOT_CORRECT
#define DCM_CONDITIONS_NOT_CORRECT                                            0x22U
#endif /* DCM_CONDITIONS_NOT_CORRECT */

#ifndef DCM_PENDING
#define DCM_PENDING                                                           1U
#endif /* DCM_PENDING */

#ifndef DCM_RES_NEG_NOT_OK
#define DCM_RES_NEG_NOT_OK                                                    3U
#endif /* DCM_RES_NEG_NOT_OK */

#ifndef DCM_E_VMSCNC_D
#define DCM_E_VMSCNC_D                                                        0xFDU
#endif /* DCM_E_VMSCNC_D */

#ifndef DCM_ZEV_ON_UDS
#define DCM_ZEV_ON_UDS                                                        15U
#endif /* DCM_ZEV_ON_UDS */

#ifndef DCM_E_VMSCNC_4
#define DCM_E_VMSCNC_4                                                        0xF4U
#endif /* DCM_E_VMSCNC_4 */

#ifndef DCM_E_SERVICENOTSUPPORTEDINACTIVESESSION
#define DCM_E_SERVICENOTSUPPORTEDINACTIVESESSION                              0x7FU
#endif /* DCM_E_SERVICENOTSUPPORTEDINACTIVESESSION */

#ifndef DCM_E_TRANSMISSIONRANGENOTINNEUTRAL
#define DCM_E_TRANSMISSIONRANGENOTINNEUTRAL                                   0x8CU
#endif /* DCM_E_TRANSMISSIONRANGENOTINNEUTRAL */

#ifndef DCM_E_CERTIFICATEVERIFICATIONFAILEDINVALIDCONTENT
#define DCM_E_CERTIFICATEVERIFICATIONFAILEDINVALIDCONTENT                     0x55U
#endif /* DCM_E_CERTIFICATEVERIFICATIONFAILEDINVALIDCONTENT */

#ifndef DCM_E_SETTINGACCESSRIGHTSFAILED
#define DCM_E_SETTINGACCESSRIGHTSFAILED                                       0x5AU
#endif /* DCM_E_SETTINGACCESSRIGHTSFAILED */

#ifndef DCM_RES_POS_NOT_OK
#define DCM_RES_POS_NOT_OK                                                    1U
#endif /* DCM_RES_POS_NOT_OK */

#ifndef DCM_ECU_PROGRAMMING_MODE_05H
#define DCM_ECU_PROGRAMMING_MODE_05H                                          5U
#endif /* DCM_ECU_PROGRAMMING_MODE_05H */

#ifndef DCM_RETURN_CONTROL_TO_ECU
#define DCM_RETURN_CONTROL_TO_ECU                                             0U
#endif /* DCM_RETURN_CONTROL_TO_ECU */

#ifndef DCM_PERIODICTRANS_ON_CAN
#define DCM_PERIODICTRANS_ON_CAN                                              9U
#endif /* DCM_PERIODICTRANS_ON_CAN */

#ifndef DCM_FORCE_RCRRP_OK
#define DCM_FORCE_RCRRP_OK                                                    3U
#endif /* DCM_FORCE_RCRRP_OK */

#ifndef DCM_OBD_ON_IP
#define DCM_OBD_ON_IP                                                         2U
#endif /* DCM_OBD_ON_IP */

#ifndef DCM_OBD_ON_UDS
#define DCM_OBD_ON_UDS                                                        14U
#endif /* DCM_OBD_ON_UDS */

#ifndef DCM_E_VMSCNC_E
#define DCM_E_VMSCNC_E                                                        0xFEU
#endif /* DCM_E_VMSCNC_E */

#ifndef DCM_DEFAULT_SESSION
#define DCM_DEFAULT_SESSION                                                   1U
#endif /* DCM_DEFAULT_SESSION */

#ifndef DCM_E_CONFIGURATIONDATAUSAGEFAILED
#define DCM_E_CONFIGURATIONDATAUSAGEFAILED                                    0x5CU
#endif /* DCM_E_CONFIGURATIONDATAUSAGEFAILED */

#ifndef DCM_E_SERVICENOTSUPPORTED
#define DCM_E_SERVICENOTSUPPORTED                                             0x11U
#endif /* DCM_E_SERVICENOTSUPPORTED */

#ifndef DCM_E_SECURITYACCESSDENIED
#define DCM_E_SECURITYACCESSDENIED                                            0x33U
#endif /* DCM_E_SECURITYACCESSDENIED */

#ifndef DCM_DID_NOT_SUPPORTED
#define DCM_DID_NOT_SUPPORTED                                                 0x01U
#endif /* DCM_DID_NOT_SUPPORTED */

#ifndef DCM_E_VMSCNC_5
#define DCM_E_VMSCNC_5                                                        0xF5U
#endif /* DCM_E_VMSCNC_5 */

#ifndef DCM_BUSY_REPEAT_REQUEST
#define DCM_BUSY_REPEAT_REQUEST                                               0x21U
#endif /* DCM_BUSY_REPEAT_REQUEST */

#ifndef DCM_SEC_LEV_LOCKED
#define DCM_SEC_LEV_LOCKED                                                    0U
#endif /* DCM_SEC_LEV_LOCKED */

#ifndef DCM_E_VOLTAGETOOLOW
#define DCM_E_VOLTAGETOOLOW                                                   0x93U
#endif /* DCM_E_VOLTAGETOOLOW */

#ifndef DCM_FAILURE_PREVENTS_EXECUTION
#define DCM_FAILURE_PREVENTS_EXECUTION                                        0x26U
#endif /* DCM_FAILURE_PREVENTS_EXECUTION */

#ifndef DCM_E_CERTIFICATEVERIFICATIONFAILEDINVALIDSCOPE
#define DCM_E_CERTIFICATEVERIFICATIONFAILEDINVALIDSCOPE                       0x56U
#endif /* DCM_E_CERTIFICATEVERIFICATIONFAILEDINVALIDSCOPE */

#ifndef DCM_GENERAL_REJECT
#define DCM_GENERAL_REJECT                                                    0x10U
#endif /* DCM_GENERAL_REJECT */

#ifndef DCM_E_SECURITYACCESSDENIEDFROMCGW
#define DCM_E_SECURITYACCESSDENIEDFROMCGW                                     0xF3U
#endif /* DCM_E_SECURITYACCESSDENIEDFROMCGW */

#ifndef DCM_E_OWNERSHIPVERIFICATIONFAILED
#define DCM_E_OWNERSHIPVERIFICATIONFAILED                                     0x58U
#endif /* DCM_E_OWNERSHIPVERIFICATIONFAILED */

#ifndef DCM_E_CERTIFICATEVERIFICATIONFAILEDINVALIDCHAINOFTRUST
#define DCM_E_CERTIFICATEVERIFICATIONFAILEDINVALIDCHAINOFTRUST                0x52U
#endif /* DCM_E_CERTIFICATEVERIFICATIONFAILEDINVALIDCHAINOFTRUST */

#ifndef DCM_UDS_ON_CAN
#define DCM_UDS_ON_CAN                                                        3U
#endif /* DCM_UDS_ON_CAN */

#ifndef DCM_E_REQUESTSEQUENCEERROR
#define DCM_E_REQUESTSEQUENCEERROR                                            0x24U
#endif /* DCM_E_REQUESTSEQUENCEERROR */

#ifndef DCM_SHORT_TERM_ADJUSTMENT
#define DCM_SHORT_TERM_ADJUSTMENT                                             3U
#endif /* DCM_SHORT_TERM_ADJUSTMENT */

#ifndef DCM_EXTENDED_DIAGNOSTIC_SESSION
#define DCM_EXTENDED_DIAGNOSTIC_SESSION                                       3U
#endif /* DCM_EXTENDED_DIAGNOSTIC_SESSION */

#ifndef DCM_RESET_TO_DEFAULT
#define DCM_RESET_TO_DEFAULT                                                  1U
#endif /* DCM_RESET_TO_DEFAULT */

#ifndef DCM_E_CERTIFICATEVERIFICATIONFAILEDINVALIDTIMEPERIOD
#define DCM_E_CERTIFICATEVERIFICATIONFAILEDINVALIDTIMEPERIOD                  0x50U
#endif /* DCM_E_CERTIFICATEVERIFICATIONFAILEDINVALIDTIMEPERIOD */

#ifndef DCM_E_RESPONSETOOLONG
#define DCM_E_RESPONSETOOLONG                                                 0x14U
#endif /* DCM_E_RESPONSETOOLONG */

#ifndef DCM_ALL_SESSION_LEVEL
#define DCM_ALL_SESSION_LEVEL                                                 255U
#endif /* DCM_ALL_SESSION_LEVEL */

#ifndef DCM_FREEZE_CURRENT_STATE
#define DCM_FREEZE_CURRENT_STATE                                              2U
#endif /* DCM_FREEZE_CURRENT_STATE */

#ifndef DCM_E_TEMPERATURETOOLOW
#define DCM_E_TEMPERATURETOOLOW                                               0x87U
#endif /* DCM_E_TEMPERATURETOOLOW */

#ifndef DCM_E_BUSYREPEATREQUEST
#define DCM_E_BUSYREPEATREQUEST                                               0x21U
#endif /* DCM_E_BUSYREPEATREQUEST */

#ifndef DCM_E_GENERALPROGRAMMINGFAILURE
#define DCM_E_GENERALPROGRAMMINGFAILURE                                       0x72U
#endif /* DCM_E_GENERALPROGRAMMINGFAILURE */

#ifndef DCM_E_SESSIONKEYCREATIONDERIVATIONFAILED
#define DCM_E_SESSIONKEYCREATIONDERIVATIONFAILED                              0x5BU
#endif /* DCM_E_SESSIONKEYCREATIONDERIVATIONFAILED */

#ifndef DCM_E_VMSCNC_6
#define DCM_E_VMSCNC_6                                                        0xF6U
#endif /* DCM_E_VMSCNC_6 */

#ifndef DCM_E_SUBFUNCTIONNOTSUPPORTED
#define DCM_E_SUBFUNCTIONNOTSUPPORTED                                         0x12U
#endif /* DCM_E_SUBFUNCTIONNOTSUPPORTED */

#ifndef DCM_RES_POS_OK
#define DCM_RES_POS_OK                                                        0U
#endif /* DCM_RES_POS_OK */

#ifndef DCM_E_VMSCNC_A
#define DCM_E_VMSCNC_A                                                        0xFAU
#endif /* DCM_E_VMSCNC_A */

#ifndef DCM_E_CERTIFICATEVERIFICATIONFAILEDINVALIDCERTIFICATE
#define DCM_E_CERTIFICATEVERIFICATIONFAILEDINVALIDCERTIFICATE                 0x57U
#endif /* DCM_E_CERTIFICATEVERIFICATIONFAILEDINVALIDCERTIFICATE */

#ifndef DCM_E_REQUIREDTIMEDELAYNOTEXPIRED
#define DCM_E_REQUIREDTIMEDELAYNOTEXPIRED                                     0x37U
#endif /* DCM_E_REQUIREDTIMEDELAYNOTEXPIRED */

#ifndef DCM_E_CRLEXPIRED
#define DCM_E_CRLEXPIRED                                                      0xF1U
#endif /* DCM_E_CRLEXPIRED */

#ifndef DCM_E_CHALLENGECALCULATIONFAILED
#define DCM_E_CHALLENGECALCULATIONFAILED                                      0x59U
#endif /* DCM_E_CHALLENGECALCULATIONFAILED */

#ifndef DCM_E_TORQUECONVERTERCLUTCHLOCKED
#define DCM_E_TORQUECONVERTERCLUTCHLOCKED                                     0x91U
#endif /* DCM_E_TORQUECONVERTERCLUTCHLOCKED */

#ifndef DCM_E_THROTTLE_PEDALTOOLOW
#define DCM_E_THROTTLE_PEDALTOOLOW                                            0x8BU
#endif /* DCM_E_THROTTLE_PEDALTOOLOW */

#ifndef DCM_E_RPMTOOHIGH
#define DCM_E_RPMTOOHIGH                                                      0x81U
#endif /* DCM_E_RPMTOOHIGH */

#ifndef DCM_E_AUTHENTICATIONREQUIRED
#define DCM_E_AUTHENTICATIONREQUIRED                                          0x34U
#endif /* DCM_E_AUTHENTICATIONREQUIRED */

#ifndef DCM_E_TRANSMISSIONRANGENOTINGEAR
#define DCM_E_TRANSMISSIONRANGENOTINGEAR                                      0x8DU
#endif /* DCM_E_TRANSMISSIONRANGENOTINGEAR */

#ifndef DCM_ROE_ON_CAN
#define DCM_ROE_ON_CAN                                                        6U
#endif /* DCM_ROE_ON_CAN */

#ifndef DCM_UDS_ON_IP
#define DCM_UDS_ON_IP                                                         5U
#endif /* DCM_UDS_ON_IP */

#ifndef DCM_INITIAL
#define DCM_INITIAL                                                           0U
#endif /* DCM_INITIAL */

#ifndef DCM_E_ENGINEISNOTRUNNING
#define DCM_E_ENGINEISNOTRUNNING                                              0x84U
#endif /* DCM_E_ENGINEISNOTRUNNING */

#ifndef DCM_E_VOLTAGETOOHIGH
#define DCM_E_VOLTAGETOOHIGH                                                  0x92U
#endif /* DCM_E_VOLTAGETOOHIGH */

#ifndef DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT
#define DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT                           0x13U
#endif /* DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT */

#ifndef DCM_REQUEST_OUT_OF_RANGE
#define DCM_REQUEST_OUT_OF_RANGE                                              0x31U
#endif /* DCM_REQUEST_OUT_OF_RANGE */

#ifndef DCM_UDS_ON_LIN
#define DCM_UDS_ON_LIN                                                        13U
#endif /* DCM_UDS_ON_LIN */

#ifndef DCM_E_SHIFTERLEVERNOTINPARK
#define DCM_E_SHIFTERLEVERNOTINPARK                                           0x90U
#endif /* DCM_E_SHIFTERLEVERNOTINPARK */

#ifndef DCM_SEC_LEV_ALL
#define DCM_SEC_LEV_ALL                                                       255U
#endif /* DCM_SEC_LEV_ALL */

#ifndef DCM_ROE_ON_FLEXRAY
#define DCM_ROE_ON_FLEXRAY                                                    7U
#endif /* DCM_ROE_ON_FLEXRAY */

/******************************************************************************/
/*                 Compatibility between C/C++ Languages End                  */
/******************************************************************************/
#ifdef __cplusplus
}
#endif

/******************************************************************************/
/*                  Multiple Header Inclusion Protection End                  */
/******************************************************************************/
#endif

/******************************************************************************/
/*                              End of the file                               */
/******************************************************************************/
