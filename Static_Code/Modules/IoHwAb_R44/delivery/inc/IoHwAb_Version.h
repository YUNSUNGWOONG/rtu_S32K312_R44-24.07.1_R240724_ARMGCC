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
**  SRC-MODULE: IoHwAb_Version.h                                              **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR IOHWAB                                                **
**                                                                            **
**  PURPOSE   : C header for IoHwAb_Version                                   **
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
** 1.7.1     10-May-2024  YongEun.Lee       #CP44-7556                        **
** 1.7.0     05-Mar-2024  YongEun.Lee       #CP44-3784                        **
** 1.6.4     15-Dec-2023  YongEun.Lee       #CP44-3041                        **
** 1.6.3     07-Sep-2023  KhaLN1            #CP44-2913, #CP44-2914            **
** 1.6.2     15-Aug-2023  KhaLN1            #CP44-2683, #CP44-2684            **
** 1.6.1     17-Jul-2023  KhaLN1            #CP44-2582                        **
** 1.6.0     30-Jun-2023  KhaLN1            #CP44-2241                        **
** 1.5.0     12-Jun-2023  KhaLN1            #CP44-2240                        **
** 1.4.5     18-May-2023  KhaLN1            #CP44-2223                        **
** 1.4.4     30-Dec-2022  KhaLN1            #CP44-1449                        **
** 1.4.3     05-Dec-2022  KhaLN1            #CP44-1247                        **
** 1.4.2     09-Nov-2022  KhaLN1            #CP44-966                         **
** 1.4.1     27-Sep-2022  KhaLN1            #CP44-840                         **
** 1.4.0     22-Aug-2022  KhaLN1            #CP44-485                         **
** 1.3.2     17-Aug-2022  KhaLN1            #CP44-731                         **
** 1.3.0.1   30-Jun-2022  KhaLN1            #CP44-365                         **
** 1.3.0     16-Mar-2022  PhucNHM           R44-Redmine #24320                **
** 1.2.0     18-Nov-2021  PhucNHM           R44-Redmine #18098                **
** 1.1.0     15-Jul-2021  YangJin.Kim       R44-Redmine #18100                **
** 1.0.0     04-Dec-2020  YangJin.Kim       R40-Redmine #26992                **
*******************************************************************************/

#ifndef IOHWAB_VERSION_H
#define IOHWAB_VERSION_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "IoHwAb_Cfg.h"

#if (defined(IOHWAB_MCAL_CYPRESS_S6J32XX) || defined(IOHWAB_MCAL_CYPRESS_S6J33XX ))
#include "Dio_Version.h"
#include "Port_Version.h"
#include "Icu_Version.h"
#include "Gpt_Version.h"
#include "Pwm_Version.h"
#endif
/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/* AUTOSAR Specification Version Information */
#define IOHWAB_VERSION_AR_RELEASE_MAJOR_VERSION     4u
#define IOHWAB_VERSION_AR_RELEASE_MINOR_VERSION     4u
#define IOHWAB_VERSION_AR_RELEASE_REVISION_VERSION  0u

/* Software Version Information */
#define IOHWAB_VERSION_SW_MAJOR_VERSION             1u
#define IOHWAB_VERSION_SW_MINOR_VERSION             7u
#define IOHWAB_VERSION_SW_PATCH_VERSION             1u

/* Minor Version Information of ADC module */
#define IOHWAB_ADC_AR_RELEASE_MINOR_VERSION_R42 2u
#define IOHWAB_ADC_AR_RELEASE_MINOR_VERSION_R47 7u

/* Minor Version Information of SPI module */
#define IOHWAB_SPI_AR_RELEASE_MINOR_VERSION_R42 2u
#define IOHWAB_SPI_AR_RELEASE_MINOR_VERSION_R47 7u

/* Minor Version Information of DIO module */
#define IOHWAB_DIO_AR_RELEASE_MINOR_VERSION_R42 2u
#define IOHWAB_DIO_AR_RELEASE_MINOR_VERSION_R47 7u

/* Minor Version Information of PWM module */
#define IOHWAB_PWM_AR_RELEASE_MINOR_VERSION_R42 2u
#define IOHWAB_PWM_AR_RELEASE_MINOR_VERSION_R47 7u

/* Minor Version Information of PORT module */
#define IOHWAB_PORT_AR_RELEASE_MINOR_VERSION_R42 2u
#define IOHWAB_PORT_AR_RELEASE_MINOR_VERSION_R47 7u

/* Minor Version Information of ICU module */
#define IOHWAB_ICU_AR_RELEASE_MINOR_VERSION_R42 2u
#define IOHWAB_ICU_AR_RELEASE_MINOR_VERSION_R47 7u

/* Minor Version Information of GPT module */
#define IOHWAB_GPT_AR_RELEASE_MINOR_VERSION_R42 2u
#define IOHWAB_GPT_AR_RELEASE_MINOR_VERSION_R47 7u

/* Minor Version Information of OCU module */
#define IOHWAB_OCU_AR_RELEASE_MINOR_VERSION_R42 2u
#define IOHWAB_OCU_AR_RELEASE_MINOR_VERSION_R47 7u

/* Included Files AUTOSAR Specification Version */

#if (defined(IOHWAB_MCAL_INFINEON_TC33X)) || (defined(IOHWAB_MCAL_INFINEON_TC36X)) \
 || (defined(IOHWAB_MCAL_INFINEON_TC37X)) || (defined(IOHWAB_MCAL_INFINEON_TC38X)) \
 || (defined(IOHWAB_MCAL_INFINEON_TC39X))

#define IOHWAB_ADC_AR_RELEASE_MAJOR_VERSION     4u
#define IOHWAB_ADC_AR_RELEASE_MINOR_VERSION     2u

#define IOHWAB_SPI_AR_RELEASE_MAJOR_VERSION     4u
#define IOHWAB_SPI_AR_RELEASE_MINOR_VERSION     2u

#define IOHWAB_DIO_AR_RELEASE_MAJOR_VERSION     4u
#define IOHWAB_DIO_AR_RELEASE_MINOR_VERSION     2u

#define IOHWAB_PWM_AR_RELEASE_MAJOR_VERSION     4u
#define IOHWAB_PWM_AR_RELEASE_MINOR_VERSION     2u

#define IOHWAB_PORT_AR_RELEASE_MAJOR_VERSION    4u
#define IOHWAB_PORT_AR_RELEASE_MINOR_VERSION    2u

#define IOHWAB_ICU_AR_RELEASE_MAJOR_VERSION     4u
#define IOHWAB_ICU_AR_RELEASE_MINOR_VERSION     2u

#define IOHWAB_GPT_AR_RELEASE_MAJOR_VERSION     4u
#define IOHWAB_GPT_AR_RELEASE_MINOR_VERSION     2u

#define IOHWAB_OCU_AR_RELEASE_MAJOR_VERSION     4u
#define IOHWAB_OCU_AR_RELEASE_MINOR_VERSION     2u

#elif defined (IOHWAB_MCAL_NXP_S32G2X)

#define IOHWAB_ADC_AR_RELEASE_MAJOR_VERSION     4u
#define IOHWAB_ADC_AR_RELEASE_MINOR_VERSION     4u

#define IOHWAB_SPI_AR_RELEASE_MAJOR_VERSION     4u
#define IOHWAB_SPI_AR_RELEASE_MINOR_VERSION     4u

#define IOHWAB_DIO_AR_RELEASE_MAJOR_VERSION     4u
#define IOHWAB_DIO_AR_RELEASE_MINOR_VERSION     4u

#define IOHWAB_PWM_AR_RELEASE_MAJOR_VERSION     4u
#define IOHWAB_PWM_AR_RELEASE_MINOR_VERSION     4u

#define IOHWAB_PORT_AR_RELEASE_MAJOR_VERSION    4u
#define IOHWAB_PORT_AR_RELEASE_MINOR_VERSION    4u

#define IOHWAB_ICU_AR_RELEASE_MAJOR_VERSION     4u
#define IOHWAB_ICU_AR_RELEASE_MINOR_VERSION     4u

#define IOHWAB_GPT_AR_RELEASE_MAJOR_VERSION     4u
#define IOHWAB_GPT_AR_RELEASE_MINOR_VERSION     4u

#define IOHWAB_OCU_AR_RELEASE_MAJOR_VERSION     4u
#define IOHWAB_OCU_AR_RELEASE_MINOR_VERSION     4u

#elif (defined(IOHWAB_MCAL_NXP_S32K31X)) || (defined(IOHWAB_MCAL_NXP_S32K31X_3_0_0_P01_HF01))

#define IOHWAB_ADC_AR_RELEASE_MAJOR_VERSION     4u
#define IOHWAB_ADC_AR_RELEASE_MINOR_VERSION     7u

#define IOHWAB_SPI_AR_RELEASE_MAJOR_VERSION     4u
#define IOHWAB_SPI_AR_RELEASE_MINOR_VERSION     7u

#define IOHWAB_DIO_AR_RELEASE_MAJOR_VERSION     4u
#define IOHWAB_DIO_AR_RELEASE_MINOR_VERSION     7u

#define IOHWAB_PWM_AR_RELEASE_MAJOR_VERSION     4u
#define IOHWAB_PWM_AR_RELEASE_MINOR_VERSION     7u

#define IOHWAB_PORT_AR_RELEASE_MAJOR_VERSION    4u
#define IOHWAB_PORT_AR_RELEASE_MINOR_VERSION    7u

#define IOHWAB_ICU_AR_RELEASE_MAJOR_VERSION     4u
#define IOHWAB_ICU_AR_RELEASE_MINOR_VERSION     7u

#define IOHWAB_GPT_AR_RELEASE_MAJOR_VERSION     4u
#define IOHWAB_GPT_AR_RELEASE_MINOR_VERSION     7u

#define IOHWAB_OCU_AR_RELEASE_MAJOR_VERSION     4u
#define IOHWAB_OCU_AR_RELEASE_MINOR_VERSION     7u

#elif defined(IOHWAB_MCAL_NVIDIA_ORINX_FSI)

#define IOHWAB_PORT_AR_RELEASE_MAJOR_VERSION    4u
#define IOHWAB_PORT_AR_RELEASE_MINOR_VERSION    3u

#define IOHWAB_DIO_AR_RELEASE_MAJOR_VERSION     4u
#define IOHWAB_DIO_AR_RELEASE_MINOR_VERSION     3u

#define IOHWAB_GPT_AR_RELEASE_MAJOR_VERSION     4u
#define IOHWAB_GPT_AR_RELEASE_MINOR_VERSION     3u

#elif defined(IOHWAB_MCAL_CYPRESS_CYTXXX)

#define IOHWAB_ADC_AR_RELEASE_MAJOR_VERSION     4u
#define IOHWAB_ADC_AR_RELEASE_MINOR_VERSION     2u

#define IOHWAB_SPI_AR_RELEASE_MAJOR_VERSION     4u
#define IOHWAB_SPI_AR_RELEASE_MINOR_VERSION     2u

#define IOHWAB_DIO_AR_RELEASE_MAJOR_VERSION     4u
#define IOHWAB_DIO_AR_RELEASE_MINOR_VERSION     2u

#define IOHWAB_PWM_AR_RELEASE_MAJOR_VERSION     4u
#define IOHWAB_PWM_AR_RELEASE_MINOR_VERSION     2u

#define IOHWAB_PORT_AR_RELEASE_MAJOR_VERSION    4u
#define IOHWAB_PORT_AR_RELEASE_MINOR_VERSION    2u

#define IOHWAB_ICU_AR_RELEASE_MAJOR_VERSION     4u
#define IOHWAB_ICU_AR_RELEASE_MINOR_VERSION     2u

#define IOHWAB_GPT_AR_RELEASE_MAJOR_VERSION     4u
#define IOHWAB_GPT_AR_RELEASE_MINOR_VERSION     2u

#define IOHWAB_OCU_AR_RELEASE_MAJOR_VERSION     4u
#define IOHWAB_OCU_AR_RELEASE_MINOR_VERSION     2u

#elif defined(IOHWAB_MCAL_RENESAS_RH850U2A)

#define IOHWAB_ADC_AR_RELEASE_MAJOR_VERSION     4u
#define IOHWAB_ADC_AR_RELEASE_MINOR_VERSION     3u

#define IOHWAB_SPI_AR_RELEASE_MAJOR_VERSION     4u
#define IOHWAB_SPI_AR_RELEASE_MINOR_VERSION     3u

#define IOHWAB_DIO_AR_RELEASE_MAJOR_VERSION     4u
#define IOHWAB_DIO_AR_RELEASE_MINOR_VERSION     3u

#define IOHWAB_PWM_AR_RELEASE_MAJOR_VERSION     4u
#define IOHWAB_PWM_AR_RELEASE_MINOR_VERSION     3u

#define IOHWAB_PORT_AR_RELEASE_MAJOR_VERSION    4u
#define IOHWAB_PORT_AR_RELEASE_MINOR_VERSION    3u

#define IOHWAB_ICU_AR_RELEASE_MAJOR_VERSION     4u
#define IOHWAB_ICU_AR_RELEASE_MINOR_VERSION     3u

#define IOHWAB_GPT_AR_RELEASE_MAJOR_VERSION     4u
#define IOHWAB_GPT_AR_RELEASE_MINOR_VERSION     3u

#define IOHWAB_OCU_AR_RELEASE_MAJOR_VERSION     4u
#define IOHWAB_OCU_AR_RELEASE_MINOR_VERSION     3u

#else

#define IOHWAB_ADC_AR_RELEASE_MAJOR_VERSION     4u
#define IOHWAB_ADC_AR_RELEASE_MINOR_VERSION     0u

#define IOHWAB_SPI_AR_RELEASE_MAJOR_VERSION     4u
#define IOHWAB_SPI_AR_RELEASE_MINOR_VERSION     0u

#define IOHWAB_DIO_AR_RELEASE_MAJOR_VERSION     4u
#define IOHWAB_DIO_AR_RELEASE_MINOR_VERSION     0u

#define IOHWAB_PWM_AR_RELEASE_MAJOR_VERSION     4u
#define IOHWAB_PWM_AR_RELEASE_MINOR_VERSION     0u

#define IOHWAB_PORT_AR_RELEASE_MAJOR_VERSION    4u
#define IOHWAB_PORT_AR_RELEASE_MINOR_VERSION    0u

#define IOHWAB_ICU_AR_RELEASE_MAJOR_VERSION     4u
#define IOHWAB_ICU_AR_RELEASE_MINOR_VERSION     0u

#define IOHWAB_GPT_AR_RELEASE_MAJOR_VERSION     4u
#define IOHWAB_GPT_AR_RELEASE_MINOR_VERSION     0u

#define IOHWAB_OCU_AR_RELEASE_MAJOR_VERSION     4u
#define IOHWAB_OCU_AR_RELEASE_MINOR_VERSION     0u

#endif /* IOHWAB_MCAL_INFINEON_TC36X, IOHWAB_MCAL_INFINEON_TC37X, 
        * IOHWAB_MCAL_INFINEON_TC38X, IOHWAB_MCAL_INFINEON_TC39X */

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/

#endif /* IOHWAB_VERSION_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
