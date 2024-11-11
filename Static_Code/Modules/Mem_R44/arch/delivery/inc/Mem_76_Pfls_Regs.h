/*******************************************************************************
**                                                                            **
**  (C) 2022 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  This source code is permitted to be used only in projects contracted      **
**  with Hyundai Autoever, and any other use is prohibited.                   **
**  If you use it for other purposes or change the source code,               **
**  you may take legal responsibility.                                        **
**  In this case, There is no warranty and technical support.                 **
**                                                                            **
**  SRC-MODULE: Mem_76_Pfls_Regs.h                                            **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Memory Driver                                         **
**                                                                            **
**  PURPOSE   : Provide all marcos for internal module                        **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By                        Description              **
********************************************************************************
** 1.0.0     13-Sep-2022   LinhTT36                  Redmine #35543           **
*******************************************************************************/
#ifndef MEM_76_PFLS_REGS_H
#define MEM_76_PFLS_REGS_H
/*******************************************************************************
**                      Include Section                                       **
********************************************************************************/

/*******************************************************************************
**                     Global Type  definition                                **
********************************************************************************/
/* total number of block within Pflash memory - MCU dependent*/
#if((MEM_76_PFLS_SUPPORT_MCU ==MEM_76_PFLS_MCU_S32K312) | (MEM_76_PFLS_SUPPORT_MCU ==MEM_76_PFLS_MCU_S32K311))
#define MEM_76_PFLS_BLOCK_COUNT                                 2u
#elif(MEM_76_PFLS_SUPPORT_MCU ==MEM_76_PFLS_MCU_S32K314)
#define MEM_76_PFLS_BLOCK_COUNT                                 4u
#endif

#if(MEM_76_PFLS_SUPPORT_MCU ==MEM_76_PFLS_MCU_S32K311)
#define MEM_76_PFLS_B_BANK_OFFSET                          0x00100000UL
#elif(MEM_76_PFLS_SUPPORT_MCU ==MEM_76_PFLS_MCU_S32K312)
#define MEM_76_PFLS_B_BANK_OFFSET                          0x00100000UL
#elif(MEM_76_PFLS_SUPPORT_MCU ==MEM_76_PFLS_MCU_S32K314)
#define MEM_76_PFLS_B_BANK_OFFSET                          0x00200000UL
#endif

/* cycle of write command */
#define MEM_76_PFLS_GET_CYCLE_OF_WRITE_COMMAND(writeSize)      (writeSize / 32U)
/* a program/erase sector consist of 8KB */
#define MEM_76_PFLS_SECTOR_SIZE                                 (8192u)
/* super sector size - 64KB = 65536 bytes  */
#define MEM_76_PFLS_SUPER_SECTOR_SIZE                          (65536u)
/** FLASH - Size of Registers Arrays */
#define MEM_76_PFLS_FLASH_UM_COUNT                                           9u
#define MEM_76_PFLS_FLASH_DATA_COUNT                                        32u

/** PFLASH (Flash Memory Controller) - Size of Registers Arrays */
#define MEM_76_PFLS_PFLASH_PFCRI_COUNT                                        3u
#define MEM_76_PFLS_PFLASH_PFCBLKI_SPELOCK_COUNT                              3u
#define MEM_76_PFLS_PFCBLKU_SPELOCK_COUNT                                     1u
#define MEM_76_PFLS_PFLASH_PFCBLKI_SSPELOCK_COUNT                             2u
#define MEM_76_PFLS_PFLASH_PFCBLKI_SETSLOCK_COUNT                             3u
#define MEM_76_PFLS_PFCBLKU_SETSLOCK_COUNT                                    1u
#define MEM_76_PFLS_PFLASH_PFCBLKI_SSETSLOCK_COUNT                            2u
#define MEM_76_PFLS_PFLASH_PFCBLKI_LOCKMASTER_S_COUNT                         3u
#define MEM_76_PFLS_PFLASH_PFCBLKI_LOCKMASTER_S_PFCBLKI_LOCKMASTER_SJ_COUNT   8u
#define MEM_76_PFLS_PFCBLKU_LOCKMASTER_S_COUNT                                1u
#define MEM_76_PFLS_PFLASH_PFCBLKI_LOCKMASTER_SS_PFCBLKI_LOCKMASTER_SSJ_COUNT 3u
#define MEM_76_PFLS_PFLASH_PFCBLKI_LOCKMASTER_SS_COUNT                        2u

/** Embedded Flash Memory - Register Layout Typedef */
typedef struct {
  volatile uint32       MCR;                               /**< Module Configuration, offset: 0x0 */
  volatile uint32       MCRS;                              /**< Module Configuration Status, offset: 0x4 */
  volatile const uint32 MCRE;                              /**< Extended Module Configuration, offset: 0x8 */
  volatile uint32       CTL;                               /**< Module Control, offset: 0xC */
  volatile uint32       ADR;                               /**< Address, offset: 0x10 */
  volatile const uint32 PEADR;                             /**< Program and Erase Address, offset: 0x14 */
  uint8                 RESERVED_0[56];
  volatile const uint32 SPELOCK;                           /**< Sector Program and Erase Hardware Lock, offset: 0x50 */
  volatile const uint32 SSPELOCK;                          /**< Super Sector Program and Erase Hardware Lock, offset: 0x54 */
  uint8                 RESERVED_1[24];
  volatile const uint32 XSPELOCK;                          /**< Express Sector Program and Erase Hardware Lock, offset: 0x70 */
  volatile const uint32 XSSPELOCK;                         /**< Express Super Sector Program and Erase Hardware Lock, offset: 0x74 */
  uint8                 RESERVED_2[24];
  volatile uint32       TMD;                               /**< Test Mode Disable Password Check, offset: 0x90 */
  volatile uint32       UT0;                               /**< UTest 0, offset: 0x94 */
  volatile uint32       UM[MEM_76_PFLS_FLASH_UM_COUNT];    /**< UMISRn, array offset: 0x98, array step: 0x4 */
  volatile uint32       UM9;                               /**< UMISR9, offset: 0xBC */
  uint8                 RESERVED_3[16];
  volatile uint32       UD0;                               /**< UTest Data 0, offset: 0xD0 */
  volatile uint32       UD1;                               /**< UTest Data 1, offset: 0xD4 */
  volatile uint32       UD2;                               /**< UTest Data 2, offset: 0xD8 */
  volatile uint32       UD3;                               /**< UTest Data 3, offset: 0xDC */
  volatile uint32       UD4;                               /**< UTest Data 4, offset: 0xE0 */
  volatile uint32       UD5;                               /**< UTest Data 5, offset: 0xE4 */
  volatile uint32       UA0;                               /**< UTest Address 0, offset: 0xE8 */
  volatile uint32       UA1;                               /**< UTest Address 1, offset: 0xEC */
  volatile uint32       XMCR;                              /**< Express Module Configuration, offset: 0xF0 */
  volatile const uint32 XPEADR;                            /**< Express Program Address, offset: 0xF4 */
  uint8                 RESERVED_4[8];
  volatile uint32       DATA[MEM_76_PFLS_FLASH_DATA_COUNT];/**< Program Data, array offset: 0x100, array step: 0x4 */
} FLASH_Type, *FLASH_MemMapPtr;

/** PFLASH - Flash Memory Controller- Register Layout Typedef */
typedef struct {
  volatile uint32       PFCR[MEM_76_PFLS_PFLASH_PFCRI_COUNT];          /**< Platform Flash Memory Configuration 0..Platform Flash Memory Configuration 2, array offset: 0x0, array step: 0x4 */
  uint8                 RESERVED_0[4];
  volatile uint32       PFCR4;                             /**< Platform Flash Memory Configuration 4, offset: 0x10 */
  volatile uint32       PFAPR;                             /**< Platform Flash Memory Access Protection, offset: 0x14 */
  uint8                 RESERVED_1[744];
  volatile uint32       PFCPGM_PEADR_L;                    /**< Platform Flash Memory Program Erase Address Logical, offset: 0x300 */
  volatile const uint32 PFCPGM_PEADR_P;                    /**< Platform Flash Memory Program Erase Address Physical, offset: 0x304 */
  volatile uint32       PFCPGM_XPEADR_L;                   /**< Platform Flash Memory Express Program Erase Address Logical, offset: 0x308 */
  volatile const uint32 PFCPGM_XPEADR_P;                   /**< Platform Flash Memory Express Program Erase Address Physical, offset: 0x30C */
  uint8                 RESERVED_2[48];
  volatile uint32       PFCBLK_SPELOCK[MEM_76_PFLS_PFLASH_PFCBLKI_SPELOCK_COUNT]; /**< Block n Sector Program Erase Lock, array offset: 0x340, array step: 0x4 */
  uint8                 RESERVED_3[12];
  volatile uint32       PFCBLKU_SPELOCK[MEM_76_PFLS_PFCBLKU_SPELOCK_COUNT]; /**< Block UTEST Sector Program Erase Lock, array offset: 0x358, array step: 0x4 */
  volatile uint32       PFCBLK_SSPELOCK[MEM_76_PFLS_PFLASH_PFCBLKI_SSPELOCK_COUNT]; /**< Block n Super Sector Program Erase Lock, array offset: 0x35C, array step: 0x4 */
  uint8                 RESERVED_4[28];
  volatile uint32       PFCBLK_SETSLOCK[MEM_76_PFLS_PFLASH_PFCBLKI_SETSLOCK_COUNT]; /**< Block n Set Sector Lock, array offset: 0x380, array step: 0x4 */
  uint8                 RESERVED_5[12];
  volatile uint32       PFCBLKU_SETSLOCK[MEM_76_PFLS_PFCBLKU_SETSLOCK_COUNT]; /**< Block UTEST Set Sector Lock, array offset: 0x398, array step: 0x4 */
  volatile uint32       PFCBLK_SSETSLOCK[MEM_76_PFLS_PFLASH_PFCBLKI_SSETSLOCK_COUNT]; /**< Block n Set Super Sector Lock, array offset: 0x39C, array step: 0x4 */
  uint8                 RESERVED_6[28];
  volatile const uint32 PFCBLK_LOCKMASTER_S[MEM_76_PFLS_PFLASH_PFCBLKI_LOCKMASTER_S_COUNT][MEM_76_PFLS_PFLASH_PFCBLKI_LOCKMASTER_S_PFCBLKI_LOCKMASTER_SJ_COUNT]; /**< Block a Lock Master Sector b, array offset: 0x3C0, array step: index*0x20, index2*0x4 */
  uint8                 RESERVED_7[96];
  volatile const uint32 PFCBLKU_LOCKMASTER_S[MEM_76_PFLS_PFCBLKU_LOCKMASTER_S_COUNT]; /**< Block UTEST Lock Master Sector, array offset: 0x480, array step: 0x4 */
  struct {                                         /* offset: 0x484, array step: 0x10 */
     volatile const uint32 PFCBLK_LOCKMASTER_SS[MEM_76_PFLS_PFLASH_PFCBLKI_LOCKMASTER_SS_PFCBLKI_LOCKMASTER_SSJ_COUNT];   /**< Block m Lock Master Super Sector n, array offset: 0x484, array step: index*0x10, index2*0x4 */
     uint8                 RESERVED_0[4];
  } PFCBLKI_LOCKMASTER_SS[MEM_76_PFLS_PFLASH_PFCBLKI_LOCKMASTER_SS_COUNT];
} PFLASH_Type, *PFLASH_MemMapPtr;
/*******************************************************************************
**                      Macro definition                                      **
********************************************************************************/

/* FLASH - Peripheral instance base addresses */
/** Peripheral FLASH base address */
#define MEM_76_PFLS_FLASH_BASE                            (0x402EC000u)
/** Peripheral FLASH base pointer */
#define MEM_76_PFLS_FLASH                                 ((FLASH_Type *)MEM_76_PFLS_FLASH_BASE)
/** Array initializer of FLASH peripheral base addresses */
#define MEM_76_PFLS_FLASH_BASE_ADDRS                      { MEM_76_PFLS_FLASH_BASE }
/** Array initializer of FLASH peripheral base pointers */
#define MEM_76_PFLS_FLASH_BASE_PTRS                       { MEM_76_PFLS_FLASH }

/* PFLASH - Peripheral instance base addresses */
/** Peripheral PFLASH base address */
#define MEM_76_PFLS_PFLASH_BASE                           (0x40268000u)
/** Peripheral PFLASH base pointer */
#define MEM_76_PFLS_PFLASH                                ((PFLASH_Type *)MEM_76_PFLS_PFLASH_BASE)
/** Array initializer of PFLASH peripheral base addresses */
#define MEM_76_PFLS_PFLASH_BASE_ADDRS                     { MEM_76_PFLS_PFLASH_BASE }
/** Array initializer of PFLASH peripheral base pointers */
#define MEM_76_PFLS_PFLASH_BASE_PTRS                      { MEM_76_PFLS_PFLASH }

/* ----------------------------------------------------------------------------
   -- FLASH Register Masks - Embedded Flash Memory
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup FLASH_Register_Masks FLASH Register Masks
 * @{
 */

/*! @name MCR - Module Configuration */
/*! @{ */

#define MEM_76_PFLS_FLASH_MCR_EHV_MASK                       (0x1U)
#define MEM_76_PFLS_FLASH_MCR_EHV_SHIFT                      (0U)
#define MEM_76_PFLS_FLASH_MCR_EHV_WIDTH                      (1U)
#define MEM_76_PFLS_FLASH_MCR_EHV(x)                         (((uint32_t)(((uint32_t)(x)) << FLASH_MCR_EHV_SHIFT)) & FLASH_MCR_EHV_MASK)

#define MEM_76_PFLS_FLASH_MCR_ERS_MASK                       (0x10U)
#define MEM_76_PFLS_FLASH_MCR_ERS_SHIFT                      (4U)
#define MEM_76_PFLS_FLASH_MCR_ERS_WIDTH                      (1U)
#define MEM_76_PFLS_FLASH_MCR_ERS(x)                         (((uint32_t)(((uint32_t)(x)) << FLASH_MCR_ERS_SHIFT)) & FLASH_MCR_ERS_MASK)

#define MEM_76_PFLS_FLASH_MCR_ESS_MASK                       (0x20U)
#define MEM_76_PFLS_FLASH_MCR_ESS_SHIFT                      (5U)
#define MEM_76_PFLS_FLASH_MCR_ESS_WIDTH                      (1U)
#define MEM_76_PFLS_FLASH_MCR_ESS(x)                         (((uint32_t)(((uint32_t)(x)) << FLASH_MCR_ESS_SHIFT)) & FLASH_MCR_ESS_MASK)

#define MEM_76_PFLS_FLASH_MCR_PGM_MASK                       (0x100U)
#define MEM_76_PFLS_FLASH_MCR_PGM_SHIFT                      (8U)
#define MEM_76_PFLS_FLASH_MCR_PGM_WIDTH                      (1U)
#define MEM_76_PFLS_FLASH_MCR_PGM(x)                         (((uint32_t)(((uint32_t)(x)) << FLASH_MCR_PGM_SHIFT)) & FLASH_MCR_PGM_MASK)

#define MEM_76_PFLS_FLASH_MCR_WDIE_MASK                      (0x1000U)
#define MEM_76_PFLS_FLASH_MCR_WDIE_SHIFT                     (12U)
#define MEM_76_PFLS_FLASH_MCR_WDIE_WIDTH                     (1U)
#define MEM_76_PFLS_FLASH_MCR_WDIE(x)                        (((uint32_t)(((uint32_t)(x)) << FLASH_MCR_WDIE_SHIFT)) & FLASH_MCR_WDIE_MASK)

#define MEM_76_PFLS_FLASH_MCR_PECIE_MASK                     (0x8000U)
#define MEM_76_PFLS_FLASH_MCR_PECIE_SHIFT                    (15U)
#define MEM_76_PFLS_FLASH_MCR_PECIE_WIDTH                    (1U)
#define MEM_76_PFLS_FLASH_MCR_PECIE(x)                       (((uint32_t)(((uint32_t)(x)) << FLASH_MCR_PECIE_SHIFT)) & FLASH_MCR_PECIE_MASK)

#define MEM_76_PFLS_FLASH_MCR_PEID_MASK                      (0xFF0000U)
#define MEM_76_PFLS_FLASH_MCR_PEID_SHIFT                     (16U)
#define MEM_76_PFLS_FLASH_MCR_PEID_WIDTH                     (8U)
#define MEM_76_PFLS_FLASH_MCR_PEID(x)                        (((uint32_t)(((uint32_t)(x)) << FLASH_MCR_PEID_SHIFT)) & FLASH_MCR_PEID_MASK)
/*! @} */

/*! @name MCRS - Module Configuration Status */
/*! @{ */

#define MEM_76_PFLS_FLASH_MCRS_RE_MASK                       (0x1U)
#define MEM_76_PFLS_FLASH_MCRS_RE_SHIFT                      (0U)
#define MEM_76_PFLS_FLASH_MCRS_RE_WIDTH                      (1U)
#define MEM_76_PFLS_FLASH_MCRS_RE(x)                         (((uint32_t)(((uint32_t)(x)) << FLASH_MCRS_RE_SHIFT)) & FLASH_MCRS_RE_MASK)

#define MEM_76_PFLS_FLASH_MCRS_TSPELOCK_MASK                 (0x100U)
#define MEM_76_PFLS_FLASH_MCRS_TSPELOCK_SHIFT                (8U)
#define MEM_76_PFLS_FLASH_MCRS_TSPELOCK_WIDTH                (1U)
#define MEM_76_PFLS_FLASH_MCRS_TSPELOCK(x)                   (((uint32_t)(((uint32_t)(x)) << FLASH_MCRS_TSPELOCK_SHIFT)) & FLASH_MCRS_TSPELOCK_MASK)

#define MEM_76_PFLS_FLASH_MCRS_EPEG_MASK                     (0x200U)
#define MEM_76_PFLS_FLASH_MCRS_EPEG_SHIFT                    (9U)
#define MEM_76_PFLS_FLASH_MCRS_EPEG_WIDTH                    (1U)
#define MEM_76_PFLS_FLASH_MCRS_EPEG(x)                       (((uint32_t)(((uint32_t)(x)) << FLASH_MCRS_EPEG_SHIFT)) & FLASH_MCRS_EPEG_MASK)

#define MEM_76_PFLS_FLASH_MCRS_WDI_MASK                      (0x1000U)
#define MEM_76_PFLS_FLASH_MCRS_WDI_SHIFT                     (12U)
#define MEM_76_PFLS_FLASH_MCRS_WDI_WIDTH                     (1U)
#define MEM_76_PFLS_FLASH_MCRS_WDI(x)                        (((uint32_t)(((uint32_t)(x)) << FLASH_MCRS_WDI_SHIFT)) & FLASH_MCRS_WDI_MASK)

#define MEM_76_PFLS_FLASH_MCRS_PEG_MASK                      (0x4000U)
#define MEM_76_PFLS_FLASH_MCRS_PEG_SHIFT                     (14U)
#define MEM_76_PFLS_FLASH_MCRS_PEG_WIDTH                     (1U)
#define MEM_76_PFLS_FLASH_MCRS_PEG(x)                        (((uint32_t)(((uint32_t)(x)) << FLASH_MCRS_PEG_SHIFT)) & FLASH_MCRS_PEG_MASK)

#define MEM_76_PFLS_FLASH_MCRS_DONE_MASK                     (0x8000U)
#define MEM_76_PFLS_FLASH_MCRS_DONE_SHIFT                    (15U)
#define MEM_76_PFLS_FLASH_MCRS_DONE_WIDTH                    (1U)
#define MEM_76_PFLS_FLASH_MCRS_DONE(x)                       (((uint32_t)(((uint32_t)(x)) << FLASH_MCRS_DONE_SHIFT)) & FLASH_MCRS_DONE_MASK)

#define MEM_76_PFLS_FLASH_MCRS_PES_MASK                      (0x10000U)
#define MEM_76_PFLS_FLASH_MCRS_PES_SHIFT                     (16U)
#define MEM_76_PFLS_FLASH_MCRS_PES_WIDTH                     (1U)
#define MEM_76_PFLS_FLASH_MCRS_PES(x)                        (((uint32_t)(((uint32_t)(x)) << FLASH_MCRS_PES_SHIFT)) & FLASH_MCRS_PES_MASK)

#define MEM_76_PFLS_FLASH_MCRS_PEP_MASK                      (0x20000U)
#define MEM_76_PFLS_FLASH_MCRS_PEP_SHIFT                     (17U)
#define MEM_76_PFLS_FLASH_MCRS_PEP_WIDTH                     (1U)
#define MEM_76_PFLS_FLASH_MCRS_PEP(x)                        (((uint32_t)(((uint32_t)(x)) << FLASH_MCRS_PEP_SHIFT)) & FLASH_MCRS_PEP_MASK)

#define MEM_76_PFLS_FLASH_MCRS_RWE_MASK                      (0x100000U)
#define MEM_76_PFLS_FLASH_MCRS_RWE_SHIFT                     (20U)
#define MEM_76_PFLS_FLASH_MCRS_RWE_WIDTH                     (1U)
#define MEM_76_PFLS_FLASH_MCRS_RWE(x)                        (((uint32_t)(((uint32_t)(x)) << FLASH_MCRS_RWE_SHIFT)) & FLASH_MCRS_RWE_MASK)

#define MEM_76_PFLS_FLASH_MCRS_RRE_MASK                      (0x1000000U)
#define MEM_76_PFLS_FLASH_MCRS_RRE_SHIFT                     (24U)
#define MEM_76_PFLS_FLASH_MCRS_RRE_WIDTH                     (1U)
#define MEM_76_PFLS_FLASH_MCRS_RRE(x)                        (((uint32_t)(((uint32_t)(x)) << FLASH_MCRS_RRE_SHIFT)) & FLASH_MCRS_RRE_MASK)

#define MEM_76_PFLS_FLASH_MCRS_RVE_MASK                      (0x2000000U)
#define MEM_76_PFLS_FLASH_MCRS_RVE_SHIFT                     (25U)
#define MEM_76_PFLS_FLASH_MCRS_RVE_WIDTH                     (1U)
#define MEM_76_PFLS_FLASH_MCRS_RVE(x)                        (((uint32_t)(((uint32_t)(x)) << FLASH_MCRS_RVE_SHIFT)) & FLASH_MCRS_RVE_MASK)

#define MEM_76_PFLS_FLASH_MCRS_EEE_MASK                      (0x10000000U)
#define MEM_76_PFLS_FLASH_MCRS_EEE_SHIFT                     (28U)
#define MEM_76_PFLS_FLASH_MCRS_EEE_WIDTH                     (1U)
#define MEM_76_PFLS_FLASH_MCRS_EEE(x)                        (((uint32_t)(((uint32_t)(x)) << FLASH_MCRS_EEE_SHIFT)) & FLASH_MCRS_EEE_MASK)

#define MEM_76_PFLS_FLASH_MCRS_AEE_MASK                      (0x20000000U)
#define MEM_76_PFLS_FLASH_MCRS_AEE_SHIFT                     (29U)
#define MEM_76_PFLS_FLASH_MCRS_AEE_WIDTH                     (1U)
#define MEM_76_PFLS_FLASH_MCRS_AEE(x)                        (((uint32_t)(((uint32_t)(x)) << FLASH_MCRS_AEE_SHIFT)) & FLASH_MCRS_AEE_MASK)

#define MEM_76_PFLS_FLASH_MCRS_SBC_MASK                      (0x40000000U)
#define MEM_76_PFLS_FLASH_MCRS_SBC_SHIFT                     (30U)
#define MEM_76_PFLS_FLASH_MCRS_SBC_WIDTH                     (1U)
#define MEM_76_PFLS_FLASH_MCRS_SBC(x)                        (((uint32_t)(((uint32_t)(x)) << FLASH_MCRS_SBC_SHIFT)) & FLASH_MCRS_SBC_MASK)

#define MEM_76_PFLS_FLASH_MCRS_EER_MASK                      (0x80000000U)
#define MEM_76_PFLS_FLASH_MCRS_EER_SHIFT                     (31U)
#define MEM_76_PFLS_FLASH_MCRS_EER_WIDTH                     (1U)
#define MEM_76_PFLS_FLASH_MCRS_EER(x)                        (((uint32_t)(((uint32_t)(x)) << FLASH_MCRS_EER_SHIFT)) & FLASH_MCRS_EER_MASK)
/*! @} */

/*! @name MCRE - Extended Module Configuration */
/*! @{ */

#define MEM_76_PFLS_FLASH_MCRE_n256K_MASK                    (0xC0U)
#define MEM_76_PFLS_FLASH_MCRE_n256K_SHIFT                   (6U)
#define MEM_76_PFLS_FLASH_MCRE_n256K_WIDTH                   (2U)
#define MEM_76_PFLS_FLASH_MCRE_n256K(x)                      (((uint32_t)(((uint32_t)(x)) << FLASH_MCRE_n256K_SHIFT)) & FLASH_MCRE_n256K_MASK)

#define MEM_76_PFLS_FLASH_MCRE_n512K_MASK                    (0xC000U)
#define MEM_76_PFLS_FLASH_MCRE_n512K_SHIFT                   (14U)
#define MEM_76_PFLS_FLASH_MCRE_n512K_WIDTH                   (2U)
#define MEM_76_PFLS_FLASH_MCRE_n512K(x)                      (((uint32_t)(((uint32_t)(x)) << FLASH_MCRE_n512K_SHIFT)) & FLASH_MCRE_n512K_MASK)

#define MEM_76_PFLS_FLASH_MCRE_n1M_MASK                      (0xE00000U)
#define MEM_76_PFLS_FLASH_MCRE_n1M_SHIFT                     (21U)
#define MEM_76_PFLS_FLASH_MCRE_n1M_WIDTH                     (3U)
#define MEM_76_PFLS_FLASH_MCRE_n1M(x)                        (((uint32_t)(((uint32_t)(x)) << FLASH_MCRE_n1M_SHIFT)) & FLASH_MCRE_n1M_MASK)

#define MEM_76_PFLS_FLASH_MCRE_n2M_MASK                      (0xE0000000U)
#define MEM_76_PFLS_FLASH_MCRE_n2M_SHIFT                     (29U)
#define MEM_76_PFLS_FLASH_MCRE_n2M_WIDTH                     (3U)
#define MEM_76_PFLS_FLASH_MCRE_n2M(x)                        (((uint32_t)(((uint32_t)(x)) << FLASH_MCRE_n2M_SHIFT)) & FLASH_MCRE_n2M_MASK)
/*! @} */

/*! @name CTL - Module Control */
/*! @{ */

#define MEM_76_PFLS_FLASH_CTL_RWSC_MASK                      (0x1F00U)
#define MEM_76_PFLS_FLASH_CTL_RWSC_SHIFT                     (8U)
#define MEM_76_PFLS_FLASH_CTL_RWSC_WIDTH                     (5U)
#define MEM_76_PFLS_FLASH_CTL_RWSC(x)                        (((uint32_t)(((uint32_t)(x)) << FLASH_CTL_RWSC_SHIFT)) & FLASH_CTL_RWSC_MASK)

#define MEM_76_PFLS_FLASH_CTL_RWSL_MASK                      (0x8000U)
#define MEM_76_PFLS_FLASH_CTL_RWSL_SHIFT                     (15U)
#define MEM_76_PFLS_FLASH_CTL_RWSL_WIDTH                     (1U)
#define MEM_76_PFLS_FLASH_CTL_RWSL(x)                        (((uint32_t)(((uint32_t)(x)) << FLASH_CTL_RWSL_SHIFT)) & FLASH_CTL_RWSL_MASK)
/*! @} */

/*! @name ADR - Address */
/*! @{ */

#define MEM_76_PFLS_FLASH_ADR_ADDR_MASK                      (0x7FFFEU)
#define MEM_76_PFLS_FLASH_ADR_ADDR_SHIFT                     (1U)
#define MEM_76_PFLS_FLASH_ADR_ADDR_WIDTH                     (18U)
#define MEM_76_PFLS_FLASH_ADR_ADDR(x)                        (((uint32_t)(((uint32_t)(x)) << FLASH_ADR_ADDR_SHIFT)) & FLASH_ADR_ADDR_MASK)

#define MEM_76_PFLS_FLASH_ADR_A0_MASK                        (0x80000U)
#define MEM_76_PFLS_FLASH_ADR_A0_SHIFT                       (19U)
#define MEM_76_PFLS_FLASH_ADR_A0_WIDTH                       (1U)
#define MEM_76_PFLS_FLASH_ADR_A0(x)                          (((uint32_t)(((uint32_t)(x)) << FLASH_ADR_A0_SHIFT)) & FLASH_ADR_A0_MASK)

#define MEM_76_PFLS_FLASH_ADR_A1_MASK                        (0x100000U)
#define MEM_76_PFLS_FLASH_ADR_A1_SHIFT                       (20U)
#define MEM_76_PFLS_FLASH_ADR_A1_WIDTH                       (1U)
#define MEM_76_PFLS_FLASH_ADR_A1(x)                          (((uint32_t)(((uint32_t)(x)) << FLASH_ADR_A1_SHIFT)) & FLASH_ADR_A1_MASK)

#define MEM_76_PFLS_FLASH_ADR_A2_MASK                        (0x200000U)
#define MEM_76_PFLS_FLASH_ADR_A2_SHIFT                       (21U)
#define MEM_76_PFLS_FLASH_ADR_A2_WIDTH                       (1U)
#define MEM_76_PFLS_FLASH_ADR_A2(x)                          (((uint32_t)(((uint32_t)(x)) << FLASH_ADR_A2_SHIFT)) & FLASH_ADR_A2_MASK)

#define MEM_76_PFLS_FLASH_ADR_A5_MASK                        (0x1000000U)
#define MEM_76_PFLS_FLASH_ADR_A5_SHIFT                       (24U)
#define MEM_76_PFLS_FLASH_ADR_A5_WIDTH                       (1U)
#define MEM_76_PFLS_FLASH_ADR_A5(x)                          (((uint32_t)(((uint32_t)(x)) << FLASH_ADR_A5_SHIFT)) & FLASH_ADR_A5_MASK)

#define MEM_76_PFLS_FLASH_ADR_SAD_MASK                       (0x80000000U)
#define MEM_76_PFLS_FLASH_ADR_SAD_SHIFT                      (31U)
#define MEM_76_PFLS_FLASH_ADR_SAD_WIDTH                      (1U)
#define MEM_76_PFLS_FLASH_ADR_SAD(x)                         (((uint32_t)(((uint32_t)(x)) << FLASH_ADR_SAD_SHIFT)) & FLASH_ADR_SAD_MASK)
/*! @} */

/*! @name PEADR - Program and Erase Address */
/*! @{ */

#define MEM_76_PFLS_FLASH_PEADR_PEADDR_MASK                  (0x7FFE0U)
#define MEM_76_PFLS_FLASH_PEADR_PEADDR_SHIFT                 (5U)
#define MEM_76_PFLS_FLASH_PEADR_PEADDR_WIDTH                 (14U)
#define MEM_76_PFLS_FLASH_PEADR_PEADDR(x)                    (((uint32_t)(((uint32_t)(x)) << FLASH_PEADR_PEADDR_SHIFT)) & FLASH_PEADR_PEADDR_MASK)

#define MEM_76_PFLS_FLASH_PEADR_PEA0_MASK                    (0x80000U)
#define MEM_76_PFLS_FLASH_PEADR_PEA0_SHIFT                   (19U)
#define MEM_76_PFLS_FLASH_PEADR_PEA0_WIDTH                   (1U)
#define MEM_76_PFLS_FLASH_PEADR_PEA0(x)                      (((uint32_t)(((uint32_t)(x)) << FLASH_PEADR_PEA0_SHIFT)) & FLASH_PEADR_PEA0_MASK)

#define MEM_76_PFLS_FLASH_PEADR_PEA1_MASK                    (0x100000U)
#define MEM_76_PFLS_FLASH_PEADR_PEA1_SHIFT                   (20U)
#define MEM_76_PFLS_FLASH_PEADR_PEA1_WIDTH                   (1U)
#define MEM_76_PFLS_FLASH_PEADR_PEA1(x)                      (((uint32_t)(((uint32_t)(x)) << FLASH_PEADR_PEA1_SHIFT)) & FLASH_PEADR_PEA1_MASK)

#define MEM_76_PFLS_FLASH_PEADR_PEA2_MASK                    (0x200000U)
#define MEM_76_PFLS_FLASH_PEADR_PEA2_SHIFT                   (21U)
#define MEM_76_PFLS_FLASH_PEADR_PEA2_WIDTH                   (1U)
#define MEM_76_PFLS_FLASH_PEADR_PEA2(x)                      (((uint32_t)(((uint32_t)(x)) << FLASH_PEADR_PEA2_SHIFT)) & FLASH_PEADR_PEA2_MASK)

#define MEM_76_PFLS_FLASH_PEADR_PEA3_MASK                    (0x400000U)
#define MEM_76_PFLS_FLASH_PEADR_PEA3_SHIFT                   (22U)
#define MEM_76_PFLS_FLASH_PEADR_PEA3_WIDTH                   (1U)
#define MEM_76_PFLS_FLASH_PEADR_PEA3(x)                      (((uint32_t)(((uint32_t)(x)) << FLASH_PEADR_PEA3_SHIFT)) & FLASH_PEADR_PEA3_MASK)

#define MEM_76_PFLS_FLASH_PEADR_PEA4_MASK                    (0x800000U)
#define MEM_76_PFLS_FLASH_PEADR_PEA4_SHIFT                   (23U)
#define MEM_76_PFLS_FLASH_PEADR_PEA4_WIDTH                   (1U)
#define MEM_76_PFLS_FLASH_PEADR_PEA4(x)                      (((uint32_t)(((uint32_t)(x)) << FLASH_PEADR_PEA4_SHIFT)) & FLASH_PEADR_PEA4_MASK)

#define MEM_76_PFLS_FLASH_PEADR_PEA5_MASK                    (0x1000000U)
#define MEM_76_PFLS_FLASH_PEADR_PEA5_SHIFT                   (24U)
#define MEM_76_PFLS_FLASH_PEADR_PEA5_WIDTH                   (1U)
#define MEM_76_PFLS_FLASH_PEADR_PEA5(x)                      (((uint32_t)(((uint32_t)(x)) << FLASH_PEADR_PEA5_SHIFT)) & FLASH_PEADR_PEA5_MASK)

#define MEM_76_PFLS_FLASH_PEADR_PEASAD_MASK                  (0x80000000U)
#define MEM_76_PFLS_FLASH_PEADR_PEASAD_SHIFT                 (31U)
#define MEM_76_PFLS_FLASH_PEADR_PEASAD_WIDTH                 (1U)
#define MEM_76_PFLS_FLASH_PEADR_PEASAD(x)                    (((uint32_t)(((uint32_t)(x)) << FLASH_PEADR_PEASAD_SHIFT)) & FLASH_PEADR_PEASAD_MASK)
/*! @} */

/*! @name SPELOCK - Sector Program and Erase Hardware Lock */
/*! @{ */

#define MEM_76_PFLS_FLASH_SPELOCK_SPELOCK_MASK               (0xFFFFFFFFU)
#define MEM_76_PFLS_FLASH_SPELOCK_SPELOCK_SHIFT              (0U)
#define MEM_76_PFLS_FLASH_SPELOCK_SPELOCK_WIDTH              (32U)
#define MEM_76_PFLS_FLASH_SPELOCK_SPELOCK(x)                 (((uint32_t)(((uint32_t)(x)) << FLASH_SPELOCK_SPELOCK_SHIFT)) & FLASH_SPELOCK_SPELOCK_MASK)
/*! @} */

/*! @name SSPELOCK - Super Sector Program and Erase Hardware Lock */
/*! @{ */

#define MEM_76_PFLS_FLASH_SSPELOCK_SSPELOCK_MASK             (0xFFFFFFFU)
#define MEM_76_PFLS_FLASH_SSPELOCK_SSPELOCK_SHIFT            (0U)
#define MEM_76_PFLS_FLASH_SSPELOCK_SSPELOCK_WIDTH            (28U)
#define MEM_76_PFLS_FLASH_SSPELOCK_SSPELOCK(x)               (((uint32_t)(((uint32_t)(x)) << FLASH_SSPELOCK_SSPELOCK_SHIFT)) & FLASH_SSPELOCK_SSPELOCK_MASK)
/*! @} */

/*! @name XSPELOCK - Express Sector Program and Erase Hardware Lock */
/*! @{ */

#define MEM_76_PFLS_FLASH_XSPELOCK_XSPELOCK_MASK             (0xFFFFFFFFU)
#define MEM_76_PFLS_FLASH_XSPELOCK_XSPELOCK_SHIFT            (0U)
#define MEM_76_PFLS_FLASH_XSPELOCK_XSPELOCK_WIDTH            (32U)
#define MEM_76_PFLS_FLASH_XSPELOCK_XSPELOCK(x)               (((uint32_t)(((uint32_t)(x)) << FLASH_XSPELOCK_XSPELOCK_SHIFT)) & FLASH_XSPELOCK_XSPELOCK_MASK)
/*! @} */

/*! @name XSSPELOCK - Express Super Sector Program and Erase Hardware Lock */
/*! @{ */

#define MEM_76_PFLS_FLASH_XSSPELOCK_XSSPELOCK_MASK           (0xFFFFFFFU)
#define MEM_76_PFLS_FLASH_XSSPELOCK_XSSPELOCK_SHIFT          (0U)
#define MEM_76_PFLS_FLASH_XSSPELOCK_XSSPELOCK_WIDTH          (28U)
#define MEM_76_PFLS_FLASH_XSSPELOCK_XSSPELOCK(x)             (((uint32_t)(((uint32_t)(x)) << FLASH_XSSPELOCK_XSSPELOCK_SHIFT)) & FLASH_XSSPELOCK_XSSPELOCK_MASK)
/*! @} */

/*! @name TMD - Test Mode Disable Password Check */
/*! @{ */

#define MEM_76_PFLS_FLASH_TMD_PWD_MASK                       (0xFFFFFFFFU)
#define MEM_76_PFLS_FLASH_TMD_PWD_SHIFT                      (0U)
#define MEM_76_PFLS_FLASH_TMD_PWD_WIDTH                      (32U)
#define MEM_76_PFLS_FLASH_TMD_PWD(x)                         (((uint32_t)(((uint32_t)(x)) << FLASH_TMD_PWD_SHIFT)) & FLASH_TMD_PWD_MASK)
/*! @} */

/*! @name UT0 - UTest 0 */
/*! @{ */

#define MEM_76_PFLS_FLASH_UT0_AID_MASK                       (0x1U)
#define MEM_76_PFLS_FLASH_UT0_AID_SHIFT                      (0U)
#define MEM_76_PFLS_FLASH_UT0_AID_WIDTH                      (1U)
#define MEM_76_PFLS_FLASH_UT0_AID(x)                         (((uint32_t)(((uint32_t)(x)) << FLASH_UT0_AID_SHIFT)) & FLASH_UT0_AID_MASK)

#define MEM_76_PFLS_FLASH_UT0_AIE_MASK                       (0x2U)
#define MEM_76_PFLS_FLASH_UT0_AIE_SHIFT                      (1U)
#define MEM_76_PFLS_FLASH_UT0_AIE_WIDTH                      (1U)
#define MEM_76_PFLS_FLASH_UT0_AIE(x)                         (((uint32_t)(((uint32_t)(x)) << FLASH_UT0_AIE_SHIFT)) & FLASH_UT0_AIE_MASK)

#define MEM_76_PFLS_FLASH_UT0_AIS_MASK                       (0x4U)
#define MEM_76_PFLS_FLASH_UT0_AIS_SHIFT                      (2U)
#define MEM_76_PFLS_FLASH_UT0_AIS_WIDTH                      (1U)
#define MEM_76_PFLS_FLASH_UT0_AIS(x)                         (((uint32_t)(((uint32_t)(x)) << FLASH_UT0_AIS_SHIFT)) & FLASH_UT0_AIS_MASK)

#define MEM_76_PFLS_FLASH_UT0_MRV_MASK                       (0x10U)
#define MEM_76_PFLS_FLASH_UT0_MRV_SHIFT                      (4U)
#define MEM_76_PFLS_FLASH_UT0_MRV_WIDTH                      (1U)
#define MEM_76_PFLS_FLASH_UT0_MRV(x)                         (((uint32_t)(((uint32_t)(x)) << FLASH_UT0_MRV_SHIFT)) & FLASH_UT0_MRV_MASK)

#define MEM_76_PFLS_FLASH_UT0_MRE_MASK                       (0x20U)
#define MEM_76_PFLS_FLASH_UT0_MRE_SHIFT                      (5U)
#define MEM_76_PFLS_FLASH_UT0_MRE_WIDTH                      (1U)
#define MEM_76_PFLS_FLASH_UT0_MRE(x)                         (((uint32_t)(((uint32_t)(x)) << FLASH_UT0_MRE_SHIFT)) & FLASH_UT0_MRE_MASK)

#define MEM_76_PFLS_FLASH_UT0_AISUS_MASK                     (0x40U)
#define MEM_76_PFLS_FLASH_UT0_AISUS_SHIFT                    (6U)
#define MEM_76_PFLS_FLASH_UT0_AISUS_WIDTH                    (1U)
#define MEM_76_PFLS_FLASH_UT0_AISUS(x)                       (((uint32_t)(((uint32_t)(x)) << FLASH_UT0_AISUS_SHIFT)) & FLASH_UT0_AISUS_MASK)

#define MEM_76_PFLS_FLASH_UT0_AIBPE_MASK                     (0x100U)
#define MEM_76_PFLS_FLASH_UT0_AIBPE_SHIFT                    (8U)
#define MEM_76_PFLS_FLASH_UT0_AIBPE_WIDTH                    (1U)
#define MEM_76_PFLS_FLASH_UT0_AIBPE(x)                       (((uint32_t)(((uint32_t)(x)) << FLASH_UT0_AIBPE_SHIFT)) & FLASH_UT0_AIBPE_MASK)

#define MEM_76_PFLS_FLASH_UT0_NAIBP_MASK                     (0x200U)
#define MEM_76_PFLS_FLASH_UT0_NAIBP_SHIFT                    (9U)
#define MEM_76_PFLS_FLASH_UT0_NAIBP_WIDTH                    (1U)
#define MEM_76_PFLS_FLASH_UT0_NAIBP(x)                       (((uint32_t)(((uint32_t)(x)) << FLASH_UT0_NAIBP_SHIFT)) & FLASH_UT0_NAIBP_MASK)

#define MEM_76_PFLS_FLASH_UT0_EIE_MASK                       (0x1000U)
#define MEM_76_PFLS_FLASH_UT0_EIE_SHIFT                      (12U)
#define MEM_76_PFLS_FLASH_UT0_EIE_WIDTH                      (1U)
#define MEM_76_PFLS_FLASH_UT0_EIE(x)                         (((uint32_t)(((uint32_t)(x)) << FLASH_UT0_EIE_SHIFT)) & FLASH_UT0_EIE_MASK)

#define MEM_76_PFLS_FLASH_UT0_EDIE_MASK                      (0x2000U)
#define MEM_76_PFLS_FLASH_UT0_EDIE_SHIFT                     (13U)
#define MEM_76_PFLS_FLASH_UT0_EDIE_WIDTH                     (1U)
#define MEM_76_PFLS_FLASH_UT0_EDIE(x)                        (((uint32_t)(((uint32_t)(x)) << FLASH_UT0_EDIE_SHIFT)) & FLASH_UT0_EDIE_MASK)

#define MEM_76_PFLS_FLASH_UT0_AEIE_MASK                      (0x4000U)
#define MEM_76_PFLS_FLASH_UT0_AEIE_SHIFT                     (14U)
#define MEM_76_PFLS_FLASH_UT0_AEIE_WIDTH                     (1U)
#define MEM_76_PFLS_FLASH_UT0_AEIE(x)                        (((uint32_t)(((uint32_t)(x)) << FLASH_UT0_AEIE_SHIFT)) & FLASH_UT0_AEIE_MASK)

#define MEM_76_PFLS_FLASH_UT0_RRIE_MASK                      (0x8000U)
#define MEM_76_PFLS_FLASH_UT0_RRIE_SHIFT                     (15U)
#define MEM_76_PFLS_FLASH_UT0_RRIE_WIDTH                     (1U)
#define MEM_76_PFLS_FLASH_UT0_RRIE(x)                        (((uint32_t)(((uint32_t)(x)) << FLASH_UT0_RRIE_SHIFT)) & FLASH_UT0_RRIE_MASK)

#define MEM_76_PFLS_FLASH_UT0_SBCE_MASK                      (0x40000000U)
#define MEM_76_PFLS_FLASH_UT0_SBCE_SHIFT                     (30U)
#define MEM_76_PFLS_FLASH_UT0_SBCE_WIDTH                     (1U)
#define MEM_76_PFLS_FLASH_UT0_SBCE(x)                        (((uint32_t)(((uint32_t)(x)) << FLASH_UT0_SBCE_SHIFT)) & FLASH_UT0_SBCE_MASK)

#define MEM_76_PFLS_FLASH_UT0_UTE_MASK                       (0x80000000U)
#define MEM_76_PFLS_FLASH_UT0_UTE_SHIFT                      (31U)
#define MEM_76_PFLS_FLASH_UT0_UTE_WIDTH                      (1U)
#define MEM_76_PFLS_FLASH_UT0_UTE(x)                         (((uint32_t)(((uint32_t)(x)) << FLASH_UT0_UTE_SHIFT)) & FLASH_UT0_UTE_MASK)
/*! @} */

/*! @name UM - UMISRn */
/*! @{ */

#define MEM_76_PFLS_FLASH_UM_MISR_MASK                       (0xFFFFFFFFU)
#define MEM_76_PFLS_FLASH_UM_MISR_SHIFT                      (0U)
#define MEM_76_PFLS_FLASH_UM_MISR_WIDTH                      (32U)
#define MEM_76_PFLS_FLASH_UM_MISR(x)                         (((uint32_t)(((uint32_t)(x)) << FLASH_UM_MISR_SHIFT)) & FLASH_UM_MISR_MASK)
/*! @} */

/*! @name UM9 - UMISR9 */
/*! @{ */

#define MEM_76_PFLS_FLASH_UM9_MISR_MASK                      (0x1U)
#define MEM_76_PFLS_FLASH_UM9_MISR_SHIFT                     (0U)
#define MEM_76_PFLS_FLASH_UM9_MISR_WIDTH                     (1U)
#define MEM_76_PFLS_FLASH_UM9_MISR(x)                        (((uint32_t)(((uint32_t)(x)) << FLASH_UM9_MISR_SHIFT)) & FLASH_UM9_MISR_MASK)
/*! @} */

/*! @name UD0 - UTest Data 0 */
/*! @{ */

#define MEM_76_PFLS_FLASH_UD0_EDATA_MASK                     (0xFFFFFFFFU)
#define MEM_76_PFLS_FLASH_UD0_EDATA_SHIFT                    (0U)
#define MEM_76_PFLS_FLASH_UD0_EDATA_WIDTH                    (32U)
#define MEM_76_PFLS_FLASH_UD0_EDATA(x)                       (((uint32_t)(((uint32_t)(x)) << FLASH_UD0_EDATA_SHIFT)) & FLASH_UD0_EDATA_MASK)
/*! @} */

/*! @name UD1 - UTest Data 1 */
/*! @{ */

#define MEM_76_PFLS_FLASH_UD1_EDATA_MASK                     (0xFFFFFFFFU)
#define MEM_76_PFLS_FLASH_UD1_EDATA_SHIFT                    (0U)
#define MEM_76_PFLS_FLASH_UD1_EDATA_WIDTH                    (32U)
#define MEM_76_PFLS_FLASH_UD1_EDATA(x)                       (((uint32_t)(((uint32_t)(x)) << FLASH_UD1_EDATA_SHIFT)) & FLASH_UD1_EDATA_MASK)
/*! @} */

/*! @name UD2 - UTest Data 2 */
/*! @{ */

#define MEM_76_PFLS_FLASH_UD2_EDATAC_MASK                    (0xFFU)
#define MEM_76_PFLS_FLASH_UD2_EDATAC_SHIFT                   (0U)
#define MEM_76_PFLS_FLASH_UD2_EDATAC_WIDTH                   (8U)
#define MEM_76_PFLS_FLASH_UD2_EDATAC(x)                      (((uint32_t)(((uint32_t)(x)) << FLASH_UD2_EDATAC_SHIFT)) & FLASH_UD2_EDATAC_MASK)

#define MEM_76_PFLS_FLASH_UD2_ED0_MASK                       (0x1000000U)
#define MEM_76_PFLS_FLASH_UD2_ED0_SHIFT                      (24U)
#define MEM_76_PFLS_FLASH_UD2_ED0_WIDTH                      (1U)
#define MEM_76_PFLS_FLASH_UD2_ED0(x)                         (((uint32_t)(((uint32_t)(x)) << FLASH_UD2_ED0_SHIFT)) & FLASH_UD2_ED0_MASK)

#define MEM_76_PFLS_FLASH_UD2_ED1_MASK                       (0x2000000U)
#define MEM_76_PFLS_FLASH_UD2_ED1_SHIFT                      (25U)
#define MEM_76_PFLS_FLASH_UD2_ED1_WIDTH                      (1U)
#define MEM_76_PFLS_FLASH_UD2_ED1(x)                         (((uint32_t)(((uint32_t)(x)) << FLASH_UD2_ED1_SHIFT)) & FLASH_UD2_ED1_MASK)

#define MEM_76_PFLS_FLASH_UD2_ED2_MASK                       (0x4000000U)
#define MEM_76_PFLS_FLASH_UD2_ED2_SHIFT                      (26U)
#define MEM_76_PFLS_FLASH_UD2_ED2_WIDTH                      (1U)
#define MEM_76_PFLS_FLASH_UD2_ED2(x)                         (((uint32_t)(((uint32_t)(x)) << FLASH_UD2_ED2_SHIFT)) & FLASH_UD2_ED2_MASK)

#define MEM_76_PFLS_FLASH_UD2_ED3_MASK                       (0x8000000U)
#define MEM_76_PFLS_FLASH_UD2_ED3_SHIFT                      (27U)
#define MEM_76_PFLS_FLASH_UD2_ED3_WIDTH                      (1U)
#define MEM_76_PFLS_FLASH_UD2_ED3(x)                         (((uint32_t)(((uint32_t)(x)) << FLASH_UD2_ED3_SHIFT)) & FLASH_UD2_ED3_MASK)
/*! @} */

/*! @name UD3 - UTest Data 3 */
/*! @{ */

#define MEM_76_PFLS_FLASH_UD3_EDDATA_MASK                    (0xFFFFFFFFU)
#define MEM_76_PFLS_FLASH_UD3_EDDATA_SHIFT                   (0U)
#define MEM_76_PFLS_FLASH_UD3_EDDATA_WIDTH                   (32U)
#define MEM_76_PFLS_FLASH_UD3_EDDATA(x)                      (((uint32_t)(((uint32_t)(x)) << FLASH_UD3_EDDATA_SHIFT)) & FLASH_UD3_EDDATA_MASK)
/*! @} */

/*! @name UD4 - UTest Data 4 */
/*! @{ */

#define MEM_76_PFLS_FLASH_UD4_EDDATA_MASK                    (0xFFFFFFFFU)
#define MEM_76_PFLS_FLASH_UD4_EDDATA_SHIFT                   (0U)
#define MEM_76_PFLS_FLASH_UD4_EDDATA_WIDTH                   (32U)
#define MEM_76_PFLS_FLASH_UD4_EDDATA(x)                      (((uint32_t)(((uint32_t)(x)) << FLASH_UD4_EDDATA_SHIFT)) & FLASH_UD4_EDDATA_MASK)
/*! @} */

/*! @name UD5 - UTest Data 5 */
/*! @{ */

#define MEM_76_PFLS_FLASH_UD5_EDDATAC_MASK                   (0xFFU)
#define MEM_76_PFLS_FLASH_UD5_EDDATAC_SHIFT                  (0U)
#define MEM_76_PFLS_FLASH_UD5_EDDATAC_WIDTH                  (8U)
#define MEM_76_PFLS_FLASH_UD5_EDDATAC(x)                     (((uint32_t)(((uint32_t)(x)) << FLASH_UD5_EDDATAC_SHIFT)) & FLASH_UD5_EDDATAC_MASK)

#define MEM_76_PFLS_FLASH_UD5_EDD0_MASK                      (0x1000000U)
#define MEM_76_PFLS_FLASH_UD5_EDD0_SHIFT                     (24U)
#define MEM_76_PFLS_FLASH_UD5_EDD0_WIDTH                     (1U)
#define MEM_76_PFLS_FLASH_UD5_EDD0(x)                        (((uint32_t)(((uint32_t)(x)) << FLASH_UD5_EDD0_SHIFT)) & FLASH_UD5_EDD0_MASK)

#define MEM_76_PFLS_FLASH_UD5_EDD1_MASK                      (0x2000000U)
#define MEM_76_PFLS_FLASH_UD5_EDD1_SHIFT                     (25U)
#define MEM_76_PFLS_FLASH_UD5_EDD1_WIDTH                     (1U)
#define MEM_76_PFLS_FLASH_UD5_EDD1(x)                        (((uint32_t)(((uint32_t)(x)) << FLASH_UD5_EDD1_SHIFT)) & FLASH_UD5_EDD1_MASK)

#define MEM_76_PFLS_FLASH_UD5_EDD2_MASK                      (0x4000000U)
#define MEM_76_PFLS_FLASH_UD5_EDD2_SHIFT                     (26U)
#define MEM_76_PFLS_FLASH_UD5_EDD2_WIDTH                     (1U)
#define MEM_76_PFLS_FLASH_UD5_EDD2(x)                        (((uint32_t)(((uint32_t)(x)) << FLASH_UD5_EDD2_SHIFT)) & FLASH_UD5_EDD2_MASK)

#define MEM_76_PFLS_FLASH_UD5_EDD3_MASK                      (0x8000000U)
#define MEM_76_PFLS_FLASH_UD5_EDD3_SHIFT                     (27U)
#define MEM_76_PFLS_FLASH_UD5_EDD3_WIDTH                     (1U)
#define MEM_76_PFLS_FLASH_UD5_EDD3(x)                        (((uint32_t)(((uint32_t)(x)) << FLASH_UD5_EDD3_SHIFT)) & FLASH_UD5_EDD3_MASK)
/*! @} */

/*! @name UA0 - UTest Address 0 */
/*! @{ */

#define MEM_76_PFLS_FLASH_UA0_AEI_MASK                       (0xFFFFFFFFU)
#define MEM_76_PFLS_FLASH_UA0_AEI_SHIFT                      (0U)
#define MEM_76_PFLS_FLASH_UA0_AEI_WIDTH                      (32U)
#define MEM_76_PFLS_FLASH_UA0_AEI(x)                         (((uint32_t)(((uint32_t)(x)) << FLASH_UA0_AEI_SHIFT)) & FLASH_UA0_AEI_MASK)
/*! @} */

/*! @name UA1 - UTest Address 1 */
/*! @{ */

#define MEM_76_PFLS_FLASH_UA1_AEI_MASK                       (0xFFFFFU)
#define MEM_76_PFLS_FLASH_UA1_AEI_SHIFT                      (0U)
#define MEM_76_PFLS_FLASH_UA1_AEI_WIDTH                      (20U)
#define MEM_76_PFLS_FLASH_UA1_AEI(x)                         (((uint32_t)(((uint32_t)(x)) << FLASH_UA1_AEI_SHIFT)) & FLASH_UA1_AEI_MASK)
/*! @} */

/*! @name XMCR - Express Module Configuration */
/*! @{ */

#define MEM_76_PFLS_FLASH_XMCR_XEHV_MASK                     (0x1U)
#define MEM_76_PFLS_FLASH_XMCR_XEHV_SHIFT                    (0U)
#define MEM_76_PFLS_FLASH_XMCR_XEHV_WIDTH                    (1U)
#define MEM_76_PFLS_FLASH_XMCR_XEHV(x)                       (((uint32_t)(((uint32_t)(x)) << FLASH_XMCR_XEHV_SHIFT)) & FLASH_XMCR_XEHV_MASK)

#define MEM_76_PFLS_FLASH_XMCR_XPGM_MASK                     (0x100U)
#define MEM_76_PFLS_FLASH_XMCR_XPGM_SHIFT                    (8U)
#define MEM_76_PFLS_FLASH_XMCR_XPGM_WIDTH                    (1U)
#define MEM_76_PFLS_FLASH_XMCR_XPGM(x)                       (((uint32_t)(((uint32_t)(x)) << FLASH_XMCR_XPGM_SHIFT)) & FLASH_XMCR_XPGM_MASK)

#define MEM_76_PFLS_FLASH_XMCR_XEPEG_MASK                    (0x200U)
#define MEM_76_PFLS_FLASH_XMCR_XEPEG_SHIFT                   (9U)
#define MEM_76_PFLS_FLASH_XMCR_XEPEG_WIDTH                   (1U)
#define MEM_76_PFLS_FLASH_XMCR_XEPEG(x)                      (((uint32_t)(((uint32_t)(x)) << FLASH_XMCR_XEPEG_SHIFT)) & FLASH_XMCR_XEPEG_MASK)

#define MEM_76_PFLS_FLASH_XMCR_XWDIE_MASK                    (0x800U)
#define MEM_76_PFLS_FLASH_XMCR_XWDIE_SHIFT                   (11U)
#define MEM_76_PFLS_FLASH_XMCR_XWDIE_WIDTH                   (1U)
#define MEM_76_PFLS_FLASH_XMCR_XWDIE(x)                      (((uint32_t)(((uint32_t)(x)) << FLASH_XMCR_XWDIE_SHIFT)) & FLASH_XMCR_XWDIE_MASK)

#define MEM_76_PFLS_FLASH_XMCR_XWDI_MASK                     (0x1000U)
#define MEM_76_PFLS_FLASH_XMCR_XWDI_SHIFT                    (12U)
#define MEM_76_PFLS_FLASH_XMCR_XWDI_WIDTH                    (1U)
#define MEM_76_PFLS_FLASH_XMCR_XWDI(x)                       (((uint32_t)(((uint32_t)(x)) << FLASH_XMCR_XWDI_SHIFT)) & FLASH_XMCR_XWDI_MASK)

#define MEM_76_PFLS_FLASH_XMCR_XDOK_MASK                     (0x2000U)
#define MEM_76_PFLS_FLASH_XMCR_XDOK_SHIFT                    (13U)
#define MEM_76_PFLS_FLASH_XMCR_XDOK_WIDTH                    (1U)
#define MEM_76_PFLS_FLASH_XMCR_XDOK(x)                       (((uint32_t)(((uint32_t)(x)) << FLASH_XMCR_XDOK_SHIFT)) & FLASH_XMCR_XDOK_MASK)

#define MEM_76_PFLS_FLASH_XMCR_XPEG_MASK                     (0x4000U)
#define MEM_76_PFLS_FLASH_XMCR_XPEG_SHIFT                    (14U)
#define MEM_76_PFLS_FLASH_XMCR_XPEG_WIDTH                    (1U)
#define MEM_76_PFLS_FLASH_XMCR_XPEG(x)                       (((uint32_t)(((uint32_t)(x)) << FLASH_XMCR_XPEG_SHIFT)) & FLASH_XMCR_XPEG_MASK)

#define MEM_76_PFLS_FLASH_XMCR_XDONE_MASK                    (0x8000U)
#define MEM_76_PFLS_FLASH_XMCR_XDONE_SHIFT                   (15U)
#define MEM_76_PFLS_FLASH_XMCR_XDONE_WIDTH                   (1U)
#define MEM_76_PFLS_FLASH_XMCR_XDONE(x)                      (((uint32_t)(((uint32_t)(x)) << FLASH_XMCR_XDONE_SHIFT)) & FLASH_XMCR_XDONE_MASK)

#define MEM_76_PFLS_FLASH_XMCR_XPEID_MASK                    (0xFF0000U)
#define MEM_76_PFLS_FLASH_XMCR_XPEID_SHIFT                   (16U)
#define MEM_76_PFLS_FLASH_XMCR_XPEID_WIDTH                   (8U)
#define MEM_76_PFLS_FLASH_XMCR_XPEID(x)                      (((uint32_t)(((uint32_t)(x)) << FLASH_XMCR_XPEID_SHIFT)) & FLASH_XMCR_XPEID_MASK)
/*! @} */

/*! @name XPEADR - Express Program Address */
/*! @{ */

#define MEM_76_PFLS_FLASH_XPEADR_XPEADDR_MASK                (0x7FFE0U)
#define MEM_76_PFLS_FLASH_XPEADR_XPEADDR_SHIFT               (5U)
#define MEM_76_PFLS_FLASH_XPEADR_XPEADDR_WIDTH               (14U)
#define MEM_76_PFLS_FLASH_XPEADR_XPEADDR(x)                  (((uint32_t)(((uint32_t)(x)) << FLASH_XPEADR_XPEADDR_SHIFT)) & FLASH_XPEADR_XPEADDR_MASK)

#define MEM_76_PFLS_FLASH_XPEADR_XPEA0_MASK                  (0x80000U)
#define MEM_76_PFLS_FLASH_XPEADR_XPEA0_SHIFT                 (19U)
#define MEM_76_PFLS_FLASH_XPEADR_XPEA0_WIDTH                 (1U)
#define MEM_76_PFLS_FLASH_XPEADR_XPEA0(x)                    (((uint32_t)(((uint32_t)(x)) << FLASH_XPEADR_XPEA0_SHIFT)) & FLASH_XPEADR_XPEA0_MASK)

#define MEM_76_PFLS_FLASH_XPEADR_XPEA1_MASK                  (0x100000U)
#define MEM_76_PFLS_FLASH_XPEADR_XPEA1_SHIFT                 (20U)
#define MEM_76_PFLS_FLASH_XPEADR_XPEA1_WIDTH                 (1U)
#define MEM_76_PFLS_FLASH_XPEADR_XPEA1(x)                    (((uint32_t)(((uint32_t)(x)) << FLASH_XPEADR_XPEA1_SHIFT)) & FLASH_XPEADR_XPEA1_MASK)

#define MEM_76_PFLS_FLASH_XPEADR_XPEA2_MASK                  (0x200000U)
#define MEM_76_PFLS_FLASH_XPEADR_XPEA2_SHIFT                 (21U)
#define MEM_76_PFLS_FLASH_XPEADR_XPEA2_WIDTH                 (1U)
#define MEM_76_PFLS_FLASH_XPEADR_XPEA2(x)                    (((uint32_t)(((uint32_t)(x)) << FLASH_XPEADR_XPEA2_SHIFT)) & FLASH_XPEADR_XPEA2_MASK)

#define MEM_76_PFLS_FLASH_XPEADR_XPEA3_MASK                  (0x400000U)
#define MEM_76_PFLS_FLASH_XPEADR_XPEA3_SHIFT                 (22U)
#define MEM_76_PFLS_FLASH_XPEADR_XPEA3_WIDTH                 (1U)
#define MEM_76_PFLS_FLASH_XPEADR_XPEA3(x)                    (((uint32_t)(((uint32_t)(x)) << FLASH_XPEADR_XPEA3_SHIFT)) & FLASH_XPEADR_XPEA3_MASK)

#define MEM_76_PFLS_FLASH_XPEADR_XPEA4_MASK                  (0x800000U)
#define MEM_76_PFLS_FLASH_XPEADR_XPEA4_SHIFT                 (23U)
#define MEM_76_PFLS_FLASH_XPEADR_XPEA4_WIDTH                 (1U)
#define MEM_76_PFLS_FLASH_XPEADR_XPEA4(x)                    (((uint32_t)(((uint32_t)(x)) << FLASH_XPEADR_XPEA4_SHIFT)) & FLASH_XPEADR_XPEA4_MASK)

#define MEM_76_PFLS_FLASH_XPEADR_XPEA5_MASK                  (0x1000000U)
#define MEM_76_PFLS_FLASH_XPEADR_XPEA5_SHIFT                 (24U)
#define MEM_76_PFLS_FLASH_XPEADR_XPEA5_WIDTH                 (1U)
#define MEM_76_PFLS_FLASH_XPEADR_XPEA5(x)                    (((uint32_t)(((uint32_t)(x)) << FLASH_XPEADR_XPEA5_SHIFT)) & FLASH_XPEADR_XPEA5_MASK)
/*! @} */

/*! @name DATA - Program Data */
/*! @{ */

#define MEM_76_PFLS_FLASH_DATA_PDATA_MASK                    (0xFFFFFFFFU)
#define MEM_76_PFLS_FLASH_DATA_PDATA_SHIFT                   (0U)
#define MEM_76_PFLS_FLASH_DATA_PDATA_WIDTH                   (32U)
#define MEM_76_PFLS_FLASH_DATA_PDATA(x)                      (((uint32_t)(((uint32_t)(x)) << FLASH_DATA_PDATA_SHIFT)) & FLASH_DATA_PDATA_MASK)

/* ----------------------------------------------------------------------------
   -- PFLASH Register Masks - Flash Memory Controller
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup PFLASH_Register_Masks PFLASH Register Masks
 * @{
 */

/*! @name PFCR - Platform Flash Memory Configuration 0..Platform Flash Memory Configuration 2 */
/*! @{ */

#define MEM_76_PFLS_PFLASH_PFCR_P0_CBFEN_MASK                (0x1U)
#define MEM_76_PFLS_PFLASH_PFCR_P0_CBFEN_SHIFT               (0U)
#define MEM_76_PFLS_PFLASH_PFCR_P0_CBFEN_WIDTH               (1U)
#define MEM_76_PFLS_PFLASH_PFCR_P0_CBFEN(x)                  (((uint32_t)(((uint32_t)(x)) << MEM_76_PFLS_PFLASH_PFCR_P0_CBFEN_SHIFT)) & MEM_76_PFLS_PFLASH_PFCR_P0_CBFEN_MASK)

#define MEM_76_PFLS_PFLASH_PFCR_P0_DBFEN_MASK                (0x2U)
#define MEM_76_PFLS_PFLASH_PFCR_P0_DBFEN_SHIFT               (1U)
#define MEM_76_PFLS_PFLASH_PFCR_P0_DBFEN_WIDTH               (1U)
#define MEM_76_PFLS_PFLASH_PFCR_P0_DBFEN(x)                  (((uint32_t)(((uint32_t)(x)) << MEM_76_PFLS_PFLASH_PFCR_P0_DBFEN_SHIFT)) & MEM_76_PFLS_PFLASH_PFCR_P0_DBFEN_MASK)

#define MEM_76_PFLS_PFLASH_PFCR_P0_CPFEN_MASK                (0x10U)
#define MEM_76_PFLS_PFLASH_PFCR_P0_CPFEN_SHIFT               (4U)
#define MEM_76_PFLS_PFLASH_PFCR_P0_CPFEN_WIDTH               (1U)
#define MEM_76_PFLS_PFLASH_PFCR_P0_CPFEN(x)                  (((uint32_t)(((uint32_t)(x)) << MEM_76_PFLS_PFLASH_PFCR_P0_CPFEN_SHIFT)) & MEM_76_PFLS_PFLASH_PFCR_P0_CPFEN_MASK)

#define MEM_76_PFLS_PFLASH_PFCR_P0_DPFEN_MASK                (0x20U)
#define MEM_76_PFLS_PFLASH_PFCR_P0_DPFEN_SHIFT               (5U)
#define MEM_76_PFLS_PFLASH_PFCR_P0_DPFEN_WIDTH               (1U)
#define MEM_76_PFLS_PFLASH_PFCR_P0_DPFEN(x)                  (((uint32_t)(((uint32_t)(x)) << MEM_76_PFLS_PFLASH_PFCR_P0_DPFEN_SHIFT)) & MEM_76_PFLS_PFLASH_PFCR_P0_DPFEN_MASK)

#define MEM_76_PFLS_PFLASH_PFCR_P1_CBFEN_MASK                (0x1U)
#define MEM_76_PFLS_PFLASH_PFCR_P1_CBFEN_SHIFT               (0U)
#define MEM_76_PFLS_PFLASH_PFCR_P1_CBFEN_WIDTH               (1U)
#define MEM_76_PFLS_PFLASH_PFCR_P1_CBFEN(x)                  (((uint32_t)(((uint32_t)(x)) << MEM_76_PFLS_PFLASH_PFCR_P1_CBFEN_SHIFT)) & MEM_76_PFLS_PFLASH_PFCR_P1_CBFEN_MASK)

#define MEM_76_PFLS_PFLASH_PFCR_P1_DBFEN_MASK                (0x2U)
#define MEM_76_PFLS_PFLASH_PFCR_P1_DBFEN_SHIFT               (1U)
#define MEM_76_PFLS_PFLASH_PFCR_P1_DBFEN_WIDTH               (1U)
#define MEM_76_PFLS_PFLASH_PFCR_P1_DBFEN(x)                  (((uint32_t)(((uint32_t)(x)) << MEM_76_PFLS_PFLASH_PFCR_P1_DBFEN_SHIFT)) & MEM_76_PFLS_PFLASH_PFCR_P1_DBFEN_MASK)

#define MEM_76_PFLS_PFLASH_PFCR_P1_CPFEN_MASK                (0x10U)
#define MEM_76_PFLS_PFLASH_PFCR_P1_CPFEN_SHIFT               (4U)
#define MEM_76_PFLS_PFLASH_PFCR_P1_CPFEN_WIDTH               (1U)
#define MEM_76_PFLS_PFLASH_PFCR_P1_CPFEN(x)                  (((uint32_t)(((uint32_t)(x)) << MEM_76_PFLS_PFLASH_PFCR_P1_CPFEN_SHIFT)) & MEM_76_PFLS_PFLASH_PFCR_P1_CPFEN_MASK)

#define MEM_76_PFLS_PFLASH_PFCR_P1_DPFEN_MASK                (0x20U)
#define MEM_76_PFLS_PFLASH_PFCR_P1_DPFEN_SHIFT               (5U)
#define MEM_76_PFLS_PFLASH_PFCR_P1_DPFEN_WIDTH               (1U)
#define MEM_76_PFLS_PFLASH_PFCR_P1_DPFEN(x)                  (((uint32_t)(((uint32_t)(x)) << MEM_76_PFLS_PFLASH_PFCR_P1_DPFEN_SHIFT)) & MEM_76_PFLS_PFLASH_PFCR_P1_DPFEN_MASK)

#define MEM_76_PFLS_PFLASH_PFCR_P2_CBFEN_MASK                (0x1U)
#define MEM_76_PFLS_PFLASH_PFCR_P2_CBFEN_SHIFT               (0U)
#define MEM_76_PFLS_PFLASH_PFCR_P2_CBFEN_WIDTH               (1U)
#define MEM_76_PFLS_PFLASH_PFCR_P2_CBFEN(x)                  (((uint32_t)(((uint32_t)(x)) << MEM_76_PFLS_PFLASH_PFCR_P2_CBFEN_SHIFT)) & MEM_76_PFLS_PFLASH_PFCR_P2_CBFEN_MASK)

#define MEM_76_PFLS_PFLASH_PFCR_P2_DBFEN_MASK                (0x2U)
#define MEM_76_PFLS_PFLASH_PFCR_P2_DBFEN_SHIFT               (1U)
#define MEM_76_PFLS_PFLASH_PFCR_P2_DBFEN_WIDTH               (1U)
#define MEM_76_PFLS_PFLASH_PFCR_P2_DBFEN(x)                  (((uint32_t)(((uint32_t)(x)) << MEM_76_PFLS_PFLASH_PFCR_P2_DBFEN_SHIFT)) & MEM_76_PFLS_PFLASH_PFCR_P2_DBFEN_MASK)

#define MEM_76_PFLS_PFLASH_PFCR_P2_CPFEN_MASK                (0x10U)
#define MEM_76_PFLS_PFLASH_PFCR_P2_CPFEN_SHIFT               (4U)
#define MEM_76_PFLS_PFLASH_PFCR_P2_CPFEN_WIDTH               (1U)
#define MEM_76_PFLS_PFLASH_PFCR_P2_CPFEN(x)                  (((uint32_t)(((uint32_t)(x)) << MEM_76_PFLS_PFLASH_PFCR_P2_CPFEN_SHIFT)) & MEM_76_PFLS_PFLASH_PFCR_P2_CPFEN_MASK)

#define MEM_76_PFLS_PFLASH_PFCR_P2_DPFEN_MASK                (0x20U)
#define MEM_76_PFLS_PFLASH_PFCR_P2_DPFEN_SHIFT               (5U)
#define MEM_76_PFLS_PFLASH_PFCR_P2_DPFEN_WIDTH               (1U)
#define MEM_76_PFLS_PFLASH_PFCR_P2_DPFEN(x)                  (((uint32_t)(((uint32_t)(x)) << MEM_76_PFLS_PFLASH_PFCR_P2_DPFEN_SHIFT)) & MEM_76_PFLS_PFLASH_PFCR_P2_DPFEN_MASK)
/*! @} */

/*! @name PFCR4 - Platform Flash Memory Configuration 4 */
/*! @{ */

#define MEM_76_PFLS_PFLASH_PFCR4_DERR_SUP_MASK               (0x1U)
#define MEM_76_PFLS_PFLASH_PFCR4_DERR_SUP_SHIFT              (0U)
#define MEM_76_PFLS_PFLASH_PFCR4_DERR_SUP_WIDTH              (1U)
#define MEM_76_PFLS_PFLASH_PFCR4_DERR_SUP(x)                 (((uint32_t)(((uint32_t)(x)) << MEM_76_PFLS_PFLASH_PFCR4_DERR_SUP_SHIFT)) & MEM_76_PFLS_PFLASH_PFCR4_DERR_SUP_MASK)

#define MEM_76_PFLS_PFLASH_PFCR4_BLK4_PS_MASK                (0xEU)
#define MEM_76_PFLS_PFLASH_PFCR4_BLK4_PS_SHIFT               (1U)
#define MEM_76_PFLS_PFLASH_PFCR4_BLK4_PS_WIDTH               (3U)
#define MEM_76_PFLS_PFLASH_PFCR4_BLK4_PS(x)                  (((uint32_t)(((uint32_t)(x)) << MEM_76_PFLS_PFLASH_PFCR4_BLK4_PS_SHIFT)) & MEM_76_PFLS_PFLASH_PFCR4_BLK4_PS_MASK)

#define MEM_76_PFLS_PFLASH_PFCR4_DMEEE_MASK                  (0x80U)
#define MEM_76_PFLS_PFLASH_PFCR4_DMEEE_SHIFT                 (7U)
#define MEM_76_PFLS_PFLASH_PFCR4_DMEEE_WIDTH                 (1U)
#define MEM_76_PFLS_PFLASH_PFCR4_DMEEE(x)                    (((uint32_t)(((uint32_t)(x)) << MEM_76_PFLS_PFLASH_PFCR4_DMEEE_SHIFT)) & MEM_76_PFLS_PFLASH_PFCR4_DMEEE_MASK)
/*! @} */

/*! @name PFAPR - Platform Flash Memory Access Protection */
/*! @{ */

#define MEM_76_PFLS_PFLASH_PFAPR_M15AP_MASK                  (0x3U)
#define MEM_76_PFLS_PFLASH_PFAPR_M15AP_SHIFT                 (0U)
#define MEM_76_PFLS_PFLASH_PFAPR_M15AP_WIDTH                 (2U)
#define MEM_76_PFLS_PFLASH_PFAPR_M15AP(x)                    (((uint32_t)(((uint32_t)(x)) << MEM_76_PFLS_PFLASH_PFAPR_M15AP_SHIFT)) & MEM_76_PFLS_PFLASH_PFAPR_M15AP_MASK)

#define MEM_76_PFLS_PFLASH_PFAPR_M14AP_MASK                  (0xCU)
#define MEM_76_PFLS_PFLASH_PFAPR_M14AP_SHIFT                 (2U)
#define MEM_76_PFLS_PFLASH_PFAPR_M14AP_WIDTH                 (2U)
#define MEM_76_PFLS_PFLASH_PFAPR_M14AP(x)                    (((uint32_t)(((uint32_t)(x)) << MEM_76_PFLS_PFLASH_PFAPR_M14AP_SHIFT)) & MEM_76_PFLS_PFLASH_PFAPR_M14AP_MASK)

#define MEM_76_PFLS_PFLASH_PFAPR_M13AP_MASK                  (0x30U)
#define MEM_76_PFLS_PFLASH_PFAPR_M13AP_SHIFT                 (4U)
#define MEM_76_PFLS_PFLASH_PFAPR_M13AP_WIDTH                 (2U)
#define MEM_76_PFLS_PFLASH_PFAPR_M13AP(x)                    (((uint32_t)(((uint32_t)(x)) << MEM_76_PFLS_PFLASH_PFAPR_M13AP_SHIFT)) & MEM_76_PFLS_PFLASH_PFAPR_M13AP_MASK)

#define MEM_76_PFLS_PFLASH_PFAPR_M12AP_MASK                  (0xC0U)
#define MEM_76_PFLS_PFLASH_PFAPR_M12AP_SHIFT                 (6U)
#define MEM_76_PFLS_PFLASH_PFAPR_M12AP_WIDTH                 (2U)
#define MEM_76_PFLS_PFLASH_PFAPR_M12AP(x)                    (((uint32_t)(((uint32_t)(x)) << MEM_76_PFLS_PFLASH_PFAPR_M12AP_SHIFT)) & MEM_76_PFLS_PFLASH_PFAPR_M12AP_MASK)

#define MEM_76_PFLS_PFLASH_PFAPR_M11AP_MASK                  (0x300U)
#define MEM_76_PFLS_PFLASH_PFAPR_M11AP_SHIFT                 (8U)
#define MEM_76_PFLS_PFLASH_PFAPR_M11AP_WIDTH                 (2U)
#define MEM_76_PFLS_PFLASH_PFAPR_M11AP(x)                    (((uint32_t)(((uint32_t)(x)) << MEM_76_PFLS_PFLASH_PFAPR_M11AP_SHIFT)) & MEM_76_PFLS_PFLASH_PFAPR_M11AP_MASK)

#define MEM_76_PFLS_PFLASH_PFAPR_M10AP_MASK                  (0xC00U)
#define MEM_76_PFLS_PFLASH_PFAPR_M10AP_SHIFT                 (10U)
#define MEM_76_PFLS_PFLASH_PFAPR_M10AP_WIDTH                 (2U)
#define MEM_76_PFLS_PFLASH_PFAPR_M10AP(x)                    (((uint32_t)(((uint32_t)(x)) << MEM_76_PFLS_PFLASH_PFAPR_M10AP_SHIFT)) & MEM_76_PFLS_PFLASH_PFAPR_M10AP_MASK)

#define MEM_76_PFLS_PFLASH_PFAPR_M9AP_MASK                   (0x3000U)
#define MEM_76_PFLS_PFLASH_PFAPR_M9AP_SHIFT                  (12U)
#define MEM_76_PFLS_PFLASH_PFAPR_M9AP_WIDTH                  (2U)
#define MEM_76_PFLS_PFLASH_PFAPR_M9AP(x)                     (((uint32_t)(((uint32_t)(x)) << MEM_76_PFLS_PFLASH_PFAPR_M9AP_SHIFT)) & MEM_76_PFLS_PFLASH_PFAPR_M9AP_MASK)

#define MEM_76_PFLS_PFLASH_PFAPR_M8AP_MASK                   (0xC000U)
#define MEM_76_PFLS_PFLASH_PFAPR_M8AP_SHIFT                  (14U)
#define MEM_76_PFLS_PFLASH_PFAPR_M8AP_WIDTH                  (2U)
#define MEM_76_PFLS_PFLASH_PFAPR_M8AP(x)                     (((uint32_t)(((uint32_t)(x)) << MEM_76_PFLS_PFLASH_PFAPR_M8AP_SHIFT)) & MEM_76_PFLS_PFLASH_PFAPR_M8AP_MASK)

#define MEM_76_PFLS_PFLASH_PFAPR_M7AP_MASK                   (0x30000U)
#define MEM_76_PFLS_PFLASH_PFAPR_M7AP_SHIFT                  (16U)
#define MEM_76_PFLS_PFLASH_PFAPR_M7AP_WIDTH                  (2U)
#define MEM_76_PFLS_PFLASH_PFAPR_M7AP(x)                     (((uint32_t)(((uint32_t)(x)) << MEM_76_PFLS_PFLASH_PFAPR_M7AP_SHIFT)) & MEM_76_PFLS_PFLASH_PFAPR_M7AP_MASK)

#define MEM_76_PFLS_PFLASH_PFAPR_M6AP_MASK                   (0xC0000U)
#define MEM_76_PFLS_PFLASH_PFAPR_M6AP_SHIFT                  (18U)
#define MEM_76_PFLS_PFLASH_PFAPR_M6AP_WIDTH                  (2U)
#define MEM_76_PFLS_PFLASH_PFAPR_M6AP(x)                     (((uint32_t)(((uint32_t)(x)) << MEM_76_PFLS_PFLASH_PFAPR_M6AP_SHIFT)) & MEM_76_PFLS_PFLASH_PFAPR_M6AP_MASK)

#define MEM_76_PFLS_PFLASH_PFAPR_M5AP_MASK                   (0x300000U)
#define MEM_76_PFLS_PFLASH_PFAPR_M5AP_SHIFT                  (20U)
#define MEM_76_PFLS_PFLASH_PFAPR_M5AP_WIDTH                  (2U)
#define MEM_76_PFLS_PFLASH_PFAPR_M5AP(x)                     (((uint32_t)(((uint32_t)(x)) << MEM_76_PFLS_PFLASH_PFAPR_M5AP_SHIFT)) & MEM_76_PFLS_PFLASH_PFAPR_M5AP_MASK)

#define MEM_76_PFLS_PFLASH_PFAPR_M4AP_MASK                   (0xC00000U)
#define MEM_76_PFLS_PFLASH_PFAPR_M4AP_SHIFT                  (22U)
#define MEM_76_PFLS_PFLASH_PFAPR_M4AP_WIDTH                  (2U)
#define MEM_76_PFLS_PFLASH_PFAPR_M4AP(x)                     (((uint32_t)(((uint32_t)(x)) << MEM_76_PFLS_PFLASH_PFAPR_M4AP_SHIFT)) & MEM_76_PFLS_PFLASH_PFAPR_M4AP_MASK)

#define MEM_76_PFLS_PFLASH_PFAPR_M2AP_MASK                   (0xC000000U)
#define MEM_76_PFLS_PFLASH_PFAPR_M2AP_SHIFT                  (26U)
#define MEM_76_PFLS_PFLASH_PFAPR_M2AP_WIDTH                  (2U)
#define MEM_76_PFLS_PFLASH_PFAPR_M2AP(x)                     (((uint32_t)(((uint32_t)(x)) << MEM_76_PFLS_PFLASH_PFAPR_M2AP_SHIFT)) & MEM_76_PFLS_PFLASH_PFAPR_M2AP_MASK)

#define MEM_76_PFLS_PFLASH_PFAPR_M1AP_MASK                   (0x30000000U)
#define MEM_76_PFLS_PFLASH_PFAPR_M1AP_SHIFT                  (28U)
#define MEM_76_PFLS_PFLASH_PFAPR_M1AP_WIDTH                  (2U)
#define MEM_76_PFLS_PFLASH_PFAPR_M1AP(x)                     (((uint32_t)(((uint32_t)(x)) << MEM_76_PFLS_PFLASH_PFAPR_M1AP_SHIFT)) & MEM_76_PFLS_PFLASH_PFAPR_M1AP_MASK)

#define MEM_76_PFLS_PFLASH_PFAPR_M0AP_MASK                   (0xC0000000U)
#define MEM_76_PFLS_PFLASH_PFAPR_M0AP_SHIFT                  (30U)
#define MEM_76_PFLS_PFLASH_PFAPR_M0AP_WIDTH                  (2U)
#define MEM_76_PFLS_PFLASH_PFAPR_M0AP(x)                     (((uint32_t)(((uint32_t)(x)) << MEM_76_PFLS_PFLASH_PFAPR_M0AP_SHIFT)) & MEM_76_PFLS_PFLASH_PFAPR_M0AP_MASK)
/*! @} */

/*! @name PFCPGM_PEADR_L - Platform Flash Memory Program Erase Address Logical */
/*! @{ */

#define MEM_76_PFLS_PFLASH_PFCPGM_PEADR_L_PEADR_L_MASK       (0xFFFFFFFFU)
#define MEM_76_PFLS_PFLASH_PFCPGM_PEADR_L_PEADR_L_SHIFT      (0U)
#define MEM_76_PFLS_PFLASH_PFCPGM_PEADR_L_PEADR_L_WIDTH      (32U)
#define MEM_76_PFLS_PFLASH_PFCPGM_PEADR_L_PEADR_L(x)         (((uint32_t)(((uint32_t)(x)) << MEM_76_PFLS_PFLASH_PFCPGM_PEADR_L_PEADR_L_SHIFT)) & MEM_76_PFLS_PFLASH_PFCPGM_PEADR_L_PEADR_L_MASK)
/*! @} */

/*! @name PFCPGM_PEADR_P - Platform Flash Memory Program Erase Address Physical */
/*! @{ */

#define MEM_76_PFLS_PFLASH_PFCPGM_PEADR_P_PEADR_P_MASK       (0xFFFFFFFFU)
#define MEM_76_PFLS_PFLASH_PFCPGM_PEADR_P_PEADR_P_SHIFT      (0U)
#define MEM_76_PFLS_PFLASH_PFCPGM_PEADR_P_PEADR_P_WIDTH      (32U)
#define MEM_76_PFLS_PFLASH_PFCPGM_PEADR_P_PEADR_P(x)         (((uint32_t)(((uint32_t)(x)) << MEM_76_PFLS_PFLASH_PFCPGM_PEADR_P_PEADR_P_SHIFT)) & MEM_76_PFLS_PFLASH_PFCPGM_PEADR_P_PEADR_P_MASK)
/*! @} */

/*! @name PFCPGM_XPEADR_L - Platform Flash Memory Express Program Erase Address Logical */
/*! @{ */

#define MEM_76_PFLS_PFLASH_PFCPGM_XPEADR_L_XPEADR_L_MASK     (0xFFFFFFFFU)
#define MEM_76_PFLS_PFLASH_PFCPGM_XPEADR_L_XPEADR_L_SHIFT    (0U)
#define MEM_76_PFLS_PFLASH_PFCPGM_XPEADR_L_XPEADR_L_WIDTH    (32U)
#define MEM_76_PFLS_PFLASH_PFCPGM_XPEADR_L_XPEADR_L(x)       (((uint32_t)(((uint32_t)(x)) << MEM_76_PFLS_PFLASH_PFCPGM_XPEADR_L_XPEADR_L_SHIFT)) & MEM_76_PFLS_PFLASH_PFCPGM_XPEADR_L_XPEADR_L_MASK)
/*! @} */

/*! @name PFCPGM_XPEADR_P - Platform Flash Memory Express Program Erase Address Physical */
/*! @{ */

#define MEM_76_PFLS_PFLASH_PFCPGM_XPEADR_P_XPEADR_P_MASK     (0xFFFFFFFFU)
#define MEM_76_PFLS_PFLASH_PFCPGM_XPEADR_P_XPEADR_P_SHIFT    (0U)
#define MEM_76_PFLS_PFLASH_PFCPGM_XPEADR_P_XPEADR_P_WIDTH    (32U)
#define MEM_76_PFLS_PFLASH_PFCPGM_XPEADR_P_XPEADR_P(x)       (((uint32_t)(((uint32_t)(x)) << MEM_76_PFLS_PFLASH_PFCPGM_XPEADR_P_XPEADR_P_SHIFT)) & MEM_76_PFLS_PFLASH_PFCPGM_XPEADR_P_XPEADR_P_MASK)
/*! @} */

/*! @name PFCBLK_SPELOCK - Block n Sector Program Erase Lock */
/*! @{ */

#define MEM_76_PFLS_PFLASH_PFCBLK_SPELOCK_SLCK_MASK          (0xFFFFFFFFU)
#define MEM_76_PFLS_PFLASH_PFCBLK_SPELOCK_SLCK_SHIFT         (0U)
#define MEM_76_PFLS_PFLASH_PFCBLK_SPELOCK_SLCK_WIDTH         (32U)
#define MEM_76_PFLS_PFLASH_PFCBLK_SPELOCK_SLCK(x)            (((uint32_t)(((uint32_t)(x)) << MEM_76_PFLS_PFLASH_PFCBLK_SPELOCK_SLCK_SHIFT)) & MEM_76_PFLS_PFLASH_PFCBLK_SPELOCK_SLCK_MASK)
/*! @} */

/*! @name PFCBLKU_SPELOCK - Block UTEST Sector Program Erase Lock */
/*! @{ */

#define MEM_76_PFLS_PFLASH_PFCBLKU_SPELOCK_SLCK_MASK         (0x1U)
#define MEM_76_PFLS_PFLASH_PFCBLKU_SPELOCK_SLCK_SHIFT        (0U)
#define MEM_76_PFLS_PFLASH_PFCBLKU_SPELOCK_SLCK_WIDTH        (1U)
#define MEM_76_PFLS_PFLASH_PFCBLKU_SPELOCK_SLCK(x)           (((uint32_t)(((uint32_t)(x)) << MEM_76_PFLS_PFLASH_PFCBLKU_SPELOCK_SLCK_SHIFT)) & MEM_76_PFLS_PFLASH_PFCBLKU_SPELOCK_SLCK_MASK)
/*! @} */

/*! @name PFCBLK_SSPELOCK - Block n Super Sector Program Erase Lock */
/*! @{ */

#define MEM_76_PFLS_PFLASH_PFCBLK_SSPELOCK_SSLCK_MASK        (0xFFFU)
#define MEM_76_PFLS_PFLASH_PFCBLK_SSPELOCK_SSLCK_SHIFT       (0U)
#define MEM_76_PFLS_PFLASH_PFCBLK_SSPELOCK_SSLCK_WIDTH       (12U)
#define MEM_76_PFLS_PFLASH_PFCBLK_SSPELOCK_SSLCK(x)          (((uint32_t)(((uint32_t)(x)) << MEM_76_PFLS_PFLASH_PFCBLK_SSPELOCK_SSLCK_SHIFT)) & MEM_76_PFLS_PFLASH_PFCBLK_SSPELOCK_SSLCK_MASK)
/*! @} */

/*! @name PFCBLK_SETSLOCK - Block n Set Sector Lock */
/*! @{ */

#define MEM_76_PFLS_PFLASH_PFCBLK_SETSLOCK_SETSLCK_MASK      (0xFFFFFFFFU)
#define MEM_76_PFLS_PFLASH_PFCBLK_SETSLOCK_SETSLCK_SHIFT     (0U)
#define MEM_76_PFLS_PFLASH_PFCBLK_SETSLOCK_SETSLCK_WIDTH     (32U)
#define MEM_76_PFLS_PFLASH_PFCBLK_SETSLOCK_SETSLCK(x)        (((uint32_t)(((uint32_t)(x)) << MEM_76_PFLS_PFLASH_PFCBLK_SETSLOCK_SETSLCK_SHIFT)) & MEM_76_PFLS_PFLASH_PFCBLK_SETSLOCK_SETSLCK_MASK)
/*! @} */

/*! @name PFCBLKU_SETSLOCK - Block UTEST Set Sector Lock */
/*! @{ */

#define MEM_76_PFLS_PFLASH_PFCBLKU_SETSLOCK_SETSLCK_MASK     (0x1U)
#define MEM_76_PFLS_PFLASH_PFCBLKU_SETSLOCK_SETSLCK_SHIFT    (0U)
#define MEM_76_PFLS_PFLASH_PFCBLKU_SETSLOCK_SETSLCK_WIDTH    (1U)
#define MEM_76_PFLS_PFLASH_PFCBLKU_SETSLOCK_SETSLCK(x)       (((uint32_t)(((uint32_t)(x)) << MEM_76_PFLS_PFLASH_PFCBLKU_SETSLOCK_SETSLCK_SHIFT)) & MEM_76_PFLS_PFLASH_PFCBLKU_SETSLOCK_SETSLCK_MASK)
/*! @} */

/*! @name PFCBLK_SSETSLOCK - Block n Set Super Sector Lock */
/*! @{ */

#define MEM_76_PFLS_PFLASH_PFCBLK_SSETSLOCK_SSETSLCK_MASK    (0xFFFU)
#define MEM_76_PFLS_PFLASH_PFCBLK_SSETSLOCK_SSETSLCK_SHIFT   (0U)
#define MEM_76_PFLS_PFLASH_PFCBLK_SSETSLOCK_SSETSLCK_WIDTH   (12U)
#define MEM_76_PFLS_PFLASH_PFCBLK_SSETSLOCK_SSETSLCK(x)      (((uint32_t)(((uint32_t)(x)) << MEM_76_PFLS_PFLASH_PFCBLK_SSETSLOCK_SSETSLCK_SHIFT)) & MEM_76_PFLS_PFLASH_PFCBLK_SSETSLOCK_SSETSLCK_MASK)
/*! @} */

/*! @name PFCBLK_LOCKMASTER_S - Block a Lock Master Sector b */
/*! @{ */

#define MEM_76_PFLS_PFLASH_PFCBLK_LOCKMASTER_S_LOCKMASTER_S_MASK (0xFFFFFFFFU)
#define MEM_76_PFLS_PFLASH_PFCBLK_LOCKMASTER_S_LOCKMASTER_S_SHIFT (0U)
#define MEM_76_PFLS_PFLASH_PFCBLK_LOCKMASTER_S_LOCKMASTER_S_WIDTH (32U)
#define MEM_76_PFLS_PFLASH_PFCBLK_LOCKMASTER_S_LOCKMASTER_S(x) (((uint32_t)(((uint32_t)(x)) << MEM_76_PFLS_PFLASH_PFCBLK_LOCKMASTER_S_LOCKMASTER_S_SHIFT)) & MEM_76_PFLS_PFLASH_PFCBLK_LOCKMASTER_S_LOCKMASTER_S_MASK)
/*! @} */

/*! @name PFCBLKU_LOCKMASTER_S - Block UTEST Lock Master Sector */
/*! @{ */

#define MEM_76_PFLS_PFLASH_PFCBLKU_LOCKMASTER_S_LOCKMASTER_S_MASK (0xFFU)
#define MEM_76_PFLS_PFLASH_PFCBLKU_LOCKMASTER_S_LOCKMASTER_S_SHIFT (0U)
#define MEM_76_PFLS_PFLASH_PFCBLKU_LOCKMASTER_S_LOCKMASTER_S_WIDTH (8U)
#define MEM_76_PFLS_PFLASH_PFCBLKU_LOCKMASTER_S_LOCKMASTER_S(x) (((uint32_t)(((uint32_t)(x)) << MEM_76_PFLS_PFLASH_PFCBLKU_LOCKMASTER_S_LOCKMASTER_S_SHIFT)) & MEM_76_PFLS_PFLASH_PFCBLKU_LOCKMASTER_S_LOCKMASTER_S_MASK)
/*! @} */

/*! @name PFCBLK_LOCKMASTER_SS - Block m Lock Master Super Sector n */
/*! @{ */

#define MEM_76_PFLS_PFLASH_PFCBLK_LOCKMASTER_SS_LOCKMASTER_SS_MASK (0xFFFFFFFFU)
#define MEM_76_PFLS_PFLASH_PFCBLK_LOCKMASTER_SS_LOCKMASTER_SS_SHIFT (0U)
#define MEM_76_PFLS_PFLASH_PFCBLK_LOCKMASTER_SS_LOCKMASTER_SS_WIDTH (32U)
#define MEM_76_PFLS_PFLASH_PFCBLK_LOCKMASTER_SS_LOCKMASTER_SS(x) (((uint32_t)(((uint32_t)(x)) << MEM_76_PFLS_PFLASH_PFCBLK_LOCKMASTER_SS_LOCKMASTER_SS_SHIFT)) & MEM_76_PFLS_PFLASH_PFCBLK_LOCKMASTER_SS_LOCKMASTER_SS_MASK)
/*! @} */

/*! @name DCMSTAT - DCM Status */
/*! @{ */

#define MEM_76_PFLS_PFLASH_DCMSTAT_DCMOTAR_MASK (0x1U)
#define MEM_76_PFLS_PFLASH_DCMSTAT_DCMOTAR_SHIFT (17U)
#define MEM_76_PFLS_PFLASH_DCMSTAT_DCMOTAR_WIDTH (1U)

#define MEM_76_PFLS_PFLASH_DCMSTAT_DCMOTAA_MASK (0x1U)
#define MEM_76_PFLS_PFLASH_DCMSTAT_DCMOTAA_SHIFT (16U)
#define MEM_76_PFLS_PFLASH_DCMSTAT_DCMOTAA_WIDTH (1U)

#endif
