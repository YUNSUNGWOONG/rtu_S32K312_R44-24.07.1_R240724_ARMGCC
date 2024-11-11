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
**  SRC-MODULE: CanCM_Error.h                                                 **
**                                                                            **
**  TARGET    : General CAN Communication Manager                             **
**                                                                            **
**  PRODUCT   : AUTOEVER CAN Communication Manager Module                     **
**                                                                            **
**  PURPOSE   : Declaration of DET errors                                     **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: yes                                          **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By               Description                       **
********************************************************************************
** 1.0.3.1   29-Jun-2022   NhatTD2          CP44-135                          **
** 1.0.1     22-Sep-2021   LinhTT36         Redmine #20380                    **
** 1.0.0     22-Dec-2020   SJ Kim           Initial Version                   **
*******************************************************************************/
#ifndef CANCM_ERROR_H
#define CANCM_ERROR_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "CanCM.h"                    /* Header file for Fr Module */
/* @Trace: CanCM_SUD_MACRO_008 */
/* Errors are reported to DET */
#define CANCM_E_UNINIT                 ((uint8)31)
#define CANCM_E_READBATTERYFAIL        ((uint8)32)
#define CANCM_E_INVALID_REQUEST        ((uint8)33)
#define CANCM_E_NULL_POINTER           ((uint8)34)

#endif /* CANCM_ERROR_H */

/*******************************************************************************
**                          End of File                                       **
*******************************************************************************/
