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
**  SRC-MODULE: Dcm_Callout_User_Fixed.c                                      **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostic Communication Manager Module               **
**                                                                            **
**  PURPOSE   : This file contains the API definitions for Dsl layer of Dcm,  **
**              Initialization and scheduler functions of Dcm module          **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By              Description                        **
********************************************************************************
** 1.0.2   15-07-2022    LanhLT            Change as per #36622               **
**                                                                            **
** 1.0.0   27-Oct-2021    K.H Kim          Initial Version                    **
** 1.1.0   10-Nov-2023    DH Kwak          Refer #CP44-3288                   **
** 1.3.0   31-Dec-2023    DH Kwak          Refer #CP44-3142                   **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

#include "Dcm_Version.h"
#include "Dcm_Cfg.h"
#if (DCM_VERSION_AR_RELEASE_MINOR_VERSION == 4)
#include "Dcm_Externals.h"
#else /*For DCM_VERSION_AR_RELEASE_MINOR_VERSION == 0*/
#include "Dcm_CallOuts.h"
#endif
/* Use the FBL provided by AUTRON (Do not modify, if you use AUTRON FBL) */
#if (DCM_AUTRON_FBL_USED == STD_ON)
#include "Dcm_Callout_Fixed.h"
#include "Fbl_Stub.h"

/*******************************************************************************
**                      Dcm_Internal_GetProgCondition()                       **
*******************************************************************************/
#define DCM_START_SEC_CALLOUT_CODE
#include "MemMap.h"
FUNC(Dcm_EcuStartModeType, DCM_CALLOUT_CODE) Dcm_Internal_GetProgConditions
  (P2VAR(Dcm_ProgConditionsType, AUTOMATIC,DCM_APPL_DATA) ProgConditions)
{
  Dcm_EcuStartModeType StartMode = DCM_COLD_START;
  P2VAR(Dcm_McuDepProgConditionsType, AUTOMATIC,DCM_APPL_DATA)
  bcore_ProgConditions = (Dcm_McuDepProgConditionsType*)bcore_GetProgConditions();

  /* ApplUpdated is cleared in the Dcm_Init() */
  ProgConditions->ApplUpdated = bcore_ProgConditions->ApplUpdated;
  /* ResponseRequired is cleared in the Dcm_MainFunction() */
  ProgConditions->ResponseRequired = bcore_ProgConditions->ResponseRequired;
  
  if(DCM_TRUE == bcore_ProgConditions->ApplUpdated)
  {
    /* Update return value */
    StartMode = DCM_WARM_START;
  }
  else
  {
    /* Do Nothing */
  }

  #if (DCM_VERSION_AR_RELEASE_MINOR_VERSION == 4)
  if(DCM_TRUE == bcore_ProgConditions->ReprogramingRequest)
  {
    ProgConditions->ConnectionId        = bcore_ProgConditions->ConnectionId;
    ProgConditions->TesterAddress       = bcore_ProgConditions->TesterSourceAddr;
    ProgConditions->Sid                 = bcore_ProgConditions->Sid;
    ProgConditions->SubFncId            = bcore_ProgConditions->SubFncId;
    StartMode = DCM_WARM_START;
  }
  else
  {
    ProgConditions->ConnectionId        = (uint8)0x00;
    ProgConditions->TesterAddress       = (uint16)0x00;
    ProgConditions->Sid                 = (uint8)0x00;
    ProgConditions->SubFncId            = (uint8)0x00;
  }

  ProgConditions->SecurityLevel = (uint8)0x00;
  ProgConditions->ReprogramingRequest = (boolean)0x00;
  #else /*For DCM_VERSION_AR_RELEASE_MINOR_VERSION == 0*/
    if(DCM_TRUE == bcore_ProgConditions->ReprogramingRequest)
  {
    ProgConditions->ProtocolId          = bcore_ProgConditions->ProtocolId;
    ProgConditions->TesterSourceAddr    = bcore_ProgConditions->TesterSourceAddr;
    ProgConditions->Sid                 = bcore_ProgConditions->Sid;
    ProgConditions->SubFncId            = bcore_ProgConditions->SubFncId;
    StartMode = DCM_WARM_START;
  }
  else
  {
    ProgConditions->ProtocolId          = (uint8)0x00;
    ProgConditions->TesterSourceAddr    = (uint16)0x00;
    ProgConditions->Sid                 = (uint8)0x00;
    ProgConditions->SubFncId            = (uint8)0x00;
  }

  ProgConditions->SecLvInfo = (uint8)0x00;
  ProgConditions->ReprogramingRequest = (boolean)0x00;
  #endif

  return StartMode;
}

/*******************************************************************************
**                      Dcm_Internal_SetProgConditions()                      **
*******************************************************************************/
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) Dcm_Internal_SetProgConditions
  (P2CONST(Dcm_ProgConditionsType, AUTOMATIC,DCM_APPL_DATA) ProgConditions)
{
  Std_ReturnType RetVal = E_NOT_OK;
  P2VAR(Dcm_McuDepProgConditionsType, AUTOMATIC,DCM_APPL_DATA)
  bcore_ProgConditions = (Dcm_McuDepProgConditionsType*) bcore_GetProgConditions();

  if(NULL_PTR != ProgConditions)
  {
    if(ProgConditions->ReprogramingRequest == DCM_TRUE)
    {
	  #if (DCM_VERSION_AR_RELEASE_MINOR_VERSION == 4)
      bcore_ProgConditions->ConnectionId        = ProgConditions->ConnectionId;
      bcore_ProgConditions->TesterSourceAddr    = ProgConditions->TesterAddress;
      bcore_ProgConditions->Sid                 = ProgConditions->Sid;
      bcore_ProgConditions->SubFncId            = ProgConditions->SubFncId;
      bcore_ProgConditions->ReprogramingRequest = ProgConditions->ReprogramingRequest;
      bcore_ProgConditions->ApplUpdated         = ProgConditions->ApplUpdated;
      bcore_ProgConditions->ResponseRequired    = ProgConditions->ResponseRequired;
      bcore_ProgConditions->SecurityLevel       = ProgConditions->SecurityLevel;
	  #else /*For DCM_VERSION_AR_RELEASE_MINOR_VERSION == 0*/
	  bcore_ProgConditions->ProtocolId          = ProgConditions->ProtocolId;
      bcore_ProgConditions->TesterSourceAddr    = ProgConditions->TesterSourceAddr;
      bcore_ProgConditions->Sid                 = ProgConditions->Sid;
      bcore_ProgConditions->SubFncId            = ProgConditions->SubFncId;
      bcore_ProgConditions->ReprogramingRequest = ProgConditions->ReprogramingRequest;
      bcore_ProgConditions->ApplUpdated         = ProgConditions->ApplUpdated;
      bcore_ProgConditions->ResponseRequired    = ProgConditions->ResponseRequired;
      bcore_ProgConditions->SecLvInfo           = ProgConditions->SecLvInfo;
	  #endif

      bcore_SetStartupCommand(RESTART_BOOT_DIAG);
      RetVal = E_OK;
    }
    else 
    { 
	  #if (DCM_VERSION_AR_RELEASE_MINOR_VERSION == 4)
      bcore_ProgConditions->ConnectionId        = (uint8)0x00;
      bcore_ProgConditions->TesterSourceAddr    = (uint16)0x00;
      bcore_ProgConditions->Sid                 = (uint8)0x00;
      bcore_ProgConditions->SubFncId            = (uint8)0x00;
      bcore_ProgConditions->ReprogramingRequest = (boolean)0x00;
      bcore_ProgConditions->ApplUpdated         = (boolean)0x00;
      bcore_ProgConditions->ResponseRequired    = (boolean)0x00;
      bcore_ProgConditions->SecurityLevel       = (uint8)0x00;
	  #else /*For DCM_VERSION_AR_RELEASE_MINOR_VERSION == 0*/
	  bcore_ProgConditions->ProtocolId          = (uint8)0x00;
      bcore_ProgConditions->TesterSourceAddr    = (uint16)0x00;
      bcore_ProgConditions->Sid                 = (uint8)0x00;
      bcore_ProgConditions->SubFncId            = (uint8)0x00;
      bcore_ProgConditions->ReprogramingRequest = (boolean)0x00;
      bcore_ProgConditions->ApplUpdated         = (boolean)0x00;
      bcore_ProgConditions->ResponseRequired    = (boolean)0x00;
      bcore_ProgConditions->SecLvInfo           = (uint8)0x00;
	  #endif

      bcore_SetStartupCommand(DCM_FALSE);
    }
  }
  else
  {
    /* return E_NOT_OK */
  }

  return RetVal;
}
#define DCM_STOP_SEC_CALLOUT_CODE
#include "MemMap.h"

#endif
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
