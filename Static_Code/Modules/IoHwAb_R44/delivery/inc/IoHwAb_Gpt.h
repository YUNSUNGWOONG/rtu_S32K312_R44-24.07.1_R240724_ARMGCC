/*******************************************************************************
**                                                                            **
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  This source code is permitted to be used only in projects contracted      **
**  with Hyundai Autoever, and any other use is prohibited.                   **
**  If you use it for other purposes or change the source code,               **
**  you may take legal responsibility.                                        **
**  In this case, There is no warranty and technical support.                 **
**                                                                            **
**  SRC-MODULE: IoHwAb_Gpt.h                                                  **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR IOHWAB                                                **
**                                                                            **
**  PURPOSE   : C header for IoHwAb Gpt                                       **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By               Description                       **
********************************************************************************
** 1.3.0.1   30-Jun-2022  KhaLN1            #CP44-365                         **
** 1.0.0     04-Dec-2020  YangJin.Kim       R40-Redmine #26992                **
*******************************************************************************/

#ifndef IOHWAB_GPT_H
#define IOHWAB_GPT_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "IoHwAb.h"

#if defined(IOHWAB_MCAL_FREESCALE_MPC560XB)
#include "Reg_eSys_Pit.h"
#include "Gpt_Cfg.h"
#endif /* defined(IOHWAB_MCAL_FREESCALE_MPC560XB) */

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
/* #if (IOHWAB_USE_GPT == STD_ON) */
/* #endif */

#if defined(IOHWAB_MCAL_FREESCALE_MPC560XB)
extern FUNC(void, IOHWAB_CODE)IoHwAb_GptPreModeChange(
  P2VAR(IoHwAb_IndexType, AUTOMATIC, IOHWAB_APPL_DATA) PIT_TIE_STATUS);

extern FUNC(void, IOHWAB_CODE)IoHwAb_GptPostModeChange(
  P2VAR(IoHwAb_IndexType, AUTOMATIC, IOHWAB_APPL_DATA) PIT_TIE_STATUS);
#endif /* defined(IOHWAB_MCAL_FREESCALE_MPC560XB) */

#endif /* IOHWAB_GPT_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
