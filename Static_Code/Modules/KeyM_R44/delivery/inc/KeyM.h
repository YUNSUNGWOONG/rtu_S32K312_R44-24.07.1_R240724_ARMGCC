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
** 1.0.1.0   27-Mar-2021   TamTV6       Add Trace SUD                         **
** 1.0.3.0   13-May-2022   DienTC1      #21524                                **
** 1.0.4.0   12-Aug-2022   DienTC1      #593                                  **
** 1.0.8.0   31-Jul-2023   PhuocLH9     CP44-2396, CP44-2394                  **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
#ifndef KEYM_H
#define KEYM_H
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* KeyM Configuration Header file */
#include "KeyM_Cfg.h"
/* @Trace: KeyM_SUD_DATATYPE_006 */
/* @Trace: KeyM_SUD_DATATYPE_007 */
/* KeyM Configuration Header file */
#include "Rte_KeyM_Type.h"
/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/*******************************************************************************
**                      File version check                                    **
*******************************************************************************/

/*******************************************************************************
**                      DET Error Codes                                       **
*******************************************************************************/
/* @Trace: KeyM_SUD_MACRO_011 */
/* DET error is reported if API is invoked with invalid parameter (NullPointer) */
#define KEYM_E_PARAM_POINTER                      0x01U
/* DET error is reported if Buffer is too small for operation */
#define KEYM_E_SMALL_BUFFER                       0x02U
/* DET error is reported if an API is invoked without module initialization */
#define KEYM_E_UNINIT                             0x03U
/* DET error is reported if KeyM module initialization failed */
#define KEYM_E_INIT_FAILED                        0x04U
/* DET error is reported if KeyM configuration failure */
#define KEYM_E_CONFIG_FAILURE                     0x05U

/*******************************************************************************
**                      Return Error Codes                                    **
*******************************************************************************/
/* Key management is busy with other operations */
#define KEYM_E_BUSY                               0x02U
/* Operation request accepted, response is pending. It runs now in asynchronous
  mode, response will be given through callback.*/
#define KEYM_E_PENDING                            0x03U
/* Parameter size does not match the expected value. */
#define KEYM_E_KEY_CERT_SIZE_MISMATCH             0x04U
/* Parameter to function does not provide the expected value */
#define KEYM_E_PARAMETER_MISMATCH                 0x05U
/* Key or certificate is invalid and cannot be used for the operation. */
#define KEYM_E_KEY_CERT_INVALID                   0x06U
/* Key or certificate could not be updated due to
  a write or permission failure */
#define KEYM_E_KEY_CERT_WRITE_FAIL                0x07U
/* Key or certificate update operation failed. */
#define KEYM_E_KEY_CERT_UPDATE_FAIL               0x08U
/* Key or certificate could not be provided due to
  a read or permission failure */
#define KEYM_E_KEY_CERT_READ_FAIL                 0x09U
/* The requested key or certificate is not available, slot is empty */
#define KEYM_E_KEY_CERT_EMPTY                     0x0AU
/* Certificate verification failed - Invalid Chain of Trust */
#define KEYM_E_CERT_INVALID_CHAIN_OF_TRUST        0x0BU

/*******************************************************************************
**                      Global Data Type                                      **
*******************************************************************************/

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

/*******************************************************************************
**                      Service IDs                                           **
*******************************************************************************/
/* @Trace: KeyM_SUD_MACRO_004 */
/* Service Id of KeyM_Init */
#define KEYM_INIT_SID                             0x01U
/* Service Id of KeyM_DeInit */
#define KEYM_DEINIT_SID                           0x02U
/* Service Id of KeyM_GetVersionInfo */
#define KEYM_GETVERSIONINFO_SID                   0x03U
/* Service Id of KeyM_Start */
#define KEYM_START_SID                            0x04U
/* Service Id of KeyM_Prepare */
#define KEYM_PREPARE_SID                          0x05U
/* Service Id of KeyM_Update */
#define KEYM_UPDATE_SID                           0x06U
/* Service Id of KeyM_Finalize */
#define KEYM_FINALIZE_SID                         0x07U
/* Service Id of KeyM_Verify */
#define KEYM_VERIFY_SID                           0x08U
/* Service Id of KeyM_ServiceCertificate */
#define KEYM_SERVICECERTIFICATE_SID               0x09U
/* Service Id of KeyM_SetCertificate */
#define KEYM_SETCERTIFICATE_SID                   0x0AU
/* Service Id of KeyM_GetCertificate */
#define KEYM_GETCERTIFICATE_SID                   0x0BU
/* Service Id of KeyM_VerifyCertificates */
#define KEYM_VERIFYCERTIFICATES_SID               0x0CU
/* Service Id of KeyM_VerifyCertificate */
#define KEYM_VERIFYCERTIFICATE_SID                0x0DU
/* Service Id of KeyM_VerifyCertificateChain */
#define KEYM_VERIFYCERTIFICATECHAIN_SID           0x0EU
/* Service Id of KeyM_CertElementGet */
#define KEYM_CERTELEMENTGET_SID                   0x0FU
/* Service Id of KeyM_CertElementGetFirst */
#define KEYM_CERTELEMENTGETFIRST_SID              0x10U
/* Service Id of KeyM_CertElementGetNext */
#define KEYM_CERTELEMENTGETNEXT_SID               0x11U
/* Service Id of KeyM_CertGetStatus */
#define KEYM_CERTGETSTATUS_SID                    0x12U
/* Service Id of KeyM_CertificateElementGetByIndex */
#define KEYM_CERTIFICATEELEMENTGETBYINDEX_SID     0x13U
/* Service Id of KeyM_CertificateElementGetCount */
#define KEYM_CERTIFICATEELEMENTGETCOUNT_SID       0x14U
/* Service Id of KeyM_MainFunction */
#define KEYM_MAINFUNCTION_SID                     0x19U
/* Service Id of KeyM_MainBackgroundFunction */
#define KEYM_MAINBACKGROUNDFUNCTION_SID           0x1AU

/*******************************************************************************
**                                  Macros                                    **
*******************************************************************************/
#define KEYM_UNUSED(x)                   if ((uint32)(x) != (uint32)0x0U) {}

/*******************************************************************************
**                         Global Data Types                                  **
*******************************************************************************/
/* @Trace: KeyM_SUD_DATATYPE_037 */
/* Crypto key handle. */
typedef uint16 KeyM_CryptoKeyIdType;
/* @Trace: KeyM_SUD_DATATYPE_040 */
/* This structure is the base type to initialize the Key Manager module */
typedef struct
{
  /* Dummy member, this structure shall not be used */
  void * dummy;
} KeyM_ConfigType;

#if (KEYM_CERTIFICATE_MANAGER_ENABLED == STD_ON)
/* @Trace: KeyM_SUD_DATATYPE_039 */
/* This structure is used to iterate through a number of elements of a
  certificate */
typedef struct
{
  /* Certificate ID */
  KeyM_CertificateIdType certId;
  /* Certificate Element ID */
  KeyM_CertElementIdType elementId;
  /* Element data count of the certificate element */
  uint16 elementCount;
  /* The index of current element data which has just retrieved */
  uint16 currentIndex;
  /* Get element operation result, true if the operation is OK */
  boolean resultOfGet;
} KeyM_CertElementIteratorType;

#endif /* #if (KEYM_CERTIFICATE_MANAGER_ENABLED == STD_ON) */

#if (KEYM_CRYPTO_KEY_HANDLER_UPDATE_ENABLED == STD_ON)
/* @Trace: KeyM_SUD_DATATYPE_038 */
/* Specifies the type of key handler update operation that was performed in
  the callback. */
typedef enum
{
  KEYM_KH_UPDATE_KEY_UPDATE_REPEAT = 0x01U,
  KEYM_KH_UPDATE_FINISH = 0x02U
} KeyM_KH_UpdateOperationType;
#endif /* (KEYM_CRYPTO_KEY_HANDLER_UPDATE_ENABLED == STD_ON) */
/* @Trace: SRS_KeyM_00002 */
/* These APIs are used by RTE to request KeyM services from ASW */
/*******************************************************************************
**                       Function Prototypes                                  **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, KEYM_CODE) KeyM_Init
  (P2CONST(KeyM_ConfigType, AUTOMATIC, KEYM_APPL_CONST) ConfigPtr);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#define KEYM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, KEYM_CODE) KeyM_DeInit(void);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#define KEYM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, KEYM_CODE) KeyM_GetVersionInfo(\
  P2VAR(Std_VersionInfoType, AUTOMATIC, KEYM_APPL_DATA) VersionInfo);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#if (KEYM_CRYPTO_KEY_MANAGER_ENABLED == STD_ON)

#if (KEYM_CRYPTO_KEY_START_FINALIZE_FUNCTION_ENABLED == STD_ON)
#define KEYM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, KEYM_CODE) KeyM_Start(\
  VAR(KeyM_StartType, AUTOMATIC) StartType, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_CONST) RequestData, \
  VAR(uint16, AUTOMATIC) RequestDataLength, \
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ResponseData, \
  P2VAR(uint16, AUTOMATIC, KEYM_APPL_DATA) ResponseDataLength);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#define KEYM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, KEYM_CODE) KeyM_Finalize(\
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_CONST) RequestDataPtr, \
  VAR(uint16, AUTOMATIC) RequestDataLength, \
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ResponseDataPtr, \
  VAR(uint16, AUTOMATIC) ResponseMaxDataLength);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* KEYM_CRYPTO_KEY_START_FINALIZE_FUNCTION_ENABLED == STD_ON */

#if (KEYM_CRYPTO_KEY_PREPARE_FUNCTION_ENABLED == STD_ON)
#define KEYM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, KEYM_CODE) KeyM_Prepare(\
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_CONST) RequestData, \
  VAR(uint16, AUTOMATIC) RequestDataLength, \
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ResponseData, \
  P2VAR(uint16, AUTOMATIC, KEYM_APPL_DATA) ResponseDataLength);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* KEYM_CRYPTO_KEY_PREPARE_FUNCTION_ENABLED == STD_ON */

#define KEYM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, KEYM_CODE) KeyM_Update(\
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_CONST) KeyNamePtr, \
  VAR(uint16, AUTOMATIC) KeyNameLength, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_CONST) RequestDataPtr, \
  VAR(uint16, AUTOMATIC) RequestDataLength, \
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ResultDataPtr, \
  VAR(uint16, AUTOMATIC) ResultDataMaxLength);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#if (KEYM_CRYPTO_KEY_VERIFY_FUNCTION_ENABLED == STD_ON)
#define KEYM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, KEYM_CODE) KeyM_Verify(\
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_CONST) KeyNamePtr, \
  VAR(uint16, AUTOMATIC) KeyNameLength, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_CONST) RequestData, \
  VAR(uint16, AUTOMATIC) RequestDataLength, \
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ResponseData, \
  P2VAR(uint16, AUTOMATIC, KEYM_APPL_DATA) ResponseDataLength);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* KEYM_CRYPTO_KEY_VERIFY_FUNCTION_ENABLED == STD_ON */
#endif /* KEYM_CRYPTO_KEY_MANAGER_ENABLED == STD_ON) */

#if (KEYM_CERTIFICATE_MANAGER_ENABLED == STD_ON)

#if (KEYM_SERVICE_CERTIFICATE_FUNCTION_ENABLED == STD_ON)
#define KEYM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, KEYM_CODE) KeyM_ServiceCertificate(\
  VAR(KeyM_ServiceCertificateType, AUTOMATIC) Service, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_CONST) CertNamePtr, \
  VAR(uint16, AUTOMATIC) CertNameLength, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_CONST) RequestData, \
  VAR(uint16, AUTOMATIC) RequestDataLength, \
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ResponseData, \
  VAR(uint16, AUTOMATIC) ResponseDataLength);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* KEYM_SERVICE_CERTIFICATE_FUNCTION_ENABLED == STD_ON) */

#define KEYM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, KEYM_CODE) KeyM_SetCertificate(\
  VAR(KeyM_CertificateIdType, AUTOMATIC) CertId, \
  P2CONST(KeyM_CertDataType, AUTOMATIC, KEYM_APPL_CONST) CertificateDataPtr);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#define KEYM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, KEYM_CODE) KeyM_GetCertificate(\
  VAR(KeyM_CertificateIdType, AUTOMATIC) CertId, \
  P2VAR(KeyM_CertDataType, AUTOMATIC, KEYM_APPL_DATA) CertificateDataPtr);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#define KEYM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, KEYM_CODE) KeyM_VerifyCertificates(\
  VAR(KeyM_CertificateIdType, AUTOMATIC) CertId, \
  VAR(KeyM_CertificateIdType, AUTOMATIC) CertUpperId);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#define KEYM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, KEYM_CODE) KeyM_VerifyCertificate(\
  VAR(KeyM_CertificateIdType, AUTOMATIC) CertId);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#define KEYM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, KEYM_CODE) KeyM_VerifyCertificateChain(\
  VAR(KeyM_CertificateIdType, AUTOMATIC) CertId, \
  P2CONST(KeyM_CertDataType, AUTOMATIC, KEYM_APPL_CONST) certChainData, \
  VAR(uint8, AUTOMATIC) NumberOfCertificates);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#define KEYM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, KEYM_CODE) KeyM_CertElementGet(\
  VAR(KeyM_CertificateIdType, AUTOMATIC) CertId, \
  VAR(KeyM_CertElementIdType, AUTOMATIC) CertElementId, \
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) CertElementData, \
  P2VAR(uint32, AUTOMATIC, KEYM_APPL_DATA) CertElementDataLength);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#define KEYM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, KEYM_CODE) KeyM_CertElementGetFirst(\
  VAR(KeyM_CertificateIdType, AUTOMATIC) CertId, \
  VAR(KeyM_CertElementIdType, AUTOMATIC) CertElementId, \
  P2VAR(KeyM_CertElementIteratorType, AUTOMATIC, KEYM_APPL_DATA) \
  CertElementIterator, \
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) CertElementData, \
  P2VAR(uint32, AUTOMATIC, KEYM_APPL_DATA) CertElementDataLength);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#define KEYM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, KEYM_CODE) KeyM_CertElementGetNext(\
  P2VAR(KeyM_CertElementIteratorType, AUTOMATIC, KEYM_APPL_DATA) \
  CertElementIterator, \
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) CertElementData, \
  P2VAR(uint32, AUTOMATIC, KEYM_APPL_DATA) CertElementDataLength);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#define KEYM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, KEYM_CODE) KeyM_CertGetStatus(\
  VAR(KeyM_CertificateIdType, AUTOMATIC) CertId, \
  P2VAR(KeyM_CertificateStatusType, AUTOMATIC, KEYM_APPL_DATA) Status);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#define KEYM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, KEYM_CODE) KeyM_CertificateElementGetByIndex(\
  VAR(KeyM_CertificateIdType, AUTOMATIC) CertId, \
  VAR(KeyM_CertElementIdType, AUTOMATIC) CertElementId, \
  VAR(uint32, AUTOMATIC) Index, \
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) CertElementDataPtr, \
  P2VAR(uint32, AUTOMATIC, KEYM_APPL_DATA) CertElementDataLengthPtr);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#define KEYM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, KEYM_CODE) KeyM_CertificateElementGetCount(\
  VAR(KeyM_CertificateIdType, AUTOMATIC) CertId, \
  VAR(KeyM_CertElementIdType, AUTOMATIC) CertElementId, \
  P2VAR(uint16, AUTOMATIC, KEYM_APPL_DATA) CountPtr);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#define KEYM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, KEYM_CODE) KeyM_CertElementGetOIDHex(\
  VAR(KeyM_CertificateIdType, AUTOMATIC) CertId, \
  VAR(KeyM_CertElementIdType, AUTOMATIC) CertElementId, \
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) CertElementOidData, \
  P2VAR(uint32, AUTOMATIC, KEYM_APPL_DATA) CertElementOidDataLength);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#define KEYM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, KEYM_CODE) KeyM_CertGetDERPacketData(\
  VAR(KeyM_CertificateIdType, AUTOMATIC) CertId, \
  P2VAR(uint8, AUTOMATIC, AUTOMATIC) ptrData, \
  P2VAR(uint16, AUTOMATIC, AUTOMATIC) ptrDataLength,
  CONST(uint8, AUTOMATIC)  Typestruct);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#endif /* KEYM_CERTIFICATE_MANAGER_ENABLED == STD_ON */

#endif /* KEYM_H */

/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
