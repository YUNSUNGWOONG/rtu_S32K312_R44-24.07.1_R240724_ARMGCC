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
**  SRC-MODULE: IoHwAb_Version.c                                              **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR IOHWAB                                                **
**                                                                            **
**  PURPOSE   : APIs implementation for IoHwAb module                         **
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
** 1.6.4     15-Dec-2023  YongEun.Lee       #CP44-3041                        **
** 1.3.0.1   30-Jun-2022  KhaLN1            #CP44-365                         **
** 1.3.0     16-Mar-2022  PhucNHM           R44-Redmine #24320                **
** 1.2.0     18-Nov-2021  PhucNHM           R44-Redmine #18098                **
** 1.1.0     15-Jul-2021  YangJin.Kim       R44-Redmine #18100                **
** 1.0.0     04-Dec-2020  YangJin.Kim       R40-Redmine #26992                **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "IoHwAb_Version.h"

#if (IOHWAB_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"
#endif

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/* AUTOSAR specification version information */
#define IOHWAB_VERSION_C_AR_RELEASE_MAJOR_VERSION       4
#define IOHWAB_VERSION_C_AR_RELEASE_MINOR_VERSION       4
#define IOHWAB_VERSION_C_AR_RELEASE_REVISION_VERSION    0

/* FILE VERSION INFORMATION */
#define IOHWAB_VERSION_C_SW_MAJOR_VERSION     (IOHWAB_VERSION_SW_MAJOR_VERSION)
#define IOHWAB_VERSION_C_SW_MINOR_VERSION     (IOHWAB_VERSION_SW_MINOR_VERSION)
#define IOHWAB_VERSION_C_SW_PATCH_VERSION     (IOHWAB_VERSION_SW_PATCH_VERSION)

/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/

#if (IOHWAB_AR_RELEASE_MAJOR_VERSION != \
  IOHWAB_VERSION_C_AR_RELEASE_MAJOR_VERSION)
  #error "IoHwAb_Version.c : Mismatch in Specification Major Version"
#endif

#if (IOHWAB_AR_RELEASE_MINOR_VERSION != \
  IOHWAB_VERSION_C_AR_RELEASE_MINOR_VERSION)
  #error "IoHwAb_Version.c : Mismatch in Specification Minor Version"
#endif

#if (IOHWAB_AR_RELEASE_REVISION_VERSION != \
  IOHWAB_VERSION_C_AR_RELEASE_REVISION_VERSION)
  #error "IoHwAb_Version.c : Mismatch in Specification Patch Version"
#endif

#if (IOHWAB_SW_MAJOR_VERSION != IOHWAB_VERSION_C_SW_MAJOR_VERSION)
  #error "IoHwAb_Version.c : Mismatch in Major Version"
#endif

#if (IOHWAB_SW_MINOR_VERSION != IOHWAB_VERSION_C_SW_MINOR_VERSION)
  #error "IoHwAb_Version.c : Mismatch in Minor Version"
#endif

#if (IOHWAB_SW_PATCH_VERSION != IOHWAB_VERSION_C_SW_PATCH_VERSION)
  #error "IoHwAb_Version.c : Mismatch in Patch Version"
#endif

#if ((IOHWAB_USE_DIG_DIR == STD_ON) || (IOHWAB_USE_DIG_IN == STD_ON) \
  || (IOHWAB_USE_DIG_OUT == STD_ON))
#if (PORT_AR_RELEASE_MAJOR_VERSION != IOHWAB_PORT_AR_RELEASE_MAJOR_VERSION)
  #error "Port.h : Mismatch in Specification Major Version"
#endif

#if ((PORT_AR_RELEASE_MINOR_VERSION != IOHWAB_PORT_AR_RELEASE_MINOR_VERSION) && \
    ((PORT_AR_RELEASE_MINOR_VERSION < IOHWAB_PORT_AR_RELEASE_MINOR_VERSION_R42) || \
     (PORT_AR_RELEASE_MINOR_VERSION > IOHWAB_PORT_AR_RELEASE_MINOR_VERSION_R47)))
  #error "Port.h : Mismatch in Specification Minor Version"
#endif

#if (DIO_AR_RELEASE_MAJOR_VERSION != IOHWAB_DIO_AR_RELEASE_MAJOR_VERSION)
  #error "Dio.h : Mismatch in Specification Major Version"
#endif

#if ((DIO_AR_RELEASE_MINOR_VERSION != IOHWAB_DIO_AR_RELEASE_MINOR_VERSION) && \
    ((DIO_AR_RELEASE_MINOR_VERSION < IOHWAB_DIO_AR_RELEASE_MINOR_VERSION_R42) || \
     (DIO_AR_RELEASE_MINOR_VERSION > IOHWAB_DIO_AR_RELEASE_MINOR_VERSION_R47)))
  #error "Dio.h : Mismatch in Specification Minor Version"
#endif
#endif /* ((IOHWAB_USE_DIG_DIR == STD_ON) || (IOHWAB_USE_DIG_IN == STD_ON) \
  || (IOHWAB_USE_DIG_OUT == STD_ON)) */

#if ((IOHWAB_USE_ANA_IN_DIR == STD_ON) || (IOHWAB_USE_ANA_IN == STD_ON))
#if (ADC_AR_RELEASE_MAJOR_VERSION != IOHWAB_ADC_AR_RELEASE_MAJOR_VERSION)
  #error "Adc.h : Mismatch in Specification Major Version"
#endif

#if ((ADC_AR_RELEASE_MINOR_VERSION != IOHWAB_ADC_AR_RELEASE_MINOR_VERSION) && \
    ((ADC_AR_RELEASE_MINOR_VERSION < IOHWAB_ADC_AR_RELEASE_MINOR_VERSION_R42) || \
     (ADC_AR_RELEASE_MINOR_VERSION > IOHWAB_ADC_AR_RELEASE_MINOR_VERSION_R47)))
  #error "Adc.h : Mismatch in Specification Minor Version"
#endif
#endif /* ((IOHWAB_USE_ANA_IN_DIR == STD_ON) || (IOHWAB_USE_ANA_IN == STD_ON))*/

#if ((IOHWAB_USE_MC33972 == STD_ON) || (IOHWAB_USE_L9826 == STD_ON))
#if (SPI_AR_RELEASE_MAJOR_VERSION != IOHWAB_SPI_AR_RELEASE_MAJOR_VERSION)
  #error "Spi.h : Mismatch in Specification Major Version"
#endif

#if ((SPI_AR_RELEASE_MINOR_VERSION != IOHWAB_SPI_AR_RELEASE_MINOR_VERSION) && \
    ((SPI_AR_RELEASE_MINOR_VERSION < IOHWAB_SPI_AR_RELEASE_MINOR_VERSION_R42) || \
     (SPI_AR_RELEASE_MINOR_VERSION > IOHWAB_SPI_AR_RELEASE_MINOR_VERSION_R47)))
  #error "Spi.h : Mismatch in Specification Minor Version"
#endif
#endif /* ((IOHWAB_USE_MC33972 == STD_ON) || (IOHWAB_USE_L9826 == STD_ON))*/

#if ((IOHWAB_USE_ICU == STD_ON) || (IOHWAB_MC33972_EXTINT == STD_ON))
#if (ICU_AR_RELEASE_MAJOR_VERSION != IOHWAB_ICU_AR_RELEASE_MAJOR_VERSION)
  #error "Icu.h : Mismatch in Specification Major Version"
#endif

#if ((ICU_AR_RELEASE_MINOR_VERSION != IOHWAB_ICU_AR_RELEASE_MINOR_VERSION) && \
    ((ICU_AR_RELEASE_MINOR_VERSION < IOHWAB_ICU_AR_RELEASE_MINOR_VERSION_R42) || \
     (ICU_AR_RELEASE_MINOR_VERSION > IOHWAB_ICU_AR_RELEASE_MINOR_VERSION_R47)))
  #error "Icu.h : Mismatch in Specification Minor Version"
#endif
#endif /* ((IOHWAB_USE_ICU == STD_ON) || (IOHWAB_MC33972_EXTINT == STD_ON))*/

#if (IOHWAB_USE_GPT == STD_ON)
#if (GPT_AR_RELEASE_MAJOR_VERSION != IOHWAB_GPT_AR_RELEASE_MAJOR_VERSION)
  #error "Gpt.h : Mismatch in Specification Major Version"
#endif

#if ((GPT_AR_RELEASE_MINOR_VERSION != IOHWAB_GPT_AR_RELEASE_MINOR_VERSION) && \
    ((GPT_AR_RELEASE_MINOR_VERSION < IOHWAB_GPT_AR_RELEASE_MINOR_VERSION_R42) || \
     (GPT_AR_RELEASE_MINOR_VERSION > IOHWAB_GPT_AR_RELEASE_MINOR_VERSION_R47)))
  #error "Gpt.h : Mismatch in Specification Minor Version"
#endif
#endif /* (IOHWAB_USE_GPT == STD_ON) */

#if (IOHWAB_USE_PWM == STD_ON)
#if (PWM_AR_RELEASE_MAJOR_VERSION != IOHWAB_PWM_AR_RELEASE_MAJOR_VERSION)
  #error "Pwm.h : Mismatch in Specification Major Version"
#endif

#if ((PWM_AR_RELEASE_MINOR_VERSION != IOHWAB_PWM_AR_RELEASE_MINOR_VERSION) && \
    ((PWM_AR_RELEASE_MINOR_VERSION < IOHWAB_PWM_AR_RELEASE_MINOR_VERSION_R42) || \
     (PWM_AR_RELEASE_MINOR_VERSION > IOHWAB_PWM_AR_RELEASE_MINOR_VERSION_R47)))
  #error "Pwm.h : Mismatch in Specification Minor Version"
#endif
#endif /* (IOHWAB_USE_PWM == STD_ON) */

#if (IOHWAB_USE_OCU == STD_ON)
#if (OCU_AR_RELEASE_MAJOR_VERSION != IOHWAB_OCU_AR_RELEASE_MAJOR_VERSION)
  #error "Ocu.h : Mismatch in Specification Major Version"
#endif

#if ((OCU_AR_RELEASE_MINOR_VERSION != IOHWAB_OCU_AR_RELEASE_MINOR_VERSION) && \
    ((OCU_AR_RELEASE_MINOR_VERSION < IOHWAB_OCU_AR_RELEASE_MINOR_VERSION_R42) || \
     (OCU_AR_RELEASE_MINOR_VERSION > IOHWAB_OCU_AR_RELEASE_MINOR_VERSION_R47)))
  #error "Ocu.h : Mismatch in Specification Minor Version"
#endif
#endif /* (IOHWAB_USE_OCU == STD_ON) */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
