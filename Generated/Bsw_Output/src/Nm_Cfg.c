/* polyspace +1 MISRA2012:1.1 [Not a defect:Low] "This rule is manually checked and has no impact." */
/*******************************************************************************
**                                                                            **
**  (C) 2021 HYUNDAI AUTOEVER Co., Ltd.                                       **
**  Confidential Proprietary Information. Distribution Limited.               **
**  This source code is permitted to be used only in projects contracted      **
**  with Hyundai Autoever, and any other use is prohibited.                   **
**  If you use it for other purposes or change the source code,               **
**  you may take legal responsibility.                                        **
**  In this case, There is no warranty and technical support.                 **
**                                                                            **
**  Generate On : The time-stamp is removed                                   **
**                                                                            **
**  SRC-MODULE:           Nm_Cfg.c                                            **
**                                                                            **
**  PRODUCT   :           AUTOSAR Network Management Interface Module         **
**                                                                            **
**  PURPOSE   :           This file contain function body for generic public  **
**                        API's.                                              **
**                                                                            **
**  HARDWARE DEPENDANT [Yes/No]: No                                           **
**                                                                            **
**  AUTOSAR RELEASE:  4.4.0                                                   **
*******************************************************************************/

/*******************************************************************************
**                      Generation Tool Information                           **
********************************************************************************
**  Framework Version: 1.1.5                                                  **
**  Module Version   : 1.0.5.0                                                **
**                                                                            **
**  Change History: Refer log file (use -l option to generate log file)       **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      File Generation Information                           **
*******************************************************************************/
/*
* INPUT FILE:      Configuration\Definition\ECUConfigurationParameters.arxml
*                  Configuration\Ecu\Ecud_CanNm.arxml           
*                  Configuration\Ecu\Ecud_ComM.arxml            
*                  Configuration\Ecu\Ecud_Nm.arxml              
*                  Generated\Bsw_Output\bswmd\Bswmd_Nm.arxml    
*                  Static_Code\Modules\CanNm_R44\generator\CanNm_ECU_Configuration_PDF.arxml
*                  Static_Code\Modules\ComM_R44\generator\ComM_ECU_Configuration_PDF.arxml
*                  Static_Code\Modules\Nm_R44\generator\Nm_ECU_Configuration_PDF.arxml
* GENERATED ON:    11-Nov-2024 - 12:59:14                       
*/
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* For macro definitions */
#include "Nm_Cfg.h"
/* Inclusion for declaration of internal types */
#include "Nm_IntTypes.h"
/* Inclusion for global variables */
#include "Nm_Globals.h"

/* Inclusion of CanNm APIs */
#include "CanNm.h"



/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#define NM_START_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
#include "MemMap.h"
/* List of configured channels */
CONST(Nm_ChannelConfigType, NM_CONFIG_DATA) Nm_ChannelConfig[NM_NO_OF_CHANNELS] = /* polyspace VARIABLE:* [Not a defect:Low] "This variable is checked manually and no impact." */
{
  /* Channel 0 */
  {
    /* PassiveStartUpFuncPtr */
    CanNm_PassiveStartUp,
    										    
    /* NetworkRequestFuncPtr */
    CanNm_NetworkRequest,
    										    
    /* NetworkReleaseFuncPtr */
    CanNm_NetworkRelease,
    										    
    /* DisableCommunicationFuncPtr */
    CanNm_DisableCommunication,
    										    
    /* EnableCommunicationFuncPtr */
    CanNm_EnableCommunication,
    										    
    /* SetUserDataFuncPtr */
    NULL_PTR,
    										    
    /* GetUserDataFuncPtr */
    CanNm_GetUserData,
    										    
    /* GetPduDataFuncPtr */
    CanNm_GetPduData,
    										    
    /* RepeatMessageRequestFuncPtr */
    CanNm_RepeatMessageRequest,
    										    
    /* GetNodeIdentifierFuncPtr */
    CanNm_GetNodeIdentifier,
    										    
    /* GetLocalNodeIdentifierFuncPtr */
    CanNm_GetLocalNodeIdentifier,
    										    
    /* GetStateFuncPtr */
    CanNm_GetState,
    										    
    /* ComUserDataSupport */
    TRUE,
    										    
    /* PassiveModeEnabled */
    FALSE,
    										    
    /* BusType */
    NM_BUSNM_CANNM
  }
};
#define NM_STOP_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
#include "MemMap.h"

#define NM_START_SEC_CONFIG_DATA_PREBUILD_8
#include "MemMap.h"
/* For getting the channel index from channel ID */
CONST(uint8, NM_CONFIG_DATA) Nm_ChannelIndexArray[NM_MAX_CHANNEL_ID + 1] = /* polyspace VARIABLE:* [Not a defect:Low] "This variable is checked manually and no impact." */
{
  0x00
};
#define NM_STOP_SEC_CONFIG_DATA_PREBUILD_8
#include "MemMap.h"






/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
