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
**  SRC-MODULE: IoHwAb_DigIn.c                                                **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR IOHWAB                                                **
**                                                                            **
**  PURPOSE   : APIs implementation for IoHwAb module                         **
**              IoHwAb_Dcm_DigitalSignal                                      **
**              IoHwAb_Dcm_Read_DigitalSignal                                 **
**                                                                            **
**                                                                            **
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

#ifndef IOHWAB_DCM_H
#define IOHWAB_DCM_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "IoHwAb.h"
#include "IoHwAb_Types.h"


/*****************************Digital******************************************/
#if (IOHWAB_USE_DCM_DIGOUT == STD_ON)
extern FUNC(void, IOHWAB_CODE)IoHwAb_Dcm_DigitalSignal(IoHwAb_IndexType ChIdx, uint8 action, IoHwAb_LevelType Level);
extern FUNC(void, IOHWAB_CODE)IoHwAb_Dcm_Read_DigitalSignal(IoHwAb_IndexType ChIdx, IoHwAb_LevelType* Level);
#endif
#endif /* IOHWAB_DCM_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/