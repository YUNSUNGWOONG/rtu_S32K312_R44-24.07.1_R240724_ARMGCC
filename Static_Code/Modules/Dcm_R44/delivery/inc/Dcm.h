/*******************************************************************************
**                                                                            **
** (C) 2021 HYUNDAI AUTOEVER Corp.                                            **
** Confidential Proprietary Information. Distribution Limited.                **
** This source code is permitted to be used only in projects contracted       **
** with Hyundai Autoever, and any other use is prohibited.                    **
** If you use it for other purposes or change the source code,                **
** you may take legal responsibility.                                         **
** In this case, There is no warranty and technical support.                  **
**                                                                            **
**  SRC-MODULE: Dcm.h                                                         **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostic Communication Manager Module               **
**                                                                            **
**  PURPOSE   : C header for Dcm                                              **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By            Description                          **
********************************************************************************
** 0.0.1     31-Dec-2019   SonDT1        AR440 Implementation                 **
** 0.0.2     14-Aug-2020   HueKM         Update SID2A scheduler as per #14836 **
** 0.0.3     13-Oct-2020   HueKM         Changes made as per #15766           **
** 0.0.4     04-Dec-2020   HueKM         Polyspace fixing as per #15175       **
** 1.0.9     31-Mar-2023   LanhLT        Refer #CP44-1637                     **
** 1.0.11    28-Apr-2023   SY Kim        Refer #CP44-1933                     **
** 1.1.0     12-Oct-2023   SY Kim        Refer #CP44-3106                     **
** 1.3.0     31-Dcm-2023   EK Kim        Refer #CP44-1515                     **
*******************************************************************************/
#ifndef DCM_H
#define DCM_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Dcm_Cfg.h"
#include "Dcm_Cbk.h"
#include "Dcm_Types.h"    
#include "Rte_Dcm_Type.h"
#include "SchM_Dcm.h"

#if(DCM_USE_ECU_SIGNAL_ENABLED == STD_ON)
#include "IoHwAb.h"
#endif

#if (DCM_DLT_USE_FUNC == STD_ON)
#include "Dlt.h"
#endif

/*******************************************************************************
**                   Instance and Functions provided for other BSW components **
*******************************************************************************/
#define DCM_INSTANCE_ID                                           ((uint8) 0x00)

/* Service Id of Dcm_Init */
#define DCM_INIT_SID                                              ((uint8) 0x01)

/* Service Id of Dcm_GetVersionInfo */
#define DCM_GET_VERSION_INFO_SID                                  ((uint8) 0x24)

/* Service Id of Dcm_DemTriggerOnDTCStatus */
#define DCM_DEM_TRIGGER_ONDTC_STATUS_SID                          ((uint8) 0x2B)

/* Service Id of Dcm_GetVin */
#define DCM_GET_VIN_SID                                           ((uint8) 0x07)

/* Dcm_<ModeName>ModeEntry needs to be updated */
#define DCM_MODENAMEMODEENTRY_SID                                 ((uint8) 0x2C)

/*******************************************************************************
**                     Functions provided to BSW modules and to SW-Cs         **
*******************************************************************************/
/* Service Id of Dcm_GetSecurityLevel */
#define DCM_GET_SECURITY_LEVEL_SID                                ((uint8) 0x0D)

/* Service Id of Dcm_GetSesCtrlType */
#define DCM_GET_SES_CTRL_TYPE_SID                                 ((uint8) 0x06)

/* Service Id of Dcm_GetObdProtocolId */
#define DCM_GET_OBD_PROTOCOL_ID_SID                               ((uint8) 0x07)

/* Service Id of Dcm_GetActiveProtocol */
#define DCM_GET_ACTIVE_PROTOCOL_SID                               ((uint8) 0x0F)

/* Service Id of Dcm_ResetToDefaultSession */
#define DCM_RESET_TO_DEFAULTSESSION_SID                           ((uint8) 0x2A)

/* Service Id of Dcm_TriggerOnEvent */
#define DCM_TRIGGER_ON_EVENT_SID                                  ((uint8) 0x2D)

/* Service Id of Dcm_SetAuthenticatedRole */
#define DCM_SET_DEAUTHENTICATED_ROLE                              ((uint8) 0x79)

/* Service Id of Dcm_SetActiveDiagnostic */
#define DCM_SET_ACTIVE_DIAGNOSTIC_SID                             ((uint8) 0x56)

/*******************************************************************************
**                     Callback Notifications                                 **
*******************************************************************************/
/* Service Id of Dcm_StartOfReception */
#define DCM_START_OF_RECEPTION_SID                                ((uint8) 0x46)

/* Service Id of Dcm_CopyRxData */
#define DCM_COPY_RXDATA_SID                                       ((uint8) 0x44)

/* Service Id of Dcm_TpRxIndication */
#define DCM_RX_INDICATION_SID                                     ((uint8) 0x45)

/* Service Id of Dcm_CopyTxData */
#define DCM_COPY_TXDATA_SID                                       ((uint8) 0x43)

/* Service Id of Dcm_TpTxConfirmation */
#define DCM_TP_TX_CONFIRMATION_SID                                ((uint8) 0x48)

/* Service Id of Dcm_TxConfirmation */
#define DCM_TX_CONFIRMATION_SID                                   ((uint8) 0x40)

/* Service Id of Dcm_ComM_NoComModeEntered */
#define DCM_COMM_NO_COM_MODE_ENTERED_SID                          ((uint8) 0x21)

/* Service Id of Dcm_ComM_SilentComModeEntered */
#define DCM_COMM_SILENT_COM_MODE_ENTERED_SID                      ((uint8) 0x22)

/* Service Id of Dcm_ComM_FullComModeEntered */
#define DCM_COMM_FULL_COM_MODE_ENTERED_SID                        ((uint8) 0x23)

/* Service Id of Sync Read and Write Data */
#define DCM_SYNC_READ_DATA_SID                                    ((uint8) 0x34)
#define DCM_SYNC_WRITE_DATA_SID                                   ((uint8) 0x35)

/* Service Id of Async Read and Write Data */
#define DCM_ASYNC_READ_DATA_SID                                   ((uint8) 0x3B)
#define DCM_ASYNC_WRITE_DATA_SID                                  ((uint8) 0x3E)

/* Service Id of read data length and condition check read */
#define DCM_READ_DATA_LENGTH_SID                                  ((uint8) 0x36)
#define DCM_CONDITION_CHECK_READ_SID                              ((uint8) 0x37)

/* Service Id of other functions */
#define DCM_VARIANT_FUNC_SID                                      ((uint8) 0x40)

/*******************************************************************************
**                     Callout Definitions                                    **
*******************************************************************************/
/* Service Id of Dcm_ReadMemory */
#define DCM_READ_MEMORY_SID                                       ((uint8) 0x26)

/* Service Id of Dcm_WriteMemory */
#define DCM_WRITE_MEMORY_SID                                      ((uint8) 0x27)

/* Service Id of Dcm_Confirmation */
#define DCM_CONFIRMATION_SID                                      ((uint8) 0x29)

/* Service Id for Dcm_SetProgConditions */
#define DCM_SETPROGCONDITIONS_SID                                 ((uint8) 0x61)

/*******************************************************************************
**                     Scheduled Functions                                    **
*******************************************************************************/
/* Service Id of Dcm_MainFunction */
#define DCM_MAIN_FUNCTION_SID                                     ((uint8) 0x25)

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
#define DCM_START_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
**                      Functions provided for other BSW components           **
*******************************************************************************/
extern FUNC(void, DCM_CODE) Dcm_Init(
  Dcm_ConfigConstPtrType ConfigPtr);

#if (DCM_VERSION_INFO_API == STD_ON)
extern FUNC(void, DCM_CODE) Dcm_GetVersionInfo(
  P2VAR(Std_VersionInfoType, AUTOMATIC, DCM_APPL_DATA) VersionInfo);
#endif

extern FUNC(Std_ReturnType, DCM_CODE) Dcm_GetVin(
  Dcm_Uint8PtrType pData);

extern FUNC(boolean, DCM_CODE) Dcm_GetGblReset(void);

/*******************************************************************************
**                      Functions provided to BSW modules and to SW-Cs        **
*******************************************************************************/
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_GetSecurityLevel(
  P2VAR(Dcm_SecLevelType, AUTOMATIC, DCM_APPL_DATA) SecLevel);

extern FUNC(Std_ReturnType, DCM_CODE) Dcm_GetSesCtrlType(
  P2VAR(Dcm_SesCtrlType, AUTOMATIC, DCM_APPL_DATA) SesCtrlType);

extern FUNC(Std_ReturnType, DCM_CODE) Dcm_TriggerOnEvent(
  uint8 RoeEventId);

extern FUNC(Std_ReturnType, DCM_CODE) Dcm_SetActiveDiagnostic(
  boolean active);

extern FUNC(Std_ReturnType, DCM_CODE) Dcm_ResetToDefaultSession(void);

extern FUNC(Std_ReturnType, DCM_CODE) Dcm_GetActiveProtocol(
  Dcm_ProtocolTypePtrType pActiveProtocolType
  , Dcm_Uint16PtrType pConnectionId
  , Dcm_Uint16PtrType pSourceTesterAddress);

extern  FUNC(Std_ReturnType, DCM_CODE) Dcm_GetObdProtocolId
  (P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) ProtocolId);

#if (DCM_AUTHENTICATION_SERVICE == STD_ON)
extern FUNC(Std_ReturnType, DCM_CODE) Dcm_SetDeauthenticatedRole(
  uint16 ConnectionId
  , Dcm_AuthenticationRoleType DeauthenticatedRole);
#endif

/*******************************************************************************
**                             Other functions                                **
*******************************************************************************/
#if (DCM_VIN_REF_CONFIGURED == STD_ON)
extern FUNC(void, DCM_CODE) Dcm_FetchVin(void);
#endif

#if (DCM_RESPONSE_ON_EVENT_SERVICE == STD_ON)
extern FUNC(void, DCM_CODE) Dcm_ROE_MainFunction(void);
#endif

#if (DCM_READ_DATA_BYPERIODICIDENTIFIER_SERVICE == STD_ON)
extern FUNC(void, DCM_CODE) Dcm_Periodic_Did_MainFunction(void);
#endif

#define DCM_STOP_SEC_CODE
#include "MemMap.h"

#endif /* DCM_H */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
