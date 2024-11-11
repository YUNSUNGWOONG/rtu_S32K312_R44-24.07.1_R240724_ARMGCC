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
*******************************************************************************/

#ifndef MEM_76_PFLS_USER_CALLOUTS_H
#define MEM_76_PFLS_USER_CALLOUTS_H

#define TC39x 1
#define S32K31x 2
#define PLATFORM TC39x

/*******************************************************************************
**                              Include Section                               **
*******************************************************************************/

#include "Std_Types.h"
/*******************************************************************************
**                            Global Data Types                               **
*******************************************************************************/
/* MCU MAIN PLL CLOCK - Mhz */
#define F1KM_MCU_MAIN_PLL_CLOCK                                             240
#define OMEN_BANKINFO_TYPE_A                                                (0xD3ADFA11UL)
#define OMEN_BANKINFO_TYPE_B                                                (0x2E130DA7UL)


/*******************************************************************************
**                        Global Function Declaration                         **
*******************************************************************************/
extern FUNC(Std_ReturnType, MEM_76_PFLS_CODE) Mem_76_Pfls_HwSecurityUnitTempStop_Callout(uint32 instanceID);
extern FUNC(Std_ReturnType, MEM_76_PFLS_CODE) Mem_76_Pfls_HwSecurityUnitRestart_Callout(uint32 instanceID);
extern FUNC(Std_ReturnType, MEM_76_PFLS_CODE) Mem_76_Pfls_CacheControlEnable_Callout(uint32 instanceID);
extern FUNC(Std_ReturnType, MEM_76_PFLS_CODE) Mem_76_Pfls_CacheControlDisable_Callout(uint32 instanceID);
extern FUNC(Std_ReturnType, MEM_76_PFLS_CODE) Mem_76_Pfls_GetNextBootActiveBank_Callout(uint32 *bankType);
extern FUNC(Std_ReturnType, MEM_76_PFLS_CODE) Mem_76_Pfls_SetNextBootActiveBank_Callout(uint32 bankType);
extern FUNC(Std_ReturnType, MEM_76_PFLS_CODE) Mem_76_Pfls_WaitObjResp_Callout(void);
#endif /* MEM_76_PFLS_USER_CALLOUTS_H */
/*******************************************************************************
**                                End of File                                 **
*******************************************************************************/
