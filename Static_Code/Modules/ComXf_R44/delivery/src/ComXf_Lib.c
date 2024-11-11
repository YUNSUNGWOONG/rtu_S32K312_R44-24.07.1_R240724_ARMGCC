/*******************************************************************************
**                                                                            **
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  This source code is permitted to be used only in projects contracted      **
**  with Hyundai Autoever, and any other use is prohibited.                   **
**  If you use it for other purposes or change the source code,               **
**  you may take legal responsibility.                                        **
**  In this case, There is no warranty and technical support.                 **
**                                                                            **
**  INC-MODULE:           ComXf_Lib.c                                         **
**                                                                            **
**  PRODUCT   :           AUTOSAR COM Based Transformer Module                **
**                                                                            **
**  PURPOSE   :           This file provides definitions of packing functions **
**                                                                            **
**  HARDWARE DEPENDANT [Yes/No]: No                                           **
**                                                                            **
**  AUTOSAR RELEASE:  4.4.0                                                   **
*******************************************************************************/

/*******************************************************************************
**                         Revision History                                   **
********************************************************************************
** Revision  Date             By          Description                         **
********************************************************************************
** 1.0.7     31-Aug-2022      KhaLN1      #CP44-614                           **
** 1.0.4     14-Dec-2021      PhucNHM     R44-Redmine #23089                  **
** 1.0.1     21-Nov-2020      MinhNQ26    Fix Misra rule 17.8, 18.4           **
** 1.0.0     22-Feb-2020      HIEPVT1     Initial Version                     **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA RULE CHECKER)                  **
*******************************************************************************/
/* polyspace-begin MISRA2012:20.1 [Not a defect:Low] "see SWS_MemMap_00003 of AUTOSAR" */
/* polyspace-begin MISRA2012:11.3 [Justified:Low] "The dataElement address is cast to a pointer, that point to an object has size type is equal with dataElement size type to get the correct value in memory" */ 
/* polyspace-begin MISRA2012:D4.14 [Justified:Low] "The validity of all external parameters has checked by ComXf_APIs.c" */

/*******************************************************************************
**                         Header File Include Section                        **
*******************************************************************************/
/* @Trace: SafeComXf_SUD_FILE_001 */
/* Include for ComXf.h */
#include "ComXf.h"
/* Include for ComXf_Lib.h */
#include "ComXf_Lib.h"
/*******************************************************************************
**                            Type Definition                                 **
*******************************************************************************/
/* Word order definition */
#ifndef HIGH_WORD_FIRST
#define HIGH_WORD_FIRST         HIGH_BYTE_FIRST /* Big endian word ordering */
#endif
#ifndef LOW_WORD_FIRST
#define LOW_WORD_FIRST          LOW_BYTE_FIRST /* Little endian word ordering */
#endif
/*******************************************************************************
**                Global Variable Declaration                                 **
*******************************************************************************/

/*******************************************************************************
**                            Function Declaration                            **
*******************************************************************************/

/*******************************************************************************
**                            Version Check                                   **
*******************************************************************************/

/*******************************************************************************
**                           Function Definitions                             **
*******************************************************************************/
/*=============================================================================*
** Service Name         : ComXf_PackBoolean                                   **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function will pack boolean type signal              **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : packSigType, dataElement                            **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : buffer                                              **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : ComXf_Init should be called                         **
**                                                                            **
**============================================================================*/

/* @Trace: SRS_Xfrm_00201 SafeComXf_SUD_DATATYPE_001 */

#define COMXF_START_SEC_CODE_ASIL_D
#include "MemMap.h"
FUNC(void, COMXF_CODE) ComXf_PackBoolean(
  P2VAR(uint8, AUTOMATIC, COMXF_APPL_DATA) buffer,
  P2CONST(ComXf_PackSigType, AUTOMATIC, COMXF_APPL_CONST) packSigType,
  VAR(boolean, AUTOMATIC) dataElement)
{
  /* @Trace: SafeComXf_SUD_API_020 */	
  /*
  * Apply clear bit mask value to Rte buffer and clear boolean bit value
  * fields in the  buffer
  */
  *buffer &= packSigType->startORClearBitMask;

  /* Check if value in the dataElement is one */
  if (dataElement != (boolean)FALSE)
  {
    /*
    * Apply set bit mask value to Rte buffer and set boolean bit value
    * fields in the buffer
    */
    *buffer |= packSigType->setOREndMsk;
  }
}
#define COMXF_STOP_SEC_CODE_ASIL_D
#include "MemMap.h"

/*=============================================================================*
** Service Name         : ComXf_Pack2ByteAlign                                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function will pack 2 byte aligned signal            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : byteDirection, dataElement                          **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : buffer                                              **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : ComXf_Init should be called                         **
**                                                                            **
**============================================================================*/

/* @Trace: SRS_Xfrm_00201 SafeComXf_SUD_DATATYPE_001 */

#define COMXF_START_SEC_CODE_ASIL_D
#include "MemMap.h"
FUNC(void, COMXF_CODE) ComXf_Pack2ByteAlign(
  P2VAR(uint8, AUTOMATIC, COMXF_APPL_DATA) buffer,
  VAR(uint16, AUTOMATIC) dataElement,
  VAR(sint8, AUTOMATIC) byteDirection)
{
  /* @Trace: SafeComXf_SUD_API_021 */	
  /* Local pointer to signal */
  P2CONST(uint8, AUTOMATIC, COMXF_APPL_CONST) sigBuff;

  /* Local variable to calculate the posision of data in buffer */
  VAR(sint8, AUTOMATIC) bytePos;
  VAR(uint16, AUTOMATIC) dataElementTmp;

  dataElementTmp = dataElement;
  bytePos = (sint8)COMXF_HEX_00;
  /* Take a pointer to dataElement */
  sigBuff = (uint8*)&dataElementTmp;

  /* Copy the data to Rte buffer */
  buffer[bytePos] = sigBuff[COMXF_ZEROTH_BYTE];

  /* Increment or decrement data buffer pointer as per endianness */
  bytePos += byteDirection;

  /* Copy the data to Rte buffer */
  buffer[bytePos] = sigBuff[COMXF_FIRST_BYTE];

}
#define COMXF_STOP_SEC_CODE_ASIL_D
#include "MemMap.h"

/*=============================================================================*
** Service Name         : ComXf_Pack3ByteAlign                                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function will pack 3 byte aligned signal            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : dataElement, byteDirection                          **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : buffer                                              **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : ComXf_Init should be called                         **
**                                                                            **
**============================================================================*/

/* @Trace: SRS_Xfrm_00201 SafeComXf_SUD_DATATYPE_001 */

#define COMXF_START_SEC_CODE_ASIL_D
#include "MemMap.h"
FUNC(void, COMXF_CODE) ComXf_Pack3ByteAlign(
  P2VAR(uint8, AUTOMATIC, COMXF_APPL_DATA) buffer,
  VAR(uint32, AUTOMATIC) dataElement, 
  VAR(sint8, AUTOMATIC) byteDirection)
{
  /* @Trace: SafeComXf_SUD_API_022 */	
  /* Local pointer to signal */
  P2CONST(uint8, AUTOMATIC, COMXF_APPL_CONST) sigBuff;


  /* Local variable to calculate the posision of data in buffer */
  VAR(sint8, AUTOMATIC) bytePos;
  
  VAR(uint8, AUTOMATIC) noOfBytes;
  /* Temporal variable  */
  VAR(uint32, AUTOMATIC) dataElementTmp;

  dataElementTmp = dataElement;
  bytePos = (sint8)COMXF_HEX_00;
  noOfBytes = (uint8)COMXF_HEX_00;

  /* Take a pointer to dataElement */
  sigBuff = (uint8*)& dataElementTmp;

  /* If CPU is big endian then increment dataElement pointer */
#if (CPU_BYTE_ORDER == HIGH_WORD_FIRST)

  noOfBytes++;

#endif /* #if (CPU_BYTE_ORDER == HIGH_WORD_FIRST) */


  /* Copy data byte to Rte buffer */
  buffer[bytePos] = sigBuff[noOfBytes];

  /* Increment or decrement data buffer pointer as per endianness */
  bytePos += byteDirection;
  /* Increment dataElement pointer */
  noOfBytes++;

  /* Copy data byte to Rte buffer */
  buffer[bytePos] = sigBuff[noOfBytes];

  /* Increment or decrement data buffer pointer as per endianness */
  bytePos += byteDirection;

  /* Increment dataElement pointer */
  noOfBytes++;

  /* Copy data byte to Rte buffer */
  buffer[bytePos] = sigBuff[noOfBytes];

}
#define COMXF_STOP_SEC_CODE_ASIL_D
#include "MemMap.h"

/*=============================================================================*
** Service Name         : ComXf_Pack4ByteAlign                                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function will pack 4 byte aligned signal            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : dataElement, byteDirection                          **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : buffer                                              **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : ComXf_Init should be called                         **
**                                                                            **
**============================================================================*/

/* @Trace: SRS_Xfrm_00201 SafeComXf_SUD_DATATYPE_001 */

#define COMXF_START_SEC_CODE_ASIL_D
#include "MemMap.h"
FUNC(void, COMXF_CODE) ComXf_Pack4ByteAlign(
  P2VAR(uint8, AUTOMATIC, COMXF_APPL_DATA) buffer,
  VAR(uint32, AUTOMATIC) dataElement,
  VAR(sint8, AUTOMATIC) byteDirection)
{
  /* @Trace: SafeComXf_SUD_API_023 */	
  /* Local pointer to signal */
  P2CONST(uint8, AUTOMATIC, COMXF_APPL_CONST) sigBuff;

  /* Local variable to calculate the posision of data in buffer */
  VAR(sint8, AUTOMATIC) bytePos;
  /* Temporal variable  */
  VAR(uint32, AUTOMATIC) dataElementTmp;

  dataElementTmp = dataElement;
  bytePos = (sint8)COMXF_HEX_00;
  /* Take a pointer to dataElement */
  sigBuff = (uint8*)&dataElementTmp;

  /* Copy data byte to Rte buffer */
  buffer[bytePos] = sigBuff[COMXF_ZEROTH_BYTE];

  /* Increment or decrement pointer on CPU endianness */
  bytePos += byteDirection;

  /* Copy data byte to Rte buffer */
  buffer[bytePos] = sigBuff[COMXF_FIRST_BYTE];

  /* Increment or decrement pointer on CPU endianness */
  bytePos += byteDirection;

  /* Copy data byte to Rte buffer */
  buffer[bytePos] = sigBuff[COMXF_SECOND_BYTE];

  /* Increment or decrement pointer on CPU endianness */
  bytePos += byteDirection;

  /* Copy data byte to Rte buffer */
  buffer[bytePos] = sigBuff[COMXF_THIRD_BYTE];
}
#define COMXF_STOP_SEC_CODE_ASIL_D
#include "MemMap.h"

/*=============================================================================*
** Service Name         : ComXf_PackUint64ByteAlign                           **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function will pack 5, 6, 7 or 8 byte aligned signals**
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : dataElement, byteDirection                          **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : buffer                                              **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : ComXf_Init should be called                         **
**                                                                            **
**============================================================================*/

/* @Trace: SRS_Xfrm_00201 SafeComXf_SUD_DATATYPE_001 */

#define COMXF_START_SEC_CODE_ASIL_D
#include "MemMap.h"
FUNC(void, COMXF_CODE) ComXf_PackUint64ByteAlign(
  P2VAR(uint8, AUTOMATIC, COMXF_APPL_DATA) buffer,
  P2CONST(ComXf_PackSigType, AUTOMATIC, COMXF_APPL_CONST) packSigType,
  VAR(uint64, AUTOMATIC) dataElement, 
  VAR(sint8, AUTOMATIC) byteDirection)
{
  /* @Trace: SafeComXf_SUD_API_024 */	
  /* Local variable to check against the number of bytes */
  VAR(uint8, AUTOMATIC) noOfBytes;

  /* Local variable to calculate the posision of data in buffer */
  VAR(sint8, AUTOMATIC) bytePos;
  
  /* Local pointer to signal */
  P2CONST(uint8, AUTOMATIC, COMXF_APPL_CONST) sigBuff;
  /* Temporal variable  */
  VAR(uint64, AUTOMATIC) dataElementTmp;

  dataElementTmp = dataElement;
  bytePos = (sint8)COMXF_HEX_00;
  noOfBytes = (uint8)COMXF_HEX_00;

  /* Take a pointer to dataElement */
  sigBuff = (uint8*)& dataElementTmp;

  do
  {
    /* Copy data byte to Rte buffer */
    buffer[bytePos] = sigBuff[noOfBytes];

    /* Increment or decrement pointer on CPU endianness */
    bytePos += byteDirection;

    /* Increment the local variable */
    noOfBytes++;

  } while (noOfBytes < packSigType->noOfBytes);
}
#define COMXF_STOP_SEC_CODE_ASIL_D
#include "MemMap.h"

/*=============================================================================*
** Service Name         : ComXf_Pack1ByteNotAlign                             **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function will pack single byte not aligned signal   **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : packSigType, dataElement                            **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : buffer                                              **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : ComXf_Init should be called                         **
**                                                                            **
**============================================================================*/

/* @Trace: SRS_Xfrm_00201 SafeComXf_SUD_DATATYPE_001 */

#define COMXF_START_SEC_CODE_ASIL_D
#include "MemMap.h"
FUNC(void, COMXF_CODE) ComXf_Pack1ByteNotAlign(
  P2VAR(uint8, AUTOMATIC, COMXF_APPL_DATA) buffer,
  P2CONST(ComXf_PackSigType, AUTOMATIC, COMXF_APPL_CONST) packSigType,
  VAR(uint8, AUTOMATIC) dataElement)
{
  /* Temporal variable  */
  VAR(uint8, AUTOMATIC) dataElementTmp;

  dataElementTmp = dataElement;
  /* @Trace: SafeComXf_SUD_API_025 */
  /*
   * Apply clear bit mask value to Rte buffer and clear boolean bit value
   * fields in the  buffer
   */
  *buffer &= packSigType->startORClearBitMask;

  /* Shift the data to signal position */
  dataElementTmp <<= (packSigType->shiftBits);

  /* Clear the unused data value from data element */
  dataElementTmp &= (uint8)(~(packSigType->startORClearBitMask));

  /* Copy data byte to Rte buffer */
  *buffer |= dataElementTmp;

}
#define COMXF_STOP_SEC_CODE_ASIL_D
#include "MemMap.h"

/*=============================================================================*
** Service Name         : ComXf_Pack2ByteNotAlign                             **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function will pack single byte not aligned signal   **
**                        spread across 2 bytes and 2 byte not aligned        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : packSigType, dataElement, byteDirection             **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : buffer                                              **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : ComXf_Init should be called                         **
**                                                                            **
**============================================================================*/

/* @Trace: SRS_Xfrm_00201 SafeComXf_SUD_DATATYPE_001 */

#define COMXF_START_SEC_CODE_ASIL_D
#include "MemMap.h"
FUNC(void, COMXF_CODE) ComXf_Pack2ByteNotAlign(
  P2VAR(uint8, AUTOMATIC, COMXF_APPL_DATA) buffer,
  P2CONST(ComXf_PackSigType, AUTOMATIC, COMXF_APPL_CONST) packSigType,
  VAR(uint16, AUTOMATIC) dataElement,
  VAR(sint8, AUTOMATIC) byteDirection)
{
  /* @Trace: SafeComXf_SUD_API_026 */	
  /* Local variable to store data value */
  VAR(uint8, AUTOMATIC) destBuffData;

  /* Local variable to calculate the posision of data in buffer */
  VAR(sint8, AUTOMATIC) bytePos;
  
  /* Local pointer to signal */
  P2VAR(uint8, AUTOMATIC, COMXF_APPL_DATA) sigBuff;
  VAR(uint16, AUTOMATIC) dataElementTmp;

  dataElementTmp = dataElement;
  bytePos = (sint8)COMXF_HEX_00;
  /* Shift the data to signal position */
  dataElementTmp <<= (packSigType->shiftBits);

  /* Point the signal buffer to dataElement */
  sigBuff = (uint8*)& dataElementTmp;

  /* Copy Rte buffer value to local variable */
  destBuffData = buffer[bytePos];

  /* Apply start mask */
  destBuffData &= (packSigType->startORClearBitMask);

  /* Check whether CPU is Big or Little endian */
#if (CPU_BYTE_ORDER == HIGH_WORD_FIRST)

  sigBuff[COMXF_ZEROTH_BYTE] &= (VAR(uint8, AUTOMATIC))(~(packSigType->startORClearBitMask));

#endif /* End of #if (CPU_BYTE_ORDER == HIGH_WORD_FIRST) */

  /* Copy dataElement value to Rte buffer */
  buffer[bytePos] = destBuffData | sigBuff[COMXF_ZEROTH_BYTE];

  /* Increment or decrement pointer based on CPU endianness */
  bytePos += byteDirection;

  /* Copy Rte buffer value to local variable */
  destBuffData = buffer[bytePos];

  /* Check whether CPU is Big or Little endian */
#if (CPU_BYTE_ORDER == LOW_WORD_FIRST)

  sigBuff[COMXF_FIRST_BYTE] &= (uint8)(~(packSigType->setOREndMsk));

#endif /* End of #if (CPU_BYTE_ORDER == LOW_WORD_FIRST) */

  /* Clear the data at signal position using end mask */
  destBuffData &= (packSigType->setOREndMsk);

  /* Copy dataElement value to Rte buffer */
  buffer[bytePos] = destBuffData | sigBuff[COMXF_FIRST_BYTE];

}
#define COMXF_STOP_SEC_CODE_ASIL_D
#include "MemMap.h"

/*=============================================================================*
** Service Name         : ComXf_Pack3ByteNotAlign                             **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function will pack 2 byte not aligned signal spread **
**                        across 3 bytes and 3 byte not aligned               **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : packSigType, dataElement, byteDirection             **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : buffer                                              **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : ComXf_Init should be called                         **
**                                                                            **
**============================================================================*/

/* @Trace: SRS_Xfrm_00201 SafeComXf_SUD_DATATYPE_001 */

#define COMXF_START_SEC_CODE_ASIL_D
#include "MemMap.h"
FUNC(void, COMXF_CODE) ComXf_Pack3ByteNotAlign(
  P2VAR(uint8, AUTOMATIC, COMXF_APPL_DATA) buffer,
  P2CONST(ComXf_PackSigType, AUTOMATIC, COMXF_APPL_CONST) packSigType,
  VAR(uint32, AUTOMATIC) dataElement,
  VAR(sint8, AUTOMATIC) byteDirection)
{
  /* @Trace: SafeComXf_SUD_API_027 */	
  /* Local variable to store data value */
  VAR(uint8, AUTOMATIC) destBuffData;

  /* Local variable to calculate the posision of data in buffer */
  VAR(sint8, AUTOMATIC) bytePos;
  
  /* Local pointer to signal */
  P2VAR(uint8, AUTOMATIC, COMXF_APPL_DATA) sigBuff;

  VAR(uint8, AUTOMATIC) noOfBytes;
  /* Temporal variable  */
  VAR(uint32, AUTOMATIC) dataElementTmp;

  dataElementTmp = dataElement;
  bytePos = (sint8)COMXF_HEX_00;
  noOfBytes = (uint8)COMXF_HEX_00;

  /* Shift the data to signal position */
  dataElementTmp <<= (packSigType->shiftBits);

  /* Point the signal buffer to dataElement */
  sigBuff = (uint8*)& dataElementTmp;

  /* Copy Rte buffer value to local variable */
  destBuffData = buffer[bytePos];

  /* Apply start mask */
  destBuffData &= (packSigType->startORClearBitMask);

  /* Check whether CPU is Big or Little endian */
#if (CPU_BYTE_ORDER == HIGH_WORD_FIRST)

  /* Increment signal buffer pointer */
  noOfBytes++;

  /* Apply clear mask */
  sigBuff[noOfBytes] &= (uint8)(~(packSigType->startORClearBitMask));

#endif /* End of #if (CPU_BYTE_ORDER == HIGH_WORD_FIRST) */

  /* Copy dataElement value to Rte buffer */
  buffer[bytePos] = destBuffData | sigBuff[noOfBytes];

  /* Increment or decrement pointer based on CPU endianness */
  bytePos += byteDirection;

  /* Increment signal buffer pointer */
  noOfBytes++;

  /* Copy dataElement value to Rte buffer */
  buffer[bytePos] = sigBuff[noOfBytes];

  /* Increment or decrement pointer based on CPU endianness */
  bytePos += byteDirection;

  /* Increment signal buffer pointer */
  noOfBytes++;

  /* Copy Rte buffer value to local variable */
  destBuffData = buffer[bytePos];

  /* Clear the data at signal position using start mask */
  destBuffData &= (packSigType->setOREndMsk);

#if (CPU_BYTE_ORDER == LOW_WORD_FIRST)

  /* Apply end mask */
  sigBuff[noOfBytes] &= (uint8)(~(packSigType->setOREndMsk));

#endif /* End of #if (CPU_BYTE_ORDER == LOW_WORD_FIRST) */

  /* Copy dataElement value to Rte buffer */
  buffer[bytePos] = destBuffData | sigBuff[noOfBytes];

}
#define COMXF_STOP_SEC_CODE_ASIL_D
#include "MemMap.h"

/*=============================================================================*
** Service Name         : ComXf_Pack4ByteNotAlign                             **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function will pack 3 byte not aligned signal spread **
**                        across 4 bytes and 4 byte not aligned               **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : packSigType, dataElement                            **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : buffer                                              **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : ComXf_Init should be called                         **
**                                                                            **
**============================================================================*/

/* @Trace: SRS_Xfrm_00201 SafeComXf_SUD_DATATYPE_001 */

#define COMXF_START_SEC_CODE_ASIL_D
#include "MemMap.h"
FUNC(void, COMXF_CODE) ComXf_Pack4ByteNotAlign(
  P2VAR(uint8, AUTOMATIC, COMXF_APPL_DATA) buffer,
  P2CONST(ComXf_PackSigType, AUTOMATIC, COMXF_APPL_CONST) packSigType,
  VAR(uint32, AUTOMATIC) dataElement,
  VAR(sint8, AUTOMATIC) byteDirection)
{
  /* @Trace: SafeComXf_SUD_API_028 */	
  /* Local variable to store data value */
  VAR(uint8, AUTOMATIC) destBuffData;

  /* Local variable to calculate the posision of data in buffer */
  VAR(sint8, AUTOMATIC) bytePos;
  
  /* Local pointer to signal */
  P2VAR(uint8, AUTOMATIC, COMXF_APPL_DATA) sigBuff;
  /* Temporal variable  */
  VAR(uint32, AUTOMATIC) dataElementTmp;

  dataElementTmp = dataElement;
  bytePos = (sint8)COMXF_HEX_00;
  /* Shift the data to signal position */
  dataElementTmp <<= (packSigType->shiftBits);

  /* Point the signal buffer to dataElement */
  sigBuff = (uint8*)& dataElementTmp;

  /* Copy Rte buffer value to local variable */
  destBuffData = buffer[bytePos];

  /* Clear the data at signal position using start mask */
  destBuffData &= (packSigType->startORClearBitMask);

  /* Check whether CPU is Big or Little endian */
#if (CPU_BYTE_ORDER == HIGH_WORD_FIRST)

  sigBuff[COMXF_ZEROTH_BYTE] &= (VAR(uint8, AUTOMATIC))(~(packSigType->startORClearBitMask));

#endif /* End of #if (CPU_BYTE_ORDER == HIGH_WORD_FIRST) */

  /* Copy dataElement value to Rte buffer */
  buffer[bytePos] = destBuffData | sigBuff[COMXF_ZEROTH_BYTE];

  /* Increment or decrement pointer based on CPU endianness */
  bytePos += byteDirection;

  /* Copy dataElement value to Rte buffer */
  buffer[bytePos] = sigBuff[COMXF_FIRST_BYTE];

  /* Increment or decrement pointer based on CPU endianness */
  bytePos += byteDirection;

  /* Copy dataElement value to Rte buffer */
  buffer[bytePos] = sigBuff[COMXF_SECOND_BYTE];

  /* Increment or decrement pointer based on CPU endianness */
  bytePos += byteDirection;

  /* Copy dataElement value to local variable */
  destBuffData = buffer[bytePos];

  /* Check whether CPU is Big or Little endian */
#if (CPU_BYTE_ORDER == LOW_WORD_FIRST)

  sigBuff[COMXF_THIRD_BYTE] &= (uint8)(~(packSigType->setOREndMsk));

#endif /* End of #if (CPU_BYTE_ORDER == LOW_WORD_FIRST) */

  /* Clear the data at signal position using end mask */
  destBuffData &= (packSigType->setOREndMsk);

  /* Copy dataElement value to Rte buffer */
  buffer[bytePos] = destBuffData | sigBuff[COMXF_THIRD_BYTE];

}
#define COMXF_STOP_SEC_CODE_ASIL_D
#include "MemMap.h"

/*=============================================================================*
** Service Name         : ComXf_Pack5ByteNotAlign                             **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function will pack uint32 bit not byte aligned      **
**                        signal and spread across 5 bytes                    **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : packSigType, dataElement, byteDirection             **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : buffer                                              **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : ComXf_Init should be called                         **
**                                                                            **
**============================================================================*/

/* @Trace: SRS_Xfrm_00201 SafeComXf_SUD_DATATYPE_001 */

#define COMXF_START_SEC_CODE_ASIL_D
#include "MemMap.h"
FUNC(void, COMXF_CODE) ComXf_Pack5ByteNotAlign(
  P2VAR(uint8, AUTOMATIC, COMXF_APPL_DATA) buffer,
  P2CONST(ComXf_PackSigType, AUTOMATIC, COMXF_APPL_CONST) packSigType,
  VAR(uint32, AUTOMATIC) dataElement, 
  VAR(sint8, AUTOMATIC) byteDirection)
{
  /* @Trace: SafeComXf_SUD_API_029 */	
  /* Local variable to store 4 byte data value */
  VAR(uint32, AUTOMATIC) fourByteData;

  /* Local variable to calculate the posision of data in buffer */
  VAR(sint8, AUTOMATIC) bytePos;
  
  /* Local variable to store 1 byte data value */
  VAR(uint8, AUTOMATIC) oneByteData;

  /* Local variable to store data value */
  VAR(uint8, AUTOMATIC) destBuffData;

  /* Local pointer to signal data */
  P2CONST(uint8, AUTOMATIC, COMXF_APPL_CONST) sigBuff;

  bytePos = (sint8)COMXF_HEX_00;
  /* Store dataElement value */
  fourByteData = dataElement;

  /* Point the signal buffer to dataElement */
  sigBuff = (uint8*)& fourByteData;

  /* Check whether CPU is Big or Little endian */
#if (CPU_BYTE_ORDER == HIGH_WORD_FIRST)

  /* Store dataElement higher byte value */
  oneByteData = sigBuff[COMXF_ZEROTH_BYTE];

  /* Shift the higher data byte to signal position */
  oneByteData >>= (COMXF_SHIFT_BY_EIGHT - packSigType->shiftBits);

  oneByteData &= (uint8)(~(packSigType->startORClearBitMask));

#else

  /* Store dataElement higher byte value */
  oneByteData = sigBuff[COMXF_THIRD_BYTE];

  /* Shift the higher data byte to signal position */
  oneByteData >>=
    ((uint8)COMXF_SHIFT_BY_EIGHT - packSigType->shiftBits);

  oneByteData &= (uint8)(~(packSigType->setOREndMsk));
#endif /*End of #if (CPU_BYTE_ORDER == HIGH_WORD_FIRST)*/

  /* Shift the data to signal position */
  fourByteData <<= (packSigType->shiftBits);
  
  /* Point the signal buffer to dataElement */
  sigBuff = (uint8*)& fourByteData;  

  /* Copy buffer value to local variable */
  destBuffData = buffer[bytePos];

  /* Clear the data at signal position using start mask */
  destBuffData &= (packSigType->startORClearBitMask);

  /* Check whether CPU is Big or Little endian */
#if (CPU_BYTE_ORDER == HIGH_WORD_FIRST)

  /* Copy dataElement value to Rte buffer */
  buffer[bytePos] = destBuffData | oneByteData;

  /* Increment or decrement pointer based on CPU endianness */
  bytePos += byteDirection;

  /* Copy dataElement value to Rte buffer */
  buffer[bytePos] = sigBuff[COMXF_ZEROTH_BYTE];

#else

  /* Copy dataElement value to Rte buffer */
  buffer[bytePos] = destBuffData | sigBuff[COMXF_ZEROTH_BYTE];

#endif /* End of #if (CPU_BYTE_ORDER == HIGH_WORD_FIRST) */

  /* Increment or decrement pointer based on CPU endianness */
  bytePos += byteDirection;

  /* Copy dataElement value to Rte buffer */
  buffer[bytePos] = sigBuff[COMXF_FIRST_BYTE];

  /* Increment or decrement pointer based on CPU endianness */
  bytePos += byteDirection;

  /* Copy dataElement value to Rte buffer */
  buffer[bytePos] = sigBuff[COMXF_SECOND_BYTE];

  /* Increment or decrement pointer based on CPU endianness */
  bytePos += byteDirection;

  /* Check whether CPU is Big or Little Endian */
#if (CPU_BYTE_ORDER == LOW_WORD_FIRST)

  /* Increment or decrement pointer based on CPU endianness */
  buffer[bytePos] = sigBuff[COMXF_THIRD_BYTE];

  /* Increment or decrement pointer based on CPU endianness */
  bytePos += byteDirection;

  /* Copy buffer value to local variable */
  destBuffData = buffer[bytePos];

  /* Clear the data at signal position using start mask */
  destBuffData &= (packSigType->setOREndMsk);

  /* Increment or decrement pointer based on CPU endianness */
  buffer[bytePos] = destBuffData | oneByteData;

#else

  /* Clear the data at signal position using end mask */
  buffer[bytePos] &= (packSigType->setOREndMsk);

  /* Increment or decrement pointer based on CPU endianness */
  buffer[bytePos] = buffer[bytePos] | sigBuff[COMXF_THIRD_BYTE];
#endif /* End of #if (CPU_BYTE_ORDER == LOW_WORD_FIRST) */
}
#define COMXF_STOP_SEC_CODE_ASIL_D
#include "MemMap.h"

/*=============================================================================*
** Service Name         : ComXf_PackArray                                     **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function will pack UINT8_N signal                   **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : packSigType, dataElement                            **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : buffer                                              **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : ComXf_Init should be called                         **
**                                                                            **
**============================================================================*/

/* @Trace: SRS_Xfrm_00201 SafeComXf_SUD_DATATYPE_001 */

#define COMXF_START_SEC_CODE_ASIL_D
#include "MemMap.h"
FUNC(void, COMXF_CODE) ComXf_PackArray(
  P2VAR(uint8, AUTOMATIC, COMXF_APPL_DATA) buffer,
  P2CONST(ComXf_PackSigType, AUTOMATIC, COMXF_APPL_CONST) packSigType,
  P2CONST(uint8, AUTOMATIC, COMXF_APPL_CONST) dataElement)
{
  /* @Trace: SafeComXf_SUD_API_030 */	
  /* Local reference to source buffer */
  P2CONST(uint8, AUTOMATIC, COMXF_APPL_CONST) sigBuff;

  /* Loop buffer index */
  VAR(uint8, AUTOMATIC) sigBytesIndex;

  sigBytesIndex = (uint8)COMXF_HEX_00;

  /* Copy the signal data pointer */
  sigBuff = (const uint8*)(dataElement);

  /* Copy each byte of signal data to destination buffer */
  do
  {
    /* Copy data from signal buffer to destination buffer */
    buffer[sigBytesIndex] = sigBuff[sigBytesIndex];

    /* Point to next address */
    sigBytesIndex++;

  } while (sigBytesIndex < packSigType->noOfBytes);
}
#define COMXF_STOP_SEC_CODE_ASIL_D
#include "MemMap.h"

/*=============================================================================*
** Service Name         : ComXf_Pack9ByteNotAlign                             **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function will pack uint64 byte not aligned          **
**                        signal spread across 9 bytes                        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : packSigType, dataElement, byteDirection             **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : buffer                                              **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : ComXf_Init should be called                         **
**                                                                            **
**============================================================================*/

/* @Trace: SRS_Xfrm_00201 SafeComXf_SUD_DATATYPE_001 */

#define COMXF_START_SEC_CODE_ASIL_D
#include "MemMap.h"
FUNC(void, COMXF_CODE) ComXf_Pack9ByteNotAlign(
  P2VAR(uint8, AUTOMATIC, COMXF_APPL_DATA) buffer,
  P2CONST(ComXf_PackSigType, AUTOMATIC, COMXF_APPL_CONST) packSigType,
  VAR(uint64, AUTOMATIC) dataElement,
  VAR(sint8, AUTOMATIC) byteDirection)
{
  /* @Trace: SafeComXf_SUD_API_031 */	
  /* Local variable to to check against the number of bytes */
  VAR(uint8, AUTOMATIC) noOfBytes;

  /* Local variable to calculate the posision of data in buffer */
  VAR(sint8, AUTOMATIC) bytePos;
  
  /* Local variable to store 8 byte data value */
  VAR(uint64, AUTOMATIC) eightByteData;

  /* Local variable to store 1 byte data value */
  VAR(uint8, AUTOMATIC) oneByteData;

  /* Local variable to store data value */
  VAR(uint8, AUTOMATIC) destBuffData;

  /* Local pointer to signal data */
  P2CONST(uint8, AUTOMATIC, COMXF_APPL_CONST) sigBuff;

  bytePos = (sint8)COMXF_HEX_00;
  noOfBytes = (uint8)COMXF_HEX_00;

  /* Store dataElement value */
  eightByteData = dataElement;

  /* Point the signal buffer to dataElement */
  sigBuff = (uint8*)& eightByteData;

  /* Check whether CPU is Big or Little endian */
#if (CPU_BYTE_ORDER == HIGH_WORD_FIRST)

  /* Store dataElement higher byte value */
  oneByteData = sigBuff[COMXF_ZEROTH_BYTE];

  /* Shift the higher data byte to signal position */
  oneByteData >>= (COMXF_SHIFT_BY_EIGHT - packSigType->shiftBits);

  oneByteData &= (uint8)(~(packSigType->startORClearBitMask));

#else

  /* Store dataElement higher byte value */
  oneByteData =
    sigBuff[packSigType->noOfBytes - (uint8)COMXF_SECOND_BYTE];

  /* Shift the higher data byte to signal position */
  oneByteData >>=
    ((uint8)COMXF_SHIFT_BY_EIGHT - packSigType->shiftBits);

  oneByteData &= (uint8)(~(packSigType->setOREndMsk));
#endif /*End of  (CPU_BYTE_ORDER == HIGH_WORD_FIRST)*/

  /* Shift the data to signal position */
  eightByteData <<= (packSigType->shiftBits);
  
  /* Point the signal buffer to dataElement */
  sigBuff = (uint8*)& eightByteData;  

  /* Copy buffer value to local variable */
  destBuffData = buffer[bytePos];

  /* Clear the data at signal position using start mask */
  destBuffData &= (packSigType->startORClearBitMask);

  /* Check whether CPU is Big or Little endian */
#if (CPU_BYTE_ORDER == HIGH_WORD_FIRST)

  /* Copy dataElement value to Rte buffer */
  buffer[bytePos] = destBuffData | oneByteData;

  /* Increment or decrement pointer based on CPU endianness */
  bytePos += byteDirection;

  /* Copy dataElement value to Rte buffer */
  buffer[bytePos] = sigBuff[COMXF_ZEROTH_BYTE];

#else

  /* Copy dataElement value to Rte buffer */
  buffer[bytePos] = destBuffData | sigBuff[COMXF_ZEROTH_BYTE];

#endif /* End of #if (CPU_BYTE_ORDER == HIGH_WORD_FIRST) */

  /* Increment or decrement pointer based on CPU endianness */
  bytePos += byteDirection;

  do
  {
    /* Increment the local variable */
    noOfBytes++;

    /* Copy dataElement value to Rte buffer */
    buffer[bytePos] = sigBuff[noOfBytes];

    /* Increment or decrement pointer based on CPU endianness */
    bytePos += byteDirection;

  } while (noOfBytes <
    (packSigType->noOfBytes - (uint8)COMXF_THREE_BYTES));

  /* Check whether CPU is Big or Little Endian */
#if (CPU_BYTE_ORDER == LOW_WORD_FIRST)

  /* Increment or decrement pointer based on CPU endianness */
  buffer[bytePos] =
    sigBuff[packSigType->noOfBytes - (uint8)COMXF_TWO_BYTES];

  /* Increment or decrement pointer based on CPU endianness */
  bytePos += byteDirection;

  /* Copy buffer value to local variable */
  destBuffData = buffer[bytePos];

  /* Clear the data at signal position using start mask */
  destBuffData &= (packSigType->setOREndMsk);

  /* Increment or decrement pointer based on CPU endianness */
  buffer[bytePos] = destBuffData | oneByteData;

#else

  /* Clear the data at signal position using end mask */
  buffer[bytePos] &= (packSigType->setOREndMsk);

  /* Increment or decrement pointer based on CPU endianness */
  buffer[bytePos] = buffer[bytePos] |
    sigBuff[packSigType->noOfBytes - COMXF_TWO_BYTES];

#endif /* End of #if (CPU_BYTE_ORDER == LOW_WORD_FIRST) */
}
#define COMXF_STOP_SEC_CODE_ASIL_D
#include "MemMap.h"

/*=============================================================================*
** Service Name         : ComXf_Pack5678ByteNotAlign                          **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function will pack 6,7, or 8 bytes not aligned      **
**                        signal spread across 6,7 or 8 bytes                 **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : packSigType, dataElement                            **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : buffer                                              **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : ComXf_Init should be called                         **
**                                                                            **
**============================================================================*/

/* @Trace: SRS_Xfrm_00201 SafeComXf_SUD_DATATYPE_001 */

#define COMXF_START_SEC_CODE_ASIL_D
#include "MemMap.h"
FUNC(void, COMXF_CODE) ComXf_Pack5678ByteNotAlign(
  P2VAR(uint8, AUTOMATIC, COMXF_APPL_DATA) buffer,
  P2CONST(ComXf_PackSigType, AUTOMATIC, COMXF_APPL_CONST) packSigType,
  VAR(uint64, AUTOMATIC) dataElement,
  VAR(sint8, AUTOMATIC) byteDirection)
{
  /* @Trace: SafeComXf_SUD_API_032 */	
  /* Local variable to to check against the number of bytes */
  VAR(uint8, AUTOMATIC) noOfBytes;

  /* Local variable to calculate the posision of data in buffer */
  VAR(sint8, AUTOMATIC) bytePos;
  
  /* Local variable to store data value */
  VAR(uint8, AUTOMATIC) destBuffData;

  /* Local pointer to signal */
  P2VAR(uint8, AUTOMATIC, COMXF_APPL_DATA) sigBuff;
  
  /* Temporal variable  */
  VAR(uint64, AUTOMATIC) dataElementTmp;

  bytePos = (sint8)COMXF_HEX_00;
  noOfBytes = (uint8)COMXF_HEX_00;
  dataElementTmp = dataElement;

  /* Shift the data to signal position */
  dataElementTmp <<= (packSigType->shiftBits);

  /* Point the signal buffer to dataElement */
  sigBuff = (uint8*)&dataElementTmp;

  /* Copy Rte buffer value to local variable */
  destBuffData = buffer[bytePos];

  /* Clear the data at signal position using start mask */
  destBuffData &= (packSigType->startORClearBitMask);

  /* Check whether CPU is Big or Little endian */
#if (CPU_BYTE_ORDER == HIGH_WORD_FIRST)

  sigBuff[noOfBytes] &= (uint8)(~(packSigType->startORClearBitMask));

#endif /* End of #if (CPU_BYTE_ORDER == HIGH_WORD_FIRST) */

  /* Copy dataElement value to Rte buffer */
  * buffer = destBuffData | sigBuff[noOfBytes];

  do
  {
    /* Increment the local variable */
    noOfBytes++;

    /* Increment or decrement pointer based on CPU endianness */
    bytePos += byteDirection;

    /* Copy dataElement value to Rte buffer */
    buffer[bytePos] = sigBuff[noOfBytes];

  } while (noOfBytes <
    (packSigType->noOfBytes - (uint8)COMXF_TWO_BYTES));

  /* Increment or decrement pointer based on CPU endianness */
  bytePos += byteDirection;

  /* Copy dataElement value to local variable */
  destBuffData = buffer[bytePos];

  /* Check whether CPU is Big or Little endian */
#if (CPU_BYTE_ORDER == LOW_WORD_FIRST)

  sigBuff[packSigType->noOfBytes - (VAR(uint8, AUTOMATIC))COMXF_FIRST_BYTE]
    &= (uint8)(~(packSigType->setOREndMsk));

#endif /* End of #if (CPU_BYTE_ORDER == LOW_WORD_FIRST) */

  /* Clear the data at signal position using end mask */
  destBuffData &= (packSigType->setOREndMsk);

  /* Copy dataElement value to Rte buffer */
  buffer[bytePos] = destBuffData |
    sigBuff[packSigType->noOfBytes - (uint8)COMXF_FIRST_BYTE];

}
#define COMXF_STOP_SEC_CODE_ASIL_D
#include "MemMap.h"


/*=============================================================================*
** Service Name         : ComXf_UnPackBoolean                                 **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function will unpack boolean type signal            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : unPackSigType, buffer                               **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : boolean                                             **
**                                                                            **
** Preconditions        : ComXf_Init should be called                         **
**                                                                            **
**============================================================================*/

/* @Trace: SRS_Xfrm_00201 SafeComXf_SUD_DATATYPE_001 */

#define COMXF_START_SEC_CODE_ASIL_D
#include "MemMap.h"
FUNC(boolean, COMXF_CODE) ComXf_UnPackBoolean(
  P2CONST(uint8, AUTOMATIC, COMXF_APPL_CONST) buffer,
  P2CONST(ComXf_UnPackSigType, AUTOMATIC, COMXF_APPL_CONST) unPackSigType)
{
  /* @Trace: SafeComXf_SUD_API_033 */	
  /* Local variable to store dataElement value */
  VAR(boolean, AUTOMATIC) dataElement;

  /* Make dataElementBoolean as false */
  dataElement = FALSE;

  /* Apply end mask and check for value as 1 */
  if ((*buffer & unPackSigType->rxEndMsk) != (boolean)FALSE)
  {
    /* Make dataElementBoolean as true */
    dataElement = TRUE;
  }

  /* Return dataElementBoolean value */
  return dataElement;
}
#define COMXF_STOP_SEC_CODE_ASIL_D
#include "MemMap.h"

/*=============================================================================*
** Service Name         : ComXf_UnPack2ByteAlign                              **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function will unpack byte aligned uint16 signal in  **
**                        to single byte                                      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : buffer, unPackSigType                               **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : uint8                                               **
**                                                                            **
** Preconditions        : ComXf_Init should be called                         **
**                                                                            **
**============================================================================*/

/* @Trace: SRS_Xfrm_00201 SafeComXf_SUD_DATATYPE_001 */

#define COMXF_START_SEC_CODE_ASIL_D
#include "MemMap.h"
FUNC(uint16, COMXF_CODE) ComXf_UnPack2ByteAlign(
  P2CONST(uint8, AUTOMATIC, COMXF_APPL_CONST) buffer,
  VAR(sint8, AUTOMATIC) byteDirection)
{
  /* @Trace: SafeComXf_SUD_API_034 */	
  /* Local variable to store data element value */
  VAR(uint16,AUTOMATIC) dataElement;

  /* Local variable to calculate the posision of data in buffer */
  VAR(sint8, AUTOMATIC) bytePos;
  
  /* Local pointer to data element */
  P2VAR(uint8, AUTOMATIC, COMXF_APPL_DATA) dataBuff;

  bytePos = (sint8)COMXF_HEX_00;
  /* Take a pointer to signal data element */
  dataBuff = (uint8*)& dataElement;

  /* Copy the data from input buffer */
  dataBuff[COMXF_ZEROTH_BYTE] = buffer[bytePos];

  /*
   * Increment or decrement data buffer pointer as per endianness
   * If CPU and Signal Endianness is same then it will be incremented otherwise
   * decremented
   */
  bytePos += byteDirection;

  /* Copy the data from input buffer */
  dataBuff[COMXF_FIRST_BYTE] = buffer[bytePos];

  /* Return value */
  return dataElement;
}
#define COMXF_STOP_SEC_CODE_ASIL_D
#include "MemMap.h"

/*=============================================================================*
** Service Name         : ComXf_UnPack3ByteAlign                              **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function will unpack 3 byte aligned signal          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : buffer, unPackSigType, byteDirection                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : uint32                                              **
**                                                                            **
** Preconditions        : ComXf_Init should be called                         **
**                                                                            **
**============================================================================*/

/* @Trace: SRS_Xfrm_00201 SafeComXf_SUD_DATATYPE_001 */

#define COMXF_START_SEC_CODE_ASIL_D
#include "MemMap.h"
FUNC(uint32, COMXF_CODE) ComXf_UnPack3ByteAlign(
  P2CONST(uint8, AUTOMATIC, COMXF_APPL_CONST) buffer,
  P2CONST(ComXf_UnPackSigType, AUTOMATIC, COMXF_APPL_CONST) unPackSigType,
  VAR(sint8, AUTOMATIC) byteDirection)
{
  /* @Trace: SafeComXf_SUD_API_035 */	
  /* Local variable to store data element value */
  VAR(uint32, AUTOMATIC) dataElement;

  /* Local variable to calculate the posision of data in buffer */
  VAR(sint8, AUTOMATIC) bytePos;

  /* Local variable to store sign mask value */
  VAR(uint32, AUTOMATIC) sigSignMsk;

  /* Local pointer to signal */
  P2VAR(uint8, AUTOMATIC, COMXF_APPL_DATA) dataBuff;

  bytePos = (sint8)COMXF_HEX_00;
  dataElement = (uint32)COMXF_HEX_00;

  /* Take a pointer to signal data */
  dataBuff = (uint8*)& dataElement;

  /* Copy the data from Rte buffer */
  dataBuff[COMXF_ZEROTH_BYTE] = buffer[bytePos];

  /* Increment or decrement data buffer pointer as per endianness */
  bytePos += byteDirection;

  /* Copy the data from Rte buffer */
  dataBuff[COMXF_FIRST_BYTE] = buffer[bytePos];

  /* Increment or decrement data buffer pointer as per endianness */
  bytePos += byteDirection;

  /* Copy the data from Rte buffer */
  dataBuff[COMXF_SECOND_BYTE] = buffer[bytePos];

  /* Take sign mask value into local variable  */
  sigSignMsk = unPackSigType->sigSignMsk32;

  /* Check whether signal data is signed or unsigned */
  if ((dataElement & sigSignMsk) != (uint32)COMXF_NOT_SIGNED_SIGNAL)
  {
    /* Take signed value into dataBuff */
    dataElement |= sigSignMsk;
  }

  /* Return dataElement */
  return dataElement;
}
#define COMXF_STOP_SEC_CODE_ASIL_D
#include "MemMap.h"

/*=============================================================================*
** Service Name         : ComXf_UnPack4ByteAlign                              **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function will unpack 4 byte aligned signal          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : buffer, unPackSigType, byteDirection                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : uint32                                              **
**                                                                            **
** Preconditions        : ComXf_Init should be called                         **
**                                                                            **
**============================================================================*/

/* @Trace: SRS_Xfrm_00201 SafeComXf_SUD_DATATYPE_001 */

#define COMXF_START_SEC_CODE_ASIL_D
#include "MemMap.h"
FUNC(uint32, COMXF_CODE) ComXf_UnPack4ByteAlign(
  P2CONST(uint8, AUTOMATIC, COMXF_APPL_CONST) buffer,
  VAR(sint8, AUTOMATIC) byteDirection)
{
  /* @Trace: SafeComXf_SUD_API_036 */	
  /* Local variable to store data element value */
  VAR(uint32, AUTOMATIC) dataElement;

  /* Local variable to calculate the posision of data in buffer */
  VAR(sint8, AUTOMATIC) bytePos;

  /* Local pointer to signal */
  P2VAR(uint8, AUTOMATIC, COMXF_APPL_DATA) dataBuff;

  bytePos = (sint8)COMXF_HEX_00;
  /* Take a pointer to signal data */
  dataBuff = (uint8*)& dataElement;

  /* Copy the data from Rte buffer */
  dataBuff[COMXF_ZEROTH_BYTE] = buffer[bytePos];

  /* Increment or decrement data buffer pointer as per endianness */
  bytePos += byteDirection;

  /* Copy the data from Rte buffer */
  dataBuff[COMXF_FIRST_BYTE] = buffer[bytePos];

  /* Increment or decrement data buffer pointer as per endianness */
  bytePos += byteDirection;

  /* Copy the data from Rte buffer */
  dataBuff[COMXF_SECOND_BYTE] = buffer[bytePos];

  /* Increment or decrement data buffer pointer as per endianness */
  bytePos += byteDirection;

  /* Copy the data from Rte buffer */
  dataBuff[COMXF_THIRD_BYTE] = buffer[bytePos];

  /* Return dataElement */
  return dataElement;
}
#define COMXF_STOP_SEC_CODE_ASIL_D
#include "MemMap.h"

/*=============================================================================*
** Service Name         : ComXf_UnPackUint64ByteAlign                         **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function will unpack 5,6,7 and 8 byte aligned       **
**                        signals                                             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : buffer, unPackSigType, byteDirection                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : uint64                                              **
**                                                                            **
** Preconditions        : ComXf_Init should be called                         **
**                                                                            **
**============================================================================*/

/* @Trace: SRS_Xfrm_00201 SafeComXf_SUD_DATATYPE_001 */

#define COMXF_START_SEC_CODE_ASIL_D
#include "MemMap.h"
FUNC(uint64, COMXF_CODE) ComXf_UnPackUint64ByteAlign(
  P2CONST(uint8, AUTOMATIC, COMXF_APPL_CONST) buffer,
  P2CONST(ComXf_UnPackSigType, AUTOMATIC, COMXF_APPL_CONST) unPackSigType,
  VAR(sint8, AUTOMATIC) byteDirection)
{
  /* @Trace: SafeComXf_SUD_API_037 */	
  /* Local variable to check against the number of bytes */
  VAR(uint8, AUTOMATIC) noOfBytes;

  /* Local variable to calculate the posision of data in buffer */
  VAR(sint8, AUTOMATIC) bytePos;

  /* Local variable to store data element value */
  VAR(uint64, AUTOMATIC) dataElement;

  /* Local variable to store sign mask value */
  VAR(uint64, AUTOMATIC) sigSignMsk;

  /* Local pointer to signal */
  P2VAR(uint8, AUTOMATIC, COMXF_APPL_DATA) dataBuff;

  bytePos = (sint8)COMXF_HEX_00;
  noOfBytes = (uint8)COMXF_HEX_00;

  dataElement = (uint64)COMXF_HEX_00;

  /* Take a pointer to signal data */
  dataBuff = (uint8*)& dataElement;

  do
  {
    /* Copy the data from Rte buffer */
    dataBuff[noOfBytes] = buffer[bytePos];

    /* Increment or decrement data buffer pointer as per endianness */
    bytePos += byteDirection;

    /* Increment the local variable */
    noOfBytes++;

  } while (noOfBytes < unPackSigType->noOfBytes);

  /* Take sign mask value into local variable  */
  sigSignMsk = unPackSigType->sigSignMsk64;

  /* Check whether signal data is signed or unsigned */
  if ((dataElement & sigSignMsk) != (uint64)COMXF_NOT_SIGNED_SIGNAL)
  {
    /* Take signed value into dataBuff */
    dataElement |= sigSignMsk;
  }

  /* Return dataElement */
  return dataElement;
}
#define COMXF_STOP_SEC_CODE_ASIL_D
#include "MemMap.h"

/*=============================================================================*
** Service Name         : ComXf_UnPackFloat32ByteAlign                        **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function will unpack float32 byte aligned           **
**                        type signal                                         **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : unPackSigType, buffer, byteDirection                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : float32                                             **
**                                                                            **
** Preconditions        : ComXf_Init should be called                         **
**                                                                            **
**============================================================================*/

/* @Trace: SRS_Xfrm_00201 SafeComXf_SUD_DATATYPE_001 */

#define COMXF_START_SEC_CODE_ASIL_D
#include "MemMap.h"
FUNC(float32, COMXF_CODE) ComXf_UnPackFloat32ByteAlign(
  P2CONST(uint8, AUTOMATIC, COMXF_APPL_CONST) buffer,
  VAR(sint8, AUTOMATIC) byteDirection)
{
  /* @Trace: SafeComXf_SUD_API_038 */
  /* Local variable to store data */
  VAR(ComXf_Float32DataType, AUTOMATIC) dataElement;

  /* Get the unpacked data */
  dataElement.u32 =
    ComXf_UnPack4ByteAlign(buffer, byteDirection);

  /* Return signal data */
  return (dataElement.f32);

}
#define COMXF_STOP_SEC_CODE_ASIL_D
#include "MemMap.h"

/*=============================================================================*
** Service Name         : ComXf_UnPackFloat64ByteAlign                        **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function will unpack float64 byte aligned           **
**                        type signal                                         **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : unPackSigType, buffer, byteDirection                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : float64                                             **
**                                                                            **
** Preconditions        : ComXf_Init should be called                         **
**                                                                            **
**============================================================================*/

/* @Trace: SRS_Xfrm_00201 SafeComXf_SUD_DATATYPE_001 */

#define COMXF_START_SEC_CODE_ASIL_D
#include "MemMap.h"
FUNC(float64, COMXF_CODE) ComXf_UnPackFloat64ByteAlign(
  P2CONST(uint8, AUTOMATIC, COMXF_APPL_CONST) buffer,
  P2CONST(ComXf_UnPackSigType, AUTOMATIC, COMXF_APPL_CONST) unPackSigType,
  VAR(sint8, AUTOMATIC) byteDirection)
{
  /* @Trace: SafeComXf_SUD_API_039 */
  /* Local variable to store data */
  VAR(ComXf_Float64DataType, AUTOMATIC) dataElement;

  /* Get the unpacked data */
  dataElement.u64 =
    ComXf_UnPackUint64ByteAlign(buffer,
      unPackSigType, byteDirection);

  /* Return signal data */
  return (dataElement.f64);

}
#define COMXF_STOP_SEC_CODE_ASIL_D
#include "MemMap.h"

/*=============================================================================*
** Service Name         : ComXf_UnPack1ByteNotAlign                           **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function will unpack single byte not aligned signal **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : buffer, unPackSigType                               **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : uint8                                               **
**                                                                            **
** Preconditions        : ComXf_Init should be called                         **
**                                                                            **
**============================================================================*/

/* @Trace: SRS_Xfrm_00201 SafeComXf_SUD_DATATYPE_001 */

#define COMXF_START_SEC_CODE_ASIL_D
#include "MemMap.h"
FUNC(uint8, COMXF_CODE) ComXf_UnPack1ByteNotAlign(
  P2CONST(uint8, AUTOMATIC, COMXF_APPL_CONST) buffer,
  P2CONST(ComXf_UnPackSigType, AUTOMATIC, COMXF_APPL_CONST) unPackSigType)
{
  /* @Trace: SafeComXf_SUD_API_040 */	
  /* Local variable to store data element value */
  VAR(uint8, AUTOMATIC) dataElement;

  /* Local variable to store sign mask value */
  VAR(uint8, AUTOMATIC) sigSignMsk;

  dataElement = *buffer;

  /* Mask the Data with end mask to clear data other than signal data */
  dataElement = dataElement & (unPackSigType->rxEndMsk);

  /* Shift the data to signal position */
  dataElement = dataElement >> (unPackSigType->shiftBits);

  /* Take sign mask value into local variable  */
  sigSignMsk = (uint8)unPackSigType->sigSignMsk32;

  /* Check whether signal data is signed or unsigned */
  if ((dataElement & sigSignMsk) != (uint8)COMXF_NOT_SIGNED_SIGNAL)
  {
    /* Take signed value into dataBuff */
    dataElement |= sigSignMsk;
  }

  /* Return dataElement */
  return dataElement;
}
#define COMXF_STOP_SEC_CODE_ASIL_D
#include "MemMap.h"

/*=============================================================================*
** Service Name         : ComXf_UnPack2ByteNotAlign                           **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function will unpack single byte spread across 2    **
**                        bytes and 2 byte not aligned                        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : buffer, unPackSigType, byteDirection                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : uint16                                              **
**                                                                            **
** Preconditions        : ComXf_Init should be called                         **
**                                                                            **
**============================================================================*/

/* @Trace: SRS_Xfrm_00201 SafeComXf_SUD_DATATYPE_001 */

#define COMXF_START_SEC_CODE_ASIL_D
#include "MemMap.h"
FUNC(uint16, COMXF_CODE) ComXf_UnPack2ByteNotAlign(
  P2CONST(uint8, AUTOMATIC, COMXF_APPL_CONST) buffer,
  P2CONST(ComXf_UnPackSigType, AUTOMATIC, COMXF_APPL_CONST) unPackSigType,
  VAR(sint8, AUTOMATIC) byteDirection)
{
  /* @Trace: SafeComXf_SUD_API_041 */	
  /* Local variable to store data element value */
  VAR(uint16, AUTOMATIC) dataElement;

  /* Local variable to calculate the posision of data in buffer */
  VAR(sint8, AUTOMATIC) bytePos;

  /* Local variable to store sign mask value */
  VAR(uint16, AUTOMATIC) sigSignMsk;

  /* Local pointer to signal data */
  P2VAR(uint8, AUTOMATIC, COMXF_APPL_DATA) dataBuffer;

  bytePos = (sint8)COMXF_HEX_00;
  dataElement = (uint16)COMXF_HEX_00;

  /* Take a pointer to signal data */
  dataBuffer = (uint8*)& dataElement;

  /* Copy the data from Rte buffer */
  dataBuffer[COMXF_ZEROTH_BYTE] = buffer[bytePos];

  /* Increment or decrement data buffer pointer as per endianness */
  bytePos += byteDirection;

  /* Copy the data from Rte buffer */
  dataBuffer[COMXF_FIRST_BYTE] = buffer[bytePos];

#if (CPU_BYTE_ORDER == HIGH_WORD_FIRST)

  /* Apply end mask and copy the data from Rte buffer */
  dataBuffer[COMXF_ZEROTH_BYTE] &= unPackSigType->rxEndMsk;

#else

  /* Apply end mask and copy the data from Rte buffer */
  dataBuffer[COMXF_FIRST_BYTE] &= unPackSigType->rxEndMsk;

#endif /* End of #if (CPU_BYTE_ORDER == HIGH_WORD_FIRST) */

  /* Shift data to signal position */
  dataElement >>= unPackSigType->shiftBits;

  /* Take signed value into dataBuff */
  sigSignMsk = (uint16)unPackSigType->sigSignMsk32;

  /* Check whether signal data is signed or unsigned */
  if ((dataElement & sigSignMsk) != (uint16)COMXF_NOT_SIGNED_SIGNAL)
  {
    /* Take signed value into dataBuff */
    dataElement |= sigSignMsk;
  }

  /* Return dataElement */
  return dataElement;
}
#define COMXF_STOP_SEC_CODE_ASIL_D
#include "MemMap.h"

/*=============================================================================*
** Service Name         : ComXf_UnPack3ByteNotAlign                           **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function will unpack 2 byte not aligned signal      **
**                        spread across 3 bytes and 3 byte not aligned        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : buffer, unPackSigType, byteDirection                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : uint32                                              **
**                                                                            **
** Preconditions        : ComXf_Init should be called                         **
**                                                                            **
**============================================================================*/

/* @Trace: SRS_Xfrm_00201 SafeComXf_SUD_DATATYPE_001 */

#define COMXF_START_SEC_CODE_ASIL_D
#include "MemMap.h"
FUNC(uint32, COMXF_CODE) ComXf_UnPack3ByteNotAlign(
  P2CONST(uint8, AUTOMATIC, COMXF_APPL_CONST) buffer,
  P2CONST(ComXf_UnPackSigType, AUTOMATIC, COMXF_APPL_CONST) unPackSigType,
  VAR(sint8, AUTOMATIC) byteDirection)
{
  /* @Trace: SafeComXf_SUD_API_042 */	
  /* Local variable to store data element value */
  VAR(uint32, AUTOMATIC) dataElement;

  /* Local variable to calculate the posision of data in buffer */
  VAR(sint8, AUTOMATIC) bytePos;

  /* Local variable to store sign mask value */
  VAR(uint32, AUTOMATIC) sigSignMsk;

  /* Local pointer to signal data */
  P2VAR(uint8, AUTOMATIC, COMXF_APPL_DATA) dataBuffer;

  bytePos = (sint8)COMXF_HEX_00;
  dataElement = (uint32)COMXF_HEX_00;

  /* Take a pointer to signal data */
  dataBuffer = (uint8*)& dataElement;

  /* Check whether CPU is Big or Little endian */
#if (CPU_BYTE_ORDER == HIGH_WORD_FIRST)

  /* Increment signal data pointer */
  dataBuffer++;

  /* Copy data from Rte buffer */
  *dataBuffer = buffer[bytePos];

  /* Apply end mask to received signal data */
  *dataBuffer &= unPackSigType->rxEndMsk;

  /* Increment signal data pointer */
  dataBuffer++;

  /* Increment or decrement data buffer pointer as per endianness */
  bytePos += byteDirection;

  /* Copy data from Rte buffer */
  *dataBuffer = buffer[bytePos];

  /* Increment signal data pointer */
  dataBuffer++;

  /* Increment or decrement data buffer pointer as per endianness */
  bytePos += byteDirection;

  /* Copy data from Rte buffer */
  *dataBuffer = buffer[bytePos];

  /* Shift data to signal position */
  dataElement >>= unPackSigType->shiftBits;

#else

  /* Copy data from Rte buffer */
  dataBuffer[COMXF_ZEROTH_BYTE] = buffer[bytePos];

  /* Increment or decrement data buffer pointer as per endianness */
  bytePos += byteDirection;

  /* Copy data from Rte buffer */
  dataBuffer[COMXF_FIRST_BYTE] = buffer[bytePos];

  /* Increment or decrement data buffer pointer as per endianness */
  bytePos += byteDirection;

  /* Copy data from Rte buffer */
  dataBuffer[COMXF_SECOND_BYTE] = buffer[bytePos];

  /* Apply end mask to received signal data */
  dataBuffer[COMXF_SECOND_BYTE] &= unPackSigType->rxEndMsk;

  /* Shift data to signal position */
  dataElement >>= unPackSigType->shiftBits;

#endif /* End of #if (CPU_BYTE_ORDER == HIGH_WORD_FIRST) */

  /* Take signed value into dataBuff */
  sigSignMsk = unPackSigType->sigSignMsk32;

  /* Check whether signal data is signed or unsigned */
  if ((dataElement & sigSignMsk) != (uint32)COMXF_NOT_SIGNED_SIGNAL)
  {
    /* Take signed value into dataBuff */
    dataElement |= sigSignMsk;
  }

  /* Return dataElement */
  return dataElement;
}
#define COMXF_STOP_SEC_CODE_ASIL_D
#include "MemMap.h"

/*=============================================================================*
** Service Name         : ComXf_UnPack4ByteNotAlign                           **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function will unpack signal if signal is packed     **
**                        within 4 bytes.                                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : buffer, unPackSigType, byteDirection                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : uint32                                              **
**                                                                            **
** Preconditions        : ComXf_Init should be called                         **
**                                                                            **
**============================================================================*/

/* @Trace: SRS_Xfrm_00201 SafeComXf_SUD_DATATYPE_001 */

#define COMXF_START_SEC_CODE_ASIL_D
#include "MemMap.h"
FUNC(uint32, COMXF_CODE) ComXf_UnPack4ByteNotAlign(
  P2CONST(uint8, AUTOMATIC, COMXF_APPL_CONST) buffer,
  P2CONST(ComXf_UnPackSigType, AUTOMATIC, COMXF_APPL_CONST) unPackSigType,
  VAR(sint8, AUTOMATIC) byteDirection)
{
  /* @Trace: SafeComXf_SUD_API_043 */	
  /* Local variable to store data element value */
  VAR(uint32, AUTOMATIC) dataElement;

  /* Local variable to calculate the posision of data in buffer */
  VAR(sint8, AUTOMATIC) bytePos;

  /* Local variable to store sign mask value */
  VAR(uint32, AUTOMATIC) sigSignMsk;

  /* Local pointer to signal data */
  P2VAR(uint8, AUTOMATIC, COMXF_APPL_DATA) dataBuffer;

  bytePos = (sint8)COMXF_HEX_00;
  dataElement = (uint32)COMXF_HEX_00;

  /* Take a pointer to signal data */
  dataBuffer = (uint8*)& dataElement;

  /* Copy data from Rte buffer */
  dataBuffer[COMXF_ZEROTH_BYTE] = buffer[bytePos];

  /* Increment or decrement data buffer pointer as per endianness */
  bytePos += byteDirection;

  /* Copy data from Rte buffer */
  dataBuffer[COMXF_FIRST_BYTE] = buffer[bytePos];

  /* Increment or decrement data buffer pointer as per endianness */
  bytePos += byteDirection;

  /* Copy data from Rte buffer */
  dataBuffer[COMXF_SECOND_BYTE] = buffer[bytePos];

  /* Increment or decrement data buffer pointer as per endianness */
  bytePos += byteDirection;

  /* Copy data from Rte buffer */
  dataBuffer[COMXF_THIRD_BYTE] = buffer[bytePos];

#if (CPU_BYTE_ORDER == HIGH_WORD_FIRST)

  /* Apply end mask to received signal data */
  dataBuffer[COMXF_ZEROTH_BYTE] &= unPackSigType->rxEndMsk;

#else
  /* Apply end mask to received signal data */
  dataBuffer[COMXF_THIRD_BYTE] &= unPackSigType->rxEndMsk;

#endif /* End of #if (CPU_BYTE_ORDER == HIGH_WORD_FIRST) */

  /* Shift data to signal position */
  dataElement >>= unPackSigType->shiftBits;

  /* Apply end mask to received signal data */
  sigSignMsk = unPackSigType->sigSignMsk32;

  /* Check whether signal data is signed or unsigned */
  if ((dataElement & sigSignMsk) != (uint32)COMXF_NOT_SIGNED_SIGNAL)
  {
    /* Take signed value into dataBuff */
    dataElement |= sigSignMsk;
  }

  /* Return dataElement */
  return dataElement;
}
#define COMXF_STOP_SEC_CODE_ASIL_D
#include "MemMap.h"

/*=============================================================================*
** Service Name         : ComXf_UnPack5ByteNotAlign                           **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function will unpack signal if signal is packed     **
**                        within 5 bytes.                                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : unPackSigType, buffer, byteDirection                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : uint32                                              **
**                                                                            **
** Preconditions        : ComXf_Init should be called                         **
**                                                                            **
**============================================================================*/

/* @Trace: SRS_Xfrm_00201 SafeComXf_SUD_DATATYPE_001 */

#define COMXF_START_SEC_CODE_ASIL_D
#include "MemMap.h"
FUNC(uint32, COMXF_CODE) ComXf_UnPack5ByteNotAlign(
  P2CONST(uint8, AUTOMATIC, COMXF_APPL_CONST) buffer,
  P2CONST(ComXf_UnPackSigType, AUTOMATIC, COMXF_APPL_CONST) unPackSigType,
  VAR(sint8, AUTOMATIC) byteDirection)
{
  /* @Trace: SafeComXf_SUD_API_044 */	
  /* Local variable to store data element value */
  VAR(uint32, AUTOMATIC) dataElement;

  /* Local variable to calculate the posision of data in buffer */
  VAR(sint8, AUTOMATIC) bytePos;

  /* Local variable to store high byte data element value */
  VAR(uint32, AUTOMATIC) fourHighByteData;

  /* Local variable to store sign mask value */
  VAR(uint32, AUTOMATIC) sigSignMsk;

  /* Local pointer to signal data */
  P2VAR(uint8, AUTOMATIC, COMXF_APPL_DATA) dataBuffer;

  bytePos = (sint8)COMXF_HEX_00;
  dataElement = (uint32)COMXF_HEX_00;

  /* Take a pointer to signal data */
  dataBuffer = (uint8*)& dataElement;

#if (CPU_BYTE_ORDER == HIGH_WORD_FIRST)

  /* Copy high byte of signal data from Rte buffer */
  fourHighByteData = buffer[bytePos];

  /* increment or decrement data buffer pointer as per endianness */
  bytePos += byteDirection;

  /* Copy data from Rte buffer */
  dataBuffer[COMXF_ZEROTH_BYTE] = buffer[bytePos];

#else

  /* Copy data from Rte buffer */
  dataBuffer[COMXF_ZEROTH_BYTE] = buffer[bytePos];

#endif /* End of #if (CPU_BYTE_ORDER == HIGH_WORD_FIRST) */

  /* Increment or decrement data buffer pointer as per endianness */
  bytePos += byteDirection;

  /* Copy data from Rte buffer */
  dataBuffer[COMXF_FIRST_BYTE] = buffer[bytePos];

  /* Increment or decrement data buffer pointer as per endianness */
  bytePos += byteDirection;

  /* Copy data from Rte buffer */
  dataBuffer[COMXF_SECOND_BYTE] = buffer[bytePos];

  /* Increment or decrement data buffer pointer as per endianness */
  bytePos += byteDirection;

  /* Copy data from Rte buffer */
  dataBuffer[COMXF_THIRD_BYTE] = buffer[bytePos];

  /* Increment or decrement data buffer pointer as per endianness */
  bytePos += byteDirection;

#if (CPU_BYTE_ORDER == LOW_WORD_FIRST)

  /* Copy high byte of signal data */
  fourHighByteData = buffer[bytePos];

#endif/*End of #if (CPU_BYTE_ORDER == LOW_WORD_FIRST)*/

  /* Apply end mask to received signal data */
  fourHighByteData &= unPackSigType->rxEndMsk;

  /* Shift data to signal position */
  fourHighByteData <<=
    ((uint32)COMXF_SHIFT_BY_THIRTYTWO - unPackSigType->shiftBits);

  /* Shift data to signal position */
  dataElement >>= unPackSigType->shiftBits;

  /* Do ORing of high byte of signal data with remaining data */
  dataElement = dataElement | fourHighByteData;

  /* Apply end mask to received signal data */
  sigSignMsk = unPackSigType->sigSignMsk32;

  /* Check whether signal data is signed or unsigned */
  if ((dataElement & sigSignMsk) != (uint32)COMXF_NOT_SIGNED_SIGNAL)
  {
    /* Take signed value into dataBuff */
    dataElement |= sigSignMsk;
  }

  /* Return dataElement */
  return dataElement;
}
#define COMXF_STOP_SEC_CODE_ASIL_D
#include "MemMap.h"

/*=============================================================================*
** Service Name         : ComXf_UnPackArray                                   **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function will unpack signal if signal type is array **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : unPackSigType, buffer                               **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : dataElement                                         **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : ComXf_Init should be called                         **
**                                                                            **
**============================================================================*/

/* @Trace: SRS_Xfrm_00201 SafeComXf_SUD_DATATYPE_001 */

#define COMXF_START_SEC_CODE_ASIL_D
#include "MemMap.h"
FUNC(void, COMXF_CODE) ComXf_UnPackArray(
  P2CONST(uint8, AUTOMATIC, COMXF_APPL_CONST) buffer,
  P2CONST(ComXf_UnPackSigType, AUTOMATIC, COMXF_APPL_CONST) unPackSigType,
  P2VAR(uint8, AUTOMATIC, COMXF_APPL_DATA) dataElement)
{
  /* @Trace: SafeComXf_SUD_API_045 */	
  /* Local variable to store count variable of for loop */  
  VAR(uint16, AUTOMATIC) i;
  
  /* Local pointer to signal data buffer */
  P2VAR(uint8, AUTOMATIC, COMXF_APPL_DATA) sigBuffer;

  /* Take a pointer to signal data */
  sigBuffer = (uint8*)dataElement;

  /* Loop for signal size */
  for (i = 0; i < unPackSigType->noOfBytes; i++) {
    /* Copy the data from signal buffer to application buffer */
    sigBuffer[i] = buffer[i];
  }
}
#define COMXF_STOP_SEC_CODE_ASIL_D
#include "MemMap.h"

/*=============================================================================*
** Service Name         : ComXf_UnPack9ByteNotAlign                           **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function will unpack signal if signal is packed     **
**                        within 9 bytes.                                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : unPackSigType, buffer, byteDirection                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : uint64                                              **
**                                                                            **
** Preconditions        : ComXf_Init should be called                         **
**                                                                            **
**============================================================================*/

/* @Trace: SRS_Xfrm_00201 SafeComXf_SUD_DATATYPE_001 */

#define COMXF_START_SEC_CODE_ASIL_D
#include "MemMap.h"
FUNC(uint64, COMXF_CODE) ComXf_UnPack9ByteNotAlign(
  P2CONST(uint8, AUTOMATIC, COMXF_APPL_CONST) buffer,
  P2CONST(ComXf_UnPackSigType, AUTOMATIC, COMXF_APPL_CONST) unPackSigType,
  VAR(sint8, AUTOMATIC) byteDirection)
{
  /* @Trace: SafeComXf_SUD_API_046 */	
  /* Local variable to to check against the number of bytes */
  VAR(uint8, AUTOMATIC) noOfBytes;

  /* Local variable to calculate the posision of data in buffer */
  VAR(sint8, AUTOMATIC) bytePos;

  /* Local variable to store data element value */
  VAR(uint64, AUTOMATIC) dataElement;

  /* Local variable to store high byte data element value */
  VAR(uint64, AUTOMATIC) eightHighByteData;

  /* Local variable to store sign mask value */
  VAR(uint64, AUTOMATIC) sigSignMsk;

  /* Local pointer to signal data */
  P2VAR(uint8, AUTOMATIC, COMXF_APPL_DATA) dataBuffer;

  bytePos = (sint8)COMXF_HEX_00;
  noOfBytes = (uint8)COMXF_HEX_00;

  dataElement = (uint64)COMXF_HEX_00;

  /* Take a pointer to signal data */
  dataBuffer = (uint8*)& dataElement;

#if (CPU_BYTE_ORDER == HIGH_WORD_FIRST)

  /* Copy high byte of signal data from Rte buffer */
  dataElement = buffer[bytePos];

  /* Increment or decrement data buffer pointer as per endianness */
  bytePos += byteDirection;

  /* Copy data from Rte buffer */
  dataBuffer[COMXF_ZEROTH_BYTE] = buffer[bytePos];

#else

  /* Copy data from Rte buffer */
  dataBuffer[COMXF_ZEROTH_BYTE] = buffer[bytePos];

#endif /* End of #if (CPU_BYTE_ORDER == HIGH_WORD_FIRST) */

  /* Increment or decrement data buffer pointer as per endianness */
  bytePos += byteDirection;

  do
  {
    /* Increment the local variable */
    noOfBytes++;

    /* Copy data from input buffer */
    dataBuffer[noOfBytes] = buffer[bytePos];

    /* Increment or decrement data buffer pointer as per endianness */
    bytePos += byteDirection;

  } while (noOfBytes <
    (unPackSigType->noOfBytes - (uint8)COMXF_TWO_BYTES));

#if (CPU_BYTE_ORDER == LOW_WORD_FIRST)

  /* Copy high byte of signal data */
  eightHighByteData = buffer[bytePos];

#endif /* End of #if (CPU_BYTE_ORDER == LOW_WORD_FIRST)*/

  /* Apply end mask to received signal data */
  eightHighByteData &= unPackSigType->rxEndMsk;

  /* Shift data to signal position */
  eightHighByteData <<=
    (((unPackSigType->noOfBytes - (uint64)COMXF_FIRST_BYTE)*
      (uint64)COMXF_SHIFT_BY_EIGHT) - unPackSigType->shiftBits);

  /* Shift data to signal position */
  dataElement >>= unPackSigType->shiftBits;

  /* Do ORing of high byte of signal data with remaining data */
  dataElement = dataElement | eightHighByteData;

  /* Apply end mask to received signal data */
  sigSignMsk = unPackSigType->sigSignMsk64;

  /* Check whether signal data is signed or unsigned */
  if ((dataElement & sigSignMsk) != (uint64)COMXF_NOT_SIGNED_SIGNAL)
  {
    /* Take signed value into dataBuff */
    dataElement |= sigSignMsk;
  }

  /* Return dataElement */
  return dataElement;
}
#define COMXF_STOP_SEC_CODE_ASIL_D
#include "MemMap.h"

/*=============================================================================*
** Service Name         : ComXf_UnPack5678ByteNotAlign                        **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function will unpack signal if signal is packed     **
**                        within 6,7 or 8 bytes.                              **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : buffer, unPackSigType, byteDirection                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : uint64                                              **
**                                                                            **
** Preconditions        : ComXf_Init should be called                         **
**                                                                            **
**============================================================================*/

/* @Trace: SRS_Xfrm_00201 SafeComXf_SUD_DATATYPE_001 */

#define COMXF_START_SEC_CODE_ASIL_D
#include "MemMap.h"
FUNC(uint64, COMXF_CODE) ComXf_UnPack5678ByteNotAlign(
  P2CONST(uint8, AUTOMATIC, COMXF_APPL_CONST) buffer,
  P2CONST(ComXf_UnPackSigType, AUTOMATIC, COMXF_APPL_CONST) unPackSigType,
  VAR(sint8, AUTOMATIC) byteDirection)
{
  /* @Trace: SafeComXf_SUD_API_047 */	
  /* Local variable to to check against the number of bytes */
  VAR(uint8, AUTOMATIC) noOfBytes;

  /* Local variable to calculate the posision of data in buffer */
  VAR(sint8, AUTOMATIC) bytePos;

  /* Local variable to store data element value */
  VAR(uint64, AUTOMATIC) dataElement;

  /* Local variable to store sign mask value */
  VAR(uint64, AUTOMATIC) sigSignMsk;

  /* Local pointer to signal data */
  P2VAR(uint8, AUTOMATIC, COMXF_APPL_DATA) dataBuffer;

  noOfBytes = (uint8)COMXF_HEX_00;
  dataElement = (uint64)COMXF_HEX_00;
  bytePos = (sint8)COMXF_HEX_00;

  /* Take a pointer to signal data */
  dataBuffer = (uint8*)& dataElement;

  do
  {
    /* Copy data from Rte buffer */
    dataBuffer[noOfBytes] = buffer[bytePos];

    /* increment or decrement data buffer pointer as per endianness */
    bytePos += byteDirection;

    /* Increment the local variable */
    noOfBytes++;

  } while (noOfBytes < unPackSigType->noOfBytes);

#if (CPU_BYTE_ORDER == HIGH_WORD_FIRST)

  /* Apply end mask to received signal data */
  dataBuffer[unPackSigType->noOfBytes - noOfBytes]
    &= unPackSigType->rxEndMsk;

#else
  /* Apply end mask to received signal data */
  dataBuffer[noOfBytes - (uint8)COMXF_FIRST_BYTE]
    &= unPackSigType->rxEndMsk;

#endif /* End of #if (CPU_BYTE_ORDER == HIGH_WORD_FIRST) */

  /* Shift data to signal position */
  dataElement >>= unPackSigType->shiftBits;

  /* Apply end mask to received signal data */
  sigSignMsk = unPackSigType->sigSignMsk64;

  /* Check whether signal data is signed or unsigned */
  if ((dataElement & sigSignMsk) != (uint64)COMXF_NOT_SIGNED_SIGNAL)
  {
    /* Take signed value into dataBuff */
    dataElement |= sigSignMsk;
  }

  /* Return dataElement */
  return dataElement;
}
#define COMXF_STOP_SEC_CODE_ASIL_D
#include "MemMap.h"

/*=============================================================================*
** Service Name         : ComXf_UnPackFloat32ByteNotAlign                     **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function will unpack float32 byte not aligned       **
**                        type signal                                         **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : unPackSigType, buffer, byteDirection                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : float32                                             **
**                                                                            **
** Preconditions        : ComXf_Init should be called                         **
**                                                                            **
**============================================================================*/

/* @Trace: SRS_Xfrm_00201 SafeComXf_SUD_DATATYPE_001 */

#define COMXF_START_SEC_CODE_ASIL_D
#include "MemMap.h"
FUNC(float32, COMXF_CODE) ComXf_UnPackFloat32ByteNotAlign(
  P2CONST(uint8, AUTOMATIC, COMXF_APPL_CONST) buffer,
  P2CONST(ComXf_UnPackSigType, AUTOMATIC, COMXF_APPL_CONST) unPackSigType,
  VAR(sint8, AUTOMATIC) byteDirection)
{
  /* @Trace: SafeComXf_SUD_API_048 */
  /* Local variable to store data */
  VAR(ComXf_Float32DataType, AUTOMATIC) dataElement;

  /* Get the unpacked data */
  dataElement.u32 =
    ComXf_UnPack5ByteNotAlign(buffer,
      unPackSigType, byteDirection);

  /* Return signal data */
  return (dataElement.f32);

}
#define COMXF_STOP_SEC_CODE_ASIL_D
#include "MemMap.h"

/*=============================================================================*
** Service Name         : ComXf_UnPackFloat64ByteNotAlign                     **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function will unpack float64 byte not aligned       **
**                        type signal                                         **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : unPackSigType, buffer, byteDirection                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : float64                                             **
**                                                                            **
** Preconditions        : ComXf_Init should be called                         **
**                                                                            **
**============================================================================*/

/* @Trace: SRS_Xfrm_00201 SafeComXf_SUD_DATATYPE_001 */

#define COMXF_START_SEC_CODE_ASIL_D
#include "MemMap.h"
FUNC(float64, COMXF_CODE) ComXf_UnPackFloat64ByteNotAlign(
  P2CONST(uint8, AUTOMATIC, COMXF_APPL_CONST) buffer,
  P2CONST(ComXf_UnPackSigType, AUTOMATIC, COMXF_APPL_CONST) unPackSigType,
  VAR(sint8, AUTOMATIC) byteDirection)
{
  /* @Trace: SafeComXf_SUD_API_049 */
  /* Local variable to store data */
  VAR(ComXf_Float64DataType, AUTOMATIC) dataElement;

  /* Get the unpacked data */
  dataElement.u64 =
    ComXf_UnPack9ByteNotAlign(buffer,
      unPackSigType, byteDirection);

  /* Return signal data */
  return (dataElement.f64);
}
#define COMXF_STOP_SEC_CODE_ASIL_D
#include "MemMap.h"

/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA RULE CHECKER)                   **
*******************************************************************************/
/* polyspace-end MISRA2012:20.1 */
/* polyspace-end MISRA2012:11.3*/
/* polyspace-end MISRA2012:D4.14*/
/*******************************************************************************
*                       End of File                                            *
*******************************************************************************/
