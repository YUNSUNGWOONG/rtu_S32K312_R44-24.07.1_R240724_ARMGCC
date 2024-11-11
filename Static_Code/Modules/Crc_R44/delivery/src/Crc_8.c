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
**  SRC-MODULE: Crc_8.c                                                       **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Crc Library Module                                    **
**                                                                            **
**  PURPOSE   : Implementation for 8-bit CRC functions of Crc Library Module  **
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
#if(CRC_8_MODE == CRC_8_TABLE)
#define CRC_START_SEC_CONST_ASIL_D_8
#include "MemMap.h"

/* Global look up table for 8 bit table based CRC calculation */
/* Explicit typecasting not added as it is not required */
/* polyspace-begin MISRA2012:8.9 VARIABLE:ALL [Justified:Low] "Avoid re-create large object each time function is called" */
static CONST(uint8, CRC_CONST) Crc_Table8[CRC_COUNT256] =
{
  0x00U, 0x1DU, 0x3AU, 0x27U, 0x74U, 0x69U, 0x4EU, 0x53U, 0xE8U, 0xF5U, 0xD2U, 
  0xCFU, 0x9CU, 0x81U, 0xA6U, 0xBBU, 0xCDU, 0xD0U, 0xF7U, 0xEAU, 0xB9U, 0xA4U, 
  0x83U, 0x9EU, 0x25U, 0x38U, 0x1FU, 0x02U, 0x51U, 0x4CU, 0x6BU, 0x76U, 0x87U, 
  0x9AU, 0xBDU, 0xA0U, 0xF3U, 0xEEU, 0xC9U, 0xD4U, 0x6FU, 0x72U, 0x55U, 0x48U, 
  0x1BU, 0x06U, 0x21U, 0x3CU, 0x4AU, 0x57U, 0x70U, 0x6DU, 0x3EU, 0x23U, 0x04U, 
  0x19U, 0xA2U, 0xBFU, 0x98U, 0x85U, 0xD6U, 0xCBU, 0xECU, 0xF1U, 0x13U, 0x0EU, 
  0x29U, 0x34U, 0x67U, 0x7AU, 0x5DU, 0x40U, 0xFBU, 0xE6U, 0xC1U, 0xDCU, 0x8FU, 
  0x92U, 0xB5U, 0xA8U, 0xDEU, 0xC3U, 0xE4U, 0xF9U, 0xAAU, 0xB7U, 0x90U, 0x8DU, 
  0x36U, 0x2BU, 0x0CU, 0x11U, 0x42U, 0x5FU, 0x78U, 0x65U, 0x94U, 0x89U, 0xAEU, 
  0xB3U, 0xE0U, 0xFDU, 0xDAU, 0xC7U, 0x7CU, 0x61U, 0x46U, 0x5BU, 0x08U, 0x15U, 
  0x32U, 0x2FU, 0x59U, 0x44U, 0x63U, 0x7EU, 0x2DU, 0x30U, 0x17U, 0x0AU, 0xB1U, 
  0xACU, 0x8BU, 0x96U, 0xC5U, 0xD8U, 0xFFU, 0xE2U, 0x26U, 0x3BU, 0x1CU, 0x01U, 
  0x52U, 0x4FU, 0x68U, 0x75U, 0xCEU, 0xD3U, 0xF4U, 0xE9U, 0xBAU, 0xA7U, 0x80U,
  0x9DU, 0xEBU, 0xF6U, 0xD1U, 0xCCU, 0x9FU, 0x82U, 0xA5U, 0xB8U, 0x03U, 0x1EU, 
  0x39U, 0x24U, 0x77U, 0x6AU, 0x4DU, 0x50U, 0xA1U, 0xBCU, 0x9BU, 0x86U, 0xD5U, 
  0xC8U, 0xEFU, 0xF2U, 0x49U, 0x54U, 0x73U, 0x6EU, 0x3DU, 0x20U, 0x07U, 0x1AU, 
  0x6CU, 0x71U, 0x56U, 0x4BU, 0x18U, 0x05U, 0x22U, 0x3FU, 0x84U, 0x99U, 0xBEU, 
  0xA3U, 0xF0U, 0xEDU, 0xCAU, 0xD7U, 0x35U, 0x28U, 0x0FU, 0x12U, 0x41U, 0x5CU, 
  0x7BU, 0x66U, 0xDDU, 0xC0U, 0xE7U, 0xFAU, 0xA9U, 0xB4U, 0x93U, 0x8EU, 0xF8U, 
  0xE5U, 0xC2U, 0xDFU, 0x8CU, 0x91U, 0xB6U, 0xABU, 0x10U, 0x0DU, 0x2AU, 0x37U, 
  0x64U, 0x79U, 0x5EU, 0x43U, 0xB2U, 0xAFU, 0x88U, 0x95U, 0xC6U, 0xDBU, 0xFCU, 
  0xE1U, 0x5AU, 0x47U, 0x60U, 0x7DU, 0x2EU, 0x33U, 0x14U, 0x09U, 0x7FU, 0x62U, 
  0x45U, 0x58U, 0x0BU, 0x16U, 0x31U, 0x2CU, 0x97U, 0x8AU, 0xADU, 0xB0U, 0xE3U, 
  0xFEU, 0xD9U, 0xC4U
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
** Function Name        : Crc_CalculateCRC8                                   **
**                                                                            **
** Service ID           : CRC_CALCULATECRC8_SID: 0x01                         **
**                                                                            **
** Description          : This function returns the 8 bit checksum calculated **
**                        by runtime and table based method.                  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : Crc_DataPtr     : Pointer to start address of       **
**                                          data block to be calculated       **
**                        Crc_Length      : Length of data block to be        **
**                                          calculated in bytes               **
**                        Crc_StartValue8 : Start value when the algorithm    **
**                                          starts                            **
**                        Crc_IsFirstCall : TRUE: First call in a sequence or **
**                                          individual CRC calculation; start **
**                                          from initial value, ignore        **
**                                          Crc_StartValue8.                  **
**                                          FALSE: Subsequent call in a call  **
**                                          sequence; Crc_StartValue8 is      **
**                                          interpreted to be the return value**
**                                          of the previous function call.    **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : 8 bit result of CRC calculation                     **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : Crc_Table8[]                  **
**                        Function(s) invoked : None                          **
*******************************************************************************/

/* @Trace: SRS_LIBS_08518 SRS_LIBS_08525 SRS_LIBS_08526 */
/* @Trace: SafeCRC_SUD_MACRO_001 */
#if((CRC_8_MODE == CRC_8_RUNTIME) || (CRC_8_MODE == CRC_8_TABLE))
FUNC(uint8, CRC_CODE) Crc_CalculateCRC8
  (P2CONST(uint8, CRC_CONST, CRC_APPL_CONST)Crc_DataPtr, uint32 Crc_Length,
  uint8 Crc_StartValue8, boolean Crc_IsFirstCall)
{
  /* Local variable to hold CRC result calculation */
  VAR(uint8, AUTOMATIC) resultCrc;
  /* Local variable to hold address that pointed to input data */
  VAR(uint32, AUTOMATIC) dataIndex;
  /* Initial value for CRC result calculation. It be returned when pointer to 
  start address of data block is null */
  /* @Trace: SafeCrc_SUD_API_003 */
  resultCrc = CRC_ZERO;
  /* Check if pointer to start address of data block is null */
  if (NULL_PTR != Crc_DataPtr)
  {
    /* @Trace: SafeCrc_SUD_API_004 */
    /* Check if it is the first function call */
    if (CRC_TRUE == Crc_IsFirstCall)
      {
        /* Initial value for CRC result calculation */
        resultCrc = CRC_INITIAL_VALUE8;
      }
      else
      {
        /* Initialize CRC result  with previous result */
        resultCrc = CRC_XOR_OUT8 ^ Crc_StartValue8;
      }
      /* Initial address that pointed to input data */
      dataIndex = CRC_ZERO;
      /* @Trace: SafeCrc_SUD_API_005 */
      /* Loop for each byte data from input data */
      while (dataIndex < Crc_Length) /* polyspace MISRA2012:D4.14 [Justified:Low] "The value of this variable must be validated by caller" */
      {
        /* Local variable to hold one byte data from input data */
        VAR(uint8, AUTOMATIC) byteData;
        /* Copy the data byte into local variable */
        /* polyspace-begin MISRA2012:D4.14 MISRA2012:D4.1 MISRA2012:18.1 RTE:IDP [Justified:Low] "Array and length shall be validated by the caller" */
        /* polyspace +4 DEFECT:OUT_BOUND_PTR [Not a defect:Justified] "Array and length shall be validated by the caller" */
        /* polyspace +3 DEFECT:TAINTED_SIGN_CHANGE [Not a defect:Justified] "Array and length shall be validated by the caller" */
        /* polyspace +2 CERT-C:MEM35-C [Justified:Low] "Array and length shall be validated by the caller" */
        /* polyspace +1 CERT-C:ARR30-C [Justified:Low] "Array and length shall be validated by the caller" */
        byteData = Crc_DataPtr[dataIndex]; 
        /* polyspace-end MISRA2012:D4.14 MISRA2012:D4.1 MISRA2012:18.1 RTE:IDP [Justified:Low] "Array and length shall be validated by the caller" */
        /* Perform XOR of data byte with CRC result */
        resultCrc = resultCrc ^ byteData;
        /* Check if CRC8 calculation method is runtime mode */
        /* @Trace: SafeCRC_SUD_MACRO_001 */
        #if(CRC_8_MODE == CRC_8_RUNTIME)
          /* @Trace: SafeCrc_SUD_API_007 */
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
              resultCrc = (resultCrc << CRC_ONE) ^ CRC_POLY8;
            }
            else
            {
              resultCrc = resultCrc << CRC_ONE;
            }
            /* Decrement the loop index */
            loopIndex--;
          }

        #else
          /* @Trace: SafeCrc_SUD_API_006 */
          /* Fetch value of CRC from the Table */
          resultCrc = Crc_Table8[resultCrc];
        #endif
        /* Point to next data byte in input data */
        dataIndex++;
      }
      /* @Trace: SafeCrc_SUD_API_008 */
      /* XOR final value with XOROUT value */
      resultCrc = resultCrc ^ CRC_XOR_OUT8;
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
