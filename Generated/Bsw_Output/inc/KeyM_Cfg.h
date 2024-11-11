/*******************************************************************************
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  This source code is permitted to be used only in projects contracted      **
**  with Hyundai Autoever, and any other use is prohibited.                   **
**  If you use it for other purposes or change the source code,               **
**  you may take legal responsibility.                                        **
**  In this case, There is no warranty and technical support.                 **
**                                                                            **
**  SRC-MODULE: KeyM_Cfg.h                                           **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR KeyM                                                  **
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
**  Framework version : 1.1.5                                          **
**                                                                            **
**  Module version : 1.0.9.0                                         **
**                                                                            **
**  Tool Version:                                               **
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
*                  Configuration\Ecu\Ecud_KeyM.arxml            
*                  Configuration\Ecu\Ecud_NvM.arxml             
*                  Configuration\Ecu\Ecud_StbM.arxml            
*                  Generated\Bsw_Output\bswmd\Bswmd_CryIf.arxml 
*                  Generated\Bsw_Output\bswmd\Bswmd_Crypto_76_HaeModule.arxml
*                  Generated\Bsw_Output\bswmd\Bswmd_Csm.arxml   
*                  Generated\Bsw_Output\bswmd\Bswmd_KeyM.arxml  
*                  Generated\Bsw_Output\bswmd\Bswmd_NvM.arxml   
*                  Generated\Bsw_Output\bswmd\Bswmd_StbM.arxml  
*                  Generated\Bsw_Output\swcd\Swcd_Bsw_StbM.arxml
*                  Static_Code\Modules\CryIf_R44\generator\CryIf_ECU_Configuration_PDF.arxml
*                  Static_Code\Modules\Crypto_76_HaeModule_R44\generator\AUTOSAR_Crypto_76_HaeModule_ECU_Configuration_PDF.arxml
*                  Static_Code\Modules\Csm_R44\generator\Csm_ECU_Configuration_PDF.arxml
*                  Static_Code\Modules\KeyM_R44\generator\KeyM_ECU_Configuration_PDF.arxml
*                  Static_Code\Modules\NvM_R44\generator\NvM_ECU_Configuration_PDF.arxml
*                  Static_Code\Modules\StbM_R44\generator\StbM_ECU_Configuration_PDF.arxml
* GENERATED ON: The time-stamp is removed
*/

#ifndef KEYM_CFG_H
#define KEYM_CFG_H
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Std_Types.h"
#include "Rte_KeyM_Type.h"            /* Rte KeyM Type file */

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/*******************************************************************************
**                      Common Published Information                          **
*******************************************************************************/
#define    KEYM_AR_RELEASE_MAJOR_VERSION                 0x04U
#define    KEYM_AR_RELEASE_MINOR_VERSION                 0x04U
#define    KEYM_AR_RELEASE_REVISION_VERSION              0x00U
#define    KEYM_SW_MAJOR_VERSION                         0x01U
#define    KEYM_SW_MINOR_VERSION                         0x00U
#define    KEYM_SW_PATCH_VERSION                         0x09U
#define    KEYM_VENDOR_ID                                0x004CU
#define    KEYM_MODULE_ID                                0x006DU

/*******************************************************************************
**                      Precompile Options                                    **
*******************************************************************************/
/* Enables or disables the part that manages certificates */
#define KEYM_CERTIFICATE_MANAGER_ENABLED                       (STD_OFF)

/* Enables or disables the key handler prepare function call */
#define KEYM_CRYPTO_KEY_HANDLER_PREPARE_ENABLED                (STD_OFF)

/* Enables or disables the key handler service function call */
#define KEYM_CRYPTO_KEY_HANDLER_SERVICE_CERTIFICATE_ENABLED    (STD_OFF)

/* Enables or disables the key handler start and finalize function call */
#define KEYM_CRYPTO_KEY_HANDLER_START_FINALIZE_ENABLED         (STD_OFF)

/* Enables or disables the call to the key handler update function KeyM_KH_Update() */
#define KEYM_CRYPTO_KEY_HANDLER_UPDATE_ENABLED                 (STD_OFF)

/* Enables or disables the call to the key handler verify function KeyM_KH_Verify() */
#define KEYM_CRYPTO_KEY_HANDLER_VERIFY_ENABLED                 (STD_OFF)

/* Enables or disables the part that manages crypto key operations */
#define KEYM_CRYPTO_KEY_MANAGER_ENABLED                        (STD_ON)

/* Enables or disables the prepare function of the key manager */
#define KEYM_CRYPTO_KEY_PREPARE_FUNCTION_ENABLED               (STD_OFF)

/* Enables or disables the start and finish function of the key manager */
#define KEYM_CRYPTO_KEY_START_FINALIZE_FUNCTION_ENABLED        (STD_OFF)

/* This parameter defines if the function KeyM_Verify() runs in synchronous or asynchronous mode */
#define KEYM_CRYPTO_KEY_VERIFY_ASYNC_MODE                      (STD_OFF)

/* Enables or disables the verify function of the key manager */
#define KEYM_CRYPTO_KEY_VERIFY_FUNCTION_ENABLED                (STD_OFF)

/* Enables or disables the certificate service function of the key manager */
#define KEYM_SERVICE_CERTIFICATE_FUNCTION_ENABLED              (STD_OFF)

/* Enables or disable the certificate element verification */
#define KEYM_CERT_ELEMENT_VERIFICATION_ENABLED                 (STD_OFF)

/* Enables or disable the certificate private key storage */
#define KEYM_CERT_PRIVATE_KEY_STORAGE_ENABLED                  (STD_OFF)

/* Enables or disable the certificate element object type */
#define KEYM_CERT_ELEMENT_OBJECT_TYPE_ENABLED                  (STD_OFF)

/* Enables or disable the certificate element condition primitive */
#define KEYM_CERT_ELEMENT_COND_PRIMITIVE_ENABLED               (STD_OFF)

/* Enables or disable the certificate element condition element */
#define KEYM_CERT_ELEMENT_COND_ELEMENT_ENABLED                 (STD_OFF)

/* Enables or disable cerificate element condition array */
#define KEYM_CERT_ELEMENT_COND_ARRAY_ENABLED                   (STD_OFF)

/* Enables or disable the certificate element condition sender received */
#define KEYM_CERT_ELEMENT_COND_SENDER_RECEIVER_ENABLED         (STD_OFF)

/* Enables or disable the certificate signature generate */
#define KEYM_CERT_SIGNATURE_GENERATE_ENABLED                   (STD_OFF)

/* Enables or disable the key additional hint */
#define KEYM_CRYPTO_KEY_ADDITIONAL_HINT_ENABLED                (STD_OFF)

/* Enables or disables storage Key in NvM */
#define KEYM_STORAGE_IN_NVM_ENABLED                            (STD_OFF)

/* Configure for Det error detect */
#define KEYM_DEV_ERROR_DETECT                                  (STD_ON)

/* Maximum number of certificates defined in a certificate chain */
#define KEYM_CERTIFICATE_CHAIN_MAX_DEPTH                       (3U)

/* Maximum length in bytes of certificate or key names used for the service interface */
#define KEYM_KEY_CERT_NAME_MAX_LENGTH                          (14U)

/* Specifies the period of main function KeyM_MainFunction in seconds */
#define KEYM_MAIN_FUNCTION_PERIOD                              (0.01)

/* Internal buffer length */
#define KEYM_INTERAL_BUFFER_LENGTH                             (300U)

/* Certificate verify application callback enable */
#define KEYM_CERT_VERIFY_APPLICATION_CALLBACK_ENABLE           (STD_OFF)

/* Certificate service application callback enable */
#define KEYM_CERT_SERVICE_APPLICATION_CALLBACK_ENABLE          (STD_OFF)

/* Specifies STBM module is used to get current time */
#define KEYM_USE_STBM                                          (STD_OFF)
/*******************************************************************************
**                      Computed Macros                                       **
*******************************************************************************/
/* Total key of KeyM */
#define KEYM_TOTAL_KEY                                         (0x01U)

/* Total certificate of KeyM */
#define KEYM_TOTAL_CERTIFICATE                                 (0x00U)


/* Enables or disables CVC Cerificate */
#define KEYM_CERT_CVC_CERTIFICATE_ENABLED                      (STD_OFF)

/* Enables or disables X509 Cerificate */
#define KEYM_CERT_X509_CERTIFICATE_ENABLED                     (STD_OFF)

/* Enables or disables X509 CRL Cerificate */
#define KEYM_CERT_X509_CRL_ENABLED                             (STD_OFF)

/* Maximum number of revoked Certificates element in a CRL */
#define KEYM_CERT_MAX_REVOK_ENTRY                              (0U)

/* Maximum number of certificateIssuerName and certificateSubjectName element in a X509 cerificate and CRL */
#define KEYM_CERT_MAX_NAME_NUMBER                              (0U)

/* Maximum number of certificateExtension element in a cerificate */
#define KEYM_CERT_MAX_EXTENSION_NUMBER                         (0U)

/* Maximum number of certificateSubjectPublicKeyInfo_SubjectPublicKey a CVC cerificate */
#define KEYM_CERT_MAX_DOMAIN_PARAM_NUMBER                      (0U)

#define KEYM_START_SEC_VAR_CLEARED_8
#include "MemMap.h"

/* Array contains data of key 1 */
extern VAR(uint8, KEYM_VAR_CLEARED) KeyMCryptoKey_DummyKey[];


#define KEYM_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h"







#endif /* KEYM_CFG_H */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
