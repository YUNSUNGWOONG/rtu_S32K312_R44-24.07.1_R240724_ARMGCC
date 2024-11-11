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
**  SRC-MODULE: CanTrcv_IntTypes.h                                            **
**                                                                            **
**  TARGET    : General CAN Transceiver                                       **
**                                                                            **
**  PRODUCT   : AUTOSAR CAN Transceiver Driver Module                         **
**                                                                            **
**  PURPOSE   : Provides Type Definitions used within the module              **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision       Date                By               Description            **
********************************************************************************
** 1.0.11         08-Feb-2024         Yubin Song       #CP44-3726             **
** 1.0.9          03-Mar-2023         HieuTM8          #CP44-1774             **
** 1.0.7          31-Oct-2022         HieuTM8          #CP44-1036             **
** 1.0.6          14-Oct-2022         HieuTM8          #CP44-709, #CP44-648   **
** 1.0.5          30-Jul-2022         HieuTM8          #CP44-512              **
** 1.0.2          28-Mar-2022         HieuTM8          Redmine #25608         **
** 1.0.1          14-Sep-2021         DuyNHP2          Redmine #20148         **
** 1.0.0          15-Dec-2020         JsLim            Initial version        **
*******************************************************************************/
/* @Trace: SRS_BSW_00300 */
#ifndef CANTRCV_INTTYPES_H
#define CANTRCV_INTTYPES_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* @Trace: CanTrcv_SUD_FILE_001 */
/* @Trace: CanTrcv_SUD_DATATYPE_011 CanTrcv_SUD_DATATYPE_012 */
/* Standard type header file */
#include "Std_Types.h"
/* Com stack type header file */
#include "ComStack_Types.h"
/* Can general type header file */
/* @Trace: CanTrcv_SUD_DATATYPE_013 CanTrcv_SUD_DATATYPE_014 CanTrcv_SUD_DATATYPE_015 */
#include "Can_GeneralTypes.h"
/* @Trace: CanTrcv_SUD_MACRO_002 CanTrcv_SUD_MACRO_003 */
/* Can Transceiver configuration header file */
#include "CanTrcv_Cfg.h"

/* Dio header file */
/* @Trace: CanTrcv_SUD_DATATYPE_003 CanTrcv_SUD_DATATYPE_004  CanTrcv_SUD_DATATYPE_005 CanTrcv_SUD_DATATYPE_035 CanTrcv_SUD_DATATYPE_017 */
#include "Dio.h"
/* EcuM header file */
/* @Trace: CanTrcv_SUD_DATATYPE_006 */
#if ((STD_ON == CANTRCV_HW_PN_SUPPORTED) || \
  (STD_ON == CANTRCV_WAKEUP_SUPPORTED))
#include "EcuM.h"
#endif /* ((STD_ON == CANTRCV_HW_PN_SUPPORTED) || \
  (STD_ON == CANTRCV_WAKEUP_SUPPORTED)) */
/* Icu header file */
/* @Trace: CanTrcv_SUD_DATATYPE_007 */
#if (STD_OFF == CANTRCV_SUPPORT_AR403)
#if (STD_ON == CANTRCV_ICU_CHANNEL_USED)
#include "Icu.h"
#endif /* (STD_ON == CANTRCV_ICU_CHANNEL_USED) */
/* Dem header file */
/* @Trace: CanTrcv_SUD_DATATYPE_001 CanTrcv_SUD_DATATYPE_002 */
#if (STD_ON == CANTRCV_E_BUS_ERROR_SUPPORTED)
#include "Dem.h"
#endif /* (STD_ON == CANTRCV_E_BUS_ERROR_SUPPORTED) */
#endif /*(STD_OFF == CANTRCV_SUPPORT_AR403)*/

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/*******************************************************************************
**                      MACRO Definitions                                     **
*******************************************************************************/
/* @Trace: CanTrcv_SUD_MACRO_005 */
/* Macros for numerical values */
#define CANTRCV_ZERO                               (0)
#define CANTRCV_ONE                                (1)
#define CANTRCV_TWO                                (2)
#define CANTRCV_THREE                              (3)
#define CANTRCV_FOUR                               (4)
#define CANTRCV_FIVE                               (5)
#define CANTRCV_SIX                                (6)
#define CANTRCV_SEVEN                              (7)
#define CANTRCV_EIGHT                              (8)
#define CANTRCV_SIXTEEN                            (16)
#define CANTRCV_TWENTYFOUR                         (24)

/* Macros for boolean Values */
#define CANTRCV_UNINITIALIZED                      ((boolean)0x00)
#define CANTRCV_INITIALIZED                        ((boolean)0x01)
#define CANTRCV_FALSE                              ((boolean)0x00)
#define CANTRCV_ERR                                ((boolean)0x01)
#define CANTRCV_N_ERR                              ((boolean)0x00)
#define CANTRCV_TRUE                               ((boolean)0x01)
#define CANTRCV_UNUSED                             ((uint8)0xFF)
#define CANTRCV_INVALID_PNINDEX                    ((uint8)0xFF)

/* ARISUCAN registers */
#if (STD_ON == CANTRCV_ARISUCAN_SUPPORTED)
/* ARISUCAN SBC SPI REGISTER */
#define ARISUCAN_M_S_CTRL_REG_W                    ((uint16)0x0081)
#define ARISUCAN_M_S_CTRL_REG_R                    ((uint16)0x0001)
#define ARISUCAN_HW_CTRL_0_REG_W                   ((uint16)0x0082)
#define ARISUCAN_HW_CTRL_0_REG_R                   ((uint16)0x0002)
#define ARISUCAN_WD_CTRL_REG_W                     ((uint16)0x0083)
#define ARISUCAN_WD_CTRL_REG_R                     ((uint16)0x0003)
#define ARISUCAN_BUS_CTRL_0_REG_W                  ((uint16)0x0084)
#define ARISUCAN_BUS_CTRL_0_REG_R                  ((uint16)0x0004)
#define ARISUCAN_WK_CTRL_0_REG_W                   ((uint16)0x0086)
#define ARISUCAN_WK_CTRL_0_REG_R                   ((uint16)0x0006)
#define ARISUCAN_WK_CTRL_1_REG_W                   ((uint16)0x0087)
#define ARISUCAN_WK_CTRL_1_REG_R                   ((uint16)0x0007)
#define ARISUCAN_WK_PUPD_CTRL_REG_W                ((uint16)0x0088)
#define ARISUCAN_WK_PUPD_CTRL_REG_R                ((uint16)0x0008)
#define ARISUCAN_BUS_CTRL_2_REG_W                  ((uint16)0x008A)
#define ARISUCAN_BUS_CTRL_2_REG_R                  ((uint16)0x000A)
#define ARISUCAN_BUS_CTRL_3_REG_W                  ((uint16)0x008B)
#define ARISUCAN_BUS_CTRL_3_REG_R                  ((uint16)0x000B)
#define ARISUCAN_TIMER_CTRL_0_REG_W                ((uint16)0x008C)
#define ARISUCAN_TIMER_CTRL_0_REG_R                ((uint16)0x000C)
#define ARISUCAN_SYS_STATUS_CTRL_REG_W             ((uint16)0x008D)
#define ARISUCAN_SYS_STATUS_CTRL_REG_R             ((uint16)0x000D)
#define ARISUCAN_SUP_STAT_1_REG_W                  ((uint16)0x00C0)
#define ARISUCAN_SUP_STAT_1_REG_R                  ((uint16)0x0040)
#define ARISUCAN_SUP_STAT_0_REG_W                  ((uint16)0x00C1)
#define ARISUCAN_SUP_STAT_0_REG_R                  ((uint16)0x0041)
#define ARISUCAN_THERM_STAT_REG_W                  ((uint16)0x00C2)
#define ARISUCAN_THERM_STAT_REG_R                  ((uint16)0x0042)
#define ARISUCAN_DEV_STAT_REG_W                    ((uint16)0x00C3)
#define ARISUCAN_DEV_STAT_REG_R                    ((uint16)0x0043)
#define ARISUCAN_BUS_STAT_0_REG_W                  ((uint16)0x00C4)
#define ARISUCAN_BUS_STAT_0_REG_R                  ((uint16)0x0044)
#define ARISUCAN_WK_STAT_0_REG_W                   ((uint16)0x00C6)
#define ARISUCAN_WK_STAT_0_REG_R                   ((uint16)0x0046)
#define ARISUCAN_WK_LVL_STAT_REG_W                 ((uint16)0x00C8)
#define ARISUCAN_WK_LVL_STAT_REG_R                 ((uint16)0x0048)
#define ARISUCAN_WK_STAT_2_REG_W                   ((uint16)0x00C9)
#define ARISUCAN_WK_STAT_2_REG_R                   ((uint16)0x0049)
#define ARISUCAN_BUS_STAT_2_REG_W                  ((uint16)0x00CA)
#define ARISUCAN_BUS_STAT_2_REG_R                  ((uint16)0x004A)
#define ARISUCAN_BUS_STAT_3_REG_W                  ((uint16)0x00CB)
#define ARISUCAN_BUS_STAT_3_REG_R                  ((uint16)0x004B)
#define ARISUCAN_SMPS_STAT_REG_W                   ((uint16)0x00CC)
#define ARISUCAN_SMPS_STAT_REG_R                   ((uint16)0x004C)
#define ARISUCAN_FAM_PROD_STAT_R                   ((uint16)0x007E)

#define ARISUCAN_Read_Reg_Filter                   ((uint8)0xFE)
#define ARISUCAN_DATAMASK                          ((uint16)0xFF00)
#define ARISUCAN_CAN_0_1_3_MASK                    ((uint16)0x7)
#define ARISUCAN_CAN_2_MASK                        ((uint16)0x38)

/* M_S_CTRL */
/* Registor bit
  NIDE_1      :7 - SBC Mode Control
  MODE_0      :6 - SBC Mode Control
  VEXT_ON     :5 - If PCFG is left open, VEXT Mode Control
  VIO_OV_RST  :2 - VIO Over Voltage Reset / Fail-Safe enable
  VIO_RT_1    :1 - Limit number of resets due to a Watchdog failure
  VIO_RT_0    :0 - VIO Reset Threshold Control
*/
#define ARISUCAN_M_S_CTRL_MODE_1_BIT               ((uint16)0x0001 << 15)
#define ARISUCAN_M_S_CTRL_MODE_0_BIT               ((uint16)0x0001 << 14)
#define ARISUCAN_M_S_CTRL_VEXT_ON_BIT              ((uint16)0x0001 << 13)
#define ARISUCAN_M_S_CTRL_VIO_OV_RST_BIT           ((uint16)0x0001 << 10)
#define ARISUCAN_M_S_CTRL_VIO_RT_1_BIT             ((uint16)0x0001 << 9)
#define ARISUCAN_M_S_CTRL_VIO_RT_0_BIT             ((uint16)0x0001 << 8)
#define ARISUCAN_SUP_STAT_1_VS_UV_NOT_OK_BIT       ((uint16)0x0001 << 6)
#define ARISUCAN_W_K_LVL_STAT_UV_STATE_NOT_OK_BIT  ((uint16)0x0001 << 3)
#define ARISUCAN_W_K_STAT_2_UV_LATCH_NOT_OK_BIT    ((uint16)0x0001 << 7)

#define ARISUCAN_H_W_CTRL_0_PWM_AUTO_1_BIT         ((uint16)0x0001 << 3)
#define ARISUCAN_H_W_CTRL_0_PWM_AUTO_0_BIT         ((uint16)0x00F7)
#define ARISUCAN_W_K_CTRL_0_VBSENSE01_CFG_BIT      ((uint16)0x0001 << 4)
#define ARISUCAN_W_K_CTRL_0_VBSENSE01_CFG_CHECK_BIT ((uint16)0x0003 << 4)
#define ARISUCAN_W_K_CTRL_0_VBSENSE_EN_BIT         ((uint16)0x0001)
#define ARISUCAN_W_K_CTRL_0_VBSENSE_DISABLE_BIT    ((uint16)0xFFFE)

#define ARISUCAN_M_S_CTRL_MODE_POS                 ((uint8)14)
#define ARISUCAN_BUS_CTRL_MODE_POS                 ((uint8)8)
#define ARISUCAN_BUS_CTRL_CANTRCV_3_MODE_POS       ((uint8)3)
#define ARISUCAN_M_S_CTRL_MODE_MASK                ((uint16)0x00C0)
#define ARISUCAN_VBSENSE_CFG_MASK                  ((uint8)4)
#define ARISUCAN_VBAT_UV_STATE_MASK                ((uint8)3)
#define ARISUCAN_VS_UV_MASK                        ((uint8)6)
#define ARISUCAN_WK_STAT_MASK                      ((uint8)7)
#define ARISUCAN_M_S_CTRL_MASK                     ((uint8)6)

/* ARISU_CAN_DEFINE */
#define ARISUCAN_OK                                ((uint8) 0x00)
#define ARISUCAN_BUSY                              ((uint8) 0x01)
#define ARISUCAN_FIVE                              ((uint8) 0x05)
#define ARISUCAN_EIGHT                             ((uint8) 0x08)
#define ARISU_SPI_MAX_COUNT                        ((uint8) 5)
#define ARISU_8_BIT                                ((uint16) 0x00FF)

#endif /* (STD_ON == CANTRCV_ARISUCAN_SUPPORTED) */

/* XJA11XX registers */
#if (STD_ON == CANTRCV_XJA11XX_SUPPORTED)

/* Access the register type */
#define XJA11XX_REG_WRITE                          ((uint8)0x00)
#define XJA11XX_REG_READ                           ((uint8)0x01)

/* Mode control register */
#define XJA11XX_MODE_CONTROL_REG                   ((uint8)0x01)
/* Bit CM - bit [0:2] */
#define XJA11XX_MC_MASK           ((uint8)0x07)

/* Main status register  */
#define XJA11XX_MAIN_STATUS_REG                    ((uint8)0x01)
/* Bit FSMS - bit 7 */
#define XJA11XX_FSMS_MASK         ((uint8)0x80)
#define XJA11XX_FSMS_UNDERVOLTAGE ((uint8)0x80)

/* System event capture enable register */
#define XJA11XX_SYSTEM_EVENT_CAPTURE_REG           ((uint8)0x04)
/* Default value of System event capture enable register */
#define XJA11XX_SYSTEM_EVENT_CAPTURE_DEFAULT_VALUE ((uint8)0x00)
/* Bit OTWE - bit 2 */
#define XJA11XX_OTWE_ENABLE       ((uint8)0x04)
/* Bit SPIFE - bit 1 */
#define XJA11XX_SPIFE_ENABLE      ((uint8)0x02)

/* General-purpose memory 0 */
#define XJA11XX_MEMORY_0_REG                       ((uint8)0x06)

/* General-purpose memory 1 */
#define XJA11XX_MEMORY_1_REG                       ((uint8)0x07)

/* General-purpose memory 2 */
#define XJA11XX_MEMORY_2_REG                       ((uint8)0x08)

/* General-purpose memory 3 */
#define XJA11XX_MEMORY_3_REG                       ((uint8)0x09)

/* Lock control register */
#define XJA11XX_LOCK_CONTROL_REG                   ((uint8)0x0A)
#define XJA11XX_LK6C_SHIFT        (6)
#define XJA11XX_LK5C_SHIFT        (5)
#define XJA11XX_LK4C_SHIFT        (4)
#define XJA11XX_LK3C_SHIFT        (3)
#define XJA11XX_LK2C_SHIFT        (2)
#define XJA11XX_LK1C_SHIFT        (1)
#define XJA11XX_LOCK_CONTROL_ENABLE   ((uint8)0x00)
#define XJA11XX_LOCK_CONTROL_DISABLE  ((uint8)0x01)

/* CAN control register */
#define XJA11XX_CAN_CONTROL_REG                     ((uint8)0x20)
/* Default value of CAN control register */
#define XJA11XX_CAN_CONTROL_REG_DEFAULT_VALUE ((uint8)0x00)
/* Bit PNCOK - bit 5 */
#define XJA11XX_PNCOK_SUCCESSFUL  ((uint8)0x20)
/* Bit CPNC - bit 4 */
#define XJA11XX_CPNC_MASK         ((uint8)0x10)
#define XJA11XX_CPNC_SHIFT        (4)
/* Bit CMC - bit [0:1] */
#define XJA11XX_CMC_CLEAR         ((uint8)0xFC)

/* Transceiver status register */
#define XJA11XX_TRCV_STATUS_REG                     ((uint8)0x22)
/* Bit CPNERR - bit 6 */
#define XJA11XX_CPNERR_MASK       ((uint8)0x40)
/* Bit CPNS - bit 5 */
#define XJA11XX_CPNS_MASK         ((uint8)0x20)
/* Bit CBSS - bit 3 */
#define XJA11XX_CBSS_MASK         ((uint8)0x08)
/* Bit CFS - bit 0 */
#define XJA11XX_CFS_MASK          ((uint8)0x01)

/* Transceiver event capture enable register */
#define XJA11XX_TRCV_EVENT_CAPTURE_ENABLE_REG       ((uint8)0x23)
/* Default value of Transceiver event capture enable register */
#define XJA11XX_TRCV_EVENT_CAPTURE_ENABLE_DEFAULT_VALUE ((uint8)0x00)
/* Bit CBSE - bit 4 */
#define XJA11XX_CBSE_ENABLE       ((uint8)0x10)
/* Bit CFE - bit 1 */
#define XJA11XX_CFE_ENABLE        ((uint8)0x02)
/* Bit CWE- bit 0 */
#define XJA11XX_CWE_ENABLE        ((uint8)0x01)

/* Data rate register */
#define XJA11XX_DATA_RATE_REG                       ((uint8)0x26)
/* Default value of Data rate register */
#define XJA11XX_DATA_RATE_DEFAULT_VALUE ((uint8)0x05)

/* Default value of ID registers X */
#define XJA11XX_ID_X_DEFAULT_VALUE ((uint8)0x00)

/* ID registers 0 */
#define XJA11XX_ID_0_REG                            ((uint8)0x27)
/* Bit ID7:ID0 - bit [0:7] */
#define XJA11XX_ID7_ID0_MASK      ((uint32)0x000000FF)

/* ID registers 1 */
#define XJA11XX_ID_1_REG                            ((uint8)0x28)
/* Bit ID15:ID8 - bit [0:7] */
#define XJA11XX_ID15_ID8_MASK     ((uint32)0x0000FF00)

/* ID registers 2 */
#define XJA11XX_ID_2_REG                            ((uint8)0x29)
/* Bit ID23:ID16 - bit [0:7] */
#define XJA11XX_ID23_ID16_MASK    ((uint32)0x00FF0000)
/* Bit ID5:ID0 - bit [2:7] */
#define XJA11XX_ID5_ID0_MASK      ((uint32)0x0000003F)
#define XJA11XX_ID5_ID0_SHIFT     (2)

/* ID registers 3 */
#define XJA11XX_ID_3_REG                            ((uint8)0x2A)
/* Bit ID28:ID24 - bit [0:4] */
#define XJA11XX_ID28_ID24_MASK    ((uint32)0x1F000000)
/* Bit ID10:ID6 - bit [0:4] */
#define XJA11XX_ID10_ID6_MASK     ((uint32)0x000007C0)

/* Default value of ID Mask registers X */
#define XJA11XX_ID_MASK_X_DEFAULT_VALUE ((uint8)0x00)

/* ID Mask registers 0 */
#define XJA11XX_ID_MASK_0_REG                       ((uint8)0x2B)

/* Bit M7:M0 - bit [0:7] */
#define XJA11XX_M7_M0_MASK        ((uint32)0x000000FF)

/* ID Mask registers 1 */
#define XJA11XX_ID_MASK_1_REG                       ((uint8)0x2C)
/* Bit M15:M8 - bit [0:7] */
#define XJA11XX_M15_M8_MASK       ((uint32)0x0000FF00)

/* ID Mask registers 2 */
#define XJA11XX_ID_MASK_2_REG                       ((uint8)0x2D)
/* Bit M23:M16 - bit [0:7] */
#define XJA11XX_M23_M16_MASK      ((uint32)0x00FF0000)
/* Bit M5:M0 - bit [2:7] */
#define XJA11XX_M5_M0_MASK        ((uint32)0x0000003F)
#define XJA11XX_M5_M0_SHIFT       (2)

/* ID Mask registers 3 */
#define XJA11XX_ID_MASK_3_REG                       ((uint8)0x2E)
/* Bit M28:M24 - bit [0:4] */
#define XJA11XX_M28_M24_MASK      ((uint32)0x1F000000)
/* Bit M10:M6 - bit [0:4] */
#define XJA11XX_M10_M6_MASK       ((uint32)0x000007C0)

/* Frame control register */
#define XJA11XX_FRAME_CONTROL_REG                    ((uint8)0x2F)
/* Default value of Frame control register */
#define XJA11XX_FRAME_CONTROL_DEFAULT_VALUE ((uint8)0x40)
/* Bit IDE - bit 7 */
#define XJA11XX_IDE_MASK          ((uint8)0x80)
#define XJA11XX_IDE_SHIFT         (7)
/* Bit PNDM - bit 6 */
#define XJA11XX_PNDM_EVALUATED_ENABLE     (0x40)
#define XJA11XX_PNDM_EVALUATED_DISABLE    (0x00)
/* Bit DLC - bit [0:3] */
#define XJA11XX_DLC_MASK          ((uint8)0x0F)

/* WAKE pin event capture enable register */
#define XJA11XX_WAKE_PIN_EVENT_CAPTURE_REG           ((uint8)0x4C)
/* Default value of WAKE pin event capture enable register */
#define XJA11XX_WAKE_PIN_EVENT_CAPTURE_DEFAULT_VALUE ((uint8)0x00)
/* Bit WPRE - bit 1 */
#define XJA11XX_WPRE_DISABLE       ((uint8)0x00)
#define XJA11XX_WPRE_ENABLE        ((uint8)0x02)
/* Bit WPFE - bit 0 */
#define XJA11XX_WPFE_DISABLE       ((uint8)0x00)
#define XJA11XX_WPFE_ENABLE        ((uint8)0x01)

/* Global event status register */
#define XJA11XX_GLOBAL_EVENT_STATUS_REG              ((uint8)0x60)
/* Bit WPE - bit 3 */
#define XJA11XX_WPE_MASK           ((uint8)0x08)
/* Bit TRXE - bit 2 */
#define XJA11XX_TRXE_MASK          ((uint8)0x04)
/* Bit SYSE - bit 0 */
#define XJA11XX_SYSE_MASK          ((uint8)0x01)

/* Data rate register */
#define XJA11XX_SYSTEM_EVENT_STATUS_REG              ((uint8)0x61)
/* Bit PO - bit 4 */
#define XJA11XX_PO_MASK           ((uint8)0x10)
/* Bit OTW - bit 2 */
#define XJA11XX_OTW_MASK          ((uint8)0x04)
/* Bit SPIF - bit 1 */
#define XJA11XX_SPIF_MASK         ((uint8)0x02)

/* Transceiver event status register */
#define XJA11XX_TRCV_EVENT_STATUS_REG               ((uint8)0x63)
/* Bit PNFDE - bit 5 */
#define XJA11XX_PNFDE_MASK        ((uint8)0x20)
/* Bit CBS - bit 4 */
#define XJA11XX_CBS_MASK          ((uint8)0x10)
#define XJA11XX_CBS_ACTIVE        ((uint8)0x00)
/* Bit CF - bit 1 */
#define XJA11XX_CF_MASK           ((uint8)0x02)
/* Bit CW - bit 0 */
#define XJA11XX_CW_MASK           ((uint8)0x01)
/* Bit PNFDE - bit 5, CW - bit 0 */
#define XJA11XX_PNFDE_CW_MASK     ((uint8)0x21)

/* WAKE pin event status register */
#define XJA11XX_WAKE_PIN_EVENT_STATUS_REG           ((uint8)0x64)
/* Bit WPR - bit 1 */
#define XJA11XX_WPR_MASK          ((uint8)0x02)
/* Bit WPF flag - bit 0 */
#define XJA11XX_WPF_MASK           ((uint8)0x01)

/* Default value of Data mask registers X */
#define XJA11XX_DATA_MASK_X_DEFAULT_VALUE ((uint8)0xFF)
/* Command to set Data mask registers X */
#define XJA11XX_DATA_MASK_X_SET_VALUE     ((uint8)0x00)

/* Data mask registers 0 */
#define XJA11XX_DATA_MASK_0_REG                     ((uint8)0x68)

/* Data mask registers 1 */
#define XJA11XX_DATA_MASK_1_REG                     ((uint8)0x69)

/* Data mask registers 2 */
#define XJA11XX_DATA_MASK_2_REG                     ((uint8)0x6A)

/* Data mask registers 3 */
#define XJA11XX_DATA_MASK_3_REG                     ((uint8)0x6B)

/* Data mask registers 4 */
#define XJA11XX_DATA_MASK_4_REG                     ((uint8)0x6C)

/* Data mask registers 5 */
#define XJA11XX_DATA_MASK_5_REG                     ((uint8)0x6D)

/* Data mask registers 6 */
#define XJA11XX_DATA_MASK_6_REG                     ((uint8)0x6E)

/* Data mask registers 7 */
#define XJA11XX_DATA_MASK_7_REG                     ((uint8)0x6F)

#endif /* (STD_ON == CANTRCV_XJA11XX_SUPPORTED) */

/*TCAN1145 registers*/
#if (STD_ON == CANTRCV_TCAN1145_SUPPORTED)

/* Access the register type */
#define TCAN1145_REG_WRITE                          ((uint8)0x01)
#define TCAN1145_REG_READ                           ((uint8)0x00)
#define TCAN1145_REG_BITMASKS                       ((uint8)0xFF)

/* 0x44 Check Can baudrate*/
#define TCAN1145_CAN_DATARATE_50                   ((uint16)50)
#define TCAN1145_CAN_DATARATE_100                  ((uint16)100)
#define TCAN1145_CAN_DATARATE_125                  ((uint16)125)
#define TCAN1145_CAN_DATARATE_250                  ((uint16)250)
#define TCAN1145_CAN_DATARATE_1000                 ((uint16)1000)

/*Mode Control Register*/
#define TCAN1145_MODE_CNTRL_REG                     ((uint8)0x10)
/* Bit ModeSelect - bit [0:2] */
#define TCAN1145_MC_MASK                   ((uint8)0x07)
/*Bit SW_EN - bit 7*/
#define TCAN1145_MODE_CNTRL_SW_EN          ((uint8)0x80)
#define TCAN1145_MODE_CNTRL_SW_EN_CLEAR    ((uint8)0x7F)
#define TCAN1145_MODE_CNTRL_REG_DEFAULT_VALUE ((uint8)0x04)
#define TCAN1145_MODE_CNTRL_BITMASKS        ((uint8)0xF8)
#define TCAN1145_MODE_CNTRL_SW_EN_SHIFT    (7) 

/*Wake Pin configuration*/
#define TCAN1145_WAKE_PIN_CONFIG_REG                ((uint8)0x11)
/*Bit Wake_STAT- bit[4:5]*/
#define TCAN1145_WAKE_PIN_CONFIG_CLEAR     ((uint8)0xCF)
/* Bit Status of WAKE config - bit [6:7] */
#define TCAN1145_WAKE_PIN_RE_EDGE       ((uint8)0x40)
#define TCAN1145_WAKE_PIN_FE_EDGE       ((uint8)0x80)
#define TCAN1145_WAKE_PIN_MASK          ((uint8)0x30)

/* ID Regsiters 1 */
#define TCAN1145_ID_REG1_REG                        ((uint8)0x30)

/* ID Regsiters 2 */
#define TCAN1145_ID_REG2_REG                        ((uint8)0x31)

/* ID Regsiters 3 */
#define TCAN1145_ID_REG3_REG                        ((uint8)0x32)
/*Bit IDE- bit 5*/
#define TCAN1145_ID_REG3_IDE_0_BIT          ((uint8)0xDF)
#define TCAN1145_ID_REG3_IDE_1_BIT          ((uint8)0x20)
/* Bit IDE - bit 5 */
#define TCAN1145_ID_REG3_IDE_CLEAR        ((uint8)0x20)
#define TCAN1145_ID_REG3_IDE_SHIFT        (5)
/*Bit for ID - bit [0:5]*/
#define TCAN1145_ID_REG3_REG_BITMASK        ((uint8)0xE0)
/*Bit for Extended ID - bit [5:7]*/
#define TCAN1145_ID_REG3_REG_EX_ID_BITMASK  ((uint8)0x3F)

/* ID Regsiters 4 */
#define TCAN1145_ID_REG4_REG                        ((uint8)0x33)
/*Bit for ID - bit [2:7]*/
#define TCAN1145_ID_REG4_REG_BITMASK        ((uint8)0x03)

/* ID Mask 1*/
#define TCAN1145_ID_MASK1_REG                       ((uint8)0x34)
/*Bit for Extended ID - bit [0:1]*/
#define TCAN1145_ID_MASK1_REG_BITMASK       ((uint8)0xFC)

/* ID Mask 2*/
#define TCAN1145_ID_MASK2_REG                       ((uint8)0x35)

/* ID Mask 3*/
#define TCAN1145_ID_MASK3_REG                       ((uint8)0x36)

/* ID Mask 4*/
#define TCAN1145_ID_MASK4_REG                       ((uint8)0x37)

/* ID Make,DLC,Data mask En */
#define TCAN1145_ID_MASK_DLC_REG                    ((uint8)0x38)
/*Bit MASK_EN - bit 0*/
#define TCAN1145_ID_MASK_DLC_MASK_ENABLE    ((uint8)0x01)
#define TCAN1145_ID_MASK_DLC_MASK_DISABLE   ((uint8)0xFE)
/*Bit for ID - bit [5:7]*/
#define TCAN1145_ID_MASK_DLC_BITMASK        ((uint8)0x1F)

/* Default value of Data mask registers Y */
#define TCAN1145_DATA_MASK_Y_DEFAULT_VALUE ((uint8)0xFF)
/* Command to set Data mask registers Y */
#define TCAN1145_DATA_MASK_Y_SET_VALUE     ((uint8)0x00)
/* Data Y register */
#define TCAN1145_DATA_MASK_7_REG                         ((uint8)0x39)
#define TCAN1145_DATA_MASK_6_REG                         ((uint8)0x3A)
#define TCAN1145_DATA_MASK_5_REG                         ((uint8)0x3B)
#define TCAN1145_DATA_MASK_4_REG                         ((uint8)0x3C)
#define TCAN1145_DATA_MASK_3_REG                         ((uint8)0x3D)
#define TCAN1145_DATA_MASK_2_REG                         ((uint8)0x3E)
#define TCAN1145_DATA_MASK_1_REG                         ((uint8)0x3F)
#define TCAN1145_DATA_MASK_0_REG                         ((uint8)0x40)
/* CAN and CAN FD DR and behavior */
#define TCAN1145_CONFIG1_REG                        ((uint8)0x44)
/*Bit FD_PASSIVE - bit7*/
#define TCAN1145_CONFIG1_SW_FD_PASSIVE      ((uint8)0x80)
/*Bit CAN_DR - bit [4:6]*/
#define TCAN1145_CONFIG1_CAN_DR             ((uint8)0x70)
#define TCAN1145_CONFIG1_CAN_DR_BITMASK     ((uint8)0x8F)
/*Bit CFD_DR - bit [2:3]*/
#define TCAN1145_CONFIG1_FD_DR_BITMASK      ((uint8)0xF3)
#define TCAN1145_CONFIG1_FD_DR_4X_BIT       ((uint8)0x04)

/* Mode Configuration register */ 
#define TCAN1145_CONFIG4_REG                        ((uint8)0x47)
/*Bit SWCFG - bit 7*/
#define TCAN1145_CONFIG4_SWCFG_REG_BIT      ((uint8)0x80)

/*selective wakeup interrupt 1*/
#define TCAN1145_INT_1_REG                          ((uint8)0x51)
/*Bit CANDOM - bit 0*/
#define TCAN1145_INT_1_CANDOM               ((uint8)0x01)
/*Bit CANDOM - bit 2*/
#define TCAN1145_INT_1_CANSLNT              ((uint8)0x04)
/*Bit CANINT - bit 6*/
#define TCAN1145_INT_1_CANINT_CLEAR_BIT     ((uint8)0xBF)
#define TCAN1145_INT_1_CANINT_REG           ((uint8)0x40)
/*Bit FRAME_OVF -bit 3*/
#define TCAN1145_INT_1_CLEAR_FRAME_OVF_BIT  ((uint8)0xF7)
#define TCAN1145_INT_1_FRAME_OVF_BIT        ((uint8)0x80)
#define TCAN1145_INT_1_CLEAR_FLAG_BITMASK   ((uint8)0x87)


/*selective wakeup interrupt 2*/
#define TCAN1145_INT_2_REG                          ((uint8)0x52)
/*Bit PWRON - bit 6*/
#define TCAN1145_INT_2_PWRON_BIT            ((uint8)0x40)
/*Bit SMS - bit 7*/
#define TCAN1145_INT_2_SMS_REG_CLEAR_BIT    ((uint8)0x7F)
/*Bit undervoltage - bit [2:4]*/
#define TCAN1145_INT_2_UVSUP_BIT            ((uint8)0x10)
#define TCAN1145_INT_2_UVIO_BIT             ((uint8)0x08)
#define TCAN1145_INT_2_UVCC_BIT             ((uint8)0x04)


/*selective wakeup interrupt 3*/
#define TCAN1145_INT_3_REG                          ((uint8)0x53)
/*Bit SWERR - bit 6*/
#define TCAN1145_INT_3_SWERR_BIT            ((uint8)0x40)

/*Interrupt Enavle for INT_1*/
#define TCAN1145_INT_ENB_1_REG                      ((uint8)0x56)
/*Bit SWERR - bit 6*/
#define TCAN1145_INT_ENB_1_CANSLNT_ENB      ((uint8)0x04)

#endif /* (STD_ON == CANTRCV_TCAN1145_SUPPORTED) */

/* TLE9255W registers */
#if (STD_ON == CANTRCV_TLE9255W_SUPPORTED)

/* Access the register type */
#define TLE9255W_REG_WRITE                          ((uint8)0x01)
#define TLE9255W_REG_READ                           ((uint8)0x00)

/* Mode Control Register */
#define TLE9255W_MODE_CTRL_REG                      ((uint8)0x01)
/* Bit Mode - bit [0:3] */
#define TLE9255W_MODE_MASK        ((uint8)0x0F)

/* Hardware Control register */
#define TLE9255W_HW_CTRL_REG                        ((uint8)0x02)
/* Default value of Hardware Control register */
#define TLE9255W_HW_CTRL_DEFAULT_VALUE ((uint8)0xE1)
/* Bit LWU_NEG - bit 6 */
#define TLE9255W_LWU_NEG_PERFORMED ((uint8)0x40)
/* Bit LWU_POS - bit 5 */
#define TLE9255W_LWU_POS_PERFORMED ((uint8)0x20)

/* TXD Timeout Control register */
#define TLE9255W_TXD_TO_CTRL_REG                    ((uint8)0x03)
/* Default value of TXD Timeout Control register */
#define TLE9255W_TXD_TO_CTRL_DEFAULT_VALUE ((uint8)0x01)

/* Supply Control register */
#define TLE9255W_SUPPLY_CTRL_REG                    ((uint8)0x04)
/* Default value of Supply Control register */
#define TLE9255W_SUPPLY_CTRL_DEFAULT_VALUE ((uint8)0xCC)

/* Selective Wake Control register */
#define TLE9255W_SWK_CTRL_1_REG                     ((uint8)0x05)
/* Default value of Selective Wake Control register */
#define TLE9255W_SWK_CTRL_1_DEFAULT_VALUE ((uint8)0x00)
/* Bit CFG_VAL - bit 0 */
#define TLE9255W_CFG_VAL_VALID    ((uint8)0x01)

/* Baudrate Control register */
#define TLE9255W_SWK_CTRL_2_REG                     ((uint8)0x06)
/* Default value of Baudrate Control register */
#define TLE9255W_SWK_CTRL_2_DEFAULT_VALUE ((uint8)0x04)
/* Bit BR - bit [0:2] */
#define TLE9255W_BR_CLEAR         ((uint8)0xF8)
/* Bit SWK_EN - bit 7 */
#define TLE9255W_SWK_MASK         ((uint8)0x80)
#define TLE9255W_SWK_EN_CLEAR     ((uint8)0x7F)
#define TLE9255W_SWK_EN_SHIFT     (7)

/* Identifier 3 Control register */
#define TLE9255W_SWK_ID3_CTRL_REG                   ((uint8)0x07)
/* Default value of Identifier 3 Control register */
#define TLE9255W_SWK_ID3_CTRL_DEFAULT_VALUE ((uint8)0x1F)
/* Bit ID28_24 - bit [0:4]  */
#define TLE9255W_ID28_24_MASK     ((uint32)0x1F000000)
/* Bit ID10_6 - bit [0:4] */
#define TLE9255W_ID10_6_MASK      ((uint32)0x000007C0)
/* Bit IDE - bit 5 */
#define TLE9255W_IDE_CLEAR        ((uint8)0x20)
#define TLE9255W_IDE_SHIFT        (5)

/* Identifier 2 Control register */
#define TLE9255W_SWK_ID2_CTRL_REG                   ((uint8)0x08)
/* Default value of Identifier 2 Control register */
#define TLE9255W_SWK_ID2_CTRL_DEFAULT_VALUE ((uint8)0xFF)
/* Bit ID23_16 - bit [0:7] */
#define TLE9255W_ID23_16_MASK     ((uint32)0x00FF0000)
/* Bit ID5_0 - bit [0:5] */
#define TLE9255W_ID5_0_MASK       ((uint32)0x0000003F)

/* Identifier 1 Control register */
#define TLE9255W_SWK_ID1_CTRL_REG                   ((uint8)0x09)
/* Default value of Identifier 1 Control register */
#define TLE9255W_SWK_ID1_CTRL_DEFAULT_VALUE ((uint8)0xFF)
/* Bit ID15_8 - bit [0:7] */
#define TLE9255W_ID15_8_MASK      ((uint32)0x0000FF00)

/* Identifier 0 Control register */
#define TLE9255W_SWK_ID0_CTRL_REG                   ((uint8)0x0A)
/* Default value of Identifier 0 Control register */
#define TLE9255W_SWK_ID0_CTRL_DEFAULT_VALUE ((uint8)0xFF)
/* Bit ID7_0 - bit [0:7] */
#define TLE9255W_ID7_0_MASK       ((uint32)0x000000FF)

/* Default value of Mask Identifier X Control register */
#define TLE9255W_SWK_MASK_IDX_CTRL_DEFAULT_VALUE ((uint8)0x00)

/* Mask Identifier 3 Control register */
#define TLE9255W_SWK_MASK_ID3_CTRL_REG              ((uint8)0x0B)
/* Bit Mask_ID28_24 - bit [0:4] */
#define TLE9255W_MASK_ID28_24_MASK  ((uint32)0x1F000000)

/* Mask Identifier 2 Control register */
#define TLE9255W_SWK_MASK_ID2_CTRL_REG              ((uint8)0x0C)
/* Bit Mask_ID23_16 - bit [0:7] */
#define TLE9255W_MASK_ID23_16_MASK  ((uint32)0x00FF0000)

/* Mask Identifier 1 Control register */
#define TLE9255W_SWK_MASK_ID1_CTRL_REG              ((uint8)0x0D)
/* Bit Mask_ID15_8 - bit [0:7] */
#define TLE9255W_MASK_ID15_8_MASK   ((uint32)0x0000FF00)
/* Bit MASK_ID10_8 - bit [8:10] */
#define TLE9255W_MASK_ID10_8_MASK   ((uint32)0x00000700)

/* Mask Identifier 0 Control register */
#define TLE9255W_SWK_MASK_ID0_CTRL_REG             ((uint8)0x0E)
/* Bit MASK_ID7_0 - bit [0:7] */
#define TLE9255W_MASK_ID7_0_MASK    ((uint32)0x000000FF)

/* Data Length Code Control register */
#define TLE9255W_SWK_DLC_CTRL_REG                   ((uint8)0x0F)
/* Default value of Data Length Code Control register */
#define TLE9255W_SWK_DLC_CTRL_DEFAULT_VALUE ((uint8)0x00)

/* Default value of Data X Control register */
#define TLE9255W_SWK_DATAX_CTRL_DEFAULT_VALUE ((uint8)0x00)

/* Data 7 Control register */
#define TLE9255W_SWK_DATA7_CTRL_REG                 ((uint8)0x10)

/* Data 6 Control register */
#define TLE9255W_SWK_DATA6_CTRL_REG                 ((uint8)0x11)

/* Data 5 Control register */
#define TLE9255W_SWK_DATA5_CTRL_REG                 ((uint8)0x12)

/* Data 4 Control register */
#define TLE9255W_SWK_DATA4_CTRL_REG                 ((uint8)0x13)

/* Data 3 Control register */
#define TLE9255W_SWK_DATA3_CTRL_REG                 ((uint8)0x14)

/* Data 2 Control register */
#define TLE9255W_SWK_DATA2_CTRL_REG                 ((uint8)0x15)

/* Data 1 Control register */
#define TLE9255W_SWK_DATA1_CTRL_REG                 ((uint8)0x16)

/* Data 0 Control register */
#define TLE9255W_SWK_DATA0_CTRL_REG                 ((uint8)0x17)

/* Transceiver Status register */
#define TLE9255W_TRANS_STAT_REG                     ((uint8)0x18)
/* Bit POR - bit 7 */
#define TLE9255W_POR_MASK           ((uint8)0x80)

/* Wake Status register */
#define TLE9255W_WAKE_STAT_REG                      ((uint8)0x1B)
/* Bit LWU - bit 2 */
#define TLE9255W_LWU_MASK           ((uint8)0x04)
/* Bit WUP - bit 1 */
#define TLE9255W_WUP_MASK           ((uint8)0x02)
/* Bit WUF - bit 0  */
#define TLE9255W_WUF_MASK           ((uint8)0x01)

/* Selective Wake Status register */
#define TLE9255W_SWK_STAT_REG                       ((uint8)0x1C)
/* Bit SYSERR - bit 4 */
#define TLE9255W_SYSERR_MASK        ((uint8)0x10)
/* Bit CANTO - bit 2 */
#define TLE9255W_CANTO_MASK         ((uint8)0x04)
/* Bit CANSIL - bit 1 */
#define TLE9255W_CANSIL_MASK        ((uint8)0x02)

#endif /* (STD_ON == CANTRCV_TLE9255W_SUPPORTED) */

/* polyspace +3 MISRA2012:D4.9 [Justified:Low] "Macro function used for unused pointer to reduce code size." */
#define CANTRCV_UNUSED_PTR(x)                  do { \
                                                    if ((x) != NULL_PTR) {} \
                                                  } while(0)

/* polyspace +4 MISRA2012:D4.9 [Justified:Low] "Macro function used for unused variable to reduce code size." */
#define CANTRCV_UNUSED_VAL(x)                 (void)x

/*******************************************************************************
**                      Global Data Type                                      **
*******************************************************************************/
/* @Trace: CanTrcv_SUD_DATATYPE_022 */
/* Transceiver Devices that are used for the implementation */
typedef enum
{
  CANTRCV_NCV7342 = 0,
  CANTRCV_TJA1040,
  CANTRCV_TJA1041,
  CANTRCV_TJA1041A,
  CANTRCV_TJA1042,
  CANTRCV_TJA1043,
  CANTRCV_TJA1463,
  CANTRCV_TJA1044,
  CANTRCV_TJA1050,
  CANTRCV_TJA1051,
  CANTRCV_TJA1054,
  CANTRCV_TJA1054A,
  CANTRCV_TJA1055,
  CANTRCV_TJA1057,
  CANTRCV_TJA1145,
  CANTRCV_TLE6250G,
  CANTRCV_TLE6251G,
  CANTRCV_TLE62513G,
  CANTRCV_TLE6251DS,
  CANTRCV_TLE62542G,
  CANTRCV_TLE62543G,
  CANTRCV_TLE7250G,
  CANTRCV_TLE7250LE,
  CANTRCV_TLE9255W,
  CANTRCV_UJA1169,
  CANTRCV_ARISU_CAN0,
  CANTRCV_ARISU_CAN1,
  CANTRCV_ARISU_CAN2,
  CANTRCV_ARISU_CAN3,
  CANTRCV_TLE9250SJ,
  CANTRCV_TLE9251VSJ,
  CANTRCV_TJA1059,
  CANTRCV_TCAN1043A,
  CANTRCV_TCAN1044,
  CANTRCV_TCAN1057,
  CANTRCV_TCAN1145
} CanTrcv_HwType;
/* @Trace: CanTrcv_SUD_DATATYPE_023 */
/* Sleep mode use type */
typedef enum
{
  CANTRCV_SLEEPMODE_UNUSED = 0,
  CANTRCV_SLEEPMODE_USED
} CanTrcv_StandByMode;

#if (STD_ON == CANTRCV_WAKEUP_SUPPORTED)
/* Define wake up pending status */
/* @Trace: CanTrcv_SUD_DATATYPE_024 */
typedef enum
{
  CANTRCV_WAKEUP_NO_PENDING = 0,
  CANTRCV_WAKEUP_PENDING
} CanTrcv_WakeUpPendingType;

/* Define status of wake up event on Can Transceiver */
/* @Trace: CanTrcv_SUD_DATATYPE_025 */
typedef enum
{
  CANTRCV_WAKE_UP_NOT_OCCURRED = 0,
  CANTRCV_WAKE_UP_OCCURRED
} CanTrcv_WakeupEventType;
#endif /* (STD_ON == CANTRCV_WAKEUP_SUPPORTED) */

#if (STD_ON == CANTRCV_ARISUCAN_SUPPORTED)

/* @Trace: CanTrcv_SUD_DATATYPE_019 */
typedef uint16 CanTrcv_ArisuCanType;

/* Define SBC mode for ArisuCan */
/* @Trace: CanTrcv_SUD_MACRO_006 */
/* @Trace: CanTrcv_SUD_DATATYPE_021 */
typedef enum
{
  ARISUCAN_SBCMODE_NORMAL = 0,
  ARISUCAN_SBCMODE_SLEEP,
  ARISUCAN_SBCMODE_STOP,
  ARISUCAN_SBCMODE_INIT,
  ARISUCAN_SBCMODE_RESTART,
  ARISUCAN_SBCMODE_MAX
} ArisuCan_SBCModeType;

/* Define CAN mode for ArisuCan */
/* @Trace: CanTrcv_SUD_DATATYPE_020 */
typedef enum
{
  ARISU_CANTRCV_OFF = 0,
  ARISU_CANTRCV_WAKECAPABLE,
  ARISU_CANTRCV_RECEIVEONLY,
  ARISU_CANTRCV_NORMAL,
  ARISU_CANTRCV_UNUSED = 0xFF
} ArisuCan_CANModeType;

/* Can configuration for ArisuCan */
/* @Trace: CanTrcv_SUD_DATATYPE_031 */
typedef struct
{
  ArisuCan_CANModeType ArisuCan0Mode;
  ArisuCan_CANModeType ArisuCan1Mode;
  ArisuCan_CANModeType ArisuCan2Mode;
  ArisuCan_CANModeType ArisuCan3Mode;
} ArisuCan_CanConfigType;

/* Define Channel mode for ArisuCan */
typedef enum
{
  ARISUCAN_UNCONFIGURE = 0,
  ARISUCAN_CONFIGURE
} ArisuCan_ChannelModeType;

/* Channel configuration for ArisuCan */
typedef struct
{
  ArisuCan_ChannelModeType ArisuCan0Used;
  ArisuCan_ChannelModeType ArisuCan1Used;
  ArisuCan_ChannelModeType ArisuCan2Used;
  ArisuCan_ChannelModeType ArisuCan3Used;
} ArisuCan_ChannelConfigType;

#define ARISUCAN_START_OFFSET       (CANTRCV_ARISU_CAN0)
#define ARISUCAN_END_OFFSET         (CANTRCV_ARISU_CAN3)
#define ARISUCAN_TYPE_NUM_OF_MODE   (0x04U)
#endif

#if (STD_ON == CANTRCV_XJA11XX_SUPPORTED)

/* Define lock or unlock register for XJA11XX */
/* @Trace: CanTrcv_SUD_DATATYPE_029 */
typedef enum
{
  XJA11XX_UNLOCK_REG = 0,
  XJA11XX_LOCK_REG
} XJA11XX_LockCtrlType;

/* Define Mode Control for XJA11XX */
/* @Trace: CanTrcv_SUD_DATATYPE_030 */
typedef enum
{
  XJA11XX_SLEEP_MODE = 1,
  XJA11XX_STANDBY_MODE = 4,
  XJA11XX_NORMAL_MODE = 7
} XJA11XX_ModeControlType;
/* @Trace: CanTrcv_SUD_DATATYPE_028 */
/* Define Can Mode for XJA11XX */
#if (STD_OFF == CANTRCV_SUPPORT_AR403)
typedef enum
{
  XJA11XX_CAN_OFFLINE_MODE = 0,
  XJA11XX_CAN_ACTIVE_UNDERVOLTAGE_MODE,
  XJA11XX_CAN_ACTIVE_UNDERVOLTAGE_DISABLE_MODE,
  XJA11XX_CAN_MODE_UNUSED
} XJA11XX_CanModeType;
#endif /*(STD_OFF == CANTRCV_SUPPORT_AR403)*/
#endif /* (STD_ON == CANTRCV_XJA11XX_SUPPORTED) */

#if (STD_ON == CANTRCV_TLE9255W_SUPPORTED)

/* Define Mode Control for TLE9255W */
/* @Trace: CanTrcv_SUD_DATATYPE_027 */
typedef enum
{
  TLE9255W_SLEEP_MODE = 1,
  TLE9255W_STANDBY_MODE = 2,
  TLE9255W_RECEIVE_ONLY_MODE = 4,
  TLE9255W_NORMAL_MODE = 8
} TLE9255W_ModeControlType;

#endif /* (STD_ON == CANTRCV_TLE9255W_SUPPORTED) */

#if (STD_ON == CANTRCV_TCAN1145_SUPPORTED)

/* Define Mode Control for TCAN1145 */
/* @Trace: CanTrcv_SUD_DATATYPE_039 */

typedef enum
{
  TCAN1145_SLEEP_MODE = 1,
  TCAN1145_STANDBY_MODE = 4,
  TCAN1145_NORMAL_MODE = 7
} TCAN1145_ModeControlType;
/* Define Can Mode for TCAN1145 */
/*#if (STD_OFF == CANTRCV_SUPPORT_AR403)
typedef enum
{
   XJA11XX_CAN_OFFLINE_MODE = 0,
  XJA11XX_CAN_ACTIVE_UNDERVOLTAGE_MODE,
  XJA11XX_CAN_ACTIVE_UNDERVOLTAGE_DISABLE_MODE,
  XJA11XX_CAN_MODE_UNUSED
} TCAN1145_CanModeType;
#endif*/ /*(STD_OFF == CANTRCV_SUPPORT_AR403)*/
#endif /* (STD_ON == CANTRCV_TCAN1145_SUPPORTED) */

/* @Trace: CanTrcv_SUD_DATATYPE_026 */
#if ((STD_ON == CANTRCV_XJA11XX_SUPPORTED) || \
  (STD_ON == CANTRCV_TLE9255W_SUPPORTED) || \
  (STD_ON == CANTRCV_TCAN1145_SUPPORTED))
/* Define local wake up direction */
typedef enum
{
  CANTRCV_NEGATIVE_EDGE = 0,
  CANTRCV_POSITIVE_EDGE
} LocalWakeupDirectionType;
#endif /* ((STD_ON == CANTRCV_XJA11XX_SUPPORTED) || \
  (STD_ON == CANTRCV_TLE9255W_SUPPORTED) || \
  (STD_ON == CANTRCV_TCAN1145_SUPPORTED)) */
/* @Trace: CanTrcv_SUD_DATATYPE_034 */
#if (STD_ON == CANTRCV_HW_PN_SUPPORTED)
/* Frame mask type */
typedef struct
{
  uint8 PnFrameDataMask0;
  uint8 PnFrameDataMask1;
  uint8 PnFrameDataMask2;
  uint8 PnFrameDataMask3;
  uint8 PnFrameDataMask4;
  uint8 PnFrameDataMask5;
  uint8 PnFrameDataMask6;
  uint8 PnFrameDataMask7;
} CanTrcv_PnFrameMaskSpecType;
/* @Trace: CanTrcv_SUD_DATATYPE_033 */
/* PN configuration type */
typedef struct
{
  /* Indicates whether the selective wake-up function is enabled or disabled
    in HW. */
  boolean PnEnabled;
  /* Indicates if the Bus Error (BUSERR) flag is managed by the BSW. */
  boolean BusErrFlag;
  /* Indicates whether extended or standard ID is used. */
  boolean PnCanIdIsExtended;
  /* Indicate if the Power On Reset (POR) flag is available and is managed by
    the transceiver. */
  boolean PowerOnFlag;
  /* Indicates the data transfer rate in kbps. */
  uint8 BaudRate;
  /* Data Length of the Wake-up Frame (WUF). */
  uint8 PnFrameDlc;
  /* PNDM bit '1' DLC check, '0' No DLC check */
  uint8 PnDlcMatchingCondition;
  /* CAN ID of the Wake-up Frame (WUF). */
  uint32 PnFrameCanId;
  /* ID Mask for the selective activation of the transceiver. */
  uint32 PnFrameCanIdMask;
  /* Defines data payload mask to be used on the received payload in order to
    determine */
  const CanTrcv_PnFrameMaskSpecType* PnFrameMaskSpec;
} CanTrcv_PartialNetworkType;
#endif /* (STD_ON == CANTRCV_HW_PN_SUPPORTED) */

/* CAN Transceiver Driver Network Structure */
/* @Trace: CanTrcv_SUD_DATATYPE_032 */
typedef struct
{
  /* Indicate channel is used or not */
  boolean ChannelUsed;
  /* ECU power supply controlled by this transceiver or not */
  boolean ControlPowerSupply;
  #if (STD_ON == CANTRCV_WAKEUP_SUPPORTED)
  /* Indicate wake up by bus supported or not */
  boolean WakeupByBusUsed;
  #endif /* (STD_ON == CANTRCV_WAKEUP_SUPPORTED) */
  /* Select sleep mode is used or not */
  CanTrcv_StandByMode SleepModeUsed;
  #if (STD_ON == CANTRCV_SPI_SUPPORTED)
  /* Define whether the access to the Spi sequence is synchronous or
    asynchronous. */
  boolean SpiAccessSynchronous;
  #endif /* (STD_ON == CANTRCV_SPI_SUPPORTED) */
  #if (STD_ON == CANTRCV_HW_PN_SUPPORTED)
  /* Partial network configuration index */
  uint8 PnNetworkIndex;
  #endif /* (STD_ON == CANTRCV_HW_PN_SUPPORTED) */
  #if(STD_OFF == CANTRCV_SUPPORT_AR403)
  #if (STD_ON == CANTRCV_ICU_CHANNEL_USED)
  /* Reference to the IcuChannel to enable/disable the interrupts */
  Icu_ChannelType IcuChannelId;
  #endif /* (STD_ON == CANTRCV_ICU_CHANNEL_USED) */
  #endif /*(STD_OFF == CANTRCV_SUPPORT_AR403)*/
  /* DIO STB Pin or SPI channel ID in case using SPI */
  Dio_ChannelType SelectPin1;
  /* DIO EN Pin or SPI sequence ID in case using SPI */
  Dio_ChannelType SelectPin2;
  /* DIO ERR Pin or Select chip selection in case using SPI */
  Dio_ChannelType SelectPin3;
  #if (STD_OFF == CANTRCV_SUPPORT_AR403)
  #if (STD_ON == CANTRCV_E_BUS_ERROR_SUPPORTED)
  /* CANTRCV_E_BUS_ERROR */
  Dem_EventIdType DemEventId;
  #endif /* (STD_ON == CANTRCV_E_BUS_ERROR_SUPPORTED) */
  #endif /*(STD_OFF == CANTRCV_SUPPORT_AR403)*/
  /* Hardware device name */
  CanTrcv_HwType CanTrcvHwDev;
  /* State of CAN transceiver after call to CanTrcv_Init */
  CanTrcv_TrcvModeType InitState;
  #if (STD_OFF == CANTRCV_SUPPORT_AR403)
  #if (STD_ON == CANTRCV_XJA11XX_SUPPORTED)
  /* Can Mode of XJA11XX device */
  XJA11XX_CanModeType XJA11XXCanMode;
  #endif /* (STD_ON == CANTRCV_XJA11XX_SUPPORTED) */
  #if ((STD_ON == CANTRCV_XJA11XX_SUPPORTED) || \
  (STD_ON == CANTRCV_TLE9255W_SUPPORTED) || \
  (STD_ON == CANTRCV_TCAN1145_SUPPORTED))
  /* Direction perform local wake up */
  LocalWakeupDirectionType LocalWakeupDirection;
  #endif /* #if ((STD_ON == CANTRCV_XJA11XX_SUPPORTED) || \
  (STD_ON == CANTRCV_TLE9255W_SUPPORTED) || \
  (STD_ON == CANTRCV_TCAN1145_SUPPORTED))*/
  #if (STD_ON == CANTRCV_HW_PN_SUPPORTED)
  #if (STD_ON == CANTRCV_HW_POR_SUPPORTED)
  /* Reference to specify the wakeup sources that should be used if the HW
    supports POR flags */
  EcuM_WakeupSourceType PorWakeupSource;
  #endif /* (STD_ON == CANTRCV_HW_POR_SUPPORTED) */
  /* Reference to specify the wakeup sources that should be used if the HW
    supports SYSERR flags */
  EcuM_WakeupSourceType SyserrWakeupSource;
  #endif /* (STD_ON == CANTRCV_HW_PN_SUPPORTED) */
  #if (STD_ON == CANTRCV_WAKEUP_SUPPORTED)
  /* Wakeup source Id */
  EcuM_WakeupSourceType WakeupSource;
  #endif /* (STD_ON == CANTRCV_WAKEUP_SUPPORTED) */
  #endif /*(STD_OFF == CANTRCV_SUPPORT_AR403)*/
} CanTrcv_NetworkType;
/* @Trace: CanTrcv_SUD_DATATYPE_038 */
typedef struct
{
  P2FUNC(Std_ReturnType, CANTRCV_APPL_CODE, WriteReg)(
    CONST(uint8, AUTOMATIC) transceiver,
    CONST(uint8, AUTOMATIC) address,
    CONST(uint8, AUTOMATIC) data);

  P2FUNC(Std_ReturnType, CANTRCV_APPL_CODE, ReadReg)(
    CONST(uint8, AUTOMATIC) transceiver,
    CONST(uint8, AUTOMATIC) address,
    P2VAR(uint8, AUTOMATIC, CANTRCV_VAR) ptrDesData);

}CanTrcv_WriteReadReg_Type;

/* @Trace: SWS_CanTrcv_00209 SRS_BSW_00404 SRS_BSW_00438 */
/* Can Transceiver configuration type */
#if (STD_ON == CANTRCV_POSTBUILD_SUPPORTED)
typedef struct
{
  #if (STD_OFF == CANTRCV_SPI_SUPPORTED) && \
    (STD_OFF == CANTRCV_SPI_ASYNCTRANSMIT_SUPPORTED) && \
    (STD_OFF == CANTRCV_HW_PN_SUPPORTED)
  uint8 ConfigIndex;
  #endif /* (STD_OFF == CANTRCV_SPI_SUPPORTED) && \
    (STD_OFF == CANTRCV_SPI_ASYNCTRANSMIT_SUPPORTED) && \
    (STD_OFF == CANTRCV_HW_PN_SUPPORTED) */
  #if (STD_ON == CANTRCV_SPI_SUPPORTED)
  /* The number of retry when SPI communication failure */
  uint16 SPICommRetries;
  #endif /* STD_ON == CANTRCV_SPI_SUPPORTED */
  #if (STD_OFF == CANTRCV_SUPPORT_AR403)
  #if (STD_ON == CANTRCV_SPI_ASYNCTRANSMIT_SUPPORTED)
  /* The timeout for Spi_asynctransmit */
  uint32 SPICommTimeout;
  #endif /* STD_ON == CANTRCV_SPI_ASYNCTRANSMIT_SUPPORTED */
  #endif /*(STD_OFF == CANTRCV_SUPPORT_AR403)*/
  #if (STD_ON == CANTRCV_HW_PN_SUPPORTED)
  /* Partial network configuration */
  const CanTrcv_PartialNetworkType* PnNetwork;
  #endif /* (STD_ON == CANTRCV_HW_PN_SUPPORTED) */
} CanTrcv_ConfigType;
#else
typedef void CanTrcv_ConfigType;
#endif /* (STD_ON == CANTRCV_POSTBUILD_SUPPORTED) */

#endif /* CANTRCV_INTTYPES_H */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
