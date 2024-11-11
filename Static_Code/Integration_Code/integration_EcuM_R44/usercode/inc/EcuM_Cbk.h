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
**  FILE-NAME : EcuM_Cbk.h                                                    **
**                                                                            **
**  TARGET    : TC3xx                                                         **
**                                                                            **
**  PRODUCT   : AUTOSAR EcuM Module                                           **
**                                                                            **
**  PURPOSE   : Header file for the using of MCAL modules AUTOSAR             **
**              lower version                                                 **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: yes                                          **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: yes                                       **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By               Description                       **
********************************************************************************
** 1.3.0     23-Oct-2023   Eugean Kim       CP44-3079                         **
** 1.0.3.1   19-Jul-2022   Manje Woo        CP44-624                          **
** 1.0.1     28-Sep-2021   TriBD            R44_2021 #20029                   **
*******************************************************************************/

#ifndef ECUM_CBK_H
#define ECUM_CBK_H

/* Include EcuM.h to get prototype for callback function */
#include "EcuM.h"

extern FUNC(void, ECUM_CODE) Init_McuSetMode(void);

#endif /* ECUM_CBK_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
