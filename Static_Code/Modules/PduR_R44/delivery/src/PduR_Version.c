/* polyspace +1 MISRA2012:1.1 [Not a defect:Low] "The number of macros doesn't matter" */
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
**  SRC-MODULE: PduR_Version.c                                                **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR PDU Router                                            **
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
** Revision  Date          By          Description                            **
********************************************************************************
** 1.0.5     11-Nov-2022   HaoTA4      CP44-1051                              **
** 1.0.4     11-Aug-2022   PhucNHM     CP44-635                               **
** 1.0.0     04-Dec-2020   AUTOEVER    Initial Version                        **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* @Trace: PduR_SUD_FILE_001 */
#include "PduR.h"           /* Generated Header File */
#include "PduR_Cfg.h"           /* Generated Header File */
#include "PduR_Version.h"       /* PduR Version Header File */
#include "PduR_Incl.h"          /* PduR Inclusion Header File */
/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/
/* @Traceability BEGIN -- SRS: SWS_BSW_00036 */
/* @Trace: SRS_BSW_00337 */
/* AUTOSAR Specification Version Information */
#if ((PDUR_AR_RELEASE_MAJOR_VERSION != PDUR_VERSION_AR_RELEASE_MAJOR_VERSION)||\
     (PDUR_AR_RELEASE_MINOR_VERSION != PDUR_VERSION_AR_RELEASE_MINOR_VERSION))
#error "PduR: Mismatch AUTOSAR Version in PduR_Version.c"
#endif

/* Software Version Information */
#if ((PDUR_SW_MAJOR_VERSION != PDUR_VERSION_SW_MAJOR_VERSION)||\
     (PDUR_SW_MINOR_VERSION != PDUR_VERSION_SW_MINOR_VERSION)||\
     (PDUR_SW_PATCH_VERSION != PDUR_VERSION_SW_PATCH_VERSION))
#error "PduR: Mismatch Software Version in PduR_Version.c"
#endif

/* CanIf Version check*/
#if (PDUR_CANIF_SUPPORT == STD_ON)
#if ((CANIF_AR_RELEASE_MAJOR_VERSION != PDUR_CANIF_AR_RELEASE_MAJOR_VERSION)||\
     (CANIF_AR_RELEASE_MINOR_VERSION != PDUR_CANIF_AR_RELEASE_MINOR_VERSION))
#error "CanIf : Mismatch AUTOSAR Version with CanIf.h"
#endif
#endif /* End of if (PDUR_CANIF_SUPPORT == STD_ON) */

/* LinIf Version Check */
#if (PDUR_LINIF_SUPPORT == STD_ON)
#if ((LINIF_AR_RELEASE_MAJOR_VERSION != PDUR_LINIF_AR_RELEASE_MAJOR_VERSION)||\
     (LINIF_AR_RELEASE_MINOR_VERSION != PDUR_LINIF_AR_RELEASE_MINOR_VERSION))
#error "LinIf : Mismatch AUTOSAR Version with LinIf.h"
#endif
#endif /* End of if (PDUR_LINIF_SUPPORT == STD_ON) */

/* FrIf Version Check */
#if (PDUR_FRIF_SUPPORT == STD_ON)
#if ((FRIF_AR_RELEASE_MAJOR_VERSION != PDUR_FRIF_AR_RELEASE_MAJOR_VERSION)||\
     (FRIF_AR_RELEASE_MINOR_VERSION != PDUR_FRIF_AR_RELEASE_MINOR_VERSION))
#error "FrIf : Mismatch AUTOSAR Version with FrIf.h"
#endif
#endif /* End of if (PDUR_FRIF_SUPPORT == STD_ON) */

/* SoAd Version Check */
#if (PDUR_SOAD_SUPPORT == STD_ON)
#if ((SOAD_AR_RELEASE_MAJOR_VERSION != PDUR_SOAD_AR_RELEASE_MAJOR_VERSION)||\
     (SOAD_AR_RELEASE_MINOR_VERSION != PDUR_SOAD_AR_RELEASE_MINOR_VERSION))
#error "SoAd : Mismatch AUTOSAR Version with SoAd.h"
#endif
#endif /* End of if (PDUR_SOAD_SUPPORT == STD_ON) */

/* SecOC Version Check */
#if (PDUR_SECOC_SUPPORT == STD_ON)
#if ((SECOC_AR_RELEASE_MAJOR_VERSION != PDUR_SECOC_AR_RELEASE_MAJOR_VERSION)||\
     (SECOC_AR_RELEASE_MINOR_VERSION != PDUR_SECOC_AR_RELEASE_MINOR_VERSION))
#error "SecOC : Mismatch AUTOSAR Version with SecOC.h"
#endif
#endif /* End of if (PDUR_SECOC_SUPPORT == STD_ON) */

/* CanTp Version check */
#if (PDUR_CANTP_SUPPORT == STD_ON)
#if ((CANTP_AR_RELEASE_MAJOR_VERSION != PDUR_CANTP_AR_RELEASE_MAJOR_VERSION)||\
     (CANTP_AR_RELEASE_MINOR_VERSION != PDUR_CANTP_AR_RELEASE_MINOR_VERSION))
#error "CanTp : Mismatch AUTOSAR Version with CanTp.h"
#endif
#endif /* End of if (PDUR_CANIF_SUPPORT == STD_ON) */

/* FrTp Version Check */
#if (PDUR_FRTP_SUPPORT == STD_ON)
#if ((FRTP_AR_RELEASE_MAJOR_VERSION != PDUR_FRTP_AR_RELEASE_MAJOR_VERSION)||\
     (FRTP_AR_RELEASE_MINOR_VERSION != PDUR_FRTP_AR_RELEASE_MINOR_VERSION))
#error "FrTp : Mismatch AUTOSAR Version with FrTp.h"
#endif
#endif /* End of if (PDUR_FRTP_SUPPORT == STD_ON) */

/* J1939Tp Version Check */
#if (PDUR_J1939TP_SUPPORT == STD_ON)
#if ((J1939TP_AR_RELEASE_MAJOR_VERSION != PDUR_J1939TP_AR_RELEASE_MAJOR_VERSION)||\
     (J1939TP_AR_RELEASE_MINOR_VERSION != PDUR_J1939TP_AR_RELEASE_MINOR_VERSION))
#error "J1939Tp : Mismatch AUTOSAR Version with J1939Tp.h"
#endif
#endif /* End of if (PDUR_J1939TP_SUPPORT == STD_ON) */


/* DoIP Version Check */
#if (PDUR_DOIP_SUPPORT == STD_ON)
#if ((DOIP_AR_RELEASE_MAJOR_VERSION != PDUR_DOIP_AR_RELEASE_MAJOR_VERSION)||\
     (DOIP_AR_RELEASE_MINOR_VERSION != PDUR_DOIP_AR_RELEASE_MINOR_VERSION))
#error "DoIP : Mismatch AUTOSAR Version with DoIP.h"
#endif
#endif /* End of if (PDUR_DOIP_SUPPORT == STD_ON) */

/* Com Version check */
#if (PDUR_COM_SUPPORT == STD_ON)
#if ((COM_AR_RELEASE_MAJOR_VERSION != PDUR_COM_AR_RELEASE_MAJOR_VERSION)||\
     (COM_AR_RELEASE_MINOR_VERSION != PDUR_COM_AR_RELEASE_MINOR_VERSION))
#error "Com : Mismatch AUTOSAR Version with Com.h"
#endif
#endif /* End of if (PDUR_COM_SUPPORT == STD_ON) */

/* Dcm Version check */
#if (PDUR_DCM_SUPPORT == STD_ON)
#if ((DCM_AR_RELEASE_MAJOR_VERSION != PDUR_DCM_AR_RELEASE_MAJOR_VERSION)||\
     (DCM_AR_RELEASE_MINOR_VERSION != PDUR_DCM_AR_RELEASE_MINOR_VERSION))
#error "Dcm : Mismatch AUTOSAR Version with Dcm.h"
#endif
#endif /* End of if (PDUR_DCM_SUPPORT == STD_ON) */

/* LdCom Version check */
#if (PDUR_LDCOM_SUPPORT == STD_ON)
#if ((LDCOM_AR_RELEASE_MAJOR_VERSION != PDUR_LDCOM_AR_RELEASE_MAJOR_VERSION)||\
     (LDCOM_AR_RELEASE_MINOR_VERSION != PDUR_LDCOM_AR_RELEASE_MINOR_VERSION))
#error "LdCom : Mismatch AUTOSAR Version with LdCom.h"
#endif
#endif /* End of if (PDUR_LDCOM_SUPPORT == STD_ON) */

/* SomeIpTp Version check */
#if (PDUR_SOMEIPTP_SUPPORT == STD_ON)
#if ((SOMEIPTP_AR_RELEASE_MAJOR_VERSION != PDUR_SOMEIPTP_AR_RELEASE_MAJOR_VERSION)||\
     (SOMEIPTP_AR_RELEASE_MINOR_VERSION != PDUR_SOMEIPTP_AR_RELEASE_MINOR_VERSION))
#error "SomeIpTp : Mismatch AUTOSAR Version with SomeIpTp.h"
#endif
#endif /* End of if (PDUR_SOMEIPTP_SUPPORT == STD_ON) */

/* IpduM Version check */
#if (PDUR_IPDUM_SUPPORT == STD_ON)
#if ((IPDUM_AR_RELEASE_MAJOR_VERSION != PDUR_IPDUM_AR_RELEASE_MAJOR_VERSION)||\
     (IPDUM_AR_RELEASE_MINOR_VERSION != PDUR_IPDUM_AR_RELEASE_MINOR_VERSION))
#error "IpduM : Mismatch AUTOSAR Version with IpduM.h"
#endif
#endif /* End of if (PDUR_IPDUM_SUPPORT == STD_ON) */

/* Dlt Version check */
#if (PDUR_DLT_SUPPORT == STD_ON)
#if ((DLT_AR_RELEASE_MAJOR_VERSION != PDUR_DLT_AR_RELEASE_MAJOR_VERSION)||\
     (DLT_AR_RELEASE_MINOR_VERSION != PDUR_DLT_AR_RELEASE_MINOR_VERSION))
#error "Dlt : Mismatch AUTOSAR Version with Dlt.h"
#endif
#endif /* End of if (PDUR_DLT_SUPPORT == STD_ON) */

/* J1939Rm Version check */
#if (PDUR_J1939RM_SUPPORT == STD_ON)
#if ((J1939RM_AR_RELEASE_MAJOR_VERSION != PDUR_J1939RM_AR_RELEASE_MAJOR_VERSION)||\
     (J1939RM_AR_RELEASE_MINOR_VERSION != PDUR_J1939RM_AR_RELEASE_MINOR_VERSION))
#error "J1939Rm : Mismatch AUTOSAR Version with J1939Rm.h"
#endif
#endif /* End of if (PDUR_J1939RM_SUPPORT == STD_ON) */

/* J1939Dcm Version check */
#if (PDUR_J1939DCM_SUPPORT == STD_ON)
#if ((J1939DCM_AR_RELEASE_MAJOR_VERSION != PDUR_J1939DCM_AR_RELEASE_MAJOR_VERSION)||\
     (J1939DCM_AR_RELEASE_MINOR_VERSION != PDUR_J1939DCM_AR_RELEASE_MINOR_VERSION))
#error "J1939Dcm : Mismatch AUTOSAR Version with J1939Dcm.h"
#endif
#endif /* End of if (PDUR_J1939DCM_SUPPORT == STD_ON) */

/* CanNm Version check */
#if (PDUR_CANNM_SUPPORT == STD_ON)
#if ((CANNM_AR_RELEASE_MAJOR_VERSION != PDUR_CANNM_AR_RELEASE_MAJOR_VERSION)||\
     (CANNM_AR_RELEASE_MINOR_VERSION != PDUR_CANNM_AR_RELEASE_MINOR_VERSION))
#error "CanNm : Mismatch AUTOSAR Version with CanNm.h"
#endif
#endif /* End of if (PDUR_CANNM_SUPPORT == STD_ON) */

/* FrNm Version check */
#if (PDUR_FRNM_SUPPORT == STD_ON)
#if ((FRNM_AR_RELEASE_MAJOR_VERSION != PDUR_FRNM_AR_RELEASE_MAJOR_VERSION)||\
     (FRNM_AR_RELEASE_MINOR_VERSION != PDUR_FRNM_AR_RELEASE_MINOR_VERSION))
#error "FrNm : Mismatch AUTOSAR Version with FrNm.h"
#endif
#endif /* End of if (PDUR_FRNM_SUPPORT == STD_ON) */

/* UdpNm Version check */
#if (PDUR_UDPNM_SUPPORT == STD_ON)
#if ((UDPNM_AR_RELEASE_MAJOR_VERSION != PDUR_UDPNM_AR_RELEASE_MAJOR_VERSION)||\
     (UDPNM_AR_RELEASE_MINOR_VERSION != PDUR_UDPNM_AR_RELEASE_MINOR_VERSION))
#error "UdpNm : Mismatch AUTOSAR Version with UdpNm.h"
#endif
#endif /* End of if (PDUR_UDPNM_SUPPORT == STD_ON) */

/* DET Version check */
#if (PDUR_DEV_ERROR_DETECT == STD_ON)
#if ((DET_AR_RELEASE_MAJOR_VERSION != PDUR_DET_AR_RELEASE_MAJOR_VERSION)||\
     (DET_AR_RELEASE_MINOR_VERSION != PDUR_DET_AR_RELEASE_MINOR_VERSION))
#error "Det : Mismatch AUTOSAR Version with Det.h"
#endif
#endif  /* End of if (PDUR_DEV_ERROR_DETECT == STD_ON) */
/* @Traceability END -- SRS: SWS_BSW_00036 */
/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
