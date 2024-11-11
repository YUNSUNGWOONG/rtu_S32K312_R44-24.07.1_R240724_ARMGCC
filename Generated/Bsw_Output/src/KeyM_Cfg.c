/*******************************************************************************
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  This source code is permitted to be used only in projects contracted      **
**  with Hyundai Autoever, and any other use is prohibited.                   **
**  If you use it for other purposes or change the source code,               **
**  you may take legal responsibility.                                        **
**  In this case, There is no warranty and technical support.                 **
**                                                                            **
**  SRC-MODULE: KeyM_Cfg.c                                           **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR KEYM                                                  **
**                                                                            **
**  PURPOSE   : Define configuration datas                                    **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: yes                                       **
**                                                                            **
********************************************************************************

********************************************************************************
**                        Generation Tool Information                         **
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
**                        File Generation Information                         **
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

/*******************************************************************************
**                              Include Section                               **
*******************************************************************************/
/* polyspace-begin MISRA-C3:1.1 [Justified:Low] "KeyM shall support various primitive API. For this functionality, it needs a lot of MACRO for optimize source code." */

#include "Rte_KeyM.h"            /* Rte KeyM Header file */
#include "KeyM_Ram.h"            /* KeyM Ram Header file */


/*******************************************************************************
**                                Global Data                                 **
*******************************************************************************/
#define KEY1_NAME_LENGTH                     (4U)

#define KEY1_DATA_LENGTH                     (300U)


/*******************************************************************************
**                             Key Configuration                              **
*******************************************************************************/
#define KEYM_START_SEC_CONST_8
#include "MemMap.h"

/* Array contains name of key 1 */
static CONST(uint8, KEYM_CONFIG_DATA) KeyM_Key1_Name[KEY1_NAME_LENGTH] = \
{(uint8)'k', (uint8)'e', (uint8)'y', (uint8)'0'};

#define KEYM_STOP_SEC_CONST_8
#include "MemMap.h"

#define KEYM_START_SEC_VAR_CLEARED_8
#include "MemMap.h"

/* Array contains data of key 1 */
VAR(uint8, KEYM_VAR_CLEARED) KeyMCryptoKey_DummyKey[KEY1_DATA_LENGTH];

#define KEYM_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h"




#define KEYM_START_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h"

/* KeyM crypto key configuration array */
VAR(KeyM_CryptoKeyType, KEYM_VAR_INIT) KeyM_CryptoKey[KEYM_TOTAL_KEY] = \
{
  /* Key 1 */
  {
    /* Key name */
    &KeyM_Key1_Name[0u],
    /* Key name length */
    4U,
    /* Key Id */
    0U,
    /* Key data max length */
    300U,
    /* Key data */
    &KeyMCryptoKey_DummyKey[0u],
    /* Key data length */
    0U,
    /* Key generation type */
    KEYM_STORED_KEY,
    /* Key storage location */
    KEYM_STORAGE_IN_RAM,
    /* Csm source key id */
    0xFFFFFFFFU,
    /* Csm target key id */
    0U,
    /* Csm verify job */
    {
      0xFFFFFFFFU,
      KEYM_FALSE
    },
    /* Verify job type */
    KEYM_VERIFY_NO_TYPE,
    /* Key generation info */
    NULL_PTR,
    /* Length of Key generation info */
    0U,
    #if (KEYM_CRYPTO_KEY_ADDITIONAL_HINT_ENABLED == STD_ON)
    /* Additional hints to the crypto key */
    0xFF,
    #endif
    #if (KEYM_STORAGE_IN_NVM_ENABLED == STD_ON)
    /* NvM block Id */
    0xFFU,
    #endif
    #if (KEYM_CRYPTO_KEY_START_FINALIZE_FUNCTION_ENABLED == STD_ON)
    /* The flag indicates that the key has alternated */
    KEYM_FALSE,
    #endif
    /* The key state */
    0U
  }
};

#define KEYM_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h"


#if (KEYM_CERTIFICATE_MANAGER_ENABLED == STD_ON)
/*******************************************************************************
**                         Certificate Configuration                          **
*******************************************************************************/


































/* polyspace-end MISRA-C3:1.1 */
#endif
/*******************************************************************************
**                               End of File                                  **
*******************************************************************************/
