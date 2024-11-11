/*******************************************************************************
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  This source code is permitted to be used only in projects contracted      **
**  with Hyundai Autoever, and any other use is prohibited.                   **
**  If you use it for other purposes or change the source code,               **
**  you may take legal responsibility.                                        **
**  In this case, There is no warranty and technical support.                 **
**                                                                            **
**  SRC-MODULE: IpduM_IntFunc.c                                               **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR IpduM Module                                          **
**                                                                            **
**  PURPOSE   : Provides definition of Internal Functions:                    **
**              IpduM_SetData                                                 **
**              IpduM_CopyData                                                **
**              IpduM_CopySegments                                            **
**              IpduM_GetSelBitField                                          **
**              IpduM_BinarySearch                                            **
**              IpduM_LinearSearch                                            **
**              IpduM_FetchTxMuxIpduPart                                      **
**              IpduM_DetCheckTxFunc                                          **
**              IpduM_InitMux                                                 **
**              IpduM_TxIpduMux                                               **
**              IpduM_TriggerTxIpduMux                                        **
**              IpduM_TxConfirmIpduMux                                        **
**              IpduM_RxIpduMux                                               **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision       Date                By               Description            **
********************************************************************************
** 1.0.8          27-Mar-2024         DH Kim           CP44-3766,3812,5321    **
** 1.0.7          27-Jul-2023         HaoTA4           CP44-2462              **
** 1.0.6          27-Jan-2023         JW Oh            CP44-1590              **
** 1.0.5          16-Dec-2022         NhatTD2          CP44-1256              **
** 1.0.4.1        14-Nov-2022         NhatTD2          CP44-973               **
** 1.0.3          15-Jul-2022         DuyNHP2          CP44-567               **
** 1.0.2          27-Jun-2022         DuyNHP2          CP44-141               **
** 1.0.1          10-Mar-2022         DuyNHP2          R44-Redmine #24418     **
** 1.0.0          15-Dec-2020         JsLim            Initial Version        **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* Inclusion for IpduM header files  */
#include "IpduM.h"

#if(IPDUM_ENABLE_MODULE == STD_ON)

/* Inclusion for PduR_IpduM functions */
#include "PduR_IpduM.h"

#if (IPDUM_COM_SUPPORT_DIRECT == STD_ON)
/* Inclusion for COM functions */
#include "Com.h"
#endif
/* Inclusion for functions of Exclusive Area */
#include "SchM_IpduM.h"
/* Inclusion for Global variables and symbols */
#include "IpduM_Globals.h"
/* Inclusion for IpduM internal functions header files */
#include "IpduM_IntFunc.h"

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

#define IPDUM_START_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
**                      Static function prototypes                            **
*******************************************************************************/
LOCAL_INLINE FUNC(void, IPDUM_CODE) IpduM_CopyData(
  P2CONST(uint8, AUTOMATIC, IPDUM_CONST) SrcPtr,
  P2VAR(uint8, AUTOMATIC, IPDUM_VAR) DstPtr, PduLengthType CopiedLength);

#if (IPDUM_TX_IPDU == STD_ON)
static FUNC(void, IPDUM_CODE) IpduM_CopySegments(
  IpduM_TxMuxSegmentIntType SegmentId,
  P2CONST(uint8, AUTOMATIC, IPDUM_APPL_DATA) SrcDataPtr, uint8 SegmentSize);
#endif

#if ((IPDUM_TX_IPDU == STD_ON) || (IPDUM_TX_CONTAINER == STD_ON))
LOCAL_INLINE FUNC(void, IPDUM_CODE) IpduM_SetData(
  P2VAR(uint8, AUTOMATIC, IPDUM_APPL_DATA) DstPtr,
  uint8 Value, PduLengthType DstLength);
#endif

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

/*******************************************************************************
** Function Name        : IpduM_SetData                                       **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : This function performs of setting all buffer bytes  **
**                        to an integer number                                **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : DstPtr - Pointer to destination buffer              **
**                        Value - Value of default pattern in byte            **
**                        DstLength - Size of destination buffer              **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) : None                           **
**                                                                            **
**                        Function(s) invoked: None                           **
**                                                                            **
*******************************************************************************/
#if ((IPDUM_TX_IPDU == STD_ON) || (IPDUM_TX_CONTAINER == STD_ON))
LOCAL_INLINE FUNC(void, IPDUM_CODE) IpduM_SetData(
  P2VAR(uint8, AUTOMATIC, IPDUM_APPL_DATA) DstPtr,
  uint8 Value, PduLengthType DstLength)
{
  PduLengthType LpDstLength = DstLength;
  uint8 *LpDstPtr = DstPtr;
  while ((PduLengthType)IPDUM_ZERO != LpDstLength)
  {
    /* @Trace: IpduM_SUD_API_001 */
    /* Set destination buffer to default value */
    /* polyspace +1 RTE:IDP [Not a defect:Low] "Pointer is not null and inside its bound. This is assured by generator" */
    *LpDstPtr = Value;
    /* Increment Source Buffer pointer */
    ++LpDstPtr;
    /* Decrease copied length */
    LpDstLength--;
  }
} /* End of IpduM_CopyData() */
#endif /* ((IPDUM_TX_IPDU == STD_ON) || (IPDUM_TX_STATIC_CONTAINER == STD_ON)) */

/*******************************************************************************
** Function Name        : IpduM_CopyData                                      **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function copy Data from source buffer to       **
**                        destination buffer in byte                          **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : Reentrant for different I-PDU                       **
**                                                                            **
** Input Parameters     : SrcPtr                                              **
**                        DstPtr                                              **
**                        CopiedLength                                        **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) : None                           **
**                                                                            **
**                        Function(s) invoked: None                           **
**                                                                            **
*******************************************************************************/
LOCAL_INLINE FUNC(void, IPDUM_CODE) IpduM_CopyData(
  P2CONST(uint8, AUTOMATIC, IPDUM_CONST) SrcPtr,
  P2VAR(uint8, AUTOMATIC, IPDUM_VAR) DstPtr, PduLengthType CopiedLength)
{
  if ((SrcPtr != NULL_PTR) && (DstPtr != NULL_PTR))
  {
    PduLengthType LpCopiedLength = CopiedLength;
    const uint8 *LpSrcPtr = SrcPtr;
    uint8 *LpDstPtr = DstPtr;

    while ((PduLengthType)IPDUM_ZERO != LpCopiedLength)
    {
      /* @Trace: IpduM_SUD_API_002 */
      /* Copy the data into destination buffer from source buffer */
      /* polyspace +1 RTE:IDP [Not a defect:Low] "Pointer is not null and inside its bound. This is assured by generator" */
      *LpDstPtr = *LpSrcPtr;
      /* Increment Source Buffer pointer */
      ++LpSrcPtr;
      /* Increment Destination Buffer Pointer */
      ++LpDstPtr;
      /* Decrease copied data length */
      LpCopiedLength--;

    }
  }
  else
  {
      /* No action */
  }
} /* End of IpduM_CopyData() */

/*******************************************************************************
** Function Name        : IpduM_CopySegments                                  **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function copy the data from source I-PDU to    **
**                        destination I-PDU as per the configured segments.   **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : Reentrant for different I-PDU                       **
**                                                                            **
** Input Parameters     : SegmentId                                           **
**                        SrcDataPtr                                          **
**                        SegmentSize                                         **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) : IpduM_SegmentField[]           **
**                                                                            **
**                        Function(s) invoked: None                           **
**                                                                            **
*******************************************************************************/
#if (IPDUM_TX_IPDU == STD_ON)
static FUNC(void, IPDUM_CODE) IpduM_CopySegments(
  IpduM_TxMuxSegmentIntType SegmentId,
  P2CONST(uint8, AUTOMATIC, IPDUM_APPL_DATA) SrcDataPtr, uint8 SegmentSize)
{
  if (NULL_PTR != SrcDataPtr)
  {
    IpduM_TxMuxSegmentIntType LpSegmentId = SegmentId;
    uint8 LpSegmentSize = SegmentSize;
    P2CONST(uint8, AUTOMATIC, IPDUM_CONST) ptrSrc;
    P2VAR(uint8, AUTOMATIC, IPDUM_VAR) ptrDst;
    uint8 noOfByte;
    uint8 bytePos;

    /* Enter critical area */
    SchM_Enter_IpduM_DEST_DATA_PROTECTION_AREA();

    #if (IPDUM_SEGMENT_BITFIELD == STD_ON)
    while ((uint8)IPDUM_ZERO != LpSegmentSize)
    #endif
    {
    /* @Trace: IpduM_SUD_API_003 */
    /* Get address of source buffer corresponding to this segment */
    /* polyspace +1 RTE:OBAI [Not a defect:Low] "Array access index is in-bounds. This is assured by generator" */
    ptrSrc = &SrcDataPtr[IpduM_GetTxSegmentByteOffset(LpSegmentId)];
    /* Get address of destination buffer corresponding to this segment */
    ptrDst = IpduM_GetAddrTxSegmentDestBuf(LpSegmentId);

    /* Get size of segment in byte */
    noOfByte = IpduM_GetTxSegmentSize(LpSegmentId);
    /* Initiate copied byte postion as zero */
    bytePos = (uint8)IPDUM_ZERO;

    #if (IPDUM_SEGMENT_BITFIELD == STD_ON)
    /* Check if the first Byte Mask is valid */
    if (IPDUM_BYTE_MASK_INVALID != IpduM_GetTxSegmentFirstByteSetMask(LpSegmentId))
    {
      /* @Trace: IpduM_SUD_API_004 */
      /* Copy only masked bit in first segment byte from source buffer */
      /* polyspace +4 RTE:IDP [Not a defect:Low] "Pointer is not null and inside its bound. This is assured by generator" */
      /* polyspace +3 RTE:NIV [Not a defect:Low] "Variable initialized by calling function" */
      ptrDst[IPDUM_ZERO] = \
        (ptrDst[IPDUM_ZERO] & IpduM_GetTxSegmentFirstByteClrMask(LpSegmentId)) |
        (ptrSrc[IPDUM_ZERO] & IpduM_GetTxSegmentFirstByteSetMask(LpSegmentId));
      /* Change position of next copied byte as 1 */
      bytePos = (uint8)IPDUM_ONE;
    }
    else
    {
      /* No action */
    }
    /* Check if the last Byte Mask is valid */
    if (IPDUM_BYTE_MASK_INVALID != IpduM_GetTxSegmentLastByteSetMask(LpSegmentId))
    {
      /* @Trace: IpduM_SUD_API_005 */
      /* Decrease by 1 for the position of last copied byte */
      noOfByte--;
      /* Copy only masked bit in last segment byte from source buffer */
      /* polyspace +4 RTE:IDP [Not a defect:Low] "Pointer is not null and inside its bound. This is assured by generator" */
      /* polyspace +3 RTE:NIV [Not a defect:Low] "Variable initialized by calling function" */
      ptrDst[noOfByte] = \
        (ptrDst[noOfByte] & IpduM_GetTxSegmentLastByteClrMask(LpSegmentId)) |
        (ptrSrc[noOfByte] & IpduM_GetTxSegmentLastByteSetMask(LpSegmentId));
    }
    else
    {
      /* No action */
    }
    #endif /* (IPDUM_SEGMENT_BITFIELD == STD_ON) */

    /* Loop to copy all remaining bytes */
    while (bytePos < noOfByte)
    {
      /* @Trace: IpduM_SUD_API_006 */
      /* Copy the data into destination buffer from source buffer */
      /* polyspace +2 RTE:IDP [Not a defect:Low] "Pointer is not null and inside its bound. This is assured by generator" */
      /* polyspace +1 RTE:NIV [Not a defect:Low] "Variable initialized by calling function" */
      ptrDst[bytePos] = ptrSrc[bytePos];
      /* Increase byte position copied */
      bytePos++;
    }

    #if (IPDUM_SEGMENT_BITFIELD == STD_ON)
    /* Increment to next Segment Field element */
    ++LpSegmentId;
    /* Decrease the number of remaining segment */
    --LpSegmentSize;


    #endif
        } /* End while ((uint8)IPDUM_ZERO != SegmentSize) */

        /* Exit critical area */
        SchM_Exit_IpduM_DEST_DATA_PROTECTION_AREA();
        IPDUM_UNUSED(LpSegmentSize);
  }
} /* End of IpduM_CopySegments() */
#endif /* (IPDUM_TX_IPDU == STD_ON) */

/*******************************************************************************
** Function Name        : IpduM_GetSelBitField                                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function extracts the selector field value     **
**                        from an I-PDU.                                      **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : Reentrant for different I-PDU                       **
**                                                                            **
** Input Parameters     : SelFieldId                                          **
**                        ByteOrder                                           **
**                        DestPtr                                             **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : selVal                                              **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) : IpduM_SelBitField[]            **
**                                                                            **
**                        Function(s) invoked: None                           **
**                                                                            **
*******************************************************************************/
/* @Trace: SWS_IpduM_00098 SWS_IpduM_00173
 * SRS_IpduM_02809 SRS_IpduM_02801 SRS_IpduM_02802 SRS_IpduM_02803
 */

#if (IPDUM_RX_DYNAMIC_IPDU == STD_ON)
FUNC(uint16, IPDUM_CODE) IpduM_GetSelBitField(
  IpduM_RxMuxIntType SelFieldId, boolean ByteOrder,
  P2CONST(uint8, AUTOMATIC, IPDUM_APPL_DATA) DestPtr)
{
  #if (IPDUM_RX_IPDU_SELFIELD_MAXBYTE == IPDUM_ONE)
  uint16 selVal;

  selVal = (uint16)((uint8)(IpduM_GetRxMuxSelFieldStartByteMask(SelFieldId) & \
            DestPtr[IpduM_GetRxMuxSelFieldBytePos(SelFieldId)])) >>
            IpduM_GetRxMuxSelFieldBitShift(SelFieldId);

  IPDUM_UNUSED(ByteOrder);
  #else /* (IPDUM_RX_IPDU_SELFIELD_MAXBYTE > IPDUM_ONE) */
  uint32 selVal;
  uint8 noOfByte;
  #if (IPDUM_RX_IPDU_BIG_ENDIAN == STD_ON)
  uint8 byteCnt;
  #endif
  uint8 selBuf[IPDUM_RX_IPDU_SELFIELD_MAXBYTE];
  /* polyspace +2 RTE:IDP [Not a defect:Low] "Pointer is not null and inside its bound. This is assured by generator" */
  selBuf[0] = IpduM_GetRxMuxSelFieldStartByteMask(SelFieldId) & \
            DestPtr[IpduM_GetRxMuxSelFieldBytePos(SelFieldId)];
  noOfByte = IpduM_GetRxMuxSelFieldNoOfByte(SelFieldId);

  #if (IPDUM_RX_IPDU_SELFIELD_MAXBYTE == IPDUM_THREE)
  /* Get SelectorField value if located in 3-byte or 2-byte */
  if ((uint8)IPDUM_THREE == noOfByte)
  {
    /* @Trace: IpduM_SUD_API_007 */
    selBuf[1] = DestPtr[IpduM_GetRxMuxSelFieldBytePos(SelFieldId) + IPDUM_ONE];
    selBuf[2] = IpduM_GetRxMuxSelFieldEndByteMask(SelFieldId) & \
                DestPtr[IpduM_GetRxMuxSelFieldBytePos(SelFieldId) + IPDUM_TWO];
  }
  else
  #endif
  {
    /* @Trace: IpduM_SUD_API_008 */
    selBuf[1] = IpduM_GetRxMuxSelFieldEndByteMask(SelFieldId) & \
                DestPtr[IpduM_GetRxMuxSelFieldBytePos(SelFieldId) + IPDUM_ONE];
  }
  /* Inititate Selector Value as zero */
  selVal = (uint32)IPDUM_ZERO;

  #if ((IPDUM_RX_IPDU_LITTLE_ENDIAN == STD_ON) && \
       (IPDUM_RX_IPDU_BIG_ENDIAN == STD_ON))
  if (IPDUM_LITTLE_ENDIAN == ByteOrder)
  #else
    IPDUM_UNUSED(ByteOrder);
  #endif
  {
    #if (IPDUM_RX_IPDU_LITTLE_ENDIAN == STD_ON)
    do
    {
      /* @Trace: IpduM_SUD_API_009 */
      noOfByte--;
      selVal = (selVal << IPDUM_EIGHT) | (uint32)selBuf[noOfByte];
    } while ((uint8)IPDUM_ZERO < noOfByte);
    #endif
  }
  #if ((IPDUM_RX_IPDU_LITTLE_ENDIAN == STD_ON) && \
       (IPDUM_RX_IPDU_BIG_ENDIAN == STD_ON))
  else
  #endif
  {
    #if (IPDUM_RX_IPDU_BIG_ENDIAN == STD_ON)
    byteCnt = (uint8)IPDUM_ZERO;
    do
    {
      /* @Trace: IpduM_SUD_API_010 */
      selVal = (selVal << IPDUM_EIGHT) | (uint32)selBuf[byteCnt];
      byteCnt++;
    } while (noOfByte > byteCnt);
    #endif
  }
  /* Shift the value to make it byte aligned */
  selVal >>= IpduM_GetRxMuxSelFieldBitShift(SelFieldId);
  #endif /* (IPDUM_RX_IPDU_SELFIELD_MAXBYTE > IPDUM_ONE) */

  /* Return Selector bit value */
  return (uint16)selVal;
} /* End of IpduM_GetSelBitField() */
#endif /* (IPDUM_RX_DYNAMIC_IPDU == STD_ON) */

/*******************************************************************************
** Function Name        : IpduM_BinarySearch                                  **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function searches the given selector value in  **
**                        the existing list.                                  **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : RxDynPartId                                         **
**                        Size                                                **
**                        Key                                                 **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : IpduM_RxPartIntType                                 **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) : IpduM_RxMuxDynPartArr[]        **
**                                                                            **
**                        Function(s) invoked: None                           **
**                                                                            **
*******************************************************************************/
/* @Trace: SWS_IpduM_00042
 * SRS_IpduM_02812
 */

#if ((IPDUM_RX_DYNAMIC_IPDU == STD_ON) && (IPDUM_BINARY_SEARCH == STD_ON))
FUNC(IpduM_RxPartIntType, IPDUM_CODE) IpduM_BinarySearch(
  IpduM_RxPartIntType RxDynPartId, IpduM_RxPartIntType Size, uint16 Key)
{
  IpduM_RxPartIntType newDynIdx;
  uint16 selectorVal;
  IpduM_RxPartIntType lowIdx;
  IpduM_RxPartIntType highIdx;
  IpduM_RxPartIntType midIdx;

  /* Set return value as E_NOT_OK */
  newDynIdx = IPDUM_RXPART_INVALID_IDX;
  /* Initialize highIdx variable with number of List I-PDUs - 1 */
  highIdx = RxDynPartId + Size - (IpduM_RxPartIntType)IPDUM_ONE;
  /* Initialize lowIdx variable with one */
  lowIdx = RxDynPartId + (IpduM_RxPartIntType)IPDUM_ONE;
  if ((uint8)IPDUM_RXPART_INVALID_VALUE != RxDynPartId) {
      /* Get the lower limit of Selector Bit Field Value */
      selectorVal = IpduM_GetRxMuxDynSelVal(RxDynPartId);

      if (Key != selectorVal)
      {
        /* @Trace: IpduM_SUD_API_011 */
        /* Check whether search Selector Bit Field Value is in range */
        /* polyspace +1 RTE:OBAI [Not a defect:Low] "Array access index is in-bounds. This is assured by generator" */
        if ((selectorVal < Key) && (IpduM_GetRxMuxDynSelVal(highIdx) >= Key))
        {
          do
          {
            /* @Trace: IpduM_SUD_API_012 */
            /* Get the middle index number */
            midIdx = (highIdx + lowIdx) >> IPDUM_ONE;
            /* Get the Selector Bit Field Value of the midIdx Rx L-PDU */
            selectorVal = IpduM_GetRxMuxDynSelVal(midIdx);

            /* Compare Selector Bit Field Value with the requested one */
            if (Key == selectorVal)
            {
              /* @Trace: IpduM_SUD_API_013 */
              /* Found Dynamic part correlatively */
              newDynIdx = midIdx;
              /* Set highIdx to zero to break the loop */
              highIdx = (IpduM_RxPartIntType)IPDUM_ZERO;
            }
            /* Compare the Selector Bit Field Value with the requested one */
            else if (Key < selectorVal)
            {
              /* @Trace: IpduM_SUD_API_014 */
              /* If the priority is lower, update highIdx */
              highIdx = midIdx - (IpduM_RxPartIntType)IPDUM_ONE;
            } /* End of if (Key <selectorVal) */
            else
            {
              /* @Trace: IpduM_SUD_API_015 */
              /* If the priority is higher, update lowIdx */
              lowIdx = midIdx + (IpduM_RxPartIntType)IPDUM_ONE;
            }
          } while (lowIdx <= highIdx);
        } /* End of checking searched Selector Value in range */
        else
        {
          /* No action */
        }
      } /* End of if (Key != selectorVal) */
      else
      {
        /* @Trace: IpduM_SUD_API_016 */
        /* Dynamic part found as the first one */
        newDynIdx = RxDynPartId;
      }
  }
  return (newDynIdx);
} /* End of IpduM_BinarySearch() */
#endif /*((IPDUM_RX_DYNAMIC_IPDU == STD_ON)&&(IPDUM_BINARY_SEARCH == STD_ON)) */

/*******************************************************************************
** Function Name        : IpduM_LinearSearch                                  **
**                                                                            **
** Service ID           : Not applicable                                      **
**                                                                            **
** Description          : This function searches the given selector value in  **
**                        the existing list.                                  **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : Reentrant but not for same Ipdu                     **
**                                                                            **
** Input Parameters     : RxDynPartId                                         **
**                        Size                                                **
**                        Key                                                 **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : IpduM_RxPartIntType                                 **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) : IpduM_RxMuxDynPartArr[]        **
**                                                                            **
**                        Function(s) invoked: None                           **
**                                                                            **
*******************************************************************************/
/* @Trace: SWS_IpduM_00042
 * SRS_IpduM_02812
 */

#if ((IPDUM_RX_DYNAMIC_IPDU == STD_ON) && (IPDUM_LINEAR_SEARCH == STD_ON))
FUNC(IpduM_RxPartIntType, IPDUM_CODE) IpduM_LinearSearch(
  IpduM_RxPartIntType RxDynPartId, IpduM_RxPartIntType Size, uint16 Key)
{
  
  IpduM_RxPartIntType newDynIdx;
  IpduM_RxPartIntType LpRxDynPartId = RxDynPartId;
  IpduM_RxPartIntType LpSize = Size;
  /* Initiate index as "invalid value" */
  newDynIdx = IPDUM_RXPART_INVALID_IDX;
  if ((uint8)IPDUM_RXPART_INVALID_VALUE != LpRxDynPartId) 
  {
    /* Loop all the Rx L-PDUs for the requested CAN ID */
    do
    {
      /* @Trace: IpduM_SUD_API_017 */
      /* Check if searched Selector Value is matched */
    if (IpduM_GetRxMuxDynSelVal(LpRxDynPartId) == Key)
      {
        /* @Trace: IpduM_SUD_API_018 */
        /* Found dynamic part correlatively */
        newDynIdx = LpRxDynPartId;
        /* Reset Size to break the loop */
        LpSize = (IpduM_RxPartIntType)IPDUM_ONE;
      }
      else
      {
        /* @Trace: IpduM_SUD_API_019 */
        /* Increase index to next dynamic part */
        LpRxDynPartId++;
      }
      /* Decrement the size */
      LpSize--;
    } while ((IpduM_RxPartIntType)IPDUM_ZERO != LpSize);
  }
  return (newDynIdx);
} /* End of IpduM_LinearSearch() */
#endif /*((IPDUM_RX_DYNAMIC_IPDU == STD_ON)&&(IPDUM_LINEAR_SEARCH == STD_ON)) */

/*******************************************************************************
** Function Name        : IpduM_FetchTxMuxIpduPart                            **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is called by the update one of part   **
**                        of multiplexed ipdu from upper layer                **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Re-entrant for the same PDU-ID. Re-entrant for  **
**                        different PDU-ID.                                   **
**                                                                            **
** Input Parameters     : PduIdType TxPduId,                                  **
**                        const PduInfoType *PduInfoPtr                       **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) : IpduM_TxInIpdu[]               **
**                                                                            **
**                        Function(s) invoked: Com_TriggerTransmit()          **
**                                             PduR_IpduMTriggerTransmit()    **
**                                             IpduM_CopySegments()           **
**                                                                            **
*******************************************************************************/
/* @Trace: SWS_IpduM_00168 SWS_IpduM_00169 SWS_IpduM_00171 SWS_IpduM_00172
 * SWS_IpduM_00223
 * SRS_IpduM_02811 SRS_IpduM_02816
 */

#if (IPDUM_TX_IPDU == STD_ON)
FUNC(Std_ReturnType, IPDUM_CODE) IpduM_FetchTxMuxIpduPart(
  IpduM_TxPartIntType TxInIpduId)
{
  /*Local structure of PduInfoType */
  PduInfoType pduInfo;
  /* Local variable point to PduInfoPtr */
  P2VAR(PduInfoType, AUTOMATIC, IPDUM_VAR) ptrPduInfo;
  /* Temporal buffer */
  uint8 sduDataBuff[IPDUM_MAX_TX_IPDU_LENGTH];

  /* Local variable for return value*/
  Std_ReturnType retVal;

  ptrPduInfo = &pduInfo;
  ptrPduInfo->SduDataPtr = &sduDataBuff[IPDUM_ZERO];
  ptrPduInfo->SduLength = IPDUM_MAX_TX_IPDU_LENGTH;

  /* Invoke the trigger transmit function */
  /* polyspace-begin CERT-C:DCL39-C [Not a defect: Justified] "PduInfoType: Type of PduInfoPtr is defined by Autosar, it can not be modified. No impact" */
  retVal = IpduM_UpTriggerTxFunc(IpduM_GetTxPartConfRefPduId(TxInIpduId), ptrPduInfo);
  /* polyspace-end CERT-C:DCL39-C [Not a defect: Justified] "PduInfoType: Type of PduInfoPtr is defined by Autosar, it can not be modified. No impact" */

  /* Check if fetch data via TriggerTransmit returns E_OK */
  if (E_OK == retVal)
  {
    /* @Trace: IpduM_SUD_API_020 */
    /* Multiplex the updated part by Copying the data into static or
     *   dynamic part 2nd part
     */
    /* Copy data in bit of static or dynamic I-PDUs into buffer */
    IpduM_CopySegments(IpduM_GetTxSegmentIdx(TxInIpduId),
        ptrPduInfo->SduDataPtr, IpduM_GetTxNoOfSegment(TxInIpduId));
  }
  else
  {
    /* No action */
  }
  return (retVal);
} /* End of IpduM_FetchTxMuxIpduPart() */
#endif /* (IPDUM_JIT_UPDATE == STD_ON) */

/*******************************************************************************
** Function Name        : IpduM_DetCheckFuncs                                 **
**                                                                            **
** Service ID           : Not applicable                                      **
**                                                                            **
** Description          : This function performs NULL pointer check on        **
**                        PduInfoPtr and reports DET.                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : ApiId                                               **
**                        CheckedId                                           **
**                        MaxId                                               **
**                        PduInfoPtr                                          **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : uint8                                               **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) : IpduM_InitStatus               **
**                                                                            **
**                        Function(s) invoked: Det_ReportError()              **
**                                                                            **
*******************************************************************************/
/* @Trace: SWS_IpduM_00026 SWS_IpduM_00153 SWS_IpduM_00162 SWS_IpduM_00174
 * SRS_BSW_00337 SRS_BSW_00414
 */

#if (IPDUM_DEV_ERROR_DETECT == STD_ON)
FUNC(uint8, IPDUM_CODE) IpduM_DetCheckFuncs(
  uint8 ApiId, PduIdType CheckedId, PduIdType MaxId,
  P2CONST(PduInfoType, AUTOMATIC, IPDUM_APPL_DATA) PduInfoPtr)
{
  uint8 errorId;

  /* Check if module not initialized yet */
  if (IPDUM_UNINIT == IpduM_InitStatus)
  {
    /* @Trace: IpduM_SUD_API_021 */
    errorId = IPDUM_E_UNINIT;
  }
  /* Check PduId is greater than maximum configured PduId */
  else if (MaxId < CheckedId)
  {
    /* @Trace: IpduM_SUD_API_022 */
    errorId = IPDUM_E_PARAM;
  }
  /* Check if PduInfoPtr is NULL Pointer */
  /* polyspace-end MISRA-C3:D4.14 [Justified:Low] "This ptr can not enter in state of NULL" */
  else if ((IPDUM_TXCONFIRMATION_SID != ApiId) && \
    ((PduInfoPtr == NULL_PTR) || (PduInfoPtr->SduDataPtr == NULL_PTR)))
  {
    /* @Trace: IpduM_SUD_API_023 */
    errorId = IPDUM_E_PARAM_POINTER;
  }
  else
  {
    /* @Trace: IpduM_SUD_API_024 */
    errorId = IPDUM_E_NO_ERROR;
  }

  if (IPDUM_E_NO_ERROR != errorId)
  {
    /* @Trace: IpduM_SUD_API_025 */
    /* Report to DET */
    (void)Det_ReportError((uint16)IPDUM_MODULE_ID, IPDUM_INSTANCE_ID,
                          ApiId, errorId);
  }
  return (errorId);
}
#endif /* (IPDUM_DEV_ERROR_DETECT == STD_ON) */

/*******************************************************************************
** Function Name        : IpduM_InitMux                                       **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function initiates for all configured          **
**                        TxPathway and RxPathway                             **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
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
** Remarks              : Global Variable(s) : IpduM_TxOutIpdu[]              **
**                                             IpduM_TxConfDynPartMapArray[]  **
**                                             IpduM_JitDynPartMapArray[]     **
**                                                                            **
**                        Function(s) invoked: IpduM_SetData()                **
**                                             IpduM_FetchTxMuxIpduPart()     **
**                                                                            **
*******************************************************************************/
/* @Trace: SWS_IpduM_00067 SWS_IpduM_00068 SWS_IpduM_000143
 * SRS_IpduM_02809
 */
#if (IPDUM_TX_IPDU == STD_ON)
FUNC(void, IPDUM_CODE) IpduM_InitMux(void)
{
  IpduM_TxMuxIntType txOutId;
  IpduM_TxPartIntType dynPartId;
  #if (IPDUM_JIT_UPDATE == STD_ON)
  IpduM_TxPartIntType jitIdx;
  #endif

  txOutId = (IpduM_TxMuxIntType)IPDUM_ZERO;
  /* Initiate all configured TxPathway */
  while ((IpduM_TxMuxIntType)IPDUM_NO_OF_TX_PATHWAYS > txOutId)
  {
    /* @Trace: IpduM_SUD_API_026 */
    /* Fills not used areas of an I-PDU with this byte-pattern */
    /* polyspace +1 RTE:IDP [Not a defect:Low] "Pointer is not null and inside its bound. This is assured by generator" */
    IpduM_SetData(IpduM_GetAddrBufOfTxMux(txOutId),
        IpduM_GetTxMuxDefaultVal(txOutId), IpduM_GetLengthBufOfTxMux(txOutId));
    #if (IPDUM_META_DATA_SUPPORT == STD_ON)
      /* @Trace: IpduM_SUD_API_027 */
      /* Fills not used areas of an I-PDU metadata with this byte-pattern */
      IpduM_SetData(IpduM_GetAddrMetaDataBufOfTxMux(txOutId),
                    IpduM_GetTxMuxDefaultVal(txOutId),
                    IpduM_GetLengthMetaDataOfTxMux(txOutId));
    #endif

    #if (IPDUM_TX_STATIC_IPDU == STD_ON)
    /* Check if Static part contained in multiplexed I-PDU */
    if (IPDUM_TXPART_INVALID_IDX != IpduM_GetTxMuxStaticPartIdx(txOutId))
    {
      /* @Trace: IpduM_SUD_API_028 */
      /* Fetch initial signal values of Static part */
      (void)IpduM_FetchTxMuxIpduPart(IpduM_GetTxMuxStaticPartIdx(txOutId));
    }
    else
    {
      /* No action */
    }
    #endif /* #if (IPDUM_TX_STATIC_IPDU == STD_ON)) */
      /* @Trace: IpduM_SUD_API_029 */
    dynPartId = IpduM_GetTxMuxInitDynPart(txOutId);
    /* Fetch initial signal values of Dynamic part */
    (void)IpduM_FetchTxMuxIpduPart(dynPartId);

    #if (IPDUM_TX_CONF_IPDU == STD_ON)
    if (FALSE != IpduM_IsTxMuxConfEnabled(txOutId))
    {
      /* @Trace: IpduM_SUD_API_030 */
      /* Initiate the index for Tx Confirmation of Dynamic part */
      IpduM_SetTxMuxConfDynPart((IpduM_GetIdxOfConfDynTxPartBuf(txOutId)), dynPartId);
      /* Initiate Tx Confirmation Pending Flag to zero */
      IpduM_ClearTxConfPendingFlag(
                         (IpduM_GetTxMuxByteIdxOfConfPendingFlagBuf(txOutId)),
                         (IpduM_GetTxMuxByteMaskOfConfPendingFlagBuf(txOutId)));
    }
    else
    {
      /* No action */
    }
    #endif /* (IPDUM_TX_CONF_IPDU == STD_ON) */

    #if (IPDUM_JIT_UPDATE == STD_ON)
     /* @Trace: IpduM_SUD_API_031 */
    jitIdx = IpduM_GetIdxOfJITDynTxPartBuf(txOutId);
    if (IPDUM_TXPART_INVALID_IDX != jitIdx)
    {
      /* @Trace: IpduM_SUD_API_032 */
      /* Initiate the index for JIT-update of Dynamic part */
      IpduM_SetTxMuxJITDynPart(jitIdx, dynPartId);
    }
    else
    {
      /* No action */
    }
    #endif /* (IPDUM_JIT_UPDATE == STD_ON) */

    /* Increase getting index of next TxPathway */
    ++txOutId;
  } /* End of while ((IpduM_TxPartIntType)IPDUM_NO_OF_TX_PATHWAYS != txOutId) */
} /* End of IpduM_InitMux() */
#endif /* (IPDUM_TX_IPDU == STD_ON) */

/*******************************************************************************
** Function Name        : IpduM_TxIpduMux                                     **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : This function is called for processing the          **
**                        transmission request of multiplexed I-PDU           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant for different PDU-ID.                    **
**                                                                            **
** Input Parameters     : PduInfoPtr - Length of and pointer to the PDU data  **
**                                     and pointer to MetaData                **
**                        TxInIpduPtr - Pointer to Tx In Ipdu structure       **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : E_OK - Transmit request has been accepted           **
**                        E_NOT_OK - Transmit request has not been accepted   **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) : IpduM_TxInIpdu[]               **
**                                             IpduM_TxOutIpdu[]              **
**                                             IpduM_JitDynPartMapArray[]     **
**                                                                            **
**                        Function(s) invoked: IpduM_CopyData()               **
**                                             IpduM_FetchTxMuxIpduPart()     **
**                                             PduR_IpduMTransmit()           **
**                                             IpduM_CopySegments()           **
**                        SchM_Enter_IpduM_TX_STATUS_PROTECTION_AREA()        **
**                        SchM_Exit_IpduM_TX_STATUS_PROTECTION_AREA()         **
**                                                                            **
*******************************************************************************/
/* @Trace: SWS_IpduM_00015 SWS_IpduM_00017 SWS_IpduM_00152 SWS_IpduM_00225
 * SWS_IpduM_00226
 * SRS_IpduM_02816 SRS_IpduM_02814
 */

#if (IPDUM_TX_IPDU == STD_ON)
FUNC(Std_ReturnType, IPDUM_CODE) IpduM_TxIpduMux(
  IpduM_TxPartIntType TxInIpduId,
  P2CONST(PduInfoType, AUTOMATIC, IPDUM_APPL_DATA) PduInfoPtr)
{
  IpduM_TxPartIntType TxOutIpduId;
  /* Local variable for return value*/
  Std_ReturnType retVal;
  /* Flag of enabling trigger transmission */
  boolean triggerFlag;
  #if ((IPDUM_TX_STATIC_IPDU == STD_ON) && (IPDUM_JIT_UPDATE == STD_ON))
  /* Mapping index of second part in Tx In Ipdu array */
  /* @Trace: IpduM_SUD_API_033 */
  IpduM_TxPartIntType jitIdx;
  #endif
  /* Temporal storing of Dynamic part index in Tx In Ipdu array */
  IpduM_TxPartIntType dynPartIdx;
  IpduM_TxPartIntType secPartIdx;
  #if (IPDUM_TX_CONF_IPDU == STD_ON)
  /* @Trace: IpduM_SUD_API_034 */
  IpduM_TxConfIntType confIdx;
  uint8 confMask;
  uint8 confFlag;
  #endif

  /* Initiate as invalid index */
  /* @Trace: IpduM_SUD_API_035 */
  dynPartIdx = IPDUM_TXPART_INVALID_IDX;
  secPartIdx = IPDUM_TXPART_INVALID_IDX;
  /* Get Tx Multiplexed I-PDU index corresponding */
  TxOutIpduId = IpduM_GetTxMuxIpduFromPartIpdu(TxInIpduId);

  /* Check whether previous transmission is not pending for confirmation */
  #if (IPDUM_TX_CONF_IPDU == STD_ON)
  /* @Trace: IpduM_SUD_API_036 */
  SchM_Enter_IpduM_TX_STATUS_PROTECTION_AREA();
  confIdx = IpduM_GetTxMuxByteIdxOfConfPendingFlagBuf(TxOutIpduId);
  confMask = IpduM_GetTxMuxByteMaskOfConfPendingFlagBuf(TxOutIpduId);
  confFlag = IpduM_GetTxConfPendingFlag(confIdx, confMask);
  SchM_Exit_IpduM_TX_STATUS_PROTECTION_AREA();
  
  if ((FALSE == IpduM_IsTxMuxConfEnabled(TxOutIpduId)) ||
        ((uint8)IPDUM_ZERO == confFlag))
  #endif
  {
    #if (IPDUM_TX_STATIC_IPDU == STD_ON)
    /* Check if Tx request for static part */
    if (FALSE == IpduM_IsTxReqForDynamicPart(TxInIpduId))
    {
      /* @Trace: IpduM_SUD_API_038 */
      /* Get flag whether receiving static part trigger the transmission */
      triggerFlag = IpduM_IsTxMuxSentByReceivingStaticPart(TxOutIpduId);
      #if (IPDUM_JIT_UPDATE == STD_ON)
      if (FALSE != triggerFlag)
      {
        /* Get index of dynamic part from JIT update store if trigger */
        if (IPDUM_TXPART_INVALID_IDX != IpduM_GetIdxOfJITDynTxPartBuf(TxOutIpduId))
        {
          /* @Trace: IpduM_SUD_API_039 */
          secPartIdx = IpduM_GetTxMuxJITDynPartIdx(
                                  (IpduM_GetIdxOfJITDynTxPartBuf(TxOutIpduId)));
        }
        else
        {
          /* @Trace: IpduM_SUD_API_040 */
          secPartIdx = IPDUM_TXPART_INVALID_IDX;
        }
          /* @Trace: IpduM_SUD_API_041 */
        dynPartIdx = secPartIdx;
      }
      else
      {
        /* No action */
      }
      #endif
    }  /* End of checking Tx request for static part */
    /* Tx request for dynamic part */
    else
    #endif
    {
      /* @Trace: IpduM_SUD_API_042 */
      #if (IPDUM_JIT_UPDATE == STD_ON)
      jitIdx = IpduM_GetIdxOfJITDynTxPartBuf(TxOutIpduId);
      if (IPDUM_TXPART_INVALID_IDX != jitIdx)
      {
        /* @Trace: IpduM_SUD_API_043 */
        /* Store the last latest dynamic part sent by the upper layer */
        IpduM_SetTxMuxJITDynPart(jitIdx, TxInIpduId);
      }
      else
      {
        /* No action */
      }
      #endif /* (IPDUM_JIT_UPDATE == STD_ON) */
      /* Get flag whether receiving dynamic part trigger the transmission */
      /* @Trace: IpduM_SUD_API_044 */
      triggerFlag = IpduM_IsTxMuxSentByReceivingDynamicPart(TxOutIpduId);
      if (FALSE != triggerFlag)
      {
        /* @Trace: IpduM_SUD_API_045 */
        /* Store index of last dynamic part temporarily */
        dynPartIdx = TxInIpduId;

        #if ((IPDUM_TX_STATIC_IPDU == STD_ON) && (IPDUM_JIT_UPDATE == STD_ON))
          /* @Trace: IpduM_SUD_API_046 */
        secPartIdx = IpduM_GetTxMuxStaticPartIdx(TxOutIpduId);
        #endif
      }
      else
      {
        /* No action */
      }
    } /* End of checking Tx request for dynamic part */
    /* Copy data Tx static or dynamic I-PDUs into buffer */
      /* @Trace: IpduM_SUD_API_047 */
    /* polyspace-end MISRA-C3:D4.14 [Justified:Low] "This ptr can not enter in state of NULL" */
    IpduM_CopySegments(IpduM_GetTxSegmentIdx(TxInIpduId),
                    PduInfoPtr->SduDataPtr, IpduM_GetTxNoOfSegment(TxInIpduId));
    #if (IPDUM_META_DATA_SUPPORT == STD_ON)
    /*
     * IpduM shall use the MetaData of the triggering part or the last updated
     * part when IpduMTxTriggerMode is configured to NONE.
     */
    if ((NULL_PTR != PduInfoPtr->MetaDataPtr) &&
      ((FALSE != triggerFlag) ||
      (IPDUM_TX_IPDU_TRIGGER_NONE == IpduM_GetTxMuxTriggerMode(TxOutIpduId))))
    {
      /* @Trace: IpduM_SUD_API_048 */
      SchM_Enter_IpduM_DEST_DATA_PROTECTION_AREA();
      /* Copy metadata into buffer */
      /* polyspace +2 RTE:IDP [Not a defect:Low] "Pointer is not null and inside its bound. This is assured by generator" */
        IpduM_CopyData(PduInfoPtr->MetaDataPtr,
                     IpduM_GetAddrMetaDataBufOfTxMux(TxOutIpduId),
                     IpduM_GetLengthMetaDataOfTxMux(TxOutIpduId));
      SchM_Exit_IpduM_DEST_DATA_PROTECTION_AREA();
    }
    else
    {
      /* No action */
    }
    #endif /* (IPDUM_META_DATA_SUPPORT == STD_ON) */

    /* @Trace: IpduM_SUD_API_400 */
    retVal = IpduM_StoreDynIndAndUpdrJIT(triggerFlag, secPartIdx, dynPartIdx, TxOutIpduId);

  } /* End of if TxPendingFlagPtr is not set */
  #if (IPDUM_TX_CONF_IPDU == STD_ON)
  else
  {
    /* @Trace: IpduM_SUD_API_053 */
    /* Set return value as not ok */
    retVal = E_NOT_OK;
  }
  #endif
  /* @Trace: IpduM_SUD_API_054 */
  return retVal;
} /* End of IpduM_TxIpduMux() */
#endif /* #if (IPDUM_TX_IPDU == STD_ON) */

/*******************************************************************************
** Function Name        : IpduM_TriggerTxIpduMux                              **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : This function is called for processing in case the  **
**                        contents of a multiplexed I-PDU is requested via    **
**                        IpduM_TriggerTransmit                               **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant for different PDU-ID.                    **
**                                                                            **
** Input Parameters     : PduInfoPtr - Length of and pointer to the PDU data  **
**                                     and pointer to MetaData                **
**                        TxOutIpduPtr - Pointer to Tx Out Ipdu structure     **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : E_OK - SDU has been copied and SduLength indicates  **
**                               the number of copied bytes.                  **
**                        E_NOT_OK - No SDU data has been copied              **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : IpduM_TxInIpdu[]           **
**                                                                            **
**                        Function(s) invoked    : IpduM_CopyData()           **
**                                                 IpduM_FetchTxMuxIpduPart() **
**                                                                            **
*******************************************************************************/
/* @Trace: SWS_IpduM_00021 SWS_IpduM_00022 SWS_IpduM_00089 SWS_IpduM_00090
 * SWS_IpduM_00091 SWS_IpduM_00140
 * SRS_IpduM_02811 SRS_IpduM_02813 SRS_IpduM_02818 SRS_IpduM_02810
 * SRS_IpduM_02812
 */

#if (IPDUM_TX_IPDU == STD_ON)
FUNC(Std_ReturnType, IPDUM_CODE) IpduM_TriggerTxIpduMux(
  IpduM_TxConfIntType TxOutIpduId,
  P2VAR(PduInfoType, AUTOMATIC, IPDUM_APPL_DATA) PduInfoPtr)
{
  /* Local variable for return value */
  Std_ReturnType retVal;
  IpduM_TxPartIntType txPartId = 0;

  #if (IPDUM_TX_CONF_IPDU == STD_ON)
  IpduM_TxConfIntType confIdx;
  uint8 confMask;
  #endif /* (IPDUM_TX_CONF_IPDU == STD_ON) */
  /* @Trace: IpduM_SUD_API_055 */
  /* Initiate return value as "ok" */
  retVal = E_OK;
  /*
   * Trigger Transmit for latest dynamic part that sent by the upper layer.
   * If no dynamic part was sent before, use the dynamic part
   * referenced by IpduMInitialDynamicPart.
   */
  #if (IPDUM_JIT_UPDATE == STD_ON)
  /* Get index of latest dynamic part in array Tx In Ipdu sent by upper layer */
  if (IPDUM_TXPART_INVALID_IDX != IpduM_GetIdxOfJITDynTxPartBuf(TxOutIpduId))
  {
    /* @Trace: IpduM_SUD_API_056 */
    /* Get index of dynamic part from JIT update store if trigger */
    txPartId = IpduM_GetTxMuxJITDynPartIdx(
                                  (IpduM_GetIdxOfJITDynTxPartBuf(TxOutIpduId)));
    /* Check if JIT-update of dynamic part is enabled */
    /* polyspace +2 RTE:OBAI [Not a defect:Low] "Array access index is in-bounds. This is assured by generator" */
    /* polyspace +1 RTE:IDP [Not a defect:Low] "Pointer is not null and inside its bound. This is assured by generator" */
	if ((FALSE != IpduM_IsTxPartJITRequired(txPartId)))
    {
      /* @Trace: IpduM_SUD_API_057 */
      /* JIT-update of Dynamic part */
      retVal = IpduM_FetchTxMuxIpduPart(txPartId);
    }
    else
    {
      /* No action */
    }
  }
  else
  {
    /* No action */
  }

  #if (IPDUM_TX_STATIC_IPDU == STD_ON)
    /* @Trace: IpduM_SUD_API_058 */
  txPartId = IpduM_GetTxMuxStaticPartIdx(TxOutIpduId);
  /* Check if static part is included in I-PDU */
  if ((E_OK == retVal) && (IPDUM_TXPART_INVALID_IDX != txPartId))
  {
    /* Check if JIT-update of static part is enabled */
    if (FALSE != IpduM_IsTxPartJITRequired(txPartId))
    {
      /* JIT-update of static part */
      /* @Trace: IpduM_SUD_API_059 */
      retVal = IpduM_FetchTxMuxIpduPart(txPartId);
    }
    else
    {
      /* No action */
    }
  }
  else
  {
    /* No action */
  }
  #endif /* (IPDUM_TX_STATIC_IPDU == STD_ON) */

  /* Check if no failure occurred */
  if (E_OK == retVal)
  #endif /* (IPDUM_JIT_UPDATE == STD_ON) */
  {
    /* Check if SduData can fit to buffer size reported by SduLength */
    /* polyspace +1 RTE:IDP [Not a defect:Low] "Pointer is not null and inside its bound. This is assured by generator" */
	if (IpduM_GetLengthBufOfTxMux(TxOutIpduId) <= PduInfoPtr->SduLength)
    {
      /* @Trace: IpduM_SUD_API_060 */
      /* Update length of actual copied data */
      PduInfoPtr->SduLength = IpduM_GetLengthBufOfTxMux(TxOutIpduId);

      SchM_Enter_IpduM_DEST_DATA_PROTECTION_AREA();
      /* Copy SduData into buffer provided by SduDataPtr */
      IpduM_CopyData(IpduM_GetAddrBufOfTxMux(TxOutIpduId),
                     PduInfoPtr->SduDataPtr, PduInfoPtr->SduLength);
      SchM_Exit_IpduM_DEST_DATA_PROTECTION_AREA();

      #if ((IPDUM_META_DATA_SUPPORT == STD_ON) || \
                                                (IPDUM_TX_CONF_IPDU == STD_ON))
      /* Check if MetaData buffer is provided and TriggerMode is NONE */
      if (IPDUM_TX_IPDU_TRIGGER_NONE == IpduM_GetTxMuxTriggerMode(TxOutIpduId))
      {
        #if (IPDUM_META_DATA_SUPPORT == STD_ON)
        if (NULL_PTR != PduInfoPtr->MetaDataPtr)
        {
          /* @Trace: IpduM_SUD_API_061 */
          SchM_Enter_IpduM_DEST_DATA_PROTECTION_AREA();
          /* Copy MetaData into buffer provided by MetaDataPtr */
          IpduM_CopyData(IpduM_GetAddrMetaDataBufOfTxMux(TxOutIpduId),
                         PduInfoPtr->MetaDataPtr,
                         IpduM_GetLengthMetaDataOfTxMux(TxOutIpduId));
          SchM_Exit_IpduM_DEST_DATA_PROTECTION_AREA();
        }
        else
        {
          /* No action */
        }
        #endif /* (IPDUM_META_DATA_SUPPORT == STD_ON) */

        #if (IPDUM_TX_CONF_IPDU == STD_ON)
        /* Check whether Tx confirmation is enable and pending */
        /* @Trace: IpduM_SUD_API_062 */
        confIdx = IpduM_GetTxMuxByteIdxOfConfPendingFlagBuf(TxOutIpduId);
        confMask = IpduM_GetTxMuxByteMaskOfConfPendingFlagBuf(TxOutIpduId);

        /* Check the condition of setting Tx Confirmation is satisfied */
        if (FALSE != IpduM_IsTxMuxConfEnabled(TxOutIpduId))
        {
          /* @Trace: IpduM_SUD_API_063 */
          IpduM_SetTxConfPendingFlag(confIdx, confMask);
        }
        else
        {
          /* No action */
        }
        #endif
      }
      else
      {
        /* No action */
      }
      #endif
    }
    else
    {
      /* @Trace: IpduM_SUD_API_064 */
      /* Return E_NOT_OK as no SDU data has been copied */
      retVal = E_NOT_OK;
    }
  }
  #if (IPDUM_JIT_UPDATE == STD_OFF)
    /* @Trace: IpduM_SUD_API_065 */
    IPDUM_UNUSED(txPartId);
  #endif
  /* @Trace: IpduM_SUD_API_066 */
  return (retVal);
} /* End of IpduM_TriggerTxIpduMux() */
#endif /* (IPDUM_TX_IPDU == STD_ON) */

/*******************************************************************************
** Function Name        : IpduM_TxConfirmIpduMux                              **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : This function is called for translating a specific  **
**                        multiplexed I-PDU confirmation into the             **
**                        corresponding confirmations for the COM I-PDUs      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant for different PDU-ID.                    **
**                                                                            **
** Input Parameters     : result - Result of the PDU transmission             **
**                        TxOutIpduPtr - Pointer to Tx Out Ipdu structure     **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : IpduM_TxInIpdu[]           **
**                                                                            **
**                        Function(s) invoked    : IpduM_CopyData()           **
**                                                 Com_TxConfirmation()       **
**                                                 PduR_IpduMTxConfirmation() **
**                        SchM_Enter_IpduM_TX_STATUS_PROTECTION_AREA()        **
**                        SchM_Exit_IpduM_TX_STATUS_PROTECTION_AREA()         **
**                                                                            **
*******************************************************************************/
/* @Trace: SWS_IpduM_00022 SWS_IpduM_00087 SWS_IpduM_00088 SWS_IpduM_00140
 * SRS_IpduM_02813 SRS_IpduM_02818 SRS_IpduM_02814 SRS_IpduM_02812
 */

#if (IPDUM_TX_CONF_IPDU == STD_ON)
FUNC(void, IPDUM_CODE) IpduM_TxConfirmIpduMux(
  IpduM_TxConfIntType TxOutIpduId, Std_ReturnType result)
{
  IpduM_TxPartIntType txPartId;
  IpduM_TxConfIntType confIdx;
  uint8 confMask;
  uint8 confFlag;
  /* Check whether Tx confirmation is enable and pending */
  /* @Trace: IpduM_SUD_API_067 */
  /* Enter critical area */
  SchM_Enter_IpduM_TX_STATUS_PROTECTION_AREA();
  confIdx = IpduM_GetTxMuxByteIdxOfConfPendingFlagBuf(TxOutIpduId);
  confMask = IpduM_GetTxMuxByteMaskOfConfPendingFlagBuf(TxOutIpduId);
  confFlag = IpduM_GetTxConfPendingFlag(confIdx, confMask);
  SchM_Exit_IpduM_TX_STATUS_PROTECTION_AREA();

  /* Check whether Tx confirmation is enable and pending */
  if ((FALSE != IpduM_IsTxMuxConfEnabled(TxOutIpduId)) &&
      ((uint8)IPDUM_ZERO != confFlag))

  {
    /* @Trace: IpduM_SUD_API_068 */
    /*
     * TxConfirmation for static and dynamic part in array Tx In Ipdu that
     * contained in multiplexed IPDU and latest send out by upper layer.
     */

    /* Get index of dynamic part contained in last sent out I-PDU */

    /* polyspace +2 RTE:OBAI [Not a defect:Low] "Array access index is in-bounds. This is assured by generator" */
    /* polyspace +1 RTE:IDP [Not a defect:Low] "Pointer is not null and inside its bound. This is assured by generator" */
    SchM_Enter_IpduM_TX_STATUS_PROTECTION_AREA();
    txPartId = IpduM_GetTxMuxConfDynPart((IpduM_GetIdxOfConfDynTxPartBuf(TxOutIpduId)));
    SchM_Exit_IpduM_TX_STATUS_PROTECTION_AREA();

    /* Check if confirmation of dynamic part is required */
    /* polyspace +2 RTE:OBAI [Not a defect:Low] "Array access index is in-bounds. This is assured by generator" */
    /* polyspace +1 RTE:IDP [Not a defect:Low] "Pointer is not null and inside its bound. This is assured by generator" */
    if (FALSE != IpduM_IsTxPartConfRequired(txPartId))
    {
      /* @Trace: IpduM_SUD_API_069 */
      /* Generate TxConfirm for static or dynamic part */
      IpduM_UpTxConfFunc(IpduM_GetTxPartConfRefPduId(txPartId), result);
    }
    else
    {
      /* No action */
    }

    #if (IPDUM_TX_STATIC_IPDU == STD_ON)
      /* @Trace: IpduM_SUD_API_070 */
    txPartId = IpduM_GetTxMuxStaticPartIdx(TxOutIpduId);
    /* Check if static part contained in I-PDU */
    if (IPDUM_TXPART_INVALID_IDX != txPartId)
    {
      /* Check if confirmation of static part is required */
      if (FALSE != IpduM_IsTxPartConfRequired(txPartId))
      {
        /* @Trace: IpduM_SUD_API_071 */
        /* Generate TxConfirm for static part */
        IpduM_UpTxConfFunc(IpduM_GetTxPartConfRefPduId(txPartId), result);
      }
      else
      {
        /* no action */
      }
    }
    else
    {
      /* No action */
    }
    #endif
    /* @Trace: IpduM_SUD_API_072 */
    /* Reset pending flag */
    IpduM_ClearTxConfPendingFlag(confIdx, confMask);
  }
  else
  {
    /* No action */
  }
} /* End of IpduM_TxConfirmIpduMux() */
#endif /* (IPDUM_TX_CONF_IPDU == STD_ON) */

/*******************************************************************************
** Function Name        : IpduM_RxIpduMux                                     **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : This function generates Rx Indication for dynamic   **
**                        I-PDUs and static I-PDU (if configured)             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant for different PDU-ID.                    **
**                                                                            **
** Input Parameters     : PduInfoPtr - Length of and pointer to the PDU data  **
**                                     and pointer to MetaData                **
**                        RxIpduInfoPtr - Pointer to Rx Ipdu structure        **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : IpduM_RxSegmentField[]     **
**                                                                            **
**                        Function(s) invoked    : IpduM_GetSelBitField()     **
**                                                 IpduM_BinarySearch()       **
**                                                 IpduM_LinearSearch()       **
**                                                 Com_RxIndication()         **
**                                                 PduR_IpduMRxIndication()   **
**                                                                            **
*******************************************************************************/
/* @Trace: SWS_IpduM_00041 SWS_IpduM_00042 SWS_IpduM_00086 SWS_IpduM_00227
 * SWS_IpduM_00140
 * SRS_IpduM_02812 SRS_IpduM_02817
 */

#if (IPDUM_RX_IPDU == STD_ON)
FUNC(void, IPDUM_CODE) IpduM_RxIpduMux(
  IpduM_RxMuxIntType RxIpduId,
  P2CONST(PduInfoType, AUTOMATIC, IPDUM_APPL_DATA) PduInfoPtr)
{
  #if (IPDUM_RX_DYNAMIC_IPDU == STD_ON)
  /* Local variable to store Selector value */
  uint16 selVal;
  IpduM_RxPartIntType dynPartCnt;
  IpduM_RxPartIntType dynPartIdx;
  #endif

  #if (IPDUM_RX_STATIC_IPDU == STD_ON)
  if (FALSE != IpduM_IsRxMuxStaticPartExist(RxIpduId))
  {
    /* @Trace: IpduM_SUD_API_334 */
    /* Indicates Rx Static Part to upper layer */
    IpduM_UpRxIndFunc(IpduM_GetRxMuxStaticRefPduId(RxIpduId), PduInfoPtr);
  }
  else
  {
    /* No action */
  }
  #endif

  #if (IPDUM_RX_DYNAMIC_IPDU == STD_ON)
    /* @Trace: IpduM_SUD_API_073 */
  dynPartCnt = IpduM_GetRxMuxNoOfDynPart(RxIpduId);

  #if (IPDUM_CHECK_NO_OF_DYN_RX_IND_IPDU_IS_ZERO == STD_ON)
  /* Check if existing Rx Dynamic part */
  if ((IpduM_RxPartIntType)IPDUM_ZERO < dynPartCnt)
  {
  #endif
  /* @Trace: IpduM_SUD_API_074 */
    /* Get and store the Sel Bit value */
    selVal = IpduM_GetSelBitField(IpduM_GetRxMuxSelField(RxIpduId),
                                       IpduM_GetRxMuxByteOrder(RxIpduId),
                                       PduInfoPtr->SduDataPtr);
    dynPartIdx = IpduM_GetRxMuxDynPartIdx(RxIpduId);
    #if ((IPDUM_BINARY_SEARCH == STD_ON) && (IPDUM_LINEAR_SEARCH == STD_ON))
    if ((IpduM_RxPartIntType)IPDUM_BINARY_SEARCH_THRESHOLD < dynPartCnt)
    #endif
    #if (IPDUM_BINARY_SEARCH == STD_ON)
    {
      /* @Trace: IpduM_SUD_API_075 */
      /* Search selector field in the data base for dynamic I-PDU */
      dynPartIdx = IpduM_BinarySearch(dynPartIdx, dynPartCnt, selVal);
    }
    #endif
    #if ((IPDUM_BINARY_SEARCH == STD_ON) && (IPDUM_LINEAR_SEARCH == STD_ON))
    else
    #endif
    #if (IPDUM_LINEAR_SEARCH == STD_ON)
    {
      /* @Trace: IpduM_SUD_API_076 */
      /* Search selector field in the data base for dynamic I-PDU */
      dynPartIdx = IpduM_LinearSearch(dynPartIdx, dynPartCnt, selVal);
    }
    #endif
    /* Check if the Dynamic part found corresponding to Selector Value */
    if (IPDUM_RXPART_INVALID_IDX != dynPartIdx)
    {
      /* @Trace: IpduM_SUD_API_077 */
      /* Indicates Rx Dynamic Part to upper layer */
      IpduM_UpRxIndFunc(IpduM_GetRxMuxDynRefPduId(dynPartIdx), PduInfoPtr);
    }
    else
    {
      /* No action */
    }
  #if (IPDUM_CHECK_NO_OF_DYN_RX_IND_IPDU_IS_ZERO == STD_ON)
  } /* End of checking if existing Rx Dynamic part */
  else
  {
    /* No action */
  }
  #endif
  #endif /* (IPDUM_RX_DYNAMIC_IPDU == STD_ON) */
} /* End of IpduM_RxIpduMux() */
#endif /* (IPDUM_RX_IPDU == STD_ON) */

/*******************************************************************************
** Function Name        :                                                     **
**                                                                            **
** Service ID           : Not applicable                                      **
**                                                                            **
** Description          :                                                     **
**                                                                            **
** Reentrancy           :                                                     **
**                                                                            **
** Input Parameters     :                                                     **
**                                                                            **
** Output Parameters    :                                                     **
**                                                                            **
** Return parameter     :                                                     **
**                                                                            **
** Preconditions        :                                                     **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                                                                            **
**                        Function(s) invoked:                                **
**                                                                            **
*******************************************************************************/
#if ((IPDUM_TX_CONTAINER == STD_ON) || ((IPDUM_RX_CONTAINER == STD_ON) && (IPDUM_RX_DYNAMIC_CONTAINER == STD_ON)))
  FUNC(void, IPDUM_CODE) IpduM_ReadContainerHeader(
  P2CONST(uint8, AUTOMATIC, IPDUM_APPL_DATA) BufPtr,
  P2VAR(IpduM_HeaderFieldType, AUTOMATIC, IPDUM_APPL_DATA) Header,
  uint8 HeaderSize)
{
  #if ((IPDUM_TX_DYNAMIC_CONTAINER == STD_ON) || (IPDUM_RX_DYNAMIC_CONTAINER == STD_ON))
  if (IPDUM_HEADERTYPE_SHORT == HeaderSize)
  {
    /* @Trace: IpduM_SUD_API_078 */
    #if (IPDUM_HEADER_BYTE_ORDER == IPDUM_LITTLE_ENDIAN)
    Header->HeaderId = (((uint32)BufPtr[IPDUM_ZERO] << IPDUM_ZERO) |
                        ((uint32)BufPtr[IPDUM_ONE]  << IPDUM_EIGHT) |
                        ((uint32)BufPtr[IPDUM_TWO]  << IPDUM_SIXTEEN));
    #else
      /* @Trace: IpduM_SUD_API_079 */
    Header->HeaderId = (((uint32)BufPtr[IPDUM_ZERO] << IPDUM_SIXTEEN) |
                        ((uint32)BufPtr[IPDUM_ONE]  << IPDUM_EIGHT) |
                        ((uint32)BufPtr[IPDUM_TWO]  << IPDUM_ZERO));
    #endif
    /* @Trace: IpduM_SUD_API_080 */
    Header->Dlc = (uint32)BufPtr[3];
  }
  else if (IPDUM_HEADERTYPE_LONG == HeaderSize)
  {
    /* @Trace: IpduM_SUD_API_081 */
    #if (IPDUM_HEADER_BYTE_ORDER == IPDUM_LITTLE_ENDIAN)
    Header->HeaderId = (((uint32)BufPtr[IPDUM_ZERO]  << IPDUM_ZERO) |
                        ((uint32)BufPtr[IPDUM_ONE]   << IPDUM_EIGHT) |
                        ((uint32)BufPtr[IPDUM_TWO]   << IPDUM_SIXTEEN) |
                        ((uint32)BufPtr[IPDUM_THREE] << IPDUM_TWENTYFOUR));
    Header->Dlc = (((uint32)BufPtr[IPDUM_FOUR]  << IPDUM_ZERO) |
                   ((uint32)BufPtr[IPDUM_FIVE]  << IPDUM_EIGHT) |
                   ((uint32)BufPtr[IPDUM_SIX]   << IPDUM_SIXTEEN) |
                   ((uint32)BufPtr[IPDUM_SEVEN] << IPDUM_TWENTYFOUR));
    #else
      /* @Trace: IpduM_SUD_API_082 */
    Header->HeaderId = (((uint32)BufPtr[IPDUM_ZERO]  << IPDUM_TWENTYFOUR) |
                        ((uint32)BufPtr[IPDUM_ONE]   << IPDUM_SIXTEEN) |
                        ((uint32)BufPtr[IPDUM_TWO]   << IPDUM_EIGHT) |
                        ((uint32)BufPtr[IPDUM_THREE] << IPDUM_ZERO));
    Header->Dlc = (((uint32)BufPtr[IPDUM_FOUR]  << IPDUM_TWENTYFOUR) |
                   ((uint32)BufPtr[IPDUM_FIVE]  << IPDUM_SIXTEEN) |
                   ((uint32)BufPtr[IPDUM_SIX]   << IPDUM_EIGHT) |
                   ((uint32)BufPtr[IPDUM_SEVEN] << IPDUM_ZERO));
    #endif
  }
  else
  #endif /* ((IPDUM_TX_DYNAMIC_CONTAINER == STD_ON) || (IPDUM_RX_DYNAMIC_CONTAINER == STD_ON)) */
  {
    /* @Trace: IpduM_SUD_API_083 */
    Header->HeaderId = (uint32)IPDUM_ZERO;
    Header->Dlc = (uint32)IPDUM_ZERO;
    IPDUM_UNUSED(BufPtr);
    IPDUM_UNUSED(HeaderSize);
  }
} /* End of IpduM_ReadContainerHeader() */
#endif /* ((IPDUM_TX_CONTAINER == STD_ON) || (IPDUM_RX_CONTAINER == STD_ON)) */

/*******************************************************************************
** Function Name        :                                                     **
**                                                                            **
** Service ID           : Not applicable                                      **
**                                                                            **
** Description          :                                                     **
**                                                                            **
** Reentrancy           :                                                     **
**                                                                            **
** Input Parameters     :                                                     **
**                                                                            **
** Output Parameters    :                                                     **
**                                                                            **
** Return parameter     :                                                     **
**                                                                            **
** Preconditions        :                                                     **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                                                                            **
**                        Function(s) invoked:                                **
**                                                                            **
*******************************************************************************/
#if (IPDUM_TX_CONTAINER == STD_ON)
#if (IPDUM_TX_DYNAMIC_CONTAINER == STD_ON)
  FUNC(void, IPDUM_CODE) IpduM_WriteContainerHeader(
  P2VAR(uint8, AUTOMATIC, IPDUM_APPL_DATA) BufPtr,
  P2CONST(IpduM_HeaderFieldType, AUTOMATIC, IPDUM_APPL_DATA) Header,
  uint8 HeaderSize)
{
  if (IPDUM_HEADERTYPE_SHORT == HeaderSize)
  {
    /* @Trace: IpduM_SUD_API_084 */
    #if (IPDUM_HEADER_BYTE_ORDER == IPDUM_LITTLE_ENDIAN)
    BufPtr[IPDUM_ZERO] = (uint8)(Header->HeaderId >> IPDUM_ZERO);
    BufPtr[IPDUM_ONE]  = (uint8)(Header->HeaderId >> IPDUM_EIGHT);
    BufPtr[IPDUM_TWO]  = (uint8)(Header->HeaderId >> IPDUM_SIXTEEN);
    #else
      /* @Trace: IpduM_SUD_API_085 */
    BufPtr[IPDUM_ZERO] = (uint8)(Header->HeaderId >> IPDUM_SIXTEEN);
    BufPtr[IPDUM_ONE]  = (uint8)(Header->HeaderId >> IPDUM_EIGHT);
    BufPtr[IPDUM_TWO]  = (uint8)(Header->HeaderId >> IPDUM_ZERO);
    #endif
    /* @Trace: IpduM_SUD_API_086 */
    BufPtr[IPDUM_THREE] = (uint8)(Header->Dlc);
  }
  else if (IPDUM_HEADERTYPE_LONG == HeaderSize)
  {
    /* @Trace: IpduM_SUD_API_087 */
    #if (IPDUM_HEADER_BYTE_ORDER == IPDUM_LITTLE_ENDIAN)
    BufPtr[IPDUM_ZERO]  = (uint8)(Header->HeaderId >> IPDUM_ZERO);
    BufPtr[IPDUM_ONE]   = (uint8)(Header->HeaderId >> IPDUM_EIGHT);
    BufPtr[IPDUM_TWO]   = (uint8)(Header->HeaderId >> IPDUM_SIXTEEN);
    BufPtr[IPDUM_THREE] = (uint8)(Header->HeaderId >> IPDUM_TWENTYFOUR);
    BufPtr[IPDUM_FOUR]  = (uint8)(Header->Dlc >> IPDUM_ZERO);
    BufPtr[IPDUM_FIVE]  = (uint8)(Header->Dlc >> IPDUM_EIGHT);
    BufPtr[IPDUM_SIX]   = (uint8)(Header->Dlc >> IPDUM_SIXTEEN);
    BufPtr[IPDUM_SEVEN] = (uint8)(Header->Dlc >> IPDUM_TWENTYFOUR);
    #else
      /* @Trace: IpduM_SUD_API_088 */
    BufPtr[IPDUM_ZERO]  = (uint8)(Header->HeaderId >> IPDUM_TWENTYFOUR);
    BufPtr[IPDUM_ONE]   = (uint8)(Header->HeaderId >> IPDUM_SIXTEEN);
    BufPtr[IPDUM_TWO]   = (uint8)(Header->HeaderId >> IPDUM_EIGHT);
    BufPtr[IPDUM_THREE] = (uint8)(Header->HeaderId >> IPDUM_ZERO);
    BufPtr[IPDUM_FOUR]  = (uint8)(Header->Dlc >> IPDUM_TWENTYFOUR);
    BufPtr[IPDUM_FIVE]  = (uint8)(Header->Dlc >> IPDUM_SIXTEEN);
    BufPtr[IPDUM_SIX]   = (uint8)(Header->Dlc >> IPDUM_EIGHT);
    BufPtr[IPDUM_SEVEN] = (uint8)(Header->Dlc >> IPDUM_ZERO);
    #endif
  }
  else
  {
    /* No action */
  }
} /* End of IpduM_WriteContainerHeader() */
#endif /* (IPDUM_TX_DYNAMIC_CONTAINER == STD_ON) */
#endif /* (IPDUM_TX_CONTAINER == STD_ON) */

/*******************************************************************************
** Function Name        :                                                     **
**                                                                            **
** Service ID           : Not applicable                                      **
**                                                                            **
** Description          :                                                     **
**                                                                            **
** Reentrancy           :                                                     **
**                                                                            **
** Input Parameters     :                                                     **
**                                                                            **
** Output Parameters    :                                                     **
**                                                                            **
** Return parameter     :                                                     **
**                                                                            **
** Preconditions        :                                                     **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                                                                            **
**                        Function(s) invoked:                                **
**                                                                            **
*******************************************************************************/
#if (IPDUM_TX_CONTAINER == STD_ON)
#if ((IPDUM_TX_DYNAMIC_CONTAINER == STD_ON) && (IPDUM_TX_LASTISBEST_CONTAINER == STD_ON))
LOCAL_INLINE FUNC(void, IPDUM_CODE) IpduM_UpdateLIBDynamicContainer(
  IpduM_TxContainerIntType ContainerId,
  P2VAR(PduInfoType, AUTOMATIC, IPDUM_APPL_DATA) PduInfoPtr)
{
  Std_ReturnType updateResult;
  PduInfoType pduInfo;
  PduLengthType availablePduLen;
  IpduM_TxContainedIntType readCnt;
  PduLengthType writeIdx;
  IpduM_TxContainedIntType currContainedId;
  PduLengthType headerSize;
  IpduM_HeaderFieldType header;

  IpduM_TxContainedIntType addedFlagPos;
  uint8 addedFlagMask;
  #if (IPDUM_TX_CONF_CONTAINER == STD_ON)
    /* @Trace: IpduM_SUD_API_089 */
  IpduM_TxContainedIntType confWriteIdx;

  confWriteIdx = IpduM_GetContainerTxPduConfBufIdx(ContainerId);
  #endif
    /* @Trace: IpduM_SUD_API_090 */
  headerSize = (PduLengthType)IpduM_GetTxContainerHeaderSize(ContainerId);
  readCnt = (IpduM_TxContainedIntType)IPDUM_ZERO;
  writeIdx = (IpduM_TxContainedIntType)IPDUM_ZERO;
  while ((IpduM_GetNoOfContainedPduInContainerTx(ContainerId) > readCnt) &&
      (IpduM_GetMaxInstanceLenOfTxContainer(ContainerId) >= (writeIdx + headerSize)))
  {
    /* @Trace: IpduM_SUD_API_091 */
    updateResult = E_NOT_OK;
    availablePduLen = IpduM_GetMaxInstanceLenOfTxContainer(ContainerId) - writeIdx - headerSize;

    #if (IPDUM_CONTAINED_TX_PDU_PRIORITY_HANDLING == STD_OFF)
      /* @Trace: IpduM_SUD_API_092 */
    currContainedId = IpduM_GetOffsetOfLIBContainerTxIdxBuf(ContainerId) + \
    		          IpduM_GetReadPosOfLIBContainerTxIdxBuf(ContainerId);
    currContainedId = IpduM_GetContainedPduIdxFromLIBContainerTxIdxBuf(currContainedId);
    #else
      /* @Trace: IpduM_SUD_API_093 */
    currContainedId = IpduM_GetFirstTxContainedOfContainer(ContainerId) + readCnt;
    #if (IPDUM_EXIST_CONTAINEDTXPDU_SAME_PRIORITY == STD_ON)
    if ((IpduM_TxContainedIntType)IPDUM_ONE < IpduM_GetNoOfContainedPduTxHaveSamePriorityValue(currContainedId))
    {
      /* @Trace: IpduM_SUD_API_094 */
      /* Update containedPdu with same priority as the order of request */
      currContainedId = IpduM_GetOffsetOfLIBContainerTxIdxBuf(ContainerId) + \
    		            IpduM_GetReadPosOfLIBContainerTxIdxBuf(ContainerId);
      currContainedId = IpduM_GetContainedPduIdxFromLIBContainerTxIdxBuf(currContainedId);
    }
    else
    {
      /* No action */
    }
    #endif /* (IPDUM_EXIST_CONTAINEDTXPDU_SAME_PRIORITY == STD_ON) */
    #endif
      /* @Trace: IpduM_SUD_API_095 */
    addedFlagPos = IpduM_GetLIBAddedFlagIdxOfTxContainedPdu(currContainedId);
    addedFlagMask = IpduM_GetLIBAddedFlagMaskOfTxContainedPdu(currContainedId);
    /* If this containedPdu was added in ContainerPdu */
    if (FALSE != (IpduM_GetLIBAddedFlagBuffer(addedFlagPos) & addedFlagMask))
    {
      /* @Trace: IpduM_SUD_API_096 */
      SchM_Enter_IpduM_TX_CONTAINER_PROTECTION_AREA();
      IpduM_ClearLIBAddedFlagOfTxContainedPdu(addedFlagPos, addedFlagMask);
      SchM_Exit_IpduM_TX_CONTAINER_PROTECTION_AREA();

      pduInfo.SduDataPtr = &PduInfoPtr->SduDataPtr[writeIdx + headerSize];
      pduInfo.SduLength = availablePduLen;

      /* Update the current containedPdu */
      updateResult = IpduM_UpTriggerTxFunc(IpduM_GetTxContainedRefPduId(currContainedId), &pduInfo);

      /* If fetching current containedPdu is successful */
      if (E_OK == updateResult)
      {
        /* @Trace: IpduM_SUD_API_097 */
        header.HeaderId = IpduM_GetTxContainedHeaderId(currContainedId);
        header.Dlc = pduInfo.SduLength;
        IpduM_WriteContainerHeader(&PduInfoPtr->SduDataPtr[writeIdx], &header, (uint8)headerSize);
        writeIdx += pduInfo.SduLength + headerSize;

        #if (IPDUM_TX_CONF_CONTAINER == STD_ON)
        /* If transmission confirmation for ContainerPdu configured */
          /* @Trace: IpduM_SUD_API_098 */
          /* Store index of containedPdu for TxConfirmation */
          IpduM_SetContainedTxPduIdxToConfBuf(confWriteIdx, currContainedId);
          /* Increase for next containedPdu */
          confWriteIdx++;
        #endif
      }
      else
      {
        /* @Trace: IpduM_SUD_API_075 */
        #if (IPDUM_CONTAINED_TX_PDU_PRIORITY_HANDLING == STD_OFF)
        /* If failed updated is caused by the available length is not enough to
        * store containedPdu, shift this contained I-PDU and all following to
        * the next container instance.
        */
        if (IpduM_GetTxContainedMaxPduLen(currContainedId) > availablePduLen)
        {
          /* @Trace: IpduM_SUD_API_099 */
          /* Break the loop as has no more containedPdu */
          readCnt = IpduM_GetNoOfContainedPduInContainerTx(ContainerId) - (IpduM_TxContainedIntType)IPDUM_ONE;
        }
        else
        {
          /* No action as skip this containedPdu silently */
        }
        #endif
      }

      /* Increase pointer to next containedPdu */
      #if (IPDUM_CONTAINED_TX_PDU_PRIORITY_HANDLING == STD_OFF)
        /* @Trace: IpduM_SUD_API_100 */
        IpduM_IncReadPosOfLIBContainerTxIdxBuf(ContainerId);
        if (IpduM_GetSizeOfLIBContainerTxIdxBuf(ContainerId) <= IpduM_GetReadPosOfLIBContainerTxIdxBuf(ContainerId))
        {
          /* @Trace: IpduM_SUD_API_101 */
          IpduM_ClearReadPosOfLIBContainerTxIdxBuf(ContainerId);
        }
      #elif (IPDUM_EXIST_CONTAINEDTXPDU_SAME_PRIORITY == STD_ON)
      if ((IpduM_TxContainedIntType)IPDUM_ONE < IpduM_GetNoOfContainedPduTxHaveSamePriorityValue(currContainedId))
      {
        /* @Trace: IpduM_SUD_API_102 */
        IpduM_IncReadPosOfLIBContainerTxIdxBuf(currContainedId);
        if (IpduM_GetNoOfContainedPduTxHaveSamePriorityValue(currContainedId) <= IpduM_GetReadPosOfLIBContainerTxIdxBuf(currContainedId))
        {
          /* @Trace: IpduM_SUD_API_103 */
          IpduM_ClearReadPosOfLIBContainerTxIdxBuf(currContainedId);
        }
      }
      #endif
    }
    else
    {
      /* @Trace: IpduM_SUD_API_104 */
      #if (IPDUM_CONTAINED_TX_PDU_PRIORITY_HANDLING == STD_OFF)
      /* Break the loop as has no more containedPdu following */
      readCnt = IpduM_GetNoOfContainedPduInContainerTx(ContainerId) - (IpduM_TxContainedIntType)IPDUM_ONE;
      #endif
    }
    /* Increase index to next containedPdu */
    /* @Trace: IpduM_SUD_API_105 */
    readCnt++;
  } /* End while loop */

  /* Update actual payload of containerPdu */
  /* @Trace: IpduM_SUD_API_106 */
  PduInfoPtr->SduLength = writeIdx;
} /* End of IpduM_UpdateLIBDynamicContainer() */
#endif /* ((IPDUM_TX_DYNAMIC_CONTAINER == STD_ON) && (IPDUM_TX_LASTISBEST_CONTAINER == STD_ON)) */
#endif /* (IPDUM_TX_CONTAINER == STD_ON) */

/*******************************************************************************
** Function Name        :                                                     **
**                                                                            **
** Service ID           : Not applicable                                      **
**                                                                            **
** Description          :                                                     **
**                                                                            **
** Reentrancy           :                                                     **
**                                                                            **
** Input Parameters     :                                                     **
**                                                                            **
** Output Parameters    :                                                     **
**                                                                            **
** Return parameter     :                                                     **
**                                                                            **
** Preconditions        :                                                     **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                                                                            **
**                        Function(s) invoked:                                **
**                                                                            **
*******************************************************************************/
#if (IPDUM_TX_CONTAINER == STD_ON)
#if ((IPDUM_TX_STATIC_CONTAINER == STD_ON) && (IPDUM_TX_LASTISBEST_CONTAINER == STD_ON))
LOCAL_INLINE FUNC(void, IPDUM_CODE) IpduM_UpdateLIBStaticContainer(
  IpduM_TxContainerIntType ContainerId,
  P2VAR(PduInfoType, AUTOMATIC, IPDUM_APPL_DATA) PduInfoPtr)
{
  Std_ReturnType updateResult;
  PduInfoType pduInfo;
  IpduM_TxContainedIntType readCnt;
  PduLengthType writeIdx;
  IpduM_TxContainedIntType currContainedId;
  PduLengthType upByteIdx;
  uint8 upByteMask;

  IpduM_TxContainedIntType addedFlagPos;
  uint8 addedFlagMask;
  #if (IPDUM_TX_CONF_CONTAINER == STD_ON)
    /* @Trace: IpduM_SUD_API_107 */
  IpduM_TxContainedIntType confWriteIdx;

  confWriteIdx = IpduM_GetContainerTxPduConfBufIdx(ContainerId);
  #endif
    /* @Trace: IpduM_SUD_API_108 */
  readCnt = (IpduM_TxContainedIntType)IPDUM_ZERO;
  while (IpduM_GetNoOfContainedPduInContainerTx(ContainerId) > readCnt)
  {
    /* @Trace: IpduM_SUD_API_109*/
    updateResult = E_NOT_OK;
    currContainedId = IpduM_GetFirstTxContainedOfContainer(ContainerId) + readCnt;

    addedFlagPos = IpduM_GetLIBAddedFlagIdxOfTxContainedPdu(currContainedId);
    addedFlagMask = IpduM_GetLIBAddedFlagMaskOfTxContainedPdu(currContainedId);
    /* If this containedPdu was added in ContainerPdu */
    if (FALSE != (IpduM_GetLIBAddedFlagBuffer(addedFlagPos) & addedFlagMask))
    {
      /* @Trace: IpduM_SUD_API_110 */
      SchM_Enter_IpduM_TX_CONTAINER_PROTECTION_AREA();
      IpduM_ClearLIBAddedFlagOfTxContainedPdu(addedFlagPos, addedFlagMask);
      SchM_Exit_IpduM_TX_CONTAINER_PROTECTION_AREA();

      writeIdx = IpduM_GetLIBStaticTxContainerOffset(currContainedId);
      pduInfo.SduDataPtr = &PduInfoPtr->SduDataPtr[writeIdx];
      pduInfo.SduLength = IpduM_GetTxContainedMaxPduLen(currContainedId);
      /* Update the current containedPdu */
      updateResult = IpduM_UpTriggerTxFunc(IpduM_GetTxContainedRefPduId(currContainedId), &pduInfo);
    }

    /* If there is no configuration of Update Bit Position, the byte mask shall
     * be zero and byte position is zero.
     */
     /* @Trace: IpduM_SUD_API_111 */
    upByteIdx = IpduM_GetStaticTxContainedUpdateBitBytePos(currContainedId);
    upByteMask = IpduM_GetStaticTxContainedUpdateBitByteMask(currContainedId);

    /* If fetching is failed or containedPdu was not updated by upper layer */
    if (E_OK != updateResult)
    {
      /* @Trace: IpduM_SUD_API_112 */
      /* This bit-wise shall not effective if the byte mask is zero */
      PduInfoPtr->SduDataPtr[upByteIdx] &= (uint8)(~upByteMask);
      /*
       * All not updated areas of the Container are set to the value of
       * IpduMUnusedAreasDefault. If has no configured IpduMUnusedAreasDefault
       * value, clear no updated area to zero to prevent unexpected behavior.
       */
      IpduM_SetData(&PduInfoPtr->SduDataPtr[writeIdx],
                    IpduM_GetLIBTxContainerUnusedBytePattern(ContainerId),
                    IpduM_GetTxContainedMaxPduLen(currContainedId));
    }
    else
    {
      #if (IPDUM_TX_CONF_CONTAINER == STD_ON)
      /* If transmission confirmation for ContainerPdu configured */
        /* @Trace: IpduM_SUD_API_113 */
        /* Store index of containedPdu for TxConfirmation */
        IpduM_SetContainedTxPduIdxToConfBuf(confWriteIdx, currContainedId);
        /* Increase for next containedPdu */
        confWriteIdx++;
      #endif
      /* This bit-wise is not effective if the byte mask is zero */
      /* @Trace: IpduM_SUD_API_114 */
      PduInfoPtr->SduDataPtr[upByteIdx] |= upByteMask;
      /* For the latest ContainedPdu with dynamic length */
      if (IpduM_GetTxContainedMaxPduLen(currContainedId) > pduInfo.SduLength)
      {
        /* @Trace: IpduM_SUD_API_115 */
        writeIdx += pduInfo.SduLength;
       /*
        * All not updated areas of the Container are set to the value of
        * IpduMUnusedAreasDefault. If has no configured IpduMUnusedAreasDefault
        * value, clear no updated area to zero to prevent unexpected behavior.
        */
        IpduM_SetData(&PduInfoPtr->SduDataPtr[writeIdx],
                      IpduM_GetLIBTxContainerUnusedBytePattern(ContainerId),
                      IpduM_GetTxContainedMaxPduLen(currContainedId) - pduInfo.SduLength);
      }
      else
      {
        /* No action */
      }
    }
    /* Increase to next containedPdu */
    /* @Trace: IpduM_SUD_API_116 */
    readCnt++;
  } /* End while loop of all Static containedPdu */
} /* End of IpduM_UpdateLIBStaticContainer() */
#endif /* ((IPDUM_TX_STATIC_CONTAINER == STD_ON) && (IPDUM_TX_LASTISBEST_CONTAINER == STD_ON)) */
#endif /* (IPDUM_TX_CONTAINER == STD_ON) */

/*******************************************************************************
** Function Name        :                                                     **
**                                                                            **
** Service ID           : Not applicable                                      **
**                                                                            **
** Description          :                                                     **
**                                                                            **
** Reentrancy           :                                                     **
**                                                                            **
** Input Parameters     :                                                     **
**                                                                            **
** Output Parameters    :                                                     **
**                                                                            **
** Return parameter     :                                                     **
**                                                                            **
** Preconditions        :                                                     **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                                                                            **
**                        Function(s) invoked:                                **
**                                                                            **
*******************************************************************************/
/* @Trace: SWS_IpduM_00193 SWS_IpduM_00194 SWS_IpduM_00220
 * SWS_IpduM_00231 SWS_IpduM_00221 SWS_IpduM_00249 SWS_IpduM_00222
 * SRS_IpduM_02820 SRS_IpduM_02821 SRS_IpduM_02823
 */
#if (IPDUM_TX_CONTAINER == STD_ON)
#if (IPDUM_TX_LASTISBEST_CONTAINER == STD_ON)
static FUNC(void, IPDUM_CODE) IpduM_UpdateLIBContainer(
  IpduM_TxContainerIntType ContainerId,
  P2VAR(PduInfoType, AUTOMATIC, IPDUM_APPL_DATA) PduInfoPtr)
{
  #if ((IPDUM_TX_DYNAMIC_CONTAINER == STD_ON) && (IPDUM_TX_STATIC_CONTAINER == STD_ON))
  if (FALSE == IpduM_IsDynamicContainerTx(ContainerId))
  #endif
  {
    /* @Trace: IpduM_SUD_API_117 */
    #if (IPDUM_TX_STATIC_CONTAINER == STD_ON)
    IpduM_UpdateLIBStaticContainer(ContainerId, PduInfoPtr);
    #endif
  }
  #if ((IPDUM_TX_DYNAMIC_CONTAINER == STD_ON) && (IPDUM_TX_STATIC_CONTAINER == STD_ON))
  else
  #endif
  {
    /* @Trace: IpduM_SUD_API_118 */
    #if (IPDUM_TX_DYNAMIC_CONTAINER == STD_ON)
    IpduM_UpdateLIBDynamicContainer(ContainerId, PduInfoPtr);
    #endif
  }
} /* End of IpduM_UpdateLIBContainer() */
#endif /* (IPDUM_TX_LASTISBEST_CONTAINER == STD_ON) */
#endif /* (IPDUM_TX_CONTAINER == STD_ON) */

/*******************************************************************************
** Function Name        :                                                     **
**                                                                            **
** Service ID           : Not applicable                                      **
**                                                                            **
** Description          :                                                     **
**                                                                            **
** Reentrancy           :                                                     **
**                                                                            **
** Input Parameters     :                                                     **
**                                                                            **
** Output Parameters    :                                                     **
**                                                                            **
** Return parameter     :                                                     **
**                                                                            **
** Preconditions        :                                                     **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                                                                            **
**                        Function(s) invoked:                                **
**                                                                            **
*******************************************************************************/
#if (IPDUM_TX_CONTAINER == STD_ON)
LOCAL_INLINE FUNC(void, IPDUM_CODE) IpduM_AddContainedPdu(
  IpduM_TxContainerIntType ContainerId, IpduM_TxContainedIntType ContainedId,
  P2CONST(PduInfoType, AUTOMATIC, IPDUM_APPL_DATA) PduInfoPtr)
{
  #if (IPDUM_TX_DYNAMIC_CONTAINER == STD_ON)
  PduLengthType headerSize;
  #if (IPDUM_TX_QUEUED_CONTAINER == STD_ON)
  uint8 *ptrTxBuff;
  PduLengthType writeIdx;
  IpduM_HeaderFieldType header;
  #endif
  #if ((IPDUM_TX_DYNAMIC_CONTAINER == STD_ON) && \
       (IPDUM_TX_LASTISBEST_CONTAINER == STD_ON) && \
       ((IPDUM_CONTAINED_TX_PDU_PRIORITY_HANDLING == STD_OFF) || \
        (IPDUM_EXIST_CONTAINEDTXPDU_SAME_PRIORITY == STD_ON)))
  IpduM_TxContainedIntType writePosLIBBuf;
  #endif
  #endif

  #if ((IPDUM_TX_DYNAMIC_CONTAINER == STD_ON) && (IPDUM_TX_STATIC_CONTAINER == STD_ON))
  if (FALSE != IpduM_IsDynamicContainerTx(ContainerId))
  #endif
  {
    /* @Trace: IpduM_SUD_API_119 */
    #if (IPDUM_TX_DYNAMIC_CONTAINER == STD_ON)
    #if (IPDUM_TX_QUEUED_CONTAINER == STD_ON)
    ptrTxBuff = IpduM_GetBasedAddrTxContainerBuffer(ContainerId);
    writeIdx = IpduM_GetWriteCntInstanceTxContainer(ContainerId) * \
              IpduM_GetMaxInstanceLenOfTxContainer(ContainerId) + \
              IpduM_GetSizeOfCurrInstanceTxContainer(ContainerId);
    #endif /* (IPDUM_TX_QUEUED_CONTAINER == STD_ON) */
    /* @Trace: IpduM_SUD_API_120 */
    headerSize = (PduLengthType)IpduM_GetTxContainerHeaderSize(ContainerId);

    #if ((IPDUM_TX_LASTISBEST_CONTAINER == STD_ON) && (IPDUM_TX_QUEUED_CONTAINER == STD_ON))
    if (FALSE == IpduM_IsLastIsBestTxContainerTx(ContainerId))
    #endif
    {
      /* @Trace: IpduM_SUD_API_121 */
      #if (IPDUM_TX_QUEUED_CONTAINER == STD_ON)
      /* If queued containerPdu, store containedPdu to container buffer */
      header.HeaderId = IpduM_GetTxContainedHeaderId(ContainedId);
      header.Dlc = PduInfoPtr->SduLength;

      IpduM_WriteContainerHeader(&ptrTxBuff[writeIdx], &header, (uint8)headerSize);
      IpduM_CopyData(PduInfoPtr->SduDataPtr, &ptrTxBuff[writeIdx + headerSize], PduInfoPtr->SduLength);
      #endif
    }
    #if ((IPDUM_TX_LASTISBEST_CONTAINER == STD_ON) && (IPDUM_TX_QUEUED_CONTAINER == STD_ON))
    else
    #endif
    {
      #if ((IPDUM_TX_DYNAMIC_CONTAINER == STD_ON) && \
           (IPDUM_TX_LASTISBEST_CONTAINER == STD_ON))
      /* If dynamic containerPdu is last-is-best, store order of ContainedPdu
       * to buffer. Do not store the containedPdu since IpduM shall update the
       * latest containedPDUs when trigger the transmission or fetched via
       * IpduM_TriggerTransmit by lower layer.
       */
      #if (IPDUM_CONTAINED_TX_PDU_PRIORITY_HANDLING == STD_OFF)
        /* @Trace: IpduM_SUD_API_122 */
      writePosLIBBuf = IpduM_GetWritePosOfLIBContainerTxIdxBuf(ContainerId) + \
    		           IpduM_GetOffsetOfLIBContainerTxIdxBuf(ContainerId);
      IpduM_SetContainedPduIdxToLIBContainerTxIdxBuf(writePosLIBBuf, ContainedId);
      IpduM_IncWritePosOfLIBContainerTxIdxBuf(ContainerId);
      if (IpduM_GetSizeOfLIBContainerTxIdxBuf(ContainerId) <= IpduM_GetWritePosOfLIBContainerTxIdxBuf(ContainerId))
      {
        /* @Trace: IpduM_SUD_API_123 */
        IpduM_ClearWritePosOfLIBContainerTxIdxBuf(ContainerId);
      }
      #elif (IPDUM_EXIST_CONTAINEDTXPDU_SAME_PRIORITY == STD_ON)
      /* In case priority handling is true, the order of ContainedPDUs is
       * defined by configuration of IpduMContainedTxPduPriority. If I-PDUs
       * with the same IpduMContainedTxPduPriority shall be collected in the
       * order the send request
       */
      if ((IpduM_TxContainedIntType)IPDUM_ONE < IpduM_GetNoOfContainedPduTxHaveSamePriorityValue(ContainedId))
      {
        /* @Trace: IpduM_SUD_API_124 */
        /* Store the order of I-PDUs with the same priority */
        writePosLIBBuf = IpduM_GetWritePosOfLIBContainerTxIdxBuf(ContainedId) + \
        		         IpduM_GetOffsetOfLIBContainerTxIdxBuf(ContainerId);
        IpduM_SetContainedPduIdxToLIBContainerTxIdxBuf(writePosLIBBuf, ContainedId);
        IpduM_IncWritePosOfLIBContainerTxIdxBuf(ContainedId);
        if (IpduM_GetNoOfContainedPduTxHaveSamePriorityValue(ContainedId) <= IpduM_GetWritePosOfLIBContainerTxIdxBuf(ContainedId))
        {
          /* @Trace: IpduM_SUD_API_125 */
          IpduM_ClearWritePosOfLIBContainerTxIdxBuf(ContainedId);
        }
      }
      else
      {
        /* No action */
      }
      #endif
      #endif /* ((IPDUM_TX_DYNAMIC_CONTAINER == STD_ON) && (IPDUM_TX_LASTISBEST_CONTAINER == STD_ON)) */
    }
    /* Increase the size of current instance */
    /* @Trace: IpduM_SUD_API_126 */
    IpduM_SetCurrInstanceLengthOfTxContainer(ContainerId, (IpduM_GetSizeOfCurrInstanceTxContainer(ContainerId) + headerSize + PduInfoPtr->SduLength));
    IPDUM_UNUSED(ContainedId);
    #endif /* (IPDUM_TX_DYNAMIC_CONTAINER == STD_ON) */
  }
  #if ((IPDUM_TX_DYNAMIC_CONTAINER == STD_ON) && (IPDUM_TX_STATIC_CONTAINER == STD_ON))
  else
  #endif
  {
    /* @Trace: IpduM_SUD_API_127 */
    /* No action for Static Container because the order of ContainedPDUs was
     * defined by IpduMContainedPduOffset in configuration
     */
    #if (IPDUM_TX_STATIC_CONTAINER == STD_ON)
    IpduM_SetCurrInstanceLengthOfTxContainer(ContainerId, (IpduM_GetSizeOfCurrInstanceTxContainer(ContainerId) + PduInfoPtr->SduLength));
    IPDUM_UNUSED(ContainedId);
    #endif
  }

} /* End of IpduM_AddContainedPdu() */
#endif /* (IPDUM_TX_CONTAINER == STD_ON) */

/*******************************************************************************
** Function Name        :                                                     **
**                                                                            **
** Service ID           : Not applicable                                      **
**                                                                            **
** Description          :                                                     **
**                                                                            **
** Reentrancy           :                                                     **
**                                                                            **
** Input Parameters     :                                                     **
**                                                                            **
** Output Parameters    :                                                     **
**                                                                            **
** Return parameter     :                                                     **
**                                                                            **
** Preconditions        :                                                     **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                                                                            **
**                        Function(s) invoked:                                **
**                                                                            **
*******************************************************************************/
#if (IPDUM_TX_CONTAINER == STD_ON)
FUNC(PduLengthType, IPDUM_CODE) IpduM_CalculateContainerSize(
  IpduM_TxContainerIntType ContainerId,
  P2CONST(uint8, AUTOMATIC, IPDUM_APPL_DATA) BufPtr)
{
  PduLengthType readIdx;
  PduLengthType pduLen;
  IpduM_HeaderFieldType header;
  /* @Trace: IpduM_SUD_API_128 */
  readIdx = (PduLengthType)IPDUM_ZERO;
  while (IpduM_GetMaxInstanceLenOfTxContainer(ContainerId) >
    (readIdx + (PduLengthType)IpduM_GetTxContainerHeaderSize(ContainerId)))
  {
    /* @Trace: IpduM_SUD_API_129 */
    IpduM_ReadContainerHeader(&BufPtr[readIdx], &header,
                              IpduM_GetTxContainerHeaderSize(ContainerId));
    if ((uint32)IPDUM_ZERO == header.HeaderId)
    {
      /* @Trace: IpduM_SUD_API_130 */
      /* There is no more containedPdu inside, break the loop */
      readIdx = IpduM_GetMaxInstanceLenOfTxContainer(ContainerId);
    }
    else
    {
      /* @Trace: IpduM_SUD_API_131 */
      /* Increase read index */
      readIdx += (PduLengthType)header.Dlc + \
                    (PduLengthType)IpduM_GetTxContainerHeaderSize(ContainerId);
      pduLen = readIdx;
    }
  }
  /* @Trace: IpduM_SUD_API_132 */
  return pduLen;
} /* End of IpduM_CalculateContainerSize() */
#endif /* (IPDUM_TX_CONTAINER == STD_ON) */

/*******************************************************************************
** Function Name        :                                                     **
**                                                                            **
** Service ID           : Not applicable                                      **
**                                                                            **
** Description          :                                                     **
**                                                                            **
** Reentrancy           :                                                     **
**                                                                            **
** Input Parameters     :                                                     **
**                                                                            **
** Output Parameters    :                                                     **
**                                                                            **
** Return parameter     :                                                     **
**                                                                            **
** Preconditions        :                                                     **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                                                                            **
**                        Function(s) invoked:                                **
**                                                                            **
*******************************************************************************/
#if (IPDUM_TX_CONTAINER == STD_ON)
#if (IPDUM_TX_CONF_CONTAINER == STD_ON)
FUNC(void, IPDUM_CODE) IpduM_StoreContainedPduIdxForConf(
  IpduM_TxContainerIntType ContainerId,
  P2CONST(PduInfoType, AUTOMATIC, IPDUM_APPL_DATA) PduInfoPtr)
{
  PduLengthType readIdx;
  IpduM_HeaderFieldType header;
  IpduM_TxContainedIntType count;
  IpduM_TxContainerIntType containedId;
  IpduM_TxContainedIntType confWriteIdx;

  /* If transmission confirmation for ContainerPdu configured */
    /* @Trace: IpduM_SUD_API_133 */
    confWriteIdx = IpduM_GetContainerTxPduConfBufIdx(ContainerId);

    count = (IpduM_TxContainedIntType)IPDUM_ZERO;
    /* Loop all containedPdu could be in the containerPdu */
    while (IpduM_GetNoOfContainedPduInContainerTx(ContainerId) > count)
    {
      /* @Trace: IpduM_SUD_API_134 */
      containedId = IpduM_GetFirstTxContainedOfContainer(ContainerId) + count;

      readIdx = (PduLengthType)IPDUM_ZERO;
      while (PduInfoPtr->SduLength >
        (readIdx + (PduLengthType)IpduM_GetTxContainerHeaderSize(ContainerId)))
      {
        /* @Trace: IpduM_SUD_API_135 */
        IpduM_ReadContainerHeader(&PduInfoPtr->SduDataPtr[readIdx], &header,
                                  IpduM_GetTxContainerHeaderSize(ContainerId));
        /* If containedPdu found in the sent out containerPdu */
        #if (IPDUM_TX_DYNAMIC_CONTAINER == STD_ON)
        if (IpduM_GetTxContainedHeaderId(containedId) == header.HeaderId)
        {
          /* @Trace: IpduM_SUD_API_136 */
          /* Store index of containedPdu for TxConfirmation */
          IpduM_SetContainedTxPduIdxToConfBuf(confWriteIdx, containedId);
          /* Increase for next containedPdu */
          confWriteIdx++;
          /* Break the loop */
          readIdx = PduInfoPtr->SduLength;
        }
        else
        #endif
        {
          /* @Trace: IpduM_SUD_API_137 */
          /* Increase read index */
          readIdx += (PduLengthType)header.Dlc + \
                    (PduLengthType)IpduM_GetTxContainerHeaderSize(ContainerId);
        }
      }
      /* Increase index to next containedPdu */
      /* @Trace: IpduM_SUD_API_138 */
      count++;
    }
  /* @Trace: IpduM_SUD_API_139 */
  IPDUM_UNUSED(confWriteIdx);
  IPDUM_UNUSED(containedId);

} /* End of IpduM_StoreContainedPduIdxForConf() */
#endif /* #if (IPDUM_TX_CONF_CONTAINER == STD_ON) */
#endif /* (IPDUM_TX_CONTAINER == STD_ON) */

/*******************************************************************************
** Function Name        :                                                     **
**                                                                            **
** Service ID           : Not applicable                                      **
**                                                                            **
** Description          :                                                     **
**                                                                            **
** Reentrancy           :                                                     **
**                                                                            **
** Input Parameters     :                                                     **
**                                                                            **
** Output Parameters    :                                                     **
**                                                                            **
** Return parameter     :                                                     **
**                                                                            **
** Preconditions        :                                                     **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                                                                            **
**                        Function(s) invoked:                                **
**                                                                            **
*******************************************************************************/
#if (IPDUM_TX_CONTAINER == STD_ON)
FUNC(void, IPDUM_CODE) IpduM_TxQueuedContainerPdu(
  IpduM_TxContainedIntType ContainerId)
{
  Std_ReturnType txResult;
  PduInfoType pduInfo;
  PduLengthType readIdx;
  uint8 instanceCnt;
  #if (IPDUM_TX_CONF_CONTAINER == STD_ON)
  IpduM_TxContainedIntType confIdx;
  uint8 confMask;
  /* @Trace: IpduM_SUD_API_140 */
  confIdx = IpduM_GetContainerByteIdxOfTxConfPendingFlagBuf(ContainerId);
  confMask = IpduM_GetContainerByteMaskOfTxConfPendingFlagBuf(ContainerId);
  
  #endif
  /* @Trace: IpduM_SUD_API_141 */
  txResult = E_OK;
  while ((E_OK == txResult)
    #if (IPDUM_TX_CONF_CONTAINER == STD_ON)
    && ((uint8)IPDUM_ZERO == IpduM_GetTxConfPendingFlag(confIdx, confMask))
    #endif
    )
  {
    /* @Trace: IpduM_SUD_API_142 */
    SchM_Enter_IpduM_TX_CONTAINER_PROTECTION_AREA();
    instanceCnt = IpduM_GetCntOfQueuedInstanceTxContainer(ContainerId);
    SchM_Exit_IpduM_TX_CONTAINER_PROTECTION_AREA();

    if ((uint8)IPDUM_ZERO < instanceCnt)
    {
      /* @Trace: IpduM_SUD_API_143 */
      pduInfo.SduLength = IpduM_GetMaxInstanceLenOfTxContainer(ContainerId);

      if ((FALSE != IpduM_IsTriggerTransmitContainerTx(ContainerId)) &&
          (FALSE != IpduM_IsLastIsBestTxContainerTx(ContainerId)))
      {
        /* @Trace: IpduM_SUD_API_144 */
        /* If trigger mode of LastIsBest ContainerPdu is triggertransmit,
         * IpduM shall update latest data of ContainerPdu when it fetched from
         * lower layer module via IpduM_TriggerTrasnmit. Hence, no data shall be
         * transferred via PduR_IpduMTransmit.
         * For optimizing, IpduM shall not provide buffer for these ContainerPDUs
         */
        pduInfo.SduDataPtr = NULL_PTR;
      }
      else
      {
        /* @Trace: IpduM_SUD_API_145 */
        readIdx = IpduM_GetReadCntInstanceTxContainer(ContainerId) * IpduM_GetMaxInstanceLenOfTxContainer(ContainerId);
        pduInfo.SduDataPtr = IpduM_GetBasedAddrTxContainerBuffer(ContainerId);
        pduInfo.SduDataPtr = &pduInfo.SduDataPtr[readIdx];

        if (FALSE != IpduM_IsLastIsBestTxContainerTx(ContainerId))
        {
          /* No action */
        }
        else
        {
          /* @Trace: IpduM_SUD_API_146 */
          pduInfo.SduLength = IpduM_CalculateContainerSize(ContainerId, pduInfo.SduDataPtr);
          #if (IPDUM_TX_CONF_CONTAINER == STD_ON)
          /* Store the index of containedPdus in the sent out containerPdu */
          /* @Trace: IpduM_SUD_API_147 */
          IpduM_StoreContainedPduIdxForConf(ContainerId, &pduInfo);
          #endif
        }
      }
      #if (IPDUM_META_DATA_SUPPORT == STD_ON)
      /* Use the MetaData last collected from the contained I-PDUs */
      if (FALSE != IpduM_IsTxContainerMetaDataSupport(ContainerId))
      {
        /* @Trace: IpduM_SUD_API_148 */
        pduInfo.MetaDataPtr = IpduM_GetBasedAddrTxContainerMetaDataBuffer(ContainerId);
      }
      else
      {
        /* No action */
      }
      #endif
      /* @Trace: IpduM_SUD_API_149 */
      txResult = PduR_IpduMTransmit(IpduM_GetTxContainerRefPduId(ContainerId), &pduInfo);

      /* If Direct containerPdu is sent out successfully */
      if ((E_OK == txResult) && \
          (FALSE == IpduM_IsTriggerTransmitContainerTx(ContainerId)))
      {
        /* @Trace: IpduM_SUD_API_150 */
        SchM_Enter_IpduM_TX_CONTAINER_PROTECTION_AREA();
        /* Direct containerPdu is sent out. Increase read pointer */
        IpduM_IncReadCntInstanceTxContainer(ContainerId);
        if (IpduM_GetMaxNoOfInstanceTxContainer(ContainerId) <= IpduM_GetReadCntInstanceTxContainer(ContainerId))
        {
          /* @Trace: IpduM_SUD_API_151 */
          IpduM_SetReadCntInstanceTxContainer(ContainerId, (uint8)IPDUM_ZERO);
        }
        /* Drop the containerPdu from the queue */
        /* @Trace: IpduM_SUD_API_152 */
        IpduM_DecCntOfQueuedInstanceTxContainer(ContainerId);
        SchM_Exit_IpduM_TX_CONTAINER_PROTECTION_AREA();

        #if (IPDUM_TX_CONF_CONTAINER == STD_ON)
          /* @Trace: IpduM_SUD_API_153 */
          IpduM_SetTxConfPendingFlag(confIdx, confMask);
        #endif
      }
      else
      {
        /* @Trace: IpduM_SUD_API_154 */
        /* Exit loop as keep current instance in queue */
        txResult = E_NOT_OK;
      }
    }
    else
    {
      /* Queue is empty. Exit loop */
      txResult = E_NOT_OK;
    }
  }
} /* End of IpduM_TxQueuedContainerPdu() */
#endif /* (IPDUM_TX_CONTAINER == STD_ON) */

/*******************************************************************************
** Function Name        :                                                     **
**                                                                            **
** Service ID           : Not applicable                                      **
**                                                                            **
** Description          :                                                     **
**                                                                            **
** Reentrancy           :                                                     **
**                                                                            **
** Input Parameters     :                                                     **
**                                                                            **
** Output Parameters    :                                                     **
**                                                                            **
** Return parameter     :                                                     **
**                                                                            **
** Preconditions        :                                                     **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                                                                            **
**                        Function(s) invoked:                                **
**                                                                            **
*******************************************************************************/
#if (IPDUM_TX_CONTAINER == STD_ON)
LOCAL_INLINE FUNC(Std_ReturnType, IPDUM_CODE) IpduM_TxCurrentContainerPdu(
  IpduM_TxContainerIntType ContainerId)
{
  Std_ReturnType txResult;
  PduInfoType pduInfo;
  PduLengthType writeIdx;
  #if (IPDUM_TX_CONF_CONTAINER == STD_ON)
  IpduM_TxContainedIntType confIdx;
  uint8 confMask;
  #endif

  /* No transmission, return "not ok" */
  txResult = E_NOT_OK;

  #if (IPDUM_TX_CONF_CONTAINER == STD_ON)
      /* @Trace: IpduM_SUD_API_155 */
  confIdx = IpduM_GetContainerByteIdxOfTxConfPendingFlagBuf(ContainerId);
  confMask = IpduM_GetContainerByteMaskOfTxConfPendingFlagBuf(ContainerId);
  /* Check if has no waiting for transmission confirmation */
  if ((uint8)IPDUM_ZERO == IpduM_GetTxConfPendingFlag(confIdx, confMask))
  #endif
  {
    /* @Trace: IpduM_SUD_API_156 */
    pduInfo.SduLength = IpduM_GetMaxInstanceLenOfTxContainer(ContainerId);

    if ((FALSE != IpduM_IsTriggerTransmitContainerTx(ContainerId)) &&
        (FALSE != IpduM_IsLastIsBestTxContainerTx(ContainerId)))
    {
      /* @Trace: IpduM_SUD_API_157 */
      /* If trigger mode of LastIsBest ContainerPdu is triggertransmit,
        * IpduM shall update latest data of ContainerPdu when it fetched from
        * lower layer module via IpduM_TriggerTrasnmit. Hence, no data shall be
        * transferred via PduR_IpduMTransmit.
        * For optimizing, IpduM shall not provide buffer for these ContainerPDUs
        */
      pduInfo.SduDataPtr = NULL_PTR;
    }
    else
    {
      /* @Trace: IpduM_SUD_API_158 */
      writeIdx = IpduM_GetWriteCntInstanceTxContainer(ContainerId) * \
                IpduM_GetMaxInstanceLenOfTxContainer(ContainerId);
      pduInfo.SduDataPtr = IpduM_GetBasedAddrTxContainerBuffer(ContainerId);
      pduInfo.SduDataPtr = &pduInfo.SduDataPtr[writeIdx];

      if (FALSE != IpduM_IsLastIsBestTxContainerTx(ContainerId))
      {
        /* @Trace: IpduM_SUD_API_159 */
        /* Update Last-Is-Best containerPdu if trigger mode is direct */
        IpduM_UpdateLIBContainer(ContainerId, &pduInfo);
      }
      else
      {
        /* @Trace: IpduM_SUD_API_160 */
        pduInfo.SduLength = IpduM_GetSizeOfCurrInstanceTxContainer(ContainerId);
        #if (IPDUM_TX_CONF_CONTAINER == STD_ON)
        /* Store the index of containedPdus in the sent out containerPdu */
        /* @Trace: IpduM_SUD_API_161 */
        IpduM_StoreContainedPduIdxForConf(ContainerId, &pduInfo);
        #endif
      }
    }

    #if (IPDUM_META_DATA_SUPPORT == STD_ON)
    /* Use the MetaData last collected from the contained I-PDUs */
    if (FALSE != IpduM_IsTxContainerMetaDataSupport(ContainerId))
    {
      /* @Trace: IpduM_SUD_API_162 */
      pduInfo.MetaDataPtr = IpduM_GetBasedAddrTxContainerMetaDataBuffer(ContainerId);
    }
    else
    {
      /* No action */
    }
    #endif

    if ((uint8)IPDUM_ZERO == IpduM_GetCntOfQueuedInstanceTxContainer(ContainerId))
    {
      /* @Trace: IpduM_SUD_API_163 */
      txResult = PduR_IpduMTransmit(IpduM_GetTxContainerRefPduId(ContainerId), &pduInfo);
    }
    else
    {
      /* No action */
    }

    /* If transmission of direct ContainerPdu is successful */
    if ((E_OK == txResult)
      #if (IPDUM_TX_TRIGGERTRANSMIT_CONTAINER == STD_ON)
      && (FALSE == IpduM_IsTriggerTransmitContainerTx(ContainerId))
      #endif
      )
    {
      /* @Trace: IpduM_SUD_API_164 */
      /* Reset the current instance ContainerPdu */
      IpduM_SetCurrInstanceLengthOfTxContainer(ContainerId, (uint8)IPDUM_ZERO);

      #if (IPDUM_TX_CONF_CONTAINER == STD_ON)
        /* @Trace: IpduM_SUD_API_165 */
        IpduM_SetTxConfPendingFlag(confIdx, confMask);
      #endif
    }
    else
    {
      /* No action */
    }
  }
  #if (IPDUM_TX_CONF_CONTAINER == STD_ON)
  else
  {
    /* No action */
  }
  #endif
  /* @Trace: IpduM_SUD_API_166 */
  return txResult;
} /* End of IpduM_TxCurrentContainerPdu() */
#endif /* (IPDUM_TX_CONTAINER == STD_ON) */

/*******************************************************************************
** Function Name        :                                                     **
**                                                                            **
** Service ID           : Not applicable                                      **
**                                                                            **
** Description          :                                                     **
**                                                                            **
** Reentrancy           :                                                     **
**                                                                            **
** Input Parameters     :                                                     **
**                                                                            **
** Output Parameters    :                                                     **
**                                                                            **
** Return parameter     :                                                     **
**                                                                            **
** Preconditions        :                                                     **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                                                                            **
**                        Function(s) invoked:                                **
**                                                                            **
*******************************************************************************/
/* @Trace: SWS_IpduM_00195 SWS_IpduM_00189 SWS_IpduM_00190 SWS_IpduM_00191
 * SWS_IpduM_00196  SWS_IpduM_00199 SWS_IpduM_00200
 * SRS_IpduM_02820  SRS_BSW_00009
 */
 
#if (IPDUM_TX_CONTAINER == STD_ON)
LOCAL_INLINE FUNC(void, IPDUM_CODE) IpduM_QueueCurrentContainerPdu(
  IpduM_TxContainerIntType ContainerId, boolean AddedTxContainedFlag)
{
  PduLengthType writeIdx;
  uint8 *ptrTxBuff;
  uint8 errorId;
  /* @Trace: IpduM_SUD_API_167 */
  errorId = IPDUM_E_NO_ERROR;

  /* Before queuing the Dynamic containerPdu, add zero header into
   * if it is not triggertransmit or last-is-best.
   */
  if ((FALSE != IpduM_IsDynamicContainerTx(ContainerId)) &&
      ((FALSE == IpduM_IsTriggerTransmitContainerTx(ContainerId)) ||
        (FALSE == IpduM_IsLastIsBestTxContainerTx(ContainerId))) &&
      ((IpduM_GetMaxInstanceLenOfTxContainer(ContainerId) - \
        IpduM_GetSizeOfCurrInstanceTxContainer(ContainerId)) >= \
        IpduM_GetTxContainerHeaderSize(ContainerId)))
  {
    /* @Trace: IpduM_SUD_API_168 */
    ptrTxBuff = IpduM_GetBasedAddrTxContainerBuffer(ContainerId);
    writeIdx = IpduM_GetWriteCntInstanceTxContainer(ContainerId) * \
               IpduM_GetMaxInstanceLenOfTxContainer(ContainerId) + \
               IpduM_GetSizeOfCurrInstanceTxContainer(ContainerId);
    IpduM_SetData(&ptrTxBuff[writeIdx], (uint8)IPDUM_ZERO, IpduM_GetTxContainerHeaderSize(ContainerId));
  }
  /* @Trace: IpduM_SUD_API_169 */
  SchM_Enter_IpduM_TX_CONTAINER_PROTECTION_AREA();

  /* If queueing a new instance ContainerPdu exceeds the queue size */
  if (((FALSE == AddedTxContainedFlag) && (IpduM_GetCntOfQueuedInstanceTxContainer(ContainerId) >= (IpduM_GetMaxNoOfInstanceTxContainer(ContainerId) - 1))) ||
		                                  ((IpduM_GetCntOfQueuedInstanceTxContainer(ContainerId) >= IpduM_GetMaxNoOfInstanceTxContainer(ContainerId))))
  {
    /* @Trace: IpduM_SUD_API_170 */
    errorId = IPDUM_E_QUEUEOVFL;

    /* Drop the oldest instance or local instance by increase read pointer */
    IpduM_IncReadCntInstanceTxContainer(ContainerId);
    if (IpduM_GetReadCntInstanceTxContainer(ContainerId) >= IpduM_GetMaxNoOfInstanceTxContainer(ContainerId))
    {
      /* @Trace: IpduM_SUD_API_171 */
      IpduM_SetReadCntInstanceTxContainer(ContainerId, (uint8)IPDUM_ZERO);
    }
  }
  else
  {
    /* @Trace: IpduM_SUD_API_172 */
    /* Increase counter of queued containerPdu instance */
    IpduM_IncCntOfQueuedInstanceTxContainer(ContainerId);
  }
  /* @Trace: IpduM_SUD_API_173 */
  /* Increase write pointer for new instance */
  IpduM_IncWriteCntInstanceTxContainer(ContainerId);
  if (IpduM_GetWriteCntInstanceTxContainer(ContainerId) >= IpduM_GetMaxNoOfInstanceTxContainer(ContainerId))
  {
    /* @Trace: IpduM_SUD_API_174 */
    IpduM_SetWriteCntInstanceTxContainer(ContainerId, (uint8)IPDUM_ZERO);
  }

  /* Reset indices for adding containedPdu as new instance is empty */
  /* @Trace: IpduM_SUD_API_175 */
  IpduM_SetCurrInstanceLengthOfTxContainer(ContainerId, (PduLengthType)IPDUM_ZERO);

  SchM_Exit_IpduM_TX_CONTAINER_PROTECTION_AREA();

  if (IPDUM_E_NO_ERROR != errorId)
  {
    /* @Trace: IpduM_SUD_API_176 */
    /* Report to DET with error IPDUM_E_QUEUEOVFL */
    (void)Det_ReportRuntimeError((uint16)IPDUM_MODULE_ID, IPDUM_INSTANCE_ID, IPDUM_TRANSMIT_SID, errorId);
  }
} /* End of IpduM_QueueCurrentContainerPdu() */
#endif /* (IPDUM_TX_CONTAINER == STD_ON) */


/*******************************************************************************
** Function Name        :                                                     **
**                                                                            **
** Service ID           : Not applicable                                      **
**                                                                            **
** Description          :                                                     **
**                                                                            **
** Reentrancy           :                                                     **
**                                                                            **
** Input Parameters     :                                                     **
**                                                                            **
** Output Parameters    :                                                     **
**                                                                            **
** Return parameter     :                                                     **
**                                                                            **
** Preconditions        :                                                     **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                                                                            **
**                        Function(s) invoked:                                **
**                                                                            **
*******************************************************************************/
#if (IPDUM_TX_CONTAINER == STD_ON)
FUNC(void, IPDUM_CODE) IpduM_TriggerContainerPdu(
  IpduM_TxContainerIntType ContainerId, boolean AddedTxContainedFlag)
{
  Std_ReturnType txResult;

  /* @Trace: IpduM_SUD_API_177 */
  txResult = E_NOT_OK;

  /* Request transmission */
  txResult = IpduM_TxCurrentContainerPdu(ContainerId);

  /* Queue the instance of Direct ContainerPdu if transmission failed as per SWS_IpduM_00195
   * or TriggerTransmit ContainerPdu
   */
  if ((E_NOT_OK == txResult) || (FALSE != IpduM_IsTriggerTransmitContainerTx(ContainerId)))
  {
    /* @Trace: IpduM_SUD_API_178 */
    IpduM_QueueCurrentContainerPdu(ContainerId, AddedTxContainedFlag);
  }
  else
  {
    /* No action */
  }

  #if ((IPDUM_TX_CONTAINER_SENDTIMEOUT == STD_ON) || (IPDUM_TX_CONTAINED_SENDTIMEOUT == STD_ON))
    /* @Trace: IpduM_SUD_API_179 */
  SchM_Enter_IpduM_TX_CONTAINER_PROTECTION_AREA();
  if (FALSE != IpduM_IsTimeoutBaseTriggeringForContainerTx(ContainerId))
  {
    /* @Trace: IpduM_SUD_API_180 */
    /* Reset send timeout as ContainerPdu has been sent out or queued */
    IpduM_SetContainerTxPduSendTimer(ContainerId, (uint16)IPDUM_ZERO);
  }
  else
  {
    /* No action */
  }
  /* @Trace: IpduM_SUD_API_181 */
  SchM_Exit_IpduM_TX_CONTAINER_PROTECTION_AREA();
  #endif

} /* End of IpduM_TriggerContainerPdu() */
#endif /* (IPDUM_TX_CONTAINER == STD_ON) */

/*******************************************************************************
** Function Name        :                                                     **
**                                                                            **
** Service ID           : Not applicable                                      **
**                                                                            **
** Description          :                                                     **
**                                                                            **
** Reentrancy           :                                                     **
**                                                                            **
** Input Parameters     :                                                     **
**                                                                            **
** Output Parameters    :                                                     **
**                                                                            **
** Return parameter     :                                                     **
**                                                                            **
** Preconditions        :                                                     **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                                                                            **
**                        Function(s) invoked:                                **
**                                                                            **
*******************************************************************************/
#if (IPDUM_TX_CONTAINER == STD_ON)
LOCAL_INLINE FUNC(void, IPDUM_CODE) IpduM_CheckCurrContainerPduAfterAdding(
  IpduM_TxContainerIntType ContainerId, IpduM_TxContainedIntType ContainedId,
  boolean IsFirstContainedPduAdded)
{
  #if (IPDUM_CONTAINERTX_FIRST_CONTAINEDPDU_TRIGGER == STD_ON)
  PduInfoType pduInfo;
  #endif
  boolean triggerTransmissionFlag;
  /* @Trace: IpduM_SUD_API_182 */
  triggerTransmissionFlag = FALSE;

  if (FALSE != IpduM_IsTxTriggerAlwaysContainedPdu(ContainedId))
  {
    /* @Trace: IpduM_SUD_API_183 */
    /* Trigger the ContainerPdu as SWS_IpduM_00181 */
	  triggerTransmissionFlag = TRUE;
  }
  #if (IPDUM_TX_DYNAMIC_CONTAINER == STD_ON)
  else if ((FALSE != IpduM_IsDynamicContainerTx(ContainerId)) &&
           (IpduM_GetContainerTxSizeThreshold(ContainerId) < IpduM_GetSizeOfCurrInstanceTxContainer(ContainerId)))
  {
    /* @Trace: IpduM_SUD_API_184 */
    /* Trigger the ContainerPdu as SWS_IpduM_00182 */
	  triggerTransmissionFlag = TRUE;
  }
  #endif
  #if (IPDUM_TX_DIRECT_STATIC_CONTAINER == STD_ON)
  /* Trigger static ContainerPdu if trigger mode is direct and all containedPdu were updated by the upper layer */
  else if ((FALSE == IpduM_IsDynamicContainerTx(ContainerId)) && (FALSE == IpduM_IsTriggerTransmitContainerTx(ContainerId)))
  {
    /* @Trace: IpduM_SUD_API_185 */
    IpduM_IncCntOfStaticTxContainedPduUpdatedByUL(ContainerId);
    if (IpduM_GetNoOfContainedPduInContainerTx(ContainerId) == IpduM_GetNoOfStaticTxContainedPduUpdatedByUL(ContainerId))
    {
      /* @Trace: IpduM_SUD_API_186 */
      triggerTransmissionFlag = TRUE;
    }
    else
    {
      /* No action */
    }
  }
  #endif
  else
  {
    /* No action */
  }

  if (FALSE != triggerTransmissionFlag)
  {
    /* @Trace: IpduM_SUD_API_187 */
    IpduM_TriggerContainerPdu(ContainerId, TRUE);

    #if (IPDUM_TX_DIRECT_STATIC_CONTAINER == STD_ON)
      /* @Trace: IpduM_SUD_API_188 */
    IpduM_ClearCntOfStaticTxContainedPduUpdatedByUL(ContainerId);
    #endif
  }
  else
  {
    
    /* If first ContainedPdu trigger is true, invoke PduR_IpduMTransmit as per SWS_IpduM_00201  */
    if (FALSE != IsFirstContainedPduAdded)
    {
      #if (IPDUM_CONTAINERTX_FIRST_CONTAINEDPDU_TRIGGER == STD_ON)
      if (FALSE != IpduM_IsContainerTxFirstContainedPduTrigger(ContainerId))
      {
        /* @Trace: IpduM_SUD_API_189 */
        pduInfo.SduDataPtr = IpduM_GetBasedAddrTxContainerBuffer(ContainerId);
        #if ((IPDUM_TX_LASTISBEST_CONTAINER == STD_ON) && (IPDUM_TX_TRIGGERTRANSMIT_CONTAINER == STD_ON))
        /*
          * If ContainerPdu is last-is-best and trigger mode is triggertransmit
          * the payload size is maximum container length. Otherwise adjust the
          * overall size.
          */
        if ((FALSE != IpduM_IsLastIsBestTxContainerTx(ContainerId)) &&
            (FALSE != IpduM_IsTriggerTransmitContainerTx(ContainerId)))
        {
          
          /* @Trace: IpduM_SUD_API_190 */
          pduInfo.SduLength = IpduM_GetMaxInstanceLenOfTxContainer(ContainerId);
        }
        else
        #endif /* ((IPDUM_TX_LASTISBEST_CONTAINER == STD_ON) && (IPDUM_TX_TRIGGERTRANSMIT_CONTAINER == STD_ON)) */
        {
          
          /* @Trace: IpduM_SUD_API_191 */
          pduInfo.SduLength = IpduM_GetSizeOfCurrInstanceTxContainer(ContainerId);
          #if (IPDUM_TX_CONF_CONTAINER == STD_ON)
          /* If transmission confirmation for ContainerPdu configured */
            /* @Trace: IpduM_SUD_API_192 */
            /* Store index of containedPdu for TxConfirmation */
            IpduM_SetContainedTxPduIdxToConfBuf(IpduM_GetContainerTxPduConfBufIdx(ContainerId), ContainedId);
          #endif
        }
        #if (IPDUM_META_DATA_SUPPORT == STD_ON)
        /* Use the MetaData last collected from the contained I-PDUs */
        if (FALSE != IpduM_IsTxContainerMetaDataSupport(ContainerId))
        {
          
          /* @Trace: IpduM_SUD_API_193 */
          pduInfo.MetaDataPtr = IpduM_GetBasedAddrTxContainerMetaDataBuffer(ContainerId);
        }
        else
        {
          /* No action */
        }
        #endif
        
        /* @Trace: IpduM_SUD_API_194 */
        (void)PduR_IpduMTransmit(IpduM_GetTxContainerRefPduId(ContainerId), &pduInfo);
        
        #if (IPDUM_TX_DIRECT_STATIC_CONTAINER == STD_ON)
          /* @Trace: IpduM_SUD_API_195 */
        IpduM_ClearCntOfStaticTxContainedPduUpdatedByUL(ContainerId);
        #endif
      }
      else
      {
        /* No action */
      }
      #endif /* (IPDUM_CONTAINERTX_FIRST_CONTAINEDPDU_TRIGGER == STD_ON) */

      #if (IPDUM_TX_CONTAINER_SENDTIMEOUT == STD_ON)
        /* @Trace: IpduM_SUD_API_196 */
      SchM_Enter_IpduM_TX_CONTAINER_PROTECTION_AREA();
      /* Initiate the transmission timer as per SWS_IpduM_00184 */
      if ((FALSE != IpduM_IsTimeoutBaseTriggeringForContainerTx(ContainerId)) &&
          ((uint16)IPDUM_ZERO < IpduM_GetContainerTxSendTimeout(ContainerId)))
      {
        /* @Trace: IpduM_SUD_API_197 */
        IpduM_SetContainerTxPduSendTimer(ContainerId, IpduM_GetContainerTxSendTimeout(ContainerId));
      }
      /* @Trace: IpduM_SUD_API_198 */
      SchM_Exit_IpduM_TX_CONTAINER_PROTECTION_AREA();
      #endif /* (IPDUM_TX_CONTAINER_SENDTIMEOUT == STD_ON) */
    }
    else
    {
      /* No action */
    }

    #if (IPDUM_TX_CONTAINED_SENDTIMEOUT == STD_ON)
    /* @Trace: IpduM_SUD_API_199 */
    SchM_Enter_IpduM_TX_CONTAINER_PROTECTION_AREA();
    /* Adapt the transmission timer as SWS_IpduM_00184 and SWS_IpduM_00185 */
    if (((FALSE != IpduM_IsTimeoutBaseTriggeringForContainerTx(ContainerId)) &&
        (IpduM_GetContainerTxPduSendTimer(ContainerId) > IpduM_GetContainedTxPduSendTimeout(ContainedId))) ||
        ((uint16)IPDUM_ZERO == IpduM_GetContainerTxPduSendTimer(ContainerId)))
    {
      /* @Trace: IpduM_SUD_API_200 */
      IpduM_SetContainerTxPduSendTimer(ContainerId, IpduM_GetContainedTxPduSendTimeout(ContainedId));
    }
    /* @Trace: IpduM_SUD_API_201 */
    SchM_Exit_IpduM_TX_CONTAINER_PROTECTION_AREA();
    #endif /* (IPDUM_TX_CONTAINED_SENDTIMEOUT == STD_ON) */
  }
} /* End of IpduM_CheckCurrContainerPduAfterAdding() */
#endif /* (IPDUM_TX_CONTAINER == STD_ON) */
/*******************************************************************************
** Function Name        :                                                     **
**                                                                            **
** Service ID           : Not applicable                                      **
**                                                                            **
** Description          :                                                     **
**                                                                            **
** Reentrancy           :                                                     **
**                                                                            **
** Input Parameters     :                                                     **
**                                                                            **
** Output Parameters    :                                                     **
**                                                                            **
** Return parameter     :                                                     **
**                                                                            **
** Preconditions        :                                                     **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                                                                            **
**                        Function(s) invoked:                                **
**                                                                            **
*******************************************************************************/
/* @Trace: SWS_IpduM_00181 SWS_IpduM_00201 SWS_IpduM_00184 SWS_IpduM_00185
 * SWS_IpduM_00186 SWS_IpduM_00188 SWS_IpduM_00192
 * SWS_IpduM_00179 SWS_IpduM_00180 SWS_IpduM_00182 SWS_IpduM_00183
 * SWS_IpduM_00187
 * SWS_IpduM_00234 SWS_IpduM_00235 SWS_IpduM_00233
 * SRS_IpduM_02820 SRS_IpduM_02825 SRS_BSW_00323
 */

#if (IPDUM_TX_CONTAINER == STD_ON)
FUNC(Std_ReturnType, IPDUM_CODE) IpduM_ContainerTransmit(
  IpduM_TxContainedIntType ContainedId,
  P2CONST(PduInfoType, AUTOMATIC, IPDUM_APPL_DATA) PduInfoPtr)
{
  IpduM_TxContainerIntType containerId;
  PduLengthType pduLength;
  PduLengthType headerSize;
  Std_ReturnType retVal;
  boolean firstContainedPdu;
  boolean addedFlag;
  IpduM_TxContainedIntType addedFlagPos;
  uint8 addedFlagMask;
  PduLengthType currInsLength;
  #if (IPDUM_TX_DYNAMIC_CONTAINER == STD_ON)
  PduLengthType maxInsLength;
  #endif
  /* @Trace: IpduM_SUD_API_202 */
  retVal = E_NOT_OK;
  containerId = IpduM_GetContainerTxIdx(ContainedId);
  pduLength = PduInfoPtr->SduLength;
  headerSize = (PduLengthType)IpduM_GetTxContainerHeaderSize(containerId);

  #if (IPDUM_DEV_ERROR_DETECT == STD_ON)
  if (
    #if (IPDUM_TX_SHORT_HEADER_CONTAINER == STD_ON)
    ((IPDUM_MAX_SHORT_PDU_LENGTH < pduLength) && (IPDUM_HEADERTYPE_SHORT == (uint8)headerSize)) ||
    #endif
    (IpduM_GetMaxInstanceLenOfTxContainer(containerId) < (pduLength + headerSize)))
  {
    /* @Trace: IpduM_SUD_API_203 */
    (void)Det_ReportError((uint16)IPDUM_MODULE_ID, IPDUM_INSTANCE_ID, IPDUM_TRANSMIT_SID, IPDUM_E_PARAM);
  }
  else
  #endif
  {
    /* @Trace: IpduM_SUD_API_204 */
    SchM_Enter_IpduM_TX_CONTAINER_PROTECTION_AREA();
    if (IPDUM_TX_CONTAINER_UNLOCK == IpduM_GetTxContainerProtection(containerId))
    {
      /* @Trace: IpduM_SUD_API_205 */
      IpduM_SetTxContainerProtection(containerId, IPDUM_TX_CONTAINER_LOCK);
      SchM_Exit_IpduM_TX_CONTAINER_PROTECTION_AREA();

      #if (IPDUM_META_DATA_SUPPORT == STD_ON)
      /* Store the MetaData last collected from the contained I-PDUs */
      if ((FALSE != IpduM_IsTxContainerMetaDataSupport(containerId)) &&
          (NULL_PTR != PduInfoPtr->MetaDataPtr))
      {
        /* @Trace: IpduM_SUD_API_206 */
        IpduM_CopyData(PduInfoPtr->MetaDataPtr,
                      IpduM_GetBasedAddrTxContainerMetaDataBuffer(containerId),
                      IpduM_GetTxContainerMetaDataLength(containerId));
      }
      #endif
      /* @Trace: IpduM_SUD_API_207 */
      retVal = E_OK;
      addedFlag = FALSE;
      firstContainedPdu = FALSE;
      #if ((IPDUM_TX_LASTISBEST_CONTAINER == STD_ON) && (IPDUM_TX_QUEUED_CONTAINER == STD_ON))
      if (FALSE != IpduM_IsLastIsBestTxContainerTx(containerId))
      #endif
      {
        /* @Trace: IpduM_SUD_API_208 */
        #if (IPDUM_TX_LASTISBEST_CONTAINER == STD_ON)
        addedFlagPos = IpduM_GetLIBAddedFlagIdxOfTxContainedPdu(ContainedId);
        addedFlagMask = IpduM_GetLIBAddedFlagMaskOfTxContainedPdu(ContainedId);

        addedFlag = IpduM_GetLIBAddedFlagBuffer(addedFlagPos) & addedFlagMask;
        #endif /* (IPDUM_TX_LASTISBEST_CONTAINER == STD_ON) */
      }
      #if ((IPDUM_TX_LASTISBEST_CONTAINER == STD_ON) && (IPDUM_TX_QUEUED_CONTAINER == STD_ON))
      else
      {
        /* No action */
      }
      #endif

      #if (IPDUM_TX_LASTISBEST_CONTAINER == STD_ON)
      if (FALSE == addedFlag)
      #endif
      {
        /* Add ContainedPdu to ContainerPdu */
        #if ((IPDUM_TX_LASTISBEST_CONTAINER == STD_ON) && (IPDUM_TX_QUEUED_CONTAINER == STD_ON))
        if (FALSE != IpduM_IsLastIsBestTxContainerTx(containerId))
        #endif
        {
          #if (IPDUM_TX_LASTISBEST_CONTAINER == STD_ON)
          /* @Trace: IpduM_SUD_API_209*/
          SchM_Enter_IpduM_TX_CONTAINER_PROTECTION_AREA();
          IpduM_SetLIBAddedFlagOfTxContainedPdu(addedFlagPos, addedFlagMask);
          SchM_Exit_IpduM_TX_CONTAINER_PROTECTION_AREA();
          #endif /* (IPDUM_TX_LASTISBEST_CONTAINER == STD_ON) */
        }
        /* @Trace: IpduM_SUD_API_210*/
        headerSize = (PduLengthType)IpduM_GetTxContainerHeaderSize(containerId);
        currInsLength = IpduM_GetSizeOfCurrInstanceTxContainer(containerId);

        #if (IPDUM_TX_DYNAMIC_CONTAINER == STD_ON)
        maxInsLength = IpduM_GetMaxInstanceLenOfTxContainer(containerId);

        /* Transmit or Queue the Dynamic Container if adding this ContainedPdu
         * would exceed maximum size of ContainerPdu as per SWS_IpduM_00182
         * SWS_IpduM_00183 */
        if ((FALSE != IpduM_IsDynamicContainerTx(containerId)) &&
            (maxInsLength < (pduLength + headerSize + currInsLength)))
        {
          /*
           * SWS_IpduM_00182: If trigger mode is direct, first the containerPdu shall be triggered
           * SWS_IpduM_00183: If trigger mode is triggertransmit, first the containerPdu shall be queued
           */
          if (FALSE != IpduM_IsTriggerTransmitContainerTx(containerId))
          {
            /* @Trace: IpduM_SUD_API_211*/
            IpduM_QueueCurrentContainerPdu(containerId, FALSE);
          }
          else
          {
            /* @Trace: IpduM_SUD_API_212 */
            IpduM_TriggerContainerPdu(containerId, FALSE);
          }
        }
        #endif

        if (((PduLengthType)IPDUM_ZERO == currInsLength) &&
            ((uint8)IPDUM_ZERO == IpduM_GetCntOfQueuedInstanceTxContainer(containerId)))
        {
          /* @Trace: IpduM_SUD_API_213 */
          firstContainedPdu = TRUE;
        }

        /* Add ContainedPdu to new or current instance of ContainerPdu */
        /* @Trace: IpduM_SUD_API_214 */
        IpduM_AddContainedPdu(containerId, ContainedId, PduInfoPtr);
      }
      /* After adding containedPdu, check trigger conditions of containerPdu */
      /* @Trace: IpduM_SUD_API_215 */
      IpduM_CheckCurrContainerPduAfterAdding(containerId, ContainedId, firstContainedPdu);
      /* @Trace: IpduM_SUD_API_216 */
      SchM_Enter_IpduM_TX_CONTAINER_PROTECTION_AREA();
      IpduM_SetTxContainerProtection(containerId, IPDUM_TX_CONTAINER_UNLOCK);
    }
    else
    {
      /* No action */
    }
    /* @Trace: IpduM_SUD_API_217 */
    SchM_Exit_IpduM_TX_CONTAINER_PROTECTION_AREA();
  }
  /* @Trace: IpduM_SUD_API_218 */
  return retVal;
} /* End of IpduM_ContainerTransmit() */
#endif /* (IPDUM_TX_CONTAINER == STD_ON) */

/*******************************************************************************
** Function Name        :                                                     **
**                                                                            **
** Service ID           : Not applicable                                      **
**                                                                            **
** Description          :                                                     **
**                                                                            **
** Reentrancy           :                                                     **
**                                                                            **
** Input Parameters     :                                                     **
**                                                                            **
** Output Parameters    :                                                     **
**                                                                            **
** Return parameter     :                                                     **
**                                                                            **
** Preconditions        :                                                     **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                                                                            **
**                        Function(s) invoked:                                **
**                                                                            **
*******************************************************************************/
#if (IPDUM_TX_CONTAINER == STD_ON)
#if (IPDUM_TX_TRIGGERTRANS_CONTAINER == STD_ON)
FUNC(Std_ReturnType, IPDUM_CODE) IpduM_ContainerTriggerTransmit(
  IpduM_TxContainerIntType ContainerId,
  P2VAR(PduInfoType, AUTOMATIC, IPDUM_APPL_DATA) PduInfoPtr)
{
  Std_ReturnType retVal;
  PduLengthType readIdx;
  const uint8 *ptrTxBuff;

  /* SWS_IpduM_00194 */
  if ((IpduM_GetMaxInstanceLenOfTxContainer(ContainerId) <= PduInfoPtr->SduLength) &&
      (((uint8)IPDUM_ZERO < IpduM_GetCntOfQueuedInstanceTxContainer(ContainerId)) ||  /* Queue is not empty */
       ((PduLengthType)IPDUM_ZERO < IpduM_GetSizeOfCurrInstanceTxContainer(ContainerId)))) /* Current instance is existing */
  {
    /* @Trace: IpduM_SUD_API_219 */
    /* Initiate return value as "ok" */
    retVal = E_OK;

    SchM_Enter_IpduM_TX_CONTAINER_PROTECTION_AREA();
    if (IPDUM_TX_CONTAINER_UNLOCK == IpduM_GetTxContainerProtection(ContainerId))
    {
      /* @Trace: IpduM_SUD_API_220 */
      IpduM_SetTxContainerProtection(ContainerId, IPDUM_TX_CONTAINER_LOCK);

      /* Use the buffer of lower layer to update the latest of containedPDUs */
      if (FALSE != IpduM_IsLastIsBestTxContainerTx(ContainerId))
      {
        /* @Trace: IpduM_SUD_API_221 */
        IpduM_UpdateLIBContainer(ContainerId, PduInfoPtr);
      }
      else
      {
        /* @Trace: IpduM_SUD_API_222 */
        ptrTxBuff = IpduM_GetBasedAddrTxContainerBuffer(ContainerId);
        readIdx = IpduM_GetReadCntInstanceTxContainer(ContainerId) * IpduM_GetMaxInstanceLenOfTxContainer(ContainerId);
        /* If has no queued instance, use the current instance */
        if ((uint8)IPDUM_ZERO == IpduM_GetCntOfQueuedInstanceTxContainer(ContainerId))
        {
          /* @Trace: IpduM_SUD_API_223 */
          PduInfoPtr->SduLength = IpduM_GetSizeOfCurrInstanceTxContainer(ContainerId);
        }
        else
        {
          /* @Trace: IpduM_SUD_API_224 */
          PduInfoPtr->SduLength = IpduM_CalculateContainerSize(ContainerId, &ptrTxBuff[readIdx]);
        }
        /* @Trace: IpduM_SUD_API_225 */
        IpduM_CopyData(&ptrTxBuff[readIdx], PduInfoPtr->SduDataPtr, PduInfoPtr->SduLength);

        #if (IPDUM_TX_CONF_CONTAINER == STD_ON)
        /* Store the index of containedPdus in the sent out containerPdu */
        /* @Trace: IpduM_SUD_API_226 */
        IpduM_StoreContainedPduIdxForConf(ContainerId, PduInfoPtr);
        #endif
      }

      #if (IPDUM_META_DATA_SUPPORT == STD_ON)
      /* Store the MetaData last collected from the contained I-PDUs */
      if ((FALSE != IpduM_IsTxContainerMetaDataSupport(ContainerId)) &&
          (NULL_PTR != PduInfoPtr->MetaDataPtr))
      {
        /* @Trace: IpduM_SUD_API_227 */
        IpduM_CopyData(PduInfoPtr->MetaDataPtr,
                      IpduM_GetBasedAddrTxContainerMetaDataBuffer(ContainerId),
                      IpduM_GetTxContainerMetaDataLength(ContainerId));
      }
      #endif

      /* If has no queued instance */
      if ((uint8)IPDUM_ZERO == IpduM_GetCntOfQueuedInstanceTxContainer(ContainerId))
      {
        /* @Trace: IpduM_SUD_API_228 */
        /* Reset the current instance */
        IpduM_SetCurrInstanceLengthOfTxContainer(ContainerId, (PduLengthType)IPDUM_ZERO);

        #if ((IPDUM_TX_CONTAINER_SENDTIMEOUT == STD_ON) || (IPDUM_TX_CONTAINED_SENDTIMEOUT == STD_ON))
        if (FALSE != IpduM_IsTimeoutBaseTriggeringForContainerTx(ContainerId))
        {
          /* @Trace: IpduM_SUD_API_229 */
          IpduM_SetContainerTxPduSendTimer(ContainerId, (uint16)IPDUM_ZERO);
        }
        #endif
      }
      else
      {
        /* @Trace: IpduM_SUD_API_230 */
        /* Increase read pointer */
        IpduM_IncReadCntInstanceTxContainer(ContainerId);
        if (IpduM_GetMaxNoOfInstanceTxContainer(ContainerId) <= IpduM_GetReadCntInstanceTxContainer(ContainerId))
        {
          /* @Trace: IpduM_SUD_API_231 */
          IpduM_SetReadCntInstanceTxContainer(ContainerId, (uint8)IPDUM_ZERO);
        }
        /* Drop the containerPdu from the queue */
        /* @Trace: IpduM_SUD_API_232 */
        IpduM_DecCntOfQueuedInstanceTxContainer(ContainerId);
      }
      /* @Trace: IpduM_SUD_API_233 */
      IpduM_SetTxContainerProtection(ContainerId, IPDUM_TX_CONTAINER_UNLOCK);
    }
    else
    {
      /* No action */
    }
    /* @Trace: IpduM_SUD_API_234 */
    SchM_Exit_IpduM_TX_CONTAINER_PROTECTION_AREA();
  }
  else
  {
    /* @Trace: IpduM_SUD_API_235 */
    /* Return E_NOT_OK if ContainerPdu is empty */
    retVal = E_NOT_OK;
  }
  /* @Trace: IpduM_SUD_API_236 */
  return retVal;
} /* End of IpduM_ContainerTriggerTransmit() */
#endif /* (IPDUM_TX_TRIGGERTRANS_CONTAINER == STD_ON) */
#endif /* (IPDUM_TX_CONTAINER == STD_ON) */

/*******************************************************************************
** Function Name        :                                                     **
**                                                                            **
** Service ID           : Not applicable                                      **
**                                                                            **
** Description          :                                                     **
**                                                                            **
** Reentrancy           :                                                     **
**                                                                            **
** Input Parameters     :                                                     **
**                                                                            **
** Output Parameters    :                                                     **
**                                                                            **
** Return parameter     :                                                     **
**                                                                            **
** Preconditions        :                                                     **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                                                                            **
**                        Function(s) invoked:                                **
**                                                                            **
*******************************************************************************/
#if (IPDUM_TX_CONTAINER == STD_ON)
#if (IPDUM_TX_CONF_CONTAINER == STD_ON)
FUNC(void, IPDUM_CODE) IpduM_ContainerTxConfirmation(
  IpduM_TxContainerIntType ContainerId, Std_ReturnType result)
{
  IpduM_TxContainedIntType confIdx;
  uint8 confMask;
  IpduM_TxContainedIntType containedId;
  IpduM_TxContainedIntType noOfContainedPdu;
  IpduM_TxContainedIntType confReadIdx;

  /* @Trace: IpduM_SUD_API_237 */
  confIdx = IpduM_GetContainerByteIdxOfTxConfPendingFlagBuf(ContainerId);
  confMask = IpduM_GetContainerByteMaskOfTxConfPendingFlagBuf(ContainerId);
  if ((uint8)IPDUM_ZERO != IpduM_GetTxConfPendingFlag(confIdx, confMask))
  {
    /* @Trace: IpduM_SUD_API_238 */
    confReadIdx = IpduM_GetContainerTxPduConfBufIdx(ContainerId);
    noOfContainedPdu = IpduM_GetNoOfContainedPduInContainerTx(ContainerId);
    while ((IpduM_TxContainedIntType)IPDUM_ZERO < noOfContainedPdu)
    {
      /* @Trace: IpduM_SUD_API_239 */
      containedId = IpduM_GetContainedTxPduIdxFromConfBuf(confReadIdx);
      if (IPDUM_TXCONTAINED_INVALID_IDX != containedId)
      {
        /* @Trace: IpduM_SUD_API_240 */
        /* Invoke TxConfirmation of upper layer */
        IpduM_UpTxConfFunc(IpduM_GetTxContainedRefPduId(containedId), result);
        /* Reset stored index of containedPdu */
        IpduM_SetContainedTxPduIdxToConfBuf(confReadIdx, IPDUM_TXCONTAINED_INVALID_IDX);
        confReadIdx++;
        noOfContainedPdu--;
      }
      else
      {
        /* @Trace: IpduM_SUD_API_241 */
        /* Break the loop */
        noOfContainedPdu = (IpduM_TxContainedIntType)IPDUM_ZERO;
      }
    }
    /* @Trace: IpduM_SUD_API_242 */
    /* Clear TxConfirmation Pending flag */
    IpduM_ClearTxConfPendingFlag(confIdx, confMask);
  }
  else
  {
    /* No action */
  }
}
#endif /* (IPDUM_TX_CONF_CONTAINER == STD_ON) */
#endif /* (IPDUM_TX_CONTAINER == STD_ON) */


/*******************************************************************************
**           Internal functions for Rx Container Pdu                          **
*******************************************************************************/
#if (IPDUM_RX_CONTAINER == STD_ON)
#if (IPDUM_RX_DYNAMIC_CONTAINER == STD_ON)
LOCAL_INLINE FUNC(IpduM_RxContainedIntType, IPDUM_CODE) IpduM_SearchRxContained(
  IpduM_RxContainerIntType ContainerId, uint32 HeaderId);

static FUNC(void, IPDUM_CODE) IpduM_ExtractRxDynamicContainerPdu(
  uint8 ApiId, IpduM_RxContainerIntType ContainerId,
  P2CONST(PduInfoType, AUTOMATIC, IPDUM_APPL_DATA) PduInfoPtr);
#endif

#if (IPDUM_RX_STATIC_CONTAINER== STD_ON)
static FUNC(void, IPDUM_CODE) IpduM_ExtractRxStaticContainerPdu(
  uint8 ApiId, IpduM_RxContainerIntType ContainerId,
  P2CONST(PduInfoType, AUTOMATIC, IPDUM_APPL_DATA) PduInfoPtr);
#endif

#if (IPDUM_RX_DEFFERRED_CONTAINER == STD_ON)
LOCAL_INLINE FUNC(void, IPDUM_CODE) IpduM_EnqueueRxContainerPdu(
  IpduM_RxContainerIntType ContainerId,
  P2CONST(PduInfoType, AUTOMATIC, IPDUM_APPL_DATA) PduInfoPtr);
#endif
#endif /*(IPDUM_RX_CONTAINER == STD_ON) */

/*******************************************************************************
** Function Name        :                                                     **
**                                                                            **
** Service ID           : Not applicable                                      **
**                                                                            **
** Description          :                                                     **
**                                                                            **
** Reentrancy           :                                                     **
**                                                                            **
** Input Parameters     :                                                     **
**                                                                            **
** Output Parameters    :                                                     **
**                                                                            **
** Return parameter     :                                                     **
**                                                                            **
** Preconditions        :                                                     **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                                                                            **
**                        Function(s) invoked:                                **
**                                                                            **
*******************************************************************************/
#if ((IPDUM_RX_CONTAINER == STD_ON) && (IPDUM_RX_DYNAMIC_CONTAINER == STD_ON))
LOCAL_INLINE FUNC(IpduM_RxContainedIntType, IPDUM_CODE) IpduM_SearchRxContained(
  IpduM_RxContainerIntType ContainerId, uint32 HeaderId)
{
  IpduM_RxContainedIntType count;
  IpduM_RxContainedIntType currContainedId;
  IpduM_RxContainedIntType retContainedId;

  /* @Trace: IpduM_SUD_API_243 */
  retContainedId = IPDUM_RXCONTAINED_INVALID_IDX;
  count = IpduM_GetNoOfContainedPduInRxContainer(ContainerId);
  currContainedId = IpduM_GetFirstContainedPduOfRxContainer(ContainerId);

  while ((IpduM_RxContainedIntType)IPDUM_ZERO < count)
  {

    if (IpduM_GetRxContainedHeaderId(currContainedId) == HeaderId)
    {
      /* @Trace: IpduM_SUD_API_244 */
      retContainedId = currContainedId;
      /* Break the loop */
      count = (IpduM_RxContainedIntType)IPDUM_ZERO;
    }
    else
    {
      /* @Trace: IpduM_SUD_API_245 */
      currContainedId++;
      count--;
    }
  }
  /* @Trace: IpduM_SUD_API_246 */
  return retContainedId;
} /* End of IpduM_SearchRxContainedPdu() */
#endif /*(IPDUM_RX_CONTAINER == STD_ON) */

/*******************************************************************************
** Function Name        :                                                     **
**                                                                            **
** Service ID           : Not applicable                                      **
**                                                                            **
** Description          :                                                     **
**                                                                            **
** Reentrancy           :                                                     **
**                                                                            **
** Input Parameters     :                                                     **
**                                                                            **
** Output Parameters    :                                                     **
**                                                                            **
** Return parameter     :                                                     **
**                                                                            **
** Preconditions        :                                                     **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                                                                            **
**                        Function(s) invoked:                                **
**                                                                            **
*******************************************************************************/
/* @Trace: SWS_IpduM_00204 SWS_IpduM_00206 SWS_IpduM_00251 SWS_IpduM_00207
 * SWS_IpduM_00208 SWS_IpduM_00210
 * SWS_IpduM_00228 SWS_IpduM_00229
 * SWS_IpduM_00213 SWS_IpduM_00214
 * SRS_IpduM_02820 SRS_IpduM_02824
 * SRS_IpduM_02822
 */

#if (IPDUM_RX_CONTAINER == STD_ON)
#if (IPDUM_RX_DYNAMIC_CONTAINER == STD_ON)
static FUNC(void, IPDUM_CODE) IpduM_ExtractRxDynamicContainerPdu(
  uint8 ApiId, IpduM_RxContainerIntType ContainerId,
  P2CONST(PduInfoType, AUTOMATIC, IPDUM_APPL_DATA) PduInfoPtr)
{
  PduInfoType pduInfo;
  PduLengthType headerSize;
  PduLengthType readIdx;
  IpduM_HeaderFieldType header;
  IpduM_RxContainedIntType containedId;

  /* @Trace: IpduM_SUD_API_247 */
  headerSize = IpduM_GetRxContainerHeaderSize(ContainerId);
  readIdx = (PduLengthType)IPDUM_ZERO;
  while (PduInfoPtr->SduLength >= (readIdx + headerSize))
  {
    /* @Trace: IpduM_SUD_API_248 */
    IpduM_ReadContainerHeader(&(PduInfoPtr->SduDataPtr[readIdx]), &header, (uint8)headerSize);

    /* If the payload length exceeds the remaining bytes of the container
     * the processing for this Container PDU shall be stopped
     */
    if ((PduInfoPtr->SduLength - readIdx - headerSize) < (PduLengthType)header.Dlc)
    {
      /* @Trace: IpduM_SUD_API_249 */
      /* Report to DET with runtime error IPDUM_E_HEADER */
      (void)Det_ReportRuntimeError((uint16)IPDUM_MODULE_ID, IPDUM_INSTANCE_ID, ApiId, IPDUM_E_HEADER);
      /* Break the loop */
      readIdx = PduInfoPtr->SduLength;
    }
    else
    {
      /* @Trace: IpduM_SUD_API_250 */
      /* Indicate the reception of containedPdu to upper layer */

      pduInfo.SduDataPtr = &(PduInfoPtr->SduDataPtr[readIdx + headerSize]);
      pduInfo.SduLength = header.Dlc;
      #if (IPDUM_META_DATA_SUPPORT == STD_ON)
      /* Check if contained I-PDU that support MetaData. */
      if (FALSE != IpduM_IsRxContainedPduSupportMetaData(containedId))
      {
        /* @Trace: IpduM_SUD_API_251 */
        pduInfo.MetaDataPtr = PduInfoPtr->MetaDataPtr;
      }
      else
      {
        /* @Trace: IpduM_SUD_API_252 */
        pduInfo.MetaDataPtr = NULL_PTR;
      }
      #endif
      /* @Trace: IpduM_SUD_API_253 */
      containedId = IpduM_SearchRxContained(ContainerId, header.HeaderId);
      if (IPDUM_RXCONTAINED_INVALID_IDX != containedId)
      {
        /* @Trace: IpduM_SUD_API_254 */
        IpduM_UpRxIndFunc(IpduM_GetRxContainedRefPduId(containedId), &pduInfo);
      }
      else
      {
        /* No action */
      }
      /* Increase read index */
      /* @Trace: IpduM_SUD_API_255 */
      readIdx += headerSize + (PduLengthType)header.Dlc;
    }
  }
} /* End of IpduM_ExtractRxDynamicContainerPdu() */
#endif /* (IPDUM_RX_DYNAMIC_CONTAINER == STD_ON) */
#endif /*(IPDUM_RX_CONTAINER == STD_ON) */

/*******************************************************************************
** Function Name        :                                                     **
**                                                                            **
** Service ID           : Not applicable                                      **
**                                                                            **
** Description          :                                                     **
**                                                                            **
** Reentrancy           :                                                     **
**                                                                            **
** Input Parameters     :                                                     **
**                                                                            **
** Output Parameters    :                                                     **
**                                                                            **
** Return parameter     :                                                     **
**                                                                            **
** Preconditions        :                                                     **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                                                                            **
**                        Function(s) invoked:                                **
**                                                                            **
*******************************************************************************/
/* @Trace: SWS_IpduM_00236
 * SWS_IpduM_00228 SWS_IpduM_00229
 * SWS_IpduM_00237
 * SRS_IpduM_02825 SRS_IpduM_02800
 */

#if (IPDUM_RX_CONTAINER == STD_ON)
#if (IPDUM_RX_STATIC_CONTAINER== STD_ON)
static FUNC(void, IPDUM_CODE) IpduM_ExtractRxStaticContainerPdu(
  uint8 ApiId, IpduM_RxContainerIntType ContainerId,
  P2CONST(PduInfoType, AUTOMATIC, IPDUM_APPL_DATA) PduInfoPtr)
{
  PduInfoType pduInfo;
  IpduM_RxContainedIntType readCnt;
  PduLengthType readIdx;
  IpduM_RxContainedIntType currContainedId;
  PduLengthType upByteIdx;
  uint8 upByteMask;

  /* If all containedPDUs are completely contained in the Rx ContainerPDU */
  if (IpduM_GetMinSizeOfInstanceRxContainer(ContainerId) <= PduInfoPtr->SduLength)
  {
    /* @Trace: IpduM_SUD_API_256 */
    readCnt = (IpduM_RxContainedIntType)IPDUM_ZERO;
    while (IpduM_GetNoOfContainedPduInRxContainer(ContainerId) > readCnt)
    {
      /* @Trace: IpduM_SUD_API_257 */
      currContainedId = IpduM_GetFirstContainedPduOfRxContainer(ContainerId) + readCnt;

      upByteIdx = IpduM_GetStaticRxContainedUpdateBitBytePos(currContainedId);
      upByteMask = IpduM_GetStaticRxContainedUpdateBitByteMask(currContainedId);

      /* Only process and indicate ContainedRxPdu to the upper layer if its received update-bit is set */
      if ((FALSE == IpduM_IsRxContainedUpdateBitConfigured(currContainedId)) ||
    	  ((uint8)IPDUM_ZERO != (PduInfoPtr->SduDataPtr[upByteIdx] & upByteMask)))
      {
        /* @Trace: IpduM_SUD_API_258 */
        readIdx = IpduM_GetStaticRxContainedPduOffset(currContainedId);

        pduInfo.SduDataPtr = &PduInfoPtr->SduDataPtr[readIdx];
        #if (IPDUM_META_DATA_SUPPORT == STD_ON)
        /* Check if contained I-PDU that support MetaData. */
        if (FALSE != IpduM_IsRxContainedPduSupportMetaData(currContainedId))
        {
          /* @Trace: IpduM_SUD_API_259 */
          pduInfo.MetaDataPtr = PduInfoPtr->MetaDataPtr;
        }
        else
        {
          /* @Trace: IpduM_SUD_API_260 */
          pduInfo.MetaDataPtr = NULL_PTR;
        }
        #endif
        /* If ContainedRxPdu is the last PDU contained in Rx ContainerPdu */
        if (IpduM_GetNoOfContainedPduInRxContainer(ContainerId) == \
                                (readCnt + (IpduM_RxContainedIntType)IPDUM_ONE))
        {
          /* @Trace: IpduM_SUD_API_261 */
          /* Get actual received length of the last containedPdu */
          pduInfo.SduLength  = PduInfoPtr->SduLength - readIdx;
        }
        else
        {
          /* @Trace: IpduM_SUD_API_262 */
          /* Get the fixed length of ContainedPdu */
          pduInfo.SduLength = IpduM_GetMaxLengthOfStaticRxContainedPdu(currContainedId);
        }
        /* Indicate the receiption of containedPdu to upper layer */
        /* @Trace: IpduM_SUD_API_263 */
        IpduM_UpRxIndFunc(IpduM_GetRxContainedRefPduId(currContainedId), &pduInfo);
      }
      else
      {
        /* No action */
      }
      /* Increase to next containedPdu */
      /* @Trace: IpduM_SUD_API_264 */
      readCnt++;
    } /* End while loop of all Static containedPdu */
  }
  else
  {
    /* Ignore all contained PDUs that are according to their configuration not
     * or not completely contained in the received Container PDU. Report to DET
     * with error IPDUM_E_CONTAINER if Development Error Detection is configured
     */
    #if (IPDUM_DEV_ERROR_DETECT == STD_ON)
      /* @Trace: IpduM_SUD_API_265 */
    (void)Det_ReportError((uint16)IPDUM_MODULE_ID, IPDUM_INSTANCE_ID, ApiId, IPDUM_E_CONTAINER);
    #endif
  }
} /* End of IpduM_ExtractRxStaticContainerPdu() */
#endif /* (IPDUM_RX_STATIC_CONTAINER== STD_ON) */
#endif /*(IPDUM_RX_CONTAINER == STD_ON) */

/*******************************************************************************
** Function Name        :                                                     **
**                                                                            **
** Service ID           : Not applicable                                      **
**                                                                            **
** Description          :                                                     **
**                                                                            **
** Reentrancy           :                                                     **
**                                                                            **
** Input Parameters     :                                                     **
**                                                                            **
** Output Parameters    :                                                     **
**                                                                            **
** Return parameter     :                                                     **
**                                                                            **
** Preconditions        :                                                     **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                                                                            **
**                        Function(s) invoked:                                **
**                                                                            **
*******************************************************************************/
#if (IPDUM_RX_CONTAINER == STD_ON)
#if (IPDUM_RX_DEFFERRED_CONTAINER == STD_ON)
LOCAL_INLINE FUNC(void, IPDUM_CODE) IpduM_EnqueueRxContainerPdu(
  IpduM_RxContainerIntType ContainerId,
  P2CONST(PduInfoType, AUTOMATIC, IPDUM_APPL_DATA) PduInfoPtr)
{
  P2VAR(uint8, AUTOMATIC, IPDUM_VAR) ptrRxBuf;
  PduLengthType writeIdx;
  uint32 queueBufIdx;
  PduLengthType pduLength;
  uint8 errorId;

  /* If number of instance would exceed the queue size */
  if (IpduM_GetMaxNoOfInstanceRxContainer(ContainerId) <= IpduM_GetCntOfQueuedInstanceRxContainer(ContainerId))
  {
    /* @Trace: IpduM_SUD_API_266 */
    errorId = IPDUM_E_QUEUEOVFL;

    SchM_Enter_IpduM_RX_CONTAINER_PROTECTION_AREA();
    /* Increase read pointer as the oldest instance shall be overwritten */
    IpduM_IncReadCntInstanceRxContainer(ContainerId);
    if (IpduM_GetMaxNoOfInstanceRxContainer(ContainerId) <= IpduM_GetReadCntInstanceRxContainer(ContainerId))
    {
      /* @Trace: IpduM_SUD_API_267 */
      IpduM_SetReadCntInstanceRxContainer(ContainerId, (uint8)IPDUM_ZERO);
    }
    else
    {
      /* No action */
    }
    /* @Trace: IpduM_SUD_API_268 */
    SchM_Exit_IpduM_RX_CONTAINER_PROTECTION_AREA();

    /* Report to DET with error IPDUM_E_QUEUEOVFL */
    (void)Det_ReportRuntimeError((uint16)IPDUM_MODULE_ID, IPDUM_INSTANCE_ID, IPDUM_RXINDICATION_SID, errorId);
  }
  else
  {
    /* @Trace: IpduM_SUD_API_269 */
    SchM_Enter_IpduM_RX_CONTAINER_PROTECTION_AREA();
    IpduM_IncCntOfQueuedInstanceRxContainer(ContainerId);
    SchM_Exit_IpduM_RX_CONTAINER_PROTECTION_AREA();
  }

  /* Enqueue the Rx ContainerPdu */

  if (IpduM_GetMaxSizeOfInstanceRxContainer(ContainerId) < PduInfoPtr->SduLength)
  {
    /* @Trace: IpduM_SUD_API_270 */
    pduLength = IpduM_GetMaxSizeOfInstanceRxContainer(ContainerId);
  }
  else
  {
    /* @Trace: IpduM_SUD_API_271 */
    pduLength = PduInfoPtr->SduLength;
  }
  /* @Trace: IpduM_SUD_API_272 */
  ptrRxBuf = IpduM_GetBasedAddrRxContainerBuf(ContainerId);
  writeIdx = IpduM_GetMaxSizeOfInstanceRxContainer(ContainerId) * \
             IpduM_GetWriteCntInstanceRxContainer(ContainerId);
  /* Store the Rx ContainerPdu to buffer for defferred processing */
  IpduM_CopyData(PduInfoPtr->SduDataPtr, &ptrRxBuf[writeIdx], pduLength);

  queueBufIdx = IpduM_GetQueuedInstanceRxContainerBufIdx(ContainerId) + \
                IpduM_GetWriteCntInstanceRxContainer(ContainerId);
  #if (IPDUM_META_DATA_SUPPORT == STD_ON)
  if ((NULL_PTR != PduInfoPtr->MetaDataPtr) && \
      (FALSE != IpduM_IsRxContainerMetaDataSupport(ContainerId)))
  {
    /* @Trace: IpduM_SUD_API_273 */
    ptrRxBuf = IpduM_GetBasedAddrRxContainerMetaDataBuffer(ContainerId);
    writeIdx = IpduM_GetRxContainerMetaDataLength(ContainerId) * IpduM_GetWriteCntInstanceRxContainer(ContainerId);
    /* Store the Rx ContainerPdu to MetaData buffer for defferred processing */
    IpduM_CopyData(PduInfoPtr->MetaDataPtr, &ptrRxBuf[writeIdx], IpduM_GetRxContainerMetaDataLength(ContainerId));

    /* Specifies that existing metadata in the queued instance */
    IpduM_SetQueuedInstanceRxContainerSupportMetaData(queueBufIdx, TRUE);
  }
  else
  {
    /* @Trace: IpduM_SUD_API_274 */
    /* Specifies that no existing metadata in the queued instance */
    IpduM_SetQueuedInstanceRxContainerSupportMetaData(queueBufIdx, FALSE);
  }
  #endif
  /* @Trace: IpduM_SUD_API_275 */
  SchM_Enter_IpduM_RX_CONTAINER_PROTECTION_AREA();
  /* Update write pointer */
  IpduM_IncWriteCntInstanceRxContainer(ContainerId);
  if (IpduM_GetMaxNoOfInstanceRxContainer(ContainerId) <= IpduM_GetWriteCntInstanceRxContainer(ContainerId))
  {
    /* @Trace: IpduM_SUD_API_276 */
    IpduM_SetWriteCntInstanceRxContainer(ContainerId, (uint8)IPDUM_ZERO);
  }
  else
  {
    /* No action */
  }
  /* @Trace: IpduM_SUD_API_277 */
  SchM_Exit_IpduM_RX_CONTAINER_PROTECTION_AREA();

  /* Store the length of instance Rx ContainerPdu has been queued */
  IpduM_SetSizeOfQueuedInstanceRxContainer(queueBufIdx, pduLength);
} /* End of IpduM_EnqueueRxContainerPdu() */
#endif /* (IPDUM_RX_DEFFERRED_CONTAINER == STD_ON) */
#endif /*(IPDUM_RX_CONTAINER == STD_ON) */

/*******************************************************************************
** Function Name        :                                                     **
**                                                                            **
** Service ID           : Not applicable                                      **
**                                                                            **
** Description          :                                                     **
**                                                                            **
** Reentrancy           :                                                     **
**                                                                            **
** Input Parameters     :                                                     **
**                                                                            **
** Output Parameters    :                                                     **
**                                                                            **
** Return parameter     :                                                     **
**                                                                            **
** Preconditions        :                                                     **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                                                                            **
**                        Function(s) invoked:                                **
**                                                                            **
*******************************************************************************/
#if (IPDUM_RX_CONTAINER == STD_ON)
#if (IPDUM_RX_DEFFERRED_CONTAINER == STD_ON)
FUNC(void, IPDUM_CODE) IpduM_ExtractQueuedRxContainer(
  IpduM_RxContainerIntType ContainerId)
{
  PduInfoType pduInfo;
  PduLengthType readIdx;
  uint32 queueBufIdx;
  P2CONST(uint8, AUTOMATIC, IPDUM_VAR) prtSduBuf;
  #if (IPDUM_META_DATA_SUPPORT == STD_ON)
  /* @Trace: IpduM_SUD_API_278 */
  P2CONST(uint8, AUTOMATIC, IPDUM_VAR) prtMetaDataBuf;
  pduInfo.MetaDataPtr = IpduM_GetAddrOfDeferredRxContainerMetaDataBuf();
  #else
  /* @Trace: IpduM_SUD_API_279 */
  pduInfo.MetaDataPtr = NULL_PTR;
  #endif
  /* @Trace: IpduM_SUD_API_280 */
  pduInfo.SduDataPtr = IpduM_GetAddrOfDeferredRxContainerSduBuf();
  prtSduBuf = IpduM_GetBasedAddrRxContainerBuf(ContainerId);

  while ((uint8)IPDUM_ZERO < IpduM_GetCntOfQueuedInstanceRxContainer(ContainerId))
  {
    /* @Trace: IpduM_SUD_API_281 */
    SchM_Enter_IpduM_RX_CONTAINER_PROTECTION_AREA();

    readIdx = IpduM_GetMaxSizeOfInstanceRxContainer(ContainerId) * IpduM_GetReadCntInstanceRxContainer(ContainerId);
    queueBufIdx = IpduM_GetQueuedInstanceRxContainerBufIdx(ContainerId) + IpduM_GetReadCntInstanceRxContainer(ContainerId);

    /* Copy to extra sdu buffer to avoid interrupt by RxIndication while extracting the Rx ContainerPdu */
    IpduM_CopyData(&prtSduBuf[readIdx], pduInfo.SduDataPtr, IpduM_GetSizeOfQueuedInstanceRxContainer(queueBufIdx));

    #if (IPDUM_META_DATA_SUPPORT == STD_ON)
    if (FALSE != IpduM_GetQueuedInstanceRxContainerSupportMetaData(queueBufIdx))
    {
      /* @Trace: IpduM_SUD_API_282 */
      prtMetaDataBuf = IpduM_GetBasedAddrRxContainerMetaDataBuffer(ContainerId);
      readIdx = IpduM_GetRxContainerMetaDataLength(ContainerId) * IpduM_GetReadCntInstanceRxContainer(ContainerId);
      /* Copy to extra metadata buffer to avoid interrupt by RxIndication while extracting the Rx ContainerPdu */
      IpduM_CopyData(&prtMetaDataBuf[readIdx], pduInfo.MetaDataPtr, IpduM_GetRxContainerMetaDataLength(ContainerId));
    }
    else
    {
      /* @Trace: IpduM_SUD_API_283 */
      pduInfo.MetaDataPtr = NULL_PTR;
    }
    #endif

    /* Increase read pointer */
    /* @Trace: IpduM_SUD_API_284 */
    IpduM_IncReadCntInstanceRxContainer(ContainerId);
    if (IpduM_GetMaxNoOfInstanceRxContainer(ContainerId) <= IpduM_GetReadCntInstanceRxContainer(ContainerId))
    {
      /* @Trace: IpduM_SUD_API_285 */
      IpduM_SetReadCntInstanceRxContainer(ContainerId, (uint8)IPDUM_ZERO);
    }
    else
    {
      /* No action */
    }

    /* Drop the Rx ContainerPdu from queue */
    /* @Trace: IpduM_SUD_API_286 */
    IpduM_DecCntOfQueuedInstanceRxContainer(ContainerId);

    SchM_Exit_IpduM_RX_CONTAINER_PROTECTION_AREA();

    pduInfo.SduLength = IpduM_GetSizeOfQueuedInstanceRxContainer(queueBufIdx);

    /* Extract the queued Rx ContainerPdu */
    #if ((IPDUM_RX_DYNAMIC_CONTAINER == STD_ON) && (IPDUM_RX_STATIC_CONTAINER== STD_ON))
    if (FALSE != IpduM_IsRxDynamicContainerPdu(ContainerId))
    #endif
    {
      #if (IPDUM_RX_DYNAMIC_CONTAINER == STD_ON)
      /* @Trace: IpduM_SUD_API_287 */
      IpduM_ExtractRxDynamicContainerPdu(IPDUM_MAINFUNCTIONRX_SID, ContainerId, &pduInfo);
      #endif
    }
    #if ((IPDUM_RX_DYNAMIC_CONTAINER == STD_ON) && (IPDUM_RX_STATIC_CONTAINER== STD_ON))
    else
    #endif
    {
      /* @Trace: IpduM_SUD_API_288 */
      #if (IPDUM_RX_STATIC_CONTAINER== STD_ON)
      IpduM_ExtractRxStaticContainerPdu(IPDUM_MAINFUNCTIONRX_SID, ContainerId, &pduInfo);
      #endif
    }
  }
} /* End of IpduM_ExtractQueuedRxContainer() */
#endif /* (IPDUM_RX_DEFFERRED_CONTAINER == STD_ON) */
#endif /*(IPDUM_RX_CONTAINER == STD_ON) */

/*******************************************************************************
** Function Name        : IpduM_ContainerRxIndication                         **
**                                                                            **
** Service ID           :                                                     **
**                                                                            **
** Description          :                                                     **
**                                                                            **
** Reentrancy           :                                                     **
**                                                                            **
** Input Parameters     :                                                     **
**                                                                            **
** Output Parameters    :                                                     **
**                                                                            **
** Return parameter     :                                                     **
**                                                                            **
** Preconditions        :                                                     **
**                                                                            **
** Remarks              : Global Variable(s) : None                           **
**                                                                            **
**                        Function(s) invoked:                                **
**                                                                            **
*******************************************************************************/
/* @Trace: SWS_IpduM_00202 SWS_IpduM_00203 SWS_IpduM_00205 SWS_IpduM_00250
 * SWS_IpduM_00209
 * SWS_IpduM_00237
 * SRS_IpduM_02820 SRS_IpduM_02824 SRS_IpduM_02825
 */

#if (IPDUM_RX_CONTAINER == STD_ON)
FUNC(void, IPDUM_CODE) IpduM_ContainerRxIndication(
  IpduM_RxContainerIntType ContainerId,
  P2CONST(PduInfoType, AUTOMATIC, IPDUM_APPL_DATA) PduInfoPtr)
{
  #if (IPDUM_RX_STATIC_CONTAINER == STD_ON)
  if ((FALSE == IpduM_IsRxDynamicContainerPdu(ContainerId)) &&
      ((IpduM_GetMinSizeOfInstanceRxContainer(ContainerId) > PduInfoPtr->SduLength) ||
        (IpduM_GetMaxSizeOfInstanceRxContainer(ContainerId) < PduInfoPtr->SduLength)))
  {
    /* @Trace: IpduM_SUD_API_289 */
    /* Ignore all contained PDUs that are according to their configuration not
    * or not completely contained in the received Container PDU. Report to DET
    * with error IPDUM_E_CONTAINER if Development Error Detection is configured
    */
    #if (IPDUM_DEV_ERROR_DETECT == STD_ON)
    (void)Det_ReportError((uint16)IPDUM_MODULE_ID, IPDUM_INSTANCE_ID, IPDUM_RXINDICATION_SID, IPDUM_E_CONTAINER);
    #endif
  }
  else
  #endif
  {
    #if (IPDUM_RX_DEFFERRED_CONTAINER == STD_ON)
    if (FALSE != IpduM_IsRxContainerPduImmediateProcessing(ContainerId))
    #endif
    {
      #if ((IPDUM_RX_DYNAMIC_CONTAINER == STD_ON) && (IPDUM_RX_STATIC_CONTAINER == STD_ON))
      if (FALSE != IpduM_IsRxDynamicContainerPdu(ContainerId))
      #endif
      {
        /* @Trace: IpduM_SUD_API_290 */
        #if (IPDUM_RX_DYNAMIC_CONTAINER == STD_ON)
        IpduM_ExtractRxDynamicContainerPdu(IPDUM_RXINDICATION_SID, ContainerId, PduInfoPtr);
        #endif
      }
      #if ((IPDUM_RX_DYNAMIC_CONTAINER == STD_ON) && (IPDUM_RX_STATIC_CONTAINER == STD_ON))
      else
      #endif
      {
        /* @Trace: IpduM_SUD_API_291 */
        #if (IPDUM_RX_STATIC_CONTAINER == STD_ON)
        IpduM_ExtractRxStaticContainerPdu(IPDUM_RXINDICATION_SID, ContainerId, PduInfoPtr);
        #endif
      }
    }
    #if (IPDUM_RX_DEFFERRED_CONTAINER == STD_ON)
    else
    {
      /* @Trace: IpduM_SUD_API_292 */
      IpduM_EnqueueRxContainerPdu(ContainerId, PduInfoPtr);
    }
    #endif
  }
} /* End of IpduM_ContainerRxIndication() */
#endif /* (IPDUM_RX_CONTAINER == STD_ON) */

/*******************************************************************************
** Function Name        : IpduM_InitContainer                                 **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function initiates for all configured          **
**                        TxContainer and RxContainer                         **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
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
** Remarks              : Global Variable(s) :                                **
**                                                                            **
**                                                                            **
**                                                                            **
**                        Function(s) invoked:                                **
**                                                                            **
**                                                                            **
*******************************************************************************/
#if (IPDUM_TX_CONTAINER == STD_ON)
FUNC(void, IPDUM_CODE) IpduM_InitContainer(void)
{
  #if (IPDUM_TX_CONF_CONTAINER == STD_ON)
  IpduM_TxContainedIntType TxContainedConfirmArrIdx;
  IpduM_TxContainerIntType TxContainerHandlingBufIdx;

  TxContainedConfirmArrIdx = (IpduM_TxContainedIntType)IPDUM_ZERO;
  while (TxContainedConfirmArrIdx < IPDUM_TX_CONTAINER_CONFIRM_BUFFERSIZE)
  {
    /* @Trace: IpduM_SUD_API_293 */
    IpduM_SetContainedTxPduIdxToConfBuf(TxContainedConfirmArrIdx, IPDUM_TXCONTAINED_INVALID_IDX);
    TxContainedConfirmArrIdx++;
  }
  #endif /* (IPDUM_TX_CONF_CONTAINER == STD_ON) */

  TxContainerHandlingBufIdx = (IpduM_TxContainerIntType)IPDUM_ZERO;
  while (TxContainerHandlingBufIdx < IPDUM_NO_OF_TX_CONTAINERS)
  {
    /* @Trace: IpduM_SUD_API_294 */
	IpduM_SetWriteCntInstanceTxContainer(TxContainerHandlingBufIdx, IPDUM_ZERO);
	IpduM_SetReadCntInstanceTxContainer(TxContainerHandlingBufIdx, IPDUM_ZERO);
	IpduM_SetCntOfQueuedInstanceTxContainer(TxContainerHandlingBufIdx, IPDUM_ZERO);
	IpduM_SetCurrInstanceLengthOfTxContainer(TxContainerHandlingBufIdx, IPDUM_ZERO);
	TxContainerHandlingBufIdx++;
  }

} /* End of IpduM_InitContainer() */
#endif /* (IPDUM_TX_CONTAINER == STD_ON) */

/*******************************************************************************
** Function Name        : IpduM_StoreDynIndAndUpdrJIT                         **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This is a Subfunction for IpduM_TxIpduMux           **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
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
** Remarks              : Global Variable(s) :                                **
**                                                                            **
**                                                                            **
**                                                                            **
**                        Function(s) invoked:                                **
**                                                                            **
**                                                                            **
*******************************************************************************/
#if (IPDUM_TX_IPDU == STD_ON)
FUNC(Std_ReturnType, IPDUM_CODE) IpduM_StoreDynIndAndUpdrJIT(
  boolean triggerFlag, 
  IpduM_TxPartIntType secPartIdx, 
  IpduM_TxPartIntType dynPartIdx, 
  IpduM_TxPartIntType TxOutIpduId)
{
  /* @Trace: IpduM_SUD_API_401 */
  Std_ReturnType retVal;
  IpduM_TxConfIntType confIdx;
  uint8 confMask;
  retVal = E_OK;
  confIdx = IpduM_GetTxMuxByteIdxOfConfPendingFlagBuf(TxOutIpduId);
  confMask = IpduM_GetTxMuxByteMaskOfConfPendingFlagBuf(TxOutIpduId);
  if (FALSE != triggerFlag)
  {
    #if ((IPDUM_TX_STATIC_IPDU == STD_ON) && (IPDUM_JIT_UPDATE == STD_ON))
    /* polyspace +2 RTE:OBAI [Not a defect:Low] "Array access index is in-bounds. This is assured by generator" */
    if ((IPDUM_TXPART_INVALID_IDX != secPartIdx) &&
        (FALSE != IpduM_IsTxPartJITRequired(secPartIdx)))
    {
      /* @Trace: IpduM_SUD_API_049 */
      /* Just-In-Time update of Static or Dynamic Part */
      retVal = IpduM_FetchTxMuxIpduPart(secPartIdx);
    }
    else
    {
      /* No action */
    }
    /* Check if JIT update is successful */
    if (E_OK == retVal)
    #else
    IPDUM_UNUSED(secPartIdx);
    #endif
    {
      /* @Trace: IpduM_SUD_API_050 */
      /* Send out the multiplexed I-PDU */
      retVal = PduR_IpduMTransmit(IpduM_GetTxMuxOutgoingRefPduId(TxOutIpduId),
                                  IpduM_GetTxMuxPduInfoPtr(TxOutIpduId));
    }
    #if ((IPDUM_TX_STATIC_IPDU == STD_ON) && (IPDUM_JIT_UPDATE == STD_ON))
    else
    {
      /* No action */
    }
    #endif

    #if (IPDUM_TX_CONF_IPDU == STD_ON)
    /* Check the condition of setting Tx Confirmation is satisfied */
    if ((FALSE != IpduM_IsTxMuxConfEnabled(TxOutIpduId)) && (E_OK == retVal))
    {
      /* Store index of dynamic part contained in last sent out I-PDU */
      /* polyspace +3 RTE:OBAI [Not a defect:Low] "Array access index is in-bounds. This is assured by generator" */
      /* polyspace +2 RTE:IDP [Not a defect:Low] "Pointer is not null and inside its bound. This is assured by generator" */
      SchM_Enter_IpduM_TX_STATUS_PROTECTION_AREA();
      if ((IPDUM_TXPART_INVALID_IDX != dynPartIdx) && \
          (IpduM_GetTxMuxConfDynPart((IpduM_GetIdxOfConfDynTxPartBuf(TxOutIpduId))) != dynPartIdx))
      {
        /* @Trace: IpduM_SUD_API_051 */
        IpduM_SetTxMuxConfDynPart((IpduM_GetIdxOfConfDynTxPartBuf(TxOutIpduId)), dynPartIdx);
      }
      else
      {
        /* No action */
      }
      SchM_Exit_IpduM_TX_STATUS_PROTECTION_AREA();
      /* @Trace: IpduM_SUD_API_052 */
      /* Reset pending flag */
      IpduM_SetTxConfPendingFlag(confIdx, confMask);
    } /* End of checking the condition of setting Tx Confirmation */
    else
    {
      /* No action */
    }
    #endif
  } /* End of checking the trigger transmission flag */
  else
  {
    /* No action */
  }
  
  /* @Trace: IpduM_SUD_API_402 */
  return retVal;
}

#endif /*IPDUM_TX_IPDU == STD_ON*/

#define IPDUM_STOP_SEC_CODE
#include "MemMap.h"

#endif /* IPDUM_ENABLE_MODULE == STD_ON */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
