/*******************************************************************************
**                           HYUNDAI AUTOEVER Corp.                           **
********************************************************************************
** (C) 2021 HYUNDAI AUTOEVER Corp.                                            **
** Confidential Proprietary Information. Distribution Limited.                **
** This source code is permitted to be used only in projects contracted       **
** with Hyundai Autoever, and any other use is prohibited.                    **
** If you use it for other purposes or change the source code,                **
** you may take legal responsibility.                                         **
** In this case, There is no warranty and technical support.                  **
********************************************************************************
**  Module Name : RTE                                                         **
**                                                                            **
**  File Name : Rte_User.c                                                    **
**                                                                            **
**  Generated On : Mon Nov 11 2024 13:32:30 KST                               **
**                                                                            **
**  Generated from :                                                          **
**  Configuration\Definition\Os_ECU_Configuration_PDF_S32K312.arxml           **
**  Configuration\Ecu\ECUCD_EcucValueCollection.arxml                         **
**  Configuration\Ecu\Ecud_BswM.arxml                                         **
**  Configuration\Ecu\Ecud_CanCM.arxml                                        **
**  Configuration\Ecu\Ecud_CanIf.arxml                                        **
**  Configuration\Ecu\Ecud_CanNm.arxml                                        **
**  Configuration\Ecu\Ecud_CanSM.arxml                                        **
**  Configuration\Ecu\Ecud_CanTp.arxml                                        **
**  Configuration\Ecu\Ecud_CanTrcv.arxml                                      **
**  Configuration\Ecu\Ecud_Com.arxml                                          **
**  Configuration\Ecu\Ecud_ComM.arxml                                         **
**  Configuration\Ecu\Ecud_ComXf.arxml                                        **
**  Configuration\Ecu\Ecud_Crc.arxml                                          **
**  Configuration\Ecu\Ecud_CryIf.arxml                                        **
**  Configuration\Ecu\Ecud_Crypto_76_HaeModule.arxml                          **
**  Configuration\Ecu\Ecud_Csm.arxml                                          **
**  Configuration\Ecu\Ecud_Dcm.arxml                                          **
**  Configuration\Ecu\Ecud_Dem.arxml                                          **
**  Configuration\Ecu\Ecud_Det.arxml                                          **
**  Configuration\Ecu\Ecud_E2EXf.arxml                                        **
**  Configuration\Ecu\Ecud_EcuC.arxml                                         **
**  Configuration\Ecu\Ecud_EcuM.arxml                                         **
**  Configuration\Ecu\Ecud_FiM.arxml                                          **
**  Configuration\Ecu\Ecud_Fota.arxml                                         **
**  Configuration\Ecu\Ecud_IoHwAb.arxml                                       **
**  Configuration\Ecu\Ecud_LinIf.arxml                                        **
**  Configuration\Ecu\Ecud_LinSM.arxml                                        **
**  Configuration\Ecu\Ecud_LinTrcv.arxml                                      **
**  Configuration\Ecu\Ecud_MemIf.arxml                                        **
**  Configuration\Ecu\Ecud_Nm.arxml                                           **
**  Configuration\Ecu\Ecud_NvM.arxml                                          **
**  Configuration\Ecu\Ecud_Os.arxml                                           **
**  Configuration\Ecu\Ecud_PduR.arxml                                         **
**  Configuration\Ecu\Ecud_Rte.arxml                                          **
**  Configuration\Ecu\Ecud_StbM.arxml                                         **
**  Configuration\Ecu\Ecud_Tm.arxml                                           **
**  Configuration\Ecu\Ecud_WdgIf.arxml                                        **
**  Configuration\Ecu\Ecud_WdgM.arxml                                         **
**  Configuration\Ecu\Ecud_Wdg_76_Acw.arxml                                   **
**  Configuration\Ecu\Mcal\Ecud_Adc.arxml                                     **
**  Configuration\Ecu\Mcal\Ecud_Wdg.arxml                                     **
**  Configuration\System\Bswmd\Bswmd_Adc.arxml                                **
**  Configuration\System\Bswmd\Bswmd_BswM.arxml                               **
**  Configuration\System\Bswmd\Bswmd_Can.arxml                                **
**  Configuration\System\Bswmd\Bswmd_ComXf.arxml                              **
**  Configuration\System\Bswmd\Bswmd_Crypto.arxml                             **
**  Configuration\System\Bswmd\Bswmd_Dio.arxml                                **
**  Configuration\System\Bswmd\Bswmd_E2EXf.arxml                              **
**  Configuration\System\Bswmd\Bswmd_Fee.arxml                                **
**  Configuration\System\Bswmd\Bswmd_Fls.arxml                                **
**  Configuration\System\Bswmd\Bswmd_Gpt.arxml                                **
**  Configuration\System\Bswmd\Bswmd_Icu.arxml                                **
**  Configuration\System\Bswmd\Bswmd_Lin.arxml                                **
**  Configuration\System\Bswmd\Bswmd_Mcl.arxml                                **
**  Configuration\System\Bswmd\Bswmd_Mcu.arxml                                **
**  Configuration\System\Bswmd\Bswmd_Port.arxml                               **
**  Configuration\System\Bswmd\Bswmd_Pwm.arxml                                **
**  Configuration\System\Bswmd\Bswmd_Spi.arxml                                **
**  Configuration\System\Bswmd\Bswmd_Wdg.arxml                                **
**  Configuration\System\Composition\EcuExtract.arxml                         **
**  Configuration\System\DBImport\DataTypes\AUTOSAR_DataTypes.arxml           **
**  Configuration\System\DBImport\DataTypes\CanStack_DataTypes.arxml          **
**  Configuration\System\DBImport\DataTypes\ComStack_DataTypes.arxml          **
**  Configuration\System\DBImport\FD_CAN1.arxml                               **
**  Configuration\System\DBImport\LIN1.arxml                                  **
**  Configuration\System\DBImport\LIN2.arxml                                  **
**  Configuration\System\Swcd_App\App_Dcm.arxml                               **
**  Configuration\System\Swcd_App\App_Dem.arxml                               **
**  Configuration\System\Swcd_App\App_E2EXf.arxml                             **
**  Configuration\System\Swcd_App\App_Lin.arxml                               **
**  Configuration\System\Swcd_App\App_Mode.arxml                              **
**  Configuration\System\Swcd_App\App_WdgM.arxml                              **
**  Configuration\System\Swcd_Bsw\MODE_PortInterfaces.arxml                   **
**  Configuration\System\Swcd_Bsw\Swcd_Bsw_BswM.arxml                         **
**  Configuration\System\Swcd_Bsw\Swcd_Lin.arxml                              **
**  Configuration\System\Transformer\Transformer.arxml                        **
**  Generated\Bsw_Output\bswmd\Bswmd_CanCM.arxml                              **
**  Generated\Bsw_Output\bswmd\Bswmd_CanIf.arxml                              **
**  Generated\Bsw_Output\bswmd\Bswmd_CanNm.arxml                              **
**  Generated\Bsw_Output\bswmd\Bswmd_CanSM.arxml                              **
**  Generated\Bsw_Output\bswmd\Bswmd_CanTp.arxml                              **
**  Generated\Bsw_Output\bswmd\Bswmd_CanTrcv.arxml                            **
**  Generated\Bsw_Output\bswmd\Bswmd_Com.arxml                                **
**  Generated\Bsw_Output\bswmd\Bswmd_ComM.arxml                               **
**  Generated\Bsw_Output\bswmd\Bswmd_Crc.arxml                                **
**  Generated\Bsw_Output\bswmd\Bswmd_CryIf.arxml                              **
**  Generated\Bsw_Output\bswmd\Bswmd_Crypto_76_HaeModule.arxml                **
**  Generated\Bsw_Output\bswmd\Bswmd_Csm.arxml                                **
**  Generated\Bsw_Output\bswmd\Bswmd_Dcm.arxml                                **
**  Generated\Bsw_Output\bswmd\Bswmd_Dem.arxml                                **
**  Generated\Bsw_Output\bswmd\Bswmd_Det.arxml                                **
**  Generated\Bsw_Output\bswmd\Bswmd_EcuM.arxml                               **
**  Generated\Bsw_Output\bswmd\Bswmd_FiM.arxml                                **
**  Generated\Bsw_Output\bswmd\Bswmd_Fota.arxml                               **
**  Generated\Bsw_Output\bswmd\Bswmd_IoHwAb.arxml                             **
**  Generated\Bsw_Output\bswmd\Bswmd_IpduM.arxml                              **
**  Generated\Bsw_Output\bswmd\Bswmd_KeyM.arxml                               **
**  Generated\Bsw_Output\bswmd\Bswmd_LinIf.arxml                              **
**  Generated\Bsw_Output\bswmd\Bswmd_LinSM.arxml                              **
**  Generated\Bsw_Output\bswmd\Bswmd_LinTrcv.arxml                            **
**  Generated\Bsw_Output\bswmd\Bswmd_MemIf.arxml                              **
**  Generated\Bsw_Output\bswmd\Bswmd_Mem_76_Pfls.arxml                        **
**  Generated\Bsw_Output\bswmd\Bswmd_Nm.arxml                                 **
**  Generated\Bsw_Output\bswmd\Bswmd_NvM.arxml                                **
**  Generated\Bsw_Output\bswmd\Bswmd_Os.arxml                                 **
**  Generated\Bsw_Output\bswmd\Bswmd_PduR.arxml                               **
**  Generated\Bsw_Output\bswmd\Bswmd_StbM.arxml                               **
**  Generated\Bsw_Output\bswmd\Bswmd_Tm.arxml                                 **
**  Generated\Bsw_Output\bswmd\Bswmd_WdgIf.arxml                              **
**  Generated\Bsw_Output\bswmd\Bswmd_WdgM.arxml                               **
**  Generated\Bsw_Output\bswmd\Bswmd_Wdg_76_Acw.arxml                         **
**  Generated\Bsw_Output\swcd\Swcd_Bsw_ComM.arxml                             **
**  Generated\Bsw_Output\swcd\Swcd_Bsw_Csm.arxml                              **
**  Generated\Bsw_Output\swcd\Swcd_Bsw_Dcm.arxml                              **
**  Generated\Bsw_Output\swcd\Swcd_Bsw_Dem.arxml                              **
**  Generated\Bsw_Output\swcd\Swcd_Bsw_Det.arxml                              **
**  Generated\Bsw_Output\swcd\Swcd_Bsw_EcuM.arxml                             **
**  Generated\Bsw_Output\swcd\Swcd_Bsw_FiM.arxml                              **
**  Generated\Bsw_Output\swcd\Swcd_Bsw_IoHwAb.arxml                           **
**  Generated\Bsw_Output\swcd\Swcd_Bsw_KeyM.arxml                             **
**  Generated\Bsw_Output\swcd\Swcd_Bsw_NvM.arxml                              **
**  Generated\Bsw_Output\swcd\Swcd_Bsw_Os.arxml                               **
**  Generated\Bsw_Output\swcd\Swcd_Bsw_StbM.arxml                             **
**  Generated\Bsw_Output\swcd\Swcd_Bsw_WdgM.arxml                             **
**  Generated\Bsw_Output\swcd\Swcd_Fota.arxml                                 **
**  Static_Code\Modules\EcuM_R44\generator\EcuM_PortInterface.arxml           **
**  Static_Code\Modules\Rte_R44\generator\SafeRTE_PDF.arxml                   **
**                                                                            **
**  Generator version : 1.8.0.0                                               **
**                                                                            **
**  NOTE: This is a generated file, Please DO NOT EDIT manually!              **
**                                                                           **/

/******************************************************************************/
/*                              Header Inclusion                              */
/******************************************************************************/
#include "Rte_User.h"
#include "Rte_Static.h"
#include "Os.h"

/* polyspace-begin MISRA-C3:5.8 [Justified:Low] "Rte is using 'Data' as common name for input parameter in almost functions" */

/******************************************************************************/
/*                               RTE User APIs                                */
/******************************************************************************/
/* Rte_MemCpy API is used to copy the data */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

typedef unsigned long long RTE_WRITETYPE;

/* polyspace-begin MISRA-C3:D4.9 [Justified:Low] "Function like macro is used to improve performance" */

/* little-endian */

#if (!defined(CPU_BYTE_ORDER) || !defined(LOW_BYTE_FIRST) || (CPU_BYTE_ORDER == LOW_BYTE_FIRST))

#define RTE_WORD_LEFTSIDE(WORD, SHIFTSIZE) ((WORD) >> (SHIFTSIZE))
#define RTE_WORD_RIGHTSIDE(WORD, SHIFTSIZE) ((WORD) << (SHIFTSIZE))

/* big-endian */

#else

#define RTE_WORD_LEFTSIDE(WORD, SHIFTSIZE) ((WORD) << (SHIFTSIZE))
#define RTE_WORD_RIGHTSIDE(WORD, SHIFTSIZE) ((WORD) >> (SHIFTSIZE))

#endif

/* polyspace-end MISRA-C3:D4.9 [Justified:Low] "Function like macro is used to improve performance" */

#define RTE_WRITESIZE sizeof(RTE_WRITETYPE)
#define RTE_THREE 3U
#define RTE_FOUR  4U
#define RTE_EIGHT 8U

/*LDRA_INSPECTED 65 D ; Source: MISRA:2012 R.2.2 */
/*LDRA_INSPECTED 76 D ; Source: MISRA:2012 R.2.1 */
FUNC(void, RTE_CODE) Rte_MemCpy(P2VAR(void, AUTOMATIC, RTE_DATA) Lpt_dst, P2CONST(void, AUTOMATIC, RTE_DATA) Lpt_src, CONST(uint32, RTE_DATA) Lu32_Size)
{
  /* Copy destination pointer */
  P2VAR(uint8, AUTOMATIC, RTE_DATA) Lpt_dest = NULL_PTR;

  /* Copy source pointer */
  P2CONST(uint8, AUTOMATIC, RTE_CONST) Lpt_srce = NULL_PTR;

  /* Copy size */
  VAR(uint32, RTE_DATA) Lu32_cnt = 0U;

  /* Copy length for local */
  VAR(uint32, RTE_DATA) Lu32_len = 0U;

  /* Destination align diff */ 
  VAR(uint8, RTE_DATA) Lu8_dst = 0U;

  /* Source align diff */ 
  VAR(uint8, RTE_DATA) Lu8_src = 0U;

  /* Copy Data */
  VAR(uint32, RTE_DATA) Lu32_data = 0U;

  /* Copy left side Data */
  VAR(uint32, RTE_DATA) Lu32_Ldata = 0U;

  /* Copy right side Data */
  VAR(uint32, RTE_DATA) Lu32_Rdata = 0U;

  Lu32_cnt = Lu32_Size;

  /* Null Pointer is checked before Rte_MemCpy is called */
  if((Lpt_dst == Lpt_src) || (Lu32_cnt == RTE_ZERO))
  {
    /* Do nothing */
  }
  else
  {
    /* polyspace-begin MISRA-C3:11.5 [Justified:Low] "Cast pointers into more strictly aligned pointer for memory copy." */
    /* polyspace-begin CERT-C:EXP36-C [Justified:Low] "Cast pointers into more strictly aligned pointer for memory copy." */
    Lpt_dest = (uint8 *)Lpt_dst;
    /* polyspace-end CERT-C:EXP36-C [Justified:Low] "Cast pointers into more strictly aligned pointer for memory copy." */
    Lpt_srce = (const uint8 *)Lpt_src;
    /* polyspace-end MISRA-C3:11.5 [Justified:Low] "Cast pointers into more strictly aligned pointer for memory copy." */

    /* polyspace +1 MISRA-C3:11.4 [Justified:Low] "The integer value represents the misalignment. The value is used for 4bytes-alignment." */
    Lu8_dst = (uint8)((uint32)Lpt_dest & RTE_THREE); 

    /* Copy data by 1 byte until destination address is 4bytes-aligned */
    if((Lu32_cnt >= RTE_FOUR) && (Lu8_dst != RTE_ZERO))
    {
      Lu32_len = (uint32)RTE_FOUR - Lu8_dst;
      Lu32_cnt = Lu32_cnt - Lu32_len;
      while(Lu32_len != RTE_ZERO)
      {
        /*LDRA_INSPECTED 45 D ; Source: MISRA:2012 D.4.1 */
        *Lpt_dest = *Lpt_srce;
        Lpt_dest++;
        Lpt_srce++;
        Lu32_len--;
      }
    }

    /* polyspace +1 MISRA-C3:11.4 [Justified:Low] "The integer value represents the misalignment. The value is used for 4bytes-alignment." */
    Lu8_src = (uint8)((uint32)Lpt_srce & RTE_THREE); 

    /* Make data from source address and Copy the data if source address is not 4bytes-aligned */
    if((Lu32_cnt >= RTE_FOUR) && (Lu8_src != RTE_ZERO))
    {
      /* Byte copy for first 4 bytes - To avoid accessing the address out of range */
      for (Lu32_len = RTE_FOUR; Lu32_len != RTE_ZERO; Lu32_len--)
      {
        /*LDRA_INSPECTED 45 D ; Source: MISRA:2012 D.4.1 */
        *Lpt_dest = *Lpt_srce;
        Lpt_dest++;
        Lpt_srce++;
        Lu32_cnt--;
      }

      if (Lu32_cnt >= RTE_EIGHT)
      {
        /* polyspace +1 CERT-C:EXP39-C MISRA-C3:11.3 MISRA-C3:18.4 [Justified:Low] "Pointer arithmatic used to achieve better throughput." */
        Lu32_Ldata = RTE_WORD_LEFTSIDE((*(const uint32 *)(Lpt_srce - Lu8_src)), (RTE_EIGHT * Lu8_src));

        for(Lu32_len = Lu32_cnt / RTE_FOUR; Lu32_len != RTE_ZERO; Lu32_len--)
        {
          /* polyspace-begin RTE:IDP [Not a defect:Low] "Dereferenced pointer is used to achieve better throughput."*/
          /* polyspace +1 CERT-C:EXP39-C MISRA-C3:11.3 MISRA-C3:18.4 [Justified:Low] "Pointer arithmatic used to achieve better throughput." */
          Lu32_data = *(const uint32 *)((Lpt_srce + RTE_FOUR) - Lu8_src);
          /* polyspace-end RTE:IDP [Not a defect:Low] "Dereferenced pointer is used to achieve better throughput."*/
          Lu32_Rdata = RTE_WORD_RIGHTSIDE(Lu32_data, (RTE_EIGHT * (RTE_FOUR - Lu8_src)));

          /* polyspace +1 CERT-C:EXP39-C MISRA-C3:11.3 [Justified:Low] "This typecast is needed in order to store the value combined with L and R data" */
          *(uint32 *)Lpt_dest = Lu32_Ldata | Lu32_Rdata;

          Lu32_Ldata = RTE_WORD_LEFTSIDE(Lu32_data, (RTE_EIGHT * Lu8_src));

          /* polyspace +2 MISRA-C3:18.4 [Justified:Low] "Pointer arithmatic used to achieve better throughput." */
          Lpt_dest += RTE_FOUR;
          Lpt_srce += RTE_FOUR;
          Lu32_cnt -= RTE_FOUR;
        }
      }

      for (Lu32_len = Lu32_cnt; Lu32_len != RTE_ZERO; Lu32_len--)
      {
        /*LDRA_INSPECTED 45 D ; Source: MISRA:2012 D.4.1 */
        /* polyspace +1 RTE:IDP [Not a defect:Low] "Dereferenced pointer is used to achieve better throughput."*/
        *Lpt_dest = *Lpt_srce;
        Lpt_dest++;
        Lpt_srce++;
      }
    }

    /* destination & source address is 4-byte aligned */
    else
    {
      /* Copy in RTE_WRITESIZE units  */
      for(Lu32_len = Lu32_cnt / RTE_WRITESIZE; Lu32_len != RTE_ZERO; Lu32_len--)
      {
        /*LDRA_INSPECTED 45 D ; Source: MISRA:2012 D.4.1 */
        /* polyspace-begin RTE:IDP [Not a defect:Low] "Dereferenced pointer is used to achieve better throughput."*/
        /* polyspace +1 CERT-C:EXP39-C MISRA-C3:11.3 [Justified:Low] "A cast used to achieve better throughput." */
        *(RTE_WRITETYPE *)Lpt_dest = *(const RTE_WRITETYPE *)Lpt_srce;
        /* polyspace-end RTE:IDP [Not a defect:Low] "Dereferenced pointer is used to achieve better throughput."*/

        /* polyspace +2 MISRA-C3:18.4 [Justified:Low] "Pointer arithmatic used to achieve better throughput." */
        Lpt_dest += RTE_WRITESIZE;
        Lpt_srce += RTE_WRITESIZE;
      }

      /* Copy remainder after copying RTE_WRITESIZE units */
      for(Lu32_len = Lu32_cnt % RTE_WRITESIZE; Lu32_len != RTE_ZERO; Lu32_len--)
      {
        /*LDRA_INSPECTED 45 D ; Source: MISRA:2012 D.4.1 */
        /* polyspace +1 RTE:IDP [Not a defect:Low] "Dereferenced pointer is used to achieve better throughput."*/
        *Lpt_dest = *Lpt_srce;
        Lpt_dest++;
        Lpt_srce++;
      }
    }
  }
}

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/* Rte_MemSet API is used to set the data into destination address */
/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_START_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/*LDRA_INSPECTED 65 D ; Source: MISRA:2012 R.2.2 */
/*LDRA_INSPECTED 76 D ; Source: MISRA:2012 R.2.1 */
FUNC(void, RTE_CODE) Rte_MemSet(P2VAR(void, AUTOMATIC, RTE_DATA) Lpt_dst, VAR(uint8, RTE_VAR) Data, CONST(uint32, RTE_DATA) Lu32_Size)
{
  /* Copy destination pointer */
  P2VAR(uint8, AUTOMATIC, RTE_DATA) Lpt_dest = NULL_PTR;
  VAR(uint32, RTE_DATA) Lu32_len = 0;

  /* Copy size */
  VAR(uint32, RTE_DATA) Lu32_cnt = 0;

  /* Destination align diff */ 
  VAR(uint8, RTE_DATA) Lu8_dst = 0;

  VAR(RTE_WRITETYPE, RTE_DATA) Ldt_Data = 0;
  VAR(RTE_WRITETYPE, RTE_DATA) Ldt_tmp = 0;

  Lu32_cnt = Lu32_Size;

  if((Lpt_dst == NULL_PTR) || (Lu32_cnt == RTE_ZERO))
  {
    /* Do nothing */
  }
  else
  {
    /* polyspace-begin MISRA-C3:11.5 [Justified:Low] "Cast pointers into more strictly aligned pointer for memory copy." */
    /* polyspace-begin CERT-C:EXP36-C [Justified:Low] "Cast pointers into more strictly aligned pointer for memory set." */
    Lpt_dest = (uint8 *)Lpt_dst;
    /* polyspace-end CERT-C:EXP36-C [Justified:Low] "Cast pointers into more strictly aligned pointer for memory set." */
    /* polyspace-end MISRA-C3:11.5 [Justified:Low] "Cast pointers into more strictly aligned pointer for memory copy." */

    /* polyspace +1 MISRA-C3:11.4 [Justified:Low] "The integer value represents the misalignment. The value is used for 4bytes-alignment." */
    Lu8_dst = (uint8)((uint32)Lpt_dest & RTE_THREE); 

    /* Copy Data until it makes 4bytes-align */
    if ((Lu32_cnt >= RTE_FOUR) && (Lu8_dst != RTE_ZERO))
    {
      Lu32_len = (uint32)RTE_FOUR - Lu8_dst;
      Lu32_cnt = Lu32_cnt - Lu32_len;
      while(Lu32_len != RTE_ZERO)
      {
        /*LDRA_INSPECTED 45 D ; Source: MISRA:2012 D.4.1 */
        *Lpt_dest = Data;
        Lpt_dest++;
        Lu32_len--;
      }
    }

    /* Copy Data  */
    if(Lu32_cnt >= RTE_WRITESIZE)
    {
      Ldt_tmp = (RTE_WRITETYPE)Data;
      Ldt_Data = Ldt_tmp;

      for(Lu32_len = RTE_ONE; Lu32_len < RTE_WRITESIZE; Lu32_len++)
      {
        Ldt_tmp = (Ldt_tmp << RTE_EIGHT); 
        Ldt_Data |= Ldt_tmp;
      }

      /* Copy in RTE_WRITESIZE units 
       * : RTE_WRITETYPE and RTE_WRITESIZE has MCU core dependency */
      for(Lu32_len = Lu32_cnt / RTE_WRITESIZE; Lu32_len != RTE_ZERO; Lu32_len--)
      {
        /*LDRA_INSPECTED 45 D ; Source: MISRA:2012 D.4.1 */
        /* polyspace-begin RTE:IDP [Not a defect:Low] "Dereferenced pointer is used to achieve better throughput."*/
        /* polyspace +1 CERT-C:EXP39-C MISRA-C3:11.3 [Justified:Low] "A cast used to achieve better throughput." */
        *(RTE_WRITETYPE *)Lpt_dest = Ldt_Data;
        /* polyspace-end RTE:IDP [Not a defect:Low] "Dereferenced pointer is used to achieve better throughput."*/
        /* polyspace +1 MISRA-C3:18.4 [Justified:Low] "Pointer arithmatic used to achieve better throughput." */
        Lpt_dest += RTE_WRITESIZE;
      }
    }
      /* Copy remainder by one byte size */
    for(Lu32_len = Lu32_cnt % RTE_WRITESIZE; Lu32_len != RTE_ZERO; Lu32_len--)
    {
      /*LDRA_INSPECTED 45 D ; Source: MISRA:2012 D.4.1 */
      /* polyspace +1 RTE:IDP [Not a defect:Low] "Dereferenced pointer is used to achieve better throughput."*/
      *Lpt_dest = Data;
      Lpt_dest++;
    }
  }
}

/*LDRA_INSPECTED 580 S ; Source: MISRA:2012 R.1.1,R.20.4 */
/*LDRA_INSPECTED 628 S ; Source: MISRA:2012 R.2.5 */
/*LDRA_INSPECTED 338 S ; Source: MISRA:2012 R.20.1 */
#define RTE_COMMON_STOP_SEC_CODE_ASIL_D
#include "Rte_MemMap.h"

/******************************************************************************/
/*                              End of the file                               */
/******************************************************************************/
