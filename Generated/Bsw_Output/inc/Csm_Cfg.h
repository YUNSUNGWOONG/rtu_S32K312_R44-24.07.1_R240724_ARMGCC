/*******************************************************************************
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  This source code is permitted to be used only in projects contracted      **
**  with Hyundai Autoever, and any other use is prohibited.                   **
**  If you use it for other purposes or change the source code,               **
**  you may take legal responsibility.                                        **
**  In this case, There is no warranty and technical support.                 **
**                                                                            **
**  SRC-MODULE: Csm_Cfg.h                                                     **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Csm                                                   **
**                                                                            **
**  PURPOSE   : Macro configuration datas                                     **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: yes                                       **
**                                                                            **
********************************************************************************

********************************************************************************
**                      Generation Tool Information                           **
********************************************************************************
**  Framework version: 1.1.5                                                **
**  Module version: 1.0.10.0                                                   **
**                                                                            **
**  Change History: Refer log file (use -l option to generate log file)       **
**                                                                            **
********************************************************************************
**                      File Generation Information                           **
*******************************************************************************/
/*
* INPUT FILE:      Configuration\Definition\ECUConfigurationParameters.arxml
*                  Configuration\Ecu\Ecud_CryIf.arxml           
*                  Configuration\Ecu\Ecud_Crypto_76_HaeModule.arxml
*                  Configuration\Ecu\Ecud_Csm.arxml             
*                  Generated\Bsw_Output\bswmd\Bswmd_CryIf.arxml 
*                  Generated\Bsw_Output\bswmd\Bswmd_Crypto_76_HaeModule.arxml
*                  Generated\Bsw_Output\bswmd\Bswmd_Csm.arxml   
*                  Static_Code\Modules\CryIf_R44\generator\CryIf_ECU_Configuration_PDF.arxml
*                  Static_Code\Modules\Crypto_76_HaeModule_R44\generator\AUTOSAR_Crypto_76_HaeModule_ECU_Configuration_PDF.arxml
*                  Static_Code\Modules\Csm_R44\generator\Csm_ECU_Configuration_PDF.arxml
* GENERATED ON: The time-stamp is removed
*/

#ifndef CSM_CFG_H
#define CSM_CFG_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Std_Types.h"

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/*******************************************************************************
**                      User Include File                                     **
*******************************************************************************/
 
/*******************************************************************************
**                      Common Published Information                          **
*******************************************************************************/
#define    CSM_AR_RELEASE_MAJOR_VERSION                  0x04U
#define    CSM_AR_RELEASE_MINOR_VERSION                  0x04U
#define    CSM_AR_RELEASE_REVISION_VERSION               0x00U
#define    CSM_SW_MAJOR_VERSION                          0x01U
#define    CSM_SW_MINOR_VERSION                          0x00U
#define    CSM_SW_PATCH_VERSION                          0x0AU
#define    CSM_VENDOR_ID                                 0x004CU
#define    CSM_MODULE_ID                                 0x006EU

/*******************************************************************************
**                      Precompile Options                                    **
*******************************************************************************/
/* Enable job-base related APIs */
#define    CSM_JOB_PROCESSING_ENABLE                     STD_ON

/* Enable asynchronous job-base related APIs */
#define    CSM_PROCESSING_MODE_ASYNC_ENABLE              STD_ON

/* Enable support for Csm_Hash function */
#define    CSM_PRIMITIVE_HASH_ENABLE                     STD_ON

/* Enable support for Csm_MacGenerate function */
#define    CSM_PRIMITIVE_MAC_GENERATE_ENABLE             STD_ON

/* Enable support for Csm_MacVerify function */
#define    CSM_PRIMITIVE_MAC_VERIFY_ENABLE               STD_ON

/* Enable support for Csm_Encrypt function */
#define    CSM_PRIMITIVE_ENCRYPT_ENABLE                  STD_ON

/* Enable support for Csm_Decrypt function */
#define    CSM_PRIMITIVE_DECRYPT_ENABLE                  STD_ON

/* Enable support for Csm_AEADEncrypt function */
#define    CSM_PRIMITIVE_AEADENCRYPT_ENABLE              STD_OFF

/* Enable support for Csm_AEADDecrypt function */
#define    CSM_PRIMITIVE_AEADDECRYPT_ENABLE              STD_OFF

/* Enable support for Csm_SignatureGenerate function */
#define    CSM_PRIMITIVE_SIGNATURE_GENERATE_ENABLE       STD_OFF

/* Enable support for Csm_SignatureVerify function */
#define    CSM_PRIMITIVE_SIGNATURE_VERIFY_ENABLE         STD_ON

/* Enable support for Csm_RandomGenerate function */
#define    CSM_PRIMITIVE_RANDOM_GENERATE_ENABLE          STD_ON

/* Enable support for Csm_JobKeySetValid function */
#define    CSM_PRIMITIVE_JOB_KEY_SET_VALID_ENABLE        STD_OFF

/* Enable support for Csm_JobRandomSeed function */
#define    CSM_PRIMITIVE_JOB_RANDOM_SEED_ENABLE          STD_OFF

/* Enable support for Csm_JobKeyGenerate function */
#define    CSM_PRIMITIVE_JOB_KEY_GENERATE_ENABLE         STD_OFF

/* Enable support for Csm_JobKeyDerive function */
#define    CSM_PRIMITIVE_JOB_KEY_DERIVE_ENABLE           STD_OFF

/* Enable support for Csm_JobKeyExchangeCalcPubVal function */
#define    CSM_PRIMITIVE_JOB_KEY_EXCHANGE_CALC_PUB_VAL_ENABLE STD_OFF

/* Enable support for Csm_JobKeyExchangeCalcSecret function */
#define    CSM_PRIMITIVE_JOB_KEY_EXCHANGE_CALC_SECRET_ENABLE STD_OFF

/* Enable queuing operations */
#define    CSM_QUEUE_OPERATION_ENABLE                    STD_ON

/* Enable Synchronous Key Management APIs */
#define    CSM_KEY_MANAGEMENT_ENABLE                     STD_ON

/* Enable support for Application Callback */
#define    CSM_APPLICATION_CALLBACK_ENABLE               STD_OFF

#define    CSM_DEV_ERROR_DETECT                          STD_ON

#define    CSM_VERSION_INFO_API                          STD_ON

/* #define CSM_INPUT_DATA_NO_VALIDATION                  NOT_CONFIG */

#define    CSM_USE_DEPRECATED                            STD_OFF

/* #define CSM_ASYM_PUBLIC_KEY_MAX_LENGTH                NOT_CONFIG */

/* #define CSM_ASYM_PRIVATE_KEY_MAX_LENGTH               NOT_CONFIG */

/* Total configured Csm job */
#define    CSM_TOTAL_CONFIGURED_JOB                      13U

/* Total configured Csm queue */
#define    CSM_TOTAL_CONFIGURED_QUEUE                    2U

/* Total configured Csm callback */
#define    CSM_TOTAL_APPLICATION_CALLBACK                0U

/* Maximum value of queue counter */
#define    CSM_QUEUE_COUNTER_MAX                         0xFFFFFFFFU

/* Default value for jobPrimitiveInputOutput */
#define    CSM_DEFAULT_PRIMITIVE_INPUT_OUTPUT            { NULL_PTR, 0U, \
                                                           NULL_PTR, 0U, \
                                                           NULL_PTR, 0U, \
                                                           NULL_PTR, NULL_PTR,\
                                                           NULL_PTR, NULL_PTR,\
                                                           NULL_PTR, 0U, \
                                                           0U, 0U \
                                                         }

/* Total configured Csm key */
#define    CSM_TOTAL_CONFIGURED_KEY                      25U

/* Queue maximum size */
#define    CSM_QUEUE_CSMQUEUE_HSI_MAX_SIZE               3U

/* Queue maximum size */
#define    CSM_QUEUE_CSMQUEUE_CRYPTOLIB_MAX_SIZE         10U


/*******************************************************************************
**                       Callback Function Prototypes                         **
*******************************************************************************/

#endif /* CSM_CFG_H */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
