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
**  File Name : Rte_NvM.h                                                     **
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
#ifndef RTE_NVM_H
#define RTE_NVM_H
#ifndef RTE_ALLOW_CROSS_HEADER_INCLUSION
#ifdef RTE_APPLICATION_HEADER_FILE
#error Multiple Application Header Files included.
#endif
#define RTE_APPLICATION_HEADER_FILE
#endif

/******************************************************************************/
/*                              Header Inclusion                              */
/******************************************************************************/
#include "Rte_User.h"
#include "Rte_NvM_Type.h"
#include "Rte_Static.h"
#include "Rte_DataHandleType.h"
#include "Rte_Hook.h"
#include "Rte_IntMacros.h"

/******************************************************************************/
/*                Compatibility between C/C++ Languages Start                 */
/******************************************************************************/
#ifdef __cplusplus
extern "C" 
{

#endif

/******************************************************************************/
/*                                Init Macros                                 */
/******************************************************************************/

/******************************************************************************/
/*                          Component Data Structure                          */
/******************************************************************************/
struct Rte_CDS_NvM
{
  uint8 Rte_Dummy;
} ;
/******************************************************************************/
/*               Type Definitions for Component Data Structure                */
/******************************************************************************/
typedef struct Rte_CDS_NvM Rte_CDS_NvM;

/******************************************************************************/
/*                           Instance Handle Type                             */
/******************************************************************************/
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_NvM_START_SEC_CONST_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"
extern CONSTP2CONST(Rte_CDS_NvM, RTE_CONST, RTE_CONST) Rte_Inst_NvM;
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_NvM_STOP_SEC_CONST_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"

/******************************************************************************/
/*                         Runnable Prototype Mapping                         */
/******************************************************************************/
#ifndef RTE_RUNNABLE_EraseBlock
#define RTE_RUNNABLE_EraseBlock NvM_EraseNvBlock
#endif

#ifndef RTE_RUNNABLE_GetDataIndex
#define RTE_RUNNABLE_GetDataIndex NvM_GetDataIndex
#endif

#ifndef RTE_RUNNABLE_GetErrorStatus
#define RTE_RUNNABLE_GetErrorStatus NvM_GetErrorStatus
#endif

#ifndef RTE_RUNNABLE_InvalidateNvBlock
#define RTE_RUNNABLE_InvalidateNvBlock NvM_InvalidateNvBlock
#endif

#ifndef RTE_RUNNABLE_MainFunction
#define RTE_RUNNABLE_MainFunction NvM_MainFunction
#endif

#ifndef RTE_RUNNABLE_ReadBlock
#define RTE_RUNNABLE_ReadBlock NvM_ReadBlock
#endif

#ifndef RTE_RUNNABLE_ReadPRAMBlock
#define RTE_RUNNABLE_ReadPRAMBlock NvM_ReadPRAMBlock
#endif

#ifndef RTE_RUNNABLE_RestoreBlockDefaults
#define RTE_RUNNABLE_RestoreBlockDefaults NvM_RestoreBlockDefaults
#endif

#ifndef RTE_RUNNABLE_RestorePRAMBlockDefaults
#define RTE_RUNNABLE_RestorePRAMBlockDefaults NvM_RestorePRAMBlockDefaults
#endif

#ifndef RTE_RUNNABLE_SetBlockProtection
#define RTE_RUNNABLE_SetBlockProtection NvM_SetBlockProtection
#endif

#ifndef RTE_RUNNABLE_SetDataIndex
#define RTE_RUNNABLE_SetDataIndex NvM_SetDataIndex
#endif

#ifndef RTE_RUNNABLE_SetRamBlockStatus
#define RTE_RUNNABLE_SetRamBlockStatus NvM_SetRamBlockStatus
#endif

#ifndef RTE_RUNNABLE_WriteBlock
#define RTE_RUNNABLE_WriteBlock NvM_WriteBlock
#endif

#ifndef RTE_RUNNABLE_WritePRAMBlock
#define RTE_RUNNABLE_WritePRAMBlock NvM_WritePRAMBlock
#endif

/******************************************************************************/
/*                             Runnable Prototype                             */
/******************************************************************************/
#define NvM_START_SEC_CODE
#include "NvM_MemMap.h"
FUNC(Std_ReturnType, NvM_CODE) NvM_EraseNvBlock(VAR(NvM_BlockIdType, AUTOMATIC) BlockId);
#define NvM_STOP_SEC_CODE
#include "NvM_MemMap.h"

#define NvM_START_SEC_CODE
#include "NvM_MemMap.h"
FUNC(Std_ReturnType, NvM_CODE) NvM_GetDataIndex(VAR(NvM_BlockIdType, AUTOMATIC) BlockId, P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) DataIndexPtr);
#define NvM_STOP_SEC_CODE
#include "NvM_MemMap.h"

#define NvM_START_SEC_CODE
#include "NvM_MemMap.h"
FUNC(Std_ReturnType, NvM_CODE) NvM_GetErrorStatus(VAR(NvM_BlockIdType, AUTOMATIC) BlockId, P2VAR(NvM_RequestResultType, AUTOMATIC, RTE_APPL_DATA) RequestResultPtr);
#define NvM_STOP_SEC_CODE
#include "NvM_MemMap.h"

#define NvM_START_SEC_CODE
#include "NvM_MemMap.h"
FUNC(Std_ReturnType, NvM_CODE) NvM_InvalidateNvBlock(VAR(NvM_BlockIdType, AUTOMATIC) BlockId);
#define NvM_STOP_SEC_CODE
#include "NvM_MemMap.h"

#define NvM_START_SEC_CODE
#include "NvM_MemMap.h"
FUNC(void, NvM_CODE) NvM_MainFunction(void);
#define NvM_STOP_SEC_CODE
#include "NvM_MemMap.h"

#define NvM_START_SEC_CODE
#include "NvM_MemMap.h"
FUNC(Std_ReturnType, NvM_CODE) NvM_ReadBlock(VAR(NvM_BlockIdType, AUTOMATIC) BlockId, VAR(VoidPtr, AUTOMATIC) DstPtr);
#define NvM_STOP_SEC_CODE
#include "NvM_MemMap.h"

#define NvM_START_SEC_CODE
#include "NvM_MemMap.h"
FUNC(Std_ReturnType, NvM_CODE) NvM_ReadPRAMBlock(VAR(NvM_BlockIdType, AUTOMATIC) BlockId);
#define NvM_STOP_SEC_CODE
#include "NvM_MemMap.h"

#define NvM_START_SEC_CODE
#include "NvM_MemMap.h"
FUNC(Std_ReturnType, NvM_CODE) NvM_RestoreBlockDefaults(VAR(NvM_BlockIdType, AUTOMATIC) BlockId, VAR(VoidPtr, AUTOMATIC) DstPtr);
#define NvM_STOP_SEC_CODE
#include "NvM_MemMap.h"

#define NvM_START_SEC_CODE
#include "NvM_MemMap.h"
FUNC(Std_ReturnType, NvM_CODE) NvM_RestorePRAMBlockDefaults(VAR(NvM_BlockIdType, AUTOMATIC) BlockId);
#define NvM_STOP_SEC_CODE
#include "NvM_MemMap.h"

#define NvM_START_SEC_CODE
#include "NvM_MemMap.h"
FUNC(Std_ReturnType, NvM_CODE) NvM_SetBlockProtection(VAR(NvM_BlockIdType, AUTOMATIC) BlockId, VAR(boolean, AUTOMATIC) ProtectionEnabled);
#define NvM_STOP_SEC_CODE
#include "NvM_MemMap.h"

#define NvM_START_SEC_CODE
#include "NvM_MemMap.h"
FUNC(Std_ReturnType, NvM_CODE) NvM_SetDataIndex(VAR(NvM_BlockIdType, AUTOMATIC) BlockId, VAR(uint8, AUTOMATIC) DataIndex);
#define NvM_STOP_SEC_CODE
#include "NvM_MemMap.h"

#define NvM_START_SEC_CODE
#include "NvM_MemMap.h"
FUNC(Std_ReturnType, NvM_CODE) NvM_SetRamBlockStatus(VAR(NvM_BlockIdType, AUTOMATIC) BlockId, VAR(boolean, AUTOMATIC) BlockChanged);
#define NvM_STOP_SEC_CODE
#include "NvM_MemMap.h"

#define NvM_START_SEC_CODE
#include "NvM_MemMap.h"
FUNC(Std_ReturnType, NvM_CODE) NvM_WriteBlock(VAR(NvM_BlockIdType, AUTOMATIC) BlockId, VAR(ConstVoidPtr, AUTOMATIC) SrcPtr);
#define NvM_STOP_SEC_CODE
#include "NvM_MemMap.h"

#define NvM_START_SEC_CODE
#include "NvM_MemMap.h"
FUNC(Std_ReturnType, NvM_CODE) NvM_WritePRAMBlock(VAR(NvM_BlockIdType, AUTOMATIC) BlockId);
#define NvM_STOP_SEC_CODE
#include "NvM_MemMap.h"

/******************************************************************************/
/*                              RTE API Mapping                               */
/******************************************************************************/

/******************************************************************************/
/*                             RTE API Prototypes                             */
/******************************************************************************/

/******************************************************************************/
/*                             Application Errors                             */
/******************************************************************************/
#define RTE_E_NvMAdmin_E_NOT_OK 1U

#define RTE_E_NvMService_E_OK 0U

#define RTE_E_NvMService_E_NOT_OK 1U

#define RTE_E_NvMAdmin_E_OK 0U

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

