/* polyspace +1 MISRA2012:1.1 [Justified:Low] "This rule is checked manually  and has no impact" */
/*******************************************************************************
**  FILE-NAME: LinSM_Cfg.c                                                    **
**                                                                            **
**  MODULE-NAME: AUTOSAR LIN State Manager Module                             **
**                                                                            **
**  NOTE: This file is auto generated, do not edit this file manually.        **
**                                                                            **
********************************************************************************

********************************************************************************
**                      Generation Tool Information                           **
********************************************************************************
**  Framework Version: 1.1.5                                                  **
**  Module version : 1.0.9.0                                                  **
**                                                                            **
**  Change History: Refer log file (use -l option to generate log file)       **
**                                                                            **
********************************************************************************
**                      File Generation Information                           **
*******************************************************************************/
/*
* INPUT FILE:      Configuration\Definition\ECUConfigurationParameters.arxml
*                  Configuration\Ecu\Ecud_ComM.arxml            
*                  Configuration\Ecu\Ecud_LinIf.arxml           
*                  Configuration\Ecu\Ecud_LinSM.arxml           
*                  Generated\Bsw_Output\bswmd\Bswmd_LinSM.arxml 
*                  Static_Code\Modules\ComM_R44\generator\ComM_ECU_Configuration_PDF.arxml
*                  Static_Code\Modules\LinIf_R44\generator\LinIf_ECU_Configuration_PDF.arxml
*                  Static_Code\Modules\LinSM_R44\generator\LinSM_ECU_Configuration_PDF.arxml
* GENERATED ON: The time-stamp is removed
*/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "LinSM_PCTypes.h"

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
#define    LINSM_CFG_AR_RELEASE_MAJOR_VERSION            0x04u
#define    LINSM_CFG_AR_RELEASE_MINOR_VERSION            0x04u
#define    LINSM_CFG_AR_RELEASE_REVISION_VERSION         0x00u
#define    LINSM_CFG_SW_MAJOR_VERSION                    0x01u
#define    LINSM_CFG_SW_MINOR_VERSION                    0x00u
#define    LINSM_CFG_SW_PATCH_VERSION                    0x09u

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#define LINSM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
CONST(NetworkHandleType, LINSM_CONST) LinSM_GaaInternalChannelMap[LINSM_MAX_INTERNAL_CHANNEL_MAP] =
{
  /* Internal 0 - 0 */	
  LINSM_INACTIVE_CHANNEL,
  
  /* Internal 1 - 1 */	
  0,
  
  /* Internal 2 - 2 */	
  1
};
#define LINSM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"	        

#define LINSM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
CONST(LinSM_SchMFuncPtr, LINSM_CONST) LinSM_GaaSchMEnterFuncPtr[LINSM_NO_OF_CHANNELS] =
{
  /* Protection 0 - LinSMChannel_LIN1 */	
  SchM_Enter_LinSM_CHANNEL_STATUS_PROTECTION_0,
  
  /* Protection 1 - LinSMChannel_LIN2 */	
  SchM_Enter_LinSM_CHANNEL_STATUS_PROTECTION_1
};
#define LINSM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"	        

#define LINSM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
CONST(LinSM_SchMFuncPtr, LINSM_CONST) LinSM_GaaSchMExitFuncPtr[LINSM_NO_OF_CHANNELS] =
{
  /* Protection 0 - LinSMChannel_LIN1 */	
  SchM_Exit_LinSM_CHANNEL_STATUS_PROTECTION_0,
  
  /* Protection 1 - LinSMChannel_LIN2 */	
  SchM_Exit_LinSM_CHANNEL_STATUS_PROTECTION_1
};
#define LINSM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"	        

#define LINSM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
CONST(uint8, LINSM_CONST) LinSM_GaaScheduleIds[LINSM_MAX_SCHEDULE_ID] =
{
  /* Protection 0 - LinSMChannel_LIN1 */	
  0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,
  
  /* Protection 1 - LinSMChannel_LIN2 */	
  0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22
};
#define LINSM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"	        

#define LINSM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
CONST(uint8, LINSM_CONST) LinSM_GaaTrcvPassiveMode[LINSM_NO_OF_CHANNELS] =
{
  /* TrcvPassive 0 - LinSMChannel_LIN1 */	
  LINSM_TRCV_CONFIGURED_FALSE,
  
  /* TrcvPassive 1 - LinSMChannel_LIN2 */	
  LINSM_TRCV_CONFIGURED_FALSE
};
#define LINSM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"	        

#define LINSM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
CONST(LinSM_NodeType, LINSM_VAR) LinSM_CurrentNodeType[LINSM_NO_OF_CHANNELS] = 
{
  /* Channel 0 - LinSMChannel_LIN1 */	
  LINSM_MASTER_NODE,
  
  /* Channel 1 - LinSMChannel_LIN2 */	
  LINSM_MASTER_NODE
};
#define LINSM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"	        


/*******************************************************************************
**                      Initialization Structure                              **
*******************************************************************************/
#define LINSM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
CONST(LinSM_StaticChannel, LINSM_CONST) LinSM_GaaStaticChannel[LINSM_NO_OF_CHANNELS] =
{
  /* Channel 0 - LinSMChannel_LIN1 */
  {
     /* LinSMChannelId */	
     1
  },
  
  /* Channel 1 - LinSMChannel_LIN2 */
  {
     /* LinSMChannelId */	
     2
  }
};
#define LINSM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"	        

#define LINSM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
CONST(LinSM_HandleChannel, LINSM_CONST) LinSM_GaaHandleChannel[LINSM_NO_OF_CHANNELS] =
{
  /* Channel 0 - LinSMChannel_LIN1 */
  {
     /* *pScheduleIds */	
     (P2CONST(uint8,AUTOMATIC,LINIF_CONST))&LinSM_GaaScheduleIds[0]
  },
  
  /* Channel 1 - LinSMChannel_LIN2 */
  {
     /* *pScheduleIds */	
     (P2CONST(uint8,AUTOMATIC,LINIF_CONST))&LinSM_GaaScheduleIds[23]
  }
};
#define LINSM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"	        

#define LINSM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
CONST(LinSM_ConfigType, LINSM_CONST) LinSM_GaaConfigType[LINSM_NO_OF_CHANNELS] =
{
  /* Channel 0 - LinSMChannel_LIN1 */
  {
     /* NoOfSchedules */	
     23,
     
     /* ModeRequestRepetitionMax  */	
     0
  },
  
  /* Channel 1 - LinSMChannel_LIN2 */
  {
     /* NoOfSchedules */	
     23,
     
     /* ModeRequestRepetitionMax  */	
     0
  }
};
#define LINSM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"	        


/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/