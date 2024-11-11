/*******************************************************************************
**                                                                            **
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**                                                                            **
**  Confidential Proprietary Information. Distribution Limited.               **
**  This source code is permitted to be used only in projects contracted      **
**  with Hyundai Autoever, and any other use is prohibited.                   **
**  If you use it for other purposes or change the source code,               **
**  you may take legal responsibility.                                        **
**  In this case, There is no warranty and technical support.                 **
**                                                                            **
**  SRC-MODULE: Com_Pack.c                                                    **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Com Module                                            **
**                                                                            **
**  PURPOSE   : Provision of Packing, invalidate and update functions         **
**              functionality.                                                **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By          Description                            **
********************************************************************************
** 1.1.11.0  27-Oct-2023   PhucNHM     BUGCLASSIC-701                         **
** 1.1.9.0   28-Mar-2023   PhucNHM     CP44-267                               **
** 1.1.5.0   12-Oct-2022   DuyNHP2     CP44-811                               **
** 1.1.4     02-Jun-2022   DuyNHP2     R44-Redmine #27636                     **
** 1.1.3.1   21-Jun-2022   SMKwon      CP44-109                               **
** 1.1.2     25-Apr-2022   PhucNHM     R44-Redmine #25654                     **
** 1.1.1     25-Mar-2022   PhuPV10     R44-Redmine #25573 #25073              **
** 1.1.0     10-Feb-2022   PhucNHM     R44-Redmine #19316 #23495 #23725       **
**                                                 #23982 #24211              **
** 1.0.1     28-Sep-2021   DuyNGB      R44-Redmine #20139                     **
** 1.0.0     04-Dec-2020   SMKwon      Initial Version                        **
*******************************************************************************/
/* polyspace-begin MISRA2012:D4.14 [Not a defect:Low] "LpTxPack and LpSigDataPtr pointers were checked outside packing functions" */
/* polyspace-begin MISRA2012:11.5 [Not a defect:Low] "Following Com_SWS_00197 and Com_SWS_00198, data pointer of Com_Send/ReceiveSignal is void, so the casting to another type is inevitable." */
/* polyspace-begin RTE:IDP [Not a defect:Low] "NULL pointer was checked by generator" */
/* polyspace-begin RTE:SHF [Not a defect:Low] "Shift amount is inside its bounds. This is assured by generator */
/* polyspace-begin CERT-C:EXP36-C [Justified:Low] "Following Com_SWS_00197 and Com_SWS_00198, data pointer of Com_Send/ReceiveSignal is void, so the casting to another type is inevitable." */
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

#include "Com.h"          /* Com header file */
#include "Com_Pack.h"     /* Com Pack header file */
#include "SchM_Com.h"     /* SchM Com header file */
#include "string.h"

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

/*******************************************************************************
** Function Name        : Com_PackOneByte                                     **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function packs signal of size less than or     **
**                        equal to 8 bit into the I-PDU buffer.               **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same signal.                  **
**                        Reentrant for different signals.                    **
**                                                                            **
** Input Parameters     : LpSigDataPtr                                        **
**                                                                            **
** InOut parameter      : LpTxPack                                            **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : SchM_Enter_XXX()           **
**                                                 SchM_Exit_XXX()            **
*******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SRS_Com_02094*/
FUNC(void, COM_CODE) Com_PackOneByte
  (P2CONST(Com_TxPack, AUTOMATIC, COM_CONST) LpTxPack,
  P2CONST (void, AUTOMATIC, COM_CONST) LpSigDataPtr)
{
  /* @Trace: Com_SUD_API_00716 */
  /* @Trace: SWS_Com_00675, SRS_Com_02078 */
  uint8 LucApplSignal;
  uint8 LucIpduByte;
  uint8 LucStartMask;
  /* Get the the value of SignalDataPtr to local application variable */
  LucApplSignal = *((P2CONST(uint8, AUTOMATIC, COM_CONST)) LpSigDataPtr);
  /* Shift the application signal value to get signal start position in
  an I-PDU */
  /* polyspace +1 RTE:OVFL [Not a defect:Low] "Value won't overflow. This is assured by generator" */
  LucApplSignal = (uint8)(LucApplSignal << (LpTxPack->ucNoOfShiftBit));
  /* Enter protection area */
  #if(COM_TX_INTERRUPT_BASED_PROCESS == STD_OFF)
  SchM_Enter_Com_TX_EXT_SIG_DATA_PROTECTION_AREA();
  #endif
  /* Get the I-PDU buffer value into local I-PDU variable */
  /* polyspace +1 RTE:NIV [Not a defect:Low] "Variable initialized with configuration data" */
  LucIpduByte = *(P2VAR(uint8, AUTOMATIC, COM_VAR))(LpTxPack->pWrBuffer);
  /* Get the start mask the value into local variable */
  LucStartMask = LpTxPack->ucWrStartMask;
  /* Apply the start mask value to I-PDU variable to clear signal value */
  LucIpduByte &= LucStartMask;
  /* Apply start mask value to local application variable and
  move local application variable value to local I-PDU variable */
  LucIpduByte |= LucApplSignal & ((uint8)(~LucStartMask));
  /* Copy the local I-PDU variable value to I-PDU buffer */
  *((P2VAR(uint8, AUTOMATIC, COM_VAR)) LpTxPack->pWrBuffer) = LucIpduByte;
  /* Exit protection area */
  #if(COM_TX_INTERRUPT_BASED_PROCESS == STD_OFF)
  SchM_Exit_Com_TX_EXT_SIG_DATA_PROTECTION_AREA();
  #endif
}
/* @Traceability END -- SRS: SWS_Com_00675, SRS_Com_02078 */
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Com_PackBytes                                       **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function packs the signal which spread across  **
**                        four bytes in an I-PDU.                             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same signal.                  **
**                        Reentrant for different signals.                    **
**                                                                            **
** Input Parameters     : LpTxPack, LpSigDataPtr                              **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : SchM_Enter_XXX()           **
**                                                 SchM_Exit_XXX()            **
*******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"

FUNC(void, COM_CODE) Com_PackBytes
  (P2CONST(Com_TxPack, AUTOMATIC, COM_CONST) LpTxPack,
  P2CONST (void, AUTOMATIC, COM_CONST) LpSigDataPtr)
{
  /* @Trace: Com_SUD_API_00717 */
  /* @Trace: SRS_Com_02078, SWS_Com_00675, SWS_Com_00007, SWS_Com_00472 */
  P2VAR(uint8, AUTOMATIC, COM_VAR) LpAppSigPtr;
  P2VAR(uint8, AUTOMATIC, COM_VAR) LpWrBuffer;
  Com_MIdWord_Access LunApplSignal;
  uint8 LucSizeOrData;
  uint8 LucNoOfByte;
  uint8 LucEndMask;
  /* Get the pointer to I-PDU buffer */
  LpWrBuffer = (LpTxPack->pWrBuffer);
  /* Get the number of bytes of data */
  LucNoOfByte = (uint8)(LpTxPack->ddSigTypeOrSize);
  /* Get the signal size */
  LucSizeOrData = (LucNoOfByte & COM_SIG_SIZE_MASK_VALUE);
  /* Get the number of bytes that signal spread across */
  LucNoOfByte = LucNoOfByte & COM_SIG_BYTE_MASK_VALUE;
  /* Initialize double word variable to zero */
  LunApplSignal.whole_dword = COM_ZERO;
  /* Check whether signal size is 8 bit */
  if(COM_SIZE_8 == LucSizeOrData)
  {
    /* @Trace: Com_SUD_API_00718 */
    /*  Get the signal value to lower byte of double word variable */
    LunApplSignal.byte_val.BO_Byte[COM_DWORD_LS_BYTE_IDX] =
                    *(P2CONST(uint8, AUTOMATIC, COM_CONST)) LpSigDataPtr;
  }
  /* Check whether signal size is 16 bit */
  else if(COM_SIZE_16 == LucSizeOrData)
  {
    /* @Trace: Com_SUD_API_00719 */
    /* Get the signal value to lower word of double word variable */
    LunApplSignal.word_val.BO_Word[COM_DWORD_LS_WORD_IDX] =
                   *(P2CONST(uint16, AUTOMATIC, COM_CONST)) LpSigDataPtr;
  }
  else
  {
    /* @Trace: Com_SUD_API_00720 */
    /* Get the the signal value to double word variable */
    LunApplSignal.whole_dword =
                  *(P2CONST(uint32, AUTOMATIC, COM_CONST)) LpSigDataPtr;
  }
  /* @Trace: Com_SUD_API_00721 */
  /* Shift left the double word variable value by number of shift bits */
  LunApplSignal.whole_dword <<= (LpTxPack->ucNoOfShiftBit);
  /* Get the pointer to lower byte of double word variable data */
  LpAppSigPtr = (P2VAR(uint8, AUTOMATIC, COM_VAR))
    &LunApplSignal.byte_val.BO_Byte[COM_DWORD_LS_BYTE_IDX];
  /* Get the end mask value */
  LucEndMask = LpTxPack->ucWrEndMask;
  /* Decrement the signal size by one */
  LucNoOfByte--;
  /* Enter protection area */
  #if(COM_TX_INTERRUPT_BASED_PROCESS == STD_OFF)
  SchM_Enter_Com_TX_EXT_SIG_DATA_PROTECTION_AREA();
  #endif
  /* Get the data from I-PDU buffer to local variable */
  /* polyspace +1 RTE:NIV [Not a defect:Low] "Variable initialized with configuration data" */
  LucSizeOrData = *LpWrBuffer;
  /* Clear signal data from I-PDU buffer by applying start mask */
  LucSizeOrData &= LpTxPack->ucWrStartMask;
  /* Write data from application buffer to local I-PDU buffer */
  LucSizeOrData |= *LpAppSigPtr;
  /* Copy local I-PDU buffer data into I-PDU buffer */
  *LpWrBuffer = LucSizeOrData;
  #if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)
  /* @Trace: Com_SUD_API_01600 */
  /* Decrement application signal pointer */
  LpAppSigPtr--;
  /* Decrement I-PDU buffer pointer */
  LpWrBuffer--;
  #else
  /* @Trace: Com_SUD_API_01601 */
  /* Increment application signal pointer */
  LpAppSigPtr++;
  /* Increment I-PDU buffer pointer */
  LpWrBuffer++;
  #endif
  /* Loop for number of bytes of data */
  while(LucNoOfByte != COM_ONE)
  {
    /* @Trace: Com_SUD_API_00722 */
    /* Copy data from application signal pointer to I-PDU buffer */
    *LpWrBuffer = *LpAppSigPtr;
    #if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)
    /* @Trace: Com_SUD_API_01602 */
    /* Decrement application signal pointer */
    LpAppSigPtr--;
    /* Decrement I-PDU buffer pointer */
    LpWrBuffer--;
    #else
    /* @Trace: Com_SUD_API_01603 */
    /* Increment application signal pointer */
    LpAppSigPtr++;
    /* Increment I-PDU buffer pointer */
    LpWrBuffer++;
    #endif
    /* @Trace: Com_SUD_API_01604 */
    LucNoOfByte--;
  }
  /* @Trace: Com_SUD_API_00723 */
  /* Get the first byte of I-PDU buffer data to local I-PDU variable */
  /* polyspace +1 RTE:NIV [Not a defect:Low] "Variable initialized with configuration data" */
  LucSizeOrData = *LpWrBuffer;
  /* Clear local I-PDU variable data by applying end mask */
  LucSizeOrData &= LucEndMask;
  /* Get application data value by applying negate mask to local I-PDU variable
  to clear unoccupied area and write to I-PDU buffer  */
  LucSizeOrData |= *LpAppSigPtr & ((uint8)(~LucEndMask));
  /* Store local I-PDU buffer variable to I-PDU buffer */
  *LpWrBuffer = LucSizeOrData;
  /* Exit protection area */
  #if(COM_TX_INTERRUPT_BASED_PROCESS == STD_OFF)
  SchM_Exit_Com_TX_EXT_SIG_DATA_PROTECTION_AREA();
  #endif
}
/* @Traceability END -- SRS: SRS_Com_02078, SWS_Com_00675, SWS_Com_00007, 
SWS_Com_00472 */
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Com_PackFiveBytes                                   **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function packs the signal which spread across  **
**                        five bytes in an I-PDU.                             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same signal.                  **
**                        Reentrant for different signals.                    **
**                                                                            **
** Input Parameters     : LpTxPack, LpSigDataPtr                              **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : SchM_Enter_XXX()           **
**                                                 SchM_Exit_XXX()            **
*******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE) Com_PackFiveBytes
(P2CONST(Com_TxPack, AUTOMATIC, COM_CONST) LpTxPack,
                    P2CONST (void, AUTOMATIC, COM_CONST) LpSigDataPtr)
{
  /* @Trace: Com_SUD_API_00724 */
   /* @Trace: SWS_Com_00675, SWS_Com_00007 */
  P2VAR(uint8, AUTOMATIC, COM_VAR) LpWrBuffer;
  P2VAR(uint8, AUTOMATIC, COM_VAR) LpAppSigPtr;
  Com_MIdWord_Access LunApplSignal;
  Com_MIWord_Access LunApplSigHi;
  uint8 LucShiftOrData;
  uint8 LucEndMask;
  /* Get the local pointer to I-PDU buffer */
  LpWrBuffer =
  (P2VAR(uint8, AUTOMATIC, COM_VAR)) LpTxPack->pWrBuffer;
  /* Copy signal data to double word variable */
  LunApplSignal.whole_dword = *(P2CONST(uint32, AUTOMATIC, COM_CONST))
                                                                   LpSigDataPtr;
  /* Get the number of shift bits to a local variable */
  LucShiftOrData = LpTxPack->ucNoOfShiftBit;
  /* Get the end mask value to a local variable */
  LucEndMask = LpTxPack->ucWrEndMask;
  /* Copy the higher byte of double word variable to the lower byte of word
  variable */
  LunApplSigHi.whole_word = 
    (uint8)LunApplSignal.byte_val.BO_Byte[COM_DWORD_MS_BYTE_IDX];
  /* Shift the double word variable left by the number of shift bits to get
  start position of signal in I-PDU */
  LunApplSignal.whole_dword <<= LucShiftOrData;
  /* Shift the word variable left by the number of shift bits */
  /* polyspace +2 RTE:OVFL [Not a defect:Low] "Value won't overflow. This is assured by generator" */
  LunApplSigHi.whole_word =
    (uint16)((LunApplSigHi.whole_word) << LucShiftOrData);
  /* Apply negate end mask to clear unwanted data in higher byte of word
  variable */
  LunApplSigHi.byte_val.BO_Byte[COM_WORD_MS_BYTE_IDX] &= (uint8)(~(LucEndMask));
  /* Get the pointer to lower byte of the double word variable and assign to
  local application signal pointer */
  LpAppSigPtr = (P2VAR(uint8, AUTOMATIC, COM_VAR))
    &LunApplSignal.byte_val.BO_Byte[COM_DWORD_LS_BYTE_IDX];
  /* Enter protection area */
  #if(COM_TX_INTERRUPT_BASED_PROCESS == STD_OFF)
  SchM_Enter_Com_TX_EXT_SIG_DATA_PROTECTION_AREA();
  #endif
  /* Get the data from I-PDU buffer pointer to local variable */
  LucShiftOrData = *LpWrBuffer;
  /* Clear signal data from local I-PDU buffer variable by applying start
  mask */
  LucShiftOrData &= LpTxPack->ucWrStartMask;
  /* Write data from application buffer pointer to a local I-PDU buffer
  variable */
  LucShiftOrData |= *LpAppSigPtr;
  /* Copy data into I-PDU buffer from local I-PDU buffer variable */
  *LpWrBuffer = LucShiftOrData;
  #if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)
  /* @Trace: Com_SUD_API_01605 */
  /* Decrement application signal pointer */
  LpAppSigPtr--;
  /* Decrement I-PDU buffer pointer */
  LpWrBuffer--;
  #else
  /* @Trace: Com_SUD_API_01606 */
  /* Increment application signal pointer */
  LpAppSigPtr++;
  /* Increment I-PDU buffer pointer */
  LpWrBuffer++;
  #endif
  /* @Trace: Com_SUD_API_01607 */
  /* Get the number of bytes of data */
  LucShiftOrData = COM_FOUR;
  /* Loop for number of bytes of data */
  do
  {
    /* @Trace: Com_SUD_API_00725 */
    /* Copy data from application signal pointer to I-PDU buffer */
    *LpWrBuffer = *LpAppSigPtr;
    #if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)
    /* @Trace: Com_SUD_API_01608 */
    /* Decrement application signal pointer */
    LpAppSigPtr--;
    /* Decrement I-PDU buffer pointer */
    LpWrBuffer--;
    #else
    /* @Trace: Com_SUD_API_01609 */
    /* Increment application signal pointer */
    LpAppSigPtr++;
    /* Increment I-PDU buffer pointer */
    LpWrBuffer++;
    #endif
    /* @Trace: Com_SUD_API_01610 */
    /* Decrement the number of bytes of data */
    LucShiftOrData--;
  }while(LucShiftOrData != COM_ONE);
  /* @Trace: Com_SUD_API_00726 */
  /* Get the data from I-PDU buffer pointer to local I-PDU buffer variable */
  LucShiftOrData = *LpWrBuffer;
  /*Clear signal data from the local I-PDU buffer variable by applying end mask
  to it */
  LucShiftOrData &= LucEndMask;
  /* Copy higher byte data of word variable to local I-PDU buffer */
  LucShiftOrData |= (LunApplSigHi.byte_val.BO_Byte[COM_WORD_MS_BYTE_IDX]);
  /* Store the local I-PDU buffer data into local I-PDU buffer variable */
  *LpWrBuffer = LucShiftOrData;
  /* Exit protection area */
  #if(COM_TX_INTERRUPT_BASED_PROCESS == STD_OFF)
  SchM_Exit_Com_TX_EXT_SIG_DATA_PROTECTION_AREA();
  #endif
}
/* @Traceability END -- SRS: SWS_Com_00675, SWS_Com_00007 */
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Com_PackByteOrdering                                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function packs the signal which spread across  **
**                        four bytes in an I-PDU and does the endianness      **
**                        conversion.                                         **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same signal.                  **
**                        Reentrant for different signals.                    **
**                                                                            **
** Input Parameters     : LpTxPack, LpSigDataPtr                              **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : SchM_Enter_XXX()           **
**                                                 SchM_Exit_XXX()            **
*******************************************************************************/

#define COM_START_SEC_CODE
#include "MemMap.h"

FUNC(void, COM_CODE) Com_PackByteOrdering
(P2CONST(Com_TxPack, AUTOMATIC, COM_CONST) LpTxPack,
  P2CONST (void, AUTOMATIC, COM_CONST) LpSigDataPtr)
{
  /* @Trace: Com_SUD_API_00727 */
   /* @Trace: SWS_Com_00675, SWS_Com_00007*/
  P2VAR(uint8, AUTOMATIC, COM_VAR) LpAppSigPtr;
  P2VAR(uint8, AUTOMATIC, COM_VAR) LpWrBuffer;
  Com_MIdWord_Access LunApplSignal;
  uint8 LucSizeOrData;
  uint8 LucNoOfByte;
  uint8 LucEndMask;
  /* Get the pointer to I-PDU buffer to a local variable */
  LpWrBuffer = (LpTxPack->pWrBuffer);
  #if (CPU_BYTE_ORDER == LOW_BYTE_FIRST)
  /* Get signal actual type */
  uint8 LucType = LpTxPack->ucType;
  /* Modify LpWrBuffer pointer to point to correct MSB position in case
   * network byte order is different from system byte order */
  /* polyspace-begin MISRA2012:18.4 [Justified:Low] "Pointer access accepted for buffer processing. There is no safety impact" */
  if ((LucType == COM_SIG_TYPE_UINT16) ||
    (LucType == COM_SIG_TYPE_SINT16))
  {
    /* @Trace: Com_SUD_API_01901 */
    LpWrBuffer += COM_ONE;
  } else if ((LucType == COM_SIG_TYPE_UINT32) ||
    (LucType == COM_SIG_TYPE_SINT32))
  {
    /* @Trace: Com_SUD_API_01902 */
    LpWrBuffer += COM_THREE;
  } else if ((LucType == COM_SIG_TYPE_UINT64) ||
    (LucType == COM_SIG_TYPE_SINT64))
  {
    /* @Trace: Com_SUD_API_01903 */
    LpWrBuffer += COM_SEVEN;
  } else
  {
    /*Do nothing*/
  }
  /* polyspace-end MISRA2012:18.4 [Justified:Low] "Pointer access accepted for buffer processing. There is no safety impact" */
  #endif
  /* @Trace: Com_SUD_API_01904 */
  /* Get the number of bytes of data */
  LucNoOfByte = (uint8)(LpTxPack->ddSigTypeOrSize);
  /* Get the size of data */
  LucSizeOrData = (LucNoOfByte & COM_SIG_SIZE_MASK_VALUE);
  /* Get the number of counts that signal spread across */
  LucNoOfByte = LucNoOfByte & COM_SIG_BYTE_MASK_VALUE;
  /* Initialize double word variable to zero */
  LunApplSignal.whole_dword = COM_ZERO;
  /* Check whether signal size is 8 bit */
  if(COM_SIZE_8 == LucSizeOrData)
  {
    /* @Trace: Com_SUD_API_00728 */
    /*  Get the signal data to lower byte of double word variable */
    LunApplSignal.byte_val.BO_Byte[COM_DWORD_LS_BYTE_IDX] =
                    *(P2CONST(uint8, AUTOMATIC, COM_CONST)) LpSigDataPtr;
  }
  /* Check whether signal size is 16 bit */
  else if(COM_SIZE_16 == LucSizeOrData)
  {
    /* @Trace: Com_SUD_API_00729 */
    /*  Get the signal data to lower word of double word variable */
    LunApplSignal.word_val.BO_Word[COM_DWORD_LS_WORD_IDX] =
                   *(P2CONST(uint16, AUTOMATIC, COM_CONST)) LpSigDataPtr;
  }
  else
  {
    /* @Trace: Com_SUD_API_00730 */
    /*  Get the signal data to double word variable */
    LunApplSignal.whole_dword =
                *(P2CONST(uint32, AUTOMATIC, COM_CONST)) LpSigDataPtr;
  }
  /* @Trace: Com_SUD_API_00731 */
  /* Shift the signal value in double word variable by number of shift bits */
  LunApplSignal.whole_dword <<= (LpTxPack->ucNoOfShiftBit);
  /* Get the local pointer to lower byte of double word variable and assign it
  to local application signal pointer */
  LpAppSigPtr = (P2VAR(uint8, AUTOMATIC, COM_VAR))
    &LunApplSignal.byte_val.BO_Byte[COM_DWORD_LS_BYTE_IDX];
  /* Get the end mask value */
  LucEndMask = LpTxPack->ucWrEndMask;
  /* Decrement the signal size */
  LucNoOfByte--;
  /* Enter protection area */
  #if(COM_TX_INTERRUPT_BASED_PROCESS == STD_OFF)
  SchM_Enter_Com_TX_EXT_SIG_DATA_PROTECTION_AREA();
  #endif
  /* Get the first byte of I-PDU buffer into local variable */
  /* polyspace +1 RTE:NIV [Not a defect:Low] "Variable initialized with configuration data" */
  LucSizeOrData = *LpWrBuffer;
  /* Clear signal data from the I-PDU by applying start mask */
  LucSizeOrData &= LpTxPack->ucWrStartMask;
  /* Write data from application buffer pointer */
  LucSizeOrData |= *LpAppSigPtr;
  /* Copy data from application signal pointer to a local variable */
  *LpWrBuffer = LucSizeOrData;
  #if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)
  /* @Trace: Com_SUD_API_01611 */
  /* Decrement application signal pointer */
  LpAppSigPtr--;
  /* Increment I-PDU buffer pointer */
  LpWrBuffer++;
  #else
  /* @Trace: Com_SUD_API_01612 */
  /* Increment application signal pointer */
  LpAppSigPtr++;
  /* Decrement I-PDU buffer pointer */
  LpWrBuffer--;
  #endif
  /* Loop for number of bytes of data */
  while(LucNoOfByte != COM_ONE)
  {
    /* @Trace: Com_SUD_API_00732 */
    /* Copy application data to I-PDU buffer */
    *LpWrBuffer = *LpAppSigPtr;
    #if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)
    /* @Trace: Com_SUD_API_01613 */
    /* Decrement application signal pointer */
    LpAppSigPtr--;
    /* Increment I-PDU buffer pointer */
    LpWrBuffer++;
    #else
    /* @Trace: Com_SUD_API_01614 */
    /* Increment application signal pointer */
    LpAppSigPtr++;
    /* Decrement I-PDU buffer pointer */
    LpWrBuffer--;
    #endif
    /* @Trace: Com_SUD_API_01615 */
    LucNoOfByte--;
  }
  /* @Trace: Com_SUD_API_00733 */
  /* Get the first byte of I-PDU buffer into local I-PDU variable */
  /* polyspace +1 RTE:NIV [Not a defect:Low] "Variable initialized with configuration data" */
  LucSizeOrData = *LpWrBuffer;
  /* Clear local I-PDU variable data by applying End Mask to it */
  LucSizeOrData &= LucEndMask;
  /* Get application data value by applying negate mask to local I-PDU variable
  to clear unoccupied area and write to I-PDU buffer  */
  LucSizeOrData |= *LpAppSigPtr & ((uint8)(~LucEndMask));
  /* Store local I-PDU buffer variable to I-PDU */
  *LpWrBuffer = LucSizeOrData;
  /* Exit protection area */
  #if(COM_TX_INTERRUPT_BASED_PROCESS == STD_OFF)
  SchM_Exit_Com_TX_EXT_SIG_DATA_PROTECTION_AREA();
  #endif
}
/* @Traceability END -- SRS: SWS_Com_00675, SWS_Com_00007 */
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Com_PackFiveByteOrdering                            **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function packs the signal which spread across  **
**                        five bytes in an I-PDU and does the endianness      **
**                        conversion.                                         **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same signal.                  **
**                        Reentrant for different signals.                    **
**                                                                            **
** Input Parameters     : LpTxPack, LpSigDataPtr                              **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : SchM_Enter_XXX()           **
**                                                 SchM_Exit_XXX()            **
*******************************************************************************/

#define COM_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SRS_Com_02078 */
FUNC(void, COM_CODE) Com_PackFiveByteOrdering
(P2CONST(Com_TxPack, AUTOMATIC, COM_CONST) LpTxPack,
                    P2CONST (void, AUTOMATIC, COM_CONST) LpSigDataPtr)
{
  /* @Trace: Com_SUD_API_00734 */
  P2VAR(uint8, AUTOMATIC, COM_VAR) LpWrBuffer;
  P2VAR(uint8, AUTOMATIC, COM_VAR) LpAppSigPtr;
  Com_MIdWord_Access LunApplSignal;
  Com_MIWord_Access LunApplSigHi;
  uint8 LucShiftOrData;
  uint8 LucEndMask;
  /* Get the local pointer to I-PDU buffer */
  LpWrBuffer =
  (P2VAR(uint8, AUTOMATIC, COM_VAR)) LpTxPack->pWrBuffer;
  #if (CPU_BYTE_ORDER == LOW_BYTE_FIRST)
  /* Get signal actual type */
  uint8 LucType = LpTxPack->ucType;
  /* Modify LpWrBuffer pointer to point to correct MSB position in case
   * network byte order is different from system byte order */
  /* polyspace-begin MISRA2012:18.4 [Justified:Low] "Pointer access accepted for buffer processing. There is no safety impact" */
  if ((LucType == COM_SIG_TYPE_UINT16) ||
    (LucType == COM_SIG_TYPE_SINT16))
  {
    /* @Trace: Com_SUD_API_01917 */
    LpWrBuffer += COM_ONE;
  } else if ((LucType == COM_SIG_TYPE_UINT32) ||
    (LucType == COM_SIG_TYPE_SINT32))
  {
    /* @Trace: Com_SUD_API_01918 */
    LpWrBuffer += COM_THREE;
  } else if ((LucType == COM_SIG_TYPE_UINT64) ||
    (LucType == COM_SIG_TYPE_SINT64))
  {
    /* @Trace: Com_SUD_API_01919 */
    LpWrBuffer += COM_SEVEN;
  } else
  {
    /*Do nothing*/
  }
  /* polyspace-end MISRA2012:18.4 [Justified:Low] "Pointer access accepted for buffer processing. There is no safety impact" */
  #endif
  /* @Trace: Com_SUD_API_01920 */
  /* Copy signal data to double word variable */
  LunApplSignal.whole_dword=*(P2CONST(uint32, AUTOMATIC, COM_CONST))
                                                                   LpSigDataPtr;
  /* Get the number of shift bits to a local variable */
  LucShiftOrData = LpTxPack->ucNoOfShiftBit;
  /* Get the end mask value to local variable */
  LucEndMask = LpTxPack->ucWrEndMask;
  /* Copy the higher byte of double word variable to the lower byte of word
  variable */
  LunApplSigHi.whole_word = 
    (uint8)LunApplSignal.byte_val.BO_Byte[COM_DWORD_MS_BYTE_IDX];
  /* Shift the double word variable by the number of shift bits to get start
  position of signal in I-PDU */
  LunApplSignal.whole_dword <<= LucShiftOrData;
  /* Shift the word variable by number of shift bits */
  /* polyspace +2 RTE:OVFL [Not a defect:Low] "Value won't overflow. This is assured by generator" */
  LunApplSigHi.whole_word =
    (uint16)((LunApplSigHi.whole_word) << LucShiftOrData);
  /* Apply negate end mask to clear unwanted data in higher byte of word
  variable */
  LunApplSigHi.byte_val.BO_Byte[COM_WORD_MS_BYTE_IDX] &= (uint8)(~(LucEndMask));
  /* Get the pointer to lower byte of the double word variable and assign to
  local application signal pointer */
  LpAppSigPtr = (P2VAR(uint8, AUTOMATIC, COM_VAR))
    &LunApplSignal.byte_val.BO_Byte[COM_DWORD_LS_BYTE_IDX];
  /* Enter protection area */
  #if(COM_TX_INTERRUPT_BASED_PROCESS == STD_OFF)
  SchM_Enter_Com_TX_EXT_SIG_DATA_PROTECTION_AREA();
  #endif
  /* Get the data from I-PDU buffer pointer to local variable */
  LucShiftOrData = *LpWrBuffer;
  /* Clear signal data from local I-PDU buffer variable by applying start
  mask */
  LucShiftOrData &= LpTxPack->ucWrStartMask;
  /* Copy data from application signal pointer to a local I-PDU buffer
  variable */
  LucShiftOrData |= *LpAppSigPtr;
  /* Copy data into I-PDU buffer from local I-PDU buffer variable */
  *LpWrBuffer = LucShiftOrData;
  #if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)
  /* @Trace: Com_SUD_API_01616 */
  /* Decrement application signal pointer */
  LpAppSigPtr--;
  /* Increment I-PDU buffer pointer */
  LpWrBuffer++;
  #else
  /* @Trace: Com_SUD_API_01617 */
  /* Increment application signal pointer */
  LpAppSigPtr++;
  /* Decrement I-PDU buffer pointer */
  LpWrBuffer--;
  #endif
  /* @Trace: Com_SUD_API_01618 */
  /* Get the number of bytes of data in local variable */
  LucShiftOrData = COM_FOUR;
  /* Loop for number of bytes of data */
  do
  {
    /* @Trace: Com_SUD_API_00735 */
    /* Copy data from application signal pointer to I-PDU buffer */
    *LpWrBuffer = *LpAppSigPtr;
    #if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)
    /* @Trace: Com_SUD_API_01619 */
    /* Decrement application signal pointer */
    LpAppSigPtr--;
    /* Increment I-PDU buffer pointer */
    LpWrBuffer++;
    #else
    /* @Trace: Com_SUD_API_01620 */
    /* Increment application signal pointer */
    LpAppSigPtr++;
    /* Decrement I-PDU buffer pointer */
    LpWrBuffer--;
    #endif
    /* @Trace: Com_SUD_API_01621 */
    /* Decrement the data byte */
    LucShiftOrData--;
  }while(LucShiftOrData != COM_ONE);
  /* @Trace: Com_SUD_API_00736 */
  /* Get the data from I-PDU buffer pointer to local I-PDU buffer variable */
  LucShiftOrData = *LpWrBuffer;
  /* Clear signal data from the local I-PDU buffer variable by applying end
  mask */
  LucShiftOrData &= LucEndMask;
  /* Copy higher byte data of word variable to local I-PDU buffer */
  LucShiftOrData |= (LunApplSigHi.byte_val.BO_Byte[COM_WORD_MS_BYTE_IDX]);
  /* Copy the local I-PDU buffer data into local I-PDU buffer variable */
  *LpWrBuffer = LucShiftOrData;
  /* Exit protection area */
  #if(COM_TX_INTERRUPT_BASED_PROCESS == STD_OFF)
  SchM_Exit_Com_TX_EXT_SIG_DATA_PROTECTION_AREA();
  #endif
}
/* @Traceability END -- SRS: SRS_Com_02078 */
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Com_PackNBytes                                      **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function packs the signal of uint8[n] type     **
**                        which spreads across N bytes in an I-PDU.           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same signal.                  **
**                        Reentrant for different signals.                    **
**                                                                            **
** Input Parameters     : LpTxPack, LpSigDataPtr                              **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : Com_GaaTxDynSigLength      **
**                        Function(s) invoked    : SchM_Enter_XXX()           **
**                                                 SchM_Exit_XXX()            **
*******************************************************************************/

#define COM_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SRS_Com_02078 */
FUNC(void, COM_CODE) Com_PackNBytes
  (P2CONST(Com_TxPack, AUTOMATIC, COM_CONST) LpTxPack,
  P2CONST (void, AUTOMATIC, COM_CONST) LpSigDataPtr)
{
  /* @Trace: Com_SUD_API_00737 */
  P2VAR(uint8, AUTOMATIC, COM_VAR) LpWrBuffer;
  P2CONST(uint8, AUTOMATIC, COM_CONST) LpApplBuffer;
  PduLengthType LddSize;
  uint8 LucIpduBuffer;
  #if(COM_TX_DYN_SUPPORT == STD_ON)
  /* #2142 : separate DYN PDU from TP */
  if((LpTxPack->ddTxIpduDynLegthRef) != COM_INVALID_TXID_PARAM)
  {
    /* @Trace: Com_SUD_API_00738 */
    /* Get the size of the signal or signal group */
    /* polyspace +1 RTE:OBAI [Not a defect:Low] "Array access index is in-bounds. This is assured by generator" */
    LddSize = Com_GaaTxDynSigLength[LpTxPack->ddTxIpduDynLegthRef];
  }
  else
  #endif
  {
    /* @Trace: Com_SUD_API_00739 */
    /* Get the size of the signal or signal group */
    LddSize = LpTxPack->ddSigTypeOrSize;
  }

  /* Check whether signal size is not equal to zero */
  if(LddSize != (PduLengthType)COM_ZERO)
  {
    /* @Trace: Com_SUD_API_00740 */
    /* Get the pointer to application buffer */
    LpApplBuffer = (P2CONST(uint8, AUTOMATIC, COM_CONST)) LpSigDataPtr;
    /* Get the pointer to an I-PDU buffer */
    LpWrBuffer = (P2VAR(uint8, AUTOMATIC, COM_VAR)) LpTxPack->pWrBuffer;
    /* Enter protection area */
    #if(COM_TX_INTERRUPT_BASED_PROCESS == STD_OFF)
    SchM_Enter_Com_TX_EXT_SIG_DATA_PROTECTION_AREA();
    #endif
    /* Get the data from the I-PDU buffer pointer to a local I-PDU buffer
    variable */
    /* polyspace +1 RTE:NIV [Not a defect:Low] "Variable initialized with configuration data" */
    LucIpduBuffer = *LpWrBuffer;
    /* Apply the start mask to local I-PDU buffer variable */
    LucIpduBuffer &= LpTxPack->ucWrStartMask;
    /* Copy the application  data to local I-PDU buffer variable */
    LucIpduBuffer |= *LpApplBuffer;
    /* Write the application data back to I-PDU buffer */
    *LpWrBuffer = LucIpduBuffer;
    /* Increment the application pointer */
    LpApplBuffer++;
    /* Increment the WrBuffer pointer */
    LpWrBuffer++;
    /* Decrement the size size */
    LddSize--;
    /* Check whether size of the signal is not equal to one */
    while(LddSize > (PduLengthType)COM_ONE)
    {
      /* @Trace: Com_SUD_API_00741 */
      /* Copy the application buffer data to I-PDU buffer pointer */
      *LpWrBuffer = *LpApplBuffer;
      /* Get the pointer to next application buffer */
      LpApplBuffer++;
      /* Get the pointer to next I-PDU buffer */
      LpWrBuffer++;
      /* Decrement the signal size count */
      LddSize--;
    }
    /* @Trace: Com_SUD_API_00742 */
    /* Get the value of I-PDU buffer to a local I-PDU buffer variable */
    /* polyspace +1 RTE:NIV [Not a defect:Low] "Variable initialized with configuration data" */
    LucIpduBuffer = *LpWrBuffer;
    /* Apply the end mask to local I-PDU buffer variable to clear unoccupied
    areas */
    LucIpduBuffer &= LpTxPack->ucWrEndMask;
    /* Copy the application  data to local variable */
    LucIpduBuffer |= *LpApplBuffer;
    /* Copy the local I-PDU buffer variable data to the I-PDU buffer */
    *LpWrBuffer = LucIpduBuffer;
    /* Exit protection area */
    #if(COM_TX_INTERRUPT_BASED_PROCESS == STD_OFF)
    SchM_Exit_Com_TX_EXT_SIG_DATA_PROTECTION_AREA();
    #endif
  }/* Check whether signal size is not equal to zero */
}
/* @Traceability END -- SRS: SRS_Com_02078 */
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Com_Pack16bit                                       **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function packs signal of size less than or     **
**                        equal to 16 bit into the I-PDU buffer.              **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same signal.                  **
**                        Reentrant for different signals.                    **
**                                                                            **
** Input Parameters     : LpSigDataPtr                                        **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : LpTxPack                                            **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : SchM_Enter_XXX()           **
**                                                 SchM_Exit_XXX()            **
*******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SRS_Com_02078 */
FUNC(void, COM_CODE) Com_Pack16bit
(P2CONST(Com_TxPack, AUTOMATIC, COM_CONST) LpTxPack,
                        P2CONST(void, AUTOMATIC, COM_CONST) LpSigDataPtr)
{
  /* @Trace: Com_SUD_API_00743 */
  #if(CPU_TYPE == CPU_TYPE_8)
  uint8 localDataSrc;
  uint8 localDataDst;
  #elif(CPU_TYPE == CPU_TYPE_16)
  uint16 localDataSrc;
  uint16 localDataDst;
  #elif(CPU_TYPE == CPU_TYPE_32)
  uint32 localDataSrc;
  uint32 localDataDst;
  #endif

  /* Enter protection area */
  #if(COM_TX_INTERRUPT_BASED_PROCESS == STD_OFF)
  SchM_Enter_Com_TX_EXT_SIG_DATA_PROTECTION_AREA();
  #endif

  /* Assign data pointers to local platform specific pointers */
  /* polyspace-begin MISRA-C3:11.6 [Not a defect:Low] "Casting from pointer to integer is acceptable to get memory address value" */
  #if(CPU_TYPE == CPU_TYPE_8)
  localDataSrc = (uint8)LpSigDataPtr;
  localDataDst = (uint8)(LpTxPack->pWrBuffer);

  #elif(CPU_TYPE == CPU_TYPE_16)
  localDataSrc = (uint16)LpSigDataPtr;
  localDataDst = (uint16)(LpTxPack->pWrBuffer);

  #elif(CPU_TYPE == CPU_TYPE_32)
  localDataSrc = (uint32)LpSigDataPtr;
  localDataDst = (uint32)(LpTxPack->pWrBuffer);
  #endif
  /* polyspace-end MISRA-C3:11.6 [Not a defect:Low] "Casting from pointer to integer is acceptable to get memory address value" */

  /* Copy data from source to destination buffer */
  /* polyspace-begin MISRA-C3:11.4 [Not a defect:Low] "Casting from integer to pointer is acceptable as localDataDst/Src carrying address value" */
  /* polyspace-begin CERT-C:INT36-C [Not a defect:Low] "Casting from integer to pointer is acceptable as localDataDst/Src carrying address value" */
  /* polyspace +1 RTE:STD_LIB [Not a defect:Low] "All pointers are available and in range. This is assured by generator" */
  memcpy((void*)(&((uint8*)localDataDst)[0]),
    (void*)(&((uint8*)localDataSrc)[0]), sizeof(uint16));
  /* polyspace-end MISRA-C3:11.4 [Not a defect:Low] "Casting from integer to pointer is acceptable as localDataDst/Src carrying address value" */
  /* polyspace-end CERT-C:INT36-C [Not a defect:Low] "Casting from integer to pointer is acceptable as localDataDst/Src carrying address value" */

  /* Exit protection area */
  #if(COM_TX_INTERRUPT_BASED_PROCESS == STD_OFF)
  SchM_Exit_Com_TX_EXT_SIG_DATA_PROTECTION_AREA();
  #endif
}
/* @Traceability END -- SRS: SRS_Com_02078 */
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Com_Pack32bit                                       **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function packs signal of size less than or     **
**                        equal to 32 bit into the I-PDU buffer.              **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same signal.                  **
**                        Reentrant for different signals.                    **
**                                                                            **
** Input Parameters     : LpSigDataPtr                                        **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : LpTxPack                                            **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : SchM_Enter_XXX()           **
**                                                 SchM_Exit_XXX()            **
*******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE) Com_Pack32bit
(P2CONST(Com_TxPack, AUTOMATIC, COM_CONST) LpTxPack,
                        P2CONST(void, AUTOMATIC, COM_CONST) LpSigDataPtr)
{
  /* @Trace: Com_SUD_API_00744 */
  #if(CPU_TYPE == CPU_TYPE_8)
  uint8 localDataSrc;
  uint8 localDataDst;
  #elif(CPU_TYPE == CPU_TYPE_16)
  uint16 localDataSrc;
  uint16 localDataDst;
  #elif(CPU_TYPE == CPU_TYPE_32)
  uint32 localDataSrc;
  uint32 localDataDst;
  #endif

  /* Enter protection area */
  #if(COM_TX_INTERRUPT_BASED_PROCESS == STD_OFF)
  SchM_Enter_Com_TX_EXT_SIG_DATA_PROTECTION_AREA();
  #endif

  /* Assign data pointers to local platform specific pointers */
  /* polyspace-begin MISRA-C3:11.6 [Not a defect:Low] "Casting from pointer to integer is acceptable to get memory address value" */
  #if(CPU_TYPE == CPU_TYPE_8)
  localDataSrc = (uint8)LpSigDataPtr;
  localDataDst = (uint8)(LpTxPack->pWrBuffer);

  #elif(CPU_TYPE == CPU_TYPE_16)
  localDataSrc = (uint16)LpSigDataPtr;
  localDataDst = (uint16)(LpTxPack->pWrBuffer);

  #elif(CPU_TYPE == CPU_TYPE_32)
  localDataSrc = (uint32)LpSigDataPtr;
  localDataDst = (uint32)(LpTxPack->pWrBuffer);
  #endif
  /* polyspace-end MISRA-C3:11.6 [Not a defect:Low] "Casting from pointer to integer is acceptable to get memory address value" */

  /* Copy data from source to destination buffer */
  /* polyspace-begin MISRA-C3:11.4 [Not a defect:Low] "Casting from integer to pointer is acceptable as localDataDst/Src carrying address value" */
  /* polyspace-begin CERT-C:INT36-C [Not a defect:Low] "Casting from integer to pointer is acceptable as localDataDst/Src carrying address value" */
  /* polyspace +1 RTE:STD_LIB [Not a defect:Low] "All pointers are available and in range. This is assured by generator" */
  memcpy((void*)(&((uint8*)localDataDst)[0]),
    (void*)(&((uint8*)localDataSrc)[0]), sizeof(uint32));
  /* polyspace-end MISRA-C3:11.4 [Not a defect:Low] "Casting from integer to pointer is acceptable as localDataDst/Src carrying address value" */
  /* polyspace-end CERT-C:INT36-C [Not a defect:Low] "Casting from integer to pointer is acceptable as localDataDst/Src carrying address value" */

  /* Exit protection area */
  #if(COM_TX_INTERRUPT_BASED_PROCESS == STD_OFF)
  SchM_Exit_Com_TX_EXT_SIG_DATA_PROTECTION_AREA();
  #endif
}

#define COM_STOP_SEC_CODE
#include "MemMap.h"


/*******************************************************************************
** Function Name        : Com_Write_8                                         **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function copies 8 bit data from the source     **
**                        pointer to destination pointer.                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same signal.                  **
**                        Reentrant for different signals.                    **
**                                                                            **
** Input Parameters     : LpSource, LddSize                                   **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : LpDest                                              **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : SchM_Enter_XXX()           **
**                                                 SchM_Exit_XXX()            **
*******************************************************************************/

#define COM_START_SEC_CODE
#include "MemMap.h"

FUNC(void, COM_CODE) Com_Write_8
  (P2CONST(void, AUTOMATIC, COM_CONST) LpSource,
  P2VAR(void, AUTOMATIC, COM_VAR) LpDest, PduLengthType LddSize)
{
  /* @Trace: Com_SUD_API_00745 */
  /* Enter protection area */
  #if(COM_TX_INTERRUPT_BASED_PROCESS == STD_OFF)
  SchM_Enter_Com_SIG_DATA_PROTECTION_AREA();
  #endif
  /* Copy data from source to destination buffer */
  *((P2VAR(uint8, AUTOMATIC, COM_VAR)) LpDest) =
                      *((P2CONST(uint8, AUTOMATIC, COM_CONST)) LpSource);
  /* Exit protection area */
  #if(COM_TX_INTERRUPT_BASED_PROCESS == STD_OFF)
  SchM_Exit_Com_SIG_DATA_PROTECTION_AREA();
  #endif

  COM_UNUSED(LddSize);
}

#define COM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Com_Write_16                                        **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function copies 16 bit data from the source    **
**                        pointer to destination pointer.                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same signal.                  **
**                        Reentrant for different signals.                    **
**                                                                            **
** Input Parameters     : LpSource, LddSize                                   **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : LpDest                                              **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : SchM_Enter_XXX()           **
**                                                 SchM_Exit_XXX()            **
*******************************************************************************/

#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE) Com_Write_16
  (P2CONST(void, AUTOMATIC, COM_CONST) LpSource,
  P2VAR(void, AUTOMATIC, COM_VAR) LpDest, PduLengthType LddSize)
{
  /* @Trace: Com_SUD_API_00746 */
  /* Enter protection area */
  #if(COM_TX_INTERRUPT_BASED_PROCESS == STD_OFF)
  SchM_Enter_Com_SIG_DATA_PROTECTION_AREA();
  #endif
  /* Copy data from source to destination buffer */
  *((P2VAR(uint16, AUTOMATIC, COM_VAR)) LpDest) =
                    *((P2CONST(uint16, AUTOMATIC, COM_CONST)) LpSource);
  /* Exit protection area */
  #if(COM_TX_INTERRUPT_BASED_PROCESS == STD_OFF)
  SchM_Exit_Com_SIG_DATA_PROTECTION_AREA();
  #endif

  COM_UNUSED(LddSize);
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Com_Write_32                                        **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function copies 32 bit data from the source    **
**                        pointer to destination pointer.                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same signal.                  **
**                        Reentrant for different signals.                    **
**                                                                            **
** Input Parameters     : LpSource, LddSize                                   **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : LpDest                                              **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : SchM_Enter_XXX()           **
**                                                 SchM_Exit_XXX()            **
*******************************************************************************/

#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE) Com_Write_32
  (P2CONST(void, AUTOMATIC, COM_CONST) LpSource,
  P2VAR(void, AUTOMATIC, COM_VAR) LpDest, PduLengthType LddSize)
{
  /* @Trace: Com_SUD_API_00747*/
  /* Enter protection area */
  #if(COM_TX_INTERRUPT_BASED_PROCESS == STD_OFF)
  SchM_Enter_Com_SIG_DATA_PROTECTION_AREA();
  #endif
  /* Copy data from source to destination buffer */
  *((P2VAR(uint32, AUTOMATIC, COM_VAR)) LpDest) =
                    *((P2CONST(uint32, AUTOMATIC, COM_CONST)) LpSource);
  /* Exit protection area */
  #if(COM_TX_INTERRUPT_BASED_PROCESS == STD_OFF)
  SchM_Exit_Com_SIG_DATA_PROTECTION_AREA();
  #endif

  COM_UNUSED(LddSize);
}

#define COM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Com_Write_64                                        **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function copies 64 bit data from the source    **
**                        pointer to destination pointer.                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same signal.                  **
**                        Reentrant for different signals.                    **
**                                                                            **
** Input Parameters     : LpSource, LpDest, LddSize                           **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : SchM_Enter_XXX()           **
**                                                 SchM_Exit_XXX()            **
*******************************************************************************/

#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE) Com_Write_64
  (P2CONST(void, AUTOMATIC, COM_CONST) LpSource,
  P2VAR(void, AUTOMATIC, COM_VAR) LpDest, PduLengthType LddSize)
{
  /* @Trace: Com_SUD_API_00748 */
  /* Enter protection area */
  P2VAR(uint32, AUTOMATIC, COM_VAR) LpTarget;
  P2CONST(uint32, AUTOMATIC, COM_VAR) LpSrc;
  LpSrc = (P2CONST(uint32, AUTOMATIC, COM_VAR)) LpSource;
  LpTarget = (P2VAR(uint32, AUTOMATIC, COM_VAR)) LpDest;
  #if(COM_TX_INTERRUPT_BASED_PROCESS == STD_OFF)
  SchM_Enter_Com_SIG_DATA_PROTECTION_AREA();
  #endif
  /* Copy data from source to destination buffer */
  *LpTarget = *LpSrc;
  /* Increment pointers */
  LpSrc++;
  LpTarget++;
  /* Copy data from source to destination buffer */
  *LpTarget = *LpSrc;
  /* Exit protection area */
  #if(COM_TX_INTERRUPT_BASED_PROCESS == STD_OFF)
  SchM_Exit_Com_SIG_DATA_PROTECTION_AREA();
  #endif

  COM_UNUSED(LddSize);
}

#define COM_STOP_SEC_CODE
#include "MemMap.h"


/*******************************************************************************
** Function Name        : Com_Write_NBytes                                    **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function copies N byte data from the source    **
**                        pointer to destination pointer.                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same signal.                  **
**                        Reentrant for different signals.                    **
**                                                                            **
** Input Parameters     : LpSource, LpDest, LddSize                           **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : SchM_Enter_XXX()           **
**                                                 SchM_Exit_XXX()            **
*******************************************************************************/

#define COM_START_SEC_CODE
#include "MemMap.h"

FUNC(void, COM_CODE) Com_Write_NBytes
  (P2CONST(void, AUTOMATIC, COM_CONST) LpSource,
  P2VAR(void, AUTOMATIC, COM_VAR) LpDest, PduLengthType LddSize)
{
  /* @Trace: Com_SUD_API_00749 */
  P2VAR(uint8, AUTOMATIC, COM_VAR) LpDestBuffer;
  P2CONST(uint8, AUTOMATIC, COM_CONST) LpSourceBuffer;
  PduLengthType LddSigSize;

  /* Get the pointer to destination buffer */
  LpDestBuffer = (P2VAR(uint8, AUTOMATIC, COM_VAR)) LpDest;
  /* Get the pointer to source buffer */
  LpSourceBuffer = (P2CONST(uint8, AUTOMATIC, COM_CONST)) LpSource;
  /* Get the size of this signal */
  LddSigSize = LddSize;
 
  /* Enter protection area */
  #if(COM_TX_INTERRUPT_BASED_PROCESS == STD_OFF)
  SchM_Enter_Com_SIG_DATA_PROTECTION_AREA();
  #endif
  while(LddSigSize != (PduLengthType)COM_ZERO)
  {
    /* @Trace: Com_SUD_API_00750 */
    /* Copy the data from source buffer to destination buffer */
    *LpDestBuffer = *LpSourceBuffer;
    /* Get the pointer to next destination data */
    LpDestBuffer++;
    /* Get the pointer to next source data */
    LpSourceBuffer++;
    /* Decrement the signal size count */
    LddSigSize--;
  }
  /* Exit protection area */
  #if(COM_TX_INTERRUPT_BASED_PROCESS == STD_OFF)
  /* @Trace: Com_SUD_API_00751 */
  SchM_Exit_Com_SIG_DATA_PROTECTION_AREA();
  #endif
}

#define COM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Com_Validate_8                                      **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function performs validation check on the      **
**                        signal and returns true if signal is valid.         **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : LpSource, LddSize                                   **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : LpTarget                                            **
**                                                                            **
** Return parameter     : LblReturnValue                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : SchM_Enter_XXX()           **
**                                                 SchM_Exit_XXX()            **
*******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(boolean, COM_CODE) Com_Validate_8
(P2CONST(void, AUTOMATIC, COM_CONST) LpSource,
                  P2VAR(void, AUTOMATIC, COM_VAR) LpTarget,
                                                          PduLengthType LddSize)
{
  /* @Trace: Com_SUD_API_00752 */
  boolean LblReturnValue;
  /* Initialize return value to true */
  LblReturnValue = COM_FALSE;
  /* Enter protection area */
  #if(COM_TX_INTERRUPT_BASED_PROCESS == STD_OFF)
  SchM_Enter_Com_TX_EXT_SIG_DATA_PROTECTION_AREA();
  #endif
  /* Check whether data is valid or not */
  if((*(P2VAR(uint8, AUTOMATIC, COM_VAR)) LpTarget) !=
                      (*(P2CONST(uint8, AUTOMATIC, COM_CONST)) LpSource))
  {

    /* @Trace: Com_SUD_API_00753 */
    (*(P2VAR(uint8, AUTOMATIC, COM_VAR)) LpTarget) =
                      (*(P2CONST(uint8, AUTOMATIC, COM_CONST)) LpSource);
    /* Set return value to false */
    LblReturnValue = COM_TRUE;
  }
  /* @Trace: Com_SUD_API_00754 */
  /* Exit Protection Area */
  #if(COM_TX_INTERRUPT_BASED_PROCESS == STD_OFF)
  SchM_Exit_Com_TX_EXT_SIG_DATA_PROTECTION_AREA();
  #endif

  COM_UNUSED(LddSize);
  /* Return value */
  return(LblReturnValue);
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Com_Validate_16                                     **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function performs validation check on the      **
**                        signal and returns true if signal is valid.         **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : LpSource, LddSize                                   **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : LpTarget                                            **
**                                                                            **
** Return parameter     : LblReturnValue                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : SchM_Enter_XXX()           **
**                                                 SchM_Exit_XXX()            **
*******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(boolean, COM_CODE) Com_Validate_16
(P2CONST(void, AUTOMATIC, COM_CONST) LpSource,
                      P2VAR(void, AUTOMATIC, COM_VAR) LpTarget,
                                                          PduLengthType LddSize)
{
  /* @Trace: Com_SUD_API_00755 */
  boolean LblReturnValue;
  /* Initialize return value to true */
  LblReturnValue = COM_FALSE;
  /* Enter protection area */
  #if(COM_TX_INTERRUPT_BASED_PROCESS == STD_OFF)
  SchM_Enter_Com_TX_EXT_SIG_DATA_PROTECTION_AREA();
  #endif
  /* Check whether invalid data is not equal to signal data */
  if((*(P2VAR(uint16, AUTOMATIC, COM_VAR)) LpTarget) !=
                     (*(P2CONST(uint16, AUTOMATIC, COM_CONST)) LpSource))
  {
    /* @Trace: Com_SUD_API_00756 */
    /* Set return value to false */
    LblReturnValue = COM_TRUE;
    (*(P2VAR(uint16, AUTOMATIC, COM_VAR)) LpTarget) =
                     (*(P2CONST(uint16, AUTOMATIC, COM_CONST)) LpSource);
  }
  /* @Trace: Com_SUD_API_00757 */
  /* Exit protection area */
  #if(COM_TX_INTERRUPT_BASED_PROCESS == STD_OFF)
  SchM_Exit_Com_TX_EXT_SIG_DATA_PROTECTION_AREA();
  #endif

  COM_UNUSED(LddSize);
  /* Return value */
  return(LblReturnValue);
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name        : Com_Validate_32                                     **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function performs validation check on the      **
**                        signal and returns true if signal is valid.         **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : LpSource, LddSize                                   **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : LpTarget                                            **
**                                                                            **
** Return parameter     : LblReturnValue                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : SchM_Enter_XXX()           **
**                                                 SchM_Exit_XXX()            **
*******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(boolean, COM_CODE) Com_Validate_32
(P2CONST(void, AUTOMATIC, COM_CONST) LpSource,
                      P2VAR(void, AUTOMATIC, COM_VAR) LpTarget,
                                                          PduLengthType LddSize)
{
  /* @Trace: Com_SUD_API_00758 */
  boolean LblReturnValue;
  /* Initialize return value to true */
  LblReturnValue = COM_FALSE;
  /* Enter protection area */
  #if(COM_TX_INTERRUPT_BASED_PROCESS == STD_OFF)
  SchM_Enter_Com_TX_EXT_SIG_DATA_PROTECTION_AREA();
  #endif
  /* Check whether invalid data is not equal to signal data */
  if((*(P2VAR(uint32, AUTOMATIC, COM_VAR)) LpTarget) !=
                     (*(P2CONST(uint32, AUTOMATIC, COM_CONST)) LpSource))
  {
    /* @Trace: Com_SUD_API_00759 */
    /* Set return value to false */
    LblReturnValue = COM_TRUE;
    (*(P2VAR(uint32, AUTOMATIC, COM_VAR)) LpTarget) =
                     (*(P2CONST(uint32, AUTOMATIC, COM_CONST)) LpSource);
  }
  /* @Trace: Com_SUD_API_00760 */
  /* Exit protection area */
  #if(COM_TX_INTERRUPT_BASED_PROCESS == STD_OFF)
  SchM_Exit_Com_TX_EXT_SIG_DATA_PROTECTION_AREA();
  #endif

  COM_UNUSED(LddSize);
  /* Return value */
  return(LblReturnValue);
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Com_Validate_64                                     **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function performs validation check on the      **
**                        signal and returns true if signal is valid.         **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : LpSource, LddSize                                   **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : LpTarget                                            **
**                                                                            **
** Return parameter     : LblReturnValue                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : SchM_Enter_XXX()           **
**                                                 SchM_Exit_XXX()            **
*******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(boolean, COM_CODE) Com_Validate_64
(P2CONST(void, AUTOMATIC, COM_CONST) LpSource,
                       P2VAR(void, AUTOMATIC, COM_VAR) LpTarget,
                                                          PduLengthType LddSize)
{
  /* @Trace: Com_SUD_API_00761 */
  boolean LblReturnValue;
  /* Initialize return value to true */
  LblReturnValue = COM_FALSE;
  /* Enter protection area */
  #if(COM_TX_INTERRUPT_BASED_PROCESS == STD_OFF)
  SchM_Enter_Com_TX_EXT_SIG_DATA_PROTECTION_AREA();
  #endif
  /* Check whether invalid data is not equal to signal data */
  if((*(P2VAR(uint32, AUTOMATIC, COM_VAR)) LpTarget) !=
                     (*(P2CONST(uint32, AUTOMATIC, COM_CONST)) LpSource))
  {
    /* @Trace: Com_SUD_API_00762 */
    /* Set return value to false */
    LblReturnValue = COM_TRUE;
    (*(P2VAR(uint32, AUTOMATIC, COM_VAR)) LpTarget) =
                     (*(P2CONST(uint32, AUTOMATIC, COM_CONST)) LpSource);
  }
  /* @Trace: Com_SUD_API_00763 */
  /* Exit protection area */
  #if(COM_TX_INTERRUPT_BASED_PROCESS == STD_OFF)
  SchM_Exit_Com_TX_EXT_SIG_DATA_PROTECTION_AREA();
  #endif

  COM_UNUSED(LddSize);
  /* Return value */
  return(LblReturnValue);
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Com_Validate_NBytes                                 **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function performs validation check on the      **
**                        signal and returns true if signal is valid.         **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : LpSource, LpTarget, LddSize                         **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LblReturnValue                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : SchM_Enter_XXX()           **
**                                                 SchM_Exit_XXX()            **
*******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(boolean, COM_CODE) Com_Validate_NBytes
(P2CONST(void, AUTOMATIC, COM_CONST) LpSource,
                  P2VAR(void, AUTOMATIC, COM_VAR) LpTarget,
                                                          PduLengthType LddSize)
{
  /* @Trace: Com_SUD_API_00764 */
  P2VAR(uint8, AUTOMATIC, COM_VAR) LpTargetPtr;
  P2CONST(uint8, AUTOMATIC, COM_CONST) LpSourcePtr;
  boolean LblReturnValue;
  PduLengthType LddSigSize;

  /* Initialize return value to true */
  LblReturnValue = COM_FALSE;
  /* Get the pointer to destination buffer */
  LpTargetPtr = (P2VAR(uint8, AUTOMATIC, COM_VAR)) LpTarget;
  /* Get the pointer to source buffer */
  LpSourcePtr = (P2CONST(uint8, AUTOMATIC, COM_VAR)) LpSource;
  /* Get the size of this signal */
  LddSigSize = LddSize;
  
  /* Enter protection area */
  #if(COM_TX_INTERRUPT_BASED_PROCESS == STD_OFF)
  SchM_Enter_Com_TX_EXT_SIG_DATA_PROTECTION_AREA();
  #endif
  /* Loop to check whether the data is invalid or not, based on signal size */
  do
  {
    /* @Trace: Com_SUD_API_00765 */
    /* Decrement signal size */
    LddSigSize--;
    /* Check whether invalid data is not equal to signal data */
    if(*LpTargetPtr != *LpSourcePtr)
    {
      /* @Trace: Com_SUD_API_00766 */
      /* Set return value to false */
      LblReturnValue = COM_TRUE;
      *LpTargetPtr = *LpSourcePtr;
    }
    /* @Trace: Com_SUD_API_00767 */
    /* Increment invalid data pointer */
    LpTargetPtr++;
    /* Increment signal data pointer */
    LpSourcePtr++;
  }while(LddSigSize != (PduLengthType)COM_ZERO);
  /* Enter protection area */
  #if(COM_TX_INTERRUPT_BASED_PROCESS == STD_OFF)
  /* @Trace: Com_SUD_API_00768 */
  SchM_Exit_Com_TX_EXT_SIG_DATA_PROTECTION_AREA();
  #endif

  /* Return value */
  return(LblReturnValue);
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/* #7709 start */
/*******************************************************************************
** Function Name        : Com_PackAndValidateSigGrp                           **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function performs validation check on the      **
**                        signal group and returns true if signal is valid.   **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : LpTxPack, LpSigDataPtr                              **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LblReturnValue                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : SchM_Enter_XXX()           **
**                                                 SchM_Exit_XXX()            **
*******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(boolean, COM_CODE) Com_PackAndValidateSigGrp
(P2CONST(Com_TxPack, AUTOMATIC, COM_CONST) LpTxPack,
                      P2CONST (void, AUTOMATIC, COM_CONST) LpSigDataPtr,
                      P2VAR (void, AUTOMATIC, COM_VAR) LpTargetDataPtr,
                      P2CONST (void, AUTOMATIC, COM_CONST) LpMaskingDataPtr)
{
  /* @Trace: Com_SUD_API_00769 */
  P2VAR(uint8, AUTOMATIC, COM_VAR) LpWrBuffer;
  P2CONST(uint8, AUTOMATIC, COM_CONST) LpApplBuffer;
  P2CONST(uint8, AUTOMATIC, COM_CONST) LpMaskingBuffer;
  PduLengthType LddSize;
  uint8 LucIpduBuffer;
  /* For checking value has been changed or not */
  uint8 LucIpduBuffer1;
  boolean LblReturnValue;

  /* Initialize return value to true */
  LblReturnValue = COM_FALSE;
  /* Get the size of the signal or signal group */
  LddSize = LpTxPack->ddSigTypeOrSize;
  /* Check whether signal size is not equal to zero */
  if(LddSize != (PduLengthType)COM_ZERO)
  {
    /* @Trace: Com_SUD_API_00770 */
    /* Get the pointer to application buffer */
    LpApplBuffer = (P2CONST(uint8, AUTOMATIC, COM_CONST)) LpSigDataPtr;
    /* Get the pointer to an I-PDU buffer */
    LpWrBuffer = (P2VAR(uint8, AUTOMATIC, COM_VAR)) LpTargetDataPtr;
    /* Get the pointer to a Masking buffer */
    LpMaskingBuffer = (P2CONST(uint8, AUTOMATIC, COM_CONST)) LpMaskingDataPtr;    
    /* Enter protection area */
    #if(COM_TX_INTERRUPT_BASED_PROCESS == STD_OFF)
    SchM_Enter_Com_TX_EXT_SIG_DATA_PROTECTION_AREA();
    #endif
    /* Get the data from the I-PDU buffer pointer to a local I-PDU buffer
    variable */
    /* polyspace +1 RTE:NIV [Not a defect:Low] "Variable initialized with configuration data" */
    LucIpduBuffer = *LpWrBuffer;
    /* For checking value has been changed or not */
    LucIpduBuffer1 = LucIpduBuffer;

    /* Apply the start mask to local I-PDU buffer variable */
    LucIpduBuffer &= (uint8)(*LpMaskingBuffer);
    /* Copy the application  data to local I-PDU buffer variable */
    LucIpduBuffer |= *LpApplBuffer;
    /* Write the application data back to I-PDU buffer */
    *LpWrBuffer = LucIpduBuffer;
    /* For checking value has been changed or not */
    if(LucIpduBuffer != LucIpduBuffer1)
    {
      /* @Trace: Com_SUD_API_00771 */
      LblReturnValue = COM_TRUE;
    }
    /* @Trace: Com_SUD_API_00772 */
    /* Increment the application pointer */
    LpApplBuffer++;
    /* Increment the WrBuffer pointer */
    LpWrBuffer++;
    /* Get the pointer to next Masking buffer */
    LpMaskingBuffer++;
    /* Decrement the size size */
    LddSize--;
    if(LddSize > (PduLengthType)COM_ZERO)
    {
      /* Check whether size of the signal is not equal to one */
      while(LddSize != (PduLengthType)COM_ONE)
      {
        /* @Trace: Com_SUD_API_00773 */
        /* Copy the application buffer data to I-PDU buffer pointer */
        /* polyspace +1 RTE:NIV [Not a defect:Low] "Variable initialized with configuration data" */
        LucIpduBuffer = *LpWrBuffer;
        /* For checking value has been changed or not */
        LucIpduBuffer1 = LucIpduBuffer;
        
        LucIpduBuffer &= (uint8)(*LpMaskingBuffer);
        LucIpduBuffer |= *LpApplBuffer;
        *LpWrBuffer = LucIpduBuffer;
        if(LucIpduBuffer != LucIpduBuffer1)
        {
          /* @Trace: Com_SUD_API_00774 */
          LblReturnValue = COM_TRUE;
        }
        /* @Trace: Com_SUD_API_00775 */
        /* Get the pointer to next application buffer */
        LpApplBuffer++;
        /* Get the pointer to next I-PDU buffer */
        LpWrBuffer++;
        /* Get the pointer to next Masking buffer */
        LpMaskingBuffer++;
        /* Decrement the signal size count */
        LddSize--;
      }
      /* @Trace: Com_SUD_API_00776 */
      /* Get the value of I-PDU buffer to a local I-PDU buffer variable */
      /* polyspace +1 RTE:NIV [Not a defect:Low] "Variable initialized with configuration data" */
      LucIpduBuffer = *LpWrBuffer;
      /* For checking value has been changed or not */
      LucIpduBuffer1 = LucIpduBuffer;
      /* Apply the end mask to local I-PDU buffer variable to clear unoccupied
      areas */
      LucIpduBuffer &= (uint8)(*LpMaskingBuffer);
      /* Copy the application  data to local variable */
      LucIpduBuffer |= *LpApplBuffer;
      /* Copy the local I-PDU buffer variable data to the I-PDU buffer */
      *LpWrBuffer = LucIpduBuffer;
      /* For checking value has been changed or not */
      if(LucIpduBuffer != LucIpduBuffer1)
      {
        /* @Trace: Com_SUD_API_00777 */
        LblReturnValue = COM_TRUE;
      }
    }
    /* @Trace: Com_SUD_API_00778 */
    /* Exit protection area */
    #if(COM_TX_INTERRUPT_BASED_PROCESS == STD_OFF)
    SchM_Exit_Com_TX_EXT_SIG_DATA_PROTECTION_AREA();
    #endif
  }/* Check whether signal size is not equal to zero */

  /* @Trace: Com_SUD_API_00779 */
  return (LblReturnValue);
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Com_PackSigGrp                                      **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function performs validation check on the      **
**                        signal group and returns true if signal is valid.   **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : LpTxPack, LpSigDataPtr                              **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LblReturnValue                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : SchM_Enter_XXX()           **
**                                                 SchM_Exit_XXX()            **
*******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(boolean, COM_CODE) Com_PackSigGrp
(P2CONST(Com_TxPack, AUTOMATIC, COM_CONST) LpTxPack,
                      P2CONST (void, AUTOMATIC, COM_CONST) LpSigDataPtr,
                      P2VAR (void, AUTOMATIC, COM_VAR) LpTargetDataPtr,
                      P2CONST (void, AUTOMATIC, COM_CONST) LpMaskingDataPtr)
{
  /* @Trace: Com_SUD_API_00780 */
  P2VAR(uint8, AUTOMATIC, COM_VAR) LpWrBuffer;
  P2CONST(uint8, AUTOMATIC, COM_CONST) LpApplBuffer;
  P2CONST(uint8, AUTOMATIC, COM_CONST) LpMaskingBuffer;
  PduLengthType LddSize;
  uint8 LucIpduBuffer;
  boolean LblReturnValue;

  /* Initialize return value to true */
  LblReturnValue = COM_FALSE;
  /* Get the size of the signal or signal group */
  LddSize = LpTxPack->ddSigTypeOrSize;
  /* Check whether signal size is not equal to zero */
  if(LddSize != (PduLengthType)COM_ZERO)
  {
    /* @Trace: Com_SUD_API_00781 */
    /* Get the pointer to application buffer */
    LpApplBuffer = (P2CONST(uint8, AUTOMATIC, COM_CONST)) LpSigDataPtr;
    /* Get the pointer to an I-PDU buffer */
    LpWrBuffer = (P2VAR(uint8, AUTOMATIC, COM_VAR)) LpTargetDataPtr;
    /* Get the pointer to a Masking buffer */
    LpMaskingBuffer = (P2CONST(uint8, AUTOMATIC, COM_CONST)) LpMaskingDataPtr;
    /* Enter protection area */
    #if(COM_TX_INTERRUPT_BASED_PROCESS == STD_OFF)
    SchM_Enter_Com_TX_EXT_SIG_DATA_PROTECTION_AREA();
    #endif
    /* Get the data from the I-PDU buffer pointer to a local I-PDU buffer
    variable */
    /* polyspace +1 RTE:NIV [Not a defect:Low] "Variable initialized with configuration data" */
    LucIpduBuffer = *LpWrBuffer;

    /* Apply the start mask to local I-PDU buffer variable */
    LucIpduBuffer &= (uint8)(*LpMaskingBuffer);
    /* Copy the application  data to local I-PDU buffer variable */
    LucIpduBuffer |= *LpApplBuffer;
    /* Write the application data back to I-PDU buffer */
    *LpWrBuffer = LucIpduBuffer;
    /* Increment the application pointer */
    LpApplBuffer++;
    /* Increment the WrBuffer pointer */
    LpWrBuffer++;
    /* Get the pointer to next Masking buffer */
    LpMaskingBuffer++;
    /* Decrement the size size */
    LddSize--;
    if(LddSize > (PduLengthType)COM_ZERO)
    {
      /* Check whether size of the signal is not equal to one */
      while(LddSize != (PduLengthType)COM_ONE)
      {
        /* @Trace: Com_SUD_API_00782 */
        /* Copy the application buffer data to I-PDU buffer pointer */
        /* polyspace +1 RTE:NIV [Not a defect:Low] "Variable initialized with configuration data" */
        LucIpduBuffer = *LpWrBuffer;
        LucIpduBuffer &= (uint8)(*LpMaskingBuffer);
        LucIpduBuffer |= *LpApplBuffer;
        *LpWrBuffer = LucIpduBuffer;
        /* Get the pointer to next application buffer */
        LpApplBuffer++;
        /* Get the pointer to next I-PDU buffer */
        LpWrBuffer++;
        /* Get the pointer to next Masking buffer */
        LpMaskingBuffer++;
        /* Decrement the signal size count */
        LddSize--;
      }
      /* @Trace: Com_SUD_API_00783 */
      /* Get the value of I-PDU buffer to a local I-PDU buffer variable */
      /* polyspace +1 RTE:NIV [Not a defect:Low] "Variable initialized with configuration data" */
      LucIpduBuffer = *LpWrBuffer;
      /* Apply the end mask to local I-PDU buffer variable to clear unoccupied
      areas */
      LucIpduBuffer &= (uint8)(*LpMaskingBuffer);
      /* Copy the application  data to local variable */
      LucIpduBuffer |= *LpApplBuffer;
      /* Copy the local I-PDU buffer variable data to the I-PDU buffer */
      *LpWrBuffer = LucIpduBuffer;
    }
    /* @Trace: Com_SUD_API_00784 */
    /* Exit protection area */
    #if(COM_TX_INTERRUPT_BASED_PROCESS == STD_OFF)
    SchM_Exit_Com_TX_EXT_SIG_DATA_PROTECTION_AREA();
    #endif
  }/* Check whether signal size is not equal to zero */

  /* @Trace: Com_SUD_API_00785 */
  return (LblReturnValue);
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"


/*******************************************************************************
** Function Name        : Com_PackAndValidateSigGrpArray                      **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function performs validation check on the      **
**                        signal group and returns true if signal is valid.   **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : LpTxPack, LpSigDataPtr                              **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LblReturnValue                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : SchM_Enter_XXX()           **
**                                                 SchM_Exit_XXX()            **
*******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(boolean, COM_CODE) Com_PackAndValidateSigGrpArray
(P2CONST(Com_TxPack, AUTOMATIC, COM_CONST) LpTxPack,
                      P2CONST (void, AUTOMATIC, COM_CONST) LpSigDataPtr,
                      P2VAR (void, AUTOMATIC, COM_VAR) LpTargetDataPtr)
{
  /* @Trace: Com_SUD_API_00786 */
  P2VAR(uint8, AUTOMATIC, COM_VAR) LpWrBuffer;
  P2CONST(uint8, AUTOMATIC, COM_CONST) LpApplBuffer;
  PduLengthType LddSize;
  uint8 LucIpduBuffer;
  /* For checking value has been changed or not */
  uint8 LucIpduBuffer1;
  boolean LblReturnValue;

  /* Initialize return value to true */
  LblReturnValue = COM_FALSE;
  /* Get the size of the signal or signal group */
  LddSize = LpTxPack->ddSigTypeOrSize;
  /* Check whether signal size is not equal to zero */
  if(LddSize != (PduLengthType)COM_ZERO)
  {
    /* @Trace: Com_SUD_API_00787 */
    /* Get the pointer to application buffer */
    LpApplBuffer = (P2CONST(uint8, AUTOMATIC, COM_CONST)) LpSigDataPtr;
    /* Get the pointer to an I-PDU buffer */
    LpWrBuffer = (P2VAR(uint8, AUTOMATIC, COM_VAR)) LpTargetDataPtr;
    /* Enter protection area */
    #if(COM_TX_INTERRUPT_BASED_PROCESS == STD_OFF)
    SchM_Enter_Com_TX_EXT_SIG_DATA_PROTECTION_AREA();
    #endif
    /* Get the data from the I-PDU buffer pointer to a local I-PDU buffer
    variable */
    /* polyspace +1 RTE:NIV [Not a defect:Low] "Variable initialized with configuration data" */
    LucIpduBuffer = *LpWrBuffer;
    /* For checking value has been changed or not */
    LucIpduBuffer1 = LucIpduBuffer;

    /* Apply the start mask to local I-PDU buffer variable */
    LucIpduBuffer &= LpTxPack->ucWrStartMask;
    /* Copy the application  data to local I-PDU buffer variable */
    LucIpduBuffer |= *LpApplBuffer;
    /* Write the application data back to I-PDU buffer */
    *LpWrBuffer = LucIpduBuffer;
    /* For checking value has been changed or not */
    if(LucIpduBuffer != LucIpduBuffer1)
    {
      /* @Trace: Com_SUD_API_00788 */
      LblReturnValue = COM_TRUE;
    }
    /* @Trace: Com_SUD_API_00789 */
    /* Increment the application pointer */
    LpApplBuffer++;
    /* Increment the WrBuffer pointer */
    LpWrBuffer++;
    /* Decrement the size size */
    LddSize--;
    if(LddSize > (PduLengthType)COM_ZERO)
    {
      /* Check whether size of the signal is not equal to one */
      while(LddSize != (PduLengthType)COM_ONE)
      {
        /* For checking value has been changed or not */
        /* polyspace +1 RTE:NIV [Not a defect:Low] "Variable initialized with configuration data" */
        if(*LpWrBuffer != *LpApplBuffer)
        {
          /* @Trace: Com_SUD_API_00790 */
          LblReturnValue = COM_TRUE;
          /* Copy the application buffer data to I-PDU buffer pointer */
          *LpWrBuffer = *LpApplBuffer;
        }
        /* @Trace: Com_SUD_API_00791 */
        /* Get the pointer to next application buffer */
        LpApplBuffer++;
        /* Get the pointer to next I-PDU buffer */
        LpWrBuffer++;
        /* Decrement the signal size count */
        LddSize--;
      }
      /* @Trace: Com_SUD_API_00792 */
      /* Get the value of I-PDU buffer to a local I-PDU buffer variable */
      /* polyspace +1 RTE:NIV [Not a defect:Low] "Variable initialized with configuration data" */
      LucIpduBuffer = *LpWrBuffer;
      /* For checking value has been changed or not */
      LucIpduBuffer1 = LucIpduBuffer;
      /* Apply the end mask to local I-PDU buffer variable to clear unoccupied
      areas */
      LucIpduBuffer &= LpTxPack->ucWrEndMask;
      /* Copy the application  data to local variable */
      LucIpduBuffer |= *LpApplBuffer;
      /* Copy the local I-PDU buffer variable data to the I-PDU buffer */
      *LpWrBuffer = LucIpduBuffer;
      /* For checking value has been changed or not */
       if(LucIpduBuffer != LucIpduBuffer1)
      {
        /* @Trace: Com_SUD_API_00793 */
        LblReturnValue = COM_TRUE;
      }
    }
    /* @Trace: Com_SUD_API_00794 */
    /* Exit protection area */
    #if(COM_TX_INTERRUPT_BASED_PROCESS == STD_OFF)
    SchM_Exit_Com_TX_EXT_SIG_DATA_PROTECTION_AREA();
    #endif
  }/* Check whether signal size is not equal to zero */

  /* @Trace: Com_SUD_API_00795 */
  return (LblReturnValue);
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name        : Com_PackSigGrpArray                                 **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function performs validation check on the      **
**                        signal group and returns true if signal is valid.   **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : LpTxPack, LpSigDataPtr                              **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LblReturnValue                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : SchM_Enter_XXX()           **
**                                                 SchM_Exit_XXX()            **
*******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(boolean, COM_CODE) Com_PackSigGrpArray
(P2CONST(Com_TxPack, AUTOMATIC, COM_CONST) LpTxPack,
                      P2CONST (void, AUTOMATIC, COM_CONST) LpSigDataPtr,
                      P2VAR (void, AUTOMATIC, COM_VAR) LpTargetDataPtr)
{
  /* @Trace: Com_SUD_API_00796 */
  P2VAR(uint8, AUTOMATIC, COM_VAR) LpWrBuffer;
  P2CONST(uint8, AUTOMATIC, COM_CONST) LpApplBuffer;
  PduLengthType LddSize;
  uint8 LucIpduBuffer;
  boolean LblReturnValue;

  /* Initialize return value to true */
  LblReturnValue = COM_FALSE;
  /* Get the size of the signal or signal group */
  LddSize = LpTxPack->ddSigTypeOrSize;
  /* Check whether signal size is not equal to zero */
  if(LddSize != (PduLengthType)COM_ZERO)
  {
    /* @Trace: Com_SUD_API_00797 */
    /* Get the pointer to application buffer */
    LpApplBuffer = (P2CONST(uint8, AUTOMATIC, COM_CONST)) LpSigDataPtr;
    /* Get the pointer to an I-PDU buffer */
    LpWrBuffer = (P2VAR(uint8, AUTOMATIC, COM_VAR)) LpTargetDataPtr;
    /* Enter protection area */
    #if(COM_TX_INTERRUPT_BASED_PROCESS == STD_OFF)
    SchM_Enter_Com_TX_EXT_SIG_DATA_PROTECTION_AREA();
    #endif
    /* Get the data from the I-PDU buffer pointer to a local I-PDU buffer
    variable */
    /* polyspace +1 RTE:NIV [Not a defect:Low] "Variable initialized with configuration data" */
    LucIpduBuffer = *LpWrBuffer;

    /* Apply the start mask to local I-PDU buffer variable */
    LucIpduBuffer &= LpTxPack->ucWrStartMask;
    /* Copy the application  data to local I-PDU buffer variable */
    /* polyspace +1 RTE:NIV [Not a defect:Low] "Variable initialized with configuration data" */
    LucIpduBuffer |= *LpApplBuffer;
    /* Write the application data back to I-PDU buffer */
    *LpWrBuffer = LucIpduBuffer;
    /* Increment the application pointer */
    LpApplBuffer++;
    /* Increment the WrBuffer pointer */
    LpWrBuffer++;
    /* Decrement the size size */
    LddSize--;
    if(LddSize > (PduLengthType)COM_ZERO)
    {
      /* Check whether size of the signal is not equal to one */
      while(LddSize != (PduLengthType)COM_ONE)
      {
        /* @Trace: Com_SUD_API_00798 */
        /* Copy the application buffer data to I-PDU buffer pointer */
        /* polyspace +1 RTE:NIV [Not a defect:Low] "Variable initialized with configuration data" */
        *LpWrBuffer = *LpApplBuffer;
        /* Get the pointer to next application buffer */
        LpApplBuffer++;
        /* Get the pointer to next I-PDU buffer */
        LpWrBuffer++;
        /* Decrement the signal size count */
        LddSize--;
      }
      /* @Trace: Com_SUD_API_00799 */
      /* Get the value of I-PDU buffer to a local I-PDU buffer variable */
      /* polyspace +1 RTE:NIV [Not a defect:Low] "Variable initialized with configuration data" */
      LucIpduBuffer = *LpWrBuffer;
      /* Apply the end mask to local I-PDU buffer variable to clear unoccupied
      areas */
      LucIpduBuffer &= LpTxPack->ucWrEndMask;
      /* Copy the application  data to local variable */
      /* polyspace +1 RTE:NIV [Not a defect:Low] "Variable initialized with configuration data" */
      LucIpduBuffer |= *LpApplBuffer;
      /* Copy the local I-PDU buffer variable data to the I-PDU buffer */
      *LpWrBuffer = LucIpduBuffer;
    }
    /* @Trace: Com_SUD_API_00800 */
    /* Exit protection area */
    #if(COM_TX_INTERRUPT_BASED_PROCESS == STD_OFF)
    SchM_Exit_Com_TX_EXT_SIG_DATA_PROTECTION_AREA();
    #endif
  }/* Check whether signal size is not equal to zero */

  /* @Trace: Com_SUD_API_00801 */
  return (LblReturnValue);
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
/* #7709 end */
/*******************************************************************************
** Function Name        : Com_PackEightBytes                                  **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function packs the signal which spread across  **
**                        eight bytes in an I-PDU.                            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same signal.                  **
**                        Reentrant for different signals.                    **
**                                                                            **
** Input Parameters     : LpTxPack, LpSigDataPtr                              **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : SchM_Enter_XXX()           **
**                                                 SchM_Exit_XXX()            **
*******************************************************************************/

/* Pack function for a float32 signal that can be fit in 8 bytes */
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE) Com_PackEightBytes
  (P2CONST(Com_TxPack, AUTOMATIC, COM_CONST) LpTxPack,
  P2CONST (void, AUTOMATIC, COM_CONST) LpSigDataPtr)
{
  /* @Trace: Com_SUD_API_00802 */
  P2CONST(uint8, AUTOMATIC, COM_VAR) LpAppSigPtr;
  P2VAR(uint8, AUTOMATIC, COM_VAR) LpWrBuffer;
  PduLengthType LucNoOfByte;
  /* Get the pointer to I-PDU buffer */
  LpWrBuffer = (LpTxPack->pWrBuffer);
  /* Get the number of bytes of data */
  LucNoOfByte = (LpTxPack->ddSigTypeOrSize);
  /* Get the number of bytes that signal spread across */
  LucNoOfByte = LucNoOfByte & COM_SIG_BYTE_MASK_VALUE;
  /* Get the address of the signal buffer */
  LpAppSigPtr = (P2CONST(uint8, AUTOMATIC, COM_VAR)) LpSigDataPtr;
  /* Enter protection area */
  #if(COM_TX_INTERRUPT_BASED_PROCESS == STD_OFF)
  SchM_Enter_Com_TX_EXT_SIG_DATA_PROTECTION_AREA();
  #endif
  /* Loop for number of bytes of data */
  while(LucNoOfByte != COM_ZERO)
  {
    /* @Trace: Com_SUD_API_00803 */
    /* Copy data from application signal pointer to I-PDU buffer */
    *LpWrBuffer = *LpAppSigPtr;
    #if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)
    /* @Trace: Com_SUD_API_01622 */
    /* Decrement application signal pointer */
    LpAppSigPtr--;
    /* Decrement I-PDU buffer pointer */
    LpWrBuffer--;
    #else
    /* @Trace: Com_SUD_API_01623 */
    /* Increment application signal pointer */
    LpAppSigPtr++;
    /* Increment I-PDU buffer pointer */
    LpWrBuffer++;
    #endif
    /* @Trace: Com_SUD_API_01624 */
    LucNoOfByte--;
  }
  /* @Trace: Com_SUD_API_00804 */
  /* Exit protection area */
  #if(COM_TX_INTERRUPT_BASED_PROCESS == STD_OFF)
  SchM_Exit_Com_TX_EXT_SIG_DATA_PROTECTION_AREA();
  #endif
}

#define COM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name        : Com_PackEightByteOrdering                           **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function packs the signal which spread across  **
**                        five bytes in an I-PDU and needs                    **
**                        Endianness Conversion                               **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same signal.                  **
**                        Reentrant for different signals.                    **
**                                                                            **
** Input Parameters     : LpTxPack, LpSigDataPtr                              **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : SchM_Enter_XXX()           **
**                                                 SchM_Exit_XXX()            **
*******************************************************************************/

/* Pack function for a float32 signal that can be fit in 8 bytes */
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE) Com_PackEightByteOrdering
  (P2CONST(Com_TxPack, AUTOMATIC, COM_CONST) LpTxPack,
  P2CONST (void, AUTOMATIC, COM_CONST) LpSigDataPtr)
{
  /* @Trace: Com_SUD_API_00805 */
  P2CONST(uint8, AUTOMATIC, COM_VAR) LpAppSigPtr;
  P2VAR(uint8, AUTOMATIC, COM_VAR) LpWrBuffer;
  P2CONST(uint32, AUTOMATIC, COM_CONST) LpSigDataPtr32;
  /* Buffer to temporarily hold data */
  Com_MIdWord_Access LaaApplSignal[COM_TWO];
  PduLengthType LucNoOfByte;
  /* Get the pointer to I-PDU buffer */
  LpWrBuffer = (LpTxPack->pWrBuffer);
  #if (CPU_BYTE_ORDER == LOW_BYTE_FIRST)
  /* Get signal actual type */
  uint8 LucType = LpTxPack->ucType;
  /* Modify LpWrBuffer pointer to point to correct MSB position in case
   * network byte order is different from system byte order */
  /* polyspace-begin MISRA2012:18.4 [Justified:Low] "Pointer access accepted for buffer processing. There is no safety impact" */
  if ((LucType == COM_SIG_TYPE_UINT16) ||
    (LucType == COM_SIG_TYPE_SINT16))
  {
    /* @Trace: Com_SUD_API_01905 */
    LpWrBuffer += COM_ONE;
  } else if ((LucType == COM_SIG_TYPE_UINT32) ||
    (LucType == COM_SIG_TYPE_SINT32))
  {
    /* @Trace: Com_SUD_API_01906 */
    LpWrBuffer += COM_THREE;
  } else if ((LucType == COM_SIG_TYPE_UINT64) ||
    (LucType == COM_SIG_TYPE_SINT64))
  {
    /* @Trace: Com_SUD_API_01907 */
    LpWrBuffer += COM_SEVEN;
  } else
  {
    /*Do nothing*/
  }
  /* polyspace-end MISRA2012:18.4 [Justified:Low] "Pointer access accepted for buffer processing. There is no safety impact" */
  #endif
  /* @Trace: Com_SUD_API_01908 */
  /* Get the number of bytes of data */
  LucNoOfByte = (LpTxPack->ddSigTypeOrSize);
  /* Get the number of bytes that signal spread across */
  LucNoOfByte = LucNoOfByte & COM_SIG_BYTE_MASK_VALUE;

  LpSigDataPtr32 = (P2CONST(uint32, AUTOMATIC, COM_CONST)) LpSigDataPtr;
  /* Enter protection area */
  /* Get the the signal value to double word variable */
  LaaApplSignal[COM_ZERO].whole_dword = *LpSigDataPtr32;
  LpSigDataPtr32++;
  /* Get the upper bytes */
  LaaApplSignal[COM_ONE].whole_dword = *LpSigDataPtr32;
  LpAppSigPtr =
    (P2VAR(uint8, AUTOMATIC, COM_VAR))
    &LaaApplSignal[COM_ZERO].byte_val.BO_Byte[COM_DWORD_LS_BYTE_IDX];
  #if(COM_TX_INTERRUPT_BASED_PROCESS == STD_OFF)
  SchM_Enter_Com_TX_EXT_SIG_DATA_PROTECTION_AREA();
  #endif
  /* Loop for number of bytes of data */
  while((LucNoOfByte != COM_ZERO) && (LucNoOfByte <= COM_EIGHT))
  {
    /* @Trace: Com_SUD_API_00806 */
    /* Copy data from application signal pointer to I-PDU buffer */
    *LpWrBuffer = *LpAppSigPtr;
    #if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)
    /* @Trace: Com_SUD_API_01625 */
    /* Decrement application signal pointer */
    LpAppSigPtr--;
    /* Decrement I-PDU buffer pointer */
    LpWrBuffer++;
    #else
    /* @Trace: Com_SUD_API_01626 */
    /* Increment application signal pointer */
    LpAppSigPtr++;
    /* Increment I-PDU buffer pointer */
    LpWrBuffer--;
    #endif
    /* @Trace: Com_SUD_API_01627 */
    LucNoOfByte--;
  }
  /* @Trace: Com_SUD_API_00807 */
  /* Exit protection area */
  #if(COM_TX_INTERRUPT_BASED_PROCESS == STD_OFF)
  SchM_Exit_Com_TX_EXT_SIG_DATA_PROTECTION_AREA();
  #endif
}

#define COM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name        : Com_PackNineBytes                                   **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function packs the signal which spread across  **
**                        five bytes in an I-PDU.                             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same signal.                  **
**                        Reentrant for different signals.                    **
**                                                                            **
** Input Parameters     : LpTxPack, LpSigDataPtr                              **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : SchM_Enter_XXX()           **
**                                                 SchM_Exit_XXX()            **
*******************************************************************************/

#define COM_START_SEC_CODE
#include "MemMap.h"

FUNC(void, COM_CODE) Com_PackNineBytes
  (P2CONST(Com_TxPack, AUTOMATIC, COM_CONST) LpTxPack,
  P2CONST (void, AUTOMATIC, COM_CONST) LpSigDataPtr)
{
  /* @Trace: Com_SUD_API_00808 */
  P2VAR(uint8, AUTOMATIC, COM_VAR) LpWrBuffer;
  P2VAR(uint8, AUTOMATIC, COM_VAR) LpAppSigPtr;
  P2CONST(uint32, AUTOMATIC, COM_CONST) LpSigDataPtr32;
  Com_MIdWord_Access LaaApplSignal[COM_THREE];
  uint8 LucShiftOrData;
  uint8 LucEndMask;
  /* Get the local pointer to I-PDU buffer */
  LpWrBuffer =
  (P2VAR(uint8, AUTOMATIC, COM_VAR)) LpTxPack->pWrBuffer;
  LpSigDataPtr32 = (P2CONST(uint32, AUTOMATIC, COM_CONST))
    LpSigDataPtr;
  /* Copy signal data to double word variable */
  LaaApplSignal[COM_ZERO].whole_dword = *LpSigDataPtr32;
  /* Copy signal data to double word variable */
  LaaApplSignal[COM_ONE].whole_dword = *LpSigDataPtr32;
  /* Get the number of shift bits to a local variable */
  LucShiftOrData = LpTxPack->ucNoOfShiftBit;
  /* Shift the double word variable left by the number of shift bits to get
  start position of signal in I-PDU */
  LaaApplSignal[COM_ZERO].whole_dword <<= LucShiftOrData;
  /* Shift the double word variable left by the number of shift bits to get
  start position of signal in I-PDU */
  LaaApplSignal[COM_ONE].whole_dword >>= (COM_THIRTY_TWO - LucShiftOrData);
  /* Increment the pointer to point to the next 32 bits */
  LpSigDataPtr32++;
  /* Get the data in the local buffer */
  LaaApplSignal[COM_ONE].whole_dword |= ((*LpSigDataPtr32) << LucShiftOrData);
  /* Copy the second set of data to a local variable */
  LaaApplSignal[COM_TWO].whole_dword = *LpSigDataPtr32;
  /* Shift the data to get the upper byte */
  LaaApplSignal[COM_TWO].whole_dword >>= (COM_THIRTY_TWO - LucShiftOrData);
  /* Get the end mask value to a local variable */
  LucEndMask = LpTxPack->ucWrEndMask;
  /* Point to the first byte to be copied */
  LpAppSigPtr =
    (P2VAR(uint8, AUTOMATIC, COM_VAR))
    &LaaApplSignal[COM_ZERO].byte_val.BO_Byte[COM_DWORD_LS_BYTE_IDX];

  /* Get the data from I-PDU buffer pointer to local variable */
  LucShiftOrData = *LpWrBuffer;
  /* Clear signal data from local I-PDU buffer variable by applying start
  mask */
  LucShiftOrData &= LpTxPack->ucWrStartMask;
  /* Write data from application buffer pointer to a local I-PDU buffer
  variable */
  LucShiftOrData |= *LpAppSigPtr;
  /* Copy data into I-PDU buffer from local I-PDU buffer variable */
  *LpWrBuffer = LucShiftOrData;
  #if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)
  /* @Trace: Com_SUD_API_01628 */
  /* Decrement application signal pointer */
  LpAppSigPtr--;
  /* Decrement I-PDU buffer pointer */
  LpWrBuffer--;
  #else
  /* @Trace: Com_SUD_API_01629 */
  /* Increment application signal pointer */
  LpAppSigPtr++;
  /* Increment I-PDU buffer pointer */
  LpWrBuffer++;
  #endif
  /* @Trace: Com_SUD_API_01630 */
  /* Get the number of bytes of data */
  LucShiftOrData = COM_EIGHT;
  /* Loop for number of bytes of data */
  do
  {
    /* @Trace: Com_SUD_API_00809 */
    /* Copy data from application signal pointer to I-PDU buffer */
    *LpWrBuffer = *LpAppSigPtr;
    #if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)
    /* @Trace: Com_SUD_API_01631 */
    /* Decrement application signal pointer */
    LpAppSigPtr--;
    /* Decrement I-PDU buffer pointer */
    LpWrBuffer--;
    #else
    /* @Trace: Com_SUD_API_01632 */
    /* Increment application signal pointer */
    LpAppSigPtr++;
    /* Increment I-PDU buffer pointer */
    LpWrBuffer++;
    #endif
    /* @Trace: Com_SUD_API_01633 */
    /* Decrement the number of bytes of data */
    LucShiftOrData--;
  }while(LucShiftOrData != COM_FIVE);

  /* @Trace: Com_SUD_API_00810 */
  LpAppSigPtr =
    (P2VAR(uint8, AUTOMATIC, COM_VAR))
    &LaaApplSignal[COM_ONE].byte_val.BO_Byte[COM_DWORD_LS_BYTE_IDX];

  do
  {
    /* @Trace: Com_SUD_API_00811 */
    /* Copy data from application signal pointer to I-PDU buffer */
    *LpWrBuffer = *LpAppSigPtr;
    #if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)
    /* @Trace: Com_SUD_API_01634 */
    /* Decrement application signal pointer */
    LpAppSigPtr--;
    /* Decrement I-PDU buffer pointer */
    LpWrBuffer--;
    #else
    /* @Trace: Com_SUD_API_01635 */
    /* Increment application signal pointer */
    LpAppSigPtr++;
    /* Increment I-PDU buffer pointer */
    LpWrBuffer++;
    #endif
    /* @Trace: Com_SUD_API_01636 */
    /* Decrement the number of bytes of data */
    LucShiftOrData--;
  }while(LucShiftOrData != COM_ONE);

  /* @Trace: Com_SUD_API_00812 */
  /* Get the data from I-PDU buffer pointer to local I-PDU buffer variable */
  LucShiftOrData = *LpWrBuffer;
  /*Clear signal data from the local I-PDU buffer variable by applying end mask
  to it */
  LucShiftOrData &= LucEndMask;
  /* Copy higher byte data of word variable to local I-PDU buffer */
  LucShiftOrData |= 
    (LaaApplSignal[COM_TWO].byte_val.BO_Byte[COM_DWORD_LS_BYTE_IDX]);
  /* Store the local I-PDU buffer data into local I-PDU buffer variable */
  *LpWrBuffer = LucShiftOrData;
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Com_PackNineByteOrdering                            **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function packs the signal which spread across  **
**                        five bytes in an I-PDU.                             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same signal.                  **
**                        Reentrant for different signals.                    **
**                                                                            **
** Input Parameters     : LpTxPack, LpSigDataPtr                              **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : SchM_Enter_XXX()           **
**                                                 SchM_Exit_XXX()            **
*******************************************************************************/

#define COM_START_SEC_CODE
#include "MemMap.h"

FUNC(void, COM_CODE) Com_PackNineByteOrdering
  (P2CONST(Com_TxPack, AUTOMATIC, COM_CONST) LpTxPack,
  P2CONST (void, AUTOMATIC, COM_CONST) LpSigDataPtr)
{
  /* @Trace: Com_SUD_API_00813 */
  P2VAR(uint8, AUTOMATIC, COM_VAR) LpWrBuffer;
  P2VAR(uint8, AUTOMATIC, COM_VAR) LpAppSigPtr;
  P2CONST(uint32, AUTOMATIC, COM_CONST) LpSigDataPtr32;
  Com_MIdWord_Access LaaApplSignal[COM_THREE];
  uint8 LucShiftOrData;
  uint8 LucEndMask;
  /* Get the local pointer to I-PDU buffer */
  LpWrBuffer =
  (P2VAR(uint8, AUTOMATIC, COM_VAR)) LpTxPack->pWrBuffer;
  #if (CPU_BYTE_ORDER == LOW_BYTE_FIRST)
  /* Get signal actual type */
  uint8 LucType = LpTxPack->ucType;
  /* Modify LpWrBuffer pointer to point to correct MSB position in case
   * network byte order is different from system byte order */
  /* polyspace-begin MISRA2012:18.4 [Justified:Low] "Pointer access accepted for buffer processing. There is no safety impact" */
  if ((LucType == COM_SIG_TYPE_UINT16) ||
    (LucType == COM_SIG_TYPE_SINT16))
  {
    /* @Trace: Com_SUD_API_01909 */
    LpWrBuffer += COM_ONE;
  } else if ((LucType == COM_SIG_TYPE_UINT32) ||
    (LucType == COM_SIG_TYPE_SINT32))
  {
    /* @Trace: Com_SUD_API_01910 */
    LpWrBuffer += COM_THREE;
  } else if ((LucType == COM_SIG_TYPE_UINT64) ||
    (LucType == COM_SIG_TYPE_SINT64))
  {
    /* @Trace: Com_SUD_API_01911 */
    LpWrBuffer += COM_SEVEN;
  } else
  {
    /*Do nothing*/
  }
  /* polyspace-end MISRA2012:18.4 [Justified:Low] "Pointer access accepted for buffer processing. There is no safety impact" */
  #endif
  /* @Trace: Com_SUD_API_01912 */
  LpSigDataPtr32 = (P2CONST(uint32, AUTOMATIC, COM_CONST))
    LpSigDataPtr;
  /* Copy signal data to double word variable */
  LaaApplSignal[COM_ZERO].whole_dword = *LpSigDataPtr32;
  /* Copy signal data to double word variable */
  LaaApplSignal[COM_ONE].whole_dword = *LpSigDataPtr32;
  /* Get the number of shift bits to a local variable */
  LucShiftOrData = LpTxPack->ucNoOfShiftBit;
  /* Shift the double word variable left by the number of shift bits to get
  start position of signal in I-PDU */
  LaaApplSignal[COM_ZERO].whole_dword <<= LucShiftOrData;
  /* Shift the double word variable left by the number of shift bits to get
  start position of signal in I-PDU */
  LaaApplSignal[COM_ONE].whole_dword >>= (COM_THIRTY_TWO - LucShiftOrData);
  /* Increment the pointer to point to the next 32 bits */
  LpSigDataPtr32++;
  /* Get the data in the local buffer */
  LaaApplSignal[COM_ONE].whole_dword |= ((*LpSigDataPtr32) << LucShiftOrData);
  /* Copy the second set of data to a local variable */
  LaaApplSignal[COM_TWO].whole_dword = *LpSigDataPtr32;
  /* Shift the data to get the upper byte */
  LaaApplSignal[COM_TWO].whole_dword >>= (COM_THIRTY_TWO - LucShiftOrData);
  /* Get the end mask value to a local variable */
  LucEndMask = LpTxPack->ucWrEndMask;
  /* Point to the first byte to be copied */
  LpAppSigPtr = (P2VAR(uint8, AUTOMATIC, COM_VAR))
    &LaaApplSignal[COM_ZERO].byte_val.BO_Byte[COM_DWORD_LS_BYTE_IDX];
  LucShiftOrData = *LpWrBuffer;
  /* Clear signal data from local I-PDU buffer variable by applying start
  mask */
  LucShiftOrData &= LpTxPack->ucWrStartMask;
  /* Write data from application buffer pointer to a local I-PDU buffer
  variable */
  LucShiftOrData |= *LpAppSigPtr;
  /* Copy data into I-PDU buffer from local I-PDU buffer variable */
  *LpWrBuffer = LucShiftOrData;
  #if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)
  /* @Trace: Com_SUD_API_01637 */
  /* Decrement application signal pointer */
  LpAppSigPtr--;
  /* Decrement I-PDU buffer pointer */
  LpWrBuffer++;
  #else
  /* @Trace: Com_SUD_API_01638 */
  /* Increment application signal pointer */
  LpAppSigPtr++;
  /* Increment I-PDU buffer pointer */
  LpWrBuffer--;
  #endif
  /* @Trace: Com_SUD_API_01639 */
  /* Get the number of bytes of data */
  LucShiftOrData = COM_EIGHT;
  /* Loop for number of bytes of data */
  do
  {
    /* @Trace: Com_SUD_API_00814 */
    /* Copy data from application signal pointer to I-PDU buffer */
    *LpWrBuffer = *LpAppSigPtr;
    #if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)
    /* @Trace: Com_SUD_API_01640 */
    /* Decrement application signal pointer */
    LpAppSigPtr--;
    /* Decrement I-PDU buffer pointer */
    LpWrBuffer++;
    #else
    /* @Trace: Com_SUD_API_01641 */
    /* Increment application signal pointer */
    LpAppSigPtr++;
    /* Increment I-PDU buffer pointer */
    LpWrBuffer--;
    #endif
    /* @Trace: Com_SUD_API_01642 */
    /* Decrement the number of bytes of data */
    LucShiftOrData--;
  }while(LucShiftOrData != COM_FIVE);

  /* @Trace: Com_SUD_API_00815 */
  LpAppSigPtr = (P2VAR(uint8, AUTOMATIC, COM_VAR))
      &LaaApplSignal[COM_ONE].byte_val.BO_Byte[COM_DWORD_LS_BYTE_IDX];

  do
  {
    /* @Trace: Com_SUD_API_00816 */
    /* Copy data from application signal pointer to I-PDU buffer */
    *LpWrBuffer = *LpAppSigPtr;
    #if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)
    /* @Trace: Com_SUD_API_01643 */
    /* Decrement application signal pointer */
    LpAppSigPtr--;
    /* Decrement I-PDU buffer pointer */
    LpWrBuffer++;
    #else
    /* @Trace: Com_SUD_API_01644 */
    /* Increment application signal pointer */
    LpAppSigPtr++;
    /* Increment I-PDU buffer pointer */
    LpWrBuffer--;
    #endif
    /* @Trace: Com_SUD_API_01645 */
    /* Decrement the number of bytes of data */
    LucShiftOrData--;
  }while(LucShiftOrData != COM_ONE);

  /* @Trace: Com_SUD_API_00817 */
  /* Get the data from I-PDU buffer pointer to local I-PDU buffer variable */
  LucShiftOrData = *LpWrBuffer;
  /*Clear signal data from the local I-PDU buffer variable by applying end mask
  to it */
  LucShiftOrData &= LucEndMask;
  /* Copy higher byte data of word variable to local I-PDU buffer */
  LucShiftOrData |= 
    (LaaApplSignal[COM_TWO].byte_val.BO_Byte[COM_DWORD_LS_BYTE_IDX]);
  /* Store the local I-PDU buffer data into local I-PDU buffer variable */
  *LpWrBuffer = LucShiftOrData;
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name        : Com_PackByte64Bit                                   **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function packs the signal which spread across  **
**                        five bytes in an I-PDU.                             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same signal.                  **
**                        Reentrant for different signals.                    **
**                                                                            **
** Input Parameters     : LpTxPack, LpSigDataPtr                              **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : SchM_Enter_XXX()           **
**                                                 SchM_Exit_XXX()            **
*******************************************************************************/

#define COM_START_SEC_CODE
#include "MemMap.h"

FUNC(void, COM_CODE) Com_PackBytes64bit
  (P2CONST(Com_TxPack, AUTOMATIC, COM_CONST) LpTxPack,
  P2CONST (void, AUTOMATIC, COM_CONST) LpSigDataPtr)
{
  /* @Trace: Com_SUD_API_00818 */
  P2VAR(uint8, AUTOMATIC, COM_VAR) LpWrBuffer;
  P2VAR(uint8, AUTOMATIC, COM_VAR) LpAppSigPtr;
  P2CONST(uint32, AUTOMATIC, COM_CONST) LpSigDataPtr32;
  Com_MIdWord_Access LaaApplSignal[COM_THREE];
  uint8 LucShiftOrData;
  uint8 LucEndMask;
  PduLengthType LucNoOfByte;
  uint8 LucSizeOrData;
  
  LucNoOfByte = (uint8)(LpTxPack->ddSigTypeOrSize);
  /* Get the number of bytes that signal spread across */
  LucSizeOrData = (uint8)(LucNoOfByte & COM_SIG_BYTE_MASK_VALUE);
  LaaApplSignal[COM_ZERO].whole_dword = COM_ZERO;
  LaaApplSignal[COM_ONE].whole_dword = COM_ZERO;
  LaaApplSignal[COM_TWO].whole_dword = COM_ZERO;
  /* Get the local pointer to I-PDU buffer */
  LpWrBuffer =
  (P2VAR(uint8, AUTOMATIC, COM_VAR)) LpTxPack->pWrBuffer;
  LpSigDataPtr32 = (P2CONST(uint32, AUTOMATIC, COM_CONST))
    LpSigDataPtr;

  /* Copy signal data to double word variable */
  LaaApplSignal[COM_ZERO].whole_dword = *LpSigDataPtr32;
  /* Copy signal data to double word variable */
  /* Get the number of shift bits to a local variable */
  LucShiftOrData = LpTxPack->ucNoOfShiftBit;
    /* Increment the pointer to point to the next 32 bits */
  LpSigDataPtr32++;

  if(LucShiftOrData != 0)
  {
    /* @Trace: Com_SUD_API_00819 */
    /* Shift the double word variable left by the number of shift bits to get
    start position of signal in I-PDU */
    LaaApplSignal[COM_TWO].whole_dword = LaaApplSignal[COM_ZERO].whole_dword;
    LaaApplSignal[COM_ZERO].whole_dword <<= LucShiftOrData;
    /* Shift the double word variable left by the number of shift bits to get
    start position of signal in I-PDU */
    LaaApplSignal[COM_ONE].whole_dword |= (LaaApplSignal[COM_TWO].whole_dword)>>(32 - LucShiftOrData);

    /* Get the data in the local buffer */
    LaaApplSignal[COM_TWO].whole_dword = COM_ZERO;
    LaaApplSignal[COM_TWO].whole_dword = ((*LpSigDataPtr32) << LucShiftOrData);
    LaaApplSignal[COM_ONE].whole_dword |= LaaApplSignal[COM_TWO].whole_dword;
    /* Copy the second set of data to a local variable */
  }
  else
  {
    /* @Trace: Com_SUD_API_00820 */
    LaaApplSignal[COM_ONE].whole_dword = *LpSigDataPtr32;
  }
  /* @Trace: Com_SUD_API_00821 */
  /* Point to the first byte to be copied */
  LpAppSigPtr =
    (P2VAR(uint8, AUTOMATIC, COM_VAR))
    &LaaApplSignal[COM_ZERO].byte_val.BO_Byte[COM_DWORD_LS_BYTE_IDX];

  /* Get the data from I-PDU buffer pointer to local variable */
  LucShiftOrData = *LpWrBuffer;
  /* Clear signal data from local I-PDU buffer variable by applying start
  mask */
  LucShiftOrData &= LpTxPack->ucWrStartMask;
  /* Write data from application buffer pointer to a local I-PDU buffer
  variable */
  LucShiftOrData |= *LpAppSigPtr;
  /* Copy data into I-PDU buffer from local I-PDU buffer variable */
  *LpWrBuffer = LucShiftOrData;
  #if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)
  /* @Trace: Com_SUD_API_01646 */
  /* Decrement application signal pointer */
  LpAppSigPtr--;
  /* Decrement I-PDU buffer pointer */
  LpWrBuffer--;
  #else
  /* @Trace: Com_SUD_API_01647 */
  /* Increment application signal pointer */
  LpAppSigPtr++;
  /* Increment I-PDU buffer pointer */
  LpWrBuffer++;
  #endif
  /* @Trace: Com_SUD_API_01648 */
  /* Get the number of bytes of data */
  LucShiftOrData = 3;
  /* Loop for number of bytes of data */
  do
  {
    /* @Trace: Com_SUD_API_00822 */
    /* Copy data from application signal pointer to I-PDU buffer */
    *LpWrBuffer = *LpAppSigPtr;
    #if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)
    /* @Trace: Com_SUD_API_01649 */
    /* Decrement application signal pointer */
    LpAppSigPtr--;
    /* Decrement I-PDU buffer pointer */
    LpWrBuffer--;
    #else
    /* @Trace: Com_SUD_API_01650 */
    /* Increment application signal pointer */
    LpAppSigPtr++;
    /* Increment I-PDU buffer pointer */
    LpWrBuffer++;
    #endif
    /* @Trace: Com_SUD_API_01651 */
    /* Decrement the number of bytes of data */
    LucShiftOrData--;
  }while(LucShiftOrData != 0);

  /* @Trace: Com_SUD_API_00823 */
  LucShiftOrData = LucSizeOrData  - 4; 
  LpAppSigPtr =
    (P2VAR(uint8, AUTOMATIC, COM_VAR))
    &LaaApplSignal[COM_ONE].byte_val.BO_Byte[COM_DWORD_LS_BYTE_IDX];

  do
  {
    /* @Trace: Com_SUD_API_00824 */
    /* Copy data from application signal pointer to I-PDU buffer */
    *LpWrBuffer = *LpAppSigPtr;
    #if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)
    /* @Trace: Com_SUD_API_01652 */
    /* Decrement application signal pointer */
    LpAppSigPtr--;
    /* Decrement I-PDU buffer pointer */
    LpWrBuffer--;
    #else
    /* @Trace: Com_SUD_API_01653 */
    /* Increment application signal pointer */
    LpAppSigPtr++;
    /* Increment I-PDU buffer pointer */
    LpWrBuffer++;
    #endif
    /* @Trace: Com_SUD_API_01654 */
    /* Decrement the number of bytes of data */
    LucShiftOrData--;
  }while(LucShiftOrData != 0);

  /* @Trace: Com_SUD_API_00825 */
  /* Get the end mask value to a local variable */
  LucEndMask = LpTxPack->ucWrEndMask;
  /* Get the data from I-PDU buffer pointer to local I-PDU buffer variable */
  LucShiftOrData = *LpWrBuffer;
  /*Clear signal data from the local I-PDU buffer variable by applying end mask
  to it */
  LucShiftOrData &= LucEndMask;
  /* Copy higher byte data of word variable to local I-PDU buffer */

   /*Store the local I-PDU buffer data into local I-PDU buffer variable */
  *LpWrBuffer = LucShiftOrData;
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Com_PackBytes64bitOrdering                          **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function packs the signal which spread across  **
**                        five bytes in an I-PDU.                             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same signal.                  **
**                        Reentrant for different signals.                    **
**                                                                            **
** Input Parameters     : LpTxPack, LpSigDataPtr                              **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : SchM_Enter_XXX()           **
**                                                 SchM_Exit_XXX()            **
*******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"

FUNC(void, COM_CODE) Com_PackBytes64bitOrdering
  (P2CONST(Com_TxPack, AUTOMATIC, COM_CONST) LpTxPack,
  P2CONST (void, AUTOMATIC, COM_CONST) LpSigDataPtr)
{
  /* @Trace: Com_SUD_API_00826 */
  P2VAR(uint8, AUTOMATIC, COM_VAR) LpWrBuffer;
  P2VAR(uint8, AUTOMATIC, COM_VAR) LpAppSigPtr;
  P2CONST(uint32, AUTOMATIC, COM_CONST) LpSigDataPtr32;
  Com_MIdWord_Access LaaApplSignal[COM_THREE];
  uint8 LucShiftOrData;
  uint8 LucEndMask;
  PduLengthType LucNoOfByte;
  uint8 LucSizeOrData;
  
  LucNoOfByte = (uint8)(LpTxPack->ddSigTypeOrSize);
  /* Get the number of bytes that signal spread across */
  LucSizeOrData = (uint8)(LucNoOfByte & COM_SIG_BYTE_MASK_VALUE);
  LaaApplSignal[COM_ZERO].whole_dword = COM_ZERO;
  LaaApplSignal[COM_ONE].whole_dword = COM_ZERO;
  LaaApplSignal[COM_TWO].whole_dword = COM_ZERO;
  /* Get the local pointer to I-PDU buffer */
  LpWrBuffer =
  (P2VAR(uint8, AUTOMATIC, COM_VAR)) LpTxPack->pWrBuffer;
  #if (CPU_BYTE_ORDER == LOW_BYTE_FIRST)
  /* Get signal actual type */
  uint8 LucType = LpTxPack->ucType;
  /* Modify LpWrBuffer pointer to point to correct MSB position in case
   * network byte order is different from system byte order */
  /* polyspace-begin MISRA2012:18.4 [Justified:Low] "Pointer access accepted for buffer processing. There is no safety impact" */
  if ((LucType == COM_SIG_TYPE_UINT16) ||
    (LucType == COM_SIG_TYPE_SINT16))
  {
    /* @Trace: Com_SUD_API_01913 */
    LpWrBuffer += COM_ONE;
  } else if ((LucType == COM_SIG_TYPE_UINT32) ||
    (LucType == COM_SIG_TYPE_SINT32))
  {
    /* @Trace: Com_SUD_API_01914 */
    LpWrBuffer += COM_THREE;
  } else if ((LucType == COM_SIG_TYPE_UINT64) ||
    (LucType == COM_SIG_TYPE_SINT64))
  {
    /* @Trace: Com_SUD_API_01915 */
    LpWrBuffer += COM_SEVEN;
  } else
  {
    /*Do nothing*/
  }
  /* polyspace-end MISRA2012:18.4 [Justified:Low] "Pointer access accepted for buffer processing. There is no safety impact" */
  #endif
  /* @Trace: Com_SUD_API_01916 */
  LpSigDataPtr32 = (P2CONST(uint32, AUTOMATIC, COM_CONST))
    LpSigDataPtr;
  /* Get the number of shift bits to a local variable */
  LucShiftOrData = LpTxPack->ucNoOfShiftBit;
  /* Copy signal data to double word variable */
  LaaApplSignal[COM_ZERO].whole_dword = *LpSigDataPtr32;
  /* Increment the pointer to point to the next 32 bits */
  LpSigDataPtr32++;
  /* Check that number of shift bit is zero */
  if(LucShiftOrData != 0)
  {
    /* @Trace: Com_SUD_API_00827 */
    /* Shift the double word variable left by the number of shift bits to get
    start position of signal in I-PDU */
    LaaApplSignal[COM_TWO].whole_dword = LaaApplSignal[COM_ZERO].whole_dword;
    LaaApplSignal[COM_ZERO].whole_dword <<= LucShiftOrData;
    /* Shift the double word variable left by the number of shift bits to get
    start position of signal in I-PDU */
    LaaApplSignal[COM_ONE].whole_dword |= 
      (LaaApplSignal[COM_TWO].whole_dword)>>(32 - LucShiftOrData);
    
    /* Get the data in the local buffer */
    LaaApplSignal[COM_TWO].whole_dword = COM_ZERO;

    LaaApplSignal[COM_TWO].whole_dword = ((*LpSigDataPtr32) << LucShiftOrData);

    LaaApplSignal[COM_ONE].whole_dword |= LaaApplSignal[COM_TWO].whole_dword;
    /* Copy the second set of data to a local variable */
  }
  else
  {
    /* @Trace: Com_SUD_API_00828 */
    /* Copy the rest of signal data to double word variable */
    LaaApplSignal[COM_ONE].whole_dword = *LpSigDataPtr32;
  }
  /* @Trace: Com_SUD_API_00829 */
  /* Point to the first byte to be copied */
  LpAppSigPtr =
    (P2VAR(uint8, AUTOMATIC, COM_VAR))
    &LaaApplSignal[COM_ZERO].byte_val.BO_Byte[COM_DWORD_LS_BYTE_IDX];

  /* Get the data from I-PDU buffer pointer to local variable */
  LucShiftOrData = *LpWrBuffer;
  /* Clear signal data from local I-PDU buffer variable by applying start
  mask */
  LucShiftOrData &= LpTxPack->ucWrStartMask;
  /* Write data from application buffer pointer to a local I-PDU buffer
  variable */
  LucShiftOrData |= *LpAppSigPtr;
  /* Copy data into I-PDU buffer from local I-PDU buffer variable */
  *LpWrBuffer = LucShiftOrData;
  #if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)
  /* @Trace: Com_SUD_API_01655 */
  /* Decrement application signal pointer */
  LpAppSigPtr--;
  /* Decrement I-PDU buffer pointer */
  LpWrBuffer++;
  #else
  /* @Trace: Com_SUD_API_01656 */
  /* Increment application signal pointer */
  LpAppSigPtr++;
  /* Increment I-PDU buffer pointer */
  LpWrBuffer--;
  #endif
  /* @Trace: Com_SUD_API_01657 */
  /* Get the number of bytes of data */
  LucShiftOrData = 3;
  /* Loop for number of bytes of data */
  do
  {
    /* @Trace: Com_SUD_API_00830 */
    /* Copy data from application signal pointer to I-PDU buffer */
    *LpWrBuffer = *LpAppSigPtr;
    #if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)
    /* @Trace: Com_SUD_API_01658 */
    /* Decrement application signal pointer */
    LpAppSigPtr--;
    /* Decrement I-PDU buffer pointer */
    LpWrBuffer++;
    #else
    /* @Trace: Com_SUD_API_01659 */
    /* Increment application signal pointer */
    LpAppSigPtr++;
    /* Increment I-PDU buffer pointer */
    LpWrBuffer--;
    #endif
    /* @Trace: Com_SUD_API_01660 */
    /* Decrement the number of bytes of data */
    LucShiftOrData--;
  }while(LucShiftOrData != 0);

  /* @Trace: Com_SUD_API_00831 */
  LucShiftOrData = LucSizeOrData  - 4; 
  LpAppSigPtr =
    (P2VAR(uint8, AUTOMATIC, COM_VAR))
    &LaaApplSignal[COM_ONE].byte_val.BO_Byte[COM_DWORD_LS_BYTE_IDX];

  do
  {
    /* @Trace: Com_SUD_API_00832 */
    /* Copy data from application signal pointer to I-PDU buffer */
    *LpWrBuffer = *LpAppSigPtr;
    #if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)
    /* @Trace: Com_SUD_API_01661 */
    /* Decrement application signal pointer */
    LpAppSigPtr--;
    /* Decrement I-PDU buffer pointer */
    LpWrBuffer++;
    #else
    /* @Trace: Com_SUD_API_01662 */
    /* Increment application signal pointer */
    LpAppSigPtr++;
    /* Increment I-PDU buffer pointer */
    LpWrBuffer--;
    #endif
    /* @Trace: Com_SUD_API_01663 */
    /* Decrement the number of bytes of data */
    LucShiftOrData--;
  }while(LucShiftOrData != COM_ZERO);


  #if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)
  /* @Trace: Com_SUD_API_01664 */
  LpWrBuffer--;
  #else
  /* @Trace: Com_SUD_API_01665 */
  LpWrBuffer++;
  #endif
    /* @Trace: Com_SUD_API_00833 */
  /* Get the end mask value to a local variable */
  LucEndMask = LpTxPack->ucWrEndMask;
  LucEndMask= ~LucEndMask;
  /* Get the data from I-PDU buffer pointer to local I-PDU buffer variable */
  LucShiftOrData = *LpWrBuffer;
  /*Clear signal data from the local I-PDU buffer variable by applying end mask
  to it */
  LucShiftOrData &= LucEndMask;
  /* Copy higher byte data of word variable to local I-PDU buffer */
   /*Store the local I-PDU buffer data into local I-PDU buffer variable */
  *LpWrBuffer = LucShiftOrData;
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/* polyspace-end MISRA2012:D4.14 [Not a defect:Low] "LpTxPack and LpSigDataPtr pointers were checked outside packing functions" */
/* polyspace-end MISRA2012:11.5 [Not a defect:Low] "Following Com_SWS_00197 and Com_SWS_00198, data pointer of Com_Send/ReceiveSignal is void, so the casting to another type is inevitable." */
/* polyspace-end RTE:IDP [Not a defect:Low] "NULL pointer was checked by generator" */
/* polyspace-end RTE:SHF [Not a defect:Low] "Shift amount is inside its bounds. This is assured by generator */
/* polyspace-end CERT-C:EXP36-C [Justified:Low] "Following Com_SWS_00197 and Com_SWS_00198, data pointer of Com_Send/ReceiveSignal is void, so the casting to another type is inevitable." */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
