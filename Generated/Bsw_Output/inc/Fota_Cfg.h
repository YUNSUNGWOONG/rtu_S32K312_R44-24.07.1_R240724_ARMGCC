/*******************************************************************************
**                                                                            **
**  (C) 2022 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Fota_Cfg.h                                                    **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Firmware Over The Air                                 **
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
**  Framework version : 1.1.5                                                **
**                                                                            **
**  Module version : 0.0.6.4                                                  **
**                                                                            **
**  Tool Version:                                                        **
**                                                                            **
**  Change History: Refer log file (use -l option to generate log file)       **
**                                                                            **
********************************************************************************
**                      File Generation Information                           **
*******************************************************************************/
/*
* INPUT FILE:      Configuration\Definition\Crypto_s32k312_mqfp172.epd
*                  Configuration\Ecu\Ecud_CryIf.arxml           
*                  Configuration\Ecu\Ecud_Crypto_76_HaeModule.arxml
*                  Configuration\Ecu\Ecud_Csm.arxml             
*                  Configuration\Ecu\Ecud_Fota.arxml            
*                  Configuration\Ecu\Ecud_Mem_76_Pfls.arxml     
*                  Configuration\Ecu\Mcal\Ecud_Crypto.arxml     
*                  Generated\Bsw_Output\bswmd\Bswmd_Fota.arxml  
*                  Static_Code\Modules\CryIf_R44\generator\CryIf_ECU_Configuration_PDF.arxml
*                  Static_Code\Modules\Crypto_76_HaeModule_R44\generator\AUTOSAR_Crypto_76_HaeModule_ECU_Configuration_PDF.arxml
*                  Static_Code\Modules\Csm_R44\generator\Csm_ECU_Configuration_PDF.arxml
*                  Static_Code\Modules\Fota_R44\generator\Fota_ECU_Configuration_PDF.arxml
*                  Static_Code\Modules\Mem_R44\generator\Mem_76_Pfls_ECU_Configuration_PDF.arxml
* GENERATED ON: The time-stamp is removed
*/
#ifndef FOTA_CFG_H
#define FOTA_CFG_H
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/



/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
#define    FOTA_CFG_AR_RELEASE_MAJOR_VERSION             0x04u
#define    FOTA_CFG_AR_RELEASE_MINOR_VERSION             0x04u
#define    FOTA_CFG_AR_RELEASE_REVISION_VERSION          0x00u
#define    FOTA_CFG_SW_MAJOR_VERSION                     0x00u
#define    FOTA_CFG_SW_MINOR_VERSION                     0x00u
#define    FOTA_CFG_SW_PATCH_VERSION                     0x01u

/*******************************************************************************
**                      Common Published Information                          **
*******************************************************************************/
#define    FOTA_AR_RELEASE_MAJOR_VERSION                 0x04U
#define    FOTA_AR_RELEASE_MINOR_VERSION                 0x04U
#define    FOTA_AR_RELEASE_REVISION_VERSION              0x00U
#define    FOTA_SW_MAJOR_VERSION                         0x00U
#define    FOTA_SW_MINOR_VERSION                         0x00U
#define    FOTA_SW_PATCH_VERSION                         0x01U
#define    FOTA_VENDOR_ID                                0x004CU
#define    FOTA_MODULE_ID                                0x00FFU


/*******************************************************************************
**                      Pre-compile Options                                   **
*******************************************************************************/
#define    FOTA_STD_ON                                   (1U)
#define    FOTA_STD_OFF                                  (0U)
#define    FOTA_FBL_MODE                                 (0U)
#define    FOTA_APP_MODE                                 (1U)
#define    FOTA_UPDATER_MODE                             (2U)
#define    FOTA_SEC_SHA160                               (0U)
#define    FOTA_SEC_SHA256                               (1U)
#define    FOTA_OTA_ES98765_01                           (0U)
#define    FOTA_OTA_ES98765_02                           (1U)
#define    FOTA_VERIFY_DATA_SIZE_ONE_CYCLE_MAX           (0U)
#define    FOTA_MD_SKMETA_LENGTH                         (48U)
#define    FOTA_MD_HEADER_LENGTH                         (8U)
#define    FOTA_MAC_LENGTH                               (16U)
#define    FOTA_MD_DIGEST_LENGTH                         (32U)
#define    FOTA_DERIVEKEY_LENGTH                         (32U)
#define    FOTA_DEC_KEY_LENGTH                           (16U)
#define    FOTA_DEC_IV_LENGTH                            (16U)
#define    FOTA_SINGLE_TYPE                              (0U)
#define    FOTA_NON_MMU_TYPE                             (1U)
#define    FOTA_MMU_TYPE                                 (2U)

/* Number of Fota instances */
#define    FOTA_NUM_OF_SWUNIT                            (1U)

#define    FOTA_NUMBER_OF_BLOCK_0                        (5U)

#define    FOTA_NUM_OF_VERIFY_0                          (1U)
#define    FOTA_NUM_OF_FIRMWARE_BLOCK_0                  (2U)
#define    FOTA_NUM_OF_METADATA_BLOCK_0                  (1U)
#define    FOTA_NUM_OF_MAX_VERIFY                        (1U)
#define    FOTA_NO_OF_PRECALLOUT_0                       (0U)
#define    FOTA_NO_OF_POSTCALLOUT_0                      (0U)
#define    FOTA_NUM_OF_PROTECTED_BLOCK_0                 (0U)

#define    FOTA_MODE                                     FOTA_APP_MODE
#define    FOTA_IMPLEMENTATION_RULE                      FOTA_OTA_ES98765_01
#define    FOTA_MCU_MEMORY_ACCESS_TYPE                   FOTA_SINGLE_TYPE
#define    FOTA_CSM_SUPPORT                              FOTA_STD_ON
#define    FOTA_OTA_NON_MMU_USED                         FOTA_STD_OFF
#define    FOTA_METADATA_INFO_USED                       FOTA_STD_ON
#define    FOTA_FIRMWARE_INFO_USED                       FOTA_STD_ON
#define    FOTA_SF20_ENABLE                              FOTA_STD_ON
#define    FOTA_DECRYPTION_USING_CSM                     FOTA_STD_OFF
#define    FOTA_VERSION_INFO_API                         FOTA_STD_OFF
#define    FOTA_DEV_ERROR_DETECT                         FOTA_STD_ON
#define    FOTA_LARGE_SECTOR                             FOTA_STD_OFF
#define    FOTA_ARM_ARCHITECHTURE_MCU                    FOTA_STD_ON
#define    FOTA_BOOT_MANAGER_USED                        FOTA_STD_OFF
#define    FOTA_SOFTWARE_VERSION_CHECK                   FOTA_STD_OFF
#define    FOTA_USER_CALL_OUT_USED                       FOTA_STD_OFF
#define    FOTA_VERIFY_BUFFER_USED                       FOTA_STD_OFF
#define    FOTA_DOWN_GRADE_PROTECTION_USED               FOTA_STD_OFF

#define    FBL_STARTUP_COMMAND_VALUE                     (0xA5430911U)
#define    FBL_COMMON_RAM_ADDRESS                        (0x20400004U)
#define    FOTA_SECURITY_KEY_VALUE                       (0x90482442U)
#define    FBL_STARTUP_COMMAND_ADDRESS                   (0x20400000U)
#define    FOTA_CPD_KEY_VALUE                            (0x19801217U)
#define    FOTA_SVC_MAX_LENGTH_VERSION                   (0x7FU)
#define    SEC_SECURE_FLASH_HASH_ALGORITHM               (0xA5430911U)
#define    FOTA_TP_BLOCK_LENGTH                          (514U)

/*******************************************************************************
**                     Global Data Types                                      **
*******************************************************************************/


/*******************************************************************************
**                     Global Data                                            **
*******************************************************************************/



#endif /* FOTA_CFG_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
