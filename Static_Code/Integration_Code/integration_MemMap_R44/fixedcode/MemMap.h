/*******************************************************************************
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**                                                                            **
**  Confidential Proprietary Information. Distribution Limited.               **
**  This source code is permitted to be used only in projects contracted      **
**  with Hyundai Autoever, and any other use is prohibited.                   **
**  If you use it for other purposes or change the source code,               **
**  you may take legal responsibility.                                        **
**  In this case, There is no warranty and technical support.                 **
**                                                                            **
**  FILE-NAME : MemMap.h                                                      **
**                                                                            **
**  TARGET    : MCU using GHS complier                                        **
**                                                                            **
**  PRODUCT   : AUTOSAR BSW R4.4.0 Modules                                    **
**                                                                            **
**  PURPOSE   : Provision for sections for memory mapping.                    **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: yes                                          **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: yes                                       **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                              Revision History                              **
********************************************************************************
** Revision   Date          By            Description                         **
********************************************************************************
** 1.0.0      10-Sep-2021   Sungho Park   Initial version                     **
** 1.0.1      01-Dec-2021   JH Lim        Redmine #33260                      **
** 1.0.2      01-Dec-2021   HiepVT1       Update MemMap section for SomeIpXf  **
**                                        and WdgIf                           **
** 1.0.3      11-Mar-2022   Gongbin Lim   Update MemMap section for E2EXf     **
** 1.0.4      17-Mar-2022   ThuanVT       Add Nm Callout Code section         **
** 1.0.5      06-Apr-2022   LanhLT        Update MemMap section for FiM       **
** 1.0.6      09-May-2022   ThuanVT       Add new section for ComM            **
** 1.0.6      08-Nov-2022   ThinhNQ7      Add section for XCP POST BUILD      **
** 1.0.7      16-Dec-2022   NamNT1        Add PostBuild section for CanNm, Nm **
** 1.0.8      28-Mar-2023   Manje Woo     Add section for DataLog             **
** 1.0.9      15-May-2023   TruongPQ1     Add section for EthTSyn             **
** 1.0.10     15-JUN-2023   KaHyunKim     Add section for Csm,Add User Memmap **
** 1.0.12     27-JUN-2023   JH Kim        Add section for WdgM                **
** 1.0.13     07-AUG-2023   KH Kim        change the section name(crypto)     **
** 1.0.14     23-AUG-2023   JHLim         CP44-3234                           **
** 1.0.15     11-SEP-2023   LanhLT        Update section of Dcm               **
** 1.0.16     31-OCT-2023   MK Choi       Add section for Fota, Pfls          **
** 1.0.17     31-JEN-2024   JS Kang       Add section for Crypto stack        **
** 1.0.18     01-FEB-2024   HaoTA4        Update section of PduR              **
*******************************************************************************/

/*******************************************************************************
* PRE-JUSTIFICATION BEGINE SECTION (MISRA-C RULE CHECKER)
* These rules will not be applied for varification based on the MISRA Rule
* in Rte generated source
*******************************************************************************/
/* polyspace:begin<MISRA-C:19.6:Not a defect:Justify with annotations> No Impact of this rule violation (AUTOSAR Standard : Memory Mapping) */

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "HwResource.h"

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/* AUTOSAR specification version information */
#define MEMMAP_AR_MAJOR_VERSION   4
#define MEMMAP_AR_MINOR_VERSION   4
#define MEMMAP_AR_PATCH_VERSION   0

/* File version information */
#define MEMMAP_SW_MAJOR_VERSION   1
#define MEMMAP_SW_MINOR_VERSION   0

/*******************************************************************************
**                      Global Symbols                                        **
*******************************************************************************/

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*******************************************************************************
**                      Module section mapping                                **
*******************************************************************************/
/*
 * The symbol 'START_WITH_IF' is undefined.
 *
 * Thus, the preprocessor continues searching for defined symbols.
 * This first #ifdef makes integration of delivered parts of MemMap.h
 * easier because every supplier starts with #elif
 */

#if defined (START_WITH_IF)
/* -------------------------------------------------------------------------- */
/*                 FOTA                                                        */
/* -------------------------------------------------------------------------- */
#elif defined (FOTA_START_SEC_CODE)
  #undef       FOTA_START_SEC_CODE
  // TEST //#pragma ghs section text=".text.DEFAULT_CODE"
  // TEST //#pragma ghs section rodata=".rodata.DEFAULT_ROM_CONST"
  // TEST //#pragma ghs section bss=".bss.DEFAULT_RAM_VAR_CLEARED"
  // TEST //#pragma ghs section data=".data.DEFAULT_RAM_VAR_INIT"
#elif defined (FOTA_STOP_SEC_CODE)
  #undef       FOTA_STOP_SEC_CODE
  // TEST //#pragma ghs section

/* -------------------------------------------------------------------------- */
/*                                MEM_76_PFLS                                 */
/* -------------------------------------------------------------------------- */
#elif defined (MEM_76_PFLS_START_FUNCTION_POINTER_TABLE)
  #undef       MEM_76_PFLS_START_FUNCTION_POINTER_TABLE
  // TEST //#pragma ghs section bss=".bss.DEFAULT_RAM_VAR_CLEARED"
#elif defined (MEM_76_PFLS_STOP_FUNCTION_POINTER_TABLE)
  #undef       MEM_76_PFLS_STOP_FUNCTION_POINTER_TABLE
#elif defined (MEM_76_PFLS_START_SEC_VAR_CLEARED_BOOLEAN)
  #undef       MEM_76_PFLS_START_SEC_VAR_CLEARED_BOOLEAN
  // TEST //#pragma ghs section bss=".bss.DEFAULT_RAM_VAR_CLEARED"
#elif defined (MEM_76_PFLS_STOP_SEC_VAR_CLEARED_BOOLEAN)
  #undef       MEM_76_PFLS_STOP_SEC_VAR_CLEARED_BOOLEAN
  // TEST //#pragma ghs section

#elif defined (MEM_76_PFLS_START_SEC_VAR_CLEARED_8)
  #undef       MEM_76_PFLS_START_SEC_VAR_CLEARED_8
  // TEST //#pragma ghs section bss=".bss.DEFAULT_RAM_VAR_CLEARED"
#elif defined (MEM_76_PFLS_STOP_SEC_VAR_CLEARED_8)
  #undef       MEM_76_PFLS_STOP_SEC_VAR_CLEARED_8
  // TEST //#pragma ghs section
#elif defined (MEM_76_PFLS_START_SEC_VAR_CLEARED_16)
  #undef       MEM_76_PFLS_START_SEC_VAR_CLEARED_16
  // TEST //#pragma ghs section bss=".bss.DEFAULT_RAM_VAR_CLEARED"
#elif defined (MEM_76_PFLS_STOP_SEC_VAR_CLEARED_16)
  #undef       MEM_76_PFLS_STOP_SEC_VAR_CLEARED_16
  // TEST //#pragma ghs section
#elif defined (MEM_76_PFLS_START_SEC_VAR_CLEARED_32)
  #undef       MEM_76_PFLS_START_SEC_VAR_CLEARED_32
  // TEST //#pragma ghs section bss=".bss.DEFAULT_RAM_VAR_CLEARED"
#elif defined (MEM_76_PFLS_STOP_SEC_VAR_CLEARED_32)
  #undef       MEM_76_PFLS_STOP_SEC_VAR_CLEARED_32
  // TEST //#pragma ghs section
#elif defined (MEM_76_PFLS_START_SEC_VAR_CLEARED_UNSPECIFIED)
  #undef       MEM_76_PFLS_START_SEC_VAR_CLEARED_UNSPECIFIED
  // TEST //#pragma ghs section bss=".bss.DEFAULT_RAM_VAR_CLEARED"
#elif defined (MEM_76_PFLS_STOP_SEC_VAR_CLEARED_UNSPECIFIED)
  #undef       MEM_76_PFLS_STOP_SEC_VAR_CLEARED_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (MEM_76_PFLS_START_SEC_CONST_BOOLEAN)
  #undef       MEM_76_PFLS_START_SEC_CONST_BOOLEAN
  // TEST //#pragma ghs section rodata=".rodata.DEFAULT_ROM_CONST"
#elif defined (MEM_76_PFLS_STOP_SEC_CONST_BOOLEAN)
  #undef       MEM_76_PFLS_STOP_SEC_CONST_BOOLEAN
  // TEST //#pragma ghs section
#elif defined (MEM_76_PFLS_START_SEC_CONST_8)
  #undef       MEM_76_PFLS_START_SEC_CONST_8
  // TEST //#pragma ghs section rodata=".rodata.DEFAULT_ROM_CONST"
#elif defined (MEM_76_PFLS_STOP_SEC_CONST_8)
  #undef       MEM_76_PFLS_STOP_SEC_CONST_8
  // TEST //#pragma ghs section
#elif defined (MEM_76_PFLS_START_SEC_CONST_16)
  #undef       MEM_76_PFLS_START_SEC_CONST_16
  // TEST //#pragma ghs section rodata=".rodata.DEFAULT_ROM_CONST"
#elif defined (MEM_76_PFLS_STOP_SEC_CONST_16)
  #undef       MEM_76_PFLS_STOP_SEC_CONST_16
  // TEST //#pragma ghs section
#elif defined (MEM_76_PFLS_START_SEC_CONST_32)
  #undef       MEM_76_PFLS_START_SEC_CONST_32
  // TEST //#pragma ghs section rodata=".rodata.DEFAULT_ROM_CONST"
  #pragma alignvar (4)
#elif defined (MEM_76_PFLS_STOP_SEC_CONST_32)
  #undef       MEM_76_PFLS_STOP_SEC_CONST_32
  #pragma alignvar (4)
  // TEST //#pragma ghs section

#elif defined (MEM_76_PFLS_START_SEC_VAR_NO_INIT_BOOLEAN)
  #undef       MEM_76_PFLS_START_SEC_VAR_NO_INIT_BOOLEAN
  // TEST //#pragma ghs section bss=".bss.DEFAULT_RAM_VAR_NO_INIT"
#elif defined (MEM_76_PFLS_STOP_SEC_VAR_NO_INIT_BOOLEAN)
  #undef       MEM_76_PFLS_STOP_SEC_VAR_NO_INIT_BOOLEAN
  // TEST //#pragma ghs section
#elif defined (MEM_76_PFLS_START_SEC_VAR_NO_INIT_8)
  #undef       MEM_76_PFLS_START_SEC_VAR_NO_INIT_8
  // TEST //#pragma ghs section bss=".bss.DEFAULT_RAM_VAR_NO_INIT"
#elif defined (MEM_76_PFLS_STOP_SEC_VAR_NO_INIT_8)
  #undef       MEM_76_PFLS_STOP_SEC_VAR_NO_INIT_8
  // TEST //#pragma ghs section
#elif defined (MEM_76_PFLS_START_SEC_VAR_NO_INIT_16)
  #undef       MEM_76_PFLS_START_SEC_VAR_NO_INIT_16
  // TEST //#pragma ghs section bss=".bss.DEFAULT_RAM_VAR_NO_INIT"
#elif defined (MEM_76_PFLS_STOP_SEC_VAR_NO_INIT_16)
  #undef       MEM_76_PFLS_STOP_SEC_VAR_NO_INIT_16
  // TEST //#pragma ghs section
#elif defined (MEM_76_PFLS_START_SEC_VAR_NO_INIT_32)
  #undef       MEM_76_PFLS_START_SEC_VAR_NO_INIT_32
  // TEST //#pragma ghs section bss=".bss.DEFAULT_RAM_VAR_NO_INIT"
#elif defined (MEM_76_PFLS_STOP_SEC_VAR_NO_INIT_32)
  #undef       MEM_76_PFLS_STOP_SEC_VAR_NO_INIT_32
  // TEST //#pragma ghs section
#elif defined (MEM_76_PFLS_START_SEC_VAR_NO_INIT_UNSPECIFIED)
  #undef       MEM_76_PFLS_START_SEC_VAR_NO_INIT_UNSPECIFIED
  // TEST //#pragma ghs section bss=".bss.DEFAULT_RAM_VAR_NO_INIT"
#elif defined (MEM_76_PFLS_STOP_SEC_VAR_NO_INIT_UNSPECIFIED)
  #undef       MEM_76_PFLS_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (MEM_76_PFLS_START_SEC_VAR_INIT_BOOLEAN)
  #undef       MEM_76_PFLS_START_SEC_VAR_INIT_BOOLEAN
  // TEST //#pragma ghs section data=".data.DEFAULT_RAM_VAR_INIT"
#elif defined (MEM_76_PFLS_STOP_SEC_VAR_INIT_BOOLEAN)
  #undef       MEM_76_PFLS_STOP_SEC_VAR_INIT_BOOLEAN
  // TEST //#pragma ghs section
#elif defined (MEM_76_PFLS_START_SEC_VAR_INIT_8)
  #undef       MEM_76_PFLS_START_SEC_VAR_INIT_8
  // TEST //#pragma ghs section data=".data.DEFAULT_RAM_VAR_INIT"
#elif defined (MEM_76_PFLS_STOP_SEC_VAR_INIT_8)
  #undef       MEM_76_PFLS_STOP_SEC_VAR_INIT_8
  // TEST //#pragma ghs section
#elif defined (MEM_76_PFLS_START_SEC_VAR_INIT_16)
  #undef       MEM_76_PFLS_START_SEC_VAR_INIT_16
  // TEST //#pragma ghs section data=".data.DEFAULT_RAM_VAR_INIT"
#elif defined (MEM_76_PFLS_STOP_SEC_VAR_INIT_16)
  #undef       MEM_76_PFLS_STOP_SEC_VAR_INIT_16
  // TEST //#pragma ghs section
#elif defined (MEM_76_PFLS_START_SEC_VAR_INIT_32)
  #undef       MEM_76_PFLS_START_SEC_VAR_INIT_32
  // TEST //#pragma ghs section data=".data.DEFAULT_RAM_VAR_INIT"
#elif defined (MEM_76_PFLS_STOP_SEC_VAR_INIT_32)
  #undef       MEM_76_PFLS_STOP_SEC_VAR_INIT_32
  // TEST //#pragma ghs section
#elif defined (MEM_76_PFLS_START_SEC_VAR_INIT_UNSPECIFIED)
  #undef       MEM_76_PFLS_START_SEC_VAR_INIT_UNSPECIFIED
  // TEST //#pragma ghs section data=".data.DEFAULT_RAM_VAR_INIT"
#elif defined (MEM_76_PFLS_STOP_SEC_VAR_INIT_UNSPECIFIED)
  #undef       MEM_76_PFLS_STOP_SEC_VAR_INIT_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (MEM_76_PFLS_START_SEC_CODE)
  #undef       MEM_76_PFLS_START_SEC_CODE
  // TEST //#pragma ghs section text=".text.DEFAULT_CODE"
  // TEST //#pragma ghs section rodata=".rodata.DEFAULT_ROM_CONST"
  // TEST //#pragma ghs section bss=".bss.DEFAULT_RAM_VAR_CLEARED"
  // TEST //#pragma ghs section data=".data.DEFAULT_RAM_VAR_INIT"
#elif defined (MEM_76_PFLS_STOP_SEC_CODE)
  #undef       MEM_76_PFLS_STOP_SEC_CODE
  // TEST //#pragma ghs section
#elif defined (MEM_76_PFLS_START_SEC_CALLOUT_CODE)
  #undef       MEM_76_PFLS_START_SEC_CALLOUT_CODE
  // TEST //#pragma ghs section text=".text.DEFAULT_CALLOUT_CODE"
  // TEST //#pragma ghs section rodata=".rodata.DEFAULT_ROM_CONST_UNSPECIFIED"
  // TEST //#pragma ghs section bss=".bss.DEFAULT_RAM_VAR_CLEARED_UNSPECIFIED"
  // TEST //#pragma ghs section data=".data.DEFAULT_RAM_VAR_INIT_UNSPECIFIED"
#elif defined (MEM_76_PFLS_STOP_SEC_CALLOUT_CODE)
  #undef       MEM_76_PFLS_STOP_SEC_CALLOUT_CODE
  // TEST //#pragma ghs section
#elif defined (MEM_76_PFLS_START_SEC_VAR_CLEARED_ALIGNED_ADDR_UNSPECIFIED)
  #undef       MEM_76_PFLS_START_SEC_VAR_CLEARED_ALIGNED_ADDR_UNSPECIFIED
  // TEST //#pragma ghs section bss=".bss.MEM_76_PFLS_RAM_VAR_CLEARED_ALIGNED_ADDR_UNSPECIFIED"
#elif defined (MEM_76_PFLS_STOP_SEC_VAR_CLEARED_ALIGNED_ADDR_UNSPECIFIED)
  #undef       MEM_76_PFLS_STOP_SEC_VAR_CLEARED_ALIGNED_ADDR_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (MEM_76_PFLS_START_SEC_CONST_UNSPECIFIED)
  #undef MEM_76_PFLS_START_SEC_CONST_UNSPECIFIED
  // TEST //#pragma ghs section rodata=".rodata.DEFAULT_ROM_CONST"
#elif defined (MEM_76_PFLS_STOP_SEC_CONST_UNSPECIFIED)
  #undef MEM_76_PFLS_STOP_SEC_CONST_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (MEM_76_PFLS_START_SEC_RAM_CODE)
  #undef MEM_76_PFLS_START_SEC_RAM_CODE
  // TEST //#pragma ghs section text=".BTL_CFLS_CODE"
  // TEST //#pragma ghs section rodata=".rodata.DEFAULT_ROM_CONST_UNSPECIFIED"
  // TEST //#pragma ghs section bss=".bss.DEFAULT_RAM_VAR_CLEARED_UNSPECIFIED"
  // TEST //#pragma ghs section data=".data.DEFAULT_RAM_VAR_INIT_UNSPECIFIED"
#elif defined (MEM_76_PFLS_STOP_SEC_RAM_CODE)
  #undef MEM_76_PFLS_STOP_SEC_RAM_CODE
  // TEST //#pragma ghs section
#elif defined (MEM_76_PFLS_START_SRAM_VAR_ALIGN_32)
  #undef MEM_76_PFLS_START_SRAM_VAR_ALIGN_32
  // TEST //#pragma ghs section text=".SRAM_BTL_CFLS_CODE"
#elif defined (MEM_76_PFLS_STOP_SRAM_VAR_ALIGN_32)
  #undef MEM_76_PFLS_START_STOP_VAR_ALIGN_32
  // TEST //#pragma ghs section

/* -------------------------------------------------------------------------- */
/*                                ETHTSYN                                     */
/* -------------------------------------------------------------------------- */
#elif defined (ETHTSYN_START_SEC_CODE)
  #undef       ETHTSYN_START_SEC_CODE
  // TEST //#pragma ghs section text=".text.ETHTSYN_CODE"
  // TEST //#pragma ghs section rodata=".rodata.ETHTSYN_ROM_CONST_UNSPECIFIED"
  // TEST //#pragma ghs section bss=".bss.ETHTSYN_RAM_VAR_CLEARED_UNSPECIFIED"
  // TEST //#pragma ghs section data=".data.ETHTSYN_RAM_VAR_INIT_UNSPECIFIED"
#elif defined (ETHTSYN_STOP_SEC_CODE)
  #undef       ETHTSYN_STOP_SEC_CODE
  // TEST //#pragma ghs section
#elif defined (ETHTSYN_START_SEC_CONST_UNSPECIFIED)
  #undef       ETHTSYN_START_SEC_CONST_UNSPECIFIED
  // TEST //#pragma ghs section rodata=".rodata.ETHTSYN_ROM_CONST_UNSPECIFIED"
  #pragma alignvar (4)
#elif defined (ETHTSYN_STOP_SEC_CONST_UNSPECIFIED)
  #undef       ETHTSYN_STOP_SEC_CONST_UNSPECIFIED
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (ETHTSYN_START_SEC_VAR_CLEARED_UNSPECIFIED)
  #undef       ETHTSYN_START_SEC_VAR_CLEARED_UNSPECIFIED
  // TEST //#pragma ghs section bss=".bss.ETHTSYN_RAM_VAR_CLEARED_UNSPECIFIED"
  #pragma alignvar (4)
#elif defined (ETHTSYN_STOP_SEC_VAR_CLEARED_UNSPECIFIED)
  #undef       ETHTSYN_STOP_SEC_VAR_CLEARED_UNSPECIFIED
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (ETHTSYN_START_SEC_VAR_CLEARED_BOOLEAN)
  #undef       ETHTSYN_START_SEC_VAR_CLEARED_BOOLEAN
  // TEST //#pragma ghs section bss=".bss.ETHTSYN_RAM_VAR_CLEARED_BOOLEAN"
  #pragma alignvar (1)
#elif defined (ETHTSYN_STOP_SEC_VAR_CLEARED_BOOLEAN)
  #undef       ETHTSYN_STOP_SEC_VAR_CLEARED_BOOLEAN
  #pragma alignvar (4)
  // TEST //#pragma ghs section
/* -------------------------------------------------------------------------- */
/*                                ETHDIAG                                     */
/* -------------------------------------------------------------------------- */
#elif defined (ETHDIAG_START_SEC_CODE)
  #undef       ETHDIAG_START_SEC_CODE
  // TEST //#pragma ghs section text=".text.ETHDIAG_CODE"
  // TEST //#pragma ghs section rodata=".rodata.ETHDIAG_ROM_CONST_UNSPECIFIED"
  // TEST //#pragma ghs section bss=".bss.ETHDIAG_RAM_VAR_CLEARED_UNSPECIFIED"
  // TEST //#pragma ghs section data=".data.ETHDIAG_RAM_VAR_INIT_UNSPECIFIED"
#elif defined (ETHDIAG_STOP_SEC_CODE)
  #undef       ETHDIAG_STOP_SEC_CODE
  // TEST //#pragma ghs section
#elif defined (ETHDIAG_START_SEC_CONFIG_DATA_PREBUILD_8)
  #undef       ETHDIAG_START_SEC_CONFIG_DATA_PREBUILD_8
  // TEST //#pragma ghs section rodata=".rodata.ETHDIAG_ROM_CONFIG_CONST_PREBUILD_8"
#elif defined (ETHDIAG_STOP_SEC_CONFIG_DATA_PREBUILD_8)
  #undef       ETHDIAG_STOP_SEC_CONFIG_DATA_PREBUILD_8
  // TEST //#pragma ghs section
#elif defined (ETHDIAG_START_SEC_CONFIG_DATA_PREBUILD_16)
  #undef       ETHDIAG_START_SEC_CONFIG_DATA_PREBUILD_16
  // TEST //#pragma ghs section rodata=".rodata.ETHDIAG_ROM_CONFIG_CONST_PREBUILD_16"
#elif defined (ETHDIAG_STOP_SEC_CONFIG_DATA_PREBUILD_16)
  #undef       ETHDIAG_STOP_SEC_CONFIG_DATA_PREBUILD_16
  // TEST //#pragma ghs section
#elif defined (ETHDIAG_START_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED)
  #undef       ETHDIAG_START_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
  // TEST //#pragma ghs section rodata=".rodata.ETHDIAG_ROM_CONFIG_CONST_PREBUILD_UNSPECIFIED"
#elif defined (ETHDIAG_STOP_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED)
  #undef       ETHDIAG_STOP_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (ETHDIAG_START_SEC_CONST_BOOLEAN)
  #undef       ETHDIAG_START_SEC_CONST_BOOLEAN
  // TEST //#pragma ghs section rodata=".rodata.ETHDIAG_ROM_CONST_BOOLEAN"
  #pragma alignvar (1)
#elif defined (ETHDIAG_STOP_SEC_CONST_BOOLEAN)
  #undef       ETHDIAG_STOP_SEC_CONST_BOOLEAN
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (ETHDIAG_START_SEC_CONST_UNSPECIFIED)
  #undef       ETHDIAG_START_SEC_CONST_UNSPECIFIED
  // TEST //#pragma ghs section rodata=".rodata.ETHDIAG_ROM_CONST_UNSPECIFIED"
  #pragma alignvar (4)
#elif defined (ETHDIAG_STOP_SEC_CONST_UNSPECIFIED)
  #undef       ETHDIAG_STOP_SEC_CONST_UNSPECIFIED
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (ETHDIAG_START_SEC_VAR_CLEARED_BOOLEAN)
  #undef       ETHDIAG_START_SEC_VAR_CLEARED_BOOLEAN
  // TEST //#pragma ghs section bss=".bss.ETHDIAG_RAM_VAR_CLEARED_BOOLEAN"
  #pragma alignvar (1)
#elif defined (ETHDIAG_STOP_SEC_VAR_CLEARED_BOOLEAN)
  #undef       ETHDIAG_STOP_SEC_VAR_CLEARED_BOOLEAN
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (ETHDIAG_START_SEC_VAR_CLEARED_8)
  #undef       ETHDIAG_START_SEC_VAR_CLEARED_8
  // TEST //#pragma ghs section bss=".bss.ETHDIAG_RAM_VAR_CLEARED_8"
  #pragma alignvar (1)
#elif defined (ETHDIAG_STOP_SEC_VAR_CLEARED_8)
  #undef       ETHDIAG_STOP_SEC_VAR_CLEARED_8
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (ETHDIAG_START_SEC_VAR_CLEARED_UNSPECIFIED)
  #undef       ETHDIAG_START_SEC_VAR_CLEARED_UNSPECIFIED
  // TEST //#pragma ghs section bss=".bss.ETHDIAG_RAM_VAR_CLEARED_UNSPECIFIED"
  #pragma alignvar (4)
#elif defined (ETHDIAG_STOP_SEC_VAR_CLEARED_UNSPECIFIED)
  #undef       ETHDIAG_STOP_SEC_VAR_CLEARED_UNSPECIFIED
  #pragma alignvar (4)
  // TEST //#pragma ghs section
/* -------------------------------------------------------------------------- */
/*                                ATM                                         */
/* -------------------------------------------------------------------------- */
#elif defined (ATM_START_SEC_CONST_8)
  #undef       ATM_START_SEC_CONST_8
  // TEST //#pragma ghs section rodata=".rodata.ATM_ROM_CONST_8"
#elif defined (ATM_STOP_SEC_CONST_8)
  #undef       ATM_STOP_SEC_CONST_8
  // TEST //#pragma ghs section
#elif defined (ATM_START_SEC_CONST_UNSPECIFIED)
  #undef       ATM_START_SEC_CONST_UNSPECIFIED
  // TEST //#pragma ghs section rodata=".rodata.ATM_ROM_CONST_UNSPECIFIED"
#elif defined (ATM_STOP_SEC_CONST_UNSPECIFIED)
  #undef       ATM_STOP_SEC_CONST_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (ATM_START_SEC_CODE)
  #undef       ATM_START_SEC_CODE
  // TEST //#pragma ghs section text=".text.ATM_CODE"
  // TEST //#pragma ghs section rodata=".rodata.ATM_ROM_CONST_UNSPECIFIED"
  // TEST //#pragma ghs section bss=".bss.ATM_RAM_VAR_CLEARED_UNSPECIFIED"
  // TEST //#pragma ghs section data=".data.ATM_RAM_VAR_INIT_UNSPECIFIED"
#elif defined (ATM_STOP_SEC_CODE)
  #undef       ATM_STOP_SEC_CODE
  // TEST //#pragma ghs section
/* -------------------------------------------------------------------------- */
/*                                CANTP                                       */
/* -------------------------------------------------------------------------- */
#elif defined (CANTP_START_SEC_VAR_CLEARED_BOOLEAN)
  #undef       CANTP_START_SEC_VAR_CLEARED_BOOLEAN
  // TEST //#pragma ghs section bss=".bss.CANTP_RAM_VAR_CLEARED_BOOLEAN"
#elif defined (CANTP_STOP_SEC_VAR_CLEARED_BOOLEAN)
  #undef       CANTP_STOP_SEC_VAR_CLEARED_BOOLEAN
  // TEST //#pragma ghs section
#elif defined (CANTP_START_SEC_VAR_CLEARED_8)
  #undef       CANTP_START_SEC_VAR_CLEARED_8
  // TEST //#pragma ghs section bss=".bss.CANTP_RAM_VAR_CLEARED_8"
#elif defined (CANTP_STOP_SEC_VAR_CLEARED_8)
  #undef       CANTP_STOP_SEC_VAR_CLEARED_8
  // TEST //#pragma ghs section
#elif defined (CANTP_START_SEC_VAR_CLEARED_16)
  #undef       CANTP_START_SEC_VAR_CLEARED_16
  // TEST //#pragma ghs section bss=".bss.CANTP_RAM_VAR_CLEARED_16"
#elif defined (CANTP_STOP_SEC_VAR_CLEARED_16)
  #undef       CANTP_STOP_SEC_VAR_CLEARED_16
  // TEST //#pragma ghs section
#elif defined (CANTP_START_SEC_VAR_CLEARED_UNSPECIFIED)
  #undef       CANTP_START_SEC_VAR_CLEARED_UNSPECIFIED
  // TEST //#pragma ghs section bss=".bss.CANTP_RAM_VAR_CLEARED_UNSPECIFIED"
#elif defined (CANTP_STOP_SEC_VAR_CLEARED_UNSPECIFIED)
  #undef       CANTP_STOP_SEC_VAR_CLEARED_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (CANTP_START_SEC_CONST_8)
  #undef       CANTP_START_SEC_CONST_8
  // TEST //#pragma ghs section rodata=".rodata.CANTP_ROM_CONST_8"
#elif defined (CANTP_STOP_SEC_CONST_8)
  #undef       CANTP_STOP_SEC_CONST_8
  // TEST //#pragma ghs section
#elif defined (CANTP_START_SEC_CONST_16)
  #undef       CANTP_START_SEC_CONST_16
  // TEST //#pragma ghs section rodata=".rodata.CANTP_ROM_CONST_16"
#elif defined (CANTP_STOP_SEC_CONST_16)
  #undef       CANTP_STOP_SEC_CONST_16
  // TEST //#pragma ghs section
#elif defined (CANTP_START_SEC_CONST_UNSPECIFIED)
  #undef       CANTP_START_SEC_CONST_UNSPECIFIED
  // TEST //#pragma ghs section rodata=".rodata.CANTP_ROM_CONST_UNSPECIFIED"
#elif defined (CANTP_STOP_SEC_CONST_UNSPECIFIED)
  #undef       CANTP_STOP_SEC_CONST_UNSPECIFIED
  // TEST //#pragma ghs section
/* Data Configuration Section for Module*/
#elif defined (CANTP_START_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED)
  #undef       CANTP_START_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
  // TEST //#pragma ghs section rodata=".rodata.CANTP_ROM_CONFIG_UNSPECIFIED"
#elif defined (CANTP_STOP_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED)
  #undef       CANTP_STOP_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (CANTP_START_SEC_CONFIG_DATA_PREBUILD_BOOLEAN)
  #undef       CANTP_START_SEC_CONFIG_DATA_PREBUILD_BOOLEAN
  // TEST //#pragma ghs section rodata=".rodata.CANTP_ROM_CONFIG_CONST_BOOLEAN"
#elif defined (CANTP_STOP_SEC_CONFIG_DATA_PREBUILD_BOOLEAN)
  #undef       CANTP_STOP_SEC_CONFIG_DATA_PREBUILD_BOOLEAN
  // TEST //#pragma ghs section
#elif defined (CANTP_START_SEC_CONFIG_DATA_PREBUILD_8)
  #undef       CANTP_START_SEC_CONFIG_DATA_PREBUILD_8
  // TEST //#pragma ghs section rodata=".rodata.CANTP_ROM_CONFIG_CONST_8"
#elif defined (CANTP_STOP_SEC_CONFIG_DATA_PREBUILD_8)
  #undef       CANTP_STOP_SEC_CONFIG_DATA_PREBUILD_8
  // TEST //#pragma ghs section
#elif defined (CANTP_START_SEC_CONFIG_DATA_PREBUILD_16)
  #undef       CANTP_START_SEC_CONFIG_DATA_PREBUILD_16
  // TEST //#pragma ghs section rodata=".rodata.CANTP_ROM_CONFIG_CONST_16"
#elif defined (CANTP_STOP_SEC_CONFIG_DATA_PREBUILD_16)
  #undef       CANTP_STOP_SEC_CONFIG_DATA_PREBUILD_16
  // TEST //#pragma ghs section
#elif defined (CANTP_START_SEC_CONFIG_DATA_PREBUILD_32)
  #undef       CANTP_START_SEC_CONFIG_DATA_PREBUILD_32
  // TEST //#pragma ghs section rodata=".rodata.CANTP_ROM_CONFIG_CONST_32"
#elif defined (CANTP_STOP_SEC_CONFIG_DATA_PREBUILD_32)
  #undef       CANTP_STOP_SEC_CONFIG_DATA_PREBUILD_32
  // TEST //#pragma ghs section
#elif defined (CANTP_START_SEC_CONFIG_DATA_PREBUILD_PTR)
  #undef       CANTP_START_SEC_CONFIG_DATA_PREBUILD_PTR
  // TEST //#pragma ghs section rodata=".rodata.CANTP_ROM_CONFIG_CONST_PTR"
#elif defined (CANTP_STOP_SEC_CONFIG_DATA_PREBUILD_PTR)
  #undef       CANTP_STOP_SEC_CONFIG_DATA_PREBUILD_PTR
  // TEST //#pragma ghs section
#elif defined (CANTP_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED)
  #undef       CANTP_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
  // TEST //#pragma ghs section rodata=".rodata.CANTP_ROM_CONFIG_UNSPECIFIED"
#elif defined (CANTP_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED)
  #undef       CANTP_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (CANTP_START_SEC_CONFIG_DATA_POSTBUILD_BOOLEAN)
  #undef       CANTP_START_SEC_CONFIG_DATA_POSTBUILD_BOOLEAN
  // TEST //#pragma ghs section rodata=".rodata.CANTP_ROM_CONFIG_CONST_BOOLEAN"
#elif defined (CANTP_STOP_SEC_CONFIG_DATA_POSTBUILD_BOOLEAN)
  #undef       CANTP_STOP_SEC_CONFIG_DATA_POSTBUILD_BOOLEAN
  // TEST //#pragma ghs section
#elif defined (CANTP_START_SEC_CONFIG_DATA_POSTBUILD_8)
  #undef       CANTP_START_SEC_CONFIG_DATA_POSTBUILD_8
  // TEST //#pragma ghs section rodata=".rodata.CANTP_ROM_CONFIG_CONST_8"
#elif defined (CANTP_STOP_SEC_CONFIG_DATA_POSTBUILD_8)
  #undef       CANTP_STOP_SEC_CONFIG_DATA_POSTBUILD_8
  // TEST //#pragma ghs section
#elif defined (CANTP_START_SEC_CONFIG_DATA_POSTBUILD_16)
  #undef       CANTP_START_SEC_CONFIG_DATA_POSTBUILD_16
  // TEST //#pragma ghs section rodata=".rodata.CANTP_ROM_CONFIG_CONST_16"
#elif defined (CANTP_STOP_SEC_CONFIG_DATA_POSTBUILD_16)
  #undef       CANTP_STOP_SEC_CONFIG_DATA_POSTBUILD_16
  // TEST //#pragma ghs section
#elif defined (CANTP_START_SEC_CONFIG_DATA_POSTBUILD_32)
  #undef       CANTP_START_SEC_CONFIG_DATA_POSTBUILD_32
  // TEST //#pragma ghs section rodata=".rodata.CANTP_ROM_CONFIG_CONST_32"
#elif defined (CANTP_STOP_SEC_CONFIG_DATA_POSTBUILD_32)
  #undef       CANTP_STOP_SEC_CONFIG_DATA_POSTBUILD_32
  // TEST //#pragma ghs section
#elif defined (CANTP_START_SEC_CONFIG_DATA_POSTBUILD_PTR)
  #undef       CANTP_START_SEC_CONFIG_DATA_POSTBUILD_PTR
  // TEST //#pragma ghs section rodata=".rodata.CANTP_ROM_CONFIG_CONST_PTR"
#elif defined (CANTP_STOP_SEC_CONFIG_DATA_POSTBUILD_PTR)
  #undef       CANTP_STOP_SEC_CONFIG_DATA_POSTBUILD_PTR
  // TEST //#pragma ghs section
/* End Configuration Section for Module*/
#elif defined (CANTP_START_SEC_VAR_NO_INIT_UNSPECIFIED)
  #undef       CANTP_START_SEC_VAR_NO_INIT_UNSPECIFIED
  // TEST //#pragma ghs section bss=".bss.CANTP_RAM_VAR_NO_INIT_UNSPECIFIED"
#elif defined (CANTP_STOP_SEC_VAR_NO_INIT_UNSPECIFIED)
  #undef       CANTP_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (CANTP_START_SEC_VAR_INIT_UNSPECIFIED)
  #undef       CANTP_START_SEC_VAR_INIT_UNSPECIFIED
  // TEST //#pragma ghs section data=".data.CANTP_RAM_VAR_INIT_UNSPECIFIED"
#elif defined (CANTP_STOP_SEC_VAR_INIT_UNSPECIFIED)
  #undef       CANTP_STOP_SEC_VAR_INIT_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (CANTP_START_SEC_VAR_INIT_BOOLEAN)
  #undef       CANTP_START_SEC_VAR_INIT_BOOLEAN
  // TEST //#pragma ghs section data=".data.CANTP_RAM_VAR_INIT_BOOLEAN"
#elif defined (CANTP_STOP_SEC_VAR_INIT_BOOLEAN)
  #undef       CANTP_STOP_SEC_VAR_INIT_BOOLEAN
  // TEST //#pragma ghs section
#elif defined (CANTP_START_SEC_VAR_INIT_8)
  #undef       CANTP_START_SEC_VAR_INIT_8
  // TEST //#pragma ghs section data=".data.CANTP_RAM_VAR_INIT_8"
#elif defined (CANTP_STOP_SEC_VAR_INIT_8)
  #undef       CANTP_STOP_SEC_VAR_INIT_8
  // TEST //#pragma ghs section
#elif defined (CANTP_START_SEC_VAR_INIT_16)
  #undef       CANTP_START_SEC_VAR_INIT_16
  // TEST //#pragma ghs section data=".data.CANTP_RAM_VAR_INIT_16"
#elif defined (CANTP_STOP_SEC_VAR_INIT_16)
  #undef       CANTP_STOP_SEC_VAR_INIT_16
  // TEST //#pragma ghs section
#elif defined (CANTP_START_SEC_CODE)
  #undef       CANTP_START_SEC_CODE
  // TEST //#pragma ghs section text=".text.CANTP_CODE"
  // TEST //#pragma ghs section rodata=".rodata.CANTP_ROM_CONST_UNSPECIFIED"
  // TEST //#pragma ghs section bss=".bss.CANTP_RAM_VAR_CLEARED_UNSPECIFIED"
  // TEST //#pragma ghs section data=".data.CANTP_RAM_VAR_INIT_UNSPECIFIED"
#elif defined (CANTP_STOP_SEC_CODE)
  #undef       CANTP_STOP_SEC_CODE
  // TEST //#pragma ghs section
/* -------------------------------------------------------------------------- */
/*                 DCM                                                      */
/* -------------------------------------------------------------------------- */
#elif defined (DCM_START_SEC_VAR_POWER_ON_CLEARED_BOOLEAN)
  #undef       DCM_START_SEC_VAR_POWER_ON_CLEARED_BOOLEAN
  // TEST //#pragma ghs section bss=".bss.DCM_RAM_VAR_POWER_ON_CLEARED_BOOLEAN"
#elif defined (DCM_STOP_SEC_VAR_POWER_ON_CLEARED_BOOLEAN)
  #undef       DCM_STOP_SEC_VAR_POWER_ON_CLEARED_BOOLEAN
  // TEST //#pragma ghs section
#elif defined (DCM_START_SEC_VAR_NO_INIT_BOOLEAN)
  #undef       DCM_START_SEC_VAR_NO_INIT_BOOLEAN
  // TEST //#pragma ghs section bss=".bss.DCM_RAM_VAR_NO_INIT_BOOLEAN"
#elif defined (DCM_STOP_SEC_VAR_NO_INIT_BOOLEAN)
  #undef       DCM_STOP_SEC_VAR_NO_INIT_BOOLEAN
  // TEST //#pragma ghs section
#elif defined (DCM_START_SEC_VAR_NO_INIT_8)
  #undef       DCM_START_SEC_VAR_NO_INIT_8
  // TEST //#pragma ghs section bss=".bss.DCM_RAM_VAR_NO_INIT_8"
#elif defined (DCM_STOP_SEC_VAR_NO_INIT_8)
  #undef       DCM_STOP_SEC_VAR_NO_INIT_8
  // TEST //#pragma ghs section
#elif defined (DCM_START_SEC_VAR_NO_INIT_16)
  #undef       DCM_START_SEC_VAR_NO_INIT_16
  // TEST //#pragma ghs section bss=".bss.DCM_RAM_VAR_NO_INIT_16"
#elif defined (DCM_STOP_SEC_VAR_NO_INIT_16)
  #undef       DCM_STOP_SEC_VAR_NO_INIT_16
  // TEST //#pragma ghs section
#elif defined (DCM_START_SEC_VAR_NO_INIT_32)
  #undef       DCM_START_SEC_VAR_NO_INIT_32
  // TEST //#pragma ghs section bss=".bss.DCM_RAM_VAR_NO_INIT_32"
#elif defined (DCM_STOP_SEC_VAR_NO_INIT_32)
  #undef       DCM_STOP_SEC_VAR_NO_INIT_32
  // TEST //#pragma ghs section
#elif defined (DCM_START_SEC_VAR_NO_INIT_UNSPECIFIED)
  #undef       DCM_START_SEC_VAR_NO_INIT_UNSPECIFIED
  // TEST //#pragma ghs section bss=".bss.DCM_RAM_VAR_NO_INIT_UNSPECIFIED"
#elif defined (DCM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED)
  #undef       DCM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (DCM_START_SEC_VAR_CLEARED_BOOLEAN)
  #undef       DCM_START_SEC_VAR_CLEARED_BOOLEAN
  // TEST //#pragma ghs section bss=".bss.DCM_RAM_VAR_CLEARED_BOOLEAN"
#elif defined (DCM_STOP_SEC_VAR_CLEARED_BOOLEAN)
  #undef       DCM_STOP_SEC_VAR_CLEARED_BOOLEAN
  // TEST //#pragma ghs section
#elif defined (DCM_START_SEC_VAR_CLEARED_8)
  #undef       DCM_START_SEC_VAR_CLEARED_8
  // TEST //#pragma ghs section bss=".bss.DCM_RAM_VAR_CLEARED_8"
#elif defined (DCM_STOP_SEC_VAR_CLEARED_8)
  #undef       DCM_STOP_SEC_VAR_CLEARED_8
  // TEST //#pragma ghs section
#elif defined (DCM_START_SEC_VAR_CLEARED_16)
  #undef       DCM_START_SEC_VAR_CLEARED_16
  // TEST //#pragma ghs section bss=".bss.DCM_RAM_VAR_CLEARED_16"
#elif defined (DCM_STOP_SEC_VAR_CLEARED_16)
  #undef       DCM_STOP_SEC_VAR_CLEARED_16
  // TEST //#pragma ghs section
#elif defined (DCM_START_SEC_VAR_CLEARED_32)
  #undef       DCM_START_SEC_VAR_CLEARED_32
  // TEST //#pragma ghs section bss=".bss.DCM_RAM_VAR_CLEARED_32"
#elif defined (DCM_STOP_SEC_VAR_CLEARED_32)
  #undef       DCM_STOP_SEC_VAR_CLEARED_32
  // TEST //#pragma ghs section
#elif defined (DCM_START_SEC_VAR_CLEARED_UNSPECIFIED)
  #undef       DCM_START_SEC_VAR_CLEARED_UNSPECIFIED
  // TEST //#pragma ghs section bss=".bss.DCM_RAM_VAR_CLEARED_UNSPECIFIED"
#elif defined (DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED)
  #undef       DCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (DCM_START_SEC_VAR_INIT_BOOLEAN)
  #undef       DCM_START_SEC_VAR_INIT_BOOLEAN
  // TEST //#pragma ghs section data=".data.DCM_RAM_VAR_INIT_BOOLEAN"
#elif defined (DCM_STOP_SEC_VAR_INIT_BOOLEAN)
  #undef       DCM_STOP_SEC_VAR_INIT_BOOLEAN
  // TEST //#pragma ghs section
#elif defined (DCM_START_SEC_VAR_INIT_8)
  #undef       DCM_START_SEC_VAR_INIT_8
  // TEST //#pragma ghs section data=".data.DCM_RAM_VAR_INIT_8"
#elif defined (DCM_STOP_SEC_VAR_INIT_8)
  #undef       DCM_STOP_SEC_VAR_INIT_8
  // TEST //#pragma ghs section
#elif defined (DCM_START_SEC_VAR_INIT_16)
  #undef       DCM_START_SEC_VAR_INIT_16
  // TEST //#pragma ghs section data=".data.DCM_RAM_VAR_INIT_16"
#elif defined (DCM_STOP_SEC_VAR_INIT_16)
  #undef       DCM_STOP_SEC_VAR_INIT_16
  // TEST //#pragma ghs section
#elif defined (DCM_START_SEC_VAR_INIT_32)
  #undef       DCM_START_SEC_VAR_INIT_32
  // TEST //#pragma ghs section data=".data.DCM_RAM_VAR_INIT_32"
#elif defined (DCM_STOP_SEC_VAR_INIT_32)
  #undef       DCM_STOP_SEC_VAR_INIT_32
  // TEST //#pragma ghs section
#elif defined (DCM_START_SEC_VAR_INIT_UNSPECIFIED)
  #undef       DCM_START_SEC_VAR_INIT_UNSPECIFIED
  // TEST //#pragma ghs section data=".data.DCM_RAM_VAR_INIT_UNSPECIFIED"
#elif defined (DCM_STOP_SEC_VAR_INIT_UNSPECIFIED)
  #undef       DCM_STOP_SEC_VAR_INIT_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (DCM_START_SEC_CONST_BOOLEAN)
  #undef       DCM_START_SEC_CONST_BOOLEAN
  // TEST //#pragma ghs section rodata=".rodata.DCM_ROM_CONST_BOOLEAN"
#elif defined (DCM_STOP_SEC_CONST_BOOLEAN)
  #undef       DCM_STOP_SEC_CONST_BOOLEAN
  // TEST //#pragma ghs section
#elif defined (DCM_START_SEC_CONST_8)
  #undef       DCM_START_SEC_CONST_8
  // TEST //#pragma ghs section rodata=".rodata.DCM_ROM_CONST_8"
#elif defined (DCM_STOP_SEC_CONST_8)
  #undef       DCM_STOP_SEC_CONST_8
  // TEST //#pragma ghs section
#elif defined (DCM_START_SEC_CONST_16)
  #undef       DCM_START_SEC_CONST_16
  // TEST //#pragma ghs section rodata=".rodata.DCM_ROM_CONST_16"
#elif defined (DCM_STOP_SEC_CONST_16)
  #undef       DCM_STOP_SEC_CONST_16
  // TEST //#pragma ghs section
#elif defined (DCM_START_SEC_CONST_32)
  #undef       DCM_START_SEC_CONST_32
  // TEST //#pragma ghs section rodata=".rodata.DCM_ROM_CONST_32"
#elif defined (DCM_STOP_SEC_CONST_32)
  #undef       DCM_STOP_SEC_CONST_32
  // TEST //#pragma ghs section
#elif defined (DCM_START_SEC_CONST_UNSPECIFIED)
  #undef       DCM_START_SEC_CONST_UNSPECIFIED
  // TEST //#pragma ghs section rodata=".rodata.DCM_ROM_CONST_UNSPECIFIED"
#elif defined (DCM_STOP_SEC_CONST_UNSPECIFIED)
  #undef       DCM_STOP_SEC_CONST_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (DCM_START_SEC_CODE)
  #undef       DCM_START_SEC_CODE
  // TEST //#pragma ghs section text=".text.DCM_CODE"
  // TEST //#pragma ghs section rodata=".rodata.DCM_ROM_CONST_UNSPECIFIED"
  // TEST //#pragma ghs section bss=".bss.DCM_RAM_VAR_CLEARED_UNSPECIFIED"
  // TEST //#pragma ghs section data=".data.DCM_RAM_VAR_INIT_UNSPECIFIED"
#elif defined (DCM_STOP_SEC_CODE)
  #undef       DCM_STOP_SEC_CODE
  // TEST //#pragma ghs section
#elif defined (DCM_START_SEC_CALLOUT_CODE)
  #undef       DCM_START_SEC_CALLOUT_CODE
  // TEST //#pragma ghs section text=".text.DCM_CODE"
  // TEST //#pragma ghs section rodata=".rodata.DCM_ROM_CONST_UNSPECIFIED"
  // TEST //#pragma ghs section bss=".bss.DCM_RAM_VAR_CLEARED_UNSPECIFIED"
  // TEST //#pragma ghs section data=".data.DCM_RAM_VAR_INIT_UNSPECIFIED"
#elif defined (DCM_STOP_SEC_CALLOUT_CODE)
  #undef       DCM_STOP_SEC_CALLOUT_CODE
  // TEST //#pragma ghs section
/* -------------------------------------------------------------------------- */
/*             Dem                                                           */
/* -------------------------------------------------------------------------- */
#elif defined (DEM_START_SEC_CONST_BOOLEAN)
  #undef       DEM_START_SEC_CONST_BOOLEAN
  // TEST //#pragma ghs section rodata=".rodata.DEM_ROM_CONST_BOOLEAN"
#elif defined (DEM_STOP_SEC_CONST_BOOLEAN)
  #undef       DEM_STOP_SEC_CONST_BOOLEAN
  // TEST //#pragma ghs section
#elif defined (DEM_START_SEC_VAR_POWER_ON_CLEARED_UNSPECIFIED)
  #undef       DEM_START_SEC_VAR_POWER_ON_CLEARED_UNSPECIFIED
  // TEST //#pragma ghs section bss=".bss.DEM_RAM_VAR_POWER_ON_CLEARED_UNSPECIFIED"
#elif defined (DEM_STOP_SEC_VAR_POWER_ON_CLEARED_UNSPECIFIED)
  #undef       DEM_STOP_SEC_VAR_POWER_ON_CLEARED_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (DEM_START_SEC_VAR_CLEARED_8)
  #undef       DEM_START_SEC_VAR_CLEARED_8
  // TEST //#pragma ghs section bss=".bss.DEM_RAM_VAR_CLEARED_8"
#elif defined (DEM_STOP_SEC_VAR_CLEARED_8)
  #undef       DEM_STOP_SEC_VAR_CLEARED_8
  // TEST //#pragma ghs section
#elif defined (DEM_START_SEC_VAR_CLEARED_16)
  #undef       DEM_START_SEC_VAR_CLEARED_16
  // TEST //#pragma ghs section bss=".bss.DEM_RAM_VAR_CLEARED_16"
#elif defined (DEM_STOP_SEC_VAR_CLEARED_16)
  #undef       DEM_STOP_SEC_VAR_CLEARED_16
  // TEST //#pragma ghs section
#elif defined (DEM_START_SEC_VAR_CLEARED_32)
  #undef       DEM_START_SEC_VAR_CLEARED_32
  // TEST //#pragma ghs section bss=".bss.DEM_RAM_VAR_CLEARED_32"
#elif defined (DEM_STOP_SEC_VAR_CLEARED_32)
  #undef       DEM_STOP_SEC_VAR_CLEARED_32
  // TEST //#pragma ghs section
#elif defined (DEM_START_SEC_VAR_CLEARED_BOOLEAN)
  #undef       DEM_START_SEC_VAR_CLEARED_BOOLEAN
  // TEST //#pragma ghs section bss=".bss.DEM_RAM_VAR_CLEARED_BOOLEAN"
#elif defined (DEM_STOP_SEC_VAR_CLEARED_BOOLEAN)
  #undef       DEM_STOP_SEC_VAR_CLEARED_BOOLEAN
  // TEST //#pragma ghs section
#elif defined (DEM_START_SEC_VAR_NO_INIT_8)
  #undef       DEM_START_SEC_VAR_NO_INIT_8
  // TEST //#pragma ghs section bss=".bss.DEM_RAM_VAR_NO_INIT_8"
#elif defined (DEM_STOP_SEC_VAR_NO_INIT_8)
  #undef       DEM_STOP_SEC_VAR_NO_INIT_8
  // TEST //#pragma ghs section
#elif defined (DEM_START_SEC_VAR_INIT_UNSPECIFIED)
  #undef DEM_START_SEC_VAR_INIT_UNSPECIFIED
  // TEST //#pragma ghs section data=".data.DEM_RAM_VAR_INIT_UNSPECIFIED"
#elif defined (DEM_STOP_SEC_VAR_INIT_UNSPECIFIED)
  #undef DEM_STOP_SEC_VAR_INIT_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (DEM_START_SEC_VAR_NO_INIT_UNSPECIFIED)
  #undef       DEM_START_SEC_VAR_NO_INIT_UNSPECIFIED
  // TEST //#pragma ghs section bss=".bss.DEM_RAM_VAR_NO_INIT_UNSPECIFIED"
#elif defined (DEM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED)
  #undef       DEM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (DEM_START_SEC_CONST_UNSPECIFIED)
  #undef       DEM_START_SEC_CONST_UNSPECIFIED
  // TEST //#pragma ghs section rodata=".rodata.DEM_ROM_CONST_UNSPECIFIED"
#elif defined (DEM_STOP_SEC_CONST_UNSPECIFIED)
  #undef       DEM_STOP_SEC_CONST_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (DEM_START_SEC_CODE)
  #undef       DEM_START_SEC_CODE
  // TEST //#pragma ghs section text=".text.DEM_CODE"
  // TEST //#pragma ghs section rodata=".rodata.DEM_ROM_CONST_UNSPECIFIED"
  // TEST //#pragma ghs section bss=".bss.DEM_RAM_VAR_CLEARED_UNSPECIFIED"
  // TEST //#pragma ghs section data=".data.DEM_RAM_VAR_INIT_UNSPECIFIED"
#elif defined (DEM_STOP_SEC_CODE)
  #undef       DEM_STOP_SEC_CODE
  // TEST //#pragma ghs section
#elif defined (DEM_START_SEC_VAR_CLEARED_UNSPECIFIED)
  #undef DEM_START_SEC_VAR_CLEARED_UNSPECIFIED
  // TEST //#pragma ghs section bss=".bss.DEM_RAM_VAR_CLEARED_UNSPECIFIED"
#elif defined (DEM_STOP_SEC_VAR_CLEARED_UNSPECIFIED)
  #undef DEM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
  // TEST //#pragma ghs section
/* -------------------------------------------------------------------------- */
/*                              Det                                           */
/* -------------------------------------------------------------------------- */
#elif defined (DET_START_SEC_VAR_NO_INIT_16)
  #undef       DET_START_SEC_VAR_NO_INIT_16
  // TEST //#pragma ghs section bss=".bss.DET_RAM_VAR_NO_INIT_16"
#elif defined (DET_STOP_SEC_VAR_NO_INIT_16)
  #undef       DET_STOP_SEC_VAR_NO_INIT_16
  // TEST //#pragma ghs section
#elif defined (DET_START_SEC_VAR_CLEARED_BOOLEAN)
  #undef       DET_START_SEC_VAR_CLEARED_BOOLEAN
  // TEST //#pragma ghs section bss=".bss.DET_RAM_VAR_CLEARED_BOOLEAN"
#elif defined (DET_STOP_SEC_VAR_CLEARED_BOOLEAN)
  #undef       DET_STOP_SEC_VAR_CLEARED_BOOLEAN
  // TEST //#pragma ghs section
#elif defined (DET_START_SEC_VAR_CLEARED_UNSPECIFIED)
  #undef       DET_START_SEC_VAR_CLEARED_UNSPECIFIED
  // TEST //#pragma ghs section bss=".bss.DET_RAM_VAR_CLEARED_UNSPECIFIED"
#elif defined (DET_STOP_SEC_VAR_CLEARED_UNSPECIFIED)
  #undef       DET_STOP_SEC_VAR_CLEARED_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (DET_START_SEC_CONST_UNSPECIFIED)
  #undef       DET_START_SEC_CONST_UNSPECIFIED
  // TEST //#pragma ghs section rodata=".rodata.DET_ROM_CONST_UNSPECIFIED"
#elif defined (DET_STOP_SEC_CONST_UNSPECIFIED)
  #undef       DET_STOP_SEC_CONST_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (DET_START_SEC_CODE)
  #undef       DET_START_SEC_CODE
  // TEST //#pragma ghs section text=".text.DET_CODE"
  // TEST //#pragma ghs section rodata=".rodata.DET_ROM_CONST_UNSPECIFIED"
  // TEST //#pragma ghs section bss=".bss.DET_RAM_VAR_CLEARED_UNSPECIFIED"
  // TEST //#pragma ghs section data=".data.DET_RAM_VAR_INIT_UNSPECIFIED"
#elif defined (DET_STOP_SEC_CODE)
  #undef       DET_STOP_SEC_CODE
  // TEST //#pragma ghs section
/* -------------------------------------------------------------------------- */
/*                                 E2E                                        */
/* -------------------------------------------------------------------------- */
#elif defined (E2E_START_SEC_CODE_ASIL_D)
  #undef       E2E_START_SEC_CODE_ASIL_D
  // TEST //#pragma ghs section text=".text.E2E_CODE"
  // TEST //#pragma ghs section rodata=".rodata.E2E_ROM_CONST_UNSPECIFIED"
  // TEST //#pragma ghs section bss=".bss.E2E_RAM_VAR_CLEARED_UNSPECIFIED"
  // TEST //#pragma ghs section data=".data.E2E_RAM_VAR_INIT_UNSPECIFIED"
#elif defined (E2E_STOP_SEC_CODE_ASIL_D)
  #undef       E2E_STOP_SEC_CODE_ASIL_D
  // TEST //#pragma ghs section
/* -------------------------------------------------------------------------- */
/*                             E2EXf                                          */
/* -------------------------------------------------------------------------- */
#elif defined (E2EXF_START_SEC_VAR_INIT_ASIL_D_BOOLEAN)
  #undef       E2EXF_START_SEC_VAR_INIT_ASIL_D_BOOLEAN
  // TEST //#pragma ghs section data=".data.E2EXF_RAM_VAR_INIT_BOOLEAN"
#elif defined (E2EXF_STOP_SEC_VAR_INIT_ASIL_D_BOOLEAN)
  #undef       E2EXF_STOP_SEC_VAR_INIT_ASIL_D_BOOLEAN
  // TEST //#pragma ghs section
#elif defined (E2EXF_START_SEC_CONST_ASIL_D_UNSPECIFIED)
  #undef       E2EXF_START_SEC_CONST_ASIL_D_UNSPECIFIED
  // TEST //#pragma ghs section rodata=".rodata.E2EXF_ROM_CONST_UNSPECIFIED"
#elif defined (E2EXF_STOP_SEC_CONST_ASIL_D_UNSPECIFIED)
  #undef       E2EXF_STOP_SEC_CONST_ASIL_D_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (E2EXF_START_SEC_VAR_NO_INIT_ASIL_D_UNSPECIFIED)
  #undef       E2EXF_START_SEC_VAR_NO_INIT_ASIL_D_UNSPECIFIED
  // TEST //#pragma ghs section bss=".bss.E2EXF_RAM_VAR_NO_INIT_UNSPECIFIED"
#elif defined (E2EXF_STOP_SEC_VAR_NO_INIT_ASIL_D_UNSPECIFIED)
  #undef       E2EXF_STOP_SEC_VAR_NO_INIT_ASIL_D_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (E2EXF_START_SEC_CODE_ASIL_D)
  #undef       E2EXF_START_SEC_CODE_ASIL_D
  // TEST //#pragma ghs section text=".text.E2EXF_CODE"
  // TEST //#pragma ghs section rodata=".rodata.E2EXF_ROM_CONST_UNSPECIFIED"
  // TEST //#pragma ghs section bss=".bss.E2EXF_RAM_VAR_CLEARED_UNSPECIFIED"
  // TEST //#pragma ghs section data=".data.E2EXF_RAM_VAR_INIT_UNSPECIFIED"
#elif defined (E2EXF_STOP_SEC_CODE_ASIL_D)
  #undef       E2EXF_STOP_SEC_CODE_ASIL_D
  // TEST //#pragma ghs section
#elif defined (E2EXF_START_SEC_VAR_NO_INIT_ASIL_D_PTR)
  #undef       E2EXF_START_SEC_VAR_NO_INIT_ASIL_D_PTR
  // TEST //#pragma ghs section text=".text.E2EXF_CODE"
  // TEST //#pragma ghs section rodata=".rodata.E2EXF_ROM_CONST_UNSPECIFIED"
  // TEST //#pragma ghs section bss=".bss.E2EXF_RAM_VAR_CLEARED_UNSPECIFIED"
  // TEST //#pragma ghs section data=".data.E2EXF_RAM_VAR_INIT_UNSPECIFIED"
#elif defined (E2EXF_STOP_SEC_VAR_NO_INIT_ASIL_D_PTR)
  #undef       E2EXF_STOP_SEC_VAR_NO_INIT_ASIL_D_PTR
  // TEST //#pragma ghs section
#elif defined (E2EXF_START_SEC_VAR_INIT_BOOLEAN)
  #undef       E2EXF_START_SEC_VAR_INIT_BOOLEAN
  // TEST //#pragma ghs section data=".data.E2EXF_RAM_VAR_INIT"
#elif defined (E2EXF_STOP_SEC_VAR_INIT_BOOLEAN)
  #undef       E2EXF_STOP_SEC_VAR_INIT_BOOLEAN
  // TEST //#pragma ghs section
#elif defined (E2EXF_START_SEC_VAR_NO_INIT_UNSPECIFIED)
  #undef       E2EXF_START_SEC_VAR_NO_INIT_UNSPECIFIED
  // TEST //#pragma ghs section bss=".bss.E2EXF_RAM_VAR_NO_INIT"
#elif defined (E2EXF_STOP_SEC_VAR_NO_INIT_UNSPECIFIED)
  #undef       E2EXF_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (E2EXF_START_SEC_VAR_NO_INIT_ASIL_D_8)
  #undef       E2EXF_START_SEC_VAR_NO_INIT_ASIL_D_8
  // TEST //#pragma ghs section bss=".bss.E2EXF_RAM_VAR_NO_INIT"
#elif defined (E2EXF_STOP_SEC_VAR_NO_INIT_ASIL_D_8)
  #undef       E2EXF_STOP_SEC_VAR_NO_INIT_ASIL_D_8
  // TEST //#pragma ghs section
#elif defined (E2EXF_START_SEC_CONST_UNSPECIFIED)
  #undef       E2EXF_START_SEC_CONST_UNSPECIFIED
  // TEST //#pragma ghs section rodata=".rodata.E2EXF_ROM_CONST"
#elif defined (E2EXF_STOP_SEC_CONST_UNSPECIFIED)
  #undef       E2EXF_STOP_SEC_CONST_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (E2EXF_START_SEC_CONFIG_DATA_PREBUILD_ASIL_D_UNSPECIFIED)
  #undef       E2EXF_START_SEC_CONFIG_DATA_PREBUILD_ASIL_D_UNSPECIFIED
  // TEST //#pragma ghs section rodata=".rodata.E2EXF_ROM_CONST"
#elif defined (E2EXF_STOP_SEC_CONFIG_DATA_PREBUILD_ASIL_D_UNSPECIFIED)
  #undef       E2EXF_STOP_SEC_CONFIG_DATA_PREBUILD_ASIL_D_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (E2EXF_START_SEC_CODE)
  #undef       E2EXF_START_SEC_CODE
  // TEST //#pragma ghs section text=".text.E2EXF_CODE"
  // TEST //#pragma ghs section rodata=".rodata.E2EXF_ROM_CONST"
  // TEST //#pragma ghs section bss=".bss.E2EXF_RAM_VAR_CLEARED"
  // TEST //#pragma ghs section data=".data.E2EXF_RAM_VAR_INIT"
#elif defined (E2EXF_STOP_SEC_CODE)
  #undef       E2EXF_STOP_SEC_CODE
  // TEST //#pragma ghs section
#elif defined (E2EXF_START_SEC_VAR_CLEARED_BOOLEAN)
  #undef       E2EXF_START_SEC_VAR_CLEARED_BOOLEAN
  // TEST //#pragma ghs section bss=".bss.E2EXF_RAM_VAR_CLEARED_BOOLEAN"
#elif defined (E2EXF_STOP_SEC_VAR_CLEARED_BOOLEAN)
  #undef       E2EXF_STOP_SEC_VAR_CLEARED_BOOLEAN
  // TEST //#pragma ghs section
#elif defined (E2EXF_START_SEC_VAR_CLEARED_8)
  #undef       E2EXF_START_SEC_VAR_CLEARED_8
  // TEST //#pragma ghs section bss=".bss.E2EXF_RAM_VAR_CLEARED_8"
#elif defined (E2EXF_STOP_SEC_VAR_CLEARED_8)
  #undef       E2EXF_STOP_SEC_VAR_CLEARED_8
  // TEST //#pragma ghs section
#elif defined (E2EXF_START_SEC_VAR_CLEARED_16)
  #undef       E2EXF_START_SEC_VAR_CLEARED_16
  // TEST //#pragma ghs section bss=".bss.E2EXF_RAM_VAR_CLEARED_16"
#elif defined (E2EXF_STOP_SEC_VAR_CLEARED_16)
  #undef       E2EXF_STOP_SEC_VAR_CLEARED_16
  // TEST //#pragma ghs section
#elif defined (E2EXF_START_SEC_VAR_CLEARED_32)
  #undef       E2EXF_START_SEC_VAR_CLEARED_32
  // TEST //#pragma ghs section bss=".bss.E2EXF_RAM_VAR_CLEARED_32"
#elif defined (E2EXF_STOP_SEC_VAR_CLEARED_32)
  #undef       E2EXF_STOP_SEC_VAR_CLEARED_32
  // TEST //#pragma ghs section
#elif defined (E2EXF_START_SEC_VAR_CLEARED_UNSPECIFIED)
  #undef       E2EXF_START_SEC_VAR_CLEARED_UNSPECIFIED
  // TEST //#pragma ghs section bss=".bss.E2EXF_RAM_VAR_CLEARED_UNSPECIFIED"
#elif defined (E2EXF_STOP_SEC_VAR_CLEARED_UNSPECIFIED)
  #undef       E2EXF_STOP_SEC_VAR_CLEARED_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (E2EXF_START_SEC_VAR_UNSPECIFIED)
  #undef       E2EXF_START_SEC_VAR_UNSPECIFIED
  // TEST //#pragma ghs section bss=".bss.E2EXF_RAM_VAR_UNSPECIFIED"
#elif defined (E2EXF_STOP_SEC_VAR_UNSPECIFIED)
  #undef       E2EXF_STOP_SEC_VAR_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (E2EXF_START_SEC_CONST_8)
  #undef       E2EXF_START_SEC_CONST_8
  // TEST //#pragma ghs section rodata=".rodata.E2EXF_ROM_CONST_8"
#elif defined (E2EXF_STOP_SEC_CONST_8)
  #undef       E2EXF_STOP_SEC_CONST_8
  // TEST //#pragma ghs section
#elif defined (E2EXF_START_SEC_CONST_16)
  #undef       E2EXF_START_SEC_CONST_16
  // TEST //#pragma ghs section rodata=".rodata.E2EXF_ROM_CONST_16"
#elif defined (E2EXF_STOP_SEC_CONST_16)
  #undef       E2EXF_STOP_SEC_CONST_16
  // TEST //#pragma ghs section
/* Data Configuration Section for Module*/
#elif defined (E2EXF_START_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED)
  #undef       E2EXF_START_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
  // TEST //#pragma ghs section rodata=".rodata.E2EXF_ROM_CONFIG_UNSPECIFIED"
#elif defined (E2EXF_STOP_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED)
  #undef       E2EXF_STOP_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (E2EXF_START_SEC_CONFIG_DATA_PREBUILD_BOOLEAN)
  #undef       E2EXF_START_SEC_CONFIG_DATA_PREBUILD_BOOLEAN
  // TEST //#pragma ghs section rodata=".rodata.E2EXF_ROM_CONFIG_CONST_BOOLEAN"
#elif defined (E2EXF_STOP_SEC_CONFIG_DATA_PREBUILD_BOOLEAN)
  #undef       E2EXF_STOP_SEC_CONFIG_DATA_PREBUILD_BOOLEAN
  // TEST //#pragma ghs section
#elif defined (E2EXF_START_SEC_CONFIG_DATA_PREBUILD_8)
  #undef       E2EXF_START_SEC_CONFIG_DATA_PREBUILD_8
  // TEST //#pragma ghs section rodata=".rodata.E2EXF_ROM_CONFIG_CONST_8"
#elif defined (E2EXF_STOP_SEC_CONFIG_DATA_PREBUILD_8)
  #undef       E2EXF_STOP_SEC_CONFIG_DATA_PREBUILD_8
  // TEST //#pragma ghs section
#elif defined (E2EXF_START_SEC_CONFIG_DATA_PREBUILD_16)
  #undef       E2EXF_START_SEC_CONFIG_DATA_PREBUILD_16
  // TEST //#pragma ghs section rodata=".rodata.E2EXF_ROM_CONFIG_CONST_16"
#elif defined (E2EXF_STOP_SEC_CONFIG_DATA_PREBUILD_16)
  #undef       E2EXF_STOP_SEC_CONFIG_DATA_PREBUILD_16
  // TEST //#pragma ghs section
#elif defined (E2EXF_START_SEC_CONFIG_DATA_PREBUILD_32)
  #undef       E2EXF_START_SEC_CONFIG_DATA_PREBUILD_32
  // TEST //#pragma ghs section rodata=".rodata.E2EXF_ROM_CONFIG_CONST_32"
#elif defined (E2EXF_STOP_SEC_CONFIG_DATA_PREBUILD_32)
  #undef       E2EXF_STOP_SEC_CONFIG_DATA_PREBUILD_32
  // TEST //#pragma ghs section
#elif defined (E2EXF_START_SEC_CONFIG_DATA_PREBUILD_PTR)
  #undef       E2EXF_START_SEC_CONFIG_DATA_PREBUILD_PTR
  // TEST //#pragma ghs section rodata=".rodata.E2EXF_ROM_CONFIG_CONST_PTR"
#elif defined (E2EXF_STOP_SEC_CONFIG_DATA_PREBUILD_PTR)
  #undef       E2EXF_STOP_SEC_CONFIG_DATA_PREBUILD_PTR
  // TEST //#pragma ghs section
#elif defined (E2EXF_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED)
  #undef       E2EXF_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
  // TEST //#pragma ghs section rodata=".rodata.E2EXF_ROM_CONFIG_UNSPECIFIED"
#elif defined (E2EXF_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED)
  #undef       E2EXF_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (E2EXF_START_SEC_CONFIG_DATA_POSTBUILD_BOOLEAN)
  #undef       E2EXF_START_SEC_CONFIG_DATA_POSTBUILD_BOOLEAN
  // TEST //#pragma ghs section rodata=".rodata.E2EXF_ROM_CONFIG_CONST_BOOLEAN"
#elif defined (E2EXF_STOP_SEC_CONFIG_DATA_POSTBUILD_BOOLEAN)
  #undef       E2EXF_STOP_SEC_CONFIG_DATA_POSTBUILD_BOOLEAN
  // TEST //#pragma ghs section
#elif defined (E2EXF_START_SEC_CONFIG_DATA_POSTBUILD_8)
  #undef       E2EXF_START_SEC_CONFIG_DATA_POSTBUILD_8
  // TEST //#pragma ghs section rodata=".rodata.E2EXF_ROM_CONFIG_CONST_8"
#elif defined (E2EXF_STOP_SEC_CONFIG_DATA_POSTBUILD_8)
  #undef       E2EXF_STOP_SEC_CONFIG_DATA_POSTBUILD_8
  // TEST //#pragma ghs section
#elif defined (E2EXF_START_SEC_CONFIG_DATA_POSTBUILD_16)
  #undef       E2EXF_START_SEC_CONFIG_DATA_POSTBUILD_16
  // TEST //#pragma ghs section rodata=".rodata.E2EXF_ROM_CONFIG_CONST_16"
#elif defined (E2EXF_STOP_SEC_CONFIG_DATA_POSTBUILD_16)
  #undef       E2EXF_STOP_SEC_CONFIG_DATA_POSTBUILD_16
  // TEST //#pragma ghs section
#elif defined (E2EXF_START_SEC_CONFIG_DATA_POSTBUILD_32)
  #undef       E2EXF_START_SEC_CONFIG_DATA_POSTBUILD_32
  // TEST //#pragma ghs section rodata=".rodata.E2EXF_ROM_CONFIG_CONST_32"
#elif defined (E2EXF_STOP_SEC_CONFIG_DATA_POSTBUILD_32)
  #undef       E2EXF_STOP_SEC_CONFIG_DATA_POSTBUILD_32
  // TEST //#pragma ghs section
#elif defined (E2EXF_START_SEC_CONFIG_DATA_POSTBUILD_PTR)
  #undef       E2EXF_START_SEC_CONFIG_DATA_POSTBUILD_PTR
  // TEST //#pragma ghs section rodata=".rodata.E2EXF_ROM_CONFIG_CONST_PTR"
#elif defined (E2EXF_STOP_SEC_CONFIG_DATA_POSTBUILD_PTR)
  #undef       E2EXF_STOP_SEC_CONFIG_DATA_POSTBUILD_PTR
  // TEST //#pragma ghs section
/* End Configuration Section for Module*/
#elif defined (E2EXF_START_SEC_VAR_INIT_UNSPECIFIED)
  #undef       E2EXF_START_SEC_VAR_INIT_UNSPECIFIED
  // TEST //#pragma ghs section data=".data.E2EXF_RAM_VAR_INIT_UNSPECIFIED"
#elif defined (E2EXF_STOP_SEC_VAR_INIT_UNSPECIFIED)
  #undef       E2EXF_STOP_SEC_VAR_INIT_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (E2EXF_START_SEC_VAR_INIT_8)
  #undef       E2EXF_START_SEC_VAR_INIT_8
  // TEST //#pragma ghs section data=".data.E2EXF_RAM_VAR_INIT_8"
#elif defined (E2EXF_STOP_SEC_VAR_INIT_8)
  #undef       E2EXF_STOP_SEC_VAR_INIT_8
  // TEST //#pragma ghs section
#elif defined (E2EXF_START_SEC_VAR_INIT_16)
  #undef       E2EXF_START_SEC_VAR_INIT_16
  // TEST //#pragma ghs section data=".data.E2EXF_RAM_VAR_INIT_16"
#elif defined (E2EXF_STOP_SEC_VAR_INIT_16)
  #undef       E2EXF_STOP_SEC_VAR_INIT_16
  // TEST //#pragma ghs section
/* -------------------------------------------------------------------------- */
/*                             SomeIpXf                                       */
/* -------------------------------------------------------------------------- */
#elif defined (SOMEIPXF_START_SEC_VAR_INIT_ASIL_D_BOOLEAN)
  #undef      SOMEIPXF_START_SEC_VAR_INIT_ASIL_D_BOOLEAN
 // TEST //#pragma ghs section data=".data.SOMEIPXF_RAM_VAR_INIT_BOOLEAN"
#elif defined (SOMEIPXF_STOP_SEC_VAR_INIT_ASIL_D_BOOLEAN)
  #undef      SOMEIPXF_STOP_SEC_VAR_INIT_ASIL_D_BOOLEAN
  // TEST //#pragma ghs section
#elif defined (SOMEIPXF_START_SEC_VAR_NO_INIT_ASIL_D_16)
  #undef      SOMEIPXF_START_SEC_VAR_NO_INIT_ASIL_D_16
  // TEST //#pragma ghs section data=".data.SOMEIPXF_RAM_VAR_NO_INIT_16"
#elif defined (SOMEIPXF_STOP_SEC_VAR_NO_INIT_ASIL_D_16)
  #undef      SOMEIPXF_STOP_SEC_VAR_NO_INIT_ASIL_D_16
  // TEST //#pragma ghs section
#elif defined (SOMEIPXF_START_SEC_CODE_ASIL_D)
  #undef      SOMEIPXF_START_SEC_CODE_ASIL_D
  // TEST //#pragma ghs section text=".text.SOMEIPXF_CODE"
  // TEST //#pragma ghs section rodata=".rodata.SOMEIPXF_ROM_CONST_UNSPECIFIED"
  // TEST //#pragma ghs section bss=".bss.SOMEIPXF_RAM_VAR_CLEARED_UNSPECIFIED"
  // TEST //#pragma ghs section data=".data.SOMEIPXF_RAM_VAR_INIT_UNSPECIFIED"
#elif defined (SOMEIPXF_STOP_SEC_CODE_ASIL_D)
  #undef      SOMEIPXF_STOP_SEC_CODE_ASIL_D
  // TEST //#pragma ghs section
/* -------------------------------------------------------------------------- */
/*                 RegMon                                                     */
/* -------------------------------------------------------------------------- */
#elif defined (REGMON_START_SEC_CODE)
  #undef       REGMON_START_SEC_CODE
  // TEST //#pragma ghs section text=".text.REGMON_CODE"
  // TEST //#pragma ghs section rodata=".rodata.REGMON_ROM_CONST_UNSPECIFIED"
  // TEST //#pragma ghs section bss=".bss.REGMON_RAM_VAR_CLEARED_UNSPECIFIED"
  // TEST //#pragma ghs section data=".data.REGMON_RAM_VAR_INIT_UNSPECIFIED"
#elif defined (REGMON_STOP_SEC_CODE)
  #undef       REGMON_STOP_SEC_CODE
  // TEST //#pragma ghs section
#elif defined (REGMON_START_SEC_VAR_UNSPECIFIED)
  #undef       REGMON_START_SEC_VAR_UNSPECIFIED
  // TEST //#pragma ghs section bss=".bss.REGMON_RAM_VAR_CLEARED_UNSPECIFIED"
#elif defined (REGMON_STOP_SEC_VAR_UNSPECIFIED)
  #undef       REGMON_STOP_SEC_VAR_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (REGMON_START_SEC_CONST_UNSPECIFIED)
  #undef       REGMON_START_SEC_CONST_UNSPECIFIED
  // TEST //#pragma ghs section rodata=".rodata.REGMON_ROM_CONST_UNSPECIFIED"
#elif defined (REGMON_STOP_SEC_CONST_UNSPECIFIED)
  #undef       REGMON_STOP_SEC_CONST_UNSPECIFIED
  // TEST //#pragma ghs section
/* -------------------------------------------------------------------------- */
/*                                 OS                                         */
/* -------------------------------------------------------------------------- */
#elif defined (OS_START_SEC_VAR_NO_INIT_UNSPECIFIED)
  #undef       OS_START_SEC_VAR_NO_INIT_UNSPECIFIED
  // TEST //#pragma ghs section bss=".bss.DEFAULT_RAM_VAR_NO_INIT"
#elif defined (OS_STOP_SEC_VAR_NO_INIT_UNSPECIFIED)
  #undef       OS_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (OS_START_SEC_VAR_CLEARED_BOOLEAN)
  #undef       OS_START_SEC_VAR_CLEARED_BOOLEAN
  // TEST //#pragma ghs section bss=".bss.DEFAULT_RAM_VAR_CLEARED"
#elif defined (OS_STOP_SEC_VAR_CLEARED_BOOLEAN)
  #undef       OS_STOP_SEC_VAR_CLEARED_BOOLEAN
  // TEST //#pragma ghs section
#elif defined (OS_START_SEC_VAR_CLEARED_8)
  #undef       OS_START_SEC_VAR_CLEARED_8
  // TEST //#pragma ghs section bss=".bss.DEFAULT_RAM_VAR_CLEARED"
#elif defined (OS_STOP_SEC_VAR_CLEARED_8)
  #undef       OS_STOP_SEC_VAR_CLEARED_8
  // TEST //#pragma ghs section
#elif defined (OS_START_SEC_VAR_CLEARED_16)
  #undef       OS_START_SEC_VAR_CLEARED_16
  // TEST //#pragma ghs section bss=".bss.DEFAULT_RAM_VAR_CLEARED"
#elif defined (OS_STOP_SEC_VAR_CLEARED_16)
  #undef       OS_STOP_SEC_VAR_CLEARED_16
  // TEST //#pragma ghs section
#elif defined (OS_START_SEC_VAR_CLEARED_32)
  #undef       OS_START_SEC_VAR_CLEARED_32
  // TEST //#pragma ghs section bss=".bss.DEFAULT_RAM_VAR_CLEARED"
#elif defined (OS_STOP_SEC_VAR_CLEARED_32)
  #undef       OS_STOP_SEC_VAR_CLEARED_32
  // TEST //#pragma ghs section
#elif defined (OS_START_SEC_VAR_CLEARED_UNSPECIFIED)
  #undef       OS_START_SEC_VAR_CLEARED_UNSPECIFIED
  // TEST //#pragma ghs section bss=".bss.DEFAULT_RAM_VAR_CLEARED"
#elif defined (OS_STOP_SEC_VAR_CLEARED_UNSPECIFIED)
  #undef       OS_STOP_SEC_VAR_CLEARED_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (OS_START_SEC_SAFETY_VAR_CLEARED_UNSPECIFIED)
  #undef       OS_START_SEC_SAFETY_VAR_CLEARED_UNSPECIFIED
  // TEST //#pragma ghs section bss=".bss.DEFAULT_SAFETY_VAR_CLEARED"
#elif defined (OS_STOP_SEC_SAFETY_VAR_CLEARED_UNSPECIFIED)
  #undef       OS_STOP_SEC_SAFETY_VAR_CLEARED_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (OS_START_SEC_USER_STACK)
  #undef       OS_START_SEC_USER_STACK
  // TEST //#pragma ghs section bss=".USR_STACK"
#elif defined (OS_STOP_SEC_USER_STACK)
  #undef       OS_STOP_SEC_USER_STACK
  // TEST //#pragma ghs section
#elif defined (OS_START_SEC_APP_STACK)
  #undef       OS_START_SEC_APP_STACK
  // TEST //#pragma ghs section bss=".OSAPP_STACK"
#elif defined (OS_STOP_SEC_APP_STACK)
  #undef       OS_STOP_SEC_APP_STACK
  // TEST //#pragma ghs section
#elif defined (OS_START_SEC_TASK_STACK)
  #undef       OS_START_SEC_TASK_STACK
  // TEST //#pragma ghs section bss=".OSTASK_STACK"
#elif defined (OS_STOP_SEC_TASK_STACK)
  #undef       OS_STOP_SEC_TASK_STACK
  // TEST //#pragma ghs section
#elif defined (OS_START_SEC_VAR_INIT_32)
  #undef       OS_START_SEC_VAR_INIT_32
  // TEST //#pragma ghs section data=".data.DEFAULT_RAM_VAR_INIT"
#elif defined (OS_STOP_SEC_VAR_INIT_32)
  #undef       OS_STOP_SEC_VAR_INIT_32
  // TEST //#pragma ghs section
#elif defined (OS_START_SEC_VAR_INIT_UNSPECIFIED)
  #undef       OS_START_SEC_VAR_INIT_UNSPECIFIED
  // TEST //#pragma ghs section data=".data.DEFAULT_RAM_VAR_INIT"
#elif defined (OS_STOP_SEC_VAR_INIT_UNSPECIFIED)
  #undef       OS_STOP_SEC_VAR_INIT_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (OS_START_SEC_CONST_32)
  #undef       OS_START_SEC_CONST_32
  // TEST //#pragma ghs section rodata=".rodata.DEFAULT_ROM_CONST"
#elif defined (OS_STOP_SEC_CONST_32)
  #undef       OS_STOP_SEC_CONST_32
  // TEST //#pragma ghs section
#elif defined (OS_START_SEC_CONST_UNSPECIFIED)
  #undef       OS_START_SEC_CONST_UNSPECIFIED
  // TEST //#pragma ghs section rodata=".rodata.DEFAULT_ROM_CONST"
#elif defined (OS_STOP_SEC_CONST_UNSPECIFIED)
  #undef       OS_STOP_SEC_CONST_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (OS_START_SEC_CODE)
  #undef       OS_START_SEC_CODE
  // TEST //#pragma ghs section text=".text.DEFAULT_CODE"
  // TEST //#pragma ghs section rodata=".rodata.DEFAULT_ROM_CONST"
  // TEST //#pragma ghs section bss=".bss.DEFAULT_RAM_VAR_CLEARED"
  // TEST //#pragma ghs section data=".data.DEFAULT_RAM_VAR_INIT"
#elif defined (OS_STOP_SEC_CODE)
  #undef       OS_STOP_SEC_CODE
  // TEST //#pragma ghs section
#elif defined (OS_START_SEC_API_CODE)
  #undef       OS_START_SEC_API_CODE
  // TEST //#pragma ghs section text=".text.OS_API_CODE"
#elif defined (OS_STOP_SEC_API_CODE)
  #undef       OS_STOP_SEC_API_CODE
  // TEST //#pragma ghs section
#elif defined (OS_START_SEC_EXCEPTION_VECTOR)
  #undef       OS_START_SEC_EXCEPTION_VECTOR
  #if (HWRESOURCE_GET_FAMILY() == HWRESOURCE_S32K14X)
    // TEST //#pragma ghs section data=".vector.EXCEPTION"
  #else
    // TEST //#pragma ghs section text=".vector.EXCEPTION"
  #endif
#elif defined (OS_STOP_SEC_EXCEPTION_VECTOR)
  #undef       OS_STOP_SEC_EXCEPTION_VECTOR
  // TEST //#pragma ghs section
#elif defined (OS_START_SEC_INTERRUPT_VECTOR)
  #undef       OS_START_SEC_INTERRUPT_VECTOR
  // TEST //#pragma ghs section text=".vector.INTERRUPT"
#elif defined (OS_STOP_SEC_INTERRUPT_VECTOR)
  #undef       OS_STOP_SEC_INTERRUPT_VECTOR
  // TEST //#pragma ghs section
/* OS IOC - INIT_UNSPECIFIED */
#elif defined (IOC_START_SEC_VAR_INIT_CORE0_UNSPECIFIED)
  #undef       IOC_START_SEC_VAR_INIT_CORE0_UNSPECIFIED
  // TEST //#pragma ghs section data=".data.IOC_RAM_VAR_INIT_CORE0_UNSPECIFIED"
#elif defined (IOC_STOP_SEC_VAR_INIT_CORE0_UNSPECIFIED)
  #undef       IOC_STOP_SEC_VAR_INIT_CORE0_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (IOC_START_SEC_VAR_INIT_CORE1_UNSPECIFIED)
  #undef       IOC_START_SEC_VAR_INIT_CORE1_UNSPECIFIED
  // TEST //#pragma ghs section data=".data.IOC_RAM_VAR_INIT_CORE1_UNSPECIFIED"
#elif defined (IOC_STOP_SEC_VAR_INIT_CORE1_UNSPECIFIED)
  #undef       IOC_STOP_SEC_VAR_INIT_CORE1_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (IOC_START_SEC_VAR_INIT_CORE2_UNSPECIFIED)
  #undef       IOC_START_SEC_VAR_INIT_CORE2_UNSPECIFIED
  // TEST //#pragma ghs section data=".data.IOC_RAM_VAR_INIT_CORE2_UNSPECIFIED"
#elif defined (IOC_STOP_SEC_VAR_INIT_CORE2_UNSPECIFIED)
  #undef       IOC_STOP_SEC_VAR_INIT_CORE2_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (IOC_START_SEC_VAR_INIT_UNSPECIFIED)
  #undef       IOC_START_SEC_VAR_INIT_UNSPECIFIED
  // TEST //#pragma ghs section data=".data.IOC_RAM_VAR_INIT_UNSPECIFIED"
#elif defined (IOC_STOP_SEC_VAR_INIT_UNSPECIFIED)
  #undef       IOC_STOP_SEC_VAR_INIT_UNSPECIFIED
  // TEST //#pragma ghs section
/* OS IOC - NO_INIT_UNSPECIFIED */
#elif defined (IOC_START_SEC_VAR_NO_INIT_CORE0_UNSPECIFIED)
  #undef       IOC_START_SEC_VAR_NO_INIT_CORE0_UNSPECIFIED
  // TEST //#pragma ghs section bss=".bss.IOC_RAM_VAR_NO_INIT_CORE0_UNSPECIFIED"
#elif defined (IOC_STOP_SEC_VAR_NO_INIT_CORE0_UNSPECIFIED)
  #undef       IOC_STOP_SEC_VAR_NO_INIT_CORE0_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (IOC_START_SEC_VAR_NO_INIT_CORE1_UNSPECIFIED)
  #undef       IOC_START_SEC_VAR_NO_INIT_CORE1_UNSPECIFIED
  // TEST //#pragma ghs section bss=".bss.IOC_RAM_VAR_NO_INIT_CORE1_UNSPECIFIED"
#elif defined (IOC_STOP_SEC_VAR_NO_INIT_CORE1_UNSPECIFIED)
  #undef       IOC_STOP_SEC_VAR_NO_INIT_CORE1_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (IOC_START_SEC_VAR_NO_INIT_CORE2_UNSPECIFIED)
  #undef       IOC_START_SEC_VAR_NO_INIT_CORE2_UNSPECIFIED
  // TEST //#pragma ghs section bss=".bss.IOC_RAM_VAR_NO_INIT_CORE2_UNSPECIFIED"
#elif defined (IOC_STOP_SEC_VAR_NO_INIT_CORE2_UNSPECIFIED)
  #undef       IOC_STOP_SEC_VAR_NO_INIT_CORE2_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (IOC_START_SEC_VAR_NO_INIT_UNSPECIFIED)
  #undef       IOC_START_SEC_VAR_NO_INIT_UNSPECIFIED
  // TEST //#pragma ghs section bss=".bss.IOC_RAM_VAR_NO_INIT_UNSPECIFIED"
#elif defined (IOC_STOP_SEC_VAR_NO_INIT_UNSPECIFIED)
  #undef       IOC_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
  // TEST //#pragma ghs section
/* -------------------------------------------------------------------------- */
/*                 LinSM                                                      */
/* -------------------------------------------------------------------------- */
#elif defined (LINSM_START_SEC_CONST_UNSPECIFIED)
  #undef       LINSM_START_SEC_CONST_UNSPECIFIED
  // TEST //#pragma ghs section rodata=".rodata.LINSM_ROM_CONST_UNSPECIFIED"
#elif defined (LINSM_STOP_SEC_CONST_UNSPECIFIED)
  #undef       LINSM_STOP_SEC_CONST_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (LINSM_START_SEC_CONST_8)
  #undef       LINSM_START_SEC_CONST_8
  // TEST //#pragma ghs section rodata=".rodata.LINSM_ROM_CONST_8"
#elif defined (LINSM_STOP_SEC_CONST_8)
  #undef       LINSM_STOP_SEC_CONST_8
  // TEST //#pragma ghs section
#elif defined (LINSM_START_SEC_VAR_CLEARED_UNSPECIFIED)
  #undef       LINSM_START_SEC_VAR_CLEARED_UNSPECIFIED
  // TEST //#pragma ghs section bss=".bss.LINSM_RAM_VAR_CLEARED_UNSPECIFIED"
#elif defined (LINSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED)
  #undef       LINSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (LINSM_START_SEC_VAR_CLEARED_BOOLEAN)
  #undef       LINSM_START_SEC_VAR_CLEARED_BOOLEAN
  // TEST //#pragma ghs section bss=".bss.LINSM_RAM_VAR_CLEARED_BOOLEAN"
#elif defined (LINSM_STOP_SEC_VAR_CLEARED_BOOLEAN)
  #undef       LINSM_STOP_SEC_VAR_CLEARED_BOOLEAN
  // TEST //#pragma ghs section
#elif defined (LINSM_START_SEC_VAR_CLEARED_8)
  #undef       LINSM_START_SEC_VAR_CLEARED_8
  // TEST //#pragma ghs section bss=".bss.LINSM_RAM_VAR_CLEARED_8"
#elif defined (LINSM_STOP_SEC_VAR_CLEARED_8)
  #undef       LINSM_STOP_SEC_VAR_CLEARED_8
  // TEST //#pragma ghs section
#elif defined (LINSM_START_SEC_CODE)
  #undef       LINSM_START_SEC_CODE
  // TEST //#pragma ghs section text=".text.LINSM_CODE"
  // TEST //#pragma ghs section rodata=".rodata.LINSM_ROM_CONST_UNSPECIFIED"
  // TEST //#pragma ghs section bss=".bss.LINSM_RAM_VAR_CLEARED_UNSPECIFIED"
  // TEST //#pragma ghs section data=".data.LINSM_RAM_VAR_INIT_UNSPECIFIED"
#elif defined (LINSM_STOP_SEC_CODE)
  #undef       LINSM_STOP_SEC_CODE
  // TEST //#pragma ghs section
/* -------------------------------------------------------------------------- */
/*                 LinTrcv                                                      */
/* -------------------------------------------------------------------------- */
#elif defined (LINTRCV_START_SEC_CONST_UNSPECIFIED)
  #undef       LINTRCV_START_SEC_CONST_UNSPECIFIED
  // TEST //#pragma ghs section rodata=".rodata.LINTRCV_ROM_CONST_UNSPECIFIED"
#elif defined (LINTRCV_STOP_SEC_CONST_UNSPECIFIED)
  #undef       LINTRCV_STOP_SEC_CONST_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (LINTRCV_START_SEC_VAR_NO_INIT_UNSPECIFIED)
  #undef       LINTRCV_START_SEC_VAR_NO_INIT_UNSPECIFIED
  // TEST //#pragma ghs section bss=".bss.LINTRCV_RAM_VAR_NO_INIT_UNSPECIFIED"
#elif defined (LINTRCV_STOP_SEC_VAR_NO_INIT_UNSPECIFIED)
  #undef       LINTRCV_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (LINTRCV_START_SEC_VAR_CLEARED_BOOLEAN)
  #undef       LINTRCV_START_SEC_VAR_CLEARED_BOOLEAN
  // TEST //#pragma ghs section bss=".bss.LINTRCV_RAM_VAR_CLEARED_BOOLEAN"
#elif defined (LINTRCV_STOP_SEC_VAR_CLEARED_BOOLEAN)
  #undef       LINTRCV_STOP_SEC_VAR_CLEARED_BOOLEAN
  // TEST //#pragma ghs section
#elif defined (LINTRCV_START_SEC_CODE)
  #undef       LINTRCV_START_SEC_CODE
  // TEST //#pragma ghs section text=".text.LINTRCV_CODE"
  // TEST //#pragma ghs section rodata=".rodata.LINTRCV_ROM_CONST_UNSPECIFIED"
  // TEST //#pragma ghs section bss=".bss.LINTRCV_RAM_VAR_CLEARED_UNSPECIFIED"
  // TEST //#pragma ghs section data=".data.LINTRCV_RAM_VAR_INIT_UNSPECIFIED"
#elif defined (LINTRCV_STOP_SEC_CODE)
  #undef       LINTRCV_STOP_SEC_CODE
  // TEST //#pragma ghs section
#elif defined (LINTRCV_7259GE_START_SEC_CONST_UNSPECIFIED)
  #undef       LINTRCV_7259GE_START_SEC_CONST_UNSPECIFIED
  // TEST //#pragma ghs section rodata=".rodata.LINTRCV_ROM_CONST_UNSPECIFIED"
#elif defined (LINTRCV_7259GE_STOP_SEC_CONST_UNSPECIFIED)
  #undef       LINTRCV_7259GE_STOP_SEC_CONST_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (LINTRCV_7259GE_START_SEC_VAR_NO_INIT_UNSPECIFIED)
  #undef       LINTRCV_7259GE_START_SEC_VAR_NO_INIT_UNSPECIFIED
  // TEST //#pragma ghs section bss=".bss.LINTRCV_RAM_VAR_NO_INIT_UNSPECIFIED"
#elif defined (LINTRCV_7259GE_STOP_SEC_VAR_NO_INIT_UNSPECIFIED)
  #undef       LINTRCV_7259GE_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (LINTRCV_7259GE_START_SEC_VAR_CLEARED_BOOLEAN)
  #undef       LINTRCV_7259GE_START_SEC_VAR_CLEARED_BOOLEAN
  // TEST //#pragma ghs section bss=".bss.LINTRCV_RAM_VAR_CLEARED_BOOLEAN"
#elif defined (LINTRCV_7259GE_STOP_SEC_VAR_CLEARED_BOOLEAN)
  #undef       LINTRCV_7259GE_STOP_SEC_VAR_CLEARED_BOOLEAN
  // TEST //#pragma ghs section
#elif defined (LINTRCV_7259GE_START_SEC_CODE)
  #undef       LINTRCV_7259GE_START_SEC_CODE
  // TEST //#pragma ghs section text=".text.LINTRCV_CODE"
  // TEST //#pragma ghs section rodata=".rodata.LINTRCV_ROM_CONST_UNSPECIFIED"
  // TEST //#pragma ghs section bss=".bss.LINTRCV_RAM_VAR_CLEARED_UNSPECIFIED"
  // TEST //#pragma ghs section data=".data.LINTRCV_RAM_VAR_INIT_UNSPECIFIED"
#elif defined (LINTRCV_7259GE_STOP_SEC_CODE)
  #undef       LINTRCV_7259GE_STOP_SEC_CODE
  // TEST //#pragma ghs section
/* -------------------------------------------------------------------------- */
/*                             LinNm                                          */
/* -------------------------------------------------------------------------- */
#elif defined (LINNM_START_SEC_VAR_CLEARED_BOOLEAN)
  #undef       LINNM_START_SEC_VAR_CLEARED_BOOLEAN
  // TEST //#pragma ghs section bss=".bss.LINNM_RAM_VAR_CLEARED_BOOLEAN"
#elif defined (LINNM_STOP_SEC_VAR_CLEARED_BOOLEAN)
  #undef       LINNM_STOP_SEC_VAR_CLEARED_BOOLEAN
  // TEST //#pragma ghs section
#elif defined (LINNM_START_SEC_VAR_NO_INIT_UNSPECIFIED)
  #undef       LINNM_START_SEC_VAR_NO_INIT_UNSPECIFIED
  // TEST //#pragma ghs section bss=".bss.LINNM_RAM_VAR_NO_INIT_UNSPECIFIED"
#elif defined (LINNM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED)
  #undef       LINNM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (LINNM_START_SEC_CONST_UNSPECIFIED)
  #undef       LINNM_START_SEC_CONST_UNSPECIFIED
  // TEST //#pragma ghs section rodata=".rodata.LINNM_ROM_CONST_UNSPECIFIED"
#elif defined (LINNM_STOP_SEC_CONST_UNSPECIFIED)
  #undef       LINNM_STOP_SEC_CONST_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (LINNM_START_SEC_CODE)
  #undef       LINNM_START_SEC_CODE
  // TEST //#pragma ghs section text=".text.LINNM_CODE"
  // TEST //#pragma ghs section rodata=".rodata.LINNM_ROM_CONST_UNSPECIFIED"
  // TEST //#pragma ghs section bss=".bss.LINNM_RAM_VAR_CLEARED_UNSPECIFIED"
  // TEST //#pragma ghs section data=".data.LINNM_RAM_VAR_INIT_UNSPECIFIED"
#elif defined (LINNM_STOP_SEC_CODE)
  #undef       LINNM_STOP_SEC_CODE
  // TEST //#pragma ghs section
/* -------------------------------------------------------------------------- */
/*             FiM                                                            */
/* -------------------------------------------------------------------------- */
#elif defined (FIM_START_SEC_CODE)
  #undef       FIM_START_SEC_CODE
  // TEST //#pragma ghs section text=".text.FIM_CODE"
  // TEST //#pragma ghs section rodata=".rodata.FIM_ROM_CONST_UNSPECIFIED"
  // TEST //#pragma ghs section bss=".bss.FIM_RAM_VAR_CLEARED_UNSPECIFIED"
  // TEST //#pragma ghs section data=".data.FIM_RAM_VAR_INIT_UNSPECIFIED"
#elif defined (FIM_STOP_SEC_CODE)
  #undef       FIM_STOP_SEC_CODE
  // TEST //#pragma ghs section
#elif defined (FIM_START_SEC_VAR_NO_INIT_UNSPECIFIED)
  #undef       FIM_START_SEC_VAR_NO_INIT_UNSPECIFIED
  // TEST //#pragma ghs section bss=".bss.FIM_RAM_VAR_NO_INIT_UNSPECIFIED"
#elif defined (FIM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED)
  #undef       FIM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (FIM_START_SEC_VAR_CLEARED_BOOLEAN)
  #undef       FIM_START_SEC_VAR_CLEARED_BOOLEAN
  // TEST //#pragma ghs section bss=".bss.FIM_RAM_VAR_CLEARED_BOOLEAN"
#elif defined (FIM_STOP_SEC_VAR_CLEARED_BOOLEAN)
  #undef       FIM_STOP_SEC_VAR_CLEARED_BOOLEAN
  // TEST //#pragma ghs section
#elif defined (FIM_START_SEC_VAR_CLEARED_UNSPECIFIED)
  #undef       FIM_START_SEC_VAR_CLEARED_UNSPECIFIED
  // TEST //#pragma ghs section bss=".bss.FIM_RAM_VAR_CLEARED_UNSPECIFIED"
#elif defined (FIM_STOP_SEC_VAR_CLEARED_UNSPECIFIED)
  #undef       FIM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (FIM_START_SEC_CONST_UNSPECIFIED)
  #undef       FIM_START_SEC_CONST_UNSPECIFIED
  // TEST //#pragma ghs section rodata=".rodata.FIM_ROM_CONST_UNSPECIFIED"
#elif defined (FIM_STOP_SEC_CONST_UNSPECIFIED)
  #undef       FIM_STOP_SEC_CONST_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (FIM_START_SEC_VAR_CLEARED_8)
  #undef       FIM_START_SEC_VAR_CLEARED_8
  // TEST //#pragma ghs section bss=".bss.FIM_RAM_VAR_CLEARED_8"
#elif defined (FIM_STOP_SEC_VAR_CLEARED_8)
  #undef       FIM_STOP_SEC_VAR_CLEARED_8
  // TEST //#pragma ghs section
/* -------------------------------------------------------------------------- */
/*                 FRSM                                                       */
/* -------------------------------------------------------------------------- */
#elif defined (FRSM_START_SEC_VAR_CLEARED_BOOLEAN)
  #undef       FRSM_START_SEC_VAR_CLEARED_BOOLEAN
  // TEST //#pragma ghs section bss=".bss.FRSM_RAM_VAR_CLEARED_BOOLEAN"
#elif defined (FRSM_STOP_SEC_VAR_CLEARED_BOOLEAN)
  #undef       FRSM_STOP_SEC_VAR_CLEARED_BOOLEAN
  // TEST //#pragma ghs section
  #elif defined (FRSM_START_SEC_VAR_CLEARED_8)
  #undef       FRSM_START_SEC_VAR_CLEARED_8
  // TEST //#pragma ghs section bss=".bss.FRSM_RAM_VAR_CLEARED_8"
#elif defined (FRSM_STOP_SEC_VAR_CLEARED_8)
  #undef       FRSM_STOP_SEC_VAR_CLEARED_8
  // TEST //#pragma ghs section
#elif defined (FRSM_START_SEC_VAR_CLEARED_UNSPECIFIED)
  #undef       FRSM_START_SEC_VAR_CLEARED_UNSPECIFIED
  // TEST //#pragma ghs section bss=".bss.FRSM_RAM_VAR_CLEARED_UNSPECIFIED"
#elif defined (FRSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED)
  #undef       FRSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (FRSM_START_SEC_VAR_NO_INIT_8)
  #undef       FRSM_START_SEC_VAR_NO_INIT_8
  // TEST //#pragma ghs section bss=".bss.FRSM_RAM_VAR_NO_INIT_8"
#elif defined (FRSM_STOP_SEC_VAR_NO_INIT_8)
  #undef       FRSM_STOP_SEC_VAR_NO_INIT_8
  // TEST //#pragma ghs section
#elif defined (FRSM_START_SEC_CONST_UNSPECIFIED)
  #undef       FRSM_START_SEC_CONST_UNSPECIFIED
  // TEST //#pragma ghs section rodata=".rodata.FRSM_ROM_CONST_UNSPECIFIED"
#elif defined (FRSM_STOP_SEC_CONST_UNSPECIFIED)
  #undef       FRSM_STOP_SEC_CONST_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (FRSM_START_SEC_VAR_NO_INIT_UNSPECIFIED)
  #undef       FRSM_START_SEC_VAR_NO_INIT_UNSPECIFIED
  // TEST //#pragma ghs section bss=".bss.FRSM_RAM_VAR_NO_INIT_UNSPECIFIED"
#elif defined (FRSM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED)
  #undef       FRSM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (FRSM_START_SEC_CODE)
  #undef       FRSM_START_SEC_CODE
  // TEST //#pragma ghs section text=".text.FRSM_CODE"
  // TEST //#pragma ghs section rodata=".rodata.FRSM_ROM_CONST_UNSPECIFIED"
  // TEST //#pragma ghs section bss=".bss.FRSM_RAM_VAR_CLEARED_UNSPECIFIED"
  // TEST //#pragma ghs section data=".data.FRSM_RAM_VAR_INIT_UNSPECIFIED"
#elif defined (FRSM_STOP_SEC_CODE)
  #undef       FRSM_STOP_SEC_CODE
  // TEST //#pragma ghs section
/* -------------------------------------------------------------------------- */
/*             FrIf                                                           */
/* -------------------------------------------------------------------------- */
#elif defined (FRIF_START_SEC_VAR_CLEARED_BOOLEAN)
  #undef       FRIF_START_SEC_VAR_CLEARED_BOOLEAN
  // TEST //#pragma ghs section bss=".bss.FRIF_RAM_VAR_CLEARED_BOOLEAN"
#elif defined (FRIF_STOP_SEC_VAR_CLEARED_BOOLEAN)
  #undef       FRIF_STOP_SEC_VAR_CLEARED_BOOLEAN
  // TEST //#pragma ghs section
#elif defined (FRIF_START_SEC_CONST_UNSPECIFIED)
  #undef       FRIF_START_SEC_CONST_UNSPECIFIED
  // TEST //#pragma ghs section rodata=".rodata.FRIF_ROM_CONST_UNSPECIFIED"
#elif defined (FRIF_STOP_SEC_CONST_UNSPECIFIED)
  #undef       FRIF_STOP_SEC_CONST_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (FRIF_START_SEC_VAR_NO_INIT_8)
  #undef       FRIF_START_SEC_VAR_NO_INIT_8
  // TEST //#pragma ghs section bss=".bss.FRIF_RAM_VAR_NO_INIT_8"
#elif defined (FRIF_STOP_SEC_VAR_NO_INIT_8)
  #undef       FRIF_STOP_SEC_VAR_NO_INIT_8
  // TEST //#pragma ghs section
#elif defined (FRIF_START_SEC_VAR_NO_INIT_8)
  #undef       FRIF_START_SEC_VAR_NO_INIT_8
  // TEST //#pragma ghs section bss=".bss.FRIF_RAM_VAR_NO_INIT_8"
#elif defined (FRIF_STOP_SEC_VAR_NO_INIT_8)
  #undef       FRIF_STOP_SEC_VAR_NO_INIT_8
  // TEST //#pragma ghs section
#elif defined (FRIF_START_SEC_VAR_NO_INIT_UNSPECIFIED)
  #undef       FRIF_START_SEC_VAR_NO_INIT_UNSPECIFIED
  // TEST //#pragma ghs section bss=".bss.FRIF_RAM_VAR_NO_INIT_UNSPECIFIED"
#elif defined (FRIF_STOP_SEC_VAR_NO_INIT_UNSPECIFIED)
  #undef       FRIF_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (FRIF_START_SEC_VAR_CLEARED_16)
  #undef       FRIF_START_SEC_VAR_CLEARED_16
  // TEST //#pragma ghs section bss=".bss.FRIF_RAM_VAR_CLEARED_16"
#elif defined (FRIF_STOP_SEC_VAR_CLEARED_16)
  #undef       FRIF_STOP_SEC_VAR_CLEARED_16
  // TEST //#pragma ghs section
#elif defined (FRIF_START_SEC_CONST_8)
  #undef       FRIF_START_SEC_CONST_8
  // TEST //#pragma ghs section rodata=".rodata.FRIF_ROM_CONST_8"
#elif defined (FRIF_STOP_SEC_CONST_8)
  #undef       FRIF_STOP_SEC_CONST_8
  // TEST //#pragma ghs section
#elif defined (FRIF_START_SEC_CONST_UNSPECIFIED)
  #undef       FRIF_START_SEC_CONST_UNSPECIFIED
  // TEST //#pragma ghs section rodata=".rodata.FRIF_ROM_CONST_UNSPECIFIED"
#elif defined (FRIF_STOP_SEC_CONST_UNSPECIFIED)
  #undef       FRIF_STOP_SEC_CONST_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (FRIF_START_SEC_CODE)
  #undef       FRIF_START_SEC_CODE
  // TEST //#pragma ghs section text=".text.FRIF_CODE"
  // TEST //#pragma ghs section rodata=".rodata.FRIF_ROM_CONST_UNSPECIFIED"
  // TEST //#pragma ghs section bss=".bss.FRIF_RAM_VAR_CLEARED_UNSPECIFIED"
  // TEST //#pragma ghs section data=".data.FRIF_RAM_VAR_INIT_UNSPECIFIED"
#elif defined (FRIF_STOP_SEC_CODE)
  #undef       FRIF_STOP_SEC_CODE
  // TEST //#pragma ghs section
/* -------------------------------------------------------------------------- */
/*                 CANIF                                                      */
/* -------------------------------------------------------------------------- */
#elif defined (CANIF_START_SEC_VAR_CLEARED_BOOLEAN)
  #undef       CANIF_START_SEC_VAR_CLEARED_BOOLEAN
  // TEST //#pragma ghs section bss=".bss.CANIF_RAM_VAR_CLEARED_BOOLEAN"
#elif defined (CANIF_STOP_SEC_VAR_CLEARED_BOOLEAN)
  #undef       CANIF_STOP_SEC_VAR_CLEARED_BOOLEAN
  // TEST //#pragma ghs section
#elif defined (CANIF_START_SEC_VAR_CLEARED_8)
  #undef       CANIF_START_SEC_VAR_CLEARED_8
  // TEST //#pragma ghs section bss=".bss.CANIF_RAM_VAR_CLEARED_8"
#elif defined (CANIF_STOP_SEC_VAR_CLEARED_8)
  #undef       CANIF_STOP_SEC_VAR_CLEARED_8
  // TEST //#pragma ghs section
#elif defined (CANIF_START_SEC_VAR_NO_INIT_8)
  #undef       CANIF_START_SEC_VAR_NO_INIT_8
  // TEST //#pragma ghs section bss=".bss.CANIF_RAM_VAR_NO_INIT_8"
#elif defined (CANIF_STOP_SEC_VAR_NO_INIT_8)
  #undef       CANIF_STOP_SEC_VAR_NO_INIT_8
  // TEST //#pragma ghs section
#elif defined (CANIF_START_SEC_CONST_8)
  #undef       CANIF_START_SEC_CONST_8
  // TEST //#pragma ghs section rodata=".rodata.CANIF_ROM_CONST_8"
#elif defined (CANIF_STOP_SEC_CONST_8)
  #undef       CANIF_STOP_SEC_CONST_8
  // TEST //#pragma ghs section
 #elif defined (CANIF_START_SEC_VAR_INIT_UNSPECIFIED)
  #undef       CANIF_START_SEC_VAR_INIT_UNSPECIFIED
  // TEST //#pragma ghs section data=".data.CANIF_RAM_VAR_INIT_UNSPECIFIED"
#elif defined (CANIF_STOP_SEC_VAR_INIT_UNSPECIFIED)
  #undef       CANIF_STOP_SEC_VAR_INIT_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (CANIF_START_SEC_VAR_NO_INIT_UNSPECIFIED)
  #undef       CANIF_START_SEC_VAR_NO_INIT_UNSPECIFIED
  // TEST //#pragma ghs section bss=".bss.CANIF_RAM_VAR_NO_INIT_UNSPECIFIED"
#elif defined (CANIF_STOP_SEC_VAR_NO_INIT_UNSPECIFIED)
  #undef       CANIF_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (CANIF_START_SEC_VAR_CLEARED_UNSPECIFIED)
  #undef       CANIF_START_SEC_VAR_CLEARED_UNSPECIFIED
  // TEST //#pragma ghs section bss=".bss.CANIF_RAM_VAR_CLEARED_UNSPECIFIED"
#elif defined (CANIF_STOP_SEC_VAR_CLEARED_UNSPECIFIED)
  #undef       CANIF_STOP_SEC_VAR_CLEARED_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (CANIF_START_SEC_CONST_UNSPECIFIED)
  #undef       CANIF_START_SEC_CONST_UNSPECIFIED
  // TEST //#pragma ghs section rodata=".rodata.CANIF_ROM_CONST_UNSPECIFIED"
#elif defined (CANIF_STOP_SEC_CONST_UNSPECIFIED)
  #undef       CANIF_STOP_SEC_CONST_UNSPECIFIED
  // TEST //#pragma ghs section
/* Data Configuration Section for Module*/
#elif defined (CANIF_START_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED)
  #undef       CANIF_START_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
  // TEST //#pragma ghs section rodata=".rodata.CANIF_ROM_CONFIG_UNSPECIFIED"
#elif defined (CANIF_STOP_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED)
  #undef       CANIF_STOP_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (CANIF_START_SEC_CONFIG_DATA_PREBUILD_BOOLEAN)
  #undef       CANIF_START_SEC_CONFIG_DATA_PREBUILD_BOOLEAN
  // TEST //#pragma ghs section rodata=".rodata.CANIF_ROM_CONFIG_CONST_BOOLEAN"
#elif defined (CANIF_STOP_SEC_CONFIG_DATA_PREBUILD_BOOLEAN)
  #undef       CANIF_STOP_SEC_CONFIG_DATA_PREBUILD_BOOLEAN
  // TEST //#pragma ghs section
#elif defined (CANIF_START_SEC_CONFIG_DATA_PREBUILD_8)
  #undef       CANIF_START_SEC_CONFIG_DATA_PREBUILD_8
  // TEST //#pragma ghs section rodata=".rodata.CANIF_ROM_CONFIG_CONST_8"
#elif defined (CANIF_STOP_SEC_CONFIG_DATA_PREBUILD_8)
  #undef       CANIF_STOP_SEC_CONFIG_DATA_PREBUILD_8
  // TEST //#pragma ghs section
#elif defined (CANIF_START_SEC_CONFIG_DATA_PREBUILD_16)
  #undef       CANIF_START_SEC_CONFIG_DATA_PREBUILD_16
  // TEST //#pragma ghs section rodata=".rodata.CANIF_ROM_CONFIG_CONST_16"
#elif defined (CANIF_STOP_SEC_CONFIG_DATA_PREBUILD_16)
  #undef       CANIF_STOP_SEC_CONFIG_DATA_PREBUILD_16
  // TEST //#pragma ghs section
#elif defined (CANIF_START_SEC_CONFIG_DATA_PREBUILD_32)
  #undef       CANIF_START_SEC_CONFIG_DATA_PREBUILD_32
  // TEST //#pragma ghs section rodata=".rodata.CANIF_ROM_CONFIG_CONST_32"
#elif defined (CANIF_STOP_SEC_CONFIG_DATA_PREBUILD_32)
  #undef       CANIF_STOP_SEC_CONFIG_DATA_PREBUILD_32
  // TEST //#pragma ghs section
#elif defined (CANIF_START_SEC_CONFIG_DATA_PREBUILD_PTR)
  #undef       CANIF_START_SEC_CONFIG_DATA_PREBUILD_PTR
  // TEST //#pragma ghs section rodata=".rodata.CANIF_ROM_CONFIG_CONST_PTR"
#elif defined (CANIF_STOP_SEC_CONFIG_DATA_PREBUILD_PTR)
  #undef       CANIF_STOP_SEC_CONFIG_DATA_PREBUILD_PTR
  // TEST //#pragma ghs section
#elif defined (CANIF_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED)
  #undef       CANIF_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
  // TEST //#pragma ghs section rodata=".rodata.CANIF_ROM_CONFIG_UNSPECIFIED"
#elif defined (CANIF_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED)
  #undef       CANIF_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (CANIF_START_SEC_CONFIG_DATA_POSTBUILD_BOOLEAN)
  #undef       CANIF_START_SEC_CONFIG_DATA_POSTBUILD_BOOLEAN
  // TEST //#pragma ghs section rodata=".rodata.CANIF_ROM_CONFIG_CONST_BOOLEAN"
#elif defined (CANIF_STOP_SEC_CONFIG_DATA_POSTBUILD_BOOLEAN)
  #undef       CANIF_STOP_SEC_CONFIG_DATA_POSTBUILD_BOOLEAN
  // TEST //#pragma ghs section
#elif defined (CANIF_START_SEC_CONFIG_DATA_POSTBUILD_8)
  #undef       CANIF_START_SEC_CONFIG_DATA_POSTBUILD_8
  // TEST //#pragma ghs section rodata=".rodata.CANIF_ROM_CONFIG_CONST_8"
#elif defined (CANIF_STOP_SEC_CONFIG_DATA_POSTBUILD_8)
  #undef       CANIF_STOP_SEC_CONFIG_DATA_POSTBUILD_8
  // TEST //#pragma ghs section
#elif defined (CANIF_START_SEC_CONFIG_DATA_POSTBUILD_16)
  #undef       CANIF_START_SEC_CONFIG_DATA_POSTBUILD_16
  // TEST //#pragma ghs section rodata=".rodata.CANIF_ROM_CONFIG_CONST_16"
#elif defined (CANIF_STOP_SEC_CONFIG_DATA_POSTBUILD_16)
  #undef       CANIF_STOP_SEC_CONFIG_DATA_POSTBUILD_16
  // TEST //#pragma ghs section
#elif defined (CANIF_START_SEC_CONFIG_DATA_POSTBUILD_32)
  #undef       CANIF_START_SEC_CONFIG_DATA_POSTBUILD_32
  // TEST //#pragma ghs section rodata=".rodata.CANIF_ROM_CONFIG_CONST_32"
#elif defined (CANIF_STOP_SEC_CONFIG_DATA_POSTBUILD_32)
  #undef       CANIF_STOP_SEC_CONFIG_DATA_POSTBUILD_32
  // TEST //#pragma ghs section
#elif defined (CANIF_START_SEC_CONFIG_DATA_POSTBUILD_PTR)
  #undef       CANIF_START_SEC_CONFIG_DATA_POSTBUILD_PTR
  // TEST //#pragma ghs section rodata=".rodata.CANIF_ROM_CONFIG_CONST_PTR"
#elif defined (CANIF_STOP_SEC_CONFIG_DATA_POSTBUILD_PTR)
  #undef       CANIF_STOP_SEC_CONFIG_DATA_POSTBUILD_PTR
  // TEST //#pragma ghs section
/* End Configuration Section for Module*/
 #elif defined (CANIF_START_SEC_CODE)
  #undef        CANIF_START_SEC_CODE
  // TEST //#pragma ghs section text=".text.CANIF_CODE"
  // TEST //#pragma ghs section rodata=".rodata.CANIF_ROM_CONST_UNSPECIFIED"
  // TEST //#pragma ghs section bss=".bss.CANIF_RAM_VAR_CLEARED_UNSPECIFIED"
  // TEST //#pragma ghs section data=".data.CANIF_RAM_VAR_INIT_UNSPECIFIED"
#elif defined (CANIF_STOP_SEC_CODE)
  #undef       CANIF_STOP_SEC_CODE
  // TEST //#pragma ghs section
#elif defined (CANIF_START_SEC_VAR_CLEARED_16)
  #undef       CANIF_START_SEC_VAR_CLEARED_16
  // TEST //#pragma ghs section bss=".bss.CANIF_RAM_VAR_CLEARED_16"
#elif defined (CANIF_STOP_SEC_VAR_CLEARED_16)
  #undef       CANIF_STOP_SEC_VAR_CLEARED_16
  // TEST //#pragma ghs section
/* -------------------------------------------------------------------------- */
/*                 CANTRCV                                                    */
/* -------------------------------------------------------------------------- */
#elif defined (CANTRCV_START_SEC_VAR_CLEARED_BOOLEAN)
  #undef       CANTRCV_START_SEC_VAR_CLEARED_BOOLEAN
  // TEST //#pragma ghs section bss=".bss.CANTRCV_RAM_VAR_CLEARED_BOOLEAN"
#elif defined (CANTRCV_STOP_SEC_VAR_CLEARED_BOOLEAN)
  #undef       CANTRCV_STOP_SEC_VAR_CLEARED_BOOLEAN
  // TEST //#pragma ghs section
#elif defined (CANTRCV_START_SEC_VAR_CLEARED_8)
  #undef       CANTRCV_START_SEC_VAR_CLEARED_8
  // TEST //#pragma ghs section bss=".bss.CANTRCV_RAM_VAR_CLEARED_8"
#elif defined (CANTRCV_STOP_SEC_VAR_CLEARED_8)
  #undef       CANTRCV_STOP_SEC_VAR_CLEARED_8
  // TEST //#pragma ghs section
#elif defined (CANTRCV_START_SEC_VAR_CLEARED_16)
  #undef       CANTRCV_START_SEC_VAR_CLEARED_16
  // TEST //#pragma ghs section bss=".bss.CANTRCV_RAM_VAR_CLEARED_16"
#elif defined (CANTRCV_STOP_SEC_VAR_CLEARED_16)
  #undef       CANTRCV_STOP_SEC_VAR_CLEARED_16
  // TEST //#pragma ghs section
#elif defined (CANTRCV_START_SEC_VAR_CLEARED_32)
  #undef       CANTRCV_START_SEC_VAR_CLEARED_32
  // TEST //#pragma ghs section bss=".bss.CANTRCV_RAM_VAR_CLEARED_32"
#elif defined (CANTRCV_STOP_SEC_VAR_CLEARED_32)
  #undef       CANTRCV_STOP_SEC_VAR_CLEARED_32
  // TEST //#pragma ghs section
#elif defined (CANTRCV_START_SEC_VAR_CLEARED_UNSPECIFIED)
  #undef       CANTRCV_START_SEC_VAR_CLEARED_UNSPECIFIED
  // TEST //#pragma ghs section bss=".bss.CANTRCV_RAM_VAR_CLEARED_UNSPECIFIED"
#elif defined (CANTRCV_STOP_SEC_VAR_CLEARED_UNSPECIFIED)
  #undef       CANTRCV_STOP_SEC_VAR_CLEARED_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (CANTRCV_START_SEC_VAR_UNSPECIFIED)
  #undef       CANTRCV_START_SEC_VAR_UNSPECIFIED
  // TEST //#pragma ghs section bss=".bss.CANTRCV_RAM_VAR_UNSPECIFIED"
#elif defined (CANTRCV_STOP_SEC_VAR_UNSPECIFIED)
  #undef       CANTRCV_STOP_SEC_VAR_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (CANTRCV_START_SEC_CONST_8)
  #undef       CANTRCV_START_SEC_CONST_8
  // TEST //#pragma ghs section rodata=".rodata.CANTRCV_ROM_CONST_8"
#elif defined (CANTRCV_STOP_SEC_CONST_8)
  #undef       CANTRCV_STOP_SEC_CONST_8
  // TEST //#pragma ghs section
#elif defined (CANTRCV_START_SEC_CONST_16)
  #undef       CANTRCV_START_SEC_CONST_16
  // TEST //#pragma ghs section rodata=".rodata.CANTRCV_ROM_CONST_16"
#elif defined (CANTRCV_STOP_SEC_CONST_16)
  #undef       CANTRCV_STOP_SEC_CONST_16
  // TEST //#pragma ghs section
#elif defined (CANTRCV_START_SEC_CONST_UNSPECIFIED)
  #undef       CANTRCV_START_SEC_CONST_UNSPECIFIED
  // TEST //#pragma ghs section rodata=".rodata.CANTRCV_ROM_CONST_UNSPECIFIED"
#elif defined (CANTRCV_STOP_SEC_CONST_UNSPECIFIED)
  #undef       CANTRCV_STOP_SEC_CONST_UNSPECIFIED
  // TEST //#pragma ghs section
/* Data Configuration Section for Module*/
#elif defined (CANTRCV_START_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED)
  #undef       CANTRCV_START_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
  // TEST //#pragma ghs section rodata=".rodata.CANTRCV_ROM_CONFIG_UNSPECIFIED"
#elif defined (CANTRCV_STOP_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED)
  #undef       CANTRCV_STOP_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (CANTRCV_START_SEC_CONFIG_DATA_PREBUILD_BOOLEAN)
  #undef       CANTRCV_START_SEC_CONFIG_DATA_PREBUILD_BOOLEAN
  // TEST //#pragma ghs section rodata=".rodata.CANTRCV_ROM_CONFIG_CONST_BOOLEAN"
#elif defined (CANTRCV_STOP_SEC_CONFIG_DATA_PREBUILD_BOOLEAN)
  #undef       CANTRCV_STOP_SEC_CONFIG_DATA_PREBUILD_BOOLEAN
  // TEST //#pragma ghs section
#elif defined (CANTRCV_START_SEC_CONFIG_DATA_PREBUILD_8)
  #undef       CANTRCV_START_SEC_CONFIG_DATA_PREBUILD_8
  // TEST //#pragma ghs section rodata=".rodata.CANTRCV_ROM_CONFIG_CONST_8"
#elif defined (CANTRCV_STOP_SEC_CONFIG_DATA_PREBUILD_8)
  #undef       CANTRCV_STOP_SEC_CONFIG_DATA_PREBUILD_8
  // TEST //#pragma ghs section
#elif defined (CANTRCV_START_SEC_CONFIG_DATA_PREBUILD_16)
  #undef       CANTRCV_START_SEC_CONFIG_DATA_PREBUILD_16
  // TEST //#pragma ghs section rodata=".rodata.CANTRCV_ROM_CONFIG_CONST_16"
#elif defined (CANTRCV_STOP_SEC_CONFIG_DATA_PREBUILD_16)
  #undef       CANTRCV_STOP_SEC_CONFIG_DATA_PREBUILD_16
  // TEST //#pragma ghs section
#elif defined (CANTRCV_START_SEC_CONFIG_DATA_PREBUILD_32)
  #undef       CANTRCV_START_SEC_CONFIG_DATA_PREBUILD_32
  // TEST //#pragma ghs section rodata=".rodata.CANTRCV_ROM_CONFIG_CONST_32"
#elif defined (CANTRCV_STOP_SEC_CONFIG_DATA_PREBUILD_32)
  #undef       CANTRCV_STOP_SEC_CONFIG_DATA_PREBUILD_32
  // TEST //#pragma ghs section
#elif defined (CANTRCV_START_SEC_CONFIG_DATA_PREBUILD_PTR)
  #undef       CANTRCV_START_SEC_CONFIG_DATA_PREBUILD_PTR
  // TEST //#pragma ghs section rodata=".rodata.CANTRCV_ROM_CONFIG_CONST_PTR"
#elif defined (CANTRCV_STOP_SEC_CONFIG_DATA_PREBUILD_PTR)
  #undef       CANTRCV_STOP_SEC_CONFIG_DATA_PREBUILD_PTR
  // TEST //#pragma ghs section
#elif defined (CANTRCV_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED)
  #undef       CANTRCV_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
  // TEST //#pragma ghs section rodata=".rodata.CANTRCV_ROM_CONFIG_UNSPECIFIED"
#elif defined (CANTRCV_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED)
  #undef       CANTRCV_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (CANTRCV_START_SEC_CONFIG_DATA_POSTBUILD_BOOLEAN)
  #undef       CANTRCV_START_SEC_CONFIG_DATA_POSTBUILD_BOOLEAN
  // TEST //#pragma ghs section rodata=".rodata.CANTRCV_ROM_CONFIG_CONST_BOOLEAN"
#elif defined (CANTRCV_STOP_SEC_CONFIG_DATA_POSTBUILD_BOOLEAN)
  #undef       CANTRCV_STOP_SEC_CONFIG_DATA_POSTBUILD_BOOLEAN
  // TEST //#pragma ghs section
#elif defined (CANTRCV_START_SEC_CONFIG_DATA_POSTBUILD_8)
  #undef       CANTRCV_START_SEC_CONFIG_DATA_POSTBUILD_8
  // TEST //#pragma ghs section rodata=".rodata.CANTRCV_ROM_CONFIG_CONST_8"
#elif defined (CANTRCV_STOP_SEC_CONFIG_DATA_POSTBUILD_8)
  #undef       CANTRCV_STOP_SEC_CONFIG_DATA_POSTBUILD_8
  // TEST //#pragma ghs section
#elif defined (CANTRCV_START_SEC_CONFIG_DATA_POSTBUILD_16)
  #undef       CANTRCV_START_SEC_CONFIG_DATA_POSTBUILD_16
  // TEST //#pragma ghs section rodata=".rodata.CANTRCV_ROM_CONFIG_CONST_16"
#elif defined (CANTRCV_STOP_SEC_CONFIG_DATA_POSTBUILD_16)
  #undef       CANTRCV_STOP_SEC_CONFIG_DATA_POSTBUILD_16
  // TEST //#pragma ghs section
#elif defined (CANTRCV_START_SEC_CONFIG_DATA_POSTBUILD_32)
  #undef       CANTRCV_START_SEC_CONFIG_DATA_POSTBUILD_32
  // TEST //#pragma ghs section rodata=".rodata.CANTRCV_ROM_CONFIG_CONST_32"
#elif defined (CANTRCV_STOP_SEC_CONFIG_DATA_POSTBUILD_32)
  #undef       CANTRCV_STOP_SEC_CONFIG_DATA_POSTBUILD_32
  // TEST //#pragma ghs section
#elif defined (CANTRCV_START_SEC_CONFIG_DATA_POSTBUILD_PTR)
  #undef       CANTRCV_START_SEC_CONFIG_DATA_POSTBUILD_PTR
  // TEST //#pragma ghs section rodata=".rodata.CANTRCV_ROM_CONFIG_CONST_PTR"
#elif defined (CANTRCV_STOP_SEC_CONFIG_DATA_POSTBUILD_PTR)
  #undef       CANTRCV_STOP_SEC_CONFIG_DATA_POSTBUILD_PTR
  // TEST //#pragma ghs section
/* End Configuration Section for Module*/
#elif defined (CANTRCV_START_SEC_CODE)
  #undef       CANTRCV_START_SEC_CODE
  // TEST //#pragma ghs section text=".text.CANTRCV_CODE"
  // TEST //#pragma ghs section rodata=".rodata.CANTRCV_ROM_CONST_UNSPECIFIED"
  // TEST //#pragma ghs section bss=".bss.CANTRCV_RAM_VAR_CLEARED_UNSPECIFIED"
  // TEST //#pragma ghs section data=".data.CANTRCV_RAM_VAR_INIT_UNSPECIFIED"
#elif defined (CANTRCV_STOP_SEC_CODE)
  #undef       CANTRCV_STOP_SEC_CODE
  // TEST //#pragma ghs section
#elif defined (CANTRCV_START_SEC_VAR_INIT_UNSPECIFIED)
  #undef       CANTRCV_START_SEC_VAR_INIT_UNSPECIFIED
  // TEST //#pragma ghs section data=".data.CANTRCV_RAM_VAR_INIT_UNSPECIFIED"
#elif defined (CANTRCV_STOP_SEC_VAR_INIT_UNSPECIFIED)
  #undef       CANTRCV_STOP_SEC_VAR_INIT_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (CANTRCV_START_SEC_VAR_INIT_BOOLEAN)
  #undef       CANTRCV_START_SEC_VAR_INIT_BOOLEAN
  // TEST //#pragma ghs section data=".data.CANTRCV_RAM_VAR_INIT_BOOLEAN"
#elif defined (CANTRCV_STOP_SEC_VAR_INIT_BOOLEAN)
  #undef       CANTRCV_STOP_SEC_VAR_INIT_BOOLEAN
  // TEST //#pragma ghs section
#elif defined (CANTRCV_START_SEC_VAR_INIT_8)
  #undef       CANTRCV_START_SEC_VAR_INIT_8
  // TEST //#pragma ghs section data=".data.CANTRCV_RAM_VAR_INIT_8"
#elif defined (CANTRCV_STOP_SEC_VAR_INIT_8)
  #undef       CANTRCV_STOP_SEC_VAR_INIT_8
  // TEST //#pragma ghs section
#elif defined (CANTRCV_START_SEC_VAR_INIT_16)
  #undef       CANTRCV_START_SEC_VAR_INIT_16
  // TEST //#pragma ghs section data=".data.CANTRCV_RAM_VAR_INIT_16"
#elif defined (CANTRCV_STOP_SEC_VAR_INIT_16)
  #undef       CANTRCV_STOP_SEC_VAR_INIT_16
  // TEST //#pragma ghs section
/* -------------------------------------------------------------------------- */
/*                 BswM                                                       */
/* -------------------------------------------------------------------------- */
#elif defined (BSWM_START_SEC_VAR_CLEARED_BOOLEAN)
  #undef       BSWM_START_SEC_VAR_CLEARED_BOOLEAN
  // TEST //#pragma ghs section bss=".bss.BSWM_RAM_VAR_CLEARED_BOOLEAN"
#elif defined (BSWM_STOP_SEC_VAR_CLEARED_BOOLEAN)
  #undef       BSWM_STOP_SEC_VAR_CLEARED_BOOLEAN
  // TEST //#pragma ghs section
#elif defined (BSWM_START_SEC_VAR_NO_INIT_BOOLEAN)
  #undef       BSWM_START_SEC_VAR_NO_INIT_BOOLEAN
  // TEST //#pragma ghs section bss=".bss.BSWM_RAM_VAR_NO_INIT_BOOLEAN"
#elif defined (BSWM_STOP_SEC_VAR_NO_INIT_BOOLEAN)
  #undef       BSWM_STOP_SEC_VAR_NO_INIT_BOOLEAN
  // TEST //#pragma ghs section
#elif defined (BSWM_START_SEC_VAR_NO_INIT_UNSPECIFIED)
  #undef       BSWM_START_SEC_VAR_NO_INIT_UNSPECIFIED
  // TEST //#pragma ghs section bss=".bss.BSWM_RAM_VAR_NO_INIT_UNSPECIFIED"
#elif defined (BSWM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED)
  #undef       BSWM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (BSWM_START_SEC_CONST_UNSPECIFIED)
  #undef       BSWM_START_SEC_CONST_UNSPECIFIED
  // TEST //#pragma ghs section rodata=".rodata.BSWM_ROM_CONST_UNSPECIFIED"
#elif defined (BSWM_STOP_SEC_CONST_UNSPECIFIED)
  #undef       BSWM_STOP_SEC_CONST_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (BSWM_START_SEC_CODE)
  #undef       BSWM_START_SEC_CODE
  // TEST //#pragma ghs section text=".text.BSWM_CODE"
  // TEST //#pragma ghs section rodata=".rodata.BSWM_ROM_CONST_UNSPECIFIED"
  // TEST //#pragma ghs section bss=".bss.BSWM_RAM_VAR_CLEARED_UNSPECIFIED"
  // TEST //#pragma ghs section data=".data.BSWM_RAM_VAR_INIT_UNSPECIFIED"
#elif defined (BSWM_STOP_SEC_CODE)
  #undef       BSWM_STOP_SEC_CODE
  // TEST //#pragma ghs section
#elif defined (BSWM_START_SEC_VAR_CLEARED_UNSPECIFIED)
  #undef       BSWM_START_SEC_VAR_CLEARED_UNSPECIFIED
  // TEST //#pragma ghs section bss=".bss.BSWM_RAM_VAR_CLEARED_UNSPECIFIED"
#elif defined (BSWM_STOP_SEC_VAR_CLEARED_UNSPECIFIED)
  #undef       BSWM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
  // TEST //#pragma ghs section
/* -------------------------------------------------------------------------- */
/*             ComM                                                           */
/* -------------------------------------------------------------------------- */
#elif defined (COMM_START_SEC_VAR_POWER_ON_CLEARED_8)
  #undef       COMM_START_SEC_VAR_POWER_ON_CLEARED_8
  // TEST //#pragma ghs section bss=".bss.COMM_RAM_VAR_POWER_ON_CLEARED_8"
#elif defined (COMM_STOP_SEC_VAR_POWER_ON_CLEARED_8)
  #undef       COMM_STOP_SEC_VAR_POWER_ON_CLEARED_8
  // TEST //#pragma ghs section
#elif defined (COMM_START_SEC_VAR_POWER_ON_CLEARED_16)
  #undef       COMM_START_SEC_VAR_POWER_ON_CLEARED_16
  // TEST //#pragma ghs section bss=".bss.COMM_RAM_VAR_POWER_ON_CLEARED_16"
#elif defined (COMM_STOP_SEC_VAR_POWER_ON_CLEARED_16)
  #undef       COMM_STOP_SEC_VAR_POWER_ON_CLEARED_16
  // TEST //#pragma ghs section
#elif defined (COMM_START_SEC_VAR_POWER_ON_CLEARED_UNSPECIFIED)
  #undef       COMM_START_SEC_VAR_POWER_ON_CLEARED_UNSPECIFIED
  // TEST //#pragma ghs section bss=".bss.COMM_RAM_VAR_POWER_ON_CLEARED_UNSPECIFIED"
#elif defined (COMM_STOP_SEC_VAR_POWER_ON_CLEARED_UNSPECIFIED)
  #undef       COMM_STOP_SEC_VAR_POWER_ON_CLEARED_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (COMM_START_SEC_VAR_POWER_ON_CLEARED_BOOLEAN)
  #undef       COMM_START_SEC_VAR_POWER_ON_CLEARED_BOOLEAN
  // TEST //#pragma ghs section bss=".bss.COMM_RAM_VAR_POWER_ON_CLEARED_BOOLEAN"
#elif defined (COMM_STOP_SEC_VAR_POWER_ON_CLEARED_BOOLEAN)
  #undef       COMM_STOP_SEC_VAR_POWER_ON_CLEARED_BOOLEAN
  // TEST //#pragma ghs section
#elif defined (COMM_START_SEC_VAR_CLEARED_8)
  #undef       COMM_START_SEC_VAR_CLEARED_8
  // TEST //#pragma ghs section bss=".bss.COMM_RAM_VAR_CLEARED_8"
#elif defined (COMM_STOP_SEC_VAR_CLEARED_8)
  #undef       COMM_STOP_SEC_VAR_CLEARED_8
  // TEST //#pragma ghs section
#elif defined (COMM_START_SEC_VAR_CLEARED_16)
  #undef       COMM_START_SEC_VAR_CLEARED_16
  // TEST //#pragma ghs section bss=".bss.COMM_RAM_VAR_CLEARED_16"
#elif defined (COMM_STOP_SEC_VAR_CLEARED_16)
  #undef       COMM_STOP_SEC_VAR_CLEARED_16
  // TEST //#pragma ghs section
#elif defined (COMM_START_SEC_VAR_CLEARED_32)
  #undef       COMM_START_SEC_VAR_CLEARED_32
  // TEST //#pragma ghs section bss=".bss.COMM_RAM_VAR_CLEARED_32"
#elif defined (COMM_STOP_SEC_VAR_CLEARED_32)
  #undef       COMM_STOP_SEC_VAR_CLEARED_32
  // TEST //#pragma ghs section
#elif defined (COMM_START_SEC_VAR_CLEARED_BOOLEAN)
  #undef       COMM_START_SEC_VAR_CLEARED_BOOLEAN
  // TEST //#pragma ghs section bss=".bss.COMM_RAM_VAR_CLEARED_BOOLEAN"
#elif defined (COMM_STOP_SEC_VAR_CLEARED_BOOLEAN)
  #undef       COMM_STOP_SEC_VAR_CLEARED_BOOLEAN
  // TEST //#pragma ghs section
#elif defined (COMM_START_SEC_VAR_CLEARED_UNSPECIFIED)
  #undef       COMM_START_SEC_VAR_CLEARED_UNSPECIFIED
  // TEST //#pragma ghs section bss=".bss.COMM_RAM_VAR_CLEARED_UNSPECIFIED"
#elif defined (COMM_STOP_SEC_VAR_CLEARED_UNSPECIFIED)
  #undef       COMM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (COMM_START_SEC_VAR_NO_INIT_8)
  #undef       COMM_START_SEC_VAR_NO_INIT_8
  // TEST //#pragma ghs section bss=".bss.COMM_RAM_VAR_NO_INIT_8"
#elif defined (COMM_STOP_SEC_VAR_NO_INIT_8)
  #undef       COMM_STOP_SEC_VAR_NO_INIT_8
  // TEST //#pragma ghs section
#elif defined (COMM_START_SEC_VAR_NO_INIT_16)
  #undef       COMM_START_SEC_VAR_NO_INIT_16
  // TEST //#pragma ghs section bss=".bss.COMM_RAM_VAR_NO_INIT_16"
#elif defined (COMM_STOP_SEC_VAR_NO_INIT_16)
  #undef       COMM_STOP_SEC_VAR_NO_INIT_16
  // TEST //#pragma ghs section
#elif defined (COMM_START_SEC_VAR_NO_INIT_32)
  #undef       COMM_START_SEC_VAR_NO_INIT_32
  // TEST //#pragma ghs section bss=".bss.COMM_RAM_VAR_NO_INIT_32"
#elif defined (COMM_STOP_SEC_VAR_NO_INIT_32)
  #undef       COMM_STOP_SEC_VAR_NO_INIT_32
  // TEST //#pragma ghs section
#elif defined (COMM_START_SEC_VAR_SAVED_ZONE_16)
  #undef       COMM_START_SEC_VAR_SAVED_ZONE_16
  // TEST //#pragma ghs section bss=".bss.COMM_RAM_VAR_SAVED_ZONE_16"
#elif defined (COMM_STOP_SEC_VAR_SAVED_ZONE_16)
  #undef       COMM_STOP_SEC_VAR_SAVED_ZONE_16
  // TEST //#pragma ghs section
#elif defined (COMM_START_SEC_VAR_SAVED_ZONE_8)
  #undef       COMM_START_SEC_VAR_SAVED_ZONE_8
  // TEST //#pragma ghs section bss=".bss.COMM_RAM_VAR_SAVED_ZONE_8"
#elif defined (COMM_STOP_SEC_VAR_SAVED_ZONE_8)
  #undef       COMM_STOP_SEC_VAR_SAVED_ZONE_8
  // TEST //#pragma ghs section
#elif defined (COMM_START_SEC_VAR_NO_INIT_UNSPECIFIED)
  #undef       COMM_START_SEC_VAR_NO_INIT_UNSPECIFIED
  // TEST //#pragma ghs section bss=".bss.COMM_RAM_VAR_NO_INIT_UNSPECIFIED"
#elif defined (COMM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED)
  #undef       COMM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (COMM_START_SEC_VAR_SAVED_ZONE_UNSPECIFIED)
  #undef       COMM_START_SEC_VAR_SAVED_ZONE_UNSPECIFIED
  // TEST //#pragma ghs section bss=".bss.COMM_RAM_VAR_SAVED_ZONE_UNSPECIFIED"
#elif defined (COMM_STOP_SEC_VAR_SAVED_ZONE_UNSPECIFIED)
  #undef       COMM_STOP_SEC_VAR_SAVED_ZONE_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (COMM_START_SEC_CONST_8)
  #undef       COMM_START_SEC_CONST_8
  // TEST //#pragma ghs section rodata=".rodata.COMM_ROM_CONST_8"
#elif defined (COMM_STOP_SEC_CONST_8)
  #undef       COMM_STOP_SEC_CONST_8
  // TEST //#pragma ghs section
#elif defined (COMM_START_SEC_CONST_16)
  #undef       COMM_START_SEC_CONST_16
  // TEST //#pragma ghs section rodata=".rodata.COMM_ROM_CONST_16"
#elif defined (COMM_STOP_SEC_CONST_16)
  #undef       COMM_STOP_SEC_CONST_16
  // TEST //#pragma ghs section
#elif defined (COMM_START_SEC_CONST_UNSPECIFIED)
  #undef       COMM_START_SEC_CONST_UNSPECIFIED
  // TEST //#pragma ghs section rodata=".rodata.COMM_ROM_CONST_UNSPECIFIED"
#elif defined (COMM_STOP_SEC_CONST_UNSPECIFIED)
  #undef       COMM_STOP_SEC_CONST_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (COMM_START_SEC_CODE)
  #undef       COMM_START_SEC_CODE
  // TEST //#pragma ghs section text=".text.COMM_CODE"
  // TEST //#pragma ghs section rodata=".rodata.COMM_ROM_CONST_UNSPECIFIED"
  // TEST //#pragma ghs section bss=".bss.COMM_RAM_VAR_CLEARED_UNSPECIFIED"
  // TEST //#pragma ghs section data=".data.COMM_RAM_VAR_INIT_UNSPECIFIED"
#elif defined (COMM_STOP_SEC_CODE)
  #undef       COMM_STOP_SEC_CODE
  // TEST //#pragma ghs section
/* -------------------------------------------------------------------------- */
/*             LINIF                                                          */
/* -------------------------------------------------------------------------- */
#elif defined (LINIF_START_SEC_CODE)
  #undef       LINIF_START_SEC_CODE
  // TEST //#pragma ghs section text=".text.LINIF_CODE"
  // TEST //#pragma ghs section rodata=".rodata.LINIF_ROM_CONST_UNSPECIFIED"
  // TEST //#pragma ghs section bss=".bss.LINIF_RAM_VAR_CLEARED_UNSPECIFIED"
  // TEST //#pragma ghs section data=".data.LINIF_RAM_VAR_INIT_UNSPECIFIED"
#elif defined (LINIF_STOP_SEC_CODE)
  #undef       LINIF_STOP_SEC_CODE
  // TEST //#pragma ghs section
#elif defined (LINIF_START_SEC_VAR_CLEARED_BOOLEAN)
  #undef       LINIF_START_SEC_VAR_CLEARED_BOOLEAN
  // TEST //#pragma ghs section bss=".bss.LINIF_RAM_VAR_CLEARED_BOOLEAN"
#elif defined (LINIF_STOP_SEC_VAR_CLEARED_BOOLEAN)
  #undef       LINIF_STOP_SEC_VAR_CLEARED_BOOLEAN
  // TEST //#pragma ghs section
#elif defined (LINIF_START_SEC_VAR_NO_INIT_UNSPECIFIED)
  #undef       LINIF_START_SEC_VAR_NO_INIT_UNSPECIFIED
  // TEST //#pragma ghs section bss=".bss.LINIF_RAM_VAR_NO_INIT_UNSPECIFIED"
#elif defined (LINIF_STOP_SEC_VAR_NO_INIT_UNSPECIFIED)
  #undef       LINIF_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (LINIF_START_SEC_CONST_UNSPECIFIED)
  #undef       LINIF_START_SEC_CONST_UNSPECIFIED
  // TEST //#pragma ghs section rodata=".rodata.LINIF_ROM_CONST_UNSPECIFIED"
#elif defined (LINIF_STOP_SEC_CONST_UNSPECIFIED)
  #undef       LINIF_STOP_SEC_CONST_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (LINIF_START_SEC_DBTOC_CONST_UNSPECIFIED)
  #undef       LINIF_START_SEC_DBTOC_CONST_UNSPECIFIED
  // TEST //#pragma ghs section rodata=".rodata.LINIF_ROM_CONFIG_UNSPECIFIED"
#elif defined (LINIF_STOP_SEC_DBTOC_CONST_UNSPECIFIED)
  #undef       LINIF_STOP_SEC_DBTOC_CONST_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (LINIF_START_SEC_CONST_8)
  #undef       LINIF_START_SEC_CONST_8
  // TEST //#pragma ghs section rodata=".rodata.LINIF_ROM_CONST_8"
#elif defined (LINIF_STOP_SEC_CONST_8)
  #undef       LINIF_STOP_SEC_CONST_8
  // TEST //#pragma ghs section
#elif defined (LINIF_START_SEC_CONST_UNSPECIFIED)
  #undef       LINIF_START_SEC_CONST_UNSPECIFIED
  // TEST //#pragma ghs section rodata=".rodata.LINIF_ROM_CONFIG_UNSPECIFIED"
#elif defined (LINIF_STOP_SEC_CONST_UNSPECIFIED)
  #undef       LINIF_STOP_SEC_CONST_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (LINIF_START_SEC_VAR_NO_INIT_8)
  #undef       LINIF_START_SEC_VAR_NO_INIT_8
  // TEST //#pragma ghs section bss=".bss.LINIF_RAM_VAR_NO_INIT_8"
#elif defined (LINIF_STOP_SEC_VAR_NO_INIT_8)
  #undef       LINIF_STOP_SEC_VAR_NO_INIT_8
  // TEST //#pragma ghs section
/* -------------------------------------------------------------------------- */
/*             LINTP                                                          */
/* -------------------------------------------------------------------------- */
#elif defined (LINTP_START_SEC_CODE)
  #undef       LINTP_START_SEC_CODE
  // TEST //#pragma ghs section text=".text.LINTP_CODE"
  // TEST //#pragma ghs section rodata=".rodata.LINTP_ROM_CONST_UNSPECIFIED"
  // TEST //#pragma ghs section bss=".bss.LINTP_RAM_VAR_CLEARED_UNSPECIFIED"
  // TEST //#pragma ghs section data=".data.LINTP_RAM_VAR_INIT_UNSPECIFIED"
#elif defined (LINTP_STOP_SEC_CODE)
  #undef       LINTP_STOP_SEC_CODE
  // TEST //#pragma ghs section
#elif defined (LINTP_START_SEC_VAR_CLEARED_BOOLEAN)
  #undef       LINTP_START_SEC_VAR_CLEARED_BOOLEAN
  // TEST //#pragma ghs section bss=".bss.LINTP_RAM_VAR_CLEARED_BOOLEAN"
#elif defined (LINTP_STOP_SEC_VAR_CLEARED_BOOLEAN)
  #undef       LINTP_STOP_SEC_VAR_CLEARED_BOOLEAN
  // TEST //#pragma ghs section
#elif defined (LINTP_START_SEC_VAR_NO_INIT_UNSPECIFIED)
  #undef       LINTP_START_SEC_VAR_NO_INIT_UNSPECIFIED
  // TEST //#pragma ghs section bss=".bss.LINTP_RAM_VAR_NO_INIT_UNSPECIFIED"
#elif defined (LINTP_STOP_SEC_VAR_NO_INIT_UNSPECIFIED)
  #undef       LINTP_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (LINTP_START_SEC_VAR_CLEARED_16)
  #undef       LINTP_START_SEC_VAR_CLEARED_16
  // TEST //#pragma ghs section bss=".bss.LINTP_RAM_VAR_CLEARED_16"
#elif defined (LINTP_STOP_SEC_VAR_CLEARED_16)
  #undef       LINTP_STOP_SEC_VAR_CLEARED_16
  // TEST //#pragma ghs section
#elif defined (LINTP_START_SEC_VAR_NO_INIT_8)
  #undef       LINTP_START_SEC_VAR_NO_INIT_8
  // TEST //#pragma ghs section bss=".bss.LINTP_RAM_VAR_NO_INIT_8"
#elif defined (LINTP_STOP_SEC_VAR_NO_INIT_8)
  #undef       LINTP_STOP_SEC_VAR_NO_INIT_8
  // TEST //#pragma ghs section
#elif defined (LINTP_START_SEC_DBTOC_CONST_UNSPECIFIED)
  #undef       LINTP_START_SEC_DBTOC_CONST_UNSPECIFIED
  // TEST //#pragma ghs section rodata=".rodata.LINTP_ROM_CONFIG_UNSPECIFIED"
#elif defined (LINTP_STOP_SEC_DBTOC_CONST_UNSPECIFIED)
  #undef       LINTP_STOP_SEC_DBTOC_CONST_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (LINTP_START_SEC_CONST_UNSPECIFIED)
  #undef       LINTP_START_SEC_CONST_UNSPECIFIED
  // TEST //#pragma ghs section rodata=".rodata.LINTP_ROM_CONFIG_UNSPECIFIED"
#elif defined (LINTP_STOP_SEC_CONST_UNSPECIFIED)
  #undef       LINTP_STOP_SEC_CONST_UNSPECIFIED
  // TEST //#pragma ghs section
/* -------------------------------------------------------------------------- */
/*             Com                                                            */
/* -------------------------------------------------------------------------- */
#elif defined (COM_START_SEC_VAR_POWER_ON_CLEARED_8)
  #undef       COM_START_SEC_VAR_POWER_ON_CLEARED_8
  // TEST //#pragma ghs section bss=".bss.COM_RAM_VAR_POWER_ON_CLEARED_8"
#elif defined (COM_STOP_SEC_VAR_POWER_ON_CLEARED_8)
  #undef       COM_STOP_SEC_VAR_POWER_ON_CLEARED_8
  // TEST //#pragma ghs section
#elif defined (COM_START_SEC_VAR_POWER_ON_CLEARED_16)
  #undef       COM_START_SEC_VAR_POWER_ON_CLEARED_16
  // TEST //#pragma ghs section bss=".bss.COM_RAM_VAR_POWER_ON_CLEARED_16"
#elif defined (COM_STOP_SEC_VAR_POWER_ON_CLEARED_16)
  #undef       COM_STOP_SEC_VAR_POWER_ON_CLEARED_16
  // TEST //#pragma ghs section
#elif defined (COM_START_SEC_VAR_POWER_ON_CLEARED_UNSPECIFIED)
  #undef       COM_START_SEC_VAR_POWER_ON_CLEARED_UNSPECIFIED
  // TEST //#pragma ghs section bss=".bss.COM_RAM_VAR_POWER_ON_CLEARED_UNSPECIFIED"
#elif defined (COM_STOP_SEC_VAR_POWER_ON_CLEARED_UNSPECIFIED)
  #undef       COM_STOP_SEC_VAR_POWER_ON_CLEARED_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (COM_START_SEC_VAR_POWER_ON_CLEARED_BOOLEAN)
  #undef       COM_START_SEC_VAR_POWER_ON_CLEARED_BOOLEAN
  // TEST //#pragma ghs section bss=".bss.COM_RAM_VAR_POWER_ON_CLEARED_BOOLEAN"
#elif defined (COM_STOP_SEC_VAR_POWER_ON_CLEARED_BOOLEAN)
  #undef       COM_STOP_SEC_VAR_POWER_ON_CLEARED_BOOLEAN
  // TEST //#pragma ghs section
#elif defined (COM_START_SEC_VAR_CLEARED_8)
  #undef       COM_START_SEC_VAR_CLEARED_8
  // TEST //#pragma ghs section bss=".bss.COM_RAM_VAR_CLEARED_8"
#elif defined (COM_STOP_SEC_VAR_CLEARED_8)
  #undef       COM_STOP_SEC_VAR_CLEARED_8
  // TEST //#pragma ghs section
#elif defined (COM_START_SEC_VAR_CLEARED_16)
  #undef       COM_START_SEC_VAR_CLEARED_16
  // TEST //#pragma ghs section bss=".bss.COM_RAM_VAR_CLEARED_16"
#elif defined (COM_STOP_SEC_VAR_CLEARED_16)
  #undef       COM_STOP_SEC_VAR_CLEARED_16
  // TEST //#pragma ghs section
#elif defined (COM_START_SEC_VAR_CLEARED_BOOLEAN)
  #undef       COM_START_SEC_VAR_CLEARED_BOOLEAN
  // TEST //#pragma ghs section bss=".bss.COM_RAM_VAR_CLEARED_BOOLEAN"
#elif defined (COM_STOP_SEC_VAR_CLEARED_BOOLEAN)
  #undef       COM_STOP_SEC_VAR_CLEARED_BOOLEAN
  // TEST //#pragma ghs section
#elif defined (COM_START_SEC_VAR_CLEARED_UNSPECIFIED)
  #undef       COM_START_SEC_VAR_CLEARED_UNSPECIFIED
  // TEST //#pragma ghs section bss=".bss.COM_RAM_VAR_CLEARED_UNSPECIFIED"
#elif defined (COM_STOP_SEC_VAR_CLEARED_UNSPECIFIED)
  #undef       COM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (COM_START_SEC_VAR_CLEARED_UNSPECIFIED_ALIGN4)
  #undef       COM_START_SEC_VAR_CLEARED_UNSPECIFIED_ALIGN4
  // TEST //#pragma ghs section bss=".bss.COM_RAM_VAR_CLEARED_UNSPECIFIED"
  #pragma alignvar (4)
#elif defined (COM_STOP_SEC_VAR_CLEARED_UNSPECIFIED_ALIGN4)
  #undef       COM_STOP_SEC_VAR_CLEARED_UNSPECIFIED_ALIGN4
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (COM_START_SEC_VAR_NOINIT_8)
  #undef       COM_START_SEC_VAR_NOINIT_8
  // TEST //#pragma ghs section bss=".bss.COM_RAM_VAR_NO_INIT_8"
#elif defined (COM_STOP_SEC_VAR_NOINIT_8)
  #undef       COM_STOP_SEC_VAR_NOINIT_8
  // TEST //#pragma ghs section
#elif defined (COM_START_SEC_VAR_NOINIT_16)
  #undef       COM_START_SEC_VAR_NOINIT_16
  // TEST //#pragma ghs section bss=".bss.COM_RAM_VAR_NO_INIT_16"
#elif defined (COM_STOP_SEC_VAR_NOINIT_16)
  #undef       COM_STOP_SEC_VAR_NOINIT_16
  // TEST //#pragma ghs section
#elif defined (COM_START_SEC_VAR_NOINIT_32)
  #undef       COM_START_SEC_VAR_NOINIT_32
  // TEST //#pragma ghs section bss=".bss.COM_RAM_VAR_NO_INIT_32"
#elif defined (COM_STOP_SEC_VAR_NOINIT_32)
  #undef       COM_STOP_SEC_VAR_NOINIT_32
  // TEST //#pragma ghs section
#elif defined (COM_START_SEC_VAR_SAVED_ZONE_16)
  #undef       COM_START_SEC_VAR_SAVED_ZONE_16
  // TEST //#pragma ghs section bss=".bss.COM_SAVED_RAM_16"
#elif defined (COM_STOP_SEC_VAR_SAVED_ZONE_16)
  #undef       COM_STOP_SEC_VAR_SAVED_ZONE_16
  // TEST //#pragma ghs section
#elif defined (COM_START_SEC_VAR_SAVED_ZONE_8)
  #undef       COM_START_SEC_VAR_SAVED_ZONE_8
  // TEST //#pragma ghs section bss=".bss.COM_SAVED_RAM_8"
#elif defined (COM_STOP_SEC_VAR_SAVED_ZONE_8)
  #undef       COM_STOP_SEC_VAR_SAVED_ZONE_8
  // TEST //#pragma ghs section
#elif defined (COM_START_SEC_VAR_SAVED_ZONE_UNSPECIFIED)
  #undef       COM_START_SEC_VAR_SAVED_ZONE_UNSPECIFIED
  // TEST //#pragma ghs section bss=".bss.COM_SAVED_RAM_UNSPECIFIED"
#elif defined (COM_STOP_SEC_VAR_SAVED_ZONE_UNSPECIFIED)
  #undef       COM_STOP_SEC_VAR_SAVED_ZONE_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (COM_START_SEC_CONST_8)
  #undef       COM_START_SEC_CONST_8
  // TEST //#pragma ghs section rodata=".rodata.COM_ROM_CONST_8"
#elif defined (COM_STOP_SEC_CONST_8)
  #undef       COM_STOP_SEC_CONST_8
  // TEST //#pragma ghs section
#elif defined (COM_START_SEC_CONST_16)
  #undef       COM_START_SEC_CONST_16
  // TEST //#pragma ghs section rodata=".rodata.COM_ROM_CONST_16"
#elif defined (COM_STOP_SEC_CONST_16)
  #undef       COM_STOP_SEC_CONST_16
  // TEST //#pragma ghs section
#elif defined (COM_START_SEC_CONST_32)
  #undef       COM_START_SEC_CONST_32
  // TEST //#pragma ghs section rodata=".rodata.COM_ROM_CONST_32"
#elif defined (COM_STOP_SEC_CONST_32)
  #undef       COM_STOP_SEC_CONST_32
  // TEST //#pragma ghs section
#elif defined (COM_START_SEC_CONST_64)
  #undef       COM_START_SEC_CONST_64
  // TEST //#pragma ghs section rodata=".rodata.COM_ROM_CONST_64"
#elif defined (COM_STOP_SEC_CONST_64)
  #undef       COM_STOP_SEC_CONST_64
  // TEST //#pragma ghs section
#elif defined (COM_START_SEC_CONST_UNSPECIFIED)
  #undef       COM_START_SEC_CONST_UNSPECIFIED
  // TEST //#pragma ghs section rodata=".rodata.COM_ROM_CONST_UNSPECIFIED"
#elif defined (COM_STOP_SEC_CONST_UNSPECIFIED)
  #undef       COM_STOP_SEC_CONST_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (COM_START_SEC_CODE)
  #undef       COM_START_SEC_CODE
  // TEST //#pragma ghs section text=".text.COM_CODE"
  // TEST //#pragma ghs section rodata=".rodata.COM_ROM_CONST_UNSPECIFIED"
  // TEST //#pragma ghs section bss=".bss.COM_RAM_VAR_CLEARED_UNSPECIFIED"
  // TEST //#pragma ghs section data=".data.COM_RAM_VAR_INIT_UNSPECIFIED"
#elif defined (COM_STOP_SEC_CODE)
  #undef       COM_STOP_SEC_CODE
  // TEST //#pragma ghs section
#elif defined (COM_START_SEC_APPL_CODE)
  #undef       COM_START_SEC_APPL_CODE
  // TEST //#pragma ghs section text=".text.COM_APPL_CODE"
  // TEST //#pragma ghs section rodata=".rodata.COM_ROM_CONST_UNSPECIFIED"
  // TEST //#pragma ghs section bss=".bss.COM_RAM_VAR_CLEARED_UNSPECIFIED"
  // TEST //#pragma ghs section data=".data.COM_RAM_VAR_INIT_UNSPECIFIED"
#elif defined (COM_STOP_SEC_APPL_CODE)
  #undef       COM_STOP_SEC_APPL_CODE
  // TEST //#pragma ghs section
#elif defined (COM_START_SEC_VAR_NO_INIT_UNSPECIFIED)
  #undef       COM_START_SEC_VAR_NO_INIT_UNSPECIFIED
  // TEST //#pragma ghs section bss=".bss.COM_RAM_VAR_NO_INIT_UNSPECIFIED"
#elif defined (COM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED)
  #undef       COM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (COM_START_SEC_VAR_NOINIT_UNSPECIFIED)
  #undef       COM_START_SEC_VAR_NOINIT_UNSPECIFIED
  // TEST //#pragma ghs section bss=".bss.COM_RAM_VAR_NO_INIT_UNSPECIFIED"
#elif defined (COM_STOP_SEC_VAR_NOINIT_UNSPECIFIED)
  #undef       COM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (COM_START_SEC_VAR_NO_INIT_8)
  #undef       COM_START_SEC_VAR_NO_INIT_8
  // TEST //#pragma ghs section bss=".bss.COM_RAM_VAR_NO_INIT_8"
#elif defined (COM_STOP_SEC_VAR_NO_INIT_8)
  #undef       COM_STOP_SEC_VAR_NO_INIT_8
  // TEST //#pragma ghs section
#elif defined (COM_START_SEC_VAR_INIT_16)
  #undef       COM_START_SEC_VAR_INIT_16
  // TEST //#pragma ghs section data=".data.COM_RAM_VAR_INIT_16"
#elif defined (COM_STOP_SEC_VAR_INIT_16)
  #undef       COM_STOP_SEC_VAR_INIT_16
  // TEST //#pragma ghs section
#elif defined (COM_START_SEC_VAR_NO_INIT_16)
  #undef       COM_START_SEC_VAR_NO_INIT_16
  // TEST //#pragma ghs section bss=".bss.COM_RAM_VAR_NO_INIT_16"
#elif defined (COM_STOP_SEC_VAR_NO_INIT_16)
  #undef       COM_STOP_SEC_VAR_NO_INIT_16
  // TEST //#pragma ghs section
#elif defined (COM_START_SEC_VAR_INIT_UNSPECIFIED)
  #undef       COM_START_SEC_VAR_INIT_UNSPECIFIED
  // TEST //#pragma ghs section data=".data.COM_RAM_VAR_INIT_UNSPECIFIED"
#elif defined (COM_STOP_SEC_VAR_INIT_UNSPECIFIED)
  #undef       COM_STOP_SEC_VAR_INIT_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (COM_START_SEC_VAR_INIT_32)
  #undef       COM_START_SEC_VAR_INIT_32
  // TEST //#pragma ghs section data=".data.COM_RAM_VAR_INIT_32"
#elif defined (COM_STOP_SEC_VAR_INIT_32)
  #undef       COM_STOP_SEC_VAR_INIT_32
  // TEST //#pragma ghs section
#elif defined (COM_START_SEC_VAR_INIT_8)
  #undef       COM_START_SEC_VAR_INIT_8
  // TEST //#pragma ghs section data=".data.COM_RAM_VAR_INIT_8"
#elif defined (COM_STOP_SEC_VAR_INIT_8)
  #undef       COM_STOP_SEC_VAR_INIT_8
  // TEST //#pragma ghs section
/* -------------------------------------------------------------------------- */
/*                  PduR                                                      */
/* -------------------------------------------------------------------------- */

#elif defined (PDUR_START_SEC_VAR_CLEARED_BOOLEAN)
  #undef       PDUR_START_SEC_VAR_CLEARED_BOOLEAN
  // TEST //#pragma ghs section bss=".bss.PDUR_RAM_VAR_CLEARED_BOOLEAN"
#elif defined (PDUR_STOP_SEC_VAR_CLEARED_BOOLEAN)
  #undef       PDUR_STOP_SEC_VAR_CLEARED_BOOLEAN
#elif defined (PDUR_START_SEC_CONST_UNSPECIFIED)
  #undef       PDUR_START_SEC_CONST_UNSPECIFIED
  // TEST //#pragma ghs section rodata=".rodata.PDUR_ROM_CONST_UNSPECIFIED"
#elif defined (PDUR_STOP_SEC_CONST_UNSPECIFIED)
  #undef       PDUR_STOP_SEC_CONST_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (PDUR_START_SEC_VAR_NO_INIT_16)
  #undef       PDUR_START_SEC_VAR_NO_INIT_16
  // TEST //#pragma ghs section bss=".bss.PDUR_RAM_VAR_NO_INIT_16"
#elif defined (PDUR_STOP_SEC_VAR_NO_INIT_16)
  #undef       PDUR_STOP_SEC_VAR_NO_INIT_16
  // TEST //#pragma ghs section
#elif defined (PDUR_START_SEC_VAR_NO_INIT_UNSPECIFIED)
  #undef       PDUR_START_SEC_VAR_NO_INIT_UNSPECIFIED
  // TEST //#pragma ghs section bss=".bss.PDUR_RAM_VAR_NO_INIT_UNSPECIFIED"
#elif defined (PDUR_STOP_SEC_VAR_NO_INIT_UNSPECIFIED)
  #undef       PDUR_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (PDUR_START_SEC_VAR_NO_INIT_8)
  #undef       PDUR_START_SEC_VAR_NO_INIT_8
  // TEST //#pragma ghs section bss=".bss.PDUR_RAM_VAR_NO_INIT_8"
#elif defined (PDUR_STOP_SEC_VAR_NO_INIT_8)
  #undef       PDUR_STOP_SEC_VAR_NO_INIT_8
  // TEST //#pragma ghs section
#elif defined (PDUR_START_SEC_CONFIG_VAR_NO_INIT_8)
  #undef       PDUR_START_SEC_CONFIG_VAR_NO_INIT_8
  // TEST //#pragma ghs section rodata=".rodata.PDUR_ROM_CONFIG_NO_INIT_8"
#elif defined (PDUR_STOP_SEC_CONFIG_VAR_NO_INIT_8)
  #undef       PDUR_STOP_SEC_CONFIG_VAR_NO_INIT_8
  // TEST //#pragma ghs section
#elif defined (PDUR_START_SEC_VAR_CLEARED_8)
  #undef       PDUR_START_SEC_VAR_CLEARED_8
  // TEST //#pragma ghs section bss=".bss.PDUR_RAM_VAR_CLEARED_8"
#elif defined (PDUR_STOP_SEC_VAR_CLEARED_8)
  #undef       PDUR_STOP_SEC_VAR_CLEARED_8
  // TEST //#pragma ghs section
#elif defined (PDUR_START_SEC_VAR_CLEARED_UNSPECIFIED)
  #undef       PDUR_START_SEC_VAR_CLEARED_UNSPECIFIED
  // TEST //#pragma ghs section bss=".bss.PDUR_RAM_VAR_CLEARED_UNSPECIFIED"
#elif defined (PDUR_STOP_SEC_VAR_CLEARED_UNSPECIFIED)
  #undef       PDUR_STOP_SEC_VAR_CLEARED_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (PDUR_START_SEC_VAR_INIT_PTR)
  #undef       PDUR_START_SEC_VAR_INIT_PTR
  // TEST //#pragma ghs section data=".data.PDUR_RAM_VAR_INIT_PTR"
#elif defined (PDUR_STOP_SEC_VAR_INIT_PTR)
  #undef       PDUR_STOP_SEC_VAR_INIT_PTR
  // TEST //#pragma ghs section
#elif defined (PDUR_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED)
  #undef       PDUR_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
  // TEST //#pragma ghs section rodata=".rodata.(PDUR_ROM_CONFIG_UNSPECIFIED"
#elif defined (PDUR_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED)
  #undef       PDUR_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (PDUR_START_SEC_VAR_INIT_UNSPECIFIED)
  #undef       PDUR_START_SEC_VAR_INIT_UNSPECIFIED
  // TEST //#pragma ghs section data=".data.PDUR_RAM_VAR_INIT_UNSPECIFIED"
#elif defined (PDUR_STOP_SEC_VAR_INIT_UNSPECIFIED)
  #undef       PDUR_STOP_SEC_VAR_INIT_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (PDUR_START_SEC_VAR_INIT_32)
  #undef       PDUR_START_SEC_VAR_INIT_32
  // TEST //#pragma ghs section data=".data.PDUR_RAM_VAR_INIT_32"
#elif defined (PDUR_STOP_SEC_VAR_INIT_32)
  #undef       PDUR_STOP_SEC_VAR_INIT_32
  // TEST //#pragma ghs section
#elif defined (PDUR_START_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED)
  #undef       PDUR_START_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
  // TEST //#pragma ghs section rodata=".rodata.PDUR_ROM_CONFIG_UNSPECIFIED"
#elif defined (PDUR_STOP_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED)
  #undef       PDUR_STOP_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (PDUR_START_SEC_VAR_INIT_8)
  #undef       PDUR_START_SEC_VAR_INIT_8
  // TEST //#pragma ghs section data=".data.PDUR_RAM_VAR_INIT_8"
#elif defined (PDUR_STOP_SEC_VAR_INIT_8)
  #undef       PDUR_STOP_SEC_VAR_INIT_8
  // TEST //#pragma ghs section
#elif defined (PDUR_START_SEC_VAR_INIT_16)
  #undef       PDUR_START_SEC_VAR_INIT_16
  // TEST //#pragma ghs section data=".data.PDUR_RAM_VAR_INIT_16"
#elif defined (PDUR_STOP_SEC_VAR_INIT_16)
  #undef       PDUR_STOP_SEC_VAR_INIT_16
  // TEST //#pragma ghs section
#elif defined (PDUR_START_SEC_CONST_SAVED_RECOVERY_ZONE)
  #undef       PDUR_START_SEC_CONST_SAVED_RECOVERY_ZONE
  // TEST //#pragma ghs section rodata=".rodata.PDUR_ROM_SAVED_RECOVERY_ZONE"
#elif defined (PDUR_STOP_SEC_CONST_SAVED_RECOVERY_ZONE)
  #undef       PDUR_STOP_SEC_CONST_SAVED_RECOVERY_ZONE
  // TEST //#pragma ghs section
#elif defined (PDUR_START_SEC_CODE)
  #undef       PDUR_START_SEC_CODE
  // TEST //#pragma ghs section text=".text.PDUR_CODE"
  // TEST //#pragma ghs section rodata=".rodata.PDUR_ROM_CONST_UNSPECIFIED"
  // TEST //#pragma ghs section bss=".bss.PDUR_RAM_VAR_CLEARED_UNSPECIFIED"
  // TEST //#pragma ghs section data=".data.PDUR_RAM_VAR_INIT_UNSPECIFIED"
#elif defined (PDUR_STOP_SEC_CODE)
  #undef       PDUR_STOP_SEC_CODE
  // TEST //#pragma ghs section

/* -------------------------------------------------------------------------- */
/*             IpduM                                                          */
/* -------------------------------------------------------------------------- */
#elif defined (IPDUM_START_SEC_VAR_NO_INIT_BOOLEAN)
  #undef       IPDUM_START_SEC_VAR_NO_INIT_BOOLEAN
  // TEST //#pragma ghs section bss=".bss.IPDUM_RAM_VAR_NO_INIT_BOOLEAN"
#elif defined (IPDUM_STOP_SEC_VAR_NO_INIT_BOOLEAN)
  #undef       IPDUM_STOP_SEC_VAR_NO_INIT_BOOLEAN
  // TEST //#pragma ghs section
#elif defined (IPDUM_START_SEC_VAR_NO_INIT_8)
  #undef       IPDUM_START_SEC_VAR_NO_INIT_8
  // TEST //#pragma ghs section bss=".bss.IPDUM_RAM_VAR_NO_INIT_8"
#elif defined (IPDUM_STOP_SEC_VAR_NO_INIT_8)
  #undef       IPDUM_STOP_SEC_VAR_NO_INIT_8
  // TEST //#pragma ghs section
#elif defined (IPDUM_START_SEC_VAR_NO_INIT_16)
  #undef       IPDUM_START_SEC_VAR_NO_INIT_16
  // TEST //#pragma ghs section bss=".bss.IPDUM_RAM_VAR_NO_INIT_16"
#elif defined (IPDUM_STOP_SEC_VAR_NO_INIT_16)
  #undef       IPDUM_STOP_SEC_VAR_NO_INIT_16
  // TEST //#pragma ghs section
#elif defined (IPDUM_START_SEC_VAR_NO_INIT_32)
  #undef       IPDUM_START_SEC_VAR_NO_INIT_32
  // TEST //#pragma ghs section bss=".bss.IPDUM_RAM_VAR_NO_INIT_32"
#elif defined (IPDUM_STOP_SEC_VAR_NO_INIT_32)
  #undef       IPDUM_STOP_SEC_VAR_NO_INIT_32
  // TEST //#pragma ghs section
#elif defined (IPDUM_START_SEC_VAR_NO_INIT_UNSPECIFIED)
  #undef       IPDUM_START_SEC_VAR_NO_INIT_UNSPECIFIED
  // TEST //#pragma ghs section bss=".bss.IPDUM_RAM_VAR_NO_INIT_UNSPECIFIED"
#elif defined (IPDUM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED)
  #undef       IPDUM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (IPDUM_START_SEC_VAR_CLEARED_BOOLEAN)
  #undef       IPDUM_START_SEC_VAR_CLEARED_BOOLEAN
  // TEST //#pragma ghs section bss=".bss.IPDUM_RAM_VAR_CLEARED_BOOLEAN"
#elif defined (IPDUM_STOP_SEC_VAR_CLEARED_BOOLEAN)
  #undef       IPDUM_STOP_SEC_VAR_CLEARED_BOOLEAN
  // TEST //#pragma ghs section
#elif defined (IPDUM_START_SEC_VAR_CLEARED_8)
  #undef       IPDUM_START_SEC_VAR_CLEARED_8
  // TEST //#pragma ghs section bss=".bss.IPDUM_RAM_VAR_CLEARED_8"
#elif defined (IPDUM_STOP_SEC_VAR_CLEARED_8)
  #undef       IPDUM_STOP_SEC_VAR_CLEARED_8
  // TEST //#pragma ghs section
#elif defined (IPDUM_START_SEC_VAR_CLEARED_16)
  #undef       IPDUM_START_SEC_VAR_CLEARED_16
  // TEST //#pragma ghs section bss=".bss.IPDUM_RAM_VAR_CLEARED_16"
#elif defined (IPDUM_STOP_SEC_VAR_CLEARED_16)
  #undef       IPDUM_STOP_SEC_VAR_CLEARED_16
  // TEST //#pragma ghs section
#elif defined (IPDUM_START_SEC_VAR_CLEARED_32)
  #undef       IPDUM_START_SEC_VAR_CLEARED_32
  // TEST //#pragma ghs section bss=".bss.IPDUM_RAM_VAR_CLEARED_32"
#elif defined (IPDUM_STOP_SEC_VAR_CLEARED_32)
  #undef       IPDUM_STOP_SEC_VAR_CLEARED_32
  // TEST //#pragma ghs section
#elif defined (IPDUM_START_SEC_VAR_CLEARED_UNSPECIFIED)
  #undef       IPDUM_START_SEC_VAR_CLEARED_UNSPECIFIED
  // TEST //#pragma ghs section bss=".bss.IPDUM_RAM_VAR_CLEARED_UNSPECIFIED"
#elif defined (IPDUM_STOP_SEC_VAR_CLEARED_UNSPECIFIED)
  #undef       IPDUM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (IPDUM_START_SEC_VAR_INIT_BOOLEAN)
  #undef       IPDUM_START_SEC_VAR_INIT_BOOLEAN
  // TEST //#pragma ghs section data=".data.IPDUM_RAM_VAR_INIT_BOOLEAN"
#elif defined (IPDUM_STOP_SEC_VAR_INIT_BOOLEAN)
  #undef       IPDUM_STOP_SEC_VAR_INIT_BOOLEAN
  // TEST //#pragma ghs section
#elif defined (IPDUM_START_SEC_VAR_INIT_8)
  #undef       IPDUM_START_SEC_VAR_INIT_8
  // TEST //#pragma ghs section data=".data.IPDUM_RAM_VAR_INIT_8"
#elif defined (IPDUM_STOP_SEC_VAR_INIT_8)
  #undef       IPDUM_STOP_SEC_VAR_INIT_8
  // TEST //#pragma ghs section
#elif defined (IPDUM_START_SEC_VAR_INIT_16)
  #undef       IPDUM_START_SEC_VAR_INIT_16
  // TEST //#pragma ghs section data=".data.IPDUM_RAM_VAR_INIT_16"
#elif defined (IPDUM_STOP_SEC_VAR_INIT_16)
  #undef       IPDUM_STOP_SEC_VAR_INIT_16
  // TEST //#pragma ghs section
#elif defined (IPDUM_START_SEC_VAR_INIT_32)
  #undef       IPDUM_START_SEC_VAR_INIT_32
  // TEST //#pragma ghs section data=".data.IPDUM_RAM_VAR_INIT_32"
#elif defined (IPDUM_STOP_SEC_VAR_INIT_32)
  #undef       IPDUM_STOP_SEC_VAR_INIT_32
  // TEST //#pragma ghs section
#elif defined (IPDUM_START_SEC_VAR_INIT_UNSPECIFIED)
  #undef       IPDUM_START_SEC_VAR_INIT_UNSPECIFIED
  // TEST //#pragma ghs section data=".data.IPDUM_RAM_VAR_INIT_UNSPECIFIED"
#elif defined (IPDUM_STOP_SEC_VAR_INIT_UNSPECIFIED)
  #undef       IPDUM_STOP_SEC_VAR_INIT_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (IPDUM_START_SEC_CONST_BOOLEAN)
  #undef       IPDUM_START_SEC_CONST_BOOLEAN
  // TEST //#pragma ghs section rodata=".rodata.IPDUM_ROM_CONST_BOOLEAN"
#elif defined (IPDUM_STOP_SEC_CONST_BOOLEAN)
  #undef       IPDUM_STOP_SEC_CONST_BOOLEAN
  // TEST //#pragma ghs section
#elif defined (IPDUM_START_SEC_CONST_8)
  #undef       IPDUM_START_SEC_CONST_8
  // TEST //#pragma ghs section rodata=".rodata.IPDUM_ROM_CONST_8"
#elif defined (IPDUM_STOP_SEC_CONST_8)
  #undef       IPDUM_STOP_SEC_CONST_8
  // TEST //#pragma ghs section
#elif defined (IPDUM_START_SEC_CONST_16)
  #undef       IPDUM_START_SEC_CONST_16
  // TEST //#pragma ghs section rodata=".rodata.IPDUM_ROM_CONST_16"
#elif defined (IPDUM_STOP_SEC_CONST_16)
  #undef       IPDUM_STOP_SEC_CONST_16
  // TEST //#pragma ghs section
#elif defined (IPDUM_START_SEC_CONST_UNSPECIFIED)
  #undef       IPDUM_START_SEC_CONST_UNSPECIFIED
  // TEST //#pragma ghs section rodata=".rodata.IPDUM_ROM_CONST_UNSPECIFIED"
#elif defined (IPDUM_STOP_SEC_CONST_UNSPECIFIED)
  #undef       IPDUM_STOP_SEC_CONST_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (IPDUM_START_SEC_CODE)
  #undef       IPDUM_START_SEC_CODE
  // TEST //#pragma ghs section text=".text.IPDUM_CODE"
  // TEST //#pragma ghs section rodata=".rodata.IPDUM_ROM_CONST_UNSPECIFIED"
  // TEST //#pragma ghs section bss=".bss.IPDUM_RAM_VAR_CLEARED_UNSPECIFIED"
  // TEST //#pragma ghs section data=".data.IPDUM_RAM_VAR_INIT_UNSPECIFIED"
#elif defined (IPDUM_STOP_SEC_CODE)
  #undef       IPDUM_STOP_SEC_CODE
  // TEST //#pragma ghs section
/* -------------------------------------------------------------------------- */
/*                  CanSM                                                     */
/* -------------------------------------------------------------------------- */
#elif defined (CANSM_START_SEC_CODE)
  #undef       CANSM_START_SEC_CODE
  // TEST //#pragma ghs section text=".text.CANSM_CODE"
  // TEST //#pragma ghs section rodata=".rodata.CANSM_ROM_CONST_UNSPECIFIED"
  // TEST //#pragma ghs section bss=".bss.CANSM_RAM_VAR_CLEARED_UNSPECIFIED"
  // TEST //#pragma ghs section data=".data.CANSM_RAM_VAR_INIT_UNSPECIFIED"
#elif defined (CANSM_STOP_SEC_CODE)
  #undef       CANSM_STOP_SEC_CODE
  // TEST //#pragma ghs section
#elif defined (CANSM_START_SEC_CONST_UNSPECIFIED)
  #undef       CANSM_START_SEC_CONST_UNSPECIFIED
  // TEST //#pragma ghs section rodata=".rodata.CANSM_ROM_CONST_UNSPECIFIED"
#elif defined (CANSM_STOP_SEC_CONST_UNSPECIFIED)
  #undef       CANSM_STOP_SEC_CONST_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (CANSM_START_SEC_CONST_8)
  #undef       CANSM_START_SEC_CONST_8
  // TEST //#pragma ghs section rodata=".rodata.CANSM_ROM_CONST_8"
#elif defined (CANSM_STOP_SEC_CONST_8)
  #undef       CANSM_STOP_SEC_CONST_8
  // TEST //#pragma ghs section
#elif defined (CANSM_START_SEC_CONST_16)
  #undef       CANSM_START_SEC_CONST_16
  // TEST //#pragma ghs section rodata=".rodata.CANSM_ROM_CONST_16"
#elif defined (CANSM_STOP_SEC_CONST_16)
  #undef       CANSM_STOP_SEC_CONST_16
  // TEST //#pragma ghs section
/* Data Configuration Section for Module*/
#elif defined (CANSM_START_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED)
  #undef       CANSM_START_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
  // TEST //#pragma ghs section rodata=".rodata.CANSM_ROM_CONFIG_UNSPECIFIED"
#elif defined (CANSM_STOP_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED)
  #undef       CANSM_STOP_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (CANSM_START_SEC_CONFIG_DATA_PREBUILD_BOOLEAN)
  #undef       CANSM_START_SEC_CONFIG_DATA_PREBUILD_BOOLEAN
  // TEST //#pragma ghs section rodata=".rodata.CANSM_ROM_CONFIG_CONST_BOOLEAN"
#elif defined (CANSM_STOP_SEC_CONFIG_DATA_PREBUILD_BOOLEAN)
  #undef       CANSM_STOP_SEC_CONFIG_DATA_PREBUILD_BOOLEAN
  // TEST //#pragma ghs section
#elif defined (CANSM_START_SEC_CONFIG_DATA_PREBUILD_8)
  #undef       CANSM_START_SEC_CONFIG_DATA_PREBUILD_8
  // TEST //#pragma ghs section rodata=".rodata.CANSM_ROM_CONFIG_CONST_8"
#elif defined (CANSM_STOP_SEC_CONFIG_DATA_PREBUILD_8)
  #undef       CANSM_STOP_SEC_CONFIG_DATA_PREBUILD_8
  // TEST //#pragma ghs section
#elif defined (CANSM_START_SEC_CONFIG_DATA_PREBUILD_16)
  #undef       CANSM_START_SEC_CONFIG_DATA_PREBUILD_16
  // TEST //#pragma ghs section rodata=".rodata.CANSM_ROM_CONFIG_CONST_16"
#elif defined (CANSM_STOP_SEC_CONFIG_DATA_PREBUILD_16)
  #undef       CANSM_STOP_SEC_CONFIG_DATA_PREBUILD_16
  // TEST //#pragma ghs section
#elif defined (CANSM_START_SEC_CONFIG_DATA_PREBUILD_32)
  #undef       CANSM_START_SEC_CONFIG_DATA_PREBUILD_32
  // TEST //#pragma ghs section rodata=".rodata.CANSM_ROM_CONFIG_CONST_32"
#elif defined (CANSM_STOP_SEC_CONFIG_DATA_PREBUILD_32)
  #undef       CANSM_STOP_SEC_CONFIG_DATA_PREBUILD_32
  // TEST //#pragma ghs section
#elif defined (CANSM_START_SEC_CONFIG_DATA_PREBUILD_PTR)
  #undef       CANSM_START_SEC_CONFIG_DATA_PREBUILD_PTR
  // TEST //#pragma ghs section rodata=".rodata.CANSM_ROM_CONFIG_CONST_PTR"
#elif defined (CANSM_STOP_SEC_CONFIG_DATA_PREBUILD_PTR)
  #undef       CANSM_STOP_SEC_CONFIG_DATA_PREBUILD_PTR
  // TEST //#pragma ghs section
#elif defined (CANSM_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED)
  #undef       CANSM_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
  // TEST //#pragma ghs section rodata=".rodata.CANSM_ROM_CONFIG_UNSPECIFIED"
#elif defined (CANSM_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED)
  #undef       CANSM_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (CANSM_START_SEC_CONFIG_DATA_POSTBUILD_BOOLEAN)
  #undef       CANSM_START_SEC_CONFIG_DATA_POSTBUILD_BOOLEAN
  // TEST //#pragma ghs section rodata=".rodata.CANSM_ROM_CONFIG_CONST_BOOLEAN"
#elif defined (CANSM_STOP_SEC_CONFIG_DATA_POSTBUILD_BOOLEAN)
  #undef       CANSM_STOP_SEC_CONFIG_DATA_POSTBUILD_BOOLEAN
  // TEST //#pragma ghs section
#elif defined (CANSM_START_SEC_CONFIG_DATA_POSTBUILD_8)
  #undef       CANSM_START_SEC_CONFIG_DATA_POSTBUILD_8
  // TEST //#pragma ghs section rodata=".rodata.CANSM_ROM_CONFIG_CONST_8"
#elif defined (CANSM_STOP_SEC_CONFIG_DATA_POSTBUILD_8)
  #undef       CANSM_STOP_SEC_CONFIG_DATA_POSTBUILD_8
  // TEST //#pragma ghs section
#elif defined (CANSM_START_SEC_CONFIG_DATA_POSTBUILD_16)
  #undef       CANSM_START_SEC_CONFIG_DATA_POSTBUILD_16
  // TEST //#pragma ghs section rodata=".rodata.CANSM_ROM_CONFIG_CONST_16"
#elif defined (CANSM_STOP_SEC_CONFIG_DATA_POSTBUILD_16)
  #undef       CANSM_STOP_SEC_CONFIG_DATA_POSTBUILD_16
  // TEST //#pragma ghs section
#elif defined (CANSM_START_SEC_CONFIG_DATA_POSTBUILD_32)
  #undef       CANSM_START_SEC_CONFIG_DATA_POSTBUILD_32
  // TEST //#pragma ghs section rodata=".rodata.CANSM_ROM_CONFIG_CONST_32"
#elif defined (CANSM_STOP_SEC_CONFIG_DATA_POSTBUILD_32)
  #undef       CANSM_STOP_SEC_CONFIG_DATA_POSTBUILD_32
  // TEST //#pragma ghs section
#elif defined (CANSM_START_SEC_CONFIG_DATA_POSTBUILD_PTR)
  #undef       CANSM_START_SEC_CONFIG_DATA_POSTBUILD_PTR
  // TEST //#pragma ghs section rodata=".rodata.CANSM_ROM_CONFIG_CONST_PTR"
#elif defined (CANSM_STOP_SEC_CONFIG_DATA_POSTBUILD_PTR)
  #undef       CANSM_STOP_SEC_CONFIG_DATA_POSTBUILD_PTR
  // TEST //#pragma ghs section
/* End Configuration Section for Module*/
#elif defined (CANSM_START_SEC_VAR_CLEARED_BOOLEAN)
  #undef       CANSM_START_SEC_VAR_CLEARED_BOOLEAN
  // TEST //#pragma ghs section bss=".bss.CANSM_RAM_VAR_CLEARED_BOOLEAN"
#elif defined (CANSM_STOP_SEC_VAR_CLEARED_BOOLEAN)
  #undef       CANSM_STOP_SEC_VAR_CLEARED_BOOLEAN
  // TEST //#pragma ghs section
#elif defined (CANSM_START_SEC_VAR_CLEARED_UNSPECIFIED)
  #undef       CANSM_START_SEC_VAR_CLEARED_UNSPECIFIED
  // TEST //#pragma ghs section bss=".bss.CANSM_RAM_VAR_CLEARED_UNSPECIFIED"
#elif defined (CANSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED)
  #undef       CANSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (CANSM_START_SEC_VAR_CLEARED_16)
  #undef       CANSM_START_SEC_VAR_CLEARED_16
  // TEST //#pragma ghs section bss=".bss.CANSM_RAM_VAR_CLEARED_16"
#elif defined (CANSM_STOP_SEC_VAR_CLEARED_16)
  #undef       CANSM_STOP_SEC_VAR_CLEARED_16
  // TEST //#pragma ghs section
#elif defined (CANSM_START_SEC_VAR_CLEARED_8)
  #undef       CANSM_START_SEC_VAR_CLEARED_8
  // TEST //#pragma ghs section bss=".bss.CANSM_RAM_VAR_CLEARED_8"
#elif defined (CANSM_STOP_SEC_VAR_CLEARED_8)
  #undef       CANSM_STOP_SEC_VAR_CLEARED_8
  // TEST //#pragma ghs section
#elif defined (CANSM_START_SEC_VAR_INIT_BOOLEAN)
  #undef       CANSM_START_SEC_VAR_INIT_BOOLEAN
  // TEST //#pragma ghs section data=".data.CANSM_RAM_VAR_INIT_BOOLEAN"
#elif defined (CANSM_STOP_SEC_VAR_INIT_BOOLEAN)
  #undef       CANSM_STOP_SEC_VAR_INIT_BOOLEAN
  // TEST //#pragma ghs section
#elif defined (CANSM_START_SEC_VAR_INIT_8)
  #undef       CANSM_START_SEC_VAR_INIT_8
  // TEST //#pragma ghs section data=".data.CANSM_RAM_VAR_INIT_8"
#elif defined (CANSM_STOP_SEC_VAR_INIT_8)
  #undef       CANSM_STOP_SEC_VAR_INIT_8
  // TEST //#pragma ghs section
#elif defined (CANSM_START_SEC_VAR_INIT_16)
  #undef       CANSM_START_SEC_VAR_INIT_16
  // TEST //#pragma ghs section data=".data.CANSM_RAM_VAR_INIT_16"
#elif defined (CANSM_STOP_SEC_VAR_INIT_16)
  #undef       CANSM_STOP_SEC_VAR_INIT_16
  // TEST //#pragma ghs section
#elif defined (CANSM_START_SEC_VAR_INIT_UNSPECIFIED)
  #undef       CANSM_START_SEC_VAR_INIT_UNSPECIFIED
  // TEST //#pragma ghs section data=".data.CANSM_RAM_VAR_INIT_UNSPECIFIED"
#elif defined (CANSM_STOP_SEC_VAR_INIT_UNSPECIFIED)
  #undef       CANSM_STOP_SEC_VAR_INIT_UNSPECIFIED
  // TEST //#pragma ghs section
/* -------------------------------------------------------------------------- */
/*                  CanNM                                                     */
/* -------------------------------------------------------------------------- */
#elif defined (CANNM_START_SEC_VAR_CLEARED_BOOLEAN)
  #undef       CANNM_START_SEC_VAR_CLEARED_BOOLEAN
  // TEST //#pragma ghs section bss=".bss.CANNM_RAM_VAR_CLEARED_BOOLEAN"
  #pragma alignvar (1)
#elif defined (CANNM_STOP_SEC_VAR_CLEARED_BOOLEAN)
  #undef       CANNM_STOP_SEC_VAR_CLEARED_BOOLEAN
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (CANNM_START_SEC_VAR_CLEARED_8)
  #undef       CANNM_START_SEC_VAR_CLEARED_8
  // TEST //#pragma ghs section bss=".bss.CANNM_RAM_VAR_CLEARED_8"
  #pragma alignvar (1)
#elif defined (CANNM_STOP_SEC_VAR_CLEARED_8)
  #undef       CANNM_STOP_SEC_VAR_CLEARED_8
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (CANNM_START_SEC_VAR_CLEARED_16)
  #undef       CANNM_START_SEC_VAR_CLEARED_16
  // TEST //#pragma ghs section bss=".bss.CANNM_RAM_VAR_CLEARED_16"
  #pragma alignvar (1)
#elif defined (CANNM_STOP_SEC_VAR_CLEARED_16)
  #undef       CANNM_STOP_SEC_VAR_CLEARED_16
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (CANNM_START_SEC_VAR_CLEARED_32)
  #undef       CANNM_START_SEC_VAR_CLEARED_32
  // TEST //#pragma ghs section bss=".bss.CANNM_RAM_VAR_CLEARED_32"
  #pragma alignvar (1)
#elif defined (CANNM_STOP_SEC_VAR_CLEARED_32)
  #undef       CANNM_STOP_SEC_VAR_CLEARED_32
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (CANNM_START_SEC_VAR_CLEARED_UNSPECIFIED)
  #undef       CANNM_START_SEC_VAR_CLEARED_UNSPECIFIED
  // TEST //#pragma ghs section bss=".bss.CANNM_RAM_VAR_CLEARED_UNSPECIFIED"
  #pragma alignvar (1)
#elif defined (CANNM_STOP_SEC_VAR_CLEARED_UNSPECIFIED)
  #undef       CANNM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (CANNM_START_SEC_CONST_BOOLEAN)
  #undef       CANNM_START_SEC_CONST_BOOLEAN
  // TEST //#pragma ghs section rodata=".rodata.CANNM_ROM_CONST_BOOLEAN"
  #pragma alignvar (1)
#elif defined (CANNM_STOP_SEC_CONST_BOOLEAN)
  #undef       CANNM_STOP_SEC_CONST_BOOLEAN
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (CANNM_START_SEC_CONST_8)
  #undef       CANNM_START_SEC_CONST_8
  // TEST //#pragma ghs section rodata=".rodata.CANNM_ROM_CONST_8"
  #pragma alignvar (1)
#elif defined (CANNM_STOP_SEC_CONST_8)
  #undef       CANNM_STOP_SEC_CONST_8
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (CANNM_START_SEC_CONST_16)
  #undef       CANNM_START_SEC_CONST_16
  // TEST //#pragma ghs section rodata=".rodata.CANNM_ROM_CONST_16"
  #pragma alignvar (1)
#elif defined (CANNM_STOP_SEC_CONST_16)
  #undef       CANNM_STOP_SEC_CONST_16
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (CANNM_START_SEC_CONST_32)
  #undef       CANNM_START_SEC_CONST_32
  // TEST //#pragma ghs section rodata=".rodata.CANNM_ROM_CONST_32"
  #pragma alignvar (1)
#elif defined (CANNM_STOP_SEC_CONST_32)
  #undef       CANNM_STOP_SEC_CONST_32
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (CANNM_START_SEC_CONST_UNSPECIFIED)
  #undef       CANNM_START_SEC_CONST_UNSPECIFIED
  // TEST //#pragma ghs section rodata=".rodata.CANNM_ROM_CONST_UNSPECIFIED"
  #pragma alignvar (1)
#elif defined (CANNM_STOP_SEC_CONST_UNSPECIFIED)
  #undef       CANNM_STOP_SEC_CONST_UNSPECIFIED
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (CANNM_START_SEC_VAR_NO_INIT_BOOLEAN)
  #undef       CANNM_START_SEC_VAR_NO_INIT_BOOLEAN
  // TEST //#pragma ghs section bss=".bss.CANNM_RAM_VAR_NO_INIT_BOOLEAN"
  #pragma alignvar (1)
#elif defined (CANNM_STOP_SEC_VAR_NO_INIT_BOOLEAN)
  #undef       CANNM_STOP_SEC_VAR_NO_INIT_BOOLEAN
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (CANNM_START_SEC_VAR_NO_INIT_8)
  #undef       CANNM_START_SEC_VAR_NO_INIT_8
  // TEST //#pragma ghs section bss=".bss.CANNM_RAM_VAR_NO_INIT_8"
  #pragma alignvar (1)
#elif defined (CANNM_STOP_SEC_VAR_NO_INIT_8)
  #undef       CANNM_STOP_SEC_VAR_NO_INIT_8
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (CANNM_START_SEC_VAR_NO_INIT_16)
  #undef       CANNM_START_SEC_VAR_NO_INIT_16
  // TEST //#pragma ghs section bss=".bss.CANNM_RAM_VAR_NO_INIT_16"
  #pragma alignvar (1)
#elif defined (CANNM_STOP_SEC_VAR_NO_INIT_16)
  #undef       CANNM_STOP_SEC_VAR_NO_INIT_16
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (CANNM_START_SEC_VAR_NO_INIT_32)
  #undef       CANNM_START_SEC_VAR_NO_INIT_32
  // TEST //#pragma ghs section bss=".bss.CANNM_RAM_VAR_NO_INIT_32"
  #pragma alignvar (1)
#elif defined (CANNM_STOP_SEC_VAR_NO_INIT_32)
  #undef       CANNM_STOP_SEC_VAR_NO_INIT_32
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (CANNM_START_SEC_VAR_NO_INIT_UNSPECIFIED)
  #undef       CANNM_START_SEC_VAR_NO_INIT_UNSPECIFIED
  // TEST //#pragma ghs section bss=".bss.CANNM_RAM_VAR_NO_INIT_UNSPECIFIED"
  #pragma alignvar (1)
#elif defined (CANNM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED)
  #undef       CANNM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (CANNM_START_SEC_VAR_INIT_BOOLEAN)
  #undef       CANNM_START_SEC_VAR_INIT_BOOLEAN
  // TEST //#pragma ghs section data=".data.CANNM_RAM_VAR_INIT_BOOLEAN"
  #pragma alignvar (1)
#elif defined (CANNM_STOP_SEC_VAR_INIT_BOOLEAN)
  #undef       CANNM_STOP_SEC_VAR_INIT_BOOLEAN
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (CANNM_START_SEC_VAR_INIT_8)
  #undef       CANNM_START_SEC_VAR_INIT_8
  // TEST //#pragma ghs section data=".data.CANNM_RAM_VAR_INIT_8"
  #pragma alignvar (1)
#elif defined (CANNM_STOP_SEC_VAR_INIT_8)
  #undef       CANNM_STOP_SEC_VAR_INIT_8
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (CANNM_START_SEC_VAR_INIT_16)
  #undef       CANNM_START_SEC_VAR_INIT_16
  // TEST //#pragma ghs section data=".data.CANNM_RAM_VAR_INIT_16"
  #pragma alignvar (1)
#elif defined (CANNM_STOP_SEC_VAR_INIT_16)
  #undef       CANNM_STOP_SEC_VAR_INIT_16
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (CANNM_START_SEC_VAR_INIT_32)
  #undef       CANNM_START_SEC_VAR_INIT_32
  // TEST //#pragma ghs section data=".data.CANNM_RAM_VAR_INIT_32"
  #pragma alignvar (1)
#elif defined (CANNM_STOP_SEC_VAR_INIT_32)
  #undef       CANNM_STOP_SEC_VAR_INIT_32
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (CANNM_START_SEC_VAR_INIT_UNSPECIFIED)
  #undef       CANNM_START_SEC_VAR_INIT_UNSPECIFIED
  // TEST //#pragma ghs section data=".data.CANNM_RAM_VAR_INIT_UNSPECIFIED"
  #pragma alignvar (1)
#elif defined (CANNM_STOP_SEC_VAR_INIT_UNSPECIFIED)
  #undef       CANNM_STOP_SEC_VAR_INIT_UNSPECIFIED
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (CANNM_START_SEC_CONFIG_CONST_POSTBUILD_UNSPECIFIED)
  #undef       CANNM_START_SEC_CONFIG_CONST_POSTBUILD_UNSPECIFIED
  // TEST //#pragma ghs section rodata=".rodata.CANNM_ROM_CONST_CONFIG_POSTBUILD_UNSPECIFIED"
  #pragma alignvar (1)
#elif defined (CANNM_STOP_SEC_CONFIG_CONST_POSTBUILD_UNSPECIFIED)
  #undef       CANNM_STOP_SEC_CONFIG_CONST_POSTBUILD_UNSPECIFIED
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (CANNM_START_SEC_CONFIG_CONST_POSTBUILD_8)
  #undef       CANNM_START_SEC_CONFIG_CONST_POSTBUILD_8
  // TEST //#pragma ghs section rodata=".rodata.CANNM_ROM_CONST_CONFIG_POSTBUILD_8"
  #pragma alignvar (1)
#elif defined (CANNM_STOP_SEC_CONFIG_CONST_POSTBUILD_8)
  #undef       CANNM_STOP_SEC_CONFIG_CONST_POSTBUILD_8
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (CANNM_START_SEC_VAR_NO_INIT_POSTBUILD_32)
  #undef       CANNM_START_SEC_VAR_NO_INIT_POSTBUILD_32
  // TEST //#pragma ghs section bss=".bss.CANNM_RAM_VAR_NO_INIT_POSTBUILD_32"
  #pragma alignvar (1)
#elif defined (CANNM_STOP_SEC_VAR_NO_INIT_POSTBUILD_32)
  #undef       CANNM_STOP_SEC_VAR_NO_INIT_POSTBUILD_32
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (CANNM_START_SEC_CODE)
  #undef       CANNM_START_SEC_CODE
  // TEST //#pragma ghs section text=".text.CANNM_CODE"
  // TEST //#pragma ghs section rodata=".rodata.CANNM_ROM_CONST_UNSPECIFIED"
  // TEST //#pragma ghs section bss=".bss.CANNM_RAM_VAR_CLEARED_UNSPECIFIED"
  // TEST //#pragma ghs section data=".data.CANNM_RAM_VAR_INIT_UNSPECIFIED"
#elif defined (CANNM_STOP_SEC_CODE)
  #undef       CANNM_STOP_SEC_CODE
  // TEST //#pragma ghs section
/* -------------------------------------------------------------------------- */
/*                  CanCM                                                     */
/* -------------------------------------------------------------------------- */
#elif defined (CANCM_START_SEC_CONST_8)
  #undef      CANCM_START_SEC_CONST_8
  // TEST //#pragma ghs section rodata=".rodata.CANCM_ROM_CONST_8"
#elif defined (CANCM_STOP_SEC_CONST_8)
  #undef      CANCM_STOP_SEC_CONST_8
  // TEST //#pragma ghs section
#elif defined (CANCM_START_SEC_CONST_BOOLEAN)
  #undef      CANCM_START_SEC_CONST_BOOLEAN
  // TEST //#pragma ghs section rodata=".rodata.CANCM_ROM_CONST_BOOLEAN"
#elif defined (CANCM_STOP_SEC_CONST_BOOLEAN)
  #undef      CANCM_STOP_SEC_CONST_BOOLEAN
  // TEST //#pragma ghs section
#elif defined (CANCM_START_SEC_CONST_UNSPECIFIED)
  #undef      CANCM_START_SEC_CONST_UNSPECIFIED
  // TEST //#pragma ghs section rodata=".rodata.CANCM_ROM_CONST_UNSPECIFIED"
#elif defined (CANCM_STOP_SEC_CONST_UNSPECIFIED)
  #undef      CANCM_STOP_SEC_CONST_UNSPECIFIED
  // TEST //#pragma ghs section
/* Data Configuration Section for Module*/
#elif defined (CANCM_START_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED)
  #undef       CANCM_START_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
  // TEST //#pragma ghs section rodata=".rodata.CANCM_ROM_CONFIG_UNSPECIFIED"
#elif defined (CANCM_STOP_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED)
  #undef       CANCM_STOP_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (CANCM_START_SEC_CONFIG_DATA_PREBUILD_BOOLEAN)
  #undef       CANCM_START_SEC_CONFIG_DATA_PREBUILD_BOOLEAN
  // TEST //#pragma ghs section rodata=".rodata.CANCM_ROM_CONFIG_CONST_BOOLEAN"
#elif defined (CANCM_STOP_SEC_CONFIG_DATA_PREBUILD_BOOLEAN)
  #undef       CANCM_STOP_SEC_CONFIG_DATA_PREBUILD_BOOLEAN
  // TEST //#pragma ghs section
#elif defined (CANCM_START_SEC_CONFIG_DATA_PREBUILD_8)
  #undef       CANCM_START_SEC_CONFIG_DATA_PREBUILD_8
  // TEST //#pragma ghs section rodata=".rodata.CANCM_ROM_CONFIG_CONST_8"
#elif defined (CANCM_STOP_SEC_CONFIG_DATA_PREBUILD_8)
  #undef       CANCM_STOP_SEC_CONFIG_DATA_PREBUILD_8
  // TEST //#pragma ghs section
#elif defined (CANCM_START_SEC_CONFIG_DATA_PREBUILD_16)
  #undef       CANCM_START_SEC_CONFIG_DATA_PREBUILD_16
  // TEST //#pragma ghs section rodata=".rodata.CANCM_ROM_CONFIG_CONST_16"
#elif defined (CANCM_STOP_SEC_CONFIG_DATA_PREBUILD_16)
  #undef       CANCM_STOP_SEC_CONFIG_DATA_PREBUILD_16
  // TEST //#pragma ghs section
#elif defined (CANCM_START_SEC_CONFIG_DATA_PREBUILD_32)
  #undef       CANCM_START_SEC_CONFIG_DATA_PREBUILD_32
  // TEST //#pragma ghs section rodata=".rodata.CANCM_ROM_CONFIG_CONST_32"
#elif defined (CANCM_STOP_SEC_CONFIG_DATA_PREBUILD_32)
  #undef       CANCM_STOP_SEC_CONFIG_DATA_PREBUILD_32
  // TEST //#pragma ghs section
#elif defined (CANCM_START_SEC_CONFIG_DATA_PREBUILD_PTR)
  #undef       CANCM_START_SEC_CONFIG_DATA_PREBUILD_PTR
  // TEST //#pragma ghs section rodata=".rodata.CANCM_ROM_CONFIG_CONST_PTR"
#elif defined (CANCM_STOP_SEC_CONFIG_DATA_PREBUILD_PTR)
  #undef       CANCM_STOP_SEC_CONFIG_DATA_PREBUILD_PTR
  // TEST //#pragma ghs section
#elif defined (CANCM_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED)
  #undef       CANCM_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
  // TEST //#pragma ghs section rodata=".rodata.CANCM_ROM_CONFIG_UNSPECIFIED"
#elif defined (CANCM_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED)
  #undef       CANCM_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (CANCM_START_SEC_CONFIG_DATA_POSTBUILD_BOOLEAN)
  #undef       CANCM_START_SEC_CONFIG_DATA_POSTBUILD_BOOLEAN
  // TEST //#pragma ghs section rodata=".rodata.CANCM_ROM_CONFIG_CONST_BOOLEAN"
#elif defined (CANCM_STOP_SEC_CONFIG_DATA_POSTBUILD_BOOLEAN)
  #undef       CANCM_STOP_SEC_CONFIG_DATA_POSTBUILD_BOOLEAN
  // TEST //#pragma ghs section
#elif defined (CANCM_START_SEC_CONFIG_DATA_POSTBUILD_8)
  #undef       CANCM_START_SEC_CONFIG_DATA_POSTBUILD_8
  // TEST //#pragma ghs section rodata=".rodata.CANCM_ROM_CONFIG_CONST_8"
#elif defined (CANCM_STOP_SEC_CONFIG_DATA_POSTBUILD_8)
  #undef       CANCM_STOP_SEC_CONFIG_DATA_POSTBUILD_8
  // TEST //#pragma ghs section
#elif defined (CANCM_START_SEC_CONFIG_DATA_POSTBUILD_16)
  #undef       CANCM_START_SEC_CONFIG_DATA_POSTBUILD_16
  // TEST //#pragma ghs section rodata=".rodata.CANCM_ROM_CONFIG_CONST_16"
#elif defined (CANCM_STOP_SEC_CONFIG_DATA_POSTBUILD_16)
  #undef       CANCM_STOP_SEC_CONFIG_DATA_POSTBUILD_16
  // TEST //#pragma ghs section
#elif defined (CANCM_START_SEC_CONFIG_DATA_POSTBUILD_32)
  #undef       CANCM_START_SEC_CONFIG_DATA_POSTBUILD_32
  // TEST //#pragma ghs section rodata=".rodata.CANCM_ROM_CONFIG_CONST_32"
#elif defined (CANCM_STOP_SEC_CONFIG_DATA_POSTBUILD_32)
  #undef       CANCM_STOP_SEC_CONFIG_DATA_POSTBUILD_32
  // TEST //#pragma ghs section
#elif defined (CANCM_START_SEC_CONFIG_DATA_POSTBUILD_PTR)
  #undef       CANCM_START_SEC_CONFIG_DATA_POSTBUILD_PTR
  // TEST //#pragma ghs section rodata=".rodata.CANCM_ROM_CONFIG_CONST_PTR"
#elif defined (CANCM_STOP_SEC_CONFIG_DATA_POSTBUILD_PTR)
  #undef       CANCM_STOP_SEC_CONFIG_DATA_POSTBUILD_PTR
  // TEST //#pragma ghs section
/* End Configuration Section for Module*/
#elif defined (CANCM_START_SEC_VAR_CLEARED_UNSPECIFIED)
  #undef      CANCM_START_SEC_VAR_CLEARED_UNSPECIFIED
  // TEST //#pragma ghs section bss=".bss.CANCM_RAM_VAR_CLEARED_UNSPECIFIED"
#elif defined (CANCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED)
  #undef      CANCM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (CANCM_START_SEC_VAR_NO_INIT_UNSPECIFIED)
  #undef      CANCM_START_SEC_VAR_NO_INIT_UNSPECIFIED
  // TEST //#pragma ghs section bss=".bss.CANCM_RAM_VAR_NO_INIT_UNSPECIFIED"
#elif defined (CANCM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED)
  #undef      CANCM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (CANCM_START_SEC_VAR_CLEARED_16)
  #undef      CANCM_START_SEC_VAR_CLEARED_16
  // TEST //#pragma ghs section bss=".bss.CANCM_RAM_VAR_CLEARED_16"
#elif defined (CANCM_STOP_SEC_VAR_CLEARED_16)
  #undef      CANCM_STOP_SEC_VAR_CLEARED_16
  // TEST //#pragma ghs section
#elif defined (CANCM_START_SEC_VAR_CLEARED_BOOLEAN)
  #undef      CANCM_START_SEC_VAR_CLEARED_BOOLEAN
  // TEST //#pragma ghs section bss=".bss.CANCM_RAM_VAR_CLEARED_BOOLEAN"
#elif defined (CANCM_STOP_SEC_VAR_CLEARED_BOOLEAN)
  #undef      CANCM_STOP_SEC_VAR_CLEARED_BOOLEAN
  // TEST //#pragma ghs section
#elif defined (CANCM_START_SEC_CODE)
  #undef      CANCM_START_SEC_CODE
  // TEST //#pragma ghs section text=".text.CANCM_CODE"
  // TEST //#pragma ghs section rodata=".rodata.CANCM_ROM_CONST_UNSPECIFIED"
  // TEST //#pragma ghs section bss=".bss.CANCM_RAM_VAR_CLEARED_UNSPECIFIED"
  // TEST //#pragma ghs section data=".data.CANCM_RAM_VAR_INIT_UNSPECIFIED"
#elif defined (CANCM_STOP_SEC_CODE)
  #undef      CANCM_STOP_SEC_CODE
  // TEST //#pragma ghs section
/* -------------------------------------------------------------------------- */
/*                  OSEKNm                                                    */
/* -------------------------------------------------------------------------- */
#elif defined (OSEKNM_START_SEC_VAR_CLEARED_BOOLEAN)
  #undef       OSEKNM_START_SEC_VAR_CLEARED_BOOLEAN
  // TEST //#pragma ghs section bss=".bss.OSEKNM_RAM_VAR_CLEARED_BOOLEAN"
  #pragma alignvar (1)
#elif defined (OSEKNM_STOP_SEC_VAR_CLEARED_BOOLEAN)
  #undef       OSEKNM_STOP_SEC_VAR_CLEARED_BOOLEAN
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (OSEKNM_START_SEC_VAR_POWER_ON_INIT_BOOLEAN)
  #undef       OSEKNM_START_SEC_VAR_POWER_ON_INIT_BOOLEAN
  // TEST //#pragma ghs section bss=".bss.OSEKNM_RAM_VAR_CLEARED_BOOLEAN"
  #pragma alignvar (1)
#elif defined (OSEKNM_STOP_SEC_VAR_POWER_ON_INIT_BOOLEAN)
  #undef       OSEKNM_STOP_SEC_VAR_POWER_ON_INIT_BOOLEAN
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (OSEKNM_START_SEC_VAR_CLEARED_8)
  #undef       OSEKNM_START_SEC_VAR_CLEARED_8
  // TEST //#pragma ghs section bss=".bss.OSEKNM_RAM_VAR_CLEARED_8"
  #pragma alignvar (1)
#elif defined (OSEKNM_STOP_SEC_VAR_CLEARED_8)
  #undef       OSEKNM_STOP_SEC_VAR_CLEARED_8
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (OSEKNM_START_SEC_VAR_CLEARED_16)
  #undef       OSEKNM_START_SEC_VAR_CLEARED_16
  // TEST //#pragma ghs section bss=".bss.OSEKNM_RAM_VAR_CLEARED_16"
  #pragma alignvar (1)
#elif defined (OSEKNM_STOP_SEC_VAR_CLEARED_16)
  #undef       OSEKNM_STOP_SEC_VAR_CLEARED_16
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (OSEKNM_START_SEC_VAR_CLEARED_32)
  #undef       OSEKNM_START_SEC_VAR_CLEARED_32
  // TEST //#pragma ghs section bss=".bss.OSEKNM_RAM_VAR_CLEARED_32"
  #pragma alignvar (4)
#elif defined (OSEKNM_STOP_SEC_VAR_CLEARED_32)
  #undef       OSEKNM_STOP_SEC_VAR_CLEARED_32
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (OSEKNM_START_SEC_VAR_CLEARED_UNSPECIFIED)
  #undef       OSEKNM_START_SEC_VAR_CLEARED_UNSPECIFIED
  // TEST //#pragma ghs section bss=".bss.OSEKNM_RAM_VAR_CLEARED_UNSPECIFIED"
  #pragma alignvar (4)
#elif defined (OSEKNM_STOP_SEC_VAR_CLEARED_UNSPECIFIED)
  #undef       OSEKNM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (OSEKNM_START_SEC_CONST_BOOLEAN)
  #undef       OSEKNM_START_SEC_CONST_BOOLEAN
  // TEST //#pragma ghs section rodata=".rodata.OSEKNM_ROM_CONST_BOOLEAN"
  #pragma alignvar (1)
#elif defined (OSEKNM_STOP_SEC_CONST_BOOLEAN)
  #undef       OSEKNM_STOP_SEC_CONST_BOOLEAN
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (OSEKNM_START_SEC_CONST_8)
  #undef       OSEKNM_START_SEC_CONST_8
  // TEST //#pragma ghs section rodata=".rodata.OSEKNM_ROM_CONST_8"
  #pragma alignvar (1)
#elif defined (OSEKNM_STOP_SEC_CONST_8)
  #undef       OSEKNM_STOP_SEC_CONST_8
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (OSEKNM_START_SEC_CONST_16)
  #undef       OSEKNM_START_SEC_CONST_16
  // TEST //#pragma ghs section rodata=".rodata.OSEKNM_ROM_CONST_16"
  #pragma alignvar (1)
#elif defined (OSEKNM_STOP_SEC_CONST_16)
  #undef       OSEKNM_STOP_SEC_CONST_16
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (OSEKNM_START_SEC_CONST_32)
  #undef       OSEKNM_START_SEC_CONST_32
  // TEST //#pragma ghs section rodata=".rodata.OSEKNM_ROM_CONST_32"
  #pragma alignvar (4)
#elif defined (OSEKNM_STOP_SEC_CONST_32)
  #undef       OSEKNM_STOP_SEC_CONST_32
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (OSEKNM_START_SEC_CONST_UNSPECIFIED)
  #undef       OSEKNM_START_SEC_CONST_UNSPECIFIED
  // TEST //#pragma ghs section rodata=".rodata.OSEKNM_ROM_CONST_UNSPECIFIED"
  #pragma alignvar (4)
#elif defined (OSEKNM_STOP_SEC_CONST_UNSPECIFIED)
  #undef       OSEKNM_STOP_SEC_CONST_UNSPECIFIED
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (OSEKNM_START_SEC_VAR_NO_INIT_BOOLEAN)
  #undef       OSEKNM_START_SEC_VAR_NO_INIT_BOOLEAN
  // TEST //#pragma ghs section bss=".bss.OSEKNM_RAM_VAR_NO_INIT_BOOLEAN"
  #pragma alignvar (1)
#elif defined (OSEKNM_STOP_SEC_VAR_NO_INIT_BOOLEAN)
  #undef       OSEKNM_STOP_SEC_VAR_NO_INIT_BOOLEAN
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (OSEKNM_START_SEC_VAR_NO_INIT_8)
  #undef       OSEKNM_START_SEC_VAR_NO_INIT_8
  // TEST //#pragma ghs section bss=".bss.OSEKNM_RAM_VAR_NO_INIT_8"
  #pragma alignvar (1)
#elif defined (OSEKNM_STOP_SEC_VAR_NO_INIT_8)
  #undef       OSEKNM_STOP_SEC_VAR_NO_INIT_8
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (OSEKNM_START_SEC_VAR_NO_INIT_16)
  #undef       OSEKNM_START_SEC_VAR_NO_INIT_16
  // TEST //#pragma ghs section bss=".bss.OSEKNM_RAM_VAR_NO_INIT_16"
  #pragma alignvar (1)
#elif defined (OSEKNM_STOP_SEC_VAR_NO_INIT_16)
  #undef       OSEKNM_STOP_SEC_VAR_NO_INIT_16
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (OSEKNM_START_SEC_VAR_NO_INIT_32)
  #undef       OSEKNM_START_SEC_VAR_NO_INIT_32
  // TEST //#pragma ghs section bss=".bss.OSEKNM_RAM_VAR_NO_INIT_32"
  #pragma alignvar (4)
#elif defined (OSEKNM_STOP_SEC_VAR_NO_INIT_32)
  #undef       OSEKNM_STOP_SEC_VAR_NO_INIT_32
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (OSEKNM_START_SEC_VAR_NO_INIT_UNSPECIFIED)
  #undef       OSEKNM_START_SEC_VAR_NO_INIT_UNSPECIFIED
  // TEST //#pragma ghs section bss=".bss.OSEKNM_RAM_VAR_NO_INIT_UNSPECIFIED"
  #pragma alignvar (4)
#elif defined (OSEKNM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED)
  #undef       OSEKNM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (OSEKNM_START_SEC_VAR_INIT_BOOLEAN)
  #undef       OSEKNM_START_SEC_VAR_INIT_BOOLEAN
  // TEST //#pragma ghs section data=".data.OSEKNM_RAM_VAR_INIT_BOOLEAN"
  #pragma alignvar (1)
#elif defined (OSEKNM_STOP_SEC_VAR_INIT_BOOLEAN)
  #undef       OSEKNM_STOP_SEC_VAR_INIT_BOOLEAN
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (OSEKNM_START_SEC_VAR_INIT_8)
  #undef       OSEKNM_START_SEC_VAR_INIT_8
  // TEST //#pragma ghs section data=".data.OSEKNM_RAM_VAR_INIT_8"
  #pragma alignvar (1)
#elif defined (OSEKNM_STOP_SEC_VAR_INIT_8)
  #undef       OSEKNM_STOP_SEC_VAR_INIT_8
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (OSEKNM_START_SEC_VAR_INIT_16)
  #undef       OSEKNM_START_SEC_VAR_INIT_16
  // TEST //#pragma ghs section data=".data.OSEKNM_RAM_VAR_INIT_16"
  #pragma alignvar (1)
#elif defined (OSEKNM_STOP_SEC_VAR_INIT_16)
  #undef       OSEKNM_STOP_SEC_VAR_INIT_16
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (OSEKNM_START_SEC_VAR_INIT_32)
  #undef       OSEKNM_START_SEC_VAR_INIT_32
  // TEST //#pragma ghs section data=".data.OSEKNM_RAM_VAR_INIT_32"
  #pragma alignvar (4)
#elif defined (OSEKNM_STOP_SEC_VAR_INIT_32)
  #undef       OSEKNM_STOP_SEC_VAR_INIT_32
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (OSEKNM_START_SEC_VAR_INIT_UNSPECIFIED)
  #undef       OSEKNM_START_SEC_VAR_INIT_UNSPECIFIED
  // TEST //#pragma ghs section data=".data.OSEKNM_RAM_VAR_INIT_UNSPECIFIED"
  #pragma alignvar (4)
#elif defined (OSEKNM_STOP_SEC_VAR_INIT_UNSPECIFIED)
  #undef       OSEKNM_STOP_SEC_VAR_INIT_UNSPECIFIED
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (OSEKNM_START_SEC_CODE)
  #undef       OSEKNM_START_SEC_CODE
  // TEST //#pragma ghs section text=".text.OSEKNM_CODE"
  // TEST //#pragma ghs section rodata=".rodata.OSEKNM_ROM_CONST_UNSPECIFIED"
  // TEST //#pragma ghs section bss=".bss.OSEKNM_RAM_VAR_CLEARED_UNSPECIFIED"
  // TEST //#pragma ghs section data=".data.OSEKNM_RAM_VAR_INIT_UNSPECIFIED"
#elif defined (OSEKNM_STOP_SEC_CODE)
  #undef       OSEKNM_STOP_SEC_CODE
  // TEST //#pragma ghs section
/* -------------------------------------------------------------------------- */
/*                  ECUM                                                      */
/* -------------------------------------------------------------------------- */
#elif defined (ECUM_START_SEC_DBTOC_CONFIG_CONST_UNSPECIFIED)
  #undef       ECUM_START_SEC_DBTOC_CONFIG_CONST_UNSPECIFIED
  // TEST //#pragma ghs section rodata=".rodata.ECUM_ROM_CONFIG_UNSPECIFIED"
#elif defined (ECUM_STOP_SEC_DBTOC_CONFIG_CONST_UNSPECIFIED)
  #undef       ECUM_STOP_SEC_DBTOC_CONFIG_CONST_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (ECUM_START_SEC_CODE)
  #undef       ECUM_START_SEC_CODE
  // TEST //#pragma ghs section text=".text.ECUM_CODE"
  // TEST //#pragma ghs section rodata=".rodata.ECUM_ROM_CONST_UNSPECIFIED"
  // TEST //#pragma ghs section bss=".bss.ECUM_RAM_VAR_CLEARED_UNSPECIFIED"
  // TEST //#pragma ghs section data=".data.ECUM_RAM_VAR_INIT_UNSPECIFIED"
#elif defined (ECUM_STOP_SEC_CODE)
  #undef       ECUM_STOP_SEC_CODE
  // TEST //#pragma ghs section
#elif defined (ECUM_START_SEC_CONFIG_CONST_32)
  #undef       ECUM_START_SEC_CONFIG_CONST_32
  // TEST //#pragma ghs section rodata=".rodata.ECUM_ROM_CONFIG_CONST_32"
#elif defined (ECUM_STOP_SEC_CONFIG_CONST_32)
  #undef       ECUM_STOP_SEC_CONFIG_CONST_32
  // TEST //#pragma ghs section
#elif defined (ECUM_START_SEC_CONST_32)
  #undef       ECUM_START_SEC_CONST_32
  // TEST //#pragma ghs section rodata=".rodata.ECUM_ROM_CONST_32"
#elif defined (ECUM_STOP_SEC_CONST_32)
  #undef       ECUM_STOP_SEC_CONST_32
  // TEST //#pragma ghs section
#elif defined (ECUM_START_SEC_CONST_8)
  #undef       ECUM_START_SEC_CONST_8
  // TEST //#pragma ghs section rodata=".rodata.ECUM_ROM_CONST_8"
#elif defined (ECUM_STOP_SEC_CONST_8)
  #undef       ECUM_STOP_SEC_CONST_8
  // TEST //#pragma ghs section
#elif defined (ECUM_START_SEC_CONST_UNSPECIFIED)
  #undef       ECUM_START_SEC_CONST_UNSPECIFIED
  // TEST //#pragma ghs section rodata=".rodata.ECUM_ROM_CONST_UNSPECIFIED"
#elif defined (ECUM_STOP_SEC_CONST_UNSPECIFIED)
  #undef       ECUM_STOP_SEC_CONST_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (ECUM_START_SEC_CALLOUT_CODE)
  #undef       ECUM_START_SEC_CALLOUT_CODE
  // TEST //#pragma ghs section text=".text.ECUM_CALLOUT_CODE"
  // TEST //#pragma ghs section rodata=".rodata.ECUM_ROM_CONST_UNSPECIFIED"
  // TEST //#pragma ghs section bss=".bss.ECUM_RAM_VAR_CLEARED_UNSPECIFIED"
  // TEST //#pragma ghs section data=".data.ECUM_RAM_VAR_INIT_UNSPECIFIED"
#elif defined (ECUM_STOP_SEC_CALLOUT_CODE)
  #undef       ECUM_STOP_SEC_CALLOUT_CODE
  // TEST //#pragma ghs section
#elif defined (ECUM_START_SEC_VAR_CLEARED_BOOLEAN)
  #undef       ECUM_START_SEC_VAR_CLEARED_BOOLEAN
  // TEST //#pragma ghs section bss=".bss.ECUM_RAM_VAR_CLEARED_BOOLEAN"
#elif defined (ECUM_STOP_SEC_VAR_CLEARED_BOOLEAN)
  #undef       ECUM_STOP_SEC_VAR_CLEARED_BOOLEAN
  // TEST //#pragma ghs section
#elif defined (ECUM_START_SEC_VAR_POWER_ON_CLEARED_16)
  #undef       ECUM_START_SEC_VAR_POWER_ON_CLEARED_16
  // TEST //#pragma ghs section bss=".bss.ECUM_RAM_VAR_POWER_ON_CLEARED_16"
#elif defined (ECUM_STOP_SEC_VAR_POWER_ON_CLEARED_16)
  #undef       ECUM_STOP_SEC_VAR_POWER_ON_CLEARED_16
  // TEST //#pragma ghs section
#elif defined (ECUM_START_SEC_VAR_CLEARED_32)
  #undef       ECUM_START_SEC_VAR_CLEARED_32
  // TEST //#pragma ghs section bss=".bss.ECUM_RAM_VAR_CLEARED_32"
#elif defined (ECUM_STOP_SEC_VAR_CLEARED_32)
  #undef       ECUM_STOP_SEC_VAR_CLEARED_32
  // TEST //#pragma ghs section
#elif defined (ECUM_START_SEC_VAR_CLEARED_16)
  #undef       ECUM_START_SEC_VAR_CLEARED_16
  // TEST //#pragma ghs section bss=".bss.ECUM_RAM_VAR_CLEARED_16"
#elif defined (ECUM_STOP_SEC_VAR_CLEARED_16)
  #undef       ECUM_STOP_SEC_VAR_CLEARED_16
  // TEST //#pragma ghs section
#elif defined (ECUM_START_SEC_VAR_CLEARED_8)
  #undef       ECUM_START_SEC_VAR_CLEARED_8
  // TEST //#pragma ghs section bss=".bss.ECUM_RAM_VAR_CLEARED_8"
#elif defined (ECUM_STOP_SEC_VAR_CLEARED_8)
  #undef       ECUM_STOP_SEC_VAR_CLEARED_8
  // TEST //#pragma ghs section
#elif defined (ECUM_START_SEC_VAR_NO_INIT_8)
  #undef       ECUM_START_SEC_VAR_NO_INIT_8
  // TEST //#pragma ghs section bss=".bss.ECUM_RAM_VAR_NO_INIT_8"
#elif defined (ECUM_STOP_SEC_VAR_NO_INIT_8)
  #undef       ECUM_STOP_SEC_VAR_NO_INIT_8
  // TEST //#pragma ghs section
#elif defined (ECUM_START_SEC_VAR_NO_INIT_UNSPECIFIED)
  #undef       ECUM_START_SEC_VAR_NO_INIT_UNSPECIFIED
  // TEST //#pragma ghs section bss=".bss.ECUM_RAM_VAR_NO_INIT_UNSPECIFIED"
#elif defined (ECUM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED)
  #undef       ECUM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (ECUM_START_SEC_VAR_SAVED_ZONE_UNSPECIFIED)
  #undef       ECUM_START_SEC_VAR_SAVED_ZONE_UNSPECIFIED
  // TEST //#pragma ghs section bss=".bss.ECUM_RAM_VAR_SAVED_ZONE_UNSPECIFIED"
#elif defined (ECUM_STOP_SEC_VAR_SAVED_ZONE_UNSPECIFIED)
  #undef       ECUM_STOP_SEC_VAR_SAVED_ZONE_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (ECUM_START_SEC_VAR_POWER_ON_CLEARED_UNSPECIFIED)
  #undef       ECUM_START_SEC_VAR_POWER_ON_CLEARED_UNSPECIFIED
  // TEST //#pragma ghs section bss=".bss.ECUM_RAM_VAR_CLEARED_UNSPECIFIED"
#elif defined (ECUM_STOP_SEC_VAR_POWER_ON_CLEARED_UNSPECIFIED)
  #undef       ECUM_STOP_SEC_VAR_POWER_ON_CLEARED_UNSPECIFIED
  // TEST //#pragma ghs section
/* -------------------------------------------------------------------------- */
/*                 NM                                                         */
/* -------------------------------------------------------------------------- */
#elif defined (NM_START_SEC_VAR_CLEARED_BOOLEAN)
  #undef       NM_START_SEC_VAR_CLEARED_BOOLEAN
  // TEST //#pragma ghs section bss=".bss.NM_RAM_VAR_CLEARED_BOOLEAN"
  #pragma alignvar (1)
#elif defined (NM_STOP_SEC_VAR_CLEARED_BOOLEAN)
  #undef       NM_STOP_SEC_VAR_CLEARED_BOOLEAN
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (NM_START_SEC_VAR_CLEARED_8)
  #undef       NM_START_SEC_VAR_CLEARED_8
  // TEST //#pragma ghs section bss=".bss.NM_RAM_VAR_CLEARED_8"
  #pragma alignvar (1)
#elif defined (NM_STOP_SEC_VAR_CLEARED_8)
  #undef       NM_STOP_SEC_VAR_CLEARED_8
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (NM_START_SEC_VAR_CLEARED_16)
  #undef       NM_START_SEC_VAR_CLEARED_16
  // TEST //#pragma ghs section bss=".bss.NM_RAM_VAR_CLEARED_16"
  #pragma alignvar (1)
#elif defined (NM_STOP_SEC_VAR_CLEARED_16)
  #undef       NM_STOP_SEC_VAR_CLEARED_16
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (NM_START_SEC_VAR_CLEARED_32)
  #undef       NM_START_SEC_VAR_CLEARED_32
  // TEST //#pragma ghs section bss=".bss.NM_RAM_VAR_CLEARED_32"
  #pragma alignvar (4)
#elif defined (NM_STOP_SEC_VAR_CLEARED_32)
  #undef       NM_STOP_SEC_VAR_CLEARED_32
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (NM_START_SEC_VAR_CLEARED_UNSPECIFIED)
  #undef       NM_START_SEC_VAR_CLEARED_UNSPECIFIED
  // TEST //#pragma ghs section bss=".bss.NM_RAM_VAR_CLEARED_UNSPECIFIED"
  #pragma alignvar (4)
#elif defined (NM_STOP_SEC_VAR_CLEARED_UNSPECIFIED)
  #undef       NM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (NM_START_SEC_VAR_POWER_ON_INIT_BOOLEAN)
  #undef       NM_START_SEC_VAR_POWER_ON_INIT_BOOLEAN
  // TEST //#pragma ghs section data=".data.NM_RAM_VAR_INIT_BOOLEAN"
  #pragma alignvar (1)
#elif defined (NM_STOP_SEC_VAR_POWER_ON_INIT_BOOLEAN)
  #undef       NM_STOP_SEC_VAR_POWER_ON_INIT_BOOLEAN
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (NM_START_SEC_VAR_POWER_ON_INIT_8)
  #undef       NM_START_SEC_VAR_POWER_ON_INIT_8
  // TEST //#pragma ghs section data=".data.NM_RAM_VAR_INIT_8"
  #pragma alignvar (1)
#elif defined (NM_STOP_SEC_VAR_POWER_ON_INIT_8)
  #undef       NM_STOP_SEC_VAR_POWER_ON_INIT_8
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (NM_START_SEC_VAR_POWER_ON_INIT_16)
  #undef       NM_START_SEC_VAR_POWER_ON_INIT_16
  // TEST //#pragma ghs section data=".data.NM_RAM_VAR_INIT_16"
  #pragma alignvar (1)
#elif defined (NM_STOP_SEC_VAR_POWER_ON_INIT_16)
  #undef       NM_STOP_SEC_VAR_POWER_ON_INIT_16
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (NM_START_SEC_VAR_POWER_ON_INIT_32)
  #undef       NM_START_SEC_VAR_POWER_ON_INIT_32
  // TEST //#pragma ghs section data=".data.NM_RAM_VAR_INIT_32"
  #pragma alignvar (4)
#elif defined (NM_STOP_SEC_VAR_POWER_ON_INIT_32)
  #undef       NM_STOP_SEC_VAR_POWER_ON_INIT_32
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (NM_START_SEC_VAR_POWER_ON_INIT_UNSPECIFIED)
  #undef       NM_START_SEC_VAR_POWER_ON_INIT_UNSPECIFIED
  // TEST //#pragma ghs section data=".data.NM_RAM_VAR_INIT_UNSPECIFIED"
  #pragma alignvar (4)
#elif defined (NM_STOP_SEC_VAR_POWER_ON_INIT_UNSPECIFIED)
  #undef       NM_STOP_SEC_VAR_POWER_ON_INIT_UNSPECIFIED
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (NM_START_SEC_VAR_INIT_BOOLEAN)
  #undef       NM_START_SEC_VAR_INIT_BOOLEAN
  // TEST //#pragma ghs section data=".data.NM_RAM_VAR_INIT_BOOLEAN"
  #pragma alignvar (1)
#elif defined (NM_STOP_SEC_VAR_INIT_BOOLEAN)
  #undef       NM_STOP_SEC_VAR_INIT_BOOLEAN
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (NM_START_SEC_VAR_INIT_8)
  #undef       NM_START_SEC_VAR_INIT_8
  // TEST //#pragma ghs section data=".data.NM_RAM_VAR_INIT_8"
  #pragma alignvar (1)
#elif defined (NM_STOP_SEC_VAR_INIT_8)
  #undef       NM_STOP_SEC_VAR_INIT_8
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (NM_START_SEC_VAR_INIT_16)
  #undef       NM_START_SEC_VAR_INIT_16
  // TEST //#pragma ghs section data=".data.NM_RAM_VAR_INIT_16"
  #pragma alignvar (1)
#elif defined (NM_STOP_SEC_VAR_INIT_16)
  #undef       NM_STOP_SEC_VAR_INIT_16
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (NM_START_SEC_VAR_INIT_32)
  #undef       NM_START_SEC_VAR_INIT_32
  // TEST //#pragma ghs section data=".data.NM_RAM_VAR_INIT_32"
  #pragma alignvar (4)
#elif defined (NM_STOP_SEC_VAR_INIT_32)
  #undef       NM_STOP_SEC_VAR_INIT_32
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (NM_START_SEC_VAR_INIT_UNSPECIFIED)
  #undef       NM_START_SEC_VAR_INIT_UNSPECIFIED
  // TEST //#pragma ghs section data=".data.NM_RAM_VAR_INIT_UNSPECIFIED"
  #pragma alignvar (4)
#elif defined (NM_STOP_SEC_VAR_INIT_UNSPECIFIED)
  #undef       NM_STOP_SEC_VAR_INIT_UNSPECIFIED
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (NM_START_SEC_VAR_NO_INIT_BOOLEAN)
  #undef       NM_START_SEC_VAR_NO_INIT_BOOLEAN
  // TEST //#pragma ghs section bss=".bss.NM_RAM_VAR_NO_INIT_BOOLEAN"
  #pragma alignvar (1)
#elif defined (NM_STOP_SEC_VAR_NO_INIT_BOOLEAN)
  #undef       NM_STOP_SEC_VAR_NO_INIT_BOOLEAN
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (NM_START_SEC_VAR_NO_INIT_8)
  #undef       NM_START_SEC_VAR_NO_INIT_8
  // TEST //#pragma ghs section bss=".bss.NM_RAM_VAR_NO_INIT_8"
  #pragma alignvar (1)
#elif defined (NM_STOP_SEC_VAR_NO_INIT_8)
  #undef       NM_STOP_SEC_VAR_NO_INIT_8
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (NM_START_SEC_VAR_NO_INIT_16)
  #undef       NM_START_SEC_VAR_NO_INIT_16
  // TEST //#pragma ghs section bss=".bss.NM_RAM_VAR_NO_INIT_16"
  #pragma alignvar (1)
#elif defined (NM_STOP_SEC_VAR_NO_INIT_16)
  #undef       NM_STOP_SEC_VAR_NO_INIT_16
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (NM_START_SEC_VAR_NO_INIT_32)
  #undef       NM_START_SEC_VAR_NO_INIT_32
  // TEST //#pragma ghs section bss=".bss.NM_RAM_VAR_NO_INIT_32"
  #pragma alignvar (4)
#elif defined (NM_STOP_SEC_VAR_NO_INIT_32)
  #undef       NM_STOP_SEC_VAR_NO_INIT_32
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (NM_START_SEC_VAR_NO_INIT_UNSPECIFIED)
  #undef       NM_START_SEC_VAR_NO_INIT_UNSPECIFIED
  // TEST //#pragma ghs section bss=".bss.NM_RAM_VAR_NO_INIT_UNSPECIFIED"
  #pragma alignvar (4)
#elif defined (NM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED)
  #undef       NM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (NM_START_SEC_CONST_BOOLEAN)
  #undef       NM_START_SEC_CONST_BOOLEAN
  // TEST //#pragma ghs section rodata=".rodata.NM_ROM_CONST_BOOLEAN"
  #pragma alignvar (1)
#elif defined (NM_STOP_SEC_CONST_BOOLEAN)
  #undef       NM_STOP_SEC_CONST_BOOLEAN
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (NM_START_SEC_CONST_8)
  #undef       NM_START_SEC_CONST_8
  // TEST //#pragma ghs section rodata=".rodata.NM_ROM_CONST_8"
  #pragma alignvar (1)
#elif defined (NM_STOP_SEC_CONST_8)
  #undef       NM_STOP_SEC_CONST_8
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (NM_START_SEC_CONST_16)
  #undef       NM_START_SEC_CONST_16
  // TEST //#pragma ghs section rodata=".rodata.NM_ROM_CONST_16"
  #pragma alignvar (1)
#elif defined (NM_STOP_SEC_CONST_16)
  #undef       NM_STOP_SEC_CONST_16
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (NM_START_SEC_CONST_32)
  #undef       NM_START_SEC_CONST_32
  // TEST //#pragma ghs section rodata=".rodata.NM_ROM_CONST_32"
  #pragma alignvar (4)
#elif defined (NM_STOP_SEC_CONST_32)
  #undef       NM_STOP_SEC_CONST_32
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (NM_START_SEC_CONST_UNSPECIFIED)
  #undef       NM_START_SEC_CONST_UNSPECIFIED
  // TEST //#pragma ghs section rodata=".rodata.NM_ROM_CONST_UNSPECIFIED"
  #pragma alignvar (4)
#elif defined (NM_STOP_SEC_CONST_UNSPECIFIED)
  #undef       NM_STOP_SEC_CONST_UNSPECIFIED
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (NM_START_SEC_CODE)
  #undef       NM_START_SEC_CODE
  // TEST //#pragma ghs section text=".text.NM_CODE"
  // TEST //#pragma ghs section rodata=".rodata.NM_ROM_CONST_UNSPECIFIED"
  // TEST //#pragma ghs section bss=".bss.NM_RAM_VAR_CLEARED_UNSPECIFIED"
  // TEST //#pragma ghs section data=".data.NM_RAM_VAR_INIT_UNSPECIFIED"
#elif defined (NM_STOP_SEC_CODE)
  #undef       NM_STOP_SEC_CODE
  // TEST //#pragma ghs section
#elif defined (NM_START_SEC_CONFIG_DATA_PREBUILD_8)
  #undef       NM_START_SEC_CONFIG_DATA_PREBUILD_8
  // TEST //#pragma ghs section rodata=".rodata.NM_ROM_CONST_8"
  #pragma alignvar (1)
#elif defined (NM_STOP_SEC_CONFIG_DATA_PREBUILD_8)
  #undef       NM_STOP_SEC_CONFIG_DATA_PREBUILD_8
    // TEST //#pragma ghs section
#elif defined (NM_START_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED)
  #undef       NM_START_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
  // TEST //#pragma ghs section rodata=".rodata.NM_ROM_CONST_UNSPECIFIED"
  #pragma alignvar (4)
#elif defined (NM_STOP_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED)
  #undef       NM_STOP_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
    // TEST //#pragma ghs section
#elif defined (NM_START_SEC_CONFIG_DATA_PREBUILD_PTR)
  #undef       NM_START_SEC_CONFIG_DATA_PREBUILD_PTR
  // TEST //#pragma ghs section rodata=".rodata.NM_ROM_CONST_UNSPECIFIED"
  #pragma alignvar (4)
#elif defined (NM_STOP_SEC_CONFIG_DATA_PREBUILD_PTR)
  #undef       NM_STOP_SEC_CONFIG_DATA_PREBUILD_PTR
    // TEST //#pragma ghs section
#elif defined (NM_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED)
  #undef       NM_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
  // TEST //#pragma ghs section rodata=".rodata.NM_ROM_CONFIG_DATA_POSTBUILD_UNSPECIFIED"
  #pragma alignvar (4)
#elif defined (NM_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED)
  #undef       NM_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
    // TEST //#pragma ghs section
#elif defined (NM_START_SEC_CALLOUT_CODE)
  #undef       NM_START_SEC_CALLOUT_CODE
  // TEST //#pragma ghs section text=".text.NM_CALLOUT_CODE"
  // TEST //#pragma ghs section rodata=".rodata.NM_ROM_CONST_UNSPECIFIED"
  // TEST //#pragma ghs section bss=".bss.NM_RAM_VAR_CLEARED_UNSPECIFIED"
  // TEST //#pragma ghs section data=".data.NM_RAM_VAR_INIT_UNSPECIFIED"
#elif defined (NM_STOP_SEC_CALLOUT_CODE)
  #undef       NM_STOP_SEC_CALLOUT_CODE
  // TEST //#pragma ghs section
/* -------------------------------------------------------------------------- */
/*                                 MemIf                                      */
/* -------------------------------------------------------------------------- */
#elif defined (MEMIF_START_SEC_CODE)
  #undef       MEMIF_START_SEC_CODE
  // TEST //#pragma ghs section text=".text.MEMIF_CODE"
  // TEST //#pragma ghs section rodata=".rodata.MEMIF_ROM_CONST_UNSPECIFIED"
  // TEST //#pragma ghs section bss=".bss.MEMIF_RAM_VAR_CLEARED_UNSPECIFIED"
  // TEST //#pragma ghs section data=".data.MEMIF_RAM_VAR_INIT_UNSPECIFIED"
#elif defined (MEMIF_STOP_SEC_CODE)
  #undef       MEMIF_STOP_SEC_CODE
  // TEST //#pragma ghs section
/* -------------------------------------------------------------------------- */
/*                                 Crc                                        */
/* -------------------------------------------------------------------------- */
#elif defined (CRC_START_SEC_CODE_ASIL_D)
  #undef       CRC_START_SEC_CODE_ASIL_D
  // TEST //#pragma ghs section text=".text.CRC_CODE"
  // TEST //#pragma ghs section rodata=".rodata.CRC_ROM_CONST_UNSPECIFIED"
  // TEST //#pragma ghs section bss=".bss.CRC_RAM_VAR_CLEARED_UNSPECIFIED"
  // TEST //#pragma ghs section data=".data.CRC_RAM_VAR_INIT_UNSPECIFIED"
#elif defined (CRC_STOP_SEC_CODE_ASIL_D)
  #undef       CRC_STOP_SEC_CODE_ASIL_D
  // TEST //#pragma ghs section
#elif defined (CRC_START_SEC_CONST_ASIL_D_8)
  #undef       CRC_START_SEC_CONST_ASIL_D_8
  // TEST //#pragma ghs section rodata=".rodata.CRC_ROM_CONST_8"
#elif defined (CRC_STOP_SEC_CONST_ASIL_D_8)
  #undef       CRC_STOP_SEC_CONST_ASIL_D_8
  // TEST //#pragma ghs section
#elif defined (CRC_START_SEC_CONST_ASIL_D_16)
  #undef       CRC_START_SEC_CONST_ASIL_D_16
  // TEST //#pragma ghs section rodata=".rodata.CRC_ROM_CONST_16"
#elif defined (CRC_STOP_SEC_CONST_ASIL_D_16)
  #undef       CRC_STOP_SEC_CONST_ASIL_D_16
  // TEST //#pragma ghs section
#elif defined (CRC_START_SEC_CONST_ASIL_D_32)
  #undef       CRC_START_SEC_CONST_ASIL_D_32
  // TEST //#pragma ghs section rodata=".rodata.CRC_ROM_CONST_32"
#elif defined (CRC_STOP_SEC_CONST_ASIL_D_32)
  #undef       CRC_STOP_SEC_CONST_ASIL_D_32
  // TEST //#pragma ghs section
#elif defined (CRC_START_SEC_CONST_ASIL_D_64)
  #undef       CRC_START_SEC_CONST_ASIL_D_64
  // TEST //#pragma ghs section rodata=".rodata.CRC_ROM_CONST_64"
#elif defined (CRC_STOP_SEC_CONST_ASIL_D_64)
  #undef       CRC_STOP_SEC_CONST_ASIL_D_64
  // TEST //#pragma ghs section
/* -------------------------------------------------------------------------- */
/*                                 NvM                                        */
/* -------------------------------------------------------------------------- */
#elif defined (NVM_START_SEC_CODE)
  #undef       NVM_START_SEC_CODE
  // TEST //#pragma ghs section text=".text.NVM_CODE"
  // TEST //#pragma ghs section rodata=".rodata.NVM_ROM_CONST_UNSPECIFIED"
  // TEST //#pragma ghs section bss=".bss.NVM_RAM_VAR_CLEARED_UNSPECIFIED"
  // TEST //#pragma ghs section data=".data.NVM_RAM_VAR_INIT_UNSPECIFIED"
#elif defined (NVM_STOP_SEC_CODE)
  #undef       NVM_STOP_SEC_CODE
  // TEST //#pragma ghs section
#elif defined (NVM_START_SEC_VAR_CLEARED_8)
 #undef        NVM_START_SEC_VAR_CLEARED_8
 // TEST //#pragma ghs section bss=".bss.NVM_RAM_VAR_CLEARED_8"
#elif defined (NVM_STOP_SEC_VAR_CLEARED_8)
 #undef        NVM_STOP_SEC_VAR_CLEARED_8
 // TEST //#pragma ghs section
#elif defined (NVM_START_SEC_VAR_CLEARED_16)
  #undef       NVM_START_SEC_VAR_CLEARED_16
  // TEST //#pragma ghs section bss=".bss.NVM_RAM_VAR_CLEARED_16"
#elif defined (NVM_STOP_SEC_VAR_CLEARED_16)
  #undef       NVM_STOP_SEC_VAR_CLEARED_16
  // TEST //#pragma ghs section
#elif defined (NVM_START_SEC_VAR_CLEARED_32)
  #undef       NVM_START_SEC_VAR_CLEARED_32
  // TEST //#pragma ghs section bss=".bss.NVM_RAM_VAR_CLEARED_32"
#elif defined (NVM_STOP_SEC_VAR_CLEARED_32)
  #undef       NVM_STOP_SEC_VAR_CLEARED_32
  // TEST //#pragma ghs section
#elif defined (NVM_START_SEC_VAR_POWER_ON_CLEARED_16)
  #undef       NVM_START_SEC_VAR_POWER_ON_CLEARED_16
  // TEST //#pragma ghs section bss=".bss.NVM_RAM_VAR_POWER_ON_CLEARED_16"
#elif defined (NVM_STOP_SEC_VAR_POWER_ON_CLEARED_16)
  #undef       NVM_STOP_SEC_VAR_POWER_ON_CLEARED_16
  // TEST //#pragma ghs section
#elif defined (NVM_START_SEC_VAR_POWER_ON_CLEARED_8)
  #undef       NVM_START_SEC_VAR_POWER_ON_CLEARED_8
  // TEST //#pragma ghs section bss=".bss.NVM_RAM_VAR_POWER_ON_CLEARED_8"
#elif defined (NVM_STOP_SEC_VAR_POWER_ON_CLEARED_8)
  #undef       NVM_STOP_SEC_VAR_POWER_ON_CLEARED_8
  // TEST //#pragma ghs section
#elif defined (NVM_START_SEC_VAR_NO_INIT_8)
  #undef       NVM_START_SEC_VAR_NO_INIT_8
  // TEST //#pragma ghs section bss=".bss.NVM_RAM_VAR_NO_INIT_8"
#elif defined (NVM_STOP_SEC_VAR_NO_INIT_8)
  #undef       NVM_STOP_SEC_VAR_NO_INIT_8
  // TEST //#pragma ghs section
#elif defined (NVM_START_SEC_VAR_NO_INIT_UNSPECIFIED)
  #undef       NVM_START_SEC_VAR_NO_INIT_UNSPECIFIED
  // TEST //#pragma ghs section bss=".bss.NVM_RAM_VAR_NO_INIT_UNSPECIFIED"
#elif defined (NVM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED)
  #undef       NVM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (NVM_START_SEC_VAR_CLEARED_UNSPECIFIED)
  #undef       NVM_START_SEC_VAR_CLEARED_UNSPECIFIED
  // TEST //#pragma ghs section bss=".bss.NVM_RAM_VAR_CLEARED_UNSPECIFIED"
#elif defined (NVM_STOP_SEC_VAR_CLEARED_UNSPECIFIED)
  #undef       NVM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (NVM_START_SEC_VAR_POWER_ON_CLEARED_UNSPECIFIED)
  #undef       NVM_START_SEC_VAR_POWER_ON_CLEARED_UNSPECIFIED
  // TEST //#pragma ghs section bss=".bss.NVM_RAM_VAR_POWER_ON_CLEARED_UNSPECIFIED"
#elif defined (NVM_STOP_SEC_VAR_POWER_ON_CLEARED_UNSPECIFIED)
  #undef       NVM_STOP_SEC_VAR_POWER_ON_CLEARED_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (NVM_START_SEC_VAR_NO_INIT_BOOLEAN)
  #undef       NVM_START_SEC_VAR_NO_INIT_BOOLEAN
  // TEST //#pragma ghs section bss=".bss.NVM_RAM_VAR_NO_INIT_BOOLEAN"
#elif defined (NVM_STOP_SEC_VAR_NO_INIT_BOOLEAN)
  #undef       NVM_STOP_SEC_VAR_NO_INIT_BOOLEAN
  // TEST //#pragma ghs section
#elif defined (NVM_START_SEC_VAR_POWER_ON_CLEARED_BOOLEAN)
  #undef       NVM_START_SEC_VAR_POWER_ON_CLEARED_BOOLEAN
  // TEST //#pragma ghs section bss=".bss.NVM_RAM_VAR_POWER_ON_CLEARED_BOOLEAN"
#elif defined (NVM_STOP_SEC_VAR_POWER_ON_CLEARED_BOOLEAN)
  #undef       NVM_STOP_SEC_VAR_POWER_ON_CLEARED_BOOLEAN
  // TEST //#pragma ghs section
#elif defined (NVM_START_SEC_VAR_CLEARED_BOOLEAN)
  #undef       NVM_START_SEC_VAR_CLEARED_BOOLEAN
  // TEST //#pragma ghs section bss=".bss.NVM_RAM_VAR_CLEARED_BOOLEAN"
#elif defined (NVM_STOP_SEC_VAR_CLEARED_BOOLEAN)
  #undef       NVM_STOP_SEC_VAR_CLEARED_BOOLEAN
  // TEST //#pragma ghs section
#elif defined (NVM_START_SEC_CONST_8)
  #undef       NVM_START_SEC_CONST_8
  // TEST //#pragma ghs section rodata=".rodata.NVM_ROM_CONST_8"
#elif defined (NVM_STOP_SEC_CONST_8)
  #undef       NVM_STOP_SEC_CONST_8
  // TEST //#pragma ghs section
#elif defined (NVM_START_SEC_CONST_16)
  #undef       NVM_START_SEC_CONST_16
  // TEST //#pragma ghs section rodata=".rodata.NVM_ROM_CONST_16"
#elif defined (NVM_STOP_SEC_CONST_16)
  #undef       NVM_STOP_SEC_CONST_16
  // TEST //#pragma ghs section
#elif defined (NVM_START_SEC_CONST_UNSPECIFIED)
  #undef       NVM_START_SEC_CONST_UNSPECIFIED
  // TEST //#pragma ghs section rodata=".rodata.NVM_ROM_CONST_UNSPECIFIED"
#elif defined (NVM_STOP_SEC_CONST_UNSPECIFIED)
  #undef       NVM_STOP_SEC_CONST_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (NVM_START_SEC_VAR_NO_INIT_16)
  #undef       NVM_START_SEC_VAR_NO_INIT_16
  // TEST //#pragma ghs section bss=".bss.NVM_RAM_VAR_NO_INIT_16"
#elif defined (NVM_STOP_SEC_VAR_NO_INIT_16)
  #undef       NVM_STOP_SEC_VAR_NO_INIT_16
  // TEST //#pragma ghs section
#elif defined (NVM_START_SEC_VAR_NO_INIT_32)
  #undef       NVM_START_SEC_VAR_NO_INIT_32
  // TEST //#pragma ghs section bss=".bss.NVM_RAM_VAR_NO_INIT_32"
#elif defined (NVM_STOP_SEC_VAR_NO_INIT_32)
  #undef       NVM_STOP_SEC_VAR_NO_INIT_32
  // TEST //#pragma ghs section
#elif defined (NVM_START_SEC_VAR_INIT_8)
  #undef       NVM_START_SEC_VAR_INIT_8
  // TEST //#pragma ghs section data=".data.NVM_RAM_VAR_INIT_8"
#elif defined (NVM_STOP_SEC_VAR_INIT_8)
  #undef       NVM_STOP_SEC_VAR_INIT_8
  // TEST //#pragma ghs section
#elif defined (NVM_START_SEC_VAR_CLEARED_ALIGNED_ADDR_UNSPECIFIED)
  #undef       NVM_START_SEC_VAR_CLEARED_ALIGNED_ADDR_UNSPECIFIED
  // TEST //#pragma ghs section bss=".bss.NVM_RAM_VAR_CLEARED_ALIGNED_ADDR_UNSPECIFIED"
#elif defined (NVM_STOP_SEC_VAR_CLEARED_ALIGNED_ADDR_UNSPECIFIED)
  #undef       NVM_STOP_SEC_VAR_CLEARED_ALIGNED_ADDR_UNSPECIFIED
  // TEST //#pragma ghs section
/* -------------------------------------------------------------------------- */
/*                                 Eep                                        */
/* -------------------------------------------------------------------------- */
#elif defined (EEP_START_SEC_CODE)
  #undef       EEP_START_SEC_CODE
  // TEST //#pragma ghs section text=".text.EEP_CODE"
  // TEST //#pragma ghs section rodata=".rodata.EEP_ROM_CONST_UNSPECIFIED"
  // TEST //#pragma ghs section bss=".bss.EEP_RAM_VAR_CLEARED_UNSPECIFIED"
  // TEST //#pragma ghs section data=".data.EEP_RAM_VAR_INIT_UNSPECIFIED"
#elif defined (EEP_STOP_SEC_CODE)
  #undef       EEP_STOP_SEC_CODE
  // TEST //#pragma ghs section
#elif defined (EEP_START_SEC_VAR_CLEARED_BOOLEAN)
  #undef       EEP_START_SEC_VAR_CLEARED_BOOLEAN
  // TEST //#pragma ghs section bss=".bss.EEP_RAM_VAR_POWER_ON_CLEARED_BOOLEAN"
#elif defined (EEP_STOP_SEC_VAR_CLEARED_BOOLEAN)
  #undef       EEP_STOP_SEC_VAR_CLEARED_BOOLEAN
  // TEST //#pragma ghs section
#elif defined (EEP_START_SEC_VAR_CLEARED_8)
  #undef       EEP_START_SEC_VAR_CLEARED_8
  // TEST //#pragma ghs section bss=".bss.EEP_RAM_VAR_POWER_ON_CLEARED_8"
#elif defined (EEP_STOP_SEC_VAR_CLEARED_8)
  #undef       EEP_STOP_SEC_VAR_CLEARED_8
  // TEST //#pragma ghs section
#elif defined (EEP_START_SEC_VAR_CLEARED_16)
  #undef       EEP_START_SEC_VAR_CLEARED_16
  // TEST //#pragma ghs section bss=".bss.EEP_RAM_VAR_POWER_ON_CLEARED_16"
#elif defined (EEP_STOP_SEC_VAR_CLEARED_16)
  #undef       EEP_STOP_SEC_VAR_CLEARED_16
  // TEST //#pragma ghs section
#elif defined (EEP_START_SEC_VAR_CLEARED_32)
  #undef       EEP_START_SEC_VAR_CLEARED_32
  // TEST //#pragma ghs section bss=".bss.EEP_RAM_VAR_POWER_ON_CLEARED_32"
#elif defined (EEP_STOP_SEC_VAR_CLEARED_32)
  #undef       EEP_STOP_SEC_VAR_CLEARED_32
  // TEST //#pragma ghs section
#elif defined (EEP_START_SEC_VAR_POWER_ON_CLEARED_8)
  #undef       EEP_START_SEC_VAR_POWER_ON_CLEARED_8
  // TEST //#pragma ghs section bss=".bss.EEP_RAM_VAR_POWER_ON_CLEARED_8"
#elif defined (EEP_STOP_SEC_VAR_POWER_ON_CLEARED_8)
  #undef       EEP_STOP_SEC_VAR_POWER_ON_CLEARED_8
  // TEST //#pragma ghs section
#elif defined (EEP_START_SEC_VAR_POWER_ON_CLEARED_16)
  #undef       EEP_START_SEC_VAR_POWER_ON_CLEARED_16
  // TEST //#pragma ghs section bss=".bss.EEP_RAM_VAR_POWER_ON_CLEARED_16"
#elif defined (EEP_STOP_SEC_VAR_POWER_ON_CLEARED_16)
  #undef       EEP_STOP_SEC_VAR_POWER_ON_CLEARED_16
  // TEST //#pragma ghs section
#elif defined (EEP_START_SEC_VAR_POWER_ON_CLEARED_32)
  #undef       EEP_START_SEC_VAR_POWER_ON_CLEARED_32
  // TEST //#pragma ghs section bss=".bss.EEP_RAM_VAR_POWER_ON_CLEARED_32"
#elif defined (EEP_STOP_SEC_VAR_POWER_ON_CLEARED_32)
  #undef       EEP_STOP_SEC_VAR_POWER_ON_CLEARED_32
  // TEST //#pragma ghs section
#elif defined (EEP_START_SEC_CONST_UNSPECIFIED)
  #undef       EEP_START_SEC_CONST_UNSPECIFIED
  // TEST //#pragma ghs section rodata=".rodata.EEP_ROM_CONST_UNSPECIFIED"
#elif defined (EEP_STOP_SEC_CONST_UNSPECIFIED)
  #undef       EEP_STOP_SEC_CONST_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (EEP_START_SEC_VAR_CLEARED_ALIGNED_ADDR_UNSPECIFIED)
  #undef       EEP_START_SEC_VAR_CLEARED_ALIGNED_ADDR_UNSPECIFIED
  // TEST //#pragma ghs section bss=".bss.EEP_RAM_VAR_CLEARED_ALIGNED_ADDR_UNSPECIFIED"
#elif defined (EEP_STOP_SEC_VAR_CLEARED_ALIGNED_ADDR_UNSPECIFIED)
  #undef       EEP_STOP_SEC_VAR_CLEARED_ALIGNED_ADDR_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (EEP_START_SEC_VAR_INIT_8)
  #undef       EEP_START_SEC_VAR_INIT_8
  // TEST //#pragma ghs section data=".data.EEP_RAM_VAR_INIT_8"
#elif defined (EEP_STOP_SEC_VAR_INIT_8)
  #undef       EEP_STOP_SEC_VAR_INIT_8
  // TEST //#pragma ghs section
#elif defined (EEP_START_SEC_VAR_INIT_UNSPECIFIED)
  #undef       EEP_START_SEC_VAR_INIT_UNSPECIFIED
  // TEST //#pragma ghs section data=".data.EEP_RAM_VAR_INIT_UNSPECIFIED"
#elif defined (EEP_STOP_SEC_VAR_INIT_UNSPECIFIED)
  #undef       EEP_STOP_SEC_VAR_INIT_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (EEP_START_SEC_VAR_CLEARED_UNSPECIFIED)
  #undef       EEP_START_SEC_VAR_CLEARED_UNSPECIFIED
  // TEST //#pragma ghs section bss=".bss.EEP_RAM_VAR_CLEARED_UNSPECIFIED"
#elif defined (EEP_STOP_SEC_VAR_CLEARED_UNSPECIFIED)
  #undef       EEP_STOP_SEC_VAR_CLEARED_UNSPECIFIED
  // TEST //#pragma ghs section
/* -------------------------------------------------------------------------- */
/*                                 Ea                                         */
/* -------------------------------------------------------------------------- */
#elif defined (EA_START_SEC_CODE)
  #undef       EA_START_SEC_CODE
  // TEST //#pragma ghs section text=".text.EA_CODE"
  // TEST //#pragma ghs section rodata=".rodata.EA_ROM_CONST_UNSPECIFIED"
  // TEST //#pragma ghs section bss=".bss.EA_RAM_VAR_CLEARED_UNSPECIFIED"
  // TEST //#pragma ghs section data=".data.EA_RAM_VAR_INIT_UNSPECIFIED"
#elif defined (EA_STOP_SEC_CODE)
  #undef       EA_STOP_SEC_CODE
  // TEST //#pragma ghs section
#elif defined (EA_START_SEC_VAR_CLEARED_BOOLEAN)
  #undef       EA_START_SEC_VAR_CLEARED_BOOLEAN
  // TEST //#pragma ghs section bss=".bss.EA_RAM_VAR_CLEARED_BOOLEAN"
#elif defined (EA_STOP_SEC_VAR_CLEARED_BOOLEAN)
  #undef       EA_STOP_SEC_VAR_CLEARED_BOOLEAN
  // TEST //#pragma ghs section
#elif defined (EA_START_SEC_NO_INIT_VAR_BOOLEAN)
  #undef       EA_START_SEC_NO_INIT_VAR_BOOLEAN
  // TEST //#pragma ghs section bss=".bss.EA_RAM_VAR_NO_INIT_BOOLEAN"
#elif defined (EA_STOP_SEC_NO_INIT_VAR_BOOLEAN)
  #undef       EA_STOP_SEC_NO_INIT_VAR_BOOLEAN
  // TEST //#pragma ghs section
#elif defined (EA_START_SEC_VAR_CLEARED_UNSPECIFIED)
  #undef       EA_START_SEC_VAR_CLEARED_UNSPECIFIED
  // TEST //#pragma ghs section bss=".bss.EA_RAM_VAR_CLEARED_UNSPECIFIED"
#elif defined (EA_STOP_SEC_VAR_CLEARED_UNSPECIFIED)
  #undef       EA_STOP_SEC_VAR_CLEARED_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (EA_START_SEC_VAR_CLEARED_ALIGNED_ADDR_UNSPECIFIED)
  #undef       EA_START_SEC_VAR_CLEARED_ALIGNED_ADDR_UNSPECIFIED
  // TEST //#pragma ghs section bss=".bss.EA_RAM_VAR_CLEARED_ALIGNED_ADDR_UNSPECIFIED"
#elif defined (EA_STOP_SEC_VAR_CLEARED_ALIGNED_ADDR_UNSPECIFIED)
  #undef       EA_STOP_SEC_VAR_CLEARED_ALIGNED_ADDR_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (EA_START_SEC_VAR_SAVED_ZONE_UNSPECIFIED)
  #undef       EA_START_SEC_VAR_SAVED_ZONE_UNSPECIFIED
  // TEST //#pragma ghs section bss=".bss.EA_RAM_VAR_SAVED_ZONE_UNSPECIFIED"
#elif defined (EA_STOP_SEC_VAR_SAVED_ZONE_UNSPECIFIED)
  #undef       EA_STOP_SEC_VAR_SAVED_ZONE_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (EA_START_SEC_CONST_16)
  #undef       EA_START_SEC_CONST_16
  // TEST //#pragma ghs section rodata=".rodata.EA_ROM_CONST_16"
#elif defined (EA_STOP_SEC_CONST_16)
  #undef       EA_STOP_SEC_CONST_16
  // TEST //#pragma ghs section
#elif defined (EA_START_SEC_CONST_32)
  #undef       EA_START_SEC_CONST_32
  // TEST //#pragma ghs section rodata=".rodata.EA_ROM_CONST_32"
#elif defined (EA_STOP_SEC_CONST_32)
  #undef       EA_STOP_SEC_CONST_32
  // TEST //#pragma ghs section
#elif defined (EA_START_SEC_CONST_PTR)
  #undef       EA_START_SEC_CONST_PTR
  // TEST //#pragma ghs section rodata=".rodata.EA_ROM_CONST_PTR"
#elif defined (EA_STOP_SEC_CONST_PTR)
  #undef       EA_STOP_SEC_CONST_PTR
  // TEST //#pragma ghs section
#elif defined (EA_START_SEC_VAR_NO_INIT_PTR)
  #undef       EA_START_SEC_VAR_NO_INIT_PTR
  // TEST //#pragma ghs section bss=".bss.EA_RAM_VAR_NO_INIT_PTR"
#elif defined (EA_STOP_SEC_VAR_NO_INIT_PTR)
  #undef       EA_STOP_SEC_VAR_NO_INIT_PTR
  // TEST //#pragma ghs section
#elif defined (EA_START_SEC_CONST_UNSPECIFIED)
  #undef       EA_START_SEC_CONST_UNSPECIFIED
  // TEST //#pragma ghs section rodata=".rodata.EA_ROM_CONST_UNSPECIFIED"
#elif defined (EA_STOP_SEC_CONST_UNSPECIFIED)
  #undef       EA_STOP_SEC_CONST_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (EA_START_SEC_NO_INIT_VAR_16)
  #undef       EA_START_SEC_NO_INIT_VAR_16
  // TEST //#pragma ghs section bss=".bss.EA_RAM_VAR_NO_INIT_16"
#elif defined (EA_STOP_SEC_NO_INIT_VAR_16)
  #undef       EA_STOP_SEC_NO_INIT_VAR_16
  // TEST //#pragma ghs section
#elif defined (EA_START_SEC_NO_INIT_VAR_8)
  #undef       EA_START_SEC_NO_INIT_VAR_8
  // TEST //#pragma ghs section bss=".bss.EA_RAM_VAR_NO_INIT_8"
#elif defined (EA_STOP_SEC_NO_INIT_VAR_8)
  #undef       EA_STOP_SEC_NO_INIT_VAR_8
  // TEST //#pragma ghs section
#elif defined (EA_START_SEC_NO_INIT_VAR_UNSPECIFIED)
  #undef       EA_START_SEC_NO_INIT_VAR_UNSPECIFIED
  // TEST //#pragma ghs section bss=".bss.EA_RAM_VAR_NO_INIT_UNSPECIFIED"
#elif defined (EA_STOP_SEC_NO_INIT_VAR_UNSPECIFIED)
  #undef       EA_STOP_SEC_NO_INIT_VAR_UNSPECIFIED
  // TEST //#pragma ghs section
/* -------------------------------------------------------------------------- */
/*                 RTE                                                        */
/* -------------------------------------------------------------------------- */
#elif defined (BSWMODULEDESCRIPTION_CALIB_START_SEC_CODE)
  #undef       BSWMODULEDESCRIPTION_CALIB_START_SEC_CODE
  // TEST //#pragma ghs section text=".text.RTE_CODE"
  // TEST //#pragma ghs section rodata=".rodata.RTE_ROM_CONST_UNSPECIFIED"
  // TEST //#pragma ghs section bss=".bss.RTE_RAM_VAR_CLEARED_UNSPECIFIED"
  // TEST //#pragma ghs section data=".data.RTE_RAM_VAR_INIT_UNSPECIFIED"
#elif defined (BSWMODULEDESCRIPTION_CALIB_STOP_SEC_CODE)
  #undef       BSWMODULEDESCRIPTION_CALIB_STOP_SEC_CODE
  // TEST //#pragma ghs section
/* -------------------------------------------------------------------------- */
/*                 CAL                                                        */
/* -------------------------------------------------------------------------- */
#elif defined (CAL_START_SEC_CODE)
  #undef       CAL_START_SEC_CODE
  // TEST //#pragma ghs section text=".text. CAL_CODE"
  // TEST //#pragma ghs section rodata=".rodata. CAL_ROM_CONST_UNSPECIFIED"
  // TEST //#pragma ghs section bss=".bss. CAL_RAM_VAR_CLEARED_UNSPECIFIED"
  // TEST //#pragma ghs section data=".data. CAL_RAM_VAR_INIT_UNSPECIFIED"
#elif defined (CAL_STOP_SEC_CODE)
  #undef       CAL_STOP_SEC_CODE
  // TEST //#pragma ghs section
#elif defined (CAL_START_SEC_CONST_32)
  #undef       CAL_START_SEC_CONST_32
  // TEST //#pragma ghs section rodata=".rodata. CAL_ROM_CONST_32"
#elif defined (CAL_STOP_SEC_CONST_32)
  #undef       CAL_STOP_SEC_CONST_32
  // TEST //#pragma ghs section
#elif defined (CAL_START_SEC_CONST_UNSPECIFIED)
  #undef       CAL_START_SEC_CONST_UNSPECIFIED
  // TEST //#pragma ghs section rodata=".rodata. CAL_ROM_CONST_UNSPECIFIED"
#elif defined (CAL_STOP_SEC_CONST_UNSPECIFIED)
  #undef       CAL_STOP_SEC_CONST_UNSPECIFIED
  // TEST //#pragma ghs section
/* -------------------------------------------------------------------------- */
/*                 CSM                                                        */
/* -------------------------------------------------------------------------- */
#elif defined (CSM_START_SEC_CODE)
  #undef       CSM_START_SEC_CODE
  // TEST //#pragma ghs section text=".text.CSM_CODE"
  // TEST //#pragma ghs section rodata=".rodata.CSM_ROM_CONST_UNSPECIFIED"
  // TEST //#pragma ghs section bss=".bss.CSM_RAM_VAR_CLEARED_UNSPECIFIED"
  // TEST //#pragma ghs section data=".data.CSM_RAM_VAR_INIT_UNSPECIFIED"
#elif defined (CSM_STOP_SEC_CODE)
  #undef       CSM_STOP_SEC_CODE
  // TEST //#pragma ghs section

#elif defined (CSM_START_SEC_CONST_8)
  #undef       CSM_START_SEC_CONST_8
  // TEST //#pragma ghs section rodata=".rodata.CSM_ROM_CONST_8"
#elif defined (CSM_STOP_SEC_CONST_8)
  #undef       CSM_STOP_SEC_CONST_8
  // TEST //#pragma ghs section

#elif defined (CSM_START_SEC_CONST_UNSPECIFIED)
  #undef       CSM_START_SEC_CONST_UNSPECIFIED
  // TEST //#pragma ghs section rodata=".rodata.CSM_ROM_CONST_UNSPECIFIED"
#elif defined (CSM_STOP_SEC_CONST_UNSPECIFIED)
  #undef       CSM_STOP_SEC_CONST_UNSPECIFIED
  // TEST //#pragma ghs section

#elif defined (CSM_START_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED)
  #undef       CSM_START_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
  // TEST //#pragma ghs section rodata=".rodata.CSM_ROM_CONFIG_DATA_PREBUILD_UNSPECIFIED"
#elif defined (CSM_STOP_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED)
  #undef       CSM_STOP_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
  // TEST //#pragma ghs section

#elif defined (CSM_START_SEC_VAR_CLEARED_BOOLEAN)
  #undef       CSM_START_SEC_VAR_CLEARED_BOOLEAN
  // TEST //#pragma ghs section bss=".bss.CSM_RAM_VAR_CLEARED_BOOLEAN"
#elif defined (CSM_STOP_SEC_VAR_CLEARED_BOOLEAN)
  #undef       CSM_STOP_SEC_VAR_CLEARED_BOOLEAN
  // TEST //#pragma ghs section

#elif defined (CSM_START_SEC_VAR_CLEARED_8)
  #undef       CSM_START_SEC_VAR_CLEARED_8
  // TEST //#pragma ghs section bss=".bss.CSM_RAM_VAR_CLEARED_8"
#elif defined (CSM_STOP_SEC_VAR_CLEARED_8)
  #undef       CSM_STOP_SEC_VAR_CLEARED_8
  // TEST //#pragma ghs section
  
 #elif defined (CSM_START_SEC_VAR_CLEARED_16)
  #undef       CSM_START_SEC_VAR_CLEARED_16
  // TEST //#pragma ghs section bss=".bss.CSM_RAM_VAR_CLEARED_16"
#elif defined (CSM_STOP_SEC_VAR_CLEARED_16)
  #undef       CSM_STOP_SEC_VAR_CLEARED_16
  // TEST //#pragma ghs section

#elif defined (CSM_START_SEC_VAR_CLEARED_32)
  #undef       CSM_START_SEC_VAR_CLEARED_32
  // TEST //#pragma ghs section bss=".bss.CSM_RAM_VAR_CLEARED_32"
#elif defined (CSM_STOP_SEC_VAR_CLEARED_32)
  #undef       CSM_STOP_SEC_VAR_CLEARED_32
  // TEST //#pragma ghs section

#elif defined (CSM_START_SEC_VAR_NO_INIT_UNSPECIFIED)
  #undef       CSM_START_SEC_VAR_NO_INIT_UNSPECIFIED
  // TEST //#pragma ghs section bss=".bss.CSM_RAM_VAR_NO_INIT_UNSPECIFIED"
#elif defined (CSM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED)
  #undef       CSM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
  // TEST //#pragma ghs section

#elif defined (CSM_START_SEC_VAR_CLEARED_UNSPECIFIED)
  #undef       CSM_START_SEC_VAR_CLEARED_UNSPECIFIED
  // TEST //#pragma ghs section bss=".bss.CSM_RAM_VAR_CLEARED_UNSPECIFIED"
#elif defined (CSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED)
  #undef       CSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
  // TEST //#pragma ghs section

#elif defined (CSM_START_SEC_VAR_INIT_UNSPECIFIED)
  #undef       CSM_START_SEC_VAR_INIT_UNSPECIFIED
  // TEST //#pragma ghs section data=".data.CSM_RAM_VAR_INIT_UNSPECIFIED"
#elif defined (CSM_STOP_SEC_VAR_INIT_UNSPECIFIED)
  #undef       CSM_STOP_SEC_VAR_INIT_UNSPECIFIED
  // TEST //#pragma ghs section

/* -------------------------------------------------------------------------- */
/*                 CRYPTOLIB                                                  */
/* -------------------------------------------------------------------------- */
#elif defined (CRYPTOLIB_START_SEC_CODE)
  #undef       CRYPTOLIB_START_SEC_CODE
  // TEST //#pragma ghs section text=".text.CRYPTOLIB_CODE"
  // TEST //#pragma ghs section rodata=".rodata.CRYPTOLIB_ROM_CONST_UNSPECIFIED"
  // TEST //#pragma ghs section bss=".bss.CRYPTOLIB_RAM_VAR_CLEARED_UNSPECIFIED"
  // TEST //#pragma ghs section data=".data.CRYPTOLIB_RAM_VAR_INIT_UNSPECIFIED"
#elif defined (CRYPTOLIB_STOP_SEC_CODE)
  #undef       CRYPTOLIB_STOP_SEC_CODE
  // TEST //#pragma ghs section
#elif defined (CRYPTOLIB_START_SEC_VAR_INIT_BOOLEAN)
  #undef       CRYPTOLIB_START_SEC_VAR_INIT_BOOLEAN
  // TEST //#pragma ghs section data=".data.CRYPTOLIB_RAM_VAR_INIT_BOOLEAN"
#elif defined (CRYPTOLIB_STOP_SEC_VAR_INIT_BOOLEAN)
  #undef       CRYPTOLIB_STOP_SEC_VAR_INIT_BOOLEAN
  // TEST //#pragma ghs section
#elif defined (CRYPTOLIB_START_SEC_VAR_INIT_8)
  #undef       CRYPTOLIB_START_SEC_VAR_INIT_8
  // TEST //#pragma ghs section data=".data.CRYPTOLIB_RAM_VAR_INIT_8"
#elif defined (CRYPTOLIB_STOP_SEC_VAR_INIT_8)
  #undef       CRYPTOLIB_STOP_SEC_VAR_INIT_8
  // TEST //#pragma ghs section
#elif defined (CRYPTOLIB_START_SEC_VAR_INIT_16)
  #undef       CRYPTOLIB_START_SEC_VAR_INIT_16
  // TEST //#pragma ghs section data=".data.CRYPTOLIB_RAM_VAR_INIT_16"
#elif defined (CRYPTOLIB_STOP_SEC_VAR_INIT_16)
  #undef       CRYPTOLIB_STOP_SEC_VAR_INIT_16
  // TEST //#pragma ghs section
#elif defined (CRYPTOLIB_START_SEC_VAR_INIT_32)
  #undef       CRYPTOLIB_START_SEC_VAR_INIT_32
  // TEST //#pragma ghs section data=".data.CRYPTOLIB_RAM_VAR_INIT_32"
#elif defined (CRYPTOLIB_STOP_SEC_VAR_INIT_32)
  #undef       CRYPTOLIB_STOP_SEC_VAR_INIT_32
  // TEST //#pragma ghs section
#elif defined (CRYPTOLIB_START_SEC_VAR_INIT_UNSPECIFIED)
  #undef       CRYPTOLIB_START_SEC_VAR_INIT_UNSPECIFIED
  // TEST //#pragma ghs section data=".data.CRYPTOLIB_RAM_VAR_INIT_UNSPECIFIED"
#elif defined (CRYPTOLIB_STOP_SEC_VAR_INIT_UNSPECIFIED)
  #undef       CRYPTOLIB_STOP_SEC_VAR_INIT_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (CRYPTOLIB_START_SEC_VAR_CLEARED_BOOLEAN)
  #undef       CRYPTOLIB_START_SEC_VAR_CLEARED_BOOLEAN
  // TEST //#pragma ghs section bss=".bss.CRYPTOLIB_RAM_VAR_CLEARED_BOOLEAN"
#elif defined (CRYPTOLIB_STOP_SEC_VAR_CLEARED_BOOLEAN)
  #undef       CRYPTOLIB_STOP_SEC_VAR_CLEARED_BOOLEAN
  // TEST //#pragma ghs section
#elif defined (CRYPTOLIB_START_SEC_VAR_CLEARED_8)
  #undef       CRYPTOLIB_START_SEC_VAR_CLEARED_8
  // TEST //#pragma ghs section bss=".bss.CRYPTOLIB_RAM_VAR_CLEARED_8"
#elif defined (CRYPTOLIB_STOP_SEC_VAR_CLEARED_8)
  #undef       CRYPTOLIB_STOP_SEC_VAR_CLEARED_8
  // TEST //#pragma ghs section
#elif defined (CRYPTOLIB_START_SEC_VAR_CLEARED_32)
  #undef       CRYPTOLIB_START_SEC_VAR_CLEARED_32
  // TEST //#pragma ghs section bss=".bss.CRYPTOLIB_RAM_VAR_CLEARED_32"
#elif defined (CRYPTOLIB_STOP_SEC_VAR_CLEARED_32)
  #undef       CRYPTOLIB_STOP_SEC_VAR_CLEARED_32
  // TEST //#pragma ghs section
#elif defined (CRYPTOLIB_START_SEC_VAR_CLEARED_UNSPECIFIED)
  #undef       CRYPTOLIB_START_SEC_VAR_CLEARED_UNSPECIFIED
  // TEST //#pragma ghs section bss=".bss.CRYPTOLIB_RAM_VAR_CLEARED_UNSPECIFIED"
#elif defined (CRYPTOLIB_STOP_SEC_VAR_CLEARED_UNSPECIFIED)
  #undef       CRYPTOLIB_STOP_SEC_VAR_CLEARED_UNSPECIFIED
  // TEST //#pragma ghs section

/* -------------------------------------------------------------------------- */
/*                 CryIf                                                      */
/* -------------------------------------------------------------------------- */
#elif defined (CRYIF_START_SEC_CODE)
  #undef      CRYIF_START_SEC_CODE
  // TEST //#pragma ghs section text=".text.CRYIF_CODE"
  // TEST //#pragma ghs section rodata=".rodata.CRYIF_ROM_CONST_UNSPECIFIED"
  // TEST //#pragma ghs section bss=".bss.CRYIF_RAM_VAR_CLEARED_UNSPECIFIED"
  // TEST //#pragma ghs section data=".data.CRYIF_RAM_VAR_INIT_UNSPECIFIED"
#elif defined (CRYIF_STOP_SEC_CODE)
  #undef      CRYIF_STOP_SEC_CODE
  // TEST //#pragma ghs section

#elif defined (CRYIF_START_SEC_VAR_CLEARED_BOOLEAN)
  #undef      CRYIF_START_SEC_VAR_CLEARED_BOOLEAN
  // TEST //#pragma ghs section bss=".bss.CRYIF_RAM_VAR_CLEARED_BOOLEAN"
#elif defined (CRYIF_STOP_SEC_VAR_CLEARED_BOOLEAN)
  #undef      CRYIF_STOP_SEC_VAR_CLEARED_BOOLEAN
  // TEST //#pragma ghs section

#elif defined (CRYIF_START_SEC_VAR_CLEARED_8)
  #undef      CRYIF_START_SEC_VAR_CLEARED_8
  // TEST //#pragma ghs section bss=".bss.CRYIF_RAM_VAR_CLEARED_8"
#elif defined (CRYIF_STOP_SEC_VAR_CLEARED_8)
  #undef      CRYIF_STOP_SEC_VAR_CLEARED_8
  // TEST //#pragma ghs section

#elif defined (CRYIF_START_SEC_VAR_CLEARED_32)
  #undef      CRYIF_START_SEC_VAR_CLEARED_32
  // TEST //#pragma ghs section bss=".bss.CRYIF_RAM_VAR_CLEARED_32"
#elif defined (CRYIF_STOP_SEC_VAR_CLEARED_32)
  #undef      CRYIF_STOP_SEC_VAR_CLEARED_32
  // TEST //#pragma ghs section

#elif defined (CRYIF_START_SEC_VAR_CLEARED_UNSPECIFIED)
  #undef      CRYIF_START_SEC_VAR_CLEARED_UNSPECIFIED
  // TEST //#pragma ghs section bss=".bss.CRYIF_RAM_VAR_CLEARED_UNSPECIFIED"
#elif defined (CRYIF_STOP_SEC_VAR_CLEARED_UNSPECIFIED)
  #undef      CRYIF_STOP_SEC_VAR_CLEARED_UNSPECIFIED
  // TEST //#pragma ghs section

#elif defined (CRYIF_START_SEC_CONST_UNSPECIFIED)
  #undef      CRYIF_START_SEC_CONST_UNSPECIFIED
  // TEST //#pragma ghs section rodata=".rodata.CRYIF_ROM_CONST_UNSPECIFIED"
#elif defined (CRYIF_STOP_SEC_CONST_UNSPECIFIED)
    #undef      CRYIF_STOP_SEC_CONST_UNSPECIFIED
  // TEST //#pragma ghs section

#elif defined (CRYIF_START_SEC_CONST_8)
  #undef      CRYIF_START_SEC_CONST_8
  // TEST //#pragma ghs section rodata=".rodata.CRYIF_ROM_CONST_8"
#elif defined (CRYIF_STOP_SEC_CONST_8)
    #undef      CRYIF_STOP_SEC_CONST_8
  // TEST //#pragma ghs section

#elif defined (CRYIF_START_SEC_CONST_PTR)
  #undef      CRYIF_START_SEC_CONST_PTR
  // TEST //#pragma ghs section rodata=".rodata.CRYIF_ROM_CONST_PTR"
#elif defined (CRYIF_STOP_SEC_CONST_PTR)
    #undef      CRYIF_STOP_SEC_CONST_PTR
  // TEST //#pragma ghs section

#elif defined (CRYIF_START_SEC_CONST_32)
  #undef      CRYIF_START_SEC_CONST_32
  // TEST //#pragma ghs section rodata=".rodata.CRYIF_ROM_CONST_32"
#elif defined (CRYIF_STOP_SEC_CONST_32)
  #undef      CRYIF_STOP_SEC_CONST_32
  // TEST //#pragma ghs section

/* -------------------------------------------------------------------------- */
/*                 CRYPTO                                                     */
/* -------------------------------------------------------------------------- */
#elif defined (CRYPTO_76_COMMON_START_SEC_CODE)
  #undef       CRYPTO_76_COMMON_START_SEC_CODE
  // TEST //#pragma ghs section text=".text.CRYPTO_76_COMMON_CODE"
  // TEST //#pragma ghs section rodata=".rodata.CRYPTO_76_COMMON_ROM_CONST_UNSPECIFIED"
  // TEST //#pragma ghs section bss=".bss.CRYPTO_76_COMMON_RAM_VAR_CLEARED_UNSPECIFIED"
  // TEST //#pragma ghs section data=".data.CRYPTO_76_COMMON_RAM_VAR_INIT_UNSPECIFIED"
#elif defined (CRYPTO_76_COMMON_STOP_SEC_CODE)
  #undef       CRYPTO_76_COMMON_STOP_SEC_CODE
  // TEST //#pragma ghs section

#elif defined (CRYPTO_76_COMMON_START_SEC_VAR_CLEARED_BOOLEAN)
  #undef      CRYPTO_76_COMMON_START_SEC_VAR_CLEARED_BOOLEAN
  // TEST //#pragma ghs section bss=".bss.CRYPTO_76_COMMON_RAM_VAR_CLEARED_BOOLEAN"
#elif defined (CRYPTO_76_COMMON_STOP_SEC_VAR_CLEARED_BOOLEAN)
  #undef       CRYPTO_76_COMMON_STOP_SEC_VAR_CLEARED_BOOLEAN
  // TEST //#pragma ghs section

#elif defined (CRYPTO_76_COMMON_START_SEC_CONST_UNSPECIFIED)
  #undef       CRYPTO_76_COMMON_START_SEC_CONST_UNSPECIFIED
  // TEST //#pragma ghs section rodata=".rodata.CRYPTO_76_COMMON_ROM_CONST_UNSPECIFIED"
#elif defined (CRYPTO_76_COMMON_STOP_SEC_CONST_UNSPECIFIED)
  #undef      CRYPTO_76_COMMON_STOP_SEC_CONST_UNSPECIFIED
  // TEST //#pragma ghs section

#elif defined (CRYPTO_76_COMMON_START_SEC_VAR_CLEARED_8)
  #undef      CRYPTO_76_COMMON_START_SEC_VAR_CLEARED_8
  // TEST //#pragma ghs section bss=".bss.CRYPTO_76_COMMON_RAM_VAR_CLEARED_8"
#elif defined (CRYPTO_76_COMMON_STOP_SEC_VAR_CLEARED_8)
  #undef      CRYPTO_76_COMMON_STOP_SEC_VAR_CLEARED_8
  // TEST //#pragma ghs section

#elif defined (CRYPTO_76_COMMON_START_SEC_VAR_CLEARED_32)
  #undef      CRYPTO_76_COMMON_START_SEC_VAR_CLEARED_32
  // TEST //#pragma ghs section bss=".bss.CRYPTO_76_COMMON_RAM_VAR_CLEARED_32"
#elif defined (CRYPTO_76_COMMON_STOP_SEC_VAR_CLEARED_32)
  #undef      CRYPTO_76_COMMON_STOP_SEC_VAR_CLEARED_32
  // TEST //#pragma ghs section

#elif defined (CRYPTO_76_COMMON_START_SEC_VAR_INIT_UNSPECIFIED)
  #undef      CRYPTO_76_COMMON_START_SEC_VAR_INIT_UNSPECIFIED
  // TEST //#pragma ghs section data=".data.CRYPTO_76_COMMON_RAM_VAR_INIT_UNSPECIFIED"
#elif defined (CRYPTO_76_COMMON_STOP_SEC_VAR_INIT_UNSPECIFIED)
  #undef      CRYPTO_76_COMMON_STOP_SEC_VAR_INIT_UNSPECIFIED
  // TEST //#pragma ghs section

#elif defined (CRYPTO_76_COMMON_START_SEC_VAR_CLEARED_UNSPECIFIED)
  #undef      CRYPTO_76_COMMON_START_SEC_VAR_CLEARED_UNSPECIFIED
  // TEST //#pragma ghs section bss=".bss.CRYPTO_76_COMMON_RAM_VAR_CLEARED_UNSPECIFIED"
#elif defined (CRYPTO_76_COMMON_STOP_SEC_VAR_CLEARED_UNSPECIFIED)
  #undef      CRYPTO_76_COMMON_STOP_SEC_VAR_CLEARED_UNSPECIFIED
  // TEST //#pragma ghs section

/* -------------------------------------------------------------------------- */
/*                 KEYM                                                       */
/* -------------------------------------------------------------------------- */
#elif defined (KEYM_START_SEC_CODE)
  #undef       KEYM_START_SEC_CODE
  // TEST //#pragma ghs section text=".text.KEYM_CODE"
  // TEST //#pragma ghs section rodata=".rodata.KEYM_ROM_CONST_UNSPECIFIED"
  // TEST //#pragma ghs section bss=".bss.KEYM_RAM_VAR_CLEARED_UNSPECIFIED"
  // TEST //#pragma ghs section data=".data.KEYM_RAM_VAR_INIT_UNSPECIFIED"
#elif defined (KEYM_STOP_SEC_CODE)
  #undef       KEYM_STOP_SEC_CODE
  // TEST //#pragma ghs section

#elif defined (KEYM_START_SEC_CONST_8)
  #undef       KEYM_START_SEC_CONST_8
  // TEST //#pragma ghs section rodata=".rodata.KEYM_ROM_CONST_8"
#elif defined (KEYM_STOP_SEC_CONST_8)
  #undef       KEYM_STOP_SEC_CONST_8
  // TEST //#pragma ghs section

#elif defined (KEYM_START_SEC_VAR_CLEARED_8)
  #undef       KEYM_START_SEC_VAR_CLEARED_8
  // TEST //#pragma ghs section bss=".bss.KEYM_RAM_VAR_CLEARED_8"
#elif defined (KEYM_STOP_SEC_VAR_CLEARED_8)
  #undef       KEYM_STOP_SEC_VAR_CLEARED_8
  // TEST //#pragma ghs section

#elif defined (KEYM_START_SEC_VAR_INIT_UNSPECIFIED)
  #undef       KEYM_START_SEC_VAR_INIT_UNSPECIFIED
  // TEST //#pragma ghs section data=".data.KEYM_RAM_VAR_INIT_UNSPECIFIED"
#elif defined (KEYM_STOP_SEC_VAR_INIT_UNSPECIFIED)
  #undef       KEYM_STOP_SEC_VAR_INIT_UNSPECIFIED
  // TEST //#pragma ghs section

#elif defined (KEYM_START_SEC_CONST_UNSPECIFIED)
  #undef       KEYM_START_SEC_CONST_UNSPECIFIED
  // TEST //#pragma ghs section rodata=".rodata.KEYM_ROM_CONST_UNSPECIFIED"
#elif defined (KEYM_STOP_SEC_CONST_UNSPECIFIED)
  #undef       KEYM_STOP_SEC_CONST_UNSPECIFIED
  // TEST //#pragma ghs section

#elif defined (KEYM_START_SEC_VAR_NO_INIT_UNSPECIFIED)
  #undef       KEYM_START_SEC_VAR_NO_INIT_UNSPECIFIED
  // TEST //#pragma ghs section bss=".bss.KEYM_RAM_VAR_NO_INIT_UNSPECIFIED"
#elif defined (KEYM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED)
  #undef       KEYM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
  // TEST //#pragma ghs section

#elif defined (KEYM_START_SEC_VAR_CLEARED_UNSPECIFIED)
  #undef       KEYM_START_SEC_VAR_CLEARED_UNSPECIFIED
  // TEST //#pragma ghs section bss=".bss.KEYM_RAM_VAR_CLEARED_UNSPECIFIED"
#elif defined (KEYM_STOP_SEC_VAR_CLEARED_UNSPECIFIED)
  #undef       KEYM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
  // TEST //#pragma ghs section

#elif defined (KEYM_START_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED)
  #undef       KEYM_START_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
  // TEST //#pragma ghs section rodata=".rodata.KEYM_ROM_CONFIG_DATA_PREBUILD_UNSPECIFIED"
#elif defined (KEYM_STOP_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED)
  #undef       KEYM_STOP_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
  // TEST //#pragma ghs section
  
/* -------------------------------------------------------------------------- */
/*                 WDGIF                                                      */
/* -------------------------------------------------------------------------- */
#elif defined (WDGIF_START_SEC_CODE)
  #undef       WDGIF_START_SEC_CODE
  // TEST //#pragma ghs section text=".text.WDGIF_CODE"
  // TEST //#pragma ghs section rodata=".rodata.WDGIF_ROM_CONST_UNSPECIFIED"
  // TEST //#pragma ghs section bss=".bss.WDGIF_RAM_VAR_CLEARED_UNSPECIFIED"
  // TEST //#pragma ghs section data=".data.WDGIF_RAM_VAR_INIT_UNSPECIFIED"
#elif defined (WDGIF_STOP_SEC_CODE)
  #undef       WDGIF_STOP_SEC_CODE
  // TEST //#pragma ghs section
#elif defined (WDGIF_START_SEC_CONFIG_DATA_PREBUILD_PTR)
  #undef       WDGIF_START_SEC_CONFIG_DATA_PREBUILD_PTR
  // TEST //#pragma ghs section rodata=".rodata.WDGIF_RAM_VAR_INIT_UNSPECIFIED"
#elif defined (WDGIF_STOP_SEC_CONFIG_DATA_PREBUILD_PTR)
  #undef       WDGIF_STOP_SEC_CONFIG_DATA_PREBUILD_PTR
  // TEST //#pragma ghs section
/* ---------------------------------------------------------------------------*/
/*                           WDG_76_ACW                                       */
/* -------------------------------------------------------------------------- */
#elif defined (WDG_76_ACW_START_SEC_CODE)
  #undef       WDG_76_ACW_START_SEC_CODE
  // TEST //#pragma ghs section text=".text.WDG_76_ACW_CODE"
  // TEST //#pragma ghs section rodata=".rodata.WDG_76_ACW_ROM_CONST_UNSPECIFIED"
  // TEST //#pragma ghs section bss=".bss.WDG_76_ACW_RAM_VAR_CLEARED_UNSPECIFIED"
  // TEST //#pragma ghs section data=".data.WDG_76_ACW_RAM_VAR_INIT_UNSPECIFIED"
#elif defined (WDG_76_ACW_STOP_SEC_CODE)
  #undef       WDG_76_ACW_STOP_SEC_CODE
  // TEST //#pragma ghs section
#elif defined (WDG_76_ACW_START_SEC_VAR_CLEARED_32)
  #undef       WDG_76_ACW_START_SEC_VAR_CLEARED_32
  // TEST //#pragma ghs section bss=".bss.WDG_76_ACW_RAM_VAR_CLEARED_32"
#elif defined (WDG_76_ACW_STOP_SEC_VAR_CLEARED_32)
  #undef       WDG_76_ACW_STOP_SEC_VAR_CLEARED_32
  // TEST //#pragma ghs section
#elif defined (WDG_76_ACW_START_SEC_VAR_INIT_UNSPECIFIED)
  #undef       WDG_76_ACW_START_SEC_VAR_INIT_UNSPECIFIED
  // TEST //#pragma ghs section bss=".bss.WDG_76_ACW_RAM_VAR_CLEARED_UNSPECIFIED"
#elif defined (WDG_76_ACW_STOP_SEC_VAR_INIT_UNSPECIFIED)
  #undef       WDG_76_ACW_STOP_SEC_VAR_INIT_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (WDG_76_ACW_START_SEC_CONST_UNSPECIFIED)
  #undef       WDG_76_ACW_START_SEC_CONST_UNSPECIFIED
  // TEST //#pragma ghs section rodata=".rodata.WDG_76_ACW_ROM_CONST_UNSPECIFIED"
#elif defined (WDG_76_ACW_STOP_SEC_CONST_UNSPECIFIED)
  #undef       WDG_76_ACW_STOP_SEC_CONST_UNSPECIFIED
  // TEST //#pragma ghs section
/* -------------------------------------------------------------------------- */
/*                 WDGM                                                       */
/* -------------------------------------------------------------------------- */
#elif defined (WDGM_START_SEC_VAR_CLEARED_BOOLEAN)
  #undef       WDGM_START_SEC_VAR_CLEARED_BOOLEAN
  // TEST //#pragma ghs section bss=".bss.WDGM_RAM_VAR_CLEARED_BOOLEAN"
#elif defined (WDGM_STOP_SEC_VAR_CLEARED_BOOLEAN)
  #undef       WDGM_STOP_SEC_VAR_CLEARED_BOOLEAN
  // TEST //#pragma ghs section
#elif defined (WDGM_START_SEC_CONST_UNSPECIFIED)
  #undef       WDGM_START_SEC_CONST_UNSPECIFIED
  // TEST //#pragma ghs section rodata=".rodata.WDGM_ROM_CONST_UNSPECIFIED"
#elif defined (WDGM_STOP_SEC_CONST_UNSPECIFIED)
  #undef       WDGM_STOP_SEC_CONST_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (WDGM_START_SEC_CODE)
  #undef       WDGM_START_SEC_CODE
  // TEST //#pragma ghs section text=".text.WDGM_CODE"
  // TEST //#pragma ghs section rodata=".rodata.WDGM_ROM_CONST_UNSPECIFIED"
  // TEST //#pragma ghs section bss=".bss.WDGM_RAM_VAR_CLEARED_UNSPECIFIED"
  // TEST //#pragma ghs section data=".data.WDGM_RAM_VAR_INIT_UNSPECIFIED"
#elif defined (WDGM_STOP_SEC_CODE)
  #undef       WDGM_STOP_SEC_CODE
  // TEST //#pragma ghs section
#elif defined (WDGM_START_SEC_PUBLIC_CODE)
  #undef       WDGM_START_SEC_PUBLIC_CODE
  // TEST //#pragma ghs section text=".text.WDGM_PUBLIC_CODE"
  // TEST //#pragma ghs section rodata=".rodata.WDGM_ROM_CONST_UNSPECIFIED"
  // TEST //#pragma ghs section bss=".bss.WDGM_RAM_VAR_CLEARED_UNSPECIFIED"
  // TEST //#pragma ghs section data=".data.WDGM_RAM_VAR_INIT_UNSPECIFIED"
#elif defined (WDGM_STOP_SEC_PUBLIC_CODE)
  #undef       WDGM_STOP_SEC_PUBLIC_CODE
  // TEST //#pragma ghs section
#elif defined (WDGM_START_SEC_VAR_CLEARED_8)
  #undef       WDGM_START_SEC_VAR_CLEARED_8
  // TEST //#pragma ghs section bss=".bss.WDGM_RAM_VAR_CLEARED_8"
#elif defined (WDGM_STOP_SEC_VAR_CLEARED_8)
  #undef       WDGM_STOP_SEC_VAR_CLEARED_8
  // TEST //#pragma ghs section
#elif defined (WDGM_START_SEC_VAR_CLEARED_16)
  #undef       WDGM_START_SEC_VAR_CLEARED_16
  // TEST //#pragma ghs section bss=".bss.WDGM_RAM_VAR_CLEARED_16"
#elif defined (WDGM_STOP_SEC_VAR_CLEARED_16)
  #undef       WDGM_STOP_SEC_VAR_CLEARED_16
  // TEST //#pragma ghs section
#elif defined (WDGM_START_SEC_VAR_CLEARED_UNSPECIFIED)
  #undef       WDGM_START_SEC_VAR_CLEARED_UNSPECIFIED
  // TEST //#pragma ghs section bss=".bss.WDGM_RAM_VAR_CLEARED_UNSPECIFIED"
#elif defined (WDGM_STOP_SEC_VAR_CLEARED_UNSPECIFIED)
  #undef       WDGM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (WDGM_START_SEC_CONST_8)
  #undef       WDGM_START_SEC_CONST_8
  // TEST //#pragma ghs section rodata=".rodata.WDGM_ROM_CONST_8"
#elif defined (WDGM_STOP_SEC_CONST_8)
  #undef       WDGM_STOP_SEC_CONST_8
  // TEST //#pragma ghs section
#elif defined (WDGM_START_SEC_CONST_16)
  #undef       WDGM_START_SEC_CONST_16
  // TEST //#pragma ghs section rodata=".rodata.WDGM_ROM_CONST_16"
#elif defined (WDGM_STOP_SEC_CONST_16)
  #undef       WDGM_STOP_SEC_CONST_16
  // TEST //#pragma ghs section
#elif defined (WDGM_START_SEC_VAR_NO_INIT_UNSPECIFIED)
  #undef       WDGM_START_SEC_VAR_NO_INIT_UNSPECIFIED
  // TEST //#pragma ghs section bss=".bss.WDGM_RAM_VAR_NO_INIT_UNSPECIFIED"
#elif defined (WDGM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED)
  #undef       WDGM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
  // TEST //#pragma ghs section
// sinil start, 13.04.02
// WdgM_GusFreeRunningCounter
#elif defined (WDGM_START_SEC_VAR_CLEARED_32)
  #undef       WDGM_START_SEC_VAR_CLEARED_32
  // TEST //#pragma ghs section bss=".bss.WDGM_RAM_VAR_CLEARED_32"
#elif defined (WDGM_STOP_SEC_VAR_CLEARED_32)
  #undef       WDGM_STOP_SEC_VAR_CLEARED_32
  // TEST //#pragma ghs section
// sinil end, 13.04.02
#elif defined (WDGM_START_SEC_VAR_INIT_UNSPECIFIED)
  #undef       WDGM_START_SEC_VAR_INIT_UNSPECIFIED
  // TEST //#pragma ghs section data=".data.WDGM_RAM_VAR_INIT_UNSPECIFIED"
#elif defined (WDGM_STOP_SEC_VAR_INIT_UNSPECIFIED)
  #undef       WDGM_STOP_SEC_VAR_INIT_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (WDGM_START_SEC_VAR_NO_INIT_BOOLEAN)
  #undef       WDGM_START_SEC_VAR_NO_INIT_BOOLEAN
  // TEST //#pragma ghs section bss=".bss.WDGM_RAM_VAR_NO_INIT_BOOLEAN"
#elif defined (WDGM_STOP_SEC_VAR_NO_INIT_BOOLEAN)
  #undef       WDGM_STOP_SEC_VAR_NO_INIT_BOOLEAN
  // TEST //#pragma ghs section
/* -------------------------------------------------------------------------- */
/* WDGM Global MemMap                                                         */
/* -------------------------------------------------------------------------- */
#elif defined (WDGM_START_SEC_CONST_ASIL_D_GLOBAL_UNSPECIFIED)
  #undef       WDGM_START_SEC_CONST_ASIL_D_GLOBAL_UNSPECIFIED
  // TEST //#pragma ghs section rodata=".rodata.WDGM_ROM_CONST_ASIL_D_GLOBAL_UNSPECIFIED"
#elif defined (WDGM_STOP_SEC_CONST_ASIL_D_GLOBAL_UNSPECIFIED)
  #undef       WDGM_STOP_SEC_CONST_ASIL_D_GLOBAL_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (WDGM_START_SEC_CODE_ASIL_D_GLOBAL)
  #undef       WDGM_START_SEC_CODE_ASIL_D_GLOBAL
  // TEST //#pragma ghs section text=".text.WDGM_CODE"
  // TEST //#pragma ghs section rodata=".rodata.WDGM_ROM_CONST_ASIL_D_GLOBAL_UNSPECIFIED"
  // TEST //#pragma ghs section bss=".bss.WDGM_RAM_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED"
  // TEST //#pragma ghs section data=".data.WDGM_RAM_VAR_INIT_ASIL_D_GLOBAL_UNSPECIFIED"
#elif defined (WDGM_STOP_SEC_CODE_ASIL_D_GLOBAL)
  #undef       WDGM_STOP_SEC_CODE_ASIL_D_GLOBAL
  // TEST //#pragma ghs section
#elif defined (WDGM_START_SEC_CONST_ASIL_D_GLOBAL_8)
  #undef       WDGM_START_SEC_CONST_ASIL_D_GLOBAL_8
  // TEST //#pragma ghs section rodata=".rodata.WDGM_ROM_CONST_ASIL_D_GLOBAL_8"
#elif defined (WDGM_STOP_SEC_CONST_ASIL_D_GLOBAL_8)
  #undef       WDGM_STOP_SEC_CONST_ASIL_D_GLOBAL_8
  // TEST //#pragma ghs section
#elif defined (WDGM_START_SEC_CONST_ASIL_D_GLOBAL_16)
  #undef       WDGM_START_SEC_CONST_ASIL_D_GLOBAL_16
  // TEST //#pragma ghs section rodata=".rodata.WDGM_ROM_CONST_ASIL_D_GLOBAL_16"
#elif defined (WDGM_STOP_SEC_CONST_ASIL_D_GLOBAL_16)
  #undef       WDGM_STOP_SEC_CONST_ASIL_D_GLOBAL_16
  // TEST //#pragma ghs section
#elif defined (WDGM_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_BOOLEAN)
  #undef       WDGM_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_BOOLEAN
  // TEST //#pragma ghs section bss=".bss.WDGM_RAM_VAR_CLEARED_ASIL_D_GLOBAL_BOOLEAN"
#elif defined (WDGM_STOP_SEC_VAR_CLEARED_ASIL_D_GLOBAL_BOOLEAN)
  #undef       WDGM_STOP_SEC_VAR_CLEARED_ASIL_D_GLOBAL_BOOLEAN
  // TEST //#pragma ghs section
#elif defined (WDGM_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_8)
  #undef       WDGM_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_8
  // TEST //#pragma ghs section bss=".bss.WDGM_RAM_VAR_CLEARED_ASIL_D_GLOBAL_8"
#elif defined (WDGM_STOP_SEC_VAR_CLEARED_ASIL_D_GLOBAL_8)
  #undef       WDGM_STOP_SEC_VAR_CLEARED_ASIL_D_GLOBAL_8
  // TEST //#pragma ghs section
#elif defined (WDGM_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_16)
  #undef       WDGM_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_16
  // TEST //#pragma ghs section bss=".bss.WDGM_RAM_VAR_CLEARED_ASIL_D_GLOBAL_16"
#elif defined (WDGM_STOP_SEC_VAR_CLEARED_ASIL_D_GLOBAL_16)
  #undef       WDGM_STOP_SEC_VAR_CLEARED_ASIL_D_GLOBAL_16
  // TEST //#pragma ghs section
#elif defined (WDGM_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED)
  #undef       WDGM_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED
  // TEST //#pragma ghs section bss=".bss.WDGM_RAM_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED"
#elif defined (WDGM_STOP_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED)
  #undef       WDGM_STOP_SEC_VAR_CLEARED_ASIL_D_GLOBAL_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (WDGM_START_SEC_VAR_NO_INIT_ASIL_D_GLOBAL_UNSPECIFIED)
  #undef       WDGM_START_SEC_VAR_NO_INIT_ASIL_D_GLOBAL_UNSPECIFIED
  // TEST //#pragma ghs section bss=".bss.WDGM_RAM_VAR_NO_INIT_ASIL_D_GLOBAL_UNSPECIFIED"
#elif defined (WDGM_STOP_SEC_VAR_NO_INIT_ASIL_D_GLOBAL_UNSPECIFIED)
  #undef       WDGM_STOP_SEC_VAR_NO_INIT_ASIL_D_GLOBAL_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (WDGM_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_32)
  #undef       WDGM_START_SEC_VAR_CLEARED_ASIL_D_GLOBAL_32
  // TEST //#pragma ghs section bss=".bss.WDGM_RAM_VAR_CLEARED_ASIL_D_GLOBAL_32"
#elif defined (WDGM_STOP_SEC_VAR_CLEARED_ASIL_D_GLOBAL_32)
  #undef       WDGM_STOP_SEC_VAR_CLEARED_ASIL_D_GLOBAL_32
  // TEST //#pragma ghs section
#elif defined (WDGM_START_SEC_VAR_INIT_ASIL_D_GLOBAL_UNSPECIFIED)
  #undef       WDGM_START_SEC_VAR_INIT_ASIL_D_GLOBAL_UNSPECIFIED
  // TEST //#pragma ghs section data=".data.WDGM_RAM_VAR_INIT_ASIL_D_GLOBAL_UNSPECIFIED"
#elif defined (WDGM_STOP_SEC_VAR_INIT_ASIL_D_GLOBAL_UNSPECIFIED)
  #undef       WDGM_STOP_SEC_VAR_INIT_ASIL_D_GLOBAL_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (WDGM_START_SEC_VAR_NO_INIT_ASIL_D_GLOBAL_BOOLEAN)
  #undef       WDGM_START_SEC_VAR_NO_INIT_ASIL_D_GLOBAL_BOOLEAN
  // TEST //#pragma ghs section bss=".bss.WDGM_RAM_VAR_NO_INIT_ASIL_D_GLOBAL_BOOLEAN"
#elif defined (WDGM_STOP_SEC_VAR_NO_INIT_ASIL_D_GLOBAL_BOOLEAN)
  #undef       WDGM_STOP_SEC_VAR_NO_INIT_ASIL_D_GLOBAL_BOOLEAN
  // TEST //#pragma ghs section
#elif defined (WDGM_START_SEC_CONFIG_DATA_PREBUILD_ASIL_D_UNSPECIFIED)
  #undef       WDGM_START_SEC_CONFIG_DATA_PREBUILD_ASIL_D_UNSPECIFIED
  // TEST //#pragma ghs section rodata=".rodata.WDGM_ROM_CONST_ASIL_D_GLOBAL_UNSPECIFIED"
#elif defined (WDGM_STOP_SEC_CONFIG_DATA_PREBUILD_ASIL_D_UNSPECIFIED)
  #undef       WDGM_STOP_SEC_CONFIG_DATA_PREBUILD_ASIL_D_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (WDGM_START_SEC_CONFIG_DATA_PREBUILD_ASIL_D_16)
  #undef       WDGM_START_SEC_CONFIG_DATA_PREBUILD_ASIL_D_16
  // TEST //#pragma ghs section rodata=".rodata.WDGM_ROM_CONST_ASIL_D_GLOBAL_16"
#elif defined (WDGM_STOP_SEC_CONFIG_DATA_PREBUILD_ASIL_D_16)
  #undef       WDGM_STOP_SEC_CONFIG_DATA_PREBUILD_ASIL_D_16
  // TEST //#pragma ghs section
/* -------------------------------------------------------------------------- */
/*        Xcp                                                                 */
/* -------------------------------------------------------------------------- */
#elif defined (XCP_START_SEC_VAR_CLEARED_8)
  #undef       XCP_START_SEC_VAR_CLEARED_8
  // TEST //#pragma ghs section bss=".bss.XCP_RAM_VAR_CLEARED_8"
  #pragma alignvar (4)
#elif defined (XCP_STOP_SEC_VAR_CLEARED_8)
  #undef       XCP_STOP_SEC_VAR_CLEARED_8
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (XCP_START_SEC_VAR_CLEARED_16)
  #undef       XCP_START_SEC_VAR_CLEARED_16
  // TEST //#pragma ghs section bss=".bss.XCP_RAM_VAR_CLEARED_16"
  #pragma alignvar (4)
#elif defined (XCP_STOP_SEC_VAR_CLEARED_16)
  #undef       XCP_STOP_SEC_VAR_CLEARED_16
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (XCP_START_SEC_CONST_8)
  #undef       XCP_START_SEC_CONST_8
  // TEST //#pragma ghs section rodata=".rodata.XCP_ROM_CONST_8"
  #pragma alignvar (4)
#elif defined (XCP_STOP_SEC_CONST_8)
  #undef       XCP_STOP_SEC_CONST_8
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (XCP_START_SEC_VAR_CLEARED_32)
  #undef       XCP_START_SEC_VAR_CLEARED_32
  // TEST //#pragma ghs section bss=".bss.XCP_RAM_VAR_CLEARED_32"
  #pragma alignvar (4)
#elif defined (XCP_STOP_SEC_VAR_CLEARED_32)
  #undef       XCP_STOP_SEC_VAR_CLEARED_32
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (XCP_START_SEC_VAR_CLEARED_UNSPECIFIED)
  #undef       XCP_START_SEC_VAR_CLEARED_UNSPECIFIED
  // TEST //#pragma ghs section bss=".bss.XCP_RAM_VAR_CLEARED_UNSPECIFIED"
  #pragma alignvar (4)
#elif defined (XCP_STOP_SEC_VAR_CLEARED_UNSPECIFIED)
  #undef       XCP_STOP_SEC_VAR_CLEARED_UNSPECIFIED
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (XCP_START_SEC_VAR_POWER_ON_CLEARED_BOOLEAN)
  #undef       XCP_START_SEC_VAR_POWER_ON_CLEARED_BOOLEAN
  // TEST //#pragma ghs section bss=".bss.XCP_RAM_VAR_CLEARED_BOOLEAN"
  #pragma alignvar (4)
#elif defined (XCP_STOP_SEC_VAR_POWER_ON_CLEARED_BOOLEAN)
  #undef       XCP_STOP_SEC_VAR_POWER_ON_CLEARED_BOOLEAN
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (XCP_START_SEC_VAR_POWER_ON_CLEARED_UNSPECIFIED)
  #undef       XCP_START_SEC_VAR_POWER_ON_CLEARED_UNSPECIFIED
  // TEST //#pragma ghs section bss=".bss.XCP_RAM_VAR_CLEARED_UNSPECIFIED"
  #pragma alignvar (4)
#elif defined (XCP_STOP_SEC_VAR_POWER_ON_CLEARED_UNSPECIFIED)
  #undef       XCP_STOP_SEC_VAR_POWER_ON_CLEARED_UNSPECIFIED
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (XCP_START_SEC_VAR_NO_INIT_BOOLEAN)
  #undef       XCP_START_SEC_VAR_NO_INIT_BOOLEAN
  // TEST //#pragma ghs section bss=".bss.XCP_RAM_VAR_NO_INIT_BOOLEAN"
  #pragma alignvar (4)
#elif defined (XCP_STOP_SEC_VAR_NO_INIT_BOOLEAN)
  #undef       XCP_STOP_SEC_VAR_NO_INIT_BOOLEAN
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (XCP_START_SEC_VAR_NO_INIT_8)
  #undef       XCP_START_SEC_VAR_NO_INIT_8
  // TEST //#pragma ghs section bss=".bss.XCP_RAM_VAR_NO_INIT_8"
  #pragma alignvar (4)
#elif defined (XCP_STOP_SEC_VAR_NO_INIT_8)
  #undef       XCP_STOP_SEC_VAR_NO_INIT_8
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (XCP_START_SEC_VAR_NO_INIT_32)
  #undef       XCP_START_SEC_VAR_NO_INIT_32
  // TEST //#pragma ghs section bss=".bss.XCP_RAM_VAR_NO_INIT_32"
  #pragma alignvar (4)
#elif defined (XCP_STOP_SEC_VAR_NO_INIT_32)
  #undef       XCP_STOP_SEC_VAR_NO_INIT_32
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (XCP_START_SEC_VAR_NO_INIT_UNSPECIFIED)
  #undef       XCP_START_SEC_VAR_NO_INIT_UNSPECIFIED
  // TEST //#pragma ghs section bss=".bss.XCP_RAM_VAR_NO_INIT_UNSPECIFIED"
  #pragma alignvar (4)
#elif defined (XCP_STOP_SEC_VAR_NO_INIT_UNSPECIFIED)
  #undef       XCP_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (XCP_START_SEC_VAR_CLEARED_BOOLEAN)
  #undef       XCP_START_SEC_VAR_CLEARED_BOOLEAN
  // TEST //#pragma ghs section bss=".bss.XCP_RAM_VAR_CLEARED_BOOLEAN"
  #pragma alignvar (4)
#elif defined (XCP_STOP_SEC_VAR_CLEARED_BOOLEAN)
  #undef       XCP_STOP_SEC_VAR_CLEARED_BOOLEAN
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (XCP_START_SEC_CONST_UNSPECIFIED)
  #undef       XCP_START_SEC_CONST_UNSPECIFIED
  // TEST //#pragma ghs section rodata=".rodata.XCP_ROM_CONST_UNSPECIFIED"
  #pragma alignvar (4)
#elif defined (XCP_STOP_SEC_CONST_UNSPECIFIED)
  #undef       XCP_STOP_SEC_CONST_UNSPECIFIED
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (XCP_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED)
  #undef       XCP_START_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
  // TEST //#pragma ghs section rodata=".rodata.XCP_ROM_CONFIG_UNSPECIFIED"
#elif defined (XCP_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED)
  #undef       XCP_STOP_SEC_CONFIG_DATA_POSTBUILD_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (XCP_START_SEC_CODE)
  #undef       XCP_START_SEC_CODE
  // TEST //#pragma ghs section text=".text.XCP_CODE"
  // TEST //#pragma ghs section rodata=".rodata.XCP_ROM_CONST_UNSPECIFIED"
  // TEST //#pragma ghs section bss=".bss.XCP_RAM_VAR_CLEARED_UNSPECIFIED"
  // TEST //#pragma ghs section data=".data.XCP_RAM_VAR_INIT_UNSPECIFIED"
#elif defined (XCP_STOP_SEC_CODE)
  #undef       XCP_STOP_SEC_CODE
  // TEST //#pragma ghs section
#elif defined (XCP_START_SEC_VAR_POWER_ON_CLEARED_8)
  #undef       XCP_START_SEC_VAR_POWER_ON_CLEARED_8
  // TEST //#pragma ghs section bss=".bss.XCP_RAM_VAR_CLEARED_8"
  #pragma alignvar (4)
#elif defined (XCP_STOP_SEC_VAR_POWER_ON_CLEARED_8)
  #undef       XCP_STOP_SEC_VAR_POWER_ON_CLEARED_8
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (XCP_START_SEC_VAR_CALIBRATION_ROM)
  #undef       XCP_START_SEC_VAR_CALIBRATION_ROM
  #pragma alignvar (4)
  // TEST //#pragma ghs section rodata=".rodata.XCP_ROM_CALIBRATION_ROM"
#elif defined (XCP_STOP_SEC_VAR_CALIBRATION_ROM)
  #undef       XCP_STOP_SEC_VAR_CALIBRATION_ROM
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (XCP_START_SEC_VAR_CALIBRATION_RAM)
  #undef       XCP_START_SEC_VAR_CALIBRATION_RAM
  #pragma alignvar (4)
  // TEST //#pragma ghs section rodata=".rodata.XCP_ROM_CALIBRATION_RAM"
#elif defined (XCP_STOP_SEC_VAR_CALIBRATION_RAM)
  #undef       XCP_STOP_SEC_VAR_CALIBRATION_RAM
  #pragma alignvar (4)
  // TEST //#pragma ghs section
/* -------------------------------------------------------------------------- */
/*                 CoSvAb                                                     */
/* -------------------------------------------------------------------------- */
#elif defined (COSVAB_START_SEC_CODE)
  #undef       COSVAB_START_SEC_CODE
  // TEST //#pragma ghs section text=".text.COSVAB_CODE"
  // TEST //#pragma ghs section rodata=".rodata.COSVAB_ROM_CONST_UNSPECIFIED"
  // TEST //#pragma ghs section bss=".bss.COSVAB_RAM_VAR_CLEARED_UNSPECIFIED"
  // TEST //#pragma ghs section data=".data.COSVAB_RAM_VAR_INIT_UNSPECIFIED"
#elif defined (COSVAB_STOP_SEC_CODE)
  #undef       COSVAB_STOP_SEC_CODE
  // TEST //#pragma ghs section
#elif defined (COSVAB_START_SEC_VAR_INIT_8)
  #undef       COSVAB_START_SEC_VAR_INIT_8
  // TEST //#pragma ghs section data=".data.COSVAB_RAM_VAR_INIT_8"
#elif defined (COSVAB_STOP_SEC_VAR_INIT_8)
  #undef       COSVAB_STOP_SEC_VAR_INIT_8
  // TEST //#pragma ghs section
#elif defined (COSVAB_START_SEC_VAR_CLEARED_32)
  #undef       COSVAB_START_SEC_VAR_CLEARED_32
  // TEST //#pragma ghs section bss=".bss.COSVAB_RAM_VAR_CLEARED_32"
#elif defined (COSVAB_STOP_SEC_VAR_CLEARED_32)
  #undef       COSVAB_STOP_SEC_VAR_CLEARED_32
  // TEST //#pragma ghs section
#elif defined (COSVAB_START_SEC_CONST_32)
  #undef       COSVAB_START_SEC_CONST_32
  // TEST //#pragma ghs section rodata=".rodata.COSVAB_ROM_CONST_32"
#elif defined (COSVAB_STOP_SEC_CONST_32)
  #undef       COSVAB_STOP_SEC_CONST_32
  // TEST //#pragma ghs section
#elif defined (COSVAB_START_SEC_CONST_UNSPECIFIED)
  #undef       COSVAB_START_SEC_CONST_UNSPECIFIED
  // TEST //#pragma ghs section rodata=".rodata.COSVAB_ROM_CONST_UNSPECIFIED"
#elif defined (COSVAB_STOP_SEC_CONST_UNSPECIFIED)
  #undef       COSVAB_STOP_SEC_CONST_UNSPECIFIED
  // TEST //#pragma ghs section
/* -------------------------------------------------------------------------- */
/*                 IoHwAb                                                     */
/* -------------------------------------------------------------------------- */
#elif defined (IOHWAB_START_SEC_CODE)
  #undef       IOHWAB_START_SEC_CODE
  // TEST //#pragma ghs section text=".text.IOHWAB_CODE"
  // TEST //#pragma ghs section rodata=".rodata.IOHWAB_ROM_CONST_UNSPECIFIED"
  // TEST //#pragma ghs section bss=".bss.IOHWAB_RAM_VAR_CLEARED_UNSPECIFIED"
  // TEST //#pragma ghs section data=".data.IOHWAB_RAM_VAR_INIT_UNSPECIFIED"
#elif defined (IOHWAB_STOP_SEC_CODE)
  #undef       IOHWAB_STOP_SEC_CODE
  // TEST //#pragma ghs section
#elif defined (IOHWAB_START_SEC_VAR_CLEARED_8)
  #undef       IOHWAB_START_SEC_VAR_CLEARED_8
  // TEST //#pragma ghs section bss=".bss.IOHWAB_RAM_VAR_CLEARED_8"
#elif defined (IOHWAB_STOP_SEC_VAR_CLEARED_8)
  #undef       IOHWAB_STOP_SEC_VAR_CLEARED_8
  // TEST //#pragma ghs section
#elif defined (IOHWAB_START_SEC_VAR_CLEARED_16)
  #undef       IOHWAB_START_SEC_VAR_CLEARED_16
  // TEST //#pragma ghs section bss=".bss.IOHWAB_RAM_VAR_CLEARED_16"
#elif defined (IOHWAB_STOP_SEC_VAR_CLEARED_16)
  #undef       IOHWAB_STOP_SEC_VAR_CLEARED_16
  // TEST //#pragma ghs section
#elif defined (IOHWAB_START_SEC_VAR_CLEARED_UNSPECIFIED)
  #undef       IOHWAB_START_SEC_VAR_CLEARED_UNSPECIFIED
  // TEST //#pragma ghs section bss=".bss.IOHWAB_RAM_VAR_CLEARED_UNSPECIFIED"
#elif defined (IOHWAB_STOP_SEC_VAR_CLEARED_UNSPECIFIED)
  #undef       IOHWAB_STOP_SEC_VAR_CLEARED_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (IOHWAB_START_SEC_CONST_8)
  #undef       IOHWAB_START_SEC_CONST_8
  // TEST //#pragma ghs section rodata=".rodata.IOHWAB_ROM_CONST_8"
#elif defined (IOHWAB_STOP_SEC_CONST_8)
  #undef       IOHWAB_STOP_SEC_CONST_8
  // TEST //#pragma ghs section
#elif defined (IOHWAB_START_SEC_CONST_16)
  #undef       IOHWAB_START_SEC_CONST_16
  // TEST //#pragma ghs section rodata=".rodata.IOHWAB_ROM_CONST_16"
#elif defined (IOHWAB_STOP_SEC_CONST_16)
  #undef       IOHWAB_STOP_SEC_CONST_16
  // TEST //#pragma ghs section
#elif defined (IOHWAB_START_SEC_CONST_UNSPECIFIED)
  #undef       IOHWAB_START_SEC_CONST_UNSPECIFIED
  // TEST //#pragma ghs section rodata=".rodata.IOHWAB_ROM_CONST_UNSPECIFIED"
#elif defined (IOHWAB_STOP_SEC_CONST_UNSPECIFIED)
  #undef       IOHWAB_STOP_SEC_CONST_UNSPECIFIED
  // TEST //#pragma ghs section
/* -------------------------------------------------------------------------- */
/*                               J1939TP                                      */
/* -------------------------------------------------------------------------- */
#elif defined (J1939TP_START_SEC_VAR_CLEARED_BOOLEAN)
  #undef       J1939TP_START_SEC_VAR_CLEARED_BOOLEAN
  // TEST //#pragma ghs section bss=".bss.J1939TP_RAM_VAR_CLEARED_BOOLEAN"
#elif defined (J1939TP_STOP_SEC_VAR_CLEARED_BOOLEAN)
  #undef       J1939TP_STOP_SEC_VAR_CLEARED_BOOLEAN
  // TEST //#pragma ghs section
#elif defined (J1939TP_START_SEC_VAR_NO_INIT_UNSPECIFIED)
  #undef       J1939TP_START_SEC_VAR_NO_INIT_UNSPECIFIED
  // TEST //#pragma ghs section bss=".bss.J1939TP_RAM_VAR_NO_INIT_UNSPECIFIED"
#elif defined (J1939TP_STOP_SEC_VAR_NO_INIT_UNSPECIFIED)
  #undef       J1939TP_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (J1939TP_START_SEC_CONST_8)
  #undef       J1939TP_START_SEC_CONST_8
  // TEST //#pragma ghs section rodata=".rodata.J1939TP_ROM_CONST_8"
#elif defined (J1939TP_STOP_SEC_CONST_8)
  #undef       J1939TP_STOP_SEC_CONST_8
  // TEST //#pragma ghs section
#elif defined (J1939TP_START_SEC_CONST_16)
  #undef       J1939TP_START_SEC_CONST_16
  // TEST //#pragma ghs section rodata=".rodata.J1939TP_ROM_CONST_16"
#elif defined (J1939TP_STOP_SEC_CONST_16)
  #undef       J1939TP_STOP_SEC_CONST_16
  // TEST //#pragma ghs section
#elif defined (J1939TP_START_SEC_CONST_UNSPECIFIED)
  #undef       J1939TP_START_SEC_CONST_UNSPECIFIED
  // TEST //#pragma ghs section rodata=".rodata.J1939TP_ROM_CONST_UNSPECIFIED"
#elif defined (J1939TP_STOP_SEC_CONST_UNSPECIFIED)
  #undef       J1939TP_STOP_SEC_CONST_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (J1939TP_START_SEC_CODE)
  #undef       J1939TP_START_SEC_CODE
  // TEST //#pragma ghs section text=".text.J1939TP_CODE"
  // TEST //#pragma ghs section rodata=".rodata.J1939TP_ROM_CONST_UNSPECIFIED"
  // TEST //#pragma ghs section bss=".bss.J1939TP_RAM_VAR_CLEARED_UNSPECIFIED"
  // TEST //#pragma ghs section data=".data.J1939TP_RAM_VAR_INIT_UNSPECIFIED"
#elif defined (J1939TP_STOP_SEC_CODE)
  #undef       J1939TP_STOP_SEC_CODE
  // TEST //#pragma ghs section
/* -------------------------------------------------------------------------- */
/*                               J1939Rm                                      */
/* -------------------------------------------------------------------------- */
#elif defined (J1939RM_START_SEC_VAR_NO_INIT_8)
  #undef       J1939RM_START_SEC_VAR_NO_INIT_8
  // TEST //#pragma ghs section bss=".bss.J1939RM_RAM_VAR_NO_INIT_8"
#elif defined (J1939RM_STOP_SEC_VAR_NO_INIT_8)
  #undef       J1939RM_STOP_SEC_VAR_NO_INIT_8
  // TEST //#pragma ghs section
#elif defined (J1939RM_START_SEC_VAR_NO_INIT_UNSPECIFIED)
  #undef       J1939RM_START_SEC_VAR_NO_INIT_UNSPECIFIED
  // TEST //#pragma ghs section bss=".bss.J1939RM_RAM_VAR_NO_INIT_UNSPECIFIED"
#elif defined (J1939RM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED)
  #undef       J1939RM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (J1939RM_START_SEC_VAR_CLEARED_BOOLEAN)
  #undef       J1939RM_START_SEC_VAR_CLEARED_BOOLEAN
  // TEST //#pragma ghs section bss=".bss.J1939RM_RAM_VAR_CLEARED_BOOLEAN"
#elif defined (J1939RM_STOP_SEC_VAR_CLEARED_BOOLEAN)
  #undef       J1939RM_STOP_SEC_VAR_CLEARED_BOOLEAN
  // TEST //#pragma ghs section
#elif defined (J1939RM_START_SEC_VAR_CLEARED_8)
  #undef       J1939RM_START_SEC_VAR_CLEARED_8
  // TEST //#pragma ghs section bss=".bss.J1939RM_RAM_VAR_CLEARED_8"
#elif defined (J1939RM_STOP_SEC_VAR_CLEARED_8)
  #undef       J1939RM_STOP_SEC_VAR_CLEARED_8
  // TEST //#pragma ghs section
#elif defined (J1939RM_START_SEC_VAR_CLEARED_16)
  #undef       J1939RM_START_SEC_VAR_CLEARED_16
  // TEST //#pragma ghs section bss=".bss.J1939RM_RAM_VAR_CLEARED_16"
#elif defined (J1939RM_STOP_SEC_VAR_CLEARED_16)
  #undef       J1939RM_STOP_SEC_VAR_CLEARED_16
  // TEST //#pragma ghs section
#elif defined (J1939RM_START_SEC_VAR_INIT_8)
  #undef       J1939RM_START_SEC_VAR_INIT_8
  // TEST //#pragma ghs section data=".data.J1939RM_RAM_VAR_INIT_8"
#elif defined (J1939RM_STOP_SEC_VAR_INIT_8)
  #undef       J1939RM_STOP_SEC_VAR_INIT_8
  // TEST //#pragma ghs section
#elif defined (J1939RM_START_SEC_VAR_INIT_32)
  #undef       J1939RM_START_SEC_VAR_INIT_32
  // TEST //#pragma ghs section data=".data.J1939RM_RAM_VAR_INIT_32"
#elif defined (J1939RM_STOP_SEC_VAR_INIT_32)
  #undef       J1939RM_STOP_SEC_VAR_INIT_32
  // TEST //#pragma ghs section
#elif defined (J1939RM_START_SEC_VAR_INIT_UNSPECIFIED)
  #undef       J1939RM_START_SEC_VAR_INIT_UNSPECIFIED
  // TEST //#pragma ghs section data=".data.J1939RM_RAM_VAR_INIT_UNSPECIFIED"
#elif defined (J1939RM_STOP_SEC_VAR_INIT_UNSPECIFIED)
  #undef       J1939RM_STOP_SEC_VAR_INIT_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (J1939RM_START_SEC_CONST_8)
  #undef       J1939RM_START_SEC_CONST_8
  // TEST //#pragma ghs section rodata=".rodata.J1939RM_ROM_CONST_8"
#elif defined (J1939RM_STOP_SEC_CONST_8)
  #undef       J1939RM_STOP_SEC_CONST_8
  // TEST //#pragma ghs section
#elif defined (J1939RM_START_SEC_CONST_UNSPECIFIED)
  #undef       J1939RM_START_SEC_CONST_UNSPECIFIED
  // TEST //#pragma ghs section rodata=".rodata.J1939RM_ROM_CONST_UNSPECIFIED"
#elif defined (J1939RM_STOP_SEC_CONST_UNSPECIFIED)
  #undef       J1939RM_STOP_SEC_CONST_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (J1939RM_START_SEC_CODE)
  #undef       J1939RM_START_SEC_CODE
  // TEST //#pragma ghs section text=".text.J1939RM_CODE"
  // TEST //#pragma ghs section rodata=".rodata.J1939RM_ROM_CONST_UNSPECIFIED"
  // TEST //#pragma ghs section bss=".bss.J1939RM_RAM_VAR_CLEARED_UNSPECIFIED"
  // TEST //#pragma ghs section data=".data.J1939RM_RAM_VAR_INIT_UNSPECIFIED"
#elif defined (J1939RM_STOP_SEC_CODE)
  #undef       J1939RM_STOP_SEC_CODE
  // TEST //#pragma ghs section
#elif defined (J1939RM_START_SEC_DBTOC_CONFIG_CONST_UNSPECIFIED)
  #undef       J1939RM_START_SEC_DBTOC_CONFIG_CONST_UNSPECIFIED
  // TEST //#pragma ghs section rodata=".rodata.J1939RM_ROM_CONFIG_UNSPECIFIED"
#elif defined (J1939RM_STOP_SEC_DBTOC_CONFIG_CONST_UNSPECIFIED)
  #undef       J1939RM_STOP_SEC_DBTOC_CONFIG_CONST_UNSPECIFIED
  // TEST //#pragma ghs section
/* -------------------------------------------------------------------------- */
/*                               J1939Nm                                      */
/* -------------------------------------------------------------------------- */
#elif defined (J1939NM_START_SEC_VAR_CLEARED_BOOLEAN)
  #undef       J1939NM_START_SEC_VAR_CLEARED_BOOLEAN
  // TEST //#pragma ghs section bss=".bss.J1939NM_RAM_VAR_CLEARED_BOOLEAN"
  #pragma alignvar (1)
#elif defined (J1939NM_STOP_SEC_VAR_CLEARED_BOOLEAN)
  #undef       J1939NM_STOP_SEC_VAR_CLEARED_BOOLEAN
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (J1939NM_START_SEC_VAR_CLEARED_8)
  #undef       J1939NM_START_SEC_VAR_CLEARED_8
  // TEST //#pragma ghs section bss=".bss.J1939NM_RAM_VAR_CLEARED_8"
  #pragma alignvar (1)
#elif defined (J1939NM_STOP_SEC_VAR_CLEARED_8)
  #undef       J1939NM_STOP_SEC_VAR_CLEARED_8
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (J1939NM_START_SEC_VAR_CLEARED_UNSPECIFIED)
  #undef       J1939NM_START_SEC_VAR_CLEARED_UNSPECIFIED
  // TEST //#pragma ghs section bss=".bss.J1939NM_RAM_VAR_CLEARED_UNSPECIFIED"
  #pragma alignvar (4)
#elif defined (J1939NM_STOP_SEC_VAR_CLEARED_UNSPECIFIED)
  #undef       J1939NM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (J1939NM_START_SEC_VAR_NO_INIT_8)
  #undef       J1939NM_START_SEC_VAR_NO_INIT_8
  // TEST //#pragma ghs section bss=".bss.J1939NM_RAM_VAR_NO_INIT_8"
  #pragma alignvar (1)
#elif defined (J1939NM_STOP_SEC_VAR_NO_INIT_8)
  #undef       J1939NM_STOP_SEC_VAR_NO_INIT_8
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (J1939NM_START_SEC_VAR_NO_INIT_16)
  #undef       J1939NM_START_SEC_VAR_NO_INIT_16
  // TEST //#pragma ghs section bss=".bss.J1939NM_RAM_VAR_NO_INIT_16"
  #pragma alignvar (1)
#elif defined (J1939NM_STOP_SEC_VAR_NO_INIT_16)
  #undef       J1939NM_STOP_SEC_VAR_NO_INIT_16
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (J1939NM_START_SEC_VAR_NO_INIT_32)
  #undef       J1939NM_START_SEC_VAR_NO_INIT_32
  // TEST //#pragma ghs section bss=".bss.J1939NM_RAM_VAR_NO_INIT_32"
  #pragma alignvar (4)
#elif defined (J1939NM_STOP_SEC_VAR_NO_INIT_32)
  #undef       J1939NM_STOP_SEC_VAR_NO_INIT_32
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (J1939NM_START_SEC_VAR_NO_INIT_UNSPECIFIED)
  #undef       J1939NM_START_SEC_VAR_NO_INIT_UNSPECIFIED
  // TEST //#pragma ghs section bss=".bss.J1939NM_RAM_VAR_NO_INIT_UNSPECIFIED"
  #pragma alignvar (4)
#elif defined (J1939NM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED)
  #undef       J1939NM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (J1939NM_START_SEC_VAR_INIT_UNSPECIFIED)
  #undef       J1939NM_START_SEC_VAR_INIT_UNSPECIFIED
  // TEST //#pragma ghs section data=".data.J1939NM_RAM_VAR_INIT_UNSPECIFIED"
  #pragma alignvar (4)
#elif defined (J1939NM_STOP_SEC_VAR_INIT_UNSPECIFIED)
  #undef       J1939NM_STOP_SEC_VAR_INIT_UNSPECIFIED
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (J1939NM_START_SEC_CONST_BOOLEAN)
  #undef       J1939NM_START_SEC_CONST_BOOLEAN
  // TEST //#pragma ghs section rodata=".rodata.J1939NM_ROM_CONST_BOOLEAN"
  #pragma alignvar (1)
#elif defined (J1939NM_STOP_SEC_CONST_BOOLEAN)
  #undef       J1939NM_STOP_SEC_CONST_BOOLEAN
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (J1939NM_START_SEC_CONST_8)
  #undef       J1939NM_START_SEC_CONST_8
  // TEST //#pragma ghs section rodata=".rodata.J1939NM_ROM_CONST_8"
  #pragma alignvar (1)
#elif defined (J1939NM_STOP_SEC_CONST_8)
  #undef       J1939NM_STOP_SEC_CONST_8
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (J1939NM_START_SEC_CONST_16)
  #undef       J1939NM_START_SEC_CONST_16
  // TEST //#pragma ghs section rodata=".rodata.J1939NM_ROM_CONST_16"
  #pragma alignvar (1)
#elif defined (J1939NM_STOP_SEC_CONST_16)
  #undef       J1939NM_STOP_SEC_CONST_16
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (J1939NM_START_SEC_CONST_UNSPECIFIED)
  #undef       J1939NM_START_SEC_CONST_UNSPECIFIED
  // TEST //#pragma ghs section rodata=".rodata.J1939NM_ROM_CONST_UNSPECIFIED"
  #pragma alignvar (4)
#elif defined (J1939NM_STOP_SEC_CONST_UNSPECIFIED)
  #undef       J1939NM_STOP_SEC_CONST_UNSPECIFIED
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (J1939NM_START_SEC_CODE)
  #undef       J1939NM_START_SEC_CODE
  // TEST //#pragma ghs section text=".text.J1939NM_CODE"
  // TEST //#pragma ghs section rodata=".rodata.J1939NM_ROM_CONST_UNSPECIFIED"
  // TEST //#pragma ghs section bss=".bss.J1939NM_RAM_VAR_CLEARED_UNSPECIFIED"
  // TEST //#pragma ghs section data=".data.J1939NM_RAM_VAR_INIT_UNSPECIFIED"
#elif defined (J1939NM_STOP_SEC_CODE)
  #undef       J1939NM_STOP_SEC_CODE
  // TEST //#pragma ghs section
/* -------------------------------------------------------------------------- */
/*                               J1939Dcm                                     */
/* -------------------------------------------------------------------------- */
#elif defined (J1939DCM_START_SEC_VAR_CLEARED_BOOLEAN)
  #undef       J1939DCM_START_SEC_VAR_CLEARED_BOOLEAN
  // TEST //#pragma ghs section bss=".bss.J1939DCM_RAM_VAR_CLEARED_BOOLEAN"
#elif defined (J1939DCM_STOP_SEC_VAR_CLEARED_BOOLEAN)
  #undef       J1939DCM_STOP_SEC_VAR_CLEARED_BOOLEAN
  // TEST //#pragma ghs section
#elif defined (J1939DCM_START_SEC_VAR_NO_INIT_8)
  #undef       J1939DCM_START_SEC_VAR_NO_INIT_8
  // TEST //#pragma ghs section bss=".bss.J1939DCM_RAM_VAR_NO_INIT_8"
#elif defined (J1939DCM_STOP_SEC_VAR_NO_INIT_8)
  #undef       J1939DCM_STOP_SEC_VAR_NO_INIT_8
  // TEST //#pragma ghs section
#elif defined (J1939DCM_START_SEC_VAR_NO_INIT_32)
  #undef       J1939DCM_START_SEC_VAR_NO_INIT_32
  // TEST //#pragma ghs section bss=".bss.J1939DCM_RAM_VAR_NO_INIT_32"
#elif defined (J1939DCM_STOP_SEC_VAR_NO_INIT_32)
  #undef       J1939DCM_STOP_SEC_VAR_NO_INIT_32
  // TEST //#pragma ghs section
#elif defined (J1939DCM_START_SEC_VAR_NO_INIT_UNSPECIFIED)
  #undef       J1939DCM_START_SEC_VAR_NO_INIT_UNSPECIFIED
  // TEST //#pragma ghs section bss=".bss.J1939DCM_RAM_VAR_NO_INIT_UNSPECIFIED"
#elif defined (J1939DCM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED)
  #undef       J1939DCM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (J1939DCM_START_SEC_VAR_INIT_UNSPECIFIED)
  #undef       J1939DCM_START_SEC_VAR_INIT_UNSPECIFIED
  // TEST //#pragma ghs section data=".data.J1939DCM_RAM_VAR_INIT_UNSPECIFIED"
#elif defined (J1939DCM_STOP_SEC_VAR_INIT_UNSPECIFIED)
  #undef       J1939DCM_STOP_SEC_VAR_INIT_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (J1939DCM_START_SEC_CONST_INIT_UNSPECIFIED)
  #undef       J1939DCM_START_SEC_CONST_INIT_UNSPECIFIED
  // TEST //#pragma ghs section rodata=".rodata.J1939DCM_ROM_CONST_INIT_UNSPECIFIED"
#elif defined (J1939DCM_STOP_SEC_CONST_INIT_UNSPECIFIED)
  #undef       J1939DCM_STOP_SEC_CONST_INIT_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (J1939DCM_START_SEC_CONST_8)
  #undef       J1939DCM_START_SEC_CONST_8
  // TEST //#pragma ghs section rodata=".rodata.J1939DCM_ROM_CONST_8"
#elif defined (J1939DCM_STOP_SEC_CONST_8)
  #undef       J1939DCM_STOP_SEC_CONST_8
  // TEST //#pragma ghs section
#elif defined (J1939DCM_START_SEC_CONST_32)
  #undef       J1939DCM_START_SEC_CONST_32
  // TEST //#pragma ghs section rodata=".rodata.J1939DCM_ROM_CONST_32"
#elif defined (J1939DCM_STOP_SEC_CONST_32)
  #undef       J1939DCM_STOP_SEC_CONST_32
  // TEST //#pragma ghs section
#elif defined (J1939DCM_START_SEC_CONST_UNSPECIFIED)
  #undef       J1939DCM_START_SEC_CONST_UNSPECIFIED
  // TEST //#pragma ghs section rodata=".rodata.J1939DCM_ROM_CONST_UNSPECIFIED"
#elif defined (J1939DCM_STOP_SEC_CONST_UNSPECIFIED)
  #undef       J1939DCM_STOP_SEC_CONST_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (J1939DCM_START_SEC_CODE)
  #undef       J1939DCM_START_SEC_CODE
  // TEST //#pragma ghs section text=".text.J1939DCM_CODE"
  // TEST //#pragma ghs section rodata=".rodata.J1939DCM_ROM_CONST_UNSPECIFIED"
  // TEST //#pragma ghs section bss=".bss.J1939DCM_RAM_VAR_CLEARED_UNSPECIFIED"
  // TEST //#pragma ghs section data=".data.J1939DCM_RAM_VAR_INIT_UNSPECIFIED"
#elif defined (J1939DCM_STOP_SEC_CODE)
  #undef       J1939DCM_STOP_SEC_CODE
  // TEST //#pragma ghs section
/* -------------------------------------------------------------------------- */
/*                              OS Profiler                                   */
/* -------------------------------------------------------------------------- */
#elif defined (OPF_START_SEC_VAR_NO_INIT_BOOLEAN)
  #undef       OPF_START_SEC_VAR_NO_INIT_BOOLEAN
  // TEST //#pragma ghs section bss=".bss.OPF_RAM_VAR_NO_INIT_BOOLEAN"
#elif defined (OPF_STOP_SEC_VAR_NO_INIT_BOOLEAN)
  #undef       OPF_STOP_SEC_VAR_NO_INIT_BOOLEAN
  // TEST //#pragma ghs section
#elif defined (OPF_START_SEC_VAR_NO_INIT_8)
  #undef       OPF_START_SEC_VAR_NO_INIT_8
  // TEST //#pragma ghs section bss=".bss.OPF_RAM_VAR_NO_INIT_8"
#elif defined (OPF_STOP_SEC_VAR_NO_INIT_8)
  #undef       OPF_STOP_SEC_VAR_NO_INIT_8
  // TEST //#pragma ghs section
#elif defined (OPF_START_SEC_VAR_NO_INIT_16)
  #undef       OPF_START_SEC_VAR_NO_INIT_16
  // TEST //#pragma ghs section bss=".bss.OPF_RAM_VAR_NO_INIT_16"
#elif defined (OPF_STOP_SEC_VAR_NO_INIT_16)
  #undef       OPF_STOP_SEC_VAR_NO_INIT_16
  // TEST //#pragma ghs section
#elif defined (OPF_START_SEC_VAR_NO_INIT_32)
  #undef       OPF_START_SEC_VAR_NO_INIT_32
  // TEST //#pragma ghs section bss=".bss.OPF_RAM_VAR_NO_INIT_32"
  #pragma alignvar (4)
#elif defined (OPF_STOP_SEC_VAR_NO_INIT_32)
  #undef       OPF_STOP_SEC_VAR_NO_INIT_32
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (OPF_START_SEC_VAR_NO_INIT_UNSPECIFIED)
  #undef       OPF_START_SEC_VAR_NO_INIT_UNSPECIFIED
  // TEST //#pragma ghs section bss=".bss.OPF_RAM_VAR_NO_INIT_UNSPECIFIED"
#elif defined (OPF_STOP_SEC_VAR_NO_INIT_UNSPECIFIED)
  #undef       OPF_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (OPF_START_SEC_VAR_CLEARED_BOOLEAN)
  #undef       OPF_START_SEC_VAR_CLEARED_BOOLEAN
  // TEST //#pragma ghs section bss=".bss.OPF_RAM_VAR_CLEARED_BOOLEAN"
#elif defined (OPF_STOP_SEC_VAR_CLEARED_BOOLEAN)
  #undef       OPF_STOP_SEC_VAR_CLEARED_BOOLEAN
  // TEST //#pragma ghs section
#elif defined (OPF_START_SEC_VAR_CLEARED_8)
  #undef       OPF_START_SEC_VAR_CLEARED_8
  // TEST //#pragma ghs section bss=".bss.OPF_RAM_VAR_CLEARED_8"
#elif defined (OPF_STOP_SEC_VAR_CLEARED_8)
  #undef       OPF_STOP_SEC_VAR_CLEARED_8
  // TEST //#pragma ghs section
#elif defined (OPF_START_SEC_VAR_CLEARED_16)
  #undef       OPF_START_SEC_VAR_CLEARED_16
  // TEST //#pragma ghs section bss=".bss.OPF_RAM_VAR_CLEARED_16"
#elif defined (OPF_STOP_SEC_VAR_CLEARED_16)
  #undef       OPF_STOP_SEC_VAR_CLEARED_16
  // TEST //#pragma ghs section
#elif defined (OPF_START_SEC_VAR_CLEARED_32)
  #undef       OPF_START_SEC_VAR_CLEARED_32
  // TEST //#pragma ghs section bss=".bss.OPF_RAM_VAR_CLEARED_32"
  #pragma alignvar (4)
#elif defined (OPF_STOP_SEC_VAR_CLEARED_32)
  #undef       OPF_STOP_SEC_VAR_CLEARED_32
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (OPF_START_SEC_VAR_CLEARED_UNSPECIFIED)
  #undef       OPF_START_SEC_VAR_CLEARED_UNSPECIFIED
  // TEST //#pragma ghs section bss=".bss.OPF_RAM_VAR_CLEARED_UNSPECIFIED"
#elif defined (OPF_STOP_SEC_VAR_CLEARED_UNSPECIFIED)
  #undef       OPF_STOP_SEC_VAR_CLEARED_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (OPF_START_CORE1_SEC_VAR_CLEARED_BOOLEAN)
  #undef       OPF_START_CORE1_SEC_VAR_CLEARED_BOOLEAN
  // TEST //#pragma ghs section bss=".bss.OPF_RAM_CORE1_VAR_CLEARED_BOOLEAN"
#elif defined (OPF_STOP_CORE1_SEC_VAR_CLEARED_BOOLEAN)
  #undef       OPF_STOP_CORE1_SEC_VAR_CLEARED_BOOLEAN
  // TEST //#pragma ghs section
#elif defined (OPF_START_CORE1_SEC_VAR_CLEARED_8)
  #undef       OPF_START_CORE1_SEC_VAR_CLEARED_8
  // TEST //#pragma ghs section bss=".bss.OPF_RAM_CORE1_VAR_CLEARED_8"
#elif defined (OPF_STOP_CORE1_SEC_VAR_CLEARED_8)
  #undef       OPF_STOP_CORE1_SEC_VAR_CLEARED_8
  // TEST //#pragma ghs section
#elif defined (OPF_START_CORE1_SEC_VAR_CLEARED_16)
  #undef       OPF_START_CORE1_SEC_VAR_CLEARED_16
  // TEST //#pragma ghs section bss=".bss.OPF_RAM_CORE1_VAR_CLEARED_16"
#elif defined (OPF_STOP_CORE1_SEC_VAR_CLEARED_16)
  #undef       OPF_STOP_CORE1_SEC_VAR_CLEARED_16
  // TEST //#pragma ghs section
#elif defined (OPF_START_CORE1_SEC_VAR_CLEARED_32)
  #undef       OPF_START_CORE1_SEC_VAR_CLEARED_32
  // TEST //#pragma ghs section bss=".bss.OPF_RAM_CORE1_VAR_CLEARED_32"
  #pragma alignvar (4)
#elif defined (OPF_STOP_CORE1_SEC_VAR_CLEARED_32)
  #undef       OPF_STOP_CORE1_SEC_VAR_CLEARED_32
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (OPF_START_CORE1_SEC_VAR_CLEARED_UNSPECIFIED)
  #undef       OPF_START_CORE1_SEC_VAR_CLEARED_UNSPECIFIED
  // TEST //#pragma ghs section bss=".bss.OPF_RAM_CORE1_VAR_CLEARED_UNSPECIFIED"
#elif defined (OPF_STOP_CORE1_SEC_VAR_CLEARED_UNSPECIFIED)
  #undef       OPF_STOP_CORE1_SEC_VAR_CLEARED_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (OPF_START_CORE2_SEC_VAR_CLEARED_BOOLEAN)
  #undef       OPF_START_CORE2_SEC_VAR_CLEARED_BOOLEAN
  // TEST //#pragma ghs section bss=".bss.OPF_RAM_CORE2_VAR_CLEARED_BOOLEAN"
#elif defined (OPF_STOP_CORE2_SEC_VAR_CLEARED_BOOLEAN)
  #undef       OPF_STOP_CORE2_SEC_VAR_CLEARED_BOOLEAN
  // TEST //#pragma ghs section
#elif defined (OPF_START_CORE2_SEC_VAR_CLEARED_8)
  #undef       OPF_START_CORE2_SEC_VAR_CLEARED_8
  // TEST //#pragma ghs section bss=".bss.OPF_RAM_CORE2_VAR_CLEARED_8"
#elif defined (OPF_STOP_CORE2_SEC_VAR_CLEARED_8)
  #undef       OPF_STOP_CORE2_SEC_VAR_CLEARED_8
  // TEST //#pragma ghs section
#elif defined (OPF_START_CORE2_SEC_VAR_CLEARED_16)
  #undef       OPF_START_CORE2_SEC_VAR_CLEARED_16
  // TEST //#pragma ghs section bss=".bss.OPF_RAM_CORE2_VAR_CLEARED_16"
#elif defined (OPF_STOP_CORE2_SEC_VAR_CLEARED_16)
  #undef       OPF_STOP_CORE2_SEC_VAR_CLEARED_16
  // TEST //#pragma ghs section
#elif defined (OPF_START_CORE2_SEC_VAR_CLEARED_32)
  #undef       OPF_START_CORE2_SEC_VAR_CLEARED_32
  // TEST //#pragma ghs section bss=".bss.OPF_RAM_CORE2_VAR_CLEARED_32"
  #pragma alignvar (4)
#elif defined (OPF_STOP_CORE2_SEC_VAR_CLEARED_32)
  #undef       OPF_STOP_CORE2_SEC_VAR_CLEARED_32
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (OPF_START_CORE2_SEC_VAR_CLEARED_UNSPECIFIED)
  #undef       OPF_START_CORE2_SEC_VAR_CLEARED_UNSPECIFIED
  // TEST //#pragma ghs section bss=".bss.OPF_RAM_CORE2_VAR_CLEARED_UNSPECIFIED"
#elif defined (OPF_STOP_CORE2_SEC_VAR_CLEARED_UNSPECIFIED)
  #undef       OPF_STOP_CORE2_SEC_VAR_CLEARED_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (OPF_START_SEC_VAR_INIT_BOOLEAN)
  #undef       OPF_START_SEC_VAR_INIT_BOOLEAN
  // TEST //#pragma ghs section data=".data.OPF_RAM_VAR_INIT_BOOLEAN"
#elif defined (OPF_STOP_SEC_VAR_INIT_BOOLEAN)
  #undef       OPF_STOP_SEC_VAR_INIT_BOOLEAN
  // TEST //#pragma ghs section
#elif defined (OPF_START_SEC_VAR_INIT_8)
  #undef       OPF_START_SEC_VAR_INIT_8
  // TEST //#pragma ghs section data=".data.OPF_RAM_VAR_INIT_8"
#elif defined (OPF_STOP_SEC_VAR_INIT_8)
  #undef       OPF_STOP_SEC_VAR_INIT_8
  // TEST //#pragma ghs section
#elif defined (OPF_START_SEC_VAR_INIT_16)
  #undef       OPF_START_SEC_VAR_INIT_16

  // TEST //#pragma ghs section data=".data.OPF_RAM_VAR_INIT_16"
#elif defined (OPF_STOP_SEC_VAR_INIT_16)
  #undef       OPF_STOP_SEC_VAR_INIT_16
  // TEST //#pragma ghs section
#elif defined (OPF_START_SEC_VAR_INIT_32)
  #undef       OPF_START_SEC_VAR_INIT_32
  // TEST //#pragma ghs section data=".data.OPF_RAM_VAR_INIT_32"
  #pragma alignvar (4)
#elif defined (OPF_STOP_SEC_VAR_INIT_32)
  #undef       OPF_STOP_SEC_VAR_INIT_32
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (OPF_START_SEC_VAR_INIT_UNSPECIFIED)
  #undef       OPF_START_SEC_VAR_INIT_UNSPECIFIED
  // TEST //#pragma ghs section data=".data.OPF_RAM_VAR_INIT_UNSPECIFIED"
#elif defined (OPF_STOP_SEC_VAR_INIT_UNSPECIFIED)
  #undef       OPF_STOP_SEC_VAR_INIT_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (OPF_START_SEC_CONST_BOOLEAN)
  #undef       OPF_START_SEC_CONST_BOOLEAN
  // TEST //#pragma ghs section rodata=".rodata.OPF_ROM_CONST_BOOLEAN"
#elif defined (OPF_STOP_SEC_CONST_BOOLEAN)
  #undef       OPF_STOP_SEC_CONST_BOOLEAN
  // TEST //#pragma ghs section
#elif defined (OPF_START_SEC_CONST_8)
  #undef       OPF_START_SEC_CONST_8
  // TEST //#pragma ghs section rodata=".rodata.OPF_ROM_CONST_8"
#elif defined (OPF_STOP_SEC_CONST_8)
  #undef       OPF_STOP_SEC_CONST_8
  // TEST //#pragma ghs section
#elif defined (OPF_START_SEC_CONST_16)
  #undef       OPF_START_SEC_CONST_16
  // TEST //#pragma ghs section rodata=".rodata.OPF_ROM_CONST_16"
#elif defined (OPF_STOP_SEC_CONST_16)
  #undef       OPF_STOP_SEC_CONST_16
  // TEST //#pragma ghs section
#elif defined (OPF_START_SEC_CONST_32)
  #undef       OPF_START_SEC_CONST_32
  // TEST //#pragma ghs section rodata=".rodata.OPF_ROM_CONST_32"
  #pragma alignvar (4)
#elif defined (OPF_STOP_SEC_CONST_32)
  #undef       OPF_STOP_SEC_CONST_32
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (OPF_START_SEC_CONST_UNSPECIFIED)
  #undef       OPF_START_SEC_CONST_UNSPECIFIED
  // TEST //#pragma ghs section rodata=".rodata.OPF_ROM_CONST_UNSPECIFIED"
#elif defined (OPF_STOP_SEC_CONST_UNSPECIFIED)
  #undef       OPF_STOP_SEC_CONST_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (OPF_START_SEC_CODE)
  #undef       OPF_START_SEC_CODE
  // TEST //#pragma ghs section text=".text.OPF_CODE"
  // TEST //#pragma ghs section rodata=".rodata.OPF_ROM_CONST_UNSPECIFIED"
  // TEST //#pragma ghs section bss=".bss.OPF_RAM_VAR_CLEARED_UNSPECIFIED"
  // TEST //#pragma ghs section data=".data.OPF_RAM_VAR_INIT_UNSPECIFIED"
#elif defined (OPF_STOP_SEC_CODE)
  #undef       OPF_STOP_SEC_CODE
  // TEST //#pragma ghs section
/* -------------------------------------------------------------------------- */
/*                             OS Profiler CDD                                */
/* -------------------------------------------------------------------------- */
#elif defined (OSPROFILERCDD_START_SEC_VAR_NO_INIT_BOOLEAN)
  #undef       OSPROFILERCDD_START_SEC_VAR_NO_INIT_BOOLEAN
  // TEST //#pragma ghs section bss=".bss.DEFAULT_RAM_VAR_NO_INIT"
#elif defined (OSPROFILERCDD_STOP_SEC_VAR_NO_INIT_BOOLEAN)
  #undef       OSPROFILERCDD_STOP_SEC_VAR_NO_INIT_BOOLEAN
  // TEST //#pragma ghs section
#elif defined (OSPROFILERCDD_START_SEC_VAR_NO_INIT_8)
  #undef       OSPROFILERCDD_START_SEC_VAR_NO_INIT_8
  // TEST //#pragma ghs section bss=".bss.DEFAULT_RAM_VAR_NO_INIT"
#elif defined (OSPROFILERCDD_STOP_SEC_VAR_NO_INIT_8)
  #undef       OSPROFILERCDD_STOP_SEC_VAR_NO_INIT_8
  // TEST //#pragma ghs section
#elif defined (OSPROFILERCDD_START_SEC_VAR_NO_INIT_16)
  #undef       OSPROFILERCDD_START_SEC_VAR_NO_INIT_16
  // TEST //#pragma ghs section bss=".bss.DEFAULT_RAM_VAR_NO_INIT"
#elif defined (OSPROFILERCDD_STOP_SEC_VAR_NO_INIT_16)
  #undef       OSPROFILERCDD_STOP_SEC_VAR_NO_INIT_16
  // TEST //#pragma ghs section
#elif defined (OSPROFILERCDD_START_SEC_VAR_NO_INIT_32)
  #undef       OSPROFILERCDD_START_SEC_VAR_NO_INIT_32
  // TEST //#pragma ghs section bss=".bss.DEFAULT_RAM_VAR_NO_INIT"
#elif defined (OSPROFILERCDD_STOP_SEC_VAR_NO_INIT_32)
  #undef       OSPROFILERCDD_STOP_SEC_VAR_NO_INIT_32
  // TEST //#pragma ghs section
#elif defined (OSPROFILERCDD_START_SEC_VAR_NO_INIT_UNSPECIFIED)
  #undef       OSPROFILERCDD_START_SEC_VAR_NO_INIT_UNSPECIFIED
  // TEST //#pragma ghs section bss=".bss.DEFAULT_RAM_VAR_NO_INIT"
#elif defined (OSPROFILERCDD_STOP_SEC_VAR_NO_INIT_UNSPECIFIED)
  #undef       OSPROFILERCDD_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (OSPROFILERCDD_START_SEC_VAR_CLEARED_BOOLEAN)
  #undef       OSPROFILERCDD_START_SEC_VAR_CLEARED_BOOLEAN
  // TEST //#pragma ghs section bss=".bss.DEFAULT_RAM_VAR_CLEARED"
#elif defined (OSPROFILERCDD_STOP_SEC_VAR_CLEARED_BOOLEAN)
  #undef       OSPROFILERCDD_STOP_SEC_VAR_CLEARED_BOOLEAN
  // TEST //#pragma ghs section
#elif defined (OSPROFILERCDD_START_SEC_VAR_CLEARED_8)
  #undef       OSPROFILERCDD_START_SEC_VAR_CLEARED_8
  // TEST //#pragma ghs section bss=".bss.DEFAULT_RAM_VAR_CLEARED"
#elif defined (OSPROFILERCDD_STOP_SEC_VAR_CLEARED_8)
  #undef       OSPROFILERCDD_STOP_SEC_VAR_CLEARED_8
  // TEST //#pragma ghs section
#elif defined (OSPROFILERCDD_START_SEC_VAR_CLEARED_16)
  #undef       OSPROFILERCDD_START_SEC_VAR_CLEARED_16
  // TEST //#pragma ghs section bss=".bss.DEFAULT_RAM_VAR_CLEARED"
#elif defined (OSPROFILERCDD_STOP_SEC_VAR_CLEARED_16)
  #undef       OSPROFILERCDD_STOP_SEC_VAR_CLEARED_16
  // TEST //#pragma ghs section
#elif defined (OSPROFILERCDD_START_SEC_VAR_CLEARED_32)
  #undef       OSPROFILERCDD_START_SEC_VAR_CLEARED_32
  // TEST //#pragma ghs section bss=".bss.DEFAULT_RAM_VAR_CLEARED"
#elif defined (OSPROFILERCDD_STOP_SEC_VAR_CLEARED_32)
  #undef       OSPROFILERCDD_STOP_SEC_VAR_CLEARED_32
  // TEST //#pragma ghs section
#elif defined (OSPROFILERCDD_START_SEC_VAR_CLEARED_UNSPECIFIED)
  #undef       OSPROFILERCDD_START_SEC_VAR_CLEARED_UNSPECIFIED
  // TEST //#pragma ghs section bss=".bss.DEFAULT_RAM_VAR_CLEARED"
#elif defined (OSPROFILERCDD_STOP_SEC_VAR_CLEARED_UNSPECIFIED)
  #undef       OSPROFILERCDD_STOP_SEC_VAR_CLEARED_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (OSPROFILERCDD_START_SEC_VAR_INIT_BOOLEAN)
  #undef       OSPROFILERCDD_START_SEC_VAR_INIT_BOOLEAN
  // TEST //#pragma ghs section data=".data.DEFAULT_RAM_VAR_INIT"
#elif defined (OSPROFILERCDD_STOP_SEC_VAR_INIT_BOOLEAN)
  #undef       OSPROFILERCDD_STOP_SEC_VAR_INIT_BOOLEAN
  // TEST //#pragma ghs section
#elif defined (OSPROFILERCDD_START_SEC_VAR_INIT_8)
  #undef       OSPROFILERCDD_START_SEC_VAR_INIT_8
  // TEST //#pragma ghs section data=".data.DEFAULT_RAM_VAR_INIT"
#elif defined (OSPROFILERCDD_STOP_SEC_VAR_INIT_8)
  #undef       OSPROFILERCDD_STOP_SEC_VAR_INIT_8
  // TEST //#pragma ghs section
#elif defined (OSPROFILERCDD_START_SEC_VAR_INIT_16)
  #undef       OSPROFILERCDD_START_SEC_VAR_INIT_16
  // TEST //#pragma ghs section data=".data.DEFAULT_RAM_VAR_INIT"
#elif defined (OSPROFILERCDD_STOP_SEC_VAR_INIT_16)
  #undef       OSPROFILERCDD_STOP_SEC_VAR_INIT_16
  // TEST //#pragma ghs section
#elif defined (OSPROFILERCDD_START_SEC_VAR_INIT_32)
  #undef       OSPROFILERCDD_START_SEC_VAR_INIT_32
  // TEST //#pragma ghs section data=".data.DEFAULT_RAM_VAR_INIT"
#elif defined (OSPROFILERCDD_STOP_SEC_VAR_INIT_32)
  #undef       OSPROFILERCDD_STOP_SEC_VAR_INIT_32
  // TEST //#pragma ghs section
#elif defined (OSPROFILERCDD_START_SEC_VAR_INIT_UNSPECIFIED)
  #undef       OSPROFILERCDD_START_SEC_VAR_INIT_UNSPECIFIED
  // TEST //#pragma ghs section data=".data.DEFAULT_RAM_VAR_INIT"
#elif defined (OSPROFILERCDD_STOP_SEC_VAR_INIT_UNSPECIFIED)
  #undef       OSPROFILERCDD_STOP_SEC_VAR_INIT_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (OSPROFILERCDD_START_SEC_CONST_BOOLEAN)
  #undef       OSPROFILERCDD_START_SEC_CONST_BOOLEAN
  // TEST //#pragma ghs section rodata=".rodata.DEFAULT_ROM_CONST"
#elif defined (OSPROFILERCDD_STOP_SEC_CONST_BOOLEAN)
  #undef       OSPROFILERCDD_STOP_SEC_CONST_BOOLEAN
  // TEST //#pragma ghs section
#elif defined (OSPROFILERCDD_START_SEC_CONST_8)
  #undef       OSPROFILERCDD_START_SEC_CONST_8
  // TEST //#pragma ghs section rodata=".rodata.DEFAULT_ROM_CONST"
#elif defined (OSPROFILERCDD_STOP_SEC_CONST_8)
  #undef       OSPROFILERCDD_STOP_SEC_CONST_8
  // TEST //#pragma ghs section
#elif defined (OSPROFILERCDD_START_SEC_CONST_16)
  #undef       OSPROFILERCDD_START_SEC_CONST_16
  // TEST //#pragma ghs section rodata=".rodata.DEFAULT_ROM_CONST"
#elif defined (OSPROFILERCDD_STOP_SEC_CONST_16)
  #undef       OSPROFILERCDD_STOP_SEC_CONST_16
  // TEST //#pragma ghs section
#elif defined (OSPROFILERCDD_START_SEC_CONST_32)
  #undef       OSPROFILERCDD_START_SEC_CONST_32
  // TEST //#pragma ghs section rodata=".rodata.DEFAULT_ROM_CONST"
#elif defined (OSPROFILERCDD_STOP_SEC_CONST_32)
  #undef       OSPROFILERCDD_STOP_SEC_CONST_32
  // TEST //#pragma ghs section
#elif defined (OSPROFILERCDD_START_SEC_CONST_UNSPECIFIED)
  #undef       OSPROFILERCDD_START_SEC_CONST_UNSPECIFIED
  // TEST //#pragma ghs section rodata=".rodata.DEFAULT_ROM_CONST"
#elif defined (OSPROFILERCDD_STOP_SEC_CONST_UNSPECIFIED)
  #undef       OSPROFILERCDD_STOP_SEC_CONST_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (OSPROFILERCDD_START_SEC_CODE)
  #undef       OSPROFILERCDD_START_SEC_CODE
  // TEST //#pragma ghs section text=".text.DEFAULT_CODE"
  // TEST //#pragma ghs section rodata=".rodata.DEFAULT_ROM_CONST"
  // TEST //#pragma ghs section bss=".bss.DEFAULT_RAM_VAR_CLEARED"
  // TEST //#pragma ghs section data=".data.DEFAULT_RAM_VAR_INIT"
#elif defined (OSPROFILERCDD_STOP_SEC_CODE)
  #undef       OSPROFILERCDD_STOP_SEC_CODE
  // TEST //#pragma ghs section
/* -------------------------------------------------------------------------- */
/*                                 RamTst                                     */
/* -------------------------------------------------------------------------- */
#elif defined (RAMTST_START_SEC_CODE)
  #undef       RAMTST_START_SEC_CODE
  // TEST //#pragma ghs section text=".text.DEFAULT_CODE"
  // TEST //#pragma ghs section rodata=".rodata.DEFAULT_ROM_CONST"
  // TEST //#pragma ghs section bss=".bss.DEFAULT_RAM_VAR_CLEARED"
  // TEST //#pragma ghs section data=".data.DEFAULT_RAM_VAR_INIT"
#elif defined (RAMTST_STOP_SEC_CODE)
  #undef       RAMTST_STOP_SEC_CODE
  // TEST //#pragma ghs section
#elif defined (RAMTST_START_SEC_VAR_CLEARED_BOOLEAN)
  #undef       RAMTST_START_SEC_VAR_CLEARED_BOOLEAN
  // TEST //#pragma ghs section bss=".bss.DEFAULT_RAM_VAR_CLEARED"
#elif defined (RAMTST_STOP_SEC_VAR_CLEARED_BOOLEAN)
  #undef       RAMTST_STOP_SEC_VAR_CLEARED_BOOLEAN
  // TEST //#pragma ghs section
#elif defined (RAMTST_START_SEC_VAR_CLEARED_UNSPECIFIED)
  #undef       RAMTST_START_SEC_VAR_CLEARED_UNSPECIFIED
  // TEST //#pragma ghs section bss=".bss.DEFAULT_RAM_VAR_CLEARED"
#elif defined (RAMTST_STOP_SEC_VAR_CLEARED_UNSPECIFIED)
  #undef       RAMTST_STOP_SEC_VAR_CLEARED_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (RAMTST_START_SEC_CONST_UNSPECIFIED)
  #undef       RAMTST_START_SEC_CONST_UNSPECIFIED
  // TEST //#pragma ghs section rodata=".rodata.DEFAULT_ROM_CONST"
#elif defined (RAMTST_STOP_SEC_CONST_UNSPECIFIED)
  #undef       RAMTST_STOP_SEC_CONST_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (RAMTST_START_SEC_VAR_CLEARED_8)
  #undef      RAMTST_START_SEC_VAR_CLEARED_8
  // TEST //#pragma ghs section bss=".bss.DEFAULT_RAM_VAR_CLEARED"
#elif defined (RAMTST_STOP_SEC_VAR_CLEARED_8)
  #undef      RAMTST_STOP_SEC_VAR_CLEARED_8
  // TEST //#pragma ghs section
/* -------------------------------------------------------------------------- */
/*                 ETHIF                                                      */
/* -------------------------------------------------------------------------- */
#elif defined (ETHIF_START_SEC_CODE)
  #undef       ETHIF_START_SEC_CODE
  // TEST //#pragma ghs section text=".text.ETHIF_CODE"
  // TEST //#pragma ghs section rodata=".rodata.ETHIF_ROM_CONST_UNSPECIFIED"
  // TEST //#pragma ghs section bss=".bss.ETHIF_RAM_VAR_CLEARED_UNSPECIFIED"
  // TEST //#pragma ghs section data=".data.ETHIF_RAM_VAR_INIT_UNSPECIFIED"
#elif defined (ETHIF_STOP_SEC_CODE)
  #undef       ETHIF_STOP_SEC_CODE
  // TEST //#pragma ghs section
#elif defined (ETHIF_START_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED)
  #undef       ETHIF_START_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
  // TEST //#pragma ghs section rodata=".rodata.ETHIF_ROM_CONFIG_CONST_PREBUILD_UNSPECIFIED"
#elif defined (ETHIF_STOP_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED)
  #undef       ETHIF_STOP_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (ETHIF_START_SEC_VAR_CLEARED_8)
  #undef       ETHIF_START_SEC_VAR_CLEARED_8
  // TEST //#pragma ghs section bss=".bss.ETHIF_RAM_VAR_CLEARED_8"
  #pragma alignvar (1)
#elif defined (ETHIF_STOP_SEC_VAR_CLEARED_8)
  #undef       ETHIF_STOP_SEC_VAR_CLEARED_8
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (ETHIF_START_SEC_VAR_CLEARED_16)
  #undef       ETHIF_START_SEC_VAR_CLEARED_16
  // TEST //#pragma ghs section bss=".bss.ETHIF_RAM_VAR_CLEARED_16"
  #pragma alignvar (1)
#elif defined (ETHIF_STOP_SEC_VAR_CLEARED_16)
  #undef       ETHIF_STOP_SEC_VAR_CLEARED_16
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (ETHIF_START_SEC_VAR_CLEARED_32)
  #undef       ETHIF_START_SEC_VAR_CLEARED_32
  // TEST //#pragma ghs section bss=".bss.ETHIF_RAM_VAR_CLEARED_32"
  #pragma alignvar (4)
#elif defined (ETHIF_STOP_SEC_VAR_CLEARED_32)
  #undef       ETHIF_STOP_SEC_VAR_CLEARED_32
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (ETHIF_START_SEC_VAR_CLEARED_UNSPECIFIED)
  #undef       ETHIF_START_SEC_VAR_CLEARED_UNSPECIFIED
  // TEST //#pragma ghs section bss=".bss.ETHIF_RAM_VAR_CLEARED_UNSPECIFIED"
  #pragma alignvar (4)
#elif defined (ETHIF_STOP_SEC_VAR_CLEARED_UNSPECIFIED)
  #undef       ETHIF_STOP_SEC_VAR_CLEARED_UNSPECIFIED
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (ETHIF_START_SEC_VAR_INIT_UNSPECIFIED)
  #undef       ETHIF_START_SEC_VAR_INIT_UNSPECIFIED
  // TEST //#pragma ghs section data=".data.ETHIF_RAM_VAR_INIT_UNSPECIFIED"
  #pragma alignvar (4)
#elif defined (ETHIF_STOP_SEC_VAR_INIT_UNSPECIFIED)
  #undef       ETHIF_STOP_SEC_VAR_INIT_UNSPECIFIED
  #pragma alignvar (4)
  // TEST //#pragma ghs section
/* -------------------------------------------------------------------------- */
/*                 ETHSM                                                      */
/* -------------------------------------------------------------------------- */
#elif defined (ETHSM_START_SEC_CODE)
  #undef       ETHSM_START_SEC_CODE
  // TEST //#pragma ghs section text=".text.ETHSM_CODE"
  // TEST //#pragma ghs section rodata=".rodata.ETHSM_ROM_CONST_UNSPECIFIED"
  // TEST //#pragma ghs section bss=".bss.ETHSM_RAM_VAR_CLEARED_UNSPECIFIED"
  // TEST //#pragma ghs section data=".data.ETHSM_RAM_VAR_INIT_UNSPECIFIED"
#elif defined (ETHSM_STOP_SEC_CODE)
  #undef       ETHSM_STOP_SEC_CODE
  // TEST //#pragma ghs section
#elif defined (ETHSM_START_SEC_VAR_INIT_BOOLEAN)
  #undef       ETHSM_START_SEC_VAR_INIT_BOOLEAN
  // TEST //#pragma ghs section data=".data.ETHSM_RAM_VAR_INIT_BOOLEAN"
  #pragma alignvar (1)
#elif defined (ETHSM_STOP_SEC_VAR_INIT_BOOLEAN)
  #undef       ETHSM_STOP_SEC_VAR_INIT_BOOLEAN
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (ETHSM_START_SEC_VAR_CLEARED_UNSPECIFIED)
  #undef       ETHSM_START_SEC_VAR_CLEARED_UNSPECIFIED
  // TEST //#pragma ghs section bss=".bss.ETHSM_RAM_VAR_CLEARED_UNSPECIFIED"
  #pragma alignvar (4)
#elif defined (ETHSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED)
  #undef       ETHSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (ETHSM_START_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED)
  #undef       ETHSM_START_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
  // TEST //#pragma ghs section rodata=".rodata.ETHSM_ROM_CONFIG_CONST_PREBUILD_UNSPECIFIED"
#elif defined (ETHSM_STOP_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED)
  #undef       ETHSM_STOP_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (ETHSM_START_SEC_CONFIG_DATA_PREBUILD_8)
  #undef       ETHSM_START_SEC_CONFIG_DATA_PREBUILD_8
  // TEST //#pragma ghs section rodata=".rodata.ETHSM_ROM_CONFIG_CONST_PREBUILD_8"
#elif defined (ETHSM_STOP_SEC_CONFIG_DATA_PREBUILD_8)
  #undef       ETHSM_STOP_SEC_CONFIG_DATA_PREBUILD_8
  // TEST //#pragma ghs section
#elif defined (ETHSM_START_SEC_CONST_UNSPECIFIED)
  #undef       ETHSM_START_SEC_CONST_UNSPECIFIED
  // TEST //#pragma ghs section rodata=".rodata.ETHSM_ROM_CONST_UNSPECIFIED"
  #pragma alignvar (4)
#elif defined (ETHSM_STOP_SEC_CONST_UNSPECIFIED)
  #undef       ETHSM_STOP_SEC_CONST_UNSPECIFIED
  #pragma alignvar (4)
  // TEST //#pragma ghs section
/* -------------------------------------------------------------------------- */
/*                 ETHTRCV                                                    */
/* -------------------------------------------------------------------------- */
#elif defined (ETHTRCV_START_SEC_CODE)
  #undef      ETHTRCV_START_SEC_CODE
  // TEST //#pragma ghs section text=".text.ETHTRCV_CODE"
  // TEST //#pragma ghs section rodata=".rodata.ETHTRCV_ROM_CONST_UNSPECIFIED"
  // TEST //#pragma ghs section bss=".bss.ETHTRCV_RAM_VAR_CLEARED_UNSPECIFIED"
  // TEST //#pragma ghs section data=".data.ETHTRCV_RAM_VAR_INIT_UNSPECIFIED"
#elif defined (ETHTRCV_STOP_SEC_CODE)
  #undef      ETHTRCV_STOP_SEC_CODE
  // TEST //#pragma ghs section
/* -------------------------------------------------------------------------- */
/*                                ETHTRCV_PEF7071                                     */
/* -------------------------------------------------------------------------- */
#elif defined (ETHTRCV_PEF7071_START_SEC_CALLOUT_CODE)
  #undef       ETHTRCV_PEF7071_START_SEC_CALLOUT_CODE
  // TEST //#pragma ghs section text=".text.ETHTRCV_PEF7071_CODE"
  // TEST //#pragma ghs section rodata=".rodata.ETHTRCV_PEF7071_ROM_CONST_UNSPECIFIED"
  // TEST //#pragma ghs section bss=".bss.ETHTRCV_PEF7071_RAM_VAR_CLEARED_UNSPECIFIED"
  // TEST //#pragma ghs section data=".data.ETHTRCV_PEF7071_RAM_VAR_INIT_UNSPECIFIED"
#elif defined (ETHTRCV_PEF7071_STOP_SEC_CALLOUT_CODE)
  #undef       ETHTRCV_PEF7071_STOP_SEC_CALLOUT_CODE
  // TEST //#pragma ghs section
#elif defined (ETHTRCV_PEF7071_START_SEC_CODE)
  #undef       ETHTRCV_PEF7071_START_SEC_CODE
  // TEST //#pragma ghs section text=".text.ETHTRCV_PEF7071_CODE"
  // TEST //#pragma ghs section rodata=".rodata.ETHTRCV_PEF7071_ROM_CONST_UNSPECIFIED"
  // TEST //#pragma ghs section bss=".bss.ETHTRCV_PEF7071_RAM_VAR_CLEARED_UNSPECIFIED"
  // TEST //#pragma ghs section data=".data.ETHTRCV_PEF7071_RAM_VAR_INIT_UNSPECIFIED"
#elif defined (ETHTRCV_PEF7071_STOP_SEC_CODE)
  #undef       ETHTRCV_PEF7071_STOP_SEC_CODE
  // TEST //#pragma ghs section
#elif defined (ETHTRCV_PEF7071_START_SEC_VAR_CLEARED_UNSPECIFIED)
  #undef       ETHTRCV_PEF7071_START_SEC_VAR_CLEARED_UNSPECIFIED
  // TEST //#pragma ghs section bss=".bss.ETHTRCV_PEF7071_RAM_VAR_CLEARED_UNSPECIFIED"
  #pragma alignvar (4)
#elif defined (ETHTRCV_PEF7071_STOP_SEC_VAR_CLEARED_UNSPECIFIED)
  #undef       ETHTRCV_PEF7071_STOP_SEC_VAR_CLEARED_UNSPECIFIED
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (ETHTRCV_PEF7071_START_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED)
  #undef       ETHTRCV_PEF7071_START_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
  // TEST //#pragma ghs section rodata=".rodata.ETHTRCV_PEF7071_ROM_CONFIG_CONST_PREBUILD_UNSPECIFIED"
#elif defined (ETHTRCV_PEF7071_STOP_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED)
  #undef       ETHTRCV_PEF7071_STOP_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
  // TEST //#pragma ghs section
/* -------------------------------------------------------------------------- */
/*                                ETHTRCV_BCM89811                                     */
/* -------------------------------------------------------------------------- */
#elif defined (ETHTRCV_BCM89811_START_SEC_CALLOUT_CODE)
  #undef       ETHTRCV_BCM89811_START_SEC_CALLOUT_CODE
  // TEST //#pragma ghs section text=".text.ETHTRCV_BCM89811_CODE"
  // TEST //#pragma ghs section rodata=".rodata.ETHTRCV_BCM89811_ROM_CONST_UNSPECIFIED"
  // TEST //#pragma ghs section bss=".bss.ETHTRCV_BCM89811_RAM_VAR_CLEARED_UNSPECIFIED"
  // TEST //#pragma ghs section data=".data.ETHTRCV_BCM89811_RAM_VAR_INIT_UNSPECIFIED"
#elif defined (ETHTRCV_BCM89811_STOP_SEC_CALLOUT_CODE)
  #undef       ETHTRCV_BCM89811_STOP_SEC_CALLOUT_CODE
  // TEST //#pragma ghs section
#elif defined (ETHTRCV_BCM89811_START_SEC_CODE)
  #undef       ETHTRCV_BCM89811_START_SEC_CODE
  // TEST //#pragma ghs section text=".text.ETHTRCV_BCM89811_CODE"
  // TEST //#pragma ghs section rodata=".rodata.ETHTRCV_BCM89811_ROM_CONST_UNSPECIFIED"
  // TEST //#pragma ghs section bss=".bss.ETHTRCV_BCM89811_RAM_VAR_CLEARED_UNSPECIFIED"
  // TEST //#pragma ghs section data=".data.ETHTRCV_BCM89811_RAM_VAR_INIT_UNSPECIFIED"
#elif defined (ETHTRCV_BCM89811_STOP_SEC_CODE)
  #undef       ETHTRCV_BCM89811_STOP_SEC_CODE
  // TEST //#pragma ghs section
#elif defined (ETHTRCV_BCM89811_START_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED)
  #undef       ETHTRCV_BCM89811_START_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
  // TEST //#pragma ghs section rodata=".rodata.ETHTRCV_BCM89811_ROM_CONFIG_CONST_PREBUILD_UNSPECIFIED"
#elif defined (ETHTRCV_BCM89811_STOP_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED)
  #undef       ETHTRCV_BCM89811_STOP_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (ETHTRCV_BCM89811_START_SEC_VAR_CLEARED_UNSPECIFIED)
  #undef       ETHTRCV_BCM89811_START_SEC_VAR_CLEARED_UNSPECIFIED
  // TEST //#pragma ghs section bss=".bss.ETHTRCV_BCM89811_RAM_VAR_CLEARED_UNSPECIFIED"
  #pragma alignvar (4)
#elif defined (ETHTRCV_BCM89811_STOP_SEC_VAR_CLEARED_UNSPECIFIED)
  #undef       ETHTRCV_BCM89811_STOP_SEC_VAR_CLEARED_UNSPECIFIED
  #pragma alignvar (4)
  // TEST //#pragma ghs section
/* -------------------------------------------------------------------------- */
/*                 ETHSWT                                                    */
/* -------------------------------------------------------------------------- */
#elif defined (ETHSWT_START_SEC_CODE)
  #undef      ETHSWT_START_SEC_CODE
  // TEST //#pragma ghs section text=".text.ETHSWT_CODE"
  // TEST //#pragma ghs section rodata=".rodata.ETHSWT_ROM_CONST_UNSPECIFIED"
  // TEST //#pragma ghs section bss=".bss.ETHSWT_RAM_VAR_CLEARED_UNSPECIFIED"
  // TEST //#pragma ghs section data=".data.ETHSWT_RAM_VAR_INIT_UNSPECIFIED"
#elif defined (ETHSWT_STOP_SEC_CODE)
  #undef      ETHSWT_STOP_SEC_CODE
  // TEST //#pragma ghs section
#elif defined (ETHSWT_BCM89531_START_SEC_CODE)
  #undef      ETHSWT_BCM89531_START_SEC_CODE
  // TEST //#pragma ghs section text=".text.ETHSWT_CODE"
  // TEST //#pragma ghs section rodata=".rodata.ETHSWT_ROM_CONST_UNSPECIFIED"
  // TEST //#pragma ghs section bss=".bss.ETHSWT_RAM_VAR_CLEARED_UNSPECIFIED"
  // TEST //#pragma ghs section data=".data.ETHSWT_RAM_VAR_INIT_UNSPECIFIED"
#elif defined (ETHSWT_BCM89531_STOP_SEC_CODE)
  #undef      ETHSWT_BCM89531_STOP_SEC_CODE
  // TEST //#pragma ghs section
#elif defined (ETHSWT_BCM89531_START_SEC_CONST_UNSPECIFIED)
  #undef      ETHSWT_BCM89531_START_SEC_CONST_UNSPECIFIED
  // TEST //#pragma ghs section rodata=".rodata.ETHSWT_ROM_CONST_UNSPECIFIED"
#elif defined (ETHSWT_BCM89531_STOP_SEC_CONST_UNSPECIFIED)
  #undef      ETHSWT_BCM89531_STOP_SEC_CONST_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (ETHSWT_BCM89531_START_SEC_VAR_CLEARED_UNSPECIFIED)
  #undef      ETHSWT_BCM89531_START_SEC_VAR_CLEARED_UNSPECIFIED
  // TEST //#pragma ghs section bss=".bss.ETHSWT_RAM_VAR_CLEARED_UNSPECIFIED"
#elif defined (ETHSWT_BCM89531_STOP_SEC_VAR_CLEARED_UNSPECIFIED)
  #undef      ETHSWT_BCM89531_STOP_SEC_VAR_CLEARED_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (ETHSWT_BCM89531_START_SEC_VAR_NO_INIT_UNSPECIFIED)
  #undef      ETHSWT_BCM89531_START_SEC_VAR_NO_INIT_UNSPECIFIED
  // TEST //#pragma ghs section bss=".bss.ETHSWT_RAM_VAR_NO_INIT_UNSPECIFIED"
#elif defined (ETHSWT_BCM89531_STOP_SEC_VAR_NO_INIT_UNSPECIFIED)
  #undef      ETHSWT_BCM89531_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
  // TEST //#pragma ghs section
/* -------------------------------------------------------------------------- */
/*                                SOAD                                     */
/* -------------------------------------------------------------------------- */
#elif defined (SOAD_START_SEC_CODE)
  #undef       SOAD_START_SEC_CODE
  // TEST //#pragma ghs section text=".text.SOAD_CODE"
  // TEST //#pragma ghs section rodata=".rodata.SOAD_ROM_CONST_UNSPECIFIED"
  // TEST //#pragma ghs section bss=".bss.SOAD_RAM_VAR_CLEARED_UNSPECIFIED"
  // TEST //#pragma ghs section data=".data.SOAD_RAM_VAR_INIT_UNSPECIFIED"
#elif defined (SOAD_STOP_SEC_CODE)
  #undef       SOAD_STOP_SEC_CODE
  // TEST //#pragma ghs section
#elif defined (SOAD_START_SEC_VAR_CLEARED_BOOLEAN)
  #undef       SOAD_START_SEC_VAR_CLEARED_BOOLEAN
  // TEST //#pragma ghs section bss=".bss.SOAD_RAM_VAR_CLEARED_BOOLEAN"
  #pragma alignvar (1)
#elif defined (SOAD_STOP_SEC_VAR_CLEARED_BOOLEAN)
  #undef       SOAD_STOP_SEC_VAR_CLEARED_BOOLEAN
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (SOAD_START_SEC_VAR_CLEARED_8)
  #undef       SOAD_START_SEC_VAR_CLEARED_8
  // TEST //#pragma ghs section bss=".bss.SOAD_RAM_VAR_CLEARED_8"
  #pragma alignvar (1)
#elif defined (SOAD_STOP_SEC_VAR_CLEARED_8)
  #undef       SOAD_STOP_SEC_VAR_CLEARED_8
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (SOAD_START_SEC_VAR_CLEARED_16)
  #undef       SOAD_START_SEC_VAR_CLEARED_16
  // TEST //#pragma ghs section bss=".bss.SOAD_RAM_VAR_CLEARED_16"
  #pragma alignvar (1)
#elif defined (SOAD_STOP_SEC_VAR_CLEARED_16)
  #undef       SOAD_STOP_SEC_VAR_CLEARED_16
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (SOAD_START_SEC_VAR_CLEARED_UNSPECIFIED)
  #undef       SOAD_START_SEC_VAR_CLEARED_UNSPECIFIED
  // TEST //#pragma ghs section bss=".bss.SOAD_RAM_VAR_CLEARED_UNSPECIFIED"
  #pragma alignvar (4)
#elif defined (SOAD_STOP_SEC_VAR_CLEARED_UNSPECIFIED)
  #undef       SOAD_STOP_SEC_VAR_CLEARED_UNSPECIFIED
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (SOAD_START_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED)
  #undef       SOAD_START_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
  // TEST //#pragma ghs section rodata=".rodata.SOAD_ROM_CONFIG_CONST_PREBUILD_UNSPECIFIED"
#elif defined (SOAD_STOP_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED)
  #undef       SOAD_STOP_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
  // TEST //#pragma ghs section
/* -------------------------------------------------------------------------- */
/*                                SOMEIPTP                                     */
/* -------------------------------------------------------------------------- */
#elif defined (SOMEIPTP_START_SEC_CODE)
  #undef       SOMEIPTP_START_SEC_CODE
  // TEST //#pragma ghs section text=".text.SOMEIPTP_CODE"
  // TEST //#pragma ghs section rodata=".rodata.SOMEIPTP_ROM_CONST_UNSPECIFIED"
  // TEST //#pragma ghs section bss=".bss.SOMEIPTP_RAM_VAR_CLEARED_UNSPECIFIED"
  // TEST //#pragma ghs section data=".data.SOMEIPTP_RAM_VAR_INIT_UNSPECIFIED"
#elif defined (SOMEIPTP_STOP_SEC_CODE)
  #undef       SOMEIPTP_STOP_SEC_CODE
  // TEST //#pragma ghs section
#elif defined (SOMEIPTP_START_SEC_VAR_CLEARED_UNSPECIFIED)
  #undef       SOMEIPTP_START_SEC_VAR_CLEARED_UNSPECIFIED
  // TEST //#pragma ghs section bss=".bss.SOMEIPTP_RAM_VAR_CLEARED_UNSPECIFIED"
  #pragma alignvar (4)
#elif defined (SOMEIPTP_STOP_SEC_VAR_CLEARED_UNSPECIFIED)
  #undef       SOMEIPTP_STOP_SEC_VAR_CLEARED_UNSPECIFIED
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (SOMEIPTP_START_SEC_VAR_INIT_BOOLEAN)
  #undef       SOMEIPTP_START_SEC_VAR_INIT_BOOLEAN
  // TEST //#pragma ghs section data=".data.SOMEIPTP_RAM_VAR_INIT_BOOLEAN"
  #pragma alignvar (1)
#elif defined (SOMEIPTP_STOP_SEC_VAR_INIT_BOOLEAN)
  #undef       SOMEIPTP_STOP_SEC_VAR_INIT_BOOLEAN
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (SOMEIPTP_START_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED)
  #undef       SOMEIPTP_START_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
  // TEST //#pragma ghs section rodata=".rodata.SOMEIPTP_ROM_CONFIG_CONST_PREBUILD_UNSPECIFIED"
#elif defined (SOMEIPTP_STOP_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED)
  #undef       SOMEIPTP_STOP_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
  // TEST //#pragma ghs section
/* -------------------------------------------------------------------------- */
/*                                DOIP                                     */
/* -------------------------------------------------------------------------- */
#elif defined (DOIP_START_SEC_CODE)
  #undef       DOIP_START_SEC_CODE
  // TEST //#pragma ghs section text=".text.DOIP_CODE"
  // TEST //#pragma ghs section rodata=".rodata.DOIP_ROM_CONST_UNSPECIFIED"
  // TEST //#pragma ghs section bss=".bss.DOIP_RAM_VAR_CLEARED_UNSPECIFIED"
  // TEST //#pragma ghs section data=".data.DOIP_RAM_VAR_INIT_UNSPECIFIED"
#elif defined (DOIP_STOP_SEC_CODE)
  #undef       DOIP_STOP_SEC_CODE
  // TEST //#pragma ghs section
#elif defined (DOIP_START_SEC_CONFIG_DATA_PREBUILD_8)
  #undef       DOIP_START_SEC_CONFIG_DATA_PREBUILD_8
  // TEST //#pragma ghs section rodata=".rodata.DOIP_ROM_CONFIG_CONST_PREBUILD_8"
#elif defined (DOIP_STOP_SEC_CONFIG_DATA_PREBUILD_8)
  #undef       DOIP_STOP_SEC_CONFIG_DATA_PREBUILD_8
  // TEST //#pragma ghs section
#elif defined (DOIP_START_SEC_CONFIG_DATA_PREBUILD_16)
  #undef       DOIP_START_SEC_CONFIG_DATA_PREBUILD_16
  // TEST //#pragma ghs section rodata=".rodata.DOIP_ROM_CONFIG_CONST_PREBUILD_16"
#elif defined (DOIP_STOP_SEC_CONFIG_DATA_PREBUILD_16)
  #undef       DOIP_STOP_SEC_CONFIG_DATA_PREBUILD_16
  // TEST //#pragma ghs section
#elif defined (DOIP_START_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED)
  #undef       DOIP_START_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
  // TEST //#pragma ghs section rodata=".rodata.DOIP_ROM_CONFIG_CONST_PREBUILD_UNSPECIFIED"
#elif defined (DOIP_STOP_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED)
  #undef       DOIP_STOP_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (DOIP_START_SEC_VAR_CLEARED_BOOLEAN)
  #undef       DOIP_START_SEC_VAR_CLEARED_BOOLEAN
  // TEST //#pragma ghs section bss=".bss.DOIP_RAM_VAR_CLEARED_BOOLEAN"
  #pragma alignvar (1)
#elif defined (DOIP_STOP_SEC_VAR_CLEARED_BOOLEAN)
  #undef       DOIP_STOP_SEC_VAR_CLEARED_BOOLEAN
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (DOIP_START_SEC_VAR_CLEARED_UNSPECIFIED)
  #undef       DOIP_START_SEC_VAR_CLEARED_UNSPECIFIED
  // TEST //#pragma ghs section bss=".bss.DOIP_RAM_VAR_CLEARED_UNSPECIFIED"
  #pragma alignvar (4)
#elif defined (DOIP_STOP_SEC_VAR_CLEARED_UNSPECIFIED)
  #undef       DOIP_STOP_SEC_VAR_CLEARED_UNSPECIFIED
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (DOIP_START_SEC_VAR_INIT_UNSPECIFIED)
  #undef       DOIP_START_SEC_VAR_INIT_UNSPECIFIED
  // TEST //#pragma ghs section data=".data.DOIP_RAM_VAR_INIT_UNSPECIFIED"
  #pragma alignvar (4)
#elif defined (DOIP_STOP_SEC_VAR_INIT_UNSPECIFIED)
  #undef       DOIP_STOP_SEC_VAR_INIT_UNSPECIFIED
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (DOIP_START_SEC_VAR_NO_INIT_8)
  #undef       DOIP_START_SEC_VAR_NO_INIT_8
  // TEST //#pragma ghs section bss=".bss.DOIP_RAM_VAR_NO_INIT_8"
  #pragma alignvar (1)
#elif defined (DOIP_STOP_SEC_VAR_NO_INIT_8)
  #undef       DOIP_STOP_SEC_VAR_NO_INIT_8
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (DOIP_START_SEC_VAR_NO_INIT_16)
  #undef       DOIP_START_SEC_VAR_NO_INIT_16
  // TEST //#pragma ghs section bss=".bss.DOIP_RAM_VAR_NO_INIT_16"
  #pragma alignvar (1)
#elif defined (DOIP_STOP_SEC_VAR_NO_INIT_16)
  #undef       DOIP_STOP_SEC_VAR_NO_INIT_16
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (DOIP_START_SEC_VAR_NO_INIT_UNSPECIFIED)
  #undef       DOIP_START_SEC_VAR_NO_INIT_UNSPECIFIED
  // TEST //#pragma ghs section bss=".bss.DOIP_RAM_VAR_NO_INIT_UNSPECIFIED"
  #pragma alignvar (4)
#elif defined (DOIP_STOP_SEC_VAR_NO_INIT_UNSPECIFIED)
  #undef       DOIP_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
  #pragma alignvar (4)
  // TEST //#pragma ghs section
/* -------------------------------------------------------------------------- */
/*                                UDPNM                                     */
/* -------------------------------------------------------------------------- */
#elif defined (UDPNM_START_SEC_CODE)
  #undef       UDPNM_START_SEC_CODE
  // TEST //#pragma ghs section text=".text.UDPNM_CODE"
  // TEST //#pragma ghs section rodata=".rodata.UDPNM_ROM_CONST_UNSPECIFIED"
  // TEST //#pragma ghs section bss=".bss.UDPNM_RAM_VAR_CLEARED_UNSPECIFIED"
  // TEST //#pragma ghs section data=".data.UDPNM_RAM_VAR_INIT_UNSPECIFIED"
#elif defined (UDPNM_STOP_SEC_CODE)
  #undef       UDPNM_STOP_SEC_CODE
  // TEST //#pragma ghs section
#elif defined (UDPNM_START_SEC_VAR_CLEARED_BOOLEAN)
  #undef       UDPNM_START_SEC_VAR_CLEARED_BOOLEAN
  // TEST //#pragma ghs section bss=".bss.UDPNM_RAM_VAR_CLEARED_BOOLEAN"
  #pragma alignvar (1)
#elif defined (UDPNM_STOP_SEC_VAR_CLEARED_BOOLEAN)
  #undef       UDPNM_STOP_SEC_VAR_CLEARED_BOOLEAN
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (UDPNM_START_SEC_VAR_NO_INIT_8)
  #undef       UDPNM_START_SEC_VAR_NO_INIT_8
  // TEST //#pragma ghs section bss=".bss.UDPNM_RAM_VAR_NO_INIT_8"
  #pragma alignvar (1)
#elif defined (UDPNM_STOP_SEC_VAR_NO_INIT_8)
  #undef       UDPNM_STOP_SEC_VAR_NO_INIT_8
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (UDPNM_START_SEC_VAR_NO_INIT_UNSPECIFIED)
  #undef       UDPNM_START_SEC_VAR_NO_INIT_UNSPECIFIED
  // TEST //#pragma ghs section bss=".bss.UDPNM_RAM_VAR_NO_INIT_UNSPECIFIED"
  #pragma alignvar (4)
#elif defined (UDPNM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED)
  #undef       UDPNM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (UDPNM_START_SEC_CONFIG_DATA_PREBUILD_8)
  #undef       UDPNM_START_SEC_CONFIG_DATA_PREBUILD_8
  // TEST //#pragma ghs section rodata=".rodata.UDPNM_ROM_CONFIG_CONST_PREBUILD_8"
#elif defined (UDPNM_STOP_SEC_CONFIG_DATA_PREBUILD_8)
  #undef       UDPNM_STOP_SEC_CONFIG_DATA_PREBUILD_8
  // TEST //#pragma ghs section
#elif defined (UDPNM_START_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED)
  #undef       UDPNM_START_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
  // TEST //#pragma ghs section rodata=".rodata.UDPNM_ROM_CONFIG_CONST_PREBUILD_UNSPECIFIED"
#elif defined (UDPNM_STOP_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED)
  #undef       UDPNM_STOP_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
  // TEST //#pragma ghs section
/* -------------------------------------------------------------------------- */
/*                                TCPIP                                     */
/* -------------------------------------------------------------------------- */
#elif defined (TCPIP_START_SEC_CODE)
  #undef       TCPIP_START_SEC_CODE
  // TEST //#pragma ghs section text=".text.TCPIP_CODE"
  // TEST //#pragma ghs section rodata=".rodata.TCPIP_ROM_CONST_UNSPECIFIED"
  // TEST //#pragma ghs section bss=".bss.TCPIP_RAM_VAR_CLEARED_UNSPECIFIED"
  // TEST //#pragma ghs section data=".data.TCPIP_RAM_VAR_INIT_UNSPECIFIED"
#elif defined (TCPIP_STOP_SEC_CODE)
  #undef       TCPIP_STOP_SEC_CODE
  // TEST //#pragma ghs section
#elif defined (TCPIP_START_SEC_CONFIG_DATA_PREBUILD_8)
  #undef       TCPIP_START_SEC_CONFIG_DATA_PREBUILD_8
  // TEST //#pragma ghs section rodata=".rodata.TCPIP_ROM_CONFIG_CONST_PREBUILD_8"
#elif defined (TCPIP_STOP_SEC_CONFIG_DATA_PREBUILD_8)
  #undef       TCPIP_STOP_SEC_CONFIG_DATA_PREBUILD_8
  // TEST //#pragma ghs section
#elif defined (TCPIP_START_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED)
  #undef       TCPIP_START_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
  // TEST //#pragma ghs section rodata=".rodata.TCPIP_ROM_CONFIG_CONST_PREBUILD_UNSPECIFIED"
#elif defined (TCPIP_STOP_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED)
  #undef       TCPIP_STOP_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (TCPIP_START_SEC_CONST_8)
  #undef       TCPIP_START_SEC_CONST_8
  // TEST //#pragma ghs section rodata=".rodata.TCPIP_ROM_CONST_8"
  #pragma alignvar (1)
#elif defined (TCPIP_STOP_SEC_CONST_8)
  #undef       TCPIP_STOP_SEC_CONST_8
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (TCPIP_START_SEC_CONST_32)
  #undef       TCPIP_START_SEC_CONST_32
  // TEST //#pragma ghs section rodata=".rodata.TCPIP_ROM_CONST_32"
  #pragma alignvar (4)
#elif defined (TCPIP_STOP_SEC_CONST_32)
  #undef       TCPIP_STOP_SEC_CONST_32
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (TCPIP_START_SEC_CONST_UNSPECIFIED)
  #undef       TCPIP_START_SEC_CONST_UNSPECIFIED
  // TEST //#pragma ghs section rodata=".rodata.TCPIP_ROM_CONST_UNSPECIFIED"
  #pragma alignvar (4)
#elif defined (TCPIP_STOP_SEC_CONST_UNSPECIFIED)
  #undef       TCPIP_STOP_SEC_CONST_UNSPECIFIED
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (TCPIP_START_SEC_VAR_CLEARED_BOOLEAN)
  #undef       TCPIP_START_SEC_VAR_CLEARED_BOOLEAN
  // TEST //#pragma ghs section bss=".bss.TCPIP_RAM_VAR_CLEARED_BOOLEAN"
  #pragma alignvar (1)
#elif defined (TCPIP_STOP_SEC_VAR_CLEARED_BOOLEAN)
  #undef       TCPIP_STOP_SEC_VAR_CLEARED_BOOLEAN
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (TCPIP_START_SEC_VAR_CLEARED_8)
  #undef       TCPIP_START_SEC_VAR_CLEARED_8
  // TEST //#pragma ghs section bss=".bss.TCPIP_RAM_VAR_CLEARED_8"
  #pragma alignvar (1)
#elif defined (TCPIP_STOP_SEC_VAR_CLEARED_8)
  #undef       TCPIP_STOP_SEC_VAR_CLEARED_8
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (TCPIP_START_SEC_VAR_CLEARED_16)
  #undef       TCPIP_START_SEC_VAR_CLEARED_16
  // TEST //#pragma ghs section bss=".bss.TCPIP_RAM_VAR_CLEARED_16"
  #pragma alignvar (1)
#elif defined (TCPIP_STOP_SEC_VAR_CLEARED_16)
  #undef       TCPIP_STOP_SEC_VAR_CLEARED_16
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (TCPIP_START_SEC_VAR_CLEARED_32)
  #undef       TCPIP_START_SEC_VAR_CLEARED_32
  // TEST //#pragma ghs section bss=".bss.TCPIP_RAM_VAR_CLEARED_32"
  #pragma alignvar (4)
#elif defined (TCPIP_STOP_SEC_VAR_CLEARED_32)
  #undef       TCPIP_STOP_SEC_VAR_CLEARED_32
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (TCPIP_START_SEC_VAR_NO_INIT_32)
  #undef       TCPIP_START_SEC_VAR_NO_INIT_32
  // TEST //#pragma ghs section bss=".bss.TCPIP_RAM_VAR_NO_INIT_32"
  #pragma alignvar (4)
#elif defined (TCPIP_STOP_SEC_VAR_NO_INIT_32)
  #undef       TCPIP_STOP_SEC_VAR_NO_INIT_32
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (TCPIP_START_SEC_VAR_NO_INIT_UNSPECIFIED)
  #undef       TCPIP_START_SEC_VAR_NO_INIT_UNSPECIFIED
  // TEST //#pragma ghs section bss=".bss.TCPIP_RAM_VAR_NO_INIT_UNSPECIFIED"
  #pragma alignvar (4)
#elif defined (TCPIP_STOP_SEC_VAR_NO_INIT_UNSPECIFIED)
  #undef       TCPIP_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
  #pragma alignvar (4)
  // TEST //#pragma ghs section
/* -------------------------------------------------------------------------- */
/*                                 CtrlRam                                    */
/* -------------------------------------------------------------------------- */
#elif defined (CTRLRAM_START_SEC_CODE)
  #undef       CTRLRAM_START_SEC_CODE
  // TEST //#pragma ghs section text=".text.DEFAULT_CODE"
  // TEST //#pragma ghs section rodata=".rodata.DEFAULT_ROM_CONST"
  // TEST //#pragma ghs section bss=".bss.DEFAULT_RAM_VAR_CLEARED"
  // TEST //#pragma ghs section data=".data.DEFAULT_RAM_VAR_INIT"
#elif defined (CTRLRAM_STOP_SEC_CODE)
  #undef       CTRLRAM_STOP_SEC_CODE
 // TEST //#pragma ghs section
#elif defined (CTRLRAM_START_SEC_VAR_CLEARED_BOOLEAN)
  #undef       CTRLRAM_START_SEC_VAR_CLEARED_BOOLEAN
  // TEST //#pragma ghs section bss=".bss.DEFAULT_RAM_VAR_CLEARED"
#elif defined (CTRLRAM_STOP_SEC_VAR_CLEARED_BOOLEAN)
  #undef       CTRLRAM_STOP_SEC_VAR_CLEARED_BOOLEAN
  // TEST //#pragma ghs section
#elif defined (CTRLRAM_START_SEC_VAR_CLEARED_UNSPECIFIED)
  #undef       CTRLRAM_START_SEC_VAR_CLEARED_UNSPECIFIED
  // TEST //#pragma ghs section bss=".bss.DEFAULT_RAM_VAR_CLEARED"
#elif defined (CTRLRAM_STOP_SEC_VAR_CLEARED_UNSPECIFIED)
  #undef       CTRLRAM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (CTRLRAM_START_SEC_CONST_UNSPECIFIED)
  #undef       CTRLRAM_START_SEC_CONST_UNSPECIFIED
  // TEST //#pragma ghs section rodata=".rodata.DEFAULT_ROM_CONST"
#elif defined (CTRLRAM_STOP_SEC_CONST_UNSPECIFIED)
  #undef       CTRLRAM_STOP_SEC_CONST_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (CTRLRAM_START_SEC_VAR_NOINIT_8)
  #undef       CTRLRAM_START_SEC_VAR_NOINIT_8
  // TEST //#pragma ghs section bss=".CTRLRAM_RAM_VAR_NO_INIT_8"
#elif defined (CTRLRAM_STOP_SEC_VAR_NOINIT_8)
  #undef       CTRLRAM_STOP_SEC_VAR_NOINIT_8
  // TEST //#pragma ghs section
#elif defined (CTRLRAM_START_SEC_VAR_NOINIT_16)
  #undef       CTRLRAM_START_SEC_VAR_NOINIT_16
  // TEST //#pragma ghs section bss=".CTRLRAM_RAM_VAR_NO_INIT_16"
#elif defined (CTRLRAM_STOP_SEC_VAR_NOINIT_16)
  #undef       CTRLRAM_STOP_SEC_VAR_NOINIT_16
  // TEST //#pragma ghs section
#elif defined (CTRLRAM_START_SEC_VAR_NOINIT_32)
  #undef       CTRLRAM_START_SEC_VAR_NOINIT_32
  // TEST //#pragma ghs section bss=".CTRLRAM_RAM_VAR_NO_INIT_32"
#elif defined (CTRLRAM_STOP_SEC_VAR_NOINIT_32)
  #undef       CTRLRAM_STOP_SEC_VAR_NOINIT_32
  // TEST //#pragma ghs section
#elif defined (CTRLRAM_START_SEC_VAR_NOINIT_UNSPECIFIED)
  #undef       CTRLRAM_START_SEC_VAR_NOINIT_UNSPECIFIED
  // TEST //#pragma ghs section bss=".CTRLRAM_RAM_VAR_NO_INIT_UNSPECIFIED"
#elif defined (CTRLRAM_STOP_SEC_VAR_NOINIT_UNSPECIFIED)
  #undef       CTRLRAM_STOP_SEC_VAR_NOINIT_UNSPECIFIED
 // TEST //#pragma ghs section
/* Controlled RAM Section : This is considered by NO INIT or POWER_ON_CLEARED */
#elif defined (CTRLRAM_START_SEC_VAR_NOINIT_BEGIN)
  #undef       CTRLRAM_START_SEC_VAR_NOINIT_BEGIN
  // TEST //#pragma ghs section bss=".CTRLRAM_RAM_VAR_NO_INIT_BEGIN"
 #elif defined (CTRLRAM_STOP_SEC_VAR_NOINIT_BEGIN)
  #undef       CTRLRAM_STOP_SEC_VAR_NOINIT_BEGIN
  // TEST //#pragma ghs section
#elif defined (CTRLRAM_START_SEC_VAR_NOINIT_END)
  #undef       CTRLRAM_START_SEC_VAR_NOINIT_END
  // TEST //#pragma ghs section bss=".CTRLRAM_RAM_VAR_NO_INIT_END"
#elif defined (CTRLRAM_STOP_SEC_VAR_NOINIT_END)
  #undef       CTRLRAM_STOP_SEC_VAR_NOINIT_END
  // TEST //#pragma ghs section
#elif defined (CTRLRAM_START_SEC_VAR_POWER_ON_CLEARED_8)
  #undef       CTRLRAM_START_SEC_VAR_POWER_ON_CLEARED_8
  // TEST //#pragma ghs section bss=".CTRLRAM_RAM_VAR_POWER_ON_CLEARED_8"
#elif defined (CTRLRAM_STOP_SEC_VAR_POWER_ON_CLEARED_8)
  #undef       CTRLRAM_STOP_SEC_VAR_POWER_ON_CLEARED_8
  // TEST //#pragma ghs section
#elif defined (CTRLRAM_START_SEC_VAR_POWER_ON_CLEARED_16)
  #undef       CTRLRAM_START_SEC_VAR_POWER_ON_CLEARED_16
  // TEST //#pragma ghs section bss=".CTRLRAM_RAM_VAR_POWER_ON_CLEARED_16"
#elif defined (CTRLRAM_STOP_SEC_VAR_POWER_ON_CLEARED_16)
  #undef       CTRLRAM_STOP_SEC_VAR_POWER_ON_CLEARED_16
  // TEST //#pragma ghs section
#elif defined (CTRLRAM_START_SEC_VAR_POWER_ON_CLEARED_32)
  #undef       CTRLRAM_START_SEC_VAR_POWER_ON_CLEARED_32
  // TEST //#pragma ghs section bss=".CTRLRAM_RAM_VAR_POWER_ON_CLEARED_32"
#elif defined (CTRLRAM_STOP_SEC_VAR_POWER_ON_CLEARED_32)
  #undef       CTRLRAM_STOP_SEC_VAR_POWER_ON_CLEARED_32
  // TEST //#pragma ghs section
#elif defined (CTRLRAM_START_SEC_VAR_POWER_ON_CLEARED_UNSPECIFIED)
  #undef       CTRLRAM_START_SEC_VAR_POWER_ON_CLEARED_UNSPECIFIED
  // TEST //#pragma ghs section bss=".CTRLRAM_RAM_VAR_POWER_ON_CLEARED_UNSPECIFIED"
#elif defined (CTRLRAM_STOP_SEC_VAR_POWER_ON_CLEARED_UNSPECIFIED)
  #undef       CTRLRAM_STOP_SEC_VAR_POWER_ON_CLEARED_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (CTRLRAM_START_SEC_CONST_UNSPECIFIED)
  #undef       CTRLRAM_START_SEC_CONST_UNSPECIFIED
  // TEST //#pragma ghs section rodata=".rodata.CTRLRAM_ROM_CONST"
#elif defined (CTRLRAM_STOP_SEC_CONST_UNSPECIFIED)
  #undef       CTRLRAM_STOP_SEC_CONST_UNSPECIFIED
  // TEST //#pragma ghs section
/* -------------------------------------------------------------------------- */
/*                                 Ocu                                        */
/* -------------------------------------------------------------------------- */
#elif defined (OCU_START_SEC_CODE)
  #undef       OCU_START_SEC_CODE
  // TEST //#pragma ghs section text=".text.DEFAULT_CODE"
#elif defined (OCU_STOP_SEC_CODE)
  #undef       OCU_STOP_SEC_CODE
  // TEST //#pragma ghs section
#elif defined (OCU_START_SEC_CODE_FAST)
  #undef       OCU_START_SEC_CODE_FAST
  // TEST //#pragma ghs section text=".text.DEFAULT_CODE"
#elif defined (OCU_STOP_SEC_CODE_FAST)
  #undef       OCU_STOP_SEC_CODE_FAST
  // TEST //#pragma ghs section
#elif defined (OCU_START_SEC_VAR_CLEARED_8)
  #undef       OCU_START_SEC_VAR_CLEARED_8
  // TEST //#pragma ghs section bss=".bss.DEFAULT_RAM_VAR_CLEARED"
#elif defined (OCU_STOP_SEC_VAR_CLEARED_8)
  #undef       OCU_STOP_SEC_VAR_CLEARED_8
  // TEST //#pragma ghs section
#elif defined (OCU_START_SEC_VAR_CLEARED_16)
  #undef       OCU_START_SEC_VAR_CLEARED_16
  // TEST //#pragma ghs section bss=".bss.DEFAULT_RAM_VAR_CLEARED"
#elif defined (OCU_STOP_SEC_VAR_CLEARED_16)
  #undef       OCU_STOP_SEC_VAR_CLEARED_16
  // TEST //#pragma ghs section
#elif defined (OCU_START_SEC_VAR_CLEARED_UNSPECIFIED)
  #undef       OCU_START_SEC_VAR_CLEARED_UNSPECIFIED
  // TEST //#pragma ghs section bss=".bss.DEFAULT_RAM_VAR_CLEARED"
#elif defined (OCU_STOP_SEC_VAR_CLEARED_UNSPECIFIED)
  #undef       OCU_STOP_SEC_VAR_CLEARED_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (OCU_START_SEC_VAR_INIT_UNSPECIFIED)
  #undef       OCU_START_SEC_VAR_INIT_UNSPECIFIED
  // TEST //#pragma ghs section data=".data.DEFAULT_RAM_VAR_INIT"
#elif defined (OCU_STOP_SEC_VAR_INIT_UNSPECIFIED)
  #undef       OCU_STOP_SEC_VAR_INIT_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (OCU_START_SEC_CONST_8)
  #undef       OCU_START_SEC_CONST_8
  // TEST //#pragma ghs section rodata=".rodata.DEFAULT_ROM_CONST"
#elif defined (OCU_STOP_SEC_CONST_8)
  #undef       OCU_STOP_SEC_CONST_8
  // TEST //#pragma ghs section
#elif defined (OCU_START_SEC_CONST_16)
  #undef       OCU_START_SEC_CONST_16
  // TEST //#pragma ghs section rodata=".rodata.DEFAULT_ROM_CONST"
#elif defined (OCU_STOP_SEC_CONST_16)
  #undef       OCU_STOP_SEC_CONST_16
  // TEST //#pragma ghs section
#elif defined (OCU_START_SEC_CONST_UNSPECIFIED)
  #undef       OCU_START_SEC_CONST_UNSPECIFIED
  // TEST //#pragma ghs section rodata=".rodata.DEFAULT_ROM_CONST"
#elif defined (OCU_STOP_SEC_CONST_UNSPECIFIED)
  #undef       OCU_STOP_SEC_CONST_UNSPECIFIED
  // TEST //#pragma ghs section
/* -------------------------------------------------------------------------- */
/*                                 Pm                                         */
/* -------------------------------------------------------------------------- */
#elif defined (PM_START_SEC_CODE)
  #undef       PM_START_SEC_CODE
  // TEST //#pragma ghs section text=".text.DEFAULT_CODE"
  // TEST //#pragma ghs section rodata=".rodata.DEFAULT_ROM_CONST"
  // TEST //#pragma ghs section bss=".bss.DEFAULT_RAM_VAR_CLEARED"
  // TEST //#pragma ghs section data=".data.DEFAULT_RAM_VAR_INIT"
#elif defined (PM_STOP_SEC_CODE)
  #undef       PM_STOP_SEC_CODE
  // TEST //#pragma ghs section
#elif defined (PM_START_SEC_VAR_CLEARED_UNSPECIFIED)
  #undef       PM_START_SEC_VAR_CLEARED_UNSPECIFIED
  // TEST //#pragma ghs section bss=".bss.DEFAULT_RAM_VAR_CLEARED"
#elif defined (PM_STOP_SEC_VAR_CLEARED_UNSPECIFIED)
  #undef       PM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (PM_START_SEC_CONST_UNSPECIFIED)
  #undef       PM_START_SEC_CONST_UNSPECIFIED
  // TEST //#pragma ghs section rodata=".rodata.DEFAULT_ROM_CONST"
#elif defined (PM_STOP_SEC_CONST_UNSPECIFIED)
  #undef       PM_STOP_SEC_CONST_UNSPECIFIED
  // TEST //#pragma ghs section
/* -------------------------------------------------------------------------- */
/*                                 RomTst                                     */
/* -------------------------------------------------------------------------- */
#elif defined (ROMTST_START_SEC_CODE)
  #undef       ROMTST_START_SEC_CODE
  // TEST //#pragma ghs section text=".text.DEFAULT_CODE"
  // TEST //#pragma ghs section rodata=".rodata.DEFAULT_ROM_CONST"
  // TEST //#pragma ghs section bss=".bss.DEFAULT_RAM_VAR_CLEARED"
  // TEST //#pragma ghs section data=".data.DEFAULT_RAM_VAR_INIT"
#elif defined (ROMTST_STOP_SEC_CODE)
  #undef       ROMTST_STOP_SEC_CODE
  // TEST //#pragma ghs section
#elif defined (ROMTST_START_SEC_VAR_CLEARED_BOOLEAN)
  #undef       ROMTST_START_SEC_VAR_CLEARED_BOOLEAN
  // TEST //#pragma ghs section bss=".bss.DEFAULT_RAM_VAR_CLEARED"
#elif defined (ROMTST_STOP_SEC_VAR_CLEARED_BOOLEAN)
  #undef       ROMTST_STOP_SEC_VAR_CLEARED_BOOLEAN
  // TEST //#pragma ghs section
#elif defined (ROMTST_START_SEC_VAR_CLEARED_UNSPECIFIED)
  #undef       ROMTST_START_SEC_VAR_CLEARED_UNSPECIFIED
  // TEST //#pragma ghs section bss=".bss.DEFAULT_RAM_VAR_CLEARED"
#elif defined (ROMTST_STOP_SEC_VAR_CLEARED_UNSPECIFIED)
  #undef       ROMTST_STOP_SEC_VAR_CLEARED_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (ROMTST_START_SEC_CONST_UNSPECIFIED)
  #undef       ROMTST_START_SEC_CONST_UNSPECIFIED
  // TEST //#pragma ghs section rodata=".rodata.DEFAULT_ROM_CONST"
#elif defined (ROMTST_STOP_SEC_CONST_UNSPECIFIED)
  #undef       ROMTST_STOP_SEC_CONST_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (ROMTST_START_SEC_VAR_CLEARED_8)
  #undef      ROMTST_START_SEC_VAR_CLEARED_8
  // TEST //#pragma ghs section bss=".bss.DEFAULT_RAM_VAR_CLEARED"
#elif defined (ROMTST_STOP_SEC_VAR_CLEARED_8)
   #undef      ROMTST_STOP_SEC_VAR_CLEARED_8
  // TEST //#pragma ghs section
#elif defined (ROMTST_START_SEC_MEM_CHK_ID)
  #undef       ROMTST_START_SEC_MEM_CHK_ID
  // TEST //#pragma ghs section rodata=".MEM_CHK_ID"
#elif defined (ROMTST_STOP_SEC_MEM_CHK_ID)
  #undef      ROMTST_STOP_SEC_MEM_CHK_ID
  // TEST //#pragma ghs section
#elif defined (ROMTST_START_SEC_MEM_CHK_CRC)
  #undef       ROMTST_START_SEC_MEM_CHK_CRC
  // TEST //#pragma ghs section rodata=".MEM_CHK_CRC"
#elif defined (ROMTST_STOP_SEC_MEM_CHK_CRC)
  #undef      ROMTST_STOP_SEC_MEM_CHK_CRC
  // TEST //#pragma ghs section
#elif defined (ROMTST_START_SEC_MEM_CHECK)
  #undef       ROMTST_START_SEC_MEM_CHECK
  // TEST //#pragma ghs section text=".MEM_CHECK"
#elif defined (ROMTST_STOP_SEC_MEM_CHECK)
  #undef      ROMTST_STOP_SEC_MEM_CHECK
  // TEST //#pragma ghs section
/* -------------------------------------------------------------------------- */
/*                                 UART                                       */
/* -------------------------------------------------------------------------- */
#elif defined (UART_START_SEC_CODE)
  #undef       UART_START_SEC_CODE
  // TEST //#pragma ghs section text=".text.DEFAULT_CODE"
  // TEST //#pragma ghs section rodata=".rodata.DEFAULT_ROM_CONST"
  // TEST //#pragma ghs section bss=".bss.DEFAULT_RAM_VAR_CLEARED"
  // TEST //#pragma ghs section data=".data.DEFAULT_RAM_VAR_INIT"
#elif defined (UART_STOP_SEC_CODE)
  #undef       UART_STOP_SEC_CODE
  // TEST //#pragma ghs section
/* --------------------------------------------------------------------------*/
/*                                  EOL                                      */
/* --------------------------------------------------------------------------*/
#elif defined (EOL_START_SEC_CODE)
  #undef EOL_START_SEC_CODE
  // TEST //#pragma ghs section text=".text.DEFAULT_CODE"
  // TEST //#pragma ghs section rodata=".rodata.DEFAULT_ROM_CONST"
  // TEST //#pragma ghs section bss=".bss.DEFAULT_RAM_VAR_CLEARED"
  // TEST //#pragma ghs section data=".data.DEFAULT_RAM_VAR_INIT"
#elif defined (EOL_STOP_SEC_CODE)
  #undef EOL_STOP_SEC_CODE
  // TEST //#pragma ghs section
/* --------------------------------------------------------------------------*/
/*                               CDD_ROUTER                                  */
/* --------------------------------------------------------------------------*/
#elif defined (CDD_ROUTER_START_SEC_CONST_8)
  #undef CDD_ROUTER_START_SEC_CONST_8
  // TEST //#pragma ghs section rodata=".rodata.CDD_ROUTER_ROM_CONST_8"
#elif defined (CDD_ROUTER_STOP_SEC_CONST_8)
  #undef CDD_ROUTER_STOP_SEC_CONST_8
  // TEST //#pragma ghs section
#elif defined (CDD_ROUTER_START_SEC_CONST_UNSPECIFIED)
  #undef CDD_ROUTER_START_SEC_CONST_UNSPECIFIED
  // TEST //#pragma ghs section rodata=".rodata.CDD_ROUTER_ROM_CONST_UNSPECIFIED"
#elif defined (CDD_ROUTER_STOP_SEC_CONST_UNSPECIFIED)
  #undef CDD_ROUTER_STOP_SEC_CONST_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (CDD_ROUTER_START_SEC_CODE)
  #undef CDD_ROUTER_START_SEC_CODE
  // TEST //#pragma ghs section text=".text.CDD_ROUTER_CODE"
  // TEST //#pragma ghs section rodata=".rodata.CDD_ROUTER_ROM_CONST_UNSPECIFIED"
  // TEST //#pragma ghs section bss=".bss.CDD_ROUTER_RAM_VAR_CLEARED_UNSPECIFIED"
  // TEST //#pragma ghs section data=".data.CDD_ROUTER_RAM_VAR_INIT_UNSPECIFIED"
#elif defined (CDD_ROUTER_STOP_SEC_CODE)
  #undef CDD_ROUTER_STOP_SEC_CODE
  // TEST //#pragma ghs section
/* --------------------------------------------------------------------------*/
/*                               IDSM                                        */
/* --------------------------------------------------------------------------*/
#elif defined (IDSM_START_SEC_CONST_8)
  #undef IDSM_START_SEC_CONST_8
  // TEST //#pragma ghs section rodata=".rodata.DEFAULT_ROM_CONST"
#elif defined (IDSM_STOP_SEC_CONST_8)
  #undef IDSM_STOP_SEC_CONST_8
  // TEST //#pragma ghs section
#elif defined (IDSM_START_SEC_CONST_16)
  #undef       IDSM_START_SEC_CONST_16
  // TEST //#pragma ghs section rodata=".rodata.DEFAULT_ROM_CONST"
#elif defined (IDSM_STOP_SEC_CONST_16)
  #undef       IDSM_STOP_SEC_CONST_16
  // TEST //#pragma ghs section
#elif defined (IDSM_START_SEC_CONST_32)
  #undef       IDSM_START_SEC_CONST_32
  // TEST //#pragma ghs section rodata=".rodata.DEFAULT_ROM_CONST"
#elif defined (IDSM_STOP_SEC_CONST_32)
  #undef       IDSM_STOP_SEC_CONST_32
  // TEST //#pragma ghs section
#elif defined (IDSM_START_SEC_CONST_UNSPECIFIED)
  #undef IDSM_START_SEC_CONST_UNSPECIFIED
  // TEST //#pragma ghs section rodata=".rodata.DEFAULT_ROM_CONST"
#elif defined (IDSM_STOP_SEC_CONST_UNSPECIFIED)
  #undef IDSM_STOP_SEC_CONST_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (IDSM_START_SEC_VAR_CLEARED_8)
  #undef       IDSM_START_SEC_VAR_CLEARED_8
  // TEST //#pragma ghs section bss=".bss.DEFAULT_RAM_VAR_CLEARED"
#elif defined (IDSM_STOP_SEC_VAR_CLEARED_8)
  #undef       IDSM_STOP_SEC_VAR_CLEARED_8
  // TEST //#pragma ghs section
#elif defined (IDSM_START_SEC_VAR_CLEARED_16)
  #undef       IDSM_START_SEC_VAR_CLEARED_16
  // TEST //#pragma ghs section bss=".bss.DEFAULT_RAM_VAR_CLEARED"
#elif defined (IDSM_STOP_SEC_VAR_CLEARED_16)
  #undef       IDSM_STOP_SEC_VAR_CLEARED_16
  // TEST //#pragma ghs section
#elif defined (IDSM_START_SEC_VAR_CLEARED_32)
  #undef       IDSM_START_SEC_VAR_CLEARED_32
  // TEST //#pragma ghs section bss=".bss.DEFAULT_RAM_VAR_CLEARED"
#elif defined (IDSM_STOP_SEC_VAR_CLEARED_32)
  #undef       IDSM_STOP_SEC_VAR_CLEARED_32
  // TEST //#pragma ghs section
#elif defined (IDSM_START_SEC_VAR_CLEARED_UNSPECIFIED)
  #undef       IDSM_START_SEC_VAR_CLEARED_UNSPECIFIED
  // TEST //#pragma ghs section bss=".bss.DEFAULT_RAM_VAR_CLEARED"
#elif defined (IDSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED)
  #undef       IDSM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (IDSM_START_SEC_VAR_INIT_8)
  #undef       IDSM_START_SEC_VAR_INIT_8
  // TEST //#pragma ghs section data=".data.DEFAULT_RAM_VAR_INIT"
#elif defined (IDSM_STOP_SEC_VAR_INIT_8)
  #undef       IDSM_STOP_SEC_VAR_INIT_8
  // TEST //#pragma ghs section
#elif defined (IDSM_START_SEC_VAR_INIT_16)
  #undef       IDSM_START_SEC_VAR_INIT_16
  // TEST //#pragma ghs section data=".data.DEFAULT_RAM_VAR_INIT"
#elif defined (IDSM_STOP_SEC_VAR_INIT_16)
  #undef       IDSM_STOP_SEC_VAR_INIT_16
  // TEST //#pragma ghs section
#elif defined (IDSM_START_SEC_VAR_INIT_32)
  #undef       IDSM_START_SEC_VAR_INIT_32
  // TEST //#pragma ghs section data=".data.DEFAULT_RAM_VAR_INIT"
#elif defined (IDSM_STOP_SEC_VAR_INIT_32)
  #undef       IDSM_STOP_SEC_VAR_INIT_32
  // TEST //#pragma ghs section
#elif defined (IDSM_START_SEC_VAR_INIT_UNSPECIFIED)
  #undef       IDSM_START_SEC_VAR_INIT_UNSPECIFIED
  // TEST //#pragma ghs section data=".data.DEFAULT_RAM_VAR_INIT"
#elif defined (IDSM_STOP_SEC_VAR_INIT_UNSPECIFIED)
  #undef       IDSM_STOP_SEC_VAR_INIT_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (IDSM_START_SEC_CODE)
  #undef IDSM_START_SEC_CODE
  // TEST //#pragma ghs section text=".text.DEFAULT_CODE"
  // TEST //#pragma ghs section rodata=".rodata.DEFAULT_ROM_CONST"
  // TEST //#pragma ghs section bss=".bss.DEFAULT_RAM_VAR_CLEARED"
  // TEST //#pragma ghs section data=".data.DEFAULT_RAM_VAR_INIT"
#elif defined (IDSM_STOP_SEC_CODE)
  #undef IDSM_STOP_SEC_CODE
  // TEST //#pragma ghs section
/* --------------------------------------------------------------------------*/
/*                               COMXF                                       */
/* --------------------------------------------------------------------------*/
#elif defined (COMXF_START_SEC_CODE_ASIL_D)
  #undef COMXF_START_SEC_CODE_ASIL_D
  // TEST //#pragma ghs section text=".text.COMXF_CODE"
  // TEST //#pragma ghs section rodata=".rodata.COMXF_ROM_CONST_UNSPECIFIED"
  // TEST //#pragma ghs section bss=".bss.COMXF_RAM_VAR_CLEARED_UNSPECIFIED"
  // TEST //#pragma ghs section data=".data.COMXF_RAM_VAR_INIT_UNSPECIFIED"
#elif defined (COMXF_STOP_SEC_CODE_ASIL_D)
  #undef COMXF_STOP_SEC_CODE_ASIL_D
  // TEST //#pragma ghs section
#elif defined (COMXF_START_SEC_VAR_INIT_ASIL_D_BOOLEAN)
  #undef COMXF_START_SEC_VAR_INIT_ASIL_D_BOOLEAN
  // TEST //#pragma ghs section data=".data.COMXF_RAM_VAR_INIT_BOOLEAN"
#elif defined (COMXF_STOP_SEC_VAR_INIT_ASIL_D_BOOLEAN)
  #undef COMXF_STOP_SEC_VAR_INIT_ASIL_D_BOOLEAN
  // TEST //#pragma ghs section
#elif defined (COMXF_START_SEC_CONFIG_DATA_ASIL_D_UNSPECIFIED)
  #undef COMXF_START_SEC_CONFIG_DATA_ASIL_D_UNSPECIFIED
  // TEST //#pragma ghs section rodata=".rodata.COMXF_ROM_CONST_UNSPECIFIED"
#elif defined (COMXF_STOP_SEC_CONFIG_DATA_ASIL_D_UNSPECIFIED)
  #undef COMXF_STOP_SEC_CONFIG_DATA_ASIL_D_UNSPECIFIED
  // TEST //#pragma ghs section
/* --------------------------------------------------------------------------*/
/*                               T1AD                                        */
/* --------------------------------------------------------------------------*/
#elif defined (T1AD_START_SEC_VAR_CLEARED_BOOLEAN)
  #undef       T1AD_START_SEC_VAR_CLEARED_BOOLEAN
  // TEST //#pragma ghs section bss=".bss.DEFAULT_RAM_VAR_CLEARED"
  #pragma alignvar (1)
#elif defined (T1AD_STOP_SEC_VAR_CLEARED_BOOLEAN)
  #undef       T1AD_STOP_SEC_VAR_CLEARED_BOOLEAN
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (T1AD_START_SEC_VAR_CLEARED_8)
  #undef       T1AD_START_SEC_VAR_CLEARED_8
  // TEST //#pragma ghs section bss=".bss.DEFAULT_RAM_VAR_CLEARED"
  #pragma alignvar (1)
#elif defined (T1AD_STOP_SEC_VAR_CLEARED_8)
  #undef       T1AD_STOP_SEC_VAR_CLEARED_8
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (T1AD_START_SEC_VAR_CLEARED_16)
  #undef       T1AD_START_SEC_VAR_CLEARED_16
  // TEST //#pragma ghs section bss=".bss.DEFAULT_RAM_VAR_CLEARED"
  #pragma alignvar (2)
#elif defined (T1AD_STOP_SEC_VAR_CLEARED_16)
  #undef       T1AD_STOP_SEC_VAR_CLEARED_16
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (T1AD_START_SEC_VAR_CLEARED_32)
  #undef       T1AD_START_SEC_VAR_CLEARED_32
  // TEST //#pragma ghs section bss=".bss.DEFAULT_RAM_VAR_CLEARED"
  #pragma alignvar (4)
#elif defined (T1AD_STOP_SEC_VAR_CLEARED_32)
  #undef       T1AD_STOP_SEC_VAR_CLEARED_32
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (T1AD_START_SEC_VAR_CLEARED_UNSPECIFIED)
  #undef       T1AD_START_SEC_VAR_CLEARED_UNSPECIFIED
  // TEST //#pragma ghs section bss=".bss.DEFAULT_RAM_VAR_CLEARED"
  #pragma alignvar (4)
#elif defined (T1AD_STOP_SEC_VAR_CLEARED_UNSPECIFIED)
  #undef       T1AD_STOP_SEC_VAR_CLEARED_UNSPECIFIED
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (T1AD_START_SEC_CONST_BOOLEAN)
  #undef       T1AD_START_SEC_CONST_BOOLEAN
  // TEST //#pragma ghs section rodata=".rodata.DEFAULT_ROM_CONST"
  #pragma alignvar (1)
#elif defined (T1AD_STOP_SEC_CONST_BOOLEAN)
  #undef       T1AD_STOP_SEC_CONST_BOOLEAN
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (T1AD_START_SEC_CONST_8)
  #undef       T1AD_START_SEC_CONST_8
  // TEST //#pragma ghs section rodata=".rodata.DEFAULT_ROM_CONST"
  #pragma alignvar (1)
#elif defined (T1AD_STOP_SEC_CONST_8)
  #undef       T1AD_STOP_SEC_CONST_8
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (T1AD_START_SEC_CONST_16)
  #undef       T1AD_START_SEC_CONST_16
  // TEST //#pragma ghs section rodata=".rodata.DEFAULT_ROM_CONST"
  #pragma alignvar (2)
#elif defined (T1AD_STOP_SEC_CONST_16)
  #undef       T1AD_STOP_SEC_CONST_16
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (T1AD_START_SEC_CONST_32)
  #undef       T1AD_START_SEC_CONST_32
  // TEST //#pragma ghs section rodata=".rodata.DEFAULT_ROM_CONST"
  #pragma alignvar (4)
#elif defined (T1AD_STOP_SEC_CONST_32)
  #undef       T1AD_STOP_SEC_CONST_32
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (T1AD_START_SEC_CONST_UNSPECIFIED)
  #undef       T1AD_START_SEC_CONST_UNSPECIFIED
  // TEST //#pragma ghs section rodata=".rodata.DEFAULT_ROM_CONST"
  #pragma alignvar (4)
#elif defined (T1AD_STOP_SEC_CONST_UNSPECIFIED)
  #undef       T1AD_STOP_SEC_CONST_UNSPECIFIED
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (T1AD_START_SEC_VAR_NO_INIT_BOOLEAN)
  #undef       T1AD_START_SEC_VAR_NO_INIT_BOOLEAN
  // TEST //#pragma ghs section bss=".bss.DEFAULT_RAM_VAR_NO_INIT"
  #pragma alignvar (1)
#elif defined (T1AD_STOP_SEC_VAR_NO_INIT_BOOLEAN)
  #undef       T1AD_STOP_SEC_VAR_NO_INIT_BOOLEAN
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (T1AD_START_SEC_VAR_NO_INIT_8)
  #undef       T1AD_START_SEC_VAR_NO_INIT_8
  // TEST //#pragma ghs section bss=".bss.DEFAULT_RAM_VAR_NO_INIT"
  #pragma alignvar (1)
#elif defined (T1AD_STOP_SEC_VAR_NO_INIT_8)
  #undef       T1AD_STOP_SEC_VAR_NO_INIT_8
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (T1AD_START_SEC_VAR_NO_INIT_16)
  #undef       T1AD_START_SEC_VAR_NO_INIT_16
  // TEST //#pragma ghs section bss=".bss.DEFAULT_RAM_VAR_NO_INIT"
  #pragma alignvar (2)
#elif defined (T1AD_STOP_SEC_VAR_NO_INIT_16)
  #undef       T1AD_STOP_SEC_VAR_NO_INIT_16
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (T1AD_START_SEC_VAR_NO_INIT_32)
  #undef       T1AD_START_SEC_VAR_NO_INIT_32
  // TEST //#pragma ghs section bss=".bss.DEFAULT_RAM_VAR_NO_INIT"
  #pragma alignvar (4)
#elif defined (T1AD_STOP_SEC_VAR_NO_INIT_32)
  #undef       T1AD_STOP_SEC_VAR_NO_INIT_32
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (T1AD_START_SEC_VAR_NO_INIT_UNSPECIFIED)
  #undef       T1AD_START_SEC_VAR_NO_INIT_UNSPECIFIED
  // TEST //#pragma ghs section bss=".bss.DEFAULT_RAM_VAR_NO_INIT"
  #pragma alignvar (4)
#elif defined (T1AD_STOP_SEC_VAR_NO_INIT_UNSPECIFIED)
  #undef       T1AD_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (T1AD_START_SEC_VAR_INIT_BOOLEAN)
  #undef       T1AD_START_SEC_VAR_INIT_BOOLEAN
  // TEST //#pragma ghs section data=".data.DEFAULT_RAM_VAR_INIT"
  #pragma alignvar (1)
#elif defined (T1AD_STOP_SEC_VAR_INIT_BOOLEAN)
  #undef       T1AD_STOP_SEC_VAR_INIT_BOOLEAN
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (T1AD_START_SEC_VAR_INIT_8)
  #undef       T1AD_START_SEC_VAR_INIT_8
  // TEST //#pragma ghs section data=".data.DEFAULT_RAM_VAR_INIT"
  #pragma alignvar (1)
#elif defined (T1AD_STOP_SEC_VAR_INIT_8)
  #undef       T1AD_STOP_SEC_VAR_INIT_8
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (T1AD_START_SEC_VAR_INIT_16)
  #undef       T1AD_START_SEC_VAR_INIT_16
  // TEST //#pragma ghs section data=".data.DEFAULT_RAM_VAR_INIT"
  #pragma alignvar (2)
#elif defined (T1AD_STOP_SEC_VAR_INIT_16)
  #undef       T1AD_STOP_SEC_VAR_INIT_16
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (T1AD_START_SEC_VAR_INIT_32)
  #undef       T1AD_START_SEC_VAR_INIT_32
  // TEST //#pragma ghs section data=".data.DEFAULT_RAM_VAR_INIT"
  #pragma alignvar (4)
#elif defined (T1AD_STOP_SEC_VAR_INIT_32)
  #undef       T1AD_STOP_SEC_VAR_INIT_32
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (T1AD_START_SEC_VAR_INIT_UNSPECIFIED)
  #undef       T1AD_START_SEC_VAR_INIT_UNSPECIFIED
  // TEST //#pragma ghs section data=".data.DEFAULT_RAM_VAR_INIT"
  #pragma alignvar (4)
#elif defined (T1AD_STOP_SEC_VAR_INIT_UNSPECIFIED)
  #undef       T1AD_STOP_SEC_VAR_INIT_UNSPECIFIED
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (T1AD_START_SEC_CODE)
  #undef       T1AD_START_SEC_CODE
  // TEST //#pragma ghs section text=".text.T1AD_CODE"
  // TEST //#pragma ghs section rodata=".rodata.DEFAULT_ROM_CONST"
  // TEST //#pragma ghs section bss=".bss.DEFAULT_RAM_VAR_CLEARED"
  // TEST //#pragma ghs section data=".data.DEFAULT_RAM_VAR_INIT"
#elif defined (T1AD_STOP_SEC_CODE)
  #undef       T1AD_STOP_SEC_CODE
  // TEST //#pragma ghs section
/* -------------------------------------------------------------------------- */
/*                                PROVAD                                      */
/* -------------------------------------------------------------------------- */
#elif defined (PROVAD_START_SEC_VAR_CLEARED_BOOLEAN)
  #undef       PROVAD_START_SEC_VAR_CLEARED_BOOLEAN
  // TEST //#pragma ghs section bss=".bss.DEFAULT_RAM_VAR_CLEARED"
  #pragma alignvar (1)
#elif defined (PROVAD_STOP_SEC_VAR_CLEARED_BOOLEAN)
  #undef       PROVAD_STOP_SEC_VAR_CLEARED_BOOLEAN
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (PROVAD_START_SEC_VAR_CLEARED_8)
  #undef       PROVAD_START_SEC_VAR_CLEARED_8
  // TEST //#pragma ghs section bss=".bss.DEFAULT_RAM_VAR_CLEARED"
  #pragma alignvar (1)
#elif defined (PROVAD_STOP_SEC_VAR_CLEARED_8)
  #undef       PROVAD_STOP_SEC_VAR_CLEARED_8
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (PROVAD_START_SEC_VAR_CLEARED_16)
  #undef       PROVAD_START_SEC_VAR_CLEARED_16
  // TEST //#pragma ghs section bss=".bss.DEFAULT_RAM_VAR_CLEARED"
  #pragma alignvar (2)
#elif defined (PROVAD_STOP_SEC_VAR_CLEARED_16)
  #undef       PROVAD_STOP_SEC_VAR_CLEARED_16
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (PROVAD_START_SEC_VAR_CLEARED_32)
  #undef       PROVAD_START_SEC_VAR_CLEARED_32
  // TEST //#pragma ghs section bss=".bss.DEFAULT_RAM_VAR_CLEARED"
  #pragma alignvar (4)
#elif defined (PROVAD_STOP_SEC_VAR_CLEARED_32)
  #undef       PROVAD_STOP_SEC_VAR_CLEARED_32
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (PROVAD_START_SEC_VAR_CLEARED_UNSPECIFIED)
  #undef       PROVAD_START_SEC_VAR_CLEARED_UNSPECIFIED
  // TEST //#pragma ghs section bss=".bss.DEFAULT_RAM_VAR_CLEARED"
  #pragma alignvar (4)
#elif defined (PROVAD_STOP_SEC_VAR_CLEARED_UNSPECIFIED)
  #undef       PROVAD_STOP_SEC_VAR_CLEARED_UNSPECIFIED
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (PROVAD_START_SEC_CONST_BOOLEAN)
  #undef       PROVAD_START_SEC_CONST_BOOLEAN
  // TEST //#pragma ghs section rodata=".rodata.DEFAULT_ROM_CONST"
  #pragma alignvar (1)
#elif defined (PROVAD_STOP_SEC_CONST_BOOLEAN)
  #undef       PROVAD_STOP_SEC_CONST_BOOLEAN
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (PROVAD_START_SEC_CONST_8)
  #undef       PROVAD_START_SEC_CONST_8
  // TEST //#pragma ghs section rodata=".rodata.DEFAULT_ROM_CONST"
  #pragma alignvar (1)
#elif defined (PROVAD_STOP_SEC_CONST_8)
  #undef       PROVAD_STOP_SEC_CONST_8
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (PROVAD_START_SEC_CONST_16)
  #undef       PROVAD_START_SEC_CONST_16
  // TEST //#pragma ghs section rodata=".rodata.DEFAULT_ROM_CONST"
  #pragma alignvar (2)
#elif defined (PROVAD_STOP_SEC_CONST_16)
  #undef       PROVAD_STOP_SEC_CONST_16
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (PROVAD_START_SEC_CONST_32)
  #undef       PROVAD_START_SEC_CONST_32
  // TEST //#pragma ghs section rodata=".rodata.DEFAULT_ROM_CONST"
  #pragma alignvar (4)
#elif defined (PROVAD_STOP_SEC_CONST_32)
  #undef       PROVAD_STOP_SEC_CONST_32
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (PROVAD_START_SEC_CONST_UNSPECIFIED)
  #undef       PROVAD_START_SEC_CONST_UNSPECIFIED
  // TEST //#pragma ghs section rodata=".rodata.DEFAULT_ROM_CONST"
  #pragma alignvar (4)
#elif defined (PROVAD_STOP_SEC_CONST_UNSPECIFIED)
  #undef       PROVAD_STOP_SEC_CONST_UNSPECIFIED
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (PROVAD_START_SEC_VAR_NO_INIT_BOOLEAN)
  #undef       PROVAD_START_SEC_VAR_NO_INIT_BOOLEAN
  // TEST //#pragma ghs section bss=".bss.DEFAULT_RAM_VAR_NO_INIT"
  #pragma alignvar (1)
#elif defined (PROVAD_STOP_SEC_VAR_NO_INIT_BOOLEAN)
  #undef       PROVAD_STOP_SEC_VAR_NO_INIT_BOOLEAN
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (PROVAD_START_SEC_VAR_NO_INIT_8)
  #undef       PROVAD_START_SEC_VAR_NO_INIT_8
  // TEST //#pragma ghs section bss=".bss.DEFAULT_RAM_VAR_NO_INIT"
  #pragma alignvar (1)
#elif defined (PROVAD_STOP_SEC_VAR_NO_INIT_8)
  #undef       PROVAD_STOP_SEC_VAR_NO_INIT_8
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (PROVAD_START_SEC_VAR_NO_INIT_16)
  #undef       PROVAD_START_SEC_VAR_NO_INIT_16
  // TEST //#pragma ghs section bss=".bss.DEFAULT_RAM_VAR_NO_INIT"
  #pragma alignvar (2)
#elif defined (PROVAD_STOP_SEC_VAR_NO_INIT_16)
  #undef       PROVAD_STOP_SEC_VAR_NO_INIT_16
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (PROVAD_START_SEC_VAR_NO_INIT_32)
  #undef       PROVAD_START_SEC_VAR_NO_INIT_32
  // TEST //#pragma ghs section bss=".bss.DEFAULT_RAM_VAR_NO_INIT"
  #pragma alignvar (4)
#elif defined (PROVAD_STOP_SEC_VAR_NO_INIT_32)
  #undef       PROVAD_STOP_SEC_VAR_NO_INIT_32
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (PROVAD_START_SEC_VAR_NO_INIT_UNSPECIFIED)
  #undef       PROVAD_START_SEC_VAR_NO_INIT_UNSPECIFIED
  // TEST //#pragma ghs section bss=".bss.DEFAULT_RAM_VAR_NO_INIT"
  #pragma alignvar (4)
#elif defined (PROVAD_STOP_SEC_VAR_NO_INIT_UNSPECIFIED)
  #undef       PROVAD_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (PROVAD_START_SEC_VAR_INIT_BOOLEAN)
  #undef       PROVAD_START_SEC_VAR_INIT_BOOLEAN
  // TEST //#pragma ghs section data=".data.DEFAULT_RAM_VAR_INIT"
  #pragma alignvar (1)
#elif defined (PROVAD_STOP_SEC_VAR_INIT_BOOLEAN)
  #undef       PROVAD_STOP_SEC_VAR_INIT_BOOLEAN
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (PROVAD_START_SEC_VAR_INIT_8)
  #undef       PROVAD_START_SEC_VAR_INIT_8
  // TEST //#pragma ghs section data=".data.DEFAULT_RAM_VAR_INIT"
  #pragma alignvar (1)
#elif defined (PROVAD_STOP_SEC_VAR_INIT_8)
  #undef       PROVAD_STOP_SEC_VAR_INIT_8
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (PROVAD_START_SEC_VAR_INIT_16)
  #undef       PROVAD_START_SEC_VAR_INIT_16
  // TEST //#pragma ghs section data=".data.DEFAULT_RAM_VAR_INIT"
  #pragma alignvar (2)
#elif defined (PROVAD_STOP_SEC_VAR_INIT_16)
  #undef       PROVAD_STOP_SEC_VAR_INIT_16
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (PROVAD_START_SEC_VAR_INIT_32)
  #undef       PROVAD_START_SEC_VAR_INIT_32
  // TEST //#pragma ghs section data=".data.DEFAULT_RAM_VAR_INIT"
  #pragma alignvar (4)
#elif defined (PROVAD_STOP_SEC_VAR_INIT_32)
  #undef       PROVAD_STOP_SEC_VAR_INIT_32
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (PROVAD_START_SEC_VAR_INIT_UNSPECIFIED)
  #undef       PROVAD_START_SEC_VAR_INIT_UNSPECIFIED
  // TEST //#pragma ghs section data=".data.DEFAULT_RAM_VAR_INIT"
  #pragma alignvar (4)
#elif defined (PROVAD_STOP_SEC_VAR_INIT_UNSPECIFIED)
  #undef       PROVAD_STOP_SEC_VAR_INIT_UNSPECIFIED
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (PROVAD_START_SEC_CODE)
  #undef       PROVAD_START_SEC_CODE
  // TEST //#pragma ghs section text=".text.PROVAD_CODE"
  // TEST //#pragma ghs section rodata=".rodata.DEFAULT_ROM_CONST"
  // TEST //#pragma ghs section bss=".bss.DEFAULT_RAM_VAR_CLEARED"
  // TEST //#pragma ghs section data=".data.DEFAULT_RAM_VAR_INIT"
#elif defined (PROVAD_STOP_SEC_CODE)
  #undef       PROVAD_STOP_SEC_CODE
  // TEST //#pragma ghs section
/* -------------------------------------------------------------------------- /
/ MuxDemuxIf /
/ -------------------------------------------------------------------------- */
#elif defined (MuxDemuxIf_START_SEC_CODE)
#undef MuxDemuxIf_START_SEC_CODE
// TEST //#pragma ghs section text=".text.DEFAULT_CODE"
// TEST //#pragma ghs section rodata=".rodata.DEFAULT_ROM_CONST"
// TEST //#pragma ghs section bss=".bss.DEFAULT_RAM_VAR_CLEARED"
// TEST //#pragma ghs section data=".data.DEFAULT_RAM_VAR_INIT"
#elif defined (MuxDemuxIf_STOP_SEC_CODE)
#undef MuxDemuxIf_STOP_SEC_CODE
// TEST //#pragma ghs section
#elif defined (MuxDemuxIf_START_SEC_CONST_8)
#undef MuxDemuxIf_START_SEC_CONST_8
// TEST //#pragma ghs section rodata=".rodata.DEFAULT_ROM_CONST"
#elif defined (MuxDemuxIf_STOP_SEC_CONST_8)
#undef MuxDemuxIf_STOP_SEC_CONST_8
// TEST //#pragma ghs section
#elif defined (MuxDemuxIf_START_SEC_VAR_CLEARED_UNSPECIFIED)
 #undef MuxDemuxIf_START_SEC_VAR_CLEARED_UNSPECIFIED

// TEST //#pragma ghs section bss=".bss.DEFAULT_RAM_VAR_CLEARED"
#elif defined (MuxDemuxIf_STOP_SEC_VAR_CLEARED_UNSPECIFIED)
 #undef MuxDemuxIf_STOP_SEC_VAR_CLEARED_UNSPECIFIED
 // TEST //#pragma ghs section
#elif defined (MuxDemuxIf_START_SEC_CONST_UNSPECIFIED)
 #undef MuxDemuxIf_START_SEC_CONST_UNSPECIFIED

// TEST //#pragma ghs section rodata=".rodata.DEFAULT_ROM_CONST"
#elif defined (MuxDemuxIf_STOP_SEC_CONST_UNSPECIFIED)
 #undef MuxDemuxIf_STOP_SEC_CONST_UNSPECIFIED
 // TEST //#pragma ghs section
/* -------------------------------------------------------------------------- */
/*                              Tm                                            */
/* -------------------------------------------------------------------------- */
#elif defined (TM_START_SEC_CODE)
  #undef       TM_START_SEC_CODE
  // TEST //#pragma ghs section text=".text.TM_CODE"
  // TEST //#pragma ghs section rodata=".rodata.TM_ROM_CONST_UNSPECIFIED"
  // TEST //#pragma ghs section bss=".bss.TM_RAM_VAR_CLEARED_UNSPECIFIED"
  // TEST //#pragma ghs section data=".data.TM_RAM_VAR_INIT_UNSPECIFIED"
#elif defined (TM_STOP_SEC_CODE)
  #undef       TM_STOP_SEC_CODE
  // TEST //#pragma ghs section
/* -------------------------------------------------------------------------- */
/*                              CanTSyn                                       */
/* -------------------------------------------------------------------------- */
#elif defined (CANTSYN_START_SEC_CODE)
  #undef       CANTSYN_START_SEC_CODE
  // TEST //#pragma ghs section text=".text.CANTSYN_CODE"
  // TEST //#pragma ghs section rodata=".rodata.CANTSYN_ROM_CONST_UNSPECIFIED"
  // TEST //#pragma ghs section bss=".bss.CANTSYN_RAM_VAR_CLEARED_UNSPECIFIED"
  // TEST //#pragma ghs section data=".data.CANTSYN_RAM_VAR_INIT_UNSPECIFIED"
#elif defined (CANTSYN_STOP_SEC_CODE)
  #undef       CANTSYN_STOP_SEC_CODE
  // TEST //#pragma ghs section
#elif defined (CANTSYN_START_SEC_CONST_8)
  #undef       CANTSYN_START_SEC_CONST_8
  // TEST //#pragma ghs section rodata=".rodata.CANTSYN_ROM_CONST_8"
#elif defined (CANTSYN_STOP_SEC_CONST_8)
  #undef       CANTSYN_STOP_SEC_CONST_8
  // TEST //#pragma ghs section
#elif defined (CANTSYN_START_SEC_CONST_UNSPECIFIED)
  #undef       CANTSYN_START_SEC_CONST_UNSPECIFIED
  // TEST //#pragma ghs section rodata=".rodata.CANTSYN_ROM_CONST_UNSPECIFIED"
#elif defined (CANTSYN_STOP_SEC_CONST_UNSPECIFIED)
  #undef       CANTSYN_STOP_SEC_CONST_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (CANTSYN_START_SEC_VAR_CLEARED_UNSPECIFIED)
  #undef       CANTSYN_START_SEC_VAR_CLEARED_UNSPECIFIED
  // TEST //#pragma ghs section bss=".bss.CANTSYN_RAM_VAR_CLEARED_UNSPECIFIED"
#elif defined (CANTSYN_STOP_SEC_VAR_CLEARED_UNSPECIFIED)
  #undef       CANTSYN_STOP_SEC_VAR_CLEARED_UNSPECIFIED
// TEST //#pragma ghs section
/* -------------------------------------------------------------------------- */
/*             StbM                                                           */
/* -------------------------------------------------------------------------- */
#elif defined (STBM_START_SEC_VAR_POWER_ON_CLEARED_BOOLEAN)
  #undef       STBM_START_SEC_VAR_POWER_ON_CLEARED_BOOLEAN
  // TEST //#pragma ghs section bss=".bss.STBM_RAM_VAR_POWER_ON_CLEARED_BOOLEAN"
#elif defined (STBM_STOP_SEC_VAR_POWER_ON_CLEARED_BOOLEAN)
  #undef       STBM_STOP_SEC_VAR_POWER_ON_CLEARED_BOOLEAN
  // TEST //#pragma ghs section
#elif defined (STBM_START_SEC_VAR_NO_INIT_BOOLEAN)
  #undef       STBM_START_SEC_VAR_NO_INIT_BOOLEAN
  // TEST //#pragma ghs section bss=".bss.STBM_RAM_VAR_NO_INIT_BOOLEAN"
#elif defined (STBM_STOP_SEC_VAR_NO_INIT_BOOLEAN)
  #undef       STBM_STOP_SEC_VAR_NO_INIT_BOOLEAN
  // TEST //#pragma ghs section
#elif defined (STBM_START_SEC_VAR_NO_INIT_8)
  #undef       STBM_START_SEC_VAR_NO_INIT_8
  // TEST //#pragma ghs section bss=".bss.STBM_RAM_VAR_NO_INIT_8"
#elif defined (STBM_STOP_SEC_VAR_NO_INIT_8)
  #undef       STBM_STOP_SEC_VAR_NO_INIT_8
  // TEST //#pragma ghs section
#elif defined (STBM_START_SEC_VAR_NO_INIT_16)
  #undef       STBM_START_SEC_VAR_NO_INIT_16
  // TEST //#pragma ghs section bss=".bss.STBM_RAM_VAR_NO_INIT_16"
#elif defined (STBM_STOP_SEC_VAR_NO_INIT_16)
  #undef       STBM_STOP_SEC_VAR_NO_INIT_16
  // TEST //#pragma ghs section
#elif defined (STBM_START_SEC_VAR_NO_INIT_32)
  #undef       STBM_START_SEC_VAR_NO_INIT_32
  // TEST //#pragma ghs section bss=".bss.STBM_RAM_VAR_NO_INIT_32"
#elif defined (STBM_STOP_SEC_VAR_NO_INIT_32)
  #undef       STBM_STOP_SEC_VAR_NO_INIT_32
  // TEST //#pragma ghs section
#elif defined (STBM_START_SEC_VAR_NO_INIT_UNSPECIFIED)
  #undef       STBM_START_SEC_VAR_NO_INIT_UNSPECIFIED
  // TEST //#pragma ghs section bss=".bss.STBM_RAM_VAR_NO_INIT_UNSPECIFIED"
#elif defined (STBM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED)
  #undef       STBM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (STBM_START_SEC_VAR_CLEARED_BOOLEAN)
  #undef       STBM_START_SEC_VAR_CLEARED_BOOLEAN
  // TEST //#pragma ghs section bss=".bss.STBM_RAM_VAR_CLEARED_BOOLEAN"
#elif defined (STBM_STOP_SEC_VAR_CLEARED_BOOLEAN)
  #undef       STBM_STOP_SEC_VAR_CLEARED_BOOLEAN
  // TEST //#pragma ghs section
#elif defined (STBM_START_SEC_VAR_CLEARED_8)
  #undef       STBM_START_SEC_VAR_CLEARED_8
  // TEST //#pragma ghs section bss=".bss.STBM_RAM_VAR_CLEARED_8"
#elif defined (STBM_STOP_SEC_VAR_CLEARED_8)
  #undef       STBM_STOP_SEC_VAR_CLEARED_8
  // TEST //#pragma ghs section
#elif defined (STBM_START_SEC_VAR_CLEARED_16)
  #undef       STBM_START_SEC_VAR_CLEARED_16
  // TEST //#pragma ghs section bss=".bss.STBM_RAM_VAR_CLEARED_16"
#elif defined (STBM_STOP_SEC_VAR_CLEARED_16)
  #undef       STBM_STOP_SEC_VAR_CLEARED_16
  // TEST //#pragma ghs section
#elif defined (STBM_START_SEC_VAR_CLEARED_32)
  #undef       STBM_START_SEC_VAR_CLEARED_32
  // TEST //#pragma ghs section bss=".bss.STBM_RAM_VAR_CLEARED_32"
#elif defined (STBM_STOP_SEC_VAR_CLEARED_32)
  #undef       STBM_STOP_SEC_VAR_CLEARED_32
  // TEST //#pragma ghs section
#elif defined (STBM_START_SEC_VAR_CLEARED_UNSPECIFIED)
  #undef       STBM_START_SEC_VAR_CLEARED_UNSPECIFIED
  // TEST //#pragma ghs section bss=".bss.STBM_RAM_VAR_CLEARED_UNSPECIFIED"
#elif defined (STBM_STOP_SEC_VAR_CLEARED_UNSPECIFIED)
  #undef       STBM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (STBM_START_SEC_VAR_INIT_BOOLEAN)
  #undef       STBM_START_SEC_VAR_INIT_BOOLEAN
  // TEST //#pragma ghs section data=".data.STBM_RAM_VAR_INIT_BOOLEAN"
#elif defined (STBM_STOP_SEC_VAR_INIT_BOOLEAN)
  #undef       STBM_STOP_SEC_VAR_INIT_BOOLEAN
  // TEST //#pragma ghs section
#elif defined (STBM_START_SEC_VAR_INIT_8)
  #undef       STBM_START_SEC_VAR_INIT_8
  // TEST //#pragma ghs section data=".data.STBM_RAM_VAR_INIT_8"
#elif defined (STBM_STOP_SEC_VAR_INIT_8)
  #undef       STBM_STOP_SEC_VAR_INIT_8
  // TEST //#pragma ghs section
#elif defined (STBM_START_SEC_VAR_INIT_16)
  #undef       STBM_START_SEC_VAR_INIT_16
  // TEST //#pragma ghs section data=".data.STBM_RAM_VAR_INIT_16"
#elif defined (STBM_STOP_SEC_VAR_INIT_16)
  #undef       STBM_STOP_SEC_VAR_INIT_16
  // TEST //#pragma ghs section
#elif defined (STBM_START_SEC_VAR_INIT_32)
  #undef       STBM_START_SEC_VAR_INIT_32
  // TEST //#pragma ghs section data=".data.STBM_RAM_VAR_INIT_32"
#elif defined (STBM_STOP_SEC_VAR_INIT_32)
  #undef       STBM_STOP_SEC_VAR_INIT_32
  // TEST //#pragma ghs section
#elif defined (STBM_START_SEC_VAR_INIT_UNSPECIFIED)
  #undef       STBM_START_SEC_VAR_INIT_UNSPECIFIED
  // TEST //#pragma ghs section data=".data.STBM_RAM_VAR_INIT_UNSPECIFIED"
#elif defined (STBM_STOP_SEC_VAR_INIT_UNSPECIFIED)
  #undef       STBM_STOP_SEC_VAR_INIT_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (STBM_START_SEC_CONST_BOOLEAN)
  #undef       STBM_START_SEC_CONST_BOOLEAN
  // TEST //#pragma ghs section rodata=".rodata.STBM_ROM_CONST_BOOLEAN"
#elif defined (STBM_STOP_SEC_CONST_BOOLEAN)
  #undef       STBM_STOP_SEC_CONST_BOOLEAN
  // TEST //#pragma ghs section
#elif defined (STBM_START_SEC_CONST_8)
  #undef       STBM_START_SEC_CONST_8
  // TEST //#pragma ghs section rodata=".rodata.STBM_ROM_CONST_8"
#elif defined (STBM_STOP_SEC_CONST_8)
  #undef       STBM_STOP_SEC_CONST_8
  // TEST //#pragma ghs section
#elif defined (STBM_START_SEC_CONST_16)
  #undef       STBM_START_SEC_CONST_16
  // TEST //#pragma ghs section rodata=".rodata.STBM_ROM_CONST_16"
#elif defined (STBM_STOP_SEC_CONST_16)
  #undef       STBM_STOP_SEC_CONST_16
  // TEST //#pragma ghs section
#elif defined (STBM_START_SEC_CONST_UNSPECIFIED)
  #undef       STBM_START_SEC_CONST_UNSPECIFIED
  // TEST //#pragma ghs section rodata=".rodata.STBM_ROM_CONST_UNSPECIFIED"
#elif defined (STBM_STOP_SEC_CONST_UNSPECIFIED)
  #undef       STBM_STOP_SEC_CONST_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (STBM_START_SEC_CODE)
  #undef       STBM_START_SEC_CODE
  // TEST //#pragma ghs section text=".text.STBM_CODE"
  // TEST //#pragma ghs section rodata=".rodata.STBM_ROM_CONST_UNSPECIFIED"
  // TEST //#pragma ghs section bss=".bss.STBM_RAM_VAR_CLEARED_UNSPECIFIED"
  // TEST //#pragma ghs section data=".data.STBM_RAM_VAR_INIT_UNSPECIFIED"
#elif defined (STBM_STOP_SEC_CODE)
  #undef       STBM_STOP_SEC_CODE
  // TEST //#pragma ghs section
#elif defined (STBM_START_SEC_CALLOUT_CODE)
  #undef       STBM_START_SEC_CALLOUT_CODE
  // TEST //#pragma ghs section text=".text.STBM_CODE"
  // TEST //#pragma ghs section rodata=".rodata.STBM_ROM_CONST_UNSPECIFIED"
  // TEST //#pragma ghs section bss=".bss.STBM_RAM_VAR_CLEARED_UNSPECIFIED"
  // TEST //#pragma ghs section data=".data.STBM_RAM_VAR_INIT_UNSPECIFIED"
#elif defined (STBM_STOP_SEC_CALLOUT_CODE)
  #undef       STBM_STOP_SEC_CALLOUT_CODE
  // TEST //#pragma ghs section
/* --------------------------------------------------------------------------*/
/*                               LDCOM                                       */
/* --------------------------------------------------------------------------*/
/* To be used for code section */
#elif defined (LDCOM_START_SEC_CODE)
  #undef LDCOM_START_SEC_CODE
  // TEST //#pragma ghs section text=".text.LDCOM_CODE"
  // TEST //#pragma ghs section rodata=".rodata.LDCOM_ROM_CONST_UNSPECIFIED"
  // TEST //#pragma ghs section bss=".bss.LDCOM_RAM_VAR_CLEARED_UNSPECIFIED"
  // TEST //#pragma ghs section data=".data.LDCOM_RAM_VAR_INIT_UNSPECIFIED"
#elif defined (LDCOM_STOP_SEC_CODE)
  #undef LDCOM_STOP_SEC_CODE
  // TEST //#pragma ghs section
/* To be used for initializing variables */
#elif defined (LDCOM_START_SEC_VAR_CLEARED_BOOLEAN)
  #undef LDCOM_START_SEC_VAR_CLEARED_BOOLEAN
  // TEST //#pragma ghs section bss=".bss.LDCOM_RAM_VAR_CLEARED_BOOLEAN"
#elif defined (LDCOM_STOP_SEC_VAR_CLEARED_BOOLEAN)
  #undef LDCOM_STOP_SEC_VAR_CLEARED_BOOLEAN
  // TEST //#pragma ghs section
/*To be used for code section */
#elif defined (LDCOM_START_SEC_VAR_CLEARED_UNSPECIFIED)
  #undef LDCOM_START_SEC_VAR_CLEARED_UNSPECIFIED
  // TEST //#pragma ghs section bss=".bss.LDCOM_RAM_VAR_CLEARED_UNSPECIFIED"
#elif defined (LDCOM_STOP_SEC_VAR_CLEARED_UNSPECIFIED)
  #undef LDCOM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
  // TEST //#pragma ghs section
#elif defined (LDCOM_START_SEC_CONST_UNSPECIFIED)
  #undef LDCOM_START_SEC_CONST_UNSPECIFIED
  // TEST //#pragma ghs section rodata=".rodata.LDCOM_ROM_CONST_UNSPECIFIED"
#elif defined (LDCOM_STOP_SEC_CONST_UNSPECIFIED)
  #undef LDCOM_STOP_SEC_CONST_UNSPECIFIED
  // TEST //#pragma ghs section
/* -------------------------------------------------------------------------- */
/*                                DATALOG                                     */
/* -------------------------------------------------------------------------- */
#elif defined (DATALOG_START_SEC_VAR_CLEARED_BOOLEAN)
  #undef       DATALOG_START_SEC_VAR_CLEARED_BOOLEAN
  // TEST //#pragma ghs section bss=".bss.DATALOG_RAM_VAR_CLEARED"
  #pragma alignvar (1)
#elif defined (DATALOG_STOP_SEC_VAR_CLEARED_BOOLEAN)
  #undef       DATALOG_STOP_SEC_VAR_CLEARED_BOOLEAN
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (DATALOG_START_SEC_VAR_CLEARED_8)
  #undef       DATALOG_START_SEC_VAR_CLEARED_8
  // TEST //#pragma ghs section bss=".bss.DATALOG_RAM_VAR_CLEARED"
  #pragma alignvar (1)
#elif defined (DATALOG_STOP_SEC_VAR_CLEARED_8)
  #undef       DATALOG_STOP_SEC_VAR_CLEARED_8
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (DATALOG_START_SEC_VAR_CLEARED_32)
  #undef       DATALOG_START_SEC_VAR_CLEARED_32
  // TEST //#pragma ghs section bss=".bss.DATALOG_RAM_VAR_CLEARED"
  #pragma alignvar (4)
#elif defined (DATALOG_STOP_SEC_VAR_CLEARED_32)
  #undef       DATALOG_STOP_SEC_VAR_CLEARED_32
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (DATALOG_RMBA_START_SEC_VAR_CLEARED_32)
  #undef       DATALOG_RMBA_START_SEC_VAR_CLEARED_32
  // TEST //#pragma ghs section bss=".bss.DATALOG_RMBA_VAR_CLEARED"
  #pragma alignvar (4)
#elif defined (DATALOG_RMBA_STOP_SEC_VAR_CLEARED_32)
  #undef       DATALOG_RMBA_STOP_SEC_VAR_CLEARED_32
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (DATALOG_START_SEC_VAR_CLEARED_UNSPECIFIED)
  #undef       DATALOG_START_SEC_VAR_CLEARED_UNSPECIFIED
  #pragma alignvar (4)
  // TEST //#pragma ghs section bss=".bss.DATALOG_RAM_VAR_CLEARED"
#elif defined (DATALOG_STOP_SEC_VAR_CLEARED_UNSPECIFIED)
  #undef       DATALOG_STOP_SEC_VAR_CLEARED_UNSPECIFIED
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (DATALOG_START_SEC_VAR_NO_INIT_BOOLEAN)
  #undef       DATALOG_START_SEC_VAR_NO_INIT_BOOLEAN
  // TEST //#pragma ghs section bss=".bss.DATALOG_RAM_VAR_NO_INIT"
  #pragma alignvar (1)
#elif defined (DATALOG_STOP_SEC_VAR_NO_INIT_BOOLEAN)
  #undef       DATALOG_STOP_SEC_VAR_NO_INIT_BOOLEAN
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (DATALOG_START_SEC_VAR_NO_INIT_8)
  #undef       DATALOG_START_SEC_VAR_NO_INIT_8
  // TEST //#pragma ghs section bss=".bss.DATALOG_RAM_VAR_NO_INIT"
  #pragma alignvar (1)
#elif defined (DATALOG_STOP_SEC_VAR_NO_INIT_8)
  #undef       DATALOG_STOP_SEC_VAR_NO_INIT_8
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (DATALOG_START_SEC_VAR_NO_INIT_UNSPECIFIED)
  #undef       DATALOG_START_SEC_VAR_NO_INIT_UNSPECIFIED
  // TEST //#pragma ghs section bss=".bss.DATALOG_RAM_VAR_NO_INIT"
  #pragma alignvar (4)
#elif defined (DATALOG_STOP_SEC_VAR_NO_INIT_UNSPECIFIED)
  #undef       DATALOG_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (DATALOG_START_SEC_VAR_INIT_UNSPECIFIED)
  #undef       DATALOG_START_SEC_VAR_INIT_UNSPECIFIED
  // TEST //#pragma ghs section data=".data.DATALOG_RAM_VAR_INIT"
  #pragma alignvar (4)
#elif defined (DATALOG_STOP_SEC_VAR_INIT_UNSPECIFIED)
  #undef       DATALOG_STOP_SEC_VAR_INIT_UNSPECIFIED
  #pragma alignvar (4)
  // TEST //#pragma ghs section
#elif defined (DATALOG_START_SEC_CODE)
  #undef       DATALOG_START_SEC_CODE
  // TEST //#pragma ghs section text=".text.DATALOG_CODE"
  // TEST //#pragma ghs section rodata=".rodata.DATALOG_ROM_CONST_UNSPECIFIED"
  // TEST //#pragma ghs section bss=".bss.DATALOG_RAM_VAR_CLEARED_UNSPECIFIED"
  // TEST //#pragma ghs section data=".data.DATALOG_RAM_VAR_INIT_UNSPECIFIED"
#elif defined (DATALOG_STOP_SEC_CODE)
  #undef       DATALOG_STOP_SEC_CODE
  // TEST //#pragma ghs section
/******************************END*********************************************/

#else
  #define SECTION_NOT_FOUND
  
  #define OS_DO_NOT_RAISE_ERROR
  #if defined (SECTION_NOT_FOUND)
    #undef SECTION_NOT_FOUND
    #include "Os_MemMap.h"
  #endif
  #undef OS_DO_NOT_RAISE_ERROR
  
  #if defined (SECTION_NOT_FOUND)
    #undef SECTION_NOT_FOUND
    #include "Rte_MemMap.h"
  #endif

  #if defined (SECTION_NOT_FOUND)
    #undef SECTION_NOT_FOUND
    #include "Mcal_MemMap.h"
  #endif
  
  #if defined (SECTION_NOT_FOUND)
    #undef SECTION_NOT_FOUND
    #include "User_MemMap.h"
  #endif
  
  #if defined (SECTION_NOT_FOUND)
    #error "MemMap.h: No valid section define found"
  #endif
#endif  /* START_WITH_IF */
/* -------------------------------------------------------------------------- */
/* End of module section mapping                                              */
/* -------------------------------------------------------------------------- */

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/

/*******************************************************************************
* PRE-JUSTIFICATION END SECTION (MISRA-C RULE CHECKER)
*******************************************************************************/
/* polyspace:end<MISRA-C:19.6:Not a defect:Justify with annotations> No Impact of this rule violation (AUTOSAR Standard : Memory Mapping) */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
