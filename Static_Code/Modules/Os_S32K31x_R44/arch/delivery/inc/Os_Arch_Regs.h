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
**  SRC-MODULE: Os_Arch_Regs.h                                                **
**                                                                            **
**  TARGET    : S32K31x                                                       **
**                                                                            **
**  PRODUCT   : AUTOSAR OS                                                    **
**                                                                            **
**  PURPOSE   : Header file for S32K31x related register                      **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]:       Yes                                    **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]:    No                                     **
**                                                                            **
*******************************************************************************/

/* @Trace: SRS_BSW_00003 SRS_BSW_00006 SRS_BSW_00007 SRS_BSW_00009 SRS_BSW_00301 SRS_BSW_00302 SRS_BSW_00305
 SRS_BSW_00415 SRS_BSW_00305 SRS_BSW_00307 SRS_BSW_00308 SRS_BSW_00310 SRS_BSW_00328 SRS_BSW_00441 */
/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date           By            Description                         **
********************************************************************************
** 1.3.0     31-Jan-2024    HJ.Kim       Jira    CP44-4169                    **
** 1.1.1     23-Nov-2023    HJ.Kim       Jira    CP44-3306                    **
** 1.1.0      1-Sep-2023    HJ.Kim       Jira    CP44-2528                    **
**           29-Aug-2023    HJ.Kim       Jira    CP44-2442                    **
**            8-Jun-2023    HJ.Kim       Jira    CP44-2090                    **
** 1.0.1     19-Sep-2022    TinHV        Jira    CP44-192                     **
** 1.0.0.1   30-Jun-2022    TinHV        Jira    CP44-333                     **
** 1.0.0     13-Jun-2022    TinHV        Redmine #24717                       **
*******************************************************************************/
/* @Trace: SRS_PSRS_00003 SRS_PSRS_00002 */
/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace:begin<MISRA-C3:2.5:Not a defect:Justify with annotations> Macro is used for memory mapping */
/* polyspace-begin MISRA-C3:11.4 [Justified:Medium] "To access Registers" */
/* polyspace:begin<ISO-17961:intptrconv:Not a defect:Justify with annotations> To access Registers */

#ifndef OS_ARCH_REGS_H_
#define OS_ARCH_REGS_H_

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Platform_Types.h"
#include "Os_Arch_Types.h"

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
/**
 * @addtogroup OS_S32K31X_ESDD
 * @{ */
 
/** Macro for PRIV bit mask
 * \n{Ref: SWR_OS_S32K31X_006} */
#define OS_MASK_MSR_PR                              (0x00004000U)

 /** Macro for base priority
 * \n{Ref: SWR_OS_S32K31X_006} */
#define OS_MASK_BASEPRI                             (0x00000000U)

 /** Macro for valid LSB of IPR(i.e Priority should be shifted by this value)
 * \n{Ref: SWR_OS_S32K31X_006} */
#define OS_IPR_LSB                                  (0x00000004U)

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
/** @} */
#if (OS_FPU_SUPPORT == STD_ON)
extern FUNC(uint32, OS_CODE) Os_GetFpscr(void);
extern void Os_SetFpscr(uint32 param);
#endif
extern uint32 Os_GetSP(void);
extern uint32 Os_GetMSP(void);
extern void   Os_SetMSP(uint32 cortexM_msp);
extern uint32 Os_GetPSP(void);
extern void   Os_SetPSP(uint32 cortexM_psp);
extern void   Os_SwitchCurrentContext(P2CONST(Tdd_Os_ContextSwitch, AUTOMATIC, OS_CONST) pCurrentContext);
extern void   Os_ReturnKernelStack(void);
extern void   Os_LoadCurrentContext_NTISR(P2CONST(Tdd_Os_ContextSwitch, AUTOMATIC, OS_CONST) pCurrentContext);
extern void   Os_ReturnNTISRKernelStack(void);
extern void   Os_SetCONTROL(uint32 cortexM_mode);
extern uint32 Os_GetCONTROL(void);
extern uint32 Os_IrqGetVectNumber(void);

/* ----------------------------------------------------------------------------
   -- OS_S32_MPU Register Masks
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup OS_S32_MPU_Register_Masks OS_S32_MPU Register Masks
 * @{
 */

/* TYPE Bit Fields */
#define OS_S32_MPU_TYPE_SEPARATE_MASK               0x1u
#define OS_S32_MPU_TYPE_SEPARATE_SHIFT              0u
#define OS_S32_MPU_TYPE_SEPARATE_WIDTH              1u
#define OS_S32_MPU_TYPE_SEPARATE(x)                 (((uint32)(((uint32)(x))<<OS_S32_MPU_TYPE_SEPARATE_SHIFT))&OS_S32_MPU_TYPE_SEPARATE_MASK)
#define OS_S32_MPU_TYPE_DREGION_MASK                0xFF00u
#define OS_S32_MPU_TYPE_DREGION_SHIFT               8u
#define OS_S32_MPU_TYPE_DREGION_WIDTH               8u
#define OS_S32_MPU_TYPE_DREGION(x)                  (((uint32)(((uint32)(x))<<OS_S32_MPU_TYPE_DREGION_SHIFT))&OS_S32_MPU_TYPE_DREGION_MASK)
#define OS_S32_MPU_TYPE_IREGION_MASK                0xFF0000u
#define OS_S32_MPU_TYPE_IREGION_SHIFT               16u
#define OS_S32_MPU_TYPE_IREGION_WIDTH               8u
#define OS_S32_MPU_TYPE_IREGION(x)                  (((uint32)(((uint32)(x))<<OS_S32_MPU_TYPE_IREGION_SHIFT))&OS_S32_MPU_TYPE_IREGION_MASK)
/* CTRL Bit Fields */
#define OS_S32_MPU_CTRL_ENABLE_MASK                 0x1u
#define OS_S32_MPU_CTRL_ENABLE_SHIFT                0u
#define OS_S32_MPU_CTRL_ENABLE_WIDTH                1u
#define OS_S32_MPU_CTRL_ENABLE(x)                   (((uint32)(((uint32)(x))<<OS_S32_MPU_CTRL_ENABLE_SHIFT))&OS_S32_MPU_CTRL_ENABLE_MASK)
#define OS_S32_MPU_CTRL_HFNMIENA_MASK               0x2u
#define OS_S32_MPU_CTRL_HFNMIENA_SHIFT              1u
#define OS_S32_MPU_CTRL_HFNMIENA_WIDTH              1u
#define OS_S32_MPU_CTRL_HFNMIENA(x)                 (((uint32)(((uint32)(x))<<OS_S32_MPU_CTRL_HFNMIENA_SHIFT))&OS_S32_MPU_CTRL_HFNMIENA_MASK)
#define OS_S32_MPU_CTRL_PRIVDEFENA_MASK             0x4u
#define OS_S32_MPU_CTRL_PRIVDEFENA_SHIFT            2u
#define OS_S32_MPU_CTRL_PRIVDEFENA_WIDTH            1u
#define OS_S32_MPU_CTRL_PRIVDEFENA(x)               (((uint32)(((uint32)(x))<<OS_S32_MPU_CTRL_PRIVDEFENA_SHIFT))&OS_S32_MPU_CTRL_PRIVDEFENA_MASK)
/* RNR Bit Fields */
#define OS_S32_MPU_RNR_REGION_MASK                  0xFFu
#define OS_S32_MPU_RNR_REGION_SHIFT                 0u
#define OS_S32_MPU_RNR_REGION_WIDTH                 8u
#define OS_S32_MPU_RNR_REGION(x)                    (((uint32)(((uint32)(x))<<OS_S32_MPU_RNR_REGION_SHIFT))&OS_S32_MPU_RNR_REGION_MASK)
/* RBAR Bit Fields */
#define OS_S32_MPU_RBAR_REGION_MASK                 0xFu
#define OS_S32_MPU_RBAR_REGION_SHIFT                0u
#define OS_S32_MPU_RBAR_REGION_WIDTH                4u
#define OS_S32_MPU_RBAR_REGION(x)                   (((uint32)(((uint32)(x))<<OS_S32_MPU_RBAR_REGION_SHIFT))&OS_S32_MPU_RBAR_REGION_MASK)
#define OS_S32_MPU_RBAR_VALID_MASK                  0x10u
#define OS_S32_MPU_RBAR_VALID_SHIFT                 4u
#define OS_S32_MPU_RBAR_VALID_WIDTH                 1u
#define OS_S32_MPU_RBAR_VALID(x)                    (((uint32)(((uint32)(x))<<OS_S32_MPU_RBAR_VALID_SHIFT))&OS_S32_MPU_RBAR_VALID_MASK)
#define OS_S32_MPU_RBAR_ADDR_MASK                   0xFFFFFFE0u
#define OS_S32_MPU_RBAR_ADDR_SHIFT                  5u
#define OS_S32_MPU_RBAR_ADDR_WIDTH                  27u
#define OS_S32_MPU_RBAR_ADDR(x)                     (((uint32)(((uint32)(x))<<OS_S32_MPU_RBAR_ADDR_SHIFT))&OS_S32_MPU_RBAR_ADDR_MASK)
/* RASR Bit Fields */
#define OS_S32_MPU_RASR_ENABLE_MASK                 0x1u
#define OS_S32_MPU_RASR_ENABLE_SHIFT                0u
#define OS_S32_MPU_RASR_ENABLE_WIDTH                1u
#define OS_S32_MPU_RASR_ENABLE(x)                   (((uint32)(((uint32)(x))<<OS_S32_MPU_RASR_ENABLE_SHIFT))&OS_S32_MPU_RASR_ENABLE_MASK)
#define OS_S32_MPU_RASR_SIZE_MASK                   0x3Eu
#define OS_S32_MPU_RASR_SIZE_SHIFT                  1u
#define OS_S32_MPU_RASR_SIZE_WIDTH                  5u
#define OS_S32_MPU_RASR_SIZE(x)                     (((uint32)(((uint32)(x))<<OS_S32_MPU_RASR_SIZE_SHIFT))&OS_S32_MPU_RASR_SIZE_MASK)
#define OS_S32_MPU_RASR_SRD_MASK                    0xFF00u
#define OS_S32_MPU_RASR_SRD_SHIFT                   8u
#define OS_S32_MPU_RASR_SRD_WIDTH                   8u
#define OS_S32_MPU_RASR_SRD(x)                      (((uint32)(((uint32)(x))<<OS_S32_MPU_RASR_SRD_SHIFT))&OS_S32_MPU_RASR_SRD_MASK)
#define OS_S32_MPU_RASR_B_MASK                      0x10000u
#define OS_S32_MPU_RASR_B_SHIFT                     16u
#define OS_S32_MPU_RASR_B_WIDTH                     1u
#define OS_S32_MPU_RASR_B(x)                        (((uint32)(((uint32)(x))<<OS_S32_MPU_RASR_B_SHIFT))&OS_S32_MPU_RASR_B_MASK)
#define OS_S32_MPU_RASR_C_MASK                      0x20000u
#define OS_S32_MPU_RASR_C_SHIFT                     17u
#define OS_S32_MPU_RASR_C_WIDTH                     1u
#define OS_S32_MPU_RASR_C(x)                        (((uint32)(((uint32)(x))<<OS_S32_MPU_RASR_C_SHIFT))&OS_S32_MPU_RASR_C_MASK)
#define OS_S32_MPU_RASR_S_MASK                      0x40000u
#define OS_S32_MPU_RASR_S_SHIFT                     18u
#define OS_S32_MPU_RASR_S_WIDTH                     1u
#define OS_S32_MPU_RASR_S(x)                        (((uint32)(((uint32)(x))<<OS_S32_MPU_RASR_S_SHIFT))&OS_S32_MPU_RASR_S_MASK)
#define OS_S32_MPU_RASR_TEX_MASK                    0x380000u
#define OS_S32_MPU_RASR_TEX_SHIFT                   19u
#define OS_S32_MPU_RASR_TEX_WIDTH                   3u
#define OS_S32_MPU_RASR_TEX(x)                      (((uint32)(((uint32)(x))<<OS_S32_MPU_RASR_TEX_SHIFT))&OS_S32_MPU_RASR_TEX_MASK)
#define OS_S32_MPU_RASR_AP_MASK                     0x7000000u
#define OS_S32_MPU_RASR_AP_SHIFT                    24u
#define OS_S32_MPU_RASR_AP_WIDTH                    3u
#define OS_S32_MPU_RASR_AP(x)                       (((uint32)(((uint32)(x))<<OS_S32_MPU_RASR_AP_SHIFT))&OS_S32_MPU_RASR_AP_MASK)
#define OS_S32_MPU_RASR_XN_MASK                     0x10000000u
#define OS_S32_MPU_RASR_XN_SHIFT                    28u
#define OS_S32_MPU_RASR_XN_WIDTH                    1u
#define OS_S32_MPU_RASR_XN(x)                       (((uint32)(((uint32)(x))<<OS_S32_MPU_RASR_XN_SHIFT))&OS_S32_MPU_RASR_XN_MASK)
/* A_RBAR Bit Fields */
#define OS_S32_MPU_A_RBAR_REGION_MASK               0xFu
#define OS_S32_MPU_A_RBAR_REGION_SHIFT              0u
#define OS_S32_MPU_A_RBAR_REGION_WIDTH              4u
#define OS_S32_MPU_A_RBAR_REGION(x)                 (((uint32)(((uint32)(x))<<OS_S32_MPU_A_RBAR_REGION_SHIFT))&OS_S32_MPU_A_RBAR_REGION_MASK)
#define OS_S32_MPU_A_RBAR_VALID_MASK                0x10u
#define OS_S32_MPU_A_RBAR_VALID_SHIFT               4u
#define OS_S32_MPU_A_RBAR_VALID_WIDTH               1u
#define OS_S32_MPU_A_RBAR_VALID(x)                  (((uint32)(((uint32)(x))<<OS_S32_MPU_A_RBAR_VALID_SHIFT))&OS_S32_MPU_A_RBAR_VALID_MASK)
#define OS_S32_MPU_A_RBAR_ADDR_MASK                 0xFFFFFFE0u
#define OS_S32_MPU_A_RBAR_ADDR_SHIFT                5u
#define OS_S32_MPU_A_RBAR_ADDR_WIDTH                27u
#define OS_S32_MPU_A_RBAR_ADDR(x)                   (((uint32)(((uint32)(x))<<OS_S32_MPU_A_RBAR_ADDR_SHIFT))&OS_S32_MPU_A_RBAR_ADDR_MASK)
/* A_RASR Bit Fields */
#define OS_S32_MPU_A_RASR_ENABLE_MASK               0x1u
#define OS_S32_MPU_A_RASR_ENABLE_SHIFT              0u
#define OS_S32_MPU_A_RASR_ENABLE_WIDTH              1u
#define OS_S32_MPU_A_RASR_ENABLE(x)                 (((uint32)(((uint32)(x))<<OS_S32_MPU_A_RASR_ENABLE_SHIFT))&OS_S32_MPU_A_RASR_ENABLE_MASK)
#define OS_S32_MPU_A_RASR_SIZE_MASK                 0x3Eu
#define OS_S32_MPU_A_RASR_SIZE_SHIFT                1u
#define OS_S32_MPU_A_RASR_SIZE_WIDTH                5u
#define OS_S32_MPU_A_RASR_SIZE(x)                   (((uint32)(((uint32)(x))<<OS_S32_MPU_A_RASR_SIZE_SHIFT))&OS_S32_MPU_A_RASR_SIZE_MASK)
#define OS_S32_MPU_A_RASR_SRD_MASK                  0xFF00u
#define OS_S32_MPU_A_RASR_SRD_SHIFT                 8u
#define OS_S32_MPU_A_RASR_SRD_WIDTH                 8u
#define OS_S32_MPU_A_RASR_SRD(x)                    (((uint32)(((uint32)(x))<<OS_S32_MPU_A_RASR_SRD_SHIFT))&OS_S32_MPU_A_RASR_SRD_MASK)
#define OS_S32_MPU_A_RASR_B_MASK                    0x10000u
#define OS_S32_MPU_A_RASR_B_SHIFT                   16u
#define OS_S32_MPU_A_RASR_B_WIDTH                   1u
#define OS_S32_MPU_A_RASR_B(x)                      (((uint32)(((uint32)(x))<<OS_S32_MPU_A_RASR_B_SHIFT))&OS_S32_MPU_A_RASR_B_MASK)
#define OS_S32_MPU_A_RASR_C_MASK                    0x20000u
#define OS_S32_MPU_A_RASR_C_SHIFT                   17u
#define OS_S32_MPU_A_RASR_C_WIDTH                   1u
#define OS_S32_MPU_A_RASR_C(x)                      (((uint32)(((uint32)(x))<<OS_S32_MPU_A_RASR_C_SHIFT))&OS_S32_MPU_A_RASR_C_MASK)
#define OS_S32_MPU_A_RASR_S_MASK                    0x40000u
#define OS_S32_MPU_A_RASR_S_SHIFT                   18u
#define OS_S32_MPU_A_RASR_S_WIDTH                   1u
#define OS_S32_MPU_A_RASR_S(x)                      (((uint32)(((uint32)(x))<<OS_S32_MPU_A_RASR_S_SHIFT))&OS_S32_MPU_A_RASR_S_MASK)
#define OS_S32_MPU_A_RASR_TEX_MASK                  0x380000u
#define OS_S32_MPU_A_RASR_TEX_SHIFT                 19u
#define OS_S32_MPU_A_RASR_TEX_WIDTH                 3u
#define OS_S32_MPU_A_RASR_TEX(x)                    (((uint32)(((uint32)(x))<<OS_S32_MPU_A_RASR_TEX_SHIFT))&OS_S32_MPU_A_RASR_TEX_MASK)
#define OS_S32_MPU_A_RASR_AP_MASK                   0x7000000u
#define OS_S32_MPU_A_RASR_AP_SHIFT                  24u
#define OS_S32_MPU_A_RASR_AP_WIDTH                  3u
#define OS_S32_MPU_A_RASR_AP(x)                     (((uint32)(((uint32)(x))<<OS_S32_MPU_A_RASR_AP_SHIFT))&OS_S32_MPU_A_RASR_AP_MASK)
#define OS_S32_MPU_A_RASR_XN_MASK                   0x10000000u
#define OS_S32_MPU_A_RASR_XN_SHIFT                  28u
#define OS_S32_MPU_A_RASR_XN_WIDTH                  1u
#define OS_S32_MPU_A_RASR_XN(x)                     (((uint32)(((uint32)(x))<<OS_S32_MPU_A_RASR_XN_SHIFT))&OS_S32_MPU_A_RASR_XN_MASK)

/*!
 * @}
 */ /* end of group OS_S32_MPU_Register_Masks */

/*
 * FTFC (Flash Memory Module)
 */

/* Structure of FERSTAT register */
typedef volatile union
{
  struct
  {
    /* polyspace:begin<MISRA-C3:6.1:Not a defect:Justify with annotations> It is approprate type */
    Os_Reg8                 : 1;
    Os_Reg8 DFDIF           : 1;  /* Double Bit Fault Detect Interrupt Flag */
    Os_Reg8                 : 6;
    /* polyspace:end<MISRA-C3:6.1:Not a defect:Justify with annotations> It is approprate type */
  } B;
  sint8  I;
  uint8  U;
} OS_FTFC_FERSTAT_type;

/* Base address of FTFC */
#define OS_FTFC_BASE        0x40020000u

/* FERSTAT register */
#define OS_FTFC_FERSTAT     (*(OS_FTFC_FERSTAT_type *)(OS_FTFC_BASE + 0x2E))

/* @Trace: SafeOs_SUD_DATATYPE_00405 */
/* ----------------------------------------------------------------------------
   -- OS_STM Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/** OS_STM - Size of Registers Arrays */
#define OS_STM_CHANNEL_COUNT                         4u

#define OS_STM_CNT_MAX 0xFFFFFFFF
#define OS_STM0_IRQn         (39U)

#define OS_STM_CIR_CIF_MASK  (0x1U)
#define OS_STM_CCR_CEN_MASK  (0x1U)
#define OS_STM_CR_TEN_MASK   (0x1U)

typedef volatile union
{
  struct
  {
    Os_Reg32 TEN             : 1;  /* Timer enable/disable Selection */
    Os_Reg32 FRZ           : 1;  /* Stops the timer when the chip enters Debug mode */
    Os_Reg32                  : 6;  /* Channel 7 PWM enable bit */
    Os_Reg32 CPS          : 8;  /* Counter Prescaler */
    Os_Reg32                : 16;
  } B;
  sint32 I;
  uint32 U;
} OS_STM_CR_type;

typedef volatile union
{
  struct
  {
    Os_Reg32 CIF :1;
    Os_Reg32 :31;

  } B;

} OS_STM_CIR_type;

/** OS_STM - Register Layout Typedef */
typedef struct {
  Os_Reg32 CR;                                /**< Control, offset: 0x0 */
  Os_Reg32 CNT;                               /**< Count, offset: 0x4 */
  Os_Reg8 RESERVED_0[8];
  struct {                                         /* offset: 0x10, array step: 0x10 */
    Os_Reg32 CCR;                               /**< Channel Control, array offset: 0x10, array step: 0x10 */
    Os_Reg32 CIR;                               /**< Channel Interrupt, array offset: 0x14, array step: 0x10 */
    Os_Reg32 CMP;                               /**< Channel Compare, array offset: 0x18, array step: 0x10 */
    Os_Reg8 RESERVED_0[4];
  } CHANNEL[OS_STM_CHANNEL_COUNT];
} OS_STM_Type, *OS_STM_MemMapPtr;

/** Number of instances of the OS_STM module. */
#define OS_STM_INSTANCE_COUNT                       (1u)

/* OS_STM - Peripheral instance base addresses */
/** Peripheral OS_STM_0 base address */
#define OS_STM_0_BASE                            (0x40274000u)
/** Peripheral OS_STM_0 base pointer */
#define OS_STM_0                                 ((OS_STM_Type *)OS_STM_0_BASE)
/** Array initializer of OS_STM peripheral base addresses */
#define OS_STM_BASE_ADDRS                        { OS_STM_0_BASE }
/** Array initializer of OS_STM peripheral base pointers */
#define OS_STM_BASE_PTRS                         { OS_STM_0 }

/* ----------------------------------------------------------------------------
   -- OS_STM Register Masks
   ---------------------------------------------------------------------------- */
/* CR register for STM0 */
#define OS_STM0_CR           (*(volatile OS_STM_CR_type *)(OS_STM_0_BASE))
/* CNT register for STM0 */
#define OS_STM0_CNT          (*(volatile uint32 *)(OS_STM_0_BASE + 0x04U))
/* CCR register for STM0 CH0 */
#define OS_STM0_CH0_CCR      (*(volatile uint32 *)(OS_STM_0_BASE + 0x10U))
/* CIR register for STM0 CH0 */
#define OS_STM0_CH0_CIR      (*(volatile uint32 *)(OS_STM_0_BASE + 0x14U))
/* CMP register for STM0 CH0 */
#define OS_STM0_CH0_CMP      (*(volatile uint32 *)(OS_STM_0_BASE + 0x18U))

/*!
 * @addtogroup OS_STM_Register_Masks OS_STM Register Masks
 * @{
 */

/*! @name CR - Control */
/*! @{ */

#define OS_STM_CR_TEN_MASK                          (0x1U)
#define OS_STM_CR_TEN_SHIFT                         (0U)
#define OS_STM_CR_TEN_WIDTH                         (1U)
#define OS_STM_CR_TEN(x)                            (((uint32)(((uint32)(x)) << OS_STM_CR_TEN_SHIFT)) & OS_STM_CR_TEN_MASK)

#define OS_STM_CR_FRZ_MASK                          (0x2U)
#define OS_STM_CR_FRZ_SHIFT                         (1U)
#define OS_STM_CR_FRZ_WIDTH                         (1U)
#define OS_STM_CR_FRZ(x)                            (((uint32)(((uint32)(x)) << OS_STM_CR_FRZ_SHIFT)) & OS_STM_CR_FRZ_MASK)

#define OS_STM_CR_CPS_MASK                          (0xFF00U)
#define OS_STM_CR_CPS_SHIFT                         (8U)
#define OS_STM_CR_CPS_WIDTH                         (8U)
#define OS_STM_CR_CPS(x)                            (((uint32)(((uint32)(x)) << OS_STM_CR_CPS_SHIFT)) & OS_STM_CR_CPS_MASK)
/*! @} */

/*! @name CNT - Count */
/*! @{ */

#define OS_STM_CNT_CNT_MASK                         (0xFFFFFFFFU)
#define OS_STM_CNT_CNT_SHIFT                        (0U)
#define OS_STM_CNT_CNT_WIDTH                        (32U)
#define OS_STM_CNT_CNT(x)                           (((uint32)(((uint32)(x)) << OS_STM_CNT_CNT_SHIFT)) & OS_STM_CNT_CNT_MASK)
/*! @} */

/*! @name CCR - Channel Control */
/*! @{ */

#define OS_STM_CCR_CEN_MASK                         (0x1U)
#define OS_STM_CCR_CEN_SHIFT                        (0U)
#define OS_STM_CCR_CEN_WIDTH                        (1U)
#define OS_STM_CCR_CEN(x)                           (((uint32)(((uint32)(x)) << OS_STM_CCR_CEN_SHIFT)) & OS_STM_CCR_CEN_MASK)
/*! @} */

/*! @name CIR - Channel Interrupt */
/*! @{ */

#define OS_STM_CIR_CIF_MASK                         (0x1U)
#define OS_STM_CIR_CIF_SHIFT                        (0U)
#define OS_STM_CIR_CIF_WIDTH                        (1U)
#define OS_STM_CIR_CIF(x)                           (((uint32)(((uint32)(x)) << OS_STM_CIR_CIF_SHIFT)) & OS_STM_CIR_CIF_MASK)
/*! @} */

/*! @name CMP - Channel Compare */
/*! @{ */

#define OS_STM_CMP_CMP_MASK                         (0xFFFFFFFFU)
#define OS_STM_CMP_CMP_SHIFT                        (0U)
#define OS_STM_CMP_CMP_WIDTH                        (32U)
#define OS_STM_CMP_CMP(x)                           (((uint32)(((uint32)(x)) << OS_STM_CMP_CMP_SHIFT)) & OS_STM_CMP_CMP_MASK)

#define STM_CHANNEL0    0
#define STM_CHANNEL1    1
#define STM_CHANNEL2    2
#define STM_CHANNEL3    3

/* end of group OS_STM_Register_Masks */

/* ----------------------------------------------------------------------------
   -- S32_NVIC Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup S32_NVIC_Peripheral_Access_Layer S32_NVIC Peripheral Access Layer
 * @{
 */

/** S32_NVIC - Size of Registers Arrays */
#define NVIC_ISER_COUNT                      8u
#define NVIC_ICER_COUNT                      8u
#define NVIC_ISPR_COUNT                      8u
#define NVIC_ICPR_COUNT                      8u
#define NVIC_IABR_COUNT                      8u
#define NVIC_IP_COUNT                        240u

/** S32_NVIC - Register Layout Typedef */
typedef struct {
  Os_Reg32 RESERVED_0[4];
  Os_Reg32 ICTR;                              /**< Interrupt Control Type Register, offset: 0x4 */
  Os_Reg32 RESERVED_1[248];
  Os_Reg32 ISER[NVIC_ISER_COUNT];         /**< Interrupt Set Enable Register n, array offset: 0x100, array step: 0x4 */
  Os_Reg32 RESERVED_2[96];
  Os_Reg32 ICER[NVIC_ICER_COUNT];         /**< Interrupt Clear Enable Register n, array offset: 0x180, array step: 0x4 */
  Os_Reg32 RESERVED_3[96];
  Os_Reg32 ISPR[NVIC_ISPR_COUNT];         /**< Interrupt Set Pending Register n, array offset: 0x200, array step: 0x4 */
  Os_Reg32 RESERVED_4[96];
  Os_Reg32 ICPR[NVIC_ICPR_COUNT];         /**< Interrupt Clear Pending Register n, array offset: 0x280, array step: 0x4 */
  Os_Reg32 RESERVED_5[96];
  Os_Reg32 IABR[NVIC_IABR_COUNT];         /**< Interrupt Active bit Register n, array offset: 0x300, array step: 0x4 */
  Os_Reg32 RESERVED_6[224];
  Os_Reg32 IP[NVIC_IP_COUNT];              /**< Interrupt Priority Register n, array offset: 0x400, array step: 0x1 */
  Os_Reg32 RESERVED_7[2576];
  Os_Reg32 STIR;                              /**< Software Trigger Interrupt Register, offset: 0xF00 */
} NVIC_Type, *NVIC_MemMapPtr;

 /** Number of instances of the S32_NVIC module. */
#define NVIC_INSTANCE_COUNT                  (1u)

/* S32_NVIC - Peripheral instance base addresses */
/** Peripheral S32_NVIC base address */
#define NVIC_BASE                            (0xE000E000u)
/** Peripheral S32_NVIC base pointer */
#define NVIC                                 ((NVIC_Type *)NVIC_BASE)
/** Array initializer of S32_NVIC peripheral base addresses */
#define NVIC_BASE_ADDRS                      { NVIC_BASE }
/** Array initializer of S32_NVIC peripheral base pointers */
#define NVIC_BASE_PTRS                       { NVIC }

/* ----------------------------------------------------------------------------
   -- RTC Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup RTC_Peripheral_Access_Layer RTC Peripheral Access Layer
 * @{
 */
/** RTC Control - Register Layout Typedef */
typedef volatile union {
  struct
  {
    Os_Reg32 TRIG_EN   : 1; /* Trigger enable for Analog Comparator */
    Os_Reg32 reserved1 : 9;
    Os_Reg32 DIV32EN   : 1; /* Divide by 32 enable */
    Os_Reg32 DIV512EN  : 1; /* Divide by 512 enable */
    Os_Reg32 CLKSEL    : 2; /* Clock slect */
    Os_Reg32 APIIE     : 1; /* API interrupt enable */
    Os_Reg32 APIEN     : 1; /* Autonomous Periodic Interrupt Enable */
    Os_Reg32 reserved2 : 12;
    Os_Reg32 ROVREN    : 1; /* Counter Roll Over wakeup/Interrupt Enable */
    Os_Reg32 FRZEN     : 1; /* Freeze Enable Bit */
    Os_Reg32 RTCIE     : 1; /* RTC Interrupt Enable. */
    Os_Reg32 CNTEN     : 1; /* Counter Enable */

  } B;
  sint32 I;
  uint32 U;
} OS_RTC_Control_Type;

/** RTC Status - Register Layout Typedef */
typedef volatile union {
  struct
  {
    Os_Reg32 reserved  : 10;
    Os_Reg32 ROVRF     : 1;   /* Counter Roll Over Interrupt Flag */
    Os_Reg32 reserved1 : 2;
    Os_Reg32 APIF      : 1;   /* API Interrupt Flag */
    Os_Reg32 reserved2 : 3;
    Os_Reg32 INV_API   : 1;   /* Invalid APIVAL write */
    Os_Reg32 INV_RTC   : 1;   /* Invalid RTC write */
    Os_Reg32 reserved3 : 10;
    Os_Reg32 RTCF      : 1;   /* RTC Instrrupt Flag */
    Os_Reg32 reserved4 : 2;
  } B;
  sint32 I;
  uint32 U;
} OS_RTC_Status_Type;

/** RTC - Register Layout Typedef */
typedef struct {
  Os_Reg32 RTCSUPV;                           /**< RTC Supervisor control register, offset: 0x0 */
  Os_Reg32 RTCC;                              /**< RTC Control register, offset: 0x4 */
  Os_Reg32 RTCS;                              /**< RTC Status register, offset: 0x8 */
  Os_Reg32 RTCCNT;                            /**< RTC Counter register, offset: 0xC */
  Os_Reg32 APIVAL;                            /**< API Compare value register, offset: 0x10 */
  Os_Reg32 RTCVAL;                            /**< RTC Compare value register, offset: 0x14 */
} OS_RTC_Type;

/** Number of instances of the RTC module. */
#define RTC_INSTANCE_COUNT                       (1u)

#define OS_RTC_IRQn          (102U)

/* RTC - Peripheral instance base addresses */
/** Peripheral RTC base address */
#define RTC_BASE                              (0x40288000u)
/** Peripheral RTC base pointer */
#define RTC                                   ((OS_RTC_Type *)RTC_BASE)
/** Array initializer of RTC peripheral base addresses */
#define RTC_BASE_ADDRS                        { RTC_BASE }
/** Array initializer of RTC peripheral base pointers */
#define RTC_BASE_PTRS                         { RTC }
/* Max counter value of RTC */
#define OS_RTC_CNT_MAX       0xFFFFu
/** Peripheral RTC control pointer */
#define OS_RTCC                                (*(OS_RTC_Control_Type *)(RTC_BASE + 0x04U))
/** Peripheral RTC status pointer */
#define OS_RTCS                                (*(OS_RTC_Status_Type *)(RTC_BASE + 0x08U))
/** Peripheral RTC counter pointer */
#define OS_RTC_CNT                             (*(Os_Reg32 *)(RTC_BASE + 0xCU))

#define OS_RTCSUPV_SUPV_MASK                    (0x80000000U)
#define OS_RTCSUPV_SUPV_SHIFT                   (31U)
#define OS_RTCSUPV_SUPV_WIDTH                   (1U)
#define OS_RTCSUPV_SUPV(x)                      (((uint32)(((uint32)(x)) << OS_RTCSUPV_SUPV_SHIFT)) & OS_RTCSUPV_SUPV_MASK)

/* ----------------------------------------------------------------------------
   -- SWT Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup SWT_Peripheral_Access_Layer SWT Peripheral Access Layer
 * @{
 */
 
/** SWT - Register Layout Typedef */
typedef struct {
  Os_Reg32 CR;                                /**< Control, offset: 0x0 */
  Os_Reg32 IR;                                /**< Interrupt, offset: 0x4 */
  Os_Reg32 TO;                                /**< Timeout, offset: 0x8 */
  Os_Reg32 WN;                                /**< Window, offset: 0xC */
  Os_Reg32 SR;                                /**< Service, offset: 0x10 */
  Os_Reg32 CO;                                /**< Counter Output, offset: 0x14 */
  Os_Reg32 SK;                                /**< Service Key, offset: 0x18 */
  Os_Reg32 RRR;                               /**< Event Request, offset: 0x1C */
} OS_SWT_Type;

/** SWT Control - Register Layout Typedef */
typedef volatile union {
  struct
  {
    Os_Reg32 WEN          : 1; /*  Watchdog Enable */
    Os_Reg32 FRZ          : 1; /*  */
    Os_Reg32 STP          : 1; /*  */
    Os_Reg32 reserved1    : 1;
    Os_Reg32 SLK          : 1;
    Os_Reg32 HLK          : 1; /*  */
    Os_Reg32 ITR          : 1; /*  */
    Os_Reg32 WND          : 1; /* */
    Os_Reg32 RIA          : 1; /*  */
    Os_Reg32 SMD          : 2; /*  */
    Os_Reg32 reserved2    : 13; /*  */
    Os_Reg32 MAP7         : 1; /*  */
    Os_Reg32 MAP6         : 1; /*  */
    Os_Reg32 MAP5         : 1; /*  */
    Os_Reg32 MAP4         : 1; /*  */
    Os_Reg32 MAP3         : 1; /*  */
    Os_Reg32 MAP2         : 1; /*  */
    Os_Reg32 MAP1         : 1; /*  */
    Os_Reg32 MAP0         : 1; /* */
  } B;
  sint32 I;
  uint32 U;
} OS_SWT_Control_Type;

/** SWT Timeout - Register Layout Typedef */
typedef volatile union {
  struct
  {
    Os_Reg32 WTO          : 32; /*  Watchdog Timeout */
  } B;
  sint32 I;
  uint32 U;
} OS_SWT_Timeout_Type;

/** SWT Interrupt flag - Register Layout Typedef */
typedef volatile union {
  struct
  {
    Os_Reg32 TIF          : 1; /*  Interrupt flag */
    Os_Reg32 reserved1    : 31; /* Reserved */
  } B;
  sint32 I;
  uint32 U;
} OS_SWT_IR_Type;
/** Number of instances of the SWT module. */
#define SWT_INSTANCE_COUNT                       (1u)

/* SWT - Peripheral instance base addresses */
/** Peripheral SWT_0 base address */
#define SWT_0_BASE                            ((volatile) 0x40270000u)
/** Peripheral SWT_0 base pointer */
#define SWT_0                                 ((OS_SWT_Type *)SWT_0_BASE)
/** Array initializer of SWT peripheral base addresses */
#define SWT_BASE_ADDRS                        { SWT_0_BASE }
/** Array initializer of SWT peripheral base pointers */
#define SWT_BASE_PTRS                         { SWT_0 }
/* Max counter value of SWT */
#define OS_SWT_CNT_MAX       0xFFFFu

/** Peripheral SWT_0 control pointer */
#define SWT_0_CR                              (*(OS_SWT_Control_Type *)SWT_0_BASE)
/** Peripheral SWT_0 interrupt pointer */
#define SWT_0_IR                              (*(OS_SWT_IR_Type *)(SWT_0_BASE + 0x04U))
/** Peripheral SWT_0 control pointer */
#define SWT_0_TO                              (*(OS_SWT_Timeout_Type *)(SWT_0_BASE + 0x08U))
/** Peripheral SWT_0 conter output pointer */
#define SWT_0_CO                              (*(Os_Reg32 *)(SWT_0_BASE + 0x14U))
/* polyspace-end MISRA-C3:19.2 */

/* ----------------------------------------------------------------------------
   -- PIT Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup PIT_Peripheral_Access_Layer PIT Peripheral Access Layer
 * @{
 */

/** PIT - Size of Registers Arrays */
#define PIT_TIMER_COUNT                           4u

/** PIT - Register Layout Typedef */
typedef struct {
  Os_Reg32 MCR;                               /**< PIT Module Control Register, offset: 0x0 */
  Os_Reg32 RESERVED_0[220];
  Os_Reg32 LTMR64H;                           /**< PIT Upper Lifetime Timer Register, offset: 0xE0 */
  Os_Reg32 LTMR64L;                           /**< PIT Lower Lifetime Timer Register, offset: 0xE4 */
  Os_Reg32 RESERVED_1[4];
  Os_Reg32 RTI_LDVAL_STAT;                    /**< RTI Timer Load Value Sync Status Register, offset: 0xEC */
  Os_Reg32 RTI_LDVAL;                         /**< Timer Load Value Register, offset: 0xF0 */
  Os_Reg32 RTI_CVAL;                          /**< Current Timer Value Register, offset: 0xF4 */
  Os_Reg32 RTI_TCTRL;                         /**< Timer Control Register, offset: 0xF8 */
  Os_Reg32 RTI_TFLG;                          /**< Timer Flag Register, offset: 0xFC */
  struct {                                         /* offset: 0x100, array step: 0x10 */
    Os_Reg32 LDVAL;                             /**< Timer Load Value Register, array offset: 0x100, array step: 0x10 */
    Os_Reg32 CVAL;                              /**< Current Timer Value Register, array offset: 0x104, array step: 0x10 */
    Os_Reg32 TCTRL;                             /**< Timer Control Register, array offset: 0x108, array step: 0x10 */
    Os_Reg32 TFLG;                              /**< Timer Flag Register, array offset: 0x10C, array step: 0x10 */
  } TIMER[PIT_TIMER_COUNT];
} OS_PIT_Type, *OS_PIT_MemMapPtr;

/** Number of instances of the PIT module. */
#define PIT_INSTANCE_COUNT                       (2u)

/* PIT - Peripheral instance base addresses */
/** Peripheral PIT_0 base address */
#define OS_PIT_0_BASE                            ((volatile) 0x400B0000u)
/** Peripheral PIT_0 base pointer */
#define OS_PIT_0                                 ((volatile OS_PIT_Type *)OS_PIT_0_BASE)
/** Peripheral PIT_0 timer pointer */
// #define OS_PIT_0_TIMER_0                         ((volatile OS_PIT_Type *) (OS_PIT_0_BASE + 0x100)
/** Peripheral PIT_1 base address */
#define OS_PIT_1_BASE                            ((volatile) 0x400B4000u)
/** Peripheral PIT_1 base pointer */
#define OS_PIT_1                                 ((OS_PIT_Type *)OS_PIT_1_BASE)
/** Array initializer of PIT peripheral base addresses */
#define OS_PIT_BASE_ADDRS                        { OS_PIT_0_BASE, OS_PIT_1_BASE }
/** Array initializer of PIT peripheral base pointers */
#define OS_PIT_BASE_PTRS                         { OS_PIT_0, OS_PIT_1 }

#define PIT_TCTRL_TEN_MASK                       (0x1U)
#define PIT_TCTRL_TIE_MASK                       (0x2U)
#define PIT_TFLG_TIF_MASK                        (0x1U)

/*
 * SBC (System Control Block)
 */

/* polyspace-begin MISRA-C3:19.2 [Justified:Low] "These unions are used to specify register" */
/* Structure of CFSR (Configurable Fault Status Register) register */
typedef volatile union
{
  struct
  {
    Os_Reg32                : 1;
    Os_Reg32 VECTTBL        : 1;
    Os_Reg32                : 28;
    Os_Reg32 FORCED         : 1;
    Os_Reg32 DEBUGEVT       : 1;
  } B;
  sint32 I;
  uint32 U;
} OS_SBC_HFSR_type;

/* HFSR register */
#define OS_SBC_HFSR          (*(volatile OS_SBC_HFSR_type *)(0xE000ED2Cu))

/* Structure of CFSR (Configurable Fault Status Register) register */
typedef volatile union
{
  struct
  {
    Os_Reg32 MemManage      : 8;  /* MemManage */
    Os_Reg32 BusFault       : 8;  /* BusFault */
    Os_Reg32 UsageFault     : 16; /* UsageFault */
  } B;
  sint32 I;
  uint32 U;
} OS_SBC_CFSR_type;
/* polyspace-end MISRA-C3:19.2 */

/* @Trace: SafeOs_SUD_DATATYPE_00401 */
/* CFSR register */
#define OS_SBC_CFSR          (*(volatile OS_SBC_CFSR_type *)(0xE000ED28u))

/* Mask for MMFSR error bit */
#define OS_MMFSR_ERROR_MASK  0x3Fu

/* Mask for MMFSR valid bit */
#define OS_MMFSR_VALID_MASK  0x80u

/* MMFAR register */
#define OS_SBC_MMFAR        (*(volatile uint32 *) 0xE000ED34u)

/* Mask for BFSR error bit */
#define OS_BFSR_ERROR_MASK   0x3Fu

/* Mask for BFSR valid bit */
#define OS_BFSR_VALID_MASK   0x80u

/* BFAR register */
#define OS_SBC_BFAR         (*(volatile uint32 *) 0xE000ED38u)

/** Address of the PRI 15 (Systick) of System Handler Priority Register 3 */
#define OS_SHPR3_PRI_15_ADDR   ((volatile uint8 *)0xE000ED23u)

/*System Handler Priority Register 3 for Cortex M7*/
#define OS_SHPR3_ADDR   ((volatile uint32 *)0xE000ED20u)

/* Structure of CCR (Configuration and Control Register) register */
typedef volatile union
{
  struct
  {
    Os_Reg32 NONBASETHRDENA      : 1;  /* NONBASETHRDENA */
    Os_Reg32 USERSETMPEND        : 1;  /* USERSETMPEND */
    Os_Reg32                     : 1;  /* Reserved */
    Os_Reg32 UNALIGN_TRP         : 1;  /* UNALIGN_TRP */
    Os_Reg32 DIV_0_TRP           : 1;  /* DIV_0_TRP */
    Os_Reg32                     : 3;  /* Reserved */
    Os_Reg32 BFHFNMIGN           : 1;  /* BFHFNMIGN */
    Os_Reg32 STKALIGN            : 1;  /* STKALIGN */
    Os_Reg32                     : 6;  /* Reserved */
    Os_Reg32 DC                  : 1;  /* DC */
    Os_Reg32 IC                  : 1;  /* IC */
    Os_Reg32 BP                  : 1;  /* BP */
    Os_Reg32                     : 13; /* Reserved */
  } B;
  sint32 I;
  uint32 U;
} OS_SCB_CCR_type;

/* CFSR register */
#define OS_SCB_CCR          (*(volatile OS_SCB_CCR_type *)(0xE000ED14u))

/* Structure of AIRCR (Application Interrupt and Reset Control Register) register */
typedef volatile union
{
  struct
  {
    Os_Reg32 VECTRESET           : 1;  /* VECTRESET */
    Os_Reg32 VECTCLRACTIVE       : 1;  /* VECTCLRACTIVE */
    Os_Reg32 SYSRESETREQ         : 1;  /* SYSRESETREQ */
    Os_Reg32                     : 5;  /* Reserved */
    Os_Reg32 PRIGROUP            : 3;  /* PRIGROUP */
    Os_Reg32                     : 4;  /* Reserved */
    Os_Reg32 ENDIANNESS          : 1;  /* ENDIANNESS */
    Os_Reg32 VECTKEY             : 16; /* VECTKEY */
  } B;
  sint32 I;
  uint32 U;
} OS_SCB_AIRCR_type;

/* CFSR register */
#define OS_SCB_AIRCR       (*(volatile OS_SCB_AIRCR_type *)(0xE000ED0Cu))

/* Structure of CPACR (Coprocessor Access Control Register) register */
typedef volatile union
{
  struct
  {
    Os_Reg32                     : 20;  /* Reserved */
    Os_Reg32 CP11                : 2;
    Os_Reg32 CP10                : 2;
    Os_Reg32                     : 8;   /* Reserved */
  } B;
  sint32 I;
  uint32 U;
} OS_SCB_CPACR_type;

#define OS_SCB_CPACR          (*(volatile OS_SCB_CPACR_type *)(0xE000ED88u))

#define OS_SCB_CPACR_CP10_ACCESS_DENIED     0x00u
#define OS_SCB_CPACR_CP10_PRIVILEGED_ACCSS  0x01u
#define OS_SCB_CPACR_CP10_RESERVED          0x02u
#define OS_SCB_CPACR_CP10_FULL_ACCESS       0x03u
#define OS_SCB_CPACR_CP11_ACCESS_DENIED     0x00u
#define OS_SCB_CPACR_CP11_PRIVILEGED_ACCSS  0x01u
#define OS_SCB_CPACR_CP11_RESERVED          0x02u
#define OS_SCB_CPACR_CP11_FULL_ACCESS       0x03u

/* Structure of FPCCR (Floating-point Context Control Register) register */
typedef volatile union
{
  struct
  {
    Os_Reg32 LSPACT              : 1;
    Os_Reg32 USER                : 1;
    Os_Reg32                     : 1;   /* Reserved */
    Os_Reg32 THREAD              : 1;
    Os_Reg32 HFRDY               : 1;
    Os_Reg32 MMRDY               : 1;
    Os_Reg32 BFRDY               : 1;
    Os_Reg32                     : 1;   /* Reserved */
    Os_Reg32 MONRDY              : 1;
    Os_Reg32                     : 21;   /* Reserved */
    Os_Reg32 LSPEN               : 1;
    Os_Reg32 ASPEN               : 1;
  } B;
  sint32 I;
  uint32 U;
} OS_FPU_FPCCR_type;

#define OS_FPU_FPCCR          (*(volatile OS_FPU_FPCCR_type *)(0xE000EF34u))

#define OS_FPU_FPCCR_LSPEN_DISABLE          0x00u
#define OS_FPU_FPCCR_LSPEN_ENABLE           0x01u
#define OS_FPU_FPCCR_ASPEN_DISABLE          0x00u
#define OS_FPU_FPCCR_ASPEN_ENABLE           0x01u

/* @Trace: SafeOs_SUD_DATATYPE_00404 */
/*
 * SYSTICK (The System Timer)
 */

/** Structure of SysTick Control and Status Register */
typedef volatile struct
{
  Os_Reg32 ENABLE         : 1;  /**< Enables the counter */
  Os_Reg32 TICKINT        : 1;  /**< Enables SysTick exception request */
  Os_Reg32 CLKSOURCE      : 1;  /**< Indicates the clock source:
                                     0 = external clock, 1 = processor clock */
  Os_Reg32 reserved1      : 13;
  Os_Reg32 COUNTFLAG      : 1;  /**< Returns 1 if timer counted to 0
                                     since last time this was read */
  Os_Reg32 reserved2      : 15;
} OS_SYST_CSR_type;

/** SysTick Control and Status Register */
#define OS_SYST_CSR     (*(volatile OS_SYST_CSR_type *)0xE000E010u)
/** Processor clock value of the SYST_CSR */
#define OS_SYST_CSR_CLKSOURCE_PROCESSOR     (1u)

/** SysTick Reload Value Register(Valid only 24bit) */
#define OS_SYST_RVR     (*(volatile uint32 *)0xE000E014u)

/** SysTick Current Value Register(Valid only 24bit) */
#define OS_SYST_CVR     (*(volatile uint32 *)0xE000E018u)


/* @Trace: SafeOs_SUD_DATATYPE_00403 */
/* ----------------------------------------------------------------------------
   -- OS_S32_MPU Peripheral Access Layer
   ---------------------------------------------------------------------------- */

/*!
 * @addtogroup OS_S32_MPU_Peripheral_Access_Layer OS_S32_MPU Peripheral Access Layer
 */
/** OS_S32_MPU - Size of Registers Arrays */
/* maximum number of MPU regison supported */
#define OS_MPU_MAX_NUM                        16u
/* MPU Region number that is reserved for stack */
#define OS_MPU_REGION_STACK                   15u

/* MPU Type Register Definitions */
#define OS_MPU_TYPE_IREGION_POS               16u                                           /*!< MPU TYPE: IREGION Position */
#define OS_MPU_TYPE_IREGION_MSK               (0xFFu << OS_MPU_TYPE_IREGION_POS)           /*!< MPU TYPE: IREGION Mask */

#define OS_MPU_TYPE_DREGION_POS               8u                                            /*!< MPU TYPE: DREGION Position */
#define OS_MPU_TYPE_DREGION_MSK               (0xFFu << OS_MPU_TYPE_DREGION_POS)           /*!< MPU TYPE: DREGION Mask */

#define OS_MPU_TYPE_SEPARATE_POS              0u                                            /*!< MPU TYPE: SEPARATE Position */
#define OS_MPU_TYPE_SEPARATE_MSK              (1u << OS_MPU_TYPE_SEPARATE_POS)             /*!< MPU TYPE: SEPARATE Mask */

/* MPU Control Register Definitions */
#define OS_MPU_CTRL_PRIVDEFENA_POS            2u                                            /*!< MPU CTRL: PRIVDEFENA Position */
#define OS_MPU_CTRL_PRIVDEFENA_MSK            (1u << OS_MPU_CTRL_PRIVDEFENA_POS)           /*!< MPU CTRL: PRIVDEFENA Mask */

#define OS_MPU_CTRL_HFNMIENA_POS              1u                                            /*!< MPU CTRL: HFNMIENA Position */
#define OS_MPU_CTRL_HFNMIENA_MSK              (1u << OS_MPU_CTRL_HFNMIENA_POS)             /*!< MPU CTRL: HFNMIENA Mask */

#define OS_MPU_CTRL_ENABLE_POS                0u                                            /*!< MPU CTRL: ENABLE Position */
#define OS_MPU_CTRL_ENABLE_MSK                (1u << OS_MPU_CTRL_ENABLE_POS)               /*!< MPU CTRL: ENABLE Mask */

/* MPU Region Number Register Definitions */
#define OS_MPU_RNR_REGION_POS                 0u                                            /*!< MPU RNR: REGION Position */
#define OS_MPU_RNR_REGION_MSK                 (0xFFu << OS_MPU_RNR_REGION_POS)             /*!< MPU RNR: REGION Mask */

/* MPU Region Base Address Register Definitions */
#define OS_MPU_RBAR_ADDR_POS                  5u                                            /*!< MPU RBAR: ADDR Position */
#define OS_MPU_RBAR_ADDR_MSK                  (0x07FFFFFFu << OS_MPU_RBAR_ADDR_POS)        /*!< MPU RBAR: ADDR Mask */

#define OS_MPU_RBAR_VALID_POS                 4u                                            /*!< MPU RBAR: VALID Position */
#define OS_MPU_RBAR_VALID_MSK                 (0x1u << OS_MPU_RBAR_VALID_POS)              /*!< MPU RBAR: VALID Mask */

#define OS_MPU_RBAR_REGION_POS                0u                                            /*!< MPU RBAR: REGION Position */
#define OS_MPU_RBAR_REGION_MSK                (0xFu << OS_MPU_RBAR_REGION_POS)             /*!< MPU RBAR: REGION Mask */

/* MPU Region Attribute and Size Register Definitions */
#define OS_MPU_RASR_XN_POS                    28u                                           /*!< MPU RASR: ATTRS.XN Position */
#define OS_MPU_RASR_XN_MSK                    (0x1u << OS_MPU_RASR_XN_POS)                 /*!< MPU RASR: ATTRS.XN Mask */

#define OS_MPU_RASR_AP_POS                    24u                                           /*!< MPU RASR: ATTRS.AP Position */
#define OS_MPU_RASR_AP_MSK                    (0x7u << OS_MPU_RASR_AP_POS)                 /*!< MPU RASR: ATTRS.AP Mask */

#define OS_MPU_RASR_TEX_POS                   19u                                           /*!< MPU RASR: ATTRS.TEX Position */
#define OS_MPU_RASR_TEX_MSK                   (0x7u << OS_MPU_RASR_TEX_POS)                /*!< MPU RASR: ATTRS.TEX Mask */

#define OS_MPU_RASR_S_POS                     18u                                           /*!< MPU RASR: ATTRS.S Position */
#define OS_MPU_RASR_S_MSK                     (0x1u << OS_MPU_RASR_S_POS)                  /*!< MPU RASR: ATTRS.S Mask */

#define OS_MPU_RASR_C_POS                     17u                                           /*!< MPU RASR: ATTRS.C Position */
#define OS_MPU_RASR_C_MSK                     (0x1u << OS_MPU_RASR_C_POS)                  /*!< MPU RASR: ATTRS.C Mask */

#define OS_MPU_RASR_B_POS                     16u                                           /*!< MPU RASR: ATTRS.B Position */
#define OS_MPU_RASR_B_MSK                     (0x1u << OS_MPU_RASR_B_POS)                  /*!< MPU RASR: ATTRS.B Mask */

#define OS_MPU_RASR_ATTRS_POS                 16u                                           /*!< MPU RASR: MPU Region Attribute field Position */
#define OS_MPU_RASR_ATTRS_MSK                 (0xFFFFu << OS_MPU_RASR_ATTRS_POS)           /*!< MPU RASR: MPU Region Attribute field Mask */

#define OS_MPU_RASR_SRD_POS                   8u                                            /*!< MPU RASR: Sub-Region Disable Position */
#define OS_MPU_RASR_SRD_MSK                   (0xFFu << OS_MPU_RASR_SRD_POS)    

#define OS_MPU_RASR_SIZE_POS                  1u                                            /*!< MPU RASR: Region Size Field Position */
#define OS_MPU_RASR_SIZE_MSK                  (0x1Fu << OS_MPU_RASR_SIZE_POS)              /*!< MPU RASR: Region Size Field Mask */

#define OS_MPU_RASR_ENABLE_POS                0u                                            /*!< MPU RASR: Region enable bit Position */
#define OS_MPU_RASR_ENABLE_MSK                (0x1u << OS_MPU_RASR_ENABLE_POS)             /*!< MPU RASR: Region enable bit Disable Mask */

#define OS_MPU_MAX_SIZE_MSK                   0x1Fu
#define OS_MPU_MAX_SIZE                       0xFFFFFFFFu

/** Specifies status of APIs of this driver */
typedef enum
{
  OS_MPU_SUCCESS = 0u, /**< The API completed in success */
  OS_MPU_FAILURE,      /**< The API finished in failure */
} os_en_mpu_status_t;

/** Specifies enable/disable of the MPU */
typedef enum
{
  OS_MPU_GLOBAL_DISABLE = (0u),                 /**< Disable  */
  OS_MPU_GLOBAL_ENABLE  = (OS_MPU_CTRL_ENABLE_MSK), /**< Enable  */
} os_en_mpu_global_en_t;

/** Specifies region size of the MPU region */
typedef enum
{
  OS_MPU_SIZE_2B    = (0x00u << OS_MPU_RASR_SIZE_POS), /**< Invalid value */
  OS_MPU_SIZE_4B    = (0x01u << OS_MPU_RASR_SIZE_POS), /**< Invalid value */
  OS_MPU_SIZE_8B    = (0x02u << OS_MPU_RASR_SIZE_POS), /**< Invalid value */
  OS_MPU_SIZE_16B   = (0x03u << OS_MPU_RASR_SIZE_POS), /**< Invalid value */
  OS_MPU_SIZE_32B   = (0x04u << OS_MPU_RASR_SIZE_POS), /**< 32 Byte (Only for M4/M7) */
  OS_MPU_SIZE_64B   = (0x05u << OS_MPU_RASR_SIZE_POS), /**< 64 Byte (Only for M4/M7) */
  OS_MPU_SIZE_128B  = (0x06u << OS_MPU_RASR_SIZE_POS), /**< 128 Byte (Only for M4/M7) */
  OS_MPU_SIZE_256B  = (0x07u << OS_MPU_RASR_SIZE_POS), /**< 256 Byte */
  OS_MPU_SIZE_512B  = (0x08u << OS_MPU_RASR_SIZE_POS), /**< 512 Byte */
  OS_MPU_SIZE_1KB   = (0x09u << OS_MPU_RASR_SIZE_POS), /**< 1K Byte */
  OS_MPU_SIZE_2KB   = (0x0Au << OS_MPU_RASR_SIZE_POS), /**< 2K Byte */
  OS_MPU_SIZE_4KB   = (0x0Bu << OS_MPU_RASR_SIZE_POS), /**< 4K Byte */
  OS_MPU_SIZE_8KB   = (0x0Cu << OS_MPU_RASR_SIZE_POS), /**< 8K Byte */
  OS_MPU_SIZE_16KB  = (0x0Du << OS_MPU_RASR_SIZE_POS), /**< 16K Byte */
  OS_MPU_SIZE_32KB  = (0x0Eu << OS_MPU_RASR_SIZE_POS), /**< 32K Byte */
  OS_MPU_SIZE_64KB  = (0x0Fu << OS_MPU_RASR_SIZE_POS), /**< 64K Byte */
  OS_MPU_SIZE_128KB = (0x10u << OS_MPU_RASR_SIZE_POS), /**< 128K Byte */
  OS_MPU_SIZE_256KB = (0x11u << OS_MPU_RASR_SIZE_POS), /**< 256K Byte */
  OS_MPU_SIZE_512KB = (0x12u << OS_MPU_RASR_SIZE_POS), /**< 512K Byte */
  OS_MPU_SIZE_1MB   = (0x13u << OS_MPU_RASR_SIZE_POS), /**< 1M Byte */
  OS_MPU_SIZE_2MB   = (0x14u << OS_MPU_RASR_SIZE_POS), /**< 2M Byte */
  OS_MPU_SIZE_4MB   = (0x15u << OS_MPU_RASR_SIZE_POS), /**< 4M Byte */
  OS_MPU_SIZE_8MB   = (0x16u << OS_MPU_RASR_SIZE_POS), /**< 8M Byte */
  OS_MPU_SIZE_16MB  = (0x17u << OS_MPU_RASR_SIZE_POS), /**< 16M Byte */
  OS_MPU_SIZE_32MB  = (0x18u << OS_MPU_RASR_SIZE_POS), /**< 32M Byte */
  OS_MPU_SIZE_64MB  = (0x19u << OS_MPU_RASR_SIZE_POS), /**< 64M Byte */
  OS_MPU_SIZE_128MB = (0x1Au << OS_MPU_RASR_SIZE_POS), /**< 128M Byte */
  OS_MPU_SIZE_256MB = (0x1Bu << OS_MPU_RASR_SIZE_POS), /**< 256M Byte */
  OS_MPU_SIZE_512MB = (0x1Cu << OS_MPU_RASR_SIZE_POS), /**< 512M Byte */
  OS_MPU_SIZE_1GB   = (0x1Du << OS_MPU_RASR_SIZE_POS), /**< 1G Byte */
  OS_MPU_SIZE_2GB   = (0x1Eu << OS_MPU_RASR_SIZE_POS), /**< 2G Byte */
  OS_MPU_SIZE_4GB   = (0x1Fu << OS_MPU_RASR_SIZE_POS), /**< 4G Byte, Invalid value */
} os_en_mpu_region_size_t;

/** Specifies access permission of the MPU region */
typedef enum
{
  OS_MPU_ACCESS_P_NO_ACCESS       = (0x0u << OS_MPU_RASR_AP_POS), /**< All accesses generate a permission fault  */
  OS_MPU_ACCESS_P_PRIV_RW         = (0x1u << OS_MPU_RASR_AP_POS), /**< Access from privileged software only  */
  OS_MPU_ACCESS_P_PRIV_RW_USER_RO = (0x2u << OS_MPU_RASR_AP_POS), /**< Writes by unprivileged software generate a permission fault  */
  OS_MPU_ACCESS_P_FULL_ACCESS     = (0x3u << OS_MPU_RASR_AP_POS), /**< Full access  */
  OS_MPU_ACCESS_P_PRIV_RO         = (0x5u << OS_MPU_RASR_AP_POS), /**< Reads by privileged software only  */
  OS_MPU_ACCESS_P_RO              = (0x6u << OS_MPU_RASR_AP_POS), /**< Read only, by privileged or unprivileged software  */
} os_en_mpu_access_p_t;

/** Specifies attribute of the MPU region */
typedef enum
{
  OS_MPU_ATTR_STR_ORD_DEV               = ((0x0u << OS_MPU_RASR_TEX_POS)), /**< Strongly-ordered, shareable. */
  OS_MPU_ATTR_SHR_DEV                   = ((0x0u << OS_MPU_RASR_TEX_POS) | OS_MPU_RASR_B_MSK), /**< Device,           shareable. */

  OS_MPU_ATTR_NORM_MEM_WT               = ((0x0u << OS_MPU_RASR_TEX_POS) | OS_MPU_RASR_C_MSK), /**< Normal,           Not shareable, Outer and inner write-through. No write allocate. */
  OS_MPU_ATTR_NORM_SHR_MEM_WT           = ((0x0u << OS_MPU_RASR_TEX_POS) | OS_MPU_RASR_C_MSK | OS_MPU_RASR_S_MSK), /**< Normal,           shareable,     Outer and inner write-through. No write allocate. */
  OS_MPU_ATTR_NORM_MEM_WB               = ((0x0u << OS_MPU_RASR_TEX_POS) | OS_MPU_RASR_C_MSK | OS_MPU_RASR_B_MSK), /**< Normal,           Not shareable, Outer and inner write-back. No write allocate. */
  OS_MPU_ATTR_NORM_SHR_MEM_WB           = ((0x0u << OS_MPU_RASR_TEX_POS) | OS_MPU_RASR_C_MSK | OS_MPU_RASR_B_MSK | OS_MPU_RASR_S_MSK), /**< Normal,           shareable,     Outer and inner write-back. No write allocate. */

  OS_MPU_ATTR_NORM_MEM_NC               = ((0x1u << OS_MPU_RASR_TEX_POS)), /**< Normal,           Not shareable, Outer and inner non-cacheable. */
  OS_MPU_ATTR_NORM_SHR_MEM_NC           = ((0x1u << OS_MPU_RASR_TEX_POS) | OS_MPU_RASR_S_MSK), /**< Normal,           shareable,     Outer and inner non-cacheable. */
  OS_MPU_ATTR_NORM_MEM_WA               = ((0x1u << OS_MPU_RASR_TEX_POS) | OS_MPU_RASR_C_MSK | OS_MPU_RASR_B_MSK), /**< Normal,           Not shareable, Outer and inner Write-Back. Write and read allocate */
  OS_MPU_ATTR_NORM_SHR_MEM_WA           = ((0x1u << OS_MPU_RASR_TEX_POS) | OS_MPU_RASR_C_MSK | OS_MPU_RASR_B_MSK | OS_MPU_RASR_S_MSK), /**< Normal,           shareable,     Outer and inner Write-Back. Write and read allocate */

  OS_MPU_ATTR_DEV                       = ((0x2u << OS_MPU_RASR_TEX_POS)), /**< Device,           Not-shareable, */

  /* Attribute for different policy for outer and inter cache. */
  OS_MPU_ATTR_NORM_MEM_IN_NC_OUT_NC     = ((0x4u << OS_MPU_RASR_TEX_POS)), /**< Normal, Not-shareable. inner policy: Non-cachealbe,                      outer policy: Non-cacheable */
  OS_MPU_ATTR_NORM_MEM_IN_WA_OUT_NC     = ((0x4u << OS_MPU_RASR_TEX_POS) | OS_MPU_RASR_B_MSK), /**< Normal, Not-shareable. inner policy: Write back, write and read-Allocate outer policy: Non-cacheable */
  OS_MPU_ATTR_NORM_MEM_IN_WT_OUT_NC     = ((0x4u << OS_MPU_RASR_TEX_POS) | OS_MPU_RASR_C_MSK), /**< Normal, Not-shareable. inner policy: Write through, no Write-Allocate,   outer policy: Non-cacheable */
  OS_MPU_ATTR_NORM_MEM_IN_WB_OUT_NC     = ((0x4u << OS_MPU_RASR_TEX_POS) | OS_MPU_RASR_C_MSK | OS_MPU_RASR_B_MSK), /**< Normal, Not-shareable. inner policy: Write back, no Write-Allocate,      outer policy: Non-cacheable */
  OS_MPU_ATTR_NORM_SHR_MEM_IN_NC_OUT_NC = ((0x4u << OS_MPU_RASR_TEX_POS) | OS_MPU_RASR_S_MSK), /**< Normal, shareable.     inner policy: Non-cachealbe,                      outer policy: Non-cacheable */
  OS_MPU_ATTR_NORM_SHR_MEM_IN_WA_OUT_NC = ((0x4u << OS_MPU_RASR_TEX_POS) | OS_MPU_RASR_B_MSK | OS_MPU_RASR_S_MSK), /**< Normal, shareable.     inner policy: Write back, write and read-Allocate outer policy: Non-cacheable */
  OS_MPU_ATTR_NORM_SHR_MEM_IN_WT_OUT_NC = ((0x4u << OS_MPU_RASR_TEX_POS) | OS_MPU_RASR_C_MSK | OS_MPU_RASR_S_MSK), /**< Normal, shareable.     inner policy: Write through, no Write-Allocate,   outer policy: Non-cacheable */
  OS_MPU_ATTR_NORM_SHR_MEM_IN_WB_OUT_NC = ((0x4u << OS_MPU_RASR_TEX_POS) | OS_MPU_RASR_C_MSK | OS_MPU_RASR_B_MSK | OS_MPU_RASR_S_MSK), /**< Normal, shareable.     inner policy: Write back, no Write-Allocate,      outer policy: Non-cacheable */
  OS_MPU_ATTR_NORM_MEM_IN_NC_OUT_WA     = ((0x5u << OS_MPU_RASR_TEX_POS)), /**< Normal, Not-shareable. inner policy: Non-cachealbe,                      outer policy: Write back, write and read-Allocate */
  OS_MPU_ATTR_NORM_MEM_IN_WA_OUT_WA     = ((0x5u << OS_MPU_RASR_TEX_POS) | OS_MPU_RASR_B_MSK), /**< Normal, Not-shareable. inner policy: Write back, write and read-Allocate outer policy: Write back, write and read-Allocate */
  OS_MPU_ATTR_NORM_MEM_IN_WT_OUT_WA     = ((0x5u << OS_MPU_RASR_TEX_POS) | OS_MPU_RASR_C_MSK), /**< Normal, Not-shareable. inner policy: Write through, no Write-Allocate,   outer policy: Write back, write and read-Allocate */
  OS_MPU_ATTR_NORM_MEM_IN_WB_OUT_WA     = ((0x5u << OS_MPU_RASR_TEX_POS) | OS_MPU_RASR_C_MSK | OS_MPU_RASR_B_MSK                 ), /**< Normal, Not-shareable. inner policy: Write back, no Write-Allocate,      outer policy: Write back, write and read-Allocate */
  OS_MPU_ATTR_NORM_SHR_MEM_IN_NC_OUT_WA = ((0x5u << OS_MPU_RASR_TEX_POS) | OS_MPU_RASR_S_MSK), /**< Normal, shareable.     inner policy: Non-cachealbe,                      outer policy: Write back, write and read-Allocate */
  OS_MPU_ATTR_NORM_SHR_MEM_IN_WA_OUT_WA = ((0x5u << OS_MPU_RASR_TEX_POS) | OS_MPU_RASR_B_MSK | OS_MPU_RASR_S_MSK), /**< Normal, shareable.     inner policy: Write back, write and read-Allocate outer policy: Write back, write and read-Allocate */
  OS_MPU_ATTR_NORM_SHR_MEM_IN_WT_OUT_WA = ((0x5u << OS_MPU_RASR_TEX_POS) | OS_MPU_RASR_C_MSK | OS_MPU_RASR_S_MSK), /**< Normal, shareable.     inner policy: Write through, no Write-Allocate,   outer policy: Write back, write and read-Allocate */
  OS_MPU_ATTR_NORM_SHR_MEM_IN_WB_OUT_WA = ((0x5u << OS_MPU_RASR_TEX_POS) | OS_MPU_RASR_C_MSK | OS_MPU_RASR_B_MSK | OS_MPU_RASR_S_MSK), /**< Normal, shareable.     inner policy: Write back, no Write-Allocate,      outer policy: Write back, write and read-Allocate */
  OS_MPU_ATTR_NORM_MEM_IN_NC_OUT_WT     = ((0x6u << OS_MPU_RASR_TEX_POS)), /**< Normal, Not-shareable. inner policy: Non-cachealbe,                      outer policy: Write through, no Write-Allocate */
  OS_MPU_ATTR_NORM_MEM_IN_WA_OUT_WT     = ((0x6u << OS_MPU_RASR_TEX_POS) | OS_MPU_RASR_B_MSK), /**< Normal, Not-shareable. inner policy: Write back, write and read-Allocate outer policy: Write through, no Write-Allocate */
  OS_MPU_ATTR_NORM_MEM_IN_WT_OUT_WT     = ((0x6u << OS_MPU_RASR_TEX_POS) | OS_MPU_RASR_C_MSK), /**< Normal, Not-shareable. inner policy: Write through, no Write-Allocate,   outer policy: Write through, no Write-Allocate */
  OS_MPU_ATTR_NORM_MEM_IN_WB_OUT_WT     = ((0x6u << OS_MPU_RASR_TEX_POS) | OS_MPU_RASR_C_MSK | OS_MPU_RASR_B_MSK), /**< Normal, Not-shareable. inner policy: Write back, no Write-Allocate,      outer policy: Write through, no Write-Allocate */
  OS_MPU_ATTR_NORM_SHR_MEM_IN_NC_OUT_WT = ((0x6u << OS_MPU_RASR_TEX_POS) | OS_MPU_RASR_S_MSK), /**< Normal, shareable.     inner policy: Non-cachealbe,                      outer policy: Write through, no Write-Allocate */
  OS_MPU_ATTR_NORM_SHR_MEM_IN_WA_OUT_WT = ((0x6u << OS_MPU_RASR_TEX_POS) | OS_MPU_RASR_B_MSK | OS_MPU_RASR_S_MSK), /**< Normal, shareable.     inner policy: Write back, write and read-Allocate outer policy: Write through, no Write-Allocate */
  OS_MPU_ATTR_NORM_SHR_MEM_IN_WT_OUT_WT = ((0x6u << OS_MPU_RASR_TEX_POS) | OS_MPU_RASR_C_MSK | OS_MPU_RASR_S_MSK), /**< Normal, shareable.     inner policy: Write through, no Write-Allocate,   outer policy: Write through, no Write-Allocate */
  OS_MPU_ATTR_NORM_SHR_MEM_IN_WB_OUT_WT = ((0x6u << OS_MPU_RASR_TEX_POS) | OS_MPU_RASR_C_MSK | OS_MPU_RASR_B_MSK | OS_MPU_RASR_S_MSK), /**< Normal, shareable.     inner policy: Write back, no Write-Allocate,      outer policy: Write through, no Write-Allocate */
  OS_MPU_ATTR_NORM_MEM_IN_NC_OUT_WB     = ((0x7u << OS_MPU_RASR_TEX_POS)), /**< Normal, Not-shareable. inner policy: Non-cachealbe,                      outer policy: Write back, no Write-Allocate */
  OS_MPU_ATTR_NORM_MEM_IN_WA_OUT_WB     = ((0x7u << OS_MPU_RASR_TEX_POS) | OS_MPU_RASR_B_MSK), /**< Normal, Not-shareable. inner policy: Write back, write and read-Allocate outer policy: Write back, no Write-Allocate */
  OS_MPU_ATTR_NORM_MEM_IN_WT_OUT_WB     = ((0x7u << OS_MPU_RASR_TEX_POS) | OS_MPU_RASR_C_MSK), /**< Normal, Not-shareable. inner policy: Write through, no Write-Allocate,   outer policy: Write back, no Write-Allocate */
  OS_MPU_ATTR_NORM_MEM_IN_WB_OUT_WB     = ((0x7u << OS_MPU_RASR_TEX_POS) | OS_MPU_RASR_C_MSK | OS_MPU_RASR_B_MSK), /**< Normal, Not-shareable. inner policy: Write back, no Write-Allocate,      outer policy: Write back, no Write-Allocate */
  OS_MPU_ATTR_NORM_SHR_MEM_IN_NC_OUT_WB = ((0x7u << OS_MPU_RASR_TEX_POS) | OS_MPU_RASR_S_MSK), /**< Normal, shareable.     inner policy: Non-cachealbe,                      outer policy: Write back, no Write-Allocate */
  OS_MPU_ATTR_NORM_SHR_MEM_IN_WA_OUT_WB = ((0x7u << OS_MPU_RASR_TEX_POS) | OS_MPU_RASR_B_MSK | OS_MPU_RASR_S_MSK), /**< Normal, shareable.     inner policy: Write back, write and read-Allocate outer policy: Write back, no Write-Allocate */
  OS_MPU_ATTR_NORM_SHR_MEM_IN_WT_OUT_WB = ((0x7u << OS_MPU_RASR_TEX_POS) | OS_MPU_RASR_C_MSK | OS_MPU_RASR_S_MSK), /**< Normal, shareable.     inner policy: Write through, no Write-Allocate,   outer policy: Write back, no Write-Allocate */
  OS_MPU_ATTR_NORM_SHR_MEM_IN_WB_OUT_WB = ((0x7u << OS_MPU_RASR_TEX_POS) | OS_MPU_RASR_C_MSK | OS_MPU_RASR_B_MSK | OS_MPU_RASR_S_MSK), /**< Normal, shareable.     inner policy: Write back, no Write-Allocate,      outer policy: Write back, no Write-Allocate */
} os_en_mpu_attr_t;

/** Specifies enable/disable of instruction access of the MPU region */
typedef enum
{
  OS_MPU_INST_ACCESS_EN  = (0u),                /**< Instruction fetches enabled  */
  OS_MPU_INST_ACCESS_DIS = (OS_MPU_RASR_XN_MSK), /**< Instruction fetches disabled */
} os_en_mpu_execute_n_t;

/** Specifies enable/disable of the MPU region */
typedef enum
{
  OS_MPU_DISABLE = (0u),                    /**< Disable  */
  OS_MPU_ENABLE  = (OS_MPU_RASR_ENABLE_MSK), /**< Enable  */
} os_en_mpu_region_en_t;

typedef struct
{
  volatile const uint32 ulType;             /*!< Offset: 0x000 (R/ )  MPU Type Register */
  volatile uint32 ulCtrl;                   /*!< Offset: 0x004 (R/W)  MPU Control Register */
  volatile uint32 ulRnr;                    /*!< Offset: 0x008 (R/W)  MPU Region RNRber Register */
  volatile uint32 ulRbar;                   /*!< Offset: 0x00C (R/W)  MPU Region Base Address Register */
  volatile uint32 ulRasr;                   /*!< Offset: 0x010 (R/W)  MPU Region Attribute and Size Register */
  volatile uint32 ulRbar_a1;                /*!< Offset: 0x014 (R/W)  MPU Alias 1 Region Base Address Register */
  volatile uint32 ulRasr_a1;                /*!< Offset: 0x018 (R/W)  MPU Alias 1 Region Attribute and Size Register */
  volatile uint32 ulRbar_a2;                /*!< Offset: 0x01C (R/W)  MPU Alias 2 Region Base Address Register */
  volatile uint32 ulRasr_a2;                /*!< Offset: 0x020 (R/W)  MPU Alias 2 Region Attribute and Size Register */
  volatile uint32 ulRbar_a3;                /*!< Offset: 0x024 (R/W)  MPU Alias 3 Region Base Address Register */
  volatile uint32 ulRasr_a3;                /*!< Offset: 0x028 (R/W)  MPU Alias 3 Region Attribute and Size Register */
} OS_MPU_Type;

#define OS_MPU_BASE          (0xE000ED90u)                    /*!< Memory Protection Unit */
#define OS_MPU               (*(volatile OS_MPU_Type* ) OS_MPU_BASE)     /*!< Memory Protection Unit */

#endif /* OS_ARCH_REGS_H_ */

/*******************************************************************************
**              PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace:end<ISO-17961:intptrconv:Not a defect:Justify with annotations> To access Registers */
/* polyspace-end MISRA-C3:11.4 */
/* polyspace:end<MISRA-C3:2.5:Not a defect:Justify with annotations> Macro is used for memory mapping */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
