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
**  SRC-MODULE: Crc_16ARC.c                                                   **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Crc Library Module                                    **
**                                                                            **
**  PURPOSE   : Implementation of 16-bit CRC functions with polynomial 0x8005 **
**              for Crc Library Module                                        **
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
** 1.0.2     24-Dec-2021   JHLim            Redmine #33330                    **
** 1.0.2     06-Jan-2022   JHLim            Redmine #21418                    **
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
/* @Trace: SafeCRC_SUD_FILE_001 */
#include "Crc_IntFunc.h"             /* Crc Internal Function Header file */

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
/* @Trace: SafeCRC_SUD_MACRO_001 */
#if(CRC_16_ARC_MODE == CRC_16_ARC_TABLE)
#define CRC_START_SEC_CONST_ASIL_D_16
#include "MemMap.h"

/* 
 * Global look up table (reflected) for 16 bit 0x8005 polynomial table based 
 * CRC calculation 
 */
/* Explicit typecasting not added as it is not required */
/* polyspace-begin MISRA2012:8.9 VARIABLE:ALL [Justified:Low] "Avoid re-create large object each time function is called" */
static CONST(uint16, CRC_CONST) Crc_Table16ARC[CRC_COUNT256] =
{
  0x0000U, 0xC0C1U, 0xC181U, 0x0140U, 0xC301U, 0x03C0U, 0x0280U, 0xC241U, 
  0xC601U, 0x06C0U, 0x0780U, 0xC741U, 0x0500U, 0xC5C1U, 0xC481U, 0x0440U, 
  0xCC01U, 0x0CC0U, 0x0D80U, 0xCD41U, 0x0F00U, 0xCFC1U, 0xCE81U, 0x0E40U, 
  0x0A00U, 0xCAC1U, 0xCB81U, 0x0B40U, 0xC901U, 0x09C0U, 0x0880U, 0xC841U, 
  0xD801U, 0x18C0U, 0x1980U, 0xD941U, 0x1B00U, 0xDBC1U, 0xDA81U, 0x1A40U,
  0x1E00U, 0xDEC1U, 0xDF81U, 0x1F40U, 0xDD01U, 0x1DC0U, 0x1C80U, 0xDC41U, 
  0x1400U, 0xD4C1U, 0xD581U, 0x1540U, 0xD701U, 0x17C0U, 0x1680U, 0xD641U, 
  0xD201U, 0x12C0U, 0x1380U, 0xD341U, 0x1100U, 0xD1C1U, 0xD081U, 0x1040U, 
  0xF001U, 0x30C0U, 0x3180U, 0xF141U, 0x3300U, 0xF3C1U, 0xF281U, 0x3240U, 
  0x3600U, 0xF6C1U, 0xF781U, 0x3740U, 0xF501U, 0x35C0U, 0x3480U, 0xF441U,
  0x3C00U, 0xFCC1U, 0xFD81U, 0x3D40U, 0xFF01U, 0x3FC0U, 0x3E80U, 0xFE41U, 
  0xFA01U, 0x3AC0U, 0x3B80U, 0xFB41U, 0x3900U, 0xF9C1U, 0xF881U, 0x3840U, 
  0x2800U, 0xE8C1U, 0xE981U, 0x2940U, 0xEB01U, 0x2BC0U, 0x2A80U, 0xEA41U, 
  0xEE01U, 0x2EC0U, 0x2F80U, 0xEF41U, 0x2D00U, 0xEDC1U, 0xEC81U, 0x2C40U, 
  0xE401U, 0x24C0U, 0x2580U, 0xE541U, 0x2700U, 0xE7C1U, 0xE681U, 0x2640U,
  0x2200U, 0xE2C1U, 0xE381U, 0x2340U, 0xE101U, 0x21C0U, 0x2080U, 0xE041U, 
  0xA001U, 0x60C0U, 0x6180U, 0xA141U, 0x6300U, 0xA3C1U, 0xA281U, 0x6240U, 
  0x6600U, 0xA6C1U, 0xA781U, 0x6740U, 0xA501U, 0x65C0U, 0x6480U, 0xA441U, 
  0x6C00U, 0xACC1U, 0xAD81U, 0x6D40U, 0xAF01U, 0x6FC0U, 0x6E80U, 0xAE41U, 
  0xAA01U, 0x6AC0U, 0x6B80U, 0xAB41U, 0x6900U, 0xA9C1U, 0xA881U, 0x6840U,
  0x7800U, 0xB8C1U, 0xB981U, 0x7940U, 0xBB01U, 0x7BC0U, 0x7A80U, 0xBA41U, 
  0xBE01U, 0x7EC0U, 0x7F80U, 0xBF41U, 0x7D00U, 0xBDC1U, 0xBC81U, 0x7C40U, 
  0xB401U, 0x74C0U, 0x7580U, 0xB541U, 0x7700U, 0xB7C1U, 0xB681U, 0x7640U, 
  0x7200U, 0xB2C1U, 0xB381U, 0x7340U, 0xB101U, 0x71C0U, 0x7080U, 0xB041U, 
  0x5000U, 0x90C1U, 0x9181U, 0x5140U, 0x9301U, 0x53C0U, 0x5280U, 0x9241U,
  0x9601U, 0x56C0U, 0x5780U, 0x9741U, 0x5500U, 0x95C1U, 0x9481U, 0x5440U, 
  0x9C01U, 0x5CC0U, 0x5D80U, 0x9D41U, 0x5F00U, 0x9FC1U, 0x9E81U, 0x5E40U, 
  0x5A00U, 0x9AC1U, 0x9B81U, 0x5B40U, 0x9901U, 0x59C0U, 0x5880U, 0x9841U, 
  0x8801U, 0x48C0U, 0x4980U, 0x8941U, 0x4B00U, 0x8BC1U, 0x8A81U, 0x4A40U, 
  0x4E00U, 0x8EC1U, 0x8F81U, 0x4F40U, 0x8D01U, 0x4DC0U, 0x4C80U, 0x8C41U,
  0x4400U, 0x84C1U, 0x8581U, 0x4540U, 0x8701U, 0x47C0U, 0x4680U, 0x8641U, 
  0x8201U, 0x42C0U, 0x4380U, 0x8341U, 0x4100U, 0x81C1U, 0x8081U, 0x4040U
};
/* polyspace-end MISRA2012:8.9 VARIABLE:ALL [Justified:Low] "Avoid re-create large object each time function is called" */
#define CRC_STOP_SEC_CONST_ASIL_D_16
#include "MemMap.h" 
#endif

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define CRC_START_SEC_CODE_ASIL_D
#include "MemMap.h"
/*******************************************************************************
** Function Name        : Crc_CalculateCRC16ARC                               **
**                                                                            **
** Service ID           : CRC_CALCULATECRC16ARC_SID: 0x08                     **
**                                                                            **
** Description          : This function returns the 16 bit checksum calculated**
**                        using polynomial 0x8005 by runtime and table based  **
**                        method.                                             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : Crc_DataPtr     : Pointer to start address of       **
**                                          data block to be calculated       **
**                        Crc_Length      : Length of data block to be        **
**                                          calculated in bytes               **
**                        Crc_StartValue16: Start value when the algorithm    **
**                                          starts                            **
**                        Crc_IsFirstCall : TRUE: First call in a sequence or **
**                                          individual CRC calculation; start **
**                                          from initial value, ignore        **
**                                          Crc_StartValue16.                 **
**                                          FALSE: Subsequent call in a call  **
**                                          sequence; Crc_StartValue16 is     **
**                                          interpreted to be the return value**
**                                          of the previous function call.    **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : 16 bit result of CRC calculation                    **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : Crc_Table16ARC[]           **
**                        Function(s) invoked    : Crc_Reflect                **
*******************************************************************************/

/* @Trace: SRS_LIBS_08518 SRS_LIBS_08525 SRS_LIBS_08526 */
/* @Trace: SafeCRC_SUD_MACRO_001 */
#if((CRC_16_ARC_MODE == CRC_16_ARC_RUNTIME) || \
  (CRC_16_ARC_MODE == CRC_16_ARC_TABLE))
  FUNC(uint16, CRC_CODE) Crc_CalculateCRC16ARC
  (P2CONST(uint8, CRC_CONST, CRC_APPL_CONST)Crc_DataPtr, uint32 Crc_Length,
  uint16 Crc_StartValue16, boolean Crc_IsFirstCall)
{
  /* Local variable to hold CRC result calculation */
  VAR(uint16, AUTOMATIC) resultCrc;
  /* Local variable to hold address that pointed to input data */
  VAR(uint32, AUTOMATIC) dataIndex;
  /* @Trace: SafeCrc_SUD_API_021 */
  /* Initial value for CRC result calculation. It be returned when pointer to 
  start address of data block is null */
  resultCrc = CRC_ZERO;
  /* Check if pointer to start address of data block is null */
  if (NULL_PTR != Crc_DataPtr)
  {
    /* @Trace: SafeCrc_SUD_API_022 */
    /* Check if it is the first function call */
    if (CRC_TRUE == Crc_IsFirstCall)
    {
      /* Initial value for CRC result calculation */
      resultCrc = CRC_INITIAL_VALUE16ARC;
    } 
    else 
    {
      /* Check if CRC16ARC calculation method is runtime mode */
      /* @Trace: SafeCRC_SUD_MACRO_001 */
      #if(CRC_16_ARC_MODE == CRC_16_ARC_RUNTIME)
        resultCrc = (uint16)Crc_Reflect(Crc_StartValue16, CRC_SIXTEEN);
      #else
        resultCrc = Crc_StartValue16;
      #endif
    }
    /* Initial address that pointed to input data */
    dataIndex = CRC_ZERO;
    /* @Trace: SafeCrc_SUD_API_023 */
    /* Loop for each byte data from input data */
    while (dataIndex < Crc_Length) /* polyspace MISRA2012:D4.14 [Justified:Low] "The value of this variable must be validated by caller" */
    {
      /* Local variable to hold one byte data from input data */
      VAR(uint8, AUTOMATIC) byteData;
      /* Copy the data byte into local variable */
      /* polyspace-begin MISRA2012:D4.14 MISRA2012:D4.1 MISRA2012:18.1 RTE:IDP [Justified:Low] "Array and length shall be validated by the caller" */
      byteData = Crc_DataPtr[dataIndex];
      /* polyspace-end MISRA2012:D4.14 MISRA2012:D4.1 MISRA2012:18.1 RTE:IDP [Justified:Low] "Array and length shall be validated by the caller" */
      /* Check if CRC16ARC calculation method is runtime mode */
      /* @Trace: SafeCRC_SUD_MACRO_001 */
      #if(CRC_16_ARC_MODE == CRC_16_ARC_RUNTIME)
        /* @Trace: SafeCrc_SUD_API_025 */
        /* Local variable to hold loop index of each bit in byte data */
        VAR(uint8, AUTOMATIC) loopIndex;
        /* Local variable to hold reflection data result */
        VAR(uint16, AUTOMATIC) reflectData;
        /* Local variable to hold Crc temp value */
        /* Reflect data before performing XOR calculation */
        reflectData =  (uint16)Crc_Reflect(byteData, CRC_EIGHT);
        /* Perform XOR of data byte with CRC result */
        resultCrc = resultCrc ^ (reflectData << CRC_EIGHT);
        /* Initialize loop index */
        loopIndex = CRC_EIGHT;
        /* Loop for 8 bits */
        while (CRC_ZERO < loopIndex)
        {
          /* Check if MSB of byte data is set to one */
          if (CRC_MSB16 == (resultCrc & CRC_MSB16))
          {
            resultCrc = (((resultCrc << CRC_ONE) & (uint16)CRC_MASK_TWO_BYTE)^ CRC_POLY16ARC);
          }
          else
          {
            resultCrc = resultCrc << CRC_ONE;
          }
          /* Decrement the loop index */
          loopIndex--;
        }
      #else
        /* @Trace: SafeCrc_SUD_API_024 */
        /* Local variable to hold address related to data byte in Table */
        VAR(uint8, AUTOMATIC) tableDataIndex;
        /* Set value of address related to data byte to local variable */
        tableDataIndex = (uint8)(byteData ^ (resultCrc & CRC_BYTE_MASK));
        /* Fetch value of CRC from the Table */
        resultCrc = Crc_Table16ARC[tableDataIndex] ^ (resultCrc >> CRC_EIGHT);
      #endif
      /* Point to next data byte in input data */
      dataIndex++;
    }
    /* @Trace: SafeCrc_SUD_API_026 */
    /* Check if CRC16ARC calculation method is runtime mode */
    /* @Trace: SafeCRC_SUD_MACRO_001 */
    #if(CRC_16_ARC_MODE == CRC_16_ARC_RUNTIME)
      /* Reflect final CRC result */
      resultCrc = (uint16)Crc_Reflect(resultCrc, CRC_SIXTEEN);
    #endif
    /* Do not reflect final CRC in table based calculation mode*/
  }
  /* Return the CRC result */
  return resultCrc;
}
#define CRC_STOP_SEC_CODE_ASIL_D
#include "MemMap.h"
#endif 

/*******************************************************************************
**                          End of File                                       **
*******************************************************************************/
