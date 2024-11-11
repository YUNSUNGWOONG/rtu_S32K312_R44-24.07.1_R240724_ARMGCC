/*******************************************************************************
**                                                                            **
**  (C) 2019 HYUNDAI AUTRON Co., Ltd.                                         **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Fota_BootManager.h                                            **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR FOTA                                                  **
**                                                                            **
**  PURPOSE   : Manage boot software unit                                     **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                             Revision History                               **
********************************************************************************
** Revision  Date          By           Description                           **
********************************************************************************
** 1.0.0     23-Dec-2022   VuPH6        Initial version                       **
*******************************************************************************/

#ifndef FOTA_BOOTMANAGER_H
#define FOTA_BOOTMANAGER_H

/*******************************************************************************
**                              Include Section                               **
*******************************************************************************/
#include "Std_Types.h"
#include "Fota_User_Callouts.h"

#ifndef FOTA_INTEGRATION_SINGLEMEM_PLATFORM

#include "Fota_IntTypes.h"
#include "Mem_76_Pfls.h"
/*******************************************************************************
**                      Macros                                                **
*******************************************************************************/
#define FOTA_BUFF_SIZE_ONE                                                    1U

//#define __LD_BTL_RS_ADDR 0
//#define __LD_BTL_RS_SIZE 10

/* polyspace-begin CERT-C:DCL37-C,EXP39-C,INT36-C, MISRA-C3:8.6,11.3,21.2 [Justified:Low] "These symbols are
 * referred from[and allocated by] linker" */
#if (FOTA_MODE == FOTA_FBL_MODE)
#define Fota_Gau32_BTLResetSaveData                             __LD_BTL_RS_ADDR
#define Fota_Gpu32_BTLResetSaveDataSize                         __LD_BTL_RS_SIZE
#endif

/*******************************************************************************
**                             Global Variables                               **
*******************************************************************************/
/* Do not add memory placement tags here, these symbols are
 * referred from[and allocated by] linker, Placement is taken care
 * by linker
 */
extern uint32 Fota_Gau32_BTLResetSaveData[FOTA_BUFF_SIZE_ONE];
extern uint32 *Fota_Gpu32_BTLResetSaveDataSize;
/* polyspace-end CERT-C:DCL37-C,EXP39-C,INT36-C, MISRA-C3:8.6,11.3,21.2 [Justified:Low] "These symbols are
 * referred from[and allocated by] linker" */


/*******************************************************************************
**                      Types                                                 **
*******************************************************************************/



/*******************************************************************************
**                        Global Function Declaration                         **
*******************************************************************************/
#define Fota_START_SEC_CODE
#include "Fota_MemMap.h"

#if FOTA_BOOT_MANAGER_USED
extern FUNC(void, FOTA_CODE) Fota_BootManager(void);
#endif

#define Fota_STOP_SEC_CODE
#include "Fota_MemMap.h"

#endif /* #ifndef FOTA_INTEGRATION_SINGLEMEM_PLATFORM */

#endif /* FOTA_BOOTMANAGER_H */
/*******************************************************************************
**                                End of File                                 **
*******************************************************************************/
