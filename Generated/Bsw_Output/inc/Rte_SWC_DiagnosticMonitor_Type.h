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
**  File Name : Rte_SWC_DiagnosticMonitor_Type.h                              **
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
/*                 Multiple Header Inclusion Protection Start                 */
/******************************************************************************/
#ifndef RTE_SWC_DIAGNOSTICMONITOR_TYPE_H
#define RTE_SWC_DIAGNOSTICMONITOR_TYPE_H

/******************************************************************************/
/*                              Header Inclusion                              */
/******************************************************************************/
#include "Rte_Type.h"

/******************************************************************************/
/*                Compatibility between C/C++ Languages Start                 */
/******************************************************************************/
#ifdef __cplusplus
extern "C" 
{

#endif

/******************************************************************************/
/*                           Enumeration DataTypes                            */
/******************************************************************************/
#ifndef DEM_DTC_ORIGIN_PRIMARY_MEMORY
#define DEM_DTC_ORIGIN_PRIMARY_MEMORY                                         1U
#endif /* DEM_DTC_ORIGIN_PRIMARY_MEMORY */

#ifndef DEM_IUMPR_DEN_STATUS_REACHED
#define DEM_IUMPR_DEN_STATUS_REACHED                                          1U
#endif /* DEM_IUMPR_DEN_STATUS_REACHED */

#ifndef DEM_DTC_ORIGIN_MIRROR_MEMORY
#define DEM_DTC_ORIGIN_MIRROR_MEMORY                                          2U
#endif /* DEM_DTC_ORIGIN_MIRROR_MEMORY */

#ifndef DEM_DTC_FORMAT_OBD
#define DEM_DTC_FORMAT_OBD                                                    0U
#endif /* DEM_DTC_FORMAT_OBD */

#ifndef DEM_INDICATOR_BLINKING
#define DEM_INDICATOR_BLINKING                                                2U
#endif /* DEM_INDICATOR_BLINKING */

#ifndef DEM_INDICATOR_ON_DEMAND
#define DEM_INDICATOR_ON_DEMAND                                               6U
#endif /* DEM_INDICATOR_ON_DEMAND */

#ifndef DEM_DTC_ORIGIN_PERMANENT_MEMORY
#define DEM_DTC_ORIGIN_PERMANENT_MEMORY                                       3U
#endif /* DEM_DTC_ORIGIN_PERMANENT_MEMORY */

#ifndef DEM_EVENT_STATUS_FAILED
#define DEM_EVENT_STATUS_FAILED                                               1U
#endif /* DEM_EVENT_STATUS_FAILED */

#ifndef DEM_INIT_MONITOR_RESTART
#define DEM_INIT_MONITOR_RESTART                                              2U
#endif /* DEM_INIT_MONITOR_RESTART */

#ifndef DEM_DTR_CTL_NO_MIN
#define DEM_DTR_CTL_NO_MIN                                                    2U
#endif /* DEM_DTR_CTL_NO_MIN */

#ifndef DEM_INDICATOR_SLOW_FLASH
#define DEM_INDICATOR_SLOW_FLASH                                              4U
#endif /* DEM_INDICATOR_SLOW_FLASH */

#ifndef DEM_UDS_STATUS_TFTOC
#define DEM_UDS_STATUS_TFTOC                                                  2U
#endif /* DEM_UDS_STATUS_TFTOC */

#ifndef DEM_INIT_MONITOR_STORAGE_REENABLED
#define DEM_INIT_MONITOR_STORAGE_REENABLED                                    4U
#endif /* DEM_INIT_MONITOR_STORAGE_REENABLED */

#ifndef DEM_EVENT_STATUS_PREFAILED
#define DEM_EVENT_STATUS_PREFAILED                                            3U
#endif /* DEM_EVENT_STATUS_PREFAILED */

#ifndef DEM_INDICATOR_CONTINUOUS
#define DEM_INDICATOR_CONTINUOUS                                              1U
#endif /* DEM_INDICATOR_CONTINUOUS */

#ifndef DEM_DTC_FORMAT_OBD_3BYTE
#define DEM_DTC_FORMAT_OBD_3BYTE                                              3U
#endif /* DEM_DTC_FORMAT_OBD_3BYTE */

#ifndef DEM_UDS_STATUS_PDTC
#define DEM_UDS_STATUS_PDTC                                                   4U
#endif /* DEM_UDS_STATUS_PDTC */

#ifndef DEM_EVENT_STATUS_FDC_THRESHOLD_REACHED
#define DEM_EVENT_STATUS_FDC_THRESHOLD_REACHED                                4U
#endif /* DEM_EVENT_STATUS_FDC_THRESHOLD_REACHED */

#ifndef DEM_INIT_MONITOR_REENABLED
#define DEM_INIT_MONITOR_REENABLED                                            3U
#endif /* DEM_INIT_MONITOR_REENABLED */

#ifndef DEM_DTC_FORMAT_UDS
#define DEM_DTC_FORMAT_UDS                                                    1U
#endif /* DEM_DTC_FORMAT_UDS */

#ifndef DEM_DTR_CTL_NORMAL
#define DEM_DTR_CTL_NORMAL                                                    0U
#endif /* DEM_DTR_CTL_NORMAL */

#ifndef DEM_DTR_CTL_NO_MAX
#define DEM_DTR_CTL_NO_MAX                                                    1U
#endif /* DEM_DTR_CTL_NO_MAX */

#ifndef DEM_DTC_FORMAT_J1939
#define DEM_DTC_FORMAT_J1939                                                  2U
#endif /* DEM_DTC_FORMAT_J1939 */

#ifndef DEM_DTR_CTL_INVISIBLE
#define DEM_DTR_CTL_INVISIBLE                                                 4U
#endif /* DEM_DTR_CTL_INVISIBLE */

#ifndef DEM_DTR_CTL_RESET
#define DEM_DTR_CTL_RESET                                                     3U
#endif /* DEM_DTR_CTL_RESET */

#ifndef DEM_INIT_MONITOR_CLEAR
#define DEM_INIT_MONITOR_CLEAR                                                1U
#endif /* DEM_INIT_MONITOR_CLEAR */

#ifndef DEM_DTC_ORIGIN_OBD_RELEVANT_MEMORY
#define DEM_DTC_ORIGIN_OBD_RELEVANT_MEMORY                                    4U
#endif /* DEM_DTC_ORIGIN_OBD_RELEVANT_MEMORY */

#ifndef DEM_UDS_STATUS_TF
#define DEM_UDS_STATUS_TF                                                     1U
#endif /* DEM_UDS_STATUS_TF */

#ifndef DEM_IUMPR_DEN_STATUS_NOT_REACHED
#define DEM_IUMPR_DEN_STATUS_NOT_REACHED                                      0U
#endif /* DEM_IUMPR_DEN_STATUS_NOT_REACHED */

#ifndef DEM_DTC_ORIGIN_USERDEFINED_MEMORY_DEMUSERDEFINEDMEMORY0
#define DEM_DTC_ORIGIN_USERDEFINED_MEMORY_DEMUSERDEFINEDMEMORY0               0x0101U
#endif /* DEM_DTC_ORIGIN_USERDEFINED_MEMORY_DEMUSERDEFINEDMEMORY0 */

#ifndef DEM_INDICATOR_SHORT
#define DEM_INDICATOR_SHORT                                                   7U
#endif /* DEM_INDICATOR_SHORT */

#ifndef DEM_UDS_STATUS_WIR
#define DEM_UDS_STATUS_WIR                                                    128U
#endif /* DEM_UDS_STATUS_WIR */

#ifndef DEM_UDS_STATUS_TFSLC
#define DEM_UDS_STATUS_TFSLC                                                  32U
#endif /* DEM_UDS_STATUS_TFSLC */

#ifndef DEM_EVENT_STATUS_PASSED
#define DEM_EVENT_STATUS_PASSED                                               0U
#endif /* DEM_EVENT_STATUS_PASSED */

#ifndef DEM_UDS_STATUS_TNCSLC
#define DEM_UDS_STATUS_TNCSLC                                                 16U
#endif /* DEM_UDS_STATUS_TNCSLC */

#ifndef DEM_INDICATOR_OFF
#define DEM_INDICATOR_OFF                                                     0U
#endif /* DEM_INDICATOR_OFF */

#ifndef DEM_UDS_STATUS_TNCTOC
#define DEM_UDS_STATUS_TNCTOC                                                 64U
#endif /* DEM_UDS_STATUS_TNCTOC */

#ifndef DEM_IUMPR_DEN_STATUS_INHIBITED
#define DEM_IUMPR_DEN_STATUS_INHIBITED                                        2U
#endif /* DEM_IUMPR_DEN_STATUS_INHIBITED */

#ifndef DEM_INDICATOR_BLINK_CONT
#define DEM_INDICATOR_BLINK_CONT                                              3U
#endif /* DEM_INDICATOR_BLINK_CONT */

#ifndef DEM_INDICATOR_FAST_FLASH
#define DEM_INDICATOR_FAST_FLASH                                              5U
#endif /* DEM_INDICATOR_FAST_FLASH */

#ifndef DEM_EVENT_STATUS_PREPASSED
#define DEM_EVENT_STATUS_PREPASSED                                            2U
#endif /* DEM_EVENT_STATUS_PREPASSED */

#ifndef DEM_UDS_STATUS_CDTC
#define DEM_UDS_STATUS_CDTC                                                   8U
#endif /* DEM_UDS_STATUS_CDTC */

/******************************************************************************/
/*                 Compatibility between C/C++ Languages End                  */
/******************************************************************************/
#ifdef __cplusplus
}
#endif

/******************************************************************************/
/*                  Multiple Header Inclusion Protection End                  */
/******************************************************************************/
#endif

/******************************************************************************/
/*                              End of the file                               */
/******************************************************************************/
