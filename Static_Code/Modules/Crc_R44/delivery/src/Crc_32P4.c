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
**  SRC-MODULE: Crc_32P4.c                                                    **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Crc Library Module                                    **
**                                                                            **
**  PURPOSE   : Implementation of 32-bit CRC functions with polynomial        **
**              0xF4ACFB13 for Crc Library Module                             **
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
#include "Crc_IntFunc.h"             /* Crc Internal Function Header File */

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
/* @Trace: SafeCRC_SUD_MACRO_001 */
#if(CRC_32P4_MODE == CRC_32P4_TABLE)
#define CRC_START_SEC_CONST_ASIL_D_32
#include "MemMap.h"

/* 
 * Global look up table (reflected) for 32 bit 0xF4ACFB13 polynomial table 
 * based CRC calculation 
 */
/* Explicit typecasting done due to MISRA warning */
/* polyspace-begin MISRA2012:8.9 VARIABLE:ALL [Justified:Low] "Avoid re-create large object each time function is called" */
static CONST(uint32, CRC_CONST) Crc_Table32P4[CRC_COUNT256] =
{
  0x00000000UL, 0x30850FF5UL, 0x610A1FEAUL, 0x518F101FUL, 0xC2143FD4UL, 
  0xF2913021UL, 0xA31E203EUL, 0x939B2FCBUL, 0x159615F7UL, 0x25131A02UL, 
  0x749C0A1DUL, 0x441905E8UL, 0xD7822A23UL, 0xE70725D6UL, 0xB68835C9UL, 
  0x860D3A3CUL, 0x2B2C2BEEUL, 0x1BA9241BUL, 0x4A263404UL, 0x7AA33BF1UL, 
  0xE938143AUL, 0xD9BD1BCFUL, 0x88320BD0UL, 0xB8B70425UL, 0x3EBA3E19UL, 
  0x0E3F31ECUL, 0x5FB021F3UL, 0x6F352E06UL, 0xFCAE01CDUL, 0xCC2B0E38UL,
  0x9DA41E27UL, 0xAD2111D2UL, 0x565857DCUL, 0x66DD5829UL, 0x37524836UL, 
  0x07D747C3UL, 0x944C6808UL, 0xA4C967FDUL, 0xF54677E2UL, 0xC5C37817UL, 
  0x43CE422BUL, 0x734B4DDEUL, 0x22C45DC1UL, 0x12415234UL, 0x81DA7DFFUL, 
  0xB15F720AUL, 0xE0D06215UL, 0xD0556DE0UL, 0x7D747C32UL, 0x4DF173C7UL, 
  0x1C7E63D8UL, 0x2CFB6C2DUL, 0xBF6043E6UL, 0x8FE54C13UL, 0xDE6A5C0CUL, 
  0xEEEF53F9UL, 0x68E269C5UL, 0x58676630UL, 0x09E8762FUL, 0x396D79DAUL,
  0xAAF65611UL, 0x9A7359E4UL, 0xCBFC49FBUL, 0xFB79460EUL, 0xACB0AFB8UL, 
  0x9C35A04DUL, 0xCDBAB052UL, 0xFD3FBFA7UL, 0x6EA4906CUL, 0x5E219F99UL, 
  0x0FAE8F86UL, 0x3F2B8073UL, 0xB926BA4FUL, 0x89A3B5BAUL, 0xD82CA5A5UL, 
  0xE8A9AA50UL, 0x7B32859BUL, 0x4BB78A6EUL, 0x1A389A71UL, 0x2ABD9584UL, 
  0x879C8456UL, 0xB7198BA3UL, 0xE6969BBCUL, 0xD6139449UL, 0x4588BB82UL, 
  0x750DB477UL, 0x2482A468UL, 0x1407AB9DUL, 0x920A91A1UL, 0xA28F9E54UL,
  0xF3008E4BUL, 0xC38581BEUL, 0x501EAE75UL, 0x609BA180UL, 0x3114B19FUL, 
  0x0191BE6AUL, 0xFAE8F864UL, 0xCA6DF791UL, 0x9BE2E78EUL, 0xAB67E87BUL, 
  0x38FCC7B0UL, 0x0879C845UL, 0x59F6D85AUL, 0x6973D7AFUL, 0xEF7EED93UL, 
  0xDFFBE266UL, 0x8E74F279UL, 0xBEF1FD8CUL, 0x2D6AD247UL, 0x1DEFDDB2UL, 
  0x4C60CDADUL, 0x7CE5C258UL, 0xD1C4D38AUL, 0xE141DC7FUL, 0xB0CECC60UL, 
  0x804BC395UL, 0x13D0EC5EUL, 0x2355E3ABUL, 0x72DAF3B4UL, 0x425FFC41UL,
  0xC452C67DUL, 0xF4D7C988UL, 0xA558D997UL, 0x95DDD662UL, 0x0646F9A9UL, 
  0x36C3F65CUL, 0x674CE643UL, 0x57C9E9B6UL, 0xC8DF352FUL, 0xF85A3ADAUL, 
  0xA9D52AC5UL, 0x99502530UL, 0x0ACB0AFBUL, 0x3A4E050EUL, 0x6BC11511UL, 
  0x5B441AE4UL, 0xDD4920D8UL, 0xEDCC2F2DUL, 0xBC433F32UL, 0x8CC630C7UL, 
  0x1F5D1F0CUL, 0x2FD810F9UL, 0x7E5700E6UL, 0x4ED20F13UL, 0xE3F31EC1UL, 
  0xD3761134UL, 0x82F9012BUL, 0xB27C0EDEUL, 0x21E72115UL, 0x11622EE0UL,
  0x40ED3EFFUL, 0x7068310AUL, 0xF6650B36UL, 0xC6E004C3UL, 0x976F14DCUL, 
  0xA7EA1B29UL, 0x347134E2UL, 0x04F43B17UL, 0x557B2B08UL, 0x65FE24FDUL, 
  0x9E8762F3UL, 0xAE026D06UL, 0xFF8D7D19UL, 0xCF0872ECUL, 0x5C935D27UL, 
  0x6C1652D2UL, 0x3D9942CDUL, 0x0D1C4D38UL, 0x8B117704UL, 0xBB9478F1UL, 
  0xEA1B68EEUL, 0xDA9E671BUL, 0x490548D0UL, 0x79804725UL, 0x280F573AUL, 
  0x188A58CFUL, 0xB5AB491DUL, 0x852E46E8UL, 0xD4A156F7UL, 0xE4245902UL,
  0x77BF76C9UL, 0x473A793CUL, 0x16B56923UL, 0x263066D6UL, 0xA03D5CEAUL, 
  0x90B8531FUL, 0xC1374300UL, 0xF1B24CF5UL, 0x6229633EUL, 0x52AC6CCBUL, 
  0x03237CD4UL, 0x33A67321UL, 0x646F9A97UL, 0x54EA9562UL, 0x0565857DUL, 
  0x35E08A88UL, 0xA67BA543UL, 0x96FEAAB6UL, 0xC771BAA9UL, 0xF7F4B55CUL, 
  0x71F98F60UL, 0x417C8095UL, 0x10F3908AUL, 0x20769F7FUL, 0xB3EDB0B4UL, 
  0x8368BF41UL, 0xD2E7AF5EUL, 0xE262A0ABUL, 0x4F43B179UL, 0x7FC6BE8CUL,
  0x2E49AE93UL, 0x1ECCA166UL, 0x8D578EADUL, 0xBDD28158UL, 0xEC5D9147UL, 
  0xDCD89EB2UL, 0x5AD5A48EUL, 0x6A50AB7BUL, 0x3BDFBB64UL, 0x0B5AB491UL, 
  0x98C19B5AUL, 0xA84494AFUL, 0xF9CB84B0UL, 0xC94E8B45UL, 0x3237CD4BUL, 
  0x02B2C2BEUL, 0x533DD2A1UL, 0x63B8DD54UL, 0xF023F29FUL, 0xC0A6FD6AUL, 
  0x9129ED75UL, 0xA1ACE280UL, 0x27A1D8BCUL, 0x1724D749UL, 0x46ABC756UL, 
  0x762EC8A3UL, 0xE5B5E768UL, 0xD530E89DUL, 0x84BFF882UL, 0xB43AF777UL,
  0x191BE6A5UL, 0x299EE950UL, 0x7811F94FUL, 0x4894F6BAUL, 0xDB0FD971UL, 
  0xEB8AD684UL, 0xBA05C69BUL, 0x8A80C96EUL, 0x0C8DF352UL, 0x3C08FCA7UL, 
  0x6D87ECB8UL, 0x5D02E34DUL, 0xCE99CC86UL, 0xFE1CC373UL, 0xAF93D36CUL, 
  0x9F16DC99UL
};
/* polyspace-end MISRA2012:8.9 VARIABLE:ALL [Justified:Low] "Avoid re-create large object each time function is called" */
#define CRC_STOP_SEC_CONST_ASIL_D_32
#include "MemMap.h"

#endif 

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define CRC_START_SEC_CODE_ASIL_D
#include "MemMap.h"
/*******************************************************************************
** Function Name        : Crc_CalculateCRC32P4                                **
**                                                                            **
** Service ID           : CRC_CALCULATECRC32P4_SID: 0x06                      **
**                                                                            **
** Description          : This function returns the 32 bit checksum calculated**
**                        using polynomial 0xF4ACFB13 by runtime and table    **
**                        based method.                                       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : Crc_DataPtr     : Pointer to start address of       **
**                                          data block to be calculated       **
**                        Crc_Length      : Length of data block to be        **
**                                          calculated in bytes               **
**                        Crc_StartValue32: Start value when the algorithm    **
**                                          starts                            **
**                        Crc_IsFirstCall : TRUE: First call in a sequence or **
**                                          individual CRC calculation; start **
**                                          from initial value, ignore        **
**                                          Crc_StartValue32.                 **
**                                          FALSE: Subsequent call in a call  **
**                                          sequence; Crc_StartValue32 is     **
**                                          interpreted to be the return value**
**                                          of the previous function call.    **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : 32 bit result of CRC calculation                    **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : Crc_Table32P4[]            **
**                        Function(s) invoked    : Crc_Reflect                **
*******************************************************************************/

/* @Trace: SRS_LIBS_08518 SRS_LIBS_08525 SRS_LIBS_08526 */
/* @Trace: SafeCRC_SUD_MACRO_001 */
#if((CRC_32P4_MODE == CRC_32P4_RUNTIME) || (CRC_32P4_MODE == CRC_32P4_TABLE))
FUNC(uint32, CRC_CODE) Crc_CalculateCRC32P4
  (P2CONST(uint8, CRC_CONST, CRC_APPL_CONST)Crc_DataPtr, uint32 Crc_Length,
  uint32 Crc_StartValue32, boolean Crc_IsFirstCall)
{
  /* Local variable to hold CRC result calculation */
  VAR(uint32, AUTOMATIC) resultCrc;
  /* Local variable to hold address that pointed to input data */
  VAR(uint32, AUTOMATIC) dataIndex;
  /* @Trace: SafeCrc_SUD_API_033 */
  /* Initial value for CRC result calculation. It be returned when pointer to 
  start address of data block is null */
  resultCrc = CRC_ZERO;
  /* Check if pointer to start address of data block is null */
  if (NULL_PTR != Crc_DataPtr)
  {
    /* @Trace: SafeCrc_SUD_API_034 */
    /* Check if it is the first function call */
    if (CRC_TRUE == Crc_IsFirstCall)
    {
      /* Initial value for CRC result calculation */
      resultCrc = CRC_INITIAL_VALUE32P4;
    }
    else
    {
      /* Initial value for CRC result calculation */
      resultCrc = CRC_XOR_OUT32P4 ^ Crc_StartValue32;
      /* Check if CRC32P4 calculation method is runtime mode */
      /* @Trace: SafeCRC_SUD_MACRO_001 */
      #if(CRC_32P4_MODE == CRC_32P4_RUNTIME)
        resultCrc = (uint32)Crc_Reflect(resultCrc, CRC_THIRTYTWO);
      #endif
      /* Do not reflect CRC in runtime table based calculation mode*/
    }
    /* Initial address that pointed to input data */
    dataIndex = CRC_ZERO;
    /* @Trace: SafeCrc_SUD_API_035 */
    /* Loop for each byte data from input data */
    while (dataIndex < Crc_Length) /* polyspace MISRA2012:D4.14 [Justified:Low] "The value of this variable must be validated by caller" */
    {
      /* Local variable to hold one byte data from input data */
      VAR(uint8, AUTOMATIC) byteData; 
      /* Copy the data byte into local variable */
      /* polyspace-begin MISRA2012:D4.14 MISRA2012:D4.1 MISRA2012:18.1 RTE:IDP [Justified:Low] "Array and length shall be validated by the caller" */
      byteData = Crc_DataPtr[dataIndex]; 
      /* polyspace-end MISRA2012:D4.14 MISRA2012:D4.1 MISRA2012:18.1 RTE:IDP [Justified:Low] "Array and length shall be validated by the caller" */
      /* Check if CRC32P4 calculation method is runtime mode */
      /* @Trace: SafeCRC_SUD_MACRO_001 */
      #if(CRC_32P4_MODE == CRC_32P4_RUNTIME)
        /* @Trace: SafeCrc_SUD_API_037 */
        /* Local variable to hold reflection data result */
        VAR(uint32, AUTOMATIC) reflectData;
        /* Local variable to hold Crc temp value */
        VAR(uint64, AUTOMATIC) resultCrc64;
        /* Reflect data before performing XOR calculation */
        reflectData =  (uint32)Crc_Reflect(byteData, CRC_EIGHT);
        /* Perform XOR of data byte with CRC result */
        resultCrc = resultCrc ^ (reflectData << CRC_TWENTYFOUR);
        /* Local variable to hold loop index of each bit in byte data */
        VAR(uint8, AUTOMATIC) loopIndex; 
        /* Initialize loop index */
        loopIndex = CRC_EIGHT;
        /* Loop for 8 bits */
        while (CRC_ZERO < loopIndex)
        {
          /* Check if MSB of byte data is set to one */
          if (CRC_MSB32 == (resultCrc & CRC_MSB32))
          {
            resultCrc64 = (uint64)resultCrc << CRC_ONE;
            resultCrc = (uint32)(resultCrc64 & (uint32)CRC_MASK_FOUR_BYTE);
            /* polyspace-begin DEFECT:*  MISRA2012:D4.1 [Not a defect:Low] "Expected behavior to implement CRC calculation algorithsm" */
            resultCrc = resultCrc ^ CRC_POLY32P4;
            /* polyspace-end DEFECT:*  MISRA2012:D4.1 [Not a defect:Low] "Expected behavior to implement CRC calculation algorithsm" */
          } 
          else
          {
            resultCrc = resultCrc << CRC_ONE;
          }
          /* Decrement the loop index */
          loopIndex--;
        }
      #else
        /* @Trace: SafeCrc_SUD_API_036 */
        /* Local variable to hold address related to data byte in Table */
        VAR(uint8, AUTOMATIC) tableDataIndex;
        /* Set value of address related to data byte to local variable */
        tableDataIndex = (uint8)(byteData ^ (resultCrc & CRC_BYTE_MASK));
        /* Fetch value of CRC from the Table */
        resultCrc = Crc_Table32P4[tableDataIndex] ^ (resultCrc >> CRC_EIGHT);
      #endif
      /* Point to next data byte in input data */
      dataIndex++;
    }
    /* @Trace: SafeCrc_SUD_API_038 */
    /* XOR final value with XOROUT value */
    resultCrc = resultCrc ^ CRC_XOR_OUT32P4;
    /* Check if CRC32P4 calculation method is runtime mode */
    /* @Trace: SafeCRC_SUD_MACRO_001 */
    #if(CRC_32P4_MODE == CRC_32P4_RUNTIME)
      /* Reflect final CRC result */
      resultCrc = (uint32)Crc_Reflect(resultCrc, CRC_THIRTYTWO);
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
