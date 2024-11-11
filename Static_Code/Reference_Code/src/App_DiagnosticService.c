/*******************************************************************************
**                            HYUNDAI MOTORS GROUP                            **
**                                                                            **
**                            All rights reserved                             **
**                                                                            **
**            You can NOT use this sample code for Product Release            **
*******************************************************************************/

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
**  FILE-NAME : App_DiagnosticService.c                                       **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostic Communication Manager Module               **
**                                                                            **
**  PURPOSE   : This file contains the API definitions for SW-C Sample of Dcm **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: yes                                       **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By              Description                        **
********************************************************************************
** 0.0.1     14-Nov-2020   HueKM           Initial Version                    **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "HwResource.h"
#include "Rte_SWC_DiagnosticService.h"
#if defined(RTE_E_SecurityAccess_L9_E_NOT_OK)
#include "HKMC_ASK_Server.h"
#endif
/*******************************************************************************
**                      Global Symbols                                        **
*******************************************************************************/
#define APPDCM_AC                                                 ((uint8) 0x0A)
#define APPDCM_RPM_HIGH                                           ((uint8) 0x07)
#define APPDCM_RPM_LOW                                            ((uint8) 0x50)

#define APPDCM_ROUTINE_START                                      ((uint8) 0x01)
#define APPDCM_ROUTINE_STOP                                       ((uint8) 0x02)
#define APPDCM_ROUTINE_REQUEST                                    ((uint8) 0x03)

#define APPDCM_MAX_PENDING_COUNT_VALUE                           ((uint16) 0xFF)

#define APPDCM_FILE_NAME_LENGTH                                ((uint16) 0x0004)
#define APPDCM_FILE_DATA_LENGTH                                ((uint64) 0x0008)
#define APPDCM_FILE_HALF_DATA_LENGTH                           ((uint64) 0x0004)

#define APPDCM_FILE_READ_BLOCK_LENGTH                          ((uint64) 0x000A)
#define APPDCM_FILE_WRITE_BLOCK_LENGTH                         ((uint64) 0x0006)

/* Generate Seed from random generator */
#if (defined(Rte_Call_HaePseudoRandomSeed_L1_RandomSeedStart) || \
     defined(Rte_Call_HaePseudoRandomSeed_L9_RandomSeedStart) || \
	 defined(Rte_Call_CsmKeyManagement_RandomSeed_L1_RandomSeed) ||\
	 defined(Rte_Call_CsmKeyManagement_RandomSeed_L9_RandomSeed))
#define APPDCM_HAE_PSEUDO_ENTROPY_LENGTH 48U
#endif

#if (defined(RTE_E_SecurityAccess_L1_E_NOT_OK) || \
     defined(RTE_E_SecurityAccess_L9_E_NOT_OK))
uint8 AppDcm_GaaRandomNum[8];
#endif

/* Routine Control Service */
uint8 AppDcm_GucEcuIsBusy = 0U;
uint8 AppDcm_GucRoutineType = 0U;
uint16 AppDcm_GusPendingCount = 0U;

uint8 AppDcm_GaaVIN[] = {
  0x31, 0x47, 0x31, 0x4A, 0x43, 0x35, 0x34, 0x34, 
  0x34, 0x52, 0x37, 0x32, 0x35, 0x32, 0x33, 0x36, 0x37};

uint8 AppDcm_GaaECT[] = {0xA6U};
uint8 AppDcm_GaaBatVolt[] = {0x8CU};
uint8 AppDcm_GaaRPM[] = {APPDCM_RPM_HIGH, APPDCM_RPM_LOW};

uint8 AppDcm_GaaWriteData[255];
uint8 AppDcm_GucActualtorValue = APPDCM_AC;

uint8 AppDcm_ReadDataInvoked = 0U;
uint8 AppDcm_WriteDataInvoked = 0U;
uint8 AppDcm_Tid1RequestControlInvoked = 0U;
uint8 AppDcm_ConditionCheckReadInvoked = 0U;
uint8 AppDcm_GetScalingInformationInvoked = 0U;

uint8 AppDcm_GucSID = 0U;
uint8 AppDcm_GucReqType = 0U;
uint16 AppDcm_GusDataSize = 0U;
uint16 AppDcm_GusSourceAddress = 0U;
Dcm_ConfirmationStatusType AppDcm_GddConfirmationStatus = 0U;

/* Store random seed value */
uint8 AppDcm_GaaSeed[4] = {0x00, 0x00, 0x00, 0x00};

/* Seed and Key value for testing purpose */
uint8 AppDcm_GaaKeyTest[4] = {0xD7, 0xBD, 0x4C, 0xEC};
uint8 AppDcm_GaaSeedTest[4] = {0x50, 0x00, 0xAC, 0x71};

#if defined(RTE_E_UploadDownloadServices_E_NOT_OK)
uint8 AppDcm_GaaProgrammingData[4] = {0x00, 0x00, 0x00, 0x00};
#endif

#if defined(RTE_E_RequestFileTransfer_E_NOT_OK)
uint8 AppDcm_LucBlockCounter;
uint8 AppDcm_GaaFileData[APPDCM_FILE_DATA_LENGTH];
uint8 AppDcm_GaaFilePathAndName[APPDCM_FILE_NAME_LENGTH];
#endif

/* Global Variables for SecurityAccess_L9 */
#if defined(APPDCM_L9_AUTRON_HSM_RANDOM_ICUM)
// TEST //#pragma ghs section bss=".gbbss.DEFAULT_GLOBALB_RAM_VAR_CLEARED"
#endif
uint8 AppDcm_GaaAdvSeed[8];
#if defined(APPDCM_L9_AUTRON_HSM_RANDOM_ICUM)
// TEST //#pragma ghs section
#endif

#if (defined(APPDCM_L9_ICUS_RANDOM) || defined(APPDCM_L9_AUTRON_HSM_RANDOM_ICUM))
Std_ReturnType AppDcm_SeedGenResult;
#endif

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define SWC_DiagnosticService_START_SEC_CODE
#include "SWC_DiagnosticService_MemMap.h"

/*******************************************************************************
** Function Name        : AppDcm_DiagnosticSessionControlNotification         **
**                                                                            **
** Description          : This function notifies session transition.          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
*******************************************************************************/
FUNC(void, SWC_DiagnosticService_CODE) 
AppDcm_DiagnosticSessionControlNotification(void)
{
  Rte_ModeType_DcmDiagnosticSessionControl LddPrevMode;
  Rte_ModeType_DcmDiagnosticSessionControl LddNextMode;

  Rte_Mode_modeNotificationPort_SessionControl_Dcm_DiagnosticSessionControlModeSwitchInterface(
    &LddPrevMode, &LddNextMode);
}

/*******************************************************************************
** Function Name        : AppDcm_StartProtocol                                **
**                                                                            **
** Description          : This function allows the application to examine     **
**                        the environment conditions and enable/disable       **
**                        further processing of the protocol.                 **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     :                                                     **
** - ProtocolType : Type of the protocol to be started.                       **
** - TesterSourceAddress : source address of the tester.                      **
** - ConnectionId : Unique connection identifier.                             **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     :                                                     **
** - Std_ReturnType                                                           **
**   - RTE_E_OK : Request was successful.                                     **
**   - RTE_E_CallbackDCMRequestServices_E_NOT_OK : Request was not successful.**
**   - RTE_E_CallbackDCMRequestServices_E_PROTOCOL_NOT_ALLOWED :              **
**     Protocol not allowed.                                                  **
**                                                                            **
*******************************************************************************/
#if defined(RTE_E_CallbackDCMRequestServices_E_NOT_OK)
FUNC(Std_ReturnType, SWC_DiagnosticService_CODE) 
AppDcm_StartProtocol(
  VAR(Dcm_ProtocolType, AUTOMATIC) ProtocolType, 
  VAR(uint16, AUTOMATIC) TesterSourceAddress, 
  VAR(uint16, AUTOMATIC) ConnectionId)
{
  Std_ReturnType LddRetVal = RTE_E_OK;

  return LddRetVal;
}
#endif

/*******************************************************************************
** Function Name        : AppDcm_StopProtocol                                 **
**                                                                            **
** Description          : This function informs the application of            **
**                        the protocol stop.                                  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     :                                                     **
** - ProtocolType : Type of the protocol to be stopped.                       **
** - TesterSourceAddress : source address of the tester.                      **
** - ConnectionId : Unique connection identifier.                             **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     :                                                     **
** - Std_ReturnType                                                           **
**   - RTE_E_OK : Request was successful.                                     **
**   - RTE_E_CallbackDCMRequestServices_E_NOT_OK : Request was not successful.**
**                                                                            **
*******************************************************************************/
#if defined(RTE_E_CallbackDCMRequestServices_E_NOT_OK)
FUNC(Std_ReturnType, SWC_DiagnosticService_CODE) 
AppDcm_StopProtocol(
  VAR(Dcm_ProtocolType, AUTOMATIC) ProtocolType, 
  VAR(uint16, AUTOMATIC) TesterSourceAddress, 
  VAR(uint16, AUTOMATIC) ConnectionId)
{
  Std_ReturnType LddRetVal = RTE_E_OK;

  return LddRetVal;
}
#endif


/*******************************************************************************
** Function Name        : ServiceRequestSupplierNotification_Confirmation     **
**                                                                            **
** Description          : This function notifies the confirmation of          **
**                        diagnostic service.                                 **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     :                                                     **
** - SID : Value of service identifier                                        **
** - ReqType : Addressing type of the request                                 **
**   (0 = physical request, 1 = functional request)                           **
** - ConnectionId : Unique connection identifier                              **
** - ConfirmationStatus : Confirmation of a successful transmission or a      **
**   transmission error of a diagnostic service.                              **
** - ProtocolType : Type of Dcm Protocol                                      **
** - TesterSourceAddress : source address of the tester                       **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     :                                                     **
** - Std_ReturnType                                                           **
**   - RTE_E_OK : Request was successful                                      **
**   - RTE_E_ServiceRequestNotification_E_NOT_OK : Request was not successful **
**                                                                            **
*******************************************************************************/
#if defined(RTE_E_ServiceRequestNotification_E_NOT_OK)
FUNC(Std_ReturnType, SWC_DiagnosticService_CODE)
ServiceRequestSupplierNotification_Confirmation(
  VAR(uint8, AUTOMATIC) SID, 
  VAR(uint8, AUTOMATIC) ReqType, 
  VAR(uint16, AUTOMATIC) ConnectionId, 
  VAR(Dcm_ConfirmationStatusType, AUTOMATIC) ConfirmationStatus, 
  VAR(Dcm_ProtocolType, AUTOMATIC) ProtocolType, 
  VAR(uint16, AUTOMATIC) TesterSourceAddress)
{
  Std_ReturnType LddRetVal = RTE_E_OK;

  AppDcm_GucSID = SID;
  AppDcm_GucReqType = ReqType;
  AppDcm_GusSourceAddress = TesterSourceAddress;
  AppDcm_GddConfirmationStatus = ConfirmationStatus;

  return LddRetVal;
}
#endif

/*******************************************************************************
** Function Name        : ServiceRequestSupplierNotification_Indication       **
**                                                                            **
** Description          : This function notifies the indication of            **
**                        diagnostic service.                                 **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     :                                                     **
** - SID : Value of service identifier                                        **
** - RequestData : Complete request data (diagnostic buffer),                 **
**   except the service ID                                                    **
** - DataSize : Number of valid bytes in the RequestData parameter            **
** - ReqType : Addressing type of the request                                 **
**   (0 = physical request, 1 = functional request)                           **
** - ConnectionId : Unique connection identifier                              **
** - ProtocolType : Type of the protocol to be indicated                      **
** - TesterSourceAddress : source address of the tester                       **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    :                                                     **
** - ErrorCode : If this operation returns value E_NOT_OK, the Dcm module     **
**   shall send a negative response with NRC code equal to the parameter      **
**   ErrorCode parameter value.                                               **
**                                                                            **
** Return parameter     :                                                     **
** - Std_ReturnType                                                           **
**   - RTE_E_OK : Request was successful                                      **
**   - RTE_E_ServiceRequestNotification_E_NOT_OK : Request was not successful **
**   - RTE_E_ServiceRequestNotification_E_REQUEST_NOT_ACCEPTED :              **
**     Request not accepted                                                   **
**                                                                            **
*******************************************************************************/
#if defined(RTE_E_ServiceRequestNotification_E_NOT_OK)
FUNC(Std_ReturnType, SWC_DiagnosticService_CODE) 
ServiceRequestSupplierNotification_Indication(
  VAR(uint8, AUTOMATIC) SID, 
  P2CONST(uint8, AUTOMATIC, RTE_APPL_CONST) RequestData, 
  VAR(uint16, AUTOMATIC) DataSize, 
  VAR(uint8, AUTOMATIC) ReqType, 
  VAR(uint16, AUTOMATIC) ConnectionId, 
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode, 
  VAR(Dcm_ProtocolType, AUTOMATIC) ProtocolType, 
  VAR(uint16, AUTOMATIC) TesterSourceAddress)
{
  Std_ReturnType LddRetVal = RTE_E_OK;

  *ErrorCode = DCM_POS_RESP;

  AppDcm_GucSID = SID;
  AppDcm_GusDataSize = DataSize;
  AppDcm_GucReqType = ReqType;
  AppDcm_GusSourceAddress = TesterSourceAddress;

  return LddRetVal;
}
#endif

/*******************************************************************************
** Function Name        : ServiceRequestManufacturerNotification_Confirmation **
**                                                                            **
** Description          : This function notifies the confirmation of          **
**                        diagnostic service.                                 **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     :                                                     **
** - SID : Value of service identifier                                        **
** - ReqType : Addressing type of the request                                 **
**   (0 = physical request, 1 = functional request)                           **
** - ConnectionId : Unique connection identifier                              **
** - ConfirmationStatus : Confirmation of a successful transmission or a      **
**   transmission error of a diagnostic service.                              **
** - ProtocolType : Type of Dcm Protocol                                      **
** - TesterSourceAddress : source address of the tester                       **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     :                                                     **
** - Std_ReturnType                                                           **
**   - RTE_E_OK : Request was successful                                      **
**   - RTE_E_ServiceRequestNotification_E_NOT_OK : Request was not successful **
**                                                                            **
*******************************************************************************/
#if defined(RTE_E_ServiceRequestNotification_E_NOT_OK)
FUNC(Std_ReturnType, SWC_DiagnosticService_CODE)
ServiceRequestManufacturerNotification_Confirmation(
  VAR(uint8, AUTOMATIC) SID, 
  VAR(uint8, AUTOMATIC) ReqType, 
  VAR(uint16, AUTOMATIC) ConnectionId, 
  VAR(Dcm_ConfirmationStatusType, AUTOMATIC) ConfirmationStatus, 
  VAR(Dcm_ProtocolType, AUTOMATIC) ProtocolType, 
  VAR(uint16, AUTOMATIC) TesterSourceAddress)
{
  Std_ReturnType LddRetVal = RTE_E_OK;

  AppDcm_GucSID = SID;
  AppDcm_GucReqType = ReqType;
  AppDcm_GusSourceAddress = TesterSourceAddress;
  AppDcm_GddConfirmationStatus = ConfirmationStatus;

  return LddRetVal;
}
#endif

/*******************************************************************************
** Function Name        : ServiceRequestManufacturerNotification_Indication   **
**                                                                            **
** Description          : This function notifies the confirmation of          **
**                        diagnostic service.                                 **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     :                                                     **
** - SID : Value of service identifier                                        **
** - RequestData : Complete request data (diagnostic buffer),                 **
**   except the service ID                                                    **
** - DataSize : Number of valid bytes in the RequestData parameter            **
** - ReqType : Addressing type of the request                                 **
**   (0 = physical request, 1 = functional request)                           **
** - ConnectionId : Unique connection identifier                              **
** - ProtocolType : Type of the protocol to be indicated                      **
** - TesterSourceAddress : source address of the tester                       **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    :                                                     **
** - ErrorCode : If this operation returns value E_NOT_OK, the Dcm module     **
**   shall send a negative response with NRC code equal to the parameter      **
**   ErrorCode parameter value.                                               **
**                                                                            **
** Return parameter     :                                                     **
** - Std_ReturnType                                                           **
**   - RTE_E_OK : Request was successful                                      **
**   - RTE_E_ServiceRequestNotification_E_NOT_OK : Request was not successful **
**   - RTE_E_ServiceRequestNotification_E_REQUEST_NOT_ACCEPTED :              **
**     Request not accepted                                                   **
**                                                                            **
*******************************************************************************/
#if defined(RTE_E_ServiceRequestNotification_E_NOT_OK)
FUNC(Std_ReturnType, SWC_DiagnosticService_CODE)
ServiceRequestManufacturerNotification_Indication(
  VAR(uint8, AUTOMATIC) SID, 
  P2CONST(uint8, AUTOMATIC, RTE_APPL_CONST) RequestData, 
  VAR(uint16, AUTOMATIC) DataSize, 
  VAR(uint8, AUTOMATIC) ReqType, 
  VAR(uint16, AUTOMATIC) ConnectionId, 
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode, 
  VAR(Dcm_ProtocolType, AUTOMATIC) ProtocolType, 
  VAR(uint16, AUTOMATIC) TesterSourceAddress)
{
  Std_ReturnType LddRetVal = RTE_E_OK;

  *ErrorCode = DCM_POS_RESP;

  AppDcm_GucSID = SID;
  AppDcm_GusDataSize = DataSize;
  AppDcm_GucReqType = ReqType;
  AppDcm_GusSourceAddress = TesterSourceAddress;

  return LddRetVal;
}
#endif


/*******************************************************************************
** Function Name        : AppDcm_ConditionCheckRead_ActuatorControl           **
**                                                                            **
** Description          : This function requests to the application if the    **
**                        conditions to read the Data are correct.            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    :                                                     **
** - ErrorCode : If this operation returns value E_NOT_OK, the Dcm module     **
**   shall send a negative response with NRC code equal to the parameter      **
**   ErrorCode parameter value.                                               **
**                                                                            **
** Return parameter     :                                                     **
** - Std_ReturnType                                                           **
**   - RTE_E_OK : Request was successful.                                     **
**   - RTE_E_DataServices_ActuatorControl_E_NOT_OK :                          **
**     Request was not successful.                                            **
**                                                                            **
*******************************************************************************/
#if defined(RTE_E_DataServices_ActuatorControl_E_NOT_OK)
FUNC(Std_ReturnType, SWC_DiagnosticService_CODE) 
AppDcm_ConditionCheckRead_ActuatorControl(
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode)
{
  Std_ReturnType LddRetVal;

  if (1U == AppDcm_GucEcuIsBusy)
  {
    AppDcm_GucEcuIsBusy = 0U;

    LddRetVal = RTE_E_DataServices_ActuatorControl_E_NOT_OK;
    *ErrorCode = DCM_E_CONDITIONSNOTCORRECT;
  }
  else
  {
    LddRetVal = RTE_E_OK;
    *ErrorCode = DCM_POS_RESP;
  }

  AppDcm_ConditionCheckReadInvoked++;
  return LddRetVal;
}
#endif

/*******************************************************************************
** Function Name        : AppDcm_FreezeCurrentState_ActuatorControl           **
**                                                                            **
** Description          : This function requests to the application to freeze **
**                        the current state of an IOControl.                  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    :                                                     **
** - ErrorCode : If this operation returns value E_NOT_OK, the Dcm module     **
**   shall send a negative response with NRC code equal to the parameter      **
**   ErrorCode parameter value.                                               **
**                                                                            **
** Return parameter     :                                                     **
** - Std_ReturnType                                                           **
**   - RTE_E_OK : Request was successful                                      **
**   - RTE_E_DataServices_ActuatorControl_E_NOT_OK :                          **
**     Request was not successful                                             **
**                                                                            **
*******************************************************************************/
#if defined(RTE_E_DataServices_ActuatorControl_E_NOT_OK)
FUNC(Std_ReturnType, SWC_DiagnosticService_CODE) 
AppDcm_FreezeCurrentState_ActuatorControl(
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode)
{
  Std_ReturnType LddRetVal;

  if (1U == AppDcm_GucEcuIsBusy)
  {
    AppDcm_GucEcuIsBusy = 0U;

    LddRetVal = RTE_E_DataServices_ActuatorControl_E_NOT_OK;
    *ErrorCode = DCM_E_CONDITIONSNOTCORRECT;
  }
  else
  {
    LddRetVal = RTE_E_OK;
    *ErrorCode = DCM_POS_RESP;
  }

  return LddRetVal;
}
#endif

/*******************************************************************************
** Function Name        : AppDcm_ReadData_ActuatorControl                     **
**                                                                            **
** Description          : This function requests to the application a data    **
**                        value of a DID.                                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    :                                                     **
** - Data : Buffer where the requested data shall be copied to                **
**                                                                            **
** Return parameter     :                                                     **
** - Std_ReturnType                                                           **
**   - RTE_E_OK : Request was successful                                      **
**   - RTE_E_DataServices_ActuatorControl_E_NOT_OK :                          **
**     Request was not successful                                             **
**                                                                            **
*******************************************************************************/
#if defined(RTE_E_DataServices_ActuatorControl_E_NOT_OK)
FUNC(Std_ReturnType, SWC_DiagnosticService_CODE) 
AppDcm_ReadData_ActuatorControl(
  P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) Data)
{
  Std_ReturnType LddRetVal = RTE_E_OK;

  Data[0] = AppDcm_GucActualtorValue;

  AppDcm_ReadDataInvoked++;
  return LddRetVal;
}
#endif

/*******************************************************************************
** Function Name        : AppDcm_WriteData_ActuatorControl                    **
**                                                                            **
** Description          : This function requests the application to write     **
**                        a data value of a DID.                              **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     :                                                     **
** - Data : Buffer containing the data to be written                          **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    :                                                     **
** - ErrorCode : If this operation returns value E_NOT_OK, the Dcm module     **
**   shall send a negative response with NRC code equal to the parameter      **
**   ErrorCode parameter value.                                               **
**                                                                            **
** Return parameter     :                                                     **
** - Std_ReturnType                                                           **
**   - RTE_E_OK : Request was successful                                      **
**   - RTE_E_DataServices_ActuatorControl_E_NOT_OK :                          **
**     Request was not successful                                             **
**                                                                            **
*******************************************************************************/
#if defined(RTE_E_DataServices_ActuatorControl_E_NOT_OK)
FUNC(Std_ReturnType, SWC_DiagnosticService_CODE) 
AppDcm_WriteData_ActuatorControl(
  P2CONST(uint8, AUTOMATIC, RTE_APPL_CONST) Data, 
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode)
{
  Std_ReturnType LddRetVal;

  if (1U == AppDcm_GucEcuIsBusy)
  {
    AppDcm_GucEcuIsBusy = 0U;

    LddRetVal = RTE_E_DataServices_ActuatorControl_E_NOT_OK;
    *ErrorCode = DCM_E_CONDITIONSNOTCORRECT;
  }
  else
  {
    AppDcm_GucActualtorValue = Data[0];

    LddRetVal = RTE_E_OK;
    *ErrorCode = DCM_POS_RESP;
  }

  AppDcm_WriteDataInvoked++;
  return LddRetVal;
}
#endif

/*******************************************************************************
** Function Name        : AppDcm_ResetToDefault_ActuatorControl               **
**                                                                            **
** Description          : This function requests to the application to reset  **
**                        an IOControl to default value.                      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    :                                                     **
** - ErrorCode : If this operation returns value E_NOT_OK, the Dcm module     **
**   shall send a negative response with NRC code equal to the parameter      **
**   ErrorCode parameter value.                                               **
**                                                                            **
** Return parameter     :                                                     **
** - Std_ReturnType                                                           **
**   - RTE_E_OK : Request was successful                                      **
**   - RTE_E_DataServices_ActuatorControl_E_NOT_OK :                          **
**     Request was not successful                                             **
**                                                                            **
*******************************************************************************/
#if defined(RTE_E_DataServices_ActuatorControl_E_NOT_OK)
FUNC(Std_ReturnType, SWC_DiagnosticService_CODE) 
AppDcm_ResetToDefault_ActuatorControl(
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode)
{
  Std_ReturnType LddRetVal;

  if (1U == AppDcm_GucEcuIsBusy)
  {
    AppDcm_GucEcuIsBusy = 0U;

    LddRetVal = RTE_E_DataServices_ActuatorControl_E_NOT_OK;
    *ErrorCode = DCM_E_CONDITIONSNOTCORRECT;
  }
  else
  {
    AppDcm_GucActualtorValue = APPDCM_AC;

    LddRetVal = RTE_E_OK;
    *ErrorCode = DCM_POS_RESP;
  }

  return LddRetVal;
}
#endif

/*******************************************************************************
** Function Name        : AppDcm_ReturnControlToECU_ActuatorControl           **
**                                                                            **
** Description          : This function requests to the application to return **
**                        control to ECU of an IOControl.                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    :                                                     **
** - ErrorCode : If this operation returns value E_NOT_OK, the Dcm module     **
**   shall send a negative response with NRC code equal to the parameter      **
**   ErrorCode parameter value.                                               **
**                                                                            **
** Return parameter     :                                                     **
** - Std_ReturnType                                                           **
**   - RTE_E_OK : Request was successful                                      **
**   - RTE_E_DataServices_ActuatorControl_E_NOT_OK :                          **
**     Request was not successful                                             **
**                                                                            **
*******************************************************************************/
#if defined(RTE_E_DataServices_ActuatorControl_E_NOT_OK)
FUNC(Std_ReturnType, SWC_DiagnosticService_CODE) 
AppDcm_ReturnControlToECU_ActuatorControl(
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode)
{
  Std_ReturnType LddRetVal;

  if (1U == AppDcm_GucEcuIsBusy)
  {
    AppDcm_GucEcuIsBusy = 0U;

    LddRetVal = RTE_E_DataServices_ActuatorControl_E_NOT_OK;
    *ErrorCode = DCM_E_CONDITIONSNOTCORRECT;
  }
  else
  {
    AppDcm_GucActualtorValue = APPDCM_AC;

    LddRetVal = RTE_E_OK;
    *ErrorCode = DCM_POS_RESP;
  }

  return LddRetVal;
}
#endif

/*******************************************************************************
** Function Name        : AppDcm_ShortTermAdjustment_ActuatorControl          **
**                                                                            **
** Description          : This function requests to the application to adjust **
**                        the IO signal.                                      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     :                                                     **
** - ControlStateInfo : ControlState information contained in                 **
**   the ControlOptionRecord parameter of the InputOutputControlByIdentifier  **
**   diagnostic request.                                                      **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    :                                                     **
** - ErrorCode : If this operation returns value E_NOT_OK, the Dcm module     **
**   shall send a negative response with NRC code equal to the parameter      **
**   ErrorCode parameter value.                                               **
**                                                                            **
** Return parameter     :                                                     **
** - Std_ReturnType                                                           **
**   - RTE_E_OK : Request was successful                                      **
**   - RTE_E_DataServices_ActuatorControl_E_NOT_OK :                          **
**     Request was not successful                                             **
**                                                                            **
*******************************************************************************/
#if defined(RTE_E_DataServices_ActuatorControl_E_NOT_OK)
FUNC(Std_ReturnType, SWC_DiagnosticService_CODE) 
AppDcm_ShortTermAdjustment_ActuatorControl(
  P2CONST(uint8, AUTOMATIC, RTE_APPL_CONST) ControlStateInfo, 
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode)
{
  Std_ReturnType LddRetVal;

  if (1U == AppDcm_GucEcuIsBusy)
  {
    AppDcm_GucEcuIsBusy = 0U;

    LddRetVal = RTE_E_DataServices_ActuatorControl_E_NOT_OK;
    *ErrorCode = DCM_E_CONDITIONSNOTCORRECT;
  }
  else
  {
    AppDcm_GucActualtorValue = ControlStateInfo[0];

    LddRetVal = RTE_E_OK;
    *ErrorCode = DCM_POS_RESP;
  }

  return LddRetVal;
}
#endif


/*******************************************************************************
** Function Name        : AppDcm_ConditionCheckRead_SystemSupplierECUHardware **
**                        VersionNumber                                       **
**                                                                            **
** Description          : This function requests to the application if the    **
**                        conditions to read the Data are correct.            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    :                                                     **
** - ErrorCode : If this operation returns value E_NOT_OK, the Dcm module     **
**   shall send a negative response with NRC code equal to the parameter      **
**   ErrorCode parameter value.                                               **
**                                                                            **
** Return parameter     :                                                     **
** - Std_ReturnType                                                           **
**   - RTE_E_OK : Request was successful                                      **
**   - RTE_E_DataServices_SystemSupplierECUHardwareVersionNumber_E_NOT_OK :   **
**     Request was not successful                                             **
**                                                                            **
*******************************************************************************/
#if defined(RTE_E_DataServices_SystemSupplierECUHardwareVersionNumber_E_NOT_OK)
FUNC(Std_ReturnType, SWC_DiagnosticService_CODE)
AppDcm_ConditionCheckRead_SystemSupplierECUHardwareVersionNumber(
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode)
{
  Std_ReturnType LddRetVal = RTE_E_OK;

  *ErrorCode = DCM_POS_RESP;

  return LddRetVal;
}
#endif

/*******************************************************************************
** Function Name        : AppDcm_ReadData_SystemSupplierECUHardware           **
**                        VersionNumber                                       **
**                                                                            **
** Description          : This function requests to the application a data    **
**                        value of a DID.                                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    :                                                     **
** - Data : Buffer where the requested data shall be copied to                **
**                                                                            **
** Return parameter     :                                                     **
** - Std_ReturnType                                                           **
**   - RTE_E_OK : Request was successful                                      **
**   - RTE_E_DataServices_SystemSupplierECUHardwareVersionNumber_E_NOT_OK :   **
**     Request was not successful                                             **
**                                                                            **
*******************************************************************************/
#if defined(RTE_E_DataServices_SystemSupplierECUHardwareVersionNumber_E_NOT_OK)
FUNC(Std_ReturnType, SWC_DiagnosticService_CODE)
AppDcm_ReadData_SystemSupplierECUHardwareVersionNumber(
  P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) Data)
{
  Std_ReturnType LddRetVal = RTE_E_OK;

  Data[0] = 0x00U;

  return LddRetVal;
}
#endif

/*******************************************************************************
** Function Name        : AppDcm_ConditionCheckRead_SystemSupplierECU         **
**                        SoftwareNumber                                      **
**                                                                            **
** Description          : This function requests to the application if the    **
**                        conditions to read the Data are correct.            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    :                                                     **
** - ErrorCode : If this operation returns value E_NOT_OK, the Dcm module     **
**   shall send a negative response with NRC code equal to the parameter      **
**   ErrorCode parameter value.                                               **
**                                                                            **
** Return parameter     :                                                     **
** - Std_ReturnType                                                           **
**   - RTE_E_OK : Request was successful                                      **
**   - RTE_E_DataServices_SystemSupplierECUSoftwareNumber_E_NOT_OK :          **
**     Request was not successful                                             **
**                                                                            **
*******************************************************************************/
#if defined(RTE_E_DataServices_SystemSupplierECUSoftwareNumber_E_NOT_OK)
FUNC(Std_ReturnType, SWC_DiagnosticService_CODE)
AppDcm_ConditionCheckRead_SystemSupplierECUSoftwareNumber(
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode)
{
  Std_ReturnType LddRetVal = RTE_E_OK;

  *ErrorCode = DCM_POS_RESP;

  return LddRetVal;
}
#endif

/*******************************************************************************
** Function Name        : AppDcm_ReadData_SystemSupplierECUSoftwareNumber     **
**                                                                            **
** Description          : This function requests to the application a data    **
**                        value of a DID.                                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    :                                                     **
** - Data : Buffer where the requested data shall be copied to                **
**                                                                            **
** Return parameter     :                                                     **
** - Std_ReturnType                                                           **
**   - RTE_E_OK : Request was successful                                      **
**   - RTE_E_DataServices_SystemSupplierECUSoftwareNumber_E_NOT_OK :          **
**     Request was not successful                                             **
**                                                                            **
*******************************************************************************/
#if defined(RTE_E_DataServices_SystemSupplierECUSoftwareNumber_E_NOT_OK)
FUNC(Std_ReturnType, SWC_DiagnosticService_CODE)
AppDcm_ReadData_SystemSupplierECUSoftwareNumber(
  P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) Data)
{
  Std_ReturnType LddRetVal = RTE_E_OK;

  Data[0] = 0x00U;

  return LddRetVal;
}
#endif

/*******************************************************************************
** Function Name        : AppDcm_ConditionCheckRead_VehicleManufacturerECU    **
**                        SoftwareVersionNumber                               **
**                                                                            **
** Description          : This function requests to the application if the    **
**                        conditions to read the Data are correct.            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    :                                                     **
** - ErrorCode : If this operation returns value E_NOT_OK, the Dcm module     **
**   shall send a negative response with NRC code equal to the parameter      **
**   ErrorCode parameter value.                                               **
**                                                                            **
** Return parameter     :                                                     **
** - Std_ReturnType                                                           **
**   - RTE_E_OK : Request was successful                                      **
**   - RTE_E_DataServices_VehicleManufacturerECUSoftwareVersionNumber_E_NOT_OK**
**     : Request was not successful                                           **
**                                                                            **
*******************************************************************************/
#if defined(RTE_E_DataServices_VehicleManufacturerECUSoftwareVersionNumber_E_NOT_OK)
FUNC(Std_ReturnType, SWC_DiagnosticService_CODE)
AppDcm_ConditionCheckRead_VehicleManufacturerECUSoftwareVersionNumber(
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode)
{
  Std_ReturnType LddRetVal = RTE_E_OK;

  *ErrorCode = DCM_POS_RESP;

  return LddRetVal;
}
#endif

/*******************************************************************************
** Function Name        : AppDcm_ReadData_VehicleManufacturerECUSoftware      **
**                        VersionNumber                                       **
**                                                                            **
** Description          : This function requests to the application a data    **
**                        value of a DID.                                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    :                                                     **
** - Data : Buffer where the requested data shall be copied to                **
**                                                                            **
** Return parameter     :                                                     **
** - Std_ReturnType                                                           **
**   - RTE_E_OK : Request was successful                                      **
**   - RTE_E_DataServices_VehicleManufacturerECUSoftwareVersionNumber_E_NOT_OK**
**     : Request was not successful                                           **
**                                                                            **
*******************************************************************************/
#if defined(RTE_E_DataServices_VehicleManufacturerECUSoftwareVersionNumber_E_NOT_OK)
FUNC(Std_ReturnType, SWC_DiagnosticService_CODE)
AppDcm_ReadData_VehicleManufacturerECUSoftwareVersionNumber(
  P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) Data)
{
  Std_ReturnType LddRetVal = RTE_E_OK;

  Data[0] = 0x00U;

  return LddRetVal;
}
#endif

/*******************************************************************************
** Function Name        : AppDcm_ConditionCheckRead_VehicleSpeed              **
**                                                                            **
** Description          : This function requests to the application if the    **
**                        conditions to read the Data are correct.            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    :                                                     **
** - ErrorCode : If this operation returns value E_NOT_OK, the Dcm module     **
**   shall send a negative response with NRC code equal to the parameter      **
**   ErrorCode parameter value.                                               **
**                                                                            **
** Return parameter     :                                                     **
** - Std_ReturnType                                                           **
**   - RTE_E_OK : Request was successful                                      **
**   - RTE_E_DataServices_VehicleSpeed_E_NOT_OK : Request was not successful  **
**                                                                            **
*******************************************************************************/
#if defined(RTE_E_DataServices_VehicleSpeed_E_NOT_OK)
FUNC(Std_ReturnType, SWC_DiagnosticService_CODE)
AppDcm_ConditionCheckRead_VehicleSpeed(
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode)
{
  Std_ReturnType LddRetVal = RTE_E_OK;

  *ErrorCode = DCM_POS_RESP;

  return LddRetVal;
}
#endif

/*******************************************************************************
** Function Name        : AppDcm_GetScalingInformation_VehicleSpeed           **
**                                                                            **
** Description          : This function requests to the application           **
**                        for the scaling information of a Data.              **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    :                                                     **
** - ScalingInfo : Scaling information (scalingByte and scalingByteExtension) **
** - ErrorCode : If this operation returns value E_NOT_OK, the Dcm module     **
**   shall send a negative response with NRC code equal to the parameter      **
**   ErrorCode parameter value.                                               **
**                                                                            **
** Return parameter     :                                                     **
** - Std_ReturnType                                                           **
**   - RTE_E_OK : Request was successful                                      **
**   - RTE_E_DataServices_VehicleSpeed_E_NOT_OK : Request was not successful  **
**                                                                            **
*******************************************************************************/
#if defined(RTE_E_DataServices_VehicleSpeed_E_NOT_OK)
FUNC(Std_ReturnType, SWC_DiagnosticService_CODE)
AppDcm_GetScalingInformation_VehicleSpeed(
  P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) ScalingInfo, 
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode)
{
  Std_ReturnType LddRetVal = RTE_E_OK;

  /*
    s#1 {unsigned numeric, 1 data byte}        0x01
    s#2 {formula, 5 data bytes}                0x95
    e#2 [byte#1] {formulaIdentifier=C0*x+C1}   0x00
    e#2 [byte#2] {C0 high byte}                0xE0
    e#2 [byte#3] {C0 low byte}[C0=75*10P-2P]   0x4B
    e#2 [byte#4] {C1 high byte}                0x00
    e#2 [byte#5] {C1 low byte}[C1=30*10P0P]    0x1E
    s#3 {unit / format, 1 data byte}           0xA1
    e#3 [byte#1]  {unit ID, km/h}              0x30
  */

  ScalingInfo[0] = (uint8) 0x01U;
  ScalingInfo[1] = (uint8) 0x95U;
  ScalingInfo[2] = (uint8) 0x00U;
  ScalingInfo[3] = (uint8) 0xE0U;
  ScalingInfo[4] = (uint8) 0x4BU;
  ScalingInfo[5] = (uint8) 0x00U;
  ScalingInfo[6] = (uint8) 0x1EU;
  ScalingInfo[7] = (uint8) 0xA1U;
  ScalingInfo[8] = (uint8) 0x30U;

  *ErrorCode = DCM_POS_RESP;
  AppDcm_GetScalingInformationInvoked++;

  return LddRetVal;
}
#endif

/*******************************************************************************
** Function Name        : AppDcm_ReadData_VehicleSpeed                        **
**                                                                            **
** Description          : This function requests to the application a data    **
**                        value of a DID.                                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    :                                                     **
** - Data : Buffer where the requested data shall be copied to                **
**                                                                            **
** Return parameter     :                                                     **
** - Std_ReturnType                                                           **
**   - RTE_E_OK : Request was successful                                      **
**   - RTE_E_DataServices_VehicleSpeed_E_NOT_OK : Request was not successful  **
**                                                                            **
*******************************************************************************/
#if defined(RTE_E_DataServices_VehicleSpeed_E_NOT_OK)
FUNC(Std_ReturnType, SWC_DiagnosticService_CODE)
AppDcm_ReadData_VehicleSpeed(
  P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) Data)
{
  Std_ReturnType LddRetVal = RTE_E_OK;

  Data[0] = 0x00U;

  return LddRetVal;
}
#endif


/*******************************************************************************
** Function Name        : AppDcm_ConditionCheckRead_VINDataIdentifier         **
**                                                                            **
** Description          : This function requests to the application if the    **
**                        conditions to read the Data are correct.            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    :                                                     **
** - ErrorCode : If this operation returns value E_NOT_OK, the Dcm module     **
**   shall send a negative response with NRC code equal to the parameter      **
**   ErrorCode parameter value.                                               **
**                                                                            **
** Return parameter     :                                                     **
** - Std_ReturnType                                                           **
**   - RTE_E_OK : Request was successful                                      **
**   - RTE_E_DataServices_VINDataIdentifier_E_NOT_OK :                        **
**     Request was not successful                                             **
**                                                                            **
*******************************************************************************/
#if defined(RTE_E_DataServices_VINDataIdentifier_E_NOT_OK)
FUNC(Std_ReturnType, SWC_DiagnosticService_CODE)
AppDcm_ConditionCheckRead_VINDataIdentifier(
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode)
{
  Std_ReturnType LddRetVal = RTE_E_OK;

  *ErrorCode = DCM_POS_RESP;

  return LddRetVal;
}
#endif

/*******************************************************************************
** Function Name        : AppDcm_ReadData_VINDataIdentifier                   **
**                                                                            **
** Description          : This function requests to the application a data    **
**                        value of a DID.                                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    :                                                     **
** - Data : Buffer where the requested data shall be copied to                **
**                                                                            **
** Return parameter     :                                                     **
** - Std_ReturnType                                                           **
**   - RTE_E_OK : Request was successful                                      **
**   - RTE_E_DataServices_VINDataIdentifier_E_NOT_OK :                        **
**     Request was not successful                                             **
**                                                                            **
*******************************************************************************/
#if defined(RTE_E_DataServices_VINDataIdentifier_E_NOT_OK)
FUNC(Std_ReturnType, SWC_DiagnosticService_CODE)
AppDcm_ReadData_VINDataIdentifier(
  P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) Data)
{
  Std_ReturnType LddRetVal = RTE_E_OK;

  for(uint16 LusIndex = 0U; LusIndex < 17U; LusIndex++)
  {
    Data[LusIndex] = AppDcm_GaaVIN[LusIndex];
  }

  return LddRetVal;
}
#endif

/*******************************************************************************
** Function Name        : AppDcm_WriteData_VINDataIdentifier                  **
**                                                                            **
** Description          : This function requests the application to write     **
**                        a data value of a DID.                              **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     :                                                     **
** - Data : Buffer containing the data to be written                          **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    :                                                     **
** - ErrorCode : If this operation returns value E_NOT_OK, the Dcm module     **
**   shall send a negative response with NRC code equal to the parameter      **
**   ErrorCode parameter value.                                               **
**                                                                            **
** Return parameter     :                                                     **
** - Std_ReturnType                                                           **
**   - RTE_E_OK : Request was successful                                      **
**   - RTE_E_DataServices_VINDataIdentifier_E_NOT_OK :                        **
**     Request was not successful                                             **
**                                                                            **
*******************************************************************************/
#if defined(RTE_E_DataServices_VINDataIdentifier_E_NOT_OK)
FUNC(Std_ReturnType, SWC_DiagnosticService_CODE)
AppDcm_WriteData_VINDataIdentifier(
  P2CONST(uint8, AUTOMATIC, RTE_APPL_CONST) Data, 
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode)
{
  Std_ReturnType LddRetVal;

  if (Data[0] == 0x57U)
  {
    for(uint16 LusIndex = 0U; LusIndex < 17U; LusIndex++)
    {
      AppDcm_GaaVIN[LusIndex] = Data[LusIndex];
    }

    LddRetVal = RTE_E_OK;
    *ErrorCode = DCM_POS_RESP;
  }
  else
  {
    *ErrorCode = DCM_E_REQUESTOUTOFRANGE;
    LddRetVal = RTE_E_DataServices_VINDataIdentifier_E_NOT_OK;
  }

  return LddRetVal;
}
#endif

/*******************************************************************************
** Function Name        : AppDcm_GetScalingInformation_VINDataIdentifier      **
**                                                                            **
** Description          : This function requests to the application           **
**                        for the scaling information of a Data.              **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    :                                                     **
** - ScalingInfo : Scaling information (scalingByte and scalingByteExtension) **
** - ErrorCode : If this operation returns value E_NOT_OK, the Dcm module     **
**   shall send a negative response with NRC code equal to the parameter      **
**   ErrorCode parameter value.                                               **
**                                                                            **
** Return parameter     :                                                     **
** - Std_ReturnType                                                           **
**   - RTE_E_OK : Request was successful                                      **
**   - RTE_E_DataServices_VINDataIdentifier_E_NOT_OK :                        **
**     Request was not successful                                             **
**                                                                            **
*******************************************************************************/
#if defined(RTE_E_DataServices_VINDataIdentifier_E_NOT_OK)
FUNC(Std_ReturnType, SWC_DiagnosticService_CODE)
AppDcm_GetScalingInformation_VINDataIdentifier(
  P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) ScalingInfo, 
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode)
{
  Std_ReturnType LddRetVal = RTE_E_OK;

  /*
    0x6F = scalingByte#1 {ASCII, 15 data bytes}
    0x62 = scalingByte#2 {ASCII, 2 data bytes}
  */

  ScalingInfo[0] = 0x6FU;
  ScalingInfo[1] = 0x62U;

  *ErrorCode = DCM_POS_RESP;

  return LddRetVal;
}
#endif

/*******************************************************************************
** Function Name        : AppDcm_ConditionCheckRead_BatVolt                   **
**                                                                            **
** Description          : This function requests to the application if the    **
**                        conditions to read the Data are correct.            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    :                                                     **
** - ErrorCode : If this operation returns value E_NOT_OK, the Dcm module     **
**   shall send a negative response with NRC code equal to the parameter      **
**   ErrorCode parameter value.                                               **
**                                                                            **
** Return parameter     :                                                     **
** - Std_ReturnType                                                           **
**   - RTE_E_OK : Request was successful                                      **
**   - RTE_E_DataServices_BatVolt_E_NOT_OK : Request was not successful       **
**                                                                            **
*******************************************************************************/
#if defined(RTE_E_DataServices_BatVolt_E_NOT_OK)
FUNC(Std_ReturnType, SWC_DiagnosticService_CODE) 
AppDcm_ConditionCheckRead_BatVolt(
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode)
{
  Std_ReturnType LddRetVal = RTE_E_OK;

  *ErrorCode = DCM_POS_RESP;

  return LddRetVal;
}
#endif

/*******************************************************************************
** Function Name        : AppDcm_ReadData_BatVolt                             **
**                                                                            **
** Description          : This function requests to the application a data    **
**                        value of a DID.                                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    :                                                     **
** - Data : Buffer where the requested data shall be copied to                **
**                                                                            **
** Return parameter     :                                                     **
** - Std_ReturnType                                                           **
**   - RTE_E_OK : Request was successful                                      **
**   - RTE_E_DataServices_BatVolt_E_NOT_OK : Request was not successful       **
**                                                                            **
*******************************************************************************/
#if defined(RTE_E_DataServices_BatVolt_E_NOT_OK)
FUNC(Std_ReturnType, SWC_DiagnosticService_CODE)
AppDcm_ReadData_BatVolt(
  P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) Data)
{
  Std_ReturnType LddRetVal = RTE_E_OK;

  Data[0] = AppDcm_GaaBatVolt[0];

  return LddRetVal;
}
#endif

/*******************************************************************************
** Function Name        : AppDcm_WriteData_BatVolt                            **
**                                                                            **
** Description          : This function requests the application to write     **
**                        a data value of a DID.                              **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     :                                                     **
** - Data : Buffer containing the data to be written                          **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    :                                                     **
** - ErrorCode : If this operation returns value E_NOT_OK, the Dcm module     **
**   shall send a negative response with NRC code equal to the parameter      **
**   ErrorCode parameter value.                                               **
**                                                                            **
** Return parameter     :                                                     **
** - Std_ReturnType                                                           **
**   - RTE_E_OK : Request was successful                                      **
**   - RTE_E_DataServices_BatVolt_E_NOT_OK : Request was not successful       **
**                                                                            **
*******************************************************************************/
#if defined(RTE_E_DataServices_BatVolt_E_NOT_OK)
FUNC(Std_ReturnType, SWC_DiagnosticService_CODE)
AppDcm_WriteData_BatVolt(
  P2CONST(uint8, AUTOMATIC, RTE_APPL_CONST) Data, 
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode)
{
  Std_ReturnType LddRetVal = RTE_E_OK;

  *ErrorCode = DCM_POS_RESP;
  AppDcm_GaaBatVolt[0] = Data[0];

  return LddRetVal;
}
#endif

/*******************************************************************************
** Function Name        : AppDcm_ConditionCheckRead_ECT                       **
**                                                                            **
** Description          : This function requests to the application if the    **
**                        conditions to read the Data are correct.            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    :                                                     **
** - ErrorCode : If this operation returns value E_NOT_OK, the Dcm module     **
**   shall send a negative response with NRC code equal to the parameter      **
**   ErrorCode parameter value.                                               **
**                                                                            **
** Return parameter     :                                                     **
** - Std_ReturnType                                                           **
**   - RTE_E_OK : Request was successful                                      **
**   - RTE_E_DataServices_ECT_E_NOT_OK : Request was not successful           **
**                                                                            **
*******************************************************************************/
#if defined(RTE_E_DataServices_ECT_E_NOT_OK)
FUNC(Std_ReturnType, SWC_DiagnosticService_CODE)
AppDcm_ConditionCheckRead_ECT(
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode)
{
  Std_ReturnType LddRetVal = RTE_E_OK;

  *ErrorCode = DCM_POS_RESP;

  return LddRetVal;
}
#endif

/*******************************************************************************
** Function Name        : AppDcm_ReadData_ECT                                 **
**                                                                            **
** Description          : This function requests to the application a data    **
**                        value of a DID.                                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    :                                                     **
** - Data : Buffer where the requested data shall be copied to                **
**                                                                            **
** Return parameter     :                                                     **
** - Std_ReturnType                                                           **
**   - RTE_E_OK : Request was successful                                      **
**   - RTE_E_DataServices_ECT_E_NOT_OK : Request was not successful           **
**                                                                            **
*******************************************************************************/
#if defined(RTE_E_DataServices_ECT_E_NOT_OK)
FUNC(Std_ReturnType, SWC_DiagnosticService_CODE)
AppDcm_ReadData_ECT(
  P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) Data)
{
  Std_ReturnType LddRetVal = RTE_E_OK;

  Data[0] = AppDcm_GaaECT[0];

  return LddRetVal;
}
#endif

/*******************************************************************************
** Function Name        : AppDcm_WriteData_ECT                                **
**                                                                            **
** Description          : This function requests the application to write     **
**                        a data value of a DID.                              **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     :                                                     **
** - Data : Buffer containing the data to be written                          **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    :                                                     **
** - ErrorCode : If this operation returns value E_NOT_OK, the Dcm module     **
**   shall send a negative response with NRC code equal to the parameter      **
**   ErrorCode parameter value.                                               **
**                                                                            **
** Return parameter     :                                                     **
** - Std_ReturnType                                                           **
**   - RTE_E_OK : Request was successful                                      **
**   - RTE_E_DataServices_ECT_E_NOT_OK : Request was not successful           **
**                                                                            **
*******************************************************************************/
#if defined(RTE_E_DataServices_ECT_E_NOT_OK)
FUNC(Std_ReturnType, SWC_DiagnosticService_CODE)
AppDcm_WriteData_ECT(
  P2CONST(uint8, AUTOMATIC, RTE_APPL_CONST) Data, 
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode)
{
  Std_ReturnType LddRetVal = RTE_E_OK;

  *ErrorCode = DCM_POS_RESP;
  AppDcm_GaaECT[0] = Data[0];

  return LddRetVal;
}
#endif

/*******************************************************************************
** Function Name        : AppDcm_ConditionCheckRead_RPM                       **
**                                                                            **
** Description          : This function requests to the application if the    **
**                        conditions to read the Data are correct.            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    :                                                     **
** - ErrorCode : If this operation returns value E_NOT_OK, the Dcm module     **
**   shall send a negative response with NRC code equal to the parameter      **
**   ErrorCode parameter value.                                               **
**                                                                            **
** Return parameter     :                                                     **
** - Std_ReturnType                                                           **
**   - RTE_E_OK : Request was successful                                      **
**   - RTE_E_DataServices_RPM_E_NOT_OK : Request was not successful           **
**                                                                            **
*******************************************************************************/
#if defined(RTE_E_DataServices_RPM_E_NOT_OK)
FUNC(Std_ReturnType, SWC_DiagnosticService_CODE) 
AppDcm_ConditionCheckRead_RPM(
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode)
{
  Std_ReturnType LddRetVal = RTE_E_OK;

  *ErrorCode = DCM_POS_RESP;

  return LddRetVal;
}
#endif

/*******************************************************************************
** Function Name        : AppDcm_ReadData_ECT                                 **
**                                                                            **
** Description          : This function requests to the application a data    **
**                        value of a DID.                                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    :                                                     **
** - Data : Buffer where the requested data shall be copied to                **
**                                                                            **
** Return parameter     :                                                     **
** - Std_ReturnType                                                           **
**   - RTE_E_OK : Request was successful                                      **
**   - RTE_E_DataServices_RPM_E_NOT_OK : Request was not successful           **
**                                                                            **
*******************************************************************************/
#if defined(RTE_E_DataServices_RPM_E_NOT_OK)
FUNC(Std_ReturnType, SWC_DiagnosticService_CODE)
AppDcm_ReadData_RPM(
  P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) Data)
{
  Std_ReturnType LddRetVal = RTE_E_OK;

  Data[0] = AppDcm_GaaRPM[0];
  Data[1] = AppDcm_GaaRPM[1];

  return LddRetVal;
}
#endif

/*******************************************************************************
** Function Name        : AppDcm_WriteData_RPM                                **
**                                                                            **
** Description          : This function requests the application to write     **
**                        a data value of a DID.                              **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     :                                                     **
** - Data : Buffer containing the data to be written                          **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    :                                                     **
** - ErrorCode : If this operation returns value E_NOT_OK, the Dcm module     **
**   shall send a negative response with NRC code equal to the parameter      **
**   ErrorCode parameter value.                                               **
**                                                                            **
** Return parameter     :                                                     **
** - Std_ReturnType                                                           **
**   - RTE_E_OK : Request was successful                                      **
**   - RTE_E_DataServices_RPM_E_NOT_OK : Request was not successful           **
**                                                                            **
*******************************************************************************/
#if defined(RTE_E_DataServices_RPM_E_NOT_OK)
FUNC(Std_ReturnType, SWC_DiagnosticService_CODE)
AppDcm_WriteData_RPM(
  P2CONST(uint8, AUTOMATIC, RTE_APPL_CONST) Data, 
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode)
{
  Std_ReturnType LddRetVal = RTE_E_OK;

  *ErrorCode = DCM_POS_RESP;
  AppDcm_GaaRPM[0] = Data[0];
  AppDcm_GaaRPM[1] = Data[1];

  return LddRetVal;
}
#endif

/*******************************************************************************
** Function Name        : AppDcm_FreezeCurrentState_RPM                       **
**                                                                            **
** Description          : This function requests to the application to freeze **
**                        the current state of an IOControl.                  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    :                                                     **
** - ErrorCode : If this operation returns value E_NOT_OK, the Dcm module     **
**   shall send a negative response with NRC code equal to the parameter      **
**   ErrorCode parameter value. (Refer to the Rte_Dcm_Type.h)                 **
**                                                                            **
** Return parameter     :                                                     **
** - Std_ReturnType                                                           **
**   - RTE_E_OK : Request was successful                                      **
**   - RTE_E_DataServices_RPM_E_NOT_OK : Request was not successful           **
**                                                                            **
*******************************************************************************/
#if defined(RTE_E_DataServices_RPM_E_NOT_OK)
FUNC(Std_ReturnType, SWC_DiagnosticService_CODE)
AppDcm_FreezeCurrentState_RPM(
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode)
{
  Std_ReturnType LddRetVal;

  if (1U == AppDcm_GucEcuIsBusy)
  {
    AppDcm_GucEcuIsBusy = 0U;

    *ErrorCode = DCM_E_CONDITIONSNOTCORRECT;
    LddRetVal = RTE_E_DataServices_RPM_E_NOT_OK;
  }
  else
  {
    LddRetVal = RTE_E_OK;
    *ErrorCode = DCM_POS_RESP;
  }

  return LddRetVal;
}
#endif

/*******************************************************************************
** Function Name        : AppDcm_ReturnControlToECU_RPM                       **
**                                                                            **
** Description          : This function requests to the application to return **
**                        control to ECU of an IOControl.                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    :                                                     **
** - ErrorCode : If this operation returns value E_NOT_OK, the Dcm module     **
**   shall send a negative response with NRC code equal to the parameter      **
**   ErrorCode parameter value.                                               **
**                                                                            **
** Return parameter     :                                                     **
** - Std_ReturnType                                                           **
**   - RTE_E_OK : Request was successful                                      **
**   - RTE_E_DataServices_RPM_E_NOT_OK : Request was not successful           **
**                                                                            **
*******************************************************************************/
#if defined(RTE_E_DataServices_RPM_E_NOT_OK)
FUNC(Std_ReturnType, SWC_DiagnosticService_CODE)
AppDcm_ReturnControlToECU_RPM(
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode)
{
  Std_ReturnType LddRetVal;

  if (1U == AppDcm_GucEcuIsBusy)
  {
    AppDcm_GucEcuIsBusy = 0U;

    *ErrorCode = DCM_E_CONDITIONSNOTCORRECT;
    LddRetVal = RTE_E_DataServices_RPM_E_NOT_OK;
  }
  else
  {
    AppDcm_GaaRPM[0] = APPDCM_RPM_HIGH;
    AppDcm_GaaRPM[1] = APPDCM_RPM_LOW;

    LddRetVal = RTE_E_OK;
    *ErrorCode = DCM_POS_RESP;
  }

  return LddRetVal;
}
#endif

/*******************************************************************************
** Function Name        : AppDcm_ShortTermAdjustment_RPM                      **
**                                                                            **
** Description          : This function requests to the application to adjust **
**                        the IO signal.                                      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     :                                                     **
** - ControlStateInfo : ControlState information contained in the             **
**   ControlOptionRecord parameter of the InputOutputControlByIdentifier      **
**   diagnostic request                                                       **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    :                                                     **
** - ErrorCode : If this operation returns value E_NOT_OK, the Dcm module     **
**   shall send a negative response with NRC code equal to the parameter      **
**   ErrorCode parameter value.                                               **
**                                                                            **
** Return parameter     :                                                     **
** - Std_ReturnType                                                           **
**   - RTE_E_OK : Request was successful                                      **
**   - RTE_E_DataServices_RPM_E_NOT_OK : Request was not successful           **
**                                                                            **
*******************************************************************************/
#if defined(RTE_E_DataServices_RPM_E_NOT_OK)
FUNC(Std_ReturnType, SWC_DiagnosticService_CODE)
AppDcm_ShortTermAdjustment_RPM(
  P2CONST(uint8, AUTOMATIC, RTE_APPL_CONST) ControlStateInfo, 
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode)
{
  Std_ReturnType LddRetVal;

  if (1U == AppDcm_GucEcuIsBusy)
  {
    AppDcm_GucEcuIsBusy = 0U;

    *ErrorCode = DCM_E_CONDITIONSNOTCORRECT;
    LddRetVal = RTE_E_DataServices_RPM_E_NOT_OK;
  }
  else
  {
    AppDcm_GaaRPM[0] = ControlStateInfo[0];
    AppDcm_GaaRPM[1] = ControlStateInfo[1];

    LddRetVal = RTE_E_OK;
    *ErrorCode = DCM_POS_RESP;
  }

  return LddRetVal;
}
#endif

/*******************************************************************************
** Function Name        : AppDcm_IsDidAvailable_DID_0100h_0110h               **
**                                                                            **
** Description          : This function requests if a specific DID is         **
**                        available within the range or not.                  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     :                                                     **
** - DID : DID value                                                          **
** - OpStatus: Status of the current operation                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    :                                                     **
** - Supported : Indicate if the DID is available within the range.           **
**   - 1 : it is supported within the range                                   **
**   - 0 : it is not supported within the range                               **
**                                                                            **
** Return parameter     :                                                     **
** - Std_ReturnType                                                           **
**   - RTE_E_OK : Request was successful                                      **
**   - RTE_E_DataServices_DIDRange_DIDs_0100h_0110h_E_NOT_OK :                **
**     Request was not successful                                             **
**   - RTE_E_DataServices_DIDRange_DIDs_0100h_0110h_DCM_E_PENDING :           **
**     Request is not yet finished. Further call(s) required to finish.       **
*******************************************************************************/
#if defined(RTE_E_DataServices_DIDRange_DIDs_0100h_0110h_E_NOT_OK)
FUNC(Std_ReturnType, SWC_DiagnosticService_CODE) 
AppDcm_IsDidAvailable_DID_0100h_0110h(
  VAR(uint16, AUTOMATIC) DID, 
  VAR(Dcm_OpStatusType, AUTOMATIC) OpStatus, 
  P2VAR(Dcm_DidSupportedType, AUTOMATIC, RTE_APPL_DATA) Supported)
{
  Std_ReturnType LddRetVal;

  if ((DID >= 0x0100) && (DID <= 0x0109))
  {
    LddRetVal = RTE_E_OK;
    *Supported = 1U;
  }
  else
  {
    LddRetVal = RTE_E_DataServices_DIDRange_DIDs_0100h_0110h_E_NOT_OK;
    *Supported = 0U;
  }

  return LddRetVal;
}
#endif

/*******************************************************************************
** Function Name        : AppDcm_ReadDidData_DID_0100h_0110h                  **
**                                                                            **
** Description          : This function requests to the application a data    **
**                        value of a DID.                                     **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     :                                                     **
** - DID : DID value                                                          **
** - OpStatus : Status of the current operation                               **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    :                                                     **
** - Data : Buffer where the requested data shall be copied to                **
** - DataLength : Length of the data to be read                               **
** - ErrorCode : If this operation returns value E_NOT_OK, the Dcm module     **
**   shall send a negative response with NRC code equal to the parameter      **
**   ErrorCode parameter value.                                               **
**                                                                            **
** Return parameter     :                                                     **
** - Std_ReturnType                                                           **
**   - RTE_E_OK : Request was successful                                      **
**   - RTE_E_DataServices_DIDRange_DIDs_0100h_0110h_E_NOT_OK :                **
**     Request was not successful                                             **
**   - RTE_E_DataServices_DIDRange_DIDs_0100h_0110h_DCM_E_PENDING :           **
**     Request is not yet finished. Further call required to finish           **
**                                                                            **
*******************************************************************************/
#if defined(RTE_E_DataServices_DIDRange_DIDs_0100h_0110h_E_NOT_OK)
FUNC(Std_ReturnType, SWC_DiagnosticService_CODE) 
AppDcm_ReadDidData_DID_0100h_0110h(
  VAR(uint16, AUTOMATIC) DID, 
  P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) Data, 
  VAR(Dcm_OpStatusType, AUTOMATIC) OpStatus, 
  P2VAR(uint16, AUTOMATIC, RTE_APPL_DATA) DataLength, 
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode)
{
  Std_ReturnType LddRetVal = RTE_E_DataServices_DIDRange_DIDs_0100h_0110h_E_NOT_OK;

  switch (DID)
  {
    case 0x0100:
      *DataLength = 1U;
      *ErrorCode = DCM_POS_RESP;
      break;

    case 0x0101:
      *DataLength = 27U;
      *ErrorCode = DCM_POS_RESP;
      break;

    case 0x0102:
      *DataLength = 1U;
      *ErrorCode = DCM_POS_RESP;
      break;

    case 0x0103:
      *DataLength = 5U;
      *ErrorCode = DCM_POS_RESP;
      break;

    case 0x0104:
      *DataLength = 0U;
      *ErrorCode = DCM_E_CONDITIONSNOTCORRECT;
      break;

    default:
      *DataLength = 0U;
      *ErrorCode = DCM_E_CONDITIONSNOTCORRECT;
      break;
  }

  if (0U != *DataLength)
  {
    for(uint16 LusIndex = 0U; LusIndex < *DataLength; LusIndex++)
    {
      Data[LusIndex] = LusIndex + 1U;
    }

    LddRetVal = RTE_E_OK;
  }

  return LddRetVal;
}
#endif

/*******************************************************************************
** Function Name        : AppDcm_WriteDidData_DID_0100h_0110h                 **
**                                                                            **
** Description          : This function requests the application to write     **
**                        a data value of a DID.                              **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     :                                                     **
** - DID : DID value                                                          **
** - Data : Buffer containing the data to be written                          **
** - OpStatus : Status of the current operation                               **
** - DataLength : Length of the data to be written                            **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    :                                                     **
** - ErrorCode : If this operation returns value E_NOT_OK, the Dcm module     **
**   shall send a negative response with NRC code equal to the parameter      **
**   ErrorCode parameter value.                                               **
**                                                                            **
** Return parameter     :                                                     **
** - Std_ReturnType                                                           **
**   - RTE_E_OK : Request was successful                                      **
**   - RTE_E_DataServices_DIDRange_DIDs_0100h_0110h_E_NOT_OK :                **
**     Request was not successful                                             **
**   - RTE_E_DataServices_DIDRange_DIDs_0100h_0110h_DCM_E_PENDING :           **
**     Request is not yet finished. Further call required to finish           **
**                                                                            **
*******************************************************************************/
#if defined(RTE_E_DataServices_DIDRange_DIDs_0100h_0110h_E_NOT_OK)
FUNC(Std_ReturnType, SWC_DiagnosticService_CODE) 
AppDcm_WriteDidData_DID_0100h_0110h(
  VAR(uint16, AUTOMATIC) DID, 
  P2CONST(uint8, AUTOMATIC, RTE_APPL_CONST) Data, 
  VAR(Dcm_OpStatusType, AUTOMATIC) OpStatus, 
  VAR(uint16, AUTOMATIC) DataLength, 
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode)
{
  Std_ReturnType LddRetVal = RTE_E_DataServices_DIDRange_DIDs_0100h_0110h_E_NOT_OK;

  switch (DID)
  {
    case 0x0100:
    case 0x0101:
    case 0x0102:
    case 0x0103:
      for(uint16 LusIndex = 0U; LusIndex < DataLength; LusIndex++)
      {
        AppDcm_GaaWriteData[LusIndex] = Data[LusIndex];
      }

      *ErrorCode = DCM_POS_RESP;
      LddRetVal = RTE_E_OK;
      break;

    case 0x0104:
      *ErrorCode = DCM_E_CONDITIONSNOTCORRECT;
      break;

    case 0x0110:
      *ErrorCode = DCM_E_GENERALPROGRAMMINGFAILURE;
      break;

    default:
      *ErrorCode = DCM_E_CONDITIONSNOTCORRECT;
      break;
  }

  return LddRetVal;
}
#endif

/*******************************************************************************
** Function Name        : AppDcm_ReadDidRangeDataLength_DID_0100h_0110h       **
**                                                                            **
** Description          : This function requests the application to           **
**                        return the data length of a DID Range               **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     :                                                     **
** - DID : Data ID value                                                      **
** - OpStatus : Status of the current operation                               **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    :                                                     **
** - DataLength: Length of the data to be written/read                        **
**                                                                            **
** Return parameter     :                                                     **
** - Std_ReturnType                                                           **
**   - RTE_E_OK : Request was successful.                                     **
**   - RTE_E_DataServices_DIDRange_DIDs_0100h_0110h_E_NOT_OK :                **
**     Request was not successful.                                            **
**   - RTE_E_DataServices_DIDRange_DIDs_0100h_0110h_DCM_E_PENDING:            **
**     Request is not yet finished. Further call(s) required to finish.       **
**                                                                            **
*******************************************************************************/
#if defined(RTE_E_DataServices_DIDRange_DIDs_0100h_0110h_E_NOT_OK)
FUNC(Std_ReturnType, SWC_DiagnosticService_CODE) 
AppDcm_ReadDidRangeDataLength_DID_0100h_0110h(
  VAR(uint16, AUTOMATIC) DID, 
  VAR(Dcm_OpStatusType, AUTOMATIC) OpStatus, 
  P2VAR(uint16, AUTOMATIC, RTE_APPL_DATA) DataLength)
{
  Std_ReturnType LddRetVal = RTE_E_OK;

  return LddRetVal;
}
#endif

/*******************************************************************************
** Function Name        : AppDcm_RequestResults_CalibrationActuator           **
**                                                                            **
** Description          : This function requests to the application           **
**                         the result of a routine execution.                 **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     :                                                     **
** - OpStatus : Status of the current operation                               **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    :                                                     **
** - DataOut_RID_0200h_RequestOutSignal : Fixed-length Output data to provide **
**   in the routine control response.                                         **
** - ErrorCode : If this operation returns value E_NOT_OK, the Dcm module     **
**   shall send a negative response with NRC code equal to the parameter      **
**   ErrorCode parameter value.                                               **
**                                                                            **
** Return parameter     :                                                     **
** - Std_ReturnType                                                           **
**   - RTE_E_OK : Request was successful                                      **
**   - RTE_E_RoutineServices_RID_0200h_CalibrationActuator_E_NOT_OK :         **
**     Request was not successful                                             **
**   - RTE_E_RoutineServices_RID_0200h_CalibrationActuator_DCM_E_PENDING :    **
**     Request is not yet finished. Further call required to finish           **
**   - RTE_E_RoutineServices_RID_0200h_CalibrationActuator_DCM_E_FORCE_RCRRP :**
**     application request the transmission of a response Response Pending    **
**     (NRC 0x78)                                                             **
**                                                                            **
*******************************************************************************/
#if defined(RTE_E_RoutineServices_RID_0200h_CalibrationActuator_E_NOT_OK)
FUNC(Std_ReturnType, SWC_DiagnosticService_CODE)
AppDcm_RequestResults_CalibrationActuator(
  VAR(Dcm_OpStatusType, AUTOMATIC) OpStatus,
  P2VAR(Dcm_RequestDataOut_RID_0200h_CalibrationActuator_RID_0200h_RequestOutSignalType, \
    AUTOMATIC, RTE_APPL_DATA) DataOut_RID_0200h_RequestOutSignal,
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode)
{
  Std_ReturnType LddRetVal;

  if ((APPDCM_ROUTINE_STOP == AppDcm_GucRoutineType) ||
    (APPDCM_ROUTINE_START == AppDcm_GucRoutineType))
  {
    LddRetVal = RTE_E_OK;
    *ErrorCode = DCM_POS_RESP;

    DataOut_RID_0200h_RequestOutSignal[0] = 0x71U;
    AppDcm_GucRoutineType = APPDCM_ROUTINE_REQUEST;
  }
  else
  {
    /* This sequence check have to be performed by SW-C. */
    *ErrorCode = DCM_E_REQUESTSEQUENCEERROR;
    LddRetVal = RTE_E_RoutineServices_RID_0200h_CalibrationActuator_E_NOT_OK;
  }

  return LddRetVal;
}
#endif

/*******************************************************************************
** Function Name        : AppDcm_Start_CalibrationActuator                    **
**                                                                            **
** Description          : This function requests to the application to start  **
**                        the execution of a routine.                         **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     :                                                     **
** - DataIn_RID_0200h_StartInSignal : Fixed-length input data provided        **
**   in the routine control request                                           **
** - OpStatus : Status of the current operation                               **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    :                                                     **
** - DataOut_RID_0200h_StartOutSignal : Fixed-length Output data to provide   **
**   in the routine control response                                          **
** - ErrorCode : If this operation returns value E_NOT_OK, the Dcm module     **
**   shall send a negative response with NRC code equal to the parameter      **
**   ErrorCode parameter value.                                               **
**                                                                            **
** Return parameter     :                                                     **
** - Std_ReturnType                                                           **
**   - RTE_E_OK : Request was successful                                      **
**   - RTE_E_RoutineServices_RID_0200h_CalibrationActuator_E_NOT_OK :         **
**     Request was not successful                                             **
**   - RTE_E_RoutineServices_RID_0200h_CalibrationActuator_DCM_E_PENDING :    **
**     Request is not yet finished. Further call required to finish           **
**   - RTE_E_RoutineServices_RID_0200h_CalibrationActuator_DCM_E_FORCE_RCRRP :**
**     application request the transmission of a response Response Pending    **
**     (NRC 0x78)                                                             **
**                                                                            **
*******************************************************************************/
#if defined(RTE_E_RoutineServices_RID_0200h_CalibrationActuator_E_NOT_OK)
FUNC(Std_ReturnType, SWC_DiagnosticService_CODE)
AppDcm_Start_CalibrationActuator(
  VAR(Dcm_StartDataIn_RID_0200h_CalibrationActuator_RID_0200h_StartInSignalType, \
    AUTOMATIC) DataIn_RID_0200h_StartInSignal, 
  VAR(Dcm_OpStatusType, AUTOMATIC) OpStatus, 
  P2VAR(Dcm_StartDataOut_RID_0200h_CalibrationActuator_RID_0200h_StartOutSignalType, \
    AUTOMATIC, RTE_APPL_DATA) DataOut_RID_0200h_StartOutSignal, 
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode)
{
  Std_ReturnType LddRetVal;

  if (1U == AppDcm_GucEcuIsBusy)
  {
    AppDcm_GusPendingCount++;
    LddRetVal = RTE_E_RoutineServices_RID_0200h_CalibrationActuator_DCM_E_PENDING;

    if (APPDCM_MAX_PENDING_COUNT_VALUE == AppDcm_GusPendingCount)
    {
      AppDcm_GucEcuIsBusy = 0U;
      AppDcm_GusPendingCount = 0U;
    }
  }
  else 
  {
    LddRetVal = RTE_E_OK;
    AppDcm_GucRoutineType = APPDCM_ROUTINE_START;

    *ErrorCode = DCM_POS_RESP;
    DataOut_RID_0200h_StartOutSignal[0] = DataIn_RID_0200h_StartInSignal;
  }
  
  return LddRetVal;
}
#endif

/*******************************************************************************
** Function Name        : AppDcm_Stop_CalibrationActuator                     **
**                                                                            **
** Description          : This function requests to the application to stop   **
**                        the execution of a routine.                         **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     :                                                     **
** - DataIn_RID_0200h_StopInSignal : Fixed-length input data provided         **
**   in the routine control request                                           **
** - OpStatus : Status of the current operation                               **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    :                                                     **
** - DataOut_RID_0200h_StopOutSignal : Fixed-length Output data to provide    **
**   in the routine control response.                                         **
** - ErrorCode : If this operation returns value E_NOT_OK, the Dcm module     **
**   shall send a negative response with NRC code equal to the parameter      **
**   ErrorCode parameter value.                                               **
**                                                                            **
** Return parameter     :                                                     **
** - Std_ReturnType                                                           **
**   - RTE_E_OK : Request was successful                                      **
**   - RTE_E_RoutineServices_RID_0200h_CalibrationActuator_E_NOT_OK :         **
**     Request was not successful                                             **
**   - RTE_E_RoutineServices_RID_0200h_CalibrationActuator_DCM_E_PENDING :    **
**     Request is not yet finished. Further call required to finish           **
**   - RTE_E_RoutineServices_RID_0200h_CalibrationActuator_DCM_E_FORCE_RCRRP :**
**     application request the transmission of a response Response Pending    **
**     (NRC 0x78)                                                             **
**                                                                            **
*******************************************************************************/
#if defined(RTE_E_RoutineServices_RID_0200h_CalibrationActuator_E_NOT_OK)
FUNC(Std_ReturnType, SWC_DiagnosticService_CODE)
AppDcm_Stop_CalibrationActuator(
  VAR(Dcm_StopDataIn_RID_0200h_CalibrationActuator_RID_0200h_StopInSignalType, \
    AUTOMATIC) DataIn_RID_0200h_StopInSignal, 
  VAR(Dcm_OpStatusType, AUTOMATIC) OpStatus, 
  P2VAR(Dcm_StopDataOut_RID_0200h_CalibrationActuator_RID_0200h_StopOutSignalType, \
    AUTOMATIC, RTE_APPL_DATA) DataOut_RID_0200h_StopOutSignal, 
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode)
{
  Std_ReturnType LddRetVal;

  if (APPDCM_ROUTINE_START == AppDcm_GucRoutineType)
  {
    LddRetVal = RTE_E_OK;
    *ErrorCode = DCM_POS_RESP;

    DataOut_RID_0200h_StopOutSignal[0] = DataIn_RID_0200h_StopInSignal;
    AppDcm_GucRoutineType = APPDCM_ROUTINE_STOP;
  }
  else
  {
    /* This sequence check have to be performed by SW-C. */
    *ErrorCode = DCM_E_REQUESTSEQUENCEERROR;
    LddRetVal = RTE_E_RoutineServices_RID_0200h_CalibrationActuator_E_NOT_OK;
  }

  return LddRetVal;
}
#endif

#if (defined(Rte_Call_HaePseudoRandomSeed_L1_RandomSeedStart) || \
     defined(Rte_Call_HaePseudoRandomSeed_L9_RandomSeedStart) || \
	 defined(Rte_Call_CsmKeyManagement_RandomSeed_L1_RandomSeed) || \
	 defined(Rte_Call_CsmKeyManagement_RandomSeed_L9_RandomSeed))
/*******************************************************************************
** Function Name        : AppDcm_GetRandomSeed                                **
**                                                                            **
** Description          : This function shall offer user random seed for      **
**                        SW PRNG Entropy. This function is used when HSM     **
**                        is not applied                                      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : RandomSeed[]                                        **
**                                                                            **
** Return parameter     :                                                     **
** - Std_ReturnType                                                           **
**   - E_OK : Success generate User RandomSeed                                **
**   - E_NOT_OK : Fail generate User RandomSeed                               **
**                                                                            **
*******************************************************************************/
#if (defined(Rte_Call_HaePseudoRandomSeed_L1_RandomSeedStart) || \
     defined(Rte_Call_HaePseudoRandomSeed_L9_RandomSeedStart) || \
	 defined(Rte_Call_CsmKeyManagement_RandomSeed_L1_RandomSeed) || \
	 defined(Rte_Call_CsmKeyManagement_RandomSeed_L9_RandomSeed))

FUNC(Std_ReturnType, RTE_CODE) AppDcm_GetRandomSeed(
  P2VAR(uint8, AUTOMATIC,DCM_APPL_DATA) RandomSeed)
{
  Std_ReturnType RetVal = E_NOT_OK;

  /*
  * Apply user RandomSeed to the argument in this function.
  * RandomSeed is a 16-row array. (RandomSeed[16])
  * Assign a random number to this variable (RandomSeed)
  * ex) current time, tick count, event timer, ADC noise, sensor value, etc..
  */

  /*
  * If you apply RandomSeed, you must return E_OK.
  * E_OK : Use the user RandomSeed
  * E_NOT_OK : Fail to use RandomSeed
  */

  /* Example of SPC58x RandomSeed.
   * This code is an example and is not guaranteed and should be used only for reference.
   * OS tick address is different for each MCU
   *
   *
   * uint32 LulSeed, LulSeedAddr, LulNoise;
   * uint8 LucIndex;
   *
   * LulSeedAddr = 0xF4070004; // Address of SPC58x OS Tick
   * LulSeed=(*(volatile uint32*)LulSeedAddr);
   *
   * for(LucIndex=0; LucIndex<APPDCM_HAE_PSEUDO_ENTROPY_LENGTH; LucIndex++)
   * {
   *   LulSeed = (uint32)((LulSeed * 1103515245 + 12345)>>16) & 0xFF;
   *   RandomSeed[LucIndex] = (uint8)(LulSeed + LulNoise);
   * }
   *
   *  RetVal = E_OK;
   *
   */

  uint32 LulSeed, LulSeedAddr, LulNoise;
  uint8 LucIndex;


  for(LucIndex=0; LucIndex<APPDCM_HAE_PSEUDO_ENTROPY_LENGTH; LucIndex++)
  {
    RandomSeed[LucIndex] = LucIndex;
  }

   RetVal = E_OK;

  return RetVal;
}
#endif

/*******************************************************************************
** Function Name        : AppDcm_GetSeed_L1                                   **
**                                                                            **
** Description          : Request to application for asynchronous provision of**
**                        seed value.                                         **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     :                                                     **
** - OpStatus : Status of the current operation                               **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    :                                                     **
** - Seed : Pointer for provided seed                                         **
** - ErrorCode : If this operation returns value E_NOT_OK, the Dcm module     **
**   shall send a negative response with NRC code equal to the parameter      **
**   ErrorCode parameter value.                                               **
**                                                                            **
** Return parameter     :                                                     **
** - Std_ReturnType                                                           **
**   - RTE_E_OK : Request was successful                                      **
**   - RTE_E_SecurityAccess_L1_E_NOT_OK : Request was not successful          **
**   - RTE_E_SecurityAccess_L1_DCM_E_PENDING :                                **
**     Request is not yet finished. Further call required to finish           **
**                                                                            **
*******************************************************************************/
#if defined(RTE_E_SecurityAccess_L1_E_NOT_OK)
FUNC(Std_ReturnType, SWC_DiagnosticService_CODE) 
AppDcm_GetSeed_L1(
  VAR(Dcm_OpStatusType, AUTOMATIC) OpStatus, 
  P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) Seed, 
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode)
{
  Std_ReturnType LddRetVal;

  LddRetVal = RTE_E_OK;
  *ErrorCode = DCM_POS_RESP;

  for (uint8 LucIndex = 0U; LucIndex < 4U; LucIndex++)
  {
    Seed[LucIndex] = AppDcm_GaaSeedTest[LucIndex];
  }

  return LddRetVal;
}
#endif

/*******************************************************************************
** Function Name        : AppDcm_CompareKey_L1                                **
**                                                                            **
** Description          : Request to application for asynchronous comparing   **
**                        key.                                                **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     :                                                     **
** - Key : Key, which needs to be compared                                    **
** - OpStatus : Status of the current operation                               **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     :                                                     **
** - Std_ReturnType                                                           **
**   - RTE_E_OK : Request was successful                                      **
**   - RTE_E_SecurityAccess_L1_E_NOT_OK : Request was not successful          **
**   - RTE_E_SecurityAccess_L1_DCM_E_PENDING :                                **
**     Request is not yet finished, Further call required to finish           **
**   - RTE_E_SecurityAccess_L1_DCM_E_COMPARE_KEY_FAILED : Key did not match   **
**                                                                            **
*******************************************************************************/
#if defined(RTE_E_SecurityAccess_L1_E_NOT_OK)
FUNC(Std_ReturnType, SWC_DiagnosticService_CODE) 
AppDcm_CompareKey_L1(
  P2CONST(uint8, AUTOMATIC, RTE_APPL_CONST) Key, 
  VAR(Dcm_OpStatusType, AUTOMATIC) OpStatus, 
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode)
{
  Std_ReturnType LddRetVal = RTE_E_OK;

  *ErrorCode = DCM_POS_RESP;

  for (uint8 LucIndex = 0U; LucIndex < 4U; LucIndex++)
  {
    if (Key[LucIndex] != AppDcm_GaaKeyTest[LucIndex])
    {
      LddRetVal = RTE_E_SecurityAccess_L1_DCM_E_COMPARE_KEY_FAILED;
      break;
    }
  }

  return LddRetVal;
}
#endif

/*******************************************************************************
** Function Name        : AppDcm_GetSeed_L9                                   **
**                                                                            **
** Description          : Request to application for asynchronous provision of**
**                        seed value.                                         **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     :                                                     **
** - OpStatus : Status of the current operation                               **
**   - DCM_INITIAL : Indicates the initial call to the operation              **
**   - DCM_PENDING : Indicates that a pending return has been done on         **
**                   the previous call of the operation                       **
**   - DCM_CANCEL : Indicates that the DCM requests to cancel                 **
**                  the pending operation                                     **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    :                                                     **
** - Seed : Pointer for provided seed                                         **
** - ErrorCode : If this operation returns value E_NOT_OK, the Dcm module     **
**   shall send a negative response with NRC code equal to the parameter      **
**   ErrorCode parameter value. (Refer to the Rte_Dcm_Type.h)                 **
**                                                                            **
** Return parameter     :                                                     **
** - Std_ReturnType                                                           **
**   - RTE_E_OK : Request was successful                                      **
**   - RTE_E_SecurityAccess_L9_E_NOT_OK : Request was not successful          **
**   - RTE_E_SecurityAccess_L9_DCM_E_PENDING :                                **
**     Request is not yet finished, Further call required to finish           **
**                                                                            **
*******************************************************************************/
#if defined(RTE_E_SecurityAccess_L9_E_NOT_OK)
FUNC(Std_ReturnType, RTE_CODE) AppDcm_GetSeed_L9(
  Dcm_OpStatusType OpStatus,
  P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) Seed,
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode)
{
  Std_ReturnType LddRetVal = RTE_E_SecurityAccess_L9_E_NOT_OK;
  uint32 resultLength = 8UL; /* L1 SeedKey Length is 4-byte*/

  #if defined(Rte_Call_AutHsmPseudoRandomGenerate_L9_RandomGenerate)
  /* Case 1. Random Generate with HSM PRNG (TRNG + SW PRNG) : Autron HSM 1.0 */
  if (RTE_E_OK == Rte_Call_AutHsmPseudoRandomGenerate_L9_RandomGenerate(&AppDcm_GaaRandomNum[0], resultLength))
  #elif defined(Rte_Call_HaeHsmPseudoRandomGenerate_L9_RandomGenerate)
  /* Case 2. Random Generate with HSM PRNG (TRNG + SW PRNG) : HAE HSM 2.0 */
  if (RTE_E_OK == Rte_Call_HaeHsmPseudoRandomGenerate_L9_RandomGenerate(&AppDcm_GaaRandomNum[0], resultLength))
  #elif ((defined(Rte_Call_HaePseudoRandomSeed_L9_RandomSeedStart)) || \
		 (defined(Rte_Call_CsmKeyManagement_RandomSeed_L9_RandomSeed))) /* R44 Csm */
  /* Case 3. Random Generate with SW PRNG : HAE CryptoLib */
  volatile static boolean LblRandomSeedUpdated = FALSE;

  if (FALSE == LblRandomSeedUpdated)
  {
    uint8 LaaHaeHacSalt_L9[APPDCM_HAE_PSEUDO_ENTROPY_LENGTH] = {0U};

    /* Get User RandomSeed */
    if (E_OK == AppDcm_GetRandomSeed(LaaHaeHacSalt_L9))
    {
      /* Update RandomSeed */
      #if defined(Rte_Call_HaePseudoRandomSeed_L9_RandomSeedStart)
      if (RTE_E_OK == Rte_Call_HaePseudoRandomSeed_L1_RandomSeedStart())
      {
        if (RTE_E_OK == Rte_Call_HaePseudoRandomSeed_L9_RandomSeedUpdate(LaaHaeHacSalt_L9, APPDCM_HAE_PSEUDO_ENTROPY_LENGTH))
        {
          if (RTE_E_OK == Rte_Call_HaePseudoRandomSeed_L9_RandomSeedFinish())
          {
            LblRandomSeedUpdated = TRUE;
          }
        }
      }
      #elif defined(Rte_Call_CsmKeyManagement_RandomSeed_L9_RandomSeed)
      if (RTE_E_OK == Rte_Call_CsmKeyManagement_RandomSeed_L9_RandomSeed(LaaHaeHacSalt_L9, APPDCM_HAE_PSEUDO_ENTROPY_LENGTH))
      {
    	LblRandomSeedUpdated = TRUE;
      }
      #endif
    }
  }
  if ((TRUE == LblRandomSeedUpdated) &&
  #if (defined(Rte_Call_HaePseudoRandomSeed_L9_RandomSeedStart))
      (RTE_E_OK == Rte_Call_HaePseudoRandomGenerate_L9_RandomGenerate(&AppDcm_GaaRandomNum[0], resultLength)))
  #elif (defined(Rte_Call_CsmKeyManagement_RandomSeed_L9_RandomSeed))
	  (RTE_E_OK == Rte_Call_RandomGenerate_L9_CsmRandomGenerateConfig_RandomGenerate(&AppDcm_GaaRandomNum[0], &resultLength)))
  #endif
  #else
  #error 'Not found Csm Random Generate Configuration. Please make random number in AppDcm_GaaRandomNum[] by yourself'
  #endif
  {
    uint8 LucIndex;
    for (LucIndex = 0U; LucIndex < resultLength; LucIndex++)
    {
      Seed[LucIndex] = AppDcm_GaaRandomNum[LucIndex];
    }
    LddRetVal = RTE_E_OK;
  }
  #if (defined(Rte_Call_HaePseudoRandomSeed_L9_RandomSeedStart) || \
       defined(Rte_Call_CsmKeyManagement_RandomSeed_L9_RandomSeed))
  else
  {
    LblRandomSeedUpdated = FALSE;
  }
  #endif

  if (RTE_E_OK != LddRetVal)
  {
    *ErrorCode = DCM_E_CONDITIONSNOTCORRECT;
  }

  return LddRetVal;
}


#elif (defined(APPDCM_L9_ICUS_RANDOM) || defined(APPDCM_L9_AUTRON_HSM_RANDOM_ICUM))
FUNC(Std_ReturnType, RTE_CODE) AppDcm_GetSeed_L9(
  Dcm_OpStatusType OpStatus,
  P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) Seed,
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode)
{
  Std_ReturnType LddRetVal = RTE_E_SecurityAccess_L9_E_NOT_OK;

  switch(OpStatus)
  {
  case DCM_INITIAL:
    #if defined(APPDCM_L9_ICUS_RANDOM)
    /***************************************************************************
     *                 true random generator(RH850 ICUS)                       *
     ***************************************************************************/
    if (RTE_E_OK == Rte_Call_AutIcusRandomGenerate_L9_RandomGenerate(&AppDcm_GaaAdvSeed[0], 8U))

    #elif defined(APPDCM_L9_AUTRON_HSM_RANDOM_ICUM)
    /***************************************************************************
     *                 true random generator(RH850 ICUM)                       *
     ***************************************************************************/
    if (RTE_E_OK == Rte_Call_AutHsmTrueRandomGenerate_L9_RandomGenerate(&AppDcm_GaaAdvSeed[0], 8U))

    #endif
    {
      AppDcm_SeedGenResult = RTE_E_SecurityAccess_L9_DCM_E_PENDING;
      LddRetVal = RTE_E_SecurityAccess_L9_DCM_E_PENDING;
    }
    break;

  case DCM_PENDING:
    LddRetVal = AppDcm_SeedGenResult;
    if (RTE_E_OK == AppDcm_SeedGenResult)
    {
      uint8 LucIndex;
      for (LucIndex = 0U; LucIndex < 8U; LucIndex++)
      {
        Seed[LucIndex] = AppDcm_GaaAdvSeed[LucIndex];
      }
    }
    break;

  case DCM_CANCEL:
    LddRetVal = RTE_E_OK;
    break;

  default :
    break;
  }

  if (RTE_E_SecurityAccess_L9_E_NOT_OK == LddRetVal)
  {
    *ErrorCode = DCM_E_CONDITIONSNOTCORRECT;
  }
  return LddRetVal;
}

FUNC(Std_ReturnType, SWC_DiagnosticService_CODE) AppDcm_GetSeedCbk_L9(
  VAR(Std_ReturnType, AUTOMATIC) retVal)
{
  if (retVal == RTE_E_OK)
  {
    AppDcm_SeedGenResult = RTE_E_OK;
  }
  else
  {
    AppDcm_SeedGenResult = RTE_E_SecurityAccess_L9_E_NOT_OK;
  }

  return RTE_E_OK;
}

#elif defined(APPDCM_L9_HAE_PSEUDO_RANDOM)
FUNC(Std_ReturnType, RTE_CODE) AppDcm_GetSeed_L9(
  Dcm_OpStatusType OpStatus,
  P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) Seed,
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode)
{
  Std_ReturnType LddRetVal = RTE_E_SecurityAccess_L9_E_NOT_OK;
  volatile static boolean LblRandomSeedUpdated = FALSE;

  if (FALSE == LblRandomSeedUpdated)
  {
    uint8 LaaRandomSeed[4] = {0U, };
    /*
     * Apply user RandomSeed to the argument in this function.
     * RandomSeed is a 4-row array. (RandomSeed[4])
     * Assign a random number to this variable (RandomSeed)
     * ex) current time, tick count, event timer, ADC noise, sensor value, etc..
     */
    LaaRandomSeed[0] = 1U;
    LaaRandomSeed[1] = 2U;
    LaaRandomSeed[2] = 3U;
    LaaRandomSeed[3] = 4U;

    /* Update RandomSeed */
    if (RTE_E_OK == Rte_Call_HaeAdvRandomSeed_L9_RandomSeedStart())
    {
      if (RTE_E_OK == Rte_Call_HaeAdvRandomSeed_L9_RandomSeedUpdate(LaaRandomSeed, 4U))
      {
        if (RTE_E_OK == Rte_Call_HaeAdvRandomSeed_L9_RandomSeedFinish())
        {
          LblRandomSeedUpdated = TRUE;
        }
      }
    }
  }

  if (TRUE == LblRandomSeedUpdated)
  {
    if (RTE_E_OK == Rte_Call_HaeAdvRandomGenerate_L9_RandomGenerate(&AppDcm_GaaAdvSeed[0], 8U))
    {
      uint8 LucIndex;
      for (LucIndex = 0U; LucIndex < 8U; LucIndex++)
      {
        Seed[LucIndex] = AppDcm_GaaAdvSeed[LucIndex];
      }
      LddRetVal = RTE_E_OK;
    }
  }
  if (RTE_E_OK != LddRetVal)
  {
    *ErrorCode = DCM_E_CONDITIONSNOTCORRECT;
  }

  return LddRetVal;
}
#endif

#endif /* defined(RTE_E_SecurityAccess_L9_E_NOT_OK) */

/*******************************************************************************
** Function Name        : AppDcm_CompareKey_L9                                **
**                                                                            **
** Description          : Request to application for asynchronous comparing   **
**                        key.                                                **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     :                                                     **
** - Key : Key, which needs to be compared                                    **
** - OpStatus : Status of the current operation                               **
**   - DCM_INITIAL : Indicates the initial call to the operation              **
**   - DCM_PENDING : Indicates that a pending return has been done on         **
**                   the previous call of the operation                       **
**   - DCM_CANCEL : Indicates that the DCM requests to cancel                 **
**                  the pending operation                                     **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     :                                                     **
** - Std_ReturnType                                                           **
**   - RTE_E_OK : Request was successful                                      **
**   - RTE_E_SecurityAccess_L9_E_NOT_OK : Request was not successful          **
**   - RTE_E_SecurityAccess_L9_DCM_E_PENDING :                                **
**     Request is not yet finished, Further call required to finish           **
**   - RTE_E_SecurityAccess_L9_DCM_E_COMPARE_KEY_FAILED : Key did not match   **
**                                                                            **
*******************************************************************************/
FUNC(Std_ReturnType, RTE_CODE) AppDcm_CompareKey_L9(
	P2CONST(uint8, AUTOMATIC, RTE_APPL_DATA) Key,
	Dcm_OpStatusType OpStatus,
	P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode)
{
  Std_ReturnType LddRetVal = RTE_E_SecurityAccess_L9_E_NOT_OK;
  uint8 LaaKey[8] = {0U, };
  *ErrorCode = DCM_POS_RESP;

  /* Call ASK library Key Generate API */
  if (SEEDKEY_SUCCESS == ASK_KeyGenerate(&AppDcm_GaaRandomNum[0], &LaaKey[0]))
  {
    uint8 LucIndex;
    /* Compare generated Key & received Key*/
    for (LucIndex = 0U; LucIndex < 8U; LucIndex++)
    {
      if (LaaKey[LucIndex] != Key[LucIndex])
      {
        break;
      }
    }
    if (LucIndex == 8U)
    {
      /* key matches */
      LddRetVal = RTE_E_OK;
    }
    else
    {
      /* key does not match */
      LddRetVal = RTE_E_SecurityAccess_L9_DCM_E_COMPARE_KEY_FAILED;
    }
  }

  return LddRetVal;
}

/*******************************************************************************
** Function Name        : AppDcm_UploadDownloadServices_ProcessRequestDownload**
**                                                                            **
** Description          : This function will start a download process         **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     :                                                     **
** - OpStatus: Status of the current operation                                **
** - DataFormatIdentifier:                                                    **
**   Bit 7 - 4: Compression Method                                            **
**   Bit 3 - 0: Encrypting method                                             **
** - MemoryIdentifier: Identifier of the Memory Block, if the parameter       **
**   is not used it shall be set to 0.                                        **
** - MemoryAddress: Starting address of server memory to which data is to be  **
**   written.                                                                 **
** - MemorySize: Uncompressed memory size in bytes                            **
**                                                                            **
** InOut parameter      :                                                     **
** - BlockLength: Max Number of bytes for one Dcm_WriteMemory                 **
**                                                                            **
** Output Parameters    :                                                     **
** - ErrorCode : If this operation returns value E_NOT_OK, the Dcm module     **
**   shall send a negative response with NRC code equal to the parameter      **
**   ErrorCode parameter value.                                               **
**                                                                            **
** Return parameter     :                                                     **
** - Std_ReturnType                                                           **
**   - RTE_E_OK : Request was successful                                      **
**   - RTE_E_UploadDownloadServices_E_NOT_OK : Request was not successful     **
**   - RTE_E_UploadDownloadServices_DCM_E_PENDING: Request is not yet finished**
**                                                                            **
*******************************************************************************/
#if defined(RTE_E_UploadDownloadServices_E_NOT_OK)
FUNC(Std_ReturnType, SWC_DiagnosticService_CODE)
AppDcm_UploadDownloadServices_ProcessRequestDownload(
  VAR(Dcm_OpStatusType, AUTOMATIC) OpStatus, 
  VAR(uint8, AUTOMATIC) DataFormatIdentifier, 
  VAR(uint8, AUTOMATIC) MemoryIdentifier, 
  VAR(uint32, AUTOMATIC) MemoryAddress, 
  VAR(uint32, AUTOMATIC) MemorySize, 
  P2VAR(uint32, AUTOMATIC, RTE_APPL_DATA) BlockLength, 
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode)
{
  Std_ReturnType LddRetVal;

  /* Only support two memory size */
  if (MemorySize == 0x04 || MemorySize == 0x0C)
  {
    LddRetVal = RTE_E_OK;
    *ErrorCode = DCM_POS_RESP;

    /* The block length reflect the complete request message length */
    *BlockLength = 0x06;    
  }
  else
  {
    *ErrorCode = DCM_E_REQUESTOUTOFRANGE;
    LddRetVal = RTE_E_UploadDownloadServices_E_NOT_OK;
  }

  return LddRetVal;
}
#endif

/*******************************************************************************
** Function Name        : AppDcm_UploadDownloadServices_ProcessRequestUpload  **
**                                                                            **
** Description          : This function will start a upload process           **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     :                                                     **
** - OpStatus: Status of the current operation                                **
** - DataFormatIdentifier:                                                    **
**   Bit 7 - 4: Compression Method                                            **
**   Bit 3 - 0: Encrypting method                                             **
** - MemoryIdentifier: Identifier of the Memory Block, if the parameter       **
**   is not used it shall be set to 0.                                        **
** - MemoryAddress: Starting address of server memory to which data is to be  **
**   written.                                                                 **
** - MemorySize: Uncompressed memory size in bytes                            **
**                                                                            **
** InOut parameter      :                                                     **
** - BlockLength: Max Number of bytes for one Dcm_WriteMemory                 **
**                                                                            **
** Output Parameters    :                                                     **
** - ErrorCode : If this operation returns value E_NOT_OK, the Dcm module     **
**   shall send a negative response with NRC code equal to the parameter      **
**   ErrorCode parameter value.                                               **
**                                                                            **
** Return parameter     :                                                     **
** - Std_ReturnType                                                           **
**   - RTE_E_OK : Request was successful                                      **
**   - RTE_E_UploadDownloadServices_E_NOT_OK : Request was not successful     **
**   - RTE_E_UploadDownloadServices_DCM_E_PENDING: Request is not yet finished**
**                                                                            **
*******************************************************************************/
#if defined(RTE_E_UploadDownloadServices_E_NOT_OK)
FUNC(Std_ReturnType, SWC_DiagnosticService_CODE)
AppDcm_UploadDownloadServices_ProcessRequestUpload(
  VAR(Dcm_OpStatusType, AUTOMATIC) OpStatus, 
  VAR(uint8, AUTOMATIC) DataFormatIdentifier, 
  VAR(uint8, AUTOMATIC) MemoryIdentifier, 
  VAR(uint32, AUTOMATIC) MemoryAddress, 
  VAR(uint32, AUTOMATIC) MemorySize, 
  P2VAR(uint32, AUTOMATIC, RTE_APPL_DATA) BlockLength, 
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode)
{
  Std_ReturnType LddRetVal;

  /* Only support two memory size */
  if (MemorySize == 0x04 || MemorySize == 0x0C)
  {
    LddRetVal = RTE_E_OK;
    *ErrorCode = DCM_POS_RESP;

    /* The block length reflect the complete response message length */
    *BlockLength = 0x06;    
  }
  else
  {
    *ErrorCode = DCM_E_REQUESTOUTOFRANGE;
    LddRetVal = RTE_E_UploadDownloadServices_E_NOT_OK;
  }

  return LddRetVal;
}
#endif

/*******************************************************************************
** Function Name        : AppDcm_UploadDownloadServices_                      **
**                        ProcessTransferDataRead                             **
**                                                                            **
** Description          : This function is used to request memory data        **
**                        identified by the parameter memoryAddress and       **
**                        memorySize from the UDS request message.            **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     :                                                     **
** - OpStatus: Status of the current operation                                **
** - MemoryIdentifier: Identifier of the Memory Block, if the parameter       **
**   is not used it shall be set to 0.                                        **
** - MemoryAddress: Starting address of server memory to which data is to be  **
**   retrieved.                                                               **
** - MemorySize: Number of bytes in the MemoryData                            **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    :                                                     **
** - MemoryData: Data read (Points to the diagnostic buffer in DCM)           **
** - ErrorCode : If this operation returns value E_NOT_OK, the Dcm module     **
**   shall send a negative response with NRC code equal to the parameter      **
**   ErrorCode parameter value.                                               **
**                                                                            **
** Return parameter     :                                                     **
** - Dcm_ReturnReadMemoryType:                                                **
**   - RTE_E_OK : Request was successful                                      **
**   - RTE_E_UploadDownloadServices_E_NOT_OK : Request was not successful     **
**   - RTE_E_UploadDownloadServices_DCM_E_PENDING: Request is not yet finished**
**                                                                            **
*******************************************************************************/
#if defined(RTE_E_UploadDownloadServices_E_NOT_OK)
FUNC(Std_ReturnType, SWC_DiagnosticService_CODE) 
AppDcm_UploadDownloadServices_ProcessTransferDataRead(
  VAR(Dcm_OpStatusType, AUTOMATIC) OpStatus, 
  VAR(uint8, AUTOMATIC) MemoryIdentifier, 
  VAR(uint32, AUTOMATIC) MemoryAddress, 
  VAR(uint32, AUTOMATIC) MemorySize, 
  P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) MemoryData, 
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode)
{
  Std_ReturnType LddRetVal;

  /* Only support two memory size */
  if (MemorySize == 0x04 || MemorySize == 0x0C)
  {
    LddRetVal = RTE_E_OK;
    *ErrorCode = DCM_POS_RESP;

    for (uint32 LulIndex = 0U; LulIndex < MemorySize; LulIndex++)
    {
      MemoryData[LulIndex] = AppDcm_GaaProgrammingData[LulIndex];
    }
  }
  else
  {
    *ErrorCode = DCM_E_REQUESTOUTOFRANGE;
    LddRetVal = RTE_E_UploadDownloadServices_E_NOT_OK;
  }

  return LddRetVal;
}
#endif

/*******************************************************************************
** Function Name        : AppDcm_UploadDownloadServices_                      **
**                        ProcessTransferDataWrite                            **
**                                                                            **
** Description          : The function is used to write memory data identified**
**                        by the parameter memoryAddress and memorySize.      **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     :                                                     **
** - OpStatus : Status of the current operation                               **
** - MemoryIdentifier : Identifier of the Memory Block, if the parameter      **
**   is not used it shall be set to 0.                                        **
** - MemoryAddress : Starting address of server memory to which data          **
**   is copy to. If it�셲 not used (e.g. if the data is compressed)            **
**   this parameter shall be set to 0.                                        **
** - MemorySize : Number of bytes in the MemoryData                           **
** - MemoryData : Data to write (Points to the diagnostic buffer in DCM)      **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    :                                                     **
** - ErrorCode : If this operation returns value E_NOT_OK, the Dcm module     **
**   shall send a negative response with NRC code equal to the parameter      **
**   ErrorCode parameter value.                                               **
**                                                                            **
** Return parameter     :                                                     **
** - Dcm_ReturnWriteMemoryType:                                               **
**   - RTE_E_OK : Request was successful                                      **
**   - RTE_E_UploadDownloadServices_E_NOT_OK : Request was not successful     **
**   - RTE_E_UploadDownloadServices_DCM_E_PENDING: Request is not yet finished**
**                                                                            **
*******************************************************************************/
#if defined(RTE_E_UploadDownloadServices_E_NOT_OK)
FUNC(Std_ReturnType, SWC_DiagnosticService_CODE) 
AppDcm_UploadDownloadServices_ProcessTransferDataWrite(
  VAR(Dcm_OpStatusType, AUTOMATIC) OpStatus, 
  VAR(uint8, AUTOMATIC) MemoryIdentifier, 
  VAR(uint32, AUTOMATIC) MemoryAddress, 
  VAR(uint32, AUTOMATIC) MemorySize, 
  P2CONST(uint8, AUTOMATIC, RTE_APPL_CONST) MemoryData, 
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode)
{
  Std_ReturnType LddRetVal = RTE_E_UploadDownloadServices_E_NOT_OK;

  /* Only support two memory size */
  if (MemorySize == 0x04 || MemorySize == 0x0C)
  {
    LddRetVal = RTE_E_OK;
    *ErrorCode = DCM_POS_RESP;

    for (uint32 LulIndex = 0U; LulIndex < MemorySize; LulIndex++)
    {
      AppDcm_GaaProgrammingData[LulIndex] = MemoryData[LulIndex];
    }
  }
  else
  {
    *ErrorCode = DCM_E_REQUESTOUTOFRANGE;
    LddRetVal = RTE_E_UploadDownloadServices_E_NOT_OK;
  }

  return LddRetVal;
}
#endif

/*******************************************************************************
** Function Name        : AppDcm_UploadDownloadServices_                      **
**                        ProcessRequestTransferExit                          **
**                                                                            **
** Description          : This function is used to                            **
**                        terminate a download or uploadprocess.              **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     :                                                     **
** - OpStatus: Status of the current operation                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    :                                                     **
** - ErrorCode : If this operation returns value E_NOT_OK, the Dcm module     **
**   shall send a negative response with NRC code equal to the parameter      **
**   ErrorCode parameter value.                                               **
**                                                                            **
** Return parameter     :                                                     **
** - Std_ReturnType:                                                          **
**   - RTE_E_OK : Request was successful                                      **
**   - RTE_E_UploadDownloadServices_E_NOT_OK : Request was not successful     **
**   - RTE_E_UploadDownloadServices_DCM_E_PENDING: Request is not yet finished**
**                                                                            **
*******************************************************************************/
#if defined(RTE_E_UploadDownloadServices_E_NOT_OK)
FUNC(Std_ReturnType, SWC_DiagnosticService_CODE) 
AppDcm_UploadDownloadServices_ProcessRequestTransferExit(
  VAR(Dcm_OpStatusType, AUTOMATIC) OpStatus, 
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode)
{
  Std_ReturnType LddRetVal = RTE_E_OK;

  *ErrorCode = DCM_POS_RESP;

  return LddRetVal;
}
#endif

/*******************************************************************************
** Function Name        : AppDcm_RequestControlServices_Tid1_RequestControl   **
**                                                                            **
** Description          : Invokes a TID-specific function taking a configured **
**                        number of bytes as input and returing a fixed       **
**                        number of bytes as output.                          **
**                        This is typically used to implement OBD Service $08 **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      :                                                     **
** - OutBuffer : Output buffer in which the RequestControl function can store **
**   its result                                                               **
** - InBuffer : Input buffer containing the data of the OBD Service           **
**   0x08 request                                                             **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     :                                                     **
** - Std_ReturnType                                                           **
**   - RTE_E_OK : Request was successful.                                     **
**   - RTE_E_RequestControlServices_Tid1_E_NOT_OK : Request was not successful**
**                                                                            **
*******************************************************************************/
#if defined(RTE_E_RequestControlServices_Tid1_E_NOT_OK)
FUNC(Std_ReturnType, SWC_DiagnosticService_CODE) 
AppDcm_RequestControlServices_Tid1_RequestControl(
  P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) OutBuffer, 
  P2CONST(uint8, AUTOMATIC, RTE_APPL_CONST) InBuffer)
{
  Std_ReturnType LddRetVal = RTE_E_OK;

	AppDcm_Tid1RequestControlInvoked++;
	return LddRetVal;
}
#endif

/*******************************************************************************
** Function Name        : AppDcm_InfotypeServices_VINInfoData_                **
**                        GetInfotypeValueData                                **
**                                                                            **
** Description          : The function provides the data related to           **
**                        the requested Infotype.                             **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     :                                                     **
** - OpStatus : Status of the current operation                               **
**                                                                            **
** InOut parameter      :                                                     **
** - DataValueBufferSize : When the function is called this parameter contains**
**   the maximum number of data bytes that can be written to the buffer.      **
**   The callee fills in the number of written data bytes in DataValueBuffer. **
**                                                                            **
** Output Parameters    :                                                     **
** - DataValueBuffer : Buffer containing the Infotype information             **
**                                                                            **
** Return parameter     :                                                     **
** - Std_ReturnType:                                                          **
**   - RTE_E_OK: Request was successful.                                      **
**   - RTE_E_InfotypeServices_VINInfoData_E_NOT_OK: Request was not successful**
**   - RTE_E_InfotypeServices_VINInfoData_DCM_E_PENDING:                      **
**     Request is not yet finished. Further call(s) required to finish.       **
**                                                                            **
*******************************************************************************/
#if defined(RTE_E_InfotypeServices_VINInfoData_E_NOT_OK)
FUNC(Std_ReturnType, SWC_DiagnosticService_CODE) 
AppDcm_InfotypeServices_VINInfoData_GetInfotypeValueData(
  VAR(Dcm_OpStatusType, AUTOMATIC) OpStatus, 
  P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) DataValueBuffer, 
  P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) DataValueBufferSize)
{
  Std_ReturnType LddRetVal = RTE_E_OK;
  uint8 LucVinLength;

  if (*DataValueBufferSize > 17)
  {
    LucVinLength = 17;
  }
  else
  {
    LucVinLength = *DataValueBufferSize;
  }

  DataValueBuffer[0] = 0x01;

  for (uint8 idx = 1; idx <= LucVinLength; idx++)
  {
	  DataValueBuffer[idx] = AppDcm_GaaVIN[idx - 1];
  }

  *DataValueBufferSize -= (LucVinLength + 1);

  return LddRetVal;
}
#endif

/*******************************************************************************
** Function Name        : AppDcm_RequestFileTransfer_ProcessRequestAddFile    **
**                                                                            **
** Description          : This function is used to start a RequestFileTransfer**
**                        process with modeOfOperation equal to 0x01 (AddFile)**
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     :                                                     **
** - OpStatus : Status of the current operation                               **
** - filePathAndNameLength : Defines the length in bytes for                  **
**   the parameter filePathAndName.                                           **
** - filePathAndName : Defines the file system location of the server where   **
**   the file which shall be added, deleted, replaced or read from depending  **
**   on the parameter modeOfOperation parameter. In addition this parameter   **
**   includes the file name of the file which shall be added, deleted,        **
**   replaced or read as part of the file path.                               **
** - dataFormatIdentifier : This data-parameter is a one byte value with each **
**   nibble encoded separately. The high nibble specifies                     **
**   the "compressionMethod", and the low nibble specifies                    **
**   the "encryptingMethod". The value 0x00 specifies that neither            **
**   compressionMethod nor encryptingMethod is used. Values other than 0x00   **
**   are vehicle manufacturer specific.                                       **
** - fileSizeUncompressed : Defines the size of the uncompressed file to be   **
**   download in bytes.                                                       **
** - fileSizeCompressed : Defines the size of the compressed file to be       **
**   downloaded in bytes.                                                     **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    :                                                     **
** - maxNumberOfBlockLength: Max number of bytes to be included in each       **
**   TransferData request excluding the SID and the blockSequenceCounter.     **
** - ErrorCode : If this operation returns value E_NOT_OK, the Dcm module     **
**   shall send a negative response with NRC code equal to the parameter      **
**   ErrorCode parameter value.                                               **
**                                                                            **
** Return parameter     :                                                     **
** - Std_ReturnType :                                                         **
**   - RTE_E_OK: Request was successful                                       **
**   - RTE_E_RequestFileTransfer_E_NOT_OK: Request was not successful         **
**   - RTE_E_RequestFileTransfer_DCM_E_PENDING: Request is not yet finished   **
**   - RTE_E_RequestFileTransfer_DCM_E_FORCE_RCRRP:                           **
**     Application request the transmission of a response Response Pending    **
**     (NRC 0x78)                                                             **
**                                                                            **
*******************************************************************************/
#if defined(RTE_E_RequestFileTransfer_E_NOT_OK)
FUNC(Std_ReturnType, SWC_DiagnosticService_CODE) 
AppDcm_RequestFileTransfer_ProcessRequestAddFile(
  VAR(Dcm_OpStatusType, AUTOMATIC) OpStatus, 
  VAR(uint16, AUTOMATIC) filePathAndNameLength, 
  P2CONST(uint8, AUTOMATIC, RTE_APPL_CONST) filePathAndName, 
  VAR(uint8, AUTOMATIC) dataFormatIdentifier, 
  VAR(uint64, AUTOMATIC) fileSizeUncompressed, 
  VAR(uint64, AUTOMATIC) fileSizeCompressed, 
  P2VAR(uint64, AUTOMATIC, RTE_APPL_DATA) maxNumberOfBlockLength, 
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode)
{
  Std_ReturnType LddRetVal = RTE_E_RequestFileTransfer_E_NOT_OK;

  if (APPDCM_FILE_NAME_LENGTH != filePathAndNameLength) 
  {
    *ErrorCode = DCM_E_REQUESTOUTOFRANGE;
  }
  else if (APPDCM_FILE_DATA_LENGTH != fileSizeUncompressed)
  {
    *ErrorCode = DCM_E_REQUESTOUTOFRANGE;
  }
  else
  {
    for (uint8 LucIndex = 0x00; LucIndex < APPDCM_FILE_NAME_LENGTH; LucIndex++)
    {
      AppDcm_GaaFilePathAndName[LucIndex] = filePathAndName[LucIndex];
    }

    LddRetVal = RTE_E_OK;
    *ErrorCode = DCM_POS_RESP;

    AppDcm_LucBlockCounter = 0x01;
    *maxNumberOfBlockLength = APPDCM_FILE_WRITE_BLOCK_LENGTH;
  }

  return LddRetVal;
}
#endif

/*******************************************************************************
** Function Name        : AppDcm_RequestFileTransfer_ProcessRequestDeleteFile **
**                                                                            **
** Description          : This function is used to start a RequestFileTransfer**
**                        process with modeOfOperation equal to 0x02          **
**                        (DeleteFile).                                       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     :                                                     **
** - OpStatus : Status of the current operation                               **
** - filePathAndNameLength : Defines the length in bytes for                  **
**   the parameter filePathAndName.                                           **
** - filePathAndName : Defines the file system location of the server where   **
**   the file which shall be added, deleted, replaced or read from depending  **
**   on the parameter modeOfOperation parameter. In addition this parameter   **
**   includes the file name of the file which shall be added, deleted,        **
**   replaced or read as part of the file path.                               **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    :                                                     **
** - ErrorCode : If this operation returns value E_NOT_OK, the Dcm module     **
**   shall send a negative response with NRC code equal to the parameter      **
**   ErrorCode parameter value.                                               **
**                                                                            **
** Return parameter     :                                                     **
** - Std_ReturnType :                                                         **
**   - RTE_E_OK: Request was successful                                       **
**   - RTE_E_RequestFileTransfer_E_NOT_OK: Request was not successful         **
**   - RTE_E_RequestFileTransfer_DCM_E_PENDING: Request is not yet finished   **
**   - RTE_E_RequestFileTransfer_DCM_E_FORCE_RCRRP:                           **
**     Application request the transmission of a response Response Pending    **
**     (NRC 0x78)                                                             **
**                                                                            **
*******************************************************************************/
#if defined(RTE_E_RequestFileTransfer_E_NOT_OK)
FUNC(Std_ReturnType, SWC_DiagnosticService_CODE) 
AppDcm_RequestFileTransfer_ProcessRequestDeleteFile(
  VAR(Dcm_OpStatusType, AUTOMATIC) OpStatus, 
  VAR(uint16, AUTOMATIC) filePathAndNameLength, 
  P2CONST(uint8, AUTOMATIC, RTE_APPL_CONST) filePathAndName, 
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode)
{
  Std_ReturnType LddRetVal = RTE_E_OK;

  *ErrorCode = DCM_POS_RESP;

  if (APPDCM_FILE_NAME_LENGTH != filePathAndNameLength) 
  {
    *ErrorCode = DCM_E_REQUESTOUTOFRANGE;
    LddRetVal = RTE_E_RequestFileTransfer_E_NOT_OK;
  }
  else
  {
    for (uint8 LucIndex = 0x00; LucIndex < APPDCM_FILE_NAME_LENGTH; LucIndex++)
    {
      if (AppDcm_GaaFilePathAndName[LucIndex] != filePathAndName[LucIndex])
      {
        *ErrorCode = DCM_E_REQUESTOUTOFRANGE;
        LddRetVal = RTE_E_RequestFileTransfer_E_NOT_OK;
        break;
      }
    }
  }

  return LddRetVal;
}
#endif

/*******************************************************************************
** Function Name        : AppDcm_RequestFileTransfer_ProcessRequestReadDir    **
**                                                                            **
** Description          : This function is used to start a RequestFileTransfer**
**                        process with modeOfOperation equal to 0x05          **
**                        (ReadDir).                                          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : 
** - OpStatus : Status of the current operation                               **
** - filePathAndNameLength : Defines the length in bytes for                  **
**   the parameter filePathAndName.                                           **
** - filePathAndName : Defines the file system location of the server where   **
**   the file which shall be added, deleted, replaced or read from depending  **
**   on the parameter modeOfOperation parameter. In addition this parameter   **
**   includes the file name of the file which shall be added, deleted,        **
**   replaced or read as part of the file path.                               **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    :                                                     **
** - dirInfoLength : Defines the size of directory information to be          **
**   uploaded in bytes.                                                       **
** - maxNumberOfBlockLength : Max number of bytes to be included in each      **
**   TransferData request excluding the SID and the blockSequenceCounter.     **
** - ErrorCode : If this operation returns value E_NOT_OK, the Dcm module     **
**   shall send a negative response with NRC code equal to the parameter      **
**   ErrorCode parameter value.                                               **
**                                                                            **
** Return parameter     :                                                     **
** - Std_ReturnType :                                                         **
**   - RTE_E_OK: Request was successful                                       **
**   - RTE_E_RequestFileTransfer_E_NOT_OK: Request was not successful         **
**   - RTE_E_RequestFileTransfer_DCM_E_PENDING: Request is not yet finished   **
**   - RTE_E_RequestFileTransfer_DCM_E_FORCE_RCRRP:                           **
**     Application request the transmission of a response Response Pending    **
**     (NRC 0x78)                                                             **
**                                                                            **
*******************************************************************************/
#if defined(RTE_E_RequestFileTransfer_E_NOT_OK)
FUNC(Std_ReturnType, SWC_DiagnosticService_CODE) 
AppDcm_RequestFileTransfer_ProcessRequestReadDir(
  VAR(Dcm_OpStatusType, AUTOMATIC) OpStatus, 
  VAR(uint16, AUTOMATIC) filePathAndNameLength, 
  P2CONST(uint8, AUTOMATIC, RTE_APPL_CONST) filePathAndName, 
  P2VAR(uint64, AUTOMATIC, RTE_APPL_DATA) dirInfoLength, 
  P2VAR(uint64, AUTOMATIC, RTE_APPL_DATA) maxNumberOfBlockLength, 
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode)
{
  Std_ReturnType LddRetVal = RTE_E_OK;

  *ErrorCode = DCM_POS_RESP;

  return LddRetVal;
}
#endif

/*******************************************************************************
** Function Name        : AppDcm_RequestFileTransfer_ProcessRequestReadFile   **
**                                                                            **
** Description          : This function is used to start a RequestFileTransfer**
**                        process with modeOfOperation equal to 0x04          **
**                        (ReadFile).                                         **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : 
** - OpStatus : Status of the current operation                               **
** - filePathAndNameLength : Defines the length in bytes for                  **
**   the parameter filePathAndName.                                           **
** - filePathAndName : Defines the file system location of the server where   **
**   the file which shall be added, deleted, replaced or read from depending  **
**   on the parameter modeOfOperation parameter. In addition this parameter   **
**   includes the file name of the file which shall be added, deleted,        **
**   replaced or read as part of the file path.                               **
** - dataFormatIdentifier : This data-parameter is a one byte value with each **
**   nibble encoded separately. The high nibble specifies                     **
**   the "compressionMethod", and the low nibble specifies                    **
**   the "encryptingMethod". The value 0x00 specifies that neither            **
**   compressionMethod nor encryptingMethod is used. Values other than 0x00   **
**   are vehicle manufacturer specific.                                       **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    :                                                     **
** - fileSizeUncompressed : Defines the size of the uncompressed file to be   **
**   uploaded in bytes.                                                       **
** - fileSizeCompressed : Defines the size of the compressed file to be       **
**   uploaded in bytes.                                                       **
** - maxNumberOfBlockLength : Max number of bytes to be included in each      **
**   TransferData response excluding the SID and the blockSequenceCounter.    **
** - ErrorCode : If this operation returns value E_NOT_OK, the Dcm module     **
**   shall send a negative response with NRC code equal to the parameter      **
**   ErrorCode parameter value.                                               **
**                                                                            **
** Return parameter     :                                                     **
** - Std_ReturnType :                                                         **
**   - RTE_E_OK: Request was successful                                       **
**   - RTE_E_RequestFileTransfer_E_NOT_OK: Request was not successful         **
**   - RTE_E_RequestFileTransfer_DCM_E_PENDING: Request is not yet finished   **
**   - RTE_E_RequestFileTransfer_DCM_E_FORCE_RCRRP:                           **
**     Application request the transmission of a response Response Pending    **
**     (NRC 0x78)                                                             **
**                                                                            **
*******************************************************************************/
#if defined(RTE_E_RequestFileTransfer_E_NOT_OK)
FUNC(Std_ReturnType, SWC_DiagnosticService_CODE) 
AppDcm_RequestFileTransfer_ProcessRequestReadFile(
  VAR(Dcm_OpStatusType, AUTOMATIC) OpStatus, 
  VAR(uint16, AUTOMATIC) filePathAndNameLength, 
  P2CONST(uint8, AUTOMATIC, RTE_APPL_CONST) filePathAndName, 
  VAR(uint8, AUTOMATIC) dataFormatIdentifier, 
  P2VAR(uint64, AUTOMATIC, RTE_APPL_DATA) fileSizeUncompressed, 
  P2VAR(uint64, AUTOMATIC, RTE_APPL_DATA) fileSizeCompressed, 
  P2VAR(uint64, AUTOMATIC, RTE_APPL_DATA) maxNumberOfBlockLength, 
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode)
{
  Std_ReturnType LddRetVal = RTE_E_OK;

  if (APPDCM_FILE_NAME_LENGTH != filePathAndNameLength) 
  {
    *ErrorCode = DCM_E_REQUESTOUTOFRANGE;
    LddRetVal = RTE_E_RequestFileTransfer_E_NOT_OK;
  }
  else
  {
    for (uint8 LucIndex = 0x00; LucIndex < APPDCM_FILE_NAME_LENGTH; LucIndex++)
    {
      if (AppDcm_GaaFilePathAndName[LucIndex] != filePathAndName[LucIndex])
      {
        *ErrorCode = DCM_E_REQUESTOUTOFRANGE;
        LddRetVal = RTE_E_RequestFileTransfer_E_NOT_OK;
        break;
      }
    }

    if (RTE_E_OK == LddRetVal)
    {
      AppDcm_LucBlockCounter = 0x01;

      *ErrorCode = DCM_POS_RESP;
      *fileSizeCompressed = 0x00;

      *fileSizeUncompressed = APPDCM_FILE_DATA_LENGTH;
      *maxNumberOfBlockLength = APPDCM_FILE_READ_BLOCK_LENGTH;
    }
  }

  return LddRetVal;
}
#endif

/*******************************************************************************
** Function Name        : AppDcm_RequestFileTransfer_ProcessRequestReplaceFile**
**                                                                            **
** Description          : This function is used to start a RequestFileTransfer**
**                        process with modeOfOperation equal to 0x03          **
**                        (ReplaceFile).                                      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     :                                                     **
** - OpStatus : Status of the current operation                               **
** - filePathAndNameLength : Defines the length in bytes for                  **
**   the parameter filePathAndName.                                           **
** - filePathAndName : Defines the file system location of the server where   **
**   the file which shall be added, deleted, replaced or read from depending  **
**   on the parameter modeOfOperation parameter. In addition this parameter   **
**   includes the file name of the file which shall be added, deleted,        **
**   replaced or read as part of the file path.                               **
** - dataFormatIdentifier : This data-parameter is a one byte value with each **
**   nibble encoded separately. The high nibble specifies                     **
**   the "compressionMethod", and the low nibble specifies                    **
**   the "encryptingMethod". The value 0x00 specifies that neither            **
**   compressionMethod nor encryptingMethod is used. Values other than 0x00   **
**   are vehicle manufacturer specific.                                       **
** - fileSizeUncompressed : Defines the size of the uncompressed file to be   **
**   download in bytes.                                                       **
** - fileSizeCompressed : Defines the size of the compressed file to be       **
**   downloaded in bytes.                                                     **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    :                                                     **
** - maxNumberOfBlockLength: Max number of bytes to be included in each       **
**   TransferData request excluding the SID and the blockSequenceCounter.     **
** - ErrorCode : If this operation returns value E_NOT_OK, the Dcm module     **
**   shall send a negative response with NRC code equal to the parameter      **
**   ErrorCode parameter value.                                               **
**                                                                            **
** Return parameter     :                                                     **
** - Std_ReturnType :                                                         **
**   - RTE_E_OK: Request was successful                                       **
**   - RTE_E_RequestFileTransfer_E_NOT_OK: Request was not successful         **
**   - RTE_E_RequestFileTransfer_DCM_E_PENDING: Request is not yet finished   **
**   - RTE_E_RequestFileTransfer_DCM_E_FORCE_RCRRP:                           **
**     Application request the transmission of a response Response Pending    **
**     (NRC 0x78)                                                             **
**                                                                            **
*******************************************************************************/
#if defined(RTE_E_RequestFileTransfer_E_NOT_OK)
FUNC(Std_ReturnType, SWC_DiagnosticService_CODE) 
AppDcm_RequestFileTransfer_ProcessRequestReplaceFile(
  VAR(Dcm_OpStatusType, AUTOMATIC) OpStatus, 
  VAR(uint16, AUTOMATIC) filePathAndNameLength, 
  P2CONST(uint8, AUTOMATIC, RTE_APPL_CONST) filePathAndName, 
  VAR(uint8, AUTOMATIC) dataFormatIdentifier, 
  VAR(uint64, AUTOMATIC) fileSizeUncompressed, 
  VAR(uint64, AUTOMATIC) fileSizeCompressed, 
  P2VAR(uint64, AUTOMATIC, RTE_APPL_DATA) maxNumberOfBlockLength, 
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode)
{
  Std_ReturnType LddRetVal = RTE_E_RequestFileTransfer_E_NOT_OK;

  if (APPDCM_FILE_NAME_LENGTH != filePathAndNameLength) 
  {
    *ErrorCode = DCM_E_REQUESTOUTOFRANGE;
  }
  else if (APPDCM_FILE_DATA_LENGTH != fileSizeUncompressed)
  {
    *ErrorCode = DCM_E_REQUESTOUTOFRANGE;
  }
  else
  {
    for (uint8 LucIndex = 0x00; LucIndex < APPDCM_FILE_NAME_LENGTH; LucIndex++)
    {
      AppDcm_GaaFilePathAndName[LucIndex] = filePathAndName[LucIndex];
    }

    LddRetVal = RTE_E_OK;
    *ErrorCode = DCM_POS_RESP;

    AppDcm_LucBlockCounter = 0x01;
    *maxNumberOfBlockLength = APPDCM_FILE_WRITE_BLOCK_LENGTH;
  }

  return LddRetVal;
}
#endif

/*******************************************************************************
** Function Name        : AppDcm_RequestFileTransfer_ReadFileOrDir            **
**                                                                            **
** Description          : This function is called when data shall be sent as  **
**                        a response to UDS service TransferData if there�셲   **
**                        an ongoing RequestFileTransfer process started with **
**                        0x04 (ReadFile) or 0x05 (ReadDir).                  **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     :                                                     **
** - OpStatus : Status of the current operation.                              **
** - Data : Pointer to the data to be written.                                **
**                                                                            **
** InOut parameter      :                                                     **
** - DataLength : As in, the parameter defines the maximum block length to be **
**   used, i.e. the value of maxNumberOfBlockLength sent to the client in the **
**   response of RequestFileTransfer.                                         **
**   As out, the parameter defines the actual length in bytes for the         **
**   parameter Data. The value shall not exceed, but might be less, the value **
**   provided as in parameter.                                                **
**                                                                            **
** Output Parameters    :                                                     **
** - ErrorCode : If this operation returns value E_NOT_OK, the Dcm module     **
**   shall send a negative response with NRC code equal to the parameter      **
**   ErrorCode parameter value.                                               **
**                                                                            **
** Return parameter     :                                                     **
** - Std_ReturnType :                                                         **
**   - RTE_E_OK: Request was successful                                       **
**   - RTE_E_RequestFileTransfer_E_NOT_OK: Request was not successful         **
**   - RTE_E_RequestFileTransfer_DCM_E_PENDING: Request is not yet finished   **
**   - RTE_E_RequestFileTransfer_DCM_E_FORCE_RCRRP:                           **
**     Application request the transmission of a response Response Pending    **
**     (NRC 0x78)                                                             **
**                                                                            **
*******************************************************************************/
#if defined(RTE_E_RequestFileTransfer_E_NOT_OK)
FUNC(Std_ReturnType, SWC_DiagnosticService_CODE) 
AppDcm_RequestFileTransfer_ReadFileOrDir(
  VAR(Dcm_OpStatusType, AUTOMATIC) OpStatus, 
  P2VAR(uint64, AUTOMATIC, RTE_APPL_DATA) DataLength, 
  P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) Data, 
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode)
{
  Std_ReturnType LddRetVal = RTE_E_OK;

  for (uint8 LucIndex = 0x00; LucIndex < APPDCM_FILE_DATA_LENGTH; LucIndex++)
  {
    Data[LucIndex] = AppDcm_GaaFileData[LucIndex];
  }

  *ErrorCode = DCM_POS_RESP;
  *DataLength = APPDCM_FILE_DATA_LENGTH;

  AppDcm_LucBlockCounter++;
  return LddRetVal;
}
#endif

/*******************************************************************************
** Function Name        : App_Dcm_RequestFileTransfer_WriteFile               **
**                                                                            **
** Description          : This function is called when data is received using **
**                        UDS service TransferData if there�셲 an ongoing      **
**                        RequestFileTransfer process started with 0x01       **
**                        (AddFile) or 0x03 (ReplaceFile).                    **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     :                                                     **
** - OpStatus : Status of the current operation                               **
** - DataLength : Defines the length in bytes for the parameter Data.         **
**   The value will not exceed, but might be less, compared to the value of   **
**   maxNumberOfBlockLength return in Dcm_ProcessRequestFileTransfer.         **
** - Data : Pointer to the data to be written.                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    :                                                     **
** - ErrorCode : If this operation returns value E_NOT_OK, the Dcm module     **
**   shall send a negative response with NRC code equal to the parameter      **
**   ErrorCode parameter value.                                               **
**                                                                            **
** Return parameter     :                                                     **
** - Std_ReturnType :                                                         **
**   - RTE_E_OK: Request was successful                                       **
**   - RTE_E_RequestFileTransfer_E_NOT_OK: Request was not successful         **
**   - RTE_E_RequestFileTransfer_DCM_E_PENDING: Request is not yet finished   **
**   - RTE_E_RequestFileTransfer_DCM_E_FORCE_RCRRP:                           **
**     Application request the transmission of a response Response Pending    **
**     (NRC 0x78)                                                             **
**                                                                            **
*******************************************************************************/
#if defined(RTE_E_RequestFileTransfer_E_NOT_OK)
FUNC(Std_ReturnType, SWC_DiagnosticService_CODE) 
App_Dcm_RequestFileTransfer_WriteFile(
  VAR(Dcm_OpStatusType, AUTOMATIC) OpStatus, 
  VAR(uint64, AUTOMATIC) DataLength, 
  P2CONST(uint8, AUTOMATIC, RTE_APPL_CONST) Data, 
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, RTE_APPL_DATA) ErrorCode)
{
  Std_ReturnType LddRetVal = RTE_E_RequestFileTransfer_E_NOT_OK;

  uint8 LucFileDataIndex = 0x00;

  if (APPDCM_FILE_HALF_DATA_LENGTH != DataLength)
  {
    *ErrorCode = DCM_E_REQUESTOUTOFRANGE;
  }
  else
  {
    if (AppDcm_LucBlockCounter == 0x01)
    {
      LucFileDataIndex = 0x00;
    }
    else
    {
      LucFileDataIndex = APPDCM_FILE_HALF_DATA_LENGTH;
    }

    for (uint8 LucIndex = 0x00; LucIndex < APPDCM_FILE_HALF_DATA_LENGTH; LucIndex++)
    {
      AppDcm_GaaFileData[LucFileDataIndex] = Data[LucIndex];
      LucFileDataIndex++;
    }

    LddRetVal = RTE_E_OK;
    *ErrorCode = DCM_POS_RESP;

    AppDcm_LucBlockCounter++;
  }

  return LddRetVal;
}
#endif

#define SWC_DiagnosticService_STOP_SEC_CODE
#include "SWC_DiagnosticService_MemMap.h"

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
