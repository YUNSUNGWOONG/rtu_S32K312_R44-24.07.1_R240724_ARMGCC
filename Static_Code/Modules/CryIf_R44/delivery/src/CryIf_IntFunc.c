/*******************************************************************************
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  This source code is permitted to be used only in projects contracted      **
**  with Hyundai Autoever, and any other use is prohibited.                   **
**  If you use it for other purposes or change the source code,               **
**  you may take legal responsibility.                                        **
**  In this case, There is no warranty and technical support.                 **
**                                                                            **
**  SRC-MODULE: CryIf_IntFunc.c                                               **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR CRYIF                                                 **
**                                                                            **
**  PURPOSE   : Define all internal functions of CryIf module                 **
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
** 1.0.1.0   20-Mar-2021        TamTV6       Fixed defect #18458, #18326      ** 
**                                           Add trace SUD                    **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* For module header */
#include "CryIf_IntFunc.h"
/* For configured macro */
#include "CryIf_Globals.h"
/* For Csm type and definition */
#include "Csm.h"
/* @Trace: CryIf_SUD_DATATYPE_001 */
/* @Trace: CryIf_SUD_DATATYPE_002 */
/* @Trace: CryIf_SUD_DATATYPE_003 */
/* @Trace: CryIf_SUD_DATATYPE_004 */
/* @Trace: CryIf_SUD_DATATYPE_005 */
/* @Trace: CryIf_SUD_DATATYPE_024 */
#define CRYIF_START_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
**                      Declare static function                               **
*******************************************************************************/
static FUNC(Std_ReturnType, CRYIF_CODE) CryIf_CheckRedirectKey(\
  P2VAR(uint32, AUTOMATIC, CRYIF_APPL_DATA) ptrRedirectKey);
/*******************************************************************************
** Function Name        : CryIf_GetIndexChannel                               **
**                                                                            **
** Service ID           : N/A                                                 **
**                                                                            **
** Description          : Get index of a element in the array                 **
**                        CryIf_ChannelList based on the Channel value.       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : Channel: input channel Id                           **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return Parameters    : uint32                                              **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : CryIf_ChannelList[]           **
**                                                                            **
**                        Function(s) invoked : None                          **
**                                                                            **
*******************************************************************************/
FUNC(uint32, CRYIF_CODE) CryIf_GetIndexChannel(\
  VAR(uint32, AUTOMATIC) Channel)
{
  /* Variable holds return value */
  VAR(uint32, AUTOMATIC) retVal;
  /* Variable holds midle index */
  VAR(uint32, AUTOMATIC) midle;
  /* Variable holds head index */
  VAR(uint32, AUTOMATIC) head;
  /* Variable holds tail index */
  VAR(uint32, AUTOMATIC) tail;

  /* Failed return */
  retVal = CRYIF_TOTAL_CHANNEL_ID_NUMBER;
  /* Get index of array that value is Id with binary search */
  /* Initialize first value of head and tail */
  head = CRYIF_ONE_VALUE;
  tail = CRYIF_TOTAL_CHANNEL_ID_NUMBER;
  /* @Trace: CryIf_SUD_FUNC_091 */
  while ((head <= tail) && (CRYIF_TOTAL_CHANNEL_ID_NUMBER == retVal))
  {
    midle = (head + tail)/CRYIF_TWO_VALUE;
    /* polyspace-begin DEFECT:DEAD_CODE MISRA-C3:14.3 MISRA-C3:2.1 [Justified:Low] "The value of if condition depends on channel list configuration. In reality, it is variant, not a constant." */
    if (CryIf_ChannelList[midle - CRYIF_ONE_VALUE].ChannelId == Channel)
    {
      /* Search successfully and return value */
      retVal = midle - CRYIF_ONE_VALUE;
    }
    else if (CryIf_ChannelList[midle - CRYIF_ONE_VALUE].ChannelId < Channel)
    {
      /* Update head again */
      head = midle + CRYIF_ONE_VALUE;
    }
    else
    {
      /* Update tail again */
      tail = midle - CRYIF_ONE_VALUE;
    }
    /* polyspace-end DEFECT:DEAD_CODE MISRA-C3:14.3 MISRA-C3:2.1 */
  } /* End of while */

  return retVal;
} /* End of CryIf_GetIndexChannel */

/*******************************************************************************
** Function Name        : CryIf_GetIndexKey                                   **
**                                                                            **
** Service ID           : N/A                                                 **
**                                                                            **
** Description          : Get index of a element in the array                 **
**                        CryIf_CryIfKeyList based on the KeyId value.        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : KeyId: input CryIfKeyId                             **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return Parameters    : uint32                                              **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : CryIf_CryIfKeyList[]          **
**                                                                            **
**                        Function(s) invoked : None                          **
**                                                                            **
*******************************************************************************/
FUNC(uint32, CRYIF_CODE) CryIf_GetIndexKey(\
  VAR(uint32, AUTOMATIC) KeyId)
{
  /* Variable holds return value */
  VAR(uint32, AUTOMATIC) retVal;
  /* Variable holds midle index */
  VAR(uint32, AUTOMATIC) midle;
  /* Variable holds head index */
  VAR(uint32, AUTOMATIC) head;
  /* Variable holds tail index */
  VAR(uint32, AUTOMATIC) tail;

  /* Failed return */
  retVal = CRYIF_TOTAL_CRYIF_KEY_ID_NUMBER;
  /* Get index of array that value is Id with binary search */
  /* Initialize first value of head and tail */
  head = CRYIF_ONE_VALUE;
  tail = CRYIF_TOTAL_CRYIF_KEY_ID_NUMBER;
  /* @Trace: CryIf_SUD_FUNC_092 */
  while ((head <= tail) && (CRYIF_TOTAL_CRYIF_KEY_ID_NUMBER == retVal))
  {
    midle = (head + tail)/CRYIF_TWO_VALUE;
    if (CryIf_CryIfKeyList[midle - CRYIF_ONE_VALUE].CryIfKeyId == KeyId)
    {
      /* Search successfully and return value */
      retVal = midle - CRYIF_ONE_VALUE;
    }
    else if (CryIf_CryIfKeyList[midle - CRYIF_ONE_VALUE].CryIfKeyId < KeyId)
    {
      /* Update head again */
      head = midle + CRYIF_ONE_VALUE;
    }
    else
    {
      /* Update tail again */
      tail = midle - CRYIF_ONE_VALUE;
    }
  } /* End of while */

  return retVal;
} /* End of CryIf_GetIndexKey */

/*******************************************************************************
** Function Name        : CryIf_GetIndexKeyElement                            **
**                                                                            **
** Service ID           : N/A                                                 **
**                                                                            **
** Description          : Get index of a element in the array                 **
**                        CryIf_CryIfKeyList based on the KeyId value.        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : ElementId: input Crypto Driver Key Element ID       **
**                        IndexKey: input index of array CryIf_CryIfKeyList   **
**                        numberElement: number of Key elements of a key      **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return Parameters    : uint32                                              **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : CryIf_KeyElementList[]        **
**                                              CryIf_CryIfKeyList[]          **
**                                                                            **
**                        Function(s) invoked : None                          **
**                                                                            **
*******************************************************************************/
FUNC(uint32, CRYIF_CODE) CryIf_GetIndexKeyElement(\
  VAR(uint32, AUTOMATIC) IndexKey,\
  VAR(uint32, AUTOMATIC) ElementId,\
  VAR(uint32, AUTOMATIC) numberElement)
{
  /* Variable holds return value */
  VAR(uint32, AUTOMATIC) retVal;
  /* Variable holds midle index */
  VAR(uint32, AUTOMATIC) midle;
  /* Variable holds head index */
  VAR(uint32, AUTOMATIC) head;
  /* Variable holds tail index */
  VAR(uint32, AUTOMATIC) tail;
  /* Variable holds max index value */
  VAR(uint32, AUTOMATIC) max;
  /* Variable holds min index value */
  VAR(uint32, AUTOMATIC) min;

  /* Failed return */
  retVal = CRYIF_TOTAL_KEY_ELEMENT_NUMBER;
  /* Get index of array that value is Id with binary search */
  min = CryIf_CryIfKeyList[IndexKey].IndexStart;
  /* Initialize first value of head and tail */
  max = min + numberElement;
  min++;
  head = min;
  tail = max;
  /* @Trace: CryIf_SUD_FUNC_093 */
  while ((head <= tail) && (CRYIF_TOTAL_KEY_ELEMENT_NUMBER == retVal))
  {
    midle = (head + tail)/CRYIF_TWO_VALUE;
    if (CryIf_KeyElementList[midle - CRYIF_ONE_VALUE].ElementId == \
      ElementId)
    {
      /* Search successfully and return value */
      retVal = midle - CRYIF_ONE_VALUE;
    }
    else if (CryIf_KeyElementList[midle - CRYIF_ONE_VALUE].ElementId < \
      ElementId)
    {
      /* Update head again */
      head = midle + CRYIF_ONE_VALUE;
    }
    else
    {
      /* Update tail again */
      tail = midle - CRYIF_ONE_VALUE;
    }
  } /* End of while */

  return retVal;
} /* End of CryIf_GetIndexKeyElement */

/*******************************************************************************
** Function Name        : CryIf_DispatchKey                                   **
**                                                                            **
** Service ID           : N/A                                                 **
**                                                                            **
** Description          : Dispatch the corresponding crypto driver key to     **
**                        Crypto driver module                                **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : serJob: current service of Csm job                  **
**                        keyInfo: CryIf key in struct jobPrimitiveInfo       **
**                                                                            **
** InOut Parameters     : ptrJob: point to Csm job                            **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return Parameters    : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : CryIf_CryIfKeyList[]          **
**                                                                            **
**                        Function(s) invoked : CryIf_GetIndexKey             **
**                                              Det_ReportError               **
**                                                                            **
*******************************************************************************/
FUNC(Std_ReturnType, CRYIF_CODE) CryIf_DispatchKey(\
  P2VAR(Crypto_JobType, AUTOMATIC, CRYIF_APPL_DATA) ptrJob,\
  VAR(Crypto_ServiceInfoType, AUTOMATIC) serJob,\
  VAR(uint32, AUTOMATIC) keyInfo)
{
  /* Variable holds return value */
  VAR(Std_ReturnType, AUTOMATIC) retVal;
  /* Variable holds index of key id array for source key */
  VAR(uint32, AUTOMATIC) indexArrKey;
  /* Variable holds index of key id array for target key */
  VAR(uint32, AUTOMATIC) indexArrTargetKey;

  retVal = E_OK;
  /*
   * If service is KeySetValid, RandomSeed, KeyGenerate, KeyDerive,
   * KeyExchange.
   */
  if ((CRYPTO_KEYSETVALID == serJob) || \
    (CRYPTO_RANDOMSEED == serJob) || \
    (CRYPTO_KEYGENERATE == serJob) || \
    (CRYPTO_KEYDERIVE == serJob) || \
    (CRYPTO_KEYEXCHANGECALCPUBVAL == serJob) || \
    (CRYPTO_KEYEXCHANGECALCSECRET == serJob))
  {
    /* @Trace: CryIf_SUD_FUNC_094 */
    /* Get index of key id array from cryIfKeyId */
    indexArrKey = CryIf_GetIndexKey(ptrJob->jobPrimitiveInputOutput.cryIfKeyId);
    /* Check the parameter cryIfKeyId must be in range */
    if (CRYIF_TOTAL_CRYIF_KEY_ID_NUMBER <= indexArrKey)
    {
      retVal = E_NOT_OK;
    }
    else
    {
      /* Adapt cryIfKeyId to corresponding crypto driver key id */
      ptrJob->cryptoKeyId = CryIf_CryIfKeyList[indexArrKey].CryptoKeyId;
      /* @Trace: CryIf_SUD_FUNC_095 */
      if (CRYPTO_KEYDERIVE == serJob)
      {
        /* Get index of key id array from targetCryIfKeyId */
        indexArrTargetKey = CryIf_GetIndexKey(\
          ptrJob->jobPrimitiveInputOutput.targetCryIfKeyId);
        if (CRYIF_TOTAL_CRYIF_KEY_ID_NUMBER <= indexArrTargetKey)
        {
          retVal = E_NOT_OK;
        }
        else
        {
          /* Adapt targetCryptoKeyId to corresponding crypto driver keyid */
          ptrJob->targetCryptoKeyId = \
            CryIf_CryIfKeyList[indexArrTargetKey].CryptoKeyId;
        }
      } /* End of serJob = CRYPTO_KEYDERIVE; CRYPTO_CERTIFICATEVERIFY */
    } /* End of indexArrKey < CRYIF_TOTAL_CRYIF_KEY_ID_NUMBER */
  } /* End of serJob check */
  else if ((CRYPTO_MACGENERATE == serJob) || \
    (CRYPTO_MACVERIFY == serJob) || \
    (CRYPTO_ENCRYPT == serJob) || \
    (CRYPTO_DECRYPT == serJob) || \
    (CRYPTO_AEADENCRYPT == serJob) || \
    (CRYPTO_AEADDECRYPT == serJob) || \
    (CRYPTO_SIGNATUREGENERATE == serJob) || \
    (CRYPTO_SIGNATUREVERIFY == serJob))
  {
    /* @Trace: CryIf_SUD_FUNC_096 */
    /* Get index of key id array from cryIfKeyId */
    indexArrKey = CryIf_GetIndexKey(keyInfo);
    /* Check the parameter cryIfKeyId must be in range */
    if (CRYIF_TOTAL_CRYIF_KEY_ID_NUMBER <= indexArrKey)
    {
      retVal = E_NOT_OK;
    }
    else
    {
      /* Adapt cryptoKeyId to corresponding crypto driver key id */
      ptrJob->cryptoKeyId = CryIf_CryIfKeyList[indexArrKey].CryptoKeyId;
    }
  } /* End of else if ((CRYPTO_MACGENERATE == serJob)... */
  else if ((CRYPTO_RANDOMGENERATE == serJob) || \
    (CRYPTO_HASH == serJob))
  {
    /* @Trace: CryIf_SUD_FUNC_104 */
    /* Return E_OK for services that no need to check cryIfKeyId */
    retVal = E_OK;
  }
  else
  {
    /* @Trace: CryIf_SUD_FUNC_097 */
    /*Return E_NOT_OK for other services */
    retVal = E_NOT_OK;
  }
  return retVal;
} /* End of CryIf_GetIndexKeyElement */

/*******************************************************************************
** Function Name        : CryIf_RedirectKey                                   **
**                                                                            **
** Service ID           : N/A                                                 **
**                                                                            **
** Description          : Redirect the corresponding crypto driver key to     **
**                        Crypto driver module                                **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : ptrJob: point to Csm job                            **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return Parameters    : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : CryIf_CryIfKeyList[]          **
**                                                                            **
**                        Function(s) invoked : CryIf_CheckRedirectKey        **
**                                                                            **
*******************************************************************************/
/* polyspace-begin MISRA2012:8.13 [Justified:Low] "According to AUTOSAR specification, ptrJob is an InOut parameter, not only for reading. ptrJob->jobRedirectionInfoRef is updated in consequence invokes." */
FUNC(Std_ReturnType, CRYIF_CODE) CryIf_RedirectKey(\
  P2VAR(Crypto_JobType, AUTOMATIC, CRYIF_APPL_DATA) ptrJob)
{
  /* Variable holds return value */
  VAR(Std_ReturnType, AUTOMATIC) retVal;
  /* Pointer of redirection key */
  P2VAR(Crypto_JobRedirectionInfoType, AUTOMATIC, CRYIF_APPL_DATA) ptrRedirect;

  retVal = E_OK;
  ptrRedirect = ptrJob->jobRedirectionInfoRef;
  if (NULL_PTR != ptrRedirect)
  {
    /* @Trace: CryIf_SUD_FUNC_099 */
    /* Primary input rederection */
    if ((uint8)CRYPTO_REDIRECT_CONFIG_PRIMARY_INPUT == \
      (ptrRedirect->redirectionConfig & \
      (uint8)CRYPTO_REDIRECT_CONFIG_PRIMARY_INPUT))
    {
      retVal = CryIf_CheckRedirectKey(&ptrRedirect->inputKeyId);
    }
    /* @Trace: CryIf_SUD_FUNC_100 */
    /* Secondary input rederection */
    if ((E_OK == retVal) && \
      ((uint8)CRYPTO_REDIRECT_CONFIG_SECONDARY_INPUT == \
      (ptrRedirect->redirectionConfig & \
      (uint8)CRYPTO_REDIRECT_CONFIG_SECONDARY_INPUT)))
    {
      retVal = CryIf_CheckRedirectKey(&ptrRedirect->secondaryInputKeyId);
    }
    /* @Trace: CryIf_SUD_FUNC_101 */
    /* Tertiary input rederection */
    if ((E_OK == retVal) && \
      ((uint8)CRYPTO_REDIRECT_CONFIG_TERTIARY_INPUT == \
      (ptrRedirect->redirectionConfig & \
      (uint8)CRYPTO_REDIRECT_CONFIG_TERTIARY_INPUT)))
    {
      retVal = CryIf_CheckRedirectKey(&ptrRedirect->tertiaryInputKeyId);
    }
    /* @Trace: CryIf_SUD_FUNC_102 */
    /* Primary output rederection */
    if ((E_OK == retVal) &&\
      ((uint8)CRYPTO_REDIRECT_CONFIG_PRIMARY_OUTPUT == \
      (ptrRedirect->redirectionConfig & \
      (uint8)CRYPTO_REDIRECT_CONFIG_PRIMARY_OUTPUT)))
    {
      retVal = CryIf_CheckRedirectKey(&ptrRedirect->outputKeyId);
    }
    /* @Trace: CryIf_SUD_FUNC_103 */
    /* Secondary output rederection */
    if ((E_OK == retVal) && \
      ((uint8)CRYPTO_REDIRECT_CONFIG_SECONDARY_OUTPUT == \
      (ptrRedirect->redirectionConfig & \
      (uint8)CRYPTO_REDIRECT_CONFIG_SECONDARY_OUTPUT)))
    {
      retVal = CryIf_CheckRedirectKey(&ptrRedirect->secondaryOutputKeyId);
    }
  } /* End of if (ptrRedirect != NULL) */

  return retVal;
}
/* polyspace-end MISRA2012:8.13 */

/*******************************************************************************
** Function Name        : CryIf_CheckRedirectKey                              **
**                                                                            **
** Service ID           : N/A                                                 **
**                                                                            **
** Description          : Check and Redirect the corresponding crypto driver  **
**                        key to Crypto driver module                         **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut Parameters     : ptrRedirectKey: point to CryIf Key of Csm job       **
**                        redirection                                         **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return Parameters    : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : CryIf_CryIfKeyList[]          **
**                                                                            **
**                        Function(s) invoked : None                          **
**                                                                            **
*******************************************************************************/
static FUNC(Std_ReturnType, CRYIF_CODE) CryIf_CheckRedirectKey(\
  P2VAR(uint32, AUTOMATIC, CRYIF_APPL_DATA) ptrRedirectKey)
{
  /* Variable holds return value */
  VAR(Std_ReturnType, AUTOMATIC) retVal;
  /* Variable holds index of key id array for redirect key */
  VAR(uint32, AUTOMATIC) redirectKey;

  /* Get index of key id array*/
  redirectKey = CRYIF_TOTAL_CRYIF_KEY_ID_NUMBER;
  retVal = E_NOT_OK;
  /* @Trace: CryIf_SUD_FUNC_098 */
  while ((CRYIF_ZERO_VALUE < redirectKey) && (E_OK != retVal))
  {
    redirectKey--;
    if (CryIf_CryIfKeyList[redirectKey].CryIfKeyId == *ptrRedirectKey)
    {
      /* Adapt key to corresponding crypto driver key */
      *ptrRedirectKey = CryIf_CryIfKeyList[redirectKey].CryptoKeyId;
      retVal = E_OK;
    }
  }

  return retVal;
}

#define CRYIF_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
