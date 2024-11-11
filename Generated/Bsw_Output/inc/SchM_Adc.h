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
**  File Name : SchM_Adc.h                                                    **
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
#ifndef SCHM_ADC_H
#define SCHM_ADC_H

/******************************************************************************/
/*                              Header Inclusion                              */
/******************************************************************************/
#include "SchM_Adc_Type.h"
#include "Rte.h"
#include "Os.h"

/******************************************************************************/
/*                Compatibility between C/C++ Languages Start                 */
/******************************************************************************/
#ifdef __cplusplus
extern "C" 
{

#endif

/******************************************************************************/
/*                   BSW Activation Event Type definitions                    */
/******************************************************************************/

/******************************************************************************/
/*                        BSW Activating Event Macros                         */
/******************************************************************************/

/******************************************************************************/
/*                            SchM API Prototypes                             */
/******************************************************************************/

#define SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_101() do {\
 \
  (void) SuspendAllInterrupts(); \
} while(0);

#define SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_101() do {\
 \
  (void) ResumeAllInterrupts(); \
} while(0);
#define SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_102() do {\
 \
  (void) SuspendAllInterrupts(); \
} while(0);

#define SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_102() do {\
 \
  (void) ResumeAllInterrupts(); \
} while(0);
#define SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_103() do {\
 \
  (void) SuspendAllInterrupts(); \
} while(0);

#define SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_103() do {\
 \
  (void) ResumeAllInterrupts(); \
} while(0);
#define SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_00() do {\
 \
  (void) SuspendAllInterrupts(); \
} while(0);

#define SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_00() do {\
 \
  (void) ResumeAllInterrupts(); \
} while(0);
#define SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_01() do {\
 \
  (void) SuspendAllInterrupts(); \
} while(0);

#define SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_01() do {\
 \
  (void) ResumeAllInterrupts(); \
} while(0);
#define SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_02() do {\
 \
  (void) SuspendAllInterrupts(); \
} while(0);

#define SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_02() do {\
 \
  (void) ResumeAllInterrupts(); \
} while(0);
#define SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_03() do {\
 \
  (void) SuspendAllInterrupts(); \
} while(0);

#define SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_03() do {\
 \
  (void) ResumeAllInterrupts(); \
} while(0);
#define SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_04() do {\
 \
  (void) SuspendAllInterrupts(); \
} while(0);

#define SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_04() do {\
 \
  (void) ResumeAllInterrupts(); \
} while(0);
#define SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_05() do {\
 \
  (void) SuspendAllInterrupts(); \
} while(0);

#define SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_05() do {\
 \
  (void) ResumeAllInterrupts(); \
} while(0);
#define SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_10() do {\
 \
  (void) SuspendAllInterrupts(); \
} while(0);

#define SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_10() do {\
 \
  (void) ResumeAllInterrupts(); \
} while(0);
#define SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_11() do {\
 \
  (void) SuspendAllInterrupts(); \
} while(0);

#define SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_11() do {\
 \
  (void) ResumeAllInterrupts(); \
} while(0);
#define SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_12() do {\
 \
  (void) SuspendAllInterrupts(); \
} while(0);

#define SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_12() do {\
 \
  (void) ResumeAllInterrupts(); \
} while(0);
#define SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_13() do {\
 \
  (void) SuspendAllInterrupts(); \
} while(0);

#define SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_13() do {\
 \
  (void) ResumeAllInterrupts(); \
} while(0);
#define SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_14() do {\
 \
  (void) SuspendAllInterrupts(); \
} while(0);

#define SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_14() do {\
 \
  (void) ResumeAllInterrupts(); \
} while(0);
#define SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_15() do {\
 \
  (void) SuspendAllInterrupts(); \
} while(0);

#define SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_15() do {\
 \
  (void) ResumeAllInterrupts(); \
} while(0);
#define SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_16() do {\
 \
  (void) SuspendAllInterrupts(); \
} while(0);

#define SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_16() do {\
 \
  (void) ResumeAllInterrupts(); \
} while(0);
#define SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_17() do {\
 \
  (void) SuspendAllInterrupts(); \
} while(0);

#define SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_17() do {\
 \
  (void) ResumeAllInterrupts(); \
} while(0);
#define SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_18() do {\
 \
  (void) SuspendAllInterrupts(); \
} while(0);

#define SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_18() do {\
 \
  (void) ResumeAllInterrupts(); \
} while(0);
#define SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_19() do {\
 \
  (void) SuspendAllInterrupts(); \
} while(0);

#define SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_19() do {\
 \
  (void) ResumeAllInterrupts(); \
} while(0);
#define SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_20() do {\
 \
  (void) SuspendAllInterrupts(); \
} while(0);

#define SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_20() do {\
 \
  (void) ResumeAllInterrupts(); \
} while(0);
#define SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_21() do {\
 \
  (void) SuspendAllInterrupts(); \
} while(0);

#define SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_21() do {\
 \
  (void) ResumeAllInterrupts(); \
} while(0);
#define SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_22() do {\
 \
  (void) SuspendAllInterrupts(); \
} while(0);

#define SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_22() do {\
 \
  (void) ResumeAllInterrupts(); \
} while(0);
#define SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_23() do {\
 \
  (void) SuspendAllInterrupts(); \
} while(0);

#define SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_23() do {\
 \
  (void) ResumeAllInterrupts(); \
} while(0);
#define SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_24() do {\
 \
  (void) SuspendAllInterrupts(); \
} while(0);

#define SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_24() do {\
 \
  (void) ResumeAllInterrupts(); \
} while(0);
#define SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_25() do {\
 \
  (void) SuspendAllInterrupts(); \
} while(0);

#define SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_25() do {\
 \
  (void) ResumeAllInterrupts(); \
} while(0);
#define SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_26() do {\
 \
  (void) SuspendAllInterrupts(); \
} while(0);

#define SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_26() do {\
 \
  (void) ResumeAllInterrupts(); \
} while(0);
#define SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_27() do {\
 \
  (void) SuspendAllInterrupts(); \
} while(0);

#define SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_27() do {\
 \
  (void) ResumeAllInterrupts(); \
} while(0);
#define SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_28() do {\
 \
  (void) SuspendAllInterrupts(); \
} while(0);

#define SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_28() do {\
 \
  (void) ResumeAllInterrupts(); \
} while(0);
#define SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_29() do {\
 \
  (void) SuspendAllInterrupts(); \
} while(0);

#define SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_29() do {\
 \
  (void) ResumeAllInterrupts(); \
} while(0);
#define SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_30() do {\
 \
  (void) SuspendAllInterrupts(); \
} while(0);

#define SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_30() do {\
 \
  (void) ResumeAllInterrupts(); \
} while(0);
#define SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_31() do {\
 \
  (void) SuspendAllInterrupts(); \
} while(0);

#define SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_31() do {\
 \
  (void) ResumeAllInterrupts(); \
} while(0);
#define SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_32() do {\
 \
  (void) SuspendAllInterrupts(); \
} while(0);

#define SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_32() do {\
 \
  (void) ResumeAllInterrupts(); \
} while(0);
#define SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_33() do {\
 \
  (void) SuspendAllInterrupts(); \
} while(0);

#define SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_33() do {\
 \
  (void) ResumeAllInterrupts(); \
} while(0);
#define SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_34() do {\
 \
  (void) SuspendAllInterrupts(); \
} while(0);

#define SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_34() do {\
 \
  (void) ResumeAllInterrupts(); \
} while(0);
#define SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_35() do {\
 \
  (void) SuspendAllInterrupts(); \
} while(0);

#define SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_35() do {\
 \
  (void) ResumeAllInterrupts(); \
} while(0);
#define SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_36() do {\
 \
  (void) SuspendAllInterrupts(); \
} while(0);

#define SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_36() do {\
 \
  (void) ResumeAllInterrupts(); \
} while(0);
#define SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_37() do {\
 \
  (void) SuspendAllInterrupts(); \
} while(0);

#define SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_37() do {\
 \
  (void) ResumeAllInterrupts(); \
} while(0);
#define SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_38() do {\
 \
  (void) SuspendAllInterrupts(); \
} while(0);

#define SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_38() do {\
 \
  (void) ResumeAllInterrupts(); \
} while(0);
#define SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_39() do {\
 \
  (void) SuspendAllInterrupts(); \
} while(0);

#define SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_39() do {\
 \
  (void) ResumeAllInterrupts(); \
} while(0);
#define SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_40() do {\
 \
  (void) SuspendAllInterrupts(); \
} while(0);

#define SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_40() do {\
 \
  (void) ResumeAllInterrupts(); \
} while(0);
#define SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_41() do {\
 \
  (void) SuspendAllInterrupts(); \
} while(0);

#define SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_41() do {\
 \
  (void) ResumeAllInterrupts(); \
} while(0);
#define SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_42() do {\
 \
  (void) SuspendAllInterrupts(); \
} while(0);

#define SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_42() do {\
 \
  (void) ResumeAllInterrupts(); \
} while(0);
#define SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_43() do {\
 \
  (void) SuspendAllInterrupts(); \
} while(0);

#define SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_43() do {\
 \
  (void) ResumeAllInterrupts(); \
} while(0);
#define SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_44() do {\
 \
  (void) SuspendAllInterrupts(); \
} while(0);

#define SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_44() do {\
 \
  (void) ResumeAllInterrupts(); \
} while(0);
#define SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_45() do {\
 \
  (void) SuspendAllInterrupts(); \
} while(0);

#define SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_45() do {\
 \
  (void) ResumeAllInterrupts(); \
} while(0);
#define SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_46() do {\
 \
  (void) SuspendAllInterrupts(); \
} while(0);

#define SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_46() do {\
 \
  (void) ResumeAllInterrupts(); \
} while(0);
#define SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_47() do {\
 \
  (void) SuspendAllInterrupts(); \
} while(0);

#define SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_47() do {\
 \
  (void) ResumeAllInterrupts(); \
} while(0);
#define SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_48() do {\
 \
  (void) SuspendAllInterrupts(); \
} while(0);

#define SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_48() do {\
 \
  (void) ResumeAllInterrupts(); \
} while(0);
#define SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_49() do {\
 \
  (void) SuspendAllInterrupts(); \
} while(0);

#define SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_49() do {\
 \
  (void) ResumeAllInterrupts(); \
} while(0);
#define SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_50() do {\
 \
  (void) SuspendAllInterrupts(); \
} while(0);

#define SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_50() do {\
 \
  (void) ResumeAllInterrupts(); \
} while(0);
#define SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_51() do {\
 \
  (void) SuspendAllInterrupts(); \
} while(0);

#define SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_51() do {\
 \
  (void) ResumeAllInterrupts(); \
} while(0);
#define SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_54() do {\
 \
  (void) SuspendAllInterrupts(); \
} while(0);

#define SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_54() do {\
 \
  (void) ResumeAllInterrupts(); \
} while(0);
#define SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_55() do {\
 \
  (void) SuspendAllInterrupts(); \
} while(0);

#define SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_55() do {\
 \
  (void) ResumeAllInterrupts(); \
} while(0);
#define SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_56() do {\
 \
  (void) SuspendAllInterrupts(); \
} while(0);

#define SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_56() do {\
 \
  (void) ResumeAllInterrupts(); \
} while(0);
#define SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_57() do {\
 \
  (void) SuspendAllInterrupts(); \
} while(0);

#define SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_57() do {\
 \
  (void) ResumeAllInterrupts(); \
} while(0);
#define SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_58() do {\
 \
  (void) SuspendAllInterrupts(); \
} while(0);

#define SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_58() do {\
 \
  (void) ResumeAllInterrupts(); \
} while(0);
#define SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_59() do {\
 \
  (void) SuspendAllInterrupts(); \
} while(0);

#define SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_59() do {\
 \
  (void) ResumeAllInterrupts(); \
} while(0);
#define SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_60() do {\
 \
  (void) SuspendAllInterrupts(); \
} while(0);

#define SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_60() do {\
 \
  (void) ResumeAllInterrupts(); \
} while(0);
#define SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_61() do {\
 \
  (void) SuspendAllInterrupts(); \
} while(0);

#define SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_61() do {\
 \
  (void) ResumeAllInterrupts(); \
} while(0);
#define SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_62() do {\
 \
  (void) SuspendAllInterrupts(); \
} while(0);

#define SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_62() do {\
 \
  (void) ResumeAllInterrupts(); \
} while(0);
#define SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_63() do {\
 \
  (void) SuspendAllInterrupts(); \
} while(0);

#define SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_63() do {\
 \
  (void) ResumeAllInterrupts(); \
} while(0);
#define SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_64() do {\
 \
  (void) SuspendAllInterrupts(); \
} while(0);

#define SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_64() do {\
 \
  (void) ResumeAllInterrupts(); \
} while(0);
#define SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_65() do {\
 \
  (void) SuspendAllInterrupts(); \
} while(0);

#define SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_65() do {\
 \
  (void) ResumeAllInterrupts(); \
} while(0);
#define SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_66() do {\
 \
  (void) SuspendAllInterrupts(); \
} while(0);

#define SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_66() do {\
 \
  (void) ResumeAllInterrupts(); \
} while(0);
#define SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_67() do {\
 \
  (void) SuspendAllInterrupts(); \
} while(0);

#define SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_67() do {\
 \
  (void) ResumeAllInterrupts(); \
} while(0);
#define SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_68() do {\
 \
  (void) SuspendAllInterrupts(); \
} while(0);

#define SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_68() do {\
 \
  (void) ResumeAllInterrupts(); \
} while(0);
#define SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_69() do {\
 \
  (void) SuspendAllInterrupts(); \
} while(0);

#define SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_69() do {\
 \
  (void) ResumeAllInterrupts(); \
} while(0);
#define SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_70() do {\
 \
  (void) SuspendAllInterrupts(); \
} while(0);

#define SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_70() do {\
 \
  (void) ResumeAllInterrupts(); \
} while(0);
#define SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_71() do {\
 \
  (void) SuspendAllInterrupts(); \
} while(0);

#define SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_71() do {\
 \
  (void) ResumeAllInterrupts(); \
} while(0);
#define SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_72() do {\
 \
  (void) SuspendAllInterrupts(); \
} while(0);

#define SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_72() do {\
 \
  (void) ResumeAllInterrupts(); \
} while(0);
#define SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_73() do {\
 \
  (void) SuspendAllInterrupts(); \
} while(0);

#define SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_73() do {\
 \
  (void) ResumeAllInterrupts(); \
} while(0);
#define SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_74() do {\
 \
  (void) SuspendAllInterrupts(); \
} while(0);

#define SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_74() do {\
 \
  (void) ResumeAllInterrupts(); \
} while(0);
#define SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_75() do {\
 \
  (void) SuspendAllInterrupts(); \
} while(0);

#define SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_75() do {\
 \
  (void) ResumeAllInterrupts(); \
} while(0);
#define SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_76() do {\
 \
  (void) SuspendAllInterrupts(); \
} while(0);

#define SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_76() do {\
 \
  (void) ResumeAllInterrupts(); \
} while(0);
#define SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_77() do {\
 \
  (void) SuspendAllInterrupts(); \
} while(0);

#define SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_77() do {\
 \
  (void) ResumeAllInterrupts(); \
} while(0);
#define SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_78() do {\
 \
  (void) SuspendAllInterrupts(); \
} while(0);

#define SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_78() do {\
 \
  (void) ResumeAllInterrupts(); \
} while(0);
#define SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_79() do {\
 \
  (void) SuspendAllInterrupts(); \
} while(0);

#define SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_79() do {\
 \
  (void) ResumeAllInterrupts(); \
} while(0);
#define SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_80() do {\
 \
  (void) SuspendAllInterrupts(); \
} while(0);

#define SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_80() do {\
 \
  (void) ResumeAllInterrupts(); \
} while(0);
#define SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_81() do {\
 \
  (void) SuspendAllInterrupts(); \
} while(0);

#define SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_81() do {\
 \
  (void) ResumeAllInterrupts(); \
} while(0);
#define SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_82() do {\
 \
  (void) SuspendAllInterrupts(); \
} while(0);

#define SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_82() do {\
 \
  (void) ResumeAllInterrupts(); \
} while(0);
#define SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_83() do {\
 \
  (void) SuspendAllInterrupts(); \
} while(0);

#define SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_83() do {\
 \
  (void) ResumeAllInterrupts(); \
} while(0);
#define SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_84() do {\
 \
  (void) SuspendAllInterrupts(); \
} while(0);

#define SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_84() do {\
 \
  (void) ResumeAllInterrupts(); \
} while(0);
#define SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_85() do {\
 \
  (void) SuspendAllInterrupts(); \
} while(0);

#define SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_85() do {\
 \
  (void) ResumeAllInterrupts(); \
} while(0);
#define SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_86() do {\
 \
  (void) SuspendAllInterrupts(); \
} while(0);

#define SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_86() do {\
 \
  (void) ResumeAllInterrupts(); \
} while(0);
#define SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_87() do {\
 \
  (void) SuspendAllInterrupts(); \
} while(0);

#define SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_87() do {\
 \
  (void) ResumeAllInterrupts(); \
} while(0);
#define SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_88() do {\
 \
  (void) SuspendAllInterrupts(); \
} while(0);

#define SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_88() do {\
 \
  (void) ResumeAllInterrupts(); \
} while(0);
#define SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_89() do {\
 \
  (void) SuspendAllInterrupts(); \
} while(0);

#define SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_89() do {\
 \
  (void) ResumeAllInterrupts(); \
} while(0);
#define SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_90() do {\
 \
  (void) SuspendAllInterrupts(); \
} while(0);

#define SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_90() do {\
 \
  (void) ResumeAllInterrupts(); \
} while(0);
#define SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_91() do {\
 \
  (void) SuspendAllInterrupts(); \
} while(0);

#define SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_91() do {\
 \
  (void) ResumeAllInterrupts(); \
} while(0);
#define SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_92() do {\
 \
  (void) SuspendAllInterrupts(); \
} while(0);

#define SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_92() do {\
 \
  (void) ResumeAllInterrupts(); \
} while(0);
#define SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_95() do {\
 \
  (void) SuspendAllInterrupts(); \
} while(0);

#define SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_95() do {\
 \
  (void) ResumeAllInterrupts(); \
} while(0);
#define SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_96() do {\
 \
  (void) SuspendAllInterrupts(); \
} while(0);

#define SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_96() do {\
 \
  (void) ResumeAllInterrupts(); \
} while(0);
#define SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_97() do {\
 \
  (void) SuspendAllInterrupts(); \
} while(0);

#define SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_97() do {\
 \
  (void) ResumeAllInterrupts(); \
} while(0);
#define SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_98() do {\
 \
  (void) SuspendAllInterrupts(); \
} while(0);

#define SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_98() do {\
 \
  (void) ResumeAllInterrupts(); \
} while(0);
#define SchM_Enter_Adc_ADC_EXCLUSIVE_AREA_99() do {\
 \
  (void) SuspendAllInterrupts(); \
} while(0);

#define SchM_Exit_Adc_ADC_EXCLUSIVE_AREA_99() do {\
 \
  (void) ResumeAllInterrupts(); \
} while(0);

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
