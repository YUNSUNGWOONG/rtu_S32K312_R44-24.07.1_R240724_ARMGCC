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
*******************************************************************************/

#ifndef FOTA_CALLOUT_FIXED_H
#define FOTA_CALLOUT_FIXED_H
/*******************************************************************************
**                              Include Section                               **
*******************************************************************************/

#include "Fota_User_Callouts.h"

#ifndef FOTA_INTEGRATION_SINGLEMEM_PLATFORM

#include "Std_Types.h"
#include "HwResource.h"

/* polyspace-begin MISRA-C3:20.9 [Justified:Low] "Not a defect" */
/*******************************************************************************
**                            Global Data Types                               **
*******************************************************************************/


/*******************************************************************************
**                             Macro Definition                               **
*******************************************************************************/
#if (HWRESOURCE_FAMILY(HWRESOURCE_CYT2BXX)) || (HWRESOURCE_FAMILY(HWRESOURCE_CYT4BXX)) || \
    (HWRESOURCE_FAMILY(HWRESOURCE_CYT6BXX))

/* polyspace-begin MISRA-C3:D4.9 [Justified:Low] "use function like-macro for reduce execution time and stack" */
/* polyspace-begin MISRA-C3:11.4 [Justified:Low] "The integer value represents the register address. It should be casted to an address so that
* the register value can be read via the address" */
#define FOTA_REG(ADDR)                                             (*(volatile uint32 *)(ADDR))
/* polyspace-end MISRA-C3:D4.9 [Justified:Low] "use function like-macro for reduce execution time and stack" */
/* polyspace-end MISRA-C3:11.4 [Justified:Low] "The integer value represents the register address. It should be casted to an address so that
* the register value can be read via the address" */

#define FOTA_FLASHC                                                      ((uint32)0x40240000UL)
#define FOTA_FLASHC_FLASH_CTL                                            ((uint32)0x40240000UL)
#define FOTA_FLASHC_FLASH_CMD                                            ((uint32)0x40240408UL)
#define FOTA_FLASHC_CM0_CA_CTL0                                          ((uint32)0x40240400UL)
#define FOTA_MAIN_FLASH_SAFETY                                           ((uint32)0x4024F400UL)
#define FOTA_FAULT_STRUCT3_MASK1                                         ((uint32)0x40210354UL)

#define FOTA_FLASHC_CM0_CA_CTL0_CA_EN_MASK                               ((uint32)0x80000000UL)
#define FOTA_FLASHC_FLASH_CMD_INV_MASK                                   ((uint32)0x80000000UL)
#define FOTA_FLASHC_FLASH_CTL_MAIN_ERR_SILENT_MASK                       ((uint32)0x00040000UL)
#define FOTA_FLASHC_FLASH_CTL_MAIN_BANK_MODE_MASK                        ((uint32)0x00001000UL)
#define FOTA_FLASHC_FLASH_CTL_MAIN_MAP_MASK                              ((uint32)0x00000100UL)

#endif  /* HWRESOURCE_FAMILY */

/*******************************************************************************
**                        Global Function Declaration                         **
*******************************************************************************/
extern FUNC(void, FOTA_CODE) Fota_PrepareForApplEntry(void);

/* polyspace-end MISRA-C3:20.9 [Justified:Low] "Not a defect" */
#endif /* #ifndef FOTA_INTEGRATION_SINGLEMEM_PLATFORM */
#endif /* FOTA_CALLOUT_FIXED_H */
/*******************************************************************************
**                                End of File                                 **
*******************************************************************************/
