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
**  SRC-MODULE: LinTrcv_Version.h                                             **
**                                                                            **
**  TARGET    : MC33661                                                       **
**                                                                            **
**  PRODUCT   : AUTOSAR LIN Transceiver Driver                                **
**                                                                            **
**  PURPOSE   : Version check of DEPENDENT modules DIO, EcuM, DET             **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: yes                                          **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision       Date                  By         Description                **
********************************************************************************
** 1.0.6          14-Mar-2024           YB Song    #CP44-3713                 **
** 1.0.2          17-May-2022           DuyNHP2    R44-Redmine #20124 #27289  **
** 1.0.0          22-Dec-2020           SJ Kim     Initial Version            **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "LinTrcv_Version.h"                 /* LinTrcv Version header file */
#include "Dio.h"                             /* Dio header file */

#if (STD_ON == LINTRCV_DEV_ERROR_DETECT)
#include "Det.h"                             /* Det header file */
#endif
#if (STD_ON == LINTRCV_TIMER_TYPE)
#include "Tm.h"                              /* Tm header file */
#endif

/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/
/* LinTrcv AUTOSAR Version check */
#if ((LINTRCV_AR_RELEASE_MAJOR_VERSION != \
                                  LINTRCV_VERSION_AR_RELEASE_MAJOR_VERSION) || \
  (LINTRCV_AR_RELEASE_MINOR_VERSION != \
                                  LINTRCV_VERSION_AR_RELEASE_MINOR_VERSION) || \
  (LINTRCV_AR_RELEASE_REVISION_VERSION != \
                                   LINTRCV_VERSION_AR_RELEASE_REVISION_VERSION))
  #error "LinTrcv : Mismatch AUTOSAR Version in LinTrcv_Version.c"
#endif

/* LinTrcv Software Version check */
#if ((LINTRCV_SW_MAJOR_VERSION != LINTRCV_VERSION_SW_MAJOR_VERSION) || \
     (LINTRCV_SW_MINOR_VERSION != LINTRCV_VERSION_SW_MINOR_VERSION) || \
     (LINTRCV_SW_PATCH_VERSION != LINTRCV_VERSION_SW_PATCH_VERSION))
  #error "LinTrcv : Mismatch Sofware Version in LinTrcv_Version.c"
#endif

/* Tm version check */
#if (STD_ON == LINTRCV_TIMER_TYPE)
  #if ((defined TM_AR_RELEASE_MAJOR_VERSION) && \
                        (defined TM_AR_RELEASE_MINOR_VERSION))
    #if ((TM_AR_RELEASE_MAJOR_VERSION != LINTRCV_TM_AR_RELEASE_MAJOR_VERSION) || \
       (TM_AR_RELEASE_MINOR_VERSION != LINTRCV_TM_AR_RELEASE_MINOR_VERSION))
    #error "LinTrcv : Mismatch AUTOSAR Version with Tm.h"
    #endif
  #endif
#endif

/* DIO version check */
#if ((defined DIO_AR_RELEASE_MAJOR_VERSION) && \
                                         (defined DIO_AR_RELEASE_MINOR_VERSION))
  #if ((DIO_AR_RELEASE_MAJOR_VERSION != LINTRCV_DIO_AR_RELEASE_MAJOR_VERSION) || \
      ((DIO_AR_RELEASE_MINOR_VERSION != LINTRCV_DIO_AR_RELEASE_MINOR_VERSION_1) && \
       (DIO_AR_RELEASE_MINOR_VERSION != LINTRCV_DIO_AR_RELEASE_MINOR_VERSION_2) && \
       (DIO_AR_RELEASE_MINOR_VERSION != LINTRCV_DIO_AR_RELEASE_MINOR_VERSION_3)))
    #error "LinTrcv : Mismatch AUTOSAR Version with Dio.h"
  #endif
#endif

/* DET version check */
#if (STD_ON == LINTRCV_DEV_ERROR_DETECT)
  #if ((defined DET_AR_RELEASE_MAJOR_VERSION) && \
                       (defined DET_AR_RELEASE_MINOR_VERSION))
    #if ((DET_AR_RELEASE_MAJOR_VERSION != LINTRCV_DET_AR_RELEASE_MAJOR_VERSION)||\
      (DET_AR_RELEASE_MINOR_VERSION != LINTRCV_DET_AR_RELEASE_MINOR_VERSION))
        #error "LinTrcv : Mismatch AUTOSAR Version with Det.h"
    #endif
  #endif
#endif

/* EcuM version check */
#if (STD_ON == LINTRCV_WAKEUP_SUPPORT)
  #if ((defined ECUM_AR_RELEASE_MAJOR_VERSION) && \
                      (defined ECUM_AR_RELEASE_MINOR_VERSION))
    #if ((ECUM_AR_RELEASE_MAJOR_VERSION != LINTRCV_ECUM_AR_RELEASE_MAJOR_VERSION)||\
      (ECUM_AR_RELEASE_MINOR_VERSION != LINTRCV_ECUM_AR_RELEASE_MINOR_VERSION))
        #error "LinTrcv : Mismatch AUTOSAR Version with EcuM.h"
    #endif
  #endif
#endif

/* LinIf version check */
#if (STD_ON == LINTRCV_WAKEUP_SUPPORT)
  #if ((defined LINIF_AR_RELEASE_MAJOR_VERSION) && \
                      (defined LINIF_AR_RELEASE_MINOR_VERSION))
    #if ((LINIF_AR_RELEASE_MAJOR_VERSION != LINTRCV_LINIF_AR_RELEASE_MAJOR_VERSION)||\
      (LINIF_AR_RELEASE_MINOR_VERSION != LINTRCV_LINIF_AR_RELEASE_MINOR_VERSION))
        #error "LinTrcv : Mismatch AUTOSAR Version with LinIf.h"
    #endif
  #endif
#endif

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
