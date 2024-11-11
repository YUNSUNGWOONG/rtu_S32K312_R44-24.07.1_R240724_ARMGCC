/*******************************************************************************
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  This source code is permitted to be used only in projects contracted      **
**  with Hyundai Autoever, and any other use is prohibited.                   **
**  If you use it for other purposes or change the source code,               **
**  you may take legal responsibility.                                        **
**  In this case, There is no warranty and technical support.                 **
**                                                                            **
**  SRC-MODULE: KeyM.h                                                        **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR KEYM                                                  **
**                                                                            **
**  PURPOSE   : Header file to publish Key Manager function prototypes        **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By           Description                           **
********************************************************************************
** 1.0.0.0   15-Jan-2021   JH Lim       Initial version                       **
** 1.0.4.0   12-Aug-2022   DienTC1      #593                                  **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
#ifndef KEYM_EXTERNALS_H
#define KEYM_EXTERNALS_H
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* KeyM Configuration Header file */
#include "KeyM_Cfg.h"
/* KeyM Configuration Header file */
#include "Rte_KeyM_Type.h"
/* KeyM Type Header file */
#include "KeyM_IntType.h"
/* KeyM header file */
#include "KeyM.h"

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/*******************************************************************************
**                      File version check                                    **
*******************************************************************************/

/*******************************************************************************
**                      DET Error Codes                                       **
*******************************************************************************/

/*******************************************************************************
**                      Return Error Codes                                    **
*******************************************************************************/

/*******************************************************************************
**                      Global Data Type                                      **
*******************************************************************************/

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

/*******************************************************************************
**                      Service IDs                                           **
*******************************************************************************/

/*******************************************************************************
**                                  Macros                                    **
*******************************************************************************/

/*******************************************************************************
**                         Global Data Types                                  **
*******************************************************************************/

/*******************************************************************************
**                       Function Prototypes                                  **
*******************************************************************************/

#if (KEYM_CRYPTO_KEY_MANAGER_ENABLED == STD_ON)

#if (KEYM_CRYPTO_KEY_START_FINALIZE_FUNCTION_ENABLED == STD_ON)

#if (KEYM_CRYPTO_KEY_HANDLER_START_FINALIZE_ENABLED == STD_ON)
#define KEYM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, KEYM_CODE) KeyM_KH_Start(\
  VAR(KeyM_StartType, AUTOMATIC) StartType, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_CONST) RequestData, \
  VAR(uint16, AUTOMATIC) RequestDataLength, \
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ResponseData, \
  P2VAR(uint16, AUTOMATIC, KEYM_APPL_DATA) ResponseDataLength);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#define KEYM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, KEYM_CODE) KeyM_KH_Finalize(\
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_CONST) RequestData, \
  VAR(uint16, AUTOMATIC) RequestDataLength, \
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ResponseData, \
  P2VAR(uint16, AUTOMATIC, KEYM_APPL_DATA) ResponseDataLength);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* KEYM_CRYPTO_KEY_HANDLER_START_FINALIZE_ENABLED == STD_ON */
#endif /* KEYM_CRYPTO_KEY_START_FINALIZE_FUNCTION_ENABLED == STD_ON */

#if (KEYM_CRYPTO_KEY_PREPARE_FUNCTION_ENABLED == STD_ON)
#if (KEYM_CRYPTO_KEY_HANDLER_PREPARE_ENABLED == STD_ON)
#define KEYM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, KEYM_CODE) KeyM_KH_Prepare(\
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_CONST) RequestData, \
  VAR(uint16, AUTOMATIC) RequestDataLength, \
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ResponseDataPtr, \
  P2VAR(uint16, AUTOMATIC, KEYM_APPL_DATA) ResponseDataLength);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* KEYM_CRYPTO_KEY_HANDLER_PREPARE_ENABLED == STD_ON */
#endif /* KEYM_CRYPTO_KEY_PREPARE_FUNCTION_ENABLED == STD_ON */

#if (KEYM_CRYPTO_KEY_HANDLER_UPDATE_ENABLED == STD_ON)
#define KEYM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, KEYM_CODE) KeyM_KH_Update(\
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_CONST) KeyNamePtr, \
  VAR(uint16, AUTOMATIC) KeyNameLength, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_CONST) RequestData, \
  VAR(uint16, AUTOMATIC) RequestDataLength, \
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ResultDataPtr, \
  P2VAR(uint16, AUTOMATIC, KEYM_APPL_DATA) ResultDataLengthPtr, \
  P2VAR(KeyM_CryptoKeyIdType, AUTOMATIC, KEYM_APPL_DATA) KeymId, \
  P2VAR(KeyM_KH_UpdateOperationType, AUTOMATIC, KEYM_APPL_DATA) \
  UpdateOperation);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* KEYM_CRYPTO_KEY_HANDLER_UPDATE_ENABLED == STD_ON */

#if (KEYM_CRYPTO_KEY_VERIFY_FUNCTION_ENABLED == STD_ON)
#if (KEYM_CRYPTO_KEY_HANDLER_VERIFY_ENABLED == STD_ON)
#define KEYM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, KEYM_CODE) KeyM_KH_Verify(\
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_CONST) KeyNamePtr, \
  VAR(uint16, AUTOMATIC)  KeyNameLength, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_CONST) RequestData, \
  VAR(uint16, AUTOMATIC) RequestDataLength, \
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ResponseData, \
  P2VAR(uint16, AUTOMATIC, KEYM_APPL_DATA) ResponseDataLength);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* KEYM_CRYPTO_KEY_HANDLER_VERIFY_ENABLED == STD_ON */
#endif /* KEYM_CRYPTO_KEY_VERIFY_FUNCTION_ENABLED == STD_ON */

#endif /* KEYM_CRYPTO_KEY_MANAGER_ENABLED == STD_ON) */

#if (KEYM_CERTIFICATE_MANAGER_ENABLED == STD_ON)

#if (KEYM_SERVICE_CERTIFICATE_FUNCTION_ENABLED == STD_ON)
#if (KEYM_CRYPTO_KEY_HANDLER_SERVICE_CERTIFICATE_ENABLED == STD_ON)
#define KEYM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, KEYM_CODE) KeyM_KH_ServiceCertificate(\
  VAR(KeyM_ServiceCertificateType, AUTOMATIC) Service, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_CONST) CertName, \
  VAR(uint16, AUTOMATIC) CertNameLength, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_CONST) RequestData, \
  VAR(uint16, AUTOMATIC) RequestDataLength, \
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ResponseData, \
  P2VAR(uint16, AUTOMATIC, KEYM_APPL_DATA) ResponseDataLength);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* KEYM_CRYPTO_KEY_HANDLER_SERVICE_CERTIFICATE_ENABLED == STD_ON) */
#endif /* KEYM_SERVICE_CERTIFICATE_FUNCTION_ENABLED == STD_ON) */


#endif /* KEYM_CERTIFICATE_MANAGER_ENABLED == STD_ON */

#endif /* KEYM_EXTERNALS_H */

/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
