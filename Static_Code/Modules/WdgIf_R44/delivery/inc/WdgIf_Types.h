/*******************************************************************************
**                                                                            **
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  This source code is permitted to be used only in projects contracted with **
**  Hyundai Autoever, and any other use is prohibited.                        **
**  If you use it for other  purposes or change the source code, you may take **
**  legal responsibility.                                                     **
**  In this case, There is no warranty and technical support.                 **
**                                                                            **
**  SRC-MODULE: WdgIf_Types.h                                                 **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR AUTOEVER CUSTOM WDGIF                                 **
**                                                                            **
**  PURPOSE   : Watchdog Interface Define Standard Global Data Types          **
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
** 0.0.1     23-Sep-2019 <Tungdt39>         R44-Redmine <#1440>               **
** 1.3.1.0   10-Aug-2022 <TriBD>            CP44-323                          **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
#ifndef WDGIF_TYPES_H
#define WDGIF_TYPES_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Std_Types.h"


/*******************************************************************************
**                      Global Data Types                                     **
**                      Select mode operate of Wdf device                     **
*******************************************************************************/
typedef enum
{
  WDGIF_OFF_MODE,
  WDGIF_SLOW_MODE,
  WDGIF_FAST_MODE
} WdgIf_ModeType;

#endif /* END OF FILE WDGIF_TYPES_H */
/*******************************************************************************
**                          End of File                                       **
*******************************************************************************/

