/*******************************************************************************
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  This source code is permitted to be used only in projects contracted      **
**  with Hyundai Autoever, and any other use is prohibited.                   **
**  If you use it for other purposes or change the source code,               **
**  you may take legal responsibility.                                        **
**  In this case, There is no warranty and technical support.                 **
**                                                                            **
**  SRC-MODULE: KeyM_Asn1.h                                                   **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR KEYM                                                  **
**                                                                            **
**  PURPOSE   : Key manager internal header file for ASN1                     **
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
** 1.0.4.0   12-Aug-2022   DienTC1       #593                                 **
*******************************************************************************/
#ifndef KEYM_ASN1_H
#define KEYM_ASN1_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* KeyM Configuration Header file */
#include "KeyM_Cfg.h"
/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
#if (KEYM_CERTIFICATE_MANAGER_ENABLED == STD_ON)
/*******************************************************************************
**                                Macro                                       **
*******************************************************************************/
/* @Trace: KeyM_SUD_MACRO_007 */
/* ASN.1 Error codes */
/* Out of data when parsing an ASN1 data structure. */
#define KEYM_E_ASN1_OUT_OF_DATA       (0x21U)
/* ASN1 tag was of an unexpected value */
#define KEYM_E_ASN1_UNEXPECTED_TAG    (0x22U)
/* Error when trying to determine the length or invalid length */
#define KEYM_E_ASN1_INVALID_LENGTH    (0x23U)
/* Actual length differs from expected length */
#define KEYM_E_ASN1_LENGTH_MISMATCH   (0x24U)
/* Data is invalid. (not used) */
#define KEYM_E_ASN1_INVALID_DATA      (0x25U)
/* Buffer too small when writing ASN.1 data structure */
#define KEYM_E_ASN1_BUF_TOO_SMALL     (0x26U)

/* The tag number for DER encoded ASN.1 types */
#define KEYM_ASN1_BOOLEAN            (0x01U)
#define KEYM_ASN1_INTEGER            (0x02U)
#define KEYM_ASN1_BIT_STRING         (0x03U)
#define KEYM_ASN1_OCTET_STRING       (0x04U)
#define KEYM_ASN1_NULL               (0x05U)
#define KEYM_ASN1_OID                (0x06U)
#define KEYM_ASN1_UTF8_STRING        (0x0CU)
#define KEYM_ASN1_SEQUENCE           (0x10U)
#define KEYM_ASN1_SET                (0x11U)
#define KEYM_ASN1_PRINTABLE_STRING   (0x13U)
#define KEYM_ASN1_T61_STRING         (0x14U)
#define KEYM_ASN1_IA5_STRING         (0x16U)
#define KEYM_ASN1_UTC_TIME           (0x17U)
#define KEYM_ASN1_GENERALIZED_TIME   (0x18U)
#define KEYM_ASN1_UNIVERSAL_STRING   (0x1CU)
#define KEYM_ASN1_BMP_STRING         (0x1EU)

/* The P/C component value */
#define KEYM_ASN1_PC_PRIMITIVE       (0x00U)
#define KEYM_ASN1_PC_CONSTRUCTED     (0x20U)

/* The class component value */
#define KEYM_ASN1_CLASS_UNIVERSAL         (0x00U)
#define KEYM_ASN1_CLASS_APPLICATION       (0x40U)
#define KEYM_ASN1_CLASS_CONTEXT_SPECIFIC  (0x80U)
#define KEYM_ASN1_CLASS_PRIVATE           (0xC0U)

/* Bit masks for the class component of ASN.1 tag */
#define KEYM_ASN1_TAG_CLASS_MASK   (0xC0U)
/* Bit masks for the P/C component of ASN.1 tag */
#define KEYM_ASN1_TAG_PC_MASK      (0x20U)
/* Bit masks for the value component of ASN.1 tag */
#define KEYM_ASN1_TAG_VALUE_MASK   (0x1FU)

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
/* Tag-length-value structure that is used for ASN1 element */
typedef struct
{
  /* Tag value of element */
  uint8 Tag;
  /* Length of element in byte */
  uint16 Length;
  /* Pointer to data of element */
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) PtrData;
} KeyM_AsnElementType;
/*******************************************************************************
**                       Function Prototypes                                  **
*******************************************************************************/

#define KEYM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, KEYM_CODE) KeyM_Asn1GetTag(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrPosition, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_CONST) ptrEndOfData, \
  P2VAR(uint16, AUTOMATIC, KEYM_APPL_DATA) ptrLength, \
  const uint8 tag);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#define KEYM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, KEYM_CODE) KeyM_Asn1WriteTag(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrPosition, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_CONST) ptrStartOfData, \
  const uint8 tag, \
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrLengthBytes);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#define KEYM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, KEYM_CODE) KeyM_Asn1GetLength(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrPosition, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_CONST) ptrEndOfData, \
  P2VAR(uint16, AUTOMATIC, KEYM_APPL_DATA) ptrLength);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#define KEYM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, KEYM_CODE) KeyM_Asn1WriteLength(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrPosition, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_CONST) ptrStartOfData, \
  const uint16 length, \
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrLengthBytes);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#define KEYM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, KEYM_CODE) KeyM_Asn1WriteBuffer(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrPosition, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_CONST) ptrStartOfData, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_CONST) ptrBuffer, \
  const uint16 length);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#define KEYM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, KEYM_CODE) KeyM_Asn1GetBoolean(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrPosition, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_CONST) ptrEndOfData, \
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrValue);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#define KEYM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, KEYM_CODE) KeyM_Asn1GetBitstringNoneUnusedBits(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrPosition, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_CONST) ptrEndOfData, \
  P2VAR(uint16, AUTOMATIC, KEYM_APPL_DATA) ptrLength);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#define KEYM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, KEYM_CODE) KeyM_Asn1GetAlgorithmIdent(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrPosition, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_CONST) ptrEndOfData, \
  P2VAR(KeyM_AsnElementType, AUTOMATIC, KEYM_APPL_DATA) ptrAlgorithm, \
  P2VAR(KeyM_AsnElementType, AUTOMATIC, KEYM_APPL_DATA) ptrParams);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#define KEYM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, KEYM_CODE) KeyM_Asn1GetAlgorithmIdentNull(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrPosition, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_CONST) ptrEndOfData, \
  P2VAR(KeyM_AsnElementType, AUTOMATIC, KEYM_APPL_DATA) ptrAlgorithm);
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#endif /* KEYM_CERTIFICATE_MANAGER_ENABLED == STD_ON */
#endif /* KEYM_ASN1_H */
/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
