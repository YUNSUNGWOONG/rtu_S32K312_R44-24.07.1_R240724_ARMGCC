/*******************************************************************************
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  This source code is permitted to be used only in projects contracted      **
**  with Hyundai Autoever, and any other use is prohibited.                   **
**  If you use it for other purposes or change the source code,               **
**  you may take legal responsibility.                                        **
**  In this case, There is no warranty and technical support.                 **
**                                                                            **
**  SRC-MODULE: KeyM_Asn1.c                                                   **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR KEYM                                                  **
**                                                                            **
**  PURPOSE   : Key Manager internal API Functionality of ASN1                **
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
** 1.0.4.0   12-Aug-2022   DienTC1      #593                                  **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* KeyM ASN1 header file */
#include "KeyM_Asn1.h"
/* KeyM internal function prototype */
#include "KeyM_IntFunc.h"
/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/*******************************************************************************
**                      File version check                                    **
*******************************************************************************/

/*******************************************************************************
**                       Function Definitions                                 **
*******************************************************************************/

#if (KEYM_CERTIFICATE_MANAGER_ENABLED == STD_ON)

/*******************************************************************************
** Function Name      : KeyM_Asn1GetTag                                       **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Get the tag and length of ASN.1 element. Updates the  **
**                      pointer to immediately behind the tag and length      **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Reentrant                                             **
**                                                                            **
** Input Parameters   : ptrEndOfData, tag                                     **
**                                                                            **
** InOut Parameters   : ptrPosition, ptrLength                                **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : Std_ReturnType                                        **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                                                                            **
**                      Function(s) invoked :                                 **
**                      KeyM_Asn1GetLength                                    **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, KEYM_CODE) KeyM_Asn1GetTag(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrPosition, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_CONST) ptrEndOfData, \
  P2VAR(uint16, AUTOMATIC, KEYM_APPL_DATA) ptrLength, \
  const uint8 tag)
{
  Std_ReturnType retVal;

  *ptrLength = 0u;
  /* @Trace: KeyM_SUD_FUNC_181 */
  if (1 > (ptrEndOfData - *ptrPosition))
  {
    retVal = KEYM_E_ASN1_OUT_OF_DATA;
  }
  else if (**ptrPosition != tag)
  {
    retVal = KEYM_E_ASN1_UNEXPECTED_TAG;
  }
  else
  {
    /* @Trace: KeyM_SUD_FUNC_182 */
    (*ptrPosition)++;
    retVal = KeyM_Asn1GetLength(ptrPosition, ptrEndOfData, ptrLength);
  }

  return retVal;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name      : KeyM_Asn1WriteTag                                     **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Write a ASN.1 tag in ASN.1 format. This function works**
**                      backwards in data buffer                              **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Reentrant                                             **
**                                                                            **
** Input Parameters   : ptrStartOfData, tag                                   **
**                                                                            **
** InOut Parameters   : ptrPosition                                           **
**                                                                            **
** Output Parameters  : ptrLengthBytes                                        **
**                                                                            **
** Return parameter   : Std_ReturnType                                        **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                                                                            **
**                      Function(s) invoked :                                 **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, KEYM_CODE) KeyM_Asn1WriteTag(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrPosition, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_CONST) ptrStartOfData, \
  const uint8 tag, \
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrLengthBytes)
{
  Std_ReturnType retVal;

  retVal = E_OK;

  if (1 > (*ptrPosition - ptrStartOfData))
  {
    /* @Trace: KeyM_SUD_FUNC_183 */
    retVal = KEYM_E_ASN1_BUF_TOO_SMALL;
  }
  else
  {
    /* @Trace: KeyM_SUD_FUNC_184 */
    (*ptrPosition)--;
    **ptrPosition = tag;
    *ptrLengthBytes = 1u;
  }

  return retVal;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name      : KeyM_Asn1GetLength                                    **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Get the length of an ASN.1 element. Updates the       **
**                      pointer to immediately behind the length              **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Reentrant                                             **
**                                                                            **
** Input Parameters   : ptrEndOfData                                          **
**                                                                            **
** InOut Parameters   : ptrPosition, ptrLength                                **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : Std_ReturnType                                        **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                                                                            **
**                      Function(s) invoked :                                 **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, KEYM_CODE) KeyM_Asn1GetLength(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrPosition, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_CONST) ptrEndOfData, \
  P2VAR(uint16, AUTOMATIC, KEYM_APPL_DATA) ptrLength)
{
  Std_ReturnType retVal;

  retVal = E_OK;
  *ptrLength = KEYM_ZERO;

  /* @Trace: KeyM_SUD_FUNC_185 */
  if (1 > (ptrEndOfData - *ptrPosition))
  {
    retVal = KEYM_E_ASN1_OUT_OF_DATA;
  }
  else if (KEYM_ZERO == (**ptrPosition & KEYM_THE_8TH_BIT_MASK))
  {
    *ptrLength = **ptrPosition;
    (*ptrPosition)++;
  }
  else
  {
    switch (**ptrPosition & KEYM_THE_LAST_7_BITS_MASK)
    {
      case KEYM_ONE:
        /* @Trace: KeyM_SUD_FUNC_186 */
        if (2 > (ptrEndOfData - *ptrPosition))
        {
          retVal = KEYM_E_ASN1_OUT_OF_DATA;
        }
        else
        {
          *ptrLength = (*ptrPosition)[KEYM_ONE];
          (*ptrPosition) = &(*ptrPosition)[KEYM_TWO];
        }
        break;
      case KEYM_TWO:
        /* @Trace: KeyM_SUD_FUNC_187 */
        if (3 > (ptrEndOfData - *ptrPosition))
        {
          retVal = KEYM_E_ASN1_OUT_OF_DATA;
        }
        else
        {
          *ptrLength = ((uint16)(*ptrPosition)[KEYM_ONE] << KEYM_EIGHT) | \
            (*ptrPosition)[KEYM_TWO];
          (*ptrPosition) = &(*ptrPosition)[KEYM_THREE];
        }
        break;
      default:
        /* @Trace: KeyM_SUD_FUNC_188 */
        retVal = KEYM_E_ASN1_INVALID_LENGTH;
        break;
    }
  } /* @if ((ptrEndOfData - *ptrPosition) < KEYM_ONE) */
  /* @Trace: KeyM_SUD_FUNC_189 */
  if (E_OK == retVal)
  {
    if (*ptrLength > (uint16)((sint32)(ptrEndOfData - *ptrPosition)))
    {
      retVal = KEYM_E_ASN1_OUT_OF_DATA;;
    }
  }
  
  return retVal;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name      : KeyM_Asn1WriteLength                                  **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Write a length in ASN.1 format. This function works   **
**                      backwards in data buffer                              **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Reentrant                                             **
**                                                                            **
** Input Parameters   : ptrStartOfData, length                                **
**                                                                            **
** InOut Parameters   : ptrPosition                                           **
**                                                                            **
** Output Parameters  : ptrLengthBytes                                        **
**                                                                            **
** Return parameter   : Std_ReturnType                                        **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                                                                            **
**                      Function(s) invoked :                                 **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, KEYM_CODE) KeyM_Asn1WriteLength(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrPosition, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_CONST) ptrStartOfData, \
  const uint16 length, \
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrLengthBytes)
{
  Std_ReturnType retVal;

  retVal = E_OK;

  if (0x80u > length)
  {
    /* @Trace: KeyM_SUD_FUNC_190 */
    if (1 > (*ptrPosition - ptrStartOfData))
    {
      retVal = KEYM_E_ASN1_BUF_TOO_SMALL;
    }
    else
    {
      (*ptrPosition)--;
      **ptrPosition = (uint8)length;
      *ptrLengthBytes = 0x1u;
    }
  }
  else if (0xFFu >= length)
  {
    /* @Trace: KeyM_SUD_FUNC_191 */
    if (2 > (*ptrPosition - ptrStartOfData))
    {
      retVal = KEYM_E_ASN1_BUF_TOO_SMALL;
    }
    else
    {
      (*ptrPosition)--;
      **ptrPosition = (uint8)length;
      (*ptrPosition)--;
      **ptrPosition = 0x81;
      *ptrLengthBytes = 0x2u;
    }
  }
  else
  {
    if (3 > (*ptrPosition - ptrStartOfData))
    {
      /* @Trace: KeyM_SUD_FUNC_192 */
      retVal = KEYM_E_ASN1_BUF_TOO_SMALL;
    }
    else
    {
      /* @Trace: KeyM_SUD_FUNC_193 */
      (*ptrPosition)--;
      **ptrPosition = (uint8)(length & 0x00FFu);
      (*ptrPosition)--;
      **ptrPosition = (uint8)((length & 0xFF00u) >> 8u);
      (*ptrPosition)--;
      **ptrPosition = 0x82;
      *ptrLengthBytes = 0x3u;
    }
  }

  return retVal;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name      : KeyM_Asn1WriteBuffer                                  **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Write raw buffer data. This function works backwards  **
**                      in data buffer                                        **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Reentrant                                             **
**                                                                            **
** Input Parameters   : ptrStartOfData, ptrBuffer, length                     **
**                                                                            **
** InOut Parameters   : ptrPosition                                           **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : Std_ReturnType                                        **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                                                                            **
**                      Function(s) invoked :                                 **
**                      KeyM_PrvMemCopy                                       **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, KEYM_CODE) KeyM_Asn1WriteBuffer(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrPosition, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_CONST) ptrStartOfData, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_CONST) ptrBuffer, \
  const uint16 length)
{
  Std_ReturnType retVal;

  if (*ptrPosition < (&(ptrStartOfData[length])))
  {
    /* @Trace: KeyM_SUD_FUNC_194 */
    retVal = KEYM_E_ASN1_BUF_TOO_SMALL;
  }
  else
  {
    /* @Trace: KeyM_SUD_FUNC_195 */
    for (uint16 i = 0; i < length; i++)
    {
      (*ptrPosition)--;
    }
    
    retVal = KeyM_PrvMemCopy(ptrBuffer, *ptrPosition, length);
  }

  return retVal;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name      : KeyM_Asn1GetBoolean                                   **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Get a boolean ASN.1 tag and its value.                **
**                      Updates the pointer to immediately behind the full    **
**                      element                                               **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Reentrant                                             **
**                                                                            **
** Input Parameters   : ptrEndOfData                                          **
**                                                                            **
** InOut Parameters   : ptrPosition, ptrValue                                 **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : Std_ReturnType                                        **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                                                                            **
**                      Function(s) invoked :                                 **
**                      KeyM_Asn1GetTag                                       **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, KEYM_CODE) KeyM_Asn1GetBoolean(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrPosition, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_CONST) ptrEndOfData, \
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) ptrValue)
{
  Std_ReturnType retVal;
  uint16 length;

  length = KEYM_ZERO;

  /* @Trace: KeyM_SUD_FUNC_196 */
  retVal = KeyM_Asn1GetTag(ptrPosition, ptrEndOfData, &length, \
    KEYM_ASN1_BOOLEAN);

  if (E_OK == retVal)
  {
    if (KEYM_ONE != length)
    {
      retVal = KEYM_E_ASN1_INVALID_LENGTH;
    }
    else
    {
      /* @Trace: KeyM_SUD_FUNC_197 */
      *ptrValue = (**ptrPosition != KEYM_ZERO) ? KEYM_ONE : KEYM_ZERO;
      (*ptrPosition)++;
    }
  }

  return retVal;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name      : KeyM_Asn1GetBitstringNoneUnusedBits                   **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Get a bitstring ASN.1 tag without unused bits and its **
**                      value. Updates the pointer to the beginning of the    **
**                      bit/octet string                                      **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Reentrant                                             **
**                                                                            **
** Input Parameters   : ptrEndOfData                                          **
**                                                                            **
** InOut Parameters   : ptrPosition, ptrLength                                **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : Std_ReturnType                                        **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                                                                            **
**                      Function(s) invoked :                                 **
**                      KeyM_Asn1GetTag                                       **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, KEYM_CODE) KeyM_Asn1GetBitstringNoneUnusedBits(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrPosition, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_CONST) ptrEndOfData, \
  P2VAR(uint16, AUTOMATIC, KEYM_APPL_DATA) ptrLength)
{
  Std_ReturnType retVal;
  uint16 length;

  length = 0u;
  retVal = KeyM_Asn1GetTag(ptrPosition, ptrEndOfData, &length, \
    KEYM_ASN1_BIT_STRING);
  /* @Trace: KeyM_SUD_FUNC_198 */
  if (E_OK == retVal)
  {
    if ((KEYM_TWO > length) || (KEYM_ZERO != **ptrPosition))
    {
     retVal = KEYM_E_ASN1_INVALID_DATA;
    }
    else
    {
      /* @Trace: KeyM_SUD_FUNC_199 */
      /* Avoid the byte that is used to contain the number of
        unused bits of BIT string */
      (*ptrPosition)++;
      *ptrLength = length - 1u;
    }
  }

  return retVal;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name      : KeyM_Asn1GetAlgorithmIdent                            **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Get AlgorithmIdentifier ASN.1 sequence. Updates the   **
**                      pointer to immediately behind the full                **
**                      AlgorithmIdentifier                                   **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Reentrant                                             **
**                                                                            **
** Input Parameters   : ptrEndOfData                                          **
**                                                                            **
** InOut Parameters   : ptrPosition, ptrAlgorithm, ptrParams                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : Std_ReturnType                                        **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                                                                            **
**                      Function(s) invoked :                                 **
**                      KeyM_Asn1GetTag, KeyM_Asn1GetLength                   **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, KEYM_CODE) KeyM_Asn1GetAlgorithmIdent(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrPosition, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_CONST) ptrEndOfData, \
  P2VAR(KeyM_AsnElementType, AUTOMATIC, KEYM_APPL_DATA) ptrAlgorithm, \
  P2VAR(KeyM_AsnElementType, AUTOMATIC, KEYM_APPL_DATA) ptrParams)
{
  Std_ReturnType retVal;
  uint16 length;

  /* @Trace: KeyM_SUD_FUNC_200 */
  ptrParams->Tag = 0u;
  ptrParams->Length = 0u;
  ptrParams->PtrData = NULL_PTR;

  ptrAlgorithm->Tag = **ptrPosition;
  ptrAlgorithm->Length = 0u;
  ptrAlgorithm->PtrData = NULL_PTR;
  length = 0u;
  retVal = KeyM_Asn1GetTag(ptrPosition, ptrEndOfData, &length, KEYM_ASN1_OID);

  if (E_OK == retVal)
  {
    ptrAlgorithm->PtrData = *ptrPosition;
    ptrAlgorithm->Length = length;
    *ptrPosition = &(*ptrPosition)[length];

    if (*ptrPosition == ptrEndOfData)
    {
      /* Do nothing */
    }
    else
    {
      /* @Trace: KeyM_SUD_FUNC_201 */
      ptrParams->Tag = **ptrPosition;
      (*ptrPosition)++;
      length = **ptrPosition;
      if ((KEYM_ASN1_NULL != ptrParams->Tag) && (0u != length))
      {
        (*ptrPosition)++;
        ptrParams->PtrData = *ptrPosition;
        ptrParams->Length = length;
        *ptrPosition = &(*ptrPosition)[length];
      }
      else if ((KEYM_ASN1_NULL == ptrParams->Tag) && (0u != length))
      {
        retVal = KEYM_E_ASN1_LENGTH_MISMATCH;
      }
      else
      {
        (*ptrPosition)++;
      }
      /* @Trace: KeyM_SUD_FUNC_202 */
      if (*ptrPosition != ptrEndOfData)
      {
        retVal = KEYM_E_ASN1_LENGTH_MISMATCH;
      }
    } /* @if (*ptrPosition == ptrEndOfData) */
  } /* @if (E_OK == retVal) */

  return retVal;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name      : KeyM_Asn1GetAlgorithmIdentNull                        **
**                                                                            **
** Service ID         : None                                                  **
**                                                                            **
** Description        : Get AlgorithmIdentifier ASN.1 sequence with NULL or no**
**                      params. Updates the pointer to immediately behind     **
**                      the full AlgorithmIdentifier                          **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Reentrant                                             **
**                                                                            **
** Input Parameters   : ptrEndOfData                                          **
**                                                                            **
** InOut Parameters   : ptrPosition, ptrAlgorithm                             **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : Std_ReturnType                                        **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s) :                                  **
**                                                                            **
**                      Function(s) invoked :                                 **
**                      KeyM_Asn1GetAlgorithmIdent                            **
*******************************************************************************/
#define KEYM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, KEYM_CODE) KeyM_Asn1GetAlgorithmIdentNull(\
  P2VAR(uint8, AUTOMATIC, KEYM_APPL_DATA) *ptrPosition, \
  P2CONST(uint8, AUTOMATIC, KEYM_APPL_CONST) ptrEndOfData, \
  P2VAR(KeyM_AsnElementType, AUTOMATIC, KEYM_APPL_DATA) ptrAlgorithm)
{
  Std_ReturnType retVal;
  KeyM_AsnElementType params;

  /* @Trace: KeyM_SUD_FUNC_203 */
  params.Length = 0u;
  params.PtrData = NULL_PTR;
  params.Tag = 0u;

  retVal = KeyM_Asn1GetAlgorithmIdent(ptrPosition, ptrEndOfData, ptrAlgorithm,\
    &params);
  if (E_OK == retVal)
  {
    if ((KEYM_ASN1_NULL != params.Tag) && (KEYM_ZERO != params.Tag))
    {
      /* @Trace: KeyM_SUD_FUNC_204 */
      retVal = KEYM_E_ASN1_INVALID_DATA;
    }
  }

  return retVal;
}
#define KEYM_STOP_SEC_CODE
#include "MemMap.h"

#endif /* KEYM_CERTIFICATE_MANAGER_ENABLED == STD_ON */
/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/

/*******************************************************************************
**                          End of File                                       **
*******************************************************************************/
