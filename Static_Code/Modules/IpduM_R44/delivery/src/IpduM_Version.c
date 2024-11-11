/*******************************************************************************
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  This source code is permitted to be used only in projects contracted      **
**  with Hyundai Autoever, and any other use is prohibited.                   **
**  If you use it for other purposes or change the source code,               **
**  you may take legal responsibility.                                        **
**  In this case, There is no warranty and technical support.                 **
**                                                                            **
**  SRC-MODULE: IpduM_Version.c                                               **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR IpduM module                                          **
**                                                                            **
**  PURPOSE   : This file provides Version Checks for the IpduM module        **
**              with it neighboring modules                                   **
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
** 1.0.6          27-Jan-2023         JW Oh            CP44-1590              **
** 1.0.2          27-Jun-2022         DuyNHP2          CP44-141               **
** 1.0.1          10-Mar-2022         DuyNHP2          R44-Redmine #24418     **
** 1.0.0          15-Dec-2020         JsLim            Initial Version        **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "IpduM_Version.h"

#if(IPDUM_ENABLE_MODULE == STD_ON)

#if (IPDUM_COM_SUPPORT_DIRECT == STD_ON)
#include "Com.h"
#endif

#if ((IPDUM_DEV_ERROR_DETECT == STD_ON) || \
     (IPDUM_TX_CONTAINER == STD_ON) || (IPDUM_RX_CONTAINER == STD_ON))
#include "Det.h"
#endif

#include "PduR_IpduM.h"
#include "SchM_IpduM.h"

/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/
/* Inter Module check for ComStack_Types.h */
#if ((defined COMSTACK_TYPES_AR_RELEASE_MAJOR_VERSION) && \
     (defined COMSTACK_TYPES_AR_RELEASE_MINOR_VERSION))
 #if ((COMSTACK_TYPES_AR_RELEASE_MAJOR_VERSION != IPDUM_COMSTACK_TYPES_AR_MAJOR_VERSION) || \
      (COMSTACK_TYPES_AR_RELEASE_MINOR_VERSION != IPDUM_COMSTACK_TYPES_AR_MINOR_VERSION))
 #error "IpduM : Mismatch AUTOSAR Version with ComStack_Types.h"
 #endif
#endif

/* Inter Module check for Com.h */
#if ((IPDUM_COM_SUPPORT_DIRECT == STD_ON) && \
     (defined COM_AR_RELEASE_MAJOR_VERSION) && \
     (defined COM_AR_RELEASE_MINOR_VERSION))
 #if ((COM_AR_RELEASE_MAJOR_VERSION != IPDUM_COM_AR_MAJOR_VERSION) || \
      (COM_AR_RELEASE_MINOR_VERSION != IPDUM_COM_AR_MINOR_VERSION))
 #error "IpduM : Mismatch AUTOSAR Version with Com.h"
 #endif
#endif /* (IPDUM_COM_SUPPORT_DIRECT == STD_ON) */

/* Inter Module check for Det.h */
#if (((IPDUM_DEV_ERROR_DETECT == STD_ON) || \
      (IPDUM_TX_CONTAINER == STD_ON) || (IPDUM_RX_CONTAINER == STD_ON)) && \
     (defined DET_AR_RELEASE_MAJOR_VERSION) && \
     (defined DET_AR_RELEASE_MINOR_VERSION))
 #if ((DET_AR_RELEASE_MAJOR_VERSION != IPDUM_DET_AR_MAJOR_VERSION) || \
      (DET_AR_RELEASE_MINOR_VERSION != IPDUM_DET_AR_MINOR_VERSION))
 #error "IpduM : Mismatch AUTOSAR Version with Det.h"
 #endif
#endif /* (IPDUM_DEV_ERROR_DETECT == STD_ON) */

/* Inter Module check for PduR_IpduM.h */
#if ((defined PDUR_IPDUM_AR_RELEASE_MAJOR_VERSION) && \
     (defined PDUR_IPDUM_AR_RELEASE_MINOR_VERSION))
 #if ((PDUR_IPDUM_AR_RELEASE_MAJOR_VERSION != IPDUM_PDUR_IPDUM_AR_MAJOR_VERSION) || \
      (PDUR_IPDUM_AR_RELEASE_MINOR_VERSION != IPDUM_PDUR_IPDUM_AR_MINOR_VERSION))
 #error "IpduM : Mismatch AUTOSAR Version with PduR_IpduM.h"
 #endif
#endif

/* Inter Module check for SchM_IpduM.h */
#if ((defined SCHM_IPDUM_AR_RELEASE_MAJOR_VERSION) && \
     (defined SCHM_IPDUM_AR_RELEASE_MINOR_VERSION))
 #if ((SCHM_IPDUM_AR_RELEASE_MAJOR_VERSION != IPDUM_SCHM_IPDUM_AR_MAJOR_VERSION) || \
      (SCHM_IPDUM_AR_RELEASE_MINOR_VERSION != IPDUM_SCHM_IPDUM_AR_MINOR_VERSION))
 #error "IpduM : Mismatch AUTOSAR Version with SchM_IpduM.h"
 #endif
#endif

#endif /* IPDUM_ENABLE_MODULE == STD_ON */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
