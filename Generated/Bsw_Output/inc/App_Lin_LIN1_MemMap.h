/*******************************************************************************
**                           HYUNDAI AUTOEVER Corp.                           **
********************************************************************************
** (C) 2021 HYUNDAI AUTOEVER Corp.                                            **
** Confidential Proprietary Information. Distribution Limited.                **
** This source code is permitted to be used only in projects contracted       **
** with Hyundai Autoever, and any other use is prohibited.                    **
** If you use it for other purposes or change the source code,                **
** you may take legal responsibility.                                         **
** In this case, There is no warranty and technical support.                  **
********************************************************************************
**  Module Name : RTE                                                         **
**                                                                            **
**  File Name : App_Lin_LIN1_MemMap.h                                         **
**                                                                            **
**  Generated On : Mon Nov 11 2024 13:32:30 KST                               **
**                                                                            **
**  Generated from :                                                          **
**  Configuration\Definition\Os_ECU_Configuration_PDF_S32K312.arxml           **
**  Configuration\Ecu\ECUCD_EcucValueCollection.arxml                         **
**  Configuration\Ecu\Ecud_BswM.arxml                                         **
**  Configuration\Ecu\Ecud_CanCM.arxml                                        **
**  Configuration\Ecu\Ecud_CanIf.arxml                                        **
**  Configuration\Ecu\Ecud_CanNm.arxml                                        **
**  Configuration\Ecu\Ecud_CanSM.arxml                                        **
**  Configuration\Ecu\Ecud_CanTp.arxml                                        **
**  Configuration\Ecu\Ecud_CanTrcv.arxml                                      **
**  Configuration\Ecu\Ecud_Com.arxml                                          **
**  Configuration\Ecu\Ecud_ComM.arxml                                         **
**  Configuration\Ecu\Ecud_ComXf.arxml                                        **
**  Configuration\Ecu\Ecud_Crc.arxml                                          **
**  Configuration\Ecu\Ecud_CryIf.arxml                                        **
**  Configuration\Ecu\Ecud_Crypto_76_HaeModule.arxml                          **
**  Configuration\Ecu\Ecud_Csm.arxml                                          **
**  Configuration\Ecu\Ecud_Dcm.arxml                                          **
**  Configuration\Ecu\Ecud_Dem.arxml                                          **
**  Configuration\Ecu\Ecud_Det.arxml                                          **
**  Configuration\Ecu\Ecud_E2EXf.arxml                                        **
**  Configuration\Ecu\Ecud_EcuC.arxml                                         **
**  Configuration\Ecu\Ecud_EcuM.arxml                                         **
**  Configuration\Ecu\Ecud_FiM.arxml                                          **
**  Configuration\Ecu\Ecud_Fota.arxml                                         **
**  Configuration\Ecu\Ecud_IoHwAb.arxml                                       **
**  Configuration\Ecu\Ecud_LinIf.arxml                                        **
**  Configuration\Ecu\Ecud_LinSM.arxml                                        **
**  Configuration\Ecu\Ecud_LinTrcv.arxml                                      **
**  Configuration\Ecu\Ecud_MemIf.arxml                                        **
**  Configuration\Ecu\Ecud_Nm.arxml                                           **
**  Configuration\Ecu\Ecud_NvM.arxml                                          **
**  Configuration\Ecu\Ecud_Os.arxml                                           **
**  Configuration\Ecu\Ecud_PduR.arxml                                         **
**  Configuration\Ecu\Ecud_Rte.arxml                                          **
**  Configuration\Ecu\Ecud_StbM.arxml                                         **
**  Configuration\Ecu\Ecud_Tm.arxml                                           **
**  Configuration\Ecu\Ecud_WdgIf.arxml                                        **
**  Configuration\Ecu\Ecud_WdgM.arxml                                         **
**  Configuration\Ecu\Ecud_Wdg_76_Acw.arxml                                   **
**  Configuration\Ecu\Mcal\Ecud_Adc.arxml                                     **
**  Configuration\Ecu\Mcal\Ecud_Wdg.arxml                                     **
**  Configuration\System\Bswmd\Bswmd_Adc.arxml                                **
**  Configuration\System\Bswmd\Bswmd_BswM.arxml                               **
**  Configuration\System\Bswmd\Bswmd_Can.arxml                                **
**  Configuration\System\Bswmd\Bswmd_ComXf.arxml                              **
**  Configuration\System\Bswmd\Bswmd_Crypto.arxml                             **
**  Configuration\System\Bswmd\Bswmd_Dio.arxml                                **
**  Configuration\System\Bswmd\Bswmd_E2EXf.arxml                              **
**  Configuration\System\Bswmd\Bswmd_Fee.arxml                                **
**  Configuration\System\Bswmd\Bswmd_Fls.arxml                                **
**  Configuration\System\Bswmd\Bswmd_Gpt.arxml                                **
**  Configuration\System\Bswmd\Bswmd_Icu.arxml                                **
**  Configuration\System\Bswmd\Bswmd_Lin.arxml                                **
**  Configuration\System\Bswmd\Bswmd_Mcl.arxml                                **
**  Configuration\System\Bswmd\Bswmd_Mcu.arxml                                **
**  Configuration\System\Bswmd\Bswmd_Port.arxml                               **
**  Configuration\System\Bswmd\Bswmd_Pwm.arxml                                **
**  Configuration\System\Bswmd\Bswmd_Spi.arxml                                **
**  Configuration\System\Bswmd\Bswmd_Wdg.arxml                                **
**  Configuration\System\Composition\EcuExtract.arxml                         **
**  Configuration\System\DBImport\DataTypes\AUTOSAR_DataTypes.arxml           **
**  Configuration\System\DBImport\DataTypes\CanStack_DataTypes.arxml          **
**  Configuration\System\DBImport\DataTypes\ComStack_DataTypes.arxml          **
**  Configuration\System\DBImport\FD_CAN1.arxml                               **
**  Configuration\System\DBImport\LIN1.arxml                                  **
**  Configuration\System\DBImport\LIN2.arxml                                  **
**  Configuration\System\Swcd_App\App_Dcm.arxml                               **
**  Configuration\System\Swcd_App\App_Dem.arxml                               **
**  Configuration\System\Swcd_App\App_E2EXf.arxml                             **
**  Configuration\System\Swcd_App\App_Lin.arxml                               **
**  Configuration\System\Swcd_App\App_Mode.arxml                              **
**  Configuration\System\Swcd_App\App_WdgM.arxml                              **
**  Configuration\System\Swcd_Bsw\MODE_PortInterfaces.arxml                   **
**  Configuration\System\Swcd_Bsw\Swcd_Bsw_BswM.arxml                         **
**  Configuration\System\Swcd_Bsw\Swcd_Lin.arxml                              **
**  Configuration\System\Transformer\Transformer.arxml                        **
**  Generated\Bsw_Output\bswmd\Bswmd_CanCM.arxml                              **
**  Generated\Bsw_Output\bswmd\Bswmd_CanIf.arxml                              **
**  Generated\Bsw_Output\bswmd\Bswmd_CanNm.arxml                              **
**  Generated\Bsw_Output\bswmd\Bswmd_CanSM.arxml                              **
**  Generated\Bsw_Output\bswmd\Bswmd_CanTp.arxml                              **
**  Generated\Bsw_Output\bswmd\Bswmd_CanTrcv.arxml                            **
**  Generated\Bsw_Output\bswmd\Bswmd_Com.arxml                                **
**  Generated\Bsw_Output\bswmd\Bswmd_ComM.arxml                               **
**  Generated\Bsw_Output\bswmd\Bswmd_Crc.arxml                                **
**  Generated\Bsw_Output\bswmd\Bswmd_CryIf.arxml                              **
**  Generated\Bsw_Output\bswmd\Bswmd_Crypto_76_HaeModule.arxml                **
**  Generated\Bsw_Output\bswmd\Bswmd_Csm.arxml                                **
**  Generated\Bsw_Output\bswmd\Bswmd_Dcm.arxml                                **
**  Generated\Bsw_Output\bswmd\Bswmd_Dem.arxml                                **
**  Generated\Bsw_Output\bswmd\Bswmd_Det.arxml                                **
**  Generated\Bsw_Output\bswmd\Bswmd_EcuM.arxml                               **
**  Generated\Bsw_Output\bswmd\Bswmd_FiM.arxml                                **
**  Generated\Bsw_Output\bswmd\Bswmd_Fota.arxml                               **
**  Generated\Bsw_Output\bswmd\Bswmd_IoHwAb.arxml                             **
**  Generated\Bsw_Output\bswmd\Bswmd_IpduM.arxml                              **
**  Generated\Bsw_Output\bswmd\Bswmd_KeyM.arxml                               **
**  Generated\Bsw_Output\bswmd\Bswmd_LinIf.arxml                              **
**  Generated\Bsw_Output\bswmd\Bswmd_LinSM.arxml                              **
**  Generated\Bsw_Output\bswmd\Bswmd_LinTrcv.arxml                            **
**  Generated\Bsw_Output\bswmd\Bswmd_MemIf.arxml                              **
**  Generated\Bsw_Output\bswmd\Bswmd_Mem_76_Pfls.arxml                        **
**  Generated\Bsw_Output\bswmd\Bswmd_Nm.arxml                                 **
**  Generated\Bsw_Output\bswmd\Bswmd_NvM.arxml                                **
**  Generated\Bsw_Output\bswmd\Bswmd_Os.arxml                                 **
**  Generated\Bsw_Output\bswmd\Bswmd_PduR.arxml                               **
**  Generated\Bsw_Output\bswmd\Bswmd_StbM.arxml                               **
**  Generated\Bsw_Output\bswmd\Bswmd_Tm.arxml                                 **
**  Generated\Bsw_Output\bswmd\Bswmd_WdgIf.arxml                              **
**  Generated\Bsw_Output\bswmd\Bswmd_WdgM.arxml                               **
**  Generated\Bsw_Output\bswmd\Bswmd_Wdg_76_Acw.arxml                         **
**  Generated\Bsw_Output\swcd\Swcd_Bsw_ComM.arxml                             **
**  Generated\Bsw_Output\swcd\Swcd_Bsw_Csm.arxml                              **
**  Generated\Bsw_Output\swcd\Swcd_Bsw_Dcm.arxml                              **
**  Generated\Bsw_Output\swcd\Swcd_Bsw_Dem.arxml                              **
**  Generated\Bsw_Output\swcd\Swcd_Bsw_Det.arxml                              **
**  Generated\Bsw_Output\swcd\Swcd_Bsw_EcuM.arxml                             **
**  Generated\Bsw_Output\swcd\Swcd_Bsw_FiM.arxml                              **
**  Generated\Bsw_Output\swcd\Swcd_Bsw_IoHwAb.arxml                           **
**  Generated\Bsw_Output\swcd\Swcd_Bsw_KeyM.arxml                             **
**  Generated\Bsw_Output\swcd\Swcd_Bsw_NvM.arxml                              **
**  Generated\Bsw_Output\swcd\Swcd_Bsw_Os.arxml                               **
**  Generated\Bsw_Output\swcd\Swcd_Bsw_StbM.arxml                             **
**  Generated\Bsw_Output\swcd\Swcd_Bsw_WdgM.arxml                             **
**  Generated\Bsw_Output\swcd\Swcd_Fota.arxml                                 **
**  Static_Code\Modules\EcuM_R44\generator\EcuM_PortInterface.arxml           **
**  Static_Code\Modules\Rte_R44\generator\SafeRTE_PDF.arxml                   **
**                                                                            **
**  Generator version : 1.8.0.0                                               **
**                                                                            **
**  NOTE: This is a generated file, Please DO NOT EDIT manually!              **
**                                                                           **/
/******************************************************************************/
/*                Compatibility between C/C++ Languages Start                 */
/******************************************************************************/
#ifdef __cplusplus
extern "C" 
{

#endif

/******************************************************************************/
/*                           Memory Map Protection                            */
/******************************************************************************/
#if defined (START_App_Lin_LIN1_MEMMAP)

#elif defined (App_Lin_LIN1_START_SEC_CALIB_16)
  #undef App_Lin_LIN1_START_SEC_CALIB_16
  #define RTE_App_Lin_LIN1_START_SEC_CALIB_16
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_STOP_SEC_CALIB_16)
  #undef App_Lin_LIN1_STOP_SEC_CALIB_16
  #define RTE_App_Lin_LIN1_STOP_SEC_CALIB_16
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_START_SEC_CALIB_32)
  #undef App_Lin_LIN1_START_SEC_CALIB_32
  #define RTE_App_Lin_LIN1_START_SEC_CALIB_32
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_STOP_SEC_CALIB_32)
  #undef App_Lin_LIN1_STOP_SEC_CALIB_32
  #define RTE_App_Lin_LIN1_STOP_SEC_CALIB_32
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_START_SEC_CALIB_8)
  #undef App_Lin_LIN1_START_SEC_CALIB_8
  #define RTE_App_Lin_LIN1_START_SEC_CALIB_8
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_STOP_SEC_CALIB_8)
  #undef App_Lin_LIN1_STOP_SEC_CALIB_8
  #define RTE_App_Lin_LIN1_STOP_SEC_CALIB_8
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_START_SEC_CALIB_BOOLEAN)
  #undef App_Lin_LIN1_START_SEC_CALIB_BOOLEAN
  #define RTE_App_Lin_LIN1_START_SEC_CALIB_BOOLEAN
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_STOP_SEC_CALIB_BOOLEAN)
  #undef App_Lin_LIN1_STOP_SEC_CALIB_BOOLEAN
  #define RTE_App_Lin_LIN1_STOP_SEC_CALIB_BOOLEAN
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_START_SEC_CALIB_UNSPECIFIED)
  #undef App_Lin_LIN1_START_SEC_CALIB_UNSPECIFIED
  #define RTE_App_Lin_LIN1_START_SEC_CALIB_UNSPECIFIED
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_STOP_SEC_CALIB_UNSPECIFIED)
  #undef App_Lin_LIN1_STOP_SEC_CALIB_UNSPECIFIED
  #define RTE_App_Lin_LIN1_STOP_SEC_CALIB_UNSPECIFIED
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_START_SEC_CARTO_16)
  #undef App_Lin_LIN1_START_SEC_CARTO_16
  #define RTE_App_Lin_LIN1_START_SEC_CARTO_16
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_STOP_SEC_CARTO_16)
  #undef App_Lin_LIN1_STOP_SEC_CARTO_16
  #define RTE_App_Lin_LIN1_STOP_SEC_CARTO_16
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_START_SEC_CARTO_32)
  #undef App_Lin_LIN1_START_SEC_CARTO_32
  #define RTE_App_Lin_LIN1_START_SEC_CARTO_32
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_STOP_SEC_CARTO_32)
  #undef App_Lin_LIN1_STOP_SEC_CARTO_32
  #define RTE_App_Lin_LIN1_STOP_SEC_CARTO_32
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_START_SEC_CARTO_8)
  #undef App_Lin_LIN1_START_SEC_CARTO_8
  #define RTE_App_Lin_LIN1_START_SEC_CARTO_8
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_STOP_SEC_CARTO_8)
  #undef App_Lin_LIN1_STOP_SEC_CARTO_8
  #define RTE_App_Lin_LIN1_STOP_SEC_CARTO_8
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_START_SEC_CARTO_BOOLEAN)
  #undef App_Lin_LIN1_START_SEC_CARTO_BOOLEAN
  #define RTE_App_Lin_LIN1_START_SEC_CARTO_BOOLEAN
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_STOP_SEC_CARTO_BOOLEAN)
  #undef App_Lin_LIN1_STOP_SEC_CARTO_BOOLEAN
  #define RTE_App_Lin_LIN1_STOP_SEC_CARTO_BOOLEAN
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_START_SEC_CARTO_UNSPECIFIED)
  #undef App_Lin_LIN1_START_SEC_CARTO_UNSPECIFIED
  #define RTE_App_Lin_LIN1_START_SEC_CARTO_UNSPECIFIED
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_STOP_SEC_CARTO_UNSPECIFIED)
  #undef App_Lin_LIN1_STOP_SEC_CARTO_UNSPECIFIED
  #define RTE_App_Lin_LIN1_STOP_SEC_CARTO_UNSPECIFIED
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_START_SEC_CONFIG_DATA_16)
  #undef App_Lin_LIN1_START_SEC_CONFIG_DATA_16
  #define RTE_App_Lin_LIN1_START_SEC_CONFIG_DATA_16
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_STOP_SEC_CONFIG_DATA_16)
  #undef App_Lin_LIN1_STOP_SEC_CONFIG_DATA_16
  #define RTE_App_Lin_LIN1_STOP_SEC_CONFIG_DATA_16
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_START_SEC_CONFIG_DATA_32)
  #undef App_Lin_LIN1_START_SEC_CONFIG_DATA_32
  #define RTE_App_Lin_LIN1_START_SEC_CONFIG_DATA_32
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_STOP_SEC_CONFIG_DATA_32)
  #undef App_Lin_LIN1_STOP_SEC_CONFIG_DATA_32
  #define RTE_App_Lin_LIN1_STOP_SEC_CONFIG_DATA_32
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_START_SEC_CONFIG_DATA_8)
  #undef App_Lin_LIN1_START_SEC_CONFIG_DATA_8
  #define RTE_App_Lin_LIN1_START_SEC_CONFIG_DATA_8
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_STOP_SEC_CONFIG_DATA_8)
  #undef App_Lin_LIN1_STOP_SEC_CONFIG_DATA_8
  #define RTE_App_Lin_LIN1_STOP_SEC_CONFIG_DATA_8
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_START_SEC_CONFIG_DATA_BOOLEAN)
  #undef App_Lin_LIN1_START_SEC_CONFIG_DATA_BOOLEAN
  #define RTE_App_Lin_LIN1_START_SEC_CONFIG_DATA_BOOLEAN
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_STOP_SEC_CONFIG_DATA_BOOLEAN)
  #undef App_Lin_LIN1_STOP_SEC_CONFIG_DATA_BOOLEAN
  #define RTE_App_Lin_LIN1_STOP_SEC_CONFIG_DATA_BOOLEAN
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_START_SEC_CONFIG_DATA_UNSPECIFIED)
  #undef App_Lin_LIN1_START_SEC_CONFIG_DATA_UNSPECIFIED
  #define RTE_App_Lin_LIN1_START_SEC_CONFIG_DATA_UNSPECIFIED
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_STOP_SEC_CONFIG_DATA_UNSPECIFIED)
  #undef App_Lin_LIN1_STOP_SEC_CONFIG_DATA_UNSPECIFIED
  #define RTE_App_Lin_LIN1_STOP_SEC_CONFIG_DATA_UNSPECIFIED
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_START_SEC_CONST_16)
  #undef App_Lin_LIN1_START_SEC_CONST_16
  #define RTE_App_Lin_LIN1_START_SEC_CONST_16
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_STOP_SEC_CONST_16)
  #undef App_Lin_LIN1_STOP_SEC_CONST_16
  #define RTE_App_Lin_LIN1_STOP_SEC_CONST_16
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_START_SEC_CONST_32)
  #undef App_Lin_LIN1_START_SEC_CONST_32
  #define RTE_App_Lin_LIN1_START_SEC_CONST_32
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_STOP_SEC_CONST_32)
  #undef App_Lin_LIN1_STOP_SEC_CONST_32
  #define RTE_App_Lin_LIN1_STOP_SEC_CONST_32
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_START_SEC_CONST_8)
  #undef App_Lin_LIN1_START_SEC_CONST_8
  #define RTE_App_Lin_LIN1_START_SEC_CONST_8
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_STOP_SEC_CONST_8)
  #undef App_Lin_LIN1_STOP_SEC_CONST_8
  #define RTE_App_Lin_LIN1_STOP_SEC_CONST_8
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_START_SEC_CONST_BOOLEAN)
  #undef App_Lin_LIN1_START_SEC_CONST_BOOLEAN
  #define RTE_App_Lin_LIN1_START_SEC_CONST_BOOLEAN
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_STOP_SEC_CONST_BOOLEAN)
  #undef App_Lin_LIN1_STOP_SEC_CONST_BOOLEAN
  #define RTE_App_Lin_LIN1_STOP_SEC_CONST_BOOLEAN
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_START_SEC_CONST_UNSPECIFIED)
  #undef App_Lin_LIN1_START_SEC_CONST_UNSPECIFIED
  #define RTE_App_Lin_LIN1_START_SEC_CONST_UNSPECIFIED
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_STOP_SEC_CONST_UNSPECIFIED)
  #undef App_Lin_LIN1_STOP_SEC_CONST_UNSPECIFIED
  #define RTE_App_Lin_LIN1_STOP_SEC_CONST_UNSPECIFIED
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_START_SEC_CONST_SAVED_RECOVERY_ZONE_16)
  #undef App_Lin_LIN1_START_SEC_CONST_SAVED_RECOVERY_ZONE_16
  #define RTE_App_Lin_LIN1_START_SEC_CONST_SAVED_RECOVERY_ZONE_16
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_STOP_SEC_CONST_SAVED_RECOVERY_ZONE_16)
  #undef App_Lin_LIN1_STOP_SEC_CONST_SAVED_RECOVERY_ZONE_16
  #define RTE_App_Lin_LIN1_STOP_SEC_CONST_SAVED_RECOVERY_ZONE_16
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_START_SEC_CONST_SAVED_RECOVERY_ZONE_32)
  #undef App_Lin_LIN1_START_SEC_CONST_SAVED_RECOVERY_ZONE_32
  #define RTE_App_Lin_LIN1_START_SEC_CONST_SAVED_RECOVERY_ZONE_32
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_STOP_SEC_CONST_SAVED_RECOVERY_ZONE_32)
  #undef App_Lin_LIN1_STOP_SEC_CONST_SAVED_RECOVERY_ZONE_32
  #define RTE_App_Lin_LIN1_STOP_SEC_CONST_SAVED_RECOVERY_ZONE_32
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_START_SEC_CONST_SAVED_RECOVERY_ZONE_8)
  #undef App_Lin_LIN1_START_SEC_CONST_SAVED_RECOVERY_ZONE_8
  #define RTE_App_Lin_LIN1_START_SEC_CONST_SAVED_RECOVERY_ZONE_8
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_STOP_SEC_CONST_SAVED_RECOVERY_ZONE_8)
  #undef App_Lin_LIN1_STOP_SEC_CONST_SAVED_RECOVERY_ZONE_8
  #define RTE_App_Lin_LIN1_STOP_SEC_CONST_SAVED_RECOVERY_ZONE_8
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_START_SEC_CONST_SAVED_RECOVERY_ZONE_BOOLEAN)
  #undef App_Lin_LIN1_START_SEC_CONST_SAVED_RECOVERY_ZONE_BOOLEAN
  #define RTE_App_Lin_LIN1_START_SEC_CONST_SAVED_RECOVERY_ZONE_BOOLEAN
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_STOP_SEC_CONST_SAVED_RECOVERY_ZONE_BOOLEAN)
  #undef App_Lin_LIN1_STOP_SEC_CONST_SAVED_RECOVERY_ZONE_BOOLEAN
  #define RTE_App_Lin_LIN1_STOP_SEC_CONST_SAVED_RECOVERY_ZONE_BOOLEAN
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_START_SEC_CONST_SAVED_RECOVERY_ZONE_UNSPECIFIED)
  #undef App_Lin_LIN1_START_SEC_CONST_SAVED_RECOVERY_ZONE_UNSPECIFIED
  #define RTE_App_Lin_LIN1_START_SEC_CONST_SAVED_RECOVERY_ZONE_UNSPECIFIED
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_STOP_SEC_CONST_SAVED_RECOVERY_ZONE_UNSPECIFIED)
  #undef App_Lin_LIN1_STOP_SEC_CONST_SAVED_RECOVERY_ZONE_UNSPECIFIED
  #define RTE_App_Lin_LIN1_STOP_SEC_CONST_SAVED_RECOVERY_ZONE_UNSPECIFIED
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_START_SEC_INTERNAL_VAR_CLEARED_16)
  #undef App_Lin_LIN1_START_SEC_INTERNAL_VAR_CLEARED_16
  #define RTE_App_Lin_LIN1_START_SEC_INTERNAL_VAR_CLEARED_16
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_STOP_SEC_INTERNAL_VAR_CLEARED_16)
  #undef App_Lin_LIN1_STOP_SEC_INTERNAL_VAR_CLEARED_16
  #define RTE_App_Lin_LIN1_STOP_SEC_INTERNAL_VAR_CLEARED_16
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_START_SEC_INTERNAL_VAR_CLEARED_32)
  #undef App_Lin_LIN1_START_SEC_INTERNAL_VAR_CLEARED_32
  #define RTE_App_Lin_LIN1_START_SEC_INTERNAL_VAR_CLEARED_32
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_STOP_SEC_INTERNAL_VAR_CLEARED_32)
  #undef App_Lin_LIN1_STOP_SEC_INTERNAL_VAR_CLEARED_32
  #define RTE_App_Lin_LIN1_STOP_SEC_INTERNAL_VAR_CLEARED_32
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_START_SEC_INTERNAL_VAR_CLEARED_8)
  #undef App_Lin_LIN1_START_SEC_INTERNAL_VAR_CLEARED_8
  #define RTE_App_Lin_LIN1_START_SEC_INTERNAL_VAR_CLEARED_8
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_STOP_SEC_INTERNAL_VAR_CLEARED_8)
  #undef App_Lin_LIN1_STOP_SEC_INTERNAL_VAR_CLEARED_8
  #define RTE_App_Lin_LIN1_STOP_SEC_INTERNAL_VAR_CLEARED_8
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_START_SEC_INTERNAL_VAR_CLEARED_BOOLEAN)
  #undef App_Lin_LIN1_START_SEC_INTERNAL_VAR_CLEARED_BOOLEAN
  #define RTE_App_Lin_LIN1_START_SEC_INTERNAL_VAR_CLEARED_BOOLEAN
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_STOP_SEC_INTERNAL_VAR_CLEARED_BOOLEAN)
  #undef App_Lin_LIN1_STOP_SEC_INTERNAL_VAR_CLEARED_BOOLEAN
  #define RTE_App_Lin_LIN1_STOP_SEC_INTERNAL_VAR_CLEARED_BOOLEAN
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_START_SEC_INTERNAL_VAR_CLEARED_UNSPECIFIED)
  #undef App_Lin_LIN1_START_SEC_INTERNAL_VAR_CLEARED_UNSPECIFIED
  #define RTE_App_Lin_LIN1_START_SEC_INTERNAL_VAR_CLEARED_UNSPECIFIED
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_STOP_SEC_INTERNAL_VAR_CLEARED_UNSPECIFIED)
  #undef App_Lin_LIN1_STOP_SEC_INTERNAL_VAR_CLEARED_UNSPECIFIED
  #define RTE_App_Lin_LIN1_STOP_SEC_INTERNAL_VAR_CLEARED_UNSPECIFIED
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_START_SEC_INTERNAL_VAR_INIT_16)
  #undef App_Lin_LIN1_START_SEC_INTERNAL_VAR_INIT_16
  #define RTE_App_Lin_LIN1_START_SEC_INTERNAL_VAR_INIT_16
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_STOP_SEC_INTERNAL_VAR_INIT_16)
  #undef App_Lin_LIN1_STOP_SEC_INTERNAL_VAR_INIT_16
  #define RTE_App_Lin_LIN1_STOP_SEC_INTERNAL_VAR_INIT_16
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_START_SEC_INTERNAL_VAR_INIT_32)
  #undef App_Lin_LIN1_START_SEC_INTERNAL_VAR_INIT_32
  #define RTE_App_Lin_LIN1_START_SEC_INTERNAL_VAR_INIT_32
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_STOP_SEC_INTERNAL_VAR_INIT_32)
  #undef App_Lin_LIN1_STOP_SEC_INTERNAL_VAR_INIT_32
  #define RTE_App_Lin_LIN1_STOP_SEC_INTERNAL_VAR_INIT_32
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_START_SEC_INTERNAL_VAR_INIT_8)
  #undef App_Lin_LIN1_START_SEC_INTERNAL_VAR_INIT_8
  #define RTE_App_Lin_LIN1_START_SEC_INTERNAL_VAR_INIT_8
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_STOP_SEC_INTERNAL_VAR_INIT_8)
  #undef App_Lin_LIN1_STOP_SEC_INTERNAL_VAR_INIT_8
  #define RTE_App_Lin_LIN1_STOP_SEC_INTERNAL_VAR_INIT_8
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_START_SEC_INTERNAL_VAR_INIT_BOOLEAN)
  #undef App_Lin_LIN1_START_SEC_INTERNAL_VAR_INIT_BOOLEAN
  #define RTE_App_Lin_LIN1_START_SEC_INTERNAL_VAR_INIT_BOOLEAN
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_STOP_SEC_INTERNAL_VAR_INIT_BOOLEAN)
  #undef App_Lin_LIN1_STOP_SEC_INTERNAL_VAR_INIT_BOOLEAN
  #define RTE_App_Lin_LIN1_STOP_SEC_INTERNAL_VAR_INIT_BOOLEAN
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_START_SEC_INTERNAL_VAR_INIT_UNSPECIFIED)
  #undef App_Lin_LIN1_START_SEC_INTERNAL_VAR_INIT_UNSPECIFIED
  #define RTE_App_Lin_LIN1_START_SEC_INTERNAL_VAR_INIT_UNSPECIFIED
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_STOP_SEC_INTERNAL_VAR_INIT_UNSPECIFIED)
  #undef App_Lin_LIN1_STOP_SEC_INTERNAL_VAR_INIT_UNSPECIFIED
  #define RTE_App_Lin_LIN1_STOP_SEC_INTERNAL_VAR_INIT_UNSPECIFIED
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_START_SEC_INTERNAL_VAR_NO_INIT_16)
  #undef App_Lin_LIN1_START_SEC_INTERNAL_VAR_NO_INIT_16
  #define RTE_App_Lin_LIN1_START_SEC_INTERNAL_VAR_NO_INIT_16
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_STOP_SEC_INTERNAL_VAR_NO_INIT_16)
  #undef App_Lin_LIN1_STOP_SEC_INTERNAL_VAR_NO_INIT_16
  #define RTE_App_Lin_LIN1_STOP_SEC_INTERNAL_VAR_NO_INIT_16
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_START_SEC_INTERNAL_VAR_NO_INIT_32)
  #undef App_Lin_LIN1_START_SEC_INTERNAL_VAR_NO_INIT_32
  #define RTE_App_Lin_LIN1_START_SEC_INTERNAL_VAR_NO_INIT_32
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_STOP_SEC_INTERNAL_VAR_NO_INIT_32)
  #undef App_Lin_LIN1_STOP_SEC_INTERNAL_VAR_NO_INIT_32
  #define RTE_App_Lin_LIN1_STOP_SEC_INTERNAL_VAR_NO_INIT_32
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_START_SEC_INTERNAL_VAR_NO_INIT_8)
  #undef App_Lin_LIN1_START_SEC_INTERNAL_VAR_NO_INIT_8
  #define RTE_App_Lin_LIN1_START_SEC_INTERNAL_VAR_NO_INIT_8
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_STOP_SEC_INTERNAL_VAR_NO_INIT_8)
  #undef App_Lin_LIN1_STOP_SEC_INTERNAL_VAR_NO_INIT_8
  #define RTE_App_Lin_LIN1_STOP_SEC_INTERNAL_VAR_NO_INIT_8
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_START_SEC_INTERNAL_VAR_NO_INIT_BOOLEAN)
  #undef App_Lin_LIN1_START_SEC_INTERNAL_VAR_NO_INIT_BOOLEAN
  #define RTE_App_Lin_LIN1_START_SEC_INTERNAL_VAR_NO_INIT_BOOLEAN
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_STOP_SEC_INTERNAL_VAR_NO_INIT_BOOLEAN)
  #undef App_Lin_LIN1_STOP_SEC_INTERNAL_VAR_NO_INIT_BOOLEAN
  #define RTE_App_Lin_LIN1_STOP_SEC_INTERNAL_VAR_NO_INIT_BOOLEAN
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_START_SEC_INTERNAL_VAR_NO_INIT_UNSPECIFIED)
  #undef App_Lin_LIN1_START_SEC_INTERNAL_VAR_NO_INIT_UNSPECIFIED
  #define RTE_App_Lin_LIN1_START_SEC_INTERNAL_VAR_NO_INIT_UNSPECIFIED
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_STOP_SEC_INTERNAL_VAR_NO_INIT_UNSPECIFIED)
  #undef App_Lin_LIN1_STOP_SEC_INTERNAL_VAR_NO_INIT_UNSPECIFIED
  #define RTE_App_Lin_LIN1_STOP_SEC_INTERNAL_VAR_NO_INIT_UNSPECIFIED
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_START_SEC_INTERNAL_VAR_POWER_ON_CLEARED_16)
  #undef App_Lin_LIN1_START_SEC_INTERNAL_VAR_POWER_ON_CLEARED_16
  #define RTE_App_Lin_LIN1_START_SEC_INTERNAL_VAR_POWER_ON_CLEARED_16
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_STOP_SEC_INTERNAL_VAR_POWER_ON_CLEARED_16)
  #undef App_Lin_LIN1_STOP_SEC_INTERNAL_VAR_POWER_ON_CLEARED_16
  #define RTE_App_Lin_LIN1_STOP_SEC_INTERNAL_VAR_POWER_ON_CLEARED_16
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_START_SEC_INTERNAL_VAR_POWER_ON_CLEARED_32)
  #undef App_Lin_LIN1_START_SEC_INTERNAL_VAR_POWER_ON_CLEARED_32
  #define RTE_App_Lin_LIN1_START_SEC_INTERNAL_VAR_POWER_ON_CLEARED_32
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_STOP_SEC_INTERNAL_VAR_POWER_ON_CLEARED_32)
  #undef App_Lin_LIN1_STOP_SEC_INTERNAL_VAR_POWER_ON_CLEARED_32
  #define RTE_App_Lin_LIN1_STOP_SEC_INTERNAL_VAR_POWER_ON_CLEARED_32
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_START_SEC_INTERNAL_VAR_POWER_ON_CLEARED_8)
  #undef App_Lin_LIN1_START_SEC_INTERNAL_VAR_POWER_ON_CLEARED_8
  #define RTE_App_Lin_LIN1_START_SEC_INTERNAL_VAR_POWER_ON_CLEARED_8
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_STOP_SEC_INTERNAL_VAR_POWER_ON_CLEARED_8)
  #undef App_Lin_LIN1_STOP_SEC_INTERNAL_VAR_POWER_ON_CLEARED_8
  #define RTE_App_Lin_LIN1_STOP_SEC_INTERNAL_VAR_POWER_ON_CLEARED_8
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_START_SEC_INTERNAL_VAR_POWER_ON_CLEARED_BOOLEAN)
  #undef App_Lin_LIN1_START_SEC_INTERNAL_VAR_POWER_ON_CLEARED_BOOLEAN
  #define RTE_App_Lin_LIN1_START_SEC_INTERNAL_VAR_POWER_ON_CLEARED_BOOLEAN
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_STOP_SEC_INTERNAL_VAR_POWER_ON_CLEARED_BOOLEAN)
  #undef App_Lin_LIN1_STOP_SEC_INTERNAL_VAR_POWER_ON_CLEARED_BOOLEAN
  #define RTE_App_Lin_LIN1_STOP_SEC_INTERNAL_VAR_POWER_ON_CLEARED_BOOLEAN
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_START_SEC_INTERNAL_VAR_POWER_ON_CLEARED_UNSPECIFIED)
  #undef App_Lin_LIN1_START_SEC_INTERNAL_VAR_POWER_ON_CLEARED_UNSPECIFIED
  #define RTE_App_Lin_LIN1_START_SEC_INTERNAL_VAR_POWER_ON_CLEARED_UNSPECIFIED
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_STOP_SEC_INTERNAL_VAR_POWER_ON_CLEARED_UNSPECIFIED)
  #undef App_Lin_LIN1_STOP_SEC_INTERNAL_VAR_POWER_ON_CLEARED_UNSPECIFIED
  #define RTE_App_Lin_LIN1_STOP_SEC_INTERNAL_VAR_POWER_ON_CLEARED_UNSPECIFIED
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_START_SEC_INTERNAL_VAR_POWER_ON_INIT_16)
  #undef App_Lin_LIN1_START_SEC_INTERNAL_VAR_POWER_ON_INIT_16
  #define RTE_App_Lin_LIN1_START_SEC_INTERNAL_VAR_POWER_ON_INIT_16
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_STOP_SEC_INTERNAL_VAR_POWER_ON_INIT_16)
  #undef App_Lin_LIN1_STOP_SEC_INTERNAL_VAR_POWER_ON_INIT_16
  #define RTE_App_Lin_LIN1_STOP_SEC_INTERNAL_VAR_POWER_ON_INIT_16
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_START_SEC_INTERNAL_VAR_POWER_ON_INIT_32)
  #undef App_Lin_LIN1_START_SEC_INTERNAL_VAR_POWER_ON_INIT_32
  #define RTE_App_Lin_LIN1_START_SEC_INTERNAL_VAR_POWER_ON_INIT_32
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_STOP_SEC_INTERNAL_VAR_POWER_ON_INIT_32)
  #undef App_Lin_LIN1_STOP_SEC_INTERNAL_VAR_POWER_ON_INIT_32
  #define RTE_App_Lin_LIN1_STOP_SEC_INTERNAL_VAR_POWER_ON_INIT_32
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_START_SEC_INTERNAL_VAR_POWER_ON_INIT_8)
  #undef App_Lin_LIN1_START_SEC_INTERNAL_VAR_POWER_ON_INIT_8
  #define RTE_App_Lin_LIN1_START_SEC_INTERNAL_VAR_POWER_ON_INIT_8
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_STOP_SEC_INTERNAL_VAR_POWER_ON_INIT_8)
  #undef App_Lin_LIN1_STOP_SEC_INTERNAL_VAR_POWER_ON_INIT_8
  #define RTE_App_Lin_LIN1_STOP_SEC_INTERNAL_VAR_POWER_ON_INIT_8
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_START_SEC_INTERNAL_VAR_POWER_ON_INIT_BOOLEAN)
  #undef App_Lin_LIN1_START_SEC_INTERNAL_VAR_POWER_ON_INIT_BOOLEAN
  #define RTE_App_Lin_LIN1_START_SEC_INTERNAL_VAR_POWER_ON_INIT_BOOLEAN
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_STOP_SEC_INTERNAL_VAR_POWER_ON_INIT_BOOLEAN)
  #undef App_Lin_LIN1_STOP_SEC_INTERNAL_VAR_POWER_ON_INIT_BOOLEAN
  #define RTE_App_Lin_LIN1_STOP_SEC_INTERNAL_VAR_POWER_ON_INIT_BOOLEAN
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_START_SEC_INTERNAL_VAR_POWER_ON_INIT_UNSPECIFIED)
  #undef App_Lin_LIN1_START_SEC_INTERNAL_VAR_POWER_ON_INIT_UNSPECIFIED
  #define RTE_App_Lin_LIN1_START_SEC_INTERNAL_VAR_POWER_ON_INIT_UNSPECIFIED
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_STOP_SEC_INTERNAL_VAR_POWER_ON_INIT_UNSPECIFIED)
  #undef App_Lin_LIN1_STOP_SEC_INTERNAL_VAR_POWER_ON_INIT_UNSPECIFIED
  #define RTE_App_Lin_LIN1_STOP_SEC_INTERNAL_VAR_POWER_ON_INIT_UNSPECIFIED
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_START_SEC_VAR_CLEARED_16)
  #undef App_Lin_LIN1_START_SEC_VAR_CLEARED_16
  #define RTE_App_Lin_LIN1_START_SEC_VAR_CLEARED_16
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_STOP_SEC_VAR_CLEARED_16)
  #undef App_Lin_LIN1_STOP_SEC_VAR_CLEARED_16
  #define RTE_App_Lin_LIN1_STOP_SEC_VAR_CLEARED_16
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_START_SEC_VAR_CLEARED_32)
  #undef App_Lin_LIN1_START_SEC_VAR_CLEARED_32
  #define RTE_App_Lin_LIN1_START_SEC_VAR_CLEARED_32
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_STOP_SEC_VAR_CLEARED_32)
  #undef App_Lin_LIN1_STOP_SEC_VAR_CLEARED_32
  #define RTE_App_Lin_LIN1_STOP_SEC_VAR_CLEARED_32
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_START_SEC_VAR_CLEARED_8)
  #undef App_Lin_LIN1_START_SEC_VAR_CLEARED_8
  #define RTE_App_Lin_LIN1_START_SEC_VAR_CLEARED_8
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_STOP_SEC_VAR_CLEARED_8)
  #undef App_Lin_LIN1_STOP_SEC_VAR_CLEARED_8
  #define RTE_App_Lin_LIN1_STOP_SEC_VAR_CLEARED_8
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_START_SEC_VAR_CLEARED_BOOLEAN)
  #undef App_Lin_LIN1_START_SEC_VAR_CLEARED_BOOLEAN
  #define RTE_App_Lin_LIN1_START_SEC_VAR_CLEARED_BOOLEAN
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_STOP_SEC_VAR_CLEARED_BOOLEAN)
  #undef App_Lin_LIN1_STOP_SEC_VAR_CLEARED_BOOLEAN
  #define RTE_App_Lin_LIN1_STOP_SEC_VAR_CLEARED_BOOLEAN
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_START_SEC_VAR_CLEARED_UNSPECIFIED)
  #undef App_Lin_LIN1_START_SEC_VAR_CLEARED_UNSPECIFIED
  #define RTE_App_Lin_LIN1_START_SEC_VAR_CLEARED_UNSPECIFIED
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_STOP_SEC_VAR_CLEARED_UNSPECIFIED)
  #undef App_Lin_LIN1_STOP_SEC_VAR_CLEARED_UNSPECIFIED
  #define RTE_App_Lin_LIN1_STOP_SEC_VAR_CLEARED_UNSPECIFIED
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_START_SEC_VAR_FAST_CLEARED_16)
  #undef App_Lin_LIN1_START_SEC_VAR_FAST_CLEARED_16
  #define RTE_App_Lin_LIN1_START_SEC_VAR_FAST_CLEARED_16
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_STOP_SEC_VAR_FAST_CLEARED_16)
  #undef App_Lin_LIN1_STOP_SEC_VAR_FAST_CLEARED_16
  #define RTE_App_Lin_LIN1_STOP_SEC_VAR_FAST_CLEARED_16
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_START_SEC_VAR_FAST_CLEARED_32)
  #undef App_Lin_LIN1_START_SEC_VAR_FAST_CLEARED_32
  #define RTE_App_Lin_LIN1_START_SEC_VAR_FAST_CLEARED_32
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_STOP_SEC_VAR_FAST_CLEARED_32)
  #undef App_Lin_LIN1_STOP_SEC_VAR_FAST_CLEARED_32
  #define RTE_App_Lin_LIN1_STOP_SEC_VAR_FAST_CLEARED_32
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_START_SEC_VAR_FAST_CLEARED_8)
  #undef App_Lin_LIN1_START_SEC_VAR_FAST_CLEARED_8
  #define RTE_App_Lin_LIN1_START_SEC_VAR_FAST_CLEARED_8
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_STOP_SEC_VAR_FAST_CLEARED_8)
  #undef App_Lin_LIN1_STOP_SEC_VAR_FAST_CLEARED_8
  #define RTE_App_Lin_LIN1_STOP_SEC_VAR_FAST_CLEARED_8
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_START_SEC_VAR_FAST_CLEARED_BOOLEAN)
  #undef App_Lin_LIN1_START_SEC_VAR_FAST_CLEARED_BOOLEAN
  #define RTE_App_Lin_LIN1_START_SEC_VAR_FAST_CLEARED_BOOLEAN
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_STOP_SEC_VAR_FAST_CLEARED_BOOLEAN)
  #undef App_Lin_LIN1_STOP_SEC_VAR_FAST_CLEARED_BOOLEAN
  #define RTE_App_Lin_LIN1_STOP_SEC_VAR_FAST_CLEARED_BOOLEAN
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_START_SEC_VAR_FAST_CLEARED_UNSPECIFIED)
  #undef App_Lin_LIN1_START_SEC_VAR_FAST_CLEARED_UNSPECIFIED
  #define RTE_App_Lin_LIN1_START_SEC_VAR_FAST_CLEARED_UNSPECIFIED
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_STOP_SEC_VAR_FAST_CLEARED_UNSPECIFIED)
  #undef App_Lin_LIN1_STOP_SEC_VAR_FAST_CLEARED_UNSPECIFIED
  #define RTE_App_Lin_LIN1_STOP_SEC_VAR_FAST_CLEARED_UNSPECIFIED
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_START_SEC_VAR_FAST_INIT_16)
  #undef App_Lin_LIN1_START_SEC_VAR_FAST_INIT_16
  #define RTE_App_Lin_LIN1_START_SEC_VAR_FAST_INIT_16
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_STOP_SEC_VAR_FAST_INIT_16)
  #undef App_Lin_LIN1_STOP_SEC_VAR_FAST_INIT_16
  #define RTE_App_Lin_LIN1_STOP_SEC_VAR_FAST_INIT_16
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_START_SEC_VAR_FAST_INIT_32)
  #undef App_Lin_LIN1_START_SEC_VAR_FAST_INIT_32
  #define RTE_App_Lin_LIN1_START_SEC_VAR_FAST_INIT_32
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_STOP_SEC_VAR_FAST_INIT_32)
  #undef App_Lin_LIN1_STOP_SEC_VAR_FAST_INIT_32
  #define RTE_App_Lin_LIN1_STOP_SEC_VAR_FAST_INIT_32
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_START_SEC_VAR_FAST_INIT_8)
  #undef App_Lin_LIN1_START_SEC_VAR_FAST_INIT_8
  #define RTE_App_Lin_LIN1_START_SEC_VAR_FAST_INIT_8
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_STOP_SEC_VAR_FAST_INIT_8)
  #undef App_Lin_LIN1_STOP_SEC_VAR_FAST_INIT_8
  #define RTE_App_Lin_LIN1_STOP_SEC_VAR_FAST_INIT_8
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_START_SEC_VAR_FAST_INIT_BOOLEAN)
  #undef App_Lin_LIN1_START_SEC_VAR_FAST_INIT_BOOLEAN
  #define RTE_App_Lin_LIN1_START_SEC_VAR_FAST_INIT_BOOLEAN
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_STOP_SEC_VAR_FAST_INIT_BOOLEAN)
  #undef App_Lin_LIN1_STOP_SEC_VAR_FAST_INIT_BOOLEAN
  #define RTE_App_Lin_LIN1_STOP_SEC_VAR_FAST_INIT_BOOLEAN
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_START_SEC_VAR_FAST_INIT_UNSPECIFIED)
  #undef App_Lin_LIN1_START_SEC_VAR_FAST_INIT_UNSPECIFIED
  #define RTE_App_Lin_LIN1_START_SEC_VAR_FAST_INIT_UNSPECIFIED
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_STOP_SEC_VAR_FAST_INIT_UNSPECIFIED)
  #undef App_Lin_LIN1_STOP_SEC_VAR_FAST_INIT_UNSPECIFIED
  #define RTE_App_Lin_LIN1_STOP_SEC_VAR_FAST_INIT_UNSPECIFIED
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_START_SEC_VAR_FAST_NO_INIT_16)
  #undef App_Lin_LIN1_START_SEC_VAR_FAST_NO_INIT_16
  #define RTE_App_Lin_LIN1_START_SEC_VAR_FAST_NO_INIT_16
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_STOP_SEC_VAR_FAST_NO_INIT_16)
  #undef App_Lin_LIN1_STOP_SEC_VAR_FAST_NO_INIT_16
  #define RTE_App_Lin_LIN1_STOP_SEC_VAR_FAST_NO_INIT_16
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_START_SEC_VAR_FAST_NO_INIT_32)
  #undef App_Lin_LIN1_START_SEC_VAR_FAST_NO_INIT_32
  #define RTE_App_Lin_LIN1_START_SEC_VAR_FAST_NO_INIT_32
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_STOP_SEC_VAR_FAST_NO_INIT_32)
  #undef App_Lin_LIN1_STOP_SEC_VAR_FAST_NO_INIT_32
  #define RTE_App_Lin_LIN1_STOP_SEC_VAR_FAST_NO_INIT_32
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_START_SEC_VAR_FAST_NO_INIT_8)
  #undef App_Lin_LIN1_START_SEC_VAR_FAST_NO_INIT_8
  #define RTE_App_Lin_LIN1_START_SEC_VAR_FAST_NO_INIT_8
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_STOP_SEC_VAR_FAST_NO_INIT_8)
  #undef App_Lin_LIN1_STOP_SEC_VAR_FAST_NO_INIT_8
  #define RTE_App_Lin_LIN1_STOP_SEC_VAR_FAST_NO_INIT_8
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_START_SEC_VAR_FAST_NO_INIT_BOOLEAN)
  #undef App_Lin_LIN1_START_SEC_VAR_FAST_NO_INIT_BOOLEAN
  #define RTE_App_Lin_LIN1_START_SEC_VAR_FAST_NO_INIT_BOOLEAN
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_STOP_SEC_VAR_FAST_NO_INIT_BOOLEAN)
  #undef App_Lin_LIN1_STOP_SEC_VAR_FAST_NO_INIT_BOOLEAN
  #define RTE_App_Lin_LIN1_STOP_SEC_VAR_FAST_NO_INIT_BOOLEAN
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_START_SEC_VAR_FAST_NO_INIT_UNSPECIFIED)
  #undef App_Lin_LIN1_START_SEC_VAR_FAST_NO_INIT_UNSPECIFIED
  #define RTE_App_Lin_LIN1_START_SEC_VAR_FAST_NO_INIT_UNSPECIFIED
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_STOP_SEC_VAR_FAST_NO_INIT_UNSPECIFIED)
  #undef App_Lin_LIN1_STOP_SEC_VAR_FAST_NO_INIT_UNSPECIFIED
  #define RTE_App_Lin_LIN1_STOP_SEC_VAR_FAST_NO_INIT_UNSPECIFIED
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_START_SEC_VAR_FAST_POWER_ON_CLEARED_16)
  #undef App_Lin_LIN1_START_SEC_VAR_FAST_POWER_ON_CLEARED_16
  #define RTE_App_Lin_LIN1_START_SEC_VAR_FAST_POWER_ON_CLEARED_16
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_STOP_SEC_VAR_FAST_POWER_ON_CLEARED_16)
  #undef App_Lin_LIN1_STOP_SEC_VAR_FAST_POWER_ON_CLEARED_16
  #define RTE_App_Lin_LIN1_STOP_SEC_VAR_FAST_POWER_ON_CLEARED_16
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_START_SEC_VAR_FAST_POWER_ON_CLEARED_32)
  #undef App_Lin_LIN1_START_SEC_VAR_FAST_POWER_ON_CLEARED_32
  #define RTE_App_Lin_LIN1_START_SEC_VAR_FAST_POWER_ON_CLEARED_32
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_STOP_SEC_VAR_FAST_POWER_ON_CLEARED_32)
  #undef App_Lin_LIN1_STOP_SEC_VAR_FAST_POWER_ON_CLEARED_32
  #define RTE_App_Lin_LIN1_STOP_SEC_VAR_FAST_POWER_ON_CLEARED_32
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_START_SEC_VAR_FAST_POWER_ON_CLEARED_8)
  #undef App_Lin_LIN1_START_SEC_VAR_FAST_POWER_ON_CLEARED_8
  #define RTE_App_Lin_LIN1_START_SEC_VAR_FAST_POWER_ON_CLEARED_8
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_STOP_SEC_VAR_FAST_POWER_ON_CLEARED_8)
  #undef App_Lin_LIN1_STOP_SEC_VAR_FAST_POWER_ON_CLEARED_8
  #define RTE_App_Lin_LIN1_STOP_SEC_VAR_FAST_POWER_ON_CLEARED_8
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_START_SEC_VAR_FAST_POWER_ON_CLEARED_BOOLEAN)
  #undef App_Lin_LIN1_START_SEC_VAR_FAST_POWER_ON_CLEARED_BOOLEAN
  #define RTE_App_Lin_LIN1_START_SEC_VAR_FAST_POWER_ON_CLEARED_BOOLEAN
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_STOP_SEC_VAR_FAST_POWER_ON_CLEARED_BOOLEAN)
  #undef App_Lin_LIN1_STOP_SEC_VAR_FAST_POWER_ON_CLEARED_BOOLEAN
  #define RTE_App_Lin_LIN1_STOP_SEC_VAR_FAST_POWER_ON_CLEARED_BOOLEAN
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_START_SEC_VAR_FAST_POWER_ON_CLEARED_UNSPECIFIED)
  #undef App_Lin_LIN1_START_SEC_VAR_FAST_POWER_ON_CLEARED_UNSPECIFIED
  #define RTE_App_Lin_LIN1_START_SEC_VAR_FAST_POWER_ON_CLEARED_UNSPECIFIED
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_STOP_SEC_VAR_FAST_POWER_ON_CLEARED_UNSPECIFIED)
  #undef App_Lin_LIN1_STOP_SEC_VAR_FAST_POWER_ON_CLEARED_UNSPECIFIED
  #define RTE_App_Lin_LIN1_STOP_SEC_VAR_FAST_POWER_ON_CLEARED_UNSPECIFIED
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_START_SEC_VAR_FAST_POWER_ON_INIT_16)
  #undef App_Lin_LIN1_START_SEC_VAR_FAST_POWER_ON_INIT_16
  #define RTE_App_Lin_LIN1_START_SEC_VAR_FAST_POWER_ON_INIT_16
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_STOP_SEC_VAR_FAST_POWER_ON_INIT_16)
  #undef App_Lin_LIN1_STOP_SEC_VAR_FAST_POWER_ON_INIT_16
  #define RTE_App_Lin_LIN1_STOP_SEC_VAR_FAST_POWER_ON_INIT_16
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_START_SEC_VAR_FAST_POWER_ON_INIT_32)
  #undef App_Lin_LIN1_START_SEC_VAR_FAST_POWER_ON_INIT_32
  #define RTE_App_Lin_LIN1_START_SEC_VAR_FAST_POWER_ON_INIT_32
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_STOP_SEC_VAR_FAST_POWER_ON_INIT_32)
  #undef App_Lin_LIN1_STOP_SEC_VAR_FAST_POWER_ON_INIT_32
  #define RTE_App_Lin_LIN1_STOP_SEC_VAR_FAST_POWER_ON_INIT_32
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_START_SEC_VAR_FAST_POWER_ON_INIT_8)
  #undef App_Lin_LIN1_START_SEC_VAR_FAST_POWER_ON_INIT_8
  #define RTE_App_Lin_LIN1_START_SEC_VAR_FAST_POWER_ON_INIT_8
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_STOP_SEC_VAR_FAST_POWER_ON_INIT_8)
  #undef App_Lin_LIN1_STOP_SEC_VAR_FAST_POWER_ON_INIT_8
  #define RTE_App_Lin_LIN1_STOP_SEC_VAR_FAST_POWER_ON_INIT_8
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_START_SEC_VAR_FAST_POWER_ON_INIT_BOOLEAN)
  #undef App_Lin_LIN1_START_SEC_VAR_FAST_POWER_ON_INIT_BOOLEAN
  #define RTE_App_Lin_LIN1_START_SEC_VAR_FAST_POWER_ON_INIT_BOOLEAN
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_STOP_SEC_VAR_FAST_POWER_ON_INIT_BOOLEAN)
  #undef App_Lin_LIN1_STOP_SEC_VAR_FAST_POWER_ON_INIT_BOOLEAN
  #define RTE_App_Lin_LIN1_STOP_SEC_VAR_FAST_POWER_ON_INIT_BOOLEAN
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_START_SEC_VAR_FAST_POWER_ON_INIT_UNSPECIFIED)
  #undef App_Lin_LIN1_START_SEC_VAR_FAST_POWER_ON_INIT_UNSPECIFIED
  #define RTE_App_Lin_LIN1_START_SEC_VAR_FAST_POWER_ON_INIT_UNSPECIFIED
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_STOP_SEC_VAR_FAST_POWER_ON_INIT_UNSPECIFIED)
  #undef App_Lin_LIN1_STOP_SEC_VAR_FAST_POWER_ON_INIT_UNSPECIFIED
  #define RTE_App_Lin_LIN1_STOP_SEC_VAR_FAST_POWER_ON_INIT_UNSPECIFIED
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_START_SEC_VAR_INIT_16)
  #undef App_Lin_LIN1_START_SEC_VAR_INIT_16
  #define RTE_App_Lin_LIN1_START_SEC_VAR_INIT_16
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_STOP_SEC_VAR_INIT_16)
  #undef App_Lin_LIN1_STOP_SEC_VAR_INIT_16
  #define RTE_App_Lin_LIN1_STOP_SEC_VAR_INIT_16
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_START_SEC_VAR_INIT_32)
  #undef App_Lin_LIN1_START_SEC_VAR_INIT_32
  #define RTE_App_Lin_LIN1_START_SEC_VAR_INIT_32
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_STOP_SEC_VAR_INIT_32)
  #undef App_Lin_LIN1_STOP_SEC_VAR_INIT_32
  #define RTE_App_Lin_LIN1_STOP_SEC_VAR_INIT_32
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_START_SEC_VAR_INIT_8)
  #undef App_Lin_LIN1_START_SEC_VAR_INIT_8
  #define RTE_App_Lin_LIN1_START_SEC_VAR_INIT_8
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_STOP_SEC_VAR_INIT_8)
  #undef App_Lin_LIN1_STOP_SEC_VAR_INIT_8
  #define RTE_App_Lin_LIN1_STOP_SEC_VAR_INIT_8
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_START_SEC_VAR_INIT_BOOLEAN)
  #undef App_Lin_LIN1_START_SEC_VAR_INIT_BOOLEAN
  #define RTE_App_Lin_LIN1_START_SEC_VAR_INIT_BOOLEAN
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_STOP_SEC_VAR_INIT_BOOLEAN)
  #undef App_Lin_LIN1_STOP_SEC_VAR_INIT_BOOLEAN
  #define RTE_App_Lin_LIN1_STOP_SEC_VAR_INIT_BOOLEAN
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_START_SEC_VAR_INIT_UNSPECIFIED)
  #undef App_Lin_LIN1_START_SEC_VAR_INIT_UNSPECIFIED
  #define RTE_App_Lin_LIN1_START_SEC_VAR_INIT_UNSPECIFIED
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_STOP_SEC_VAR_INIT_UNSPECIFIED)
  #undef App_Lin_LIN1_STOP_SEC_VAR_INIT_UNSPECIFIED
  #define RTE_App_Lin_LIN1_STOP_SEC_VAR_INIT_UNSPECIFIED
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_START_SEC_VAR_NO_INIT_16)
  #undef App_Lin_LIN1_START_SEC_VAR_NO_INIT_16
  #define RTE_App_Lin_LIN1_START_SEC_VAR_NO_INIT_16
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_STOP_SEC_VAR_NO_INIT_16)
  #undef App_Lin_LIN1_STOP_SEC_VAR_NO_INIT_16
  #define RTE_App_Lin_LIN1_STOP_SEC_VAR_NO_INIT_16
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_START_SEC_VAR_NO_INIT_32)
  #undef App_Lin_LIN1_START_SEC_VAR_NO_INIT_32
  #define RTE_App_Lin_LIN1_START_SEC_VAR_NO_INIT_32
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_STOP_SEC_VAR_NO_INIT_32)
  #undef App_Lin_LIN1_STOP_SEC_VAR_NO_INIT_32
  #define RTE_App_Lin_LIN1_STOP_SEC_VAR_NO_INIT_32
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_START_SEC_VAR_NO_INIT_8)
  #undef App_Lin_LIN1_START_SEC_VAR_NO_INIT_8
  #define RTE_App_Lin_LIN1_START_SEC_VAR_NO_INIT_8
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_STOP_SEC_VAR_NO_INIT_8)
  #undef App_Lin_LIN1_STOP_SEC_VAR_NO_INIT_8
  #define RTE_App_Lin_LIN1_STOP_SEC_VAR_NO_INIT_8
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_START_SEC_VAR_NO_INIT_BOOLEAN)
  #undef App_Lin_LIN1_START_SEC_VAR_NO_INIT_BOOLEAN
  #define RTE_App_Lin_LIN1_START_SEC_VAR_NO_INIT_BOOLEAN
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_STOP_SEC_VAR_NO_INIT_BOOLEAN)
  #undef App_Lin_LIN1_STOP_SEC_VAR_NO_INIT_BOOLEAN
  #define RTE_App_Lin_LIN1_STOP_SEC_VAR_NO_INIT_BOOLEAN
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_START_SEC_VAR_NO_INIT_UNSPECIFIED)
  #undef App_Lin_LIN1_START_SEC_VAR_NO_INIT_UNSPECIFIED
  #define RTE_App_Lin_LIN1_START_SEC_VAR_NO_INIT_UNSPECIFIED
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_STOP_SEC_VAR_NO_INIT_UNSPECIFIED)
  #undef App_Lin_LIN1_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
  #define RTE_App_Lin_LIN1_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_START_SEC_VAR_POWER_ON_CLEARED_16)
  #undef App_Lin_LIN1_START_SEC_VAR_POWER_ON_CLEARED_16
  #define RTE_App_Lin_LIN1_START_SEC_VAR_POWER_ON_CLEARED_16
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_STOP_SEC_VAR_POWER_ON_CLEARED_16)
  #undef App_Lin_LIN1_STOP_SEC_VAR_POWER_ON_CLEARED_16
  #define RTE_App_Lin_LIN1_STOP_SEC_VAR_POWER_ON_CLEARED_16
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_START_SEC_VAR_POWER_ON_CLEARED_32)
  #undef App_Lin_LIN1_START_SEC_VAR_POWER_ON_CLEARED_32
  #define RTE_App_Lin_LIN1_START_SEC_VAR_POWER_ON_CLEARED_32
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_STOP_SEC_VAR_POWER_ON_CLEARED_32)
  #undef App_Lin_LIN1_STOP_SEC_VAR_POWER_ON_CLEARED_32
  #define RTE_App_Lin_LIN1_STOP_SEC_VAR_POWER_ON_CLEARED_32
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_START_SEC_VAR_POWER_ON_CLEARED_8)
  #undef App_Lin_LIN1_START_SEC_VAR_POWER_ON_CLEARED_8
  #define RTE_App_Lin_LIN1_START_SEC_VAR_POWER_ON_CLEARED_8
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_STOP_SEC_VAR_POWER_ON_CLEARED_8)
  #undef App_Lin_LIN1_STOP_SEC_VAR_POWER_ON_CLEARED_8
  #define RTE_App_Lin_LIN1_STOP_SEC_VAR_POWER_ON_CLEARED_8
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_START_SEC_VAR_POWER_ON_CLEARED_BOOLEAN)
  #undef App_Lin_LIN1_START_SEC_VAR_POWER_ON_CLEARED_BOOLEAN
  #define RTE_App_Lin_LIN1_START_SEC_VAR_POWER_ON_CLEARED_BOOLEAN
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_STOP_SEC_VAR_POWER_ON_CLEARED_BOOLEAN)
  #undef App_Lin_LIN1_STOP_SEC_VAR_POWER_ON_CLEARED_BOOLEAN
  #define RTE_App_Lin_LIN1_STOP_SEC_VAR_POWER_ON_CLEARED_BOOLEAN
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_START_SEC_VAR_POWER_ON_CLEARED_UNSPECIFIED)
  #undef App_Lin_LIN1_START_SEC_VAR_POWER_ON_CLEARED_UNSPECIFIED
  #define RTE_App_Lin_LIN1_START_SEC_VAR_POWER_ON_CLEARED_UNSPECIFIED
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_STOP_SEC_VAR_POWER_ON_CLEARED_UNSPECIFIED)
  #undef App_Lin_LIN1_STOP_SEC_VAR_POWER_ON_CLEARED_UNSPECIFIED
  #define RTE_App_Lin_LIN1_STOP_SEC_VAR_POWER_ON_CLEARED_UNSPECIFIED
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_START_SEC_VAR_POWER_ON_INIT_16)
  #undef App_Lin_LIN1_START_SEC_VAR_POWER_ON_INIT_16
  #define RTE_App_Lin_LIN1_START_SEC_VAR_POWER_ON_INIT_16
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_STOP_SEC_VAR_POWER_ON_INIT_16)
  #undef App_Lin_LIN1_STOP_SEC_VAR_POWER_ON_INIT_16
  #define RTE_App_Lin_LIN1_STOP_SEC_VAR_POWER_ON_INIT_16
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_START_SEC_VAR_POWER_ON_INIT_32)
  #undef App_Lin_LIN1_START_SEC_VAR_POWER_ON_INIT_32
  #define RTE_App_Lin_LIN1_START_SEC_VAR_POWER_ON_INIT_32
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_STOP_SEC_VAR_POWER_ON_INIT_32)
  #undef App_Lin_LIN1_STOP_SEC_VAR_POWER_ON_INIT_32
  #define RTE_App_Lin_LIN1_STOP_SEC_VAR_POWER_ON_INIT_32
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_START_SEC_VAR_POWER_ON_INIT_8)
  #undef App_Lin_LIN1_START_SEC_VAR_POWER_ON_INIT_8
  #define RTE_App_Lin_LIN1_START_SEC_VAR_POWER_ON_INIT_8
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_STOP_SEC_VAR_POWER_ON_INIT_8)
  #undef App_Lin_LIN1_STOP_SEC_VAR_POWER_ON_INIT_8
  #define RTE_App_Lin_LIN1_STOP_SEC_VAR_POWER_ON_INIT_8
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_START_SEC_VAR_POWER_ON_INIT_BOOLEAN)
  #undef App_Lin_LIN1_START_SEC_VAR_POWER_ON_INIT_BOOLEAN
  #define RTE_App_Lin_LIN1_START_SEC_VAR_POWER_ON_INIT_BOOLEAN
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_STOP_SEC_VAR_POWER_ON_INIT_BOOLEAN)
  #undef App_Lin_LIN1_STOP_SEC_VAR_POWER_ON_INIT_BOOLEAN
  #define RTE_App_Lin_LIN1_STOP_SEC_VAR_POWER_ON_INIT_BOOLEAN
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_START_SEC_VAR_POWER_ON_INIT_UNSPECIFIED)
  #undef App_Lin_LIN1_START_SEC_VAR_POWER_ON_INIT_UNSPECIFIED
  #define RTE_App_Lin_LIN1_START_SEC_VAR_POWER_ON_INIT_UNSPECIFIED
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_STOP_SEC_VAR_POWER_ON_INIT_UNSPECIFIED)
  #undef App_Lin_LIN1_STOP_SEC_VAR_POWER_ON_INIT_UNSPECIFIED
  #define RTE_App_Lin_LIN1_STOP_SEC_VAR_POWER_ON_INIT_UNSPECIFIED
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_START_SEC_VAR_SAVED_ZONE_16)
  #undef App_Lin_LIN1_START_SEC_VAR_SAVED_ZONE_16
  #define RTE_App_Lin_LIN1_START_SEC_VAR_SAVED_ZONE_16
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_STOP_SEC_VAR_SAVED_ZONE_16)
  #undef App_Lin_LIN1_STOP_SEC_VAR_SAVED_ZONE_16
  #define RTE_App_Lin_LIN1_STOP_SEC_VAR_SAVED_ZONE_16
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_START_SEC_VAR_SAVED_ZONE_32)
  #undef App_Lin_LIN1_START_SEC_VAR_SAVED_ZONE_32
  #define RTE_App_Lin_LIN1_START_SEC_VAR_SAVED_ZONE_32
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_STOP_SEC_VAR_SAVED_ZONE_32)
  #undef App_Lin_LIN1_STOP_SEC_VAR_SAVED_ZONE_32
  #define RTE_App_Lin_LIN1_STOP_SEC_VAR_SAVED_ZONE_32
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_START_SEC_VAR_SAVED_ZONE_8)
  #undef App_Lin_LIN1_START_SEC_VAR_SAVED_ZONE_8
  #define RTE_App_Lin_LIN1_START_SEC_VAR_SAVED_ZONE_8
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_STOP_SEC_VAR_SAVED_ZONE_8)
  #undef App_Lin_LIN1_STOP_SEC_VAR_SAVED_ZONE_8
  #define RTE_App_Lin_LIN1_STOP_SEC_VAR_SAVED_ZONE_8
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_START_SEC_VAR_SAVED_ZONE_BOOLEAN)
  #undef App_Lin_LIN1_START_SEC_VAR_SAVED_ZONE_BOOLEAN
  #define RTE_App_Lin_LIN1_START_SEC_VAR_SAVED_ZONE_BOOLEAN
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_STOP_SEC_VAR_SAVED_ZONE_BOOLEAN)
  #undef App_Lin_LIN1_STOP_SEC_VAR_SAVED_ZONE_BOOLEAN
  #define RTE_App_Lin_LIN1_STOP_SEC_VAR_SAVED_ZONE_BOOLEAN
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_START_SEC_VAR_SAVED_ZONE_UNSPECIFIED)
  #undef App_Lin_LIN1_START_SEC_VAR_SAVED_ZONE_UNSPECIFIED
  #define RTE_App_Lin_LIN1_START_SEC_VAR_SAVED_ZONE_UNSPECIFIED
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_STOP_SEC_VAR_SAVED_ZONE_UNSPECIFIED)
  #undef App_Lin_LIN1_STOP_SEC_VAR_SAVED_ZONE_UNSPECIFIED
  #define RTE_App_Lin_LIN1_STOP_SEC_VAR_SAVED_ZONE_UNSPECIFIED
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_START_SEC_VAR_SLOW_CLEARED_16)
  #undef App_Lin_LIN1_START_SEC_VAR_SLOW_CLEARED_16
  #define RTE_App_Lin_LIN1_START_SEC_VAR_SLOW_CLEARED_16
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_STOP_SEC_VAR_SLOW_CLEARED_16)
  #undef App_Lin_LIN1_STOP_SEC_VAR_SLOW_CLEARED_16
  #define RTE_App_Lin_LIN1_STOP_SEC_VAR_SLOW_CLEARED_16
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_START_SEC_VAR_SLOW_CLEARED_32)
  #undef App_Lin_LIN1_START_SEC_VAR_SLOW_CLEARED_32
  #define RTE_App_Lin_LIN1_START_SEC_VAR_SLOW_CLEARED_32
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_STOP_SEC_VAR_SLOW_CLEARED_32)
  #undef App_Lin_LIN1_STOP_SEC_VAR_SLOW_CLEARED_32
  #define RTE_App_Lin_LIN1_STOP_SEC_VAR_SLOW_CLEARED_32
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_START_SEC_VAR_SLOW_CLEARED_8)
  #undef App_Lin_LIN1_START_SEC_VAR_SLOW_CLEARED_8
  #define RTE_App_Lin_LIN1_START_SEC_VAR_SLOW_CLEARED_8
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_STOP_SEC_VAR_SLOW_CLEARED_8)
  #undef App_Lin_LIN1_STOP_SEC_VAR_SLOW_CLEARED_8
  #define RTE_App_Lin_LIN1_STOP_SEC_VAR_SLOW_CLEARED_8
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_START_SEC_VAR_SLOW_CLEARED_BOOLEAN)
  #undef App_Lin_LIN1_START_SEC_VAR_SLOW_CLEARED_BOOLEAN
  #define RTE_App_Lin_LIN1_START_SEC_VAR_SLOW_CLEARED_BOOLEAN
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_STOP_SEC_VAR_SLOW_CLEARED_BOOLEAN)
  #undef App_Lin_LIN1_STOP_SEC_VAR_SLOW_CLEARED_BOOLEAN
  #define RTE_App_Lin_LIN1_STOP_SEC_VAR_SLOW_CLEARED_BOOLEAN
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_START_SEC_VAR_SLOW_CLEARED_UNSPECIFIED)
  #undef App_Lin_LIN1_START_SEC_VAR_SLOW_CLEARED_UNSPECIFIED
  #define RTE_App_Lin_LIN1_START_SEC_VAR_SLOW_CLEARED_UNSPECIFIED
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_STOP_SEC_VAR_SLOW_CLEARED_UNSPECIFIED)
  #undef App_Lin_LIN1_STOP_SEC_VAR_SLOW_CLEARED_UNSPECIFIED
  #define RTE_App_Lin_LIN1_STOP_SEC_VAR_SLOW_CLEARED_UNSPECIFIED
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_START_SEC_VAR_SLOW_INIT_16)
  #undef App_Lin_LIN1_START_SEC_VAR_SLOW_INIT_16
  #define RTE_App_Lin_LIN1_START_SEC_VAR_SLOW_INIT_16
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_STOP_SEC_VAR_SLOW_INIT_16)
  #undef App_Lin_LIN1_STOP_SEC_VAR_SLOW_INIT_16
  #define RTE_App_Lin_LIN1_STOP_SEC_VAR_SLOW_INIT_16
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_START_SEC_VAR_SLOW_INIT_32)
  #undef App_Lin_LIN1_START_SEC_VAR_SLOW_INIT_32
  #define RTE_App_Lin_LIN1_START_SEC_VAR_SLOW_INIT_32
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_STOP_SEC_VAR_SLOW_INIT_32)
  #undef App_Lin_LIN1_STOP_SEC_VAR_SLOW_INIT_32
  #define RTE_App_Lin_LIN1_STOP_SEC_VAR_SLOW_INIT_32
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_START_SEC_VAR_SLOW_INIT_8)
  #undef App_Lin_LIN1_START_SEC_VAR_SLOW_INIT_8
  #define RTE_App_Lin_LIN1_START_SEC_VAR_SLOW_INIT_8
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_STOP_SEC_VAR_SLOW_INIT_8)
  #undef App_Lin_LIN1_STOP_SEC_VAR_SLOW_INIT_8
  #define RTE_App_Lin_LIN1_STOP_SEC_VAR_SLOW_INIT_8
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_START_SEC_VAR_SLOW_INIT_BOOLEAN)
  #undef App_Lin_LIN1_START_SEC_VAR_SLOW_INIT_BOOLEAN
  #define RTE_App_Lin_LIN1_START_SEC_VAR_SLOW_INIT_BOOLEAN
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_STOP_SEC_VAR_SLOW_INIT_BOOLEAN)
  #undef App_Lin_LIN1_STOP_SEC_VAR_SLOW_INIT_BOOLEAN
  #define RTE_App_Lin_LIN1_STOP_SEC_VAR_SLOW_INIT_BOOLEAN
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_START_SEC_VAR_SLOW_INIT_UNSPECIFIED)
  #undef App_Lin_LIN1_START_SEC_VAR_SLOW_INIT_UNSPECIFIED
  #define RTE_App_Lin_LIN1_START_SEC_VAR_SLOW_INIT_UNSPECIFIED
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_STOP_SEC_VAR_SLOW_INIT_UNSPECIFIED)
  #undef App_Lin_LIN1_STOP_SEC_VAR_SLOW_INIT_UNSPECIFIED
  #define RTE_App_Lin_LIN1_STOP_SEC_VAR_SLOW_INIT_UNSPECIFIED
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_START_SEC_VAR_SLOW_NO_INIT_16)
  #undef App_Lin_LIN1_START_SEC_VAR_SLOW_NO_INIT_16
  #define RTE_App_Lin_LIN1_START_SEC_VAR_SLOW_NO_INIT_16
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_STOP_SEC_VAR_SLOW_NO_INIT_16)
  #undef App_Lin_LIN1_STOP_SEC_VAR_SLOW_NO_INIT_16
  #define RTE_App_Lin_LIN1_STOP_SEC_VAR_SLOW_NO_INIT_16
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_START_SEC_VAR_SLOW_NO_INIT_32)
  #undef App_Lin_LIN1_START_SEC_VAR_SLOW_NO_INIT_32
  #define RTE_App_Lin_LIN1_START_SEC_VAR_SLOW_NO_INIT_32
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_STOP_SEC_VAR_SLOW_NO_INIT_32)
  #undef App_Lin_LIN1_STOP_SEC_VAR_SLOW_NO_INIT_32
  #define RTE_App_Lin_LIN1_STOP_SEC_VAR_SLOW_NO_INIT_32
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_START_SEC_VAR_SLOW_NO_INIT_8)
  #undef App_Lin_LIN1_START_SEC_VAR_SLOW_NO_INIT_8
  #define RTE_App_Lin_LIN1_START_SEC_VAR_SLOW_NO_INIT_8
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_STOP_SEC_VAR_SLOW_NO_INIT_8)
  #undef App_Lin_LIN1_STOP_SEC_VAR_SLOW_NO_INIT_8
  #define RTE_App_Lin_LIN1_STOP_SEC_VAR_SLOW_NO_INIT_8
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_START_SEC_VAR_SLOW_NO_INIT_BOOLEAN)
  #undef App_Lin_LIN1_START_SEC_VAR_SLOW_NO_INIT_BOOLEAN
  #define RTE_App_Lin_LIN1_START_SEC_VAR_SLOW_NO_INIT_BOOLEAN
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_STOP_SEC_VAR_SLOW_NO_INIT_BOOLEAN)
  #undef App_Lin_LIN1_STOP_SEC_VAR_SLOW_NO_INIT_BOOLEAN
  #define RTE_App_Lin_LIN1_STOP_SEC_VAR_SLOW_NO_INIT_BOOLEAN
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_START_SEC_VAR_SLOW_NO_INIT_UNSPECIFIED)
  #undef App_Lin_LIN1_START_SEC_VAR_SLOW_NO_INIT_UNSPECIFIED
  #define RTE_App_Lin_LIN1_START_SEC_VAR_SLOW_NO_INIT_UNSPECIFIED
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_STOP_SEC_VAR_SLOW_NO_INIT_UNSPECIFIED)
  #undef App_Lin_LIN1_STOP_SEC_VAR_SLOW_NO_INIT_UNSPECIFIED
  #define RTE_App_Lin_LIN1_STOP_SEC_VAR_SLOW_NO_INIT_UNSPECIFIED
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_START_SEC_VAR_SLOW_POWER_ON_CLEARED_16)
  #undef App_Lin_LIN1_START_SEC_VAR_SLOW_POWER_ON_CLEARED_16
  #define RTE_App_Lin_LIN1_START_SEC_VAR_SLOW_POWER_ON_CLEARED_16
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_STOP_SEC_VAR_SLOW_POWER_ON_CLEARED_16)
  #undef App_Lin_LIN1_STOP_SEC_VAR_SLOW_POWER_ON_CLEARED_16
  #define RTE_App_Lin_LIN1_STOP_SEC_VAR_SLOW_POWER_ON_CLEARED_16
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_START_SEC_VAR_SLOW_POWER_ON_CLEARED_32)
  #undef App_Lin_LIN1_START_SEC_VAR_SLOW_POWER_ON_CLEARED_32
  #define RTE_App_Lin_LIN1_START_SEC_VAR_SLOW_POWER_ON_CLEARED_32
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_STOP_SEC_VAR_SLOW_POWER_ON_CLEARED_32)
  #undef App_Lin_LIN1_STOP_SEC_VAR_SLOW_POWER_ON_CLEARED_32
  #define RTE_App_Lin_LIN1_STOP_SEC_VAR_SLOW_POWER_ON_CLEARED_32
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_START_SEC_VAR_SLOW_POWER_ON_CLEARED_8)
  #undef App_Lin_LIN1_START_SEC_VAR_SLOW_POWER_ON_CLEARED_8
  #define RTE_App_Lin_LIN1_START_SEC_VAR_SLOW_POWER_ON_CLEARED_8
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_STOP_SEC_VAR_SLOW_POWER_ON_CLEARED_8)
  #undef App_Lin_LIN1_STOP_SEC_VAR_SLOW_POWER_ON_CLEARED_8
  #define RTE_App_Lin_LIN1_STOP_SEC_VAR_SLOW_POWER_ON_CLEARED_8
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_START_SEC_VAR_SLOW_POWER_ON_CLEARED_BOOLEAN)
  #undef App_Lin_LIN1_START_SEC_VAR_SLOW_POWER_ON_CLEARED_BOOLEAN
  #define RTE_App_Lin_LIN1_START_SEC_VAR_SLOW_POWER_ON_CLEARED_BOOLEAN
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_STOP_SEC_VAR_SLOW_POWER_ON_CLEARED_BOOLEAN)
  #undef App_Lin_LIN1_STOP_SEC_VAR_SLOW_POWER_ON_CLEARED_BOOLEAN
  #define RTE_App_Lin_LIN1_STOP_SEC_VAR_SLOW_POWER_ON_CLEARED_BOOLEAN
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_START_SEC_VAR_SLOW_POWER_ON_CLEARED_UNSPECIFIED)
  #undef App_Lin_LIN1_START_SEC_VAR_SLOW_POWER_ON_CLEARED_UNSPECIFIED
  #define RTE_App_Lin_LIN1_START_SEC_VAR_SLOW_POWER_ON_CLEARED_UNSPECIFIED
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_STOP_SEC_VAR_SLOW_POWER_ON_CLEARED_UNSPECIFIED)
  #undef App_Lin_LIN1_STOP_SEC_VAR_SLOW_POWER_ON_CLEARED_UNSPECIFIED
  #define RTE_App_Lin_LIN1_STOP_SEC_VAR_SLOW_POWER_ON_CLEARED_UNSPECIFIED
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_START_SEC_VAR_SLOW_POWER_ON_INIT_16)
  #undef App_Lin_LIN1_START_SEC_VAR_SLOW_POWER_ON_INIT_16
  #define RTE_App_Lin_LIN1_START_SEC_VAR_SLOW_POWER_ON_INIT_16
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_STOP_SEC_VAR_SLOW_POWER_ON_INIT_16)
  #undef App_Lin_LIN1_STOP_SEC_VAR_SLOW_POWER_ON_INIT_16
  #define RTE_App_Lin_LIN1_STOP_SEC_VAR_SLOW_POWER_ON_INIT_16
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_START_SEC_VAR_SLOW_POWER_ON_INIT_32)
  #undef App_Lin_LIN1_START_SEC_VAR_SLOW_POWER_ON_INIT_32
  #define RTE_App_Lin_LIN1_START_SEC_VAR_SLOW_POWER_ON_INIT_32
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_STOP_SEC_VAR_SLOW_POWER_ON_INIT_32)
  #undef App_Lin_LIN1_STOP_SEC_VAR_SLOW_POWER_ON_INIT_32
  #define RTE_App_Lin_LIN1_STOP_SEC_VAR_SLOW_POWER_ON_INIT_32
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_START_SEC_VAR_SLOW_POWER_ON_INIT_8)
  #undef App_Lin_LIN1_START_SEC_VAR_SLOW_POWER_ON_INIT_8
  #define RTE_App_Lin_LIN1_START_SEC_VAR_SLOW_POWER_ON_INIT_8
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_STOP_SEC_VAR_SLOW_POWER_ON_INIT_8)
  #undef App_Lin_LIN1_STOP_SEC_VAR_SLOW_POWER_ON_INIT_8
  #define RTE_App_Lin_LIN1_STOP_SEC_VAR_SLOW_POWER_ON_INIT_8
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_START_SEC_VAR_SLOW_POWER_ON_INIT_BOOLEAN)
  #undef App_Lin_LIN1_START_SEC_VAR_SLOW_POWER_ON_INIT_BOOLEAN
  #define RTE_App_Lin_LIN1_START_SEC_VAR_SLOW_POWER_ON_INIT_BOOLEAN
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_STOP_SEC_VAR_SLOW_POWER_ON_INIT_BOOLEAN)
  #undef App_Lin_LIN1_STOP_SEC_VAR_SLOW_POWER_ON_INIT_BOOLEAN
  #define RTE_App_Lin_LIN1_STOP_SEC_VAR_SLOW_POWER_ON_INIT_BOOLEAN
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_START_SEC_VAR_SLOW_POWER_ON_INIT_UNSPECIFIED)
  #undef App_Lin_LIN1_START_SEC_VAR_SLOW_POWER_ON_INIT_UNSPECIFIED
  #define RTE_App_Lin_LIN1_START_SEC_VAR_SLOW_POWER_ON_INIT_UNSPECIFIED
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_STOP_SEC_VAR_SLOW_POWER_ON_INIT_UNSPECIFIED)
  #undef App_Lin_LIN1_STOP_SEC_VAR_SLOW_POWER_ON_INIT_UNSPECIFIED
  #define RTE_App_Lin_LIN1_STOP_SEC_VAR_SLOW_POWER_ON_INIT_UNSPECIFIED
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_START_SEC_CALLOUT_CODE)
  #undef App_Lin_LIN1_START_SEC_CALLOUT_CODE
  #define RTE_App_Lin_LIN1_START_SEC_CALLOUT_CODE
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_STOP_SEC_CALLOUT_CODE)
  #undef App_Lin_LIN1_STOP_SEC_CALLOUT_CODE
  #define RTE_App_Lin_LIN1_STOP_SEC_CALLOUT_CODE
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_START_SEC_CODE)
  #undef App_Lin_LIN1_START_SEC_CODE
  #define RTE_App_Lin_LIN1_START_SEC_CODE
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_STOP_SEC_CODE)
  #undef App_Lin_LIN1_STOP_SEC_CODE
  #define RTE_App_Lin_LIN1_STOP_SEC_CODE
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_START_SEC_CODE_FAST)
  #undef App_Lin_LIN1_START_SEC_CODE_FAST
  #define RTE_App_Lin_LIN1_START_SEC_CODE_FAST
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_STOP_SEC_CODE_FAST)
  #undef App_Lin_LIN1_STOP_SEC_CODE_FAST
  #define RTE_App_Lin_LIN1_STOP_SEC_CODE_FAST
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_START_SEC_CODE_SLOW)
  #undef App_Lin_LIN1_START_SEC_CODE_SLOW
  #define RTE_App_Lin_LIN1_START_SEC_CODE_SLOW
  #include "MemMap.h"
#elif defined (App_Lin_LIN1_STOP_SEC_CODE_SLOW)
  #undef App_Lin_LIN1_STOP_SEC_CODE_SLOW
  #define RTE_App_Lin_LIN1_STOP_SEC_CODE_SLOW
  #include "MemMap.h"

#else

/*To be used if no memory section is found */
#error "App_Lin_LIN1_MemMap.h: No valid section define found"

#endif

/******************************************************************************/
/*                 Compatibility between C/C++ Languages End                  */
/******************************************************************************/
#ifdef __cplusplus
}
#endif

/******************************************************************************/
/*                              End of the file                               */
/******************************************************************************/
