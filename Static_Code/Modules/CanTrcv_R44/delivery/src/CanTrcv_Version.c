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
**  SRC-MODULE: CanTrcv_Version.c                                             **
**                                                                            **
**  TARGET    : General CAN Transceiver                                       **
**                                                                            **
**  PRODUCT   : AUTOSAR CAN Transceiver Driver Module                         **
**                                                                            **
**  PURPOSE   : Provision of Version information                              **
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
** 1.0.10         02-Jun-2023         HieuTM8          #CP44-2209             **
** 1.0.5          06-Jul-2022         HjSeong          #CP44-505              **
** 1.0.4          12-May-2022         HieuTM8          Redmine #27274         **
** 1.0.1          14-Sep-2021         DuyNHP2          Redmine #20148         **
** 1.0.0          15-Dec-2020         JsLim            Initial version        **
*******************************************************************************/


/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* @Trace: CanTrcv_SUD_FILE_001 */
#include "CanTrcv_Version.h"     /* Module version check header file */
#include "CanIf.h"               /* CAN Interface module header file */
#if(STD_OFF==CANTRCV_SUPPORT_AR403)
#if (STD_ON == CANTRCV_TIMER_1US16BIT)
#include "Tm.h"                  /* Time Service module header file */
#endif /* (STD_ON == CANTRCV_TIMER_1US16BIT) */
#endif /*(STD_OFF==CANTRCV_SUPPORT_AR403)*/



/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/
/* Interal checking for AR Version */
#if ((CANTRCV_AR_RELEASE_MAJOR_VERSION != \
                                  CANTRCV_VERSION_AR_RELEASE_MAJOR_VERSION) || \
  ((CANTRCV_AR_RELEASE_MINOR_VERSION != \
                                  CANTRCV_VERSION_AR_RELEASE_MINOR_VERSION)  && \
   (CANTRCV_AR_RELEASE_MINOR_VERSION != \
                                  CANTRCV_VERSION_AR_RELEASE_MINOR_VERSION_ZERO)) || \
  ((CANTRCV_AR_RELEASE_REVISION_VERSION != \
                                   CANTRCV_VERSION_AR_RELEASE_REVISION_VERSION) &&  \
  (CANTRCV_AR_RELEASE_REVISION_VERSION != \
                                   CANTRCV_VERSION_AR_RELEASE_REVISION_VERSION_THREE)))
  #error "CanTrcv : Mismatch AUTOSAR Version in CanTrcv_Version.c"
#endif

/* Interal checking for SW Version */
#if ((CANTRCV_SW_MAJOR_VERSION != CANTRCV_VERSION_SW_MAJOR_VERSION) || \
     (CANTRCV_SW_MINOR_VERSION != CANTRCV_VERSION_SW_MINOR_VERSION) || \
     (CANTRCV_SW_PATCH_VERSION != CANTRCV_VERSION_SW_PATCH_VERSION))
  #error "CanTrcv : Mismatch Sofware Version in CanTrcv_Version.c"
#endif

/* Inter Module check for Det.h */
#if ((defined DET_AR_RELEASE_MAJOR_VERSION) && \
                                         (defined DET_AR_RELEASE_MINOR_VERSION))
  #if ((DET_AR_RELEASE_MAJOR_VERSION != CANTRCV_DET_AR_MAJOR_VERSION) || \
       ((DET_AR_RELEASE_MINOR_VERSION != CANTRCV_DET_AR_MINOR_VERSION) && \
        (DET_AR_RELEASE_MINOR_VERSION != CANTRCV_DET_AR_MINOR_VERSION_ZERO)))
    #error "CanTrcv : Mismatch AUTOSAR Version with Det.h"
  #endif
#endif

#if(STD_OFF==CANTRCV_SUPPORT_AR403)
/* Inter Module check for Dem.h */
#if ((defined DEM_AR_RELEASE_MAJOR_VERSION) && \
                                         (defined DEM_AR_RELEASE_MINOR_VERSION))
  #if ((DEM_AR_RELEASE_MAJOR_VERSION != CANTRCV_DEM_AR_MAJOR_VERSION) || \
       (DEM_AR_RELEASE_MINOR_VERSION != CANTRCV_DEM_AR_MINOR_VERSION))
    #error "CanTrcv : Mismatch AUTOSAR Version with Dem.h"
  #endif
#endif
#endif

/* Inter Module check for CanIf.h */
#if ((defined CANIF_AR_RELEASE_MAJOR_VERSION) && \
                                       (defined CANIF_AR_RELEASE_MINOR_VERSION))
  #if ((CANIF_AR_RELEASE_MAJOR_VERSION != CANTRCV_CANIF_AR_MAJOR_VERSION) || \
       ((CANIF_AR_RELEASE_MINOR_VERSION != CANTRCV_CANIF_AR_MINOR_VERSION) && \
        (CANIF_AR_RELEASE_MINOR_VERSION != CANTRCV_CANIF_AR_MINOR_VERSION_ZERO)))
    #error "CanTrcv : Mismatch AUTOSAR Version with CanIf.h"
  #endif
#endif

#if(STD_OFF==CANTRCV_SUPPORT_AR403)
#if (STD_ON == CANTRCV_TIMER_1US16BIT)
/* Inter Module check for Tm.h */
#if ((defined TM_AR_RELEASE_MAJOR_VERSION) && \
                                          (defined TM_AR_RELEASE_MINOR_VERSION))
  #if ((TM_AR_RELEASE_MAJOR_VERSION != CANTRCV_TM_AR_MAJOR_VERSION) || \
       (TM_AR_RELEASE_MINOR_VERSION != CANTRCV_TM_AR_MINOR_VERSION))
    #error "CanTrcv : Mismatch AUTOSAR Version with Tm.h"
  #endif
#endif
#endif /* (STD_ON == CANTRCV_TIMER_1US16BIT) */
#endif

/* Inter Module check for Dio.h */
#if ((defined DIO_AR_RELEASE_MAJOR_VERSION) && \
                                         (defined DIO_AR_RELEASE_MINOR_VERSION))
  #if ((DIO_AR_RELEASE_MAJOR_VERSION != CANTRCV_DIO_AR_MAJOR_VERSION) || \
       ((DIO_AR_RELEASE_MINOR_VERSION != CANTRCV_DIO_AR_MINOR_VERSION_ZERO) && \
        (DIO_AR_RELEASE_MINOR_VERSION != CANTRCV_DIO_AR_MINOR_VERSION_TWO) && \
        (DIO_AR_RELEASE_MINOR_VERSION != CANTRCV_DIO_AR_MINOR_VERSION_FOUR) && \
        (DIO_AR_RELEASE_MINOR_VERSION != CANTRCV_DIO_AR_MINOR_VERSION_THREE)))
    #error "CanTrcv : Mismatch AUTOSAR Version with Dio.h"
  #endif
#endif

#if (STD_ON == CANTRCV_SPI_SUPPORTED)
/* Inter Module check for Spi.h */
#if ((defined SPI_AR_RELEASE_MAJOR_VERSION) && \
                                         (defined SPI_AR_RELEASE_MINOR_VERSION))
  #if ((SPI_AR_RELEASE_MAJOR_VERSION != CANTRCV_SPI_AR_MAJOR_VERSION) || \
       ((SPI_AR_RELEASE_MINOR_VERSION != CANTRCV_SPI_AR_MINOR_VERSION_ZERO) && \
        (SPI_AR_RELEASE_MINOR_VERSION != CANTRCV_SPI_AR_MINOR_VERSION_TWO) && \
        (SPI_AR_RELEASE_MINOR_VERSION != CANTRCV_SPI_AR_MINOR_VERSION_FOUR)))
    #error "CanTrcv : Mismatch AUTOSAR Version with Spi.h"
  #endif
#endif
#endif /* (STD_ON == CANTRCV_SPI_SUPPORTED) */

#if(STD_OFF==CANTRCV_SUPPORT_AR403)
#if (STD_ON == CANTRCV_ICU_CHANNEL_USED)
/* Inter Module check for Icu.h */
#if ((defined ICU_AR_RELEASE_MAJOR_VERSION) && \
                                         (defined ICU_AR_RELEASE_MINOR_VERSION))
  #if ((ICU_AR_RELEASE_MAJOR_VERSION != CANTRCV_ICU_AR_MAJOR_VERSION) || \
       (ICU_AR_RELEASE_MINOR_VERSION != CANTRCV_ICU_AR_MINOR_VERSION))
    #error "CanTrcv : Mismatch AUTOSAR Version with Icu.h"
  #endif
#endif
#endif /* (STD_ON == CANTRCV_ICU_CHANNEL_USED) */
#endif /*(STD_OFF==CANTRCV_SUPPORT_AR403)*/

#if ((STD_ON == CANTRCV_HW_PN_SUPPORTED) || \
  (STD_ON == CANTRCV_WAKEUP_SUPPORTED))
/* Inter Module check for EcuM.h */
#if ((defined ECUM_AR_RELEASE_MAJOR_VERSION) && \
                                        (defined ECUM_AR_RELEASE_MINOR_VERSION))
  #if ((ECUM_AR_RELEASE_MAJOR_VERSION != CANTRCV_ECUM_AR_MAJOR_VERSION) || \
       ((ECUM_AR_RELEASE_MINOR_VERSION != CANTRCV_ECUM_AR_MINOR_VERSION) && \
        (ECUM_AR_RELEASE_MINOR_VERSION != CANTRCV_ECUM_AR_MINOR_VERSION_ZERO)))
    #error "CanTrcv : Mismatch AUTOSAR Version with EcuM.h"
  #endif
#endif
#endif /* ((STD_ON == CANTRCV_HW_PN_SUPPORTED) || \
  (STD_ON == CANTRCV_WAKEUP_SUPPORTED)) */

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
