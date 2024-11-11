/* polyspace +1 MISRA2012:1.1 [Not a defect:Low] "This rule is manually checked and has no impact." */
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
**  SRC-MODULE: ComM_Version.c                                                **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR COM Manager                                           **
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
** 1.1.7          31-Jan-2024         MUKim            CP44-3149              **
** 1.1.5          09-Jun-2023         NamNT1           CP44-2062              **
** 1.1.0          12-Aug-2022         ThuanVT          R44-Redmine #29733     **
** 1.0.4.1        20-Jun-2022         SMKwon           CP44-115               **
** 1.0.1          27-Dec-2020         DatNXT           R44-Redmine #14801     **
** 1.0.0          15-Dec-2020         JsLim            Initial Version        **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* ComM Pre Compile Types header file */
/* @Trace: ComM_SUD_MACRO_004  */
/* @Trace: ComM_SUD_MACRO_006  */
#include "ComM_PCTypes.h"
/* Version info header file */
/* @Trace: ComM_SUD_MACRO_001 */
#include "ComM_Version.h"
/* ComM_Com header file to get version info */
#if ((COMM_PNC_SUPPORT == STD_ON) && (COMM_PNC_ENABLED == STD_ON))
#if ((COMM_CANNETWORK_PRESENT == STD_ON) || (COMM_FRNETWORK_PRESENT == STD_ON) ||\
     (COMM_ETHNETWORK_PRESENT == STD_ON))
#include "ComM_Com.h"
#endif
#endif
/* Dcm header file to get version info */
#include "Dcm.h"
/* BswM header file to get version info */
#include "BswM.h"
/* EcuM header file to get version info */
#include "EcuM.h"
/* Nm header file to get version info */
#if ((COMM_FULL_NMVARIANT_SUPPORT == STD_ON) ||\
  (COMM_PASSIVE_NMVARIANT_SUPPORT == STD_ON))
#include "Nm.h"
#endif
/* NvM header file to get version info */
#if (COMM_NVM_BLOCK_DESCRIPTOR == STD_ON)
#include "NvM.h"
#endif
/* Rte header file to get version info */
#include "Rte.h"
/* Com header file to get version info */
#if ((COMM_PNC_SUPPORT == STD_ON) && (COMM_PNC_ENABLED == STD_ON))
#if ((COMM_CANNETWORK_PRESENT == STD_ON) || (COMM_FRNETWORK_PRESENT == STD_ON) ||\
     (COMM_ETHNETWORK_PRESENT == STD_ON))
/* @Trace: ComM_SUD_DATATYPE_001 */
#include "Com.h"
#endif
#endif
/* CanCM header file to get version info */
#if (COMM_CANCM_SUPPORT == STD_ON)
#include "CanCM.h"
#endif
/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/
/* Internal checking for AR Version */
#if((COMM_AR_RELEASE_MAJOR_VERSION != COMM_VERSION_AR_RELEASE_MAJOR_VERSION) ||\
    (COMM_AR_RELEASE_MINOR_VERSION != COMM_VERSION_AR_RELEASE_MINOR_VERSION) ||\
    (COMM_AR_RELEASE_REVISION_VERSION != \
                                      COMM_VERSION_AR_RELEASE_REVISION_VERSION))
  #error "ComM : Mismatch AUTOSAR Version in ComM_Version.c"
#endif

/* Internal checking for SW Version */
#if((COMM_SW_MAJOR_VERSION != COMM_VERSION_SW_MAJOR_VERSION) || \
    (COMM_SW_MINOR_VERSION != COMM_VERSION_SW_MINOR_VERSION) || \
    (COMM_SW_PATCH_VERSION != COMM_VERSION_SW_PATCH_VERSION))
  #error "ComM : Mismatch Software Version in ComM_Version.c"
#endif

/* Inter Module check for Dcm.h */
#if((defined DCM_AR_RELEASE_MAJOR_VERSION) && \
    (defined DCM_AR_RELEASE_MINOR_VERSION))
    #if((DCM_AR_RELEASE_MAJOR_VERSION != COMM_DCM_AR_RELEASE_MAJOR_VERSION) || \
        (DCM_AR_RELEASE_MINOR_VERSION != COMM_DCM_AR_RELEASE_MINOR_VERSION))
      #error "ComM : Mismatch AUTOSAR Version with Dcm.h"
    #endif
#endif

/* Inter Module check for Nm.h */
#if(((COMM_FULL_NMVARIANT_SUPPORT == STD_ON) || \
                                (COMM_PASSIVE_NMVARIANT_SUPPORT == STD_ON)) && \
      (defined NM_AR_RELEASE_MAJOR_VERSION ) && \
      (defined NM_AR_RELEASE_MINOR_VERSION))
    #if((NM_AR_RELEASE_MAJOR_VERSION != COMM_NM_AR_RELEASE_MAJOR_VERSION) || \
      (NM_AR_RELEASE_MINOR_VERSION != COMM_NM_AR_RELEASE_MINOR_VERSION))
      #error "ComM : Mismatch AUTOSAR Version with Nm.h"
    #endif
#endif

/* Inter Module check for Nvm.h */
#if((COMM_NVM_BLOCK_DESCRIPTOR == STD_ON) && \
     (defined NVM_AR_RELEASE_MAJOR_VERSION) && \
     (defined NVM_AR_RELEASE_MINOR_VERSION))
    #if((NVM_AR_RELEASE_MAJOR_VERSION != COMM_NVM_AR_RELEASE_MAJOR_VERSION) || \
        (NVM_AR_RELEASE_MINOR_VERSION != COMM_NVM_AR_RELEASE_MINOR_VERSION))
      #error "ComM : Mismatch AUTOSAR Version with Nvm.h"
    #endif
#endif

/* Inter Module check for Rte.h */
#if((defined RTE_AR_RELEASE_MAJOR_VERSION) && \
    (defined RTE_AR_RELEASE_MINOR_VERSION))
   #if((RTE_AR_RELEASE_MAJOR_VERSION != COMM_RTE_AR_RELEASE_MAJOR_VERSION) || \
       (RTE_AR_RELEASE_MINOR_VERSION != COMM_RTE_AR_RELEASE_MINOR_VERSION))
      #error "ComM : Mismatch AUTOSAR Version with Rte.h"
   #endif
#endif

/* Inter Module check for CanSM.h */
#if((COMM_CANNETWORK_PRESENT == STD_ON) && \
    (defined CANSM_AR_RELEASE_MAJOR_VERSION) && \
    (defined CANSM_AR_RELEASE_MINOR_VERSION))
  #if((CANSM_AR_RELEASE_MAJOR_VERSION != \
                                       COMM_CANSM_AR_RELEASE_MAJOR_VERSION) || \
        (CANSM_AR_RELEASE_MINOR_VERSION != COMM_CANSM_AR_RELEASE_MINOR_VERSION))
    #error "ComM : Mismatch AUTOSAR Version with CanSM.h"
  #endif
#endif

/* Inter Module check for FrSM.h */
#if((COMM_FRNETWORK_PRESENT == STD_ON) && \
    (defined FRSM_AR_RELEASE_MAJOR_VERSION) && \
    (defined FRSM_AR_RELEASE_MINOR_VERSION))
  #if((FRSM_AR_RELEASE_MAJOR_VERSION != COMM_FRSM_AR_RELEASE_MAJOR_VERSION) || \
      (FRSM_AR_RELEASE_MINOR_VERSION != COMM_FRSM_AR_RELEASE_MINOR_VERSION))
    #error "ComM : Mismatch AUTOSAR Version with FrSM.h"
  #endif
#endif

/* Inter Module check for LinSM.h */
#if((COMM_LINNETWORK_PRESENT == STD_ON) && \
    (defined LINSM_AR_RELEASE_MAJOR_VERSION) && \
    (defined LINSM_AR_RELEASE_MINOR_VERSION))
  #if((LINSM_AR_RELEASE_MAJOR_VERSION != \
                                       COMM_LINSM_AR_RELEASE_MAJOR_VERSION) || \
        (LINSM_AR_RELEASE_MINOR_VERSION != COMM_LINSM_AR_RELEASE_MINOR_VERSION))
    #error "ComM : Mismatch AUTOSAR Version with LinSM.h"
  #endif
#endif

/* Inter Module check for EthSM.h */
#if((COMM_ETHNETWORK_PRESENT == STD_ON) && \
    (defined ETHSM_AR_RELEASE_MAJOR_VERSION) && \
    (defined ETHSM_AR_RELEASE_MINOR_VERSION))
  #if((ETHSM_AR_RELEASE_MAJOR_VERSION != \
                                       COMM_ETHSM_AR_RELEASE_MAJOR_VERSION) || \
        (ETHSM_AR_RELEASE_MINOR_VERSION != COMM_ETHSM_AR_RELEASE_MINOR_VERSION))
    #error "ComM : Mismatch AUTOSAR Version with  EthSM.h"
  #endif
#endif

/* Inter Module check for Det.h */
#if ((COMM_DEV_ERROR_DETECT == STD_ON) && \
     (defined DET_AR_RELEASE_MAJOR_VERSION) && \
     (defined DET_AR_RELEASE_MINOR_VERSION))
  #if ((DET_AR_RELEASE_MAJOR_VERSION != COMM_DET_AR_RELEASE_MAJOR_VERSION) || \
       (DET_AR_RELEASE_MINOR_VERSION != COMM_DET_AR_RELEASE_MINOR_VERSION))
    #error "ComM : Mismatch AUTOSAR Version with Det.h"
  #endif
#endif

/* Inter Module check for BswM.h */
#if((defined BSWM_AR_RELEASE_MAJOR_VERSION) && \
    (defined BSWM_AR_RELEASE_MINOR_VERSION))
  #if((BSWM_AR_RELEASE_MAJOR_VERSION != COMM_BSWM_AR_RELEASE_MAJOR_VERSION) || \
  (BSWM_AR_RELEASE_MINOR_VERSION != COMM_BSWM_AR_RELEASE_MINOR_VERSION))
    #error "ComM : Mismatch AUTOSAR Version with BswM.h"
  #endif
#endif

/* Inter Module check for Com.h */
#if((COMM_PNC_SUPPORT == STD_ON) && (COMM_PNC_ENABLED == STD_ON))
#if ((COMM_CANNETWORK_PRESENT == STD_ON) || (COMM_FRNETWORK_PRESENT == STD_ON) ||\
     (COMM_ETHNETWORK_PRESENT == STD_ON))
#if((defined COM_AR_RELEASE_MAJOR_VERSION) && \
    (defined COM_AR_RELEASE_MINOR_VERSION))
  #if((COM_AR_RELEASE_MAJOR_VERSION != COMM_COM_AR_RELEASE_MAJOR_VERSION) || \
      (COM_AR_RELEASE_MINOR_VERSION != COMM_COM_AR_RELEASE_MINOR_VERSION))
    #error "ComM : Mismatch AUTOSAR Version with Com.h"
  #endif
#endif
#endif
#endif

/* Inter Module check for CanCM.h */
#if ((COMM_CANCM_SUPPORT == STD_ON) && \
     (defined CANCM_AR_RELEASE_MAJOR_VERSION) && \
     (defined CANCM_AR_RELEASE_MINOR_VERSION))
  #if ((CANCM_AR_RELEASE_MAJOR_VERSION != \
                                       COMM_CANCM_AR_RELEASE_MAJOR_VERSION) || \
        (CANCM_AR_RELEASE_MINOR_VERSION != COMM_CANCM_AR_RELEASE_MINOR_VERSION))
    #error "ComM : Mismatch AUTOSAR Version with CanCM.h"
  #endif
#endif

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/

