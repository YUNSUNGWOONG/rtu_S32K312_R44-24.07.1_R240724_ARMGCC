/*******************************************************************************
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**                                                                            **
**  Confidential Proprietary Information. Distribution Limited.               **
**  This source code is permitted to be used only in projects contracted      **
**  with Hyundai Autoever, and any other use is prohibited.                   **
**  If you use it for other purposes or change the source code,               **
**  you may take legal responsibility.                                        **
**  In this case, There is no warranty and technical support.                 **
**                                                                            **
**  SRC-MODULE: CanTp.h                                                       **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR CAN Transport Protocol                                **
**                                                                            **
**  PURPOSE   : Main header file for CanTp                                    **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: No                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: No                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By             Description                         **
********************************************************************************
** 1.1.0     13-Sep-2023   HieuTM8        #CP44-2819                          **
** 1.0.10.0  20-Apr-2023   HieuTM8        #CP44-2002                          **
** 1.0.7     31-Oct-2022   HieuTM8        #CP44-1038                          **
** 1.0.4     04-Jul-2022   HieuTM8        CP44-98                             **
** 1.0.3.1   22-Jun-2022   SMKwon         CP44-94                             **
** 1.0.3     30-May-2022   HieuTM8        R44-Redmine #26803                  **
** 1.0.1     28-Feb-2022   HieuTM8        R44-Redmine #20400, #19344          **
** 1.0.0     04-Dec-2020   SMKwon         Initial Version                     **
*******************************************************************************/
#ifndef CANTP_H
#define CANTP_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* @Trace: CanTp_SUD_FILE_001 */
#include "string.h"
/* @Trace: CanTp_SUD_MACRO_012 */
#include "ComStack_Types.h"       /* Communication Stack Types Header File */
/* @Trace: CanTp_SUD_MACRO_009 */
#include "CanTp_Cfg.h"            /* Configuration header file */
#include "CanTp_IntTypes.h"
/* If support PostBuild */
#if (CANTP_VARIANT_POSTBUILD_SUPPORT == STD_ON)
#include "CanTp_PBcfg.h"          /* Include Configuration support PostBuild */
#endif                            /* End of if (STD_ON == CANTP_VARIANT_POSTBUILD_SUPPORT) */
#include "CanTp_Cbk.h"
#if (CANTP_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"                  /* DET header file */
#endif

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/* @Trace: SWS_CanTp_00267 */
/* @Trace: CanTp_SUD_MACRO_001 */
/* SWS_CanTp_00267: Version number macros for checking */
/* AUTOSAR specification version information */
#define CANTP_H_AR_RELEASE_MAJOR_VERSION    0x04u
#define CANTP_H_AR_RELEASE_MINOR_VERSION    0x04u
#define CANTP_H_AR_RELEASE_REVISION_VERSION 0x00u

/* CANTP software version information */
#define CANTP_H_SW_MAJOR_VERSION            0x01u
#define CANTP_H_SW_MINOR_VERSION            0x01u
#define CANTP_H_SW_PATCH_VERSION            0x00u

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/* Instance id */
#define CANTP_INSTANCE_ID          ((uint8) 0)
/* @Trace: SWS_CanTp_00293 SWS_CanTp_00352 */
/* SWS_CanTp_00293, SWS_CanTp_00352: The CanTp module shall be able to detect the following errors */
/* DET Error codes */
/* @Trace: CanTp_SUD_MACRO_013 */
#define CANTP_E_PARAM_ID           ((uint8) 0x02)
#define CANTP_E_PARAM_POINTER      ((uint8) 0x03)
#define CANTP_E_UNINIT             ((uint8) 0x20)
#define CANTP_E_INVALID_TX_ID      ((uint8) 0x30)
#define CANTP_E_INVALID_RX_ID      ((uint8) 0x40)
#define CANTP_E_PADDING            ((uint8) 0x70)
#define CANTP_E_INVALID_TATYPE     ((uint8) 0x90)
#define CANTP_E_OPER_NOT_SUPPORTED ((uint8) 0xA0)
#define CANTP_E_COM                ((uint8) 0xB0)
#define CANTP_E_RX_COM             ((uint8) 0xC0)
#define CANTP_E_TX_COM             ((uint8) 0xD0)

/* API Service IDs */
/* @Trace: CanTp_SUD_MACRO_010 */
#define CANTP_INIT_SID             ((uint8) 0x01)
#define CANTP_SHUTDOWN_SID         ((uint8) 0x02)
#define CANTP_TRANSMIT_SID         ((uint8) 0x49)
#define CANTP_MAINFUNCTION_SID     ((uint8) 0x06)
#define CANTP_GETVERSIONINFO_SID   ((uint8) 0x07)
#define CANTP_RXINDICATION_SID     ((uint8) 0x42)
#define CANTP_TXCONFIRMATION_SID   ((uint8) 0x40)
#define CANTP_CANCELTRANSMIT_SID   ((uint8) 0x4A)
#define CANTP_CANCELRECEIVE_SID    ((uint8) 0x4C)
#define CANTP_CHANGEPARAM_SID      ((uint8) 0x4B)
#define CANTP_READPRAM_SID         ((uint8) 0x0B)

#define CANTP_EIGHT                    0x08

/*******************************************************************************
**                                  Macros                                    **
*******************************************************************************/
/* @Trace: CanTp_SUD_MACRO_011 */
#ifndef CANTP_ZERO
#define CANTP_ZERO 0x00
#endif
/* MISRA-C 14.2 fixed */
/* polyspace +1 MISRA-C3:D4.9 [Not a defect:Low] "use function like-macro for removing unused argument compiler warning" */
#define CANTP_UNUSED_PTR(x)                       (void)x
                                                    
/* polyspace +2 MISRA-C3:D4.9 [Not a defect:Low] "use function like-macro for removing unused argument compiler warning" */
#define CANTP_UNUSED(x)                           (void)x                                                   

/* polyspace +1 MISRA-C3:D4.9 [Not a defect:Low] "No impact of this violation" */
#define CANTP_MEMCPY(Dst, Src, Size)              (memcpy(Dst, Src, Size))
/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
/* @Trace: CanTp_SUD_DATATYPE_008 */
#if (STD_ON == CANTP_VERSION_INFO_API)
#define CANTP_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void,
  CANTP_CODE) CanTp_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC,
    CANTP_APPL_DATA) versioninfo);
#define CANTP_STOP_SEC_CODE
#include "MemMap.h"
#endif /* End of if (STD_ON == CANTP_VERSION_INFO_API) */

#define CANTP_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void,
  CANTP_CODE) CanTp_Init(P2CONST(CanTp_ConfigType, AUTOMATIC,
    CANTP_APPL_CONST) CfgPtr);
#define CANTP_STOP_SEC_CODE
#include "MemMap.h"

#define CANTP_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, CANTP_CODE) CanTp_Shutdown(void);

#define CANTP_STOP_SEC_CODE
#include "MemMap.h"
/* @Trace: CanTp_SUD_DATATYPE_003 CanTp_SUD_DATATYPE_007 */
#define CANTP_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, CANTP_CODE) CanTp_Transmit(PduIdType CanTpTxSduId,
  P2CONST(PduInfoType, AUTOMATIC, CANTP_APPL_CONST) CanTpTxInfoPtr);
#define CANTP_STOP_SEC_CODE
#include "MemMap.h"
/* @Trace: CanTp_SUD_DATATYPE_007 */
#if (STD_ON == CANTP_TC)
#define CANTP_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, CANTP_CODE) CanTp_CancelTransmit(PduIdType
  CanTpTxSduId);
#define CANTP_STOP_SEC_CODE
#include "MemMap.h"
#endif /* End of if (STD_ON == CANTP_TC) */
/* @Trace: CanTp_SUD_DATATYPE_006 CanTp_SUD_DATATYPE_007 */
#if ((STD_ON == CANTP_READ_PARAMETER_API) && (STD_ON == CANTP_RX_PHYSICAL_ADDRESSING))
#define CANTP_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, CANTP_CODE) CanTp_ChangeParameter(PduIdType id,
  TPParameterType parameter, VAR(uint16, AUTOMATIC) Value);
#define CANTP_STOP_SEC_CODE
#include "MemMap.h"
#endif /* End of if (((STD_ON == CANTP_READ_PARAMETER_API) && (STD_ON == CANTP_RX_PHYSICAL_ADDRESSING)) */
/* @Trace: CanTp_SUD_DATATYPE_007 */
#if (STD_ON == CANTP_RX_NSDU)
#define CANTP_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, CANTP_CODE) CanTp_CancelReceive(PduIdType
  CanTpRxSduId);
#define CANTP_STOP_SEC_CODE
#include "MemMap.h"
#endif /* End of (STD_ON == CANTP_RX_NSDU) */
/* @Trace: CanTp_SUD_DATATYPE_006 CanTp_SUD_DATATYPE_007 */
#if (STD_ON == CANTP_READ_PARAMETER_API)
#define CANTP_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, CANTP_CODE) CanTp_ReadParameter(PduIdType id,
  TPParameterType parameter, P2VAR(uint16, AUTOMATIC, CANTP_APPL_DATA) ptrValue);
#define CANTP_STOP_SEC_CODE
#include "MemMap.h"
#endif /* End of (STD_ON == CANTP_READ_PARAMETER_API) */

#define CANTP_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, CANTP_CODE) CanTp_MainFunction(void);
#define CANTP_STOP_SEC_CODE
#include "MemMap.h"
/* @Trace: CanTp_SUD_DATATYPE_007 */
#define CANTP_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, CANTP_CODE) CanTp_TxConfirmation(PduIdType txPduId,
  Std_ReturnType result);
#define CANTP_STOP_SEC_CODE
#include "MemMap.h"
/* @Trace: CanTp_SUD_DATATYPE_003 */
#define CANTP_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, CANTP_CODE) CanTp_RxIndication(PduIdType rxPduId, P2CONST(
  PduInfoType, AUTOMATIC, CANTP_APPL_CONST) ptrPduInfo);
#define CANTP_STOP_SEC_CODE
#include "MemMap.h"

#endif /* CANTP_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/

