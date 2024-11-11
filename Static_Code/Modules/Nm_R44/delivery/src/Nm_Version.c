/* polyspace +1 MISRA2012:1.1 [Not a defect:Low] "This rule is manually checked and has no impact." */
/*******************************************************************************
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  This source code is permitted to be used only in projects contracted      **
**  with Hyundai Autoever, and any other use is prohibited.                   **
**  If you use it for other purposes or change the source code,               **
**  you may take legal responsibility.                                        **
**  In this case, There is no warranty and technical support.                 **
**                                                                            **
**  SRC-MODULE: Nm_Version.c                                                  **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Nm module                                             **
**                                                                            **
**  PURPOSE   : This file provides Version Checks for the Nm module with it   **
**              neighboring modules                                           **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision   Date          By             Description                        **
********************************************************************************
** 1.0.2      08-Jul-2022   ThuanVT        CP44-100                           **
** 1.0.1.1    20-Jun-2022   SMKwon         CP44-105                           **
** 1.0.0      04-Dec-2020   Autoever       Initial Version                    **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* Inclusion for Version macros */
#include "Nm_Version.h"

/* Inclustion for Com Stack Types header file */
#include "ComStack_Types.h"
/* Inclusion of ComM_Nm header file */
#include "ComM_Nm.h"
/* Inclusion of Det header file */
#if (NM_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"
#endif
/* Inclusion for Com header file */
#if (NM_STATE_CHANGE_IND_ENABLED == STD_ON)
#include "Com.h"
#endif
/* Inclusion for BswM_Nm header file */
#if (NM_CAR_WAKE_UP_RX_ENABLED == STD_ON)
#include "BswM_Nm.h"
#endif
/* Inclusion for SchM_Nm header file */
#if (NM_COORDINATOR_SUPPORT_ENABLED == STD_ON)
#include "SchM_Nm.h"
#endif
/* Inclusion for CanNm header file */
#if (NM_CANNM_ENABLED == STD_ON)
#include "CanNm.h"
#endif
/* Inclusion for FrNm header file */
#if (NM_FRNM_ENABLED == STD_ON)
#include "FrNm.h"
#endif
/* Inclusion for UdpNm header file */
#if (NM_UDPNM_ENABLED == STD_ON)
#include "UdpNm.h"
#endif
/* Inclusion for J1939Nm header file */
#if (NM_J1939NM_ENABLED == STD_ON)
#include "J1939Nm.h"
#endif
/* Inclusion for OsekNm header file */
#if (NM_OSEKNM_ENABLED == STD_ON)
#include "OsekNm.h"
#endif

/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/
/* Interal checking for AR Version */
#if ((NM_AR_RELEASE_MAJOR_VERSION != NM_VERSION_AR_RELEASE_MAJOR_VERSION) || \
     (NM_AR_RELEASE_MINOR_VERSION != NM_VERSION_AR_RELEASE_MINOR_VERSION) || \
     (NM_AR_RELEASE_REVISION_VERSION != NM_VERSION_AR_RELEASE_REVISION_VERSION))
  #error "Nm : Mismatch AUTOSAR Version in Nm_Version.c"
#endif
/* Interal checking for SW Version */
#if ((NM_SW_MAJOR_VERSION != NM_VERSION_SW_MAJOR_VERSION) || \
     (NM_SW_MINOR_VERSION != NM_VERSION_SW_MINOR_VERSION) || \
     (NM_SW_PATCH_VERSION != NM_VERSION_SW_PATCH_VERSION))
  #error "Nm : Mismatch Sofware Version in Nm_Version.c"
#endif

/* Inter Module check for ComStack_Types.h */
#if ((defined COMSTACK_TYPES_AR_RELEASE_MAJOR_VERSION) && \
     (defined COMSTACK_TYPES_AR_RELEASE_MINOR_VERSION))
  #if ((COMSTACK_TYPES_AR_RELEASE_MAJOR_VERSION != \
                                        NM_COMSTACK_TYPES_AR_MAJOR_VERSION) || \
       (COMSTACK_TYPES_AR_RELEASE_MINOR_VERSION != \
                                            NM_COMSTACK_TYPES_AR_MINOR_VERSION))
    #error "Nm : Mismatch AUTOSAR Version with ComStack_Types.h"
  #endif
#endif

/* Inter Module check for ComM_Nm.h */
#if ((defined COMM_NM_AR_RELEASE_MAJOR_VERSION) && \
     (defined COMM_NM_AR_RELEASE_MINOR_VERSION))
  #if ((COMM_NM_AR_RELEASE_MAJOR_VERSION != NM_COMM_AR_MAJOR_VERSION) || \
       (COMM_NM_AR_RELEASE_MINOR_VERSION != NM_COMM_AR_MINOR_VERSION))
    #error "Nm : Mismatch AUTOSAR Version with ComM_Nm.h"
  #endif
#endif

/* Inter Module check for Det.h */
#if ((NM_DEV_ERROR_DETECT == STD_ON) && \
     (defined DET_AR_RELEASE_MAJOR_VERSION) && \
     (defined DET_AR_RELEASE_MINOR_VERSION))
  #if ((DET_AR_RELEASE_MAJOR_VERSION != NM_DET_AR_MAJOR_VERSION) || \
       (DET_AR_RELEASE_MINOR_VERSION != NM_DET_AR_MINOR_VERSION))
    #error "Nm : Mismatch AUTOSAR Version with Det.h"
  #endif
#endif /* (NM_DEV_ERROR_DETECT == STD_ON) */

/* Inter Module check for Com.h */
#if ((NM_STATE_CHANGE_IND_ENABLED == STD_ON) && \
     (defined COM_AR_RELEASE_MAJOR_VERSION) && \
     (defined COM_AR_RELEASE_MINOR_VERSION))
  #if ((COM_AR_RELEASE_MAJOR_VERSION != NM_COM_AR_MAJOR_VERSION) || \
       (COM_AR_RELEASE_MINOR_VERSION != NM_COM_AR_MINOR_VERSION))
    #error "Nm : Mismatch AUTOSAR Version with Com.h"
  #endif
#endif /* (NM_STATE_CHANGE_IND_ENABLED == STD_ON) */

/* Inter Module check for BswM_Nm.h */
#if ((NM_CAR_WAKE_UP_RX_ENABLED == STD_ON) && \
     (defined BSWM_NM_AR_RELEASE_MAJOR_VERSION) && \
     (defined BSWM_NM_AR_RELEASE_MINOR_VERSION))
  #if ((BSWM_NM_AR_RELEASE_MAJOR_VERSION != NM_BSWM_AR_MAJOR_VERSION) || \
       (BSWM_NM_AR_RELEASE_MINOR_VERSION != NM_BSWM_AR_MINOR_VERSION))
    #error "Nm : Mismatch AUTOSAR Version with BswM_Nm.h"
  #endif
#endif /* (NM_CAR_WAKE_UP_RX_ENABLED == STD_ON) */

/* Inter Module check for SchM_Nm.h */
#if ((NM_COORDINATOR_SUPPORT_ENABLED == STD_ON) && \
     (defined SCHM_NM_AR_RELEASE_MAJOR_VERSION) && \
     (defined SCHM_NM_AR_RELEASE_MINOR_VERSION))
  #if ((SCHM_NM_AR_RELEASE_MAJOR_VERSION != NM_SCHM_AR_MAJOR_VERSION) || \
       (SCHM_NM_AR_RELEASE_MINOR_VERSION != NM_SCHM_AR_MAJOR_VERSION))
    #error "Nm : Mismatch AUTOSAR Version with SchM_Nm.h"
  #endif
#endif /* (NM_COORDINATOR_SUPPORT_ENABLED == STD_ON) */

/* Inter Module check for CanNm.h */
#if ((NM_CANNM_ENABLED == STD_ON) && \
     (defined CANNM_AR_RELEASE_MAJOR_VERSION) && \
     (defined CANNM_AR_RELEASE_MINOR_VERSION))
  #if ((CANNM_AR_RELEASE_MAJOR_VERSION != NM_CANNM_AR_MAJOR_VERSION) || \
       (CANNM_AR_RELEASE_MINOR_VERSION != NM_CANNM_AR_MINOR_VERSION))
    #error "Nm : Mismatch AUTOSAR Version with CanNm.h"
  #endif
#endif /* (NM_CANNM_ENABLED == STD_ON) */

/* Inter Module check for FrNm.h */
#if ((NM_FRNM_ENABLED == STD_ON) && \
     (defined FRNM_AR_RELEASE_MAJOR_VERSION) && \
     (defined FRNM_AR_RELEASE_MINOR_VERSION))
  #if ((FRNM_AR_RELEASE_MAJOR_VERSION != NM_FRNM_AR_MAJOR_VERSION) || \
       (FRNM_AR_RELEASE_MINOR_VERSION != NM_FRNM_AR_MINOR_VERSION))
    #error "Nm : Mismatch AUTOSAR Version with FrNm.h"
  #endif
#endif /* (NM_FRNM_ENABLED == STD_ON) */

/* Inter Module check for UdpNm.h */
#if ((NM_UDPNM_ENABLED == STD_ON) && \
     (defined UDPNM_AR_RELEASE_MAJOR_VERSION) && \
     (defined UDPNM_AR_RELEASE_MINOR_VERSION))
  #if ((UDPNM_AR_RELEASE_MAJOR_VERSION != NM_UDPNM_AR_MAJOR_VERSION) || \
       (UDPNM_AR_RELEASE_MINOR_VERSION != NM_UDPNM_AR_MINOR_VERSION))
    #error "Nm : Mismatch AUTOSAR Version with UdpNm.h"
  #endif
#endif /* (NM_UDPNM_ENABLED == STD_ON) */

/* Inter Module check for J1939Nm.h */
#if ((NM_J1939NM_ENABLED == STD_ON) && \
     (defined J1939NM_AR_RELEASE_MAJOR_VERSION) && \
     (defined J1939NM_AR_RELEASE_MINOR_VERSION))
  #if ((J1939NM_AR_RELEASE_MAJOR_VERSION != NM_J1939NM_AR_MAJOR_VERSION) || \
       (J1939NM_AR_RELEASE_MINOR_VERSION != NM_J1939NM_AR_MINOR_VERSION))
    #error "Nm : Mismatch AUTOSAR Version with J1939Nm.h"
  #endif
#endif /* (NM_J1939NM_ENABLED == STD_ON) */

/* Inter Module check for OsekNm.h */
#if ((NM_OSEKNM_ENABLED == STD_ON) && \
     (defined OSEKNM_AR_RELEASE_MAJOR_VERSION) && \
     (defined OSEKNM_AR_RELEASE_MINOR_VERSION))
  #if ((OSEKNM_AR_RELEASE_MAJOR_VERSION != NM_OSEKNM_AR_MAJOR_VERSION) || \
       (OSEKNM_AR_RELEASE_MINOR_VERSION != NM_OSEKNM_AR_MINOR_VERSION))
    #error "Nm : Mismatch AUTOSAR Version with OsekNm.h"
  #endif
#endif /* (NM_OSEKNM_ENABLED == STD_ON) */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
