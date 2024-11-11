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
**  SRC-MODULE: Crc_IntTypes.h                                                **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Crc Library Module                                    **
**                                                                            **
**  PURPOSE   : Provision of Macros using in CRC module                       **
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
** 1.0.2     24-Dec-2021   JHLim             Redmine #33330                   **
** 1.0.2.2   29-Jun-2022   SH Park           Improvement mobilegence          **
**                                             Classic <CP44-224>             **
** 1.0.3     12-Aug-2022   SH Park           Improvement mobilegence          **
**                                             Classic <CP44-81>              **
** 1.0.3.1   18-Nov-2022   ThuanLD5          Improvement mobilegence          **
**                                             Classic <CP44-361>             **
**                                                     <CP44-362>             **
*******************************************************************************/
#ifndef CRC_INTTYPES_H
#define CRC_INTTYPES_H

/*******************************************************************************
**                      Internal Macros                                       **
*******************************************************************************/
/* Macro for 8bit Table Mode of CRC Calculation */
#define CRC_8_TABLE              (0x00U)

/* Macro for 8bit Runtime Mode of CRC Calculation */
#define CRC_8_RUNTIME            (0x01U)

/* Macro for 8bit with polynomial 0x2F Table Mode of CRC Calculation */
#define CRC_8H2F_TABLE           (0x00U)

/* Macro for 8bit with polynomial 0x2F Runtime Mode of CRC Calculation */
#define CRC_8H2F_RUNTIME         (0x01U)

/* Macro for 16bit Table Mode of CRC Calculation */
#define CRC_16_TABLE             (0x00U)

/* Macro for 16bit Runtime Mode of CRC Calculation */
#define CRC_16_RUNTIME           (0x01U)

/* Macro for 16bit with polynomial 0x8005 Table Mode of CRC Calculation */
#define CRC_16_ARC_TABLE         (0x00U)

/* Macro for 16bit with polynomial Runtime Mode of CRC Calculation */
#define CRC_16_ARC_RUNTIME       (0x01U)

/* Macro for 32bit Table Mode of CRC Calculation */
#define CRC_32_TABLE             (0x00U)

/* Macro for 32bit Runtime Mode of CRC Calculation */
#define CRC_32_RUNTIME           (0x01U)

/* Macro for 32bit with polynomial 0xF4ACFB13 Table Mode of CRC Calculation */
#define CRC_32P4_TABLE           (0x00U)

/* Macro for 32bit with polynomial 0xF4ACFB13 Runtime Mode of CRC Calculation */
#define CRC_32P4_RUNTIME         (0x01U)

/* Macro for 64bit Table Mode of CRC Calculation */
#define CRC_64_TABLE             (0x00U)

/* Macro for 64bit Runtime Mode of CRC Calculation */
#define CRC_64_RUNTIME           (0x01U)

/* Macro for not configuration Mode of CRC Calculation */
#define CRC_NOT_CFG              (0x02U)

/* Begin define macro for specific calculation mode */
/* @Trace: SafeCRC_SUD_MACRO_001 */
#if((CRC_16_ARC_MODE == CRC_16_ARC_TABLE)\
    || (CRC_32_MODE == CRC_32_TABLE)        \
    || (CRC_32P4_MODE == CRC_32P4_TABLE)    \
    || (CRC_64_MODE == CRC_64_TABLE))
/* Macro for masking in Table Mode of CRC Calculation */
#define CRC_BYTE_MASK            (0xFFU)
#endif

/* @Trace: SafeCRC_SUD_MACRO_001 */
#if((CRC_8_MODE == CRC_8_TABLE)             \
    || (CRC_8H2F_MODE == CRC_8H2F_TABLE)    \
    || (CRC_16_MODE == CRC_16_TABLE)        \
    || (CRC_16_ARC_MODE == CRC_16_ARC_TABLE)\
    || (CRC_32_MODE == CRC_32_TABLE)        \
    || (CRC_32P4_MODE == CRC_32P4_TABLE)    \
    || (CRC_64_MODE == CRC_64_TABLE))
/* Array index of Table to perform CRC calculation */
#define CRC_COUNT256             (256U)
#endif

/* @Trace: SafeCRC_SUD_MACRO_001 */
#if((CRC_8_MODE == CRC_8_RUNTIME)             \
    || (CRC_8H2F_MODE == CRC_8H2F_RUNTIME)    \
    || (CRC_16_ARC_MODE == CRC_16_ARC_RUNTIME)\
    || (CRC_32_MODE == CRC_32_RUNTIME)        \
    || (CRC_32P4_MODE == CRC_32P4_RUNTIME)    \
    || (CRC_64_MODE == CRC_64_RUNTIME))
/* 8 bit MSB mask */
#define CRC_MSB8                 (0x80U)
#endif

/* @Trace: SafeCRC_SUD_MACRO_001 */
#if((CRC_16_MODE == CRC_16_RUNTIME)           \
    || (CRC_16_ARC_MODE == CRC_16_ARC_RUNTIME)\
    || (CRC_32_MODE == CRC_32_RUNTIME)        \
    || (CRC_32P4_MODE == CRC_32P4_RUNTIME)    \
    || (CRC_64_MODE == CRC_64_RUNTIME))
/* 16 bit MSB mask */
#define CRC_MSB16                (0x8000U)
#endif

/* @Trace: SafeCRC_SUD_MACRO_001 */
#if((CRC_16_ARC_MODE == CRC_16_ARC_RUNTIME)\
    || (CRC_32_MODE == CRC_32_RUNTIME)        \
    || (CRC_32P4_MODE == CRC_32P4_RUNTIME)    \
    || (CRC_64_MODE == CRC_64_RUNTIME))
/* 32 bit MSB mask and 64 bit MSB mask */
#define CRC_MSB32                (0x80000000UL)
#define CRC_MSB64                (0x8000000000000000ULL)
#endif

/* @Trace: SafeCRC_SUD_MACRO_001 */
#if(CRC_8_MODE == CRC_8_RUNTIME)
/* CRC-SAE-J1850 standard 8 bit generator polynomial */
#define CRC_POLY8                (0x1DU)
#endif

/* @Trace: SafeCRC_SUD_MACRO_001 */
#if(CRC_8H2F_MODE == CRC_8H2F_RUNTIME)
/* CRC-8 bit 0x2F polynomial */
#define CRC_POLY8H2F             (0x2FU)
#endif

/* @Trace: SafeCRC_SUD_MACRO_001 */
#if(CRC_16_MODE == CRC_16_RUNTIME)
/* CRC-CCITT standard 16 bit generator polynomial */
#define CRC_POLY16               (0x1021U)
#endif

/* @Trace: SafeCRC_SUD_MACRO_001 */
#if(CRC_16_ARC_MODE == CRC_16_ARC_RUNTIME)
/* CRC-16/ARC standard 16 bit generator polynomial */
#define CRC_POLY16ARC            (0x8005U)
#endif

/* @Trace: SafeCRC_SUD_MACRO_001 */
#if(CRC_32_MODE == CRC_32_RUNTIME)
/* IEEE-802.3 standard 32 bit generator polynomial */
#define CRC_POLY32               (0x04C11DB7UL)
#endif

/* @Trace: SafeCRC_SUD_MACRO_001 */
#if(CRC_32P4_MODE == CRC_32P4_RUNTIME)
/* CRC32P4 bit generator polynomial */
#define CRC_POLY32P4             (0xF4ACFB13UL)
#endif

/* @Trace: SafeCRC_SUD_MACRO_001 */
#if(CRC_64_MODE == CRC_64_RUNTIME)
/* CRC64 bit generator polynomial */
#define CRC_POLY64               (0x42F0E1EBA9EA3693ULL)
#endif

/* Macro for TRUE value */
#define CRC_TRUE                 (0x01U)

/* Final XOR value for 8 bit checksum */
#define CRC_XOR_OUT8             (0xFFU)

/* Final XOR value for 8 bit checksum with 0x2F polynomial */
#define CRC_XOR_OUT8H2F          (0xFFU)

/* Final XOR value for 32 bit checksum */
#define CRC_XOR_OUT32            (0xFFFFFFFFUL)

/* Final XOR value for 32 bit checksum with 0xF4ACFB13 polynomial */
#define CRC_XOR_OUT32P4          (0xFFFFFFFFUL)

/* Final XOR value for 64 bit checksum */
#define CRC_XOR_OUT64            (0xFFFFFFFFFFFFFFFFULL)

/* Macro for the Initial value of 8 bit CRC calculation */
#define CRC_INITIAL_VALUE8       (0xFFU)

/* Macro for the Initial value of 8 bit 0x2F CRC calculation */
#define CRC_INITIAL_VALUE8H2F    (0xFFU)

/* Macro for the Initial value of 16 bit CRC calculation */
#define CRC_INITIAL_VALUE16      (0xFFFFU)

/* Macro for the Initial value of 16 bit 0x8005 CRC calculation */
#define CRC_INITIAL_VALUE16ARC   (0x0000U)

/* Macro for the Initial value of 32 bit CRC calculation */
#define CRC_INITIAL_VALUE32      (0xFFFFFFFFUL)

/* Macro for the Initial value of 32 0xF4ACFB13 bit CRC calculation */
#define CRC_INITIAL_VALUE32P4    (0xFFFFFFFFUL)

/* Macro for the Initial value of 64 bit CRC calculation */
#define CRC_INITIAL_VALUE64      (0xFFFFFFFFFFFFFFFFULL)

/* Macro for the number 0 */
#define CRC_ZERO                 (0x00U)

/* Macro for get one byte */
#define CRC_MASK_ONE_BYTE        (0xFFU)

/* Macro for get two bytes */
#define CRC_MASK_TWO_BYTE        (0xFFFFU)

/* Macro for get four bytes */
#define CRC_MASK_FOUR_BYTE       (0xFFFFFFFFUL)

/* Macro for get four bytes high */
#define CRC_MASK_FOUR_BYTE_HIGH      (0xFFFFFFFF00000000ULL)
/* @Trace: SafeCRC_SUD_MACRO_001 */
#if((CRC_8_MODE == CRC_8_RUNTIME)             \
    || (CRC_8H2F_MODE == CRC_8H2F_RUNTIME)    \
    || (CRC_16_ARC_MODE == CRC_16_ARC_RUNTIME)\
    || (CRC_32_MODE == CRC_32_RUNTIME)        \
    || (CRC_32P4_MODE == CRC_32P4_RUNTIME)    \
    || (CRC_64_MODE == CRC_64_RUNTIME))
/* Macro for the number 1 */
#define CRC_ONE                  (0x01U)
#endif

/* Macro for the number 8 */
#define CRC_EIGHT                (0x08U)

/* @Trace: SafeCRC_SUD_MACRO_001 */
#if((CRC_16_MODE == CRC_16_RUNTIME)           \
    || (CRC_16_ARC_MODE == CRC_16_ARC_RUNTIME))
/* Macro for the number 16 */
#define CRC_SIXTEEN              (0x10U)
#endif

/* @Trace: SafeCRC_SUD_MACRO_001 */
#if((CRC_32_MODE == CRC_32_RUNTIME)        \
    || (CRC_32P4_MODE == CRC_32P4_RUNTIME))
/* Macro for the number 24 */
#define CRC_TWENTYFOUR           (0x18U)

/* Macro for the number 32 */
#define CRC_THIRTYTWO            (0x20U)
#endif

/* @Trace: SafeCRC_SUD_MACRO_001 */
#if(CRC_64_MODE == CRC_64_RUNTIME) 
/* Macro for the number 56 */
#define CRC_FIFTYSIX             (0x38U)
/* Macro for the number 64 */
#define CRC_SIXTYFOUR            (0x40U)
#endif

#endif /* CRC_INTTYPES_H */

/*******************************************************************************
**                          End of File                                       **
*******************************************************************************/
