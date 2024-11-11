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
**  SRC-MODULE: Dcm_PackUnPack.c                                              **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostic Communication Manager Module               **
**                                                                            **
**  PURPOSE   : Provision of unpacking of signals from request message and    **
**              packing of signals to the response message.                   **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By             Description                         **
********************************************************************************
** 0.0.1     31-Dec-2019   SonDT1         AR440 Implementation                **
** 0.0.2     16-Aug-2020   SonDT1         Changes made as per #14836          **
** 0.0.3     13-Oct-2020   HueKM          Changes made as per #15766          **
** 0.0.4     04-Dec-2020   HueKM          Polyspace fixing as per #15175      **
** 0.0.5     16-Dec-2020   HueKM          Mapping SUD API ID as per #17448    **
** 1.0.2     18-May-2022   LanhLT         Changes made as per #26479          **
** 1.0.7     16-Dec-2022   LanhLT         Fix UNECE                           **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Dcm_PCTypes.h"
#include "Dcm_PackUnpack.h"
#include "SchM_Dcm.h"

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define DCM_START_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Dcm_UnPack2Byte                                     **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Convert two byte of uint8 array to uint16 variable  **
**                        without consider endianness                         **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant for different signals.                    **
**                        Non-Reentrant for the same signal.                  **
**                                                                            **
** Input Parameters     : pRxData                                             **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : uint16                                              **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
FUNC(uint16, DCM_CODE) Dcm_UnPack2Byte(
  P2CONST(uint8, AUTOMATIC, DCM_APPL_CONST) pRxData)
{
  /* @Trace: Dcm_SUD_API_20318 */
  Dcm_MIWord_Access LddSignalData;
  LddSignalData.whole_word = DCM_ZERO;

  LddSignalData.byte_val.BO_Byte[DCM_ZERO] = pRxData[DCM_ZERO];
  LddSignalData.byte_val.BO_Byte[DCM_ONE] = pRxData[DCM_ONE];

  return LddSignalData.whole_word;
}

/*******************************************************************************
** Function Name        : Dcm_UnPack2ByteOrder                                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Convert two byte of uint8 array to uint16 variable  **
**                        with consider endianness                            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant for different signals.                    **
**                        Non-Reentrant for the same signal.                  **
**                                                                            **
** Input Parameters     : pRxData                                             **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : uint16                                              **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
FUNC(uint16, DCM_CODE) Dcm_UnPack2ByteOrder(
  P2CONST(uint8, AUTOMATIC, DCM_APPL_CONST) pRxData)
{
  /* @Trace: Dcm_SUD_API_20319 */
  Dcm_MIWord_Access LddSignalData;
  LddSignalData.whole_word = DCM_ZERO;

  LddSignalData.byte_val.BO_Byte[DCM_ZERO] = pRxData[DCM_ONE];
  LddSignalData.byte_val.BO_Byte[DCM_ONE] = pRxData[DCM_ZERO];

  return LddSignalData.whole_word;
}

/*******************************************************************************
** Function Name        : Dcm_UnPack4Byte                                     **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Convert four byte of uint8 array to uint32 variable **
**                        without consider endianness                         **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant for different signals.                    **
**                        Non-Reentrant for the same signal.                  **
**                                                                            **
** Input Parameters     : pRxData                                             **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : uint32                                              **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
FUNC(uint32, DCM_CODE) Dcm_UnPack4Byte(
  P2CONST(uint8, AUTOMATIC, DCM_APPL_CONST) pRxData)
{
  /* @Trace: Dcm_SUD_API_20320 */
  Dcm_MIdWord_Access LddSignalData;
  LddSignalData.whole_dword = DCM_ZERO;

  LddSignalData.byte_val.BO_Byte[DCM_ZERO] = pRxData[DCM_ZERO];
  LddSignalData.byte_val.BO_Byte[DCM_ONE] = pRxData[DCM_ONE];
  LddSignalData.byte_val.BO_Byte[DCM_TWO] = pRxData[DCM_TWO];
  LddSignalData.byte_val.BO_Byte[DCM_THREE] = pRxData[DCM_THREE];

  return LddSignalData.whole_dword;
}

/*******************************************************************************
** Function Name        : Dcm_UnPack4ByteOrder                                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Convert four byte of uint8 array to uint32 variable **
**                        with consider endianness                            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant for different signals.                    **
**                        Non-Reentrant for the same signal.                  **
**                                                                            **
** Input Parameters     : pRxData                                             **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : uint32                                              **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
FUNC(uint32, DCM_CODE) Dcm_UnPack4ByteOrder(
  P2CONST(uint8, AUTOMATIC, DCM_APPL_CONST) pRxData)
{
  /* @Trace: Dcm_SUD_API_20321 */
  Dcm_MIdWord_Access LddSignalData;
  LddSignalData.whole_dword = DCM_ZERO;

  LddSignalData.byte_val.BO_Byte[DCM_ZERO] = pRxData[DCM_THREE];
  LddSignalData.byte_val.BO_Byte[DCM_ONE] = pRxData[DCM_TWO];
  LddSignalData.byte_val.BO_Byte[DCM_TWO] = pRxData[DCM_ONE];
  LddSignalData.byte_val.BO_Byte[DCM_THREE] = pRxData[DCM_ZERO];

  return LddSignalData.whole_dword;
}

/*******************************************************************************
** Function Name        : Dcm_UnPack1ByteArray                                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Convert received data to uint8 array                **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant for different signals.                    **
**                        Non-Reentrant for the same signal.                  **
**                                                                            **
** Input Parameters     : pRxData, pUnPackData                                **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : pOutData                                            **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
FUNC(void, DCM_CODE) Dcm_UnPack1ByteArray(
  P2VAR(void, AUTOMATIC, DCM_APPL_DATA) pOutData,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pRxData,
  P2CONST(Dcm_PackUnPackType, AUTOMATIC, DCM_APPL_CONST) pUnPackData)
{
  uint16 LusSignalSize;
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) LpShadowRxData;
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) LpOneByteBuffer;

  LpShadowRxData = pRxData;
  LusSignalSize = pUnPackData->usSignalSize;
  /* polyspace +2 MISRA-C3:11.5 [Justified:Low] Justify with annotations */
  /* polyspace +1 CERT-C:EXP36-C [Justified:Low] "pOutData depend on configuration DcmDspDataType, pOutData will cast to specific type after in specific unpack function" */
  LpOneByteBuffer = (P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA)) pOutData;

  SchM_Enter_Dcm_SIGNAL_DATA_PROTECTION_AREA();

  while (LusSignalSize != DCM_ZERO) 
  {
    /* @Trace: Dcm_SUD_API_20322 */
    *LpOneByteBuffer = *LpShadowRxData;

    LusSignalSize--;
    LpShadowRxData = &LpShadowRxData[DCM_ONE];
    LpOneByteBuffer = &LpOneByteBuffer[DCM_ONE];
  }

  SchM_Exit_Dcm_SIGNAL_DATA_PROTECTION_AREA();
}

/*******************************************************************************
** Function Name        : Dcm_UnPack2ByteArray                                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Convert received data to uint16 array               **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant for different signals.                    **
**                        Non-Reentrant for the same signal.                  **
**                                                                            **
** Input Parameters     : pRxData, pUnPackData                                **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : pOutData                                            **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
FUNC(void, DCM_CODE) Dcm_UnPack2ByteArray(
  P2VAR(void, AUTOMATIC, DCM_APPL_DATA) pOutData,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pRxData,
  P2CONST(Dcm_PackUnPackType, AUTOMATIC, DCM_APPL_CONST) pUnPackData)
{
  uint16 LusSignalSize;
  boolean LblByteConversion;

  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) LpShadowRxData;
  P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) LpTwoByteBuffer;

  P2FUNC(uint16, DCM_APPL_CODE, LpUnPackFunc) (
    P2CONST(uint8, AUTOMATIC, DCM_APPL_CONST) pRxData);

  LpShadowRxData = pRxData;
  /* polyspace +2 MISRA-C3:11.5 [Justified:Low] Justify with annotations */
  /* polyspace +1 CERT-C:EXP36-C [Justified:Low] "pOutData depend on configuration DcmDspDataType, pOutData will cast to specific type after in specific unpack function" */
  LpTwoByteBuffer = (P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA)) pOutData;

  LblByteConversion = pUnPackData->blByteConversion;
  LusSignalSize = pUnPackData->usSignalSize >> DCM_ONE;

  if (DCM_FALSE == LblByteConversion)
  {
    /* @Trace: Dcm_SUD_API_20323 */
    LpUnPackFunc = Dcm_UnPack2Byte;
  }
  else
  {
    /* @Trace: Dcm_SUD_API_20324 */
    LpUnPackFunc = Dcm_UnPack2ByteOrder;
  }

  SchM_Enter_Dcm_SIGNAL_DATA_PROTECTION_AREA();

  while (LusSignalSize != DCM_ZERO)
  {
    /* @Trace: Dcm_SUD_API_20325 */
    *LpTwoByteBuffer = LpUnPackFunc(LpShadowRxData);

    LusSignalSize--;
    LpShadowRxData = &LpShadowRxData[DCM_TWO];
    LpTwoByteBuffer = &LpTwoByteBuffer[DCM_ONE];
  }

  SchM_Exit_Dcm_SIGNAL_DATA_PROTECTION_AREA();
}

/*******************************************************************************
** Function Name        : Dcm_UnPack4ByteArray                                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Convert received data to uint32 array               **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant for different signals.                    **
**                        Non-Reentrant for the same signal.                  **
**                                                                            **
** Input Parameters     : pRxData, pUnPackData                                **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : pOutData                                            **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
FUNC(void, DCM_CODE) Dcm_UnPack4ByteArray(
  P2VAR(void, AUTOMATIC, DCM_APPL_DATA) pOutData,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pRxData,
  P2CONST(Dcm_PackUnPackType, AUTOMATIC, DCM_APPL_CONST) pUnPackData)
{
  uint16 LusSignalSize;
  boolean LblByteConversion;

  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) LpShadowRxData;
  P2VAR(uint32, AUTOMATIC, DCM_APPL_DATA) LpFourByteBuffer;

  P2FUNC(uint32, DCM_APPL_CODE, LpUnPackFunc) (
    P2CONST(uint8, AUTOMATIC, DCM_APPL_CONST) pRxData);

  LpShadowRxData = pRxData;
  /* polyspace +2 MISRA-C3:11.5 [Justified:Low] Justify with annotations */
  /* polyspace +1 CERT-C:EXP36-C [Justified:Low] "pOutData depend on configuration DcmDspDataType, pOutData will cast to specific type after in specific unpack function" */
  LpFourByteBuffer = (P2VAR(uint32, AUTOMATIC, DCM_APPL_DATA)) pOutData;

  LblByteConversion = pUnPackData->blByteConversion;
  LusSignalSize = pUnPackData->usSignalSize >> DCM_TWO;

  if (DCM_FALSE == LblByteConversion)
  {
    /* @Trace: Dcm_SUD_API_20326 */
    LpUnPackFunc = Dcm_UnPack4Byte;
  }
  else
  {
    /* @Trace: Dcm_SUD_API_20327 */
    LpUnPackFunc = Dcm_UnPack4ByteOrder;
  }

  SchM_Enter_Dcm_SIGNAL_DATA_PROTECTION_AREA();

  while (LusSignalSize != DCM_ZERO)
  {
    /* @Trace: Dcm_SUD_API_20328 */
    *LpFourByteBuffer = LpUnPackFunc(LpShadowRxData);

    LusSignalSize--;
    LpShadowRxData = &LpShadowRxData[DCM_FOUR];
    LpFourByteBuffer = &LpFourByteBuffer[DCM_ONE];
  }

  SchM_Exit_Dcm_SIGNAL_DATA_PROTECTION_AREA();
}

/*******************************************************************************
** Function Name        : Dcm_Pack2Byte                                       **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Convert uint16 variable to uint8 array              **
**                        without consider endianness                         **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant for different signals.                    **
**                        Non-Reentrant for the same signal.                  **
**                                                                            **
** Input Parameters     : signalData                                          **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : pTxData                                             **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
FUNC(void, DCM_CODE) Dcm_Pack2Byte(
  uint16 signalData,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pTxData)
{
  /* @Trace: Dcm_SUD_API_20329 */
  Dcm_MIWord_Access LddSignalData;
  LddSignalData.whole_word = signalData;

  pTxData[DCM_ZERO] = LddSignalData.byte_val.BO_Byte[DCM_ZERO];
  pTxData[DCM_ONE] = LddSignalData.byte_val.BO_Byte[DCM_ONE];
}

/*******************************************************************************
** Function Name        : Dcm_Pack2ByteOrder                                  **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Convert uint16 variable to uint8 array              **
**                        with consider endianness                            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant for different signals.                    **
**                        Non-Reentrant for the same signal.                  **
**                                                                            **
** Input Parameters     : signalData                                          **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : pTxData                                             **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
FUNC(void, DCM_CODE) Dcm_Pack2ByteOrder(
  uint16 signalData,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pTxData)
{
  /* @Trace: Dcm_SUD_API_20330 */
  Dcm_MIWord_Access LddSignalData;
  LddSignalData.whole_word = signalData;

  pTxData[DCM_ZERO] = LddSignalData.byte_val.BO_Byte[DCM_ONE];
  pTxData[DCM_ONE] = LddSignalData.byte_val.BO_Byte[DCM_ZERO];
}

/*******************************************************************************
** Function Name        : Dcm_Pack4Byte                                       **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Convert uint32 variable to uint8 array              **
**                        without consider endianness                         **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant for different signals.                    **
**                        Non-Reentrant for the same signal.                  **
**                                                                            **
** Input Parameters     : signalData                                          **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : pTxData                                             **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
FUNC(void, DCM_CODE) Dcm_Pack4Byte(
  uint32 signalData,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pTxData)
{
  /* @Trace: Dcm_SUD_API_20331 */
  Dcm_MIdWord_Access LddSignalData;
  LddSignalData.whole_dword = signalData;

  pTxData[DCM_ZERO] = LddSignalData.byte_val.BO_Byte[DCM_ZERO];
  pTxData[DCM_ONE] = LddSignalData.byte_val.BO_Byte[DCM_ONE];
  pTxData[DCM_TWO] = LddSignalData.byte_val.BO_Byte[DCM_TWO];
  pTxData[DCM_THREE] = LddSignalData.byte_val.BO_Byte[DCM_THREE];
}

/*******************************************************************************
** Function Name        : Dcm_Pack4ByteOrder                                  **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Convert uint32 variable to uint8 array              **
**                        with consider endianness                            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant for different signals.                    **
**                        Non-Reentrant for the same signal.                  **
**                                                                            **
** Input Parameters     : signalData                                          **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : pTxData                                             **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
FUNC(void, DCM_CODE) Dcm_Pack4ByteOrder(
  uint32 signalData,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pTxData)
{
  /* @Trace: Dcm_SUD_API_20332 */
  Dcm_MIdWord_Access LddSignalData;
  LddSignalData.whole_dword = signalData;

  pTxData[DCM_ZERO] = LddSignalData.byte_val.BO_Byte[DCM_THREE];
  pTxData[DCM_ONE] = LddSignalData.byte_val.BO_Byte[DCM_TWO];
  pTxData[DCM_TWO] = LddSignalData.byte_val.BO_Byte[DCM_ONE];
  pTxData[DCM_THREE] = LddSignalData.byte_val.BO_Byte[DCM_ZERO];
}

/*******************************************************************************
** Function Name        : Dcm_Pack1ByteArray                                  **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Convert uint8 array to transmit data                **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant for different signals.                    **
**                        Non-Reentrant for the same signal.                  **
**                                                                            **
** Input Parameters     : pInData, pPackData                                  **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : pTxData                                             **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
FUNC(void, DCM_CODE) Dcm_Pack1ByteArray(
  P2VAR(void, AUTOMATIC, DCM_APPL_DATA) pInData,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pTxData,
  P2CONST(Dcm_PackUnPackType, AUTOMATIC, DCM_APPL_CONST) pPackData)
{
  uint16 LusSignalSize;
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) LpShadowTxData;
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) LpOneByteBuffer;

  LpShadowTxData = pTxData;
  LusSignalSize = pPackData->usSignalSize;
  /* polyspace +2 MISRA-C3:11.5 [Justified:Low] Justify with annotations */
  /* polyspace +1 CERT-C:EXP36-C [Justified:Low] "pInData depend on configuration DcmDspDataType, pInData will cast to specific type after in specific pack function" */
  LpOneByteBuffer = (P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA)) pInData;

  SchM_Enter_Dcm_SIGNAL_DATA_PROTECTION_AREA();

  while (LusSignalSize != DCM_ZERO) 
  {
    /* @Trace: Dcm_SUD_API_20333 */
    *LpShadowTxData = *LpOneByteBuffer;

    LusSignalSize--;
    LpShadowTxData = &LpShadowTxData[DCM_ONE];
    LpOneByteBuffer = &LpOneByteBuffer[DCM_ONE];
  }

  SchM_Exit_Dcm_SIGNAL_DATA_PROTECTION_AREA();
}

/*******************************************************************************
** Function Name        : Dcm_Pack2ByteArray                                  **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Convert uint16 array to transmit data               **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant for different signals.                    **
**                        Non-Reentrant for the same signal.                  **
**                                                                            **
** Input Parameters     : pInData, pPackData                                  **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : pTxData                                             **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
FUNC(void, DCM_CODE) Dcm_Pack2ByteArray(
  P2VAR(void, AUTOMATIC, DCM_APPL_DATA) pInData,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pTxData,
  P2CONST(Dcm_PackUnPackType, AUTOMATIC, DCM_APPL_CONST) pPackData)
{
  uint16 LusSignalSize;
  boolean LblByteConversion;

  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) LpShadowTxData;
  P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA) LpTwoByteBuffer;
  P2FUNC(void, DCM_APPL_CODE, LpPackFunc) (
    uint16 signalData, P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pTxData);

  LpShadowTxData = pTxData;
  /* polyspace +2 MISRA-C3:11.5 [Justified:Low] Justify with annotations */
  /* polyspace +1 CERT-C:EXP36-C [Justified:Low] "pInData depend on configuration DcmDspDataType, pInData will cast to specific type after in specific pack function" */
  LpTwoByteBuffer = (P2VAR(uint16, AUTOMATIC, DCM_APPL_DATA)) pInData;

  LblByteConversion = pPackData->blByteConversion;
  LusSignalSize = pPackData->usSignalSize >> DCM_ONE;

  if (DCM_FALSE == LblByteConversion)
  {
    /* @Trace: Dcm_SUD_API_20334 */
    LpPackFunc = Dcm_Pack2Byte;
  }
  else
  {
    /* @Trace: Dcm_SUD_API_20335 */
    LpPackFunc = Dcm_Pack2ByteOrder;
  }

  SchM_Enter_Dcm_SIGNAL_DATA_PROTECTION_AREA();

  while (LusSignalSize != DCM_ZERO)
  {
    /* @Trace: Dcm_SUD_API_20336 */
    LpPackFunc(*LpTwoByteBuffer, LpShadowTxData);

    LusSignalSize--;
    LpShadowTxData = &LpShadowTxData[DCM_TWO];
    LpTwoByteBuffer = &LpTwoByteBuffer[DCM_ONE];
  }

  SchM_Exit_Dcm_SIGNAL_DATA_PROTECTION_AREA();
}

/*******************************************************************************
** Function Name        : Dcm_Pack4ByteArray                                  **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Convert uint32 array to transmit data               **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant for different signals.                    **
**                        Non-Reentrant for the same signal.                  **
**                                                                            **
** Input Parameters     : pInData, pPackData                                  **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : pTxData                                             **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
FUNC(void, DCM_CODE) Dcm_Pack4ByteArray(
  P2VAR(void, AUTOMATIC, DCM_APPL_DATA) pInData,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pTxData,
  P2CONST(Dcm_PackUnPackType, AUTOMATIC, DCM_APPL_CONST) pPackData)
{
  uint16 LusSignalSize;
  boolean LblByteConversion;

  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) LpShadowTxData;
  P2VAR(uint32, AUTOMATIC, DCM_APPL_DATA) LpFourByteBuffer;
  P2FUNC(void, DCM_APPL_CODE, LpPackFunc) (
    uint32 signalData, P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) pTxData);

  LpShadowTxData = pTxData;
  /* polyspace +2 MISRA-C3:11.5 [Justified:Low] Justify with annotations */
  /* polyspace +1 CERT-C:EXP36-C [Justified:Low] "pInData depend on configuration DcmDspDataType, pInData will cast to specific type after in specific pack function" */
  LpFourByteBuffer = (P2VAR(uint32, AUTOMATIC, DCM_APPL_DATA)) pInData;

  LblByteConversion = pPackData->blByteConversion;
  LusSignalSize = pPackData->usSignalSize >> DCM_TWO;

  if (DCM_FALSE == LblByteConversion)
  {
    /* @Trace: Dcm_SUD_API_20337 */
    LpPackFunc = Dcm_Pack4Byte;
  }
  else
  {
    /* @Trace: Dcm_SUD_API_20338 */
    LpPackFunc = Dcm_Pack4ByteOrder;
  }

  SchM_Enter_Dcm_SIGNAL_DATA_PROTECTION_AREA();

  while (LusSignalSize != DCM_ZERO)
  {
    /* @Trace: Dcm_SUD_API_20339 */
    LpPackFunc(*LpFourByteBuffer, LpShadowTxData);

    LusSignalSize--;
    LpShadowTxData = &LpShadowTxData[DCM_FOUR];
    LpFourByteBuffer = &LpFourByteBuffer[DCM_ONE];
  }

  SchM_Exit_Dcm_SIGNAL_DATA_PROTECTION_AREA();
}

#define DCM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
