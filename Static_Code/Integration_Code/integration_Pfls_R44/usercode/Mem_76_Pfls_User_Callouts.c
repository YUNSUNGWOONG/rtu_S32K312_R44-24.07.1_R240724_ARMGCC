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
**                                                                         **
*******************************************************************************/

/*******************************************************************************
**                              Include Section                               **
*******************************************************************************/
/* polyspace-begin MISRA-C3:20.9 [Justified:Low] "Not a defect" */
#include "Mem_76_Pfls_User_Callouts.h"
#include "Std_Types.h"
#include "Mem_76_Pfls.h"
#include "Mem_76_Pfls_Cfg.h"
#include "Csm.h"
#include "Fota_Cfg.h"

#if (FOTA_STD_ON == FOTA_SF20_ENABLE)
#if (HWRESOURCE_VENDOR(HWRESOURCE_NXP))
  #include "Cache_Setup.h"
  #include "Crypto_Cfg.h"
  #include "Crypto_ASRExtension.h"
#else
#include "HKMC_SecureFlash2.h"
  #if (HWRESOURCE_FAMILY(HWRESOURCE_TC39X) || HWRESOURCE_FAMILY(HWRESOURCE_TC38X) ||\
    HWRESOURCE_FAMILY(HWRESOURCE_TC37X) || HWRESOURCE_FAMILY(HWRESOURCE_TC36X)    ||\
    HWRESOURCE_FAMILY(HWRESOURCE_TC33X) || HWRESOURCE_FAMILY(HWRESOURCE_TC29X)    ||\
    HWRESOURCE_FAMILY(HWRESOURCE_TC27X) || HWRESOURCE_FAMILY(HWRESOURCE_TC23X)    ||\
    HWRESOURCE_FAMILY(HWRESOURCE_SPC58XH) || HWRESOURCE_FAMILY(HWRESOURCE_SPC58XC)||\
    (HWRESOURCE_FAMILY(HWRESOURCE_SPC58XB) && HWRESOURCE_MCU(HWRESOURCE_SPC584B)) ||\
    (HWRESOURCE_FAMILY(HWRESOURCE_CYT2BXX) && (HWRESOURCE_MCU(HWRESOURCE_CYT2B9XX)||\
                                              HWRESOURCE_MCU(HWRESOURCE_CYT2BLXX))) ||\
    (HWRESOURCE_FAMILY(HWRESOURCE_CYT3BXX) && HWRESOURCE_MCU(HWRESOURCE_CYT3BBXX)) ||\
    (HWRESOURCE_FAMILY(HWRESOURCE_CYT4BXX) && (HWRESOURCE_MCU(HWRESOURCE_CYT4BBXX) ||\
                                              HWRESOURCE_MCU(HWRESOURCE_CYT4BFXX))) ||\
    (HWRESOURCE_FAMILY(HWRESOURCE_CYT6BXX) && HWRESOURCE_MCU(HWRESOURCE_CYT6BJXX)) ||\
    (HWRESOURCE_FAMILY(HWRESOURCE_RH850F1X) && HWRESOURCE_MCU(HWRESOURCE_RH850F1KM)))
  #include "Hsm_HostAPI.h"
  #endif
#endif
#endif
/* polyspace-begin MISRA-C3:2.2 [Justified:Low] "if-condition depends on the configuration." */

/*******************************************************************************
**                             Macro Definition                               **
*******************************************************************************/

/*******************************************************************************
**                            Global Data Types                               **
*******************************************************************************/

/*******************************************************************************
**                              Global Data                                   **
*******************************************************************************/
#if (FOTA_STD_ON == FOTA_SF20_ENABLE)
#if ((HWRESOURCE_FAMILY(HWRESOURCE_CYT2BXX) && (HWRESOURCE_MCU(HWRESOURCE_CYT2B9XX)||\
                                              HWRESOURCE_MCU(HWRESOURCE_CYT2BLXX))) ||\
    (HWRESOURCE_FAMILY(HWRESOURCE_CYT3BXX) && HWRESOURCE_MCU(HWRESOURCE_CYT3BBXX)) ||\
    (HWRESOURCE_FAMILY(HWRESOURCE_CYT4BXX) && (HWRESOURCE_MCU(HWRESOURCE_CYT4BBXX) ||\
                                              HWRESOURCE_MCU(HWRESOURCE_CYT4BFXX))) ||\
    (HWRESOURCE_FAMILY(HWRESOURCE_CYT6BXX) && HWRESOURCE_MCU(HWRESOURCE_CYT6BJXX)))

static HSMAPI_OBJ_t apiobj;
#endif /* HWRESOURCE_FAMILY */
#endif /* FOTA_STD_ON == FOTA_SF20_ENABLE */

/*******************************************************************************
**                          Function Definitions                              **
*******************************************************************************/
#if (FOTA_STD_ON == FOTA_SF20_ENABLE)
#if ((HWRESOURCE_FAMILY(HWRESOURCE_CYT2BXX) && (HWRESOURCE_MCU(HWRESOURCE_CYT2B9XX)||\
                                               HWRESOURCE_MCU(HWRESOURCE_CYT2BLXX))) ||\
    (HWRESOURCE_FAMILY(HWRESOURCE_CYT3BXX) && HWRESOURCE_MCU(HWRESOURCE_CYT3BBXX)) ||\
    (HWRESOURCE_FAMILY(HWRESOURCE_CYT4BXX) && (HWRESOURCE_MCU(HWRESOURCE_CYT4BBXX) ||\
                                               HWRESOURCE_MCU(HWRESOURCE_CYT4BFXX))) ||\
    (HWRESOURCE_FAMILY(HWRESOURCE_CYT6BXX) && HWRESOURCE_MCU(HWRESOURCE_CYT6BJXX)))
Std_ReturnType HSM_BbmGetNextBootActiveBank(HSMAPI_OBJ_t *apiObj, uint32 *bankType);
Std_ReturnType HSM_BbmSetNextBootActiveBank(HSMAPI_OBJ_t *apiObj, uint32 bankType);
Std_ReturnType HSM_WaitObjResp(HSMAPI_OBJ_t *apiObj);
#endif /* HWRESOURCE_FAMILY */
#endif /* FOTA_STD_ON == FOTA_SF20_ENABLE */

/* polyspace-begin MISRA-C3:2.7 [Justified:Low] "Not a defect" */
FUNC(Std_ReturnType, MEM_76_PFLS_CODE) Mem_76_Pfls_HwSecurityUnitTempStop_Callout(uint32 instanceID)
/* polyspace-end MISRA-C3:2.7 [Justified:Low] "Not a defect" */
{
  Std_ReturnType retVal;

  retVal = E_OK;
  #if (FOTA_STD_ON == FOTA_SF20_ENABLE)
  #if (HWRESOURCE_FAMILY(HWRESOURCE_TC39X) || HWRESOURCE_FAMILY(HWRESOURCE_TC38X) ||\
    HWRESOURCE_FAMILY(HWRESOURCE_TC37X) || HWRESOURCE_FAMILY(HWRESOURCE_TC36X)    ||\
    HWRESOURCE_FAMILY(HWRESOURCE_TC33X) || HWRESOURCE_FAMILY(HWRESOURCE_TC29X)    ||\
    HWRESOURCE_FAMILY(HWRESOURCE_TC27X) || HWRESOURCE_FAMILY(HWRESOURCE_TC23X)    ||\
    HWRESOURCE_FAMILY(HWRESOURCE_SPC58XH) || HWRESOURCE_FAMILY(HWRESOURCE_SPC58XC)||\
    (HWRESOURCE_FAMILY(HWRESOURCE_SPC58XB) && HWRESOURCE_MCU(HWRESOURCE_SPC584B)) ||\
    (HWRESOURCE_FAMILY(HWRESOURCE_CYT2BXX) && (HWRESOURCE_MCU(HWRESOURCE_CYT2B9XX)||\
                                              HWRESOURCE_MCU(HWRESOURCE_CYT2BLXX))) ||\
    (HWRESOURCE_FAMILY(HWRESOURCE_CYT3BXX) && HWRESOURCE_MCU(HWRESOURCE_CYT3BBXX)) ||\
    (HWRESOURCE_FAMILY(HWRESOURCE_CYT4BXX) && (HWRESOURCE_MCU(HWRESOURCE_CYT4BBXX) ||\
                                              HWRESOURCE_MCU(HWRESOURCE_CYT4BFXX))) ||\
    (HWRESOURCE_FAMILY(HWRESOURCE_CYT6BXX) && HWRESOURCE_MCU(HWRESOURCE_CYT6BJXX)) ||\
    (HWRESOURCE_FAMILY(HWRESOURCE_RH850F1X) && HWRESOURCE_MCU(HWRESOURCE_RH850F1KM)))
    if(HSM_CheckHsmTempStopState()==TRUE) /* TempStop State */
    {
      /*@Sec_Gbl_HsmTempStopRetValue = E_OK;*/
      retVal = E_OK;
    }
    else                                  /* Restart State */
    {
      /*@Sec_Gbl_HsmTempStopRetValue = E_NOT_OK;*/
      retVal = HSM_TempStop();
    }

  #endif
  #endif

  return retVal;
}

/* polyspace-begin MISRA-C3:2.7 [Justified:Low] "Not a defect" */
FUNC(Std_ReturnType, MEM_76_PFLS_CODE) Mem_76_Pfls_HwSecurityUnitRestart_Callout(uint32 instanceID)
/* polyspace-end MISRA-C3:2.7 [Justified:Low] "Not a defect" */
{
  Std_ReturnType retVal;

  retVal = E_OK;
  #if (FOTA_STD_ON == FOTA_SF20_ENABLE)
  #if (HWRESOURCE_FAMILY(HWRESOURCE_TC39X) || HWRESOURCE_FAMILY(HWRESOURCE_TC38X) ||\
    HWRESOURCE_FAMILY(HWRESOURCE_TC37X) || HWRESOURCE_FAMILY(HWRESOURCE_TC36X)    ||\
    HWRESOURCE_FAMILY(HWRESOURCE_TC33X) || HWRESOURCE_FAMILY(HWRESOURCE_TC29X)    ||\
    HWRESOURCE_FAMILY(HWRESOURCE_TC27X) || HWRESOURCE_FAMILY(HWRESOURCE_TC23X)    ||\
    HWRESOURCE_FAMILY(HWRESOURCE_SPC58XH) || HWRESOURCE_FAMILY(HWRESOURCE_SPC58XC)||\
    (HWRESOURCE_FAMILY(HWRESOURCE_SPC58XB) && HWRESOURCE_MCU(HWRESOURCE_SPC584B)) ||\
    (HWRESOURCE_FAMILY(HWRESOURCE_CYT2BXX) && (HWRESOURCE_MCU(HWRESOURCE_CYT2B9XX)||\
                                              HWRESOURCE_MCU(HWRESOURCE_CYT2BLXX))) ||\
    (HWRESOURCE_FAMILY(HWRESOURCE_CYT3BXX) && HWRESOURCE_MCU(HWRESOURCE_CYT3BBXX)) ||\
    (HWRESOURCE_FAMILY(HWRESOURCE_CYT4BXX) && (HWRESOURCE_MCU(HWRESOURCE_CYT4BBXX) ||\
                                              HWRESOURCE_MCU(HWRESOURCE_CYT4BFXX))) ||\
    (HWRESOURCE_FAMILY(HWRESOURCE_CYT6BXX) && HWRESOURCE_MCU(HWRESOURCE_CYT6BJXX)) ||\
    (HWRESOURCE_FAMILY(HWRESOURCE_RH850F1X) && HWRESOURCE_MCU(HWRESOURCE_RH850F1KM)))
    if(HSM_CheckHsmTempStopState()==FALSE) /* Restart State */
    {
      /*@Sec_Gbl_HsmRestartRetValue = E_OK;*/
      retVal = E_OK;
    }
    else								   /* TempStop State */
    {
      /*@Sec_Gbl_HsmRestartRetValue = E_NOT_OK;*/
      retVal = HSM_Restart();
    }

  #endif
  #endif

  return retVal;
}
/* polyspace-begin MISRA-C3:2.7 [Justified:Low] "Not a defect" */
FUNC(Std_ReturnType, MEM_76_PFLS_CODE) Mem_76_Pfls_CacheControlEnable_Callout(uint32 instanceID)
/* polyspace-end MISRA-C3:2.7 [Justified:Low] "Not a defect" */
{
  Std_ReturnType retVal;

  retVal = E_OK;
#if(MOBILGENE_S32K312_CACHE_ID)
  User_Cache_Init();
#endif
  return retVal;
}
/* polyspace-begin MISRA-C3:2.7 [Justified:Low] "Not a defect" */
FUNC(Std_ReturnType, MEM_76_PFLS_CODE) Mem_76_Pfls_CacheControlDisable_Callout(uint32 instanceID)
/* polyspace-end MISRA-C3:2.7 [Justified:Low] "Not a defect" */
{
  Std_ReturnType retVal;

  retVal = E_OK;
#if(MOBILGENE_S32K312_CACHE_ID)
  User_Cache_DeInit();
#endif
  return retVal;
}

#if (FOTA_STD_ON == FOTA_SF20_ENABLE)
#if ((HWRESOURCE_FAMILY(HWRESOURCE_CYT2BXX) && (HWRESOURCE_MCU(HWRESOURCE_CYT2B9XX)||\
                                              HWRESOURCE_MCU(HWRESOURCE_CYT2BLXX))) ||\
    (HWRESOURCE_FAMILY(HWRESOURCE_CYT3BXX) && HWRESOURCE_MCU(HWRESOURCE_CYT3BBXX)) ||\
    (HWRESOURCE_FAMILY(HWRESOURCE_CYT4BXX) && (HWRESOURCE_MCU(HWRESOURCE_CYT4BBXX) ||\
                                              HWRESOURCE_MCU(HWRESOURCE_CYT4BFXX))) ||\
    (HWRESOURCE_FAMILY(HWRESOURCE_CYT6BXX) && (HWRESOURCE_MCU(HWRESOURCE_CYT6BJXX))))
FUNC(Std_ReturnType, MEM_76_PFLS_CODE) Mem_76_Pfls_GetNextBootActiveBank_Callout(uint32 *bankType)
{
  Std_ReturnType retVal;

  retVal = HSM_BbmGetNextBootActiveBank(&apiobj, bankType);

  return retVal;
}
FUNC(Std_ReturnType, MEM_76_PFLS_CODE) Mem_76_Pfls_SetNextBootActiveBank_Callout(uint32 bankType)
{
  Std_ReturnType retVal;

  retVal = HSM_BbmSetNextBootActiveBank(&apiobj, bankType);

  return retVal;
}
FUNC(Std_ReturnType, MEM_76_PFLS_CODE) Mem_76_Pfls_WaitObjResp_Callout(void)
{
  Std_ReturnType retVal;

  retVal = HSM_WaitObjResp(&apiobj);

  return retVal;
}
#endif /* HWRESOURCE_FAMILY */
#endif /* FOTA_STD_ON == FOTA_SF20_ENABLE */

/* polyspace-end MISRA-C3:2.2 [Justified:Low] "if-condition depends on the configuration." */
/* polyspace-end MISRA-C3:20.9 [Justified:Low] "Not a defect" */

/*******************************************************************************
**                             End of File                                    **
*******************************************************************************/
