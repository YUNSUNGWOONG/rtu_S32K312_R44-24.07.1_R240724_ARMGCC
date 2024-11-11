/*******************************************************************************
**                                                                            **
**  (C) 2022 HYUNDAI AUTOEVER Co., Ltd.                                       **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Fbl_Stub.h                                                    **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : BOOTLOADER                                                    **
**                                                                            **
**  PURPOSE   : Header file of Fbl_SharedCfg.c                                **
**                                                                            **
*******************************************************************************/
/*******************************************************************************
**                             Revision History                               **
********************************************************************************
** Revision  Date          By           Description                           **
********************************************************************************
** 1.0.0     17-Nov-2022   LinhTT36     Initial version                       **
*******************************************************************************/
#ifndef FBL_SHAREDCFG_H
#define FBL_SHAREDCFG_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Std_Types.h"
#include "Fota_User_Callouts.h"
#include "Dcm_Version.h"
#if (DCM_VERSION_AR_RELEASE_MAJOR_VERSION == 4U) && (DCM_VERSION_AR_RELEASE_MINOR_VERSION == 4U) /* DCM R44 */
  #include "Dcm_Externals.h"
#elif (DCM_VERSION_AR_RELEASE_MAJOR_VERSION == 4U) && (DCM_VERSION_AR_RELEASE_MINOR_VERSION == 0U) /* DCM R40 */
  #include "Dcm_Callouts.h"
#else
  #error "Fota and Dcm_Version : Mismatch in Specification Major Version"
#endif
#ifndef FOTA_INTEGRATION_SINGLEMEM_PLATFORM
  #include "Fota_Cfg.h"
#endif /* #ifndef FOTA_INTEGRATION_SINGLEMEM_PLATFORM */
/*******************************************************************************
**                      Macro definition                                     **
*******************************************************************************/

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/




/*******************************************************************************
**                      Macro definition                                     **
*******************************************************************************/
/**
 * Shared definition information
 */
 



#define FBL_SHARED_DATA_ADDR                                      (0x80000030UL)

/* polyspace-begin CERT-C:EXP39-C, MISRA-C3:11.3,11.4 [Justified:Medium] "The integer value represents the register address. It should be casted to an address so that
 * the register value can be read via the address" */
/* Macros to access 'Common RAM' elements */
#define FBL_COMMON_RAM_PTR                    ((uint32 *)FBL_COMMON_RAM_ADDRESS)
/* Macro to get startup command address */
#define FBL_STARTUP_COMMAND_PTR           ((uint32*)FBL_STARTUP_COMMAND_ADDRESS)
/* polyspace-end CERT-C:EXP39-C, MISRA-C3:11.3,11.4 [Justified:Medium] "The integer value represents the register address. It should be casted to an address so that
 * the register value can be read via the address" */



/*******************************************************************************
**                        Global Function Declaration                         **
*******************************************************************************/
/* polyspace-begin MISRA-C3:20.7 [Not a defect:Low] "No Impact of this rule violation" */
extern FUNC(void,FOTA_CODE) Fbl_SetStartupCommand(VAR(uint32,FOTA_CODE) command);
extern FUNC(Dcm_McuDepProgConditionsType*, FOTA_CODE) Fbl_GetProgConditionsAddress(void);
/* polyspace-end MISRA-C3:20.7 [Not a defect:Low] "No Impact of this rule violation" */

#endif
/*******************************************************************************
**                                End of File                                 **
*******************************************************************************/
