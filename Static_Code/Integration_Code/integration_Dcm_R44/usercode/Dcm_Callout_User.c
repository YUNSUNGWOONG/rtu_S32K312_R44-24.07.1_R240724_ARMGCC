/*******************************************************************************
**                                                                            **
** (C) 2021 HYUNDAI AUTOEVER Corp.                                            **
** Confidential Proprietary Information. Distribution Limited.                **
** This source code is permitted to be used only in projects contracted       **
** with Hyundai Autoever, and any other use is prohibited.                    **
** If you use it for other purposes or change the source code,                **
** you may take legal responsibility.                                         **
** In this case, There is no warranty and technical support.                  **
**                                                                            **
**  FILE NAME : Dcm_Callout_User.c                                            **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostic Communication Manager Module               **
**                                                                            **
**  PURPOSE   : This file contains the callout functions definitions of Dcm   **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: yes                                       **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By              Description                        **
********************************************************************************
** 1.0.0   27-10-2021    K.H Kim          Initial Version                     **
** 1.1.0   04-04-2023    SY Kim           Refer #CP44-1901                    **
** 1.2.0   06-Nov-2023   SY Kim           Refer #CP44-3194                    **
** 1.3.0   31-Jan-2024   SY Kim           Refer #CP44-4033                    **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Dcm_Version.h"
#include "Dcm_Cfg.h"
#if (DCM_CNR_USED_SHA1 == STD_ON)
#include "Hmg_Pkcs1.h"
#include "Hmg_Rsa.h"
#include "Hmg_Sha160.h"
#include "Hmg_HmacSha160.h"
#endif
#if (DCM_VERSION_AR_RELEASE_MINOR_VERSION == 4)
#include "Dcm_Externals.h"
#else /*For DCM_VERSION_AR_RELEASE_MINOR_VERSION == 0*/
#include "Dcm_CallOuts.h"
#endif
#include "Dcm_PCTypes.h"
#include "Dcm_Types.h"
/* Use the FBL provided by AUTRON (Do not modify, if you use AUTRON FBL) */
#if (DCM_AUTRON_FBL_USED == STD_ON)
#include "Dcm_Callout_Fixed.h"

#include "Fbl_Stub.h"
#include "Fbl_Shared.h"
#endif

#if (DCM_CSAC_CONFIGURED == STD_ON) || (DCM_AUTHENTICATION_ES_SUPPORT == STD_ON) /* CSAC with SHA256 */
#include "Csm.h"
#endif
/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*******************************************************************************
*                       Function Definitions                                  **
*******************************************************************************/
#define DCM_START_SEC_CALLOUT_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Dcm_ReadMemory                                      **
**                                                                            **
** Description          : The Dcm_ReadMemory callout is used to request memory**
**                        data identified by the parameter memoryAddress and  **
**                        memorySize from the UDS request message.            **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : OpStatus, MemoryIdentifier,                         **
**                        MemoryAddress, MemorySize.                          **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : MemoryData, ErrorCode                               **
**                                                                            **
** Return parameter     : ReturnReadMemoryType                                **
**                        DCM_READ_OK: read was successful                    **
**                        DCM_READ_FAILED: read was not successful            **
**                        DCM_READ_PENDING: read is not yet finished          **
**                        DCM_READ_FORCE_RCRRP: reading is pending,           **
**                        the Response pending transmission starts immediately**
**                                                                            **
** Preconditions        : DCM module must be initialized                      **
**                                                                            **
*******************************************************************************/
/* polyspace+2 MISRA-C3:15.5 [Justified:Low] "As per SWS_Dcm_00539, this is AUTOSAR Standard define, can not modify." */
/* polyspace +1 MISRA-C3:8.3 [Justified:Low] "Not a defect" */
FUNC(Dcm_ReturnReadMemoryType, DCM_CALLOUT_CODE) Dcm_ReadMemory(
  Dcm_OpStatusType OpStatus,
  uint8 MemoryIdentifier,
  uint32 MemoryAddress, 
  uint32 MemorySize,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) MemoryData
  #if (DCM_VERSION_AR_RELEASE_MINOR_VERSION == 4)
  ,
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode
  #endif
  )
{
  Dcm_ReturnReadMemoryType RetVal = DCM_READ_FAILED;

  /* This is only for testing. Do not use this code as it is */

  uint32 i;

  for (i = 0u; i < MemorySize; i++)
  {
      /* polyspace-begin CERT-C:INT36-C MISRA-C3:11.4 [Justified:Low] "The integer value represents the register address."*/
      /* It should be casted to an address so that the register value can be read via the address."*/
      MemoryData[i] = ((uint8 *)MemoryAddress)[i];
	  /* polyspace-end CERT-C:INT36-C MISRA-C3:11.4 [Justified:Low] "The integer value represents the register address."*/
  }

  RetVal = DCM_READ_OK;
  #if (DCM_VERSION_AR_RELEASE_MINOR_VERSION == 4)
  *ErrorCode = DCM_POS_RESP;
  #endif

  /* The following lines of code is added to avoid compiler warning */

  DCM_UNUSED(OpStatus);
  /* MemoryIdentifier argument is not supported by Dcm */
  DCM_UNUSED(MemoryIdentifier);
  return RetVal;
}

/*******************************************************************************
** Function Name        : Dcm_WriteMemory                                     **
**                                                                            **
** Description          : The Dcm_WriteMemory callout is used to write memory **
**                        data identified by the parameter memoryAddress and  **
**                        memorySize.                                         **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : OpStatus, MemoryIdentifier,                         **
**                        MemoryAddress, MemorySize, MemoryData               **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : ErrorCode                                           **
**                                                                            **
** Return parameter     : ReturnWriteMemoryType                               **
**                        DCM_WRITE_OK: write was successful                  **
**                        DCM_WRITE_FAILED: write was not successful          **
**                        DCM_WRITE_PENDING: write is not yet finished        **
**                        DCM_WRITE_FORCE_RCRRP: writing is pending,          **
**                        the Response pending transmission starts immediately**
**                                                                            **
** Preconditions        : DCM module must be initialized                      **
**                                                                            **
*******************************************************************************/
/* polyspace +1 MISRA-C3:8.3 [Justified:Low] "Not a defect" */
FUNC(Dcm_ReturnWriteMemoryType, DCM_CALLOUT_CODE) Dcm_WriteMemory(
  Dcm_OpStatusType OpStatus,
  uint8 MemoryIdentifier,
  uint32 MemoryAddress, 
  uint32 MemorySize,
  P2CONST(uint8, AUTOMATIC, DCM_APPL_CONST) MemoryData
  #if (DCM_VERSION_AR_RELEASE_MINOR_VERSION == 4)
  ,
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) ErrorCode
  #endif
  )
{
  Dcm_ReturnWriteMemoryType RetVal = DCM_WRITE_FAILED;

  /* This is only for testing. Do not use this code as it is. */
  uint32 i;
	
  for (i = 0u; i < MemorySize; i++)
  {
    /* polyspace-begin CERT-C:INT36-C MISRA-C3:11.4 [Justified:Low] "The integer value represents the register address."*/
    /* It should be casted to an address so that the register value can be read via the address."*/
    ((uint8 *)MemoryAddress)[i] = MemoryData[i];
	/* polyspace-end CERT-C:INT36-C MISRA-C3:11.4 [Justified:Low] "The integer value represents the register address."*/
  }

  RetVal = DCM_WRITE_OK;
  #if (DCM_VERSION_AR_RELEASE_MINOR_VERSION == 4)
  *ErrorCode = DCM_POS_RESP;
  #endif

  /* Callout shall be filled by the system designer
  The following lines of code is added to avoid compiler warning */

  DCM_UNUSED(OpStatus);
  /* MemoryIdentifier argument is not supported by Dcm */
  DCM_UNUSED(MemoryIdentifier);

  return RetVal;
}

/*******************************************************************************
** Function Name        : Dcm_GetProgConditions                               **
**                                                                            **
** Description          : The Dcm_GetProgConditions callout is called upon Dcm**
**                        initialization and allows to determine if a response**
**                        ($50 or $51) has to be sent. The context parameter  **
**                        are defined in Dcm_ProgConditionsType.              **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : ProgConditions : Conditions on which the jump from  **
**                                         the bootloader has been requested  **
**                                                                            **
** Return parameter     : Dcm_EcuStartModeType                                **
**                        DCM_COLD_START : The ECU starts normally            **
**                        DCM_WARM_START : The ECU starts from a bootloader   **
**                                         jump                               **
*******************************************************************************/
/* polyspace +3 MISRA-C3:8.13 [Justified:Low] "Not a defect" */
/* polyspace +1 MISRA2012:2.7 [Justified:Low] "Not a defect" */
FUNC(Dcm_EcuStartModeType, DCM_CALLOUT_CODE) Dcm_GetProgConditions(
  P2VAR(Dcm_ProgConditionsType, AUTOMATIC, DCM_APPL_DATA) ProgConditions)
{
  Dcm_EcuStartModeType LddStartMode = DCM_COLD_START;

  /* Use the FBL provided by AUTRON (Do not modify, if you use AUTRON FBL) */
  #if(DCM_AUTRON_FBL_USED == STD_ON)
  LddStartMode = Dcm_Internal_GetProgConditions(ProgConditions);
  #endif

  return LddStartMode;
}

/*******************************************************************************
** Function Name        : Dcm_SetProgConditions                               **
**                                                                            **
** Description          : The Dcm_SetProgConditions callout allows the        **
**                        integrator to store relevant information prior to   **
**                        jumping to bootloader/jump due to ECUReset request. **
**                        The context parameter are defined                   **
**                        in Dcm_ProgConditionsType.                          **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : OpStatus: Status of the current operation           **
**                        ProgConditions : Conditions on which the jump to    **
**                                         bootloader has been requested      **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                        E_OK : Conditions have correctly been set           **
**                        E_NOT_OK : Conditions cannot be set                 **
**                        DCM_E_PENDING : Conditions set is in progress,      **
**                                       a further call to this API is needed **
**                                       to end the setting                   **
**                        DCM_E_FORCE_RCRRP : Application requests the        **
**                                           transmission of a response       **
**                                           Response Pending (NRC 0x78)      **
*******************************************************************************/
/* polyspace+1 MISRA-C3:2.7 [Justified:Low] "Not a defect" */
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) Dcm_SetProgConditions(
  #if (DCM_VERSION_AR_RELEASE_MINOR_VERSION == 4)
  Dcm_OpStatusType OpStatus,
  #endif
  P2CONST(Dcm_ProgConditionsType, AUTOMATIC,DCM_APPL_DATA) ProgConditions)
{
  Std_ReturnType LddRetVal = E_OK;

  /* Use the FBL provided by AUTRON (Do not modify, if you use AUTRON FBL) */
  #if(DCM_AUTRON_FBL_USED == STD_ON)
  LddRetVal = Dcm_Internal_SetProgConditions(ProgConditions);
  #endif

  return LddRetVal;
}

/*******************************************************************************
** Function Name        : Dcm_SignatureVerify                                 **
**                                                                            **
** Description          : Verifies the given MAC by comparing if the signature**
**                        is generated with the given data                    **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : dataPtr : Contains the pointer to the data to be    **
**                                  verified                                  **
**                        dataLength : Contains the data to be verified       **
**                                     legnth in bytes                        **
**                        signaturePtr : Holds a pointer to the signature     **
**                                       to be verified                       **
**                        signatureLength : Conatins the signature length in  **
**                                          bytes                             **
**                        publicKey : RSA public key structure                **
**                                                                            **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : verifyPtr : Holds a pointer to the memory location, **
**                                    which will hold the result of the       **
**                                    signature verification                  **
**                                                                            **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                        E_OK : signature verify successed                   **
**                        E_NOT_OK : signature verify failed                  **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                        Dcm_GddHaePkcs1V15Sha1SeedVerifyPublickey,          **
**                        Dcm_GaaHaePkcs1V15Sha1SeedVerifyModulus,            **
**                        Dcm_GaaHaePkcs1V15Sha1SeedVerifySeed                **
**                                                                            **
*******************************************************************************/
#if (DCM_CNR_USED_SHA1 == STD_ON)
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) Dcm_SignatureVerify
(
    P2CONST(uint8, AUTOMATIC, DCM_APPL_CONST) dataPtr,
    VAR(uint32, AUTOMATIC) dataLength,
    P2CONST(uint8, AUTOMATIC, DCM_APPL_CONST) signaturePtr,
    VAR(uint32, AUTOMATIC) signatureLength,
    P2CONST(Dcm_AsymPublicKeyType, AUTOMATIC, DCM_APPL_CONST) publicKey,
    P2VAR(Std_ReturnType, AUTOMATIC, DCM_APPL_CONST) verifyPtr
)
{
    Std_ReturnType LddReturnValue;
    uint8 LucIndex;
    boolean LblPrimitiveRet;
    HmgRsaPublickey LddPkcs1V15Sha1Publickey;
    uint8 LaaRsaPkcs1v15Modulus[HMG_RSA_BYTES_SIZE];
    uint8 LaaRsaPkcs1v15Seed[HMG_SHA160_DIGEST_SIZE];
    uint8 LaaTempExponent[4] = { 0x01U, 0x00U, 0x01U, 0x00U };

    /* Verify Init */
    LddReturnValue = E_OK;
    (void)memset((void*)LaaRsaPkcs1v15Modulus, 0x00, HMG_RSA_BYTES_SIZE);
    (void)memset((void*)LaaRsaPkcs1v15Seed, 0x00, HMG_SHA160_DIGEST_SIZE);
    LddPkcs1V15Sha1Publickey.modulus = LaaRsaPkcs1v15Modulus;
    LddPkcs1V15Sha1Publickey.exponent = DCM_ZERO;

    /* Verify Start */
    (void)memcpy((void*)LaaRsaPkcs1v15Modulus, \
      	(const void*)((publicKey->data) + 33U), HMG_RSA_BYTES_SIZE);

    LddPkcs1V15Sha1Publickey.exponent
    #if (defined(HIGH_BYTE_FIRST) && (CPU_BYTE_ORDER == HIGH_BYTE_FIRST))
    = ((uint32)(LaaTempExponent[0]) << 24)
    + ((uint32)(LaaTempExponent[1]) << 16)
    + ((uint32)(LaaTempExponent[2]) << 8)
    + (uint32)(LaaTempExponent[3]);
    #else
    = (uint32)(LaaTempExponent[0])
    + ((uint32)(LaaTempExponent[1]) << 8)
    + ((uint32)(LaaTempExponent[2]) << 16)
    + ((uint32)(LaaTempExponent[3]) << 24);
    #endif

    /* Verify Update - Generate digest(20byte) by padding seed(8byte) */
    if (dataLength <= HMG_SHA160_DIGEST_SIZE)
    {
      for(LucIndex = DCM_ZERO ; LucIndex < dataLength ; LucIndex++)
      {
        LaaRsaPkcs1v15Seed[LucIndex] = dataPtr[LucIndex];
      }

      LblPrimitiveRet = Hmg_RsaPkcs1v15Verify(
        signaturePtr,
        LaaRsaPkcs1v15Seed,
        HMG_SHA_160,
        &LddPkcs1V15Sha1Publickey);

      if (LblPrimitiveRet == E_OK)
      {
        *verifyPtr = E_OK;
        LddReturnValue = E_OK;
      }
      else
      {
        *verifyPtr = E_NOT_OK;
        LddReturnValue = E_NOT_OK;
      }
    }
    else
    {
      LddReturnValue = E_NOT_OK;
    }

    return LddReturnValue;
}
#endif
/*******************************************************************************
** Function Name        : Dcm_GetRandomSeed                                   **
**                                                                            **
** Description          : This function is used to update the RandomSeed used **
**                        in the C-SAC algorithm.                             **
**                                                                            **
** Precondition         : Use a SecurityLeveL L21 (CSAC)                      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : RandomSeed : RandomSeed To be applied to the C-SAC  **
**                                     platform                               **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                        E_OK: RandomSeed is valid                           **
**                              Apply user randomseed in platform             **
**                        E_NOT_OK: RandomSeed is invalid                     **
**                                                                            **
*******************************************************************************/
#if (DCM_CSAC_CONFIGURED == STD_ON) || (DCM_AUTHENTICATION_ES_SUPPORT == STD_ON)
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) Dcm_GetRandomSeed
  (P2VAR(uint8, AUTOMATIC,DCM_APPL_DATA) RandomSeed)
{
  Std_ReturnType LddRetVal = E_NOT_OK;

 /*
  * Apply user RandomSeed to the argument in this callout function.
  * RandomSeed is a 16-row array. (RandomSeed[16])
  */
  
 /*
  * If you apply RandomSeed, you must return E_OK.
  * E_OK : Use the user RandomSeed
  * E_NOT_OK : Use the Autron RandomSeed
  */
  
  #if (DCM_VERSION_AR_RELEASE_MINOR_VERSION == 4)
  LddRetVal = E_OK;
  #endif
  #ifdef INSTST_TESTCODE_INTEGRATED
  LddRetVal = E_OK;
  #endif

  return LddRetVal;
}
#endif

/*******************************************************************************
** Function Name        : Dcm_GetPublicKey                                    **
**                                                                            **
** Description          : This function is used to update the RandomSeed used **
**                        in the C-SAC algorithm.                             **
**                                                                            **
** Precondition         : Use a SecurityLeveL L21 (CSAC) &&                   **
**                        Do not use the Autron Fbl                           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : PublicKey : Public key                              **
**                                    for certificate authentication          **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
*******************************************************************************/
#if (DCM_CSAC_CONFIGURED == STD_ON) || (DCM_AUTHENTICATION_ES_SUPPORT == STD_ON)
FUNC(void, DCM_CALLOUT_CODE) Dcm_GetPublicKey
  (P2VAR(uint8, AUTOMATIC,DCM_APPL_DATA) PublicKey)
{
  /* Do not consider return value in this function */

  #if(DCM_AUTRON_FBL_USED == STD_ON)
  /*
   * Autron Fbl Public Key Used.
   * If you want to use your public key, delete this code.
   */
  T_BAIFT *ls_baift = (T_BAIFT *)&cas_FBL_BAIFT;
  uint16 LulIndex = 0U;

  /* Copy Fbl public key to the dcm */
  for(; LulIndex < 256U; LulIndex++)
  {
    PublicKey[LulIndex] = ((const uint8*)ls_baift->pcs_Pubkey)[LulIndex];
  }
  #endif /*(DCM_AUTRON_FBL_USED == STD_ON)*/
  /*
   * PublicKey Size is 256-bytes.
   * PublicKey[256] shall be initialized.
   * Refer to ES95489 and assign your public key for C-SAC.
   */

  #if(DCM_AUTRON_FBL_USED == STD_OFF)
  #if defined(CSM_SIGNATURE_AUTHSMPKCS1V15SHA256VERIFY) || defined(CSM_SIGNATURE_HAEPKCS1V15SHA256VERIFY) || defined(CSM_SIGNATURE_ESCPKCS1V15SHA256VERIFY) || (DCM_CRYPTO_R44_USED == STD_ON)
  uint16 LulIndex = 0U;
  /*If Certificate and C&R are used SHA256, PublicKey must be changed*/
  #define DCM_START_SEC_CONST_8
  #include "MemMap.h"
  CONST(uint8, DCM_CONST) Dcm_SecSerPublicKeyForSHA256[256] = 
  {
    0xDEU, 0xC4U, 0xD1U, 0xFFU, 0x08U, 0xB4U, 0x44U, 0x61U, 0xA2U, 0x56U, 0x0BU, 0xE0U, 0x5CU, 0x24U, 0x7FU, 0x74U, 
    0xC4U, 0x5CU, 0x19U, 0x1AU, 0x06U, 0xEFU, 0x86U, 0x87U, 0x66U, 0x47U, 0xC8U, 0x8AU, 0xBBU, 0xA4U, 0xB0U, 0x79U,
    0x3AU, 0x4BU, 0x36U, 0x3FU, 0x79U, 0xACU, 0x37U, 0xC6U, 0x40U, 0x0AU, 0x22U, 0x72U, 0x2CU, 0xF7U, 0xE2U, 0x47U,
    0xB0U, 0x03U, 0xC7U, 0x98U, 0x5AU, 0x49U, 0x7EU, 0x36U, 0xDDU, 0x4FU, 0x96U, 0xFBU, 0x1FU, 0xD7U, 0x27U, 0x4EU,
    0x05U, 0x8EU, 0x1EU, 0x0CU, 0x69U, 0x49U, 0x5EU, 0xDAU, 0x2FU, 0x79U, 0x8AU, 0xFBU, 0xCBU, 0x22U, 0x98U, 0x61U,
    0x27U, 0xFCU, 0xF9U, 0xD2U, 0xA6U, 0x29U, 0xA7U, 0xF6U, 0xB4U, 0xE8U, 0xCEU, 0x55U, 0xD2U, 0xEBU, 0xABU, 0x47U,
    0xBDU, 0xDEU, 0xA5U, 0xF1U, 0x46U, 0x97U, 0x5AU, 0x86U, 0xD2U, 0x1DU, 0x95U, 0x78U, 0xE5U, 0x75U, 0x70U, 0xAFU,
    0x7BU, 0xE0U, 0xA5U, 0x63U, 0x71U, 0x03U, 0xC7U, 0x69U, 0x25U, 0x4EU, 0xF8U, 0xB3U, 0xD5U, 0x45U, 0xE6U, 0xACU,
    0x0FU, 0x53U, 0x59U, 0x64U, 0xD3U, 0x82U, 0x01U, 0x02U, 0x51U, 0x17U, 0xB8U, 0x5FU, 0x16U, 0xD5U, 0x11U, 0xFDU,
    0x5FU, 0x23U, 0x08U, 0xC3U, 0x7CU, 0xE8U, 0xB0U, 0x80U, 0xFBU, 0x8EU, 0xDBU, 0xA9U, 0x26U, 0x27U, 0x23U, 0x59U,
    0x2AU, 0x71U, 0x66U, 0xECU, 0x16U, 0x62U, 0xD3U, 0x51U, 0x5DU, 0xA4U, 0xF4U, 0xA9U, 0x11U, 0x60U, 0x33U, 0x88U,
    0x4BU, 0x97U, 0x3BU, 0x60U, 0xB6U, 0xCFU, 0x7CU, 0x3EU, 0x35U, 0x36U, 0xF9U, 0x49U, 0x6EU, 0xCBU, 0x33U, 0x56U,
    0x0EU, 0x1DU, 0x3CU, 0xC9U, 0xA9U, 0xA5U, 0x6EU, 0x00U, 0xC6U, 0xA8U, 0xA1U, 0x80U, 0xC9U, 0xA4U, 0xEDU, 0x70U,
    0x66U, 0x13U, 0x93U, 0x68U, 0xF6U, 0x36U, 0xB2U, 0xD8U, 0x5AU, 0x38U, 0x3EU, 0x7BU, 0x36U, 0xF1U, 0x82U, 0x14U,
    0x10U, 0x8BU, 0xADU, 0xCBU, 0x7CU, 0x31U, 0xF3U, 0xA2U, 0xA5U, 0x1DU, 0x45U, 0xADU, 0xBFU, 0xC6U, 0xCBU, 0xA2U,
    0xF1U, 0xF7U, 0x8CU, 0x56U, 0x88U, 0xC3U, 0xB1U, 0x7CU, 0x59U, 0x78U, 0xF7U, 0xF8U, 0x5FU, 0x72U, 0x67U, 0x13U
  };
  #define DCM_STOP_SEC_CONST_8
  #include "MemMap.h"

  for( ; LulIndex < 256U; LulIndex++)
  {
    PublicKey[LulIndex] = ((const uint8*)Dcm_SecSerPublicKeyForSHA256)[LulIndex];
  }


#elif (DCM_CSAC_CONFIGURED == STD_ON)
  uint16 LulIndex = 0U;

  for( ; LulIndex < 256U; LulIndex++)
  {
    PublicKey[LulIndex] = ((const uint8*)Dcm_SecSerPublicKey)[LulIndex];
  }
#else
    //user code

#endif /* SHA256 */
#endif /*(DCM_AUTRON_FBL_USED == STD_OFF)*/
}
#endif

#if (DCM_VERSION_AR_RELEASE_MINOR_VERSION != 4)
/*******************************************************************************
** Function Name        : Dcm_GetImagePublicKey                               **
**                                                                            **
** Description          : This function is used to update the ImagePublicKey. **
**                                                                            **
** Precondition         : Use a Secure flash &&                               **
**                        Use the Autron Fbl                                  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : ImagePublicKey : Secure flash public key            **
**                                                                            **
** Return parameter     : none                                                **
*******************************************************************************/
/* polyspace+4 MISRA-C3:8.13 [Justified:Low] "This Parameter is modified when DCM_AUTRON_FBL_USED is STD_ON." */
/* polyspace+2 MISRA-C3:8.4 [Not a defect:Justify with annotations] "No Impact of this rule violation." */
/* polyspace+2 MISRA-C3:2.7 [Justified:Low] "This Parameter is used when DCM_AUTRON_FBL_USED is STD_ON." */
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) Dcm_GetImagePublicKey
  (P2VAR(uint8, AUTOMATIC,DCM_APPL_DATA) ImagePublicKey)
{
  /* polyspace+1 DEFECT:UNMODIFIED_VAR_NOT_CONST [Justified:Low] "This Parameter is modified when DCM_AUTRON_FBL_USED is STD_ON." */	
  Std_ReturnType RetVal = E_NOT_OK;
  
  #if(DCM_AUTRON_FBL_USED == STD_ON)
  /*
   * Autron Fbl ImagePublic Key Used.
   * If you want to use your Imagepublic key, delete this code.
   */
  T_BAIFT *ls_baift = (T_BAIFT *)&cas_FBL_BAIFT;
  uint16 LulIndex = 0U;

  /* Copy Fbl Imagepublic key to the dcm */
  for( ; LulIndex < 256U; LulIndex++)
  {
	  ImagePublicKey[LulIndex] = ((const uint8*)ls_baift->pcs_ImagePubkey)[LulIndex];
  }

  RetVal = E_OK;
  
  #endif
  /*
   * ImagePublicKey Size is 256-bytes.
   * ImagePublicKey[256] shall be initialized.
   * Refer to ES95489 and assign your image public key.
   */

  return RetVal;
}

/*******************************************************************************
** Function Name        : Dcm_ProcessRequestDownload                          **
**                                                                            **
** Description          : DCM shall call this callout function to start a     **
**                        download process. This service                      **
**                                                                            **
** Precondition         : None                                                **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : OpStatus                                            **
**                        DataFormatIdentifier                                **
**                        MemoryAddress                                       **
**                        MemorySize                                          **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : LpBlockLength                                       **
**                        ErrorCode                                           **
**                                                                            **
** Return parameter     : none                                                **
*******************************************************************************/
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As per Dcm754, this is Autosar Standar define, can not modify */
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) Dcm_ProcessRequestDownload
(
  Dcm_OpStatusType OpStatus, 
  uint8 DataFormatIdentifier, 
  uint32 MemoryAddress,
  uint32 MemorySize, 
  P2VAR(uint32, AUTOMATIC, DCM_PRIVATE_DATA)LpBlockLength,
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_PRIVATE_DATA) LpNegativeErrorCode
)
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As per Dcm754, this is Autosar Standar define, can not modify */
{
  /* polyspace+1 DEFECT:UNMODIFIED_VAR_NOT_CONST [Justified:Low] "This Callout Function should be filled by user. so the variable will be used by the user" */
  Std_ReturnType retVal = E_OK;
  
  /*
  * Callout shall be filled by the system designer
  * The following lines of code is added to avoid compiler warning
  */

  DCM_UNUSED(OpStatus);
  DCM_UNUSED(DataFormatIdentifier);
  DCM_UNUSED(MemoryAddress);
  DCM_UNUSED(MemorySize);
  DCM_UNUSED_PTR(LpBlockLength);
  DCM_UNUSED_PTR(LpNegativeErrorCode);
    
  return retVal;
}

/*******************************************************************************
** Function Name        : Dcm_ProcessRequestTransferExit                      **
**                                                                            **
** Description          : DCM shall call this callout function to terminate   **
**                        a download or upload process.                       **
**                                                                            **
** Precondition         : None                                                **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : OpStatus                                            **
**                        LpMemoryData                                        **
**                        ParameterRecordSize                                 **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : ErrorCode                                           **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
*******************************************************************************/
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "As per Dcm755, this is Autosar Standar define, can not modify */
FUNC(Std_ReturnType, DCM_CALLOUT_CODE) Dcm_ProcessRequestTransferExit
(
Dcm_OpStatusType OpStatus, 
P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) LpMemoryData,
uint32* LulParameterRecordSize, 
P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_PRIVATE_DATA)    
  LpNegativeErrorCode
)
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "As per Dcm755, this is Autosar Standar define, can not modify */
{
  /* polyspace+1 DEFECT:UNMODIFIED_VAR_NOT_CONST [Justified:Low] "This Callout Function should be filled by user. so the variable will be used by the user" */
  Std_ReturnType retVal = E_OK;

  /*
  * Callout shall be filled by the system designer
  * The following lines of code is added to avoid compiler warning
  */
  
  DCM_UNUSED(OpStatus);
  DCM_UNUSED_PTR(LpMemoryData);
  DCM_UNUSED_PTR(LulParameterRecordSize);
  DCM_UNUSED_PTR(LpNegativeErrorCode);

  return retVal;
}
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "This Callout Function should be filled by user. so the pointer will be used by the user" */
#endif
#if (DCM_AUTHENTICATION_SERVICE == STD_ON)
FUNC(void, DCM_CALLOUT_CODE) Dcm_Authentication_User_CallOut (
  Dcm_OpStatusType OpStatus, 
  P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext, 
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) pErrorCode)
{
  DCM_UNUSED(OpStatus);
  DCM_UNUSED_PTR(pMsgContext);
  DCM_UNUSED_PTR(pErrorCode);
}

#if (DCM_AUTHENTICATION_ES_SUPPORT == STD_ON)

/*******************************************************************************
** Function Name        : Dcm_SettingAccessRightsFailedFnc                    **
**                                                                            **
** Description          : DCM shall call this callout function to set NRC 5A  **
**                        (Setting Access Rights failed)                      **
**                                                                            **
** Precondition         : None                                                **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : OpStatus                                            **
**                        authorization                                       **
**                        Error                                               **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : retVal                                              **
**                        Error                                               **
**                                                                            **
** Return parameter     : none                                                **
*******************************************************************************/

FUNC(Std_ReturnType, DCM_CALLOUT_CODE) Dcm_SettingAccessRightsFailedFnc(
P2VAR(Dcm_CertAuthorizationInfoType, AUTOMATIC, DCM_APPL_DATA) authorization,
P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) Error)
{
  Std_ReturnType retVal = E_OK;
  /* callout function for NRC 5A */
  /* @ *Error = 0x5A; */
  return retVal;
}

/*******************************************************************************
** Function Name        : Dcm_DeauthenticationFailedFnc                       **
**                                                                            **
** Description          : DCM shall call this callout function to set NRC 5D  **
**                        (DeAuthentication failed)                           **
**                                                                            **
** Precondition         : None                                                **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : OpStatus                                            **
**                        authorization                                       **
**                        Error                                               **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : retVal                                              **
**                        Error                                               **
**                                                                            **
** Return parameter     : none                                                **
*******************************************************************************/

FUNC(Std_ReturnType, DCM_CALLOUT_CODE) Dcm_DeauthenticationFailedFnc(
Dcm_OpStatusType OpStatus,
P2VAR(Dcm_MsgContextType, AUTOMATIC, DCM_APPL_DATA) pMsgContext,
P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, DCM_APPL_DATA) Error)
{
  Std_ReturnType retVal = E_OK;
  /* callout function for NRC 5D */
  /* @*Error = 0x5D; */
  return retVal;
}

#endif /* (DCM_AUTHENTICATION_ES_SUPPORT == STD_ON) */

#endif /* (DCM_AUTHENTICATION_SERVICE == STD_ON) */
#define DCM_STOP_SEC_CALLOUT_CODE
#include "MemMap.h"

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
