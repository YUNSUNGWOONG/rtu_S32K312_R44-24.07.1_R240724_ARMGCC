/*******************************************************************************
**                                                                            **
**  (C) 2022 HYUNDAI AUTOEVER Co., Ltd.                                       **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE:                                                               **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : BOOTLOADER                                                    **
**                                                                            **
**  PURPOSE   :                                                               **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                             Revision History                               **
********************************************************************************
** Revision  Date          By           Description                           **
********************************************************************************
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                              Include Section                               **
*******************************************************************************/
/* polyspace-begin MISRA-C3:20.9 [Justified:Low] "Not a defect" */
#include "Fota_User_Callouts.h"

#ifndef FOTA_INTEGRATION_SINGLEMEM_PLATFORM

#include "Fota_IntTypes.h"
#include "Fota_Globals.h"

#include "Fota_Callout_Fixed.h"
#include "Fota_PflsInterface.h"
#include "Fota_NonMmuSubFunc.h"

#if (HWRESOURCE_FAMILY(HWRESOURCE_CYT2BXX)) || (HWRESOURCE_FAMILY(HWRESOURCE_CYT4BXX)) || \
    (HWRESOURCE_FAMILY(HWRESOURCE_CYT6BXX))
#include "arm_ghs.h"
#endif

/*******************************************************************************
**                             Macro Definition                               **
*******************************************************************************/

/*******************************************************************************
**                            Global Data Types                               **
*******************************************************************************/

/*******************************************************************************
**                              Global Data                                   **
*******************************************************************************/

/*******************************************************************************
**                          Function Definitions                              **
*******************************************************************************/
#if FOTA_BOOT_MANAGER_USED

/*******************************************************************************
** Function Name        : Fota_FlashInit                                      **
**                                                                            **
** Description          : Function Initializing Flash.                        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
********************************************************************************/
static FUNC(void, FOTA_CODE) Fota_FlashInit(void)
{
#if (HWRESOURCE_FAMILY(HWRESOURCE_CYT2BXX)) || (HWRESOURCE_FAMILY(HWRESOURCE_CYT4BXX)) || \
    (HWRESOURCE_FAMILY(HWRESOURCE_CYT6BXX))
  /*Enable writting main flash*/
  FOTA_REG(FOTA_MAIN_FLASH_SAFETY) = 1U;
  /*Disables CM0 cache*/
  FOTA_REG(FOTA_FLASHC_CM0_CA_CTL0) &= ~FOTA_FLASHC_CM0_CA_CTL0_CA_EN_MASK; /* CA_EN = 0U */
  /*Invalidates the flash cache and buffer*/
  FOTA_REG(FOTA_FLASHC_FLASH_CMD) |= FOTA_FLASHC_FLASH_CMD_INV_MASK; /* INV = 1U */
  /* Setting the Silent mode for avoid bus error (Hard Fault) */
  FOTA_REG(FOTA_FLASHC_FLASH_CTL) &= ~FOTA_FLASHC_FLASH_CTL_MAIN_ERR_SILENT_MASK; /* MAIN_ERR_SILENT = 0UL */
#else

#endif
}

/*******************************************************************************
** Function Name        : Fota_PrepareForApplEntry                            **
**                                                                            **
** Description          : The Fota_PrepareForApplEntry API is called just     **
**                        before entering to valid application.               **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
*******************************************************************************/
FUNC(void, FOTA_CODE) Fota_PrepareForApplEntry(void)
{
  /* Initializing Flash. */
  /* polyspace-begin MISRA-C3:2.2 [Justified:Low] "if-condition depends on the MCU." */
  Fota_FlashInit();
  /* polyspace-end MISRA-C3:2.2 [Justified:Low] "if-condition depends on the MCU." */
  
#if (HWRESOURCE_FAMILY(HWRESOURCE_CYT2BXX)) || (HWRESOURCE_FAMILY(HWRESOURCE_CYT4BXX)) || \
    (HWRESOURCE_FAMILY(HWRESOURCE_CYT6BXX))
  /* Disable ECC ERROR Interrupt for Jump RTSW*/
  FOTA_REG(FOTA_FAULT_STRUCT3_MASK1) = 0x00000000UL;

  /* Set PRIMASK to 0 (Initial Value) for jump RTSW
   * Enable Interrupts(instruction is equivalent to writing a 0 into PRIMASK)
   * It should be located before Icu_SetMode(), because ICU ISR should be
   * executed before peripheral flag cleared by Icu_SetMode()
   */
  __CPS(__CPS_ENABLE, __CPS_I, __CPS_DEFAULT);
  __asm("isb");
#else

#endif
}

#endif /* FOTA_BOOT_MANAGER_USED */

#endif /* #ifndef FOTA_INTEGRATION_SINGLEMEM_PLATFORM */

/* polyspace-end MISRA-C3:20.9 [Justified:Low] "Not a defect" */
/*******************************************************************************
**                             End of File                                    **
*******************************************************************************/
