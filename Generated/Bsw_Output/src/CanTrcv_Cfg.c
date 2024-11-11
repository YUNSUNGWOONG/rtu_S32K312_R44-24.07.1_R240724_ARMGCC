
/*******************************************************************************
**                                                                            **
**  (C) 2021 HYUNDAI AUTOEVER Co., Ltd.                                       **
**                                                                            **
**  Confidential Proprietary Information. Distribution Limited.               **
**  This source code is permitted to be used only in projects contracted      **
**  with Hyundai Autoever, and any other use is prohibited.                   **
**  If you use it for other purposes or change the source code,               **
**  you may take legal responsibility.                                        **
**  In this case, There is no warranty and technical support.                 **
**                                                                            **
**  SRC-MODULE:           CanTrcv_Cfg.c                                       **
**                                                                            **
**  PRODUCT   :           AUTOSAR CAN Tranceiver Module                       **
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
**  Framework version : 1.1.5                                                 **
**                                                                            **
**  Module version :    1.0.11.0                                              **
**                                                                            **
**  Change History: Refer log file (use -l option to generate log file)       **
**                                                                            **
********************************************************************************
**                      File Generation Information                           **
*******************************************************************************/
/*
* INPUT FILE:      Configuration\Definition\Dio_s32k312_mqfp172.epd
*                  Configuration\Ecu\Ecud_CanTrcv.arxml         
*                  Configuration\Ecu\Ecud_EcuM.arxml            
*                  Configuration\Ecu\Mcal\Ecud_Dio.arxml        
*                  Configuration\System\Bswmd\Bswmd_Dio.arxml   
*                  Configuration\System\DBImport\DataTypes\AUTOSAR_DataTypes.arxml
*                  Configuration\System\DBImport\DataTypes\CanStack_DataTypes.arxml
*                  Generated\Bsw_Output\bswmd\Bswmd_CanTrcv.arxml
*                  Static_Code\Modules\CanTrcv_R44\generator\CanTrcv_ECU_Configuration_PDF.arxml
*                  Static_Code\Modules\EcuM_R44\generator\EcuM_ECU_Configuration_PDF.arxml
* GENERATED ON: The time-stamp is removed
*/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "CanTrcv_IntTypes.h"
#include "CanTrcv_Globals.h"
#include "EcuM.h"


/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#define CANTRCV_START_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
#include "MemMap.h"
/* CAN Transceiver Driver Network Structure */
/* polyspace +1 VARIABLE:* [Justified:Low] "Global variable CanTrcv_CanTrcvNetwork definition." */
CONST(CanTrcv_NetworkType, CANTRCV_CONST) CanTrcv_CanTrcvNetwork[] =
{
  /*CanTrcvChannel_FD_CAN1 - 0 */
  {
    /* ChannelUsed */
     CANTRCV_TRUE,
    
    /* ControlPowerSupply */
     CANTRCV_FALSE,
    
    /* WakeupByBusUsed */
     CANTRCV_FALSE,
    
    /* SleepModeUsed */
     CANTRCV_SLEEPMODE_UNUSED,
    
    /* PnNetworkIndex */
     CANTRCV_INVALID_PNINDEX,
    
    /* SelectPin1 */
     DioConf_DioChannel_DioChannel_PTC20,
    
    /* SelectPin2 */
     DioConf_DioChannel_DioChannel_PTC21,
    
    /* SelectPin3 */
     CANTRCV_UNUSED,
    
    /* CanTrcvHwDev */
     CANTRCV_TJA1043,
    
    /* InitState */
     CANTRCV_TRCVMODE_STANDBY,
    
    /* SyserrWakeupSource */
     CANTRCV_UNUSED,
    
    /* WakeupSource */
     CANTRCV_UNUSED
  }
};

#define CANTRCV_STOP_SEC_CONFIG_DATA_PREBUILD_UNSPECIFIED
#include "MemMap.h"


/*******************************************************************************
**                          End Of File                                       **
*******************************************************************************/
