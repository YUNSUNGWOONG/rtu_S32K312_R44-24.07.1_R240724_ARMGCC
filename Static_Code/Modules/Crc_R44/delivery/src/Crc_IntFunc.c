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
**  SRC-MODULE: Crc_IntFunc.c                                                 **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Crc Library Module                                    **
**                                                                            **
**  PURPOSE   : Implementation of reflection data in CRC functions for Crc    **
**              Library Module                                                **     
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By               Description                       **
********************************************************************************
** 0.0.1     05-Sep-2019   TuanVA17         Initial Version                   **
** 0.0.2     03-Mar-2020   TienNV21         Update traceability apply new     **
**                                          V-Cycle                           **
** 0.0.3     07-Apr-2020   TienNV21         Update code annotation            **
** 1.0.2.2   29-Jun-2022   SH Park          Improvement mobilegence           **
**                                            Classic <CP44-224>              **
** 1.0.3     12-Aug-2022   SH Park          Improvement mobilegence           **
**                                            Classic <CP44-81>               **
** 1.0.3.1   18-Nov-2022   ThuanLD5         Improvement mobilegence           **
**                                            Classic <CP44-361>              **
**                                                    <CP44-362>              **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Crc_IntFunc.h"             /* Crc Internal Function Header file */

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

/*******************************************************************************
** Function Name        : Crc_Reflect                                         **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function returns the symmetric reflection      **
**                        of input.                                           **
**                                                                            **
** Re-entrancy          : NA                                                  **
**                                                                            **
** Input Parameters     : data       : Input data to be reflected             **
**                        dataLength : Length of data to be reflected         **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : reflectData   : Reflected data                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : None                       **
*******************************************************************************/

/* @Trace: SRS_LIBS_08518 SRS_LIBS_08525 */
/* @Trace: SafeCRC_SUD_MACRO_001 */
#if((CRC_16_ARC_MODE == CRC_16_ARC_RUNTIME) \
  || (CRC_32_MODE == CRC_32_RUNTIME)        \
  || (CRC_32P4_MODE == CRC_32P4_RUNTIME)    \
  || (CRC_64_MODE == CRC_64_RUNTIME))
#define CRC_START_SEC_CODE_ASIL_D
#include "MemMap.h"
FUNC(uint64, CRC_CODE) Crc_Reflect
  (uint64 data, CONST(uint8, CRC_CONST) dataLength)
{
  /* Value of temp data from input data */
  VAR(uint64, AUTOMATIC) tempData;
  /* Value of reflection */
  VAR(uint64, AUTOMATIC) reflectData;
  /* Value of most significant bit */
  VAR(uint64, AUTOMATIC) msBitValue;
  /* Count of no. of bits */
  VAR(uint64, AUTOMATIC) bitCount;
  /* @Trace: SafeCrc_SUD_API_046 */
  /* Initial value of temp data */
  tempData = data;
  /* Initial value of reflection */
  reflectData = CRC_ZERO;

  /* @Trace: SafeCrc_SUD_API_045 */
  if(CRC_EIGHT == dataLength)
  {
    /* Set MS bit for one byte data  */
    msBitValue = CRC_MSB8;
  }
  else if(CRC_SIXTEEN == dataLength)
  {
    /* Set MS bit for two bytes data */
    msBitValue = CRC_MSB16;
  } 
  else if(CRC_THIRTYTWO == dataLength)
  {
    /* Set MS bit for four bytes data */
    msBitValue = CRC_MSB32;
  }
  else 
  {
    /* Set MS bit for 8 bytes data */
    msBitValue = CRC_MSB64;
  }

  /* @Trace: SafeCrc_SUD_API_047 */
  /* Start of count */
  bitCount = CRC_ZERO;
  /* Loop for each bit of input data */
  while(bitCount < dataLength) /* polyspace MISRA2012:D4.14 "The value of this variable must be validated by caller" */
  {
    /* Check if the LSB of data is set */
    if((uint64)CRC_TRUE == (tempData & CRC_ONE))
    {
      /* Take mirror image of nth bit at bit position (dataLength-n) */
      reflectData = reflectData | msBitValue;
    }
    
    /* Right shift msBitValue by one bit */
    msBitValue = msBitValue >> CRC_ONE;
    /* Right shift tempData by one bit */
    tempData = tempData >> CRC_ONE;
    /* Increment bit count */
    bitCount++;
  }
  /* Return the reflected data */
  return (reflectData);
}
#define CRC_STOP_SEC_CODE_ASIL_D
#include "MemMap.h"
#endif /* #if((CRC_16_ARC_MODE == CRC_16_ARC_RUNTIME) \
         ||(CRC_32_MODE == CRC_32_RUNTIME)            \
         ||(CRC_32P4_MODE == CRC_32P4_RUNTIME)        \
         ||(CRC_64_MODE == CRC_64_RUNTIME)) */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
