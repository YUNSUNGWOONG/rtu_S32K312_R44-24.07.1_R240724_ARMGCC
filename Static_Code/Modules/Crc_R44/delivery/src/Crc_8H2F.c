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
**  SRC-MODULE: Crc_8H2F.c                                                    **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Crc Library Module                                    **
**                                                                            **
**  PURPOSE   : Implementation of 8-bit CRC functions with polynomial 0x2F    **
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
#include "Crc.h"                     /* Crc Header file */

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
/* @Trace: SafeCRC_SUD_MACRO_001 */
#if(CRC_8H2F_MODE == CRC_8H2F_TABLE)
#define CRC_START_SEC_CONST_ASIL_D_8
#include "MemMap.h"

/* Global look up table for 8 bit 0x2F polynomial table based CRC calculation */
/* Explicit typecasting not added as it is not required */
/* polyspace-begin MISRA2012:8.9 VARIABLE:ALL [Justified:Low] "Avoid re-create large object each time function is called" */
static CONST(uint8, CRC_CONST) Crc_Table8H2F[CRC_COUNT256] =
{
  0x00U, 0x2FU, 0x5EU, 0x71U, 0xBCU, 0x93U, 0xE2U, 0xCDU, 0x57U, 0x78U, 0x09U, 
  0x26U, 0xEBU, 0xC4U, 0xB5U, 0x9AU, 0xAEU, 0x81U, 0xF0U, 0xDFU, 0x12U, 0x3DU, 
  0x4CU, 0x63U, 0xF9U, 0xD6U, 0xA7U, 0x88U, 0x45U, 0x6AU, 0x1BU, 0x34U, 0x73U, 
  0x5CU, 0x2DU, 0x02U, 0xCFU, 0xE0U, 0x91U, 0xBEU, 0x24U, 0x0BU, 0x7AU, 0x55U, 
  0x98U, 0xB7U, 0xC6U, 0xE9U, 0xDDU, 0xF2U, 0x83U, 0xACU, 0x61U, 0x4EU, 0x3FU, 
  0x10U, 0x8AU, 0xA5U, 0xD4U, 0xFBU, 0x36U, 0x19U, 0x68U, 0x47U, 0xE6U, 0xC9U, 
  0xB8U, 0x97U, 0x5AU, 0x75U, 0x04U, 0x2BU, 0xB1U, 0x9EU, 0xEFU, 0xC0U, 0x0DU, 
  0x22U, 0x53U, 0x7CU, 0x48U, 0x67U, 0x16U, 0x39U, 0xF4U, 0xDBU, 0xAAU, 0x85U, 
  0x1FU, 0x30U, 0x41U, 0x6EU, 0xA3U, 0x8CU, 0xFDU, 0xD2U, 0x95U, 0xBAU, 0xCBU, 
  0xE4U, 0x29U, 0x06U, 0x77U, 0x58U, 0xC2U, 0xEDU, 0x9CU, 0xB3U, 0x7EU, 0x51U, 
  0x20U, 0x0FU, 0x3BU, 0x14U, 0x65U, 0x4AU, 0x87U, 0xA8U, 0xD9U, 0xF6U, 0x6CU, 
  0x43U, 0x32U, 0x1DU, 0xD0U, 0xFFU, 0x8EU, 0xA1U, 0xE3U, 0xCCU, 0xBDU, 0x92U, 
  0x5FU, 0x70U, 0x01U, 0x2EU, 0xB4U, 0x9BU, 0xEAU, 0xC5U, 0x08U, 0x27U, 0x56U,
  0x79U, 0x4DU, 0x62U, 0x13U, 0x3CU, 0xF1U, 0xDEU, 0xAFU, 0x80U, 0x1AU, 0x35U, 
  0x44U, 0x6BU, 0xA6U, 0x89U, 0xF8U, 0xD7U, 0x90U, 0xBFU, 0xCEU, 0xE1U, 0x2CU, 
  0x03U, 0x72U, 0x5DU, 0xC7U, 0xE8U, 0x99U, 0xB6U, 0x7BU, 0x54U, 0x25U, 0x0AU, 
  0x3EU, 0x11U, 0x60U, 0x4FU, 0x82U, 0xADU, 0xDCU, 0xF3U, 0x69U, 0x46U, 0x37U, 
  0x18U, 0xD5U, 0xFAU, 0x8BU, 0xA4U, 0x05U, 0x2AU, 0x5BU, 0x74U, 0xB9U, 0x96U, 
  0xE7U, 0xC8U, 0x52U, 0x7DU, 0x0CU, 0x23U, 0xEEU, 0xC1U, 0xB0U, 0x9FU, 0xABU, 
  0x84U, 0xF5U, 0xDAU, 0x17U, 0x38U, 0x49U, 0x66U, 0xFCU, 0xD3U, 0xA2U, 0x8DU, 
  0x40U, 0x6FU, 0x1EU, 0x31U, 0x76U, 0x59U, 0x28U, 0x07U, 0xCAU, 0xE5U, 0x94U, 
  0xBBU, 0x21U, 0x0EU, 0x7FU, 0x50U, 0x9DU, 0xB2U, 0xC3U, 0xECU, 0xD8U, 0xF7U, 
  0x86U, 0xA9U, 0x64U, 0x4BU, 0x3AU, 0x15U, 0x8FU, 0xA0U, 0xD1U, 0xFEU, 0x33U, 
  0x1CU, 0x6DU, 0x42U
};
/* polyspace-end MISRA2012:8.9 VARIABLE:ALL [Justified:Low] "Avoid re-create large object each time function is called" */
#define CRC_STOP_SEC_CONST_ASIL_D_8
#include "MemMap.h" 
#endif

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define CRC_START_SEC_CODE_ASIL_D
#include "MemMap.h"
/*******************************************************************************
** Function Name        : Crc_CalculateCRC8H2F                                **
**                                                                            **
** Service ID           : CRC_CALCULATECRC8H2F_SID: 0x05                      **
**                                                                            **
** Description          : This function returns the 8 bit checksum calculated **
**                        using polynomial 0x2F by runtime and table method.  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : Crc_DataPtr       : Pointer to start address of     **
**                                            data block to be calculated     **
**                        Crc_Length        : Length of data block to be      **
**                                            calculated in bytes             **
**                        Crc_StartValue8H2F: Start value when the algorithm  **
**                                            starts                          **
**                        Crc_IsFirstCall   : TRUE: First call in a sequence  **
**                                            or individual CRC calculation;  **
**                                            start from initial value, ignore**
**                                            Crc_StartValue8H2F.             **
**                                            FALSE: Subsequent call in a call**
**                                            sequence; Crc_StartValue8H2F is **
**                                            interpreted to be the return    **
**                                            value of the previous function  **
**                                            call.                           **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : 8 bit result of CRC for polynomial calculation      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : Crc_Table8H2F[]            **
**                        Function(s) invoked    : None                       **
*******************************************************************************/

/* @Trace: SRS_LIBS_08518 SRS_LIBS_08525 SRS_LIBS_08526 */
/* @Trace: SafeCRC_SUD_MACRO_001 */
#if((CRC_8H2F_MODE == CRC_8H2F_RUNTIME) || (CRC_8H2F_MODE == CRC_8H2F_TABLE))
FUNC(uint8, CRC_CODE) Crc_CalculateCRC8H2F
  (P2CONST(uint8, CRC_CONST, CRC_APPL_CONST)Crc_DataPtr, uint32 Crc_Length,
  uint8 Crc_StartValue8H2F, boolean Crc_IsFirstCall)
{
  /* Local variable to hold CRC result calculation */
  VAR(uint8, AUTOMATIC) resultCrc;
  /* Local variable to hold address that pointed to input data */
  VAR(uint32, AUTOMATIC) dataIndex;
  /* @Trace: SafeCrc_SUD_API_009 */
  /* Initial value for CRC result calculation. It be returned when pointer to 
  start address of data block is null */
  resultCrc = CRC_ZERO;
  /* Check if pointer to start address of data block is null */
  if (NULL_PTR != Crc_DataPtr)
  {
    /* @Trace: SafeCrc_SUD_API_010 */
    /* Check if it is the first function call */
    if (CRC_TRUE == Crc_IsFirstCall)
    {
      /* Initial value for CRC result calculation */
      resultCrc = CRC_INITIAL_VALUE8H2F;
    }
    else
    {
      /* Initialize CRC result  with previous result */
      resultCrc = CRC_XOR_OUT8H2F ^ Crc_StartValue8H2F;
    }
    /* Initial address that pointed to input data */
    dataIndex = CRC_ZERO;

    /* @Trace: SafeCrc_SUD_API_011 */
    /* Loop for each byte data from input data */
    /* polyspace-begin CERT-C:INT31-C [Justified:Low] "The value of this variable must be validated by caller" */
    /* polyspace +1 DEFECT:TAINTED_SIGN_CHANGE [Not a defect:Justified] "The value of this variable must be validated by caller" */
    while (dataIndex < Crc_Length) /* polyspace MISRA2012:D4.14 [Justified:Low] "The value of this variable must be validated by caller" */
    {
      /* Local variable to hold one byte data from input data */
      VAR(uint8, AUTOMATIC) byteData;
      /* Copy the data byte into local variable */
      /* polyspace-begin MISRA2012:D4.14 MISRA2012:D4.1 MISRA2012:18.1 RTE:IDP [Justified:Low] "Array and length shall be validated by the caller" */
      byteData = Crc_DataPtr[dataIndex]; 
      /* polyspace-end MISRA2012:D4.14 MISRA2012:D4.1 MISRA2012:18.1 RTE:IDP [Justified:Low] "Array and length shall be validated by the caller" */
      /* Perform XOR of data byte with CRC result */
      resultCrc = resultCrc ^ byteData;
      /* Check if CRC8H2F calculation method is runtime mode */
      /* @Trace: SafeCRC_SUD_MACRO_001 */
      #if(CRC_8H2F_MODE == CRC_8H2F_RUNTIME)
        /* @Trace: SafeCrc_SUD_API_013 */
        /* Local variable to hold loop index of each bit in byte data */
        VAR(uint8, AUTOMATIC) loopIndex;
        /* Initialize loop index */
        loopIndex = CRC_EIGHT;
        /* Loop for 8 bits */
        while (CRC_ZERO < loopIndex)
        {
          /* Check if MSB of byte data is set to one */
          if (CRC_MSB8 == (resultCrc & CRC_MSB8))
          {
            resultCrc = (resultCrc << CRC_ONE) ^ CRC_POLY8H2F;
          }
          else
          {
            resultCrc = resultCrc << CRC_ONE;
          }
          /* Decrement the loop index */
          loopIndex--;
        }
      #else
        /* @Trace: SafeCrc_SUD_API_012 */
        /* Fetch value of CRC from the Table */
        resultCrc = Crc_Table8H2F[resultCrc];
      #endif
      /* Point to next data byte in input data */
      dataIndex++;
    }
    /* polyspace-end CERT-C:INT31-C [Justified:Low] "The value of this variable must be validated by caller" */
    /* @Trace: SafeCrc_SUD_API_014 */
    /* XOR final value with XOROUT value */
    resultCrc = resultCrc ^ CRC_XOR_OUT8H2F;
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
