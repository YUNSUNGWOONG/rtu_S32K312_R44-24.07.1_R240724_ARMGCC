/*==================================================================================================
*   Project              : RTD AUTOSAR 4.7
*   Platform             : CORTEXM
*   Peripheral           : ADC_SAR
*   Dependencies         : none
*
*   Autosar Version      : 4.7.0
*   Autosar Revision     : ASR_REL_4_7_REV_0000
*   Autosar Conf.Variant :
*   SW Version           : 3.0.0
*   Build Version        : S32K3_RTD_3_0_0_P01_D2303_ASR_REL_4_7_REV_0000_20230331
*
*   Copyright 2020 - 2023 NXP Semiconductors
*
*   NXP Confidential. This software is owned or controlled by NXP and may only be
*   used strictly in accordance with the applicable license terms. By expressly
*   accepting such terms or by downloading, installing, activating and/or otherwise
*   using the software, you are agreeing that you have read, and that you agree to
*   comply with and are bound by, such license terms. If you do not agree to be
*   bound by the applicable license terms, then you may not retain, install,
*   activate or otherwise use the software.
==================================================================================================*/

#ifndef ADC_IPW_CFGDEFINES_H
#define ADC_IPW_CFGDEFINES_H

/**
*   @file
*
*   @addtogroup adc_ipw_config Adc Ipw Configuration
*   @{
*/

#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/
/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/

#define ADC_IPW_VENDOR_ID_CFGDEFINES                     43
#define ADC_IPW_AR_RELEASE_MAJOR_VERSION_CFGDEFINES      4
#define ADC_IPW_AR_RELEASE_MINOR_VERSION_CFGDEFINES      7
#define ADC_IPW_AR_RELEASE_REVISION_VERSION_CFGDEFINES   0
#define ADC_IPW_SW_MAJOR_VERSION_CFGDEFINES              3
#define ADC_IPW_SW_MINOR_VERSION_CFGDEFINES              0
#define ADC_IPW_SW_PATCH_VERSION_CFGDEFINES              0

/*==================================================================================================
*                              DEFINES AND MACROS
==================================================================================================*/
#define ADC_IPW_INVALID_LOGICAL_UNIT_ID     (0xFFU)

#define ADC_IPW_INVALID_PHYSICAL_UNIT_ID    (0xFFU)

#define ADC_IPW_INVALID_DMA_CHANNEL_ID      (0xFFU)

#define ADC_IPW_INVALID_TRANSFER_TYPE       (0xFFU)

#define ADC_IPW_NUM_OF_GROUP_CHN                (3U)

/**
 * @brief          Max number of ADC SAR Hw units.
 */
#define ADC_IPW_MAX_HW_UNITS                    (2U)

/**
 * @brief   Define the number of maximum ADC hardware unit configured
 */
#define ADC_IPW_MAX_HW_UNITS_CFG                (2U)

/**
 * @brief          Max number of CTU Hw units.
 */
#define ADC_IPW_CTU_MAX_HW_UNITS                (1U)

/**
 * @brief   Define the number of maximum BCTU hardware unit configured
 */
#define ADC_IPW_CTU_MAX_HW_UNITS_CFG            (0U)

#define ADC_IPW_CTU_UNIT_0        (0U)


#define ADC_IPW_CTU_LOGICAL_ID_SHIFT            (28UL)
#define ADC_IPW_CTU_LOGICAL_ID_MASK             (((1UL << ADC_IPW_CTU_MAX_HW_UNITS) - 1UL) << ADC_IPW_CTU_LOGICAL_ID_SHIFT)
#define ADC_IPW_CTU_NOTIF_CTU_LOGICAL_0        ((0U) << ADC_IPW_CTU_LOGICAL_ID_SHIFT)


/**
* @brief           Bctu trigger mode is supported.
*/
#define ADC_IPW_CTU_TRIGGER_MODE_SUPPORTED      (STD_ON)

/**
* @brief           PDB available/unavailable (STD_ON/STD_OFF).
*/
#define ADC_IPW_PDB_AVAILABLE                   (STD_OFF)

/**
* @brief           BCTU available/unavailable (STD_ON/STD_OFF).
*/
#define ADC_IPW_BCTU_AVAILABLE                  (STD_ON)

/**
* @brief           CTU available/unavailable (STD_ON/STD_OFF).
*/
#define ADC_IPW_CTU_AVAILABLE                   (STD_OFF)

/**
* @brief           Define the number of maximum channels
*/
#define ADC_IPW_MAXIMUM_HW_CHANNELS             (66U)

/**
* @brief           Maximum CTU event configuration.
*/
#define ADC_IPW_MAX_CTU_TRIG_SOURCE_ID      (47U)
#define ADC_IPW_EXT_TRG_SRC                     (48U) /* Normal and injected external trigger */
#define ADC_IPW_AUX_EXT_TRG_SRC                 (49U) /* Auxiliary normal external trigger */

/**
* @brief           ADC hardware is supported CALSTAT register
*/
#define ADC_IPW_CALSTAT_AVAILABLE               (STD_OFF)

/**
* @brief          Definitions used for extracting the CTU Logical Unit Id in symbolic name having uint16 type
*/
#define ADC_IPW_CTU_LOGICAL_ID_MASK_U16         (0xFF00U)
#define ADC_IPW_CTU_LOGICAL_ID_SHIFT_U16        (8U)


/**
* @brief          Mapping between ADC Physical Id and CTU Physical Id.
*/
#define ADC_IPW_ADC_TO_CTU_MAPPING_ARRAY        { 0U, 0U }


/**
* @brief          Offset for ADC index and BCTU register's bitfield when using BCTU
*/
#define ADC_IPW_ADC_INDEX_OFFSET_BITFIELD_ARRAY        {0U}


/**
* @brief           SDADC is used (STD_ON/STD_OFF).
*/
#define ADC_IPW_SDADC_IS_USED                   (STD_OFF)



#ifdef __cplusplus
}
#endif

/** @} */

#endif /* ADC_IPW_CFGDEFINES_H */
