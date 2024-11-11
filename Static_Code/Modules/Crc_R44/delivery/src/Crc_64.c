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
**  SRC-MODULE: CRC_64.c                                                      **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Crc Library Module                                    **
**                                                                            **
**  PURPOSE   : Implementation of 64-bit CRC functions for Crc Library Module **
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
#if(CRC_64_MODE == CRC_64_TABLE)
#define CRC_START_SEC_CONST_ASIL_D_64
#include "MemMap.h"

/* Global look up table (reflected) for 64 bit table based CRC calculation */
/* Explicit typecasting done due to MISRA warning */
/* polyspace-begin MISRA2012:8.9 VARIABLE:ALL [Justified:Low] "Avoid re-create large object each time function is called" */
static CONST(uint64, CRC_CONST) Crc_Table64[CRC_COUNT256] =
{
  0x0000000000000000ULL, 0xB32E4CBE03A75F6FULL, 0xF4843657A840A05BULL,
  0x47AA7AE9ABE7FF34ULL, 0x7BD0C384FF8F5E33ULL, 0xC8FE8F3AFC28015CULL,
  0x8F54F5D357CFFE68ULL, 0x3C7AB96D5468A107ULL, 0xF7A18709FF1EBC66ULL,
  0x448FCBB7FCB9E309ULL, 0x0325B15E575E1C3DULL, 0xB00BFDE054F94352ULL,
  0x8C71448D0091E255ULL, 0x3F5F08330336BD3AULL, 0x78F572DAA8D1420EULL,
  0xCBDB3E64AB761D61ULL, 0x7D9BA13851336649ULL, 0xCEB5ED8652943926ULL,
  0x891F976FF973C612ULL, 0x3A31DBD1FAD4997DULL, 0x064B62BCAEBC387AULL,
  0xB5652E02AD1B6715ULL, 0xF2CF54EB06FC9821ULL, 0x41E11855055BC74EULL,
  0x8A3A2631AE2DDA2FULL, 0x39146A8FAD8A8540ULL, 0x7EBE1066066D7A74ULL,
  0xCD905CD805CA251BULL, 0xF1EAE5B551A2841CULL, 0x42C4A90B5205DB73ULL,
  0x056ED3E2F9E22447ULL, 0xB6409F5CFA457B28ULL, 0xFB374270A266CC92ULL,
  0x48190ECEA1C193FDULL, 0x0FB374270A266CC9ULL, 0xBC9D3899098133A6ULL,
  0x80E781F45DE992A1ULL, 0x33C9CD4A5E4ECDCEULL, 0x7463B7A3F5A932FAULL,
  0xC74DFB1DF60E6D95ULL, 0x0C96C5795D7870F4ULL, 0xBFB889C75EDF2F9BULL,
  0xF812F32EF538D0AFULL, 0x4B3CBF90F69F8FC0ULL, 0x774606FDA2F72EC7ULL,
  0xC4684A43A15071A8ULL, 0x83C230AA0AB78E9CULL, 0x30EC7C140910D1F3ULL,
  0x86ACE348F355AADBULL, 0x3582AFF6F0F2F5B4ULL, 0x7228D51F5B150A80ULL,
  0xC10699A158B255EFULL, 0xFD7C20CC0CDAF4E8ULL, 0x4E526C720F7DAB87ULL,
  0x09F8169BA49A54B3ULL, 0xBAD65A25A73D0BDCULL, 0x710D64410C4B16BDULL,
  0xC22328FF0FEC49D2ULL, 0x85895216A40BB6E6ULL, 0x36A71EA8A7ACE989ULL,
  0x0ADDA7C5F3C4488EULL, 0xB9F3EB7BF06317E1ULL, 0xFE5991925B84E8D5ULL,
  0x4D77DD2C5823B7BAULL, 0x64B62BCAEBC387A1ULL, 0xD7986774E864D8CEULL,
  0x90321D9D438327FAULL, 0x231C512340247895ULL, 0x1F66E84E144CD992ULL,
  0xAC48A4F017EB86FDULL, 0xEBE2DE19BC0C79C9ULL, 0x58CC92A7BFAB26A6ULL,
  0x9317ACC314DD3BC7ULL, 0x2039E07D177A64A8ULL, 0x67939A94BC9D9B9CULL,
  0xD4BDD62ABF3AC4F3ULL, 0xE8C76F47EB5265F4ULL, 0x5BE923F9E8F53A9BULL,
  0x1C4359104312C5AFULL, 0xAF6D15AE40B59AC0ULL, 0x192D8AF2BAF0E1E8ULL,
  0xAA03C64CB957BE87ULL, 0xEDA9BCA512B041B3ULL, 0x5E87F01B11171EDCULL,
  0x62FD4976457FBFDBULL, 0xD1D305C846D8E0B4ULL, 0x96797F21ED3F1F80ULL,
  0x2557339FEE9840EFULL, 0xEE8C0DFB45EE5D8EULL, 0x5DA24145464902E1ULL,
  0x1A083BACEDAEFDD5ULL, 0xA9267712EE09A2BAULL, 0x955CCE7FBA6103BDULL,
  0x267282C1B9C65CD2ULL, 0x61D8F8281221A3E6ULL, 0xD2F6B4961186FC89ULL,
  0x9F8169BA49A54B33ULL, 0x2CAF25044A02145CULL, 0x6B055FEDE1E5EB68ULL,
  0xD82B1353E242B407ULL, 0xE451AA3EB62A1500ULL, 0x577FE680B58D4A6FULL,
  0x10D59C691E6AB55BULL, 0xA3FBD0D71DCDEA34ULL, 0x6820EEB3B6BBF755ULL,
  0xDB0EA20DB51CA83AULL, 0x9CA4D8E41EFB570EULL, 0x2F8A945A1D5C0861ULL,
  0x13F02D374934A966ULL, 0xA0DE61894A93F609ULL, 0xE7741B60E174093DULL,
  0x545A57DEE2D35652ULL, 0xE21AC88218962D7AULL, 0x5134843C1B317215ULL,
  0x169EFED5B0D68D21ULL, 0xA5B0B26BB371D24EULL, 0x99CA0B06E7197349ULL,
  0x2AE447B8E4BE2C26ULL, 0x6D4E3D514F59D312ULL, 0xDE6071EF4CFE8C7DULL,
  0x15BB4F8BE788911CULL, 0xA6950335E42FCE73ULL, 0xE13F79DC4FC83147ULL,
  0x521135624C6F6E28ULL, 0x6E6B8C0F1807CF2FULL, 0xDD45C0B11BA09040ULL,
  0x9AEFBA58B0476F74ULL, 0x29C1F6E6B3E0301BULL, 0xC96C5795D7870F42ULL,
  0x7A421B2BD420502DULL, 0x3DE861C27FC7AF19ULL, 0x8EC62D7C7C60F076ULL,
  0xB2BC941128085171ULL, 0x0192D8AF2BAF0E1EULL, 0x4638A2468048F12AULL,
  0xF516EEF883EFAE45ULL, 0x3ECDD09C2899B324ULL, 0x8DE39C222B3EEC4BULL,
  0xCA49E6CB80D9137FULL, 0x7967AA75837E4C10ULL, 0x451D1318D716ED17ULL,
  0xF6335FA6D4B1B278ULL, 0xB199254F7F564D4CULL, 0x02B769F17CF11223ULL,
  0xB4F7F6AD86B4690BULL, 0x07D9BA1385133664ULL, 0x4073C0FA2EF4C950ULL,
  0xF35D8C442D53963FULL, 0xCF273529793B3738ULL, 0x7C0979977A9C6857ULL,
  0x3BA3037ED17B9763ULL, 0x888D4FC0D2DCC80CULL, 0x435671A479AAD56DULL,
  0xF0783D1A7A0D8A02ULL, 0xB7D247F3D1EA7536ULL, 0x04FC0B4DD24D2A59ULL,
  0x3886B22086258B5EULL, 0x8BA8FE9E8582D431ULL, 0xCC0284772E652B05ULL,
  0x7F2CC8C92DC2746AULL, 0x325B15E575E1C3D0ULL, 0x8175595B76469CBFULL,
  0xC6DF23B2DDA1638BULL, 0x75F16F0CDE063CE4ULL, 0x498BD6618A6E9DE3ULL,
  0xFAA59ADF89C9C28CULL, 0xBD0FE036222E3DB8ULL, 0x0E21AC88218962D7ULL,
  0xC5FA92EC8AFF7FB6ULL, 0x76D4DE52895820D9ULL, 0x317EA4BB22BFDFEDULL,
  0x8250E80521188082ULL, 0xBE2A516875702185ULL, 0x0D041DD676D77EEAULL,
  0x4AAE673FDD3081DEULL, 0xF9802B81DE97DEB1ULL, 0x4FC0B4DD24D2A599ULL,
  0xFCEEF8632775FAF6ULL, 0xBB44828A8C9205C2ULL, 0x086ACE348F355AADULL,
  0x34107759DB5DFBAAULL, 0x873E3BE7D8FAA4C5ULL, 0xC094410E731D5BF1ULL,
  0x73BA0DB070BA049EULL, 0xB86133D4DBCC19FFULL, 0x0B4F7F6AD86B4690ULL,
  0x4CE50583738CB9A4ULL, 0xFFCB493D702BE6CBULL, 0xC3B1F050244347CCULL,
  0x709FBCEE27E418A3ULL, 0x3735C6078C03E797ULL, 0x841B8AB98FA4B8F8ULL,
  0xADDA7C5F3C4488E3ULL, 0x1EF430E13FE3D78CULL, 0x595E4A08940428B8ULL,
  0xEA7006B697A377D7ULL, 0xD60ABFDBC3CBD6D0ULL, 0x6524F365C06C89BFULL,
  0x228E898C6B8B768BULL, 0x91A0C532682C29E4ULL, 0x5A7BFB56C35A3485ULL,
  0xE955B7E8C0FD6BEAULL, 0xAEFFCD016B1A94DEULL, 0x1DD181BF68BDCBB1ULL,
  0x21AB38D23CD56AB6ULL, 0x9285746C3F7235D9ULL, 0xD52F0E859495CAEDULL,
  0x6601423B97329582ULL, 0xD041DD676D77EEAAULL, 0x636F91D96ED0B1C5ULL,
  0x24C5EB30C5374EF1ULL, 0x97EBA78EC690119EULL, 0xAB911EE392F8B099ULL,
  0x18BF525D915FEFF6ULL, 0x5F1528B43AB810C2ULL, 0xEC3B640A391F4FADULL,
  0x27E05A6E926952CCULL, 0x94CE16D091CE0DA3ULL, 0xD3646C393A29F297ULL,
  0x604A2087398EADF8ULL, 0x5C3099EA6DE60CFFULL, 0xEF1ED5546E415390ULL,
  0xA8B4AFBDC5A6ACA4ULL, 0x1B9AE303C601F3CBULL, 0x56ED3E2F9E224471ULL,
  0xE5C372919D851B1EULL, 0xA26908783662E42AULL, 0x114744C635C5BB45ULL,
  0x2D3DFDAB61AD1A42ULL, 0x9E13B115620A452DULL, 0xD9B9CBFCC9EDBA19ULL,
  0x6A978742CA4AE576ULL, 0xA14CB926613CF817ULL, 0x1262F598629BA778ULL,
  0x55C88F71C97C584CULL, 0xE6E6C3CFCADB0723ULL, 0xDA9C7AA29EB3A624ULL,
  0x69B2361C9D14F94BULL, 0x2E184CF536F3067FULL, 0x9D36004B35545910ULL,
  0x2B769F17CF112238ULL, 0x9858D3A9CCB67D57ULL, 0xDFF2A94067518263ULL,
  0x6CDCE5FE64F6DD0CULL, 0x50A65C93309E7C0BULL, 0xE388102D33392364ULL,
  0xA4226AC498DEDC50ULL, 0x170C267A9B79833FULL, 0xDCD7181E300F9E5EULL,
  0x6FF954A033A8C131ULL, 0x28532E49984F3E05ULL, 0x9B7D62F79BE8616AULL,
  0xA707DB9ACF80C06DULL, 0x14299724CC279F02ULL, 0x5383EDCD67C06036ULL,
  0xE0ADA17364673F59ULL
};
/* polyspace-end MISRA2012:8.9 VARIABLE:ALL [Justified:Low] "Avoid re-create large object each time function is called" */
#define CRC_STOP_SEC_CONST_ASIL_D_64
#include "MemMap.h"
#endif

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define CRC_START_SEC_CODE_ASIL_D
#include "MemMap.h"
/*******************************************************************************
** Function Name        : Crc_CalculateCRC64                                  **
**                                                                            **
** Service ID           : CRC_CALCULATECRC64_SID: 0x07                        **
**                                                                            **
** Description          : This function returns the 64 bit checksum calculated**
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
**                        Crc_StartValue64: Start value when the algorithm    **
**                                          starts                            **
**                        Crc_IsFirstCall : TRUE: First call in a sequence or **
**                                          individual CRC calculation; start **
**                                          from initial value, ignore        **
**                                          Crc_StartValue64.                 **
**                                          FALSE: Subsequent call in a call  **
**                                          sequence; Crc_StartValue64 is     **
**                                          interpreted to be the return value**
**                                          of the previous function call.    **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : 64 bit result of CRC calculation                    **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : Crc_Table64[]              **
**                        Function(s) invoked    : Crc_Reflect                **
*******************************************************************************/

/* @Trace: SRS_LIBS_08518 SRS_LIBS_08525 SRS_LIBS_08526 */
/* @Trace: SafeCRC_SUD_MACRO_001 */
#if((CRC_64_MODE == CRC_64_RUNTIME) || (CRC_64_MODE == CRC_64_TABLE))
FUNC(uint64, CRC_CODE) Crc_CalculateCRC64
  (P2CONST(uint8, CRC_CONST, CRC_APPL_CONST)Crc_DataPtr, uint32 Crc_Length,
  uint64 Crc_StartValue64, boolean Crc_IsFirstCall)
{
  /* Local variable to hold CRC result calculation */
  VAR(uint64, AUTOMATIC) resultCrc;
  /* Local variable to hold address that pointed to input data */
  VAR(uint32, AUTOMATIC) dataIndex;
  /* @Trace: SafeCrc_SUD_API_039 */
  /* Initial value for CRC result calculation. It be returned when pointer to 
  start address of data block is null */
  resultCrc = CRC_ZERO;
  /* Check if pointer to start address of data block is null */
  if (NULL_PTR != Crc_DataPtr)
  {
    /* @Trace: SafeCrc_SUD_API_040 */
    /* Check if it is the first function call */
    if (Crc_IsFirstCall == CRC_TRUE)
    {
      /* Initial value for CRC result calculation */
      resultCrc = CRC_INITIAL_VALUE64;
    }
    else
    {
      /* Initial value for CRC result calculation */
      resultCrc = CRC_XOR_OUT64 ^ Crc_StartValue64;
      /* Check if CRC64 calculation method is runtime mode */
      /* @Trace: SafeCRC_SUD_MACRO_001 */
      #if(CRC_64_MODE == CRC_64_RUNTIME)
        resultCrc = Crc_Reflect(resultCrc, CRC_SIXTYFOUR);
      #endif
      /* Do not reflect CRC in table based calculation mode*/
    }
    /* Initial address that pointed to input data */
    dataIndex = CRC_ZERO;
    /* @Trace: SafeCrc_SUD_API_041 */
    /* Loop for each byte data from input data */
    while (dataIndex < Crc_Length) /* polyspace MISRA2012:D4.14 [Justified:Low] "The value of this variable must be validated by caller" */
    {
      VAR(uint8, AUTOMATIC) byteData;
      /* Copy the data byte into local variable */
      /* polyspace-begin MISRA2012:D4.14 MISRA2012:D4.1 MISRA2012:18.1 RTE:IDP [Justified:Low] "Array and length shall be validated by the caller" */
      byteData = Crc_DataPtr[dataIndex]; 
      /* polyspace-end MISRA2012:D4.14 MISRA2012:D4.1 MISRA2012:18.1 RTE:IDP [Justified:Low] "Array and length shall be validated by the caller" */
      /* Check if CRC64 calculation method is runtime mode */
      /* @Trace: SafeCRC_SUD_MACRO_001 */
      #if(CRC_64_MODE == CRC_64_RUNTIME)
        /* @Trace: SafeCrc_SUD_API_043 */
        /* Local variable to hold reflection data result */
        VAR(uint64, AUTOMATIC) reflectData;
        /* Local variable to hold Crc temp value */
        VAR(uint64, AUTOMATIC) resultCrcHiTemp64;
        VAR(uint64, AUTOMATIC) resultCrcLoTemp64;
        /* Reflect data before performing XOR calculation */
        reflectData =  Crc_Reflect(byteData, CRC_EIGHT);
        /* Perform XOR of data byte with CRC result */
        resultCrc = resultCrc ^ (reflectData << CRC_FIFTYSIX);
        /* Local variable to hold loop index of each bit in byte data */
        VAR(uint8, AUTOMATIC) loopIndex;
        /* Initialize loop index */
        loopIndex = CRC_EIGHT;
        /* Loop for 8 bits */
        while (CRC_ZERO < loopIndex)
        {
          /* Check if MSB of byte data is set to one */
          if (CRC_MSB64 == (resultCrc & CRC_MSB64))
          {
            resultCrcHiTemp64 = (resultCrc & CRC_MASK_FOUR_BYTE_HIGH) >> CRC_THIRTYTWO;
            resultCrcLoTemp64 = (uint32)(resultCrc & CRC_MASK_FOUR_BYTE);
            resultCrcHiTemp64 = (uint64)resultCrcHiTemp64 << CRC_ONE;
            resultCrcLoTemp64 = (uint64)resultCrcLoTemp64 << CRC_ONE;
            /* polyspace-begin DEFECT:*  MISRA2012:D4.1 [Not a defect:Low] "Expected behavior to implement CRC calculation algorithsm" */
            resultCrc = (uint64)((resultCrcHiTemp64 << CRC_THIRTYTWO) | resultCrcLoTemp64) ^ CRC_POLY64;
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
      /* @Trace: SafeCrc_SUD_API_042 */
        /* Local variable to hold address related to data byte in Table */
        VAR(uint8, AUTOMATIC) tableDataIndex;
        /* Set value of address related to data byte to local variable */
        tableDataIndex = (uint8)(byteData ^ (resultCrc & CRC_BYTE_MASK));
        /* Fetch value of CRC from the Table */
        resultCrc = Crc_Table64[tableDataIndex] ^ (resultCrc >> CRC_EIGHT);
      #endif
      /* Point to next data byte in input data */
      dataIndex++;
    } 
    /* @Trace: SafeCrc_SUD_API_044 */
    /* XOR final value with XOROUT value */
    resultCrc = resultCrc ^ CRC_XOR_OUT64;
    /* Check if CRC64 calculation method is runtime mode */
    /* @Trace: SafeCRC_SUD_MACRO_001 */
    #if(CRC_64_MODE == CRC_64_RUNTIME)
      /* Reflect final CRC result */
      resultCrc = Crc_Reflect(resultCrc, CRC_SIXTYFOUR);
    #endif
    /* Do not reflect CRC in table based calculation mode*/
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
