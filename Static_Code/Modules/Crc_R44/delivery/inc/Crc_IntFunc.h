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
**  SRC-MODULE: Crc_IntFunc.h                                                 **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Crc Library Module                                    **
**                                                                            **
**  PURPOSE   : Provision of Internal function prototypes                     **
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
** 0.0.1     05-Sep-2019   TuanVA17          Initial Version                  **
** 0.0.2     07-Apr-2020   TienNV21          Update code annotation           **
** 1.0.2.2   29-Jun-2022   SH Park           Improvement mobilegence          **
**                                             Classic <CP44-224>             **
** 1.0.3     12-Aug-2022   SH Park           Improvement mobilegence          **
**                                             Classic <CP44-81>              **
** 1.0.3.1   18-Nov-2022   ThuanLD5          Improvement mobilegence          **
**                                             Classic <CP44-361>             **
**                                                     <CP44-362>             **
*******************************************************************************/
#ifndef CRC_INTFUNC_H
#define CRC_INTFUNC_H
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Crc.h"                 /* Crc Header File */

/*******************************************************************************
**                       Function Prototypes                                  **
*******************************************************************************/
/* @Trace: SafeCRC_SUD_MACRO_001 */
#if((CRC_16_ARC_MODE == CRC_16_ARC_RUNTIME) \
  ||(CRC_32_MODE == CRC_32_RUNTIME)         \
  ||(CRC_32P4_MODE == CRC_32P4_RUNTIME)     \
  ||(CRC_64_MODE == CRC_64_RUNTIME))
#define CRC_START_SEC_CODE_ASIL_D
#include "MemMap.h"
extern FUNC(uint64, CRC_CODE) Crc_Reflect(uint64 data,
  CONST(uint8, CRC_CONST) dataLength);
#define CRC_STOP_SEC_CODE_ASIL_D
#include "MemMap.h"
#endif 
#endif

/*******************************************************************************
**                          End of File                                       **
*******************************************************************************/
