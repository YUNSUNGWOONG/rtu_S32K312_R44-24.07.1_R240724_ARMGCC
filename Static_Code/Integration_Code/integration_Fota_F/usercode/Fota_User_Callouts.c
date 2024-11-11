/*******************************************************************************
**                                                                            **
**  (C) 2022 HYUNDAI AUTOEVER Co., Ltd.                                       **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE:                                                   **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : BOOTLOADER                                                    **
**                                                                            **
**  PURPOSE   :          **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                             Revision History                               **
********************************************************************************
** Revision  Date          By           Description                           **
********************************************************************************
** 1.0.2     10-Jan-2024   JYS         CP44-3725                              **
** 1.0.0     31-Oct-2023   Autoever    Initial Version                        **
*******************************************************************************/

/*******************************************************************************
**                              Include Section                               **
*******************************************************************************/
/* polyspace-begin MISRA-C3:20.9 [Justified:Low] "Not a defect" */
#include "Fota_User_Callouts.h"

#ifndef FOTA_INTEGRATION_SINGLEMEM_PLATFORM

#include "Std_Types.h"
#include "Fota_Globals.h"
#include "Fota_PflsInterface.h" /* for S32k3 SecureBoot */
#include "Fota_Verify.h"
#include "Csm.h"
#include "Fota_Cfg.h"
#include "Fota_IntFunc.h"
#include "Fota.h"
#if (FOTA_STD_ON == FOTA_SF20_ENABLE)
#include "Fota_Decrypt.h"
#include "HKMC_SecureFlash2.h"
#if (HWRESOURCE_VENDOR(HWRESOURCE_NXP))
#include "Crypto_Cfg.h"
#include "Crypto_Util.h"
#include "Crypto_ASRExtension.h"
#include "Hse_Ip.h"
#else
#include "Hsm_HostAPI.h"
#include "SecurityApp_SecureBoot.h"
#endif
#endif
#if HWRESOURCE_FAMILY(HWRESOURCE_SPC58XH)
#include "Mcu.h"
#include "Mcu_LLD.h"
#include "Mcu_MagicCarpet_LLD.h"
#endif

#include "Rte_Type.h"
#include "EcuM.h"
#include "Dcm.h"

#if ((HWRESOURCE_FAMILY(HWRESOURCE_CYT2BXX)) ||\
     (HWRESOURCE_FAMILY(HWRESOURCE_CYT3BXX)) ||\
     (HWRESOURCE_FAMILY(HWRESOURCE_CYT4BXX)) ||\
     (HWRESOURCE_FAMILY(HWRESOURCE_CYT6BXX)))
#include "arm_ghs.h"
#endif

#if ( HWRESOURCE_FAMILY(HWRESOURCE_TC33X) || HWRESOURCE_FAMILY(HWRESOURCE_TC35X) || HWRESOURCE_FAMILY(HWRESOURCE_TC36X) || \
      HWRESOURCE_FAMILY(HWRESOURCE_TC37X) || HWRESOURCE_FAMILY(HWRESOURCE_TC38X) || HWRESOURCE_FAMILY(HWRESOURCE_TC39X) )
#include "Mem_76_Pfls_Cfg.h"
#include "Mem_76_Pfls_Regs.h"
#endif

/*******************************************************************************
**                             Macro Definition                               **
*******************************************************************************/
#if (FOTA_STD_ON == FOTA_SF20_ENABLE)
  #if (HWRESOURCE_VENDOR(HWRESOURCE_NXP))
    #define HSE_TEST
    #define SEC_SF_PBKDF2_ENCRYPT_KEY                                           (CryptoConf_CryptoKey_PBKDF2_Encrypt_Key)                 /*Crypto_Cfh.h*/
    #define SEC_SF_PBKDF2_DECRYPT_KEY                                           (CryptoConf_CryptoKey_PBKDF2_Decrypt_Key)                 /*Crypto_Cfh.h*/
    #define SEC_SF_PBKDF2_SOURCE_KEY_PSK_OFFSET                                 (CryptoConf_CryptoKey_PBKDF2_Source_Key_PSK0)             /*Crypto_Cfh.h*/
    #define SEC_SF_PBKDF2_EXTRACTED_KEY                                         (CryptoConf_CryptoKey_PBKDF2_ExtractedKey)                /*Crypto_Cfh.h*/
    #define SEC_SF_PBKDF2_EXTRACTED_ELEMENT										(CryptoConf_CryptoKeyElement_PBKDF2_ExtractedKey)         /*Crypto_Cfh.h*/
    #define SEC_SF_PBKDF2_TARGET_KEY                                            (CryptoConf_CryptoKey_PBKDF2_Target_Key)                  /*Crypto_Cfh.h*/
    #define SEC_SF_PBKDF2_TARGET_ELEMENT										(CryptoConf_CryptoKeyElement_PBKDF2_Target_Key)           /*Crypto_Cfh.h*/
    #define SEC_SF_PBKDF2_DECRYPT_AES_ECB                                       0U
    #define KEY_SIZE	16U

    typedef struct
    {
        uint32 IVT_header;       /**< @brief IVT header marker */
        uint32 bootCfgWord;      /**< @brief Boot Configuration Word */
        uint32 reserved1;        /**< @brief 4 bytes reserved */
        uint32 pAppImg_addr_0;   /**< @brief Application address for Boot Target 0 */
        uint32 reserved2;        /**< @brief 4 bytes reserved */
        uint32 pAppImg_addr_1;   /**< @brief Application address for Boot Target 1 */
        uint32 reserved3;        /**< @brief 4 bytes reserved */
        uint32 pAppImg_addr_2;   /**< @brief Application address for Boot Target 2 */
        uint32 reserved4;        /**< @brief 4 bytes reserved */
        uint32 LCCfgWord;        /**< @brief Life-Cycle configuration word */
        uint32 cyrstalOscConfig; /**< @brief DEBUG Config */
        uint32 pHSE;             /**< @brief pointer to HSE image */
        uint32 reserved5[45];    /**< @brief 192 bytes reserved */
        uint32 GMAC[7];          /**< @brief GMAC TAG over the IVT image */
    } ivt_t;
	#define FOTA_HSE_CORE0_ID  ((hseAppCore_t)0U)
	/* List of identifiers for the MU instances */
	#define FOTA_HSE_MU0_INSTANCE                     ((uint8)0U)
	/* Identifier of the MU channel used by HSE to listen for administrative requests */
	#define FOTA_HSE_MU_CHANNEL                       ((uint8)1U)
	#define BOOT_SEQ_SHIFT                            ((uint8)3U)
	#define BOOT_SEQ_ENABLE                           ((uint8)1U)
	#define BOOT_SEQ_MASK                             ((uint8)8U)

	typedef enum
	{
	  FOTA_SECURE_BOOT_MAC_GENERATE      = 0U,
	  FOTA_SECURE_BOOT_TAG_WRITE         = 1U,
	  FOTA_SECURE_BOOT_TAG_WRITE_CHK     = 2U,
	  FOTA_SECURE_BOOT_INSTALL_SMR       = 3U,
	  FOTA_SECURE_BOOT_IVT_ERASE         = 4U,
	  FOTA_SECURE_BOOT_IVT_ERASE_CHK     = 5U,
	  FOTA_SECURE_BOOT_IVT_WRITE         = 6U,
	  FOTA_SECURE_BOOT_IVT_WRITE_CHK     = 7U,
	  FOTA_SECURE_BOOT_END               = 8U
	} Fota_MacUpdateStat;

  #endif
#endif

#if ((FOTA_SOFTWARE_VERSION_CHECK == STD_ON) &&\
  (FOTA_MCU_MEMORY_ACCESS_TYPE == FOTA_SINGLE_TYPE))
typedef enum
{
  FOTA_VERSION_CHECK_CALLOUT_EQUAL = 0,
  FOTA_VERSION_CHECK_CALLOUT_SMALLER,
  FOTA_VERSION_CHECK_CALLOUT_GREATER
} Fota_VersionCompareCallOutType;
#endif
/*******************************************************************************
**                            Global Data Types                               **
*******************************************************************************/

/*******************************************************************************
**                              Global Data                                            **
*******************************************************************************/

const uint8 Fota_MetadataBlock_Length_64[4] =
{ 0x00, 0x00, 0x00, 0x40 };

const uint8 Fota_MetadataBlock_Length_32[1] =
{ 0x38 };

const uint8 Fota_MetadataBlock_Delimiter[4] =
{ 0x3B, 0x49, 0x0C, 0x30 };

const uint8 Sec_Gau8_Signature_Length[4] =
{ 0x00, 0x00, 0x01, 0x00 };

const uint8 Sec_Gau8_Asims_Delimiter[FBL_SIGN_ASIMS_DELIMITER_NUM][4] =
{
  /* aSIMS Delimiter */
  {0x3B, 0x49, 0x21, 0x1B},

  {0x3B, 0x49, 0x1B, 0x21},

  {0x3B, 0x49, 0x22, 0x2B},

  {0x3B, 0x49, 0x2B, 0x22},

  {0x3B, 0x49, 0x23, 0x3B},

  {0x3B, 0x49, 0x3B, 0x23},

  {0x3B, 0x49, 0x24, 0x4B},

  {0x3B, 0x49, 0x4B, 0x24}
};

const uint8 Sec_Gau8_Fst_Delimiter[FBL_SIGN_FST_DELIMITER_NUM][4] =
{
  /* FST Delimiter */
  {0x3B, 0x49, 0x31, 0x1C},

  {0x3B, 0x49, 0x1C, 0x31},

  {0x3B, 0x49, 0x32, 0x2C},

  {0x3B, 0x49, 0x2C, 0x32},

  {0x3B, 0x49, 0x33, 0x3C},

  {0x3B, 0x49, 0x3C, 0x33},

  {0x3B, 0x49, 0x34, 0x4C},

  {0x3B, 0x49, 0x4C, 0x34},

  {0x3B, 0x49, 0x35, 0x5C},

  {0x3B, 0x49, 0x5C, 0x35}
};

/* ASIMs public key*/
const uint8 Fota_Sec_Gau8_ImageServPubKeyAsims[SEC_RSA_PUBLIC_KEY_MODULUS_LENGTH + 4U] = {
  0xB4U, 0xD0U, 0x84U, 0xE9U, 0x8CU, 0x88U, 0x50U, 0x7CU, 0x20U, 0x01U, 0x18U, 0x37U, 0xD8U, 0x43U, 0xC0U, 0xE4U,
  0xE1U, 0x0AU, 0x99U, 0xC7U, 0x52U, 0x20U, 0x28U, 0x3FU, 0xABU, 0x74U, 0x74U, 0xCDU, 0x87U, 0xBAU, 0x84U, 0xBFU,
  0xC2U, 0xE7U, 0xADU, 0x2CU, 0xB4U, 0xCCU, 0xF0U, 0xC3U, 0xABU, 0x1EU, 0x5CU, 0xEAU, 0x14U, 0x45U, 0x6BU, 0x8CU,
  0xDCU, 0xE7U, 0xCEU, 0xA1U, 0x1EU, 0x36U, 0xD9U, 0xE7U, 0xFDU, 0xA4U, 0x1AU, 0xD4U, 0x16U, 0x82U, 0xD3U, 0x47U,
  0xE8U, 0x5EU, 0xDBU, 0x9BU, 0x6DU, 0x00U, 0xFDU, 0xC8U, 0x15U, 0x14U, 0xB3U, 0xE8U, 0xB4U, 0x7EU, 0xECU, 0x2CU,
  0xFEU, 0xB7U, 0xFDU, 0x9FU, 0x30U, 0xBCU, 0x22U, 0x80U, 0x63U, 0xC2U, 0x40U, 0x7FU, 0x55U, 0x34U, 0x4BU, 0x04U,
  0x65U, 0xFFU, 0xD2U, 0x53U, 0xEFU, 0x89U, 0xBEU, 0xE3U, 0x5CU, 0xCBU, 0xA8U, 0x54U, 0x34U, 0xD5U, 0xB5U, 0xAAU,
  0x92U, 0x9AU, 0xB9U, 0x22U, 0x2EU, 0x67U, 0x3AU, 0xF4U, 0x2AU, 0x7FU, 0x48U, 0xA8U, 0xE5U, 0x88U, 0x85U, 0x07U,
  0x16U, 0xC4U, 0x37U, 0x4DU, 0xC3U, 0x51U, 0x2FU, 0x65U, 0x29U, 0x39U, 0xCEU, 0x3CU, 0x7BU, 0x0BU, 0x8CU, 0xE5U,
  0x50U, 0x15U, 0x3EU, 0xAEU, 0xEFU, 0xA3U, 0x0BU, 0xCEU, 0x18U, 0xF8U, 0x00U, 0x20U, 0x35U, 0xC6U, 0x37U, 0x78U,
  0x2EU, 0xA7U, 0x5CU, 0xDAU, 0x79U, 0x80U, 0xB5U, 0xB8U, 0x09U, 0xDFU, 0x1EU, 0x0FU, 0x0FU, 0xE4U, 0xC4U, 0x62U,
  0xA0U, 0x4EU, 0x6CU, 0x33U, 0x1CU, 0x07U, 0x2EU, 0x18U, 0x06U, 0x6EU, 0xE6U, 0x9EU, 0x23U, 0x89U, 0xEDU, 0x7AU,
  0x23U, 0x4AU, 0xC4U, 0xA1U, 0xA3U, 0xF5U, 0x11U, 0xCAU, 0x5DU, 0x84U, 0x13U, 0x9FU, 0xC2U, 0x63U, 0xB9U, 0x14U,
  0xFCU, 0x75U, 0x58U, 0x51U, 0x52U, 0xEDU, 0x77U, 0xF7U, 0xE1U, 0x3FU, 0x69U, 0xC1U, 0x72U, 0xEBU, 0xF1U, 0xD3U,
  0x3EU, 0x57U, 0x51U, 0x91U, 0xBCU, 0x19U, 0x13U, 0xA5U, 0x89U, 0xBAU, 0x0CU, 0x81U, 0x14U, 0x45U, 0xFFU, 0x77U,
  0x32U, 0xE3U, 0x44U, 0xC4U, 0x3BU, 0xF5U, 0x50U, 0x4CU, 0x48U, 0xE7U, 0x7BU, 0xF8U, 0xB2U, 0xA6U, 0xB5U, 0x9BU,

  0x01, 0x00, 0x01, 0x00
};

/* User must changes this to use FST public key*/
const uint8 Fota_Sec_Gau8_ImageServPubKeyFst[SEC_RSA_PUBLIC_KEY_MODULUS_LENGTH+4U] = {
  0xD6U, 0xE5U, 0xA8U, 0xD3U, 0x44U, 0x70U, 0x98U, 0xD3U, 0x44U, 0xBEU, 0x8EU, 0x7AU, 0x60U, 0x4BU, 0x96U, 0x2FU,
  0x14U, 0x89U, 0x4EU, 0x59U, 0xEBU, 0xCCU, 0xA7U, 0xC6U, 0x1CU, 0x2CU, 0x2BU, 0x1AU, 0x3CU, 0x1FU, 0x8EU, 0xB2U,
  0xCCU, 0xD7U, 0x67U, 0x5EU, 0x6DU, 0xF2U, 0x3CU, 0x20U, 0x5FU, 0xC9U, 0x78U, 0x81U, 0xBAU, 0x61U, 0xECU, 0x93U,
  0x14U, 0x85U, 0xB1U, 0x5AU, 0x01U, 0x96U, 0x7AU, 0xF9U, 0xE2U, 0xECU, 0xDDU, 0xEAU, 0x61U, 0x95U, 0x0BU, 0xF2U,
  0xD9U, 0x89U, 0xBDU, 0x3AU, 0x63U, 0xBEU, 0x44U, 0x98U, 0xC4U, 0xEDU, 0xA4U, 0xB5U, 0x34U, 0xDBU, 0x97U, 0x10U,
  0x89U, 0x3DU, 0x8BU, 0xDFU, 0x99U, 0xF1U, 0x32U, 0x9FU, 0x64U, 0x88U, 0xC5U, 0xCDU, 0x08U, 0xA9U, 0xC4U, 0xBDU,
  0x66U, 0x51U, 0xFBU, 0x81U, 0x7FU, 0x8AU, 0xE3U, 0xABU, 0x6AU, 0x83U, 0x59U, 0x7EU, 0xDDU, 0x88U, 0x69U, 0x8EU,
  0x88U, 0xBFU, 0x9AU, 0xF8U, 0x64U, 0xABU, 0x7DU, 0xD7U, 0xA5U, 0x82U, 0xF3U, 0x1BU, 0x05U, 0xDBU, 0x36U, 0x0FU,
  0x5AU, 0x83U, 0x9AU, 0xD3U, 0x70U, 0xE2U, 0x5BU, 0x9EU, 0x5FU, 0xBFU, 0x6AU, 0xC4U, 0x11U, 0xE6U, 0x09U, 0x8AU,
  0x06U, 0xB1U, 0x63U, 0x22U, 0xCBU, 0xF1U, 0x50U, 0xA4U, 0xADU, 0x2FU, 0x97U, 0x97U, 0xC0U, 0xF7U, 0x5EU, 0x94U,
  0x48U, 0x39U, 0x41U, 0x54U, 0x92U, 0x92U, 0xA8U, 0xCFU, 0xABU, 0xEEU, 0xE4U, 0x12U, 0x8AU, 0xF8U, 0xB3U, 0x7FU,
  0x0DU, 0xE5U, 0xBDU, 0x27U, 0x69U, 0xF1U, 0xF4U, 0x8BU, 0xBBU, 0x87U, 0xB0U, 0x1FU, 0x0DU, 0xCDU, 0x00U, 0x24U,
  0x5AU, 0x6DU, 0x36U, 0xE2U, 0xD5U, 0xB9U, 0xDFU, 0x42U, 0x80U, 0x47U, 0x0EU, 0x34U, 0x89U, 0x27U, 0xDFU, 0xB6U,
  0x02U, 0xF6U, 0x1DU, 0xE0U, 0x94U, 0x4DU, 0xDAU, 0x2AU, 0x40U, 0x85U, 0xACU, 0x66U, 0xE7U, 0x38U, 0x8CU, 0x3CU,
  0x69U, 0xA0U, 0xA4U, 0x9AU, 0xFCU, 0x96U, 0x1BU, 0x65U, 0x2BU, 0xBAU, 0xC6U, 0x45U, 0x54U, 0x67U, 0x1EU, 0xB9U,
  0xB8U, 0xDBU, 0x01U, 0x66U, 0x75U, 0xA4U, 0xC8U, 0xFEU, 0x3AU, 0x1BU, 0x7AU, 0x35U, 0xEDU, 0xB4U, 0x72U, 0xDDU,

  0x01, 0x00, 0x01, 0x00
};

const uint16 Fota_Gau16_CRCA001_8[256] = {
  0x0000, 0xC0C1, 0xC181, 0x0140, 0xC301, 0x03C0, 0x0280, 0xC241,
  0xC601, 0x06C0, 0x0780, 0xC741, 0x0500, 0xC5C1, 0xC481, 0x0440,
  0xCC01, 0x0CC0, 0x0D80, 0xCD41, 0x0F00, 0xCFC1, 0xCE81, 0x0E40,
  0x0A00, 0xCAC1, 0xCB81, 0x0B40, 0xC901, 0x09C0, 0x0880, 0xC841,
  0xD801, 0x18C0, 0x1980, 0xD941, 0x1B00, 0xDBC1, 0xDA81, 0x1A40,
  0x1E00, 0xDEC1, 0xDF81, 0x1F40, 0xDD01, 0x1DC0, 0x1C80, 0xDC41,
  0x1400, 0xD4C1, 0xD581, 0x1540, 0xD701, 0x17C0, 0x1680, 0xD641,
  0xD201, 0x12C0, 0x1380, 0xD341, 0x1100, 0xD1C1, 0xD081, 0x1040,
  0xF001, 0x30C0, 0x3180, 0xF141, 0x3300, 0xF3C1, 0xF281, 0x3240,
  0x3600, 0xF6C1, 0xF781, 0x3740, 0xF501, 0x35C0, 0x3480, 0xF441,
  0x3C00, 0xFCC1, 0xFD81, 0x3D40, 0xFF01, 0x3FC0, 0x3E80, 0xFE41,
  0xFA01, 0x3AC0, 0x3B80, 0xFB41, 0x3900, 0xF9C1, 0xF881, 0x3840,
  0x2800, 0xE8C1, 0xE981, 0x2940, 0xEB01, 0x2BC0, 0x2A80, 0xEA41,
  0xEE01, 0x2EC0, 0x2F80, 0xEF41, 0x2D00, 0xEDC1, 0xEC81, 0x2C40,
  0xE401, 0x24C0, 0x2580, 0xE541, 0x2700, 0xE7C1, 0xE681, 0x2640,
  0x2200, 0xE2C1, 0xE381, 0x2340, 0xE101, 0x21C0, 0x2080, 0xE041,
  0xA001, 0x60C0, 0x6180, 0xA141, 0x6300, 0xA3C1, 0xA281, 0x6240,
  0x6600, 0xA6C1, 0xA781, 0x6740, 0xA501, 0x65C0, 0x6480, 0xA441,
  0x6C00, 0xACC1, 0xAD81, 0x6D40, 0xAF01, 0x6FC0, 0x6E80, 0xAE41,
  0xAA01, 0x6AC0, 0x6B80, 0xAB41, 0x6900, 0xA9C1, 0xA881, 0x6840,
  0x7800, 0xB8C1, 0xB981, 0x7940, 0xBB01, 0x7BC0, 0x7A80, 0xBA41,
  0xBE01, 0x7EC0, 0x7F80, 0xBF41, 0x7D00, 0xBDC1, 0xBC81, 0x7C40,
  0xB401, 0x74C0, 0x7580, 0xB541, 0x7700, 0xB7C1, 0xB681, 0x7640,
  0x7200, 0xB2C1, 0xB381, 0x7340, 0xB101, 0x71C0, 0x7080, 0xB041,
  0x5000, 0x90C1, 0x9181, 0x5140, 0x9301, 0x53C0, 0x5280, 0x9241,
  0x9601, 0x56C0, 0x5780, 0x9741, 0x5500, 0x95C1, 0x9481, 0x5440,
  0x9C01, 0x5CC0, 0x5D80, 0x9D41, 0x5F00, 0x9FC1, 0x9E81, 0x5E40,
  0x5A00, 0x9AC1, 0x9B81, 0x5B40, 0x9901, 0x59C0, 0x5880, 0x9841,
  0x8801, 0x48C0, 0x4980, 0x8941, 0x4B00, 0x8BC1, 0x8A81, 0x4A40,
  0x4E00, 0x8EC1, 0x8F81, 0x4F40, 0x8D01, 0x4DC0, 0x4C80, 0x8C41,
  0x4400, 0x84C1, 0x8581, 0x4540, 0x8701, 0x47C0, 0x4680, 0x8641,
  0x8201, 0x42C0, 0x4380, 0x8341, 0x4100, 0x81C1, 0x8081, 0x4040
};

#if (FOTA_STD_ON == FOTA_SF20_ENABLE)
  #if (HWRESOURCE_VENDOR(HWRESOURCE_NXP))
    /* polyspace-begin MISRA-C3:8.9 [Justified:Low] "No Impact of this rule violation" */
    static uint8 test_flag;
    /* polyspace-end MISRA-C3:8.9 [Justified:Low] "No Impact of this rule violation" */

    static uint8 re_val[10]={0xFFu,0xFFu,0xFFu,0xFFu,0xFFu,0xFFu,0xFFu,0xFFu,0xFFu,0xFFu};

    static const uint8 FST_PSKKey[10][KEY_SIZE] =
    {
      {0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f},
      {0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x2e, 0x2f},
      {0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39, 0x3a, 0x3b, 0x3c, 0x3d, 0x3e, 0x3f},
      {0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4a, 0x4b, 0x4c, 0x4d, 0x4e, 0x4f},
      {0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5a, 0x5b, 0x5c, 0x5d, 0x5e, 0x5f},

      {0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6a, 0x6b, 0x6c, 0x6d, 0x6e, 0x6f},
      {0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, 0x78, 0x79, 0x7a, 0x7b, 0x7c, 0x7d, 0x7e, 0x7f},
      {0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f},
      {0x90, 0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x98, 0x99, 0x9a, 0x9b, 0x9c, 0x9d, 0x9e, 0x9f},
      {0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAa, 0xAb, 0xAc, 0xAd, 0xAe, 0xAf}
    };

    static const uint8 FST_PSKKey1[KEY_SIZE] =
    {
      0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f
    };

    static const uint8 AES_ECBKey[KEY_SIZE] =
    {
      0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f
    };

    static const uint8 Sha256_HMAC_Key[KEY_SIZE+KEY_SIZE] =
    {
      0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f,
      0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x2e, 0x2f
    };

	static hseSmrEntry_t smrEntry;
	static hseCrEntry_t crEntry;
	static ivt_t IVT;
	static hseSrvDescriptor_t	Fota_HseSrvDescriptor;
	static Hse_Ip_ReqType       Fota_HseIpRequest;
    static uint8 HmacTag[32];
    static uint8 Fota_IVTBuffer[8192];

  #endif
#endif

#if HWRESOURCE_FAMILY(HWRESOURCE_SPC58XH)
static VAR(boolean, AUTOMATIC) Fota_DestructiveResetEnable = FOTA_FALSE;
#endif

#if ((HWRESOURCE_MCU(HWRESOURCE_RH850F1K)) |\
     (HWRESOURCE_MCU(HWRESOURCE_RH850F1L)))
void WritetProtectRegister( uint32 *regadrr, uint32 value, uint32 *protadrr);
#endif
/*******************************************************************************
**                          Function Definitions                              **
*******************************************************************************/

#if (FOTA_STD_ON == FOTA_SF20_ENABLE)

  FUNC(Std_ReturnType, FOTA_CODE) Fota_DecryptStart_Callout
  (
    P2CONST(uint8, AUTOMATIC, FOTA_CODE) iv,
    P2CONST(uint8, AUTOMATIC, FOTA_CODE) firmwareKey,
    CONST(uint8, AUTOMATIC) firmwareKeyLen,
    P2CONST(uint8, AUTOMATIC, FOTA_CODE) macOfFirmwareKey,
    P2CONST(uint8, AUTOMATIC, FOTA_CODE) macKey,
    CONST(uint8, AUTOMATIC) macKeyLen
  )
  {
    Std_ReturnType retVal;

    if(RT_SUCCESS==SecureFlash_DecryptStart(iv, firmwareKey, \
                   firmwareKeyLen, macOfFirmwareKey, macKey, macKeyLen))
    {
		retVal=E_OK;
    }
	else
	{
		retVal=E_NOT_OK;
	}

    return retVal;
  }

  /* polyspace-begin MISRA-C3:8.13 [Justified:Low] "Not a defect" */
  FUNC(Std_ReturnType, FOTA_CODE) Fota_DecryptUpdate_Callout
  (
    P2VAR(uint8, AUTOMATIC, FOTA_CODE) output,
    P2CONST(uint8, AUTOMATIC, FOTA_CODE) input,
    CONST(uint32, AUTOMATIC) dataLen
  )
  /* polyspace-end MISRA-C3:8.13 [Justified:Low] "Not a defect" */
  {
    Std_ReturnType retVal;

    if(RT_SUCCESS==SecureFlash_DecryptUpdate(output, input, dataLen))
    {
		retVal=E_OK;
    }
	else
	{
		retVal=E_NOT_OK;
	}

    return retVal;
  }

  FUNC(Std_ReturnType, FOTA_CODE) Fota_DecryptFinish_Callout
  (
    P2VAR(uint32, AUTOMATIC, FOTA_CODE) totalLen
  )
  {
    Std_ReturnType retVal;

    if(RT_SUCCESS==SecureFlash_DecryptFinish(totalLen))
    {
		retVal=E_OK;
    }
	else
	{
		retVal=E_NOT_OK;
	}
    Fota_SecureFlashDecryptOn = FALSE;

    return retVal;
  }

  #if (HWRESOURCE_VENDOR(HWRESOURCE_NXP))
    FUNC(void, FOTA_CODE) Fota_S32k3_Hse_Psk_injection(void)
    {
    #if 1
      if(test_flag == 9)
      {
        (void)Crypto_Exts_FormatKeyCatalogs();  /* initial KeyCatalogs(RAM/NvM) */
        test_flag = 0;

        re_val[0] = Csm_KeyElementSet(\
          CryptoConf_CryptoKey_PBKDF2_Encrypt_Key,\
          CryptoConf_CryptoKeyElement_PBKDF2_Encrypt_Key,\
          AES_ECBKey,\
          KEY_SIZE);

        re_val[0] |= Csm_KeySetValid(CryptoConf_CryptoKey_PBKDF2_Encrypt_Key);

        re_val[0] |= Csm_KeyElementSet(\
          CryptoConf_CryptoKey_PBKDF2_Decrypt_Key,\
          CryptoConf_CryptoKeyElement_PBKDF2_Decrypt_Key,\
          AES_ECBKey,\
          KEY_SIZE);

        re_val[0] |= Csm_KeySetValid(CryptoConf_CryptoKey_PBKDF2_Decrypt_Key);

        re_val[0] |= Csm_KeyElementSet(\
            CryptoConf_CryptoKey_PBKDF2_Source_Key_PSK0,\
            CryptoConf_CryptoKeyElement_PBKDF2_Source_Key_PSK0,\
            &FST_PSKKey[0][0],\
            KEY_SIZE);
        re_val[0] |= Csm_KeySetValid(CryptoConf_CryptoKey_PBKDF2_Source_Key_PSK0);

        re_val[0] |= Csm_KeyElementSet(\
            CryptoConf_CryptoKey_PBKDF2_Source_Key_PSK1,\
            CryptoConf_CryptoKeyElement_PBKDF2_Source_Key_PSK1,\
            &FST_PSKKey[1][0],\
            KEY_SIZE);
        re_val[0] |= Csm_KeySetValid(CryptoConf_CryptoKey_PBKDF2_Source_Key_PSK1);

        re_val[0] |= Csm_KeyElementSet(\
            CryptoConf_CryptoKey_PBKDF2_Source_Key_PSK2,\
            CryptoConf_CryptoKeyElement_PBKDF2_Source_Key_PSK2,\
            &FST_PSKKey[2][0],\
            KEY_SIZE);
        re_val[0] |= Csm_KeySetValid(CryptoConf_CryptoKey_PBKDF2_Source_Key_PSK2);

        re_val[0] |= Csm_KeyElementSet(\
            CryptoConf_CryptoKey_PBKDF2_Source_Key_PSK3,\
            CryptoConf_CryptoKeyElement_PBKDF2_Source_Key_PSK3,\
            &FST_PSKKey[3][0],\
            KEY_SIZE);
        re_val[0] |= Csm_KeySetValid(CryptoConf_CryptoKey_PBKDF2_Source_Key_PSK3);

        re_val[0] |= Csm_KeyElementSet(\
            CryptoConf_CryptoKey_PBKDF2_Source_Key_PSK4,\
            CryptoConf_CryptoKeyElement_PBKDF2_Source_Key_PSK4,\
            &FST_PSKKey[4][0],\
            KEY_SIZE);
        re_val[0] |= Csm_KeySetValid(CryptoConf_CryptoKey_PBKDF2_Source_Key_PSK4);

        re_val[0] |= Csm_KeyElementSet(\
            CryptoConf_CryptoKey_PBKDF2_Source_Key_PSK5,\
            CryptoConf_CryptoKeyElement_PBKDF2_Source_Key_PSK5,\
            &FST_PSKKey[5][0],\
            KEY_SIZE);
        re_val[0] |= Csm_KeySetValid(CryptoConf_CryptoKey_PBKDF2_Source_Key_PSK5);

        re_val[0] |= Csm_KeyElementSet(\
            CryptoConf_CryptoKey_PBKDF2_Source_Key_PSK6,\
            CryptoConf_CryptoKeyElement_PBKDF2_Source_Key_PSK6,\
            &FST_PSKKey[6][0],\
            KEY_SIZE);
        re_val[0] |= Csm_KeySetValid(CryptoConf_CryptoKey_PBKDF2_Source_Key_PSK6);

        re_val[0] |= Csm_KeyElementSet(\
            CryptoConf_CryptoKey_PBKDF2_Source_Key_PSK7,\
            CryptoConf_CryptoKeyElement_PBKDF2_Source_Key_PSK7,\
            &FST_PSKKey[7][0],\
            KEY_SIZE);
        re_val[0] |= Csm_KeySetValid(CryptoConf_CryptoKey_PBKDF2_Source_Key_PSK7);

        re_val[0] |= Csm_KeyElementSet(\
            CryptoConf_CryptoKey_PBKDF2_Source_Key_PSK8,\
            CryptoConf_CryptoKeyElement_PBKDF2_Source_Key_PSK8,\
            &FST_PSKKey[8][0],\
            KEY_SIZE);
        re_val[0] |= Csm_KeySetValid(CryptoConf_CryptoKey_PBKDF2_Source_Key_PSK8);

        re_val[0] |= Csm_KeyElementSet(\
            CryptoConf_CryptoKey_PBKDF2_Source_Key_PSK9,\
            CryptoConf_CryptoKeyElement_PBKDF2_Source_Key_PSK9,\
            &FST_PSKKey[9][0],\
            KEY_SIZE);
        re_val[0] |= Csm_KeySetValid(CryptoConf_CryptoKey_PBKDF2_Source_Key_PSK9);

        /* for Secure Boot */
        re_val[0] = Csm_KeyElementSet(\
          CryptoConf_CryptoKey_MacGen_Sha256_HMAC_key,\
          CryptoConf_CryptoKeyElement_MacGen_Sha256_HMAC_key,\
          Sha256_HMAC_Key,\
          KEY_SIZE+KEY_SIZE);

        re_val[0] |= Csm_KeySetValid(CryptoConf_CryptoKey_MacGen_Sha256_HMAC_key);

        re_val[0] = Csm_KeyElementSet(\
          CryptoConf_CryptoKey_MacVer_Sha256_HMAC_key,\
          CryptoConf_CryptoKeyElement_MacVer_Sha256_HMAC_key,\
          Sha256_HMAC_Key,\
          KEY_SIZE+KEY_SIZE);

        re_val[0] |= Csm_KeySetValid(CryptoConf_CryptoKey_MacVer_Sha256_HMAC_key);
      }
    #endif
    }

#if 0 /* example */
    FUNC(Std_ReturnType, FOTA_CODE) Fota_S32k3_SecureBootEnable(void)
    {
	  VAR(Std_ReturnType, AUTOMATIC) retVal;
	  VAR(uint32,AUTOMATIC)         ElementIndex = 0; /* Temparary value for Crypto Defect */
	  VAR(uint8,AUTOMATIC)          EcuSwUnitIdx;
	  Crypto_VerifyResultType       verifyPtr;
	  hseMacScheme_t                macScheme;
	  hseMacSrv_t                   *pMacSrv;
	  hseSmrVerifySrv_t		        *pSmrVerifySrv;
	  hseSmrEntryInstallSrv_t       *pSmrEntryInstall;
	  hseCrEntryInstallSrv_t	    *pCrEntryInstallSrv;
	  hseAttrSmrCoreStatus_t	    smrCoreStatus_Get;
	  hseSrvResponse_t              hseRequestResult;
	  VAR(uint32,AUTOMATIC)         HmacTagLength=32UL;

	  retVal = E_NOT_OK;

	  EcuSwUnitIdx=Fota_FindSoftwareArea(FOTA_FBL_TYPE);
	  if (FOTA_INVALID_INDEX != EcuSwUnitIdx)
	  {
	    /* Steps for configuring secure boot is as followed. */
	    /* 1)copy IVT of length 256B from BLOCK0 section to data flash section */
	    FOTA_MEMCPY((void *)&IVT,
	    			(const void *)Fota_Gast_SwUnitTable[EcuSwUnitIdx].StartAddress,
	    			sizeof(ivt_t));

		if(BOOT_SEQ_ENABLE!=((IVT.bootCfgWord >> BOOT_SEQ_SHIFT) & BOOT_SEQ_ENABLE))
		{
		  (void)Csm_KeySetValid(CryptoConf_CryptoKey_MacVer_Sha256_HMAC_key);
		  /* polyspace-begin DEFECT:OUT_BOUND_ARRAY, CERT-C:ARR30-C, MISRA-C3:18.1 [Justified:High] "It gets array index in range" */
		  ElementIndex = Crypto_Util_GetKeyElementIdx (Crypto_Util_GetKeyIdx(CryptoConf_CryptoKey_MacVer_Sha256_HMAC_key), CryptoConf_CryptoKeyElement_MacVer_Sha256_HMAC_key);
		  *Crypto_aKeyElementList[ElementIndex].pu32CryptoElementActualSize = 32U;
		  /* polyspace-end DEFECT:OUT_BOUND_ARRAY, CERT-C:ARR30-C, MISRA-C3:18.1 [Justified:High] "It gets array index in range" */

		  (void)Fota_GetMemInstanceBySwUnit(EcuSwUnitIdx, &Fota_MemoryInstance);
		  (void)Fota_PflsGetFlashAlignment(Fota_MemoryInstance, &Fota_PflsWriteAlignmentValue);
		  Fota_PflsGetSectorSize(Fota_MemoryInstance, &Fota_PflsEraseAlignmentValue, Fota_Gast_SwUnitTable[EcuSwUnitIdx].StartAddress);

	      /*
	       * 2)copy start address of app from IVT in local variable.
	       *	 In case of SHE secure boot, SMR#0 shall be configured so app address
	       *	 is copied in local variable.
	       */
	      smrEntry.pSmrSrc = IVT.pAppImg_addr_0;              /* Start of APP code, pointing to active partition */
	      smrEntry.smrSize = 0x4FC00UL;                       /* 0x44FFFF(End) - 0x400000(Start) - 0x100(IVT) - 0x300(Tag) + 1 */
	      smrEntry.authKeyHandle = Crypto_aKeyElementList[ElementIndex].u32HseKeyHandle;
	      smrEntry.authScheme.macScheme.macAlgo = HSE_MAC_ALGO_HMAC;
	      smrEntry.authScheme.macScheme.sch.hmac.hashAlgo = HSE_HASH_ALGO_SHA2_256;
	      smrEntry.pInstAuthTag[0] = Fota_Gast_SwUnitTable[EcuSwUnitIdx].StartAddress + sizeof(ivt_t);      /* signature tag address, pointing to active partition */
	      smrEntry.pInstAuthTag[1] = (uint32)NULL;            /* In this example, AES keys is used hence 2nd tag address is NULL */

	      /* 3)Configure CR entry */
	      crEntry.coreId = FOTA_HSE_CORE0_ID;                 /* Define the behavior for core 0 - M33_0, core 1 - M33_1 */
	      crEntry.preBootSmrMap = (uint32)FOTA_TRUE;          /* Tie it to the verification of SMR defined above (index 0) */
	      crEntry.pPassReset = IVT.pAppImg_addr_0;            /* Entry point - address of the first instruction */
	      crEntry.crSanction = HSE_CR_SANCTION_DIS_ALL_KEYS;  /* Sanction in case SMR verification fails - keep core in reset */
	      crEntry.altPreBootSmrMap = 0x0UL;                   /* Not used here - configuration in case boot fails */
	      crEntry.pAltReset = IVT.pAppImg_addr_0;             /* Alternate Reset should not be NULL or 0xFFFFFFFF */
	      crEntry.startOption = HSE_CR_AUTO_START;

	      /* Sync */
	      Fota_HseIpRequest.eReqType   = HSE_IP_REQTYPE_SYNC;
	      Fota_HseIpRequest.u32Timeout = 5000000U; //for HSE_IP_REQTYPE_SYNC

		  /*
		   * 4) Generate and verify the tag so as to confirm
		   * that application is verified for secure boot
		   */
		  (void)Csm_KeySetValid(CryptoConf_CryptoKey_MacGen_Sha256_HMAC_key);
		  /* polyspace-begin DEFECT:OUT_BOUND_ARRAY, CERT-C:ARR30-C, MISRA-C3:18.1 [Justified:High] "It gets array index in range" */
		  ElementIndex = Crypto_Util_GetKeyElementIdx (Crypto_Util_GetKeyIdx(CryptoConf_CryptoKey_MacGen_Sha256_HMAC_key), CryptoConf_CryptoKeyElement_MacGen_Sha256_HMAC_key);
		  *Crypto_aKeyElementList[ElementIndex].pu32CryptoElementActualSize = 32U;
		  /* polyspace-end DEFECT:OUT_BOUND_ARRAY, CERT-C:ARR30-C, MISRA-C3:18.1 [Justified:High] "It gets array index in range" */

		  macScheme.macAlgo = HSE_MAC_ALGO_HMAC;
		  macScheme.sch.hmac.hashAlgo = HSE_HASH_ALGO_SHA2_256;
		  /* Fill the descriptor for the HSE request */
		  FOTA_MEMSET(&Fota_HseSrvDescriptor, 0, sizeof(hseSrvDescriptor_t));
		  Fota_HseSrvDescriptor.srvId  = HSE_SRV_ID_MAC;
		  pMacSrv = &(Fota_HseSrvDescriptor.hseSrv.macReq);

		  pMacSrv->accessMode = HSE_ACCESS_MODE_ONE_PASS;
		  pMacSrv->streamId = 0u;
		  pMacSrv->macScheme = macScheme;
		  pMacSrv->authDir = HSE_AUTH_DIR_GENERATE;
		  pMacSrv->keyHandle = Crypto_aKeyElementList[ElementIndex].u32HseKeyHandle;
		  pMacSrv->inputLength = smrEntry.smrSize;
		  pMacSrv->pInput = (HOST_ADDR)IVT.pAppImg_addr_0;
		  pMacSrv->pTagLength = (HOST_ADDR)&HmacTagLength;
		  pMacSrv->pTag = (HOST_ADDR)HmacTag;
		  pMacSrv->sgtOption = HSE_SGT_OPTION_NONE;

		  hseRequestResult = Hse_Ip_ServiceRequest(FOTA_HSE_MU0_INSTANCE, FOTA_HSE_MU_CHANNEL,
                                                   &Fota_HseIpRequest, &Fota_HseSrvDescriptor);

		  if(HSE_SRV_RSP_OK != hseRequestResult)
		  {
		    retVal|=E_NOT_OK;
		  }

		  macScheme.macAlgo = HSE_MAC_ALGO_HMAC;
		  macScheme.sch.hmac.hashAlgo = HSE_HASH_ALGO_SHA2_256;
		  /* Fill the descriptor for the HSE request */
		  FOTA_MEMSET(&Fota_HseSrvDescriptor, 0, sizeof(hseSrvDescriptor_t));
		  Fota_HseSrvDescriptor.srvId  = HSE_SRV_ID_MAC;
		  pMacSrv = &(Fota_HseSrvDescriptor.hseSrv.macReq);

		  pMacSrv->accessMode = HSE_ACCESS_MODE_ONE_PASS;
		  pMacSrv->streamId = 0u;
		  pMacSrv->macScheme = macScheme;
		  pMacSrv->authDir = HSE_AUTH_DIR_VERIFY;
		  pMacSrv->keyHandle = smrEntry.authKeyHandle;
		  pMacSrv->inputLength = smrEntry.smrSize;
		  pMacSrv->pInput = (HOST_ADDR)IVT.pAppImg_addr_0;
		  pMacSrv->pTagLength = (HOST_ADDR)&HmacTagLength;
		  pMacSrv->pTag = (HOST_ADDR)smrEntry.pInstAuthTag[0];
		  pMacSrv->sgtOption = HSE_SGT_OPTION_NONE;

		  hseRequestResult = Hse_Ip_ServiceRequest(FOTA_HSE_MU0_INSTANCE, FOTA_HSE_MU_CHANNEL,
                                                   &Fota_HseIpRequest, &Fota_HseSrvDescriptor);

		  if(HSE_SRV_RSP_OK != hseRequestResult)
		  {
		    retVal|=E_NOT_OK;
		  }

		  /* Tag Flash */
		  retVal|=Fota_PflsWriteRequest(Fota_MemoryInstance, \
                                        smrEntry.pInstAuthTag[0], \
                                        HmacTag, \
                                        HmacTagLength);
		  do
		  {
		  }while(MEM_JOB_PENDING==Fota_PflsGetJobResult(Fota_MemoryInstance));

          /* 5) Finally, install SMR and CR entry and verify SMR install */
          /* Clear the service descriptor placed in shared memory */
		  FOTA_MEMSET(&Fota_HseSrvDescriptor, 0, sizeof(hseSrvDescriptor_t));
          pSmrEntryInstall = &(Fota_HseSrvDescriptor.hseSrv.smrEntryInstallReq);

          /* Fill the service descriptor */
          Fota_HseSrvDescriptor.srvId = HSE_SRV_ID_SMR_ENTRY_INSTALL;
          pSmrEntryInstall->accessMode = HSE_ACCESS_MODE_ONE_PASS;
          pSmrEntryInstall->entryIndex = 0u;
          pSmrEntryInstall->pSmrEntry = (HOST_ADDR)&smrEntry;

          pSmrEntryInstall->pSmrData = (HOST_ADDR)IVT.pAppImg_addr_0;           /* pointing to active partition */
          pSmrEntryInstall->smrDataLength = smrEntry.smrSize;
          pSmrEntryInstall->pAuthTag[0] = (HOST_ADDR)smrEntry.pInstAuthTag[0];  /* pointing to passive partition */
          pSmrEntryInstall->pAuthTag[1] = (HOST_ADDR)smrEntry.pInstAuthTag[1];  /* pointing to passive partition */
          pSmrEntryInstall->authTagLength[0] = HmacTagLength;
          pSmrEntryInstall->authTagLength[1] = HmacTagLength;

		  hseRequestResult = Hse_Ip_ServiceRequest(FOTA_HSE_MU0_INSTANCE, FOTA_HSE_MU_CHANNEL,
                                                 &Fota_HseIpRequest, &Fota_HseSrvDescriptor);

		  if(HSE_SRV_RSP_OK != hseRequestResult)
		  {
		    retVal|=E_NOT_OK;
		  }

		  /* verify SMR entry - SMR verify is not allowed for SHE boot,
		     only on next cycle could it be verified if BOOT_SEQ=0 */
		  FOTA_MEMSET(&Fota_HseSrvDescriptor, 0, sizeof(hseSrvDescriptor_t));
		  pSmrVerifySrv = &(Fota_HseSrvDescriptor.hseSrv.smrVerifyReq);

		  Fota_HseSrvDescriptor.srvId = HSE_SRV_ID_SMR_VERIFY;
		  pSmrVerifySrv->entryIndex = 0u;

		  hseRequestResult = Hse_Ip_ServiceRequest(FOTA_HSE_MU0_INSTANCE, FOTA_HSE_MU_CHANNEL,
                                                   &Fota_HseIpRequest, &Fota_HseSrvDescriptor);

		  if(HSE_SRV_RSP_OK != hseRequestResult)
		  {
		    retVal|=E_NOT_OK;
		  }

		  /* Install CR Entry */
		  /* Clear the service descriptor placed in shared memory */
		  FOTA_MEMSET(&Fota_HseSrvDescriptor, 0, sizeof(hseSrvDescriptor_t));
          pCrEntryInstallSrv = &(Fota_HseSrvDescriptor.hseSrv.smrEntryInstallReq);

		  /* Fill the service descriptor */
		  Fota_HseSrvDescriptor.srvId = HSE_SRV_ID_CORE_RESET_ENTRY_INSTALL;
		  pCrEntryInstallSrv->crEntryIndex = 0u;
		  pCrEntryInstallSrv->pCrEntry = (HOST_ADDR)&crEntry;

		  hseRequestResult = Hse_Ip_ServiceRequest(FOTA_HSE_MU0_INSTANCE, FOTA_HSE_MU_CHANNEL,
                                                 &Fota_HseIpRequest, &Fota_HseSrvDescriptor);

		  if(HSE_SRV_RSP_OK != hseRequestResult)
		  {
		    retVal|=E_NOT_OK;
		  }

		  /* verify if secure boot is success */
		  FOTA_MEMSET(&Fota_HseSrvDescriptor, 0, sizeof(hseSrvDescriptor_t));

		  Fota_HseSrvDescriptor.srvId = HSE_SRV_ID_GET_ATTR;
		  Fota_HseSrvDescriptor.hseSrv.getAttrReq.attrId = HSE_SMR_CORE_BOOT_STATUS_ATTR_ID;
		  Fota_HseSrvDescriptor.hseSrv.getAttrReq.attrLen = sizeof(hseAttrSmrCoreStatus_t);
		  Fota_HseSrvDescriptor.hseSrv.getAttrReq.pAttr = (HOST_ADDR)&smrCoreStatus_Get;

		  hseRequestResult = Hse_Ip_ServiceRequest(FOTA_HSE_MU0_INSTANCE, FOTA_HSE_MU_CHANNEL,
                                                 &Fota_HseIpRequest, &Fota_HseSrvDescriptor);

		  if(HSE_SRV_RSP_OK != hseRequestResult)
		  {
		    retVal|=E_NOT_OK;
		  }
	    }

		if(HSE_SRV_RSP_OK == hseRequestResult)
		{
		  retVal=E_OK;

		  /* BOOT_SEQ Enable */
	      FOTA_MEMCPY((void *)Fota_IVTBuffer,
                      (const void *)Fota_Gast_SwUnitTable[EcuSwUnitIdx].StartAddress,
                      Fota_PflsEraseAlignmentValue);

		  /* IVT area erase */
		  retVal|=Fota_PflsEraseRequest(Fota_MemoryInstance, \
                                        Fota_Gast_SwUnitTable[EcuSwUnitIdx].StartAddress, \
                                        Fota_PflsEraseAlignmentValue);
		  do
		  {
		  }while(MEM_JOB_PENDING==Fota_PflsGetJobResult(Fota_MemoryInstance));

		  Fota_IVTBuffer[FOTA_FOUR] |= BOOT_SEQ_MASK; /* 4~7: Boot configuration word */

		  retVal|=Fota_PflsWriteRequest(Fota_MemoryInstance, \
                                        Fota_Gast_SwUnitTable[EcuSwUnitIdx].StartAddress, \
                                        Fota_IVTBuffer, \
                                        Fota_PflsEraseAlignmentValue);
		  do
		  {
		  }while(MEM_JOB_PENDING==Fota_PflsGetJobResult(Fota_MemoryInstance));

          #if(FOTA_MCU_MEMORY_ACCESS_TYPE==FOTA_MMU_TYPE) /* MMU TYPE */
		  /* passive partition BOOT_SEQ Enable */
          (void)Fota_PflsTgtAreaSet(Fota_MemoryInstance,FOTA_ALT_ADDR);

		  /* IVT area erase */
		  retVal|=Fota_PflsEraseRequest(Fota_MemoryInstance, \
                                        Fota_Gast_SwUnitTable[EcuSwUnitIdx].StartAddress, \
                                        Fota_PflsEraseAlignmentValue);
		  do
		  {
		  }while(MEM_JOB_PENDING==Fota_PflsGetJobResult(Fota_MemoryInstance));

		  retVal|=Fota_PflsWriteRequest(Fota_MemoryInstance, \
                                        Fota_Gast_SwUnitTable[EcuSwUnitIdx].StartAddress, \
                                        Fota_IVTBuffer, \
                                        Fota_PflsEraseAlignmentValue);
		  do
		  {
		  }while(MEM_JOB_PENDING==Fota_PflsGetJobResult(Fota_MemoryInstance));
          #endif
		}
	  }

	  return retVal;
    }
#endif

    FUNC(Fota_JobResultType_CallOut, FOTA_CODE) Fota_S32k3_SecureBootProcess(void)
    {
	  Fota_JobResultType_CallOut secureBootProcessResult=FOTA_JOB_FAILED_CALL_OUT;
	  VAR(Fota_JobResultType_CallOut, AUTOMATIC) memJobResult;
	  static Fota_MacUpdateStat macUpdateStat=FOTA_SECURE_BOOT_MAC_GENERATE;
	  VAR(Std_ReturnType, AUTOMATIC) retVal=E_OK;
	  VAR(uint32,AUTOMATIC)         ElementIndex = 0; /* Temparary value for Crypto Defect */
	  static VAR(uint8,AUTOMATIC)   EcuSwUnitIdx;
	  static VAR(uint32,AUTOMATIC)  TgtAreaAddr;
	  VAR(uint32,AUTOMATIC)         TgtAreaSize;
	  static VAR(uint32,AUTOMATIC)  SignatureTagAddr;
	  VAR(uint32,AUTOMATIC)         SignatureTagSize;
	  VAR(uint32,AUTOMATIC)         TgtStartAddr;
	  VAR(uint32,AUTOMATIC)         TgtStartSize;
	  hseMacScheme_t                macScheme;
	  hseMacSrv_t                   *pMacSrv;
	  hseSmrVerifySrv_t		        *pSmrVerifySrv;
	  hseSmrEntryInstallSrv_t       *pSmrEntryInstall;
	  hseCrEntryInstallSrv_t	    *pCrEntryInstallSrv;
	  hseAttrSmrCoreStatus_t	    smrCoreStatus_Get;
	  hseSrvResponse_t              hseRequestResult;
	  VAR(uint32,AUTOMATIC)         HmacTagLength=32UL;

	  /* polyspace-begin CERT-C:INT36-C, MISRA-C3:10.5,11.4 [Justified:Low] "No Impact of this rule violation" */
	  EcuSwUnitIdx=Fota_FindSoftwareArea(FOTA_FBL_TYPE);
	  if (FOTA_INVALID_INDEX != EcuSwUnitIdx)
	  {
	    switch(macUpdateStat)
	    {
		  case FOTA_SECURE_BOOT_MAC_GENERATE:
		    /* Steps for configuring secure boot is as followed. */
		    /* 1)copy IVT of length 256B from BLOCK0 section to data flash section */
		    FOTA_MEMCPY((void *)&IVT,
		    			(const void *)Fota_Gast_SwUnitTable[EcuSwUnitIdx].StartAddress,
		    			sizeof(ivt_t));

			if(BOOT_SEQ_ENABLE==((IVT.bootCfgWord >> BOOT_SEQ_SHIFT) & BOOT_SEQ_ENABLE))
			{
			  (void)Csm_KeySetValid(CryptoConf_CryptoKey_MacVer_Sha256_HMAC_key);
			  /* polyspace-begin DEFECT:OUT_BOUND_ARRAY, CERT-C:ARR30-C, MISRA-C3:18.1 [Justified:High] "It gets array index in range" */
			  ElementIndex = Crypto_Util_GetKeyElementIdx (Crypto_Util_GetKeyIdx(CryptoConf_CryptoKey_MacVer_Sha256_HMAC_key), CryptoConf_CryptoKeyElement_MacVer_Sha256_HMAC_key);
			  *Crypto_aKeyElementList[ElementIndex].pu32CryptoElementActualSize = 32U;
			  /* polyspace-end DEFECT:OUT_BOUND_ARRAY, CERT-C:ARR30-C, MISRA-C3:18.1 [Justified:High] "It gets array index in range" */

			  (void)Fota_GetMemInstanceBySwUnit(EcuSwUnitIdx, &Fota_MemoryInstance);
			  (void)Fota_PflsGetFlashAlignment(Fota_MemoryInstance, &Fota_PflsWriteAlignmentValue);
			  (void)Fota_PflsGetSectorSize(Fota_MemoryInstance, &Fota_PflsEraseAlignmentValue, Fota_Gast_SwUnitTable[EcuSwUnitIdx].StartAddress);
			  SignatureTagAddr=Fota_Gast_SwUnitTable[EcuSwUnitIdx].StartAddress + sizeof(ivt_t);

		      /*
		       * 2)copy start address of app from IVT in local variable.
		       *	 In case of SHE secure boot, SMR#0 shall be configured so app address
		       *	 is copied in local variable.
		       */
		      smrEntry.pSmrSrc = IVT.pAppImg_addr_0;              /* Start of APP code, pointing to active partition */
		      smrEntry.smrSize = 0x4FC00UL;                       /* 0x44FFFF(End) - 0x400000(Start) - 0x100(IVT) - 0x300(Tag) + 1 */
		      smrEntry.authKeyHandle = Crypto_aKeyElementList[ElementIndex].u32HseKeyHandle;
		      smrEntry.authScheme.macScheme.macAlgo = HSE_MAC_ALGO_HMAC;
		      smrEntry.authScheme.macScheme.sch.hmac.hashAlgo = HSE_HASH_ALGO_SHA2_256;
		      smrEntry.pInstAuthTag[0] = SignatureTagAddr;        /* signature tag address, pointing to active partition */
		      smrEntry.pInstAuthTag[1] = (uint32)NULL;            /* In this example, AES keys is used hence 2nd tag address is NULL */

		      /* 3)Configure CR entry */
		      crEntry.coreId = FOTA_HSE_CORE0_ID;                 /* Define the behavior for core 0 - M33_0, core 1 - M33_1 */
		      crEntry.preBootSmrMap = (uint32)FOTA_TRUE;          /* Tie it to the verification of SMR defined above (index 0) */
		      crEntry.pPassReset = IVT.pAppImg_addr_0;            /* Entry point - address of the first instruction */
		      crEntry.crSanction = HSE_CR_SANCTION_DIS_ALL_KEYS;  /* Sanction in case SMR verification fails - keep core in reset */
		      crEntry.altPreBootSmrMap = 0x0UL;                   /* Not used here - configuration in case boot fails */
		      crEntry.pAltReset = IVT.pAppImg_addr_0;             /* Alternate Reset should not be NULL or 0xFFFFFFFF */
		      crEntry.startOption = HSE_CR_AUTO_START;

		      /* Sync */
		      Fota_HseIpRequest.eReqType   = HSE_IP_REQTYPE_SYNC;
		      Fota_HseIpRequest.u32Timeout = 5000000U; //for HSE_IP_REQTYPE_SYNC

			  /*
			   * 4) Generate and verify the tag so as to confirm
			   * that application is verified for secure boot
			   */
			  (void)Csm_KeySetValid(CryptoConf_CryptoKey_MacGen_Sha256_HMAC_key);
			  /* polyspace-begin DEFECT:OUT_BOUND_ARRAY, CERT-C:ARR30-C, MISRA-C3:18.1 [Justified:High] "It gets array index in range" */
			  ElementIndex = Crypto_Util_GetKeyElementIdx (Crypto_Util_GetKeyIdx(CryptoConf_CryptoKey_MacGen_Sha256_HMAC_key), CryptoConf_CryptoKeyElement_MacGen_Sha256_HMAC_key);
			  *Crypto_aKeyElementList[ElementIndex].pu32CryptoElementActualSize = 32U;
			  /* polyspace-end DEFECT:OUT_BOUND_ARRAY, CERT-C:ARR30-C, MISRA-C3:18.1 [Justified:High] "It gets array index in range" */

			  TgtAreaAddr=IVT.pAppImg_addr_0;

			  #if(FOTA_MCU_MEMORY_ACCESS_TYPE==FOTA_MMU_TYPE) /* MMU TYPE */
			  /* polyspace-begin CERT-C:EXP39-C [Justified:Low] "This conversion is used for OSS. they are same type" */
			  (void)Fota_PflsGetCovAddr(Fota_MemoryInstance, \
	                                    FOTA_ALT_ADDR, \
	                                    &TgtAreaAddr, \
	                                    &TgtAreaSize);
			  /* polyspace-end CERT-C:EXP39-C [Justified:Low] "This conversion is used for OSS. they are same type" */
			  #endif

			  macScheme.macAlgo = HSE_MAC_ALGO_HMAC;
			  macScheme.sch.hmac.hashAlgo = HSE_HASH_ALGO_SHA2_256;
			  /* Fill the descriptor for the HSE request */
			  FOTA_MEMSET(&Fota_HseSrvDescriptor, 0, sizeof(hseSrvDescriptor_t));
			  Fota_HseSrvDescriptor.srvId  = HSE_SRV_ID_MAC;
			  pMacSrv = &(Fota_HseSrvDescriptor.hseSrv.macReq);

			  pMacSrv->accessMode = HSE_ACCESS_MODE_ONE_PASS;
			  pMacSrv->streamId = 0u;
			  pMacSrv->macScheme = macScheme;
			  pMacSrv->authDir = HSE_AUTH_DIR_GENERATE;
			  pMacSrv->keyHandle = Crypto_aKeyElementList[ElementIndex].u32HseKeyHandle;
			  pMacSrv->inputLength = smrEntry.smrSize;
			  pMacSrv->pInput = (HOST_ADDR)TgtAreaAddr;
			  pMacSrv->pTagLength = (HOST_ADDR)&HmacTagLength;
			  pMacSrv->pTag = (HOST_ADDR)HmacTag;
			  pMacSrv->sgtOption = HSE_SGT_OPTION_NONE;

			  hseRequestResult = Hse_Ip_ServiceRequest(FOTA_HSE_MU0_INSTANCE, FOTA_HSE_MU_CHANNEL,
	                                                   &Fota_HseIpRequest, &Fota_HseSrvDescriptor);
			  if(HSE_SRV_RSP_OK != hseRequestResult)
			  {
				retVal|=(Std_ReturnType)E_NOT_OK;
			  }

			  macScheme.macAlgo = HSE_MAC_ALGO_HMAC;
			  macScheme.sch.hmac.hashAlgo = HSE_HASH_ALGO_SHA2_256;
			  /* Fill the descriptor for the HSE request */
			  FOTA_MEMSET(&Fota_HseSrvDescriptor, 0, sizeof(hseSrvDescriptor_t));
			  Fota_HseSrvDescriptor.srvId  = HSE_SRV_ID_MAC;
			  pMacSrv = &(Fota_HseSrvDescriptor.hseSrv.macReq);

			  pMacSrv->accessMode = HSE_ACCESS_MODE_ONE_PASS;
			  pMacSrv->streamId = 0u;
			  pMacSrv->macScheme = macScheme;
			  pMacSrv->authDir = HSE_AUTH_DIR_VERIFY;
			  pMacSrv->keyHandle = smrEntry.authKeyHandle;
			  pMacSrv->inputLength = smrEntry.smrSize;
			  pMacSrv->pInput = (HOST_ADDR)TgtAreaAddr;
			  pMacSrv->pTagLength = (HOST_ADDR)&HmacTagLength;
			  pMacSrv->pTag = (HOST_ADDR)HmacTag;
			  pMacSrv->sgtOption = HSE_SGT_OPTION_NONE;

			  hseRequestResult = Hse_Ip_ServiceRequest(FOTA_HSE_MU0_INSTANCE, FOTA_HSE_MU_CHANNEL,
	                                                   &Fota_HseIpRequest, &Fota_HseSrvDescriptor);
			  if(HSE_SRV_RSP_OK != hseRequestResult)
			  {
				retVal|=(Std_ReturnType)E_NOT_OK;
			  }

			  if(E_OK==retVal)
			  {
				secureBootProcessResult=FOTA_JOB_PENDING_CALL_OUT;
			  	macUpdateStat=FOTA_SECURE_BOOT_TAG_WRITE;
			  }
			  else
			  {
				secureBootProcessResult=FOTA_JOB_FAILED_CALL_OUT;
			  	macUpdateStat=FOTA_SECURE_BOOT_MAC_GENERATE;
			  }
			}
			else
			{
			  secureBootProcessResult=FOTA_JOB_OK_CALL_OUT;
			}

			break;

		  case FOTA_SECURE_BOOT_TAG_WRITE:
			/* Tag Flash */
			#if(FOTA_MCU_MEMORY_ACCESS_TYPE==FOTA_MMU_TYPE) /* MMU TYPE */
	        (void)Fota_PflsTgtAreaSet(Fota_MemoryInstance,FOTA_ALT_ADDR);
			#endif

			retVal=Fota_PflsWriteRequest(Fota_MemoryInstance, \
	                                     SignatureTagAddr, \
	                                     HmacTag, \
	                                     HmacTagLength);
			if(E_OK==retVal)
			{
			  secureBootProcessResult=FOTA_JOB_PENDING_CALL_OUT;
			  macUpdateStat=FOTA_SECURE_BOOT_TAG_WRITE_CHK;
			}
			else
			{
			  secureBootProcessResult=FOTA_JOB_FAILED_CALL_OUT;
			  macUpdateStat=FOTA_SECURE_BOOT_MAC_GENERATE;
			}
			break;

		  case FOTA_SECURE_BOOT_TAG_WRITE_CHK:

			memJobResult = (Fota_JobResultType_CallOut)Fota_PflsGetJobResult(Fota_MemoryInstance);
			if (FOTA_JOB_OK_CALL_OUT == memJobResult)
			{
			  secureBootProcessResult=FOTA_JOB_PENDING_CALL_OUT;
			  macUpdateStat=FOTA_SECURE_BOOT_INSTALL_SMR;
			}
			else if (FOTA_JOB_FAILED_CALL_OUT == memJobResult)
			{
			  secureBootProcessResult=FOTA_JOB_FAILED_CALL_OUT;
			  macUpdateStat=FOTA_SECURE_BOOT_MAC_GENERATE;
			}
			else
			{
			  secureBootProcessResult=FOTA_JOB_PENDING_CALL_OUT;
			}
			break;

		  case FOTA_SECURE_BOOT_INSTALL_SMR:
			#if(FOTA_MCU_MEMORY_ACCESS_TYPE==FOTA_MMU_TYPE) /* MMU TYPE */
			/* polyspace-begin CERT-C:EXP39-C [Justified:Low] "This conversion is used for OSS. they are same type" */
			(void)Fota_PflsGetCovAddr(Fota_MemoryInstance, \
	                                  FOTA_ALT_ADDR, \
	                                  &SignatureTagAddr, \
	                                  &SignatureTagSize);
			/* polyspace-end CERT-C:EXP39-C [Justified:Low] "This conversion is used for OSS. they are same type" */
			#endif

	        /* 5) Finally, install SMR and CR entry and verify SMR install */
	        /* Clear the service descriptor placed in shared memory */
			FOTA_MEMSET(&Fota_HseSrvDescriptor, 0, sizeof(hseSrvDescriptor_t));
	        pSmrEntryInstall = &(Fota_HseSrvDescriptor.hseSrv.smrEntryInstallReq);

	        /* Fill the service descriptor */
	        Fota_HseSrvDescriptor.srvId = HSE_SRV_ID_SMR_ENTRY_INSTALL;
	        pSmrEntryInstall->accessMode = HSE_ACCESS_MODE_ONE_PASS;
	        pSmrEntryInstall->entryIndex = 0u;
	        pSmrEntryInstall->pSmrEntry = (HOST_ADDR)&smrEntry;

	        pSmrEntryInstall->pSmrData = (HOST_ADDR)TgtAreaAddr;          /* pointing to passive partition */
	        pSmrEntryInstall->smrDataLength = smrEntry.smrSize;
	        pSmrEntryInstall->pAuthTag[0] = (HOST_ADDR)SignatureTagAddr;  /* pointing to passive partition */
	        pSmrEntryInstall->pAuthTag[1] = (HOST_ADDR)SignatureTagAddr;  /* pointing to passive partition */
	        pSmrEntryInstall->authTagLength[0] = (uint16)HmacTagLength;
	        pSmrEntryInstall->authTagLength[1] = (uint16)HmacTagLength;

			hseRequestResult = Hse_Ip_ServiceRequest(FOTA_HSE_MU0_INSTANCE, FOTA_HSE_MU_CHANNEL,
	                                               &Fota_HseIpRequest, &Fota_HseSrvDescriptor);
			if(HSE_SRV_RSP_OK != hseRequestResult)
			{
			  retVal|=(Std_ReturnType)E_NOT_OK;
			}

			/* verify SMR entry - SMR verify is not allowed for SHE boot,
			   only on next cycle could it be verified if BOOT_SEQ=0 */
			FOTA_MEMSET(&Fota_HseSrvDescriptor, 0, sizeof(hseSrvDescriptor_t));
			pSmrVerifySrv = &(Fota_HseSrvDescriptor.hseSrv.smrVerifyReq);

			Fota_HseSrvDescriptor.srvId = HSE_SRV_ID_SMR_VERIFY;
			pSmrVerifySrv->entryIndex = 0u;
			pSmrVerifySrv->options = HSE_SMR_VERIFICATION_OPTION_PASSIVE_MEM;

			hseRequestResult = Hse_Ip_ServiceRequest(FOTA_HSE_MU0_INSTANCE, FOTA_HSE_MU_CHANNEL,
	                                                 &Fota_HseIpRequest, &Fota_HseSrvDescriptor);
			if(HSE_SRV_RSP_OK != hseRequestResult)
			{
			  retVal|=(Std_ReturnType)E_NOT_OK;
			}

			/* Install CR Entry */
			/* Clear the service descriptor placed in shared memory */
			FOTA_MEMSET(&Fota_HseSrvDescriptor, 0, sizeof(hseSrvDescriptor_t));
			pCrEntryInstallSrv = &(Fota_HseSrvDescriptor.hseSrv.crEntryInstallReq);

			/* Fill the service descriptor */
			Fota_HseSrvDescriptor.srvId = HSE_SRV_ID_CORE_RESET_ENTRY_INSTALL;
			pCrEntryInstallSrv->crEntryIndex = 0u;
			pCrEntryInstallSrv->pCrEntry = (HOST_ADDR)&crEntry;

			hseRequestResult = Hse_Ip_ServiceRequest(FOTA_HSE_MU0_INSTANCE, FOTA_HSE_MU_CHANNEL,
	                                               &Fota_HseIpRequest, &Fota_HseSrvDescriptor);
			if(HSE_SRV_RSP_OK != hseRequestResult)
			{
			  retVal|=(Std_ReturnType)E_NOT_OK;
			}

			/* verify if secure boot is success */
			FOTA_MEMSET(&Fota_HseSrvDescriptor, 0, sizeof(hseSrvDescriptor_t));

			Fota_HseSrvDescriptor.srvId = HSE_SRV_ID_GET_ATTR;
			Fota_HseSrvDescriptor.hseSrv.getAttrReq.attrId = HSE_SMR_CORE_BOOT_STATUS_ATTR_ID;
			Fota_HseSrvDescriptor.hseSrv.getAttrReq.attrLen = sizeof(hseAttrSmrCoreStatus_t);
			Fota_HseSrvDescriptor.hseSrv.getAttrReq.pAttr = (HOST_ADDR)&smrCoreStatus_Get;

			hseRequestResult = Hse_Ip_ServiceRequest(FOTA_HSE_MU0_INSTANCE, FOTA_HSE_MU_CHANNEL,
	                                               &Fota_HseIpRequest, &Fota_HseSrvDescriptor);
			if(HSE_SRV_RSP_OK != hseRequestResult)
			{
			  retVal|=(Std_ReturnType)E_NOT_OK;
			}

			if(E_OK==retVal)
			{
			  secureBootProcessResult=FOTA_JOB_PENDING_CALL_OUT;
			  macUpdateStat=FOTA_SECURE_BOOT_IVT_ERASE;
			}
			else
			{
			  secureBootProcessResult=FOTA_JOB_FAILED_CALL_OUT;
			  macUpdateStat=FOTA_SECURE_BOOT_MAC_GENERATE;
			}
			break;

		  case FOTA_SECURE_BOOT_IVT_ERASE:

	        #if(FOTA_MCU_MEMORY_ACCESS_TYPE==FOTA_MMU_TYPE) /* MMU TYPE */
			TgtStartAddr=Fota_Gast_SwUnitTable[EcuSwUnitIdx].StartAddress;
			/* polyspace-begin CERT-C:EXP39-C [Justified:Low] "This conversion is used for OSS. they are same type" */
			(void)Fota_PflsGetCovAddr(Fota_MemoryInstance, \
	                                  FOTA_ALT_ADDR, \
	                                  &TgtStartAddr, \
	                                  &TgtStartSize);
			/* polyspace-end CERT-C:EXP39-C [Justified:Low] "This conversion is used for OSS. they are same type" */
	        #endif

			/* passive partition BOOT_SEQ Enable */
		    FOTA_MEMCPY((void *)Fota_IVTBuffer,
	                    (const void *)TgtStartAddr,
	                    Fota_PflsEraseAlignmentValue);

	        (void)Fota_PflsTgtAreaSet(Fota_MemoryInstance,FOTA_ALT_ADDR);

			/* IVT area erase */
			retVal=Fota_PflsEraseRequest(Fota_MemoryInstance, \
	                                      Fota_Gast_SwUnitTable[EcuSwUnitIdx].StartAddress, \
	                                      Fota_PflsEraseAlignmentValue);
			if(E_OK==retVal)
			{
			  secureBootProcessResult=FOTA_JOB_PENDING_CALL_OUT;
			  macUpdateStat=FOTA_SECURE_BOOT_IVT_ERASE_CHK;
			}
			else
			{
			  secureBootProcessResult=FOTA_JOB_FAILED_CALL_OUT;
			  macUpdateStat=FOTA_SECURE_BOOT_MAC_GENERATE;
			}
			break;

		  case FOTA_SECURE_BOOT_IVT_ERASE_CHK:

			memJobResult = (Fota_JobResultType_CallOut)Fota_PflsGetJobResult(Fota_MemoryInstance);
			if (FOTA_JOB_OK_CALL_OUT == memJobResult)
			{
			  secureBootProcessResult=FOTA_JOB_PENDING_CALL_OUT;
			  macUpdateStat=FOTA_SECURE_BOOT_IVT_WRITE;
			}
			else if (FOTA_JOB_FAILED_CALL_OUT == memJobResult)
			{
			  secureBootProcessResult=FOTA_JOB_FAILED_CALL_OUT;
			  macUpdateStat=FOTA_SECURE_BOOT_MAC_GENERATE;
			}
			else
			{
			  secureBootProcessResult=FOTA_JOB_PENDING_CALL_OUT;
			}
			break;

		  case FOTA_SECURE_BOOT_IVT_WRITE:
			Fota_IVTBuffer[FOTA_FOUR] |= BOOT_SEQ_MASK; /* 4~7: Boot configuration word */

			retVal=Fota_PflsWriteRequest(Fota_MemoryInstance, \
	                                     Fota_Gast_SwUnitTable[EcuSwUnitIdx].StartAddress, \
	                                     Fota_IVTBuffer, \
	                                     Fota_PflsEraseAlignmentValue);
			if(E_OK==retVal)
			{
			  secureBootProcessResult=FOTA_JOB_PENDING_CALL_OUT;
			  macUpdateStat=FOTA_SECURE_BOOT_IVT_WRITE_CHK;
			}
			else
			{
			  secureBootProcessResult=FOTA_JOB_FAILED_CALL_OUT;
			  macUpdateStat=FOTA_SECURE_BOOT_MAC_GENERATE;
			}
			break;

		  case FOTA_SECURE_BOOT_IVT_WRITE_CHK:

			memJobResult = (Fota_JobResultType_CallOut)Fota_PflsGetJobResult(Fota_MemoryInstance);
			if (FOTA_JOB_OK_CALL_OUT == memJobResult)
			{
			  secureBootProcessResult=FOTA_JOB_OK_CALL_OUT;
			  macUpdateStat=FOTA_SECURE_BOOT_MAC_GENERATE;
			}
			else if (FOTA_JOB_FAILED_CALL_OUT == memJobResult)
			{
			  secureBootProcessResult=FOTA_JOB_FAILED_CALL_OUT;
			  macUpdateStat=FOTA_SECURE_BOOT_MAC_GENERATE;
			}
			else
			{
			  secureBootProcessResult=FOTA_JOB_PENDING_CALL_OUT;
			}
			break;
		  default:
      /* Do Nothing */
			break;
	    }
	  }
	  /* polyspace-end CERT-C:INT36-C, MISRA-C3:10.5,11.4 [Justified:Low] "No Impact of this rule violation" */

	  return secureBootProcessResult;
    }
  #endif /* HWRESOURCE_VENDOR(HWRESOURCE_NXP) */

  /* polyspace-begin MISRA-C3:2.7,8.13 [Justified:Low] "Not a defect" */
  FUNC(Std_ReturnType, FOTA_CODE) Fota_DeriveKeyRequest_Callout
  (
    uint8 *Lpu8_MetaDataBuffer,
    uint8 MDBlockId,
    uint32 KDFKeyId,
    uint32 KDFResultKeyId,
    uint32 Csm_Meta_Header_Length,
    uint32 Csm_Meta_SK_Length
  )
  /* polyspace-end MISRA-C3:2.7,8.13 [Justified:Low] "Not a defect" */
  {
    Std_ReturnType retVal = E_NOT_OK;
    uint8 Lu8_Index;

    uint32 KDFcounter[1] = {1024};
    uint32 KDFPSKindexLen = 1u; /* for HSM index */
    uint32 KDFResultLen = FOTA_DERIVEKEY_LENGTH;
    uint8 Lau8_SecureFlashDerivedKey[FOTA_DERIVEKEY_LENGTH];
    uint32 KDFAlgorithm[1] = {0x81}; /* for HSM index */
    #if (HWRESOURCE_VENDOR(HWRESOURCE_NXP))
      uint8 rul_ExtractedKey[FOTA_DERIVEKEY_LENGTH];
      uint8 Pbkdf2_Encrypted_DerivedKey[FOTA_DERIVEKEY_LENGTH];
      uint32 ElementIndex = 0; /* Temparary value for Crypto Defect */
      uint32 KDFcounterLen = 4;
    #endif
	FOTA_MEMSET(Lau8_SecureFlashDerivedKey, 0, FOTA_DERIVEKEY_LENGTH);

    #if (HWRESOURCE_VENDOR(HWRESOURCE_NXP))

      retVal = Csm_KeyElementSet(\
        (SEC_SF_PBKDF2_SOURCE_KEY_PSK_OFFSET+(uint32)(Fota_Gu8_MetadataPSKidx)),\
        FOTA_CSM_KE_ID_SALT,\
        &Lpu8_MetaDataBuffer[Csm_Meta_Header_Length],\
        Csm_Meta_SK_Length);

      retVal |= Csm_KeyElementSet(\
        (SEC_SF_PBKDF2_SOURCE_KEY_PSK_OFFSET+(uint32)(Fota_Gu8_MetadataPSKidx)),\
        FOTA_CSM_KE_ID_ITERATION,\
        (uint8 *)KDFcounter,\
        KDFcounterLen);

      retVal |= Csm_KeyElementSet(\
        SEC_SF_PBKDF2_EXTRACTED_KEY,\
        FOTA_CSM_KE_ID_MAINKEY,\
        rul_ExtractedKey,\
        FOTA_DERIVEKEY_LENGTH);

      retVal |= Csm_KeySetValid(SEC_SF_PBKDF2_ENCRYPT_KEY);
      retVal |= Csm_KeySetValid(SEC_SF_PBKDF2_DECRYPT_KEY);
      retVal |= Csm_KeySetValid(SEC_SF_PBKDF2_SOURCE_KEY_PSK_OFFSET+(uint32)(Fota_Gu8_MetadataPSKidx));

      /* polyspace-begin DEFECT:OUT_BOUND_ARRAY, CERT-C:ARR30-C, MISRA-C3:18.1 [Justified:High] "It gets array index in range" */
      ElementIndex = Crypto_Util_GetKeyElementIdx (Crypto_Util_GetKeyIdx(SEC_SF_PBKDF2_ENCRYPT_KEY), CRYPTO_KE_CIPHER_KEY);
        *Crypto_aKeyElementList[ElementIndex].pu32CryptoElementActualSize = 16U;
      ElementIndex = Crypto_Util_GetKeyElementIdx (Crypto_Util_GetKeyIdx(SEC_SF_PBKDF2_DECRYPT_KEY), CRYPTO_KE_CIPHER_KEY);
        *Crypto_aKeyElementList[ElementIndex].pu32CryptoElementActualSize = 16U;
      ElementIndex = Crypto_Util_GetKeyElementIdx (Crypto_Util_GetKeyIdx(SEC_SF_PBKDF2_SOURCE_KEY_PSK_OFFSET+(uint32)(Fota_Gu8_MetadataPSKidx)), CRYPTO_KE_KEYDERIVATION_PASSWORD);
        *Crypto_aKeyElementList[ElementIndex].pu32CryptoElementActualSize = 16U;
      /* polyspace-end DEFECT:OUT_BOUND_ARRAY, CERT-C:ARR30-C, MISRA-C3:18.1 [Justified:High] "It gets array index in range" */


      if(E_OK == retVal)
      {
        retVal |= Csm_KeyDerive(
                  (SEC_SF_PBKDF2_SOURCE_KEY_PSK_OFFSET \
                    + (uint32)(Fota_Gu8_MetadataPSKidx)),
                  SEC_SF_PBKDF2_TARGET_KEY);

#if 0
        retVal |= Csm_KeyCopy(SEC_SF_PBKDF2_TARGET_KEY, SEC_SF_PBKDF2_EXTRACTED_KEY);
#else
        retVal |= Csm_KeyElementCopyPartial(SEC_SF_PBKDF2_TARGET_KEY,SEC_SF_PBKDF2_TARGET_ELEMENT,0U,0U,\
                  FOTA_DERIVEKEY_LENGTH,SEC_SF_PBKDF2_EXTRACTED_KEY,SEC_SF_PBKDF2_EXTRACTED_ELEMENT);
#endif

        retVal |= Csm_KeyElementGet(SEC_SF_PBKDF2_EXTRACTED_KEY,\
                  FOTA_CSM_KE_ID_MAINKEY,\
                  Pbkdf2_Encrypted_DerivedKey,\
                  &KDFResultLen);

        retVal |= Csm_Decrypt(SEC_SF_PBKDF2_DECRYPT_AES_ECB,\
                CRYPTO_OPERATIONMODE_SINGLECALL,\
                Pbkdf2_Encrypted_DerivedKey,\
                KDFResultLen,\
                Lau8_SecureFlashDerivedKey,\
                &KDFResultLen);
      }
    #else /* HWRESOURCE_VENDOR(HWRESOURCE_NXP) */
      retVal = \
          Csm_KeyElementSet(KDFKeyId, \
            FOTA_CSM_KE_ID_HSMINDEX, \
            &Fota_Gu8_MetadataPSKidx, \
            KDFPSKindexLen);

      retVal |= \
          Csm_KeyElementSet(KDFKeyId, \
            FOTA_CSM_KE_ID_SALT, \
            &Lpu8_MetaDataBuffer[Csm_Meta_Header_Length], \
            Csm_Meta_SK_Length);

      /* KeyElementId : Iteration */
      retVal |= \
          Csm_KeyElementSet(KDFKeyId, \
            FOTA_CSM_KE_ID_ITERATION, \
            (uint8*)KDFcounter, \
            sizeof(KDFcounter));

      retVal |= \
          Csm_KeyElementSet(KDFKeyId, \
            FOTA_CSM_KE_ID_ALGORITHM, \
            (uint8*)KDFAlgorithm, \
            sizeof(KDFAlgorithm));

      retVal |= Csm_KeySetValid(KDFKeyId);

      retVal |= \
          Csm_KeyElementSet(KDFResultKeyId, \
            FOTA_CSM_KE_ID_MAINKEY, \
            Lau8_SecureFlashDerivedKey, \
            sizeof(Lau8_SecureFlashDerivedKey));

      retVal |= Csm_KeySetValid(KDFResultKeyId);

      if(E_OK == retVal)
      {
        retVal |= Csm_KeyDerive(KDFKeyId, KDFResultKeyId);

        retVal |= Csm_KeyElementGet(KDFResultKeyId, FOTA_CSM_KE_ID_MAINKEY, \
          Lau8_SecureFlashDerivedKey, &KDFResultLen);
      }
    #endif /* HWRESOURCE_VENDOR(HWRESOURCE_NXP) */

    if (E_OK == retVal)
    {
      for (Lu8_Index = 0U; Lu8_Index < FOTA_DEC_KEY_LENGTH; Lu8_Index++)
      {
        rst_MetaPars.FirmwareKeyPtr[Lu8_Index]
          = Lau8_SecureFlashDerivedKey[Lu8_Index];
      }

      for (Lu8_Index = 0U; Lu8_Index < FOTA_MAC_LENGTH; Lu8_Index++)
      {
        rst_MetaPars.MacKeyPtr[Lu8_Index]
          = Lau8_SecureFlashDerivedKey[FOTA_DEC_KEY_LENGTH + Lu8_Index];
      }
    }

    return retVal;
  }

#endif /* (FOTA_STD_ON == FOTA_SF20_ENABLE)*/

#if (HWRESOURCE_FAMILY(HWRESOURCE_S32K31X))
#include "Power_Ip_MC_RGM.h"
/* polyspace-begin MISRA-C3:8.4,8.9,11.4 [Justified:Low] "No Impact of this rule violation" */
static Power_Ip_MC_RGM_Type * Fota_Power_Ip_pxMC_RGM = (Power_Ip_MC_RGM_Type *)IP_MC_RGM_BASE;

uint32 JYSRegValue = 0U;
/* polyspace-end MISRA-C3:8.4,8.9,11.4 [Justified:Low] "No Impact of this rule violation" */

static FUNC(Std_ReturnType, FOTA_CODE) Mcu_s32k3xx_GetResetReason(void)
{
	/* Temporary variables for DES and FES registers value. */
	uint32 RegValue = 0U;
	Std_ReturnType retVal;
	/* Check "Destructive Reset Reason" from DES Status Register. */
	RegValue = Fota_Power_Ip_pxMC_RGM->DES & MC_RGM_DES_RWBITS_MASK32;

	JYSRegValue = RegValue;

	if ((uint32)0U != RegValue)
	{
		/* Cold start */
		retVal = E_NOT_OK;
	}
	else
	{
		/* Warm start */
		retVal = E_OK;
	}

	return retVal;
}

/* polyspace-begin MISRA-C3:8.9,11.4 [Justified:Low] "No Impact of this rule violation" */
static Power_Ip_MC_ME_Type * Power_Ip_pxMC_ME = (Power_Ip_MC_ME_Type *)IP_MC_ME_BASE;
/* polyspace-end MISRA-C3:8.9,11.4 [Justified:Low] "No Impact of this rule violation" */

static FUNC(void, FOTA_CODE) Mcu_S32k31x_Reset(void)
{
  /* Makes a request to trigger a Destructive Reset Event */
  Power_Ip_pxMC_ME->MODE_CONF=MC_ME_MODE_CONF(MC_ME_MODE_CONF_FUNC_RST_MASK);
  Power_Ip_pxMC_ME->MODE_UPD = MC_ME_MODE_UPD_MODE_UPD(MC_ME_MODE_UPD_MODE_UPD_MASK);
  /* Write key to MC_ME_CTL_KEY */
  Power_Ip_pxMC_ME->CTL_KEY = MC_ME_CTL_KEY_KEY(MC_ME_CTL_KEY_DIRECT_KEY_U32);

  /* Write inverted key to MC_ME_CTL_KEY */
  Power_Ip_pxMC_ME->CTL_KEY = MC_ME_CTL_KEY_KEY(MC_ME_CTL_KEY_INVERTED_KEY_U32);
}
#endif

#if (HWRESOURCE_FAMILY(HWRESOURCE_TC21X) ||\
     HWRESOURCE_FAMILY(HWRESOURCE_TC22X) ||\
     HWRESOURCE_FAMILY(HWRESOURCE_TC23X) ||\
     HWRESOURCE_FAMILY(HWRESOURCE_TC26X) ||\
     HWRESOURCE_FAMILY(HWRESOURCE_TC27X) ||\
     HWRESOURCE_FAMILY(HWRESOURCE_TC29X) ||\
     HWRESOURCE_FAMILY(HWRESOURCE_TC33X) ||\
     HWRESOURCE_FAMILY(HWRESOURCE_TC36X) ||\
     HWRESOURCE_FAMILY(HWRESOURCE_TC37X) ||\
     HWRESOURCE_FAMILY(HWRESOURCE_TC38X) ||\
     HWRESOURCE_FAMILY(HWRESOURCE_TC39X))
static FUNC(Std_ReturnType, FOTA_CODE) Mcu_tcxxx_GetResetReason(void)
{
  Std_ReturnType retVal;
  Ifx_SCU_RSTSTAT resetState = SCU_RSTSTAT;
  /* polyspace-begin MISRA-C3:2.2 [Not a defect:Low] "No Impact of this rule violation" */
  /* Check for reset warm start */
  if (0x1 == (resetState.B.SW))
  {
    retVal = E_OK;
  }
  else
  {
    retVal = E_NOT_OK;
  }
  /* polyspace-end MISRA-C3:2.2 [Not a defect:Low] "No Impact of this rule violation" */
  return retVal;
}

static FUNC(void, FOTA_CODE) Mcu_Tcxxx_Reset(void)
{
  EcuM_UserType user = 0;
  (void)EcuM_SelectShutdownTarget(ECUM_STATE_RESET, ECUM_RESET_MCU);
  (void)EcuM_ReleaseRUN(user);
}
#endif

#if (HWRESOURCE_FAMILY(HWRESOURCE_S32K14X))
static FUNC(Std_ReturnType, FOTA_CODE) Mcu_s32k14x_GetResetReason(void)
{
  Std_ReturnType retVal;
  if ((REG_READ32(RCM_SRS_ADDR32) & RCM_SRS_SW_MASK32) == RCM_SRS_SW_MASK32)
  {
    /* warm start(software reset) is executed */
    retVal = E_OK;
  }
  else
  {
    retVal = E_NOT_OK;
  }
  return retVal;
}

static FUNC(void, FOTA_CODE) Mcu_S32k14x_Reset(void)
{
  ASM_KEYWORD(" dsb");               /* All memory accesses have to be completed before reset */
  /** @violates @ref Mcu_CortexM4_c_REF_4 Required Rule 11.1, Conversion from integer to pointer */
  /** @violates @ref Mcu_CortexM4_c_REF_5 The cast is used to access memory mapped registers.*/
  REG_WRITE32( CM4_AIRCR_BASEADDR, (uint32)(CM4_AIRCR_VECTKEY(0x5FAU) |
                                            (REG_READ32(CM4_AIRCR_BASEADDR) & CM4_AIRCR_PRIGROUP_MASK) |
                                            CM4_AIRCR_SYSRESETREQ_MASK ));
  ASM_KEYWORD(" dsb");               /* All memory accesses have to be completed */
}

#endif

#if ((HWRESOURCE_FAMILY(HWRESOURCE_MPC5606X)) ||\
     (HWRESOURCE_FAMILY(HWRESOURCE_MPC5606X)) ||\
     (HWRESOURCE_FAMILY(HWRESOURCE_MPC5607X)))
static FUNC(Std_ReturnType, FOTA_CODE) Mcu_mpc560xb_GetResetReason(void)
{
  Std_ReturnType retVal;
  /* polyspace-begin DEFECT:DEAD_CODE, MISRA-C3:14.3,2.1 [Justified:Low] "if-condition depends on the MCU." */
  if ((RGM_FES_F_SOFT & (uint32)RGM_FES_SOFT) == TRUE)
  {
    /* warm start(software reset) is executed */
    retVal = E_OK;
  }
  else
  {
    retVal = E_NOT_OK;
  }
  /* polyspace-end DEFECT:DEAD_CODE, MISRA-C3:14.3,2.1 [Justified:Low] "if-condition depends on the MCU." */
  return retVal;
}

static FUNC(void, FOTA_CODE) Mcu_Mpc560xx_Reset(void)
{
  uint32 Lu32_Indx = 0UL;

  /* ME_MCTRL (SV)                                          */
  /* -trigger s/w-controlled mode changes                   */
  /*--------------------------------------------------------*/
  /*  TARGET_MODE[0:3] - RESET(0),TEST(1),SAFE(2),DRUN(3)   */
  /*                     RUN0/1/2/3(4/5/6/7),HALT0(8),STOP0(10 */
  /*  KEY[16:31] - Key(0x5AF0),Inverted Key(0xA50F)         */

  REG_WRITE32(MC_ME_MCTL_R, (0U | MCU_SOFT_CONTROL_KEY_ONE));
  REG_WRITE32(MC_ME_MCTL_R, (0U | MCU_SOFT_CONTROL_KEY_TWO));

  do
  {
      /* polyspace-begin DEFECT:DEAD_CODE, MISRA-C3:14.3,2.1 [Justified:Low] "No Impact of this rule violation. Fail-safe." */
      if (Lu32_Indx > 4294967295UL)
      {
          break;
      }
      /* polyspace-end DEFECT:DEAD_CODE, MISRA-C3:14.3,2.1 [Justified:Low] "No Impact of this rule violation. Fail-safe." */
      Lu32_Indx++;
  }
  while ((MC_ME_GS & (MCU_TRANSITION_STATUS)) == MCU_TRANSITION_STATUS);
}
#endif /* #if (HWRESOURCE_FAMILY(HWRESOURCE_MPC560XB)) */

#if ((HWRESOURCE_FAMILY(HWRESOURCE_SPC58XC)) ||\
      (HWRESOURCE_FAMILY(HWRESOURCE_SPC58XB)) ||\
      (HWRESOURCE_FAMILY(HWRESOURCE_SPC58XG)) ||\
      (HWRESOURCE_FAMILY(HWRESOURCE_SPC58XH)))
static FUNC(Std_ReturnType, FOTA_CODE) Mcu_spc58x_GetResetReason(void)
{
  uint32 porValue;
  Std_ReturnType retVal;

  porValue = SYST_MC_POWER_ON_START();
  if(FALSE != porValue)
  {
    /* Clear the power on reset. It is required for detection of warm start
     * and to clear the BTL and APP shared memory.
     * APPLICATION may also need Power on reset bit to trigger further
     * actions. For now it is a work around but bootloader
     * should not modify this bit for proper functioning of application
     * software.
     */

   /* Cold start - The start-up of the ECU from a powered-down or off state */
    retVal = E_NOT_OK;
  }
  else
  {
    /* Warm start means that the MCU does have a continuous power supply
     * and the RESET is not from the change of Vcc,
     * he reset was generated by watchdog, software, etc etc ..
     */
    retVal = E_OK;
  }
  return retVal;
}

static FUNC(void, FOTA_CODE) Mcu_Spc58x_Reset(void)
{
  MC_ME_MCTL = 0x00005AF0U; /* Target mode = DRUN, KEY = 5AF0*/
  MC_ME_MCTL = 0x0000A50FU; /* Target mode = DRUN, KEY = A50F*/
}
#endif /* #if (HWRESOURCE_FAMILY(HWRESOURCE_SPC58XC)) */

#if ((HWRESOURCE_FAMILY(HWRESOURCE_CYT2BXX)) ||\
     (HWRESOURCE_FAMILY(HWRESOURCE_CYT3BXX)) ||\
     (HWRESOURCE_FAMILY(HWRESOURCE_CYT4BXX)) ||\
     (HWRESOURCE_FAMILY(HWRESOURCE_CYT6BXX)))
static FUNC(Std_ReturnType, FOTA_CODE) Mcu_cytxxx_GetResetReason(void)
{
  Std_ReturnType Ldt_retvalue;

  /* Reset Status Register - Power-On Reset Status
   * 1 A Power-On Reset has occurred.
   * 0 No Power-On Reset has occurred.
   */

  if ((CY_SYSRESET_SOFT != *CYTXXX_SRSS & CY_SYSRESET_MASK))
  {
    /* Clear the power on reset. It is required for detection of warm start
     * and to clear the BTL and APP shared memory.
     * APPLICATION may also need Power on reset bit to trigger further
     * actions. For now it is a work around but bootloader
     * should not modify this bit for proper functioning of application
     * software.
     * It is valid only when only SW Reset bit is set */

    /* Cold start - The start-up of the ECU from a powered-down or off state */
    Ldt_retvalue = E_NOT_OK;
  }
  else
  {
    /* Warm start means that the MCU does have a continuous power supply
     * and the RESET is not from the change of Vcc,
     * he reset was generated by watchdog, software, etc etc ..
     */
    Ldt_retvalue = E_OK;
  }
  return Ldt_retvalue;
}
#endif

#if ((HWRESOURCE_FAMILY(HWRESOURCE_CYT2BXX)) ||\
     (HWRESOURCE_FAMILY(HWRESOURCE_CYT3BXX)) ||\
     (HWRESOURCE_FAMILY(HWRESOURCE_CYT4BXX)) ||\
     (HWRESOURCE_FAMILY(HWRESOURCE_CYT6BXX)))
static FUNC(void, FOTA_CODE) Mcu_Cytxxx_Reset(void)
{
  /* Ensure all outstanding memory accesses included
    buffered write are completed before reset */
  __asm("dsb");
  /* Keep priority group unchanged */
  *CYTXXX_SCB_AIRCR = (uint32)((0x5FAUL << SCB_AIRCR_VECTKEY_Pos)    |
                        (*CYTXXX_SCB_AIRCR & SCB_AIRCR_PRIGROUP_Msk) |
                         SCB_AIRCR_SYSRESETREQ_Msk);
  /* Ensure completion of memory access */
  __asm("dsb");
  while(1)
  {
    /* Wait until reset */
  }
}
#endif

#if (HWRESOURCE_MCU(HWRESOURCE_RH850F1KM))
static FUNC(Std_ReturnType, FOTA_CODE) Mcu_Rh850F1km_GetResetReason(void)
{
  Std_ReturnType Ldt_retvalue;

  /* Reset Status Register - Power-On Reset Status
   * 1 Soft Reset has occurred.
   * 0 No Soft Reset has occurred.
   */
  if (1 != SYST_MC_SOFT_RESET_ON_START())
  {
    /* Clear the power on reset. It is required for detection of warm start
     * and to clear the BTL and APP shared memory.
     * APPLICATION may also need Power on reset bit to trigger further
     * actions. For now it is a work around but bootloader
     * should not modify this bit for proper functioning of application
     * software.
     */

   /* Cold start - The start-up of the ECU from a powered-down or off state */
    Ldt_retvalue = E_NOT_OK;
  }
  else
  {
    /* Warm start means that the MCU does have a continuous power supply
     * and the RESET is not from the change of Vcc,
     * he reset was generated by watchdog, software, etc etc ..
     */
    Ldt_retvalue = E_OK;
  }

  return Ldt_retvalue;
}

static FUNC(void, FOTA_CODE) Mcu_Rh850F1km_Reset(void)
{
  /* clear power reset because after softreset is execute,
    power reset still keep active value (power on reset event)
    => when init MCU, Os check this value and clear RAM value (power on reset event).
       After clear power reset bit, then soft-reset execute,
       OS isn't clear RAM value */
  protected_write(WPROTREG.ulPROTCMD0, WPROTREG.ulPROTS0, RESFREG.ulRESFC,
    (RESFREG.ulRESFC & (~(uint32)0x00000200)));     /* Enable PLL */
  /* SW reset */
  protected_write(WPROTREG.ulPROTCMD0, WPROTREG.ulPROTS0, RESFREG.ulSWRESA, 0x01u);
}
#endif /* #if (HWRESOURCE_MCU(HWRESOURCE_RH850F1KM)) */

#if ((HWRESOURCE_MCU(HWRESOURCE_RH850F1K)) |\
     (HWRESOURCE_MCU(HWRESOURCE_RH850F1L)))
#pragma asm
.text
.align  2
.global _WritetProtectRegister
_WritetProtectRegister:
  prepare {r20,r21}, 8
  mov   0x000000a5, r20
  not   r7, r21

  st.w  r20, 0[r8]
  st.w  r7, 0[r6]
  st.w  r21, 0[r6]
  st.w  r7, 0[r6]

  dispose 8, {r20,r21}
  jmp   [lp]
#pragma endasm

Std_ReturnType Mcu_Rh850F1x_GetResetReason(void)
{
  Std_ReturnType Ldt_retvalue;

  /* Reset Status Register - Power-On Reset Status
   * 1 A Power-On Reset has occurred.
   * 0 No Power-On Reset has occurred.
   */
  if(TRUE == SYST_MC_POWER_ON_START_F1K())
  {
    /* Cold start - The start-up of the ECU from a powered-down or off state */
    Ldt_retvalue = E_NOT_OK;
  }
  else
  {
    /* Warm start means that the MCU does have a continuous power supply
     * and the RESET is not from the change of Vcc,
     * he reset was generated by watchdog, software, etc etc ..
     */
    Ldt_retvalue = E_OK;
  }
  return Ldt_retvalue;
}

static FUNC(void, FOTA_CODE) Mcu_Rh850F1x_Reset(void)
{
  WritetProtectRegister( (uint32 *)&SWRESA, 0x1, (uint32 *)&PROTCMD0);
}
#endif


FUNC(Std_ReturnType, FOTA_CODE) Fota_IsWarmReset(void)
{
	Std_ReturnType retVal = E_NOT_OK;
  #if (HWRESOURCE_FAMILY(HWRESOURCE_S32K31X))
	retVal = Mcu_s32k3xx_GetResetReason();
  #elif (HWRESOURCE_FAMILY(HWRESOURCE_TC21X) ||\
         HWRESOURCE_FAMILY(HWRESOURCE_TC22X) ||\
         HWRESOURCE_FAMILY(HWRESOURCE_TC23X) ||\
         HWRESOURCE_FAMILY(HWRESOURCE_TC26X) ||\
         HWRESOURCE_FAMILY(HWRESOURCE_TC27X) ||\
         HWRESOURCE_FAMILY(HWRESOURCE_TC29X) ||\
         HWRESOURCE_FAMILY(HWRESOURCE_TC33X) ||\
         HWRESOURCE_FAMILY(HWRESOURCE_TC36X) ||\
         HWRESOURCE_FAMILY(HWRESOURCE_TC37X) ||\
         HWRESOURCE_FAMILY(HWRESOURCE_TC38X) ||\
         HWRESOURCE_FAMILY(HWRESOURCE_TC39X))
  retVal = Mcu_tcxxx_GetResetReason();
  #elif (HWRESOURCE_FAMILY(HWRESOURCE_S32K14X))
  retVal = Mcu_s32k14x_GetResetReason();
  #elif (HWRESOURCE_FAMILY(HWRESOURCE_S32K31X))
  retVal = Mcu_s32k3xx_GetResetReason();
  #elif ((HWRESOURCE_FAMILY(HWRESOURCE_MPC5606X)) ||\
         (HWRESOURCE_FAMILY(HWRESOURCE_MPC5606X)) ||\
         (HWRESOURCE_FAMILY(HWRESOURCE_MPC5607X)))
  retVal = Mcu_mpc560xb_GetResetReason();
  #elif ((HWRESOURCE_FAMILY(HWRESOURCE_SPC58XC)) ||\
         (HWRESOURCE_FAMILY(HWRESOURCE_SPC58XB)) ||\
         (HWRESOURCE_FAMILY(HWRESOURCE_SPC58XG)) ||\
         (HWRESOURCE_FAMILY(HWRESOURCE_SPC58XH)))
  retVal = Mcu_spc58x_GetResetReason();
  #elif ((HWRESOURCE_FAMILY(HWRESOURCE_CYT2BXX)) ||\
         (HWRESOURCE_FAMILY(HWRESOURCE_CYT3BXX)) ||\
         (HWRESOURCE_FAMILY(HWRESOURCE_CYT4BXX)) ||\
         (HWRESOURCE_FAMILY(HWRESOURCE_CYT6BXX)))
  retVal = Mcu_cytxxx_GetResetReason();
  #elif (HWRESOURCE_MCU(HWRESOURCE_RH850F1KM))
  retVal = Mcu_Rh850F1km_GetResetReason();
  #elif ((HWRESOURCE_MCU(HWRESOURCE_RH850F1K)) |\
         (HWRESOURCE_MCU(HWRESOURCE_RH850F1L)))
  retVal = Mcu_Rh850F1x_GetResetReason();
  #else
  #endif

  return retVal;
}

/*******************************************************************************
** Function Name        : EcuM_RequestReset                                   **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Integration Code For Request Reset using Release    **
**                        Run API                                             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : user                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType (E_OK or E_NOT_OK)                   **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                                                                            **
**                        Function(s) invoked    : EcuM_SelectShutdownTarget  **
**                                                 EcuM_ReleaseRUN            **
*******************************************************************************/
FUNC(void, FOTA_CODE) Fota_RequestReset(void)
{
  #if ((HWRESOURCE_FAMILY(HWRESOURCE_CYT2BXX)) ||\
       (HWRESOURCE_FAMILY(HWRESOURCE_CYT3BXX)) ||\
       (HWRESOURCE_FAMILY(HWRESOURCE_CYT4BXX)) ||\
       (HWRESOURCE_FAMILY(HWRESOURCE_CYT6BXX)))
  Mcu_Cytxxx_Reset();
  #elif (HWRESOURCE_FAMILY(HWRESOURCE_S32K14X))
  Mcu_S32k14x_Reset();
  #elif (HWRESOURCE_FAMILY(HWRESOURCE_S32K31X))
  Mcu_S32k31x_Reset();
  #elif ((HWRESOURCE_FAMILY(HWRESOURCE_MPC5605X)) ||\
         (HWRESOURCE_FAMILY(HWRESOURCE_MPC5606X)) ||\
         (HWRESOURCE_FAMILY(HWRESOURCE_MPC5607X)))
  Mcu_Mpc560xx_Reset();
  #elif ((HWRESOURCE_FAMILY(HWRESOURCE_SPC58XC)) ||\
         (HWRESOURCE_FAMILY(HWRESOURCE_SPC58XB)) ||\
         (HWRESOURCE_FAMILY(HWRESOURCE_SPC58XG)) ||\
         (HWRESOURCE_FAMILY(HWRESOURCE_SPC58XH)))
  Mcu_Spc58x_Reset();
  #elif (HWRESOURCE_MCU(HWRESOURCE_RH850F1KM))
  Mcu_Rh850F1km_Reset();
  #elif ((HWRESOURCE_MCU(HWRESOURCE_RH850F1K)) |\
         (HWRESOURCE_MCU(HWRESOURCE_RH850F1L)))
  Mcu_Rh850F1x_Reset();
  #elif (HWRESOURCE_FAMILY(HWRESOURCE_TC21X) ||\
         HWRESOURCE_FAMILY(HWRESOURCE_TC22X) ||\
         HWRESOURCE_FAMILY(HWRESOURCE_TC23X) ||\
         HWRESOURCE_FAMILY(HWRESOURCE_TC26X) ||\
         HWRESOURCE_FAMILY(HWRESOURCE_TC27X) ||\
         HWRESOURCE_FAMILY(HWRESOURCE_TC29X) ||\
         HWRESOURCE_FAMILY(HWRESOURCE_TC33X) ||\
         HWRESOURCE_FAMILY(HWRESOURCE_TC36X) ||\
         HWRESOURCE_FAMILY(HWRESOURCE_TC37X) ||\
         HWRESOURCE_FAMILY(HWRESOURCE_TC38X) ||\
         HWRESOURCE_FAMILY(HWRESOURCE_TC39X))
  Mcu_Tcxxx_Reset();
  #else
  #endif
}

FUNC(uint16, FOTA_CODE) Fota_OutDelayTime_Callout(void)
{
  Std_ReturnType LddRetVal = 0x03U;

  return LddRetVal;
}

#if ((FOTA_DOWN_GRADE_PROTECTION_USED==STD_ON) && (FOTA_MCU_MEMORY_ACCESS_TYPE!=FOTA_SINGLE_TYPE))
FUNC(Std_ReturnType, FOTA_CODE) Fota_DualMemDownGradeChk_Callout(void)
{
	/* Downgrade check rule                                       */
	/* if Target Partition Version >= Active Partition Version    */
	/* then return E_OK (upgrade or same version case)            */
	/* else return E_NOT_OK (downgrade case)                      */
    /* refer to UM if you want more information                   */
	/* check All of SwUnit                                        */
	/* if security level is OEUK, return E_OK                     */


	VAR(Std_ReturnType, FOTA_CODE) retVal = E_NOT_OK;
	Dcm_SecLevelType			   ren_SecLevel;

#if (FOTA_MCU_MEMORY_ACCESS_TYPE!=FOTA_MMU_TYPE)
	Fota_PartitionType             LenActivePartition;
#endif

	if(Dcm_GetSecurityLevel(&ren_SecLevel)==E_OK)
	{
		/* rollback case (OEUK)*/
		if(ren_SecLevel == FOTA_SECURITY_ROW_L10)
		{
			retVal = E_OK;
		}
		else
		{
			/* Version comare code should be bellow for downgrade check  */
			/* All of SwUnit should be checked                           */

			/*********************************************************/
			/* Version Check Rule                                    */
			/*            Running Partitition   Target Partition     */
			/* TV II     : Always A part (STD)   Always B part (ALT) */
			/* Aurix 2G	 : Always A part (STD)   Always B part (ALT) */
			/* S32K3	 : Always A part (STD)   Always B part (ALT) */
			/* SPC58xH   : Always A part (STD)   Always B part (ALT) */
			/* SPC58xC   : Depends on PC         Depends on PC       */
			/* RH850     : Depends on PC         Depends on PC       */
			/*********************************************************/

			 #if (FOTA_MCU_MEMORY_ACCESS_TYPE == FOTA_MMU_TYPE)
			 /**************************************************************************************************/
			 /*                                    MMU MCU                                                     */
			 /* version compare rutine should be hear                                                          */
			 /* Upgrade Case   : return CODEFLASH_RET_OK  (Version in Inactive area >= Version in Active area) */
			 /* Downgrade Case : return CODEFLASH_RET_ERR (Version in Inactive area <  Version in Active area) */
			 /**************************************************************************************************/

			 /* Always Running Partition is A */

            /* user should fill below code if MMU*/
			 /*@ if((*(uint32*)(ACTIVE_AREA_VERSION_ADDR_SWUNIT1) <= *(uint32*)(INACTIVE_AREA_VERSION_ADDR_SWUNIT1)) &&    */
			 /*@    (*(uint32*)(ACTIVE_AREA_VERSION_ADDR_SWUNIT2) <= *(uint32*)(INACTIVE_AREA_VERSION_ADDR_SWUNIT2)) &&    */
			 /*@     ... Number of SwUnits      		                                                                   */
			 /*@ {	                                                                                                       */
			 /*@     ren_Ret=E_OK;                                                                                         */
			 /*@ }                                                                                                         */
			 /*@ else                                                                                                      */
			 /*@ {                                                                                                         */
			 /*@     ren_Ret=E_NOT_OK;                                                                                     */
			 /*@ }                                                                                                         */

			 #else

			  if(Fota_GetActivePartition(&LenActivePartition)==E_OK)
			  {
				  if(LenActivePartition==FOTA_PARTITION_A)
				  {
				  /**************************************************************************************************/
				  /*                                  Non MMU MCU (Partition_A Active case)                         */
				  /* version compare rutine should be hear                                                          */
				  /* Upgrade Case   : return E_OK  (Version in Partition B >= Version in Partition A)               */
				  /* Downgrade Case : return E_NOT_OK (Version in Partition B < Version in Partition A)             */
				  /**************************************************************************************************/

				 /* user should fill below code if Non MMU*/
				 /*@    if(*(uint32*)(PARTA_VERSION_ADDR) <= *(uint32*)(PARTB_VERSION_ADDR))            */
				 /*@    {                                                                               */
				 /*@ 		retVal = E_OK;                                                              */
				 /*@    }                                                                               */
				 /*@    else                                                                            */
				 /*@    {                                                                               */
				 /*@   	    retVal = E_NOT_OK;                                                          */
				 /*@    }                                                                               */

				  }
				  else if(LenActivePartition==FOTA_PARTITION_B)
				  {

				  /**************************************************************************************************/
				  /*                                  Non MMU MCU (Partition_B Active case)                         */
				  /* version compare rutine should be hear                                                          */
				  /* Upgrade Case   : return E_OK  (Version in Partition A >= Version in Partition B)               */
				  /* Downgrade Case : return E_NOT_OK (Version in Partition A < Version in Partition B)             */
				  /**************************************************************************************************/

				 /* user should fill below code if Non MMU*/
				 /*@    if(*(uint32*)(PARTB_VERSION_ADDR) <= *(uint32*)(PARTA_VERSION_ADDR))            */
				 /*@    {                                                                               */
				 /*@ 	    retVal = E_OK;                                                              */
				 /*@    }                                                                               */
				 /*@    else                                                                            */
				 /*@    {                                                                               */
				 /*@   	    retVal = E_NOT_OK;                                                          */
				 /*@    }                                                                               */

				  }
				  else
				  {
					  retVal = E_NOT_OK;
				  }
			  }
			  else
			  {
				  retVal = E_NOT_OK;
			  }

		     #endif

		}
	}
	else
	{
		retVal = E_NOT_OK;
	}

	return retVal;
}
#endif


#if (FOTA_MCU_MEMORY_ACCESS_TYPE!=FOTA_SINGLE_TYPE)
FUNC(Std_ReturnType, FOTA_CODE) Fota_DualMemSwUnitsVerDependChk_Callout(void)
{
	VAR(Std_ReturnType, FOTA_CODE) retVal = E_NOT_OK;
	/* version check rule                                                                      */
	/* You must check the version dependencies of all SwUnit                                   */
	/* Here, version dependency between SwUnits is checked.                                    */
	/* The version location is the SwUnit location in the inactive area                        */
	/* In the case of Non MMU, only a single SwUnit is supported, so it always returns as E_OK */

	#if(FOTA_MCU_MEMORY_ACCESS_TYPE==FOTA_MMU_TYPE)
	/* Version comare code should be bellow */






	    retVal = E_OK;

	#else
		retVal = E_OK;
    #endif


	return retVal;
}
#endif


#if ((FOTA_SOFTWARE_VERSION_CHECK == STD_ON) &&\
  (FOTA_MCU_MEMORY_ACCESS_TYPE == FOTA_SINGLE_TYPE))
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "Not a defect" */
static FUNC(Fota_VersionCompareCallOutType, FOTA_CODE) Fota_CompareVersionCallOut(
                                        uint8 *newVer, uint8 lengthNewVer,
                                        uint8 *currentVersion, uint8 lengthCurrent)
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "Not a defect" */
{
  Fota_VersionCompareCallOutType result=FOTA_VERSION_CHECK_CALLOUT_EQUAL;
  uint8 index;

  if (lengthNewVer > lengthCurrent)
  {
    result = FOTA_VERSION_CHECK_CALLOUT_GREATER;
  }
  else if (lengthCurrent < lengthNewVer)
  {
    result = FOTA_VERSION_CHECK_CALLOUT_SMALLER;
  }
  else
  {
    /* Check the Header is fully written */
    for (index = 0; index < lengthCurrent; index++)
    {
      if (currentVersion[index] == newVer[index])
      {
        result = FOTA_VERSION_CHECK_CALLOUT_EQUAL;
      }
      else if (newVer[index] > currentVersion[index])
      {
        result = FOTA_VERSION_CHECK_CALLOUT_GREATER;
      }
      else
      {
        result = FOTA_VERSION_CHECK_CALLOUT_SMALLER;
      }

      if (result!=FOTA_VERSION_CHECK_CALLOUT_EQUAL)
      {
        break;
      }
    }
  }
  return result;
}
#endif /* #if (FOTA_DOWN_GRADE_PROTECTION_USED == FOTA_STD_ON) */

#if ((FOTA_SOFTWARE_VERSION_CHECK == STD_ON) &&\
  (FOTA_MCU_MEMORY_ACCESS_TYPE == FOTA_SINGLE_TYPE))
/* polyspace-begin MISRA-C3:2.7,8.13 [Justified:Low] "Not a defect" */
FUNC(Std_ReturnType, FOTA_CODE) Fota_SvcCheckVersion(uint8 *newVer, uint8 lengthNewVer,
                                    uint8 *currentVersion, uint8 lengthCurrent)
/* polyspace-end MISRA-C3:2.7,8.13 [Justified:Low] "Not a defect" */
{
  Std_ReturnType retVal=E_NOT_OK;
  Dcm_SecLevelType  secLevel;
  Fota_VersionCompareCallOutType result;
  if (Dcm_GetSecurityLevel(&secLevel) == (Std_ReturnType)E_OK)
  {
    /* rollback case (OEUK)*/
    if (secLevel == FOTA_SECURITY_ROW_L10)
    {
      retVal = E_OK;
    }
    else
    {
      result = Fota_CompareVersionCallOut(newVer, lengthNewVer,
                                          currentVersion, lengthCurrent);
      /* This is HAE test code, Do not use this. */
      if ((FOTA_VERSION_CHECK_CALLOUT_GREATER == result) ||
        (FOTA_VERSION_CHECK_CALLOUT_EQUAL == result))
      {
        retVal = E_OK;
      }
      else
      {
        retVal = E_NOT_OK;
      }
    }
    if (E_OK == retVal)
    {
      /* version check rule                                                                      */
      /* You must check the version dependencies of all SwUnit                                   */
      /* Here, version dependency between SwUnits is checked.                                    */
    }
  }
  /* User should make own version check logic here. */
  return retVal;
}
#endif /* #if ((FOTA_SOFTWARE_VERSION_CHECK == STD_ON) && (FOTA_MCU_MEMORY_ACCESS_TYPE==FOTA_SINGLE_TYPE)) */

FUNC(void, FOTA_CODE) Fota_DestructiveResetSet(void)
{
	#if HWRESOURCE_FAMILY(HWRESOURCE_SPC58XH)
	Fota_DestructiveResetEnable = TRUE;
	#endif
}

#if HWRESOURCE_FAMILY(HWRESOURCE_SPC58XH)
FUNC(void, FOTA_CODE) Fota_DestructiveReset(void)
{
	if (Fota_DestructiveResetEnable == TRUE)
	{
		Mcu_RGM_PerformReset(MCU_DEST_RESET);
		Fota_DestructiveResetEnable = FALSE;
	}
	else
	{
		Mcu_LLD_PerformReset();
	}
}
#endif

FUNC(Fota_JobResultType_CallOut, FOTA_CODE) Fota_SecureBootMacUpdate(void)
{
	Fota_JobResultType_CallOut jobResult = FOTA_JOB_FAILED_CALL_OUT;
	/* Hae HSM Use Case */
#if (FOTA_STD_ON == FOTA_SF20_ENABLE)

#if (HWRESOURCE_VENDOR(HWRESOURCE_NXP))
	  jobResult=Fota_S32k3_SecureBootProcess();

#else


	HSM_SECURITY_INFO_t rst_HsmSecInfo;
	HSM_VERSION_CTX_t   rst_HsmVerInfo;
	uint32              rul_HsmVer;

	FOTA_MEMSET(&rst_HsmSecInfo, 0, sizeof(rst_HsmSecInfo));
	FOTA_MEMSET(&rst_HsmVerInfo, 0, sizeof(rst_HsmVerInfo));

	if((HSM_GetAllSecurityInfo(&rst_HsmSecInfo)==E_OK) &&
	   (HSM_GetVersionInfo(&rst_HsmVerInfo)==E_OK))
	{

		/* SecureBoot Not Enabled */
		if((rst_HsmSecInfo.secureBootState == HSM_SECUREBOOT_DISABLE) ||
		   (rst_HsmSecInfo.secureBootState == HSM_SECUREBOOT_NOT_PERFORMED))
		{
			jobResult = FOTA_JOB_OK_CALL_OUT;
		}
		else /* SecureBoot Enabled */
		{
			rul_HsmVer = (uint32)FOTA_ZERO;
			rul_HsmVer|= (uint32)(rst_HsmVerInfo.hsmMajorVersion)<<16;
			rul_HsmVer|= (uint32)(rst_HsmVerInfo.hsmMinorVersion)<<8;
			rul_HsmVer|= (uint32)(rst_HsmVerInfo.hsmPatchVersion);

 		    if(rul_HsmVer>=FOTA_SUP_HSM_VER)
			{
 				/*****************************************/
 				/* User Should fill Mac Update code here */
 	            /* Mac Update OK : retVal = E_OK         */
 	            /* Mac Update NG : retVal = E_NOT_OK     */
 	            /*****************************************/










 		    	/*****************************************/
			}
 		    else /* in case of Not Support Version, It should return E_NOT_OK for fail of activation */
 		    {
 		    	jobResult = FOTA_JOB_FAILED_CALL_OUT;
 		    }
		}
	}
	else /* HSM is not working */
	{
		jobResult = FOTA_JOB_FAILED_CALL_OUT;
	}

#endif
#endif
	return jobResult;
}

#if ((MEM_76_PFLS_DISABLE_ECC_TRAP == STD_OFF) && \
     ((MEM_76_PFLS_SUPPORT_MCU == MEM_76_PFLS_MCU_TC39X) || \
     (MEM_76_PFLS_SUPPORT_MCU == MEM_76_PFLS_MCU_TC38X) || \
     (MEM_76_PFLS_SUPPORT_MCU == MEM_76_PFLS_MCU_TC37X) || \
     (MEM_76_PFLS_SUPPORT_MCU == MEM_76_PFLS_MCU_TC35X) || \
     (MEM_76_PFLS_SUPPORT_MCU == MEM_76_PFLS_MCU_TC36X) || \
     (MEM_76_PFLS_SUPPORT_MCU == MEM_76_PFLS_MCU_TC33X)))

#include "IfxCpu_reg.h"

#define FOTA_MCU_PASSWORDMASK                                          (uint16)0x003F
#define FOTA_MCU_SCUWDTCPUCON0_ENDINIT_OFF                                       (0u)
#define FOTA_MCU_SCUWDTCPUCON0_LCK_OFF                                           (1u)
#define FOTA_MCU_SCUWDTCPUCON0_PW_OFF                                            (2u)
#define FOTA_MCU_SCUWDTCPUCON0_REL_OFF                                          (16u)
#define FOTA_MCU_ONE                                                             (1U)
#define FOTA_MCU_ZERO                                                            (0U)

FUNC(void, DualM_CODE) Fota_Mcu_WdtClearCpuEndinit(void)
{
  uint16 ruw_Passwd;
  /* Fetch the password from the register */
  ruw_Passwd  = SCU_WDTCPU0_CON0.B.PW;
  /* Mask the password */
  ruw_Passwd ^= FOTA_MCU_PASSWORDMASK;

  if (FOTA_MCU_ZERO != SCU_WDTCPU0_CON0.B.LCK)
  {
    /* Password Access Bit Pattern operation */
    SCU_WDTCPU0_CON0.U = (uint32)((uint32)(FOTA_MCU_ONE << FOTA_MCU_SCUWDTCPUCON0_ENDINIT_OFF) |
                        (uint32)(FOTA_MCU_ZERO << FOTA_MCU_SCUWDTCPUCON0_LCK_OFF) |
                        (uint32)(ruw_Passwd << FOTA_MCU_SCUWDTCPUCON0_PW_OFF) |
                        (uint32)(SCU_WDTCPU0_CON0.B.REL << FOTA_MCU_SCUWDTCPUCON0_REL_OFF));
  }

  /* Clear ENDINT and set LCK bit in Config_0 register */
  SCU_WDTCPU0_CON0.U = (uint32)((uint32)(FOTA_MCU_ZERO << FOTA_MCU_SCUWDTCPUCON0_ENDINIT_OFF) |
                     (uint32)(FOTA_MCU_ONE << FOTA_MCU_SCUWDTCPUCON0_LCK_OFF) |
                     (uint32)(ruw_Passwd << FOTA_MCU_SCUWDTCPUCON0_PW_OFF) |
                     (uint32)(SCU_WDTCPU0_CON0.B.REL << FOTA_MCU_SCUWDTCPUCON0_REL_OFF));

  /* Read back ENDINIT and wait until it has been cleared */
  while (FOTA_MCU_ONE == SCU_WDTCPU0_CON0.B.ENDINIT){}
}

FUNC(void, DualM_CODE) Fota_Mcu_WdtSetCpuEndinit(void)
{
  uint16 ruw_Passwd;
  /* Fetch the password from the register */
  ruw_Passwd  = SCU_WDTCPU0_CON0.B.PW;
  /* Mask the password */
  ruw_Passwd ^= FOTA_MCU_PASSWORDMASK;

  if (FOTA_MCU_ZERO != SCU_WDTCPU0_CON0.B.LCK)
  {
    /* Password Access Bit Pattern operation */
    SCU_WDTCPU0_CON0.U = (uint32)((uint32)(FOTA_MCU_ONE << FOTA_MCU_SCUWDTCPUCON0_ENDINIT_OFF) |
                        (uint32)(FOTA_MCU_ZERO << FOTA_MCU_SCUWDTCPUCON0_LCK_OFF) |
                        (uint32)(ruw_Passwd << FOTA_MCU_SCUWDTCPUCON0_PW_OFF) |
                        (uint32)(SCU_WDTCPU0_CON0.B.REL << FOTA_MCU_SCUWDTCPUCON0_REL_OFF));
  }

  /* Set ENDINT and set LCK bit in Config_0 register */
  SCU_WDTCPU0_CON0.U = (uint32)((uint32)(FOTA_MCU_ONE << FOTA_MCU_SCUWDTCPUCON0_ENDINIT_OFF) |
                     (uint32)(FOTA_MCU_ONE << FOTA_MCU_SCUWDTCPUCON0_LCK_OFF) |
                     (uint32)(ruw_Passwd << FOTA_MCU_SCUWDTCPUCON0_PW_OFF) |
                     (uint32)(SCU_WDTCPU0_CON0.B.REL << FOTA_MCU_SCUWDTCPUCON0_REL_OFF));

  /* Read back ENDINIT and wait until it has been set */
  while (FOTA_MCU_ZERO == SCU_WDTCPU0_CON0.B.ENDINIT){}
}
#endif

FUNC(void, FOTA_CODE) Fota_BeforeFlashReadFunc(void)
{
#if (MEM_76_PFLS_DISABLE_ECC_TRAP == STD_OFF)

#if((MEM_76_PFLS_SUPPORT_MCU == MEM_76_PFLS_MCU_TC39X) || \
   (MEM_76_PFLS_SUPPORT_MCU == MEM_76_PFLS_MCU_TC38X) || \
   (MEM_76_PFLS_SUPPORT_MCU == MEM_76_PFLS_MCU_TC37X) || \
   (MEM_76_PFLS_SUPPORT_MCU == MEM_76_PFLS_MCU_TC35X) || \
   (MEM_76_PFLS_SUPPORT_MCU == MEM_76_PFLS_MCU_TC36X) || \
   (MEM_76_PFLS_SUPPORT_MCU == MEM_76_PFLS_MCU_TC33X))
uint32 eccControlValue;

Fota_Mcu_WdtClearCpuEndinit(); 

#if(MEM_76_PFLS_SUPPORT_MCU == MEM_76_PFLS_MCU_TC39X)
eccControlValue = (MEM_76_PFLS_CPU0_FLASHCON1.U & MEM_76_PFLS_MASKUECC_CLR);
eccControlValue = (eccControlValue | MEM_76_PFLS_MASKUECC_DIS);
MEM_76_PFLS_CPU0_FLASHCON1.U = eccControlValue;
eccControlValue = (MEM_76_PFLS_CPU1_FLASHCON1.U & MEM_76_PFLS_MASKUECC_CLR);
eccControlValue = (eccControlValue | MEM_76_PFLS_MASKUECC_DIS);
MEM_76_PFLS_CPU1_FLASHCON1.U = eccControlValue;
eccControlValue = (MEM_76_PFLS_CPU2_FLASHCON1.U & MEM_76_PFLS_MASKUECC_CLR);
eccControlValue = (eccControlValue | MEM_76_PFLS_MASKUECC_DIS);
MEM_76_PFLS_CPU2_FLASHCON1.U = eccControlValue;
eccControlValue = (MEM_76_PFLS_CPU3_FLASHCON1.U & MEM_76_PFLS_MASKUECC_CLR);
eccControlValue = (eccControlValue | MEM_76_PFLS_MASKUECC_DIS);
MEM_76_PFLS_CPU3_FLASHCON1.U = eccControlValue;
eccControlValue = (MEM_76_PFLS_CPU4_FLASHCON1.U & MEM_76_PFLS_MASKUECC_CLR);
eccControlValue = (eccControlValue | MEM_76_PFLS_MASKUECC_DIS);
MEM_76_PFLS_CPU4_FLASHCON1.U = eccControlValue;
eccControlValue = (MEM_76_PFLS_CPU5_FLASHCON1.U & MEM_76_PFLS_MASKUECC_CLR);
eccControlValue = (eccControlValue | MEM_76_PFLS_MASKUECC_DIS);
MEM_76_PFLS_CPU5_FLASHCON1.U = eccControlValue;
#elif(MEM_76_PFLS_SUPPORT_MCU == MEM_76_PFLS_MCU_TC38X)
eccControlValue = (MEM_76_PFLS_CPU0_FLASHCON1.U & MEM_76_PFLS_MASKUECC_CLR);
eccControlValue = (eccControlValue | MEM_76_PFLS_MASKUECC_DIS);
MEM_76_PFLS_CPU0_FLASHCON1.U = eccControlValue;
eccControlValue = (MEM_76_PFLS_CPU1_FLASHCON1.U & MEM_76_PFLS_MASKUECC_CLR);
eccControlValue = (eccControlValue | MEM_76_PFLS_MASKUECC_DIS);
MEM_76_PFLS_CPU1_FLASHCON1.U = eccControlValue;
eccControlValue = (MEM_76_PFLS_CPU2_FLASHCON1.U & MEM_76_PFLS_MASKUECC_CLR);
eccControlValue = (eccControlValue | MEM_76_PFLS_MASKUECC_DIS);
MEM_76_PFLS_CPU2_FLASHCON1.U = eccControlValue;
eccControlValue = (MEM_76_PFLS_CPU3_FLASHCON1.U & MEM_76_PFLS_MASKUECC_CLR);
eccControlValue = (eccControlValue | MEM_76_PFLS_MASKUECC_DIS);
MEM_76_PFLS_CPU3_FLASHCON1.U = eccControlValue;
#elif((MEM_76_PFLS_SUPPORT_MCU == MEM_76_PFLS_MCU_TC37X) || \
      (MEM_76_PFLS_SUPPORT_MCU == MEM_76_PFLS_MCU_TC35X))
eccControlValue = (MEM_76_PFLS_CPU0_FLASHCON1.U & MEM_76_PFLS_MASKUECC_CLR);
eccControlValue = (eccControlValue | MEM_76_PFLS_MASKUECC_DIS);
MEM_76_PFLS_CPU0_FLASHCON1.U = eccControlValue;
eccControlValue = (MEM_76_PFLS_CPU1_FLASHCON1.U & MEM_76_PFLS_MASKUECC_CLR);
eccControlValue = (eccControlValue | MEM_76_PFLS_MASKUECC_DIS);
MEM_76_PFLS_CPU1_FLASHCON1.U = eccControlValue;
eccControlValue = (MEM_76_PFLS_CPU2_FLASHCON1.U & MEM_76_PFLS_MASKUECC_CLR);
eccControlValue = (eccControlValue | MEM_76_PFLS_MASKUECC_DIS);
MEM_76_PFLS_CPU2_FLASHCON1.U = eccControlValue;
#elif(MEM_76_PFLS_SUPPORT_MCU == MEM_76_PFLS_MCU_TC36X)
eccControlValue = (MEM_76_PFLS_CPU0_FLASHCON1.U & MEM_76_PFLS_MASKUECC_CLR);
eccControlValue = (eccControlValue | MEM_76_PFLS_MASKUECC_DIS);
MEM_76_PFLS_CPU0_FLASHCON1.U = eccControlValue;
eccControlValue = (MEM_76_PFLS_CPU1_FLASHCON1.U & MEM_76_PFLS_MASKUECC_CLR);
eccControlValue = (eccControlValue | MEM_76_PFLS_MASKUECC_DIS);
MEM_76_PFLS_CPU1_FLASHCON1.U = eccControlValue;
#elif(MEM_76_PFLS_SUPPORT_MCU == MEM_76_PFLS_MCU_TC33X)
eccControlValue = (MEM_76_PFLS_CPU0_FLASHCON1.U & MEM_76_PFLS_MASKUECC_CLR);
eccControlValue = (eccControlValue | MEM_76_PFLS_MASKUECC_DIS);
MEM_76_PFLS_CPU0_FLASHCON1.U = eccControlValue;
#endif /* #if(MEM_76_PFLS_SUPPORT_MCU == MEM_76_PFLS_MCU_TC3XX) */

Fota_Mcu_WdtSetCpuEndinit();

#endif /* #if(MEM_76_PFLS_SUPPORT_MCU == MEM_76_PFLS_MCU_TC3XX) */

#endif /* #if (MEM_76_PFLS_DISABLE_ECC_TRAP == STD_OFF) */
}

FUNC(void, FOTA_CODE) Fota_AfterFlashReadFunc(void)
{
#if (MEM_76_PFLS_DISABLE_ECC_TRAP == STD_OFF)

#if((MEM_76_PFLS_SUPPORT_MCU == MEM_76_PFLS_MCU_TC39X) || \
   (MEM_76_PFLS_SUPPORT_MCU == MEM_76_PFLS_MCU_TC38X) || \
   (MEM_76_PFLS_SUPPORT_MCU == MEM_76_PFLS_MCU_TC37X) || \
   (MEM_76_PFLS_SUPPORT_MCU == MEM_76_PFLS_MCU_TC35X) || \
   (MEM_76_PFLS_SUPPORT_MCU == MEM_76_PFLS_MCU_TC36X) || \
   (MEM_76_PFLS_SUPPORT_MCU == MEM_76_PFLS_MCU_TC33X))
uint32 eccControlValue;

Fota_Mcu_WdtClearCpuEndinit(); 

#if(MEM_76_PFLS_SUPPORT_MCU == MEM_76_PFLS_MCU_TC39X)
eccControlValue = (MEM_76_PFLS_CPU0_FLASHCON1.U & MEM_76_PFLS_MASKUECC_CLR);
eccControlValue = (eccControlValue | MEM_76_PFLS_MASKUECC_EN);
MEM_76_PFLS_CPU0_FLASHCON1.U = eccControlValue;
eccControlValue = (MEM_76_PFLS_CPU1_FLASHCON1.U & MEM_76_PFLS_MASKUECC_CLR);
eccControlValue = (eccControlValue | MEM_76_PFLS_MASKUECC_EN);
MEM_76_PFLS_CPU1_FLASHCON1.U = eccControlValue;
eccControlValue = (MEM_76_PFLS_CPU2_FLASHCON1.U & MEM_76_PFLS_MASKUECC_CLR);
eccControlValue = (eccControlValue | MEM_76_PFLS_MASKUECC_EN);
MEM_76_PFLS_CPU2_FLASHCON1.U = eccControlValue;
eccControlValue = (MEM_76_PFLS_CPU3_FLASHCON1.U & MEM_76_PFLS_MASKUECC_CLR);
eccControlValue = (eccControlValue | MEM_76_PFLS_MASKUECC_EN);
MEM_76_PFLS_CPU3_FLASHCON1.U = eccControlValue;
eccControlValue = (MEM_76_PFLS_CPU4_FLASHCON1.U & MEM_76_PFLS_MASKUECC_CLR);
eccControlValue = (eccControlValue | MEM_76_PFLS_MASKUECC_EN);
MEM_76_PFLS_CPU4_FLASHCON1.U = eccControlValue;
eccControlValue = (MEM_76_PFLS_CPU5_FLASHCON1.U & MEM_76_PFLS_MASKUECC_CLR);
eccControlValue = (eccControlValue | MEM_76_PFLS_MASKUECC_EN);
MEM_76_PFLS_CPU5_FLASHCON1.U = eccControlValue;
#elif(MEM_76_PFLS_SUPPORT_MCU == MEM_76_PFLS_MCU_TC38X)
eccControlValue = (MEM_76_PFLS_CPU0_FLASHCON1.U & MEM_76_PFLS_MASKUECC_CLR);
eccControlValue = (eccControlValue | MEM_76_PFLS_MASKUECC_EN);
MEM_76_PFLS_CPU0_FLASHCON1.U = eccControlValue;
eccControlValue = (MEM_76_PFLS_CPU1_FLASHCON1.U & MEM_76_PFLS_MASKUECC_CLR);
eccControlValue = (eccControlValue | MEM_76_PFLS_MASKUECC_EN);
MEM_76_PFLS_CPU1_FLASHCON1.U = eccControlValue;
eccControlValue = (MEM_76_PFLS_CPU2_FLASHCON1.U & MEM_76_PFLS_MASKUECC_CLR);
eccControlValue = (eccControlValue | MEM_76_PFLS_MASKUECC_EN);
MEM_76_PFLS_CPU2_FLASHCON1.U = eccControlValue;
eccControlValue = (MEM_76_PFLS_CPU3_FLASHCON1.U & MEM_76_PFLS_MASKUECC_CLR);
eccControlValue = (eccControlValue | MEM_76_PFLS_MASKUECC_EN);
MEM_76_PFLS_CPU3_FLASHCON1.U = eccControlValue;
#elif((MEM_76_PFLS_SUPPORT_MCU == MEM_76_PFLS_MCU_TC37X) || \
      (MEM_76_PFLS_SUPPORT_MCU == MEM_76_PFLS_MCU_TC35X))
eccControlValue = (MEM_76_PFLS_CPU0_FLASHCON1.U & MEM_76_PFLS_MASKUECC_CLR);
eccControlValue = (eccControlValue | MEM_76_PFLS_MASKUECC_EN);
MEM_76_PFLS_CPU0_FLASHCON1.U = eccControlValue;
eccControlValue = (MEM_76_PFLS_CPU1_FLASHCON1.U & MEM_76_PFLS_MASKUECC_CLR);
eccControlValue = (eccControlValue | MEM_76_PFLS_MASKUECC_EN);
MEM_76_PFLS_CPU1_FLASHCON1.U = eccControlValue;
eccControlValue = (MEM_76_PFLS_CPU2_FLASHCON1.U & MEM_76_PFLS_MASKUECC_CLR);
eccControlValue = (eccControlValue | MEM_76_PFLS_MASKUECC_EN);
MEM_76_PFLS_CPU2_FLASHCON1.U = eccControlValue;
#elif(MEM_76_PFLS_SUPPORT_MCU == MEM_76_PFLS_MCU_TC36X)
eccControlValue = (MEM_76_PFLS_CPU0_FLASHCON1.U & MEM_76_PFLS_MASKUECC_CLR);
eccControlValue = (eccControlValue | MEM_76_PFLS_MASKUECC_EN);
MEM_76_PFLS_CPU0_FLASHCON1.U = eccControlValue;
eccControlValue = (MEM_76_PFLS_CPU1_FLASHCON1.U & MEM_76_PFLS_MASKUECC_CLR);
eccControlValue = (eccControlValue | MEM_76_PFLS_MASKUECC_EN);
MEM_76_PFLS_CPU1_FLASHCON1.U = eccControlValue;
#elif(MEM_76_PFLS_SUPPORT_MCU == MEM_76_PFLS_MCU_TC33X)
eccControlValue = (MEM_76_PFLS_CPU0_FLASHCON1.U & MEM_76_PFLS_MASKUECC_CLR);
eccControlValue = (eccControlValue | MEM_76_PFLS_MASKUECC_EN);
MEM_76_PFLS_CPU0_FLASHCON1.U = eccControlValue;
#endif /* #if(MEM_76_PFLS_SUPPORT_MCU == MEM_76_PFLS_MCU_TC3XX) */

Fota_Mcu_WdtSetCpuEndinit();

#endif /* #if(MEM_76_PFLS_SUPPORT_MCU == MEM_76_PFLS_MCU_TC3XX) */

#endif /* #if (MEM_76_PFLS_DISABLE_ECC_TRAP == STD_OFF) */
}

/* polyspace-begin MISRA-C3:2.7,8.13 [Justified:Low] "Not a defect" */

FUNC (Std_ReturnType, FOTA_CODE) Fota_ProcessReadActiveArea_UserCallout
(
  VAR(uint16, AUTOMATIC) InEcuSwUnit,
  VAR(uint8, AUTOMATIC) OpStatus,
  P2VAR(uint8, AUTOMATIC, FOTA_PRIVATE_DATA) LpOut_MemoryArea,
  P2VAR(uint8, AUTOMATIC, FOTA_PRIVATE_DATA) LpErrorCode
)
{
	/* if It is not used, LddRetVal should be E_NOT_OK */
  *LpErrorCode = DCM_E_REQUESTOUTOFRANGE;
  return (E_NOT_OK);

}

FUNC (Std_ReturnType, FOTA_CODE) Fota_ProcessActivate_UserCallout
(
  VAR(uint8, AUTOMATIC) InMemArea,
  VAR(uint16, AUTOMATIC) InEcuSwUnit,
  VAR(uint8, AUTOMATIC) OpStatus,
  P2VAR(uint8, AUTOMATIC, FOTA_PRIVATE_DATA) LpErrorCode
)
{
	/* if It is not used, LddRetVal should be E_OK */
  *LpErrorCode = DCM_E_REQUESTOUTOFRANGE;
  return (E_OK);
}

FUNC (Std_ReturnType, FOTA_CODE) Fota_ProcessEraseTargetArea_UserCallout
(
  VAR(uint8, AUTOMATIC) InMemArea,
  VAR(uint16, AUTOMATIC) InEcuSwUnit,
  VAR(uint8, AUTOMATIC) OpStatus,
  P2VAR(uint8, AUTOMATIC, FOTA_PRIVATE_DATA) LpOut_MemoryArea,
  P2VAR(uint8, AUTOMATIC, FOTA_PRIVATE_DATA) LpErrorCode
)
{
	/* if It is not used, LddRetVal should be E_NOT_OK */
  *LpErrorCode = DCM_E_REQUESTOUTOFRANGE;
  return (E_NOT_OK);
}

FUNC(Std_ReturnType, FOTA_CODE) Fota_ProcessRequestDownload_UserCallout
(
  Dcm_OpStatusType OpStatus,
  uint8 DataFormatIdentifier,
  uint32 MemoryAddress,
  uint32 MemorySize,
  P2VAR(uint32, AUTOMATIC, FOTA_PRIVATE_DATA) LpBlockLength,
  P2VAR(uint8, AUTOMATIC, FOTA_PRIVATE_DATA) LpErrorCode
)
{
	/* if It is not used, LddRetVal should be E_NOT_OK */
  *LpErrorCode = DCM_E_REQUESTOUTOFRANGE;
  return (E_NOT_OK);
}

FUNC(Dcm_ReturnWriteMemoryType, FOTA_CODE) Fota_ProcessTransferDataWrite_UserCallout
(
  Dcm_OpStatusType OpStatus,
  uint8 MemoryIdentifier /* Not Supported Argument */,
  uint32 MemoryAddress,
  uint32 MemoryWriteLen,
  P2CONST(uint8, AUTOMATIC, FOTA_PRIVATE_DATA) pWriteData
)
{
	/* if It is not used, LddRetVal should be E_NOT_OK */
  return (E_NOT_OK);
}

FUNC (Std_ReturnType, FOTA_CODE) Fota_ProcessRequestTransferExit_UserCallout
(
  Dcm_OpStatusType OpStatus,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) LpMemoryData,
  uint32* LulParameterRecordSize,
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, FOTA_PRIVATE_DATA)LpErrorCode
)
{
	/* if It is not used, LddRetVal should be E_NOT_OK */
  *LpErrorCode = DCM_E_REQUESTOUTOFRANGE;
  return (E_NOT_OK);
}

FUNC (Std_ReturnType, FOTA_CODE) Fota_ProcessVerify_UserCallout
(
  VAR(uint8, AUTOMATIC) InMemArea,
  VAR(uint16, AUTOMATIC) InEcuSwUnit,
  VAR(uint8, AUTOMATIC) OpStatus,
  P2VAR(uint8, AUTOMATIC, FOTA_PRIVATE_DATA) LpOut_MemoryArea,
  P2VAR(uint8, AUTOMATIC, FOTA_PRIVATE_DATA) LpErrorCode
)
{
	/* if It is not used, LddRetVal should be E_NOT_OK */
  *LpErrorCode = DCM_E_REQUESTOUTOFRANGE;
  return (E_NOT_OK);
}

FUNC (Std_ReturnType, FOTA_CODE) Fbl_SelectEntryPoint(
  P2VAR(uint32, AUTOMATIC, FOTA_PRIVATE_DATA) Lu32_EntryPointAddress)
{
  #if 0
  Std_ReturnType retVal = E_NOT_OK;
  *Lu32_EntryPointAddress = 0UL;
  #else
  Std_ReturnType retVal = E_OK;
  #endif
  /* user code */
  return (retVal);
}

/* Start Pfls user callout */
FUNC (void, FOTA_CODE) Fota_PflsInit_UserCallout
(
  P2VAR(boolean, AUTOMATIC, FOTA_PRIVATE_DATA) pPflsUserCalloutUse
)
{
	/* if It is not used, rub_PflsUserCalloutUse should be FALSE */
    *pPflsUserCalloutUse = FALSE;
}

FUNC (void, FOTA_CODE) Fota_PflsDeinit_UserCallout
(
  void
)
{
}

FUNC (Std_ReturnType, FOTA_CODE) Fota_PflsCancelReq_UserCallout
(
  VAR(uint32, AUTOMATIC) rul_MemoryInstance
)
{
	/* if It is not used, LddRetVal should be E_OK */
  FOTA_UNUSED(rul_MemoryInstance);
  return (E_OK);
}

FUNC(Std_ReturnType, FOTA_CODE) Fota_PflsEraseRequest_UserCallout
(
  VAR(uint32, AUTOMATIC) In_MemoryArea,
  VAR(uint32, AUTOMATIC) areaAddress,
  VAR(uint32, AUTOMATIC) eraseLen
)
{
	/* if It is not used, LddRetVal should be E_OK */
  FOTA_UNUSED(In_MemoryArea);
  FOTA_UNUSED(areaAddress);
  FOTA_UNUSED(eraseLen);
  return (E_OK);
}

FUNC(Std_ReturnType, FOTA_CODE) Fota_PflsWriteRequest_UserCallout
(
  VAR(uint32, AUTOMATIC) In_MemoryArea,
  VAR(uint32, AUTOMATIC) rul_WriteStartAddr,
  P2CONST(uint8, AUTOMATIC, FOTA_PRIVATE_DATA) rup_Write_buff,
  VAR(uint32, AUTOMATIC) rul_write_size
)
{
	/* if It is not used, LddRetVal should be E_OK */
  FOTA_UNUSED(In_MemoryArea);
  FOTA_UNUSED(rul_WriteStartAddr);
  FOTA_UNUSED(rup_Write_buff);
  FOTA_UNUSED(rul_write_size);
  return (E_OK);
}

FUNC (Std_ReturnType, FOTA_CODE) Fota_PflsReadRequest_UserCallout
(
  VAR(uint32, AUTOMATIC) In_MemoryArea,
  VAR(uint32, AUTOMATIC) rul_ReadStartAddr,
  P2VAR(uint8, AUTOMATIC, FOTA_PRIVATE_DATA) rup_Read_buff,
  VAR(uint32, AUTOMATIC) rul_read_size
)
{
	/* if It is not used, LddRetVal should be E_OK */
  FOTA_UNUSED(In_MemoryArea);
  FOTA_UNUSED(rul_ReadStartAddr);
  FOTA_UNUSED(rup_Read_buff);
  FOTA_UNUSED(rul_read_size);
  return (E_OK);
}

FUNC (Std_ReturnType, FOTA_CODE) Fota_PflsSwapBankRequest_UserCallout
(
  void
)
{
  /* if It is not used, LddRetVal should be E_OK */
  return (E_OK);
}

FUNC (Mem_76_Pfls_JobResultType_CallOut, FOTA_CODE) Fota_PflsGetJobResult_UserCallout
(
  VAR(uint32, AUTOMATIC) In_MemoryArea
)
{
	Mem_76_Pfls_JobResultType_CallOut jobResult;
  /* if It is not used, LddRetVal should be E_OK */
  FOTA_UNUSED(In_MemoryArea);
  jobResult = MEM_JOB_OK_CALL_OUT;
  return (jobResult);
}

FUNC (Std_ReturnType, FOTA_CODE) Fota_PflsGetActiveBank_UserCallout
(
  P2VAR(uint8, AUTOMATIC, FOTA_PRIVATE_DATA) pReadBank
)
{
  /* if It is not used, LddRetVal should be E_OK */
  FOTA_UNUSED(pReadBank);
  return (E_OK);
}

FUNC (Std_ReturnType, FOTA_CODE) Fota_PflsGetCovAddr_UserCallout
(
  VAR(uint32, AUTOMATIC) rul_MemoryInstance,
  VAR(Fota_HwSpSvAddrType_CallOut ,AUTOMATIC) ren_Fota_HwSpSvAddrType,
  P2VAR(uint32, AUTOMATIC, FOTA_PRIVATE_DATA) rup_StdAddr,
  P2VAR(uint32, AUTOMATIC, FOTA_PRIVATE_DATA) rup_length
)
{
  /* if It is not used, LddRetVal should be E_OK */
  FOTA_UNUSED(rul_MemoryInstance);
  FOTA_UNUSED(ren_Fota_HwSpSvAddrType);
  FOTA_UNUSED(rup_StdAddr);
  FOTA_UNUSED(rup_length);
  return (E_OK);
}

FUNC (Std_ReturnType, FOTA_CODE) Fota_PflsTgtAreaSet_UserCallout
(
  VAR(uint32, AUTOMATIC) rul_MemoryInstance,
  VAR(Fota_HwSpSvAddrType_CallOut, AUTOMATIC) rue_HwSpSvAddrType
)
{
  /* if It is not used, LddRetVal should be E_OK */
  FOTA_UNUSED(rul_MemoryInstance);
  FOTA_UNUSED(rue_HwSpSvAddrType);
  return (E_OK);
}

FUNC (Std_ReturnType, FOTA_CODE) Fota_PflsGetFlashAlignment_UserCallout
(
  VAR(uint32, AUTOMATIC) rul_MemoryInstance,
  P2VAR(uint32, AUTOMATIC, FOTA_PRIVATE_DATA) rup_AlineVal
)
{
  /* if It is not used, LddRetVal should be E_OK */
  FOTA_UNUSED(rul_MemoryInstance);
  FOTA_UNUSED(rup_AlineVal);
  return (E_OK);
}

FUNC (Std_ReturnType, FOTA_CODE) Fota_PflsGetSectorSize_UserCallout
(
  VAR(uint32, AUTOMATIC) rul_MemoryInstance,
  P2VAR(uint32, AUTOMATIC, FOTA_PRIVATE_DATA) rup_AlineVal,
  VAR(uint32, AUTOMATIC) address
)
{
  /* if It is not used, LddRetVal should be E_OK */
  FOTA_UNUSED(rul_MemoryInstance);
  FOTA_UNUSED(rup_AlineVal);
  FOTA_UNUSED(address);
  return (E_OK);
}
/* End Pfls user callout */

/* polyspace-end MISRA-C3:2.7,8.13 [Justified:Low] "Not a defect" */
/* polyspace-end MISRA-C3:20.9 [Justified:Low] "Not a defect" */

#endif /* #ifndef FOTA_INTEGRATION_SINGLEMEM_PLATFORM */
/*******************************************************************************
**                             End of File                                    **
*******************************************************************************/
