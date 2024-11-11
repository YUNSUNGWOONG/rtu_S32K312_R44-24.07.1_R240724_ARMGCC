/*******************************************************************************
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  This source code is permitted to be used only in projects contracted      **
**  with Hyundai Autoever, and any other use is prohibited.                   **
**  If you use it for other purposes or change the source code,               **
**  you may take legal responsibility.                                        **
**  In this case, There is no warranty and technical support.                 **
**                                                                            **
**  SRC-MODULE: CryIf.h                                                       **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR CRYIF                                                 **
**                                                                            **
**  PURPOSE   : Declare all functions of module and define all macros, types  **
**              that provide to other modules                                 **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/
/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date               By           Description                      **
********************************************************************************
** 1.0.0.0   15-Jan-2021        JH Lim       Initial version                  **
** 1.0.1.0   20-Mar-2021        TamTV6       Add trace SUD                    **
** 1.0.3.0   12-Aug-2022        DienTC1      #595                             **
*******************************************************************************/

#ifndef CRYIF_H
#define CRYIF_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

/* For pre-compile macros */
#include "CryIf_Cfg.h"
/* @Trace: CryIf_SUD_FILE_001 */
/* @Trace: CryIf_SUD_MACRO_002 */
/* @Trace: CryIf_SUD_MACRO_004 */
/* @Trace: CryIf_SUD_MACRO_007 */
/*******************************************************************************
**                        Service IDs                                         **
*******************************************************************************/
/* @Trace: CryIf_SUD_MACRO_005 */
/* Service Id of CryIf_Init */
#define CRYIF_INIT_SID                                 ((uint8)0x00U)
/* Service Id of CryIf_GetVersionInfo */
#define CRYIF_GETVERSIONINFO_SID                       ((uint8)0x01U)
/* Service Id of CryIf_ProcessJob */
#define CRYIF_PROCESSJOB_SID                           ((uint8)0x03U)
/* Service Id of CryIf_CancelJob */
#define CRYIF_CANCELJOB_SID                            ((uint8)0x0EU)
/* Service Id of CryIf_KeyElementSet */
#define CRYIF_KEYELEMENTSET_SID                        ((uint8)0x04U)
/* Service Id of CryIf_KeySetValid */
#define CRYIF_KEYSETVALID_SID                          ((uint8)0x05U)
/* Service Id of CryIf_KeyElementGet */
#define CRYIF_KEYELEMENTGET_SID                        ((uint8)0x06U)
/* Service Id of CryIf_KeyElementCopy */
#define CRYIF_KEYELEMENTCOPY_SID                       ((uint8)0x0FU)
/* Service Id of CryIf_KeyElementCopyPartial */
#define CRYIF_KEYELEMENTCOPYPARTIAL_SID                ((uint8)0x12U)
/* Service Id of CryIf_KeyCopy */
#define CRYIF_KEYCOPY_SID                              ((uint8)0x10U)
/* Service Id of CryIf_RandomSeed */
#define CRYIF_RANDOMSEED_SID                           ((uint8)0x07U)
/* Service Id of CryIf_KeyGenerate */
#define CRYIF_KEYGENERATE_SID                          ((uint8)0x08U)
/* Service Id of CryIf_KeyDerive */
#define CRYIF_KEYDERIVE_SID                            ((uint8)0x09U)
/* Service Id of CryIf_KeyExchangeCalcPubVal */
#define CRYIF_KEYEXCHANGECALCPUBVAL_SID                ((uint8)0x0AU)
/* Service Id of CryIf_KeyExchangeCalcSecret */
#define CRYIF_KEYEXCHANGECALCSECRET_SID                ((uint8)0x0BU)
/* Service Id of CryIf_CallbackNotification */
#define CRYIF_CALLBACKNOTIFICATION_SID                 ((uint8)0x0DU)

/*******************************************************************************
**                      DET Error Codes                                       **
*******************************************************************************/
/* @Trace: CryIf_SUD_MACRO_008 */
/* API request called before initialization of CRYIF module */
#define CRYIF_E_UNINIT                                 ((uint8)0x00U)
/* Initialisation of CRYIF module failed */
#define CRYIF_E_INIT_FAILED                            ((uint8)0x01U)
/* API request called with invalid parameter (null pointer) */
#define CRYIF_E_PARAM_POINTER                          ((uint8)0x02U)
/* API request called with invalid parameter (out of range) */
#define CRYIF_E_PARAM_HANDLE                           ((uint8)0x03U)
/* API request called with invalid parameter (invalid value) */
#define CRYIF_E_PARAM_VALUE                            ((uint8)0x04U)
/* Source key element size does not match the target key elements size */
#define CRYIF_E_KEY_SIZE_MISMATCH                      ((uint8)0x05U)

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/* @Trace: CryIf_SUD_DATATYPE_023 */
/* Type define Configuration data structure of the CryIf module*/
typedef struct
{
  /* Dummy element */
  boolean Dummy;
}
CryIf_ConfigType;

#define CRYIF_START_SEC_CODE
#include "MemMap.h"
/* API declaration for initialization function */
extern FUNC(void, CRYIF_CODE) CryIf_Init(\
  P2CONST(CryIf_ConfigType, AUTOMATIC, CRYIF_APPL_CONST) configPtr);

/* If enable to support Version information */
#if (STD_ON == CRYIF_VERSION_INFO_API)
/* API declaration for version information function */
extern FUNC(void, CRYIF_CODE) CryIf_GetVersionInfo(\
  P2VAR(Std_VersionInfoType, AUTOMATIC, CRYIF_APPL_DATA) versioninfo);
#endif

/* API declaration for process job function */
extern FUNC(Std_ReturnType, CRYIF_CODE) CryIf_ProcessJob(\
  VAR(uint32, AUTOMATIC) channelId,\
  P2VAR(Crypto_JobType, AUTOMATIC, CRYIF_APPL_DATA) job);

/* API declaration for cancel job function */
extern FUNC(Std_ReturnType, CRYIF_CODE) CryIf_CancelJob(\
  VAR(uint32, AUTOMATIC) channelId,\
  P2VAR(Crypto_JobType, AUTOMATIC, CRYIF_APPL_DATA) job);

/* API declaration for set key element function */
extern FUNC(Std_ReturnType, CRYIF_CODE) CryIf_KeyElementSet(\
  VAR(uint32, AUTOMATIC) cryIfKeyId,\
  VAR(uint32, AUTOMATIC) keyElementId,\
  P2CONST(uint8, AUTOMATIC, CRYIF_APPL_CONST) keyPtr,\
  VAR(uint32, AUTOMATIC) keyLength);

/* API declaration for set key valid function */
extern FUNC(Std_ReturnType, CRYIF_CODE) CryIf_KeySetValid(\
  VAR(uint32, AUTOMATIC) cryIfKeyId);

/* API declaration for get key element function */
extern FUNC(Std_ReturnType, CRYIF_CODE) CryIf_KeyElementGet(\
  VAR(uint32, AUTOMATIC) cryIfKeyId,\
  VAR(uint32, AUTOMATIC) keyElementId,\
  P2VAR(uint8, AUTOMATIC, CRYIF_APPL_DATA) resultPtr,\
  P2VAR(uint32, AUTOMATIC, CRYIF_APPL_DATA) resultLengthPtr);

/* API declaration for copy key element function */
extern FUNC(Std_ReturnType, CRYIF_CODE) CryIf_KeyElementCopy(\
  VAR(uint32, AUTOMATIC) cryIfKeyId,\
  VAR(uint32, AUTOMATIC) keyElementId,\
  VAR(uint32, AUTOMATIC) targetCryIfKeyId,\
  VAR(uint32, AUTOMATIC) targetKeyElementId);

/* API declaration for copy partial key element function */
extern FUNC(Std_ReturnType, CRYIF_CODE) CryIf_KeyElementCopyPartial(\
  VAR(uint32, AUTOMATIC) cryIfKeyId,\
  VAR(uint32, AUTOMATIC) keyElementId,\
  VAR(uint32, AUTOMATIC) keyElementSourceOffset,\
  VAR(uint32, AUTOMATIC) keyElementTargetOffset,\
  VAR(uint32, AUTOMATIC) keyElementCopyLength,\
  VAR(uint32, AUTOMATIC) targetCryIfKeyId,\
  VAR(uint32, AUTOMATIC) targetKeyElementId);

/* API declaration for copy key function */
extern FUNC(Std_ReturnType, CRYIF_CODE) CryIf_KeyCopy(\
  VAR(uint32, AUTOMATIC) cryIfKeyId,\
  VAR(uint32, AUTOMATIC) targetCryIfKeyId);

/* API declaration for random seed of crypto driver object function */
extern FUNC(Std_ReturnType, CRYIF_CODE) CryIf_RandomSeed(\
  VAR(uint32, AUTOMATIC) cryIfKeyId,\
  P2CONST(uint8, AUTOMATIC, CRYIF_APPL_CONST) seedPtr,\
  VAR(uint32, AUTOMATIC) seedLength);

/* API declaration for generate key function */
extern FUNC(Std_ReturnType, CRYIF_CODE) CryIf_KeyGenerate(\
  VAR(uint32, AUTOMATIC) cryIfKeyId);

/* API declaration for derive key function */
extern FUNC(Std_ReturnType, CRYIF_CODE) CryIf_KeyDerive(\
  VAR(uint32, AUTOMATIC) cryIfKeyId,\
  VAR(uint32, AUTOMATIC) targetCryIfKeyId);

/* API declaration for calculate public key function */
extern FUNC(Std_ReturnType, CRYIF_CODE) CryIf_KeyExchangeCalcPubVal(\
  VAR(uint32, AUTOMATIC) cryIfKeyId,\
  P2VAR(uint8, AUTOMATIC, CRYIF_APPL_DATA) publicValuePtr,\
  P2VAR(uint32, AUTOMATIC, CRYIF_APPL_DATA) publicValueLengthPtr);

/* API declaration for calculate secret key function */
extern FUNC(Std_ReturnType, CRYIF_CODE) CryIf_KeyExchangeCalcSecret(\
  VAR(uint32, AUTOMATIC) cryIfKeyId,\
  P2CONST(uint8, AUTOMATIC, CRYIF_APPL_CONST) partnerPublicValuePtr,\
  VAR(uint32, AUTOMATIC) partnerPublicValueLength);

/* API declaration for call back notification function */
extern FUNC(void, CRYIF_CODE) CryIf_CallbackNotification(\
  P2CONST(Crypto_JobType, AUTOMATIC, CRYIF_APPL_DATA) job,\
  VAR(Csm_ResultType, AUTOMATIC) result);

#define CRYIF_STOP_SEC_CODE
#include "MemMap.h"

#endif /* CRYIF_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
