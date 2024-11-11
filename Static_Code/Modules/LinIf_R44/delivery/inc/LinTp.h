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
**  SRC-MODULE: LinTp.h                                                       **
**                                                                            **
**  TARGET    : ALL                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR LinIf Module                                          **
**                                                                            **
**  PURPOSE   : Provision of extern declaration of APIs, Service-ID's,        **
**              DET error codes of the APIs, type definitions, structure data **
**              types of Lin Interface.                                       **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision    Date           By                 Description                  **
********************************************************************************
** 1.0.6       17-Oct-2022    KhaLN1             #CP44-563                    **
** 1.0.3       17-Sep-2021    DuyNGB             R44-Redmine #20121           **
** 1.0.1       20-Apr-2021    LongTQB            R44-Redmine #17195           **
** 1.0.0       22-Dec-2020    SJ Kim             Initial version              **
*******************************************************************************/

#ifndef LINTP_H
#define LINTP_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

#include "LinIf_Cfg.h" /* Configuration header file */
#include "LinIf.h"
#include "Lin_GeneralTypes.h"      /* Lin General Types header */
#include "ComStack_Types.h"

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/* AUTOSAR specification version information */
#define LINTP_AR_RELEASE_MAJOR_VERSION    (LINIF_AR_RELEASE_MAJOR_VERSION)
#define LINTP_AR_RELEASE_MINOR_VERSION    (LINIF_AR_RELEASE_MINOR_VERSION)
#define LINTP_AR_RELEASE_REVISION_VERSION (LINIF_AR_RELEASE_REVISION_VERSION)

/* File version information */
#define LINTP_SW_MAJOR_VERSION  (LINIF_SW_MAJOR_VERSION)
#define LINTP_SW_MINOR_VERSION  (LINIF_SW_MINOR_VERSION)

/*******************************************************************************
**                      Global Symbols                                        **
*******************************************************************************/

/* @Trace: LinTp_SUD_MACRO_013 */
/* API service ids */
#define LINTP_INIT_SID                          ((uint8)0x40U)
#define LINTP_TRANSMIT_SID                      ((uint8)0x41U)
#define LINTP_GETVERSIONINFO_SID                ((uint8)0x42U)
#define LINTP_SHUTDOWN_SID                      ((uint8)0x43U)
#define LINTP_CHANGEPARAMETER_SID               ((uint8)0x44U)
#define LINTP_CANCELTRANSMIT_SID                ((uint8)0x46U)
#define LINTP_CANCELRECEIVE_SID                 ((uint8)0x47U)

#define LINTP_FUNCTIONAL_NAD                    ((uint8)0x7EU)

#define LINTP_ZERO                              ((uint8)0x00U)
#define LINTP_THREE                             ((uint8)0x03U)

#define LINTP_UNINIT                            ((uint8)0x00U)
#define LINTP_INIT                              ((uint8)0x01U)

#define LINTP_CHANNEL_IDLE                      ((uint8)0x01U)
#define LINTP_TX_BUSY_BUFF_RDY                  ((uint8)0x02U)
#define LINTP_TX_BUSY_BUFF_NOT_RDY              ((uint8)0x03U)
#define LINTP_RX_BUSY_BUFF_RDY                  ((uint8)0x04U)
#define LINTP_RX_BUSY_BUFF_NOT_RDY              ((uint8)0x05U)
#define LINTP_TX_BUSY_BUFF_ERROR                ((uint8)0x06U)

#define LINTP_DL_MASK                           ((uint8)0x0FU)
#define LINTP_MAX_FRAME_COUNTER                 ((uint8)0x0FU)
#define LINTP_DIAG_SELECT                       ((uint8)0x02U)
#define LINIF_MRF                               ((uint16)0x03U)
#define LINIF_SRF                               ((uint16)0x04U)
#define LINIF_SF_PCI                            ((uint8)0x00U)
#define LINIF_FF_PCI                            ((uint8)0x10U)
#define LINIF_CF_PCI                            ((uint8)0x20U)
#define LINTP_PENDING_RESPONSE_FRAME            ((uint8)0x78U)
#define LINIF_EIGHT_LEAST_MASK                  ((uint8)0xFFU)
#define LINIF_PCI_MASK                          ((uint8)0xF0U)
#define LINTP_EIGHT                             ((uint8)0x08U)
#define LINIF_MAX_TX_LIMIT                      ((uint32)0x0FFFU)
#define LINTP_NAS_TIMER                         ((uint8)0x00U)
#define LINTP_NCS_TIMER                         ((uint8)0x01U)
#define LINTP_NCR_TIMER                         ((uint8)0x02U)
/* polyspace-begin MISRA-C3:D4.9 [Justified:Low] "use function like-macro for reduce execution time and stack" */
#define LINTP_TIMER_UPDATE_MACRO(Channel, Timer, TimerValue) \
  do\
  {\
    LinTp_GaaTimers[(Channel)][(Timer)] = (TimerValue);\
  } while(0)
/* polyspace-end MISRA-C3:D4.9 [Justified:Low] "use function like-macro for reduce execution time and stack" */
/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/* @Trace: LinIf_SUD_DATATYPE_003 */
/* Structure for LinTp Config Type */
typedef struct
{
  /* Dummy element for pre-compile variant */
  uint8 ucLinTpDummy;
}LinTp_ConfigType;

/*******************************************************************************
**                      Global Function Prototypes                            **
*******************************************************************************/
#define LINTP_START_SEC_CODE
#include "MemMap.h"

extern FUNC(void, LINTP_CODE) LinTp_Init
  (P2CONST(LinTp_ConfigType, AUTOMATIC, LINTP_APPL_CONST) ConfigPtr);

#if (LINTP_VERSION_INFO_API == STD_ON)
extern FUNC(void, LINTP_CODE) LinTp_GetVersionInfo
  (P2VAR(Std_VersionInfoType, AUTOMATIC, LINTP_APPL_DATA) versioninfo);
#endif

extern FUNC(void, LINTP_CODE) LinTp_Shutdown (void);

extern FUNC(Std_ReturnType, LINTP_CODE) LinTp_Transmit
  (PduIdType TxPduId, P2CONST(PduInfoType, AUTOMATIC, LINTP_APPL_CONST)
  PduInfoPtr);

extern FUNC(Std_ReturnType, LINTP_CODE) LinTp_ChangeParameter
  (PduIdType id, TPParameterType parameter, uint16 value);

#define LINTP_STOP_SEC_CODE
#include "MemMap.h"

#endif  /* LINTP_H */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
