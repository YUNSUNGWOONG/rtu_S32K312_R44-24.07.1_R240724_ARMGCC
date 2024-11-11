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
**  File Name : Rte_Csm.h                                                     **
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
#ifndef RTE_CSM_H
#define RTE_CSM_H
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
#include "Rte_Csm_Type.h"
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
struct Rte_CDS_Csm
{
  uint8 Rte_Dummy;
} ;
/******************************************************************************/
/*               Type Definitions for Component Data Structure                */
/******************************************************************************/
typedef struct Rte_CDS_Csm Rte_CDS_Csm;

/******************************************************************************/
/*                           Instance Handle Type                             */
/******************************************************************************/
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Csm_START_SEC_CONST_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"
extern CONSTP2CONST(Rte_CDS_Csm, RTE_CONST, RTE_CONST) Rte_Inst_Csm;
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_Csm_STOP_SEC_CONST_ASIL_D_UNSPECIFIED
#include "Rte_MemMap.h"

/******************************************************************************/
/*                         Runnable Prototype Mapping                         */
/******************************************************************************/
#ifndef RTE_RUNNABLE_Decrypt
#define RTE_RUNNABLE_Decrypt Csm_Decrypt
#endif

#ifndef RTE_RUNNABLE_Encrypt
#define RTE_RUNNABLE_Encrypt Csm_Encrypt
#endif

#ifndef RTE_RUNNABLE_Hash
#define RTE_RUNNABLE_Hash Csm_Hash
#endif

#ifndef RTE_RUNNABLE_KeyCopy
#define RTE_RUNNABLE_KeyCopy Csm_KeyCopy
#endif

#ifndef RTE_RUNNABLE_KeyDerive
#define RTE_RUNNABLE_KeyDerive Csm_KeyDerive
#endif

#ifndef RTE_RUNNABLE_KeyElementCopy
#define RTE_RUNNABLE_KeyElementCopy Csm_KeyElementCopy
#endif

#ifndef RTE_RUNNABLE_KeyElementCopyPartial
#define RTE_RUNNABLE_KeyElementCopyPartial Csm_KeyElementCopyPartial
#endif

#ifndef RTE_RUNNABLE_KeyElementGet
#define RTE_RUNNABLE_KeyElementGet Csm_KeyElementGet
#endif

#ifndef RTE_RUNNABLE_KeyElementSet
#define RTE_RUNNABLE_KeyElementSet Csm_KeyElementSet
#endif

#ifndef RTE_RUNNABLE_KeyExchangeCalcPubVal
#define RTE_RUNNABLE_KeyExchangeCalcPubVal Csm_KeyExchangeCalcPubVal
#endif

#ifndef RTE_RUNNABLE_KeyExchangeCalcSecret
#define RTE_RUNNABLE_KeyExchangeCalcSecret Csm_KeyExchangeCalcSecret
#endif

#ifndef RTE_RUNNABLE_KeyGenerate
#define RTE_RUNNABLE_KeyGenerate Csm_KeyGenerate
#endif

#ifndef RTE_RUNNABLE_KeySetValid
#define RTE_RUNNABLE_KeySetValid Csm_KeySetValid
#endif

#ifndef RTE_RUNNABLE_MacGenerate
#define RTE_RUNNABLE_MacGenerate Csm_MacGenerate
#endif

#ifndef RTE_RUNNABLE_MacVerify
#define RTE_RUNNABLE_MacVerify Csm_MacVerify
#endif

#ifndef RTE_RUNNABLE_MainFunction
#define RTE_RUNNABLE_MainFunction Csm_MainFunction
#endif

#ifndef RTE_RUNNABLE_RandomGenerate
#define RTE_RUNNABLE_RandomGenerate Csm_RandomGenerate
#endif

#ifndef RTE_RUNNABLE_RandomSeed
#define RTE_RUNNABLE_RandomSeed Csm_RandomSeed
#endif

/******************************************************************************/
/*                             Runnable Prototype                             */
/******************************************************************************/
#define Csm_START_SEC_CODE
#include "Csm_MemMap.h"
FUNC(Std_ReturnType, Csm_CODE) Csm_Decrypt(VAR(uint32, AUTOMATIC) jobId, VAR(Crypto_OperationModeType, AUTOMATIC) mode, VAR(Csm_ConstDataPtr, AUTOMATIC) dataPtr, VAR(uint32, AUTOMATIC) dataLength, P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) resultPtr, P2VAR(uint32, AUTOMATIC, RTE_APPL_DATA) resultLengthPtr);
#define Csm_STOP_SEC_CODE
#include "Csm_MemMap.h"

#define Csm_START_SEC_CODE
#include "Csm_MemMap.h"
FUNC(Std_ReturnType, Csm_CODE) Csm_Encrypt(VAR(uint32, AUTOMATIC) jobId, VAR(Crypto_OperationModeType, AUTOMATIC) mode, VAR(Csm_ConstDataPtr, AUTOMATIC) dataPtr, VAR(uint32, AUTOMATIC) dataLength, P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) resultPtr, P2VAR(uint32, AUTOMATIC, RTE_APPL_DATA) resultLengthPtr);
#define Csm_STOP_SEC_CODE
#include "Csm_MemMap.h"

#define Csm_START_SEC_CODE
#include "Csm_MemMap.h"
FUNC(Std_ReturnType, Csm_CODE) Csm_Hash(VAR(uint32, AUTOMATIC) jobId, VAR(Crypto_OperationModeType, AUTOMATIC) mode, VAR(Csm_ConstDataPtr, AUTOMATIC) dataPtr, VAR(uint32, AUTOMATIC) dataLength, P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) resultPtr, P2VAR(uint32, AUTOMATIC, RTE_APPL_DATA) resultLengthPtr);
#define Csm_STOP_SEC_CODE
#include "Csm_MemMap.h"

#define Csm_START_SEC_CODE
#include "Csm_MemMap.h"
FUNC(Std_ReturnType, Csm_CODE) Csm_KeyCopy(VAR(uint32, AUTOMATIC) keyId, VAR(uint32, AUTOMATIC) targetKeyId);
#define Csm_STOP_SEC_CODE
#include "Csm_MemMap.h"

#define Csm_START_SEC_CODE
#include "Csm_MemMap.h"
FUNC(Std_ReturnType, Csm_CODE) Csm_KeyDerive(VAR(uint32, AUTOMATIC) keyId, VAR(uint32, AUTOMATIC) targetKeyId);
#define Csm_STOP_SEC_CODE
#include "Csm_MemMap.h"

#define Csm_START_SEC_CODE
#include "Csm_MemMap.h"
FUNC(Std_ReturnType, Csm_CODE) Csm_KeyElementCopy(VAR(uint32, AUTOMATIC) keyId, VAR(uint32, AUTOMATIC) keyElementId, VAR(uint32, AUTOMATIC) targetKeyId, VAR(uint32, AUTOMATIC) targetKeyElementId);
#define Csm_STOP_SEC_CODE
#include "Csm_MemMap.h"

#define Csm_START_SEC_CODE
#include "Csm_MemMap.h"
FUNC(Std_ReturnType, Csm_CODE) Csm_KeyElementCopyPartial(VAR(uint32, AUTOMATIC) keyId, VAR(uint32, AUTOMATIC) keyElementId, VAR(uint32, AUTOMATIC) keyElementSourceOffset, VAR(uint32, AUTOMATIC) keyElementTargetOffset, VAR(uint32, AUTOMATIC) keyElementCopyLength, VAR(uint32, AUTOMATIC) targetKeyId, VAR(uint32, AUTOMATIC) targetKeyElementId);
#define Csm_STOP_SEC_CODE
#include "Csm_MemMap.h"

#define Csm_START_SEC_CODE
#include "Csm_MemMap.h"
FUNC(Std_ReturnType, Csm_CODE) Csm_KeyElementGet(VAR(uint32, AUTOMATIC) keyId, VAR(uint32, AUTOMATIC) keyElementId, P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) keyPtr, P2VAR(uint32, AUTOMATIC, RTE_APPL_DATA) keyLengthPtr);
#define Csm_STOP_SEC_CODE
#include "Csm_MemMap.h"

#define Csm_START_SEC_CODE
#include "Csm_MemMap.h"
FUNC(Std_ReturnType, Csm_CODE) Csm_KeyElementSet(VAR(uint32, AUTOMATIC) keyId, VAR(uint32, AUTOMATIC) keyElementId, VAR(Csm_ConstDataPtr, AUTOMATIC) keyPtr, VAR(uint32, AUTOMATIC) keyLength);
#define Csm_STOP_SEC_CODE
#include "Csm_MemMap.h"

#define Csm_START_SEC_CODE
#include "Csm_MemMap.h"
FUNC(Std_ReturnType, Csm_CODE) Csm_KeyExchangeCalcPubVal(VAR(uint32, AUTOMATIC) keyId, P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) publicValuePtr, P2VAR(uint32, AUTOMATIC, RTE_APPL_DATA) publicValueLengthPtr);
#define Csm_STOP_SEC_CODE
#include "Csm_MemMap.h"

#define Csm_START_SEC_CODE
#include "Csm_MemMap.h"
FUNC(Std_ReturnType, Csm_CODE) Csm_KeyExchangeCalcSecret(VAR(uint32, AUTOMATIC) keyId, VAR(Csm_ConstDataPtr, AUTOMATIC) partnerPublicValuePtr, VAR(uint32, AUTOMATIC) partnerPublicValueLength);
#define Csm_STOP_SEC_CODE
#include "Csm_MemMap.h"

#define Csm_START_SEC_CODE
#include "Csm_MemMap.h"
FUNC(Std_ReturnType, Csm_CODE) Csm_KeyGenerate(VAR(uint32, AUTOMATIC) keyId);
#define Csm_STOP_SEC_CODE
#include "Csm_MemMap.h"

#define Csm_START_SEC_CODE
#include "Csm_MemMap.h"
FUNC(Std_ReturnType, Csm_CODE) Csm_KeySetValid(VAR(uint32, AUTOMATIC) keyId);
#define Csm_STOP_SEC_CODE
#include "Csm_MemMap.h"

#define Csm_START_SEC_CODE
#include "Csm_MemMap.h"
FUNC(Std_ReturnType, Csm_CODE) Csm_MacGenerate(VAR(uint32, AUTOMATIC) jobId, VAR(Crypto_OperationModeType, AUTOMATIC) mode, VAR(Csm_ConstDataPtr, AUTOMATIC) dataPtr, VAR(uint32, AUTOMATIC) dataLength, P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) macPtr, P2VAR(uint32, AUTOMATIC, RTE_APPL_DATA) macLengthPtr);
#define Csm_STOP_SEC_CODE
#include "Csm_MemMap.h"

#define Csm_START_SEC_CODE
#include "Csm_MemMap.h"
FUNC(Std_ReturnType, Csm_CODE) Csm_MacVerify(VAR(uint32, AUTOMATIC) jobId, VAR(Crypto_OperationModeType, AUTOMATIC) mode, VAR(Csm_ConstDataPtr, AUTOMATIC) dataPtr, VAR(uint32, AUTOMATIC) dataLength, VAR(Csm_ConstDataPtr, AUTOMATIC) macPtr, VAR(uint32, AUTOMATIC) macLength, P2VAR(Crypto_VerifyResultType, AUTOMATIC, RTE_APPL_DATA) verifyPtr);
#define Csm_STOP_SEC_CODE
#include "Csm_MemMap.h"

#define Csm_START_SEC_CODE
#include "Csm_MemMap.h"
FUNC(void, Csm_CODE) Csm_MainFunction(void);
#define Csm_STOP_SEC_CODE
#include "Csm_MemMap.h"

#define Csm_START_SEC_CODE
#include "Csm_MemMap.h"
FUNC(Std_ReturnType, Csm_CODE) Csm_RandomGenerate(VAR(uint32, AUTOMATIC) jobId, P2VAR(uint8, AUTOMATIC, RTE_APPL_DATA) resultPtr, P2VAR(uint32, AUTOMATIC, RTE_APPL_DATA) resultLengthPtr);
#define Csm_STOP_SEC_CODE
#include "Csm_MemMap.h"

#define Csm_START_SEC_CODE
#include "Csm_MemMap.h"
FUNC(Std_ReturnType, Csm_CODE) Csm_RandomSeed(VAR(uint32, AUTOMATIC) keyId, VAR(Csm_ConstDataPtr, AUTOMATIC) seedPtr, VAR(uint32, AUTOMATIC) seedLength);
#define Csm_STOP_SEC_CODE
#include "Csm_MemMap.h"

/******************************************************************************/
/*                              RTE API Mapping                               */
/******************************************************************************/

/******************************************************************************/
/*                             RTE API Prototypes                             */
/******************************************************************************/

/******************************************************************************/
/*                             Application Errors                             */
/******************************************************************************/
#define RTE_E_CsmSha256HmacGenerate_CsmMacGenerateConfig_E_NOT_OK 1U

#define RTE_E_CsmRandomGenerate_CsmRandomGenerateConfig_CSM_E_ENTROPY_EXHAUSTION 4U

#define RTE_E_CsmDecryptAES_ECB_DecryptAES_ECB_E_OK 0U

#define RTE_E_CsmKeyManagement_PBKDF2_Source_Key_E_NOT_OK 1U

#define RTE_E_CsmRandomGenerate_CsmRandomGenerateConfig_E_OK 0U

#define RTE_E_CsmKeyManagement_RandomSeed_L9_CSM_E_KEY_SIZE_MISMATCH 10U

#define RTE_E_CsmKeyManagement_PBKDF2_Extracted_Key_CSM_E_KEY_READ_FAIL 6U

#define RTE_E_CsmKeyManagement_PBKDF2_Extracted_Key_E_OK 0U

#define RTE_E_CsmKeyManagement_PBKDF2_Target_Key_CSM_E_BUSY 2U

#define RTE_E_CsmKeyManagement_PBKDF2_Target_Key_CSM_E_KEY_READ_FAIL 6U

#define RTE_E_CsmSha256HmacVerify_CsmMacVerifyConfig_E_OK 0U

#define RTE_E_RandomGenerate_L9_CsmRandomGenerateConfig_CSM_E_BUSY 2U

#define RTE_E_CsmDecryptAES_ECB_DecryptAES_ECB_CSM_E_KEY_NOT_VALID 9U

#define RTE_E_CsmKeyManagement_PBKDF2_Extracted_Key_CSM_E_KEY_SIZE_MISMATCH 10U

#define RTE_E_CsmKeyManagement_PBKDF2_Source_Key_CSM_E_SMALL_BUFFER 3U

#define RTE_E_CsmKeyManagement_PBKDF2_Source_Key_CSM_E_KEY_NOT_AVAILABLE 8U

#define RTE_E_CsmKeyManagement_RandomSeed_L9_CSM_E_KEY_READ_FAIL 6U

#define RTE_E_CsmSha256HmacVerify_CsmMacVerifyConfig_CSM_E_BUSY 2U

#define RTE_E_CsmSha256HmacVerify_CsmMacVerifyConfig_CSM_E_KEY_NOT_VALID 9U

#define RTE_E_CsmSha256HmacGenerate_CsmMacGenerateConfig_CSM_E_KEY_NOT_VALID 9U

#define RTE_E_CsmKeyManagement_Dummy_CSM_E_KEY_WRITE_FAIL 7U

#define RTE_E_CsmKeyManagement_Dummy_CSM_E_KEY_SIZE_MISMATCH 10U

#define RTE_E_CsmKeyManagement_PBKDF2_Source_Key_CSM_E_KEY_READ_FAIL 6U

#define RTE_E_CsmKeyManagement_RandomSeed_L9_CSM_E_KEY_NOT_AVAILABLE 8U

#define RTE_E_CsmSha256HmacGenerate_CsmMacGenerateConfig_CSM_E_SMALL_BUFFER 3U

#define RTE_E_CsmKeyManagement_RandomSeed_L9_E_OK 0U

#define RTE_E_CsmDecryptAES_ECB_DecryptAES_ECB_CSM_E_KEY_EMPTY 13U

#define RTE_E_CsmDecryptAES_ECB_DecryptAES_ECB_CSM_E_KEY_SIZE_MISMATCH 10U

#define RTE_E_CsmSha256HmacVerify_CsmMacVerifyConfig_CSM_E_KEY_SIZE_MISMATCH 10U

#define RTE_E_CsmHash_CsmHashConfig_CSM_E_BUSY 2U

#define RTE_E_CsmHash_CsmHashConfig_E_OK 0U

#define RTE_E_CsmHash_CsmHashConfig_E_NOT_OK 1U

#define RTE_E_CsmKeyManagement_RandomSeed_L9_E_NOT_OK 1U

#define RTE_E_CsmEncryptAES_ECB_EncryptAES_ECB_CSM_E_SMALL_BUFFER 3U

#define RTE_E_CsmKeyManagement_PBKDF2_Extracted_Key_CSM_E_SMALL_BUFFER 3U

#define RTE_E_CsmSha256HmacVerify_CsmMacVerifyConfig_CSM_E_SMALL_BUFFER 3U

#define RTE_E_CsmKeyManagement_RandomSeed_L9_CSM_E_BUSY 2U

#define RTE_E_CsmDecryptAES_ECB_DecryptAES_ECB_CSM_E_SMALL_BUFFER 3U

#define RTE_E_CsmHash_CsmHashConfig_CSM_E_SMALL_BUFFER 3U

#define RTE_E_CsmKeyManagement_PBKDF2_Extracted_Key_CSM_E_KEY_WRITE_FAIL 7U

#define RTE_E_CsmKeyManagement_PBKDF2_Target_Key_CSM_E_KEY_WRITE_FAIL 7U

#define RTE_E_CsmKeyManagement_PBKDF2_Target_Key_E_NOT_OK 1U

#define RTE_E_CsmKeyManagement_PBKDF2_Source_Key_CSM_E_KEY_EMPTY 13U

#define RTE_E_CsmSha256HmacVerify_CsmMacVerifyConfig_E_NOT_OK 1U

#define RTE_E_CsmKeyManagement_RandomSeed_L9_CSM_E_SMALL_BUFFER 3U

#define RTE_E_CsmDecryptAES_ECB_DecryptAES_ECB_CSM_E_BUSY 2U

#define RTE_E_CsmEncryptAES_ECB_EncryptAES_ECB_E_OK 0U

#define RTE_E_CsmSha256HmacGenerate_CsmMacGenerateConfig_CSM_E_BUSY 2U

#define RTE_E_CsmKeyManagement_PBKDF2_Extracted_Key_E_NOT_OK 1U

#define RTE_E_CsmEncryptAES_ECB_EncryptAES_ECB_CSM_E_KEY_EMPTY 13U

#define RTE_E_CsmKeyManagement_PBKDF2_Target_Key_CSM_E_KEY_SIZE_MISMATCH 10U

#define RTE_E_CsmKeyManagement_RandomSeed_L9_CSM_E_KEY_WRITE_FAIL 7U

#define RTE_E_CsmKeyManagement_PBKDF2_Source_Key_CSM_E_KEY_WRITE_FAIL 7U

#define RTE_E_CsmKeyManagement_PBKDF2_Source_Key_CSM_E_BUSY 2U

#define RTE_E_CsmKeyManagement_RandomSeed_L9_CSM_E_KEY_EMPTY 13U

#define RTE_E_CsmKeyManagement_Dummy_CSM_E_KEY_NOT_AVAILABLE 8U

#define RTE_E_CsmRandomGenerate_CsmRandomGenerateConfig_CSM_E_BUSY 2U

#define RTE_E_CsmEncryptAES_ECB_EncryptAES_ECB_CSM_E_BUSY 2U

#define RTE_E_CsmKeyManagement_Dummy_CSM_E_BUSY 2U

#define RTE_E_CsmKeyManagement_PBKDF2_Target_Key_CSM_E_SMALL_BUFFER 3U

#define RTE_E_CsmKeyManagement_PBKDF2_Source_Key_E_OK 0U

#define RTE_E_CsmKeyManagement_Dummy_CSM_E_SMALL_BUFFER 3U

#define RTE_E_CsmKeyManagement_PBKDF2_Extracted_Key_CSM_E_BUSY 2U

#define RTE_E_CsmKeyManagement_Dummy_E_OK 0U

#define RTE_E_CsmEncryptAES_ECB_EncryptAES_ECB_CSM_E_KEY_NOT_VALID 9U

#define RTE_E_CsmSha256HmacGenerate_CsmMacGenerateConfig_CSM_E_KEY_SIZE_MISMATCH 10U

#define RTE_E_CsmSha256HmacVerify_CsmMacVerifyConfig_CSM_E_KEY_EMPTY 13U

#define RTE_E_CsmKeyManagement_PBKDF2_Target_Key_CSM_E_KEY_NOT_AVAILABLE 8U

#define RTE_E_RandomGenerate_L9_CsmRandomGenerateConfig_E_NOT_OK 1U

#define RTE_E_CsmSha256HmacGenerate_CsmMacGenerateConfig_CSM_E_KEY_EMPTY 13U

#define RTE_E_CsmKeyManagement_Dummy_E_NOT_OK 1U

#define RTE_E_CsmSha256HmacGenerate_CsmMacGenerateConfig_E_OK 0U

#define RTE_E_CsmKeyManagement_Dummy_CSM_E_KEY_READ_FAIL 6U

#define RTE_E_CsmDecryptAES_ECB_DecryptAES_ECB_E_NOT_OK 1U

#define RTE_E_CsmKeyManagement_Dummy_CSM_E_KEY_EMPTY 13U

#define RTE_E_CsmKeyManagement_PBKDF2_Target_Key_E_OK 0U

#define RTE_E_CsmEncryptAES_ECB_EncryptAES_ECB_CSM_E_KEY_SIZE_MISMATCH 10U

#define RTE_E_CsmEncryptAES_ECB_EncryptAES_ECB_E_NOT_OK 1U

#define RTE_E_CsmKeyManagement_PBKDF2_Extracted_Key_CSM_E_KEY_NOT_AVAILABLE 8U

#define RTE_E_CsmRandomGenerate_CsmRandomGenerateConfig_E_NOT_OK 1U

#define RTE_E_CsmKeyManagement_PBKDF2_Source_Key_CSM_E_KEY_SIZE_MISMATCH 10U

#define RTE_E_RandomGenerate_L9_CsmRandomGenerateConfig_CSM_E_ENTROPY_EXHAUSTION 4U

#define RTE_E_CsmKeyManagement_PBKDF2_Extracted_Key_CSM_E_KEY_EMPTY 13U

#define RTE_E_RandomGenerate_L9_CsmRandomGenerateConfig_E_OK 0U

#define RTE_E_CsmKeyManagement_PBKDF2_Target_Key_CSM_E_KEY_EMPTY 13U

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
