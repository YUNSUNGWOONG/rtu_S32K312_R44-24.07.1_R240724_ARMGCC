/* polyspace +1 MISRA2012:1.1 [Not a defect:Low] "The number of macros doesn't master." */
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
**  SRC-MODULE:           CanCM_Cfg.c                                         **
**                                                                            **
**  PRODUCT   :           AUTOSAR CAN Communication Manager Module            **
**                                                                            **
**  PURPOSE   :           This file contain function body for generic public  **
**                        API's.                                              **
**                                                                            **
**  HARDWARE DEPENDANT [Yes/No]: No                                           **
**                                                                            **
**  AUTOSAR RELEASE:  4.4.0                                                   **
********************************************************************************

********************************************************************************
**                      Generation Tool Information                           **
********************************************************************************
**  Framework version:   1.1.5                                                **
**  Module version:      1.0.9.0                                              **
**                                                                            **
**  Change History: Refer log file (use -l option to generate log file)       **
**                                                                            **
*******************************************************************************/
 
/*******************************************************************************
**                         Input File                                         **
*******************************************************************************/
/*
* INPUT FILE:      Configuration\Definition\ECUConfigurationParameters.arxml
*                  Configuration\Ecu\Ecud_CanCM.arxml           
*                  Configuration\Ecu\Ecud_CanIf.arxml           
*                  Configuration\Ecu\Ecud_CanSM.arxml           
*                  Configuration\Ecu\Ecud_ComM.arxml            
*                  Configuration\Ecu\Ecud_Dem.arxml             
*                  Configuration\Ecu\Ecud_EcuM.arxml            
*                  Configuration\Ecu\Ecud_IoHwAb.arxml          
*                  Generated\Bsw_Output\bswmd\Bswmd_CanCM.arxml 
*                  Static_Code\Modules\CanCM_R44\generator\CanCM_ECU_Configuration_PDF.arxml
*                  Static_Code\Modules\CanIf_R44\generator\CanIf_ECU_Configuration_PDF.arxml
*                  Static_Code\Modules\CanSM_R44\generator\CanSM_ECU_Configuration_PDF.arxml
*                  Static_Code\Modules\ComM_R44\generator\ComM_ECU_Configuration_PDF.arxml
*                  Static_Code\Modules\Dem_R44\generator\Dem_ECU_Configuration_PDF.arxml
*                  Static_Code\Modules\EcuM_R44\generator\EcuM_ECU_Configuration_PDF.arxml
*                  Static_Code\Modules\IoHwAb_R44\generator\IoHwAb_ECU_Configuration_PDF.arxml
* GENERATED ON:    11-Nov-2024 - 12:59:03                       
*/
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

#include "CanCM.h"
#include "CanCM_InitTypes.h"
#include "CanCM_PCTypes.h"
#include "CanCM_Ram.h"

/*******************************************************************************
*                        Version Check                                        **
*******************************************************************************/

#if (CANCM_PCTYPES_AR_RELEASE_MAJOR_VERSION != \
  CANCM_CFG_AR_RELEASE_MAJOR_VERSION )
  #error "CanCM_Cfg.c : Mismatch in Specification Major Version"
#endif

#if (CANCM_PCTYPES_AR_RELEASE_MINOR_VERSION != \
  CANCM_CFG_AR_RELEASE_MINOR_VERSION)
  #error "CanCM_Cfg.c : Mismatch in Specification Minor Version"
#endif

#if (CANCM_PCTYPES_AR_RELEASE_PATCH_VERSION != \
  CANCM_CFG_AR_RELEASE_REVISION_VERSION)
  #error "CanCM_Cfg.c : Mismatch in Specification Revision Version"
#endif

#if (CANCM_PCTYPES_SW_MAJOR_VERSION != CANCM_CFG_SW_MAJOR_VERSION)
  #error "CanCM_Cfg.c : Mismatch in Software Major Version"
#endif

#if (CANCM_PCTYPES_SW_MINOR_VERSION != CANCM_CFG_SW_MINOR_VERSION)
  #error "CanCM_Cfg.c : Mismatch in Software Major Version"
#endif

/*******************************************************************************
*                        Global Variables                                     **
*******************************************************************************/

#define CANCM_START_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
#include "MemMap.h"
/* Global array saving previous battery voltage value */
/* polyspace +1 VARIABLE:ALL [Not a defect:Low] "The variable is already checked by generator and no impact" */
CONST(uint16, CANCM_CONST) CanCM_AdcDefaultVal[CANCM_NUMBER_OF_ADC_GROUPS] =
{
  2640
};
#define CANCM_STOP_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
#include "MemMap.h"

#define CANCM_START_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
#include "MemMap.h"
/* Global Array for Adc group Ids */
/* polyspace +1 VARIABLE:ALL [Not a defect:Low] "The variable is already checked by generator and no impact" */
VAR(IoHwAb_IndexType, CANCM_VAR_NOINIT)CanCM_AdcGroup[CANCM_NUMBER_OF_ADC_GROUPS] =
{
  IoHwAbAnalogInputDirectLogical_CANBAT
};
#define CANCM_STOP_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
#include "MemMap.h"

#define CANCM_START_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
#include "MemMap.h"
/* Global Array for Channel index mapping with ComM Channel Id */
/* polyspace +1 VARIABLE:ALL [Not a defect:Low] "The variable is already checked by generator and no impact" */
CONST(NetworkHandleType, CANCM_CONST)CanCM_ComMChannelMap[CANCM_COM_M_CHANNEL_MAP] =
{
  0
};
#define CANCM_STOP_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
#include "MemMap.h"

#define CANCM_START_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
#include "MemMap.h"
/* Global Structure Array for Channel Configuration */
/* polyspace +1 VARIABLE:ALL [Not a defect:Low] "The variable is already checked by generator and no impact" */
CONST(Tdd_CanCM_ChannelConfig, CANCM_CONST) CanCM_ChannelConfig[CANCM_NUMBER_OF_CHANNELS] = 
{
  /*  CANCM_Channel 0 - 0 */
  {
     /* ddWakSrc */	
     ECUM_WKSOURCE_FD_CAN1_RX_POLL,
     	
     /* ddWakPin */	
     IoHwAbDigitalDirectLogical_FD_CAN1_RX,
     	
     /* ddEventId */	
     44,
     	
     /* ddAbnormalUpper */	
     0x0FF6,
     	
     /* ddAbnormalLower */	
     0x000A,
     	
     /* ddCriticalUpper */	
     0x1000,
     	
     /* ddCriticalLower */	
     0x0000,
     	
     /* ddHysteresis */	
     0x0008,
     	
     /* ddActivationTime */	
     0x002C,
     	
     /* ddDelayTimeCritical */	
     0x0028,
     	
     /* ddTimeoutStartTime */	
     0x00C8,
     	
     /* ucComMChannelId */	
     0,
     	
     /* ucChannelId */	
     0x00,
     	
     /* ucCanIfCtrlId */	
     0x00
  }
};
#define CANCM_STOP_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
#include "MemMap.h"



/*******************************************************************************
**                          END OF FILE                                       **
*******************************************************************************/
