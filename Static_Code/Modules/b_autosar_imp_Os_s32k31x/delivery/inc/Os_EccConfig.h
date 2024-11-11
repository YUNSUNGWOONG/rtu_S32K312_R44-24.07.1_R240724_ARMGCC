/*******************************************************************************
**                                                                            **
**  (C) 2023 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  This source code is permitted to be used only in projects contracted      **
**  with Hyundai Autoever, and any other use is prohibited.                   **
**  If you use it for other purposes or change the source code,               **
**  you may take legal responsibility.                                        **
**  In this case, There is no warranty and technical support.                 **
**                                                                            **
**  SRC-MODULE: Os_EccConfig.h                                                **
**                                                                            **
**  TARGET    : s32k31x                                                       **
**                                                                            **
**  PRODUCT   : AUTOSAR Platform Integration Code                             **
**                                                                            **
**  PURPOSE   : Provision of register, function and global variable           **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: yes                                          **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: No                                        **
**                                                                            **
*******************************************************************************/
/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date           By            Description                         **
********************************************************************************
** 1.1.0      7-Apr-2023    HG.Kim        Redmine # 39577                     **
*******************************************************************************/
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Os_PortTypes.h"

/* ============================================================================
   =============================== Module: ERM ================================
   ============================================================================
*/
/* ERM - Register Layout Typedef */
typedef struct {
  Os_Reg32 CR0;                                /**< Configuration, offset: 0x0 */
  Os_Reg32 CR1;                                /**< Configuration, offset: 0x4 */
  Os_Reg32 CR2;                                /**< Configuration, offset: 0x8 */
  Os_Reg32 SR0;                                /**< Status, offset: 0x10 */
  Os_Reg32 SR1;                                /**< Status, offset: 0x14 */
  Os_Reg32 SR2;                                /**< Status, offset: 0x18 */
  /* Memory 0*/
  Os_Reg32 EAR0;                                /**< Error Address, offset: 0x100 */
  Os_Reg32 SYN0;                                /**< Syndrome, offset: 0x104 */
  Os_Reg32 CORR_ERR_CNT0;                       /**< Correctable Error Count, offset: 0x108 */
  /* Memory 1*/
  Os_Reg32 EAR1;                                /**< Error Address, offset: 0x110 */
  Os_Reg32 SYN1;                                /**< Syndrome, offset: 0x114 */
  Os_Reg32 CORR_ERR_CNT1;                       /**< Correctable Error Count, offset: 0x118 */
  /* Memory 2*/
  Os_Reg32 CORR_ERR_CNT2;                       /**< Correctable Error Count, offset: 0x128 */
  /* Memory 3*/
  Os_Reg32 CORR_ERR_CNT3;                       /**< Correctable Error Count, offset: 0x138 */
  /* Memory 4*/
  Os_Reg32 CORR_ERR_CNT4;                       /**< Correctable Error Count, offset: 0x148 */
  /* Memory 5*/
  Os_Reg32 CORR_ERR_CNT5;                       /**< Correctable Error Count, offset: 0x158 */
  /* Memory 6*/
  Os_Reg32 CORR_ERR_CNT6;                       /**< Correctable Error Count, offset: 0x168 */
  /* Memory 7*/
  Os_Reg32 CORR_ERR_CNT7;                       /**< Correctable Error Count, offset: 0x178 */
  /* Memory 8*/
  Os_Reg32 CORR_ERR_CNT8;                       /**< Correctable Error Count, offset: 0x188 */
  /* Memory 9*/
  Os_Reg32 CORR_ERR_CNT9;                       /**< Correctable Error Count, offset: 0x198 */
  /* Memory 10*/
  Os_Reg32 EAR10;                                /**< Error Address, offset: 0x1A0h */
  Os_Reg32 SYN10;                                /**< Syndrome, offset: 0x1A4h */
  Os_Reg32 CORR_ERR_CNT10;                       /**< Correctable Error Count, offset: 0x1A8h */
  /* Memory 11*/
  Os_Reg32 EAR11;                                /**< Error Address, offset: 0x1B0h */
  Os_Reg32 SYN11;                                /**< Syndrome, offset: 0x1B4h */
  Os_Reg32 CORR_ERR_CNT11;                       /**< Correctable Error Count, offset: 0x1B8h */
  /* Memory 12*/
  Os_Reg32 EAR12;                                /**< Error Address, offset: 0x1C0h */
  Os_Reg32 SYN12;                                /**< Syndrome, offset: 0x1C4h */
  Os_Reg32 CORR_ERR_CNT12;                       /**< Correctable Error Count, offset: 0x1C8h */
  /* Memory 13*/
  Os_Reg32 EAR13;                                /**< Error Address, offset: 0x1D0h */
  Os_Reg32 SYN13;                                /**< Syndrome, offset: 0x1D4h */
  Os_Reg32 CORR_ERR_CNT13;                       /**< Correctable Error Count, offset: 0x1D8h */
  /* Memory 14*/
  Os_Reg32 EAR14;                                /**< Error Address, offset: 0x1E0h */
  Os_Reg32 SYN14;                                /**< Syndrome, offset: 0x1E4h */
  Os_Reg32 CORR_ERR_CNT14;                       /**< Correctable Error Count, offset: 0x1E8h */
  /* Memory 15*/
  Os_Reg32 EAR15;                                /**< Error Address, offset: 0x1F0h */
  Os_Reg32 SYN15;                                /**< Syndrome, offset: 0x1F4h */
  Os_Reg32 CORR_ERR_CNT15;                       /**< Correctable Error Count, offset: 0x1F8h */
  /* Memory 16*/
  Os_Reg32 EAR16;                                /**< Error Address, offset: 0x200h */
  Os_Reg32 SYN16;                                /**< Syndrome, offset: 0x204h */
  Os_Reg32 CORR_ERR_CNT16;                       /**< Correctable Error Count, offset: 0x208h */
  /* Memory 17*/
  Os_Reg32 EAR17;                                /**< Error Address, offset: 0x210h */
  Os_Reg32 CORR_ERR_CNT17;                       /**< Correctable Error Count, offset: 0x218h */
  /* Memory 18*/
  Os_Reg32 EAR18;                                /**< Error Address, offset: 0x220h */
  Os_Reg32 CORR_ERR_CNT18;                       /**< Correctable Error Count, offset: 0x228h */
  /* Memory 19*/
  Os_Reg32 EAR19;                                /**< Error Address, offset: 0x230h */
  Os_Reg32 CORR_ERR_CNT19;                       /**< Correctable Error Count, offset: 0x238h */
} OS_ERM_Type;


/** ERM Configuration - Register Layout Typedef */
typedef volatile union {
  struct
  {
    Os_Reg32 reserved7    : 2; /* Reserved */
    Os_Reg32 ENCIE7       : 1; /* Enable Memory 7 Single Correction Interrupt Notification */
    Os_Reg32 ESCIE7       : 1; /* Enable Memory 7 Non-Correctable Interrupt Notification */
    
    Os_Reg32 reserved6    : 2; /* Reserved */
    Os_Reg32 ENCIE6       : 1; /* Enable Memory 6 Single Correction Interrupt Notification */
    Os_Reg32 ESCIE6       : 1; /* Enable Memory 6 Non-Correctable Interrupt Notification */

    Os_Reg32 reserved5    : 2; /* Reserved */
    Os_Reg32 ENCIE5       : 1; /* Enable Memory 5 Single Correction Interrupt Notification */
    Os_Reg32 ESCIE5       : 1; /* Enable Memory 5 Non-Correctable Interrupt Notification */

    Os_Reg32 reserved4    : 2; /* Reserved */
    Os_Reg32 ENCIE4       : 1; /* Enable Memory 4 Single Correction Interrupt Notification */
    Os_Reg32 ESCIE4       : 1; /* Enable Memory 4 Non-Correctable Interrupt Notification */

    Os_Reg32 reserved3    : 2; /* Reserved */
    Os_Reg32 ENCIE3       : 1; /* Enable Memory 3 Single Correction Interrupt Notification */
    Os_Reg32 ESCIE3       : 1; /* Enable Memory 3 Non-Correctable Interrupt Notification */

    Os_Reg32 reserved2    : 2; /* Reserved */
    Os_Reg32 ENCIE2       : 1; /* Enable Memory 2 Single Correction Interrupt Notification */
    Os_Reg32 ESCIE2       : 1; /* Enable Memory 2 Non-Correctable Interrupt Notification */

    Os_Reg32 reserved1    : 2; /* Reserved */
    Os_Reg32 ENCIE1       : 1; /* Enable Memory 1 Single Correction Interrupt Notification */
    Os_Reg32 ESCIE1       : 1; /* Enable Memory 1 Non-Correctable Interrupt Notification */

    Os_Reg32 reserved0    : 2; /* Reserved */
    Os_Reg32 ENCIE0       : 1; /* Enable Memory 0 Single Correction Interrupt Notification */
    Os_Reg32 ESCIE0       : 1; /* Enable Memory 0 Non-Correctable Interrupt Notification */

  } B;
  sint32 I;
  uint32 U;
} OS_ERM_CR_Type;

/** ERM Status - Register Layout Typedef */
typedef volatile union {
  struct
  {
    Os_Reg32 reserved7    : 2; /* Reserved */
    Os_Reg32 NCE7         : 1; /* Memory 7 Non-Correctable Error Event */
    Os_Reg32 SBC7         : 1; /* Memory 7 Single-Bit Correction Event */
    Os_Reg32 reserved6    : 2; /* Reserved */
    Os_Reg32 NCE6         : 1; /* Memory 6 Non-Correctable Error Event */
    Os_Reg32 SBC6         : 1; /* Memory 6 Single-Bit Correction Event */
    Os_Reg32 reserved5    : 2; /* Reserved */
    Os_Reg32 NCE5         : 1; /* Memory 5 Non-Correctable Error Event */
    Os_Reg32 SBC5         : 1; /* Memory 5 Single-Bit Correction Event */
    Os_Reg32 reserved4    : 2; /* Reserved */
    Os_Reg32 NCE4         : 1; /* Memory 4 Non-Correctable Error Event */
    Os_Reg32 SBC4         : 1; /* Memory 4 Single-Bit Correction Event */
    Os_Reg32 reserved3    : 2; /* Reserved */
    Os_Reg32 NCE3         : 1; /* Memory 3 Non-Correctable Error Event */
    Os_Reg32 SBC3         : 1; /* Memory 3 Single-Bit Correction Event */
    Os_Reg32 reserved2    : 2; /* Reserved */
    Os_Reg32 NCE2         : 1; /* Memory 2 Non-Correctable Error Event */
    Os_Reg32 SBC2         : 1; /* Memory 2 Single-Bit Correction Event */
    Os_Reg32 reserved1    : 2; /* Reserved */
    Os_Reg32 NCE1         : 1; /* Memory 1 Non-Correctable Error Event */
    Os_Reg32 SBC1         : 1; /* Memory 1 Single-Bit Correction Event */
    Os_Reg32 reserved0    : 2; /* Reserved */
    Os_Reg32 NCE0         : 1; /* Memory 0 Non-Correctable Error Event */
    Os_Reg32 SBC0         : 1; /* Memory 0 Single-Bit Correction Event */
  } B;
  sint32 I;
  uint32 U;
} OS_ERM_SR_Type;

/* ERM Memory n Error Address Register */
typedef volatile union {    
  struct {
    Os_Reg32 EAR:32;                  /* EAR */
  } B;
  uint32 U;
} OS_ERM_EAR_Type;

/** ERM Status - Register Layout Typedef */
typedef volatile union {
  struct
  {
    Os_Reg32 reserved1    : 32; /* Reserved */
  } B;
  sint32 I;
  uint32 U;
} OS_ISR_Type;


/* ============================================================================
   =============================== Module: FCCU ===============================
   ============================================================================
*/
typedef struct{
  Os_Reg32 CTRL;               /* Control */
  Os_Reg32 CTRLK;              /* Control Key */
  Os_Reg32 CFG;                /* Configuration */
  Os_Reg32 NCF_CFG0;           /* Non-critical Fault Configuration */
  Os_Reg32 NCFS_CFG0;          /* Non-critical Fault-State Configuration */
  Os_Reg32 NCF_S0;             /* Non-critical Fault Status */
  Os_Reg32 NCFK;               /* Non-critical Fault Key */
  Os_Reg32 NCF_E0;             /* Non-critical Fault Enable */
  Os_Reg32 NCF_TOE0;           /* Non-critical-Fault Alarm-State Timeout Enable */
  Os_Reg32 NCF_TO;             /* Non-critical-Fault Alarm-State Timeout Interval */
  Os_Reg32 CFG_TO;             /* Configuration-State Timeout Interval */
  Os_Reg32 EINOUT;             /* IO Control */
  Os_Reg32 STAT;               /* Status */
  Os_Reg32 N2AF_STATUS;        /* Normal-to-Alarm Freeze Status */
  Os_Reg32 A2FF_STATUS;        /* Alarm-to-Fault Freeze Status */
  Os_Reg32 N2FF_STATUS;        /* Normal-to-Fault Freeze Status */
  Os_Reg32 F2AF_STATUS;        /* Fault-to-Alarm Freeze Status */
  Os_Reg32 NCFF;               /* Non-critical Fault Fake */
  Os_Reg32 IRQ_STAT;           /* IRQ Status */
  Os_Reg32 IRQ_EN;             /* IRQ Enable */
  Os_Reg32 TRANS_LOCK;         /* Transient Configuration Lock */
  Os_Reg32 PERMNT_LOCK;        /* Permanent Configuration Lock */
  Os_Reg32 DELTA_T;            /* Delta T */
  Os_Reg32 IRQ_ALARM_EN0;      /* Non-critical Alarm-State Interrupt-Request Enable */
  Os_Reg32 NMI_EN0;            /* Non-critical Fault-State Non-maskable-Interrupt-Request Enable */
  Os_Reg32 EOUT_SIG_EN0;       /* Non-critical Fault-State EOUT Signaling Enable */
  Os_Reg32 TMR_ALARM;          /* Alarm-State Timer */
  Os_Reg32 TMR_CFG;            /* Configuration-State Timer */
  Os_Reg32 TMR_ETMR;           /* Fault-Output Timer */
} OS_FCCU_Type;

/* Locked-Operation Control Key */
typedef volatile union { 
  struct {
    Os_Reg32 CTRLK        : 32;           
  } B;
  uint32 U;
} OS_FCCU_CTRLK_Type;

/* Transient Configuration Lock */
typedef volatile union {   
  struct {
    Os_Reg32 CTRLK        : 9;              
    Os_Reg32 reserved     : 23;
  } B;
  uint32 U;
} OS_FCCU_TRANS_LOCK_Type;

/* Non-critical Fault Configuration */
typedef volatile union {   
  struct {
    Os_Reg32 NCFC0        : 1;              /* Non-critical Fault Configuration n */
    Os_Reg32 NCFC1        : 1;              /* Non-critical Fault Configuration n */
    Os_Reg32 NCFC2        : 1;              /* Non-critical Fault Configuration n */
    Os_Reg32 NCFC3        : 1;              /* Non-critical Fault Configuration n */
    Os_Reg32 NCFC4        : 1;              /* Non-critical Fault Configuration n */
    Os_Reg32 NCFC5        : 1;              /* Non-critical Fault Configuration n */
    Os_Reg32 NCFC6        : 1;              /* Non-critical Fault Configuration n */
    Os_Reg32 NCFC7        : 1;              /* Non-critical Fault Configuration n */
    Os_Reg32 reserved     : 24;             /* Reserved */
  } B;
  uint32 U;
} OS_FCCU_NCF_CFG0_Type;

/* Non-critical Fault-State Non-maskable-Interrupt-Request Enable */
typedef volatile union {   
  struct {
    Os_Reg32 NMIEN0       : 1;              /* Non-critical Fault-State Non-maskable-Interrupt-Request Enable n */
    Os_Reg32 NMIEN1       : 1;              /* Non-critical Fault-State Non-maskable-Interrupt-Request Enable n */
    Os_Reg32 NMIEN2       : 1;              /* Non-critical Fault-State Non-maskable-Interrupt-Request Enable n */
    Os_Reg32 NMIEN3       : 1;              /* Non-critical Fault-State Non-maskable-Interrupt-Request Enable n */
    Os_Reg32 NMIEN4       : 1;              /* Non-critical Fault-State Non-maskable-Interrupt-Request Enable n */
    Os_Reg32 NMIEN5       : 1;              /* Non-critical Fault-State Non-maskable-Interrupt-Request Enable n */
    Os_Reg32 NMIEN6       : 1;              /* Non-critical Fault-State Non-maskable-Interrupt-Request Enable n */
    Os_Reg32 NMIEN7       : 1;              /* Non-critical Fault-State Non-maskable-Interrupt-Request Enable n */
    Os_Reg32 reserved     : 24;
  } B;
  uint32 U;
} OS_FCCU_NMI_EN0_Type;

/* Non-critical Fault Enable */
typedef volatile union {   
  struct {
    Os_Reg32 NCFE0        : 1;              /* Non-critical Fault Enable n */
    Os_Reg32 NCFE1        : 1;              /* Non-critical Fault Enable n */
    Os_Reg32 NCFE2        : 1;              /* Non-critical Fault Enable n */
    Os_Reg32 NCFE3        : 1;              /* Non-critical Fault Enable n */
    Os_Reg32 NCFE4        : 1;              /* Non-critical Fault Enable n */
    Os_Reg32 NCFE5        : 1;              /* Non-critical Fault Enable n */
    Os_Reg32 NCFE6        : 1;              /* Non-critical Fault Enable n */
    Os_Reg32 NCFE7        : 1;              /* Non-critical Fault Enable n */
    Os_Reg32 reserved     : 24;             /* Reserved */
  } B;
  uint32 U;
} OS_FCCU_NCF_E0_Type;

/* IRQ Status */
typedef volatile union {
  struct {
	Os_Reg32 CFG_TO_STAT:1;           /* Configuration-State Timeout Status */
	Os_Reg32 ALRM_STAT:1;             /* Alarm Interrupt Status */
	Os_Reg32 NMI_STAT:1;              /* NMI Interrupt Status */
	Os_Reg32 _unused_1:1;             /* Reserved */
    Os_Reg32 _unused_2:1;             /* Reserved */
	Os_Reg32 _unused_3:27;            /* Reserved */
  } B;
  uint32 U;
} OS_FCCU_IRQ_STAT_Type;

/* IRQ Enable */
typedef volatile union {
  struct {
	Os_Reg32 CFG_TO_IEN:1;            /* Configuration-State Timeout Interrupt Enable */
    Os_Reg32 _unused_1:2;             /* Reserved */
	Os_Reg32 _unused_2:1;             /* Reserved */
	Os_Reg32 _unused_3:28;            /* Reserved */
  } B;
  uint32 U;
} OS_FCCU_IRQ_EN_Type;

/* Non-critical Fault Status */
typedef volatile union {
  struct {
	Os_Reg32 NCFS0:1;                 /* Non-critical Fault Status n */
	Os_Reg32 NCFS1:1;                 /* Non-critical Fault Status n */
	Os_Reg32 NCFS2:1;                 /* Non-critical Fault Status n */
	Os_Reg32 NCFS3:1;                 /* Non-critical Fault Status n */
	Os_Reg32 NCFS4:1;                 /* Non-critical Fault Status n */
	Os_Reg32 NCFS5:1;                 /* Non-critical Fault Status n */
	Os_Reg32 NCFS6:1;                 /* Non-critical Fault Status n */
	Os_Reg32 NCFS7:1;                 /* Non-critical Fault Status n */
	Os_Reg32 _unused_8:24;
  } B;
  uint32 U;
} OS_FCCU_NCF_S_Type;

/* Permanent Configuration Lock */
typedef volatile union {
  struct {
	Os_Reg32 PERMNTKEY:9;             /* Permanent Configuration Lock */
	Os_Reg32 _unused_9:23;            /* Reserved */
  } B;
  uint32 U;
} OS_FCCU_PERMNT_LOCK_Type;

/* Status */
typedef volatile union {
  struct {
	Os_Reg32 STATUS:3;                /* FCCU State */
	Os_Reg32 ESTAT:1;                 /* FCCU Faulty Condition */
	Os_Reg32 PHYSICERRORPIN:2;        /* EOUT Signal States */
	Os_Reg32 _unused_6:26;            /* Reserved */
  } B;
  uint32 U;
} OS_FCCU_STAT_Type;

/* Configuration-State Timeout Interval */
typedef volatile union {
  struct {
	Os_Reg32 TO:3;                    /* Configuration-State Timeout Interval */
	Os_Reg32 _unused_3:29;            /* Reserved */
  } B;
  uint32 U;
} OS_FCCU_CFG_TO_Type;

/* Non-critical Fault Key */
typedef volatile union {
  struct {
	  Os_Reg32 NCFK:32;                 /* Non-critical Fault Key */
  } B;
  uint32 U;
} OS_FCCU_NCFK_Type;

typedef volatile union { /* Non-critical-Fault Alarm-State Timeout Enable */
  struct {
    Os_Reg32 NCFTOE0:1;               /* Non-critical-Fault Alarm-State Timeout Enable n */
    Os_Reg32 NCFTOE1:1;               /* Non-critical-Fault Alarm-State Timeout Enable n */
    Os_Reg32 NCFTOE2:1;               /* Non-critical-Fault Alarm-State Timeout Enable n */
    Os_Reg32 NCFTOE3:1;               /* Non-critical-Fault Alarm-State Timeout Enable n */
    Os_Reg32 NCFTOE4:1;               /* Non-critical-Fault Alarm-State Timeout Enable n */
    Os_Reg32 NCFTOE5:1;               /* Non-critical-Fault Alarm-State Timeout Enable n */
    Os_Reg32 NCFTOE6:1;               /* Non-critical-Fault Alarm-State Timeout Enable n */
    Os_Reg32 NCFTOE7:1;               /* Non-critical-Fault Alarm-State Timeout Enable n */
    Os_Reg32 _unused_8:24;
  } B;
  uint32 U;
} OS_FCCU_NCF_TOE_Type;

/* Control */
typedef volatile union {    
  struct {
    Os_Reg32 OPR:5;                   /* Operation Run */
    Os_Reg32 _unused_5:1;             /* Reserved */
    Os_Reg32 OPS:2;                   /* Operation Status */
    Os_Reg32 _unused_8:1;             /* Reserved */
    Os_Reg32 DEBUG:1;                 /* Debug Mode Enable */
    Os_Reg32 _unused_10:19;           /* Reserved */
    Os_Reg32 _unused_29:2;            /* Reserved */
    Os_Reg32 _unused_31:1;            /* Reserved */
  } B;
  uint32 U;
} OS_FCCU_CTRL_Type;

/* ============================================================================
   ============================== Module: MC_RGM ==============================
   ============================================================================
*/

typedef volatile union {   /* Destructive Event Status Register */
  struct {
    Os_Reg32 F_POR:1;                 /* Flag for power-on reset */
    Os_Reg32 _unused_1:1;
    Os_Reg32 _unused_2:1;
    Os_Reg32 FCCU_FTR:1;              /* Flag for 'Destructive' Reset FCCU_FTR */
    Os_Reg32 STCU_URF:1;              /* Flag for 'Destructive' Reset STCU_URF */
    Os_Reg32 _unused_5:1;
    Os_Reg32 MC_RGM_FRE:1;            /* Flag for 'Destructive' Reset MC_RGM_FRE */
    Os_Reg32 _unused_7:1;
    Os_Reg32 FXOSC_FAIL:1;            /* Flag for 'Destructive' Reset FXOSC_FAIL */
    Os_Reg32 PLL_LOL:1;               /* Flag for 'Destructive' Reset PLL_LOL */
    Os_Reg32 CORE_CLK_FAIL:1;         /* Flag for 'Destructive' Reset CORE_CLK_FAIL */
    Os_Reg32 _unused_11:1;
    Os_Reg32 AIPS_PLAT_CLK_FAIL:1;    /* Flag for 'Destructive' Reset AIPS_PLAT_CLK_FAIL */
    Os_Reg32 _unused_13:1;
    Os_Reg32 HSE_CLK_FAIL:1;          /* Flag for 'Destructive' Reset HSE_CLK_FAIL */
    Os_Reg32 SYS_DIV_FAIL:1;          /* Flag for 'Destructive' Reset SYS_DIV_FAIL */
    Os_Reg32 _unused_16:1;
    Os_Reg32 HSE_TMPR_RST:1;          /* Flag for 'Destructive' Reset HSE_TMPR_RST */
    Os_Reg32 HSE_SNVS_RST:1;          /* Flag for 'Destructive' Reset HSE_SNVS_RST */
    Os_Reg32 _unused_19:1;
    Os_Reg32 _unused_20:1;
    Os_Reg32 _unused_21:1;
    Os_Reg32 _unused_22:1;
    Os_Reg32 _unused_23:1;
    Os_Reg32 _unused_24:1;
    Os_Reg32 _unused_25:1;
    Os_Reg32 _unused_26:1;
    Os_Reg32 _unused_27:1;
    Os_Reg32 _unused_28:1;
    Os_Reg32 SW_DEST:1;               /* Flag for 'Destructive' Reset SW_DEST */
    Os_Reg32 DEBUG_DEST:1;            /* Flag for 'Destructive' Reset DEBUG_DEST */
    Os_Reg32 _unused_31:1;
  } B;
  uint32 U;
} OS_MC_RGM_DES_Type;

typedef volatile union { /* Partition 1 COFB Set 0 Clock Enable Register */
  struct {
	Os_Reg32 _unused_0:1;             /* Reserved */
	Os_Reg32 _unused_1:1;             /* Reserved */
	Os_Reg32 _unused_2:1;             /* Reserved */
	Os_Reg32 REQ3:1;                  /* Clock enable */
	Os_Reg32 REQ4:1;                  /* Clock enable */
	Os_Reg32 REQ5:1;                  /* Clock enable */
	Os_Reg32 REQ6:1;                  /* Clock enable */
	Os_Reg32 REQ7:1;                  /* Clock enable */
	Os_Reg32 REQ8:1;                  /* Clock enable */
	Os_Reg32 REQ9:1;                  /* Clock enable */
	Os_Reg32 REQ10:1;                 /* Clock enable */
	Os_Reg32 REQ11:1;                 /* Clock enable */
	Os_Reg32 REQ12:1;                 /* Clock enable */
	Os_Reg32 REQ13:1;                 /* Clock enable */
	Os_Reg32 REQ14:1;                 /* Clock enable */
	Os_Reg32 REQ15:1;                 /* Clock enable */
	Os_Reg32 _unused_16:1;            /* Reserved */
	Os_Reg32 _unused_17:1;            /* Reserved */
	Os_Reg32 _unused_18:1;            /* Reserved */
	Os_Reg32 _unused_19:1;            /* Reserved */
	Os_Reg32 _unused_20:1;            /* Reserved */
	Os_Reg32 REQ21:1;                 /* Clock enable */
	Os_Reg32 REQ22:1;                 /* Clock enable */
	Os_Reg32 REQ23:1;                 /* Clock enable */
	Os_Reg32 REQ24:1;                 /* Clock enable */
	Os_Reg32 _unused_25:1;            /* Reserved */
	Os_Reg32 _unused_26:1;            /* Reserved */
	Os_Reg32 _unused_27:1;            /* Reserved */
	Os_Reg32 REQ28:1;                 /* Clock enable */
	Os_Reg32 REQ29:1;                 /* Clock enable */
	Os_Reg32 _unused_30:1;            /* Reserved */
	Os_Reg32 REQ31:1;                 /* Clock enable */
  } B;
  uint32 U;
} OS_MC_ME_PRTN1_COFB0_CLKEN_Type;

typedef volatile union{ /* Control Key Register */
  struct{
	Os_Reg32 KEY : 16;                  /* Control key */
	Os_Reg32 _unused_16 : 16;           /* Reserved */
  } B;
  uint32 U;
} OS_MC_ME_CTL_KEY_Type;

typedef volatile union{ /* Partition 1 Process Configuration Register */
  struct
  {
	Os_Reg32 PCE : 1;                   /* Partition clock enable */
	Os_Reg32 _unused_1 : 1;             /* Reserved */
	Os_Reg32 OSSE : 1;                  /* Output safe stating enable */
	Os_Reg32 _unused_3 : 1;             /* Reserved */
	Os_Reg32 _unused_4 : 1;             /* Reserved */
	Os_Reg32 _unused_5 : 1;             /* Reserved */
	Os_Reg32 _unused_6 : 1;             /* Reserved */
	Os_Reg32 _unused_7 : 25;            /* Reserved */
  } B;
  uint32 U;
} OS_MC_ME_PRTN1_PCONF_Type;

typedef volatile union{ /* Partition 1 Process Update Register */
  struct
  {
	Os_Reg32 PCUD : 1;                  /* Partition clock update */
	Os_Reg32 _unused_1 : 1;             /* Reserved */
	Os_Reg32 OSSUD : 1;                 /* Output safe stating update */
	Os_Reg32 _unused_3 : 1;             /* Reserved */
	Os_Reg32 _unused_4 : 1;             /* Reserved */
	Os_Reg32 _unused_5 : 1;             /* Reserved */
	Os_Reg32 _unused_6 : 1;             /* Reserved */
	Os_Reg32 _unused_7 : 25;            /* Reserved */
  } B;
  uint32 U;
} OS_MC_ME_PRTN1_PUPD_Type;

typedef volatile union{ /* Mode Configuration Register */
  struct
  {
  Os_Reg32 DEST_RST : 1;              /* Destructive reset request */
  Os_Reg32 FUNC_RST : 1;              /* Functional reset request */
  Os_Reg32 _unused_2 : 14;            /* Reserved */
  Os_Reg32 _unused_16 : 16;           /* Reserved */
  } B;
  uint32 U;
} OS_MC_ME_MODE_CONF_Type;

typedef volatile union{/* Mode Update Register */
  struct
  {
  Os_Reg32 MODE_UPD : 1;              /* Mode update */
  Os_Reg32 _unused_1 : 31;            /* Reserved */
  } B;
  uint32 U;
} OS_MC_ME_MODE_UPD_Type;


typedef volatile union { /* Read Write GPR On Power On Reset Register */
  struct 
  {
  Os_Reg32 _unused_0:1;             /* Reserved */
  Os_Reg32 _unused_1:2;             /* Reserved */
  Os_Reg32 CLKOUT_STANDBY:1;        /* Clockout standby expose over functional and destructive reset. */
  Os_Reg32 _unused_4:2;             /* Reserved */
  Os_Reg32 _unused_6:1;             /* Reserved */
  Os_Reg32 _unused_7:1;             /* Reserved */
  Os_Reg32 STANBDY_PWDOG_DIS:1;     /* Disables the standby entry and exit monitoring window of the POR WDOG. */
  Os_Reg32 POR_WDOG_TRIM:2;         /* Trims for POR WDG timeout value. */
  Os_Reg32 _unused_11:21;           /* Reserved */
  } B;
  uint32 U;
} OS_DCM_GPR_DCMRWP1_Type;

#define OS_ERM0_BASE                 (0x4025C000)
#define OS_ERM0_CR0                  (*(OS_ERM_CR_Type *)OS_ERM0_BASE)
#define OS_ERM0_CR1                  (*(OS_ERM_CR_Type *)(OS_ERM0_BASE + 0x04U))
#define OS_ERM0_CR2                  (*(OS_ERM_CR_Type *)(OS_ERM0_BASE + 0x08U))
#define OS_ERM0_SR0                  (*(OS_ERM_SR_Type *)(OS_ERM0_BASE + 0x10U))
#define OS_ERM0_SR1                  (*(OS_ERM_SR_Type *)(OS_ERM0_BASE + 0x14U))
#define OS_ERM0_SR2                  (*(OS_ERM_SR_Type *)(OS_ERM0_BASE + 0x18U))
#define OS_ERM0_EAR18                (*(OS_ERM_EAR_Type *)(OS_ERM0_BASE + 0x220U))


#define OS_ISR_BASE                  (0xE000E104)
#define OS_ISR                       (*(OS_ISR_Type *)OS_ISR_BASE)

#define OS_ERM0_CR0_ENCIEn_ON  0x44444444 /* ENCIE0 .. ENCIE7 */
#define OS_ERM0_CR1_ENCIEn_ON  0x44444444 /* ENCIE8 .. ENCIE15 */
#define OS_ERM0_CR2_ENCIEn_ON  0x44440000 /* ENCIE16 .. ENCIE19 */

#define OS_FCCU_BASE                 (0x40384000)
#define OS_FCCU_CTRL                 (*(OS_FCCU_CTRL_Type *)OS_FCCU_BASE)
#define OS_FCCU_CTRLK                (*(OS_FCCU_CTRLK_Type *)(OS_FCCU_BASE + 0x04U))
#define OS_FCCU_TRANS_LOCK           (*(OS_FCCU_TRANS_LOCK_Type *)(OS_FCCU_BASE + 0xF0U))
#define OS_FCCU_NCF_CFG0             (*(OS_FCCU_NCF_CFG0_Type *)(OS_FCCU_BASE + 0x1CU))
#define OS_FCCU_NMI_EN0              (*(OS_FCCU_NMI_EN0_Type *)(OS_FCCU_BASE + 0x10CU))
#define OS_FCCU_NCF_E0               (*(OS_FCCU_NCF_E0_Type *)(OS_FCCU_BASE + 0x94U))
#define OS_FCCU_IRQ_STAT             (*(OS_FCCU_IRQ_STAT_Type *)(OS_FCCU_BASE + 0xE0U))
#define OS_FCCU_IRQ_EN               (*(OS_FCCU_IRQ_EN_Type *)(OS_FCCU_BASE + 0xE4U))
#define OS_FCCU_NCF_S                (*(OS_FCCU_NCF_S_Type *)(OS_FCCU_BASE + 0x80U))
#define OS_FCCU_PERMNT_LOCK          (*(OS_FCCU_PERMNT_LOCK_Type *)(OS_FCCU_BASE + 0xF4U))
#define OS_FCCU_STAT                 (*(OS_FCCU_STAT_Type *)(OS_FCCU_BASE + 0xC0U))
#define OS_FCCU_CFG_TO               (*(OS_FCCU_CFG_TO_Type *)(OS_FCCU_BASE + 0xB8U))
#define OS_FCCU_NCFK                 (*(OS_FCCU_NCFK_Type *)(OS_FCCU_BASE + 0x90U))
#define OS_FCCU_NCF_TOE                 (*(OS_FCCU_NCF_TOE_Type *)(OS_FCCU_BASE + 0xA4U))

#define OS_MC_RGM_BASE                      (0x4028C000)
#define OS_MC_RGM_DES                       (*(OS_MC_RGM_DES_Type *)OS_MC_RGM_BASE)

#define OS_MC_ME_BASE                      (0x402DC000)
#define OS_MC_ME_CTL_KEY                   (*(OS_MC_ME_CTL_KEY_Type *)OS_MC_ME_BASE)
#define OS_MC_ME_PRTN1_COFB0_CLKEN         (*(OS_MC_ME_PRTN1_COFB0_CLKEN_Type *)(OS_MC_ME_BASE + 0x330U))
#define OS_MC_ME_PRTN1_PCONF               (*(OS_MC_ME_PRTN1_PCONF_Type *)(OS_MC_ME_BASE + 0x300U))
#define OS_MC_ME_PRTN1_PUPD                (*(OS_MC_ME_PRTN1_PUPD_Type *)(OS_MC_ME_BASE + 0x304U))
#define OS_MC_ME_MODE_CONF                 (*(OS_MC_ME_MODE_CONF_Type *)(OS_MC_ME_BASE + 0x4U))
#define OS_MC_ME_MODE_UPD                  (*(OS_MC_ME_MODE_UPD_Type *)(OS_MC_ME_BASE + 0x8U))

#define OS_DCM_GPR_BASE                    (0x402AC000)
#define OS_DCM_GPR_DCMRWP1                 (*(OS_DCM_GPR_DCMRWP1_Type *)(OS_DCM_GPR_BASE + 0x400U))

#define OS_NORMAL_STATE 0
#define OS_CONFIG_STATE 1
#define OS_ALARM_STATE  2
#define OS_FAULT_STATE  3

#define OS_INPROGRESS   1
#define OS_ABORTED      2
#define OS_SUCCESSFUL   3

#define OS_UNLOCK_OP1          0x913756AFU
#define OS_UNLOCK_OP2          0x825A132BU
#define OS_LOCK_TRANSKEY       0x00000000U
#define OS_UNLOCK_TRANSKEY     0x000000BCU
#define OS_LOCK_PERMNTKEY      0x000000FFU
#define OS_UNLOCK_NCF_S        0xAB3498FEU