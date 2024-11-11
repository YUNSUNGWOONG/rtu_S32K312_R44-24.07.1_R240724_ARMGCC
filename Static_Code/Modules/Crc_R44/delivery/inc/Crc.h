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
**  SRC-MODULE: Crc.h                                                         **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Crc Library Module                                    **
**                                                                            **
**  PURPOSE   : Provision of API Prototype Declarations                       **
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
** 0.0.1     05-Sep-2019   TuanVA17         Initial Version                   **
** 0.0.2     07-Apr-2020   TienNV21         Update code annotation            **
** 1.0.2     06-Jan-2022   JHLim            Redmine #21418                    **
** 1.0.2.2   29-Jun-2022   SH Park          Improvement mobilegence           **
**                                            Classic <CP44-224>              **
** 1.0.3     12-Aug-2022   SH Park          Improvement mobilegence           **
**                                            Classic <CP44-81>               **
** 1.0.3.1   18-Nov-2022   ThuanLD5         Improvement mobilegence           **
**                                            Classic <CP44-361>              **
**                                                    <CP44-362>              **
*******************************************************************************/
#ifndef CRC_H
#define CRC_H
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* @Trace: SafeCRC_SUD_FILE_001 */
#include "Crc_Cfg.h"              /* Crc Configuration Header File */
#include "Crc_IntTypes.h"         /* Crc Type Definition Header File */
#include "Std_Types.h"            /* Standard Type Definition Header File */

/*******************************************************************************
**                       Function Prototypes                                  **
*******************************************************************************/
#define CRC_START_SEC_CODE_ASIL_D
#include "MemMap.h"

/* @Trace: SafeCRC_SUD_MACRO_001 */
#if((CRC_8_MODE == CRC_8_RUNTIME) || (CRC_8_MODE == CRC_8_TABLE))
extern FUNC(uint8, CRC_CODE) Crc_CalculateCRC8
  (P2CONST(uint8, CRC_CONST, CRC_APPL_CONST)Crc_DataPtr, uint32 Crc_Length,
  uint8 Crc_StartValue8, boolean Crc_IsFirstCall);
#endif

/* @Trace: SafeCRC_SUD_MACRO_001 */
#if((CRC_8H2F_MODE == CRC_8H2F_RUNTIME) || (CRC_8H2F_MODE == CRC_8H2F_TABLE))
extern FUNC(uint8, CRC_CODE) Crc_CalculateCRC8H2F
  (P2CONST(uint8, CRC_CONST, CRC_APPL_CONST)Crc_DataPtr, uint32 Crc_Length,
  uint8 Crc_StartValue8H2F, boolean Crc_IsFirstCall);
#endif

/* @Trace: SafeCRC_SUD_MACRO_001 */
#if((CRC_16_MODE == CRC_16_RUNTIME) || (CRC_16_MODE == CRC_16_TABLE))
extern FUNC(uint16, CRC_CODE) Crc_CalculateCRC16
  (P2CONST(uint8, CRC_CONST, CRC_APPL_CONST)Crc_DataPtr, uint32 Crc_Length,
  uint16 Crc_StartValue16, boolean Crc_IsFirstCall);
#endif

/* @Trace: SafeCRC_SUD_MACRO_001 */
#if((CRC_16_ARC_MODE == CRC_16_ARC_RUNTIME) || \
  (CRC_16_ARC_MODE == CRC_16_ARC_TABLE))
extern FUNC(uint16, CRC_CODE) Crc_CalculateCRC16ARC
  (P2CONST(uint8, CRC_CONST, CRC_APPL_CONST)Crc_DataPtr, uint32 Crc_Length,
  uint16 Crc_StartValue16, boolean Crc_IsFirstCall);
#endif

/* @Trace: SafeCRC_SUD_MACRO_001 */
#if((CRC_32_MODE == CRC_32_RUNTIME) || (CRC_32_MODE == CRC_32_TABLE))
extern FUNC(uint32, CRC_CODE) Crc_CalculateCRC32
  (P2CONST(uint8, CRC_CONST, CRC_APPL_CONST)Crc_DataPtr, uint32 Crc_Length,
  uint32 Crc_StartValue32, boolean Crc_IsFirstCall);
#endif

/* @Trace: SafeCRC_SUD_MACRO_001 */
#if((CRC_32P4_MODE == CRC_32P4_RUNTIME) || (CRC_32P4_MODE == CRC_32P4_TABLE))
extern FUNC(uint32, CRC_CODE) Crc_CalculateCRC32P4
  (P2CONST(uint8, CRC_CONST, CRC_APPL_CONST)Crc_DataPtr, uint32 Crc_Length,
  uint32 Crc_StartValue32, boolean Crc_IsFirstCall);
#endif

/* @Trace: SafeCRC_SUD_MACRO_001 */
#if((CRC_64_MODE == CRC_64_RUNTIME) || (CRC_64_MODE == CRC_64_TABLE))
extern FUNC(uint64, CRC_CODE) Crc_CalculateCRC64
  (P2CONST(uint8, CRC_CONST, CRC_APPL_CONST)Crc_DataPtr, uint32 Crc_Length,
  uint64 Crc_StartValue64, boolean Crc_IsFirstCall);
#endif

extern FUNC(void, CRC_CODE) Crc_GetVersionInfo
  (P2VAR(Std_VersionInfoType, AUTOMATIC, CRC_APPL_DATA)VersionInfo);

#define CRC_STOP_SEC_CODE_ASIL_D
#include "MemMap.h"
#endif

/*******************************************************************************
**                          End of File                                       **
*******************************************************************************/
