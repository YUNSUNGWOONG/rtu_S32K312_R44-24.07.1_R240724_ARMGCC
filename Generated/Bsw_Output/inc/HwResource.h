
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
**  FILE-NAME : HwResource.h                                                  **
**                                                                            **
**  PRODUCT   : HwResource Module                                             **
**                                                                            **
**  NOTE: This file is auto generated, do not edit this file manually.        **
**                                                                            **
********************************************************************************

********************************************************************************
**                      Generation Tool Information                           **
********************************************************************************
**  Tool Version: 1.2.0.1                                                     **
*******************************************************************************/

#ifndef HWRESOURCE_H
#define HWRESOURCE_H

#include "Std_Types.h"

/*******************************************************************************
**                      Definitions                                           **
*******************************************************************************/
/* MASK */
#define HWRESOURCE_VENDOR_MASK    0xF0000000u
#define HWRESOURCE_FAMILY_MASK    0x0FF00000u
#define HWRESOURCE_MCU_MASK       0x000FFF00u
#define HWRESOURCE_PACKAGE_MASK   0x000000FFu

/* OFFSET */
#define HWRESOURCE_VENDOR_OFFSET  28u
#define HWRESOURCE_FAMILY_OFFSET  20u
#define HWRESOURCE_MCU_OFFSET     8u
#define HWRESOURCE_PACKAGE_OFFSET 0u

/* Feature Definition */
#define SWP_USE_RAMTST            STD_OFF
#define SWP_USE_ROMTST            STD_OFF
#define SWP_USE_IOHWAB            STD_ON
#define SWP_USE_DATALOG           STD_OFF
#define SWP_USE_NVM               STD_ON

/* polyspace-begin MISRA-C3:D4.9 [Justified:Low] "No Impact of this rule violation" */
/*******************************************************************************
**                      HW Resource List                                      **
*******************************************************************************/
/* Set Macro */
#define HWRESOURCE_SET_VALUE(value, offset) ((value) << (offset))

/* Vendor List */
#define HWRESOURCE_CYPRESS     (HWRESOURCE_SET_VALUE(0x1u, HWRESOURCE_VENDOR_OFFSET))
#define HWRESOURCE_FREESCALE   (HWRESOURCE_SET_VALUE(0x2u, HWRESOURCE_VENDOR_OFFSET))
#define HWRESOURCE_INFINEON    (HWRESOURCE_SET_VALUE(0x3u, HWRESOURCE_VENDOR_OFFSET))
#define HWRESOURCE_NVIDIA      (HWRESOURCE_SET_VALUE(0x4u, HWRESOURCE_VENDOR_OFFSET))
#define HWRESOURCE_NXP         (HWRESOURCE_SET_VALUE(0x5u, HWRESOURCE_VENDOR_OFFSET))
#define HWRESOURCE_RENESAS     (HWRESOURCE_SET_VALUE(0x6u, HWRESOURCE_VENDOR_OFFSET))
#define HWRESOURCE_ST          (HWRESOURCE_SET_VALUE(0x7u, HWRESOURCE_VENDOR_OFFSET))
#define HWRESOURCE_TI          (HWRESOURCE_SET_VALUE(0x8u, HWRESOURCE_VENDOR_OFFSET))

/* Family List */
#define HWRESOURCE_MPC5601X    (HWRESOURCE_SET_VALUE(0x01u, HWRESOURCE_FAMILY_OFFSET))
#define HWRESOURCE_MPC5602X    (HWRESOURCE_SET_VALUE(0x02u, HWRESOURCE_FAMILY_OFFSET))
#define HWRESOURCE_MPC5603X    (HWRESOURCE_SET_VALUE(0x03u, HWRESOURCE_FAMILY_OFFSET))
#define HWRESOURCE_MPC5604X    (HWRESOURCE_SET_VALUE(0x04u, HWRESOURCE_FAMILY_OFFSET))
#define HWRESOURCE_MPC5605X    (HWRESOURCE_SET_VALUE(0x05u, HWRESOURCE_FAMILY_OFFSET))
#define HWRESOURCE_MPC5606X    (HWRESOURCE_SET_VALUE(0x06u, HWRESOURCE_FAMILY_OFFSET))
#define HWRESOURCE_MPC5607X    (HWRESOURCE_SET_VALUE(0x07u, HWRESOURCE_FAMILY_OFFSET))
#define HWRESOURCE_ORIN        (HWRESOURCE_SET_VALUE(0x08u, HWRESOURCE_FAMILY_OFFSET))
#define HWRESOURCE_RH850F1X    (HWRESOURCE_SET_VALUE(0x09u, HWRESOURCE_FAMILY_OFFSET))
#define HWRESOURCE_S32G2X      (HWRESOURCE_SET_VALUE(0x0Au, HWRESOURCE_FAMILY_OFFSET))
#define HWRESOURCE_S32K11X     (HWRESOURCE_SET_VALUE(0x0Bu, HWRESOURCE_FAMILY_OFFSET))
#define HWRESOURCE_S32K14X     (HWRESOURCE_SET_VALUE(0x0Cu, HWRESOURCE_FAMILY_OFFSET))
#define HWRESOURCE_S32K31X     (HWRESOURCE_SET_VALUE(0x0Du, HWRESOURCE_FAMILY_OFFSET))
#define HWRESOURCE_S6J32XX     (HWRESOURCE_SET_VALUE(0x0Eu, HWRESOURCE_FAMILY_OFFSET))
#define HWRESOURCE_S6J33XX     (HWRESOURCE_SET_VALUE(0x0Fu, HWRESOURCE_FAMILY_OFFSET))
#define HWRESOURCE_SPC58XB     (HWRESOURCE_SET_VALUE(0x10u, HWRESOURCE_FAMILY_OFFSET))
#define HWRESOURCE_SPC58XC     (HWRESOURCE_SET_VALUE(0x11u, HWRESOURCE_FAMILY_OFFSET))
#define HWRESOURCE_SPC58XG     (HWRESOURCE_SET_VALUE(0x12u, HWRESOURCE_FAMILY_OFFSET))
#define HWRESOURCE_TC21X       (HWRESOURCE_SET_VALUE(0x13u, HWRESOURCE_FAMILY_OFFSET))
#define HWRESOURCE_TC22X       (HWRESOURCE_SET_VALUE(0x14u, HWRESOURCE_FAMILY_OFFSET))
#define HWRESOURCE_TC23X       (HWRESOURCE_SET_VALUE(0x15u, HWRESOURCE_FAMILY_OFFSET))
#define HWRESOURCE_TC26X       (HWRESOURCE_SET_VALUE(0x16u, HWRESOURCE_FAMILY_OFFSET))
#define HWRESOURCE_TC27X       (HWRESOURCE_SET_VALUE(0x17u, HWRESOURCE_FAMILY_OFFSET))
#define HWRESOURCE_TC29X       (HWRESOURCE_SET_VALUE(0x18u, HWRESOURCE_FAMILY_OFFSET))
#define HWRESOURCE_TC38X       (HWRESOURCE_SET_VALUE(0x19u, HWRESOURCE_FAMILY_OFFSET))
#define HWRESOURCE_TC39X       (HWRESOURCE_SET_VALUE(0x1Au, HWRESOURCE_FAMILY_OFFSET))
#define HWRESOURCE_TDA4XX      (HWRESOURCE_SET_VALUE(0x1Bu, HWRESOURCE_FAMILY_OFFSET))

/* MCU List */
#define HWRESOURCE_MPC5601D    (HWRESOURCE_SET_VALUE(0x001u, HWRESOURCE_MCU_OFFSET))
#define HWRESOURCE_MPC5602B    (HWRESOURCE_SET_VALUE(0x002u, HWRESOURCE_MCU_OFFSET))
#define HWRESOURCE_MPC5602C    (HWRESOURCE_SET_VALUE(0x003u, HWRESOURCE_MCU_OFFSET))
#define HWRESOURCE_MPC5602D    (HWRESOURCE_SET_VALUE(0x004u, HWRESOURCE_MCU_OFFSET))
#define HWRESOURCE_MPC5603B    (HWRESOURCE_SET_VALUE(0x005u, HWRESOURCE_MCU_OFFSET))
#define HWRESOURCE_MPC5603C    (HWRESOURCE_SET_VALUE(0x006u, HWRESOURCE_MCU_OFFSET))
#define HWRESOURCE_MPC5604B    (HWRESOURCE_SET_VALUE(0x007u, HWRESOURCE_MCU_OFFSET))
#define HWRESOURCE_MPC5604C    (HWRESOURCE_SET_VALUE(0x008u, HWRESOURCE_MCU_OFFSET))
#define HWRESOURCE_MPC5605B    (HWRESOURCE_SET_VALUE(0x009u, HWRESOURCE_MCU_OFFSET))
#define HWRESOURCE_MPC5606B    (HWRESOURCE_SET_VALUE(0x00Au, HWRESOURCE_MCU_OFFSET))
#define HWRESOURCE_MPC5607B    (HWRESOURCE_SET_VALUE(0x00Bu, HWRESOURCE_MCU_OFFSET))
#define HWRESOURCE_ORIN_FSI    (HWRESOURCE_SET_VALUE(0x00Cu, HWRESOURCE_MCU_OFFSET))
#define HWRESOURCE_RH850F1H    (HWRESOURCE_SET_VALUE(0x00Du, HWRESOURCE_MCU_OFFSET))
#define HWRESOURCE_RH850F1K    (HWRESOURCE_SET_VALUE(0x00Eu, HWRESOURCE_MCU_OFFSET))
#define HWRESOURCE_RH850F1KM   (HWRESOURCE_SET_VALUE(0x00Fu, HWRESOURCE_MCU_OFFSET))
#define HWRESOURCE_RH850F1L    (HWRESOURCE_SET_VALUE(0x010u, HWRESOURCE_MCU_OFFSET))
#define HWRESOURCE_S32G274A    (HWRESOURCE_SET_VALUE(0x011u, HWRESOURCE_MCU_OFFSET))
#define HWRESOURCE_S32K116     (HWRESOURCE_SET_VALUE(0x012u, HWRESOURCE_MCU_OFFSET))
#define HWRESOURCE_S32K118     (HWRESOURCE_SET_VALUE(0x013u, HWRESOURCE_MCU_OFFSET))
#define HWRESOURCE_S32K142     (HWRESOURCE_SET_VALUE(0x014u, HWRESOURCE_MCU_OFFSET))
#define HWRESOURCE_S32K144     (HWRESOURCE_SET_VALUE(0x015u, HWRESOURCE_MCU_OFFSET))
#define HWRESOURCE_S32K146     (HWRESOURCE_SET_VALUE(0x016u, HWRESOURCE_MCU_OFFSET))
#define HWRESOURCE_S32K148     (HWRESOURCE_SET_VALUE(0x017u, HWRESOURCE_MCU_OFFSET))
#define HWRESOURCE_S32K312     (HWRESOURCE_SET_VALUE(0x018u, HWRESOURCE_MCU_OFFSET))
#define HWRESOURCE_S32K314     (HWRESOURCE_SET_VALUE(0x019u, HWRESOURCE_MCU_OFFSET))
#define HWRESOURCE_S6J320A     (HWRESOURCE_SET_VALUE(0x01Au, HWRESOURCE_MCU_OFFSET))
#define HWRESOURCE_S6J320C     (HWRESOURCE_SET_VALUE(0x01Bu, HWRESOURCE_MCU_OFFSET))
#define HWRESOURCE_S6J331E     (HWRESOURCE_SET_VALUE(0x01Cu, HWRESOURCE_MCU_OFFSET))
#define HWRESOURCE_SPC584B     (HWRESOURCE_SET_VALUE(0x01Du, HWRESOURCE_MCU_OFFSET))
#define HWRESOURCE_SPC584C     (HWRESOURCE_SET_VALUE(0x01Eu, HWRESOURCE_MCU_OFFSET))
#define HWRESOURCE_SPC584G     (HWRESOURCE_SET_VALUE(0x01Fu, HWRESOURCE_MCU_OFFSET))
#define HWRESOURCE_SPC58EC     (HWRESOURCE_SET_VALUE(0x020u, HWRESOURCE_MCU_OFFSET))
#define HWRESOURCE_SPC58EG     (HWRESOURCE_SET_VALUE(0x021u, HWRESOURCE_MCU_OFFSET))
#define HWRESOURCE_SPC58NG     (HWRESOURCE_SET_VALUE(0x022u, HWRESOURCE_MCU_OFFSET))
#define HWRESOURCE_TC212L      (HWRESOURCE_SET_VALUE(0x023u, HWRESOURCE_MCU_OFFSET))
#define HWRESOURCE_TC213L      (HWRESOURCE_SET_VALUE(0x024u, HWRESOURCE_MCU_OFFSET))
#define HWRESOURCE_TC214L      (HWRESOURCE_SET_VALUE(0x025u, HWRESOURCE_MCU_OFFSET))
#define HWRESOURCE_TC222L      (HWRESOURCE_SET_VALUE(0x026u, HWRESOURCE_MCU_OFFSET))
#define HWRESOURCE_TC223L      (HWRESOURCE_SET_VALUE(0x027u, HWRESOURCE_MCU_OFFSET))
#define HWRESOURCE_TC224L      (HWRESOURCE_SET_VALUE(0x028u, HWRESOURCE_MCU_OFFSET))
#define HWRESOURCE_TC233L      (HWRESOURCE_SET_VALUE(0x029u, HWRESOURCE_MCU_OFFSET))
#define HWRESOURCE_TC234L      (HWRESOURCE_SET_VALUE(0x02Au, HWRESOURCE_MCU_OFFSET))
#define HWRESOURCE_TC237L      (HWRESOURCE_SET_VALUE(0x02Bu, HWRESOURCE_MCU_OFFSET))
#define HWRESOURCE_TC264D      (HWRESOURCE_SET_VALUE(0x02Cu, HWRESOURCE_MCU_OFFSET))
#define HWRESOURCE_TC265D      (HWRESOURCE_SET_VALUE(0x02Du, HWRESOURCE_MCU_OFFSET))
#define HWRESOURCE_TC267D      (HWRESOURCE_SET_VALUE(0x02Eu, HWRESOURCE_MCU_OFFSET))
#define HWRESOURCE_TC275T      (HWRESOURCE_SET_VALUE(0x02Fu, HWRESOURCE_MCU_OFFSET))
#define HWRESOURCE_TC277T      (HWRESOURCE_SET_VALUE(0x030u, HWRESOURCE_MCU_OFFSET))
#define HWRESOURCE_TC297T      (HWRESOURCE_SET_VALUE(0x031u, HWRESOURCE_MCU_OFFSET))
#define HWRESOURCE_TC298T      (HWRESOURCE_SET_VALUE(0x032u, HWRESOURCE_MCU_OFFSET))
#define HWRESOURCE_TC299T      (HWRESOURCE_SET_VALUE(0x033u, HWRESOURCE_MCU_OFFSET))
#define HWRESOURCE_TC387X      (HWRESOURCE_SET_VALUE(0x034u, HWRESOURCE_MCU_OFFSET))
#define HWRESOURCE_TC389X      (HWRESOURCE_SET_VALUE(0x035u, HWRESOURCE_MCU_OFFSET))
#define HWRESOURCE_TC397X      (HWRESOURCE_SET_VALUE(0x036u, HWRESOURCE_MCU_OFFSET))
#define HWRESOURCE_TC397X_ADAS (HWRESOURCE_SET_VALUE(0x037u, HWRESOURCE_MCU_OFFSET))
#define HWRESOURCE_TC399X      (HWRESOURCE_SET_VALUE(0x038u, HWRESOURCE_MCU_OFFSET))
#define HWRESOURCE_TDA4VM      (HWRESOURCE_SET_VALUE(0x039u, HWRESOURCE_MCU_OFFSET))

/* Package List */
#define HWRESOURCE_BGA292      (HWRESOURCE_SET_VALUE(0x01u, HWRESOURCE_PACKAGE_OFFSET))
#define HWRESOURCE_BGA416      (HWRESOURCE_SET_VALUE(0x02u, HWRESOURCE_PACKAGE_OFFSET))
#define HWRESOURCE_BGA525      (HWRESOURCE_SET_VALUE(0x03u, HWRESOURCE_PACKAGE_OFFSET))
#define HWRESOURCE_ELQFP176    (HWRESOURCE_SET_VALUE(0x04u, HWRESOURCE_PACKAGE_OFFSET))
#define HWRESOURCE_ETQFP100    (HWRESOURCE_SET_VALUE(0x05u, HWRESOURCE_PACKAGE_OFFSET))
#define HWRESOURCE_ETQFP144    (HWRESOURCE_SET_VALUE(0x06u, HWRESOURCE_PACKAGE_OFFSET))
#define HWRESOURCE_ETQFP64     (HWRESOURCE_SET_VALUE(0x07u, HWRESOURCE_PACKAGE_OFFSET))
#define HWRESOURCE_FCBGA827    (HWRESOURCE_SET_VALUE(0x08u, HWRESOURCE_PACKAGE_OFFSET))
#define HWRESOURCE_FPBGA233    (HWRESOURCE_SET_VALUE(0x09u, HWRESOURCE_PACKAGE_OFFSET))
#define HWRESOURCE_FPBGA272    (HWRESOURCE_SET_VALUE(0x0Au, HWRESOURCE_PACKAGE_OFFSET))
#define HWRESOURCE_LFBGA292    (HWRESOURCE_SET_VALUE(0x0Bu, HWRESOURCE_PACKAGE_OFFSET))
#define HWRESOURCE_LFBGA516    (HWRESOURCE_SET_VALUE(0x0Cu, HWRESOURCE_PACKAGE_OFFSET))
#define HWRESOURCE_LQFP100     (HWRESOURCE_SET_VALUE(0x0Du, HWRESOURCE_PACKAGE_OFFSET))
#define HWRESOURCE_LQFP144     (HWRESOURCE_SET_VALUE(0x0Eu, HWRESOURCE_PACKAGE_OFFSET))
#define HWRESOURCE_LQFP176     (HWRESOURCE_SET_VALUE(0x0Fu, HWRESOURCE_PACKAGE_OFFSET))
#define HWRESOURCE_LQFP48      (HWRESOURCE_SET_VALUE(0x10u, HWRESOURCE_PACKAGE_OFFSET))
#define HWRESOURCE_LQFP64      (HWRESOURCE_SET_VALUE(0x11u, HWRESOURCE_PACKAGE_OFFSET))
#define HWRESOURCE_LQFP80      (HWRESOURCE_SET_VALUE(0x12u, HWRESOURCE_PACKAGE_OFFSET))
#define HWRESOURCE_MAPBGA100   (HWRESOURCE_SET_VALUE(0x13u, HWRESOURCE_PACKAGE_OFFSET))
#define HWRESOURCE_MAPBGA208   (HWRESOURCE_SET_VALUE(0x14u, HWRESOURCE_PACKAGE_OFFSET))
#define HWRESOURCE_MAPBGA257   (HWRESOURCE_SET_VALUE(0x15u, HWRESOURCE_PACKAGE_OFFSET))
#define HWRESOURCE_MQFP100     (HWRESOURCE_SET_VALUE(0x16u, HWRESOURCE_PACKAGE_OFFSET))
#define HWRESOURCE_MQFP172     (HWRESOURCE_SET_VALUE(0x17u, HWRESOURCE_PACKAGE_OFFSET))
#define HWRESOURCE_QFN32       (HWRESOURCE_SET_VALUE(0x18u, HWRESOURCE_PACKAGE_OFFSET))
#define HWRESOURCE_SOC         (HWRESOURCE_SET_VALUE(0x19u, HWRESOURCE_PACKAGE_OFFSET))
#define HWRESOURCE_TEQFP144    (HWRESOURCE_SET_VALUE(0x1Au, HWRESOURCE_PACKAGE_OFFSET))
#define HWRESOURCE_TEQFP176    (HWRESOURCE_SET_VALUE(0x1Bu, HWRESOURCE_PACKAGE_OFFSET))
#define HWRESOURCE_TEQFP208    (HWRESOURCE_SET_VALUE(0x1Cu, HWRESOURCE_PACKAGE_OFFSET))
#define HWRESOURCE_TEQFP216    (HWRESOURCE_SET_VALUE(0x1Du, HWRESOURCE_PACKAGE_OFFSET))
#define HWRESOURCE_TEQFP256    (HWRESOURCE_SET_VALUE(0x1Eu, HWRESOURCE_PACKAGE_OFFSET))
#define HWRESOURCE_TQFP100     (HWRESOURCE_SET_VALUE(0x1Fu, HWRESOURCE_PACKAGE_OFFSET))
#define HWRESOURCE_TQFP144     (HWRESOURCE_SET_VALUE(0x20u, HWRESOURCE_PACKAGE_OFFSET))
#define HWRESOURCE_TQFP80      (HWRESOURCE_SET_VALUE(0x21u, HWRESOURCE_PACKAGE_OFFSET))


/*******************************************************************************
**                      HW Resource Type                                      **
*******************************************************************************/
#define HWRESOURCE_TYPE (HWRESOURCE_NXP | HWRESOURCE_S32K31X | HWRESOURCE_S32K312 | HWRESOURCE_MQFP172)

/*******************************************************************************
**                      Function Macros                                       **
*******************************************************************************/
/* Get Macros */
#define HWRESOURCE_GET_VENDOR()   (HWRESOURCE_TYPE & HWRESOURCE_VENDOR_MASK)
#define HWRESOURCE_GET_FAMILY()   (HWRESOURCE_TYPE & HWRESOURCE_FAMILY_MASK)
#define HWRESOURCE_GET_MCU()      (HWRESOURCE_TYPE & HWRESOURCE_MCU_MASK)
#define HWRESOURCE_GET_PACKAGE()  (HWRESOURCE_TYPE & HWRESOURCE_PACKAGE_MASK)

/* Check Macros */
#define HWRESOURCE_VENDOR(value)  (HWRESOURCE_GET_VENDOR() == (value))
#define HWRESOURCE_FAMILY(value)  (HWRESOURCE_GET_FAMILY() == (value))
#define HWRESOURCE_MCU(value)     (HWRESOURCE_GET_MCU() == (value))
#define HWRESOURCE_PACKAGE(value) (HWRESOURCE_GET_PACKAGE() == (value))
#define HWRESOURCE_MCU_PACKAGE(mcu, package) \
                            (HWRESOURCE_MCU(mcu) && HWRESOURCE_PACKAGE(package))

/* polyspace-end MISRA-C3:D4.9 */

/* Example for Use

#if HWRESOURCE_VENDOR(HWRESOURCE_NXP)
#endif

#if HWRESOURCE_FAMILY(HWRESOURCE_S32K31X)
#endif

#if HWRESOURCE_MCU(HWRESOURCE_S32K312)
#endif

#if HWRESOURCE_PACKAGE(HWRESOURCE_MQFP172)
#endif

#if HWRESOURCE_MCU_PACKAGE(HWRESOURCE_S32K312, HWRESOURCE_MQFP172)
#endif
*/

#endif /* HWRESOURCE_H */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
