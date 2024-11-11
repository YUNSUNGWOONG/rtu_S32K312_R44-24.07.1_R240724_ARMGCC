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
**  SRC-MODULE: Com_UnPack.c                                                  **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Com Module                                            **
**                                                                            **
**  PURPOSE   : Provision of unpacking, invalidate and update functions       **
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
** 1.1.11.0  10-Oct-2023   PhucNHM     CP44-2759                              **
** 1.1.10.0  30-May-2023   PhucNHM     CP44-2125                              **
** 1.1.9.0   28-Mar-2023   PhucNHM     CP44-267                               **
** 1.1.3.1   21-Jun-2022   SMKwon      CP44-109                               **
** 1.1.2     25-Apr-2022   PhucNHM     R44-Redmine #25654                     **
** 1.1.1     25-Mar-2022   PhuPV10     R44-Redmine #25573 #25073              **
** 1.1.0     10-Feb-2022   PhucNHM     R44-Redmine #19316 #23495 #23725       **
**                                                 #23982 #24211              **
** 1.0.1     28-Sep-2021   DuyNGB      R44-Redmine #20139                     **
** 1.0.0     04-Dec-2020   SMKwon      Initial Version                        **
*******************************************************************************/
/* polyspace-begin MISRA2012:D4.14 [Not a defect:Low] "LpRxUnpack and LpSigDataPtr pointers were checked outside unpacking functions" */
/* polyspace-begin MISRA2012:11.5 [Not a defect:Low] "Following Com_SWS_00197 and Com_SWS_00198, data pointer of Com_Send/ReceiveSignal is void, so the casting to another type is inevitable." */
/* polyspace-begin RTE:IDP [Not a defect:Low] "NULL pointer was checked by generator" */
/* polyspace-begin RTE:SHF [Not a defect:Low] "Shift amount is inside its bounds. This is assured by generator */
/* polyspace-begin CERT-C:EXP36-C [Justified:Low] "Following Com_SWS_00197 and Com_SWS_00198, data pointer of Com_Send/ReceiveSignal is void, so the casting to another type is inevitable." */
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

#include "Com.h"          /* Com header file */
#include "Com_UnPack.h"   /* Com Unpack header file */
#include "SchM_Com.h"     /* SchM Com header file */

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*******************************************************************************
**                      Function Declaration                                  **
*******************************************************************************/

#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE) Com_Up64Bts_ProcSrcData(
  P2VAR(uint8, AUTOMATIC, COM_VAR) LpApplBuffer, 
  P2CONST(uint8, AUTOMATIC, COM_CONST) LpRdBuffer, 
  PduLengthType LucSigTypeOrSize);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE) Com_Up64Bts_LocateSignByte(
  P2VAR(Com_MIdWord_Access, AUTOMATIC, COM_VAR) LocalPtrApplBuffer,
  PduLengthType LucSigTypeOrSize);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE) Com_Up64Bts_ProcDstBuffer(
  uint8 LucStartInd, uint8 LucStopInd,
  P2VAR(uint8, AUTOMATIC, COM_VAR) LpSigBuffer, 
  P2VAR(uint8, AUTOMATIC, COM_VAR) LpBuffer);
#define COM_STOP_SEC_CODE
#include "MemMap.h"
  
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE) Com_Up64BtsOrd_ProcSrcData(
  P2VAR(uint8, AUTOMATIC, COM_VAR) LpApplBuffer, 
  P2CONST(uint8, AUTOMATIC, COM_CONST) LpRdBuffer, 
  PduLengthType LucSigTypeOrSize);
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

/*******************************************************************************
** Function Name        : Com_UnPackOneByte                                   **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function unpacks one byte signal from an I-PDU **
**                        buffer.                                             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same signal.                  **
**                        Reentrant for different signals.                    **
**                                                                            **
** Input Parameters     : LpRxUnpack                                          **
**                                                                            **
** Output Parameters    : LpSigDataPtr                                        **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : None                       **
*******************************************************************************/

#define COM_START_SEC_CODE
#include "MemMap.h"

FUNC(void, COM_CODE) Com_UnPackOneByte
(P2CONST(Com_RxUnpack, AUTOMATIC, COM_CONST) LpRxUnpack,
                           P2VAR(void, AUTOMATIC, COM_VAR) LpSigDataPtr)
{
  /* @Trace: Com_SUD_API_01143 */
  /* @Trace: SWS_Com_00675, SWS_Com_00007, SWS_Com_00008 */
  uint8 LucIpduData;
  uint8 LucSignMask;
  /* Get the sign mask value */
  LucSignMask = LpRxUnpack->ucRdSignMask;
  /* Enter protection area */
  /* Reduce the invoking count of Protection Area - by AUTRON START */
  /*SchM_Enter_Com_RX_EXT_SIG_DATA_PROTECTION_AREA();*/
  /* Get the I-PDU buffer data to a local I-PDU variable */
  /* polyspace +1 RTE:NIV [Not a defect:Low] "Variable initialized by calling function" */
  LucIpduData = *(LpRxUnpack->pRdBuffer);
  /* Exit protection area */
  /*SchM_Exit_Com_RX_EXT_SIG_DATA_PROTECTION_AREA();*/
  /* Reduce the invoking count of Protection Area - by AUTRON END */
  /* Shift the local I-PDU variable by the number of shift bits to the get
  the start position */
  LucIpduData >>= (LpRxUnpack->ucNoOfShiftBits);
  /* Apply the end mask to local I-PDU variable to clear unoccupied area of
  signal */
  LucIpduData &= (LpRxUnpack->ucRdEndMask);
  /* Check whether the received signal is negative  */
  if((LucIpduData & LucSignMask) != COM_ZERO)
  {
    /* @Trace: Com_SUD_API_01144 */
    /* Perform sign conversion */
    LucIpduData |= LucSignMask;
  }
  /* @Trace: Com_SUD_API_01145 */
  /* Copy local I-PDU variable data to signal data pointer */
  *(P2VAR(uint8, AUTOMATIC, COM_VAR)) LpSigDataPtr = LucIpduData;
}

#define COM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Com_UnPackBytes                                     **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function unpacks the signal of size more than  **
**                        8 bits and spread across four bytes in an I-PDU     **
**                        buffer.                                             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same signal.                  **
**                        Reentrant for different signals.                    **
**                                                                            **
** Input Parameters     : LpRxUnpack                                          **
**                                                                            **
** Output Parameters    : LpSigDataPtr                                        **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : SchM_Exit_Com()            **
**                                                 SchM_Enter_Com()           **
*******************************************************************************/

#define COM_START_SEC_CODE
#include "MemMap.h"

FUNC(void, COM_CODE) Com_UnPackBytes
(P2CONST(Com_RxUnpack, AUTOMATIC, COM_CONST) LpRxUnpack,
                           P2VAR(void, AUTOMATIC, COM_VAR) LpSigDataPtr)
{
  /* @Trace: Com_SUD_API_01146 */
  /* @Trace: SWS_Com_00675, SWS_Com_00007, SWS_Com_00008 */
  P2CONST(uint8, AUTOMATIC, COM_CONST) LpRdBuffer;
  P2VAR(uint8, AUTOMATIC, COM_VAR) LpApplBuffer;
  P2VAR(uint8, AUTOMATIC, COM_VAR) LpSignBuffer;
  Com_MIdWord_Access LunApplSignal;
  uint8 LucSigTypeOrSize;
  uint8 LucSignMask;
  uint8 LucIpduBuffer;
  /* Initialize double word variable to zero */
  LunApplSignal.whole_dword = COM_ZERO;
  /* Get the signal size */
  LucSigTypeOrSize  = (uint8)(LpRxUnpack->ddSignalSize);
  /* Get the pointer to lower byte of double word variable and assign it to
  local application buffer pointer */
  LpApplBuffer = (P2VAR(uint8, AUTOMATIC, COM_VAR))
    &LunApplSignal.byte_val.BO_Byte[COM_DWORD_LS_BYTE_IDX];
  LpSignBuffer = LpApplBuffer;
  /* Get the pointer to I-PDU buffer */
  LpRdBuffer = (P2CONST(uint8, AUTOMATIC, COM_CONST))
    (LpRxUnpack->pRdBuffer);
  /* Enter protection area */
  SchM_Enter_Com_RX_EXT_SIG_DATA_PROTECTION_AREA();
  /* Loop for signal size */
  do
  {
    /* @Trace: Com_SUD_API_01147 */
    /* Copy the data from the I-PDU buffer to application buffer */
    /* polyspace +1 RTE:NIV [Not a defect:Low] "Variable initialized with configuration data" */
    *LpApplBuffer = *LpRdBuffer;
    #if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)
    /* @Trace: Com_SUD_API_01707 */
    /* Decrement application buffer pointer */
    LpApplBuffer--;
    /* Decrement I-PDU buffer pointer */
    LpRdBuffer--;
    #else
    /* @Trace: Com_SUD_API_01708 */
    /* Increment application buffer pointer */
    LpApplBuffer++;
    /* Increment I-PDU buffer pointer */
    LpRdBuffer++;
    #endif
    /* @Trace: Com_SUD_API_01709 */
    /* Decrement signal size */
    LucSigTypeOrSize--;
  }while(LucSigTypeOrSize != COM_ONE);
  /* Get the I-PDU buffer pointer data to a local Application Buffer variable */
  /* @Trace: Com_SUD_API_01148 */
  /* polyspace +1 RTE:NIV [Not a defect:Low] "Variable initialized with configuration data" */
  *LpApplBuffer = *LpRdBuffer;
  /* Exit protection area */
  SchM_Exit_Com_RX_EXT_SIG_DATA_PROTECTION_AREA();
  /* Get the type/size of the signal */
  LucSigTypeOrSize = (LpRxUnpack->ucSignalType);
  /* Shift the double word variable right by the number of shift bits to get the
  start position */
  LunApplSignal.whole_dword  >>= LpRxUnpack->ucNoOfShiftBits;
  /* polyspace-begin MISRA2012:18.4 [Justified:Low] "Pointer access accepted as index is signed number" */
  #if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)
  /* @Trace: Com_SUD_API_01710 */
  LpSignBuffer -= (Com_PtrType)LucSigTypeOrSize;
  #else
  /* @Trace: Com_SUD_API_01711 */
  LpSignBuffer = &LpSignBuffer[(Com_PtrType)LucSigTypeOrSize];
  #endif
  /* @Trace: Com_SUD_API_01712 */
  /* polyspace-end MISRA2012:18.4 [Justified:Low] "Pointer access accepted as index is signed number" */
  LucIpduBuffer = *LpSignBuffer;
  /* Get the sign mask value */
  LucSignMask = LpRxUnpack->ucRdSignMask;
  /* Apply end mask */
  LucIpduBuffer &= LpRxUnpack->ucRdEndMask;
  /* Check whether the signal is negative */
  if((LucIpduBuffer & LucSignMask) != COM_ZERO)
  {
    /* @Trace: Com_SUD_API_01149 */
    /* Perform sign conversion */
    LucIpduBuffer |= LucSignMask;
    /* Check whether the signal size is 24 bits */
    if(COM_TYPE_24 == LucSigTypeOrSize)
    {
      /* @Trace: Com_SUD_API_01150 */
      /* Get sign extension to higher byte of double word variable */
      LunApplSignal.byte_val.BO_Byte[COM_DWORD_MS_BYTE_IDX] =COM_SIGN_EXTENSION;
    }
  }
  else
  {
    /* Check whether the signal size is 24 bits */
    if(COM_TYPE_24 == LucSigTypeOrSize)
    {
      /* @Trace: Com_SUD_API_01151 */
      /* Get sign extension to higher byte of double word variable */
      LunApplSignal.byte_val.BO_Byte[COM_DWORD_MS_BYTE_IDX] = COM_ZERO;
    }
  }

  /* @Trace: Com_SUD_API_01152 */
  /* Copy the local I-PDU buffer data to application buffer */
  *LpSignBuffer = LucIpduBuffer;
  /* Check whether the signal size is one byte */
  if(COM_TYPE_8 == LucSigTypeOrSize)
  {
    /* @Trace: Com_SUD_API_01153 */
    /* Copy the lower byte of double word variable to signal data pointer */
    *(P2VAR(uint8, AUTOMATIC, COM_VAR)) LpSigDataPtr =
      LunApplSignal.byte_val.BO_Byte[COM_DWORD_LS_BYTE_IDX];
  }
  /* Check whether the signal size is two bytes */
  else if (COM_TYPE_16 == LucSigTypeOrSize)
  {
    /* @Trace: Com_SUD_API_01154 */
    /* Copy the lower word of double word variable to signal data pointer */
    *(P2VAR(uint16, AUTOMATIC, COM_VAR)) LpSigDataPtr =
      LunApplSignal.word_val.BO_Word[COM_DWORD_LS_WORD_IDX];
  }
  else
  {
    /* @Trace: Com_SUD_API_01155 */
    /* Copy the double word variable data to signal data pointer */
    *(P2VAR(uint32, AUTOMATIC, COM_VAR)) LpSigDataPtr =
      LunApplSignal.whole_dword;
  }
}

#define COM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Com_UnPackFiveBytes                                 **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function unpacks the signal of size more than  **
**                        32 bits and spread across five bytes in an I-PDU    **
**                        buffer.                                             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same signal.                  **
**                        Reentrant for different signals.                    **
**                                                                            **
** Input Parameters     : LpRxUnpack                                          **
**                                                                            **
** Output Parameters    : LpSigDataPtr                                        **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : SchM_Exit_Com()            **
**                                                 SchM_Enter_Com()           **
*******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE) Com_UnPackFiveBytes
(P2CONST(Com_RxUnpack, AUTOMATIC, COM_CONST) LpRxUnpack,
                           P2VAR(void, AUTOMATIC, COM_VAR) LpSigDataPtr)
{
  /* @Trace: Com_SUD_API_01156 */
  /* @Trace: SWS_Com_00675, SWS_Com_00007, SWS_Com_00008*/
  P2CONST(uint8, AUTOMATIC, COM_CONST) LpRdBuffer;
  P2VAR(uint8, AUTOMATIC, COM_VAR) LpApplBuffer;
  Com_MIdWord_Access LunApplSignal;
  Com_MIWord_Access LunApplSigHi;
  uint8 LucSigTypeOrSize;
  uint8 LucSignMask;
  /* Initialize the double word variable to zero */
  LunApplSignal.whole_dword = COM_ZERO;
  /* Initialize the lower byte of word variable to zero */
  LunApplSigHi.byte_val.BO_Byte[COM_WORD_LS_BYTE_IDX] = COM_ZERO;
  /* Get the pointer to lower byte of double word variable and assign it to
  application buffer pointer */
  LpApplBuffer = (P2VAR(uint8, AUTOMATIC, COM_VAR))
    &LunApplSignal.byte_val.BO_Byte[COM_DWORD_LS_BYTE_IDX];
  /* Get the pointer I-PDU buffer */
  /* polyspace +1 MISRA2012:D4.14 [Not a defect:Low] "NULL pointer was checked before accessing" */
  LpRdBuffer = (LpRxUnpack->pRdBuffer);
  /* Get the signal size that spread across number of bytes */
  LucSigTypeOrSize = COM_FOUR;
  /* Enter protection area */
  SchM_Enter_Com_RX_EXT_SIG_DATA_PROTECTION_AREA();
  /* Loop for signal size */
  do
  {
    /* @Trace: Com_SUD_API_01157 */
    /* Copy the data from the I-PDU buffer to application buffer */
    *LpApplBuffer = *LpRdBuffer;
    #if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)
    /* @Trace: Com_SUD_API_01713 */
    /* Decrement application buffer pointer */
    LpApplBuffer--;
    /* Decrement I-PDU buffer pointer */
    LpRdBuffer--;
    #else
    /* @Trace: Com_SUD_API_01714 */
    /* Increment application buffer pointer */
    LpApplBuffer++;
    /* Increment I-PDU buffer pointer */
    LpRdBuffer++;
    #endif
    /* @Trace: Com_SUD_API_01715 */
    /* Decrement signal size */
    LucSigTypeOrSize--;
  }while(LucSigTypeOrSize != COM_ZERO);
  /* @Trace: Com_SUD_API_01158 */
  /* Get the I-PDU buffer pointer data to the higher byte of word variable */
  LunApplSigHi.byte_val.BO_Byte[COM_WORD_MS_BYTE_IDX] = *LpRdBuffer;
  /* Exit protection area */
  SchM_Exit_Com_RX_EXT_SIG_DATA_PROTECTION_AREA();
  /* Get the number of shift bits */
  LucSignMask = LpRxUnpack->ucNoOfShiftBits & (0x1Fu);
  /* Shift the double word variable to right by the number of shift bits */
  LunApplSignal.whole_dword  >>= LucSignMask;
  /* Shift the word variable to right by the number of shift bits */
  LunApplSigHi.whole_word  >>= LucSignMask;
  /* Get the lower byte of word variable to local signal variable  */
  LucSigTypeOrSize = LunApplSigHi.byte_val.BO_Byte[COM_WORD_LS_BYTE_IDX];
  /* Apply end mask to clear unoccupied area of local signal variable */
  LucSigTypeOrSize &= LpRxUnpack->ucRdEndMask;
  /* Get the sign mask value */
  LucSignMask = LpRxUnpack->ucRdSignMask;
  /* Check whether the received signal value is negative */
  if((LucSigTypeOrSize & LucSignMask) != COM_ZERO)
  {
    /* @Trace: Com_SUD_API_01159 */
    /* Perform sign conversion */
    LucSigTypeOrSize  |= LucSignMask;
  }
  /* @Trace: Com_SUD_API_01160 */
  /* Copy the local signal variable data to higher byte of double word
  variable */
  LunApplSignal.byte_val.BO_Byte[COM_DWORD_MS_BYTE_IDX] |= LucSigTypeOrSize;
  /* Copy the double word variable data to signal data pointer */
  *(P2VAR(uint32, AUTOMATIC, COM_VAR)) LpSigDataPtr =
                                                      LunApplSignal.whole_dword;
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Com_UnPackByteOrdering                              **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function unpacks the signal of size more than  **
**                        8 bits, spread across four bytes in an I-PDU        **
**                        buffer and does the endianness conversion.          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same signal.                  **
**                        Reentrant for different signals.                    **
**                                                                            **
** Input Parameters     : LpRxUnpack                                          **
**                                                                            **
** Output Parameters    : LpSigDataPtr                                        **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : SchM_Exit_Com()            **
**                                                 SchM_Enter_Com()           **
*******************************************************************************/

#define COM_START_SEC_CODE
#include "MemMap.h"

FUNC(void, COM_CODE) Com_UnPackByteOrdering
(P2CONST(Com_RxUnpack, AUTOMATIC, COM_CONST) LpRxUnpack,
                           P2VAR(void, AUTOMATIC, COM_VAR) LpSigDataPtr)
{
  /* @Trace: Com_SUD_API_01161 */
  /* @Trace: SWS_Com_00675, SWS_Com_00007, SWS_Com_00008 */
  P2CONST(uint8, AUTOMATIC, COM_CONST) LpRdBuffer;
  P2VAR(uint8, AUTOMATIC, COM_VAR) LpApplBuffer;
  P2VAR(uint8, AUTOMATIC, COM_VAR) LpSignBuffer;
  Com_MIdWord_Access LunApplSignal;
  PduLengthType LucSigTypeOrSize;
  uint8 LucSignMask;
  uint8 LucIpduBuffer;
  /* Initialize double word variable to zero */
  LunApplSignal.whole_dword = COM_ZERO;
  /* Get the signal size */
  LucSigTypeOrSize  = (LpRxUnpack->ddSignalSize);
  
  if ((LucSigTypeOrSize >= 0x01u) && (LucSigTypeOrSize <= 0x04u))
  {
    /* @Trace: Com_SUD_API_01900 */
    /* Get the pointer to lower byte of double word variable and assign it to
    local application buffer pointer */
    LpApplBuffer = (P2VAR(uint8, AUTOMATIC, COM_VAR))
      &LunApplSignal.byte_val.BO_Byte[COM_DWORD_LS_BYTE_IDX];
    LpSignBuffer = LpApplBuffer;
    /* Get the pointer to I-PDU buffer */
    LpRdBuffer = (P2CONST(uint8, AUTOMATIC, COM_CONST))
      (LpRxUnpack->pRdBuffer);
    /* Enter protection area */
    SchM_Enter_Com_RX_EXT_SIG_DATA_PROTECTION_AREA();
    /* Loop for signal size */
    while(LucSigTypeOrSize != COM_ONE)
    {
      /* @Trace: Com_SUD_API_01162 */
      /* Copy the data from I-PDU buffer to application buffer */
      /* polyspace +1 RTE:NIV [Not a defect:Low] "Variable initialized with configuration data" */
      *LpApplBuffer = *LpRdBuffer;
      #if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)
      /* @Trace: Com_SUD_API_01716 */
      /* Decrement application buffer pointer */
      LpApplBuffer--;
      /* Increment I-PDU buffer pointer */
      LpRdBuffer++;
      #else
      /* @Trace: Com_SUD_API_01717 */
      /* Increment application buffer pointer */
      LpApplBuffer++;
      /* Decrement I-PDU buffer pointer */
      LpRdBuffer--;
      #endif
      /* @Trace: Com_SUD_API_01718 */
      /* Decrement signal size */
      LucSigTypeOrSize--;
    }
    /* @Trace: Com_SUD_API_01163 */
    /* Get the I-PDU buffer pointer data to a local I-PDU variable */
    /* polyspace +2 RTE:NIV [Not a defect:Low] "Variable initialized with configuration data" */
    /* polyspace +1 RTE:NIP [Not a defect:Low] "Pointer initialized with configuration data" */
    *LpApplBuffer = *LpRdBuffer;
    /* Exit protection area */
    SchM_Exit_Com_RX_EXT_SIG_DATA_PROTECTION_AREA();
    /* Get the type/size of the signal */
    LucSigTypeOrSize = (LpRxUnpack->ucSignalType);
    /* Shift the double word variable right by the number of shift bits to get
    the start position */
    LunApplSignal.whole_dword  >>= ((LpRxUnpack->ucNoOfShiftBits) & 0x1Fu);
    /* polyspace-begin MISRA2012:18.4 [Justified:Low] "Pointer access accepted as index is signed number" */
    #if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)
    /* @Trace: Com_SUD_API_01719 */
    LpSignBuffer -= (Com_PtrType)LucSigTypeOrSize;
    #else
    /* @Trace: Com_SUD_API_01720 */
    LpSignBuffer = &LpSignBuffer[(Com_PtrType)LucSigTypeOrSize];
    #endif
    /* @Trace: Com_SUD_API_01721 */
    /* polyspace-end MISRA2012:18.4 [Justified:Low] "Pointer access accepted as index is signed number" */
    LucIpduBuffer =*LpSignBuffer;
    /* Get the sign mask value */
    LucSignMask = LpRxUnpack->ucRdSignMask;
    /* Apply the end mask value to local I-PDU variable to clear unoccupied area
    of signal */
    LucIpduBuffer &= LpRxUnpack->ucRdEndMask;
    /* Check whether the signal is negative */
    if((LucIpduBuffer & LucSignMask) != COM_ZERO)
    {
      /* @Trace: Com_SUD_API_01164 */
      /* Perform sign conversion */
      LucIpduBuffer |= LucSignMask;
      /* Check whether the signal size is 24 bits */
      if(COM_TYPE_24 == LucSigTypeOrSize)
      {
        /* @Trace: Com_SUD_API_01165 */
        /* Get sign extension to higher byte of double word variable */
        LunApplSignal.byte_val.BO_Byte[COM_DWORD_MS_BYTE_IDX] =COM_SIGN_EXTENSION;
      }
    }
    else
    {
      /* Check whether the signal size is 24 bits */
      if(COM_TYPE_24 == LucSigTypeOrSize)
      {
        /* @Trace: Com_SUD_API_01166 */
        /* Get sign extension to higher byte of double word variable */
        LunApplSignal.byte_val.BO_Byte[COM_DWORD_MS_BYTE_IDX] = COM_ZERO;
      }
    }
    /* @Trace: Com_SUD_API_01167 */
    /* Copy the local I-PDU buffer data to application Buffer */
    *LpSignBuffer = LucIpduBuffer;
  }
  /* Check whether the signal size is one byte */
  if(COM_TYPE_8 == LucSigTypeOrSize)
  {
    /* @Trace: Com_SUD_API_01168 */
    /* Copy the lower byte of double word variable to signal data pointer */
    *(P2VAR(uint8, AUTOMATIC, COM_VAR)) LpSigDataPtr =
      LunApplSignal.byte_val.BO_Byte[COM_DWORD_LS_BYTE_IDX];
  }
  /* Check whether the signal size is two bytes */
  else if (COM_TYPE_16 == LucSigTypeOrSize)
  {
    /* @Trace: Com_SUD_API_01169 */
    /* Copy the lower word of double word variable to signal data pointer */
    *(P2VAR(uint16, AUTOMATIC, COM_VAR)) LpSigDataPtr =
      LunApplSignal.word_val.BO_Word[COM_DWORD_LS_WORD_IDX];
  }
  else
  {
    /* @Trace: Com_SUD_API_01170 */
    /* Copy the double word variable data to signal data pointer */
    *(P2VAR(uint32, AUTOMATIC, COM_VAR)) LpSigDataPtr =
      LunApplSignal.whole_dword;
  }
}

#define COM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Com_UnPackFiveByteOrdering                          **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function unpacks the signal of size more than  **
**                        32 bits, spread across five bytes in an I-PDU       **
**                        buffer and does the endianness conversion.          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same signal.                  **
**                        Reentrant for different signals.                    **
**                                                                            **
** Input Parameters     : LpRxUnpack                                          **
**                                                                            **
** Output Parameters    : LpSigDataPtr                                        **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : SchM_Exit_Com()            **
**                                                 SchM_Enter_Com()           **
*******************************************************************************/

#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE) Com_UnPackFiveByteOrdering
(P2CONST(Com_RxUnpack, AUTOMATIC, COM_CONST) LpRxUnpack,
                           P2VAR(void, AUTOMATIC, COM_VAR) LpSigDataPtr)
{
  /* @Trace: Com_SUD_API_01171 */
  /* @Trace: SWS_Com_00675, SWS_Com_00007, SWS_Com_00810 */
  P2CONST(uint8, AUTOMATIC, COM_CONST) LpRdBuffer;
  P2VAR(uint8, AUTOMATIC, COM_VAR) LpApplBuffer;
  Com_MIdWord_Access LunApplSignal;
  Com_MIWord_Access LunApplSigHi;
  uint8 LucSigTypeOrSize;
  uint8 LucSignMask;
  /* Initialize the double word variable to zero */
  LunApplSignal.whole_dword = COM_ZERO;
  /* Initialize the lower byte of word variable to zero */
  LunApplSigHi.byte_val.BO_Byte[COM_WORD_LS_BYTE_IDX] = COM_ZERO;
  /* Get the local pointer to lower byte of double word variable and assign it
  to application buffer pointer */
  LpApplBuffer = (P2VAR(uint8, AUTOMATIC, COM_VAR))
    &LunApplSignal.byte_val.BO_Byte[COM_DWORD_LS_BYTE_IDX];
  /* Get the local pointer to the I-PDU buffer */
  LpRdBuffer = (LpRxUnpack->pRdBuffer);
  /* Get the signal size that spread across number of bytes */
  LucSigTypeOrSize = COM_FOUR;
  /* Enter protection area */
  SchM_Enter_Com_RX_EXT_SIG_DATA_PROTECTION_AREA();
  /* Loop for signal size */
  do
  {
    /* @Trace: Com_SUD_API_01172 */
    /* Copy the data from I-PDU buffer pointer to application buffer pointer */
    *LpApplBuffer = *LpRdBuffer;
    #if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)
    /* @Trace: Com_SUD_API_01722 */
    /* Decrement application buffer pointer */
    LpApplBuffer--;
    /* Increment I-PDU buffer pointer */
    LpRdBuffer++;
    #else
    /* @Trace: Com_SUD_API_01723 */
    /* Increment application buffer pointer */
    LpApplBuffer++;
    /* Decrement I-PDU buffer pointer */
    LpRdBuffer--;
    #endif
    /* @Trace: Com_SUD_API_01724 */
    /* Decrement signal size */
    LucSigTypeOrSize--;
  }while(LucSigTypeOrSize != COM_ZERO);
  /* @Trace: Com_SUD_API_01173 */
  /* Get the I-PDU buffer pointer data to the higher byte of word variable */
  LunApplSigHi.byte_val.BO_Byte[COM_WORD_MS_BYTE_IDX] = *LpRdBuffer;
  /* Exit protection area */
  SchM_Exit_Com_RX_EXT_SIG_DATA_PROTECTION_AREA();
  /* Get the number of shift bits */
  LucSignMask = LpRxUnpack->ucNoOfShiftBits & (0x1Fu);
  /* Shift the double word variable to right by the number of shift bits */
  LunApplSignal.whole_dword  >>= LucSignMask;
  /* Shift the word variable to right by the number of shift bits */
  LunApplSigHi.whole_word  >>= LucSignMask;
  /* Get the lower byte of word variable to local signal variable */
  LucSigTypeOrSize = LunApplSigHi.byte_val.BO_Byte[COM_WORD_LS_BYTE_IDX];
  /* Apply end mask to clear unoccupied area of local signal variable */
  LucSigTypeOrSize &= LpRxUnpack->ucRdEndMask;
  /* Get the sign mask value */
  LucSignMask = LpRxUnpack->ucRdSignMask;
  /* Check whether the received signal is negative */
  if((LucSigTypeOrSize & LucSignMask) != COM_ZERO)
  {
    /* @Trace: Com_SUD_API_01174 */
    /* Perform sign conversion */
    LucSigTypeOrSize  |= LucSignMask;
  }
  /* @Trace: Com_SUD_API_01175 */
  /* Copy the local signal variable data to higher byte of double word
  variable */
  LunApplSignal.byte_val.BO_Byte[COM_DWORD_MS_BYTE_IDX] |= LucSigTypeOrSize;
  /* Copy double word variable data to the signal data pointer */
  *(P2VAR(uint32, AUTOMATIC, COM_VAR)) LpSigDataPtr =
    LunApplSignal.whole_dword;
}

#define COM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Com_UnPackNBytes                                    **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function unpacks the signal of type uint8[n],  **
**                        where n > 1.                                        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same signal.                  **
**                        Reentrant for different signals.                    **
**                                                                            **
** Input Parameters     : LpRxUnpack, LpSigDataPtr                            **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : Com_GaaRxDynSigLength      **
**                        Function(s) invoked    : SchM_Exit_Com()            **
**                                                 SchM_Enter_Com()           **
*******************************************************************************/

#define COM_START_SEC_CODE
#include "MemMap.h"

FUNC(void, COM_CODE) Com_UnPackNBytes
(P2CONST(Com_RxUnpack, AUTOMATIC, COM_CONST) LpRxUnpack,
  P2VAR(void, AUTOMATIC, COM_VAR) LpSigDataPtr)
{
  /* @Trace: Com_SUD_API_01176 */
  /* @Trace: SWS_Com_00675, SWS_Com_00007, SWS_Com_00810 */
  P2CONST(uint8, AUTOMATIC, COM_CONST) LpSignalBuffer;
  P2VAR(uint8, AUTOMATIC, COM_VAR) LpApplBuffer;
  PduLengthType LddSignalSize;
  /* Get the pointer to application buffer */
  LpApplBuffer = (P2VAR(uint8, AUTOMATIC, COM_VAR)) LpSigDataPtr;
  /* Get the pointer to I-PDU/signal buffer */
  LpSignalBuffer = (P2VAR(uint8, AUTOMATIC, COM_VAR))
    LpRxUnpack->pRdBuffer;
    #if(COM_RX_DYN_SUPPORT == STD_ON)
  /* #2142 : separate DYN PDU from TP */
  if((LpRxUnpack->ddRxIpduDynLegthRef) != COM_INVALID_RXID_PARAM)
  {
    /* @Trace: Com_SUD_API_01177 */
    /* Get the size of the signal or signal group */
    /* polyspace +1 RTE:OBAI [Not a defect:Low] "Array access index is in-bounds. This is assured by generator" */
    LddSignalSize = Com_GaaRxDynSigLength[LpRxUnpack->ddRxIpduDynLegthRef];
  }
  else
    #endif
  {
    /* @Trace: Com_SUD_API_01178 */
    /* Get the size of the signal or signal group */
    LddSignalSize = LpRxUnpack->ddSignalSize;
  }
  /* @Trace: Com_SUD_API_01179 */
  /* Enter protection area */
  SchM_Enter_Com_RX_EXT_SIG_DATA_PROTECTION_AREA();
  /* Loop for signal size */
  while(LddSignalSize != (PduLengthType)COM_ZERO)
  {
    /* @Trace: Com_SUD_API_01180 */
    /* Copy the data from signal buffer to application buffer */
    /* polyspace +1 RTE:NIV [Not a defect:Low] "Variable initialized with configuration data" */
    *LpApplBuffer = *LpSignalBuffer;
    /* Increment the application buffer pointer */
    LpApplBuffer++;
    /* Increment the signal buffer pointer */
    LpSignalBuffer++;
    /* Decrement the signal size count */
    LddSignalSize--;
  }
  /* @Trace: Com_SUD_API_01181 */
  /* Exit protection area */
  SchM_Exit_Com_RX_EXT_SIG_DATA_PROTECTION_AREA();
}

#define COM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Com_UnPackNineBytes                                 **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function unpacks the signal of size more than  **
**                        64 bits and spread across five bytes in an I-PDU    **
**                        buffer.                                             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same signal.                  **
**                        Reentrant for different signals.                    **
**                                                                            **
** Input Parameters     : LpRxUnpack, LpSigDataPtr                            **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : SchM_Exit_Com()            **
**                                                 SchM_Enter_Com()           **
*******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE) Com_UnPackNineBytes
(P2CONST(Com_RxUnpack, AUTOMATIC, COM_CONST) LpRxUnpack,
                           P2VAR(void, AUTOMATIC, COM_VAR) LpSigDataPtr)
{
  /* @Trace: Com_SUD_API_01182 */
  /* @Trace: SWS_Com_00675, SWS_Com_00007, SWS_Com_00810 */
  P2CONST(uint8, AUTOMATIC, COM_CONST) LpRdBuffer;
  P2VAR(uint8, AUTOMATIC, COM_VAR) LpLocalBuffer;
  P2VAR(uint8, AUTOMATIC, COM_VAR) LpLocalSigBuffer;
  P2VAR(uint8, AUTOMATIC, COM_VAR) LpApplBuffer;
  Com_MIdWord_Access LaaApplSignal[COM_TWO];
  Com_MIWord_Access LunApplSigHi;
  uint8 LucSigTypeOrSize;
  uint8 LucSignMask;
  uint8 LucCount;
  /* Initialize the double word variables to zero */
  LaaApplSignal[COM_ZERO].whole_dword = COM_ZERO;
  LaaApplSignal[COM_ONE].whole_dword = COM_ZERO;
  /* Initialize the lower byte of word variable to zero */
  LunApplSigHi.byte_val.BO_Byte[COM_WORD_LS_BYTE_IDX] = COM_ZERO;
  /* Get the pointer to lower byte of double word variable and assign it to
  application buffer pointer */
  LpApplBuffer = (P2VAR(uint8, AUTOMATIC, COM_VAR))
    &LaaApplSignal[COM_ZERO].byte_val.BO_Byte[COM_DWORD_LS_BYTE_IDX];
  /* Get the pointer I-PDU buffer */
  LpRdBuffer = (LpRxUnpack->pRdBuffer);
  /* Get the signal size that spread across number of bytes */
  LucSigTypeOrSize = COM_EIGHT;
  /* Enter protection area */
  SchM_Enter_Com_RX_EXT_SIG_DATA_PROTECTION_AREA();
  /* Loop for signal size */
  do
  {
    /* @Trace: Com_SUD_API_01183 */
    /* Copy the data from the I-PDU buffer to application buffer */
    *LpApplBuffer = *LpRdBuffer;
    #if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)
    /* @Trace: Com_SUD_API_01725 */
    /* Decrement application buffer pointer */
    LpApplBuffer--;
    /* Decrement I-PDU buffer pointer */
    LpRdBuffer--;
    #else
    /* @Trace: Com_SUD_API_01726 */
    /* Increment application buffer pointer */
    LpApplBuffer++;
    /* Increment I-PDU buffer pointer */
    LpRdBuffer++;
    #endif
    /* @Trace: Com_SUD_API_01727 */
    /* Decrement signal size */
    LucSigTypeOrSize--;
  }while(LucSigTypeOrSize != COM_FOUR);

  /* @Trace: Com_SUD_API_01184 */
  LpApplBuffer = (P2VAR(uint8, AUTOMATIC, COM_VAR))
    &LaaApplSignal[COM_ONE].byte_val.BO_Byte[COM_DWORD_LS_BYTE_IDX];

  do
  {
    /* @Trace: Com_SUD_API_01185 */
    /* Copy the data from the I-PDU buffer to application buffer */
    *LpApplBuffer = *LpRdBuffer;
    #if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)
    /* @Trace: Com_SUD_API_01728 */
    /* Decrement application buffer pointer */
    LpApplBuffer--;
    /* Decrement I-PDU buffer pointer */
    LpRdBuffer--;
    #else
    /* @Trace: Com_SUD_API_01729 */
    /* Increment application buffer pointer */
    LpApplBuffer++;
    /* Increment I-PDU buffer pointer */
    LpRdBuffer++;
    #endif
    /* @Trace: Com_SUD_API_01793 */
    /* Decrement signal size */
    LucSigTypeOrSize--;
  }while(LucSigTypeOrSize != COM_ZERO);

  /* @Trace: Com_SUD_API_01186 */
  /* Get the I-PDU buffer pointer data to the higher byte of word variable */
  LunApplSigHi.byte_val.BO_Byte[COM_WORD_MS_BYTE_IDX] = *LpRdBuffer;
  /* Exit protection area */
  SchM_Exit_Com_RX_EXT_SIG_DATA_PROTECTION_AREA();
  /* Get the number of shift bits */
  LucSignMask = LpRxUnpack->ucNoOfShiftBits & (0x1Fu);
  /* Shift the double word variable to right by the number of shift bits */
  LaaApplSignal[COM_ZERO].whole_dword  >>= LucSignMask;
  LaaApplSignal[COM_ZERO].whole_dword |=
    (LaaApplSignal[COM_ONE].whole_dword << 
      ((COM_THIRTY_TWO - LucSignMask) & 0x1Fu));
  LaaApplSignal[COM_ONE].whole_dword >>= LucSignMask;
  /* Shift the word variable to right by the number of shift bits */
  LunApplSigHi.whole_word  >>= LucSignMask;
  /* Get the lower byte of word variable to local signal variable  */
  LucSigTypeOrSize = LunApplSigHi.byte_val.BO_Byte[COM_WORD_LS_BYTE_IDX];
  /* Apply end mask to clear unoccupied area of local signal variable */
  LucSigTypeOrSize &= LpRxUnpack->ucRdEndMask;
  /* Copy the local signal variable data to higher byte of double word
  variable */
  LaaApplSignal[COM_ONE].byte_val.BO_Byte[COM_DWORD_MS_BYTE_IDX]
  |= LucSigTypeOrSize;
  /* Copy the double word variable data to signal data pointer */
  /* Get the base address */
  #if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)
  /* @Trace: Com_SUD_API_01730 */
  LpLocalBuffer = 
    (uint8 *)(&LaaApplSignal[COM_ONE].byte_val.BO_Byte[COM_DWORD_LS_BYTE_IDX]);
  #else
  /* @Trace: Com_SUD_API_01731 */
  LpLocalBuffer = 
    (uint8 *)(&LaaApplSignal[COM_ZERO].byte_val.BO_Byte[COM_DWORD_LS_BYTE_IDX]);
  #endif

  if(LpSigDataPtr != NULL_PTR)
  {
    /* @Trace: Com_SUD_API_01187 */
    LpLocalSigBuffer = (uint8 *) LpSigDataPtr;
    /* @Trace: Com_SUD_API_01188 */
    /* @Trace: Com_SUD_API_01189 */
    /* Copy the double word variable data to signal data pointer */
    for(LucCount = COM_ZERO; LucCount < COM_FOUR; LucCount++)
    {
      /* @Trace: Com_SUD_API_01190 */
      *LpLocalSigBuffer = *LpLocalBuffer;
      #if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)
      /* @Trace: Com_SUD_API_01732 */
      LpLocalBuffer--;
      LpLocalSigBuffer++;
      #else
      /* @Trace: Com_SUD_API_01733 */
      LpLocalBuffer++;
      LpLocalSigBuffer++;
      #endif
    }

    #if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)
    /* @Trace: Com_SUD_API_01191 */
    LpLocalBuffer = 
    (uint8 *)(&LaaApplSignal[COM_ZERO].byte_val.BO_Byte[COM_DWORD_LS_BYTE_IDX]);
    #else
    /* @Trace: Com_SUD_API_01735 */
    LpLocalBuffer = 
    (uint8 *)(&LaaApplSignal[COM_ONE].byte_val.BO_Byte[COM_DWORD_LS_BYTE_IDX]);
    #endif

    /* @Trace: Com_SUD_API_01192 */
    /* @Trace: Com_SUD_API_01193 */
    for(; LucCount < COM_EIGHT; LucCount++)
    {
      /* @Trace: Com_SUD_API_01194 */
      *LpLocalSigBuffer = *LpLocalBuffer;
      #if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)
      /* @Trace: Com_SUD_API_01736 */
      LpLocalBuffer--;
      LpLocalSigBuffer++;
      #else
      /* @Trace: Com_SUD_API_01737 */
      LpLocalBuffer++;
      LpLocalSigBuffer++;
      #endif
    }
  }
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Com_UnPackNineByteOrdering                          **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function unpacks the signal of size more than  **
**                        64 bits and spread across five bytes in an I-PDU    **
**                        buffer.                                             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same signal.                  **
**                        Reentrant for different signals.                    **
**                                                                            **
** Input Parameters     : LpRxUnpack, LpSigDataPtr                            **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : SchM_Exit_Com()            **
**                                                 SchM_Enter_Com()           **
*******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE) Com_UnPackNineByteOrdering
(P2CONST(Com_RxUnpack, AUTOMATIC, COM_CONST) LpRxUnpack,
                           P2VAR(void, AUTOMATIC, COM_VAR) LpSigDataPtr)
{
  /* @Trace: Com_SUD_API_01195 */
  /* @Trace: SWS_Com_00675, SWS_Com_00007, SWS_Com_00810, SWS_Com_00008*/
  P2CONST(uint8, AUTOMATIC, COM_CONST) LpRdBuffer;
  P2VAR(uint8, AUTOMATIC, COM_VAR) LpLocalBuffer;
  P2VAR(uint8, AUTOMATIC, COM_VAR) LpLocalSigBuffer;
  P2VAR(uint8, AUTOMATIC, COM_VAR) LpApplBuffer;
  Com_MIdWord_Access LaaApplSignal[COM_TWO];
  Com_MIWord_Access LunApplSigHi;
  uint8 LucSigTypeOrSize;
  uint8 LucSignMask;
  uint8 LucCount;
  /* Initialize the double word variables to zero */
  LaaApplSignal[COM_ZERO].whole_dword = COM_ZERO;
  LaaApplSignal[COM_ONE].whole_dword = COM_ZERO;
  /* Initialize the lower byte of word variable to zero */
  LunApplSigHi.byte_val.BO_Byte[COM_WORD_LS_BYTE_IDX] = COM_ZERO;
  /* Get the pointer to lower byte of double word variable and assign it to
  application buffer pointer */
  LpApplBuffer = (P2VAR(uint8, AUTOMATIC, COM_VAR))
    &LaaApplSignal[COM_ZERO].byte_val.BO_Byte[COM_DWORD_LS_BYTE_IDX];
  /* Get the pointer I-PDU buffer */
  LpRdBuffer = (LpRxUnpack->pRdBuffer);
  /* Get the signal size that spread across number of bytes */
  LucSigTypeOrSize = COM_EIGHT;
  /* Enter protection area */
  SchM_Enter_Com_RX_EXT_SIG_DATA_PROTECTION_AREA();
  /* Loop for signal size */
  do
  {
    /* @Trace: Com_SUD_API_01196 */
    /* Copy the data from the I-PDU buffer to application buffer */
    *LpApplBuffer = *LpRdBuffer;
    #if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)
    /* @Trace: Com_SUD_API_01738 */
    /* Decrement application buffer pointer */
    LpApplBuffer--;
    /* Decrement I-PDU buffer pointer */
    LpRdBuffer++;
    #else
    /* @Trace: Com_SUD_API_01739 */
    /* Increment application buffer pointer */
    LpApplBuffer++;
    /* Increment I-PDU buffer pointer */
    LpRdBuffer--;
    #endif
    /* @Trace: Com_SUD_API_01740 */
    /* Decrement signal size */
    LucSigTypeOrSize--;
  }while(LucSigTypeOrSize != COM_FOUR);

  /* @Trace: Com_SUD_API_01197 */
  LpApplBuffer = (P2VAR(uint8, AUTOMATIC, COM_VAR))
    &LaaApplSignal[COM_ONE].byte_val.BO_Byte[COM_DWORD_LS_BYTE_IDX];

  do
  {
    /* @Trace: Com_SUD_API_01198 */
    /* Copy the data from the I-PDU buffer to application buffer */
    *LpApplBuffer = *LpRdBuffer;
    #if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)
    /* @Trace: Com_SUD_API_01741 */
    /* Decrement application buffer pointer */
    LpApplBuffer--;
    /* Decrement I-PDU buffer pointer */
    LpRdBuffer++;
    #else
    /* @Trace: Com_SUD_API_01742 */
    /* Increment application buffer pointer */
    LpApplBuffer++;
    /* Increment I-PDU buffer pointer */
    LpRdBuffer--;
    #endif
    /* @Trace: Com_SUD_API_01743 */
    /* Decrement signal size */
    LucSigTypeOrSize--;
  }while(LucSigTypeOrSize != COM_ZERO);

  /* @Trace: Com_SUD_API_01199 */
  /* Get the I-PDU buffer pointer data to the higher byte of word variable */
  LunApplSigHi.byte_val.BO_Byte[COM_WORD_MS_BYTE_IDX] = *LpRdBuffer;
  /* Exit protection area */
  SchM_Exit_Com_RX_EXT_SIG_DATA_PROTECTION_AREA();
  /* Get the number of shift bits */
  LucSignMask = LpRxUnpack->ucNoOfShiftBits;
  /* Shift the double word variable to right by the number of shift bits */
  LaaApplSignal[COM_ZERO].whole_dword  >>= LucSignMask;
  LaaApplSignal[COM_ZERO].whole_dword |=
    (LaaApplSignal[COM_ONE].whole_dword << (COM_THIRTY_TWO - LucSignMask));
  LaaApplSignal[COM_ONE].whole_dword >>= LucSignMask;
  /* Shift the word variable to right by the number of shift bits */
  LunApplSigHi.whole_word  >>= LucSignMask;
  /* Get the lower byte of word variable to local signal variable  */
  LucSigTypeOrSize = LunApplSigHi.byte_val.BO_Byte[COM_WORD_LS_BYTE_IDX];
  /* Apply end mask to clear unoccupied area of local signal variable */
  LucSigTypeOrSize &= LpRxUnpack->ucRdEndMask;
  /* Copy the local signal variable data to higher byte of double word
  variable */
  LaaApplSignal[COM_ONE].byte_val.BO_Byte[COM_DWORD_MS_BYTE_IDX] |= 
    LucSigTypeOrSize;
  /* Copy the double word variable data to signal data pointer */
  /* Get the base address */
  #if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)
  /* @Trace: Com_SUD_API_01744 */
  LpLocalBuffer = 
    (uint8 *)(&LaaApplSignal[COM_ZERO].byte_val.BO_Byte[COM_DWORD_MS_BYTE_IDX]);
  #else
  /* @Trace: Com_SUD_API_01745 */
  LpLocalBuffer = 
    (uint8 *)(&LaaApplSignal[COM_ZERO].byte_val.BO_Byte[COM_DWORD_LS_BYTE_IDX]);
  #endif
  if(LpSigDataPtr != NULL_PTR)
  {
    /* @Trace: Com_SUD_API_01200 */
    LpLocalSigBuffer = (uint8 *) LpSigDataPtr;
    /* @Trace: Com_SUD_API_01201 */
    /* @Trace: Com_SUD_API_01202 */
    /* Copy the double word variable data to signal data pointer */
    for(LucCount = COM_ZERO; LucCount < COM_FOUR; LucCount++)
    {
      /* @Trace: Com_SUD_API_01203 */
      *LpLocalSigBuffer = *LpLocalBuffer;
      #if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)
      /* @Trace: Com_SUD_API_01746 */
      LpLocalBuffer++;
      LpLocalSigBuffer++;
      #else
      /* @Trace: Com_SUD_API_01747 */
      LpLocalBuffer++;
      LpLocalSigBuffer++;
      #endif
    }

    #if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)
    /* @Trace: Com_SUD_API_01204 */
    LpLocalBuffer = 
    (uint8 *)(&LaaApplSignal[COM_ONE].byte_val.BO_Byte[COM_DWORD_MS_BYTE_IDX]);
    #else
    /* @Trace: Com_SUD_API_01748 */
    LpLocalBuffer = 
    (uint8 *)(&LaaApplSignal[COM_ONE].byte_val.BO_Byte[COM_DWORD_LS_BYTE_IDX]);
    #endif

    /* @Trace: Com_SUD_API_01205 */
    /* @Trace: Com_SUD_API_01206 */
    for(; LucCount < COM_EIGHT; LucCount++)
    {
      /* @Trace: Com_SUD_API_01207 */
      *LpLocalSigBuffer = *LpLocalBuffer;
      #if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)
      /* @Trace: Com_SUD_API_01749 */
      LpLocalBuffer++;
      LpLocalSigBuffer++;
      #else
      /* @Trace: Com_SUD_API_01750 */
      LpLocalBuffer++;
      LpLocalSigBuffer++;
      #endif
    }
  }
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"


/*******************************************************************************
** Function Name        : Com_UnPackEightBytes                                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function unpacks the signal of size more than  **
**                        64 bits and spread across eight bytes in an I-PDU   **
**                        buffer.                                             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same signal.                  **
**                        Reentrant for different signals.                    **
**                                                                            **
** Input Parameters     : LpRxUnpack, LpSigDataPtr                            **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : SchM_Exit_Com()            **
**                                                 SchM_Enter_Com()           **
*******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE) Com_UnPackEightBytes
(P2CONST(Com_RxUnpack, AUTOMATIC, COM_CONST) LpRxUnpack,
                           P2VAR(void, AUTOMATIC, COM_VAR) LpSigDataPtr)
{
  /* @Trace: Com_SUD_API_01208 */
  /* @Trace: SWS_Com_00675, SWS_Com_00007, SWS_Com_00810 */
  P2CONST(uint8, AUTOMATIC, COM_CONST) LpRdBuffer;
  P2VAR(uint8, AUTOMATIC, COM_VAR) LpApplBuffer;
  uint8 LucSigTypeOrSize;
  /* Get the pointer to lower byte of double word variable and assign it to
  application buffer pointer */
  LpApplBuffer = (P2VAR(uint8, AUTOMATIC, COM_VAR)) LpSigDataPtr;
  /* Get the pointer I-PDU buffer */
  LpRdBuffer = (LpRxUnpack->pRdBuffer);
  /* Get the signal size that spread across number of bytes */
  LucSigTypeOrSize = COM_EIGHT;
  /* Enter protection area */
  SchM_Enter_Com_RX_EXT_SIG_DATA_PROTECTION_AREA();
  /* Loop for signal size */
  do
  {
    /* @Trace: Com_SUD_API_01209 */
    /* Copy the data from the I-PDU buffer to application buffer */
    *LpApplBuffer = *LpRdBuffer;
    #if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)
    /* @Trace: Com_SUD_API_01751 */
    /* Decrement application buffer pointer */
    LpApplBuffer--;
    /* Decrement I-PDU buffer pointer */
    LpRdBuffer--;
    #else
    /* @Trace: Com_SUD_API_01752 */
    /* Increment application buffer pointer */
    LpApplBuffer++;
    /* Increment I-PDU buffer pointer */
    LpRdBuffer++;
    #endif
    /* @Trace: Com_SUD_API_01753 */
    /* Decrement signal size */
    LucSigTypeOrSize--;
  }while(LucSigTypeOrSize != COM_ZERO);
  /* @Trace: Com_SUD_API_01210 */
  /* Exit protection area */
  SchM_Exit_Com_RX_EXT_SIG_DATA_PROTECTION_AREA();
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name        : Com_UnPackEightByteOrdering                         **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function unpacks the signal of size more than  **
**                        64 bits and spread across eight bytes in an I-PDU   **
**                        buffer.                                             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same signal.                  **
**                        Reentrant for different signals.                    **
**                                                                            **
** Input Parameters     : LpRxUnpack, LpSigDataPtr                            **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : SchM_Exit_Com()            **
**                                                 SchM_Enter_Com()           **
*******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"

FUNC(void, COM_CODE) Com_UnPackEightByteOrdering
(P2CONST(Com_RxUnpack, AUTOMATIC, COM_CONST) LpRxUnpack,
                           P2VAR(void, AUTOMATIC, COM_VAR) LpSigDataPtr)
{
  /* @Trace: Com_SUD_API_01211 */
  P2CONST(uint8, AUTOMATIC, COM_CONST) LpRdBuffer;
  P2VAR(uint8, AUTOMATIC, COM_VAR) LpApplBuffer;
  uint8 LucSigTypeOrSize;
  /* Get the pointer to lower byte of double word variable and assign it to
  application buffer pointer */
  LpApplBuffer = (P2VAR(uint8, AUTOMATIC, COM_VAR)) LpSigDataPtr;
  /* Get the pointer I-PDU buffer */
  LpRdBuffer = (LpRxUnpack->pRdBuffer);
  /* Get the signal size that spread across number of bytes */
  LucSigTypeOrSize = COM_EIGHT;
  /* Enter protection area */
  SchM_Enter_Com_RX_EXT_SIG_DATA_PROTECTION_AREA();
  /* Loop for signal size */
  do
  {
    /* @Trace: Com_SUD_API_01212 */
    /* Copy the data from the I-PDU buffer to application buffer */
    *LpApplBuffer = *LpRdBuffer;
    #if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)
    /* @Trace: Com_SUD_API_01754 */
    /* Decrement application buffer pointer */
    LpApplBuffer--;
    /* Decrement I-PDU buffer pointer */
    LpRdBuffer++;
    #else
    /* @Trace: Com_SUD_API_01755 */
    /* Increment application buffer pointer */
    LpApplBuffer++;
    /* Increment I-PDU buffer pointer */
    LpRdBuffer--;
    #endif
    /* @Trace: Com_SUD_API_01756 */
    /* Decrement signal size */
    LucSigTypeOrSize--;
  }while(LucSigTypeOrSize != COM_ZERO);
  /* @Trace: Com_SUD_API_01213 */
  SchM_Exit_Com_RX_EXT_SIG_DATA_PROTECTION_AREA();
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Com_Up64Bts_ProcSrcData                             **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Sub function of Com_UnPackBytes64bit                **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : NA                                                  **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Function(s) invoked    :                            **
*******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE) Com_Up64Bts_ProcSrcData(
  P2VAR(uint8, AUTOMATIC, COM_VAR) LpApplBuffer, 
  P2CONST(uint8, AUTOMATIC, COM_CONST) LpRdBuffer, 
  PduLengthType LucSigTypeOrSize)
{
  /* @Trace: Com_SUD_API_01542 */
  P2VAR(uint8, AUTOMATIC, COM_VAR) LpLocalApplBuffer;
  P2CONST(uint8, AUTOMATIC, COM_CONST) LpLocalRdBuffer;
  PduLengthType LucLocalSigTypeOrSize = LucSigTypeOrSize;

  LpLocalApplBuffer = LpApplBuffer;
  LpLocalRdBuffer = LpRdBuffer;
  /* Loop for signal size */
  do
  {
    /* @Trace: Com_SUD_API_01215 */
    /* Copy the data from the I-PDU buffer to application buffer */
    *LpLocalApplBuffer = *LpLocalRdBuffer;
    #if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)
    /* @Trace: Com_SUD_API_01757 */
    /* Decrement application buffer pointer */
    LpLocalApplBuffer--;
    /* Decrement I-PDU buffer pointer */
    LpLocalRdBuffer--;
    #else
    /* @Trace: Com_SUD_API_01758 */
    /* Increment application buffer pointer */
    LpLocalApplBuffer++;
    /* Increment I-PDU buffer pointer */
    LpLocalRdBuffer++;
    #endif
    /* @Trace: Com_SUD_API_01759 */
    /* Decrement signal size */
    LucLocalSigTypeOrSize--;
  }while(LucLocalSigTypeOrSize != 0);
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Com_Up64Bts_LocateSignByte                          **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Sub function of Com_UnPackBytes64bit                **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : NA                                                  **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Function(s) invoked    :                            **
*******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE) Com_Up64Bts_LocateSignByte(
  P2VAR(Com_MIdWord_Access, AUTOMATIC, COM_VAR) LocalPtrApplBuffer,
  PduLengthType LucSigTypeOrSize)
{
  /* Check whether the signal size is 40 bits */
  if(COM_TYPE_40 == LucSigTypeOrSize)
  {
    /* @Trace: Com_SUD_API_01244 */
    /* Get sign extension to higher byte of double word variable */
    LocalPtrApplBuffer[COM_ONE].whole_dword |= COM_SIGN_MASK_40_BIT;
  }
  if(COM_TYPE_48 == LucSigTypeOrSize)
  {
    /* @Trace: Com_SUD_API_01245 */
    /* Get sign extension to higher byte of double word variable */
    LocalPtrApplBuffer[COM_ONE].whole_dword |= COM_SIGN_MASK_48_BIT;
  }
  if(COM_TYPE_56 == LucSigTypeOrSize)
  {
    /* @Trace: Com_SUD_API_01246 */
    /* Get sign extension to higher byte of double word variable */
    LocalPtrApplBuffer[COM_ONE].whole_dword |= COM_SIGN_MASK_56_BIT;
  }
  if(COM_TYPE_64 == LucSigTypeOrSize)
  {
    /* @Trace: Com_SUD_API_01247 */
    /* Get sign extension to higher byte of double word variable */
    LocalPtrApplBuffer[COM_ONE].whole_dword |= (uint32)COM_SIGN_MASK_64_BIT;
  }
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Com_Up64Bts_ProcDstBuffer                           **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Sub function of Com_UnPackBytes64bit                **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : NA                                                  **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Function(s) invoked    :                            **
*******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE) Com_Up64Bts_ProcDstBuffer(
  uint8 LucStartInd, uint8 LucStopInd,
  P2VAR(uint8, AUTOMATIC, COM_VAR) LpSigBuffer, 
  P2VAR(uint8, AUTOMATIC, COM_VAR) LpBuffer)
{  
  /* @Trace: Com_SUD_API_01519 */
  uint8 LucCount;
  P2VAR(uint8, AUTOMATIC, COM_VAR) LpLocalSigBuffer;
  P2VAR(uint8, AUTOMATIC, COM_VAR) LpLocalBuffer;

  LpLocalSigBuffer = LpSigBuffer;
  LpLocalBuffer = LpBuffer;
  /* @Trace: Com_SUD_API_01251 */
  /* @Trace: Com_SUD_API_01252 */
  /* Copy the double word variable data to signal data pointer */
  for(LucCount = LucStartInd; LucCount < LucStopInd; LucCount++)
  {
    /* @Trace: Com_SUD_API_01253 */
    *LpLocalSigBuffer = *LpLocalBuffer;
    #if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)
    /* @Trace: Com_SUD_API_01787 */
    LpLocalBuffer--;
    LpLocalSigBuffer++;
    #else
    /* @Trace: Com_SUD_API_01788 */
    LpLocalBuffer++;
    LpLocalSigBuffer++;
    #endif
  }
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Com_UnPackBytes64bit                                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function unpacks the signal of size more than  **
**                        64 bits and spread across five bytes in an I-PDU    **
**                        buffer.                                             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same signal.                  **
**                        Reentrant for different signals.                    **
**                                                                            **
** Input Parameters     : LpRxUnpack, LpSigDataPtr                            **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : SchM_Exit_Com()            **
**                                                 SchM_Enter_Com()           **
*******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE) Com_UnPackBytes64bit
(P2CONST(Com_RxUnpack, AUTOMATIC, COM_CONST) LpRxUnpack,
                           P2VAR(void, AUTOMATIC, COM_VAR) LpSigDataPtr)
{
  /* @Trace: Com_SUD_API_01214 */
  P2CONST(uint8, AUTOMATIC, COM_CONST) LpRdBuffer;
  P2VAR(uint8, AUTOMATIC, COM_VAR) LpLocalBuffer;
  P2VAR(uint8, AUTOMATIC, COM_VAR) LpLocalSigBuffer;
  P2VAR(uint8, AUTOMATIC, COM_VAR) LpApplBuffer;
  P2VAR(uint8, AUTOMATIC, COM_VAR) LpSignBuffer;
  Com_MIdWord_Access LaaApplSignal[COM_THREE];
  Com_MIWord_Access LunApplSigHi;
  uint8 LucSigTypeOrSize;
  uint8 LucSignMask;
  uint8 LucIpduBuffer;
  uint8 lUcRdEndMask;
  lUcRdEndMask = COM_ZERO;
  /* Initialize the double word variables to zero */
  LaaApplSignal[COM_ZERO].whole_dword = COM_ZERO;
  LaaApplSignal[COM_ONE].whole_dword = COM_ZERO;
  LaaApplSignal[COM_TWO].whole_dword = COM_ZERO;
  /* Initialize the lower byte of word variable to zero */
  LunApplSigHi.byte_val.BO_Byte[COM_WORD_LS_BYTE_IDX] = COM_ZERO;
  /* Get the pointer to lower byte of double word variable and assign it to
  application buffer pointer */
  LpApplBuffer = (P2VAR(uint8, AUTOMATIC, COM_VAR))
    &LaaApplSignal[COM_ZERO].byte_val.BO_Byte[COM_DWORD_LS_BYTE_IDX];
  LpSignBuffer = LpApplBuffer;
  /* Get the pointer I-PDU buffer */
  LpRdBuffer = (LpRxUnpack->pRdBuffer);
  /* Get the signal size that spread across number of bytes */
  LucSigTypeOrSize =  COM_FOUR;
  /* Enter protection area */
  SchM_Enter_Com_RX_EXT_SIG_DATA_PROTECTION_AREA();
  /* Process for first 4 bytes */
  Com_Up64Bts_ProcSrcData(LpApplBuffer, LpRdBuffer, LucSigTypeOrSize);
  LucSigTypeOrSize =  (uint8)(LpRxUnpack->ddSignalSize) - 4;
  LpApplBuffer = (P2VAR(uint8, AUTOMATIC, COM_VAR))
    &LaaApplSignal[COM_ONE].byte_val.BO_Byte[COM_DWORD_LS_BYTE_IDX];
  /* polyspace-begin MISRA2012:18.4 [Justified:Low] "Pointer access accepted as index is signed number" */
  #if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)
  /* @Trace: Com_SUD_API_01520 */
  LpRdBuffer -= 4;
  #else
  /* @Trace: Com_SUD_API_01521 */
  LpRdBuffer += 4;
  #endif
  /* polyspace-end MISRA2012:18.4 [Justified:Low] "Pointer access accepted as index is signed number" */
  /* @Trace: Com_SUD_API_01218 */
  /* Process for the rest bytes (up to 4 bytes) */
  Com_Up64Bts_ProcSrcData(LpApplBuffer, LpRdBuffer, LucSigTypeOrSize);
  /* Get the I-PDU buffer pointer data to the higher byte of word variable */
  LunApplSigHi.byte_val.BO_Byte[COM_WORD_MS_BYTE_IDX] = *LpRdBuffer;
  /* Exit protection area */
  SchM_Exit_Com_RX_EXT_SIG_DATA_PROTECTION_AREA();
  /* Get the number of shift bits */
  LucSignMask = LpRxUnpack->ucNoOfShiftBits;
  /* Shift the double word variable to right by the number of shift bits */

  if(LucSignMask != 0)
  {
    /* @Trace: Com_SUD_API_01219 */
    LaaApplSignal[COM_ZERO].whole_dword  >>= LucSignMask;
    LaaApplSignal[COM_TWO].whole_dword = LaaApplSignal[COM_ONE].whole_dword;
    LaaApplSignal[COM_ONE].whole_dword <<= (COM_THIRTY_TWO - LucSignMask);
    LaaApplSignal[COM_ZERO].whole_dword |= LaaApplSignal[COM_ONE].whole_dword ;
    LaaApplSignal[COM_ONE].whole_dword  = LaaApplSignal[COM_TWO].whole_dword; 
    LaaApplSignal[COM_ONE].whole_dword >>= LucSignMask;
  }
  /* @Trace: Com_SUD_API_01220 */
  /* Shift the word variable to right by the number of shift bits */
  LunApplSigHi.whole_word  >>= LucSignMask;
  /* Apply end mask to clear unoccupied area of local signal variable */
  lUcRdEndMask &= LpRxUnpack->ucRdEndMask;
  /* Copy the double word variable data to signal data pointer */
  /* Get the base address */
  /* polyspace-begin MISRA2012:18.4 [Justified:Low] "Pointer access accepted as index is signed number" */
  #if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)
  /* @Trace: Com_SUD_API_01763 */
  LpSignBuffer -= (Com_PtrType)((uint8)(LucSigTypeOrSize));
  #else
  /* @Trace: Com_SUD_API_01764 */
  LpSignBuffer = &LpSignBuffer[(Com_PtrType)((uint8)(LucSigTypeOrSize))];
  #endif
  /* @Trace: Com_SUD_API_01765 */
  /* polyspace-end MISRA2012:18.4 [Justified:Low] "Pointer access accepted as index is signed number" */
  LucIpduBuffer = (*LpSignBuffer)|lUcRdEndMask;
  *LpSignBuffer |= LucIpduBuffer;
  #if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)
  /* @Trace: Com_SUD_API_01766 */
  LpLocalBuffer = 
    (uint8 *)(&LaaApplSignal[COM_ONE].byte_val.BO_Byte[COM_DWORD_LS_BYTE_IDX]);
  #else
  /* @Trace: Com_SUD_API_01767 */
  LpLocalBuffer = 
    (uint8 *)(&LaaApplSignal[COM_ZERO].byte_val.BO_Byte[COM_DWORD_LS_BYTE_IDX]);
  #endif
  /* @Trace: Com_SUD_API_01768 */
  /* get sign mask */
  LucSignMask = LpRxUnpack->ucRdSignMask;
  LucSigTypeOrSize =  (uint8)(LpRxUnpack->ucSignalType); 
  if((LucIpduBuffer & LucSignMask) != COM_ZERO)
  {
    /* @Trace: Com_SUD_API_01221 */
    /* Perform sign conversion */
    LucIpduBuffer |= LucSignMask;

    Com_Up64Bts_LocateSignByte(&LaaApplSignal[COM_ZERO], LucSigTypeOrSize);
  }
  else
  {
    /* @Trace: Com_SUD_API_01226 */
    LaaApplSignal[COM_ONE].whole_dword |= COM_ZERO; 
  }
  /* @Trace: Com_SUD_API_01227 */
  *LpSignBuffer = LucIpduBuffer;
  if(LpSigDataPtr != NULL_PTR)
  {
    /* @Trace: Com_SUD_API_01228 */
    LpLocalSigBuffer = (uint8 *) LpSigDataPtr;
    /* Process for first 4 bytes */
    Com_Up64Bts_ProcDstBuffer(COM_ZERO, COM_FOUR, LpLocalSigBuffer, 
      LpLocalBuffer);
    LucSigTypeOrSize =  (uint8)(LpRxUnpack->ddSignalSize) - 4;
    #if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)
    /* @Trace: Com_SUD_API_01771 */
    LpLocalBuffer = 
    (uint8 *)(&LaaApplSignal[COM_ZERO].byte_val.BO_Byte[COM_DWORD_LS_BYTE_IDX]);
    #else
    /* @Trace: Com_SUD_API_01772 */
    LpLocalBuffer = 
    (uint8 *)(&LaaApplSignal[COM_ONE].byte_val.BO_Byte[COM_DWORD_LS_BYTE_IDX]);
    #endif
    /* @Trace: Com_SUD_API_01232 */
    /* Process for the rest bytes (up to 4 bytes) */
    Com_Up64Bts_ProcDstBuffer(COM_ZERO, LucSigTypeOrSize, &LpLocalSigBuffer[4], 
      LpLocalBuffer);
  }
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Com_Up64BtsOrd_ProcSrcData                          **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Sub function of Com_UnPackBytes64bitOrdering        **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : NA                                                  **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Function(s) invoked    :                            **
*******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE) Com_Up64BtsOrd_ProcSrcData(
  P2VAR(uint8, AUTOMATIC, COM_VAR) LpApplBuffer, 
  P2CONST(uint8, AUTOMATIC, COM_CONST) LpRdBuffer, 
  PduLengthType LucSigTypeOrSize)
{
  /* @Trace: Com_SUD_API_01523 */
  P2VAR(uint8, AUTOMATIC, COM_VAR) LpLocalApplBuffer;
  P2CONST(uint8, AUTOMATIC, COM_CONST) LpLocalRdBuffer;
  PduLengthType LucLocalSigTypeOrSize = LucSigTypeOrSize;

  LpLocalApplBuffer = LpApplBuffer;
  LpLocalRdBuffer = LpRdBuffer;
  /* Loop for signal size */
  do
  {
    /* @Trace: Com_SUD_API_01237 */
    /* Copy the data from the I-PDU buffer to application buffer */
    *LpLocalApplBuffer = *LpLocalRdBuffer;
    #if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)
    /* @Trace: Com_SUD_API_01775 */
    /* Decrement application buffer pointer */
    LpLocalApplBuffer--;
    /* Decrement I-PDU buffer pointer */
    LpLocalRdBuffer++;
    #else
    /* @Trace: Com_SUD_API_01776 */
    /* Increment application buffer pointer */
    LpLocalApplBuffer++;
    /* Increment I-PDU buffer pointer */
    LpLocalRdBuffer--;
    #endif
    /* @Trace: Com_SUD_API_01777 */
    /* Decrement signal size */
    LucLocalSigTypeOrSize--;
  }while(LucLocalSigTypeOrSize != 0);
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Com_UnPackBytes64bitOrdering                        **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function unpacks the signal of size more than  **
**                        64 bits and spread across five bytes in an I-PDU    **
**                        buffer.                                             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same signal.                  **
**                        Reentrant for different signals.                    **
**                                                                            **
** Input Parameters     : LpRxUnpack, LpSigDataPtr                            **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : SchM_Exit_Com()            **
**                                                 SchM_Enter_Com()           **
*******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE) Com_UnPackBytes64bitOrdering
(P2CONST(Com_RxUnpack, AUTOMATIC, COM_CONST) LpRxUnpack,
                           P2VAR(void, AUTOMATIC, COM_VAR) LpSigDataPtr)
{
  /* @Trace: Com_SUD_API_01236 */
  P2CONST(uint8, AUTOMATIC, COM_CONST) LpRdBuffer;
  P2VAR(uint8, AUTOMATIC, COM_VAR) LpLocalBuffer;
  P2VAR(uint8, AUTOMATIC, COM_VAR) LpLocalSigBuffer;
  P2VAR(uint8, AUTOMATIC, COM_VAR) LpApplBuffer;
  P2VAR(uint8, AUTOMATIC, COM_VAR) LpSignBuffer;
  Com_MIdWord_Access LaaApplSignal[COM_THREE];
  Com_MIWord_Access LunApplSigHi;
  PduLengthType LucSigTypeOrSize;
  uint8 LucSignMask;
  uint8 LucIpduBuffer;
  uint8 lUcRdEndMask;
  lUcRdEndMask = COM_ZERO;
  /* Initialize the double word variables to zero */
  LaaApplSignal[COM_ZERO].whole_dword = COM_ZERO;
  LaaApplSignal[COM_ONE].whole_dword = COM_ZERO;
  /* Initialize the lower byte of word variable to zero */
  LunApplSigHi.byte_val.BO_Byte[COM_WORD_LS_BYTE_IDX] = COM_ZERO;
  /* Get the pointer to lower byte of double word variable and assign it to
  application buffer pointer */
  LpApplBuffer = (P2VAR(uint8, AUTOMATIC, COM_VAR))
    &LaaApplSignal[COM_ZERO].byte_val.BO_Byte[COM_DWORD_LS_BYTE_IDX];
  LpSignBuffer = LpApplBuffer;
  /* Get the pointer I-PDU buffer */
  LpRdBuffer = (LpRxUnpack->pRdBuffer);
  /* Get the signal size that spread across number of bytes */
  LucSigTypeOrSize =  COM_FOUR;
  /* Enter protection area */
  SchM_Enter_Com_RX_EXT_SIG_DATA_PROTECTION_AREA();
  /* Process for first 4 bytes */
  Com_Up64BtsOrd_ProcSrcData(LpApplBuffer, LpRdBuffer, LucSigTypeOrSize);

  if (LpRxUnpack->ddSignalSize > 0x04u)
  {
    /* @Trace: Com_SUD_API_01238 */
    LucSigTypeOrSize = (LpRxUnpack->ddSignalSize) - 4;
    LpApplBuffer = (P2VAR(uint8, AUTOMATIC, COM_VAR))
      &LaaApplSignal[COM_ONE].byte_val.BO_Byte[COM_DWORD_LS_BYTE_IDX];
  /* polyspace-begin MISRA2012:18.4 [Justified:Low] "Pointer access accepted as index is signed number" */
    #if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)
    /* @Trace: Com_SUD_API_01591 */
    LpRdBuffer += 4;
    #else
    /* @Trace: Com_SUD_API_01590 */
    LpRdBuffer -= 4;
    #endif
  /* polyspace-end MISRA2012:18.4 [Justified:Low] "Pointer access accepted as index is signed number" */
    /* Process for the rest bytes (up to 4 bytes) */
    /* @Trace: Com_SUD_API_01589 */
    Com_Up64BtsOrd_ProcSrcData(LpApplBuffer, LpRdBuffer, LucSigTypeOrSize);
  }

  /* @Trace: Com_SUD_API_01240 */
  /* Get the I-PDU buffer pointer data to the higher byte of word variable */
  LunApplSigHi.byte_val.BO_Byte[COM_WORD_MS_BYTE_IDX] = *LpRdBuffer;
  /* Exit protection area */
  SchM_Exit_Com_RX_EXT_SIG_DATA_PROTECTION_AREA();
  /* Get the number of shift bits */
  LucSignMask = LpRxUnpack->ucNoOfShiftBits;

  if(LucSignMask != 0)
  {
    /* @Trace: Com_SUD_API_01241 */
    LaaApplSignal[COM_ZERO].whole_dword  >>= (LucSignMask & 0x1Fu);
    LaaApplSignal[COM_TWO].whole_dword = LaaApplSignal[COM_ONE].whole_dword;
    LaaApplSignal[COM_ONE].whole_dword <<= (COM_THIRTY_TWO - LucSignMask);
    LaaApplSignal[COM_ZERO].whole_dword |= LaaApplSignal[COM_ONE].whole_dword ;
    LaaApplSignal[COM_ONE].whole_dword  = LaaApplSignal[COM_TWO].whole_dword; 
    LaaApplSignal[COM_ONE].whole_dword >>= (LucSignMask & 0x1Fu);
  }

  /* @Trace: Com_SUD_API_01242 */
  /* Shift the word variable to right by the number of shift bits */
  LunApplSigHi.whole_word  >>= (LucSignMask & 0x1Fu);
  /* Apply end mask to clear unoccupied area of local signal variable */
  lUcRdEndMask &= LpRxUnpack->ucRdEndMask;
  /* Copy the double word variable data to signal data pointer */
  /* Get the base address */
  /* polyspace-begin MISRA2012:18.4 [Justified:Low] "Pointer access accepted as index is signed number" */
  #if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)
  /* @Trace: Com_SUD_API_01781 */
  LpSignBuffer -= (Com_PtrType)((uint8)(LucSigTypeOrSize));
  #else
  /* @Trace: Com_SUD_API_01782 */
  LpSignBuffer = &LpSignBuffer[(Com_PtrType)((uint8)(LucSigTypeOrSize))];
  #endif
  /* @Trace: Com_SUD_API_01783 */
  /* polyspace-end MISRA2012:18.4 [Justified:Low] "Pointer access accepted as index is signed number" */
  LucIpduBuffer = (*LpSignBuffer)|lUcRdEndMask;
  *LpSignBuffer |= LucIpduBuffer;
  #if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)
  /* @Trace: Com_SUD_API_01784 */
  LpLocalBuffer = 
    (uint8 *)(&LaaApplSignal[COM_ONE].byte_val.BO_Byte[COM_DWORD_LS_BYTE_IDX]);
  #else
  /* @Trace: Com_SUD_API_01785 */
  LpLocalBuffer = 
    (uint8 *)(&LaaApplSignal[COM_ZERO].byte_val.BO_Byte[COM_DWORD_LS_BYTE_IDX]);
  #endif
  /* @Trace: Com_SUD_API_01786 */
  /* get sign mask */
  LucSignMask = LpRxUnpack->ucRdSignMask;
  LucSigTypeOrSize =  (uint8)(LpRxUnpack->ucSignalType); 
  if((LucIpduBuffer & LucSignMask) != COM_ZERO)
  {
    /* @Trace: Com_SUD_API_01243 */
    /* Perform sign conversion */
    LucIpduBuffer |= LucSignMask;
    Com_Up64Bts_LocateSignByte(&LaaApplSignal[COM_ZERO], LucSigTypeOrSize);
  }
  else
  {
    /* @Trace: Com_SUD_API_01248 */
    LaaApplSignal[COM_ONE].whole_dword |= COM_ZERO; 
  }
  /* @Trace: Com_SUD_API_01249 */
  *LpSignBuffer = LucIpduBuffer;
  if(LpSigDataPtr != NULL_PTR)
  {
    /* @Trace: Com_SUD_API_01250 */
    LpLocalSigBuffer = (uint8 *) LpSigDataPtr;
    /* Process for first 4 bytes */
    Com_Up64Bts_ProcDstBuffer(COM_ZERO, COM_FOUR, LpLocalSigBuffer, 
      LpLocalBuffer);

    #if (CPU_BYTE_ORDER == HIGH_BYTE_FIRST)
    /* @Trace: Com_SUD_API_01254 */
    LpLocalBuffer = 
    (uint8 *)(&LaaApplSignal[COM_ZERO].byte_val.BO_Byte[COM_DWORD_LS_BYTE_IDX]);
    #else
    /* @Trace: Com_SUD_API_01790 */
    LpLocalBuffer = 
    (uint8 *)(&LaaApplSignal[COM_ONE].byte_val.BO_Byte[COM_DWORD_LS_BYTE_IDX]);
    #endif
    /* @Trace: Com_SUD_API_01588 */
    /* Process for the rest bytes (up to 4 bytes) */
    Com_Up64Bts_ProcDstBuffer(COM_FOUR, COM_EIGHT, &LpLocalSigBuffer[4], 
      LpLocalBuffer);
  }
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
/* polyspace-end MISRA2012:D4.14 [Not a defect:Low] "LpRxUnpack and LpSigDataPtr pointers were checked outside unpacking functions" */
/* polyspace-end MISRA2012:11.5 [Not a defect:Low] "Following Com_SWS_00197 and Com_SWS_00198, data pointer of Com_Send/ReceiveSignal is void, so the casting to another type is inevitable." */
/* polyspace-end RTE:IDP [Not a defect:Low] "NULL pointer was checked by generator" */
/* polyspace-end RTE:SHF [Not a defect:Low] "Shift amount is inside its bounds. This is assured by generator */
/* polyspace-end CERT-C:EXP36-C [Justified:Low] "Following Com_SWS_00197 and Com_SWS_00198, data pointer of Com_Send/ReceiveSignal is void, so the casting to another type is inevitable." */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/

